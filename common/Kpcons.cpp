//----------------------------------
// kpcons.cpp
// Win32 console implementation
//


// ================================================== definitions

#include "stdafx.h"

#include "envir.h"

#if (Envir!=MSWin32Mfc)
#include <stdio.h>
#endif
#include <string.h>
#include <string>
#include <fstream>
#if ((Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32Con) || (Envir==MSWin32ConMfc))
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpmsg.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"


// =========================================
COLORREF KpConsoleColorScheme[KpNumOfShadows3]={
RGB_White, // KpShadowNorm   // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black,     // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor,   // URL nuorodos spalva
};


// ========================================= KpConsole implementation
KpConsole::KpConsole(void)
{
#if TRUE // Envir == MSWin32
int ii;
#endif

   m_lhOpenResult = S_OK;
   m_hInstance = NULL;
   m_lpszFNameBuf[0] = Nul;
   m_pLogFile = NULL;
   m_bRefreshFlg = False;

   m_hWndHandle = NULL;
   m_hDisplayCtrl = NULL;

   m_iKpCtrlStyle = KPW_CONTROL_STYLE_NORMAL;

   m_iNumOfCols = KPW_CONSOLE_CTRL_NUMOFCOLUMNS;
   m_iNumOfRows = KPW_CONSOLE_CTRL_NUMOFLINES;

#if TRUE // Envir == MSWin32
   for(ii = 0; ii < KPW_CONSOLE_CTRL_NUMOFLINES; ii++)
   {
      for(int jj = 0; jj < KPW_CONSOLE_CTRL_NUMOFCOLUMNS; jj++)
         m_lpszaConsoleBuf[ii][jj] = Spc;
      m_lpszaConsoleBuf[ii][KPW_CONSOLE_CTRL_NUMOFCOLUMNS] = Nul;
   }
#endif
   m_iCurConsoleBufRow = 0;

   m_iCurX = 0;
   m_iCurY = KPW_CONSOLE_CTRL_NUMOFLINES-1;

   m_bCurOn = True;

   m_iKbBufTail = 0;
   m_iKbBufHead = 0;

   m_hRefreshTimer = 0;

   m_ColorScheme = KpConsoleColorScheme;
PutLogMessage_("KpConsole::KpConsole() %x", m_ColorScheme);
}


// --------------------------------------
KpConsole::~KpConsole(void)
{
   KpConsoleDestructor();
}


// --------------------------------------
HRESULT KpConsole::KpConsoleDestructor(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

   if(m_hRefreshTimer != 0)
   {
      if(!::KillTimer(m_hWndHandle, m_hRefreshTimer /* KPW_CONSOLE_REFRESH_TIMER */))
      {
//       retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//       if(SUCCEEDED(retc)) retc=retc0;
      }
      m_hRefreshTimer = 0;
   }

   retc0 = KpWndDestructor();
   if(SUCCEEDED(retc)) retc = retc0;

   if(m_pLogFile != NULL)
   {
      if(fclose(m_pLogFile)!=0)
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
      m_pLogFile = NULL;
   }

return(retc);
}


// --------------------------------------
HRESULT KpConsole::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------
HRESULT KpConsole::SetColorScheme(COLORREF *pColorScheme)
{
   m_ColorScheme = pColorScheme;
return(S_OK);
}


HRESULT KpConsole::SetCtrlStyle(KpControlStyles iKpCtrlStyle)
{
   m_iKpCtrlStyle = iKpCtrlStyle;
return(S_OK);
}


