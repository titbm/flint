"""
Disassemble PROJ5.EXE (16-bit DOS, Borland C++ 4.5, Large model)
to find and analyze the lpuls() function.

Strategy:
1. Parse MZ EXE header to find code start
2. Search for characteristic byte patterns (port I/O to 0x310 = ADRPPI2)
3. Disassemble candidate regions
4. Also search for string references to find function boundaries
"""

import sys
import struct
from capstone import *

EXE_PATH = r"..\!GENESIS\Flint 2.77\PROJ5.EXE"

def read_exe(path):
    with open(path, "rb") as f:
        return f.read()

def parse_mz_header(data):
    """Parse MZ EXE header"""
    if data[:2] != b'MZ':
        print("Not an MZ EXE!")
        return None
    
    header = struct.unpack_from('<HHHHHHHHHHHHHH', data, 0)
    last_page_bytes = header[1]
    num_pages = header[2]
    header_size_para = header[4]  # in 16-byte paragraphs
    min_alloc = header[5]
    max_alloc = header[6]
    init_ss = header[7]
    init_sp = header[8]
    init_ip = header[10]
    init_cs = header[11]
    
    code_start = header_size_para * 16
    
    print(f"MZ Header:")
    print(f"  Pages: {num_pages}, Last page bytes: {last_page_bytes}")
    print(f"  Header size: {header_size_para} paragraphs ({code_start} bytes)")
    print(f"  Init CS:IP = {init_cs:04X}:{init_ip:04X}")
    print(f"  Init SS:SP = {init_ss:04X}:{init_sp:04X}")
    print(f"  Code start offset in file: 0x{code_start:X}")
    
    # Total file size from header
    if last_page_bytes:
        total = (num_pages - 1) * 512 + last_page_bytes
    else:
        total = num_pages * 512
    print(f"  Declared size: {total} bytes, Actual: {len(data)} bytes")
    
    return code_start

def find_port_patterns(data, code_start):
    """
    Search for IN/OUT instructions to ports related to PPI2 (0x310).
    In 16-bit code:
      - in al, dx  = 0xEC
      - out dx, al = 0xEE
      - mov dx, 0x310 = 0xBA 0x10 0x03
      - mov dx, 0x312 = 0xBA 0x12 0x03 (ADRPPI2+2)
      - mov dx, 0x313 = 0xBA 0x13 0x03 (ADRPPI2+3)
      - mov dx, 0x314 = 0xBA 0x14 0x03 (ADRPT2)
    
    Also look for the loop counter pattern (cmp with 10 or 11)
    """
    
    results = []
    
    # Search for mov dx, 0x0310 (BA 10 03)
    pattern_ppi2 = b'\xba\x10\x03'
    pattern_ppi2_2 = b'\xba\x12\x03'  # ADRPPI2+2
    pattern_ppi2_3 = b'\xba\x13\x03'  # ADRPPI2+3
    pattern_pt2 = b'\xba\x14\x03'     # ADRPT2
    pattern_ppi = b'\xba\x08\x03'     # ADRPPI
    pattern_ppi_2 = b'\xba\x0a\x03'   # ADRPPI+2
    
    patterns = {
        'ADRPPI2 (0x310)': pattern_ppi2,
        'ADRPPI2+2 (0x312)': pattern_ppi2_2,
        'ADRPPI2+3 (0x313)': pattern_ppi2_3,
        'ADRPT2 (0x314)': pattern_pt2,
        'ADRPPI (0x308)': pattern_ppi,
        'ADRPPI+2 (0x30A)': pattern_ppi_2,
    }
    
    print("\n=== Port access patterns found ===")
    for name, pattern in patterns.items():
        offset = code_start
        found = []
        while True:
            pos = data.find(pattern, offset)
            if pos == -1:
                break
            found.append(pos)
            offset = pos + 1
        if found:
            print(f"  {name}: {len(found)} occurrences at offsets: {[f'0x{x:X}' for x in found[:20]]}")
            results.extend([(pos, name) for pos in found])
    
    return results

