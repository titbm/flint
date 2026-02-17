/*************************************************************
	file rdwrf.cpp
	iB

		int rdfile(char filename[], char masname[], unsigned int nmb)
		int wrfile(char filename[], char masname[], unsigned int nmb)
		void RdCfg(int gl_nmber)
		void FlashRd(void)
		void FlashWr(void)
		void CurDir(void)
		int rddir(char f_namext[])
		void sort_fnm(void)
		void sort_dnm(void)
		long rdcft_t(char filename[])
		int rdgls(void)
		int rdasc_t(char filename[])
		int wrasc(char filename[])
		int wrt_cft(char filename[])
		int wrt_bft(char filename[])
		long rdbft_t(char filename[])
		long rdbmp(char filename[])
**************************************************************/
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dir.h>
#include <errno.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>

static char foerr[] = {"File open error"};
char mname[100][13];
char dname[50][13];
extern char gtype[50][16];
char path[MAXPATH];
extern char wrkpath[MAXPATH];
int lastd;								// номер последнего поддиректори€
int lastf;								// номер последнего файла в директории
extern long nmax;						// номер последней точки таблицы
extern int xofs, yofs, zofs;		// смещение 3D объекта в образце
extern double nglas;					// показатель преломлени€ стекла
extern int xsize, ysize, zsize;	// размер образца в 0.1 мм
extern int huge *iTabl;
extern unsigned long ulMax;
extern unsigned int dx, dy, dz;	// in KPU steps
extern unsigned long ulFlash;
extern unsigned long ulService;
extern int xptr, yptr, zptr;		// координаты точки отсчета (прив€зки)
extern int l_period;					// мин.период лазера в мс
extern int step_freq;				// частота шагов привода в √ц
extern int f_const;					// частота шагов: 1-const,0-variable
extern unsigned int step;			// размер шага при юстировке
extern unsigned int glpos9;		// используемые позиции из 9

void CurDir(void);
void sort_fnm(void);
void sort_dnm(void);
void out_time(int newt);
int msgbox(char msgtxt[], int more);
int msg(int msgx, int msgy, int onoff, char msgtxt[]);


int rdfile(char filename[], char masname[], unsigned int nmb) {
	FILE *fin;

	if((fin=fopen(filename,"rb")) == NULL) {msgbox(foerr,0); return 1;}
	fread(masname,sizeof(char),nmb,fin); fclose(fin); return 0;
	}


int wrfile(char filename[], char masname[], unsigned int nmb) {
	FILE *fout;

	if((fout=fopen(filename,"wb")) == NULL) {msgbox(foerr,0); return 1;}
	clearerr(fout); fwrite(masname,sizeof(char),nmb,fout);
	fclose(fout); return 0;
	}


void RdCfg(int gl_nmber) {
	char *cret="\n", *strtmp, cfgmas[40];

	if(gl_nmber) rdfile("flint9.cfg",cfgmas,40);
	else rdfile("flint1.cfg",cfgmas,40);
	strtmp=strtok(cfgmas,cret); xptr=atoi(strtmp);
	strtmp=strtok(NULL,cret); yptr=atoi(strtmp);
	strtmp=strtok(NULL,cret); zptr=atoi(strtmp);
	strtmp=strtok(NULL,cret); step=atoi(strtmp);
	strtmp=strtok(NULL,cret); l_period=atoi(strtmp);
	strtmp=strtok(NULL,cret); step_freq=atoi(strtmp);
	strtmp=strtok(NULL,cret); f_const=atoi(strtmp);
	if(gl_nmber) {strtmp=strtok(NULL,cret); glpos9=atoi(strtmp);}
	}


void FlashRd(void) {
	FILE *fin; unsigned char mas[8]; char old_dir[MAXDIR];

	CurDir(); strcpy(old_dir,path); chdir(wrkpath);
	if((fin=fopen("flash.dat","rb")) == NULL) msgbox(foerr,0);
	fread(mas,1,8,fin); fclose(fin);
	ulFlash=((unsigned long)mas[0]<<24)+((unsigned long)mas[1]<<16)
		+((unsigned long)mas[2]<<8)+mas[3];
	ulService=((unsigned long)mas[4]<<24)+((unsigned long)mas[5]<<16)
		+((unsigned long)mas[6]<<8)+mas[7];
	chdir(old_dir);
	}


