#!/usr/bin/env python3
"""
Сопоставление функций из PIC.CPP (ver 2.61) с кодом в PROJ5.EXE (ver 2.77)

Стратегия поиска:
- Каждая функция в PIC.CPP использует специфические порты в определённом порядке
- Ищем эти характерные паттерны последовательностей outportb/inportb в бинарнике
- Базовый адрес платы: ADRPT0 = 0x300 (из исходника)

Карта портов платы:
  0x300..0x303 = PT0  (ch0: K2x, ch1: Xdist, ch2: K2z, ctrl)
  0x304..0x307 = PT1  (ch0: K2y, ch1: Ydist, ch2: Zdist, ctrl)
  0x308..0x30B = PPI  (PA: K1, PB: endSensors, PC: control, ctrl)
  0x30C        = RG   (direction/enable register)
  0x310..0x313 = PPI2 (PA+PC0-3: sensors, PB+PC4-7: shutters, ctrl)
  0x314..0x317 = PT2  (ch0: LaserFreq, ch1: EOShutter, ch2: GlobalDelay, ctrl)
  0x318..0x31B = CMOS (reset, increment, low read, high read)
  0x31C        = LRG  (laser control: D0=Pump, D1=EOShutter)
"""
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_16

EXE_PATH = "PROJ5.EXE"

# Порты платы (из #define в PIC.CPP)
PORT_NAMES = {
    0x300: "PT0.ch0 (K2x/LaserFreq)", 0x301: "PT0.ch1 (Xdist)",
    0x302: "PT0.ch2 (K2z)", 0x303: "PT0.ctrl",
    0x304: "PT1.ch0 (K2y)", 0x305: "PT1.ch1 (Ydist)",
    0x306: "PT1.ch2 (Zdist)", 0x307: "PT1.ctrl",
    0x308: "PPI.PA (K1)", 0x309: "PPI.PB (endSensors)",
    0x30A: "PPI.PC (control)", 0x30B: "PPI.ctrl",
    0x30C: "RG (dir/enable)", 0x30D: "RG+1",
    0x310: "PPI2.PA (sens1-8)", 0x311: "PPI2.PB (EM shutters)",
    0x312: "PPI2.PC (EM9/10/COM)", 0x313: "PPI2.ctrl",
    0x314: "PT2.ch0 (LaserFreq)", 0x315: "PT2.ch1 (EOShutter delay)",
    0x316: "PT2.ch2 (GlobalDelay)", 0x317: "PT2.ctrl",
    0x318: "CMOS.reset", 0x319: "CMOS.incr",
    0x31A: "CMOS.low", 0x31B: "CMOS.high",
    0x31C: "LRG (Laser Control)",
}

def read_exe():
    with open(EXE_PATH, "rb") as f:
        return f.read()

def find_port_io_dx(data, header_size, exe_size):
    """
    В 16-бит реальном режиме порты >= 0x100 адресуются через DX:
      OUT DX, AL  = 0xEE
      OUT DX, AX  = 0xEF
      IN  AL, DX  = 0xEC
      IN  AX, DX  = 0xED
    
    Нужно найти паттерны: 
      MOV DX, 0x300+N  (BA xx 03 или 66 BA xx 03 00 00)
      ... 
      OUT DX, AL / IN AL, DX
    """
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = False
    
    print("=" * 78)
    print("  ПОИСК ОБРАЩЕНИЙ К ПОРТАМ ПЛАТЫ (0x300-0x31C) ЧЕРЕЗ DX")
    print("=" * 78)
    
    # Ищем MOV DX, 0x3xx в коде
    board_refs = []
    code = data[header_size:exe_size]
    
    for i in range(len(code) - 2):
        # BA xx 03 = MOV DX, 0x03xx
        if code[i] == 0xBA and code[i+2] == 0x03:
            port = code[i+1] + 0x300
            if 0x300 <= port <= 0x31C:
                file_off = header_size + i
                board_refs.append((file_off, port, i))
    
    print(f"\n  Найдено {len(board_refs)} загрузок адреса порта платы в DX\n")
    
    # Группируем по близости (в пределах одной функции)
    if not board_refs:
        print("  НЕ НАЙДЕНО! Попробуем другой базовый адрес...")
        return []
    
    for file_off, port, code_off in board_refs:
        name = PORT_NAMES.get(port, f"0x{port:03X}")
        print(f"    0x{file_off:05X} (code 0x{code_off:05X}): MOV DX, 0x{port:03X}  ({name})")
    
    return board_refs

