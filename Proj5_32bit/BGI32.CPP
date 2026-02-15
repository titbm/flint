/***********************************************************************
    BGI32.CPP
    BGI-compatible graphics layer for Open Watcom C++ / DOS4GW
    VGA Mode 12h: 640x480, 16 colors, 4 bit-planes

    FLINT+ v2.61 port
***********************************************************************/
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <i86.h>
#include <dos.h>
#include "bgi32.h"

/*--- VGA hardware constants ---*/
#define VGA_BASE        0xA0000     /* Video memory linear address */
#define VGA_WIDTH       640
#define VGA_HEIGHT      480
#define VGA_BPL         80          /* Bytes per line (640/8) */

#define VGA_SEQ_INDEX   0x3C4
#define VGA_SEQ_DATA    0x3C5
#define VGA_GC_INDEX    0x3CE
#define VGA_GC_DATA     0x3CF

/* Sequencer registers */
#define SEQ_MAP_MASK    0x02        /* Map Mask Register */

/* Graphics controller registers */
#define GC_SET_RESET    0x00
#define GC_ENABLE_SR    0x01
#define GC_COLOR_CMP    0x02
#define GC_DATA_ROT     0x03
#define GC_READ_MAP     0x04        /* Read Map Select */
#define GC_MODE         0x05        /* Graphics Mode Register */
#define GC_MISC         0x06
#define GC_COLOR_NOCARE 0x07
#define GC_BIT_MASK     0x08        /* Bit Mask Register */

/*--- Module state ---*/
static unsigned char *vga_mem = (unsigned char *)VGA_BASE;
static int _fg_color   = WHITE;
static int _fill_color  = BLACK;
static int _fill_style  = SOLID_FILL;
static char _fill_pattern[8] = {
    (char)0xFF,(char)0xFF,(char)0xFF,(char)0xFF,
    (char)0xFF,(char)0xFF,(char)0xFF,(char)0xFF
};
static int _line_style  = SOLID_LINE;
static int _graph_result = grOk;

/* Built-in 8x8 font from VGA BIOS ROM (will be loaded at init) */
static unsigned char _font8x8[256][8];
static int _font_loaded = 0;

/* BGI driver stub */
void *EGAVGA_driver_far = (void *)0;


/*=== Internal VGA helpers =============================================*/

/* Set VGA write mode 0, with map mask for selected planes */
static inline void vga_set_write_planes(unsigned char mask) {
    outp(VGA_SEQ_INDEX, SEQ_MAP_MASK);
    outp(VGA_SEQ_DATA, mask);
}

/* Set the bit mask register */
static inline void vga_set_bit_mask(unsigned char mask) {
    outp(VGA_GC_INDEX, GC_BIT_MASK);
    outp(VGA_GC_DATA, mask);
}

/* Set read map select (0-3) */
static inline void vga_set_read_plane(unsigned char plane) {
    outp(VGA_GC_INDEX, GC_READ_MAP);
    outp(VGA_GC_DATA, plane);
}

/* Set VGA to write mode 0 (default) */
static void vga_write_mode_0(void) {
    outp(VGA_GC_INDEX, GC_MODE);
    unsigned char mode = inp(VGA_GC_DATA);
    outp(VGA_GC_INDEX, GC_MODE);
    outp(VGA_GC_DATA, mode & 0xFC);  /* clear bits 0-1 = mode 0 */
}

/* Set VGA to write mode 2 */
static void vga_write_mode_2(void) {
    outp(VGA_GC_INDEX, GC_MODE);
    unsigned char mode = inp(VGA_GC_DATA);
    outp(VGA_GC_INDEX, GC_MODE);
    outp(VGA_GC_DATA, (mode & 0xFC) | 0x02);
}

/* Reset GC registers to safe defaults after drawing */
static void vga_reset_gc(void) {
    vga_set_bit_mask(0xFF);
    vga_set_write_planes(0x0F);
    outp(VGA_GC_INDEX, GC_DATA_ROT);
}

/* Reverse bit order of a byte (bit0<->bit7, bit1<->bit6, etc.) */
static inline unsigned char reverse8(unsigned char b) {
    b = ((b & 0xF0) >> 4) | ((b & 0x0F) << 4);
    b = ((b & 0xCC) >> 2) | ((b & 0x33) << 2);
    b = ((b & 0xAA) >> 1) | ((b & 0x55) << 1);
    return b;
}

