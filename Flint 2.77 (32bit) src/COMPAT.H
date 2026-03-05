/***********************************************************************
    COMPAT.H
    Compatibility layer: Borland C++ -> Open Watcom C++ (DOS/4GW 32-bit)
    FLINT+ v2.61 port
***********************************************************************/
#ifndef __COMPAT_H
#define __COMPAT_H

#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <direct.h>
#include <string.h>
#include <i86.h>
#include <dos.h>
#include <bios.h>

/*--- I/O port access: Borland -> Watcom ---*/
/* Add I/O bus delay after port writes to match 16-bit Borland C timing.
   Without this, consecutive 8254 PIT writes may be too fast for the chip
   to latch values correctly. Reading port 0x80 inserts ~1us ISA bus delay. */
#define inportb(p)      ((unsigned char)inp((p)))
static void __inline _compat_iodelay(void) { inp(0x80); }
#define outportb(p,v)   do { outp((p),(v)); _compat_iodelay(); } while(0)

/*--- Far memory: Borland -> Watcom flat model ---*/
#define farmalloc(s)    malloc((s))
#define farfree(p)      free((p))
#define farcoreleft()   _memavl()

/*--- Drive/directory: Borland -> Watcom ---*/
/* Borland: getdisk() returns 0=A, 1=B, ...
   Watcom:  _getdrive() returns 1=A, 2=B, ... */
#define getdisk()       (_getdrive()-1)
#define setdisk(d)      _chdrive((d)+1)

/* Borland: getcurdir(drive, buf) where drive 0=current, 1=A, ...
   Watcom: _getdcwd(drive, buf, size) where drive 0=current, 1=A, ... */
static char _compat_cwd_buf[256];
inline void getcurdir(int drive, char *buf) {
    _getdcwd(drive, _compat_cwd_buf, 256);
    /* Skip "X:\" prefix to match Borland getcurdir behavior */
    char *p = _compat_cwd_buf;
    if(p[1] == ':' && (p[2] == '\\' || p[2] == '/')) p += 3;
    strcpy(buf, p);
}

/*--- BIOS keyboard: Borland -> Watcom ---*/
/* Borland: bioskey(0)=read, bioskey(1)=ready
   Watcom:  _bios_keybrd(_KEYBRD_READ), _bios_keybrd(_KEYBRD_READY) */
inline int bioskey(int cmd) {
    if(cmd == 0) return _bios_keybrd(_KEYBRD_READ);
    if(cmd == 1) return _bios_keybrd(_KEYBRD_READY);
    return 0;
}

/*--- BIOS disk: Borland -> Watcom ---*/
/* Borland: biosdisk(cmd, drive, head, track, sector, nsects, buffer)
   Watcom:  _bios_disk(cmd, &diskinfo) */
#include <bios.h>
inline int biosdisk(int cmd, int drive, int head, int track,
                    int sector, int nsects, void *buffer) {
    struct diskinfo_t di;
    di.drive    = drive;
    di.head     = head;
    di.track    = track;
    di.sector   = sector;
    di.nsectors = nsects;
    di.buffer   = buffer;
    unsigned status = _bios_disk(cmd, &di);
    return (status >> 8);  /* Borland returns status in AH */
}

/*--- Date: Borland -> Watcom ---*/
/* Borland: struct date { int da_year, da_day, da_mon; } + getdate(&d)
   Watcom:  struct dosdate_t { ... } + _dos_getdate(&d) */
struct date {
    int da_year;
    char da_day;
    char da_mon;
};

inline void getdate(struct date *d) {
    struct dosdate_t dd;
    _dos_getdate(&dd);
    d->da_year = dd.year;
    d->da_mon  = dd.month;
    d->da_day  = dd.day;
}

/*--- findfirst/findnext: Borland -> Watcom ---*/
/* Watcom: _dos_findfirst/_dos_findnext with struct find_t from <dos.h> */

struct ffblk {
    char ff_name[14];
    unsigned ff_attrib;
    /* internal storage for Watcom find_t */
    struct find_t _ft;
};

#define FA_DIREC _A_SUBDIR

inline int findfirst(const char *pattern, struct ffblk *ffbl, int attrib) {
    unsigned rc = _dos_findfirst(pattern, attrib, &ffbl->_ft);
    if(rc) return -1;
    strncpy(ffbl->ff_name, ffbl->_ft.name, 13);
    ffbl->ff_name[13] = 0;
    ffbl->ff_attrib = (unsigned char)ffbl->_ft.attrib;
    return 0;
}

inline int findnext(struct ffblk *ffbl) {
    unsigned rc = _dos_findnext(&ffbl->_ft);
    if(rc) return -1;
    strncpy(ffbl->ff_name, ffbl->_ft.name, 13);
    ffbl->ff_name[13] = 0;
    ffbl->ff_attrib = (unsigned char)ffbl->_ft.attrib;
    return 0;
}

/*--- PC speaker: Borland sound()/nosound() ---*/
inline void sound(unsigned freq) {
    unsigned divisor;
    if(freq == 0) return;
    divisor = 1193180 / freq;
    outp(0x43, 0xB6);                    /* PIT channel 2, mode 3 */
    outp(0x42, divisor & 0xFF);          /* low byte */
    outp(0x42, (divisor >> 8) & 0xFF);   /* high byte */
    outp(0x61, inp(0x61) | 0x03);        /* enable speaker */
}

inline void nosound(void) {
    outp(0x61, inp(0x61) & 0xFC);        /* disable speaker */
}

/*--- Precise delay: Borland delay() replacement for Watcom ---*/
/* Watcom's delay() uses INT 21h/AH=2Ch with ~55ms resolution.
   This reads system PIT channel 0 (port 0x40) to measure elapsed
   time with ~1us accuracy.  Non-invasive: does NOT reprogram any
   timer, only latches and reads the existing counter.
   PIT ch0 runs in mode 3 (square wave): counter decrements by 2
   per clock tick.  PIT frequency: 1193182 Hz.
   Counter units per ms = 1193182/1000 * 2 = ~2386. */
inline void pit_delay_ms(unsigned ms) {
    unsigned long total = (unsigned long)ms * 2386UL;
    unsigned long elapsed = 0;
    unsigned int prev, curr;
    outp(0x43, 0x00);          /* latch ch0 */
    prev  = (unsigned int)inp(0x40);
    prev |= (unsigned int)inp(0x40) << 8;
    while(elapsed < total) {
        outp(0x43, 0x00);      /* latch ch0 */
        curr  = (unsigned int)inp(0x40);
        curr |= (unsigned int)inp(0x40) << 8;
        if(curr <= prev)
            elapsed += (unsigned long)(prev - curr);
        else
            elapsed += (unsigned long)prev + 65536UL - (unsigned long)curr;
        prev = curr;
    }
}
#define delay pit_delay_ms

/*--- Mouse cursor macros: Borland pseudo-registers -> Watcom int386 ---*/
#define CURSOR_ON()  { union REGS _r; _r.w.ax=1; int386(0x33,&_r,&_r); }
#define CURSOR_OFF() { union REGS _r; _r.w.ax=2; int386(0x33,&_r,&_r); }

/*--- Misc: stricmp -> matches Watcom ---*/
/* stricmp is available in Watcom, no change needed */

/*--- MAXPATH, MAXDIR, MAXDRIVE etc. ---*/
#ifndef MAXPATH
#define MAXPATH 260
#endif
#ifndef MAXDIR
#define MAXDIR  256
#endif

#endif /* __COMPAT_H */
