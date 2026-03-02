/***********************************
	proj5.h
	iB
	ver.2.77 (reconstructed)
	32-bit DOS/4GW port (Open Watcom)
***********************************/
#if !defined(__PROJ5_H)
#define __PROJ5_H

#include "compat.h"
#include "bgi32.h"

#define ADRPT0 0x300
#define ADRPT1 ADRPT0+4			//0x304
#define ADRPPI ADRPT0+0x08		//0x308
#define ADRRG ADRPT0+0x0c		//0x30c
#define ADRPPI2 ADRPT0+0x10	//0x310
#define ADRPT2 ADRPT0+0x14		//0x314
#define ADRCMOS ADRPT0+0x18	//0x318
#define LRG ADRPT0+0x1c			//0x31c
#define PUMP_ON 0x01				// OR
#define PUMP_OFF 0xfe				// AND
#define SHUT_ON 0x02				// OR
#define SHUT_OFF 0xfd				// AND
#define STEP_ON 0xfe				// AND
#define STEP_OFF 0x01				// OR
/* CURSOR_ON/CURSOR_OFF defined in compat.h */
#define ESC 27
#define ENTER 13
#define COLDLG 3
#define COLBK 56
#define COLBKL 59
#define COL_ON 60
#define STEP_ON 0xfe		// AND
#define STEP_OFF 0x01	// OR
#define PULS_ON 0xbf		// AND
#define PULS_OFF 0x40	// OR
#define PR_OPEN 0x7f		// AND
#define PR_CLOSE 0x80	// OR
#define X0 160				// Picture:Xleft
#define Y0 450				// Picture:Ydown
/*--------------------------------------------------------
	btc_***[]:	1 parameter:		1 - button
											3 - ctlbt
											4 - special
					2 parameter:		0 - press+autorepeat
											1 - release
					next parameters:	x_left, y_top, dx, dy
---------------------------------------------------------*/

/* v2.77: Main screen - removed F6 Statist (v2.70) and F7 Info (v2.77)
   F9 XYZ moved into right column at old F7 slot */
#define BNM_SCR 7
static char *bnam_scr[] = {"F9 XYZ","F1 Config","F2 Convert",
	"F3 DatLoad","F4 GlsLoad","F5 Start",
	"F10 Exit"};
static int btc_scr[] = {
	1,1,520,380,90,18,
	1,1,520,210,90,18,
	1,1,520,240,90,18,
	1,1,520,270,90,18,
	1,1,520,320,90,18,
	1,1,520,350,90,18,
	1,1,520,430,90,18};

/* v2.77: Config dialog
   v2.70: Gate delay +/- (was unused Delay), X button for positions
   v2.71: Las.puls button removed; Pump/Gate toggles replace Las.adjust
   v2.73: dT display
   v2.77: sh_delay display
   Total: 28 + 9*gl_nmb */
#define BNM_CFG 30		// 30 + 9*gl_nmb
static char *bnam_cfg[] = {"Ok","Cancel","Load .cfg",
	"Save .cfg","+","-","+","-","+","-","S+","S-","X+","X-","Y+",
	"Y-","Z+","Z-","1","9","protect.open","gate delay",
	"laser pump","work ptr","constant","variable","Reset","X",
	"Shot","metal mode",
	"","","","","","","","",""};
static int btc_cfg[] = {
	1,1,300,386,90,18,	// 0  Ok
	1,1,400,386,90,18,	// 1  Cancel
	1,1,120,125,90,18,	// 2  Load .cfg
	1,1,130,386,90,18,	// 3  Save .cfg
	1,0,345,132,22,14,	// 4  + las.puls period
	1,0,345,149,22,14,	// 5  -
	1,0,345,177,22,14,	// 6  + gate delay (v2.70)
	1,0,345,194,22,14,	// 7  -
	1,0,345,237,22,14,	// 8  + step freq.
	1,0,345,254,22,14,	// 9  -
	1,0,465,132,22,14,	// 10 S+
	1,0,465,149,22,14,	// 11 S-
	1,0,465,177,22,14,	// 12 X+
	1,0,465,194,22,14,	// 13 X-
	1,0,465,222,22,14,	// 14 Y+
	1,0,465,239,22,14,	// 15 Y-
	1,0,465,267,22,14,	// 16 Z+
	1,0,465,284,22,14,	// 17 Z-
	3,0,120,90,10,10,		// 18 1
	3,0,120,105,10,10,	// 19 9
	3,0,120,160,10,10,	// 20 protect open
	3,0,120,185,10,10,	// 21 gate delay (v2.71)
	3,0,120,200,10,10,	// 22 laser pump (v2.71)
	3,0,400,90,10,10,		// 23 work ptr
	3,0,280,280,10,10,	// 24 constant
	3,0,280,295,10,10,	// 25 variable
	1,1,180,320,46,14,	// 26 Statistics reset (v2.78: wider)
	1,1,335,344,22,14,	// 27 X (clear positions, v2.70)
	1,1,130,320,46,14,	// 28 Shot (v2.78: direct PC6 pulse)
	3,0,120,225,10,10,	// 29 metal mode (v2.78)
	4,0,280,315,12,12,	// 30 pos 1
	4,0,296,315,12,12,	// 31 pos 2
	4,0,312,315,12,12,	// 32 pos 3
	4,0,280,331,12,12,	// 33 pos 4
	4,0,296,331,12,12,	// 34 pos 5
	4,0,312,331,12,12,	// 35 pos 6
	4,0,280,347,12,12,	// 36 pos 7
	4,0,296,347,12,12,	// 37 pos 8
	4,0,312,347,12,12};	// 38 pos 9

