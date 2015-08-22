// ---------------------------
// StartDemo.cpp
// .jar ir Flash failø rodymas per XGecko
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>
#include <string>

#include <b64/encode.h>
#include <b64/decode.h>

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

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
#include "kpmsg.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#if CompilerGr == Mingw
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#endif


// -----------------------------------------
const unsigned char lpszProdName[] = "StartDemo";

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ----------------------------------------------------------
long XKpGecko::onDOMEvent(XGeckoDOMEvent *event)
{
long retl = 0;

KP_TRACE_("XKpGecko::onDOMEvent():   %ls", event->word);

// Jei ivyki apdorojome, graziname 1
// Priesingu atveju - 0
// return 1;
return(retl);
}


// ----------------------------------------------------------
int clipboardFilter(IString *dst, const IString *src)
{
   dst->setData(src->getData());

return(XGecko::CLIPBOARD_MODIFY);
}


// ---------------------------------------------------- main
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
static unsigned char cmd_line[KP_MAX_FNAME_LEN + 1];
MSG msg;
int retp;
// KpGeckoDialog *dlg_ptr = NULL;
bool endfl = False;

   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);

   if(SUCCEEDED(retc))
   {
//    strcpy(cmd_line, "F:/kp/source/Tev/xml/wiris_sample/es/lb-p01-pythagoras.html");
      strcpy(cmd_line, "F:/kp/source/Tev/lzdsh/doc/WinLED_instrukcija.xgecko.htm");
      strcpy(cmd_line, "StartDemo.htm");
      retc = StartCmdProcess(cmd_line, (const unsigned char *)"F:/kp/source/Tev/lzdsh/doc", // "F:/kp/source/Tev/xml/wiris_sample/es", // 
         NULL, NULL, True, SW_SHOWNORMAL,
         SW_SHOWMINIMIZED, True, (const unsigned char *)"", True); // , &dlg_ptr);
   }

// ------------------------------ praneðimø ciklas
   if(SUCCEEDED(retc)) do
   {
      KP_ASSERT(GetMessage(&msg, NULL, 0, 0) >= 0, KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         retp = LOWORD(msg.wParam);
      }

// ------------------------------------------------- pagrindinis praneðimø apdorojimas
      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl = True;
         break;

      case WM_CLOSE:
         endfl = True;
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK: /* endfl = True; */ break;
         case IDCANCEL: endfl = True; break;
         }
         break;

      default: DispatchMessage(&msg); break;

      }  // if(SUCCEEDED(retc)) switch(msg.message)

   } while((!endfl) && SUCCEEDED(retc));


KpMsgOutF("Jau");

   if(KpGeckoDialogPtr /* dlg_ptr */ != NULL)
   {
      KpGeckoDialogPtr /* dlg_ptr */ ->FinitGecko();
      KP_DELETE(KpGeckoDialogPtr); // dlg_ptr;
      KpPubDlgPtr /* KpGeckoDialogPtr */ /* dlg_ptr */ = NULL;
   }
   
   KP_DELETE(KpFileSysPtr);

   if(SUCCEEDED(retc)) retc = KpFinitWindows();

return(RET_CODE_WIN(retc));
}
