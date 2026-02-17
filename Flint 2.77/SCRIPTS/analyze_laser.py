#!/usr/bin/env python3
"""
Глубокий анализ управления лазером в PROJ5.EXE
Ищем код вокруг строк laser/pump/gate, анализируем PIT-таймер и порты управления
"""
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_16

EXE_PATH = "PROJ5.EXE"

def read_exe():
    with open(EXE_PATH, "rb") as f:
        return f.read()

def find_all_strings(data, min_len=4):
    """Найти все строки и их смещения"""
    strings = {}
    current = []
    start = 0
    for i, b in enumerate(data):
        if 0x20 <= b <= 0x7E:
            if not current:
                start = i
            current.append(chr(b))
        else:
            if len(current) >= min_len:
                strings[start] = ''.join(current)
            current = []
    return strings

def file_offset_to_seg_off(file_offset, header_size):
    """Конвертация файлового смещения в сегмент:смещение (приблизительно)"""
    linear = file_offset - header_size
    seg = linear >> 4
    off = linear & 0xF
    return seg, off

def find_references_to_offset(data, header_size, target_file_offset, code_start, code_end):
    """Ищем ссылки на данный адрес в коде (как загрузку адреса данных)"""
    # Для 16-бит кода ссылка на данные может быть как immediate в MOV, LEA, PUSH и т.д.
    # Целевой линейный адрес относительно начала сегмента данных
    target_linear = target_file_offset - header_size
    refs = []
    
    # Ищем 2-байтовые значения, которые могут быть смещениями на эту строку
    # В large model данные адресуются как seg:offset
    target_lo = target_linear & 0xFFFF
    
    for i in range(code_start, min(code_end, len(data) - 1)):
        val = struct.unpack_from("<H", data, i)[0]
        if val == target_lo:
            refs.append(i)
    
    return refs

def disasm_range(data, header_size, file_start, file_end, base_addr=0):
    """Дизассемблируем диапазон"""
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = False
    code = data[file_start:file_end]
    result = []
    for insn in md.disasm(code, base_addr):
        result.append(insn)
    return result

def disasm_around(data, header_size, file_offset, before=64, after=128):
    """Дизассемблируем код ВОКРУГ данного файлового смещения"""
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = False
    start = max(header_size, file_offset - before)
    end = min(len(data), file_offset + after)
    code = data[start:end]
    base = start - header_size
    result = []
    for insn in md.disasm(code, base):
        result.append((start + (insn.address - base), insn))
    return result

def analyze_cfg_files(data):
    """Анализируем ссылки на cfg файлы и параметры конфигурации"""
    print("=" * 78)
    print("  АНАЛИЗ КОНФИГУРАЦИИ ЛАЗЕРА (из flint1.cfg / flint9.cfg)")
    print("=" * 78)
    print("""
  Из документации (FLINT.TXT ver.2.77) формат cfg файлов:
    Поле  1: привязка по X (в 10 мкм)
    Поле  2: привязка по Y (в 10 мкм)
    Поле  3: привязка по Z (в 10 мкм)
    Поле  4: шаг набора привязки (в 10 мкм)
    Поле  5: ПЕРИОД ЛАЗЕРА (в мс) ← ключевой параметр
    Поле  6: ЗАДЕРЖКА ЗАТВОРА GATE (в 10 мкс) ← ключевой параметр
    Поле  7: макс. частота отработки шагов (в Гц)
    Поле  8: флаг постоянной/переменной скорости (1/0)
    Поле  9: поправка dT (в мс) для расчёта скоростей
    Поле 10: задержка срабатывания эл.мех.затворов (в мс)
    Поле 11: рабочие позиции (только flint9.cfg)
""")

def find_laser_strings(data, all_strings):
    """Найти все строки, связанные с лазером"""
    print("=" * 78)
    print("  СТРОКИ, СВЯЗАННЫЕ С ЛАЗЕРОМ")
    print("=" * 78)
    
    keywords = ['laser', 'pump', 'gate', 'las', 'period', 'delay', 
                'check', 'flash', 'timer', 'накач', 'затвор']
    
    laser_strings = {}
    for offset, s in all_strings.items():
        sl = s.lower()
        if any(k in sl for k in keywords):
            laser_strings[offset] = s
            print(f"  0x{offset:05X}: \"{s}\"")
    
    return laser_strings

