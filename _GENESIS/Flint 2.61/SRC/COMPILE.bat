@echo off
:: ===============================================
::   Compiling FLINT 2.61
::   Auto-detect environment:
::     DOS / Windows 9x - native compilation
::     Windows NT+      - compile via DOSBox-X
:: ===============================================
:: Compiler flags:
::   -ml   Large memory model (far code + far data)
::   -O1   Optimize for size
::   -3    Generate 386 instructions
:: Linker:
::   TLINK /c /x - case-sensitive, no map
::   Libraries: GRAPHICS EMU MATHL CL
:: ===============================================
if "%OS%"=="Windows_NT" goto NT_COMPILE

:: ---------------------------------------------
::  DOS / Windows 9x - native compilation
::  Run from source directory (SRC)
:: ---------------------------------------------
echo ===================================
echo   Compiling FLINT 2.61
echo ===================================

:: Locate compiler: BCDIR (if set) -> Tools\BC45 -> C:\BC45
if not "%BCDIR%"=="" goto CHECK_BC
if exist ..\..\..\Tools\BC45\BIN\BCC.EXE set BCDIR=..\..\..\Tools\BC45
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
%BCDIR%\BGI\BGIOBJ /F %BCDIR%\BGI\EGAVGA EGAVGA
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE PROJ5.CPP
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE PIC.CPP
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE MSKEYC.CPP
%BCDIR%\BIN\BCC -c -ml -O1 -3 -I%BCDIR%\INCLUDE RDWRF.CPP

:: Link
echo %BCDIR%\LIB\C0L PROJ5 PIC MSKEYC RDWRF EGAVGA+ > LINK.RSP
echo ,PROJ5.EXE+ >> LINK.RSP
echo ,+ >> LINK.RSP
echo ,GRAPHICS EMU MATHL CL >> LINK.RSP
%BCDIR%\BIN\TLINK /c /x /L%BCDIR%\LIB @LINK.RSP

:: Cleanup
if exist *.OBJ del *.OBJ
if exist LINK.RSP del LINK.RSP

if not exist PROJ5.EXE goto COMPILE_FAIL
echo.
echo *** Compilation successful ***

:: Build output directory
echo Building output directory...
if not exist BUILD mkdir BUILD
copy PROJ5.EXE BUILD\ >nul
del PROJ5.EXE
copy ..\FLINT.GLS BUILD\ >nul
copy ..\FLINT1.CFG BUILD\ >nul
copy ..\FLINT9.CFG BUILD\ >nul
if exist ..\FLASH.DAT copy ..\FLASH.DAT BUILD\ >nul
if exist ..\BFT_FILES xcopy /E /I ..\BFT_FILES BUILD\BFT_FILES >nul

:: Generate BUILD\RUN.bat (DOS only)
echo @echo off > BUILD\RUN.bat
echo if not exist PROJ5.EXE goto NO_EXE >> BUILD\RUN.bat
echo PROJ5.EXE >> BUILD\RUN.bat
echo goto END >> BUILD\RUN.bat
echo :NO_EXE >> BUILD\RUN.bat
echo echo PROJ5.EXE not found. >> BUILD\RUN.bat
echo pause >> BUILD\RUN.bat
echo :END >> BUILD\RUN.bat

echo.
echo Done! BUILD directory created.
echo To run: BUILD\RUN.bat
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
echo   Compiling FLINT 2.61
echo ===========================================

set SRCDIR=%~dp0.
set FLINTDIR=%~dp0..
set TOOLSDIR=%~dp0..\..\..\Tools
set BUILDDIR=%~dp0BUILD

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
if not exist "%SRCDIR%\PROJ5.EXE" (
    echo ERROR: Compilation failed. Check DOSBox-X output.
    pause & exit /b 1
)

:: Build output directory with EXE and data files
echo Building output directory...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

:: Copy compiled EXE
move /Y "%SRCDIR%\PROJ5.EXE" "%BUILDDIR%\" >nul

:: Copy data from Flint 2.61
copy /Y "%FLINTDIR%\FLINT.GLS"  "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT1.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT9.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLASH.DAT"  "%BUILDDIR%\" >nul 2>nul

:: Copy BFT files if present
if exist "%FLINTDIR%\BFT_FILES" (
    xcopy /E /I /Y "%FLINTDIR%\BFT_FILES" "%BUILDDIR%\BFT_FILES" >nul
)

:: Generate dual-mode RUN.bat inside BUILD
>"%BUILDDIR%\RUN.bat" (
    echo @echo off
    echo if "%%OS%%"=="Windows_NT" goto NT_RUN
    echo if not exist PROJ5.EXE goto NO_EXE
    echo PROJ5.EXE
    echo goto END
    echo :NT_RUN
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
echo Done! BUILD directory created: %BUILDDIR%
echo To run - double-click BUILD\RUN.bat
pause
goto END

:END
