// ---------------------------
// iBsh1.cpp
// bendri MIKO_VIEW grupës produktø dalykai – ArkSh, StartGrp, RegAtm
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#ifdef IBSH_RES_MODE_MSHTML
#if CompilerGr==Mingw
#include "HTMLWindow.h"
#endif
#endif

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "res_com.h"
#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpctype.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "tvmain.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#ifdef IBSH_RES_MODE_XGECKO
#  if CompilerGr==Mingw
#include "KpGecko.h"
#  endif
#endif
#include "KpRtfDlg.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "xmlsty.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBshr.h"
#include "iBsht.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// -----------------------------------------
COLORREF KpColorSchemeLocal[KpNumOfShadows3]={
IBSH_TOOL_BCOL, // RGB(240, 240, 240), // RGB_Lightgray, // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Gray,      // RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
IBSH_TOOL_BCOL, // RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,  // KpLinkColor,
};
