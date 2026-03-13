@echo off
:: ===============================================
::   Compiling Z_DIAG (16-bit)
::   Z-axis diagnostic tool for FLINT hardware
::   Auto-detect environment:
::     DOS / Windows 9x - native compilation
::     Windows NT+      - compile via DOSBox-X
:: ===============================================
:: Compiler flags:
::   -ml   Large memory model (far code + far data)
::   -O1   Optimize for size
::   -3    Generate 386 instructions
:: ===============================================
if "%OS%"=="Windows_NT" goto NT_COMPILE

:: ---------------------------------------------
::  DOS / Windows 9x - native compilation
::  Run from source directory
:: ---------------------------------------------
echo ===================================
echo   Compiling Z_DIAG (16-bit)
echo ===================================

:: Locate compiler: BCDIR (if set) -> ..\BC45 -> C:\BC45
if not "%BCDIR%"=="" goto CHECK_BC
if exist ..\BC45\BIN\BCC.EXE set BCDIR=..\BC45
if not "%BCDIR%"=="" goto CHECK_BC
if exist C:\BC45\BIN\BCC.EXE set BCDIR=C:\BC45
if not "%BCDIR%"=="" goto CHECK_BC
goto NO_BC

:CHECK_BC
if not exist %BCDIR%\BIN\BCC.EXE goto NO_BC
echo Compiler: %BCDIR%
set PATH=%BCDIR%\BIN;%PATH%
echo.

:: Compile
echo Compiling Z_DIAG.CPP...
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE Z_DIAG.CPP
if errorlevel 1 goto COMPILE_FAIL

:: Link
echo %BCDIR%\LIB\C0L Z_DIAG+ > LINK.RSP
echo ,Z_DIAG.EXE+ >> LINK.RSP
echo ,+ >> LINK.RSP
echo ,EMU MATHL CL >> LINK.RSP
%BCDIR%\BIN\TLINK /c /x /L%BCDIR%\LIB @LINK.RSP

:: Cleanup
if exist *.OBJ del *.OBJ
if exist LINK.RSP del LINK.RSP

if not exist Z_DIAG.EXE goto COMPILE_FAIL
echo.
echo *** Compilation successful ***

:: Build output directory
set BUILDNAME=ZDIAG
echo Building output directory: %BUILDNAME%
if not exist %BUILDNAME% mkdir %BUILDNAME%
copy Z_DIAG.EXE %BUILDNAME%\ >nul
del Z_DIAG.EXE

:: Generate dual-mode RUN.bat
echo @echo off > %BUILDNAME%\RUN.bat
echo if "%%OS%%"=="Windows_NT" goto NT_RUN >> %BUILDNAME%\RUN.bat
echo if not exist Z_DIAG.EXE goto NO_EXE >> %BUILDNAME%\RUN.bat
echo Z_DIAG.EXE >> %BUILDNAME%\RUN.bat
echo goto END >> %BUILDNAME%\RUN.bat
echo :NT_RUN >> %BUILDNAME%\RUN.bat
echo set DOSBOX=%%~dp0..\..\DOSBox-X\dosbox-x.exe >> %BUILDNAME%\RUN.bat
echo if exist "%%DOSBOX%%" goto DOSBOX_OK >> %BUILDNAME%\RUN.bat
echo for %%%%I in (dosbox-x.exe) do if not "%%%%~$PATH:I"=="" set DOSBOX=%%%%~$PATH:I >> %BUILDNAME%\RUN.bat
echo if exist "%%DOSBOX%%" goto DOSBOX_OK >> %BUILDNAME%\RUN.bat
echo echo ERROR: DOSBox-X not found. >> %BUILDNAME%\RUN.bat
echo pause ^& exit /b 1 >> %BUILDNAME%\RUN.bat
echo :DOSBOX_OK >> %BUILDNAME%\RUN.bat
echo "%%DOSBOX%%" -conf NUL -set "machine=svga_s3" -set "memsize=16" -set "cycles=max" -c "MOUNT C \"%%~dp0.\"" -c "C:" -c "Z_DIAG.EXE" -c "pause" -c "EXIT" >> %BUILDNAME%\RUN.bat
echo goto END >> %BUILDNAME%\RUN.bat
echo :NO_EXE >> %BUILDNAME%\RUN.bat
echo echo Z_DIAG.EXE not found. >> %BUILDNAME%\RUN.bat
echo pause >> %BUILDNAME%\RUN.bat
echo :END >> %BUILDNAME%\RUN.bat

