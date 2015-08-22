/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11d.cpp                                              */
/* DESCRIPTION:      Kphp11:  Irenginiai                                      */
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
#include "kphp11tt.h"
#include "kphp11mz.h"
#include "kphp11rc.h"
#include "kphp11ry.h"
#include "kphp1152.h"
#include "kphp11s.h"


/* ----------------------------------------- konstruktorius */
EmuD_comt::EmuD_comt()
{
  devtyp = DEV_NO;
  portadr = 0;
  portnum = 0;
  intvect = 0;
  strcpy((char *)devnam,"  ");
  devno = 0;
  filnam[0] = Nul;
  wndw = NULL;
  ttadr = NULL;
}


/* ---------------------------------------------------- var */
EmuDt EmuDv;


/* ----------------------------------------- konstruktorius */
EmuDt::EmuDt(void)
{
int ii;

  for(ii=0; ii<MaxDev; ii++)
  {
    devcl[ii] = NULL;
  }
}


/* ------------------------------------------ destruktorius */
EmuDt::~EmuDt()
{
HRESULT retc = S_OK;

int ii;

  for(ii = 0; ii < MaxDev; ii++)
  {
    if(NULL != devcl[ii])
    {
      KP_DELETE(devcl[ii]->ttadr); // šiaip jau ir pats turėtų išsimest

      KP_DELETE(devcl[ii]);
    }
  }
}


/* ---------- portu adresu sinchronizavimas ir patikrinimas */
/* True - gerai */
short EmuDt::testports(void)
{
int ii, jj;
short rc = True;

  for(ii=0; ii<MaxDev-1; ii++)
  {
    if(NULL != devcl[ii])
    {
      if(devcl[ii]->portnum != 0)
      {
        if(devcl[ii]->portadr < EmuYv.mem_top) rc = False;

        for(jj=ii+1; jj<MaxDev; jj++)
        {
          if(NULL != devcl[jj])
          {
            if(devcl[jj]->portnum != 0)
            {
              if((devcl[jj]->devtyp == devcl[ii]->devtyp) &&
                 (devcl[jj]->devno == devcl[ii]->devno))
                rc = False;
              if((devcl[jj]->portadr >= devcl[ii]->portadr) &&
                 (devcl[jj]->portadr <
                  devcl[ii]->portadr + 2*devcl[ii]->portnum))
                rc = False;
              if((devcl[jj]->portadr + 2*devcl[jj]->portnum >
                  devcl[ii]->portadr) &&
                 (devcl[jj]->portadr + 2*devcl[jj]->portnum <=
                  devcl[ii]->portadr + 2*devcl[ii]->portnum))
                rc = False;
            }
          }
        }
      }
    }
  }

  if(!rc) EmuSv.s_err("D: Device conflict", (unsigned char *)"", __FILE__, __LINE__);

return(rc);
}


/* ----------------------------- naujo irenginio prijungimas */
/* devtp - irenginio tipas
   porta - CSR adresas,
   intv  - trukio vekt. adr.,
   devn  - kisenes nr.,
   filn  - susieto failo vardas,
   wnd   - terminalo isvedimo langas,
   tta   - terminalo tipo klases adresas.
True - gerai */
short EmuDt::plugdev(DevTypes devtp, AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd, TermTypes termtyp)
{
int ii;
EmuD_TT_comt *tta = NULL;
short rc = False;
HRESULT retc = S_OK;

  for(ii=0; ii<MaxDev; ii++)
  {
    if(NULL == devcl[ii])
    {
      switch(termtyp)
      {
        case TERM_VT52:
          KP_NEW(tta, EmuD_TT_vt52t);
          break;
      }

      switch(devtp)
      {
      case DEV_TT:
         KP_NEW(devcl[ii], EmuD_TTt(porta, intv, devn, filn, wnd, tta));
         break;
      case DEV_MZ:
         KP_NEW(devcl[ii], EmuD_MZt(porta, intv, devn, filn, wnd, tta));
         break;
      case DEV_RC:
         KP_NEW(devcl[ii], EmuD_RCt(porta, intv, devn, filn, wnd, tta));
         break;
      case DEV_RY:
         KP_NEW(devcl[ii], EmuD_RYt(porta, intv, devn, filn, wnd, tta));
         break;
      default: KP_ERROR(E_INVALIDARG, null);
      }
      if(NULL != devcl[ii]) rc = True;
      break;
    }
  }
  if(!rc) EmuSv.s_err("D: Impossible to plug device", (unsigned char *)"", __FILE__, __LINE__);

  rc &= testports();

return(rc);
}


/* ---------- irenginiu inicializavimas (trukiu uzdraudimas) */
/* True - gerai */
short EmuDt::reset(void)
{
int ii;
short rc = True;

  for(ii=0; ii<MaxDev; ii++)
  {
    if(NULL != devcl[ii])
      devcl[ii]->reset();
  }

  if(!rc) EmuSv.s_err("D: Illegal device", (unsigned char *)"", __FILE__, __LINE__);

return(rc);
}


