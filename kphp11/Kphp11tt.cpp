/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11tt.cpp                                             */
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

#include "res_com.h"
#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpwindow.h"
#ifdef Debug
#include "kperr.h"
#endif
#include "kphp11y.h"
#include "kphp11w.h"
#include "kphp11p.h"
#include "kphp11d.h"
#include "kphp11tt.h"
#include "kphp11s.h"


/* ============================================== EmuD_TT_comt */

/* -------------------------------- konstruktorius */
EmuD_TT_comt::EmuD_TT_comt()
{
  tkbin=tkbout=0;
}


/* ------------------------ simboli i klav. eile, False - nera vietos */
short EmuD_TT_comt::tokbbuf(KbChar /* unsigned int */ chr)
{
short rc=False;
int ii;

  ii=(tkbin+1)%KPW_KB_BUF_SIZE;
  if(ii!=tkbout)
  {
    tkbuf[tkbin]=chr;
    tkbin=ii;
    rc=True;
  }

return(rc);
}


/* ----------------------------- ar yra simbolis klav. buferyje? */
short EmuD_TT_comt::tkbhit(void)
{
return(tkbin!=tkbout);
}


/* -------- simboli is klaviaturos buferio, Nul - buferis tuscias */
KbChar /* unsigned int */ EmuD_TT_comt::tfromkbbuf(void)
{
KbChar /* unsigned int */ rc=Nul;

  if(tkbin!=tkbout)
  {
    rc=tkbuf[tkbout];
    tkbout=(tkbout+1)%KPW_KB_BUF_SIZE;
  }

return(rc);
}


/* ============================================== EmuD_TT_t */


/* ----------------------------------------- konstruktorius */
/* porta - CSR adresas,
   intv  - trukio vekt. adr.,
   devn  - kisenes nr.,
   filn  - susieto failo vardas, NULL,
   wnd   - terminalo isvedimo langas,
   tta   - terminalo tipo klases adresas */
EmuD_TTt::EmuD_TTt
(
   AdrTyp porta,
   AdrTyp intv,
   int devn,
   unsigned char *
#ifdef Debug
      filn
#endif
      ,
   KpConsole *wnd,
   EmuD_TT_comt *tta
) : EmuD_comt()
{
HRESULT retc=S_OK;

#ifdef Debug
   if(filn!=NULL) if(filn[0]!=Nul)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
#endif

  devtyp = DEV_TT;
  portadr = porta;
  portnum = TT_MaxPort;
  intvect = intv;
  strcpy((char *)devnam,"TT");
  devno = devn;
  filnam[0] = Nul;
  wndw = wnd;
  ttadr = tta;

  reset();
}


EmuD_TTt::~EmuD_TTt()
{
HRESULT retc = S_OK;
   KP_DELETE(ttadr);
}

/* ------------------ inicializavimas (trukiu uzdraudimas) */
void EmuD_TTt::reset(void)
{
  ports[TT_in_CSR] = 0;
  ports[TT_in_DATA] = 0;
  ports[TT_out_CSR] = TT_ready;
  ports[TT_out_DATA] = (Word16Typ)intvect;
}


/* ---------------------------- vidinis simbolio isvedimas */
KbChar /* unsigned int */ EmuD_TTt::ttputchar(KbChar /* unsigned */ chr)
{
KbChar /* unsigned int */
   rc =
#if Compiler == Mingw
#  if (__MINGW32_MAJOR_VERSION * 100 + __MINGW32_MINOR_VERSION) < 315
      (unsigned int)
#  endif
#endif
         EOF;

   if(ttadr != NULL)
      rc = ttadr->tputchar(chr, wndw);

#ifdef KPCONS_OLD_STYLE
   if(wndw) wndw->DoRefresh();
#endif

return(rc);
}


/* ------------- registro (zodzio) skaitymas; True - gerai */
short EmuD_TTt::getw(AdrTyp adress, Word16Typ *valp)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         ports[TT_in_CSR] &= (~TT_ready);
         if(ttadr != NULL)
            if(ttadr->tkbhit()) ports[TT_in_CSR] |= TT_ready;

         if(TT_in_DATA == portn)
         {
            if(ttadr != NULL)
            {
               *valp = ttadr->tfromkbbuf();
               ports[TT_in_CSR] &= (~TT_ready);
               rc = True;
            }
         }
         else
         {
            *valp = ports[portn];
            rc = True;
         }


      }
      else EmuSv.n_err("TT: Trap to 10", adress, __FILE__, __LINE__);
   }

return(rc);
}


/* ------------- registro (baito) skaitymas; True - gerai */
short EmuD_TTt::getb(AdrTyp adress, ByteTyp *valp)
{
short rc = False;
int portn;
Word16Typ /* unsigned int */ ival=0;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         rc=getw(adress, &ival);
         if(rc) *valp=(ByteTyp)ival;
      }
      else
      {
         *valp=0;
         rc = True;
      }
   }

return(rc);
}


/* ------------- registro (zodzio) rasymas; True - gerai */
short EmuD_TTt::putw(AdrTyp adress, Word16Typ val)
{
short rc = False;
int portn;

  portn = (adress - portadr) / 2;
  if((portn>=0) && (portn < portnum))
  {
    if(((adress - portadr) % 2) == 0)
    {
      switch(portn)
      {
        case TT_in_CSR:
        case TT_out_CSR:
          ports[portn] = (ports[portn] & ~TT_ien) | (val & TT_ien);
          if((val & TT_ien) && (ports[portn] & TT_ready)) rc=dintrpt(portn);
          break;
        case TT_out_DATA:
          ttputchar((KbChar)val);
          rc=dputw(TT_out_CSR, TT_ready);
          break;
      }
    }
    else EmuSv.n_err("TT: Trap to 10", adress, __FILE__, __LINE__);

    rc = True;
  }

return(rc);
}


/* ------------- registro (baito) rasymas; True - gerai */
short EmuD_TTt::putb(AdrTyp adress, ByteTyp val)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
      if(((adress - portadr) % 2) == 0)
         rc=putw(adress, val);

return(rc);
}


/* ------------- registro (zodzio) rasymas is Win32 puses; True - gerai */
short EmuD_TTt::dputw(int portn, Word16Typ val)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case TT_in_CSR:
      case TT_out_CSR:
         ports[portn]=(ports[portn] & (~TT_ready)) | (val & TT_ready);
         rc=True;
         if((val & TT_ready) && (ports[portn] & TT_ien)) rc=dintrpt(portn);
         break;
      default:
         EmuSv.n_err("TT: Illegal port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("TT: Illegal port", portn, __FILE__, __LINE__);

return(rc);
}


// ------------- trukio generavimas
short EmuD_TTt::dintrpt(int portn)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case TT_in_CSR:
      case TT_out_CSR:
         if(ports[portn] & TT_ien) EmuPv.intrpt(intvect + portn*2);
         rc=True;
         break;
      default:
         EmuSv.n_err("TT: Illegal interrupt port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("TT: Illegal interrupt port", portn, __FILE__, __LINE__);

return(rc);
}
