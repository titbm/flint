# FLINT v2.77 — Complete UI Drawing Reference

All coordinates are for 640×480 BGI (EGA/VGA) mode. Default font: DEFAULT_FONT (8×8 bitmap), LEFT_TEXT/TOP_TEXT justify.

---

## Color Constants & Palette

```
Standard EGA 16 colors (indices 0-15):
  0  BLACK         = #000000
  1  BLUE          = #0000AA
  2  GREEN         = #00AA00
  3  CYAN          = #00AAAA   ← COLDLG (dialog background)
  4  RED           = #AA0000
  5  MAGENTA       = #AA00AA
  6  BROWN         = #AA5500
  7  LIGHTGRAY     = #AAAAAA
  8  DARKGRAY      = #555555
  9  LIGHTBLUE     = #5555FF
  10 LIGHTGREEN    = #55FF55
  11 LIGHTCYAN     = #55FFFF
  12 LIGHTRED      = #FF5555
  13 LIGHTMAGENTA  = #FF55FF
  14 YELLOW        = #FFFF00
  15 WHITE         = #FFFFFF

Custom palette indices (set via setrgbpalette or palette DAC):
  56  COLBK         — custom background (DARKGRAY #555555)
  59  COLBKL        — custom light background (LIGHTCYAN #55FFFF)
  60  COL_ON        — active/highlight color (LIGHTRED #FF5555)
  63  (used in button) — white/bright white

NOTE: Colors 56, 59, 60, 63 are DAC palette entries beyond EGA 16.
      The program uses VGA 256-color DAC. Exact RGB values found in
      FLINT.GLS or hardcoded palette initialization.
      For recreation: COLBK≈DARKGRAY (#555555), COLBKL≈LIGHTCYAN (#55FFFF),
      COL_ON≈LIGHTRED (#FF5555), 63≈white.
```

### Constants from PROJ5.H
```c
#define COLDLG  3    // CYAN — dialog background color
#define COLBK   56   // dark custom blue
#define COLBKL  59   // light custom blue  
#define COL_ON  60   // active/selected indicator
#define X0      160  // Picture X-left origin
#define Y0      450  // Picture Y-down origin
```

---

## Fill Patterns (pattern[][8])

20 patterns defined, indices 0–19. Pattern 0 = solid (0xFF bytes), pattern 19 = empty (0x00 bytes). Intermediate = varying dot densities (dithering from solid to empty).

```c
pattern[0]  = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}  // solid
pattern[1]  = {0xF7,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF}  // nearly solid
pattern[2]  = {0xF7,0xFF,0x7F,0xFF,0xF7,0xFF,0x7F,0xFF}
...
pattern[10] = {0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55}  // 50% checkerboard
...
pattern[18] = {0x80,0x00,0x00,0x00,0x08,0x00,0x00,0x00}  // nearly empty
pattern[19] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}  // empty
```

---

## 1. `button(int btc[], int nmb, char buttxt[])` — Normal button

Draws a 3D raised button. `btc[]` array: each button = 6 ints: `[type, action, x, y, dx, dy]`.

```
Let x  = btc[6*nmb+2]
    y  = btc[6*nmb+3]
    dx = btc[6*nmb+4]
    dy = btc[6*nmb+5]

1. setfillstyle(1, 63)        // SOLID_FILL, white
   bar(x, y, x+dx, y+dy)     // white highlight (top-left edges)

2. setfillstyle(1, BLACK)
   bar(x+1, y+1, x+dx+1, y+dy+1)  // shadow (offset +1,+1)

3. setfillstyle(1, 7)         // LIGHTGRAY
   bar(x+1, y+1, x+dx, y+dy) // main button face

4. setcolor(BLACK)
   outtextxy(x+4, y+4, buttxt)  // text at +4,+4 from top-left
```

Visual: white border top-left → black shadow bottom-right → gray fill → black text.

---

## 2. `buttonp(int btc[], int nmb, char buttxt[])` — Pressed button

```
Let x, y, dx, dy = same as button

1. setfillstyle(1, BLACK)
   bar(x, y, x+dx, y+dy)     // black border (top-left)

2. setfillstyle(1, 7)         // LIGHTGRAY  
   bar(x+1, y+1, x+dx+1, y+dy+1)  // face shifted +1,+1

3. setcolor(BLACK)
   outtextxy(x+5, y+5, buttxt)  // text at +5,+5 (shifted 1px vs normal)
```

Visual: inverted 3D — black top-left, gray face shifted down-right, text shifted.

---

## 3. `ctlbt(int btxl, int btyl, int colctl, char ctltxt[])` — Checkbox/radio

```
1. setcolor(colctl)
   rectangle(btxl, btyl, btxl+10, btyl+10)  // 10×10 checkbox outline

2. outtextxy(btxl+15, btyl+2, ctltxt)        // label text 15px right, 2px down
```

The fill inside is controlled by `sw_ctl()` — see below.

---

## 4. `sw_ctl(int flag, int param, int xpos, int ypos, int col)` — Fill checkbox

```
color = (flag == param) ? COL_ON : col

setfillstyle(1, color)
bar(xpos+1, ypos+1, xpos+9, ypos+9)   // fill inside 10×10 checkbox
```

When selected: COL_ON (60) fill. When not: dialog background color fill.

---

## 5. `WndBkgr(int xl, int yt, int xr, int yb, int col, char txt[])` — Window background

```
1. setfillstyle(1, BLACK)
   bar(xl+5, yt+5, xr+5, yb+5)     // drop shadow (offset +5,+5)

2. setfillstyle(1, col)
   bar(xl, yt, xr, yb)              // main window fill

3. setcolor(BLACK)
   rectangle(xl, yt, xr, yb)        // border

4. outtextxy(xl+10, yt+5, txt)       // title text

5. line(xl+3, yt+18, xr-3, yt+18)   // title separator line
6. line(xl+3, yb-30, xr-3, yb-30)   // bottom separator line (button area)
```

---

## 6. `draw_bt(int btc[], char *bnam[], int nmb)` — Draw all buttons

