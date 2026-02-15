/*********************************************************************
	file mskeyc.cpp
	iB
	32-bit DOS/4GW port (Open Watcom)

		void out_time(int newt)
		void set_gr_cursor(int hot_spot_row, int hot_spot_column,
				unsigned short *scr_cur_masks)
		void ms_init(void)
		void ms_state(struct MOUSE_STATE * current_state)
		void ms_move(int h_pos, int v_pos)
		int ms_release(struct MOUSE_STATE * current_state)
		void beep(int tone, int duration)       // Hz,ms
		int ms_key_cmd(void)
*********************************************************************/
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <i86.h>
#include <time.h>
#include <string.h>

#include "compat.h"
#include "bgi32.h"

#define ESC 27
#define ENTER 13
#define COLBKL 59


union REGS r;
struct SREGS s;
union KEY {
	int i;
	char c[2];
	} key;
struct MOUSE_STATE {
	char buttons;
	int h_pos;
	int v_pos;
	};
int coord[2];   // coord[0] - hor., coord[1] - vert.
int sts_old, nmb_rpt;
long t_old;


void out_time(int newt) {
	time_t t;
	long t_new; char strtime[25]; int old_color, old_color_bk;
	struct fillsettingstype fillinf;

	t_new=time(&t);
	if((t_old != t_new)||(!newt)) {
		t_old=t_new; strcpy(strtime,ctime(&t)+11); strtime[8]=0;
		old_color=getcolor(); setcolor(COLBKL);
		getfillsettings(&fillinf); old_color_bk=fillinf.color;
		setfillstyle(1,BLUE); bar(20,7,84,15);
		outtextxy(20,7,strtime); setcolor(old_color);
		setfillstyle(1,old_color_bk);
		}
	}


/*
 * set_gr_cursor — INT 33h AX=9 (Set Graphics Cursor Block).
 *
 * In DOS/4GW protected mode, the mouse driver is a real-mode TSR.
 * INT 33h AX=9 expects ES:DX to be a REAL-MODE segment:offset pair
 * pointing to the 64-byte cursor mask data.
 *
 * Strategy: use DPMI INT 31h AX=0100h to allocate a real-mode DOS
 * memory block, copy the 64-byte mask there, then call INT 33h
 * via DPMI simulate-real-mode-interrupt (INT 31h AX=0300h).
 */
void set_gr_cursor(int hot_spot_row, int hot_spot_column,
		unsigned short *scr_cur_masks) {

	/* In DOSBox-X / DOS4GW, setting custom graphics cursor via DPMI
	 * real-mode interrupt simulation causes GPF. Use default cursor instead.
	 * The mouse will work fine with the standard arrow cursor. */
	(void)hot_spot_row;
	(void)hot_spot_column;
	(void)scr_cur_masks;
	return;

#if 0  /* Original DPMI-based implementation — disabled for DOSBox compatibility */
	union REGS  regs;
	struct SREGS sregs;

	/* --- 1. Allocate a DOS real-mode memory block (64 bytes = 4 paragraphs) */
	regs.w.ax = 0x0100;      /* DPMI: Allocate DOS Memory */
	regs.w.bx = 4;           /* 4 paragraphs = 64 bytes   */
	int386x(0x31, &regs, &regs, &sregs);
	if(regs.x.cflag) return; /* allocation failed — just skip cursor shape */

	unsigned short rm_seg = (unsigned short)regs.w.ax;  /* real-mode segment  */
	unsigned short rm_sel = (unsigned short)regs.w.dx;  /* PM selector to use */

	/* --- 2. Copy 64 bytes of cursor mask data using the PM selector       */
	/*    DOS/4GW maps real-mode memory linearly: linear addr = segment<<4 */
	unsigned short *dst = (unsigned short *)((unsigned long)rm_seg << 4);
	for(int i = 0; i < 32; i++) dst[i] = scr_cur_masks[i];

	/* --- 3. Set up DPMI "real mode call structure" and simulate INT 33h   */
	struct {                       /* DPMI real-mode call structure (50 bytes) */
		unsigned long  edi, esi, ebp, reserved;
		unsigned long  ebx, edx, ecx, eax;
		unsigned short flags, es, ds, fs, gs;
		unsigned short ip, cs, sp, ss;
	} rmcall;
	memset(&rmcall, 0, sizeof(rmcall));

	rmcall.eax = 0x0009;
	rmcall.ebx = (unsigned long)hot_spot_column;
	rmcall.ecx = (unsigned long)hot_spot_row;
	rmcall.edx = 0;               /* offset 0 within the allocated block     */
	rmcall.es  = rm_seg;          /* real-mode segment of cursor mask data    */

	memset(&regs, 0, sizeof(regs));
	memset(&sregs, 0, sizeof(sregs));

	regs.w.ax = 0x0300;           /* DPMI: Simulate Real Mode Interrupt      */
	regs.w.bx = 0x0033;           /* interrupt number = 33h                  */
	regs.w.cx = 0;                /* words to copy from PM stack (0)         */
	segread(&sregs);              /* get current DS selector for flat model   */
	regs.x.edi = (unsigned int)&rmcall;  /* flat offset of call structure    */
	int386x(0x31, &regs, &regs, &sregs);

	/* --- 4. Free the DOS memory block                                     */
	regs.w.ax = 0x0101;           /* DPMI: Free DOS Memory                   */
	regs.w.dx = rm_sel;
	int386(0x31, &regs, &regs);
#endif /* disabled DPMI cursor */
	}


