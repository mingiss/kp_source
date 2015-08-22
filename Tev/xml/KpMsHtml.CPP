// ---------------------------------------
// KpGecko.cpp
// dialogas su tux_gecko langu
//

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"

#if Compiler != Watcom
using namespace std;
#endif

#if CompilerGr!=Mingw
#error CompilerGr!=Mingw
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
#include "tvxml.h"
#include "tvmain.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11t.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpMsHtml.h"
#include "iBshl.h"
#include "xmln.h"
#include "kpstap.h"
#include "iBsh.h"
#include "lzdsh.h"
#include "lzdsho.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

KpMsHtmlDlg::KpMsHtmlDlg(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers, UC_Modes iEncMode,
      const unsigned char *lpszCaption,
      int iWndDXmin, int iWndDXmax, int iWndDYmin, int iWndDYmax,
      int iWndSoftBorderWdt, int iWndSoftCaptHgt, int iWndHardBorderWdt, int iWndHardCaptHgt,
      int iScrX, int iScrY, int iScrDX, int iScrDY,
      int iResDXenl, int iResDYenl,
      DWORD dwStyle, int iInitWndX, int iInitWndY, int iInitWndDX, int iInitWndDY)
: KpPubDlg(pKpFileSys,
   iXmlVers, iEncMode, lpszCaption, iWndDXmin, iWndDXmax, iWndDYmin, iWndDYmax,
   iWndSoftBorderWdt, iWndSoftCaptHgt, iWndHardBorderWdt, iWndHardCaptHgt,
   iScrX, iScrY, iScrDX, iScrDY, iResDXenl, iResDYenl,
   dwStyle, iInitWndX, iInitWndY, iInitWndDX, iInitWndDY)
{
#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   m_ResHtml = NULL;
#  endif
#endif
}

KpMsHtmlDlg::~KpMsHtmlDlg(void)
{
#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   KP_DELETE(m_ResHtml);
#  endif
#endif
}


// ----------------------------------
HRESULT KpMsHtmlDlg::RedrawWindowLocal(void)
{
HRESULT retc = S_OK;

#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   KP_ASSERT(m_ResHtml, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) if(!SetWindowPos(m_ResHtml->hwnd_, HWND_TOP,
      m_iResX, m_iResY, m_iScrCurDX + m_iResDXenl, m_iScrCurDY + m_iResDYenl, 0))
   {
#     ifdef Debug
      KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#     endif
   }

   if(SUCCEEDED(retc)) if(!InvalidateRect(m_ResHtml->hwnd_, 0, TRUE))
   {
#     ifdef Debug
      KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#     endif
   }
#  endif // #  if Compiler != Watcom
#endif // #ifdef IBSH_RES_MODE_MSHTML

return(retc);
}


// --------------------------------------------------
HRESULT KpMsHtmlDlg::DisplayResult(void)
{
HRESULT retc = S_OK;

   KP_ASSERT(m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True)

   if(SUCCEEDED(retc)) retc = m_pKpFileSys->BlockSemaphore();

// ------------------------------- numetam UTF-16 failo kepuræ (du baitus) - tai kad nebûna
#  ifdef IBSH_RES_MODE_MSHTML
#     if Compiler != Watcom
   if(SUCCEEDED(retc)) if(m_ResHtml) m_ResHtml->HTML(/* (const char *) */ m_pResBuf); // m_lpszResultFormatted);
#     endif
#  endif

// ----------------------
   if(SUCCEEDED(retc)) retc = DisplayResultCommon();

   if(m_pKpFileSys != NULL) /* if(SUCCEEDED(retc)) retc = */ m_pKpFileSys->ReleaseSemaphore();

return(retc);
}
