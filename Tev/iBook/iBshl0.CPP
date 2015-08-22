// ---------------------------------------
// iBshl0.cpp
// iBshl visiškas užblokavimas
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

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#if Compiler != Watcom
using namespace std;
#endif

#if CompilerGr != Mingw
// #error CompilerGr != Mingw
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
#include "kphp11i.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11t.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
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
#include "KpRtfDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBsht.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// -------------------------------------------
iBshDlg::iBshDlg(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers, UC_Modes iEncMode,
      const unsigned char *lpszCaption,
      int iWndDXmin, int iWndDXmax, int iWndDYmin, int iWndDYmax,
      int iWndSoftBorderWdt, int iWndSoftCaptHgt, int iWndHardBorderWdt, int iWndHardCaptHgt,
      int iScrX, int iScrY, int iScrDX, int iScrDY,
      int iResDXenl, int iResDYenl,
      DWORD dwStyle, int iInitWndX, int iInitWndY, int iInitWndDX, int iInitWndDY)
#ifdef IBSH_RES_MODE_XGECKO
#  if CompilerGr == Mingw
: KpGeckoDialog(
#  else
: KpPubDlg(
#  endif
#else
#  ifdef IBSH_RES_MODE_MSHTML
: KpMsHtmlDlg(
#  else
#     ifdef IBSH_RES_MODE_RTF
: KpRtfDlg(
#     else
: KpPubDlg(
#     endif
#  endif
#endif
   pKpFileSys,
   iXmlVers, iEncMode, lpszCaption, iWndDXmin, iWndDXmax, iWndDYmin, iWndDYmax,
   iWndSoftBorderWdt, iWndSoftCaptHgt, iWndHardBorderWdt, iWndHardCaptHgt,
   iScrX, iScrY, iScrDX, iScrDY, iResDXenl, iResDYenl,
   dwStyle, iInitWndX, iInitWndY, iInitWndDX, iInitWndDY)
{}

// HRESULT iBshDlg::QueryInterface(const unsigned char *, void **) { return(E_NOINTERFACE); }

HRESULT iBshDlg::OpenWindow(HINSTANCE, bool){ return(S_OK); }

// HRESULT iBshDlg::CompleteResize(void){ return(S_OK); }

// HRESULT iBshDlg::RedrawWindow(void){ return(S_OK); }

int iBshDlg::DoEdit(void){ return(IDOK); }

HRESULT iBshDlg::Resize(void){ return(S_OK); }

HRESULT iBshDlg::RedrawWindow(void){ return(S_OK); }

// HRESULT KpPubDlg::CloseWindow(void){ return(S_OK); }

// apibrįėžtas xmln0.cpp
// HRESULT XmlNode::TestChildContents(KpChar, KpChar *, bool *){ return(S_OK); }

// ----------------------------------
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
{}

KpMsHtmlDlg::~KpMsHtmlDlg(void){}

HRESULT KpMsHtmlDlg::RedrawWindowLocal(void){ return(S_OK); }

HRESULT KpMsHtmlDlg::DisplayResult(void){ return(S_OK); }
