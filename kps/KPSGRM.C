/*-------------------------------------------------------------------------*/
/* kpsgrm.c                                                                */
/*  batch file creation from parameter list file for group file processing */
/*     uses macro file as template and supersedes all $1,                  */
/*     $2, ... to parameters from each parameter file line                 */
/*-------------------------------------------------------------------------*/

/*------------------------------*/
/* #define KpInc */   /* Kp* projects */
#define TvInc         /* Tev C++ projects */

#ifdef TvInc
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "kpstdlib.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kptt.h"
#include "kpctype.h"
#endif

#ifdef KpInc
#include "kpxe.h"
#include <string.h>
#endif


/*------------------------------*/
int werr,feof3,rerr3;

/*------------------------------*/
#if Lang>=AnsiC
void filmcr(unsigned char *parms, char *mcrfn, FILE *modfl)
#else
void filmcr(parms,mcrfn,modfl)
unsigned char *parms; /* parameter string */
char *mcrfn; /* macro file name */
FILE *modfl; /* batch file */
#endif
{
  FILE *fils2;
  int retc,rerr2,feof2;
  unsigned char parbuf[FileLinLen+1],buf1[FileLinLen+1],buf2[FileLinLen+1];
  unsigned char *pnts,*pntd,*pntf;
  int kk,jj;
  unsigned char cc;

  msbcpy(parbuf,parms);
  if(((*parms)!='*')&&(strlen((char *)parbuf)!=0))
  {
    if((fils2=fopen(mcrfn,"r"))!=False)
    {
      rerr2=feof2=retc=False;
      do
      {
        fgetss(buf1,FileLinLen,fils2);
        rerr2|=ferror(fils2); retc|=rerr2; rerr3|=rerr2;
        feof2|=feof(fils2); retc|=feof2;
        if(!retc)
        {
          pnts=buf1; pntd=buf2;
          while(*pnts)
          {
            if((*pnts=='$') /* || (*pnts=='\\') */)
            {
              cc = *pnts;
              pnts++;
              if(cisdigit(*pnts))
              {
                kk=(*pnts++)-'0';
                pntf=parms;
                while(((*pntf)==Spc)&&(*pntf)) pntf++;
                for(jj=1;jj<kk;jj++)
                {
                  while(((*pntf)!=Spc)&&(*pntf)) pntf++;
                  while(((*pntf)==Spc)&&(*pntf)) pntf++;
                }
                while(((*pntf)!=Spc)&&(*pntf)) (*pntd++)=(*pntf++);
              }
              else (*pntd++)=cc;
            }
            else (*pntd++)=(*pnts++);
          }
          *pntd=0;
          fputss((char *)buf2,modfl);
          werr|=ferror(modfl); retc|=werr;
          feof3|=feof(modfl); retc|=feof3;
        }
      } while(!retc);
      if(rerr2) csperror(Rk_rde,"","",mcrfn);
      fclose(fils2);
    }
    else
    {
      csperror(Rk_ntf,"","",mcrfn);
      rerr3|=True;
    }
  }
}

/*------------------------------*/
int main(int argc, char **argv)
{
  char mcrfn[Fnsiz+1]; /* macro file name */
  char parmfn[Fnsiz+1]; /* parameter file name */
  char modfn[Fnsiz+1]; /* batch file name */
  unsigned char parms[FileLinLen+1]; /* parameter string */
  FILE *modfl; /* batch file */
  FILE *fils1;
  int retc,rerr1,feof1;

  mcrfn[0]=0;
  parmfn[0]=0;
  modfn[0]=0;
  if(argc>1) strcpy(mcrfn,argv[1]);
  if(argc>2) strcpy(parmfn,argv[2]);
  if(argc>3) strcpy(modfn,argv[3]);

  printf("\nGroup macro file creation\n\n");

  if(strlen(mcrfn)==0)
  {
    printf("Macro file name:");
    gets(mcrfn);
  }
  if(strlen(parmfn)==0)
  {
#if Os==Sintran
    printf("Parameter (&<filname> for parameter list):");
#else
    printf("Parameter (@<filname> for parameter list):");
#endif
    gets(parmfn);
  }
  if(strlen(modfn)==0)
  {
/*
    printf("Batch file name:");
    gets(modfn);
*/
    strcpy(modfn,"kpsgrm.tmp");
  }

  msbcpy((unsigned char *)mcrfn,(unsigned char *)mcrfn);
  msbcpy((unsigned char *)parmfn,(unsigned char *)parmfn);
  msbcpy((unsigned char *)modfn,(unsigned char *)modfn);

  printf("\n");

  werr=feof3=rerr3=False;
  rerr1=feof1=retc=False;

  if((parmfn[0]!='@') && (parmfn[0]!='&'))
  {
    if((modfl=fopen(modfn,"w"))!=False)
    {
      filmcr((unsigned char *)parmfn,mcrfn,modfl);
      werr|=(fclose(modfl)!=0);
    }
    else feof3=True;
  }
  else
  {
    if((fils1=fopen(parmfn+1,"r"))!=False)
    {
      if((modfl=fopen(modfn,"w"))!=False)
      {
        do
        {
          fgetss((char *)parms,FileLinLen,fils1);
          rerr1|=ferror(fils1); retc|=rerr1;
          feof1|=feof(fils1); retc|=feof1;
          if(!retc) filmcr(parms,mcrfn,modfl);
          retc|=werr; retc|=feof3; retc|=rerr3;
        } while(!retc);
        werr|=(fclose(modfl)!=0);
      }
      else feof3=True;
      if(rerr1) cskerror(Rk_rde,"","",parmfn+1);
      fclose(fils1);
    }
    else
    {
      cskerror(Rk_ntf,"","",parmfn+1);
      rerr1=True;
    }
  }

  if(werr) cskerror(Rk_wre,"","",modfn);
  if(feof3) cskerror(Rk_drf,"","",modfn);

return(RET_CODE(S_OK));
}
