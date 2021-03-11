/*-------------------------------------------------------------------------*/
/* kpsgrm.cpp                                                                */
/*  batch file creation from parameter list file for group file processing */
/*     uses macro file as template and supersedes all $1,                  */
/*     $2, ... to parameters from each parameter file line                 */
/*-------------------------------------------------------------------------*/

/*------------------------------*/
// #include "envdef.h"
#include "envir.h"
// #include "envsupp.h"

#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kpstap.h"


// =======================================
const unsigned char lpszProdName[] = "kpsgrm";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 43);
bool bServiceFl = False;

int KpHp11NumOfExtFun = 0;
KpHp11ExtFun KpHp11ExtFunTab[1] =
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};


// =======================================
HRESULT KpErrorProcClass::FormatErrorMessage
(
	const HRESULT lhRetc,
	unsigned char *lpszMsg
)
{
return(FormatErrorMessageMain(lhRetc, lpszMsg));
}


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*------------------------------*/
int werr,feof3,rerr3;

/*------------------------------*/
#if Lang>=AnsiC
void filmcr(const unsigned char *parms, const unsigned char *mcrfn, FILE *modfl)
#else
void filmcr(parms,mcrfn,modfl)
const unsigned char *parms; /* parameter string */
const unsigned char *mcrfn; /* macro file name */
FILE *modfl; /* batch file */
#endif
{
  FILE *fils2;
  int retc,rerr2,feof2;
  unsigned char parbuf[FileLinLen+1],buf1[FileLinLen+1],buf2[FileLinLen+1];
  const unsigned char *pnts,*pntf;
  unsigned char *pntd;
  int kk,jj;
  unsigned char cc;

  msbcpy(parbuf, parms);
  if(((*parms)!='*')&&(strlen((const char *)parbuf)!=0))
  {
    if((fils2=fopen((const char *)mcrfn,"r"))!=False)
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
                while((/* ((*pntf)==Spc) || */ ((*pntf)==Tab)) && (*pntf)) pntf++;
                for(jj=1;jj<kk;jj++)
                {
                  while(/* ((*pntf)!=Spc) && */ ((*pntf)!=Tab) && (*pntf)) pntf++;
                  while((/* ((*pntf)==Spc) || */ ((*pntf)==Tab)) && (*pntf)) pntf++;
                }
                while(/* ((*pntf)!=Spc) && */ ((*pntf)!=Tab) && (*pntf)) (*pntd++)=(*pntf++);
              }
              else (*pntd++)=(*pnts++);
            }
            else (*pntd++)=(*pnts++);
          }
          *pntd=0;
          fputss(buf2,modfl);
          werr|=ferror(modfl); retc|=werr;
          feof3|=feof(modfl); retc|=feof3;
        }
      } while(!retc);
      if(rerr2) KP_ERROR(KP_E_FERROR, null); // csperror(Rk_rde,(const unsigned char *)"",(const unsigned char *)"",mcrfn);
      fclose(fils2);
    }
    else
    {
      KP_ERROR(KP_E_FILE_NOT_FOUND, null); // csperror(Rk_ntf,mcrfn,(const unsigned char *)"",mcrfn);
      rerr3|=True;
    }
  }
}

/*------------------------------*/
int main(int argc, char **argv)
{
  unsigned char mcrfn[Fnsiz+1]; /* macro file name */
  unsigned char parmfn[Fnsiz+1]; /* parameter file name */
  unsigned char modfn[Fnsiz+1]; /* batch file name */
  unsigned char parms[FileLinLen+1]; /* parameter string */
  FILE *modfl; /* batch file */
  FILE *fils1;
  int retc,rerr1,feof1;

  mcrfn[0]=0;
  parmfn[0]=0;
  modfn[0]=0;
  if(argc>1) fstrcpy(mcrfn,argv[1]);
  if(argc>2) fstrcpy(parmfn,argv[2]);
  if(argc>3) fstrcpy(modfn,argv[3]);

  printf("\nGroup macro file creation\n\n");

  if(fstrlen(mcrfn)==0)
  {
    printf("Macro file name:");
    gets((char *)mcrfn);
  }
  if(fstrlen(parmfn)==0)
  {
#if Os==Sintran
    printf("Parameter (&<filname> for parameter list):");
#else
    printf("Parameter (@<filname> for parameter list):");
#endif
    gets((char *)parmfn);
  }
  if(fstrlen(modfn)==0)
  {
/*
    printf("Batch file name:");
    gets(modfn);
*/
    fstrcpy(modfn,"kpsgrm.tmp");
  }

  msbcpy((unsigned char *)mcrfn,(unsigned char *)mcrfn);
  msbcpy((unsigned char *)parmfn,(unsigned char *)parmfn);
  msbcpy((unsigned char *)modfn,(unsigned char *)modfn);

  printf("\n");

  werr=feof3=rerr3=False;
  rerr1=feof1=retc=False;

  if((parmfn[0]!='@') && (parmfn[0]!='&'))
  {
    if((modfl=fopen((const char *)modfn,"w"))!=False)
    {
      filmcr(parmfn,mcrfn,modfl);
      werr|=(fclose(modfl)!=0);
    }
    else feof3=True;
  }
  else
  {
    if((fils1=fopen((const char *)parmfn+1,"r"))!=False)
    {
      if((modfl=fopen((const char *)modfn,"w"))!=False)
      {
        do
        {
          fgetss(parms,FileLinLen,fils1);
          rerr1|=ferror(fils1); retc|=rerr1;
          feof1|=feof(fils1); retc|=feof1;
          if(!retc)
              if (parms[0] != '#') // !!!! TODO: perkompiliuot su komentaru
		          filmcr(parms, mcrfn, modfl);
          retc|=werr; retc|=feof3; retc|=rerr3;
        } while(!retc);
        werr|=(fclose(modfl)!=0);
      }
      else feof3=True;
      if(rerr1) KP_ERROR(KP_E_FERROR, null); // cskerror(Rk_rde,(const unsigned char *)"",(const unsigned char *)"",parmfn+1);
      fclose(fils1);
    }
    else
    {
      KP_ERROR(KP_E_FILE_NOT_FOUND, null); // cskerror(Rk_ntf,(const unsigned char *)"",(const unsigned char *)"",parmfn+1);
      rerr1=True;
    }
  }

  if(werr) KP_ERROR(KP_E_FERROR, null); // cskerror(Rk_wre,(const unsigned char *)"",(const unsigned char *)"",modfn);
  if(feof3) KP_ERROR(KP_E_FERROR, null); // cskerror(Rk_drf,(const unsigned char *)"",(const unsigned char *)"",modfn);

return(RET_CODE_MAIN(S_OK));
}
