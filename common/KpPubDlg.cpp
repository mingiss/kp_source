// ---------------------------------------
// KpPubDlg.cpp
// dialogas su publishinimo langu (tux_gecko, MSHTML, RichEdit) - dël lzdshl ir arkshl
//

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#if Compiler != Watcom
using namespace std;
#endif

#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
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
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11w.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
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
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpMsHtml.h"
#include "KpRtfDlg.h"
#include "xmln.h"
#include "xmlu.h"
#include "kpstap.h"
#include "iBsh.h"
#include "iBshr.h"
#include "iBshl.h"

// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif


// #define Logging // TODO: dar reikia patestuot – m_bResizing kai kada nenusiima per WM_WINDOWPOSCHANGED (IBSH_SKIN_STANDART)


// ----------------------------------
KpPubDlg::KpPubDlg(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers, UC_Modes iEncMode,
      const unsigned char *lpszCaption,
      int iWndDXmin, int iWndDXmax, int iWndDYmin, int iWndDYmax,
      int iWndSoftBorderWdt, int iWndSoftCaptHgt, int iWndHardBorderWdt, int iWndHardCaptHgt,
      int iScrX, int iScrY, int iScrDX, int iScrDY,
      int iResDXenl, int iResDYenl,
      DWORD dwStyle, int iInitWndX, int iInitWndY, int iInitWndDX, int iInitWndDY,
      HWND hParent)