/* Fast horizontal line using write mode 2 (byte-level) */
static void hline_fast(int x1, int x2, int y, int color) {
    if(y < 0 || y >= VGA_HEIGHT) return;
    if(x1 > x2) { int t = x1; x1 = x2; x2 = t; }
    if(x1 < 0) x1 = 0;
    if(x2 >= VGA_WIDTH) x2 = VGA_WIDTH - 1;
    if(x1 > x2) return;

    unsigned long base = (unsigned long)y * VGA_BPL;
    int bx1 = x1 >> 3, bx2 = x2 >> 3;
    unsigned char lm = 0xFF >> (x1 & 7);
    unsigned char rm = (unsigned char)(0xFF << (7 - (x2 & 7)));

    vga_write_mode_2();
    if(bx1 == bx2) {
        unsigned char m = lm & rm;
        vga_set_bit_mask(m);
        volatile unsigned char d = vga_mem[base + bx1]; (void)d;
        vga_mem[base + bx1] = (unsigned char)color;
    } else {
        vga_set_bit_mask(lm);
        volatile unsigned char d = vga_mem[base + bx1]; (void)d;
        vga_mem[base + bx1] = (unsigned char)color;
        if(bx2 > bx1 + 1) {
            vga_set_bit_mask(0xFF);
            for(int bx = bx1 + 1; bx < bx2; bx++) {
                volatile unsigned char d2 = vga_mem[base + bx]; (void)d2;
                vga_mem[base + bx] = (unsigned char)color;
            }
        }
        vga_set_bit_mask(rm);
        volatile unsigned char d3 = vga_mem[base + bx2]; (void)d3;
        vga_mem[base + bx2] = (unsigned char)color;
    }
    vga_write_mode_0();
    vga_set_bit_mask(0xFF);
}

/* Fast vertical line using write mode 2 (constant bit mask) */
static void vline_fast(int x, int y1, int y2, int color) {
    if(x < 0 || x >= VGA_WIDTH) return;
    if(y1 > y2) { int t = y1; y1 = y2; y2 = t; }
    if(y1 < 0) y1 = 0;
    if(y2 >= VGA_HEIGHT) y2 = VGA_HEIGHT - 1;
    if(y1 > y2) return;

    int bx = x >> 3;
    unsigned char mask = 1 << (7 - (x & 7));
    vga_write_mode_2();
    vga_set_bit_mask(mask);
    for(int y = y1; y <= y2; y++) {
        unsigned long off = (unsigned long)y * VGA_BPL + bx;
        volatile unsigned char d = vga_mem[off]; (void)d;
        vga_mem[off] = (unsigned char)color;
    }
    vga_write_mode_0();
    vga_set_bit_mask(0xFF);
    outp(VGA_GC_DATA, 0x00);
    outp(VGA_GC_INDEX, GC_ENABLE_SR);
    outp(VGA_GC_DATA, 0x00);
    outp(VGA_GC_INDEX, GC_SET_RESET);
    outp(VGA_GC_DATA, 0x00);
}


