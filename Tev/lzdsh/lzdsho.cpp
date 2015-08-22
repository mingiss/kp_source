// ---------------------------
// lzdsho.cpp
// zodyno perziuros programa
// parinkciu dialogas
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
#include "xml8.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlu.h"
#include "tvxmle.h"
#include "tvxmls.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"
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
#include "lzdsho.h"


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
LzdShOptDlg::LzdShOptDlg(KpPubDlg *pOffsetWnd, int iWndCurX, int iWndCurY)
{
HRESULT retc = S_OK;

   m_lhOpenResult = S_OK;

   m_pOffsetWnd = pOffsetWnd;

// KP_ASSERTC(m_pOffsetWnd != NULL, E_POINTER, null, True);

   m_hDialogWindow = NULL;
   m_bWindowOpen = False;

   m_iWndCurX = iWndCurX;
   m_iWndCurY = iWndCurY;
   if((m_pOffsetWnd != NULL) && SUCCEEDED(retc))
   {
      m_iWndCurX = m_pOffsetWnd->m_iWndCurX + LZDSH_OPT_WND_X_OFFSET;
#if IBSH_SKIN == IBSH_SKIN_START_GRP
      m_iWndCurX += m_pOffsetWnd->m_iWndCurDX;
#endif
      m_iWndCurY = m_pOffsetWnd->m_iWndCurY + LZDSH_OPT_WND_Y_OFFSET;
   }

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
   m_hSkinBox = NULL;
#endif
#endif
   m_hUpdBox = NULL;

// m_bLButPressed = False; // left mouse button pressed flag, used for draging
   m_iMouseX = (-1);
   m_iMouseY = (-1);
   m_bCaptured = False;

   m_ButExit = NULL;

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
   m_SkinList = NULL;
   m_iCurSkin = LzdshSkinMahd;
   m_iCurSkinTmp = m_iCurSkin;
#endif
#endif

#if IBSH_SKIN != IBSH_SKIN_START_GRP
   m_bOnTop = 0L; // False;

   m_bReactToSel = 0L; // False;
#endif

   m_bTestUpdates = 0L; // = False; // (-1L); // True;

   m_OkButton = NULL;
   m_CancelButton = NULL;

// ---------------- skin list
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
   m_SkinList = NULL;
   KP_NEW(m_SkinList, KpTreeEntry(LZDSH_SKIN_STA_TXT, strlen(LZDSH_SKIN_STA_TXT) + 1, NULL));

   if(SUCCEEDED(retc)) retc = m_SkinList->PutToEnd(LZDSH_SKIN_MAHD_TXT, strlen(LZDSH_SKIN_MAHD_TXT) + 1);
#endif
#endif

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------------------
LzdShOptDlg::~LzdShOptDlg(void)
{
HRESULT retc = S_OK;
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
   KP_DELETE(m_SkinList);
#endif
#endif
}


// ----------------------------------
HRESULT LzdShOptDlg::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// ----------------------------------
HRESULT LzdShOptDlg::OpenWindow(HINSTANCE hInst)
{
HRESULT retc = S_OK;

   KP_ASSERT(hInst, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) m_hInstance=hInst;

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#  ifndef LZDSH_DELT
long ll;
static unsigned char publisher[KP_MAX_FNAME_LEN + 1];
int prod_ver = 0;
static unsigned char key_name[KP_MAX_FILE_LIN_WDT + 1];
HKEY hKey = NULL;
DWORD dwBufLen;
DWORD dwValType;

   KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);
   KP_ASSERT(m_pOffsetWnd != NULL, E_POINTER, null, True);
   KP_ASSERT(m_pOffsetWnd->m_hDialogWindow != NULL, E_POINTER, null, True);
   KP_ASSERT(m_pOffsetWnd->m_pKpFileSys != NULL, E_POINTER, null, True);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );
      if(RegOpenKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
      {
// ---------------- current skin
         dwBufLen = sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "Skin", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen) == ERROR_SUCCESS)
         {
            KP_ASSERT(dwValType == REG_DWORD, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) m_iCurSkin = ll;
         }
      }
      if(hKey)
      {
         RegCloseKey(hKey);
         hKey = NULL;
      }
   }

   m_iCurSkinTmp = m_iCurSkin;

#  endif // #  ifndef LZDSH_DELT

