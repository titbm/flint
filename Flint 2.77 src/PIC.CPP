/*********************************************************************
	pic.cpp
	iB
	ver.2.77 (reconstructed from v2.61 + changelog v2.61-v2.77)
			int pi_ini(void)
			int lpuls(void)
			void sh_open(unsigned int pos)
			void sh_close(void)
			int process(void)
			int move_sen(int dir)
			int move(int x, int y, int z)

	Changes from v2.61:
	v2.70: Dr.check indicator, reiterations display in mainscr
	v2.71: Pump/Gate control via LRG in process()
	v2.72: Timer-based laser pulse (PT2), dT speed correction in move()
	v2.73: Gate delay control via PT2.ch1, safe mode (10µs) on exit
	v2.74: Merged first/next retry counters in lpuls()
	v2.75: f_beep for critical msgbox, removed endSensor check in pi_ini
	v2.76: Removed out_time() calls everywhere
	v2.77: Optimized shutter handling in lpuls(), configurable sh_delay
*********************************************************************/
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <graphics.h>

/*------------------------------------------------------------------
  TRACE: runtime diagnostic log for remote debugging.
  Writes FLINT.LOG next to EXE with timestamped hardware events.
  Comment out #define TRACE to disable for production builds.
------------------------------------------------------------------*/
#define TRACE

#ifdef TRACE
FILE *tlog = NULL;
static char _tbuf[160];
void tlog_open(void)  { tlog=fopen("FLINT.LOG","w"); }
void tlog_close(void) { if(tlog){fclose(tlog); tlog=NULL;} }
void tlog_write(const char *s) {
	if(tlog){fputs(s,tlog); fputc('\n',tlog); fflush(tlog);}
	}
#else
void tlog_open(void)  {}
void tlog_close(void) {}
void tlog_write(const char *s) {}
#endif

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
PT2:	ch.0:		Laser Frequency (Tlas = K1*10mcs  655ms max)
		ch.1:		EOShutt-Pump Delay (Tsh = K2*10mcs)
		ch.2:		Global Delay (K3*10mcs)
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
extern int gate_delay;				// v2.70: Gate delay (x10 mcs)
extern int step_freq;
extern int f_const;
extern unsigned int step;
extern double nglas;
extern int xsize, ysize, zsize;
extern int huge *iTabl;
unsigned char ctlw;
extern int gl_nmb;
extern unsigned int glpos9;
extern unsigned int nmrpt[];		// v2.74: 10 elements (was 20)
extern unsigned int errnmb;
extern int d_check;
extern int f_noise;
extern int dT;						// v2.73: CPU time correction (ms)
extern int sh_delay;				// v2.77: EM shutter delay (ms)
extern int f_metal;				// v2.78: metal mode flag
unsigned char LCtl;					// Laser Control Word
unsigned int LPeriod;				// Laser Period in 10's mcs
extern unsigned long ulFlash;

int msg(int msgx, int msgy, int onoff, char msgtxt[]);
int msgbox(char msgtxt[], int more, int f_beep=0);
void draw(int flag, int all);
void beep(int tone, int duration);
void out_time(int newt);
void progbar(long nmb_max, long nmb, int set, int xl, int yt);
void glaspos(int xl, int yt, int cw);
void show_reit(int mode);
/* Forward declarations for functions in this file */
void sh_open(unsigned int pos);
void sh_close(void);
int lpuls_metal(int flag);
int move_sen(int dir);
int move(int x, int y, int z);

/* v2.73: Segment time estimator for htime()
   Returns number of l_period intervals needed for a move of (dx,dy,dz) steps */
int seg_time(int adx, int ady, int adz) {
	int t; long ms; int count;
	t=(abs(adx)>abs(ady))? abs(adx):abs(ady);
	if(t<abs(adz)) t=abs(adz);
	ms=(long)t*1000/step_freq;
	count=(int)(ms/l_period)+1;
	if(ms%l_period > l_period-dT) count++;
	return count;
	}