// --------------------------------------
HRESULT KpConsole::Init(HINSTANCE hInstance, const unsigned char *lpszLogFileName, const unsigned char *lpszHat)
{
HRESULT retc = S_OK;
#if FALSE // Envir==MSWin32Mfc
CString str1;
#else
unsigned char str_buf[KP_MAX_FNAME_LEN + 100];
#endif
#if TRUE // Envir==MSWin32
WNDCLASSEX wcx;
int ii;
int wnd_x;
int wnd_y;
// CREATESTRUCT cst;
#endif

   m_hInstance = hInstance;
   hKpInstance = hInstance;

   retc = GetOpenResult();

   m_lpszFNameBuf[0] = Nul;
   m_pLogFile = NULL;

   KP_ASSERT((m_iKpCtrlStyle >= 0) && (m_iKpCtrlStyle < KPW_NUM_OF_CONTROL_STYLES_0), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      if(lpszLogFileName != NULL)
      {
         strncpy(m_lpszFNameBuf, lpszLogFileName, KP_MAX_FNAME_LEN);
         m_lpszFNameBuf[KP_MAX_FNAME_LEN] = Nul;
      }
      else
         if(m_iWndType == TYP_Trace)
            retc = TvUniFname.Generate(m_lpszFNameBuf);
   }

   if((strlen(m_lpszFNameBuf) != 0) && SUCCEEDED(retc))
   {
      m_pLogFile = fopen((const char *)m_lpszFNameBuf, "w");
//    KP_ASSERT(m_pLogFile != NULL, KP_E_DIR_ERROR, null, False);
   }

#if FALSE // Envir==MSWin32Mfc
   if(SUCCEEDED(retc)) if((lpszHat == null) && (strlen(m_lpszFNameBuf) != 0))
   {
      KP_ASSERT(strlen(KP_MSG_LOG_STARTED) + strlen(m_lpszFNameBuf) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, KP_MSG_LOG_STARTED, m_lpszFNameBuf);
         retc = AddString(str_buf);
      }
   }

#elif TRUE // Envir==MSWin32
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "KPCONSOLE";
      wcx.lpfnWndProc   = (WNDPROC)KpConsoleDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(m_hInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION /* IDI_ICON1 */) );
      wcx.hIconSm       = LoadIcon(m_hInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION /* IDI_ICON1 */));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
