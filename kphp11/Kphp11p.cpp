/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11p.cpp                                              */
/* DESCRIPTION:      Kphp11:  Procesorius                                     */
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
#include "kphp11rc.h"

/*---------------------------------------------------- var */
EmuPt EmuPv;


/* ----------------------------------------- konstruktorius */
EmuPt::EmuPt()
{
int ii;

  for(ii=0; ii<SP_IND; ii++) reg[ii]=0;
  SP=1000;
  PC=0;
  PS=0;

  waitint=0;
  waitprio=0;
  
#ifdef KPHP11_SPEED_CALIBRATED
   m_lInterv = m_lOps = 0100000L;
   m_lCurInsCnt = 0L;

SYSTEMTIME cur_time_obj;
   GetSystemTime(&cur_time_obj);
   m_lPrevTime = cur_time_obj.wSecond * 1000 + cur_time_obj.wMilliseconds;
   
   m_iMsecsDelay = 500L;
#endif  
}


/*PH****-------------------------------------- registru skaitymas/rasymas */
/* True - gerai */
short EmuPt::TestSP(RegTyp iNewVal)
{
short rc=True;

   if(iNewVal<=MIN_SP)
   {
      rc=EmuSv.s_err("P: Stack overflow", (unsigned char *)"", __FILE__, __LINE__);
      EmuSv.status = Monitor;
      EmuMv.prompt();
   }

return(rc);
}

short EmuPt::getrw(AdrTyp regno, RegTyp *val)
{
short rc=True;

   if((regno >= NumOfReg) && rc) rc=EmuSv.n_err("P: Illegal register", regno, __FILE__, __LINE__);

   if(rc) *val = R[regno];

return(rc);
}


short EmuPt::getrb(AdrTyp regno, ByteTyp *val)
{
short rc=True;

   if((regno >= NumOfReg) && rc) rc=EmuSv.n_err("P: Illegal register", regno, __FILE__, __LINE__);

   if(rc) *val = (ByteTyp)(R[regno] & ValMaskB);

return(rc);
}


short EmuPt::putrw(AdrTyp regno, RegTyp val)
{
short rc=True;

   if((regno >= NumOfReg) && rc) rc=EmuSv.n_err("P: Illegal register", regno, __FILE__, __LINE__);

   if((regno==SP_IND) && rc) rc=TestSP(val);

   if(rc)
   {
      if(PS_IND != regno) R[regno] = val /* & RegMaskW */;
      else mtps(val);
   }

return(rc);
}


short EmuPt::putrb(AdrTyp regno, ByteTyp val)
{
short rc=True;
RegTyp new_val;

   if((regno >= NumOfReg) && rc) rc=EmuSv.n_err("P: Illegal register", regno, __FILE__, __LINE__);

   if(rc)
   {
      if(PS_IND != regno)
      {
         new_val = val;
         if(val & SigPosB) new_val |= SigMaskB;
         new_val = (new_val & ~ValMaskB) | val;

         if((regno==SP_IND) && rc) rc=TestSP(new_val);

         if(rc) R[regno] = new_val;
      }
      else mtps(val);
   }

return(rc);
}


/* ------------------------------------------------- rasymas i PSW */
void EmuPt::mtps(RegTyp val)
{
AdrTyp tmpint;

  PS = val & FL_PS;
  if((0 != waitint) && (waitprio >= (val & FL_P)))
  {

#if FALSE // #ifdef Debug //
char str_buf[100];
sprintf(str_buf, "kphp11p: interrupt %06o released", waitint);
KP_TRACE(str_buf);
#endif

    tmpint = waitint;
    waitint = 0;
    waitprio = 0;
    intrpt(tmpint);
  }
}


/*PH****------------------------------------------ darbas su steku */
short EmuPt::push(Word16Typ val)
{
RegTyp regval;
short rc=True;

   regval = (RegTyp)(((long)SP - 2) & AdrMask);
   rc=TestSP(regval);
   if(rc)
   {
      SP = regval;
      rc = EmuYv.putw((AdrTyp)regval, val);
   }

return(rc);
}