def find_port_io_imm(data, header_size, exe_size):
    """
    Однако возможно компилятор использует IN/OUT с immediate для портов < 256
    Или использует DX индексную адресацию.
    Также проверим: может базовый адрес другой (не 0x300)?
    """
    print("\n" + "=" * 78)
    print("  ПОИСК АЛЬТЕРНАТИВНЫХ БАЗОВЫХ АДРЕСОВ ПЛАТЫ")
    print("=" * 78)
    
    code = data[header_size:exe_size]
    
    # Ищем паттерн: MOV DX, 0xNNN где N в диапазоне 0x200-0x3FF (типичные ISA-адреса)
    base_candidates = {}
    for i in range(len(code) - 2):
        if code[i] == 0xBA:
            port = struct.unpack_from("<H", code, i+1)[0]
            if 0x200 <= port <= 0x3FF:
                if port not in base_candidates:
                    base_candidates[port] = []
                base_candidates[port].append(header_size + i)
    
    # Показываем группы портов
    if base_candidates:
        # Ищем группы смежных портов (базовый адрес + смещения)
        port_list = sorted(base_candidates.keys())
        print(f"\n  Порты в диапазоне 0x200-0x3FF, загружаемые в DX:")
        for port in port_list:
            refs = base_candidates[port]
            name = PORT_NAMES.get(port, "")
            print(f"    0x{port:03X}: {len(refs):3d} раз  {name}")
    
    # Проверим также: может базовый адрес грузится в переменную, а затем прибавляются смещения?
    # Ищем характерные константы из pi_ini():
    # 0x82 (PPI mode), 150=0x96 (K1), 0xfd, 0xff, 0xfc, 0x91, 0x34, 0x78, 0xb4, 0xb8, 0x7a
    
    return base_candidates

def search_pi_ini(data, header_size, exe_size):
    """
    Ищем функцию pi_ini() по характерной последовательности:
    1. outportb(ADRPPI+3, 0x82)  — PPI mode: mode0, PA-out, PB-inp, PC-out
    2. outportb(ADRPPI, 150)     — K1=150
    3. outportb(ADRPPI+2, 0xfd)  — stepM-off, endS-enable
    4. outportb(ADRPPI+2, 0xff)  — endS-reset
    5. outportb(ADRPPI+2, 0xfc)  — stepM-on, endS-enable
    
    Паттерн: серия OUT с значениями 0x82, 0x96(=150), 0xfd, 0xff, 0xfc
    """
    print("\n" + "=" * 78)
    print("  ПОИСК ФУНКЦИИ pi_ini() ПО ПАТТЕРНАМ")
    print("=" * 78)
    
    code = data[header_size:exe_size]
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = False
    
    # Ищем значение 0x82 (PPI mode word) рядом с 150 (K1=150, 0x96)
    # В asm это будет что-то вроде:
    #   MOV AL, 0x82 / OUT DX, AL
    #   MOV AL, 0x96 / OUT DX, AL
    
    # Ищем байт 0x96 (=150) рядом с 0x82 в пределах 50 байт
    candidates = []
    for i in range(len(code) - 50):
        if code[i] == 0x82:
            # Проверяем: есть ли 0x96 (150) в следующих 30 байтах?
            window = code[i:i+50]
            if 0x96 in window:
                j = window.index(0x96)
                # И далее 0xfd, 0xff, 0xfc?
                window2 = code[i:i+100]
                if 0xfd in window2 and 0xff in window2 and 0xfc in window2:
                    candidates.append(header_size + i)
    
    print(f"\n  Кандидаты (0x82 + 0x96 + 0xfd/0xff/0xfc в пределах 100 байт): {len(candidates)}")
    
    # Для каждого кандидата — дизассемблируем контекст
    shown = set()
    for cand in candidates[:20]:
        # Ищем начало функции (push bp; mov bp, sp) ДО этой позиции
        func_start = None
        for back in range(min(200, cand - header_size)):
            off = cand - back - header_size
            if off >= 0 and code[off] == 0x55 and off+2 < len(code) and code[off+1] == 0x8B and code[off+2] == 0xEC:
                func_start = header_size + off
                break
            # enter
            if off >= 0 and code[off] == 0xC8:
                func_start = header_size + off
                break
        
        if func_start and func_start not in shown:
            shown.add(func_start)
            print(f"\n  Функция-кандидат @ 0x{func_start:05X}:")
            instrs = list(md.disasm(data[func_start:func_start+300], func_start - header_size))
            for insn in instrs[:60]:
                hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
                marker = "  "
                if insn.mnemonic in ('in', 'out'):
                    marker = ">>"
                elif 'dx' in insn.op_str and '0x3' in insn.op_str:
                    marker = "##"
                print(f"    {marker} {insn.address:05X}  {hex_bytes:<20s}  {insn.mnemonic:<7s} {insn.op_str}")

