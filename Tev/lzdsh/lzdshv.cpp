// ---------------------------
// lzdshv.cpp
// zodyno perziuros programa
// versijos (About) langelis
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

#ifdef KP_USE_WXWIDGETS
#include "wx/app.h"
#include "wx/listbox.h"
#include "wx/sizer.h"
#endif

#ifdef IBSH_RES_MODE_MSHTML
#if CompilerGr==Mingw
#include "HTMLWindow.h"
#endif
#endif

#if TRUE // #ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#ifdef KP_USE_TextGRAB
// #include "atlbase.h"
#include "tgsdkx.h"
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
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpstmsg.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlu.h"
#include "xml8.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpRtfDlg.h"
#ifdef IBSH_RES_MODE_XGECKO
#  if CompilerGr==Mingw
#include "KpGecko.h"
#  endif
#endif
#include "iBshl.h"
#include "lzdsh.h"
#include "lzdshl.h"
#include "lzdshr.h"
#include "lzdsht.h"
#include "lzdshv.h"



// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif


// ----------------------------------
LzdShAboutDlg::LzdShAboutDlg(void)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

// LZDSH_DLG_PTR_INIT;
   KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);
KpPubDlg *lzdsh_dlg = NULL;
   if(SUCCEEDED(retc)) lzdsh_dlg = theKpStAppPtr->m_pGrpKpPubDlg;
   KP_ASSERT(lzdsh_dlg != NULL, E_POINTER, null, True);

   m_hDialogWindow = NULL;
   m_bWindowOpen = False;

   m_iWndCurX = 100;
   m_iWndCurY = 100;
   if(SUCCEEDED(retc))
   {
      m_iWndCurX = LZDSH_ABOUT_WND_X;
      m_iWndCurY = LZDSH_ABOUT_WND_Y;
   }

   m_GuideButton = NULL;
   m_AboutButton = NULL;

   m_UpdButton = NULL;

// m_bLButPressed=False; // left mouse button pressed flag, used for draging
   m_iMouseX = (-1);
   m_iMouseY = (-1);
   bool m_bCaptured = False;

   m_ButExit = NULL;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------------------
HRESULT LzdShAboutDlg::OpenWindow(HINSTANCE hInst)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
HBRUSH brush;
unsigned char publisher[KP_MAX_FNAME_LEN + 1];
int prod_ver = 0;

   KP_ASSERT(hInst, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) m_hInstance = hInst;

   LZDSH_DLG_PTR_INIT;
   KP_ASSERT(lzdsh_dlg->m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);

// ---------------- current skin
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdVer(&prod_ver);

// --------------------------------- "LZDSHABOUT" class
   if(SUCCEEDED(retc))
   {
#if IBSH_SKIN == IBSH_SKIN_STANDART
      brush=CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];
#else
#if FALSE
      if(GetObject(lzdsh_dlg->m_aPenScheme[KpShadowNorm], sizeof(log_pen), &log_pen))
         brush = CreateSolidBrush(log_pen.elpColor);
      else
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         brush=CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];
      }
#else
      brush=CreateSolidBrush(KpColorSchemeLocal[KpShadowNorm]);
#endif
#endif
   }

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "LZDSHABOUT",
      wcx.lpfnWndProc   = (WNDPROC)LzdShAboutDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON));
      wcx.hIconSm       = LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush;

      if(!RegisterClassEx(&wcx))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

