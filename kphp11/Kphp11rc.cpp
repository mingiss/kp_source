// ----------------------------------
// kphp11rc.cpp
// remote control device implementation
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
#include "kperr.h"
#include "kphp11y.h"
#include "kphp11w.h"
#include "kphp11p.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11s.h"
#include "kphp11i.h"
#include "kphp11t.h"

/* ----------------------------------------- */
KpRcPars RcParBuf; // fiktyvus RC parametru buferis poslinkiu skaiciavimui

/* ----------------------------------------- konstruktorius */
/* porta - CSR adresas,
   intv  - trukio vekt. adr.,
   devn  - kisenes nr., 0
   filn  - susieto failo vardas, NULL,
   wnd   - terminalo isvedimo langas, NULL
   tta   - terminalo tipo klases adresas, NULL */
EmuD_RCt::EmuD_RCt(
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

   devtyp = DEV_RC;
   portadr = porta;
   portnum = RC_MaxPort;
   intvect = intv;
   strcpy((char *)devnam,"RC");
   devno = devn;

   filnam[0] = Nul; // strncpy((char *)filnam, (char *)filn, Fnsiz);
   wndw = NULL; // wnd;
   ttadr = NULL; // tta;

   reset();
}


/* ------------------ inicializavimas (trukiu uzdraudimas) */
void EmuD_RCt::reset(void)
{
  ports[RC_CSR] = 0;
  ports[RC_ADDR1] = 0;
  ports[RC_ADDR2] = 0;
}


/* ------------- registro (zodzio) skaitymas; True - gerai */
short EmuD_RCt::getw(AdrTyp adress, Word16Typ *valp)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         *valp=ports[portn];
         if(portn==RC_CSR) ports[portn]&=(~RC_ready);

         rc = True;
      }
      else EmuSv.n_err("RC: Trap to 10", adress, __FILE__, __LINE__);
   }

return(rc);
}


/* ------------- registro (baito) skaitymas; True - gerai */
short EmuD_RCt::getb(AdrTyp adress, ByteTyp *valp)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         *valp = (ByteTyp)(ports[portn] & ValMaskB);
         if(portn==RC_CSR) ports[portn]&=(~RC_ready);
      }
      else
         *valp = (ByteTyp)((ports[portn] >> 8) & ValMaskB);

      rc = True;
   }

return(rc);
}


