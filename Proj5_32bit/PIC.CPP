/*********************************************************************
	pic.cpp
	iB
	32-bit DOS/4GW port (Open Watcom)

			int pi_ini(void)
			int lpuls(void)
			void sh_open(unsigned int pos)
			void sh_close(void)
			int process(void)
			int move_sen(int dir)
			int move(int x, int y, int z)
*********************************************************************/
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <i86.h>

#include "compat.h"
#include "bgi32.h"

#define ADRPT0 0x300
#define ADRPT1 ADRPT0+4			// 0x304
#define ADRPPI ADRPT0+8			// 0x308
#define ADRRG ADRPT0+0x0c		// 0x30c
#define ADRPPI2 ADRPT0+0x10	// 0x310
#define ADRPT2  ADRPT0+0x14	// 0x314
#define ADRCMOS ADRPT0+0x18	// 0x318
#define LRG     ADRPT0+0x1c	// 0x31c
/*-------------------------------------------------------------------
RG(out):	D0:	X.direction (0 - negativ, 1 - positiv)
			D1:	Y.direction (0 - negativ, 1 - positiv)
			D2:	Z.direction (0 - negativ, 1 - positiv)
			D3:	X.enable (D3 = 1)
			D4:	Y.enable (D4 = 1)
			D5:	Z.enable (D5 = 1)
			D6:	-
			D7:	OSC.enable (D7 = 0)
PPI:	PA(out):	PA0-PA7:	K1 ( =7...255)
		PB(inp):	PB0-PB5:	endSENSORS (0 - endSENSOR on, 1 - off)
					PB6:		"IRQ2"(1 - event)
					PB7:		"IRQ3"(1 - event)
		PC(out):	PC0:	stepMOTORS (0 - on, 1 - off)
					PC1:	ctl.1: endSENSORS(0-enable,1-reset)
					PC2:	ctl.2
					PC3:	ctl.3
					PC4:	ctl.4
					PC5:	LASER (0 - disable, 1 - enable)
					PC6:	LASERpuls (0 - on, 1 - off)
					PC7:	PROTECT (0 - open, 1 - close)
PT0:	ch.0: 	K2x ( =2-65535)
		ch.1: 	Xdistance ( =1-65535)
		ch.2: 	K2z ( =2-65535)
PT1:	ch.0: 	K2y ( =2-65535)
		ch.1: 	Ydistance ( =1-65535)
		ch.2: 	Zdistance ( =1-65535)
PPI2:	PA0..7,PC0,PC1(inp):	FOS1..10
		PC2,PC3(inp):			reserved
		PB0..7,PC4..6(out):	shutter1..10
		PC7(out):				reserved
PT2:	ch.0:		Laser Frequency (Tlas = K1*10mks  655ms max)
		ch.1:		EOShutt-Pump Delay (Tsh = K2*10mks)
		ch.2:		Global Delay (K3*10mks)
CMOS(out):		CMOS counter reset
CMOS+1(out):	CMOS counter increment
CMOS+2(inp):	CMOS counter low byte read
CMOS+3(inp):	CMOS counter high byte read
LRG(out):		D0=1:	Laser Pumping Enable, PowerOn|Reset: D0=0
					D1=1:	Laser EOShutter Enable, PowerOn|Reset: D1=0
--------------------------------------------------------------------*/
#define XUP 0x01			// OR
#define XDOWN 0xfe		// AND
#define YUP 0x02			// OR
#define YDOWN 0xfd		// AND
#define ZUP 0x04			// OR
#define ZDOWN 0xfb		// AND
#define XON 0x08			// OR
#define XOFF 0xf7			// AND
#define YON 0x10			// OR
#define YOFF 0xef			// AND
#define ZON 0x20			// OR
#define ZOFF 0xdf			// AND
#define OSCON 0x7f		// AND
#define OSCOFF 0x80		// OR
#define PULS_ON 0xbf		// AND
#define PULS_OFF 0x40	// OR
#define PR_OPEN 0x7f		// AND
#define PR_CLOSE 0x80	// OR

#define ESC 27
#define COLBK 56
#define COLBKL 59
#define SH_TIME 50

