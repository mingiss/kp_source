/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11y.cpp                                              */
/* DESCRIPTION:      Kphp11:  Atmintis                                        */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

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
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kphp11y.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11p.h"
#include "kphp11s.h"
#include "kphp11a.h"
#include "kphp11i.h"


/*---------------------------------------------------- var */
EmuYt EmuYv;


/* ----------------------------------------- konstruktorius */
EmuYt::EmuYt(void)
{
   bank = (ByteTyp *)cMemBank;
   mem_top = MemSize;
#ifdef Debug
#ifndef ExternalKphp11
      EmuYv.memsav((unsigned char *)"kphp11.bin");
#endif
#endif
}


/* ----------------------------------------- destruktorius */
EmuYt::~EmuYt(void)
{
#ifdef Debug
#if TRUE // #ifdef ExternalKphp11
      EmuYv.memsav((unsigned char *)"kphp11.bin");
#endif
#endif
}


/*--------------------------------------------------- skaitymas/rasymas */
/* True - gerai */
short EmuYt::getw(AdrTyp addrv, Word16Typ *valp)
{
short rc = False;

   if(0 != addrv % 2) EmuSv.n_err("Y: Odd address", addrv, __FILE__, __LINE__);
   else
   {
      if(addrv >= mem_top - 1)
      {
         rc = EmuDv.getw(addrv, valp);
         if(!rc)
         {
            EmuSv.n_err("Y: Trap to 4", addrv, __FILE__, __LINE__);
KP_TRACE("getw Trap to 4");
         }
      }
      else
      {
         *valp = /* (WordTyp) */ bank[addrv] | (/* (WordTyp) */ bank[addrv + 1] << 8);
         rc = True;
      }
   }

return(rc);
}


short EmuYt::getb(AdrTyp addrv, ByteTyp *valp)
{
short rc = False;

  if(addrv >= mem_top)
  {
    rc = EmuDv.getb(addrv, valp);
    if(!rc)
    {
       EmuSv.n_err("Y: Trap to 4", addrv, __FILE__, __LINE__);
KP_TRACE("getb Trap to 4");
    }
  }
  else
  {
    *valp = bank[addrv];
    rc = True;
  }
return(rc);
}


short EmuYt::putw(AdrTyp addrv, Word16Typ val)
{
short rc = False;

  if(0 != addrv % 2) EmuSv.n_err("Y: Odd address", addrv, __FILE__, __LINE__);
  else
  {
    if(addrv >= mem_top - 1)
    {
      rc = EmuDv.putw(addrv, val);
      if(!rc)
      {
         EmuSv.n_err("Y: Trap to 4", addrv, __FILE__, __LINE__);
KP_TRACE("putw Trap to 4");
      }
    }
    else
    {
      bank[addrv] = (ByteTyp)(val & ValMaskB);
      bank[addrv+1] = (ByteTyp)(val >> 8);
      rc = True;
    }
  }
return(rc);
}


short EmuYt::putb(AdrTyp addrv, ByteTyp val)
{
short rc = False;

  if(addrv >= mem_top)
  {
    rc = EmuDv.putb(addrv, val);
    if(!rc)
    {
       EmuSv.n_err("Y: Trap to 4", addrv, __FILE__, __LINE__);
KP_TRACE("putb Trap to 4");
    }
  }
  else
  {
    bank[addrv] = val;
    rc = True;
  }
return(rc);
}


/* ---------------------------------------------------- .sav failo skaitymas */
/* True - gerai */
short EmuYt::loadsav(
unsigned char *
#ifdef ExternalKphp11
fname
#endif
)
{
short rc = True;
Word16Typ /* AdrTyp */ ii;

#ifdef ExternalKphp11
FILE *ff;
ByteTyp byt;

  ff = fopen((char *)fname,"rb");
  if(NULL != ff)
  {
    ii = 0;
    do
    {
      byt = fgetc(ff);
      if(!feof(ff) && !ferror(ff)) rc &= putb(ii++, byt);
    } while(!feof(ff) && !ferror(ff) && rc);

    if(ferror(ff))
    {
      EmuSv.s_err("Y: File read error: ", fname, __FILE__, __LINE__);
      rc = False;
    }
#endif

    if(rc) rc &= getw(040, &ii);
    if(rc) rc &= EmuPv.putrw(PC_IND, ii);
    if(rc) rc &= getw(042, &ii);
    if(rc) rc &= EmuPv.putrw(SP_IND, ii);

#ifdef ExternalKphp11
  }
  else
  {
    EmuSv.s_err("Y: File not found: ",fname, __FILE__, __LINE__);
    rc = False;
  }
#endif

return(rc);
}


/* ------------------------------ atminties turinio issaugojimas .sav formatu */
/* True - gerai */
short EmuYt::memsav(unsigned char *fname)
{
short rc = True;
FILE *ff;
AdrTyp ii;
ByteTyp byt;

// KP_TRACE("memsav");

  ff = fopen((char *)fname,"wb");
  if(NULL != ff)
  {
    for(ii=0; (ii<mem_top) && rc; ii++)
    {
      rc &= getb(ii, &byt);
      fputc(byt, ff);
      if(feof(ff) || ferror(ff)) rc = False;;
    }
    if(rc) rc &= (fclose(ff) == 0);

    if(!rc) EmuSv.s_err("Y: File write error: ", fname, __FILE__, __LINE__);
  }
  else
  {
//  EmuSv.s_err("Y: Directory I/O error: ",fname, __FILE__, __LINE__);
//  rc = False;
  }

return(rc);
}
