"""
Hardware simulator for Flint KPU (counter/motor board).

Models the actual hardware behavior:
- PT0/PT1 counters (step pulse generators per axis)
- Motor step counting (physical position tracking)
- ADRRG register (motor enable/direction)
- Sensor states (end sensors, optical sensors)

Runs through process() scenarios with real BFT data and config,
comparing xcur/ycur/zcur (software position) with physical position
(counter-based step count).

Simulates both 2.61 k2 formula and 2.77 k2 formula to see differences.
"""

import struct
import sys
import os
import math

# ─── Hardware constants ────────────────────────────────────
XUP   = 0x01;  XDOWN = 0xFE
YUP   = 0x02;  YDOWN = 0xFD
ZUP   = 0x04;  ZDOWN = 0xFB
XON   = 0x08;  XOFF  = 0xF7
YON   = 0x10;  YOFF  = 0xEF
ZON   = 0x20;  ZOFF  = 0xDF
OSCON = 0x7F;  OSCOFF= 0x80

# I/O ports
ADRPT0 = 0x300      # PT0: X k2 (0x300), Z k2 (0x302)
ADRPT1 = 0x304      # PT1: Y k2 (0x304), Z d  (0x306)
ADRRG  = 0x30C      # Motor control register
ADRPPI = 0x308      # PPI: sensor input on +1


class Counter:
    """Models one axis counter: programs K2 (period) and d (step count)."""
    def __init__(self, name):
        self.name = name
        self.k2 = 0       # frequency divider (step period = k2 * 10us)
        self.d = 0         # number of steps to count

    def program_k2(self, lo, hi):
        self.k2 = lo + hi * 256

    def program_d(self, lo, hi):
        self.d = lo + hi * 256

    def get_steps(self):
        """Physical steps this counter will produce."""
        return self.d

    def __repr__(self):
        return f"{self.name}(k2={self.k2}, d={self.d})"


class MotorState:
    """Physical motor position tracked by actual counter steps."""
    def __init__(self):
        self.phys_x = 0    # physical X in motor steps
        self.phys_y = 0    # physical Y in motor steps
        self.phys_z = 0    # physical Z in motor steps