/*--- Load 8x8 font ---*/
static void load_vga_font(void) {
    /* Built-in 8x8 CP437 font for printable ASCII (32-127).
     * This avoids relying on BIOS INT 10h in protected mode. */
    static const unsigned char basic_font[][8] = {
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, /* 32 space */
        {0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00}, /* 33 ! */
        {0x36,0x36,0x14,0x00,0x00,0x00,0x00,0x00}, /* 34 " */
        {0x36,0x36,0x7F,0x36,0x7F,0x36,0x36,0x00}, /* 35 # */
        {0x0C,0x3E,0x03,0x1E,0x30,0x1F,0x0C,0x00}, /* 36 $ */
        {0x00,0x63,0x33,0x18,0x0C,0x66,0x63,0x00}, /* 37 % */
        {0x1C,0x36,0x1C,0x6E,0x3B,0x33,0x6E,0x00}, /* 38 & */
        {0x06,0x06,0x03,0x00,0x00,0x00,0x00,0x00}, /* 39 ' */
        {0x18,0x0C,0x06,0x06,0x06,0x0C,0x18,0x00}, /* 40 ( */
        {0x06,0x0C,0x18,0x18,0x18,0x0C,0x06,0x00}, /* 41 ) */
        {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, /* 42 * */
        {0x00,0x0C,0x0C,0x3F,0x0C,0x0C,0x00,0x00}, /* 43 + */
        {0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x06}, /* 44 , */
        {0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00}, /* 45 - */
        {0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00}, /* 46 . */
        {0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x00}, /* 47 / */
        {0x3E,0x63,0x73,0x7B,0x6F,0x67,0x3E,0x00}, /* 48 0 */
        {0x0C,0x0E,0x0C,0x0C,0x0C,0x0C,0x3F,0x00}, /* 49 1 */
        {0x1E,0x33,0x30,0x1C,0x06,0x33,0x3F,0x00}, /* 50 2 */
        {0x1E,0x33,0x30,0x1C,0x30,0x33,0x1E,0x00}, /* 51 3 */
        {0x38,0x3C,0x36,0x33,0x7F,0x30,0x78,0x00}, /* 52 4 */
        {0x3F,0x03,0x1F,0x30,0x30,0x33,0x1E,0x00}, /* 53 5 */
        {0x1C,0x06,0x03,0x1F,0x33,0x33,0x1E,0x00}, /* 54 6 */
        {0x3F,0x33,0x30,0x18,0x0C,0x0C,0x0C,0x00}, /* 55 7 */
        {0x1E,0x33,0x33,0x1E,0x33,0x33,0x1E,0x00}, /* 56 8 */
        {0x1E,0x33,0x33,0x3E,0x30,0x18,0x0E,0x00}, /* 57 9 */
        {0x00,0x0C,0x0C,0x00,0x00,0x0C,0x0C,0x00}, /* 58 : */
        {0x00,0x0C,0x0C,0x00,0x00,0x0C,0x0C,0x06}, /* 59 ; */
        {0x18,0x0C,0x06,0x03,0x06,0x0C,0x18,0x00}, /* 60 < */
        {0x00,0x00,0x3F,0x00,0x00,0x3F,0x00,0x00}, /* 61 = */
        {0x06,0x0C,0x18,0x30,0x18,0x0C,0x06,0x00}, /* 62 > */
        {0x1E,0x33,0x30,0x18,0x0C,0x00,0x0C,0x00}, /* 63 ? */
        {0x3E,0x63,0x7B,0x7B,0x7B,0x03,0x1E,0x00}, /* 64 @ */
        {0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0x00}, /* 65 A */
        {0x3F,0x66,0x66,0x3E,0x66,0x66,0x3F,0x00}, /* 66 B */
        {0x3C,0x66,0x03,0x03,0x03,0x66,0x3C,0x00}, /* 67 C */
        {0x1F,0x36,0x66,0x66,0x66,0x36,0x1F,0x00}, /* 68 D */
        {0x7F,0x46,0x16,0x1E,0x16,0x46,0x7F,0x00}, /* 69 E */
        {0x7F,0x46,0x16,0x1E,0x16,0x06,0x0F,0x00}, /* 70 F */
        {0x3C,0x66,0x03,0x03,0x73,0x66,0x7C,0x00}, /* 71 G */
        {0x33,0x33,0x33,0x3F,0x33,0x33,0x33,0x00}, /* 72 H */
        {0x1E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00}, /* 73 I */
        {0x78,0x30,0x30,0x30,0x33,0x33,0x1E,0x00}, /* 74 J */
        {0x67,0x66,0x36,0x1E,0x36,0x66,0x67,0x00}, /* 75 K */
        {0x0F,0x06,0x06,0x06,0x46,0x66,0x7F,0x00}, /* 76 L */
        {0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00}, /* 77 M */
        {0x63,0x67,0x6F,0x7B,0x73,0x63,0x63,0x00}, /* 78 N */
        {0x1C,0x36,0x63,0x63,0x63,0x36,0x1C,0x00}, /* 79 O */
        {0x3F,0x66,0x66,0x3E,0x06,0x06,0x0F,0x00}, /* 80 P */
        {0x1E,0x33,0x33,0x33,0x3B,0x1E,0x38,0x00}, /* 81 Q */
        {0x3F,0x66,0x66,0x3E,0x36,0x66,0x67,0x00}, /* 82 R */
        {0x1E,0x33,0x07,0x0E,0x38,0x33,0x1E,0x00}, /* 83 S */
        {0x3F,0x2D,0x0C,0x0C,0x0C,0x0C,0x1E,0x00}, /* 84 T */
        {0x33,0x33,0x33,0x33,0x33,0x33,0x3F,0x00}, /* 85 U */
        {0x33,0x33,0x33,0x33,0x33,0x1E,0x0C,0x00}, /* 86 V */
        {0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00}, /* 87 W */
        {0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00}, /* 88 X */
        {0x33,0x33,0x33,0x1E,0x0C,0x0C,0x1E,0x00}, /* 89 Y */
        {0x7F,0x63,0x31,0x18,0x4C,0x66,0x7F,0x00}, /* 90 Z */
        {0x1E,0x06,0x06,0x06,0x06,0x06,0x1E,0x00}, /* 91 [ */
        {0x03,0x06,0x0C,0x18,0x30,0x60,0x40,0x00}, /* 92 \ */
        {0x1E,0x18,0x18,0x18,0x18,0x18,0x1E,0x00}, /* 93 ] */
        {0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00}, /* 94 ^ */
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF}, /* 95 _ */
        {0x0C,0x0C,0x18,0x00,0x00,0x00,0x00,0x00}, /* 96 ` */
        {0x00,0x00,0x1E,0x30,0x3E,0x33,0x6E,0x00}, /* 97 a */
        {0x07,0x06,0x06,0x3E,0x66,0x66,0x3B,0x00}, /* 98 b */
        {0x00,0x00,0x1E,0x33,0x03,0x33,0x1E,0x00}, /* 99 c */
        {0x38,0x30,0x30,0x3E,0x33,0x33,0x6E,0x00}, /*100 d */
        {0x00,0x00,0x1E,0x33,0x3F,0x03,0x1E,0x00}, /*101 e */
        {0x1C,0x36,0x06,0x0F,0x06,0x06,0x0F,0x00}, /*102 f */
        {0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x1F}, /*103 g */
        {0x07,0x06,0x36,0x6E,0x66,0x66,0x67,0x00}, /*104 h */
        {0x0C,0x00,0x0E,0x0C,0x0C,0x0C,0x1E,0x00}, /*105 i */
        {0x30,0x00,0x30,0x30,0x30,0x33,0x33,0x1E}, /*106 j */
        {0x07,0x06,0x66,0x36,0x1E,0x36,0x67,0x00}, /*107 k */
        {0x0E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00}, /*108 l */
        {0x00,0x00,0x33,0x7F,0x7F,0x6B,0x63,0x00}, /*109 m */
        {0x00,0x00,0x1F,0x33,0x33,0x33,0x33,0x00}, /*110 n */
        {0x00,0x00,0x1E,0x33,0x33,0x33,0x1E,0x00}, /*111 o */
        {0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x0F}, /*112 p */
        {0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x78}, /*113 q */
        {0x00,0x00,0x3B,0x6E,0x66,0x06,0x0F,0x00}, /*114 r */
        {0x00,0x00,0x3E,0x03,0x1E,0x30,0x1F,0x00}, /*115 s */
        {0x08,0x0C,0x3E,0x0C,0x0C,0x2C,0x18,0x00}, /*116 t */
        {0x00,0x00,0x33,0x33,0x33,0x33,0x6E,0x00}, /*117 u */
        {0x00,0x00,0x33,0x33,0x33,0x1E,0x0C,0x00}, /*118 v */
        {0x00,0x00,0x63,0x6B,0x7F,0x7F,0x36,0x00}, /*119 w */
        {0x00,0x00,0x63,0x36,0x1C,0x36,0x63,0x00}, /*120 x */
        {0x00,0x00,0x33,0x33,0x33,0x3E,0x30,0x1F}, /*121 y */
        {0x00,0x00,0x3F,0x19,0x0C,0x26,0x3F,0x00}, /*122 z */
        {0x38,0x0C,0x0C,0x07,0x0C,0x0C,0x38,0x00}, /*123 { */
        {0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00}, /*124 | */
        {0x07,0x0C,0x0C,0x38,0x0C,0x0C,0x07,0x00}, /*125 } */
        {0x6E,0x3B,0x00,0x00,0x00,0x00,0x00,0x00}, /*126 ~ */
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, /*127 DEL */
    };

    memset(_font8x8, 0, sizeof(_font8x8));
    for(int i = 0; i < 96; i++) {
        memcpy(_font8x8[32 + i], basic_font[i], 8);
    }
    _font_loaded = 1;
}