#define CLC1 0x40			// Counter Latch Command
#define CLC2 0x80
#define PUMP_ON 0x01		// OR
#define PUMP_OFF 0xfe	// AND
#define SHUT_ON 0x2		// OR
#define SHUT_OFF 0xfd	// AND

extern int f_demo;
extern int xptr, yptr, zptr;
extern int do_ptr;
extern int f_ptr;
extern int xcur, ycur, zcur;
extern int f_xyz;
extern long start_nmb;
extern long lastn;
extern long nmax;
extern int l_period;
extern int step_freq;
extern int f_const;
extern unsigned int step;
extern double nglas;
extern int xsize, ysize, zsize;
extern short *iTabl;             /* 32-bit: short* flat pointer */
unsigned char ctlw;
extern int gl_nmb;
extern unsigned int glpos9;
extern unsigned int nmrpt[];
extern unsigned int errnmb;
extern int d_check;
extern int f_noise;
unsigned char LCtl;
unsigned int LPeriod;
unsigned char SDelay;
unsigned int Dly;
extern unsigned long ulFlash;

int msg(int msgx, int msgy, int onoff, char msgtxt[]);
int msgbox(char msgtxt[], int more);
void draw(int flag, int all);
void beep(int tone, int duration);
void out_time(int newt);
void progbar(long nmb_max, long nmb, int set, int xl, int yt);

int pi_ini(void);
int lpuls(void);
void sh_open(unsigned int pos);
void sh_close(void);
int move_sen(int dir);
int move(int x, int y, int z);


int pi_ini(void) {
	ctlw = (XUP|YUP|ZUP)&XOFF&YOFF&ZOFF&OSCON;
	outportb(ADRRG,ctlw);
	LCtl=0; outportb(LRG,LCtl);
	outportb(ADRPPI+3,0x82);	// PPI:mode0,PA-out,PB-inp,PC-out
	outportb(ADRPPI,150);		// K1=150:F1=100kHz
	outportb(ADRPPI+2,0xfd);	// stepM-off,endS-en.,las-en.,puls-off,protect
	outportb(ADRPPI+2,0xff);	// -"-,endS-reset,-"-,-"-,-"-
	outportb(ADRPPI+2,0xfc);	// stepM-on,endS-enable,-"-,-"-,-"-
	outportb(ADRPPI2+3,0x91);	// PPI2:mode0,PA,PC0...3-inp,PB,PC4...7-out
	outportb(ADRPPI2+1,0xff);	// PPI2:0xff->PB:EM1...8-off
	outportb(ADRPPI2+3,0x09);	// PPI2:1->PC4:EM9-off
	outportb(ADRPPI2+3,0x0b);	// PPI2:1->PC5:EM10-off
	outportb(ADRPPI2+3,0x0d);	// PPI2:1->PC6:EMCOM-off
	outportb(ADRPT0+3,0x34);	// PT0.ch.0:mode2,binary,lb,hb
	outportb(ADRPT0+3,0x78);	// PT0.ch.1:mode4,binary,lb,hb
	outportb(ADRPT0+3,0xb4);	// PT0.ch.2:mode2,binary,lb,hb
	outportb(ADRPT1+3,0x34);	// PT1.ch.0:mode2,binary,lb,hb
	outportb(ADRPT1+3,0x78);	// PT1.ch.1:mode4,binary,lb,hb
	outportb(ADRPT1+3,0xb8);	// PT1.ch.2:mode4,binary,lb,hb
	outportb(ADRPT2+3,0x34);	// PT2.ch.0:mode2,binary,lb,hb
	outportb(ADRPT2+3,0x7a);	// PT2.ch.1:mode5,binary,lb,hb
	outportb(ADRPT2+3,0xb8);	// PT2.ch.2:mode4,binary,lb,hb
	if((inportb(ADRPPI)!=150)||((inportb(ADRPPI+1)&0x3f)!=0x3f)) return 0;
	return 1;
	}


