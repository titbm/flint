#!/usr/bin/env python3
"""
simulate_continuation.py — Simulation of FLINT process() continuation logic.

Reads BFT data file and CFG config, then simulates:
  1) Full run from point 0 to point N  (first run)
  2) Continuation run from point N     (second run, no move_sen)

Compares the positions at each step to detect any discrepancy
that could explain the Z-axis shift seen in reconstructed FLINT.

Usage:
  python simulate_continuation.py [options]

  --bft FILE     BFT data file   (default: ../Flint 2.77 src/BUILD/BFT_FILES/cube.bft)
  --cfg FILE     CFG config file  (default: ../Flint 2.77 src/BUILD/FLINT1.CFG)
  --break N      Stop first run at point N (0-based), then continue (default: 10)
  --points M     Process M points after continuation  (default: 5)
  --verbose      Show every point's state
  --all          Process all points (first run + continuation = full run)
"""

import struct
import sys
import os
import argparse
import math

# ═══════════════════════════════════════════════════════════════
#  BFT file parser
# ═══════════════════════════════════════════════════════════════

def read_bft(path):
    """Read BFT file: 14-byte header + int16 triplets.
    Returns (nglas, xsize, ysize, zsize, nmax, points[])
    where points[i] = (x, y, z) raw int16 values."""
    with open(path, "rb") as f:
        hdr = f.read(14)
    if len(hdr) < 14:
        raise ValueError(f"BFT header too short: {len(hdr)} bytes")
    magic, nglas_i, xsize, ysize, zsize, nmax_hi, nmax_lo = struct.unpack("<7H", hdr)
    if magic != 0x6662:
        raise ValueError(f"Bad BFT magic: 0x{magic:04X} (expected 0x6662)")
    nglas = nglas_i / 1000.0
    nmax = nmax_hi * 65536 + nmax_lo

    with open(path, "rb") as f:
        f.seek(14)
        raw = f.read(nmax * 6)  # 3 x int16 per point
    points = []
    for i in range(nmax):
        off = i * 6
        x, y, z = struct.unpack_from("<3h", raw, off)
        points.append((x, y, z))
    return nglas, xsize, ysize, zsize, nmax, points


# ═══════════════════════════════════════════════════════════════
#  CFG file parser
# ═══════════════════════════════════════════════════════════════

def read_cfg(path):
    """Read CFG file (newline-separated fields).
    Returns dict with: xptr, yptr, zptr, step, l_period, gate_delay,
                        step_freq, f_const, dT, sh_delay [, glpos9]"""
    with open(path, "rb") as f:
        data = f.read()
    lines = data.replace(b"\r\n", b"\n").replace(b"\r", b"\n").split(b"\n")
    vals = [l.strip() for l in lines if l.strip()]
    names = ["xptr", "yptr", "zptr", "step", "l_period", "gate_delay",
             "step_freq", "f_const", "dT", "sh_delay", "glpos9"]
    cfg = {}
    for i, name in enumerate(names):
        if i < len(vals):
            try:
                cfg[name] = int(vals[i])
            except ValueError:
                cfg[name] = 0
    return cfg


# ═══════════════════════════════════════════════════════════════
#  Process simulation
# ═══════════════════════════════════════════════════════════════