void FlashWr(void) {
	FILE *fout; unsigned char mas[8];
	char old_dir[MAXDIR];

	mas[0]=(unsigned char)(ulFlash >> 24);
	mas[1]=(unsigned char)((ulFlash >> 16) & 0xff);
	mas[2]=(unsigned char)((ulFlash >> 8) & 0xff);
	mas[3]=(unsigned char)(ulFlash & 0xff);
	mas[4]=(unsigned char)(ulService >> 24);
	mas[5]=(unsigned char)((ulService >> 16) & 0xff);
	mas[6]=(unsigned char)((ulService >> 8) & 0xff);
	mas[7]=(unsigned char)(ulService & 0xff);
	CurDir(); strcpy(old_dir,path); chdir(wrkpath);
	if((fout=fopen("flash.dat","wb")) == NULL) msgbox(foerr,0);
	fwrite(mas,1,8,fout); fclose(fout); chdir(old_dir);
	}


void CurDir(void) {
	strcpy(path,"X:\\"); path[0]='A'+getdisk(); getcurdir(0,path+3);
	}


int rddir(char f_namext[]) {
	int i,k,done; struct ffblk ffbl;

	lastf=0;
	for(i=0; i<60; i++) for(k=0; k<13; k++) mname[i][k]=0;
	for(i=0; i<30; i++) for(k=0; k<10; k++) dname[i][k]=0;
	CurDir(); i=0;
	done=findfirst("*",&ffbl,FA_DIREC);					// SubDirs in current dir
	if((ffbl.ff_name[0]=='.')&&(ffbl.ff_name[1]!='.')) done=findnext(&ffbl);
	while(!done) {
		for(k=0; k<13; k++) dname[i][k]=ffbl.ff_name[k];
		lastd=i; i+=1;
		if(i == 48) done=1;
		else done=findnext(&ffbl);
		}
	sort_dnm(); i=0; done=findfirst(f_namext,&ffbl,0);	// Files in current dir
	if(done) return 0;
	while(!done) {
		for(k=0; k<13; k++) mname[i][k]=ffbl.ff_name[k];
		lastf=i; i+=1;
		if(i == 98) done=1;
		else done=findnext(&ffbl);
		}
	sort_fnm(); return 1;
	}


void sort_fnm(void) {
	int i,m,k,s; char c;

	for(i=0; i<lastf; i++) {
		for(m=i+1; m<=lastf; m++) {
			for(k=0; k<8; k++) {
				if(mname[m][k] < mname[i][k]) {
					for(s=0; s<13; s++) {
						c=mname[m][s]; mname[m][s]=mname[i][s]; mname[i][s]=c;
						}
					k=8;
					}
				if(mname[m][k] > mname[i][k]) k=8;
				}
			}
		}
	}


void sort_dnm(void) {
	int i,m,k,s; char c;

	if((dname[0][0]=='.')&&(dname[0][1]=='.')) m=1;
	else m=0;
	for(i=m; i<lastd; i++) {
		for(m=i+1; m<=lastd; m++) {
			for(k=0; k<8; k++) {
				if(dname[m][k] < dname[i][k]) {
					for(s=0; s<13; s++) {
						c=dname[m][s]; dname[m][s]=dname[i][s]; dname[i][s]=c;
						}
					k=8;
					}
				if(dname[m][k] > dname[i][k]) k=8;
				}
			}
		}
	}


long rdcft_t(char filename[]) {
	char string[32],*strtmp,*seprtr="\t\n";
	FILE *fptr; int i; unsigned long ln=0; double d;	// ln - file line number

	if((fptr=fopen(filename, "r")) == NULL) {msgbox(foerr,0); return 0;}
	fgets(string,32,fptr); strtmp=strtok(string, seprtr);
	if(strcmp(strtmp,"flinttab")) {fclose(fptr); return 0;}
	fgets(string,32,fptr);									// nglas
	strtmp=strtok(string,seprtr); strtmp=strtok(NULL,seprtr);
	nglas=atof(strtmp);
	fgets(string,32,fptr);									// xsize
	strtmp=strtok(string,seprtr); strtmp=strtok(NULL,seprtr);
	d=atof(strtmp)*10; xsize=(int)d;
	fgets(string,32,fptr);									// ysize
	strtmp=strtok(string,seprtr); strtmp=strtok(NULL,seprtr);
	d=atof(strtmp)*10; ysize=(int)d;
	fgets(string,32,fptr);									// zsize
	strtmp=strtok(string,seprtr); strtmp=strtok(NULL,seprtr);
	d=atof(strtmp)*10; zsize=(int)d;
	for(; fgets(string,32,fptr)!=NULL; ln++) {
		strtmp=strtok(string,seprtr);						// point number not in use
		for(i=0; i<3; i++) {
			strtmp=strtok(NULL,seprtr); iTabl[3*ln+i]=atoi(strtmp);
			}
		if(ln == ulMax) {fclose(fptr); return -1;}	// проверка на переполнение
		}
	fclose(fptr); return ln;
	}


