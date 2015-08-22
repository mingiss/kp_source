/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11s.h, former Kphp11w.h                              */
/* DESCRIPTION:      kphp11 bendra busena ir valdymas                         */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

#ifndef Kphp11s
#define Kphp11s

typedef enum
{
  Monitor,
  Run,
  Wait
} Emu_stat;
           
           
// emuliatoriaus busena ir valdymas 
class EmuSt
{
  short errfl;  /* error nesting flag */
  short prfl;   /* pr3() nesting flag */

public:
  short errfl_gl; // global error flag

  Emu_stat status;
  short trfl;   /* trace flag */
  short intrfl; /* interrupts trace flag */

  short s_err(const char *errstr, const unsigned char *addstr, const char *lpszSourceFile, int iSourceLine); /* klaida, grazina False */
  short n_err(const char *errstr, AdrTyp adr, const char *lpszSourceFile, int iSourceLine);
  short pr3(void); /* vykdomos instrukcijos isvedimas, True - gerai */

  EmuSt(); /* konstruktorius */
};

extern EmuSt EmuSv;

#endif
