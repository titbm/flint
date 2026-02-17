/*********************************************************************
	proj5.cpp
	iB
			int main()
			void button(int btc[], int nmb, char buttxt[])
			void buttonp(int btc[], int nmb, char buttxt[])
			void ctlbt(int btxl, int btyl, int colctl, char ctltxt[])
			int pressbt(int btc[], int nmb)
			int msgbox(char msgtxt[], int more)
			void infobox(char msgtxt[])
			int msg(int msgx, int msgy, int onoff, char msgtxt[])
			int InrDcr(int param, int pmin, int pmax, int pstep, int updn)
			void sw_ctl(int flag, int param, int xpos, int ypos, int col)
			int dlgopen(char destnm[], char dlgnm[], int flag)
			int disksel(int nmb)
			void WndBkgr(int xl,int yt,int xr,int yb, int col,char txt[])
			int dlgcfg(void)
			int dlged(void)
			void chdiska(void)
			int inp_dig(int xl, int yt, double min, double max, int ax)
			void glload(int direct)
			int dlgload(void)
			int gselect(void)
			int dlgstart(void)
			void ClearRpt(void)
			int dlgstat(void)
			void mainscr(int all)
			void glaspos(int xl, int yt)
			void drawfl(void)
			void draw(int flag, int all)
			void DrawPix(int hp,int hs, int vp, int vs, int color)
			int draw_bt(int btc[], char *bnam[], int nmb)
			int dlgsort(void);
			int sort(void)
			int sort2(void)
			long cros(unsigned long k1, unsigned long k2)
			void swap(unsigned long k1, unsigned long k2)
			int minmax(void)
			unsigned int scan_ms(int btc[], char *bnam[], int nbt)
			void progbar(long nmb_max, long nmb, int set, int xl, int yt)
			long htime(void)
			int dlgdim()
*********************************************************************/
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <alloc.h>
#include <dir.h>
#include <bios.h>
#include <ctype.h>

#pragma hdrstop
#include "proj5.h"