/*=== Public BGI-compatible functions ==================================*/

int registerfarbgidriver(void *driver) {
    (void)driver;
    return 0;  /* Always succeeds - no BGI driver needed */
}


void initgraph(int *driver, int *mode, const char *path) {
    (void)driver; (void)mode; (void)path;

    /* Set VGA mode 12h (640x480, 16 colors) via INT 10h */
    union REGS r;
    r.w.ax = 0x0012;
    int386(0x10, &r, &r);

    /* Initialize VGA registers to known state */
    vga_write_mode_0();
    vga_reset_gc();

    /* Load VGA ROM font */
    load_vga_font();

    _fg_color   = WHITE;
    _fill_color  = BLACK;
    _fill_style  = SOLID_FILL;
    _graph_result = grOk;

    memset(_fill_pattern, 0xFF, 8);
}


void closegraph(void) {
    /* Restore text mode 03h */
    union REGS r;
    r.w.ax = 0x0003;
    int386(0x10, &r, &r);
}


int graphresult(void) {
    int r = _graph_result;
    _graph_result = grOk;
    return r;
}


/*--- Pixel operations ---*/

void putpixel(int x, int y, int color) {
    unsigned long offset;
    unsigned char bit_pos, bit_mask;

    if(x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) return;

    offset = (unsigned long)y * VGA_BPL + (x >> 3);
    bit_pos = 7 - (x & 7);
    bit_mask = 1 << bit_pos;

    /* Use write mode 2: write color value, bit mask selects pixel */
    vga_write_mode_2();
    vga_set_bit_mask(bit_mask);

    /* Read-modify-write: read to latch existing data */
    volatile unsigned char dummy = vga_mem[offset];
    (void)dummy;

    /* Write the color (all 4 planes updated according to color value) */
    vga_mem[offset] = (unsigned char)color;

    /* Restore defaults */
    vga_write_mode_0();
    vga_set_bit_mask(0xFF);
}


