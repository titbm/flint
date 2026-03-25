# Содержимое папки Tools

Папка содержит инструменты для сборки программы, запуска в DOS-эмуляторе и вспомогательные Python-скрипты.

---

## Python-скрипты

| Файл | Назначение |
|------|------------|
| `generate_screenshots.py` | Генерирует скриншоты всех диалогов программы **программно** — воссоздаёт интерфейс по определениям кнопок из `PROJ5.CPP`/`PROJ5.H` с использованием Python PIL. Разрешение 640×480, расширенная EGA-палитра. Результат — PNG-файлы в `Help/screenshots/` |
| `replace_screenshots.py` | Заменяет base64-закодированные изображения, **встроенные внутрь `FLINT_Help.html`**, новыми PNG-файлами из `Help/screenshots/`. Обходит совпадения справа налево, чтобы не сбить позиции |
| `fix_hotspots.py` | Применяет к `FLINT_Help.html` набор исправлений позиций хотспотов: сдвиги координат, удаление устаревших и добавление новых `<div class="hotspot">`, обновление счётчиков строк в таблицах описаний (секции MAINSCR, CONFIG, MSGBOX) |

---

## BC45/

Минимальный набор файлов из **Borland C++ 4.5** для компиляции **16-битной** версии программы (`Flint 2.77 src/`). Содержит только то, что необходимо для сборки — не весь дистрибутив Borland.

Borland C++ 4.5 доступен на [WinWorld](https://winworldpc.com/product/borland-c/40):
[прямая ссылка на скачивание (CD-образ)](https://winworldpc.com/download/c2a44ac3-a459-4f66-11c3-a5c28fc2a3ef/from/c39ac2af-c381-c2bf-1b25-11c3a4e284a2)

| Папка / файл | Содержимое |
|--------------|------------|
| `BIN/BCC.EXE` | Компилятор Borland C++ 16-bit |
| `BIN/CPP.EXE` | Препроцессор |
| `BIN/TLINK.EXE` | Компоновщик (16-bit) |
| `BIN/RTM.EXE` | DPMI Runtime Manager |
| `BIN/DPMI16BI.OVL` | DPMI16 хост (нужен RTM при запуске BCC в DOS) |
| `BIN/DPMI32VM.OVL` | DPMI32 хост |
| `BGI/EGAVGA.BGI` | BGI-драйвер EGA/VGA (нужен при запуске готовой программы) |
| `BGI/BGIOBJ.EXE` | Утилита конвертации BGI-драйвера в OBJ для линковки |
| `INCLUDE/` | Заголовочные файлы стандартной библиотеки |
| `LIB/` | Библиотеки для 16-битных DOS-программ |
| `SRC/` | (пусто) |

---

## BC45_32/

Минимальный набор файлов для компиляции **32-битной BCC32-версии** программы (`Flint 2.77 (BCC32) src/`). Собран из файлов Borland C++ 4.5 и установленного **Borland PowerPack for DOS 1.0a** с тремя применёнными патчами.

PowerPack и патчи доступны на [old-dos.ru](http://old-dos.ru/index.php?page=files&mode=files&do=show&id=2139):
- [прямая ссылка на PowerPack](http://old-dos.ru/dl.php?id=4247)
- [прямая ссылка на патчи](http://old-dos.ru/dl.php?id=38609)

| Папка / файл | Содержимое |
|--------------|------------|
| `BIN/BCC32.EXE` | Компилятор Borland C++ 32-bit (DPMI) |
| `BIN/BCC32A.EXE` | Вспомогательный вариант компилятора |
| `BIN/BCC32.CFG` | Конфигурация компилятора (пути include/lib) |
| `BIN/CPP32.EXE` | Препроцессор 32-bit |
| `BIN/TLINK32.EXE` | Компоновщик 32-bit |
| `BIN/TLINK32.CFG` | Конфигурация компоновщика |
| `BIN/TLIB.EXE` | Утилита управления библиотеками |
| `BIN/32RTM.EXE` | DPMI32 Runtime Manager (нужен для запуска собранного EXE) |
| `BIN/32STUB.EXE` | Stub-загрузчик для 32-bit DOS-приложений |
| `BIN/RTM.EXE` | DPMI Runtime Manager 16-bit |
| `BIN/DPMI16BI.OVL` | DPMI16 хост |
| `BIN/DPMI32VM.OVL` | DPMI32 хост |
| `BIN/MAKE.EXE` | Утилита сборки |
| `BIN/TD32.EXE` | Turbo Debugger 32-bit |
| `BIN/TDUMP.EXE` | Дамп объектных файлов |
| `BIN/TDXDEBUG.DLL` | DLL Turbo Debugger |
| `BGI/BGI32.DLL` + `BGIVGA.DLL` | BGI-библиотека для 32-bit (DLL-форма, нужна при запуске) |
| `BGI/` (прочее) | Остальные BGI32 DLL-драйверы и шрифты |
| `INCLUDE/` | Заголовочные файлы (Borland + PowerPack) |
| `LIB/` | Библиотеки для 32-bit DOS-программ |

---

## WATCOM/

Минимальный набор файлов из **OpenWatcom** для компиляции **32-битной Watcom-версии** программы (`Flint 2.77 (WTCM32) src/`).

OpenWatcom для DOS можно найти на [win3x.org](http://www.win3x.org/win3board/viewtopic.php?t=3671&view=min).

| Папка / файл | Содержимое |
|--------------|------------|
| `binnt/wpp386.exe` | Компилятор C++ (32-bit, запуск под Windows NT/XP) |
| `binnt/wlink.exe` | Компоновщик |
| `binnt/wmake.exe` | Утилита сборки |
| `binnt/wstub.exe` | DOS-заглушка для 32-bit приложений |
| `binnt/wpp38601.int` | Языковые ресурсы компилятора |
| `binnt/wppd386.dll` + `wlinkd.dll` | DLL компилятора и компоновщика |
| `binw/dos4gw.exe` | DOS/4GW DPMI-расширитель (нужен при запуске собранного EXE) |
| `binw/wstub.exe` | DOS-заглушка (вариант для DOS-хоста) |
| `h/` | Заголовочные файлы стандартной библиотеки Watcom |
| `lib386/` | Библиотеки для 32-bit (DOS4G и flat-модель) |

---

## DOSBox-X/

Полная установка **DOSBox-X** — DOS-эмулятор с расширенной поддержкой аппаратного ввода-вывода (ISA-порты, реальные таймеры), использующийся для запуска и тестирования программы.

| Файл / папка | Содержимое |
|--------------|------------|
| `dosbox-x.exe` | Исполняемый файл DOSBox-X |
| `dosbox-x.conf` | Конфигурация проекта: настройки машины, маппинг дисков |
| `dosbox-x.reference.conf` | Справочная конфигурация (краткая) |
| `dosbox-x.reference.full.conf` | Полная справочная конфигурация со всеми параметрами |
| `drivez/README.TXT` | Описание виртуального диска Z: (встроен в DOSBox-X) |
| `inpout32.dll` / `inpoutx64.dll` | Драйверы прямого доступа к портам ввода-вывода (нужны для работы с ISA-платой из Windows) |
| `glshaders/`, `shaders/` | Шейдеры для рендеринга экрана |
| `languages/`, `scripts/` | Локализации и сценарии запуска |
| `Nouveau_IBM.ttf`, `SarasaGothicFixed.ttf`, `FREECG98.BMP`, `wqy_*.bdf` | Шрифты |
