//----------------------------------
// KpRichEd.cpp
//


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <ctype.h>
#include <string>
#include <iostream>
#include <fstream>
#if Compiler != Watcom
#include <sstream>
#endif
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
// #include <iostream.h>
#include <time.h>
#include <windows.h>
#include <winbase.h>
// #include <windowsx.h>
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
#include <RichEdit.h>
#include <Richole.h>
#endif
// #include <shlobj.h>


#if FALSE
// #include <winuser.h>
typedef struct tagWINDOWINFO
{
    DWORD cbSize;
    RECT  rcWindow;
    RECT  rcClient;
    DWORD dwStyle;
    DWORD dwExStyle;
    DWORD dwOtherStuff;
    UINT  cxWindowBorders;
    UINT  cyWindowBorders;
    ATOM  atomWindowType;
    WORD  wCreatorVersion;
} WINDOWINFO, *PWINDOWINFO, *LPWINDOWINFO;

BOOL WINAPI
GetWindowInfo(
    HWND hwnd,
    PWINDOWINFO pwi
);
#endif

#include <commctrl.h>

#if FALSE
WINUSERAPI
BOOL
WINAPI
TrackMouseEvent(
    LPTRACKMOUSEEVENT lpEventTrack);
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

#endif
#if (Envir!=MSWin32Mfc)
#include <stdio.h>
#endif
#include <string.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpmsg.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpsock.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "tvxmls.h"
#include "tvrtf.h"


// ============================================================================= KpRichEdit
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// IKpRichEditOleCallback IKpRichEditOleCallbackObj;
IRichEditOleCallback *pIKpRichEditOleCallbackObj = NULL;


STDMETHODIMP IKpRichEditOleCallback::GetDragDropEffect(BOOL /* fDrag */, DWORD /* grfKeyState */, LPDWORD pdwEffect)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) if(pdwEffect == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #ifdef Debug
stringstream str_stream;
str_stream << "IKpRichEditOleCallback:GetDragDropEffect: *pdwEffect: ";
if(SUCCEEDED(retc)) str_stream << *pdwEffect;
KP_TRACE(KpString(str_stream.str()));
#endif

   if(SUCCEEDED(retc)) *pdwEffect = 0L;

return(retc); // S_OK; // E_NOTIMPL;
}
#endif


#if FALSE
STDMETHODIMP IKpRichEditOleCallback::GetNewStorage(LPSTORAGE FAR *lplpstg)
{
// Initialize a Storage Object from a DocFile in memory
LPLOCKBYTES lpLockBytes = NULL;
SCODE sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
KP_TRACE("IKpRichEditOleCallback:GetNewStorage");
if (sc != S_OK) return sc;
sc = ::StgCreateDocfileOnILockBytes(lpLockBytes, STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, lplpstg);
if (sc != S_OK) lpLockBytes->Release();
return sc;
}
#endif

// ----------------------
WNDPROC RichEditProcSav = NULL;

// POINT pLastDragStart;

