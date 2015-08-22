// ---------------------------
// iBshl.cpp
// el. knygø perþiûros programa
// dialogas
//

// #define IBSHL_TEST_INITIAL_CONTROL_SIZE // tikrinam gecko lango karpymà

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

#include "res_com.h"
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
#include "KpMsHtml.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "xmlsty.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBshr.h"
#include "iBsht.h"

// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif

#if Envir!=MSWin32
// #error Envir!=MSWin32
#endif


// -----------------------------
COLORREF KpColorSchemeBorder[KpNumOfShadows3]={
RGB(240, 240, 240), // RGB_Lightgray, // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Lightgray, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Gray,      // RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
IBSH_TOOL_BCOL, // RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor
};

#if IBSH_SKIN == IBSH_SKIN_MIKO
COLORREF KpColorSchemeToolTip[KpNumOfShadows3]={
RGB_Lightyellow, // RGB(191,191,191), // RGB(236,233,216), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor
};
#endif


// ----------------------------------
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
{
HRESULT retc = S_OK;
#if IBSH_SKIN == IBSH_SKIN_MIKO
#  ifdef IBSH_SAVE_AS
   m_ButSaveAs =  NULL;
#  endif
#endif
}


// ----------------------------------
// TODO: gal kelt á KpPubDlg? Jeigu kartais lzdshl toks pats
HRESULT iBshDlg::OpenWindow(HINSTANCE hInst, bool bShowWindow)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
HCURSOR cur_sav = NULL;
HBRUSH brush = NULL;

//-----------------
   KP_ASSERT(hInst != NULL, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) m_hInstance = hInst;

//-----------------
   if(SUCCEEDED(retc))
   {
      cur_sav=::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
      KP_ASSERT(cur_sav, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

// ------------------------
   if(SUCCEEDED(retc)) retc = RestoreSavedCoords();
   m_iDoRedraw = 1; // perpieðiam net jeigu matmenys ir nepasikeitë po RestoreSavedCoords() (Resize())

// --------------------------------- "iBsh" class
   brush = CreateSolidBrush(IBSH_TOOL_BCOL); // RGB_Gray); // White);

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "iBshCl",
      wcx.lpfnWndProc   = (WNDPROC)iBshDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* m_hInstance */, MAKEINTRESOURCE(KP_IDI_MAIN_ICON));
      wcx.hIconSm       = LoadIcon(NULL /* m_hInstance */, MAKEINTRESOURCE(KP_IDI_MAIN_ICON));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush;

      if(!RegisterClassEx(&wcx))
      {
// gali bûti daugkartiniai áëjimai, be klaidos bus tik pirmas
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

// -------------------------------------
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   if(SUCCEEDED(retc))
   {
#if FALSE // (IBSH_SKIN == IBSH_SKIN_START_GRP)
      m_BgrBmpData.m_iBmpWdt = m_iWndCurDX;
      m_BgrBmpData.m_iBmpHgt = m_iWndCurDY;

      m_BgrBmpData.m_hBitMap =  LoadBitmap(m_hInstance, MAKEINTRESOURCE(KP_IDI_BMP_BCKGRND));
#endif

      m_ButExitBmpData.m_iBmpWdt = IBSH_BUT_WDT;
      m_ButExitBmpData.m_iBmpHgt = IBSH_BUT_WDT;

      m_ButExitBmpData.m_hBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_EXIT_BITMAP)); // (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_EXIT_BITMAP), IMAGE_BITMAP, IBSH_BUT_WDT, IBSH_BUT_WDT, 0);
      m_ButExitBmpData.m_hHover = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_EXIT_LIGHT_BITMAP)); // (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_EXIT_LIGHT_BITMAP), IMAGE_BITMAP, IBSH_BUT_WDT, IBSH_BUT_WDT, 0);
      m_ButExitBmpData.m_hPressed = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_EXIT_SEL_BITMAP)); // (HBITMAP)LoadImage(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_EXIT_SEL_BITMAP), IMAGE_BITMAP, IBSH_BUT_WDT, IBSH_BUT_WDT, 0);

      m_ButMinBmpData.m_iBmpWdt = IBSH_BUT_WDT;
      m_ButMinBmpData.m_iBmpHgt = IBSH_BUT_WDT;

      m_ButMinBmpData.m_hBitMap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_MINIMIZE_BITMAP));
      m_ButMinBmpData.m_hHover = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_MINIMIZE_LIGHT_BITMAP));
      m_ButMinBmpData.m_hPressed = LoadBitmap(m_hInstance, MAKEINTRESOURCE(IBSH_IDI_MINIMIZE_SEL_BITMAP));
   }
#endif

