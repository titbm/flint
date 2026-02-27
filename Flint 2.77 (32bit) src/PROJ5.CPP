/*********************************************************************
	proj5.cpp
	iB
	ver.2.77 (reconstructed from v2.61 + changelog v2.61-v2.77)

			int main()
			void button(int btc[], int nmb, char buttxt[])
			void buttonp(int btc[], int nmb, char buttxt[])
			void ctlbt(int btxl, int btyl, int colctl, char ctltxt[])
			int pressbt(int btc[], int nmb)
			int msgbox(char msgtxt[], int more, int f_beep)
			int msg(int msgx, int msgy, int onoff, char msgtxt[])
			int InrDcr(int param, int pmin, int pmax, int pstep, int updn)
			void sw_ctl(int flag, int param, int xpos, int ypos, int col)
			int dlgopen(char destnm[], char dlgnm[], int flag)
			int disksel(int nmb)
			void WndBkgr(int xl,int yt,int xr,int yb, int col,char txt[])
			int dlgcfg(void)
			int dlged(void)
			void chdiska(void)
			long inp_dig(int xl, int yt, double min, double max, int ax)
			void glload(int direct)
			int dlgload(void)
			int gselect(void)
			int dlgstart(void)
			void ClearRpt(void)
			void mainscr(int all)
			void show_reit(int mode)
			void glaspos(int xl, int yt, int cw)
			void drawfl(void)
			void draw(int flag, int all)
			void DrawPix(int hp,int hs, int vp, int vs, int color)
			int draw_bt(int btc[], char *bnam[], int nmb)
			int dlgsort(void)
			int sort(void)
			int sort2(void)
			long cros(unsigned long k1, unsigned long k2)
			void swap(unsigned long k1, unsigned long k2)
			int minmax(void)
			unsigned int scan_ms(int btc[], char *bnam[], int nbt, int f_beep)
			void progbar(long nmb_max, long nmb, int set, int xl, int yt)
			void htime(char tmpstr[])
			int dlgdim()

	Changes from v2.61:
	v2.70: Removed dlgstat()/F6 Statist; Gate delay in dlgcfg;
	       "X" button for clearing positions; direct Point number input;
	       Reiteration display in mainscr; F9 XYZ in dlged;
	       Error positions highlighted after "Check laser"
	v2.71: Pump/Gate toggles in dlgcfg (replaced Las.adjust);
	       Immediate effect of period/delay changes when pump on
	v2.72: Pump/gate shutdown on program exit
	v2.73: dT display in dlgcfg; gate reset to 10us on exit from Config
	v2.75: f_beep for critical messages
	v2.77: Removed infobox/F7 Info (version in mainscr);
	       sh_delay display; PgUp/PgDn in dlgload;
	       Dr.check indicator; optimized shutter handling
*********************************************************************/
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <direct.h>
#include <i86.h>
#include <ctype.h>
#include "compat.h"
#include "bgi32.h"

#pragma hdrstop
#include "proj5.h"

#define BITMAP_MSG_SIZE  65536UL
#define BGMAP_SIZE       4096UL

FILE *dbgf = NULL;
void dbg(const char *msg) {
	if(!dbgf) dbgf = fopen("debug.log","w");
	if(dbgf) { fputs(msg, dbgf); fputs("\n", dbgf); fflush(dbgf); }
}
static char _dbg_buf[256];
void dbgv(const char *label, int val) {
	sprintf(_dbg_buf, "%s: %d", label, val);
	dbg(_dbg_buf);
}

/* v2.77: extern from PIC.CPP for pump/gate control */
extern unsigned char LCtl;
extern unsigned int LPeriod;

/* v2.73: segment time estimator (PIC.CPP) */
int seg_time(int adx, int ady, int adz);

/* Trace log (PIC.CPP) */
extern void tlog_open(void);
extern void tlog_close(void);
extern void tlog_write(const char *);


int main() {
	int i, k, g_mode, g_error_code, all, g_driver=DETECT;
	char strtmp[20];

	f_demo=0;
	f_bcab=0; f_bca=0; f_bc=0;
	f_sort=0; sK1=15; sK2=10;
	f_xyz=0;
	f_data=0; start_nmb=0; lastn=0;
	nmax=0; tout=0;
	do_ptr=0;
	f_ptr=0;
	strcpy(glstype,"K8");
	nglas=1.506;
	xsize=500; ysize=500; zsize=500;
	xofs=0; yofs=0; zofs=0;
	xcur=0; ycur=0; zcur=0;
	dx=20; dy=20; dz=60;
	nmb_pbt=255;
	gl_nmb=1;
	d_check=1;
	f_noise=0;
	k=1; all=1;
	fcdim=1; kdim=100;
	feqk=1; kxdim=100; kydim=100; kzdim=100;
	ClearRpt();
	RdCfg(gl_nmb);
	CurDir(); strcpy(wrkpath,path);
	/* 32-bit: no registerfarbgidriver needed */
	initgraph(&g_driver,&g_mode,"");
	g_error_code=graphresult();
	if(g_error_code != grOk) {printf("graphics error"); return 255;}
	tlog_open();
	if(!pi_ini()) f_demo=1;
	ms_init();
	set_gr_cursor(0,0,scr_cur_masks);
	/* 32-bit DOS/4GW: use malloc() for flat memory model.
	 * Each point = 3 x short = 6 bytes. */
	dbg("before malloc");
	ulMax = 8000000UL;   /* 8 million points = 48 MB (fits in DOS/4GW) */
	iTabl = (short *)malloc(ulMax * 6);
	if(iTabl == NULL) {
		ulMax = 2000000UL;  /* 2M points = 12 MB */
		iTabl = (short *)malloc(ulMax * 6);
	}
	if(iTabl == NULL) {
		ulMax = 400000UL;   /* 400K points = 2.4 MB */
		iTabl = (short *)malloc(ulMax * 6);
	}
	if(iTabl == NULL) {
		printf("Allocation error"); goto b;
	}
	dbg("malloc OK");
	/* Memory verification */
	{
		unsigned long testpos = ulMax * 3 - 1;
		unsigned long midpos = ulMax * 3 / 2;
		iTabl[0] = 0x1234;
		iTabl[midpos] = 0x5678;
		iTabl[testpos] = (short)0xABCD;
		if(iTabl[0] != 0x1234 || iTabl[midpos] != 0x5678 ||
		   iTabl[testpos] != (short)0xABCD) {
			printf("Memory test FAILED!"); goto b;
		}
		iTabl[0] = 0; iTabl[midpos] = 0; iTabl[testpos] = 0;
		sprintf(_dbg_buf, "Memory test OK: %lu points (%lu MB)",
			ulMax, (ulMax * 6) / (1024UL * 1024UL));
		dbg(_dbg_buf);
	}
	/* Allocate image save buffers */
	bitmapmsg = malloc(BITMAP_MSG_SIZE);
	bgmap = malloc(BGMAP_SIZE);
	if(!bitmapmsg || !bgmap) {
		printf("Buffer allocation error"); goto b;
	}
	dbg("buffers OK");
	FlashRd();
	while(1) {
		setlinestyle(0,1,1);
		if(k) mainscr(all);
		all=1; k=1;
		/* v2.77: BNM_SCR=7 (removed F6 Statist, F7 Info) */
		i=scan_ms(btc_scr,bnam_scr,BNM_SCR,0);
		switch(i) {
			case 0:														// F9 XYZ
c:				f_xyz=(f_xyz > 2)? 0:f_xyz+1; all=0; break;
			case 1: dlgcfg(); break;								// F1 Config
			case 2: dlged(); break;									// F2 Convert
			case 3:														// F3 DatLoad
a:				if(dlgopen(strtmp,"Data load",0)) {
					lastn=0;
					if(!rddir(strtmp)) {msgbox("File not found",0,0); goto a;}
					msg(250,300,1,"Please wait");
					if(f_bc) nmax=rdcft_t(strtmp);
					else nmax=rdbft_t(strtmp);
					msg(250,300,0,"");
					if(!nmax) {msgbox("Not flinttab file",0,0); goto a;}
					else {
						if(nmax > 0) {f_data=1; strcpy(wrkfile,strtmp);
					#ifdef TRACE
						sprintf(_tbuf,"[DATA] LOAD file=%s points=%ld",strtmp,nmax);
						tlog_write(_tbuf);
					#endif
						}
						else {msgbox("Buffer overflow",0,0); goto a;}
						}
					tout=1;
					}
				else {strcpy(wrkfile,""); nmax=0; lastn=0; tout=0; f_data=0;}
				chdiska(); break;
			case 4: dlgload(); all=0; break;						// F4 GlsLoad
			case 5: dlgstart(); break;								// F5 Start
			/* v2.70: F6 Statist removed */
			/* v2.77: F7 Info removed (version shown in mainscr) */
			case 6:														// F10 Exit
e:				if(msgbox("Exit?",0,0)) {
					free(iTabl);
				free(bitmapmsg);
				free(bgmap);
b:					closegraph();
					/* v2.72: safe shutdown - LRG off */
					outportb(LRG, 0);
					tlog_close();
					return 0;
					}
				k=0; break;
			case 255:
				switch(pkey) {
					case 59: dlgcfg(); break;						// F1
					case 60: dlged(); break;						// F2
					case 61: goto a;									// F3
					case 62: dlgload(); break;						// F4
					case 63: dlgstart(); break;					// F5
					/* v2.70: F6(64) removed */
					/* v2.77: F7(65) removed */
					case 67: goto c;									// F9
					case 68: goto e;									// F10
					}
				break;
			}
		}
	}


void button(int btc[], int nmb, char buttxt[]) {
	setfillstyle(1,63); bar(btc[6*nmb+2],btc[6*nmb+3],
		btc[6*nmb+2]+btc[6*nmb+4],btc[6*nmb+3]+btc[6*nmb+5]);
	setfillstyle(1,BLACK); bar(btc[6*nmb+2]+1,btc[6*nmb+3]+1,
		btc[6*nmb+2]+btc[6*nmb+4]+1,btc[6*nmb+3]+btc[6*nmb+5]+1);
	setfillstyle(1,7); bar(btc[6*nmb+2]+1,btc[6*nmb+3]+1,
		btc[6*nmb+2]+btc[6*nmb+4],btc[6*nmb+3]+btc[6*nmb+5]);
	setcolor(BLACK); outtextxy(btc[6*nmb+2]+4,btc[6*nmb+3]+4,buttxt);
	}


