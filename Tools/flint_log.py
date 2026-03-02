#!/usr/bin/env python3
"""
flint_log.py — Полный анализатор FLINT.LOG

Разбирает лог Flint 2.77 (32-bit) и выводит понятные отчёты:
  - Хронология действий пользователя и работы установки
  - Статистика лазерных выстрелов (успех, retry, FAIL)
  - Параметры сессий
  - Диагностика проблем

Использование:
  python flint_log.py FLINT.LOG                # полный отчёт
  python flint_log.py FLINT.LOG --timeline     # хронология событий
  python flint_log.py FLINT.LOG --shots        # анализ выстрелов
  python flint_log.py FLINT.LOG --timing       # тайминг pump+gate (физика)
  python flint_log.py FLINT.LOG --points       # таблица точек
  python flint_log.py FLINT.LOG --config       # история конфигурации
  python flint_log.py FLINT.LOG --problems     # только проблемы
  python flint_log.py FLINT.LOG --hw           # аппаратный I/O (лазер + моторы + protect)
"""

import argparse
import re
import sys
from collections import Counter, defaultdict


# ═══════════════════════════════════════════════════
#  Парсер строк лога
# ═══════════════════════════════════════════════════

class LogEvent:
    """Одно событие из лога."""
    __slots__ = ('line_no', 'tag', 'raw', 'data')
    def __init__(self, line_no, tag, raw, data=None):
        self.line_no = line_no
        self.tag = tag
        self.raw = raw
        self.data = data or {}


def parse_kv(text):
    """Разбирает 'key=val key2=val2' в словарь."""
    d = {}
    for m in re.finditer(r'(\w+)=([^\s)]+)', text):
        k, v = m.group(1), m.group(2)
        # попытка конвертировать в число
        try:
            if '.' in v:
                d[k] = float(v)
            else:
                d[k] = int(v)
        except ValueError:
            d[k] = v
    return d


def parse_log(filepath):
    """Читает FLINT.LOG и возвращает список LogEvent."""
    events = []
    with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
        for i, line in enumerate(f, 1):
            line = line.rstrip('\n\r')
            if not line:
                continue

            # Заголовки лога
            if line.startswith('=== '):
                tag = 'LOG_START' if 'Start' in line else 'LOG_END'
                events.append(LogEvent(i, tag, line))
                continue

            # [TAG] ...
            m = re.match(r'\[(\w+)\]\s*(.*)', line)
            if m:
                tag = m.group(1)
                rest = m.group(2)
                data = parse_kv(rest)

                # Дополнительный разбор для специфичных строк
                # [INI] hw=1 K1=150 ...
                # [CONFIG] PUMP ON / GATE ON / OK ... / EXIT ...
                # [LPULS] CALL / ok / retry / FAIL / FIRE / WAIT / ESC / demo
                # [PROC] START / CFG / CALC / END / ESC / MOVE ERR / LPULS FAIL / METAL FAIL
                # [PT] i=... raw=... xyz=...
                # [MOV] dx=... dy=... dz=...
                # [DATA] LOAD file=...
                # [START] st=...
                # [SHOT] fire ...
                # [METAL] ...
                # [UI] MAIN / GLASSLOAD
                # [STRT] MODE / DCHECK / ENDSENS / NOISE
                # [GLLOAD] dir=...
                # [MOVE] ERR ...

                # Уточняем под-тег
                sub = ''
                sub_m = re.match(r'(CALL|ok|retry|FAIL|FIRE|WAIT|ESC|demo)\b', rest)
                if sub_m:
                    sub = sub_m.group(1)
                elif rest.startswith('START'):
                    sub = 'START'
                elif rest.startswith('CFG'):
                    sub = 'CFG'
                elif rest.startswith('CALC'):
                    sub = 'CALC'
                elif rest.startswith('END'):
                    sub = 'END'
                elif rest.startswith('OK') or rest.startswith('ok'):
                    sub = 'OK'
                elif rest.startswith('EXIT'):
                    sub = 'EXIT'
                elif rest.startswith('LOAD'):
                    sub = 'LOAD'
                elif rest.startswith('SAVE'):
                    sub = 'SAVE'
                elif rest.startswith('PUMP'):
                    sub = 'PUMP'
                elif rest.startswith('GATE') and tag == 'CONFIG':
                    sub = 'GATE'
                elif rest.startswith('METAL'):
                    sub = 'METAL'
                elif rest.startswith('PROTECT'):
                    sub = 'PROTECT'
                elif rest.startswith('GLASS'):
                    sub = 'GLASS'
                elif rest.startswith('RESET'):
                    sub = 'RESET'
                elif rest.startswith('LOADED'):
                    sub = 'LOADED'
                elif rest.startswith('WORKPTR'):
                    sub = 'WORKPTR'
                elif rest.startswith('SPEED'):
                    sub = 'SPEED'
                elif rest.startswith('CLEAR'):
                    sub = 'CLEAR'
                elif rest.startswith('GLASPOS'):
                    sub = 'GLASPOS'
                elif rest.startswith('LPERIOD'):
                    sub = 'LPERIOD'
                elif rest.startswith('GATEDLY'):
                    sub = 'GATEDLY'
                elif rest.startswith('STEPFREQ'):
                    sub = 'STEPFREQ'
                elif rest.startswith('STEPSIZE'):
                    sub = 'STEPSIZE'
                elif rest.startswith('XPTR') or rest.startswith('YPTR') or rest.startswith('ZPTR'):
                    sub = rest.split()[0]
                elif rest.startswith('MODE'):
                    sub = 'MODE'
                elif rest.startswith('DCHECK'):
                    sub = 'DCHECK'
                elif rest.startswith('ENDSENS'):
                    sub = 'ENDSENS'
                elif rest.startswith('NOISE'):
                    sub = 'NOISE'
                elif rest.startswith('MAIN'):
                    sub = 'MAIN'
                elif rest.startswith('GLASSLOAD'):
                    sub = 'GLASSLOAD'
                elif rest.startswith('MOVE ERR') or rest.startswith('ERR'):
                    sub = 'ERR'
                elif rest.startswith('fire'):
                    sub = 'FIRE'
                elif rest.startswith('nodchk') or ('nodchk' in rest):
                    sub = 'ok'

                # [HW] sub-tags
                if tag == 'HW':
                    if rest.startswith('PT2'):
                        sub = 'PT2'
                    elif rest.startswith('LRG'):
                        sub = 'LRG'
                    elif rest.startswith('SH_OPEN'):
                        sub = 'SH_OPEN'
                    elif rest.startswith('SH_CLOSE'):
                        sub = 'SH_CLOSE'
                    elif rest.startswith('RG '):
                        sub = 'RG'
                    elif rest.startswith('SEN_GO') or rest.startswith('SEN_RET'):
                        sub = 'SEN'
                    elif rest.startswith('PPI2'):
                        sub = 'PPI2'

                data['_sub'] = sub
                data['_rest'] = rest
                events.append(LogEvent(i, tag, line, data))
            else:
                events.append(LogEvent(i, 'UNKNOWN', line))

    return events


