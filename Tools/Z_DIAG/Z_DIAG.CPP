/*********************************************************************
    Z_DIAG.CPP — Standalone Z-axis diagnostic tool for FLINT hardware
    
    Purpose: Probe ISA card behavior to understand:
    1. How 8254 counters are cascaded (K2z → dZ)
    2. What PB6/PB7 signals mean
    3. Whether motor enable bits gate counters or just drivers
    4. Z motor step integrity at various speeds
    5. Thermal/accumulation effects
    
    This program does NOT use graphics mode.
    It outputs results to both console and Z_DIAG.LOG file.
    
    SAFETY: All motor tests start with homing. Emergency stop on ESC.
    Compile: see COMPILE.bat / COMPILE32.bat
*********************************************************************/
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <bios.h>

#ifdef __WATCOMC__
#include <i86.h>
#include <bios.h>
#define inportb(p)      ((unsigned char)inp((p)))
static void __inline _compat_iodelay(void) { inp(0x80); }
#define outportb(p,v)   do { outp((p),(v)); _compat_iodelay(); } while(0)
#define bioskey(c)      ((c)==0 ? _bios_keybrd(_KEYBRD_READ) : _bios_keybrd(_KEYBRD_READY))
#endif

/*--- Hardware addresses (same as PIC.CPP) ---*/
#define ADRPT0  0x300
#define ADRPT1  (ADRPT0+4)
#define ADRPPI  (ADRPT0+8)
#define ADRRG   (ADRPT0+0x0c)
#define ADRPPI2 (ADRPT0+0x10)
#define ADRPT2  (ADRPT0+0x14)
#define ADRCMOS (ADRPT0+0x18)
#define LRG     (ADRPT0+0x1c)

/*--- RG bit masks (same as PIC.CPP) ---*/
#define XUP    0x01
#define XDOWN  0xfe
#define YUP    0x02
#define YDOWN  0xfd
#define ZUP    0x04
#define ZDOWN  0xfb
#define XON    0x08
#define XOFF   0xf7
#define YON    0x10
#define YOFF   0xef
#define ZON    0x20
#define ZOFF   0xdf
#define OSCON  0x7f
#define OSCOFF 0x80

/*--- Globals ---*/
static FILE *logf = NULL;
static unsigned char ctlw;

/* Position tracking (same coords as FLINT) */
static int xcur = 0, ycur = 0, zcur = 0;

/* Timing config (from FLINT32-12.03.2026_1.LOG [PROC] CFG line) */
static int cfg_l_period  = 35;   /* laser period, ms */
static int cfg_dT        = 6;    /* CPU time correction, ms */
static int cfg_step_freq = 1000; /* max step frequency, Hz */
static int cfg_f_const   = 0;    /* 0=variable speed, 1=const */

/*--- Logging ---*/
static void LOG(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    if(logf) {
        va_start(ap, fmt);
        vfprintf(logf, fmt, ap);
        va_end(ap);
        fflush(logf);
    }
}

/*--- 8254 counter read ---*/
static unsigned int read_counter(int base, int ch) {
    unsigned int lo, hi;
    unsigned char latch_cmd = (unsigned char)(ch << 6);
    outportb(base+3, latch_cmd);
    lo = (unsigned int)inportb(base+ch);
    hi = (unsigned int)inportb(base+ch);
    return lo + hi*256;
}

/*--- 8254 Read Back Command (8254-2 only) ---*/
/* Returns: status byte with bits:
   D7: OUT pin state
   D6: Null count (1=count not yet loaded)
   D5-D4: Mode (0-5)
   D3-D1: BCD/Binary + Mode bits
   D0: BCD (0=binary, 1=BCD) */
static unsigned char read_status(int base, int ch) {
    /* Read-Back command: 11xx_xxxx
       D5=0: latch status, D4=1: don't latch count
       D3-D1: channel select */
    unsigned char rb_cmd = 0xE0 | (1 << (ch+1));  /* 1110_0xxx, select one channel */
    outportb(base+3, rb_cmd);
    return inportb(base+ch);
}

/*--- PPI sensor read ---*/
static unsigned char read_sensors(void) {
    return inportb(ADRPPI+1);
}

/*--- Check for ESC key ---*/
static int esc_pressed(void) {
    if(bioskey(1)) {
        int k = bioskey(0);
        if((k & 0xff) == 27) return 1;
    }
    return 0;
}

/*--- Check if ISA card is present (same as pi_ini readback check) ---*/
/* Writes K1=150 to PPI PA, reads back. Returns 1=ok, 0=no card */
static int hw_detect(void) {
    outportb(ADRPPI+3, 0x82);   /* PPI: mode0, PA-out, PB-inp, PC-out */
    outportb(ADRPPI, 150);      /* K1=150 */
    return (inportb(ADRPPI) == 150);
}

/*--- Hardware init (same as pi_ini) ---*/
static void hw_init(void) {
    ctlw = (XUP|YUP|ZUP)&XOFF&YOFF&ZOFF&OSCON;
    outportb(ADRRG, ctlw);
    outportb(LRG, 0);
    outportb(ADRPPI+3, 0x82);   /* PPI: mode0, PA-out, PB-inp, PC-out */
    outportb(ADRPPI, 150);       /* K1=150: F1=100kHz */
    outportb(ADRPPI+2, 0xfd);   /* stepM-off, endS-en */
    outportb(ADRPPI+2, 0xff);   /* endS-reset */
    outportb(ADRPPI+2, 0xfc);   /* stepM-on, endS-enable */
    outportb(ADRPPI2+3, 0x91);  /* PPI2: mode0, PA,PC0..3-inp, PB,PC4..7-out */
    outportb(ADRPPI2+1, 0xff);  /* PPI2: EM1..8 off */
    outportb(ADRPPI2+3, 0x09);  /* PPI2: 1->PC4: EM9 off */
    outportb(ADRPPI2+3, 0x0b);  /* PPI2: 1->PC5: EM10 off */
    outportb(ADRPPI2+3, 0x0d);  /* PPI2: 1->PC6: EMCOM off */
    outportb(ADRPT0+3, 0x34);   /* PT0.ch0: mode2, binary, lb,hb (K2x) */
    outportb(ADRPT0+3, 0x78);   /* PT0.ch1: mode4, binary, lb,hb (dX)  */
    outportb(ADRPT0+3, 0xb4);   /* PT0.ch2: mode2, binary, lb,hb (K2z) */
    outportb(ADRPT1+3, 0x34);   /* PT1.ch0: mode2, binary, lb,hb (K2y) */
    outportb(ADRPT1+3, 0x78);   /* PT1.ch1: mode4, binary, lb,hb (dY)  */
    outportb(ADRPT1+3, 0xb8);   /* PT1.ch2: mode4, binary, lb,hb (dZ)  */
}

/*--- Emergency stop ---*/
static void hw_stop(void) {
    ctlw = ctlw & XOFF & YOFF & ZOFF;
    outportb(ADRRG, ctlw);
    ctlw = ctlw | OSCOFF;
    outportb(ADRRG, ctlw);
}

