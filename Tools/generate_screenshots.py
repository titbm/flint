#!/usr/bin/env python3
"""
Generate FLINT v2.77 screenshots from source code UI definitions.
Recreates all dialogs pixel-accurately based on BGI drawing commands in PROJ5.CPP/PROJ5.H.

Resolution: 640x480, EGA 16-color palette extended with custom colors.
"""

import os, sys, base64, struct
from PIL import Image, ImageDraw

# ── Output directory ──
OUTDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Help", "screenshots")
os.makedirs(OUTDIR, exist_ok=True)

# ── EGA 16-color palette (standard VGA) ──
EGA = {
    0:  (0x00, 0x00, 0x00),  # BLACK
    1:  (0x00, 0x00, 0xAA),  # BLUE
    2:  (0x00, 0xAA, 0x00),  # GREEN
    3:  (0x00, 0xAA, 0xAA),  # CYAN
    4:  (0xAA, 0x00, 0x00),  # RED
    5:  (0xAA, 0x00, 0xAA),  # MAGENTA
    6:  (0xAA, 0x55, 0x00),  # BROWN
    7:  (0xAA, 0xAA, 0xAA),  # LIGHTGRAY
    8:  (0x55, 0x55, 0x55),  # DARKGRAY
    9:  (0x55, 0x55, 0xFF),  # LIGHTBLUE
    10: (0x55, 0xFF, 0x55),  # LIGHTGREEN
    11: (0x55, 0xFF, 0xFF),  # LIGHTCYAN
    12: (0xFF, 0x55, 0x55),  # LIGHTRED
    13: (0xFF, 0x55, 0xFF),  # LIGHTMAGENTA
    14: (0xFF, 0xFF, 0x55),  # YELLOW
    15: (0xFF, 0xFF, 0xFF),  # WHITE
}

# Custom BGI palette indices used by FLINT
# These are set via setpalette() — approximate RGB values from typical BGI extended palette
COLDLG  = 3   # Dialog background — CYAN in standard EGA
COLBK   = 56  # Not used directly in drawing
COLBKL  = 59  # Light background for value fields — approximate as light cyan/gray
COL_ON  = 60  # Active/selected indicator — approximate as bright green/teal

# Override colors for custom palette entries (FLINT uses setrgbpalette or setpalette)
# Based on typical FLINT appearance:
COLOR_MAP = dict(EGA)
COLOR_MAP[COLDLG] = (0x00, 0xAA, 0xAA)   # Cyan — dialog background
COLOR_MAP[COLBKL] = (0x55, 0xFF, 0xFF)   # LIGHTCYAN — value fields (AC[11])
COLOR_MAP[COL_ON] = (0xFF, 0x55, 0x55)    # LIGHTRED — active selections (AC[12])
COLOR_MAP[63]     = (0xFF, 0xFF, 0xFF)    # White — button highlight

def C(idx):
    """Get RGB color from palette index."""
    return COLOR_MAP.get(idx, EGA.get(idx, (0xAA, 0xAA, 0xAA)))

BLACK = C(0)
BLUE = C(1)
GREEN = C(2)
CYAN = C(3)
RED = C(4)
LIGHTGRAY = C(7)
LIGHTBLUE = C(9)
LIGHTRED = C(12)
WHITE = C(15)