short EmuPt::pop(Word16Typ *valp)
{
RegTyp regval;
short rc=True;

  regval = SP;
  rc = EmuYv.getw((AdrTyp)regval, valp);
  if(rc) SP = (RegTyp)(((long)regval + 2) & AdrMask);

return(rc);
}


/*PH****--------------------------------------------------- trukis */
/* True - gerai */
short EmuPt::intrpt(AdrTyp intvec)
{
Word16Typ retw;
short rc = False;
#ifdef Debug
// char str_buf[100];
#endif

  if(intvec & 03) EmuSv.n_err("P: Illegal interrupt vector", intvec, __FILE__, __LINE__);
  else
  {
    rc = EmuYv.getw((AdrTyp)(((long)intvec + 2) & AdrMask), &retw);
    if(rc)
    {
      if(((PS & FL_P) <= (retw & FL_P)) || (intvec==EMT_INTV) || (intvec==TRAP_INTV))
      {
#if FALSE // #ifdef Debug //
if(intvec==RC_DEF_INT) KP_TRACE("kphp11p: RC interrupt triggered")
// else
// {
// sprintf(str_buf, "kphp11p: interrupt %06o triggered", intvec);
// KP_TRACE(str_buf);
// }
#endif
        rc = push(PS);
        if(rc) rc = push(PC);

        if(rc) mtps((RegTyp)retw /* & RegMaskW */);
        if(rc) rc = EmuYv.getw(intvec, &retw);
        if(rc) PC = (RegTyp)retw /* & AdrMask */;
        if(rc) intlev++;
      }
      else
      {
        if(0 != waitint) EmuSv.s_err("P: Lost interrupt", (unsigned char *)"", __FILE__, __LINE__);

        waitint = intvec;
        waitprio = (retw & FL_P);

#if FALSE // #ifdef Debug //
sprintf(str_buf, "kphp11p: interrupt %06o delayed", intvec);
KP_TRACE(str_buf);
#endif

      }
    }
  }

  if(EmuSv.status == Wait) EmuSv.status = Run;
  if(!rc && (EmuSv.status != Monitor))
  {
/* !!!! siaip nereikia, kai viskas veiks */
    EmuSv.status = Monitor;
    EmuMv.prompt();
  }

return(rc);
}


/*PH****-------------------------------- efective address suradimas */
/* True - gerai */
short EmuPt::getea(unsigned int ea, FulAdrTyp *addrp, short bytfl)
{
AdrTyp regno;
RegTyp regval;
Word16Typ retw = 0;
AdrTyp addrv = UndefAdr;
short regflgv = False;
short rc = True;

  regno = (AdrTyp)(ea & 07);
  switch((ea & 070) >> 3)
  {
    case 0:
      addrv = regno;
      regflgv = True;
      break;

    case 1:
      addrv = (AdrTyp)(R[regno]);
      break;

    case 2:
      addrv = (AdrTyp)(R[regno]);
      R[regno] = (RegTyp)(
                           (
                             (long)addrv +
                             ((bytfl && (regno < SP_IND))?1:2)
                           ) & AdrMask
                         );
      break;

    case 3:
      addrv = (AdrTyp)(R[regno]);
      R[regno] = (RegTyp)(((long)addrv + 2) & AdrMask);
      rc = EmuYv.getw(addrv, &retw);
      if(rc) addrv = (AdrTyp)retw;
      break;

    case 4:
      addrv = (AdrTyp)(
                        (
                          (long)R[regno] -
                          ((bytfl && (regno < SP_IND))?1:2)
                        ) & AdrMask
                      );
      if(regno==SP_IND) rc=TestSP((RegTyp)addrv);
      if(rc) R[regno] = (RegTyp)addrv;
      break;

    case 5:
      regval = (RegTyp)(((long)R[regno] - 2) & AdrMask);
      if(regno==SP_IND) rc=TestSP(regval);
      if(rc)
      {
         R[regno] = regval;
         rc = EmuYv.getw((AdrTyp)regval, &retw);
      }
      if(rc) addrv = (AdrTyp)retw;
      break;

    case 6:
      regval = PC;
      PC = (RegTyp)(((long)regval + 2) & AdrMask);
      rc = EmuYv.getw((AdrTyp)regval, &retw);
      if(rc) addrv = (AdrTyp)(((long)retw + R[regno]) & AdrMask);
      break;

    case 7:
      regval = PC;
      PC = (RegTyp)(((long)regval + 2) & AdrMask);
      rc = EmuYv.getw((AdrTyp)regval, &retw);
      if(rc)
      {
        rc = EmuYv.getw((AdrTyp)(((long)retw + R[regno]) & AdrMask), &retw);
        if(rc) addrv = (AdrTyp)retw;
      }
      break;
  }

  if(rc)
  {
    addrp->addr = addrv;
    addrp->regflg = regflgv;
  }

return(rc);
}