: KpWnd(NULL, TYP_KpDialog, lpszCaption, hParent, hKpInstance,
      NULL, NULL, KPW_CONTROL_STYLE_NORMAL,
      iInitWndDX, iInitWndDY, 1, 1, 0, dwStyle, NULL)
{
HRESULT retc = m_lhOpenResult;

// ------------
// KP_ASSERTC(pKpFileSys != NULL, E_INVALIDARG, null, True);
   m_pKpFileSys = pKpFileSys;

// ------------
   m_iXmlVers = iXmlVers;
   m_iEncMode = iEncMode;

// ------------
   m_hDialogWindow = NULL;

   m_hCaption = NULL;
   m_lpszCaption[0] = Nul;
   KP_ASSERT(lpszCaption != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszCaption) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(m_lpszCaption, lpszCaption);
   m_lpszCaption[KP_MAX_FNAME_LEN] = Nul;

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   m_hPubIcon = NULL;
   m_hBackGround = NULL;
   m_ButExit =  NULL;
   m_ButMinimize = NULL;
#endif

// ------------- buvæ LzdShDlg laukai
   m_MainList = NULL;
   m_SearchList = NULL;
   m_HistList = NULL;
   m_CurList = NULL;

   m_DictList = NULL;
   m_iCurDictEntry = 0;

#ifdef LZDSHT_DISPLAY_SINGLE_THREAD
   m_bNewContentReady = False;
#endif

   m_iCtrlCtbl = TV_IX_CTBL;

#ifdef IBSH_RES_MODE_XGECKO
   m_bDictChanged = False;
#endif

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   m_BgrBmpData.m_hBitMap = NULL;
   m_BgrBmpData.m_hdcBmpHdc = NULL;
#endif

// #if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// h_hBckGrnd = NULL;
// m_hdcBckGrnd = NULL;
// #endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   m_LogoBmpData.m_hBitMap = NULL; // m_hLogoBmp = NULL;
   m_LogoBmpData.m_hdcBmpHdc = NULL; // m_hdcLogo = NULL;
#endif

// m_MenuButFile = NULL;
   m_MenuButOpt = NULL;
   m_MenuButHelp = NULL;

   m_InpEdit = NULL;

   m_TabMain = NULL;
   m_TabSearch = NULL;
   m_TabHist = NULL;

   m_iNumOfDictEntries = 0;
   m_iNumOfLines = 16; // LZDSH_LIST_NUM_LINES;

#ifdef IBSH_RES_MODE_XGECKO
   m_ButBack = NULL;
   m_ButForward = NULL;
#endif

   m_ButSearch = NULL;
   m_ButFontZoom = NULL;
   m_ButNarrow = NULL;
   m_ButAcc = NULL;

   m_DictBox = NULL;

   m_bDiagOnTop = False;
   m_iDiagOnTopCnt = 9999; // kad LzdShSearch::DisplayResult() paþintø pirmà kartà // (-1); // 0;

   m_hCurSav = NULL;

#ifdef LZDSHT_SEARCH_SINGLE_THREAD
   m_bButSearchPressed=False;
#endif

   m_lpszCurDictName[0] = Nul;
#ifdef IBSH_RES_MODE_XGECKO
   m_lpszSelDictName[0] = Nul;
#endif

   m_iNumOfHistEntries = 0;
// -------------

// ------------- buvæ KpGeckoDialog laukai
#ifdef IBSH_RES_MODE_XGECKO
   m_pResCtrl = NULL;
#endif
// -------------

// -------------------------
// atkelta ið LzdShDlg
#ifdef IBSH_RES_MODE_RTF
   m_ResRichEdit = NULL;
#  ifdef LZDSH_EDITOR_BUILD
#     ifdef Debug
// m_ResRichTest = NULL;
#     endif
#  endif
#endif
// -------------

   m_RedrawTimer = 0;
   m_iDoRedraw = 0;

   m_dwStyle = dwStyle;

   m_iWndCurX = iInitWndX;
   m_iWndCurY = iInitWndY;

   m_iWndCurDX = m_iWndCurDXprec = m_iWndDX = iInitWndDX;
   m_iWndCurDY = m_iWndCurDYprec = m_iWndDY = iInitWndDY;

   m_iWndDXmin = iWndDXmin;
   m_iWndDXmax = iWndDXmax;
   m_iWndDYmin = iWndDYmin;
   m_iWndDYmax = iWndDYmax;

// ----------
   m_iWndSoftHorBorderWdt = m_iWndSoftTopBorderWdt = m_iWndSoftBotBorderWdt = iWndSoftBorderWdt;
   m_iWndSoftCaptHgt = iWndSoftCaptHgt;
   m_iWndHardBorderWdt = iWndHardBorderWdt;
   m_iWndHardCaptHgt = iWndHardCaptHgt;

// ----------
   m_hScreen = NULL;

   m_iFact = 1000;

   m_iScrX = m_iScrCurX = iScrX;
   m_iScrY = m_iScrCurY = iScrY;

   m_iScrDX = m_iScrCurDX = iScrDX;
   m_iScrDY = m_iScrCurDY = iScrDY;

// ----------
   m_iResX = 0; // èia paraðèiø netvarkom, tvarkom HTML-e
   m_iResY = 0;

   m_iResDXenl = iResDXenl;
   m_iResDYenl = iResDYenl;

// m_iResDX = m_iScrDX + m_iResDXenl;
// m_iResDY = m_iScrDY + m_iResDYenl;

// -------------
   m_iMouseX = (-1);
   m_iMouseY = (-1);

   m_bLButPressed = False;
   m_bCaptured =
#if IBSH_SKIN == IBSH_SKIN_STANDART
      True;
#else
      False;
#endif
   m_bResizing = False;

   m_bClose = False;
   m_bLogoff = False;

   m_bRefreshing = m_bRefresh = False;

   m_bXGeckoPending = False;

// -------------------- buvæ LzdShSearch laukai
   m_bWrkFl = False;

   m_bKbdInput = False;

#if IBSH_SKIN == IBSH_SKIN_STANDART
   m_TabCtrl=NULL;
   m_hTabImgList=NULL;
#endif

   m_hMainBmp = NULL;
   m_hSearchBmp = NULL;
   m_hHistBmp = NULL;
   m_hMainMaskBmp = NULL;
   m_hSearchMaskBmp = NULL;
   m_hHistMaskBmp = NULL;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// --------------------------------------------------
KpPubDlg::~KpPubDlg()
{
HRESULT retc = S_OK;

// m_hDialogWindow èia jau NULL
// PutLogMessage_("KpPubDlg::~KpPubDlg() %x %x", m_RedrawTimer, m_hDialogWindow);
   if(m_RedrawTimer && m_hDialogWindow) if(!KillTimer(m_hDialogWindow, m_RedrawTimer))
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   m_RedrawTimer = 0;

   KP_DELETE(m_pKpFileSys);

// èia negalima, sunaikina ~KpWnd()
// if(m_hDialogWindow != NULL) ::DestroyWindow(m_hDialogWindow);
// m_hDialogWindow = NULL;
}


// ----------------------------------
HRESULT KpPubDlg::CreateBackground(void)
{
HRESULT retc = S_OK;

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   if(SUCCEEDED(retc))
   {
      if(m_hBackGround != NULL) ::DestroyWindow(m_hBackGround);
      m_hBackGround = NULL;
      if(m_BgrBmpData.m_hBitMap != NULL)
         retc = KpCreateBitmap(m_hInstance, m_hDialogWindow, &m_hBackGround, m_BgrBmpData.m_hBitMap,
//          0, 0, m_iWndCurDX - 2 * m_iWndHardBorderWdt, m_iWndCurDY - m_iWndHardCaptHgt - 2 * m_iWndHardBorderWdt, 0);
            0, 0, m_BgrBmpData.m_iBmpWdt, m_BgrBmpData.m_iBmpHgt, 0L);
#  if (IBSH_SKIN == IBSH_SKIN_START_GRP)
      else
         retc = KpCreateBitmap(m_hInstance, m_hDialogWindow, &m_hBackGround, KP_IDI_BMP_BCKGRND,
            0, 0, m_iWndCurDX, IBSH_WND_SOFT_CAPTION_HGT, 0L);
#  endif
   }
#endif

// --------------------------------------------------- m_ButExit
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// if(SUCCEEDED(retc)) if(m_ButExit != NULL) ::DestroyWindow(m_ButExit); // jau turi bûti sunaikintas prieð iðkvieèiant ir iðvalant m_ButExit

   if(SUCCEEDED(retc)) if(m_ButExit == NULL) // kad pakartotinai nekrautø butono ið statiniø bitmapø – antrà kartà jie nesiselektina á HDC
   {                                         // norint, kad pasikrautø dinaminis buttonas, reikia iðvalyt m_ButExit
      if(m_ButExitBmpData.m_hBitMap != NULL)
      {
         retc = KpCreateButtonLoc(m_hInstance, m_hDialogWindow,
            &m_ButExit, KP_ID_EXIT,
            null,
            m_ButExitBmpData.m_hBitMap,
            (m_ButExitBmpData.m_hHover != NULL)?m_ButExitBmpData.m_hHover:m_ButExitBmpData.m_hBitMap,
            (m_ButExitBmpData.m_hPressed != NULL)?m_ButExitBmpData.m_hPressed:m_ButExitBmpData.m_hBitMap,
            IBSH_BUT_EXIT_X(this), IBSH_BUT_EXIT_Y(this),
            m_ButExitBmpData.m_iBmpWdt, m_ButExitBmpData.m_iBmpHgt, // IBSH_BUT_WDT, IBSH_BUT_WDT,
            KP_WND_UNPROC_BUT, 0, NULL); // KpColorSchemeLocal);
      }
      else
      {
         m_ButExitBmpData.m_iBmpWdt = IBSH_BUT_WDT;
         m_ButExitBmpData.m_iBmpHgt = IBSH_BUT_WDT;

         retc = KpCreateButtonLoc(m_hInstance, m_hDialogWindow,
            &m_ButExit, KP_ID_EXIT,
            IBSH_IDI_EXIT_BITMAP, IBSH_IDI_EXIT_LIGHT_BITMAP, IBSH_IDI_EXIT_SEL_BITMAP,
            IBSH_BUT_EXIT_X(this), IBSH_BUT_EXIT_Y(this),
            IBSH_BUT_WDT, IBSH_BUT_WDT,
            KP_WND_UNPROC_BUT, 0, NULL); // KpColorSchemeLocal);
      }

      KP_ASSERT(m_ButExit, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }
#endif

// --------------------------------------------------- m_ButMinimize
#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// if(SUCCEEDED(retc)) if(m_ButMinimize != NULL) ::DestroyWindow(m_ButMinimize); // jau turi bûti sunaikintas prieð iðkvieèiant ir iðvalant m_ButMinimize

   if(SUCCEEDED(retc)) if(m_ButMinimize == NULL) // kad pakartotinai nekrautø butono ið statiniø bitmapø – antrà kartà jie nesiselektina á HDC
   {                                         // norint, kad pasikrautø dinaminis buttonas, reikia iðvalyt m_ButMinimize
      if(m_ButMinBmpData.m_hBitMap != NULL)
      {
         retc = KpCreateButtonLoc(m_hInstance, m_hDialogWindow,
            &m_ButMinimize, KP_ID_MINIMIZE,
            null,
            m_ButMinBmpData.m_hBitMap,
            (m_ButMinBmpData.m_hHover != NULL)?m_ButMinBmpData.m_hHover:m_ButMinBmpData.m_hBitMap,
            (m_ButMinBmpData.m_hPressed != NULL)?m_ButMinBmpData.m_hPressed:m_ButMinBmpData.m_hBitMap,
            IBSH_BUT_MIN_X(this), IBSH_BUT_MIN_Y(this),
            m_ButMinBmpData.m_iBmpWdt, m_ButMinBmpData.m_iBmpHgt, // IBSH_BUT_WDT, IBSH_BUT_WDT,
            KP_WND_UNPROC_BUT, 0, NULL); // KpColorSchemeLocal);

         KP_ASSERT(m_ButMinimize, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }
   }
#endif

return(retc);
}


// -----------------------------------------
#ifdef Logging
static bool resizing = False;
#endif
BOOL CALLBACK KpPubDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
UINT msg = uMsg;
BOOL retb = False;
bool sizing_area = False;
int ix, iy;
int dx, dy;
int new_x, new_y;
int border_wdt;
WINDOWPOS *winpos_ptr = NULL;
KpPubDlg *dlg_ptr = NULL;
KpWnd *cur_wnd = NULL;
CREATESTRUCT *csp = NULL;

// --------------
   if(SUCCEEDED(retc))
   {
      if(msg == WM_CREATE)
      {
         if(SUCCEEDED(retc)) csp = (LPCREATESTRUCT)lParam;
         KP_ASSERT(csp != NULL, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc)) dlg_ptr = (KpPubDlg *)csp->lpCreateParams;
         KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
      }
      else
      {
         retc = GetCurWindow(&cur_wnd, hwndDlg);
         if(SUCCEEDED(retc)) dlg_ptr = dynamic_cast<KpPubDlg *>(cur_wnd);
      }
   }
// KP_ASSERT(dlg_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
   if((dlg_ptr != NULL) && SUCCEEDED(retc))
   {
//    KP_ASSERT(dlg_ptr->m_iWndType == TYP_KpDialog, KP_E_SYSTEM_ERROR, null, True);
      if(dlg_ptr->m_iWndType != TYP_KpDialog) dlg_ptr = NULL;
   }

   if((dlg_ptr != NULL) && SUCCEEDED(retc))
      KP_ASSERT(dlg_ptr->m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);


#ifdef Logging
if(dlg_ptr != NULL)
{
if(resizing != dlg_ptr->m_bResizing)
PutLogMessage_("KpPubDialogProc: m_bResizing: %d", dlg_ptr->m_bResizing);
resizing = dlg_ptr->m_bResizing;
}
#endif

// --------------
   if((dlg_ptr != NULL) && SUCCEEDED(retc)) switch(msg)
   {

// ---------------------------------------   drag window
   case WM_LBUTTONDOWN:
      if(SUCCEEDED(retc)) dlg_ptr->m_bLButPressed = True;

      if(SUCCEEDED(retc))
      {
         sizing_area=((GET_X_LPARAM(lParam) > dlg_ptr->m_iWndCurDX - KPPUBDLG_RESIZE_WDT_SENS) &&
                     (GET_Y_LPARAM(lParam) > dlg_ptr->m_iWndCurDY - KPPUBDLG_RESIZE_WDT_SENS));

         if(sizing_area)
         {
            if(!::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_SIZENWSE)))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
         }
      }

      break;

   case WM_LBUTTONUP:
      if(SUCCEEDED(retc))
      {
         dlg_ptr->m_bLButPressed = False;

         if(dlg_ptr->m_bCaptured)
         {
            ReleaseCapture();
            dlg_ptr->m_bCaptured = False;
         }
#if IBSH_SKIN != IBSH_SKIN_STANDART
         dlg_ptr->m_bResizing = False;
#endif
#ifdef Logging
PutLogMessage_("KpPubDialogProc: WM_LBUTTONUP m_bResizing: %d m_bCaptured: %d", dlg_ptr->m_bResizing, dlg_ptr->m_bCaptured);
#endif
         dlg_ptr->m_iMouseX = (-1);
         dlg_ptr->m_iMouseY = (-1);
      }
      break;

   case WM_CAPTURECHANGED:
      if(SUCCEEDED(retc))
      {
         dlg_ptr->m_iMouseX = (-1);
         dlg_ptr->m_iMouseY = (-1);
#if IBSH_SKIN != IBSH_SKIN_STANDART
         dlg_ptr->m_bResizing = False;
#else
//       dlg_ptr->m_bCaptured = False;
#endif
#ifdef Logging
PutLogMessage_("KpPubDialogProc: WM_CAPTURECHANGED m_bResizing; %d", dlg_ptr->m_bResizing);
#endif
      }
      break;

   case WM_MOUSEMOVE:
// ----------------- lango stumdymas
      if(SUCCEEDED(retc))
      {
         sizing_area = ((GET_X_LPARAM(lParam) > dlg_ptr->m_iWndCurDX - KPPUBDLG_RESIZE_WDT_SENS) &&
                       (GET_Y_LPARAM(lParam) > dlg_ptr->m_iWndCurDY - KPPUBDLG_RESIZE_WDT_SENS));

         if((wParam & MK_LBUTTON) == 0)
         {
#if IBSH_SKIN != IBSH_SKIN_STANDART
            dlg_ptr->m_bResizing = False;
#endif
            if(sizing_area)
            {
               if(!::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_SIZENWSE)))
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
               }
            }

            if(dlg_ptr->m_bCaptured)
            {
// KP_TRACE("ReleaseCapture");
               ReleaseCapture();
               dlg_ptr->m_bCaptured = False;
            }
         }
         else // if((wParam&MK_LBUTTON)==0)
         {
            ix = GET_X_LPARAM /* LOWORD */(lParam) + dlg_ptr->m_iWndCurX;
            iy = GET_Y_LPARAM /* HIWORD */(lParam) + dlg_ptr->m_iWndCurY;

            dx = ix - dlg_ptr->m_iMouseX;
            dy = iy - dlg_ptr->m_iMouseY;

            if(
//             (abs(dx)<50) && (abs(dy)<50) &&
               ((abs(dx)>0) || (abs(dy)>0)) &&
               (dlg_ptr->m_hDialogWindow != NULL) &&
               (dlg_ptr->m_iMouseX >= 0) && (dlg_ptr->m_iMouseY >= 0)
            )
            {

// pirma karta button down
               if(!dlg_ptr->m_bCaptured)
               {
                  SetCapture(dlg_ptr->m_hDialogWindow);
                  dlg_ptr->m_bCaptured = True;

#if IBSH_SKIN != IBSH_SKIN_STANDART
                  if(sizing_area)
                  {
                     dlg_ptr->m_bResizing = True;

                     if(!::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_SIZENWSE)))
                     {
#ifdef Debug
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                     }
                  }
#endif
               }

               if(SUCCEEDED(retc))
               {
// keiciam matmenis
#if IBSH_SKIN != IBSH_SKIN_STANDART
                  if(dlg_ptr->m_bResizing)
                  {
                     if(
                        ((dx > 0) && (GET_X_LPARAM(lParam) > dlg_ptr->m_iWndCurDX - KPPUBDLG_RESIZE_WDT_SENS)) ||
                        ((dx < 0) && (GET_X_LPARAM(lParam) < dlg_ptr->m_iWndCurDX))
                       )
                        dlg_ptr->m_iWndCurDXprec += dx;

                     if(
                        ((dy>0) && (GET_Y_LPARAM(lParam) > dlg_ptr->m_iWndCurDY - KPPUBDLG_RESIZE_WDT_SENS)) ||
                        ((dy<0) && (GET_Y_LPARAM(lParam) < dlg_ptr->m_iWndCurDY))
                       )
                        dlg_ptr->m_iWndCurDYprec += dy;

                     retc = dlg_ptr->Resize();

#if FALSE // ????
                     if(SUCCEEDED(retc))
                     {
                        dlg_ptr->m_iDoRedraw = 1;
                        retc = dlg_ptr->RedrawWindow();
                     }
#endif
                  }
                  else
#endif
                  {
                     dlg_ptr->m_iWndCurX += dx;
                     dlg_ptr->m_iWndCurY += dy;

                     if(!SetWindowPos(dlg_ptr->m_hDialogWindow, HWND_TOP,
                        dlg_ptr->m_iWndCurX, dlg_ptr->m_iWndCurY,
                        dlg_ptr->m_iWndCurDX, dlg_ptr->m_iWndCurDY, 0))
                     {
#ifdef Debug
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                     }
                  }

               } // if(SUCCEEDED(retc))

            } // if( (abs(dx)<50) && (abs(dy)<50) && ((abs(dx)>0) || (abs(dy)>0)) && ...

            dlg_ptr->m_iMouseX = ix;
            dlg_ptr->m_iMouseY = iy;

         } // else // if((wParam&MK_LBUTTON)==0)