# ── BGI 8x8 bitmap font (authentic CP437 from VGA BIOS ROM) ──
# Extracted from BGI32.CPP basic_font[] array — chars 32-127, each 8 bytes.
# Each byte = 1 row of 8 pixels, MSB = leftmost pixel.
FONT_8x8 = {
    32: [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
    33: [0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x00],
    34: [0x36,0x36,0x14,0x00,0x00,0x00,0x00,0x00],
    35: [0x36,0x36,0x7F,0x36,0x7F,0x36,0x36,0x00],
    36: [0x0C,0x3E,0x03,0x1E,0x30,0x1F,0x0C,0x00],
    37: [0x00,0x63,0x33,0x18,0x0C,0x66,0x63,0x00],
    38: [0x1C,0x36,0x1C,0x6E,0x3B,0x33,0x6E,0x00],
    39: [0x06,0x06,0x03,0x00,0x00,0x00,0x00,0x00],
    40: [0x18,0x0C,0x06,0x06,0x06,0x0C,0x18,0x00],
    41: [0x06,0x0C,0x18,0x18,0x18,0x0C,0x06,0x00],
    42: [0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00],
    43: [0x00,0x0C,0x0C,0x3F,0x0C,0x0C,0x00,0x00],
    44: [0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x06],
    45: [0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00],
    46: [0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00],
    47: [0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x00],
    48: [0x3E,0x63,0x73,0x7B,0x6F,0x67,0x3E,0x00],
    49: [0x0C,0x0E,0x0C,0x0C,0x0C,0x0C,0x3F,0x00],
    50: [0x1E,0x33,0x30,0x1C,0x06,0x33,0x3F,0x00],
    51: [0x1E,0x33,0x30,0x1C,0x30,0x33,0x1E,0x00],
    52: [0x38,0x3C,0x36,0x33,0x7F,0x30,0x78,0x00],
    53: [0x3F,0x03,0x1F,0x30,0x30,0x33,0x1E,0x00],
    54: [0x1C,0x06,0x03,0x1F,0x33,0x33,0x1E,0x00],
    55: [0x3F,0x33,0x30,0x18,0x0C,0x0C,0x0C,0x00],
    56: [0x1E,0x33,0x33,0x1E,0x33,0x33,0x1E,0x00],
    57: [0x1E,0x33,0x33,0x3E,0x30,0x18,0x0E,0x00],
    58: [0x00,0x0C,0x0C,0x00,0x00,0x0C,0x0C,0x00],
    59: [0x00,0x0C,0x0C,0x00,0x00,0x0C,0x0C,0x06],
    60: [0x18,0x0C,0x06,0x03,0x06,0x0C,0x18,0x00],
    61: [0x00,0x00,0x3F,0x00,0x00,0x3F,0x00,0x00],
    62: [0x06,0x0C,0x18,0x30,0x18,0x0C,0x06,0x00],
    63: [0x1E,0x33,0x30,0x18,0x0C,0x00,0x0C,0x00],
    64: [0x3E,0x63,0x7B,0x7B,0x7B,0x03,0x1E,0x00],
    65: [0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0x00],
    66: [0x3F,0x66,0x66,0x3E,0x66,0x66,0x3F,0x00],
    67: [0x3C,0x66,0x03,0x03,0x03,0x66,0x3C,0x00],
    68: [0x1F,0x36,0x66,0x66,0x66,0x36,0x1F,0x00],
    69: [0x7F,0x46,0x16,0x1E,0x16,0x46,0x7F,0x00],
    70: [0x7F,0x46,0x16,0x1E,0x16,0x06,0x0F,0x00],
    71: [0x3C,0x66,0x03,0x03,0x73,0x66,0x7C,0x00],
    72: [0x33,0x33,0x33,0x3F,0x33,0x33,0x33,0x00],
    73: [0x1E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00],
    74: [0x78,0x30,0x30,0x30,0x33,0x33,0x1E,0x00],
    75: [0x67,0x66,0x36,0x1E,0x36,0x66,0x67,0x00],
    76: [0x0F,0x06,0x06,0x06,0x46,0x66,0x7F,0x00],
    77: [0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00],
    78: [0x63,0x67,0x6F,0x7B,0x73,0x63,0x63,0x00],
    79: [0x1C,0x36,0x63,0x63,0x63,0x36,0x1C,0x00],
    80: [0x3F,0x66,0x66,0x3E,0x06,0x06,0x0F,0x00],
    81: [0x1E,0x33,0x33,0x33,0x3B,0x1E,0x38,0x00],
    82: [0x3F,0x66,0x66,0x3E,0x36,0x66,0x67,0x00],
    83: [0x1E,0x33,0x07,0x0E,0x38,0x33,0x1E,0x00],
    84: [0x3F,0x2D,0x0C,0x0C,0x0C,0x0C,0x1E,0x00],
    85: [0x33,0x33,0x33,0x33,0x33,0x33,0x3F,0x00],
    86: [0x33,0x33,0x33,0x33,0x33,0x1E,0x0C,0x00],
    87: [0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00],
    88: [0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00],
    89: [0x33,0x33,0x33,0x1E,0x0C,0x0C,0x1E,0x00],
    90: [0x7F,0x63,0x31,0x18,0x4C,0x66,0x7F,0x00],
    91: [0x1E,0x06,0x06,0x06,0x06,0x06,0x1E,0x00],
    92: [0x03,0x06,0x0C,0x18,0x30,0x60,0x40,0x00],
    93: [0x1E,0x18,0x18,0x18,0x18,0x18,0x1E,0x00],
    94: [0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00],
    95: [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF],
    96: [0x0C,0x0C,0x18,0x00,0x00,0x00,0x00,0x00],
    97: [0x00,0x00,0x1E,0x30,0x3E,0x33,0x6E,0x00],
    98: [0x07,0x06,0x06,0x3E,0x66,0x66,0x3B,0x00],
    99: [0x00,0x00,0x1E,0x33,0x03,0x33,0x1E,0x00],
   100: [0x38,0x30,0x30,0x3E,0x33,0x33,0x6E,0x00],
   101: [0x00,0x00,0x1E,0x33,0x3F,0x03,0x1E,0x00],
   102: [0x1C,0x36,0x06,0x0F,0x06,0x06,0x0F,0x00],
   103: [0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x1F],
   104: [0x07,0x06,0x36,0x6E,0x66,0x66,0x67,0x00],
   105: [0x0C,0x00,0x0E,0x0C,0x0C,0x0C,0x1E,0x00],
   106: [0x30,0x00,0x30,0x30,0x30,0x33,0x33,0x1E],
   107: [0x07,0x06,0x66,0x36,0x1E,0x36,0x67,0x00],
   108: [0x0E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00],
   109: [0x00,0x00,0x33,0x7F,0x7F,0x6B,0x63,0x00],
   110: [0x00,0x00,0x1F,0x33,0x33,0x33,0x33,0x00],
   111: [0x00,0x00,0x1E,0x33,0x33,0x33,0x1E,0x00],
   112: [0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x0F],
   113: [0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x78],
   114: [0x00,0x00,0x3B,0x6E,0x66,0x06,0x0F,0x00],
   115: [0x00,0x00,0x3E,0x03,0x1E,0x30,0x1F,0x00],
   116: [0x08,0x0C,0x3E,0x0C,0x0C,0x2C,0x18,0x00],
   117: [0x00,0x00,0x33,0x33,0x33,0x33,0x6E,0x00],
   118: [0x00,0x00,0x33,0x33,0x33,0x1E,0x0C,0x00],
   119: [0x00,0x00,0x63,0x6B,0x7F,0x7F,0x36,0x00],
   120: [0x00,0x00,0x63,0x36,0x1C,0x36,0x63,0x00],
   121: [0x00,0x00,0x33,0x33,0x33,0x3E,0x30,0x1F],
   122: [0x00,0x00,0x3F,0x19,0x0C,0x26,0x3F,0x00],
   123: [0x38,0x0C,0x0C,0x07,0x0C,0x0C,0x38,0x00],
   124: [0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00],
   125: [0x07,0x0C,0x0C,0x38,0x0C,0x0C,0x07,0x00],
   126: [0x6E,0x3B,0x00,0x00,0x00,0x00,0x00,0x00],
   127: [0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00],
}

def draw_bgi_text(img, x, y, text, color):
    """Render text using the authentic 8x8 BGI bitmap font, pixel-by-pixel."""
    for ci, ch in enumerate(text):
        code = ord(ch)
        glyph = FONT_8x8.get(code)
        if glyph is None:
            continue  # skip unprintable chars
        cx = x + ci * 8
        for row in range(8):
            byte_val = glyph[row]
            if byte_val == 0:
                continue
            for bit in range(8):
                if byte_val & (1 << bit):
                    px, py = cx + bit, y + row
                    if 0 <= px < 640 and 0 <= py < 480:
                        img.putpixel((px, py), color)

# ── FLINT logo bitmap (from PROJ5.H: flint[] array, 120x34 pixels, MSB-first) ──
FLINT_LOGO = bytes([
0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x83,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0x3F,0xFF,0x9F,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0x3F,0xFF,0x0F,0xF0,0xFF,0x9F,0xF3,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,
0xC0,0x1F,0xFE,0x07,0xF8,0x03,0x80,0x78,0xFF,0xF8,0x3F,0xFF,0xFF,0xFF,0xFF,
0xE0,0x1F,0xFE,0x01,0xF8,0x03,0xC0,0x38,0x3F,0xF0,0x1F,0xFF,0xF0,0x3F,0xFF,
0xE0,0x1F,0xFC,0x00,0xFC,0x03,0xC0,0x3C,0x0F,0xE0,0x0F,0xFF,0xF8,0x1F,0xFF,
0xE0,0x0F,0xFE,0x00,0x7C,0x01,0xC0,0x3C,0x07,0xE0,0x07,0xFF,0xF8,0x1F,0xFF,
0xF0,0x0F,0xFE,0x01,0xFC,0x01,0xE0,0x1E,0x03,0xE0,0x03,0xFF,0xF8,0x1F,0xFF,
0xF0,0x0F,0xFE,0x03,0xFE,0x01,0xE0,0x1E,0x03,0xE0,0x07,0xFF,0xFC,0x0F,0xFF,
0xF0,0x07,0xFE,0x03,0xFE,0x01,0xE0,0x1E,0x01,0xE0,0x0F,0xFF,0xFC,0x0F,0xFF,
0xF8,0x07,0xFF,0x01,0xFF,0x00,0xF0,0x0F,0x01,0xF0,0x0F,0xFF,0xFE,0x07,0xFF,
0xF8,0x07,0xFF,0x01,0xFF,0x00,0xF0,0x0F,0x01,0xF0,0x0F,0xFF,0xFE,0x07,0xFF,
0xF8,0x03,0xFF,0x01,0xFF,0x00,0xF0,0x0F,0x00,0xF8,0x0F,0xFF,0xFE,0x07,0xFF,
0xFC,0x03,0xFF,0x80,0xFF,0x00,0x78,0x07,0x80,0xF8,0x0F,0xFF,0xFF,0x03,0xFF,
0xFC,0x03,0xFF,0x80,0xFF,0x80,0x78,0x07,0x80,0x7C,0x07,0xFE,0x00,0x00,0x03,
0xEC,0x03,0xFF,0x80,0x7B,0x80,0x78,0x07,0x80,0x7C,0x07,0xFE,0x00,0x00,0x03,
0xE0,0x01,0xFF,0xC0,0x7C,0x00,0x3C,0x03,0x80,0x60,0x07,0xFF,0x00,0x00,0x01,
0xF0,0x00,0x07,0xC0,0x7C,0x00,0x3C,0x01,0x80,0x30,0x00,0x3F,0x00,0x00,0x01,
0xF8,0x00,0x07,0xC0,0x3E,0x00,0x3C,0x00,0x80,0x38,0x00,0x1F,0x80,0x00,0x00,
0xFC,0x00,0x03,0xE0,0x3F,0x80,0x1E,0x00,0x00,0x3C,0x00,0x1F,0x80,0x00,0x00,
0xFF,0x00,0x01,0xE0,0x3F,0xF8,0x1E,0x01,0x00,0x3F,0x00,0x0F,0xFF,0xC0,0xFF,
0xFF,0x80,0x00,0xE0,0x1F,0xFF,0x1F,0xE1,0xC0,0x7F,0x00,0x0F,0xFF,0xC0,0xFF,
0xFF,0x80,0x7F,0xF0,0x1F,0xFF,0xCF,0xFC,0xF0,0xFF,0x80,0xFF,0xFF,0xE0,0x7F,
0xFF,0x80,0x7F,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xE0,0x7F,
0xFF,0x80,0x3D,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x7F,0xFF,0xE0,0x7F,
0xFF,0xC0,0x3C,0xF8,0x0F,0xFC,0x3F,0xFF,0xFF,0xFF,0xC0,0x7F,0xFF,0xF0,0x3F,
0xFF,0xC0,0x38,0x78,0x07,0xF8,0x1F,0xFF,0xFF,0xFF,0xF8,0x3F,0xFF,0xF0,0x3F,
0xFF,0xE0,0x30,0x7C,0x07,0xF0,0x07,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xF0,0x3F,
0xFF,0xF0,0x00,0x3C,0x03,0xF0,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,
0xFF,0xFC,0x00,0x3C,0x03,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,
0xFF,0xFE,0x00,0x3E,0x03,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x80,0x1F,0x81,0xFC,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xE0,0x3F,0xF9,0xFF,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
])

# ── Fill patterns from PROJ5.H (for gradient background) ──
PATTERNS = [
    bytes([0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF]),  # 0: solid
    bytes([0xF7, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF]),  # 1
    bytes([0xF7, 0xFF, 0x7F, 0xFF, 0xF7, 0xFF, 0x7F, 0xFF]),  # 2
    bytes([0xDD, 0xFF, 0x77, 0xFF, 0xDD, 0xFF, 0x77, 0xFF]),  # 3
    bytes([0xDD, 0x7F, 0xDD, 0xF7, 0xDD, 0x7F, 0xDD, 0xF7]),  # 4
    bytes([0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77]),  # 5
    bytes([0x55, 0x77, 0xDD, 0x77, 0x55, 0x77, 0xDD, 0x77]),  # 6
    bytes([0xAA, 0xDD, 0xAA, 0x77, 0xAA, 0xDD, 0xAA, 0x77]),  # 7
    bytes([0xAA, 0x57, 0xAA, 0x75, 0xAA, 0x57, 0xAA, 0x75]),  # 8
    bytes([0xAA, 0x55, 0xAA, 0x57, 0xAA, 0x55, 0xAA, 0x75]),  # 9
    bytes([0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55]),  # 10: checkerboard
    bytes([0xAA, 0x54, 0xAA, 0x45, 0xAA, 0x54, 0xAA, 0x45]),  # 11
    bytes([0x55, 0x88, 0x55, 0x22, 0x55, 0x88, 0x55, 0x22]),  # 12
    bytes([0x88, 0xAA, 0x88, 0x22, 0x88, 0xAA, 0x88, 0x22]),  # 13
    bytes([0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22]),  # 14
    bytes([0x88, 0x20, 0x88, 0x02, 0x88, 0x20, 0x88, 0x02]),  # 15
    bytes([0x88, 0x00, 0x22, 0x00, 0x88, 0x00, 0x22, 0x00]),  # 16
    bytes([0x80, 0x00, 0x08, 0x00, 0x80, 0x00, 0x08, 0x00]),  # 17
    bytes([0x80, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00]),  # 18
    bytes([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]),  # 19: empty
]

# ── Drawing helpers ──

def fill_pattern(img, x1, y1, x2, y2, pat_idx, color):
    """Fill rectangle with BGI fill pattern."""
    pat = PATTERNS[pat_idx]
    w, h = img.size
    for y in range(max(0, y1), min(h, y2 + 1)):
        row_byte = pat[y % 8]
        for x in range(max(0, x1), min(w, x2 + 1)):
            bit = (row_byte >> (7 - (x % 8))) & 1
            if bit:
                img.putpixel((x, y), color)

def button(draw, img, x, y, w, h, text, pressed=False):
    """Draw a 3D button like BGI button()/buttonp()."""
    if not pressed:
        # White highlight top-left
        draw.rectangle([x, y, x+w, y+h], fill=C(63))
        # Black shadow bottom-right
        draw.rectangle([x+1, y+1, x+w+1, y+h+1], fill=BLACK)
        # Gray fill
        draw.rectangle([x+1, y+1, x+w, y+h], fill=LIGHTGRAY)
        # Text
        draw_bgi_text(img, x+4, y+3, text, BLACK)
    else:
        draw.rectangle([x, y, x+w, y+h], fill=BLACK)
        draw.rectangle([x+1, y+1, x+w+1, y+h+1], fill=LIGHTGRAY)
        draw_bgi_text(img, x+5, y+4, text, BLACK)

def ctlbt(draw, img, x, y, color, text, filled=False, fill_color=None):
    """Draw a checkbox/radio button."""
    draw.rectangle([x, y, x+10, y+10], outline=color)
    if filled and fill_color:
        draw.rectangle([x+1, y+1, x+9, y+9], fill=fill_color)
    draw_bgi_text(img, x+15, y+1, text, color)

def wnd_bkgr(draw, img, xl, yt, xr, yb, col, txt):
    """Draw a window background with shadow, title, and separator lines."""
    # Shadow
    draw.rectangle([xl+5, yt+5, xr+5, yb+5], fill=BLACK)
    # Fill
    draw.rectangle([xl, yt, xr, yb], fill=col)
    # Border
    draw.rectangle([xl, yt, xr, yb], outline=BLACK)
    # Title
    draw_bgi_text(img, xl+10, yt+4, txt, BLACK)
    # Separator lines
    draw.line([(xl+3, yt+18), (xr-3, yt+18)], fill=BLACK)
    draw.line([(xl+3, yb-30), (xr-3, yb-30)], fill=BLACK)

def glaspos(draw, img, xl, yt, cw, fill_color=None):
    """Draw 3x3 glass position matrix."""
    if fill_color is None:
        fill_color = C(COL_ON)
    mask = 0x01
    for i in range(3):
        for k in range(3):
            rx = xl + 16*k
            ry = yt + 16*i
            draw.rectangle([rx, ry, rx+14, ry+14], outline=C(COLBKL))
            if cw & mask:
                draw.rectangle([rx+1, ry+1, rx+13, ry+13], fill=fill_color)
            mask <<= 1
            num = str(3*i + k + 1)
            draw_bgi_text(img, rx+4, ry+3, num, BLACK)

def value_field(draw, img, x1, y1, x2, y2, text):
    """Draw a value display field (COLBKL background)."""
    draw.rectangle([x1, y1, x2, y2], fill=C(COLBKL))
    draw_bgi_text(img, x1+9, y1+3, text, BLACK)

def draw_flint_logo(img, draw, ox=500, oy=50):
    """Draw the FLINT logo from bitmap data with shadow effect."""
    # Pass 1: black shadow (offset +3,+3 then +0,+0)
    for sh_pass, color in [(3, BLACK), (0, LIGHTBLUE)]:
        for i in range(34):
            for k in range(15):
                byte_val = FLINT_LOGO[15*i + k]
                mask = 0x80
                for m in range(8):
                    if not (byte_val & mask):
                        px = ox + 8*k + m + sh_pass
                        py = oy - i + sh_pass
                        if 0 <= px < 640 and 0 <= py < 480:
                            img.putpixel((px, py), color)
                    mask >>= 1

def draw_gradient_bg(img, xl=0, xr=639, with_text=True):
    """Draw the mainscr gradient background."""
    draw = ImageDraw.Draw(img)
    # Upper gradient: patterns 0..19 (but capped by loop logic)
    # for(i=0; i<20; i++) setfillpattern(pattern[i], BLUE); bar(xl,16*i,xr,16*(i+1))
    for i in range(20):
        fill_pattern(img, xl, 16*i, xr, 16*(i+1), i if i < 20 else 19, BLUE)
    # Lower gradient: patterns 19-i for i=0..9
    for i in range(10):
        fill_pattern(img, xl, 16*(i+20), xr, 16*(i+21), 19-i, BLUE)
    if with_text:
        draw_bgi_text(img, 170, 310, "Institute for Laser Technologies", BLUE)
        draw_bgi_text(img, 230, 320, "and Engineering", BLUE)

def show_reit(draw, img, gl_nmb=0, glpos9=0x1FF, nmrpt=None):
    """Draw reiteration grid on main screen."""
    if nmrpt is None:
        nmrpt = [0]*10
    if gl_nmb:
        mask = 1
        for i in range(3):
            for k in range(3):
                rx1 = k*42 + 10
                ry1 = i*16 + 404
                rx2 = k*42 + 50
                ry2 = i*16 + 418
                draw.rectangle([rx1, ry1, rx2, ry2], outline=C(COLBKL))
                draw.rectangle([rx1+1, ry1+1, rx2-1, ry2-1], fill=BLACK)
                if glpos9 & mask:
                    draw_bgi_text(img, rx1+4, ry1+3, str(nmrpt[3*i+k]), C(COLBKL))
                mask <<= 1
    else:
        draw.rectangle([20, 404, 60, 418], outline=C(COLBKL))
        draw.rectangle([21, 405, 59, 417], fill=BLACK)
        draw_bgi_text(img, 24, 407, str(nmrpt[9]), C(COLBKL))

# ── Fake data for demo display ──
DEMO_DATA = {
    "wrkfile": "MEGAFON1.BFT",
    "nmax": 12458,
    "lastn": 0,
    "nglas": 1.506,
    "glstype": "K8",
    "xsize": 500,  # in 0.1mm units
    "ysize": 500,
    "zsize": 500,
    "xptr": 11750,
    "yptr": 11750,
    "zptr": 5500,
    "step": 100,
    "l_period": 200,
    "gate_delay": 5,
    "step_freq": 500,
    "f_const": 1,
    "gl_nmb": 1,
    "glpos9": 0x1FF,
    "dT": 3,
    "sh_delay": 10,
    "ulFlash": 1547832,
    "ulMax": 32000,
    "d_check": 1,
    "f_demo": 1,
}

# ════════════════════════════════════════════════════════════
#  SCREEN GENERATORS
# ════════════════════════════════════════════════════════════

def gen_mainscr():
    """Generate Main Screen screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    d = DEMO_DATA
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    # Blue pads behind buttons
    btns = [
        (520,380,90,18), (520,210,90,18), (520,240,90,18),
        (520,270,90,18), (520,320,90,18), (520,350,90,18),
        (520,430,90,18),
    ]
    bnames = ["F9 XYZ","F1 Config","F2 Convert","F3 DatLoad","F4 GlsLoad","F5 Start","F10 Exit"]
    for (bx,by,bw,bh) in btns:
        dr.rectangle([bx-2, by-2, bx+bw+3, by+bh+3], fill=BLUE)
    for (bx,by,bw,bh), nm in zip(btns, bnames):
        button(dr, img, bx, by, bw, bh, nm)

    # FLINT logo
    draw_flint_logo(img, dr)

    # Version display (v2.77)
    draw_bgi_text(img, 580, 55, "2.77", C(9))

    # Time estimation
    draw_bgi_text(img, 20, 235, "Time: 0:34:52", C(COLBKL))

    # Demo indicator
    draw_bgi_text(img, 565, 85, "Demo", C(COL_ON))

    # Info panel
    draw_bgi_text(img, 20, 30, "File:", C(COLBKL))
    draw_bgi_text(img, 65, 30, d["wrkfile"], C(COLBKL))
    draw_bgi_text(img, 20, 175, "Nmax:", C(COLBKL))
    draw_bgi_text(img, 65, 175, str(d["nmax"]), C(COLBKL))
    draw_bgi_text(img, 20, 194, "Nlast:", C(COLBKL))

    # Nlast value field
    dr.rectangle([31, 206, 86, 222], fill=C(COLBKL))
    draw_bgi_text(img, 40, 210, str(d["lastn"]), BLACK)

    # Glass info box
    draw_bgi_text(img, 30, 270, "GLASS:", C(COLBKL))
    draw_bgi_text(img, 30, 285, "n:", C(COLBKL))
    draw_bgi_text(img, 50, 285, "1.506", C(COLBKL))
    draw_bgi_text(img, 30, 300, "X:", C(COLBKL))
    draw_bgi_text(img, 50, 300, "50.0", C(COLBKL))
    draw_bgi_text(img, 30, 313, "Y:", C(COLBKL))
    draw_bgi_text(img, 50, 313, "50.0", C(COLBKL))
    draw_bgi_text(img, 30, 326, "Z:", C(COLBKL))
    draw_bgi_text(img, 50, 326, "50.0", C(COLBKL))
    dr.rectangle([20, 260, 96, 344], outline=C(COLBKL))

    # Checkboxes for 1/9 and Dr.check
    ctlbt(dr, img, 30, 50, C(COLBKL), "1")
    ctlbt(dr, img, 30, 70, C(COLBKL), "9", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 30, 145, C(COLBKL), "Dr.check", filled=d["d_check"], fill_color=C(COL_ON))

    # Glass position 3x3 grid
    glaspos(dr, img, 30, 90, d["glpos9"])

    # Reiteration display
    draw_bgi_text(img, 20, 386, "Reiterations:", C(COLBKL))
    show_reit(dr, img, gl_nmb=d["gl_nmb"], nmrpt=[0]*10)

    # Picture area (draw rectangle for viewing area)
    X0, Y0 = 160, 450
    k = 3000 // 500  # kscale
    hs = k * 500 // 10
    vs = k * 500 // 10
    dr.rectangle([X0, Y0-vs, X0+hs, Y0], outline=C(COLBKL))
    dr.rectangle([X0+1, Y0-vs+1, X0+hs-1, Y0-1], fill=BLACK)
    draw_bgi_text(img, X0-10, Y0+3, "0", C(COLBKL))
    draw_bgi_text(img, X0-10, Y0-50, "Y", C(COLBKL))
    draw_bgi_text(img, X0+42, Y0+3, "X", C(COLBKL))

    img.save(os.path.join(OUTDIR, "mainscr.png"))
    return img


def gen_config():
    """Generate Configuration dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)
    d = DEMO_DATA

    wnd_bkgr(dr, img, 100, 60, 520, 410, C(COLDLG), "Configuration")

    # Buttons
    button(dr, img, 300, 386, 90, 18, "Ok")
    button(dr, img, 400, 386, 90, 18, "Cancel")
    button(dr, img, 120, 125, 90, 18, "Load .cfg")
    button(dr, img, 130, 386, 90, 18, "Save .cfg")
    # +/- buttons  
    for bx, by in [(345,132),(345,149),(345,177),(345,194),(345,237),(345,254),
                    (465,132),(465,149),(465,177),(465,194),(465,222),(465,239),
                    (465,267),(465,284)]:
        button(dr, img, bx, by, 22, 14, "+" if (by % 2 == 0) else "-")
    # Specific labels for +/-
    button(dr, img, 345, 132, 22, 14, "+")
    button(dr, img, 345, 149, 22, 14, "-")
    button(dr, img, 345, 177, 22, 14, "+")
    button(dr, img, 345, 194, 22, 14, "-")
    button(dr, img, 345, 237, 22, 14, "+")
    button(dr, img, 345, 254, 22, 14, "-")
    button(dr, img, 465, 132, 22, 14, "S+")
    button(dr, img, 465, 149, 22, 14, "S-")
    button(dr, img, 465, 177, 22, 14, "X+")
    button(dr, img, 465, 194, 22, 14, "X-")
    button(dr, img, 465, 222, 22, 14, "Y+")
    button(dr, img, 465, 239, 22, 14, "Y-")
    button(dr, img, 465, 267, 22, 14, "Z+")
    button(dr, img, 465, 284, 22, 14, "Z-")
    button(dr, img, 203, 320, 22, 14, "#")
    button(dr, img, 335, 344, 22, 14, "X")

    # Checkboxes
    ctlbt(dr, img, 120, 90, BLACK, "1", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 120, 105, BLACK, "9")
    ctlbt(dr, img, 120, 160, BLACK, "protect.open")
    ctlbt(dr, img, 120, 185, BLACK, "gate delay")
    ctlbt(dr, img, 120, 200, BLACK, "laser pump")
    ctlbt(dr, img, 400, 90, BLACK, "work ptr")
    ctlbt(dr, img, 280, 280, BLACK, "constant", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 280, 295, BLACK, "variable")

    # Labels and value rectangles
    draw_bgi_text(img, 270, 100, ".cfg", BLACK)
    draw_bgi_text(img, 280, 120, "Las.puls", BLACK)
    draw_bgi_text(img, 280, 130, "period", BLACK)
    dr.rectangle([280, 140, 340, 156], outline=BLACK)
    draw_bgi_text(img, 320, 159, "ms", BLACK)
    draw_bgi_text(img, 280, 175, "Gate", BLACK)
    dr.rectangle([280, 185, 340, 201], outline=BLACK)
    draw_bgi_text(img, 320, 204, "us", BLACK)
    draw_bgi_text(img, 280, 225, "Step", BLACK)
    draw_bgi_text(img, 280, 235, "freq.", BLACK)
    dr.rectangle([280, 245, 340, 261], outline=BLACK)
    draw_bgi_text(img, 320, 264, "Hz", BLACK)

    draw_bgi_text(img, 400, 130, "Step", BLACK)
    dr.rectangle([400, 140, 460, 156], outline=BLACK)
    draw_bgi_text(img, 400, 175, "X", BLACK)
    dr.rectangle([400, 185, 460, 201], outline=BLACK)
    draw_bgi_text(img, 400, 220, "Y", BLACK)
    dr.rectangle([400, 230, 460, 246], outline=BLACK)
    draw_bgi_text(img, 400, 265, "Z", BLACK)
    dr.rectangle([400, 275, 460, 291], outline=BLACK)

    # Values
    value_field(dr, img, 281, 141, 339, 155, str(d["l_period"]))
    value_field(dr, img, 281, 186, 339, 200, str(d["gate_delay"]*10))
    value_field(dr, img, 281, 246, 339, 260, str(d["step_freq"]))
    value_field(dr, img, 401, 141, 459, 155, str(d["step"]))
    value_field(dr, img, 401, 186, 459, 200, str(d["xptr"]))
    value_field(dr, img, 401, 231, 459, 245, str(d["yptr"]))
    value_field(dr, img, 401, 276, 459, 290, str(d["zptr"]))

    # dT and sh_delay (v2.73/v2.77)
    draw_bgi_text(img, 400, 342, "dT:", BLACK)
    draw_bgi_text(img, 428, 342, str(d["dT"]), BLACK)
    draw_bgi_text(img, 460, 342, "ms", BLACK)
    draw_bgi_text(img, 400, 352, "sh:", BLACK)
    draw_bgi_text(img, 428, 352, str(d["sh_delay"]), BLACK)
    draw_bgi_text(img, 460, 352, "ms", BLACK)

    # Demo label
    draw_bgi_text(img, 120, 352, "Demo", BLACK)

    # ulMax
    draw_bgi_text(img, 120, 363, f"{d['ulMax']} pixels max", BLACK)

    # Statistics
    draw_bgi_text(img, 160, 324, "Reset", BLACK)
    draw_bgi_text(img, 130, 255, "Flash nmb", BLACK)
    dr.rectangle([130, 265, 226, 281], outline=BLACK)
    value_field(dr, img, 131, 266, 225, 280, str(d["ulFlash"]))
    draw_bgi_text(img, 130, 287, "Service date", BLACK)
    dr.rectangle([130, 297, 226, 313], outline=BLACK)
    value_field(dr, img, 131, 298, 225, 312, "15-9-2004")

    # Position rectangles
    dr.rectangle([120, 249, 238, 341], outline=BLACK)
    dr.rectangle([265, 110, 510, 370], outline=BLACK)

    img.save(os.path.join(OUTDIR, "config.png"))
    return img