// ----------------------------- m_hDialogWindow
   if(SUCCEEDED(retc))
   {
      m_hDialogWindow = CreateWindowEx
      (
#if IBSH_SKIN == IBSH_SKIN_STANDART
         0,                      // DWORD dwExStyle,      // extended window style
#endif
#if (IBSH_SKIN == IBSH_SKIN_SPLASH) || (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         WS_EX_APPWINDOW,
#endif
         "iBshCl",
         (const char *)m_lpszCaption, // LPCTSTR lpWindowName, // pointer to window name
         m_dwStyle,  // DWORD dwStyle,        // window style
         m_iWndCurX, // IBSH_WND_X, // CW_USEDEFAULT, // int x,               // horizontal position of window
         m_iWndCurY, // IBSH_WND_Y, // CW_USEDEFAULT, // int y,               // vertical position of window
         m_iWndCurDX
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
         + 100
#endif
         , // IBSH_WND_DX, // int nWidth,           // window width
         m_iWndCurDY
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
         + 100
#endif
         , // IBSH_WND_DY, // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         NULL, // m_Menu,       // HMENU hMenu,          // handle to menu, or child-window identifier
         m_hInstance,
         this // NULL           // LPVOID lpParam        // pointer to window-creation data
      );
      KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

// ----------------------------------
   if(SUCCEEDED(retc))
   {
      m_hWndHandle = m_hDialogWindow;
// PutLogMessage_("HWND iBshDlg::OpenWindow() m_hWndHandle %x", m_hWndHandle);
      retc = WndPreg(this, TYP_KpDialog, hKpInstance, NULL, False);
   }

   if(SUCCEEDED(retc)) retc = KpSleep(500, m_hDialogWindow);

//-------------
   if(cur_sav != NULL) ::SetCursor(cur_sav);
   cur_sav = NULL;

//-------------
   if(SUCCEEDED(retc)) retc = OpenWindowLocal();

//-------------
   if(bShowWindow && SUCCEEDED(retc)) retc = ShowDialog();

//-------------
   if(m_RedrawTimer && m_hDialogWindow) if(!KillTimer(m_hDialogWindow, m_RedrawTimer))
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   m_RedrawTimer = 0;

   if(SUCCEEDED(retc))
   {
      m_RedrawTimer = SetTimer(m_hDialogWindow, KP_REDRAW_TIMER, KP_IBSHL_REDRAW_TIMEOUT, NULL);
      if(!m_RedrawTimer)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


// -----------------------------------------
BOOL CALLBACK iBshDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
BOOL retb = False;
bool endfl = False;
UINT msg = 0;
int cmd_id = 0;
HICON icon = NULL;
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP)
HDC hdc = NULL;
PAINTSTRUCT ps;
#endif
bool renew = False;
#ifdef IBSH_SAVE_AS
OPENFILENAME op_fn_str;
unsigned char filters[100];
static unsigned char out_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
KpChar cur_tag;
#endif
const unsigned char *pnts = NULL;
const unsigned char *pnts1 = NULL;
unsigned char *pntd = NULL;
XmlO1 *out_file = NULL;
XmlNode *cur_node = NULL;
KpChar *contents = NULL;
CREATESTRUCT *csp = NULL;
iBshDlg *dlg_ptr = NULL;

// --------------
   msg = uMsg;
   cmd_id = LOWORD(wParam);
   endfl = False;

   if(SUCCEEDED(retc))
   {
      if(msg == WM_CREATE)
      {
         if(SUCCEEDED(retc)) csp = (LPCREATESTRUCT)lParam;
         KP_ASSERT(csp != NULL, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc)) dlg_ptr = (iBshDlg *)csp->lpCreateParams;
         KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
      }
      else
         retc = GetCurWindow((KpWnd **)&dlg_ptr, hwndDlg);
   }

// KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   if((dlg_ptr != NULL) && SUCCEEDED(retc))
   {
      KP_ASSERT(dlg_ptr->m_iWndType == TYP_KpDialog, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(dlg_ptr->m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);
   }

// --------------
   if(SUCCEEDED(retc)) switch(msg)
   {
// --------------
   case WM_CREATE:
      KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(hKpInstance != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) dlg_ptr->m_hDialogWindow = hwndDlg;

// --------------------------------
      if(SUCCEEDED(retc)) retc = dlg_ptr->CreateBackground();

#if (IBSH_SKIN == IBSH_SKIN_MIKO) // || (IBSH_SKIN == IBSH_SKIN_START_GRP)
      if(SUCCEEDED(retc)) retc = KpCreateBitmap( // KpCreateIcon(
                                    dlg_ptr->m_hInstance, hwndDlg, &dlg_ptr->m_hPubIcon,
                                    IBSH_IDI_ADD_ICON, // KP_IDI_MAIN_ICON,
                                    IBSH_ICON_X, IBSH_ICON_Y, IBSH_ICON_WDT, IBSH_ICON_WDT, 0);

      if(SUCCEEDED(retc)) retc = KpCreateStaticRaw(dlg_ptr->m_hInstance, hwndDlg, &dlg_ptr->m_hCaption,
                                    dlg_ptr->m_lpszCaption, // IBSH_WND_CAPTION, //
                                    IBSH_CAPT_X, IBSH_CAPT_Y, IBSH_CAPT_DX, IBSH_CAPT_DY,
                                    IBSH_CAPT_STYLE, 0, 0L, KpColorSchemeLocal);
#endif

      if(SUCCEEDED(retc)) retc = KpCreateStaticRaw(dlg_ptr->m_hInstance, hwndDlg, &dlg_ptr->m_hScreen, (const unsigned char *)"",
                                    dlg_ptr->m_iScrX, dlg_ptr->m_iScrY,
                                    dlg_ptr->m_iScrDX
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
                                    + 80
#endif
                                    ,
                                    dlg_ptr->m_iScrDY
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
                                    + 80
#endif
                                    ,
                                    KPW_CONTROL_STYLE_NORMAL, 0 /* WS_EX_CLIENTEDGE */ /* WS_EX_WINDOWEDGE */, 0L,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL
#else
                                    KpColorSchemeLocal
#endif
                                    );

#if IBSH_SKIN == IBSH_SKIN_MIKO
#  ifdef IBSH_SAVE_AS
      if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hKpInstance, hwndDlg, &(dlg_ptr->m_ButSaveAs), KP_ID_SAVE_AS,
         IBSH_IDI_SAVE_AS_BITMAP, IBSH_IDI_SAVE_AS_LIGHT_BITMAP, IBSH_IDI_SAVE_AS_SEL_BITMAP,
         IBSH_BUT_SAVE_AS_X(dlg_ptr), IBSH_BUT_SAVE_AS_Y(dlg_ptr), IBSH_BUT_WDT, IBSH_BUT_WDT,
         KP_WND_UNPROC_BUT, 0, NULL); // KpColorSchemeLocal);
      KP_ASSERT(dlg_ptr->m_ButSaveAs, KP_E_SYSTEM_ERROR, GetLastError(), True);
#  endif
#endif

      retb = False;
      break;

   case WM_INITDIALOG:
      retb = True;
      break;

// --------------------------------- lango raised su suapvalintais kampais efektas
#if (IBSH_SKIN == IBSH_SKIN_MIKO) // || (IBSH_SKIN == IBSH_SKIN_START_GRP)
   case WM_PAINT:
      KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
         retc = KpDrawRect(hdc, 0, 0, dlg_ptr->m_iWndCurDX, dlg_ptr->m_iWndCurDY, KP_WND_TOOLBAR /* KP_WND_RAISED_BUTTON|KP_WND_TAB */, KpColorSchemeBorder);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retb = DefWindowProc(hwndDlg, msg, wParam, lParam);
      break;
#endif

// ---------------------------------------
   case WM_COMMAND:
      KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) switch(cmd_id)
      {
//-----------------
#ifdef IBSH_SAVE_AS
      case KP_ID_SAVE_AS:

         op_fn_str.lStructSize = sizeof(op_fn_str);
         op_fn_str.hwndOwner = hwndDlg; // dlg_ptr->m_hDialogWindow;
         op_fn_str.hInstance = dlg_ptr->m_hInstance;

         op_fn_str.lpstrDefExt = "htm"; // "txt";

         pnts = strchr(dlg_ptr->m_lpszCaption, '.'); // ieðkosim prievardþio
         if(pnts) do
         {
            pnts1 = strchr(pnts + 1, '.');
            if(pnts1) pnts = pnts1;
         } while(pnts1);

         pntd = filters;
         if(pnts)
         {
            strcpy(pntd, "*");
            strcat(pntd, pnts);
            strcat(pntd, " failai");
            pntd += strlen(pntd) + 1;

            strcpy(pntd, "*");
            strcat(pntd, pnts);
            pntd += strlen(pntd) + 1;

            op_fn_str.lpstrDefExt = (const char *)pnts + 1;
         }

         strcpy(pntd, KP_MSG_ALL_FILES);
         pntd += strlen(pntd) + 1;
         strcpy(pntd, "*.*");
         pntd += strlen(pntd) + 1;

         *(pntd++) = Nul;
         *(pntd++) = Nul;

         op_fn_str.lpstrFilter = (const char *)filters;

         op_fn_str.lpstrCustomFilter = NULL;
         op_fn_str.nMaxCustFilter = 0;
         op_fn_str.nFilterIndex = 1;

         strncpy(out_fname, dlg_ptr->m_lpszCaption, KP_MAX_FNAME_LEN);
         out_fname[KP_MAX_FNAME_LEN] = Nul;
         op_fn_str.lpstrFile = (char *)out_fname;
         op_fn_str.nMaxFile = KP_MAX_FNAME_LEN;

         op_fn_str.lpstrFileTitle = NULL;
         op_fn_str.nMaxFileTitle = 0;

// pradinis aplankas - My Documents
         if(SUCCEEDED(retc)) retc = GetLocalPath(path, KP_My_Documents, False);
         if(SUCCEEDED(retc))
         {
            op_fn_str.lpstrInitialDir=(const char *)path;
            op_fn_str.lpstrTitle = (const char *)KP_MSG_SAVE_AS; // "Save As"

            op_fn_str.Flags=0;

            op_fn_str.nFileOffset = 0;

            pnts = (const unsigned char *)strchr(op_fn_str.lpstrFile, '.');
            if(pnts != NULL) op_fn_str.nFileExtension = pnts - (const unsigned char *)op_fn_str.lpstrFile + 1;
            else op_fn_str.nFileExtension = (int)strlen(op_fn_str.lpstrFile);

            op_fn_str.lCustData = 0L;
            op_fn_str.lpfnHook = NULL;
            op_fn_str.lpTemplateName = NULL;
         }

//       KP_ASSERT(GetSaveFileName(&op_fn_str), KP_E_DIR_ERROR, CommDlgExtendedError(), True);
         if(SUCCEEDED(retc))
         {
            if(!GetSaveFileName(&op_fn_str)) retc0 = KP_E_DIR_ERROR; // klaidà apdoroti, tyliai tik kai nukanceliuoja

// -------------------------------
            if(SUCCEEDED(retc0))
            {
FILE *in_file = fopen(op_fn_str.lpstrFile, "rb");
               if(in_file)
               {
                  fclose(in_file);
                  in_file = NULL;

unsigned char str_buf[KP_MAX_FNAME_LEN + 100];
                  sprintf((char *)str_buf, (const char *)KP_MSG_FILE_EXISTS, op_fn_str.lpstrFile);
                  retc0 = KpMsgOut(str_buf, IDI_WARNING, KP_MB_GERAI_ATSAUKTI);
               }
            }

// -------------------------------
            if(SUCCEEDED(retc0))
            {
               KP_NEWO(out_file, XmlO1((const unsigned char *)op_fn_str.lpstrFile, (const unsigned char *)"w",
                     CreateNew8File,
                     NULL, // plpszaHtmSpecCharTags,
                     NULL, NULL,
                     HTM_TG_FirstTag,
                     dlg_ptr->m_pKpFileSys->m_lpInFileObj->
#ifdef IBSHT_ARCHIVE
                        FilePtr->
#endif
                        GetTagsArrPtr(), True, // plpszaHtmlTags, False,
                     XM_VERS_HTML401_TRANS,
                     iaHtmCodeTables71, // iaHtmNulCodeTables,
                     True, False));
               retc0 = retc;
            }

            if(SUCCEEDED(retc0)) retc0 = out_file->SetEncoding(UC_PlainText, TV_MAIN_HTML_CTBL, TV_MAIN_HTML_CTBL); // 42, 42); // DOS-inë standartinë IBM-772 lentelë // 43, 43); // DOS-inë IBM-773 lentelë //

// -------------------------------
            KP_ASSERT00(dlg_ptr->m_pKpFileSys->m_pCurEntry, KP_E_SYSTEM_ERROR, null, True);

            cur_node = NULL;
            if(SUCCEEDED(retc0)) retc0 = dlg_ptr->m_pKpFileSys->m_pCurEntry->SearchSubNode(HTM_TG_PRE, &cur_node);
            if(SUCCEEDED(retc0))
            {
               if(cur_node != NULL)
               {
// ----------------- out_file nustatom paskutiná tagà steke á HTM_TG_PRE ~ kad nelauþtø eiluèiø
                  KP_ASSERT00(out_file->m_fFiles != NULL, KP_E_SYSTEM_ERROR, null, True);
                  KP_ASSERT00(out_file->m_fFiles[XL_IX_DefDataFile]->m_lpTagStack != NULL, KP_E_SYSTEM_ERROR, null, True);
                  if(SUCCEEDED(retc0)) retc = PushTag(&out_file->m_fFiles[XL_IX_DefDataFile]->m_lpTagStack, HTM_TG_PRE, NULL, 0);

// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//                retc0 = cur_node->GetFirstChild((KpTreeEntry **)&cur_node);
                  cur_node = (XmlNode *)cur_node->m_pFirstChild;

                  KP_ASSERT00(cur_node, KP_E_FILE_FORMAT, dlg_ptr->m_lpszCaption, True);

                  if(SUCCEEDED(retc0)) retc0 = cur_node->GetNodeTag(&cur_tag);
                  KP_ASSERT00(cur_tag == XL_Text, KP_E_FILE_FORMAT, dlg_ptr->m_lpszCaption, True);

                  if(SUCCEEDED(retc0)) retc0 = cur_node->GetContentsPtr(&contents);
                  KP_ASSERT00(contents, KP_E_FILE_FORMAT, dlg_ptr->m_lpszCaption, True);

                  if(SUCCEEDED(retc0))
                  {
                     if(*contents == C_Cr) contents++;
                     if(*contents == C_Lf) contents++;
                  }
                  if(SUCCEEDED(retc0)) retc0 = dlg_ptr->m_pKpFileSys->m_pCurEntry->PutKpStr(contents, out_file);

// ------------------ iðimam HTM_TG_PRE ið steko
                  if(SUCCEEDED(retc0)) retc = PushTag(&out_file->m_fFiles[XL_IX_DefDataFile]->m_lpTagStack, HTM_TG_PRE, NULL, 0);
               }
               else
                  retc0 = dlg_ptr->m_pKpFileSys->m_pCurEntry->WriteNode(out_file); // dlg_ptr->m_pKpFileSys->m_pCurEntry->WriteNode(out_file);
            }

// -------------------------------
            if(SUCCEEDED(retc0)) retc0 = out_file->CloseFile(True);

            KP_DELETE(out_file);

         } // if(SUCCEEDED(retc))

         break;
#endif // #ifdef IBSH_SAVE_AS

//-----------------
      case IDOK:
         retb = False;
         break;

      case KP_ID_EXIT:
      case IDCANCEL:
         endfl = True;
         retb = False;
         retc = KP_E_CANCEL;
         break;

      case KP_ID_MINIMIZE:
         if(!CloseWindow(hwndDlg))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
         }
         break;

      }
      break; // case WM_COMMAND:

   case WM_CLOSE:
      if(dlg_ptr != NULL) // kad jau niekas neuþdarinëtø daugiau – pas Gintarà lûþta StartGrp.exe
      {
         dlg_ptr->CloseWindow(); // stabdom taimerius
         dlg_ptr->m_hWndHandle = dlg_ptr->m_hDialogWindow = NULL;
// PutLogMessage_("HWND iBshDialogProc() WM_CLOSE hwndDlg %x", hwndDlg);
      }
      endfl = True;
      retb = DefWindowProc(hwndDlg, msg, wParam, lParam);
      retc = KP_E_CANCEL; // Alt + F4
      break;

   case WM_QUIT:
      switch(cmd_id)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         default: retc = KP_E_CANCEL; break;
      }
      endfl=True;
      break;

   case WM_EXITSIZEMOVE:
      KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) if(dlg_ptr->m_bResizing) // KpPubDlgPtr->m_bResizing)
         renew = True;
      break;

   default:
      retb = DefWindowProc(hwndDlg, msg, wParam, lParam);
      break;

   } // if(SUCCEEDED(retc)) switch(uMsg)

   if(SUCCEEDED(retc)) /* retb = */ KpPubDialogProc(hwndDlg, uMsg, wParam, lParam);

   if(renew && SUCCEEDED(retc))
   {
      KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(dlg_ptr != NULL) dlg_ptr->WaitForXGecko();

      if(SUCCEEDED(retc)) retc = dlg_ptr->m_pKpFileSys->SearchForEntry(dlg_ptr);
      if(SUCCEEDED(retc)) retc = dlg_ptr->DisplayResult();

      retb = DefWindowProc(hwndDlg, msg, wParam, lParam);
   }