int main() {
	int i, k, g_mode, g_error_code, all, g_driver=DETECT;
	char *strtmp;

	f_demo=0;
	f_bcab=0; f_bca=0; f_bc=0;						// default: *.bft, *.bft, *.bft
	f_sort=0; sK1=15; sK2=10;						// ���������� off, K1, K2
	f_xyz=0;		  										// ��� ����������� ��������: XY
	f_data=0; start_nmb=0; lastn=0;
	nmax=0; tout=0;
	do_ptr=0;	  										// ���������� �������� �����
	f_ptr=0;												// �������� � Start ����.
	strcpy(glstype,"K8");							// ����� ������ �� ���������
	nglas=1.506;										// n ������ -"-
	xsize=500; ysize=500; zsize=500;				// ������ ������� � 0.1mm
	xofs=0; yofs=0; zofs=0;
	xcur=0; ycur=0; zcur=0;
	dx=20; dy=20; dz=60;								// ��� ����� � ���������� bmp
	nmb_pbt=255;										// ������� ������ ���
	gl_nmb=1;											// 9 �������� (if 0 => 1 �������)
	d_check=1;											// �������� ��������� - ���.
	f_noise=0;											// ptr auto reboot
	k=1;													// ����� mainscreen
	all=1;												// ������ ������������
	fcdim=1; kdim=100;								// 100% around centre
	feqk=1; kxdim=100; kydim=100; kzdim=100;
	ClearRpt();											// clear reiteration numbers
	RdCfg(gl_nmb);										// ���� ���������� .cfg
	CurDir(); strcpy(wrkpath,path);
	if(registerfarbgidriver(EGAVGA_driver_far) < 0) {	// egavga.drv -> .exe
		printf("Graphics error"); return 255;
		}
	initgraph(&g_driver,&g_mode,"");				// ������������� �������������
	g_error_code=graphresult();
	if(g_error_code != grOk) {printf("graphics error"); return 255;}
	if(!pi_ini()) f_demo=0; // Force full mode						 	// �������� ������
	ms_init();										 	// ������������� ����
	set_gr_cursor(0,0,scr_cur_masks);
	ulMax=(unsigned long)farcoreleft()-30000;	// ��������� ������ ��� iTabl[]
	if((iTabl=(int huge *)farmalloc((ulMax=2400000UL))) == NULL) {
		ulMax=(unsigned long)farcoreleft()-30000;
		if((iTabl=(int huge *)farmalloc(ulMax)) == NULL) {
		printf("Allocation error"); goto b;
		}
	ulMax/=6;
	FlashRd();
	while(1) {
		setlinestyle(0,1,1);
		if(k) mainscr(all);
		all=1; k=1; i=scan_ms(btc_scr,bnam_scr,BNM_SCR);
		switch(i) {
			case 0:														// F9 XYZ
c:				f_xyz=(f_xyz > 2)? 0:f_xyz+1; all=0; break;
			case 1: dlgcfg(); break;								// F1 Config
			case 2: dlged(); break;									// F2 Convert
			case 3:														// F3 DatLoad
a:				if(dlgopen(strtmp,"Data load",0)) {
					lastn=0;
					if(!rddir(strtmp)) {msgbox("File not found",0); goto a;}
					msg(250,300,1,"Please wait");
					if(f_bc) nmax=rdcft_t(strtmp);				// *.cft -> iTabl[]
					else nmax=rdbft_t(strtmp);						// *.bft -> iTabl[]
					msg(250,300,0,"");
					if(!nmax) {msgbox("Not flinttab file",0); goto a;}
					else {
						if(nmax > 0) {f_data=1; strcpy(wrkfile,strtmp);}
						else {msgbox("Buffer overflow",0); goto a;}
						}
               tout=1;
					}
				else {strcpy(wrkfile,""); nmax=0; lastn=0; tout=0; f_data=0;}
				chdiska(); break;
			case 4: dlgload(); all=0; break;						// F4 GlsLoad
			case 5: dlgstart(); break;								// F5 Start
			case 6: dlgstat(); break;								// F6 Statist
			case 7:														// F7 Info
d:				infobox("2.61 iB"); k=0; break;
			case 8:														// F10 Exit
e:				if(msgbox("Exit?",0)) {
					farfree(iTabl);
b:					closegraph(); return 0;
					}
				k=0; break;
			case 255:
				switch(pkey) {
					case 59: dlgcfg(); break;
					case 60: dlged(); break;
					case 61: goto a;
					case 62: dlgload(); break;
					case 63: dlgstart(); break;
					case 64: dlgstat(); break;
					case 65: goto d;
					case 67: goto c;
					case 68: goto e;
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


int msgbox(char msgtxt[], int more) {
	getimage(180,290,385,345,bitmapmsg);
	setfillstyle(1,BLACK); bar(184,294,384,344);
	setfillstyle(1,COL_ON); bar(180,290,380,340);
	setcolor(BLACK); outtextxy(190,297,msgtxt);
	if(more) outtextxy(190,325,"Next pix:");
	draw_bt(btc_msg,bnam_msg,BNM_MSG+more);
	while(1) {
		int i=scan_ms(btc_msg, bnam_msg, BNM_MSG+more);
		putimage(180,290,bitmapmsg, 0);
		if(!i) return 1;						// Ok
		else if(i == 1) return 0;			// No
		else if(i == 2) return 2;			// Next
		else {if(pkey == 13) return 1; else return 0;}
		}
	}


void infobox(char msgtxt[]) {
	int i,k,m;
	unsigned int p,mask;

	getimage(178,260,392,344,bitmapmsg);
	setfillstyle(1,BLACK); bar(182,264,392,344);
	setfillstyle(1,CYAN); bar(178,260,388,340);
	setcolor(BLACK); outtextxy(255,272,"ILTiP Ltd");
	outtextxy(235,284,"RUSSIA Sosnovy Bor");
	outtextxy(235,296,"+7(81269)22622"); outtextxy(255,324,msgtxt);
	setfillstyle(1,BLUE); bar(189,271,221,303);
	for(i=0; i<28; i++) {
		for(k=0; k<4; k++) {
			p=fico[4*i+k]; mask=0x8000;
			for(m=0; m<8; m++) {
				if(p&mask) putpixel(190+8*k+m,301-i,LIGHTCYAN);
				mask >>=1;
				if(p&mask) putpixel(190+8*k+m,301-i,LIGHTRED);
				mask >>=1;
				}
			}
		}
	button(btc_info,0,bnam_info[0]);
	i=scan_ms(btc_info,bnam_info,BNM_INFO);
	putimage(178,260,bitmapmsg,0);
	}


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


int dlgcfg(void) {
	int i,x,y,z,xptrnew,yptrnew,zptrnew,stepnew,gl_nmbnew,lpnew;
	int sfnew,f_constnew,glp9new,ptr_work=0,f_make=0,f_rdcfg=0,pr_open=0;
	char *cret="\n",tmpstr[20],cfgmas[40];
	double d; struct date dd;

	setdisk(wrkpath[0]-'A'); chdir(wrkpath);
	xptrnew=xptr; yptrnew=yptr; zptrnew=zptr;
	stepnew=step; gl_nmbnew=gl_nmb; glp9new=glpos9;
	lpnew=l_period; sfnew=step_freq; f_constnew=f_const;
	WndBkgr(100,60,520,410,COLDLG,"Configuration");
	draw_bt(btc_cfg,bnam_cfg,BNM_CFG+9*gl_nmbnew);
	outtextxy(160,314,"Reset");
	outtextxy(130,245,"Flash nmb"); rectangle(130,255,226,271);
	outtextxy(130,277,"Service date"); rectangle(130,287,226,303);
	outtextxy(270,100,".cfg");
	outtextxy(400,130,"Step"); rectangle(400,140,460,156);
	outtextxy(400,175,"X"); rectangle(400,185,460,201);
	outtextxy(400,220,"Y"); rectangle(400,230,460,246);
	outtextxy(400,265,"Z"); rectangle(400,275,460,291);
	outtextxy(280,120,"Las.puls"); outtextxy(280,130,"period");
	rectangle(280,140,340,156); outtextxy(320,159,"ms");
	outtextxy(280,175,"Delay"); rectangle(280,185,340,201);
	outtextxy(320,204,"us");
	outtextxy(280,225,"Step"); outtextxy(280,235,"freq.");
	rectangle(280,245,340,261); outtextxy(320,264,"Hz");
	if(f_demo) outtextxy(120,340,"Demo");
	ultoa(ulMax,tmpstr,10); strcat(tmpstr," pixels max");
	outtextxy(120,350,tmpstr);
	rectangle(120,238,238,330);
	rectangle(265,110,510,370);
	while(1) {
		sw_ctl(gl_nmbnew,0,120,90,COLDLG);						// 1 glass
		sw_ctl(gl_nmbnew,1,120,105,COLDLG);						// 9 glasses
		sw_ctl(pr_open,1,120,160,COLDLG);						// protect open/close
		if(f_rdcfg) {
			RdCfg(gl_nmbnew); xptrnew=xptr; yptrnew=yptr; zptrnew=zptr;
			stepnew=step; lpnew=l_period; sfnew=step_freq; f_constnew=f_const;
			if(gl_nmbnew) glp9new=glpos9;
			f_rdcfg=0;
			}
		setfillstyle(1,COLDLG); bar(280,313,330,363);		// 9 glass positions
		setfillstyle(1,COL_ON);
		if(gl_nmbnew) glaspos(280,313,glp9new);
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
//		itoa(lpnew,tmpstr,10);										// Delay
		bar(281,186,339,200); outtextxy(290,190,tmpstr);
		itoa(sfnew,tmpstr,10);										// Step frequency
		bar(281,246,339,260); outtextxy(290,250,tmpstr);
		setfillstyle(1,COLBKL); bar(131,256,225,270);
		outtextxy(140,260,ultoa(ulFlash,cfgmas,10));			// Flash Nmb
		strcpy(tmpstr,itoa((ulService >> 24),cfgmas,10));
		strcat(tmpstr,"-");
		strcat(tmpstr,itoa(((ulService >> 16) & 0xff),cfgmas,10));
		strcat(tmpstr,"-");
		strcat(tmpstr,itoa((ulService & 0xffff),cfgmas,10));
		bar(131,288,225,302); outtextxy(140,292,tmpstr);	// Service Date
		if(ptr_work && f_make) {							// ��������� �������� �����
			outportb(ADRPPI+2,inportb(ADRPPI+2)&STEP_ON);
			msg(260,300,1,"Please wait"); delay(30);
			if(!do_ptr) {move_sen(0); do_ptr=1;}
			x=23500-xptrnew;			// ����������� �������� �� X � Z - ��������
			y=yptrnew; d=(1-1/nglas)*10*zsize; z=11000-zptrnew-(int)d;
			if(!move(x,y,z)) {
				outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF);
				msgbox("KPU error",0); return 0;
				}
			msg(260,300,0,""); f_make = 0;
			}
		i=scan_ms(btc_cfg,bnam_cfg,BNM_CFG+9*gl_nmbnew);
		switch(i) {
			case 0:														// Enter/Ok
a:				l_period=lpnew; step_freq=sfnew, f_const=f_constnew;
				xptr=xptrnew; yptr=yptrnew; zptr=zptrnew;
				step=stepnew; gl_nmb=gl_nmbnew; glpos9=glp9new; i=1; goto c;
			case 1:														// Esc/Cancel
b:				i=0;
c:				outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF|PR_CLOSE);
				sh_close(); nmb_pbt=255;
				setdisk(path[0]-'A'); chdir(path); FlashWr(); return i;
			case 2: f_rdcfg=1; f_make=1; break;					// Load .cfg
			case 3:														// Las.puls
				outportb(ADRPPI+2,inportb(ADRPPI+2)&PR_OPEN);
				sh_open(0x03ff);										// delay 50 ms
				outportb(ADRPPI+2,inportb(ADRPPI+2)&PULS_ON);
				outportb(ADRPPI+2,inportb(ADRPPI+2)|PULS_OFF);
				ulFlash++;
				if(!pr_open) {
					outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE); sh_close();
					}
				delay(50); break;
			case 4:														// Save .cfg
				if(msgbox("Are you sure?",0)) {
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
					itoa(sfnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					itoa(f_constnew,tmpstr,10);
					strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
					if(gl_nmbnew) {
						itoa(glp9new,tmpstr,10);			// glass positions -> cfg
						strcat(cfgmas,tmpstr); strcat(cfgmas,cret);
						wrfile("flint9.cfg",cfgmas,40);
						}
					else wrfile("flint1.cfg",cfgmas,40);
					} break;
			case 5: lpnew=InrDcr(lpnew,20,2000,5,1); break;			// LasPeriod+
			case 6: lpnew=InrDcr(lpnew,20,2000,5,0); break;			// LasPeriod-
			case 7: break;														// Delay+
			case 8: break;														// Delay-
			case 9: sfnew=InrDcr(sfnew,100,2000,100,1); break;		// StepFreq+
			case 10: sfnew=InrDcr(sfnew,100,2000,100,0); break;	// StepFreq-
			case 11:	stepnew=InrDcr(stepnew,10,1000,10,1); break;	// StepSize+
			case 12: stepnew=InrDcr(stepnew,10,1000,10,0); break;	// StepSize-
			case 13: xptrnew=InrDcr(xptrnew,0,23500,stepnew,1);	// Xptr+
				f_make=1; break;
			case 14: xptrnew=InrDcr(xptrnew,0,23500,stepnew,0);	// Xptr-
				f_make=1; break;
			case 15: yptrnew=InrDcr(yptrnew,0,23500,stepnew,1);	// Yptr+
				f_make=1; break;
			case 16: yptrnew=InrDcr(yptrnew,0,23500,stepnew,0);	// Yptr-
				f_make=1; break;
			case 17: zptrnew=InrDcr(zptrnew,0,11000,stepnew,1);	// Zptr+
				f_make=1; break;
			case 18: zptrnew=InrDcr(zptrnew,0,11000,stepnew,0);	// Zptr-
				f_make=1; break;
			case 19: gl_nmbnew=0; f_rdcfg=1; f_make=1; errnmb=0; break;	// 1 gl.
			case 20: gl_nmbnew=1; f_rdcfg=1; f_make=1; errnmb=0; break;	// 9 gl.
			case 21: pr_open=(pr_open)? 0:1;						// Protect open/close
				if(pr_open) {
					outportb(ADRPPI+2,inportb(ADRPPI+2)&PR_OPEN); sh_open(0x03ff);
					}
				else {outportb(ADRPPI+2,inportb(ADRPPI+2)|PR_CLOSE); sh_close();}
				break;
			case 22: ptr_work=(ptr_work)? 0:1;					// Work ptr on/off
				if(ptr_work) {
					if(msgbox("GLASS: n,size is true?",0)) f_make=1;
					else ptr_work=0;
					} break;
			case 23: f_constnew=1; break;				// Step frequence - constant
			case 24: f_constnew=0; break;				// Step frequence - variable
			case 25:											// Laser adjustment
				while(!kbhit()) {
					outportb(ADRPPI+2,inportb(ADRPPI+2)&PULS_ON);
					outportb(ADRPPI+2,inportb(ADRPPI+2)|PULS_OFF);
					delay(lpnew); out_time(1); ulFlash++;
					setfillstyle(1,COLBKL); bar(131,256,225,270);
					outtextxy(140,260,ultoa(ulFlash,tmpstr,10));
					} break;
			case 26:
				if(msgbox("Are you sure?",0)) {
					getdate(&dd);
					ulService=((unsigned long)dd.da_day<<24)+
					((unsigned long)dd.da_mon<<16)+dd.da_year;
					ulFlash=0; FlashWr();
					} break;
			case 27: glp9new ^= 0x0001; break;
			case 28: glp9new ^= 0x0002; break;
			case 29: glp9new ^= 0x0004; break;
			case 30: glp9new ^= 0x0008; break;
			case 31: glp9new ^= 0x0010; break;
			case 32: glp9new ^= 0x0020; break;
			case 33: glp9new ^= 0x0040; break;
			case 34: glp9new ^= 0x0080; break;
			case 35: glp9new ^= 0x0100; break;
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
	rectangle(264,174,376,301); rectangle(109,174,221,301);	// subdir.access
	rectangle(109,329,221,348); outtextxy(110,317,"Drive:");	// disk access
	rectangle(419,174,531,193);
	if(!flag) ff=f_bc;
	else if(flag == 1) ff=f_bca;
	else ff=f_bcab;
	m=0; n=0;
	while(1) {
		setfillstyle(1,GREEN); bar(420,220,580,335);					// bmp area
		if(ff == 3) {															// if *.bmp
			setcolor(BLACK); setfillstyle(1,COLBKL);
			rectangle(450,232,510,250); bar(451,233,509,249);
			rectangle(450,257,510,275); bar(451,258,509,274);
			rectangle(450,282,510,300); bar(451,283,509,299);
			outtextxy(420,237,"dx:"); outtextxy(420,262,"dy:");
			outtextxy(420,287,"dz:"); outtextxy(520,250,"0.1-1.5");
			outtextxy(520,287,"0-1.5"); outtextxy(490,222,"mm");
			gcvt((double)dx/100,4,str); outtextxy(460,238,str);	// dx
			gcvt((double)dy/100,4,str); outtextxy(460,263,str);	// dy
			gcvt((double)dz/100,4,str); outtextxy(460,288,str);	// dz
			}
		if(!ff) strcpy(fnmext,"*.bft");
		if(ff == 1) strcpy(fnmext,"*.cft");
		if(ff == 2) strcpy(fnmext,"*.asc");
		if(ff == 3) strcpy(fnmext,"*.bmp");
		rddir(fnmext);						// ����� fnmext, mname[], dname[]
		setfillstyle(1,GREEN);
		bar(110,160,580,168); outtextxy(110,160,path);			// path
		sw_ctl(ff,0,btc_opn[62],btc_opn[63], GREEN);				// *.bft
		sw_ctl(ff,1,btc_opn[68],btc_opn[69], GREEN);				// *.cft
		sw_ctl(ff,2,btc_opn[74],btc_opn[75], GREEN);				// *.asc
		sw_ctl(ff,3,btc_opn[80],btc_opn[81], GREEN);				// *.bmp
		setcolor(BLACK); setfillstyle(1,COLBKL);
		bar(110,175,220,300);											// SubDir area
		for(i=0; i<12; i++) outtextxy(120,180+10*i,dname[i+n]);
		bar(110,330,220,347);											// ChDisk area
		str[0]=getdisk()+'A'; str[1]=':'; str[2]=0;
		outtextxy(120,336,str); bar(265,175,375,300);			// FileNames area
		for(i=0; i<12; i++) outtextxy(275,180+10*i,strlwr(mname[i+m]));
		bar(420,175,530,192); outtextxy(430,181,fnamnew);
		k=(ff == 3)? 4:0;
		i = scan_ms(btc_opn,bnam_opn,BNM_OPN+flag+k);
		switch(i) {
			case 0:															// Enter/Ok
a:				strcpy(destnm,fnamnew);
				if(!flag) f_bc=ff;
				else if(flag == 1) f_bca=ff;
				else f_bcab=ff;
				nmb_pbt=255; return 1;
			case 1:															// Esc/Cansel
b:				nmb_pbt=255; return 0;
			case 2: n=(n<2)? 0:(n-1); break;							// SubDir Up
			case 3: if(lastd>10) n=(n>lastd-10)? lastd-9:n+1; break;		// Down
			case 4: k=(coord[1]-180)/10;								// SubDir area
				if((k+n)<=lastd) {
					strcpy(fnamnew,""); strcpy(dirnam,dname[k+n]);
					chdir(dirnam); n=0; m=0;
					} break;
			case 5: save=getdisk();										// ChDisk
				for (disk=0; disk<10; ++disk) {
					setdisk(disk); if(disk == getdisk()) k=disk;
					}
				setdisk(save); disk=disksel(k);
				if(disk == -1) break;
				if((disk < 2)&&(biosdisk(2,disk,0,1,1,1,mname)!=0)) {
					delay(300);
					if(biosdisk(2,disk,0,1,1,1,mname)!=0) {		// mname not in use
						msgbox("disk error",0); break;
						}
					}
				strcpy(fnamnew,""); setdisk(disk); break;
			case 6: m=(m<2)? 0:(m-1); break;							// FileNames Up
			case 7: if(lastf>10) m=(m>lastf-10)? lastf-9:m+1; break;		// Down
			case 8: k=(coord[1]-180)/10;								// FileNames area
				if((k+m)<=lastf) {
					setfillstyle(1,COLBKL); bar(420,175,530,192);
					outtextxy(430,181,mname[k+m]); strcpy(fnamnew,mname[k+m]);
					} break;
			case 9: str[0]=0x5f;											// Input FileName
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
			case 10: ff=0; goto d;										// *.bft
			case 11: ff=1; goto d;										// *.cft
			case 12: ff=2; goto d;										// *.asc
			case 13: ff=3;													// *.bmp
d:				strcpy(fnamnew,""); m=0; break;
			case 14: k=inp_dig(451,233,0.1,1.5,2); if(k>0) dx=k; break;	// dx
			case 15: k=inp_dig(451,258,0.1,1.5,2); if(k>0) dy=k; break;	// dy
			case 16: k=inp_dig(451,283,0,1.5,2); if(k>=0) dz=k; break;	// dz
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
		i=ms_key_cmd();
		if(i==1) {											// left button release
			if((170<coord[0])&&(coord[0]<210)&&(330<coord[1])&&(coord[1]<330+m)) {
				m=(coord[1]-330)/10; putimage(170,324,bitmapmsg,0); return m;
				}
			}
		if(i==ESC) {putimage(170,324,bitmapmsg,0); return -1;}
		}
	}


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
			sw_ctl(f_invert,1,505,221,COLDLG);						// Invert
			sw_ctl(f_mirror,1,505,234,COLDLG);						// Mirror
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
			gcvt(nglas,4,tmpstr);									// Glass parameters
			bar(501,86,559,100); outtextxy(510,90,tmpstr);		// Nglass
			bar(501,55,575,69); outtextxy(505,59,glstype);		// Glass type
			gcvt((double)xsize/10,4,tmpstr);							// Xsize
			bar(501,122,559,136); outtextxy(510,126,tmpstr);
			gcvt((double)ysize/10,4,tmpstr);							// Ysize
			bar(501,158,559,172); outtextxy(510,162,tmpstr);
			gcvt((double)zsize/10,4,tmpstr);							// Zsize
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
			gcvt((double)(vsize*10-vmax-vofs)/100,4,tmpstr);	//dT
			bar(528,275,586,289); outtextxy(537,279,tmpstr);
			gcvt((double)(hmin+hofs)/100,4,tmpstr);				//dL
			bar(528,293,586,307); outtextxy(537,297,tmpstr);
			gcvt((double)(hsize*10-hmax-hofs)/100,4,tmpstr);	//dR
			bar(528,311,586,325); outtextxy(537,315,tmpstr);
			gcvt((double)(vmin+vofs)/100,4,tmpstr);				//dB
			bar(528,329,586,343); outtextxy(537,333,tmpstr);
			}
		i=(f_invert)? BLACK:WHITE; k=(f_invert)? COLDLG:BLACK;
		setfillstyle(1,k); bar(121,411-yt,119+xr,409);
		for(t=0; t<nmax; t++) {											// Picture
			k=(f_mirror && (!h))?
				(int)((long)kscale*(10*hsize-iTabl[3*t+h]-hofs)/100) :
				(int)((long)kscale*(iTabl[3*t+h]+hofs)/100);
			m=(f_mirror && (f_view == 1))?
				(int)((long)kscale*(10*vsize-iTabl[3*t+v]-vofs)/100) :
				(int)((long)kscale*(iTabl[3*t+v]+vofs)/100);
			if((k>0)&&(k<xr)&&(m>0)&&(m<yt)) putpixel(120+k,410-m,i);
			}
		chpic0=0;
		i=scan_ms(btc_ed,bnam_ed,BNM_ED);
		switch(i) {
			case 0:															// Cancel
d:				nmax=0; lastn=0; f_data=0;
				strcpy(wrkfile,""); nmb_pbt=255; tout=0; return 0;
			case 1:															// Data Save
a:				if(dlgopen(wrkfile,"Enter name",1)) {
					if(!strcmp(wrkfile,"")) {msgbox("Enter file name",0); goto a;}
					strcpy(tmpstr,wrkfile);
					if(rddir(tmpstr)) if(!msgbox("Overwrite?",0)) goto a;
					msg(250,300,1,"Please wait /press ESC");
					for(t=0; t<nmax; t++) {
						iTabl[3*t]=(f_mirror)? 10*xsize-iTabl[3*t]-xofs :
							iTabl[3*t]+xofs;
						iTabl[3*t+1]+=yofs; iTabl[3*t+2]+=zofs;
						if(f_bca != 2) {
							iTabl[3*t+2]=(int)((double)iTabl[3*t+2]/nglas);
							}
						}
					if(!f_bca) wrt_bft(tmpstr);						// iTabl[]->*.bft
					else if(f_bca == 1) wrt_cft(tmpstr);			// iTabl[]->*.cft
					else {
						for(t=0; t<nmax; t++) {							// �������� ������
							iTabl[3*t]-=5*xsize; iTabl[3*t+1]-=5*ysize;
							iTabl[3*t+2]-=5*zsize;
							}
						wrasc(tmpstr);										// iTabl[]->*.asc
						}
					chdiska();
					f_data=1; lastn=0; nmb_pbt=255; tout=1; return 1;
					}
				chdiska(); goto b;
			case 2:															// Data Load
f:				if(dlgopen(tmpstr,"Data load",2)) {
					if(!rddir(tmpstr)) {msgbox("File not found",0); goto f;}
					msg(250,300,1,"Please wait");
					if(f_bcab == 2) {
						if(rdasc_t(tmpstr) == 1) {						// 3DSfile->iTabl[]
							msg(250,300,0,""); msgbox("Buffer overflow",0); goto f;
							}
						msg(250,300,0,"");
						}
					else {
						if(!f_bcab) nmax=rdbft_t(tmpstr);			// *.bft->iTabl[]
						else if(f_bcab==1) nmax=rdcft_t(tmpstr);	// *.cft->iTabl[]
						else nmax=rdbmp(tmpstr);						// *.bmp->iTabl[]
						msg(250,300,0,"");
						if(!nmax) {
							if(f_bcab == 3) msgbox("Not B&W bmp file",0);
							else msgbox("Not flinttab file",0);
							goto f;
							}
						else if(nmax < 0) {msgbox("Buffer overflow",0); goto f;}
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
			case 3: f_view=(f_view > 2)? 0:(f_view +=1); break;		// View XYZ
			case 4: xofs=(f_mirror)? xofs=-5*xsize : xofs=5*xsize;	// 0->Center
				yofs=5*ysize; zofs=5*zsize; chpic0=1; break;
			case 5:																	// up
				if(!f_view) yofs=InrDcr(yofs,-23500,23500,25,1);
				else if(f_view == 1) xofs=InrDcr(xofs,-23500,23500,25,!f_mirror);
				else zofs=InrDcr(zofs,-11000,11000,25,1);
				chpic0=1; break;
			case 6:																	// <-
				if(!h) xofs=InrDcr(xofs,-23500,23500,25,f_mirror);
				else yofs=InrDcr(yofs,-23500,23500,25,0);
				chpic0=1; break;
			case 7:																	// dn
				if(!f_view) yofs=InrDcr(yofs,-23500,23500,25,0);
				else if(f_view == 1) xofs=InrDcr(xofs,-23500,23500,25,f_mirror);
				else zofs=InrDcr(zofs,-11000,11000,25,0);
				chpic0=1; break;
			case 8:																	// ->
				if(!h) xofs=InrDcr(xofs,-23500,23500,25,!f_mirror);
				else yofs=InrDcr(yofs,-23500,23500,25,1);
				chpic0=1; break;
			case 9: nglas=(nglas > 1.999)? 2.000:(nglas + 0.001);		// + n
				strcpy(glstype,""); break;
			case 10: nglas=(nglas < 1.001)? 1.000:(nglas - 0.001);	// - n
				strcpy(glstype,""); break;
			case 11: xsize = InrDcr(xsize,10,2350,1,1); break;			// + Xsize
			case 12: xsize = InrDcr(xsize,10,2350,1,0); break;			// - Xsize
			case 13: ysize = InrDcr(ysize,10,2350,1,1); break;			// + Ysize
			case 14: ysize = InrDcr(ysize,10,2350,1,0); break;			// - Ysize
			case 15: zsize = InrDcr(zsize,10,1100,1,1); break;			// + Zsize
			case 16: zsize = InrDcr(zsize,10,1100,1,0); break;			// - Zsize
			case 17: dlgsort(); break;											// Sort
			case 18:															// Input nglass
				if(inp_dig(501,86,0.999,2.001,0)>0) strcpy(glstype,"");
				break;
			case 19: k=inp_dig(501,122,0.9,235.1,1);				// Input Xsize
				if(k>0) xsize=k; break;
			case 20: k=inp_dig(501,158,0.9,235.1,1);				// Input Ysize
				if(k>0) ysize=k; break;
			case 21: k=inp_dig(501,194,0.9,110.1,1);				// Input Zsize
				if(k>0) zsize=k; break;
			case 22: gselect(); goto b;								// Input glass type
			case 23: f_mirror=(f_mirror)? 0:1; break;				// Mirror
			case 24: dlgdim(); break;									// Dimensions
			case 25: minmax();											// C->Center
				xofs=5*xsize-(xmin+xmax)/2; yofs=5*ysize-(ymin+ymax)/2;
				zofs=5*zsize-(int)((double)(zmin+zmax)/(2*nglas));
				chpic0=1; break;
			case 26: f_invert=(f_invert)? 0:1; break;				// Invert
			case 27: k=inp_dig(528,275,0,200,2);					// Input dTop
				if(k>=0) vofs=vsize*10-vmax-k;
l:				if(!f_view) yofs=vofs;
				else if(f_view == 1) xofs=vofs;
				else zofs=vofs;
				break;
			case 28: k=inp_dig(528,293,0,200,2);					// Input dLeft
				if(k>=0) hofs=k-hmin;
r:				if((f_view==0)||(f_view==2)) xofs=hofs;
				else yofs=hofs;
				break;
			case 29: k=inp_dig(528,311,0,200,2);					// Input dRight
				if(k>=0) hofs=hsize*10-hmax-k; goto r;
			case 30: k=inp_dig(528,329,0,200,2);					// Input dBottom
				if(k>=0) vofs=k-vmin; goto l;
			case 255: if(pkey == 27) goto d;							// ESC
			}
		}
	}


void chdiska(void) {
	if((path[0]-'A')<2) {setdisk(wrkpath[0]-'A'); chdir(wrkpath);}
	}


int inp_dig(int xl, int yt, double min, double max, int ax) { // ���� �����
	int s; double d; char c,str[7];

	str[0]=0x5f;
	for(s=1; s<7; s++) str[s]=0;
	s=0; setcolor(BLACK);
	while(1) {
		setfillstyle(1,WHITE); bar(xl,yt,xl+58,yt+14);
		outtextxy(xl+9,yt+4,str);
		while(!kbhit()) out_time(1);
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
				else d*=100;
				return (int)d;
				}
			else msgbox("Out of range",0);
			}
		}
	}


void glload(int direct) {
	msg(260,270,1,"Please wait");
	outportb(ADRPPI+2,inportb(ADRPPI+2)&STEP_ON); delay(30);
	move_sen(direct); outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF);
	msg(260,270,0,""); nmb_pbt=255;
	}


int dlgload(void) {
	WndBkgr(180,180,450,400,COLDLG,"Glass Load");
	draw_bt(btc_gload,bnam_gload,BNM_GLOAD);
	rectangle(300,230,390,335); rectangle(310,294,350,312);
	outtextxy(310,240,"1   2   3"); outtextxy(338,260,"10");
	outtextxy(310,280,"4   5   6"); outtextxy(310,320,"7   8   9");
	while(1) {
		int i=scan_ms(btc_gload,bnam_gload,BNM_GLOAD);
		switch(i) {
			case 0: glload(0); do_ptr=1; return 0;				// Up
			case 1: glload(1); do_ptr=0; return 0;				// Down
a:			case 2: nmb_pbt=255; return 1;						// Cancel
			case 255: if(pkey == 27) goto a; break;			// Esc
			}
		}
	}


int gselect(void) {													// Glass select
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
		i=scan_ms(btc_gsel,bnam_gsel,BNM_GSEL);
		switch(i) {
a:			case 0: nglas=nglsnew; strcpy(glstype,glstypnew);	// Ok
				i=1; goto c;
b:			case 1: i=0;													// Cancel
c:				nmb_pbt=255; setdisk(path[0]-'A'); chdir(path); return i;
			case 2: n=(coord[1]-220)/10;								// Glas type area
				if((n+m)<k) {
					strcpy(tmpstr,gtype[n+m]); strcpy(str,strtok(tmpstr,seprtr));
					setfillstyle(1,COLBKL); bar(310,215,440,232);
					outtextxy(320,221,str);
					strcpy(glstypnew,str); strcpy(str,strtok(NULL,seprtr));
					outtextxy(384,221,str); nglsnew=(double)atof(str);
					} break;
			case 3: m=(m<2)? 0:(m-1); f_dr=1; break;						// Up
			case 4: if(k>10) m=(m>k-10)? k-9:(m+1); f_dr=1; break;	// Down
			case 255:
				if(pkey == 13) goto a;
				if(pkey == 27) goto b;
				break;
			}
		}
	}


int dlgstart(void) {
	char tmpstr[10],str[23]; int k,m,f_start; long st_nmbnew=lastn;
	f_start=2;
	WndBkgr(100,100,520,400,COLDLG,"Start");
	draw_bt(btc_strt,bnam_strt,BNM_STRT);
	line(103,212,517,212); line(236,156,275,156);
	outtextxy(120,281,"After noise:");
	rectangle(280,150,340,168); rectangle(120,291,380,360);
	while(1) {
		sw_ctl(f_start,0,120,130,COLDLG);
		sw_ctl(f_start,1,120,150,COLDLG);
		sw_ctl(f_start,2,120,170,COLDLG);
		sw_ctl(f_start,3,120,190,COLDLG);
		sw_ctl(f_ptr,1,120,225,COLDLG);
		sw_ctl(d_check,1,120,245,COLDLG);
		sw_ctl(f_noise,2,135,300,COLDLG);
		sw_ctl(f_noise,1,135,320,COLDLG);
		sw_ctl(f_noise,0,135,340,COLDLG);
		setcolor(BLACK); setfillstyle(1,COLBKL);
		ltoa(st_nmbnew+1,tmpstr,10);								// Number
		bar(281,151,339,167); outtextxy(290,156,tmpstr);
		int i=scan_ms(btc_strt,bnam_strt,BNM_STRT);
		switch(i) {
			case 0:														// Ok
a:				m=minmax();
				if(m == 1) {			// ��������: ��� ����� � ��������� �����
					if(st_nmbnew < nmax) {
						start_nmb=st_nmbnew;
	// � �������, ����� "Continuation", ��� ��� ������!=Nlast ����� errnmb
						if((lastn != start_nmb)||(f_start != 2)) errnmb=0;
						lastn=start_nmb;	// ����� ������ �������� ��� errnmb!=0
						nmb_pbt=255; mainscr(1);
	// � ������ "Point Number" ��� ��� ������ = 0 ����� ����-��������
						if((f_start == 1)||(!start_nmb)) outportb(ADRCMOS,0);
						outportb(ADRPPI+2,inportb(ADRPPI+2)&STEP_ON);
						delay(30);
						if(!f_start) ClearRpt();					// ����� rpt
						k=process();
						outportb(ADRPPI+2,inportb(ADRPPI+2)|STEP_OFF);
						FlashWr();
						if(k) return 1;
						ltoa(lastn,tmpstr,10); strcpy(str,"Finished point: ");
						strcat(str,tmpstr); msgbox(str,0); return 0;
						}
					msgbox("Start number > nmax",0);
					}
				else if(!m) msgbox("Data out of range",0);
				else msgbox("Data out of glass",0);
				break;
			case 1:														// Cancel
b:				nmb_pbt=255; return 0;
			case 2: if((f_start == 1) && nmax) {				// +
				st_nmbnew=(st_nmbnew>(nmax-2))? nmax-1:(st_nmbnew+1);
				} break;
			case 3: if((f_start == 1) && nmax) {				// -
				st_nmbnew=(st_nmbnew<1)? 0:(st_nmbnew-1);
				} break;
			case 4: if((f_start == 1) && nmax) {				// ++
				st_nmbnew=(st_nmbnew>(nmax-11))? nmax-1:(st_nmbnew+10);
				} break;
			case 5: if((f_start == 1) && nmax) {				// --
				st_nmbnew=(st_nmbnew<10)? 0:(st_nmbnew-10);
				} break;
			case 6: f_start=0; st_nmbnew=0; break;				// Beginning
			case 7: f_start=1; break;								// Point number
			case 8: f_start=2; st_nmbnew=lastn; break;		// Continuation
			case 9: f_start=3;										// Saved in CMOS
				st_nmbnew=(long)inportb(ADRCMOS+2)+(long)inportb(ADRCMOS+3)*256;
				break;
			case 10: f_ptr=(f_ptr)? 0:1; break;					// End Sensors
			case 11: d_check=(d_check)? 0:1;						// Drawing Check
				if(!d_check) errnmb=0; break;
			case 12: f_noise=2; break;								// Stop
			case 13: f_noise=1; break;								// Ptr auto reboot
			case 14: f_noise=0; break;								// Ignore
			case 255:
				if(pkey == 13) goto a;								// Enter
				if(pkey == 27) goto b;								// Esc
				break;
			}
		}
	}


void ClearRpt(void) {
	for(int k=0; k<20; k++) nmrpt[k]=0;
	}


int dlgstat(void) {
	char tmpstr[10], str[40];
   int i;

	WndBkgr(100,130,520,400,COLDLG,"Statistics");
	draw_bt(btc_stat, bnam_stat, BNM_STAT);
	line(103,198,517,198); FlashRd(); outtextxy(130,160,"Total flash nmb:");
	outtextxy(320,160,ultoa(ulFlash,str,10));
	outtextxy(130,172,"Service date:");
	strcpy(str,itoa((ulService>>24),tmpstr,10)); strcat(str,"-");
	strcat(str,itoa(((ulService>>16) & 0xff),tmpstr,10));
	strcat(str,"-"); strcat(str,itoa((ulService & 0xffff),tmpstr,10));
	outtextxy(320,172,str); setfillstyle(1,COL_ON);
	if(errnmb & 0x0200) bar(320,210,372,242);
	rectangle(320,210,372,242); int mask = 0x0001;
	for(i=0;i<9;i++) {						// Errnmb ������� -> ������� ���
		if(errnmb&mask) bar(321+55*(i%3),256+35*(i/3),371+55*(i%3),286+35*(i/3));
		rectangle(320+55*(i%3), 255+35*(i/3), 372+55*(i%3), 287+35*(i/3));
		mask<<=1;
		}
	ltoa(nmax,tmpstr,10); strcpy(str,"Total px.nmb.: ");
	strcat(str,tmpstr); outtextxy(130,225,str);
	if(lastn) {
		ltoa(lastn,tmpstr,10); strcpy(str,"Stopped after: ");
		strcat(str,tmpstr); outtextxy(130,240,str);
		}
	outtextxy(130,265,"Reiterations: 1st"); outtextxy(242,275,"next");
	outtextxy(130,310,"Total:"); long k=0;
	for(i=0; i<10; i++) k+=nmrpt[2*i];
	ltoa(k,tmpstr,10); outtextxy(190,310,tmpstr); k=0;
	for(i=0; i<10; i++) k+=nmrpt[2*i+1];
	ltoa(k,tmpstr,10); outtextxy(190,320,tmpstr);
	if(gl_nmb) {													// ��� �������� �1 - �9
		outtextxy(325,215,"-"); mask=0x0001;
		for(i=0; i<9; i++) {
			if(glpos9 & mask) {
				itoa(nmrpt[2*i],tmpstr,10);
				outtextxy(325+(i%3)*55,260+(i/3)*35,tmpstr);
				itoa(nmrpt[2*i+1],tmpstr,10);
				outtextxy(325+(i%3)*55,270+(i/3)*35,tmpstr);
				}
			else outtextxy(325+(i%3)*55,260+(i/3)*35,"-");
			mask<<=1;
			}
		}
	else {															// ��� ������� �10
		itoa(nmrpt[18],tmpstr,10); outtextxy(325,215,tmpstr);
		itoa(nmrpt[19],tmpstr,10); outtextxy(325,225,tmpstr);
		for(i=0; i<9; i++) outtextxy(325+(i%3)*55,260+(i/3)*35,"-");
		}
	while(1) {
		i=scan_ms(btc_stat,bnam_stat,BNM_STAT);
		switch(i) {
a:			case 0: nmb_pbt=255; return 0;									// Ok
			case 255: if((pkey == 13)||(pkey == 27)) goto a; break;	// Enter|Esc
			}
		}
	}


void mainscr(int all) {
	char tmpstr[25]; int i;

	int xl=(all)? 0:144; int xr=(all)? 639:464;
	for(i=(!all); i<20; i++) {									// background
		setfillpattern(&pattern[i][0],BLUE); bar(xl,16*i,xr,16*(i+1));
		}
	for(i=0; i<10; i++) {
		setfillpattern(&pattern[19-i][0],BLUE); bar(xl,16*(i+20),xr,16*(i+21));
		}
	out_time(0); setcolor(BLUE);
	outtextxy(170,310,"Institute for Laser Technologies");
	outtextxy(230,320,"and Engineering");
	if(all) {
		setfillstyle(1,BLUE);
		for(i=0; i<BNM_SCR; i++) {
			bar(btc_scr[6*i+2]-2,btc_scr[6*i+3]-2,
				btc_scr[6*i+2]+93,btc_scr[6*i+3]+21);
			}
		drawfl(); draw_bt(btc_scr, bnam_scr, BNM_SCR);
		setcolor(COLBKL); ctlbt(30,50,COLBKL,"1"); ctlbt(30,70,COLBKL,"9");
		setfillstyle(1,COL_ON);
		if(gl_nmb) {bar(31,71,39,79); glaspos(30,85,glpos9);}
		else bar(31,51,39,59);
		outtextxy(20,30,"File:"); outtextxy(65,30,wrkfile);
		outtextxy(20,145,"Nmax:");
		ltoa(nmax,tmpstr,10); outtextxy(65,145,tmpstr);
		outtextxy(20,164,"Nlast:");
		outtextxy(30,240,"GLASS:"); outtextxy(30,260,"n:");	// Glass parameters
		gcvt(nglas,4,tmpstr); outtextxy(50,260,tmpstr);
		outtextxy(30,280,"X:");
		gcvt((double)xsize/10,4,tmpstr); outtextxy(50,280,tmpstr);
		outtextxy(30,300,"Y:");
		gcvt((double)ysize/10,4,tmpstr); outtextxy(50,300,tmpstr);
		outtextxy(30,320,"Z:");
		gcvt((double)zsize/10,4,tmpstr); outtextxy(50,320,tmpstr);
		rectangle(20,230,96,340);
		if(f_demo) {setcolor(LIGHTRED); outtextxy(30,360,"Demo");}
		setcolor(BLACK); setfillstyle(1,COLBKL); bar(31,176,86,192);
		ltoa(lastn,tmpstr,10); outtextxy(40,181,tmpstr);	// � ������.���.�����
		if(tout) {htime(tmpstr); setcolor(COLBKL); outtextxy(20,205,tmpstr);}
		}
	setcolor(COLBKL); outtextxy(65,30,wrkfile);
	if(f_data) draw(f_xyz,1);
	}


void glaspos(int xl, int yt, int cw) {			// ���� - ������ ����������
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
		int i = scan_ms(btc_sort, bnam_sort, BNM_SORT);
		switch(i) {
a:			case 0: nmb_pbt=255; return 1;						// Close
			case 1: f_sort=0; break;
			case 2: f_sort=1; break;
			case 3: f_sort=2; break;
			case 4: sK1 = (sK1>99)? 100:sK1+1; break;
			case 5: sK1 = (sK1<2)? 1:sK1-1; break;
			case 6: sK2 = (sK2>99)? 100:sK2+1; break;
			case 7: sK2 = (sK2<2)? 1:sK2-1; break;
			case 8: if(f_sort == 1) if(!sort()) {				// Sort/Time
b:					nmb_pbt=255; return 0;
					}
				if(f_sort == 2) if(!sort2()) goto b;
				htime(tmpstr); setcolor(BLACK); setfillstyle(1,GREEN);
            bar(130,350,266,358); outtextxy(130,350,tmpstr); break;
			case 255: if((pkey == 13)||(pkey == 27)) goto a; break;	// Close|Esc
			}
		}
	}


