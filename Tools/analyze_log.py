#!/usr/bin/env python3
"""
analyze_log.py - Анализатор FLINT.LOG
Парсит лог-файл, сгенерированный TRACE-системой в PIC.CPP (32-bit),
и выводит диагностику по Z-координатам, расстояниям между точками,
параметрам движения и т.д.

Использование:
    python analyze_log.py FLINT.LOG
    python analyze_log.py FLINT.LOG --points       # детальная таблица точек
    python analyze_log.py FLINT.LOG --moves        # детальная таблица move()
    python analyze_log.py FLINT.LOG --z-histogram  # гистограмма Z-зазоров
"""
import sys
import re
import argparse
from collections import Counter, defaultdict


def parse_log(filepath):
    """Парсит FLINT.LOG и возвращает структурированные данные."""
    proc_cfg = {}
    proc_calc = {}
    proc_start = {}
    points = []      # список dict: i, raw_x, raw_y, raw_z, x, y, z, dx, dy, dz
    moves = []       # список dict: dx, dy, dz, tseg, k2x, k2y, k2z
    events = []      # прочие события: LPULS, METAL, ERR, ESC, END

    with open(filepath, 'r') as f:
        for line in f:
            line = line.strip()

            # [PROC] START
            m = re.match(r'\[PROC\] START n=(\d+)/(\d+) metal=(\d+) dchk=(\d+) '
                         r'lper=(\d+) gate=(\d+) shd=(\d+)', line)
            if m:
                proc_start = {
                    'start_nmb': int(m.group(1)),
                    'nmax': int(m.group(2)),
                    'f_metal': int(m.group(3)),
                    'd_check': int(m.group(4)),
                    'l_period': int(m.group(5)),
                    'gate_delay': int(m.group(6)),
                    'sh_delay': int(m.group(7)),
                }
                continue

            # [PROC] CFG
            m = re.match(r'\[PROC\] CFG xptr=(-?\d+) yptr=(-?\d+) zptr=(-?\d+) '
                         r'zsize=(-?\d+) nglas=([\d.]+) step=(\d+) sf=(\d+) '
                         r'dT=(\d+) fc=(\d+) demo=(\d+)', line)
            if m:
                proc_cfg = {
                    'xptr': int(m.group(1)),
                    'yptr': int(m.group(2)),
                    'zptr': int(m.group(3)),
                    'zsize': int(m.group(4)),
                    'nglas': float(m.group(5)),
                    'step': int(m.group(6)),
                    'step_freq': int(m.group(7)),
                    'dT': int(m.group(8)),
                    'f_const': int(m.group(9)),
                    'f_demo': int(m.group(10)),
                }
                continue

            # [PROC] CALC
            m = re.match(r'\[PROC\] CALC refr_ofs=(-?\d+) z_base=(-?\d+)', line)
            if m:
                proc_calc = {
                    'refr_ofs': int(m.group(1)),
                    'z_base': int(m.group(2)),
                }
                continue

            # [PT] per-point
            m = re.match(r'\[PT\] i=(\d+) raw=(-?\d+),(-?\d+),(-?\d+) '
                         r'xyz=(-?\d+),(-?\d+),(-?\d+) d=(-?\d+),(-?\d+),(-?\d+)', line)
            if m:
                points.append({
                    'i': int(m.group(1)),
                    'raw_x': int(m.group(2)),
                    'raw_y': int(m.group(3)),
                    'raw_z': int(m.group(4)),
                    'x': int(m.group(5)),
                    'y': int(m.group(6)),
                    'z': int(m.group(7)),
                    'dx': int(m.group(8)),
                    'dy': int(m.group(9)),
                    'dz': int(m.group(10)),
                })
                continue

            # [MOV] per-move
            m = re.match(r'\[MOV\] dx=(-?\d+) dy=(-?\d+) dz=(-?\d+) '
                         r'tseg=(\d+) k2x=(\d+) k2y=(\d+) k2z=(\d+)', line)
            if m:
                moves.append({
                    'dx': int(m.group(1)),
                    'dy': int(m.group(2)),
                    'dz': int(m.group(3)),
                    'tseg': int(m.group(4)),
                    'k2x': int(m.group(5)),
                    'k2y': int(m.group(6)),
                    'k2z': int(m.group(7)),
                })
                continue

            # Other events
            if line.startswith('['):
                events.append(line)

    return proc_start, proc_cfg, proc_calc, points, moves, events