#define BNM_OPN 12		// 12 + flag + k
static char *bnam_opn[] = {"Ok","Cancel","up","dn","","","up","dn",
	"","","*.bft","*.cft","*.asc","*.bmp","","",""};
static int btc_opn[] = {
	1,1,370,386,90,18,	// Ok
	1,1,470,386,90,18,	// Cancel
	1,0,225,175,22,14,	// subdir up
	1,0,225,286,22,14,	// subdir dn
	4,0,110,180,110,120,	// directory area
	4,1,110,330,110,17,	// ChDisk area
	1,0,380,175,22,14,	// up
	1,0,380,286,22,14,	// dn
	4,0,265,180,110,120,	// directory area
	4,0,420,175,110,17,	// file name input
	3,0,280,330,10,10,	// *.bft
	3,0,280,345,10,10,	// *.cft
	3,0,280,315,10,10,	// *.asc
	3,0,280,360,10,10,	// *.bmp
	4,0,450,232,60,18,	// dx
	4,0,450,257,60,18,	// dy
	4,0,450,282,60,18};	// dz

#define BNM_ED 31
static char *bnam_ed[] = {"Cancel","Data Save","Data Load","F9 XYZ",
	"0->Center","up","<-","dn","->","+","-","+","-","+","-","+","-","Sort",
	"","","","","","X-mirror","Dimensions","C->Center","invert","","","",""};
static int btc_ed[] = {
	1,1,500,438,90,18,	// Cancel
	1,1,391,438,90,18,	// Data Save
	1,1,100,438,90,18,	// Data Load
	1,1,500,250,90,18,	// View XYZ
	1,1,500,384,90,18,	// 0->Center
	1,0,534,348,22,14,	// up
	1,0,508,358,22,14,	// <-
	1,0,534,365,22,14,	// dn
	1,0,560,358,22,14,	// ->
	1,0,565,77,22,14,		// + n
	1,0,565,94,22,14,		// - n
	1,0,565,113,22,14,	// + Xsize
	1,0,565,130,22,14,	// - Xsize
	1,0,565,149,22,14,	// + Ysize
	1,0,565,166,22,14,	// - Ysize
	1,0,565,185,22,14,	// + Zsize
	1,0,565,202,22,14,	// - Zsize
	1,1,294,438,90,18,	// sort
	4,1,500,85,60,16,		// nglass
	4,1,500,121,60,16,	// Xsize
	4,1,500,157,60,16,	// Ysize
	4,1,500,193,60,16,	// Zsize
	4,1,500,54,76,16,		// Glass
	3,0,505,234,10,10,	// Mirror
	1,1,197,438,90,18,	// Dimensions
	1,1,500,407,90,18,	// C->Center
	3,0,505,221,10,10,	// Invert
	4,1,527,274,60,16,	// dT
	4,1,527,292,60,16,	// dL
	4,1,527,310,60,16,	// dR
	4,1,527,328,60,16};	// dB

#define BNM_GLOAD 3
static char *bnam_gload[] = {"PgUp Up","PgDn Down","Cancel"};
static int btc_gload[] = {
	1,1,300,207,90,18,	// Up
	1,1,300,339,90,18,	// Down
	1,1,300,376,90,18};	// Cancel

