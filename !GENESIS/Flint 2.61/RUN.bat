@echo off
:: ═══════════════════════════════════════════
::   Запуск FLINT 2.61
::   Автоопределение: DOS/Win9x — напрямую,
::   Windows NT+ — через DOSBox-X
:: ═══════════════════════════════════════════
if "%OS%"=="Windows_NT" goto NT_RUN

:: ── DOS / Windows 9x ──────────────────────
if not exist PROJ5.EXE goto NO_EXE
echo Запуск Flint 2.61...
PROJ5.EXE
goto END

:NT_RUN
:: ── Windows NT+ (через DOSBox-X) ─────────
chcp 65001 >nul

if not exist "%~dp0proj5.exe" (
    echo ОШИБКА: proj5.exe не найден в %~dp0
    pause & exit /b 1
)

:: Поиск DOSBox-X: сначала в Tools, затем в PATH
set DOSBOX=%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe
if exist "%DOSBOX%" goto DOSBOX_OK
for %%I in (dosbox-x.exe) do if not "%%~$PATH:I"=="" set DOSBOX=%%~$PATH:I
if exist "%DOSBOX%" goto DOSBOX_OK
echo ОШИБКА: DOSBox-X не найден.
echo Установите DOSBox-X или поместите его в Tools\DOSBox-X\
pause & exit /b 1
:DOSBOX_OK

echo Запуск Flint 2.61...
"%DOSBOX%" -conf NUL ^
  -set "machine=svga_s3" ^
  -set "memsize=16" ^
  -set "cycles=max" ^
  -c "MOUNT C \"%~dp0.\"" ^
  -c "C:" ^
  -c "PROJ5.EXE" ^
  -c "EXIT"
goto END

:NO_EXE
echo ОШИБКА: PROJ5.EXE не найден в текущей папке.
echo Убедитесь, что вы запускаете скрипт из его директории.
pause
goto END

:END