```
for i = 0 to nmb-1:
    if btc[6*i] == 1:  button(btc, i, bnam[i])    // standard button
    if btc[6*i] == 3:  ctlbt(btc[6*i+2], btc[6*i+3], BLACK, bnam[i])  // checkbox
    // type 4 = special area, not drawn
```

---

## 7. `msgbox(char msgtxt[], int more, int f_beep)` — Message box

```
1. getimage(180, 290, 385, 345, bitmapmsg)  // save background

2. setfillstyle(1, BLACK)
   bar(184, 294, 384, 344)              // shadow

3. setfillstyle(1, COL_ON)              // 60
   bar(180, 290, 380, 340)              // bright green/yellow box

4. setcolor(BLACK)
   outtextxy(190, 297, msgtxt)          // message text

5. if(more): outtextxy(190, 325, "Next pix:")

6. draw_bt(btc_msg, bnam_msg, BNM_MSG+more)
   
Buttons (from btc_msg):
   Ok:   button at (310, 322, 22, 14) — text "Ok"
   No:   button at (340, 322, 22, 14) — text "No"
   Next: button at (266, 322, 22, 14) — text "Nx" (only if more>0)
```

---

## 8. `msg(int msgx, int msgy, int onoff, char msgtxt[])` — Temporary message

```
if onoff:
  1. getimage(msgx, msgy, msgx+205, msgy+45, bitmapmsg)
  2. setfillstyle(1, BLACK)
     bar(msgx+4, msgy+4, msgx+204, msgy+44)    // shadow
  3. setfillstyle(1, COL_ON)
     bar(msgx, msgy, msgx+200, msgy+40)          // bright box
  4. setcolor(BLACK)
     outtextxy(msgx+10, msgy+7, msgtxt)

else:
  putimage(msgx, msgy, bitmapmsg, 0)             // restore saved
```

---

## 9. `mainscr(int all)` — Main screen

### Background gradient
```
xl = all ? 0 : 144
xr = all ? 639 : 464

// Top half: patterns 0→19 (solid→empty), color BLUE
for i = (all?0:1) to 19:
    setfillpattern(&pattern[i], BLUE)
    bar(xl, 16*i, xr, 16*(i+1))

// Bottom half: patterns 19→10 (empty→half), color BLUE  
for i = 0 to 9:
    setfillpattern(&pattern[19-i], BLUE)
    bar(xl, 16*(i+20), xr, 16*(i+21))
```

This creates a blue gradient: solid blue at top → transparent in middle → back to partially blue at bottom. Y range: 0–480 in 16-pixel bands.

### Text overlay on gradient
```
setcolor(BLUE)
outtextxy(170, 310, "Institute for Laser Technologies")
outtextxy(230, 320, "and Engineering")
```

### If `all` (full redraw):
```
// Blue rectangles behind buttons
setfillstyle(1, BLUE)
for i = 0 to BNM_SCR-1:    // 7 buttons
    bar(btc_scr[6*i+2]-2, btc_scr[6*i+3]-2,
        btc_scr[6*i+2]+93, btc_scr[6*i+3]+21)

// Draw FLINT logo  
drawfl()

// Draw all 7 buttons
draw_bt(btc_scr, bnam_scr, BNM_SCR)

// Version display
htime(tmpstr)                    // calculate time string
setcolor(9)                      // LIGHTBLUE
outtextxy(580, 55, "2.77")      // version number

// Left panel info
setcolor(COLBKL)                 // 59
if(tout): outtextxy(20, 235, tmpstr)   // time estimate

// Checkboxes for glass mode
ctlbt(30, 50, COLBKL, "1")      // "1" glass checkbox
ctlbt(30, 70, COLBKL, "9")      // "9" glass checkbox
ctlbt(30, 145, COLBKL, "Dr.check")  // Drawing check checkbox

// Fill active checkbox
setfillstyle(1, COL_ON)
if gl_nmb:
    bar(31, 71, 39, 79)         // "9" checkbox filled
    glaspos(30, 85, glpos9)     // draw 3×3 glass position grid
else:
    bar(31, 51, 39, 59)         // "1" checkbox filled

if d_check:
    bar(31, 146, 39, 154)       // Dr.check checkbox filled

// File info
outtextxy(20, 30, "File:")
outtextxy(65, 30, wrkfile)

// Point counts
outtextxy(20, 175, "Nmax:")
outtextxy(65, 175, <nmax string>)
outtextxy(20, 194, "Nlast:")

// Glass info box
outtextxy(30, 270, "GLASS:")
outtextxy(30, 285, "n:")
outtextxy(50, 285, <nglas value>)       // e.g. "1.506"
outtextxy(30, 300, "X:")
outtextxy(50, 300, <xsize/10 value>)    // e.g. "50"
outtextxy(30, 313, "Y:")
outtextxy(50, 313, <ysize/10 value>)
outtextxy(30, 326, "Z:")
outtextxy(50, 326, <zsize/10 value>)
rectangle(20, 260, 96, 344)             // glass info border

// Demo label
if f_demo:
    setcolor(COL_ON)
    outtextxy(565, 85, "Demo")

// Nlast value display
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(31, 206, 86, 222)
outtextxy(40, 211, <lastn string>)
```

### Always (both all and !all):
```
setcolor(COLBKL)
outtextxy(65, 30, wrkfile)        // refresh filename

outtextxy(20, 386, "Reiterations:")
show_reit(0)                      // draw reiteration grid

if f_data: draw(f_xyz, 1)         // draw picture
```

### Main screen button layout (btc_scr):
```
Button 0: "F9 XYZ"     at (520, 380, 90, 18)
Button 1: "F1 Config"   at (520, 210, 90, 18)
Button 2: "F2 Convert"  at (520, 240, 90, 18)
Button 3: "F3 DatLoad"  at (520, 270, 90, 18)
Button 4: "F4 GlsLoad"  at (520, 320, 90, 18)
Button 5: "F5 Start"    at (520, 350, 90, 18)
Button 6: "F10 Exit"    at (520, 430, 90, 18)
```

---

## 10. `show_reit(int mode)` — Reiteration grid