#ifdef Logging
PutLogMessage_("KpPubDialogProc: WM_MOUSEMOVE m_bResizing: %d m_bCaptured: %d", dlg_ptr->m_bResizing, dlg_ptr->m_bCaptured);
#endif
      } // if(SUCCEEDED(retc))

      break;


// ------------------------- po lango pastumdymo
   case WM_MOVE:
      if(SUCCEEDED(retc))
      {
         border_wdt = dlg_ptr->m_iWndHardBorderWdt;

         new_x = LOWORD(lParam);
         if(new_x & 0x8000) new_x = (((-1) & (~0xFFFF)) | new_x);
         dlg_ptr->m_iWndCurX = new_x - border_wdt;

         new_y = HIWORD(lParam);
         if(new_y & 0x8000) new_y = (((-1) & (~0xFFFF)) | new_y);
         dlg_ptr->m_iWndCurY =
            new_y -
            (
               border_wdt +
               dlg_ptr->m_iWndHardCaptHgt
            );
         retb = False;
      }
      break;

   case WM_WINDOWPOSCHANGED:
      if(SUCCEEDED(retc))
      {
#ifdef Logging
PutLogMessage_("KpPubDialogProc: WM_WINDOWPOSCHANGED 1 m_bResizing: %d m_bCaptured: %d", dlg_ptr->m_bResizing, dlg_ptr->m_bCaptured);
#endif

         winpos_ptr = (WINDOWPOS *)lParam;
         if(winpos_ptr)
         {
            if(
               (dlg_ptr->m_iWndCurDXprec != winpos_ptr->cx) ||
               (dlg_ptr->m_iWndCurDYprec != winpos_ptr->cy)
              )
            {
               dlg_ptr->m_iWndCurDXprec = winpos_ptr->cx;
               dlg_ptr->m_iWndCurDYprec = winpos_ptr->cy;

#if IBSH_SKIN == IBSH_SKIN_STANDART
               dlg_ptr->m_bResizing = True; // False; //
#endif
            }
         }

//       retb = DefWindowProc(hwndDlg, msg, wParam, lParam);

         if(!dlg_ptr->m_bLButPressed) // kad nerefreðintø draginimo metu
         {
            retc = dlg_ptr->CompleteDrag();
#if IBSH_SKIN == IBSH_SKIN_STANDART
//          dlg_ptr->m_bResizing = True; // False; //
#endif
         }

#if IBSH_SKIN == IBSH_SKIN_STANDART
         if(!dlg_ptr->m_bCaptured)
            dlg_ptr->m_bResizing = False; // True; //
         dlg_ptr->m_bCaptured = True;
#endif

#ifdef Logging
PutLogMessage_("KpPubDialogProc: WM_WINDOWPOSCHANGED 2 m_bResizing: %d m_bCaptured: %d", dlg_ptr->m_bResizing, dlg_ptr->m_bCaptured);
#endif
      } // if(SUCCEEDED(retc))

      break;

   case WM_EXITSIZEMOVE:
      if(SUCCEEDED(retc)) if(dlg_ptr->m_bResizing)
      {
         retc = dlg_ptr->Resize();
//       dlg_ptr->m_bResizing = False;
         dlg_ptr->m_bCaptured = False;
         dlg_ptr->m_iDoRedraw = 1;
      }