int getpixel(int x, int y) {
    unsigned long offset;
    unsigned char bit_pos, bit_mask;
    int color = 0;

    if(x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) return 0;

    offset = (unsigned long)y * VGA_BPL + (x >> 3);
    bit_pos = 7 - (x & 7);
    bit_mask = 1 << bit_pos;

    for(int plane = 0; plane < 4; plane++) {
        vga_set_read_plane(plane);
        if(vga_mem[offset] & bit_mask)
            color |= (1 << plane);
    }
    return color;
}


/*--- Line drawing (Bresenham + fast h/v paths) ---*/

void line(int x1, int y1, int x2, int y2) {
    /* Fast paths for horizontal and vertical lines */
    if(y1 == y2) { hline_fast(x1, x2, y1, _fg_color); return; }
    if(x1 == x2) { vline_fast(x1, y1, y2, _fg_color); return; }

    /* General Bresenham */
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while(1) {
        putpixel(x1, y1, _fg_color);
        if(x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx)  { err += dx; y1 += sy; }
    }
}


void rectangle(int x1, int y1, int x2, int y2) {
    hline_fast(x1, x2, y1, _fg_color);  /* top */
    hline_fast(x1, x2, y2, _fg_color);  /* bottom */
    vline_fast(x1, y1, y2, _fg_color);  /* left */
    vline_fast(x2, y1, y2, _fg_color);  /* right */
}


/*--- Filled rectangle (bar) - optimized byte-level VGA ---*/

