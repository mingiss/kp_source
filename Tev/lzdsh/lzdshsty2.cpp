// ==================================================
// lzdshsty2.cpp
// papildomi fiktyvus stiliaus elementai projektams lzdshw*
//


// ==================================== definitions
#include "envir.h"

#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#if OsGr==MSWin
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#endif

#ifdef KP_USE_WXWIDGETS
#include "wx/app.h"
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kpfonts.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "xmlb.h"
#include "xmlu.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"
#include "KpPubDlg.h"
#include "KpRtfDlg.h"
// #include "lvzx.h"
#include "xmlsty.h"
#include "lzdsh.h"
#include "lzdshl.h"
#include "lzdsht.h"


// ----------------------------------
COLORREF KpColorScheme[KpNumOfShadows3]={
/* W2k: */ RGB(214,211,206), // Win98: RGB(191,191,191), // XP: RGB(236,233,216), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas                                 
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas                      
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai                                         
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.                                              
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas                                           
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva                                                   
RGB_Darkblue,  // RGB_Navy,
};