int rdgls(void) {
	FILE *fptr; int i,k; char string[16];

	for(i=0; i<50; i++) for(k=0; k<16; k++) gtype[i][k]=0x00;
	if((fptr=fopen("flint.gls","r")) == NULL) {msgbox(foerr,0); return 0;}
	for(i=0; fgets(string,32,fptr)!=NULL; i++) strcpy(gtype[i],string);
	fclose(fptr); return i;
	}


int rdasc_t(char filename[]) {
	unsigned long i=0; char string[64],*strtmp; FILE *fpr;
	double ddig; char *seprtr=" ", *xlbl="X:", *ylbl="Y:", *zlbl="Z:";

	if((fpr=fopen(filename,"r")) == NULL) {msgbox(foerr,0); return -1;}
	for(; fgets(string,64,fpr) != NULL;) {
		if(strstr(string,xlbl)) {						// "X:" ?
			strtmp=strtok(string,seprtr);
			while(strtmp != NULL) {
				if(!stricmp(strtmp,xlbl)) {			// "X:" ?
					strtmp=strtok(NULL,seprtr); ddig=10*atof(strtmp);
					iTabl[3*i]=(int)(ddig/1);
					}
				else if(!stricmp(strtmp, ylbl)) {	// "Y:" ?
					strtmp=strtok(NULL,seprtr); ddig=10*atof(strtmp);
					iTabl[3*i+1]=(int)(ddig/(-1));
					}
				else if(!stricmp(strtmp,zlbl)) {		// "Z:" ?
					strtmp=strtok(NULL,seprtr); ddig=10*atof(strtmp);
					iTabl[3*i+2]=(int)(ddig/1);
					}
				strtmp=strtok(NULL,seprtr);
				}
			i++;
			if(i == ulMax) {								// проверка на переполнение
				fclose(fpr); nmax=0; return 1;
				}
			out_time(1);
			}
		}
	fclose(fpr); nmax=i; return 0;
	}


int wrasc(char filename[]) {
	FILE *fpw; char string[65],strtmp[10];
	long nmb; double dig; unsigned int k;

	for(k=0; k<8; k++) {			// file name -> object name
		if(filename[k+6] == 0x2e) strtmp[k]=0x00;
		else strtmp[k]=filename[k+6];
		}
	strtmp[8]=0x00;
	if((fpw=fopen(filename,"w")) == NULL) {msgbox(foerr,0); return 1;}
	strcpy(string,"Ambient light color: ");
	strcat(string,"Red=0.039216 Green=0.039216 Blue=0.039216\n\n");
	fputs(string,fpw);
	strcpy(string,"Named object: \""); strcat(string,strtmp);
	strcat(string,"\"\n"); fputs(string,fpw);
	strcpy(string,"Tri-mesh, Vertices: ");
	ltoa(nmax,strtmp,10); strcat(string,strtmp);
	strcat(string,"     Faces: 0\nVertex list:\n"); fputs(string,fpw);
	for(nmb=0; nmb<nmax; nmb++) {
		ltoa(nmb,strtmp,10); strcpy(string,"Vertex ");
		strcat(string,strtmp); strcat(string,":  X: ");
		dig=(double)iTabl[3*nmb]/10; gcvt(dig,6,strtmp);
		strcat(string,strtmp); strcat(string,"     Y: ");
		dig=(double)(-iTabl[3*nmb+1])/10; gcvt(dig,6,strtmp);
		strcat(string,strtmp); strcat(string,"     Z: ");
		dig=(double)iTabl[3*nmb+2]/10; gcvt(dig,6,strtmp);
		strcat(string,strtmp); strcat(string,"\n");
		fputs(string,fpw); out_time(1);
		}
	fclose(fpw); return 0;
	}