void bar(int x1, int y1, int x2, int y2) {
    int tmp;

    /* Normalize coordinates */
    if(x1 > x2) { tmp = x1; x1 = x2; x2 = tmp; }
    if(y1 > y2) { tmp = y1; y1 = y2; y2 = tmp; }

    /* Clip */
    if(x1 < 0) x1 = 0;
    if(y1 < 0) y1 = 0;
    if(x2 >= VGA_WIDTH) x2 = VGA_WIDTH - 1;
    if(y2 >= VGA_HEIGHT) y2 = VGA_HEIGHT - 1;
    if(x1 > x2 || y1 > y2) return;

    int byte_x1 = x1 >> 3;
    int byte_x2 = x2 >> 3;
    unsigned char left_mask  = 0xFF >> (x1 & 7);
    unsigned char right_mask = (unsigned char)(0xFF << (7 - (x2 & 7)));

    /*
     * Unified solid + pattern fill using write mode 2.
     * For SOLID_FILL, _fill_pattern is all 0xFF → pat always 0xFF → single fg pass.
     * For pattern fill, two passes per scanline: foreground + background.
     * Each pass uses bit mask = pattern byte, writing at byte granularity
     * instead of per-pixel putpixel. This is ~30x faster for pattern fills.
     */
    vga_write_mode_2();

    for(int y = y1; y <= y2; y++) {
        unsigned char pat = (unsigned char)_fill_pattern[y & 7];
        unsigned long base = (unsigned long)y * VGA_BPL;

        if(byte_x1 == byte_x2) {
            /* Single byte spans both edges */
            unsigned char edge = left_mask & right_mask;
            unsigned char fg = pat & edge;
            unsigned char bg = (unsigned char)(~pat) & edge;
            if(fg) {
                vga_set_bit_mask(fg);
                volatile unsigned char d = vga_mem[base + byte_x1]; (void)d;
                vga_mem[base + byte_x1] = (unsigned char)_fill_color;
            }
            if(bg) {
                vga_set_bit_mask(bg);
                volatile unsigned char d = vga_mem[base + byte_x1]; (void)d;
                vga_mem[base + byte_x1] = 0;
            }
        } else {
            /* Left edge */
            unsigned char fg = pat & left_mask;
            unsigned char bg = (unsigned char)(~pat) & left_mask;
            if(fg) {
                vga_set_bit_mask(fg);
                volatile unsigned char d = vga_mem[base + byte_x1]; (void)d;
                vga_mem[base + byte_x1] = (unsigned char)_fill_color;
            }
            if(bg) {
                vga_set_bit_mask(bg);
                volatile unsigned char d = vga_mem[base + byte_x1]; (void)d;
                vga_mem[base + byte_x1] = 0;
            }

            /* Full bytes in middle */
            if(byte_x2 > byte_x1 + 1) {
                if(pat == 0xFF) {
                    /* All foreground — single pass */
                    vga_set_bit_mask(0xFF);
                    for(int bx = byte_x1 + 1; bx < byte_x2; bx++) {
                        volatile unsigned char d = vga_mem[base + bx]; (void)d;
                        vga_mem[base + bx] = (unsigned char)_fill_color;
                    }
                } else if(pat == 0x00) {
                    /* All background — single pass, black */
                    vga_set_bit_mask(0xFF);
                    for(int bx = byte_x1 + 1; bx < byte_x2; bx++) {
                        volatile unsigned char d = vga_mem[base + bx]; (void)d;
                        vga_mem[base + bx] = 0;
                    }
                } else {
                    /* Mixed pattern — two passes */
                    vga_set_bit_mask(pat);
                    for(int bx = byte_x1 + 1; bx < byte_x2; bx++) {
                        volatile unsigned char d = vga_mem[base + bx]; (void)d;
                        vga_mem[base + bx] = (unsigned char)_fill_color;
                    }
                    vga_set_bit_mask((unsigned char)~pat);
                    for(int bx = byte_x1 + 1; bx < byte_x2; bx++) {
                        volatile unsigned char d = vga_mem[base + bx]; (void)d;
                        vga_mem[base + bx] = 0;
                    }
                }
            }

            /* Right edge */
            fg = pat & right_mask;
            bg = (unsigned char)(~pat) & right_mask;
            if(fg) {
                vga_set_bit_mask(fg);
                volatile unsigned char d = vga_mem[base + byte_x2]; (void)d;
                vga_mem[base + byte_x2] = (unsigned char)_fill_color;
            }
            if(bg) {
                vga_set_bit_mask(bg);
                volatile unsigned char d = vga_mem[base + byte_x2]; (void)d;
                vga_mem[base + byte_x2] = 0;
            }
        }
    }

    vga_write_mode_0();
    vga_set_bit_mask(0xFF);
}


/*--- Color and style ---*/

void setcolor(int color) {
    _fg_color = color & 0x0F;
}

int getcolor(void) {
    return _fg_color;
}

void setfillstyle(int pattern, int color) {
    _fill_style = pattern;
    _fill_color = color & 0x0F;
    if(pattern == SOLID_FILL) {
        memset(_fill_pattern, 0xFF, 8);
    } else if(pattern == EMPTY_FILL) {
        memset(_fill_pattern, 0x00, 8);
    }
    /* USER_FILL keeps the current pattern from setfillpattern */
}

void setfillpattern(const char *upattern, int color) {
    _fill_style = USER_FILL;
    _fill_color = color & 0x0F;
    memcpy(_fill_pattern, upattern, 8);
}

void getfillsettings(struct fillsettingstype *fillinfo) {
    fillinfo->pattern = _fill_style;
    fillinfo->color   = _fill_color;
}

void setlinestyle(int linestyle, unsigned upattern, int thickness) {
    (void)upattern; (void)thickness;
    _line_style = linestyle;
}


/*--- Text output ---*/