# ═══════════════════════════════════════════════════
#  Группировка в сессии
# ═══════════════════════════════════════════════════

class Session:
    """Одна сессия обработки (от START до END/ESC/FAIL)."""
    def __init__(self, start_event):
        self.start = start_event
        self.events = [start_event]
        self.points = []
        self.shots = []
        self.end_event = None
        self.params = {}

    def add(self, ev):
        self.events.append(ev)
        if ev.tag == 'PT':
            self.points.append(ev)
        elif ev.tag == 'LPULS' or ev.tag == 'METAL':
            self.shots.append(ev)


def group_sessions(events):
    """Разбивает события на сессии обработки."""
    sessions = []
    current = None

    for ev in events:
        if ev.tag == 'PROC' and ev.data.get('_sub') == 'START':
            current = Session(ev)
            current.params = ev.data.copy()
            sessions.append(current)
        elif current:
            current.add(ev)
            if ev.tag == 'PROC' and ev.data.get('_sub') in ('END', 'ESC', 'ERR'):
                current.end_event = ev
                current = None
    return sessions


# ═══════════════════════════════════════════════════
#  Анализ выстрелов
# ═══════════════════════════════════════════════════

def analyze_shots(shots):
    """Анализирует список событий LPULS/METAL и возвращает статистику."""
    stats = {
        'total_calls': 0,        # CALL-ов
        'total_pulses': 0,       # фактических выстрелов (FIRE)
        'first_shot_ok': 0,      # ok с i=0
        'retries_needed': 0,     # ok с i>0
        'total_retries': 0,      # суммарных retry-строк
        'total_fails': 0,        # FAIL
        'total_esc': 0,          # ESC
        'demo': 0,               # demo ok
        'retry_per_point': [],   # retry count per point
        'fail_points': [],       # номера точек с FAIL
        'dsens_values': Counter(),
    }

    call_count = 0
    retry_count = 0

    for ev in shots:
        sub = ev.data.get('_sub', '')
        rest = ev.data.get('_rest', '')

        if sub == 'CALL':
            stats['total_calls'] += 1
            call_count += 1
            retry_count = 0
        elif sub == 'FIRE':
            stats['total_pulses'] += 1
        elif 'demo' in rest:
            stats['demo'] += 1
        elif sub == 'ok':
            i = ev.data.get('i', 0)
            if i == 0 and 'nodchk' not in rest:
                stats['first_shot_ok'] += 1
            elif 'nodchk' in rest:
                stats['first_shot_ok'] += 1
            else:
                stats['retries_needed'] += 1
            stats['retry_per_point'].append(retry_count)
        elif sub == 'retry':
            retry_count += 1
            stats['total_retries'] += 1
            dsens = ev.data.get('dsens', '')
            if dsens != '':
                stats['dsens_values'][str(dsens)] += 1
        elif sub == 'FAIL':
            stats['total_fails'] += 1
            stats['retry_per_point'].append(retry_count)
        elif sub == 'ESC':
            stats['total_esc'] += 1

    return stats


# ═══════════════════════════════════════════════════
#  Форматирование вывода — русский язык
# ═══════════════════════════════════════════════════