// nepavyko uzregistruot - reiskia jau yra ???
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc)) retc = GetWindowsCount(&ii);
   if(SUCCEEDED(retc))
   {
      wnd_x = KPW_CONSOLE_WND_X - ii * 80;
      wnd_y = KPW_CONSOLE_WND_Y - ii * 60;
   }

   if(SUCCEEDED(retc))
   {
#if FALSE
      cst.lpCreateParams = this;
      cst.hInstance = m_hInstance;
      cst.hMenu = 0;
      cst.hwndParent = HWND_DESKTOP;
      cst.cy = KPW_CONSOLE_WND_HGT(m_iStyle);
      cst.cx = KPW_CONSOLE_WND_WDT(m_iStyle);
      cst.y = wnd_y;
      cst.x = wnd_x;
      cst.style = WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME;
      cst.lpszName = "Console";
      cst.lpszClass = "KPCONSOLE";
      cst.dwExStyle = 0;
#endif

      KP_ASSERT(strlen(KP_MSG_CONS_TITLE) + strlen(lpszProdName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) sprintf((char *)str_buf, KP_MSG_CONS_TITLE, lpszProdName);

      if(SUCCEEDED(retc))
      {
         m_hWndHandle = CreateWindowEx
            (
               0,                      // DWORD dwExStyle,      // extended window style
               "KPCONSOLE",
               (const char *)((lpszHat != null)?lpszHat:str_buf),              // LPCTSTR lpWindowName, // pointer to window name
               WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
               wnd_x,                  // CW_USEDEFAULT,          // int x,                // horizontal position of window
               wnd_y,                  // CW_USEDEFAULT,          // int y,                // vertical position of window
               KPW_CONSOLE_WND_WDT(m_iKpCtrlStyle), // int nWidth,           // window width
               KPW_CONSOLE_WND_HGT(m_iKpCtrlStyle), // int nHeight,          // window height
               HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
               0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
               m_hInstance,
               this /* &cst */         // LPVOID lpParam        // pointer to window-creation data
            );

         if(m_hWndHandle==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc)) if((lpszHat == null) && (strlen(m_lpszFNameBuf) != 0))
   {
      KP_ASSERT(strlen(KP_MSG_LOG_STARTED) + strlen(m_lpszFNameBuf) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, KP_MSG_LOG_STARTED, m_lpszFNameBuf);
         retc = AddString(str_buf);
      }
   }

#else
   if(SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#endif

   if(SUCCEEDED(retc)) retc = Refresh();

return(retc);
}


// -------------------------------------------
#if TRUE // Envir==MSWin32
BOOL CALLBACK KpConsoleDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
BOOL retw = FALSE;
KpConsole *cur_wnd = NULL;
CREATESTRUCT *csp = NULL;
unsigned char *tmp_disp_buf = NULL;
// DWORD thread_id;
// int msg_id=RegisterWindowMessage("KP_CREATE");
HFONT font = NULL;

#ifndef KPCONS_OLD_STYLE
HDC hdc = NULL;
PAINTSTRUCT ps;
#endif

   if(SUCCEEDED(retc)) retc = GetCurWindow((KpWnd **)(&cur_wnd), hwndDlg);

#ifdef Debug
// unsigned char str_buf[100];

   if(SUCCEEDED(retc))
   {
      if(cur_wnd != NULL)
      {
//       if(cur_wnd->m_hInstance==NULL)
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//       if(SUCCEEDED(retc))
         {
            if(cur_wnd->m_iWndType == TYP_KpConsole)
            {
               switch(uMsg)
               {
               case WM_NCHITTEST:
               case WM_SETCURSOR:
               case WM_CTLCOLOREDIT:
                  break;
               case WM_NCMOUSEMOVE:
// sprintf((char *)str_buf, "C %x   WM_NCMOUSEMOVE   %x %x", hwndDlg, wParam, lParam); KP_TRACE1(str_buf);

//                if(!PostMessage(NULL, WM_KP_CREATE /* WM_CREATE */, 0, 0))
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

//                thread_id=GetCurrentThreadId();
//                if(!PostThreadMessage(thread_id, 0xFFFF /* WM_CREATE */, 0, 0))
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

                  break;
               case WM_CREATE:
// sprintf((char *)str_buf, "C %x   WM_CREATE        %x %x", hwndDlg, wParam, lParam); KP_TRACE1(str_buf);
                  break;
               case WM_KP_CREATE:
// sprintf((char *)str_buf, "C %x   WM_KP_CREATE     %x %x", hwndDlg, wParam, lParam); KP_TRACE1(str_buf);
                  break;
               case WM_INITDIALOG:
// sprintf((char *)str_buf, "C %x   WM_INITDIALOG    %x %x", hwndDlg, wParam, lParam); KP_TRACE1(str_buf);
                  break;
               case WM_CLOSE:
// sprintf((char *)str_buf, "C %x   WM_CLOSE         %x %x", hwndDlg, wParam, lParam); KP_TRACE1(str_buf);
                  break;
               case WM_CHAR:
// sprintf((char *)str_buf, "C %x   WM_CHAR          %x %x", hwndDlg, wParam, lParam); KP_TRACE1(str_buf);
                  break;
               default:
// sprintf((char *)str_buf, "C %x   %8x          %x %x", hwndDlg, uMsg, wParam, lParam); KP_TRACE1(str_buf);
                  break;
               }
            }
         }
      }
//    else
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
#endif

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
      if(SUCCEEDED(retc)) csp = (LPCREATESTRUCT)lParam;
      KP_ASSERT(csp != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) cur_wnd = (KpConsole *)csp->lpCreateParams;
      KP_ASSERT(cur_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);

#ifdef KPCONS_OLD_STYLE
      KP_NEWA(tmp_disp_buf, unsigned char, KPW_CONSOLE_CTRL_NUMOFLINES * KPW_CONSOLE_CTRL_NUMOFCOLUMNS + 1);
      if(SUCCEEDED(retc))
      {
         memset(tmp_disp_buf, Spc, KPW_CONSOLE_CTRL_NUMOFLINES * KPW_CONSOLE_CTRL_NUMOFCOLUMNS);
         tmp_disp_buf[KPW_CONSOLE_CTRL_NUMOFLINES * KPW_CONSOLE_CTRL_NUMOFCOLUMNS] = Nul;
         retc = KpCreateEdit(cur_wnd->m_hInstance, hwndDlg, &cur_wnd->m_hDisplayCtrl, tmp_disp_buf /* KPW_CONSOLE_CTRL_INIT_STR */, KPW_CONSOLE_CTRL_X, KPW_CONSOLE_CTRL_Y, cur_wnd->m_iKpCtrlStyle, WS_EX_CLIENTEDGE, 0 /* ES_READONLY */, KPW_CONSOLE_CTRL_NUMOFLINES);
      }
      KP_ASSERT(cur_wnd->m_hDisplayCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);
      KP_DELETEA(tmp_disp_buf);

      KP_ASSERT(PostMessage(NULL, WM_KP_CREATE /* WM_CREATE */, 0, (LPARAM)cur_wnd), KP_E_SYSTEM_ERROR, GetLastError(), False);

      if(SUCCEEDED(retc))
      {
         cur_wnd->m_hRefreshTimer = SetTimer(hwndDlg, KPW_CONSOLE_REFRESH_TIMER, KPW_CONSOLE_REFRESH_TIMEOUT, KpConsoleRefreshTimer);
         KP_ASSERT(cur_wnd->m_hRefreshTimer !=0, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }
#endif
      break;

   case WM_INITDIALOG:
      retw = TRUE;
      break;

#ifndef KPCONS_OLD_STYLE
   case WM_PAINT:
      KP_ASSERT(cur_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(cur_wnd->m_iWndType == TYP_KpConsole, KP_E_SYSTEM_ERROR, null, True);

      hdc = NULL;
      if(SUCCEEDED(retc)) hdc = BeginPaint(hwndDlg, &ps);
      KP_ASSERT(hdc != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc)) retc = KpDrawRect(hdc, KPW_CONSOLE_CTRL_X, KPW_CONSOLE_CTRL_Y,
         KPW_CONSOLE_CTRL_X + KPW_CONSOLE_CTRL_WDT(cur_wnd->m_iKpCtrlStyle),
         KPW_CONSOLE_CTRL_Y + KPW_CONSOLE_CTRL_HGT(cur_wnd->m_iKpCtrlStyle),
         KP_WND_SUNKEN_BORDER, cur_wnd->m_ColorScheme); // KpstEdiDialogPtr->m_aPenScheme);

      if(SUCCEEDED(retc)) retc = CrFont(&font, cur_wnd->m_iKpCtrlStyle);
      if(SUCCEEDED(retc)) SelectObject(hdc, font);

      if(SUCCEEDED(retc)) SetTextColor(hdc, cur_wnd->m_ColorScheme[KpShadowDark]);
      if(SUCCEEDED(retc)) SetBkColor(hdc, cur_wnd->m_ColorScheme[KpShadowNorm]);

      if(SUCCEEDED(retc))
      {
int ii1 = ps.rcPaint.top - KPW_CONSOLE_CTRL_Y - KPW_CTRL_BORDER_WDT;
         if(ii1 < 0) ii1 = 0;
         ii1 /= iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle];

int ii2 = ps.rcPaint.bottom - KPW_CONSOLE_CTRL_Y - KPW_CTRL_BORDER_WDT;
         if(ii2 < 0) ii2 = 0;
         ii2 /= iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle];
         ii2++;
         if(ii2 > KPW_CONSOLE_CTRL_NUMOFLINES) ii2 = KPW_CONSOLE_CTRL_NUMOFLINES;

int jj1 = ps.rcPaint.left - KPW_CONSOLE_CTRL_X - KPW_CTRL_BORDER_WDT;
         if(jj1 < 0) jj1 = 0;
         jj1 /= KPW_CONSOLE_CHAR_WDT(cur_wnd->m_iKpCtrlStyle);

int jj2 = ps.rcPaint.right - KPW_CONSOLE_CTRL_X - KPW_CTRL_BORDER_WDT;
         jj2 /= KPW_CONSOLE_CHAR_WDT(cur_wnd->m_iKpCtrlStyle);
         jj2++;
         if(jj2 > KPW_CONSOLE_CTRL_NUMOFCOLUMNS) jj2 = KPW_CONSOLE_CTRL_NUMOFCOLUMNS;

         for(int ii = ii1; (ii < ii2) && SUCCEEDED(retc); ii++)
         {
int row_len = strlen(cur_wnd->m_lpszaConsoleBuf[ii]);
            for(int jj = jj1; (jj < jj2) && SUCCEEDED(retc); jj++)
            {
RECT char_rect;
               char_rect.left = KPW_CONSOLE_CHAR_HPOS(cur_wnd->m_iKpCtrlStyle, jj);
               char_rect.top = KPW_CONSOLE_CHAR_VPOS(cur_wnd->m_iKpCtrlStyle, ii);
               char_rect.right = char_rect.left + KPW_CONSOLE_CHAR_WDT(cur_wnd->m_iKpCtrlStyle);
               char_rect.bottom = char_rect.top + iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle];
               retc = KpDrawBox(hdc, char_rect, KpShadowNorm /* KpShadowBackground */, cur_wnd->m_ColorScheme);

               if(SUCCEEDED(retc))
               {
char out_str[2] = { Spc, Nul };
                  if(jj < row_len) out_str[0] = cur_wnd->m_lpszaConsoleBuf[ii][jj];
                  TextOut(hdc, char_rect.left, char_rect.top, out_str, 1); // strlen(out_str));
               }
            }
         }
      }

      EndPaint(hwndDlg, &ps);

      if(font != NULL) DeleteObject(font);

      break;