def gen_convert():
    """Generate Data Convert dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 80, 20, 610, 462, C(COLDLG), "Data Convert")

    # Buttons
    button(dr, img, 500, 438, 90, 18, "Cancel")
    button(dr, img, 391, 438, 90, 18, "Data Save")
    button(dr, img, 100, 438, 90, 18, "Data Load")
    button(dr, img, 500, 250, 90, 18, "View XYZ")
    button(dr, img, 500, 384, 90, 18, "0->Center")
    button(dr, img, 294, 438, 90, 18, "Sort")
    button(dr, img, 197, 438, 90, 18, "Dimensions")
    button(dr, img, 500, 407, 90, 18, "C->Center")

    # Direction buttons
    button(dr, img, 534, 348, 22, 14, "up")
    button(dr, img, 508, 358, 22, 14, "<-")
    button(dr, img, 534, 365, 22, 14, "dn")
    button(dr, img, 560, 358, 22, 14, "->")

    # +/- buttons for n, sizes
    for y_pos in [77, 94, 113, 130, 149, 166, 185, 202]:
        label = "+" if (y_pos - 77) % 2 == 0 else "-"
        # Actually alternate +/-
        label = "+" if ((y_pos - 77) // 17) % 2 == 0 else "-"
        button(dr, img, 565, y_pos, 22, 14, label)
    button(dr, img, 565, 77, 22, 14, "+")
    button(dr, img, 565, 94, 22, 14, "-")
    button(dr, img, 565, 113, 22, 14, "+")
    button(dr, img, 565, 130, 22, 14, "-")
    button(dr, img, 565, 149, 22, 14, "+")
    button(dr, img, 565, 166, 22, 14, "-")
    button(dr, img, 565, 185, 22, 14, "+")
    button(dr, img, 565, 202, 22, 14, "-")

    # Labels
    draw_bgi_text(img, 90, 45, "File:", BLACK)
    draw_bgi_text(img, 140, 45, "MEGAFON1.BFT", BLACK)
    draw_bgi_text(img, 500, 44, "Glass:", BLACK)
    dr.rectangle([500, 54, 576, 70], outline=BLACK)
    draw_bgi_text(img, 500, 75, "n:", BLACK)
    dr.rectangle([500, 85, 560, 101], outline=BLACK)
    draw_bgi_text(img, 500, 111, "Xsize:", BLACK)
    dr.rectangle([500, 121, 560, 137], outline=BLACK)
    draw_bgi_text(img, 500, 147, "Ysize:", BLACK)
    dr.rectangle([500, 157, 560, 173], outline=BLACK)
    draw_bgi_text(img, 500, 183, "Zsize:", BLACK)
    dr.rectangle([500, 193, 560, 209], outline=BLACK)
    dr.rectangle([527, 274, 587, 290], outline=BLACK)
    draw_bgi_text(img, 502, 279, "dT:", BLACK)
    dr.rectangle([527, 292, 587, 308], outline=BLACK)
    draw_bgi_text(img, 502, 297, "dL:", BLACK)
    dr.rectangle([527, 310, 587, 326], outline=BLACK)
    draw_bgi_text(img, 502, 315, "dR:", BLACK)
    dr.rectangle([527, 328, 587, 344], outline=BLACK)
    draw_bgi_text(img, 502, 333, "dB:", BLACK)

    # Values
    value_field(dr, img, 501, 55, 575, 69, "K8")
    value_field(dr, img, 501, 86, 559, 100, "1.506")
    value_field(dr, img, 501, 122, 559, 136, "50.0")
    value_field(dr, img, 501, 158, 559, 172, "50.0")
    value_field(dr, img, 501, 194, 559, 208, "50.0")
    value_field(dr, img, 528, 275, 586, 289, "5.00")
    value_field(dr, img, 528, 293, 586, 307, "3.20")
    value_field(dr, img, 528, 311, 586, 325, "3.20")
    value_field(dr, img, 528, 329, 586, 343, "5.00")

    # Checkboxes
    ctlbt(dr, img, 505, 221, BLACK, "invert")
    ctlbt(dr, img, 505, 234, BLACK, "mirror")

    # View area with some dots
    dr.rectangle([110, 60, 480, 419], fill=C(COLDLG))
    draw_bgi_text(img, 110, 363, "Y", C(COLBKL))
    draw_bgi_text(img, 160, 413, "X", C(COLBKL))
    draw_bgi_text(img, 110, 413, "0", BLACK)

    # Simulated object in view
    kscale = 3500 // 500
    xr = kscale * 500 // 10
    yt_view = kscale * 500 // 10
    dr.rectangle([120, 410-yt_view, 120+xr, 410], fill=BLACK, outline=C(COLBKL))

    img.save(os.path.join(OUTDIR, "convert.png"))
    return img


def gen_fileopen():
    """Generate File Open dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 90, 130, 590, 410, GREEN, "Data load")

    button(dr, img, 370, 386, 90, 18, "Ok")
    button(dr, img, 470, 386, 90, 18, "Cancel")
    button(dr, img, 225, 175, 22, 14, "up")
    button(dr, img, 225, 286, 22, 14, "dn")
    button(dr, img, 380, 175, 22, 14, "up")
    button(dr, img, 380, 286, 22, 14, "dn")

    dr.rectangle([264, 174, 376, 301], outline=BLACK)
    dr.rectangle([109, 174, 221, 301], outline=BLACK)
    dr.rectangle([109, 329, 221, 348], outline=BLACK)
    draw_bgi_text(img, 110, 317, "Drive:", BLACK)
    dr.rectangle([419, 174, 531, 193], outline=BLACK)

    # Checkboxes for file types
    ctlbt(dr, img, 280, 330, BLACK, "*.bft", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 280, 345, BLACK, "*.cft")
    ctlbt(dr, img, 280, 315, BLACK, "*.asc")
    ctlbt(dr, img, 280, 360, BLACK, "*.bmp")

    # Path
    draw_bgi_text(img, 110, 160, "C:\\BFT_FILES", BLACK)

    # Directory list
    value_field(dr, img, 110, 175, 220, 300, "")
    dirs = ["..", "BACKUP", "OLD"]
    for i, dn in enumerate(dirs):
        draw_bgi_text(img, 120, 180+10*i, dn, BLACK)

    # Drive
    value_field(dr, img, 110, 330, 220, 347, "")
    draw_bgi_text(img, 120, 336, "C:", BLACK)

    # File list
    value_field(dr, img, 265, 175, 375, 300, "")
    files = ["megafon1.bft", "megafon2.bft"]
    for i, fn in enumerate(files):
        draw_bgi_text(img, 275, 180+10*i, fn, BLACK)

    # File name input
    value_field(dr, img, 420, 175, 530, 192, "megafon1.bft")

    img.save(os.path.join(OUTDIR, "fileopen.png"))
    return img