void program_pt2(int period, unsigned char gate) {
	unsigned int val=(unsigned int)period*100;
	outportb(ADRPT2,(unsigned char)(val%256));
	outportb(ADRPT2,(unsigned char)(val/256));
	outportb(ADRPT2+1,gate);
	outportb(ADRPT2+1,0);
	}


unsigned int read_pt2(void) {
	unsigned int low, high;
	outportb(ADRPT2+3,0);								// Counter Latch ch0
	low = (unsigned int)inportb(ADRPT2);
	high = (unsigned int)inportb(ADRPT2);
	return low + high*256;
	}




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
	outportb(ADRPT2+3,0x34);	// PT2.ch.0:mode2,binary,lb,hb (pump freq)
	outportb(ADRPT2+3,0x7a);	// PT2.ch.1:mode5,binary,lb,hb (gate delay)
	outportb(ADRPT2+3,0xb8);	// PT2.ch.2:mode4,binary,lb,hb
	program_pt2(l_period,1);		// init safe timer values
	/* v2.75: Removed endSensor check from pi_ini, only check K1 readback */
	{	int hw = (inportb(ADRPPI) == 150);
#ifdef TRACE
		sprintf(_tbuf,"[INI] hw=%d K1=%d lper=%d gate=%d shd=%d dchk=%d",
			hw,(int)inportb(ADRPPI),l_period,gate_delay,sh_delay,d_check);
		tlog_write(_tbuf);
#endif
		return hw;
	}
	}


/* v2.72+: Timer-based laser pulse via PT2
   v2.74:  Merged first/next retry counters
   v2.77:  EM shutter optimization, hardware timer sync */
int lpuls(int flag) {
	unsigned int i,k,dsens,mask,wrkpos,shft;
	unsigned int prevwrkpos;

	if(f_demo) {
		ulFlash++; return 1;
		}
	prevwrkpos=errnmb;
	mask=(gl_nmb)? glpos9:0x0200;
	if(d_check && errnmb) {
		wrkpos=errnmb & mask;
		}
	else wrkpos=mask;
	if(flag) sh_open(wrkpos);
	for(i=0; i<11; i++) {
		if(kbhit()) {
			if(getch() == ESC) {errnmb=wrkpos; return 0;}
			}
		/* Wait for PT2 counter to near-complete */
		while((read_pt2()-2) & 0xFFE0) ;
		/* Fire: program gate delay */
		program_pt2(l_period,(unsigned char)gate_delay);
		ulFlash++;
		
		delay(1);

		/* Safe reset: gate minimum */
		program_pt2(l_period,1);
		if(!d_check) {
#ifdef TRACE
			sprintf(_tbuf,"[LPULS] ok i=0 nodchk fl=%lu",ulFlash);
			tlog_write(_tbuf);
#endif
			return 1;
			}
		dsens=((unsigned int)inportb(ADRPPI2)+
					(unsigned int)inportb(ADRPPI2+2)*256)&0x03ff;
		wrkpos-=(dsens & wrkpos);
		if(!wrkpos) {
#ifdef TRACE
			sprintf(_tbuf,"[LPULS] ok i=%u dsens=%04X mask=%04X fl=%lu",
				i,dsens,mask,ulFlash);
			tlog_write(_tbuf);
#endif
			if(i || errnmb) sh_open(mask);
			errnmb=0; return 1;
			}
		if(i == 10) break;
		shft=0x0001;
		for(k=0; k<10; k++) {if(wrkpos & shft) nmrpt[k]+=1; shft*=2;}
		show_reit(0);
		if(wrkpos != prevwrkpos) {sh_open(wrkpos); prevwrkpos=wrkpos;}
		}
#ifdef TRACE
	sprintf(_tbuf,"[LPULS] FAIL i=10 wrkpos=%04X dsens=%04X mask=%04X fl=%lu",
		wrkpos,dsens,mask,ulFlash);
	tlog_write(_tbuf);
#endif
	errnmb=wrkpos; return 0;
	}


