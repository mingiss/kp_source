// ---------------------------------------
// ShowHtm.cpp
// bandymas daryti StartGrp meniu, dabar naudojam bendrà iBshl
//

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <fstream>
#include <windows.h>
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
#include "res_com.h"
#include "tvxml.h"
#include "tvmain.h"
#include "kpcapp.h"
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
#include "xml8.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
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
#include "kpstap.h"
#include "KpFileSys.h"
#include "iBsh.h"
#include "iBshl.h"
#include "lzdsh.h"
#include "lzdsho.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// ----------------------------------
ShowHtmFile::ShowHtmFile(const unsigned char *lpszInFileName, int iInitCtrlDX, int iInitCtrlDY)
{
   m_lpszFName[0] = Nul;
   m_lpInFileObj = NULL;

   m_iCtrlDX = iInitCtrlDX;
   m_iCtrlDY = iInitCtrlDY;

   KP_ASSERTC(lpszInFileName != null, E_INVALIDARG, null, True);
   KP_ASSERTC(strlen(lpszInFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(m_lhOpenResult)) strcpy(m_lpszFName, lpszInFileName);

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = OpenFiles(); // failas paprastas iðorinis, kaþkaip per CreateGeckoStream() padaryt, nereikia viso failo á buferá skaityt
}


HRESULT ShowHtmFile::OpenFiles
(
   const unsigned char *lpszInFileName,
   XmlVersions iVersion,
   HRESULT CreateLowLevelObj
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   )
)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc = BlockSemaphore();

   if(SUCCEEDED(retc)) if(lpszInFileName != null)
   {
      KP_ASSERT(strlen(lpszInFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcpy(m_lpszFName, lpszInFileName);
   }
    
   KP_ASSERT(m_lpszFName[0] != Nul, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(m_lpInFileObj == NULL, KP_E_SYSTEM_ERROR, null, True); // failas jau atidarytas

   if(SUCCEEDED(retc)) m_lpInFileObj = fopen((const char *)m_lpszFName, "r");

   if(SUCCEEDED(retc)) retc = SearchForEntry();

   /* if(SUCCEEDED(retc)) retc = */ ReleaseSemaphore();

return(retc);
}


HRESULT ShowHtmFile::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc = BlockSemaphore();

   KP_ASSERT((!bCheckFileExist) || (m_lpszFName[0] == Nul), KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT((!bCheckFileExist) || (m_lpInFileObj != NULL), KP_E_NO_FILE, null, True); // failas dar neatidarytas

   if((m_lpInFileObj != NULL) && SUCCEEDED(retc)) fclose(m_lpInFileObj);

   m_lpInFileObj = NULL;
   m_lpszFName[0] = Nul;

   /* if(SUCCEEDED(retc)) retc = */ ReleaseSemaphore();

return(retc);
}


HRESULT ShowHtmFile::SearchForEntry(void)
{
HRESULT retc = S_OK;

   if(SUCCEEDED(retc)) retc = BlockSemaphore();

// TODO: kažkaip vien nuo SearchForEntry() nenusiresetina XKpGeckoStream::read() pointeris
// m_iResultPtr = 0;

   KP_ASSERT(m_lpInFileObj != NULL, KP_E_NO_FILE, null, True);

   KP_ASSERT(m_pResBuf != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
// TODO: naudot ReadFileContents(), dinaminio ilgio m_pResBuf
      fseek(m_lpInFileObj, 0, SEEK_SET);
size_t read = 0;
      read = fread(m_pResBuf, sizeof(m_pResBuf[0]), KPPUBDLG_RESULT_BUF_LEN, m_lpInFileObj);
      KP_ASSERT((read >= 0) && (read < KPPUBDLG_RESULT_BUF_LEN), KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) m_pResBuf[read] = Nul; // m_pResBuf[KPPUBDLG_RESULT_BUF_LEN] = Nul;
      KP_ASSERT(!ferror(m_lpInFileObj), KP_E_FERROR, null, True);
   }

// suparsinam HTML buferá
   if(SUCCEEDED(retc)) retc = ParseResBufHtml();

// iðsitraukiam lango matmenis
   if(SUCCEEDED(retc)) retc = ExtractHtmWndSize(m_pCurEntry);

   /* if(SUCCEEDED(retc)) retc = */ ReleaseSemaphore();

return(retc);
}



ShowHtmFile::~ShowHtmFile(void)
{
   CloseFiles(False);
}


extern HRESULT ShowHtmXGecko(const unsigned char *lpszHtmFName, // KpGeckoDialog **ppDlgPtr,
   HWND hParent, int iGeckoX, int iGeckoY, int iGeckoDX, int iGeckoDY,
   const unsigned char *lpszWndName, LPSTR lpszIcon)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
DWORD wnd_style;
int wnd_x = 0;
int wnd_y = 0;
int wnd_dx = KP_SHOWXGECKO_DX;
int wnd_dy = KP_SHOWXGECKO_DY;
int wnd_dx_max = 1600;
int wnd_dy_max = 1200;
HWND gecko_wnd = NULL;
HDC hdc = NULL;

// KP_ASSERT(ppDlgPtr != NULL, E_INVALIDARG, null, True);
// KP_ASSERT(KpGeckoDialogPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

// ------------------------
// PutLogMessage_("ShowHtmXGecko() 1: %d %d", pShowHtmFile->m_iCtrlDX, pShowHtmFile->m_iCtrlDY);
   KP_NEW(KpFileSysPtr /* pShowHtmFile */, ShowHtmFile(lpszHtmFName, iGeckoDX, iGeckoDY));
// PutLogMessage_("ShowHtmXGecko() 2: %d %d", pShowHtmFile->m_iCtrlDX, pShowHtmFile->m_iCtrlDY);
   KP_ASSERT(pShowHtmFile != NULL, KP_E_OUTOFMEM, null, True);
   if(SUCCEEDED(retc)) retc = pShowHtmFile->GetOpenResult();

   if(SUCCEEDED(retc))
   {
      if(KpGeckoDialogPtr != NULL)
      {
// nereikia – èia uþtenka objekto su þemiausiu interfeisu KpPubDlgPtr
//       retc = KpGeckoDialogPtr->QueryInterface((const unsigned char *)"KpGeckoDialog");
//       if(FAILED(retc)) KP_ERROR(retc, null);
PutLogMessage_("ShowHtmXGecko() 1: %d %d %d %d", KpGeckoDialogPtr->m_iWndCurX, KpGeckoDialogPtr->m_iWndCurY, KpGeckoDialogPtr->m_iWndCurDX, KpGeckoDialogPtr->m_iWndCurDY);
         KpGeckoDialogPtr->m_iWndCurDXprec = pShowHtmFile->m_iCtrlDX + 2 * (IBSH_WND_BORDER_WDT + IBSH_WND_SOFT_BORDER_WDT);
         KpGeckoDialogPtr->m_iWndCurDYprec = pShowHtmFile->m_iCtrlDY + 2 * (IBSH_WND_BORDER_WDT + IBSH_WND_SOFT_BORDER_WDT) + IBSH_WND_CAPTION_HGT + IBSH_WND_SOFT_CAPTION_HGT;

         KpGeckoDialogPtr->Resize();
PutLogMessage_("ShowHtmXGecko() 2: %d %d %d %d", KpGeckoDialogPtr->m_iWndCurX, KpGeckoDialogPtr->m_iWndCurY, KpGeckoDialogPtr->m_iWndCurDX, KpGeckoDialogPtr->m_iWndCurDY);
      }
      else PutLogMessage_("ShowHtmXGecko(): KpGeckoDialogPtr == NULL");
   }


// -----------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "KPSHOWXGECKO",
      wcx.lpfnWndProc   = (WNDPROC)ShowHtmXGeckoDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(hKpInstance, /* MAKEINTRESOURCE */ (lpszIcon));
      wcx.hIconSm       = LoadIcon(hKpInstance, /* MAKEINTRESOURCE */ (lpszIcon));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));

      if(!RegisterClassEx(&wcx))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      if(hParent == HWND_DESKTOP)
      {
         hdc = GetDC(hParent);
         KP_ASSERT(hdc != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         wnd_dx_max = GetDeviceCaps(hdc, HORZRES);
         wnd_dy_max = GetDeviceCaps(hdc, VERTRES);

         wnd_dx = pShowHtmFile->m_iCtrlDX; // KP_SHOWXGECKO_DX; // KpGeckoDialogPtr->m_iWndDX;
         wnd_dy = pShowHtmFile->m_iCtrlDY; // KP_SHOWXGECKO_DY; // KpGeckoDialogPtr->m_iWndDY;

         if(SUCCEEDED(retc))
         {
            wnd_x = (wnd_dx_max - wnd_dx) / 2;
            wnd_y = (wnd_dy_max - wnd_dy) / 2;
         }
      }
      else
      {
         wnd_x = iGeckoX;
         wnd_y = iGeckoY;

         wnd_dx_max = wnd_dx = pShowHtmFile->m_iCtrlDX; // iGeckoDX;
         wnd_dy_max = wnd_dy = pShowHtmFile->m_iCtrlDY; // iGeckoDY;
      }
   }

   if(SUCCEEDED(retc)) wnd_style = ((hParent == HWND_DESKTOP)?WS_POPUP /* WS_POPUPWINDOW */ : WS_CHILD) | WS_VISIBLE | WS_BORDER; // |WS_THICKFRAME|WS_CAPTION|WS_POPUP

   if(SUCCEEDED(retc))
   {
// TODO: dubliuojasi iBshDlg ir KpGeckoDialog, kaþkaip apjungt
      if(KpGeckoDialogPtr == NULL)
      {
         KP_NEW(KpPubDlgPtr /* KpGeckoDialogPtr */ /* *ppDlgPtr */, KpGeckoDialog(XM_VERS_XHTML /* XM_VERS_HTML401_TRANS */,
                  UC_PlainText, // UC_UTF_8, // XM_NO_VERS, UC_No_Mode // !!!! TODO: pabandyt atpaþint dinamiðkai
            80, wnd_dx_max, 60, wnd_dy_max,
            0 /* iWndMargin */, 0 /* iWndSoftCaptHgt */,
            0, 0, 0, 0, 0, 0,
            wnd_style, 0, 0, wnd_dx, wnd_dy));
      }
      else
      {
         retc = KpGeckoDialogPtr->QueryInterface((const unsigned char *)"KpGeckoDialog");
         if(FAILED(retc)) KP_ERROR(retc, null);

         if(SUCCEEDED(retc))
         {
            KpGeckoDialogPtr->m_iXmlVers = XM_VERS_XHTML; // XM_VERS_HTML401_TRANS;
            KpGeckoDialogPtr->m_iEncMode = UC_PlainText;

            KpGeckoDialogPtr->m_iWndDXmin = 80;
            KpGeckoDialogPtr->m_iWndCurResDX = KpGeckoDialogPtr->m_iWndDXmax = wnd_dx_max;
            KpGeckoDialogPtr->m_iWndDYmin = 60;
            KpGeckoDialogPtr->m_iWndCurResDY = KpGeckoDialogPtr->m_iWndDYmax = wnd_dy_max;
PutLogMessage_("ShowHtmXGecko(): %d %d", KpGeckoDialogPtr->m_iWndCurResDX, KpGeckoDialogPtr->m_iWndCurResDY);

            KpGeckoDialogPtr->m_iWndMargin = 0;
            KpGeckoDialogPtr->m_iWndSoftCaptHgt = 0;

            KpGeckoDialogPtr->m_iWndCurResX = KpGeckoDialogPtr->m_iWndResX = 0;
            KpGeckoDialogPtr->m_iWndCurResY = KpGeckoDialogPtr->m_iWndResY = 0;

            KpGeckoDialogPtr->m_iResDXenl = 0;
            KpGeckoDialogPtr->m_iResDYenl = 0;
            KpGeckoDialogPtr->m_iResDXcor = 0;
            KpGeckoDialogPtr->m_iResDYcor = 0;
         }
      }
   }