#if FALSE // iðkeltas á iBshDlg::DoEdit(); be to lûþta pas Gintarà StartGrp.exe
   if(endfl)
   {
//    KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
// PutLogMessage_("HWND iBshDialogProc() m_hWndHandle %x", dlg_ptr->m_hWndHandle);
      if(dlg_ptr != NULL) dlg_ptr->m_hWndHandle = dlg_ptr->m_hDialogWindow = NULL;
      DestroyWindow(hwndDlg);
   }
#endif

   if(endfl && (dlg_ptr != NULL)) dlg_ptr->CloseWindow(); // stabdom taimerius

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, msg, wParam, lParam);
      retb = TRUE;
   }

   if(endfl || FAILED(retc)) PostQuitMessage(RET_CODE_WM_QUIT(retc));

return(retb);
}


// ----------------------------------
int iBshDlg::DoEdit(void)
{
int retp = IDOK;

HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
MSG msg;
bool endfl = False;

// ----------------------------------
// KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(m_hDialogWindow, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }

      retp = LOWORD(msg.wParam);

// ------------------------------------------------- pagrindinis praneðimø apdorojimas
// WM_QUIT praneðimas ið KpGeckoStreamFactory() kaþko neateina
// Login: m_bLogoff == True
// Logoff: m_bLogoff == True && m_bClose == True
// DoLogin OK: m_bClose == True
// DoLogin Cancel: m_bLogoff == True && m_bClose == True
      if(m_bClose) retc = KP_S_DONE;
      if(m_bLogoff) retc = KP_S_LOGOFF;

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: if(SUCCEEDED(retc)) retc = KP_E_CANCEL; break;
         case IDABORT: if(SUCCEEDED(retc)) retc = KP_E_SYSTEM_ERROR; break;
         default: if(SUCCEEDED(retc)) retc = KP_E_CANCEL;
         }
         endfl = True;
         break;

      case WM_CLOSE:
         endfl = True;
         break;

      case WM_CAPTURECHANGED:
         if(SUCCEEDED(retc)) retc = ExitCapture();
         break;