#endif

   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case IDCANCEL:
         PostQuitMessage(IDCANCEL);
         break;
      }
      break;

   case WM_CLOSE:
// unsigned char str_buf[200];
// SendMessage(hKpConsoleCtrl, WM_GETTEXT, 100, (LPARAM)str_buf);

      PostQuitMessage(IDCANCEL);
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc))
   {
//    Sleep(3000);
      PostQuitMessage(IDABORT);
   }

return(retw);
}
#endif


// ------------------------------------
#ifdef KPCONS_OLD_STYLE
VOID CALLBACK KpConsoleRefreshTimer(HWND hwndDlg, UINT, UINT, DWORD)
{
HRESULT retc=S_OK;
KpConsole *cur_wnd=NULL;

   if(SUCCEEDED(retc)) retc=GetCurWindow((KpWnd **)(&cur_wnd), hwndDlg);

// if((cur_wnd==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   if((cur_wnd!=NULL) && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc))
//       if(!KillTimer(hwndDlg, cur_wnd->m_hRefreshTimer /* KPW_CONSOLE_REFRESH_TIMER */))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) if(cur_wnd->m_bRefreshFlg)
      {
         cur_wnd->m_bRefreshFlg=False;
         retc=cur_wnd->DoRefresh();
      }
   }
}
#endif