// ----------------------------------------
BOOL CALLBACK KpRichEditProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;

   if((RichEditProcSav == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
// KP_TRACE("KpRichEditProc WM_CREATE");

//    pLastDragStart.x = pLastDragStart.y = 0;

      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;

// ----------------------------------------
// pavojingø praneðimø wrapperis
   case WM_GETTEXT:
// KP_TRACE("KpRichEditProc WM_GETTEXT");
      break;
   case EM_GETSELTEXT:
// KP_TRACE("KpRichEditProc EM_GETSELTEXT");
      break;
   case EM_GETTEXTEX:
   case EM_STREAMOUT:

   case EM_DISPLAYBAND:
   case EM_GETIMECOMPTEXT:
   case EM_SETOLECALLBACK:
      break;

   case KP_WM_GETTEXT:
      retw=(*RichEditProcSav)(hwndDlg, WM_GETTEXT, wParam, lParam);
      break;

   case KP_EM_GETSELTEXT:
      retw=(*RichEditProcSav)(hwndDlg, EM_GETSELTEXT, wParam, lParam);
      break;

   case KP_EM_GETTEXTEX:
      retw=(*RichEditProcSav)(hwndDlg, EM_GETTEXTEX, wParam, lParam);
      break;

   case KP_EM_STREAMOUT:
      retw=(*RichEditProcSav)(hwndDlg, EM_STREAMOUT, wParam, lParam);
      break;

   case KP_EM_SETOLECALLBACK:
      retw=(*RichEditProcSav)(hwndDlg, EM_SETOLECALLBACK, wParam, lParam);
      break;

// ---------------------------------------- disable drag/drop
// EM_SETEVENTMASK ENM_DRAGDROPDONE
// WM_NOTIFY EN_DRAGDROPDONE

#if FALSE
   case WM_LBUTTONDOWN:
//    pLastDragStart.x = GET_X_LPARAM(lParam);
//    pLastDragStart.y = GET_Y_LPARAM(lParam);
#ifdef Debug
#if Envir==MSWin32
{
stringstream str_stream;
str_stream << "KpRichEditProc WM_LBUTTONDOWN: "; // <<
   // "[" << pLastDragStart.x << ", " << pLastDragStart.y << "]";
KP_TRACE(KpString(str_stream.str()));
}
#endif
#endif

#if FALSE
      {
TRACKMOUSEEVENT tr_ev;

         tr_ev.cbSize = sizeof(tr_ev);
         tr_ev.dwFlags = TME_LEAVE;
         tr_ev.hwndTrack = hwndDlg; // theDialog.m_ResRichEdit;
         tr_ev.dwHoverTime = HOVER_DEFAULT;

         if(!TrackMouseEvent(&tr_ev)) // EM_SETEVENTMASK // dël WM_MOUSELEAVE generavimo
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

#if FALSE
   case WM_LBUTTONUP:
KP_TRACE("KpRichEditProc WM_LBUTTONUP");
//    pLastDragStart.x = pLastDragStart.y = 0;

      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

#if FALSE
   case WM_MOUSEMOVE:
#if FALSE
      if(wParam & MK_LBUTTON) if(DragDetect(hwndDlg, pLastDragStart))
      {
#  if FALSE // #ifdef Debug
#     if Envir==MSWin32
{
stringstream str_stream;
str_stream << "KpRichEditProc ------ Drag: " <<
   "[" << pLastDragStart.x << ", " << pLastDragStart.y << "] " <<
   "[" << GET_X_LPARAM(lParam) << ", " << GET_Y_LPARAM(lParam) << "]";
KP_TRACE(KpString(str_stream.str()));
}
#     endif
#  endif
      }
#endif

#if FALSE // #ifdef Debug //
#if Envir==MSWin32
{
stringstream str_stream;
str_stream << "KpRichEditProc WM_MOUSEMOVE: " <<
   "[" << GET_X_LPARAM(lParam) << ", " << GET_Y_LPARAM(lParam) << "] " <<
   hex << (wParam & MK_LBUTTON);
KP_TRACE(KpString(str_stream.str()));
}
#endif
#endif
      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

// case WM_KILLFOCUS:
// KP_TRACE("KpRichEditProc WM_KILLFOCUS");
//    retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
//    break;

// case WM_CAPTURECHANGED:
// KP_TRACE("KpRichEditProc WM_CAPTURECHANGED");
//    retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
//    break;

#if FALSE
   case WM_MOUSELEAVE:
KP_TRACE("KpRichEditProc WM_MOUSELEAVE");

{
CHARRANGE ch_rang;
      ch_rang.cpMin = 0;
      ch_rang.cpMax = 0;
      SendMessage(hwndDlg, EM_EXSETSEL, 0, (long)&ch_rang);
}

      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

// ----------------------------------------
#if FALSE // #ifdef Debug
   case WM_NCHITTEST:
   case WM_SETCURSOR:
   case WM_CAPTURECHANGED:
   case WM_PAINT:
   case WM_ERASEBKGND:
   case WM_MOUSEACTIVATE:
   case WM_TIMER:
   case WM_IME_SETCONTEXT:
   case WM_IME_NOTIFY:
      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

   default:
#if FALSE // #ifdef Debug
#if Envir==MSWin32
stringstream str_stream;
str_stream << "KpRichEditProc: " << uMsg;
// sprintf((char *)str_buf, "D  %x          %x %x", uMsg, wParam, lParam); KP_TRACE(str_buf);
KP_TRACE(KpString(str_stream.str()));
#endif
#endif
//    retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;

   } // switch(uMsg)

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// ----------------------------------------
HRESULT KpCreateRichEdit(HINSTANCE hInst, HWND hParent, HWND *phEditControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc=S_OK;
HWND edit_field=NULL;

// if(hInst==NULL)
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// if((phEditControl==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
// if(SUCCEEDED(retc)) *phEditControl=NULL;

   if(((iKpCtrlStyle < 0) || (iKpCtrlStyle >= KPW_NUM_OF_CONTROL_STYLES_0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((hRichEditLib==NULL) && SUCCEEDED(retc))
   {

#ifndef KpRichEdit20
      hRichEditLib=LoadLibrary("Riched32.dll");
#else
      hRichEditLib=LoadLibraryW(L"RICHED20.DLL");
#endif
      if(hRichEditLib==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }


#if FALSE // #ifdef Debug
WNDCLASSEX wcx;

   if(SUCCEEDED(retc))
      if(!GetClassInfoEx(hKpInstance, "RichEdit", &wcx))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      wcx.hInstance = hKpInstance;
      wcx.lpszClassName = "KpRichEdit";
      wcx.style |= CS_SAVEBITS;
      wcx.cbSize = sizeof(WNDCLASSEX);

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }
#endif

#if FALSE // #ifdef Debug
WNDCLASSEX wcx;
HWND rtf_wnd = NULL;
HBRUSH brush = NULL;

// ---------------------------
   brush = NULL;
   brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "KpRichEdit",
      wcx.lpfnWndProc   = DefWindowProc;
      wcx.style         = CS_DBLCLKS | CS_SAVEBITS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, IDI_ASTERISK); // MAKEINTRESOURCE(/* lpszIconID */ IDI_ASTERISK));
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, IDI_ASTERISK); // MAKEINTRESOURCE(/* lpszIconID */ IDI_ASTERISK));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush; // (HBRUSH)iaColorMap[KpShadowNorm];

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

// if(brush) if(!DeleteObject(brush))
//    /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   brush = NULL;

// ---------------------------
   if(SUCCEEDED(retc))
   {
      rtf_wnd=CreateWindowEx
      (
         0,                // DWORD dwExStyle,        // extended window style
         "KpRichEdit",
         "", // "KpRichEditWnd",  // LPCTSTR lpWindowName,   // pointer to window name
         dwStyle|WS_VISIBLE|WS_CHILD, // DWORD dwStyle,       // window style
         iPosX, iPosY, iWdt, iHgt, hParent,
         0,                // HMENU hMenu,            // handle to menu, or child-window identifier
         hKpInstance,
         NULL              // LPVOID lpParam          // pointer to window-creation data
      );

      if(rtf_wnd==NULL)
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
         retc=KP_E_SYSTEM_ERROR;
      }
   }
#endif


WNDCLASSEX wcxw;
// _WNDCLASSEXW wcxw;
   if(SUCCEEDED(retc))
//    if(!GetClassInfoExW(hKpInstance, L"RichEdit20W", &wcxw))
      if(!GetClassInfoEx(hKpInstance, "RichEdit", &wcxw))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      RichEditProcSav = wcxw.lpfnWndProc;

      wcxw.hInstance = hInst;
      wcxw.lpszClassName = "KpRichEdit"; // L"KpRichEdit";
      wcxw.lpfnWndProc = (WNDPROC)KpRichEditProc;
      wcxw.cbSize = sizeof(wcxw);

      if(!RegisterClassEx(&wcxw)) // if(!RegisterClassExW(&wcxw)) //
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }


   if(SUCCEEDED(retc))
   {
      edit_field=CreateWindowEx(dwExStyle|WS_EX_TRANSPARENT/*|WS_EX_CLIENTEDGE|ES_SUNKEN*/,
#if TRUE
                  "KpRichEdit",
#else
#  ifndef KpRichEdit20
                  "RichEdit",
#  else
                  RICHEDIT_CLASS,
//                "RichEdit20A",
//                "RichEdit20W",
#  endif
#endif
                  (LPCTSTR)lpszText,
#if FALSE // #ifdef Debug
                  WS_VISIBLE|WS_CHILD|DS_SETFONT, // |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  0, 0, iWdt, iHgt, rtf_wnd, 0,
#else
                  dwStyle|WS_VISIBLE|WS_CHILD|DS_SETFONT,
                  iPosX, iPosY, iWdt, iHgt, hParent, 0,
#endif
                  GetModuleHandle(NULL), 0);
      if(!edit_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// rtf_wnd niekas netrina !!!

   if(SUCCEEDED(retc)) retc=SetCtrlFont(edit_field, iKpCtrlStyle);

   if((phEditControl!=NULL) && SUCCEEDED(retc)) *phEditControl=edit_field;

// --------------------------- uþdraudþiam drag/drop
   if((pIKpRichEditOleCallbackObj == NULL) && SUCCEEDED(retc))
   {
      KP_NEW(pIKpRichEditOleCallbackObj, IKpRichEditOleCallback);
   }
   if(SUCCEEDED(retc)) if(!SendMessage(edit_field, KP_EM_SETOLECALLBACK, 0, (LPARAM)pIKpRichEditOleCallbackObj))
   {
#ifdef Debug
char str_buf[100];
sprintf(str_buf, "%d", GetLastError());
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
#else
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
   }

return(retc);
}
#endif


#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// ----------------------
extern HRESULT KpCreateRichEditUni(HINSTANCE hInst, HWND hParent, KpWnd **pEditControl, const UniChar *sazText,
   int iWdt, int iHeight, int iPosX, int iPosY,
   KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle,
   const unsigned char *lpszFontName, int iFontSize, int iFlags, RGB_Color iFontColor,
   CHARFORMATW *pFontFmt)
{
HRESULT retc=S_OK;

   if(hInst==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((pEditControl==NULL) && SUCCEEDED(retc)) // butinas, nes po to reikia naikinti
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) *pEditControl=NULL;

   if((lpszFontName == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((pFontFmt == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(((iKpCtrlStyle < 0) || (iKpCtrlStyle >= KPW_NUM_OF_CONTROL_STYLES_0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((iKpCtrlStyle!=KPW_CONTROL_STYLE_NORMAL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);

   if((hRichEditLib==NULL) && SUCCEEDED(retc))
   {

#ifndef KpRichEdit20
      hRichEditLib=LoadLibrary("Riched32.dll");
#else
      hRichEditLib=LoadLibraryW(L"RICHED20.DLL");
#endif
      if(hRichEditLib==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }


//------------------------------------ ieskom tevo koordinaciu
WINDOWPLACEMENT parent_placement;
   parent_placement.length = sizeof(parent_placement);
   if(SUCCEEDED(retc))
      if(!GetWindowPlacement(hParent, &parent_placement))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);


//------------------------------------ kuriam apkarpymo teveli
WNDCLASSEX wcx;
HWND edit_popup = 0;
HWND tag_edit = 0;
int edit_x = 0;
int edit_y = 0;
DWORD ex_style = 0L;
DWORD style = 0L;
HBRUSH brush = NULL;

// ---------------------------------
   brush = NULL;
   if(SUCCEEDED(retc)) brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowLight]));

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hInst;
      wcx.lpszClassName = "KP_EDIT_FRAME",
      wcx.lpfnWndProc   = DefWindowProc; // (WNDPROC)KpEditFrameProc; //
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION);
      wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION);
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush; // KpWhiteBrush;

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

// if(brush) if(!DeleteObject(brush))
//    /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   brush = NULL;

// ---------------------------------
   if(SUCCEEDED(retc))
   {
      edit_x = parent_placement.rcNormalPosition.left + iPosX; // parent_placement.ptMaxPosition.x;
      edit_y = parent_placement.rcNormalPosition.top + iPosY; // parent_placement.ptMaxPosition.y;

      ex_style = dwExStyle; // |WS_EX_TRANSPARENT|WS_EX_TOPMOST|WS_EX_CLIENTEDGE
      style = dwStyle | WS_VISIBLE|WS_POPUP; // DS_SETFONT|WS_CHILD |WS_CLIPSIBLINGS; // |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT;

      edit_popup = CreateWindowEx(
         ex_style,
         "KP_EDIT_FRAME",
         "KpEditFrame", // "LzdShTagEditFrame",
         style,
         edit_x, edit_y, iWdt, iHeight,
         hParent,
         0, hKpInstance, 0);

      if(!edit_popup)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

WNDCLASSEX wcxw;
// _WNDCLASSEXW wcxw;
   if(SUCCEEDED(retc))
//    if(!GetClassInfoExW(hKpInstance, L"RichEdit20W", &wcxw))
      if(!GetClassInfoEx(hKpInstance, "RichEdit", &wcxw))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      RichEditProcSav = wcxw.lpfnWndProc;

      wcxw.hInstance = hInst;
      wcxw.lpszClassName = "KpRichEditUni"; // L"KpRichEditUni";
      wcxw.lpfnWndProc = (WNDPROC)KpRichEditUniProc;
      wcxw.cbSize = sizeof(wcxw);

      if(!RegisterClassEx(&wcxw)) // if(!RegisterClassExW(&wcxw)) //
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
int cor_x = 0;
int cor_y = 0;
      cor_x = 1;
      cor_y = 0;
//    cor_y = - int iFontSize/8;
      if(iFlags & KPS_ItalicFl){ if(iFontSize>21) cor_y = - (iFontSize-21);}
      else{ if(iFontSize>21) cor_y = - (iFontSize-21)*3/2;}
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "cor_x: %d  cor_y: %d", cor_x, cor_y);
KP_TRACE(str_buf);
#endif
KP_TRACE("KpCreateRichEditUni: CreateWindowEx");

// siaip jau reiketu dar ikelti RICHED20.DLL i hRichEditLib, bet jau turi buti
      tag_edit = CreateWindowEx( // CreateWindowExW( //
         0,
         "KpRichEditUni", // L"KpRichEditUni", // L"RichEdit20W", // "RichEdit", // "EDIT", //
         "", // L"", // (char *)cont_buf,
         WS_VISIBLE|WS_CHILD|DS_SETFONT,
         cor_x, cor_y, iWdt - cor_x, iHeight - cor_y,
         edit_popup,
         0, hKpInstance, 0);

      if(!tag_edit)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
      if(!SetFocus(tag_edit))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

// --------------------------- uþdraudþiam drag/drop
   if((pIKpRichEditOleCallbackObj == NULL) && SUCCEEDED(retc))
   {
      KP_NEW(pIKpRichEditOleCallbackObj, IKpRichEditOleCallback);
   }
   if(SUCCEEDED(retc)) if(!SendMessage(tag_edit, KP_EM_SETOLECALLBACK, 0, (LPARAM)pIKpRichEditOleCallbackObj))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// ----------------------- set font attributes
HFONT hfont=0;
#if FALSE // #if TRUE //
HDC hdc = 0;
   if(SUCCEEDED(retc))
   {
      hdc = GetDC(tag_edit);
      if(!hdc)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      hfont=CreateFont
      (
         -MulDiv(iFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72*2), // int nHeight,               // logical height of font
         0,                          // int nWidth,                // logical average character width
         0,                          // int nEscapement,           // angle of escapement
         0,                          // int nOrientation,          // base-line orientation angle
         (iFlags & KPS_BoldFl)?FW_BOLD:FW_NORMAL, // FW_DONTCARE, // int fnWeight,              // font weight
         (iFlags & KPS_ItalicFl)!=0,  // DWORD fdwItalic,           // italic attribute flag
         (iFlags & KPS_UnderlFl)!=0,  // DWORD fdwUnderline,        // underline attribute flag
         False,                      // DWORD fdwStrikeOut,        // strikeout attribute flag
         rtf_ctbl, //  !!! perduot parametru                  // DWORD fdwCharSet,          // character set identifier
         OUT_DEFAULT_PRECIS,         // DWORD fdwOutputPrecision,  // output precision
         CLIP_DEFAULT_PRECIS,        // DWORD fdwClipPrecision,    // clipping precision
         DEFAULT_QUALITY,            // DWORD fdwQuality,          // output quality
         DEFAULT_PITCH, // |FF_SWISS, // DWORD fdwPitchAndFamily,   // pitch and family
         (char *)lpszFontName // "Times New Roman" // LPCTSTR lpszFace           // pointer to typeface name string
      );
      if(hfont==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
      if(!PostMessage(tag_edit, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True, 0)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
   if(SUCCEEDED(retc))
   {
      pFontFmt->cbSize = sizeof(*pFontFmt);
      pFontFmt->dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_COLOR | // CFM_STRIKEOUT |
         CFM_FACE | CFM_SIZE | CFM_OFFSET; // CFM_CHARSET |

      pFontFmt->dwEffects = 0;
      if(iFlags & KPS_BoldFl) pFontFmt->dwEffects |= CFE_BOLD;
      if(iFlags & KPS_ItalicFl) pFontFmt->dwEffects |= CFE_ITALIC;
      if(iFlags & KPS_UnderlFl) pFontFmt->dwEffects |= CFE_UNDERLINE;

      pFontFmt->yHeight = iFontSize*(20/2);
      pFontFmt->yOffset = 0;
      pFontFmt->crTextColor = iFontColor;
//    pFontFmt->bCharSet = BALTIC_CHARSET;
      pFontFmt->bPitchAndFamily = DEFAULT_PITCH;

#if FALSE // #if TRUE //
      strncpy(pFontFmt->szFaceName, (char *)lpszFontName, // "Palemonas", // "Vytis", // "akademinisLT", // "akademinisLT Kirciuotos", // "Times New Roman",
         LF_FACESIZE);
#else
      if(SUCCEEDED(retc)) if(strlen(lpszFontName) >= LF_FACESIZE)
         retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         retc = KptStrToUnicode(pFontFmt->szFaceName, lpszFontName, 1);
         if(FAILED(retc))
            retc = KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
#endif
      pFontFmt->szFaceName[LF_FACESIZE] = 0; // Nul;
   }

   if(SUCCEEDED(retc))
      if(!PostMessage(tag_edit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)pFontFmt))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE("EM_SETCHARFORMAT");
#endif

// --------------------------------- sukuriam KpWnd apvalkala
   KP_NEWO(*pEditControl, KpWnd(edit_popup, TYP_KpRichEditUni, NULL, hParent,
         hKpInstance, hfont, LoadIcon(hInst, IDI_APPLICATION), iKpCtrlStyle,
         iWdt, iHeight, 1, 1, ex_style, style,
         tag_edit // nestandartiskai naudojam m_phMDI_Client EDIT control'o issaugojimui
         ));

   if(SUCCEEDED(retc)) (*pEditControl)->m_pFontFmt = pFontFmt;
   if(SUCCEEDED(retc)) retc = WndPreg(*pEditControl, TYP_KpRichEditUni, hInst, NULL, False);


// ------------- send text to the edit control
// static UniChar uni_str[] = {C_A, C_B, 0x0411, 0x0414, 0x03B1, 0x03B4, 0x0104, 0x010D, 0xE002, 0xE020, 0};
   if(SUCCEEDED(retc)) retc = KpSetWindowUniText(tag_edit, sazText /* uni_str */, lpszFontName);

// ------------- dar karta nustatom fonta
#if FALSE
#if FALSE // #if TRUE //
   if(SUCCEEDED(retc))
      if(!PostMessage(tag_edit, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True, 0)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
   if(SUCCEEDED(retc))
      if(!PostMessage(tag_edit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)pFontFmt))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
#endif

return(retc);
}
#endif


// -------------------------------------------
#if FALSE
BOOL CALLBACK KpEditFrameProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CHAR:
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "WM_CHAR %c %x %lx", wParam, wParam, lParam);
KP_TRACE(str_buf);
#endif
      retw=TRUE;
      break;

   default:
// sprintf((char *)str_buf, "D  %x          %x %x", uMsg, wParam, lParam); KP_TRACE(str_buf);
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


// ----------------------------------
KpChar KbCyrScanCodesArr[KPT_Ctbsiz] = // rusiskos klaviaturos skankodai
{
   C_Quest, // '?' // 00
   C_Quest, // '?' // 01
   C_Quest, // '?' // 02 // C_a_Ogon
   C_Quest, // '?' // 03 // C_c_Caron
   C_Quest, // '?' // 04 // C_e_Ogon
   C_Quest, // '?' // 05 // C_e_Adot
   C_Quest, // '?' // 06 // C_i_Ogon
   C_Quest, // '?' // 07 // C_s_Car
   C_Quest, // '?' // 08 // C_u_Ogon
   C_Quest, // '?' // 09 // C_u_Macr
   C_Quest, // '?' // 0a
   C_Quest, // '?' // 0b
   C_Quest, // '?' // 0c
   C_hard_Cyr,     // 0d // C_z_Car
   C_Quest, // '?' // 0e
   C_Quest, // '?' // 0f
   C_ya_Cyr,       // 10
   C_zh_Cyr,       // 11
   C_e_Cyr,        // 12
   C_r_Cyr,        // 13
   C_t_Cyr,        // 14
   C_y_Cyr,        // 15
   C_u_Cyr,        // 16
   C_i_Cyr,        // 17
   C_o_Cyr,        // 18
   C_p_Cyr,        // 19
   C_sh_Cyr,       // 1a
   C_shch_Cyr,     // 1b
   C_Quest, // '?' // 1c
   C_Quest, // '?' // 1d
   C_a_Cyr,        // 1e
   C_s_Cyr,        // 1f
   C_d_Cyr,        // 20
   C_f_Cyr,        // 21
   C_g_Cyr,        // 22
   C_h_Cyr,        // 23
   C_j_Cyr,        // 24
   C_k_Cyr,        // 25
   C_l_Cyr,        // 26
   C_Quest, // '?' // 27
   C_Quest, // '?' // 28
   C_yu_Cyr,       // 29
   C_Quest, // '?' // 2a
   C_ee_Cyr,       // 2b
   C_z_Cyr,        // 2c
   C_soft_Cyr,     // 2d
   C_c_Cyr,        // 2e
   C_v_Cyr,        // 2f
   C_b_Cyr,        // 30
   C_n_Cyr,        // 31
   C_m_Cyr,        // 32
   C_Quest, // '?' // 33
   C_Quest, // '?' // 34
   C_Quest, // '?' // 35
   C_Quest, // '?' // 36
   C_Quest, // '?' // 37
   C_Quest, // '?' // 38
   C_Quest, // '?' // 39
   C_Quest, // '?' // 3a
   C_Quest, // '?' // 3b
   C_Quest, // '?' // 3c
   C_Quest, // '?' // 3d
   C_Quest, // '?' // 3e
   C_Quest, // '?' // 3f
   C_Quest, // '?' // 40
   C_Quest, // '?' // 41
   C_Quest, // '?' // 42
   C_Quest, // '?' // 43
   C_Quest, // '?' // 44
   C_Quest, // '?' // 45
   C_Quest, // '?' // 46
   C_Quest, // '?' // 47
   C_Quest, // '?' // 48
   C_Quest, // '?' // 49
   C_Quest, // '?' // 4a
   C_Quest, // '?' // 4b
   C_Quest, // '?' // 4c
   C_Quest, // '?' // 4d
   C_Quest, // '?' // 4e
   C_Quest, // '?' // 4f
   C_Quest, // '?' // 50
   C_Quest, // '?' // 51
   C_Quest, // '?' // 52
   C_Quest, // '?' // 53
   C_Quest, // '?' // 54
   C_Quest, // '?' // 55
   C_Quest, // '?' // 56
   C_Quest, // '?' // 57
   C_Quest, // '?' // 58
   C_Quest, // '?' // 59
   C_Quest, // '?' // 5a
   C_Quest, // '?' // 5b
   C_Quest, // '?' // 5c
   C_Quest, // '?' // 5d
   C_Quest, // '?' // 5e
   C_Quest, // '?' // 5f
   C_Quest, // '?' // 60
   C_Quest, // '?' // 61
   C_Quest, // '?' // 62
   C_Quest, // '?' // 63
   C_Quest, // '?' // 64
   C_Quest, // '?' // 65
   C_Quest, // '?' // 66
   C_Quest, // '?' // 67
   C_Quest, // '?' // 68
   C_Quest, // '?' // 69
   C_Quest, // '?' // 6a
   C_Quest, // '?' // 6b
   C_Quest, // '?' // 6c
   C_Quest, // '?' // 6d
   C_Quest, // '?' // 6e
   C_Quest, // '?' // 6f
   C_Quest, // '?' // 70
   C_Quest, // '?' // 71
   C_Quest, // '?' // 72
   C_Quest, // '?' // 73
   C_Quest, // '?' // 74
   C_Quest, // '?' // 75
   C_Quest, // '?' // 76
   C_Quest, // '?' // 77
   C_Quest, // '?' // 78
   C_Quest, // '?' // 79
   C_Quest, // '?' // 7a
   C_Quest, // '?' // 7b
   C_Quest, // '?' // 7c
   C_Quest, // '?' // 7d
   C_Quest, // '?' // 7e
   C_Quest, // '?' // 7f
   C_Quest, // '?' // 80
   C_Quest, // '?' // 81
   C_Quest, // '?' // 82
   C_Quest, // '?' // 83
   C_Quest, // '?' // 84
   C_Quest, // '?' // 85
   C_Quest, // '?' // 86
   C_Quest, // '?' // 87
   C_Quest, // '?' // 88
   C_Quest, // '?' // 89
   C_Quest, // '?' // 8a
   C_Quest, // '?' // 8b
   C_Quest, // '?' // 8c
   C_Quest, // '?' // 8d
   C_Quest, // '?' // 8e
   C_Quest, // '?' // 8f
   C_Quest, // '?' // 90
   C_Quest, // '?' // 91
   C_Quest, // '?' // 92
   C_Quest, // '?' // 93
   C_Quest, // '?' // 94
   C_Quest, // '?' // 95
   C_Quest, // '?' // 96
   C_Quest, // '?' // 97
   C_Quest, // '?' // 98
   C_Quest, // '?' // 99
   C_Quest, // '?' // 9a
   C_Quest, // '?' // 9b
   C_Quest, // '?' // 9c
   C_Quest, // '?' // 9d
   C_Quest, // '?' // 9e
   C_Quest, // '?' // 9f
   C_Quest, // '?' // a0
   C_Quest, // '?' // a1
   C_Quest, // '?' // a2
   C_Quest, // '?' // a3
   C_Quest, // '?' // a4
   C_Quest, // '?' // a5
   C_Quest, // '?' // a6
   C_Quest, // '?' // a7
   C_Quest, // '?' // a8
   C_Quest, // '?' // a9
   C_Quest, // '?' // aa
   C_Quest, // '?' // ab
   C_Quest, // '?' // ac
   C_Quest, // '?' // ad
   C_Quest, // '?' // ae
   C_Quest, // '?' // af
   C_Quest, // '?' // b0
   C_Quest, // '?' // b1
   C_Quest, // '?' // b2
   C_Quest, // '?' // b3
   C_Quest, // '?' // b4
   C_Quest, // '?' // b5
   C_Quest, // '?' // b6
   C_Quest, // '?' // b7
   C_Quest, // '?' // b8
   C_Quest, // '?' // b9
   C_Quest, // '?' // ba
   C_Quest, // '?' // bb
   C_Quest, // '?' // bc
   C_Quest, // '?' // bd
   C_Quest, // '?' // be
   C_Quest, // '?' // bf
   C_Quest, // '?' // c0
   C_Quest, // '?' // c1
   C_Quest, // '?' // c2
   C_Quest, // '?' // c3
   C_Quest, // '?' // c4
   C_Quest, // '?' // c5
   C_Quest, // '?' // c6
   C_Quest, // '?' // c7
   C_Quest, // '?' // c8
   C_Quest, // '?' // c9
   C_Quest, // '?' // ca
   C_Quest, // '?' // cb
   C_Quest, // '?' // cc
   C_Quest, // '?' // cd
   C_Quest, // '?' // ce
   C_Quest, // '?' // cf
   C_Quest, // '?' // d0
   C_Quest, // '?' // d1
   C_Quest, // '?' // d2
   C_Quest, // '?' // d3
   C_Quest, // '?' // d4
   C_Quest, // '?' // d5
   C_Quest, // '?' // d6
   C_Quest, // '?' // d7
   C_Quest, // '?' // d8
   C_Quest, // '?' // d9
   C_Quest, // '?' // da
   C_Quest, // '?' // db
   C_Quest, // '?' // dc
   C_Quest, // '?' // dd
   C_Quest, // '?' // de
   C_Quest, // '?' // df
   C_Quest, // '?' // e0
   C_Quest, // '?' // e1
   C_Quest, // '?' // e2
   C_Quest, // '?' // e3
   C_Quest, // '?' // e4
   C_Quest, // '?' // e5
   C_Quest, // '?' // e6
   C_Quest, // '?' // e7
   C_Quest, // '?' // e8
   C_Quest, // '?' // e9
   C_Quest, // '?' // ea
   C_Quest, // '?' // eb
   C_Quest, // '?' // ec
   C_Quest, // '?' // ed
   C_Quest, // '?' // ee
   C_Quest, // '?' // ef
   C_Quest, // '?' // f0
   C_Quest, // '?' // f1
   C_Quest, // '?' // f2
   C_Quest, // '?' // f3
   C_Quest, // '?' // f4
   C_Quest, // '?' // f5
   C_Quest, // '?' // f6
   C_Quest, // '?' // f7
   C_Quest, // '?' // f8
   C_Quest, // '?' // f9
   C_Quest, // '?' // fa
   C_Quest, // '?' // fb
   C_Quest, // '?' // fc
   C_Quest, // '?' // fd
   C_Quest, // '?' // fe
   C_Quest, // '?' // ff
};


// ----------------------------------
BOOL CALLBACK KpRichEditUniProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;

   if((RichEditProcSav == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_KEYDOWN:
#  if FALSE // #  ifdef Debug
char str_buf[100];
sprintf(str_buf, "WM_KEYDOWN %c %x %lx", wParam, wParam, lParam);
KP_TRACE(str_buf);
#  endif

      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);

      if(SUCCEEDED(retc))
         if(!PostThreadMessage(GetCurrentThreadId(), WM_LZDSH_REFRESH_DISPLAY, 0, 0L))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "KpRichEditUniProc: WM_LZDSH_REFRESH_DISPLAY sent; ThreadId:%ld", GetCurrentThreadId());
KP_TRACE(str_buf);
#endif

      break;

#if FALSE
   case WM_KEYUP:
#if FALSE // #  ifdef Debug
// char str_buf[100];
sprintf(str_buf, "WM_KEYUP %c %x %lx", wParam, wParam, lParam);
KP_TRACE(str_buf);
#  endif
      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

   case WM_CHAR:
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "WM_CHAR %c %x %lx", wParam, wParam, lParam);
KP_TRACE(str_buf);
#endif

// cyrillic keyboard
      if(wParam == '?')
      {
int scan_code = 0;
KpChar kp_char = C_Nul;

         scan_code = (lParam >> 16) & 0xFF;
         kp_char = KbCyrScanCodesArr[scan_code];

         if(
            ((GetKeyState(VK_CAPITAL) & 1) && (!(GetKeyState(VK_SHIFT) & 0x8000))) ||
            ((!(GetKeyState(VK_CAPITAL) & 1)) && (GetKeyState(VK_SHIFT) & 0x8000))
           )
            kp_char = TvKpToUpper(kp_char);

         wParam = iaUniChars[kp_char];
      }

#if FALSE // #ifdef Debug
// char str_buf[100];
sprintf(str_buf, "VK_SHIFT: %x VK_CAPITAL: %x", GetKeyState(VK_SHIFT), GetKeyState(VK_CAPITAL));
KP_TRACE(str_buf);
#endif

      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);

// ----------- ieskom uzregistruoto KpWnd lango
KpWnd *cur_wnd;
      cur_wnd = NULL;
      if(SUCCEEDED(retc)) retc = GetCurChildWindow(&cur_wnd, hwndDlg);
      if(SUCCEEDED(retc)) if(!cur_wnd)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) if(!cur_wnd->m_pFontFmt)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// ---------------------------------- atstatom buvusius fonto atributus
static UniChar uni_buf[KP_MAX_FILE_LIN_LEN+1];
CHARRANGE char_range;
      if(SUCCEEDED(retc)) retc = KpGetWindowUniText(hwndDlg, uni_buf, KP_MAX_FILE_LIN_LEN);
      char_range.cpMin = 0L;
      char_range.cpMax = 0L;
      SendMessage(hwndDlg, EM_EXGETSEL, 0, (LPARAM)&char_range);
#if FALSE // #ifdef Debug
// char str_buf[100];
sprintf(str_buf, "EM_EXGETSEL %ld %ld", char_range.cpMin, char_range.cpMax);
KP_TRACE(str_buf);
#endif

      if(SUCCEEDED(retc))
         if(!PostMessage(hwndDlg, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)cur_wnd->m_pFontFmt))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

unsigned char font_name[LF_FACESIZE+1];
      if(SUCCEEDED(retc))
      {
         retc = KptUnicodeToStr(font_name, cur_wnd->m_pFontFmt->szFaceName, 1);
         if(FAILED(retc))
            retc = KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         font_name[LF_FACESIZE] = Nul;
      }

      if(SUCCEEDED(retc)) retc = KpSetWindowUniText(hwndDlg, uni_buf, font_name);
      SendMessage(hwndDlg, EM_EXSETSEL, 0, (LPARAM)&char_range);

      break;

#if FALSE
   case WM_UNICHAR:
#  ifdef Debug
// char str_buf[100];
sprintf(str_buf, "WM_UNICHAR %c %x %lx", wParam, wParam, lParam);
KP_TRACE(str_buf);
#  endif
      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

// ----------------------------------------
// pavojingø praneðimø wrapperis
   case WM_GETTEXT:
// KP_TRACE("KpRichEditUniProc WM_GETTEXT");
      break;
   case EM_GETSELTEXT:
// KP_TRACE("KpRichEditUniProc EM_GETSELTEXT");
      break;
   case EM_GETTEXTEX:
   case EM_STREAMOUT:

   case EM_DISPLAYBAND:
   case EM_GETIMECOMPTEXT:
   case EM_SETOLECALLBACK:
      break;

   case KP_WM_GETTEXT:
      retw=(*RichEditProcSav)(hwndDlg, WM_GETTEXT, wParam, lParam);
      break;

   case KP_EM_GETSELTEXT:
      retw=(*RichEditProcSav)(hwndDlg, EM_GETSELTEXT, wParam, lParam);
      break;

   case KP_EM_GETTEXTEX:
      retw=(*RichEditProcSav)(hwndDlg, EM_GETTEXTEX, wParam, lParam);
      break;

   case KP_EM_STREAMOUT:
      retw=(*RichEditProcSav)(hwndDlg, EM_STREAMOUT, wParam, lParam);
      break;

   case KP_EM_SETOLECALLBACK:
      retw=(*RichEditProcSav)(hwndDlg, EM_SETOLECALLBACK, wParam, lParam);
      break;

// ----------------------------------------
   default:
// sprintf((char *)str_buf, "D  %x          %x %x", uMsg, wParam, lParam); KP_TRACE(str_buf);
//    retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      retw=(*RichEditProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;

   } // switch(uMsg)

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// --------------------------------------------------
HRESULT XmlNode::SetTagHeadings(int iNumOfParStyles, HWND hParent)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char str_buf[100];
HWND form_wnd = NULL;
HWND form_ctrl = NULL;
WNDCLASSEX wcx;
HDC dc = 0;
DWORD ex_style=0L;
DWORD style=0L;
int wnd_x;
int wnd_y;
int wnd_dx;
int wnd_dy;


// ------------------------------
   SetTagHeadings_node_suff[0] = C_Nul;

   SetTagHeadings_rtf_file_buf[0] = Nul;

   SetTagHeadings_rtf_file = NULL;
   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%x %x", SetTagHeadings_rtf_file_buf, XMLN_RICH_BUF_LEN);
      KP_NEWO(SetTagHeadings_rtf_file, TvRtfO(str_buf, CreateNewBFile, iaRtfFonts));
   }


// ------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "SetTagHeadingsClass",
      wcx.lpfnWndProc   = DefWindowProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, IDI_ASTERISK); // MAKEINTRESOURCE(/* lpszIconID */ IDI_ASTERISK));
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, IDI_ASTERISK); // MAKEINTRESOURCE(/* lpszIconID */ IDI_ASTERISK));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   wnd_x = 100;
   wnd_y = 100;
   wnd_dx = rtf_grab_ctrl_dx + 2*rtf_grab_ctrl_margin + 2*iWndBorderWdt;
   wnd_dy = rtf_grab_ctrl_dy + 2*rtf_grab_ctrl_margin + iWndCaptionHgt + 2*iWndBorderWdt;;
   if(SUCCEEDED(retc))
   {
      dc=GetDC(HWND_DESKTOP);
      if(dc==NULL)
      {
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      else
      {
//       wnd_x=(GetDeviceCaps(dc, HORZRES)-wnd_dx)/2;
//       wnd_y=(GetDeviceCaps(dc, VERTRES)-wnd_dy)/2;

         wnd_x = GetDeviceCaps(dc, HORZRES) - wnd_dx - rtf_grab_wnd_margin_x;
         wnd_y = GetDeviceCaps(dc, VERTRES) - wnd_dy - rtf_grab_wnd_margin_y;
      }
   }

   if(SUCCEEDED(retc))
   {
      ex_style=WS_EX_TOPMOST; // WS_EX_NOACTIVATE|
      style=WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME; // |WS_BORDER|WS_POPUP

      form_wnd=CreateWindowEx
      (
         ex_style,               // DWORD dwExStyle,      // extended window style
         "SetTagHeadingsClass",
         "SetTagHeadingsWnd",            // LPCTSTR lpWindowName, // pointer to window name
         style,                  // DWORD dwStyle,        // window style
         wnd_x, // CW_USEDEFAULT // int x,                // horizontal position of window
         wnd_y, // CW_USEDEFAULT // int y,                // vertical position of window
         wnd_dx,                 // int nWidth,           // window width
         wnd_dy,                 // int nHeight,          // window height
         hParent, // HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         hKpInstance,
         NULL    // LPVOID lpParam        // pointer to window-creation data
      );

      if(form_wnd==NULL)
      {
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

// if(SUCCEEDED(retc))
//    if(!SetWindowPos(form_wnd, HWND_NOTOPMOST, wnd_x, wnd_y, wnd_dx, wnd_dy, SWP_NOACTIVATE))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

#ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "XmlNode::SetTagHeadings: %d %d", iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL], rtf_grab_ctrl_dy);
KP_TRACE(str_buf);
}
#endif

   if(SUCCEEDED(retc)) retc=KpCreateRichEdit(hKpInstance, form_wnd, &form_ctrl, (const unsigned char *)"",
         rtf_grab_ctrl_dx, rtf_grab_ctrl_dy,
         rtf_grab_ctrl_x, rtf_grab_ctrl_y,
         KPW_CONTROL_STYLE_NORMAL,
         0 /* WS_EX_CLIENTEDGE|ES_SUNKEN */,
         /* WS_POPUPWINDOW| */ ES_MULTILINE|WS_VSCROLL /* |ES_READONLY */);
   if(SUCCEEDED(retc)) if(form_ctrl==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);


// --------------------------- palaukiam, kol langas susikurs - blogai, kai refresinam pavieniu mazgu tekstukus -
//                                pirmas tekstas jau reiksminis, pilno lizdo pirmas tuscias
//                                o gal cia nusiust tuscia teksta ir patikrint, kad jau atsirado?
   if(SUCCEEDED(retc)) KpSleep(100, HWND_DESKTOP);

// ---------------------------
   if(SUCCEEDED(retc)) retc = SetTagHeadings_loop(iNumOfParStyles, form_ctrl);


// ---------------------------
   if(SetTagHeadings_rtf_file != NULL)
   {
      retc0=SetTagHeadings_rtf_file->CloseFile(True);
      if(SUCCEEDED(retc)) retc=retc0;
   }

   KP_DELETE(SetTagHeadings_rtf_file);

   if(form_wnd) DestroyWindow(form_wnd);
   form_wnd = NULL;
   form_ctrl = NULL;

return(retc);
}
#endif