/*PH****----------------------------------------- skaitymas pagal adresa */
short EmuPt::getdea(FulAdrTyp *addrp, long *resp, short bytfl)
{
ByteTyp retb = 0;
Word16Typ retw = 0;
long res = 0l;
short rc = True;

  if(addrp->regflg)
  {
    if(bytfl)
    {
      rc = getrb(addrp->addr, &retb);
      if(rc) res = retb;
    }
    else
    {
      rc = getrw(addrp->addr, /* (RegTyp *) */ &retw);
      if(rc) res = retw;
    }
  }
  else
  {
    if(bytfl)
    {
      rc = EmuYv.getb(addrp->addr, &retb);
      if(rc) res = retb;
    }
    else
    {
      rc = EmuYv.getw(addrp->addr, &retw);
      if(rc) res = retw;
    }
  }

  if(bytfl)
  {
    if(res & SigPosB) res |= SigMaskB;
  }
  else
  {
    if(res & SigPosW) res |= SigMaskW;
  }

  if(rc) *resp = res;

return(rc);
}


/* --------------------------------------------------- rasymas adresu */
/* True - gerai */
short EmuPt::putdea(FulAdrTyp *addrp, long val, short bytfl)
{
short rc = False;

  if(addrp->regflg)
  {
    if(bytfl) rc = putrb(addrp->addr, (ByteTyp)val);
    else rc = putrw(addrp->addr, (RegTyp)val);
  }
  else
  {
    if(bytfl) rc = EmuYv.putb(addrp->addr, (ByteTyp)val);
    else rc = EmuYv.putw(addrp->addr, (Word16Typ)val);
  }

return(rc);
}


/*PH****------------------------------------------ FL_N ir FL_Z uzpildymas */
void EmuPt::setclrfl(long val)
{
  if(val == 0) setfl(FL_Z);
  else clrfl(FL_Z);

  if(val < 0) setfl(FL_N);
  else clrfl(FL_N);
}


/* ------------------------------------ sudetis / atimtis (arg1 - arg2),
                                   pasirupinant perpildymu veliavelemis */
long EmuPt::dadd(long arg1, long arg2, short bytfl, short subfl)
{
long res, maxval, sigpos;

if(arg1==0177774)
arg1=0177774;

  maxval = (bytfl? Maxuchar: Maxuint); /* naudoju ir kaip kauke */
  if(subfl) res = (arg1 & maxval) - (arg2 & maxval);
  else res = (arg1 & maxval) + (arg2 & maxval);
  if((res > maxval) || (res < 0)) setfl(FL_C);
  else clrfl(FL_C);

  if(subfl) res = arg1 - arg2;
  else res = arg1 + arg2;
  maxval = (bytfl? Maxchar: Maxint);
  if((res > maxval) || (res < -maxval-1)) setfl(FL_V);
  else clrfl(FL_V);

/* maxval = (bytfl? ValMaskB: ValMaskW); */
  sigpos = (bytfl? SigPosB: SigPosW);
  if(res & sigpos) res |= ~maxval;
  else res &= maxval;

return(res);
}


