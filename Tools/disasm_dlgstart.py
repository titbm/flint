"""
Disassemble the dlgstart() jump table and switch case handlers from PROJ5.EXE.

Ghidra failed to recover the jump table at 0x0001d357. The decompilation shows:
  - dlgstart at 1928:3f0e
  - ClearRpt at 1928:4395 (immediately after dlgstart + its embedded data)
  - Jump table at CS:4359, 15 entries (case values + jump targets)
  - scan_ms returns case number, loop matches it in the table

This script:
1. Parses the MZ EXE header
2. Locates the code at segment 1928
3. Dumps the jump table entries 
4. Disassembles the switch case handler code
"""
import struct
import sys
import os

EXE_PATH = os.path.join(os.path.dirname(__file__), 
    "..", "!GENESIS", "Flint 2.77", "PROJ5.EXE")

def read_mz_header(data):
    """Parse DOS MZ EXE header."""
    if data[:2] != b'MZ' and data[:2] != b'ZM':
        raise ValueError("Not a valid MZ EXE")
    
    fields = struct.unpack_from('<HHHHHHHHHHHHHHH', data, 0)
    hdr = {
        'e_magic':    fields[0],
        'e_cblp':     fields[1],   # Bytes on last page
        'e_cp':       fields[2],   # Pages in file (512 bytes each)
        'e_crlc':     fields[3],   # Relocations
        'e_cparhdr':  fields[4],   # Header size in paragraphs (16 bytes)
        'e_minalloc': fields[5],
        'e_maxalloc': fields[6],
        'e_ss':       fields[7],   # Initial SS (relative)
        'e_sp':       fields[8],   # Initial SP
        'e_csum':     fields[9],
        'e_ip':       fields[10],  # Initial IP
        'e_cs':       fields[11],  # Initial CS (relative)
        'e_lfarlc':   fields[12],  # File offset of relocation table
        'e_ovno':     fields[13],  # Overlay number
    }
    hdr['header_size'] = hdr['e_cparhdr'] * 16
    
    # File size from header
    if hdr['e_cblp']:
        hdr['file_size'] = (hdr['e_cp'] - 1) * 512 + hdr['e_cblp']
    else:
        hdr['file_size'] = hdr['e_cp'] * 512
    
    return hdr

def seg_off_to_file(hdr, seg, off):
    """Convert segment:offset (relative to load base) to file offset."""
    return hdr['header_size'] + seg * 16 + off