def analyze_pit_timer(data, header_size):
    """Анализируем обращения к PIT (8254) - порты 0x40-0x43"""
    print("\n" + "=" * 78)
    print("  АНАЛИЗ PIT ТАЙМЕРА (8254) - порты 0x40-0x43")
    print("=" * 78)
    print("""
  PIT 8254 — Programmable Interval Timer:
    Port 0x40 = Channel 0 (генератор импульсов накачки по док.)
    Port 0x41 = Channel 1 (задержка затвора Gate по док.)
    Port 0x42 = Channel 2 (speaker / свободен)
    Port 0x43 = Control Word Register
""")
    
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    
    # Ищем все обращения к портам 0x40-0x43
    pit_accesses = []
    for i in range(header_size, len(data) - 1):
        if data[i] in (0xE4, 0xE5, 0xE6, 0xE7):  # IN/OUT imm8
            port = data[i+1]
            if 0x40 <= port <= 0x43:
                op = "IN " if data[i] in (0xE4, 0xE5) else "OUT"
                reg = "AL" if data[i] in (0xE4, 0xE6) else "AX"
                pit_accesses.append((i, port, op, reg))
    
    for file_off, port, op, reg in pit_accesses:
        ch_name = {0x40: "Ch0/Pump", 0x41: "Ch1/Gate", 0x42: "Ch2/Free", 0x43: "Control"}[port]
        print(f"\n  --- Port 0x{port:02X} ({ch_name}): {op} {reg} @ file offset 0x{file_off:05X} ---")
        
        # Дизассемблируем контекст
        instrs = disasm_around(data, header_size, file_off, before=48, after=48)
        for foff, insn in instrs:
            marker = " >>>" if foff == file_off else "    "
            hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
            print(f"  {marker} {insn.address:05X}  {hex_bytes:<20s}  {insn.mnemonic:<7s} {insn.op_str}")

def analyze_additional_timer(data, header_size):
    """
    Из документации: 'дополнительный таймер платы' - это НЕ стандартный PIT.
    Это таймер на плате управления. Ищем по паттернам обращений к нестандартным портам.
    """
    print("\n" + "=" * 78)
    print("  АНАЛИЗ ДОПОЛНИТЕЛЬНОГО ТАЙМЕРА ПЛАТЫ")
    print("=" * 78)
    print("""
  Из документации (ver.2.71):
    Канал 0 — генератор импульсов накачки
    Канал 1 — программируемая задержка затвора Gate
    Канал 2 — свободен (задержки в программе)
  
  Управление через нестандартные порты платы.
  Ищем блоки кода, содержащие последовательные OUT к одному и тому же порту...
""")

def find_flash_dat_code(data, header_size, all_strings):
    """Анализируем код работы с flash.dat (файл прошивки?)"""
    print("\n" + "=" * 78)
    print("  АНАЛИЗ КОДА РАБОТЫ С flash.dat")
    print("=" * 78)
    
    for offset, s in all_strings.items():
        if 'flash.dat' in s.lower():
            print(f"\n  Строка \"{s}\" @ 0x{offset:05X}")
            # Ищем ссылки на эту строку в коде
            # Строка в сегменте данных, её смещение относительно начала данных
            linear = offset - header_size
            print(f"  Линейный адрес: 0x{linear:05X}")

def analyze_check_laser(data, header_size, all_strings):
    """Анализируем функцию 'Check laser' — проверка пробоя"""
    print("\n" + "=" * 78)
    print("  АНАЛИЗ ФУНКЦИИ 'Check laser'")
    print("=" * 78)
    
    for offset, s in all_strings.items():
        if 'check laser' in s.lower():
            print(f"\n  Строка \"{s}\" @ 0x{offset:05X}")

