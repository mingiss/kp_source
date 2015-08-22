/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11p.h                                                */
/* DESCRIPTION:      Kphp11:  Procesorius                                     */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

// #define KPHP11_SPEED_CALIBRATED

#ifndef Kphp11p
#define Kphp11p

#define NumOfReg 9
#define R reg
#define SP_IND 6
#define PC_IND 7
#define PS_IND 8
#define SP (reg[SP_IND])
#define PC (reg[PC_IND])
#define PS (reg[PS_IND])

#define EMT_INTV  030
#define TRAP_INTV 034
           
#define MIN_SP 0400 // apatine steko riba
          
#define FL_P  0340 /* 0200 */
#define FL_T   020
#define FL_N   010
#define FL_Z    04
#define FL_V    02
#define FL_C    01
#define FL_PS (FL_P | FL_T | FL_N | FL_Z | FL_V | FL_C)

#define setfl(fl) (PS |= (fl))  /* PS veliaveliu istatymas */
#define clrfl(fl) (PS &= ~(fl)) /* PS veliaveliu istrynimas */
#define getfl(fl) (PS & (fl))   /* PS veliaveliu skaitymas */

typedef unsigned short /* int */ RegTyp;

class FulAdrTyp
{
public:
  AdrTyp addr;
  short regflg;
};


class EmuPt
{
  RegTyp reg[NumOfReg];

  AdrTyp waitint;           /* laukiantis eiles trukis */
  RegTyp waitprio;

#ifdef KPHP11_SPEED_CALIBRATED
   long m_lOps; // operacij÷ per sekund“
   long m_lCurInsCnt; // operacij÷ skaitiklis
   long m_lPrevTime;
   long m_iMsecsDelay; // kiek msec uÿlaikyti i’ viso per sekund“
   long m_lInterv; // kas kelias operacijas daryti pauzes
#endif  

  short TestSP(RegTyp iNewVal); // tikrina steka

  void setclrfl(long val);  /* FL_N ir FL_Z uzpildymas */
  long dadd(long arg1, long arg2, short bytfl, short subfl);
/* sudetis / atimtis (arg1 - arg2), pasirupinant perpildymu veliavelemis */
  long dadd(long arg1, long arg2, short bytfl);
  short getea(unsigned int ea, FulAdrTyp *addrp, short bytfl);
                            /* efective address suradimas; True - gerai */
  short getdea(FulAdrTyp *addrp, long *res, short bytfl);
                            /* skaitymas pagal adresa; True - gerai */
  short putdea(FulAdrTyp *addrp, long val, short bytfl);
                            /* rasymas adresu; True - gerai */
  short push(Word16Typ val);  /* i steka */
  short pop(Word16Typ *valp); /* is steko */

  short procunar(unsigned int opcod, FulAdrTyp *dest, short bytfl);
                            /* unariniu instrukciju vykdymas; True - gerai */
  short procbinar(unsigned int opcod, FulAdrTyp *srcp, FulAdrTyp *destp, short bytfl);
                            /* binariniu instrukciju vykdymas; True - gerai */
  short procmul(unsigned int opcod, AdrTyp regno, FulAdrTyp *srcp); /* MUL & C¯, True - gerai */
  short procbr(unsigned int opcod); /* BR-u analizavimas: True - salyga tenkinama */

  void mtps(RegTyp val);    /* rasymas i PSW */

public:

  int intlev;               /* trukio gylis */

                            /* registru skaitymas/rasymas; True - gerai */
  short getrw(AdrTyp regno, RegTyp *val);
  short getrb(AdrTyp regno, ByteTyp *val);
  short putrw(AdrTyp regno, RegTyp val);
  short putrb(AdrTyp regno, ByteTyp val);

#ifdef KPHP11_SPEED_CALIBRATED
   void DoDelay(void);
#endif  

  short iexe(void);        /* vienos instrukcijos ivykdymas; True - gerai */

  short intrpt(AdrTyp intvec); /* trukis; True - gerai */

  EmuPt();                  /* konstruktorius */
};

extern EmuPt EmuPv;

#endif
