"""
Disassemble process() and move() from PROJ5.EXE using Capstone.
Focus on finding differences in Z calculation and move logic.
"""
import struct
import os
from capstone import *

EXE_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)),
    "..", "!GENESIS", "Flint 2.77", "PROJ5.EXE")

def read_mz_header(data):
    fields = struct.unpack_from('<HHHHHHHHHHHHHHH', data, 0)
    return {'header_size': fields[4] * 16}

GHIDRA_BASE = 0x1000  # Ghidra load base in segments

def file_off(hdr, ghidra_seg, offset):
    file_seg = ghidra_seg - GHIDRA_BASE
    return hdr['header_size'] + file_seg * 16 + offset

def disasm_block(md, data, hdr, ghidra_seg, start_off, end_off, label=""):
    """Disassemble a block of code."""
    length = end_off - start_off
    foff = file_off(hdr, ghidra_seg, start_off)
    code_bytes = data[foff:foff+length]
    
    if label:
        print(f"\n{'='*78}")
        print(f"  {label}")
        print(f"  [{ghidra_seg:04X}:{start_off:04X} - {ghidra_seg:04X}:{end_off:04X}]  ({length} bytes)")
        print(f"{'='*78}")
    
    for instr in md.disasm(code_bytes, start_off):
        addr_str = f"{ghidra_seg:04X}:{instr.address:04X}"
        hex_str = instr.bytes.hex(' ')
        line = f"  {addr_str}  {hex_str:<30s}  {instr.mnemonic:<8s} {instr.op_str}"
        print(line)

def main():
    with open(os.path.abspath(EXE_PATH), 'rb') as f:
        data = f.read()
    
    hdr = read_mz_header(data)
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    
    # PIC.CPP functions are in segment 215c (Ghidra) = 015c (file)
    PIC_SEG = 0x215c
    
    # Function addresses from Ghidra annotations:
    # process()  215c:02ac - 215c:05ad (769 bytes)
    # move_sen() 215c:05ad - 215c:0750 (419 bytes)  
    # move()     215c:0750 - 215c:0b84 (1076 bytes)
    # seg_time() 215c:0b84 - 215c:0c45 (193 bytes)
    # calc_k2()  215c:0c45 - 215c:0cdc (151 bytes)
    
    print("=" * 78)
    print("  DISASSEMBLY OF PIC.CPP FUNCTIONS FROM PROJ5.EXE")
    print("=" * 78)
    
    disasm_block(md, data, hdr, PIC_SEG, 0x02ac, 0x05ad, "process()")
    print()
    disasm_block(md, data, hdr, PIC_SEG, 0x05ad, 0x0750, "move_sen()")
    print()
    disasm_block(md, data, hdr, PIC_SEG, 0x0750, 0x0b84, "move()")
    print()
    disasm_block(md, data, hdr, PIC_SEG, 0x0b84, 0x0c45, "seg_time()")
    print()
    disasm_block(md, data, hdr, PIC_SEG, 0x0c45, 0x0cdc, "calc_k2()")

if __name__ == '__main__':
    main()