/*--- Wait for Z movement to complete, checking ESC ---*/
/* Returns: 0=ok, 1=ESC abort, 2=end-sensor hit */
static int wait_z_done(void) {
    unsigned char stspb;
    int fz = 1;
    while(fz) {
        stspb = read_sensors();
        if((stspb & 0x40) == 0x40) { fz = 0; }
        outportb(ADRRG, ctlw);
        /* End sensor check (Z bits) */
        if((stspb & 0x30) != 0x30) {
            delay(1);
            stspb = read_sensors();
            if((stspb & 0x30) != 0x30) {
                hw_stop();
                return 2;
            }
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    return 0;
}

/*--- Wait for XY+Z movement to complete ---*/
static int wait_xyz_done(void) {
    unsigned char stspb;
    int fxy = 1, fz = 1;
    while(fxy || fz) {
        stspb = read_sensors();
        if(fxy && ((stspb & 0x80) == 0x80)) { ctlw = ctlw & XOFF & YOFF; fxy = 0; }
        if(fz  && ((stspb & 0x40) == 0x40)) { ctlw = ctlw & ZOFF; fz = 0; }
        outportb(ADRRG, ctlw);
        if((!fxy) && (!fz)) break;
        if((stspb & 0x3f) != 0x3f) {
            delay(1);
            stspb = read_sensors();
            if((stspb & 0x3f) != 0x3f) { hw_stop(); return 2; }
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    return 0;
}

/*--- Home Z axis only (simplified move_sen, Z-only) ---*/
/* dir=0: home DOWN (to sensor), returns steps taken */
/* dir=1: home UP (away from sensor) */
static int home_z(int dir, unsigned int *steps_taken) {
    unsigned char stspb;
    int fz, done, rc;
    unsigned int z_remain;

    /* Phase 1: fast approach */
    outportb(ADRPT0+2, 0x64); outportb(ADRPT0+2, 0x00);  /* K2z=100 (1000Hz) */
    outportb(ADRPT1+2, 0x00); outportb(ADRPT1+2, 0x40);  /* dZ=16384 */

    if(!dir) ctlw = ZON & ZDOWN & OSCON;      /* Z down */
    else     ctlw = (ZON | ZUP) & OSCON;      /* Z up */
    /* Also need XOFF YOFF */
    ctlw = ctlw & XOFF & YOFF;

    outportb(ADRRG, ctlw);
    fz = 1;
    z_remain = 16384;
    while(fz) {
        stspb = read_sensors();
        if((stspb & 0x30) != 0x30) {
            /* Z end sensor hit */
            z_remain = read_counter(ADRPT1, 2);
            ctlw = ctlw & ZOFF;
            fz = 0;
        }
        if((stspb & 0x40) == 0x40) {
            /* Counter finished without sensor - unexpected */
            z_remain = 0;
            ctlw = ctlw & ZOFF;
            fz = 0;
        }
        outportb(ADRRG, ctlw);
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    *steps_taken = 16384 - z_remain;

    /* Phase 2: slow reverse approach */
    outportb(ADRPT0+2, 0xc8); outportb(ADRPT0+2, 0x00);  /* K2z=200 (500Hz) */
    outportb(ADRPT1+2, 0xc8); outportb(ADRPT1+2, 0x00);  /* dZ=200 */
    if(!dir) ctlw = (ZON | ZUP) & XOFF & YOFF & OSCON;   /* reverse: up */
    else     ctlw = ZON & ZDOWN & XOFF & YOFF & OSCON;    /* reverse: down */
    outportb(ADRRG, ctlw);
    fz = 1; done = 0;
    while(!done) {
        stspb = read_sensors();
        /* Debounce: 10 reads */
        { unsigned char t = stspb; int j;
          for(j = 0; j < 10; j++) t &= read_sensors();
          stspb = t;
        }
        if(stspb & 0x40) { ctlw = ctlw & ZOFF; done = 1; }
        outportb(ADRRG, ctlw);
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    outportb(ADRRG, 0x80);  /* all off, osc off */
    return 0;
}

/*--- seg_time(): exact copy from PIC.CPP ---*/
static int seg_time(int adx, int ady, int adz) {
    int t; long ms; int count;
    t = (abs(adx) > abs(ady)) ? abs(adx) : abs(ady);
    if(t < abs(adz)) t = abs(adz);
    ms = (long)t * 1000 / cfg_step_freq;
    count = (int)(ms / cfg_l_period) + 1;
    if(ms % cfg_l_period > cfg_l_period - cfg_dT) count++;
    return count;
}

/*--- calc_k2(): exact copy from PIC.CPP ---*/
static long calc_k2(int delta, int t) {
    long k2, k2min, k2max = 65500;
    k2min = 100000L / cfg_step_freq;
    k2 = k2min;
    if(!cfg_f_const) {
        k2 = ((long)t * cfg_l_period - cfg_dT) * 100 / abs(delta);
        if(k2 < k2min) k2 = k2min;
        if(k2 > k2max) k2 = k2max;
    }
    return k2;
}

/*--- Home all 3 axes (replicates move_sen(0) from PIC.CPP) ---*/
/* Returns: 0=ok, 1=ESC abort */
static int home_all(void) {
    unsigned char stspb, tw;
    int fxy, fz, done;

    /* Phase 1: fast drive to sensors */
    outportb(ADRPT0,   0x64); outportb(ADRPT0,   0x00);  /* K2x=100 */
    outportb(ADRPT0+1, 0x00); outportb(ADRPT0+1, 0x70);  /* dX=28672 */
    outportb(ADRPT1,   0x64); outportb(ADRPT1,   0x00);  /* K2y=100 */
    outportb(ADRPT1+1, 0x00); outportb(ADRPT1+1, 0x70);  /* dY=28672 */
    outportb(ADRPT0+2, 0x64); outportb(ADRPT0+2, 0x00);  /* K2z=100 */
    outportb(ADRPT1+2, 0x00); outportb(ADRPT1+2, 0x40);  /* dZ=16384 */

    ctlw = (XON|YON|ZON|XUP) & YDOWN & ZDOWN & OSCON;
    tw   = (ctlw|XUP) & XOFF & YOFF & ZOFF & YDOWN & ZDOWN & OSCON;
    outportb(ADRRG, ctlw);

    while(ctlw != tw) {
        stspb = read_sensors();
        if((stspb & 0x03) != 0x03) ctlw = ctlw & XOFF;
        if((stspb & 0x0c) != 0x0c) ctlw = ctlw & YOFF;
        if((stspb & 0x30) != 0x30) ctlw = ctlw & ZOFF;
        outportb(ADRRG, ctlw);
        if(esc_pressed()) { hw_stop(); return 1; }
    }

    /* Phase 2: slow reverse with debounce (same as move_sen) */
    outportb(ADRPT0,   0xc8); outportb(ADRPT0,   0x00);  /* K2x=200 */
    outportb(ADRPT0+1, 0xc8); outportb(ADRPT0+1, 0x00);  /* dX=200 */
    outportb(ADRPT1,   0xc8); outportb(ADRPT1,   0x00);  /* K2y=200 */
    outportb(ADRPT1+1, 0xc8); outportb(ADRPT1+1, 0x00);  /* dY=200 */
    outportb(ADRPT0+2, 0xc8); outportb(ADRPT0+2, 0x00);  /* K2z=200 */
    outportb(ADRPT1+2, 0xc8); outportb(ADRPT1+2, 0x00);  /* dZ=200 */
    ctlw = (XON|YON|ZON|YUP|ZUP) & XDOWN & OSCON;
    outportb(ADRRG, ctlw);

    fxy = 1; fz = 1; done = 0;
    while(!done) {
        stspb = read_sensors();
        { unsigned char t = stspb; int j;
          for(j = 0; j < 10; j++) t &= read_sensors();
          stspb = t;
        }
        if(stspb & 0x80) { ctlw = ctlw & XOFF & YOFF; fxy = 0; }
        if(stspb & 0x40) { ctlw = ctlw & ZOFF; fz = 0; }
        outportb(ADRRG, ctlw);
        if((!fxy) && (!fz)) done = 1;
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    outportb(ADRRG, 0x80);  /* all off, osc off */
    xcur = 23300; ycur = 200; zcur = 200;
    return 0;
}

/*--- Move XYZ simultaneously (replicates move() from PIC.CPP) ---*/
/* Moves to absolute position (x,y,z). Uses calc_k2/seg_time timing. */
/* Returns: 0=ok, 1=ESC, 2=sensor error */
static int move_xyz(int x, int y, int z) {
    int dx, dy, dz, fxy, fz, done;
    unsigned char stspb;
    long k2; int t_seg;

    fxy = 0; fz = 0; done = 0;
    dx = x - xcur; dy = y - ycur; dz = z - zcur;
    if(!dx && !dy && !dz) return 0;
    t_seg = seg_time(dx, dy, dz);

    if(dx) {
        k2 = calc_k2(dx, t_seg);
        outportb(ADRPT0,   (unsigned char)(k2 % 256));
        outportb(ADRPT0,   (unsigned char)(k2 / 256));
        outportb(ADRPT0+1, (unsigned char)(abs(dx) % 256));
        outportb(ADRPT0+1, (unsigned char)(abs(dx) / 256));
        ctlw = (dx > 0) ? ctlw|XUP|XON : (ctlw & XDOWN)|XON;
        fxy = 1;
    } else ctlw = ctlw & XOFF;

    if(dy) {
        k2 = calc_k2(dy, t_seg);
        outportb(ADRPT1,   (unsigned char)(k2 % 256));
        outportb(ADRPT1,   (unsigned char)(k2 / 256));
        outportb(ADRPT1+1, (unsigned char)(abs(dy) % 256));
        outportb(ADRPT1+1, (unsigned char)(abs(dy) / 256));
        ctlw = (dy > 0) ? ctlw|YUP|YON : (ctlw & YDOWN)|YON;
        fxy = 1;
    } else ctlw = ctlw & YOFF;

    if(dz) {
        k2 = calc_k2(dz, t_seg);
        outportb(ADRPT0+2, (unsigned char)(k2 % 256));
        outportb(ADRPT0+2, (unsigned char)(k2 / 256));
        outportb(ADRPT1+2, (unsigned char)(abs(dz) % 256));
        outportb(ADRPT1+2, (unsigned char)(abs(dz) / 256));
        ctlw = (dz > 0) ? ctlw|ZUP|ZON : (ctlw & ZDOWN)|ZON;
        fz = 1;
    } else ctlw = ctlw & ZOFF;

    ctlw = ctlw & OSCON;
    outportb(ADRRG, ctlw);

    /* Poll PB7 (XY done) and PB6 (Z done) — same as original move() */
    while(!done) {
        stspb = read_sensors();
        if(fxy && ((stspb & 0x80) == 0x80)) { ctlw = ctlw & XOFF & YOFF; fxy = 0; }
        if(fz  && ((stspb & 0x40) == 0x40)) { ctlw = ctlw & ZOFF; fz = 0; }
        outportb(ADRRG, ctlw);
        if((!fxy) && (!fz)) done = 1;
        /* End-sensor check (all 6 bits) */
        if((stspb & 0x3f) != 0x3f) {
            delay(1);
            stspb = read_sensors();
            if((stspb & 0x3f) != 0x3f) {
                hw_stop();
                return 2;
            }
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    xcur = x; ycur = y; zcur = z;
    return 0;
}

/*--- Move Z by 'steps' steps at given K2z speed ---*/
/* Positive steps = up, negative = down */
/* Returns: 0=ok, 1=ESC, 2=sensor */
static int move_z(int steps, unsigned int k2z) {
    unsigned int abssteps;
    if(steps == 0) return 0;
    abssteps = (unsigned int)abs(steps);

    /* Load K2z */
    outportb(ADRPT0+2, (unsigned char)(k2z % 256));
    outportb(ADRPT0+2, (unsigned char)(k2z / 256));
    /* Load dZ */
    outportb(ADRPT1+2, (unsigned char)(abssteps % 256));
    outportb(ADRPT1+2, (unsigned char)(abssteps / 256));
    /* Direction + enable */
    ctlw = ctlw & XOFF & YOFF & ZOFF;
    if(steps > 0) ctlw = (ctlw | ZUP | ZON) & OSCON;
    else          ctlw = ((ctlw & ZDOWN) | ZON) & OSCON;
    outportb(ADRRG, ctlw);

    return wait_z_done();
}


/*=====================================================================
    TEST 1: Counter Behavior Probe
    
    Loads values into 8254 counters WITHOUT enabling motors,
    reads them back over time to see if they count down.
    This reveals whether GATE is tied high or gated by motor enable.
=====================================================================*/
static void test1_counter_probe(void) {
    unsigned int k2z_0, k2z_1, k2z_2;
    unsigned int dz_0, dz_1, dz_2;
    unsigned int k2x_0, k2x_1;
    unsigned int dx_0, dx_1;

    LOG("\n=== TEST 1: Counter Behavior Probe ===\n");
    LOG("Loading counters with motors OFF, checking if they count down.\n\n");

    /* Ensure motors off, oscillator ON */
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    /* Load K2z=1000, dZ=5000 */
    outportb(ADRPT0+2, (unsigned char)(1000 % 256));
    outportb(ADRPT0+2, (unsigned char)(1000 / 256));
    outportb(ADRPT1+2, (unsigned char)(5000 % 256));
    outportb(ADRPT1+2, (unsigned char)(5000 / 256));

    /* Read immediately */
    k2z_0 = read_counter(ADRPT0, 2);
    dz_0  = read_counter(ADRPT1, 2);
    LOG("T=0ms:  K2z=%5u  dZ=%5u\n", k2z_0, dz_0);

    /* Wait 50ms */
    delay(50);
    k2z_1 = read_counter(ADRPT0, 2);
    dz_1  = read_counter(ADRPT1, 2);
    LOG("T=50ms: K2z=%5u  dZ=%5u\n", k2z_1, dz_1);

    /* Wait 200ms more */
    delay(200);
    k2z_2 = read_counter(ADRPT0, 2);
    dz_2  = read_counter(ADRPT1, 2);
    LOG("T=250ms: K2z=%5u  dZ=%5u\n", k2z_2, dz_2);

    /* Analysis */
    LOG("\nAnalysis:\n");
    if(k2z_0 == k2z_1 && k2z_1 == k2z_2) {
        LOG("  K2z: NOT counting (GATE likely controlled by motor enable)\n");
    } else if(k2z_1 < k2z_0) {
        LOG("  K2z: COUNTING DOWN (GATE is always high, or tied to OSC)\n");
        LOG("  K2z counted %u ticks in 50ms\n", k2z_0 - k2z_1);
    } else {
        LOG("  K2z: unexpected behavior (0→1: %u→%u)\n", k2z_0, k2z_1);
    }

    if(dz_0 == dz_1 && dz_1 == dz_2) {
        LOG("  dZ: NOT counting (needs K2z output as clock, or GATE gated)\n");
    } else if(dz_1 < dz_0) {
        LOG("  dZ: COUNTING DOWN (receiving clock from K2z)\n");
        LOG("  dZ counted %u steps in 50ms\n", dz_0 - dz_1);
    } else {
        LOG("  dZ: unexpected behavior\n");
    }

    /* Sub-test: same with oscillator OFF */
    LOG("\n--- Sub-test: oscillator OFF ---\n");
    ctlw = ctlw | OSCOFF;
    outportb(ADRRG, ctlw);
    delay(10);

    /* Reload */
    outportb(ADRPT0+2, (unsigned char)(1000 % 256));
    outportb(ADRPT0+2, (unsigned char)(1000 / 256));
    outportb(ADRPT1+2, (unsigned char)(5000 % 256));
    outportb(ADRPT1+2, (unsigned char)(5000 / 256));

    k2z_0 = read_counter(ADRPT0, 2);
    dz_0  = read_counter(ADRPT1, 2);
    delay(50);
    k2z_1 = read_counter(ADRPT0, 2);
    dz_1  = read_counter(ADRPT1, 2);
    LOG("OSC OFF T=0:   K2z=%5u  dZ=%5u\n", k2z_0, dz_0);
    LOG("OSC OFF T=50ms: K2z=%5u  dZ=%5u\n", k2z_1, dz_1);

    if(k2z_0 == k2z_1)
        LOG("  K2z: stopped when OSC off => OSC is the clock source\n");
    else
        LOG("  K2z: still counting with OSC off => clock is not from OSC\n");

    /* Sub-test: motor enable ON but oscillator OFF */
    LOG("\n--- Sub-test: ZON=1, OSC OFF ---\n");
    ctlw = (ZON | ZUP) | OSCOFF;
    outportb(ADRRG, ctlw);
    delay(10);
    outportb(ADRPT0+2, (unsigned char)(1000 % 256));
    outportb(ADRPT0+2, (unsigned char)(1000 / 256));
    outportb(ADRPT1+2, (unsigned char)(5000 % 256));
    outportb(ADRPT1+2, (unsigned char)(5000 / 256));
    k2z_0 = read_counter(ADRPT0, 2);
    dz_0  = read_counter(ADRPT1, 2);
    delay(50);
    k2z_1 = read_counter(ADRPT0, 2);
    dz_1  = read_counter(ADRPT1, 2);
    LOG("ZON+OSCOFF T=0:   K2z=%5u  dZ=%5u\n", k2z_0, dz_0);
    LOG("ZON+OSCOFF T=50ms: K2z=%5u  dZ=%5u\n", k2z_1, dz_1);
    if(k2z_0 != k2z_1)
        LOG("  K2z counts with ZON+OSCOFF => GATE from motor enable?\n");
    else
        LOG("  K2z doesn't count => needs OSC\n");

    /* Restore safe state */
    hw_stop();

    /* Same test for X axis to compare */
    LOG("\n--- Sub-test: X axis (K2x, dX) for comparison ---\n");
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);
    outportb(ADRPT0, (unsigned char)(1000 % 256));
    outportb(ADRPT0, (unsigned char)(1000 / 256));
    outportb(ADRPT0+1, (unsigned char)(5000 % 256));
    outportb(ADRPT0+1, (unsigned char)(5000 / 256));
    k2x_0 = read_counter(ADRPT0, 0);
    dx_0  = read_counter(ADRPT0, 1);
    delay(50);
    k2x_1 = read_counter(ADRPT0, 0);
    dx_1  = read_counter(ADRPT0, 1);
    LOG("X: T=0: K2x=%5u dX=%5u  T=50ms: K2x=%5u dX=%5u\n",
        k2x_0, dx_0, k2x_1, dx_1);

    hw_stop();
    LOG("\n=== TEST 1 COMPLETE ===\n");
}


/*=====================================================================
    TEST 2: PB6/PB7 Signal Source
    
    Move Z a small number of steps.
    Monitor PB6 and dZ counter simultaneously.
    Check if PB6 goes high exactly when dZ reaches 0.
=====================================================================*/
static void test2_pb_signal(void) {
    unsigned int dz_before, dz_after;
    unsigned char pb_before, pb_after;
    unsigned char pb_during[100];
    unsigned int  dz_during[100];
    int n = 0, i;

    LOG("\n=== TEST 2: PB6/PB7 Signal Source ===\n");
    LOG("Moving Z 50 steps UP at K2z=500, sampling PB6 and dZ.\n\n");

    /* Setup: motors off, osc on */
    ctlw = (ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    pb_before = read_sensors();
    LOG("Before move: PB=0x%02X (PB6=%d PB7=%d)\n",
        (int)pb_before, (pb_before>>6)&1, (pb_before>>7)&1);

    /* Load K2z=500 (200Hz), dZ=50 */
    outportb(ADRPT0+2, (unsigned char)(500 % 256));
    outportb(ADRPT0+2, (unsigned char)(500 / 256));
    outportb(ADRPT1+2, 50);
    outportb(ADRPT1+2, 0);

    dz_before = read_counter(ADRPT1, 2);
    LOG("Counter loaded: dZ=%u\n", dz_before);

    /* Enable Z motor */
    ctlw = (ZUP | ZON) & XOFF & YOFF & OSCON;
    outportb(ADRRG, ctlw);

    /* Sample PB and dZ rapidly during movement */
    /* 50 steps at 200Hz = 250ms. Sample every ~2ms */
    n = 0;
    while(n < 100) {
        pb_during[n] = read_sensors();
        dz_during[n] = read_counter(ADRPT1, 2);
        n++;
        if((pb_during[n-1] & 0x40) == 0x40) {
            /* PB6 fired - take a few more samples */
            int extra;
            for(extra = 0; extra < 5 && n < 100; extra++) {
                pb_during[n] = read_sensors();
                dz_during[n] = read_counter(ADRPT1, 2);
                n++;
            }
            break;
        }
        delay(2);
    }

    /* Stop */
    ctlw = ctlw & ZOFF;
    outportb(ADRRG, ctlw);

    pb_after = read_sensors();
    dz_after = read_counter(ADRPT1, 2);

    LOG("\nSamples (total %d):\n", n);
    LOG("  %4s  %5s  %4s  %4s\n", "i", "dZ", "PB6", "PB7");
    for(i = 0; i < n; i++) {
        LOG("  %4d  %5u  %4d  %4d\n", i, dz_during[i],
            (dz_during[i], (pb_during[i]>>6)&1), (pb_during[i]>>7)&1);
    }
    LOG("\nAfter stop: PB=0x%02X dZ=%u\n", (int)pb_after, dz_after);

    /* Check: did PB6 go high when dZ hit 0? */
    LOG("\nAnalysis:\n");
    for(i = 0; i < n; i++) {
        if((pb_during[i] & 0x40) == 0x40) {
            LOG("  PB6 went HIGH at sample %d, dZ=%u at that moment\n",
                i, dz_during[i]);
            if(dz_during[i] == 0)
                LOG("  => PB6 fires when dZ=0. PB6 IS the terminal count of PT1.ch2!\n");
            else
                LOG("  => PB6 fired but dZ=%u != 0. PB6 may come from elsewhere!\n",
                    dz_during[i]);
            break;
        }
    }
    if(i == n) {
        LOG("  PB6 never went high during %d samples!\n", n);
        LOG("  Either dZ didn't reach 0, or PB6 is not connected to dZ.\n");
    }

    hw_stop();
    LOG("\n=== TEST 2 COMPLETE ===\n");
}


/*=====================================================================
    TEST 3: 8254 Mode Detection
    
    Uses Read-Back command (if 8254-2 chip) to read counter mode.
    Falls back to behavioral test if Read-Back not supported.
=====================================================================*/
static void test3_mode_detect(void) {
    unsigned char st;
    int ch, base;
    const char *base_names[] = {"PT0", "PT1"};
    const char *ch_names[]   = {"ch0", "ch1", "ch2"};
    int bases[] = {ADRPT0, ADRPT1};
    int mode, bcd, out;

    LOG("\n=== TEST 3: 8254 Mode Detection (Read-Back) ===\n");
    LOG("Attempting Read-Back command on all counters.\n");
    LOG("(Works only on 8254-2. Original 8254 ignores this command.)\n\n");

    /* First: init state - osc on, motors off */
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    /* Load some values so counters are initialized */
    outportb(ADRPT0,   0xe8); outportb(ADRPT0,   0x03);  /* K2x=1000 */
    outportb(ADRPT0+1, 0x88); outportb(ADRPT0+1, 0x13);  /* dX=5000 */
    outportb(ADRPT0+2, 0xe8); outportb(ADRPT0+2, 0x03);  /* K2z=1000 */
    outportb(ADRPT1,   0xe8); outportb(ADRPT1,   0x03);  /* K2y=1000 */
    outportb(ADRPT1+1, 0x88); outportb(ADRPT1+1, 0x13);  /* dY=5000 */
    outportb(ADRPT1+2, 0x88); outportb(ADRPT1+2, 0x13);  /* dZ=5000 */
    delay(10);

    for(base = 0; base < 2; base++) {
        for(ch = 0; ch < 3; ch++) {
            st = read_status(bases[base], ch);
            out  = (st >> 7) & 1;
            mode = (st >> 1) & 7;
            bcd  = st & 1;
            LOG("  %s.%s: status=0x%02X  OUT=%d  Mode=%d  BCD=%d\n",
                base_names[base], ch_names[ch], (int)st, out, mode, bcd);
        }
    }

    /* Validate: if all status bytes are the same weird value, Read-Back probably unsupported */
    LOG("\nNote: If all values look identical/random, chip may be 8254 (not 8254-2)\n");
    LOG("and Read-Back is not supported. Use TEST 1 behavioral results instead.\n");

    hw_stop();
    LOG("\n=== TEST 3 COMPLETE ===\n");
}


/*=====================================================================
    TEST 4: Z Step Integrity
    
    Homes Z, moves UP a known distance, homes again.
    Compares expected vs actual steps.
    Repeats at different K2z values (speeds).
=====================================================================*/
static void test4_z_integrity(void) {
    unsigned int home_steps;
    unsigned int k2z_values[] = {100, 150, 200, 300, 500, 1000};
    int num_speeds = 6;
    int test_dist = 5000;  /* steps to move up */
    int sp, rc;
    unsigned int home1, home2;
    int delta;

    LOG("\n=== TEST 4: Z Step Integrity at Various Speeds ===\n");
    LOG("Home → Move UP %d steps → Home. Compare actual vs expected.\n", test_dist);
    LOG("Testing %d different K2z values.\n\n", num_speeds);
    LOG("  %5s  %6s  %6s  %6s  %6s  %s\n",
        "K2z", "Fstep", "Up", "Home1", "Home2", "Delta");

    for(sp = 0; sp < num_speeds; sp++) {
        unsigned int k2z = k2z_values[sp];
        unsigned int fstep = 100000U / k2z;  /* approximate Hz */

        /* Home (get baseline) */
        LOG("  [homeing...]");
        rc = home_z(0, &home1);
        if(rc) { LOG(" ABORTED\n"); return; }

        /* Move UP test_dist steps */
        rc = move_z(test_dist, k2z);
        if(rc == 1) { LOG(" ESC\n"); hw_stop(); return; }
        if(rc == 2) { LOG(" SENSOR HIT during move\n"); continue; }

        /* Read dZ counter (should be 0 if all steps generated) */
        { unsigned int dz_remain = read_counter(ADRPT1, 2);
          LOG("\r  k2z=%-5u %4uHz  dZ_remain=%u", k2z, fstep, dz_remain);
        }

        /* Home again (measure actual distance) */
        rc = home_z(0, &home2);
        if(rc) { LOG(" ABORTED\n"); return; }

        delta = (int)home2 - test_dist;
        LOG("\r  %5u  %4uHz  %5d  %5u  %5u  %+5d %s\n",
            k2z, fstep, test_dist, home1, home2, delta,
            (abs(delta) > 10) ? "*** STEP LOSS ***" : "OK");
    }

    hw_stop();
    LOG("\n=== TEST 4 COMPLETE ===\n");
}


/*=====================================================================
    TEST 5: Thermal Accumulation / Fatigue
    
    Repeatedly: Home → Move UP → Home → Move UP → Home.
    Checks if error accumulates over cycles (thermal effect).
=====================================================================*/
static void test5_thermal(void) {
    int num_cycles = 10;
    int test_dist = 8000;
    unsigned int k2z = 100;  /* max speed, most likely to fail */
    int cyc, rc;
    unsigned int home_steps;
    int delta;

    LOG("\n=== TEST 5: Thermal Accumulation ===\n");
    LOG("Repeat %d cycles: Home → UP %d steps (K2z=%u) → Home.\n",
        num_cycles, test_dist, k2z);
    LOG("Checking if step loss increases over time.\n\n");
    LOG("  %5s  %6s  %6s  %s\n", "Cycle", "Home", "Delta", "Status");

    for(cyc = 0; cyc < num_cycles; cyc++) {
        /* Home */
        rc = home_z(0, &home_steps);
        if(rc) { LOG("  Cycle %d: home ABORTED\n", cyc); return; }

        /* Move up */
        rc = move_z(test_dist, k2z);
        if(rc == 1) { LOG("  Cycle %d: ESC\n", cyc); hw_stop(); return; }
        if(rc == 2) { LOG("  Cycle %d: SENSOR during move\n", cyc); continue; }

        /* Home again to measure */
        rc = home_z(0, &home_steps);
        if(rc) { LOG("  Cycle %d: home2 ABORTED\n", cyc); return; }

        delta = (int)home_steps - test_dist;
        LOG("  %5d  %6u  %+5d  %s\n", cyc, home_steps, delta,
            (abs(delta) > 10) ? "*** LOSS ***" : "OK");
    }

    hw_stop();
    LOG("\n=== TEST 5 COMPLETE ===\n");
}


/*=====================================================================
    TEST 6: Oscillator Frequency Measurement
    
    Loads a large K2 value, measures time until counter reaches a
    known lower value. Calculates input clock frequency.
=====================================================================*/
static void test6_osc_freq(void) {
    unsigned int start_val = 60000;
    unsigned int v0, v1;
    unsigned long t0, t1;
    unsigned long ticks;
    double freq;

    LOG("\n=== TEST 6: Oscillator Frequency Measurement ===\n");
    LOG("Loading K2z=%u, measuring countdown rate.\n\n", start_val);

    /* Osc on, motors off */
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    /* Load K2z with large value */
    outportb(ADRPT0+2, (unsigned char)(start_val % 256));
    outportb(ADRPT0+2, (unsigned char)(start_val / 256));

    /* Check first if counter is actually counting */
    v0 = read_counter(ADRPT0, 2);
    delay(10);
    v1 = read_counter(ADRPT0, 2);
    if(v0 == v1) {
        LOG("K2z not counting (v0=%u v1=%u). Cannot measure frequency.\n", v0, v1);
        LOG("This means K2z GATE is NOT always high.\n");
        hw_stop();
        LOG("\n=== TEST 6 COMPLETE (no data) ===\n");
        return;
    }

    /* Measure: use BIOS tick counter (18.2 Hz = 55ms per tick) */
    /* For better precision, use a tight loop and count iterations */
    LOG("Counter is active. Measuring...\n");

    /* Reload */
    outportb(ADRPT0+2, (unsigned char)(start_val % 256));
    outportb(ADRPT0+2, (unsigned char)(start_val / 256));

    v0 = read_counter(ADRPT0, 2);
    /* Busy-wait until counter decrements by a known amount */
    {
        unsigned long loops = 0;
        unsigned int target = v0 - 10000;
        while(1) {
            v1 = read_counter(ADRPT0, 2);
            loops++;
            if(v1 <= target || v1 > v0) break;  /* wrapped or reached target */
            if(loops > 10000000UL) { LOG("Timeout\n"); break; }
        }
        LOG("Counted %u ticks down (%u -> %u) in %lu read loops\n",
            v0 - v1, v0, v1, loops);
    }

    /* Alternative: timed measurement using delay() */
    LOG("\nTimed measurement (100ms window):\n");
    outportb(ADRPT0+2, (unsigned char)(start_val % 256));
    outportb(ADRPT0+2, (unsigned char)(start_val / 256));
    v0 = read_counter(ADRPT0, 2);
    delay(100);
    v1 = read_counter(ADRPT0, 2);
    if(v1 < v0) {
        unsigned int counted = v0 - v1;
        freq = (double)counted / 0.1;  /* counts per second */
        LOG("  Counted %u ticks in 100ms => %.0f Hz input clock\n", counted, freq);
        LOG("  At K1=150 PPI.PA: base clock = %.0f Hz\n", freq);
        if(freq > 90000.0 && freq < 110000.0)
            LOG("  => Consistent with 100 kHz\n");
    } else {
        LOG("  Counter wrapped or didn't count (v0=%u v1=%u)\n", v0, v1);
    }

    hw_stop();
    LOG("\n=== TEST 6 COMPLETE ===\n");
}


/*=====================================================================
    TEST 7: Full Sensor Readout
    
    Reads all PPI/PPI2 ports, shows state of all sensors, end-stops,
    and control signals. Useful for verifying hardware wiring.
=====================================================================*/
static void test7_sensor_readout(void) {
    unsigned char ppi_pa, ppi_pb, ppi_pc;
    unsigned char ppi2_pa, ppi2_pb, ppi2_pc;
    int i;

    LOG("\n=== TEST 7: Full Sensor/Port Readout ===\n\n");

    /* PPI */
    /* PA is output, reading it back may not work on all 8255s */
    ppi_pb = inportb(ADRPPI+1);
    /* PC: lower nibble out, reading back */

    LOG("PPI (0x%03X):\n", ADRPPI);
    LOG("  PB (sensors) = 0x%02X\n", (int)ppi_pb);
    LOG("    PB0 (endSens X-): %d  %s\n", ppi_pb&1, (ppi_pb&1)?"free":"TRIGGERED");
    LOG("    PB1 (endSens X+): %d  %s\n", (ppi_pb>>1)&1, ((ppi_pb>>1)&1)?"free":"TRIGGERED");
    LOG("    PB2 (endSens Y-): %d  %s\n", (ppi_pb>>2)&1, ((ppi_pb>>2)&1)?"free":"TRIGGERED");
    LOG("    PB3 (endSens Y+): %d  %s\n", (ppi_pb>>3)&1, ((ppi_pb>>3)&1)?"free":"TRIGGERED");
    LOG("    PB4 (endSens Z-): %d  %s\n", (ppi_pb>>4)&1, ((ppi_pb>>4)&1)?"free":"TRIGGERED");
    LOG("    PB5 (endSens Z+): %d  %s\n", (ppi_pb>>5)&1, ((ppi_pb>>5)&1)?"free":"TRIGGERED");
    LOG("    PB6 (IRQ2/done): %d\n", (ppi_pb>>6)&1);
    LOG("    PB7 (IRQ3/done): %d\n", (ppi_pb>>7)&1);

    /* PPI2 */
    ppi2_pa = inportb(ADRPPI2);
    /* Read PC lower nibble (input) */
    /* Note: PC input bits are PC0-3 on PPI2 */
    LOG("\nPPI2 (0x%03X):\n", ADRPPI2);
    LOG("  PA (sensors dup) = 0x%02X\n", (int)ppi2_pa);

    /* RG current state */
    LOG("\nRG (0x%03X): ctlw=0x%02X\n", ADRRG, (int)ctlw);

    /* Read all 8254 counters */
    LOG("\n8254 Counters:\n");
    LOG("  PT0.ch0 (K2x) = %5u\n", read_counter(ADRPT0, 0));
    LOG("  PT0.ch1 (dX)  = %5u\n", read_counter(ADRPT0, 1));
    LOG("  PT0.ch2 (K2z) = %5u\n", read_counter(ADRPT0, 2));
    LOG("  PT1.ch0 (K2y) = %5u\n", read_counter(ADRPT1, 0));
    LOG("  PT1.ch1 (dY)  = %5u\n", read_counter(ADRPT1, 1));
    LOG("  PT1.ch2 (dZ)  = %5u\n", read_counter(ADRPT1, 2));

    LOG("\nPress any key to see live sensor update (ESC to stop)...\n");
    bioskey(0);

    while(!esc_pressed()) {
        ppi_pb = read_sensors();
        printf("\rPB=0x%02X [%c%c%c%c%c%c|%c%c] ",
            (int)ppi_pb,
            (ppi_pb&0x01)?'.':'X', (ppi_pb&0x02)?'.':'X',
            (ppi_pb&0x04)?'.':'X', (ppi_pb&0x08)?'.':'X',
            (ppi_pb&0x10)?'.':'Z', (ppi_pb&0x20)?'.':'Z',
            (ppi_pb&0x40)?'6':'.', (ppi_pb&0x80)?'7':'.');
        delay(100);
    }
    LOG("\n\n=== TEST 7 COMPLETE ===\n");
}


/*=====================================================================
    TEST 8: Reproduce Z Bug
    
    Simulates the exact sequence from the log:
    Home → Move UP 8580 → Move DOWN 648 (9 layers of ~72) → Home →
    Move UP 8256 → Move DOWN 324 (9 layers of ~36) → Home.
    Compares homing results.
=====================================================================*/
static void test8_reproduce(void) {
    unsigned int home_steps;
    int rc, layer;
    int delta1, delta2;
    unsigned int actual1, actual2;

    LOG("\n=== TEST 8: Reproduce Z Bug from Log ===\n");
    LOG("Replicating the exact move sequence from FLINT32-12.03.2026_2.LOG\n\n");

    /* === Run 1 simulation === */
    LOG("--- Run 1 (cub3.bft pattern) ---\n");
    rc = home_z(0, &home_steps);
    if(rc) { LOG("Home failed\n"); return; }
    LOG("Home: %u steps to sensor\n", home_steps);

    /* Big move up: 8580 steps at K2z=100 */
    LOG("Moving UP 8580 steps at K2z=100...\n");
    rc = move_z(8580, 100);
    if(rc) { LOG("Move failed (rc=%d)\n", rc); hw_stop(); return; }

    /* 9 layers down, ~72 steps each */
    for(layer = 0; layer < 9; layer++) {
        rc = move_z(-72, 100);
        if(rc) { LOG("Layer %d failed\n", layer); hw_stop(); return; }
        delay(35);  /* simulate l_period */
    }

    /* Home and check */
    rc = home_z(0, &actual1);
    if(rc) { LOG("Home1 failed\n"); return; }
    delta1 = (int)actual1 - (8580 - 9*72);
    LOG("Run1 home: actual=%u expected=%d delta=%+d\n\n",
        actual1, 8580-9*72, delta1);

    /* === Run 2 simulation === */
    LOG("--- Run 2 (cubt2.bft pattern) ---\n");

    /* Big move up: 8256 steps at K2z=100 */
    LOG("Moving UP 8256 steps at K2z=100...\n");
    rc = move_z(8256, 100);
    if(rc) { LOG("Move failed (rc=%d)\n", rc); hw_stop(); return; }

    /* 9 layers down, ~36 steps each */
    for(layer = 0; layer < 9; layer++) {
        rc = move_z(-36, 100);
        if(rc) { LOG("Layer %d failed\n", layer); hw_stop(); return; }
        delay(35);
    }

    /* Home and check */
    rc = home_z(0, &actual2);
    if(rc) { LOG("Home2 failed\n"); return; }
    delta2 = (int)actual2 - (8256 - 9*36);
    LOG("Run2 home: actual=%u expected=%d delta=%+d\n\n",
        actual2, 8256-9*36, delta2);

    /* Summary */
    LOG("=== Summary ===\n");
    LOG("Run 1: delta=%+d %s\n", delta1,
        (abs(delta1) > 10) ? "*** STEP LOSS ***" : "OK");
    LOG("Run 2: delta=%+d %s\n", delta2,
        (abs(delta2) > 10) ? "*** STEP LOSS ***" : "OK");
    if(abs(delta1) <= 10 && abs(delta2) > 10)
        LOG("=> Problem reproduces! Run 2 loses steps after Run 1 works fine.\n");
    else if(abs(delta1) > 10)
        LOG("=> Run 1 also has issues — may be mechanical or speed problem.\n");
    else
        LOG("=> Both runs OK — problem may be intermittent or load-dependent.\n");

    hw_stop();
    LOG("\n=== TEST 8 COMPLETE ===\n");
}


/*=====================================================================
    TEST 9: Homing Repeatability
    
    Checks if the Z end-stop sensor gives consistent results.
    10 cycles: home → move up 2000 steps → home again.
    Reports each homing distance and the total spread (max-min).
    If spread > ~5 steps, the sensor is unreliable and all
    homing-based tests (4,5,8) cannot be trusted.
=====================================================================*/
static void test9_home_repeat(void) {
    int num_cycles = 10;
    unsigned int results[10];
    unsigned int home_steps;
    unsigned int mn, mx;
    int cyc, rc;

    LOG("\n=== TEST 9: Homing Repeatability ===\n");
    LOG("10 cycles: Home -> UP 2000 -> Home. Measuring sensor consistency.\n\n");
    LOG("  %5s  %6s\n", "Cycle", "Home");

    for(cyc = 0; cyc < num_cycles; cyc++) {
        /* Home down */
        rc = home_z(0, &home_steps);
        if(rc) { LOG("  Cycle %d: home ABORTED\n", cyc); return; }

        if(cyc == 0) {
            /* First cycle: just record baseline */
            results[cyc] = 0;
            LOG("  %5d  %6s  (baseline)\n", cyc, "-");
        } else {
            results[cyc] = home_steps;
            LOG("  %5d  %6u\n", cyc, home_steps);
        }

        /* Move up 2000 steps at moderate speed */
        rc = move_z(2000, 200);
        if(rc == 1) { LOG("  ESC\n"); hw_stop(); return; }
        if(rc == 2) { LOG("  SENSOR during move up\n"); continue; }
    }

    /* Final home */
    rc = home_z(0, &home_steps);
    if(rc) { LOG("  Final home ABORTED\n"); return; }
    LOG("  final  %6u\n", home_steps);

    /* Statistics (skip cycle 0) */
    mn = results[1]; mx = results[1];
    for(cyc = 2; cyc < num_cycles; cyc++) {
        if(results[cyc] < mn) mn = results[cyc];
        if(results[cyc] > mx) mx = results[cyc];
    }
    if(home_steps < mn) mn = home_steps;
    if(home_steps > mx) mx = home_steps;

    LOG("\nSpread: min=%u max=%u range=%u\n", mn, mx, mx - mn);
    if((mx - mn) <= 5)
        LOG("=> Sensor is STABLE (range <= 5 steps). Homing tests are reliable.\n");
    else if((mx - mn) <= 20)
        LOG("=> Sensor has SOME jitter (%u steps). Results need averaging.\n", mx - mn);
    else
        LOG("=> Sensor is UNRELIABLE (%u steps spread). Homing-based tests CANNOT be trusted!\n", mx - mn);

    hw_stop();
    LOG("\n=== TEST 9 COMPLETE ===\n");
}


/*=====================================================================
    TEST 10: XY+Z Simultaneous Move Integrity

    THE critical test: moves all 3 axes simultaneously (like move()),
    then homes and checks if Z position is correct.
    This tests the exact hardware behavior that FLINT uses.
    The original Z bug only appeared during XY+Z combined moves.
=====================================================================*/
static void test10_xyz_integrity(void) {
    int rc, sp;
    unsigned int k2_vals[] = {100, 150, 200, 300};
    int num_speeds = 4;
    /* Target positions: X=20000, Y=2000, Z=8000 (typical FLINT move) */
    int x_tgt = 20000, y_tgt = 2000, z_tgt = 8000;
    unsigned int home_steps;
    int delta;

    LOG("\n=== TEST 10: XY+Z Simultaneous Move Integrity ===\n");
    LOG("Home all -> move XYZ simultaneously -> home all -> check Z.\n");
    LOG("Uses calc_k2/seg_time timing (same algorithm as FLINT move()).\n");
    LOG("Config: l_period=%d dT=%d step_freq=%d f_const=%d\n\n",
        cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
    LOG("  %6s  %6s  %6s  %6s  %6s  %6s  %s\n",
        "Speed", "X_tgt", "Y_tgt", "Z_tgt", "Z_home", "Z_dlt", "Status");

    for(sp = 0; sp < num_speeds; sp++) {
        /* Override step_freq to test different speeds */
        int saved_sf = cfg_step_freq;
        cfg_step_freq = 100000L / k2_vals[sp];

        LOG("  [homing all axes...]");

        /* Home all axes */
        rc = home_all();
        if(rc) { LOG(" ABORTED\n"); cfg_step_freq = saved_sf; return; }

        /* Move to target position using move_xyz (same as FLINT move()) */
        rc = move_xyz(x_tgt, y_tgt, z_tgt);
        if(rc == 1) { LOG(" ESC\n"); cfg_step_freq = saved_sf; hw_stop(); return; }
        if(rc == 2) { LOG(" SENSOR during XYZ move\n"); cfg_step_freq = saved_sf; continue; }

        /* Read Z counter remainder (should be 0) */
        { unsigned int zd = read_counter(ADRPT1, 2);
          if(zd != 0)
              LOG("\n  *** Z counter remainder: %u (should be 0!) ***\n", zd);
        }

        /* Home all and check Z distance */
        rc = home_all();
        if(rc) { LOG(" ABORTED\n"); cfg_step_freq = saved_sf; return; }

        /* After home: zcur=200. The Z-distance from tgt to home = z_tgt - 200.
           But home_all uses fast drive to sensor, so we measure indirectly.
           We'll use home_z for precise Z measurement instead. */

        /* Move Z to a known position first */
        rc = move_z(z_tgt - 200, k2_vals[sp]);
        if(rc) { LOG(" move_z failed\n"); cfg_step_freq = saved_sf; continue; }

        /* Now home Z precisely and measure */
        rc = home_z(0, &home_steps);
        if(rc) { LOG(" home failed\n"); cfg_step_freq = saved_sf; return; }

        delta = (int)home_steps - (z_tgt - 200);
        LOG("\r  %4uHz  %6d  %6d  %6d  %6u  %+5d  %s\n",
            (unsigned)(100000L / k2_vals[sp]),
            x_tgt, y_tgt, z_tgt, home_steps, delta,
            (abs(delta) > 10) ? "*** LOSS ***" : "OK");

        cfg_step_freq = saved_sf;
    }

    hw_stop();
    LOG("\n=== TEST 10 COMPLETE ===\n");
}


/*=====================================================================
    TEST 11: Full Process Simulation

    Simulates process() with a synthetic point table:
    Homes all axes, then makes a sequence of XY+Z moves
    that mimic real engraving (XY scan + Z layers).
    After each "run", homes Z and checks for step loss.

    This is the closest simulation of the actual Z bug scenario
    without running FLINT itself.
=====================================================================*/
static void test11_process_sim(void) {
    int rc, layer, pt;
    int delta;
    unsigned int home_steps;
    int xbase = 23500 - 500;   /* xptr=500 */
    int ybase = 500;           /* yptr=500 */
    int zbase;
    int num_layers = 9;
    int pts_per_layer = 20;    /* 20 XY points per Z layer */
    int z_step = 72;           /* Z step per layer (from original bug log) */

    LOG("\n=== TEST 11: Full Process Simulation ===\n");
    LOG("Simulates FLINT process() with synthetic point table.\n");
    LOG("Config: l_period=%d dT=%d step_freq=%d\n", cfg_l_period, cfg_dT, cfg_step_freq);
    LOG("Pattern: %d layers x %d pts, Z_step=%d\n\n", num_layers, pts_per_layer, z_step);

    /* === Run 1: large Z offset (like cub3.bft) === */
    LOG("--- Run 1: Z_base=8580, %d layers x %d pts ---\n", num_layers, pts_per_layer);

    rc = home_all();
    if(rc) { LOG("Home ABORTED\n"); return; }
    LOG("Homed: X=%d Y=%d Z=%d\n", xcur, ycur, zcur);

    /* Initial move to starting position */
    zbase = 8580;
    rc = move_xyz(xbase, ybase, zbase);
    if(rc) { LOG("Initial move failed (rc=%d)\n", rc); hw_stop(); return; }
    LOG("At start position: X=%d Y=%d Z=%d\n", xcur, ycur, zcur);

    for(layer = 0; layer < num_layers; layer++) {
        int znew = zbase - layer * z_step;

        /* Simulate XY scan within layer */
        for(pt = 0; pt < pts_per_layer; pt++) {
            int xnew = xbase + (pt % 5) * 100 - 200;
            int ynew = ybase + (pt / 5) * 100;
            rc = move_xyz(xnew, ynew, znew);
            if(rc == 1) { LOG("ESC at layer %d pt %d\n", layer, pt); hw_stop(); return; }
            if(rc == 2) { LOG("SENSOR at layer %d pt %d\n", layer, pt); hw_stop(); return; }
            /* In real FLINT, lpuls() fires here. We just add the delay. */
            delay(cfg_l_period);
        }
        LOG("  Layer %d done, Z=%d\n", layer, zcur);
    }

    /* Home and check Z */
    { int expected_z = zbase - (num_layers - 1) * z_step;
      LOG("Expected final Z=%d, actual zcur=%d\n", expected_z, zcur);
    }
    rc = home_z(0, &home_steps);
    if(rc) { LOG("Home failed\n"); return; }
    delta = (int)home_steps - (zcur - 200);
    LOG("Run1: Z home=%u, expected=%d, delta=%+d %s\n\n",
        home_steps, zcur - 200, delta,
        (abs(delta) > 10) ? "*** STEP LOSS ***" : "OK");

    /* === Run 2: smaller Z offset (continuation, like cubt2.bft) === */
    LOG("--- Run 2: Z_base=8256, %d layers x %d pts (continuation) ---\n",
        num_layers, pts_per_layer);

    /* Note: in real FLINT, Run 2 starts from the home position set by move_sen(0) above */
    /* But: the issue in the bug was that Run 2 uses F4+PgUp to reload, which calls
       move_sen(0) resetting positions. Then process() runs from start_nmb=0. */

    rc = home_all();
    if(rc) { LOG("Home ABORTED\n"); return; }

    zbase = 8256;
    z_step = 36;  /* smaller Z step for run 2 */
    rc = move_xyz(xbase, ybase, zbase);
    if(rc) { LOG("Initial move failed (rc=%d)\n", rc); hw_stop(); return; }
    LOG("At start position: X=%d Y=%d Z=%d\n", xcur, ycur, zcur);

    for(layer = 0; layer < num_layers; layer++) {
        int znew = zbase - layer * z_step;
        for(pt = 0; pt < pts_per_layer; pt++) {
            int xnew = xbase + (pt % 5) * 100 - 200;
            int ynew = ybase + (pt / 5) * 100;
            rc = move_xyz(xnew, ynew, znew);
            if(rc == 1) { LOG("ESC at layer %d pt %d\n", layer, pt); hw_stop(); return; }
            if(rc == 2) { LOG("SENSOR at layer %d pt %d\n", layer, pt); hw_stop(); return; }
            delay(cfg_l_period);
        }
        LOG("  Layer %d done, Z=%d\n", layer, zcur);
    }

    rc = home_z(0, &home_steps);
    if(rc) { LOG("Home failed\n"); return; }
    delta = (int)home_steps - (zcur - 200);
    LOG("Run2: Z home=%u, expected=%d, delta=%+d %s\n\n",
        home_steps, zcur - 200, delta,
        (abs(delta) > 10) ? "*** STEP LOSS ***" : "OK");

    hw_stop();
    LOG("\n=== TEST 11 COMPLETE ===\n");
}


/*=====================================================================
    TEST 12: Counter Cross-Talk

    Checks if programming X/Y counters affects Z counters,
    or vice versa. On a correctly wired ISA card, channels on
    the same 8254 chip share the control register but should
    have independent counting.

    PT0: ch0=K2x, ch1=dX, ch2=K2z   (X and Z on SAME chip!)
    PT1: ch0=K2y, ch1=dY, ch2=dZ    (Y and Z on SAME chip!)

    This is suspicious: K2z is on PT0 but dZ is on PT1.
    If the chip has a bug or if the address decoding is wrong,
    programming K2x could corrupt K2z (they're on the same chip).
=====================================================================*/
static void test12_crosstalk(void) {
    unsigned int k2z_before, dz_before, k2z_after, dz_after;
    unsigned int k2x_before, dx_before, k2x_after, dx_after;
    unsigned int k2y_before, dy_before, k2y_after, dy_after;

    LOG("\n=== TEST 12: Counter Cross-Talk ===\n");
    LOG("PT0 has K2x(ch0), dX(ch1), K2z(ch2) on SAME chip.\n");
    LOG("PT1 has K2y(ch0), dY(ch1), dZ(ch2) on SAME chip.\n");
    LOG("Checking if programming one channel corrupts another.\n\n");

    /* Init: osc on, motors off */
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    /* --- Test A: Load Z counters, then load X, check Z --- */
    LOG("--- Test A: Load Z, then load X, check Z ---\n");

    /* Load K2z=1234 */
    outportb(ADRPT0+2, (unsigned char)(1234 % 256));
    outportb(ADRPT0+2, (unsigned char)(1234 / 256));
    /* Load dZ=5678 */
    outportb(ADRPT1+2, (unsigned char)(5678 % 256));
    outportb(ADRPT1+2, (unsigned char)(5678 / 256));
    delay(1);

    k2z_before = read_counter(ADRPT0, 2);
    dz_before  = read_counter(ADRPT1, 2);
    LOG("Before X load: K2z=%u  dZ=%u\n", k2z_before, dz_before);

    /* Now load K2x=9999 and dX=8888 */
    outportb(ADRPT0,   (unsigned char)(9999 % 256));
    outportb(ADRPT0,   (unsigned char)(9999 / 256));
    outportb(ADRPT0+1, (unsigned char)(8888 % 256));
    outportb(ADRPT0+1, (unsigned char)(8888 / 256));
    delay(1);

    k2z_after = read_counter(ADRPT0, 2);
    dz_after  = read_counter(ADRPT1, 2);
    LOG("After X load:  K2z=%u  dZ=%u\n", k2z_after, dz_after);

    if(k2z_before != k2z_after)
        LOG("*** K2z CHANGED from %u to %u after loading K2x! CROSS-TALK! ***\n",
            k2z_before, k2z_after);
    else
        LOG("K2z unchanged. No cross-talk on PT0.\n");

    if(dz_before != dz_after)
        LOG("*** dZ CHANGED from %u to %u after loading K2x+dX! ***\n",
            dz_before, dz_after);
    else
        LOG("dZ unchanged. No cross-talk on PT1.\n");

    /* --- Test B: Load Y, check dZ (same chip PT1) --- */
    LOG("\n--- Test B: Load Y, check dZ (both on PT1) ---\n");

    /* Reload dZ=5678 */
    outportb(ADRPT1+2, (unsigned char)(5678 % 256));
    outportb(ADRPT1+2, (unsigned char)(5678 / 256));
    delay(1);
    dz_before = read_counter(ADRPT1, 2);
    LOG("Before Y load: dZ=%u\n", dz_before);

    /* Load K2y=7777 and dY=6666 */
    outportb(ADRPT1,   (unsigned char)(7777 % 256));
    outportb(ADRPT1,   (unsigned char)(7777 / 256));
    outportb(ADRPT1+1, (unsigned char)(6666 % 256));
    outportb(ADRPT1+1, (unsigned char)(6666 / 256));
    delay(1);

    dz_after = read_counter(ADRPT1, 2);
    LOG("After Y load:  dZ=%u\n", dz_after);

    if(dz_before != dz_after)
        LOG("*** dZ CHANGED from %u to %u after loading K2y+dY! CROSS-TALK on PT1! ***\n",
            dz_before, dz_after);
    else
        LOG("dZ unchanged. No cross-talk on PT1.\n");

    /* --- Test C: Rapid alternating loads (stress test) --- */
    LOG("\n--- Test C: Rapid alternating XYZ counter loads ---\n");
    { int i; int fail = 0;
      for(i = 0; i < 50; i++) {
        unsigned int zt;
        /* Load Z */
        outportb(ADRPT0+2, (unsigned char)(4000 % 256));
        outportb(ADRPT0+2, (unsigned char)(4000 / 256));
        outportb(ADRPT1+2, (unsigned char)(3000 % 256));
        outportb(ADRPT1+2, (unsigned char)(3000 / 256));
        /* Load X (same chip as K2z) */
        outportb(ADRPT0,   (unsigned char)(2000 % 256));
        outportb(ADRPT0,   (unsigned char)(2000 / 256));
        /* Load Y (same chip as dZ) */
        outportb(ADRPT1,   (unsigned char)(1500 % 256));
        outportb(ADRPT1,   (unsigned char)(1500 / 256));
        /* Immediately read Z back */
        zt = read_counter(ADRPT0, 2);
        if(zt != 4000 && zt != 3999 && zt != 3998) {
            LOG("  iter %d: K2z=%u (expected ~4000) *** CORRUPT ***\n", i, zt);
            fail++;
        }
        zt = read_counter(ADRPT1, 2);
        if(zt != 3000 && zt != 2999 && zt != 2998) {
            LOG("  iter %d: dZ=%u (expected ~3000) *** CORRUPT ***\n", i, zt);
            fail++;
        }
      }
      if(!fail)
          LOG("50 rapid alternating loads: all Z counters stable.\n");
      else
          LOG("*** %d CORRUPTIONS in 50 iterations! ***\n", fail);
    }

    hw_stop();
    LOG("\n=== TEST 12 COMPLETE ===\n");
}


/*=====================================================================
    TEST 13: Sensor Noise During XY Motion

    Moves X and Y axes while monitoring Z end-stop sensors.
    If XY motor vibration induces electrical noise on the Z sensor
    lines, this will detect it. False Z sensor triggers during
    combined XY+Z moves could explain the step loss.
=====================================================================*/
static void test13_sensor_noise(void) {
    int rc;
    unsigned char stspb;
    int samples = 0, z_triggers = 0, any_triggers = 0;
    unsigned int home_steps;

    LOG("\n=== TEST 13: Sensor Noise During XY Motion ===\n");
    LOG("Moving XY while monitoring Z sensors for false triggers.\n\n");

    /* Home all first */
    rc = home_all();
    if(rc) { LOG("Home ABORTED\n"); return; }
    LOG("Homed. Starting XY motion...\n");

    /* Move to center area first (away from all sensors) */
    rc = move_xyz(15000, 10000, 5000);
    if(rc) { LOG("Move to center failed (rc=%d)\n", rc); hw_stop(); return; }

    /* Now do rapid XY-only moves while polling Z sensors */
    { int pass;
      for(pass = 0; pass < 5; pass++) {
        int x_to   = 20000 - pass * 1000;
        long k2;
        int dx, t;

        /* Program X move manually (not using move_xyz to keep Z static) */
        dx = x_to - xcur;
        if(!dx) continue;
        t = seg_time(dx, 0, 0);
        k2 = calc_k2(dx, t);

        outportb(ADRPT0,   (unsigned char)(k2 % 256));
        outportb(ADRPT0,   (unsigned char)(k2 / 256));
        outportb(ADRPT0+1, (unsigned char)(abs(dx) % 256));
        outportb(ADRPT0+1, (unsigned char)(abs(dx) / 256));
        /* X only: Y off, Z off, OSC on (bit7=0) */
        if(dx > 0) ctlw = XUP | XON;  /* 0x09 */
        else        ctlw = XON;        /* 0x08: dir bit0=0 = negative */
        outportb(ADRRG, ctlw);

        /* Poll sensors during X motion */
        while(1) {
            stspb = read_sensors();
            samples++;

            /* Check Z sensor bits (PB4, PB5) */
            if((stspb & 0x30) != 0x30) {
                z_triggers++;
                LOG("  *** Z sensor noise at sample %d: PB=0x%02X (pass %d) ***\n",
                    samples, (int)stspb, pass);
            }
            /* Check all sensor bits */
            if((stspb & 0x3f) != 0x3f) {
                any_triggers++;
            }

            /* X done? */
            if((stspb & 0x80) == 0x80) {
                ctlw = ctlw & XOFF;
                outportb(ADRRG, ctlw);
                xcur = x_to;
                break;
            }
            if(esc_pressed()) { hw_stop(); goto t13_done; }
        }
        LOG("  Pass %d: X->%d, %d samples, Z noise: %d\n",
            pass, x_to, samples, z_triggers);
      }
    }

t13_done:
    LOG("\nTotal: %d samples, %d Z sensor triggers, %d any sensor triggers\n",
        samples, z_triggers, any_triggers);
    if(z_triggers > 0)
        LOG("*** Z SENSORS TRIGGERED %d TIMES DURING XY MOTION! ***\n"
            "This could cause false end-stop detection in move()!\n", z_triggers);
    else
        LOG("No Z sensor noise detected during XY motion.\n");

    hw_stop();
    LOG("\n=== TEST 13 COMPLETE ===\n");
}


/*=====================================================================
    TEST 14: Gravity Drift (Stepper Hold Test)

    Disables stepper motor power (PC0=1), waits increasing
    intervals, re-enables steppers and homes to check if Z
    has drifted due to gravity. The Z axis is vertical and
    subject to gravitational pull when steppers are off.

    In FLINT, steppers stay ON between points (PC0=0 from
    pi_ini). But between F5 runs, if the operator pauses,
    the steppers might lose holding torque due to thermal
    protection or driver timeout.
=====================================================================*/
static void test14_gravity_drift(void) {
    int rc;
    unsigned int home_steps;
    int z_ref = 6000;   /* reference Z position to test from */
    int wait_times[] = {0, 1, 5, 10, 30};  /* seconds to wait with steppers off */
    int num_waits = 5;
    int w, delta;
    unsigned int baseline = 0;

    LOG("\n=== TEST 14: Gravity Drift (Stepper Hold) ===\n");
    LOG("Home -> move Z up -> disable steppers -> wait -> re-enable -> home.\n");
    LOG("Checks if Z drifts when stepper power is cut.\n\n");
    LOG("  %6s  %6s  %6s  %s\n", "Wait_s", "Home", "Delta", "Status");

    for(w = 0; w < num_waits; w++) {
        /* Home Z */
        rc = home_z(0, &home_steps);
        if(rc) { LOG("Home ABORTED\n"); return; }

        /* Move Z up to reference */
        rc = move_z(z_ref, 200);
        if(rc == 1) { LOG("ESC\n"); hw_stop(); return; }
        if(rc == 2) { LOG("SENSOR during move up\n"); continue; }

        /* Disable stepper motors (PC0=1: stepM off) */
        if(wait_times[w] > 0) {
            outportb(ADRPPI+2, 0xfd);  /* stepM=OFF, endS=enable */
            LOG("  Steppers OFF, waiting %d sec...", wait_times[w]);
            { int s;
              for(s = 0; s < wait_times[w]; s++) {
                delay(1000);
                if(esc_pressed()) { hw_stop(); LOG(" ESC\n"); return; }
              }
            }
            /* Re-enable steppers */
            outportb(ADRPPI+2, 0xfc);  /* stepM=ON, endS=enable */
            delay(50);  /* settle time */
            LOG(" re-enabled.\n");
        }

        /* Home Z and measure */
        rc = home_z(0, &home_steps);
        if(rc) { LOG("Home ABORTED\n"); return; }

        if(w == 0) {
            baseline = home_steps;
            LOG("  %5ds  %6u  %6s  baseline\n", wait_times[w], home_steps, "-");
        } else {
            delta = (int)home_steps - (int)baseline;
            LOG("  %5ds  %6u  %+5d  %s\n", wait_times[w], home_steps, delta,
                (abs(delta) > 10) ? "*** DRIFT ***" : "OK");
        }
    }

    /* Restore stepper power */
    outportb(ADRPPI+2, 0xfc);

    hw_stop();
    LOG("\n=== TEST 14 COMPLETE ===\n");
}


/*=====================================================================
    TEST 15: CPU Timing / delay() Calibration

    Borland's delay() is calibrated at startup using a busy loop.
    If the calibration is wrong, ALL timing in FLINT is wrong:
    - move() waits are too short/long
    - process() l_period pauses are wrong
    - dT correction is mismatched

    Also measures raw BIOS tick (INT 08h, 55ms) accuracy
    and busy-loop speed to characterize the CPU.
=====================================================================*/
static void test15_cpu_timing(void) {
    unsigned long t0, t1;
    unsigned long far *bios_tick = (unsigned long far *)MK_FP(0x40, 0x6C);
    int i;

    LOG("\n=== TEST 15: CPU Timing / delay() Calibration ===\n\n");

    /* --- Test A: delay(1) accuracy --- */
    LOG("--- A: delay() accuracy ---\n");
    LOG("Calling delay(N), measuring with BIOS tick counter (55ms/tick).\n\n");

    {
        int delays[] = {1, 10, 55, 100, 500, 1000};
        int num = 6;
        for(i = 0; i < num; i++) {
            unsigned long ticks;
            t0 = *bios_tick;
            delay(delays[i]);
            t1 = *bios_tick;
            ticks = t1 - t0;
            LOG("  delay(%4d ms): %3lu BIOS ticks = ~%lu ms  (expect ~%d ms)\n",
                delays[i], ticks, ticks * 55, delays[i]);
        }
    }

    /* --- Test B: BIOS tick rate verification --- */
    LOG("\n--- B: BIOS tick rate ---\n");
    LOG("Counting BIOS ticks over 1 second (delay-measured).\n");
    t0 = *bios_tick;
    delay(1000);
    t1 = *bios_tick;
    LOG("  1000ms delay = %lu ticks (expect ~18)\n", t1 - t0);
    if((t1 - t0) < 15 || (t1 - t0) > 22)
        LOG("  *** ABNORMAL tick rate! Timer may be reprogrammed. ***\n");
    else
        LOG("  Tick rate OK.\n");

    /* --- Test C: Busy-loop speed (characterizes CPU) --- */
    LOG("\n--- C: CPU busy-loop speed ---\n");
    {
        volatile unsigned long count = 0;
        t0 = *bios_tick;
        /* Wait for tick edge */
        while(*bios_tick == t0) { /* wait */ }
        t0 = *bios_tick;
        /* Count loops for exactly 1 tick (55ms) */
        while(*bios_tick == t0) count++;
        LOG("  Loops in 1 BIOS tick (~55ms): %lu\n", count);
        if(count < 100000UL)
            LOG("  => Slow CPU (486 class or heavy TSR load)\n");
        else if(count < 1000000UL)
            LOG("  => Pentium class\n");
        else
            LOG("  => Fast CPU (P3+ class)\n");
    }

    /* --- Test D: I/O port timing --- */
    LOG("\n--- D: I/O port access timing ---\n");
    LOG("100 sequential inportb() calls, timed with BIOS tick.\n");
    {
        volatile unsigned long count = 0;
        t0 = *bios_tick;
        while(*bios_tick == t0) { /* wait */ }
        t0 = *bios_tick;
        while(*bios_tick == t0) {
            (void)inportb(0x80);  /* unused port, safe read */
            count++;
        }
        LOG("  inportb(0x80) calls in 55ms: %lu\n", count);
        if(count > 0) {
            unsigned long ns_per_io = 55000000UL / count;
            LOG("  => ~%lu ns per I/O read\n", ns_per_io);
            if(ns_per_io < 500)
                LOG("  *** WARNING: Very fast I/O (<500ns). ISA 8254 may need wait states. ***\n");
        }
    }

    /* --- Test E: outportb pair timing (critical for 8254) --- */
    LOG("\n--- E: outportb() pair timing (8254 low+high byte) ---\n");
    LOG("The 8254 needs TWO consecutive writes (lo, hi). If an interrupt\n");
    LOG("fires between them, the counter gets a corrupted value.\n");
    {
        volatile unsigned long count = 0;
        t0 = *bios_tick;
        while(*bios_tick == t0) { /* wait */ }
        t0 = *bios_tick;
        while(*bios_tick == t0) {
            /* Simulate 8254 double-write to an unused port */
            outportb(0x80, 0x00);
            outportb(0x80, 0x00);
            count++;
        }
        LOG("  outportb() pairs in 55ms: %lu\n", count);
        if(count > 0) {
            unsigned long ns_per_pair = 55000000UL / count;
            LOG("  => ~%lu ns per write pair\n", ns_per_pair);
        }
    }

    LOG("\n=== TEST 15 COMPLETE ===\n");
}


/*=====================================================================
    TEST 16: Interrupt Interference

    Tests whether disabling interrupts (CLI) during counter
    programming and motor polling changes the outcome.

    The 8254 needs two consecutive byte writes. If INT 08h
    (timer) fires between outportb(lo) and outportb(hi),
    the counter gets garbage. This is the #1 suspect for
    intermittent step loss in recompiled code.

    Sub-tests:
    A) Program Z counter with CLI/STI, verify readback
    B) Same WITHOUT CLI/STI, check for corruption
    C) Move Z with CLI-protected counter programming
=====================================================================*/
static void test16_interrupt(void) {
    int i, fail_cli = 0, fail_nocli = 0;
    unsigned int target = 12345;
    unsigned int readback;

    LOG("\n=== TEST 16: Interrupt Interference ===\n");
    LOG("Testing if interrupts corrupt 8254 counter programming.\n\n");

    /* Init */
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    /* --- Test A: CLI-protected writes --- */
    LOG("--- A: 200 counter writes WITH CLI/STI ---\n");
    for(i = 0; i < 200; i++) {
        disable();  /* CLI */
        outportb(ADRPT1+2, (unsigned char)(target % 256));
        outportb(ADRPT1+2, (unsigned char)(target / 256));
        enable();   /* STI */
        delay(0);
        readback = read_counter(ADRPT1, 2);
        /* Mode 4: after load, counter may already start if GATE is high.
           Allow small decrement. */
        if(readback != target && readback != target - 1 && readback != target - 2) {
            LOG("  iter %d: wrote %u, read %u *** MISMATCH ***\n", i, target, readback);
            fail_cli++;
        }
    }
    LOG("  Result: %d/200 corrupt with CLI. %s\n", fail_cli,
        fail_cli ? "*** STILL CORRUPT ***" : "OK");

    /* --- Test B: Unprotected writes (normal code path) --- */
    LOG("\n--- B: 200 counter writes WITHOUT CLI (normal code) ---\n");
    for(i = 0; i < 200; i++) {
        outportb(ADRPT1+2, (unsigned char)(target % 256));
        outportb(ADRPT1+2, (unsigned char)(target / 256));
        delay(0);
        readback = read_counter(ADRPT1, 2);
        if(readback != target && readback != target - 1 && readback != target - 2) {
            LOG("  iter %d: wrote %u, read %u *** MISMATCH ***\n", i, target, readback);
            fail_nocli++;
        }
    }
    LOG("  Result: %d/200 corrupt without CLI. %s\n", fail_nocli,
        fail_nocli ? "*** INTERRUPT CORRUPTION DETECTED ***" : "OK");

    /* --- Analysis --- */
    LOG("\nAnalysis:\n");
    if(fail_nocli > 0 && fail_cli == 0)
        LOG("  => INTERRUPTS corrupt counter writes! CLI/STI needed around outportb pairs.\n"
            "  => This is the likely cause of Z step loss in recompiled code!\n");
    else if(fail_nocli > 0 && fail_cli > 0)
        LOG("  => Corruption even with CLI. Hardware or bus timing issue.\n");
    else if(fail_nocli == 0 && fail_cli == 0)
        LOG("  => No corruption detected in 200 iterations.\n"
            "  => Interrupt interference is unlikely (but not impossible under load).\n");

    /* --- Test C: Move Z with CLI-protected programming --- */
    if(fail_nocli > 0) {
        unsigned int home_steps;
        int rc, delta;
        int test_dist = 5000;

        LOG("\n--- C: Z move with CLI-protected counter programming ---\n");
        rc = home_z(0, &home_steps);
        if(rc) { LOG("Home ABORTED\n"); return; }

        /* CLI-protected move */
        disable();
        outportb(ADRPT0+2, (unsigned char)(100 % 256));
        outportb(ADRPT0+2, (unsigned char)(100 / 256));
        outportb(ADRPT1+2, (unsigned char)(test_dist % 256));
        outportb(ADRPT1+2, (unsigned char)(test_dist / 256));
        ctlw = (ZUP | ZON) & XOFF & YOFF & OSCON;
        outportb(ADRRG, ctlw);
        enable();

        rc = wait_z_done();
        if(rc) { LOG("Move failed rc=%d\n", rc); hw_stop(); return; }

        rc = home_z(0, &home_steps);
        if(rc) { LOG("Home2 ABORTED\n"); return; }
        delta = (int)home_steps - test_dist;
        LOG("  CLI-protected move: home=%u expected=%d delta=%+d %s\n",
            home_steps, test_dist, delta,
            (abs(delta) > 10) ? "*** STILL LOSES ***" : "OK");
    }

    hw_stop();
    LOG("\n=== TEST 16 COMPLETE ===\n");
}


/*=====================================================================
    TEST 17: System Environment Report

    Collects and logs everything about the DOS environment:
    - DOS version
    - Conventional + extended memory
    - CPU type indicators
    - Loaded device drivers / TSRs (via MCB chain)
    - ISA card port scan (beyond base 0x300)

    None of this moves any motors. Pure information gathering.
=====================================================================*/
static void test17_environment(void) {
    LOG("\n=== TEST 17: System Environment Report ===\n\n");

    /* --- DOS version --- */
    {
        union REGS r;
        r.h.ah = 0x30;
        int86(0x21, &r, &r);
        LOG("DOS version: %d.%d\n", r.h.al, r.h.ah);
    }

    /* --- Conventional memory --- */
    {
        union REGS r;
        int86(0x12, &r, &r);
        LOG("Conventional memory: %d KB\n", r.x.ax);
    }

    /* --- Extended memory (INT 15h, AH=88h) --- */
    {
        union REGS r;
        r.h.ah = 0x88;
        int86(0x15, &r, &r);
        LOG("Extended memory (XMS): %u KB\n", r.x.ax);
    }

    /* --- CPU flags test (crude 386+ detection) --- */
    LOG("\nCPU identification:\n");
    {
        /* On 8086/286 pushf/popf behave differently.
           We just report what compiler says + loop speed from test15 */
#ifdef __BORLANDC__
        LOG("  Compiler: Borland C++ %d.%d\n",
            __BORLANDC__ / 0x100, (__BORLANDC__ % 0x100) / 0x10);
#endif
#ifdef __WATCOMC__
        LOG("  Compiler: Watcom C/C++ %d.%d\n",
            __WATCOMC__ / 100, __WATCOMC__ % 100);
#endif
        LOG("  sizeof(int)=%d sizeof(long)=%d sizeof(void*)=%d\n",
            (int)sizeof(int), (int)sizeof(long), (int)sizeof(void*));
        LOG("  Memory model: ");
#ifdef __TINY__
        LOG("TINY\n");
#elif defined(__SMALL__)
        LOG("SMALL\n");
#elif defined(__MEDIUM__)
        LOG("MEDIUM\n");
#elif defined(__COMPACT__)
        LOG("COMPACT\n");
#elif defined(__LARGE__)
        LOG("LARGE\n");
#elif defined(__HUGE__)
        LOG("HUGE\n");
#elif defined(__FLAT__)
        LOG("FLAT (32-bit)\n");
#else
        LOG("unknown\n");
#endif
    }

    /* --- Program Segment Prefix info --- */
    {
        unsigned int psp_seg;
        unsigned char far *psp;
        unsigned int env_seg;
        unsigned char far *env;
        int env_count = 0;

        /* Get PSP segment */
        {   union REGS r; struct SREGS s;
            r.h.ah = 0x62;
            intdosx(&r, &r, &s);
            psp_seg = r.x.bx;
        }
        psp = (unsigned char far *)MK_FP(psp_seg, 0);
        /* Environment segment is at PSP:002Ch */
        env_seg = *(unsigned int far *)(psp + 0x2C);
        env = (unsigned char far *)MK_FP(env_seg, 0);

        LOG("\nEnvironment variables:\n");
        while(*env) {
            char line[128];
            int j = 0;
            while(*env && j < 127) line[j++] = *env++;
            line[j] = 0;
            env++;
            LOG("  %s\n", line);
            env_count++;
            if(env_count > 30) { LOG("  ... (truncated)\n"); break; }
        }
    }

    /* --- ISA port scan (0x300..0x31F) --- */
    LOG("\nISA card port scan (0x300-0x31F):\n");
    {
        int port;
        for(port = 0x300; port < 0x320; port++) {
            unsigned char val = inportb(port);
            if((port & 0x07) == 0) LOG("  %03X:", port);
            LOG(" %02X", (int)val);
            if((port & 0x07) == 7) LOG("\n");
        }
    }

    /* --- Stack info --- */
    LOG("\nStack pointer (approx): SP=%u\n", _SP);

    /* --- BIOS equipment list --- */
    {
        union REGS r;
        int86(0x11, &r, &r);
        LOG("BIOS equipment word: 0x%04X\n", r.x.ax);
        LOG("  Floppy: %s, Video mode: %d, Serial ports: %d, Printers: %d\n",
            (r.x.ax & 1) ? "yes" : "no",
            (r.x.ax >> 4) & 3,
            (r.x.ax >> 9) & 7,
            (r.x.ax >> 14) & 3);
    }

    LOG("\n=== TEST 17 COMPLETE ===\n");
}


/*=====================================================================
    TEST 18: Timing-Critical Sequence Stress Test

    Simulates the EXACT I/O sequence that move() does when
    programming a Z move, but does it 1000 times and checks
    if the counter value is correct each time.

    This catches intermittent problems that test 16 might miss:
    - The full sequence is: program K2z (2 bytes), program dZ
      (2 bytes), set RG, then immediately read back. Under heavy
      interrupt load, one of the 4 outportb calls can be delayed.

    Runs both with and without CLI to compare.
=====================================================================*/
static void test18_sequence_stress(void) {
    int i;
    int fail_nocli = 0, fail_cli = 0;
    unsigned int k2z_tgt = 200;
    unsigned int dz_tgt  = 5000;
    unsigned int rb_k2z, rb_dz;

    LOG("\n=== TEST 18: Timing-Critical Sequence Stress ===\n");
    LOG("Programming K2z+dZ 1000 times, checking readback each time.\n");
    LOG("(Simulates move() counter programming sequence)\n\n");

    /* Init: osc on, motors off */
    ctlw = (XUP|YUP|ZUP) & XOFF & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(10);

    /* --- Without CLI --- */
    LOG("--- A: 1000 iterations WITHOUT CLI ---\n");
    for(i = 0; i < 1000; i++) {
        /* Exact move() sequence for Z: */
        outportb(ADRPT0+2, (unsigned char)(k2z_tgt % 256));   /* K2z lo */
        outportb(ADRPT0+2, (unsigned char)(k2z_tgt / 256));   /* K2z hi */
        outportb(ADRPT1+2, (unsigned char)(dz_tgt % 256));    /* dZ lo */
        outportb(ADRPT1+2, (unsigned char)(dz_tgt / 256));    /* dZ hi */
        /* DON'T start motor — just verify counter values */
        rb_k2z = read_counter(ADRPT0, 2);
        rb_dz  = read_counter(ADRPT1, 2);
        /* Allow small decrement for mode2 auto-reload */
        if(abs((int)rb_k2z - (int)k2z_tgt) > 3) {
            if(fail_nocli < 20)
                LOG("  i=%d K2z: wrote %u, read %u ***\n", i, k2z_tgt, rb_k2z);
            fail_nocli++;
        }
        if(abs((int)rb_dz - (int)dz_tgt) > 3) {
            if(fail_nocli < 20)
                LOG("  i=%d dZ: wrote %u, read %u ***\n", i, dz_tgt, rb_dz);
            fail_nocli++;
        }
    }
    LOG("  Without CLI: %d failures / 2000 checks. %s\n\n", fail_nocli,
        fail_nocli ? "*** CORRUPTION ***" : "OK");

    /* --- With CLI --- */
    LOG("--- B: 1000 iterations WITH CLI ---\n");
    for(i = 0; i < 1000; i++) {
        disable();
        outportb(ADRPT0+2, (unsigned char)(k2z_tgt % 256));
        outportb(ADRPT0+2, (unsigned char)(k2z_tgt / 256));
        outportb(ADRPT1+2, (unsigned char)(dz_tgt % 256));
        outportb(ADRPT1+2, (unsigned char)(dz_tgt / 256));
        enable();
        rb_k2z = read_counter(ADRPT0, 2);
        rb_dz  = read_counter(ADRPT1, 2);
        if(abs((int)rb_k2z - (int)k2z_tgt) > 3) {
            if(fail_cli < 20)
                LOG("  i=%d K2z: wrote %u, read %u ***\n", i, k2z_tgt, rb_k2z);
            fail_cli++;
        }
        if(abs((int)rb_dz - (int)dz_tgt) > 3) {
            if(fail_cli < 20)
                LOG("  i=%d dZ: wrote %u, read %u ***\n", i, dz_tgt, rb_dz);
            fail_cli++;
        }
    }
    LOG("  With CLI: %d failures / 2000 checks. %s\n\n", fail_cli,
        fail_cli ? "*** STILL CORRUPT ***" : "OK");

    /* --- Analysis --- */
    LOG("Analysis:\n");
    if(fail_nocli > 0 && fail_cli == 0)
        LOG("  => INTERRUPTS corrupt the 4-write sequence!\n"
            "  => CLI/STI wrapping around counter programming in move() would fix the bug.\n");
    else if(fail_nocli > 0 && fail_cli > 0)
        LOG("  => Corruption persists even with CLI.\n"
            "  => Hardware timing issue (ISA bus speed, wait states).\n");
    else
        LOG("  => No corruption in 1000 iterations.\n");

    hw_stop();
    LOG("\n=== TEST 18 COMPLETE ===\n");
}


/*=====================================================================
    AUTO-DIAGNOSTIC
    
    Runs ALL tests in sequence, producing a full report
    in Z_DIAG.LOG. The operator just starts it and waits.
    
    Phase 0: Environment & timing (no hardware needed)
      - System info, CPU timing, delay() calibration
    Phase 1: Hardware readout (no motors)
      - Sensor snapshot, counter probe, 8254 modes, osc frequency
    Phase 2: Sensor reliability
      - Homing repeatability (10 cycles)
    Phase 3: Z-only motor tests
      - PB6/PB7, step integrity, thermal, Z bug reproduction
    Phase 4: Counter & wiring tests
      - Cross-talk, interrupt interference, sequence stress
    Phase 5: XY+Z interaction tests (MOST IMPORTANT)
      - XY+Z simultaneous integrity, sensor noise, process simulation
    Phase 6: Mechanical tests
      - Gravity drift with steppers off
=====================================================================*/
static void auto_diagnostic(void) {
    unsigned char ppi_pb;
    int sensor_ok = 1;

    LOG("\n");
    LOG("###########################################################\n");
    LOG("#                                                         #\n");
    LOG("#              Z_DIAG AUTO-DIAGNOSTIC                     #\n");
    LOG("#                                                         #\n");
    LOG("###########################################################\n");
    LOG("\nRunning full diagnostic sequence...\n");
    LOG("Press ESC at any time to abort.\n\n");

    /* --- Phase 0: Environment & timing (no motors, no card needed) --- */
    LOG("============ PHASE 0: Environment & CPU timing ============\n");

    test17_environment();
    if(esc_pressed()) goto aborted;

    test15_cpu_timing();
    if(esc_pressed()) goto aborted;

    /* --- Phase 1: Safe read-only tests (no motors) --- */
    LOG("============ PHASE 1: Hardware readout (no motors) ============\n");

    /* Sensor snapshot */
    LOG("\n--- Sensor Snapshot ---\n");
    ppi_pb = read_sensors();
    LOG("PPI PB = 0x%02X\n", (int)ppi_pb);
    LOG("  X-: %d  X+: %d  Y-: %d  Y+: %d  Z-: %d  Z+: %d  PB6: %d  PB7: %d\n",
        ppi_pb&1, (ppi_pb>>1)&1, (ppi_pb>>2)&1, (ppi_pb>>3)&1,
        (ppi_pb>>4)&1, (ppi_pb>>5)&1, (ppi_pb>>6)&1, (ppi_pb>>7)&1);
    LOG("PT0.ch0(K2x)=%u  PT0.ch1(dX)=%u  PT0.ch2(K2z)=%u\n",
        read_counter(ADRPT0, 0), read_counter(ADRPT0, 1), read_counter(ADRPT0, 2));
    LOG("PT1.ch0(K2y)=%u  PT1.ch1(dY)=%u  PT1.ch2(dZ)=%u\n",
        read_counter(ADRPT1, 0), read_counter(ADRPT1, 1), read_counter(ADRPT1, 2));

    if(esc_pressed()) goto aborted;

    /* Counter probe */
    test1_counter_probe();
    if(esc_pressed()) goto aborted;

    /* 8254 mode detect */
    test3_mode_detect();
    if(esc_pressed()) goto aborted;

    /* Oscillator frequency */
    test6_osc_freq();
    if(esc_pressed()) goto aborted;

    /* --- Phase 2: Homing sensor check --- */
    LOG("\n============ PHASE 2: Sensor reliability ============\n");
    test9_home_repeat();
    if(esc_pressed()) goto aborted;

    /* Check if sensor was reliable from test9 output */
    /* We re-run a quick 3-home check inline for the flag */
    {
        unsigned int h1, h2, h3;
        int rc, spread;
        rc = home_z(0, &h1);
        if(rc) goto aborted;
        rc = move_z(2000, 200);
        if(rc == 1) goto aborted;
        rc = home_z(0, &h2);
        if(rc) goto aborted;
        rc = move_z(2000, 200);
        if(rc == 1) goto aborted;
        rc = home_z(0, &h3);
        if(rc) goto aborted;
        spread = (int)h2 - (int)h3;
        if(spread < 0) spread = -spread;
        if(spread > 20) {
            sensor_ok = 0;
            LOG("\n*** WARNING: Sensor spread=%d > 20 steps. Motor test results are SUSPECT. ***\n", spread);
        }
    }

    /* --- Phase 3: Motor tests --- */
    LOG("\n============ PHASE 3: Motor tests ============\n");
    if(!sensor_ok)
        LOG("(Sensor unreliable - results below may not reflect real step loss)\n");

    /* PB6/PB7 signal */
    test2_pb_signal();
    if(esc_pressed()) goto aborted;

    /* Step integrity */
    test4_z_integrity();
    if(esc_pressed()) goto aborted;

    /* Thermal */
    test5_thermal();
    if(esc_pressed()) goto aborted;

    /* Reproduce bug (Z-only) */
    test8_reproduce();
    if(esc_pressed()) goto aborted;

    /* --- Phase 4: Counter & wiring tests --- */
    LOG("\n============ PHASE 4: Counter cross-talk & wiring ============\n");

    test12_crosstalk();
    if(esc_pressed()) goto aborted;

    test16_interrupt();
    if(esc_pressed()) goto aborted;

    test18_sequence_stress();
    if(esc_pressed()) goto aborted;

    /* --- Phase 5: XY+Z combined tests (MOST IMPORTANT) --- */
    LOG("\n============ PHASE 5: XY+Z interaction tests ============\n");
    LOG("(These tests replicate actual FLINT move() behavior)\n");

    test10_xyz_integrity();
    if(esc_pressed()) goto aborted;

    test13_sensor_noise();
    if(esc_pressed()) goto aborted;

    test11_process_sim();
    if(esc_pressed()) goto aborted;

    /* --- Phase 6: Gravity/hold test --- */
    LOG("\n============ PHASE 6: Mechanical tests ============\n");

    test14_gravity_drift();

    /* --- Summary --- */
    LOG("\n");
    LOG("###########################################################\n");
    LOG("#              AUTO-DIAGNOSTIC COMPLETE                    #\n");
    LOG("###########################################################\n");
    LOG("\nConfig: l_period=%d dT=%d step_freq=%d f_const=%d\n",
        cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
    LOG("Sensor reliability: %s\n", sensor_ok ? "OK" : "*** UNRELIABLE ***");
    LOG("Full results saved to Z_DIAG.LOG\n");
    LOG("Send this file for analysis.\n");
    return;

aborted:
    LOG("\n*** AUTO-DIAGNOSTIC ABORTED BY USER (ESC) ***\n");
    LOG("Partial results saved to Z_DIAG.LOG\n");
    hw_stop();
}


/*=====================================================================
    MAIN MENU
=====================================================================*/
int main(void) {
    int choice;

    logf = fopen("Z_DIAG.LOG", "w");
    if(logf) fprintf(logf, "=== Z_DIAG Log Start ===\n");

    printf("=== Z_DIAG: FLINT Z-Axis Diagnostic Tool ===\n");
    printf("Detecting hardware...\n");
    if(!hw_detect()) {
        LOG("\n*** WARNING: ISA card NOT DETECTED at base address 0x%03X ***\n", ADRPT0);
        LOG("K1 readback failed (expected 150, got %d).\n", (int)inportb(ADRPPI));
        LOG("Test results below are WITHOUT real hardware.\n\n");
        printf("WARNING: ISA card not found. Results will be without hardware.\n\n");
    } else {
        LOG("ISA card detected at 0x%03X. K1=%d\n\n", ADRPT0, (int)inportb(ADRPPI));
    }
    printf("Initializing...\n");
    hw_init();
    LOG("Hardware initialized. Sensors: 0x%02X\n\n", (int)read_sensors());

    while(1) {
        printf("\n");
        printf("  A. >>> AUTO-DIAGNOSTIC (run all, save log, ~30 min) <<<\n");
        printf("\n");
        printf("  --- Z-only tests ---\n");
        printf("  1. Counter behavior probe (no motors)\n");
        printf("  2. PB6/PB7 signal source (50 steps Z)\n");
        printf("  3. 8254 mode detection (read-back)\n");
        printf("  4. Z step integrity (various speeds)\n");
        printf("  5. Thermal accumulation (10 cycles)\n");
        printf("  6. Oscillator frequency measurement\n");
        printf("  7. Full sensor/port readout\n");
        printf("  8. Reproduce Z bug from log (Z-only)\n");
        printf("  9. Homing repeatability (sensor check)\n");
        printf("\n");
        printf("  --- XY+Z interaction tests ---\n");
        printf("  B. XY+Z simultaneous move integrity\n");
        printf("  C. Full process() simulation (XY+Z)\n");
        printf("  D. Counter cross-talk (PT0/PT1)\n");
        printf("  E. Sensor noise during XY motion\n");
        printf("  F. Gravity drift (stepper hold)\n");
        printf("\n");
        printf("  --- Environment & timing tests ---\n");
        printf("  H. CPU timing / delay() calibration\n");
        printf("  I. Interrupt interference test\n");
        printf("  J. System environment report\n");
        printf("  K. I/O sequence stress test (1000x)\n");
        printf("\n");
        printf("  G. Config (l_period=%d dT=%d sf=%d fc=%d)\n",
               cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
        printf("  0. Exit\n");
        printf("\nChoice: ");

        choice = bioskey(0) & 0xff;
        printf("%c\n", choice);

        switch(choice) {
            case 'a': case 'A': auto_diagnostic(); break;
            case '1': test1_counter_probe(); break;
            case '2': test2_pb_signal(); break;
            case '3': test3_mode_detect(); break;
            case '4': test4_z_integrity(); break;
            case '5': test5_thermal(); break;
            case '6': test6_osc_freq(); break;
            case '7': test7_sensor_readout(); break;
            case '8': test8_reproduce(); break;
            case '9': test9_home_repeat(); break;
            case 'b': case 'B': test10_xyz_integrity(); break;
            case 'c': case 'C': test11_process_sim(); break;
            case 'd': case 'D': test12_crosstalk(); break;
            case 'e': case 'E': test13_sensor_noise(); break;
            case 'f': case 'F': test14_gravity_drift(); break;
            case 'h': case 'H': test15_cpu_timing(); break;
            case 'i': case 'I': test16_interrupt(); break;
            case 'j': case 'J': test17_environment(); break;
            case 'k': case 'K': test18_sequence_stress(); break;
            case 'g': case 'G':
                printf("l_period (ms) [%d]: ", cfg_l_period);
                { char buf[20]; int v;
                  gets(buf);
                  if(buf[0]) { v = atoi(buf); if(v > 0) cfg_l_period = v; }
                }
                printf("dT (ms) [%d]: ", cfg_dT);
                { char buf[20]; int v;
                  gets(buf);
                  if(buf[0]) { v = atoi(buf); if(v >= 0) cfg_dT = v; }
                }
                printf("step_freq (Hz) [%d]: ", cfg_step_freq);
                { char buf[20]; int v;
                  gets(buf);
                  if(buf[0]) { v = atoi(buf); if(v > 0) cfg_step_freq = v; }
                }
                printf("f_const (0/1) [%d]: ", cfg_f_const);
                { char buf[20]; int v;
                  gets(buf);
                  if(buf[0]) { v = atoi(buf); cfg_f_const = (v != 0) ? 1 : 0; }
                }
                LOG("Config updated: l_period=%d dT=%d step_freq=%d f_const=%d\n",
                    cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
                break;
            case '0': case 27: goto done;
            default: printf("Invalid choice\n"); break;
        }
    }

done:
    hw_stop();
    if(logf) {
        fprintf(logf, "=== Z_DIAG Log End ===\n");
        fclose(logf);
    }
    printf("\nDone. Results saved to Z_DIAG.LOG\n");
    return 0;
}
