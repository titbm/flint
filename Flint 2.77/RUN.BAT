@echo off
chcp 65001 >nul

set DOSBOX=%~dp0..\Tools\DOSBox-X\dosbox-x.exe

if not exist "%~dp0proj5.exe" (
    echo ОШИБКА: proj5.exe не найден в %~dp0
    pause & exit /b 1
)
if not exist "%DOSBOX%" (
    echo ОШИБКА: DOSBox-X не найден: %DOSBOX%
    pause & exit /b 1
)

echo Запуск Flint 2.77...
"%DOSBOX%" -conf NUL ^
  -set "machine=svga_s3" ^
  -set "memsize=16" ^
  -set "cycles=max" ^
  -c "MOUNT C \"%~dp0.\"" ^
  -c "C:" ^
  -c "PROJ5.EXE" ^
  -c "EXIT"