def disasm_16bit(data, base_off, length, cs_seg):
    """Simple 16-bit x86 disassembler for the most common instructions."""
    pos = 0
    lines = []
    
    while pos < length:
        addr = base_off + pos
        b = data[pos]
        prefix = ""
        
        # Check for segment override prefixes
        seg_prefixes = {0x26: 'ES:', 0x2E: 'CS:', 0x36: 'SS:', 0x3E: 'DS:'}
        if b in seg_prefixes:
            prefix = seg_prefixes[b]
            pos += 1
            b = data[pos]
        
        instr = ""
        nbytes = 1
        raw_start = pos - (1 if prefix else 0)
        
        # --- Common instructions ---
        
        # NOP
        if b == 0x90:
            instr = "nop"
        
        # RET near
        elif b == 0xC3:
            instr = "ret"
        elif b == 0xCB:
            instr = "retf"
        elif b == 0xC2:
            imm = struct.unpack_from('<H', data, pos+1)[0]
            instr = f"ret {imm:#06x}"
            nbytes = 3
        elif b == 0xCA:
            imm = struct.unpack_from('<H', data, pos+1)[0]
            instr = f"retf {imm:#06x}"
            nbytes = 3
            
        # PUSH reg
        elif 0x50 <= b <= 0x57:
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            instr = f"push {regs[b-0x50]}"
        
        # POP reg
        elif 0x58 <= b <= 0x5f:
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            instr = f"pop {regs[b-0x58]}"
        
        # MOV reg16, imm16
        elif 0xB8 <= b <= 0xBF:
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            imm = struct.unpack_from('<H', data, pos+1)[0]
            instr = f"mov {regs[b-0xB8]}, {imm:#06x}"
            nbytes = 3
        
        # MOV reg8, imm8
        elif 0xB0 <= b <= 0xB7:
            regs8 = ['al','cl','dl','bl','ah','ch','dh','bh']
            imm = data[pos+1]
            instr = f"mov {regs8[b-0xB0]}, {imm:#04x}"
            nbytes = 2
        
        # XOR r/m16, r16 (0x31) or XOR r16, r/m16 (0x33)
        elif b in (0x31, 0x33, 0x29, 0x2B, 0x01, 0x03, 0x09, 0x0B, 0x39, 0x3B, 0x89, 0x8B):
            ops = {0x31:'xor', 0x33:'xor', 0x29:'sub', 0x2B:'sub', 
                   0x01:'add', 0x03:'add', 0x09:'or', 0x0B:'or',
                   0x39:'cmp', 0x3B:'cmp', 0x89:'mov', 0x8B:'mov'}
            op = ops[b]
            direction = b & 0x02  # 0=r/m,r  2=r,r/m
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            reg = (modrm >> 3) & 7
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            nbytes = 2
            
            if mod == 3:
                if direction:
                    instr = f"{op} {regs[reg]}, {regs[rm]}"
                else:
                    instr = f"{op} {regs[rm]}, {regs[reg]}"
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
                nbytes = 2 + extra
                if direction:
                    instr = f"{op} {regs[reg]}, {rm_str}"
                else:
                    instr = f"{op} {rm_str}, {regs[reg]}"
        
        # JMP short
        elif b == 0xEB:
            rel = struct.unpack_from('<b', data, pos+1)[0]
            target = addr + 2 + rel
            instr = f"jmp short {cs_seg:04X}:{target:04X}"
            nbytes = 2
        
        # JMP near
        elif b == 0xE9:
            rel = struct.unpack_from('<h', data, pos+1)[0]
            target = addr + 3 + rel
            instr = f"jmp near {cs_seg:04X}:{target:04X}"
            nbytes = 3
        
        # CALL near
        elif b == 0xE8:
            rel = struct.unpack_from('<h', data, pos+1)[0]
            target = addr + 3 + rel
            instr = f"call near {cs_seg:04X}:{target:04X}"
            nbytes = 3
        
        # CALL far
        elif b == 0x9A:
            off = struct.unpack_from('<H', data, pos+1)[0]
            seg = struct.unpack_from('<H', data, pos+3)[0]
            instr = f"call far {seg:04X}:{off:04X}"
            nbytes = 5
        
        # JMP far
        elif b == 0xEA:
            off = struct.unpack_from('<H', data, pos+1)[0]
            seg = struct.unpack_from('<H', data, pos+3)[0]
            instr = f"jmp far {seg:04X}:{off:04X}"
            nbytes = 5
        
        # Conditional jumps (short)
        elif 0x70 <= b <= 0x7F:
            cc = ['jo','jno','jb','jnb','jz','jnz','jbe','ja',
                  'js','jns','jp','jnp','jl','jge','jle','jg']
            rel = struct.unpack_from('<b', data, pos+1)[0]
            target = addr + 2 + rel
            instr = f"{cc[b-0x70]} {cs_seg:04X}:{target:04X}"
            nbytes = 2
        
        # INT
        elif b == 0xCD:
            instr = f"int {data[pos+1]:#04x}"
            nbytes = 2
        
        # CMP AX, imm16
        elif b == 0x3D:
            imm = struct.unpack_from('<H', data, pos+1)[0]
            instr = f"cmp ax, {imm:#06x}"
            nbytes = 3
        
        # CMP AL, imm8
        elif b == 0x3C:
            imm = data[pos+1]
            instr = f"cmp al, {imm:#04x}"
            nbytes = 2
        
        # ADD/OR/ADC/SBB/AND/SUB/XOR/CMP r/m16, imm16 (0x81)
        # ADD/OR/ADC/SBB/AND/SUB/XOR/CMP r/m16, imm8 sign-ext (0x83)
        elif b in (0x81, 0x83, 0x80):
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            op_idx = (modrm >> 3) & 7
            rm = modrm & 7
            ops = ['add','or','adc','sbb','and','sub','xor','cmp']
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            
            if mod == 3:
                rm_str = regs[rm]
                extra = 0
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
            
            nbytes = 2 + extra
            if b == 0x83:
                imm = struct.unpack_from('<b', data, pos+nbytes)[0]
                instr = f"{ops[op_idx]} {rm_str}, {imm:#04x}"
                nbytes += 1
            elif b == 0x81:
                imm = struct.unpack_from('<H', data, pos+nbytes)[0]
                instr = f"{ops[op_idx]} {rm_str}, {imm:#06x}"
                nbytes += 2
            else:  # 0x80
                imm = data[pos+nbytes]
                instr = f"{ops[op_idx]} byte {rm_str}, {imm:#04x}"
                nbytes += 1
        
        # INC reg16
        elif 0x40 <= b <= 0x47:
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            instr = f"inc {regs[b-0x40]}"
        
        # DEC reg16
        elif 0x48 <= b <= 0x4F:
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            instr = f"dec {regs[b-0x48]}"
        
        # LEA
        elif b == 0x8D:
            modrm = data[pos+1]
            reg = (modrm >> 3) & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            rm_str, extra = decode_modrm16(data, pos+1, prefix)
            instr = f"lea {regs[reg]}, {rm_str}"
            nbytes = 2 + extra
        
        # TEST r/m, r
        elif b in (0x85, 0x84):
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            reg = (modrm >> 3) & 7
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            if mod == 3:
                instr = f"test {regs[rm]}, {regs[reg]}"
                nbytes = 2
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
                nbytes = 2 + extra
                instr = f"test {rm_str}, {regs[reg]}"
        
        # XCHG
        elif b == 0x87:
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            reg = (modrm >> 3) & 7
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            if mod == 3:
                instr = f"xchg {regs[rm]}, {regs[reg]}"
                nbytes = 2
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
                nbytes = 2 + extra
                instr = f"xchg {rm_str}, {regs[reg]}"
                
        # MOV r/m16, imm16 (0xC7) or MOV r/m8, imm8 (0xC6)
        elif b in (0xC7, 0xC6):
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            if mod == 3:
                if b == 0xC7:
                    imm = struct.unpack_from('<H', data, pos+2)[0]
                    instr = f"mov {regs[rm]}, {imm:#06x}"
                    nbytes = 4
                else:
                    regs8 = ['al','cl','dl','bl','ah','ch','dh','bh']
                    imm = data[pos+2]
                    instr = f"mov {regs8[rm]}, {imm:#04x}"
                    nbytes = 3
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
                nbytes = 2 + extra
                if b == 0xC7:
                    imm = struct.unpack_from('<H', data, pos+nbytes)[0]
                    instr = f"mov word {rm_str}, {imm:#06x}"
                    nbytes += 2
                else:
                    imm = data[pos+nbytes]
                    instr = f"mov byte {rm_str}, {imm:#04x}"
                    nbytes += 1
        
        # OUT DX, AL
        elif b == 0xEE:
            instr = "out dx, al"
        # OUT DX, AX
        elif b == 0xEF:
            instr = "out dx, ax"
        # IN AL, DX
        elif b == 0xEC:
            instr = "in al, dx"
        # IN AX, DX
        elif b == 0xED:
            instr = "in ax, dx"
        # OUT imm8, AL
        elif b == 0xE6:
            instr = f"out {data[pos+1]:#04x}, al"
            nbytes = 2
        # IN AL, imm8
        elif b == 0xE4:
            instr = f"in al, {data[pos+1]:#04x}"
            nbytes = 2
            
        # CLD/STD/CLI/STI
        elif b == 0xFC: instr = "cld"
        elif b == 0xFD: instr = "std"
        elif b == 0xFA: instr = "cli"
        elif b == 0xFB: instr = "sti"
        
        # CBW/CWD
        elif b == 0x98: instr = "cbw"
        elif b == 0x99: instr = "cwd"
        
        # 0xFF group (INC/DEC/CALL/JMP/PUSH r/m)
        elif b == 0xFF:
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            op_idx = (modrm >> 3) & 7
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            ops_ff = ['inc','dec','call','call far','jmp','jmp far','push','???']
            
            if mod == 3:
                instr = f"{ops_ff[op_idx]} {regs[rm]}"
                nbytes = 2
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
                nbytes = 2 + extra
                instr = f"{ops_ff[op_idx]} word {rm_str}"
        
        # 0xF7 group (TEST/NOT/NEG/MUL/IMUL/DIV/IDIV r/m16)
        elif b == 0xF7:
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            op_idx = (modrm >> 3) & 7
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            ops_f7 = ['test','???','not','neg','mul','imul','div','idiv']
            
            if mod == 3:
                if op_idx == 0:  # TEST r/m, imm
                    imm = struct.unpack_from('<H', data, pos+2)[0]
                    instr = f"test {regs[rm]}, {imm:#06x}"
                    nbytes = 4
                else:
                    instr = f"{ops_f7[op_idx]} {regs[rm]}"
                    nbytes = 2
            else:
                rm_str, extra = decode_modrm16(data, pos+1, prefix)
                nbytes = 2 + extra
                if op_idx == 0:
                    imm = struct.unpack_from('<H', data, pos+nbytes)[0]
                    instr = f"test word {rm_str}, {imm:#06x}"
                    nbytes += 2
                else:
                    instr = f"{ops_f7[op_idx]} word {rm_str}"
        
        # SHL/SHR/SAR/etc group (0xD1 = shift by 1, 0xD3 = shift by CL)
        elif b in (0xD1, 0xD3, 0xD0, 0xD2, 0xC1, 0xC0):
            modrm = data[pos+1]
            mod = (modrm >> 6) & 3
            op_idx = (modrm >> 3) & 7
            rm = modrm & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            ops_shift = ['rol','ror','rcl','rcr','shl','shr','???','sar']
            
            if mod == 3:
                rm_str = regs[rm]
                extra = 0
            else:
                rm_str, extra_modrm = decode_modrm16(data, pos+1, prefix)
                extra = extra_modrm
            
            nbytes = 2 + extra
            if b in (0xD1, 0xD0):
                instr = f"{ops_shift[op_idx]} {rm_str}, 1"
            elif b in (0xD3, 0xD2):
                instr = f"{ops_shift[op_idx]} {rm_str}, cl"
            else:  # C1, C0
                imm = data[pos+nbytes]
                instr = f"{ops_shift[op_idx]} {rm_str}, {imm}"
                nbytes += 1
        
        # MOV AX, [mem]
        elif b == 0xA1:
            addr16 = struct.unpack_from('<H', data, pos+1)[0]
            instr = f"mov ax, [{prefix}{addr16:#06x}]"
            nbytes = 3
        # MOV [mem], AX
        elif b == 0xA3:
            addr16 = struct.unpack_from('<H', data, pos+1)[0]
            instr = f"mov [{prefix}{addr16:#06x}], ax"
            nbytes = 3
            
        # LOOP/LOOPZ/LOOPNZ
        elif b == 0xE2:
            rel = struct.unpack_from('<b', data, pos+1)[0]
            target = addr + 2 + rel
            instr = f"loop {cs_seg:04X}:{target:04X}"
            nbytes = 2
        elif b == 0xE1:
            rel = struct.unpack_from('<b', data, pos+1)[0]
            target = addr + 2 + rel
            instr = f"loopz {cs_seg:04X}:{target:04X}"
            nbytes = 2
        elif b == 0xE0:
            rel = struct.unpack_from('<b', data, pos+1)[0]
            target = addr + 2 + rel
            instr = f"loopnz {cs_seg:04X}:{target:04X}"
            nbytes = 2
            
        # 0x0F prefix (extended instructions - just show raw for now)
        elif b == 0x0F:
            b2 = data[pos+1]
            # Conditional jumps near (0F 80-8F)
            if 0x80 <= b2 <= 0x8F:
                cc = ['jo','jno','jb','jnb','jz','jnz','jbe','ja',
                      'js','jns','jp','jnp','jl','jge','jle','jg']
                rel = struct.unpack_from('<h', data, pos+2)[0]
                target = addr + 4 + rel
                instr = f"{cc[b2-0x80]} near {cs_seg:04X}:{target:04X}"
                nbytes = 4
            else:
                instr = f"db 0x0F, 0x{b2:02X}  ; (extended)"
                nbytes = 2
        
        # LES/LDS
        elif b == 0xC4:
            modrm = data[pos+1]
            reg = (modrm >> 3) & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            rm_str, extra = decode_modrm16(data, pos+1, prefix)
            instr = f"les {regs[reg]}, {rm_str}"
            nbytes = 2 + extra
        elif b == 0xC5:
            modrm = data[pos+1]
            reg = (modrm >> 3) & 7
            regs = ['ax','cx','dx','bx','sp','bp','si','di']
            rm_str, extra = decode_modrm16(data, pos+1, prefix)
            instr = f"lds {regs[reg]}, {rm_str}"
            nbytes = 2 + extra
        
        else:
            raw_bytes = ' '.join(f'{data[pos+j]:02X}' for j in range(min(6, length-pos)))
            instr = f"db {raw_bytes}"
            # Try to advance past unknown instruction
            nbytes = 1
        
        # Build hex dump
        raw = data[raw_start:pos+nbytes] if prefix else data[pos:pos+nbytes]
        hex_str = ' '.join(f'{x:02X}' for x in raw)
        
        file_addr = addr  # This is the offset within the segment
        lines.append(f"  {cs_seg:04X}:{file_addr:04X}  {hex_str:<20s}  {prefix}{instr}")
        
        pos += nbytes
    
    return lines