```
setcolor(COLBKL)
setfillstyle(1, BLACK)

if gl_nmb (9-glass mode):
    // 3×3 grid of rectangles
    for i = 0 to 2:
        for k = 0 to 2:
            rectangle(k*42+10, i*16+404, k*42+50, i*16+418)
            
            if mode:
                color = (errnmb & mask) ? COL_ON : BLACK
                setfillstyle(1, color)
            
            bar(k*42+11, i*16+405, k*42+49, i*16+417)
            
            if glpos9 & mask:
                outtextxy(k*42+14, i*16+408, <nmrpt[3*i+k] string>)
            
            mask <<= 1

    Grid cell positions:
    (10,404)-(50,418)   (52,404)-(92,418)   (94,404)-(134,418)
    (10,420)-(50,434)   (52,420)-(92,434)   (94,420)-(134,434)
    (10,436)-(50,450)   (52,436)-(92,450)   (94,436)-(134,450)

else (1-glass mode):
    rectangle(20, 404, 60, 418)
    bar(21, 405, 59, 417)
    outtextxy(24, 408, <nmrpt[9] string>)
```

---

## 11. `glaspos(int xl, int yt, int cw)` — Glass position 3×3 matrix

```
mask = 0x01
for i = 0 to 2:       // rows
    for k = 0 to 2:   // columns
        rectangle(xl+16*k, yt+16*i, xl+16*k+14, yt+16*i+14)
        
        if (cw & mask):
            bar(xl+16*k+1, yt+16*i+1, xl+16*k+13, yt+16*i+13)
        
        mask <<= 1
        outtextxy(xl+16*k+4, yt+16*i+4, <position number 1-9>)

// Called with setfillstyle(1, COL_ON) already active
// Draws a 3×3 grid of 14×14 cells, spacing 16px
// Numbers 1-9 inside, filled cells = selected positions
```

---

## 12. `drawfl()` — FLINT logo

```
// Two-pass rendering: first BLACK shadow, then LIGHTBLUE foreground
// Shadow offset: sh=1 → multiply by 3 → offset (3,3)
// Foreground: sh=0 → offset (0,0)

color = BLACK, sh = 2
while sh > 0:
    sh--
    for i = 0 to 33:        // 34 rows
        for k = 0 to 14:    // 15 bytes per row
            mask = 0x80
            for m = 0 to 7: // 8 bits per byte
                if !(flint[15*i+k] & mask):   // inverted: 0-bits are logo
                    putpixel(500 + 8*k + m + 3*sh, 50 - i + 3*sh, color)
                mask >>= 1
    color = LIGHTBLUE

// Result: Logo at approximately (500,17)-(619,53) area
// "FLINT" text rendered from bitmap, 120×34 pixels
// Black shadow 3px right/down, LIGHTBLUE foreground
```

The `flint[]` array is 34 rows × 15 bytes = 510 bytes. Bits=0 are drawn pixels (inverted mask).

---

## 13. `draw(int flag, int all)` — Picture drawing

```
// Coordinate labels
setcolor(COLBKL)
outtextxy(X0-10, Y0+3, "0")    // (150, 453, "0")

switch f_xyz:
    0: outtextxy(150,403,"Y")  outtextxy(202,453,"X")  hsize=xsize vsize=ysize
    1: outtextxy(150,403,"X")  outtextxy(202,453,"Y")  hsize=ysize vsize=xsize
    2: outtextxy(202,453,"X")  outtextxy(150,403,"Z")  hsize=xsize vsize=zsize
    3: outtextxy(202,453,"Y")  outtextxy(150,403,"Z")  hsize=ysize vsize=zsize

// Scale calculation
k = max(xsize, ysize, zsize)
k = (k > zsize) ? 3000/k : 3000/zsize
vs = k*vsize/10
hs = k*hsize/10

// Picture border
rectangle(X0, Y0-vs, X0+hs, Y0)     // (160, 450-vs, 160+hs, 450)

if all:
    setfillstyle(1, BLACK)
    bar(X0+1, Y0-vs+1, X0+hs-1, Y0-1)    // black interior

    // Draw all pixels
    for i = 0 to nmax-1:
        // compute hp, vp based on flag
        color = (i < lastn) ? COL_ON : COLBKL
        DrawPix(hp, hs, vp, vs, color)

else:
    // Draw single pixel (current point)
    DrawPix(hp, hs, vp, vs, COL_ON)
```

### `DrawPix(int hp, int hs, int vp, int vs, int color)`
```
if (hp>0 && hp<hs && vp>0 && vp<vs):
    putpixel(X0+hp, Y0-vp, color)    // putpixel(160+hp, 450-vp, color)
```

---

## 14. `dlgcfg()` — Configuration dialog

### Window
```
WndBkgr(100, 60, 520, 410, COLDLG, "Configuration")
// → shadow at (105,65,525,415) BLACK
// → fill at (100,60,520,410) CYAN
// → border rectangle(100,60,520,410) BLACK
// → title outtextxy(110,65,"Configuration")
// → title line(103,78,517,78)
// → bottom line(103,380,517,380)
```

### Draw all buttons
```
draw_bt(btc_cfg, bnam_cfg, BNM_CFG + 9*gl_nmb)  
// 28 base buttons + 9*gl_nmb position buttons
```

### Static labels (all BLACK on COLDLG):
```
outtextxy(160, 324, "Reset")
outtextxy(130, 255, "Flash nmb")
rectangle(130, 265, 226, 281)
outtextxy(130, 287, "Service date")
rectangle(130, 297, 226, 313)
outtextxy(270, 100, ".cfg")
outtextxy(400, 130, "Step")
rectangle(400, 140, 460, 156)
outtextxy(400, 175, "X")
rectangle(400, 185, 460, 201)
outtextxy(400, 220, "Y")
rectangle(400, 230, 460, 246)
outtextxy(400, 265, "Z")
rectangle(400, 275, 460, 291)
outtextxy(280, 120, "Las.puls")
outtextxy(280, 130, "period")
rectangle(280, 140, 340, 156)
outtextxy(320, 159, "ms")
outtextxy(280, 175, "Gate")
rectangle(280, 185, 340, 201)
outtextxy(320, 204, "us")
outtextxy(280, 225, "Step")
outtextxy(280, 235, "freq.")
rectangle(280, 245, 340, 261)
outtextxy(320, 264, "Hz")
outtextxy(400, 342, "dT:")
outtextxy(428, 342, <dT value>)
outtextxy(460, 342, "ms")
outtextxy(400, 352, "sh:")
outtextxy(428, 352, <sh_delay value>)
outtextxy(460, 352, "ms")
if f_demo: outtextxy(120, 352, "Demo")
outtextxy(120, 363, <ulMax string> + " pixels max")
rectangle(120, 249, 238, 341)
rectangle(265, 110, 510, 370)
```

