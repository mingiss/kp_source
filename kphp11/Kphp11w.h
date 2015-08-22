/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11w.h, former Kphp11e.h                              */
/* DESCRIPTION:      Win32 langas                                             */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      MSWindows                                                */
/* SYSTEM_INTERFACE: MSWindows                                                */
/* USER_INTERFACE:   Graph                                                    */
/* ARCHIVE_VERSION:  LATEST                                                   */
/* ARCHIVE_COMMENT:                                                           */
/*----------------------------------------------------------------------------*/
 
#ifndef Kphp11w
#define Kphp11w

// #define D1_HGT 3
#define D1_HGT 15

class EmuWt : public KpConsole
{
public:
   void einit(void); /* init */

   EmuWt();                  /* konstruktorius */
   ~EmuWt();                 /* destruktorius */
};

extern EmuWt EmuWv;
// extern WndT  EmuWp;

#endif