echo.
echo Done! %BUILDNAME% directory created.
echo To run: %BUILDNAME%\RUN.bat
pause
goto END

:NO_BC
echo ERROR: Borland C++ compiler not found.
echo Set path: SET BCDIR=C:\BC45
echo and re-run this script.
pause
goto END

:COMPILE_FAIL
echo.
echo ERROR: Compilation failed.
pause
goto END

:: ---------------------------------------------
::  Windows NT+ - compile via DOSBox-X
:: ---------------------------------------------
:NT_COMPILE
echo ===========================================
echo   Compiling Z_DIAG (16-bit)
echo ===========================================

for %%I in ("%~dp0.") do set "SRCDIR=%%~fI"
for %%I in ("%~dp0..") do set "TOOLSDIR=%%~fI"

:: Generate timestamp (DDMMYY_HHMMSS)
for /f %%I in ('powershell -noprofile -command "Get-Date -Format ddMMyy_HHmmss"') do set "TSTAMP=%%I"
set BUILDDIR=%~dp0ZDIAG_%TSTAMP%

:: Check for BC45 compiler
if exist "%TOOLSDIR%\BC45\BIN\BCC.EXE" (
    set BCDIR=%TOOLSDIR%\BC45
    set BCNAME=Borland C++ 4.5
) else (
    echo ERROR: Compiler not found.
    echo Need Borland C++ 4.5 in %TOOLSDIR%\BC45\
    pause & exit /b 1
)

:: Locate DOSBox-X: first in Tools, then in PATH
set DOSBOX=%TOOLSDIR%\DOSBox-X\dosbox-x.exe
if exist "%DOSBOX%" goto DOSBOX_OK
for %%I in (dosbox-x.exe) do if not "%%~$PATH:I"=="" set DOSBOX=%%~$PATH:I
if exist "%DOSBOX%" goto DOSBOX_OK
echo ERROR: DOSBox-X not found.
echo Install DOSBox-X or place it in Tools\DOSBox-X\
pause & exit /b 1
:DOSBOX_OK

echo Compiler: %BCNAME% (%BCDIR%)
echo Sources:  %SRCDIR%
echo.

:: Generate temporary ~BUILD.BAT
>"%SRCDIR%\~BUILD.BAT" (
    echo @echo off
    echo C:\BIN\BCC -c -ml -O1 -3 -IC:\INCLUDE D:\Z_DIAG.CPP
    echo echo C:\LIB\C0L D:\Z_DIAG+ ^> D:\LINK.RSP
    echo echo ,D:\Z_DIAG.EXE+ ^>^> D:\LINK.RSP
    echo echo ,+ ^>^> D:\LINK.RSP
    echo echo ,EMU MATHL CL ^>^> D:\LINK.RSP
    echo C:\BIN\TLINK /c /x /LC:\LIB @D:\LINK.RSP
    echo if exist D:\Z_DIAG.EXE echo *** SUCCESS ***
    echo if not exist D:\Z_DIAG.EXE echo *** FAILED ***
    echo DEL D:\*.OBJ
    echo DEL D:\LINK.RSP
)

:: DOSBox-X: C: = compiler, D: = sources
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
if not exist "%SRCDIR%\Z_DIAG.EXE" (
    echo ERROR: Compilation failed. Check DOSBox-X output.
    pause & exit /b 1
)

:: Build output directory
echo Building output directory...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

move /Y "%SRCDIR%\Z_DIAG.EXE" "%BUILDDIR%\" >nul

:: Generate dual-mode RUN.bat
>"%BUILDDIR%\RUN.bat" (
    echo @echo off
    echo if "%%OS%%"=="Windows_NT" goto NT_RUN
    echo if not exist Z_DIAG.EXE goto NO_EXE
    echo Z_DIAG.EXE
    echo goto END
    echo :NT_RUN
    echo set DOSBOX=%%~dp0..\..\DOSBox-X\dosbox-x.exe
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
    echo   -c "Z_DIAG.EXE" ^^
    echo   -c "pause" ^^
    echo   -c "EXIT"
    echo goto END
    echo :NO_EXE
    echo echo Z_DIAG.EXE not found.
    echo pause
    echo :END
)

echo.
echo Done! Directory created: ZDIAG_%TSTAMP%
echo To run - double-click RUN.bat inside it
pause
goto END

:END