### Dynamic values (in main loop):
```
// Checkboxes
sw_ctl(gl_nmb, 0, 120, 90, COLDLG)      // "1" glass
sw_ctl(gl_nmb, 1, 120, 105, COLDLG)     // "9" glasses
sw_ctl(pr_open, 1, 120, 160, COLDLG)    // protect open
sw_ctl(f_gate, 1, 120, 185, COLDLG)     // Gate
sw_ctl(LCtl, 3, 120, 200, COLDLG)       // Pump (active when LCtl==3)
sw_ctl(ptr_work, 1, 400, 90, COLDLG)    // Work ptr
sw_ctl(f_const, 1, 280, 280, COLDLG)    // Constant
sw_ctl(f_const, 0, 280, 295, COLDLG)    // Variable

// Glass position grid (9-glass mode)
setfillstyle(1, COLDLG)
bar(280, 313, 330, 363)                  // clear area
setfillstyle(1, COL_ON)
if gl_nmb: glaspos(280, 315, glpos9)     // 3×3 at (280,315)

// Value displays (COLBKL background bars with BLACK text)
setfillstyle(1, COLBKL)
bar(401,141,459,155)  outtextxy(410,145, step)        // Step
bar(401,186,459,200)  outtextxy(410,190, xptr)        // X
bar(401,231,459,245)  outtextxy(410,235, yptr)        // Y
bar(401,276,459,290)  outtextxy(410,280, zptr)        // Z
bar(281,141,339,155)  outtextxy(290,145, l_period)    // Las period
bar(281,186,339,200)  outtextxy(290,190, gate*10)     // Gate delay (µs)
bar(281,246,339,260)  outtextxy(290,250, step_freq)   // Step freq
bar(131,266,225,280)  outtextxy(140,270, ulFlash)     // Flash nmb
bar(131,298,225,312)  outtextxy(140,302, service_date)// Service date

// dT/sh refresh
setfillstyle(1, COLDLG)
bar(428, 342, 452, 360)
outtextxy(428, 342, <dT>)
outtextxy(428, 352, <sh_delay>)
```

### Config button layout (btc_cfg):
```
Button  0: "Ok"          (300, 386, 90, 18)
Button  1: "Cancel"      (400, 386, 90, 18)
Button  2: "Load .cfg"   (120, 125, 90, 18)
Button  3: "Save .cfg"   (130, 386, 90, 18)
Button  4: "+"            (345, 132, 22, 14)  las.period+
Button  5: "-"            (345, 149, 22, 14)  las.period-
Button  6: "+"            (345, 177, 22, 14)  gate delay+
Button  7: "-"            (345, 194, 22, 14)  gate delay-
Button  8: "+"            (345, 237, 22, 14)  step freq+
Button  9: "-"            (345, 254, 22, 14)  step freq-
Button 10: "S+"           (465, 132, 22, 14)  step+
Button 11: "S-"           (465, 149, 22, 14)  step-
Button 12: "X+"           (465, 177, 22, 14)  X ptr+
Button 13: "X-"           (465, 194, 22, 14)  X ptr-
Button 14: "Y+"           (465, 222, 22, 14)  Y ptr+
Button 15: "Y-"           (465, 239, 22, 14)  Y ptr-
Button 16: "Z+"           (465, 267, 22, 14)  Z ptr+
Button 17: "Z-"           (465, 284, 22, 14)  Z ptr-
Checkbox 18: "1"          (120, 90,  10, 10)
Checkbox 19: "9"          (120, 105, 10, 10)
Checkbox 20: "protect.open" (120, 160, 10, 10)
Checkbox 21: "gate delay"   (120, 185, 10, 10)
Checkbox 22: "laser pump"   (120, 200, 10, 10)
Checkbox 23: "work ptr"     (400, 90,  10, 10)
Checkbox 24: "constant"     (280, 280, 10, 10)
Checkbox 25: "variable"     (280, 295, 10, 10)
Button 26: "#"              (203, 320, 22, 14)  statistics reset
Button 27: "X"              (335, 344, 22, 14)  clear positions
Special 28-36: position grid (280-312, 315-347, 12, 12) 9 cells
```

---

## 15. `dlged()` — Convert/Editor dialog

### Window
```
WndBkgr(80, 20, 610, 462, COLDLG, "Data Convert")
// shadow (85,25,615,467) BLACK  
// fill (80,20,610,462) CYAN
// border, title "Data Convert" at (90,25)
// title line(83,38,607,38)
// bottom line(83,432,607,432)
```

### Static labels:
```
outtextxy(90, 45, "File:")
outtextxy(140, 45, fasc)         // filename
outtextxy(500, 44, "Glass:")
rectangle(500, 54, 576, 70)
outtextxy(500, 75, "n:")
rectangle(500, 85, 560, 101)
outtextxy(500, 111, "Xsize:")
rectangle(500, 121, 560, 137)
outtextxy(500, 147, "Ysize:")
rectangle(500, 157, 560, 173)
outtextxy(500, 183, "Zsize:")
rectangle(500, 193, 560, 209)
rectangle(527, 274, 587, 290)
outtextxy(502, 279, "dT:")
rectangle(527, 292, 587, 308)
outtextxy(502, 297, "dL:")
rectangle(527, 310, 587, 326)
outtextxy(502, 315, "dR:")
rectangle(527, 328, 587, 344)
outtextxy(502, 333, "dB:")
```