def find_kpu_code(data, header_size, all_strings):
    """AKPU и KPU - контроллер позиционного управления?"""
    print("\n" + "=" * 78)
    print("  АНАЛИЗ КПУ (Контроллер Позиционного Управления)")
    print("=" * 78)
    
    for offset, s in all_strings.items():
        if 'kpu' in s.lower() or 'akpu' in s.lower():
            print(f"  Строка \"{s}\" @ 0x{offset:05X}")

def deep_disassembly_analysis(data, header_size, exe_size):
    """
    Полный анализ потока управления: находим все функции, 
    определяем какие обращаются к портам, строим граф вызовов
    """
    print("\n" + "=" * 78)
    print("  ГЛУБОКИЙ АНАЛИЗ: ФУНКЦИИ С ПОРТОВЫМ I/O")
    print("=" * 78)
    
    md = Cs(CS_ARCH_X86, CS_MODE_16)
    md.detail = False
    
    code_data = data[header_size:exe_size]
    
    # Находим все функции (начала PUSH BP / MOV BP,SP или ENTER)
    # И ищем среди них те, что обращаются к портам
    functions = []
    func_start = None
    
    # Ищем паттерны начала функций: 55 8B EC (push bp; mov bp, sp)
    # или C8 xx xx xx (enter)
    for i in range(len(code_data) - 2):
        # push bp; mov bp, sp
        if code_data[i] == 0x55 and code_data[i+1] == 0x8B and code_data[i+2] == 0xEC:
            functions.append(header_size + i)
        # enter
        elif code_data[i] == 0xC8:
            functions.append(header_size + i)
    
    functions.sort()
    
    print(f"  Найдено {len(functions)} предполагаемых функций\n")
    
    # Для каждой функции проверяем наличие обращений к портам
    port_functions = []
    
    for idx, func_off in enumerate(functions):
        # Определяем конец функции (до следующей функции, но не более 2KB)
        if idx + 1 < len(functions):
            func_end = min(functions[idx + 1], func_off + 2048)
        else:
            func_end = min(func_off + 2048, exe_size)
        
        func_code = data[func_off:func_end]
        
        # Ищем port I/O в этой функции
        ports_used = set()
        has_pit = False
        
        for j in range(len(func_code) - 1):
            if func_code[j] in (0xE4, 0xE5): # IN AL/AX, imm8
                port = func_code[j+1]
                ports_used.add(('IN', port))
                if 0x40 <= port <= 0x43: has_pit = True
            elif func_code[j] in (0xE6, 0xE7): # OUT imm8, AL/AX
                port = func_code[j+1]
                ports_used.add(('OUT', port))
                if 0x40 <= port <= 0x43: has_pit = True
        
        # Также ищем INT 21h вызовы для работы с файлами
        has_file_io = False
        for j in range(len(func_code) - 1):
            if func_code[j] == 0xCD and func_code[j+1] == 0x21:
                has_file_io = True
                break
        
        # Ищем строки внутри функции
        func_strings = []
        text = func_code.replace(b'\x00', b' ')
        ascii_text = ''.join(chr(b) if 0x20 <= b <= 0x7E else '.' for b in func_code)
        
        if ports_used:
            port_functions.append({
                'offset': func_off,
                'size': func_end - func_off,
                'ports': ports_used,
                'has_pit': has_pit,
                'has_file_io': has_file_io,
            })
    
    # Показываем функции с PIT-портами (связанные с таймером/лазером)
    print("  === ФУНКЦИИ, ОБРАЩАЮЩИЕСЯ К PIT (порты 0x40-0x43) ===\n")
    for f in port_functions:
        if f['has_pit']:
            pit_ports = [(op, p) for op, p in f['ports'] if 0x40 <= p <= 0x43]
            other_ports = [(op, p) for op, p in f['ports'] if not (0x40 <= p <= 0x43)]
            
            print(f"  Функция @ 0x{f['offset']:05X} (размер ~{f['size']} байт)")
            print(f"    PIT порты: {', '.join(f'{op} 0x{p:02X}' for op, p in sorted(pit_ports))}")
            if other_ports:
                print(f"    Другие порты: {', '.join(f'{op} 0x{p:02X}' for op, p in sorted(other_ports)[:10])}")
            
            # Дизассемблируем эту функцию
            instrs = list(md.disasm(data[f['offset']:f['offset']+f['size']], f['offset']-header_size))
            
            print(f"    Дизассемблирование:")
            for insn in instrs[:60]:
                hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
                # Отмечаем port I/O
                marker = "  "
                if insn.mnemonic in ('in', 'out'):
                    marker = ">>"
                elif insn.mnemonic == 'int':
                    marker = "!!"
                print(f"    {marker} {insn.address:05X}  {hex_bytes:<20s}  {insn.mnemonic:<7s} {insn.op_str}")
            if len(instrs) > 60:
                print(f"    ... (ещё {len(instrs)-60} инструкций)")
            print()
    
    # Ищем функции связанные с портом 0x61 (speaker) - используется для sound/beep
    print("\n  === ФУНКЦИЯ ЗВУКОВОГО ОПОВЕЩЕНИЯ (порт 0x61/0x42/0x43) ===\n")
    for f in port_functions:
        port_nums = set(p for _, p in f['ports'])
        if 0x61 in port_nums:
            print(f"  Функция @ 0x{f['offset']:05X}: порты {', '.join(f'{op} 0x{p:02X}' for op, p in sorted(f['ports']))}")
            instrs = list(md.disasm(data[f['offset']:f['offset']+min(f['size'], 300)], f['offset']-header_size))
            for insn in instrs[:40]:
                hex_bytes = ' '.join(f'{b:02X}' for b in insn.bytes)
                marker = ">>" if insn.mnemonic in ('in', 'out') else "  "
                print(f"    {marker} {insn.address:05X}  {hex_bytes:<20s}  {insn.mnemonic:<7s} {insn.op_str}")
            print()

    return port_functions

