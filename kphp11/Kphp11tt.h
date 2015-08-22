/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11tt.h                                               */
/* DESCRIPTION:      Kphp11:  Terminalas                                      */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

#ifndef Kphp11tt
#define Kphp11tt

#define TT_ien   0100
#define TT_ready 0200

#define TT_in_CSR   0 
#define TT_in_DATA  1
#define TT_out_CSR  2
#define TT_out_DATA 3
#define TT_MaxPort  4

#define TT_DEF_CSR 0177560
#define TT_DEF_INT 060

class EmuD_TTt : public EmuD_comt
{            
   Word16Typ   ports[TT_MaxPort]; /* registrai */

   KbChar /* unsigned int */ ttgetchar(void); /* vidinis simbolio ivedimas, Nul - nera ko ivesti */
   KbChar /* unsigned int */ ttputchar(KbChar /* unsigned */ chr); /* vidinis simbolio isvedimas */

public:

   EmuD_TTt(AdrTyp porta, AdrTyp intv, int devn, unsigned char *filn, KpConsole *wnd, EmuD_TT_comt *tta);
                          /* konstruktorius, porta - CSR adresas,
                             intv - trukio vekt. adr., devn - kisenes nr.,
                             filn - susieto failo vardas (NULL); wnd - terminalo isvedimo langas,
                             tta - terminalo tipo klases adr. */
   ~EmuD_TTt();

   void reset(void);      /* inicializavimas (trukiu uzdraudimas) */

                          /* skaitymas/rasymas; True - gerai */
   short getw(AdrTyp adress, Word16Typ *valp);
   short getb(AdrTyp adress, ByteTyp *valp);
   short putw(AdrTyp adress, Word16Typ val);
   short putb(AdrTyp adress, ByteTyp val);

                          /* Win32 puses skaitymas/rasymas; True - gerai */
   short dputw(int portn, Word16Typ val);

   short dintrpt(int portn); // portn - CSR porto numeris 0..portnum
};

#endif
