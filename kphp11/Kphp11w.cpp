/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11w.cpp, former Kphp11e.cpp                          */
/* DESCRIPTION:      Kphp11: Emuliatoriaus langas                             */
/* LANGUAGE:         C++                                                      */
/* DESTINATION:      MSWindows                                                */
/* SYSTEM_INTERFACE: MSWindows                                                */
/* USER_INTERFACE:   Graph                                                    */
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
#include "kphp11w.h"


/*---------------------------------------------------- var */
EmuWt EmuWv;
// WndP  EmuWp((WndC *)&EmuWv);

/* ----------------------------------------- konstruktorius */
EmuWt::EmuWt()
  : KpConsole()
{
/*  einit(); */

   m_iKpCtrlStyle = KPW_CONTROL_STYLE_MONOSPACE;
}


/* ------------------------------------------ destruktorius */
EmuWt::~EmuWt()
//  : ~WndT()
{
   KpConsoleDestructor();
}


/*--------------------------------------------------- init */
void EmuWt::einit(void)
{
// wInitEasyWin("kphp11", 0, 0, "Kphp11");

  wbcolor(KpGreen, KpBlack, KpBlack);
  wcrsor(True);
}
