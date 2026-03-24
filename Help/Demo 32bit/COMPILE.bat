@echo off
:: ===============================================
::   HELLO32 - 32-bit DOS DPMI32 demo
::   Borland C++ 4.5 + Power Pack
::   Auto-detect environment:
::     DOS / Windows 9x - not supported (BCC32 is Win32-only)
::     Windows NT+      - BCC32.EXE (Win32 host)
:: ===============================================
:: Compiler: Borland BCC32.EXE
:: Flags:
::   -WX      Target: DOS extended (DPMI32)
:: Linker: TLINK32.EXE (called by BCC32)
:: Runtime: 32RTM.EXE + DPMI32VM.OVL (Power Pack, patched)
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

:: Generate timestamp (YYYYMMDD_HHMMSS)
for /f %%I in ('powershell -noprofile -command "Get-Date -Format yyyyMMdd_HHmmss"') do set "TSTAMP=%%I"
set "BUILDDIR=%~dp0BUILD_32BIT_%TSTAMP%"

echo.
echo ===========================================
echo   Building HELLO32 (Borland 32-bit DPMI32)
echo ===========================================

:: Locate BC45_32
if not exist "%BC32%\BIN\BCC32.EXE" (
    echo ERROR: BCC32.EXE not found in %BC32%\BIN\
    echo Run Tools\SETUP_BC45_32.bat first.
    pause
    exit /b 1
)

echo Compiler: %BC32%\BIN\BCC32.EXE
echo Sources:  %SRCDIR%
echo.

:: BCC32 needs TLINK32 in PATH
set "PATH=%BC32%\BIN;%PATH%"

:: cd to source dir, then use relative paths — BCC32 can't handle spaces in args
cd /d "%SRCDIR%"
echo Compiling...
..\Tools\BC45_32\BIN\BCC32.EXE -WX -I..\Tools\BC45_32\INCLUDE -L..\Tools\BC45_32\LIB -eHELLO32.EXE HELLO32.C
if errorlevel 1 goto compile_fail
if not exist "%SRCDIR%\HELLO32.EXE" goto compile_fail

echo.
echo *** Compilation successful ***
echo.

:: Build output directory
echo Building output directory...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

:: Copy compiled EXE
move /Y "%SRCDIR%\HELLO32.EXE" "%BUILDDIR%\" >nul

:: Copy Borland DPMI32 runtime (required to run)
copy /Y "%BC32%\BIN\32RTM.EXE"    "%BUILDDIR%\" >nul
copy /Y "%BC32%\BIN\DPMI32VM.OVL" "%BUILDDIR%\" >nul

:: Clean intermediate files
del /Q "%SRCDIR%\HELLO32.obj" >nul 2>nul

:: Generate dosbox-x.conf
>"%BUILDDIR%\dosbox-x.conf" echo [dosbox]
>>"%BUILDDIR%\dosbox-x.conf" echo memsize=32
>>"%BUILDDIR%\dosbox-x.conf" echo.
>>"%BUILDDIR%\dosbox-x.conf" echo [cpu]
>>"%BUILDDIR%\dosbox-x.conf" echo core=auto
>>"%BUILDDIR%\dosbox-x.conf" echo cputype=pentium

:: Generate RUN.bat
>"%BUILDDIR%\RUN.bat" echo @echo off
>>"%BUILDDIR%\RUN.bat" echo set "DOSBOX=%%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo for %%%%I in ^(dosbox-x.exe^) do if not "%%%%~$PATH:I"=="" set "DOSBOX=%%%%~$PATH:I"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo echo ERROR: DOSBox-X not found. ^& pause ^& exit /b 1
>>"%BUILDDIR%\RUN.bat" echo :DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo "%%DOSBOX%%" -conf "%%~dp0dosbox-x.conf" -c "MOUNT C \"%%~dp0.\"" -c "C:" -c "HELLO32.EXE" -c "pause" -c "EXIT"

echo.
echo ===========================================
echo   Done! Directory: BUILD_32BIT_%TSTAMP%
echo   To run: double-click RUN.bat inside it
echo ===========================================
pause
goto END

:compile_fail
echo.
echo ERROR: Compilation failed.
del /Q "%SRCDIR%\HELLO32.obj" >nul 2>nul
pause
exit /b 1

:END