def describe_event(ev):
    """Описывает одно событие человеческим языком."""
    tag = ev.tag
    sub = ev.data.get('_sub', '')
    rest = ev.data.get('_rest', '')
    d = ev.data

    # ── Старт/стоп лога ──
    if tag == 'LOG_START':
        return '🟢 Программа запущена'
    if tag == 'LOG_END':
        return '🔴 Программа завершена'

    # ── Инициализация ──
    if tag == 'INI':
        hw = d.get('hw', '?')
        hw_str = 'Плата найдена' if hw == 1 else 'ДЕМО-РЕЖИМ (плата не найдена)'
        return (f'⚙️  Инициализация: {hw_str}\n'
                f'      Период лазера: {d.get("lper","?")}×10мкс = {d.get("lper",0)*10}мкс, '
                f'Gate delay: {d.get("gate","?")}×10мкс = {d.get("gate",0)*10}мкс\n'
                f'      Задержка затвора: {d.get("shd","?")}мс, '
                f'Контроль рисунка: {"ДА" if d.get("dchk") else "НЕТ"}')

    # ── Главное меню ──
    if tag == 'UI':
        if sub == 'MAIN':
            btn_name = rest.split('(')[1].split(')')[0] if '(' in rest else f'btn={d.get("btn","?")}'
            return f'📋 Меню: нажата кнопка {btn_name}'
        if sub == 'GLASSLOAD':
            direction = rest.replace('GLASSLOAD ', '')
            return f'📋 Загрузка стекла: {direction}'
        return f'📋 UI: {rest}'

    # ── Загрузка данных ──
    if tag == 'DATA':
        if sub == 'LOAD':
            return f'📂 Загружен файл: {d.get("file","?")} — {d.get("points","?")} точек'
        return f'📂 Данные: {rest}'

    # ── Конфигурация ──
    if tag == 'CONFIG':
        if sub == 'PUMP':
            state = 'ВКЛЮЧЕНА ⚡' if 'ON' in rest else 'выключена'
            return f'🔧 Накачка лазера: {state}'
        if sub == 'GATE':
            state = 'включена' if 'ON' in rest else 'выключена'
            return f'🔧 Gate-задержка (Config UI): {state}'
        if sub == 'PROTECT':
            state = 'ОТКРЫТА ⚠️' if 'OPEN' in rest else 'закрыта'
            return f'🔧 Защита: {state}'
        if sub == 'METAL':
            state = 'включён' if 'ON' in rest else 'выключён'
            return f'🔧 Режим металла: {state}'
        if sub == 'OK':
            return (f'✅ Config OK: период={d.get("lper","?")}×10мкс, '
                    f'gate={d.get("gate","?")}×10мкс, '
                    f'шаг-частота={d.get("sfq","?")}Гц, '
                    f'sh_delay={d.get("shd","?")}мс, '
                    f'режим={"const" if d.get("const") else "var"}, '
                    f'металл={"да" if d.get("metal") else "нет"}')
        if sub == 'EXIT':
            return (f'🚪 Выход из Config: LCtl={d.get("LCtl","?")}, '
                    f'gate сброшен на 1 (безопасный)')
        if sub == 'LOADED':
            return f'📥 Загружена конфигурация: период={d.get("lper","?")}, gate={d.get("gate","?")}'
        if sub == 'SAVE':
            return f'💾 Сохранена конфигурация: X={d.get("x","?")} Y={d.get("y","?")} Z={d.get("z","?")}'
        if sub == 'LOAD':
            return f'📥 Загрузка .cfg для glass={d.get("glass","?")}'
        if sub == 'GLASS':
            num = rest.replace('GLASS ', '')
            return f'🔧 Режим стекла: {num}'
        if sub == 'RESET':
            return '🔧 Статистика сброшена'
        if sub == 'WORKPTR':
            state = 'включён' if 'ON' in rest else 'выключён'
            return f'🔧 Рабочий указатель: {state}'
        if sub == 'SPEED':
            mode = rest.replace('SPEED ', '')
            return f'🔧 Скорость: {mode}'
        if sub == 'CLEAR':
            return '🔧 Позиции стёкол очищены'
        if sub == 'GLASPOS':
            # Парсим hex маску позиций
            m2 = re.search(r'GLASPOS\s+([0-9A-Fa-f]+)', rest)
            mask = int(m2.group(1), 16) if m2 else 0
            positions = [str(i+1) for i in range(9) if mask & (1 << i)]
            return f'🔧 Позиции стёкол: [{",".join(positions) or "нет"}]'
        if sub == 'LPERIOD':
            # [CONFIG] LPERIOD 40
            val_m = re.search(r'LPERIOD\s+(\d+)', rest)
            val = int(val_m.group(1)) if val_m else '?'
            return f'🔧 Период лазера → {val}×10мкс = {val*10 if isinstance(val,int) else "?"}мкс'
        if sub == 'GATEDLY':
            val_m = re.search(r'GATEDLY\s+(\d+)', rest)
            val = int(val_m.group(1)) if val_m else '?'
            return f'🔧 Gate delay → {val}×10мкс = {val*10 if isinstance(val,int) else "?"}мкс'
        if sub == 'STEPFREQ':
            val_m = re.search(r'STEPFREQ\s+(\d+)', rest)
            val = val_m.group(1) if val_m else '?'
            return f'🔧 Частота шагов → {val} Гц'
        if sub == 'STEPSIZE':
            val_m = re.search(r'STEPSIZE\s+(\d+)', rest)
            val = val_m.group(1) if val_m else '?'
            return f'🔧 Размер шага → {val}'
        if sub in ('XPTR', 'YPTR', 'ZPTR'):
            val_m = re.search(r'[XYZ]PTR\s+(\d+)', rest)
            val = val_m.group(1) if val_m else '?'
            return f'🔧 Указатель {sub[0]} → {val}'
        return f'🔧 Config: {rest}'

    # ── Стартовый диалог ──
    if tag == 'STRT':
        if sub == 'MODE':
            mode = rest.replace('MODE ', '')
            mode_ru = {'beginning': 'с начала', 'point_number': 'с номера точки',
                       'continuation': 'продолжение'}.get(mode, mode)
            if 'cmos' in mode:
                return f'🎯 Режим старта: CMOS (pt={d.get("pt","?")})'
            return f'🎯 Режим старта: {mode_ru}'
        if sub == 'DCHECK':
            state = 'ВКЛЮЧЁН' if 'ON' in rest else 'выключен'
            return f'🎯 Контроль рисунка: {state}'
        if sub == 'ENDSENS':
            state = 'включены' if 'ON' in rest else 'выключены'
            return f'🎯 Концевики: {state}'
        if sub == 'NOISE':
            mode = rest.replace('NOISE ', '')
            mode_ru = {'stop': 'стоп', 'reboot': 'перезагрузка', 'ignore': 'игнорировать'}.get(mode, mode)
            return f'🎯 При шуме: {mode_ru}'
        return f'🎯 Старт: {rest}'

    # ── Запуск процесса ──
    if tag == 'START':
        return (f'🚀 ЗАПУСК ОБРАБОТКИ: точка {d.get("st","?")+1 if isinstance(d.get("st"),int) else "?"}, '
                f'dcheck={"да" if d.get("dchk") else "нет"}, '
                f'металл={"да" if d.get("metal") else "нет"}, '
                f'LCtl={d.get("LCtl","?")}, gate={d.get("gate","?")}')

    # ── Процесс ──
    if tag == 'PROC':
        if sub == 'START':
            return (f'▶️  Процесс: точки {d.get("n","?")}/{d.get("nmax","?") if "nmax" in rest else ""}, '
                    f'период={d.get("lper","?")}×10мкс, gate={d.get("gate","?")}×10мкс')
        if sub == 'CFG':
            return (f'    Конфиг: X={d.get("xptr","?")} Y={d.get("yptr","?")} Z={d.get("zptr","?")}, '
                    f'стекло={d.get("zsize","?")}×0.1мм, n={d.get("nglas","?")}, '
                    f'шаг={d.get("step","?")}, частота={d.get("sf","?")}Гц, '
                    f'dT={d.get("dT","?")}мс, '
                    f'{"ДЕМО" if d.get("demo") else "РЕАЛ"}')
        if sub == 'CALC':
            return f'    Расчёт: refr_ofs={d.get("refr_ofs","?")}, z_base={d.get("z_base","?")}'
        if sub == 'END':
            fl = d.get('fl', '?')
            return f'✅ ОБРАБОТКА ЗАВЕРШЕНА: {d.get("n","?")} точек, {fl} выстрелов всего'
        if sub == 'ESC':
            return f'⏹️  ПРЕРВАНО (ESC) на точке {d.get("pt","?")}/{d.get("nmax","?") if "nmax" in rest else ""}, выстрелов: {d.get("fl","?")}'
        if sub == 'ERR':
            if 'MOVE' in rest:
                return f'❌ ОШИБКА МОТОРА на точке {d.get("pt","?")}'
            if 'LPULS' in rest:
                return f'❌ ОТКАЗ ЛАЗЕРА на точке {d.get("pt","?")}, retry={d.get("retry","?")}'
            if 'METAL' in rest:
                return f'❌ ОТКАЗ МЕТАЛЛ-РЕЖИМА на точке {d.get("pt","?")}, retry={d.get("retry","?")}'
            return f'❌ Ошибка: {rest}'
        return f'▶️  Процесс: {rest}'

    # ── Точки обработки ──
    if tag == 'PT':
        return None  # пропускаем в timeline, показываем в --points

    # ── Перемещения ──
    if tag == 'MOV':
        return None  # пропускаем в timeline

    # ── Лазерные выстрелы ──
    if tag == 'LPULS':
        if sub == 'CALL':
            return None  # скрываем, информация в ok/retry/FAIL
        if sub == 'FIRE':
            return None  # техническая деталь
        if sub == 'WAIT':
            return None  # техническая деталь
        if 'demo' in rest:
            return None  # демо-выстрелы не интересны
        if sub == 'ok':
            i = d.get('i', 0)
            if i == 0 and 'nodchk' not in rest:
                return None  # первый выстрел успешен — норма, не показываем
            elif 'nodchk' in rest:
                return None  # без проверки — не интересно
            else:
                return f'    ⚡ Выстрел OK после {i} повтор(ов), dsens={d.get("dsens","?")}'
        if sub == 'retry':
            i = d.get('i', '?')
            dsens = d.get('dsens', '?')
            wrk = d.get('wrk', '?')
            return f'    ⚠️  Повтор #{i}: датчик={dsens}, нужно={wrk}'
        if sub == 'FAIL':
            return f'    ❌ ПРОВАЛ после 11 попыток! dsens={d.get("dsens","?")}, маска={d.get("mask","?")}'
        if sub == 'ESC':
            return f'    ⏹️  ESC при выстреле #{d.get("i","?")}'
        return f'    Лазер: {rest}'

    # ── Metal-режим ──
    if tag == 'METAL':
        if sub == 'CALL':
            return None
        if 'demo' in rest:
            return None
        if sub == 'ok':
            i = d.get('i', 0)
            if i == 0:
                return None
            return f'    ⚡ Металл OK после {i} повтор(ов)'
        if sub == 'retry':
            return f'    ⚠️  Металл повтор #{d.get("i","?")}: dsens={d.get("dsens","?")}'
        if sub == 'FAIL':
            return f'    ❌ Металл ПРОВАЛ! dsens={d.get("dsens","?")}'
        if sub == 'ESC':
            return f'    ⏹️  ESC в металл-режиме'
        return f'    Металл: {rest}'

    # ── Тестовый выстрел ──
    if tag == 'SHOT':
        return f'💥 Тестовый выстрел: pump={"вкл" if d.get("pump") else "выкл"}, gate={"вкл" if d.get("gate") else "выкл"}, fl={d.get("fl","?")}'

    # ── Загрузка стекла (мотор) ──
    if tag == 'GLLOAD':
        direction = 'ВВЕРХ' if d.get('dir', 0) == 0 else 'ВНИЗ'
        return f'🔄 Загрузка стекла: мотор {direction}'

    # ── Ошибка мотора ──
    if tag == 'MOVE':
        if sub == 'ERR':
            return f'❌ Ошибка мотора: sens={d.get("sens","?")} цель=({d.get("x","?")},{d.get("y","?")},{d.get("z","?")})'
        return f'🔄 Мотор: {rest}'

    # ── Аппаратный I/O ──
    if tag == 'HW':
        if sub == 'PT2':
            ch0 = d.get('ch0', '?')
            ch1 = d.get('ch1', '?')
            ch1_us = f'{ch1*10}мкс' if isinstance(ch1, int) else '?'
            if isinstance(ch0, int):
                ch0_us = ch0 * 10  # тиков → мкс (clock=100кГц=10мкс/тик)
                if ch0_us >= 1000:
                    ch0_str = f'{ch0_us/1000:.1f}мс'
                else:
                    ch0_str = f'{ch0_us}мкс'
            else:
                ch0_str = '?'
            lo = d.get('lo', '?')
            hi = d.get('hi', '?')
            safe = ' ⚠️ БЕЗОПАСНЫЙ' if isinstance(ch1, int) and ch1 <= 1 else ''
            return (f'🔌 PT2: ch0={ch0} ({ch0_str} период), '
                    f'ch1={ch1} ({ch1_us} gate){safe}')
        if sub == 'LRG':
            # [HW] LRG <- XX ...
            m2 = re.search(r'<-\s*([0-9A-Fa-f]+)', rest)
            val = int(m2.group(1), 16) if m2 else None
            if val is not None:
                pump = 'ВКЛ' if val & 1 else 'выкл'
                shutter = 'ВКЛ' if val & 2 else 'выкл'
                label = ''
                if '(init)' in rest:
                    label = ' [инициализация]'
                elif '(shutdown)' in rest:
                    label = ' [выключение]'
                return f'🔌 LRG <- 0x{val:02X}: накачка={pump}, EOShutter={shutter}{label}'
            return f'🔌 LRG: {rest}'
        if sub == 'SH_OPEN':
            pos = d.get('pos', '?')
            pb = d.get('PB', '?')
            shd = d.get('shd', '?')
            # Декодировать позиции shutters
            if isinstance(pos, str) and all(c in '0123456789abcdefABCDEF' for c in pos):
                posval = int(pos, 16)
            elif isinstance(pos, int):
                posval = pos
            else:
                posval = None
            if posval is not None:
                positions = [str(i+1) for i in range(10) if posval & (1 << i)]
                pos_str = ','.join(positions) if positions else 'нет'
            else:
                pos_str = '?'
            return f'🔌 SH_OPEN: затворы=[{pos_str}] PB=0x{pb} shd={shd}мс'
        if sub == 'SH_CLOSE':
            return '🔌 SH_CLOSE: все затворы закрыты'
        if sub == 'RG':
            # [HW] RG OUT XX fxy=N fz=N  /  RG STOP XX sens=XX  /  RG RECOVER XX  /  RG END XX  /  RG IDLE 80
            m_rg = re.search(r'RG\s+(\w+)\s+([0-9A-Fa-f]+)', rest)
            if m_rg:
                action = m_rg.group(1)
                val = int(m_rg.group(2), 16)
                dirs = []
                if val & 0x01: dirs.append('X↑')
                else: dirs.append('X↓')
                if val & 0x02: dirs.append('Y↑')
                else: dirs.append('Y↓')
                if val & 0x04: dirs.append('Z↑')
                else: dirs.append('Z↓')
                enables = []
                if val & 0x08: enables.append('X')
                if val & 0x10: enables.append('Y')
                if val & 0x20: enables.append('Z')
                osc = 'вкл' if not (val & 0x80) else 'выкл'
                en_str = ','.join(enables) if enables else 'нет'
                dir_str = ','.join(dirs)
                lbl = {'OUT': 'ПУСК', 'STOP': 'СТОП', 'RECOVER': 'ВОЗВРАТ', 'END': 'ФИНАЛ', 'IDLE': 'ПОКОЙ'}.get(action, action)
                extra = ''
                m_sens = re.search(r'sens=([0-9A-Fa-f]+)', rest)
                if m_sens:
                    extra = f' датчик=0x{m_sens.group(1)}'
                m_fxy = re.search(r'fxy=(\d+)\s+fz=(\d+)', rest)
                if m_fxy:
                    extra += f' fxy={m_fxy.group(1)} fz={m_fxy.group(2)}'
                return f'⚙️  RG {lbl} 0x{val:02X}: напр=[{dir_str}] вкл=[{en_str}] осц={osc}{extra}'
            return f'⚙️  RG: {rest}'
        if sub == 'SEN':
            # [HW] SEN_GO dir=N RG=XX target=XX  /  SEN_RET RG=XX
            if rest.startswith('SEN_GO'):
                m_sg = re.search(r'dir=(\d+)\s+RG=([0-9A-Fa-f]+)\s+target=([0-9A-Fa-f]+)', rest)
                if m_sg:
                    d = int(m_sg.group(1))
                    rg = int(m_sg.group(2), 16)
                    tgt = int(m_sg.group(3), 16)
                    dname = 'ДОМОЙ' if d == 0 else 'ЗАГРУЗКА'
                    return f'⚙️  SEN {dname}: RG=0x{rg:02X} → цель=0x{tgt:02X}'
                return f'⚙️  SEN_GO: {rest}'
            else:
                m_sr = re.search(r'RG=([0-9A-Fa-f]+)', rest)
                if m_sr:
                    rg = int(m_sr.group(1), 16)
                    return f'⚙️  SEN ВОЗВРАТ: RG=0x{rg:02X} (200 шагов назад)'
                return f'⚙️  SEN_RET: {rest}'
        if sub == 'PPI2':
            # [HW] PPI2 PR_OPEN  /  PPI2 PR_CLOSE
            if 'PR_OPEN' in rest:
                return '🛡️  PPI2 PROTECT ОТКРЫТ (реле разблокировано)'
            elif 'PR_CLOSE' in rest:
                return '🛡️  PPI2 PROTECT ЗАКРЫТ (реле заблокировано)'
            return f'🛡️  PPI2: {rest}'
        return f'🔌 HW: {rest}'