def analyze_board_ports(data, header_size, exe_size):
    """
    Анализируем обращения к нестандартным портам платы управления.
    Из документации: плата управления подключена через DSUB-9.
    Ищем порты, к которым идёт много обращений — это порты платы.
    """
    print("\n" + "=" * 78)
    print("  АНАЛИЗ ПОРТОВ ПЛАТЫ УПРАВЛЕНИЯ")
    print("=" * 78)
    
    # Собираем статистику по портам
    port_stats = {}
    for i in range(header_size, exe_size - 1):
        if data[i] in (0xE4, 0xE5):  # IN
            port = data[i+1]
            if port not in port_stats: port_stats[port] = {'in': 0, 'out': 0, 'offsets': []}
            port_stats[port]['in'] += 1
            port_stats[port]['offsets'].append(i)
        elif data[i] in (0xE6, 0xE7):  # OUT
            port = data[i+1]
            if port not in port_stats: port_stats[port] = {'in': 0, 'out': 0, 'offsets': []}
            port_stats[port]['out'] += 1
            port_stats[port]['offsets'].append(i)
    
    # Стандартные порты PC
    standard_ports = {
        0x20: "PIC1 cmd", 0x21: "PIC1 data",
        0x40: "PIT ch0", 0x41: "PIT ch1", 0x42: "PIT ch2", 0x43: "PIT ctrl",
        0x60: "PS/2 data", 0x61: "System ctrl", 0x64: "PS/2 cmd",
        0xA0: "PIC2 cmd", 0xA1: "PIC2 data",
        0xF0: "FPU clear",
    }
    
    print("\n  Порт   IN  OUT  Всего  Тип")
    print("  " + "-" * 50)
    for port in sorted(port_stats.keys()):
        s = port_stats[port]
        total = s['in'] + s['out']
        if total < 2:
            continue
        port_type = standard_ports.get(port, "** ПЛАТА **")
        print(f"  0x{port:02X}  {s['in']:4d}  {s['out']:3d}  {total:5d}  {port_type}")
    
    # Выделяем группу портов, которые вероятно принадлежат плате
    print("\n  Наиболее активные нестандартные порты (порты платы управления):")
    board_ports = {}
    for port in sorted(port_stats.keys()):
        if port not in standard_ports:
            s = port_stats[port]
            total = s['in'] + s['out']
            if total >= 3:
                board_ports[port] = s
                print(f"    Port 0x{port:02X} ({port:3d}): IN={s['in']}, OUT={s['out']}")
    
    return board_ports

