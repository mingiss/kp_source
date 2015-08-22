// -------------------------------------
// kpstaps.cpp
// klasės KpStSelDownload realizacija
//


// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

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
#include "kpwindow.h"
#include "kperr.h"
#include "kpttucf.h"
#include "kpsock.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
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
#include "xmlis.h"
#include "xmli.h"
#include "xmlg.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstaps.h"


// ----------------------------------
KpStSelDownload *KpStSelDownDialogPtr = NULL;


// ----------------------------------
KpStSelDownload::KpStSelDownload(void)
{
   m_lhOpenResult = S_OK;
   ClearControls();
}


// ----------------------------------
void KpStSelDownload::ClearControls(void)
{
   m_hDialogWindow = NULL;

   m_DownListBox = NULL;

   m_NoMoreBox = NULL;
// m_bTestUpdates = True;

   m_OkButton = NULL;
   m_CancelButton = NULL;

   m_bShiftFl = False;

   m_iProdVer = 0;
}


// ----------------------
HRESULT KpStSelDownload::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// ----------------------------------
HRESULT KpStSelDownload::OpenWindow(int iProdVer, const unsigned char *lpszProdName, bool bUpdFl)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

   KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(theKpStAppPtr->m_hInstance != NULL, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(KpStSelDownDialogPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = CloseWindow();

unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) 
   {
      if(lpszProdName != null)
      {
         KP_ASSERT(strlen(lpszProdName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc)) strcpy(prod_name, lpszProdName);  
      }
      else retc = theKpStAppPtr->GetIniProdName(prod_name);
   }

WNDCLASSEX wcx;
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = theKpStAppPtr->m_hInstance;
      wcx.lpszClassName = "KPSTSELDOWN",
      wcx.lpfnWndProc   = (WNDPROC)KpStSelDownDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(theKpStAppPtr->m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
      wcx.hIconSm       = LoadIcon(theKpStAppPtr->m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
//       KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());
      }
   }

unsigned char wnd_title[KP_MAX_FNAME_LEN + 100];
   KP_ASSERT(strlen(bUpdFl?KPST_MSG_SELUPD_TITLE:KPST_MSG_SELDOWN_TITLE) + 3 + strlen(prod_name) < KP_MAX_FNAME_LEN + 100,
      KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(wnd_title, bUpdFl?KPST_MSG_SELUPD_TITLE:KPST_MSG_SELDOWN_TITLE);
      strcat(wnd_title, " - ");
      strcat(wnd_title, prod_name);
   }

KpStSelDownloadPars dlg_pars;
   if(SUCCEEDED(retc))
   {
      dlg_pars.m_iProdVer = iProdVer;
      strcpy(dlg_pars.m_lpszProdName, prod_name); 
      dlg_pars.m_bUpdFl = bUpdFl;
   }
   
   if(SUCCEEDED(retc))
      m_hDialogWindow = CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPSTSELDOWN",
         (const char *)wnd_title,                // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         KPST_SELDOWN_WND_X, // CW_USEDEFAULT, // int x,               // horizontal position of window
         KPST_SELDOWN_WND_Y, // CW_USEDEFAULT, // int y,               // vertical position of window
         KPST_SELDOWN_WND_DX,         // int nWidth,           // window width
         KPST_SELDOWN_WND_DY,
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         theKpStAppPtr->m_hInstance,
         &dlg_pars               // LPVOID lpParam        // pointer to window-creation data
      );

   KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

// --------------------------- iškeliam į viršų – lzdshp.exe iškviečiant per Help meniu mygtuką „Tikrinti versiją“ kažkodėl palindęs po kitais langais  
WINDOWPLACEMENT wnd_pl;
   if(SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) KpSleep(500);
      retc0 = S_OK;
      KP_ASSERT00(GetWindowPlacement(m_hDialogWindow, &wnd_pl), KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc0)) wnd_pl.showCmd = SW_SHOWNORMAL;
      KP_ASSERT00(SetWindowPlacement(m_hDialogWindow, &wnd_pl), KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT00(SetWindowPos(m_hDialogWindow, HWND_TOPMOST, 0, 0, 100, 100, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE), KP_E_SYSTEM_ERROR, null, True);
   }
      
return(retc);
}