def search_by_port_sequence(data, header_size, exe_size):
    """
    Ищем характерные последовательности обращений к портам для каждой функции.
    Стратегия: ищем MOV DX, port_addr последовательности.
    
    pi_ini:
        Порты в порядке: ADRRG(30C), LRG(31C), PPI+3(30B), PPI(308), PPI+2(30A)×3,
                         PPI2+3(313), PPI2+1(311), PPI2+3(313)×3,
                         PT0+3(303)×2, PT1+3(307)×2, PT2+3(317)×2,
                         PPI(308), PPI+1(309)
    
    lpuls:
        Порты: PPI+2(30A), PPI2(310), PPI2+2(312)
    
    sh_open:
        Порты: PPI2+1(311), PPI2+3(313)×several
        
    process:
        Порты: PPI+2(30A), CMOS+1(319)
        
    move:
        Порты: PT0(300), PT0+1(301), PT1(304), PT1+1(305), PT0+2(302), PT1+2(306),
               ADRRG(30C), PPI+1(309)
    """
    print("\n" + "=" * 78)
    print("  ПОИСК ВСЕХ MOV DX, 0x3xx В КОДЕ")
    print("=" * 78)
    
    code = data[header_size:exe_size]
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = False
    
    # Собираем все MOV DX, 0x3xx с позициями
    dx_loads = []
    for i in range(len(code) - 2):
        if code[i] == 0xBA:
            val = struct.unpack_from("<H", code, i+1)[0]
            if 0x300 <= val <= 0x31F:
                dx_loads.append((i, val))
    
    if not dx_loads:
        # Может быть, адрес платы НЕ 0x300 в этой версии?
        # Попробуем все BA xx yy где yy = 02 или 03
        print("  Нет загрузок 0x300-0x31F. Ищем другие ISA-адреса...")
        for base_try in range(0x200, 0x400, 0x10):
            count = 0
            for i in range(len(code) - 2):
                if code[i] == 0xBA:
                    val = struct.unpack_from("<H", code, i+1)[0]
                    if base_try <= val < base_try + 0x20:
                        count += 1
            if count >= 10:
                print(f"    Базовый адрес 0x{base_try:03X}: {count} загрузок в DX")
    else:
        print(f"\n  Найдено {len(dx_loads)} загрузок портов 0x300-0x31F:")
        
        # Группируем по функциям (разрыв > 200 байт = другая функция)
        groups = []
        current_group = [dx_loads[0]]
        for i in range(1, len(dx_loads)):
            if dx_loads[i][0] - dx_loads[i-1][0] < 300:
                current_group.append(dx_loads[i])
            else:
                groups.append(current_group)
                current_group = [dx_loads[i]]
        groups.append(current_group)
        
        print(f"  Сгруппированы в {len(groups)} блоков:\n")
        
        for gi, group in enumerate(groups):
            ports_in_group = [PORT_NAMES.get(p, f"0x{p:03X}") for _, p in group]
            port_vals = [p for _, p in group]
            
            # Определяем какая функция из PIC.CPP
            func_guess = "?"
            pset = set(port_vals)
            if 0x30B in pset and 0x308 in pset and 0x303 in pset and 0x313 in pset:
                func_guess = "pi_ini()"
            elif 0x30A in pset and 0x310 in pset and len(group) < 15:
                func_guess = "lpuls()"
            elif 0x311 in pset and 0x313 in pset and 0x30A not in pset:
                func_guess = "sh_open() / sh_close()"
            elif 0x300 in pset and 0x304 in pset and 0x30C in pset and 0x309 in pset:
                func_guess = "move() / move_sen()"
            elif 0x319 in pset:
                func_guess = "process() (CMOS increment)"
            
            start_off = group[0][0]
            end_off = group[-1][0]
            
            # Ищем начало функции
            func_start = None
            for back in range(min(500, start_off)):
                off = start_off - back
                if off >= 0 and code[off] == 0x55 and off+2 < len(code) and code[off+1] == 0x8B and code[off+2] == 0xEC:
                    func_start = off
                    break
                if off >= 0 and code[off] == 0xC8:
                    func_start = off
                    break
            
            print(f"  ═══ Блок #{gi+1}: code {start_off:05X}-{end_off:05X}  ≈ {func_guess} ═══")
            if func_start:
                print(f"  Начало функции @ code 0x{func_start:05X} (file 0x{func_start+header_size:05X})")
            print(f"  Порты: {', '.join(f'0x{p:03X}' for p in port_vals)}")
            
            # Дизассемблируем
            if func_start:
                ds_start = func_start
                ds_end = min(end_off + 100, len(code))
                instrs = list(md.disasm(code[ds_start:ds_end], ds_start))
                
                for insn in instrs[:80]:
                    hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
                    marker = "  "
                    if insn.mnemonic in ('in', 'out'):
                        marker = ">>"
                    elif insn.mnemonic == 'mov' and 'dx' in insn.op_str and '0x3' in insn.op_str:
                        marker = "##"
                    elif insn.mnemonic in ('call', 'lcall'):
                        marker = "@@"
                    print(f"    {marker} {insn.address:05X}  {hex_bytes:<24s}  {insn.mnemonic:<7s} {insn.op_str}")
                if len(instrs) > 80:
                    print(f"    ... (ещё {len(instrs)-80} инструкций)")
            print()
    
    return dx_loads

