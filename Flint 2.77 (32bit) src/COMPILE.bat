@echo off
:: ═══════════════════════════════════════════════
::   Компиляция FLINT+ v2.77 (32-bit)
::   Автоопределение среды:
::     DOS / Windows 9x — Watcom binw (DOS)
::     Windows NT+      — Watcom binnt (Win32)
:: ═══════════════════════════════════════════════
:: Компилятор: Open Watcom C++ wpp386
:: Флаги:
::   -bt=dos  Целевая платформа DOS
::   -mf      Flat memory model 32-bit
::   -ox      Максимальная оптимизация
::   -w3      Уровень предупреждений 3
:: Линковка:
::   wlink system dos4g — расширитель памяти DOS/4GW
:: ═══════════════════════════════════════════════
if "%OS%"=="Windows_NT" goto NT_COMPILE

:: ─────────────────────────────────────────────
::  DOS / Windows 9x — нативная компиляция
::  Запускать из папки с исходниками
:: ─────────────────────────────────────────────
echo ===================================
echo   Компиляция FLINT+ v2.77 (32-bit)
echo ===================================

:: Поиск Watcom: WATCOM (если задана) -> ..\Tools\WATCOM -> C:\WATCOM
if not "%WATCOM%"=="" goto CHECK_WATCOM
if exist ..\Tools\WATCOM\binw\wpp386.exe set WATCOM=..\Tools\WATCOM
if not "%WATCOM%"=="" goto CHECK_WATCOM
if exist C:\WATCOM\binw\wpp386.exe set WATCOM=C:\WATCOM
if not "%WATCOM%"=="" goto CHECK_WATCOM
goto NO_WATCOM

:CHECK_WATCOM
if not exist %WATCOM%\binw\wpp386.exe goto NO_WATCOM
echo Компилятор: Open Watcom C++ (%WATCOM%)

:: Настройка окружения Watcom (DOS — используем binw)
set PATH=%WATCOM%\binw;%PATH%
set INCLUDE=%WATCOM%\h
set LIB=%WATCOM%\lib386\dos
echo.

:: Путь к данным Flint 2.77
if "%FLINTDIR%"=="" set FLINTDIR=..\!GENESIS\Flint 2.77

:: Компиляция
echo Компиляция...
wmake -f MAKEFILE
if errorlevel 1 goto COMPILE_FAIL

if not exist PROJ5.EXE goto COMPILE_FAIL
echo.
echo *** Компиляция успешна ***

:: Сборка папки BUILD
echo Сборка папки BUILD...
if not exist BUILD mkdir BUILD
copy PROJ5.EXE BUILD\ >nul
del PROJ5.EXE

:: Копируем DOS/4GW
if exist %WATCOM%\binw\dos4gw.exe copy %WATCOM%\binw\dos4gw.exe BUILD\ >nul

:: Удаляем промежуточные файлы
if exist *.OBJ del *.OBJ
if exist *.ERR del *.ERR
if exist DEBUG.LOG del DEBUG.LOG

:: Копируем данные из Flint 2.77
if exist %FLINTDIR%\FLINT.GLS copy %FLINTDIR%\FLINT.GLS BUILD\ >nul
if exist %FLINTDIR%\FLINT1.CFG copy %FLINTDIR%\FLINT1.CFG BUILD\ >nul
if exist %FLINTDIR%\FLINT9.CFG copy %FLINTDIR%\FLINT9.CFG BUILD\ >nul
if exist %FLINTDIR%\FLASH.DAT copy %FLINTDIR%\FLASH.DAT BUILD\ >nul
if exist %FLINTDIR%\CONFIG.SYS copy %FLINTDIR%\CONFIG.SYS BUILD\ >nul
if exist %FLINTDIR%\BFT_FILES xcopy /E /I %FLINTDIR%\BFT_FILES BUILD\BFT_FILES >nul

