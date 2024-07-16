/* testing ptree data analysis on yisun.dat raster files */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <fftw3.h>

#define ESCAPE_KEY 27
#define SPACE_KEY 32
#define ENTER_KEY 10
#define PI 3.141592653589793
#define maximum(A,B) ((A) > (B) ? (A) : (B))
#define minimum(A,B) ((A) < (B) ? (A) : (B))
#define periodize(A,B,C) ((A) < (B) ? (A) + (C) - (B) : ((A) >= (C) ? (A) - (C) + (B) : (A)))
#define crop(A,B,C) ((A) < (B) ? (B) : ((A) > (C) ? (C) : (A)))
#define rand01 ((double)rand()/(double)RAND_MAX)
#define entry(j,k,n) ((j) + (k)*(n)) /* This defines index for entry (j,k) in row major order (not 'fortran') n by m matrix */

#define RGB3 3 // 3 bytes of color info per pixel
#define RGBA 4 // 4 bytes of color+alpha info
#define UCHAR_MAX 255 // is this right?

#include "inputhandling.h"
#include "matrices.h"
#include "d_llists.h"
#include "ptreehandling.h"

/* Here are the method functions */
void setglobals();
void setdependencies();
void Lra_to_raster(struct llist **,int,double,double);

/* These are the real global variables */
int MEMDEBUG=0;
void * MEMDEBUGLIST=NULL;

/* These are convenient global variables */
int GLOBAL_verbose=0;
int ON_MY_COMPUTER=1;
double STD_VIEW=1;
int GRAYSCALE=0;
char GLOBAL_STRING[64];
char GLOBAL_STRING_2[128];
int GLOBAL_RECORD_NUMBER=0;
double GLOBAL_TI=0;
double GLOBAL_TF=0;
double GLOBAL_time=0;
int PTREE_BOTHER=0;
int GLOBAL_PTREE_BITBYBIT=0;
int GLOBAL_PTREE_BITBYBIT_CURRENT_NUMBER=0;
int GLOBAL_PTREE_ZZZ=1;
struct ptree *GLOBAL_PTREE=NULL;
int GLOBAL_PTREE_NREGIONS=8;
int GLOBAL_PTREE_NLEGS=0;
int GLOBAL_PTREE_LEGTIME=0;
int GLOBAL_PTREE_EVENT_THRESHOLD=1;
double GLOBAL_PTREE_EVENT_WITHIN=1;
int GLOBAL_PTREE_REGION_TYPE=1;
struct llist **GLOBAL_Lra=NULL;
struct litem **GLOBAL_lra=NULL;
int GLOBAL_Lra_length=0;
int GLOBAL_Yisun_length=0;

#include "inputhandling.c"
#include "matrices.c"
#include "d_llists.c"
#include "ptreehandling.c"

/* Here are the method functions */

void setdependencies()
{
  /* merely enforces global dependencies */
  sprintf(GLOBAL_STRING_2,"%s_%d",GLOBAL_STRING,GLOBAL_RECORD_NUMBER);
}

void Lra_to_raster(struct llist **Lra,int length,double t1,double t2)
{
  char filename[1024],filename_base[512],command[4096];
  FILE *fp=NULL;
  int nr=0;
  struct litem *l=NULL;
  double xpos=0,ypos=0,maxdia=10000,xpos2=0,ypos2=0,xside=0,yside=0;
  double rcolor=0,gcolor=0,bcolor=0;
  int colorcode=0;
  sprintf(filename_base,"./%s_raster_%d_to_%d",GLOBAL_STRING,(int)t1,(int)t2);
  sprintf(filename,"%s.fig",filename_base);
  if ((fp=fopen(filename,"w"))==NULL){ printf(" %% Warning, can't create %s in Lra_to_raster\n",filename); fp=stdout;} 
  fprintf(fp,"%s",FIG_PREAMBLE); fprintf(fp,"%s",FIG_PREAMBLE_COLOR_7);
  for (nr=0;nr<length;nr++){
    colorscale(0,nr,length,0,&rcolor,&gcolor,&bcolor); colorcode = crop((int)floor(512*rcolor),0,511);
    fprintf(fp,"2 1 2 1 %d 7 %d 0 -1 3.000 0 0 -1 0 0 %d\n\t",/*color*/colorcode+32,/*depth*/999,/*npoints*/2);
    xpos = 0; ypos = (nr+0.5)/(double)length; fprintf(fp," %d %d",(int)floor(maxdia*xpos),(int)maxdia-(int)floor(maxdia*ypos));
    xpos = 1; ypos = (nr+0.5)/(double)length; fprintf(fp," %d %d",(int)floor(maxdia*xpos),(int)maxdia-(int)floor(maxdia*ypos));
    fprintf(fp,"\n");}
  for (nr=0;nr<length;nr++){
    colorscale(0,nr,length,0,&rcolor,&gcolor,&bcolor); colorcode = crop((int)floor(512*rcolor),0,511);
    l = Lra[nr]->first;
    while (l!=NULL && *(double *)l->item <= t2){
      if (*(double *)l->item >= t1){
	fprintf(fp,"2 1 0 1 %d 7 %d 0 -1 0.000 0 0 -1 0 0 %d\n\t",/*color*/colorcode+32,/*depth*/nr%999+1,/*npoints*/5);
	xpos = (*(double *)l->item - t1)/(t2-t1); xside = 0.5/(t2-t1); ypos = (nr+0.5)/(double)length; yside = 0.5/(double)length;
	xpos2 = xpos+xside; ypos2 = ypos+yside;	fprintf(fp," %d %d",(int)floor(maxdia*xpos2),(int)maxdia-(int)floor(maxdia*ypos2));
	xpos2 = xpos-xside; ypos2 = ypos+yside;	fprintf(fp," %d %d",(int)floor(maxdia*xpos2),(int)maxdia-(int)floor(maxdia*ypos2));
	xpos2 = xpos-xside; ypos2 = ypos-yside;	fprintf(fp," %d %d",(int)floor(maxdia*xpos2),(int)maxdia-(int)floor(maxdia*ypos2));
	xpos2 = xpos+xside; ypos2 = ypos-yside;	fprintf(fp," %d %d",(int)floor(maxdia*xpos2),(int)maxdia-(int)floor(maxdia*ypos2));
	xpos2 = xpos+xside; ypos2 = ypos+yside;	fprintf(fp," %d %d",(int)floor(maxdia*xpos2),(int)maxdia-(int)floor(maxdia*ypos2));
	fprintf(fp,"\n");}
      l=l->child;}}
  if (fp!=stdout){ fclose(fp);}
  sprintf(command,"fig2dev -Ljpeg -q %d %s.fig %s.jpg;",/*quality*/5,filename_base,filename_base); system(command);
  sprintf(command,"fig2dev -Leps %s.fig %s.eps;",filename_base,filename_base); system(command);
  sprintf(command,"rm %s.fig;",filename_base); system(command);
}

