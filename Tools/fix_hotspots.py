#!/usr/bin/env python3
"""
fix_hotspots.py — Apply all hotspot position fixes to FLINT_Help.html.

Changes:
  MAINSCR section:
    - 10 position changes (F9 XYZ, F1-F5, Nmax, Nlast, Panel, Demo)
    - 1 removal ("Максимальное количество точек" hotspot + table row)
    - 4 new hotspots (Версия 2.77, Dr.check, Сетка реитераций, Оценка времени)
    - Table count 19 -> 22, renumber rows after removal

  CONFIG section:
    - 1 position change (Save .cfg left:120->130)
    - 1 removal (Las.adjust hotspot div only, no table entry)
    - 3 new hotspots (Gate delay, Laser pump, Кнопка X)

  START section:
    - (buttons already at correct positions: + at top:140, - at top:160)

  MSGBOX section:
    - 1 new hotspot (Nx button)
    - Table count 2 -> 3, add Nx row
"""

import os
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(SCRIPT_DIR)
HTML_PATH = os.path.join(PROJECT_ROOT, "Help", "FLINT_Help.html")


def apply_replacements(html: str) -> str:
    """Apply all hotspot fixes via string replacements."""

    changes = []

    # ========================================================================
    # MAINSCR — Position Changes (10 items)
    # ========================================================================

    # 1. F9 XYZ
    changes.append((
        'style="left:40px;top:430px;width:90px;height:18px;" data-tip="F9 XYZ',
        'style="left:520px;top:380px;width:90px;height:18px;" data-tip="F9 XYZ',
    ))

    # 2. F1 Config
    changes.append((
        'style="left:520px;top:160px;width:90px;height:18px;" data-tip="F1 Config',
        'style="left:520px;top:210px;width:90px;height:18px;" data-tip="F1 Config',
    ))

    # 3. F2 Convert
    changes.append((
        'style="left:520px;top:190px;width:90px;height:18px;" data-tip="F2 Convert',
        'style="left:520px;top:240px;width:90px;height:18px;" data-tip="F2 Convert',
    ))

    # 4. F3 DatLoad
    changes.append((
        'style="left:520px;top:220px;width:90px;height:18px;" data-tip="F3 DatLoad',
        'style="left:520px;top:270px;width:90px;height:18px;" data-tip="F3 DatLoad',
    ))

    # 5. F4 GlsLoad
    changes.append((
        'style="left:520px;top:280px;width:90px;height:18px;" data-tip="F4 GlsLoad',
        'style="left:520px;top:320px;width:90px;height:18px;" data-tip="F4 GlsLoad',
    ))

    # 6. F5 Start
    changes.append((
        'style="left:520px;top:310px;width:90px;height:18px;" data-tip="F5 Start',
        'style="left:520px;top:350px;width:90px;height:18px;" data-tip="F5 Start',
    ))

    # 7. Nmax
    changes.append((
        'style="left:20px;top:145px;width:120px;height:12px;" data-tip="Nmax',
        'style="left:20px;top:175px;width:120px;height:12px;" data-tip="Nmax',
    ))

    # 8. Nlast
    changes.append((
        'style="left:20px;top:164px;width:70px;height:20px;" data-tip="Nlast',
        'style="left:20px;top:194px;width:70px;height:20px;" data-tip="Nlast',
    ))

    # 9. Панель параметров
    changes.append((
        'style="left:20px;top:230px;width:80px;height:115px;" data-tip="\u041f\u0430\u043d\u0435\u043b\u044c \u043f\u0430\u0440\u0430\u043c\u0435\u0442\u0440\u043e\u0432',
        'style="left:20px;top:260px;width:76px;height:84px;" data-tip="\u041f\u0430\u043d\u0435\u043b\u044c \u043f\u0430\u0440\u0430\u043c\u0435\u0442\u0440\u043e\u0432',
    ))

    # 10. Demo
    changes.append((
        'style="left:30px;top:360px;width:50px;height:12px;" data-tip="Demo',
        'style="left:565px;top:85px;width:50px;height:12px;" data-tip="Demo',
    ))

    # ========================================================================
    # MAINSCR — Remove hotspot div for "Максимальное количество точек"
    # ========================================================================
    changes.append((
        '        <div class="hotspot" style="left:20px;top:380px;width:100px;height:12px;" data-tip="\u041c\u0430\u043a\u0441\u0438\u043c\u0430\u043b\u044c\u043d\u043e\u0435 \u043a\u043e\u043b\u0438\u0447\u0435\u0441\u0442\u0432\u043e \u0442\u043e\u0447\u0435\u043a (\u0437\u0430\u0432\u0438\u0441\u0438\u0442 \u043e\u0442 \u0434\u043e\u0441\u0442\u0443\u043f\u043d\u043e\u0439 \u043f\u0430\u043c\u044f\u0442\u0438)"></div>\n',
        '',
    ))

    # ========================================================================
    # MAINSCR — Add 4 new hotspot divs before tooltip
    # ========================================================================
    new_mainscr_hotspots = (
        '        <div class="hotspot" style="left:580px;top:55px;width:32px;height:12px;" '
            'data-tip="\u0412\u0435\u0440\u0441\u0438\u044f \u00ab2.77\u00bb \u2014 \u043d\u043e\u043c\u0435\u0440 \u0432\u0435\u0440\u0441\u0438\u0438 \u043d\u0430 \u0433\u043b\u0430\u0432\u043d\u043e\u043c \u044d\u043a\u0440\u0430\u043d\u0435"></div>\n'
        '        <div class="hotspot" style="left:30px;top:145px;width:80px;height:12px;" '
            'data-tip="\u0418\u043d\u0434\u0438\u043a\u0430\u0442\u043e\u0440 Dr.check \u2014 \u043a\u0440\u0430\u0441\u043d\u0430\u044f \u043f\u043e\u043b\u043e\u0441\u043a\u0430 \u043f\u0440\u0438 \u043e\u0448\u0438\u0431\u043a\u0435 \u043a\u043e\u043d\u0442\u0440\u043e\u043b\u044f"></div>\n'
        '        <div class="hotspot" style="left:10px;top:386px;width:120px;height:64px;" '
            'data-tip="\u0421\u0435\u0442\u043a\u0430 \u0440\u0435\u0438\u0442\u0435\u0440\u0430\u0446\u0438\u0439 3\u00d73 \u2014 \u0441\u0447\u0451\u0442\u0447\u0438\u043a\u0438 \u043f\u043e\u0432\u0442\u043e\u0440\u043d\u044b\u0445 \u043f\u0440\u043e\u0445\u043e\u0434\u043e\u0432 \u043f\u043e \u043f\u043e\u0437\u0438\u0446\u0438\u044f\u043c"></div>\n'
        '        <div class="hotspot" style="left:20px;top:235px;width:110px;height:12px;" '
            'data-tip="\u041e\u0446\u0435\u043d\u043a\u0430 \u0432\u0440\u0435\u043c\u0435\u043d\u0438 \u043e\u0431\u0440\u0430\u0431\u043e\u0442\u043a\u0438 (\u0447\u0430\u0441\u044b:\u043c\u0438\u043d\u0443\u0442\u044b:\u0441\u0435\u043a\u0443\u043d\u0434\u044b)"></div>\n'
    )
    changes.append((
        '        <div class="tooltip" id="tip-mainscr"></div>',
        new_mainscr_hotspots + '        <div class="tooltip" id="tip-mainscr"></div>',
    ))

    # ========================================================================
    # MAINSCR — Table: remove row 13, renumber, update count 19->22
    # ========================================================================

    # Remove "Максимальное количество точек" table row
    changes.append((
        '<tr><td>13</td><td>\u041c\u0430\u043a\u0441\u0438\u043c\u0430\u043b\u044c\u043d\u043e\u0435 \u043a\u043e\u043b\u0438\u0447\u0435\u0441\u0442\u0432\u043e \u0442\u043e\u0447\u0435\u043a (\u0437\u0430\u0432\u0438\u0441\u0438\u0442 \u043e\u0442 \u0434\u043e\u0441\u0442\u0443\u043f\u043d\u043e\u0439 \u043f\u0430\u043c\u044f\u0442\u0438)</td></tr>\n',
        '',
    ))

    # Renumber rows 14->13 ... 19->18
    for old_num in range(14, 20):
        new_num = old_num - 1
        # The mainscr table rows have unique descriptions, so searching by <td>N</td> in
        # the mainscr context should be safe. We include surrounding tags for specificity.
        changes.append((
            f'<tr><td>{old_num}</td>',
            f'<tr><td>{new_num}</td>',
        ))

    # Update count
    changes.append((
        '\u0422\u0430\u0431\u043b\u0438\u0446\u0430 \u044d\u043b\u0435\u043c\u0435\u043d\u0442\u043e\u0432 (19)',
        '\u0422\u0430\u0431\u043b\u0438\u0446\u0430 \u044d\u043b\u0435\u043c\u0435\u043d\u0442\u043e\u0432 (22)',
    ))

    # ========================================================================
    # CONFIG — Position Change: Save .cfg (left:120->130)
    # ========================================================================
    # Be careful to target the correct div — the one with top:386px (Save .cfg),
    # NOT the one with top:125px (Load .cfg).
    changes.append((
        'style="left:120px;top:386px;width:90px;height:18px;" data-tip="Save .cfg',
        'style="left:130px;top:386px;width:90px;height:18px;" data-tip="Save .cfg',
    ))

    # ========================================================================
    # CONFIG — Remove Las.adjust hotspot div
    # ========================================================================
    changes.append((
        '        <div class="hotspot" style="left:120px;top:205px;width:90px;height:18px;" data-tip="Las.adjust \u2014 \u043d\u0435\u043f\u0440\u0435\u0440\u044b\u0432\u043d\u0430\u044f \u0440\u0430\u0431\u043e\u0442\u0430 \u043b\u0430\u0437\u0435\u0440\u0430 \u0434\u043b\u044f \u043d\u0430\u0441\u0442\u0440\u043e\u0439\u043a\u0438 (\u0432\u044b\u0445\u043e\u0434 \u2014 \u043b\u044e\u0431\u0430\u044f \u043a\u043b\u0430\u0432\u0438\u0448\u0430)"></div>\n',
        '',
    ))

    # ========================================================================
    # CONFIG — Add 3 new hotspot divs before tooltip
    # ========================================================================
    new_config_hotspots = (
        '        <div class="hotspot" style="left:120px;top:185px;width:90px;height:12px;" '
            'data-tip="Gate delay \u2014 \u043d\u0430\u0441\u0442\u0440\u043e\u0439\u043a\u0430 \u0437\u0430\u0434\u0435\u0440\u0436\u043a\u0438 \u0437\u0430\u0442\u0432\u043e\u0440\u0430 (1\u201350, \u00d710 \u043c\u043a\u0441), \u043a\u043d\u043e\u043f\u043a\u0438 +/\u2212"></div>\n'
        '        <div class="hotspot" style="left:120px;top:200px;width:90px;height:12px;" '
            'data-tip="\u041f\u0435\u0440\u0435\u043a\u043b\u044e\u0447\u0430\u0442\u0435\u043b\u0438 Pump (\u043d\u0430\u043a\u0430\u0447\u043a\u0430) \u0438 Gate (\u0437\u0430\u0442\u0432\u043e\u0440)"></div>\n'
        '        <div class="hotspot" style="left:335px;top:344px;width:22px;height:14px;" '
            'data-tip="\u041a\u043d\u043e\u043f\u043a\u0430 \u00abX\u00bb \u2014 \u043e\u0447\u0438\u0441\u0442\u043a\u0430 \u043f\u043e\u0437\u0438\u0446\u0438\u0439 (glp9new=0)"></div>\n'
    )
    changes.append((
        '        <div class="tooltip" id="tip-config"></div>',
        new_config_hotspots + '        <div class="tooltip" id="tip-config"></div>',
    ))

    # ========================================================================
    # START — no changes needed (buttons at correct positions 140/160)
    # ========================================================================

    # + button: already at correct position top:140
    # changes.append((
    #     'style="left:345px;top:140px;width:22px;height:14px;" data-tip="+ \u2014',
    #     'style="left:345px;top:140px;width:22px;height:14px;" data-tip="+ \u2014',
    # ))

    # - button: already at correct position top:160
    # changes.append((
    #     'style="left:345px;top:160px;width:22px;height:14px;" data-tip="- \u2014',
    #     'style="left:345px;top:160px;width:22px;height:14px;" data-tip="- \u2014',
    # ))

    # ========================================================================
    # MSGBOX — Add 1 new hotspot div before tooltip
    # ========================================================================
    new_msgbox_hotspot = (
        '        <div class="hotspot" style="left:266px;top:322px;width:22px;height:14px;" '
            'data-tip="\u041a\u043d\u043e\u043f\u043a\u0430 \u00abNx\u00bb \u2014 \u043f\u0435\u0440\u0435\u0439\u0442\u0438 \u043a \u0441\u043b\u0435\u0434\u0443\u044e\u0449\u0435\u043c\u0443 \u043f\u0438\u043a\u0441\u0435\u043b\u044e (Next pixel)"></div>\n'
    )
    changes.append((
        '        <div class="tooltip" id="tip-msgbox"></div>',
        new_msgbox_hotspot + '        <div class="tooltip" id="tip-msgbox"></div>',
    ))

    # ========================================================================
    # MSGBOX — Table: update count 2->3, add Nx row
    # ========================================================================
    changes.append((
        '\u0422\u0430\u0431\u043b\u0438\u0446\u0430 \u044d\u043b\u0435\u043c\u0435\u043d\u0442\u043e\u0432 (2)',
        '\u0422\u0430\u0431\u043b\u0438\u0446\u0430 \u044d\u043b\u0435\u043c\u0435\u043d\u0442\u043e\u0432 (3)',
    ))

    # Add Nx row after No row
    changes.append((
        '<tr><td>2</td><td>No \u2014 \u043e\u0442\u043c\u0435\u043d\u0438\u0442\u044c \u0434\u0435\u0439\u0441\u0442\u0432\u0438\u0435</td></tr>',
        '<tr><td>2</td><td>No \u2014 \u043e\u0442\u043c\u0435\u043d\u0438\u0442\u044c \u0434\u0435\u0439\u0441\u0442\u0432\u0438\u0435</td></tr>\n'
        '<tr><td>3</td><td>Nx \u2014 \u043f\u0435\u0440\u0435\u0439\u0442\u0438 \u043a \u0441\u043b\u0435\u0434\u0443\u044e\u0449\u0435\u043c\u0443 \u043f\u0438\u043a\u0441\u0435\u043b\u044e (Next pixel)</td></tr>',
    ))

    # ========================================================================
    # Apply all changes
    # ========================================================================
    for i, (old, new) in enumerate(changes):
        count = html.count(old)
        if count == 0:
            print(f"  WARNING: Change #{i+1} — pattern NOT FOUND:")
            print(f"    old = {old[:80]}...")
            continue
        if count > 1:
            print(f"  WARNING: Change #{i+1} — pattern found {count} times (expected 1):")
            print(f"    old = {old[:80]}...")
            # Still apply — for simple row renumbering this should be OK
            # if uniquely numbered
        html = html.replace(old, new, 1)
        print(f"  OK: Change #{i+1} applied.")

    return html


def main():
    print(f"Reading {HTML_PATH}")
    with open(HTML_PATH, "r", encoding="utf-8") as f:
        html = f.read()

    original_len = len(html)
    print(f"  File size: {original_len} chars")

    print("Applying hotspot fixes...")
    html = apply_replacements(html)

    new_len = len(html)
    print(f"  New size: {new_len} chars (delta: {new_len - original_len:+d})")

    print(f"Writing {HTML_PATH}")
    with open(HTML_PATH, "w", encoding="utf-8") as f:
        f.write(html)

    print("Done.")


if __name__ == "__main__":
    main()
