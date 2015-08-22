// ---------------------------
// kpstapd.cpp
// common application for program starters
// install key input dialog KPSTKEY
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
HRESULT KpStApp::OpenKeyWindow(const unsigned char *lpszHint1)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
HDC dc;
int wnd_x = 0;
int wnd_y = 0;
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int prod_name_2_fl = 0;
KpStLicPars *lic_pars_ptr = NULL;

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
      wcx.lpszClassName = "KPSTKEY",
      wcx.lpfnWndProc   = (WNDPROC)KpStKeyDialogProc;
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

   KP_DELETE(lic_pars_ptr);

   KP_NEW(lic_pars_ptr, KpStLicPars);

   if(SUCCEEDED(retc))
   {
      dc=GetDC(HWND_DESKTOP);
      if(dc==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      wnd_x = (GetDeviceCaps(dc, HORZRES)-KPSTKEY_WND_DX) / 2;
      wnd_y = (GetDeviceCaps(dc, VERTRES)-KPSTKEY_WND_DY) / 2;

      lic_pars_ptr->m_lpszHint = lpszHint1;
      lic_pars_ptr->m_iWndWdt = KPSTKEY_WND_DX;
      lic_pars_ptr->m_iWndHgt = KPSTKEY_WND_DY;

      m_hKeyDialogWindow=CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPSTKEY",
         (char *)KPST_MSG_DIEG_RAKTAS_1,       // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         wnd_x,  // CW_USEDEFAULT, // int x,               // horizontal position of window
         wnd_y,  // CW_USEDEFAULT, // int y,               // vertical position of window
         lic_pars_ptr->m_iWndWdt,          // int nWidth,           // window width
         lic_pars_ptr->m_iWndHgt,          // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         m_hInstance,
         lic_pars_ptr       // LPVOID lpParam        // pointer to window-creation data
      );
   }

   KP_ASSERT(m_hKeyDialogWindow, KP_E_SYSTEM_ERROR, GetLastError(), True);

// nereikia naikint - sunaikins lango callback programa KpStLicDialogProc()
// KP_DELETE(lic_pars_ptr);

return(retc);
}


// -----------------------------------------
BOOL CALLBACK KpStKeyDialogProc(
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
static unsigned char out_buf[KP_MAX_FILE_LIN_WDT + 1];
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
#endif
static unsigned char hint[KP_MAX_FILE_LIN_WDT + 1];
LPCREATESTRUCT cst_ptr;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
unsigned char code_buf[KP_KWD_LEN + 1];
const unsigned char *pnts;
unsigned char *pntd;
int prod_name_2_fl = 0;
unsigned char *prod_name_2_ptr = null;
// int wnd_dx, wnd_dy;
HDC hdc = NULL;
PAINTSTRUCT ps;
// KpWnd *cur_wnd = NULL;
KpStLicPars *lic_pars_ptr = NULL;
unsigned char url_buf[KP_MAX_FNAME_LEN + 1];
int lic_high = 0;

   retp=LOWORD(wParam);
   endfl=False;

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
// ------
      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

// ------
      if(SUCCEEDED(retc))
      {
         hint[0] = Nul;
         cst_ptr = (LPCREATESTRUCT)lParam;
         if(cst_ptr != NULL) lic_pars_ptr = (KpStLicPars *)cst_ptr->lpCreateParams;
         if(lic_pars_ptr != NULL)
         {
            KP_ASSERT(strlen(lic_pars_ptr->m_lpszHint) + strlen(KPST_MSG_REG_UNSUC_0) + 1 < KP_MAX_FILE_LIN_WDT, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc))
            {
               strcpy(hint, lic_pars_ptr->m_lpszHint);
               if(hint[0] != Nul) strcat(hint, " ");
               strcat(hint, KPST_MSG_REG_UNSUC_0);
            }
         }
      }

// ------
#if FALSE
      KP_NEWO(cur_wnd, KpWnd(hwndDlg, TYP_KpDialog, null, NULL,
            hKpInstance, NULL, NULL, KPW_CONTROL_STYLE_NORMAL,
            lic_pars_ptr->m_iWndWdt, lic_pars_ptr->m_iWndHgt, 1, 1, 0L, 0L,
            NULL));

      if(SUCCEEDED(retc)) retc = WndPreg(cur_wnd, TYP_KpDialog, hKpInstance, null, False);