:: Генерация BUILD\RUN.bat (только DOS — без dosbox-x.conf)
echo @echo off > BUILD\RUN.bat
echo if not exist PROJ5.EXE goto NO_EXE >> BUILD\RUN.bat
echo if not exist DOS4GW.EXE goto NO_DOS4GW >> BUILD\RUN.bat
echo PROJ5.EXE >> BUILD\RUN.bat
echo goto END >> BUILD\RUN.bat
echo :NO_EXE >> BUILD\RUN.bat
echo echo PROJ5.EXE not found. >> BUILD\RUN.bat
echo pause >> BUILD\RUN.bat
echo goto END >> BUILD\RUN.bat
echo :NO_DOS4GW >> BUILD\RUN.bat
echo echo DOS4GW.EXE not found. >> BUILD\RUN.bat
echo pause >> BUILD\RUN.bat
echo :END >> BUILD\RUN.bat

echo.
echo Готово! Папка BUILD создана.
echo Для запуска: BUILD\RUN.bat
pause
goto END

:NO_WATCOM
echo ОШИБКА: Open Watcom C++ не найден.
echo Укажите путь: SET WATCOM=C:\WATCOM
echo и запустите скрипт повторно.
pause
goto END

:COMPILE_FAIL
echo.
echo ОШИБКА: Компиляция не удалась.
if exist *.OBJ del *.OBJ
if exist *.ERR del *.ERR
pause
goto END

:: ─────────────────────────────────────────────
::  Windows NT+ — нативная компиляция (Watcom)
:: ─────────────────────────────────────────────
:NT_COMPILE
chcp 65001 >nul
echo ═══════════════════════════════════════════
echo   Компиляция FLINT+ v2.77 (32-bit)
echo ═══════════════════════════════════════════

set "SRCDIR=%~dp0."
set "FLINTDIR=%~dp0..\!GENESIS\Flint 2.77"
set "TOOLSDIR=%~dp0..\Tools"
set "BUILDDIR=%~dp0BUILD"
set "WATCOM=%~dp0..\Tools\WATCOM"

:: ────────────────────────────────────────────
:: Компилятор: Open Watcom C++ wpp386
:: Флаги:
::   -bt=dos  Целевая платформа DOS
::   -mf      Flat memory model 32-bit
::   -ox      Максимальная оптимизация
::   -w3      Уровень предупреждений 3
:: Линковка:
::   wlink system dos4g — расширитель памяти DOS/4GW
:: ────────────────────────────────────────────

rem --- Поиск Watcom ---
if not exist "%WATCOM%\binnt\wpp386.exe" goto :no_watcom

rem --- Настройка окружения Watcom ---
set "PATH=%WATCOM%\binnt;%WATCOM%\binw;%PATH%"
set "INCLUDE=%WATCOM%\h"
set "WATCOM_DIR=%WATCOM%"
set "LIB=%WATCOM%\lib386\dos"

echo Компилятор: Open Watcom C++
echo Исходники:  %SRCDIR%
echo.

rem --- Компиляция ---
cd /d "%SRCDIR%"
echo Компиляция...
wmake -f MAKEFILE
if errorlevel 1 goto :compile_fail

echo.
if not exist "%SRCDIR%\proj5.exe" goto :no_exe

:: Собираем готовую папку BUILD с EXE и данными для запуска
echo Сборка папки BUILD...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

:: Копируем скомпилированный EXE и DOS/4GW
move /Y "%SRCDIR%\proj5.exe" "%BUILDDIR%\" >nul
copy /Y "%WATCOM%\binw\dos4gw.exe" "%BUILDDIR%\" >nul

:: Удаляем промежуточные файлы
del /Q "%SRCDIR%\*.obj" >nul 2>nul
del /Q "%SRCDIR%\*.err" >nul 2>nul
del /Q "%SRCDIR%\DEBUG.LOG" >nul 2>nul

