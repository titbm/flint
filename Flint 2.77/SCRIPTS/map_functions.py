"""
Детальное сопоставление функций PIC.CPP v2.61 → PROJ5.EXE v2.77
Разбиваем большой блок #6 (code 0x115C2-0x12200) на отдельные функции,
сопоставляя каждую с исходным кодом PIC.CPP по паттернам портов.
"""
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_16

EXE_PATH = "PROJ5.EXE"
HEADER_SIZE = 7680  # 480 paragraphs * 16

# Порты платы
PORT_NAMES = {
    0x300: "PT0.ch0(K2x)", 0x301: "PT0.ch1(dX)", 0x302: "PT0.ch2(K2z)", 0x303: "PT0.ctrl",
    0x304: "PT1.ch0(K2y)", 0x305: "PT1.ch1(dY)", 0x306: "PT1.ch2(dZ)", 0x307: "PT1.ctrl",
    0x308: "PPI.PA(K1)", 0x309: "PPI.PB(endSens)", 0x30A: "PPI.PC(ctl)", 0x30B: "PPI.ctrl",
    0x30C: "RG(dir/en)", 0x30D: "?", 0x30E: "?", 0x30F: "?",
    0x310: "PPI2.PA(sens)", 0x311: "PPI2.PB(EM1-8)", 0x312: "PPI2.PC(EM9/10)",
    0x313: "PPI2.ctrl", 0x314: "PT2.ch0(LasFrq)", 0x315: "PT2.ch1(EOShDly)",
    0x316: "PT2.ch2", 0x317: "PT2.ctrl",
    0x318: "CMOS.reset", 0x319: "CMOS.incr", 0x31A: "CMOS.low", 0x31B: "CMOS.high",
    0x31C: "LRG(LaserCtl)"
}

# Характерные значения для идентификации функций
PIC_SIGNATURES = {
    "pi_ini": {
        "desc": "Инициализация аппаратуры",
        "key_values": [0x82, 0x96, 0xFD, 0xFF, 0xFC, 0x91, 0x34, 0x78, 0xB4, 0xB8, 0x7A],
        "key_ports": [0x30B, 0x308, 0x30A, 0x313, 0x311, 0x303, 0x307, 0x317],
        "src_lines": "142-162"
    },
    "lpuls": {
        "desc": "Лазерный импульс + проверка датчиков",
        "key_values": [0xBF, 0x40],  # PULS_ON, PULS_OFF
        "key_ports": [0x30A, 0x310, 0x312],
        "src_lines": "165-200"
    },
    "sh_open": {
        "desc": "Открытие электромеханических затворов",
        "key_values": [0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D],
        "key_ports": [0x311, 0x313],
        "src_lines": "203-211"
    },
    "sh_close": {
        "desc": "Закрытие всех затворов",
        "key_values": [0xFF, 0x09, 0x0B, 0x0D],
        "key_ports": [0x311, 0x313],
        "src_lines": "214-217"
    },
    "process": {
        "desc": "Главный цикл обработки",
        "key_values": [0x7F, 0x80],  # PR_OPEN, PR_CLOSE
        "key_ports": [0x30A, 0x319],  # PPI.PC + CMOS.incr
        "src_lines": "220-271"
    },
    "move_sen": {
        "desc": "Движение к концевым датчикам (homing)",
        "key_values": [0x64, 0x70, 0x40, 0xC8],  # K2=100, dX=0x7000, dZ=0x4000, K2=200
        "key_ports": [0x300, 0x301, 0x304, 0x305, 0x302, 0x306, 0x30C, 0x309],
        "src_lines": "274-319"
    },
    "move": {
        "desc": "Перемещение по 3 осям (X,Y,Z)",
        "key_values": [0xC8],  # K2=200 в откате
        "key_ports": [0x300, 0x301, 0x304, 0x305, 0x302, 0x306, 0x30C, 0x309],
        "src_lines": "322-421"
    }
}

def load_exe():
    with open(EXE_PATH, "rb") as f:
        return f.read()