void outtextxy(int x, int y, const char *textstring) {
    if(!_font_loaded || !textstring) return;

    /*
     * Optimized: draw each character row as 1-2 byte-level VGA writes
     * instead of up to 8 individual putpixel calls per row.
     * Font data is LSB-first (bit 0 = leftmost pixel),
     * VGA is MSB-first (bit 7 = leftmost pixel), so we reverse bits.
     */
    vga_write_mode_2();

    while(*textstring) {
        unsigned char ch = (unsigned char)*textstring++;
        const unsigned char *glyph = _font8x8[ch];
        int byte_x = x >> 3;
        int shift = x & 7;

        for(int row = 0; row < 8; row++) {
            int sy = y + row;
            if(sy < 0 || sy >= VGA_HEIGHT) continue;

            unsigned char fb = glyph[row];
            if(fb == 0) continue;  /* empty row — skip */

            unsigned char rev = reverse8(fb);
            unsigned long rbase = (unsigned long)sy * VGA_BPL;

            if(shift == 0) {
                /* Byte-aligned: all 8 pixels in one VGA byte */
                if(byte_x >= 0 && byte_x < VGA_BPL) {
                    vga_set_bit_mask(rev);
                    volatile unsigned char d = vga_mem[rbase + byte_x]; (void)d;
                    vga_mem[rbase + byte_x] = (unsigned char)_fg_color;
                }
            } else {
                /* Unaligned: split across two bytes */
                unsigned char m1 = rev >> shift;
                unsigned char m2 = (unsigned char)(rev << (8 - shift));
                if(m1 && byte_x >= 0 && byte_x < VGA_BPL) {
                    vga_set_bit_mask(m1);
                    volatile unsigned char d = vga_mem[rbase + byte_x]; (void)d;
                    vga_mem[rbase + byte_x] = (unsigned char)_fg_color;
                }
                if(m2 && (byte_x + 1) >= 0 && (byte_x + 1) < VGA_BPL) {
                    vga_set_bit_mask(m2);
                    volatile unsigned char d = vga_mem[rbase + byte_x + 1]; (void)d;
                    vga_mem[rbase + byte_x + 1] = (unsigned char)_fg_color;
                }
            }
        }
        x += 8;
    }

    vga_write_mode_0();
    vga_set_bit_mask(0xFF);
}


/*--- Image operations ---*/

unsigned long imagesize(int left, int top, int right, int bottom) {
    unsigned long w = (unsigned long)(right - left + 1);
    unsigned long h = (unsigned long)(bottom - top + 1);
    /* Header: 4 bytes (width as short + height as short)
     * Data: 4 planes * ceil(w/8) * h bytes */
    unsigned long bytes_per_row = (w + 7) / 8;
    return 4 + 4 * bytes_per_row * h;
}


void getimage(int left, int top, int right, int bottom, void *bitmap) {
    unsigned short *header = (unsigned short *)bitmap;
    unsigned char *data;
    int w = right - left + 1;
    int h = bottom - top + 1;
    int bytes_per_row = (w + 7) / 8;

    header[0] = (unsigned short)w;
    header[1] = (unsigned short)h;
    data = (unsigned char *)bitmap + 4;

    /* For each plane, read the pixel data */
    for(int plane = 0; plane < 4; plane++) {
        vga_set_read_plane(plane);

        for(int y = 0; y < h; y++) {
            unsigned long row_base = (unsigned long)(top + y) * VGA_BPL;
            int start_byte = left >> 3;
            int bit_offset = left & 7;

            for(int bx = 0; bx < bytes_per_row; bx++) {
                int src_byte = start_byte + bx;
                unsigned char val = 0;

                if(bit_offset == 0) {
                    /* Aligned case */
                    if(src_byte < VGA_BPL)
                        val = vga_mem[row_base + src_byte];
                } else {
                    /* Unaligned: combine two source bytes */
                    unsigned char b1 = 0, b2 = 0;
                    if(src_byte < VGA_BPL)
                        b1 = vga_mem[row_base + src_byte];
                    if(src_byte + 1 < VGA_BPL)
                        b2 = vga_mem[row_base + src_byte + 1];
                    val = (b1 << bit_offset) | (b2 >> (8 - bit_offset));
                }

                /* Mask out excess bits in the last byte */
                if(bx == bytes_per_row - 1) {
                    int extra_bits = bytes_per_row * 8 - w;
                    if(extra_bits > 0)
                        val &= (0xFF << extra_bits);
                }

                data[plane * bytes_per_row * h + y * bytes_per_row + bx] = val;
            }
        }
    }
}