int wrt_cft(char filename[]) {
	long i; FILE *fpw; double d; char strdst[33],strtmp[10];
	char *dbp=":\t",*tab="\t",*cr="\n";

	if((fpw=fopen(filename,"w")) == NULL) {msgbox(foerr,0); return -1;}
	strcpy(strdst,"flinttab"); strcat(strdst,cr); fputs(strdst,fpw);
	strcpy(strdst,"nglass="); strcat(strdst,tab);
	gcvt(nglas,4,strtmp); strcat(strdst,strtmp);
	strcat(strdst,cr); fputs(strdst,fpw);
	strcpy(strdst,"xsize="); strcat(strdst,tab);
	d=(double)xsize/10; gcvt(d,4,strtmp); strcat(strdst,strtmp);
	strcat(strdst,cr); fputs(strdst,fpw);
	strcpy(strdst,"ysize="); strcat(strdst,tab);
	d=(double)ysize/10; gcvt(d,4,strtmp); strcat(strdst,strtmp);
	strcat(strdst,cr); fputs(strdst,fpw);
	strcpy(strdst,"zsize="); strcat(strdst,tab);
	d=(double)zsize/10; gcvt(d,4,strtmp); strcat(strdst,strtmp);
	strcat(strdst,cr); fputs(strdst,fpw);
	for(i=0; i<nmax; i++) {
		ltoa(i+1,strdst,10); strcat(strdst,dbp);					// "i:\t"
		itoa(iTabl[3*i],strtmp,10);									// "X\t"
		strcat(strdst,strtmp); strcat(strdst,tab);
		itoa(iTabl[3*i+1],strtmp,10);									// "Y\t"
		strcat(strdst,strtmp); strcat(strdst,tab);
		itoa(iTabl[3*i+2],strtmp,10);									// "Z\t"
		strcat(strdst,strtmp); strcat(strdst,cr); fputs(strdst,fpw);
		out_time(1);
		}
	fclose(fpw); return 0;
	}


int wrt_bft(char filename[]) {
	FILE *fout; unsigned int tmp[7];

	tmp[0]=0x6662;												// "bf"
	tmp[1]=(unsigned int)(nglas*1000);
	tmp[2]=xsize; tmp[3]=ysize; tmp[4]=zsize;
	tmp[5]=(unsigned int)(nmax/65536); tmp[6]=(unsigned int)(nmax%65536);
	if((fout=fopen(filename,"wb")) == NULL) {msgbox(foerr,0); return 1;}
	clearerr(fout); fwrite(tmp,sizeof(int),7,fout);
	fwrite(iTabl,12,(unsigned int)(nmax/2+nmax%2),fout);
	fclose(fout); return 0;
	}


long rdbft_t(char filename[]) {
	FILE *fin; unsigned int tmp[7]; unsigned long nmb;

	if ((fin=fopen(filename,"rb")) == NULL) {msgbox(foerr,0); return 1;}
	fread(tmp,sizeof(int),7,fin);
	if(tmp[0] != 0x6662){fclose(fin); return 0;}					// "bf" - ?
	nglas=(float)tmp[1]/1000; xsize=tmp[2]; ysize=tmp[3]; zsize=tmp[4];
	nmb=(long)65536*tmp[5]+tmp[6];
	if(nmb > ulMax) {fclose(fin); return -1;}						// переполнение?
	fread(iTabl,12,(unsigned int)(nmb/2+nmb%2),fin);
	fclose(fin); return nmb;
	}


long rdbmp(char filename[]) {
	FILE *fin; unsigned int tmp[31],uiXBmp,uiYBmp,i,k,m,n; long nmb,l;
	unsigned char p,mask,ucSBmp[256];			// max 2048 точек в строке bmp

	if ((fin=fopen(filename,"rb")) == NULL) {msgbox(foerr,0); return 1;}
	fread(tmp,sizeof(int),31,fin);
	if(tmp[0] != 0x4d42) {fclose(fin); return 0;}						// "BM"?
	uiXBmp=tmp[9]; uiYBmp=tmp[11]; l=(long)(tmp[1]+65536*tmp[2]);	// size
	n=uiXBmp/8+((uiXBmp%8)? 1:0);
	if(n%4) n=(n/4+1)*4;								//  ол-во байт на строку в *.bmp
	if(l != (long)n*uiYBmp+62) {fclose(fin); return 0;}		// B&W *.bmp ?
	nmb=0; l=ulMax;
	for(i=0; i<uiYBmp; i++) {
		fread(ucSBmp,sizeof(unsigned char),n,fin);
		for(k=0; k<n; k++) {
			p=ucSBmp[k]; mask=0x80;
			for(m=0; m<8; m++) {
				if((8*k+m) < uiXBmp) {
					if(!(p&mask)) {
						iTabl[3*nmb]=(8*k+m)*dx; iTabl[3*nmb+1]=i*dy;
						iTabl[3*nmb+2]=((8*k+m)%2 == i%2)? 0:dz; nmb+=1;
						if(nmb > l) {fclose(fin); return -1;}		// переполнение? 
						}
					}
				mask >>=1;
				}
			}
		out_time(1);
		}
	fclose(fin); l=(long)uiXBmp*dx/10; xsize=(int)l;
	l=(long)uiYBmp*dy/10; ysize=(int)l; zsize=100; return nmb;
	}