def find_function_boundaries(data, code_start):
    """
    Borland C++ large model functions typically start with:
      push bp       (55)
      mov bp, sp    (89 E5 or 8B EC)
    And end with:
      pop bp        (5D)
      retf          (CB) or ret (C3) or retf N (CA xx xx)
    
    For large model, far returns (CB/CA) are used.
    """
    
    # Common prologue: 55 8B EC (push bp; mov bp,sp - Intel syntax)
    # or 55 89 E5 (AT&T convention, same thing)
    prologue1 = b'\x55\x8b\xec'
    prologue2 = b'\x55\x89\xe5'
    
    prologues = []
    for pat in [prologue1, prologue2]:
        offset = code_start
        while True:
            pos = data.find(pat, offset)
            if pos == -1 or pos >= len(data):
                break
            prologues.append(pos)
            offset = pos + 1
    
    prologues.sort()
    print(f"\n=== Found {len(prologues)} function prologues ===")
    return prologues

def disassemble_region(data, start, length, base_addr=0):
    """Disassemble a region of 16-bit x86 code"""
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    
    code = data[start:start+length]
    lines = []
    for insn in md.disasm(code, base_addr):
        line = f"  {insn.address:08X}  {insn.bytes.hex():16s}  {insn.mnemonic:8s} {insn.op_str}"
        lines.append(line)
    return lines

def find_lpuls_candidates(data, code_start, prologues, port_refs):
    """
    Find functions that contain references to ADRPPI2 (0x310) 
    and ADRPPI2+2 (0x312) - these are the sensor reading ports.
    lpuls() reads sensors: inportb(ADRPPI2) and inportb(ADRPPI2+2)
    """
    
    # Get offsets of PPI2 and PPI2+2 references
    ppi2_offsets = set()
    for pos, name in port_refs:
        if '0x310' in name or '0x312' in name:
            ppi2_offsets.add(pos)
    
    if not ppi2_offsets:
        print("No PPI2 references found!")
        return []
    
    # For each function (prologue), check if it contains PPI2 references
    candidates = []
    for idx, func_start in enumerate(prologues):
        # Estimate function end as next prologue or +2000 bytes
        if idx + 1 < len(prologues):
            func_end = prologues[idx + 1]
        else:
            func_end = func_start + 2000
        func_end = min(func_end, len(data))
        
        # Check if any PPI2 reference falls within this function
        refs_in_func = [p for p in ppi2_offsets if func_start <= p < func_end]
        if len(refs_in_func) >= 2:  # lpuls reads both ADRPPI2 and ADRPPI2+2
            candidates.append((func_start, func_end, refs_in_func))
    
    print(f"\n=== Functions with PPI2 sensor reads (>=2 refs): {len(candidates)} ===")
    for start, end, refs in candidates:
        print(f"  Offset 0x{start:X}-0x{end:X} ({end-start} bytes), PPI2 refs: {[f'0x{r:X}' for r in refs]}")
    
    return candidates

def analyze_lpuls_candidate(data, func_start, func_end):
    """
    Disassemble and analyze a candidate lpuls() function.
    Look for:
    - Loop counter comparison (cmp reg, 10 or 11)
    - Port I/O sequences
    - sh_open calls
    - delay calls
    """
    length = min(func_end - func_start, 3000)
    
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    
    code = data[func_start:func_start+length]
    
    instructions = []
    for insn in md.disasm(code, func_start):
        instructions.append(insn)
    
    print(f"\n{'='*70}")
    print(f"Disassembly at file offset 0x{func_start:X} ({len(instructions)} instructions):")
    print(f"{'='*70}")
    
    # Print full disassembly with annotations
    for insn in instructions:
        annotation = ""
        op = insn.op_str
        mn = insn.mnemonic
        
        # Annotate interesting instructions
        if 'dx' in op and ('0x310' in op or '0x312' in op or '0x313' in op or '0x314' in op or '0x308' in op or '0x30a' in op):
            port_names = {
                '0x310': 'ADRPPI2', '0x312': 'ADRPPI2+2', '0x313': 'ADRPPI2+3',
                '0x314': 'ADRPT2', '0x308': 'ADRPPI', '0x30a': 'ADRPPI+2',
                '0x311': 'ADRPPI2+1', '0x315': 'ADRPT2+1', '0x317': 'ADRPT2+3',
            }
            for addr, name in port_names.items():
                if addr in op:
                    annotation = f"  ; <<< {name}"
                    break
        
        if mn == 'in':
            annotation += "  ; IN (port read)"
        if mn == 'out':
            annotation += "  ; OUT (port write)"
        
        if mn == 'cmp' and ('0xa' in op or '0xb' in op or ', 5' in op or ', 0xa' in op or ', 0xb' in op):
            annotation += f"  ; <<< LOOP LIMIT? (cmp with {op})"
        
        if mn == 'call':
            annotation += "  ; <<< CALL"
        
        # Check for retf (end of function in large model)
        if mn in ('retf', 'lret'):
            annotation += "  ; <<< RETURN (end of function)"
        
        line = f"  {insn.address:05X}  {insn.bytes.hex():20s}  {mn:8s} {op:30s}{annotation}"
        print(line)
        
        # Stop at retf (function end)
        if mn in ('retf', 'lret') and insn.address > func_start + 20:
            # Check if this might be the end
            pass
    
    return instructions