int sort(void) {
	long i,k,m,ti,tk,tm,bgn,end,rmin,rmin1,rmin2,r,indx;
   unsigned int zmin;

	if(!nmax) return 0;
	getimage(160,464,460,474,bitmapmsg); progbar(nmax,0,1,160,464);	// 300*10
	for(i=0; i<(nmax-1); i++) {									// ���������� �� Z
		zmin=iTabl[3*i+2]; indx=0;
		for(k=i+1; k<nmax; k++) {
			tk=3*k+2;
         if(iTabl[tk]<zmin) {zmin=iTabl[tk]; indx=k;}
			}
		if(indx) swap(i,indx);
      progbar(nmax,i,0,160,464); out_time(1);
		if(kbhit()) {
      	if(getch()==ESC) {putimage(160,464,bitmapmsg,0); return 0;}
         }
		}
	putimage(160,464,bitmapmsg,0);
   progbar(nmax,0,1,160,464);
	zmin=iTabl[2]; bgn=0;											// ���������� � dZ=50
	for(i=1; i<=nmax; i++) {
		ti=3*i+2;
		if((iTabl[ti]>zmin+49)||(i == nmax)) {					// i ��� dZ=50
			zmin=iTabl[ti]; end=i-1;
			for(k=bgn; k<=end; k++) {				// ���������� �� min(max(dX,dY))
				tk=3*k;
            rmin1=(long)abs(iTabl[tk+3]-iTabl[tk]);		// dX
				rmin2=(long)abs(iTabl[tk+4]-iTabl[tk+1]);		// dY
				rmin=(rmin1>rmin2)? rmin1:rmin2; indx=0;
				for(m=k+2; m<=end; m++) {
					tm=3*m;
               rmin1=(long)abs(iTabl[tm]-iTabl[tk]);
					rmin2=(long)abs(iTabl[tm+1]-iTabl[tk+1]);
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
	long i,j,jmin,l,lmin; int zmin;

	if(!nmax) return 0;
	getimage(160,464,460,474,bitmapmsg); progbar(nmax,0,1,160,464);	// 300*10
	for(i=1; i<nmax; i++) {                               // ����� Zmin
		zmin=iTabl[2];
      if(iTabl[3*i+2]<zmin) swap(0,i);
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


inline long cros(unsigned long k1, unsigned long k2) {
   unsigned long dx,dy,dr; long dz; int k;

	k1*=3; k2*=3;
	dx=(long)abs(iTabl[k2]-iTabl[k1]);
   dy=(long)abs(iTabl[k2+1]-iTabl[k1+1]);
	dz=(long)(iTabl[k2+2]-iTabl[k1+2]);
	dr=(dx>dy)? dx:dy; k=(dz>0)? sK1:sK2; dr+=(dz*k)/10; return(dr);
	}


inline void swap(unsigned long k1, unsigned long k2) {
   int t;

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
		((yptr+ymax)>23500)||((zptr+zmin)<10)||((zptr+zmax)>11000)) return 0;
	else if((xmin < 0)||(xmax > xsize*10)||(ymin < 0)||(ymax > ysize*10)||
		(zmin < 0)||(zmax > zsize*10)) return -1;
	return 1;
	}


unsigned int scan_ms(int btc[], char *bnam[], int nbt) {
	int i, k, m;

	pkey=0;
	while(1) {
		i=ms_key_cmd();
		if(i==0) {							// ���� ������
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
		else if(i==1) {					// ���� ��������
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
		getimage(xl+265,yt+2,xl+289,yt+10,bgmap);					// 24*8
		setcolor(LIGHTRED); outtextxy(xl+290,yt+2,"%");
		}
	if(k_old != k) {
		k_old=k;
		if(k_old != 0) {
			setfillstyle(1,BLUE);
			for(k=0; k<k_old; k++) bar(xl+3+k*5,yt+2,xl+6+k*5,yt+8);
			}
		}
	if(p_old != p) {
		p_old=p; setcolor(LIGHTRED); putimage(xl+265,yt+2,bgmap,0);
      outtextxy(xl+265,yt+2,itoa(p,str,10));
		}
	}


void htime(char tmpstr[]) {
	long i,tim=0; int dx,dy,dz,t,r; char str[4];

	if(nmax) {
		getimage(160,464,460,474,bitmapmsg); progbar(nmax,0,1,160,464);  // 24*8
		for(i=0; i<nmax-1; i++) {
			dx=abs(iTabl[i+3]-iTabl[i]); dy=abs(iTabl[i+4]-iTabl[i+1]);
			dz=abs(iTabl[i+5]-iTabl[i+2]); t=(dx>dy)? dx:dy;
			if(t<dz) t=dz;
			r=(int)((long)l_period*step_freq/1000);
			if(t<r) t=r;
			tim+=(unsigned long)t; progbar(nmax,i,0,160,464);
			}
		putimage(160,464,bitmapmsg,0); tim/=step_freq;
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
		int i=scan_ms(btc_dim, bnam_dim, BNM_DIM);
		switch(i) {
a:			case 0: nmb_pbt=255; return 1;									// Cancel
			case 1: kdim=(kdim > 199)? 200:kdim+1; break;				// K+
			case 2: kdim=(kdim < 51)? 50:kdim-1; break;					// K-
b:			case 3: if(feqk) {kxdim=kdim; kydim=kdim; kzdim=kdim;}	// Ok
				if(fcdim) {
					xc=5*xsize-xofs; yc=5*ysize-yofs; zc=5*zsize-zofs;	// 10*size/2
					for(k=0; k<nmax; k++) {
						t=3*k;
						tmp=(long)(iTabl[t]-xc)*kxdim/100+xc; iTabl[t]=(int)tmp;
						tmp=(long)(iTabl[t+1]-yc)*kydim/100+yc; iTabl[t+1]=(int)tmp;
						tmp=(long)(iTabl[t+2]-zc)*kzdim/100+zc; iTabl[t+2]=(int)tmp;
						}
					}
				else for(k=0; k<nmax; k++) {
					t=3*k;
					tmp=(long)(iTabl[t]+xofs)*kxdim/100-xofs; iTabl[t]=(int)tmp;
					tmp=(long)(iTabl[t+1]+yofs)*kydim/100-yofs; iTabl[t+1]=(int)tmp;
					tmp=(long)(iTabl[t+2]+zofs)*kzdim/100-zofs; iTabl[t+2]=(int)tmp;
					}
				nmb_pbt=255; return 0;
			case 4: fcdim=0; break;										// from 0
			case 5: fcdim=1; break;										// from centre
			case 6: feqk=1; break;	 									// equal kx,ky,kz
			case 7: feqk=0; break;										// not equal
			case 8: kxdim=(kxdim > 199)? 200:kxdim+1; break;	// Kx+
			case 9: kxdim=(kxdim < 51)? 50:kxdim-1; break;		// Kx-
			case 10: kydim=(kydim > 199)? 200:kydim+1; break;	// Ky+
			case 11: kydim=(kydim < 51)? 50:kydim-1; break;		// Ky-
			case 12: kzdim=(kzdim > 199)? 200:kzdim+1; break;	// Kz+
			case 13: kzdim=(kzdim < 51)? 50:kzdim-1; break;		// Kz-
			case 255:
				if(pkey == 13) goto b;
				if(pkey == 27) goto a;
				break;
			}
		}
	}