def read_cfg_file():
    """Читаем конфигурационные файлы для определения параметров лазера"""
    print("\n" + "=" * 78)
    print("  СОДЕРЖИМОЕ КОНФИГУРАЦИОННЫХ ФАЙЛОВ")
    print("=" * 78)
    
    for cfg_name in ["FLINT1.CFG", "FLINT9.CFG"]:
        try:
            with open(cfg_name, "r") as f:
                content = f.read()
            print(f"\n  --- {cfg_name} ---")
            lines = content.strip().split('\n')
            field_names = [
                "привязка X (×10 мкм)",
                "привязка Y (×10 мкм)", 
                "привязка Z (×10 мкм)",
                "шаг привязки (×10 мкм)",
                "ПЕРИОД ЛАЗЕРА (мс)",
                "ЗАДЕРЖКА ЗАТВОРА GATE (×10 мкс)",
                "макс. частота шагов (Гц)",
                "флаг скорости (1=пост/0=перем)",
                "поправка dT (мс)",
                "задержка эл.мех.затворов (мс)",
                "рабочие позиции (flint9)",
            ]
            for i, line in enumerate(lines):
                name = field_names[i] if i < len(field_names) else "?"
                print(f"    [{i+1:2d}] {line.strip():>10s}  ← {name}")
        except FileNotFoundError:
            print(f"\n  {cfg_name}: файл не найден")
        except Exception as e:
            print(f"\n  {cfg_name}: ошибка чтения: {e}")