/* v2.78: Direct PC6 pulse for metal engraving mode.
   Same d_check/retry/EM-shutter logic as lpuls(), but fires
   via PC6 bit instead of PT2 timer. No pump needed. */
int lpuls_metal(int flag) {
	unsigned int i,k,dsens,mask,wrkpos,shft;
	unsigned int prevwrkpos;

	if(f_demo) {
		ulFlash++; return 1;
		}
	prevwrkpos=errnmb;
	mask=(gl_nmb)? glpos9:0x0200;
	if(d_check && errnmb) {
		wrkpos=errnmb & mask;
		}
	else wrkpos=mask;
	if(flag) sh_open(wrkpos);
	for(i=0; i<11; i++) {
		if(kbhit()) {
			if(getch() == ESC) {errnmb=wrkpos; return 0;}
			}
		/* Fire: direct PC6 pulse */
		outportb(ADRPPI+2,inportb(ADRPPI+2)&PULS_ON);
		delay(1);
		outportb(ADRPPI+2,inportb(ADRPPI+2)|PULS_OFF);
		ulFlash++;
		delay(1);
		if(!d_check) {
#ifdef TRACE
			sprintf(_tbuf,"[METAL] ok i=0 nodchk fl=%lu",ulFlash);
			tlog_write(_tbuf);
#endif
			return 1;
			}
		dsens=((unsigned int)inportb(ADRPPI2)+
					(unsigned int)inportb(ADRPPI2+2)*256)&0x03ff;
		wrkpos-=(dsens & wrkpos);
		if(!wrkpos) {
#ifdef TRACE
			sprintf(_tbuf,"[METAL] ok i=%u dsens=%04X mask=%04X fl=%lu",
				i,dsens,mask,ulFlash);
			tlog_write(_tbuf);
#endif
			if(i || errnmb) sh_open(mask);
			errnmb=0; return 1;
			}
		if(i == 10) break;
		shft=0x0001;
		for(k=0; k<10; k++) {if(wrkpos & shft) nmrpt[k]+=1; shft*=2;}
		show_reit(0);
		if(wrkpos != prevwrkpos) {sh_open(wrkpos); prevwrkpos=wrkpos;}
		}
#ifdef TRACE
	sprintf(_tbuf,"[METAL] FAIL i=10 wrkpos=%04X dsens=%04X mask=%04X fl=%lu",
		wrkpos,dsens,mask,ulFlash);
	tlog_write(_tbuf);
#endif
	errnmb=wrkpos; return 0;
	}


/* v2.77: configurable sh_delay instead of fixed SH_TIME=50 */
void sh_open(unsigned int pos) {
	outportb(ADRPPI2+1,(unsigned char)(pos%256)^0xff);		// PB: EM1-EM8
	if(pos & 0x0100) outportb(ADRPPI2+3,0x08);				// PC4=0: EM9-on
	else outportb(ADRPPI2+3,0x09);
	if(pos & 0x0200) outportb(ADRPPI2+3,0x0a);				// PC5=0: EM10-on
	else outportb(ADRPPI2+3,0x0b);
	outportb(ADRPPI2+3,0x0c);										// PC6=0: EMCOM-on
	delay(sh_delay); outportb(ADRPPI2+3,0x0d);				// PC6=1: EMCOM-off
	}


void sh_close(void) {
	outportb(ADRPPI2+1,0xff); outportb(ADRPPI2+3,0x09);	// PB0-PB7=1,PC4=1
	outportb(ADRPPI2+3,0x0b); outportb(ADRPPI2+3,0x0d);	// PC5,PC6=1
	}


