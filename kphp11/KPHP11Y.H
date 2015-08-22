/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11y.h                                                */
/* DESCRIPTION:      Kphp11:  Atmintis                                        */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

#ifndef Kphp11y
#define Kphp11y

#define ValMaskB           0377   /* kauke baitui */
#define SigPosB            0200   /* zenklo pozicija baituose */
#define SigMaskB        (~((long)ValMaskB)) /* zenklo ispletimas is baito i zodi */
#define ValMaskW        0177777   /* kauke zodziui */
#define SigPosW         0100000   /* zenklo pozicija zodziuose */
#define SigMaskW        (~((long)ValMaskW)) /* zenklo ispletimas is zodzio */
#define ValMaskL        037777777777L /* kauke ilgam zodziui */
#define SigPosL         020000000000L /* zenklo pozicija ilguose zodziuose */
#define SigMaskL        (~((long)ValMaskL)) /* zenklo ispletimas is ilgo zodzio */
#define AdrMask         0177777   /* kauke adresams */
#define RegMaskW        0177777   /* kauke registrams */
#define MaxMask         0177777   /* max. monitoriuje ivedamu reiksmiu kauke */

#define MaxValPosNum         12   /* max. spausdinamu reiksmiu posiciju sk. */

#define ValPosNumW            6   /* spausdinamu reiksmiu posiciju sk. */
#define ValPosNumB            3

#define UndefAdr        0177776
#define MemSize         0160000   /* atminties dydis baitais */

typedef unsigned int AdrTyp;
// typedef unsigned short Adr16Typ;
// typedef unsigned int WordTyp;
typedef unsigned short Word16Typ;
typedef unsigned char ByteTyp;

#if FALSE
#define cMemBank MemBankObj.m_sArr
typedef union
{
   long m_lAlign;
   Word16Typ /* ByteTyp */ m_sArr[MemSize/2];
} MemBankType;

extern MemBankType MemBankObj;
#else
#define cMemBank MemBankObj
typedef Word16Typ /* ByteTyp */ /* [MemSize/2] */ MemBankType;
extern MemBankType MemBankObj[MemSize/2];
#endif


class EmuYt
{
   ByteTyp *bank;

public:

   AdrTyp mem_top;              /* atminties pabaigos adresas */
                                /* skaitymas/rasymas; True - gerai */
   short getw(AdrTyp adress, Word16Typ *valp);
   short getb(AdrTyp adress, ByteTyp *valp);
   short putw(AdrTyp adress, Word16Typ val);
   short putb(AdrTyp adress, ByteTyp val);

   short loadsav(unsigned char *fname); /* .sav failo skaitymas, True - gerai */
   short memsav(unsigned char *fname); /* atminties turinio issaugojimas .sav formatu, True - gerai */

   EmuYt(void);                     /* konstruktorius */
   ~EmuYt(void);
};

extern EmuYt EmuYv;

#endif