# ═══════════════════════════════════════════════════
#  Отчёты
# ═══════════════════════════════════════════════════

def print_header(title):
    w = 70
    print()
    print('=' * w)
    print(f'  {title}')
    print('=' * w)


def report_summary(events, sessions):
    """Общая сводка."""
    print_header('СВОДКА FLINT.LOG')

    # Найти INI
    ini = [e for e in events if e.tag == 'INI']
    if ini:
        e = ini[0]
        hw = e.data.get('hw', '?')
        print(f'\n  Режим:          {"Реальная работа" if hw == 1 else "ДЕМО (нет платы)"}')
        print(f'  Период лазера:  {e.data.get("lper","?")}×10мкс ({e.data.get("lper",0)*10}мкс)')
        print(f'  Gate delay:     {e.data.get("gate","?")}×10мкс ({e.data.get("gate",0)*10}мкс)')
        print(f'  Sh delay:       {e.data.get("shd","?")}мс')
        print(f'  Контроль (dchk):{" ДА" if e.data.get("dchk") else " НЕТ"}')

    # Загрузки файлов
    loads = [e for e in events if e.tag == 'DATA' and e.data.get('_sub') == 'LOAD']
    if loads:
        print(f'\n  Загружено файлов: {len(loads)}')
        for e in loads:
            print(f'    - {e.data.get("file","?")} ({e.data.get("points","?")} точек)')

    # Сессии
    print(f'\n  Сессий обработки: {len(sessions)}')
    for idx, s in enumerate(sessions, 1):
        n_pts = len(s.points)
        n_shots = len([e for e in s.shots if e.data.get('_sub') in ('ok', 'FAIL') or 'demo' in e.data.get('_rest', '')])
        end = s.end_event
        if end:
            end_sub = end.data.get('_sub', '')
            if end_sub == 'END':
                result = '✅ завершена'
            elif end_sub == 'ESC':
                result = f'⏹️  прервана (ESC) на точке {end.data.get("pt","?")}'
            else:
                result = f'❌ ошибка'
        else:
            result = '⚠️  незавершена'

        dchk = s.params.get('dchk', '?')
        metal = s.params.get('metal', '?')
        print(f'\n  --- Сессия {idx} ---')
        print(f'    Точек отработано: {n_pts}')
        print(f'    Выстрелов: {n_shots}')
        print(f'    Контроль: {"ДА" if dchk else "НЕТ"}')
        print(f'    Металл:   {"ДА" if metal else "НЕТ"}')
        print(f'    Результат: {result}')

        # Статистика выстрелов
        shot_stats = analyze_shots(s.shots)
        ok1 = shot_stats['first_shot_ok']
        ok_retry = shot_stats['retries_needed']
        fails = shot_stats['total_fails']
        retries = shot_stats['total_retries']
        demos = shot_stats['demo']

        if demos:
            print(f'    (демо: {demos} виртуальных выстрелов)')
        else:
            total_real = ok1 + ok_retry + fails
            if total_real > 0:
                pct_ok1 = ok1 * 100.0 / total_real if total_real else 0
                print(f'    1-й выстрел OK: {ok1}/{total_real} ({pct_ok1:.0f}%)')
                if ok_retry:
                    print(f'    Потребовали повторов: {ok_retry}')
                if retries:
                    print(f'    Всего повторных попыток: {retries}')
                if fails:
                    print(f'    ❌ ПРОВАЛОВ: {fails}')