def print_summary(proc_start, proc_cfg, proc_calc, points, moves, events):
    """Выводит общую сводку."""
    print("=" * 70)
    print("  FLINT.LOG — Сводка")
    print("=" * 70)

    if proc_start:
        print(f"\n--- Параметры процесса ---")
        print(f"  Точек: {proc_start['start_nmb']}..{proc_start['nmax']} "
              f"(всего {proc_start['nmax'] - proc_start['start_nmb']})")
        print(f"  metal={proc_start['f_metal']}  d_check={proc_start['d_check']}")
        print(f"  l_period={proc_start['l_period']}  gate_delay={proc_start['gate_delay']}  "
              f"sh_delay={proc_start['sh_delay']}")

    if proc_cfg:
        print(f"\n--- Конфигурация ---")
        print(f"  xptr={proc_cfg['xptr']}  yptr={proc_cfg['yptr']}  zptr={proc_cfg['zptr']}")
        print(f"  zsize={proc_cfg['zsize']}  nglas={proc_cfg['nglas']:.4f}")
        print(f"  step={proc_cfg['step']}  step_freq={proc_cfg['step_freq']}  "
              f"dT={proc_cfg['dT']}  f_const={proc_cfg['f_const']}")
        print(f"  demo={proc_cfg['f_demo']}")

    if proc_calc:
        print(f"\n--- Расчётные значения ---")
        print(f"  refr_ofs = zsize*10*(1-1/nglas) = {proc_calc['refr_ofs']}")
        print(f"  z_base = 11000 - zptr - refr_ofs = {proc_calc['z_base']}")
        print(f"  znew = z_base - iTabl[z]")

    if not points:
        print("\n(Точек в логе нет)")
        return

    print(f"\n--- Статистика точек ({len(points)} шт.) ---")

    # Z-анализ
    z_vals = [p['z'] for p in points]
    dz_vals = [p['dz'] for p in points]
    raw_z = [p['raw_z'] for p in points]

    z_min, z_max = min(z_vals), max(z_vals)
    print(f"  Z motor: min={z_min}  max={z_max}  range={z_max - z_min}")
    print(f"  Z raw (iTabl): min={min(raw_z)}  max={max(raw_z)}  range={max(raw_z)-min(raw_z)}")

    # Уникальные Z-слои
    z_unique = sorted(set(z_vals))
    print(f"  Уникальных Z-позиций: {len(z_unique)}")

    if len(z_unique) > 1:
        z_gaps = [z_unique[i+1] - z_unique[i] for i in range(len(z_unique)-1)]
        print(f"  Z-зазоры между слоями: min={min(z_gaps)}  max={max(z_gaps)}  "
              f"avg={sum(z_gaps)/len(z_gaps):.1f}")
        gap_counts = Counter(z_gaps)
        print(f"  Распределение Z-зазоров:")
        for gap, cnt in sorted(gap_counts.items()):
            print(f"    gap={gap} (×{cnt})")

    # dz при переходе между точками
    nonzero_dz = [d for d in dz_vals if d != 0]
    if nonzero_dz:
        abs_dz = [abs(d) for d in nonzero_dz]
        print(f"\n  dz (переходы) ненулевых: {len(nonzero_dz)}/{len(dz_vals)}")
        print(f"    |dz| min={min(abs_dz)}  max={max(abs_dz)}  avg={sum(abs_dz)/len(abs_dz):.1f}")

        if proc_cfg and proc_cfg['nglas'] > 0:
            ng = proc_cfg['nglas']
            print(f"\n  --- Реальное смещение фокуса в стекле (nglas={ng:.4f}) ---")
            for gap, cnt in sorted(Counter(nonzero_dz).items()):
                real_mm = gap / 10.0 / ng
                motor_mm = gap / 10.0
                print(f"    dz={gap} steps ({motor_mm:.2f}mm motor) → "
                      f"фокус в стекле: {real_mm:.3f}mm  (×{cnt})")

    # X/Y rangе
    x_vals = [p['x'] for p in points]
    y_vals = [p['y'] for p in points]
    print(f"\n  X motor: min={min(x_vals)}  max={max(x_vals)}  range={max(x_vals)-min(x_vals)}")
    print(f"  Y motor: min={min(y_vals)}  max={max(y_vals)}  range={max(y_vals)-min(y_vals)}")

    # Events summary
    err_events = [e for e in events if 'ERR' in e or 'FAIL' in e]
    esc_events = [e for e in events if 'ESC' in e]
    end_events = [e for e in events if '[PROC] END' in e]
    if end_events:
        print(f"\n  Завершение: {end_events[-1]}")
    if err_events:
        print(f"\n  !!! ОШИБКИ ({len(err_events)}):")
        for e in err_events[:10]:
            print(f"    {e}")
    if esc_events:
        print(f"\n  Прервано пользователем (ESC)")