/* v2.71+: Pump/Gate managed via config dialog (LRG)
   v2.76:  Removed out_time() calls
   v2.77:  Dr.check indicator update, reiteration display */
int process(void) {
	long i; int xnew,ynew,znew,k; char tmpstr[20];
	int flag;

#ifdef TRACE
	sprintf(_tbuf,"[PROC] START n=%ld/%ld metal=%d dchk=%d lper=%d gate=%d shd=%d",
		start_nmb,nmax,f_metal,d_check,l_period,gate_delay,sh_delay);
	tlog_write(_tbuf);
#endif
	msg(160,80,1,"For STOP: press ESC");
	if(f_ptr || (!do_ptr)) move_sen(0);
	outportb(ADRPPI+2,inportb(ADRPPI+2)&PR_OPEN);				// Protect-open
	flag=1;

	progbar(nmax,start_nmb,1,160,464);
	for(i=start_nmb; i<nmax; i++) {
		xnew=23500-xptr-iTabl[3*i];
		ynew=yptr+iTabl[3*i+1];
		znew=11000-zptr-zsize*10*(1-1/nglas)-iTabl[3*i+2];
		if(!move(xnew,ynew,znew)) {
			outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
			sh_close(); msg(160,80,0,"");
#ifdef TRACE
			sprintf(_tbuf,"[PROC] MOVE ERR pt=%ld x=%d y=%d z=%d",i,xnew,ynew,znew);
			tlog_write(_tbuf);
#endif
			msgbox("KPU/End sens.error",0,1);
			return 0;
			}
a:		if(f_metal) {
			if(!lpuls_metal(flag)) {
				outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
				sh_close(); msg(160,80,0,"");
				if(gl_nmb) glaspos(280,315,1);
				k=msgbox("Check laser. Retry: Ok",1,1);
				if(!k) return 0;
				msg(160,80,1,"For STOP: press ESC");
				flag=1;
				if(k == 1) goto a;
				errnmb=0;
				}
			else flag=0;
			}
		else {
a2:		if(!lpuls(flag)) {
			outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
			sh_close(); msg(160,80,0,"");
			/* v2.70: highlight failed positions red */
			if(gl_nmb) glaspos(280,315,1);
			k=msgbox("Check laser. Retry: Ok",1,1);
			if(!k) return 0;
			msg(160,80,1,"For STOP: press ESC");
			flag=1;
			if(k == 1) goto a2;
			errnmb=0;												// for Next
			}
		else flag=0;
		}
		outportb(ADRCMOS+1,0);											// CMOS increment
		draw(f_xyz, 0);													// Draw pixel
		lastn=i+1;
		setcolor(BLACK); setfillstyle(1,COLBKL); bar(31,206,86,222);
		ltoa(lastn,tmpstr,10); outtextxy(40,211,tmpstr);
		/* v2.70: show reiterations in real-time */
		if(d_check) {
			unsigned long ulRpt=0; unsigned int rk;
			for(rk=0; rk<10; rk++) ulRpt+=nmrpt[rk];
			if(ulRpt > 0) {
				setfillstyle(1,COLBKL); bar(31,224,86,232);
				ltoa(ulRpt,tmpstr,10); outtextxy(40,225,tmpstr);
				}
			}
		progbar(nmax,i,0,160,464);
		if(kbhit()) {
			if(getch() == ESC) {
				outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
				sh_close(); msg(160,80,0,""); return 0;
				}
			}
		}
	/* Normal end */
	outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE);
	sh_close();
#ifdef TRACE
	sprintf(_tbuf,"[PROC] END ok n=%ld fl=%lu",nmax,ulFlash);
	tlog_write(_tbuf);