class FlintSim:
    """Simulates the FLINT process() and dlgstart() flow."""

    def __init__(self, bft_path, cfg_path):
        self.nglas, self.xsize, self.ysize, self.zsize, self.nmax, self.points = read_bft(bft_path)
        self.cfg = read_cfg(cfg_path)
        self.xptr = self.cfg["xptr"]
        self.yptr = self.cfg["yptr"]
        self.zptr = self.cfg["zptr"]

        # State variables (globals)
        self.xcur = 0
        self.ycur = 0
        self.zcur = 0
        self.do_ptr = 0
        self.f_ptr = 0
        self.lastn = 0
        self.start_nmb = 0

        # Refraction offset — constant for the entire run
        self.refr_ofs = int(self.zsize * 10 * (1 - 1.0 / self.nglas))
        # NOTE: the C code does: znew = 11000 - zptr - zsize*10*(1-1/nglas) - iTabl[3*i+2]
        # In 16-bit C: zsize*10 is int16 * int16 = int16 (may overflow!)
        # In 32-bit C: zsize*10 is int32 * int32 = int32 (no overflow)
        # The FPU computation (1-1/nglas) is done in extended precision.
        # Then zsize*10*(1-1/nglas) converts int to double, multiplies.
        # Final result is truncated to int by F_FTOL (Borland) or cast (Watcom).

        # Compute the exact floating-point value for reference:
        self.z_refr_fp = self.zsize * 10 * (1.0 - 1.0 / self.nglas)
        self.z_base_fp = 11000 - self.zptr - self.z_refr_fp

        # Integer version (as the binary does it):
        # zsize*10 in 16-bit int:
        zs10_16 = (self.zsize * 10) & 0xFFFF
        if zs10_16 >= 0x8000:
            zs10_16 -= 0x10000  # sign-extend
        self.zs10_16 = zs10_16
        # In the FPU, zsize*10 is loaded via fild (sign-extended 16-bit)
        # then multiplied by (1-1/nglas).
        self.z_refr_16 = zs10_16 * (1.0 - 1.0 / self.nglas)
        # z_base: 11000-zptr is also a 16-bit int subtraction
        zbase_int16 = (11000 - self.zptr) & 0xFFFF
        if zbase_int16 >= 0x8000:
            zbase_int16 -= 0x10000
        self.zbase_int16 = zbase_int16

    def info(self):
        """Print configuration summary."""
        print("=" * 70)
        print("FLINT Continuation Simulation")
        print("=" * 70)
        print(f"  nglas   = {self.nglas:.4f}")
        print(f"  xsize   = {self.xsize}  ysize = {self.ysize}  zsize = {self.zsize}")
        print(f"  nmax    = {self.nmax}")
        print(f"  xptr    = {self.xptr}  yptr = {self.yptr}  zptr = {self.zptr}")
        print(f"  refr_ofs (int)      = {self.refr_ofs}")
        print(f"  refr_ofs (float)    = {self.z_refr_fp:.6f}")
        print(f"  z_base  (float)     = {self.z_base_fp:.6f}")
        print(f"  zsize*10 (16-bit)   = {self.zs10_16}")
        print(f"  z_refr  (via 16-bit)= {self.z_refr_16:.6f}")
        print(f"  11000-zptr (16-bit) = {self.zbase_int16}")
        print(f"  First point raw: {self.points[0]}")
        if self.nmax > 1:
            print(f"  Last  point raw: {self.points[self.nmax - 1]}")
        print()

    def calc_point(self, i, use_16bit=True):
        """Calculate xnew, ynew, znew for point i.
        
        If use_16bit=True, simulates the 16-bit C behavior:
          xnew = (int16)(23500 - xptr) - iTabl[3*i]
          ynew = (int16)(yptr) + iTabl[3*i+1]  
          znew = (int)( (float)(int16)(11000-zptr) - (float)(int16)(zsize*10) * (1-1/nglas) ) - iTabl[3*i+2]
        """
        px, py, pz = self.points[i]

        if use_16bit:
            # 16-bit integer arithmetic for X and Y
            xnew_16 = ((23500 - self.xptr) & 0xFFFF)
            if xnew_16 >= 0x8000: xnew_16 -= 0x10000
            xnew = xnew_16 - px

            ynew = self.yptr + py

            # Z: FPU computation path from binary
            # fild(int16(11000-zptr))  - fild(int16(zsize*10)) * (1-1/nglas) - fild(int16(iTabl_z))
            # Then F_FTOL truncates to int
            z_float = float(self.zbase_int16) - float(self.zs10_16) * (1.0 - 1.0 / self.nglas) - float(pz)
            znew = int(z_float)  # F_FTOL truncates toward zero
        else:
            # 32-bit / straightforward computation
            xnew = 23500 - self.xptr - px
            ynew = self.yptr + py
            z_float = 11000 - self.zptr - self.zsize * 10 * (1.0 - 1.0 / self.nglas) - pz
            znew = int(z_float)

        return xnew, ynew, znew

    def move_sen(self, direction=0):
        """Simulate move_sen(0): go to home position."""
        if direction == 0:
            self.xcur = 23300
            self.ycur = 200
            self.zcur = 200
        self.do_ptr = int(not direction)

    def move(self, x, y, z):
        """Simulate move(): set position (f_demo mode)."""
        dx = x - self.xcur
        dy = y - self.ycur
        dz = z - self.zcur
        self.xcur = x
        self.ycur = y
        self.zcur = z
        return dx, dy, dz

    def process(self, start, end, verbose=False, label=""):
        """Simulate process() loop from start to end (exclusive).
        Returns list of (i, xnew, ynew, znew, dx, dy, dz) tuples."""
        results = []

        if verbose:
            print(f"\n--- process({label}) start_nmb={start} → {end-1} ---")
            print(f"  Before: xcur={self.xcur} ycur={self.ycur} zcur={self.zcur} do_ptr={self.do_ptr}")

        # Check if move_sen should be called
        if self.f_ptr or (not self.do_ptr):
            if verbose:
                print(f"  >>> move_sen(0) CALLED (f_ptr={self.f_ptr}, do_ptr={self.do_ptr})")
            self.move_sen(0)
            if verbose:
                print(f"  After move_sen: xcur={self.xcur} ycur={self.ycur} zcur={self.zcur} do_ptr={self.do_ptr}")
        else:
            if verbose:
                print(f"  >>> move_sen SKIPPED (f_ptr={self.f_ptr}, do_ptr={self.do_ptr})")

        for i in range(start, min(end, self.nmax)):
            xnew, ynew, znew = self.calc_point(i)
            dx, dy, dz = self.move(xnew, ynew, znew)
            results.append((i, xnew, ynew, znew, dx, dy, dz))
            self.lastn = i + 1

            if verbose:
                px, py, pz = self.points[i]
                print(f"  pt[{i:5d}] raw=({px:6d},{py:6d},{pz:6d}) "
                      f"→ xyz=({xnew:6d},{ynew:6d},{znew:6d}) "
                      f"d=({dx:6d},{dy:6d},{dz:6d})")

        if verbose:
            print(f"  After: xcur={self.xcur} ycur={self.ycur} zcur={self.zcur} lastn={self.lastn}")

        return results


