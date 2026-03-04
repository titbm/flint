# Debugging Guide: Continuation Z-Axis Shift

## Problem Summary

Both 16-bit and 32-bit reconstructions show a position shift (especially Z-axis)
when using "Continuation" mode. The original binary (`!GENESIS/Flint 2.77/PROJ5.EXE`)
does not have this issue.

## Analysis Results

### Mathematical Simulation (CONCLUSIVE)

`Tools/simulate_continuation.py` proves that the **process() formula and continuation
logic are mathematically correct**. Tested with all available BFT files (cube, sphere,
spiral): positions are identical whether run continuously or with interruption + continuation.

```
python Tools/simulate_continuation.py --verbose --break 50 --points 10
python Tools/simulate_continuation.py --bft "path/to/file.bft" --break N --points M
```

### Code Comparison (COMPLETE)

All PIC.CPP functions (process, move, move_sen, seg_time, calc_k2, lpuls, etc.)
have been verified instruction-by-instruction against the original binary disassembly.
**Every function matches** except the v2.78 additions.

### v2.78 Differences (ONLY KNOWN CODE DIFFERENCES)

The reconstruction has three v2.78 additions not present in the original binary:

1. **Laser check in dlgstart() Ok handler** (COMMENTED OUT):
   ```cpp
   if(!f_metal && !LCtl) { msgbox1("Laser is not enabled."); goto b; }
   ```
   This check **blocks** the start if the laser pump is not enabled.
   In the original binary, there is NO such check — Ok goes directly to minmax().
   **Status: COMMENTED OUT in both versions** (matching binary behavior).

2. **f_metal branch in process()** — dead code when f_metal=0 (default).

3. **lpuls_metal() function** — never called when f_metal=0.

---

## Debugging Procedure

### Step 1: Test without v2.78 laser check

The laser check has been commented out in both versions. **Recompile and test continuation.**

If the problem **disappears**: the issue was the laser check forcing a different workflow
(requiring LCtl to be enabled, which may affect hardware behavior).

If the problem **persists**: the issue is NOT the laser check. Proceed to Step 2.

### Step 2: Capture TRACE log

Both versions have comprehensive TRACE logging enabled (`#define TRACE` in PIC.CPP and PROJ5.CPP).

1. Compile the reconstruction (16-bit or 32-bit)
2. Run in DOSBox with a small BFT file (e.g., cube.bft, 1000 points)
3. Start from Beginning, process ~20 points
4. Press ESC to stop
5. Start Continuation, process ~10 more points
6. Press ESC again (or let it finish)
7. Exit the program

The trace log is written to `FLINT.LOG` in the working directory.

### Step 3: Analyze the trace

```
python Tools/analyze_trace.py path/to/FLINT.LOG
```

The analyzer will:
- Identify each process() run
- Show xcur/ycur/zcur state BEFORE and AFTER each run
- Check position continuity between runs
- Flag unexpected move_sen() calls during continuation
- Detect point index gaps

**What to look for:**
- `*** POSITION CHANGED ***` — something modified xcur/ycur/zcur between runs
- `*** move_sen() CALLED during continuation ***` — move_sen should NOT run on continuation
- `*** Point index GAP ***` — start_nmb doesn't match expected

### Step 4: Compare with original binary

Run the SAME test procedure with the original binary and compare:
- Does the original binary also write FLINT.LOG? (No — it doesn't have TRACE)
- Compare the visual result on screen: does the original binary show different
  pixel positions than the reconstruction?

---

## TRACE Log Format

The following entries are logged:

| Tag | Logged when | Key fields |
|-----|-------------|------------|
| `[DLGSTART] ENTER` | dlgstart() called | lastn, xcur/ycur/zcur, doptr, fptr, demo |
| `[START] st=..` | Before process() call | start_nmb, fstart, metal, dchk, LCtl, gate |
| `[START] PRE-PROC` | Just before process() | xcur/ycur/zcur, doptr, fptr |
| `[PROC] START` | process() entry | start_nmb/nmax, metal, timing params |
| `[PROC] CFG` | process() entry | xptr/yptr/zptr, zsize, nglas, config |
| `[PROC] CALC` | process() entry | refr_ofs, z_base (computed constants) |
| `[PROC] RESUME` | After move_sen check | xcur/ycur/zcur, doptr, fptr, start_nmb |
| `[PT] i=..` | Each point | point index, raw data, computed xyz, delta |
| `[MOV] dx=..` | Each move() call | deltas, seg_time, k2 values |
| `[PROC] ESC` | ESC pressed | point index, flash count |
| `[START] POST-PROC` | After process() returns | k, lastn, xcur/ycur/zcur, doptr |

**Critical sequence for continuation:**
```
[DLGSTART] ENTER   → shows xcur/ycur/zcur from PREVIOUS run
[START] PRE-PROC   → must match POST-PROC of previous run
[PROC] RESUME      → if move_sen was called, xcur=23300,ycur=200,zcur=200
                     if skipped, xcur/ycur/zcur = same as PRE-PROC
[PT] i=N           → first point delta shows movement from current to N
```

---

## Files Modified

| File | Change |
|------|--------|
| `Flint 2.77 src/PROJ5.CPP` | Added TRACE at dlgstart entry/exit; commented out laser check |
| `Flint 2.77 (32bit) src/PROJ5.CPP` | Same changes |
| `Flint 2.77 (32bit) src/PIC.CPP` | Added missing [PROC] RESUME trace point |
| `Tools/simulate_continuation.py` | NEW: Python simulation of process() |
| `Tools/analyze_trace.py` | NEW: FLINT.LOG trace analyzer |

---

## Hypotheses

If the simulation shows correct math AND the trace shows correct state transitions,
the remaining possibilities are:

1. **Hardware timing**: move() hardware polling completes before motors finish
   (only relevant on real hardware, not in f_demo mode)
2. **DOSBox port behavior**: I/O ports return unexpected values that trigger
   sensor error paths in move()
3. **f_demo mode difference**: the original binary may handle f_demo differently
4. **Display-only issue**: draw() shows raw iTabl coordinates, not actual
   motor positions — the visual shift might not reflect actual position error