// -----------------------------------------
BOOL CALLBACK KpStSelDownDialogProc
(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
int retp = LOWORD(wParam);
bool endfl = False;
bool close_window = False;
BOOL retw = False;
CREATESTRUCT *csp = NULL;
KpStSelDownloadPars *dlg_pars_ptr = NULL;
 
   KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(KpStSelDownDialogPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
// ------------------------------------ parametrai
      if(SUCCEEDED(retc))
      {
         csp = (LPCREATESTRUCT)lParam;
         KP_ASSERT(csp != NULL, KP_E_SYSTEM_ERROR, null, True);
      }
      if(SUCCEEDED(retc)) dlg_pars_ptr = (KpStSelDownloadPars *)csp->lpCreateParams;
      KP_ASSERT(dlg_pars_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   
// ------------------------------------ tekstai
      if(SUCCEEDED(retc)) /* retc = */ KpCreateIcon(hKpInstance, hwndDlg, NULL, KP_IDI_SETUP_ICON, KPST_SELDOWN_ICON_X, KPST_SELDOWN_ICON_Y, KPST_SELDOWN_ICON_WDT, KPST_SELDOWN_ICON_WDT, 0);

      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, dlg_pars_ptr->m_lpszProdName, KPST_SELDOWN_HEAD_X, KPST_SELDOWN_HEAD_Y, 1, KPW_CONTROL_STYLE_BOLD, 0, 0, NULL);

      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, dlg_pars_ptr->m_bUpdFl?KPST_MSG_SELUPD_TITLE:KPST_MSG_SELDOWN_TITLE, KPST_SELDOWN_SUBHEAD_X, KPST_SELDOWN_SUBHEAD_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, dlg_pars_ptr->m_bUpdFl?KPST_MSG_SELUPD_PROMPT:KPST_MSG_SELDOWN_PROMPT, KPST_SELDOWN_PROMPT_X, KPST_SELDOWN_PROMPT_Y, KPST_SELDOWN_PROMPT_NUMLINES, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

// ------------------------------------ listbox
      KP_ASSERT(theKpStAppPtr->m_aGrpDownLoads != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateListBox(hKpInstance, hwndDlg, &(KpStSelDownDialogPtr->m_DownListBox), (const unsigned char *)"Sąrašas:",
                                 KPST_SELDOWN_LISTBOX_WDT, KPST_SELDOWN_LISTBOX_HGT, KPST_SELDOWN_LISTBOX_X, KPST_SELDOWN_LISTBOX_Y,
                                 KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE|ES_SUNKEN, 0L,
                                 theKpStAppPtr->m_aGrpDownLoads, -1,
                                 TYP_ListBoxChk, // TYP_ListBox,
                                 KPST_SELDOWN_LISTBOX_MAX_NUM_OF_ROWS
                                 );
      KP_ASSERT(KpStSelDownDialogPtr->m_DownListBox != NULL, KP_E_SYSTEM_ERROR, null, False);

      if(SUCCEEDED(retc)) retc = SetListBoxSel(KpStSelDownDialogPtr->m_DownListBox, 0);
//    if(SUCCEEDED(retc)) ShowWindow(KpStSelDownDialogPtr->m_DownListBox, SW_SHOW); // SW_HIDE);
//    KP_ASSERT(SetWindowPos(KpStSelDownDialogPtr->m_DownListBox, HWND_TOP, KPST_SELDOWN_LISTBOX_X, KPST_SELDOWN_LISTBOX_Y, KPST_SELDOWN_LISTBOX_WDT, KPST_SELDOWN_LISTBOX_HGT, 0), KP_E_SYSTEM_ERROR, GetLastError(), False);

// ------------------------------------ checkboxas „daugiau netikrinti“
bool chk_updates;
      chk_updates = True;
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetTestUpdates(&chk_updates, dlg_pars_ptr->m_iProdVer); // atmintukinio produkto .ini failas jau perskaitytas KpStApp::CheckUpdate()
      if(SUCCEEDED(retc)) KpStSelDownDialogPtr->m_iProdVer = dlg_pars_ptr->m_iProdVer;

      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, dlg_pars_ptr->m_bUpdFl?KPST_MSG_SELUPD_NOMORE_PROMPT:KPST_MSG_SELDOWN_NOMORE_PROMPT, KPST_SELDOWN_NOMORE_PROMPT_X, KPST_SELDOWN_NOMORE_Y, KPST_SELDOWN_NOMORE_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateCheckBox(hKpInstance, hwndDlg, &(KpStSelDownDialogPtr->m_NoMoreBox), KPST_SELDOWN_NOMORE_BOX_X, KPST_SELDOWN_NOMORE_BOX_Y, 0, 0);
      KP_ASSERT(KpStSelDownDialogPtr->m_NoMoreBox != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) SendMessage(KpStSelDownDialogPtr->m_NoMoreBox, BM_SETCHECK, (WPARAM)(chk_updates?BST_UNCHECKED:BST_CHECKED), 0);
//    if(SUCCEEDED(retc)) KpStSelDownDialogPtr->m_bTestUpdates = chk_updates;

// ------------------------------------ OK Cancel mygtukai
      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, dlg_pars_ptr->m_bUpdFl?KPST_MSG_SELUPD_BUT_PROMPT:KPST_MSG_SELDOWN_BUT_PROMPT, KPST_SELDOWN_BUT_PROMPT_X, KPST_SELDOWN_BUT_PROMPT_Y, KPST_SELDOWN_BUT_PROMPT_NUMLINES, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) /* retc = */ KpCreateButton(hKpInstance, hwndDlg, &(KpStSelDownDialogPtr->m_OkButton), IDOK, KP_MSG_GERAI, KPST_SELDOWN_OK_BUT_X, KPST_SELDOWN_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpStSelDownDialogPtr->m_OkButton != NULL, KP_E_SYSTEM_ERROR, null, False);

      if(SUCCEEDED(retc)) /* retc = */ KpCreateButton(hKpInstance, hwndDlg, &(KpStSelDownDialogPtr->m_CancelButton), IDCANCEL, KP_MSG_ATSAUKTI, KPST_SELDOWN_CANCEL_BUT_X, KPST_SELDOWN_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      KP_ASSERT(KpStSelDownDialogPtr->m_CancelButton != NULL, KP_E_SYSTEM_ERROR, null, False);

      KP_ASSERT(SetFocus(KpStSelDownDialogPtr->m_OkButton),
         KP_E_SYSTEM_ERROR, GetLastError(), False);

      break;

// -------------------------------
   case WM_INITDIALOG:
      retw = True;
      break;

// -------------------------------
   case WM_PAINT:
      {
HDC hdc = NULL;
PAINTSTRUCT ps;

         if(SUCCEEDED(retc)) hdc = BeginPaint(hwndDlg, &ps);
         KP_ASSERT(hdc != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPST_SELDOWN_LINE_X1, KPST_SELDOWN_LINE1_Y, KPST_SELDOWN_LINE_X2, KPST_SELDOWN_LINE1_Y, KP_WND_SUNKEN, NULL);
         if(SUCCEEDED(retc)) retc = KpDrawLine(hdc, KPST_SELDOWN_LINE_X1, KPST_SELDOWN_LINE2_Y, KPST_SELDOWN_LINE_X2, KPST_SELDOWN_LINE2_Y, KP_WND_SUNKEN, NULL);

         if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

         retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      }
      break;

// -------------------------------
   case WM_CLOSE:
      retc = KP_E_CANCEL; // tik šitam dialogui
      endfl = True;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

// -------------------------------
   case WM_QUIT:
      switch(retp)
      {
      case IDCANCEL: retc = KP_E_CANCEL; break;
      case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      close_window = True; // ???
      retc = KP_E_CANCEL; // tik šitam dialogui
      endfl = True;
      break;

// -------------------------------
   case WM_COMMAND:
      switch(retp)
      {
      case IDOK:
         close_window = True;
         endfl = True;
         break;

      case IDCANCEL:
         close_window = True;
         retc = KP_E_CANCEL;
         endfl = True;
         break;
         
// -------------------------------
      case BN_CLICKED:
PutLogMessage("KpStSelDownDialogProc() BN_CLICKED");
         if(SUCCEEDED(retc)) /* if(KpStSelDownDialogPtr != NULL) */ if(KpStSelDownDialogPtr->m_NoMoreBox != NULL)
         {
//          KpStSelDownDialogPtr->m_bTestUpdates = (SendMessage(KpStSelDownDialogPtr->m_NoMoreBox, BM_GETSTATE, 0, 0) & BST_CHECKED) == 0);
//          /* retc = */ theKpStAppPtr->SetTestUpdates(KpStSelDownDialogPtr->m_bTestUpdates, KpStSelDownDialogPtr->m_iProdVer);
            /* retc = */ theKpStAppPtr->SetTestUpdates((SendMessage(KpStSelDownDialogPtr->m_NoMoreBox, BM_GETSTATE, 0, 0) & BST_CHECKED) == 0, KpStSelDownDialogPtr->m_iProdVer);
PutLogMessage_("KpStSelDownDialogProc() BN_CLICKED: %d %x %x", (SendMessage(KpStSelDownDialogPtr->m_NoMoreBox, BM_GETSTATE, 0, 0) & BST_CHECKED), lParam, KpStSelDownDialogPtr->m_NoMoreBox);
         }
         break;
      }
      break;

// -------------------------------
   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

// -------------------------------
   if(close_window) KpStSelDownDialogPtr->CloseWindow();

#if FALSE // jau išsaugotas prie BN_CLICKED
PutLogMessage_("KpStSelDownDialogProc() galas: %d %x %lx %lx", endfl, retc, KpStSelDownDialogPtr, KpStSelDownDialogPtr->m_NoMoreBox);
   if((endfl || FAILED(retc)) && (KpStSelDownDialogPtr != NULL) /* && SUCCEEDED(retc) */)
      if((KpStSelDownDialogPtr->m_NoMoreBox != NULL) /* && SUCCEEDED(retc) */)
      {
//       /* retc = */ theKpStAppPtr->SetTestUpdates((SendMessage(KpStSelDownDialogPtr->m_NoMoreBox, BM_GETSTATE, 0, 0) & BST_CHECKED) != 0, KpStSelDownDialogPtr->m_iProdVer);
         /* retc = */ theKpStAppPtr->SetTestUpdates(KpStSelDownDialogPtr->m_bTestUpdates, KpStSelDownDialogPtr->m_iProdVer);
      }
#endif

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = True;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// ----------------------------------
HRESULT KpStSelDownload::CloseWindow(void)
{
HRESULT retc = S_OK;

   if(m_hDialogWindow != NULL)
      KP_ASSERT(::DestroyWindow(m_hDialogWindow),
         KP_E_SYSTEM_ERROR, GetLastError(), False);

   ClearControls();

return(retc);
}


// ----------------------------------
HRESULT KpStSelDownload::DoEdit(void)
{
HRESULT retc = S_OK;
MSG msg;
int retp;
bool endfl = False;
HWND cur_wnd = NULL;

   KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) do
   {
      KP_ASSERT(GetMessage(&msg, NULL, 0, 0) >= 0,
         KP_E_SYSTEM_ERROR, GetLastError(), True);
      if(SUCCEEDED(retc)) TranslateMessage(&msg);
      retp = LOWORD(msg.wParam);

      if(SUCCEEDED(retc)) switch(msg.message)
      {
// --------------------
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         retc = KP_E_CANCEL; // tik šitam dialogui
         endfl = True;
         break;

// --------------------
      case WM_CLOSE:
         retc = KP_E_CANCEL; // tik šitam dialogui
         endfl = True;
         break;

// --------------------
      case WM_CHAR:
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId != 0L)
               KP_ASSERT(PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam),
                  KP_E_SYSTEM_ERROR, GetLastError(), False);
            break;

         case Tab:
            cur_wnd = GetFocus();

            if(cur_wnd == m_NoMoreBox) SetFocus(m_bShiftFl?m_CancelButton:m_OkButton);
            else if(cur_wnd == m_OkButton) SetFocus(m_bShiftFl?m_NoMoreBox:m_CancelButton);
            else if(cur_wnd == m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_OkButton);
            else SetFocus(m_OkButton);
            break;

         case Enter:
            PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            break;

         case Esc:
            retc = KP_E_CANCEL;
            endfl = True;
            break;

         } // switch(retp)

         break; // case WM_CHAR:

// --------------------
//    case WM_KEYFIRST:
      case WM_KEYDOWN:
         switch(retp)
         {
         case Shift:
            m_bShiftFl = True;
            break;
#if FALSE
         case Dn:
            cur_wnd = GetFocus();

            if(cur_wnd == m_NoMoreBox) SetFocus(m_OkButton);
            else if(cur_wnd == m_OkButton); // SetFocus(m_OkButton);
            else if(cur_wnd == m_CancelButton); // SetFocus(m_CancelButton);
            else SetFocus(m_OkButton);
            break;

         case Up:
            cur_wnd = GetFocus();

            if(cur_wnd == m_NoMoreBox) // SetFocus(m_NoMoreBox);
            else if(cur_wnd == m_OkButton); SetFocus(m_NoMoreBox);
            else if(cur_wnd == m_CancelButton); SetFocus(m_NoMoreBox);
            else SetFocus(m_NoMoreBox);
            break;
#endif
         } // switch(retp)

         break; // case WM_KEYDOWN:

// ----------------------
      case WM_KEYUP:
         if(retp == Shift) m_bShiftFl = False;
         break;

// ----------------------
      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
// --------------------- išsitraukiam pažymėtus įrašus
// nereikia – viskas jau guli sąraše m_aGrpDownLoads

// --------------------- išsitraukiam NoMoreBox
#if FALSE // jau išsaugotas prie BN_CLICKED
bool chk_updates;
            chk_updates = True;
            if((m_NoMoreBox != NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_NoMoreBox, BM_GETSTATE, 0, 0)&BST_CHECKED) chk_updates = False;
// TODO: atkelti iš lzdsho.cpp m_bTestUpdates "TestUpdates"      if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetTestUpdates(chk_updates);
            }
//          if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIni();
#endif
            endfl = True;
            break;

         case IDCANCEL:
            retc = KP_E_CANCEL;
            endfl = True;
            break;

         } // switch(retp)

         break; // case WM_COMMAND:

      } // if(SUCCEEDED(retc)) switch(msg.message)

      DispatchMessage(&msg);

   } while((!endfl) && SUCCEEDED(retc));

return(retc);
}
