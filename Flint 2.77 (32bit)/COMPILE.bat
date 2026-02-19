@echo off
chcp 65001 >nul
echo ═══════════════════════════════════════════
echo   Компиляция FLINT+ v2.77 (32-bit)
echo ═══════════════════════════════════════════

set "SRCDIR=%~dp0."
set "FLINTDIR=%~dp0..\Flint 2.77"
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

:: Генерируем RUN.bat внутри BUILD
>"%BUILDDIR%\RUN.bat" echo @echo off
>>"%BUILDDIR%\RUN.bat" echo chcp 65001 ^>nul
>>"%BUILDDIR%\RUN.bat" echo set "DOSBOX=%%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe"
>>"%BUILDDIR%\RUN.bat" echo set "FLINTDIR=%%~dp0..\..\Flint 2.77"
>>"%BUILDDIR%\RUN.bat" echo if not exist "%%DOSBOX%%" echo ОШИБКА: DOSBox-X не найден ^& pause ^& exit /b 1
>>"%BUILDDIR%\RUN.bat" echo "%%DOSBOX%%" -conf "%%~dp0dosbox-x.conf" -c "MOUNT C \"%%~dp0.\"" -c "C:" -c "PROJ5.EXE" -c "echo." -c "echo Program finished. Press any key..." -c "pause" -c "EXIT"
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLINT1.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLINT9.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLASH.DAT"  "%%FLINTDIR%%\" ^>nul 2^>nul

echo.
echo ═══════════════════════════════════════════
echo   Готово! Папка BUILD создана.
echo   Для запуска — двойной клик на BUILD\RUN.bat
echo ═══════════════════════════════════════════
pause
goto :eof

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
