#!/usr/bin/env python3
"""
analyze_trace.py — FLINT.LOG trace analyzer for continuation debugging.

Parses FLINT.LOG produced by the TRACE-enabled FLINT build and:
  1) Extracts all [DLGSTART], [START], [PROC], [PT], [MOV] entries
  2) Identifies runs (first run vs continuation)
  3) Checks for position discrepancies between the last point of a run
     and the starting position of the next run (continuation)
  4) Highlights any unexpected move_sen() calls during continuation
  5) Flags any move errors or sensor issues

Usage:
  python analyze_trace.py [FLINT.LOG path]

  Default path: ../Flint 2.77 src/BUILD/FLINT.LOG
"""

import sys
import os
import re


def parse_kv(text):
    """Parse key=value pairs from a trace line."""
    result = {}
    for m in re.finditer(r'(\w+)=([\-\d.]+)', text):
        key = m.group(1)
        val = m.group(2)
        try:
            if '.' in val:
                result[key] = float(val)
            else:
                result[key] = int(val)
        except ValueError:
            result[key] = val
    return result


class Run:
    """Represents a single process() execution."""
    def __init__(self, run_id):
        self.run_id = run_id
        self.start_state = {}    # from [START] PRE-PROC
        self.cfg_state = {}      # from [START] header
        self.proc_start = {}     # from [PROC] START
        self.proc_cfg = {}       # from [PROC] CFG
        self.proc_calc = {}      # from [PROC] CALC
        self.proc_resume = {}    # from [PROC] RESUME
        self.end_state = {}      # from [START] POST-PROC
        self.points = []         # list of [PT] entries
        self.move_sen_called = False
        self.had_error = False
        self.esc_point = None
        self.final_k = None
        
    def summary(self):
        s = f"\n{'='*60}\n"
        s += f"RUN #{self.run_id}\n"
        s += f"{'='*60}\n"
        
        if self.cfg_state:
            s += f"  Config: st={self.cfg_state.get('st','?')} fstart={self.cfg_state.get('fstart','?')} metal={self.cfg_state.get('metal','?')}\n"
        
        if self.start_state:
            s += f"  Before process():\n"
            s += f"    xcur={self.start_state.get('xcur','?')} ycur={self.start_state.get('ycur','?')} zcur={self.start_state.get('zcur','?')}\n"
            s += f"    doptr={self.start_state.get('doptr','?')} fptr={self.start_state.get('fptr','?')}\n"
        
        if self.proc_resume:
            s += f"  After move_sen check:\n"
            s += f"    xcur={self.proc_resume.get('xcur','?')} ycur={self.proc_resume.get('ycur','?')} zcur={self.proc_resume.get('zcur','?')}\n"
            s += f"    doptr={self.proc_resume.get('doptr','?')} fptr={self.proc_resume.get('fptr','?')} start={self.proc_resume.get('st','?')}\n"
            s += f"    move_sen called: {'YES' if self.move_sen_called else 'NO'}\n"
        
        if self.points:
            s += f"  Points processed: {len(self.points)} ({self.points[0]['i']}..{self.points[-1]['i']})\n"
            # First and last point
            p0 = self.points[0]
            pN = self.points[-1]
            s += f"    First: pt[{p0['i']}] xyz=({p0.get('xyz_x','?')},{p0.get('xyz_y','?')},{p0.get('xyz_z','?')}) d=({p0.get('d_x','?')},{p0.get('d_y','?')},{p0.get('d_z','?')})\n"
            s += f"    Last:  pt[{pN['i']}] xyz=({pN.get('xyz_x','?')},{pN.get('xyz_y','?')},{pN.get('xyz_z','?')}) d=({pN.get('d_x','?')},{pN.get('d_y','?')},{pN.get('d_z','?')})\n"
        
        if self.end_state:
            s += f"  After process():\n"
            s += f"    k={self.end_state.get('k','?')} lastn={self.end_state.get('lastn','?')}\n"
            s += f"    xcur={self.end_state.get('xcur','?')} ycur={self.end_state.get('ycur','?')} zcur={self.end_state.get('zcur','?')}\n"
            s += f"    doptr={self.end_state.get('doptr','?')}\n"
        
        if self.had_error:
            s += f"  ** ERRORS during this run **\n"
        if self.esc_point is not None:
            s += f"  ESC at point {self.esc_point}\n"
        
        return s