def file_to_code(file_offset):
    return file_offset - HEADER_SIZE

def code_to_file(code_offset):
    return code_offset + HEADER_SIZE

def disassemble_range(data, code_start, code_end):
    """Дизассемблируем диапазон кода"""
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = True
    file_start = code_to_file(code_start)
    file_end = code_to_file(code_end)
    code_bytes = data[file_start:file_end]
    return list(md.disasm(code_bytes, code_start))

def find_function_boundaries(instructions):
    """Находим границы функций по PUSH BP; MOV BP,SP и RETF/RET"""
    functions = []
    current_func_start = None
    
    for i, insn in enumerate(instructions):
        # Ищем пролог: PUSH BP / MOV BP,SP  или  ENTER
        if insn.mnemonic == 'push' and insn.op_str == 'bp':
            # Проверяем следующую инструкцию: MOV BP, SP
            if i + 1 < len(instructions):
                next_insn = instructions[i + 1]
                if next_insn.mnemonic == 'mov' and next_insn.op_str == 'bp, sp':
                    if current_func_start is not None:
                        # Сохраняем предыдущую функцию
                        functions.append((current_func_start, insn.address - 1))
                    current_func_start = insn.address
        elif insn.mnemonic == 'enter':
            if current_func_start is not None:
                functions.append((current_func_start, insn.address - 1))
            current_func_start = insn.address
    
    # Закрываем последнюю функцию
    if current_func_start is not None:
        functions.append((current_func_start, instructions[-1].address + instructions[-1].size))
    
    return functions

def analyze_function_ports(data, instructions, func_start, func_end):
    """Анализируем порты в функции"""
    ports = []
    port_values = []  # (port, value, 'in'/'out')
    imm_values = []
    
    for i, insn in enumerate(instructions):
        if insn.address < func_start or insn.address > func_end:
            continue
        
        # MOV DX, imm16 (BA xx xx)
        if insn.mnemonic == 'mov' and insn.op_str.startswith('dx, 0x'):
            try:
                val = int(insn.op_str.split('0x')[1], 16)
                if 0x300 <= val <= 0x31C:
                    ports.append(val)
                    # Смотрим дальше: OUT DX, AL или IN AL, DX
                    for j in range(i+1, min(i+4, len(instructions))):
                        nxt = instructions[j]
                        if nxt.address > func_end:
                            break
                        if nxt.mnemonic == 'out' and 'dx' in nxt.op_str:
                            # Ищем значение в AL перед OUT
                            for k in range(j-1, max(j-4, i), -1):
                                prev = instructions[k]
                                if prev.mnemonic == 'mov' and prev.op_str.startswith('al, 0x'):
                                    pval = int(prev.op_str.split('0x')[1], 16)
                                    port_values.append((val, pval, 'out'))
                                    break
                                elif prev.mnemonic == 'mov' and prev.op_str.startswith('al,'):
                                    port_values.append((val, None, 'out'))
                                    break
                            break
                        elif nxt.mnemonic == 'in' and 'dx' in nxt.op_str:
                            port_values.append((val, None, 'in'))
                            break
            except:
                pass
        
        # Запоминаем все непосредственные значения MOV AL, imm8
        if insn.mnemonic == 'mov' and insn.op_str.startswith('al, 0x'):
            try:
                val = int(insn.op_str.split('0x')[1], 16)
                imm_values.append(val)
            except:
                pass
        
        # AND AL, imm8  / OR AL, imm8
        if insn.mnemonic in ('and', 'or') and insn.op_str.startswith('al, 0x'):
            try:
                val = int(insn.op_str.split('0x')[1], 16)
                imm_values.append(val)
            except:
                pass
    
    return ports, port_values, imm_values