#ifdef Logging
PutLogMessage_("KpPubDialogProc: WM_EXITSIZEMOVE m_bResizing: %d m_bCaptured: %d", dlg_ptr->m_bResizing, dlg_ptr->m_bCaptured);
#endif

      if(SUCCEEDED(retc))
         if(!SetWindowPos(dlg_ptr->m_hDialogWindow, HWND_TOP,
                  dlg_ptr->m_iWndCurX, dlg_ptr->m_iWndCurY,
                  dlg_ptr->m_iWndCurDX, dlg_ptr->m_iWndCurDY,
                  0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }


// IBSH_SKIN IBSH_SKIN_LZDSH_MAHAGON_3D á èia neateina
//    if((dlg_ptr != NULL) && SUCCEEDED(retc)) retc = dlg_ptr->CompleteDrag();

//    retb = DefWindowProc(hwndDlg, msg, wParam, lParam);
      break;

   } // if((dlg_ptr != NULL) && SUCCEEDED(retc)) switch(msg)

return(retb);
}


// ----------------------------------
HRESULT KpPubDlg::CloseWindow(void)
{
HRESULT retc = S_OK;

// PutLogMessage_("KpPubDlg::CloseWindow() %x %x", m_RedrawTimer, m_hDialogWindow);
   if(m_RedrawTimer && m_hDialogWindow) if(!KillTimer(m_hDialogWindow, m_RedrawTimer))
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   m_RedrawTimer = 0;

return(retc);
}