def parse_pt_line(kv_text):
    """Parse a [PT] line: i=N raw=X,Y,Z xyz=X,Y,Z d=X,Y,Z"""
    result = {}
    m = re.search(r'i=(\d+)', kv_text)
    if m: result['i'] = int(m.group(1))
    
    m = re.search(r'raw=([\-\d]+),([\-\d]+),([\-\d]+)', kv_text)
    if m:
        result['raw_x'] = int(m.group(1))
        result['raw_y'] = int(m.group(2))
        result['raw_z'] = int(m.group(3))
    
    m = re.search(r'xyz=([\-\d]+),([\-\d]+),([\-\d]+)', kv_text)
    if m:
        result['xyz_x'] = int(m.group(1))
        result['xyz_y'] = int(m.group(2))
        result['xyz_z'] = int(m.group(3))
    
    m = re.search(r'd=([\-\d]+),([\-\d]+),([\-\d]+)', kv_text)
    if m:
        result['d_x'] = int(m.group(1))
        result['d_y'] = int(m.group(2))
        result['d_z'] = int(m.group(3))
    
    return result


def analyze(log_path):
    """Main analysis of FLINT.LOG."""
    if not os.path.exists(log_path):
        print(f"ERROR: Log file not found: {log_path}")
        return
    
    with open(log_path, 'r', errors='replace') as f:
        lines = f.readlines()
    
    print(f"Loaded {len(lines)} lines from {log_path}")
    
    runs = []
    current_run = None
    run_id = 0
    
    for line_no, line in enumerate(lines, 1):
        line = line.rstrip()
        
        # New dlgstart entry
        if '[DLGSTART] ENTER' in line:
            kv = parse_kv(line)
            print(f"  Line {line_no}: dlgstart entered — "
                  f"lastn={kv.get('lastn','?')} xcur={kv.get('xcur','?')} "
                  f"ycur={kv.get('ycur','?')} zcur={kv.get('zcur','?')} "
                  f"doptr={kv.get('doptr','?')} fptr={kv.get('fptr','?')}")
        
        # [START] line — beginning of a process() call
        if '[START] st=' in line and 'fstart=' in line:
            run_id += 1
            current_run = Run(run_id)
            current_run.cfg_state = parse_kv(line)
            runs.append(current_run)
        
        # [START] PRE-PROC — state just before process()
        if '[START] PRE-PROC' in line and current_run:
            current_run.start_state = parse_kv(line)
        
        # [START] POST-PROC — state just after process()
        if '[START] POST-PROC' in line and current_run:
            current_run.end_state = parse_kv(line)

        # [PROC] START — inside process(), at top
        if '[PROC] START' in line and current_run:
            current_run.proc_start = parse_kv(line)
        
        # [PROC] CFG — config values
        if '[PROC] CFG' in line and current_run:
            current_run.proc_cfg = parse_kv(line)
        
        # [PROC] CALC — refraction computation
        if '[PROC] CALC' in line and current_run:
            current_run.proc_calc = parse_kv(line)
        
        # [PROC] RESUME — after move_sen check
        if '[PROC] RESUME' in line and current_run:
            current_run.proc_resume = parse_kv(line)
            # Check if move_sen was called by comparing xcur before/after
            if current_run.start_state:
                pre = current_run.start_state
                post = current_run.proc_resume
                if (pre.get('xcur') != post.get('xcur') or 
                    pre.get('ycur') != post.get('ycur') or
                    pre.get('zcur') != post.get('zcur')):
                    current_run.move_sen_called = True
        
        # [PT] — point processed
        if '[PT] i=' in line and current_run:
            pt = parse_pt_line(line)
            current_run.points.append(pt)
        
        # [PROC] MOVE ERR
        if '[PROC] MOVE ERR' in line and current_run:
            current_run.had_error = True
        
        # [PROC] LPULS FAIL / METAL FAIL
        if ('LPULS FAIL' in line or 'METAL FAIL' in line) and current_run:
            current_run.had_error = True
        
        # [PROC] ESC
        if '[PROC] ESC' in line and current_run:
            kv = parse_kv(line)
            current_run.esc_point = kv.get('pt', None)
        
        # [PROC] END
        if '[PROC] END' in line and current_run:
            pass  # normal completion
        
        # [MOVE] ERR (from move() sensor error)
        if '[MOVE] ERR' in line and current_run:
            current_run.had_error = True
    
    # Print run summaries
    print(f"\n{'#'*60}")
    print(f"  Found {len(runs)} process() runs")
    print(f"{'#'*60}")
    
    for run in runs:
        print(run.summary())
    
    # Cross-run analysis: check continuation integrity
    if len(runs) >= 2:
        print(f"\n{'#'*60}")
        print("  CONTINUATION ANALYSIS")
        print(f"{'#'*60}\n")
        
        for i in range(1, len(runs)):
            prev = runs[i - 1]
            curr = runs[i]
            
            print(f"--- Run #{prev.run_id} → Run #{curr.run_id} ---")
            
            # Check: position continuity
            if prev.end_state and curr.start_state:
                prev_x = prev.end_state.get('xcur')
                prev_y = prev.end_state.get('ycur')
                prev_z = prev.end_state.get('zcur')
                curr_x = curr.start_state.get('xcur')
                curr_y = curr.start_state.get('ycur')
                curr_z = curr.start_state.get('zcur')
                
                if prev_x == curr_x and prev_y == curr_y and prev_z == curr_z:
                    print(f"  Position PRESERVED: ({curr_x}, {curr_y}, {curr_z}) ✓")
                else:
                    print(f"  *** POSITION CHANGED ***")
                    print(f"    After run #{prev.run_id}: ({prev_x}, {prev_y}, {prev_z})")
                    print(f"    Before run #{curr.run_id}: ({curr_x}, {curr_y}, {curr_z})")
                    dx = (curr_x or 0) - (prev_x or 0)
                    dy = (curr_y or 0) - (prev_y or 0)
                    dz = (curr_z or 0) - (prev_z or 0)
                    print(f"    Delta: ({dx}, {dy}, {dz})")
                    print(f"    !!! THIS IS THE BUG — something modified position between runs !!!")
            
            # Check: move_sen during continuation
            if curr.cfg_state.get('fstart') == 2:
                if curr.move_sen_called:
                    print(f"  *** move_sen() CALLED during continuation (fstart=2)! ***")
                    print(f"    This would reset to home position — likely the cause of Z shift!")
                    print(f"    Check: doptr={curr.start_state.get('doptr','?')} fptr={curr.start_state.get('fptr','?')}")
                else:
                    print(f"  move_sen() correctly SKIPPED for continuation ✓")
            
            # Check: point index continuity
            if prev.points and curr.points:
                last_pt = prev.points[-1]['i']
                first_pt = curr.points[0]['i']
                expected = last_pt + 1
                if first_pt == expected:
                    print(f"  Point index continuous: {last_pt} → {first_pt} ✓")
                else:
                    print(f"  *** Point index GAP: {last_pt} → {first_pt} (expected {expected}) ***")
            
            # Check: is the first continuation point's position correct?
            if curr.points and prev.points:
                # The first point of continuation should have the same xyz as if 
                # we computed it fresh from iTabl (the absolute position is determined
                # by xptr/yptr/zptr and iTabl[3*i] only)
                # The delta d should be from the last point of prev run to this point
                p = curr.points[0]
                d_x = p.get('d_x', 0)
                d_y = p.get('d_y', 0)
                d_z = p.get('d_z', 0)
                print(f"  First continuation point delta: ({d_x}, {d_y}, {d_z})")
                if d_z != 0:
                    print(f"    NOTE: Z delta is non-zero ({d_z}) — check if this matches expected")
            
            print()


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    base_dir = os.path.dirname(script_dir)
    
    default_log = os.path.join(base_dir, "Flint 2.77 src", "BUILD", "FLINT.LOG")
    log_path = sys.argv[1] if len(sys.argv) > 1 else default_log
    
    # Try alternate locations
    if not os.path.exists(log_path):
        alternates = [
            os.path.join(base_dir, "Flint 2.77 (32bit) src", "BUILD", "FLINT.LOG"),
            os.path.join(base_dir, "!GENESIS", "Flint 2.77", "FLINT.LOG"),
        ]
        for alt in alternates:
            if os.path.exists(alt):
                print(f"Note: Using alternate log path: {alt}")
                log_path = alt
                break
    
    analyze(log_path)


if __name__ == "__main__":
    main()