// --------------------------------------------- console keyboard input
HRESULT KpConsole::wkbtobuf(unsigned char iInChar)
{
HRESULT retc=S_OK;
int new_head;

   m_iaKbBuf[m_iKbBufHead] = iInChar;

   new_head = m_iKbBufHead;
   new_head = (new_head + 1) % KPW_KB_BUF_SIZE;
   KP_ASSERT(new_head != m_iKbBufTail, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) m_iKbBufHead = new_head;

return(retc);
}


int KpConsole::wgetchar(void)
{
int ret_char;

   ret_char = Nul;

   if(m_iKbBufTail != m_iKbBufHead)
   {
      ret_char = m_iaKbBuf[m_iKbBufTail];
      m_iKbBufTail = (m_iKbBufTail + 1) % KPW_KB_BUF_SIZE;
   }

return(ret_char);
}


unsigned char *KpConsole::wgetstr(unsigned char *buf)
{
unsigned char *pntd;
int in_ch;

   pntd = buf;

   if(buf != NULL)
   {
      do
      {
         in_ch = wgetchar();
         if(in_ch == Lf) in_ch = Nul;

         if(pntd-buf >= KPW_KB_BUF_SIZE) in_ch = Nul;
         if(in_ch) *(pntd++) = in_ch;

      } while(in_ch);

      *pntd = Nul;
   }

return(pntd);
}


// --------------------------------------------- console settings
HRESULT KpConsole::wbcolor(KpColor /* col */, KpColor /* bcol */, KpColor /* fcol */)
{
HRESULT retc=S_OK;

// !!!

return(retc);
}


