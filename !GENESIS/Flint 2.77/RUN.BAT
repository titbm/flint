@echo off
:: =============================================
::   Running FLINT 2.77
::   Auto-detect: DOS/Win9x - direct,
::   Windows NT+ - via DOSBox-X
:: =============================================
if "%OS%"=="Windows_NT" goto NT_RUN

:: -- DOS / Windows 9x --------------------------
if not exist PROJ5.EXE goto NO_EXE
echo Starting Flint 2.77...
PROJ5.EXE
goto END

:NT_RUN
:: -- Windows NT+ (via DOSBox-X) ----------------

if not exist "%~dp0proj5.exe" (
    echo ERROR: proj5.exe not found in %~dp0
    pause & exit /b 1
)

:: Locate DOSBox-X: first in Tools, then in PATH
set DOSBOX=%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe
if exist "%DOSBOX%" goto DOSBOX_OK
for %%I in (dosbox-x.exe) do if not "%%~$PATH:I"=="" set DOSBOX=%%~$PATH:I
if exist "%DOSBOX%" goto DOSBOX_OK
echo ERROR: DOSBox-X not found.
echo Install DOSBox-X or place it in Tools\DOSBox-X\
pause & exit /b 1
:DOSBOX_OK

echo Starting Flint 2.77...
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
echo ERROR: PROJ5.EXE not found in current directory.
echo Make sure you are running the script from its directory.
pause
goto END

:END