void buttonp(int btc[], int nmb, char buttxt[]) {
	setfillstyle(1,BLACK); bar(btc[6*nmb+2],btc[6*nmb+3],
		btc[6*nmb+2]+btc[6*nmb+4],btc[6*nmb+3]+btc[6*nmb+5]);
	setfillstyle(1,7); bar(btc[6*nmb+2]+1,btc[6*nmb+3]+1,
		btc[6*nmb+2]+btc[6*nmb+4]+1,btc[6*nmb+3]+btc[6*nmb+5]+1);
	setcolor(BLACK); outtextxy(btc[6*nmb+2]+5,btc[6*nmb+3]+5,buttxt);
	}


void ctlbt(int btxl,int btyl,int colctl,char ctltxt[]) {
	setcolor(colctl); rectangle(btxl,btyl,btxl+10,btyl+10);
	outtextxy(btxl+15,btyl+2,ctltxt);
	}


int pressbt(int bt[],int nm) {
	if((bt[6*nm+2]<coord[0])&&(coord[0]<(bt[6*nm+2]+bt[6*nm+4]))&&
		(bt[6*nm+3]<coord[1])&&(coord[1]<(bt[6*nm+3]+bt[6*nm+5]))) return 1;
	return 0;
	}


int msgbox(char msgtxt[], int more, int f_beep) {
	getimage(180,290,385,345,bitmapmsg);
	setfillstyle(1,BLACK); bar(184,294,384,344);
	setfillstyle(1,COL_ON); bar(180,290,380,340);
	setcolor(BLACK); outtextxy(190,297,msgtxt);
	if(more) outtextxy(190,325,"Next pix:");
	draw_bt(btc_msg,bnam_msg,BNM_MSG+more);
	while(1) {
		int i=scan_ms(btc_msg, bnam_msg, BNM_MSG+more, f_beep);
		putimage(180,290,bitmapmsg, 0);
		if(!i) return 1;
		else if(i == 1) return 0;
		else if(i == 2) return 2;
		else {if(pkey == 13) return 1; else return 0;}
		}
	}


void msgbox1(char msgtxt[]) {
	getimage(180,290,385,345,bitmapmsg);
	setfillstyle(1,BLACK); bar(184,294,384,344);
	setfillstyle(1,COL_ON); bar(180,290,380,340);
	setcolor(BLACK); outtextxy(190,297,msgtxt);
	draw_bt(btc_msg1,bnam_msg1,BNM_MSG1);
	scan_ms(btc_msg1, bnam_msg1, BNM_MSG1, 0);
	putimage(180,290,bitmapmsg, 0);
	}


/* v2.77: infobox() removed - version shown directly in mainscr */


int msg(int msgx,int msgy,int onoff,char msgtxt[]) {
	if(onoff) {
		getimage(msgx,msgy,msgx+205,msgy+45,bitmapmsg);
		setfillstyle(1,BLACK); bar(msgx+4,msgy+4,msgx+204,msgy+44);
		setfillstyle(1,COL_ON); bar(msgx,msgy,msgx+200,msgy+40);
		setcolor(BLACK); outtextxy(msgx+10,msgy+7,msgtxt);
		return(1);
		}
	else putimage(msgx,msgy,bitmapmsg,0);
	return(0);
	}


void WndBkgr(int xl,int yt,int xr,int yb, int col,char txt[]) {
	setfillstyle(1,BLACK); bar(xl+5,yt+5,xr+5,yb+5);
	setfillstyle(1,col); bar(xl,yt,xr,yb);
	setcolor(BLACK);
	rectangle(xl,yt,xr,yb); outtextxy(xl+10,yt+5,txt);
	line(xl+3,yt+18,xr-3,yt+18); line(xl+3,yb-30,xr-3,yb-30);
	}


/* v2.70+: Major changes to Configuration dialog:
   v2.70: Gate delay +/- active, X button for clearing positions
   v2.71: Pump/Gate toggles replace Las.adjust, immediate effect
   v2.73: dT display, gate reset to 10us on exit
   v2.77: sh_delay display, new CFG save format */
