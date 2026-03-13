@echo off
:: ===============================================
::   Compiling FLINT+ v2.77 (32-bit) — RELEASE
::   Same as COMPILE.bat but without TRACE logging
::   (no FLINT.LOG created at runtime)
:: ===============================================
if "%OS%"=="Windows_NT" goto NT_COMPILE

:: ---------------------------------------------
::  DOS / Windows 9x - native compilation
:: ---------------------------------------------
echo ===================================
echo   Compiling FLINT+ v2.77 (32-bit)
echo   Mode: RELEASE (no logging)
echo ===================================

if not "%WATCOM%"=="" goto CHECK_WATCOM
if exist ..\Tools\WATCOM\binw\wpp386.exe set WATCOM=..\Tools\WATCOM
if not "%WATCOM%"=="" goto CHECK_WATCOM
if exist C:\WATCOM\binw\wpp386.exe set WATCOM=C:\WATCOM
if not "%WATCOM%"=="" goto CHECK_WATCOM
goto NO_WATCOM

:CHECK_WATCOM
if not exist %WATCOM%\binw\wpp386.exe goto NO_WATCOM
echo Compiler: Open Watcom C++ (%WATCOM%)

set PATH=%WATCOM%\binw;%PATH%
set INCLUDE=%WATCOM%\h
set LIB=%WATCOM%\lib386\dos
echo.

if "%FLINTDIR%"=="" set FLINTDIR=..\!GENESIS\Flint 2.77

echo Compiling (NOTRACE)...
wmake -f MAKEFILE EXTRA=-dNOTRACE
if errorlevel 1 goto COMPILE_FAIL

if not exist PROJ5.EXE goto COMPILE_FAIL
echo.
echo *** Compilation successful (RELEASE) ***

:: Build output directory
set BUILDNAME=BUILD_32BIT_NOLOGS
echo Building output directory: %BUILDNAME%
if not exist %BUILDNAME% mkdir %BUILDNAME%
copy PROJ5.EXE %BUILDNAME%\ >nul
del PROJ5.EXE

if exist %WATCOM%\binw\dos4gw.exe copy %WATCOM%\binw\dos4gw.exe %BUILDNAME%\ >nul

if exist *.OBJ del *.OBJ
if exist *.ERR del *.ERR
if exist DEBUG.LOG del DEBUG.LOG

if exist %FLINTDIR%\FLINT.GLS copy %FLINTDIR%\FLINT.GLS %BUILDNAME%\ >nul
if exist %FLINTDIR%\FLINT1.CFG copy %FLINTDIR%\FLINT1.CFG %BUILDNAME%\ >nul
if exist %FLINTDIR%\FLINT9.CFG copy %FLINTDIR%\FLINT9.CFG %BUILDNAME%\ >nul
if exist %FLINTDIR%\FLASH.DAT copy %FLINTDIR%\FLASH.DAT %BUILDNAME%\ >nul
if exist %FLINTDIR%\CONFIG.SYS copy %FLINTDIR%\CONFIG.SYS %BUILDNAME%\ >nul
if exist %FLINTDIR%\BFT_FILES xcopy /E /I %FLINTDIR%\BFT_FILES %BUILDNAME%\BFT_FILES >nul

echo @echo off > %BUILDNAME%\RUN.bat
echo if not exist PROJ5.EXE goto NO_EXE >> %BUILDNAME%\RUN.bat
echo if not exist DOS4GW.EXE goto NO_DOS4GW >> %BUILDNAME%\RUN.bat
echo SET DOS4GVM=MAXMEM#128000 >> %BUILDNAME%\RUN.bat
echo PROJ5.EXE >> %BUILDNAME%\RUN.bat
echo goto END >> %BUILDNAME%\RUN.bat
echo :NO_EXE >> %BUILDNAME%\RUN.bat
echo echo PROJ5.EXE not found. >> %BUILDNAME%\RUN.bat
echo pause >> %BUILDNAME%\RUN.bat
echo goto END >> %BUILDNAME%\RUN.bat
echo :NO_DOS4GW >> %BUILDNAME%\RUN.bat
echo echo DOS4GW.EXE not found. >> %BUILDNAME%\RUN.bat
echo pause >> %BUILDNAME%\RUN.bat
echo :END >> %BUILDNAME%\RUN.bat

echo.
echo Done! %BUILDNAME% directory created (RELEASE, no logging).
echo To run: %BUILDNAME%\RUN.bat
pause
goto END

:NO_WATCOM
echo ERROR: Open Watcom C++ not found.
echo Set path: SET WATCOM=C:\WATCOM
pause
goto END

:COMPILE_FAIL
echo.
echo ERROR: Compilation failed.
if exist *.OBJ del *.OBJ
if exist *.ERR del *.ERR
pause
goto END

:: ---------------------------------------------
::  Windows NT+ - native compilation (Watcom)
:: ---------------------------------------------
:NT_COMPILE
echo ===========================================
echo   Compiling FLINT+ v2.77 (32-bit)
echo   Mode: RELEASE (no logging)
echo ===========================================

set "SRCDIR=%~dp0."
set "FLINTDIR=%~dp0..\!GENESIS\Flint 2.77"
set "TOOLSDIR=%~dp0..\Tools"
set "WATCOM=%~dp0..\Tools\WATCOM"