/*PH****--------------------------------- unariniu instrukciju vykdymas */
short EmuPt::procunar(unsigned int opcod, FulAdrTyp *destp, short bytfl)
{
unsigned int flag_c;
long dakku, sigpos, negmask, oldval;
short rc = True;

  switch(opcod)
  {
    case 0005000:    /* CLR */
      clrfl(FL_N | FL_V | FL_C);
      setfl(FL_Z);
      rc = putdea(destp, 0, bytfl);
      break;

    case 0005700:    /* TST */
      rc = getdea(destp, &dakku, bytfl);
      if(rc)
      {
        clrfl(FL_V | FL_C);
        setclrfl(dakku);
      }
      break;

    default:
      rc = getdea(destp, &dakku, bytfl);
      if(rc)
      {
        switch(opcod)
        {
          case 0005100:    /* COM */
            dakku = ~dakku;
            clrfl(FL_V);
            setfl(FL_C);
            break;

          case 0005200:    /* INC */
            flag_c = getfl(FL_C);
            dakku = dadd(dakku, 1, bytfl, False);
            if(flag_c) setfl(FL_C);
            else clrfl(FL_C);
            break;

          case 0005300:    /* DEC */
            flag_c = getfl(FL_C);
            dakku = dadd(dakku, 1, bytfl, True);
            if(flag_c) setfl(FL_C);
            else clrfl(FL_C);
            break;

          case 0005400:    /* NEG */
            dakku = (~dakku);
            dakku = dadd(dakku, 1, bytfl, False);
            break;

          case 0005500:    /* ADC */
            dakku = dadd(dakku, (getfl(FL_C)? 1: 0), bytfl, False);
            break;

          case 0005600:    /* SBC */
            dakku = dadd(dakku, (getfl(FL_C)? 1: 0), bytfl, True);
            break;

          case 0006000:    /* ROR */
            if(bytfl)
            {
              sigpos = SigPosB;
              negmask = SigMaskB;
            }
            else
            {
              sigpos = SigPosW;
              negmask = SigMaskW;
            }
            flag_c = (unsigned int)dakku & 01;
            oldval = dakku;
            if(getfl(FL_C)) dakku |= negmask;
            else dakku &= ~negmask;
            dakku = dakku >> 1;
            if(flag_c) setfl(FL_C);
            else clrfl(FL_C);
            if((dakku & sigpos) == (oldval & sigpos)) clrfl(FL_V);
            else setfl(FL_V);
            break;

          case 0006100:    /* ROL */
            if(bytfl)
            {
              sigpos = SigPosB;
              negmask = SigMaskB;
            }
            else
            {
              sigpos = SigPosW;
              negmask = SigMaskW;
            }
            flag_c = (unsigned int)(dakku & sigpos);
            oldval = dakku;
            dakku = dakku << 1;
            if(getfl(FL_C)) dakku |= 01;
            else dakku &= ~01;
            if(dakku & sigpos) dakku |= negmask;
            else dakku &= ~negmask;
            if(flag_c) setfl(FL_C);
            else clrfl(FL_C);
            if((dakku & sigpos) == (oldval & sigpos)) clrfl(FL_V);
            else setfl(FL_V);
            break;

          case 0006200:    /* ASR */
            if(dakku & 01) setfl(FL_C);
            else clrfl(FL_C);
            dakku = dakku >> 1;
            clrfl(FL_V);
            break;

          case 0006300:    /* ASL */
            if(bytfl)
            {
              sigpos = SigPosB;
              negmask = SigMaskB;
            }
            else
            {
              sigpos = SigPosW;
              negmask = SigMaskW;
            }
            if(dakku & sigpos) setfl(FL_C);
            else clrfl(FL_C);
            oldval = dakku;
            dakku = dakku << 1;
            if(dakku & sigpos) dakku |= negmask;
            else dakku &= ~negmask;
            if((dakku & sigpos) == (oldval & sigpos)) clrfl(FL_V);
            else setfl(FL_V);
            break;

          default:
            EmuSv.n_err("P: Trap to 10", opcod, __FILE__, __LINE__);
            rc = False;
            break;
        }
      }

      if(rc)
      {
        rc = putdea(destp, dakku, bytfl);
        if(rc) setclrfl(dakku);
      }
      break;
  }

return(rc);
}


