# Borland PowerPack for DOS

This README file contains important information about the Borland PowerPack for DOS. For the latest information about this product and its accompanying programs and manuals, read this entire file.

---

## Table of Contents

1. [How to Get Help](#1-how-to-get-help)
2. [Installation](#2-installation)
3. [Features](#3-features)
4. [Important Information](#4-important-information)
5. [Miscellaneous Information](#5-miscellaneous-information)
6. [Installation Instructions (PINSTALL)](#6-installation-instructions-pinstall)
7. [Alphabetized List of Product Files (PFILELST)](#7-alphabetized-list-of-product-files-pfilelst)

---

## 1. How to Get Help

### Sources of Information

If you have any problems, please read this file, and check the on-line help and the PowerPack and Borland C++ manuals first. If you still have a question and need assistance, help is available from the following sources:

1. For instant on-line access to the Borland CompuServe forums, with their libraries of technical information and answers to common questions, type:
   - `GO BCPPDOS` — for questions pertaining to DOS
   - `GO BCPPWIN` — for questions pertaining to Windows

   If you are not a member of CompuServe, see the enclosed special offer, and write for full details on how to receive a free IntroPak containing a $15 credit toward your first month's on-line charges.

   For on-line access to Borland information on BIX, type: `JOIN BORLAND`

   For on-line access to Borland information on GEnie, type: `BORLAND`

2. Borland offers a wide variety of Technical Support plans providing a range of assistance from installation and general usage of Borland C++ to language syntax, programming, and debugging help. For information about these support programs, call **1-800-523-7070**.

3. Borland's TECHFAX service. Call **(800) 822-4269** for a FAX catalog of technical document entries.

4. Borland DLBBS. Dial **(408) 431-5096** (up to 9600 baud, 8-N-1) for a host of free technical documents and example programs.

5. For immediate assistance with everything from configuring Borland C++ to programming or debugging, call our C++ Programmer's Advisor Lines ($2/minute, first minute free):
   - Windows / Win32: **1-900-555-1002** or **1-800-782-5558** (MC/Visa)
   - DOS: **1-900-555-1004** or **1-800-368-3366** (MC/Visa)

6. Technical information on Borland C++ is available on the Internet via anonymous ftp at `ftp.borland.com`.

7. Subscribe to Borland's free electronic newsletter and get a regular update on the hottest programming tips and tricks. Send your full name and address via electronic mail to `tech-info@borland.com`.

---

## 2. Installation

For more install information see the online-text file PINSTALL.TXT (included [below](#6-installation-instructions-pinstall)).

The Borland PowerPack requires **Borland C++ version 4.02 or later**. If you do not have version 4.02 or later of Borland C++ contact the Borland Order Desk at 1-800-645-4559 to upgrade. Outside of North America, contact your local Borland office.

Make sure you specify the correct directory that you installed Borland C++ into during install.

Make sure you have turned ON the "CD-ROM:" entry if you have performed a CD-only configuration installation of Borland C++. Also make sure you have entered the full path to the BIN directory for the "CD-ROM Binary Directory" option (e.g. `D:\BC4\BIN`).

> **IMPORTANT:** Make sure to remove any overlay switches from your makefiles and projects if you are converting an overlaid application to a DOS extended application. Overlays are not compatible with DOS extended applications, and are, in fact superfluous.

> **Note:** make sure that `\BC4\BIN` comes before any PowerPack path in your PATH settings.

### Performing Custom Installations

**For 16-bit applications**, you will need the 16-bit command-line tools, the 16-bit Turbo Debugger, the 16-bit large-model Run-time Library, and the 16-bit Class Library from Borland C++. When performing a Custom install of Borland C++, make sure the following options are turned on:

- Customize Installation for Borland C++ Product — **16-bit Windows, DOS**
- Borland C++ Tools — Command Line Tools, Debugger, Visual Tools, Run-time Libraries, Class Library
- Borland C++ Debugger — Turbo Debugger
- Borland C++ Run-time Libraries — all options on
- Borland C++ Class Libraries — all options on

**For 32-bit applications**, you will need the 32-bit command-line tools, the 32-bit debugger, the 32-bit RTL libraries, and the 32-bit class Libraries from Borland C++. When performing a Custom install of Borland C++, make sure the following options are turned on:

- Customize Installation for Borland C++ Product — **32-bit Windows, DOS**
- Borland C++ Tools — Command Line Tools, Debugger, Run-time Libraries, Class Library
- Borland C++ Debugger — Turbo Debugger
- Borland C++ Visual Tools — Integrated Development Environment (IDE)
- Borland C++ Run-time Libraries — all options on
- Borland C++ Class Libraries — all options on

---

## 3. Features

Borland PowerPack for DOS lets you build 16-bit and 32-bit DOS extended applications. There is full support for 16-bit and 32-bit protected mode BGI and Turbo Vision.

You can generate DOS extended applications from the IDE by selecting the appropriate target from the TargetExpert selection list. To enable DPMI targeting and Turbo Vision for DOS in the IDE your `BCW.INI` file should contain these lines (automatically added by INSTALL):

```ini
[AddOns]
addon000=bcwdpmi.dll
```

The installation of the PowerPack will not always use `addon000`. If you have previously installed a product that uses this section, the install program will use `addon001` or the first free number in sequence.

The following section will also be added:

```ini
[dpmi]
bcinclude=C:\BC4\INCLUDE
bclib=C:\BC4\BIN
```

### BGI

BGI support for DOS extended applications follows a slightly different model from real mode. Now there are BGI DLLs. The `BGI16.DLL` contains most of the graphics library functionality. There are still separate driver files as in the old DOS BGI. The 32-bit BGI has a `BGI32.DLL` which provides support similar to `BGI16.DLL`. However, the 32-bit drivers are implemented as DLLs. The 32-bit drivers are kept in the `\BC4\BGI` directory for consistency.

Instead of linking with `GRAPHICS.LIB`, you should link with `BGI16.LIB` or `BGI32.LIB`, for 16-bit and 32-bit applications, respectively.

> **Note:** using BGI in a DOS extended application requires that you have the `BC4\BGI` directory in your path.

### Compatibility

- 32-bit DOS extended applications which use the ANSI C/C++ functions should run unmodified under NT.
- 32-bit DOS extended applications in general should run under DOS, NT, Windows 3.1 DOS boxes, Windows 3.11 DOS boxes and OS/2 2.x DOS boxes. Applications which use interrupts or IO instructions, or expect to have direct access to video/DOS memory will generally fail to run under NT.
- 16-bit DOS extended applications should run unmodified under DOS, NT, Windows 3.1 DOS boxes, Windows 3.11 DOS boxes and OS/2 2.x DOS boxes.

### Windows/Win32 API Emulation

The 16-bit and 32-bit extenders support emulation of most of the Windows and Win32 APIs. The libraries `DPMI16` and `DPMI32` include import records for those APIs which are emulated, so use of an unimplemented API will result in link time errors. If you need to use an API which is not implemented by the extenders, you can hook unresolved APIs and provide resolution for them at run time. To do this, you need to implement and export a hook function as follows:

```c
FARPROC WINAPI _export BorlandUnresolvedEntryHook(LPCSTR modName,
                                                   BOOL byOrdinal,
                                                   LPCSTR entry);
```

The first parameter is the name of the module for the function, for example, `"KERNEL"`. The second parameter tells whether the third parameter is a string or an ordinal value. If it is `FALSE`, then the third parameter is a string naming the unresolved entry, for example, `"GETATOMNAME"`. Your hook function should determine if it has an implementation for this entry. If it does, it should hand back a pointer to the function. This will be used by the loader to resolve the references in the image.

**Restrictions:**

- Your hook function may be called before the RTL has initialized. It may therefore call `strcmp` and a few related string functions, but little else. It should not attempt to do I/O, or allocations.
- If the application is a 16-bit application, the hook function should be in the first segment in the image, and this should be a preload segment. The hook function will have access to the automatic data segment.
- The function should not call any unimplemented APIs.

### Function Implementation

The `int86`, `int86x`, `intdos`, `intdosx`, and `intr` RTL functions will not be supported on DPMI32. The `int386` and `int386x` RTL functions should be used instead.

### Debuggers

Two debuggers are available:

| Debugger     | Purpose                          |
|--------------|----------------------------------|
| `TD.EXE`     | 16-bit application debugging     |
| `TD32.EXE`   | 32-bit application debugging     |

---

## 4. Important Information

### Delivering the Application

**16-bit applications** will always need to ship with the following files:

- `RTM.EXE`
- `DPMI16BI.OVL`

If these applications use BGI, you will have to ship `BGI16.DLL`, plus the appropriate BGI drivers and fonts.

**32-bit applications** will always need to ship with the following files:

- `32RTM.EXE`
- `DPMI32BI.OVL`

If these applications use BGI, you will have to ship `BGI32.DLL`, plus the appropriate BGI drivers and fonts.

If your 32-bit application will be run under a DOS box under Windows 3.1 or later, you will need to install `WINDPMI.386` in the user's `SYSTEM.INI` file. These files need to be on your path, or in the same directory as the application.

### Additional APIs

The following additional Windows APIs, not listed in the printed documentation, are emulated under DPMI16:

`_lclose`, `_lread`, `_lcreat`, `_lseek`, `_lopen`, `_lwrite`, `wsprintf`, `AnsiToOemBuff`, `GetCurrentTime`, `GetDesktopWindow`, `GetExePtr`, `GetPrivateProfileInt`, `GetPrivateProfileString`, `GetProfileInt`, `GetProfileString`, `GetSystemDirectory`, `GetTickCount`, `GetWindowsDirectory`, `OemToAnsiBuff`, `OpenFile`, `WritePrivateProfileString`, `WriteProfileString`

### TLookupValidator Class

The following validator class has been added to the product, but was not listed in the printed documentation:

**`TLookupValidator`** — `validate.h`

A lookup validator compares the string typed by a user with a list of acceptable values. `TLookupValidator` is an abstract validator type from which you can derive useful lookup validators. You will never create an instance of `TLookupValidator`. When you create a lookup validator type, you need to specify a list of valid items and override the `lookup` method to return `True` only if the user input matches an item in that list. One example of a working descendant of `TLookupValidator` is `TStringLookupValidator`.

**Member functions:**

- **`isValid`** — `virtual Boolean isValid(const char *s);`
  Calls `lookup` to find the string `s` in the list of valid input items. Returns `True` if `lookup` returns `True`, meaning lookup found `s` in the list; otherwise, returns `False`.

- **`lookup`** — `virtual Boolean lookup(const char *s);`
  Searches for the string `s` in the list of valid entries and returns `True` if it finds `s`; otherwise, returns `False`. `TLookupValidator`'s `lookup` is a pure virtual function that always returns `False`. Descendant lookup validator classes must override `lookup` to perform a search based on the actual list of acceptable items.

### Using the QEMM Memory Manager

If you use the QEMM memory manager, comment out the following line from your `CONFIG.SYS` file:

```
REM DEVICE=C:\QEMM\QDPMI.SYS SWAPFILE=DPMI.SWP SWAPSIZE=1024
```

This removes the QEMM DPMI Services Manager, which is not compatible with Borland's DPMI Manager `32RTM`. Only our tools (BCC32, MAKE, TLINK32, TD32 etc.) will not run under the QEMM server. Your applications will run under the QEMM server.

### Turbo Vision Palette Changes

Turbo Vision 2.0's application palette has been expanded to include Blue and Cyan dialog colors. In addition, the help colors have been incorporated into the application palette. This could cause you to get undefined symbol errors for `cpColor`, `cpBlackWhite`, `cpMonochrome`, `cHelpColor`, `cHelpBlackWhite`, and `cHelpMonochrome`.

The `cpXXXX` palettes have been renamed `cpAppXXXX`. The `cHelpXXXX` palettes are no longer defined because they were merged into the `cpAppXXXX` palettes. If you are overriding `TApplication::getPalette` to add the help colors to the application palette, remove your `getPalette` function. It is no longer needed. The help colors are now part of the application palette, and you can use the help system without any palette modifications.

If you are overriding `TApplication::getPalette` to extend the palette for your own user-defined classes, you will need to modify the palettes returned by your user-defined classes. The Turbo Vision 2.0 palette has been expanded from 63 colors to 131 colors. This means your user defined classes probably return references to palette entries 64 and up. You will need to modify your user-defined classes to return palette references 132 and up.

### NOEHxx Libraries

**Purpose:** The NOEHxx libraries eliminate the overhead of exception-handling code in the run-time library for users who don't need it and who do not rely on any libraries that require it.

**How to use:** A NOEHxx library must be linked in before the standard runtime library. For command-line tools this can be accomplished by specifying the appropriate NOEHxx library on the BCC command-line, or making it the first library given to TLINK.

For the IDE, add the appropriate library to the project using AddNode. To ensure the NOEHxx library is processed before the standard libraries, turn on "Show Runtime Nodes" in the `Options|Environment|ProjectView` dialog. From the project window you can move the library up and down using the `Alt+Arrow` keys. Be sure the NOEHxx library appears before other standard libraries.

> **Note:** use `NOEHWL.LIB` when building DPMI16 programs.

**What they do:** The NOEHxx libraries resolve calls to exception-related compiler helper functions to dummy functions that return appropriate return values. They also restore the pre-exception behavior of `operator new` to return `NULL` on out of memory conditions. Non-exception enabled versions of `setjmp()` and `longjmp()` are also provided.

**Limitations:** Some features introduced in BC4.0 require exception handling. These include the string class, BIDS container classes, the standard OWL libraries, and RTTI.

### Debuggers (Detailed)

Borland's Turbo Debugger supports both 16-bit DPMI debugging (`TD.EXE`) and 32-bit DPMI debugging (`TD32.EXE`). DPMI support services are provided by several files delivered with PowerPack for DOS, and are used by both debuggers.

- A new command-line switch has been added to `TD32.EXE`: **`-vd`**. This switch enables the use of 32-bit DPMI video DLLs. This allows users to create their own DPMI video DLLs to access BGI video modes under DPMI.

  Usage: `-vd<\path\video_dll_name>`

  PowerPack for DOS provides `SVGA32.DLL` for 32-bit DPMI BGI support. It is used in conjunction with `TD32.EXE`. When the `-vd` switch is used with `TD32.EXE`, the default `video_dll_name` is `SVGA32.DLL`. No name needs to be supplied. `SVGA32.DLL` is the default and it must be located in the same directory as `TD32.EXE`.

  Three DOS environment variables can be set to enable specific options available when using `SVGA32.DLL`:

  ```
  set SVGA32=MONO     (enables TD32.EXE dual monitor support)
  set SVGA32=COLOR    (enables TD32.EXE on a color monitor, the default behavior)
  set SVGA32DEBUG=<filename>  (Output SVGA32 diagnostic info to a log file)
  ```

  `SVGA32.DLL` is **not** required to debug 32-bit DPMI BGI applications.

- 32-bit DPMI dual-monitor support is provided within `SVGA32.DLL`. To use this dual-monitor support, set the `SVGA32` environment variable to `MONO`, and invoke `TD32.EXE` using the `-vd` command line switch.
- Remote debugging of DPMI applications is **not** currently supported.
- Mouse support is **not** currently provided for 32-bit dual-monitor debugging.
- MS Mouse driver 9.02 has known problems which render it incompatible with `TD32.EXE` and `TD.EXE` under DOS. All other mouse drivers function properly.

### Recompiling Existing Turbo Vision Applications

To recompile your existing Turbo Vision 1.0 applications with Turbo Vision 2.0, you must:

- Change `#include <tv.h>` to `#include <tvision/tv.h>` in all files.

If you are compiling in the IDE, you also must:

- Enable Turbo Vision support by right clicking on the EXE node in your project, selecting TargetExpert, turning on the Turbo Vision check box, and pressing OK.
- Update your include path by changing `Options|Project|Directories|Source Directories|Include` to `C:\BC4\INCLUDE`.
- Rebuild with `Project|Build All` to overwrite old OBJs.

### TPicResult Type and vsXXXX Constants

**`TPicResult`** — `validate.h`

```c
enum TPicResult = (prComplete, prIncomplete, prEmpty,
                   prError, prSyntax, prAmbiguous,
                   prIncompNoFill);
```

`TPicResult` is the result type returned by the `picture` member function of `TPXPictureValidator`.

See also: `TPXPictureValidator::picture`

---

**`vsXXXX` constants** — `validate.h`

Input line objects use `vsOK` to check that their associated validator objects were constructed properly. When called with a command parameter of `cmValid`, an input line object's `valid` member function checks its validator's `status` field. If `status` is `vsOK`, the input line's `valid` returns `True`, indicating that the validator object is ready to use.

The only value defined for `status` other than `vsOK` is `vsSyntax`, used by `TPXPictureValidator` to indicate that it could not interpret the picture string passed to it. If you create your own validator objects, you can define error codes and pass them in the `status` field.

| Constant   | Value | Meaning                                                                                       |
|------------|-------|-----------------------------------------------------------------------------------------------|
| `vsOK`     | 0     | Validator constructed properly                                                                |
| `vsSyntax` | 1     | Error in the syntax of either a `TPXPictureValidator` or a `TDBPictureValidator`              |

See also: `TValidator::status`

### Using the Paradox Engine with PowerPack for DOS

If you are using the Paradox Engine with executables created with the DOS PowerPack, and you receive the runtime error message:

> Unable to locate GDI.DLL

this means that your executable attempted to load an old version of `PXENGWIN.DLL`. Make sure that you are using version 3.01 of the Paradox Engine and that there are no older versions being found first on your path. If you do not have version 3.01 of the Paradox Engine you can obtain an upgrade by calling the Borland Order Desk at (800) 645-4559. Outside of North America contact your local Borland office.

---

## 5. Miscellaneous Information

### CD Only Configuration Install

If you have done the CD Only Configuration install, you will need to update your Turbo Vision example files by doing the following:

For each example:

1. Select the **Options** menu
2. Select the **Project** option
3. Modify the Include Source Directory to show `<CD-ROM drive>:\BC4\INCLUDE;<path you installed the PowerPack to>`
4. Modify the Library Source Directory to show `<CD-ROM drive>:\BC4\LIB;<path you installed the PowerPack to>`
5. Press the **OK** button

Doing these steps sets both your CD-ROM INCLUDE and LIBRARY paths, and your PowerPack INCLUDE and LIBRARY paths.

If you have done the CD Only Configuration install, then you must change the BC DOS & Library Icon help-file path (in the Borland C++ group) from the CD to your hard drive.

### Changing Target Type

If you change the target type for an application from DPMI16 to DPMI32 or vice-versa, you must **rebuild** the application. If you only request a MAKE, the application will not be built correctly, because MAKE logic is based on the time and date stamp.

### Reinstallation

If you reinstall any portion of Borland C++ after installing the PowerPack, some PowerPack environment settings may be lost. If this happens, reinstall the PowerPack.

### Novell Compatibility

There is a known incompatibility between Novell DOS 7 and DPMI hosted tools contained in this product. This same incompatibility exists for DPMI-hosted applications generated from these tools.

### Phar Lap Compatibility

When running protected-mode applications that use Phar Lap's DOS extender and which will spawn applications using Borland's DOS extender (for example NMAKE), load `32RTM` first. This will cause Borland's DPMI server to be used, which is compatible with both DOS extenders.

### Additional Examples

Additional examples can be found on CompuServe in library 7 of the BCPPDOS forum and on the Borland BBS (408)-431-5096 (N81, 19.2k).

The file `PP10E1.ZIP` contains the following examples and subdirectories:

| Directory   | Description                                                                                              |
|-------------|----------------------------------------------------------------------------------------------------------|
| `INT32`     | Allows for writing 32-bit interrupt handlers in C                                                        |
| `LINEAR`    | Allows access to text/graphics memory from a pointer in 32-bit C (No assembly or selector loads needed)  |
| `MOUSE`     | Example of a mouse handler in graphics mode. Works in Real, DPMI16 and DPMI32 mode.                     |
| `TIMER32`   | Shows how to hook and handle the timer (int-8) in a 32-bit program.                                     |

---

## 6. Installation Instructions (PINSTALL)

### System Requirements

Before installing the PowerPack please review the minimum system requirements listed below:

- BC++ 4.02 or later
- 4 MB Extended Memory
- Intel 386 or higher
- DOS 4.01 or later
- Approximately 3.5 MB hard disk space
- 3.5" High Density Disk Drive

### Installing Borland PowerPack for DOS

#### A) Pre-Installation Notes

**Backup Disks:** If you wish to make backup copies of your original disks use the DOS `DISKCOPY` command. You must use the same disk size and media (density) when you make your backup set of disks. Attempting to copy from 3.5" to 5.25" will cause the install program to fail. If you have a bad disk contact Borland's Disk Replacement line at **(800) 742-4045** or **(800) 231-2167** outside California.

#### B) Installation Instructions

1. Insert the PowerPack installation disk into drive A or B.
2. From the DOS prompt type `A:INSTALL` (or `B:INSTALL`) and press ENTER.
3. Read the opening screen, then press ENTER to continue.
4. When prompted, "enter the SOURCE drive to use:", specify the drive from which you will install if it is different than the default. Press ENTER to continue.
5. Make sure the "Borland C++ Directory..." entry shows the correct drive and path to your BC++ 4.02 or later installation.

   Make sure the "Windows Directory..." entry shows the correct drive and path to your Windows directory.

   If you performed a CD Only Config. Installation for Borland C++, then make sure the "CD-ROM" entry shows YES and the "CD-ROM Binary Directory..." shows the correct drive and path to your Borland C++ (`X:\BC4\BIN`, where X is your CD-ROM drive). Make sure the Borland C++ CD-ROM is in the CD-ROM drive.

6. Choose "Start Installation" to begin installation.

#### C) After Installation

After the install has completed, the README file appears. The README file contains important information about configuring and using the PowerPack, including late changes which might have occurred after the manuals were printed.

### Modifications the Install Program Makes to Your System

This section describes the modifications that are made to the files in your Windows directory. Please note that these are example modifications based on a default installation.

**Files changed in the Windows directory:**

`BCW.INI` modifications:

```ini
[AddOns]
addon000=bcwdpmi.dll

[dpmi]
bcinclude=C:\BC4\INCLUDE
bclib=c:\BC4\LIB
```

The installation of the PowerPack will not always use `addon000`. If you have previously installed a product that uses this section, the install program will use `addon001` or the first free number in sequence.

If performing an install of the PowerPack with a CD Only Configuration of Borland C++, then your PATH will be updated to include the directory to which the PowerPack was installed.

**Files added to your BC4 directory:** see the PFILELST section [below](#7-alphabetized-list-of-product-files-pfilelst) for a complete listing.

---

## 7. Alphabetized List of Product Files (PFILELST)

### BCW.PAK (Disk 2)

| File            | Description            |
|-----------------|------------------------|
| `BCWDPMI.DLL`   | BCW support file       |

### BGI16DLL.PAK (Disk 2)

| File          | Description                                  |
|---------------|----------------------------------------------|
| `ATT.BGX`     | Graphics driver for ATT400 graphics card     |
| `BGI16.DLL`   | DPMI16 drivers                               |
| `CGA.BGX`     | Graphics driver for CGA                      |
| `EGAVGA.BGX`  | Graphics driver for EGA and VGA              |
| `HERC.BGX`    | Graphics driver for Hercules                 |
| `IBM8514.BGX` | Graphics driver for IBM 8514 graphics card   |
| `PC3270.BGX`  | Graphics driver for PC3270                   |
| `VESA16.BGX`  | BGI driver for VESA                          |

### BGI16LIB.PAK (Disk 2)

| File         | Description         |
|--------------|---------------------|
| `BGI16.LIB`  | DPMI16 BGI library  |

### BGI32DLL.PAK (Disk 2)

| File           | Description                            |
|----------------|----------------------------------------|
| `BGI32.DLL`    | BGI32 DLL file                         |
| `BGIEGA.DLL`   | 32-bit BGI Driver (Metagraphics)       |
| `BGIMONO.DLL`  | 32-bit BGI Driver (Metagraphics)       |
| `BGIN__01.FNT` | 32-bit BGI Driver Library (Metagraphics) |
| `BGIN__02.FNT` | BGI32 font file                        |
| `BGIN__03.FNT` | BGI32 font file                        |
| `BGIN__04.FNT` | BGI32 font file                        |
| `BGIR__01.FNT` | BGI32 font file                        |
| `BGIR__02.FNT` | BGI32 font file                        |
| `BGIR__03.FNT` | BGI32 font file                        |
| `BGIR__04.FNT` | BGI32 font file                        |
| `BGIVGA.DLL`   | 32-bit BGI Driver (Metagraphics)       |
| `BOLD.FNT`     | BGI32 font file                        |
| `EURO.FNT`     | BGI32 font file                        |
| `GOTH.FNT`     | BGI32 font file                        |
| `LCOM.FNT`     | BGI32 font file                        |
| `LITT.FNT`     | BGI32 font file                        |
| `SANS.FNT`     | BGI32 font file                        |
| `SCRI.FNT`     | BGI32 font file                        |
| `SIMP.FNT`     | BGI32 font file                        |
| `TRIP.FNT`     | BGI32 font file                        |
| `TSCR.FNT`     | BGI32 font file                        |

### BGI32LIB.PAK (Disk 2)

| File         | Description                              |
|--------------|------------------------------------------|
| `BGI32.LIB`  | 32-bit BGI Driver Library (Metagraphics) |

### CRIT.PAK (Disk 2)

| File            | Description    |
|-----------------|----------------|
| `CRITDEMO.C`    | DPMI examples  |
| `CRITDEMO.DEF`  | DPMI examples  |
| `CRITDEMO.IDE`  | DPMI examples  |
| `CRITERR.ASM`   | DPMI examples  |
| `MAKEFILE`       | DPMI examples  |

### CTRL.PAK (Disk 2)

| File            | Description    |
|-----------------|----------------|
| `CTRL.ASM`      | DPMI examples  |
| `CTRLDEMO.C`    | DPMI examples  |
| `CTRLDEMO.DEF`  | DPMI examples  |
| `CTRLDEMO.IDE`  | DPMI examples  |
| `MAKEFILE`       | DPMI examples  |

### D16BIN.PAK (Disk 2)

| File          | Description        |
|---------------|--------------------|
| `16STUB.EXE`  | 16-bit stub file   |

### D16LIB.PAK (Disk 2)

| File          | Description              |
|---------------|--------------------------|
| `C0X.OBJ`     | DPMI16 EXE startup       |
| `DPMI16.LIB`  | DPMI16 import library    |
| `EMUX.LIB`    | DPMI16 math emulator     |

### D32BIN.PAK (Disk 2)

| File          | Description          |
|---------------|----------------------|
| `32RTM.EXE`   | 32-bit DOS extender  |
| `32STUB.EXE`  | 32-bit stub file     |

### D32LIB.PAK (Disk 2)

| File          | Description              |
|---------------|--------------------------|
| `DPMI32.LIB`  | DPMI32 import library    |

### DOCDEMO.PAK (Disk 2)

| File            | Description              |
|-----------------|--------------------------|
| `BUILD.BAT`     | Build script file        |
| `DOCDEMOS.IDE`  | Doc demo project file    |
| `MAKEFILE`       | Doc Demo makefile        |
| `TVG17B.CPP`    | Turbo Vision GUI Demo    |
| `TVGUID01.CPP` — `TVGUID21.CPP` | Turbo Vision GUI Demo (21 files) |

### DOSPTR.PAK (Disk 2)

| File           | Description         |
|----------------|---------------------|
| `DOSPTR.CPP`   | DPMI example files  |
| `DOSPTR.IDE`   | DPMI example files  |
| `MAKEFILE`      | DPMI example files  |

### FILEVIEW.PAK (Disk 2)

| File            | Description                        |
|-----------------|------------------------------------|
| `FILEVIEW.CPP`  | File view window                   |
| `FILEVIEW.H`    | Header for file view window        |
| `FILEVIEW.IDE`  | Fileview project file              |
| `FVIEWER.CPP`   | Main program for file view demo    |
| `MAKEFILE`       |                                    |
| `TVCMDS.H`      | TVISION demo file                  |

### HELLO.PAK (Disk 2)

| File          | Description                      |
|---------------|----------------------------------|
| `HELLO.CPP`   | Main program for hello demo      |
| `HELLO.IDE`   | Hello project file               |
| `MAKEFILE`     |                                  |

### HELPDOS.PAK (Disk 1)

| File          | Description           |
|---------------|-----------------------|
| `BCDOS.HLP`   | DPMI DOS help file    |
| `BHBC4.HDX`   | DPMI DOS help file    |
| `HELP.ICO`    | Borland help icon     |

### Standalone Files

| File           | Disk   | Description                    |
|----------------|--------|--------------------------------|
| `INSTALL.EXE`  | Disk 1 | Installation program           |
| `INSTALL.TXT`  | Disk 1 | Install text file              |
| `README`       | Disk 1 |                                |
| `README.COM`   | Disk 1 |                                |
| `UNPAK.EXE`    | Disk 1 | Program to decompress files    |

### LOWMEM.PAK (Disk 2)

| File           | Description         |
|----------------|---------------------|
| `LOWMEM.H`     | DPMI example file   |
| `LOWMEM16.C`   | DPMI example file   |
| `LOWMEM32.C`   | DPMI example file   |
| `MAKEFILE`      | DPMI example file   |
| `MEMDEMO.C`    | DPMI example file   |
| `MEMDEMO.IDE`  | DPMI example file   |

### SCREEN32.PAK (Disk 2)

| File            | Description         |
|-----------------|---------------------|
| `MAKEFILE`       | DPMI example file   |
| `SCREEN32.C`    | DPMI example file   |
| `SCREEN32.IDE`  | DPMI example file   |

### T16COMP.PAK (Disk 2)

Compatibility object files for 16-bit Turbo Vision:

`EDITS.OBJ`, `FRAMELIN.OBJ`, `HARDWARE.OBJ`, `SWAPST.OBJ`, `SYSINT.OBJ`, `TGRMV.OBJ`, `TTPRVLNS.OBJ`, `TVCURSOR.OBJ`, `TVEXPOSD.OBJ`, `TVWRITE.OBJ`

### T16LIB.PAK (Disk 1)

| File      | Description                      |
|-----------|----------------------------------|
| `TV.LIB`  | Real-mode Turbo Vision library   |

### T32COMP.PAK (Disk 2)

Compatibility object files for 32-bit Turbo Vision:

`EDITS.OBJ`, `FRAMELIN.OBJ`, `HARDWARE.OBJ`, `SWAPST.OBJ`, `SYSINT.OBJ`, `TGRMV.OBJ`, `TTPRVLNS.OBJ`, `TVCURSOR.OBJ`, `TVEXPOSD.OBJ`, `TVWRITE.OBJ`

### T32LIB.PAK (Disk 2)

| File        | Description                       |
|-------------|-----------------------------------|
| `TV32.LIB`  | DPMI32 Turbo Vision library       |

### TDDLL.PAK (Disk 2)

| File          | Description |
|---------------|-------------|
| `SVGA32.DLL`  |             |

### TDX.PAK (Disk 2)

| File            | Description |
|-----------------|-------------|
| `TDXDEBUG.DLL`  |             |

### TVBGI.PAK (Disk 1)

| File            | Description                               |
|-----------------|-------------------------------------------|
| `GRAPHAPP.CPP`  | Graphics utilities for BGI and TV demo    |
| `GRAPHAPP.H`    | Header file for graphics utilities        |
| `MAKEFILE`       |                                           |
| `TVBGI.CPP`     | BGI and TV demo                           |
| `TVBGI.H`       | Header for BGI and TV demo               |
| `TVBGI.IDE`     | TVBGI project file                        |

### TVDEMO.PAK (Disk 2)

| File             | Description               |
|------------------|---------------------------|
| `ASCII.CPP`      | ASCII demo                |
| `ASCII.H`        | ASCII demo                |
| `CALC.CPP`       | Calc demo                 |
| `CALC.H`         | Calc demo                 |
| `CALENDAR.CPP`   | Calendar demo             |
| `CALENDAR.H`     | Calendar demo             |
| `DEMOHELP.H`     | Demo help file            |
| `DEMOHELP.H16`   | Turbo Vision example file |
| `DEMOHELP.H32`   | Turbo Vision example file |
| `FILEVIEW.CPP`   | File viewer example       |
| `FILEVIEW.H`     | File viewer demo          |
| `GADGETS.CPP`    | Gadgets demo              |
| `GADGETS.H`      | Gadgets demo              |
| `MAKEFILE`        | Demo makefile             |
| `MOUSEDLG.CPP`   | Mouse dialog demo         |
| `MOUSEDLG.H`     | Mouse dialog demo         |
| `PUZZLE.CPP`     | Puzzle demo               |
| `PUZZLE.H`       | Puzzle demo               |
| `TVCMDS.H`       | Turbo Vision demo         |
| `TVDEMO.H`       | Turbo Vision demo         |
| `TVDEMO.IDE`     | TV demo project file      |
| `TVDEMO1.CPP`    | Turbo Vision demo         |
| `TVDEMO2.CPP`    | Turbo Vision demo         |
| `TVDEMO3.CPP`    | Turbo Vision demo         |

### TVDIR.PAK (Disk 2)

| File          | Description                  |
|---------------|------------------------------|
| `MAKEFILE`     | Turbo Vision example file    |
| `TVDIR.CPP`   | Turbo Vision example file    |
| `TVDIR.IDE`   | Turbo Vision example file    |

### TVEDIT.PAK (Disk 2)

| File           | Description                             |
|----------------|-----------------------------------------|
| `MAKEFILE`      |                                         |
| `TVEDIT.H`     | Header file for tvedit demo             |
| `TVEDIT.IDE`   | Tvedit project file                     |
| `TVEDIT1.CPP`  | Main source file for tvedit demo        |
| `TVEDIT2.CPP`  | Support source file for tvedit demo     |
| `TVEDIT3.CPP`  | Support source file for tvedit demo     |

### TVFORMS.PAK (Disk 2)

| File            | Description                              |
|-----------------|------------------------------------------|
| `DATACOLL.CPP`  | Support source file for tvforms demo     |
| `DATACOLL.H`    | Support header file for tvforms demo     |
| `FIELDS.CPP`    | Support source file for tvforms demo     |
| `FIELDS.H`      | Support header file for tvforms demo     |
| `FORMCMDS.H`    | Support header file for tvforms demo     |
| `FORMS.CPP`     | Support source file for tvforms demo     |
| `FORMS.H`       | Support header file for tvforms demo     |
| `GENFORM.CPP`   | Support source file for tvforms demo     |
| `GENFORMS.MAK`  | Make file to create forms for tvforms demo |
| `GENPARTS.H`    | Header file for genform.cpp              |
| `GENPHONE.H`    | Header file for genform.cpp              |
| `LISTDLG.CPP`   | Support source file for tvforms demo     |
| `LISTDLG.H`     | Support header file for tvforms demo     |
| `MAKEFILE`       |                                          |
| `TVFORMS.CPP`   | Main source file for tvforms demo        |
| `TVFORMS.IDE`   | Tvforms project file                     |

### TVHELP.PAK (Disk 2)

| File            | Description                             |
|-----------------|-----------------------------------------|
| `DEMOHELP.TXT`  | Sample help text file                   |
| `MAKEFILE`       |                                         |
| `TVHC.CPP`      | Main source file for TV help compiler   |
| `TVHC.H`        | Header file for tvhc.cpp               |

### TVINC.PAK (Disk 2)

Turbo Vision header files:

`APP.H`, `BUFFERS.H`, `COLORSEL.H`, `CONFIG.H`, `DIALOGS.H`, `DRAWBUF.H`, `EDITORS.H`, `HARDWARE.H`, `HELP.H`, `HELPBASE.H`, `MENUS.H`, `MSGBOX.H`, `OBJECTS.H`, `OUTLINE.H`, `RESOURCE.H`, `STDDLG.H`, `SYSTEM.H`, `TEXTVIEW.H`, `TKEYS.H`, `TOBJSTRM.H`, `TTYPES.H`, `TV.H`, `TVOBJS.H`, `UTIL.H`, `VALIDATE.H`, `VIEWS.H`

### TVPXENG.PAK (Disk 2)

| File            | Description                  |
|-----------------|------------------------------|
| `MAKEFILE`       | TurboVision example file     |
| `README.TXT`    | DPMI example file            |
| `TIS.DB`        | TurboVision example file     |
| `TVPXENG.CPP`   | TurboVision example file     |
| `TVPXENG.DEF`   | TurboVision example file     |
| `TVPXENG.IDE`   | DPMI example file            |

### TVSRC.PAK (Disk 2)

Turbo Vision source files:

| File             | Description                           |
|------------------|---------------------------------------|
| `COLORSEL.CPP`   | Turbo Vision source file              |
| `DRIVERS.CPP`    | Turbo Vision source file              |
| `DRIVERS2.CPP`   | Turbo Vision source file              |
| `EDITS.ASM`      | Turbo Vision source file              |
| `EDITSTAT.CPP`   | Turbo Vision source file              |
| `FRAMELIN.ASM`   | Turbo Vision source file              |
| `GENINC.CPP`     | Turbo Vision source file              |
| `GRP.CPP`        | Turbo Vision source file              |
| `HARDWARE.ASM`   | Turbo Vision source file              |
| `HARDWRVR.CPP`   | Turbo Vision source file              |
| `HELP.CPP`       | Turbo Vision source file              |
| `HELPBASE.CPP`   | Turbo Vision source file              |
| `HISTLIST.CPP`   | Turbo Vision source file              |
| `MAKEFILE`        | Turbo Vision library makefile         |
| `MAPCOLOR.CPP`   | Turbo Vision source file              |
| `MENU.CPP`       | Turbo Vision source file              |
| `MISC.CPP`       | Turbo Vision source file              |
| `MSGBOX.CPP`     | Turbo Vision source file              |
| `NEW.CPP`        | Turbo Vision source file              |
| `NEWSTR.CPP`     | Turbo Vision source file              |
| `NM*.CPP`        | Static names (50+ files)              |
| `PALETTE.CPP`    | Turbo Vision source file              |
| `S*.CPP`         | Turbo Vision stream/source files (50+ files) |
| `STDDLG.CPP`    | Turbo Vision source file              |
| `STRMSTAT.CPP`   | Turbo Vision source file              |
| `SWAPST.ASM`     | Turbo Vision source file              |
| `SYSERR.CPP`     | Turbo Vision source file              |
| `SYSINT.ASM`     | Turbo Vision source file              |
| `T*.CPP`         | Turbo Vision implementation files (50+ files) |
| `TEVENT.CPP`     | Turbo Vision source file              |
| `TEXTVIEW.CPP`   | Turbo Vision source file              |
| `TGRMV.ASM`      | Turbo Vision source file              |
| `TTPRVLNS.ASM`   | Turbo Vision source file              |
| `TV.INC`         | Turbo Vision source file              |
| `TVALIDAT.CPP`   | Turbo Vision source file              |
| `TVCURSOR.ASM`   | Turbo Vision source file              |
| `TVEXPOSD.ASM`   | Turbo Vision source file              |
| `TVTEXT1.CPP`    | Turbo Vision source file              |
| `TVTEXT2.CPP`    | Turbo Vision source file              |
| `TVWRITE.ASM`    | Turbo Vision source file              |

### TVTREE.PAK (Disk 2)

| File           | Description                  |
|----------------|------------------------------|
| `TVTREE.CPP`   | Turbo Vision example file    |
| `TVTREE.IDE`   | Turbo Vision example file    |

### TVTXTDEM.PAK (Disk 2)

| File             | Description                             |
|------------------|-----------------------------------------|
| `MAKEFILE`        |                                         |
| `TVTXTDEM.CPP`   | Main source file for tvtext demo        |
| `TVTXTDEM.IDE`   | Tvtxtdem project file                   |

### WINLIB16.PAK (Disk 1)

| File            | Description |
|-----------------|-------------|
| `WILDARGX.OBJ`  |             |