#if FALSE // IBSH_SKIN==IBSH_SKIN_STANDART
   case WM_MOUSEMOVE:
// ------------------ tooltips
      mouse_over_wnd = msg.hwnd;

      KP_ASSERT(pHelpDialog, KP_E_SYSTEM_ERROR, True, null);
      if(SUCCEEDED(retc)) if(hMouseOverWnd != mouse_over_wnd)
      {
         hMouseOverWnd = mouse_over_wnd;
         if(SUCCEEDED(retc)) retc = ManageToolTipTimer();
      }
      break;
#endif

     case WM_TIMER:
// PutLogMessage_("iBshDlg::DoEdit() WM_TIMER %d %d", retp, m_RedrawTimer);
         if((theKpStAppPtr != NULL) && SUCCEEDED(retc)) retc = theKpStAppPtr->CheckLicSvr(retp);

#if IBSH_SKIN == IBSH_SKIN_MIKO
// ------------------------------------ tooltips
         if(retp == ToolTipTimer)
         {
            if(hToolTip && SUCCEEDED(retc))
            {
               if(!(::DestroyWindow(hToolTip)))
               {
#  ifdef Debug
                  KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
               }
            }
            hToolTip = NULL;

// -----------------
#  ifdef IBSH_SAVE_AS
            if((hMouseOverWnd == m_ButSaveAs) && SUCCEEDED(retc))
            {
               retc = KpCreateStatic(hKpInstance, m_ButSaveAs, &hToolTip,
                  IBSH_BUT_SAVE_AS_TOOLTIP_TXT,
                  m_iWndCurX + IBSH_WND_BORDER_WDT + IBSH_BUT_SAVE_AS_X(this) + KPW_TOOLTIP_X,
                  m_iWndCurY + IBSH_WND_BORDER_WDT + IBSH_WND_CAPTION_HGT + IBSH_BUT_SAVE_AS_Y(this) + KPW_TOOLTIP_Y,
                  60, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
                  KpColorSchemeToolTip);
#     ifdef Debug
               KP_ASSERT(hToolTip, KP_E_SYSTEM_ERROR, GetLastError(), False);
#     endif
            }
#  endif

            if((hMouseOverWnd == m_ButExit) && SUCCEEDED(retc))
            {
               retc = KpCreateStatic(hKpInstance, m_ButExit, &hToolTip,
                  IBSH_BUT_EXIT_TOOLTIP_TXT,
                  m_iWndCurX + IBSH_WND_BORDER_WDT + IBSH_BUT_EXIT_X(this) + KPW_TOOLTIP_X,
                  m_iWndCurY + IBSH_WND_BORDER_WDT + IBSH_WND_CAPTION_HGT + IBSH_BUT_EXIT_Y(this) + KPW_TOOLTIP_Y,
                  60, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
                  KpColorSchemeToolTip);
#  ifdef Debug
               KP_ASSERT(hToolTip, KP_E_SYSTEM_ERROR, GetLastError(), False);
#  endif
            }

// -----------------
            if(ToolTipTimer) if(!KillTimer(HWND_DESKTOP, ToolTipTimer))
            {
#  ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
            }
            ToolTipTimer = 0;

// -----------------------------------
            if(ToolTipKillTimer) if(!KillTimer(HWND_DESKTOP, ToolTipKillTimer))
            {
#  ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
            }
            ToolTipKillTimer = SetTimer(HWND_DESKTOP, KPW_TOOLTIP_KILL_TIMER, KPW_TOOLTIP_KILL_TIMEOUT, NULL);
#  ifdef Debug
            KP_ASSERT(ToolTipKillTimer, KP_E_SYSTEM_ERROR, GetLastError(), False);
#  endif
         } // if(retp == ToolTipTimer)