// ----------------------------------
HRESULT KpPubDlg::RestoreSavedCoords(void)
{
HRESULT retc = S_OK;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver = 0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
long ll;
DWORD dwBufLen;
DWORD dwValType;
int win_dx, win_dy;
HKEY hKey = 0;
LONG retw = ERROR_SUCCESS;
HDC hdc = NULL;

// --------------------------
// KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

// -------------------------- restore window coordinates
   if(SUCCEEDED(retc))
   {
      if(theKpStAppPtr != NULL)
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);
      }
      else
      {
         strcpy(publisher, KP_DEF_PUBL_NAME);
         prod_ver = iProdVerGlob;
      }
   }

   if(SUCCEEDED(retc))
   {
      hKey = NULL;

      sprintf((char *)key_name, "Software\\%s\\%d", publisher, prod_ver);
      if(RegOpenKeyEx(HKEY_CURRENT_USER, (LPCTSTR)key_name,
         0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
      {
         dwBufLen = sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndX", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen) == ERROR_SUCCESS)
         {
            KP_ASSERT(dwValType == REG_DWORD, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) m_iWndCurX = ll;
         }

         dwBufLen = sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndY", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen) == ERROR_SUCCESS)
         {
            KP_ASSERT(dwValType == REG_DWORD, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) m_iWndCurY = ll;
         }

         dwBufLen=sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndDX", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen) == ERROR_SUCCESS)
         {
            KP_ASSERT(dwValType == REG_DWORD, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) m_iWndCurDXprec = m_iWndCurDX = ll;
         }

         dwBufLen=sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndDY", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen)==ERROR_SUCCESS)
         {
            KP_ASSERT(dwValType == REG_DWORD, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc)) m_iWndCurDYprec = m_iWndCurDY = ll;
         }

      } // if(RegOpenKeyEx(HKEY_CURRENT_USER, ...

      if(hKey)
      {
         retw = RegCloseKey(hKey);
         KP_ASSERT(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);
         hKey=0;
      }

   } // if(SUCCEEDED(retc))

// --------------
   if(SUCCEEDED(retc))
   {
      hdc=GetDC(HWND_DESKTOP);
#ifdef Debug
      KP_ASSERT(hdc, KP_E_SYSTEM_ERROR, GetLastError(), False);
#endif
   }
   if(hdc && SUCCEEDED(retc))
   {
      win_dx = GetDeviceCaps(hdc, HORZRES);
      win_dy = GetDeviceCaps(hdc, VERTRES);

      if(
         ((m_iWndCurX + m_iWndCurDX) >= win_dx) || ((m_iWndCurY + m_iWndCurDY) >= win_dy) ||
         (m_iWndCurX < 0) || (m_iWndCurY < 0)
        )
      {
         m_iWndCurX = win_dx / 2 - m_iWndCurDX / 2; // IBSH_DEF_WND_X;
         m_iWndCurY = win_dy / 2 - m_iWndCurDY / 2; // IBSH_DEF_WND_Y;
      }

      if(
         ((m_iWndCurX + m_iWndCurDX) >= win_dx) || ((m_iWndCurY + m_iWndCurDY) >= win_dy)
        )
      {
         m_iWndCurDXprec = m_iWndCurDX = IBSH_DEF_WND_DX;
         m_iWndCurDYprec = m_iWndCurDY = IBSH_DEF_WND_DY;
      }
   }

// ----------------------
   if(SUCCEEDED(retc)) retc = Resize();

return(retc);
}