def search_for_cmp_values(data, code_start):
    """
    Search for comparison with 10 (0x0A) and 11 (0x0B) near PPI2 port references.
    In 16-bit code: cmp reg, imm8
    - 83 F8 0A = cmp ax, 0xa
    - 83 FB 0A = cmp bx, 0xa  
    - 83 FE 0A = cmp si, 0xa
    - 83 FF 0A = cmp di, 0xa
    - 80 7E xx 0A = cmp byte [bp+xx], 0xa
    - etc.
    """
    print("\n=== Searching for loop limit comparisons near PPI2 references ===")
    
    # Find all ppi2 references
    ppi2_refs = []
    for pat in [b'\xba\x10\x03', b'\xba\x12\x03']:
        offset = code_start
        while True:
            pos = data.find(pat, offset)
            if pos == -1:
                break
            ppi2_refs.append(pos)
            offset = pos + 1
    
    # For each PPI2 ref, search nearby for cmp with 0x0A or 0x0B
    for ref in ppi2_refs:
        region = data[max(code_start, ref-300):ref+300]
        region_start = max(code_start, ref-300)
        
        for i in range(len(region)-2):
            byte = region[i]
            # 83 Fx 0A/0B - cmp reg, 10/11
            if byte == 0x83 and i+2 < len(region):
                modrm = region[i+1]
                imm = region[i+2]
                if (modrm & 0xF8) == 0xF8 and imm in (0x0A, 0x0B):
                    regs = {0xF8:'ax', 0xF9:'cx', 0xFA:'dx', 0xFB:'bx', 0xFC:'sp', 0xFD:'bp', 0xFE:'si', 0xFF:'di'}
                    reg = regs.get(modrm, '?')
                    abs_off = region_start + i
                    print(f"  cmp {reg}, {imm} at offset 0x{abs_off:X} (near PPI2 ref at 0x{ref:X}, delta={abs_off-ref})")
            
            # 3D 0A 00 - cmp ax, 0x000A
            if byte == 0x3D and i+2 < len(region):
                val = region[i+1] + region[i+2]*256
                if val in (0x0A, 0x0B):
                    abs_off = region_start + i
                    print(f"  cmp ax, {val} at offset 0x{abs_off:X} (near PPI2 ref at 0x{ref:X}, delta={abs_off-ref})")

def main():
    import os
    script_dir = os.path.dirname(os.path.abspath(__file__))
    exe_path = os.path.join(script_dir, EXE_PATH)
    
    print(f"Reading {exe_path}")
    data = read_exe(exe_path)
    print(f"File size: {len(data)} bytes")
    
    code_start = parse_mz_header(data)
    if code_start is None:
        return
    
    # Find port access patterns  
    port_refs = find_port_patterns(data, code_start)
    
    # Find function prologues
    prologues = find_function_boundaries(data, code_start)
    
    # Search for loop comparisons near PPI2
    search_for_cmp_values(data, code_start)
    
    # Find lpuls candidates
    candidates = find_lpuls_candidates(data, code_start, prologues, port_refs)
    
    # Disassemble each candidate
    for func_start, func_end, refs in candidates:
        analyze_lpuls_candidate(data, func_start, func_end)
        print()

if __name__ == "__main__":
    main()