:: Generate timestamp (DDMMYY_HHMMSS)
for /f %%I in ('powershell -noprofile -command "Get-Date -Format ddMMyy_HHmmss"') do set "TSTAMP=%%I"
set "BUILDDIR=%~dp0BUILD_32BIT_NOLOGS_%TSTAMP%"

rem --- Locate Watcom ---
if not exist "%WATCOM%\binnt\wpp386.exe" goto :no_watcom

rem --- Set up Watcom environment ---
set "PATH=%WATCOM%\binnt;%WATCOM%\binw;%PATH%"
set "INCLUDE=%WATCOM%\h"
set "WATCOM_DIR=%WATCOM%"
set "LIB=%WATCOM%\lib386\dos"

echo Compiler: Open Watcom C++
echo Sources:  %SRCDIR%
echo.

rem --- Compile (NOTRACE) ---
cd /d "%SRCDIR%"
echo Compiling (NOTRACE)...
wmake -f MAKEFILE EXTRA=-dNOTRACE
if errorlevel 1 goto :compile_fail

echo.
if not exist "%SRCDIR%\proj5.exe" goto :no_exe

:: Build output directory with EXE and data files
echo Building output directory...
if exist "%BUILDDIR%" rmdir /S /Q "%BUILDDIR%"
mkdir "%BUILDDIR%"

move /Y "%SRCDIR%\proj5.exe" "%BUILDDIR%\" >nul
copy /Y "%WATCOM%\binw\dos4gw.exe" "%BUILDDIR%\" >nul

del /Q "%SRCDIR%\*.obj" >nul 2>nul
del /Q "%SRCDIR%\*.err" >nul 2>nul
del /Q "%SRCDIR%\DEBUG.LOG" >nul 2>nul

copy /Y "%FLINTDIR%\FLINT.GLS"  "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT1.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLINT9.CFG" "%BUILDDIR%\" >nul
copy /Y "%FLINTDIR%\FLASH.DAT"  "%BUILDDIR%\" >nul 2>nul
copy /Y "%FLINTDIR%\CONFIG.SYS" "%BUILDDIR%\" >nul 2>nul

if not exist "%FLINTDIR%\BFT_FILES" goto :skip_bft
xcopy /E /I /Y "%FLINTDIR%\BFT_FILES" "%BUILDDIR%\BFT_FILES" >nul
:skip_bft

:: Generate dosbox-x.conf inside BUILD
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

:: Generate dual-mode RUN.bat inside BUILD
>"%BUILDDIR%\RUN.bat" echo @echo off
>>"%BUILDDIR%\RUN.bat" echo if "%%OS%%"=="Windows_NT" goto NT_RUN
>>"%BUILDDIR%\RUN.bat" echo if not exist PROJ5.EXE goto NO_EXE
>>"%BUILDDIR%\RUN.bat" echo if not exist DOS4GW.EXE goto NO_DOS4GW
>>"%BUILDDIR%\RUN.bat" echo SET DOS4GVM=MAXMEM#128000
>>"%BUILDDIR%\RUN.bat" echo PROJ5.EXE
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NT_RUN

>>"%BUILDDIR%\RUN.bat" echo set "FLINTDIR=%%~dp0..\..\!GENESIS\Flint 2.77"
>>"%BUILDDIR%\RUN.bat" echo set "DOSBOX=%%~dp0..\..\Tools\DOSBox-X\dosbox-x.exe"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo for %%%%I in ^(dosbox-x.exe^) do if not "%%%%~$PATH:I"=="" set "DOSBOX=%%%%~$PATH:I"
>>"%BUILDDIR%\RUN.bat" echo if exist "%%DOSBOX%%" goto DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo echo ERROR: DOSBox-X not found. ^& pause ^& exit /b 1
>>"%BUILDDIR%\RUN.bat" echo :DOSBOX_OK
>>"%BUILDDIR%\RUN.bat" echo "%%DOSBOX%%" -conf "%%~dp0dosbox-x.conf" -c "MOUNT C \"%%~dp0.\"" -c "C:" -c "PROJ5.EXE" -c "echo." -c "echo Program finished. Press any key..." -c "pause" -c "EXIT"
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLINT1.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLINT9.CFG" "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo copy /Y "%%~dp0FLASH.DAT"  "%%FLINTDIR%%\" ^>nul 2^>nul
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NO_EXE
>>"%BUILDDIR%\RUN.bat" echo echo PROJ5.EXE not found. ^& pause
>>"%BUILDDIR%\RUN.bat" echo goto END
>>"%BUILDDIR%\RUN.bat" echo :NO_DOS4GW
>>"%BUILDDIR%\RUN.bat" echo echo DOS4GW.EXE not found. ^& pause
>>"%BUILDDIR%\RUN.bat" echo :END

echo.
echo ===========================================
echo   Done! Directory created: BUILD_32BIT_NOLOGS_%TSTAMP%
echo   No FLINT.LOG will be created at runtime.
echo   To run - double-click RUN.bat inside it
echo ===========================================
pause
goto END

:no_watcom
echo ERROR: Open Watcom not found in %WATCOM%
echo Need wpp386.exe in %WATCOM%\binnt\
pause
exit /b 1

:compile_fail
echo.
echo ERROR: Compilation failed!
pause
exit /b 1

:no_exe
echo ERROR: proj5.exe was not created. Check compiler output.
pause
exit /b 1

:END