### Picture area (cleared each iteration):
```
setfillstyle(1, COLDLG)
bar(110, 60, 480, 419)          // clear picture area

setcolor(COLBKL)
// Axis labels depend on f_view (0-3):
//   0: outtextxy(110,363,"Y")  outtextxy(160,413,"X")
//   1: outtextxy(110,363,"X")  outtextxy(160,413,"Y")
//   2: outtextxy(110,353,"Z")  outtextxy(160,413,"X")
//   3: outtextxy(110,353,"Z")  outtextxy(160,413,"Y")
outtextxy(110, 413, "0")

// Scale box
kscale = max(xsize,ysize) vs max(zsize) → 3500/max
xr = kscale*hsize/10
yt = kscale*vsize/10
if f_invert:
    rectangle(120, 410-yt, 120+xr, 410)

// Value displays
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(501,86,559,100)    outtextxy(510,90, nglas)      // n
bar(501,55,575,69)     outtextxy(505,59, glstype)    // Glass type
bar(501,122,559,136)   outtextxy(510,126, xsize/10)  // X
bar(501,158,559,172)   outtextxy(510,162, ysize/10)  // Y
bar(501,194,559,208)   outtextxy(510,198, zsize/10)  // Z

// Margins (if f_data)
setfillstyle(1, COLBKL)
bar(528,275,586,289)   outtextxy(537,279, dT)
bar(528,293,586,307)   outtextxy(537,297, dL)
bar(528,311,586,325)   outtextxy(537,315, dR)
bar(528,329,586,343)   outtextxy(537,333, dB)

// Picture pixels
setfillstyle(1, f_invert?BLACK:WHITE ... actually just k)
bar(121, 411-yt, 119+xr, 409)     // picture background
// Loop through all points, putpixel for each
```

### Checkboxes:
```
sw_ctl(f_invert, 1, 505, 221, COLDLG)   // Invert
sw_ctl(f_mirror, 1, 505, 234, COLDLG)   // Mirror
```

### Editor button layout (btc_ed):
```
Button  0: "Cancel"       (500, 438, 90, 18)
Button  1: "Data Save"    (391, 438, 90, 18)
Button  2: "Data Load"    (100, 438, 90, 18)
Button  3: "View XYZ"     (500, 250, 90, 18)
Button  4: "0->Center"    (500, 384, 90, 18)
Button  5: "up"           (534, 348, 22, 14)
Button  6: "<-"           (508, 358, 22, 14)
Button  7: "dn"           (534, 365, 22, 14)
Button  8: "->"           (560, 358, 22, 14)
Button  9: "+"            (565, 77,  22, 14)   n+
Button 10: "-"            (565, 94,  22, 14)   n-
Button 11: "+"            (565, 113, 22, 14)   Xsize+
Button 12: "-"            (565, 130, 22, 14)   Xsize-
Button 13: "+"            (565, 149, 22, 14)   Ysize+
Button 14: "-"            (565, 166, 22, 14)   Ysize-
Button 15: "+"            (565, 185, 22, 14)   Zsize+
Button 16: "-"            (565, 202, 22, 14)   Zsize-
Button 17: "Sort"         (294, 438, 90, 18)
Special 18: nglass input  (500, 85,  60, 16)
Special 19: Xsize input   (500, 121, 60, 16)
Special 20: Ysize input   (500, 157, 60, 16)
Special 21: Zsize input   (500, 193, 60, 16)
Special 22: Glass select  (500, 54,  76, 16)
Checkbox 23: "mirror"     (505, 234, 10, 10)
Button 24: "Dimensions"   (197, 438, 90, 18)
Button 25: "C->Center"    (500, 407, 90, 18)
Checkbox 26: "invert"     (505, 221, 10, 10)
Special 27: dT input      (527, 274, 60, 16)
Special 28: dL input      (527, 292, 60, 16)
Special 29: dR input      (527, 310, 60, 16)
Special 30: dB input      (527, 328, 60, 16)
```

---

## 16. `dlgstart()` — Start dialog

### Window
```
WndBkgr(100, 100, 520, 400, COLDLG, "Start")
// shadow (105,105,525,405) BLACK
// fill (100,100,520,400) CYAN
// title "Start" at (110,105)
// title line(103,118,517,118)
// bottom line(103,370,517,370)
```

### Static elements:
```
draw_bt(btc_strt, bnam_strt, BNM_STRT)   // 14 buttons

line(103, 212, 517, 212)                   // horizontal separator
line(236, 156, 275, 156)                   // line under point number area

outtextxy(120, 281, "After noise:")
rectangle(280, 148, 340, 164)              // point number display box
rectangle(120, 291, 380, 360)              // "After noise" options frame
```

### Dynamic (in loop):
```
// Radio buttons - start mode
sw_ctl(f_start, 0, 120, 130, COLDLG)    // Beginning
sw_ctl(f_start, 1, 120, 150, COLDLG)    // Point number
sw_ctl(f_start, 2, 120, 170, COLDLG)    // Continuation
sw_ctl(f_start, 3, 120, 190, COLDLG)    // Saved in CMOS

// Checkboxes
sw_ctl(f_ptr, 1, 120, 225, COLDLG)      // End sensors
sw_ctl(d_check, 1, 120, 245, COLDLG)    // Drawing check

// Noise handling radio
sw_ctl(f_noise, 2, 135, 300, COLDLG)    // Stop
sw_ctl(f_noise, 1, 135, 320, COLDLG)    // Reboot
sw_ctl(f_noise, 0, 135, 340, COLDLG)    // Ignore

// Point number value
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(281, 151, 339, 167)
outtextxy(290, 156, <st_nmbnew+1 string>)
```

