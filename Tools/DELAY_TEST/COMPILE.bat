@echo off
:: ===============================================
::   Compiling DLYTEST (32-bit DOS/4GW)
::   Checks pit_delay_ms() accuracy and sound.
::   Compiler: Open Watcom C++ wpp386
:: ===============================================
if not "%OS%"=="Windows_NT" (
    echo ERROR: Run on Windows NT+ only.
    pause
    goto END
)

echo ===========================================
echo   Compiling DLYTEST (32-bit)
echo ===========================================

set "SRCDIR=%~dp0."
set "WATCOM=%~dp0..\..\Tools\WATCOM"

:: Generate timestamp
for /f %%I in ('powershell -noprofile -command "Get-Date -Format ddMMyy_HHmmss"') do set "TSTAMP=%%I"
set "BUILDDIR=%~dp0BUILD_%TSTAMP%"

rem --- Locate Watcom ---
if not exist "%WATCOM%\binnt\wpp386.exe" goto :no_watcom

rem --- Set up Watcom environment ---
set "PATH=%WATCOM%\binnt;%WATCOM%\binw;%PATH%"
set "INCLUDE=%WATCOM%\h"
set "LIB=%WATCOM%\lib386\dos"

echo Compiler: Open Watcom C++
echo.

rem --- Compile ---
cd /d "%SRCDIR%"
echo Compiling DLYTEST.CPP...
wpp386 -bt=dos -mf -ox -zq -w3 DLYTEST.CPP
if errorlevel 1 goto :compile_fail

echo Linking...
wlink system dos4g name DLYTEST.EXE file DLYTEST.obj
if errorlevel 1 goto :compile_fail

if not exist "%SRCDIR%\DLYTEST.EXE" goto :no_exe

rem --- Build output directory ---
echo Building output directory...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

move /Y "%SRCDIR%\DLYTEST.EXE" "%BUILDDIR%\" >nul
copy /Y "%WATCOM%\binw\dos4gw.exe" "%BUILDDIR%\" >nul

del /Q "%SRCDIR%\*.obj" >nul 2>nul
del /Q "%SRCDIR%\*.err" >nul 2>nul

rem --- Generate dosbox-x.conf with [autoexec] ---
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
>>"%BUILDDIR%\dosbox-x.conf" echo [autoexec]
>>"%BUILDDIR%\dosbox-x.conf" echo @echo off
>>"%BUILDDIR%\dosbox-x.conf" echo MOUNT C "%BUILDDIR%"
>>"%BUILDDIR%\dosbox-x.conf" echo C:
>>"%BUILDDIR%\dosbox-x.conf" echo DLYTEST.EXE
>>"%BUILDDIR%\dosbox-x.conf" echo echo.
>>"%BUILDDIR%\dosbox-x.conf" echo echo Done. Press any key...
>>"%BUILDDIR%\dosbox-x.conf" echo pause
>>"%BUILDDIR%\dosbox-x.conf" echo EXIT

rem --- Generate RUN.bat ---
>"%BUILDDIR%\RUN.bat" echo @echo off
>>"%BUILDDIR%\RUN.bat" echo if "%%OS%%"=="Windows_NT" goto NT_RUN
>>"%BUILDDIR%\RUN.bat" echo if not exist DLYTEST.EXE goto NO_EXE
>>"%BUILDDIR%\RUN.bat" echo if not exist DOS4GW.EXE goto NO_DOS4GW
>>"%BUILDDIR%\RUN.bat" echo DLYTEST.EXE
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NT_RUN
>>"%BUILDDIR%\RUN.bat" echo set "DOSBOX=%%~dp0..\..\..\Tools\DOSBox-X\dosbox-x.exe"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo for %%%%I in ^(dosbox-x.exe^) do if not "%%%%~$PATH:I"=="" set "DOSBOX=%%%%~$PATH:I"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo echo ERROR: DOSBox-X not found. ^& pause ^& exit /b 1
>>"%BUILDDIR%\RUN.bat" echo :DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo "%%DOSBOX%%" -conf "%%~dp0dosbox-x.conf"
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NO_EXE
>>"%BUILDDIR%\RUN.bat" echo echo DLYTEST.EXE not found. ^& pause
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NO_DOS4GW
>>"%BUILDDIR%\RUN.bat" echo echo DOS4GW.EXE not found. ^& pause
>>"%BUILDDIR%\RUN.bat" echo :END

echo.
echo ===========================================
echo   Done! Directory: %BUILDDIR%
echo   Run: double-click RUN.bat inside it
echo ===========================================
pause
goto END

:no_watcom
echo ERROR: Open Watcom not found in %WATCOM%
pause
exit /b 1

:compile_fail
echo ERROR: Compilation failed.
del /Q "%SRCDIR%\*.obj" >nul 2>nul
pause
exit /b 1

:no_exe
echo ERROR: DLYTEST.EXE was not created.
pause
exit /b 1

:END