def gen_glassload():
    """Generate Glass Load dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 180, 180, 450, 400, C(COLDLG), "Glass Load")

    button(dr, img, 300, 207, 90, 18, "Up")
    button(dr, img, 300, 339, 90, 18, "Down")
    button(dr, img, 300, 376, 90, 18, "Cancel")

    dr.rectangle([300, 230, 390, 335], outline=BLACK)
    dr.rectangle([310, 294, 350, 312], outline=BLACK)
    draw_bgi_text(img, 310, 240, "1   2   3", BLACK)
    draw_bgi_text(img, 338, 260, "10", BLACK)
    draw_bgi_text(img, 310, 280, "4   5   6", BLACK)
    draw_bgi_text(img, 310, 320, "7   8   9", BLACK)

    img.save(os.path.join(OUTDIR, "glassload.png"))
    return img


def gen_glassselect():
    """Generate Glass Select dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 100, 170, 520, 410, GREEN, "Glass select")

    button(dr, img, 300, 386, 90, 18, "Ok")
    button(dr, img, 400, 386, 90, 18, "Cancel")
    button(dr, img, 255, 215, 22, 14, "up")
    button(dr, img, 255, 326, 22, 14, "dn")

    dr.rectangle([119, 214, 251, 341], outline=BLACK)
    dr.rectangle([309, 214, 441, 233], outline=BLACK)
    draw_bgi_text(img, 130, 200, "Glass:  n:", BLACK)

    # Glass list
    value_field(dr, img, 120, 215, 250, 340, "")
    glasses = [
        ("BK10", "1.557"), ("K8", "1.506"), ("K100", "1.511"),
        ("KVARZ", "1.500"), ("LK4", "1.481"), ("LK5", "1.469"),
        ("LK6", "1.461"), ("LK7", "1.474"), ("OF1", "1.517"),
        ("STK19", "1.727"), ("TK16", "1.600"), ("TF1", "1.628"),
    ]
    for i, (name, n) in enumerate(glasses):
        if i < 12:
            draw_bgi_text(img, 130, 220+10*i, name, BLACK)
            draw_bgi_text(img, 194, 220+10*i, n, BLACK)

    # Selected value
    value_field(dr, img, 310, 215, 440, 232, "")
    draw_bgi_text(img, 320, 221, "K8", BLACK)
    draw_bgi_text(img, 384, 221, "1.506", BLACK)

    img.save(os.path.join(OUTDIR, "glassselect.png"))
    return img