// ----------------------------- m_hDialogWindow
   m_iWndCurX=LZDSH_ABOUT_WND_X;
   m_iWndCurY=LZDSH_ABOUT_WND_Y;

   if(SUCCEEDED(retc))
   {
      m_hDialogWindow=CreateWindowEx
      (
#if IBSH_SKIN == IBSH_SKIN_STANDART
         0,                      // DWORD dwExStyle,      // extended window style
#elif (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         WS_EX_APPWINDOW, // WS_EX_TRANSPARENT,
#endif
         "LZDSHABOUT",
         LZDSH_ABOUT_WND_TXT, // LPCTSTR lpWindowName, // pointer to window name
#if IBSH_SKIN == IBSH_SKIN_STANDART
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
#elif (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         WS_POPUP|WS_VISIBLE,
#endif
         LZDSH_ABOUT_WND_X, // CW_USEDEFAULT, // int x,               // horizontal position of window
         LZDSH_ABOUT_WND_Y, // CW_USEDEFAULT, // int y,               // vertical position of window
         LZDSH_ABOUT_WND_DX,           // int nWidth,           // window width
         LZDSH_ABOUT_WND_DY,           // int nHeight,          // window height
#ifdef KP_USE_WXWIDGETS
         (HWND)lzdsh_dlg->m_hDialogWindow->GetHWND(),
#else
         lzdsh_dlg->m_hDialogWindow,           // HWND hWndParent,      // handle to parent or owner window
#endif
         NULL,       // HMENU hMenu,          // handle to menu, or child-window identifier
         m_hInstance,
         NULL                    // LPVOID lpParam        // pointer to window-creation data
      );

      if(m_hDialogWindow==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// if(SUCCEEDED(retc)) retc=KpSleep(500, m_hDialogWindow);

// if(SUCCEEDED(retc)) SetCapture(m_hDialogWindow);

return(retc);
}


// -----------------------------------------
BOOL CALLBACK LzdShAboutDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;
int retp;
bool endfl=False;
HDC hdc=NULL;
PAINTSTRUCT ps;
HWND list_ctrl=NULL;
HWND parent_window=NULL;
#if IBSH_SKIN != IBSH_SKIN_STANDART
int ix, iy, dx, dy;
// EXTLOGPEN log_pen;
HBRUSH brush = NULL;
RECT rect;
// static HPEN capt_penscheme[KpNumOfShadows0];
static COLORREF capt_colorscheme[KpNumOfShadows0];
#endif
HPEN pen = NULL;

   retp = LOWORD(wParam);
   endfl = False;

   LZDSH_DLG_PTR_INIT;

   KP_ASSERT(pAboutDialog != NULL, E_POINTER, True, null);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:

      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);

      parent_window = hwndDlg;

// ------------------------------- combo box of skins
#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "WM_CREATE %d", hwndDlg);
KP_TRACE(str_buf);
}
#endif

// ----------------- caption text
#if IBSH_SKIN != IBSH_SKIN_STANDART
#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "%d %d %d", sizeof(lzdsh_dlg->m_aPenScheme), sizeof(lzdsh_dlg->m_aPenScheme[KpCaptionColor]), sizeof(HPEN));
KP_TRACE(str_buf);
}
#endif
//    memcpy(&(capt_penscheme[KpShadowNorm]), &(lzdsh_dlg->m_aPenScheme[KpCaptionColor]), sizeof(lzdsh_dlg->m_aPenScheme[KpCaptionColor]));
//    memcpy(capt_penscheme, lzdsh_dlg->m_aPenScheme, sizeof(lzdsh_dlg->m_aPenScheme));
      memcpy(capt_colorscheme, KpColorSchemeLocal, sizeof(KpColorSchemeLocal));

//    capt_penscheme[KpShadowNorm]=lzdsh_dlg->m_aPenScheme[KpCaptionColor];
      capt_colorscheme[KpShadowNorm]=KpColorSchemeLocal[KpCaptionColor];

//    memcpy(&capt_penscheme[KpShadowDark], &lzdsh_dlg->m_aPenScheme[KpShadowLight], sizeof(lzdsh_dlg->m_aPenScheme[KpShadowLight]));
//    capt_penscheme[KpShadowDark] = lzdsh_dlg->m_aPenScheme[KpShadowLight];
      capt_colorscheme[KpShadowDark]=KpColorSchemeLocal[KpShadowLight];

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, (const unsigned char *)LZDSH_ABOUT_WND_TXT, LZDSH_ABOUT_CAPT_TXT_X, LZDSH_ABOUT_CAPT_TXT_Y, 1, KPW_CONTROL_STYLE_HEADING_3, 0, 0, capt_colorscheme); // capt_penscheme);
#endif