int lpuls(void) {
	unsigned int i,k,m,dsens,mask,wrkpos,shft;

	if(f_demo) {
		ulFlash++; return 1;
		}
	mask=(gl_nmb)? glpos9:0x0200;
	if(d_check && errnmb) {wrkpos=errnmb & mask; sh_open(wrkpos);}
	else wrkpos=mask;
	for(i=0; i<10; i++) {
		outportb(ADRPPI+2,inportb(ADRPPI+2)&PULS_ON);
		outportb(ADRPPI+2,inportb(ADRPPI+2)|PULS_OFF);
		ulFlash++; delay(1);
		if(!d_check) return 1;
		dsens=((unsigned int)inportb(ADRPPI2)+
					(unsigned int)inportb(ADRPPI2+2)*256)&0x03ff;
		wrkpos-=(dsens & wrkpos);
		if(!wrkpos) {
			if(i || errnmb) sh_open(mask);
			errnmb=0; return 1;
			}
		if(i != 5) {
			m=(!i)? 0:1;
			shft=0x0001;
			for(k=0; k<10; k++) {if(wrkpos & shft) nmrpt[2*k+m]+=1; shft*=2;}
			sh_open(wrkpos);
			if(l_period > SH_TIME) delay(l_period-SH_TIME);
			}
		}
	errnmb=wrkpos; return 0;
	}


void sh_open(unsigned int pos) {
	outportb(ADRPPI2+1,(unsigned char)(pos%256)^0xff);		// PB: EM1-EM8
	if(pos & 0x0100) outportb(ADRPPI2+3,0x08);				// PC4=0: EM9-on
	else outportb(ADRPPI2+3,0x09);
	if(pos & 0x0200) outportb(ADRPPI2+3,0x0a);				// PC5=0: EM10-on
	else outportb(ADRPPI2+3,0x0b);
	outportb(ADRPPI2+3,0x0c);										// PC6=0: EMCOM-on
	delay(SH_TIME); outportb(ADRPPI2+3,0x0d);					// PC6=1: EMCOM-off
	}


void sh_close(void) {
	outportb(ADRPPI2+1,0xff); outportb(ADRPPI2+3,0x09);	// PB0-PB7=1,PC4=1
	outportb(ADRPPI2+3,0x0b); outportb(ADRPPI2+3,0x0d);	// PC5,PC6=1
	}


int process(void) {
	long i; int xnew,ynew,znew,k; unsigned int gpos; char tmpstr[20];

	msg(160,80,1,"For STOP: press ESC");
	if(f_ptr || (!do_ptr)) {move_sen(0); do_ptr=1;}
	outportb(ADRPPI+2,inportb(ADRPPI+2)&PR_OPEN);				// Protect-open
	gpos=(gl_nmb)? glpos9:0x0200;
	sh_open(gpos);
	progbar(nmax,start_nmb,1,160,464);
	for(i=start_nmb; i<nmax; i++) {
		xnew=23500-xptr-iTabl[3*i];
		ynew=yptr+iTabl[3*i+1];
		znew=11000-zptr-zsize*10*(int)(1-1/nglas)-iTabl[3*i+2];
		if(!move(xnew,ynew,znew)) {
			outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
			sh_close(); msg(160,80,0,""); msgbox("KPU/End sens.error",0);
			return 0;
			}
a:		if(!lpuls()) {
			outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
			sh_close(); msg(160,80,0,"");
			k=msgbox("Check laser. Retry: Ok",1);
			if(!k) return 0;
			msg(160,80,1,"For STOP: press ESC");
			if(k == 1) goto a;
			errnmb=0;
			}
		outportb(ADRCMOS+1,0);
		draw(f_xyz, 0);
		lastn=i+1;
		setcolor(BLACK); setfillstyle(1,COLBKL); bar(31,176,86,192);
		ltoa(lastn,tmpstr,10); outtextxy(40,181,tmpstr);
		progbar(nmax,i,0,160,464);
		if(kbhit()) {
			if(getch() == ESC) {
				outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
				sh_close(); msg(160,80,0,""); return 0;
				}
			}
		}
	outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
	sh_close(); beep(1000,100); beep(2000,100); beep(1000,100);
	msg(160,80,0,""); msgbox("Ok.  TABLE END",0);
	lastn=0; return 1;
	}


