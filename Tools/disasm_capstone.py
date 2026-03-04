"""
Disassemble dlgstart() case handlers from PROJ5.EXE using Capstone.
Ghidra couldn't recover the jump table — we do it manually.
"""
import struct
import os
from capstone import *

EXE_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)),
    "..", "!GENESIS", "Flint 2.77", "PROJ5.EXE")

def read_mz_header(data):
    fields = struct.unpack_from('<HHHHHHHHHHHHHHH', data, 0)
    return {
        'header_size': fields[4] * 16,
        'e_cs': fields[11],
        'e_ip': fields[10],
    }

# Ghidra load base = 0x1000 segments
# Real file segment for 1928 = 0x0928
GHIDRA_SEG = 0x1928
FILE_SEG   = 0x0928

def file_off(hdr, offset):
    return hdr['header_size'] + FILE_SEG * 16 + offset

# Known global variable names from PROJ5.H / Ghidra annotations
# We'll annotate addresses we recognize
KNOWN_GLOBALS = {}

def disasm_block(md, data, hdr, start_off, length, label=""):
    """Disassemble a block of code at the given offset within segment 1928."""
    foff = file_off(hdr, start_off)
    code_bytes = data[foff:foff+length]
    
    if label:
        print(f"\n{'='*70}")
        print(f"  {label}")
        print(f"{'='*70}")
    
    for instr in md.disasm(code_bytes, start_off):
        addr_str = f"{GHIDRA_SEG:04X}:{instr.address:04X}"
        hex_str = instr.bytes.hex(' ')
        line = f"  {addr_str}  {hex_str:<24s}  {instr.mnemonic:<8s} {instr.op_str}"
        print(line)

def main():
    with open(os.path.abspath(EXE_PATH), 'rb') as f:
        data = f.read()
    
    hdr = read_mz_header(data)
    
    # Read jump table at 1928:4359
    table_off = file_off(hdr, 0x4359)
    
    case_vals = []
    jump_targets = []
    for j in range(15):
        cv = struct.unpack_from('<h', data, table_off + j*2)[0]
        case_vals.append(cv)
    for j in range(15):
        jt = struct.unpack_from('<H', data, table_off + 30 + j*2)[0]
        jump_targets.append(jt)
    
    case_names = {
        0: 'Ok', 1: 'Cancel', 2: '+', 3: '-',
        4: 'Beginning', 5: 'PointNumber', 6: 'Continuation', 7: 'CMOS',
        8: 'EndSens', 9: 'DrCheck', 10: 'Stop', 11: 'Reboot',
        12: 'Ignore', 13: 'InputArea', 255: 'KeyHandler'
    }
    
    print("=== Jump Table at 1928:4359 ===\n")
    print(f"  {'Case':>6s}  {'Name':<14s}  {'Target':>10s}")
    print(f"  {'-----':>6s}  {'----':<14s}  {'------':>10s}")
    for cv, jt in zip(case_vals, jump_targets):
        name = case_names.get(cv, '???')
        print(f"  {cv:>6d}  {name:<14s}  {GHIDRA_SEG:04X}:{jt:04X}")
    
    # Initialize Capstone for 16-bit x86
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    
    # Build target map
    target_to_cases = {}
    for cv, jt in zip(case_vals, jump_targets):
        target_to_cases.setdefault(jt, []).append(cv)
    
    unique_targets = sorted(set(jump_targets))
    end_boundary = 0x4395  # ClearRpt
    
    # Disassemble each case handler
    for i, target in enumerate(unique_targets):
        if i + 1 < len(unique_targets):
            next_target = unique_targets[i + 1]
        else:
            next_target = end_boundary
        
        length = min(next_target - target, 1024)
        if length <= 0:
            continue
        
        cases = target_to_cases.get(target, [])
        case_str = ', '.join(f"{c} ({case_names.get(c,'?')})" for c in cases)
        
        disasm_block(md, data, hdr, target, length,
                     f"Case {case_str}  [{GHIDRA_SEG:04X}:{target:04X}-{GHIDRA_SEG:04X}:{target+length-1:04X}]")
    
    # Also disassemble the dispatch loop and prologue
    # dlgstart begins at 3F0E, case 0 handler at 40DB
    # Let's disassemble from 3F0E to just before case 0
    dlg_start = 0x3F0E
    dlg_len = unique_targets[0] - dlg_start
    disasm_block(md, data, hdr, dlg_start, dlg_len,
                 f"dlgstart() prologue + dispatch loop [{GHIDRA_SEG:04X}:{dlg_start:04X}]")

if __name__ == '__main__':
    main()