// ---------------- always on top
   if(SUCCEEDED(retc)) retc = m_pOffsetWnd->GetOnTop(&m_bOnTop);

// ---------------- react to selection
   if(SUCCEEDED(retc)) retc = m_pOffsetWnd->m_pKpFileSys->GetReactToSel(&m_bReactToSel);

#endif // #if IBSH_SKIN != IBSH_SKIN_START_GRP

// -------------------------- m_bTestUpdates
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetTestUpdates(&m_bTestUpdates);

// --------------------------------- "LZDSHOPT" class
HBRUSH brush;
// #if IBSH_SKIN != IBSH_SKIN_STANDART
// EXTLOGPEN log_pen;
// #endif

   if(SUCCEEDED(retc))
   {
#if IBSH_SKIN == IBSH_SKIN_STANDART
      brush=CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];
#else
#if FALSE
      if(GetObject(m_pOffsetWnd->m_aPenScheme[KpShadowNorm], sizeof(log_pen), &log_pen))
         brush = CreateSolidBrush(log_pen.elpColor);
      else
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];
      }
#else
      brush=CreateSolidBrush(KpColorSchemeLocal[KpShadowNorm]);
#endif
#endif
   }

WNDCLASSEX wcx;

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "LZDSHOPT",
      wcx.lpfnWndProc   = (WNDPROC)LzdShOptDialogProc;
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
   if(SUCCEEDED(retc))
   {
      m_iWndCurX = m_pOffsetWnd->m_iWndCurX + LZDSH_OPT_WND_X_OFFSET;
#if IBSH_SKIN == IBSH_SKIN_START_GRP
      m_iWndCurX += m_pOffsetWnd->m_iWndCurDX;
#endif
      m_iWndCurY = m_pOffsetWnd->m_iWndCurY + LZDSH_OPT_WND_Y_OFFSET;
   }

   if(SUCCEEDED(retc))
   {
      m_hDialogWindow=CreateWindowEx
      (
#if IBSH_SKIN == IBSH_SKIN_STANDART
         0,                      // DWORD dwExStyle,      // extended window style
// #elif (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#else
         WS_EX_APPWINDOW, // WS_EX_TRANSPARENT,
#endif
         "LZDSHOPT",
         LZDSH_OPT_WND_TXT, // LPCTSTR lpWindowName, // pointer to window name
#if IBSH_SKIN == IBSH_SKIN_STANDART
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
// #elif (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#else
         WS_POPUP|WS_VISIBLE,
#endif
         m_iWndCurX, // CW_USEDEFAULT, // int x,               // horizontal position of window
         m_iWndCurY, // CW_USEDEFAULT, // int y,               // vertical position of window
         LZDSH_OPT_WND_DX,           // int nWidth,           // window width
         LZDSH_OPT_WND_DY,           // int nHeight,          // window height
#ifdef KP_USE_WXWIDGETS
         (HWND)m_pOffsetWnd->m_hDialogWindow->GetHWND(),
#else
         m_pOffsetWnd->m_hDialogWindow,           // HWND hWndParent,      // handle to parent or owner window
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
BOOL CALLBACK LzdShOptDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
BOOL retw = FALSE;
int retp;
bool endfl = False;
#ifndef LZDSH_DELT
int ii;
#endif
HDC hdc = NULL;
PAINTSTRUCT ps;
HWND list_ctrl = NULL;
HWND parent_window = NULL;
#if IBSH_SKIN != IBSH_SKIN_STANDART
int ix, iy, dx, dy;
// EXTLOGPEN log_pen;
HBRUSH brush = NULL;
RECT rect;
// static HPEN capt_penscheme[KpNumOfShadows0];
static COLORREF capt_colorscheme[KpNumOfShadows0];
#endif
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver = 0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
HKEY hKey = NULL;
DWORD dwDisposition;
long retv;
DWORD ll;
#endif
#endif
HPEN pen = NULL;

   retp=LOWORD(wParam);
   endfl=False;

   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, True, null);
   KP_ASSERT(pOptDialog, KP_E_SYSTEM_ERROR, True, null);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:

      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);