/*PH****--------------------------------- binariniu instrukciju vykdymas */
short EmuPt::procbinar(unsigned int opcod, FulAdrTyp *srcp, FulAdrTyp *destp, short bytfl)
{
long sakku, dakku;
short rc = True;

  if(opcod != 0060000)
  {
    rc = getdea(srcp, &sakku, bytfl);
    if(opcod > 0010000) if(rc) rc = getdea(destp, &dakku, bytfl);
  }
  else
  {
    rc = getdea(srcp, &sakku, False);
    if(rc) rc = getdea(destp, &dakku, False);
  }

  if(rc)
  {
    switch(opcod)
    {
      case 0010000:    /* MOV */
        dakku = sakku;
        clrfl(FL_V);
        break;

      case 0020000:    /* CMP */
        dakku = dadd(sakku, dakku, bytfl, True);
        break;

      case 0030000:    /* BIT */
        dakku = sakku & dakku;
        clrfl(FL_V);
        break;

      case 0040000:    /* BIC */
        dakku = ~sakku & dakku;
        clrfl(FL_V);
        break;

      case 0050000:    /* BIS */
        dakku = sakku | dakku;
        clrfl(FL_V);
        break;

      case 0060000:
        if(bytfl) dakku = dadd(dakku, sakku, False, True); /* SUB */
        else dakku = dadd(dakku, sakku, False, False);     /* ADD */
        break;

      default:
        EmuSv.n_err("P: Trap to 10", opcod, __FILE__, __LINE__);
        rc = False;
        break;
    }
  }

  if(rc)
  {
    if((opcod != 0020000) && (opcod != 0030000))
    {
      rc = putdea(destp, dakku, ((opcod != 0060000) && bytfl));
    }
    setclrfl(dakku);
  }

return(rc);
}


/*PH****------------------------------------------------------- MUL & Cø */
short EmuPt::procmul(unsigned int opcod, AdrTyp regno, FulAdrTyp *srcp)
{
long sakku, dakku, dsav;
short rc = True;

  if(regno >= SP_IND)
  {
    EmuSv.n_err("P: Illegal register", opcod, __FILE__, __LINE__);
    rc = False;
  }

  if(rc)
  {
    if(((071000 == opcod) || (073000 == opcod)) && (0 == (regno % 2)))
    {
      dakku = reg[regno] | ((long)reg[regno+1] << 16);
      if(dakku & SigPosL) dakku |= SigMaskL;
    }
    else
    {
      dakku = (int)reg[regno];
      if(dakku & SigPosW) dakku |= SigMaskW;
    }

    rc = getdea(srcp, &sakku, False);
  }

  if(rc)
  {
    switch(opcod)
    {
      case 0070000:               /* MUL */
        dakku *= sakku;

        reg[regno] = (RegTyp)(dakku & ValMaskW);
        if(0 == (regno % 2))
        {
          reg[regno+1] = (RegTyp)((dakku >> 16) & ValMaskW);

//        if((dakku > Maxlong) || (dakku < -Maxlong-1)) setfl(FL_V);
//        else
             clrfl(FL_V);

//        if(dakku > Maxulong) setfl(FL_C);
//        else
             clrfl(FL_C);
        }
        else
        {
          if((dakku > Maxint) || (dakku < -Maxint-1)) setfl(FL_V);
          else clrfl(FL_V);
          if(dakku > Maxuint) setfl(FL_C);
          else clrfl(FL_C);
        }
     /* clrfl(FL_V); */
        break;

      case 0071000:               /* DIV */
        dakku /= sakku;

        reg[regno] = (RegTyp)(dakku & ValMaskW);
        if(0 == (regno % 2))
        {
          reg[regno+1] = (RegTyp)((dakku % sakku) & ValMaskW);
        }
        clrfl(FL_C | FL_V); /* !!!! reikia kazkaip nustatyti? */
        break;

      case 0072000:               /* ASH */
        dsav = dakku;
        if(sakku > 0) dakku <<= sakku;
        if(sakku < 0) dakku >>= -sakku;

        reg[regno] = (RegTyp)(dakku & ValMaskW);

        if((dsav & (SigMaskW | SigPosW)) != (dakku & (SigMaskW | SigPosW))) setfl(FL_V);
        else clrfl(FL_V);
        setfl(FL_C); /* !!!! reikia kazkaip nustatyti? */
        break;

      case 0073000:               /* ASHC */
        dsav = dakku;
        if(sakku > 0) dakku <<= sakku;
        if(sakku < 0) dakku >>= -sakku;

        reg[regno] = (RegTyp)(dakku & ValMaskW);
        if(0 == (regno % 2))
        {
          reg[regno+1] = (RegTyp)((dakku >> 16) & ValMaskW);

          if((dsav & (SigMaskL | SigPosL)) != (dakku & (SigMaskL | SigPosL))) setfl(FL_V);
          else clrfl(FL_V);
        }
        else
        {
          if((dsav & (SigMaskW | SigPosW)) != (dakku & (SigMaskW | SigPosW))) setfl(FL_V);
          else clrfl(FL_V);
        }
        setfl(FL_C); /* !!!! reikia kazkaip nustatyti? */
        break;

      case 0074000:               /* XOR */
        dakku ^= sakku;
        rc = putdea(srcp, dakku, False);
        if(rc) clrfl(FL_V);
        break;

      default:
        EmuSv.n_err("P: Trap to 10", opcod, __FILE__, __LINE__);
        rc = False;
        break;
    }
  }

  if(rc) setclrfl(dakku);

return(rc);
}


