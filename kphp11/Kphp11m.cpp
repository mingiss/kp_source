/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11m.cpp                                              */
/* DESCRIPTION:      Kphp11: Monitorius                                       */
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
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11p.h"
#include "kphp11d.h"
#include "kphp11s.h"


/*---------------------------------------------------- var */
EmuMt EmuMv;


/* ----------------------------------------- konstruktorius */
EmuMt::EmuMt()
{
  inpval = 0;
  address = UndefAdr;
  bytflg = False;
  inpfl = False;
  regrdfl = False;
  regwrfl = False;
}


/* --------------------------------------------------- init */
void EmuMt::minit(void)
{
  if(EmuSv.status==Monitor) prompt();
}


/* ---------------------------------------- prompt isvedimas */
void EmuMt::prompt(void)
{
  inpfl = False;
  inpval = 0;
  if(EmuWv.m_iCurX != 0) EmuWv.wputchar(Lf);
  EmuWv.wputchar('@');
}


/* ---------------------------------------- inpval isvedimas */
void EmuMt::printv(int posnum)
{
unsigned char buf[MaxValPosNum];

  itooct(inpval, buf, posnum);
  EmuWv.wputstr(buf);
}


/* ----------------------------- reiksmes skaitymas is atminties */
/* True - gerai */
short EmuMt::getval(void)
{
ByteTyp valb;
Word16Typ valw;
short rc;

  regwrfl = regrdfl;

  inpval = 0;

  if(regrdfl)
  {
    address %= NumOfReg;
    if(bytflg)
    {
      rc = EmuPv.getrb(address, &valb);
      if(rc) inpval = valb;
    }
    else
    {
      rc = EmuPv.getrw(address, /* (RegTyp *) */ &valw);
      if(rc) inpval = valw;
    }
  }
  else
  {
    if(bytflg)
    {
      rc = EmuYv.getb(address, &valb);
      if(rc) inpval = valb;
    }
    else
    {
      rc = EmuYv.getw(address, &valw);
      if(rc) inpval = valw;
    }
  }

return(rc);
}


/* ----------------------------- reiksmes irasymas i atminti */
/* True - gerai */
short EmuMt::putval(void)
{
short rc;

  regrdfl = regwrfl;

  if(regwrfl)
  {
    if(bytflg) rc = EmuPv.putrb(address,(ByteTyp)inpval);
    else rc = EmuPv.putrw(address,(RegTyp)inpval);
  }
  else
  {
    if(bytflg) rc = EmuYv.putb(address,(ByteTyp)inpval);
    else rc = EmuYv.putw(address,(Word16Typ)inpval);
  }

return(rc);
}


/* -------------------------------------- adreso isvedimas */
void EmuMt::pradr(void)
{
  if(regrdfl)
  {
    address &= 017;
    if(address > PS_IND) address = PS_IND;
    inpval = address;
    if(inpval < SP_IND)
    {
      EmuWv.wputchar('R');
      printv(1);
    }
    else
    {
      switch(inpval)
      {
        case SP_IND:
          EmuWv.wputstr("SP");
          break;
        case PC_IND:
          EmuWv.wputstr("PC");
          break;
        case PS_IND:
          EmuWv.wputstr("PS");
          break;
      }
    }
  }
  else
  {
    inpval = address;
    printv(ValPosNumW);
  }
}