/* ------------- registro (zodzio) rasymas; True - gerai */
short EmuD_RCt::putw(AdrTyp adress, Word16Typ val)
{
short rc = False;
int portn;
HRESULT retc0=S_OK;
KpRcPars *par_ptr=NULL;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         rc = True;

         if(portn==RC_CSR)
         {
// ----------------------------
// remote callback command
            if((val & RC_exec)!=0)
            {
               retc0 = S_OK;

// istrinam RC_ready bita
               ports[portn]&=(~RC_ready);

               par_ptr=(KpRcPars *)(ports[RC_ADDR1]+(ports[RC_ADDR2]<<16));
               if(par_ptr==NULL)
               {
                  retc0 = E_INVALIDARG;
                  KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
#ifdef Debug
//                if(SUCCEEDED(retc)) retc=retc0;
                  rc=False;
                  EmuSv.s_err("RC: invalid args", (const unsigned char *)"", __FILE__, __LINE__);
#endif
               }
               if(SUCCEEDED(retc0))
                  if(
                     (par_ptr->enc.iCallBackIx<0) ||
                     (par_ptr->enc.iCallBackIx>=KpHp11NumOfExtFun) // ||
//                   (par_ptr->enc.pCallBackPars==NULL)
                    )
                  {
                     retc0 = E_INVALIDARG;
                     KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
#ifdef Debug
//                   if(SUCCEEDED(retc)) retc=retc0;
                     rc=False;
                     EmuSv.s_err("RC: invalid args", (const unsigned char *)"", __FILE__, __LINE__);
#endif
                  }

               if(SUCCEEDED(retc0))
               {
// PutLogMessage_("EmuD_RCt::putw() %d %x", par_ptr->enc.iCallBackIx, KpHp11ExtFunTab[par_ptr->enc.iCallBackIx]);
                  retc0=KpHp11ExtFunTab[par_ptr->enc.iCallBackIx](par_ptr->enc.pCallBackPars);
                  par_ptr->m_iRetc=retc0;
               }

// istatom RC_ready bita,
// siaip turetu generuoti truki, bet tiek to - dabar gautusi rekursija
               ports[portn]|=RC_ready;
            }

// ----------------------------
// numetamas anksciau buves RC_busy bitas
            if(
               ((ports[portn] & RC_busy)!=0) &&
               ((val & RC_busy)==0)
              )
            {
               retc0 = S_OK;
               if(EmuTv.m_lMainThreadId == 0L)
               {
// XXXX: Kažkodėl kartais čia grįžta dar kartą, kai po WM_KP_REMOTE_CALL_DONE
//    padvigubinam sinchronizaciją – eilutėje ZZZZ išvalom EmuTv.m_lMainThreadId (žr. žemiau)
                  retc0 = KP_E_SYSTEM_ERROR;
                  KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
#ifdef Debug
//                if(SUCCEEDED(retc)) retc=retc0;
                  rc=False;
                  EmuSv.n_err("RC: no connection to host", adress, __FILE__, __LINE__);
#endif
               }
               if((EmuTv.m_lMainThreadId != 0L) || (EmuTv.m_lPrevThreadId != 0L)) // if(SUCCEEDED(retc0))
               {
// !!! is kur nors grazinti klaidos koda
// xGecko praryja pranešimus – sinchronizuojam per m_bRCdone
#if FALSE
long thread_id = EmuTv.m_lMainThreadId;
                  if(thread_id == 0L) thread_id = EmuTv.m_lPrevThreadId;
                  if(!PostThreadMessage(thread_id /* EmuTv.m_lMainThreadId */, WM_KP_REMOTE_CALL_DONE, 0, (LPARAM)S_OK /* retc !!! */))
                  {
                     retc0 = KP_E_SYSTEM_ERROR;
                     KpErrorProc.OutputErrorMessage(retc0, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#ifdef Debug
//                   if(SUCCEEDED(retc)) retc=retc0;
                     rc=False;
                     EmuSv.n_err("RC: no connection to host", adress, __FILE__, __LINE__);
#endif
                  }
#else
               EmuTv.m_bRCdone = True;
#endif

// XGecko kartais praryja WM_KP_REMOTE_CALL_DONE pranešimą – čia dviguba sinchronizacija per taimerį KPHP11_RC_TIMEOUT
// ZZZZZ: neišeina – kartais kažkas susidubliuoja – meta klaidą dėl tuščio EmuTv.m_lMainThreadId eilutėje XXXX (žr. aukščiau)
//       ir po to nebesiunčia WM_KP_REMOTE_CALL_DONE
//                EmuTv.m_lMainThreadId = 0L;

// if(SUCCEEDED(retc0)) KP_TRACE("kphp11rc: WM_KP_REMOTE_CALL_DONE sent");
// if(SUCCEEDED(retc0)) PutLogMessage_("EmuD_RCt::putw(): WM_KP_REMOTE_CALL_DONE sent to %d", ii);
               }

// numetam užimtumą vis dėlto čia, buvau iškėlęs į EmuTt::WaitForRemoteCallCompletion()
               if(EmuTv.m_lMainThreadId != 0L) EmuTv.m_lPrevThreadId = EmuTv.m_lMainThreadId;
               EmuTv.m_lMainThreadId = 0L;

            }

// ----------------------------
// irasom/istrinam tik RC_ien bita
            ports[portn]=((ports[portn] & (~RC_ien)) | (val & RC_ien));
// RC_busy bitas is HP11 puses gali buti tik istrinamas
            if(!(val & RC_busy))
               ports[portn]=(ports[portn] & (~RC_busy)) | (val & RC_busy);
         }
      }
      else EmuSv.n_err("RC: Trap to 10", adress, __FILE__, __LINE__);
   }

return(rc);
}


/* ------------- registro (baito) rasymas; True - gerai */
short EmuD_RCt::putb(AdrTyp adress, ByteTyp val)
{
short rc = False;
int portn;

   portn = (adress - portadr) / 2;
   if((portn>=0) && (portn < portnum))
   {
      if(((adress - portadr) % 2) == 0)
      {
         if(portn==RC_CSR) rc=putw(adress, val);
      }
      rc = True;
   }

return(rc);
}


/* ------------- registro (zodzio) rasymas is Win32 puses; True - gerai */
short EmuD_RCt::dputw(int portn, Word16Typ val)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case RC_CSR:
// gali buti irasomas tik RC_ready bitas
         ports[portn]=(ports[portn] & (~RC_ready)) | (val & RC_ready);
         rc=True;
         if(val & RC_ready)
         {
            ports[portn]|=RC_busy;
// KP_TRACE("kphp11rc: RC interrupt called");
            if(ports[portn] & RC_ien) rc=dintrpt(portn);
         }
// istrinam RC_ready bita
         ports[portn]=(ports[portn] & (~RC_ready));
         break;
      case RC_ADDR1:
      case RC_ADDR2:
         ports[portn]=val;
         rc=True;
         break;
      default:
         EmuSv.n_err("RC: Illegal port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("RC: Illegal port", portn, __FILE__, __LINE__);

return(rc);
}


// ------------- trukio generavimas
short EmuD_RCt::dintrpt(int portn)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case RC_CSR:
         if(ports[portn] & RC_ien) EmuPv.intrpt(intvect + portn*2);
         rc=True;
         break;
      default:
         EmuSv.n_err("RC: Illegal interrupt port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("RC: Illegal interrupt port", portn, __FILE__, __LINE__);

return(rc);
}