def report_timeline(events):
    """Хронология всех событий."""
    print_header('ХРОНОЛОГИЯ СОБЫТИЙ')
    print()

    for ev in events:
        desc = describe_event(ev)
        if desc is not None:
            # Добавляем номер строки
            print(f'  [{ev.line_no:5d}] {desc}')


def report_hw(events):
    """Аппаратный I/O — все записи/чтения портов."""
    print_header('АППАРАТНЫЙ I/O (порты)')
    print()
    print('  Легенда:')
    print('    PT2 ch0 = период накачки (тиков @100кГц, ×10 = мкс)')
    print('    PT2 ch1 = gate delay (×10 = мкс). ch1=1 → безопасный режим')
    print('    LRG     = регистр лазера: D0=накачка, D1=EOShutter')
    print('    SH_OPEN = электромагнитные затворы (pos = битовая маска)')
    print('    SH_CLOSE= все затворы закрыты')
    print('    RG      = регистр моторов: направление/вкл XYZ, осциллограф')
    print('    SEN     = позиционирование HOME/LOAD (move_sen)')
    print('    PPI2    = реле защиты (PR_OPEN/PR_CLOSE)')
    print()

    # Собираем HW-события + ключевые CONFIG (PUMP/GATE) для контекста
    hw_events = [ev for ev in events if ev.tag == 'HW']
    ctx_events = [ev for ev in events if
                  (ev.tag == 'CONFIG' and ev.data.get('_sub') in ('PUMP', 'GATE', 'OK', 'EXIT')) or
                  ev.tag == 'INI' or
                  ev.tag == 'LOG_START' or ev.tag == 'LOG_END' or
                  (ev.tag == 'LPULS' and ev.data.get('_sub') in ('FIRE', 'WAIT', 'ok', 'FAIL')) or
                  (ev.tag == 'MOV') or
                  (ev.tag == 'MOVE' and ev.data.get('_sub') == 'ERR') or
                  (ev.tag == 'PROC' and ev.data.get('_sub') in ('START', 'END', 'ESC', 'MOVE ERR'))]

    # Объединяем и сортируем по номеру строки
    combined = sorted(hw_events + ctx_events, key=lambda e: e.line_no)

    if not combined:
        print('  (нет [HW] событий — возможно, TRACE не включён или демо-сессия)')
        return

    print(f'  Всего HW-событий: {len(hw_events)}, контекстных: {len(ctx_events)}')
    print()

    for ev in combined:
        desc = describe_event(ev)
        if desc is not None:
            prefix = '  >>>' if ev.tag == 'HW' else '     '
            print(f'{prefix} [{ev.line_no:5d}] {desc}')


