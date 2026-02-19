@echo off
:: ═══════════════════════════════════════════════
::   Компиляция FLINT 2.61
::   Автоопределение среды:
::     DOS / Windows 9x — нативная компиляция
::     Windows NT+      — компиляция через DOSBox-X
:: ═══════════════════════════════════════════════
:: Флаги компиляции:
::   -ml   Large memory model (far code + far data)
::   -O1   Оптимизация по размеру
::   -3    Генерация 386 инструкций
:: Линковка:
::   TLINK /c /x — case-sensitive, no map
::   Библиотеки: GRAPHICS EMU MATHL CL
:: ═══════════════════════════════════════════════
if "%OS%"=="Windows_NT" goto NT_COMPILE

:: ─────────────────────────────────────────────
::  DOS / Windows 9x — нативная компиляция
::  Запускать из папки с исходниками (SRC)
:: ─────────────────────────────────────────────
echo ===================================
echo   Компиляция FLINT 2.61
echo ===================================

:: Поиск компилятора: BCDIR (если задана) -> Tools\BC45 -> C:\BC45
if not "%BCDIR%"=="" goto CHECK_BC
if exist ..\..\..\Tools\BC45\BIN\BCC.EXE set BCDIR=..\..\..\Tools\BC45
if not "%BCDIR%"=="" goto CHECK_BC
if exist C:\BC45\BIN\BCC.EXE set BCDIR=C:\BC45
if not "%BCDIR%"=="" goto CHECK_BC
goto NO_BC

:CHECK_BC
if not exist %BCDIR%\BIN\BCC.EXE goto NO_BC
echo Компилятор: %BCDIR%
set PATH=%BCDIR%\BIN;%PATH%
echo.

:: Компиляция
%BCDIR%\BGI\BGIOBJ /F %BCDIR%\BGI\EGAVGA EGAVGA
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE PROJ5.CPP
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE PIC.CPP
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE MSKEYC.CPP
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE RDWRF.CPP

:: Линковка
echo %BCDIR%\LIB\C0L PROJ5 PIC MSKEYC RDWRF EGAVGA+ > LINK.RSP
echo ,PROJ5.EXE+ >> LINK.RSP
echo ,+ >> LINK.RSP
echo ,GRAPHICS EMU MATHL CL >> LINK.RSP
%BCDIR%\BIN\TLINK /c /x /L%BCDIR%\LIB @LINK.RSP

:: Очистка
if exist *.OBJ del *.OBJ
if exist LINK.RSP del LINK.RSP

if not exist PROJ5.EXE goto COMPILE_FAIL
echo.
echo *** Компиляция успешна ***

:: Сборка папки BUILD
echo Сборка папки BUILD...
if not exist BUILD mkdir BUILD
copy PROJ5.EXE BUILD\ >nul
del PROJ5.EXE
copy ..\FLINT.GLS BUILD\ >nul
copy ..\FLINT1.CFG BUILD\ >nul
copy ..\FLINT9.CFG BUILD\ >nul
if exist ..\FLASH.DAT copy ..\FLASH.DAT BUILD\ >nul
if exist ..\BFT_FILES xcopy /E /I ..\BFT_FILES BUILD\BFT_FILES >nul

:: Генерация BUILD\RUN.bat (только DOS)
echo @echo off > BUILD\RUN.bat
echo if not exist PROJ5.EXE goto NO_EXE >> BUILD\RUN.bat
echo PROJ5.EXE >> BUILD\RUN.bat
echo goto END >> BUILD\RUN.bat
echo :NO_EXE >> BUILD\RUN.bat
echo echo PROJ5.EXE not found. >> BUILD\RUN.bat
echo pause >> BUILD\RUN.bat
echo :END >> BUILD\RUN.bat

echo.
echo Готово! Папка BUILD создана.
echo Для запуска: BUILD\RUN.bat
pause
goto END

:NO_BC
echo ОШИБКА: Компилятор Borland C++ не найден.
echo Укажите путь: SET BCDIR=C:\BC45
echo и запустите скрипт повторно.
pause
goto END

:COMPILE_FAIL
echo.
echo ОШИБКА: Компиляция не удалась.
pause
goto END

:: ─────────────────────────────────────────────
::  Windows NT+ — компиляция через DOSBox-X
:: ─────────────────────────────────────────────
:NT_COMPILE
chcp 65001 >nul
echo ═══════════════════════════════════════════
echo   Компиляция FLINT 2.61
echo ═══════════════════════════════════════════

set SRCDIR=%~dp0.
set FLINTDIR=%~dp0..
set TOOLSDIR=%~dp0..\..\..\Tools
set BUILDDIR=%~dp0BUILD

:: Проверяем наличие компилятора BC45
if exist "%TOOLSDIR%\BC45\BIN\BCC.EXE" (
    set BCDIR=%TOOLSDIR%\BC45
    set BCNAME=Borland C++ 4.5
) else (
    echo ОШИБКА: Компилятор не найден.
    echo Нужен Borland C++ 4.5 в %TOOLSDIR%\BC45\
    pause & exit /b 1
)

:: Поиск DOSBox-X: сначала в Tools, затем в PATH
set DOSBOX=%TOOLSDIR%\DOSBox-X\dosbox-x.exe
if exist "%DOSBOX%" goto DOSBOX_OK
for %%I in (dosbox-x.exe) do if not "%%~$PATH:I"=="" set DOSBOX=%%~$PATH:I
if exist "%DOSBOX%" goto DOSBOX_OK
echo ОШИБКА: DOSBox-X не найден.
echo Установите DOSBox-X или поместите его в Tools\DOSBox-X\
pause & exit /b 1
:DOSBOX_OK

echo Компилятор: %BCNAME% (%BCDIR%)
echo Исходники:  %SRCDIR%
echo.

:: Генерируем временный ~BUILD.BAT
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

:: DOSBox-X: C: = компилятор, D: = исходники
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

:: Копируем данные из Flint 2.61
copy /Y "%FLINTDIR%\FLINT.GLS"  "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT1.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT9.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLASH.DAT"  "%BUILDDIR%\" >nul 2>nul

:: Копируем BFT-файлы, если есть
if exist "%FLINTDIR%\BFT_FILES" (
    xcopy /E /I /Y "%FLINTDIR%\BFT_FILES" "%BUILDDIR%\BFT_FILES" >nul
)

:: Генерируем двухрежимный RUN.bat внутри BUILD
>"%BUILDDIR%\RUN.bat" (
    echo @echo off
    echo if "%%OS%%"=="Windows_NT" goto NT_RUN
    echo if not exist PROJ5.EXE goto NO_EXE
    echo PROJ5.EXE
    echo goto END
    echo :NT_RUN
    echo chcp 65001 ^>nul
    echo set DOSBOX=%%~dp0..\..\..\..\Tools\DOSBox-X\dosbox-x.exe
    echo set FLINTDIR=%%~dp0..\..
    echo if exist "%%DOSBOX%%" goto DOSBOX_OK
    echo for %%%%I in ^(dosbox-x.exe^) do if not "%%%%~$PATH:I"=="" set DOSBOX=%%%%~$PATH:I
    echo if exist "%%DOSBOX%%" goto DOSBOX_OK
    echo echo ERROR: DOSBox-X not found.
    echo pause ^& exit /b 1
    echo :DOSBOX_OK
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
    echo goto END
    echo :NO_EXE
    echo echo PROJ5.EXE not found.
    echo pause
    echo :END
)

echo.
echo Готово! Папка BUILD создана: %BUILDDIR%
echo Для запуска — двойной клик на BUILD\RUN.bat
pause
goto END

:END