//    KP_ASSERT(m_pOffsetWnd, KP_E_SYSTEM_ERROR, null, True);

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
sprintf(str_buf, "%d %d %d", sizeof(m_pOffsetWnd->m_aPenScheme), sizeof(m_pOffsetWnd->m_aPenScheme[KpCaptionColor]), sizeof(HPEN));
KP_TRACE(str_buf);
}
#endif
//    memcpy(&(capt_penscheme[KpShadowNorm]), &(m_pOffsetWnd->m_aPenScheme[KpCaptionColor]), sizeof(m_pOffsetWnd->m_aPenScheme[KpCaptionColor]));
//    memcpy(capt_penscheme, m_pOffsetWnd->m_aPenScheme, sizeof(m_pOffsetWnd->m_aPenScheme));
      memcpy(capt_colorscheme, KpColorSchemeLocal, sizeof(KpColorSchemeLocal));

//    capt_penscheme[KpShadowNorm]=m_pOffsetWnd->m_aPenScheme[KpCaptionColor];
      capt_colorscheme[KpShadowNorm]=KpColorSchemeLocal[KpCaptionColor];

//    memcpy(&capt_penscheme[KpShadowDark], &m_pOffsetWnd->m_aPenScheme[KpShadowLight], sizeof(m_pOffsetWnd->m_aPenScheme[KpShadowLight]));
//    capt_penscheme[KpShadowDark]=m_pOffsetWnd->m_aPenScheme[KpShadowLight];
      capt_colorscheme[KpShadowDark]=KpColorSchemeLocal[KpShadowLight];

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, (const unsigned char *)LZDSH_OPT_WND_TXT, LZDSH_SKIN_CAPT_TXT_X, LZDSH_SKIN_CAPT_TXT_Y, 1, KPW_CONTROL_STYLE_HEADING_3, 0, 0, capt_colorscheme); // capt_penscheme);
#endif

// -------------------- exit button
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(theOptDialog.m_ButExit), IDCANCEL /* KP_ID_EXIT */,
         LZDSH_IDI_EXIT_BITMAP,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_EXIT_LIGHT_BITMAP,
         LZDSH_IDI_EXIT_SEL_BITMAP,
#else
         LZDSH_IDI_EXIT_BITMAP,
         LZDSH_IDI_EXIT_BITMAP,
#endif
         LZDSH_OPT_BUT_EXIT_X, LZDSH_OPT_BUT_EXIT_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#else
         0,
#endif
         0, KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#endif

      KP_ASSERT(theOptDialog.m_ButExit, KP_E_SYSTEM_ERROR, True, null);

// ----------------- skin combo box prompt
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, LZDSH_SKIN_PROMT_TXT, LZDSH_SKIN_PROMPT_X, LZDSH_SKIN_PROMPT_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#  else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#  endif

// ----------------- skin combo box
      if(SUCCEEDED(retc)) retc=KpCreateComboBox(hKpInstance, parent_window, &(theOptDialog.m_hSkinBox), (const unsigned char *)"SkinBox",
// #if IBSH_SKIN == IBSH_SKIN_STANDART
         LZDSH_SKIN_BOX_DX, LZDSH_SKIN_BOX_DY*(LzdshNumOfSkins+1), LZDSH_SKIN_BOX_X, LZDSH_SKIN_BOX_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE|ES_SUNKEN, 0, theOptDialog.m_SkinList, 0);