// !!! be ðito kaþkaip vëliau nusimuða controlo pradþios koordinatës
   if((hParent != HWND_DESKTOP) && SUCCEEDED(retc)) KpGeckoDialogPtr->m_iWndCurX = KpGeckoDialogPtr->m_iWndCurY = 0;

   if(SUCCEEDED(retc)) KpGeckoDialogPtr->m_hParent = hParent;

   if(SUCCEEDED(retc)) retc = KpGeckoDialogPtr /* (*ppDlgPtr) */ ->InitGecko();

#if FALSE
// --------------------------------
   if(SUCCEEDED(retc))
   {
      gecko_wnd = CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPSHOWXGECKO",
         (const char *)lpszWndName, // LPCTSTR lpWindowName, // pointer to window name
         wnd_style,                 // DWORD dwStyle,        // window style
         wnd_x, // CW_USEDEFAULT,   // int x,              // horizontal position of window
         wnd_y, // CW_USEDEFAULT,   // int y,              // vertical position of window
         KpGeckoDialogPtr->m_iWndDX, // wnd_dx,                    // int nWidth,           // window width
         KpGeckoDialogPtr->m_iWndDY, // wnd_dy,                    // int nHeight,          // window height
         hParent, // HWND_DESKTOP,  // HWND hWndParent,   // handle to parent or owner window
         0,                         // HMENU hMenu,         // handle to menu, or child-window identifier
         hKpInstance,
         NULL  // *ppDlgPtr                  // LPVOID lpParam        // pointer to window-creation data
      );

      KP_ASSERT(gecko_wnd != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(SUCCEEDED(retc)) KpSleep(500);
#endif

// --------------------------------
   if(SUCCEEDED(retc))
   {
      gecko_wnd = CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPSHOWXGECKO",
         (const char *)lpszWndName, // LPCTSTR lpWindowName, // pointer to window name
         wnd_style,                 // DWORD dwStyle,        // window style
         wnd_x, // CW_USEDEFAULT,   // int x,              // horizontal position of window
         wnd_y, // CW_USEDEFAULT,   // int y,              // vertical position of window
         KpGeckoDialogPtr->m_iWndDX, // wnd_dx,                    // int nWidth,           // window width
         KpGeckoDialogPtr->m_iWndDY, // wnd_dy,                    // int nHeight,          // window height
         hParent, // HWND_DESKTOP,  // HWND hWndParent,   // handle to parent or owner window
         0,                         // HMENU hMenu,         // handle to menu, or child-window identifier
         hKpInstance,
         NULL  // *ppDlgPtr                  // LPVOID lpParam        // pointer to window-creation data
      );

      KP_ASSERT(gecko_wnd != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(SUCCEEDED(retc)) KpSleep(500);

// ------------------------
   if(SUCCEEDED(retc)) KpGeckoDialogPtr /* (*ppDlgPtr) */ ->Load();

// --------------------------------
   KP_ASSERT(KpGeckoDialogPtr /* (*ppDlgPtr) */ ->m_pResCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);
   if(SUCCEEDED(retc)) KpGeckoDialogPtr /* (*ppDlgPtr) */ ->m_pResCtrl->setVisible(true);


return(retc);
}


BOOL CALLBACK ShowHtmXGeckoDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
int retp = 0;
bool endfl = False;
UINT msg = 0;
BOOL retb = FALSE;
KpGeckoDialog *dlg_ptr = NULL;
// CREATESTRUCT *csp = NULL;

   msg = uMsg;
   retp = LOWORD(wParam);
   endfl = False;

// ------------------------------------
   if(SUCCEEDED(retc)) switch(msg)
   {
   case WM_CREATE:
      KP_ASSERT(hKpInstance != NULL, KP_E_SYSTEM_ERROR, null, True);

#if FALSE
      if(SUCCEEDED(retc))
      {
         csp = (LPCREATESTRUCT)lParam;
         KP_ASSERT(csp != NULL, KP_E_SYSTEM_ERROR, null, True);
      }
      if(SUCCEEDED(retc)) dlg_ptr = (KpGeckoDialog *)csp->lpCreateParams;
#else
      dlg_ptr = KpGeckoDialogPtr;
#endif
      KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);

// -------------------------------- KpGeckoDialog::m_pResCtrl
      if(SUCCEEDED(retc)) dlg_ptr->CreateResCtrl(dlg_ptr->m_iWndCurX, dlg_ptr->m_iWndCurY, dlg_ptr->m_iWndCurDX, dlg_ptr->m_iWndCurDY, hwndDlg);
      break; // case WM_CREATE

   case WM_COMMAND:
      switch(retp)
      {
      case IDOK: break;
      case IDCANCEL: endfl = True; break;

      }
      break;

   case WM_CLOSE: endfl = True; break;

   case WM_QUIT:
      switch(retp)
      {
      case IDCANCEL: retc = KP_E_CANCEL; break;
      case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl = True;
      break;

   default:
      retb = DefWindowProc(hwndDlg, msg, wParam, lParam);
      break;

   } // if(SUCCEEDED(retc)) switch(uMsg)

   if(SUCCEEDED(retc)) /* retb = */ KpPubDialogProc(hwndDlg, uMsg, wParam, lParam);

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, msg, wParam, lParam);
      retb = TRUE;
   }

// if(FAILED(retc)) PostQuitMessage(IDABORT);
   if(endfl || FAILED(retc)) PostQuitMessage(RET_CODE_WIN(retc));

#ifndef KP_USE_WXWIDGETS
return(retb);
#endif
}
