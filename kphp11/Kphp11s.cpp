/*---------------------------------------------------------------------------------*/
/* FILENAME:         Kphp11s.cpp, former Kphp11w.cpp                               */
/* DESCRIPTION:      pagrindinis valdymo modulis                                   */
/* LANGUAGE:         C++                                                           */
/* DESTINATION:      MSWindows                                                     */
/* SYSTEM_INTERFACE: MSWindows                                                     */
/* USER_INTERFACE:   Graph                                                         */
/* ARCHIVE_VERSION:  LATEST                                                        */
/* ARCHIVE_COMMENT:                                                                */
/*---------------------------------------------------------------------------------*/

/*---------------------------------------------------- gen */
// #define Lang 7 /* Cpp */
// #define KpInc

#include "stdafx.h"

#include "envir.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kphp11y.h"
#include "kphp11p.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11s.h"


/*--------------------------------------------------- EmuS */
/* viso emuliatoriaus busena */

EmuSt EmuSv;

EmuSt::EmuSt()
{
  trfl = intrfl = errfl = errfl_gl = prfl = False;

//status = Monitor;
  EmuPv.putrw(PC_IND, 0);
  status = Run;

}


/*-------------------------- vykdomos instrukcijos isvedimas */
/* True - gerai */
short EmuSt::pr3(void)
{
unsigned char buf[KPW_CONSOLE_CTRL_NUMOFCOLUMNS+1];
RegTyp ii=0;
Word16Typ jj1, jj2, jj3;
short prsav;
short rc = True;

  jj1=jj2=jj3=0;

  prfl++;
  prsav = prfl;

  rc &= EmuPv.getrw(PC_IND, &ii);
  if(rc) rc &= EmuYv.getw(ii, &jj1);
  if(rc) rc &= EmuYv.getw(ii+2, &jj2);
  if(rc) rc &= EmuYv.getw(ii+4, &jj3);
  if(prfl == prsav)
  {
    sprintf((char *)buf,"%06o/%06o %06o %06o\n", ii, jj1, jj2, jj3);
    EmuWv.wputstr(buf);
    prfl = 0;
  }

return(rc);
}


/*--------------------------------------------------- klaida */
short EmuSt::s_err(const char *errstr, const unsigned char *addstr, const char *lpszSourceFile, int iSourceLine)
{
unsigned char buf[KPW_CONSOLE_CTRL_NUMOFCOLUMNS+1];

   if(!errfl)
   {
      errfl = True;

      EmuWv.wputchar(Cr);
      EmuWv.wputchar(Lf);

      sprintf((char *)buf,"%s%s",errstr,addstr);

      if(strlen(buf) != 0)
      {
         EmuWv.wputstr(buf);
         EmuWv.wputchar(Cr);
         EmuWv.wputchar(Lf);
      }

      if(!errfl_gl)
         /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, buf, False, lpszSourceFile, iSourceLine, 0L);
      errfl_gl = True;


      if(Monitor != status)
      {
         status = Monitor;
         pr3();
         EmuMv.prompt();
      }

      errfl = False;
   }

return(False);
}


short EmuSt::n_err(const char *errstr, AdrTyp adr, const char *lpszSourceFile, int iSourceLine)
{
char buf[KPW_CONSOLE_CTRL_NUMOFCOLUMNS+1];

  sprintf(buf, "%s: %06o", errstr, adr & ValMaskW);

return(s_err(buf,(const unsigned char *)"", lpszSourceFile, iSourceLine));
}
