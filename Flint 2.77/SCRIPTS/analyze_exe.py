#!/usr/bin/env python3
"""
Анализатор DOS MZ EXE файла PROJ5.EXE
Извлекает строки, разбирает заголовок, дизассемблирует код
"""
import struct
import sys

EXE_PATH = "PROJ5.EXE"

def read_exe():
    with open(EXE_PATH, "rb") as f:
        return f.read()

def parse_mz_header(data):
    """Разбор DOS MZ заголовка"""
    print("=" * 70)
    print("  MZ HEADER ANALYSIS")
    print("=" * 70)
    
    fields = struct.unpack_from("<2sHHHHHHHHHHHHH", data, 0)
    sig = fields[0]
    last_page_size = fields[1]
    page_count = fields[2]
    reloc_count = fields[3]
    header_paragraphs = fields[4]
    min_alloc = fields[5]
    max_alloc = fields[6]
    init_ss = fields[7]
    init_sp = fields[8]
    checksum = fields[9]
    init_ip = fields[10]
    init_cs = fields[11]
    reloc_offset = fields[12]
    overlay_num = fields[13]
    
    header_size = header_paragraphs * 16
    if last_page_size > 0:
        exe_size = (page_count - 1) * 512 + last_page_size
    else:
        exe_size = page_count * 512
    code_start = header_size
    
    print(f"  Сигнатура:          {sig}")
    print(f"  Размер последней стр: {last_page_size} байт")
    print(f"  Количество страниц:   {page_count}")
    print(f"  Relocations:          {reloc_count}")
    print(f"  Размер заголовка:     {header_size} байт ({header_paragraphs} параграфов)")
    print(f"  Min extra memory:     {min_alloc} параграфов ({min_alloc*16} байт)")
    print(f"  Max extra memory:     {max_alloc} параграфов")
    print(f"  Initial SS:SP:        {init_ss:04X}:{init_sp:04X}")
    print(f"  Initial CS:IP:        {init_cs:04X}:{init_ip:04X}")
    print(f"  Entry point offset:   0x{code_start + init_cs*16 + init_ip:X}")
    print(f"  Reloc table offset:   0x{reloc_offset:X}")
    print(f"  Overlay number:       {overlay_num}")
    print(f"  EXE size (по заголовку): {exe_size} байт")
    print(f"  Реальный размер файла:   {len(data)} байт")
    
    if len(data) > exe_size:
        print(f"  ** Оверлей/данные после EXE: {len(data) - exe_size} байт (offset 0x{exe_size:X})")
    
    # Relocations
    if reloc_count > 0 and reloc_offset > 0:
        print(f"\n  Relocation table ({reloc_count} записей):")
        for i in range(min(reloc_count, 20)):
            off, seg = struct.unpack_from("<HH", data, reloc_offset + i * 4)
            print(f"    [{i:3d}] {seg:04X}:{off:04X}  (file offset 0x{header_size + seg*16 + off:X})")
        if reloc_count > 20:
            print(f"    ... (ещё {reloc_count - 20})")
    
    return header_size, init_cs, init_ip, exe_size