// -------------------- exit button
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(theAboutDialog.m_ButExit), IDCANCEL /* KP_ID_EXIT */,
         LZDSH_IDI_EXIT_BITMAP,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_EXIT_LIGHT_BITMAP,
         LZDSH_IDI_EXIT_SEL_BITMAP,
#else
         LZDSH_IDI_EXIT_BITMAP,
         LZDSH_IDI_EXIT_BITMAP,
#endif
         LZDSH_ABOUT_BUT_EXIT_X, LZDSH_ABOUT_BUT_EXIT_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#else
         0,
#endif
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

      KP_ASSERT(theAboutDialog.m_ButExit, KP_E_SYSTEM_ERROR, True, null);

// ------------------------ version text
      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, parent_window, NULL, LZDSH_VERSION_TXT, LZDSH_VERSION_X, LZDSH_VERSION_Y, LZDSH_VERSION_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0L, 0L,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                                    0);
#else
                                    KpColorSchemeLocal);
#endif
      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
//       hdc=GetDC(hwndDlg);
         hdc=BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// ------------------------------- caption strip
#if IBSH_SKIN != IBSH_SKIN_STANDART
#if FALSE
      pen = NULL;
      if(SUCCEEDED(retc)) if(m_aPenScheme[KpCaptionColor] == NULL))
      {
         pen = CreatePen(PS_SOLID, 1, GetSysColor(ColorMap[KpCaptionColor]));
         if(pen == NULL)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
//       if(GetObject(pen?pen:lzdsh_dlg->m_aPenScheme[KpCaptionColor], sizeof(log_pen), &log_pen))
         {
//          if(SUCCEEDED(retc))
            {
               rect.left=LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR;
               rect.top=LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR;
               rect.right=LZDSH_ABOUT_WND_DX-LZDSH_WND_BORDER_WDT*2-LZDSH_WND_BORDER_COR*2+1;
               rect.bottom=LZDSH_WND_BORDER_WDT+LZDSH_ABOUT_WND_MARGIN_UP+1;
            }

            brush = NULL;
            brush = CreateSolidBrush(KpColorSchemeLocal[KpCaptionColor]);

            if(SUCCEEDED(retc))
               if(!FillRect(hdc, &rect, brush)) // log_pen.elpColor)))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

//          if(brush) if(!DeleteObject(brush))
//             /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            brush = NULL;
         }
//       else
//          retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

#if FALSE
      if(pen!=NULL)
         if(!DeleteObject(pen))
         {
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
      pen=NULL;
#endif
#endif

// ------------------------------- window and control borders
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, 0, 0, LZDSH_ABOUT_WND_DX, LZDSH_ABOUT_WND_DY, KP_WND_RAISED_BORDER, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

// ------------------------
//    if(hdc!=NULL) ReleaseDC(hwndDlg, hdc);
//    hdc=NULL;
      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      break;


// ---------------------------------------   drag window
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)

#if FALSE // #ifdef Debug
   case WM_LBUTTONDOWN:
{
char str_buf[100];
sprintf(str_buf, "WM_LBUTTONDOWN %d", hwndDlg);
KP_TRACE(str_buf);
}
      break;
#endif

   case WM_LBUTTONUP:
      if(theAboutDialog.m_bCaptured)
      {
         ReleaseCapture();
         theAboutDialog.m_bCaptured=False;
      }

      theAboutDialog.m_iMouseX=(-1);
      theAboutDialog.m_iMouseY=(-1);
      break;

   case WM_CAPTURECHANGED:
// KP_TRACE("WM_CAPTURECHANGED");
      theAboutDialog.m_iMouseX=(-1);
      theAboutDialog.m_iMouseY=(-1);
      break;

// case WM_MOUSEFIRST:
   case WM_MOUSEMOVE:
// ----------------- lango stumdymas
      if((wParam&MK_LBUTTON)!=0)
      {
         ix=GET_X_LPARAM /* LOWORD */(lParam)+theAboutDialog.m_iWndCurX;
         iy=GET_Y_LPARAM /* HIWORD */(lParam)+theAboutDialog.m_iWndCurY;

         dx=ix-theAboutDialog.m_iMouseX;
         dy=iy-theAboutDialog.m_iMouseY;

#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "WM_MOUSEMOVE %d %d %d %d %d %d",
   theAboutDialog.m_hDialogWindow,
   theAboutDialog.m_iMouseX, theAboutDialog.m_iMouseY,
   (theAboutDialog.m_hDialogWindow!=NULL),
   (theAboutDialog.m_iMouseX>=0), (theAboutDialog.m_iMouseY>=0));
KP_TRACE(str_buf);
}
#endif

         if(
            (theAboutDialog.m_hDialogWindow!=NULL) &&
            (theAboutDialog.m_iMouseX>=0) && (theAboutDialog.m_iMouseY>=0)
           )
         {

            if(!theAboutDialog.m_bCaptured)
            {
               SetCapture(theAboutDialog.m_hDialogWindow);
               theAboutDialog.m_bCaptured=True;
            }

            theAboutDialog.m_iWndCurX+=dx;
            theAboutDialog.m_iWndCurY+=dy;

#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "WM_MOUSEMOVE ---- %d %d", theAboutDialog.m_iWndCurX, theAboutDialog.m_iWndCurY);
KP_TRACE(str_buf);
}
#endif

            if(!SetWindowPos(theAboutDialog.m_hDialogWindow, HWND_TOP,
               theAboutDialog.m_iWndCurX, theAboutDialog.m_iWndCurY,
               LZDSH_ABOUT_WND_DX, LZDSH_ABOUT_WND_DY,
               0))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
         }

         theAboutDialog.m_iMouseX=ix;
         theAboutDialog.m_iMouseY=iy;
      }
      break;