// ------------------------------------
         else if(retp == ToolTipKillTimer)
         {
            if(ToolTipKillTimer) if(!KillTimer(HWND_DESKTOP, ToolTipKillTimer))
            {
#  ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
            }
            ToolTipKillTimer = 0;

            if(hToolTip && SUCCEEDED(retc))
            {
               if(!(::DestroyWindow(hToolTip)))
               {
#  ifdef Debug
                  KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
               }
            }
            hToolTip = NULL;
         }

         else
#endif // #if IBSH_SKIN == IBSH_SKIN_MIKO

         if(retp == m_RedrawTimer)
         {
// PutLogMessage_("iBshDlg::DoEdit() retp == m_RedrawTimer %d", m_bRefresh);
            if(m_bRefresh)
            {
               m_bRefreshing = True;

               KP_ASSERT(m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);
               if(m_pKpFileSys != NULL) m_pKpFileSys->BlockSemaphore();
// PutLogMessage_("iBshDlg::DoEdit() WaitForXGecko()");
               WaitForXGecko();

// PutLogMessage_("iBshDlg::DoEdit() SearchForEntry()");
               if(SUCCEEDED(retc)) retc = m_pKpFileSys->SearchForEntry(this, m_pKpFileSys->m_lpszCurSearchKwd); // KPST_GRP_MENU_FNAME);

               m_bRefreshing = m_bRefresh = False;
// semaforà iðlaisvins besibaigiantis XKpGeckoStream::read()
// taip neveikia
               if(m_pKpFileSys != NULL) m_pKpFileSys->ReleaseSemaphore();
            }
         }

         break;

      case WM_CHAR:
         if(SUCCEEDED(retc)) switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId != 0L)
               if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());
            break;
         }
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDCANCEL:
            if(msg.hwnd == m_hDialogWindow) endfl = True;
            break;

