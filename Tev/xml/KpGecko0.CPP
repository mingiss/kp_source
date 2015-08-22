// ---------------------------------------
// KpGecko0.cpp
// tux_gecko visiðkas uþblokavimas
// Èia ne KpGecko projektams
// KpGecko paveldëtiems projektams naudoti iBsh0.cpp
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


#if CompilerGr == Mingw
// --------------------------------------------------
KpGeckoDialog *KpGeckoDialogPtr = NULL; // reikia dël KpGeckoStreamFactory(), neiðeina padaryt nestatiðkai – reiðkia tik vienas KpGecko per aplikacijà


// -------------------------------------
XGeckoInit::XGeckoInit(){}

XGeckoInit::~XGeckoInit(){}

void XGeckoInit::setProtocolIStreamFactory(IInputStream* (*)(char const*)){}


// --------------------------------
XGecko::XGecko(u32_t a_chromeFlags)
{
  this->m_clipboardHooks  = 0;
  this->m_chrome          = 0;
  this->m_chromeFlags     = a_chromeFlags;
}

XGecko::~XGecko(){}

void XGecko::setClipboardFilter(int (*)(IString*, IString const*)){}

long XGecko::onCreate(){ return 0; }

long XGecko::onDestroy0(){ return 0; }

long XGecko::onDestroy1(){ return 0; }

long XGecko::onEvent(XEvent*){ return 0; }

long XGecko::onResize(long, int, int){ return 0; }

void XGecko::loadURI(wchar_t const*){}

long XGecko::wndProc(HWND /* HWND__* */, UINT /* unsigned int */, WPARAM /* unsigned int */, LPARAM /* long */){ return 0; }

long XGecko::onDOMEvent(XGeckoDOMEvent*){ return 0; }

// ----------------------------------------------------------
#ifndef IBSH_RES_MODE_XGECKO
#  if Compiler != Watcom
int clipboardFilter(IString *dst, const IString *src)
{
   dst->setData(src->getData());

return(XGecko::CLIPBOARD_MODIFY);
}
#  endif
#endif

// --------------------------------
XWidget::XWidget(){ this->m_hWnd = 0; }

XWidget::~XWidget(){}

bool XWidget::create(char const*, unsigned int, int, int, int, int, HWND__*){ return(false); }

long XWidget::onKillFocus(HWND__*){ return 0; }

long XWidget::onSetFocus(HWND__*){ return 0; }

long XWidget::onCreate(){ return 0; }

long XWidget::onDestroy0(){ return 0; }

long XWidget::onDestroy1(){ return 0; }

long XWidget::onEvent(XEvent*){ return 0; }

long XWidget::onResize(long, int, int){ return 0; }

long XWidget::wndProc(HWND /* HWND__* */, UINT /* unsigned int */, WPARAM /* unsigned int */, LPARAM /* long */){ return 0; }

void XWidget::setVisible(bool){}


// --------------------------------
KpGeckoDialog::KpGeckoDialog(KpFileSys *pKpFileSys,
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

KpGeckoDialog::~KpGeckoDialog(){}

HRESULT KpGeckoDialog::InitGecko(void)
{
   KpGeckoDialogPtr = this; // TODO: reikia steko, atsimenant visus buvusius

return(S_OK);
}

void KpGeckoDialog::FinitGecko(void){}

HRESULT KpGeckoDialog::OpenWindowLocal(void){ return(S_OK); }

HRESULT KpGeckoDialog::CreateResCtrl(int, int, int, int, HWND){ return(S_OK); }

HRESULT KpGeckoDialog::RedrawWindowLocal(void){ return(S_OK); }

HRESULT KpGeckoDialog::DisplayResult(void)
{
// -------------------------- iðlaisvinam semaforà, kurá turëjo uþstatyti prieð iðkvieèiant m_pKpFileSys->SearchForEntry() (KpGeckoDialog::DisplayResult())
// normaliam XGecko já nuima paskutinis XKpGeckoStream::read()
// taip neveikia
// if(KpGeckoDialogPtr != NULL) if(KpGeckoDialogPtr->m_pKpFileSys != NULL)
//    KpGeckoDialogPtr->m_pKpFileSys->ReleaseSemaphore();

return(S_OK);
}


// --------------------------------
XKpGeckoStream::XKpGeckoStream(FILE *, const unsigned char *, bool){}

XKpGeckoStream::~XKpGeckoStream(void){}

int XKpGeckoStream::read(char *, int){ return(0); }


// --------------------------------
void XGecko::setZoom(float){}

#endif // #if CompilerGr == Mingw