### Start button layout (btc_strt):
```
Button  0: " Ok"            (300, 376, 90, 18)
Button  1: " Cancel"        (400, 376, 90, 18)
Button  2: "+"              (345, 150, 22, 14)
Button  3: "-"              (345, 170, 22, 14)
Checkbox 4: "Beginning"     (120, 130, 10, 10)
Checkbox 5: "Point number"  (120, 150, 10, 10)
Checkbox 6: "Continuation"  (120, 170, 10, 10)
Checkbox 7: "Saved in CMOS" (120, 190, 10, 10)
Checkbox 8: "End sensors"   (120, 225, 10, 10)
Checkbox 9: "Drawing check" (120, 245, 10, 10)
Checkbox 10: "Stop"         (135, 300, 10, 10)
Checkbox 11: "Coord.reboot/continuation" (135, 320, 10, 10)
Checkbox 12: "Ignore"       (135, 340, 10, 10)
Special 13: Point input     (280, 150, 60, 18)
```

---

## 17. `dlgload()` — Glass Load dialog

### Window
```
WndBkgr(180, 180, 450, 400, COLDLG, "Glass Load")
// shadow (185,185,455,405) BLACK
// fill (180,180,450,400) CYAN
// title "Glass Load" at (190,185)
// title line(183,198,447,198)
// bottom line(183,370,447,370)
```

### Static elements:
```
draw_bt(btc_gload, bnam_gload, BNM_GLOAD)

rectangle(300, 230, 390, 335)      // position diagram border
rectangle(310, 294, 350, 312)      // center position (10)

outtextxy(310, 240, "1   2   3")   // top row labels
outtextxy(338, 260, "10")          // center label  
outtextxy(310, 280, "4   5   6")   // middle row labels
outtextxy(310, 320, "7   8   9")   // bottom row labels
```

### Glass Load button layout (btc_gload):
```
Button 0: "Up"      (300, 207, 90, 18)
Button 1: "Down"    (300, 339, 90, 18)
Button 2: "Cancel"  (300, 376, 90, 18)
```

---

## 18. `gselect()` — Glass Select dialog

### Window
```
WndBkgr(100, 170, 520, 410, GREEN, "Glass select")
// shadow (105,175,525,415) BLACK
// fill (100,170,520,410) GREEN
// title "Glass select" at (110,175)
// title line(103,188,517,188)
// bottom line(103,380,517,380)
```

### Static elements:
```
draw_bt(btc_gsel, bnam_gsel, BNM_GSEL)

rectangle(119, 214, 251, 341)      // glass list border
rectangle(309, 214, 441, 233)      // selected glass display

outtextxy(130, 200, "Glass:  n:")

setfillstyle(1, COLBKL)
bar(310, 215, 440, 232)            // selected glass background
```

### Dynamic (in loop):
```
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(120, 215, 250, 340)            // list background

// Glass list entries (12 visible)
for i = 0 to 11 (or k-m):
    outtextxy(130, 220+10*i, glass_name)    // name
    outtextxy(194, 220+10*i, glass_n)        // refractive index

// Selected glass display
bar(310, 215, 440, 232)
outtextxy(320, 221, selected_name)
outtextxy(384, 221, selected_n)
```

### Glass Select button layout (btc_gsel):
```
Button 0: "Ok"       (300, 386, 90, 18)
Button 1: "Cancel"   (400, 386, 90, 18)
Special 2: type area (120, 220, 130, 120)
Button 3: "up"       (255, 215, 22, 14)
Button 4: "dn"       (255, 326, 22, 14)
```

---

## 19. `dlgsort()` — Sorting dialog

### Window
```
WndBkgr(110, 180, 410, 400, GREEN, "Sorting")
// shadow (115,185,415,405) BLACK
// fill (110,180,410,400) GREEN
// title "Sorting" at (120,185)
// title line(113,198,407,198)
// bottom line(113,370,407,370)
```

### Static elements:
```
draw_bt(btc_sort, bnam_sort, BNM_SORT)

rectangle(290, 262, 350, 280)      // K1 display box
rectangle(290, 302, 350, 320)      // K2 display box

outtextxy(290, 252, "K1:+dz")
outtextxy(290, 292, "K2:-dz")
outtextxy(130, 335, "Pixels:")

htime(tmpstr)
setcolor(BLACK)
outtextxy(130, 350, tmpstr)         // estimated time
```

### Dynamic (in loop):
```
// Radio buttons
sw_ctl(f_sort, 0, 130, 210, GREEN)    // Off
sw_ctl(f_sort, 1, 130, 230, GREEN)    // 0.5mm layers
sw_ctl(f_sort, 2, 130, 250, GREEN)    // K*dz

// Value displays
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(291, 263, 349, 279)
outtextxy(300, 268, sK1)              // K1 value

bar(291, 303, 349, 319)
outtextxy(300, 308, sK2)              // K2 value

outtextxy(194, 335, nmax)             // pixel count (after "Pixels:")

// After sort:
setfillstyle(1, GREEN)
bar(130, 350, 266, 358)
outtextxy(130, 350, tmpstr)           // updated time
```

### Sort button layout (btc_sort):
```
Button 0: "Close"        (290, 376, 90, 18)
Checkbox 1: "Off"        (130, 210, 10, 10)
Checkbox 2: "0.5mm layers" (130, 230, 10, 10)
Checkbox 3: "K*dz"       (130, 250, 10, 10)
Button 4: "+"            (355, 254, 22, 14)   K1+
Button 5: "-"            (355, 272, 22, 14)   K1-
Button 6: "+"            (355, 294, 22, 14)   K2+
Button 7: "-"            (355, 312, 22, 14)   K2-
Button 8: "Sort/time"    (290, 343, 90, 18)
```

---

## 20. `dlgdim()` — Dimensions Modification dialog

### Window
```
WndBkgr(110, 180, 410, 400, GREEN, "Dimensions Modification")
// shadow (115,185,415,405) BLACK
// fill (110,180,410,400) GREEN
// title "Dimensions Modification" at (120,185)
// title line(113,198,407,198)
// bottom line(113,370,407,370)
```