// ið KpGeckoStreamFactory() neateina
         case KP_ID_LOGOFF:
            if(msg.hwnd == m_hDialogWindow)
            {
//             endfl = True;
               retc = KP_S_LOGOFF;
            }
            break;
         }
         break;

      }  // if(SUCCEEDED(retc)) switch(msg.message)

   } while((!endfl) && (retc != KP_S_LOGOFF) && (retc != KP_S_DONE) &&  SUCCEEDED(retc));

// -------- save window coordinates
/* if(SUCCEEDED(retc)) retc = */ SaveCoords();

// ----------------------
#if TRUE // FALSE // StartGrp.exe lûþta pas Gintarà
   if((m_hDialogWindow != NULL) && (retc != KP_S_LOGOFF) && (retc != KP_S_DONE)) // && (retc != KP_E_CANCEL))
   {
HWND frame;
      frame = m_hDialogWindow;
      m_hWndHandle = m_hDialogWindow = NULL;
// PutLogMessage_("HWND iBshDlg::DoEdit() m_hWndHandle %x", frame);
#  if FALSE // TRUE // StartGrp.exe lûþta pas Gintarà
      if(!(::DestroyWindow(frame)))
      {
#     ifdef Debug
// jau buna uzsidares
         KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#     endif
      }
#  endif
   }
#endif

   if(FAILED(retc)) retp = RET_CODE_WIN(retc);

// PutLogMessage_("iBshDlg::DoEdit() retc %x  retp %x  KP_S_LOGOFF %x  m_bLogoff %d  m_bClose %d", retc, retp, KP_S_LOGOFF, m_bLogoff, m_bClose);

return(retp);
}


// ----------------------------------------
HRESULT iBshDlg::RedrawWindow(void)
{
HRESULT retc=S_OK;

// -----------------------------
   KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);