:: Копируем данные из Flint 2.77
copy /Y "%FLINTDIR%\FLINT.GLS"  "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT1.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT9.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLASH.DAT"  "%BUILDDIR%\" >nul 2>nul
copy /Y "%FLINTDIR%\CONFIG.SYS" "%BUILDDIR%\" >nul 2>nul

:: Копируем BFT-файлы, если есть
if not exist "%FLINTDIR%\BFT_FILES" goto :skip_bft
xcopy /E /I /Y "%FLINTDIR%\BFT_FILES" "%BUILDDIR%\BFT_FILES" >nul
:skip_bft

:: Генерируем dosbox-x.conf внутри BUILD
>"%BUILDDIR%\dosbox-x.conf" echo [dosbox]
>>"%BUILDDIR%\dosbox-x.conf" echo memsize=64
>>"%BUILDDIR%\dosbox-x.conf" echo machine=svga_s3
>>"%BUILDDIR%\dosbox-x.conf" echo.
>>"%BUILDDIR%\dosbox-x.conf" echo [cpu]
>>"%BUILDDIR%\dosbox-x.conf" echo core=dynamic
>>"%BUILDDIR%\dosbox-x.conf" echo cputype=pentium
>>"%BUILDDIR%\dosbox-x.conf" echo cycles=max
>>"%BUILDDIR%\dosbox-x.conf" echo.
>>"%BUILDDIR%\dosbox-x.conf" echo [render]
>>"%BUILDDIR%\dosbox-x.conf" echo aspect=true

:: Генерируем двухрежимный RUN.bat внутри BUILD
>"%BUILDDIR%\RUN.bat" echo @echo off
>>"%BUILDDIR%\RUN.bat" echo if "%%OS%%"=="Windows_NT" goto NT_RUN
>>"%BUILDDIR%\RUN.bat" echo if not exist PROJ5.EXE goto NO_EXE
>>"%BUILDDIR%\RUN.bat" echo if not exist DOS4GW.EXE goto NO_DOS4GW
>>"%BUILDDIR%\RUN.bat" echo PROJ5.EXE
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NT_RUN
>>"%BUILDDIR%\RUN.bat" echo chcp 65001 ^>nul
>>"%BUILDDIR%\RUN.bat" echo set "FLINTDIR=%%~dp0..\..\!GENESIS\Flint 2.77"
>>"%BUILDDIR%\RUN.bat" echo set "DOSBOX=%%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo for %%%%I in ^(dosbox-x.exe^) do if not "%%%%~$PATH:I"=="" set "DOSBOX=%%%%~$PATH:I"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo echo ERROR: DOSBox-X not found. ^& pause ^& exit /b 1
>>"%BUILDDIR%\RUN.bat" echo :DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo "%%DOSBOX%%" -conf "%%~dp0dosbox-x.conf" -c "MOUNT C \"%%~dp0.\"" -c "C:" -c "PROJ5.EXE" -c "echo." -c "echo Program finished. Press any key..." -c "pause" -c "EXIT"
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLINT1.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLINT9.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLASH.DAT"  "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NO_EXE
>>"%BUILDDIR%\RUN.bat" echo echo PROJ5.EXE not found. ^& pause
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NO_DOS4GW
>>"%BUILDDIR%\RUN.bat" echo echo DOS4GW.EXE not found. ^& pause
>>"%BUILDDIR%\RUN.bat" echo :END

echo.
echo ═══════════════════════════════════════════
echo   Готово! Папка BUILD создана.
echo   Для запуска — двойной клик на BUILD\RUN.bat
echo ═══════════════════════════════════════════
pause
goto END

:no_watcom
echo ОШИБКА: Open Watcom не найден в %WATCOM%
echo Нужен wpp386.exe в %WATCOM%\binnt\
pause
exit /b 1

:compile_fail
echo.
echo ОШИБКА: Компиляция не удалась!
pause
exit /b 1

:no_exe
echo ОШИБКА: proj5.exe не создан. Проверьте вывод компилятора.
pause
exit /b 1

:END