#endif

// ---------------------------------------
   case WM_COMMAND:
      switch(retp)
      {
//-----------------
      case IDOK:
         endfl = True;
         break;

      case IDCANCEL:
         endfl = True;
//       PostQuitMessage(IDOK);
//       PostMessage(NULL, WM_CLOSE, 0, 0);
         break;

//    case KP_ID_EXIT:
// KpMsgOut("KP_ID_EXIT");
//       PostQuitMessage(IDOK);
//       endfl=True;
//       break;

      }

//wParam
//    The low-order word is the list box identifier.
//    The high-order word is the notification message.
//lParam
//    Handle to the list box.
      break;

   case WM_DESTROY:
      endfl = True;
      break;

   case WM_CLOSE:
      endfl = True;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
      case IDCANCEL: retc = KP_E_CANCEL; break;
      case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl = True;
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
// --------------------------
//       if(msg.hwnd == theAboutDialog.m_hDialogWindow)
         {
            if(theAboutDialog.m_hDialogWindow != NULL)
            {
               if(!(::DestroyWindow(theAboutDialog.m_hDialogWindow)))
               {
#ifdef Debug
// jau buna uzsidares
//                retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
               }
            }
            theAboutDialog.m_hDialogWindow = NULL;
         }

//--------------------------
      theAboutDialog.m_bWindowOpen = False;

// -------------------------
#ifdef IBSH_RES_MODE_XGECKO
// kažko iškviečia 20 kartų
      if(SUCCEEDED(retc)) /* if(iWindowsVersion < WinVistaC) */ retc = lzdsh_dlg->RefreshResCtrl(); // kažko išvalo rezultato langą
#endif

//--------------------------
//    PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if(/* (uMsg!=WM_QUIT) && */ FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