int dlgcfg(void) {
	int i,x,y,z,xptrnew,yptrnew,zptrnew,stepnew,gl_nmbnew,lpnew;
	int sfnew,f_constnew,glp9new,ptr_work=0,f_make=0,f_rdcfg=0,pr_open=0;
	int gd_new;									// v2.70: gate delay
	int f_pt2=0;								// v2.71: PT2 reprogram flag
	char *cret="\n",tmpstr[20],cfgmas[80];	// v2.77: expanded buffer
	double d; struct date dd;

	setdisk(wrkpath[0]-'A'); chdir(wrkpath);
	xptrnew=xptr; yptrnew=yptr; zptrnew=zptr;
	stepnew=step; gl_nmbnew=gl_nmb; glp9new=glpos9;
	lpnew=l_period; sfnew=step_freq; f_constnew=f_const;
	gd_new=gate_delay;								// v2.70
	WndBkgr(100,60,520,410,COLDLG,"Configuration");
	draw_bt(btc_cfg,bnam_cfg,BNM_CFG+9*gl_nmbnew);
	outtextxy(130,255,"Flash nmb"); rectangle(130,265,226,281);
	outtextxy(130,287,"Service date"); rectangle(130,297,226,313);
	outtextxy(270,100,".cfg");
	outtextxy(400,130,"Step"); rectangle(400,140,460,156);
	outtextxy(400,175,"X"); rectangle(400,185,460,201);
	outtextxy(400,220,"Y"); rectangle(400,230,460,246);
	outtextxy(400,265,"Z"); rectangle(400,275,460,291);
	outtextxy(280,120,"Las.puls"); outtextxy(280,130,"period");
	rectangle(280,140,340,156); outtextxy(320,159,"ms");
	outtextxy(280,175,"Gate");
	rectangle(280,185,340,201); outtextxy(320,204,"us");		// v2.70: gate delay
	outtextxy(280,225,"Step"); outtextxy(280,235,"freq.");
	rectangle(280,245,340,261); outtextxy(320,264,"Hz");
	/* v2.73: dT display */
	outtextxy(400,342,"dT:");
	outtextxy(428,342,itoa(dT,tmpstr,10)); outtextxy(460,342,"ms");
	/* v2.77: sh_delay display */
	outtextxy(400,352,"sh:");
	outtextxy(428,352,itoa(sh_delay,tmpstr,10)); outtextxy(460,352,"ms");
	if(f_demo) outtextxy(120,352,"Demo");
	ultoa(ulMax,tmpstr,10); strcat(tmpstr," pixels max");
	outtextxy(120,363,tmpstr);
	rectangle(120,249,238,341);
	rectangle(265,110,510,370);
	while(1) {
		sw_ctl(gl_nmbnew,0,120,90,COLDLG);						// 1 glass
		sw_ctl(gl_nmbnew,1,120,105,COLDLG);						// 9 glasses
		sw_ctl(pr_open,1,120,160,COLDLG);						// protect open/close
		/* v2.71: Gate and Pump toggles (v2.77: gate before pump) */
		sw_ctl(f_gate,1,120,185,COLDLG);						// Gate
		sw_ctl(LCtl,3,120,200,COLDLG);						// Pump
		sw_ctl(f_metal,1,120,225,COLDLG);					// v2.78: Metal mode
		if(f_rdcfg) {
			RdCfg(gl_nmbnew); xptrnew=xptr; yptrnew=yptr; zptrnew=zptr;
			stepnew=step; lpnew=l_period; sfnew=step_freq; f_constnew=f_const;
			gd_new=gate_delay;
			if(gl_nmbnew) glp9new=glpos9;
			f_rdcfg=0;
			}
		setfillstyle(1,COLDLG); bar(280,313,330,363);		// 9 glass positions
		setfillstyle(1,COL_ON);
		if(gl_nmbnew) glaspos(280,315,glp9new);
		sw_ctl(ptr_work,1,400,90,COLDLG);						// Work ptr
		sw_ctl(f_constnew,1,280,280,COLDLG);					// Constant
		sw_ctl(f_constnew,0,280,295,COLDLG);					// Variable
		setfillstyle(1,COLBKL);
		itoa(stepnew,tmpstr,10);									// Step
		bar(401,141,459,155); outtextxy(410,145,tmpstr);
		itoa(xptrnew,tmpstr,10);									// Xptr
		bar(401,186,459,200); outtextxy(410,190,tmpstr);
		itoa(yptrnew,tmpstr,10);									// Yptr
		bar(401,231,459,245); outtextxy(410,235,tmpstr);
		itoa(zptrnew,tmpstr,10);									// Zptr
		bar(401,276,459,290); outtextxy(410,280,tmpstr);
		itoa(lpnew,tmpstr,10);										// Laser puls period
		bar(281,141,339,155); outtextxy(290,145,tmpstr);
		/* v2.70: Gate delay display (x10 mcs) */
		itoa(gd_new*10,tmpstr,10);
		bar(281,186,339,200); outtextxy(290,190,tmpstr);
		itoa(sfnew,tmpstr,10);										// Step frequency
		bar(281,246,339,260); outtextxy(290,250,tmpstr);
		setfillstyle(1,COLBKL); bar(131,266,225,280);
		outtextxy(140,270,ultoa(ulFlash,cfgmas,10));			// Flash Nmb
		strcpy(tmpstr,itoa((int)(ulService >> 24),cfgmas,10));
		strcat(tmpstr,"-");
		strcat(tmpstr,itoa((int)((ulService >> 16) & 0xff),cfgmas,10));
		strcat(tmpstr,"-");
		strcat(tmpstr,itoa((int)(ulService & 0xffff),cfgmas,10));
		bar(131,298,225,312); outtextxy(140,302,tmpstr);	// Service Date
		/* v2.77: refresh dT/sh values (updates after Load .cfg) */
		setfillstyle(1,COLDLG); bar(428,342,452,360);
		itoa(dT,tmpstr,10); outtextxy(428,342,tmpstr);
		itoa(sh_delay,tmpstr,10); outtextxy(428,352,tmpstr);
		/* v2.71: centralized PT2 reprogramming via flag */
		if(f_pt2) {
			program_pt2(lpnew, f_gate ? gd_new : 1);
			f_pt2=0;
			}
		if(ptr_work && f_make) {
			outportb(ADRPPI+2,inportb(ADRPPI+2)&STEP_ON);
			msg(260,300,1,"Please wait"); delay(30);
			if(!do_ptr) {move_sen(0); do_ptr=1;}
			x=23500-xptrnew;
			y=yptrnew; d=(1-1/nglas)*10*zsize; z=11000-zptrnew-(int)d;
			if(!move(x,y,z)) {
				outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF);
				msgbox("KPU error",0,0); return 0;
				}
			msg(260,300,0,""); f_make = 0;
			}
		i=scan_ms(btc_cfg,bnam_cfg,BNM_CFG+9*gl_nmbnew,0);
		switch(i) {
			case 0:														// Enter/Ok
a:				l_period=lpnew; step_freq=sfnew; f_const=f_constnew;
				gate_delay=gd_new;								// v2.70
				xptr=xptrnew; yptr=yptrnew; zptr=zptrnew;
				step=stepnew; gl_nmb=gl_nmbnew; glpos9=glp9new; i=1; goto c;
			case 1:														// Esc/Cancel
b:				i=0;
c:				/* v2.77: safe exit - PR_CLOSE, sh_close, program_pt2 reset */
				outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF|PR_CLOSE);
				sh_close(); nmb_pbt=255; f_gate=0;
				program_pt2(l_period, 1);
				setdisk(path[0]-'A'); chdir(path); FlashWr(); return i;
			case 2: f_rdcfg=1; f_make=1; f_pt2=1;
#ifdef TRACE
				sprintf(_tbuf,"[CONFIG] LOAD glass=%d",gl_nmbnew);
				tlog_write(_tbuf);
#endif
				break;		// Load .cfg
			case 3:														// Save .cfg
				/* v2.77: save 10-11 field format */
				if(msgbox("Are you sure?",0,0)) {
#ifdef TRACE
					sprintf(_tbuf,"[CONFIG] SAVE x=%d y=%d z=%d step=%d lper=%d gate=%d",xptrnew,yptrnew,zptrnew,stepnew,lpnew,gd_new);
					tlog_write(_tbuf);
#endif
					itoa(xptrnew,tmpstr,10);
					strcpy(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(yptrnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(zptrnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(stepnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(lpnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(gd_new,tmpstr,10);						// v2.70: gate delay
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(sfnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(f_constnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(dT,tmpstr,10);							// v2.73: dT
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(sh_delay,tmpstr,10);						// v2.77: sh_delay
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					if(gl_nmbnew) {
						itoa(glp9new,tmpstr,10);
						strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
						wrfile("flint9.cfg",cfgmas,80);
						}
					else wrfile("flint1.cfg",cfgmas,80);
					} break;
			case 4: lpnew=InrDcr(lpnew,20,655,5,1);				// LasPeriod+
				f_pt2=1; break;
			case 5: lpnew=InrDcr(lpnew,20,655,5,0);				// LasPeriod-
				f_pt2=1; break;
			case 6: gd_new=InrDcr(gd_new,1,50,1,1);				// GateDelay+
				f_pt2=1; break;
			case 7: gd_new=InrDcr(gd_new,1,50,1,0);				// GateDelay-
				f_pt2=1; break;
			case 8: sfnew=InrDcr(sfnew,100,2000,100,1); break;	// StepFreq+
			case 9: sfnew=InrDcr(sfnew,100,2000,100,0); break;	// StepFreq-
			case 10: stepnew=InrDcr(stepnew,10,1000,10,1); break;	// StepSize+
			case 11: stepnew=InrDcr(stepnew,10,1000,10,0); break;	// StepSize-
			case 12: xptrnew=InrDcr(xptrnew,0,23500,stepnew,1);	// Xptr+
				f_make=1; break;
			case 13: xptrnew=InrDcr(xptrnew,0,23500,stepnew,0);	// Xptr-
				f_make=1; break;
			case 14: yptrnew=InrDcr(yptrnew,0,23500,stepnew,1);	// Yptr+
				f_make=1; break;
			case 15: yptrnew=InrDcr(yptrnew,0,23500,stepnew,0);	// Yptr-
				f_make=1; break;
			case 16: zptrnew=InrDcr(zptrnew,0,11000,stepnew,1);	// Zptr+
				f_make=1; break;
			case 17: zptrnew=InrDcr(zptrnew,0,11000,stepnew,0);	// Zptr-
				f_make=1; break;
			case 18: gl_nmbnew=0; f_rdcfg=1; f_make=1; errnmb=0;
				f_pt2=1;
#ifdef TRACE
				tlog_write("[CONFIG] GLASS 1");
#endif
				break;
			case 19: gl_nmbnew=1; f_rdcfg=1; f_make=1; errnmb=0;
				f_pt2=1;
#ifdef TRACE
				tlog_write("[CONFIG] GLASS 9");
#endif
				break;
			case 20: pr_open=(pr_open)? 0:1;						// Protect open/close
#ifdef TRACE
				sprintf(_tbuf,"[CONFIG] PROTECT %s",pr_open ? "OPEN" : "CLOSE");
				tlog_write(_tbuf);
#endif
				if(pr_open) {
					outportb(ADRPPI+2,inportb(ADRPPI+2)&PR_OPEN); sh_open(0x03ff);
					}
				else {outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE); sh_close();}
				break;
			case 21:													// v2.71: Gate toggle
#ifdef TRACE
				sprintf(_tbuf,"[CONFIG] GATE %s",f_gate ? "OFF" : "ON");
#ifdef TRACE
				sprintf(_tbuf,"[CONFIG] PUMP %s",LCtl ? "OFF" : "ON");
				tlog_write(_tbuf);
#endif
				tlog_write(_tbuf);
#endif
				f_gate=!f_gate; f_pt2=1; break;
			case 22:													// v2.71: Pump toggle
				LCtl=(LCtl)? 0:3; outportb(LRG,LCtl); break;
			case 23: ptr_work=(ptr_work)? 0:1;					// Work ptr on/off
				if(ptr_work) {
					if(msgbox("GLASS: n,size is true?",0,0)) f_make=1;
					else ptr_work=0;
					} break;
#ifdef TRACE
					tlog_write("[CONFIG] RESET statistics");
#endif
			case 24: f_constnew=1; break;							// Constant
			case 25: f_constnew=0; break;							// Variable
			case 26:													// # Statistics reset
				if(msgbox("Are you sure?",0,0)) {
					getdate(&dd);
					ulService=((unsigned long)dd.da_day<<24)+
					((unsigned long)dd.da_mon<<16)+dd.da_year;
					ulFlash=0; FlashWr();
					} break;
			case 27: glp9new=0; break;								// X clear positions
			case 28:													// v2.78: Shot (direct PC6 pulse)
				if(!f_demo) {
					outportb(ADRPPI+2,inportb(ADRPPI+2)&PULS_ON);
					delay(1);
					outportb(ADRPPI+2,inportb(ADRPPI+2)|PULS_OFF);
				}
				ulFlash++;
				tlog_write("[SHOT] fire");
				break;
			case 29: f_metal=!f_metal;
#ifdef TRACE
				sprintf(_tbuf,"[CONFIG] METAL %s",f_metal ? "ON" : "OFF");
				tlog_write(_tbuf);
#endif
				break;					// v2.78: Metal toggle
			case 30: glp9new ^= 0x0001; break;					// Glass positions
			case 31: glp9new ^= 0x0002; break;
			case 32: glp9new ^= 0x0004; break;
			case 33: glp9new ^= 0x0008; break;
			case 34: glp9new ^= 0x0010; break;
			case 35: glp9new ^= 0x0020; break;
			case 36: glp9new ^= 0x0040; break;
			case 37: glp9new ^= 0x0080; break;
			case 38: glp9new ^= 0x0100; break;
			case 255:
				if(pkey == 13) goto a;
				if(pkey == 27) goto b;
				break;
			}
		}
	}


int InrDcr(int param, int pmin, int pmax, int pstep, int updn) {
	int i;
	if(updn) i=(param>(pmax-pstep))? pmax:param+pstep;
	else i=(param<(pmin+pstep))? pmin:param-pstep;
	return i;
	}


void sw_ctl(int flag, int param, int xpos, int ypos, int col) {
	int i=(flag == param)? COL_ON:col;
	setfillstyle(1,i); bar(xpos+1,ypos+1,xpos+9,ypos+9);
	}


int dlgopen(char destnm[], char dlgnm[], int flag) {
	int i,k,s,c,m,ff,n,save,disk;
	char fnamnew[13],dirnam[13],str[20],fnmext[20];

	strcpy(fnamnew,"");
	WndBkgr(90,130,590,410,GREEN,dlgnm);
	draw_bt(btc_opn,bnam_opn,BNM_OPN+flag);
	rectangle(264,174,376,301); rectangle(109,174,221,301);
	rectangle(109,329,221,348); outtextxy(110,317,"Drive:");
	rectangle(419,174,531,193);
	if(!flag) ff=f_bc;
	else if(flag == 1) ff=f_bca;
	else ff=f_bcab;
	m=0; n=0;
	while(1) {
		setfillstyle(1,GREEN); bar(420,220,580,335);
		if(ff == 3) {
			setcolor(BLACK); setfillstyle(1,COLBKL);
			rectangle(450,232,510,250); bar(451,233,509,249);
			rectangle(450,257,510,275); bar(451,258,509,274);
			rectangle(450,282,510,300); bar(451,283,509,299);
			outtextxy(420,237,"dx:"); outtextxy(420,262,"dy:");
			outtextxy(420,287,"dz:"); outtextxy(520,250,"0.1-1.5");
			outtextxy(520,287,"0-1.5"); outtextxy(490,222,"mm");
			gcvt((double)dx/100,4,str); outtextxy(460,238,str);
			gcvt((double)dy/100,4,str); outtextxy(460,263,str);
			gcvt((double)dz/100,4,str); outtextxy(460,288,str);
			}
		if(!ff) strcpy(fnmext,"*.bft");
		if(ff == 1) strcpy(fnmext,"*.cft");
		if(ff == 2) strcpy(fnmext,"*.asc");
		if(ff == 3) strcpy(fnmext,"*.bmp");
		rddir(fnmext);
		setfillstyle(1,GREEN);
		bar(110,160,580,168); outtextxy(110,160,path);
		sw_ctl(ff,0,btc_opn[62],btc_opn[63], GREEN);
		sw_ctl(ff,1,btc_opn[68],btc_opn[69], GREEN);
		sw_ctl(ff,2,btc_opn[74],btc_opn[75], GREEN);
		sw_ctl(ff,3,btc_opn[80],btc_opn[81], GREEN);
		setcolor(BLACK); setfillstyle(1,COLBKL);
		bar(110,175,220,300);
		for(i=0; i<12; i++) outtextxy(120,180+10*i,dname[i+n]);
		bar(110,330,220,347);
		str[0]=getdisk()+'A'; str[1]=':'; str[2]=0;
		outtextxy(120,336,str); bar(265,175,375,300);
		for(i=0; i<12; i++) outtextxy(275,180+10*i,strlwr(mname[i+m]));
		bar(420,175,530,192); outtextxy(430,181,fnamnew);
		k=(ff == 3)? 4:0;
		i = scan_ms(btc_opn,bnam_opn,BNM_OPN+flag+k,0);
		switch(i) {
			case 0:
a:				strcpy(destnm,fnamnew);
				if(!flag) f_bc=ff;
				else if(flag == 1) f_bca=ff;
				else f_bcab=ff;
				nmb_pbt=255; return 1;
			case 1:
b:				nmb_pbt=255; return 0;
			case 2: n=(n<2)? 0:(n-1); break;
			case 3: if(lastd>10) n=(n>lastd-10)? lastd-9:n+1; break;
			case 4: k=(coord[1]-180)/10;
				if((k+n)<=lastd) {
					strcpy(fnamnew,""); strcpy(dirnam,dname[k+n]);
					chdir(dirnam); n=0; m=0;
					} break;
			case 5: save=getdisk();
				for (disk=0; disk<10; ++disk) {
					setdisk(disk); if(disk == getdisk()) k=disk;
					}
				setdisk(save); disk=disksel(k);
				if(disk == -1) break;
				if((disk < 2)&&(biosdisk(2,disk,0,1,1,1,mname)!=0)) {
					delay(300);
					if(biosdisk(2,disk,0,1,1,1,mname)!=0) {
						msgbox("disk error",0,0); break;
						}
					}
				strcpy(fnamnew,""); setdisk(disk); break;
			case 6: m=(m<2)? 0:(m-1); break;
			case 7: if(lastf>10) m=(m>lastf-10)? lastf-9:m+1; break;
			case 8: k=(coord[1]-180)/10;
				if((k+m)<=lastf) {
					setfillstyle(1,COLBKL); bar(420,175,530,192);
					outtextxy(430,181,mname[k+m]); strcpy(fnamnew,mname[k+m]);
					} break;
			case 9: str[0]=0x5f;
				for(s=1; s<10; s++) str[s]=0;
				s=0; setfillstyle(1,COLBKL); bar(420,175,530,192);
				outtextxy(430,181,str);
				while(!kbhit()) out_time(1);
				c=getch();
				while(c != 13) {
					if((((c>0x2f)&&(c<0x3a))||((c>0x40)&&(c<0x5b))||
							((c>0x60)&&(c<0x7b)))&&(s<8)) {
						str[s]=c; s++; str[s]=0x5f;
						}
					if((c==8)&&(s>0)) {str[s]=0; s--; str[s]=0x5f;}
					if(c==27) {
						for(s=0; s<10; s++) str[s]=0;
						goto c;
						}
					bar(420,175,530,192); outtextxy(430,181,str);
					while(!kbhit()) out_time(1);
					c=getch();
					}
				str[s]=0;
				if(!ff) strcat(str,".bft");
				if(ff == 1) strcat(str,".cft");
				if(ff == 2) strcat(str,".asc");
				if(ff == 3) strcat(str,".bmp");
c:				strcpy(fnamnew,str); break;
			case 10: ff=0; goto d;
			case 11: ff=1; goto d;
			case 12: ff=2; goto d;
			case 13: ff=3;
d:				strcpy(fnamnew,""); m=0; break;
			case 14: k=inp_dig(451,233,0.1,1.5,2); if(k>0) dx=k; break;
			case 15: k=inp_dig(451,258,0.1,1.5,2); if(k>0) dy=k; break;
			case 16: k=inp_dig(451,283,0,1.5,2); if(k>=0) dz=k; break;
			case 255:
				if(pkey == 13) goto a;
				if(pkey == 27) goto b;
				break;
			}
		}
	}


int disksel(int nmb) {
	int i, m; char str[3];

	m=10*(nmb+1);
	getimage(170,324,210,335+m,bitmapmsg);
	setcolor(BLACK); rectangle(170,324,210,335+m);
	setfillstyle(1,COLBKL); bar(171,325,209,334+m);
	str[1]=':'; str[2]=0;
	for(i=0;i<=nmb;i++) {str[0]='A'+i; outtextxy(180,331+10*i,str);}
	while(1) {
		i=ms_key_cmd(0);
		if(i==1) {
			if((170<coord[0])&&(coord[0]<210)&&(330<coord[1])&&(coord[1]<330+m)) {
				m=(coord[1]-330)/10; putimage(170,324,bitmapmsg,0); return m;
				}
			}
		if(i==ESC) {putimage(170,324,bitmapmsg,0); return -1;}
		}
	}


/* v2.70: Added F9 XYZ hotkey for view cycling */
int dlged(void) {
	int i,k,m,h,v,xr,yt,kscale,f_view,f_mirror,f_invert;
	int hofs,vofs,hsize,vsize,hmin,vmin,hmax,vmax,chpic0;
	long t; char tmpstr[20],fasc[13];

	nmax=0; f_view=0; f_mirror=0; chpic0=0; strcpy(fasc,"");
	f_invert=0; f_data=0;
c:	xofs=0; yofs=0; zofs=0;
b:	WndBkgr(80,20,610,462,COLDLG,"Data Convert");
	draw_bt(btc_ed,bnam_ed,BNM_ED);
	outtextxy(90,45,"File:"); outtextxy(140,45,fasc);
	outtextxy(500,44,"Glass:"); rectangle(500,54,576,70);
	outtextxy(500,75,"n:"); rectangle(500,85,560,101);
	outtextxy(500,111,"Xsize:"); rectangle(500,121,560,137);
	outtextxy(500,147,"Ysize:"); rectangle(500,157,560,173);
	outtextxy(500,183,"Zsize:"); rectangle(500,193,560,209);
	rectangle(527,274,587,290); outtextxy(502,279,"dT:");
	rectangle(527,292,587,308); outtextxy(502,297,"dL:");
	rectangle(527,310,587,326); outtextxy(502,315,"dR:");
	rectangle(527,328,587,344); outtextxy(502,333,"dB:");
	while(1) {
		if(!chpic0) {
			sw_ctl(f_invert,1,505,221,COLDLG);
			sw_ctl(f_mirror,1,505,234,COLDLG);
			setfillstyle(1,COLDLG); bar(110,60,480,419); setcolor(COLBKL);
			minmax();
			switch(f_view) {
				case 0:
					outtextxy(110,363,"Y"); outtextxy(160,413,"X"); h=0; v=1;
					hsize=xsize; vsize=ysize;
					hmin=xmin; vmin=ymin; hmax=xmax; vmax=ymax; break;
				case 1:
					outtextxy(110,363,"X"); outtextxy(160,413,"Y"); h=1; v=0;
					hsize=ysize; vsize=xsize;
					hmin=ymin; vmin=xmin; hmax=ymax; vmax=xmax; break;
				case 2:
					outtextxy(160,413,"X"); h=0; hsize=xsize;
					hmin=xmin; hmax=xmax; goto k;
				case 3:
					outtextxy(160,413,"Y"); h=1; hsize=ysize;
					hmin=ymin; hmax=ymax;
k:					vmin=(int)((double)zmin/nglas); vmax=(int)((double)zmax/nglas);
					v=2; outtextxy(110,353,"Z"); vsize=zsize; break;
				}
			kscale=(xsize > ysize)? xsize:ysize;
			kscale=(kscale > zsize)? (3500/kscale):(3500/zsize);
			xr = kscale*hsize/10; yt = kscale*vsize/10;
			if(f_invert) rectangle(120,410-yt,120+xr,410);
			outtextxy(110,413,"0");
			setcolor(BLACK); setfillstyle(1,COLBKL);
			gcvt(nglas,4,tmpstr);
			bar(501,86,559,100); outtextxy(510,90,tmpstr);
			bar(501,55,575,69); outtextxy(505,59,glstype);
			gcvt((double)xsize/10,4,tmpstr);
			bar(501,122,559,136); outtextxy(510,126,tmpstr);
			gcvt((double)ysize/10,4,tmpstr);
			bar(501,158,559,172); outtextxy(510,162,tmpstr);
			gcvt((double)zsize/10,4,tmpstr);
			bar(501,194,559,208); outtextxy(510,198,tmpstr);
			}
		switch(f_view) {
			case 0: hofs=xofs; vofs=yofs; break;
			case 1: hofs=yofs; vofs=xofs; break;
			case 2: hofs=xofs; vofs=zofs; break;
			case 3: hofs=yofs; vofs=zofs; break;
			}
		if(f_data) {
			setfillstyle(1,COLBKL);
			gcvt((double)(vsize*10-vmax-vofs)/100,4,tmpstr);
			bar(528,275,586,289); outtextxy(537,279,tmpstr);
			gcvt((double)(hmin+hofs)/100,4,tmpstr);
			bar(528,293,586,307); outtextxy(537,297,tmpstr);
			gcvt((double)(hsize*10-hmax-hofs)/100,4,tmpstr);
			bar(528,311,586,325); outtextxy(537,315,tmpstr);
			gcvt((double)(vmin+vofs)/100,4,tmpstr);
			bar(528,329,586,343); outtextxy(537,333,tmpstr);
			}
		i=(f_invert)? BLACK:WHITE; k=(f_invert)? COLDLG:BLACK;
		setfillstyle(1,k); bar(121,411-yt,119+xr,409);
		for(t=0; t<nmax; t++) {
			k=(f_mirror && (!h))?
				(int)((long)kscale*(10*hsize-iTabl[3*t+h]-hofs)/100) :
				(int)((long)kscale*(iTabl[3*t+h]+hofs)/100);
			m=(f_mirror && (f_view == 1))?
				(int)((long)kscale*(10*vsize-iTabl[3*t+v]-vofs)/100) :
				(int)((long)kscale*(iTabl[3*t+v]+vofs)/100);
			if((k>0)&&(k<xr)&&(m>0)&&(m<yt)) putpixel(120+k,410-m,i);
			}
		chpic0=0;
		i=scan_ms(btc_ed,bnam_ed,BNM_ED,0);
		switch(i) {
			case 0:
d:				nmax=0; lastn=0; f_data=0;
				strcpy(wrkfile,""); nmb_pbt=255; tout=0; return 0;
			case 1:
a:				if(dlgopen(wrkfile,"Enter name",1)) {
					if(!strcmp(wrkfile,"")) {msgbox("Enter file name",0,0); goto a;}
					strcpy(tmpstr,wrkfile);
					if(rddir(tmpstr)) if(!msgbox("Overwrite?",0,0)) goto a;
					msg(250,300,1,"Please wait /press ESC");
					for(t=0; t<nmax; t++) {
						iTabl[3*t]=(f_mirror)? 10*xsize-iTabl[3*t]-xofs :
							iTabl[3*t]+xofs;
						iTabl[3*t+1]+=yofs; iTabl[3*t+2]+=zofs;
						if(f_bca != 2) {
							iTabl[3*t+2]=(short)((double)iTabl[3*t+2]/nglas);
							}
						}
					if(!f_bca) wrt_bft(tmpstr);
					else if(f_bca == 1) wrt_cft(tmpstr);
					else {
						for(t=0; t<nmax; t++) {
							iTabl[3*t]-=5*xsize; iTabl[3*t+1]-=5*ysize;
							iTabl[3*t+2]-=5*zsize;
							}
						wrasc(tmpstr);
						}
					chdiska();
					f_data=1; lastn=0; nmb_pbt=255; tout=1; return 1;
					}
				chdiska(); goto b;
			case 2:
f:				if(dlgopen(tmpstr,"Data load",2)) {
					if(!rddir(tmpstr)) {msgbox("File not found",0,0); goto f;}
					msg(250,300,1,"Please wait");
					if(f_bcab == 2) {
						if(rdasc_t(tmpstr) == 1) {
							msg(250,300,0,""); msgbox("Buffer overflow",0,0); goto f;
							}
						msg(250,300,0,"");
						}
					else {
						if(!f_bcab) nmax=rdbft_t(tmpstr);
						else if(f_bcab==1) nmax=rdcft_t(tmpstr);
						else nmax=rdbmp(tmpstr);
						msg(250,300,0,"");
						if(!nmax) {
							if(f_bcab == 3) msgbox("Not B&W bmp file",0,0);
							else msgbox("Not flinttab file",0,0);
							goto f;
							}
						else if(nmax < 0) {msgbox("Buffer overflow",0,0); goto f;}
						else if(f_bcab != 3) {
							for(t=0; t<nmax; t++) {
								iTabl[3*t+2]=(int)((double)iTabl[3*t+2]*nglas);
								}
							}
						}
					strcpy(fasc,tmpstr); strcpy(glstype, ""); f_data=1;
					}
				else {f_data=0; nmax=0; strcpy(fasc,"");}
				chdiska(); goto c;
			case 3: f_view=(f_view > 2)? 0:(f_view +=1); break;
			case 4: xofs=(f_mirror)? xofs=-5*xsize : xofs=5*xsize;
				yofs=5*ysize; zofs=5*zsize; chpic0=1; break;
			case 5:
				if(!f_view) yofs=InrDcr(yofs,-23500,23500,25,1);
				else if(f_view == 1) xofs=InrDcr(xofs,-23500,23500,25,!f_mirror);
				else zofs=InrDcr(zofs,-11000,11000,25,1);
				chpic0=1; break;
			case 6:
				if(!h) xofs=InrDcr(xofs,-23500,23500,25,f_mirror);
				else yofs=InrDcr(yofs,-23500,23500,25,0);
				chpic0=1; break;
			case 7:
				if(!f_view) yofs=InrDcr(yofs,-23500,23500,25,0);
				else if(f_view == 1) xofs=InrDcr(xofs,-23500,23500,25,f_mirror);
				else zofs=InrDcr(zofs,-11000,11000,25,0);
				chpic0=1; break;
			case 8:
				if(!h) xofs=InrDcr(xofs,-23500,23500,25,!f_mirror);
				else yofs=InrDcr(yofs,-23500,23500,25,1);
				chpic0=1; break;
			case 9: nglas=(nglas > 1.999)? 2.000:(nglas + 0.001);
				strcpy(glstype,""); break;
			case 10: nglas=(nglas < 1.001)? 1.000:(nglas - 0.001);
				strcpy(glstype,""); break;
			case 11: xsize = InrDcr(xsize,10,2350,1,1); break;
			case 12: xsize = InrDcr(xsize,10,2350,1,0); break;
			case 13: ysize = InrDcr(ysize,10,2350,1,1); break;
			case 14: ysize = InrDcr(ysize,10,2350,1,0); break;
			case 15: zsize = InrDcr(zsize,10,1100,1,1); break;
			case 16: zsize = InrDcr(zsize,10,1100,1,0); break;
			case 17: dlgsort(); break;
			case 18:
				if(inp_dig(501,86,0.999,2.001,0)>0) strcpy(glstype,"");
				break;
			case 19: k=inp_dig(501,122,0.9,235.1,1);
				if(k>0) xsize=k; break;
			case 20: k=inp_dig(501,158,0.9,235.1,1);
				if(k>0) ysize=k; break;
			case 21: k=inp_dig(501,194,0.9,110.1,1);
				if(k>0) zsize=k; break;
			case 22: gselect(); goto b;
			case 23: f_mirror=(f_mirror)? 0:1; break;
			case 24: dlgdim(); break;
			case 25: minmax();
				xofs=5*xsize-(xmin+xmax)/2; yofs=5*ysize-(ymin+ymax)/2;
				zofs=5*zsize-(int)((double)(zmin+zmax)/(2*nglas));
				chpic0=1; break;
			case 26: f_invert=(f_invert)? 0:1; break;
			case 27: k=inp_dig(528,275,0,200,2);
				if(k>=0) vofs=vsize*10-vmax-k;
l:				if(!f_view) yofs=vofs;
				else if(f_view == 1) xofs=vofs;
				else zofs=vofs;
				break;
			case 28: k=inp_dig(528,293,0,200,2);
				if(k>=0) hofs=k-hmin;
r:				if((f_view==0)||(f_view==2)) xofs=hofs;
				else yofs=hofs;
				break;
			case 29: k=inp_dig(528,311,0,200,2);
				if(k>=0) hofs=hsize*10-hmax-k; goto r;
			case 30: k=inp_dig(528,329,0,200,2);
				if(k>=0) vofs=k-vmin; goto l;
			case 255:
				if(pkey == 27) goto d;
				/* v2.70: F9 XYZ hotkey */
				if(pkey == 67) {f_view=(f_view > 2)? 0:(f_view += 1); break;}
				break;
			}
		}
	}


void chdiska(void) {
	if((path[0]-'A')<2) {setdisk(wrkpath[0]-'A'); chdir(wrkpath);}
	}


long inp_dig(int xl, int yt, double min, double max, int ax) {
	int s; double d; char c,str[7];

	str[0]=0x5f;
	for(s=1; s<7; s++) str[s]=0;
	s=0; setcolor(BLACK);
	while(1) {
		setfillstyle(1,WHITE); bar(xl,yt,xl+58,yt+14);
		outtextxy(xl+9,yt+4,str);
		while(!kbhit()) ;
		c=getch();
		if((((c>0x2f)&&(c<0x3a))||(c==0x2e))&&(s<5)) {
			str[s]=c; s++; str[s]=0x5f;
			}
		if((c==8)&&(s>0)) {str[s]=0; s--; str[s]=0x5f;}
		if(c==27) return -1;
		if(c==13) {
			d = atof(str);
			if((d >= min)&&(d <= max)) {
				if(!ax) nglas=d;
				else if(ax==1) d*=10;
				else if(ax==2) d*=100;
				return (long)d;
				}
			else msgbox("Out of range",0,0);
			}
		}
	}


void glload(int direct) {
	msg(260,270,1,"Please wait");
	outportb(ADRPPI+2,inportb(ADRPPI+2)&STEP_ON); delay(30);
	move_sen(direct); outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF);
	msg(260,270,0,""); nmb_pbt=255;
	}


/* v2.77: Added PgUp/PgDn keyboard support */
int dlgload(void) {
	WndBkgr(180,180,450,400,COLDLG,"Glass Load");
	draw_bt(btc_gload,bnam_gload,BNM_GLOAD);
	rectangle(300,230,390,335); rectangle(310,294,350,312);
	outtextxy(310,240,"1   2   3"); outtextxy(338,260,"10");
	outtextxy(310,280,"4   5   6"); outtextxy(310,320,"7   8   9");
	while(1) {
		int i=scan_ms(btc_gload,bnam_gload,BNM_GLOAD,0);
		switch(i) {
			case 0: glload(0); do_ptr=1; return 0;				// Up
			case 1: glload(1); do_ptr=0; return 0;				// Down
a:			case 2: nmb_pbt=255; return 1;						// Cancel
			case 255:
				if(pkey == 27) goto a;								// Esc
				/* v2.77: PgUp/PgDn */
				if(pkey == 73) {glload(0); do_ptr=1; return 0;}	// PgUp->Up
				if(pkey == 81) {glload(1); do_ptr=0; return 0;}	// PgDn->Down
				break;
			}
		}
	}


int gselect(void) {
	int i,k,m,n,f_dr; double nglsnew;
	char *seprtr = "\n\t",tmpstr[16],str[9],glstypnew[9];

	nglsnew=nglas; strcpy(glstypnew,glstype);
	WndBkgr(100,170,520,410,GREEN,"Glass select");
	draw_bt(btc_gsel,bnam_gsel,BNM_GSEL);
	rectangle(119,214,251,341); rectangle(309,214,441,233);
	outtextxy(130,200,"Glass:  n:");
	setfillstyle(1,COLBKL); bar(310,215,440,232);
	setdisk(wrkpath[0]-'A'); chdir(wrkpath); k=rdgls(); m=0; f_dr=1;
	while(1) {
		if(f_dr) {
			setcolor(BLACK); setfillstyle(1,COLBKL); bar(120,215,250,340);
			for(i=0; ((i<12)&&(i<k-m)); i++) {
				strcpy(tmpstr, gtype[i+m]);
				outtextxy(130,220+10*i,strtok(tmpstr, seprtr));
				outtextxy(194,220+10*i,strtok(NULL, seprtr));
				}
			f_dr=0;
			}
		i=scan_ms(btc_gsel,bnam_gsel,BNM_GSEL,0);
		switch(i) {
a:			case 0: nglas=nglsnew; strcpy(glstype,glstypnew);
				i=1; goto c;
b:			case 1: i=0;
c:				nmb_pbt=255; setdisk(path[0]-'A'); chdir(path); return i;
			case 2: n=(coord[1]-220)/10;
				if((n+m)<k) {
					strcpy(tmpstr,gtype[n+m]); strcpy(str,strtok(tmpstr,seprtr));
					setfillstyle(1,COLBKL); bar(310,215,440,232);
					outtextxy(320,221,str);
					strcpy(glstypnew,str); strcpy(str,strtok(NULL,seprtr));
					outtextxy(384,221,str); nglsnew=(double)atof(str);
					} break;
			case 3: m=(m<2)? 0:(m-1); f_dr=1; break;
			case 4: if(k>10) m=(m>k-10)? k-9:(m+1); f_dr=1; break;
			case 255:
				if(pkey == 13) goto a;
				if(pkey == 27) goto b;
				break;
			}
		}
	}


/* v2.70: Removed ++/-- buttons, added direct Point number input
   BNM_STRT=14: 0-Ok,1-Cancel,2-+,3--,4-Beginning,5-PointNumber,
   6-Continuation,7-CMOS,8-EndSens,9-DrCheck,10-Stop,11-Reboot,12-Ignore,
   13-Input area */
int dlgstart(void) {
	char tmpstr[10],str[23]; int k,m,s,c,f_start; long st_nmbnew=lastn;
	f_start=2;
	WndBkgr(100,100,520,400,COLDLG,"Start");
	draw_bt(btc_strt,bnam_strt,BNM_STRT);
	line(103,212,517,212);
	line(236,156,275,156);
	outtextxy(120,281,"After noise:");
	rectangle(280,150,340,168); rectangle(120,291,380,360);
	while(1) {
		sw_ctl(f_start,0,120,130,COLDLG);						// Beginning
		sw_ctl(f_start,1,120,150,COLDLG);						// Point number
		sw_ctl(f_start,2,120,170,COLDLG);						// Continuation
		sw_ctl(f_start,3,120,190,COLDLG);						// CMOS
		sw_ctl(f_ptr,1,120,225,COLDLG);							// End sensors
		sw_ctl(d_check,1,120,245,COLDLG);						// Drawing check
		sw_ctl(f_noise,2,135,300,COLDLG);						// Stop
		sw_ctl(f_noise,1,135,320,COLDLG);						// Reboot
		sw_ctl(f_noise,0,135,340,COLDLG);						// Ignore
		setcolor(BLACK); setfillstyle(1,COLBKL);
		ltoa(st_nmbnew+1,tmpstr,10);
		bar(281,151,339,167); outtextxy(290,156,tmpstr);
		int i=scan_ms(btc_strt,bnam_strt,BNM_STRT,0);
		switch(i) {
			case 0:														// Ok
a:				if(!f_metal && !LCtl) { msgbox1("Laser is not enabled."); goto b; }
				m=minmax();
				if(m == 1) {
					if(st_nmbnew < nmax) {
						start_nmb=st_nmbnew;
						if((lastn != start_nmb)||(f_start != 2)) errnmb=0;
						lastn=start_nmb;
						nmb_pbt=255;
						if(!f_start) ClearRpt();
						mainscr(1);
						if((f_start == 1)||(!start_nmb)) outportb(ADRCMOS,0);
						outportb(ADRPPI+2,inportb(ADRPPI+2)&STEP_ON);
						delay(30);
#ifdef TRACE
						sprintf(_tbuf,"[START] st=%ld fstart=%d metal=%d dchk=%d",start_nmb,f_start,f_metal,d_check);
						tlog_write(_tbuf);
#endif
						k=process();
						outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF);
						FlashWr();
						if(k) return 1;
						ltoa(lastn,tmpstr,10); strcpy(str,"Finished point: ");
						strcat(str,tmpstr); msgbox(str,0,0); return 0;
						}
					msgbox("Start number > nmax",0,0);
					}
				else if(!m) msgbox("Data out of range",0,0);
				else msgbox("Data out of glass",0,0);
				break;
			case 1:														// Cancel
b:				nmb_pbt=255; return 0;
			case 2: if((f_start == 1) && nmax) {				// +
				st_nmbnew=(st_nmbnew>(nmax-2))? nmax-1:(st_nmbnew+1);
				} break;
			case 3: if((f_start == 1) && nmax) {				// -
				st_nmbnew=(st_nmbnew<1)? 0:(st_nmbnew-1);
				} break;
			/* v2.70: ++ and -- removed (were cases 4,5 in v2.61) */
			case 4: f_start=0; st_nmbnew=0; break;				// Beginning
			case 5: f_start=1; break;								// Point number
			case 6: f_start=2; st_nmbnew=lastn; break;		// Continuation
			case 7: f_start=3;										// Saved in CMOS
				st_nmbnew=(long)inportb(ADRCMOS+2)+(long)inportb(ADRCMOS+3)*256;
				break;
			case 8: f_ptr=(f_ptr)? 0:1; break;					// End Sensors
			case 9: d_check=(d_check)? 0:1;						// Drawing Check
				if(!d_check) errnmb=0; break;
			case 10: f_noise=2; break;								// Stop
			case 11: f_noise=1; break;								// Ptr auto reboot
			case 12: f_noise=0; break;								// Ignore
			case 13:														// v2.70: Direct input
				if((f_start == 1) && nmax) {
					long r = inp_dig(281,149,1.0,(double)nmax,3);
					if(r > 0) st_nmbnew = r - 1;
					}
				break;
			case 255:
				if(pkey == 13) goto a;
				if(pkey == 27) goto b;
				break;
			}
		}
	}


/* v2.74: merged counters, now 10 elements (was 20) */
void ClearRpt(void) {
	for(int k=0; k<10; k++) nmrpt[k]=0;
	}


/* v2.70: dlgstat() REMOVED - statistics shown in mainscr during processing */


/* v2.77: Added version display, Dr.check indicator, reiteration grid display
   v2.70: Reiteration display area
   v2.77: Version "2.77" shown; Dr.check ctlbt; show_reit grid; htime moved up */
void mainscr(int all) {
	char tmpstr[25]; int i;

	int xl=(all)? 0:144; int xr=(all)? 639:464;
	for(i=(!all); i<20; i++) {
		setfillpattern(&pattern[i][0],BLUE); bar(xl,16*i,xr,16*(i+1));
		}
	for(i=0; i<10; i++) {
		setfillpattern(&pattern[19-i][0],BLUE); bar(xl,16*(i+20),xr,16*(i+21));
		}
	setcolor(BLUE);
	outtextxy(170,310,"Institute for Laser Technologies");
	outtextxy(230,320,"and Engineering");
	if(all) {
		setfillstyle(1,BLUE);
		for(i=0; i<BNM_SCR; i++) {
			bar(btc_scr[6*i+2]-2,btc_scr[6*i+3]-2,
				btc_scr[6*i+2]+93,btc_scr[6*i+3]+21);
			}
		drawfl(); draw_bt(btc_scr, bnam_scr, BNM_SCR);
		/* v2.77: time estimation and version display */
		htime(tmpstr);
		setcolor(9); outtextxy(580,55,"2.77");
		setcolor(COLBKL);
		if(tout) outtextxy(20,235,tmpstr);
		ctlbt(30,50,COLBKL,"1"); ctlbt(30,70,COLBKL,"9");
		ctlbt(30,145,COLBKL,"Dr.check");
		setfillstyle(1,COL_ON);
		if(gl_nmb) {bar(31,71,39,79); glaspos(30,85,glpos9);}
		else bar(31,51,39,59);
		if(d_check) bar(31,146,39,154);
		outtextxy(20,30,"File:"); outtextxy(65,30,wrkfile);
		outtextxy(20,175,"Nmax:");
		ltoa(nmax,tmpstr,10); outtextxy(65,175,tmpstr);
		outtextxy(20,194,"Nlast:");
		outtextxy(30,270,"GLASS:"); outtextxy(30,285,"n:");
		gcvt(nglas,4,tmpstr); outtextxy(50,285,tmpstr);
		outtextxy(30,300,"X:");
		gcvt((double)xsize/10,4,tmpstr); outtextxy(50,300,tmpstr);
		outtextxy(30,313,"Y:");
		gcvt((double)ysize/10,4,tmpstr); outtextxy(50,313,tmpstr);
		outtextxy(30,326,"Z:");
		gcvt((double)zsize/10,4,tmpstr); outtextxy(50,326,tmpstr);
		rectangle(20,260,96,344);
		if(f_demo) {setcolor(COL_ON); outtextxy(565,85,"Demo");}
		setcolor(BLACK); setfillstyle(1,COLBKL); bar(31,206,86,222);
		ltoa(lastn,tmpstr,10); outtextxy(40,211,tmpstr);
		}
	setcolor(COLBKL); outtextxy(65,30,wrkfile);
	outtextxy(20,386,"Reiterations:");
	show_reit(0);
	if(f_data) draw(f_xyz,1);
	}


/* v2.77: Reiteration grid display — 3x3 glass position grid with counts.
   mode: 0=draw labels only, 1=fill active positions with COL_ON */
void show_reit(int mode) {
	char tmpstr[5]; int mask=1,i,k,color;

	setcolor(COLBKL); setfillstyle(1,BLACK);
	if(gl_nmb) {
		for(i=0; i<3; i++) {
			for(k=0; k<3; k++) {
				rectangle(k*42+10, i*16+404, k*42+50, i*16+418);
				if(mode) {
					color=(rpt_active & mask)? COL_ON : BLACK;
					setfillstyle(1,color);
					}
				bar(k*42+11, i*16+405, k*42+49, i*16+417);
				if(glpos9 & mask) {
					itoa(nmrpt[3*i+k],tmpstr,10);
					outtextxy(k*42+14, i*16+408, tmpstr);
					}
				mask<<=1;
				}
			}
		}
	else {
		rectangle(20, 404, 60, 418);
		bar(21, 405, 59, 417);
		itoa(nmrpt[9],tmpstr,10);
		outtextxy(24, 408, tmpstr);
		}
	}


void glaspos(int xl, int yt, int cw) {
	char str[2];
	unsigned int mask=0x01;
	for(int i=0; i<3; i++) {
		for(int k=0; k<3; k++) {
			rectangle(xl+16*k,yt+16*i,xl+16*k+14,yt+16*i+14);
			if(cw & mask) bar(xl+16*k+1,yt+16*i+1,xl+16*k+13,yt+16*i+13);
			mask<<=1;
			itoa(3*i+k+1,str,10); outtextxy(xl+16*k+4,yt+16*i+4,str);
			}
		}
	}


void drawfl(void) {
	int color,i,k,m,sh,mask;
	color=BLACK; sh=2;
	while(sh > 0) {
		sh--;
		for(i=0; i<34; i++) {
			for(k=0; k<15; k++) {
				mask=0x80;
				for(m=0; m<8; m++) {
					if(!(flint[15*i+k] & mask)) {
						putpixel(500+8*k+m+3*sh, 50-i+3*sh, color);
						}
					mask>>=1;
					}
				}
			}
		color=LIGHTBLUE;
		}
	}


void draw(int flag, int all) {
	long i; int k,hs,vs,hp,vp,hsize,vsize,color; double d;

	setcolor(COLBKL); outtextxy(X0-10,Y0+3,"0");
	switch(f_xyz) {
		case 0: outtextxy(X0-10,Y0-50,"Y"); outtextxy(X0+42,Y0+3,"X");
			hsize=xsize; vsize=ysize; break;
		case 1: outtextxy(X0-10,Y0-50,"X"); outtextxy(X0+42,Y0+3,"Y");
			hsize=ysize; vsize=xsize; break;
		case 2: outtextxy(X0+42,Y0+3,"X");  hsize=xsize; goto a;
		case 3: outtextxy(X0+42,Y0+3,"Y"); hsize=ysize;
a:			vsize=zsize; outtextxy(X0-10,Y0-50,"Z"); break;
			}
	k=(xsize > ysize)? xsize:ysize; k=(k > zsize)? (3000/k):(3000/zsize);
	vs=k*vsize/10; hs=k*hsize/10; rectangle(X0,Y0-vs,X0+hs,Y0);
	if(all) {
		setfillstyle(1,BLACK); bar(X0+1,Y0-vs+1,X0+hs-1,Y0-1);
		for(i=0; i<nmax; i++) {
			if(!flag) {hp=k*iTabl[3*i]/100; vp=k*iTabl[3*i+1]/100;}
			else if(flag == 1) {hp=k*iTabl[3*i+1]/100; vp=k*iTabl[3*i]/100;}
			else {
				d=iTabl[3*i+2]*nglas; vp=(int)(k*d/100);
				hp=k*iTabl[3*i+flag-2]/100;
				}
			color=(i<lastn)? COL_ON:COLBKL; DrawPix(hp,hs,vp,vs,color);
			}
		}
	else {
		if(!flag) {hp=k*iTabl[3*lastn]/100; vp=k*iTabl[3*lastn+1]/100;}
		else if(flag == 1) {hp=k*iTabl[3*lastn+1]/100; vp=k*iTabl[3*lastn]/100;}
		else {
			d=iTabl[3*lastn+2]*nglas;
			hp=k*iTabl[3*lastn+flag-2]/100; vp=(int)(k*d/100);
			}
		DrawPix(hp,hs,vp,vs,COL_ON);
		}
	}


void DrawPix(int hp,int hs, int vp, int vs, int color) {
	if((hp>0)&&(hp<hs)&&(vp>0)&&(vp<vs)) putpixel(X0+hp,Y0-vp,color);
	}


int draw_bt(int btc[], char *bnam[], int nmb) {
	for(int i=0; i<nmb; i++) {
		if(btc[6*i] == 1) button(btc,i,bnam[i]);
		else if(btc[6*i] == 3) ctlbt(btc[6*i+2], btc[6*i+3], BLACK, bnam[i]);
		}
	return 1;
	}


int dlgsort(void) {
	char tmpstr[16];

	WndBkgr(110,180,410,400,GREEN,"Sorting");
	draw_bt(btc_sort, bnam_sort, BNM_SORT);
	rectangle(290,262,350,280); rectangle(290,302,350,320);
	outtextxy(290,252,"K1:+dz"); outtextxy(290,292,"K2:-dz");
	outtextxy(130,335,"Pixels:");
	htime(tmpstr); setcolor(BLACK); outtextxy(130,350,tmpstr);
	while(1) {
		sw_ctl(f_sort,0,130,210,GREEN);
		sw_ctl(f_sort,1,130,230,GREEN);
		sw_ctl(f_sort,2,130,250,GREEN);
		setcolor(BLACK); setfillstyle(1,COLBKL);
		bar(291,263,349,279); outtextxy(300,268,itoa(sK1,tmpstr,10));
		bar(291,303,349,319); outtextxy(300,308,itoa(sK2,tmpstr,10));
		outtextxy(194,335,ltoa(nmax,tmpstr,10));
		int i = scan_ms(btc_sort, bnam_sort, BNM_SORT,0);
		switch(i) {
a:			case 0: nmb_pbt=255; return 1;
			case 1: f_sort=0; break;
			case 2: f_sort=1; break;
			case 3: f_sort=2; break;
			case 4: sK1 = (sK1>99)? 100:sK1+1; break;
			case 5: sK1 = (sK1<2)? 1:sK1-1; break;
			case 6: sK2 = (sK2>99)? 100:sK2+1; break;
			case 7: sK2 = (sK2<2)? 1:sK2-1; break;
			case 8: if(f_sort == 1) if(!sort()) {
b:					nmb_pbt=255; return 0;
					}
				if(f_sort == 2) if(!sort2()) goto b;
				htime(tmpstr); setcolor(BLACK); setfillstyle(1,GREEN);
				bar(130,350,266,358); outtextxy(130,350,tmpstr); break;
			case 255: if((pkey == 13)||(pkey == 27)) goto a; break;
			}
		}
	}


int sort(void) {
	long i,k,m,bgn,end,rmin,rmin1,rmin2,r,indx;
	short zminv;

	if(!nmax) return 0;
	getimage(160,464,460,474,bitmapmsg); progbar(nmax,0,1,160,464);
	for(i=0; i<(nmax-1); i++) {
		zminv=iTabl[3*i+2]; indx=0;
		for(k=i+1; k<nmax; k++) {
			if(iTabl[3*k+2]<zminv) {zminv=iTabl[3*k+2]; indx=k;}
			}
		if(indx) swap(i,indx);
		progbar(nmax,i,0,160,464); out_time(1);
		if(kbhit()) {
			if(getch()==ESC) {putimage(160,464,bitmapmsg,0); return 0;}
			}
		}
	putimage(160,464,bitmapmsg,0);
	progbar(nmax,0,1,160,464);
	zminv=iTabl[2]; bgn=0;
	for(i=1; i<=nmax; i++) {
		if((iTabl[3*i+2]>zminv+49)||(i == nmax)) {
			zminv=iTabl[3*i+2]; end=i-1;
			for(k=bgn; k<=end; k++) {
				rmin1=(long)abs(iTabl[3*(k+1)]-iTabl[3*k]);
				rmin2=(long)abs(iTabl[3*(k+1)+1]-iTabl[3*k+1]);
				rmin=(rmin1>rmin2)? rmin1:rmin2; indx=0;
				for(m=k+2; m<=end; m++) {
					rmin1=(long)abs(iTabl[3*m]-iTabl[3*k]);
					rmin2=(long)abs(iTabl[3*m+1]-iTabl[3*k+1]);
					r=(rmin1>rmin2)? rmin1:rmin2;
					if(r < rmin) {rmin=r; indx=m;}
					}
				if(indx) swap(k+1,indx);
				progbar(nmax,k,0,160,464); out_time(1);
				if(kbhit()) {
					if(getch()==ESC) {putimage(160,464,bitmapmsg,0); return 0;}
					}
				}
			bgn=i-1;
			}
		}
	putimage(160,464,bitmapmsg,0); return 1;
	}


int sort2(void) {
	long i,j,jmin,l,lmin; short zminv;

	if(!nmax) return 0;
	getimage(160,464,460,474,bitmapmsg); progbar(nmax,0,1,160,464);
	for(i=1; i<nmax; i++) {
		zminv=iTabl[2];
		if(iTabl[3*i+2]<zminv) swap(0,i);
		out_time(1); progbar(nmax,i,0,160,464);
		if(kbhit()) {
			if(getch()==ESC) {putimage(160,464,bitmapmsg,0); return 0;}
			}
		}
	putimage(160,464,bitmapmsg,0);
	progbar(nmax,0,1,160,464);
	for(i=0; i<nmax-2; i++) {
		lmin=cros(i,i+1); jmin=i+1;
		for(j=i+2; j<nmax; j++) {
			l=cros(i, j); if(l < lmin) {lmin=l; jmin=j;}
			}
		swap(jmin,i+1); progbar(nmax-2,i,0,160,464); out_time(1);
		if(kbhit()) {
			if(getch()==ESC) {putimage(160,464,bitmapmsg,0); return 0;}
			}
		}
	putimage(160,464,bitmapmsg,0); return 1;
	}


long cros(unsigned long k1, unsigned long k2) {
	unsigned long tdx,tdy,dr; long dz; int kk;
	k1*=3; k2*=3;
	tdx=(long)abs(iTabl[k2]-iTabl[k1]);
	tdy=(long)abs(iTabl[k2+1]-iTabl[k1+1]);
	dz=(long)(iTabl[k2+2]-iTabl[k1+2]);
	dr=(tdx>tdy)? tdx:tdy; kk=(dz>0)? sK1:sK2; dr+=(dz*kk)/10; return(dr);
	}


void swap(unsigned long k1, unsigned long k2) {
	short t;
	k1*=3; k2*=3;
	t=iTabl[k1]; iTabl[k1]=iTabl[k2]; iTabl[k2]=t;
	t=iTabl[k1+1]; iTabl[k1+1]=iTabl[k2+1]; iTabl[k2+1]=t;
	t=iTabl[k1+2]; iTabl[k1+2]=iTabl[k2+2]; iTabl[k2+2]=t;
	}


int minmax(void) {
	xmin=iTabl[0]; xmax=xmin;
	ymin=iTabl[1]; ymax=ymin;
	zmin=iTabl[2]; zmax=zmin;
	for(long i=1; i<nmax; i++) {
		if(xmin>iTabl[3*i]) xmin=iTabl[3*i];
		if(xmax<iTabl[3*i]) xmax=iTabl[3*i];
		if(ymin>iTabl[3*i+1]) ymin=iTabl[3*i+1];
		if(ymax<iTabl[3*i+1]) ymax=iTabl[3*i+1];
		if(zmin>iTabl[3*i+2]) zmin=iTabl[3*i+2];
		if(zmax<iTabl[3*i+2]) zmax=iTabl[3*i+2];
		}
	zmin=(int)((double)zmin*nglas);
	zmax=(int)((double)zmax*nglas);
	if(((xptr+xmin)<10)||((xptr+xmax)>23500)||((yptr+ymin)<10)||
		((yptr+ymax)>23500)||((zptr+zmin)<10)||((zptr+zmax)>12000)) return 0;
	else if((xmin < 0)||(xmax > xsize*10)||(ymin < 0)||(ymax > ysize*10)||
		(zmin < 0)||(zmax > zsize*10)) return -1;
	return 1;
	}


unsigned int scan_ms(int btc[], char *bnam[], int nbt, int f_beep) {
	int i, k, m;

	pkey=0;
	while(1) {
		i=ms_key_cmd(f_beep);
		if(i==0) {
			m=0;
			if((nmb_pbt != 255) && pressbt(btc,nmb_pbt)) {
				if(!btc[6*nmb_pbt+1]) return nmb_pbt;
				if(btc[6*nmb_pbt+1]==1) m=1;
				}
			else {
				for(k=0; k<nbt; k++) {
					if(pressbt(btc,k)) {
						if(btc[6*k]==1) buttonp(btc,k,bnam[k]);
						nmb_pbt=k;
						if(!btc[6*k+1]) return k;
						m=1;
						}
					}
				}
			if(!m && (nmb_pbt != 255)) {
				if(btc[6*nmb_pbt]==1) button(btc,nmb_pbt,bnam[nmb_pbt]);
				nmb_pbt=255;
				}
			}
		else if(i==1) {
			for(k=0; k<nbt; k++) {
				if(pressbt(btc,k)) {
					if(btc[6*k]==1) button(btc,nmb_pbt,bnam[nmb_pbt]);
					nmb_pbt=255;
					if(btc[6*k+1]==1) return k;
					}
				}
			}
		else {
			pkey=i; return 255;
			}
		}
	}


void progbar(long nmb_max, long nmb, int set, int xl, int yt) {
	unsigned int k,p; char str[4];

	p=(unsigned int)(((nmb+1)*100)/nmb_max); k=p/2;
	if(set) {
		k_old=0; p_old=-1;
		setfillstyle(1,LIGHTGRAY); bar(xl,yt,xl+254,yt+10);
		getimage(xl+265,yt+2,xl+289,yt+10,bgmap);
		setcolor(LIGHTRED); outtextxy(xl+290,yt+2,"%");
		}
	if(k_old != (int)k) {
		k_old=k;
		if(k_old != 0) {
			setfillstyle(1,BLUE);
			for(k=0; (int)k<k_old; k++) bar(xl+3+k*5,yt+2,xl+6+k*5,yt+8);
			}
		}
	if(p_old != (int)p) {
		p_old=p; setcolor(LIGHTRED); putimage(xl+265,yt+2,bgmap,0);
		outtextxy(xl+265,yt+2,itoa(p,str,10));
		}
	}


void htime(char tmpstr[]) {
	long i,tim=0; int tdx,tdy,tdz,t; char str[4];

	if(nmax) {
		getimage(160,464,460,474,bitmapmsg); progbar(nmax,0,1,160,464);
		for(i=0; i<nmax-1; i++) {
			tdx=iTabl[i+3]-iTabl[i]; tdy=iTabl[i+4]-iTabl[i+1]; tdz=iTabl[i+5]-iTabl[i+2];
			t=seg_time(tdx,tdy,tdz);
			tim+=(long)l_period*t; progbar(nmax,i,0,160,464);
			}
		putimage(160,464,bitmapmsg,0); tim/=1000;
		}
		strcpy(tmpstr,"Time: "); strcat(tmpstr,itoa((int)tim/3600,str,10));
		strcat(tmpstr,":"); strcat(tmpstr,itoa((int)(tim%3600)/60,str,10));
		strcat(tmpstr,":"); strcat(tmpstr,itoa((int)(tim%3600)%60,str,10));
	}


int dlgdim() {
	char str[7]; long k,t,tmp; int xc,yc,zc;

	WndBkgr(110,180,410,400,GREEN,"Dimensions Modification");
	draw_bt(btc_dim,bnam_dim,BNM_DIM);
	rectangle(190,222,250,240); rectangle(300,222,360,240);
	rectangle(300,262,360,280); rectangle(300,302,360,320);
	outtextxy(190,212,"K(%):");outtextxy(300,212,"Kx(%):");
	outtextxy(300,252,"Ky(%):");outtextxy(300,292,"Kz(%):");
	outtextxy(130,350,"Pixels:");
	line(145,230,185,230); line(145,270,295,270); line(295,222,295,320);
	while(1) {
		sw_ctl(fcdim,0,130,305,GREEN); sw_ctl(fcdim,1,130,325,GREEN);
		sw_ctl(feqk,1,130,225,GREEN); sw_ctl(feqk,0,130,265,GREEN);
		setfillstyle(1,COLBKL);
		bar(191,223,249,239); outtextxy(200,228,itoa(kdim,str,10));
		bar(301,223,359,239); outtextxy(310,228,itoa(kxdim,str,10));
		bar(301,263,359,279); outtextxy(310,268,itoa(kydim,str,10));
		bar(301,303,359,319); outtextxy(310,308,itoa(kzdim,str,10));
		ltoa(nmax,str,10); outtextxy(194,350,str);
		int i=scan_ms(btc_dim, bnam_dim, BNM_DIM,0);
		switch(i) {
a:			case 0: nmb_pbt=255; return 1;
			case 1: kdim=(kdim > 199)? 200:kdim+1; break;
			case 2: kdim=(kdim < 51)? 50:kdim-1; break;
b:			case 3: if(feqk) {kxdim=kdim; kydim=kdim; kzdim=kdim;}
				if(fcdim) {
					xc=5*xsize-xofs; yc=5*ysize-yofs; zc=5*zsize-zofs;
					for(k=0; k<nmax; k++) {
						t=3*k;
						tmp=(long)(iTabl[t]-xc)*kxdim/100+xc; iTabl[t]=(short)tmp;
						tmp=(long)(iTabl[t+1]-yc)*kydim/100+yc; iTabl[t+1]=(short)tmp;
						tmp=(long)(iTabl[t+2]-zc)*kzdim/100+zc; iTabl[t+2]=(short)tmp;
						}
					}
				else for(k=0; k<nmax; k++) {
					t=3*k;
					tmp=(long)(iTabl[t]+xofs)*kxdim/100-xofs; iTabl[t]=(short)tmp;
					tmp=(long)(iTabl[t+1]+yofs)*kydim/100-yofs; iTabl[t+1]=(short)tmp;
					tmp=(long)(iTabl[t+2]+zofs)*kzdim/100-zofs; iTabl[t+2]=(short)tmp;
					}
				nmb_pbt=255; return 0;
			case 4: fcdim=0; break;
			case 5: fcdim=1; break;
			case 6: feqk=1; break;
			case 7: feqk=0; break;
			case 8: kxdim=(kxdim > 199)? 200:kxdim+1; break;
			case 9: kxdim=(kxdim < 51)? 50:kxdim-1; break;
			case 10: kydim=(kydim > 199)? 200:kydim+1; break;
			case 11: kydim=(kydim < 51)? 50:kydim-1; break;
			case 12: kzdim=(kzdim > 199)? 200:kzdim+1; break;
			case 13: kzdim=(kzdim < 51)? 50:kzdim-1; break;
			case 255:
				if(pkey == 13) goto b;
				if(pkey == 27) goto a;
				break;
			}
		}
	}
