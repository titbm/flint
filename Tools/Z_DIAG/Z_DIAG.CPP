/*********************************************************************
    Z_DIAG v2 — Standalone diagnostic for FLINT ISA hardware

    Structure:
      Phase 1 (tests 1-2):   Environment & CPU
      Phase 2 (tests 3-5):   Hardware identification
      Phase 3 (tests 6-10):  Hardware behavior study
      Phase 4 (tests 11-18): Bug hunt

    Safety: all homing loops have timeouts, ESC stops everything.
    Compile: see COMPILE.bat (BC45 -ml -O1 -3)
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
static int xcur = 0, ycur = 0, zcur = 0;

/* Config (from FLINT log: [PROC] CFG line) */
static int cfg_l_period  = 35;
static int cfg_dT        = 6;
static int cfg_step_freq = 1000;
static int cfg_f_const   = 0;

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

/*--- 8253 counter read (latch + lo + hi) ---*/
static unsigned int read_counter(int base, int ch) {
    unsigned int lo, hi;
    unsigned char latch_cmd = (unsigned char)(ch << 6);
    outportb(base+3, latch_cmd);
    lo = (unsigned int)inportb(base+ch);
    hi = (unsigned int)inportb(base+ch);
    return lo + hi*256;
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

/*--- ISA card detection (write K1=150, read back) ---*/
static int hw_detect(void) {
    outportb(ADRPPI+3, 0x82);
    outportb(ADRPPI, 150);
    return (inportb(ADRPPI) == 150);
}

/*--- Full hardware init (same as pi_ini in PIC.CPP) ---*/
static void hw_init(void) {
    ctlw = (XUP|YUP|ZUP)&XOFF&YOFF&ZOFF&OSCON;
    outportb(ADRRG, ctlw);
    outportb(LRG, 0);
    outportb(ADRPPI+3, 0x82);
    outportb(ADRPPI, 150);
    outportb(ADRPPI+2, 0xfd);
    outportb(ADRPPI+2, 0xff);
    outportb(ADRPPI+2, 0xfc);
    outportb(ADRPPI2+3, 0x91);
    outportb(ADRPPI2+1, 0xff);
    outportb(ADRPPI2+3, 0x09);
    outportb(ADRPPI2+3, 0x0b);
    outportb(ADRPPI2+3, 0x0d);
    outportb(ADRPT0+3, 0x34);   /* PT0.ch0 K2x: mode2 lo+hi */
    outportb(ADRPT0+3, 0x78);   /* PT0.ch1 dX:  mode4 lo+hi */
    outportb(ADRPT0+3, 0xb4);   /* PT0.ch2 K2z: mode2 lo+hi */
    outportb(ADRPT1+3, 0x34);   /* PT1.ch0 K2y: mode2 lo+hi */
    outportb(ADRPT1+3, 0x78);   /* PT1.ch1 dY:  mode4 lo+hi */
    outportb(ADRPT1+3, 0xb8);   /* PT1.ch2 dZ:  mode4 lo+hi */
}

/*--- Emergency stop ---*/
static void hw_stop(void) {
    ctlw = ctlw & XOFF & YOFF & ZOFF;
    outportb(ADRRG, ctlw);
    ctlw = ctlw | OSCOFF;
    outportb(ADRRG, ctlw);
}

/*--- Stop all motors and reset PB6/PB7 latches ---*/
static void hw_full_stop(void) {
    outportb(ADRRG, 0x80);          /* all motors off, OSC off */
    outportb(ADRPPI+2, 0xff);      /* reset PB6/PB7 latches  */
    outportb(ADRPPI+2, 0xfc);      /* re-enable sensors      */
}

/*--- Wait for Z done (PB6), with ESC and sensor check ---*/
static int wait_z_done(void) {
    unsigned char stspb;
    long loops = 0;
    while(1) {
        stspb = read_sensors();
        if(stspb & 0x40) {
            ctlw = ctlw & ZOFF;
            outportb(ADRRG, ctlw);
            break;
        }
        if((stspb & 0x30) != 0x30) {
            delay(1);
            stspb = read_sensors();
            if((stspb & 0x30) != 0x30) { hw_stop(); return 2; }
        }
        outportb(ADRRG, ctlw);
        if(esc_pressed()) { hw_stop(); return 1; }
        loops++;
        if(loops > 10000000L) { hw_stop(); return 3; }
    }
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

/*--- Home Z only. Always sends mode CW (safe). ---*/
/* Returns: 0=ok, 1=ESC/abort */
static int home_z(unsigned int *steps_taken) {
    unsigned char stspb;
    int fz;
    unsigned int z_remain;

    hw_full_stop();                /* reset PB6 before starting */
    outportb(ADRPT0+3, 0xb4);
    outportb(ADRPT1+3, 0xb8);
    outportb(ADRPT0+2, 0x64); outportb(ADRPT0+2, 0x00);  /* K2z=100 */
    outportb(ADRPT1+2, 0x00); outportb(ADRPT1+2, 0x40);  /* dZ=16384 */

    ctlw = ZON & ZDOWN & OSCON & XOFF & YOFF;
    ctlw = ctlw & XOFF & YOFF;
    outportb(ADRRG, ctlw);

    fz = 1;
    z_remain = 16384;
    { long loops = 0;
    while(fz) {
        stspb = read_sensors();
        if((stspb & 0x30) != 0x30) {
            z_remain = read_counter(ADRPT1, 2);
            ctlw = ctlw & ZOFF;
            fz = 0;
        }
        if(stspb & 0x40) { z_remain = 0; ctlw = ctlw & ZOFF; fz = 0; }
        outportb(ADRRG, ctlw);
        if(esc_pressed()) { hw_stop(); return 1; }
        loops++;
        if(loops > 10000000L) { hw_stop(); return 1; }
    }
    }
    *steps_taken = 16384 - z_remain;

    /* Slow reverse with debounce */
    outportb(ADRPT0+2, 0xc8); outportb(ADRPT0+2, 0x00);  /* K2z=200 */
    outportb(ADRPT1+2, 0xc8); outportb(ADRPT1+2, 0x00);  /* dZ=200 */
    ctlw = (ZON | ZUP) & XOFF & YOFF & OSCON;
    outportb(ADRRG, ctlw);
    { int done = 0; long loops2 = 0;
    while(!done) {
        unsigned char t = read_sensors(); int j;
        for(j = 0; j < 10; j++) t &= read_sensors();
        if(t & 0x40) { ctlw = ctlw & ZOFF; done = 1; }
        outportb(ADRRG, ctlw);
        if(esc_pressed()) { hw_stop(); return 1; }
        loops2++;
        if(loops2 > 5000000L) { hw_stop(); return 1; }
    }
    }
    outportb(ADRRG, 0x80);
    return 0;
}

/*--- Home all 3 axes. reinit=1 sends mode CWs first (safe). ---*/
/* reinit=0 replicates exact FLINT move_sen(0) behavior. */
/* Returns: 0=ok, 1=ESC/abort */
static int home_all(int reinit) {
    unsigned char stspb, tw;

    hw_full_stop();                /* reset PB6/PB7 before starting */
    if(reinit) {
        outportb(ADRPT0+3, 0x34);
        outportb(ADRPT0+3, 0x78);
        outportb(ADRPT0+3, 0xb4);
        outportb(ADRPT1+3, 0x34);
        outportb(ADRPT1+3, 0x78);
        outportb(ADRPT1+3, 0xb8);
    }

    outportb(ADRPT0,   0x64); outportb(ADRPT0,   0x00);
    outportb(ADRPT0+1, 0x00); outportb(ADRPT0+1, 0x70);
    outportb(ADRPT1,   0x64); outportb(ADRPT1,   0x00);
    outportb(ADRPT1+1, 0x00); outportb(ADRPT1+1, 0x70);
    outportb(ADRPT0+2, 0x64); outportb(ADRPT0+2, 0x00);
    outportb(ADRPT1+2, 0x00); outportb(ADRPT1+2, 0x40);

    ctlw = (XON|YON|ZON|XUP) & YDOWN & ZDOWN & OSCON;
    tw   = (ctlw|XUP) & XOFF & YOFF & ZOFF & YDOWN & ZDOWN & OSCON;
    outportb(ADRRG, ctlw);

    { long loops = 0;
    while(ctlw != tw) {
        stspb = read_sensors();
        if((stspb & 0x03) != 0x03) ctlw = ctlw & XOFF;
        if((stspb & 0x0c) != 0x0c) ctlw = ctlw & YOFF;
        if((stspb & 0x30) != 0x30) ctlw = ctlw & ZOFF;
        outportb(ADRRG, ctlw);
        loops++;
        if(loops > 10000000L) {
            LOG("*** home_all phase C TIMEOUT ***\n");
            ctlw = ctlw & XOFF & YOFF & ZOFF;
            outportb(ADRRG, ctlw); break;
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    }

    /* Phase D: slow reverse with debounce */
    outportb(ADRPT0,   0xc8); outportb(ADRPT0,   0x00);
    outportb(ADRPT0+1, 0xc8); outportb(ADRPT0+1, 0x00);
    outportb(ADRPT1,   0xc8); outportb(ADRPT1,   0x00);
    outportb(ADRPT1+1, 0xc8); outportb(ADRPT1+1, 0x00);
    outportb(ADRPT0+2, 0xc8); outportb(ADRPT0+2, 0x00);
    outportb(ADRPT1+2, 0xc8); outportb(ADRPT1+2, 0x00);
    ctlw = (XON|YON|ZON|YUP|ZUP) & XDOWN & OSCON;
    outportb(ADRRG, ctlw);

    { int fxy=1, fz=1, done=0; long loops2=0;
    while(!done) {
        unsigned char t = read_sensors(); int j;
        for(j=0; j<10; j++) t &= read_sensors();
        if(t & 0x80) { ctlw = ctlw & XOFF & YOFF; fxy=0; }
        if(t & 0x40) { ctlw = ctlw & ZOFF; fz=0; }
        outportb(ADRRG, ctlw);
        if(!fxy && !fz) done=1;
        loops2++;
        if(loops2 > 5000000L) {
            LOG("*** home_all phase D TIMEOUT ***\n");
            ctlw = ctlw & XOFF & YOFF & ZOFF;
            outportb(ADRRG, ctlw); done=1;
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    }
    outportb(ADRRG, 0x80);
    xcur = 23300; ycur = 200; zcur = 200;
    return 0;
}

/*--- Move XYZ (exact FLINT move() replica) ---*/
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

    { long loops = 0;
    while(!done) {
        stspb = read_sensors();
        if(fxy && (stspb & 0x80)) { ctlw = ctlw & XOFF & YOFF; fxy = 0; }
        if(fz  && (stspb & 0x40)) { ctlw = ctlw & ZOFF; fz = 0; }
        outportb(ADRRG, ctlw);
        if(!fxy && !fz) done = 1;
        if((stspb & 0x3f) != 0x3f) {
            delay(1);
            stspb = read_sensors();
            if((stspb & 0x3f) != 0x3f) { hw_stop(); return 2; }
        }
        if(esc_pressed()) { hw_stop(); return 1; }
        loops++;
        if(loops > 10000000L) { hw_stop(); return 3; }
    }
    }
    hw_full_stop();
    xcur = x; ycur = y; zcur = z;
    return 0;
}

/*--- Move Z by 'steps' at speed k2z ---*/
static int move_z(int steps, unsigned int k2z) {
    unsigned int abssteps;
    if(!steps) return 0;
    abssteps = (unsigned int)abs(steps);
    outportb(ADRPT0+2, (unsigned char)(k2z % 256));
    outportb(ADRPT0+2, (unsigned char)(k2z / 256));
    outportb(ADRPT1+2, (unsigned char)(abssteps % 256));
    outportb(ADRPT1+2, (unsigned char)(abssteps / 256));
    ctlw = ctlw & XOFF & YOFF & ZOFF;
    if(steps > 0) ctlw = (ctlw | ZUP | ZON) & OSCON;
    else          ctlw = ((ctlw & ZDOWN) | ZON) & OSCON;
    outportb(ADRRG, ctlw);
    { int rc = wait_z_done();
      hw_full_stop();
      return rc;
    }
}

/*--- Measure K2z timing (loads K2z WITHOUT mode CW) ---*/
/* Returns: loops (>0), -1=PB6 stuck, -2=timeout */
static long measure_k2z_timing(unsigned int k2z_val) {
    long loops;
    ctlw = 0x80;
    outportb(ADRRG, ctlw);

    /* dZ mode CW resets its flip-flop (known good) */
    outportb(ADRPT1+3, 0xb8);
    /* K2z: NO mode CW — tests flip-flop state as-is */
    outportb(ADRPT0+2, (unsigned char)(k2z_val % 256));
    outportb(ADRPT0+2, (unsigned char)(k2z_val / 256));
    outportb(ADRPT1+2, 0x01);
    outportb(ADRPT1+2, 0x00);

    /* Reset PB6 latch */
    outportb(ADRPPI+2, 0xff);
    outportb(ADRPPI+2, 0xfc);

    if(inportb(ADRPPI+1) & 0x40) return -1;

    ctlw = 0x20;  /* ZON, OSC on */
    outportb(ADRRG, ctlw);

    loops = 0;
    while(!(inportb(ADRPPI+1) & 0x40)) {
        loops++;
        if(loops > 10000000L) {
            ctlw = 0x80; outportb(ADRRG, ctlw);
            return -2;
        }
    }
    ctlw = 0x80; outportb(ADRRG, ctlw);
    return loops;
}

/*--- Run N-point process cycle (like FLINT process()) ---*/
static int run_points(int xbase, int ybase, int zbase,
                      int z_step, int layers, int pts) {
    int rc, layer, pt;
    rc = move_xyz(xbase, ybase, zbase);
    if(rc) return 1;
    for(layer = 0; layer < layers; layer++) {
        int znew = zbase - layer * z_step;
        for(pt = 0; pt < pts; pt++) {
            int xnew = xbase + (pt % 5) * 100 - 200;
            int ynew = ybase + (pt / 5) * 100;
            rc = move_xyz(xnew, ynew, znew);
            if(rc) { hw_stop(); return 1; }
            delay(cfg_l_period);
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }
    return 0;
}

/*--- Instrumented homing. Records Z trigger point. ---*/
/* axes: bitmask 1=X, 2=Y, 4=Z */
/* reinit: 1=send mode CWs, 0=FLINT-exact (no mode CW) */
/* Returns: 0=ok, 1=ESC, 2=timeout */
static int instrumented_homing(int reinit, int axes,
                               unsigned int *z_steps, long *z_loop) {
    unsigned char tw;
    long loops;
    int z_triggered = 0;

    outportb(ADRPPI+2, 0xfc);  /* STEP_ON */
    delay(30);

    if(reinit) {
        outportb(ADRPT0+3, 0x34);
        outportb(ADRPT0+3, 0x78);
        outportb(ADRPT0+3, 0xb4);
        outportb(ADRPT1+3, 0x34);
        outportb(ADRPT1+3, 0x78);
        outportb(ADRPT1+3, 0xb8);
    }

    /* Load counters for selected axes */
    if(axes & 1) {
        outportb(ADRPT0,   0x64); outportb(ADRPT0,   0x00);
        outportb(ADRPT0+1, 0x00); outportb(ADRPT0+1, 0x70);
    }
    if(axes & 2) {
        outportb(ADRPT1,   0x64); outportb(ADRPT1,   0x00);
        outportb(ADRPT1+1, 0x00); outportb(ADRPT1+1, 0x70);
    }
    if(axes & 4) {
        outportb(ADRPT0+2, 0x64); outportb(ADRPT0+2, 0x00);
        outportb(ADRPT1+2, 0x00); outportb(ADRPT1+2, 0x40);
    }

    /* Build ctlw and target */
    ctlw = OSCON & XOFF & YOFF & ZOFF;
    if(axes & 1) ctlw = ctlw | XON | XUP;
    if(axes & 2) ctlw = (ctlw | YON) & YDOWN;
    if(axes & 4) ctlw = (ctlw | ZON) & ZDOWN;
    tw = ctlw & XOFF & YOFF & ZOFF;
    outportb(ADRRG, ctlw);

    loops = 0;
    while(ctlw != tw) {
        unsigned char stspb = inportb(ADRPPI+1);
        if((axes & 1) && ((stspb & 0x03) != 0x03)) ctlw = ctlw & XOFF;
        if((axes & 2) && ((stspb & 0x0c) != 0x0c)) ctlw = ctlw & YOFF;
        if((axes & 4) && ((stspb & 0x30) != 0x30)) {
            if(!z_triggered) {
                unsigned int dz_remain = read_counter(ADRPT1, 2);
                *z_steps = 16384 - dz_remain;
                *z_loop = loops;
                z_triggered = 1;
            }
            ctlw = ctlw & ZOFF;
        }
        outportb(ADRRG, ctlw);
        loops++;
        if(loops > 10000000L) {
            ctlw = ctlw & XOFF & YOFF & ZOFF;
            outportb(ADRRG, ctlw);
            outportb(ADRRG, 0x80);
            *z_steps = 0; *z_loop = loops;
            outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
            return 2;
        }
        if(esc_pressed()) { hw_stop(); return 1; }
    }

    /* Phase D: slow reverse with debounce */
    if(axes & 1) {
        outportb(ADRPT0,   0xc8); outportb(ADRPT0,   0x00);
        outportb(ADRPT0+1, 0xc8); outportb(ADRPT0+1, 0x00);
    }
    if(axes & 2) {
        outportb(ADRPT1,   0xc8); outportb(ADRPT1,   0x00);
        outportb(ADRPT1+1, 0xc8); outportb(ADRPT1+1, 0x00);
    }
    if(axes & 4) {
        outportb(ADRPT0+2, 0xc8); outportb(ADRPT0+2, 0x00);
        outportb(ADRPT1+2, 0xc8); outportb(ADRPT1+2, 0x00);
    }
    /* Reverse directions */
    ctlw = OSCON & XOFF & YOFF & ZOFF;
    if(axes & 1) ctlw = (ctlw | XON) & XDOWN;
    if(axes & 2) ctlw = ctlw | YON | YUP;
    if(axes & 4) ctlw = ctlw | ZON | ZUP;
    outportb(ADRRG, ctlw);

    { int fxy=(axes&3)?1:0, fz=(axes&4)?1:0, done=0;
      long loops2 = 0;
      while(!done) {
          unsigned char t = inportb(ADRPPI+1); int j;
          for(j=0; j<10; j++) t &= inportb(ADRPPI+1);
          if(fxy && (t & 0x80)) { ctlw = ctlw & XOFF & YOFF; fxy=0; }
          if(fz  && (t & 0x40)) { ctlw = ctlw & ZOFF; fz=0; }
          outportb(ADRRG, ctlw);
          if(!fxy && !fz) done=1;
          loops2++;
          if(loops2 > 5000000L) {
              ctlw = ctlw & XOFF & YOFF & ZOFF;
              outportb(ADRRG, ctlw); break;
          }
          if(esc_pressed()) { hw_stop(); return 1; }
      }
    }
    outportb(ADRRG, 0x80);
    xcur = 23300; ycur = 200; zcur = 200;
    if(!z_triggered) { *z_steps = 16384; *z_loop = loops; }
    outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
    return 0;
}


/* ================================================================== */
/*                     PHASE 1: ENVIRONMENT                           */
/* ================================================================== */

/*--- TEST 1: Environment Report ---*/
static void test01_environment(void) {
    union REGS r;
    int i;

    LOG("\n=== TEST 1: Environment Report ===\n\n");

    /* DOS version */
    r.x.ax = 0x3000;
    int86(0x21, &r, &r);
    LOG("DOS version: %d.%02d\n", r.h.al, r.h.ah);

    /* Conventional memory */
    int86(0x12, &r, &r);
    LOG("Conventional memory: %d KB\n", r.x.ax);

    /* Extended memory */
    r.x.ax = 0x8800;
    int86(0x15, &r, &r);
    LOG("Extended memory (int15h): %u KB\n", r.x.ax);

    /* Compiler info */
    LOG("\nCompiler: Borland C++ %d.%d\n",
        __BORLANDC__ / 0x100, (__BORLANDC__ % 0x100) / 0x10);
    LOG("sizeof(int)=%d sizeof(long)=%d sizeof(void*)=%d\n",
        (int)sizeof(int), (int)sizeof(long), (int)sizeof(void*));
#ifdef __LARGE__
    LOG("Memory model: LARGE\n");
#else
    LOG("Memory model: unknown\n");
#endif

    /* BIOS equipment word */
    int86(0x11, &r, &r);
    LOG("\nBIOS equipment word: 0x%04X\n", r.x.ax);
    LOG("  Floppy: %s, Video mode: %d, Serial ports: %d, Printers: %d\n",
        (r.x.ax & 1) ? "yes" : "no",
        (r.x.ax >> 4) & 3,
        (r.x.ax >> 9) & 7,
        (r.x.ax >> 14) & 3);

    /* Stack pointer */
    { unsigned int sp_val;
      sp_val = (unsigned int)&sp_val;
      LOG("Stack pointer (approx): SP=%u\n", sp_val);
    }

    /* Environment variables */
    LOG("\nEnvironment variables:\n");
    { const char *vars[] = {"CONFIG","PROMPT","COMSPEC","PATH",
                            "TEMP","TMP","CMDLINE",NULL};
      for(i = 0; vars[i]; i++) {
          const char *v = getenv(vars[i]);
          if(v) LOG("  %s=%s\n", vars[i], v);
      }
    }

    LOG("\n=== TEST 1 COMPLETE ===\n");
}


/*--- TEST 2: CPU Timing ---*/
static void test02_cpu_timing(void) {
    unsigned long t0, t1;
    unsigned long far *bios_tick = (unsigned long far *)MK_FP(0x40, 0x6C);
    int i;

    LOG("\n=== TEST 2: CPU Timing ===\n\n");

    /* A: delay() accuracy */
    LOG("--- A: delay() accuracy ---\n");
    { int delays[] = {1, 10, 55, 100, 500, 1000};
      for(i = 0; i < 6; i++) {
          unsigned long ticks;
          t0 = *bios_tick;
          delay(delays[i]);
          t1 = *bios_tick;
          ticks = t1 - t0;
          LOG("  delay(%4d ms): %3lu ticks = ~%lu ms\n",
              delays[i], ticks, ticks * 55);
      }
    }

    /* B: BIOS tick rate */
    LOG("\n--- B: BIOS tick rate ---\n");
    t0 = *bios_tick;
    delay(1000);
    t1 = *bios_tick;
    LOG("  1000ms = %lu ticks (expect ~18). %s\n", t1-t0,
        ((t1-t0) >= 15 && (t1-t0) <= 22) ? "OK" : "*** ABNORMAL ***");

    /* C: Busy-loop speed */
    LOG("\n--- C: CPU busy-loop speed ---\n");
    { volatile unsigned long count = 0;
      t0 = *bios_tick;
      while(*bios_tick == t0) {}
      t0 = *bios_tick;
      while(*bios_tick == t0) count++;
      LOG("  Loops in 55ms: %lu", count);
      if(count < 100000UL)      LOG(" (486 class)\n");
      else if(count < 1000000UL) LOG(" (Pentium class)\n");
      else                       LOG(" (P3+ class)\n");
    }

    /* D: I/O read timing */
    LOG("\n--- D: I/O read timing ---\n");
    { volatile unsigned long count = 0;
      t0 = *bios_tick;
      while(*bios_tick == t0) {}
      t0 = *bios_tick;
      while(*bios_tick == t0) { (void)inportb(0x80); count++; }
      LOG("  inportb() calls in 55ms: %lu => ~%lu ns/read\n",
          count, count ? 55000000UL/count : 0);
    }

    /* E: I/O write pair timing */
    LOG("\n--- E: outportb() pair timing ---\n");
    { volatile unsigned long count = 0;
      t0 = *bios_tick;
      while(*bios_tick == t0) {}
      t0 = *bios_tick;
      while(*bios_tick == t0) {
          outportb(0x80, 0x00); outportb(0x80, 0x00); count++;
      }
      LOG("  pairs in 55ms: %lu => ~%lu ns/pair\n",
          count, count ? 55000000UL/count : 0);
    }

    LOG("\n=== TEST 2 COMPLETE ===\n");
}


/* ================================================================== */
/*                PHASE 2: HARDWARE IDENTIFICATION                    */
/* ================================================================== */

/*--- TEST 3: Port Scan ---*/
static void test03_port_scan(void) {
    int i, j;
    LOG("\n=== TEST 3: Port Scan 0x300-0x31F ===\n\n");
    for(i = 0x300; i < 0x320; i += 8) {
        LOG("  %03X:", i);
        for(j = 0; j < 8; j++)
            LOG(" %02X", (int)inportb(i+j));
        LOG("  |");
        /* Annotate */
        if(i == 0x300) LOG(" PT0 (K2x,dX,K2z)");
        if(i == 0x304) LOG(" PT1 (K2y,dY,dZ) [+3=CW]");
        if(i == 0x308) LOG(" PPI (PA,PB,PC,CW)");
        if(i == 0x30c) LOG(" RG,?,?,? PPI2-lo");
        if(i == 0x310) LOG(" PPI2 (PA,PB,PC,CW)");
        if(i == 0x314) LOG(" PT2 (laser timers)");
        if(i == 0x318) LOG(" CMOS counter");
        if(i == 0x31c) LOG(" LRG + upper");
        LOG("\n");
    }
    LOG("\n=== TEST 3 COMPLETE ===\n");
}


/*--- TEST 4: PPI Verify ---*/
static void test04_ppi_verify(void) {
    unsigned char pa, pb, pc;

    LOG("\n=== TEST 4: PPI (8255) Verify ===\n\n");

    /* Init PPI */
    outportb(ADRPPI+3, 0x82);  /* mode0, PA=out, PB=inp, PC=out */

    /* PA write/read */
    outportb(ADRPPI, 150);
    pa = inportb(ADRPPI);
    LOG("PA: wrote 150, read %d. %s\n", (int)pa,
        (pa == 150) ? "OK" : "*** FAIL ***");
    outportb(ADRPPI, 200);
    pa = inportb(ADRPPI);
    LOG("PA: wrote 200, read %d. %s\n", (int)pa,
        (pa == 200) ? "OK" : "*** FAIL ***");
    outportb(ADRPPI, 150);  /* restore K1=150 */

    /* PB read (input port — sensors) */
    pb = inportb(ADRPPI+1);
    LOG("PB (sensors): 0x%02X\n", (int)pb);
    LOG("  X-=%d X+=%d Y-=%d Y+=%d Z-=%d Z+=%d PB6=%d PB7=%d\n",
        pb&1, (pb>>1)&1, (pb>>2)&1, (pb>>3)&1,
        (pb>>4)&1, (pb>>5)&1, (pb>>6)&1, (pb>>7)&1);

    /* PC write/read */
    outportb(ADRPPI+2, 0xfc);
    pc = inportb(ADRPPI+2);
    LOG("PC: wrote 0xFC, read 0x%02X\n", (int)pc);

    /* PPI2 check */
    outportb(ADRPPI2+3, 0x91);
    LOG("PPI2 PA (input): 0x%02X\n", (int)inportb(ADRPPI2));
    LOG("PPI2 PB (output): 0x%02X\n", (int)inportb(ADRPPI2+1));

    LOG("\n=== TEST 4 COMPLETE ===\n");
}


/*--- TEST 5: Timer Chip Identification ---*/
static void test05_timer_chip_id(void) {
    int chip;
    int bases[] = {ADRPT0, ADRPT1, ADRPT2};
    const char *names[] = {"PT0", "PT1", "PT2"};

    LOG("\n=== TEST 5: Timer Chip ID (8253 vs 8254) ===\n");
    LOG("For each chip: write value, verify via latch+read,\n");
    LOG("then test Read-Back. If Read-Back corrupts → 8253.\n\n");

    for(chip = 0; chip < 3; chip++) {
        int base = bases[chip];
        unsigned int wrote, read1, read2;
        unsigned char rb_byte;

        LOG("--- %s (base 0x%03X) ---\n", names[chip], base);

        /* Send mode CW for ch0: mode 2, binary, lo+hi */
        outportb(base+3, 0x34);
        /* Load 12345 */
        wrote = 12345;
        outportb(base, (unsigned char)(wrote % 256));
        outportb(base, (unsigned char)(wrote / 256));
        delay(1);

        /* Latch + read ch0 */
        read1 = read_counter(base, 0);
        LOG("  Write %u, latch+read: %u. %s\n", wrote, read1,
            (abs((int)read1 - (int)wrote) < 5) ? "OK" : "*** BAD ***");

        /* Now send Read-Back command (0xE2 = ch0 status+count) */
        outportb(base+3, 0xE2);
        rb_byte = inportb(base);    /* read whatever comes back */
        LOG("  Read-Back byte: 0x%02X\n", (int)rb_byte);

        /* WITHOUT re-sending mode CW, write+read again */
        outportb(base, (unsigned char)(wrote % 256));
        outportb(base, (unsigned char)(wrote / 256));
        delay(1);
        read2 = read_counter(base, 0);
        LOG("  After RB, write %u, read: %u.", wrote, read2);
        if(abs((int)read2 - (int)wrote) < 5) {
            LOG(" OK => Read-Back did NOT corrupt. Likely 8254.\n");
        } else {
            LOG(" *** CORRUPT (%u) => 8253 (shared flip-flop) ***\n", read2);
        }

        /* Always restore chip to clean state */
        hw_init();
        LOG("\n");
    }

    LOG("=== TEST 5 COMPLETE ===\n");
}


/* ================================================================== */
/*                PHASE 3: HARDWARE BEHAVIOR                          */
/* ================================================================== */

/*--- TEST 6: Oscillator Frequency ---*/
static void test06_osc_frequency(void) {
    unsigned long far *bios_tick = (unsigned long far *)MK_FP(0x40, 0x6C);
    unsigned long t0;
    unsigned int v1, v2, delta;

    LOG("\n=== TEST 6: Oscillator Frequency ===\n\n");
    hw_init();

    /* Method A: use K2x (GATE always HIGH, confirmed by log 13.03) */
    LOG("--- A: Via K2x (GATE always HIGH) ---\n");
    outportb(ADRPT0+3, 0x34);   /* K2x: mode2, lo+hi */
    outportb(ADRPT0, (unsigned char)(60000u % 256));
    outportb(ADRPT0, (unsigned char)(60000u / 256));
    delay(2);  /* let counter load */

    v1 = read_counter(ADRPT0, 0);
    t0 = *bios_tick;
    while(*bios_tick == t0) {}  /* wait for tick edge */
    t0 = *bios_tick;
    while(*bios_tick == t0) {}  /* wait exactly 1 tick = 55ms */
    v2 = read_counter(ADRPT0, 0);

    if(v2 < v1) delta = v1 - v2;
    else delta = v1 + 60000u - v2;  /* wrapped */
    LOG("  K2x: %u -> %u in 55ms, delta=%u\n", v1, v2, delta);
    LOG("  OSC frequency (via K2x): ~%lu Hz\n", (unsigned long)delta * 1000 / 55);

    /* Method B: use K2z (needs ZON + OSC) */
    LOG("\n--- B: Via K2z (needs ZON+OSC) ---\n");
    hw_init();
    outportb(ADRPT0+3, 0xb4);   /* K2z: mode2, lo+hi */
    outportb(ADRPT0+2, (unsigned char)(60000u % 256));
    outportb(ADRPT0+2, (unsigned char)(60000u / 256));
    /* Enable ZON + OSC */
    ctlw = ZON & XOFF & YOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(2);

    v1 = read_counter(ADRPT0, 2);
    t0 = *bios_tick;
    while(*bios_tick == t0) {}
    t0 = *bios_tick;
    while(*bios_tick == t0) {}
    v2 = read_counter(ADRPT0, 2);

    ctlw = 0x80; outportb(ADRRG, ctlw);

    if(v2 < v1) delta = v1 - v2;
    else delta = v1 + 60000u - v2;
    LOG("  K2z: %u -> %u in 55ms, delta=%u\n", v1, v2, delta);
    LOG("  OSC frequency (via K2z): ~%lu Hz\n", (unsigned long)delta * 1000 / 55);

    hw_init();
    LOG("\n=== TEST 6 COMPLETE ===\n");
}


/*--- TEST 7: Counter GATE Map ---*/
static void test07_gate_map(void) {
    unsigned int v1, v2;
    int delta;

    LOG("\n=== TEST 7: Counter GATE Map ===\n");
    LOG("Which control signals gate each counter channel?\n\n");
    LOG("  %-12s  %-20s  %6s  %6s  %s\n",
        "Channel", "Condition", "Before", "After", "Counting?");

    /* K2x (PT0.ch0): test without and with motor */
    hw_init();
    outportb(ADRPT0+3, 0x34);
    outportb(ADRPT0, (unsigned char)(50000u%256));
    outportb(ADRPT0, (unsigned char)(50000u/256));
    delay(2);
    v1 = read_counter(ADRPT0, 0);
    delay(50);
    v2 = read_counter(ADRPT0, 0);
    delta = (int)v1-(int)v2;
    LOG("  K2x(PT0.0)   OSC on, XON off       %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    hw_init();
    outportb(ADRPT0+3, 0x34);
    outportb(ADRPT0, (unsigned char)(50000u%256));
    outportb(ADRPT0, (unsigned char)(50000u/256));
    ctlw = ctlw | OSCOFF;
    outportb(ADRRG, ctlw);
    delay(2);
    v1 = read_counter(ADRPT0, 0);
    delay(50);
    v2 = read_counter(ADRPT0, 0);
    delta = (int)v1-(int)v2;
    LOG("  K2x(PT0.0)   OSC OFF, XON off      %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    /* K2y (PT1.ch0) */
    hw_init();
    outportb(ADRPT1+3, 0x34);
    outportb(ADRPT1, (unsigned char)(50000u%256));
    outportb(ADRPT1, (unsigned char)(50000u/256));
    delay(2);
    v1 = read_counter(ADRPT1, 0);
    delay(50);
    v2 = read_counter(ADRPT1, 0);
    delta = (int)v1-(int)v2;
    LOG("  K2y(PT1.0)   OSC on, YON off       %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    hw_init();
    outportb(ADRPT1+3, 0x34);
    outportb(ADRPT1, (unsigned char)(50000u%256));
    outportb(ADRPT1, (unsigned char)(50000u/256));
    ctlw = ctlw | YON;
    ctlw = ctlw & OSCON;
    outportb(ADRRG, ctlw);
    delay(2);
    v1 = read_counter(ADRPT1, 0);
    delay(50);
    v2 = read_counter(ADRPT1, 0);
    delta = (int)v1-(int)v2;
    LOG("  K2y(PT1.0)   OSC on, YON on        %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    /* K2z (PT0.ch2) */
    hw_init();
    outportb(ADRPT0+3, 0xb4);
    outportb(ADRPT0+2, (unsigned char)(50000u%256));
    outportb(ADRPT0+2, (unsigned char)(50000u/256));
    delay(2);
    v1 = read_counter(ADRPT0, 2);
    delay(50);
    v2 = read_counter(ADRPT0, 2);
    delta = (int)v1-(int)v2;
    LOG("  K2z(PT0.2)   OSC on, ZON off       %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    hw_init();
    outportb(ADRPT0+3, 0xb4);
    outportb(ADRPT0+2, (unsigned char)(50000u%256));
    outportb(ADRPT0+2, (unsigned char)(50000u/256));
    ctlw = ctlw | ZON;
    ctlw = ctlw & OSCON;
    outportb(ADRRG, ctlw);
    delay(2);
    v1 = read_counter(ADRPT0, 2);
    delay(50);
    v2 = read_counter(ADRPT0, 2);
    delta = (int)v1-(int)v2;
    LOG("  K2z(PT0.2)   OSC on, ZON on        %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    hw_init();
    outportb(ADRPT0+3, 0xb4);
    outportb(ADRPT0+2, (unsigned char)(50000u%256));
    outportb(ADRPT0+2, (unsigned char)(50000u/256));
    ctlw = ctlw | ZON | OSCOFF;
    outportb(ADRRG, ctlw);
    delay(2);
    v1 = read_counter(ADRPT0, 2);
    delay(50);
    v2 = read_counter(ADRPT0, 2);
    delta = (int)v1-(int)v2;
    LOG("  K2z(PT0.2)   OSC OFF, ZON on       %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    /* dZ (PT1.ch2) — CLK from K2z OUT */
    hw_init();
    outportb(ADRPT0+3, 0xb4);
    outportb(ADRPT1+3, 0xb8);
    outportb(ADRPT0+2, 0x64); outportb(ADRPT0+2, 0x00);  /* K2z=100 */
    outportb(ADRPT1+2, (unsigned char)(50000u%256));
    outportb(ADRPT1+2, (unsigned char)(50000u/256));  /* dZ=50000 */
    ctlw = ZON & XOFF & YOFF & OSCON;
    outportb(ADRRG, ctlw);
    delay(2);
    v1 = read_counter(ADRPT1, 2);
    delay(50);
    v2 = read_counter(ADRPT1, 2);
    delta = (int)v1-(int)v2;
    LOG("  dZ(PT1.2)    K2z=100,ZON on,OSC on %6u  %6u  %s\n",
        v1, v2, (abs(delta)>5)?"YES":"no");

    hw_init();
    LOG("\n=== TEST 7 COMPLETE ===\n");
}


/*--- TEST 8: Sensor Snapshot ---*/
static void test08_sensor_snapshot(void) {
    unsigned char pb, pa, pc, pa2, pb2;

    LOG("\n=== TEST 8: Sensor Snapshot ===\n\n");

    pa = inportb(ADRPPI);
    pb = inportb(ADRPPI+1);
    pc = inportb(ADRPPI+2);

    LOG("PPI (0x308):\n");
    LOG("  PA = 0x%02X (K1=%d)\n", (int)pa, (int)pa);
    LOG("  PB = 0x%02X (sensors)\n", (int)pb);
    LOG("    X- =%d  X+ =%d  Y- =%d  Y+ =%d  Z- =%d  Z+ =%d  PB6=%d  PB7=%d\n",
        pb&1, (pb>>1)&1, (pb>>2)&1, (pb>>3)&1,
        (pb>>4)&1, (pb>>5)&1, (pb>>6)&1, (pb>>7)&1);
    LOG("  PC = 0x%02X\n", (int)pc);
    LOG("    stepM=%d  endS=%d  ctl2=%d  ctl3=%d  ctl4=%d  LASER=%d  pulse=%d  PROT=%d\n",
        pc&1, (pc>>1)&1, (pc>>2)&1, (pc>>3)&1,
        (pc>>4)&1, (pc>>5)&1, (pc>>6)&1, (pc>>7)&1);

    pa2 = inportb(ADRPPI2);
    pb2 = inportb(ADRPPI2+1);
    LOG("\nPPI2 (0x310):\n");
    LOG("  PA = 0x%02X (external sensors)\n", (int)pa2);
    LOG("  PB = 0x%02X (EM shutters)\n", (int)pb2);

    /* Counter values */
    LOG("\nCounters (after hw_init):\n");
    LOG("  PT0: K2x=%u  dX=%u  K2z=%u\n",
        read_counter(ADRPT0, 0), read_counter(ADRPT0, 1),
        read_counter(ADRPT0, 2));
    LOG("  PT1: K2y=%u  dY=%u  dZ=%u\n",
        read_counter(ADRPT1, 0), read_counter(ADRPT1, 1),
        read_counter(ADRPT1, 2));
    LOG("  PT2: ch0=%u  ch1=%u  ch2=%u\n",
        read_counter(ADRPT2, 0), read_counter(ADRPT2, 1),
        read_counter(ADRPT2, 2));

    /* RG and LRG */
    LOG("\nRG (ctlw): 0x%02X\n", (int)ctlw);
    LOG("LRG: 0x%02X\n", (int)inportb(LRG));
    LOG("CMOS: 0x%02X 0x%02X\n", (int)inportb(ADRCMOS), (int)inportb(ADRCMOS+1));

    LOG("\n=== TEST 8 COMPLETE ===\n");
}


/*--- TEST 9: PB6/PB7 Signal Nature ---*/
static void test09_pb_nature(void) {
    int i;
    unsigned char pb_readings[500];

    LOG("\n=== TEST 9: PB6/PB7 Signal Nature ===\n");
    LOG("Is PB6 (Z done) a latch or one-shot pulse?\n\n");

    hw_init();

    /* Test A: Z cascade → PB6 */
    LOG("--- A: Z cascade (no physical movement, STEP_OFF) ---\n");
    outportb(ADRPPI+2, 0xfd);  /* STEP_OFF (safe) */
    outportb(ADRPT0+3, 0xb4);  /* K2z mode2 */
    outportb(ADRPT1+3, 0xb8);  /* dZ mode4 */
    outportb(ADRPT0+2, 0xc8); outportb(ADRPT0+2, 0x00);  /* K2z=200 */
    outportb(ADRPT1+2, 0x64); outportb(ADRPT1+2, 0x00);  /* dZ=100 */

    /* Reset PB latch */
    outportb(ADRPPI+2, 0xff);
    outportb(ADRPPI+2, 0xfd);

    LOG("  PB6 before start: %d\n", (inportb(ADRPPI+1)>>6)&1);

    /* Enable ZON + OSC */
    ctlw = ZON & XOFF & YOFF & OSCON;
    outportb(ADRRG, ctlw);

    /* Wait for PB6 */
    { long loops = 0;
      while(!(inportb(ADRPPI+1) & 0x40)) {
          loops++;
          if(loops > 10000000L) {
              LOG("  *** TIMEOUT: PB6 never went HIGH ***\n");
              ctlw = 0x80; outportb(ADRRG, ctlw);
              goto test9_b;
          }
      }
      LOG("  PB6 went HIGH after %ld poll loops\n", loops);
    }

    /* Read PB 500 times immediately */
    for(i = 0; i < 500; i++)
        pb_readings[i] = inportb(ADRPPI+1);

    ctlw = 0x80; outportb(ADRRG, ctlw);

    { int high = 0;
      for(i = 0; i < 500; i++)
          if(pb_readings[i] & 0x40) high++;
      LOG("  500 reads after PB6: %d HIGH, %d LOW\n", high, 500-high);
      if(high > 480)
          LOG("  => PB6 is LATCHED (stays HIGH)\n");
      else if(high < 20)
          LOG("  => PB6 is ONE-SHOT (~%d us pulse)\n", high * 629 / 1000);
      else
          LOG("  => PB6 intermediate (%d/500)\n", high);
    }

    /* Test sensor reset */
    LOG("  PB6 before reset: %d\n", (inportb(ADRPPI+1)>>6)&1);
    outportb(ADRPPI+2, 0xff);  /* endS reset */
    outportb(ADRPPI+2, 0xfc);  /* endS enable */
    LOG("  PB6 after reset:  %d\n", (inportb(ADRPPI+1)>>6)&1);

    /* Duration test: how many reads PB6 stays HIGH */
    LOG("\n  Duration test (dZ=10, K2z=500):\n");
    hw_init();
    outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
    outportb(ADRPT0+3, 0xb4);
    outportb(ADRPT1+3, 0xb8);
    outportb(ADRPT0+2, 0xF4); outportb(ADRPT0+2, 0x01);  /* K2z=500 */
    outportb(ADRPT1+2, 0x0A); outportb(ADRPT1+2, 0x00);  /* dZ=10 */
    outportb(ADRPPI+2, 0xff);
    outportb(ADRPPI+2, 0xfd);
    ctlw = ZON & XOFF & YOFF & OSCON;
    outportb(ADRRG, ctlw);
    while(!(inportb(ADRPPI+1) & 0x40)) {
        if(esc_pressed()) { hw_stop(); return; }
    }
    { long count = 0;
      while(inportb(ADRPPI+1) & 0x40) {
          count++;
          if(count > 100000L) break;
      }
      LOG("  PB6 HIGH for %ld reads (~%ld us)\n",
          count, count * 629 / 1000);
      if(count > 100000L)
          LOG("  => LATCHED (stays forever until reset)\n");
      else
          LOG("  => TIMED: decays after ~%ld us\n", count*629/1000);
    }
    ctlw = 0x80; outportb(ADRRG, ctlw);

test9_b:
    /* Test B: XY cascade → PB7 */
    LOG("\n--- B: XY cascade → PB7 ---\n");
    hw_init();
    outportb(ADRPPI+2, 0xfd);
    outportb(ADRPT0+3, 0x34);  /* K2x mode2 */
    outportb(ADRPT0+3, 0x78);  /* dX mode4 */
    outportb(ADRPT0, 0xc8); outportb(ADRPT0, 0x00);    /* K2x=200 */
    outportb(ADRPT0+1, 0x64); outportb(ADRPT0+1, 0x00); /* dX=100 */
    outportb(ADRPPI+2, 0xff);
    outportb(ADRPPI+2, 0xfd);
    LOG("  PB7 before start: %d\n", (inportb(ADRPPI+1)>>7)&1);
    ctlw = XON & YOFF & ZOFF & OSCON;
    outportb(ADRRG, ctlw);
    { long loops = 0;
      while(!(inportb(ADRPPI+1) & 0x80)) {
          loops++;
          if(loops > 10000000L) {
              LOG("  *** TIMEOUT: PB7 never went HIGH ***\n");
              ctlw = 0x80; outportb(ADRRG, ctlw);
              goto test9_end;
          }
      }
      LOG("  PB7 went HIGH after %ld loops\n", loops);
    }
    { int high = 0;
      for(i = 0; i < 200; i++)
          if(inportb(ADRPPI+1) & 0x80) high++;
      LOG("  200 reads: %d HIGH => %s\n", high,
          (high > 180) ? "LATCHED" : "one-shot/timed");
    }
    ctlw = 0x80; outportb(ADRRG, ctlw);

test9_end:
    hw_init();
    LOG("\n=== TEST 9 COMPLETE ===\n");
}


/*--- TEST 10: Sensor Reset Behavior ---*/
static void test10_sensor_reset(void) {
    unsigned char pb;

    LOG("\n=== TEST 10: Sensor Reset Behavior ===\n\n");

    /* Current state */
    pb = inportb(ADRPPI+1);
    LOG("PB before any reset: 0x%02X\n", (int)pb);

    /* Sensor reset sequence (PC1 toggle) */
    LOG("\nSensor reset sequence (PC1=1 then PC1=0):\n");
    outportb(ADRPPI+2, 0xff);  /* endS=1 (reset) */
    pb = inportb(ADRPPI+1);
    LOG("  After PC=0xFF (reset active): PB=0x%02X\n", (int)pb);
    outportb(ADRPPI+2, 0xfc);  /* stepM=on, endS=0 (enable) */
    pb = inportb(ADRPPI+1);
    LOG("  After PC=0xFC (enable):       PB=0x%02X\n", (int)pb);

    /* STEP_ON / STEP_OFF effect */
    LOG("\nSTEP control (PC0):\n");
    outportb(ADRPPI+2, 0xfc);  /* stepM ON (PC0=0) */
    pb = inportb(ADRPPI+1);
    LOG("  STEP_ON  (PC=0xFC): PB=0x%02X\n", (int)pb);
    outportb(ADRPPI+2, 0xfd);  /* stepM OFF (PC0=1) */
    pb = inportb(ADRPPI+1);
    LOG("  STEP_OFF (PC=0xFD): PB=0x%02X\n", (int)pb);
    outportb(ADRPPI+2, 0xfc);  /* restore */

    LOG("\n=== TEST 10 COMPLETE ===\n");
}


/* ================================================================== */
/*                     PHASE 4: BUG HUNT                              */
/* ================================================================== */

/*--- TEST 11: Home Repeatability ---*/
static void test11_home_repeat(void) {
    int i, rc;
    unsigned int steps[10];
    unsigned int mn, mx;
    long sum;

    LOG("\n=== TEST 11: Home Repeatability (10 cycles) ===\n\n");
    hw_init();

    for(i = 0; i < 10; i++) {
        rc = home_z(&steps[i]);
        if(rc) { LOG("  Cycle %d: ABORTED\n", i); return; }
        LOG("  Cycle %d: %u steps\n", i, steps[i]);
        /* Move up 2000 for next cycle */
        rc = move_z(2000, 200);
        if(rc == 1) { LOG("  ABORTED\n"); return; }
        if(rc == 2) { LOG("  SENSOR\n"); continue; }
    }

    mn = 65535u; mx = 0; sum = 0;
    for(i = 0; i < 10; i++) {
        if(steps[i] < mn) mn = steps[i];
        if(steps[i] > mx) mx = steps[i];
        sum += steps[i];
    }
    LOG("\n  Min=%u  Max=%u  Avg=%u  Spread=%u %s\n",
        mn, mx, (unsigned int)(sum/10), mx-mn,
        (mx-mn > 20) ? "*** UNRELIABLE ***" : "OK");

    hw_stop();
    LOG("\n=== TEST 11 COMPLETE ===\n");
}


/*--- TEST 12: Z Step Integrity (Z only) ---*/
static void test12_z_integrity(void) {
    int rc;
    unsigned int home_steps;
    int speeds[] = {100, 200, 500};
    int dists[]  = {1000, 2000, 5000};
    int si, di, rep;

    LOG("\n=== TEST 12: Z Step Integrity (Z only) ===\n\n");
    LOG("  %6s  %5s  %3s  %6s  %6s  %6s  %s\n",
        "K2z", "Steps", "Rep", "Home", "Expect", "Delta", "Status");
    hw_init();

    for(si = 0; si < 3; si++) {
        for(di = 0; di < 3; di++) {
            for(rep = 0; rep < 3; rep++) {
                int delta;
                rc = home_z(&home_steps);
                if(rc) { LOG("ABORTED\n"); return; }

                rc = move_z(dists[di], (unsigned int)speeds[si]);
                if(rc == 1) { LOG("ABORTED\n"); return; }
                if(rc == 2) { LOG("SENSOR\n"); continue; }

                rc = home_z(&home_steps);
                if(rc) { LOG("ABORTED\n"); return; }
                delta = (int)home_steps - dists[di];
                LOG("  %6d  %5d  %3d  %6u  %6d  %+5d  %s\n",
                    speeds[si], dists[di], rep,
                    home_steps, dists[di], delta,
                    (abs(delta) > 10) ? "*** LOSS ***" : "OK");
            }
        }
    }

    hw_stop();
    LOG("\n=== TEST 12 COMPLETE ===\n");
}


/*--- TEST 13: XYZ Step Integrity ---*/
static void test13_xyz_integrity(void) {
    int rc;
    unsigned int home_steps;
    int targets[][3] = {
        {22000, 1000, 5000},
        {20000, 3000, 8000},
        {18000, 5000, 6000},
        {23000,  500, 3000}
    };
    int i;

    LOG("\n=== TEST 13: XYZ Step Integrity ===\n");
    LOG("Home all -> move XYZ -> home all -> check Z delta.\n\n");
    LOG("  %6s %6s %6s  %6s  %6s  %6s  %s\n",
        "X_tgt", "Y_tgt", "Z_tgt", "Z_home", "Expect", "Delta", "Status");
    hw_init();

    for(i = 0; i < 4; i++) {
        int delta;
        unsigned int z_steps;
        long z_loop;

        rc = home_all(1);
        if(rc) { LOG("Home ABORTED\n"); return; }

        rc = move_xyz(targets[i][0], targets[i][1], targets[i][2]);
        if(rc == 1) { LOG("ABORTED\n"); return; }
        if(rc == 2) { LOG("SENSOR\n"); continue; }

        /* Home Z only back to sensor */
        rc = home_z(&home_steps);
        if(rc) { LOG("ABORTED\n"); return; }

        delta = (int)home_steps - (zcur - 200);
        LOG("  %6d %6d %6d  %6u  %6d  %+5d  %s\n",
            targets[i][0], targets[i][1], targets[i][2],
            home_steps, targets[i][2] - 200, delta,
            (abs(delta) > 10) ? "*** LOSS ***" : "OK");
    }

    hw_stop();
    LOG("\n=== TEST 13 COMPLETE ===\n");
}


/*--- TEST 14: FLINT F5→F5 Cycle Replica (THE MAIN TEST) ---*/
static void test14_flint_replica(void) {
    int rc, layer, pt;
    int xbase = 23500 - 500;
    int ybase = 500;
    int zbase = 8580;
    int z_step = 72;
    int num_layers = 9, pts_per_layer = 20;

    LOG("\n=== TEST 14: FLINT F5->F5 Cycle Replica ===\n");
    LOG("Exact FLINT sequence: STEP_ON -> move_sen -> 180pts -> STEP_OFF -> repeat\n");
    LOG("Config: l_period=%d dT=%d step_freq=%d f_const=%d\n\n",
        cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);

    /*** RUN 1 ***/
    LOG("========== RUN 1 ==========\n");
    hw_init();
    outportb(ADRPPI+2, 0xfc);  /* STEP_ON */
    delay(30);

    /* move_sen(0) — NO mode CW reinit (exact FLINT behavior) */
    rc = home_all(0);
    if(rc) { LOG("Home ABORTED\n"); return; }
    LOG("Home OK. xcur=%d ycur=%d zcur=%d\n", xcur, ycur, zcur);

    /* 180 points */
    rc = run_points(xbase, ybase, zbase, z_step, num_layers, pts_per_layer);
    if(rc) { LOG("Run 1 ABORTED\n"); return; }
    LOG("Run 1 done. zcur=%d\n", zcur);

    /* STEP_OFF */
    outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
    ctlw = 0x80; outportb(ADRRG, ctlw);

    /* Log counter state */
    LOG("Counter state (STEP_OFF): K2z=%u dZ=%u K2x=%u\n",
        read_counter(ADRPT0, 2), read_counter(ADRPT1, 2),
        read_counter(ADRPT0, 0));
    LOG("PB=0x%02X ctlw=0x%02X\n\n",
        (int)inportb(ADRPPI+1), (int)ctlw);

    LOG("Pausing 5 seconds (simulates user pressing F5 again)...\n");
    delay(5000);
    if(esc_pressed()) { hw_stop(); LOG("ABORTED\n"); return; }

    /*** RUN 2 ***/
    LOG("\n========== RUN 2 ==========\n");
    /* NOTE: NO hw_init() here — FLINT doesn't reinit between F5 presses */
    outportb(ADRPPI+2, 0xfc);  /* STEP_ON */
    delay(30);
    LOG("Pre-homing: PB=0x%02X\n", (int)inportb(ADRPPI+1));
    LOG("Counters: K2z=%u dZ=%u K2x=%u K2y=%u\n",
        read_counter(ADRPT0, 2), read_counter(ADRPT1, 2),
        read_counter(ADRPT0, 0), read_counter(ADRPT1, 0));

    /* move_sen(0) — NO mode CW reinit (exact FLINT) */
    { unsigned int z_steps; long z_loop;
      rc = instrumented_homing(0, 7, &z_steps, &z_loop);
      if(rc == 1) { LOG("ABORTED\n"); return; }
      if(rc == 2) LOG("*** TIMEOUT ***\n");
      LOG("Run 2 home: Z=%u steps, loop=%ld\n", z_steps, z_loop);
    }

    /* 180 points (shifted Z) */
    zbase = 8256;
    z_step = 36;
    rc = run_points(xbase, ybase, zbase, z_step, num_layers, pts_per_layer);
    if(rc) { LOG("Run 2 ABORTED\n"); return; }
    LOG("Run 2 done. zcur=%d\n", zcur);

    /* Final Z home for verification */
    { unsigned int final_home;
      int delta;
      rc = home_z(&final_home);
      if(rc) { LOG("Final home ABORTED\n"); return; }
      delta = (int)final_home - (zcur - 200);
      LOG("Final Z home: %u steps (expected ~%d, delta=%+d) %s\n",
          final_home, zcur - 200, delta,
          (abs(delta) > 10) ? "*** STEP LOSS ***" : "OK");
    }

    outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
    hw_stop();
    LOG("\n=== TEST 14 COMPLETE ===\n");
}


/*--- TEST 15: Homing Isolation (which axis interferes?) ---*/
static void test15_homing_isolation(void) {
    int combo, rep, rc;
    unsigned int steps[4][5];
    int axes_list[] = {4, 5, 6, 7};  /* Z, Z+X, Z+Y, Z+X+Y */
    const char *names[] = {"Z only", "Z+X", "Z+Y", "Z+X+Y"};
    unsigned int mn, mx;
    long sum;

    LOG("\n=== TEST 15: Homing Isolation ===\n");
    LOG("5 reps x 4 combos after identical process() run.\n\n");

    for(combo = 0; combo < 4; combo++) {
        LOG("--- %s ---\n", names[combo]);
        for(rep = 0; rep < 5; rep++) {
            unsigned int z_steps; long z_loop;

            /* Full init + home + process */
            hw_init();
            rc = home_all(1);
            if(rc) { LOG("ABORTED\n"); return; }
            rc = move_xyz(20000, 5000, 8000);
            if(rc) { LOG("ABORTED\n"); return; }

            /* Instrumented homing with selected axes */
            rc = instrumented_homing(0, axes_list[combo], &z_steps, &z_loop);
            if(rc == 1) { LOG("ABORTED\n"); return; }
            if(rc == 2) LOG("  TIMEOUT\n");
            steps[combo][rep] = z_steps;
            LOG("  rep %d: %u steps (loop=%ld)\n", rep, z_steps, z_loop);
        }
    }

    /* Summary */
    LOG("\n%-10s  %6s  %6s  %6s  %6s\n", "Combo", "Min", "Max", "Avg", "Spread");
    for(combo = 0; combo < 4; combo++) {
        mn = 65535u; mx = 0; sum = 0;
        for(rep = 0; rep < 5; rep++) {
            if(steps[combo][rep] < mn) mn = steps[combo][rep];
            if(steps[combo][rep] > mx) mx = steps[combo][rep];
            sum += steps[combo][rep];
        }
        LOG("%-10s  %6u  %6u  %6u  %6u %s\n", names[combo],
            mn, mx, (unsigned int)(sum/5), mx-mn,
            (mx-mn > 50) ? "*** PROBLEM ***" : "OK");
    }

    hw_stop();
    LOG("\n=== TEST 15 COMPLETE ===\n");
}


/*--- TEST 16: Sensor Noise During XY Motion ---*/
static void test16_sensor_noise(void) {
    int rc;
    long loops;
    int noise_events = 0;

    LOG("\n=== TEST 16: Sensor Noise During XY Motion ===\n");
    LOG("Moving XY while polling Z sensors (PB4/PB5).\n\n");

    hw_init();
    rc = home_all(1);
    if(rc) { LOG("ABORTED\n"); return; }

    /* Move to a position away from Z sensors */
    rc = move_xyz(20000, 5000, 8000);
    if(rc) { LOG("ABORTED\n"); return; }

    /* Start XY movement without Z */
    outportb(ADRPT0+3, 0x34); outportb(ADRPT0+3, 0x78);
    outportb(ADRPT1+3, 0x34); outportb(ADRPT1+3, 0x78);
    outportb(ADRPT0,   0x64); outportb(ADRPT0,   0x00);  /* K2x=100 */
    outportb(ADRPT0+1, 0x00); outportb(ADRPT0+1, 0x40);  /* dX=16384 */
    outportb(ADRPT1,   0x64); outportb(ADRPT1,   0x00);  /* K2y=100 */
    outportb(ADRPT1+1, 0x00); outportb(ADRPT1+1, 0x40);  /* dY=16384 */
    ctlw = (XON|YON|XUP) & YDOWN & ZOFF & OSCON;
    outportb(ADRRG, ctlw);

    /* Poll Z sensors while XY moves */
    loops = 0;
    noise_events = 0;
    while(loops < 200000L) {
        unsigned char pb = inportb(ADRPPI+1);
        if((pb & 0x30) != 0x30) {
            noise_events++;
            if(noise_events <= 20)
                LOG("  Noise at loop %ld: PB=0x%02X (Z-=%d Z+=%d)\n",
                    loops, (int)pb, (pb>>4)&1, (pb>>5)&1);
        }
        /* Check if XY done (PB7) */
        if(inportb(ADRPPI+1) & 0x80) break;
        if(esc_pressed()) { hw_stop(); LOG("ABORTED\n"); return; }
        loops++;
    }

    ctlw = ctlw & XOFF & YOFF;
    outportb(ADRRG, ctlw);

    LOG("  Total polls: %ld, noise events: %d\n", loops, noise_events);
    if(noise_events > 0)
        LOG("  *** Z SENSORS SHOW NOISE DURING XY MOTION ***\n"
            "  This could cause false Z-stop in move_sen() phase C!\n");
    else
        LOG("  No Z sensor noise detected during XY motion.\n");

    hw_stop();
    LOG("\n=== TEST 16 COMPLETE ===\n");
}


/*--- TEST 17: K2z Timing Probe (flip-flop test) ---*/
static void test17_k2z_timing(void) {
    int rc;
    long t_ref, t_dirty;

    LOG("\n=== TEST 17: K2z Timing Probe ===\n");
    LOG("Measures actual K2z counter period via timing.\n");
    LOG("If 8253 flip-flop corrupted: K2z=100 becomes 25600 => 256x slower.\n\n");

    /* Reference: fresh hw_init, clean flip-flop */
    LOG("--- A: Reference (after hw_init) ---\n");
    hw_init();
    t_ref = measure_k2z_timing(100);
    if(t_ref == -1) { LOG("  PB6 stuck. Cannot test.\n"); return; }
    if(t_ref == -2) { LOG("  TIMEOUT. OSC/hardware issue.\n"); return; }
    LOG("  K2z=100 reference: %ld loops (~%ld us)\n\n",
        t_ref, t_ref * 629 / 1000);

    /* Dirty: after 180-point process */
    LOG("--- B: After 180-point process ---\n");
    hw_init();
    rc = home_all(1);
    if(rc) { LOG("Home ABORTED\n"); return; }
    outportb(ADRPPI+2, 0xfc); delay(30);  /* STEP_ON */
    rc = run_points(23000, 500, 8580, 72, 9, 20);
    if(rc) { LOG("Process ABORTED\n"); return; }
    outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
    ctlw = 0x80; outportb(ADRRG, ctlw);

    LOG("  Process done. zcur=%d\n", zcur);
    LOG("  Measuring K2z=100 WITHOUT mode CW reinit...\n");
    t_dirty = measure_k2z_timing(100);
    if(t_dirty == -1) {
        LOG("  PB6 stuck after process.\n");
    } else if(t_dirty == -2) {
        LOG("  *** TIMEOUT: K2z period extremely long ***\n");
        LOG("  *** FLIP-FLOP LIKELY CORRUPTED ***\n");
    } else {
        long ratio = (t_ref > 0) ? t_dirty / t_ref : 0;
        LOG("  K2z=100 post-process: %ld loops (~%ld us)\n",
            t_dirty, t_dirty * 629 / 1000);
        LOG("  Ratio vs reference: %ld (expect ~1)\n", ratio);
        if(ratio > 10)
            LOG("  *** FLIP-FLOP CORRUPTED (actual K2z ~ %ld) ***\n",
                100L * ratio);
        else
            LOG("  Flip-flop OK.\n");
    }

    /* C: Same but WITH mode CW reinit */
    LOG("\n--- C: After process, WITH mode CW reinit ---\n");
    outportb(ADRPT0+3, 0xb4);  /* K2z mode CW resets flip-flop */
    { long t_fixed = measure_k2z_timing(100);
      if(t_fixed > 0)
          LOG("  K2z=100 with reinit: %ld loops (ratio=%ld). %s\n",
              t_fixed, t_fixed/t_ref,
              (t_fixed/t_ref < 3) ? "OK (fix works)" : "*** still bad ***");
    }

    hw_stop();
    LOG("\n=== TEST 17 COMPLETE ===\n");
}


/*--- TEST 18: Gravity Drift ---*/
static void test18_gravity_drift(void) {
    int rc, w;
    unsigned int home_steps;
    int z_ref = 6000;
    int waits[] = {0, 1, 5, 10, 30};
    unsigned int baseline = 0;

    LOG("\n=== TEST 18: Gravity Drift ===\n");
    LOG("Home -> up %d -> STEP_OFF -> wait -> STEP_ON -> home -> delta\n\n", z_ref);
    LOG("  %6s  %6s  %6s  %s\n", "Wait_s", "Home", "Delta", "Status");

    hw_init();

    for(w = 0; w < 5; w++) {
        int delta;
        rc = home_z(&home_steps);
        if(rc) { LOG("ABORTED\n"); return; }

        rc = move_z(z_ref, 200);
        if(rc == 1) { LOG("ABORTED\n"); return; }
        if(rc == 2) { LOG("SENSOR\n"); continue; }

        if(waits[w] > 0) {
            outportb(ADRPPI+2, 0xfd);  /* STEP_OFF */
            { int s;
              for(s = 0; s < waits[w]; s++) {
                  delay(1000);
                  if(esc_pressed()) { hw_stop(); return; }
              }
            }
            outportb(ADRPPI+2, 0xfc);  /* STEP_ON */
            delay(50);
        }

        rc = home_z(&home_steps);
        if(rc) { LOG("ABORTED\n"); return; }

        if(w == 0) {
            baseline = home_steps;
            LOG("  %5ds  %6u  %6s  baseline\n", waits[w], home_steps, "-");
        } else {
            delta = (int)home_steps - (int)baseline;
            LOG("  %5ds  %6u  %+5d  %s\n", waits[w], home_steps, delta,
                (abs(delta) > 10) ? "*** DRIFT ***" : "OK");
        }
    }

    outportb(ADRPPI+2, 0xfc);
    hw_stop();
    LOG("\n=== TEST 18 COMPLETE ===\n");
}


/* ================================================================== */
/*                     AUTO-DIAGNOSTIC                                */
/* ================================================================== */

static void auto_diagnostic(void) {
    LOG("\n");
    LOG("###########################################################\n");
    LOG("#         Z_DIAG v2 AUTO-DIAGNOSTIC                       #\n");
    LOG("###########################################################\n");
    LOG("Press ESC at any time to abort.\n\n");

    /* === PHASE 1: Environment === */
    LOG("============ PHASE 1: Environment ============\n");
    test01_environment();
    if(esc_pressed()) goto aborted;
    test02_cpu_timing();
    if(esc_pressed()) goto aborted;

    /* === PHASE 2: Hardware identification === */
    LOG("\n============ PHASE 2: Hardware Identification ============\n");
    test03_port_scan();
    if(esc_pressed()) goto aborted;
    test04_ppi_verify();
    if(esc_pressed()) goto aborted;
    test05_timer_chip_id();
    if(esc_pressed()) goto aborted;

    /* === PHASE 3: Hardware behavior === */
    LOG("\n============ PHASE 3: Hardware Behavior ============\n");
    test06_osc_frequency();
    if(esc_pressed()) goto aborted;
    test07_gate_map();
    if(esc_pressed()) goto aborted;
    test08_sensor_snapshot();
    if(esc_pressed()) goto aborted;
    test09_pb_nature();
    if(esc_pressed()) goto aborted;
    test10_sensor_reset();
    if(esc_pressed()) goto aborted;

    LOG("\n--- Phase 3 complete. Starting Phase 4 (motors)... ---\n");

    /* === PHASE 4A: Basic mechanics === */
    LOG("\n============ PHASE 4A: Basic Mechanics ============\n");
    test11_home_repeat();
    if(esc_pressed()) goto aborted;
    test12_z_integrity();
    if(esc_pressed()) goto aborted;
    test13_xyz_integrity();
    if(esc_pressed()) goto aborted;

    /* === PHASE 4B: Bug reproduction === */
    LOG("\n============ PHASE 4B: Bug Reproduction ============\n");
    test14_flint_replica();
    if(esc_pressed()) goto aborted;

    /* === PHASE 4C: Bug isolation === */
    LOG("\n============ PHASE 4C: Bug Isolation ============\n");
    test15_homing_isolation();
    if(esc_pressed()) goto aborted;
    test16_sensor_noise();
    if(esc_pressed()) goto aborted;
    test17_k2z_timing();
    if(esc_pressed()) goto aborted;
    test18_gravity_drift();

    /* === Done === */
    LOG("\n###########################################################\n");
    LOG("#         AUTO-DIAGNOSTIC COMPLETE                        #\n");
    LOG("###########################################################\n");
    LOG("Config: l_period=%d dT=%d step_freq=%d f_const=%d\n",
        cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
    LOG("Full results in Z_DIAG.LOG\n");
    return;

aborted:
    LOG("\n*** AUTO-DIAGNOSTIC ABORTED (ESC) ***\n");
    hw_stop();
}


/* ================================================================== */
/*                          MAIN MENU                                 */
/* ================================================================== */

int main(void) {
    int choice;

    logf = fopen("Z_DIAG.LOG", "w");
    if(logf) fprintf(logf, "=== Z_DIAG v2 Log Start ===\n");

    printf("=== Z_DIAG v2: FLINT Hardware Diagnostic ===\n");
    printf("Detecting hardware...\n");
    if(!hw_detect()) {
        LOG("*** WARNING: ISA card NOT DETECTED at 0x%03X ***\n", ADRPT0);
        LOG("K1 readback failed (got %d).\n\n", (int)inportb(ADRPPI));
    } else {
        LOG("ISA card detected at 0x%03X. K1=%d\n\n", ADRPT0, (int)inportb(ADRPPI));
    }
    hw_init();
    LOG("Sensors: 0x%02X\n\n", (int)read_sensors());

    while(1) {
        printf("\n");
        printf("  ENTER >>> RUN ALL (auto-diagnostic) <<<\n\n");
        printf("  Phase 1: Environment\n");
        printf("    1. Environment report\n");
        printf("    2. CPU timing\n");
        printf("  Phase 2: Hardware ID\n");
        printf("    3. Port scan\n");
        printf("    4. PPI verify\n");
        printf("    5. Timer chip ID (8253/8254)\n");
        printf("  Phase 3: Hardware behavior\n");
        printf("    6. Oscillator frequency\n");
        printf("    7. Counter GATE map\n");
        printf("    8. Sensor snapshot\n");
        printf("    9. PB6/PB7 signal nature\n");
        printf("    A. Sensor reset behavior\n");
        printf("  Phase 4: Bug hunt\n");
        printf("    B. Home repeatability (10x)\n");
        printf("    C. Z step integrity (Z only)\n");
        printf("    D. XYZ step integrity\n");
        printf("    E. FLINT F5->F5 replica (MAIN TEST)\n");
        printf("    F. Homing isolation (Z/ZX/ZY/ZXY)\n");
        printf("    G. Sensor noise during XY\n");
        printf("    H. K2z timing probe (flip-flop)\n");
        printf("    I. Gravity drift\n\n");
        printf("  S. Config (lp=%d dT=%d sf=%d fc=%d)\n",
               cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
        printf("  Q/ESC. Exit\n");
        printf("\nChoice: ");

        choice = bioskey(0) & 0xff;
        printf("%c\n", choice);

        switch(choice) {
            case 13: case 'r': case 'R': auto_diagnostic(); break;
            case '1': test01_environment(); break;
            case '2': test02_cpu_timing(); break;
            case '3': test03_port_scan(); break;
            case '4': test04_ppi_verify(); break;
            case '5': test05_timer_chip_id(); break;
            case '6': test06_osc_frequency(); break;
            case '7': test07_gate_map(); break;
            case '8': test08_sensor_snapshot(); break;
            case '9': test09_pb_nature(); break;
            case 'a': case 'A': test10_sensor_reset(); break;
            case 'b': case 'B': test11_home_repeat(); break;
            case 'c': case 'C': test12_z_integrity(); break;
            case 'd': case 'D': test13_xyz_integrity(); break;
            case 'e': case 'E': test14_flint_replica(); break;
            case 'f': case 'F': test15_homing_isolation(); break;
            case 'g': case 'G': test16_sensor_noise(); break;
            case 'h': case 'H': test17_k2z_timing(); break;
            case 'i': case 'I': test18_gravity_drift(); break;
            case 's': case 'S':
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
                  if(buf[0]) { v = atoi(buf); cfg_f_const = (v!=0)?1:0; }
                }
                LOG("Config: l_period=%d dT=%d step_freq=%d f_const=%d\n",
                    cfg_l_period, cfg_dT, cfg_step_freq, cfg_f_const);
                break;
            case 'q': case 'Q': case 27: goto done;
            default: printf("Invalid choice\n"); break;
        }
    }

done:
    hw_stop();
    if(logf) {
        fprintf(logf, "=== Z_DIAG v2 Log End ===\n");
        fclose(logf);
    }
    printf("\nDone. Results in Z_DIAG.LOG\n");
    return 0;
}
