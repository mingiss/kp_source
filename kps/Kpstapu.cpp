// ---------------------------
// kpstapu.cpp
// common application for program starters
// remove key prompt dialog KPSTREM
//

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <ctype.h>
#include <stdio.h>
#include <string>
// #include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <mmsystem.h>

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

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpmsg.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "kpstedi.h"
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
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstmsg.h"

#if (Envir!=MSWin32) && (Envir!=MSWin32Mfc) && (Envir!=MSWin32Con)
#error Envir!=MSWin32
#endif


// ==============================
// ----------------------------------
HRESULT KpStApp::OpenRemWindow(const unsigned char *lpszHint1)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
HDC dc;
int wnd_x = 0;
int wnd_y = 0;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int prod_name_2_fl = 0;

   KP_ASSERT(m_hInstance, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdName(prod_name);
   if(SUCCEEDED(retc))
   {
      prod_name_2_fl = 0;
      if(strlen(prod_name) >= KPSTLIC_MAX_PROD_NAME_LEN) prod_name_2_fl = 1;
   }

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "KPSTREM",
      wcx.lpfnWndProc   = (WNDPROC)KpStRemDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
      wcx.hIconSm       = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
      wcx.hCursor       = ::LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      dc = GetDC(HWND_DESKTOP);
      if(dc == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      wnd_x = (GetDeviceCaps(dc, HORZRES)-KPSTREM_WND_DX)/2;
      wnd_y = (GetDeviceCaps(dc, VERTRES)-KPSTREM_WND_DY)/2;

      m_hRemDialogWindow = CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPSTREM",
         (char *)KPST_MSG_UNREG_KOD_1,       // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         wnd_x,  // CW_USEDEFAULT, // int x,               // horizontal position of window
         wnd_y,  // CW_USEDEFAULT, // int y,               // vertical position of window
         KPSTREM_WND_DX,          // int nWidth,           // window width
         KPSTREM_WND_DY,          // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         m_hInstance,
         (LPVOID)lpszHint1       // LPVOID lpParam        // pointer to window-creation data
      );
   }

   KP_ASSERT(m_hRemDialogWindow, KP_E_SYSTEM_ERROR, GetLastError(), True);

return(retc);
}


// -----------------------------------------
BOOL CALLBACK KpStRemDialogProc(
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
unsigned char out_buf[KP_MAX_FILE_LIN_WDT+1];
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
#endif
const unsigned char *hint;
LPCREATESTRUCT cst_ptr;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
bool obj_fl = False;
int prod_name_2_fl = 0;
unsigned char *prod_name_2_ptr = null;
HDC hdc = NULL;
PAINTSTRUCT ps;
int lic_high = 0;
unsigned char url_buf[KP_MAX_FNAME_LEN + 1];

   retp = LOWORD(wParam);
   endfl = False;

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
// ------
      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

// ------
      if(SUCCEEDED(retc))
      {
         hint = (unsigned char *)"";
         cst_ptr = (LPCREATESTRUCT)lParam;
         if(cst_ptr != NULL) hint = (const unsigned char *)cst_ptr->lpCreateParams;
      }

// ------
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdNameDec(prod_name);
      if(SUCCEEDED(retc))
      {
         prod_name_2_fl = 0;
         if(strlen(prod_name) >= KPSTLIC_MAX_PROD_NAME_LEN) prod_name_2_fl = 1;

         prod_name_2_ptr = prod_name;
         if(prod_name_2_fl)
         {
            prod_name_2_ptr = prod_name + KPSTLIC_MAX_PROD_NAME_LEN;
            while((*prod_name_2_ptr != Spc) && (prod_name_2_ptr > prod_name)) --prod_name_2_ptr;
            if(*prod_name_2_ptr == Spc) *prod_name_2_ptr++ = Nul;
            else
            {
               while((*prod_name_2_ptr != Spc) && (*prod_name_2_ptr != Nul)) prod_name_2_ptr++;
               if(*prod_name_2_ptr == Spc) *prod_name_2_ptr++ = Nul;
            }
         }
      }

// ------
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniCmdStr(cmd_str);
      if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_PAR)) obj_fl = True;