HRESULT KpConsole::wcrsor(int /* onflg */)
{
HRESULT retc=S_OK;

// !!!

return(retc);
}


HRESULT KpConsole::wloc(int xx,int yy)
{
HRESULT retc=S_OK;

   m_iCurX = xx; if(m_iCurX >= KPW_CONSOLE_CTRL_NUMOFCOLUMNS) m_iCurX = KPW_CONSOLE_CTRL_NUMOFCOLUMNS - 1;
   m_iCurY = yy; if(m_iCurY >= KPW_CONSOLE_CTRL_NUMOFLINES) m_iCurY = KPW_CONSOLE_CTRL_NUMOFLINES - 1;

return(retc);
}


// --------------------------------------------- console text output
#if TRUE // Envir == MSWin32
HRESULT KpConsole::DoRefresh(void)
{
HRESULT retc = S_OK;
#ifdef Debug
// char buf_out[100];
#endif

#ifdef KPCONS_OLD_STYLE
unsigned char str_buf[(KPW_CONSOLE_CTRL_NUMOFLINES+2)*KPW_CONSOLE_CTRL_NUMOFCOLUMNS+1];

   if(m_hDisplayCtrl == NULL)
   {
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   else
   {
      if(SUCCEEDED(retc))
      {
         str_buf[0] = Nul;
         for(int ii = 0; ii < KPW_CONSOLE_CTRL_NUMOFLINES; ii++)
         {
            strcat(str_buf, m_lpszaConsoleBuf[(m_iCurConsoleBufRow + ii) % KPW_CONSOLE_CTRL_NUMOFLINES]);
//          strcat(str_buf, KPW_CONSOLE_CTRL_INIT_STR+strlen(m_lpszaConsoleBuf[(m_iCurConsoleBufRow+ii)%KPW_CONSOLE_CTRL_NUMOFLINES]));
            strcat(str_buf, "\r\n");
         }
         SendMessage(m_hDisplayCtrl, WM_SETTEXT, 0, (LPARAM)str_buf);

// extern KpConsole KpTraceWindow;
// if(this!=&KpTraceWindow /* this->m_iStyle!=TYP_Trace */){ sprintf(buf_out, "%d", strlen(str_buf)); KP_TRACE(buf_out); }
      }
   }
#else
#  if FALSE
int xx_sav = m_iCurX;
int yy_sav = m_iCurY;

   if(SUCCEEDED(retc))
      for(int ii = 0; (ii < KPW_CONSOLE_CTRL_NUMOFLINES) && SUCCEEDED(retc); ii++)
         for(int jj = 0; (jj < KPW_CONSOLE_CTRL_NUMOFCOLS) && SUCCEEDED(retc); jj++)
         {
            retc = wloc(ii, jj);
            if(SUCCEEDED(retc))
            {
unsigned char out_ch = m_lpszaConsoleBuf[(m_iCurConsoleBufRow + ii) % KPW_CONSOLE_CTRL_NUMOFLINES])[jj];
               if(out_ch != Nul) retc = wputchar(out_ch);
               else
               {
                  retc = wclreol();
                  break;
               }
            }
         }

   if(SUCCEEDED9retc)) retc = wloc(xx_sav, yy_sav);
#  endif

RECT rect;
   rect.left = KPW_CONSOLE_CTRL_X;
   rect.top = KPW_CONSOLE_CTRL_Y;
   rect.right = KPW_CONSOLE_CTRL_X + KPW_CONSOLE_CTRL_WDT(m_iKpCtrlStyle);
   rect.bottom = KPW_CONSOLE_CTRL_Y + KPW_CONSOLE_CTRL_HGT(m_iKpCtrlStyle);

   RedrawWindow(m_hWndHandle, &rect, NULL, RDW_INVALIDATE);

#endif

return(retc);
}
#endif

HRESULT KpConsole::Refresh(void)
{
#ifdef KPCONS_OLD_STYLE
   m_bRefreshFlg = True;
return(S_OK);
#else
return(DoRefresh());
#endif
}


