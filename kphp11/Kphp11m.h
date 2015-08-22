/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11m.h                                                */
/* DESCRIPTION:      Kphp11: Monitorius                                       */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

#ifndef Kphp11m
#define Kphp11m

#define KP_HP11_TOGGLE_CONSOLE   (CtrlFl & 'W')
#define KP_HP11_BREAK            (CtrlFl & 'B')
#define KP_HP11_TOGGLE_TRACE     (CtrlFl & 'T')
#define KP_HP11_TOGGLE_TR_INT    (CtrlFl & 'E')
      
// ---------------------------
class EmuMt
{
  unsigned long inpval;    /* ivedama reiksme */
  AdrTyp address;          /* einamasis adresas */
  short bytflg;            /* ar operacijos baitais? */
  short regrdfl;           /* skaitymo is registro pozymis */
  short regwrfl;           /* rasymo i registra pozymis */
  short inpfl;             /* ar buvo paspaustas skaitmuo - ar reikia */
                           /*   keisti adresa lasteliu atidarymo komandose */

  void pradr(void);        /* adreso isvedimas */
  void printv(int posnum); /* inpval isvedimas */
  short putval(void);      /* reiksmes irasymas i atminti; True - gerai */
  short getval(void);      /* reiksmes skaitymas is atminties; True - gerai */

public:
  void prompt(void);       /* prompt isvedimas, ivedimo is klav. nuresetinimas */

  void minit(void);        /* init */
  void process(unsigned char ch); /* ivedimo is klav. apdorojimas */

  EmuMt();                 /* konstruktorius */
  };

extern EmuMt EmuMv;

#endif
