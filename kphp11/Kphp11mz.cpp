/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11mz.cpp                                             */
/* DESCRIPTION:      Kphp11:  Diskas MZ ?                                     */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:  tik pradetas, neveikia ?                                 */
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
#include "kphp11mz.h"
#include "kphp11s.h"


/* ----------------------------------------- konstruktorius */
/* porta - CSR adresas,
   intv  - trukio vekt. adr.,
   devn  - kisenes nr.,
   filn  - susieto failo vardas,
   wnd   - terminalo isvedimo langas, NULL,
   tta   - terminalo tipo klases adresas, NULL */
EmuD_MZt::EmuD_MZt(AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd, EmuD_TT_comt *tta)
: EmuD_comt()
{
HRESULT retc=S_OK;

   KP_ASSERT(wnd == NULL, E_INVALIDARG, null, True);
   KP_ASSERT(tta == NULL, E_INVALIDARG, null, True);

#ifdef Debug
   if((wnd!=NULL) || (tta!=NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
#endif

   devtyp = DEV_MZ;
   portadr = porta;
   portnum = MZ_MaxPort;
   intvect = intv;
   strcpy((char *)devnam,"MZ");
   devno = devn;
   if(filn != NULL) strncpy((char *)filnam,(char *)filn,Fnsiz);
   else filnam[0] = Nul;

   reset();
}


/* ------------------ inicializavimas (trukiu uzdraudimas) */
void EmuD_MZt::reset(void)
{
int ii;

  for(ii=0; ii<MZ_MaxPort; ii++) ports[ii] = 0;
}


/* ------------- registro (zodzio) skaitymas; True - gerai */
short EmuD_MZt::getw(AdrTyp adress, Word16Typ *valp)
{
short rc = False;
int portn;

  portn = (adress - portadr) / 2;
  if(portn < portnum)
  {
    if(((adress - portadr) % 2) == 0)
    {
      *valp = ports[portn];
    }
    else EmuSv.n_err("MZ: Trap to 10", adress, __FILE__, __LINE__);

    rc = True;
  }

  EmuSv.n_err("MZ: Read register", adress, __FILE__, __LINE__);

return(rc);
}


/* ------------- registro (baito) skaitymas; True - gerai */
short EmuD_MZt::getb(AdrTyp adress, ByteTyp *valp)
{
short rc = False;
int portn;

  portn = (adress - portadr) / 2;
  if(portn < portnum)
  {
    if(((adress - portadr) % 2) == 0)
    {
      *valp = (ByteTyp)(ports[portn] & ValMaskB);
    }
    else
    {
      *valp = (ByteTyp)((ports[portn] >> 8) & ValMaskB);
    }

    rc = True;
  }

  EmuSv.n_err("MZ: Read register", adress, __FILE__, __LINE__);

return(rc);
}


/* ------------- registro (zodzio) rasymas; True - gerai */
short EmuD_MZt::putw(AdrTyp adress, Word16Typ /* val */)
{
short rc = False;
int portn;

  portn = (adress - portadr) / 2;
  if(portn < portnum)
  {
    if(((adress - portadr) % 2) == 0)
    {
    }
    else EmuSv.n_err("MZ: Trap to 10", adress, __FILE__, __LINE__);

    rc = True;
  }

  EmuSv.n_err("MZ: Write register", adress, __FILE__, __LINE__);

return(rc);
}


/* ------------- registro (baito) rasymas; True - gerai */
short EmuD_MZt::putb(AdrTyp adress, ByteTyp /* val */)
{
short rc = False;
int portn;

  portn = (adress - portadr) / 2;
  if(portn < portnum)
  {
    rc = True;
  }

  EmuSv.n_err("MZ: Write register", adress, __FILE__, __LINE__);

return(rc);
}


/* ------------- registro (zodzio) rasymas is Win32 puses; True - gerai */
short EmuD_MZt::dputw(int portn, Word16Typ /* val */)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case MZ_CSR:
         rc=True;
         break;
//    default:
//       EmuSv.n_err("MZ: Illegal port", portn);
//       break;
      }
   }
// else
//    EmuSv.n_err("MZ: Illegal port", portn);

  EmuSv.n_err("MZ: Write register", portn, __FILE__, __LINE__);

return(rc);
}


// ------------- trukio generavimas
short EmuD_MZt::dintrpt(int portn)
{
short rc = False;

   if((portn>=0) && (portn < portnum))
   {
      switch(portn)
      {
      case MZ_CSR:
         if(ports[portn] & MZ_ien) EmuPv.intrpt(intvect + portn*2);
         rc=True;
         break;
      default:
         EmuSv.n_err("MZ: Illegal interrupt port", portn, __FILE__, __LINE__);
         break;
      }
   }
   else
      EmuSv.n_err("MZ: Illegal interrupt port", portn, __FILE__, __LINE__);

return(rc);
}