def reconstruct_laser_logic(data, header_size):
    """
    Восстанавливаем логику управления лазером на основе всего анализа
    """
    print("\n" + "=" * 78)
    print("  ВОССТАНОВЛЕННАЯ ЛОГИКА УПРАВЛЕНИЯ ЛАЗЕРОМ (ПСЕВДОКОД)")
    print("=" * 78)
    print("""
  На основе анализа документации, строк, портов и дизассемблированного кода:

  ┌─────────────────────────────────────────────────────────────────────┐
  │                    АРХИТЕКТУРА УПРАВЛЕНИЯ ЛАЗЕРОМ                   │
  ├─────────────────────────────────────────────────────────────────────┤
  │                                                                     │
  │  Лазер управляется через ПЛАТУ УПРАВЛЕНИЯ (ISA карта?)              │
  │  Плата содержит:                                                    │
  │    - Дополнительный таймер (аналог 8254) с 3 каналами              │
  │    - Цифровые выходы для эл.мех. затворов (9 позиций)              │
  │    - Электро-оптический затвор (Gate)                               │
  │    - Концевые датчики осей X, Y, Z                                 │
  │    - Шаговые двигатели 3-х осей                                    │
  │                                                                     │
  │  Схема генерации лазерного импульса:                                │
  │                                                                     │
  │   ┌──────────┐  period   ┌──────────┐  delay   ┌──────────┐       │
  │   │  Канал 0 │ ────────→ │  Канал 1 │ ───────→ │  Затвор  │       │
  │   │  (Pump)  │  10-500мс │  (Gate)  │ 10-500мкс│  (Gate)  │       │
  │   └──────────┘           └──────────┘           └──────────┘       │
  │    Период накачки         Задержка затвора        Генерация         │
  │                                                                     │
  │  + Эл.мех. затворы: выбирают какая из 9 позиций облучается        │
  │                                                                     │
  └─────────────────────────────────────────────────────────────────────┘

  // === Инициализация лазера ===
  void laser_init() {
      // Читаем параметры из flint1.cfg / flint9.cfg
      laser_period = cfg[5];       // период накачки в мс (поле 5)  
      gate_delay = cfg[6] * 10;    // задержка затвора в мкс (поле 6 × 10)
      shutter_delay = cfg[10];     // задержка эл.мех.затворов в мс (поле 10)
      
      // Инициализируем таймер платы
      // Канал 0: mode 2 (rate generator) — период накачки
      out(PIT_CTRL, 0x34);         // канал 0, mode 2, LSB/MSB
      out(PIT_CH0, period_lo);     // младший байт делителя
      out(PIT_CH0, period_hi);     // старший байт делителя
      
      // Канал 1: mode 1 (one-shot) — задержка затвора  
      out(PIT_CTRL, 0x72);         // канал 1, mode 1, LSB/MSB
      out(PIT_CH1, delay_lo);      // младший байт
      out(PIT_CH1, delay_hi);      // старший байт
  }

  // === Включение накачки ===
  void pump_on() {
      // Запускаем генерацию импульсов накачки
      // Канал 0 таймера генерирует прерывания с периодом laser_period
      // При каждом импульсе накачки может срабатывать затвор Gate
      set_timer_ch0(laser_period);
      pump_active = true;
  }
  
  void pump_off() {
      // Останавливаем накачку
      stop_timer_ch0();
      pump_active = false;
  }

  // === Управление затвором (Gate) ===
  void gate_enable(int delay_us) {
      // Устанавливаем задержку затвора
      // delay_us = 10..500 мкс (шаг 10 мкс)
      // При delay=10мкс — генерация отсутствует (безопасный режим)
      set_timer_ch1(delay_us);
      gate_active = true;
  }
  
  void gate_disable() {
      // Безопасное выключение — задержка = 10 мкс (нет генерации)
      set_timer_ch1(10);
      gate_active = false;
  }

  // === Управление эл.мех. затворами (для 9 позиций) ===
  void set_shutters(uint16_t mask) {
      // mask: биты 0-8 = позиции образцов
      // 1 = затвор открыт (лазер проходит)
      // 0 = затвор закрыт (лазер блокирован)
      out(SHUTTER_PORT, mask);
      delay_ms(shutter_delay);      // ждём срабатывания эл.мех.затворов
  }

  // === Основной цикл обработки (функция move()) ===
  void move(trajectory) {
      // Устанавливаем затворы для нужных позиций
      set_shutters(active_positions);
      
      // Включаем накачку с заданным периодом
      pump_on();
      
      for (each point in trajectory) {
          // Общее время на перемещение + вычисления:
          // T_total = laser_period - dT
          // dT — коррекция на время вычислений CPU (~6-8мс на 486DX66)
          
          // Вычисляем скорости по осям
          calc_speeds(point, &vx, &vy, &vz);
          
          // За 40-150мкс до конца периода — разрешаем затвор Gate
          // (чтобы избежать двойных пробоев)
          wait_for_pump_cycle();
          gate_enable(gate_delay_us);
          
          // Перемещаем стол к следующей точке
          step_motors(vx, vy, vz);
          
          // Проверяем результат пробоя (если Dr.check включен)
          if (destruction_check) {
              if (!check_destruction()) {
                  // Увеличиваем счётчик повторов
                  retries++;
                  if (retries > max_retries) {
                      // "Check laser. Retry: Ok"
                      gate_disable();
                      show_message("Check laser. Retry: Ok");
                      // Подсвечиваем красным позиции с ошибками
                      beep();   // звуковое оповещение
                  }
              }
          }
          
          // Проверяем ESC
          if (key_pressed(ESC)) {
              gate_disable();   // безопасное выключение
              pump_off();
              break;
          }
      }
      
      // "Ok.  TABLE END"
      pump_off();
      gate_disable();
  }

  // === Выход из программы ===
  void exit_program() {
      gate_disable();     // задержка = 10мкс (нет генерации)
      pump_off();          // выключаем накачку
      close_shutters();    // закрываем все затворы
      // восстанавливаем стандартные вектора прерываний
  }
""")

def main():
    data = read_exe()
    header_size = struct.unpack_from("<H", data, 8)[0] * 16  # header_paragraphs * 16
    exe_size = len(data)
    
    all_strings = find_all_strings(data)
    
    read_cfg_file()
    analyze_cfg_files(data)
    find_laser_strings(data, all_strings)
    analyze_pit_timer(data, header_size)
    board_ports = analyze_board_ports(data, header_size, exe_size)
    port_functions = deep_disassembly_analysis(data, header_size, exe_size)
    find_kpu_code(data, header_size, all_strings)
    reconstruct_laser_logic(data, header_size)

if __name__ == "__main__":
    main()
