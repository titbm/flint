@echo off
chcp 65001 >nul
echo ═══════════════════════════════════════════
echo   Компиляция FLINT 2.77
echo ═══════════════════════════════════════════

set SRCDIR=%~dp0.
set FLINTDIR=%~dp0..\Flint 2.77
set TOOLSDIR=%~dp0..\Tools
set DOSBOX=%TOOLSDIR%\DOSBox-X\dosbox-x.exe
set BUILDDIR=%~dp0BUILD

:: ────────────────────────────────────────────
:: Флаги компиляции:
::   -ml   Large memory model (far code + far data)
::   -O1   Оптимизация по размеру
::   -3    Генерация 386 инструкций (32-бит регистры)
:: Линковка:
::   TLINK /c /x — case-sensitive, no map
::   Библиотеки: GRAPHICS EMU MATHL CL
:: ────────────────────────────────────────────

:: Выбор компилятора: BC45 (предпочтительно) или BC31 (fallback)
if exist "%TOOLSDIR%\BC45\BIN\BCC.EXE" (
    set BCDIR=%TOOLSDIR%\BC45
    set BCNAME=Borland C++ 4.5
) else if exist "%TOOLSDIR%\BC31\BIN\BCC.EXE" (
    set BCDIR=%TOOLSDIR%\BC31
    set BCNAME=Borland C++ 3.1
) else (
    echo ОШИБКА: Компилятор не найден.
    echo Нужен BC 4.5 в %TOOLSDIR%\BC45\ или BC 3.1 в %TOOLSDIR%\BC31\
    pause & exit /b 1
)

:: Проверяем наличие инструментов
if not exist "%DOSBOX%" (
    echo ОШИБКА: DOSBox-X не найден: %DOSBOX%
    pause & exit /b 1
)

echo Компилятор: %BCNAME% (%BCDIR%)
echo Исходники:  %SRCDIR%
echo.

:: DOSBox-X: C: = BC31, D: = исходники. Все шаги компиляции inline.
:: Генерируем временный BUILD.BAT (удалится после компиляции)
>"%SRCDIR%\~BUILD.BAT" (
    echo @echo off
    echo C:\BGI\BGIOBJ /F C:\BGI\EGAVGA D:\EGAVGA
    echo C:\BIN\BCC -c -ml -O1 -3 -IC:\INCLUDE D:\PROJ5.CPP
    echo C:\BIN\BCC -c -ml -O1 -3 -IC:\INCLUDE D:\PIC.CPP
    echo C:\BIN\BCC -c -ml -O1 -3 -IC:\INCLUDE D:\MSKEYC.CPP
    echo C:\BIN\BCC -c -ml -O1 -3 -IC:\INCLUDE D:\RDWRF.CPP
    echo echo C:\LIB\C0L D:\PROJ5 D:\PIC D:\MSKEYC D:\RDWRF D:\EGAVGA+ ^> D:\LINK.RSP
    echo echo ,D:\PROJ5.EXE+ ^>^> D:\LINK.RSP
    echo echo ,+ ^>^> D:\LINK.RSP
    echo echo ,GRAPHICS EMU MATHL CL ^>^> D:\LINK.RSP
    echo C:\BIN\TLINK /c /x /LC:\LIB @D:\LINK.RSP
    echo if exist D:\PROJ5.EXE echo *** SUCCESS ***
    echo if not exist D:\PROJ5.EXE echo *** FAILED ***
    echo DEL D:\*.OBJ
    echo DEL D:\LINK.RSP
)
"%DOSBOX%" -conf NUL ^
  -set "machine=svga_s3" ^
  -set "memsize=16" ^
  -set "cycles=max" ^
  -c "MOUNT C \"%BCDIR%\"" ^
  -c "MOUNT D \"%SRCDIR%\"" ^
  -c "D:" ^
  -c "~BUILD.BAT" ^
  -c "EXIT"
DEL "%SRCDIR%\~BUILD.BAT" >nul 2>nul

echo.
if not exist "%SRCDIR%\PROJ5.EXE" (
    echo ОШИБКА: Компиляция не удалась. Проверьте вывод DOSBox-X.
    pause & exit /b 1
)

:: Собираем готовую папку BUILD с EXE и данными для запуска
echo Сборка папки BUILD...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

:: Копируем скомпилированный EXE
move /Y "%SRCDIR%\PROJ5.EXE" "%BUILDDIR%\" >nul

:: Копируем данные из Flint 2.77
copy /Y "%FLINTDIR%\FLINT.GLS"  "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT1.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT9.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLASH.DAT"  "%BUILDDIR%\" >nul 2>nul
copy /Y "%FLINTDIR%\CONFIG.SYS" "%BUILDDIR%\" >nul 2>nul

:: Копируем BFT-файлы, если есть
if exist "%FLINTDIR%\BFT_FILES" (
    xcopy /E /I /Y "%FLINTDIR%\BFT_FILES" "%BUILDDIR%\BFT_FILES" >nul
)

:: Генерируем RUN.bat внутри BUILD
>"%BUILDDIR%\RUN.bat" (
    echo @echo off
    echo chcp 65001 ^>nul
    echo set DOSBOX=%%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe
    echo set FLINTDIR=%%~dp0..\..\Flint 2.77
    echo if not exist "%%DOSBOX%%" ^(
    echo     echo ERROR: DOSBox-X not found: %%DOSBOX%%
    echo     pause ^& exit /b 1
    echo ^)
    echo "%%DOSBOX%%" -conf NUL ^^
    echo   -set "machine=svga_s3" ^^
    echo   -set "memsize=16" ^^
    echo   -set "cycles=max" ^^
    echo   -c "MOUNT C \"%%~dp0.\"" ^^
    echo   -c "C:" ^^
    echo   -c "PROJ5.EXE" ^^
    echo   -c "EXIT"
    echo copy /Y "%%~dp0FLINT1.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
    echo copy /Y "%%~dp0FLINT9.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
    echo copy /Y "%%~dp0FLASH.DAT"  "%%FLINTDIR%%\" ^>nul 2^>nul
)

echo.
echo Готово! Папка BUILD создана: %BUILDDIR%
echo Для запуска — двойной клик на BUILD\RUN.bat
pause