def gen_start():
    """Generate Start dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 100, 100, 520, 400, C(COLDLG), "Start")

    button(dr, img, 300, 376, 90, 18, " Ok")
    button(dr, img, 400, 376, 90, 18, " Cancel")
    button(dr, img, 345, 150, 22, 14, "+")
    button(dr, img, 345, 170, 22, 14, "-")

    dr.line([(103, 212), (517, 212)], fill=BLACK)
    dr.line([(236, 156), (275, 156)], fill=BLACK)

    # Checkboxes (radio buttons)
    ctlbt(dr, img, 120, 130, BLACK, "Beginning", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 120, 150, BLACK, "Point number")
    ctlbt(dr, img, 120, 170, BLACK, "Continuation")
    ctlbt(dr, img, 120, 190, BLACK, "Saved in CMOS")
    ctlbt(dr, img, 120, 225, BLACK, "End sensors", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 120, 245, BLACK, "Drawing check", filled=True, fill_color=C(COL_ON))

    draw_bgi_text(img, 120, 281, "After noise:", BLACK)
    dr.rectangle([280, 148, 340, 164], outline=BLACK)
    dr.rectangle([120, 291, 380, 360], outline=BLACK)

    ctlbt(dr, img, 135, 300, BLACK, "Stop", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 135, 320, BLACK, "Coord.reboot/continuation")
    ctlbt(dr, img, 135, 340, BLACK, "Ignore")

    # Point number value
    value_field(dr, img, 281, 151, 339, 167, "1")

    # Point number input area (v2.70)
    dr.rectangle([280, 150, 340, 168], outline=BLACK)

    img.save(os.path.join(OUTDIR, "start.png"))
    return img


def gen_sorting():
    """Generate Sorting dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 110, 180, 410, 400, GREEN, "Sorting")

    button(dr, img, 290, 376, 90, 18, "Close")
    button(dr, img, 290, 343, 90, 18, "Sort/time")
    button(dr, img, 355, 254, 22, 14, "+")
    button(dr, img, 355, 272, 22, 14, "-")
    button(dr, img, 355, 294, 22, 14, "+")
    button(dr, img, 355, 312, 22, 14, "-")

    ctlbt(dr, img, 130, 210, BLACK, "Off", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 130, 230, BLACK, "0.5mm layers")
    ctlbt(dr, img, 130, 250, BLACK, "K*dz")

    dr.rectangle([290, 262, 350, 280], outline=BLACK)
    dr.rectangle([290, 302, 350, 320], outline=BLACK)
    draw_bgi_text(img, 290, 252, "K1:+dz", BLACK)
    draw_bgi_text(img, 290, 292, "K2:-dz", BLACK)

    value_field(dr, img, 291, 263, 349, 279, "15")
    value_field(dr, img, 291, 303, 349, 319, "10")

    draw_bgi_text(img, 130, 335, "Pixels:", BLACK)
    draw_bgi_text(img, 194, 335, "12458", BLACK)
    draw_bgi_text(img, 130, 350, "Time: 0:34:52", BLACK)

    img.save(os.path.join(OUTDIR, "sorting.png"))
    return img