def report_shots(events, sessions):
    """Подробный анализ лазерных выстрелов."""
    print_header('АНАЛИЗ ЛАЗЕРНЫХ ВЫСТРЕЛОВ')

    for idx, s in enumerate(sessions, 1):
        shot_events = s.shots
        stats = analyze_shots(shot_events)

        print(f'\n  --- Сессия {idx} (dchk={"да" if s.params.get("dchk") else "нет"}) ---')

        demos = stats['demo']
        if demos:
            print(f'    Демо-режим: {demos} виртуальных выстрелов')
            continue

        ok1 = stats['first_shot_ok']
        ok_retry = stats['retries_needed']
        fails = stats['total_fails']
        retries = stats['total_retries']
        esc = stats['total_esc']
        total_real = ok1 + ok_retry + fails

        print(f'    Вызовов LPULS:       {stats["total_calls"]}')
        print(f'    Физических импульсов: {stats["total_pulses"]}')
        print(f'    1-й выстрел OK:      {ok1}')
        print(f'    С повторами:         {ok_retry}')
        print(f'    Всего повторов:      {retries}')
        print(f'    ПРОВАЛОВ:            {fails}')
        if esc:
            print(f'    Прервано ESC:        {esc}')

        if total_real > 0:
            pct = ok1 * 100.0 / total_real
            print(f'    Успех 1-м выстрелом: {pct:.1f}%')

        # Распределение retry
        rpp = stats['retry_per_point']
        if rpp:
            non_zero = [r for r in rpp if r > 0]
            if non_zero:
                print(f'\n    Распределение повторов (только с retry):')
                rc = Counter(non_zero)
                for count, num in sorted(rc.items()):
                    print(f'      {count} повтор(а/ов): {num} раз')

        # dsens значения
        if stats['dsens_values']:
            print(f'\n    Значения датчика при retry:')
            for val, cnt in stats['dsens_values'].most_common(10):
                if val == '0' or val == 0:
                    print(f'      dsens={val}: {cnt} раз  ← ДАТЧИК НИЧЕГО НЕ ВИДИТ!')
                else:
                    print(f'      dsens={val}: {cnt} раз')

        # Проблемные точки
        # Найти точки с FAIL
        pt_idx = None
        for ev in shot_events:
            if ev.tag == 'PROC' and 'pt=' in ev.data.get('_rest', ''):
                pt_idx = ev.data.get('pt')
            sub = ev.data.get('_sub', '')
            if sub == 'FAIL':
                if pt_idx is not None:
                    stats['fail_points'].append(pt_idx)

        if stats['fail_points']:
            print(f'\n    ❌ Точки с полным провалом: {stats["fail_points"]}')


def report_points(events):
    """Таблица обработанных точек."""
    print_header('ТАБЛИЦА ТОЧЕК')

    pts = [e for e in events if e.tag == 'PT']
    if not pts:
        print('\n  Точек в логе нет.')
        return

    print(f'\n  {"#":>6} {"rawX":>6} {"rawY":>6} {"rawZ":>6} | {"X":>6} {"Y":>6} {"Z":>6} | {"dX":>6} {"dY":>6} {"dZ":>6}')
    print('  ' + '-' * 72)

    for ev in pts:
        d = ev.data
        rest = d.get('_rest', '')
        # [PT] i=0 raw=500,500,1369 xyz=22320,830,8456 d=-980,630,8256
        m = re.match(r'i=(\d+)\s+raw=(-?\d+),(-?\d+),(-?\d+)\s+xyz=(-?\d+),(-?\d+),(-?\d+)\s+d=(-?\d+),(-?\d+),(-?\d+)', rest)
        if m:
            vals = [int(g) for g in m.groups()]
            print(f'  {vals[0]:6d} {vals[1]:6d} {vals[2]:6d} {vals[3]:6d} | {vals[4]:6d} {vals[5]:6d} {vals[6]:6d} | {vals[7]:6d} {vals[8]:6d} {vals[9]:6d}')


def report_config(events):
    """История изменений конфигурации."""
    print_header('ИСТОРИЯ КОНФИГУРАЦИИ')
    print()

    config_tags = {'CONFIG', 'STRT', 'SHOT'}
    for ev in events:
        if ev.tag in config_tags:
            desc = describe_event(ev)
            if desc:
                print(f'  [{ev.line_no:5d}] {desc}')


def report_problems(events, sessions):
    """Только проблемы и предупреждения."""
    print_header('ПРОБЛЕМЫ И ПРЕДУПРЕЖДЕНИЯ')
    print()

    problems = []

    # Проверяем INI
    ini = [e for e in events if e.tag == 'INI']
    if ini and ini[0].data.get('hw') != 1:
        problems.append(('ИНФО', 'Программа в демо-режиме (плата ISA не найдена)'))

    # Проверяем retry и FAIL по сессиям
    for idx, s in enumerate(sessions, 1):
        stats = analyze_shots(s.shots)

        if stats['demo']:
            continue

        if stats['total_fails'] > 0:
            problems.append(('КРИТИЧ', f'Сессия {idx}: {stats["total_fails"]} полных провалов (FAIL)'))

        if stats['total_retries'] > 0:
            total = stats['first_shot_ok'] + stats['retries_needed'] + stats['total_fails']
            pct_retry = stats['retries_needed'] * 100.0 / total if total else 0
            if pct_retry > 20:
                problems.append(('ВАЖНО', f'Сессия {idx}: {pct_retry:.0f}% выстрелов потребовали повторов'))
            elif pct_retry > 5:
                problems.append(('ВНИМАНИЕ', f'Сессия {idx}: {pct_retry:.0f}% выстрелов с повторами'))

        # dsens всегда 0?
        if stats['dsens_values']:
            zeros = stats['dsens_values'].get('0', 0) + stats['dsens_values'].get(0, 0)
            total_dsens = sum(stats['dsens_values'].values())
            if total_dsens > 0 and zeros == total_dsens:
                problems.append(('КРИТИЧ', f'Сессия {idx}: датчик ВСЕГДА читает 0000 — '
                                 f'затвор не срабатывает или сенсор неисправен'))

        # ESC
        for ev in s.events:
            if ev.tag == 'PROC' and ev.data.get('_sub') == 'ESC':
                problems.append(('ИНФО', f'Сессия {idx}: прервана пользователем (ESC) на точке {ev.data.get("pt","?")}'))

        # MOVE ERR
        for ev in s.events:
            if ev.tag == 'PROC' and ev.data.get('_sub') == 'ERR' and 'MOVE' in ev.data.get('_rest', ''):
                problems.append(('КРИТИЧ', f'Сессия {idx}: ошибка мотора на точке {ev.data.get("pt","?")}'))
            if ev.tag == 'MOVE' and ev.data.get('_sub') == 'ERR':
                problems.append(('КРИТИЧ', f'Сессия {idx}: концевик мотора сработал'))

    # Проверяем Config: pump не включена перед стартом
    pump_on = False
    for ev in events:
        if ev.tag == 'CONFIG' and ev.data.get('_sub') == 'PUMP':
            pump_on = 'ON' in ev.data.get('_rest', '')
        if ev.tag == 'CONFIG' and ev.data.get('_sub') == 'EXIT':
            pump_on = False  # pump state preserved in LCtl, but worth noting
        if ev.tag == 'START':
            lctl = ev.data.get('LCtl', 0)
            if not lctl:
                problems.append(('ВАЖНО', f'Строка {ev.line_no}: Старт без накачки (LCtl=0)'))

    if not problems:
        print('  ✅ Проблем не обнаружено!')
    else:
        for severity, msg in problems:
            icon = {'КРИТИЧ': '❌', 'ВАЖНО': '⚠️ ', 'ВНИМАНИЕ': '⚡', 'ИНФО': 'ℹ️ '}.get(severity, '  ')
            print(f'  {icon} [{severity}] {msg}')