#endif

// ------
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdName(prod_name);
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
      if(SUCCEEDED(retc)) retc=KpCreateIcon(hKpInstance, hwndDlg, NULL, KP_IDI_SETUP_ICON, KPST_SETUP_ICON_X, KPST_SETUP_ICON_Y, KPST_SETUP_ICON_WDT, KPST_SETUP_ICON_WDT, 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, prod_name, KPSTKEY_HEAD_X, KPSTKEY_HEAD_Y, 1, KPW_CONTROL_STYLE_BOLD, 0, 0, NULL);
      if(prod_name_2_fl && SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, prod_name_2_ptr, KPSTKEY_HEAD_X, KPSTKEY_HEAD2_Y, 1, KPW_CONTROL_STYLE_BOLD, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)KPST_MSG_PROD_REG, KPSTKEY_SUBHEAD_X, KPSTKEY_SUBHEAD_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, hint, KPSTKEY_EXPL_X, KPSTKEY_EXPL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_REG_UNSUC_1, KPSTKEY_EXPL_1_X, KPSTKEY_EXPL_1_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetRegUrl(null, url_buf, KPST_HTTP_REGISTER);
      if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hKeyUrlButton), KPST_ID_URL, url_buf, KPSTKEY_URL_X, KPSTKEY_URL_Y, KPSTKEY_URL_DX, KPW_BUTTON_HGT, KP_WND_URL, 0, 0);
      if((theKpStAppPtr->m_hKeyUrlButton == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_SIUSK_PASTU, KPSTKEY_HINT_X, KPSTKEY_HINT1_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_DARBO_LAIKAS, KPSTKEY_HINT_X, KPSTKEY_HINT2_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_DIKT_TELEF, KPSTKEY_HINT_X, KPSTKEY_HINT3_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_DIEG_KOD, KPSTKEY_INST_CODE_PROMPT_X, KPSTKEY_INST_CODE_CTRL_Y, KPSTKEY_INST_CODE_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) /* retc = */ theKpStAppPtr->FormatInstCodeFull(out_buf);
//    if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetLicHighHp11(&lic_high);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->AddHigh(out_buf, lic_high, 12);
//    if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, out_buf, KPSTKEY_INST_CODE_CTRL_X, KPSTKEY_INST_CODE_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hInstCodeEdit), out_buf, KPSTKEY_INST_CODE_CTRL_DX, KPSTKEY_INST_CODE_CTRL_X, KPSTKEY_INST_CODE_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, ES_READONLY /* WS_DISABLED */, 1);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_IVESK_RAKTA, KPSTKEY_HINT_X, KPSTKEY_HINT4_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_IVESK_RAKTA_1, KPSTKEY_HINT_X, KPSTKEY_HINT5_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, KPST_MSG_DIEG_RAKTAS, KPSTKEY_KEY_PROMPT_X, KPSTKEY_KEY_CTRL_Y, KPSTKEY_KEY_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hInstKey1Edit), (const unsigned char *)"", KPST_KEY_SEGM_EDIT_DX, KPSTKEY_KEY1_EDIT_X, KPSTKEY_KEY_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hInstKey1Edit==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"-", KPSTKEY_KEY_EDIT_DASH1_X, KPSTKEY_KEY_CTRL_Y, KPST_DASH_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hInstKey2Edit), (const unsigned char *)"", KPST_KEY_SEGM_EDIT_DX, KPSTKEY_KEY2_EDIT_X, KPSTKEY_KEY_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hInstKey2Edit==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"-", KPSTKEY_KEY_EDIT_DASH2_X, KPSTKEY_KEY_CTRL_Y, KPST_DASH_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hInstKey3Edit), (const unsigned char *)"", KPST_KEY_SEGM_EDIT_DX, KPSTKEY_KEY3_EDIT_X, KPSTKEY_KEY_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hInstKey3Edit==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, hwndDlg, NULL, (const unsigned char *)"-", KPSTKEY_KEY_EDIT_DASH3_X, KPSTKEY_KEY_CTRL_Y, KPST_DASH_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hInstKey4Edit), (const unsigned char *)"", KPST_KEY_SEGM_EDIT_DX, KPSTKEY_KEY4_EDIT_X, KPSTKEY_KEY_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, 1);
      if((theKpStAppPtr->m_hInstKey4Edit==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hKeyOkButton), IDOK, KP_MSG_TESTI, KPSTKEY_OK_BUT_X, KPSTKEY_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if((theKpStAppPtr->m_hKeyOkButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, hwndDlg, &(theKpStAppPtr->m_hKeyCancelButton), IDCANCEL, KP_MSG_ATSAUKTI, KPSTKEY_CANCEL_BUT_X, KPSTKEY_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if((theKpStAppPtr->m_hKeyCancelButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(!SetFocus(theKpStAppPtr->m_hInstKey1Edit))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      KP_DELETE(lic_pars_ptr);

      break;

   case WM_PAINT:

      KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

#if FALSE
      wnd_dx = KPSTKEY_WND_DX;
      wnd_dy = KPSTKEY_WND_DY;

      if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, hwndDlg);
      if(cur_wnd && SUCCEEDED(retc))
      {
         wnd_dx = cur_wnd->m_iWdtDots;
         wnd_dy = cur_wnd->m_iHgtDots;
      }
#endif

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

      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTKEY_LINE_X1, KPSTKEY_LINE1_Y, KPSTKEY_LINE_X2, KPSTKEY_LINE1_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTKEY_LINE_X1, KPSTKEY_LINE2_Y, KPSTKEY_LINE_X2, KPSTKEY_LINE2_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTKEY_LINE_X1, KPSTKEY_LINE3_Y, KPSTKEY_LINE_X2, KPSTKEY_LINE3_Y, KP_WND_SUNKEN, NULL);
      if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPSTKEY_LINE_X1, KPSTKEY_LINE4_Y, KPSTKEY_LINE_X2, KPSTKEY_LINE4_Y, KP_WND_SUNKEN, NULL);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_CTLCOLOREDIT:
      KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

      if((HWND)lParam == theKpStAppPtr->m_hInstCodeEdit)
      {
         KP_ASSERT(SetBkColor((HDC)wParam, GetSysColor(iaColorMap[KpShadowNorm])) != CLR_INVALID, KP_E_SYSTEM_ERROR, GetLastError(), False);
//       KP_ASSERT(SetTextColor((HDC)wParam, 0xFFFFFF) != CLR_INVALID, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
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
      switch(HIWORD(wParam))
      {
      case EN_UPDATE:
// iðskaidom theKpStAppPtr->m_hInstKey1Edit á likusius po Paste
         KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, True, null);
         if(SUCCEEDED(retc)) if((HWND)lParam == theKpStAppPtr->m_hInstKey1Edit)
         {
            SendMessage(theKpStAppPtr->m_hInstKey1Edit, WM_GETTEXT, KP_KWD_LEN + 1, (LPARAM)code_buf);
            code_buf[KP_KWD_LEN] = Nul;
            retc = RemoveSpaces(code_buf);
            if(SUCCEEDED(retc))
            {
               pnts = code_buf;
               pntd = strchr(pnts, '-');
               if(pntd)
               {
                  *pntd++ = Nul;
                  SendMessage(theKpStAppPtr->m_hInstKey1Edit, WM_SETTEXT, 0, (LPARAM)pnts);

                  pnts = pntd;
                  pntd = strchr(pnts, '-');

                  if(pntd) *pntd++ = Nul;

                  SendMessage(theKpStAppPtr->m_hInstKey2Edit, WM_SETTEXT, 0, (LPARAM)pnts);

                  if(pntd)
                  {
                     pnts = pntd;
                     pntd = strchr(pnts, '-');

                     if(pntd) *pntd++ = Nul;

                     SendMessage(theKpStAppPtr->m_hInstKey3Edit, WM_SETTEXT, 0, (LPARAM)pnts);

                     if(pntd)
                     {
                        pnts = pntd;
// atkandam pirmus 4 simbolius - tam atvejui, jeigu lauke theKpStAppPtr->m_hInstKey1Edit jau kaþkas buvo (anksèiau suvestas kodas)
                        while(*pntd && ((pntd - pnts) < 4)) pntd++;
                        if(pntd) *pntd++ = Nul;

                        SendMessage(theKpStAppPtr->m_hInstKey4Edit, WM_SETTEXT, 0, (LPARAM)pnts);
                     }
                  }
               }
            }
         }
         break;

//    case EN_CHANGE:
// KP_TRACE("KpStLicDialogProc(): EN_CHANGE");
//       break;
      }

      switch(LOWORD(wParam))
      {
      case KPST_ID_URL:
         KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetRegUrl(null, url_buf, KPST_HTTP_REGISTER);
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
HRESULT KpStApp::EnterNewKey(HINSTANCE hInst, const unsigned char *lpszHint1)
{
HRESULT retc=S_OK;
MSG msg;
int retp;
bool endfl=False;
unsigned char key_buf[KPST_NUM_OF_KEY_SEGM_CHARS+1];
unsigned char full_key_buf[KPST_NUM_OF_KEY_CHARS+100];
HWND cur_wnd;
int key_add = 0;
// int lic_high = 0;

   if(hInst==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) m_hInstance=hInst;

   if(SUCCEEDED(retc)) retc = SaveKeyDat();

   if(SUCCEEDED(retc)) retc=OpenKeyWindow(lpszHint1);

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

            if(cur_wnd==m_hKeyUrlButton) SetFocus(m_bShiftFl?m_hKeyCancelButton:m_hInstCodeEdit);
            else if(cur_wnd==m_hInstCodeEdit) SetFocus(m_bShiftFl?m_hKeyUrlButton:m_hInstKey1Edit);
            else if(cur_wnd==m_hInstKey1Edit) SetFocus(m_bShiftFl?m_hInstCodeEdit:m_hInstKey2Edit);
            else if(cur_wnd==m_hInstKey2Edit) SetFocus(m_bShiftFl?m_hInstKey1Edit:m_hInstKey3Edit);
            else if(cur_wnd==m_hInstKey3Edit) SetFocus(m_bShiftFl?m_hInstKey2Edit:m_hInstKey4Edit);
            else if(cur_wnd==m_hInstKey4Edit) SetFocus(m_bShiftFl?m_hInstKey3Edit:m_hKeyOkButton);
            else if(cur_wnd==m_hKeyOkButton) SetFocus(m_bShiftFl?m_hInstKey4Edit:m_hKeyCancelButton);
            else if(cur_wnd==m_hKeyCancelButton) SetFocus(m_bShiftFl?m_hKeyOkButton:m_hInstCodeEdit);
            else SetFocus(m_hKeyOkButton);
            break;

         case Enter:
            PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            break;

         case Esc:
            PostMessage(NULL, WM_COMMAND, IDCANCEL, 0L);
            break;

         default:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hInstKey1Edit)
            {
               if(KPST_NUM_OF_KEY_SEGM_CHARS<=SendMessage(m_hInstKey1Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)key_buf))
                  SetFocus(m_hInstKey2Edit);
            }
            else if(cur_wnd==m_hInstKey2Edit)
            {
               if(KPST_NUM_OF_KEY_SEGM_CHARS<=SendMessage(m_hInstKey2Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)key_buf))
                  SetFocus(m_hInstKey3Edit);
            }
            else if(cur_wnd==m_hInstKey3Edit)
            {
               if(KPST_NUM_OF_KEY_SEGM_CHARS<=SendMessage(m_hInstKey3Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)key_buf))
                  SetFocus(m_hInstKey4Edit);
            }
            else if(cur_wnd==m_hInstKey4Edit)
            {
               if(KPST_NUM_OF_KEY_SEGM_CHARS<=SendMessage(m_hInstKey4Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS+1, (LPARAM)key_buf))
                  PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            }
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
            if(cur_wnd==m_hKeyUrlButton) SetFocus(m_hInstCodeEdit);
            else if(cur_wnd==m_hInstCodeEdit) SetFocus(m_hInstKey1Edit);
            else if(cur_wnd==m_hInstKey1Edit) SetFocus(m_hKeyOkButton);
            else if(cur_wnd==m_hInstKey2Edit) SetFocus(m_hKeyOkButton);
            else if(cur_wnd==m_hInstKey3Edit) SetFocus(m_hKeyCancelButton);
            else if(cur_wnd==m_hInstKey4Edit) SetFocus(m_hKeyCancelButton);
            else if(cur_wnd==m_hKeyCancelButton);
            else SetFocus(m_hKeyOkButton);
            break;

         case Up:
            cur_wnd=GetFocus();
            if(cur_wnd==m_hKeyUrlButton);
            else if(cur_wnd==m_hInstCodeEdit) SetFocus(m_hKeyUrlButton);
            else if(cur_wnd==m_hInstKey1Edit) SetFocus(m_hInstCodeEdit);
            else if(cur_wnd==m_hInstKey2Edit) SetFocus(m_hInstCodeEdit);
            else if(cur_wnd==m_hInstKey3Edit) SetFocus(m_hInstCodeEdit);
            else if(cur_wnd==m_hInstKey4Edit) SetFocus(m_hInstCodeEdit);
            else if(cur_wnd==m_hKeyOkButton) SetFocus(m_hInstKey1Edit);
            else if(cur_wnd==m_hKeyCancelButton) SetFocus(m_hInstKey3Edit);
            else SetFocus(m_hKeyOkButton);
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
//          m_iInstKey1=0;
//          m_iInstKey2=0;
//          m_iInstKey3=0;
//          m_iInstKey4=0;
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY1);
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY2);
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY3);
            if(SUCCEEDED(retc)) retc=EmuTv.SetHp11Variable(0, KP11_INST_KEY4);

            full_key_buf[0] = Nul;

            if((m_hInstKey1Edit != NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_hInstKey1Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)full_key_buf);
               full_key_buf[KPST_NUM_OF_KEY_SEGM_CHARS] = Nul;
               strcat(full_key_buf, "-");
            }
            if((m_hInstKey2Edit != NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_hInstKey2Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)full_key_buf + strlen(full_key_buf));
               full_key_buf[KPST_NUM_OF_KEY_SEGM_CHARS * 2 + 1] = Nul;
               strcat(full_key_buf, "-");
            }
            if((m_hInstKey3Edit != NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_hInstKey3Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)full_key_buf + strlen(full_key_buf));
               full_key_buf[KPST_NUM_OF_KEY_SEGM_CHARS * 3 + 2] = Nul;
               strcat(full_key_buf, "-");
            }
            if((m_hInstKey4Edit != NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_hInstKey4Edit, WM_GETTEXT, KPST_NUM_OF_KEY_SEGM_CHARS + 1, (LPARAM)full_key_buf + strlen(full_key_buf));
               full_key_buf[KPST_NUM_OF_KEY_SEGM_CHARS * 4 + 3]=Nul;
            }

            if(SUCCEEDED(retc)) retc = ExtractHigh(full_key_buf, &key_add, 16);