def extract_strings(data, min_len=4):
    """Извлекаем ASCII-строки из бинарника"""
    print("\n" + "=" * 70)
    print("  EXTRACTED STRINGS")
    print("=" * 70)
    
    strings = []
    current = []
    start_offset = 0
    
    for i, b in enumerate(data):
        if 0x20 <= b <= 0x7E:  # printable ASCII
            if not current:
                start_offset = i
            current.append(chr(b))
        else:
            if len(current) >= min_len:
                s = ''.join(current)
                strings.append((start_offset, s))
            current = []
    
    if len(current) >= min_len:
        strings.append((start_offset, ''.join(current)))
    
    # Группируем по категориям
    ui_strings = []
    file_strings = []
    error_strings = []
    hw_strings = []
    other_strings = []
    
    for offset, s in strings:
        sl = s.lower()
        if any(k in sl for k in ['error', 'fail', 'invalid', 'cannot', 'unable', 'divide', 'overflow', 'null check']):
            error_strings.append((offset, s))
        elif any(k in sl for k in ['.bft', '.cfg', '.pif', '.cft', '.bmp', '.gls', 'file', 'path', 'dir', '.exe', '.com', '.bat', '.dat']):
            file_strings.append((offset, s))
        elif any(k in sl for k in ['laser', 'pump', 'gate', 'motor', 'port', 'timer', 'axis', 'speed', 'step', 'position', 'table', 'calibr']):
            hw_strings.append((offset, s))
        elif any(k in sl for k in ['press', 'click', 'key', 'button', 'menu', 'window', 'dialog', 'f1', 'f2', 'f3', 'f4', 'f5', 'f6', 'f7', 'f8', 'f9', 'f10', 'esc', 'enter', 'start', 'stop', 'exit', 'help']):
            ui_strings.append((offset, s))
        elif len(s) >= 5:
            other_strings.append((offset, s))
    
    def print_group(title, items, max_show=50):
        if items:
            print(f"\n  --- {title} ({len(items)} шт.) ---")
            for offset, s in items[:max_show]:
                print(f"    0x{offset:05X}: {s}")
            if len(items) > max_show:
                print(f"    ... (ещё {len(items) - max_show})")
    
    print_group("ОШИБКИ / ПРЕДУПРЕЖДЕНИЯ", error_strings)
    print_group("ФАЙЛЫ / ПУТИ", file_strings)
    print_group("УПРАВЛЕНИЕ ОБОРУДОВАНИЕМ (лазер, моторы)", hw_strings)
    print_group("ИНТЕРФЕЙС (UI)", ui_strings)
    print_group("ПРОЧИЕ СТРОКИ", other_strings, max_show=80)
    
    print(f"\n  Всего строк: {len(strings)}")
    return strings

def find_code_patterns(data, header_size):
    """Поиск характерных паттернов в коде"""
    print("\n" + "=" * 70)
    print("  CODE PATTERNS / PORT I/O")
    print("=" * 70)
    
    # Ищем инструкции IN/OUT (обращения к портам)
    # IN AL, imm8: E4 xx
    # IN AX, imm8: E5 xx  
    # OUT imm8, AL: E6 xx
    # OUT imm8, AX: E7 xx
    # IN AL, DX: EC
    # IN AX, DX: ED
    # OUT DX, AL: EE
    # OUT DX, AX: EF
    
    port_accesses = []
    for i in range(header_size, len(data) - 1):
        if data[i] == 0xE4:
            port_accesses.append((i, f"IN  AL, 0x{data[i+1]:02X} (port {data[i+1]})"))
        elif data[i] == 0xE5:
            port_accesses.append((i, f"IN  AX, 0x{data[i+1]:02X} (port {data[i+1]})"))
        elif data[i] == 0xE6:
            port_accesses.append((i, f"OUT 0x{data[i+1]:02X}, AL (port {data[i+1]})"))
        elif data[i] == 0xE7:
            port_accesses.append((i, f"OUT 0x{data[i+1]:02X}, AX (port {data[i+1]})"))
    
    if port_accesses:
        print(f"\n  Прямые обращения к портам (immediate) - {len(port_accesses)} шт.:")
        seen_ports = {}
        for offset, desc in port_accesses:
            port = data[offset + 1]
            if port not in seen_ports:
                seen_ports[port] = []
            seen_ports[port].append((offset, desc))
        
        for port in sorted(seen_ports.keys()):
            items = seen_ports[port]
            port_name = {
                0x20: "PIC master",
                0x21: "PIC master mask",
                0x40: "PIT Ch0 (timer)",
                0x41: "PIT Ch1",
                0x42: "PIT Ch2 (speaker)",
                0x43: "PIT control",
                0x60: "Keyboard",
                0x61: "System control",
                0x64: "Keyboard controller",
                0x3F8: "COM1",
                0x2F8: "COM2",
                0x378: "LPT1",
            }.get(port, "")
            print(f"    Port 0x{port:02X} {port_name}: {len(items)} обращений")
            for offset, desc in items[:5]:
                print(f"      0x{offset:05X}: {desc}")
            if len(items) > 5:
                print(f"      ... ещё {len(items) - 5}")
    
    # INT вызовы (CD xx)
    int_calls = {}
    for i in range(header_size, len(data) - 1):
        if data[i] == 0xCD:
            int_num = data[i+1]
            if int_num not in int_calls:
                int_calls[int_num] = []
            int_calls[int_num].append(i)
    
    if int_calls:
        print(f"\n  INT вызовы (прерывания):")
        int_names = {
            0x10: "BIOS Video",
            0x13: "BIOS Disk",
            0x16: "BIOS Keyboard",
            0x1A: "BIOS Timer",
            0x21: "DOS",
            0x33: "Mouse",
            0x2F: "Multiplex",
            0x67: "EMS",
        }
        for int_num in sorted(int_calls.keys()):
            name = int_names.get(int_num, "")
            count = len(int_calls[int_num])
            print(f"    INT 0x{int_num:02X} ({name}): {count} вызовов")