// ----------------------
#if FALSE // Envir==MSWin32Mfc
HRESULT KpConsole::AddString(CString &sItem)
{
HRESULT retc=S_OK;
DWORD err;
int err1;

   err1 = CListBox::AddString(sItem);
   KP_ASSERT(err1 != LB_ERR, KP_E_SYSTEM_ERROR, err = GetLastError(), True);
   KP_ASSERT(err1 != LB_ERRSPACE, KP_E_OUTOFMEM, null, True);

   if((m_pLogFile!=NULL) && SUCCEEDED(retc))
   {
      fputs(sItem, m_pLogFile);
      fputs("\n", m_pLogFile);
      KP_ASSERT((!ferror(m_pLogFile)) && (!feof(m_pLogFile)), KP_E_FERROR, null, True);
   }

return(retc);
}
#endif


// ----------------------------
HRESULT KpConsole::AddStringNoMessage(const unsigned char *lpszoutStr /* LPCTSTR lpszItem */)
{
HRESULT retc=S_OK;
#if FALSE // Envir==MSWin32Mfc
int err1;
#endif

// ----------------------------
#if FALSE // Envir==MSWin32Mfc
   err1 = CListBox::AddString((const char *)lpszoutStr);
   if(err1 == LB_ERR)
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   if(err1 == LB_ERRSPACE)
      retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);

// ----------------------------
#elif TRUE // Envir==MSWin32

   if((m_iCurConsoleBufRow < 0) || (m_iCurConsoleBufRow >= KPW_CONSOLE_CTRL_NUMOFLINES))
      m_iCurConsoleBufRow = 0;

   strncpy(m_lpszaConsoleBuf[m_iCurConsoleBufRow], lpszoutStr, KPW_CONSOLE_CTRL_NUMOFCOLUMNS);
   m_lpszaConsoleBuf[m_iCurConsoleBufRow][KPW_CONSOLE_CTRL_NUMOFCOLUMNS] = Nul;

   m_iCurConsoleBufRow++;
   m_iCurConsoleBufRow %= KPW_CONSOLE_CTRL_NUMOFLINES;

// ---------------------------------
   if(SUCCEEDED(retc)) retc = Refresh();

// ----------------------------
#else
   retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#endif

// ----------------------------
   if((m_pLogFile != NULL) && SUCCEEDED(retc))
   {
      fputs((const char *)lpszoutStr, m_pLogFile);
      fputs("\n", m_pLogFile);
      if(ferror(m_pLogFile) || feof(m_pLogFile))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


HRESULT KpConsole::AddString(const unsigned char *lpszOutStr)
{
HRESULT retc=S_OK;
unsigned char *str_buf=NULL;
const unsigned char *pnts=NULL;
unsigned char *pntd=NULL;

   if((lpszOutStr == NULL) && SUCCEEDED(retc))
      retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   KP_NEWA(str_buf, unsigned char, strlen(lpszOutStr) + 1);

   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszOutStr);
      pnts = str_buf;
      do
      {
         pntd = strchr(pnts, '\n');
         if(pntd)
         {
            *pntd++ = Nul;
            retc = AddStringNoMessage(pnts);

            if(SUCCEEDED(retc)) pnts = pntd;
         }
      } while(pntd && SUCCEEDED(retc));
   }

   if(SUCCEEDED(retc)) if((*pnts || (*lpszOutStr == Nul)) && (strcmp(pnts, "\r") != 0))
      retc = AddStringNoMessage(pnts);

   KP_DELETEA(str_buf);

return(retc);
}


HRESULT KpConsole::AddString(const char *lpszoutStr)
{
return(AddString((const unsigned char *)lpszoutStr));
}


HRESULT KpConsole::AddString(KpString vStr)
{
return(AddString(vStr.ExtractUnsignedValueA()));
}