// ------------------------
HRESULT KpPubDlg::SaveCoords(void)
{
HRESULT retc = S_OK;
HKEY hKey = 0;
LONG retw = ERROR_SUCCESS;
DWORD dwDisposition;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver = 0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];

   hKey = NULL;

// KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);

   if(SUCCEEDED(retc))
   {
      if(theKpStAppPtr != NULL)
      {
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);
      }
      else
      {
         strcpy(publisher, KP_DEF_PUBL_NAME);
         prod_ver = iProdVerGlob;
      }
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, "Software\\%s", publisher);

      retw = RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &hKey, &dwDisposition);
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, GetLastError(), False);

      if(hKey != NULL) RegCloseKey(hKey);
      hKey = NULL;
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name, "Software\\%s\\%d", publisher, prod_ver);

      retw = RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &hKey, &dwDisposition);
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, GetLastError(), False);
   }

   if(SUCCEEDED(retc))
   {
      retw = RegSetValueEx(hKey, "WndX", 0, REG_DWORD,
         (BYTE *)&m_iWndCurX, sizeof(m_iWndCurX));
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);
   }
   if(SUCCEEDED(retc))
   {
      retw = RegSetValueEx(hKey, "WndY", 0, REG_DWORD,
         (BYTE *)&m_iWndCurY, sizeof(m_iWndCurY));
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);
   }
   if(SUCCEEDED(retc))
   {
      retw = RegSetValueEx(hKey, "WndDX", 0, REG_DWORD,
         (BYTE *)&m_iWndCurDX, sizeof(m_iWndCurDX));
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);
   }
   if(SUCCEEDED(retc))
   {
      retw = RegSetValueEx(hKey, "WndDY", 0, REG_DWORD,
         (BYTE *)&m_iWndCurDY, sizeof(m_iWndCurDY));
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);
   }

   if(hKey != NULL)
   {
      retw = RegCloseKey(hKey);
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);
      hKey=0;
   }