// #elif (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
//       LZDSH_SKIN_BOX_DX-2*KPW_CTRL_BORDER_WDT, LZDSH_SKIN_BOX_DY*(LZDSH_NUM_OF_SKINS+1),
//       LZDSH_SKIN_BOX_X+KPW_CTRL_BORDER_WDT, LZDSH_SKIN_BOX_Y+KPW_CTRL_BORDER_WDT,
//       KPW_CONTROL_STYLE_NORMAL, 0, 0, theOptDialog.m_SkinList, 0);
// #endif
      if((theOptDialog.m_hSkinBox==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(SendMessage(theOptDialog.m_hSkinBox, CB_SETCURSEL, theOptDialog.m_iCurSkinTmp, 0L)==CB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
#endif

// ----------------- update check box
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, LZDSH_UPD_PROMT_TXT, LZDSH_UPD_PROMPT_X, LZDSH_UPD_PROMPT_Y, LZDSH_UPD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#endif
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, parent_window, &(theOptDialog.m_hUpdBox), LZDSH_UPD_BOX_X, LZDSH_UPD_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(theOptDialog.m_hUpdBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(theOptDialog.m_hUpdBox, BM_SETCHECK, (WPARAM)(theOptDialog.m_bTestUpdates?BST_CHECKED:BST_UNCHECKED), 0);

// ----------------- always on top check box
#if IBSH_SKIN != IBSH_SKIN_START_GRP
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, LZDSH_ONTOP_PROMT_TXT, LZDSH_ONTOP_PROMPT_X, LZDSH_ONTOP_PROMPT_Y, LZDSH_ONTOP_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#  else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#  endif
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, parent_window, &(theOptDialog.m_hOnTopBox), LZDSH_ONTOP_BOX_X, LZDSH_ONTOP_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(theOptDialog.m_hOnTopBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(theOptDialog.m_hOnTopBox, BM_SETCHECK, (WPARAM)(theOptDialog.m_bOnTop?BST_CHECKED:BST_UNCHECKED), 0);
#endif

// ----------------- react to selection check box
#if IBSH_SKIN != IBSH_SKIN_START_GRP
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, LZDSH_REACT_PROMT_TXT, LZDSH_REACT_PROMPT_X, LZDSH_REACT_PROMPT_Y, LZDSH_REACT_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#  else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#  endif
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, parent_window, &(theOptDialog.m_hReactBox), LZDSH_REACT_BOX_X, LZDSH_REACT_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(theOptDialog.m_hReactBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(theOptDialog.m_hReactBox, BM_SETCHECK, (WPARAM)(theOptDialog.m_bReactToSel?BST_CHECKED:BST_UNCHECKED), 0);
#endif

// ------------------------ OK/Cancel buttons
      if(SUCCEEDED(retc))
      {
#if IBSH_SKIN == IBSH_SKIN_STANDART
         retc=KpCreateButton
#else
         retc=KpCreateButtonLoc
#endif
            (hKpInstance, parent_window, &(theOptDialog.m_OkButton), IDOK,
            LZDSH_OPT_OK_BUT_TXT,
            LZDSH_OPT_OK_BUT_X, LZDSH_OPT_BUT_Y, LZDSH_TXT_BUT_WDT, LZDSH_TXT_BUT_HGT,
#if IBSH_SKIN == IBSH_SKIN_STANDART
            0, 0);
#else
            0, // KP_WND_UNPROC_BUT,
            0, KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#endif
      }
      if((theOptDialog.m_OkButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
#if IBSH_SKIN == IBSH_SKIN_STANDART
         retc=KpCreateButton
#else
         retc=KpCreateButtonLoc
#endif
            (hKpInstance, parent_window, &(theOptDialog.m_CancelButton), IDCANCEL,
            LZDSH_OPT_CANCEL_BUT_TXT,
            LZDSH_OPT_CANCEL_BUT_X, LZDSH_OPT_BUT_Y, LZDSH_TXT_BUT_WDT, LZDSH_TXT_BUT_HGT,
#if IBSH_SKIN == IBSH_SKIN_STANDART
            0, 0);
#else
            0, // KP_WND_UNPROC_BUT,
            0, KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#endif
      }
      if((theOptDialog.m_CancelButton==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "created %d", theOptDialog.m_hSkinBox);
KP_TRACE(str_buf);
}
#endif

// -------------------------------
      if(SUCCEEDED(retc))
#ifdef LZDSH_DELT
         if(!SetFocus(theOptDialog.m_hUpdBox))
#else
#if IBSH_SKIN == IBSH_SKIN_START_GRP
         if(!SetFocus(theOptDialog.m_hUpdBox))
#else
         if(!SetFocus(theOptDialog.m_hSkinBox))
#endif
#endif
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
//    KP_ASSERT(m_pOffsetWnd, KP_E_SYSTEM_ERROR, null, True);

      hdc=NULL;
      if(SUCCEEDED(retc))
      {
//       hdc=GetDC(hwndDlg);
         hdc=BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// ------------------------------- lines
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, LZDSH_OPT_LINE_X, LZDSH_OPT_LINE_1_Y, LZDSH_OPT_LINE_X+LZDSH_OPT_LINE_DX, LZDSH_OPT_LINE_1_Y, KP_WND_SUNKEN,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#  else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#  endif
#endif
#endif

#if FALSE
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, LZDSH_OPT_LINE_X, LZDSH_OPT_LINE_2_Y, LZDSH_OPT_LINE_X+LZDSH_OPT_LINE_DX, LZDSH_OPT_LINE_2_Y, KP_WND_SUNKEN,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#  else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#  endif
#endif

      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, LZDSH_OPT_LINE_X, LZDSH_OPT_LINE_3_Y, LZDSH_OPT_LINE_X+LZDSH_OPT_LINE_DX, LZDSH_OPT_LINE_3_Y, KP_WND_SUNKEN,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                                    NULL);
#else
                                    KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
#endif

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
//       if(GetObject(pen?pen:m_pOffsetWnd->m_aPenScheme[KpCaptionColor], sizeof(log_pen), &log_pen))
         {
//          if(SUCCEEDED(retc))
            {
               rect.left=LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR;
               rect.top=LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR;
               rect.right=LZDSH_OPT_WND_DX-LZDSH_WND_BORDER_WDT*2-LZDSH_WND_BORDER_COR*2+1;
               rect.bottom=LZDSH_WND_BORDER_WDT+LZDSH_OPT_WND_MARGIN_UP+1;
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
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, 0, 0, LZDSH_OPT_WND_DX, LZDSH_OPT_WND_DY, KP_WND_RAISED_BORDER, KpColorSchemeLocal); // m_pOffsetWnd->m_aPenScheme);
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
      if(theOptDialog.m_bCaptured)
      {
         ReleaseCapture();
         theOptDialog.m_bCaptured=False;
      }

      theOptDialog.m_iMouseX=(-1);
      theOptDialog.m_iMouseY=(-1);
      break;

   case WM_CAPTURECHANGED:
// KP_TRACE("WM_CAPTURECHANGED");
      theOptDialog.m_iMouseX=(-1);
      theOptDialog.m_iMouseY=(-1);
      break;

// case WM_MOUSEFIRST:
   case WM_MOUSEMOVE:
// ----------------- lango stumdymas
      if((wParam&MK_LBUTTON)!=0)
      {
         ix=GET_X_LPARAM /* LOWORD */(lParam)+theOptDialog.m_iWndCurX;
         iy=GET_Y_LPARAM /* HIWORD */(lParam)+theOptDialog.m_iWndCurY;

         dx=ix-theOptDialog.m_iMouseX;
         dy=iy-theOptDialog.m_iMouseY;

#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "WM_MOUSEMOVE %d %d %d %d %d %d",
   theOptDialog.m_hDialogWindow,
   theOptDialog.m_iMouseX, theOptDialog.m_iMouseY,
   (theOptDialog.m_hDialogWindow!=NULL),
   (theOptDialog.m_iMouseX>=0), (theOptDialog.m_iMouseY>=0));
KP_TRACE(str_buf);
}
#endif

         if(
            (theOptDialog.m_hDialogWindow!=NULL) &&
            (theOptDialog.m_iMouseX>=0) && (theOptDialog.m_iMouseY>=0)
           )
         {

            if(!theOptDialog.m_bCaptured)
            {
               SetCapture(theOptDialog.m_hDialogWindow);
               theOptDialog.m_bCaptured=True;
            }

            theOptDialog.m_iWndCurX+=dx;
            theOptDialog.m_iWndCurY+=dy;

#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "WM_MOUSEMOVE ---- %d %d", theOptDialog.m_iWndCurX, theOptDialog.m_iWndCurY);
KP_TRACE(str_buf);
}
#endif

            if(!SetWindowPos(theOptDialog.m_hDialogWindow, HWND_TOP,
               theOptDialog.m_iWndCurX, theOptDialog.m_iWndCurY,
               LZDSH_OPT_WND_DX, LZDSH_OPT_WND_DY,
               0))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
         }

         theOptDialog.m_iMouseX=ix;
         theOptDialog.m_iMouseY=iy;
      }
      break;
#endif

// ---------------------------------------
   case WM_COMMAND:
      switch(retp)
      {
      case KP_ID_UPDATE:
#ifdef KPST_UPDATE_OLD_LAUNCH
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->CheckUpdate(null, True, True);
#else
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SendCheckUpdateMsg();
#endif
         break;

//-----------------
      case IDOK:
         if((theOptDialog.m_hUpdBox!=NULL) && SUCCEEDED(retc))
         {
            if(SendMessage(theOptDialog.m_hUpdBox, BM_GETSTATE, 0, 0)&BST_CHECKED) theOptDialog.m_bTestUpdates = True;
            else theOptDialog.m_bTestUpdates = False;
         }

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#  ifndef LZDSH_DELT
         theOptDialog.m_iCurSkin = theOptDialog.m_iCurSkinTmp;
#  endif

         if((theOptDialog.m_hOnTopBox != NULL) && SUCCEEDED(retc))
         {
            if(SendMessage(theOptDialog.m_hOnTopBox, BM_GETSTATE, 0, 0)&BST_CHECKED) theOptDialog.m_bOnTop = True;
            else theOptDialog.m_bOnTop = False;
         }

         if((theOptDialog.m_hReactBox!=NULL) && SUCCEEDED(retc))
         {
            if(SendMessage(theOptDialog.m_hReactBox, BM_GETSTATE, 0, 0)&BST_CHECKED) theOptDialog.m_bReactToSel = True;
            else theOptDialog.m_bReactToSel = False;
         }
#endif // #if IBSH_SKIN != IBSH_SKIN_START_GRP

// -------- save test updates flag
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetTestUpdates(theOptDialog.m_bTestUpdates);

// -------- save skin type etc.

#if IBSH_SKIN != IBSH_SKIN_START_GRP
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

         if(SUCCEEDED(retc))
         {
            sprintf((char *)key_name,
               "Software\\%s\\%d", // "Software\\%s\\%s",
               publisher,
               prod_ver // prod_name
               );

            if((retv=RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
               (LPCTSTR)key_name,
               0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &hKey, &dwDisposition))!=ERROR_SUCCESS)
               {
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, True, __FILE__, __LINE__, 0L, NULL);
                  hKey = NULL;
               }
         }

#  ifndef LZDSH_DELT
         if(SUCCEEDED(retc))
            if((retv = RegSetValueEx(hKey, "Skin", 0, REG_DWORD,
               (BYTE *)&theOptDialog.m_iCurSkin, sizeof(theOptDialog.m_iCurSkin))) != ERROR_SUCCESS)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, True, __FILE__, __LINE__, 0L, NULL);
#  endif

         ll = theOptDialog.m_bOnTop;
         if(SUCCEEDED(retc))
            if((retv = RegSetValueEx(hKey, "OnTop", 0, REG_DWORD,
               (BYTE *)&ll, sizeof(ll))) != ERROR_SUCCESS)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, True, __FILE__, __LINE__, 0L, NULL);

         ll = theOptDialog.m_bReactToSel;
         if(SUCCEEDED(retc))
            if((retv = RegSetValueEx(hKey, "ReactToSel", 0, REG_DWORD,
               (BYTE *)&ll, sizeof(ll))) != ERROR_SUCCESS)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, True, __FILE__, __LINE__, 0L, NULL);

         if(hKey)
         {
            retw = RegCloseKey(hKey);
#  ifdef Debug
            if(retw != ERROR_SUCCESS)
            {
//             retc=KP_E_SYSTEM_ERROR;
#     ifdef Debug
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#     endif
            }
#  endif
            hKey = NULL;
         }

#endif // #if IBSH_SKIN != IBSH_SKIN_START_GRP

// ---------------------
#if IBSH_SKIN != IBSH_SKIN_START_GRP
         if(SUCCEEDED(retc)) if(theOptDialog.m_pOffsetWnd != NULL)
         {
            retc = theOptDialog.m_pOffsetWnd->BringToTop(theOptDialog.m_bOnTop);
            if(SUCCEEDED(retc)) if(theOptDialog.m_pOffsetWnd->m_pKpFileSys != NULL)
               theOptDialog.m_pOffsetWnd->m_pKpFileSys->SetReactToSel(theOptDialog.m_bReactToSel); // m_bReactToSelFlag = theOptDialog.m_bReactToSel;
         }
#endif

// ---------------------
         endfl=True;
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

// --------------------
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
      if(!endfl)
         switch(HIWORD(wParam))
         {
         case LBN_SELCHANGE:
//       case CBN_SELCHANGE:
            list_ctrl=(HWND)lParam;
            if(list_ctrl==theOptDialog.m_hSkinBox)
            {
               ii=SendMessage(theOptDialog.m_hSkinBox, CB_GETCURSEL, 0, 0);
               if(ii==LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(((ii<0) || (ii>=LzdshNumOfSkins)) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               if(SUCCEEDED(retc))
                  theOptDialog.m_iCurSkinTmp = ii;

               if(SUCCEEDED(retc))
                  KpMsgOut("Lango stilius pasikeis, programà paleidus ið naujo.", IDI_ASTERISK, KP_MB_TESTI);
            }
            break;

         } // switch(HIWORD(wParam))
#endif
#endif

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
//       if(msg.hwnd==theOptDialog.m_hDialogWindow)
         {
            if(theOptDialog.m_hDialogWindow!=NULL)
            {
               if(!(::DestroyWindow(theOptDialog.m_hDialogWindow)))
               {
#ifdef Debug
// jau buna uzsidares
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
               }
            }
            theOptDialog.m_hDialogWindow=NULL;
         }

//--------------------------
      theOptDialog.m_bWindowOpen = False;

// -------------------------
#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifdef IBSH_RES_MODE_XGECKO
// kaþko iðkvieèia 20 kartø
// PutLogMessage_("LzdShOptDialogProc(): RefreshResCtrl()");
      if(SUCCEEDED(retc)) if(theOptDialog.m_pOffsetWnd /* && (iWindowsVersion < WinVistaC) */ )
         retc = theOptDialog.m_pOffsetWnd->RefreshResCtrl(); // kaþko iðvalo rezultato langà
#endif
#endif

//--------------------------
//    PostMessage(NULL, uMsg, wParam, lParam);
      retw = TRUE;
   }

   if(/* (uMsg!=WM_QUIT) && */ FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// ----------------------------------
#if FALSE
HRESULT LzdShOptDlg::DoEdit(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
MSG msg;
int retp;
bool endfl=False;

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         TranslateMessage(&msg);

      if(SUCCEEDED(retc)) // if(msg.hwnd==theOptDialog.m_hDialogWindow)
      {
         DispatchMessage(&msg);

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
            break;

         case WM_CHAR:
            if(m_pOffsetWnd != NULL)
               if(m_pOffsetWnd->m_CurList == m_pOffsetWnd->m_MainList) theOptDialog.m_bReactToSel->SetKbdInput(True); // lzdsh_search->m_bKbdInput = True;

            switch(retp)
            {
            case KP_HP11_TOGGLE_CONSOLE:
               if(lKphp11ThreadId!=NULL)
                  if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               break;

            case Esc:
               PostMessage(NULL, WM_COMMAND, IDCANCEL, 0);
               break;
            }

         case WM_COMMAND:
            switch(retp)
            {
            case IDOK:
               endfl=True;
               break;
            case IDCANCEL:
               endfl=True;
               break;
//          case KP_ID_EXIT:
//             PostQuitMessage(IDOK);
//             endfl=True;
//             break;
#if FALSE // #ifdef Debug
            default:
{
char str_buf[100];
sprintf(str_buf, "%d", retp);
KP_TRACE(str_buf);
}
               break;
#endif
            }
            break;

#if FALSE // #ifdef Debug
         case WM_LBUTTONDOWN:
{
char str_buf[100];
sprintf(str_buf, "WM_LBUTTONDOWN %d DoEdit()", msg.hwnd);
KP_TRACE(str_buf);
}
            break;
#endif

#if FALSE // #ifdef Debug
         case 15:
         case 160:
         case 161:
         case 275:
         case 280:
         case 512:
         case 513:
         case 514:
         case 674:
            break;
         default:
{
char str_buf[100];
sprintf(str_buf, "%d", msg.message);
KP_TRACE(str_buf);
}
            break;
#endif
         } // if(SUCCEEDED(retc)) switch(msg.message)

      } // if(msg.hwnd==theOptDialog.m_hDialogWindow)

   } while((!endfl) && SUCCEEDED(retc));

   if(m_hDialogWindow!=NULL)
   {
      if(!(::DestroyWindow(m_hDialogWindow)))
      {
#ifdef Debug
// jau buna uzsidares
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   }

   theOptDialog.m_bWindowOpen = False;

return(retc);
}
#endif