def report_timing(events, sessions):
    """Подробный анализ тайминга pump+gate по каждому выстрелу."""
    print_header('КАК РАБОТАЕТ СВЯЗКА PUMP + GATE DELAY')
    print("""
  ┌─────────────────────────────────────────────────────────────────┐
  │  PT2.ch0 — таймер накачки (l_period × 100 тиков @ 100кГц)     │
  │  PT2.ch1 — gate-задержка  (gate_delay тиков, mode 5)          │
  │                                                                 │
  │  Цикл выстрела:                                                │
  │  1. Накачка непрерывно качает (LCtl.D0=1), PT2.ch0 тикает     │
  │  2. FIRE: program_pt2(lper, gate) — загружаем gate в ch1       │
  │  3. ch0 дотикивает старый цикл → перезагрузка → триггер ch1   │
  │  4. ch1 отсчитывает gate_delay тиков (= gate × 10мкс)         │
  │  5. ch1→0: Q-switch срабатывает → ЛАЗЕРНЫЙ ИМПУЛЬС            │
  │  6. SAFE RESET: program_pt2(lper, 1) — gate=1 (безопасный)    │
  │  7. Чтение dsens — датчики видели вспышку?                     │
  │                                                                 │
  │  Проблема delay(1): оригинал ждал 1мс между шагами 2 и 6,     │
  │  но DOS4GW возвращает delay(1)→0мс = gate не успел отработать  │
  │  32-bit фикс: аппаратное ожидание через read_pt2()             │
  │                                                                 │
  │  В логе:                                                        │
  │    FIRE  sync=X  — счётчик PT2 в момент синхра (должен ~0-33)  │
  │          cyc=N   — полный цикл (lper×100 тиков)                │
  │          gate=G  — gate_delay (тики × 10мкс = задержка)        │
  │    WAIT  target=T — порог: cyc - gate - 10                     │
  │          post=P  — счётчик после ожидания (P ≤ target)         │
  │          elapsed=E — тиков прошло от перезагрузки (cyc-post)   │
  │          ~Eus    — elapsed × 10мкс ≈ время ожидания            │
  │                                                                 │
  │  Важно: elapsed ДОЛЖЕН быть ≥ gate+10, иначе Q-switch          │
  │  не успел сработать → dsens=0 → retry/FAIL                    │
  └─────────────────────────────────────────────────────────────────┘
""")

    for idx, s in enumerate(sessions, 1):
        shot_evts = s.shots  # all LPULS/METAL events in session
        fires = [e for e in s.events if e.tag in ('LPULS','METAL') and e.data.get('_sub') == 'FIRE']
        waits = [e for e in s.events if e.tag in ('LPULS','METAL') and e.data.get('_sub') == 'WAIT']

        if not fires and not waits:
            # Might be demo or old format
            demo_ok = [e for e in s.events if e.tag in ('LPULS','METAL') and 'demo' in e.data.get('_rest','')]
            if demo_ok:
                print(f'  --- Сессия {idx}: ДЕМО ({len(demo_ok)} виртуальных выстрелов, тайминг не применим) ---\n')
                continue

        # Try to pair FIREs with WAITs by iteration order
        print(f'  --- Сессия {idx} ---')

        lper = s.params.get('lper', 0)
        gate = s.params.get('gate', 0)
        print(f'    Настройки: lper={lper} (цикл={lper*100} тиков = {lper*10}мкс), '
              f'gate={gate} (задержка={gate*10}мкс)')
        print(f'    target = {lper*100} - {gate} - 10 = {lper*100 - gate - 10}')
        print()

        # Build shot chains: CALL → FIRE → WAIT → (ok|retry|FAIL)
        chains = []
        current_chain = None
        point_idx = None

        for ev in s.events:
            if ev.tag == 'PT':
                point_idx = ev.data.get('i', point_idx)
            if ev.tag not in ('LPULS', 'METAL'):
                continue
            sub = ev.data.get('_sub', '')
            rest = ev.data.get('_rest', '')

            if sub == 'CALL':
                current_chain = {'call': ev, 'point': point_idx, 'pulses': []}
                chains.append(current_chain)
            elif current_chain is not None:
                if sub == 'FIRE':
                    current_chain['pulses'].append({'fire': ev, 'wait': None, 'result': None})
                elif sub == 'WAIT' and current_chain['pulses']:
                    current_chain['pulses'][-1]['wait'] = ev
                elif sub in ('ok', 'retry', 'FAIL', 'ESC') or 'demo' in rest or 'nodchk' in rest:
                    if current_chain['pulses']:
                        current_chain['pulses'][-1]['result'] = ev
                    else:
                        # ok without fire (demo/nodchk)
                        current_chain['pulses'].append({'fire': None, 'wait': None, 'result': ev})

        # Statistics
        timing_ok = 0
        timing_marginal = 0
        timing_bad = 0
        elapsed_values = []

        for chain in chains:
            for pulse in chain['pulses']:
                fire = pulse.get('fire')
                wait = pulse.get('wait')
                if fire and wait:
                    elapsed = wait.data.get('elapsed', None)
                    gate_val = fire.data.get('gate', 0)
                    if elapsed is not None:
                        elapsed_values.append(elapsed)
                        if elapsed >= gate_val + 10:
                            timing_ok += 1
                        elif elapsed >= gate_val:
                            timing_marginal += 1
                        else:
                            timing_bad += 1

        total_timed = timing_ok + timing_marginal + timing_bad
        if total_timed:
            print(f'    Выстрелов с таймингом: {total_timed}')
            print(f'      ✅ OK (elapsed ≥ gate+10):    {timing_ok}')
            if timing_marginal:
                print(f'      ⚠️  Маргинальный (gate ≤ e < gate+10): {timing_marginal}')
            if timing_bad:
                print(f'      ❌ ПЛОХОЙ (elapsed < gate):   {timing_bad}  ← Q-switch не успел!')
            if elapsed_values:
                mn = min(elapsed_values)
                mx = max(elapsed_values)
                avg = sum(elapsed_values) / len(elapsed_values)
                print(f'      elapsed: мин={mn} ({mn*10}мкс), макс={mx} ({mx*10}мкс), средн={avg:.0f} ({avg*10:.0f}мкс)')
            print()

        # Detailed per-shot table (only for shots with problems or first N)
        MAX_DETAIL = 40
        printed = 0
        has_problems = any(
            p.get('wait') and p['wait'].data.get('elapsed', 999) < (p.get('fire') and p['fire'].data.get('gate', 0) or 0) + 10
            for c in chains for p in c['pulses'] if p.get('fire')
        )
        # Check for retries
        has_retries = any(
            len(c['pulses']) > 1
            for c in chains
        )

        if has_problems or has_retries:
            print(f'    {"#":>4} {"точка":>6} {"i":>2}  {"sync":>5} {"cyc":>5} {"gate":>5} │ {"target":>6} {"post":>6} {"elapsed":>7} {"~мкс":>6} │ результат')
            print(f'    {"":->4} {"":->6} {"":->2}  {"":->5} {"":->5} {"":->5} ┼ {"":->6} {"":->6} {"":->7} {"":->6} ┼ {"":->20}')
            for ci, chain in enumerate(chains):
                if len(chain['pulses']) <= 1:
                    # Single pulse, only show if timing is bad
                    p = chain['pulses'][0] if chain['pulses'] else None
                    if p and p.get('fire') and p.get('wait'):
                        e = p['wait'].data.get('elapsed', 0)
                        g = p['fire'].data.get('gate', 0)
                        if e >= g + 10:
                            continue  # skip normal shots
                if printed >= MAX_DETAIL:
                    remaining = len(chains) - ci
                    if remaining > 0:
                        print(f'    ... ещё {remaining} цепочек ...')
                    break

                pt = chain.get('point', '?')
                for pi, pulse in enumerate(chain['pulses']):
                    fire = pulse.get('fire')
                    wait = pulse.get('wait')
                    result = pulse.get('result')

                    # FIRE fields
                    if fire:
                        fi = fire.data.get('i', '?')
                        sync = fire.data.get('sync', fire.data.get('sync_pt2', '?'))
                        cyc = fire.data.get('cyc', '?')
                        gv = fire.data.get('gate', '?')
                    else:
                        fi = sync = cyc = gv = '-'

                    # WAIT fields
                    if wait:
                        target = wait.data.get('target', '?')
                        post = wait.data.get('post', wait.data.get('post_pt2', '?'))
                        elapsed = wait.data.get('elapsed', '?')
                        us = f'~{elapsed*10}' if isinstance(elapsed, int) else '?'
                    else:
                        target = post = elapsed = us = '-'

                    # Result
                    if result:
                        rsub = result.data.get('_sub', '')
                        rrest = result.data.get('_rest', '')
                        if 'demo' in rrest:
                            res_str = 'demo'
                        elif 'nodchk' in rrest:
                            res_str = 'ok (без dchk)'
                        elif rsub == 'ok':
                            ri = result.data.get('i', 0)
                            ds = result.data.get('dsens', '?')
                            res_str = f'ok i={ri} ds={ds}'
                        elif rsub == 'retry':
                            ds = result.data.get('dsens', '?')
                            res_str = f'retry ds={ds} ←'
                        elif rsub == 'FAIL':
                            ds = result.data.get('dsens', '?')
                            res_str = f'❌ FAIL ds={ds}'
                        elif rsub == 'ESC':
                            res_str = 'ESC'
                        else:
                            res_str = rrest[:25]
                    else:
                        res_str = '?'

                    # Mark timing issues
                    mark = ''
                    if isinstance(elapsed, int) and isinstance(gv, int):
                        if elapsed < gv:
                            mark = ' ⛔'
                        elif elapsed < gv + 10:
                            mark = ' ⚠️'

                    print(f'    {ci+1:4d} {str(pt):>6} {str(fi):>2}  {str(sync):>5} {str(cyc):>5} {str(gv):>5} │ {str(target):>6} {str(post):>6} {str(elapsed):>7} {str(us):>6} │ {res_str}{mark}')
                    printed += 1

        elif not total_timed:
            # Old format without timing data
            print('    ℹ️  Тайминг-данные отсутствуют (старый формат лога без FIRE/WAIT).')
            print('    Для анализа тайминга соберите лог с 32-bit сборкой (TRACE включён).')

            # Still analyze retry patterns from old log
            retry_shots = [e for e in s.events if e.tag in ('LPULS','METAL') and e.data.get('_sub') == 'retry']
            ok_shots = [e for e in s.events if e.tag in ('LPULS','METAL') and e.data.get('_sub') == 'ok']
            fail_shots = [e for e in s.events if e.tag in ('LPULS','METAL') and e.data.get('_sub') == 'FAIL']

            if retry_shots:
                print(f'\n    Повторов: {len(retry_shots)}, OK: {len(ok_shots)}, FAIL: {len(fail_shots)}')
                # Check dsens pattern
                dsens_zero = sum(1 for e in retry_shots if e.data.get('dsens', -1) in (0, '0', '0000'))
                if dsens_zero == len(retry_shots) and retry_shots:
                    print(f'    ⛔ ВСЕ {dsens_zero} повторов с dsens=0 — типичный признак')
                    print(f'       проблемы тайминга: gate не успевает отработать до проверки')
                    print(f'       (оригинальная проблема delay(1) в 32-bit порте)')
        else:
            print(f'    ✅ Все {total_timed} выстрелов с нормальным таймингом, проблем нет.\n')

        print()