int move_sen(int dir) {
	int done,fxy,fz; unsigned char stspb,tw;

	outportb(ADRPT0,0x64); outportb(ADRPT0,0);		// K2x=100: Fstep=1000Hz
	outportb(ADRPT0+1,0); outportb(ADRPT0+1,0x70);	// dX=28672(>Xscale)
	outportb(ADRPT1,0x64); outportb(ADRPT1,0);		// K2y=100: Fstep=1000Hz
	outportb(ADRPT1+1,0); outportb(ADRPT1+1,0x70);	// dY=28672(>Yscale)
	outportb(ADRPT0+2,0x64); outportb(ADRPT0+2,0);	// K2z=100: Fstep=1000Hz
	outportb(ADRPT1+2,0); outportb(ADRPT1+2,0x40);	// dZ=16384(>Zscale)
	if(!dir) {
		ctlw=(XON|YON|ZON|XUP)&YDOWN&ZDOWN&OSCON;
		tw=(ctlw|XUP)&XOFF&YOFF&ZOFF&YDOWN&ZDOWN&OSCON;
		}
	else {
		ctlw=(XON|YON|ZON|XUP|YUP)&ZDOWN&OSCON;
		tw=(ctlw|XUP|YUP)&XOFF&YOFF&ZOFF&ZDOWN&OSCON;
		}
	outportb(ADRRG,ctlw);
	if(!f_demo) {
		while(ctlw != tw) {
			stspb=inportb(ADRPPI+1);
			if((stspb & 0x03) != 0x03) ctlw=ctlw&XOFF;
			if((stspb & 0x0c) != 0x0c) ctlw=ctlw&YOFF;
			if((stspb & 0x30) != 0x30) ctlw=ctlw&ZOFF;
			outportb(ADRRG,ctlw); out_time(1);
			}
		}
	outportb(ADRPT0,0xc8); outportb(ADRPT0,0x00);
	outportb(ADRPT0+1,0xc8); outportb(ADRPT0+1,0x00);
	outportb(ADRPT1,0xc8); outportb(ADRPT1,0x00);
	outportb(ADRPT1+1,0xc8); outportb(ADRPT1+1,0x00);
	outportb(ADRPT0+2,0xc8); outportb(ADRPT0+2,0x00);
	outportb(ADRPT1+2,0xc8); outportb(ADRPT1+2,0x00);
	if(!dir) {ctlw=(XON|YON|ZON|YUP|ZUP)&XDOWN&OSCON; outportb(ADRRG,ctlw);}
	else {ctlw=(XON|YON|ZON|ZUP)&XDOWN&YDOWN&OSCON; outportb(ADRRG,ctlw);}
	fxy=1; fz=1; done=0;
	if(!f_demo) {
		while(!done) {
			stspb=inportb(ADRPPI+1);
			if(stspb & 0x80) {ctlw=ctlw&XOFF&YOFF; fxy=0;}
			if(stspb & 0x40) {ctlw=ctlw&ZOFF; fz=0;}
			outportb(ADRRG,ctlw);
			if((!fxy) && (!fz)) done=1;
			}
		}
	outportb(ADRRG,0x80);
	if(!dir) {xcur=23300; ycur=200; zcur=200;}
	else do_ptr=0;
	return 1;
	}


