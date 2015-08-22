/*---------------------------------------------*/
/* FILENAME:         kpsfc.c                   */
/* DESCRIPTION:      File comparing            */
/* DESTINATION:      *                         */
/* SYSTEM_INTERFACE: Kpx                       */
/* USER_INTERFACE:   In-line                   */
/*---------------------------------------------*/


/*---------------------------------------------*/
#define KpInc
#include "kpxe.h"


/*---------------------------------------------*/
int main(argc,argv)
int argc;
char **argv;
{
unsigned char filn1[Fnsiz+1],filn2[Fnsiz+1];
File fils1,fils2;
int retc,ii,jj,kk;
unsigned char buf1[FileLinLen+1],buf2[FileLinLen+1];
long lncnt1,lncnt2;
int rerr1,rerr2,feof1,feof2;
unsigned char *pnts;
int fcid;
unsigned char cmodt[T_maxx+1];
short cmode;

  Tpflg=True;

  cinit();

  filn1[0] = Nul; filn2[0]=Nul;
  strcpy((char *)cmodt,"t");

  if(argc>1) strcpy((char *)filn1,argv[1]);
  if(argc>2) strcpy((char *)filn2,argv[2]);
  if(argc>3) strcpy((char *)cmodt,argv[3]);

  cputstr("File comparing\n\n");

  if(strlen((char *)filn1)==0) cngete("First  file:",filn1,Fnsiz);
  if(strlen((char *)filn2)==0){
    cngete("Second file:",filn2,Fnsiz);
    cngete("Binary/Text (b/t):",cmodt,40);
    }

  msbcpy(filn1,filn1);
  msbcpy(filn2,filn2);
  msbcpy(cmodt,cmodt); cstrlwr(cmodt); cmode=cmodt[0];

  cputstr("\n");

  if(cvnfopen(&fils1,filn1,(cmode=='b')?"rb":"r")){
    if(cvnfopen(&fils2,filn2,(cmode=='b')?"rb":"r")){
      fcid=rerr1=rerr2=feof1=feof2=retc=False;
      lncnt1=lncnt2=0;
      if(cmode=='b')
        do{
          ii=cfgetw(&fils1);
          rerr1|=cferror(&fils1); retc|=rerr1;
          feof1|=cfeof(&fils1); retc|=feof1;
          jj=cfgetw(&fils2);
          rerr2|=cferror(&fils2); retc|=rerr2;
          feof2|=cfeof(&fils2); retc|=feof2;
          if(!retc){
            if(ii!=jj){
              ccprintf("   %08x:    %04x  %04x",lncnt1,ii,jj);
              kk=ii     &0x7f; if(kk<Spc) kk='.'; ccprintf("    %c",kk);
              kk=(ii>>8)&0x7f; if(kk<Spc) kk='.'; ccprintf("%c",kk);
              kk=jj     &0x7f; if(kk<Spc) kk='.'; ccprintf("  %c",kk);
              kk=(jj>>8)&0x7f; if(kk<Spc) kk='.'; ccprintf("%c\n",kk);
              fcid=True;
              }
            }
          lncnt1+=2;
          } while(!retc);
      else
        do{
          cfgetss(buf1,FileLinLen,&fils1); lncnt1++;
          rerr1|=cferror(&fils1); retc|=rerr1;
          feof1|=cfeof(&fils1); retc|=feof1;
          cfgetss(buf2,FileLinLen,&fils2); lncnt2++;
          rerr2|=cferror(&fils2); retc|=rerr2;
          feof2|=cfeof(&fils2); retc|=feof2;
          if(!retc){
            if(strcmp((char *)buf1,(char *)buf2)){
              ccprintf("--------- %s\n",filn1);
              ccprintf("%3d:",lncnt1);
              pnts=buf1;
              while(*pnts){
                if((*pnts & 0x7F)<Spc) ccprintf("<%d>",*pnts);
                else cputchar(*pnts);
                pnts++;
                }
              cputstr("\n");

              ccprintf("----      %s\n",filn2);
              ccprintf("%3d:",lncnt2);
              pnts=buf2;
              while(*pnts){
                if((*pnts & 0x7F)<Spc) ccprintf("<%d>",*pnts);
                else cputchar(*pnts);
                pnts++;
                }
              cputstr("\n");

              fcid=True;
              }
            }
          } while(!retc);
      if(rerr1) cskerror(Rk_rde,"","",filn1);
      if(rerr2) cskerror(Rk_rde,"","",filn2);
      pnts=NULL;
      if((feof1==0)&&(feof2!=0)) pnts=filn1;
      if((feof1!=0)&&(feof2==0)) pnts=filn2;
      if(pnts!=NULL) ccprintf("--------- File \'%s\' is longer.\n",pnts);
      else if((!fcid)&&(!rerr1)&&(!rerr2))
             cputstr("--------- Files are identical.\n");

      cvfpurge(&fils2);
      }
    else cskerror(Rk_ntf,"","",filn2);
    cvfpurge(&fils1);
    }
  else cskerror(Rk_ntf,"","",filn1);

  ctfinit();

return(0);
}