void setglobals()
{
  int verbose=GLOBAL_verbose;
  int nr=0,length=GLOBAL_Lra_length,nl=0;
  struct llist **Lra = NULL;
  struct litem **lra = NULL;
  char filename[1024];
  FILE *fp=NULL;
  double *ra=NULL,*temp=NULL;
  if (PTREE_BOTHER){ GLOBAL_PTREE = ptreemake(GLOBAL_PTREE_NREGIONS,GLOBAL_PTREE_EVENT_WITHIN,GLOBAL_PTREE_EVENT_THRESHOLD,GLOBAL_PTREE_REGION_TYPE,GLOBAL_PTREE_NLEGS,GLOBAL_PTREE_LEGTIME);}
  GLOBAL_Lra = (struct llist **) tcalloc(length,sizeof(struct list *));
  Lra = GLOBAL_Lra;
  for (nr=0;nr<length;nr++){ Lra[nr] = llistmake();}
  sprintf(filename,"./%s.dat",GLOBAL_STRING);
  if ((fp=fopen(filename,"r"))==NULL){ printf("warning, cannot create %s in setglobals",filename); fp=stdin;}
  ra = (double *) tcalloc(GLOBAL_Yisun_length*length,sizeof(double));
  fread(ra,sizeof(double),GLOBAL_Yisun_length*length,fp);
  if (fp!=stdin){ fclose(fp);fp=NULL;}
  for (nr=0;nr<length;nr++){ for (nl=0;nl<GLOBAL_Yisun_length;nl++){ if (ra[nr+nl*length]>0){ temp = (double *) tcalloc(1,sizeof(double)); *temp = ra[nr + nl*length]; litemadd(Lra[nr],temp);}} llistsort(Lra[nr]->first,Lra[nr]->last,Lra[nr]->length,&double_compare);}
  tfree(ra);ra=NULL;
  //Lra_to_raster(Lra,length,GLOBAL_TI,GLOBAL_TF);
  GLOBAL_lra = (struct litem **) tcalloc(length,sizeof(struct litem *));
  lra = GLOBAL_lra;
  for (nr=0;nr<length;nr++){ lra[nr] = Lra[nr]->first;}
}

/* Here is the main function */

int main(int argc, char **argv) 
{
  int still_have_options=0;
  int tindex=0;
  meminit(); /* initialize memory list for use */
  readinput(); /* get all the global variables from some input */
  setdependencies(); /* make sure a few things are kosher */
  still_have_options = argc-1;
  while (still_have_options){
    switch(getopt(argc,argv,"R:N:L:")){
    case 'R':
      GLOBAL_RECORD_NUMBER=atoi(optarg); printf(" %% GLOBAL_RECORD_NUMBER set to %d\n",GLOBAL_RECORD_NUMBER);
      break;
    default: printf(" need option type: either '-RGLOBAL_RECORD_NUMBER', or ...\n"); exit(EXIT_SUCCESS); break;}
    still_have_options--;}
  setglobals(); /* initialize global variables */
  for (tindex=0;tindex<GLOBAL_TF;tindex++){ ptreeupdate(GLOBAL_PTREE,tindex,1,1); GLOBAL_time = tindex+1;}
  ptreerate(GLOBAL_PTREE);
  ptreedump_starter(GLOBAL_PTREE,GLOBAL_STRING,2,0,0,0,+1,-1,0);
  ptreetfree(GLOBAL_PTREE);
  return 1;
}