int move(int x, int y, int z) {
	int dx,dy,dz,fxy,fz,done; unsigned char stspb;
	long k2,k2min,k2max=65500; unsigned int i,t;

c:	i=0; t=0; fxy=0; fz=0; done=0;
	dx=x-xcur; dy=y-ycur; dz=z-zcur;
	k2=100000/step_freq; k2min=k2;
	if(dx) {
		if(!f_const) {
			k2=(l_period-3)*100/abs(dx);
			if(k2 < k2min) k2=k2min;
			if(k2 > k2max) k2=k2max;
			}
		outportb(ADRPT0,(unsigned char)(k2%256));
		outportb(ADRPT0,(unsigned char)(k2/256));
		outportb(ADRPT0+1,(unsigned char)(abs(dx)%256));
		outportb(ADRPT0+1,(unsigned char)(abs(dx)/256));
		ctlw=(dx>0)? ctlw|XUP|XON:(ctlw&XDOWN)|XON;
		i=(unsigned int)labs(dx*k2/100); fxy=1;
		}
	else ctlw=ctlw&XOFF;
	t=i;
	if(dy) {
		if(!f_const) {
			k2=(l_period-3)*100/abs(dy);
			if(k2 < k2min) k2=k2min;
			if(k2 > k2max) k2=k2max;
			}
		outportb(ADRPT1,(unsigned char)(k2%256));
		outportb(ADRPT1,(unsigned char)(k2/256));
		outportb(ADRPT1+1,(unsigned char)(abs(dy)%256));
		outportb(ADRPT1+1,(unsigned char)(abs(dy)/256));
		ctlw=(dy>0)? ctlw|YUP|YON:(ctlw&YDOWN)|YON;
		i=(unsigned int)labs(dy*k2/100); fxy=1;
		}
	else ctlw=ctlw&YOFF;
	if(t < i) t=i;
	if(dz) {
		if(!f_const) {
			k2=(l_period-3)*100/abs(dz);
			if(k2 < k2min) k2=k2min;
			if(k2 > k2max) k2=k2max;
			}
		outportb(ADRPT0+2,(unsigned char)(k2%256));
		outportb(ADRPT0+2,(unsigned char)(k2/256));
		outportb(ADRPT1+2,(unsigned char)(abs(dz)%256));
		outportb(ADRPT1+2,(unsigned char)(abs(dz)/256));
		ctlw=(dz>0)? ctlw|ZUP|ZON:(ctlw&ZDOWN)|ZON;
		i=(unsigned int)labs(dz*k2/100); fz=1;
		}
	else ctlw=ctlw&ZOFF;
	if(t < i) t=i;
	ctlw=ctlw&OSCON; outportb(ADRRG,ctlw);
	if((!dx)&&(!dy)&&(!dz)) goto b;
	if(!f_demo) {
		while(!done) {
			stspb=inportb(ADRPPI+1);
			if(fxy && ((stspb & 0x80)==0x80)) {ctlw=ctlw&XOFF&YOFF; fxy=0;}
			if(fz && ((stspb & 0x40)==0x40)) {ctlw=ctlw&ZOFF; fz=0;}
			outportb(ADRRG,ctlw);
			if((!fxy) && (!fz)) done=1;
			if((stspb & 0x3f) != 0x3f) {
				delay(1);
				stspb=inportb(ADRPPI+1);
				if((stspb & 0x3f) != 0x3f) goto a;
				else {
					if(f_noise == 2) goto a;
					if(f_noise == 1) {move_sen(0); goto c;}
					}
				}
			}
		}
b:	if(f_demo) delay(l_period-3);
	else if((l_period-3) > (int)t) delay(l_period-3-t);
	xcur=x; ycur=y; zcur=z; out_time(1); return 1;
a:	ctlw=ctlw&XOFF&YOFF&ZOFF;
	outportb(ADRRG,ctlw); fxy=0; fz=0;
	if((stspb & 0x03) != 0x03) {
		outportb(ADRPT0,0xc8); outportb(ADRPT0,0x00);
		outportb(ADRPT0+1,0xc8); outportb(ADRPT0+1,0x00);
		ctlw=(dx<0)? ctlw|XUP|XON:(ctlw&XDOWN)|XON; fxy=1;
		}
	if((stspb & 0x0c) != 0x0c) {
		outportb(ADRPT1,0xc8); outportb(ADRPT1,0x00);
		outportb(ADRPT1+1,0xc8); outportb(ADRPT1+1,0x00);
		ctlw=(dy<0)? ctlw|YUP|YON:(ctlw&YDOWN)|YON; fxy=1;
		}
	if((stspb & 0x30) != 0x30) {
		outportb(ADRPT0+2,0xc8); outportb(ADRPT0+2,0x00);
		outportb(ADRPT1+2,0xc8); outportb(ADRPT1+2,0x00);
		ctlw=(dz<0)? ctlw|ZUP|ZON:(ctlw&ZDOWN)|ZON; fz=1;
		}
	ctlw=ctlw&OSCON; outportb(ADRRG,ctlw); done=0;
	while(!done) {
		stspb=inportb(ADRPPI+1);
		if(fxy && ((stspb & 0x80) == 0x80)) {ctlw=ctlw&XOFF&YOFF; fxy=0;}
		if(fz && ((stspb & 0x40) == 0x40)) {ctlw=ctlw&ZOFF; fz=0;}
		outportb(ADRRG,ctlw);
		if((!fxy) && (!fz)) done=1;
		}
	ctlw=ctlw&XOFF&YOFF&ZOFF; outportb(ADRRG,ctlw); do_ptr=0; return 0;
	}