/* --------- irenginio suradimas pagal reg. adr., True - surado */
short EmuDt::getdevn(AdrTyp adress, int *devnr)
{
short rc = False;
int ii;

  for(ii=0; ii<MaxDev; ii++)
  {
    if(NULL != devcl[ii])
    {
      if((adress >= devcl[ii]->portadr) &&
         (adress < devcl[ii]->portadr + 2*devcl[ii]->portnum))
      {
        *devnr = ii;
        rc = True;
        break;
      }
    }
  }

return(rc);
}


/* ---------------------------- irenginio suradimas pagal varda */
/* devnm - vardas (MZ, MX, ...), devn - kisenes nr.,
   grazina devnr - ireng. masyvo indexa, True - surado */
short EmuDt::getndevn(unsigned char *devnm, int devn, int *devnr)
{
short rc = False;
int ii;

  for(ii=0; ii<MaxDev; ii++)
  {
    if(NULL != devcl[ii])
    {
      if((devnm[0] == devcl[ii]->devnam[0]) &&
         (devnm[1] == devcl[ii]->devnam[1]) &&
         (devn == devcl[ii]->devno))
      {
        *devnr = ii;
        rc = True;
        break;
      }
    }
  }

return(rc);
}


/* ---------------------------- irenginio suradimas pagal varda */
/* devtp - irenginio tipas, devn - kisenes nr.,
   grazina devnr - ireng. masyvo indexa, True - surado */
short EmuDt::getndevn(DevTypes devtp, int devn, int *devnr)
{
short rc = False;
int ii;

  for(ii=0; ii<MaxDev; ii++)
  {
    if(NULL != devcl[ii])
    {
      if((devtp == devcl[ii]->devtyp) &&
         (devn == devcl[ii]->devno))
      {
        *devnr = ii;
        rc = True;
        break;
      }
    }
  }

return(rc);
}


/* ---------------------- irenginio failo vardas, NULL - nerado */
unsigned char *EmuDt::getfnam(int devnr)
{
unsigned char *rp = NULL;

  if(NULL != devcl[devnr]) rp = devcl[devnr]->filnam;

return(rp);
}


/* ------------------ registro (zodzio) skaitymas, True - gerai */
short EmuDt::getw(AdrTyp adress, Word16Typ *valp)
{
short rc = False;
int devn;

   if(getdevn(adress, &devn))
      rc = devcl[devn]->getw(adress, valp);

return(rc);
}


/* ------------------ registro (baito) skaitymas, True - gerai */
short EmuDt::getb(AdrTyp adress, ByteTyp *valp)
{
short rc = False;
int devn;

   if(getdevn(adress, &devn))
      rc = devcl[devn]->getb(adress, valp);

return(rc);
}


/* ------------------ registro (zodzio) rasymas, True - gerai */
short EmuDt::putw(AdrTyp adress, Word16Typ val)
{
short rc = False;
int devn;

   if(getdevn(adress, &devn))
      rc = devcl[devn]->putw(adress, val);

return(rc);
}


/* ------------------ registro (baito) rasymas, True - gerai */
short EmuDt::putb(AdrTyp adress, ByteTyp val)
{
short rc = False;
int devn;

   if(getdevn(adress, &devn))
      rc = devcl[devn]->putb(adress, val);

return(rc);
}


/* --------------- i klaviaturos eile, False - nerado terminalo */
short EmuDt::tokb(KbChar /* unsigned int */ ch)
{
int ii;
short brfl = False;

 /* kaip, jei keli terminalai? */
   for(ii=0; (ii<MaxDev) && (!brfl) ; ii++)
   {
      if(NULL != devcl[ii])
      {
         if(DEV_TT == devcl[ii]->devtyp)
         {
            if(NULL != devcl[ii]->ttadr)
            {
               (devcl[ii]->ttadr)->ttokbbuf(ch);
               brfl = True;
            }
         }
      }
   }

return(brfl);
}


/* --------------- ar yra simboliu klaviaturoje */
short EmuDt::dkbhit(void)
{
short rc=False;
int ii;
short brfl = False;

/* kaip, jei keli terminalai? */
   for(ii=0; (ii<MaxDev) && (!brfl) ; ii++)
   {
      if(NULL != devcl[ii])
      {
         if(DEV_TT == devcl[ii]->devtyp)
         {
            if(NULL != devcl[ii]->ttadr)
            {
               rc=(devcl[ii]->ttadr)->tkbhit();
               brfl = True;
            }
         }
      }
   }

return(rc);
}


// -----------------------
short EmuDt::ddputw(DevTypes devtp, int devn, int portn, Word16Typ val)
{
short rc=False;
int devnr;

   rc=getndevn(devtp, devn, &devnr);
   if(rc)
   {
      if(NULL != devcl[devnr])
         rc=devcl[devnr]->dputw(portn, val);
      else
         EmuSv.n_err("D: Device not found", devtp, __FILE__, __LINE__);
   }

return(rc);
}


// -----------------------
short EmuDt::ddintrpt(DevTypes devtp, int devn, int portn)
{
short rc=False;
int devnr;

   rc=getndevn(devtp, devn, &devnr);
   if(rc)
   {
      if(NULL != devcl[devnr])
         rc=devcl[devnr]->dintrpt(portn);
      else
         EmuSv.n_err("D: Device not found", devtp, __FILE__, __LINE__);
   }

return(rc);
}