#define BNM_GSEL 5
static char *bnam_gsel[] = {"Ok","Cancel","","up","dn"};
static int btc_gsel[] = {
	1,1,300,386,90,18,	// Ok
	1,1,400,386,90,18,	// Cancel
	4,0,120,220,130,120,	// type area
	1,0,255,215,22,14,	// up
	1,0,255,326,22,14};	// dn

/* v2.70: Start dialog - removed ++ and -- buttons, added direct input
   v2.70: Point number direct input area added */
#define BNM_STRT 14
static char *bnam_strt[] = {" Ok"," Cancel","+","-",
	"Beginning","Point number","Continuation","Saved in CMOS",
	"End sensors","Drawing check","Stop","Coord.reboot/continuation",
	"Ignore",""};
static int btc_strt[] = {
	1,1,300,376,90,18,	// 0  Ok
	1,1,400,376,90,18,	// 1  Cancel
	1,0,345,140,22,14,	// 2  +
	1,0,345,160,22,14,	// 3  -
	3,0,120,130,10,10,	// 4  Beginning
	3,0,120,150,10,10,	// 5  Point number
	3,0,120,170,10,10,	// 6  Continuation
	3,0,120,190,10,10,	// 7  Saved in CMOS
	3,0,120,225,10,10,	// 8  End sensors
	3,0,120,245,10,10,	// 9  Drawing check
	3,0,135,300,10,10,	// 10 Stop
	3,0,135,320,10,10,	// 11 Ptr auto reboot
	3,0,135,340,10,10,	// 12 Ignore
	4,0,280,150,60,18};	// 13 Point number input (v2.70)

/* v2.70: Statistics removed */

#define BNM_MSG 2
static char *bnam_msg[] = {"Ok","No","Nx"};
static int btc_msg[] = {
	1,1,310,322,22,14,	// Ok
	1,1,340,322,22,14,	// No
	1,1,266,322,22,14};	// Next

#define BNM_MSG1 1
static char *bnam_msg1[] = {"Ok"};
static int btc_msg1[] = {
	1,1,269,322,22,14};	// Ok (centered)

/* v2.77: Info dialog removed, version shown in MainScreen */

#define BNM_SORT 9
static char *bnam_sort[] = {"Close","Off","0.5mm layers","K*dz",
	"+","-","+","-","Sort/time"};
static int btc_sort[] = {
	1,1,290,376,90,18,	// Close
	3,0,130,210,10,10,	// Off
	3,0,130,230,10,10,	// Sort1
	3,0,130,250,10,10,	// Sort2
	1,0,355,254,22,14,	// + K1
	1,0,355,272,22,14,	// - K1
	1,0,355,294,22,14,	// + K2
	1,0,355,312,22,14,	// - K2
	1,1,290,343,90,18};	// Sort/time

#define BNM_DIM 14
static char *bnam_dim[] = {"Cancel","+","-","Ok","from 0",
	"from centre","","","+","-","+","-","+","-"};
static int btc_dim[] = {
	1,1,290,376,90,18,	// Cancel
	1,0,255,214,22,14,	// + K
	1,0,255,232,22,14,	// - K
	1,1,190,376,90,18,	// Ok
	3,0,130,305,10,10,	// 0 axis
	3,0,130,325,10,10,	// glass center
	3,0,130,225,10,10, 	// Kx=Ky=Kz
	3,0,130,265,10,10,	// different
	1,0,365,214,22,14,	// + KX
	1,0,365,232,22,14,	// - KX
	1,0,365,254,22,14,	// + KY
	1,0,365,272,22,14,	// - KY
	1,0,365,294,22,14,	// + KZ
	1,0,365,312,22,14};	// - KZ

static unsigned short scr_cur_masks[] = {
	0x7fff, 0x3fff, 0x1fff, 0x0fff,		//AND mask
	0x07ff, 0x03ff, 0x01ff, 0x00ff,
	0x007f, 0x003f, 0x03ff, 0x01ff,
	0x31ff, 0x70ff, 0xf8ff, 0xf8ff,
	0x0000, 0x0000, 0x4000, 0x6000,		//XOR mask
	0x7000, 0x7800, 0x7c00, 0x7e00,
	0x7f00, 0x7800, 0x6800, 0x4c00,
	0x0400, 0x0600, 0x0200, 0x0000};