def print_points_table(points):
    """Подробная таблица точек."""
    print(f"\n{'i':>6} {'raw_x':>6} {'raw_y':>6} {'raw_z':>6} | "
          f"{'x':>6} {'y':>6} {'z':>6} | {'dx':>6} {'dy':>6} {'dz':>6}")
    print("-" * 78)
    for p in points:
        print(f"{p['i']:6d} {p['raw_x']:6d} {p['raw_y']:6d} {p['raw_z']:6d} | "
              f"{p['x']:6d} {p['y']:6d} {p['z']:6d} | "
              f"{p['dx']:6d} {p['dy']:6d} {p['dz']:6d}")


def print_moves_table(moves):
    """Подробная таблица move()."""
    print(f"\n{'#':>6} {'dx':>6} {'dy':>6} {'dz':>6} | "
          f"{'tseg':>5} {'k2x':>7} {'k2y':>7} {'k2z':>7}")
    print("-" * 65)
    for idx, m in enumerate(moves):
        print(f"{idx:6d} {m['dx']:6d} {m['dy']:6d} {m['dz']:6d} | "
              f"{m['tseg']:5d} {m['k2x']:7d} {m['k2y']:7d} {m['k2z']:7d}")


def print_z_histogram(points):
    """Гистограмма Z-зазоров между последовательными точками."""
    if len(points) < 2:
        print("Недостаточно точек для гистограммы.")
        return

    dz_vals = [points[i+1]['z'] - points[i]['z'] for i in range(len(points)-1)]
    dz_counts = Counter(dz_vals)

    print(f"\n--- Гистограмма dz (Z[i+1] - Z[i]) для {len(dz_vals)} переходов ---")
    print(f"{'dz':>7} {'count':>7}  {'bar'}")
    print("-" * 50)
    max_count = max(dz_counts.values())
    for dz_val in sorted(dz_counts.keys()):
        cnt = dz_counts[dz_val]
        bar_len = int(cnt / max_count * 40) if max_count > 0 else 0
        print(f"{dz_val:7d} {cnt:7d}  {'█' * bar_len}")

    # Группировка: только-Z переходы vs смешанные
    z_only = sum(1 for p in points[1:] if p['dx'] == 0 and p['dy'] == 0 and p['dz'] != 0)
    mixed = sum(1 for p in points[1:] if p['dz'] != 0 and (p['dx'] != 0 or p['dy'] != 0))
    xy_only = sum(1 for p in points[1:] if p['dz'] == 0 and (p['dx'] != 0 or p['dy'] != 0))
    print(f"\n  Переходы только по Z: {z_only}")
    print(f"  Переходы Z+XY: {mixed}")
    print(f"  Переходы только XY (dz=0): {xy_only}")


def main():
    parser = argparse.ArgumentParser(description='Анализатор FLINT.LOG')
    parser.add_argument('logfile', help='Путь к FLINT.LOG')
    parser.add_argument('--points', action='store_true', help='Показать таблицу точек')
    parser.add_argument('--moves', action='store_true', help='Показать таблицу move()')
    parser.add_argument('--z-histogram', action='store_true', help='Гистограмма Z-зазоров')
    args = parser.parse_args()

    proc_start, proc_cfg, proc_calc, points, moves, events = parse_log(args.logfile)
    print_summary(proc_start, proc_cfg, proc_calc, points, moves, events)

    if args.z_histogram:
        print_z_histogram(points)
    if args.points:
        print_points_table(points)
    if args.moves:
        print_moves_table(moves)


if __name__ == '__main__':
    main()
