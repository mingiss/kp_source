/*----------------------------------------------------------------------------*/
/* FILENAME:         Kphp11.cpp                                               */
/* DESCRIPTION:      Pagrindine aplikacija                                    */
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

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

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

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"

#include "kphp11y.h"
#include "kphp11w.h"
#include "kphp11i.h"
#include "kphp11t.h"

#include "tvmain.h"
#include "xmlp.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kphp11y.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11p.h"
#include "kphp11s.h"
#include "kphp11a.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11tt.h"
#include "kphp11rc.h"
#include "kphp11ry.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif


// -----------------------------------------
const unsigned char lpszProdName[] = "kphp11";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;
bool bServiceFl = False;
int KpHp11NumOfExtFun = 0;
KpHp11ExtFun KpHp11ExtFunTab[1] =
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};

KpErrorProcClass KpErrorProc(True, 71);

#ifdef Debug
KpConsole KpTraceWindow;
#endif

// -----------------------------------------
COLORREF KpColorSchemeHp11[KpNumOfShadows3]={
RGB_Black,     // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Green,     // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor,   // URL nuorodos spalva
};


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
DWORD retw;
BOOL retm;
MSG msg;

   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);

#ifdef Debug
   if(SUCCEEDED(retc)) retc = WndPreg(&KpTraceWindow, TYP_Trace, hInstance, NULL, True);
#endif

   if(SUCCEEDED(retc)) retc = EmuWv.SetColorScheme(KpColorSchemeHp11);
   if(SUCCEEDED(retc)) retc = EmuWv.SetCtrlStyle(KPW_CONTROL_STYLE_MONOSPACE);

   if(SUCCEEDED(retc)) 
   {
//    retw = KpHp11Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow, False);
      retc = EmuTv.KpHp11CreateThread(hInstance, True); retw = RET_CODE_WIN(retc);
   }

   if(SUCCEEDED(retc)) do
   {
      retm = GetMessage(&msg,NULL,0,0);
      if(retm < 0)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(retm && SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

// unsigned char str_buf[100]; sprintf((char *)str_buf, "%x     %x %x", msg.message, msg.wParam, msg.lParam); KP_TRACE(str_buf);

      }

   } while((msg.message != WM_QUIT) && SUCCEEDED(retc));

   EmuYv.memsav((unsigned char *)"kphp11.bin"); // turëtø destruktorius áraðyt

   if(SUCCEEDED(retc)) retc = KpFinitWindows();

   if(FAILED(retc)) retw = RET_CODE_WIN(retc);

return(retw);
}