def compare_versions(data, header_size):
    """Сравнение версий: какие изменения были с 2.61 до 2.77"""
    print("\n" + "=" * 78)
    print("  РАЗЛИЧИЯ МЕЖДУ PIC.CPP v2.61 И PROJ5.EXE v2.77")
    print("=" * 78)
    print("""
  Из changelog (FLINT.TXT):
  
  v2.70:  + Задержка gate (10-500 мкс, шаг 10 мкс) → новые порты PT2.ch1
  v2.71:  + Доп. таймер платы: ch0=pump, ch1=gate, ch2=free → порты PT2
          + Переключатели "Pump" и "Gate" в Configuration
          + LED-синхронизация через оптоволокно (DSUB-9)
  v2.72:  * Переделан формирование импульса лазера
          * Переделан расчёт скоростей в move() (фикс. период накачки)
  v2.73:  * Изменено управление лазером (pump+gate вместе, gate=10мкс)
          + Параметр dT для коррекции скоростей
  v2.74:  * Фикс зависания при выкл. накачке (ESC + gate_disable)
  v2.75:  * Управление затвором: разрешение за 40-150мкс до конца периода
  v2.77:  + Параметр shutter delay в cfg
          + LRG регистр: D0=Pump Enable, D1=EOShutter Enable
          * Переработана процедура импульса лазера и эл.мех.затворов
          + Индикатор Dr.check
  
  Новое в v2.77 по сравнению с v2.61:
  ─────────────────────────────────────
  1. Добавлен PT2 (порты 0x314-0x317) — управление лазерным таймером
  2. Добавлен LRG (порт 0x31C) — регистр управления лазером
  3. Изменён lpuls() — работа с задержкой gate через таймер
  4. Изменён move() — синхронизация с периодом накачки через таймер
  5. Добавлен CMOS счётчик (0x318-0x31B) — подсчёт импульсов
""")

def main():
    data = read_exe()
    header_size = struct.unpack_from("<H", data, 8)[0] * 16
    exe_size = len(data)
    
    board_refs = find_port_io_dx(data, header_size, exe_size)
    port_candidates = find_port_io_imm(data, header_size, exe_size)
    dx_loads = search_by_port_sequence(data, header_size, exe_size)
    
    if not dx_loads:
        search_pi_ini(data, header_size, exe_size)
    
    compare_versions(data, header_size)

if __name__ == "__main__":
    main()