def run_simulation(args):
    """Main simulation: first run + continuation, compare positions."""
    sim = FlintSim(args.bft, args.cfg)
    sim.info()

    break_pt = args.break_pt
    cont_pts = args.points

    if break_pt >= sim.nmax:
        print(f"ERROR: break point {break_pt} >= nmax {sim.nmax}")
        return

    end_pt = min(break_pt + cont_pts, sim.nmax) if not args.all else sim.nmax

    # ═══════════════════════════════════════════════════════════
    # SCENARIO A: Full run from beginning to end_pt (no interruption)
    # ═══════════════════════════════════════════════════════════
    print("=" * 70)
    print("SCENARIO A: Full run (no interruption)")
    print("=" * 70)
    sim_a = FlintSim(args.bft, args.cfg)  # fresh state
    results_a = sim_a.process(0, end_pt, verbose=args.verbose, label="full")
    print(f"  Final position: xcur={sim_a.xcur} ycur={sim_a.ycur} zcur={sim_a.zcur}")
    print(f"  Points processed: 0 to {sim_a.lastn - 1}")

    # ═══════════════════════════════════════════════════════════
    # SCENARIO B: First run (0 to break_pt), ESC, then continuation
    # ═══════════════════════════════════════════════════════════
    print()
    print("=" * 70)
    print(f"SCENARIO B: First run (0..{break_pt-1}), ESC, continuation ({break_pt}..{end_pt-1})")
    print("=" * 70)

    sim_b = FlintSim(args.bft, args.cfg)  # fresh state

    # --- First run ---
    print("\n[Phase 1] First run: 0 to", break_pt - 1)
    results_b1 = sim_b.process(0, break_pt, verbose=args.verbose, label="first")
    
    # Simulate ESC: process() returns 0
    # In dlgstart: STEP_OFF, FlashWr(), "Finished point: N", return 0
    esc_xcur = sim_b.xcur
    esc_ycur = sim_b.ycur
    esc_zcur = sim_b.zcur
    esc_lastn = sim_b.lastn
    esc_do_ptr = sim_b.do_ptr
    print(f"  ESC pressed. State saved:")
    print(f"    xcur={esc_xcur} ycur={esc_ycur} zcur={esc_zcur}")
    print(f"    lastn={esc_lastn} do_ptr={esc_do_ptr}")

    # Between runs: dlgstart returns, user presses F5 again
    # Nothing modifies xcur/ycur/zcur between the two dlgstart calls.

    # --- Continuation run ---
    print(f"\n[Phase 2] Continuation from point {break_pt}")
    # In dlgstart, before Ok: st_nmbnew = lastn
    st_nmbnew = sim_b.lastn
    # On Ok: start_nmb = st_nmbnew
    sim_b.start_nmb = st_nmbnew
    # lastn = start_nmb (redundant)
    sim_b.lastn = sim_b.start_nmb
    # f_start=2, so ClearRpt NOT called, CMOS NOT reset
    # mainscr(1) — purely visual
    # STEP_ON, delay(30)
    print(f"  start_nmb = {sim_b.start_nmb}")
    print(f"  State before process(): xcur={sim_b.xcur} ycur={sim_b.ycur} zcur={sim_b.zcur} do_ptr={sim_b.do_ptr}")
    
    results_b2 = sim_b.process(int(sim_b.start_nmb), end_pt, verbose=args.verbose, label="continuation")
    print(f"  Final position: xcur={sim_b.xcur} ycur={sim_b.ycur} zcur={sim_b.zcur}")
    print(f"  Points processed: {break_pt} to {sim_b.lastn - 1}")

    # ═══════════════════════════════════════════════════════════
    # COMPARISON
    # ═══════════════════════════════════════════════════════════
    print()
    print("=" * 70)
    print("COMPARISON: Scenario A vs Scenario B")
    print("=" * 70)
    
    # Build lookup for scenario A
    a_by_idx = {r[0]: r for r in results_a}
    # Build lookup for scenario B (both phases)
    b_by_idx = {}
    for r in results_b1:
        b_by_idx[r[0]] = r
    for r in results_b2:
        b_by_idx[r[0]] = r

    diffs = 0
    for i in sorted(set(a_by_idx.keys()) | set(b_by_idx.keys())):
        if i in a_by_idx and i in b_by_idx:
            a = a_by_idx[i]
            b = b_by_idx[i]
            # Compare (xnew, ynew, znew)
            if a[1:4] != b[1:4]:
                print(f"  DIFF pt[{i}]: A=xyz({a[1]},{a[2]},{a[3]}) B=xyz({b[1]},{b[2]},{b[3]})")
                diffs += 1
            # Compare (dx, dy, dz) — these depend on xcur which could differ at break point
            if a[4:7] != b[4:7]:
                if i == break_pt:
                    print(f"  NOTE pt[{i}]: Delta differs at break point (expected): "
                          f"A=d({a[4]},{a[5]},{a[6]}) B=d({b[4]},{b[5]},{b[6]})")
                else:
                    print(f"  DIFF pt[{i}]: A=d({a[4]},{a[5]},{a[6]}) B=d({b[4]},{b[5]},{b[6]})")
                    diffs += 1

    if diffs == 0:
        print("\n  >>> NO DIFFERENCES FOUND <<<")
        print("  The continuation math is correct. The positions are identical")
        print("  whether run continuously or with interruption + continuation.")
        print()
        print("  If the user sees a Z shift, the cause is NOT in the process()")
        print("  formula or continuation logic. Possible causes:")
        print("    1. Hardware timing (move() not completing fully)")
        print("    2. Sensor errors causing move_sen(0) reboot mid-run")
        print("    3. Some code path modifying xcur/ycur/zcur between runs")
        print("    4. Display-only issue in draw()")
    else:
        print(f"\n  >>> {diffs} DIFFERENCES FOUND <<<")
        print("  There is a logic bug in the continuation path!")

    # ═══════════════════════════════════════════════════════════
    # Additional analysis: check for 16-bit vs 32-bit differences
    # ═══════════════════════════════════════════════════════════
    print()
    print("=" * 70)
    print("16-BIT vs 32-BIT FORMULA COMPARISON")
    print("=" * 70)

    sim16 = FlintSim(args.bft, args.cfg)
    sim32 = FlintSim(args.bft, args.cfg)
    
    type_diffs = 0
    for i in range(min(sim.nmax, 20)):  # check first 20 points
        x16, y16, z16 = sim16.calc_point(i, use_16bit=True)
        x32, y32, z32 = sim32.calc_point(i, use_16bit=False)
        if x16 != x32 or y16 != y32 or z16 != z32:
            print(f"  pt[{i}]: 16bit=({x16},{y16},{z16}) 32bit=({x32},{y32},{z32})")
            type_diffs += 1

    if type_diffs == 0:
        print(f"  No 16/32-bit differences for first {min(sim.nmax, 20)} points.")
    else:
        print(f"  {type_diffs} differences found between 16-bit and 32-bit formulas!")
        print("  This could explain the issue if the original binary uses 16-bit truncation.")


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    base_dir = os.path.dirname(script_dir)

    parser = argparse.ArgumentParser(description="FLINT continuation simulation")
    parser.add_argument("--bft", default=os.path.join(base_dir, "Flint 2.77 src", "BUILD", "BFT_FILES", "cube.bft"),
                        help="BFT data file path")
    parser.add_argument("--cfg", default=os.path.join(base_dir, "Flint 2.77 src", "BUILD", "FLINT1.CFG"),
                        help="CFG config file path")
    parser.add_argument("--break", dest="break_pt", type=int, default=10,
                        help="Break first run at this point (0-based, default: 10)")
    parser.add_argument("--points", type=int, default=5,
                        help="Process this many points after continuation (default: 5)")
    parser.add_argument("--verbose", action="store_true",
                        help="Show every point's state")
    parser.add_argument("--all", action="store_true",
                        help="Process all points (continuation to end)")
    args = parser.parse_args()

    run_simulation(args)


if __name__ == "__main__":
    main()
