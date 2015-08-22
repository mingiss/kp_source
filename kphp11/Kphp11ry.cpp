// ----------------------------------
// kphp11ry.cpp
// remote memory access device implementation
//

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
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#ifdef Debug
#include "kperr.h"
#endif
#include "kphp11y.h"
#include "kphp11w.h"
#include "kphp11p.h"
#include "kphp11d.h"
#include "kphp11ry.h"
#include "kphp11s.h"


/* ----------------------------------------- konstruktorius */
/* porta - CSR adresas,
   intv  - trukio vekt. adr.,
   devn  - kisenes nr., 0
   filn  - susieto failo vardas, NULL,
   wnd   - terminalo isvedimo langas, NULL
   tta   - terminalo tipo klases adresas, NULL */
EmuD_RYt::EmuD_RYt
(
   AdrTyp porta,
   AdrTyp intv,
   int devn,
   unsigned char *
#ifdef Debug
      filn
#endif
      ,
   KpConsole *
#ifdef Debug
      wnd
#endif
      ,
   EmuD_TT_comt *
#ifdef Debug
      tta
#endif
) : EmuD_comt()
{
HRESULT retc=S_OK;

#ifdef Debug
   KP_ASSERT(wnd == NULL, E_INVALIDARG, null, True);
   KP_ASSERT(tta == NULL, E_INVALIDARG, null, True);

   if((filn!=NULL) && SUCCEEDED(retc))
      if(filn[0]!=Nul)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
#endif

   devtyp = DEV_RY;
   portadr = porta;
   portnum = RY_MaxPort;
   intvect = intv;
   strcpy((char *)devnam,"RY");
   devno = devn;

   filnam[0] = Nul; // strncpy((char *)filnam, (char *)filn, Fnsiz);
   wndw = NULL; // wnd;
   ttadr = NULL; // tta;

   reset();
}


/* ------------------ inicializavimas (trukiu uzdraudimas) */
void EmuD_RYt::reset(void)
{
  ports[RY_CSR] = RY_ready;
  ports[RY_ADDR1] = 0;
  ports[RY_ADDR2] = 0;
  ports[RY_DATA1] = 0;
  ports[RY_DATA2] = 0;
}


/* ------------- registro (zodzio) skaitymas; True - gerai */
short EmuD_RYt::getw(AdrTyp adress, Word16Typ *valp)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         *valp=ports[portn];
         rc = True;
      }
      else EmuSv.n_err("RY: Trap to 10", adress, __FILE__, __LINE__);
   }

return(rc);
}


/* ------------- registro (baito) skaitymas; True - gerai */
short EmuD_RYt::getb(AdrTyp adress, ByteTyp *valp)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
         *valp = (ByteTyp)(ports[portn] & ValMaskB);
      else
         *valp = (ByteTyp)((ports[portn] >> 8) & ValMaskB);

      rc = True;
   }

return(rc);
}


/* ------------- registro (zodzio) rasymas; True - gerai */
short EmuD_RYt::putw(AdrTyp adress, Word16Typ val)
{
short rc = False;
int portn;
unsigned char *pnts;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         switch(portn)
         {
         case RY_CSR:
            ports[portn]=(ports[portn] & (~(RY_ien | RY_read | RY_write))) | (val & (RY_ien /* | RY_read | RY_write */));
            if(val & (RY_read | RY_write))
            {
               rc=dputw(portn, ports[portn] & (~RY_ready));

               pnts=(unsigned char *)((ports[RY_ADDR1] & 0xFFFF) | ((ports[RY_ADDR2]<<16) & 0xFFFF0000));

               if(((val & (RY_read | RY_write)) == (RY_read | RY_write)) && rc)
               {
                  EmuSv.n_err("RY: illegal command", adress, __FILE__, __LINE__);
                  rc=False;
               }

               if((val & RY_read) && rc)
               {
#ifdef Debug_RYt_putw
// testuojam Ech11 lûþimà klaida_20111209_Kestutis_Labanauskas
PutLogMessage_("RYt::putw() %x %x %x", pnts, ports[RY_ADDR2], ports[RY_ADDR1]);
// KpSleep(1);               
#endif
                  rc = dputw(RY_DATA1, ((pnts[0] & 0xFF) | ((pnts[1]<<8) & 0xFF00)));
#ifdef Debug_RYt_putw
PutLogMessage_("RYt::putw() ok");
#endif
                  if(rc) rc = dputw(RY_DATA2, ((pnts[2] & 0xFF) | ((pnts[3]<<8) & 0xFF00)));
#ifdef Debug_RYt_putw
PutLogMessage_("RYt::putw() ok ok");
#endif
               }

               if((val & RY_write) && rc)
               {
                  *(pnts++)=(unsigned char)(ports[RY_DATA1] & 0xFF);
                  *(pnts++)=(unsigned char)((ports[RY_DATA1]>>8) & 0xFF);
                  *(pnts++)=(unsigned char)(ports[RY_DATA2] & 0xFF);
                  *(pnts++)=(unsigned char)((ports[RY_DATA2]>>8) & 0xFF);
               }

               if(rc) rc=dputw(portn, ports[portn] | RY_ready);
            }
            break;
         case RY_ADDR1:
         case RY_ADDR2:
         case RY_DATA1:
         case RY_DATA2:
            ports[portn]=val;
            break;
         }
         rc = True;
      }
      else EmuSv.n_err("RY: Trap to 10", adress, __FILE__, __LINE__);
   }

return(rc);
}


/* ------------- registro (baito) rasymas; True - gerai */
short EmuD_RYt::putb(AdrTyp adress, ByteTyp val)
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
         case RY_CSR:
            rc=putw(adress, val);
            break;
         case RY_ADDR1:
         case RY_ADDR2:
         case RY_DATA1:
         case RY_DATA2:
            ports[portn]=(ports[portn] & (~ValMaskB)) | (val & ValMaskB);
            break;
         }
      }
      else
      {
         switch(portn)
         {
         case RY_ADDR1:
         case RY_ADDR2:
         case RY_DATA1:
         case RY_DATA2:
            ports[portn]=(ports[portn] & ValMaskB) | ((val<<8) & (~ValMaskB));
            break;
         }
      }

      rc = True;
   }

return(rc);
}


/* ------------- registro (zodzio) rasymas is Win32 puses; True - gerai */
short EmuD_RYt::dputw(int portn, Word16Typ val)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case RY_CSR:
         ports[portn]=(ports[portn] & (~RY_ready)) | (val & RY_ready);
         rc=True;
         if((val & RY_ready) && (ports[portn] & RY_ien)) rc=dintrpt(portn);
         break;
      case RY_DATA1:
      case RY_DATA2:
         ports[portn]=val;
         rc=True;
         break;
      default:
         EmuSv.n_err("RY: Illegal port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("RY: Illegal port", portn, __FILE__, __LINE__);

return(rc);
}


// ------------- trukio generavimas
short EmuD_RYt::dintrpt(int portn)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case RY_CSR:
         if(ports[portn] & RY_ien) EmuPv.intrpt(intvect + portn*2);
         rc=True;
         break;
      default:
         EmuSv.n_err("RY: Illegal interrupt port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("RY: Illegal interrupt port", portn, __FILE__, __LINE__);

return(rc);
}