/*PH****--------------------- BR-u analizavimas: True - salyga tenkinama */
short EmuPt::procbr(unsigned int opcod)
{
unsigned int flag;
short rc = True;

  switch(opcod)
  {
    case 0000400: break;                           /* BR */
    case 0100000: rc = (getfl(FL_N) == 0); break;  /* BPL */
    case 0100400: rc = (getfl(FL_N) != 0); break;  /* BMI */
    case 0001000: rc = (getfl(FL_Z) == 0); break;  /* BNE */
    case 0001400: rc = (getfl(FL_Z) != 0); break;  /* BEQ */
    case 0102000: rc = (getfl(FL_V) == 0); break;  /* BVC */
    case 0102400: rc = (getfl(FL_V) != 0); break;  /* BVS */
    case 0103000: rc = (getfl(FL_C) == 0); break;  /* BCC, BHIS */
    case 0103400: rc = (getfl(FL_C) != 0); break;  /* BCS, BLO */

    case 0002000:                       /* BGE */
      flag = getfl(FL_N | FL_V);
      rc = ((flag == (FL_N | FL_V)) || (flag == 0));
      break;

    case 0002400:                       /* BLT */
      flag = getfl(FL_N | FL_V);
      rc = ((flag == FL_N) || (flag == FL_V));
      break;

    case 0003000:                       /* BGT */
      flag = getfl(FL_N | FL_Z | FL_V);
      rc = ((flag == (FL_N | FL_V)) || (flag == 0));
      break;

    case 0003400:                       /* BLE */
      flag = getfl(FL_N | FL_V);
      rc = ((flag == FL_N) || (flag == FL_V));
      rc |= (getfl(FL_Z) != 0);
      break;

    case 0101000:                       /* BHI */
      rc = (getfl(FL_Z | FL_C) == 0);
      break;

    case 0101400:                      /* BLOS */
      rc = ((getfl(FL_C) != 0) || (getfl(FL_Z) != 0));
      break;

    default:
      EmuSv.n_err("P: Trap to 10", opcod, __FILE__, __LINE__);
      rc = False;
      break;
  }

return(rc);
}


// -------------------------------------------
#ifdef KPHP11_SPEED_CALIBRATED
void EmuPt::DoDelay(void)
{
   m_lCurInsCnt++;
   
   if(m_lCurInsCnt >= m_lOps)
   {
SYSTEMTIME cur_time_obj;
long cur_time;
      GetSystemTime(&cur_time_obj);
      cur_time = cur_time_obj.wSecond * 1000 + cur_time_obj.wMilliseconds;
      
      if(cur_time > m_lPrevTime) // ignoruojam minutÓs ribÐ
         m_iMsecsDelay -= (cur_time - m_lPrevTime) - 1000L;

      m_lInterv = m_lOps;
      if(m_iMsecsDelay > 0) 
            m_lInterv = m_lOps * 10L / m_iMsecsDelay;

PutLogMessage_("EmuPt::DoDelay(): %ld %ld", cur_time - m_lPrevTime, m_iMsecsDelay);

      m_lPrevTime = cur_time;
      
      m_lCurInsCnt = 0L;
   }

// stabtelim
   if(m_lInterv > 0)             
      if(m_lCurInsCnt % m_lInterv == 0) Sleep(10);
      
}
#endif