//          if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
//          if(SUCCEEDED(retc)) retc = GetLicHighHp11(&lic_high); // jau nebereikia
            if(SUCCEEDED(retc))
            {
//             retc = SaveRestDaysInitHp11AndInit(key_add); // èia negerai – HP11_LICID dar nenustatytas
               retc = SaveRestDaysInitHp11(key_add); // tik atsimenam á KP11_REST_DAYS_INIT, á failà áraðinësim ir inicializuosim po CheckReg() – kai jau bus nustatytas HP11_LICID
               if(FAILED(retc)) KP_ERROR(retc, null);
            }

            if(SUCCEEDED(retc)) retc = ScanInstKeyFull(full_key_buf);

// -----------------
            if(SUCCEEDED(retc)) retc=TestKey();

            if(SUCCEEDED(retc)) endfl=True; // (retc!=KP_E_ILL_CODE)
            else
            {
               KpMsgOut(KPST_MSG_BLOGAS_DIEG_RAKTAS, IDI_ERROR, KP_MB_TESTI);
               SetFocus(m_hInstKey4Edit);
               retc=S_OK;
            }

            break;

         case IDCANCEL:
            endfl=True;
            retc=KP_E_CANCEL;
            break;
         }
      }

   } while((!endfl) && SUCCEEDED(retc));

   if(m_hKeyDialogWindow!=NULL)
   {
      if(!(::DestroyWindow(m_hKeyDialogWindow)))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }
   m_hKeyDialogWindow=NULL;

#ifdef Debug
char str_buf[100];
sprintf(str_buf, "%d", retc);
KP_TRACE(str_buf);
#endif

return(retc);
}
