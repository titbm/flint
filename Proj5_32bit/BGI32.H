/***********************************************************************
    BGI32.H
    BGI-compatible graphics layer for Open Watcom C++ / DOS4GW
    Implements a subset of Borland Graphics Interface using VGA mode 12h
    (640x480, 16 colors, 4 bit-planes)

    FLINT+ v2.61 port
***********************************************************************/
#ifndef __BGI32_H
#define __BGI32_H

#ifdef __cplusplus
extern "C" {
#endif

/*--- VGA Color constants (standard EGA/VGA 16-color palette) ---*/
#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15

/*--- BGI constants ---*/
#define DETECT          0
#define grOk            0

/*--- Fill styles ---*/
#define EMPTY_FILL      0
#define SOLID_FILL      1
#define USER_FILL       12

/*--- Line styles ---*/
#define SOLID_LINE      0
#define DOTTED_LINE     1
#define CENTER_LINE     2
#define DASHED_LINE     3

/*--- putimage operations ---*/
#define COPY_PUT        0
#define XOR_PUT         1
#define OR_PUT          2
#define AND_PUT         3
#define NOT_PUT         4

/*--- Fill settings structure ---*/
struct fillsettingstype {
    int pattern;
    int color;
};

/*--- Graphics initialization/shutdown ---*/
int  registerfarbgidriver(void *driver);
void initgraph(int *driver, int *mode, const char *path);
void closegraph(void);
int  graphresult(void);

/*--- Drawing primitives ---*/
void putpixel(int x, int y, int color);
int  getpixel(int x, int y);
void line(int x1, int y1, int x2, int y2);
void rectangle(int x1, int y1, int x2, int y2);
void bar(int x1, int y1, int x2, int y2);

/*--- Color and style ---*/
void setcolor(int color);
int  getcolor(void);
void setfillstyle(int pattern, int color);
void setfillpattern(const char *upattern, int color);
void getfillsettings(struct fillsettingstype *fillinfo);
void setlinestyle(int linestyle, unsigned upattern, int thickness);

/*--- Text output ---*/
void outtextxy(int x, int y, const char *textstring);

/*--- Image operations ---*/
unsigned long imagesize(int left, int top, int right, int bottom);
void getimage(int left, int top, int right, int bottom, void *bitmap);
void putimage(int left, int top, const void *bitmap, int op);

/*--- BGI driver stub (for registerfarbgidriver compatibility) ---*/
extern void *EGAVGA_driver_far;

#ifdef __cplusplus
}
#endif

#endif /* __BGI32_H */