def identify_function(ports, port_values, imm_values, func_size):
    """Определяем какая функция PIC.CPP это может быть"""
    port_set = set(ports)
    val_set = set(imm_values)
    
    scores = {}
    
    # pi_ini: много потов подряд, значения 0x82, 0x96, 0x91, 0x34, 0x78
    if {0x30B, 0x303, 0x307, 0x317} <= port_set and 0x82 in val_set:
        scores["pi_ini"] = 100
    
    # sh_open: PPI2.PB + PPI2.ctrl, значения 0x08/0x09/0x0A/0x0B/0x0C/0x0D
    if 0x311 in port_set and 0x313 in port_set:
        if {0x08, 0x0C, 0x0D} & val_set:
            scores["sh_open"] = 80
        if val_set >= {0x09, 0x0B, 0x0D} and 0x08 not in val_set:
            scores["sh_close"] = 90
    
    # lpuls: PPI.PC с PULS_ON(0xBF) AND / PULS_OFF(0x40) OR + PPI2.PA(0x310)
    if 0x30A in port_set and (0xBF in val_set or 0x40 in val_set):
        if 0x310 in port_set or 0x312 in port_set:
            scores["lpuls"] = 85
        else:
            scores["lpuls"] = 60
    
    # process: PPI.PC + CMOS.incr(0x319) + PR_OPEN(0x7F)/PR_CLOSE(0x80)
    if 0x319 in port_set and 0x30A in port_set:
        scores["process"] = 90
    
    # move_sen: PT0/PT1 каналы + RG + endSens, значения 0x64, 0x70
    if {0x300, 0x301, 0x304, 0x305, 0x302, 0x306} <= port_set:
        if 0x64 in val_set and 0x70 in val_set:
            scores["move_sen"] = 95
        elif 0xC8 in val_set:
            scores["move_sen/move"] = 70
    
    # move: PT0/PT1 + RG + endSens, но без фиксированных K2
    if {0x300, 0x301, 0x30C, 0x309} <= port_set:
        if 0x64 not in val_set and 0x70 not in val_set:
            scores["move"] = 75
    
    # Функция с PT2 — новая в v2.77 (лазерный таймер)
    if 0x314 in port_set or 0x315 in port_set:
        if "pi_ini" not in scores:
            scores["laser_timer_v277"] = 70
    
    # Функция с LRG — новая в v2.77
    if 0x31C in port_set and len(port_set) <= 3:
        scores["lrg_control_v277"] = 60
    
    # CMOS без process
    if (0x318 in port_set or 0x31A in port_set or 0x31B in port_set) and 0x319 not in port_set:
        scores["cmos_counter_v277"] = 65
    
    return scores