/* ----------------------------------------- komandos apdorojimas */
void EmuMt::process(unsigned char ch)
{
short outv = False; /* ar reikia isvesti inpval turini */
short ii;
int   jj;
FILE *ff;
unsigned char  dnambuf[4];
unsigned char *fnamp;
unsigned char fname[Fnsiz+1];
char cch;

  ch = ctoupper(ch);

  if((ch >= '0') && (ch <= '7'))
  {
    inpval = ((inpval * 010) & MaxMask) + (ch - '0');
    if(!inpfl) regrdfl = False;
    inpfl = True;
    EmuWv.wputchar(ch);
  }
  else
  {
    switch(ch)
    {
      case 'H':
        EmuWv.wputchar(ch);
        EmuWv.wputstr("\n");
        EmuWv.wputstr("oooooo/      - open word\n");
        EmuWv.wputstr("oooooo\\      - open byte\n");
        EmuWv.wputstr(",            - next\n");
        EmuWv.wputstr("-            - previous\n");
        EmuWv.wputstr("@            - open indirect\n");
        EmuWv.wputstr("_            - open relative\n");
        EmuWv.wputstr("oooooo Enter - close\n");
        EmuWv.wputstr("Rn           - register\n");
        EmuWv.wputstr("P            - PC\n");
        EmuWv.wputstr("S            - SP\n");
        EmuWv.wputstr("W            - PSW\n");
        EmuWv.wputstr("ooooooT      - step\n");
        EmuWv.wputstr("ooooooG      - run\n");
        EmuWv.wputstr("^B           - break\n");
        EmuWv.wputstr("^T           - trace on/off\n");
        EmuWv.wputstr("^E           - interrupts trace on/off\n");
        EmuWv.wputstr("^W           - console on/off\n");
     /* EmuWv.wputstr("Q            - quit\n"); */
        EmuWv.wputstr("B            - boot (parameter - disk name: MZ0, MX0, ...)\n");
        EmuWv.wputstr("L            - load file (parameter - file name)\n");
        prompt();
        regrdfl = regwrfl;
        break;

      case '/':
        bytflg = False;
        if(inpfl) address = (AdrTyp)(inpval & AdrMask);
        inpfl = False;
        EmuWv.wputchar(ch);
        if(getval()) outv = True;
        else prompt();
        break;

      case '\\':
        bytflg = True;
        if(inpfl) address = (AdrTyp)(inpval & AdrMask);
        inpfl = False;
        EmuWv.wputchar(ch);
        if(getval()) outv = True;
        else prompt();
        break;

      case ',':
        EmuWv.wputchar(ch);
      case Lf:
        if(inpfl)
        {
          if(putval()) EmuWv.wputchar(Lf);
        }
        else EmuWv.wputchar(Lf);
        inpfl = False;

        address = (AdrTyp)(((long)address + ((bytflg || regrdfl)?1:2)) & AdrMask);
        if(regrdfl && (address > PS_IND)) address = 0;
        inpval = address;
        pradr();
        EmuWv.wputchar(bytflg?'\\':'/');
        if(getval()) outv = True;
        else prompt();
        break;

      case '-':
      case '^':
        EmuWv.wputchar(ch);
        if(inpfl)
        {
          if(putval()) EmuWv.wputchar(Lf);
        }
        else EmuWv.wputchar(Lf);
        inpfl = False;

        address = (AdrTyp)(((long)address - ((bytflg || regrdfl)?1:2)) & AdrMask);
        pradr();
        EmuWv.wputchar(bytflg?'\\':'/');
        if(getval()) outv = True;
        else prompt();
        break;

      case '@':
        EmuWv.wputchar(ch);
        if(inpfl)
        {
          if(putval()) EmuWv.wputchar(Lf);
        }
        else EmuWv.wputchar(Lf);
        inpfl = False;

        if(getval())
        {
          address = (AdrTyp)(inpval & AdrMask);
          regrdfl = False;
          regwrfl = False;
          bytflg = False;
          pradr();
          EmuWv.wputchar(bytflg?'\\': '/');
          if(getval()) outv = True;
          else prompt();
        }
        else prompt();
        break;

      case '_':
        EmuWv.wputchar(ch);
        if(inpfl)
        {
          if(putval()) EmuWv.wputchar(Lf);
        }
        else EmuWv.wputchar(Lf);
        inpfl = False;

        if(regrdfl)
        {
       /* cbeep(); */ /* Error */
          prompt();
        }
        else
        {
          if(getval())
          {
            if(bytflg)
            {
/* SOB poslinkiai !!!! */
              if(inpval & SigPosB) inpval |= ~(unsigned int)Maxchar;

              address = (AdrTyp)(((long)address + inpval*2 + 2) & AdrMask);
            }
            else address = (AdrTyp)(((long)address + inpval + 2) & AdrMask);
            regrdfl = False;
            regwrfl = False;
            bytflg = False;
            pradr();
            EmuWv.wputchar(bytflg?'\\': '/');
            if(getval()) outv = True;
            else prompt();
          }
          else prompt();
        }
        break;

      case Cr:
        if(inpfl) putval();
        prompt();
        break;

      case 'R':
        regrdfl = True;
        regwrfl = True;
        inpfl = True;
        inpval = 0;
        EmuWv.wputchar(ch);
        break;

      case 'P':
        regrdfl = True;
        regwrfl = True;
        inpfl = True;
        inpval = PC_IND;
        EmuWv.wputchar(ch);
        EmuWv.wputchar('C');
        process('/');
        break;

      case 'S':
        regrdfl = True;
        regwrfl = True;
        inpfl = True;
        inpval = SP_IND;
        EmuWv.wputchar(ch);
        EmuWv.wputchar('P');
        process('/');
        break;

      case 'W':
        regrdfl = True;
        regwrfl = True;
        inpfl = True;
        inpval = PS_IND;
        EmuWv.wputchar('P');
        EmuWv.wputchar('S');
        process('/');
        break;

      case 'T':
        EmuWv.wputchar(ch);
        ii = True;
        if(inpfl) ii &= EmuPv.putrw(PC_IND, (RegTyp)inpval);
        if(ii) EmuPv.iexe();
        EmuSv.status = Run;
        EmuSv.s_err("",(unsigned char *)"", __FILE__, __LINE__);
        regrdfl = regwrfl;
        break;

      case 'G':
        EmuWv.wputchar(ch);
        ii = True;
        if(inpfl) ii &= EmuPv.putrw(PC_IND, (RegTyp)inpval);
        if(ii)
        {
          EmuSv.status = Run;
          EmuWv.wputchar(Lf);
        }
        EmuPv.intlev = 0;
        inpfl = False;
        inpval = 0;
        regrdfl = regwrfl;
        break;

      case (CtrlFl & 'B'):
        EmuSv.status = Monitor;

        EmuWv.wputchar(Cr);
        EmuWv.wputchar(Lf);

        EmuSv.pr3();
        prompt();
        break;

      case (CtrlFl & 'T'):
        EmuSv.trfl = !EmuSv.trfl;
        if(Monitor == EmuSv.status)
        {
          EmuWv.wputstr("\nTrace ");
          EmuWv.wputstr(EmuSv.trfl?"on":"off");
          prompt();
        }
        break;

      case (CtrlFl & 'E'):
        EmuSv.intrfl = !EmuSv.intrfl;
        if(Monitor == EmuSv.status)
        {
          EmuWv.wputstr("\nTrace interrupts ");
          EmuWv.wputstr(EmuSv.intrfl?"on":"off");
          prompt();
        }
        break;
/*
      case 'Q':
        break;
*/
      case 'B':
        EmuWv.wputchar(ch);
        EmuWv.wputchar(':');

        while(Nul == (cch = EmuWv.wgetchar()));
        cch = ctoupper(cch);
        dnambuf[0] = cch;
        EmuWv.wputchar(cch);

        while(Nul == (cch = EmuWv.wgetchar()));
        cch = ctoupper(cch);
        dnambuf[1] = cch;
        EmuWv.wputchar(cch);

        dnambuf[2] = Nul;
        while(Nul == (cch = EmuWv.wgetchar()));
        EmuWv.wputchar(cch);

        if(EmuDv.getndevn(dnambuf, cch-'0', &jj))
        {
          fnamp = EmuDv.getfnam(jj);
          ff = fopen((char *)fnamp,"rb");
          if(NULL != ff)
          {
            ii = 0;
            do
            {
              EmuYv.putb(ii++, fgetc(ff));
            } while(!feof(ff) & !ferror(ff) & (ii < D_SectSiz));

            if(ferror(ff)) EmuSv.s_err("M: File read error: ", fnamp, __FILE__, __LINE__);
          }
          else EmuSv.s_err("M: File not found: ",fnamp, __FILE__, __LINE__);
        }
        else
        {
          dnambuf[2] = cch;
          dnambuf[3] = Nul;
          EmuSv.s_err("M: Device not found: ",dnambuf, __FILE__, __LINE__);
        }
        prompt();
        break;

      case 'L':
        EmuWv.wputchar(ch);
        EmuWv.wputchar(':');

        EmuWv.wgetstr(fname);
        EmuYv.loadsav(fname);
        prompt();
        break;

      default:
     /* cbeep(); */ /* klaidingas simbolis is klaviaturos */
        break;
    }
  }

  if(outv)
  {
    printv((!regrdfl && bytflg)?ValPosNumB:ValPosNumW);
    EmuWv.wputchar(Spc);
    inpval = 0;
  }
}
