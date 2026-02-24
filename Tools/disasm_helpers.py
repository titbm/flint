"""
Disassemble helper functions from PROJ5.EXE v2.77:
- program_pt2() at 0x135AB
- read_pt2() at 0x135E1
- sh_open() at 0x13601
- Also find and disassemble process() 
"""

import struct
from capstone import *

EXE_PATH = r"..\!GENESIS\Flint 2.77\PROJ5.EXE"

def read_exe(path):
    with open(path, "rb") as f:
        return f.read()

def disasm(data, start, max_bytes=512, stop_at_retf=True):
    """Disassemble 16-bit code, optionally stopping at retf"""
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    
    code = data[start:start+max_bytes]
    lines = []
    
    for insn in md.disasm(code, start):
        port_names = {
            0x300: 'ADRPT0', 0x301: 'ADRPT0+1', 0x302: 'ADRPT0+2', 0x303: 'ADRPT0+3',
            0x304: 'ADRPT1', 0x305: 'ADRPT1+1', 0x306: 'ADRPT1+2', 0x307: 'ADRPT1+3',
            0x308: 'ADRPPI', 0x309: 'ADRPPI+1', 0x30a: 'ADRPPI+2', 0x30b: 'ADRPPI+3',
            0x30c: 'ADRRG', 
            0x310: 'ADRPPI2', 0x311: 'ADRPPI2+1', 0x312: 'ADRPPI2+2', 0x313: 'ADRPPI2+3',
            0x314: 'ADRPT2', 0x315: 'ADRPT2+1', 0x316: 'ADRPT2+2', 0x317: 'ADRPT2+3',
            0x31c: 'LRG',
        }
        
        annotation = ""
        raw = insn.bytes.hex()
        
        # Check for port addresses in operands
        for addr, name in port_names.items():
            hex_str = f"0x{addr:x}"
            if hex_str in insn.op_str:
                annotation = f"  ; {name}"
                break
        
        if insn.mnemonic == 'in':
            annotation += " [IN]"
        elif insn.mnemonic == 'out':
            annotation += " [OUT]"
        elif insn.mnemonic in ('call', 'lcall'):
            annotation += " [CALL]"
        elif insn.mnemonic in ('retf', 'lret'):
            annotation += " [RET]"
        
        line = f"  {insn.address:05X}  {raw:20s}  {insn.mnemonic:8s} {insn.op_str}{annotation}"
        lines.append(line)
        print(line)
        
        if stop_at_retf and insn.mnemonic in ('retf', 'lret') and insn.address > start + 4:
            break
    
    return lines

def find_process_function(data, code_start):
    """
    process() calls lpuls() (at near address relative to CS).
    lpuls() is at file offset 0x13468.
    The call instruction would be: 0E push cs + E8 xx xx call near
    In lpuls(), we see calls to sh_open at 0x13601 and program_pt2 at 0x135AB.
    
    process() should contain far calls to delay() and calls to lpuls().
    We can search for near calls to 0x13468.
    A near call E8 xx xx: target = offset_after_call + signed_disp16
    
    Let's find all near calls that target 0x13468.
    The pattern is: 0E (push cs) then E8 xx xx where offset_after_E8+xx_xx = 0x13468
    """
    
    targets_of_interest = {
        0x13468: 'lpuls()',
    }
    
    callers = {}
    
    # Search for "push cs + call near" patterns
    # In large model, near calls within same segment use: push cs; call near_offset
    # Or it could be done differently with lcall
    
    # Let's search for all E8 (near call) instructions and check targets
    # Near call: E8 disp16 → target = IP_after_call + disp16
    for offset in range(code_start, len(data) - 3):
        if data[offset] == 0xE8:
            disp = struct.unpack_from('<h', data, offset + 1)[0]
            target = (offset + 3 + disp) & 0xFFFF  # 16-bit wrap
            # But in segmented code, we need segment-relative addressing
            # Since we're looking at file offsets, we need to consider the segment
            # Let's try full file offset calculation
            target_full = offset + 3 + disp
            
            for tgt, name in targets_of_interest.items():
                if target_full == tgt:
                    if name not in callers:
                        callers[name] = []
                    callers[name].append(offset)
    
    print("\n=== Callers of lpuls() ===")
    for name, offsets in callers.items():
        for off in offsets:
            print(f"  Call to {name} at file offset 0x{off:X}")
    
    return callers

def find_function_start(data, call_offset):
    """Find the function prologue (push bp; mov bp,sp) before a given offset"""
    # Search backwards for prologue
    for off in range(call_offset, max(call_offset - 2000, 0), -1):
        if data[off:off+3] == b'\x55\x8b\xec':  # push bp; mov bp,sp
            return off
        # Also check for enter instruction: C8 xx xx 00
        if data[off] == 0xC8 and off + 3 < len(data) and data[off+3] == 0x00:
            return off
    return None

def main():
    import os
    script_dir = os.path.dirname(os.path.abspath(__file__))
    exe_path = os.path.join(script_dir, EXE_PATH)
    
    data = read_exe(exe_path)
    print(f"File: {exe_path} ({len(data)} bytes)")
    
    # 1. Disassemble program_pt2() at 0x135AB
    print(f"\n{'='*70}")
    print(f"program_pt2() @ 0x135AB")
    print(f"{'='*70}")
    disasm(data, 0x135AB, 200)
    
    # 2. Disassemble read_pt2() at 0x135E1
    print(f"\n{'='*70}")
    print(f"read_pt2() @ 0x135E1")
    print(f"{'='*70}")
    disasm(data, 0x135E1, 200)
    
    # 3. Disassemble sh_open() at 0x13601
    print(f"\n{'='*70}")
    print(f"sh_open() @ 0x13601")
    print(f"{'='*70}")
    disasm(data, 0x13601, 300)
    
    # 4. Find process() - the caller of lpuls()
    print(f"\n{'='*70}")
    print(f"Searching for callers of lpuls() (0x13468)...")
    print(f"{'='*70}")
    callers = find_process_function(data, 0x1E00)
    
    # 5. For each caller, find function start and disassemble
    if 'lpuls()' in callers:
        for call_off in callers['lpuls()']:
            func_start = find_function_start(data, call_off)
            if func_start:
                print(f"\n{'='*70}")
                print(f"Caller function starting at 0x{func_start:X} (calls lpuls at 0x{call_off:X})")
                print(f"{'='*70}")
                # Disassemble up to 1500 bytes (process() is a big function)
                disasm(data, func_start, 1500, stop_at_retf=True)
    
    # 6. Also search for callers of sh_open (0x13601) outside lpuls
    print(f"\n{'='*70}")
    print(f"Searching for all near calls to sh_open (0x13601)...")
    print(f"{'='*70}")
    for offset in range(0x1E00, len(data) - 3):
        if data[offset] == 0xE8:
            disp = struct.unpack_from('<h', data, offset + 1)[0]
            target = offset + 3 + disp
            if target == 0x13601:
                print(f"  Call to sh_open() at file offset 0x{offset:X}")

    # 7. sh_close() should be right after sh_open()
    # Find the retf of sh_open, then the next function
    print(f"\n{'='*70}")
    print(f"sh_close() (expected after sh_open)")
    print(f"{'='*70}")
    # Find retf after sh_open
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    code = data[0x13601:0x13601+200]
    end_off = 0x13601
    for insn in md.disasm(code, 0x13601):
        if insn.mnemonic in ('retf', 'lret') and insn.address > 0x13601 + 4:
            end_off = insn.address + insn.size
            break
    print(f"sh_close() expected at 0x{end_off:X}")
    disasm(data, end_off, 200)

if __name__ == "__main__":
    main()