// ------
      if(SUCCEEDED(retc)) retc = KpCreateIcon(hKpInstance, hwndDlg, NULL, KP_IDI_SETUP_ICON, KPST_SETUP_ICON_X, KPST_SETUP_ICON_Y, KPST_SETUP_ICON_WDT, KPST_SETUP_ICON_WDT, 0);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, prod_name, KPSTREM_HEAD_X, KPSTREM_HEAD_Y, 1, KPW_CONTROL_STYLE_BOLD, 0, 0, NULL);
      if(prod_name_2_fl && SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, prod_name_2_ptr, KPSTREM_HEAD_X, KPSTREM_HEAD2_Y, 1, KPW_CONTROL_STYLE_BOLD, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)KPST_MSG_UNREG, KPSTREM_SUBHEAD_X, KPSTREM_SUBHEAD_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, hint, KPSTREM_EXPL_X, KPSTREM_EXPL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_UNREG_UNSUCC_1, KPSTREM_EXPL_1_X, KPSTREM_EXPL_1_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetRegUrl(null, url_buf, KPST_HTTP_REMOVE);
      if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hKeyUrlButton), KPST_ID_URL, url_buf, KPSTREM_URL_X, KPSTREM_URL_Y, KPSTREM_URL_DX, KPW_BUTTON_HGT, KP_WND_URL, 0, 0);
      if((theKpStAppPtr->m_hKeyUrlButton == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_UNREG_PASTU, KPSTREM_HINT_X, KPSTREM_HINT1_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_UNREG_DARBO_LAIKAS, KPSTREM_HINT_X, KPSTREM_HINT2_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_UNREG_DIKT_TELEF, KPSTREM_HINT_X, KPSTREM_HINT3_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_UNREG_KOD, KPSTREM_CODE_PROMPT_X, KPSTREM_CODE_CTRL_Y, KPSTREM_CODE_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->FormatRemCodeFull(out_buf);

//    if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetLicHighHp11(&lic_high);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->AddHigh(out_buf, lic_high, 12);

//    if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, out_buf, KPSTREM_CODE_CTRL_X, KPSTREM_CODE_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hRemCodeEdit), out_buf, KPSTREM_CODE_CTRL_DX, KPSTREM_CODE_CTRL_X, KPSTREM_CODE_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, ES_READONLY /* WS_DISABLED */, 1);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, (obj_fl?KPST_MSG_OBJ_UNREG_NEGALESIT:KPST_MSG_UNREG_NEGALESIT) /* KPST_MSG_UNREG_TELEF */, KPSTREM_HINT4_X, KPSTREM_HINT4_Y, 1, KPW_CONTROL_STYLE_BOLD /* KPW_CONTROL_STYLE_NORMAL */, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hRemOkButton), IDOK, KP_MSG_GERAI, KPSTREM_OK_BUT_X, KPSTREM_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if((theKpStAppPtr->m_hRemOkButton == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(!SetFocus(theKpStAppPtr->m_hRemOkButton))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      break;

   case WM_CTLCOLOREDIT:
      KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

      if((HWND)lParam == theKpStAppPtr->m_hRemCodeEdit)
      {
         KP_ASSERT(SetBkColor((HDC)wParam, GetSysColor(iaColorMap[KpShadowNorm])) != CLR_INVALID, KP_E_SYSTEM_ERROR, GetLastError(), False);
//       KP_ASSERT(SetTextColor((HDC)wParam, 0xFFFFFF) != CLR_INVALID, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
      break;

   case WM_PAINT:
      KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdName(prod_name);
      prod_name_2_fl = 0;
      if(SUCCEEDED(retc))
         if(strlen(prod_name) >= KPSTLIC_MAX_PROD_NAME_LEN) prod_name_2_fl = 1;

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = BeginPaint(hwndDlg, &ps);
         KP_ASSERT(hdc, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTREM_LINE_X1, KPSTREM_LINE1_Y, KPSTREM_LINE_X2, KPSTREM_LINE1_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTREM_LINE_X1, KPSTREM_LINE2_Y, KPSTREM_LINE_X2, KPSTREM_LINE2_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTREM_LINE_X1, KPSTREM_LINE3_Y, KPSTREM_LINE_X2, KPSTREM_LINE3_Y, KP_WND_SUNKEN, NULL);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_CLOSE:
      endfl=True;
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl=True;
      break;

   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case KPST_ID_URL:
         KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetRegUrl(null, url_buf, KPST_HTTP_REMOVE);
         if(SUCCEEDED(retc)) retc = StartCmdProcess(url_buf, KPST_CUR_DIR, NULL, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
         break;
      case IDOK:
         endfl=True;
         break;
      case IDCANCEL:
         endfl=True;
         break;
      }
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// -------------------------------------------
HRESULT KpStApp::RemCodeInfo(HINSTANCE hInst, const unsigned char *lpszHint1)
{
HRESULT retc = S_OK;
MSG msg;
int retp;
bool endfl = False;
HWND cur_wnd;

   if(hInst==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) m_hInstance=hInst;

// if(SUCCEEDED(retc)) retc = SaveKeyDat();

   if(SUCCEEDED(retc)) retc=OpenRemWindow(lpszHint1);

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      retp=LOWORD(msg.wParam);

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
         endfl=True;
         retc=KP_E_CANCEL;
         break;

      case WM_CHAR:
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId!=0L)
               if(!::PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            break;

         case Tab:
            cur_wnd=GetFocus();

            if(cur_wnd==m_hRemCodeEdit) SetFocus(m_hRemOkButton);
            else if(cur_wnd==m_hRemOkButton) SetFocus(m_hRemCodeEdit);
            break;

         case Enter:
            PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            break;

         case Esc:
            PostMessage(NULL, WM_COMMAND, IDCANCEL, 0L);
            break;
         }
         break;

//    case WM_KEYFIRST:
      case WM_KEYDOWN:
         switch(retp)
         {
         case Shift:
            m_bShiftFl=True;
            break;

         case Dn:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hRemCodeEdit) SetFocus(m_hRemOkButton);
            else SetFocus(m_hRemOkButton);
            break;

         case Up:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hRemCodeEdit);
            else if(cur_wnd==m_hRemOkButton) SetFocus(m_hRemCodeEdit);
            break;
         }
         break;

      case WM_KEYUP:
         if(retp==Shift)
         {
            m_bShiftFl=False;
         }
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
            if(SUCCEEDED(retc)) endfl=True; // (retc!=KP_E_ILL_CODE)
            break;

         case IDCANCEL:
            endfl=True;
            retc=KP_E_CANCEL;
            break;
         }
      }

   } while((!endfl) && SUCCEEDED(retc));

   if(m_hRemDialogWindow!=NULL)
   {
      if(!(::DestroyWindow(m_hRemDialogWindow)))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }
   m_hRemDialogWindow=NULL;

#ifdef Debug
char str_buf[100];
sprintf(str_buf, "%d", retc);
KP_TRACE(str_buf);
#endif

return(retc);
}
