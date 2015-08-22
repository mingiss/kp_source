/*------------------------------------------------*/
/* kpsgrp.cpp                                     */
/*  grupinis failu apdorojimas pagal failu sarasa */
/*------------------------------------------------*/

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

#if OsGr==Unix
#define BatSuff ".sh"
#else
#define BatSuff ".bat"
#endif

// =======================================
const unsigned char lpszProdName[] = "kpsgrp";
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
int main(int argc, char **argv)
{
unsigned char mcrfn[Fnsiz+1]; /* makro failo vardas */
unsigned char parmfn[Fnsiz+1]; /* parametru failo vardas */
unsigned char modfn[Fnsiz+1]; /* mode failo vardas */
unsigned char modfn0[Fnsiz+1]; /* darbinio mode failo vardas */
// unsigned char modfn1[Fnsiz+1]; /* darbinio mode failo vardas */
FILE *modfl0; /* darbinis mode failas */
unsigned char combuf[FileLinLen+1];
unsigned char *pnts;
  
  KpInit();

  mcrfn[0]=0;
  parmfn[0]=0;
  if(argc>1) strcpy(mcrfn,argv[1]);
  if(argc>2) strcpy(parmfn,argv[2]);

  printf("\nGroup macro\n\n");

  if(strlen(mcrfn)==0)
  {
    printf("Macro file name:");
    gets((char *)mcrfn);
  }
  if(strlen(parmfn)==0)
  {
#if Os==Sintran
    printf("Parameter (&<filname> for parameter list):");
#else
    printf("Parameter (@<filname> for parameter list):");
#endif
    gets((char *)parmfn);
  }

  printf("\n");

  msbcpy((unsigned char *)mcrfn,(const unsigned char *)mcrfn);
  msbcpy((unsigned char *)parmfn,(const unsigned char *)parmfn);

/*
  retc=!genunfn(modfn);
  retc|=!genunfn(modfn0);
*/
  strcpy(modfn,"kpsgrp00.tmp");
  strcpy(modfn0,"kpsgrp01.tmp");

  pnts=strchr(modfn,'.');
  if(pnts) strcpy(pnts,BatSuff);
  else strcat(modfn,BatSuff);

  pnts=strchr(modfn0,'.');
  if(pnts) strcpy(pnts,BatSuff);
  else strcat(modfn0,BatSuff);

// strcpy(modfn1,"kpsgrp02.bat");

  if((modfl0=fopen((const char *)modfn0,"w"))!=False)
  {
#if OsGr==Sintran
    fputs("@kpsgrm ",modfl0);
#else
    fputs("kpsgrm ",modfl0);
#endif
    fputs((const char *)mcrfn,modfl0);
    fputs(" ",modfl0);
    fputs((const char *)parmfn,modfl0);
    fputs(" ",modfl0);

    fputss(modfn,modfl0);

#if OsGr==Unix
    fputs("chmod 775 ",modfl0);
    fputss(modfn,modfl0);
#endif

#if OsGr==Sintran
    fputs("@mode,",modfl0);
#endif
#if (OsGr==MSDos) || (OsGr==MSWin)
    fputs("call ",modfl0);
#endif
    fputs((const char *)modfn,modfl0);
#if OsGr==Sintran
    fputs(",,,,",modfl0);
#endif
    fputss((const unsigned char *)"",modfl0);

#if OsGr==Sintran
    fputs("@del-fi,",modfl0);
#endif
#if (OsGr==MSDos) || (OsGr==MSWin)
    fputs("del ",modfl0);
#endif
#if OsGr==Unix
    fputs("rm ",modfl0);
#endif
    fputss(modfn,modfl0);

    fclose(modfl0);

#if OsGr==Unix
    strcpy(combuf,"chmod 775 ");
    strcat(combuf,modfn0);
    system((const char *)combuf);
    system((const char *)modfn0);
#endif

#if OsGr==Sintran
    strcpy(combuf,"mode,");
    strcat(combuf,modfn0);
    strcat(combuf,",,,,");
    system(combuf);
#endif

#if OsGr==MSDos || (OsGr==MSWin)
    strcpy(combuf,"call ");
    strcat(combuf,modfn0);
//  fout(modfn1, combuf);
//  strcpy(combuf,"call ");
//  strcat(combuf,modfn1);
    system((const char *)combuf);
#endif

#if OsGr==Sintran
    strcpy(combuf,"del-fi,");

#elif (OsGr==MSDos) || (OsGr==MSWin)
    strcpy(combuf,"del ");
#elif OsGr==Unix
    strcpy(combuf,"rm ");
#endif
    strcat(combuf,modfn0);
    system((const char *)combuf);

#if (OsGr==MSDos) || (OsGr==MSWin)
//  strcpy(combuf,"del ");
//  strcat(combuf,modfn1);
//  system((const char *)combuf);
#endif
  }

return(0);
}
