/*********************************************************************
	file mskeyc.cpp
	iB
	ver.2.77 (reconstructed from v2.61 + changelog v2.61-v2.77)

		void out_time(int newt)
		void set_gr_cursor(int hot_spot_row, int hot_spot_column,
				unsigned int far *scr_cur_masks)
		void ms_init(void)
		void ms_state(struct MOUSE_STATE * current_state)
		void ms_move(int h_pos, int v_pos)
		int ms_release(struct MOUSE_STATE * current_state)
		void beep(int tone, int duration)       // Hz,ms
		int ms_key_cmd(void)

	Changes from v2.61:
	v2.75: Added f_beep support in ms_key_cmd() for prolonged alerts
	v2.76: Removed out_time() display - was causing missed laser pulses
	v2.77: Added PgUp/PgDn key handling in ms_key_cmd()
*********************************************************************/
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <bios.h>
#include <graphics.h>
#include <time.h>
#include <string.h>

#define CURSOR_ON()  _AX=1; geninterrupt(0x33);
#define CURSOR_OFF() _AX=2; geninterrupt(0x33);
#define ESC 27
#define ENTER 13
#define COLBKL 59

/* f_beep is now a parameter to ms_key_cmd, not a global */

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


/* v2.76: Removed time display entirely.
   "Убрал вывод текущего времени на мониторе совсем.
    Т.к. при обновлении - раз в секунду - регулярно пропускался
    один импульс лазера." */
void out_time(int newt) {
	/* v2.76: function body removed to prevent missed laser pulses */
	}


void set_gr_cursor(int hot_spot_row, int hot_spot_column,
		unsigned int far *scr_cur_masks) {
	r.x.ax=9; r.x.bx=hot_spot_column; r.x.cx=hot_spot_row;
	s.es=FP_SEG(scr_cur_masks); r.x.dx=FP_OFF(scr_cur_masks);
	int86x(0x33,&r,&r,&s);
	}


void ms_init(void) {
	r.x.ax=0; int86(0x33,&r,&r);
	if(r.x.ax == 0) {
		puts("no mouse !");
		exit(-1);
		}
	}


void ms_state(struct MOUSE_STATE * current_state) {
	r.x.ax=3; int86(0x33,&r,&r);
	current_state->buttons=r.x.bx;
	current_state->h_pos=r.x.cx; current_state->v_pos=r.x.dx;
	}


void ms_move(int h_pos, int v_pos) {
	r.x.ax=4; r.x.cx=h_pos; r.x.dx=v_pos; int86(0x33,&r,&r);
	}


int ms_release(struct MOUSE_STATE * current_state) {
	r.x.ax=6; r.x.bx=current_state->buttons; int86(0x33,&r,&r);
	current_state->h_pos=r.x.cx; current_state->v_pos=r.x.dx;
	return r.x.bx;
	}


void beep(int tone, int duration) {  // Hz,ms
	sound(tone); delay(duration); nosound();
	}


/* v2.75: Added f_beep support for prolonged sound alerts
   v2.77: Added PgUp(73)/PgDn(81) key returns via expanded range */
int ms_key_cmd(int f_beep) {
	struct MOUSE_STATE cur_state; union KEY key; int i;

	CURSOR_ON();
	while(1) {
		/* v2.75: periodic beep for critical messages */
		if(f_beep) { beep(2100, 70); beep(3000, 70); }

		cur_state.buttons=0;
		if(ms_release(&cur_state)) {
			sts_old=0; nmb_rpt=0; CURSOR_OFF(); return 1;
			}
		ms_state(&cur_state);
		if(cur_state.buttons == 0x01) {
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
			key.i=bioskey(0);
			if(key.c[0] == 0) {
				if(key.c[1] == 75) cur_state.h_pos-=8;					// left
				else if(key.c[1] == 72) cur_state.v_pos-=8;			// up
				else if(key.c[1] == 77) cur_state.h_pos+=8;			// right
				else if(key.c[1] == 80) cur_state.v_pos+=8;			// down
				/* v2.77: expanded range covers F1-F10 + PgUp/PgDn/Home/End */
				else if((key.c[1]>58)&&(key.c[1]<82)) {				// scan 59-81
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