return(retc);
}


// ----------------------------------
HRESULT KpPubDlg::ShowDialog(void)
{
HRESULT retc=S_OK;

   KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);

   if((m_hDialogWindow != NULL) && SUCCEEDED(retc)) ShowWindow(m_hDialogWindow, SW_SHOW);

return(retc);
}


// ----------------------------------
HRESULT KpPubDlg::HideDialog(void)
{
HRESULT retc=S_OK;

// KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);

   if((m_hDialogWindow != NULL) && SUCCEEDED(retc)) ShowWindow(m_hDialogWindow, SW_HIDE);

return(retc);
}


// --------------------------------------------------
HRESULT KpPubDlg::WaitForXGecko(void)
{
HRESULT retc = S_OK;

   while(m_bXGeckoPending && SUCCEEDED(retc)) retc = KpSleep(200);

return(retc);
}


// --------------------------------------------------
HRESULT KpPubDlg::ExitCapture(void)
{
HRESULT retc = S_OK;

    m_iMouseX = (-1);
    m_iMouseY = (-1);
    m_bResizing = False;

#ifdef Logging
PutLogMessage_("KpPubDlg::ExitCapture m_bResizing; %d", m_bResizing);
#endif

return(retc);
}


// --------------------------------------------------
HRESULT KpPubDlg::GetXmlVersion(XmlVersions *piVersion)
{
HRESULT retc=S_OK;

  if((piVersion == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piVersion = m_iXmlVers;

return(retc);
}


// --------------------------------------------------
HRESULT KpPubDlg::GetEncoding(UC_Modes *piEncMode)
{
HRESULT retc=S_OK;

   if((piEncMode == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piEncMode = m_iEncMode;

return(retc);
}


// ----------------------------------
HRESULT KpPubDlg::DisplayResultCommon(void)
{
HRESULT retc = S_OK;

   KP_ASSERT(m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True)
   KP_ASSERT(m_pKpFileSys->m_pResBuf != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(m_pKpFileSys->m_lpOutFileObj != NULL, KP_E_NO_FILE, null, True);

#ifndef IBSH_RES_MODE_XGECKO // KpGecko atveju turinys bus nuresetintas po paskutinio perskaitymo su XKpGeckoStream::read()
   if(SUCCEEDED(retc)) retc = m_pKpFileSys->m_lpOutFileObj->Reset();
   if(SUCCEEDED(retc)) memset(m_pKpFileSys->m_pResBuf, Nul, KP_FILESYS_RESULT_BUF_LEN * sizeof(m_pKpFileSys->m_pResBuf[0]));
#endif

   if(SUCCEEDED(retc))
   {
      if(m_bResizing)
      {
         m_iDoRedraw = 1;
#if IBSH_SKIN == IBSH_SKIN_STANDART
//       m_bResizing = False;
#endif
      }
#ifdef Logging
PutLogMessage_("KpPubDlg::DisplayResultCommon() m_bResizing: %d", m_bResizing);
#endif
   }

return(retc);
}


// ----------------------------------
HRESULT KpPubDlg::ResizeCommon(void)
{
HRESULT retc = S_OK;

   KP_ASSERT(m_pKpFileSys != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      m_iDoRedraw = 1;
      m_pKpFileSys->m_lCurEntryId = (-1L);
   }

return(retc);
}


// ----------------------------------
HRESULT KpPubDlg::GetOnTop(bool *pbAlwaysOnTop)
{
HRESULT retc = S_OK;

   KP_ASSERT(pbAlwaysOnTop, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) *pbAlwaysOnTop = False;

return(retc);
}


// ----------------------------------
HRESULT XmlNode::TestChildContents(KpChar /* iTestTag */, KpChar *lpiazTestValue, bool *pFoundFlg)
{
HRESULT retc=S_OK;

   KP_ASSERT(pFoundFlg != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      *pFoundFlg = False;
      if(lpiazTestValue == NULL) *pFoundFlg = True;
   }

return(retc);
}