### Static elements:
```
draw_bt(btc_dim, bnam_dim, BNM_DIM)

rectangle(190, 222, 250, 240)      // K display box
rectangle(300, 222, 360, 240)      // Kx display box
rectangle(300, 262, 360, 280)      // Ky display box
rectangle(300, 302, 360, 320)      // Kz display box

outtextxy(190, 212, "K(%):")
outtextxy(300, 212, "Kx(%):")
outtextxy(300, 252, "Ky(%):")
outtextxy(300, 292, "Kz(%):")
outtextxy(130, 350, "Pixels:")

// Separator lines
line(145, 230, 185, 230)           // under equal/diff radio
line(145, 270, 295, 270)           // horizontal separator
line(295, 222, 295, 320)           // vertical separator
```

### Dynamic (in loop):
```
sw_ctl(fcdim, 0, 130, 305, GREEN)    // from 0
sw_ctl(fcdim, 1, 130, 325, GREEN)    // from centre
sw_ctl(feqk, 1, 130, 225, GREEN)     // Kx=Ky=Kz
sw_ctl(feqk, 0, 130, 265, GREEN)     // different

setfillstyle(1, COLBKL)
bar(191,223,249,239)  outtextxy(200,228, kdim)
bar(301,223,359,239)  outtextxy(310,228, kxdim)
bar(301,263,359,279)  outtextxy(310,268, kydim)
bar(301,303,359,319)  outtextxy(310,308, kzdim)

outtextxy(194, 350, nmax)
```

### Dim button layout (btc_dim):
```
Button 0: "Cancel"       (290, 376, 90, 18)
Button 1: "+"            (255, 214, 22, 14)   K+
Button 2: "-"            (255, 232, 22, 14)   K-
Button 3: "Ok"           (190, 376, 90, 18)
Checkbox 4: "from 0"     (130, 305, 10, 10)
Checkbox 5: "from centre" (130, 325, 10, 10)
Checkbox 6: (unnamed)    (130, 225, 10, 10)   Kx=Ky=Kz
Checkbox 7: (unnamed)    (130, 265, 10, 10)   different
Button 8: "+"            (365, 214, 22, 14)   Kx+
Button 9: "-"            (365, 232, 22, 14)   Kx-
Button 10: "+"           (365, 254, 22, 14)   Ky+
Button 11: "-"           (365, 272, 22, 14)   Ky-
Button 12: "+"           (365, 294, 22, 14)   Kz+
Button 13: "-"           (365, 312, 22, 14)   Kz-
```

---

## 21. `dlgopen(char destnm[], char dlgnm[], int flag)` — File Open dialog

### Window
```
WndBkgr(90, 130, 590, 410, GREEN, dlgnm)
// dlgnm = "Data load" / "Enter name" / "Data load" depending on caller
// shadow (95,135,595,415) BLACK
// fill (90,130,590,410) GREEN
// title at (100,135)
// title line(93,148,587,148)
// bottom line(93,380,587,380)
```

### Static elements:
```
draw_bt(btc_opn, bnam_opn, BNM_OPN + flag)

rectangle(264, 174, 376, 301)      // file list border
rectangle(109, 174, 221, 301)      // directory list border
rectangle(109, 329, 221, 348)      // drive display border
outtextxy(110, 317, "Drive:")
rectangle(419, 174, 531, 193)      // filename input border
```

### Conditional BMP options (when ff==3):
```
setcolor(BLACK)
setfillstyle(1, COLBKL)
rectangle(450, 232, 510, 250)  bar(451,233,509,249)
rectangle(450, 257, 510, 275)  bar(451,258,509,274)
rectangle(450, 282, 510, 300)  bar(451,283,509,299)
outtextxy(420, 237, "dx:")     outtextxy(420, 262, "dy:")
outtextxy(420, 287, "dz:")     outtextxy(520, 250, "0.1-1.5")
outtextxy(520, 287, "0-1.5")   outtextxy(490, 222, "mm")
outtextxy(460, 238, dx_value)  outtextxy(460, 263, dy_value)
outtextxy(460, 288, dz_value)
```

### Dynamic (in loop):
```
// Path display
setfillstyle(1, GREEN)
bar(110, 160, 580, 168)
outtextxy(110, 160, path)

// File type radio buttons
sw_ctl(ff, 0, btc_opn[62], btc_opn[63], GREEN)   // *.bft
sw_ctl(ff, 1, btc_opn[68], btc_opn[69], GREEN)   // *.cft
sw_ctl(ff, 2, btc_opn[74], btc_opn[75], GREEN)   // *.asc
sw_ctl(ff, 3, btc_opn[80], btc_opn[81], GREEN)   // *.bmp

// Directory listing
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(110, 175, 220, 300)
for i = 0 to 11:
    outtextxy(120, 180+10*i, dname[i+n])

// Drive display
bar(110, 330, 220, 347)
outtextxy(120, 336, "A:" etc)

// File listing
bar(265, 175, 375, 300)
for i = 0 to 11:
    outtextxy(275, 180+10*i, mname[i+m])   // lowercase

// Filename input
bar(420, 175, 530, 192)
outtextxy(430, 181, fnamnew)
```

### File Open button layout (btc_opn):
```
Button 0: "Ok"       (370, 386, 90, 18)
Button 1: "Cancel"   (470, 386, 90, 18)
Button 2: "up"       (225, 175, 22, 14)   subdir up
Button 3: "dn"       (225, 286, 22, 14)   subdir dn
Special 4: dir area  (110, 180, 110, 120)
Special 5: ChDisk    (110, 330, 110, 17)
Button 6: "up"       (380, 175, 22, 14)   file up
Button 7: "dn"       (380, 286, 22, 14)   file dn
Special 8: file area (265, 180, 110, 120)
Special 9: filename  (420, 175, 110, 17)
Checkbox 10: "*.bft" (280, 330, 10, 10)
Checkbox 11: "*.cft" (280, 345, 10, 10)
Checkbox 12: "*.asc" (280, 315, 10, 10)
Checkbox 13: "*.bmp" (280, 360, 10, 10)
Special 14: dx       (450, 232, 60, 18)
Special 15: dy       (450, 257, 60, 18)
Special 16: dz       (450, 282, 60, 18)
```

---

## 22. `disksel(int nmb)` — Disk selector dropdown