class KPU_Simulator:
    """Simulates the KPU counter board hardware."""

    def __init__(self, config):
        self.cfg = config

        # Counters
        self.cnt_x = Counter("X")     # PT0+0  k2, PT0+1 d
        self.cnt_y = Counter("Y")     # PT1+0  k2, PT1+1 d
        self.cnt_z_k2 = Counter("Zk") # PT0+2  k2
        self.cnt_z_d = Counter("Zd")  # PT1+2  d

        # Control register
        self.ctlw = 0x80   # idle state

        # Physical position (actual step count)
        self.phys_x = 0
        self.phys_y = 0
        self.phys_z = 0

        # Software position (as tracked by code)
        self.xcur = 0
        self.ycur = 0
        self.zcur = 0

        # State flags
        self.do_ptr = 0
        self.f_ptr = 0

        self.log_lines = []
        self.verbose = False

    def log(self, msg):
        self.log_lines.append(msg)
        if self.verbose:
            print(msg)

    def outportb(self, port, val):
        """Simulate writing to an I/O port."""
        val = val & 0xFF

        if port == ADRPT0:      # X k2
            if not hasattr(self, '_x_k2_phase'):
                self._x_k2_phase = 0
            if self._x_k2_phase == 0:
                self._x_k2_lo = val
                self._x_k2_phase = 1
            else:
                self.cnt_x.program_k2(self._x_k2_lo, val)
                self._x_k2_phase = 0

        elif port == ADRPT0 + 1:  # X d
            if not hasattr(self, '_x_d_phase'):
                self._x_d_phase = 0
            if self._x_d_phase == 0:
                self._x_d_lo = val
                self._x_d_phase = 1
            else:
                self.cnt_x.program_d(self._x_d_lo, val)
                self._x_d_phase = 0

        elif port == ADRPT1:      # Y k2
            if not hasattr(self, '_y_k2_phase'):
                self._y_k2_phase = 0
            if self._y_k2_phase == 0:
                self._y_k2_lo = val
                self._y_k2_phase = 1
            else:
                self.cnt_y.program_k2(self._y_k2_lo, val)
                self._y_k2_phase = 0

        elif port == ADRPT1 + 1:  # Y d
            if not hasattr(self, '_y_d_phase'):
                self._y_d_phase = 0
            if self._y_d_phase == 0:
                self._y_d_lo = val
                self._y_d_phase = 1
            else:
                self.cnt_y.program_d(self._y_d_lo, val)
                self._y_d_phase = 0

        elif port == ADRPT0 + 2:  # Z k2
            if not hasattr(self, '_z_k2_phase'):
                self._z_k2_phase = 0
            if self._z_k2_phase == 0:
                self._z_k2_lo = val
                self._z_k2_phase = 1
            else:
                self.cnt_z_k2.program_k2(self._z_k2_lo, val)
                self._z_k2_phase = 0

        elif port == ADRPT1 + 2:  # Z d
            if not hasattr(self, '_z_d_phase'):
                self._z_d_phase = 0
            if self._z_d_phase == 0:
                self._z_d_lo = val
                self._z_d_phase = 1
            else:
                self.cnt_z_d.program_d(self._z_d_lo, val)
                self._z_d_phase = 0

        elif port == ADRRG:
            self.ctlw = val

    def reset_port_phases(self):
        """Reset all two-phase port write states."""
        for attr in list(self.__dict__):
            if attr.endswith('_phase'):
                setattr(self, attr, 0)

    def execute_movement(self):
        """
        Simulate what happens when ADRRG is written with motor enables.
        The counters produce exactly `d` steps per axis.
        Physical position changes by ±d depending on direction bits.

        Returns (dx_steps, dy_steps, dz_steps) actual physical steps applied.
        """
        ctlw = self.ctlw
        dx = dy = dz = 0

        if ctlw & XON:
            steps = self.cnt_x.get_steps()
            direction = 1 if (ctlw & XUP) else -1
            dx = direction * steps
            self.phys_x += dx

        if ctlw & YON:
            steps = self.cnt_y.get_steps()
            direction = 1 if (ctlw & YUP) else -1
            dy = direction * steps
            self.phys_y += dy

        if ctlw & ZON:
            # Z k2 is in cnt_z_k2, Z d is in cnt_z_d
            steps = self.cnt_z_d.get_steps()
            direction = 1 if (ctlw & ZUP) else -1
            dz = direction * steps
            self.phys_z += dz

        return dx, dy, dz

    # ─── Simulate seg_time (2.77 formula) ────────────────
    def seg_time_277(self, adx, ady, adz):
        t = max(abs(adx), abs(ady))
        if t < abs(adz):
            t = abs(adz)
        ms = t * 1000 // self.cfg['step_freq']
        count = ms // self.cfg['l_period'] + 1
        if ms % self.cfg['l_period'] > self.cfg['l_period'] - self.cfg['dT']:
            count += 1
        return count

    # ─── Simulate calc_k2 (2.77 formula) ─────────────────
    def calc_k2_277(self, delta, t_seg):
        k2min = 100000 // self.cfg['step_freq']
        k2max = 65500
        k2 = k2min
        if not self.cfg['f_const']:
            k2 = (t_seg * self.cfg['l_period'] - self.cfg['dT']) * 100 // abs(delta)
            if k2 < k2min:
                k2 = k2min
            if k2 > k2max:
                k2 = k2max
        return k2

    # ─── Simulate calc_k2 (2.61 formula) ─────────────────
    def calc_k2_261(self, delta):
        k2min = 100000 // self.cfg['step_freq']
        k2max = 65500
        k2 = k2min
        if not self.cfg['f_const']:
            k2 = (self.cfg['l_period'] - 3) * 100 // abs(delta)
            if k2 < k2min:
                k2 = k2min
            if k2 > k2max:
                k2 = k2max
        return k2

    # ─── Simulate move_sen(0) ────────────────────────────
    def sim_move_sen(self, direction=0):
        """Simulate move_sen(dir). Returns to sensor positions."""
        self.reset_port_phases()

        # Phase 1: Move toward end sensors
        # K2=100 for all axes
        for port in [ADRPT0, ADRPT1, ADRPT0+2]:
            self.outportb(port, 0x64)  # lo=100
            self.outportb(port, 0x00)  # hi=0

        # d: X=28672, Y=28672, Z=16384
        for port in [ADRPT0+1, ADRPT1+1]:
            self.outportb(port, 0x00)  # lo=0
            self.outportb(port, 0x70)  # hi=0x70 → 28672

        self.outportb(ADRPT1+2, 0x00)  # Zd lo=0
        self.outportb(ADRPT1+2, 0x40)  # Zd hi=0x40 → 16384

        if direction == 0:
            self.ctlw = (XON | YON | ZON | XUP) & YDOWN & ZDOWN & OSCON
        else:
            self.ctlw = (XON | YON | ZON | XUP | YUP) & ZDOWN & OSCON

        self.log(f"  move_sen({direction}): Phase1 ctlw=0x{self.ctlw:02X}")
        self.log(f"    X: k2={self.cnt_x.k2} d={self.cnt_x.d} dir={'UP' if self.ctlw & XUP else 'DN'}")
        self.log(f"    Y: k2={self.cnt_y.k2} d={self.cnt_y.d} dir={'UP' if self.ctlw & YUP else 'DN'}")
        self.log(f"    Z: k2={self.cnt_z_k2.k2} d={self.cnt_z_d.d} dir={'UP' if self.ctlw & ZUP else 'DN'}")

        # In reality, motors run until END SENSORS trigger.
        # Physical position goes to END SENSOR positions (0,max,max or variant).
        # For dir=0: X goes UP to end, Y goes DOWN to end, Z goes DOWN to end.
        # But end sensors stop the motors before all d steps complete.
        # Physical position after Phase 1: at the end sensor positions.

        # Phase 2: Small reverse to optical sensors
        # K2=200, d=200 for all axes
        self.reset_port_phases()
        for port in [ADRPT0, ADRPT0+1, ADRPT1, ADRPT1+1, ADRPT0+2, ADRPT1+2]:
            self.outportb(port, 0xC8)  # lo=200
            self.outportb(port, 0x00)  # hi=0

        if direction == 0:
            self.ctlw = (XON | YON | ZON | YUP | ZUP) & XDOWN & OSCON
        else:
            self.ctlw = (XON | YON | ZON | ZUP) & XDOWN & YDOWN & OSCON

        self.log(f"  move_sen({direction}): Phase2 ctlw=0x{self.ctlw:02X}")
        self.log(f"    X: k2=200 d=200 dir={'UP' if self.ctlw & XUP else 'DN'}")
        self.log(f"    Y: k2=200 d=200 dir={'UP' if self.ctlw & YUP else 'DN'}")
        self.log(f"    Z: k2=200 d=200 dir={'UP' if self.ctlw & ZUP else 'DN'}")
        self.log(f"    Waiting for optical sensors...")

        # In reality: motors run until optical sensors trigger.
        # For dir=0: X goes DOWN (back from end), Y goes UP, Z goes UP.
        # Optical sensors trigger at known positions → reference point.

        # After move_sen(0): physical position = sensor reference point
        if direction == 0:
            self.phys_x = 23300
            self.phys_y = 200
            self.phys_z = 200
            self.xcur = 23300
            self.ycur = 200
            self.zcur = 200
        # do_ptr = !dir
        self.do_ptr = 0 if direction else 1

        self.ctlw = 0x80  # idle
        self.log(f"  move_sen done: phys=({self.phys_x},{self.phys_y},{self.phys_z}) "
                 f"sw=({self.xcur},{self.ycur},{self.zcur}) do_ptr={self.do_ptr}")

    # ─── Simulate move() with 2.77 formula ──────────────
    def sim_move_277(self, x, y, z):
        """Simulate move(x,y,z) with 2.77 k2 formula.
        Returns True on success, False on simulated error."""
        dx = x - self.xcur
        dy = y - self.ycur
        dz = z - self.zcur

        t_seg = self.seg_time_277(dx, dy, dz)

        self.reset_port_phases()

        # Program counters - exactly as the code does
        phys_dx = phys_dy = phys_dz = 0

        if dx:
            k2 = self.calc_k2_277(dx, t_seg)
            self.outportb(ADRPT0, k2 % 256)
            self.outportb(ADRPT0, k2 // 256)
            self.outportb(ADRPT0 + 1, abs(dx) % 256)
            self.outportb(ADRPT0 + 1, abs(dx) // 256)
            # Physical: counter will produce exactly abs(dx) steps
            phys_dx = dx  # signed

        if dy:
            k2 = self.calc_k2_277(dy, t_seg)
            self.outportb(ADRPT1, k2 % 256)
            self.outportb(ADRPT1, k2 // 256)
            self.outportb(ADRPT1 + 1, abs(dy) % 256)
            self.outportb(ADRPT1 + 1, abs(dy) // 256)
            phys_dy = dy

        if dz:
            k2 = self.calc_k2_277(dz, t_seg)
            self.outportb(ADRPT0 + 2, k2 % 256)
            self.outportb(ADRPT0 + 2, k2 // 256)
            self.outportb(ADRPT1 + 2, abs(dz) % 256)
            self.outportb(ADRPT1 + 2, abs(dz) // 256)
            phys_dz = dz

        # Counter values that were actually programmed
        x_k2_prog = self.cnt_x.k2
        x_d_prog = self.cnt_x.d
        y_k2_prog = self.cnt_y.k2
        y_d_prog = self.cnt_y.d
        z_k2_prog = self.cnt_z_k2.k2
        z_d_prog = self.cnt_z_d.d

        # Check: do the programmed d values match abs(delta)?
        x_match = (x_d_prog == abs(dx)) if dx else True
        y_match = (y_d_prog == abs(dy)) if dy else True
        z_match = (z_d_prog == abs(dz)) if dz else True

        if not (x_match and y_match and z_match):
            self.log(f"  *** COUNTER MISMATCH! dx={dx} prog_d={x_d_prog}  "
                     f"dy={dy} prog_d={y_d_prog}  dz={dz} prog_d={z_d_prog}")

        # Physical position update: the counter produces exactly d steps
        self.phys_x += phys_dx
        self.phys_y += phys_dy
        self.phys_z += phys_dz

        # Software position update
        self.xcur = x
        self.ycur = y
        self.zcur = z

        return True

    # ─── Simulate process() ──────────────────────────────
    def sim_process(self, points, run_label="", use_261_formula=False):
        """Simulate a full process() run with given points.
        points: list of (raw_x, raw_y, raw_z) from BFT table
        """
        xptr = self.cfg['xptr']
        yptr = self.cfg['yptr']
        zptr = self.cfg['zptr']
        zsize = self.cfg['zsize']
        nglas = self.cfg['nglas']
        nmax = len(points)

        refr_ofs = int(zsize * 10 * (1 - 1/nglas))
        z_base = 11000 - zptr - refr_ofs

        self.log(f"\n{'='*60}")
        self.log(f"PROCESS {run_label}: {nmax} points")
        self.log(f"  Config: xptr={xptr} yptr={yptr} zptr={zptr} zsize={zsize} nglas={nglas:.3f}")
        self.log(f"  l_period={self.cfg['l_period']} step_freq={self.cfg['step_freq']} "
                 f"dT={self.cfg['dT']} f_const={self.cfg['f_const']}")
        self.log(f"  refr_ofs={refr_ofs} z_base={z_base}")
        self.log(f"  Formula: {'2.61' if use_261_formula else '2.77'}")

        # Homing check
        self.log(f"  do_ptr={self.do_ptr} f_ptr={self.f_ptr}")
        if self.f_ptr or not self.do_ptr:
            self.log(f"  → HOMING (move_sen(0))")
            self.sim_move_sen(0)
        else:
            self.log(f"  → SKIP homing (do_ptr=1)")

        self.log(f"  Start position: phys=({self.phys_x},{self.phys_y},{self.phys_z}) "
                 f"sw=({self.xcur},{self.ycur},{self.zcur})")

        drift_x = drift_y = drift_z = 0
        max_k2 = {'x': 0, 'y': 0, 'z': 0}
        min_k2 = {'x': 999999, 'y': 999999, 'z': 999999}
        zero_delta_count = 0

        for i, (px, py, pz) in enumerate(points):
            xnew = 23500 - xptr - px
            ynew = yptr + py
            znew = z_base - pz

            dx = xnew - self.xcur
            dy = ynew - self.ycur
            dz = znew - self.zcur

            if use_261_formula:
                # 2.61 k2 calculation
                if dx:
                    k2x = self.calc_k2_261(dx)
                    if k2x > max_k2['x']: max_k2['x'] = k2x
                    if k2x < min_k2['x']: min_k2['x'] = k2x
                if dy:
                    k2y = self.calc_k2_261(dy)
                    if k2y > max_k2['y']: max_k2['y'] = k2y
                    if k2y < min_k2['y']: min_k2['y'] = k2y
                if dz:
                    k2z = self.calc_k2_261(dz)
                    if k2z > max_k2['z']: max_k2['z'] = k2z
                    if k2z < min_k2['z']: min_k2['z'] = k2z
            else:
                # 2.77 k2 calculation
                t_seg = self.seg_time_277(dx, dy, dz)
                if dx:
                    k2x = self.calc_k2_277(dx, t_seg)
                    if k2x > max_k2['x']: max_k2['x'] = k2x
                    if k2x < min_k2['y']: max_k2['x'] = k2x
                if dy:
                    k2y = self.calc_k2_277(dy, t_seg)
                if dz:
                    k2z = self.calc_k2_277(dz, t_seg)

            # Simulate the move
            self.sim_move_277(xnew, ynew, znew)

            # Check drift
            cur_drift_x = self.phys_x - self.xcur
            cur_drift_y = self.phys_y - self.ycur
            cur_drift_z = self.phys_z - self.zcur

            if dx == 0 and dy == 0 and dz == 0:
                zero_delta_count += 1

            # Log first few and last, plus any drift
            if i < 3 or i == nmax - 1 or cur_drift_x or cur_drift_y or cur_drift_z:
                self.log(f"  [{i}] target=({xnew},{ynew},{znew}) delta=({dx},{dy},{dz}) "
                         f"phys=({self.phys_x},{self.phys_y},{self.phys_z}) "
                         f"drift=({cur_drift_x},{cur_drift_y},{cur_drift_z})")

        self.log(f"\n  End state:")
        self.log(f"    phys=({self.phys_x},{self.phys_y},{self.phys_z})")
        self.log(f"    sw  =({self.xcur},{self.ycur},{self.zcur})")
        self.log(f"    drift=({self.phys_x-self.xcur},{self.phys_y-self.ycur},{self.phys_z-self.zcur})")
        self.log(f"    zero-delta moves: {zero_delta_count}")

        # TABLE END (as in binary, no do_ptr=0)
        self.log(f"\n  TABLE END: lastn=0")
        # Note: original binary does NOT reset do_ptr here!
        # do_ptr stays at 1


def load_bft(filename):
    """Load BFT file, return (config_dict, points_list)"""
    with open(filename, 'rb') as f:
        hdr = f.read(14)
        magic = struct.unpack('<H', hdr[0:2])[0]
        if magic != 0x6662:
            raise ValueError(f"Not a BFT file: magic=0x{magic:04x}")
        nglas_raw = struct.unpack('<H', hdr[2:4])[0]
        xsize = struct.unpack('<H', hdr[4:6])[0]
        ysize = struct.unpack('<H', hdr[6:8])[0]
        zsize = struct.unpack('<H', hdr[8:10])[0]
        nmax_hi = struct.unpack('<H', hdr[10:12])[0]
        nmax_lo = struct.unpack('<H', hdr[12:14])[0]
        nmax = nmax_hi * 65536 + nmax_lo

        pts = f.read(nmax * 6)
        points = []
        for i in range(nmax):
            x, y, z = struct.unpack_from('<hhh', pts, i * 6)
            points.append((x, y, z))

    bft_cfg = {
        'nglas': nglas_raw / 1000.0,
        'xsize': xsize,
        'ysize': ysize,
        'zsize': zsize,
    }
    return bft_cfg, points


def load_cfg(filename):
    """Load FLINT1.CFG text config."""
    with open(filename, 'rb') as f:
        data = f.read()
    lines = data.decode('ascii', errors='replace').strip().split('\n')
    fields = ['xptr', 'yptr', 'zptr', 'step', 'l_period', 'gate_delay',
              'step_freq', 'f_const', 'dT', 'sh_delay']
    cfg = {}
    for i, field in enumerate(fields):
        if i < len(lines):
            try:
                cfg[field] = int(lines[i].strip())
            except ValueError:
                cfg[field] = 0
    return cfg


def analyze_k2_differences(points, cfg):
    """Compare k2 values between 2.61 and 2.77 formulas for each move."""
    print("\n" + "=" * 70)
    print("K2 FORMULA COMPARISON: 2.61 vs 2.77")
    print("=" * 70)

    xptr, yptr, zptr = cfg['xptr'], cfg['yptr'], cfg['zptr']
    zsize = cfg['zsize']
    nglas = cfg['nglas']
    refr_ofs = int(zsize * 10 * (1 - 1/nglas))
    z_base = 11000 - zptr - refr_ofs
    l_period = cfg['l_period']
    step_freq = cfg['step_freq']
    dT = cfg['dT']
    f_const = cfg['f_const']
    k2min = 100000 // step_freq

    # Starting from homed position
    xcur, ycur, zcur = 23300, 200, 200

    big_diffs = []
    clamped_to_min = 0
    total = 0

    for i, (px, py, pz) in enumerate(points):
        xnew = 23500 - xptr - px
        ynew = yptr + py
        znew = z_base - pz

        dx = xnew - xcur
        dy = ynew - ycur
        dz = znew - zcur

        if dx == 0 and dy == 0 and dz == 0:
            xcur, ycur, zcur = xnew, ynew, znew
            continue

        total += 1

        # 2.61 formula
        k2_261 = {}
        for axis, d in [('x', dx), ('y', dy), ('z', dz)]:
            if d:
                k2 = (l_period - 3) * 100 // abs(d)
                if k2 < k2min: k2 = k2min
                if k2 > 65500: k2 = 65500
                k2_261[axis] = k2

        # 2.77 formula
        t_max = max(abs(dx), abs(dy))
        if t_max < abs(dz): t_max = abs(dz)
        ms = t_max * 1000 // step_freq
        t_seg = ms // l_period + 1
        if ms % l_period > l_period - dT:
            t_seg += 1

        k2_277 = {}
        for axis, d in [('x', dx), ('y', dy), ('z', dz)]:
            if d:
                k2 = (t_seg * l_period - dT) * 100 // abs(d)
                if k2 < k2min: k2 = k2min
                if k2 > 65500: k2 = 65500
                k2_277[axis] = k2
                if k2 == k2min:
                    clamped_to_min += 1

        # Check for significant differences
        for axis in k2_261:
            if axis in k2_277:
                diff = k2_277[axis] - k2_261[axis]
                ratio = k2_277[axis] / k2_261[axis] if k2_261[axis] else 0
                if abs(diff) > 50 or ratio > 2.0 or ratio < 0.5:
                    big_diffs.append({
                        'i': i, 'axis': axis,
                        'k2_261': k2_261[axis], 'k2_277': k2_277[axis],
                        'delta': d, 'dx': dx, 'dy': dy, 'dz': dz,
                        'diff': diff, 'ratio': ratio, 't_seg': t_seg
                    })

        # Print first few
        if i < 5:
            print(f"  [{i}] delta=({dx},{dy},{dz}) t_seg={t_seg}")
            for axis in ['x', 'y', 'z']:
                if axis in k2_261 and axis in k2_277:
                    print(f"    {axis}: k2_261={k2_261[axis]:6d}  k2_277={k2_277[axis]:6d}  "
                          f"diff={k2_277[axis]-k2_261[axis]:+6d}  "
                          f"ratio={k2_277[axis]/k2_261[axis]:.2f}x")

        xcur, ycur, zcur = xnew, ynew, znew

    print(f"\n  Total moves: {total}")
    print(f"  k2 clamped to min ({k2min}): {clamped_to_min} times")
    print(f"  Significant k2 diffs (>50 or ratio>2x): {len(big_diffs)}")
    if big_diffs:
        print(f"\n  Worst differences:")
        big_diffs.sort(key=lambda x: abs(x['diff']), reverse=True)
        for d in big_diffs[:10]:
            print(f"    [{d['i']}] axis={d['axis']} k2: {d['k2_261']}→{d['k2_277']} "
                  f"diff={d['diff']:+d} ratio={d['ratio']:.2f}x "
                  f"delta=({d['dx']},{d['dy']},{d['dz']}) tseg={d['t_seg']}")

    # CRITICAL: check if k2 < k2min would ever occur without clamping
    print(f"\n  k2min for step_freq={step_freq}: {k2min}")
    print(f"  Motor max speed: {1000000//k2min//10} Hz = {1000000//k2min//10} steps/sec")
    print(f"  Motor step period at k2min: {k2min*10} us = {k2min*10/1000:.1f} ms")


def analyze_counter_programming(points, cfg):
    """Check if 16-bit counter overflow could cause wrong step counts."""
    print("\n" + "=" * 70)
    print("COUNTER PROGRAMMING ANALYSIS")
    print("  Checking: do abs(delta) values fit in 16-bit unsigned?")
    print("  Checking: are programmed d values correct?")
    print("=" * 70)

    xptr, yptr, zptr = cfg['xptr'], cfg['yptr'], cfg['zptr']
    zsize = cfg['zsize']
    nglas = cfg['nglas']
    refr_ofs = int(zsize * 10 * (1 - 1/nglas))
    z_base = 11000 - zptr - refr_ofs

    xcur, ycur, zcur = 23300, 200, 200
    overflow_count = 0

    for i, (px, py, pz) in enumerate(points):
        xnew = 23500 - xptr - px
        ynew = yptr + py
        znew = z_base - pz

        dx = xnew - xcur
        dy = ynew - ycur
        dz = znew - zcur

        for axis, d in [('X', dx), ('Y', dy), ('Z', dz)]:
            if d:
                ad = abs(d)
                lo = ad % 256
                hi = ad // 256
                reconstructed = lo + hi * 256
                if reconstructed != ad or ad > 65535:
                    print(f"  [{i}] {axis}: delta={d} abs={ad} "
                          f"lo={lo} hi={hi} recon={reconstructed} *** OVERFLOW!")
                    overflow_count += 1

                # Also check what happens in 32-bit mode with (unsigned char) cast
                # In C: (unsigned char)(abs(dx) % 256) and (unsigned char)(abs(dx)/256)
                # If abs(dx) > 65535, then abs(dx)/256 > 255 → truncated to byte!
                if ad > 65535:
                    print(f"    32-bit overflow! abs(d)={ad} > 65535")
                    overflow_count += 1

        xcur, ycur, zcur = xnew, ynew, znew

    if overflow_count == 0:
        print(f"  No counter overflows detected.")
    else:
        print(f"\n  *** {overflow_count} OVERFLOW(S) DETECTED!")


def analyze_scenario_two_runs(points, cfg, formula='277'):
    """
    Simulate the exact problematic scenario:
    1. First F5: move_sen + process full table
    2. Second F5 (no F4): skip homing + process again

    Track physical vs software position throughout.
    """
    print("\n" + "=" * 70)
    print(f"SCENARIO: Two consecutive F5 runs (formula={formula})")
    print(f"  Variant B: No F4/PgUp between runs")
    print("=" * 70)

    sim = KPU_Simulator(cfg)

    # Run 1
    sim.sim_process(points, f"RUN 1 ({formula})", use_261_formula=(formula == '261'))

    # Record end state of Run 1
    end_phys = (sim.phys_x, sim.phys_y, sim.phys_z)
    end_sw = (sim.xcur, sim.ycur, sim.zcur)
    end_drift = (sim.phys_x - sim.xcur, sim.phys_y - sim.ycur, sim.phys_z - sim.zcur)

    print(f"\n  After Run 1:")
    print(f"    Physical: ({end_phys[0]}, {end_phys[1]}, {end_phys[2]})")
    print(f"    Software: ({end_sw[0]}, {end_sw[1]}, {end_sw[2]})")
    print(f"    Drift:    ({end_drift[0]}, {end_drift[1]}, {end_drift[2]})")
    print(f"    do_ptr={sim.do_ptr}")

    # Run 2 - no homing
    sim.f_ptr = 0  # no file change
    sim.sim_process(points, f"RUN 2 ({formula})", use_261_formula=(formula == '261'))

    end2_phys = (sim.phys_x, sim.phys_y, sim.phys_z)
    end2_sw = (sim.xcur, sim.ycur, sim.zcur)
    end2_drift = (sim.phys_x - sim.xcur, sim.phys_y - sim.ycur, sim.phys_z - sim.zcur)

    print(f"\n  After Run 2:")
    print(f"    Physical: ({end2_phys[0]}, {end2_phys[1]}, {end2_phys[2]})")
    print(f"    Software: ({end2_sw[0]}, {end2_sw[1]}, {end2_sw[2]})")
    print(f"    Drift:    ({end2_drift[0]}, {end2_drift[1]}, {end2_drift[2]})")

    # Print full log
    print("\n  --- Detailed log ---")
    for line in sim.log_lines[-30:]:
        print(f"  {line}")


def analyze_move_timing(points, cfg):
    """
    Analyze physical timing of moves.
    The KEY question: does the hardware actually complete all d steps
    before the software considers the move done?

    The software waits for optical sensors (bit 7 XY, bit 6 Z).
    In the counter hardware, the optical sensor signals when d steps complete.

    But what if: the software reads the sensor TOO EARLY or TOO LATE?
    What if polling is too fast and misses the completion pulse?
    """
    print("\n" + "=" * 70)
    print("TIMING ANALYSIS: Counter completion vs sensor polling")
    print("=" * 70)

    l_period = cfg['l_period']
    step_freq = cfg['step_freq']
    dT = cfg['dT']

    xptr, yptr, zptr = cfg['xptr'], cfg['yptr'], cfg['zptr']
    zsize = cfg['zsize']
    nglas = cfg['nglas']
    refr_ofs = int(zsize * 10 * (1 - 1/nglas))
    z_base = 11000 - zptr - refr_ofs

    xcur, ycur, zcur = 23300, 200, 200

    # For each move, compute the actual time each axis takes
    time_mismatches = []

    for i, (px, py, pz) in enumerate(points):
        xnew = 23500 - xptr - px
        ynew = yptr + py
        znew = z_base - pz

        dx = xnew - xcur
        dy = ynew - ycur
        dz = znew - zcur

        if dx == 0 and dy == 0 and dz == 0:
            xcur, ycur, zcur = xnew, ynew, znew
            continue

        # 2.77 formula
        t_max = max(abs(dx), abs(dy))
        if t_max < abs(dz): t_max = abs(dz)
        ms_max = t_max * 1000 // step_freq
        t_seg = ms_max // l_period + 1
        if ms_max % l_period > l_period - dT:
            t_seg += 1

        k2min = 100000 // step_freq

        # Time each axis takes: d * k2 * 10us
        axis_times = {}
        for axis, d in [('x', dx), ('y', dy), ('z', dz)]:
            if d:
                if not cfg['f_const']:
                    k2 = (t_seg * l_period - dT) * 100 // abs(d)
                    if k2 < k2min: k2 = k2min
                    if k2 > 65500: k2 = 65500
                else:
                    k2 = k2min
                time_us = abs(d) * k2 * 10
                time_ms = time_us / 1000
                axis_times[axis] = {'d': abs(d), 'k2': k2, 'time_us': time_us, 'time_ms': time_ms}

        # The XY optical sensor triggers when BOTH X and Y are done
        # The Z optical sensor triggers when Z is done
        # The software waits for both: while(!fxy || !fz)

        xy_time = max(axis_times.get('x', {}).get('time_ms', 0),
                      axis_times.get('y', {}).get('time_ms', 0))
        z_time = axis_times.get('z', {}).get('time_ms', 0)

        # In the 2.61 formula, each axis takes roughly l_period - 3 ms
        # In the 2.77 formula, all axes are supposed to finish in t_seg * l_period ms

        target_time = t_seg * l_period  # total time in ms

        if i < 5 or (i < 20 and xy_time != z_time):
            print(f"  [{i}] delta=({dx},{dy},{dz}) tseg={t_seg} target={target_time}ms")
            for axis in ['x', 'y', 'z']:
                if axis in axis_times:
                    at = axis_times[axis]
                    print(f"    {axis}: d={at['d']} k2={at['k2']} time={at['time_ms']:.1f}ms")
            print(f"    XY completes at {xy_time:.1f}ms, Z at {z_time:.1f}ms")

        xcur, ycur, zcur = xnew, ynew, znew


def main():
    base = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    # Load config
    cfg_path = os.path.join(base, 'Flint 2.77 src', 'BUILD', 'FLINT1.CFG')
    cfg = load_cfg(cfg_path)
    print(f"Config: {cfg}")

    # Load BFT
    bft_path = os.path.join(base, 'Flint 2.77 src', 'BUILD', 'BFT_FILES', 'cube.bft')
    bft_cfg, points = load_bft(bft_path)
    cfg.update(bft_cfg)  # merge BFT header values
    print(f"BFT: {len(points)} points, nglas={cfg['nglas']:.3f}, zsize={cfg['zsize']}")

    # Analysis 1: K2 formula comparison
    analyze_k2_differences(points, cfg)

    # Analysis 2: Counter overflow check
    analyze_counter_programming(points, cfg)

    # Analysis 3: Move timing
    analyze_move_timing(points, cfg)

    # Analysis 4: Two-run scenario (2.77 and 2.61)
    analyze_scenario_two_runs(points, cfg, '277')

    print("\n\nDone.")


if __name__ == '__main__':
    main()
