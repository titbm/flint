/*********************************************************************
	file mskeyc.cpp
	iB
		void out_time(int newt)
		void set_gr_cursor(int hot_spot_row, int hot_spot_column,
				unsigned int far *scr_cur_masks)
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
#include <bios.h>
#include <graphics.h>
#include <time.h>
#include <string.h>

#define CURSOR_ON()  _AX=1; geninterrupt(0x33);
#define CURSOR_OFF() _AX=2; geninterrupt(0x33);
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


int ms_key_cmd(void) {
	struct MOUSE_STATE cur_state; union KEY key; int i;

	CURSOR_ON();
	while(1) {
		out_time(1); cur_state.buttons=0;
		if(ms_release(&cur_state)) {
			sts_old=0; nmb_rpt=0; CURSOR_OFF(); return 1;	// кн.мыши отпущена
			}
		ms_state(&cur_state);
		if(cur_state.buttons == 0x01) {							// left button
			if(sts_old == 0) {
				sts_old=1; coord[0]=cur_state.h_pos; coord[1]=cur_state.v_pos;
				CURSOR_OFF(); return 0;								// кнопка мыши нажата
				}
			else {
				if(!nmb_rpt) {
					nmb_rpt=1;
					for(i=0; i<50; i++) {   						// delay for 1 repeat
						delay(10); cur_state.buttons=0;
						if(ms_release(&cur_state)) {
							sts_old=0; nmb_rpt=0; CURSOR_OFF();	return 1; // отпущена
							}
						}
					}
				delay(10);								// delay for autorepeat of mouse
				ms_state(&cur_state);
				if(cur_state.buttons == 0x01) {
					coord[0]=cur_state.h_pos; coord[1]=cur_state.v_pos;
					CURSOR_OFF(); return 0;							// кнопка мыши нажата
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

