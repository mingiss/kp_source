/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp1152.cpp                                             */
/* DESCRIPTION:      Kphp11:  Terminalas                                      */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

/* ---------------------------------------------------- gen */
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
#include "tvxml.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp1152.h"
#include "kphp11s.h"


/* ----------------------------------------- konstruktorius */
EmuD_TT_vt52t::EmuD_TT_vt52t()
  : EmuD_TT_comt()
{
  termtyp = TERM_VT52;
  status  = VT52_CHAR;
}


/* ------------ simb. isvedimas, wnd - i kuri langa isvesti */
KbChar /* unsigned int */ EmuD_TT_vt52t::tputchar(KbChar /* unsigned int */ chr, KpConsole *wnd)
{
KbChar /* unsigned int */
   rc =
#if Compiler==Mingw
#  if (__MINGW32_MAJOR_VERSION * 100 + __MINGW32_MINOR_VERSION) < 315
      (unsigned int)
#  endif
#endif
         EOF;
unsigned char buf[2];
int xsav, ysav, ii;

  switch(status)
  {
    case VT52_CHAR:
      switch(chr)
      {
        case Esc:
          status = VT52_ESC;
          rc = chr;
          break;

        case Cr:
          if(wnd != NULL)
          {
            wnd->wloc(0, wnd->m_iCurY);
            rc = chr;
          }
          break;

        default:
          if(wnd != NULL) if(FAILED(wnd->wputchar(chr)))
                rc =
#if Compiler==Mingw
#  if (__MINGW32_MAJOR_VERSION * 100 + __MINGW32_MINOR_VERSION) < 315
                        (unsigned int)
#  endif
#endif
                                EOF;

// if((chr<Spc) && (chr!=Lf) && (chr!=Ff) && (chr!=Bs)) { char str_buf[100]; sprintf(str_buf, "%d", chr); KP_TRACE(str_buf); }

          break;
      }
      break;

    case VT52_ESC:
      switch(chr)
      {
        case 'Y':               /* zymio perkelimas */
          status = VT52_LOC1;
          rc = chr;
          break;

        case 'K':               /* eilutes galo isvalymas */
          wnd->wclreol();
          status = VT52_CHAR;
          rc = chr;
          break;

        case 'J':               /* isvalyti ekrana i desine ir zemyn */
          xsav=wnd->m_iCurX; ysav=wnd->m_iCurY;
          wnd->wclreol();
          for(ii = wnd->m_iCurY+1; ii < wnd->m_iNumOfRows; ii++)
          {
            wnd->wloc(0,ii);
            wnd->wclreol();
          }
          wnd->wloc(xsav,ysav);

          status = VT52_CHAR;
          rc = chr;
          break;

        default:
          buf[0] = (unsigned char)chr;
          buf[1] = Nul;
          EmuSv.s_err("VT52: Illegal Command: ESC ", buf, __FILE__, __LINE__);
          status = VT52_CHAR;
          break;
      }
      break;

    case VT52_LOC1:
      valsav = chr;
      status = VT52_LOC2;
      rc = chr;
      break;

    case VT52_LOC2:
      if(wnd != NULL)
      {
        wnd->wloc((chr & 0xFF) - Spc, (valsav & 0xFF) - Spc);
        rc = chr;
      }
      status = VT52_CHAR;
      break;
  }

return(rc);
}


/* ------------------------ simboli i klav. eile, False - nera vietos */
short EmuD_TT_vt52t::ttokbbuf(KbChar /* unsigned int */ chr)
{
return(tokbbuf(chr));
}