def disassemble_entry(data, header_size, init_cs, init_ip):
    """Дизассемблируем от точки входа"""
    try:
        from capstone import Cs, CS_ARCH_X86, CS_MODE_16
    except ImportError:
        print("\n  [!] capstone не установлен, пропуск дизассемблирования")
        return
    
    print("\n" + "=" * 70)
    print("  DISASSEMBLY (от точки входа)")
    print("=" * 70)
    
    entry_offset = header_size + init_cs * 16 + init_ip
    print(f"  Entry point: file offset 0x{entry_offset:X}, CS:IP = {init_cs:04X}:{init_ip:04X}\n")
    
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    
    # Дизассемблируем первые 500 байт от точки входа
    code = data[entry_offset:entry_offset + 500]
    
    print(f"  --- Entry point (первые инструкции) ---")
    count = 0
    for insn in md.disasm(code, init_ip):
        hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
        print(f"  {init_cs:04X}:{insn.address:04X}  {hex_bytes:<20s}  {insn.mnemonic:<8s} {insn.op_str}")
        count += 1
        if count >= 100:
            break
    
    # Также дизассемблируем несколько ключевых участков
    # Ищем вызовы CALL FAR (9A xx xx xx xx) в начале для определения основных функций
    print(f"\n  --- Поиск FAR CALL'ов в первых 2KB кода ---")
    scan_size = min(2048, len(data) - entry_offset)
    scan_code = data[entry_offset:entry_offset + scan_size]
    
    far_calls = []
    for i in range(len(scan_code) - 4):
        if scan_code[i] == 0x9A:  # CALL FAR
            off = struct.unpack_from("<H", scan_code, i + 1)[0]
            seg = struct.unpack_from("<H", scan_code, i + 3)[0]
            far_calls.append((entry_offset + i, seg, off))
    
    for file_off, seg, off in far_calls[:30]:
        target_file_off = header_size + seg * 16 + off
        if 0 <= target_file_off < len(data):
            # Дизассемблируем первые несколько инструкций цели
            target_code = data[target_file_off:target_file_off + 30]
            instrs = list(md.disasm(target_code, off))
            if instrs:
                first_instrs = '; '.join(f"{x.mnemonic} {x.op_str}" for x in instrs[:4])
                print(f"    0x{file_off:05X}: CALL FAR {seg:04X}:{off:04X} -> {first_instrs}")
        
def disassemble_full(data, header_size, exe_size):
    """Полная дизассемблировка кода программы"""
    try:
        from capstone import Cs, CS_ARCH_X86, CS_MODE_16
    except ImportError:
        return
    
    print("\n" + "=" * 70)
    print("  FULL DISASSEMBLY (в файл proj5_disasm.asm)")
    print("=" * 70)
    
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    
    code_data = data[header_size:exe_size]
    
    line_count = 0
    with open("proj5_disasm.asm", "w", encoding="utf-8") as f:
        f.write("; PROJ5.EXE Disassembly\n")
        f.write(f"; File size: {len(data)} bytes\n")
        f.write(f"; Code starts at file offset: 0x{header_size:X}\n")
        f.write(f"; Code size: {len(code_data)} bytes\n\n")
        
        for insn in md.disasm(code_data, 0):
            hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
            line = f"{insn.address:08X}  {hex_bytes:<24s}  {insn.mnemonic:<8s} {insn.op_str}\n"
            f.write(line)
            line_count += 1
    
    print(f"  Записано {line_count} инструкций в proj5_disasm.asm")

def main():
    data = read_exe()
    
    header_size, init_cs, init_ip, exe_size = parse_mz_header(data)
    extract_strings(data, min_len=4)
    find_code_patterns(data, header_size)
    disassemble_entry(data, header_size, init_cs, init_ip)
    disassemble_full(data, header_size, exe_size)
    
    print("\n" + "=" * 70)
    print("  ГОТОВО")
    print("=" * 70)

if __name__ == "__main__":
    main()