def main():
    data = load_exe()
    
    # Расширенный диапазон для поиска — весь блок #6 плюс окрестности
    CODE_START = 0x115B0  # Немного до начала pi_ini
    CODE_END   = 0x12200  # С запасом после последнего порта
    
    print("=" * 80)
    print("  КАРТА ФУНКЦИЙ PIC.CPP В PROJ5.EXE v2.77")
    print("=" * 80)
    
    instructions = disassemble_range(data, CODE_START, CODE_END)
    
    # Находим границы функций
    func_boundaries = find_function_boundaries(instructions)
    
    print(f"\n  Найдено {len(func_boundaries)} функций в диапазоне code {CODE_START:#07x}—{CODE_END:#07x}:\n")
    
    for idx, (fstart, fend) in enumerate(func_boundaries):
        fsize = fend - fstart
        ports, port_values, imm_values = analyze_function_ports(data, instructions, fstart, fend)
        identification = identify_function(ports, port_values, imm_values, fsize)
        
        # Определяем лучшее совпадение
        if identification:
            best = max(identification, key=identification.get)
            score = identification[best]
        else:
            best = "???"
            score = 0
        
        unique_ports = []
        seen = set()
        for p in ports:
            if p not in seen:
                unique_ports.append(p)
                seen.add(p)
        
        port_names_str = ", ".join(f"{PORT_NAMES.get(p, f'0x{p:03X}')}" for p in unique_ports)
        
        # Выводим информацию
        print(f"  ═══ Функция #{idx+1}: code {fstart:#07x}—{fend:#07x} ({fsize} байт) ═══")
        if best in PIC_SIGNATURES:
            sig = PIC_SIGNATURES[best]
            print(f"    → {best}() [{score}%] — {sig['desc']}")
            print(f"    → PIC.CPP строки {sig['src_lines']}")
        elif best != "???":
            print(f"    → {best} [{score}%]")
        else:
            print(f"    → Не идентифицирована")
        
        if ports:
            print(f"    Порты ({len(ports)} обращений): {port_names_str}")
        else:
            print(f"    Порты: нет прямых обращений к плате")
        
        # Детали портов OUT
        if port_values:
            for prt, val, direction in port_values[:12]:
                pname = PORT_NAMES.get(prt, f"0x{prt:03X}")
                if val is not None:
                    print(f"      {direction.upper():3s} {pname} ← 0x{val:02X}")
                else:
                    print(f"      {direction.upper():3s} {pname} ← (вычисляемое)")
        
        print()
    
    # ==========================================
    # Теперь анализируем другие блоки (1-5)
    # ==========================================
    print("\n" + "=" * 80)
    print("  ПРОЧИЕ БЛОКИ С ОБРАЩЕНИЯМИ К ПОРТАМ ПЛАТЫ")
    print("=" * 80)
    
    other_blocks = [
        (0x09630, 0x09650, "Блок #1: LRG"),
        (0x0A270, 0x0A560, "Блок #2: PPI.PC ×6"),
        (0x0A950, 0x0A9C0, "Блок #3: PPI.PC ×4 + LRG"),
        (0x0CCD0, 0x0CD30, "Блок #4: PPI.PC ×4"),
        (0x0D3B0, 0x0D500, "Блок #5: CMOS + PPI.PC"),
    ]
    
    for bstart, bend, name in other_blocks:
        insns = disassemble_range(data, bstart, bend)
        ports, port_values, imm_values = analyze_function_ports(data, insns, bstart, bend)
        identification = identify_function(ports, port_values, imm_values, bend-bstart)
        
        if identification:
            best = max(identification, key=identification.get)
            score = identification[best]
        else:
            best = "???"
            score = 0
        
        unique_ports = []
        seen = set()
        for p in ports:
            if p not in seen:
                unique_ports.append(p)
                seen.add(p)
        
        port_names_str = ", ".join(f"{PORT_NAMES.get(p, f'0x{p:03X}')}" for p in unique_ports)
        
        print(f"\n  ═══ {name} (code {bstart:#07x}—{bend:#07x}) ═══")
        if best in PIC_SIGNATURES:
            sig = PIC_SIGNATURES[best]
            print(f"    → Похоже на {best}() [{score}%] — {sig['desc']}")
        elif best != "???":
            print(f"    → {best} [{score}%]")
        else:
            print(f"    → Не соответствует PIC.CPP")
        
        if ports:
            print(f"    Порты: {port_names_str}")
        if port_values:
            for prt, val, direction in port_values[:8]:
                pname = PORT_NAMES.get(prt, f"0x{prt:03X}")
                if val is not None:
                    print(f"      {direction.upper():3s} {pname} ← 0x{val:02X}")
                else:
                    print(f"      {direction.upper():3s} {pname} ← (вычисляемое)")
    
    # ==========================================
    # Детальный дизасм pi_ini() vs исходник
    # ==========================================
    print("\n\n" + "=" * 80)
    print("  ДЕТАЛЬНОЕ СРАВНЕНИЕ: pi_ini() — ИСХОДНИК vs БИНАРНИК")
    print("=" * 80)
    
    # pi_ini начинается с code 0x115C2
    pi_ini_code_start = 0x115C2
    pi_ini_code_end = 0x11670  # Приблизительно до RETF после проверки K1
    
    pi_ini_insns = disassemble_range(data, pi_ini_code_start, pi_ini_code_end)
    
    src_lines = [
        ("ctlw = (XUP|YUP|ZUP)&XOFF&YOFF&ZOFF&OSCON = 0x07", None),
        ("outportb(ADRRG, ctlw)", "0x30C ← 0x07"),
        ("LCtl=0; outportb(LRG, LCtl)", "0x31C ← 0x00"),
        ("outportb(ADRPPI+3, 0x82)  // PPI mode", "0x30B ← 0x82"),
        ("outportb(ADRPPI, 150)    // K1=150", "0x308 ← 0x96"),
        ("outportb(ADRPPI+2, 0xFD) // stepM-off", "0x30A ← 0xFD"),
        ("outportb(ADRPPI+2, 0xFF) // endS-reset", "0x30A ← 0xFF"),
        ("outportb(ADRPPI+2, 0xFC) // stepM-on", "0x30A ← 0xFC"),
        ("outportb(ADRPPI2+3, 0x91) // PPI2 mode", "0x313 ← 0x91"),
        ("outportb(ADRPPI2+1, 0xFF) // EM1-8 закр.", "0x311 ← 0xFF"),
        ("outportb(ADRPPI2+3, 0x09) // PC4=1: EM9", "0x313 ← 0x09"),
        ("outportb(ADRPPI2+3, 0x0B) // PC5=1: EM10", "0x313 ← 0x0B"),
        ("outportb(ADRPPI2+3, 0x0D) // PC6=1: EMCOM", "0x313 ← 0x0D"),
        ("outportb(ADRPT0+3, 0x34)  // PT0.ch0 mode2", "0x303 ← 0x34"),
        ("outportb(ADRPT0+3, 0x78)  // PT0.ch1 mode4", "0x303 ← 0x78"),
        ("outportb(ADRPT0+3, 0xB4)  // PT0.ch2 mode2", "0x303 ← 0xB4"),
        ("outportb(ADRPT1+3, 0x34)  // PT1.ch0 mode2", "0x307 ← 0x34"),
        ("outportb(ADRPT1+3, 0x78)  // PT1.ch1 mode4", "0x307 ← 0x78"),
        ("outportb(ADRPT1+3, 0xB8)  // PT1.ch2 mode4", "0x307 ← 0xB8"),
        ("outportb(ADRPT2+3, 0x34)  // PT2.ch0 mode2 [v2.71+]", "0x317 ← 0x34"),
        ("outportb(ADRPT2+3, 0x7A)  // PT2.ch1 mode5 [v2.71+]", "0x317 ← 0x7A"),
        ("outportb(ADRPT2+3, 0xB8)  // PT2.ch2 mode4 [v2.71+]", "0x317 ← 0xB8"),
        ("sh_open(glpos9) — вызов [v2.77 добавлено]", "CALL sh_open"),
        ("inportb(ADRPPI) != 150 → return 0", "0x308 → CMP 0x96"),
    ]
    
    print("\n  Исходный код (PIC.CPP)                    │  Бинарник (PROJ5.EXE)")
    print("  " + "─" * 44 + "┼" + "─" * 35)
    
    # Сопоставляем OUT-инструкции  
    out_idx = 0
    for insn in pi_ini_insns:
        if insn.mnemonic == 'mov' and insn.op_str.startswith('dx, 0x3'):
            port = int(insn.op_str.split('0x')[1], 16)
            if 0x300 <= port <= 0x31C and out_idx < len(src_lines):
                src_text, expected = src_lines[out_idx]
                binary_text = f"code {insn.address:#07x}: MOV DX, 0x{port:03X}"
                print(f"  {src_text:<44s}│  {binary_text}")
                out_idx += 1
    
    # ==========================================
    # Итоговая таблица
    # ==========================================
    print("\n\n" + "=" * 80)
    print("  ИТОГОВАЯ ТАБЛИЦА СООТВЕТСТВИЙ")
    print("=" * 80)
    print(f"""
  ┌─────────────┬──────────────┬──────────┬─────────────────────────────────────┐
  │ Функция     │ Code offset  │ File off │ Примечания                          │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ pi_ini()    │ 0x115C2      │ 0x133C2  │ Инициализация + PT2 (v2.71+)       │
  │ (v2.77)     │   — 0x11668  │  0x13468 │ + LRG, sh_open() в конце           │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ lpuls()     │ ≈0x11715     │ ≈0x13515 │ Деструкция: PPI2.PA + PPI2.PC      │
  │ (v2.77)     │   — ≈0x118A5 │  ≈0x136A5│ + PT2 laser timer, shutter delay   │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ sh_open()   │ ≈0x117AB     │ ≈0x135AB │ PPI2.PB + PPI2.ctrl                │
  │             │   — ≈0x11870 │  ≈0x13670│ + EMCOM delay                      │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ sh_close()  │ ≈0x11870     │ ≈0x13670 │ PPI2.PB=0xFF, PC4,5,6=1            │
  │             │   — ≈0x118A5 │  ≈0x136A5│                                    │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ process()   │ ≈0x118A5     │ ≈0x136A5 │ PPI.PC + CMOS.incr + PR_OPEN/CLOSE │
  │ (v2.77)     │   — ≈0x11B80 │  ≈0x13980│ Самая большая функция              │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ move_sen()  │ ≈0x11B80     │ ≈0x13980 │ PT0+PT1 channels + RG + endSens    │
  │             │   — ≈0x11CE0 │  ≈0x13AE0│ 2 фазы: к датчикам + откат         │
  ├─────────────┼──────────────┼──────────┼─────────────────────────────────────┤
  │ move()      │ ≈0x11CE0     │ ≈0x13AE0 │ PT0+PT1 + RG + endSens + задержка  │
  │ (v2.77)     │   — ≈0x12140 │  ≈0x13F40│ + dT коррекция (v2.73+)            │
  └─────────────┴──────────────┴──────────┴─────────────────────────────────────┘

  Другие блоки с портами платы (вне PIC.CPP):
  ┌─────────────┬──────────────┬──────────┬─────────────────────────────────────┐
  │ Блок #1     │ 0x0963A      │ 0x0B43A  │ Одноразовая запись LRG              │
  │ Блок #2     │ 0x0A271      │ 0x0C071  │ UI-функция с PPI.PC ×6             │
  │ Блок #3     │ 0x0A961      │ 0x0C761  │ PPI.PC ×4 + LRG                    │
  │ Блок #4     │ 0x0CCD9      │ 0x0EAD9  │ Управление шагом + вызов sh_open   │
  │ Блок #5     │ 0x0D3C0      │ 0x0F1C0  │ CMOS counter read/reset            │
  └─────────────┴──────────────┴──────────┴─────────────────────────────────────┘
""")
    
    # Проверяем конкретные точки: находим вызовы CALL/LCALL в блоке
    print("\n" + "=" * 80)
    print("  АНАЛИЗ ВЫЗОВОВ CALL/LCALL В БЛОКЕ pi_ini() + ОКРЕСТНОСТИ")
    print("=" * 80)
    
    full_insns = disassemble_range(data, 0x115B0, 0x12200)
    
    # Ищем RETF и CALL
    retf_addrs = []
    call_targets = []
    func_starts = []
    
    for i, insn in enumerate(full_insns):
        if insn.mnemonic in ('retf', 'ret'):
            retf_addrs.append(insn.address)
        if insn.mnemonic in ('call', 'lcall'):
            call_targets.append((insn.address, insn.op_str))
        if insn.mnemonic == 'push' and insn.op_str == 'bp':
            if i + 1 < len(full_insns) and full_insns[i+1].mnemonic == 'mov' and full_insns[i+1].op_str == 'bp, sp':
                func_starts.append(insn.address)
    
    print(f"\n  Границы функций (PUSH BP; MOV BP,SP): {len(func_starts)}")
    for addr in func_starts:
        print(f"    code {addr:#07x} (file {code_to_file(addr):#07x})")
    
    print(f"\n  Возвраты (RETF/RET): {len(retf_addrs)}")
    for addr in retf_addrs:
        print(f"    code {addr:#07x}")
    
    print(f"\n  Вызовы (CALL/LCALL): {len(call_targets)}")
    for addr, target in call_targets:
        print(f"    code {addr:#07x}: {target}")

if __name__ == "__main__":
    main()