void ms_init(void) {
	union REGS rr;
	rr.w.ax = 0;
	int386(0x33, &rr, &rr);
	if(rr.w.ax == 0) {
		puts("no mouse !");
		exit(-1);
		}
	}


void ms_state(struct MOUSE_STATE * current_state) {
	union REGS rr;
	rr.w.ax = 3;
	int386(0x33, &rr, &rr);
	current_state->buttons = (char)rr.w.bx;
	current_state->h_pos = (int)rr.w.cx;
	current_state->v_pos = (int)rr.w.dx;
	}


void ms_move(int h_pos, int v_pos) {
	union REGS rr;
	rr.w.ax = 4;
	rr.w.cx = (unsigned short)h_pos;
	rr.w.dx = (unsigned short)v_pos;
	int386(0x33, &rr, &rr);
	}


int ms_release(struct MOUSE_STATE * current_state) {
	union REGS rr;
	rr.w.ax = 6;
	rr.w.bx = (unsigned short)current_state->buttons;
	int386(0x33, &rr, &rr);
	current_state->h_pos = (int)rr.w.cx;
	current_state->v_pos = (int)rr.w.dx;
	return (int)rr.w.bx;
	}


void beep(int tone, int duration) {  // Hz,ms
	sound(tone); delay(duration); nosound();
	}


int ms_key_cmd(void) {
	struct MOUSE_STATE cur_state; union KEY key; int i;

	CURSOR_ON();
	while(1) {
		out_time(1); cur_state.buttons=0;
		if(ms_release(&cur_state)) {
			sts_old=0; nmb_rpt=0; CURSOR_OFF(); return 1;
			}
		ms_state(&cur_state);
		if(cur_state.buttons == 0x01) {							// left button
			if(sts_old == 0) {
				sts_old=1; coord[0]=cur_state.h_pos; coord[1]=cur_state.v_pos;
				CURSOR_OFF(); return 0;
				}
			else {
				if(!nmb_rpt) {
					nmb_rpt=1;
					for(i=0; i<50; i++) {
						delay(10); cur_state.buttons=0;
						if(ms_release(&cur_state)) {
							sts_old=0; nmb_rpt=0; CURSOR_OFF(); return 1;
							}
						}
					}
				delay(10);
				ms_state(&cur_state);
				if(cur_state.buttons == 0x01) {
					coord[0]=cur_state.h_pos; coord[1]=cur_state.v_pos;
					CURSOR_OFF(); return 0;
					}
				}
			}
		if((key.i = bioskey(1)) != 0) {
			key.i = bioskey(0);
			if(key.c[0] == 0) {
				if(key.c[1] == 75) cur_state.h_pos-=8;					// left
				else if(key.c[1] == 72) cur_state.v_pos-=8;			// up
				else if(key.c[1] == 77) cur_state.h_pos+=8;			// right
				else if(key.c[1] == 80) cur_state.v_pos+=8;			// down
				else if((key.c[1]>58)&&(key.c[1]<69)) {				// F1-F10
					CURSOR_OFF();
					return(key.c[1]);
					}
				else beep(1000, 100);
				ms_move(cur_state.h_pos,cur_state.v_pos);
				}
			else if(key.c[0] == 27) {CURSOR_OFF(); return(ESC);}	// ESC
			else if(key.c[0] == 13) {										// Enter
				coord[0]=cur_state.h_pos; coord[1]=cur_state.v_pos;
				CURSOR_OFF(); return(ENTER);
				}
			else beep(1000,100);
			}
		sts_old=0; nmb_rpt=0;
		}
	}
