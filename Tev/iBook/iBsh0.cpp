// ---------------------------
// iBsh0.cpp
// el. knygø perþiûros programa
// standartinës tux_gecko project specific callback funkcijø realizacijos
// Èia KpGecko paveldëtiems projektams
// Ne KpGecko projektams naudoti KpGecko0.cpp
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <fstream>
#if Compiler != Watcom
#include <sstream>
#endif
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

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kpmsg.h"
#include "kperr.h"
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
#include "tvmain.h"
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
#include "htmt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpRtfDlg.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "xmlsty.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBsht.h"
#include "iBshr.h"
// #include "iBsht.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// ----------------------------------
#ifdef IBSH_RES_MODE_XGECKO
#  if Compiler != Watcom
long XKpGecko::onDOMEvent(XGeckoDOMEvent *event)
{
long retl = 0;

KP_TRACE_("XKpGecko::onDOMEvent():   %ls", event->word);

// Jei ivyki apdorojome, graziname 1
// Priesingu atveju - 0
// return 1;
return(retl);
}
#  endif
#endif


// ----------------------------------
#ifdef IBSH_RES_MODE_XGECKO
#  if Compiler != Watcom
int clipboardFilter(IString *dst, const IString *src)
{
HRESULT retc=S_OK;

   if(((dst == NULL) /* || (src == NULL) */) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// Parodom koks buvo orginalus tekstas
// DEMESIO: tekstas kartais buna ne NULL-TERMINATED
KP_TRACE_("KOPIJUOJAMA: %d\t%.*ls\n", src->length(), src->getData());

// Nurodom nauja reiksme.
// dst reiksme reikia nustatyti tik tuomet, jei yra grazinama CLIPBOARD_MODIFY
// dst->setData(L"HEHE");
// if(SUCCEEDED(retc)) dst->setData(L"");
   if(SUCCEEDED(retc)) dst->setData(src->getData());

return(XGecko::CLIPBOARD_MODIFY);
}
#  endif
#endif