static char pattern[][8] = {
	{(char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF},
	{(char)0xF7, (char)0xFF, (char)0xFF, (char)0xFF, (char)0x7F, (char)0xFF, (char)0xFF, (char)0xFF},
	{(char)0xF7, (char)0xFF, (char)0x7F, (char)0xFF, (char)0xF7, (char)0xFF, (char)0x7F, (char)0xFF},
	{(char)0xDD, (char)0xFF, (char)0x77, (char)0xFF, (char)0xDD, (char)0xFF, (char)0x77, (char)0xFF},
	{(char)0xDD, (char)0x7F, (char)0xDD, (char)0xF7, (char)0xDD, (char)0x7F, (char)0xDD, (char)0xF7},
	{(char)0xDD, (char)0x77, (char)0xDD, (char)0x77, (char)0xDD, (char)0x77, (char)0xDD, (char)0x77},
	{(char)0x55, (char)0x77, (char)0xDD, (char)0x77, (char)0x55, (char)0x77, (char)0xDD, (char)0x77},
	{(char)0xAA, (char)0xDD, (char)0xAA, (char)0x77, (char)0xAA, (char)0xDD, (char)0xAA, (char)0x77},
	{(char)0xAA, (char)0x57, (char)0xAA, (char)0x75, (char)0xAA, (char)0x57, (char)0xAA, (char)0x75},
	{(char)0xAA, (char)0x55, (char)0xAA, (char)0x57, (char)0xAA, (char)0x55, (char)0xAA, (char)0x75},
	{(char)0xAA, (char)0x55, (char)0xAA, (char)0x55, (char)0xAA, (char)0x55, (char)0xAA, (char)0x55},
	{(char)0xAA, (char)0x54, (char)0xAA, (char)0x45, (char)0xAA, (char)0x54, (char)0xAA, (char)0x45},
	{(char)0x55, (char)0x88, (char)0x55, (char)0x22, (char)0x55, (char)0x88, (char)0x55, (char)0x22},
	{(char)0x88, (char)0xAA, (char)0x88, (char)0x22, (char)0x88, (char)0xAA, (char)0x88, (char)0x22},
	{(char)0x88, (char)0x22, (char)0x88, (char)0x22, (char)0x88, (char)0x22, (char)0x88, (char)0x22},
	{(char)0x88, (char)0x20, (char)0x88, (char)0x02, (char)0x88, (char)0x20, (char)0x88, (char)0x02},
	{(char)0x88, (char)0x00, (char)0x22, (char)0x00, (char)0x88, (char)0x00, (char)0x22, (char)0x00},
	{(char)0x80, (char)0x00, (char)0x08, (char)0x00, (char)0x80, (char)0x00, (char)0x08, (char)0x00},
	{(char)0x80, (char)0x00, (char)0x00, (char)0x00, (char)0x08, (char)0x00, (char)0x00, (char)0x00},
	{(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00}};

static unsigned char flint[] = {
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
0xFF,0xFF,0xE0,0x3F,0xF9,0xFF,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

static unsigned short fico[] = {
	0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
	0x0000, 0x0400, 0x0014, 0x0000, 0x0000, 0x1500, 0x0014, 0x0000,
	0x0000, 0x1540, 0x0054, 0x0000, 0x0000, 0x1554, 0x0054, 0x0000,
	0x0000, 0x0555, 0x4150, 0x0000, 0x0000, 0x0555, 0x5550, 0x0000,
	0x0000, 0x0155, 0x5550, 0x0000, 0x0000, 0x0005, 0x5555, 0x0000,
	0x0000, 0x0000, 0x1555, 0x5400, 0x0000, 0x0000, 0x5545, 0x5550,
	0x0000, 0x0001, 0x5540, 0x0554, 0x0000, 0x0005, 0x5500, 0x0000,
	0x0000, 0x0005, 0x5500, 0x0000, 0x0000, 0x0005, 0x5500, 0x0000,
	0x2800, 0x0001, 0x5400, 0x0000, 0x2A00, 0xA000, 0x0080, 0x0000,
	0x2A02, 0xA8A8, 0xA8A0, 0x0A00, 0x2A02, 0xA0A8, 0xA8A8, 0x2A80,
	0x2A02, 0xA0A8, 0xA8A8, 0x2A00, 0x2A02, 0xA0A8, 0xA8A8, 0x2A00,
	0xAAA2, 0xA2A8, 0xA8A8, 0xAA80, 0x2AA2, 0xA028, 0x2AA8, 0x2AA0,
	0x2A02, 0xA000, 0x00A0, 0x2A00, 0x2A22, 0xA0A0, 0x0000, 0x2A00,
	0x0AAA, 0xA0A8, 0x0000, 0x2800, 0x02A0, 0xA0A0, 0x0000, 0x0000};

int f_demo;
int f_bcab;
int f_bca;
int f_bc;
int xptr,yptr,zptr;
int do_ptr;
int f_ptr;
int xcur,ycur,zcur;
int f_data;
int f_xyz;
long start_nmb;
long lastn;
long nmax;
int l_period;
int gate_delay;					// v2.70: Gate delay in 10 mcs units
int step_freq;
int f_const;
unsigned int step;
char glstype[9];
double nglas;
int xsize,ysize,zsize;
int xofs,yofs,zofs;
int gl_nmb;
unsigned int glpos9;
unsigned int nmrpt[10];			// v2.74: merged first/next counters -> 10
int d_check;
// int rpt_active;				// REMOVED: reconstruction error, binary uses errnmb here
int f_noise;
int f_sort;
int sK1, sK2;
int nmb_pbt;
int pkey;
int tout;
int dT;							// v2.73: CPU time correction in ms
int sh_delay;						// v2.77: EM shutter delay in ms
int f_gate;						// v2.71: gate on/off state
int f_metal;						// v2.78: metal mode on/off
extern char path[];
char wrkpath[MAXPATH];
char wrkfile[13];
unsigned long ulMax;
short *iTabl;
unsigned int dx,dy,dz;
int fcdim,kdim;
int feqk,kxdim,kydim,kzdim;
void *bitmapmsg;
void *bgmap;
extern int coord[2];
extern char mname[100][13];
extern char dname[50][13];
char gtype[50][16];
extern int lastf;
extern int lastd;
int xmin,xmax,ymin,ymax,zmin,zmax;
unsigned int errnmb;
int k_old,p_old;
unsigned long ulFlash;
unsigned long ulService;

void set_gr_cursor(int hot_spot_row, int hot_spot_column,
		unsigned short *scr_cur_masks);
void ms_init(void);
int ms_key_cmd(int f_beep);
void beep(int tone, int duration);
void out_time(int newt);
void CurDir(void);
int rdfile(char filename[], char masname[], unsigned int nmb);
int wrfile(char filename[], char masname[], unsigned int nmb);
void RdCfg(int gl_nmber);
void FlashRd(void);
void FlashWr(void);
int rddir(char f_namext[]);
int rdasc_t(char filename[]);
int rdgls(void);
long rdcft_t(char filename[]);
int wrasc(char filename[]);
int wrt_cft(char filename[]);
int wrt_bft(char filename[]);
long rdbft_t(char filename[]);
long rdbmp(char filename[]);
int pi_ini(void);
void program_pt2(int period, unsigned char gate);
unsigned int read_pt2(void);

void sh_open(unsigned int pos);
void sh_close(void);
int process(void);
int move_sen(int dir);
int move(int x, int y, int z);
int lpuls_metal(int flag);

void button(int btc[], int nmb, char buttxt[]);
void buttonp(int btc[], int nmb, char buttxt[]);
void ctlbt(int btxl, int btyl, int colctl, char ctltxt[]);
int pressbt(int btc[], int nmb);
int msgbox(char msgtxt[], int more, int f_beep=0);
void msgbox1(char msgtxt[]);
int msg(int msgx, int msgy, int onoff, char msgtxt[]);
int InrDcr(int param, int pmin, int pmax, int pstep, int updn);
void sw_ctl(int flag, int param, int xpos, int ypos, int col);
int dlgopen(char destnm[], char dlgnm[], int fasc);
int disksel(int nmb);
void WndBkgr(int xl,int yt,int xr,int yb, int col,char txt[]);
int dlgcfg(void);
int dlged(void);
void chdiska(void);
long inp_dig(int xl, int yt, double min, double max, int ax);
void glload(int direct);
int dlgload(void);
int gselect(void);
int dlgstart(void);
void ClearRpt(void);
void mainscr(int all);
void show_reit(int mode);
void glaspos(int xl, int yt, int cw);
void drawfl(void);
void draw(int flag, int all);
void DrawPix(int hp,int hs, int vp, int vs, int color);
int draw_bt(int btc[], char *bnam[], int nmb);
int dlgsort(void);
int sort(void);
int sort2(void);
long cros(unsigned long k1, unsigned long k2);
void swap(unsigned long k1, unsigned long k2);
int minmax(void);
unsigned int scan_ms(int btc[], char *bnam[], int nbt, int f_beep=0);
void progbar(long nmb_max, long nmb, int set, int xl, int yt);
void htime(char tmpstr[]);
int dlgdim();

#endif