// -----------------------------
   if((m_iDoRedraw == 1) && SUCCEEDED(retc))
   {

// -------------------
//    KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) if(!SetWindowPos(m_hDialogWindow, HWND_TOP, m_iWndCurX, m_iWndCurY,
         m_iWndCurDX
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
         + 100
#endif
         , m_iWndCurDY
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
         + 100
#endif
         , 0))
      {
#ifdef Debug
         KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#endif
      }

      KP_ASSERT(m_hScreen != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) if(!SetWindowPos(m_hScreen, HWND_TOP, m_iScrX, m_iScrY,
         m_iScrCurDX
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
         + 80
#endif
         , m_iScrCurDY
#ifdef IBSHL_TEST_INITIAL_CONTROL_SIZE
         + 80
#endif
         , 0))
      {
#ifdef Debug
         KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#endif
      }

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP)
//    KP_ASSERT(m_ButExit != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) if(m_ButExit != NULL) if(!SetWindowPos(m_ButExit, HWND_TOP,
                              IBSH_BUT_EXIT_X(this), IBSH_BUT_EXIT_Y(this),
                              m_ButExitBmpData.m_iBmpWdt, m_ButExitBmpData.m_iBmpHgt, // IBSH_BUT_WDT, IBSH_BUT_WDT,
                              0))
      {
#ifdef Debug
         KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#endif
      }

      if(SUCCEEDED(retc)) if(m_ButMinimize != NULL) if(!SetWindowPos(m_ButMinimize, HWND_TOP,
                              IBSH_BUT_MIN_X(this), IBSH_BUT_MIN_Y(this),
                              m_ButMinBmpData.m_iBmpWdt, m_ButMinBmpData.m_iBmpHgt, // IBSH_BUT_WDT, IBSH_BUT_WDT,
                              0))
      {
#ifdef Debug
         KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#endif
      }
#endif

// ---------------
      retc = RedrawWindowLocal();

// ---------------
      if(SUCCEEDED(retc))
         if(!InvalidateRect(m_hDialogWindow, 0, True))
         {
#ifdef Debug
            KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
#endif
         }

   } // if((m_iDoRedraw == 1) && SUCCEEDED(retc))

   if(m_iDoRedraw && SUCCEEDED(retc)) m_iDoRedraw = 0; // m_iDoRedraw--;

return(retc);
}


// ----------------------------------
HRESULT iBshDlg::Resize(void)
{
HRESULT retc=S_OK;

int wdt_sav, hgt_sav;
#ifndef IBSH_NOZOOM
int fact_x;
#endif
#ifdef IBSH_PRESERVE_RATIO
int fact_y;
#endif

// ------------------------------------
   if(SUCCEEDED(retc))
   {
      wdt_sav = m_iWndCurDX;
      hgt_sav = m_iWndCurDY;

      if(m_iWndCurDXprec < m_iWndDXmin) m_iWndCurDXprec = m_iWndDXmin;
      if(m_iWndCurDXprec > m_iWndDXmax) m_iWndCurDXprec = m_iWndDXmax;
      if(m_iWndCurDYprec < m_iWndDYmin) m_iWndCurDYprec = m_iWndDYmin;
      if(m_iWndCurDYprec > m_iWndDYmax) m_iWndCurDYprec = m_iWndDYmax;

      m_iWndCurDX = m_iWndCurDXprec;
      m_iWndCurDY = m_iWndCurDYprec;
   }

   if(SUCCEEDED(retc))
   {
      m_iScrCurDX = m_iWndCurDXprec - (2 * m_iWndHardBorderWdt) - (2 * m_iWndSoftHorBorderWdt);
      m_iScrCurDY = m_iWndCurDYprec - (2 * m_iWndHardBorderWdt) - m_iWndSoftTopBorderWdt - m_iWndSoftBotBorderWdt - m_iWndHardCaptHgt - m_iWndSoftCaptHgt;
      m_iScrX = m_iWndSoftHorBorderWdt;
      m_iScrY = m_iWndSoftTopBorderWdt + m_iWndSoftCaptHgt;
   }
// PutLogMessage_("iBshDlg::Resize(): m_iScrCurDY: %d  m_iScrY: %d  m_iWndSoftCaptHgt: %d  m_iWndSoftHorBorderWdt: %d  m_iWndSoftTopBorderWdt: %d  m_iWndSoftBotBorderWdt: %d  m_iWndCurDY: %d", m_iScrCurDY, m_iScrY, m_iWndSoftCaptHgt, m_iWndSoftHorBorderWdt, m_iWndSoftTopBorderWdt, m_iWndSoftBotBorderWdt, m_iWndCurDY);

// ------------------------------------
#ifndef IBSH_NOZOOM
   if(SUCCEEDED(retc))
   {
      fact_x = m_iScrCurDX * 1000L / m_iScrDX;
#  ifdef IBSH_PRESERVE_RATIO
      fact_y = m_iScrCurDY * 1000L / m_iScrDY;
      m_iFact = min(fact_x, fact_y);
#  else
      m_iFact = fact_x;
#  endif
   }
#endif

// -------------------
   if(((wdt_sav != m_iWndCurDX) || (hgt_sav != m_iWndCurDY)) && SUCCEEDED(retc))
      retc = ResizeCommon();

return(retc);
}