def report_full(events, sessions):
    """Полный отчёт: сводка + проблемы + хронология (без PT/MOV шума)."""
    report_summary(events, sessions)
    report_problems(events, sessions)

    print_header('ХРОНОЛОГИЯ (ключевые события)')
    print()

    for ev in events:
        desc = describe_event(ev)
        if desc is not None:
            print(f'  [{ev.line_no:5d}] {desc}')


# ═══════════════════════════════════════════════════
#  main
# ═══════════════════════════════════════════════════

def main():
    # Принудительно UTF-8 на выходе (Windows cp1251 ломает кириллицу и символы)
    import io
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

    parser = argparse.ArgumentParser(
        description='Полный анализатор FLINT.LOG — понятные отчёты на русском',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Примеры:
  python flint_log.py FLINT.LOG                # полный отчёт
  python flint_log.py FLINT.LOG --shots        # анализ выстрелов
  python flint_log.py FLINT.LOG --problems     # только проблемы
  python flint_log.py FLINT.LOG --timeline     # хронология
  python flint_log.py FLINT.LOG --config       # история конфигурации
  python flint_log.py FLINT.LOG --points       # таблица точек
        """)
    parser.add_argument('logfile', help='Путь к FLINT.LOG')
    parser.add_argument('--timeline', action='store_true', help='Хронология всех событий')
    parser.add_argument('--shots', action='store_true', help='Подробный анализ выстрелов')
    parser.add_argument('--points', action='store_true', help='Таблица обработанных точек')
    parser.add_argument('--config', action='store_true', help='История конфигурации')
    parser.add_argument('--timing', action='store_true', help='Тайминг pump+gate по каждому выстрелу')
    parser.add_argument('--problems', action='store_true', help='Только проблемы')
    parser.add_argument('--hw', action='store_true', help='Аппаратный I/O: PT2, LRG, SH, RG(моторы), PPI2(protect)')
    parser.add_argument('--output', '-o', help='Записать отчёт в файл (UTF-8)')
    args = parser.parse_args()

    # Перенаправление в файл
    close_fh = None
    if args.output:
        fh = open(args.output, 'w', encoding='utf-8')
        sys.stdout = fh
        close_fh = fh

    events = parse_log(args.logfile)
    sessions = group_sessions(events)

    if args.timeline:
        report_timeline(events)
    elif args.shots:
        report_shots(events, sessions)
    elif args.timing:
        report_timing(events, sessions)
    elif args.points:
        report_points(events)
    elif args.config:
        report_config(events)
    elif args.problems:
        report_problems(events, sessions)
    elif args.hw:
        report_hw(events)
    else:
        report_full(events, sessions)

    print()

    if close_fh:
        close_fh.close()


if __name__ == '__main__':
    main()
