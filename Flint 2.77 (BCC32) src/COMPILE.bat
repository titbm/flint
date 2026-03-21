@echo off
:: ===============================================
::   FLINT 2.77 - 32-bit DOS DPMI32
::   Borland C++ 4.5 + Power Pack
::   Auto-detect environment:
::     DOS / Windows 9x - not supported (BCC32 is Win32-only)
::     Windows NT+      - BCC32.EXE (Win32 host)
:: ===============================================
:: Compiler: Borland BCC32.EXE
:: Flags:
::   -WX      Target: DOS extended (DPMI32)
::   -O2      Optimize for speed
::   -c       Compile only (separate link step)
:: Linker: TLINK32.EXE
:: Runtime: 32RTM.EXE + DPMI32VM.OVL + BGI32.DLL + BGIVGA.DLL
:: ===============================================
if "%OS%"=="Windows_NT" goto NT_COMPILE

echo ERROR: BCC32.EXE requires Windows NT or later.
echo DOS / Windows 9x are not supported for the host build.
pause
goto END

:: ---------------------------------------------
::  Windows NT+ - compilation via BCC32
:: ---------------------------------------------
:NT_COMPILE

set "SRCDIR=%~dp0."
set "BC32=%~dp0..\Tools\BC45_32"
set "FLINTDIR=%~dp0..\!GENESIS\Flint 2.77"

:: Generate timestamp (YYYYMMDD_HHMMSS)
for /f %%I in ('powershell -noprofile -command "Get-Date -Format yyyyMMdd_HHmmss"') do set "TSTAMP=%%I"
set "BUILDDIR=%~dp0BUILD_BCC32_%TSTAMP%"

echo.
echo ===========================================
echo   Building FLINT 2.77 - BCC32 DPMI32
echo ===========================================

:: Locate BC45_32
if not exist "%BC32%\BIN\BCC32.EXE" goto NO_BC32
goto BC32_OK
:NO_BC32
echo ERROR: BCC32.EXE not found in %BC32%\BIN\
echo Run Tools\SETUP_BC45_32.bat first.
pause
exit /b 1
:BC32_OK

echo Compiler: %BC32%\BIN\BCC32.EXE
echo Sources:  %SRCDIR%
echo.

:: BCC32 needs TLINK32 in PATH
set "PATH=%BC32%\BIN;%PATH%"

:: cd to source dir, then use relative paths
cd /d "%SRCDIR%"
echo Compiling...
..\Tools\BC45_32\BIN\BCC32.EXE -WX -O2 -3 -c -I..\Tools\BC45_32\INCLUDE PROJ5.CPP
if errorlevel 1 goto compile_fail
..\Tools\BC45_32\BIN\BCC32.EXE -WX -O2 -3 -c -I..\Tools\BC45_32\INCLUDE PIC.CPP
if errorlevel 1 goto compile_fail
..\Tools\BC45_32\BIN\BCC32.EXE -WX -O2 -3 -c -I..\Tools\BC45_32\INCLUDE MSKEYC.CPP
if errorlevel 1 goto compile_fail
..\Tools\BC45_32\BIN\BCC32.EXE -WX -O2 -3 -c -I..\Tools\BC45_32\INCLUDE RDWRF.CPP
if errorlevel 1 goto compile_fail

echo Linking...
..\Tools\BC45_32\BIN\BCC32.EXE -WX -I..\Tools\BC45_32\INCLUDE -L..\Tools\BC45_32\LIB -ePROJ5.EXE PROJ5.OBJ PIC.OBJ MSKEYC.OBJ RDWRF.OBJ ..\Tools\BC45_32\LIB\BGI32.LIB ..\Tools\BC45_32\LIB\DPMI32.LIB
if errorlevel 1 goto compile_fail
if not exist "%SRCDIR%\PROJ5.EXE" goto compile_fail
del /F /Q "%SRCDIR%\con.LST" 2>nul

echo.
echo *** Compilation successful ***
echo.

:: Build output directory
echo Building output directory...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

:: Copy compiled EXE
move /Y "%SRCDIR%\PROJ5.EXE" "%BUILDDIR%\" >nul

:: Copy Borland DPMI32 runtime (required to run)
copy /Y "%BC32%\BIN\32RTM.EXE"    "%BUILDDIR%\" >nul
copy /Y "%BC32%\BIN\DPMI32VM.OVL" "%BUILDDIR%\" >nul

:: Copy BGI DLLs and fonts (required for graphics)
copy /Y "%BC32%\BGI\BGI32.DLL"  "%BUILDDIR%\" >nul
copy /Y "%BC32%\BGI\BGIVGA.DLL" "%BUILDDIR%\" >nul
copy /Y "%BC32%\BGI\*.FNT"      "%BUILDDIR%\" >nul

:: Clean intermediate files
del /Q "%SRCDIR%\*.OBJ" >nul 2>nul

:: Copy Flint data files
if exist "%FLINTDIR%\FLINT.GLS"  copy /Y "%FLINTDIR%\FLINT.GLS"  "%BUILDDIR%\" >nul
if exist "%FLINTDIR%\FLINT1.CFG" copy /Y "%FLINTDIR%\FLINT1.CFG" "%BUILDDIR%\" >nul
if exist "%FLINTDIR%\FLINT9.CFG" copy /Y "%FLINTDIR%\FLINT9.CFG" "%BUILDDIR%\" >nul
if exist "%FLINTDIR%\FLASH.DAT"  copy /Y "%FLINTDIR%\FLASH.DAT"  "%BUILDDIR%\" >nul 2>nul
if exist "%FLINTDIR%\CONFIG.SYS" copy /Y "%FLINTDIR%\CONFIG.SYS" "%BUILDDIR%\" >nul 2>nul
if exist "%FLINTDIR%\BFT_FILES"  xcopy /E /I /Y "%FLINTDIR%\BFT_FILES" "%BUILDDIR%\BFT_FILES" >nul

:: Generate dosbox-x.conf
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
>>"%BUILDDIR%\dosbox-x.conf" echo.


:: Generate RUN.bat
>"%BUILDDIR%\RUN.bat" echo @echo off
>>"%BUILDDIR%\RUN.bat" echo set "DOSBOX=%%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo for %%%%I in ^(dosbox-x.exe^) do if not "%%%%~$PATH:I"=="" set "DOSBOX=%%%%~$PATH:I"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo echo ERROR: DOSBox-X not found. ^& pause ^& exit /b 1
>>"%BUILDDIR%\RUN.bat" echo :DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo "%%DOSBOX%%" -conf "%%~dp0dosbox-x.conf" -c "MOUNT C \"%%~dp0.\"" -c "C:" -c "PROJ5.EXE" -c "echo." -c "echo Program finished. Press any key..." -c "pause" -c "EXIT"

echo.
echo ===========================================
echo   Done! Directory: BUILD_BCC32_%TSTAMP%
echo   To run: double-click RUN.bat inside it
echo ===========================================
pause
goto END

:compile_fail
echo.
echo ERROR: Compilation failed.
del /Q "%SRCDIR%\*.OBJ" >nul 2>nul
pause
exit /b 1

:END