void putimage(int left, int top, const void *bitmap, int op) {
    const unsigned short *header = (const unsigned short *)bitmap;
    const unsigned char *data;
    int w = header[0];
    int h = header[1];
    int bytes_per_row = (w + 7) / 8;

    data = (const unsigned char *)bitmap + 4;

    /* For each pixel, reconstruct color from 4 planes and write */
    /* This is the simple approach; for COPY_PUT we can optimize */

    if(op == COPY_PUT) {
        /* Optimized: write plane by plane */
        for(int plane = 0; plane < 4; plane++) {
            vga_write_mode_0();
            vga_set_write_planes(1 << plane);

            for(int y = 0; y < h; y++) {
                int screen_y = top + y;
                if(screen_y < 0 || screen_y >= VGA_HEIGHT) continue;

                unsigned long row_base = (unsigned long)screen_y * VGA_BPL;
                int start_byte = left >> 3;
                int bit_offset = left & 7;

                for(int bx = 0; bx < bytes_per_row; bx++) {
                    unsigned char src_val = data[plane * bytes_per_row * h +
                                                 y * bytes_per_row + bx];
                    int dst_byte = start_byte + bx;

                    if(bit_offset == 0) {
                        /* Aligned */
                        if(dst_byte >= 0 && dst_byte < VGA_BPL) {
                            if(bx == bytes_per_row - 1) {
                                int extra = bytes_per_row * 8 - w;
                                if(extra > 0) {
                                    unsigned char mask = (0xFF << extra);
                                    vga_set_bit_mask(mask);
                                    volatile unsigned char d = vga_mem[row_base + dst_byte];
                                    (void)d;
                                    vga_mem[row_base + dst_byte] = src_val;
                                    vga_set_bit_mask(0xFF);
                                    continue;
                                }
                            }
                            vga_set_bit_mask(0xFF);
                            vga_mem[row_base + dst_byte] = src_val;
                        }
                    } else {
                        /* Unaligned: split across two destination bytes */
                        unsigned char hi = src_val >> bit_offset;
                        unsigned char lo = src_val << (8 - bit_offset);

                        if(dst_byte >= 0 && dst_byte < VGA_BPL) {
                            unsigned char mask_hi = 0xFF >> bit_offset;
                            /* Handle last byte masking */
                            if(bx == bytes_per_row - 1) {
                                int extra = bytes_per_row * 8 - w;
                                if(extra > 0) {
                                    unsigned char wb_mask = (0xFF << extra);
                                    mask_hi &= (wb_mask >> bit_offset);
                                }
                            }
                            vga_set_bit_mask(mask_hi);
                            volatile unsigned char d = vga_mem[row_base + dst_byte];
                            (void)d;
                            vga_mem[row_base + dst_byte] = hi;
                        }
                        if(dst_byte + 1 >= 0 && dst_byte + 1 < VGA_BPL) {
                            unsigned char mask_lo = (unsigned char)(0xFF << (8 - bit_offset));
                            if(bx == bytes_per_row - 1) {
                                int extra = bytes_per_row * 8 - w;
                                int lo_bits = 8 - bit_offset;
                                if(extra >= lo_bits) {
                                    /* No bits to write in second byte */
                                    continue;
                                }
                                if(extra > 0)
                                    mask_lo &= (unsigned char)(0xFF << (extra - (8 - bit_offset) + 8));
                            }
                            vga_set_bit_mask(mask_lo);
                            volatile unsigned char d = vga_mem[row_base + dst_byte + 1];
                            (void)d;
                            vga_mem[row_base + dst_byte + 1] = lo;
                        }
                    }
                }
            }
        }
        vga_set_write_planes(0x0F);
        vga_set_bit_mask(0xFF);

    } else {
        /* Fallback: per-pixel operation for XOR_PUT etc. */
        for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++) {
                int byte_idx = x >> 3;
                unsigned char bit = 0x80 >> (x & 7);
                int color = 0;

                for(int plane = 0; plane < 4; plane++) {
                    if(data[plane * bytes_per_row * h +
                           y * bytes_per_row + byte_idx] & bit)
                        color |= (1 << plane);
                }

                int sx = left + x;
                int sy = top + y;
                if(sx < 0 || sx >= VGA_WIDTH || sy < 0 || sy >= VGA_HEIGHT) continue;

                switch(op) {
                    case XOR_PUT: {
                        int old = getpixel(sx, sy);
                        putpixel(sx, sy, old ^ color);
                        break;
                    }
                    case OR_PUT: {
                        int old = getpixel(sx, sy);
                        putpixel(sx, sy, old | color);
                        break;
                    }
                    case AND_PUT: {
                        int old = getpixel(sx, sy);
                        putpixel(sx, sy, old & color);
                        break;
                    }
                    case NOT_PUT:
                        putpixel(sx, sy, color ^ 0x0F);
                        break;
                    default:
                        putpixel(sx, sy, color);
                        break;
                }
            }
        }
    }
}