#endif
	msg(160,80,0,"");
	msgbox("Ok.  TABLE END",0,1);
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
			outportb(ADRRG,ctlw);
			/* v2.76: removed out_time(1) */
			}
		}
	outportb(ADRPT0,0xc8); outportb(ADRPT0,0x00);				// K2x=200
	outportb(ADRPT0+1,0xc8); outportb(ADRPT0+1,0x00);			// dX=200
	outportb(ADRPT1,0xc8); outportb(ADRPT1,0x00);				// K2y=200
	outportb(ADRPT1+1,0xc8); outportb(ADRPT1+1,0x00);			// dY=200
	outportb(ADRPT0+2,0xc8); outportb(ADRPT0+2,0x00);			// K2z=200
	outportb(ADRPT1+2,0xc8); outportb(ADRPT1+2,0x00);			// dZ=200
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


/* v2.77: k2 calculator for move() - computes step frequency divider per axis
   k2 = (seg_time_count * l_period - dT) * 100 / abs(delta)
   Clamped to [100000/step_freq, 65500]. Returns k2min when f_const. */
long calc_k2(int delta, int t) {
	long k2, k2min, k2max=65500;
	k2min=100000L/step_freq;
	k2=k2min;
	if(!f_const) {
		k2=((long)t*l_period-dT)*100/abs(delta);
		if(k2 < k2min) k2=k2min;
		if(k2 > k2max) k2=k2max;
		}
	return k2;
	}


/* v2.72: replaced hardcoded 3 with dT for CPU correction
   v2.76: removed out_time(1) call at end
   v2.77: fixed k2 formula - uses seg_time() and calc_k2() per original binary */
int move(int x, int y, int z) {
	int dx,dy,dz,fxy,fz,done; unsigned char stspb;
	long k2; int t_seg;

c:	fxy=0; fz=0; done=0;
	dx=x-xcur; dy=y-ycur; dz=z-zcur;
	t_seg=seg_time(dx,dy,dz);
	if(dx) {
		k2=calc_k2(dx,t_seg);
		outportb(ADRPT0,(unsigned char)(k2%256));
		outportb(ADRPT0,(unsigned char)(k2/256));
		outportb(ADRPT0+1,(unsigned char)(abs(dx)%256));
		outportb(ADRPT0+1,(unsigned char)(abs(dx)/256));
		ctlw=(dx>0)? ctlw|XUP|XON:(ctlw&XDOWN)|XON;
		fxy=1;
		}
	else ctlw=ctlw&XOFF;
	if(dy) {
		k2=calc_k2(dy,t_seg);
		outportb(ADRPT1,(unsigned char)(k2%256));
		outportb(ADRPT1,(unsigned char)(k2/256));
		outportb(ADRPT1+1,(unsigned char)(abs(dy)%256));
		outportb(ADRPT1+1,(unsigned char)(abs(dy)/256));
		ctlw=(dy>0)? ctlw|YUP|YON:(ctlw&YDOWN)|YON;
		fxy=1;
		}
	else ctlw=ctlw&YOFF;
	if(dz) {
		k2=calc_k2(dz,t_seg);
		outportb(ADRPT0+2,(unsigned char)(k2%256));
		outportb(ADRPT0+2,(unsigned char)(k2/256));
		outportb(ADRPT1+2,(unsigned char)(abs(dz)%256));
		outportb(ADRPT1+2,(unsigned char)(abs(dz)/256));
		ctlw=(dz>0)? ctlw|ZUP|ZON:(ctlw&ZDOWN)|ZON;
		fz=1;
		}
	else ctlw=ctlw&ZOFF;
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
b:	if(f_demo) delay(l_period);										// v2.77: fixed per binary
	xcur=x; ycur=y; zcur=z;
	/* v2.76: removed out_time(1) */
	return 1;
a:
#ifdef TRACE
	sprintf(_tbuf,"[MOVE] ERR sens=%02X x=%d y=%d z=%d cur=%d,%d,%d",
		(int)stspb,x,y,z,xcur,ycur,zcur);
	tlog_write(_tbuf);
#endif
	ctlw=ctlw&XOFF&YOFF&ZOFF;
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