```
m = 10*(nmb+1)

getimage(170, 324, 210, 335+m, bitmapmsg)   // save background

setcolor(BLACK)
rectangle(170, 324, 210, 335+m)              // border

setfillstyle(1, COLBKL)
bar(171, 325, 209, 334+m)                   // background

// Drive letters
for i = 0 to nmb:
    outtextxy(180, 331+10*i, "A:" / "B:" / ...)
```

---

## 23. `inp_dig(int xl, int yt, ...)` — Numeric input field

```
// Input field rendering during typing:
setfillstyle(1, WHITE)
bar(xl, yt, xl+58, yt+14)        // white input box
setcolor(BLACK)
outtextxy(xl+9, yt+4, str)       // typed text with cursor (_)
```

---

## 24. `progbar(long nmb_max, long nmb, int set, int xl, int yt)` — Progress bar

```
if set (initialization):
    setfillstyle(1, LIGHTGRAY)
    bar(xl, yt, xl+254, yt+10)         // gray track (255×11 pixels)
    
    setcolor(LIGHTRED)
    outtextxy(xl+290, yt+2, "%")       // percent sign

// Progress fill:
setfillstyle(1, BLUE)
for k = 0 to k_old-1:
    bar(xl+3+k*5, yt+2, xl+6+k*5, yt+8)    // blue bars, 4px wide, 5px spacing

// Percentage text:
setcolor(LIGHTRED)
outtextxy(xl+265, yt+2, percentage_string)
```

Typically called with `xl=160, yt=464` → bar at (160,464)-(414,474).

---

## 25. Process loop drawing (PIC.CPP `process()`)

During laser processing, the main screen is active. Additional drawing:

```
// "For STOP" message
msg(160, 80, 1, "For STOP: press ESC")
// → COL_ON box at (160,80)-(360,120) with black text

// Progress bar at bottom
progbar(nmax, start_nmb, 1, 160, 464)

// Update Nlast counter each pixel:
setcolor(BLACK)
setfillstyle(1, COLBKL)
bar(31, 176, 86, 192)
outtextxy(40, 181, lastn_string)

// Reiteration counter (if d_check):
setfillstyle(1, COLBKL)
bar(31, 200, 86, 216)
outtextxy(40, 205, ulRpt_string)

// Dr.check indicator (if d_check):
setfillstyle(1, RED)
bar(100, 174, 110, 178)       // small red box

// Each pixel:
draw(f_xyz, 0)                 // single pixel update
progbar(nmax, i, 0, 160, 464)  // progress update
```

---

## Summary: Screen Layout Map

```
640×480 Main Screen Layout:
┌─────────────────────────────────────────────────────────────────┐
│ File: <name>                                    FLINT logo  2.77│ 0-50
│ □1  □9                                                          │ 50-120
│ ┌glaspos─┐                                                      │ 85-135
│ │1 2 3   │                                                      │
│ │4 5 6   │              [gradient background                    │
│ │7 8 9   │               with blue pattern]                     │
│ └────────┘                                                      │
│ □Dr.check                                     ┌──────────┐     │ 145
│ Nmax: <n>                                     │F1 Config │     │ 175-210
│ Nlast: <n>     Institute for Laser            │F2 Convert│     │ 210-270
│ Time: h:m:s    Technologies                   │F3 DatLoad│     │
│ ┌GLASS────┐    and Engineering                │F4 GlsLoad│     │ 270-350
│ │n: 1.506 │                                   │F5 Start  │     │
│ │X: 50    │     ┌picture area──┐              │F9 XYZ    │     │ 350-400
│ │Y: 50    │     │              │              │          │     │
│ │Z: 50    │     │  dot plot    │              │F10 Exit  │     │ 430-448
│ └─────────┘     │              │                         │     │
│ Reiterations:   └──────────────┘                               │
│ ┌reit grid────────┐                                            │ 386-450
│ │ cnt│ cnt│ cnt   │                                            │ 404-450
│ │ cnt│ cnt│ cnt   │                                            │
│ │ cnt│ cnt│ cnt   │                                            │
│ └─────────────────┘              [progress bar]                │ 464-474
└─────────────────────────────────────────────────────────────────┘
```

---

## Font/Text Notes

- **Default font**: `DEFAULT_FONT` (8×8 bitmap), set by BGI `initgraph()`.
- **No `settextstyle()` calls** in any UI function — always default.
- **No `settextjustify()` calls** — always LEFT_TEXT, TOP_TEXT (default).
- Character size: 8×8 pixels. Each character including spacing.
- `outtextxy(x, y, str)` draws text with top-left at (x, y).

---

## Drawing Order Summary per Screen

| Function | 1. Background | 2. Frame/borders | 3. Labels | 4. Buttons | 5. Dynamic values | 6. Checkboxes |
|----------|--------------|-------------------|-----------|------------|-------------------|---------------|
| mainscr  | gradient pattern | — | text labels | 7 buttons | Nmax/Nlast/n/xyz | 1/9/Dr.check + glaspos |
| dlgcfg   | WndBkgr(CYAN) | rectangles | Las.puls/Gate/Step/ptr labels | 28+ buttons | value bars | 8 checkboxes |
| dlged    | WndBkgr(CYAN) | rectangles | Glass/n/Xsize/etc | 31 elements | value bars + plot | 2 checkboxes |
| dlgstart | WndBkgr(CYAN) | rectangles + lines | After noise:/etc | 14 elements | point number | 9 radios |
| dlgload  | WndBkgr(CYAN) | rectangles | position labels | 3 buttons | — | — |
| gselect  | WndBkgr(GREEN) | rectangles | Glass: n: | 5 elements | glass list | — |
| dlgsort  | WndBkgr(GREEN) | rectangles | K1/K2/Pixels | 9 elements | K values/time | 3 radios |
| dlgdim   | WndBkgr(GREEN) | rectangles + lines | K%/Kx%/etc | 14 elements | K values | 4 radios |
| dlgopen  | WndBkgr(GREEN) | rectangles | Drive:/path | 12+ elements | file/dir lists | 4 file types |
| msgbox   | COL_ON bar | — | message text | 2-3 buttons | — | — |
