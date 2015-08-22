/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11mz.h                                               */
/* DESCRIPTION:      Kphp11:  Diskas MZ                                       */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

#ifndef Kphp11mz
#define Kphp11mz

#define MZ_ien   0100

#define MZ_CSR       0 

#define MZ_MaxPort   4

#define MZ_DEF_CSR 0177000
#define MZ_DEF_INT 0360

class EmuD_MZt : public EmuD_comt
{            
  Word16Typ   ports[MZ_MaxPort]; /* registrai */

public:

  void reset(void);      /* inicializavimas (trukiu uzdraudimas) */

                          /* skaitymas/rasymas; True - gerai */
  short getw(AdrTyp adress, Word16Typ *valp);
  short getb(AdrTyp adress, ByteTyp *valp);
  short putw(AdrTyp adress, Word16Typ val);
  short putb(AdrTyp adress, ByteTyp val);

                          /* Win32 puses skaitymas/rasymas; True - gerai */
  short dputw(int portn, Word16Typ val);

  short dintrpt(int portn); // portn - CSR porto numeris 0..portnum

  EmuD_MZt(AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd, EmuD_TT_comt *tta);
                          /* konstruktorius, porta - CSR adresas,
                             intv - trukio vekt. adr., devn - kisenes nr.,
                             filn - susieto failo vardas; wnd - terminalo isvedimo langas (NULL),
                             tta - terminalo tipo klases adr. (NULL) */
};

#endif
