/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp1152.h                                               */
/* DESCRIPTION:      Kphp11:  Terminalas VT52                                 */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      *                                                        */
/* SYSTEM_INTERFACE: *                                                        */
/* USER_INTERFACE:   *                                                        */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/

#ifndef Kphp1152
#define Kphp1152


typedef enum
{
  VT52_CHAR,
  VT52_ESC,
  VT52_LOC1,
  VT52_LOC2

} StatVT52;


class EmuD_TT_vt52t : public EmuD_TT_comt
{
  StatVT52 status; /* displejaus busena */
  unsigned int valsav; /* isvedimo komandos tarpiniu reiksmiu saugojimui */

public:
   /* simbolio isvedimas, wnd - i kuri langa isvesti */
  KbChar /* unsigned int */ tputchar(KbChar /* unsigned int */ chr, KpConsole *wnd);

  short ttokbbuf(KbChar /* unsigned int */ chr); /* simboli i klav. eile, False - nera vietos */

  EmuD_TT_vt52t(); /* konstruktorius */
};


#endif