def decode_modrm16(data, modrm_pos, prefix=""):
    """Decode 16-bit ModR/M byte, return (operand_string, extra_bytes_consumed)."""
    modrm = data[modrm_pos]
    mod = (modrm >> 6) & 3
    rm = modrm & 7
    
    rm_bases = ['bx+si','bx+di','bp+si','bp+di','si','di','bp','bx']
    
    if mod == 0:
        if rm == 6:
            disp = struct.unpack_from('<H', data, modrm_pos+1)[0]
            return f"[{prefix}{disp:#06x}]", 2
        else:
            return f"[{prefix}{rm_bases[rm]}]", 0
    elif mod == 1:
        disp = struct.unpack_from('<b', data, modrm_pos+1)[0]
        if disp >= 0:
            return f"[{prefix}{rm_bases[rm]}+{disp:#04x}]", 1
        else:
            return f"[{prefix}{rm_bases[rm]}{disp:#05x}]", 1
    elif mod == 2:
        disp = struct.unpack_from('<H', data, modrm_pos+1)[0]
        return f"[{prefix}{rm_bases[rm]}+{disp:#06x}]", 2
    else:
        return "???", 0  # mod==3 should be handled by caller


def main():
    exe_path = os.path.abspath(EXE_PATH)
    print(f"Reading: {exe_path}")
    
    with open(exe_path, 'rb') as f:
        data = f.read()
    
    hdr = read_mz_header(data)
    print(f"\n=== MZ Header ===")
    print(f"  Header size:  {hdr['header_size']} bytes ({hdr['e_cparhdr']} paragraphs)")
    print(f"  File size:    {hdr['file_size']} bytes (actual: {len(data)})")
    print(f"  Entry point:  {hdr['e_cs']:04X}:{hdr['e_ip']:04X}")
    print(f"  Stack:        {hdr['e_ss']:04X}:{hdr['e_sp']:04X}")
    print(f"  Relocations:  {hdr['e_crlc']} at offset {hdr['e_lfarlc']:#06x}")
    
    # The segment 1928 is relative to load base
    # We need to figure out the actual mapping
    # Try direct mapping first: file_offset = header_size + seg*16 + offset
    
    SEG = 0x1928
    
    # First let's verify by finding known string "Start" near dlgstart
    # dlgstart at 1928:3f0e calls WndBkgr(..., "Start", ...)
    # The string is likely in data segment, not code segment.
    # But let's check ClearRpt pattern to verify our segment mapping.
    
    # ClearRpt at 1928:4395 is: loop storing 0 to nmrpt[0..9]
    # It's 23 bytes long.
    
    # Let's try to locate the segment by searching for known byte patterns
    # From v2.61 source, ClearRpt does: for(int k=0; k<20; k++) nmrpt[k]=0;
    # In 16-bit: int array of 10 elements (20 bytes), zeroing loop.
    
    # Actually, let's just try the straightforward mapping and verify
    file_off_clearrpt = seg_off_to_file(hdr, SEG, 0x4395)
    print(f"\n=== Verification ===")
    print(f"  ClearRpt should be at file offset: {file_off_clearrpt:#x}")
    
    if file_off_clearrpt < len(data):
        snippet = data[file_off_clearrpt:file_off_clearrpt+23]
        print(f"  ClearRpt bytes: {snippet.hex(' ')}")
    else:
        print(f"  ERROR: offset {file_off_clearrpt:#x} beyond file size {len(data)}")
        
        # Try to find the right segment base by searching for patterns
        # Let's search for the jump table structure: 15 entries of case values 0-14
        # The case values would be: 00 00  01 00  02 00  03 00  04 00 ...
        print("\n  Trying to locate jump table by pattern search...")
        
        # Search for: 00 00 01 00 02 00 03 00 04 00 05 00 06 00 07 00 08 00
        pattern = bytes([0,0, 1,0, 2,0, 3,0, 4,0, 5,0, 6,0, 7,0, 8,0])
        offset = 0
        while True:
            idx = data.find(pattern, offset)
            if idx == -1:
                break
            # Check if followed by 09 00 0A 00 0B 00 0C 00 
            remaining = data[idx+len(pattern):idx+len(pattern)+12]
            if remaining[:2] == bytes([9,0]) and remaining[2:4] == bytes([10,0]):
                print(f"  Found potential case value table at file offset {idx:#x}")
                # Show the full table
                table_data = data[idx:idx+60]
                print(f"  Table bytes: {table_data.hex(' ')}")
                
                # Decode: 15 case values (ints) then 15 jump targets (offsets)
                case_vals = []
                jump_targets = []
                for j in range(15):
                    cv = struct.unpack_from('<H', data, idx + j*2)[0]
                    case_vals.append(cv)
                for j in range(15):
                    jt = struct.unpack_from('<H', data, idx + 30 + j*2)[0]
                    jump_targets.append(jt)
                
                print(f"\n  Case values:   {case_vals}")
                print(f"  Jump targets:  {[f'{t:04X}' for t in jump_targets]}")
                
                # Calculate the implied segment base
                # file_offset = header_size + seg*16 + 0x4359
                # seg*16 = file_offset - header_size - 0x4359
                implied_seg16 = idx - hdr['header_size'] - 0x4359
                if implied_seg16 >= 0:
                    implied_seg = implied_seg16 // 16
                    remainder = implied_seg16 % 16
                    print(f"  Implied segment: {implied_seg:04X} (remainder: {remainder})")
                
            offset = idx + 1
        
        # Also try smaller header or OVL structure
        # Borland C++ 4.5 might use RTM.EXE for DPMI
        # Check if there's a Borland overlay/DPMI header
        print(f"\n  Checking for FBOV overlay header...")
        fbov_idx = data.find(b'FBOV')
        if fbov_idx != -1:
            print(f"  Found FBOV at offset {fbov_idx:#x}")
            # Read stub header info
            stub_size_pages = struct.unpack_from('<H', data, 2)[0]
            stub_last = struct.unpack_from('<H', data, 4)[0]  
            # Hmm, that's regular MZ fields
        
        # Let's also check if the file has a different base
        # Perhaps Ghidra rebased at a different address
        # Let's try to find the entry point code
        entry_off = seg_off_to_file(hdr, hdr['e_cs'], hdr['e_ip'])
        if entry_off < len(data):
            print(f"\n  Entry point at file offset {entry_off:#x}:")
            snippet = data[entry_off:entry_off+16]
            print(f"  {snippet.hex(' ')}")
        
        # Let's try offset 0 for the segment (i.e., maybe 1928 is absolute)
        # and we just need header_size + offset
        for test_base in [0, 0x100, 0x1000]:
            test_off = hdr['header_size'] + test_base + 0x4359
            if test_off < len(data):
                chunk = data[test_off:test_off+30]
                vals = [struct.unpack_from('<H', chunk, i*2)[0] for i in range(min(15, len(chunk)//2))]
                if vals[:5] == [0, 1, 2, 3, 4]:
                    print(f"\n  ** Match with base {test_base:#x}! Offset {test_off:#x}")
                    print(f"  Values: {vals}")
        
        return
    
    print("\n=== Jump Table at 1928:4359 ===")
    table_off = seg_off_to_file(hdr, SEG, 0x4359)
    table_data = data[table_off:table_off+60]
    
    case_vals = []
    jump_targets = []
    for j in range(15):
        cv = struct.unpack_from('<h', data, table_off + j*2)[0]
        case_vals.append(cv)
    for j in range(15):
        jt = struct.unpack_from('<H', data, table_off + 30 + j*2)[0]
        jump_targets.append(jt)
    
    print(f"  Raw bytes: {table_data.hex(' ')}")
    print(f"\n  {'Case':>6s}  {'Target':>8s}")
    print(f"  {'-----':>6s}  {'------':>8s}")
    for cv, jt in zip(case_vals, jump_targets):
        print(f"  {cv:>6d}  {SEG:04X}:{jt:04X}")
    
    # Now disassemble each case handler
    # Sort targets to find code ranges
    unique_targets = sorted(set(jump_targets))
    
    # Map case -> target for annotation
    target_to_cases = {}
    for cv, jt in zip(case_vals, jump_targets):
        target_to_cases.setdefault(jt, []).append(cv)
    
    # Also note ClearRpt at 4395 as the function end boundary
    end_boundary = 0x4395
    
    print(f"\n=== Disassembly of switch case handlers ===")
    print(f"  (Function end boundary: {SEG:04X}:{end_boundary:04X})")
    
    for i, target in enumerate(unique_targets):
        # Determine end of this handler
        if i + 1 < len(unique_targets):
            next_target = unique_targets[i + 1]
        else:
            next_target = end_boundary
        
        length = min(next_target - target, 512)  # cap at 512 bytes per handler
        if length <= 0:
            continue
        
        cases = target_to_cases.get(target, [])
        case_str = ', '.join(str(c) for c in cases)
        
        print(f"\n  --- Case {case_str} --- ({SEG:04X}:{target:04X})")
        
        handler_off = seg_off_to_file(hdr, SEG, target)
        handler_data = data[handler_off:handler_off+length]
        
        lines = disasm_16bit(handler_data, target, length, SEG)
        for line in lines:
            print(line)
    
    # Also disassemble the main dlgstart code around the jump table dispatch
    # From 3f0e to the first handler or the table
    print(f"\n=== dlgstart full disassembly (1928:3F0E to jump dispatch) ===")
    start = 0x3f0e
    # Disassemble up to the jump table
    total_len = 0x4359 - start
    dlg_off = seg_off_to_file(hdr, SEG, start)
    dlg_data = data[dlg_off:dlg_off+total_len]
    
    lines = disasm_16bit(dlg_data, start, total_len, SEG)
    for line in lines:
        print(line)


def main2():
    """Disassemble using the discovered segment mapping."""
    exe_path = os.path.abspath(EXE_PATH)
    
    with open(exe_path, 'rb') as f:
        data = f.read()
    
    hdr = read_mz_header(data)
    
    # Ghidra used segment 1928 with load base 1000
    # Physical file segment = 1928 - 1000 = 0928
    # file_offset = header_size + 0x0928*16 + offset
    GHIDRA_SEG = 0x1928
    FILE_SEG = 0x0928
    HEADER = hdr['header_size']  # 0x1E00
    
    def file_off(offset):
        return HEADER + FILE_SEG * 16 + offset
    
    # Read and verify jump table
    table_off = file_off(0x4359)
    print(f"=== Jump Table at {GHIDRA_SEG:04X}:4359 (file offset {table_off:#x}) ===\n")
    
    case_vals = []
    jump_targets = []
    for j in range(15):
        cv = struct.unpack_from('<h', data, table_off + j*2)[0]
        case_vals.append(cv)
    for j in range(15):
        jt = struct.unpack_from('<H', data, table_off + 30 + j*2)[0]
        jump_targets.append(jt)
    
    # Map from v2.77 reconstruction:
    case_names = {
        0: 'Ok', 1: 'Cancel', 2: '+', 3: '-', 
        4: 'Beginning', 5: 'PointNumber', 6: 'Continuation', 7: 'CMOS',
        8: 'EndSens', 9: 'DrCheck', 10: 'Stop', 11: 'Reboot', 
        12: 'Ignore', 13: 'InputArea', 255: 'KeyHandler'
    }
    
    print(f"  {'Case':>6s}  {'Name':<14s}  {'Target':>10s}")
    print(f"  {'-----':>6s}  {'----':<14s}  {'------':>10s}")
    for cv, jt in zip(case_vals, jump_targets):
        name = case_names.get(cv, '???')
        print(f"  {cv:>6d}  {name:<14s}  {GHIDRA_SEG:04X}:{jt:04X}")
    
    # Build target-to-cases map
    target_to_cases = {}
    for cv, jt in zip(case_vals, jump_targets):
        target_to_cases.setdefault(jt, []).append(cv)
    
    unique_targets = sorted(set(jump_targets))
    
    # ClearRpt at 4395 is the function after the jump table
    end_boundary = 0x4395
    
    # Disassemble each case handler
    print(f"\n{'='*70}")
    print(f"=== Case handlers disassembly ===")
    print(f"{'='*70}")
    
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
        
        print(f"\n--- Case {case_str} ---")
        print(f"--- {GHIDRA_SEG:04X}:{target:04X} to {GHIDRA_SEG:04X}:{target+length:04X} ({length} bytes) ---")
        
        handler_off = file_off(target)
        handler_data = data[handler_off:handler_off+length]
        
        lines = disasm_16bit(handler_data, target, length, GHIDRA_SEG)
        for line in lines:
            print(line)
    
    # Also disassemble the dispatch loop (around where the jump table is used)
    # The code before the table should set up the loop
    # Let's disassemble from just before the jump: scan_ms call area
    # From Ghidra: the "do" loop calls scan_ms then searches the table
    # Let's find the scan_ms call and the dispatch
    
    print(f"\n{'='*70}")
    print(f"=== Dispatch loop area (before table) ===")
    print(f"{'='*70}")
    
    # The main loop body should be between ~40A0 and 40DB (start of case 0)
    # Let's disassemble 100 bytes before case 0
    dispatch_start = unique_targets[0] - 150
    dispatch_len = 150
    
    print(f"\n--- {GHIDRA_SEG:04X}:{dispatch_start:04X} to {GHIDRA_SEG:04X}:{dispatch_start+dispatch_len:04X} ---")
    
    d_off = file_off(dispatch_start)
    d_data = data[d_off:d_off+dispatch_len]
    
    lines = disasm_16bit(d_data, dispatch_start, dispatch_len, GHIDRA_SEG)
    for line in lines:
        print(line)


if __name__ == '__main__':
    main2()