// ----------------------------
HRESULT KpConsole::wputchar(int iOutCh)
{
HRESULT retc=S_OK;
int cur_buf_row;
int ii;
int ll;

   cur_buf_row = (m_iCurConsoleBufRow + m_iCurY) % KPW_CONSOLE_CTRL_NUMOFLINES;

   switch(iOutCh)
   {
   case Lf:
      m_iCurX = 0;
      if(m_iCurY < KPW_CONSOLE_CTRL_NUMOFLINES - 1) m_iCurY++;
      else AddString((const unsigned char *)"");
      break;

   case Bs:
      if(m_iCurX > 0)
      {
         m_iCurX--;
#ifdef KPCONS_OLD_STYLE
         m_lpszaConsoleBuf[cur_buf_row][m_iCurX] = Spc;
         retc = Refresh();
#else
         retc = wputchar(Spc);
         m_iCurX--;
#endif
      }
      break;

   case Ff:
      m_iCurX = 0;
      m_iCurY = 0;
      for(ii = 0; ii < KPW_CONSOLE_CTRL_NUMOFLINES; ii++)
         m_lpszaConsoleBuf[ii][0] = Nul;
      retc = Refresh();
      break;

   default:
      if((iOutCh != Cr) && (m_iCurX < KPW_CONSOLE_CTRL_NUMOFCOLUMNS))
      {
         ll = strlen(m_lpszaConsoleBuf[cur_buf_row]);
         if(ll < m_iCurX) for(ii = ll; ii < m_iCurX; ii++)
            m_lpszaConsoleBuf[cur_buf_row][ii] = Spc;
         if(ll <= m_iCurX) m_lpszaConsoleBuf[cur_buf_row][m_iCurX + 1] = Nul;
         m_lpszaConsoleBuf[cur_buf_row][m_iCurX] = iOutCh;

#ifdef KPCONS_OLD_STYLE
         m_iCurX++;
         retc = Refresh();
#else
RECT rect;
         rect.left = KPW_CONSOLE_CHAR_HPOS(m_iKpCtrlStyle, m_iCurX);
         rect.top = KPW_CONSOLE_CHAR_VPOS(m_iKpCtrlStyle, m_iCurY);
         rect.right = rect.left + KPW_CONSOLE_CHAR_WDT(m_iKpCtrlStyle);
         rect.bottom = rect.top + iaCtrlRowHeights[iWindowsVersionCut][m_iKpCtrlStyle];

         RedrawWindow(m_hWndHandle, &rect, NULL, RDW_INVALIDATE);

         m_iCurX++;
#endif
      }
      break;
   }

// ---------------------------------
// if(SUCCEEDED(retc)) retc=Refresh();

return(retc);
}

// ----------------------------
HRESULT KpConsole::wputstr(const unsigned char *lpszOutStr)
{
HRESULT retc=S_OK;
int cur_buf_row;
const unsigned char *pnts;

   if(lpszOutStr != NULL)
   {
      cur_buf_row = (m_iCurConsoleBufRow + m_iCurY) % KPW_CONSOLE_CTRL_NUMOFLINES;

      pnts = lpszOutStr;

      while(*pnts)
      {
         if(*pnts != Lf)
         {
            if(*pnts != Cr)
            {
               if(m_iCurX < KPW_CONSOLE_CTRL_NUMOFCOLUMNS)
                  m_lpszaConsoleBuf[cur_buf_row][m_iCurX++] = (*pnts);
            }
            else m_iCurX = 0;
         }
         else
         {
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, ">>>%d,%d<<<", m_iCurY, KPW_CONSOLE_CTRL_NUMOFLINES);
wputstr(str_buf);
#endif
            m_iCurX = 0;
            if(m_iCurY < KPW_CONSOLE_CTRL_NUMOFLINES - 1) m_iCurY++;
            else AddString((const unsigned char *)"");

            retc = wputstr(pnts + 1);
            break;
         }
         pnts++;
      }

#ifdef KPCONS_OLD_STYLE
      if(SUCCEEDED(retc)) retc = Refresh();
#endif
   }

return(retc);
}

HRESULT KpConsole::wputstr(const char *lpszOutStr)
{
return(wputstr((const unsigned char *)lpszOutStr));
}


// ----------------------------
HRESULT KpConsole::wclreol(void)
{
HRESULT retc=S_OK;
int cur_buf_row;

   cur_buf_row = (m_iCurConsoleBufRow+m_iCurY) % KPW_CONSOLE_CTRL_NUMOFLINES;

   m_lpszaConsoleBuf[cur_buf_row][m_iCurX] = Nul;

   if(SUCCEEDED(retc)) retc = Refresh();

return(retc);
}