/*PH****---------------------------------- vienos instrukcijos ivykdymas */
short EmuPt::iexe(void)
{
Word16Typ /* unsigned int */ iakku;
unsigned int opcod;
long dakku, byte_l, byte_h;
AdrTyp regno;
FulAdrTyp src, dest;
short bytfl;
short rc, done = False;
long offset;
Word16Typ retw;

#ifdef KPHP11_SPEED_CALIBRATED
   DoDelay();
#endif

  rc = EmuYv.getw((AdrTyp)PC, /* (WordTyp *) */ &iakku);
  PC = (RegTyp)(((long)PC + 2) & AdrMask);

#if FALSE // #ifdef Debug //
char str_buf[300];
unsigned int a1, a2;
EmuYv.getw((AdrTyp)PC, /* (WordTyp *) */ &a1);
EmuYv.getw((AdrTyp)PC+2, /* (WordTyp *) */ &a2);
sprintf(str_buf, "SP:%06o PC:%06o/%06o %06o %06o", SP, PC-2, iakku, a1, a2);
KP_TRACE(str_buf);
#endif

/* ------------------------------------------ unarines instrukcijos */
  if((rc) /* && (!done) */)
  {
    {
      opcod = (iakku & 0077700);
      if((opcod >= 0005000) && (opcod <= 0006300))
      {
        bytfl = ((0100000 & iakku) == 0100000);
        rc = getea(000077 & iakku, &dest, bytfl);
        if(rc) rc = procunar(opcod, &dest, bytfl);
        done = True;
      }
    }
  }


/* ---------------------------------------- binarines instrukcijos */
  if((rc) && (!done))
  {
    opcod = (iakku & 0070000);
    if((opcod >= 0010000) && (opcod <= 0060000))
    {
      bytfl = ((0100000 & iakku) == 0100000);
      rc = getea((007700 & iakku) >> 6, &src, bytfl);
      if(rc) rc = getea(000077 & iakku, &dest, bytfl);
      if(rc) rc = procbinar(opcod, &src, &dest, bytfl);
      done = True;
    }
  }


/* --------------------------------------------------------- BR-ai */
  if((rc) && (!done))
  {
    if((iakku >= 0000400) && ((iakku & 0077400) <= 0003400))
    {
      if(procbr(0177400 & iakku))
      {
        offset = (iakku & ValMaskB);
        if(offset & SigPosB) offset |= SigMaskB;
        offset <<= 1;
        PC = (RegTyp)(((long)PC + offset) & AdrMask);
      }
      done = True;
    }
  }


/* ------------------------------------------------------------ SOB */
  if((rc) && (!done))
  {
    if((iakku & 0177000) == 0077000)
    {
      regno = (AdrTyp)((iakku & 0000700) >> 6);
      if(regno==SP_IND) rc=TestSP(R[regno]-1);
      if(rc) if(0 != (--R[regno]))
      {
        offset = iakku & 0000077;
        offset = -offset;
        offset <<= 1;
        PC = (RegTyp)(((long)PC + offset) & AdrMask);
      }
      done = True;
    }
  }


/* --------------------------------------------------------- MUL & Cø */
  if((rc) && (!done))
  {
    opcod = (iakku & 0177000);
    if((opcod >= 0070000) && (opcod <= 0074000))
    {
      regno = (AdrTyp)((iakku & 0000700) >> 6);
      rc = getea(000077 & iakku, &src, False);

      if(rc) rc = procmul(opcod, regno, &src);
      done = True;
    }
  }


/* ------------------------------------------------------ unarines II */
  if((rc) && (!done))
  {
    switch(iakku & 0177700)
    {
      case 0000300:                                        /* SWAB */
        rc = getea(000077 & iakku, &dest, False);
        if(rc) rc = getdea(&dest, &dakku, False);
        if(rc)
        {
          byte_l = dakku & ValMaskB;
          byte_h = (dakku >> 8) & ValMaskB;
          dakku = ((byte_l << 8) | byte_h);
          rc = putdea(&dest, dakku, False);
        }
        if(rc)
        {
          clrfl(FL_V | FL_C);
          setclrfl(dakku);
        }
        done = True;
        break;

      case 0006700:                                        /* SXT */
        rc = getea(000077 & iakku, &dest, False);
        if(rc)
        {
          if(getfl(FL_N)) dakku = -1;
          else dakku = 0;
          rc = putdea(&dest, dakku, False);
        }
        if(rc)
        {
          clrfl(FL_V);
          setclrfl(dakku);
        }
        done = True;
        break;

      case 0106700:                                        /* MFPS */
        rc = getea(000077 & iakku, &dest, False);
        if(rc)
        {
          dakku = PS;
          rc = putdea(&dest, dakku, False);
        }
        if(rc)
        {
          clrfl(FL_V);
          setclrfl(dakku);
        }
        done = True;
        break;

      case 0106400:                                        /* MTPS */
        rc = getea(000077 & iakku, &dest, False);
        if(rc) rc = getdea(&dest, &dakku, False);
        if(rc) mtps((RegTyp)(dakku /* & RegMaskW */));
        done = True;
        break;

      case 0000100:                                        /* JMP */
        rc = getea(000077 & iakku, &dest, False);
        if(rc && !dest.regflg) PC = (RegTyp)(dest.addr /* & AdrMask */);
        if(!dest.regflg) done = True;
        break;
    }
  }


/* ------------------------------------------------------------- JSR */
  if((rc) && (!done))
  {
    if((iakku & 0177000) == 0004000)
    {
      regno = (AdrTyp)((iakku & 0000700) >> 6);
      rc = getea(0000077 & iakku, &dest, False);
      if(rc) rc = push(/* (WordTyp) */ R[regno]);
      if(rc) R[regno] = PC;
      if(rc && !dest.regflg) PC = (RegTyp)(dest.addr /* & AdrMask */);
      if(!dest.regflg) done = True;
    }
  }


/* ------------------------------------------------------------- RTS */
  if((rc) && (!done))
  {
    if((iakku & 0177770) == 0000200)
    {
      regno = (AdrTyp)(iakku & 0000007);
      PC = R[regno];
      rc = pop(/* (WordTyp *) */ &R[regno]);
      done = True;
    }
  }


/* --------------------------------------------------------- EMT, TRAP */
  if((rc) && (!done))
  {
    switch(iakku & 0177400)
    {
      case 0104000: rc = intrpt(EMT_INTV); done = True; break; /* EMT */
      case 0104400: rc = intrpt(TRAP_INTV); done = True; break; /* TRAP */
    }
  }


/* ------------------------------------------------------ be argumentu */
  if((rc) && (!done))
  {
    switch(iakku)
    {
      case 0000000:               /* HALT */
        EmuSv.n_err("P: Halt", PC-2, __FILE__, __LINE__);
        done = True;
        break;

      case 0000001: EmuSv.status = Wait; done = True; break;     /* WAIT */
      case 0000005: EmuDv.reset(); done = True; break; /* RESET */

      case 0000240:               /* NOP */
      case 0000241:               /* CLC */
      case 0000242:               /* CLV */
      case 0000244:               /* CLZ */
      case 0000250:               /* CLN */
      case 0000257:               /* CCC */
        clrfl(iakku & 017);
        done = True;
        break;

      case 0000261:               /* SEC */
      case 0000262:               /* SEV */
      case 0000264:               /* SEZ */
      case 0000270:               /* SEN */
      case 0000277:               /* SCC */
        setfl(iakku & 017);
        done = True;
        break;

      case 0000003: rc = intrpt(014); done = True; break;  /* BPT */
      case 0000004: rc = intrpt(020); done = True; break;  /* IOT */

      case 0000002:               /* RTI */
      case 0000006:               /* RTT */
        rc = pop(&retw);
        if(rc)
        {
          PC = (RegTyp)retw /* & AdrMask */;
          rc = pop(&retw);
        }
        if(rc)
        {
          intlev--;
          if(intlev < 0) intlev = 0;

          mtps((RegTyp)retw /* & RegMaskW */);
        }
        done = True;
        break;
    }
  }


/* ------------------------ */
  if((rc) && (!done))
  {
    EmuSv.n_err("P: Trap to 10", iakku, __FILE__, __LINE__);
    rc = False;
  }

return(rc);
}