def gen_dimensions():
    """Generate Dimensions Modification dialog screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    wnd_bkgr(dr, img, 110, 180, 410, 400, GREEN, "Dimensions Modification")

    button(dr, img, 290, 376, 90, 18, "Cancel")
    button(dr, img, 190, 376, 90, 18, "Ok")
    button(dr, img, 255, 214, 22, 14, "+")
    button(dr, img, 255, 232, 22, 14, "-")
    button(dr, img, 365, 214, 22, 14, "+")
    button(dr, img, 365, 232, 22, 14, "-")
    button(dr, img, 365, 254, 22, 14, "+")
    button(dr, img, 365, 272, 22, 14, "-")
    button(dr, img, 365, 294, 22, 14, "+")
    button(dr, img, 365, 312, 22, 14, "-")

    ctlbt(dr, img, 130, 305, BLACK, "from 0", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 130, 325, BLACK, "from centre")
    ctlbt(dr, img, 130, 225, BLACK, "", filled=True, fill_color=C(COL_ON))
    ctlbt(dr, img, 130, 265, BLACK, "")

    dr.rectangle([190, 222, 250, 240], outline=BLACK)
    dr.rectangle([300, 222, 360, 240], outline=BLACK)
    dr.rectangle([300, 262, 360, 280], outline=BLACK)
    dr.rectangle([300, 302, 360, 320], outline=BLACK)
    draw_bgi_text(img, 190, 212, "K(%):", BLACK)
    draw_bgi_text(img, 300, 212, "Kx(%):", BLACK)
    draw_bgi_text(img, 300, 252, "Ky(%):", BLACK)
    draw_bgi_text(img, 300, 292, "Kz(%):", BLACK)
    draw_bgi_text(img, 130, 350, "Pixels:", BLACK)
    draw_bgi_text(img, 194, 350, "12458", BLACK)

    dr.line([(145, 230), (185, 230)], fill=BLACK)
    dr.line([(145, 270), (295, 270)], fill=BLACK)
    dr.line([(295, 222), (295, 320)], fill=BLACK)

    value_field(dr, img, 191, 223, 249, 239, "100")
    value_field(dr, img, 301, 223, 359, 239, "100")
    value_field(dr, img, 301, 263, 359, 279, "100")
    value_field(dr, img, 301, 303, 359, 319, "100")

    img.save(os.path.join(OUTDIR, "dimensions.png"))
    return img


def gen_msgbox():
    """Generate Message Box screenshot."""
    img = Image.new("RGB", (640, 480), BLACK)
    draw_gradient_bg(img, 0, 639)
    dr = ImageDraw.Draw(img)

    # msgbox background
    dr.rectangle([184, 294, 384, 344], fill=BLACK)
    dr.rectangle([180, 290, 380, 340], fill=C(COL_ON))
    draw_bgi_text(img, 190, 297, "Check laser. Retry: Ok", BLACK)

    # Buttons
    button(dr, img, 310, 322, 22, 14, "Ok")
    button(dr, img, 340, 322, 22, 14, "No")
    button(dr, img, 266, 322, 22, 14, "Nx")
    draw_bgi_text(img, 190, 325, "Next pix:", BLACK)

    img.save(os.path.join(OUTDIR, "msgbox.png"))
    return img


# ════════════════════════════════════════════════════════════
#  MAIN
# ════════════════════════════════════════════════════════════

if __name__ == "__main__":
    print("Generating FLINT v2.77 screenshots...")
    
    screens = [
        ("mainscr",     gen_mainscr),
        ("config",      gen_config),
        ("convert",     gen_convert),
        ("fileopen",    gen_fileopen),
        ("glassload",   gen_glassload),
        ("glassselect", gen_glassselect),
        ("start",       gen_start),
        ("sorting",     gen_sorting),
        ("dimensions",  gen_dimensions),
        ("msgbox",      gen_msgbox),
    ]
    
    for name, func in screens:
        print(f"  {name}...", end=" ")
        img = func()
        img.save(os.path.join(OUTDIR, f"{name}.png"))
        print("OK")
    
    print(f"\nAll screenshots saved to: {OUTDIR}")
    print(f"Total: {len(screens)} images")
