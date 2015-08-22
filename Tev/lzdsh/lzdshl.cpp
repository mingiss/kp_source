// ---------------------------
// lzdshl.cpp
// zodyno perziuros programa ir XMLT redaktorius
// dialogas
//

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

#ifdef KP_USE_WXWIDGETS
#include "wx/app.h"
#include "wx/frame.h"
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
#include "tvrtf.h"
#include "tvrtfo.h"
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
#ifdef KP_USE_TextGRAB
#include "tgsdkx.h"
#endif
#include "lzdsht.h"
#include "lzdsho.h"
#include "lzdshh.h"


// -----------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef lzdshn_included
#error lzdshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif


// ----------------------------------
#ifdef Debug
int iDictBoxStep = 0;
#endif

// ----------------------------------
int LzdShResDyCor[NumOfWinVersions9] =
{
   3, // WinUnkn,   //  0

   3, // Win20,     //  1

   3, // Win31c,    //  2  // common Windows 3.1x
   3, // Win31,     //  3  // Win32s on Windows 3.1
   3, // Win311,    //  4  // Windows 3.11 for Workgroups (with Win32s ?)

   3, // Win95c,    //  5  // common Windows 95
   3, // Win95,     //  6
   3, // Win95OSR2, //  7

   3, // Win98c,    //  8  // common Windows 98
   3, // Win98,     //  9
   3, // Win98SE,   // 10  // Windows 98 Second Edition
   3, // WinCE,     // 11
   3, // WinMe,     // 12

   4, // WinNT,     // 13  // common Windows NT

   4, // WinNT35c,  // 14  // common Windows NT 3.5x
   4, // WinNT351,  // 15

   4, // WinNT40c,  // 16  // common Windows 4.0
   4, // WinNT40,   // 17  // Windows NT 4.0 Workstation
   4, // WinNT40s,  // 18  // Windows NT 4.0 server

   4, // Win2000c,  // 19  // common Windows 2000
   4, // Win2000,   // 20  // Windows 2000 Professional // Windows 2000
   4, // Win2000s,  // 21  // Windows 2000 Server  // atsirado nuo 2004.10.01

   4, // WinXPc,    // 22  // common Windows XP

   4, // WinXP,     // 23  // Windows XP           // 20 before 2004.10.01
   4, // Win2003s,  // 24  // Windows Server 2003  // 21 before 2004.10.01
   4, // WinXpStart,// 25  // Windows XP Starter Edition
   4, // WinXpHome, // 26  // Windows XP Home Edition
   4, // WinXpPro,  // 27  // Windows XP Professional
   4, // WinXpMedia,// 28  // Windows XP Media Center Edition
   4, // WinXpTablet,// 29 // Windows XP Tablet PC Edition // Windows CE analogas?
   4, // WinXP64,   // 30  // Windows XP Professional x64 Edition
   4, // Win2003sR2,// 31  // Windows Server 2003 R2

   4, // WinVistaC, // 32  // common Windows Vista

   4, // WinVista,  // 33  // Windows Vista
   4, // WinVistaH, // 34  // Windows Vista Home Basic
   4, // WinVistaHP,// 35  // Windows Vista Home Premium
   4, // WinVistaB, // 36  // Windows Vista Business
   4, // WinVistaE, // 37  // Windows Vista Enterprise
   4, // WinVistaU, // 38  // Windows Vista Ultimate
   4, // Win2008s,  // 39  // Windows Server 2008 // Windows Server Longhorn

   4, // Win7,      // 40  // Windows 7
   4, // Win8,      // 41  // Windows 8

   4, // WinNtFuture,// 42 // common Windows NT based future versions
};


// ----------------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
COLORREF KpColorSchemeToolTip[KpNumOfShadows3]={
RGB_Lightyellow, // RGB(191,191,191), // RGB(236,233,216), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Darkblue, // RGB_Navy,
};
#else
COLORREF KpColorSchemeLocal[KpNumOfShadows3]={ // KpColorScheme[KpNumOfShadows2]={
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON
RGB(207,183,160), // RGB(172,153,133), // RGB(175,171,157), // RGB(252,246,225), // RGB_Lightyellow
RGB_White, // RGB(248,220,192), // RGB(210,205,188), // RGB_White
RGB(117,114,105), // RGB(218,109,0), // RGB(182,91,0), // RGB(127,63,0), // RGB_Brown
RGB_Black,
RGB(207,183,160), // RGB_Lightyellow
RGB(117,114,105), // RGB_Brown
RGB(124,0,0),
RGB_Darkblue, // RGB_Navy,
#  else
RGB(251,249,241), // RGB(255,247,239), // RGB(208,199,178), // RGB(249,239,214), // RGB_Lightyellow,
RGB_White, // RGB(255,244,218)
RGB(99,6,0), // RGB(132,6,0), // RGB_Brown,
RGB_Black,
RGB(250,244,234), // RGB(249,239,214), // RGB_Lightyellow,
RGB_White,
RGB(190,130,79),
RGB_Darkblue, // RGB_Navy,
#  endif
};
#endif

#ifdef KP_USE_WXWIDGETS
// ----------------------------------
BEGIN_EVENT_TABLE(LzdShFrame_tag, wxFrame)
   EVT_MENU(wxID_EXIT, LzdShFrame_tag::OnExit)
   EVT_MENU(wxID_OPEN, LzdShFrame_tag::LzdShDialogProc)

   EVT_MENU(wxID_UP, LzdShFrame_tag::LzdShDialogProc)
   EVT_MENU(wxID_DOWN, LzdShFrame_tag::LzdShDialogProc)
   EVT_MENU(wxID_HOME, LzdShFrame_tag::LzdShDialogProc)
   EVT_MENU(wxID_MOVE_FRAME, LzdShFrame_tag::LzdShDialogProc)
   EVT_MENU(wxID_RESIZE_FRAME, LzdShFrame_tag::LzdShDialogProc)
END_EVENT_TABLE()
#endif


// ----------------------------------
LzdShDlg::LzdShDlg(KpFileSys *pKpFileSys)
#if TRUE // FALSE
#  ifdef IBSH_RES_MODE_XGECKO
#     if CompilerGr == Mingw
: KpGeckoDialog(
#     else
: KpPubDlg(
#     endif
#  else
#     ifdef IBSH_RES_MODE_MSHTML
: KpMsHtmlDlg(
#     else
#        ifdef IBSH_RES_MODE_RTF
: KpRtfDlg(
#        else
: KpPubDlg(
#        endif
#     endif
#  endif
#else
: iBshDlg(
#endif
   pKpFileSys,
   (XmlVersions)LZDSH_OUT_VERS,
#ifdef LZDSH_RES_CODING_UTF8
   UC_UTF_8,
#else
   UC_UTF_16,
#endif
   IBSH_WND_CAPTION,
   LZDSH_WND_DX_MIN, LZDSH_WND_DX_MAX, LZDSH_WND_DY_MIN, LZDSH_WND_DY_MAX,
   LZDSH_CTRL_MARGIN, LZDSH_WND_SOFT_CAPTION_HGT,
   IBSH_WND_BORDER_WDT, IBSH_WND_CAPTION_HGT,
   LZDSH_RES_X, LZDSH_RES_Y, LZDSH_RES_DX, LZDSH_RES_DY, 0, 0,
   LZDSH_WND_STYLE, LZDSH_WND_X, LZDSH_WND_Y, LZDSH_WND_DX, LZDSH_WND_DY)
{
HRESULT retc = m_lhOpenResult;
HRESULT retc0 = S_OK;
// int ii;

// KpMsgOut_0("LzdShDlg::LzdShDlg()");

   m_hInstance=NULL;

// m_hDialogWindow=NULL;

   m_iWndCurX = LZDSH_WND_X;
   m_iWndCurY = LZDSH_WND_Y;
   m_iWndCurDXprec = m_iWndCurDX = LZDSH_WND_DX;
   m_iWndCurDYprec = m_iWndCurDY = LZDSH_WND_DY;

   m_InpEdit = NULL;

   m_MainList = NULL;
   m_SearchList = NULL;
   m_HistList = NULL;
   m_CurList = NULL;

#ifdef LZDSH_EDITOR_BUILD
#ifdef KP_USE_WXWIDGETS
   m_pNodList = NULL;
#else
   m_NodList = NULL;
#endif

   m_TagList = NULL;
   m_TagEditCtrl = NULL;
   m_bTagEditChanged = False;
   m_iCurEditSel = -1;

// strncpy(m_TagEditFontName, "Times New Roman", LF_FACESIZE);
// m_TagEditFontName[LF_FACESIZE] = Nul;

   m_TagEditFontFmt.cbSize = sizeof(m_TagEditFontFmt);
   m_TagEditFontFmt.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_COLOR | // CFM_STRIKEOUT |
      CFM_FACE | CFM_SIZE | CFM_OFFSET; // CFM_CHARSET |
   m_TagEditFontFmt.dwEffects = 0;
   m_TagEditFontFmt.yHeight = 10*20;
   m_TagEditFontFmt.yOffset = 0;
   m_TagEditFontFmt.crTextColor = RGB_Black;
// m_TagEditFontFmt.bCharSet = BALTIC_CHARSET;
   m_TagEditFontFmt.bPitchAndFamily = DEFAULT_PITCH;

// strcpy(m_TagEditFontFmt.szFaceName, m_TagEditFontName);
/* retc = */ KptStrToUnicode(m_TagEditFontFmt.szFaceName, (const unsigned char *)"Times New Roman" /* m_TagEditFontName */, 1);
   m_TagEditFontFmt.szFaceName[LF_FACESIZE] = 0; // Nul;
#endif

   m_iNumOfLines = LZDSH_LIST_NUM_LINES;

// -----------------------------
// iðkeltas á KpPubDlg
#if FALSE
#ifdef IBSH_RES_MODE_RTF
   m_ResRichEdit = NULL;
#  ifdef LZDSH_EDITOR_BUILD
#     ifdef Debug
// m_ResRichTest = NULL;
#     endif
#  endif
#endif
#endif

#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   m_ResHtml=NULL;
#  endif
#endif

// m_MenuButFile = NULL;
   m_MenuButOpt = NULL;
   m_MenuButHelp = NULL;

#ifdef IBSH_RES_MODE_XGECKO
   m_ButBack = NULL;
   m_ButForward = NULL;
#endif

   m_ButSearch = NULL;
   m_ButFontZoom = NULL;
   m_ButNarrow = NULL;
   m_ButAcc = NULL;

#if IBSH_SKIN != IBSH_SKIN_STANDART
   m_ButMinimize = NULL;
   m_ButExit = NULL;
#endif

   m_DictBox = NULL;

#ifdef LZDSHT_SEARCH_SINGLE_THREAD
   m_bButSearchPressed=False;
#endif

   m_Menu=NULL;

// m_DictMenu=NULL;

#if IBSH_SKIN == IBSH_SKIN_STANDART
   m_TabCtrl=NULL;
   m_hTabImgList=NULL;
#endif
   m_TabMain = NULL;
   m_TabSearch = NULL;
   m_TabHist = NULL;

// #if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// // nereikia – konstruktorius sutvarko
//    m_BgrBmpData.m_hBitMap = NULL; // m_hBckGrndBmp = NULL;
// // m_BgrBmpData.m_hBitmapCtrl = NULL; // m_hBckGrnd = NULL;
//    m_BgrBmpData.m_hdcBmpHdc = NULL; // m_hdcBckGrnd = NULL;
// #endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// nereikia – konstruktorius sutvarko
// m_LogoBmpData.m_hBitMap = NULL; // m_hLogoBmp = NULL;
// m_LogoBmpData.m_hdcBmpHdc = NULL; // m_hdcLogo = NULL;
#endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) // ||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   m_hFMenuBmp = NULL;
   m_hdcFMenu = NULL;
#endif

#if FALSE
   for(ii=0; (ii < KpNumOfShadows0) ; ii++)
   {
#  if IBSH_SKIN != IBSH_SKIN_STANDART
      m_aPenScheme[ii]=CreatePen(PS_SOLID, 1, KpColorSchemeLocal[ii]);
      if(m_aPenScheme[ii]==NULL)
      {
         retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
#  endif

      m_aPenSchemeToolTip[ii]=CreatePen(PS_SOLID, 1,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
         KpColorSchemeToolTip[ii]);
#  else
         KpColorSchemeLocal[ii]);
#  endif
      if(m_aPenSchemeToolTip[ii]==NULL)
      {
      /* retc0 = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = retc0;
      }
   }
#endif

   m_hMainBmp = NULL;
   m_hSearchBmp = NULL;
   m_hHistBmp = NULL;
   m_hMainMaskBmp = NULL;
   m_hSearchMaskBmp = NULL;
   m_hHistMaskBmp = NULL;

   m_hCurSav = NULL;

   m_iNumOfListEntries = 0;
   m_iNumOfHistEntries = 0;

#ifdef LZDSHT_DIFF_KWDS
#ifdef LZDSHT_FULL_LIST
   m_lpszaListKeywords=NULL;
#else
   for(ii=0; ii<LZDSH_LIST_NUM_LINES; ii++)
   {
      m_lpszaListKeywords[ii][0]=Nul;
//    m_lpszaListTexts[ii][0]=Nul;
   }
#endif
#endif

   m_iCtrlCtbl = TV_IX_CTBL;

   m_bShiftFl = False;

   m_bLButPressed = False;
   m_iMouseX = (-1);
   m_iMouseY = (-1);
   m_bCaptured = False;
   m_bResizing = False;
// m_bDoRedraw = False;
// m_RedrawTimer = 0;

   m_DictList = NULL;
   m_iNumOfDictEntries = 0;
   m_iCurDictEntry = 0;

   m_lpszCurDictName[0] = Nul;
#ifdef IBSH_RES_MODE_XGECKO
   m_lpszSelDictName[0] = Nul;
#endif

   m_bDiagOnTop = False;
   m_iDiagOnTopCnt = 9999; // kad LzdShSearch::DisplayResult() paþintø pirmà kartà // (-1); // 0;

// -------------------- buvæ LzdShSearch laukai
   m_bWrkFl = False;

   m_bKbdInput = False;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


// ----------------------------------
LzdShDlg::~LzdShDlg()
{
HRESULT retc = S_OK;
// int ii;

// PutLogMessage_("---------------- LzdShDlg::~LzdShDlg()");

// ----------------------------------
// iðmetam susijusá KpWnd, kad lango praneðimø callbackas neberastø
// nes lûþta ant XP po iðëjimo ið programos
// KpWnd *cur_wnd = NULL;
// HRESULT retc0 = S_OK;
// retc0 = GetCurWindow(&cur_wnd, m_hDialogWindow);
// if((cur_wnd != NULL) && SUCCEEDED(retc0)) DeleteWnd(cur_wnd);

// nepadeda – trinam visà sàraðà
   KpWndListObj.DeleteList();

// ----------------------------------
#ifdef LZDSH_EDITOR_BUILD
   if(m_TagEditCtrl != NULL)
   {
// TODO !!!! issaugoti m_TagEditCtrl->m_hMDI_Client redaguota teksta
// !!!! lango jau nebera, issaugoti kazkur anksciau. O gal ir nereikia?

KpWnd *tag_edit;
      tag_edit = m_TagEditCtrl;
      m_TagEditCtrl = NULL;
      m_iCurEditSel = -1;

//    if(!DestroyWindow(tag_edit))
//       /* retc= */KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      KP_DELETE(tag_edit);
   }
#endif

#ifdef LZDSHT_DIFF_KWDS
   KP_DELETEA(m_lpszaListKeywords);
#endif

// -----------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
   if(m_hTabImgList!=NULL)
      if(!ImageList_Destroy(m_hTabImgList))
      {
#ifdef Debug
         /* retc= */KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hTabImgList=NULL;
#endif

// -----------------------
// // #if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// nereikia – sutvarko destruktorius
// if(m_BgrBmpData.m_hBitMap /* m_hBckGrndBmp */ != NULL)
//    if(!DeleteObject(m_BgrBmpData.m_hBitMap /* m_hBckGrndBmp */))
//    {
// #ifdef Debug
//    /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// #endif
//    }
// m_BgrBmpData.m_hBitMap /* m_hBckGrndBmp */ = NULL;

// nereikia – sutvarko destruktorius
// if(m_BgrBmpData.m_hdcBmpHdc /* m_hdcBckGrnd */ != NULL)
//    if(!DeleteDC(m_BgrBmpData.m_hdcBmpHdc /* m_hdcBckGrnd))
//    {
// #ifdef Debug
//    /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// #endif
//    }
// m_BgrBmpData.m_hdcBmpHdc = NULL; // m_hdcBckGrnd = NULL;
// // #endif

// #if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// nereikia – sutvarko destruktorius
// if(m_LogoBmpData.m_hBitMap /* m_hLogoBmp */ != NULL)
//    if(!DeleteObject(m_LogoBmpData.m_hBitMap /* m_hLogoBmp */))
//    {
// #ifdef Debug
//    /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// #endif
//    }
// m_LogoBmpData.m_hBitMap = NULL; // m_hLogoBmp = NULL;

// nereikia – sutvarko destruktorius
// if(m_LogoBmpData.m_hdcBmpHdc /* m_hdcLogo */ !=NULL)
//    if(!DeleteDC(m_LogoBmpData.m_hdcBmpHdc /* m_hdcLogo */))
//    {
// #ifdef Debug
//    /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// #endif
//    }
// m_LogoBmpData.m_hdcBmpHdc = NULL; // m_hdcLogo = NULL;
// #endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) // ||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   if(m_hFMenuBmp!=NULL)
      if(!DeleteObject(m_hFMenuBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hFMenuBmp=NULL;

   if(m_hdcFMenu!=NULL)
      if(!DeleteDC(m_hdcFMenu))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hdcFMenu=NULL;
#endif


#if FALSE
#  if IBSH_SKIN != IBSH_SKIN_STANDART
   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
      if(m_aPenScheme[ii]!=NULL)
         if(!DeleteObject(m_aPenScheme[ii]))
         {
#     ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
         }
      m_aPenScheme[ii]=NULL;
   }
#  endif

   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
      if(m_aPenSchemeToolTip[ii]!=NULL)
         if(!DeleteObject(m_aPenSchemeToolTip[ii]))
         {
#  ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
         }
      m_aPenSchemeToolTip[ii]=NULL;
   }
#endif

// -----------------------
   if(m_hMainBmp!=NULL)
      if(!DeleteObject(m_hMainBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hMainBmp=NULL;

   if(m_hSearchBmp!=NULL)
      if(!DeleteObject(m_hSearchBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hSearchBmp=NULL;

   if(m_hHistBmp!=NULL)
      if(!DeleteObject(m_hHistBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hHistBmp=NULL;

   if(m_hMainMaskBmp!=NULL)
      if(!DeleteObject(m_hMainMaskBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hMainMaskBmp=NULL;

   if(m_hSearchMaskBmp!=NULL)
      if(!DeleteObject(m_hSearchMaskBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hSearchMaskBmp=NULL;

   if(m_hHistMaskBmp!=NULL)
      if(!DeleteObject(m_hHistMaskBmp))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hHistMaskBmp=NULL;


// ----------------------
// #if IBSH_SKIN != IBSH_SKIN_STANDART
#  if FALSE // iðkeltas á m_hDialogWindow
   if(m_RedrawTimer && m_hDialogWindow) if(!KillTimer
                        (
#     ifdef KP_USE_WXWIDGETS
                              (HWND)m_hDialogWindow->GetHWND(),
#     else
                              m_hDialogWindow,
#     endif
                           m_RedrawTimer)
                        )
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   m_RedrawTimer=0;
#  endif
// #endif

// ----------------------
KpTreeEntry *dict_list;
   dict_list = m_DictList;
   m_DictList = NULL;
   KP_DELETE(dict_list);

#ifdef KP_USE_WXWIDGETS
HWND frame;
   frame = m_hDialogWindow;
   m_hDialogWindow = NULL;
   KP_DELETE(frame);
#endif

#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   KP_DELETE(m_ResHtml);
#  endif
#endif

}


// ----------------------------------
HRESULT LzdShDlg::InitDisplay(void)
{
HRESULT retc=S_OK;

#ifdef IBSH_RES_MODE_MSHTML
#if Compiler != Watcom
   HTMLWindow::InitOle();
#endif

#if FALSE
   HTMLWindow *html_window = NULL;
      KP_NEW(html_window, HTMLWindow(
         "<html><head>"
         "<title>MSHTMLTest</title>"   // seems a little useless in this context
         "</head><body>"
         "<h1>This is a test</h1>"
         "I offer the following links:"
         "<ul>"
         "<li><a href='http://www.google.com'>www.google.com</a>"
         "<li><a href='http://www.adp-gmbh.ch'>www.adp-gmbh.ch</a>"
         "<li><a href='http://www.yahoo.com'>www.yahoo.com</a>"
         "</ul>"
         "</body></html>",
         "MSHTMLTest", hInstance,
         false  // not an url
      ));
#endif
#endif

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::FinitDisplay(void)
{
HRESULT retc=S_OK;

#ifdef IBSH_RES_MODE_MSHTML
#if Compiler != Watcom
   HTMLWindow::CloseOle();
#endif
#endif

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::InitThreadDisplay(void)
{
HRESULT retc = S_OK;
LzdShDlg *lzdsh_dlg = this;

// KpMsgOutF_1("InitThreadDisplay(): %d", GetCurrentThreadId());

#ifdef IBSH_RES_MODE_XGECKO
#if Compiler != Watcom
   if(SUCCEEDED(retc)) retc = InitGecko();

#ifdef LZDSHT_DISPLAY_SEARCH_THREAD
   if(SUCCEEDED(retc)) while(m_hDialogWindow == NULL) Sleep(100);

   if(SUCCEEDED(retc)) CreateResCtrl(LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE, LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE, m_hDialogWindow);
#endif

#endif
#endif

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::FinitThreadDisplay(void)
{
HRESULT retc=S_OK;

// KpMsgOutF_1("FinitThreadDisplay(): %d", GetCurrentThreadId());

#ifdef IBSH_RES_MODE_XGECKO
#if Compiler != Watcom
   if(SUCCEEDED(retc)) FinitGecko();
#endif
#endif

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::OpenWindow(HINSTANCE hInst, bool /* bShowWindow */)
{
HRESULT retc=S_OK;
#ifndef KP_USE_WXWIDGETS
WNDCLASSEX wcx;
#endif
HCURSOR cur_sav=NULL;
HBRUSH brush;
// #if IBSH_SKIN != IBSH_SKIN_STANDART
// HPEN pen = NULL;
// EXTLOGPEN log_pen;
// #endif
// int ii, jj;
bool on_top = False;

   if(hInst==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) m_hInstance=hInst;

// -----------------------------
   if(SUCCEEDED(retc)) retc = GetOnTop(&on_top);

//-----------------
#if FALSE
   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
#  if IBSH_SKIN != IBSH_SKIN_STANDART
      jj = KpColorSchemeLocal[ii];

      m_aPenScheme[ii] = CreatePen(PS_SOLID, 1, jj);
      if(m_aPenScheme[ii]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif

#  if IBSH_SKIN == IBSH_SKIN_STANDART
      jj=KpColorSchemeToolTip[ii];
#  else
      jj=KpColorSchemeLocal[ii]; // jj=KpColorSchemeWin[ii]; // jj=KpColorScheme[ii]
#  endif
      m_aPenSchemeToolTip[ii]=CreatePen(PS_SOLID, 1, jj);
      if(m_aPenSchemeToolTip[ii]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }
#endif

//-----------------
   if(SUCCEEDED(retc))
   {
      cur_sav=::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
      if(cur_sav==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// --------------------------
#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1,
#  if IBSH_SKIN == IBSH_SKIN_STANDART
         GetSysColor(iaColorMap[KpShadowNorm]));
#  else
         KpColorSchemeLocal[KpShadowNorm]);
#  endif
      if(!pen)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      if(pen)
      {
         if(GetObject(pen, sizeof(log_pen), &log_pen))
            brush=CreateSolidBrush(log_pen.elpColor);
         else
         {
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            brush = (HBRUSH)iaColorMap[KpShadowNorm];
         }
      }
      else
         brush = (HBRUSH)iaColorMap[KpShadowNorm];
   }

   if(pen) if(!DeleteObject(pen))
      /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen = NULL;

#else // #if FALSE

   brush=CreateSolidBrush(
#  if IBSH_SKIN == IBSH_SKIN_STANDART
            GetSysColor(iaColorMap[KpShadowNorm]));
#  else
            KpColorSchemeLocal[KpShadowNorm]);
#  endif

#endif // #else // #if FALSE

// ------------------------
   if(SUCCEEDED(retc)) retc = RestoreSavedCoords();

// --------------------------------- "LZDSH" class
#ifndef KP_USE_WXWIDGETS
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = m_hInstance;
      wcx.lpszClassName = "LZDSH",
      wcx.lpfnWndProc   = (WNDPROC)LzdShDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(m_hInstance, MAKEINTRESOURCE(LZDSH_IDI_LED_ICON)); // LoadIcon(m_hInstance, MAKEINTRESOURCE(LZDSH_IDI_SEARCH_ICON)); //
      wcx.hIconSm       = LoadIcon(m_hInstance, MAKEINTRESOURCE(LZDSH_IDI_LED_ICON)); // LoadIcon(m_hInstance, MAKEINTRESOURCE(LZDSH_IDI_SEARCH_ICON)); //
      wcx.hCursor       = LoadCursor(0, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush;

      if(!RegisterClassEx(&wcx))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#endif

#ifdef LZDSH_MENU
#if IBSH_SKIN == IBSH_SKIN_STANDART
#if FALSE
// ------------------------------- m_DictMenu
   if(SUCCEEDED(retc))
   {
      m_DictMenu=CreateMenu();
      if(m_DictMenu==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      if(!AppendMenu(m_DictMenu, MF_STRING, KP_ID_OPEN_CMD, (const char *)LZDSH_MSG_OPEN))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      if(!AppendMenu(m_DictMenu, MF_SEPARATOR, 0, NULL))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      if(!AppendMenu(m_DictMenu, MF_STRING, KP_ID_EXIT, (const char *)LZDSH_MSG_EXIT))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#endif

// ------------------------------- m_Menu
   if(SUCCEEDED(retc))
   {
      m_Menu=CreateMenu();
      if(m_Menu==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
// if(SUCCEEDED(retc))
// {
//    if(!AppendMenu(m_Menu, MF_POPUP|MF_STRING, (UINT_PTR)m_DictMenu, (const char *)LZDSH_MSG_DICT))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// }
   if(SUCCEEDED(retc))
   {
      if(!AppendMenu(m_Menu, MF_STRING, KP_ID_OPTIONS, (const char *)LZDSH_MSG_OPT))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      if(!AppendMenu(m_Menu, MF_STRING, KP_ID_HELP, (const char *)LZDSH_MSG_HELP))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#endif
#endif

// ----------------------------- m_hDialogWindow
#ifdef KP_USE_WXWIDGETS
wxPoint *pos = NULL;
   KP_NEW(pos, wxPoint(m_iWndCurX, m_iWndCurY));
wxSize *size = NULL;
   KP_NEW(size, wxSize(m_iWndCurDX, m_iWndCurDY));
   KP_NEW(m_hDialogWindow, LzdShFrame_tag(NULL, LZDE_ID_DIALOG, "Lizdynas", *pos, *size, wxDEFAULT_FRAME_STYLE, "LizdynasDlg"));
KP_DELETE(pos);
KP_DELETE(size);
   if((m_hDialogWindow == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) m_hDialogWindow->Show();

#else // #ifdef KP_USE_WXWIDGETS

   if(SUCCEEDED(retc)) retc = Resize();

   if(SUCCEEDED(retc))
   {
      m_hDialogWindow = CreateWindowEx
      (
#  if IBSH_SKIN == IBSH_SKIN_STANDART
         0,                      // DWORD dwExStyle,      // extended window style
#  else
         WS_EX_APPWINDOW, // WS_EX_TRANSPARENT,
#  endif
         "LZDSH",
#  ifndef LZDSH_DELT
         (const char *)IBSH_WND_CAPTION, // "WinLED", // "LzdSh", // LPCTSTR lpWindowName, // pointer to window name
#  else
         "DeLt",
#  endif
         LZDSH_WND_STYLE, // DWORD dwStyle,        // window style
         m_iWndCurX, // LZDSH_WND_X, // CW_USEDEFAULT, // int x,               // horizontal position of window
         m_iWndCurY, // LZDSH_WND_Y, // CW_USEDEFAULT, // int y,               // vertical position of window
         m_iWndCurDX, // LZDSH_WND_DX, // int nWidth,           // window width
         m_iWndCurDY, // LZDSH_WND_DY, // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         m_Menu,       // HMENU hMenu,          // handle to menu, or child-window identifier
         m_hInstance,
         this // NULL                    // LPVOID lpParam        // pointer to window-creation data
      );

      KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }
#endif

// ----------------------------------
   if(SUCCEEDED(retc))
   {
      m_hWndHandle = m_hDialogWindow;
      retc = WndPreg(this, TYP_KpDialog, hKpInstance, NULL, False);
   }

#ifdef Debug
// unsigned char str_buf[100];
// sprintf((char *)str_buf, "main: %x", m_hDialogWindow);
// KP_TRACE(str_buf);
#endif

#if FALSE
   if(SUCCEEDED(retc)) retc = KpSleep
                        (
                           1000, // 500,
#  ifdef KP_USE_WXWIDGETS
                              (HWND)m_hDialogWindow->GetHWND()
#  else
                              m_hDialogWindow
#  endif
                        );
#endif

// if(SUCCEEDED(retc)) SetCapture(m_hDialogWindow);

// if(on_top && SUCCEEDED(retc)) retc = BringToTop(on_top); // èia dar per anksti, iðkelta á LzdShDialogProc() WM_TIMER m_RedrawTimer

// -----------------------------
// #if IBSH_SKIN != IBSH_SKIN_STANDART
   if(SUCCEEDED(retc))
   {
      m_RedrawTimer = SetTimer
      (
#ifdef KP_USE_WXWIDGETS
            (HWND)m_hDialogWindow->GetHWND(),
#else
            m_hDialogWindow,
#endif
         KP_REDRAW_TIMER, KP_REDRAW_TIMEOUT, NULL
      );
      if(!m_RedrawTimer)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
// #endif

//-------------
   if(cur_sav!=NULL) ::SetCursor(cur_sav);
   cur_sav=NULL;

return(retc);
}


#if FALSE
// ----------------------
HRESULT KpCreateLzdshListBox(HINSTANCE /* hInst */, HWND hParent, HWND *phListControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, ControlStyles iCtrlStyle, DWORD dwExStyle, DWORD dwStyle, RecListEntry * /* pEntryes */, int iInitSel)
{
HRESULT retc=S_OK;
HWND list_field=NULL;

   if(((iCtrlStyle<0) || (iCtrlStyle>=KPW_NUM_OF_CONTROL_STYLES)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// ------------------------
   if(SUCCEEDED(retc))
   {
      list_field=CreateWindowEx(dwExStyle|WS_EX_TRANSPARENT/*|WS_EX_CLIENTEDGE|ES_SUNKEN*/,
                  "LISTBOX",
                  (LPCTSTR)lpszText,
//                (dwStyle|WS_CHILD|WS_VISIBLE|DS_SETFONT|LBS_HASSTRINGS|LBS_DISABLENOSCROLL|LBS_NOTIFY|WS_VSCROLL|DS_SETFONT)&(~LBS_SORT), // |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  dwStyle|LBS_OWNERDRAWFIXED|WS_CHILD|WS_VISIBLE|DS_SETFONT|LBS_DISABLENOSCROLL|LBS_NOTIFY|WS_VSCROLL|DS_SETFONT|LBS_SORT,
                  iPosX+1, iPosY+1, iWdt-2, iHgt-2,
                  hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!list_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) retc=SetCtrlFont(list_field, iCtrlStyle);

   if((phListControl!=NULL) && SUCCEEDED(retc)) *phListControl=list_field;

   if(SUCCEEDED(retc)) retc=SetListBoxSel(list_field, iInitSel);

return(retc);
}
#endif


#ifdef KP_USE_WXWIDGETS
// ----------------------------------
void LzdShFrame_tag::OnExit(wxCommandEvent& /* event */)
{
#ifdef Debug
KpMsgOut("OnExit", IDI_ASTERISK, KP_MB_TESTI);
#endif

   Close();
}
#endif


// -----------------------------------------
#ifdef KP_USE_WXWIDGETS
void LzdShFrame_tag::LzdShDialogProc(wxCommandEvent& event)
{
// LzdShFrame_tag* /* LzdShDlg* */ /* wxFrame* */ /* wxObject* */ window = NULL;
WPARAM wParam = 0; // TODO nuimt zagluske !!!!
LPARAM lParam = 0L; // TODO nuimt zagluske !!!!
#else
BOOL CALLBACK LzdShDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
// HWND window = 0;
#endif
HWND ms_window = 0;
HRESULT retc = S_OK;
BOOL retb = FALSE;
UINT msg = 0;
int retp = 0;
bool endfl=False;
int ii;
HWND parent_window = 0;
HDC hdc = NULL;
PAINTSTRUCT ps;
#if IBSH_SKIN == IBSH_SKIN_STANDART
HICON icon=NULL;
TCITEM tie;
#endif
HWND list_ctrl=NULL;
LRESULT /* int */ retv;
#ifdef KP_LISTBOX
HWND sub_list_ctrl=NULL;
KpWnd *cur_wnd=NULL;
#endif
// int ix, iy, dx, dy;
#if IBSH_SKIN == IBSH_SKIN_STANDART
// int new_wdt, new_hgt;
#endif
// char str_buf[100];
// HWND prew_mouse_over=NULL;
#if IBSH_SKIN == IBSH_SKIN_STANDART
// short bgrcols[3]={ 255, 0, 0};
WINDOWPOS *winpos_ptr=NULL;
#endif
// bool sizing_area=False;
// int new_x, new_y;
#if IBSH_SKIN != IBSH_SKIN_LZDSH_MAHAGON_3D
HPEN pen_light = NULL;
HPEN pen_dark = NULL;
HPEN pen_norm = NULL;
HPEN pen_black = NULL;
#endif
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
HKEY hKey = NULL;
DWORD dwBufLen;
DWORD dwValType;
LONG retw = ERROR_SUCCESS;
long ll;
unsigned char dict[KP_MAX_FNAME_LEN+1];
int found;

   LZDSH_DLG_PTR_INIT;

#ifdef KP_USE_WXWIDGETS
// if((this /* m_hDialogWindow */ == NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) if(&event == NULL)
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
// if(SUCCEEDED(retc))
// {
//    window = this; // event.GetEventObject();
//    if(window == NULL)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
// }

   if(SUCCEEDED(retc))
   {
      ms_window = (HWND)/* window-> */ GetHWND();
      if(ms_window == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }

#if FALSE // #ifdef Debug
KP_TRACE("----");
char str_buf[100];
sprintf(str_buf, "}}}} %d", event.GetId());
KP_TRACE(str_buf);
#endif

   if(SUCCEEDED(retc)) switch(event.GetId())
   {
   case wxID_OPEN:
      msg = WM_CREATE;
      break;
// TODO !!!! kiti pranesimai
   }
#else
   if(SUCCEEDED(retc))
   {
//    window = hwndDlg;
      ms_window = hwndDlg;
//    if(ms_window == NULL)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   msg = uMsg;
#endif

   retp = LOWORD(wParam);
   endfl=False;

//-------------------------------
#if FALSE // #ifdef Debug
if(msg != WM_CREATE)
{
   retb = DefWindowProc(ms_window, msg, wParam, lParam);
   return(retb);
}
#endif

// ------------------------------------
   if(SUCCEEDED(retc)) switch(msg)
   {
   case WM_CREATE:

#ifdef Debug
// unsigned char str_buf[100];
// sprintf((char *)str_buf, "parent: %x", window);
// KP_TRACE(str_buf);
#endif

      if((hKpInstance==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      parent_window = ms_window;

// ------------------------------- background
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_BgrBmpData.m_hBitMap /* lzdsh_dlg->m_hBckGrndBmp */ == NULL)
      {
         lzdsh_dlg->m_BgrBmpData.m_hBitMap = // lzdsh_dlg->m_hBckGrndBmp =
// #if IBSH_SKIN == IBSH_SKIN_STANDART
//          CreateBitmap(LZDSH_BCKGRND_DX, LZDSH_BCKGRND_DY, 3, 24, bgrcols);
// #else
            LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_BMP_BCKGRND));
// #endif
         KP_ASSERT(lzdsh_dlg->m_BgrBmpData.m_hBitMap /* lzdsh_dlg->m_hBckGrndBmp */ != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=GetDC(ms_window);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         lzdsh_dlg->m_BgrBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcBckGrnd */ = CreateCompatibleDC(hdc);
         KP_ASSERT(lzdsh_dlg->m_BgrBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcBckGrnd */ != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(lzdsh_dlg->m_BgrBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcBckGrnd */, lzdsh_dlg->m_BgrBmpData.m_hBitMap)) // lzdsh_dlg->m_hBckGrndBmp))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(hdc!=NULL) ReleaseDC(ms_window, hdc);
      hdc=NULL;

#if FALSE
      if(SUCCEEDED(retc))
         retc = KpCreateBitmap(hKpInstance, ms_window, &(lzdsh_dlg->m_BgrBmpData.m_hBitmapCtrl), // lzdsh_dlg->m_hBckGrnd),
            lzdsh_dlg->m_BgrBmpData.m_hBitMap /* lzdsh_dlg->m_hBckGrndBmp */, LZDSH_BCKGRND_X, LZDSH_BCKGRND_Y, LZDSH_BCKGRND_DX, LZDSH_BCKGRND_DY, WS_EX_TRANSPARENT);
      KP_ASSERT(lzdsh_dlg->m_BgrBmpData.m_hBitmapCtrl /* lzdsh_dlg->m_hBckGrnd */ != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) parent_window = lzdsh_dlg->m_BgrBmpData.m_hBitmapCtrl; // lzdsh_dlg->m_hBckGrnd;
#endif
#endif

// ------------------------------- logo
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_LogoBmpData.m_hBitMap == NULL) // (lzdsh_dlg->m_hLogoBmp == NULL)
      {
         lzdsh_dlg->m_LogoBmpData.m_hBitMap /* lzdsh_dlg->m_hLogoBmp */ = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_BMP_LOGO));
         KP_ASSERT(lzdsh_dlg->m_LogoBmpData.m_hBitMap /* lzdsh_dlg->m_hLogoBmp */ != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = GetDC(ms_window);
         KP_ASSERT(hdc != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }
      if(SUCCEEDED(retc))
      {
         lzdsh_dlg->m_LogoBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcLogo */ = CreateCompatibleDC(hdc);
         if(lzdsh_dlg->m_LogoBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcLogo */ == NULL)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(lzdsh_dlg->m_LogoBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcLogo */, lzdsh_dlg->m_LogoBmpData.m_hBitMap /* lzdsh_dlg->m_hLogoBmp */))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(hdc != NULL) ReleaseDC(ms_window, hdc);
      hdc = NULL;
#endif

// ------------------------------- faked menu
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)// ||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_hFMenuBmp==NULL)
      {
         lzdsh_dlg->m_hFMenuBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_BMP_FMENU));
         if(lzdsh_dlg->m_hFMenuBmp == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=GetDC(ms_window);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         lzdsh_dlg->m_hdcFMenu = CreateCompatibleDC(hdc);
         if(lzdsh_dlg->m_hdcFMenu == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(lzdsh_dlg->m_hdcFMenu, lzdsh_dlg->m_hFMenuBmp))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(hdc!=NULL) ReleaseDC(ms_window, hdc);
      hdc=NULL;
#endif

// ------------------------------- button menu
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
#if FALSE
      if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_MenuButFile), KP_ID_FILE,
         LZDSH_MENU_FILE_TXT,
         LZDSH_MENU_FILE_X, LZDSH_MENU_Y, LZDSH_MENU_ITEM_WDT, LZDSH_MENU_ITEM_HGT,
         KP_WND_UNPROC_BUT,
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

      if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_MenuButOpt), KP_ID_OPTIONS,
         LZDSH_MENU_OPTIONS_TXT,
         LZDSH_MENU_OPTIONS_X, LZDSH_MENU_Y, LZDSH_MENU_ITEM_WDT, LZDSH_MENU_ITEM_HGT,
         KP_WND_UNPROC_BUT,
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

      if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_MenuButHelp), KP_ID_HELP,
         LZDSH_MENU_HELP_TXT,
         LZDSH_MENU_HELP_X, LZDSH_MENU_Y, LZDSH_MENU_ITEM_WDT, LZDSH_MENU_ITEM_HGT,
         KP_WND_UNPROC_BUT,
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

// ------------------------------- m_InpEdit
//    if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, parent_window, NULL, (const unsigned char *)"LzdSh", LZDSH_HEAD_X, LZDSH_HEAD_Y, 1, KPW_CONTROL_STYLE_HEADING_3, 0, 0);

//    if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, parent_window, NULL, (const unsigned char *)"Þodis:", LZDSH_INP_PROMPT_X, LZDSH_INP_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0)
//    if(SUCCEEDED(retc)) retc = KpCreateRichEdit(hKpInstance, parent_window, &(lzdsh_dlg->m_InpEdit), (const unsigned char *)"", LZDSH_INP_DX, LZDSH_INP_DY, LZDSH_INP_X, LZDSH_INP_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE|ES_SUNKEN, 0);
      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, parent_window, &(lzdsh_dlg->m_InpEdit), (const unsigned char *)"",
         LZDSH_INP_DX_CREATE, LZDSH_INP_X_CREATE, LZDSH_INP_Y_CREATE, KPW_CONTROL_STYLE_NORMAL,
         (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE:0, 0, 1);
      KP_ASSERT(lzdsh_dlg->m_InpEdit != NULL, KP_E_SYSTEM_ERROR, null, True);
//    if(SUCCEEDED(retc)) retc = lzdsh_dlg->SetEditControlText((const unsigned char *)"");


#ifdef Debug
#ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_InpEdit, SW_HIDE);
#endif
#endif


// ------------------------------- m_TabCtrl
#if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) lzdsh_dlg->m_TabCtrl = CreateWindowEx(0, WC_TABCONTROL, "",
            WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, //  | TCS_BUTTONS,
            LZDSH_TAB_X, LZDSH_TAB_Y, LZDSH_TAB_DX, LZDSH_TAB_DY,
            parent_window, NULL, hKpInstance, NULL);
      KP_ASSERT(lzdsh_dlg->m_TabCtrl != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_hTabImgList == NULL)
      {
         lzdsh_dlg->m_hTabImgList = ImageList_Create(LZDSH_BUT_WDT, LZDSH_BUT_WDT,
                  ILC_COLOR16|ILC_MASK, 0, LZDSH_TAB_NUM_OF_TABS);
         if(lzdsh_dlg->m_hTabImgList == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(lzdsh_dlg->m_hMainBmp == NULL)
               lzdsh_dlg->m_hMainBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_MAIN_BITMAP));
         KP_ASSERT(lzdsh_dlg->m_hMainBmp != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            if(lzdsh_dlg->m_hMainMaskBmp == NULL)
               lzdsh_dlg->m_hMainMaskBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_MAIN_MASK_BITMAP));
         KP_ASSERT(lzdsh_dlg->m_hMainMaskBmp != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            if(lzdsh_dlg->m_hSearchBmp == NULL)
               lzdsh_dlg->m_hSearchBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_SEARCH_ROT_BITMAP));
         KP_ASSERT(lzdsh_dlg->m_hSearchBmp != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            if(lzdsh_dlg->m_hSearchMaskBmp == NULL)
               lzdsh_dlg->m_hSearchMaskBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_SEARCH_ROT_MASK_BITMAP));
         KP_ASSERT(lzdsh_dlg->m_hSearchMaskBmp != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            if(lzdsh_dlg->m_hHistBmp == NULL)
               lzdsh_dlg->m_hHistBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_HIST_BITMAP));
         KP_ASSERT(lzdsh_dlg->m_hHistBmp != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            if(lzdsh_dlg->m_hHistMaskBmp == NULL)
               lzdsh_dlg->m_hHistMaskBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_HIST_MASK_BITMAP));
         KP_ASSERT(lzdsh_dlg->m_hHistMaskBmp != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            if(ImageList_Add(lzdsh_dlg->m_hTabImgList, lzdsh_dlg->m_hMainBmp, lzdsh_dlg->m_hMainMaskBmp) == (-1))
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(ImageList_Add(lzdsh_dlg->m_hTabImgList, lzdsh_dlg->m_hSearchBmp, lzdsh_dlg->m_hSearchMaskBmp) == (-1))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(ImageList_Add(lzdsh_dlg->m_hTabImgList, lzdsh_dlg->m_hHistBmp, lzdsh_dlg->m_hHistMaskBmp) == (-1))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      } // if((m_hTabImgList==NULL) && SUCCEEDED(retc))

      if(SUCCEEDED(retc))
      {
         TabCtrl_SetImageList(lzdsh_dlg->m_TabCtrl, lzdsh_dlg->m_hTabImgList);

         tie.mask = TCIF_IMAGE; // | TCIF_TEXT
//       tie.iImage = -1;
//       tie.pszText = "aaaa";
      }

      for(ii = 0; (ii < LZDSH_TAB_NUM_OF_TABS) && SUCCEEDED(retc); ii++)
      {
         tie.iImage = ii;
         if(TabCtrl_InsertItem(lzdsh_dlg->m_TabCtrl, ii, &tie) == -1)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_TabCtrl, SW_HIDE);
#endif
#endif

// ---------------------------- fiktyvus tabu langai
      if(SUCCEEDED(retc))
         lzdsh_dlg->m_TabMain = CreateWindowEx
         (
            0,                      // DWORD dwExStyle,      // extended window style
            "KPTEST",
            "LzdshTabMain",      // LPCTSTR lpWindowName, // pointer to window name
            WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            CW_USEDEFAULT, // int x,               // horizontal position of window
            CW_USEDEFAULT, // int y,               // vertical position of window
            CW_USEDEFAULT, // int nWidth,           // window width
            CW_USEDEFAULT, // int nHeight,          // window height
#ifdef KP_USE_WXWIDGETS
               (HWND)GetHWND(),
#else
               lzdsh_dlg->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
#endif
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
      KP_ASSERT(lzdsh_dlg->m_TabMain != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);

      if(SUCCEEDED(retc))
         lzdsh_dlg->m_TabSearch = CreateWindowEx
         (
            0,                      // DWORD dwExStyle,      // extended window style
            "KPTEST",
            "LzdshTabSearch",      // LPCTSTR lpWindowName, // pointer to window name
            WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            CW_USEDEFAULT, // int x,               // horizontal position of window
            CW_USEDEFAULT, // int y,               // vertical position of window
            CW_USEDEFAULT, // int nWidth,           // window width
            CW_USEDEFAULT, // int nHeight,          // window height
#ifdef KP_USE_WXWIDGETS
               (HWND)GetHWND(),
#else
               lzdsh_dlg->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
#endif
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
      KP_ASSERT(lzdsh_dlg->m_TabSearch != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);

      if(SUCCEEDED(retc))
         lzdsh_dlg->m_TabHist = CreateWindowEx
         (
            0,                      // DWORD dwExStyle,      // extended window style
            "KPTEST",
            "LzdshTabHist",      // LPCTSTR lpWindowName, // pointer to window name
            WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            CW_USEDEFAULT, // int x,               // horizontal position of window
            CW_USEDEFAULT, // int y,               // vertical position of window
            CW_USEDEFAULT, // int nWidth,           // window width
            CW_USEDEFAULT, // int nHeight,          // window height
#ifdef KP_USE_WXWIDGETS
               (HWND)GetHWND(),
#else
               lzdsh_dlg->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
#endif
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
      KP_ASSERT(lzdsh_dlg->m_TabHist != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_TabMain, SW_HIDE);
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_TabSearch, SW_HIDE);
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_TabHist, SW_HIDE);
#endif
#endif

// ---------------------
#else // #if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_TabMain),
         LZDSH_ID_MAIN_TAB,
         LZDSH_IDI_MAIN_BITMAP,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_MAIN_LIGHT_BITMAP,
#else
         LZDSH_IDI_MAIN_BITMAP,
#endif
         LZDSH_IDI_MAIN_SEL_BITMAP,
         LZDSH_TAB_MAIN_X, LZDSH_TAB_MAIN_Y, LZDSH_TAB_DX, LZDSH_TAB_DY,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         KP_WND_UNPROC_BUT|
#endif
            KP_WND_TAB|KP_WND_LEFT_TAB, 0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

      if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabMain, BM_SETCHECK, BST_CHECKED, KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB);

      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_TabSearch),
         LZDSH_ID_SEARCH_TAB,
         LZDSH_IDI_SEARCH_ROT_BITMAP,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_SEARCH_ROT_LIGHT_BITMAP,
#else
         LZDSH_IDI_SEARCH_ROT_BITMAP,
#endif
         LZDSH_IDI_SEARCH_ROT_SEL_BITMAP,
         LZDSH_TAB_SEARCH_X, LZDSH_TAB_SEARCH_Y, LZDSH_TAB_DX, LZDSH_TAB_DY,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         KP_WND_UNPROC_BUT|
#endif
            KP_WND_TAB|KP_WND_RIGHT_TAB, 0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_TabHist),
         LZDSH_ID_HIST_TAB,
         LZDSH_IDI_HIST_BITMAP,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_HIST_LIGHT_BITMAP,
#else
         LZDSH_IDI_HIST_BITMAP,
#endif
         LZDSH_IDI_HIST_SEL_BITMAP,
         LZDSH_TAB_HIST_X, LZDSH_TAB_HIST_Y, LZDSH_TAB_DX, LZDSH_TAB_DY,
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         KP_WND_UNPROC_BUT|
#endif
            KP_WND_TAB|KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB, 0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

// ------------------------------- m_MainList
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "WM_CREATE %d", lzdsh_dlg->m_iNumOfLines);
KP_TRACE(str_buf);
#endif

      if(SUCCEEDED(retc)) retc = KpCreateLzdshListBox(hKpInstance, parent_window, &(lzdsh_dlg->m_MainList), (const unsigned char *)"Sàraðas:",
         LZDSH_LIST_DX_CREATE, LZDSH_LIST_DY_DYN_CREATE, LZDSH_LIST_X_CREATE, LZDSH_LIST_Y_CREATE,
         KPW_CONTROL_STYLE_NORMAL, (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         0, NULL, -1);
      KP_ASSERT(lzdsh_dlg->m_MainList != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc))
         if(SendMessage(lzdsh_dlg->m_MainList, LB_RESETCONTENT, 0, 0L) == CB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

//    if(SUCCEEDED(retc))
//    {
//       retv=SendMessage(lzdsh_dlg->m_MainList, LB_INITSTORAGE, 20000 /* lzdsh_dlg->m_iNumOfListEntries */,
//          20000L /* lzdsh_dlg->m_iNumOfListEntries */ * LZDSH_MAX_LIST_ITEM_WDT);
//       if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
//       if((retv==LB_ERR) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
//    }

#if FALSE
      for(ii=0; (ii<LZDSH_LIST_NUM_LINES) && SUCCEEDED(retc); ii++)
         retc = LzdshAppendStrToList(lzdsh_dlg->m_MainList, (const unsigned char *)"");
#endif
      if(SUCCEEDED(retc)) lzdsh_dlg->m_CurList = lzdsh_dlg->m_MainList;


#ifdef Debug
#ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_MainList, SW_HIDE);
#endif
#endif

// ------------------------------- m_SearchList
      if(SUCCEEDED(retc)) retc = KpCreateLzdshListBox(hKpInstance, parent_window, &(lzdsh_dlg->m_SearchList), (const unsigned char *)"Sàraðas:",
         LZDSH_LIST_DX_CREATE, LZDSH_LIST_DY_DYN_CREATE, LZDSH_LIST_X_CREATE, LZDSH_LIST_Y_CREATE,
         KPW_CONTROL_STYLE_NORMAL, (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         0, NULL, -1);
      KP_ASSERT(lzdsh_dlg->m_SearchList != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc))
         if(SendMessage(lzdsh_dlg->m_SearchList, LB_RESETCONTENT, 0, 0L) == CB_ERR)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

//    if(SUCCEEDED(retc))
//    {
//       retv=SendMessage(lzdsh_dlg->m_SearchList, LB_INITSTORAGE, LZDSH_MAX_NUM_OF_SEARCH_ITEMS,
//             LZDSH_MAX_NUM_OF_SEARCH_ITEMS*LZDSH_MAX_LIST_ITEM_WDT);
//       if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
//       if((retv==LB_ERR) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
//    }

      if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_SearchList, SW_HIDE);

// ------------------------------- m_HistList
      if(SUCCEEDED(retc)) retc = KpCreateLzdshListBox(hKpInstance, parent_window, &(lzdsh_dlg->m_HistList), (const unsigned char *)"Sàraðas:",
         LZDSH_LIST_DX_CREATE, LZDSH_LIST_DY_DYN_CREATE, LZDSH_LIST_X_CREATE, LZDSH_LIST_Y_CREATE,
         KPW_CONTROL_STYLE_NORMAL, (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         0, NULL, -1);
      KP_ASSERT(lzdsh_dlg->m_HistList != NULL, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc))
         if(SendMessage(lzdsh_dlg->m_HistList, LB_RESETCONTENT, 0, 0L) == CB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         retv = SendMessage(lzdsh_dlg->m_HistList, LB_INITSTORAGE, LZDSH_MAX_NUM_OF_SEARCH_ITEMS,
               LZDSH_MAX_NUM_OF_SEARCH_ITEMS*LZDSH_MAX_LIST_ITEM_WDT);
      KP_ASSERT(retv != LB_ERRSPACE, KP_E_OUTOFMEM, GetLastError(), True);
      KP_ASSERT(retv != LB_ERR, KP_E_ILLFUNC, GetLastError(), True);

      if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_HistList, SW_HIDE);

// ------------------------------- m_TagList
#ifdef LZDSH_EDITOR_BUILD
      if(SUCCEEDED(retc)) retc = KpCreateListBox(hKpInstance, parent_window, &(lzdsh_dlg->m_TagList), (const unsigned char *)"Sàraðas:",
         LZDSH_TAGLIST_DX_DYN_CREATE, LZDSH_TAGLIST_DY_CREATE, LZDSH_TAGLIST_X_CREATE, LZDSH_TAGLIST_Y_DYN_CREATE,
         KPW_CONTROL_STYLE_NORMAL, (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         0/*LBS_OWNERDRAWFIXED*/, NULL, -1, TYP_ListBoxTreeInverted);
      KP_ASSERT(lzdsh_dlg->m_TagList != NULL, KP_E_SYSTEM_ERROR, null, True);

#if FALSE
      if(SUCCEEDED(retc))
         if(SendMessage(lzdsh_dlg->m_TagList, LB_RESETCONTENT, NULL, NULL) == CB_ERR)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         retv = SendMessage(lzdsh_dlg->m_TagList, LB_INITSTORAGE, LZDSH_MAX_NUM_OF_EDIT_TAGS,
               LZDSH_MAX_NUM_OF_EDIT_TAGS*LZDSH_MAX_EDIT_TAG_WDT);
         KP_ASSERT(retv != LB_ERRSPACE, KP_E_OUTOFMEM, GetLastError(), True);
         KP_ASSERT(retv != LB_ERR, KP_E_ILLFUNC, GetLastError(), True);
      }
#else
      if(SUCCEEDED(retc)) retc = ResetListBoxContents(lzdsh_dlg->m_TagList, LZDSH_MAX_NUM_OF_EDIT_TAGS, LZDSH_MAX_EDIT_TAG_WDT);
#endif

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_TagList, SW_HIDE);
#endif
#endif

#endif


// ------------------------------- m_ResRichEdit
#ifdef IBSH_RES_MODE_RTF
//    if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, parent_window, NULL, (const unsigned char *)"Paaiðkinimas:", LZDSH_RES_PROMPT_X, LZDSH_RES_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0);
      if(SUCCEEDED(retc)) retc=KpCreateRichEdit(hKpInstance, parent_window, &(lzdsh_dlg->m_ResRichEdit), (const unsigned char *)"",
         LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE, LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE,
         KPW_CONTROL_STYLE_NORMAL,
         (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         ES_MULTILINE|WS_VSCROLL  /* |WS_CLIPSIBLINGS |ES_READONLY */);
      KP_ASSERT(lzdsh_dlg->m_ResRichEdit != NULL, KP_E_SYSTEM_ERROR, null, True);
//    if(SUCCEEDED(retc)) retc = KpSetCtrlRtfText(lzdsh_dlg->m_ResRichEdit, "", True /* False */);

//    if(SUCCEEDED(retc)) EnableWindow(lzdsh_dlg->m_ResRichEdit, False);

// #ifdef IBSH_RES_MODE_MSHTML
//    if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_ResRichEdit, SW_HIDE);
// #endif

#  ifdef Debug
#     ifdef KP_USE_WXWIDGETS
      if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_ResRichEdit, SW_HIDE);
#     endif
#  endif
#endif

// ------------------------------- m_ResRichTest
#ifdef IBSH_RES_MODE_RTF
#  ifdef LZDSH_EDITOR_BUILD
#     if FALSE // #ifdef Debug
      if(SUCCEEDED(retc)) retc = KpCreateRichEdit(hKpInstance, parent_window, &(lzdsh_dlg->m_ResRichTest), (const unsigned char *)"",
         LZDSH_RTF_TEST_DX, LZDSH_RTF_TEST_DY,
         LZDSH_RTF_TEST_X_DYN_CREATE, LZDSH_RTF_TEST_Y_DYN_CREATE,
         KPW_CONTROL_STYLE_NORMAL,
         (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         /* WS_POPUPWINDOW| */ ES_MULTILINE|WS_VSCROLL /* |ES_READONLY */);
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_ResRichTest == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#     endif
#  endif
#endif


// ------------------------------- m_ResHtml
#ifdef IBSH_RES_MODE_MSHTML // #if FALSE //
#  if Compiler != Watcom
      if(SUCCEEDED(retc))
         KP_NEW(lzdsh_dlg->m_ResHtml, HTMLWindow
            (
//             "<html><head>"
//             "<title>MSHTMLTest</title>"   // seems a little useless in this context
//             "</head><body>"
//             "<h1>This is a test</h1>"
//             "I offer the following links:"
//             "<ul>"
//             "<li><a href='http://www.google.com'>www.google.com</a>"
//             "<li><a href='http://www.adp-gmbh.ch'>www.adp-gmbh.ch</a>"
//             "<li><a href='http://www.yahoo.com'>www.yahoo.com</a>"
//             "</ul>"
//             "</body></html>"
               "",
               "MSHTML", // "MSHTMLTest",
               hKpInstance,
               false,  // not an url
               parent_window, // HWND_DESKTOP, //
               LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE, LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE
            )
         );
#  endif

#  if FALSE
   if(SUCCEEDED(retc)) if(lzdsh_dlg->m_ResHtml != NULL)
      lzdsh_dlg->m_ResHtml->HTML
      (
         "<html><head>"
         "<title>MSHTMLTest</title>"
         "</head><body>"
         "<h1>Kaka laka</h1>"
         "I offer the following links:"
         "<ul>"
         "<li><a href='http://www.google.com'>www.google.com</a>"
         "<li><a href='http://www.adp-gmbh.ch'>www.adp-gmbh.ch</a>"
         "<li><a href='http://www.yahoo.com'>www.yahoo.com</a>"
         "</ul>"
         "</body></html>"
      );
#  endif
#endif


// -------------------------------- KpGeckoDialog::m_pResCtrl
#ifdef IBSH_RES_MODE_XGECKO
#ifndef LZDSHT_DISPLAY_SEARCH_THREAD
      if(SUCCEEDED(retc)) lzdsh_dlg->CreateResCtrl(LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE, LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE, parent_window);
#endif
#endif

// ------------------------------- m_NodList
#ifdef LZDSH_EDITOR_BUILD
#  ifdef KP_USE_WXWIDGETS

      if(SUCCEEDED(retc))
      {
wxPoint *pos= NULL;
         KP_NEW(pos, wxPoint(20, 20));
wxSize *size= NULL;
         KP_NEW(size, wxSize(20, 20));
         KP_NEW(lzdsh_dlg->m_pNodList, wxWindow( // wxListBox(
                           this, // lzdsh_dlg->m_hDialogWindow, // &theDialog, // &TestWindow, // pTestWindow, //
                           LZDE_ID_NODLIST,
                           *pos, // LZDSH_NODLIST_X_DYN_CREATE, LZDSH_NODLIST_Y_CREATE),
                           *size, // LZDSH_NODLIST_DX_CREATE, LZDSH_NODLIST_DY_DYN_CREATE),
                           // 0, NULL,
                           0); // wxLB_HSCROLL));
         KP_DELETE(pos);
         KP_DELETE(size);
      }

#  else
      if(SUCCEEDED(retc)) retc=KpCreateListBox(hKpInstance, parent_window, &(lzdsh_dlg->m_NodList), (const unsigned char *)"Sàraðas:",
         LZDSH_NODLIST_DX_CREATE, LZDSH_NODLIST_DY_DYN_CREATE, LZDSH_NODLIST_X_DYN_CREATE, LZDSH_NODLIST_Y_CREATE,
         KPW_CONTROL_STYLE_NORMAL, (IBSH_SKIN == IBSH_SKIN_STANDART)?WS_EX_CLIENTEDGE|ES_SUNKEN:0,
         0/*LBS_OWNERDRAWFIXED*/, NULL, -1, TYP_ListBoxTree);
      KP_ASSERT(lzdsh_dlg->m_NodList !=NULL, KP_E_SYSTEM_ERROR, null, True);

#if FALSE
      if(SUCCEEDED(retc))
         if(SendMessage(lzdsh_dlg->m_NodList, LB_RESETCONTENT, NULL, NULL) == CB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         retv = SendMessage(lzdsh_dlg->m_NodList, LB_INITSTORAGE, LZDSH_MAX_NUM_OF_EDIT_NODES,
            LZDSH_MAX_NUM_OF_EDIT_NODES*LZDSH_MAX_EDIT_NODE_WDT);
      KP_ASSERT(retv != LB_ERRSPACE, KP_E_OUTOFMEM, GetLastError(), True);
      KP_ASSERT(retv != LB_ERR, KP_E_ILLFUNC, GetLastError(), True);
#else
      if(SUCCEEDED(retc)) retc = ResetListBoxContents(lzdsh_dlg->m_NodList, LZDSH_MAX_NUM_OF_EDIT_NODES, LZDSH_MAX_EDIT_NODE_WDT);
#endif

//    if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_NodList, SW_SHOW);

//    if(SUCCEEDED(retc)) retv=SendMessage(lzdsh_dlg->m_NodList, LB_ADDSTRING, NULL, (LPARAM)"pirma");
//    if(SUCCEEDED(retc)) retv=SendMessage(lzdsh_dlg->m_NodList, LB_ADDSTRING, NULL, (LPARAM)"antra");

#  endif

#endif


// ------------------------------- navigation buttons
#ifdef IBSH_RES_MODE_XGECKO
#  if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, parent_window, &(lzdsh_dlg->m_ButBack), LZDSH_ID_BACK,
         LZDSH_IDI_BACK_ICON, LZDSH_BUT_BACK_X, LZDSH_BUT_BACK_Y, LZDSH_BUT_BACK_DX, LZDSH_BUT_BACK_DY, 0, 0);
#  else
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButBack), LZDSH_ID_BACK,
         LZDSH_IDI_BACK_BITMAP,
         LZDSH_IDI_BACK_LIGHT_BITMAP,
         LZDSH_IDI_BACK_SEL_BITMAP,
         LZDSH_BUT_BACK_X, LZDSH_BUT_BACK_Y, LZDSH_BUT_BACK_DX, LZDSH_BUT_BACK_DY,
         KP_WND_UNPROC_BUT,
         0, KpColorSchemeLocal);
#  endif
#endif

#ifdef IBSH_RES_MODE_XGECKO
#  if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, parent_window, &(lzdsh_dlg->m_ButForward), LZDSH_ID_FORWARD,
         LZDSH_IDI_FORWARD_ICON, LZDSH_BUT_FORWARD_X, LZDSH_BUT_FORWARD_Y, LZDSH_BUT_FORWARD_DX, LZDSH_BUT_FORWARD_DY, 0, 0);
#  else
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButForward), LZDSH_ID_FORWARD,
         LZDSH_IDI_FORWARD_BITMAP,
         LZDSH_IDI_FORWARD_LIGHT_BITMAP,
         LZDSH_IDI_FORWARD_SEL_BITMAP,
         LZDSH_BUT_FORWARD_X, LZDSH_BUT_FORWARD_Y, LZDSH_BUT_FORWARD_DX, LZDSH_BUT_FORWARD_DY,
         KP_WND_UNPROC_BUT,
         0, KpColorSchemeLocal);
#  endif
#endif

// ------------------------------- toolbar buttons
#if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, parent_window, &(lzdsh_dlg->m_ButSearch), LZDSH_ID_SEARCH,
         LZDSH_IDI_SEARCH_ICON, LZDSH_BUT_SEARCH_X, LZDSH_BUT_SEARCH_Y, LZDSH_BUT_SEARCH_DX, LZDSH_BUT_WDT, 0, 0);
#else
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButSearch), LZDSH_ID_SEARCH,
         LZDSH_IDI_SEARCH_BITMAP,
#  if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_SEARCH_LIGHT_BITMAP,
         LZDSH_IDI_SEARCH_SEL_BITMAP,
#  else
         LZDSH_IDI_SEARCH_BITMAP,
         LZDSH_IDI_SEARCH_BITMAP,
#  endif
         LZDSH_BUT_SEARCH_X, LZDSH_BUT_SEARCH_Y, LZDSH_BUT_SEARCH_DX, LZDSH_BUT_WDT,
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#  else
         0,
#  endif
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

#if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, parent_window, &(lzdsh_dlg->m_ButFontZoom), LZDSH_ID_FONT_ZOOM,
         LZDSH_IDI_ZOOM_ICON, LZDSH_BUT_FONT_ZOOM_X, LZDSH_BUT_FONT_ZOOM_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT, 0, BS_AUTOCHECKBOX|BS_PUSHLIKE /* BS_FLAT */);
#else
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButFontZoom), LZDSH_ID_FONT_ZOOM,
         LZDSH_IDI_ZOOM_BITMAP,
#  if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_ZOOM_LIGHT_BITMAP,
         LZDSH_IDI_ZOOM_SEL_BITMAP,
#  else
         LZDSH_IDI_ZOOM_BITMAP,
         LZDSH_IDI_ZOOM_BITMAP,
#  endif
         LZDSH_BUT_FONT_ZOOM_X, LZDSH_BUT_FONT_ZOOM_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#  else
         0,
#  endif
         BS_PUSHLIKE, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

#if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, parent_window, &(lzdsh_dlg->m_ButNarrow), LZDSH_ID_NARROW,
         LZDSH_IDI_WIDE_SEL_ICON, LZDSH_BUT_NARROW_X, LZDSH_BUT_NARROW_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT, 0, BS_AUTOCHECKBOX|BS_PUSHLIKE /* BS_FLAT */);
#else
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButNarrow), LZDSH_ID_NARROW,
         LZDSH_IDI_WIDE_BITMAP,
#  if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_WIDE_LIGHT_BITMAP,
         LZDSH_IDI_WIDE_SEL_BITMAP,
#  else
         LZDSH_IDI_WIDE_BITMAP,
         LZDSH_IDI_WIDE_BITMAP,
#  endif
         LZDSH_BUT_NARROW_X, LZDSH_BUT_NARROW_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#  else
         0,
#  endif
         BS_PUSHLIKE, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif
//    if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_ButNarrow, BM_SETSTATE, True, 0);
      if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_ButNarrow, BM_SETCHECK, BST_CHECKED, 0);

#if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpCreateButton(hKpInstance, parent_window, &(lzdsh_dlg->m_ButAcc), LZDSH_ID_ACCENTS,
         LZDSH_IDI_ACC_SEL_ICON, LZDSH_BUT_ACCENTS_X, LZDSH_BUT_ACCENTS_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT, 0, BS_AUTOCHECKBOX|BS_PUSHLIKE /* BS_FLAT */);
#else
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButAcc), LZDSH_ID_ACCENTS,
         LZDSH_IDI_ACC_BITMAP,
#  if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_ACC_LIGHT_BITMAP,
         LZDSH_IDI_ACC_SEL_BITMAP,
#  else
         LZDSH_IDI_ACC_BITMAP,
         LZDSH_IDI_ACC_BITMAP,
#  endif
         LZDSH_BUT_ACCENTS_X, LZDSH_BUT_ACCENTS_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#  else
         0,
#  endif
         BS_PUSHLIKE, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif
//    if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_ButAcc, BM_SETSTATE, True, 0);
      if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_ButAcc, BM_SETCHECK, BST_CHECKED, 0);


#ifdef Debug
#  ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_ButSearch, SW_HIDE);
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_ButFontZoom, SW_HIDE);
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_ButNarrow, SW_HIDE);
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_ButAcc, SW_HIDE);
#  endif
#endif


// ------------------------------- control buttons
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButMinimize), KP_ID_MINIMIZE,
         LZDSH_IDI_MINIMIZE_BITMAP,
#  if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_MINIMIZE_LIGHT_BITMAP,
         LZDSH_IDI_MINIMIZE_SEL_BITMAP,
#  else
         LZDSH_IDI_MINIMIZE_BITMAP,
         LZDSH_IDI_MINIMIZE_BITMAP,
#  endif
         LZDSH_BUT_MINIMIZE_X, LZDSH_BUT_MINIMIZE_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#  else
         0,
#  endif
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) retc=KpCreateButtonLoc(hKpInstance, parent_window, &(lzdsh_dlg->m_ButExit), KP_ID_EXIT,
         LZDSH_IDI_EXIT_BITMAP,
#  if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
         LZDSH_IDI_EXIT_LIGHT_BITMAP,
         LZDSH_IDI_EXIT_SEL_BITMAP,
#  else
         LZDSH_IDI_EXIT_BITMAP,
         LZDSH_IDI_EXIT_BITMAP,
#  endif
         LZDSH_BUT_EXIT_X, LZDSH_BUT_EXIT_Y, LZDSH_BUT_WDT, LZDSH_BUT_WDT,
#  if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_UNPROC_BUT,
#  else
         0,
#  endif
         0, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

// ------------------------------- combo box of dictionaries
      if(SUCCEEDED(retc)) retc=KpCreateComboBox(hKpInstance, parent_window, &(lzdsh_dlg->m_DictBox), (const unsigned char *)"DictBox",
// #if IBSH_SKIN == IBSH_SKIN_STANDART
         LZDSH_DICT_BOX_DX, LZDSH_DICT_BOX_DY*(lzdsh_dlg->m_iNumOfDictEntries + 1), LZDSH_DICT_BOX_X, LZDSH_DICT_BOX_Y, KPW_CONTROL_STYLE_NORMAL,
         WS_EX_CLIENTEDGE|ES_SUNKEN, CBS_DROPDOWNLIST /* ES_READONLY */, lzdsh_dlg->m_DictList, 0);
// #else
//       LZDSH_DICT_BOX_DX-2*KPW_CTRL_BORDER_WDT, LZDSH_DICT_BOX_DY*(lzdsh_dlg->m_iNumOfDictEntries+1),
//       LZDSH_DICT_BOX_X+KPW_CTRL_BORDER_WDT, LZDSH_DICT_BOX_Y+KPW_CTRL_BORDER_WDT,
//       KPW_CONTROL_STYLE_NORMAL, 0, 0, lzdsh_dlg->m_DictList, 0);
// #endif
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_DictBox == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// -------------------------- restore selected dictionary
      KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
      if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

      if(SUCCEEDED(retc))
      {
         hKey = NULL;

         found = False;

         sprintf((char *)key_name,
            "Software\\%s\\%d", // "Software\\%s\\%s",
            publisher,
            prod_ver // prod_name
            );
         if(RegOpenKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS)
         {
            dwBufLen=KP_MAX_FNAME_LEN;
            if(RegQueryValueEx(hKey, "DictName", NULL,
               &dwValType, (LPBYTE)dict, &dwBufLen)==ERROR_SUCCESS)
            {
               if((dwValType != REG_SZ) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// KpMsgOut_1("LzdShDialogProc() WM_CREATE [0] lzdsh_dlg: %x", lzdsh_dlg);

               if(SUCCEEDED(retc))
               {
                  retc = lzdsh_dlg->ChangeDict(dict, False, True);
                  found = SUCCEEDED(retc);
                  if(!found) if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_OBJ_NOT_FOUND))
                     retc = KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
               }

            }
            else // if(RegQueryValueEx(hKey, "DictName", NULL,
            {
               dwBufLen=sizeof(ll);
               if(RegQueryValueEx(hKey, "Dict", NULL,
                  &dwValType, (LPBYTE)&ll, &dwBufLen)==ERROR_SUCCESS)
               {
                  if((dwValType != REG_DWORD) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc))
                  {
                     if((ll<0) || (ll >= lzdsh_dlg->m_iNumOfDictEntries))
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     else
                     {
                        if(SUCCEEDED(retc))
                        {
                           lzdsh_dlg->m_iCurDictEntry = ll;
                           retc = lzdsh_dlg->ChangeDict(ll, False, True);
                           found = SUCCEEDED(retc);
                           if(!found) if(retc == KP_E_OBJ_NOT_FOUND)
                              retc = KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                        }
                     }
                  }

               } // if(RegQueryValueEx(hKey, "Dict", NULL,

            } // else // if(RegQueryValueEx(hKey, "DictName", NULL,

         } // if(RegOpenKeyEx(HKEY_CURRENT_USER, ...


         if(hKey)
         {
            retw = RegCloseKey(hKey);
            if(retw!=ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
            hKey=0;
         }

         if((!found) && SUCCEEDED(retc))
         {
            retc = lzdsh_dlg->ChangeDict(lzdsh_dlg->m_iCurDictEntry, False, True); // (0, ...
            if(retc == KP_E_OBJ_NOT_FOUND)
               retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }

      } // if(SUCCEEDED(retc))

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
if(SUCCEEDED(retc)) ShowWindow(lzdsh_dlg->m_DictBox, SW_HIDE);
#endif
#endif

// -------------------------------
      KP_ASSERT(::SetFocus(lzdsh_dlg->m_InpEdit), KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc)) lzdsh_dlg->m_bWrkFl = True;

// -------------------------------
#if FALSE
      if(SUCCEEDED(retc)) retc = lzdsh_dlg->RestoreSavedCoords();

      if(SUCCEEDED(retc)) lzdsh_dlg->m_bResizing = False;
      if(SUCCEEDED(retc)) lzdsh_dlg->m_iDoRedraw = 1; // lzdsh_dlg->m_bDoRedraw = True;
      if(SUCCEEDED(retc)) retc = lzdsh_dlg->RedrawWindow();
#endif

// KpMsgOut_0("LzdShDialogProc() WM_CREATE [1]");

      break; // case WM_CREATE

   case WM_INITDIALOG:
      retb=TRUE;
      break;

   case WM_PAINT:
#if FALSE // #ifdef LZDSHT_DISPLAY_SEARCH_THREAD // IBSH_RES_MODE_XGECKO
//    KP_ASSERT(lzdsh_dlg->m_pResCtrl, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_pResCtrl)
      {
#  ifdef Debug
static int ii;
#  endif

//       lzdsh_dlg->m_pResCtrl->setSize(LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE);

KP_TRACE_1("issiunciau InvalidateRect() %d", ii++);
         if(!InvalidateRect(lzdsh_dlg->m_pResCtrl->m_hWnd, 0, TRUE))
         {
#  ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
         }

//       PostMessage(lzdsh_dlg->m_pResCtrl->m_hWnd, uMsg, wParam, lParam);
//       lzdsh_dlg->m_pResCtrl->wndProc(lzdsh_dlg->m_pResCtrl->m_hWnd, uMsg, wParam, lParam);
      }
#endif

      hdc=NULL;
      if(SUCCEEDED(retc))
      {
//       hdc=GetDC(ms_window);
         hdc=BeginPaint(ms_window, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// ------------------------------- background
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#if FALSE
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_BgrBmpData.m_hBitMap /* lzdsh_dlg->m_hBckGrndBmp */ == NULL)
      {
         lzdsh_dlg->m_BgrBmpData.m_hBitMap /* lzdsh_dlg->m_hBckGrndBmp */ = LoadBitmap(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_BMP_BCKGRND));
         if(lzdsh_dlg->m_BgrBmpData.m_hBitMap /* lzdsh_dlg->m_hBckGrndBmp */ == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(hdc, lzdsh_dlg->m_BgrBmpData.m_hBitMap)) // lzdsh_dlg->m_hBckGrndBmp))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_BgrBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcBckGrnd */ == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!StretchBlt(ps.hdc, LZDSH_BCKGRND_X, LZDSH_BCKGRND_Y, LZDSH_BCKGRND_DX, LZDSH_BCKGRND_DY,
            lzdsh_dlg->m_BgrBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcBckGrnd */, 0, 0, LZDSH_BCKGRND_DX, LZDSH_BCKGRND_DY,
            SRCCOPY))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

// ------------------------------- line delimiters / resize field
#if IBSH_SKIN == IBSH_SKIN_STANDART
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, LZDSH_LINE_X, LZDSH_LINE_1_Y, LZDSH_LINE_X+LZDSH_LINE_DX, LZDSH_LINE_1_Y, KP_WND_SUNKEN, NULL); // aPenSchemeWin); // lzdsh_dlg->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, LZDSH_LINE_X, LZDSH_LINE_2_Y, LZDSH_LINE_X+LZDSH_LINE_DX, LZDSH_LINE_2_Y, KP_WND_SUNKEN, NULL); // aPenSchemeWin); // lzdsh_dlg->m_aPenScheme);
#else
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc,
         lzdsh_dlg->m_iWndCurDX-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-2-LZDSH_RESIZE_WDT,
         lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-4,
         lzdsh_dlg->m_iWndCurDX-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-2,
         lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-4-LZDSH_RESIZE_WDT,
         KP_WND_RAISED, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc,
         lzdsh_dlg->m_iWndCurDX-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-2-LZDSH_RESIZE_WDT/2,
         lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-4,
         lzdsh_dlg->m_iWndCurDX-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-2,
         lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-4-LZDSH_RESIZE_WDT/2,
         KP_WND_RAISED, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc,
         lzdsh_dlg->m_iWndCurDX-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-2-1,
         lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-4,
         lzdsh_dlg->m_iWndCurDX-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-2,
         lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-4-1,
         KP_WND_RAISED, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);
#endif

// ------------------------------- logo
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_LogoBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcLogo */ == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!StretchBlt(ps.hdc, LZDSH_LOGO_X, LZDSH_LOGO_Y, LZDSH_LOGO_DX, LZDSH_LOGO_DY,
            lzdsh_dlg->m_LogoBmpData.m_hdcBmpHdc /* lzdsh_dlg->m_hdcLogo */, 0, 0, LZDSH_LOGO_DX, LZDSH_LOGO_DY,
            SRCCOPY))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

// ------------------------------- faked menu
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) // ||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_hdcFMenu == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!StretchBlt(ps.hdc, LZDSH_FMENU_X, LZDSH_FMENU_Y, LZDSH_FMENU_DX, LZDSH_FMENU_DY,
            lzdsh_dlg->m_hdcFMenu, 0, 0, LZDSH_FMENU_DX, LZDSH_FMENU_DY,
            SRCCOPY))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
// ------------------------------- window and control borders
      if(SUCCEEDED(retc)) retc = KpDrawRect(hdc, 0, 0, lzdsh_dlg->m_iWndCurDX, lzdsh_dlg->m_iWndCurDY, KP_WND_RAISED_BORDER, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, LZDSH_INP_X, LZDSH_INP_Y, LZDSH_INP_X+LZDSH_INP_DX,
         LZDSH_INP_Y+2*KPW_CTRL_BORDER_WDT+iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+3,
         KP_WND_SUNKEN_BORDER, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, LZDSH_RES_X, LZDSH_RES_Y,
         LZDSH_RES_X+LZDSH_RES_DX_DYN, LZDSH_RES_Y+LZDSH_RES_DY_DYN,
         KP_WND_SUNKEN_BORDER, KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, LZDSH_LIST_X, LZDSH_LIST_Y,
         LZDSH_LIST_X+LZDSH_LIST_DX, LZDSH_LIST_Y+LZDSH_LIST_DY_DYN,
#if IBSH_SKIN != IBSH_SKIN_LZDSH_MAHAGON_3D
         KP_WND_NO_TOP|
#endif
            KP_WND_SUNKEN_BORDER,
         KpColorSchemeLocal); // lzdsh_dlg->m_aPenScheme);

// ------------------------------ tab extention
#if IBSH_SKIN != IBSH_SKIN_LZDSH_MAHAGON_3D
      pen_light = NULL;
      pen_dark = NULL;
      pen_norm = NULL;
      pen_black = NULL;

      if(SUCCEEDED(retc))
      {
         pen_light = CreatePen(PS_SOLID, 1, KpColorSchemeLocal[KpShadowLight]);
         if(!pen_light)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         pen_dark = CreatePen(PS_SOLID, 1, KpColorSchemeLocal[KpShadowDark]);
         if(!pen_dark)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         pen_norm = CreatePen(PS_SOLID, 1, KpColorSchemeLocal[KpShadowNorm]);
         if(!pen_norm)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         pen_black = CreatePen(PS_SOLID, 1, KpColorSchemeLocal[KpShadowBlack]);
         if(!pen_black)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
//       if(!SelectObject(hdc, lzdsh_dlg->m_aPenScheme[(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)?KpShadowLight:KpShadowDark]))
         if(!SelectObject(hdc, (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)?pen_light:pen_dark]))
             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
         if(!MoveToEx(hdc, LZDSH_TAB_EXT_X1, LZDSH_TAB_EXT_Y-1, NULL))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!LineTo(hdc, LZDSH_TAB_EXT_X2-((IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)?1:0), LZDSH_TAB_EXT_Y-1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
//       if(!SelectObject(hdc, lzdsh_dlg->m_aPenScheme[(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)?KpShadowNorm:KpShadowBlack]))
         if(!SelectObject(hdc, (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)?pen_norm:pen_black]))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
         if(!MoveToEx(hdc, LZDSH_TAB_EXT_X1, LZDSH_TAB_EXT_Y, NULL))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!LineTo(hdc, LZDSH_TAB_EXT_X2-((IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)?2:0), LZDSH_TAB_EXT_Y))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT
      if(SUCCEEDED(retc))
         if(!SelectObject(hdc, pen_light)) // lzdsh_dlg->m_aPenScheme[KpShadowLight]))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!MoveToEx(hdc, LZDSH_TAB_EXT_X2-1, LZDSH_TAB_EXT_Y-1, NULL))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!LineTo(hdc, LZDSH_TAB_EXT_X2-1, LZDSH_TAB_EXT_Y+1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(!SelectObject(hdc, pen_norm)) // lzdsh_dlg->m_aPenScheme[KpShadowNorm]))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!MoveToEx(hdc, LZDSH_TAB_EXT_X2-2, LZDSH_TAB_EXT_Y, NULL))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!LineTo(hdc, LZDSH_TAB_EXT_X2-2, LZDSH_TAB_EXT_Y+1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

      if(pen_light) if(!DeleteObject(pen_light))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      pen_light = NULL;
      if(pen_dark) if(!DeleteObject(pen_dark))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      pen_dark = NULL;
      if(pen_norm) if(!DeleteObject(pen_norm))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      pen_norm = NULL;
      if(pen_black) if(!DeleteObject(pen_black))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      pen_black = NULL;
#endif
#endif

// ------------------------
//    if(hdc!=NULL) ReleaseDC(hwnd, hdc);
//    hdc=NULL;
      if(SUCCEEDED(retc)) EndPaint(ms_window, &ps);

// ------------------------
// #ifdef IBSH_RES_MODE_RTF
//    if(SUCCEEDED(retc)) if(!SetActiveWindow(lzdsh_dlg->m_ResRichEdit))
//    {
// #  ifdef Debug
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// #  endif
//    }

//    if(SUCCEEDED(retc)) PostMessage(lzdsh_dlg->m_ResRichEdit, uMsg, wParam, lParam);
// #endif

      break;


// #if IBSH_SKIN != IBSH_SKIN_STANDART
   case WM_TIMER:
      if(SUCCEEDED(retc))
      {
#ifdef LZDSHT_DISPLAY_SINGLE_THREAD
#ifndef LZDSHT_DISPLAY_SEARCH_THREAD
//       LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;
#endif
#endif

         if(retp == lzdsh_dlg->m_RedrawTimer)
         {
//          if(lzdsh_dlg->m_iDiagOnTopCnt++ > 1000 / KP_REDRAW_TIMEOUT)
            if(--lzdsh_dlg->m_iDiagOnTopCnt == 0) // m_iDiagOnTopCnt nustato LzdShSearch::DisplayResult()
            {                                      // jei per anksti – BringToTop() nenusistato
// jei pasibaigë uþdelsimo skaitiklis, keliam langà virð visø langø
               if(lzdsh_dlg->m_bDiagOnTop && lzdsh_dlg->m_hDialogWindow && SUCCEEDED(retc))
               {
//                lzdsh_dlg->m_iDiagOnTopCnt = 0;

                  retc = lzdsh_dlg->BringToTop(lzdsh_dlg->m_bDiagOnTop);
// PutLogMessage_("WM_TIMER: %d", lzdsh_dlg->m_bDiagOnTop);
               }

// selectinam postponintà m_DictBox
// atidëjimas nepadeda
//             if(SUCCEEDED(retc)) retc = SetComboBoxSel(lzdsh_dlg->m_DictBox, lzdsh_dlg->m_iCurDictEntry); // nustatom postponintà þodynà
// PutLogMessage_("WM_TIMER: m_iCurDictEntry: %d", lzdsh_dlg->m_iCurDictEntry);
            }
            if(lzdsh_dlg->m_iDiagOnTopCnt <= 0) lzdsh_dlg->m_iDiagOnTopCnt = (-1); // daugiau nebenustatinësim, kad LzdShSearch::DisplayResult() nebeatpaþintø

#ifdef LZDSHT_DISPLAY_SINGLE_THREAD
#ifndef LZDSHT_DISPLAY_SEARCH_THREAD
            if(lzdsh_dlg->m_bNewContentReady && (lzdsh_search_unsafe != NULL) && SUCCEEDED(retc))
            {
               lzdsh_dlg->m_bNewContentReady = False;
//             if(lzdsh_dlg->m_ResHtml) lzdsh_dlg->m_ResHtml->HTML((const char *)lzdsh_search_unsafe->m_lpszResultFormatted);
               retc = lzdsh_search_unsafe->DisplayResult();
            }
#endif
#endif
            if(SUCCEEDED(retc)) retc = lzdsh_dlg->RedrawWindow(); // sunaikindavo m_ResHtml
         }
#ifdef IBSH_RES_MODE_XGECKO
#  if FALSE
         else if(retp == KP_POLL_TIMER)
         {
KP_TRACE_1("LzdShDialogProc(): KP_POLL_TIMER: SetFocus(%lx)", lzdsh_dlg->m_LastFocus);
            if(lzdsh_dlg->m_LastFocus && SUCCEEDED(retc)) SetFocus(lzdsh_dlg->m_LastFocus);
            lzdsh_dlg->m_LastFocus = NULL;
            KillTimer(lzdsh_dlg->m_hDialogWindow, KP_POLL_TIMER);
         }
#  endif
#endif
         else retb = DefWindowProc(ms_window, msg, wParam, lParam);
      }
      break;
// #endif


// ---------------------------------------
#if FALSE // m_InpEdit skirtas pranesimas iki cia neateina
   case WM_CHAR:
      if(SUCCEEDED(retc))
         if(lzdsh_dlg->m_CurList == lzdsh_dlg->m_MainList)
            lzdsh_dlg->m_bKbdInput = True;
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;
#endif

#ifdef Debug
//    case WM_PASTE:
// KP_TRACE("LzdShDialogProc WM_PASTE"); //  neateina // èia dël komandos Paste á ávedimo laukà - ið tikrøjø LzdShDialogProc WM_COMMAND.EN_CHANGE
//       break;
#endif


// ---------------------------------------
// tab control
#if IBSH_SKIN == IBSH_SKIN_STANDART
   case WM_NOTIFY:
// KpMsgOut("WM_NOTIFY", IDI_ASTERISK, KP_MB_TESTI);
//    switch(HIWORD(wParam))
//    switch(HIWORD(msg.wParam))
      {
//    case TCN_SELCHANGING:
//MsgOut("TCN_SELCHANGING", IDI_ASTERISK, KP_MB_TESTI);
//       break;
//    case TCN_SELCHANGE:
//MsgOut("TCN_SELCHANGE", IDI_ASTERISK, KP_MB_TESTI);
         if(SUCCEEDED(retc)) switch(TabCtrl_GetCurSel(lzdsh_dlg->m_TabCtrl))
#else
// ---------------------------------------
   case WM_COMMAND:
      switch(retp)
#endif
      {
         case LZDSH_ID_MAIN_TAB:
            if(SUCCEEDED(retc))
            {
               ShowWindow(lzdsh_dlg->m_SearchList, SW_HIDE);
               ShowWindow(lzdsh_dlg->m_HistList, SW_HIDE);
               ShowWindow(lzdsh_dlg->m_MainList, SW_SHOW);
               lzdsh_dlg->m_CurList = lzdsh_dlg->m_MainList;
            }

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
            if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabSearch, BM_SETCHECK, BST_UNCHECKED, KP_WND_RIGHT_TAB);
            if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabHist, BM_SETCHECK, BST_UNCHECKED, KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB);
#endif

//          if(SUCCEEDED(retc))
//          {
// //          LZDSH_SEARCH_PTR_INIT;
// KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;
//             if(lzdsh_search_unsafe != NULL) lzdsh_search_unsafe->m_lCurEntryId = (-1L);
//          }
//          if(SUCCEEDED(retc)) retc=GetCurWindow(&cur_wnd, lzdsh_dlg->m_CurList);
//          if((cur_wnd==NULL) && SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//          if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0) retc = lzdsh_dlg->GetCurListSel(lzdsh_dlg->m_CurList, LZDSH_HIST_NONE);

            if(SUCCEEDED(retc)) retc = lzdsh_dlg->GetCurListSel(LZDSH_HIST_NONE);
            break;

         case LZDSH_ID_SEARCH_TAB:
            if(SUCCEEDED(retc))
            {
               ShowWindow(lzdsh_dlg->m_MainList, SW_HIDE);
               ShowWindow(lzdsh_dlg->m_HistList, SW_HIDE);
               ShowWindow(lzdsh_dlg->m_SearchList, SW_SHOW);
               lzdsh_dlg->m_CurList = lzdsh_dlg->m_SearchList;
            }

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
            if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabMain, BM_SETCHECK, BST_UNCHECKED, KP_WND_LEFT_TAB);
            if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabHist, BM_SETCHECK, BST_UNCHECKED, KP_WND_RIGHT_TAB);
#endif
//          if(SUCCEEDED(retc))
//          {
// //          LZDSH_SEARCH_PTR_INIT;
// KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;
//             if(lzdsh_search_unsafe != NULL) lzdsh_search_unsafe->m_lCurEntryId = (-1L);
//          }
//          if(SUCCEEDED(retc)) retc=GetCurWindow(&cur_wnd, lzdsh_dlg->m_CurList);
//          if((cur_wnd == NULL) && SUCCEEDED(retc))
//             retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//          if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0) retc = lzdsh_dlg->GetCurListSel(lzdsh_dlg->m_CurList, LZDSH_HIST_NONE);

            if(SUCCEEDED(retc)) retc = lzdsh_dlg->GetCurListSel(LZDSH_HIST_NONE);
            break;

         case LZDSH_ID_HIST_TAB:
            if(SUCCEEDED(retc))
            {
               ShowWindow(lzdsh_dlg->m_MainList, SW_HIDE);
               ShowWindow(lzdsh_dlg->m_SearchList, SW_HIDE);
               ShowWindow(lzdsh_dlg->m_HistList, SW_SHOW);
               lzdsh_dlg->m_CurList = lzdsh_dlg->m_HistList;
            }

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
            if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabMain, BM_SETCHECK, BST_UNCHECKED, KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB);
            if(SUCCEEDED(retc)) SendMessage(lzdsh_dlg->m_TabSearch, BM_SETCHECK, BST_UNCHECKED, KP_WND_LEFT_TAB);
#endif
//          if(SUCCEEDED(retc))
//          {
// //          LZDSH_SEARCH_PTR_INIT;
// KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;
//             if(lzdsh_search_unsafe != NULL) lzdsh_search_unsafe->m_lCurEntryId = (-1L);
//          }
//          if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, lzdsh_dlg->m_CurList);
//          if((cur_wnd==NULL) && SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//          if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0) retc=lzdsh_dlg->GetCurListSel(lzdsh_dlg->m_CurList, LZDSH_HIST_NONE);

            if(SUCCEEDED(retc)) retc = lzdsh_dlg->GetCurListSel(LZDSH_HIST_NONE);
            break;

#if IBSH_SKIN == IBSH_SKIN_STANDART
         }
//       break;

      } // switch(retp)
      break;

// ---------------------------------------
   case WM_COMMAND:
      switch(retp)
      {
#endif

// -----------------
      case LZDSH_ID_SEARCH:
// KpMsgOut("LZDSH_ID_SEARCH", IDI_ASTERISK, KP_MB_TESTI);
#ifdef LZDSHT_SEARCH_SINGLE_THREAD
         if(SUCCEEDED(retc))
         {
HCURSOR cur_sav = NULL;
            cur_sav = ::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
            if(cur_sav == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            if((lzdsh_dlg->m_hCurSav == NULL) && cur_sav && SUCCEEDED(retc)) lzdsh_dlg->m_hCurSav = cur_sav;

            lzdsh_dlg->m_bButSearchPressed = True;
         }
#else
         if(SUCCEEDED(retc))
         {
//    LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;

            if(lzdsh_search_unsafe != NULL) retc = lzdsh_search_unsafe->ProcSearch();
         }
#endif
         break;

//-----------------
      case LZDSH_ID_FONT_ZOOM:
         if(iCurFontSize!=30)
         {
            iCurFontSize=30;
#if IBSH_SKIN == IBSH_SKIN_STANDART
            icon=LoadIcon(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_ZOOM_SEL_ICON));
#endif
            for(ii=0; ii<LZDSH_NUM_OF_PAR_STYLES; ii++)
               lpszaParStyInlineCmds[ii]=lpszLzdshParStyBig;
         }
         else
         {
            iCurFontSize = 22;
#if IBSH_SKIN == IBSH_SKIN_STANDART
            icon=LoadIcon(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_ZOOM_ICON));
#endif
            for(ii = 0; ii < LZDSH_NUM_OF_PAR_STYLES; ii++)
               lpszaParStyInlineCmds[ii] = lpszLzdshParStySmall;
         }

#if IBSH_SKIN == IBSH_SKIN_STANDART
         if((icon == NULL) && SUCCEEDED(retc))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            SendMessage(lzdsh_dlg->m_ButFontZoom, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
#endif
         if(SUCCEEDED(retc))
         {
//          LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;
            if(lzdsh_search_unsafe != NULL)
            {
               lzdsh_search_unsafe->m_lCurEntryId = -1L;
//             if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->SearchForEntry();
//             if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->DisplayResult();
            }
         }
         break;

//-----------------
      case LZDSH_ID_NARROW:
         if(SUCCEEDED(retc))
         {
//          LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;

            if(lzdsh_search_unsafe != NULL)
            {
               if(lzdsh_search_unsafe->m_iLevel != SimplyLevel)
               {
                  lzdsh_search_unsafe->m_iLevel = SimplyLevel;
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  icon=LoadIcon(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_WIDE_ICON));
#endif
               }
               else
               {
                  lzdsh_search_unsafe->m_iLevel = BigLevel;
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  icon = LoadIcon(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_WIDE_SEL_ICON));
#endif
               }
            }

#if IBSH_SKIN == IBSH_SKIN_STANDART
            if((icon == NULL) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               SendMessage(lzdsh_dlg->m_ButNarrow, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
#endif
            if(SUCCEEDED(retc)) if(lzdsh_search_unsafe != NULL)
            {
               if(SUCCEEDED(retc)) lzdsh_search_unsafe->m_lCurEntryId = -1L;
//             if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->SearchForEntry();
//             if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->DisplayResult();
            }

         } // if(SUCCEEDED(retc))

         break;

//-----------------
      case LZDSH_ID_ACCENTS:
         if(SUCCEEDED(retc))
         {
//          LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;

            if(lzdsh_search_unsafe != NULL)
            {
               lzdsh_search_unsafe->m_bAccFl = (!lzdsh_search_unsafe->m_bAccFl);

#if IBSH_SKIN == IBSH_SKIN_STANDART
               if(SUCCEEDED(retc))
               {
                  if(lzdsh_search_unsafe->m_bAccFl)
                     icon = LoadIcon(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_ACC_SEL_ICON));
                  else
                     icon = LoadIcon(hKpInstance, MAKEINTRESOURCE(LZDSH_IDI_ACC_ICON));
               }
               KP_ASSERT(icon != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

               if(SUCCEEDED(retc))
                  SendMessage(lzdsh_dlg->m_ButAcc, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
#endif
               if(SUCCEEDED(retc)) lzdsh_search_unsafe->m_lCurEntryId = -1L;
//             if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->SearchForEntry();
//             if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->DisplayResult();
            }
         }
         break;

//-----------------
#ifdef IBSH_RES_MODE_XGECKO
      case LZDSH_ID_BACK:
// KP_TRACE("LzdShDialogProc(): LZDSH_ID_BACK");

#  if TRUE // #  ifdef TEST_GECKO_BACK_FORWARD
KpWnd *cur_wnd;
int ii;
int ll;
unsigned char text_buf[KP_MAX_FILE_LIN_WDT + 1]; // [TV_XL_MAX_IX_LEN + 1];

         KP_ASSERT(lzdsh_dlg->m_HistList, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(lzdsh_dlg->m_pResCtrl, KP_E_SYSTEM_ERROR, null, True);

         cur_wnd = NULL;
         if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, lzdsh_dlg->m_HistList);
         KP_ASSERT(cur_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);

         if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel >= 0)
         {
            ll = 0;
            if(SUCCEEDED(retc))
            {
               ll = SendMessage(lzdsh_dlg->m_HistList, LB_GETCOUNT, 0, 0);
               KP_ASSERT(ll != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);
            }

// KP_TRACE_1("LzdShDialogProc(): LZDSH_ID_BACK: num. of items:%d", ll);

            ii = (-1);
            if(SUCCEEDED(retc))
            {
               ii = SendMessage(lzdsh_dlg->m_HistList, LB_GETCURSEL, 0, 0L);
               KP_ASSERT(ii != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);
            }

            KP_ASSERT((ii >= 0) && (ii < ll), KP_E_SYSTEM_ERROR, null, True);

// KP_TRACE_1("LzdShDialogProc(): LZDSH_ID_BACK: cur. sel.:%d", ii);

            if(SUCCEEDED(retc))
            {
               ii--;
               if(ii < 0) ii = 0;
            }

            if(SendMessage(lzdsh_dlg->m_HistList, LB_SETCURSEL, ii, ii)==LB_ERR) // lParam reikia KpListBox
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#     if FALSE
            if(SUCCEEDED(retc))
            {
               ll = SendMessage(lzdsh_dlg->m_HistList, KP_LB_GETTEXTLEN, (WPARAM)ii, 0L); // not implemented !!!!
               if(ll == LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               else if(ll>=KP_MAX_FILE_LIN_WDT)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            }
#     endif
            if(SUCCEEDED(retc))
               if(SendMessage(lzdsh_dlg->m_HistList, KP_LB_GETTEXT, ii, (LPARAM)text_buf)==LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// KP_TRACE("LzdShDialogProc(): LZDSH_ID_BACK: SetToSearchStr()");

            if(SUCCEEDED(retc))
            {
//             LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;

               if(lzdsh_search_unsafe != NULL)
               {
                  if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->SetToSearchStr(text_buf, LZDSH_HIST_FORCED_NONE);
                  if(SUCCEEDED(retc)) retc = lzdsh_dlg->SetEditControlText(text_buf /* (const unsigned char *)lzdsh_search_unsafe->m_lpszToSearch */);
                  if(SUCCEEDED(retc)) lzdsh_search_unsafe->m_lCurEntryId = (-1L);
               }
            }

         } // if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0)
#  else
         if(SUCCEEDED(retc)) lzdsh_dlg->m_pResCtrl.goBack();
#  endif
         break;
#endif

#ifdef IBSH_RES_MODE_XGECKO
      case LZDSH_ID_FORWARD:
// KP_TRACE("LzdShDialogProc(): LZDSH_ID_FORWARD");

#  if TRUE // #  ifdef TEST_GECKO_BACK_FORWARD
// KpWnd *cur_wnd;
// int ii;
// int ll;
// unsigned char text_buf[KP_MAX_FILE_LIN_WDT+1]; // [TV_XL_MAX_IX_LEN+1];

         KP_ASSERT(lzdsh_dlg->m_HistList, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(lzdsh_dlg->m_pResCtrl, KP_E_SYSTEM_ERROR, null, True);

         cur_wnd=NULL;
         if(SUCCEEDED(retc)) retc=GetCurWindow(&cur_wnd, lzdsh_dlg->m_HistList);
         if((cur_wnd==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0)
         {
            ll = 0;
            if(SUCCEEDED(retc))
            {
               ll = SendMessage(lzdsh_dlg->m_HistList, LB_GETCOUNT, 0, 0);
               if(ll==LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

// KP_TRACE_1("LzdShDialogProc(): LZDSH_ID_FORWARD: num. of items:%d", ll);

            ii = (-1);
            if(SUCCEEDED(retc))
            {
               ii = SendMessage(lzdsh_dlg->m_HistList, LB_GETCURSEL, 0, 0L);
               if(ii==LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

            if(((ii<0) || (ii>=ll)) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// KP_TRACE_1("LzdShDialogProc(): LZDSH_ID_FORWARD: cur. sel.:%d", ii);

            if(SUCCEEDED(retc)) if(ii<ll-1) ii++;

            if(SendMessage(lzdsh_dlg->m_HistList, LB_SETCURSEL, ii, ii)==LB_ERR) // lParam reikia KpListBox
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#     if FALSE
            if(SUCCEEDED(retc))
            {
               ll = SendMessage(lzdsh_dlg->m_HistList, KP_LB_GETTEXTLEN, (WPARAM)ii, 0L); // not implemented !!!!
               if(ll == LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               else if(ll>=KP_MAX_FILE_LIN_WDT)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            }
#     endif
            if(SUCCEEDED(retc))
               if(SendMessage(lzdsh_dlg->m_HistList, KP_LB_GETTEXT, ii, (LPARAM)text_buf)==LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// KP_TRACE("LzdShDialogProc(): LZDSH_ID_FORWARD: SetToSearchStr()");
            if(SUCCEEDED(retc))
            {
//             LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search_unsafe = lzdsh_dlg->m_pKpFileSys;

               if(lzdsh_search_unsafe != NULL)
               {
                  if(SUCCEEDED(retc)) retc = lzdsh_search_unsafe->SetToSearchStr(text_buf, LZDSH_HIST_FORCED_NONE);
                  if(SUCCEEDED(retc)) retc = lzdsh_dlg->SetEditControlText(text_buf /* (const unsigned char *)lzdsh_search_unsafe->m_lpszToSearch */);
                  if(SUCCEEDED(retc)) lzdsh_search_unsafe->m_lCurEntryId = (-1L);
               }
            }

         } // if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0)
#  else
         lzdsh_dlg->m_pResCtrl->goForward();
#  endif

         break;
#endif

//-----------------
      case IDOK:
         break;

      case IDCANCEL:
         endfl=True;
         break;

      case KP_ID_MINIMIZE:
         if(!CloseWindow(ms_window))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
         }
         break;

      case KP_ID_EXIT:
// KpMsgOut("ID_EXIT");
         PostQuitMessage(IDOK);
         endfl=True;
         break;

      case KP_ID_OPEN_CMD:
// KpMsgOut("ID_OPEN");
         break;

// -----------------
      case KP_ID_OPTIONS:
         KP_ASSERT(pHelpDialog, KP_E_SYSTEM_ERROR, True, null);
         if(SUCCEEDED(retc)) if(theHelpDialog.m_bWindowOpen)
            DestroyWindow(theHelpDialog.m_hDialogWindow);

         KP_ASSERT(pOptDialog, KP_E_SYSTEM_ERROR, True, null);
// KpMsgOut("ID_OPTIONS");
         if(SUCCEEDED(retc)) if(!theOptDialog.m_bWindowOpen)
         {
            theOptDialog.m_bWindowOpen = True;
            if(SUCCEEDED(retc)) retc = theOptDialog.OpenWindow(hKpInstance);
//          if(SUCCEEDED(retc)) retc = theOptDialog.DoEdit();
         }
         break;

// -----------------
      case KP_ID_HELP:

         KP_ASSERT(pOptDialog, KP_E_SYSTEM_ERROR, True, null);
         if(SUCCEEDED(retc)) if(theOptDialog.m_bWindowOpen)
            DestroyWindow(theOptDialog.m_hDialogWindow);

         KP_ASSERT(pHelpDialog, KP_E_SYSTEM_ERROR, True, null);
         if(SUCCEEDED(retc)) if(!theHelpDialog.m_bWindowOpen)
         {
            theHelpDialog.m_bWindowOpen = True;
            if(SUCCEEDED(retc)) retc = theHelpDialog.OpenWindow(hKpInstance);
         }
         break;

#if FALSE // #ifdef Debug //
         default:
{
stringstream str_stream;
str_stream << "LzdShDialogProc: WM_COMMAND LOWORD(wParam): " << LOWORD(wParam);
KP_TRACE(KpString(str_stream.str()));
}
            break;
#endif
      } // switch(retp)

      if(!endfl)
         switch(HIWORD(wParam))
         {
         case LBN_SELCHANGE:
//       case CBN_SELCHANGE:
// KP_TRACE_2("LzdShDialogProc(): LBN_SELCHANGE hwndDlg:%lx m_HistList:%lx", hwndDlg, lzdsh_dlg->m_HistList);

            if(SUCCEEDED(retc))
            {

//          LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = lzdsh_dlg->m_pKpFileSys;
            if(lzdsh_search == NULL) break;

#if FALSE // #ifdef KP_LISTBOX
            list_ctrl = (HWND)NULL;
            sub_list_ctrl = (HWND)lParam;

            if(SUCCEEDED(retc)) if(list_ctrl==NULL)
            {
               if(FAILED(GetCurWindow(&cur_wnd, lzdsh_dlg->m_MainList))) cur_wnd=NULL;
               if(cur_wnd != NULL)
                  if(cur_wnd->m_hSubListBox==sub_list_ctrl) list_ctrl=cur_wnd->m_hWndHandle;
            }

            if(SUCCEEDED(retc)) if(list_ctrl==NULL)
            {
               if(FAILED(GetCurWindow(&cur_wnd, lzdsh_dlg->m_SearchList))) cur_wnd=NULL;
               if(cur_wnd!=NULL)
                  if(cur_wnd->m_hSubListBox==sub_list_ctrl) list_ctrl=cur_wnd->m_hWndHandle;
            }

            if(SUCCEEDED(retc)) if(list_ctrl==NULL)
            {
               if(FAILED(GetCurWindow(&cur_wnd, lzdsh_dlg->m_HistList))) cur_wnd=NULL;
               if(cur_wnd!=NULL)
                  if(cur_wnd->m_hSubListBox==sub_list_ctrl) list_ctrl=cur_wnd->m_hWndHandle;
            }
#else
            list_ctrl=(HWND)lParam;
#endif

#ifdef IBSH_RES_MODE_XGECKO
#  if FALSE
KpWnd *cur_wnd;
HWND cur_hwnd;
            cur_wnd = NULL;
            if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, (HWND)lParam);
            cur_hwnd = NULL;
            if(cur_wnd && SUCCEEDED(retc)) cur_hwnd = cur_wnd->m_hSubListBox;

            if(SUCCEEDED(retc)) lzdsh_dlg->m_LastFocus = cur_hwnd; // list_ctrl;
KP_TRACE_1("LzdShDialogProc(): LBN_SELCHANGE: lzdsh_dlg->m_LastFocus:%lx", lzdsh_dlg->m_LastFocus);
#  endif
#endif

// -------------------------
#ifdef IBSH_RES_MODE_XGECKO
// KP_TRACE_2("LzdShDialogProc: LBN_SELCHANGE: m_HistList:%lx lParam:%lx", lzdsh_dlg->m_HistList, lParam);
// KP_TRACE_2("LzdShDialogProc: LBN_SELCHANGE: m_HistList:%lx list_ctrl:%lx", lzdsh_dlg->m_HistList, list_ctrl);
            if(SUCCEEDED(retc)) if(list_ctrl != lzdsh_dlg->m_HistList)
               strcpy((unsigned char *)lzdsh_dlg->m_lpszSelDictName, (const unsigned char *)lzdsh_dlg->m_lpszCurDictName);
#endif

// -------------------------------- pagrindiniu zodziu sarasu selektinimas
            if(SUCCEEDED(retc)) if(lzdsh_search != NULL)
               if(
                  (list_ctrl == lzdsh_dlg->m_MainList) ||
                  (list_ctrl == lzdsh_dlg->m_SearchList) ||
                  (list_ctrl == lzdsh_dlg->m_HistList)
                 )
               {
                  retc = lzdsh_dlg->GetCurListSel(/* list_ctrl, */
                     (lzdsh_search->m_iToHistListFlags == LZDSH_HIST_NONE)?
                     LZDSH_HIST_DEPENDENT|LZDSH_HIST_TIMER: // LZDSH_HIST_IMMEDIATELY
                     lzdsh_search->m_iToHistListFlags);
#if FALSE // #ifdef Debug
static int ii = 0;
char str_buf[100];
sprintf(str_buf, "LzdShDialogProc: LBN_SELCHANGE [%d]", ii++);
KP_TRACE(str_buf);
#endif

//                if((list_ctrl == lzdsh_dlg->m_HistList) && SUCCEEDED(retc))
//                {
//                   strncpy((unsigned char *)lzdsh_search->m_lpszPrevHistWord,
//                         (const unsigned char *)lzdsh_search->m_lpszToSearch, KP_MAX_FILE_LIN_WDT);
//                   lzdsh_search->m_lpszPrevHistWord[KP_MAX_FILE_LIN_WDT]=Nul;
//                }

// --------------------------
// uzkomentavau, galvodamas, kad pades search rezultatu listo slankiojimo stabciojimui
//                /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->BlockSemaphore();

#if FALSE // nustato GetCurListSel() --> SetToSearchStr()
KP_TRACE("LzdShDialogProc: LBN_SELCHANGE: to m_lpszToHistStr");
                  if((list_ctrl != lzdsh_dlg->m_HistList) && SUCCEEDED(retc))
                  {
                     lzdsh_search->m_lpszToHistStr[KP_MAX_FILE_LIN_WDT]=Nul;
                     strncpy((unsigned char *)lzdsh_search->m_lpszToHistStr,
                           (const unsigned char *)lzdsh_search->m_lpszToSearch, KP_MAX_FILE_LIN_WDT);
                     lzdsh_search->m_lpszToHistStr[KP_MAX_FILE_LIN_WDT]=Nul;
                  }
#endif
                  if((list_ctrl != lzdsh_dlg->m_SearchList) && SUCCEEDED(retc))
                     retc = lzdsh_dlg->SetEditControlText((const unsigned char *)lzdsh_search->m_lpszToSearch);

// uzkomentavau, galvodamas, kad pades search rezultatu listo slankiojimo stabciojimui
//                /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();
// --------------

#ifdef Debug
// unsigned char str_buf[100];
// sprintf((char *)str_buf, "LBN_SELCHANGE: %d", ii);
// KP_TRACE(str_buf);
#endif
               }


// ------------------------------ mazgu saraso selektinimas
#ifdef LZDSH_EDITOR_BUILD
// const static KpChar null_str[2] = {C_NBSP /* C_QemSpc */ /* C_NullSpc */, C_Nul};
int cur_sel /* = -1 */;
int ll;

            if(SUCCEEDED(retc)) if(list_ctrl == lzdsh_dlg->m_NodList)
            {
               if(((lzdsh_dlg->m_NodList == NULL) || (lzdsh_dlg->m_TagList == NULL)) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// ---------------------- anksciau redaguoto tago teksto istraukimas is lzdsh_dlg->m_TagEditCtrl
// ----------------------     ir issaugojimas einamajame lizde
// jei necapturinam, scrollbaras nepajaucia, kad pele jau atleista, pradeda vaziuot listo selektinimas
//    (SaveTagBeingEdited() -> WM_LZDSH_SET_TAG_HEADINGS_CURRENT -> RefreshCurNodeHeads() iskviecia
//    SetTagHeadings() ir popup rtf langelis pasigauna pele)
               if(SUCCEEDED(retc)) SetCapture(list_ctrl);

               if(SUCCEEDED(retc)) retc = lzdsh_dlg->SaveTagBeingEdited(True, True);
               if(SUCCEEDED(retc)) if(!ReleaseCapture())
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

// jei neatnaujinam - peles capturinimas numusa scrollbaro perpiesinejima
// anksciau atnaujinimas buvo iskvieciamas per SaveTagBeingEdited() -> WM_LZDSH_SET_TAG_HEADINGS_CURRENT ->
//    RefreshCurNodeHeads(), bet tada dar peles capturinimas buna dar nepaleistas
               if(!InvalidateRect(list_ctrl, 0, TRUE))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

// ---------------------
               ll = 0;
               if(SUCCEEDED(retc))
               {
                  ll = SendMessage(lzdsh_dlg->m_NodList, LB_GETCOUNT, 0, 0);
                  if(ll==LB_ERR)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }

               cur_sel = -1;
               if(SUCCEEDED(retc))
               {
                  cur_sel = SendMessage(lzdsh_dlg->m_NodList, LB_GETCURSEL, 0, 0);
                  if(cur_sel==LB_ERR)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  if(((cur_sel<0) || (cur_sel >= ll)) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               }
#  ifdef Debug
if(SUCCEEDED(retc))
{
char str_buf[100];
static int sel_cnt = 0;
sprintf(str_buf, "LBN_SELCHANGE: %d %d", cur_sel, sel_cnt++);
KP_TRACE(str_buf);
}
#  endif
               cur_wnd=NULL;
               if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, list_ctrl);
               if((cur_wnd==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

//             tag_list_wnd=NULL;
//             if(SUCCEEDED(retc)) retc = GetCurWindow(&tag_list_wnd, lzdsh_dlg->m_TagList);
//             if((tag_list_wnd==NULL) && SUCCEEDED(retc))
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

XmlNode *cur_entry = NULL;
XmlNode *cur_node = NULL;

               cur_entry = NULL;
               if(SUCCEEDED(retc)) cur_entry = (XmlNode *)cur_wnd->m_pEntries;
               if((cur_entry==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               cur_node = NULL;
               ii = cur_sel;
               if(SUCCEEDED(retc)) retc = cur_entry->GetEntryPtr(&ii, (KpTreeEntry **)&cur_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_entry);
               if((cur_node==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#  if FALSE // #ifdef Debug
if(SUCCEEDED(retc))
{
KpChar cur_tag;
char str_buf[100];
if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
sprintf(str_buf, "LBN_SELCHANGE: m_NodList cur_tag: %d", cur_tag);
KP_TRACE(str_buf);
}
#  endif
//             /* if(SUCCEEDED(retc)) */ if(lzdsh_search != NULL) /* retc = */ lzdsh_search->BlockSemaphore();

//             if(SUCCEEDED(retc)) retc = cur_entry->InitNodeStatus();
//             if(SUCCEEDED(retc)) retc = cur_entry->SetTagHeadings();

//             /* if(SUCCEEDED(retc)) */ if(lzdsh_search != NULL) /* retc = */ lzdsh_search->ReleaseSemaphore();

#  if FALSE
               if(SUCCEEDED(retc)) if(lzdsh_search != NULL) if(lzdsh_search->m_pCurNode)
               {
                  if(SUCCEEDED(retc))
                     if(SendMessage(lzdsh_dlg->m_TagList, LB_RESETCONTENT, NULL, NULL) == CB_ERR)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc))
                  {
                     retv = SendMessage(lzdsh_dlg->m_TagList, LB_INITSTORAGE, LZDSH_MAX_NUM_OF_EDIT_TAGS,
                        LZDSH_MAX_NUM_OF_EDIT_TAGS*LZDSH_MAX_EDIT_TAG_WDT);
                     if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
                     if((retv==LB_ERR) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
                  }
               }

               if(SUCCEEDED(retc)) if(lzdsh_search != NULL) lzdsh_search->m_pCurNode = cur_node;

               if(SUCCEEDED(retc))
               {
                  retv = SendMessage(lzdsh_dlg->m_TagList, KP_LB_SETSTRINGLIST, 0, (LPARAM)cur_node);
                  switch(retv)
                  {
                  case CB_ERR:
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                     break;
                  case CB_ERRSPACE:
                     retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
                     break;
                  }
               }
#  else
               if(SUCCEEDED(retc)) if(lzdsh_search != NULL) if(lzdsh_search->m_pCurNode != cur_node)
                  retc = SetListBoxSel(lzdsh_dlg->m_TagList, 0);
               if(SUCCEEDED(retc)) if(lzdsh_search != NULL) lzdsh_search->m_pCurNode = cur_node;
               if(SUCCEEDED(retc)) retc=ResetListBoxContents(lzdsh_dlg->m_TagList, LZDSH_MAX_NUM_OF_EDIT_TAGS, LZDSH_MAX_EDIT_TAG_WDT, True, cur_node);
#  endif

//------------------------------------ RTF teksto paveiksliuku testavimas
#  if FALSE // #  ifdef Debug

XmlNode *sub_node;
XmlNode *sub_node_prev_br;
XmlNode *first_child;

#     if FALSE // #ifdef Debug
KpChar cur_tag = C_Nul;
char str_buf[100];
if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
sprintf(str_buf, "LzdShL: LBN_SELCHANGE: cur_tag: %d", cur_tag);
KP_TRACE(str_buf);
#     endif
               first_child = NULL;
               sub_node = NULL;

// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//             if((cur_node != NULL) && SUCCEEDED(retc)) retc = cur_node->GetFirstChild((KpTreeEntry **)&first_child);
               if((cur_node != NULL) && SUCCEEDED(retc)) first_child = (XmlNode *)cur_node->m_pFirstChild;

               if((first_child != NULL) && SUCCEEDED(retc))
                  KP_NEWO(sub_node, XmlNode(first_child, NULL, 0, cur_node));

               sub_node_prev_br = NULL;
               KP_NEW(sub_node_prev_br, XmlNode((KpChar)XC_Text, NULL, null_str, (const unsigned char *)"", NULL));

               if(SUCCEEDED(retc)) retc = sub_node_prev_br->ConnectBrother(sub_node);
#     if FALSE // #ifdef Debug
if(SUCCEEDED(retc)) retc = sub_node->GetNodeTag(&cur_tag);
sprintf(str_buf, "LzdShL: LBN_SELCHANGE: sub_node->cur_tag: %d", cur_tag);
KP_TRACE(str_buf);
#     endif
               if(SUCCEEDED(retc)) sub_node = sub_node_prev_br;
#     if FALSE // #ifdef Debug
if(SUCCEEDED(retc)) retc = sub_node->GetNodeTag(&cur_tag);
sprintf(str_buf, "LzdShL: LBN_SELCHANGE: sub_node_prev_br->cur_tag: %d", cur_tag);
KP_TRACE(str_buf);
#     endif
               if(SUCCEEDED(retc)) if(lzdsh_dlg->m_ResRichTest != NULL) if(lzdsh_search != NULL)
               {
// atsimenam praejusi teksta
static unsigned char ctrl_txt[LZDSHT_RESULT_BUF_LEN+1] = {Nul};
static unsigned char prev_rtf_txt[LZDSHT_RESULT_BUF_LEN+1] = {Nul};
static unsigned char prev_ctrl_txt[LZDSHT_RESULT_BUF_LEN+1] = {Nul};

// -------------
                  /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->BlockSemaphore();

                  if(SUCCEEDED(retc)) strcpy(prev_rtf_txt, lzdsh_search->m_lpszTestRtfText);
                  if(SUCCEEDED(retc))
                  {
                     retv = SendMessage(lzdsh_dlg->m_ResRichTest, KP_WM_GETTEXT,
                              (WPARAM)LZDSHT_RESULT_BUF_LEN, (LPARAM)prev_ctrl_txt);
                     if((!retv) && SUCCEEDED(retc))
                     {
                        prev_ctrl_txt[0] = Nul;
#     ifdef Debug
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
                     }
                  }

// isvedam RTF
                  KP_ASSERT(lzdsh_search->m_lpRtfTestOutFileObj != NULL, E_POINTER, null, True);

                  if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->Reset();

#     if FALSE
                  if(sub_node && SUCCEEDED(retc)) retc = sub_node->WriteNode(lzdsh_search->m_lpRtfTestOutFileObj);
#     else
                  if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->WriteHeader(ColorTable, KpGmaxcc0);

//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->PutKwrd(RT_TG_sl, -60); // "\\sl-60"
//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->PutCharProc(C_Lf, True);
//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->PutKwrd(RT_TG_sl, -260); // LZDSH_STY_LINE_SPACING_SMALL_CMD

                  if(sub_node && SUCCEEDED(retc))
                     retc=sub_node->WriteRtf(lzdsh_search->m_lpRtfTestOutFileObj, (KpChar)XC_Dict,
                        (KpChar)XC_FirstDictTag, (KpChar)XC_Nul, LZDSH_NUM_OF_PAR_STYLES, lzdsh_search->m_lpRtfTestOutFileObj->GetFldDepth());
                  if(SUCCEEDED(retc)) retc=lzdsh_search->m_lpRtfTestOutFileObj->WriteTail();
#     endif

#     if FALSE
                  if(SUCCEEDED(retc)) retc=lzdsh_search->DisplayRtfTestResult();
#     else
                  if(SUCCEEDED(retc))
                  {
                     retv = SendMessage(lzdsh_dlg->m_ResRichTest, WM_SETTEXT,
                           NULL, (LPARAM)lzdsh_search->m_lpszTestRtfText);
                     KP_ASSERT(retv != CB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), False);
                     KP_ASSERT(/* (retv != FALSE) && */ (retv != LB_ERRSPACE) && (retv != CB_ERRSPACE), KP_E_OUTOFMEM, GetLastError(), False);
#        ifdef Debug
                     KP_ASSERT(retv, KP_E_OUTOFMEM, GetLastError(), False);
#        endif
                  }
#     endif

// laukiam, kol tekstas atsiras
#     if FALSE
                  if(SUCCEEDED(retc)) KpSleep(100, HWND_DESKTOP);
#     else
int ii = 0;
                  ii = 0;
                  if(SUCCEEDED(retc)) if(strcmp(prev_rtf_txt, lzdsh_search->m_lpszTestRtfText)) do
                  {
                     if(SUCCEEDED(retc)) KpSleep(3, HWND_DESKTOP);
//                   if(SUCCEEDED(retc)) Sleep(3);

                     if(SUCCEEDED(retc))
                        retv = SendMessage(lzdsh_dlg->m_ResRichTest, KP_WM_GETTEXT,
                              (WPARAM)LZDSHT_RESULT_BUF_LEN, (LPARAM)ctrl_txt);
#        ifdef Debug
                     if((!retv) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#        endif
                     ii++;

                  } while(
                           (ii<100) &&
                           (!strcmp(ctrl_txt, prev_ctrl_txt /* lzdsh_search->m_lpszTestRtfText */)) &&
                           SUCCEEDED(retc)
                         );
#        if FALSE // #        ifdef Debug
char str_buf[100];
sprintf(str_buf, "-------------------------- LzdShL: WM_GETTEXT: %d", ii);
KP_TRACE(str_buf);
KP_TRACE(ctrl_txt);
KP_TRACE(prev_ctrl_txt);
#        endif

#     endif

//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->Reset();
////              if(SUCCEEDED(retc)) memset(lzdsh_search->m_lpszTestRtfText, Nul, LZDSHT_RESULT_BUF_LEN);


               /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->ReleaseSemaphore();
// --------------

// bandom grabint paveiksliuka

HDC hdc = 0;
HDC hdc_mem = 0;
HBITMAP new_bmp = 0;
HBITMAP old_bmp = 0;
KpTextBmp *value = NULL;

                  hdc = 0;
                  if(SUCCEEDED(retc))
                  {
                     hdc = GetDC(lzdsh_dlg->m_ResRichTest);
//                   hdc = GetDC(HWND_DESKTOP);
//                   hdc = GetDC(lzdsh_dlg->m_hDialogWindow);
                     if(hdc == NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                  }

                  hdc_mem = 0;
                  if(SUCCEEDED(retc))
                  {
                     hdc_mem = CreateCompatibleDC(hdc);
                     if(hdc_mem == 0)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                  }

//                if(SUCCEEDED(retc))
//                   if(!BitBlt(hdc_mem,
//                         0, 0, 100, 20,
//                         hdc, 0, 0, SRCCOPY))
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

// static short empty_bmp_data[20 * 100] = {0};
                  new_bmp = 0;
                  if(hdc_mem && SUCCEEDED(retc))
                  {
//                   new_bmp = CreateBitmap(100, 20, 1, 16, empty_bmp_data);
                     new_bmp = CreateCompatibleBitmap(hdc, 100, 20);
//                   new_bmp = CreateCompatibleBitmap(hdc_mem, 100, 20);
                     if(new_bmp == 0)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                  }

//                if(SUCCEEDED(retc))
//                   if(!BitBlt(lpdis->hDC,
//                         trck_pos+lpdis->rcItem.left, lpdis->rcItem.top,
//                         lpdis->rcItem.right - lpdis->rcItem.left,
//                         lpdis->rcItem.bottom - lpdis->rcItem.top,
//                         hdc_mem, 0, 0, SRCCOPY))
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

                  value = NULL;
                  if(SUCCEEDED(retc))
                  {
                     value = (KpTextBmp *)cur_node->GetValue();
                     KP_ASSERT(value != NULL, KP_E_SYSTEM_ERROR, null, False);
                     if(value != NULL) KP_ASSERT(cur_node->GetValSize() >= sizeof(KpTextBmp), KP_E_SYSTEM_ERROR, null, True);
                  }

                  old_bmp = 0;
                  if(hdc_mem && new_bmp && SUCCEEDED(retc))
                  {
//                   old_bmp = (HBITMAP)SelectObject(hdc_mem, value->m_hBmp);
                     old_bmp = (HBITMAP)SelectObject(hdc_mem, new_bmp);
                     if(old_bmp == 0)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                  }

                  if(hdc_mem && hdc && SUCCEEDED(retc))
                     if(!BitBlt(hdc_mem,
                           0, 0, 100, 20,
//                         hdc, 0, 0, SRCCOPY))
                           hdc, 5, 5, SRCCOPY))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

                  if(hdc_mem && old_bmp && SUCCEEDED(retc))
                     if(SelectObject(hdc_mem, old_bmp) == 0)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

//                if(SUCCEEDED(retc))
//                   if(SelectObject(hdc, old_prev_bmp) == 0)
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

// static int cnt = 2;
                  if((value != NULL) && SUCCEEDED(retc))
                  {
//                   if(cnt==0)
                     {
// !!!!                 if(value->m_hBmp) if(!DeleteObject(value->m_hBmp))
//                         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

                        value->m_hBmp = new_bmp; // old_bmp; // prev_bmp; //

//                      if(!BitBlt(hdc,
//                            50, 50, 100, 20,
//                            hdc_mem, 0, 0, SRCCOPY))
//                         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                     }
//                   else cnt--;
                  }

//                if(hdc_mem && old_bmp && SUCCEEDED(retc))
//                   if(SelectObject(hdc_mem, old_bmp) == 0)
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

#     if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "LzdShL: LBN_SELCHANGE: %ld %ld", GetCurrentProcessId(), GetCurrentThreadId());
KP_TRACE(str_buf);
#     endif

#     if FALSE
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/gdi/bitmaps_5a5h.asp

hdc = CreateDC("DISPLAY", NULL, NULL, NULL);
hdc_mem = CreateCompatibleDC(hdc);

new_bmp = CreateCompatibleBitmap(hdc,
                     GetDeviceCaps(hdc, HORZRES),
                     GetDeviceCaps(hdc, VERTRES));

if (!SelectObject(hdc_mem, new_bmp))

        if (!BitBlt(hdc_mem,
               0,0,
               bmp.bmWidth, bmp.bmHeight,
               hdc,
               0,0,
               SRCCOPY))
#     endif
               } // if(SUCCEEDED(retc)) if(lzdsh_dlg->m_ResRichTest != NULL) if(lzdsh_search != NULL)

               KP_DELETE(sub_node);

#  endif // #if FALSE // #  ifdef Debug
//------------------------------------

            } // if(SUCCEEDED(retc)) if(list_ctrl == lzdsh_dlg->m_NodList)


// ------------------------------------- tagu saraso selektinimas
            if(SUCCEEDED(retc)) if(list_ctrl == lzdsh_dlg->m_TagList)
            {
               if((lzdsh_dlg->m_TagList==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               ll = 0;
               if(SUCCEEDED(retc))
               {
                  ll = SendMessage(lzdsh_dlg->m_TagList, LB_GETCOUNT, 0, 0);
                  if(ll==LB_ERR)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }

               cur_sel = -1;
               if(SUCCEEDED(retc))
               {
                  cur_sel = SendMessage(lzdsh_dlg->m_TagList, LB_GETCURSEL, 0, 0);
                  if(cur_sel==LB_ERR)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  if(((cur_sel<0) || (cur_sel>=ll)) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               }

KpWnd *cur_wnd = NULL;
               if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, list_ctrl);
               if((cur_wnd==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

XmlNode *cur_node = NULL;
//             if((cur_wnd==NULL) && SUCCEEDED(retc))
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc)) cur_node = (XmlNode *)cur_wnd->m_pEntries;
               if((cur_node==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// ---------------------- anksciau redaguoto teksto istraukimas is lzdsh_dlg->m_TagEditCtrl
// ----------------------     ir issaugojimas einamajame lizde
// zr. komentarus auksciau, prie if(list_ctrl == lzdsh_dlg->m_NodList)
               if(SUCCEEDED(retc)) SetCapture(list_ctrl);
               if(SUCCEEDED(retc)) retc = lzdsh_dlg->SaveTagBeingEdited(True, True);
               if(SUCCEEDED(retc)) if(!ReleaseCapture())
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               if(!InvalidateRect(list_ctrl, 0, TRUE))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);


#  if FALSE // #  ifdef Debug
//--------------- RTF teksto paveiksliuku testavimas
XmlNode *cur_gr_node = NULL;
XmlNode *cur_node = NULL;
XmlNode *sub_node;
XmlNode *cur_node_father;
XmlNode *sub_node_father;
XmlNode *sub_node_prev_br;
KpChar cur_tag = C_Nul;

               cur_wnd=NULL;
               if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, list_ctrl);
               if((cur_wnd==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               cur_gr_node = NULL;
               if(SUCCEEDED(retc)) cur_gr_node = (XmlNode *)cur_wnd->m_pEntries;
               if((cur_gr_node==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               cur_node = NULL;
               if(SUCCEEDED(retc)) retc = cur_gr_node->GetEntryPtr(&cur_sel, (KpTreeEntry **)&cur_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_gr_node);
               if((cur_node==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               sub_node = NULL;
               if(cur_node && SUCCEEDED(retc))
                  KP_NEWO(sub_node, XmlNode(cur_node, NULL, 0, cur_node));

               if(SUCCEEDED(retc)) retc = cur_node->GetNodeTag(&cur_tag);
#     if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "LzdShL: LBN_SELCHANGE: cur_tag: %d", cur_tag);
KP_TRACE(str_buf);
#     endif
               if((cur_tag == XC_Text) && SUCCEEDED(retc))
               {
                  retc = cur_node->GetFather((KpTreeEntry **)&cur_node_father);
                  if(cur_node_father && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc = cur_node_father->GetNodeTag(&cur_tag);
                     sub_node_father = NULL;
                     if(SUCCEEDED(retc)) KP_NEW(sub_node_father, XmlNode((KpChar)cur_tag, NULL, NULL, (const unsigned char *)"", NULL));

                     if(SUCCEEDED(retc)) retc = sub_node_father->ConnectChild(sub_node);
                     if(SUCCEEDED(retc)) sub_node = sub_node_father;
                  }
               }

               sub_node_prev_br = NULL;
               if(SUCCEEDED(retc)) KP_NEW(sub_node_prev_br, XmlNode((KpChar)XC_Text, NULL, null_str, (const unsigned char *)"", NULL));

               if(SUCCEEDED(retc)) retc = sub_node_prev_br->ConnectBrother(sub_node);
               if(SUCCEEDED(retc)) sub_node = sub_node_prev_br;

               if(SUCCEEDED(retc)) if(lzdsh_dlg->m_ResRichTest != NULL) if(lzdsh_search != NULL)
               {
                  KP_ASSERT(lzdsh_search->m_lpRtfTestOutFileObj != NULL, E_POINTER, null, True);

// -----------------
               /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->BlockSemaphore();

                  if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->Reset();

#     if FALSE
                  if(sub_node && SUCCEEDED(retc)) retc = sub_node->WriteNode(lzdsh_search->m_lpRtfTestOutFileObj);
#     else
                  if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->WriteHeader(ColorTable, KpGmaxcc0);

//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->PutKwrd(RT_TG_sl, -60); // "\\sl-60"
//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->PutCharProc(C_Lf, True);
//                if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->PutKwrd(RT_TG_sl, -260); // LZDSH_STY_LINE_SPACING_SMALL_CMD

                  if(sub_node && SUCCEEDED(retc))
                     retc = sub_node->WriteRtf(lzdsh_search->m_lpRtfTestOutFileObj, (KpChar)XC_Dict,
                        (KpChar)XC_FirstDictTag, (KpChar)XC_Nul, LZDSH_NUM_OF_PAR_STYLES, lzdsh_search->m_lpRtfTestOutFileObj->GetFldDepth());
                  if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->WriteTail();
#     endif

                  if(SUCCEEDED(retc)) retc = lzdsh_search->DisplayRtfTestResult();

                  if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpRtfTestOutFileObj->Reset();
                  if(SUCCEEDED(retc)) memset(lzdsh_search->m_lpszTestRtfText, Nul, LZDSHT_RESULT_BUF_LEN);

               /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL)  */ /* retc = */ lzdsh_search->ReleaseSemaphore();
// ----------------
               } // if(SUCCEEDED(retc)) if(lzdsh_dlg->m_ResRichTest != NULL) if(lzdsh_search != NULL)

               KP_DELETE(sub_node);

#  endif // #if FALSE // #  ifdef Debug

//------------------------------------ get tag properties
XmlNode *cur_tag_node = NULL;
int ii;        ii = cur_sel;
               lzdsh_dlg->m_iCurEditSel = cur_sel;
               if((cur_node==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc)) retc = cur_node->GetEntryPtr(&ii, (KpTreeEntry **)&cur_tag_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_node);
               if((cur_tag_node==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

bool do_edit = False;
KpChar cur_tag = (KpChar)XC_Nul;
KpChar tag_tmp = (KpChar)XC_Nul;
XmlNode *first_child = NULL;
XmlNode *next_brother = NULL;
XmlNode *father = NULL;
               if(SUCCEEDED(retc)) retc = cur_tag_node->GetNodeTag(&tag_tmp);
               if(SUCCEEDED(retc))
               {
                  if(tag_tmp == XC_Text)
                  {
                     retc = cur_tag_node->GetFather((KpTreeEntry **)&father);
                     if(SUCCEEDED(retc))
                     {
                        if(father == NULL)
                           /* retc= */KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                        else
                        {
                           do_edit = True;
                           retc = father->GetNodeTag(&cur_tag);
                        }
                     }
                  }
                  else
                  {
                     cur_tag = tag_tmp;
// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//                   retc = cur_tag_node->GetFirstChild((KpTreeEntry **)&first_child);
                     first_child = (XmlNode *)cur_tag_node->m_pFirstChild;
                     if(first_child && SUCCEEDED(retc))
                     {
                        retc = first_child->GetNextBrother((KpTreeEntry **)&next_brother);
                        if((next_brother == NULL) && SUCCEEDED(retc))
                        {
                           retc = first_child->GetNodeTag(&tag_tmp);
                           if(tag_tmp == XC_Text)
                           {
                              do_edit = True;
                              cur_tag_node = first_child;
                           }
                        }
                     }
                  }
               }

//------------------------------------ get font attributes
KPS_FontStyles fstn = KPS_NoStyle;
int flags = 0;
int typeface = 0;
int rtf_ctbl = DEFAULT_CHARSET;
unsigned char *font_name = NULL;
int font_size = 22;
KpColor color = KpBlack;
RGB_Color rgb_color = RGB_Black;

               if(do_edit && SUCCEEDED(retc))
               {
                  if(((cur_tag<XM_FirstTagCode) || (cur_tag>=XC_LastDictTag)) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                  {
                     fstn = iaTagFonts[cur_tag - XM_FirstTagCode];
                     if((fstn<0) || (fstn >= KPS_NumOfFontStyles00))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  }
                  if(SUCCEEDED(retc)) flags = aFontStyles[fstn].GetFontFlags();
                  if(SUCCEEDED(retc))
                  {
                     typeface = aFontStyles[fstn].GetTypeface();
                     if((typeface<0) || (typeface>=KPT_NumOfTypefaces0))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  }
                  if(SUCCEEDED(retc)) retc=iaRtfFonts[typeface].GetRtfCodeTable(&rtf_ctbl);

                  if(SUCCEEDED(retc)) retc=iaRtfFonts[typeface].GetFontName(&font_name);
//                if(SUCCEEDED(retc))
//                {
//                   strncpy(lzdsh_dlg->m_TagEditFontName, font_name, LF_FACESIZE);
//                   lzdsh_dlg->m_TagEditFontName[LF_FACESIZE] = Nul;
//                }

                  if(SUCCEEDED(retc)) font_size=aFontStyles[fstn].GetFontSize();

                  if(SUCCEEDED(retc)) color = aFontStyles[fstn].GetColor();
                  if(SUCCEEDED(retc)) if((color<0) || (color>=KpGmaxcc0))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc)) rgb_color = ColorTable[color];

#  if FALSE // #ifdef Debug
char str_buf[100];
// sprintf(str_buf, "iCurFontSize: %d  aFontStyles[%d].GetFontSize(): %d", iCurFontSize, fstn, font_size);
// sprintf(str_buf, "font_name: \"%s\"", font_name);
rtf_ctbl = RUSSIAN_CHARSET;
sprintf(str_buf, "rtf_ctbl: %d", rtf_ctbl);
KP_TRACE(str_buf);
#  endif
               }

//------------------------------------ get tag text
               if(do_edit && SUCCEEDED(retc))
               {
KpChar *cont_ptr = NULL;
int cont_len = 0;
// unsigned char *cont_buf = NULL;
UniChar *cont_buf = NULL;
// int ctbl = TV_MAIN_SGM_CTBL;

//                if(((cur_tag<XM_FirstTagCode) || (cur_tag>=XC_LastDictTag)) && SUCCEEDED(retc))
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L, NULL);
//                if(SUCCEEDED(retc)) ctbl = iaSgmCodeTables[cur_tag - XM_FirstTagCode];

                  if(SUCCEEDED(retc))
                  {
                     retc = cur_tag_node->GetContentsPtr(&cont_ptr);
                     if((cont_ptr == NULL) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  }

                  if(SUCCEEDED(retc)) cont_len = TvKpStrLen(cont_ptr);
                  KP_NEWA(cont_buf, UniChar, cont_len + 1); // new UniChar[cont_len+100+1]; // new unsigned char[cont_len+1];

// if(SUCCEEDED(retc)) cont_buf[0] = 0;
// if(SUCCEEDED(retc)) strcpy(cont_buf, "{\\rtf1{");
// if(SUCCEEDED(retc)) wcscpy(cont_buf, L"{\\rtf1{");
//                if(SUCCEEDED(retc)) /* retc = !!!! */ KptStrDecode(cont_buf, cont_ptr, cont_len, ctbl);
// if(SUCCEEDED(retc)) /* retc = !!!! */ KptStrDecode(cont_buf+strlen(cont_buf), cont_ptr, cont_len, ctbl);
                  if(SUCCEEDED(retc))
                  {
                     retc = KptKpCharStrToUnicode(cont_buf, cont_ptr, True);
// retc = KptKpCharStrToUnicode(cont_buf+wcslen(cont_buf), cont_ptr, True);
                     if(FAILED(retc))
                     {
                        KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
                        retc = S_OK;
                     }
                  }

// --------------------------- kuriam RichEdit redagavimo lauka
RECT lb_rect = {0L, 0L, 0L, 0L};
               if(SUCCEEDED(retc))
                  if(SendMessage(lzdsh_dlg->m_TagList, LB_GETITEMRECT, (WPARAM)cur_sel, (LPARAM)&lb_rect) == LB_ERR)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#  if FALSE // #ifdef Debug
char str_buf[200];
sprintf(str_buf, "LB_GETITEMRECT: cur_sel: %d  left: %ld  top: %ld  right: %ld  bottom: %ld", cur_sel, lb_rect.left, lb_rect.top, lb_rect.right, lb_rect.bottom);
KP_TRACE(str_buf);
#  endif

                  if(SUCCEEDED(retc)) retc = KpCreateRichEditUni(hKpInstance,
                     lzdsh_dlg->m_hDialogWindow, // lzdsh_dlg->m_TagList,
                     &lzdsh_dlg->m_TagEditCtrl, cont_buf,
                     lb_rect.right-lb_rect.left,   // int iWdt
                     lb_rect.bottom-lb_rect.top,   // int iHeight  // /* 2*KPW_CTRL_BORDER_WDT+ */ iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]+3
                     LZDSH_WND_BORDER_WDT +        // int iPosX
                        LZDSH_TAGLIST_X_CREATE + KPW_CTRL_BORDER_WDT +
                        lb_rect.left,
                     LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + LZDSH_WND_DY_COR + // int iPosY
                        LZDSH_TAGLIST_Y_DYN_CREATE + KPW_CTRL_BORDER_WDT +
                        lb_rect.top,
                     KPW_CONTROL_STYLE_NORMAL, 0L, 0L,
                     font_name, font_size, flags, rgb_color,
                     &lzdsh_dlg->m_TagEditFontFmt);

// -------------
                  KP_DELETE(cont_buf);

               } // if(do_edit && SUCCEEDED(retc))

            } // if(SUCCEEDED(retc)) if(list_ctrl == lzdsh_dlg->m_TagList)

#endif // #ifdef LZDSH_EDITOR_BUILD


// ----------------- zodynu comboboxo selektinimas
            if(SUCCEEDED(retc)) if(list_ctrl == lzdsh_dlg->m_DictBox)
            {
// PutLogMessage_("LzdShDialogProc(): LBN_SELCHANGE");
               ii = SendMessage(lzdsh_dlg->m_DictBox, CB_GETCURSEL, 0, 0);
               KP_ASSERT(ii !=LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);
               KP_ASSERT((ii >= 0) && (ii < lzdsh_dlg->m_iNumOfDictEntries), KP_E_SYSTEM_ERROR, null, True);

// --------------------------
#ifdef Debug
// char str_buf[100];
// sprintf(str_buf, "LzdShDialogProc():LBN_SELCHANGE[%d][%d][%d]", iDictBoxStep, lzdsh_search->m_iSemBlocked, lzdsh_search->m_lSemBlockingThread);
// KP_TRACE(str_buf);
#define KP_TRACE_001(step) \
   sprintf(str_buf, "LzdShDialogProc():LBN_SELCHANGE[%d][%d]", iDictBoxStep, lzdsh_search->m_lThreadId); \
   KpSleep(1000, HWND_DESKTOP); \
   iDictBoxStep = step;

// KP_TRACE_001(1);
#else
#define KP_TRACE_001(step)
#endif
#ifdef Debug
iDictBoxStep = 1;
#endif

               if(SUCCEEDED(retc))
               {
                  /* retc = */ lzdsh_search->BlockSemaphore();

                  if(SUCCEEDED(retc))
                  {
                     retc = lzdsh_dlg->ChangeDict(ii, True);
                     if(retc == KP_E_OBJ_NOT_FOUND)
                        retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
                  }

// KP_TRACE_001(6);

//                if(SUCCEEDED(retc)) retc = lzdsh_dlg->SetEditControlText((const unsigned char *)"");
// KP_TRACE_001(7);
// KP_TRACE("LzdShDialogProc(): LBN_SELCHANGE: SetToSearchStr(\"\")");
//                if(SUCCEEDED(retc)) retc = lzdsh_search->SetToSearchStr((const unsigned char *)"", LZDSH_HIST_NONE);
// KP_TRACE_001(8);
                  if(SUCCEEDED(retc))
                  {
                     lzdsh_search->m_lpszCurSearchWord[0]=Nul;
                     lzdsh_search->m_lpszCurSearchKwd[0]=Nul;
//                   lzdsh_search->m_lCurEntryId=Maxlong;
                     lzdsh_search->m_lCurEntryId=-1L;
//                   retc = lzdsh_search->SearchForEntry(); // 2 ???? ar tikrai reikia, jei taip, tai nesuveiks - kitas WM_KP_REMOTE_CALL_DONE gavimo threadas
                  }
//                if(SUCCEEDED(retc)) retc = lzdsh_search->DisplayResult();
// KP_TRACE_001(9);
                  /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();
               }
// KP_TRACE_001(0);

// ------------------- ieskom m_InpEdit esancio þodþio naujai pasirinktam þodyne
               if(SUCCEEDED(retc))
                  if(/* (retp == lzdsh_dlg->m_InpEdit) && */ (lzdsh_dlg->m_CurList == lzdsh_dlg->m_MainList))
                     lzdsh_dlg->m_bKbdInput = True;
               if(SUCCEEDED(retc)) retc = lzdsh_dlg->ProcessInput(LZDSH_HIST_NONE);

            } // if(SUCCEEDED(retc)) if(list_ctrl == lzdsh_dlg->m_DictBox)

            } // if(SUCCEEDED(retc))

            break; // case LBN_SELCHANGE:


// ------------------
         case EN_CHANGE:   // èia dël Paste
#if FALSE // #ifdef Debug
{
stringstream str_stream;
str_stream << "LzdShDialogProc: EN_CHANGE: " << retp;
KP_TRACE(KpString(str_stream.str()));
}
#endif
            if(SUCCEEDED(retc))
               if(/* (retp == lzdsh_dlg->m_InpEdit) && */ (lzdsh_dlg->m_CurList == lzdsh_dlg->m_MainList))
                  lzdsh_dlg->m_bKbdInput = True;

            if(SUCCEEDED(retc)) retc = lzdsh_dlg->ProcessInput(LZDSH_HIST_DEPENDENT|LZDSH_HIST_TIMER);

            break;



#if FALSE // #ifdef Debug //
         default:
{
stringstream str_stream;
str_stream << "LzdShDialogProc: WM_COMMAND HIWORD(wParam): " << HIWORD(wParam);
KP_TRACE(KpString(str_stream.str()));
}
            break;
#endif
         } // switch(HIWORD(wParam))

//wParam
//    The low-order word is the list box identifier.
//    The high-order word is the notification message.
//lParam
//    Handle to the list box.

      break; // case WM_COMMAND:

   case WM_CLOSE:

      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_RedrawTimer)
      {
         if(!KillTimer
            (
#ifdef KP_USE_WXWIDGETS
                  (HWND)GetHWND(),
#else
                  lzdsh_dlg->m_hDialogWindow,
#endif
               lzdsh_dlg->m_RedrawTimer)
            )
            if(SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         lzdsh_dlg->m_RedrawTimer = 0;
      }

#ifndef KP_USE_WXWIDGETS
      if(SUCCEEDED(retc)) if(lzdsh_dlg->m_hDialogWindow!=NULL)
      {
//       if(!(::DestroyWindow(lzdsh_dlg->m_hDialogWindow)))
//          if(SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         lzdsh_dlg->m_hDialogWindow = NULL;
      }
#endif

      endfl=True;
      retb=DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
      case IDCANCEL: retc = KP_E_CANCEL; break;
      case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl=True;
      break;

#if FALSE // #ifdef Debug
   case WM_NCMOUSEMOVE:
   case WM_SETCURSOR:
   case WM_NCHITTEST:
      retb=DefWindowProc(ms_window, msg, wParam, lParam);
      break;
#endif

// ---------------------------------
#ifdef Debug
   case WM_KEYDOWN:
// KP_TRACE_3("LzdShDialogProc: WM_KEYDOWN %c %x %lx", wParam, wParam, lParam);
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   case WM_KEYUP:
// KP_TRACE_3("LzdShDialogProc: WM_KEYUP %c %x %lx", wParam, wParam, lParam);
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   case WM_CHAR:
// KP_TRACE_3("LzdShDialogProc: WM_CHAR %c %x %lx", wParam, wParam, lParam);
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   case WM_SYSKEYDOWN:
// KP_TRACE_3("LzdShDialogProc: WM_SYSKEYDOWN %c %x %lx", wParam, wParam, lParam);
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   case WM_SYSKEYUP:
// KP_TRACE_3("LzdShDialogProc: WM_SYSKEYUP %c %x %lx", wParam, wParam, lParam);
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   case WM_SYSCHAR:
// KP_TRACE_3("LzdShDialogProc: WM_SYSCHAR %c %x %lx", '?', wParam, lParam);
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;
#endif

#if FALSE // #ifdef Debug //
   case WM_SYSCOMMAND:
#  ifdef Debug
// char str_buf[100];
sprintf(str_buf, "LzdShDialogProc: WM_SYSCOMMAND %c %x %lx", '?', wParam, lParam);
KP_TRACE(str_buf);
#  endif
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;
#endif

#if FALSE // #ifdef Debug //
   case WM_SETCURSOR:
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;
#endif

   default:
#if FALSE // #ifdef Debug //
{
stringstream str_stream;
str_stream << "LzdShDialogProc: uMsg: " << uMsg;
KP_TRACE(KpString(str_stream.str()));
}
#endif
      retb = DefWindowProc(ms_window, msg, wParam, lParam);
      break;

   } // if(SUCCEEDED(retc)) switch(uMsg)

   if(SUCCEEDED(retc)) /* retb = */ /* iBshDialogProc */ KpPubDialogProc(hwndDlg, uMsg, wParam, lParam);

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, msg, wParam, lParam);
      retb = TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);
// if(endfl || FAILED(retc)) PostQuitMessage(RET_CODE_WIN(retc));

#ifndef KP_USE_WXWIDGETS
return(retb);
#endif
}


// ----------------------------------
HRESULT LzdShDlg::RestoreSavedCoords(void)
{
HRESULT retc=S_OK;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
long ll;
DWORD dwBufLen;
DWORD dwValType;
int win_dx, win_dy;
HKEY hKey=0;
LONG retw=ERROR_SUCCESS;
HDC hdc=NULL;

// --------------------------
   KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);

// -------------------------- restore window coordinates
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      hKey = NULL;

      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );
      if(RegOpenKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, KEY_QUERY_VALUE, &hKey)==ERROR_SUCCESS)
      {
         dwBufLen=sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndX", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen)==ERROR_SUCCESS)
         {
            if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc)) m_iWndCurX = ll;
         }

         dwBufLen=sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndY", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen)==ERROR_SUCCESS)
         {
            if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc)) m_iWndCurY=ll;
// KP_TRACE("m_iWndCurY=ll;");
         }

         dwBufLen=sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndDX", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen)==ERROR_SUCCESS)
         {
            if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               m_iWndCurDX=ll;
               m_iWndCurDXprec=m_iWndCurDX; // +1; // kad perpaisytu
            }
         }

         dwBufLen=sizeof(ll);
         if(SUCCEEDED(retc))
            if(RegQueryValueEx(hKey, "WndDY", NULL,
               &dwValType, (LPBYTE)&ll, &dwBufLen)==ERROR_SUCCESS)
         {
            if((dwValType!=REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               m_iWndCurDY=ll;
               m_iWndCurDYprec=m_iWndCurDY; // +1;
            }
         }

      } // if(RegOpenKeyEx(HKEY_CURRENT_USER, ...

      if(hKey)
      {
         retw=RegCloseKey(hKey);
         if(retw!=ERROR_SUCCESS)
            KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         hKey=0;
      }

   } // if(SUCCEEDED(retc))

// --------------
   if(SUCCEEDED(retc))
   {
      hdc=GetDC(HWND_DESKTOP);
      if(hdc==NULL)
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   }
   if((hdc!=NULL) && SUCCEEDED(retc))
   {
      win_dx=GetDeviceCaps(hdc, HORZRES);
      win_dy=GetDeviceCaps(hdc, VERTRES);

      if(
         ((m_iWndCurX+m_iWndCurDX)>=win_dx) || ((m_iWndCurY+m_iWndCurDY)>=win_dy) ||
         (m_iWndCurX<0) || (m_iWndCurY<0)
        )
      {
         m_iWndCurX=LZDSH_WND_X;
         m_iWndCurY=LZDSH_WND_Y;
// KP_TRACE("m_iWndCurY=LZDSH_WND_Y;");
         m_iWndCurDX=LZDSH_WND_DX;
         m_iWndCurDXprec=m_iWndCurDX; // +1;
         m_iWndCurDY=LZDSH_WND_DY;
         m_iWndCurDYprec=m_iWndCurDY; // +1;
      }
   }

   if(SUCCEEDED(retc)) retc = Resize();

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::SetEditControlText(const unsigned char *lpszInStr)
{
HRESULT retc=S_OK;
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *pntd = NULL;
int pos;

   if((lpszInStr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      strncpy(str_buf, lpszInStr, KP_MAX_FILE_LIN_WDT);
      str_buf[KP_MAX_FILE_LIN_WDT]=Nul;

// ---------
#ifdef IBSH_RES_MODE_XGECKO
// KP_TRACE_1("SetEditControlText: str_buf:%s", str_buf);
// KP_TRACE_1("SetEditControlText: lpszInStr:%s", lpszInStr);
      pntd = strchr(str_buf, TECH_DELIM_CHR); // 0xAD // C_hyph lentelëje 71
      if(pntd)
      {
         *pntd++ = Nul;
         if(strlen(pntd) >= TV_XL_MAX_TAG_WDT)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            strcpy((unsigned char *)m_lpszSelDictName, pntd);
      }
#endif

// ---------
      pos=strlen(str_buf)-1;
      while((pos>=0) && SUCCEEDED(retc))
      {
         if(str_buf[pos] == DOUBLE_ENTRIES_CHR) // '*'
            str_buf[pos--] = DOUBLE_ENTRIES_LZDSH_CHR; // 0xA0 // C_NBSP lentelëje 71
         else break;
      }

//    retc=KpSetRichCtrlText(m_InpEdit, str_buf, True);
      retc=KpSetCtrlText(m_InpEdit, str_buf);
   }

// ---------
#ifdef IBSH_RES_MODE_XGECKO
   if(SUCCEEDED(retc))
      if(strcmp((const unsigned char *)m_lpszSelDictName, (const unsigned char *)m_lpszCurDictName) != 0)
      {
         retc = ChangeDict((const unsigned char *)m_lpszSelDictName, True);
         if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_OBJ_NOT_FOUND))
            retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

return(retc);
}


// ----------------------------------
#ifdef LZDSH_EDITOR_BUILD
HRESULT LzdShDlg::SaveTagBeingEdited(bool bSetHeadings, bool bDestroyEditCtrl)
{
HRESULT retc=S_OK;
KpWnd *cur_wnd=NULL;
XmlNode *cur_node = NULL;
static UniChar uni_buf[KP_MAX_FILE_LIN_LEN+1];
KpChar *new_cont_ptr = NULL;

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

// ---------------------- anksciau redaguoto teksto istraukimas
   if(SUCCEEDED(retc)) if(m_TagEditCtrl)
   {
      if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, m_TagList);
      if((cur_wnd == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);


//    if((cur_wnd==NULL) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) cur_node = (XmlNode *)cur_wnd->m_pEntries;
      if((cur_node==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);


      if(SUCCEEDED(retc))
         if(m_TagEditCtrl->m_hMDI_Client == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         retc = KpGetWindowUniText(m_TagEditCtrl->m_hMDI_Client, uni_buf, KP_MAX_FILE_LIN_LEN);

      KP_NEWA(new_cont_ptr, KpChar, wcslen(uni_buf) + 1);

      if(SUCCEEDED(retc))
      {
         retc = KptUnicodeToKpCharStr(new_cont_ptr, uni_buf);
         if((retc == KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
         {
         /* retc= */KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
            retc = S_OK;
         }
      }
#ifdef Debug
static unsigned char txt_buf[KP_MAX_FILE_LIN_LEN+1];
                  if(SUCCEEDED(retc)) /* retc = */ KptUnicodeToStr(txt_buf, uni_buf, 80);
char str_buf[100];
sprintf(str_buf, "EM_GETTEXTEX: %c[%04x] %c[%04x] %c[%04x] %c[%04x] %c[%04x]",
uni_buf[0], uni_buf[0], uni_buf[1], uni_buf[1], uni_buf[2], uni_buf[2], uni_buf[3], uni_buf[3], uni_buf[4], uni_buf[4]);
KP_TRACE(str_buf);
KP_TRACE(txt_buf);
#endif


// ---------------------- anksciau redaguoto teksto issaugojimas irasu lizde
XmlNode *cur_tag_node = NULL;
int ii;
      ii = m_iCurEditSel;
      if(((ii <0) || (cur_node==NULL) || (cur_wnd==NULL)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc = cur_node->GetEntryPtr(&ii, (KpTreeEntry **)&cur_tag_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_node);
      if((cur_tag_node==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

KpChar tag_tmp = (KpChar)XC_Nul;
XmlNode *first_child = NULL;
XmlNode *next_brother = NULL;
KpChar *cont_ptr = NULL;
      if(SUCCEEDED(retc)) retc = cur_tag_node->GetNodeTag(&tag_tmp);
      if((tag_tmp != XC_Text) && SUCCEEDED(retc))
      {
// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//       retc = cur_tag_node->GetFirstChild((KpTreeEntry **)&first_child);
         first_child = (XmlNode *)cur_tag_node->m_pFirstChild;
         if((!first_child) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            retc = first_child->GetNextBrother((KpTreeEntry **)&next_brother);
         if(next_brother && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = first_child->GetNodeTag(&tag_tmp);
         if((tag_tmp != XC_Text) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) cur_tag_node = first_child;
      }

      if(SUCCEEDED(retc))
      {
         retc = cur_tag_node->GetContentsPtr(&cont_ptr);
         if((!cont_ptr) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
         if(
            TvKpStrCmp(cont_ptr, new_cont_ptr, True) ||
            (m_bTagEditChanged && bSetHeadings)
           )
      {
// ---------
      /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->BlockSemaphore();

#if FALSE // #ifdef Debug
KP_TRACE("TvKpStrCmp(cont_ptr, new_cont_ptr)");
unsigned char str_buf[200];
KptStrDecode(str_buf, cont_ptr, 80);
KP_TRACE(str_buf);
KptStrDecode(str_buf, new_cont_ptr, 80);
KP_TRACE(str_buf);
#endif
         if(SUCCEEDED(retc)) retc = cur_tag_node->SetContents(new_cont_ptr);
//       if(SUCCEEDED(retc)) retc = cur_node->SetTagHeadings(LZDSH_NUM_OF_PAR_STYLES, m_hDialogWindow);

      /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->ReleaseSemaphore();
// ----------------

// ---------------------- atnaujinam lizdo Tagu antrastes listams
         m_bTagEditChanged = True;

         if(bSetHeadings && SUCCEEDED(retc))
         {
// ----------------
         /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->BlockSemaphore();

            m_bTagEditChanged = False;

#if FALSE

XmlNode *father = NULL;
XmlNode *prev_brother = NULL;
            if((cur_node==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

if(SUCCEEDED(retc)) retc = cur_node->GetFather((KpTreeEntry **)&father);
if(SUCCEEDED(retc)) retc = cur_node->SetFather(NULL);

if(SUCCEEDED(retc)) retc = cur_node->GetPrevBrother((KpTreeEntry **)&prev_brother);
if(SUCCEEDED(retc)) retc = cur_node->SetPrevBrother(NULL);

            if(SUCCEEDED(retc)) retc = cur_node->SetTagHeadings(LZDSH_NUM_OF_PAR_STYLES, m_hDialogWindow);

if(SUCCEEDED(retc)) retc = cur_node->SetFather(father);
if(SUCCEEDED(retc)) retc = cur_node->SetPrevBrother(prev_brother);
#endif

#if FALSE
            if(SUCCEEDED(retc)) if(lzdsh_search->m_pCurEntry == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) retc = lzdsh_search->m_pCurEntry->SetTagHeadings(LZDSH_NUM_OF_PAR_STYLES, m_hDialogWindow);
#endif

//          if(SUCCEEDED(retc)) lzdsh_search->m_lCurEntryId = (-1L);

#if TRUE // #if FALSE
            KP_ASSERT(lzdsh_search->m_lThreadId != 0L, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc))
            {
//             if(!PostThreadMessage(lzdsh_search->m_lThreadId, WM_LZDSH_SET_TAG_HEADINGS_FULL, 0, GetCurrentThreadId()))
               if(!PostThreadMessage(lzdsh_search->m_lThreadId, WM_LZDSH_SET_TAG_HEADINGS_CURRENT, 0, GetCurrentThreadId()))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE("SaveTagBeingEdited: WM_LZDSH_SET_TAG_HEADINGS_CURRENT sent");
            }

         /* if(SUCCEEDED(retc)) */ /* if(lzdsh_search != NULL) */ /* retc = */ lzdsh_search->ReleaseSemaphore();
// ----------------

// laukiam atsakymo is theSearchThread apie atlikta darba
bool done;
MSG msg;
            done = False;
            if(SUCCEEDED(retc)) do
            {
               if(GetMessage(&msg, NULL, 0, 0)<0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

               if(SUCCEEDED(retc))
               {
                  TranslateMessage(&msg);

                  if(SUCCEEDED(retc)) switch(msg.message)
                  {
                  case WM_LZDSH_CURRENT_HEADINGS_SET:
                     done = True;
                     break;
                  default:
                     DispatchMessage(&msg);
                     break;
                  }
               }

            } while((!done) && SUCCEEDED(retc));

// KP_TRACE("SaveTagBeingEdited: WM_LZDSH_CURRENT_HEADINGS_SET received");
#else
            if(SUCCEEDED(retc)) lzdsh_search->m_bRefreshCurNodeHead = True;
#endif
         } // if(bSetHeadings && SUCCEEDED(retc))

         if(SUCCEEDED(retc)) lzdsh_search->m_bRefreshDisplay = True;

// --------------

      } // if(SUCCEEDED(retc)) if(TvKpStrCmp(cont_ptr, new_cont_ptr))

      cont_ptr = NULL;

      KP_DELETEA(new_cont_ptr);

      cur_tag_node = NULL;

// ---------------------- ankstesnio redagavimo lauko naikinimas
      if(bDestroyEditCtrl && SUCCEEDED(retc))
      {
//       if(SUCCEEDED(retc))
//          if(!DestroyWindow(m_TagEditCtrl))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);


KpWnd *tag_edit;
         tag_edit = m_TagEditCtrl;
         m_TagEditCtrl = NULL;

         if(SUCCEEDED(retc)) retc = DeleteWnd(tag_edit);

         KP_DELETE(tag_edit);
      }

   } // if(SUCCEEDED(retc)) if(m_TagEditCtrl)

return(retc);
}
#endif


// ----------------------------------
HRESULT LzdshAppendStrToList(HWND hwndListBox, const unsigned char *lpszInStr)
{
HRESULT retc = S_OK;
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
int pos;
LRESULT /* int */ retv;

   KP_ASSERT(hwndListBox != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszInStr != NULL, E_INVALIDARG, null, True);

   LZDSH_DLG_PTR_INIT;

   if(SUCCEEDED(retc))
   {
      strncpy(str_buf, lpszInStr, KP_MAX_FILE_LIN_WDT);
      str_buf[KP_MAX_FILE_LIN_WDT]=Nul;

      pos=strlen(str_buf)-1;
      while((pos >= 0) && SUCCEEDED(retc))
      {
         if(str_buf[pos] == DOUBLE_ENTRIES_CHR) // '*'
            str_buf[pos--] = DOUBLE_ENTRIES_LZDSH_CHR; // 0xA0 // C_NBSP lenteleje 71
         else break;
      }
   }

// m_HistList boxui persipildþius, iðmetam pirmà áraðà
   if(SUCCEEDED(retc)) if(hwndListBox == lzdsh_dlg->m_HistList)
   {
      retv = SendMessage(hwndListBox, LB_GETCOUNT, 0, 0L);
      KP_ASSERT(retv != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);

      if((retv >= LZDSH_MAX_NUM_OF_SEARCH_ITEMS - 1) && SUCCEEDED(retc))
      {
// kad nepersipildytø kpwindow.cpp eilutëje RRRRRRR, KpListBoxDialogProc() LB_ADDSTRING
// kol kas nemoku iðmest dalies
//       KP_ASSERT(SendMessage(hwndListBox, LB_DELETESTRING, 2, 0L) != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);
// metam visà listboxo turiná
         KP_ASSERT(SendMessage(hwndListBox, LB_RESETCONTENT, 0, 0L) != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);
         if(SUCCEEDED(retc))
         {
            retv = SendMessage(hwndListBox, LB_INITSTORAGE, LZDSH_MAX_NUM_OF_SEARCH_ITEMS,
                  LZDSH_MAX_NUM_OF_SEARCH_ITEMS*LZDSH_MAX_LIST_ITEM_WDT);
            KP_ASSERT(retv != LB_ERRSPACE, KP_E_OUTOFMEM, GetLastError(), True);
            KP_ASSERT(retv != LB_ERR, KP_E_ILLFUNC, GetLastError(), True);
         }

         lzdsh_dlg->m_iNumOfHistEntries = 0;
      }
   }

   if(SUCCEEDED(retc))
   {
      retv = SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)str_buf);
      if((retv == LB_ERR) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if((retv == LB_ERRSPACE) && SUCCEEDED(retc))
         retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


// ----------------------------------
#ifdef LZDSH_EDITOR_BUILD
HRESULT LzdShDlg::RefreshCurNodeHeads(void)
{
HRESULT retc=S_OK;
KpWnd *cur_wnd = NULL;
XmlNode *cur_node = NULL;
XmlNode *next_br = NULL;

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

// atnaujinam mazgo antrastes
   if((m_TagList == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, m_TagList);
   if((cur_wnd==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      cur_node = (XmlNode *)cur_wnd->m_pEntries;
      if((cur_node== NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
/* if(SUCCEEDED(retc)) */ if(lzdsh_search != NULL) /* retc = */ lzdsh_search->BlockSemaphore();

// nukerpam brolius
   if(SUCCEEDED(retc)) retc = cur_node->GetNextBrother((KpTreeEntry **)&next_br);
   if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(NULL);

   if(SUCCEEDED(retc)) retc = cur_node->SetTagHeadings(LZDSH_NUM_OF_PAR_STYLES, m_hDialogWindow);
// atstatom
   if(SUCCEEDED(retc)) retc = cur_node->SetNextBrother(next_br);

/* if(SUCCEEDED(retc)) */ if(lzdsh_search != NULL) /* retc = */ lzdsh_search->ReleaseSemaphore();

// refreshinam listboxus
#if FALSE // jau nereikia - refreshins sugrizus i LzdShDialogProc:LBN_SELCHANGE
   if(!InvalidateRect(m_NodList, 0, TRUE))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   if(!InvalidateRect(m_TagList, 0, TRUE))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif

// po refreshinimo nusimusa naujo redaguojamo langelio fokusas
#if FALSE // jau nebe, viskas kazkaip susitvarke
   if(m_TagEditCtrl && SUCCEEDED(retc))
   {
//    if(!::SetFocus(m_TagEditCtrl->m_hMDI_Client))
      if(!::SetFocus(m_TagEditCtrl->m_hWndHandle))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }
#endif

return(retc);
}
#endif


// ----------------------------------
// paliekam èia // #if FALSE // iðkelta á KpGeckoDialog
HRESULT LzdShDlg::Resize(void)
{
HRESULT retc = S_OK;
int wdt_sav, hgt_sav, numl_sav;
int ii;
LzdShDlg *lzdsh_dlg = this;

   wdt_sav = m_iWndCurDX;
   hgt_sav = m_iWndCurDY;
   numl_sav = m_iNumOfLines;

   if(m_iWndCurDXprec < LZDSH_WND_DX_MIN) m_iWndCurDXprec = LZDSH_WND_DX_MIN;
   if(m_iWndCurDXprec > LZDSH_WND_DX_MAX) m_iWndCurDXprec = LZDSH_WND_DX_MAX;
   if(m_iWndCurDYprec < LZDSH_WND_DY_MIN) m_iWndCurDYprec = LZDSH_WND_DY_MIN;
   if(m_iWndCurDYprec > LZDSH_WND_DY_MAX) m_iWndCurDYprec = LZDSH_WND_DY_MAX;

   ii = m_iWndCurDXprec - LZDSH_WND_DX_MIN;
   ii -= ii % LZDSH_GRID;
   ii += LZDSH_WND_DX_MIN;
   m_iWndCurDX = ii;

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "pries Resize %d %d", iWndCaptionHgt, iWndMenuHgt);
KP_TRACE(str_buf);
#endif

   m_iNumOfLines = (m_iWndCurDYprec - (LZDSH_WND_DY - LZDSH_LIST_DY)) /
      iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL];
   m_iWndCurDY = LZDSH_WND_DY_DYN;

   m_iNumOfLines = (m_iWndCurDY - (LZDSH_WND_DY - LZDSH_LIST_DY)) /
      iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL];
   m_iWndCurDY = LZDSH_WND_DY_DYN;

// PutLogMessage_("Resize() %d", m_iNumOfLines);

#if FALSE // #ifdef Debug
// char str_buf[100];
sprintf(str_buf, "po Resize %d %d", iWndCaptionHgt, iWndMenuHgt);
KP_TRACE(str_buf);
#endif

   if((wdt_sav != m_iWndCurDX) || (hgt_sav != m_iWndCurDY) ||
    (numl_sav != m_iNumOfLines)) m_iDoRedraw = 1; // m_bDoRedraw = True;

// cia langas vaziuodavo aukstyn, kai tik pele atsistodavai
// #if IBSH_SKIN == IBSH_SKIN_STANDART
//   m_iWndCurDXprec=m_iWndCurDX;
//   m_iWndCurDYprec=m_iWndCurDY;
// #endif

#if TRUE // #ifdef IBSH_RES_MODE_XGECKO
   retc = RefreshResCtrl();
#endif

return(retc);
}
// #endif // iðkelta á KpGeckoDialog


// ----------------------------------------
HRESULT LzdShDlg::CompleteDrag(void)
{
HRESULT retc = S_OK;

#if TRUE // #ifdef IBSH_RES_MODE_XGECKO
   retc = RefreshResCtrl();
#endif

return(retc);
}


// ----------------------------------------
HRESULT LzdShDlg::RedrawWindow(void)
{
HRESULT retc = S_OK;
LzdShDlg *lzdsh_dlg = this;

// -----------------------------
   KP_ASSERT(m_hDialogWindow, KP_E_SYSTEM_ERROR, null, False);
#ifdef IBSH_RES_MODE_XGECKO
#if Compiler != Watcom
// KP_ASSERT(m_pResCtrl, KP_E_SYSTEM_ERROR, null, True);
   if(m_pResCtrl)
#endif
#endif
   {
// --------------------------

#if FALSE
      if(SUCCEEDED(retc))
         if(!SetWindowPos(m_hDialogWindow, m_bDiagOnTop?HWND_TOPMOST:HWND_NOTOPMOST, // HWND_TOP,
            m_iWndCurX, m_iWndCurY,
            m_iWndCurDX, m_iWndCurDY,
            0))
         {
#  ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
         }
#endif

// ------------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
// KP_TRACE("WM_TIMER");
      if(!m_bResizing)
      {
// KP_TRACE("WM_TIMER not m_bResizing");
//       winpos_ptr = (WINDOWPOS *)lParam;
//       if(winpos_ptr)
         {
            if(
               (m_iWndCurDXprec!=m_iWndCurDX) ||
               (m_iWndCurDYprec!=m_iWndCurDY)
              )
            {
// KP_TRACE("WM_TIMER Resize");
               m_iWndCurDXprec=m_iWndCurDX;
               m_iWndCurDYprec=m_iWndCurDY;

               retc=Resize();
#else
      if(m_iDoRedraw)
      {
         {
            {
#endif
               if(SUCCEEDED(retc))
                  if(!SetWindowPos
                     (
#ifdef KP_USE_WXWIDGETS
                           (HWND)m_hDialogWindow->GetHWND(),
#else
                           m_hDialogWindow,
#endif
                        m_bDiagOnTop?HWND_TOPMOST:HWND_NOTOPMOST, // HWND_TOP,
                        m_iWndCurX, m_iWndCurY,
                        m_iWndCurDX, m_iWndCurDY,
                        0
                      )
                    )
                  {
#ifdef Debug
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                  }
            }
         }
      }
// PutLogMessage_("RedrawWindow(): %d %d", m_iDoRedraw, m_bDiagOnTop);

      if(m_iDoRedraw && SUCCEEDED(retc))
      {
// ---------------
#if IBSH_SKIN != IBSH_SKIN_STANDART
         if(!SetWindowPos(m_ButExit, HWND_TOP,
            LZDSH_BUT_EXIT_X, LZDSH_BUT_EXIT_Y,
            LZDSH_BUT_WDT, LZDSH_BUT_WDT,
            0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }

         if(!SetWindowPos(m_ButMinimize, HWND_TOP,
            LZDSH_BUT_MINIMIZE_X, LZDSH_BUT_MINIMIZE_Y,
            LZDSH_BUT_WDT, LZDSH_BUT_WDT,
            0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }
#endif

// ---------------
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "RedrawWindow() %d", m_iNumOfLines);
KP_TRACE(str_buf);
#endif

         if(!SetWindowPos(m_MainList, HWND_TOP,
            LZDSH_LIST_X_CREATE, LZDSH_LIST_Y_CREATE,
            LZDSH_LIST_DX_CREATE, LZDSH_LIST_DY_DYN_CREATE,
            0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }

         if(!SetWindowPos(m_SearchList, HWND_TOP,
            LZDSH_LIST_X_CREATE, LZDSH_LIST_Y_CREATE,
            LZDSH_LIST_DX_CREATE, LZDSH_LIST_DY_DYN_CREATE,
            0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }

         if(!SetWindowPos(m_HistList, HWND_TOP,
            LZDSH_LIST_X_CREATE, LZDSH_LIST_Y_CREATE,
            LZDSH_LIST_DX_CREATE, LZDSH_LIST_DY_DYN_CREATE,
            0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }

#ifdef LZDSH_EDITOR_BUILD
         if(!SetWindowPos(m_TagList, HWND_TOP,
            LZDSH_TAGLIST_X_CREATE, LZDSH_TAGLIST_Y_DYN_CREATE,
            LZDSH_TAGLIST_DX_DYN_CREATE, LZDSH_TAGLIST_DY_CREATE,
            0))
         {
#  ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
         }

#  ifndef KP_USE_WXWIDGETS
         if(!SetWindowPos(m_NodList, HWND_TOP,
            LZDSH_NODLIST_X_DYN_CREATE, LZDSH_NODLIST_Y_CREATE,
            LZDSH_NODLIST_DX_CREATE, LZDSH_NODLIST_DY_DYN_CREATE,
            0))
         {
#     ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
         }
#  endif
#endif

// ---------------------
#ifdef IBSH_RES_MODE_RTF
         if(!SetWindowPos(m_ResRichEdit, HWND_TOP,
            LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE,
            LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE,
            0))
         {
#  ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
         }
#endif

#ifdef LZDSH_EDITOR_BUILD
#if FALSE // #ifdef Debug
         if(!SetWindowPos(m_ResRichTest, HWND_TOP,
            LZDSH_RTF_TEST_X_DYN_CREATE, LZDSH_RTF_TEST_Y_DYN_CREATE,
            LZDSH_RTF_TEST_DX, LZDSH_RTF_TEST_DY,
            0))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }
#endif
#endif

// ---------------
#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
         if((m_ResHtml == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) if(!SetWindowPos(m_ResHtml->hwnd_, HWND_TOP,
            LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE,
            LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE,
            0))
         {
#     ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
         }

         if(SUCCEEDED(retc)) if(!InvalidateRect(m_ResHtml->hwnd_, 0, TRUE))
         {
#     ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
         }
#  endif // #  if Compiler != Watcom
#endif // #ifdef IBSH_RES_MODE_MSHTML


// ---------------------
#if FALSE // KP_XGECKO_VER == 124 // "1.2.4"
#ifdef IBSH_RES_MODE_XGECKO
#  if FALSE
         if(SUCCEEDED(retc))
            if(!SetWindowPos(m_pResCtrl->hWnd, HWND_TOP,
               LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE,
               LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE,
               0))
            {
#     ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
            }
#  endif

         if(SUCCEEDED(retc)) m_pResCtrl->setSize(LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE);

#endif // #ifdef IBSH_RES_MODE_XGECKO
#endif // #if KP_XGECKO_VER == 124 // "1.2.4"


// ----------------------------
#if FALSE // #ifdef IBSH_RES_MODE_MSHTML //
         if(SUCCEEDED(retc)) if(!InvalidateRect(m_ResHtml->hwnd_, 0, TRUE))
         {
#  ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
         }
#endif

// ---------------
         if(SUCCEEDED(retc))
            if(!InvalidateRect
               (
#  ifdef KP_USE_WXWIDGETS
                     (HWND)m_hDialogWindow->GetHWND(),
#  else
                     m_hDialogWindow,
#  endif
                  0, TRUE
               )
              )
            {
#  ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
            }

// ---------------------
#if TRUE // KP_XGECKO_VER == 130 // "1.3.0"
#ifdef IBSH_RES_MODE_XGECKO
#  if FALSE
         if(SUCCEEDED(retc))
            if(!SetWindowPos(m_pResCtrl->hWnd, HWND_TOP,
               LZDSH_RES_X_CREATE, LZDSH_RES_Y_CREATE,
               LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE,
               0))
            {
#     ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#     endif
            }
#  endif

         if(SUCCEEDED(retc)) m_pResCtrl->setSize(LZDSH_RES_DX_DYN_CREATE, LZDSH_RES_DY_DYN_CREATE);

#endif // #ifdef IBSH_RES_MODE_XGECKO
#endif // #if KP_XGECKO_VER == 130 // "1.3.0"

// ----------------------------
#if FALSE // #ifdef IBSH_RES_MODE_XGECKO
         if(SUCCEEDED(retc))
            if(!InvalidateRect(m_pResCtrl->m_hWnd, 0, TRUE))
            {
#  ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
            }
#endif // #ifdef IBSH_RES_MODE_XGECKO

// ----------------------------
         m_iDoRedraw = 0; // m_bDoRedraw = False;

      } // if(m_iDoRedraw && SUCCEEDED(retc))

// --------------------------
   } // if(m_pResCtrl)

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::RefreshResCtrl(void)
{
HRESULT retc=S_OK;

KP_TRACE("LzdShDlg::RefreshResCtrl()");

#ifdef IBSH_RES_MODE_XGECKO
   if(m_pResCtrl)
   {
// gecko langas netsiranda po maksimizavimo
//    if(!InvalidateRect(m_pResCtrl->m_hWnd, 0, TRUE))
//       KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());

// po LzdShOptDialogProc() ir kt. kaþko iðkvieèia 20 kartø, todël apsiribojam tik m_lCurEntryId nuresetinimu

//    if(!::RedrawWindow(m_pResCtrl->m_hWnd, NULL, NULL, RDW_UPDATENOW | RDW_ALLCHILDREN))
//       KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
   }
#endif

// RedrawWindow() padeda, bet nevisada
// kaþko pradëjo iðtrint lango turiná
// m_bNewContentReady = True; // ðito neuþtenka, m_pResBuf kaþkodël jau bûna iðvalytas, reikia formuot ið naujo
   if(m_pKpFileSys) m_pKpFileSys->m_lCurEntryId = (-1);

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::GetOnTop(bool *pbAlwaysOnTop)
{
HRESULT retc=S_OK;
static unsigned char publisher[KP_MAX_FNAME_LEN + 1];
int prod_ver = 0;
static unsigned char key_name[KP_MAX_FILE_LIN_WDT + 1];
HKEY hKey = NULL;
DWORD dwBufLen;
DWORD dwValType;
long ll = False;

   KP_ASSERT(pbAlwaysOnTop, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(theKpStAppPtr != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      *pbAlwaysOnTop = False;

      sprintf((char *)key_name, "Software\\%s\\%d", publisher, prod_ver);
      if(RegOpenKeyEx(HKEY_CURRENT_USER, (LPCTSTR)key_name, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
      {
         dwBufLen = sizeof(ll);
         if(RegQueryValueEx(hKey, "OnTop", NULL, &dwValType, (LPBYTE)&ll, &dwBufLen) == ERROR_SUCCESS)
         {
            if((dwValType != REG_DWORD) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc)) *pbAlwaysOnTop = (bool)ll;
         }
      }

      if(hKey)
      {
         RegCloseKey(hKey);
         hKey = NULL;
      }
   }

   if(SUCCEEDED(retc)) m_bDiagOnTop = (bool)ll; // *pbAlwaysOnTop;

// PutLogMessage_("GetOnTop(): %d", m_bDiagOnTop);

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::BringToTop(bool bAlwaysOnTop)
{
HRESULT retc = S_OK;

   m_bDiagOnTop = bAlwaysOnTop;

   KP_ASSERT(m_hDialogWindow, KP_E_SYSTEM_ERROR, null, True);
// PutLogMessage_("BringToTop(): %d", m_bDiagOnTop);
   KP_ASSERT(SetWindowPos(m_hDialogWindow, bAlwaysOnTop?HWND_TOPMOST:HWND_NOTOPMOST, 0, 0, 100, 100, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE),
               KP_E_SYSTEM_ERROR, null, True);

#if TRUE // #ifdef IBSH_RES_MODE_XGECKO
   if(SUCCEEDED(retc)) retc = RefreshResCtrl();
#endif

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::GetCurListSel(/* HWND hListCtrl, */ int iToHistListFlags)
{
HRESULT retc=S_OK;
int ii;
// int ll;
unsigned char text_buf[KP_MAX_FILE_LIN_WDT+1]; // [TV_XL_MAX_IX_LEN+1];
HWND hListCtrl = NULL;
KpWnd *cur_wnd = NULL;

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

#if FALSE // #ifdef Debug
if(SUCCEEDED(retc))
{
char str_buf[100];
sprintf(str_buf, "GetCurListSel pradzia: text_buf: %lx", text_buf);
KP_TRACE(str_buf);
}
#endif

   hListCtrl=m_CurList;
   if((hListCtrl==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc=GetCurWindow(&cur_wnd, hListCtrl);
   if((cur_wnd==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel>=0)
   {
#if FALSE
int ll = 0;
      if(SUCCEEDED(retc))
      {
         ll = SendMessage(hListCtrl, LB_GETCOUNT, 0, 0);
         if(ll==LB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
#endif

      if(SUCCEEDED(retc))
      {
         ii=SendMessage(hListCtrl, LB_GETCURSEL, 0, 0L);
         if(ii==LB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

//    if(((ii<0) || (ii>=LZDSH_LIST_NUM_LINES)) && SUCCEEDED(retc))
      if(((ii<0) || ((ii>=m_iNumOfListEntries) && (hListCtrl == m_MainList))) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#if FALSE
      if(SUCCEEDED(retc))
         if(strlen((const unsigned char *)m_lpszaListTexts[ii])>=KP_MAX_FILE_LIN_WDT)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) retc=SetInpStr((const unsigned char *)m_lpszaListTexts[ii]);
#else
#  if FALSE
      if(SUCCEEDED(retc))
      {
         ll = SendMessage(hListCtrl, KP_LB_GETTEXTLEN, (WPARAM)ii, 0L); // not implemented !!!!
         if(ll == LB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         else if(ll>=KP_MAX_FILE_LIN_WDT)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
      }
#  endif

      if(SUCCEEDED(retc))
         if(SendMessage(hListCtrl, KP_LB_GETTEXT, ii, (LPARAM)text_buf)==LB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// KP_TRACE_1("GetCurListSel: %s", text_buf);
// KP_TRACE_1("GetCurListSel: text_buf: %lx", text_buf);
#  if FALSE // #ifdef Debug
{
int ii;
char str_buf[100];
str_buf[0]=Nul;
for(ii=0; ii<strlen(text_buf); ii++) sprintf(str_buf+ii*2, "%02x", text_buf[ii]);
str_buf[ii*2]=Nul;
KP_TRACE(text_buf);
KP_TRACE(str_buf);
}
#  endif


#  if FALSE
      if(SUCCEEDED(retc))
         if(strlen(text_buf)>=KP_MAX_FILE_LIN_WDT) // nëra prasmës tikrinti - naudoti KP_LB_GETTEXTLEN
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
#  endif
// KP_TRACE("GetCurListSel: SetToSearchStr()");
      if(SUCCEEDED(retc)) retc = lzdsh_search->SetToSearchStr(text_buf, iToHistListFlags);
#endif
      if(SUCCEEDED(retc)) lzdsh_search->m_lCurEntryId = (-1L);
   }

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::UpdateList(long lOffset)
{
HRESULT retc=S_OK;
int ii;
long text_size;
long full_size;
long start_offset;
long end_offset;
long entry_id;
unsigned char text_buf[TV_XL_MAX_IX_LEN+1];
HCURSOR cur_sav=NULL;
LRESULT /* int */ retv;

// bool print_next=False;

#if FALSE // TRUE //
#ifdef LZDSHT_ENCODED
unsigned char *entry_img=NULL;
long img_len;
static KpChar *hw_ptr;
#else
XmlNode_tag *cur_entry=NULL;
static const KpChar *hw_ptr;
#endif
KpChar i_text_buf[TV_XL_MAX_IX_LEN+1];
#else
const unsigned char *pnts;
unsigned char *pntd;
KpChar cur_ch;
#endif

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

   KP_ASSERT(lzdsh_search->m_lpInFileObj != NULL, KP_E_NO_FILE, null, TRUE);
   KP_ASSERT(lzdsh_search->m_lpInFileObj->FilePtr != NULL, KP_E_NO_FILE, null, TRUE);

   if(SUCCEEDED(retc))
   {

      if(lzdsh_search != NULL) /* retc = */ lzdsh_search->BlockSemaphore();

      if(SUCCEEDED(retc))
      {
         cur_sav=::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
         if(cur_sav==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// ----------------------
      if(SUCCEEDED(retc))
      {
         SendMessage(m_MainList, WM_SETREDRAW, FALSE, 0L);

         if(SUCCEEDED(retc))
            if(SendMessage(m_MainList, LB_RESETCONTENT, 0, 0L) == CB_ERR)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }

// -------------------------
      if(SUCCEEDED(retc))
      {
         full_size = aiIndexWidths[lzdsh_search->m_iIndexFile];
         text_size=full_size-sizeof(long);
         if(text_size>TV_XL_MAX_IX_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
         retc = lzdsh_search->CalcOffsets(lOffset, &start_offset, &end_offset);

      if(SUCCEEDED(retc))
         retc = lzdsh_search->m_lpInFileObj->Fseek(lzdsh_search->m_iIndexFile, start_offset, SEEK_SET);

      if(SUCCEEDED(retc))
         m_iNumOfListEntries=(end_offset-start_offset)/full_size;
#ifndef LZDSHT_FULL_LIST
//    if((m_iNumOfListEntries!=LZDSH_LIST_NUM_LINES) && SUCCEEDED(retc))
      if((m_iNumOfListEntries>LZDSH_LIST_NUM_LINES) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
#endif

#ifdef LZDSHT_DIFF_KWDS
#ifdef LZDSHT_FULL_LIST
      KP_DELETEA(m_lpszaListKeywords);

      KP_NEWA(m_lpszaListKeywords, unsigned char, m_iNumOfListEntries][TV_XL_MAX_IX_LEN + 1);
#endif

// ----------------------
      if(SUCCEEDED(retc))
#ifdef LZDSHT_FULL_LIST
         for(ii=0; ii<m_iNumOfListEntries; ii++)
#else
         for(ii=0; ii<LZDSH_LIST_NUM_LINES; ii++)
#endif
         {
            m_lpszaListKeywords[ii][0]=Nul;
//          m_lpszaListTexts[ii][0]=Nul;
         }
#endif

// ----------------------
      if(SUCCEEDED(retc))
      {
         retv=SendMessage(m_MainList, LB_INITSTORAGE, m_iNumOfListEntries,
            m_iNumOfListEntries*LZDSH_MAX_LIST_ITEM_WDT);
         if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
         if((retv==LB_ERR) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
      }

      if((text_size>TV_XL_MAX_IX_LEN) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);

      for(ii=0; (ii<m_iNumOfListEntries) && SUCCEEDED(retc); ii++)
      {
         text_buf[0]=Nul;

#ifdef LZDSHT_DIFF_KWDS
         pntd=(unsigned char *)m_lpszaListKeywords[ii];
#else
         pntd=text_buf;
#endif

//       if(ii>=LZDSH_LIST_NUM_LINES)
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
            retc = lzdsh_search->m_lpInFileObj->FilePtr->GetImage(pntd, text_size, lzdsh_search->m_iIndexFile, True);

         if(SUCCEEDED(retc))
         {
            pntd[text_size] = Nul;
            retc = CutTrailSpcs(pntd, lpszSpcEolNotNBSP);
         }

         if(SUCCEEDED(retc))
            retc = lzdsh_search->m_lpInFileObj->FilePtr->GetImage(&entry_id, sizeof(long), lzdsh_search->m_iIndexFile, True);

// #ifdef LZDSHT_DIFF_KWDS
#if FALSE // TRUE //

         hw_ptr=NULL;
#ifdef LZDSHT_ENCODED
         if((entry_img!=NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc = lzdsh_search->m_lpInFileObj->ReadEntryImg(entry_id, &entry_img, &img_len);
         if((entry_img==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) retc=GetHwFromEncImg((Chars16 **)&hw_ptr, entry_img, img_len, entry_id);
#else
         if(SUCCEEDED(retc)) retc=m_lpInFileObj->SeekEntry(entry_id);

         if((cur_entry!=NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=ReadEntry(&cur_entry, lzdsh_search->m_lpInFileObj, True);
         if((cur_entry==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) retc=cur_entry->GetHw((const Chars16 **)&hw_ptr);
#endif

         if((hw_ptr!=NULL) && SUCCEEDED(retc))
         {
            if(TvIntStrLen(hw_ptr)>TV_XL_MAX_IX_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               NormalizeHeadword(i_text_buf, hw_ptr);
               TvClearAccents(i_text_buf);

//             retc=KptStrDecode((unsigned char *)m_lpszaListTexts[ii], i_text_buf, TvIntStrLen(hw_ptr), m_iCtrlCtbl);
               retc=KptStrDecode(text_buf, i_text_buf, TvIntStrLen(hw_ptr), m_iCtrlCtbl);
               if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)) retc=S_OK;
            }
         }
#else
//       strcpy((unsigned char *)m_lpszaListTexts[ii], (const unsigned char *)m_lpszaListKeywords[ii]);

#ifdef LZDSHT_DIFF_KWDS
         pnts=(const unsigned char *)m_lpszaListKeywords[ii];
#else
         pnts=text_buf;
#endif

//       pntd=(unsigned char *)m_lpszaListTexts[ii];
         pntd=text_buf;

         while((*pnts) && SUCCEEDED(retc))
         {
            if(*pnts!=EXACT_ENTRY_CHR) // '#'
            {
               retc=KptCharEncode(&cur_ch, *pnts, TV_IX_CTBL);
               if(
                  (
                     ((cur_ch<0) || (cur_ch>=C_CharSize0)) &&
                     SUCCEEDED(retc)
                  ) ||
                  (retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF)
                 )
               {
                  cur_ch=C_Quest; // '?';
                  if(SUCCEEDED(retc)) retc=KP_E_UNKN_CHR;
                  retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
               }

               if(
//                (cur_ch==C_Point) || // '.' ???
                  (cur_ch==DOUBLE_ENTRIES_CHR) || // '*'
                  (cur_ch==DOUBLE_ENTRIES_KPCHAR) // C_Bpoint, bullet
                 )
                  cur_ch=DOUBLE_ENTRIES_LZDSH_KPCHAR; // C_NBSP;

               if(SUCCEEDED(retc))
               {
//                cur_ch=TvToLower((Chars16)cur_ch);

                  retc=KptCharDecode(pntd, cur_ch, TV_IX_CTBL);
                  if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
                  {
                     *pntd='?';
                     retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                  }
                  pntd++;
               }
            }
            pnts++;
         }
         *pntd=Nul;
#endif

         if(SUCCEEDED(retc))
         {
//          retc=LzdshAppendStrToList(m_MainList, m_lpszaListTexts[ii]);
            retc=LzdshAppendStrToList(m_MainList, text_buf);
         }

#if FALSE
if(print_next)
{
KpMsgOut(text_buf, IDI_ASTERISK, KP_MB_TESTI);
print_next=False;
}
if(strcmp(text_buf, "serijinis")==0)
{
KpMsgOut(text_buf, IDI_ASTERISK, KP_MB_TESTI);
print_next=True;
}
#endif

#if FALSE
#ifdef LZDSHT_ENCODED
// besàlygiðkai trint negalima – gali bûti uþsilikæs GetHwFromEncImg()
         KP_DELETEA(hw_ptr);
         KP_DELETEA(entry_img);
#else
         KP_DELETE(cur_entry);
#endif
#endif

      }

// ----------------------
#if FALSE
      if(SUCCEEDED(retc))
      {
unsigned char str_buf[1000];
str_buf[0]=Nul;
         for(ii=0; ii<LZDSH_LIST_NUM_LINES; ii++)
         {
            strcat(str_buf, (const unsigned char *)m_lpszaListTexts[ii]); // m_lpszaListKeywords[ii]
            strcat(str_buf, " ");
         }
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
      }
#endif
// ----------------------

      if(SUCCEEDED(retc))
         SendMessage(m_MainList, WM_SETREDRAW, TRUE, 0L);

      if(cur_sav!=NULL) ::SetCursor(cur_sav);
      cur_sav=NULL;

      if(lzdsh_search != NULL) /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();

   } // if(SUCCEEDED(retc))

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::SelectList(long lOffset)
{
HRESULT retc=S_OK;
long full_size;
long start_offset;
long end_offset;

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

   if(SUCCEEDED(retc))
   {
   /* retc = */ lzdsh_search->BlockSemaphore();

      if(SUCCEEDED(retc))
         full_size = aiIndexWidths[lzdsh_search->m_iIndexFile];

      if(SUCCEEDED(retc))
         retc = lzdsh_search->CalcOffsets(lOffset, &start_offset, &end_offset);

      if(SUCCEEDED(retc))
      {
//       if(SendMessage(m_MainList, LB_SETCURSEL, (lOffset-start_offset)/full_size, (lOffset-start_offset)/full_size)==LB_ERR) // lParam reikia KpListBox
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         retc=SetListBoxSel(m_MainList, (lOffset-start_offset)/full_size);
      }

   /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();

   }

return(retc);
}


// ----------------------------------
#ifdef Debug
#if TRUE // #if FALSE
unsigned char clip_buf[KP_MAX_FILE_LIN_LEN+1];

unsigned char rtf_buf[] =
{
"{\\rtf1\\ansi\\ansicpg1252\\uc1 \\deff0\\deflang1033\\deflangfe1033{\\fonttbl{\\f0\\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f28\\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\f29\\froman\\fcharset204\\fprq2 Times New Roman Cyr;}\n"
"{\\f31\\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f32\\froman\\fcharset162\\fprq2 Times New Roman Tur;}{\\f33\\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\f34\\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}\n"
"{\\f35\\froman\\fcharset186\\fprq2 Times New Roman Baltic;}}{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;\\red0\\green255\\blue255;\\red0\\green255\\blue0;\\red255\\green0\\blue255;\\red255\\green0\\blue0;\\red255\\green255\\blue0;\\red255\\green255\\blue255;\n"
"\\red0\\green0\\blue128;\\red0\\green128\\blue128;\\red0\\green128\\blue0;\\red128\\green0\\blue128;\\red128\\green0\\blue0;\\red128\\green128\\blue0;\\red128\\green128\\blue128;\\red192\\green192\\blue192;}{\\stylesheet{\n"
"\\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\fs24\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 \\snext0 Normal;}{\\*\\cs10 \\additive Default Paragraph Font;}}\n"
"\\widowctrl\\ftnbj\\aenddoc\\noxlattoyen\\expshrtn\\noultrlspc\\dntblnsbdb\\nospaceforul\\formshade\\horzdoc\\dgmargin\\dghspace180\\dgvspace180\\dghorigin1701\\dgvorigin1984\\dghshow1\\dgvshow1\n"
"\\jexpand\\pgbrdrhead\\pgbrdrfoot\\splytwnine\\ftnlytwnine\\htmautsp\\nolnhtadjtbl\\useltbaln\\alntblind\\lytcalctblwd\\lyttblrtgr\\lnbrkrule \\fet0\\sectd \\linex0\\endnhere\\sectdefaultcl {\\*\\pnseclvl1\\pnucrm\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl2\n"
"\\pnucltr\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl4\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxta )}}{\\*\\pnseclvl5\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl6\n"
"\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl7\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang\n"
"{\\pntxtb (}{\\pntxta )}}\\pard\\plain \\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\fs24\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 {\\fs16 {\\*\\bkmkstart OLE_LINK1}a}{a}{\\cf6 a}{\\f35\\cf6\\lang1063\\langfe1033\\langnp1063 \\\'e6}\n"
"{\\f35\\lang1063\\langfe1033\\langnp1063 \\\'e6}{\\f35\\cf2\\lang1063\\langfe1033\\langnp1063 \\\'e6}{\\f29\\cf2\\lang1049\\langfe1033\\langnp1049 \\\'ff}{\\f29\\lang1049\\langfe1033\\langnp1049 \\\'ff}{\\f29\\fs32\\lang1049\\langfe1033\\langnp1049 \\\'ff}{\\*\\bkmkend OLE_LINK1}}\n"
};
#endif
#endif

// ----------------------------------
HRESULT LzdShDlg::ProcessInput(int iToHistListFlags)
{
HRESULT retc=S_OK;
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

   if(m_CurList == m_MainList)
   {
      if(SUCCEEDED(retc)) if((m_InpEdit != NULL) && m_bKbdInput)
      {
#if FALSE
         gtx.cb=KP_MAX_FILE_LIN_WDT;
         gtx.flags=GT_DEFAULT;
         gtx.codepage=CP_UNICODE;
         gtx.lpDefaultChar=NULL;
#  if Compiler==Watcom
         gtx.lpUsedDefaultChar=NULL;
#  else
         gtx.lpUsedDefChar=NULL;
#  endif
         SendMessage(m_InpEdit, EM_GETTEXTEX, (WPARAM)&gtx, str_buf);
#else
         retc=KpGetCtrlText(m_InpEdit, str_buf, KP_MAX_FILE_LIN_WDT);
#endif
         if(SUCCEEDED(retc))
         {
            str_buf[KP_MAX_FILE_LIN_WDT]=Nul;
// KP_TRACE("ProcessInput: SetToSearchStr()");
            retc = lzdsh_search->SetToSearchStr(str_buf,
               (lzdsh_search->m_iToHistListFlags == LZDSH_HIST_NONE)?
               (
//                (iToHistListFlags == LZDSH_HIST_NONE)?
//                LZDSH_HIST_DEPENDENT|LZDSH_HIST_TIMER:
                  iToHistListFlags
               ):
               lzdsh_search->m_iToHistListFlags);

//          KP_TRACE(str_buf);
         }

      } // if(m_InpEdit!=NULL)


#ifdef Debug
//----------------------------------
if(m_InpEdit!=NULL)
{

//----------------------------------
// if(lzdsh_search != NULL) /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->BlockSemaphore();
// if(SUCCEEDED(retc)) retc = SetEditControlText(lzdsh_search->m_lpszToSearch);
// if(lzdsh_search != NULL) /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();

//----------------------------------
#  if FALSE
   hdc=GetDC(m_InpEdit);
   if(hdc==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      InvalidateRgn(m_InpEdit, NULL, True);
      SendMessage(m_InpEdit, WM_PAINT, (WPARAM)hdc, NULL);
   }
   if(hdc!=NULL) ReleaseDC(m_InpEdit, hdc);
   hdc=NULL;
#  endif

} // if(m_InpEdit!=NULL)


#ifdef IBSH_RES_MODE_RTF

if(m_ResRichEdit!=NULL)
{

//----------------------------------
#  if FALSE
   if(SUCCEEDED(retc))
   {
      KP_TRACE(">>>>>>>>>");
      clip_format=0;
      while(SUCCEEDED(retc))
      {
         if(OpenClipboard(m_ResRichEdit)==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);

         SetLastError(ERROR_SUCCESS);
         clip_format=EnumClipboardFormats(clip_format);
         err=GetLastError();
         if(err!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, err, True, __FILE__, __LINE__, 0L, NULL);

         if(NULL==CloseClipboard())
         {
            err=GetLastError();
            if(err!=NO_ERROR)
            {
               retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, err, False, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) retc=retc0;
            }
         }


         if((clip_format==0) || FAILED(retc)) break;


         if(0==GetClipboardFormatName(clip_format, (char *)format_name, 30))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            format_name[0]=Nul;
         }
//       format_name[30]=Nul;

         if(SUCCEEDED(retc))
         {
            retc=KpGetClipboardData(m_ResRichEdit, clip_format, clip_buf, KP_MAX_FILE_LIN_LEN, False);
            if(FAILED(retc))
            {
               strcpy(clip_buf, ">>> Unable to get clip data <<<");
               retc=S_OK;
            }
         }
//       clip_buf[30]=Nul;

         if((strcmp(format_name, KP_CF_RTF_NAME)==0) && SUCCEEDED(retc))
         {
//          sprintf((char *)str_buf, "%d [%s] %s", clip_format, format_name, clip_buf);
//          KP_TRACE(str_buf);
            KP_TRACE(clip_buf);

            out_file=fopen("kpn1.txt", "w");
            if(out_file)
            {
               fputs((const char *)clip_buf, out_file);
               fclose(out_file);
            }
         }

      } // while(SUCCEEDED(retc))

      KP_TRACE("<<<<<<<<<");

   } // if(SUCCEEDED(retc))
#  endif

//----------------------------------
#  if FALSE
   if(SUCCEEDED(retc))
   {
      retc=GetClipboardText(m_ResRichEdit, clip_buf, KP_MAX_FILE_LIN_LEN, False);
      if(SUCCEEDED(retc))
      {
         KP_TRACE(clip_buf);
      }
      else if(retc==KP_E_OBJ_NOT_FOUND)
      {
         retc=S_OK;
         clip_buf[0]=Nul;
      }
   }
#  endif


//----------------------------------
#  if FALSE // #  ifdef Debug //
// if(SUCCEEDED(retc)) retc=KpSetCtrlText(m_ResRichEdit, (const unsigned char *)"{\\rtf1 ABCDEF}");
// if(SUCCEEDED(retc)) retc=KpSetCtrlText(m_ResRichEdit, rtf_buf);

// KpMsgOut("Prieð KpSetCtrlRtfText", IDI_ASTERISK, KP_MB_TESTI);
   if(SUCCEEDED(retc)) retc=KpSetCtrlRtfText(m_ResRichEdit, rtf_buf, True /* False */);
// KpMsgOut("Po KpSetCtrlRtfText", IDI_ASTERISK, KP_MB_TESTI);
#  endif

} // if(m_ResRichEdit!=NULL)

#endif // #ifdef IBSH_RES_MODE_RTF

//----------------------------------
// KP_TRACE(RICHEDIT_CLASS);

#endif // #ifdef Debug

#if FALSE
int ii;
unsigned char str_buf[1000];

if(SUCCEEDED(retc))
   if(SendMessage(m_MainList, LB_RESETCONTENT, NULL, NULL) == CB_ERR)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
// for(ii=0; ii<LZDSH_LIST_NUM_LINES; ii++)
// {
// if(SendMessage(m_MainList, LB_DELETESTRING, 0, NULL)==LB_ERR)
// retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// }
for(ii=0; (ii<LZDSH_LIST_NUM_LINES) && SUCCEEDED(retc); ii++)
{
   sprintf((char *)str_buf, "%s %d", lzdsh_search->m_lpszToSearch, ii);
// if(SendMessage(m_MainList, LB_SETITEMDATA, ii, (LPARAM)str_buf)==LB_ERR)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   retc = LzdshAppendStrToList(m_MainList, str_buf);
}
// for(ii=0; ii<LZDSH_LIST_NUM_LINES; ii++)
// {
//    if(SendMessage(m_MainList, LB_GETTEXT, ii, (LPARAM)str_buf)==LB_ERR)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE(str_buf);
// }
SendMessage(m_MainList, WM_SETREDRAW, TRUE, NULL);
#endif

//    SendMessage(m_InpEdit, WM_PAINT, NULL, NULL);

//    if(m_bKbdInput && SUCCEEDED(retc))
//       retc = lzdsh_search->SearchAndDisplay();

   } // if(m_CurList==m_MainList)

return(retc);
}


#if FALSE // #ifdef Debug
#if Compiler != Watcom
void KpEnumClipboardFormats(void)
{
unsigned int ii = 0;
stringstream str_stream;
unsigned char str_buf[100+1];
const unsigned char *pnts = NULL;
HGLOBAL h_mem=NULL;

   if(OpenClipboard(HWND_DESKTOP /* m_ResRichEdit */))
   {
      do
      {
         ii = EnumClipboardFormats(ii);
         if(ii)
         {
            str_stream.str("EnumClipboardFormats: ");
            switch(ii)
            {
            case CF_TEXT:           str_stream << "CF_TEXT"; break;            // 1
            case CF_BITMAP:         str_stream << "CF_BITMAP"; break;          // 2
            case CF_METAFILEPICT:   str_stream << "CF_METAFILEPICT"; break;    // 3
            case CF_SYLK:           str_stream << "CF_SYLK"; break;            // 4
            case CF_DIF:            str_stream << "CF_DIF"; break;             // 5
            case CF_TIFF:           str_stream << "CF_TIFF"; break;            // 6
            case CF_OEMTEXT:        str_stream << "CF_OEMTEXT"; break;         // 7
            case CF_DIB:            str_stream << "CF_DIB"; break;             // 8
            case CF_PALETTE:        str_stream << "CF_PALETTE"; break;         // 9
            case CF_PENDATA:        str_stream << "CF_PENDATA"; break;         // 10
            case CF_RIFF:           str_stream << "CF_RIFF"; break;            // 11
            case CF_WAVE:           str_stream << "CF_WAVE"; break;            // 12
            case CF_UNICODETEXT:    str_stream << "CF_UNICODETEXT"; break;     // 13
            case CF_ENHMETAFILE:    str_stream << "CF_ENHMETAFILE"; break;     // 14
            case CF_HDROP:          str_stream << "CF_HDROP"; break;           // 15
            case CF_LOCALE:         str_stream << "CF_LOCALE"; break;          // 16
            case CF_MAX:            str_stream << "CF_MAX"; break;             // 17
            case CF_OWNERDISPLAY:   str_stream << "CF_OWNERDISPLAY"; break;    // 128
            case CF_DSPTEXT:        str_stream << "CF_DSPTEXT"; break;         // 129
            case CF_DSPBITMAP:      str_stream << "CF_DSPBITMAP"; break;       // 130
            case CF_DSPMETAFILEPICT:str_stream << "CF_DSPMETAFILEPICT"; break; // 131
            case CF_DSPENHMETAFILE: str_stream << "CF_DSPENHMETAFILE"; break;  // 142
            case CF_PRIVATEFIRST:   str_stream << "CF_PRIVATEFIRST"; break;    // 512
            case CF_PRIVATELAST:    str_stream << "CF_PRIVATELAST"; break;     // 767
            case CF_GDIOBJFIRST:    str_stream << "CF_GDIOBJFIRST"; break;     // 768
            case CF_GDIOBJLAST:     str_stream << "CF_GDIOBJLAST"; break;      // 1023
            default:
               if(ii == KpCfRtfClFormat) str_stream << "KP_CF_RTF";
               else if(ii == KpCfHtmlClFormat) str_stream << "KP_CF_HTML";
               else str_stream << ii;
               break;
            }

            str_buf[0]= Nul;

//          KpGetClipboardData(HWND_DESKTOP, ii, str_buf, 100, True);
            h_mem=GetClipboardData(ii);
            if(h_mem)
            {
               pnts=(const unsigned char *)GlobalLock(h_mem);
               if(pnts) strncpy(str_buf, pnts, 100);
               GlobalUnlock(h_mem);
            }

            str_buf[100] = Nul;
            RemoveSpCharsSpc(str_buf);
            str_stream << ": " << str_buf;

            KP_TRACE(KpString(str_stream.str()));
         }

      } while(ii);

      CloseClipboard();
   }
}
#endif
#endif


// ----------------------------------
int /* HRESULT */ LzdShDlg::DoEdit(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
MSG msg;
int retp;
bool endfl=False;
// unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
HKEY hKey=0;
LONG retw=ERROR_SUCCESS;
DWORD dwDisposition;
// LRESULT /* long */ retv;
HWND mouse_over_wnd = NULL;
#if IBSH_SKIN == IBSH_SKIN_STANDART
int ix;
#endif
KpWnd *cur_wnd = NULL;
HWND cur_hwnd = NULL;
KpWnd *hist_wnd = NULL;
HWND hist_hwnd = NULL;

// KP_TRACE("DoEdit");

   KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True);
// #ifdef IBSH_RES_MODE_XGECKO
// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);
// #endif
   KP_ASSERT(m_hDialogWindow != NULL, KP_E_SYSTEM_ERROR, null, True);

#ifdef Debug
// UINT clip_format;
// GETTEXTEX gtx;
// HDC hdc;
// UINT clip_format;
// unsigned char format_name[100];
// DWORD err;
// FILE *out_file=NULL;
#endif

   if(SUCCEEDED(retc)) ShowWindow
                           (
#ifdef KP_USE_WXWIDGETS
                                 (HWND)m_hDialogWindow->GetHWND(),
#else
                                 m_hDialogWindow,
#endif
                              SW_SHOW
                           );

//--------------------------------------------
#if FALSE // #ifdef Debug

while (GetMessage(&msg, 0, 0, 0))
{
  TranslateMessage(&msg);
  DispatchMessage(&msg);
}

//--------------------------------------------
#else
   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #ifdef Debug
if((msg.message==LB_GETTEXT) || (msg.message==KP_LB_GETTEXT))
{
char str_buf[100];
sprintf(str_buf, "DoEdit pries TranslateMessage: msg.lParam: %lx msg.message: %d", msg.lParam, msg.message);
KP_TRACE(str_buf);
}
#endif

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);

#if FALSE // #ifdef Debug
if((msg.message==LB_GETTEXT) || (msg.message==KP_LB_GETTEXT))
{
char str_buf[100];
sprintf(str_buf, "DoEdit po TranslateMessage: msg.lParam: %lx msg.message: %d", msg.lParam, msg.message);
KP_TRACE(str_buf);
}
#endif

// ------------------------------------------------- tik DispatchMessage() blokavimui, pagrindinis praneðimø apdorojimas vëliau
         if(SUCCEEDED(retc)) switch(msg.message)
         {

// blokuoti m_ResRichEdit teksto ivedima
         case WM_CHAR:
//       case WM_KEYFIRST:
         case WM_KEYDOWN:
         case WM_KEYUP:
            if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, m_CurList);
            cur_hwnd = NULL;
            if(cur_wnd && SUCCEEDED(retc)) cur_hwnd = cur_wnd->m_hSubListBox;

#if FALSE // #if TRUE // #ifdef Debug //
unsigned char str_buf[100];
sprintf((char *)str_buf, "msg.hwnd: %lx  m_CurList: %lx  m_MainList: %lx  cur_hwnd: %lx", msg.hwnd, m_CurList, m_MainList, cur_hwnd);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
// KP_TRACE_4("WM_KEYDOWN m_CurList:%lx cur_wnd:%lx msg.hwnd:%lx cur_hwnd:%lx", m_CurList, cur_wnd, msg.hwnd, cur_hwnd);
#ifdef IBSH_RES_MODE_XGECKO
// KP_TRACE_5("WM_KEYDOWN m_InpEdit:%lx cur_hwnd:%lx m_DictBox:%lx m_pResCtrl->hWnd:%lx msg.hwnd:%lx", m_InpEdit, cur_hwnd, m_DictBox, m_pResCtrl->hWnd, msg.hwnd);
// KP_TRACE_5("WM_KEYDOWN inp:%lx list:%lx dict:%lx htm:%lx msg:%lx", m_InpEdit, m_CurList, m_DictBox, m_pResCtrl->hWnd, msg.hwnd);
#endif
#ifdef IBSH_RES_MODE_MSHTML
// KP_TRACE_5("WM_KEYDOWN inp:%lx list:%lx dict:%lx htm:%lx msg:%lx", m_InpEdit, cur_hwnd, m_DictBox, m_ResHtml->hwnd_, msg.hwnd);
#endif
// KP_TRACE_4("LzdShDlg::DoEdit(): %s m_MainList:%lx cur_hwnd:%lx msg.hwnd:%lx", (msg.message==WM_KEYDOWN)?"WM_KEYDOWN":((msg.message==WM_KEYUP)?"WM_KEYUP":"WM_CHAR"), m_MainList, cur_hwnd, msg.hwnd);

#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
            if((m_ResHtml == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#  endif
#endif

#if FALSE // #ifdef Debug
if(msg.message == WM_KEYDOWN)
{
char str_buf[100];
sprintf(str_buf, "WM_KEYDOWN %d %d", msg.wParam, msg.lParam);
KP_TRACE(str_buf);
}
#endif

//          if(ms_window!=m_ResRichEdit)
//          if((msg.hwnd!=m_ResRichEdit) && (msg.hwnd!=m_DictBox))
            if(SUCCEEDED(retc))
#ifndef IBSH_RES_MODE_XGECKO
               if
               (
#  if FALSE // èia beveik viskas dël dvigubinimosi - dvigubinimasis panaikintas
                  False
                  ||
                  (
                     (msg.hwnd == m_InpEdit)
#     ifndef IBSH_RES_MODE_RTF
                     && ((msg.message != WM_KEYDOWN) || (msg.wParam == Dlt)) // èia dël dvigubinimosi
#     endif
                  )
// #  ifdef IBSH_RES_MODE_RTF // èia dël dvigubinimosi
                  || (msg.hwnd == cur_hwnd)
// #  endif
#     ifdef IBSH_RES_MODE_MSHTML
//                || (msg.hwnd == m_ResHtml->hwnd_)
#     endif
#     ifdef IBSH_RES_MODE_XGECKO
//                || (msg.hwnd == m_pResCtrl->hWnd) // reikia leisti Ctrl+C - kad po to peradresuotø á clipboardFilter()
                  ||(                              // nesuveikia - msg.hwnd kaþkoks kitas
                     (msg.hwnd != m_InpEdit)       // tik ðitaip
                     && (msg.hwnd != cur_hwnd)     // listuose nereikia - dvigubi paspaudimai
                    )
#     endif
#  endif

                  (msg.hwnd == m_InpEdit) || (msg.hwnd == cur_hwnd) // nepraleisti klaviatûros á m_ResRichEdit - Ctrl+C blokavimas
               )
#endif // #ifndef IBSH_RES_MODE_XGECKO
            {
// KP_TRACE_3("Praleido %ld %ld %ld", msg.hwnd, m_pResCtrl->hWnd, m_hDialogWindow);
// KP_TRACE_3("LzdShDlg::DoEdit(): %s Praleido cur_hwnd:%lx msg.hwnd:%lx",
//   (msg.message==WM_KEYDOWN)?"WM_KEYDOWN":((msg.message==WM_KEYUP)?"WM_KEYUP":"WM_CHAR"), cur_hwnd, msg.hwnd);

               DispatchMessage(&msg);
#if FALSE // #ifdef LZDSHT_DISPLAY_SEARCH_THREAD // #ifdef IBSH_RES_MODE_XGECKO //
               if(lzdsh_search->m_lThreadId != 0L)
                  KP_ASSERT(PostThreadMessage(lzdsh_search->m_lThreadId, msg.message, msg.wParam, msg.lParam),
                     KP_E_SYSTEM_ERROR, GetLastError(), False);
#endif

#if FALSE // #if TRUE // #ifdef Debug //
unsigned char str_buf[100];
// sprintf((char *)str_buf, "------- %8x %8x", ms_window, m_ResRichEdit, m_hDialogWindow);
// sprintf((char *)str_buf, "msg.hwnd: %lx  m_DictBox: %lx", msg.hwnd, m_DictBox);
sprintf((char *)str_buf, "DoEdit: msg.hwnd: %lx  m_InpEdit: %lx  cur_hwnd: %lx", msg.hwnd, m_InpEdit, cur_hwnd);
// KP_TRACE(str_buf);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
            }
#if FALSE // #ifdef Debug // Copy komandos apdorojimas - vëliau
            else
            {
//             retb=0; /* !!! */
// KP_TRACE("----- blocked");
// KP_TRACE("DoEdit: WM_CHAR WM_KEYDOWN");
            }
#endif

#if FALSE // #ifdef Debug //
char str_buf[100];
sprintf(str_buf, "LzdShL: WM_CHAR; ThreadId:%ld; msg.hwnd:%d", GetCurrentThreadId(), msg.hwnd);
KP_TRACE(str_buf);
#endif

#if FALSE // #ifdef Debug // #if TRUE //
unsigned char str_buf[1000+1];
// retv=SendMessage(/* m_InpEdit lzdsh_dlg-> */ m_ResRichEdit, /* KP_WM_GETTEXT */, (WPARAM)1000, (LPARAM)str_buf);
retv=SendMessage(msg.hwnd /* m_DictBox */ /* m_MainList */ /* m_ResRichEdit */, LB_GETTEXT, (WPARAM)3, (LPARAM)str_buf);
// retv=SendMessage(/* m_InpEdit lzdsh_dlg-> */ m_ResRichEdit, EM_GETSELTEXT, (WPARAM) /* 1000 */ 0, (LPARAM)str_buf);
// GetWindowText(m_InpEdit /* m_ResRichEdit */, (char *)str_buf, 1000);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#endif
            break;

         default:
            DispatchMessage(&msg);
#if FALSE // #ifdef LZDSHT_DISPLAY_SEARCH_THREAD // #ifdef IBSH_RES_MODE_XGECKO //
            if(lzdsh_search->m_lThreadId != 0L)
               KP_ASSERT(PostThreadMessage(lzdsh_search->m_lThreadId, msg.message, msg.wParam, msg.lParam),
                  KP_E_SYSTEM_ERROR, GetLastError(), False);
#endif
            break;

         } // switch(msg.message)

      } // if(SUCCEEDED(retc))

      retp=LOWORD(msg.wParam);

// ------------------------------------------------- pagrindinis praneðimø apdorojimas
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

      case WM_CAPTURECHANGED:
// KP_TRACE("DoEdit WM_CAPTURECHANGED");
         m_iMouseX = (-1);
         m_iMouseY = (-1);
// #if IBSH_SKIN == IBSH_SKIN_STANDART
         m_bResizing = False;
// #endif
         break;

      case WM_MOUSEMOVE:
         if(m_bButSearchPressed && SUCCEEDED(retc))
         {
HCURSOR cur_sav=NULL;
            cur_sav = ::SetCursor(LoadCursor(NULL /* hKpInstance */, IDC_WAIT));
            if(cur_sav==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            if((m_hCurSav == NULL) && cur_sav && SUCCEEDED(retc)) m_hCurSav = cur_sav;
         }

#if FALSE
#if IBSH_SKIN == IBSH_SKIN_STANDART
//       if((msg.wParam&MK_LBUTTON)==0)
         {
            m_bResizing = False;
// KP_TRACE("WM_MOUSEMOVE not MK_LBUTTON");
         }
#endif
#if FALSE // #ifdef Debug
int ii;
// char str_buf[100];
if(msg.wParam&MK_LBUTTON==0) sprintf((char *)str_buf, "WM_MOUSEMOVE not MK_LBUTTON %d", ii++);
else sprintf((char *)str_buf, "WM_MOUSEMOVE %d", ii++);
KP_TRACE(str_buf);
#endif
#endif

#if IBSH_SKIN == IBSH_SKIN_STANDART

// ------------------
         mouse_over_wnd = msg.hwnd;

         if(msg.hwnd == m_TabCtrl)
         {
#  if FALSE // #ifdef Debug //
{
char str_buf[100];
sprintf((char *)str_buf, "WM_MOUSEMOVE %lx", msg.lParam);
KP_TRACE(str_buf);
}
#  endif
            ix = GET_X_LPARAM(msg.lParam);

            if((ix >= 0) && (ix<LZDSH_ONE_TAB_DX)) mouse_over_wnd = m_TabMain;
            if((ix >= LZDSH_ONE_TAB_DX) && (ix < LZDSH_ONE_TAB_DX*2)) mouse_over_wnd = m_TabSearch;
            if((ix >= LZDSH_ONE_TAB_DX*2) && (ix < LZDSH_ONE_TAB_DX*3)) mouse_over_wnd = m_TabHist;

#  if FALSE // #ifdef Debug //
{
char str_buf[100];
sprintf((char *)str_buf, "WM_MOUSEMOVE %x", mouse_over_wnd);
KP_TRACE(str_buf);
}
#  endif
         }

         KP_ASSERT(pHelpDialog, KP_E_SYSTEM_ERROR, True, null);
         if(SUCCEEDED(retc)) if((hMouseOverWnd != mouse_over_wnd) &&
            (hMouseOverWnd != theHelpDialog.m_GuideButton) && (hMouseOverWnd != theHelpDialog.m_AboutButton))
         {
// KP_TRACE_3("LzdShL: hMouseOverWnd: %ld msg.hwnd: %ld m_GuideButton: %ld", hMouseOverWnd, msg.hwnd, theHelpDialog.m_GuideButton);
            hMouseOverWnd = mouse_over_wnd;
            if(SUCCEEDED(retc)) retc = ManageToolTipTimer();
         }
#endif

         break;

      case WM_TIMER:
// KP_TRACE("DoEdit WM_TIMER");
         if(theKpStAppPtr && SUCCEEDED(retc)) retc = theKpStAppPtr->CheckLicSvr(retp);

         if((! m_bButSearchPressed) && m_hCurSav && SUCCEEDED(retc))
         {
HCURSOR cur_sav=NULL;
            cur_sav = ::SetCursor(m_hCurSav);
            KP_ASSERT(cur_sav != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);
            m_hCurSav = NULL;
         }

// ------------------------------------
         if(retp == ToolTipTimer)
         {
            if(hToolTip && SUCCEEDED(retc))
            {
               if(!(::DestroyWindow(hToolTip)))
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
               }
            }
            hToolTip=NULL;

// -----------------
#ifdef IBSH_RES_MODE_XGECKO
            if((hMouseOverWnd==m_ButBack) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_ButBack, &hToolTip,
                  (const unsigned char *)" Atgal",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_BUT_BACK_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_BUT_BACK_Y+KPW_TOOLTIP_Y,
                  55, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
#endif

#ifdef IBSH_RES_MODE_XGECKO
            if((hMouseOverWnd==m_ButForward) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_ButForward, &hToolTip,
                  (const unsigned char *)" Pirmyn",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_BUT_FORWARD_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_BUT_FORWARD_Y+KPW_TOOLTIP_Y,
                  55, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
#endif

            if((hMouseOverWnd==m_ButSearch) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_ButSearch, &hToolTip,
                  (const unsigned char *)" Paieðka",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_BUT_SEARCH_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_BUT_SEARCH_Y+KPW_TOOLTIP_Y,
                  55, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }

            if((hMouseOverWnd==m_ButFontZoom) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_ButFontZoom, &hToolTip,
                  (const unsigned char *)" Ðrifto didinimas",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_BUT_FONT_ZOOM_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_BUT_FONT_ZOOM_Y+KPW_TOOLTIP_Y,
                  100, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }

            if((hMouseOverWnd==m_ButNarrow) && SUCCEEDED(retc))
            {
               retc = KpCreateStatic(hKpInstance, m_ButNarrow, &hToolTip,
                  (const unsigned char *)((lzdsh_search->m_iLevel==SimplyLevel)?" Iðsamiai":" Glaustai"),
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_BUT_NARROW_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_BUT_NARROW_Y+KPW_TOOLTIP_Y,
                  60, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }

            if((hMouseOverWnd==m_ButAcc) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_ButAcc, &hToolTip,
                  (const unsigned char *)" Kirèiai", // " Diakritai",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_BUT_ACCENTS_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_BUT_ACCENTS_Y+KPW_TOOLTIP_Y,
                  47, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }

// #if IBSH_SKIN != IBSH_SKIN_STANDART
            if((hMouseOverWnd==m_TabMain) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_TabMain, &hToolTip,
                  (const unsigned char *)" Pagrindinis sàraðas",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_TAB_MAIN_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_TAB_MAIN_Y+KPW_TOOLTIP_Y,
                  123, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }

            if((hMouseOverWnd==m_TabSearch) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_TabSearch, &hToolTip,
                  (const unsigned char *)" Paieðkos rezultatai",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_TAB_SEARCH_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_TAB_SEARCH_Y+KPW_TOOLTIP_Y,
                  120, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }

            if((hMouseOverWnd==m_TabHist) && SUCCEEDED(retc))
            {
               retc=KpCreateStatic(hKpInstance, m_TabHist, &hToolTip,
                  (const unsigned char *)" Perþiûrëti þodþiai",
                  m_iWndCurX+LZDSH_WND_BORDER_WDT+LZDSH_TAB_HIST_X+KPW_TOOLTIP_X,
                  m_iWndCurY+LZDSH_WND_BORDER_WDT+LZDSH_WND_CAPTION_HGT+LZDSH_WND_DY_COR+LZDSH_TAB_HIST_Y+KPW_TOOLTIP_Y,
                  110, 1, KPW_CONTROL_STYLE_NORMAL, 0, WS_POPUP|WS_BORDER,
#if IBSH_SKIN == IBSH_SKIN_STANDART
                  KpColorSchemeToolTip); // m_aPenSchemeToolTip);
#else
                  KpColorSchemeLocal);
#endif
#ifdef Debug
               if((hToolTip==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
// #endif

// -----------------
            if(ToolTipTimer) if(!KillTimer(HWND_DESKTOP, ToolTipTimer))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            ToolTipTimer=0;

// -----------------------------------
            if(ToolTipKillTimer) if(!KillTimer(HWND_DESKTOP, ToolTipKillTimer))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            ToolTipKillTimer=SetTimer(HWND_DESKTOP, KPW_TOOLTIP_KILL_TIMER, KPW_TOOLTIP_KILL_TIMEOUT, NULL);
#ifdef Debug
            if(ToolTipKillTimer==0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         } // if(retp==ToolTipTimer)

// ------------------------------------
         else if(retp==ToolTipKillTimer)
         {
            if(ToolTipKillTimer) if(!KillTimer(HWND_DESKTOP, ToolTipKillTimer))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
            ToolTipKillTimer=0;

            if(hToolTip && SUCCEEDED(retc))
            {
               if(!(::DestroyWindow(hToolTip)))
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
               }
            }
            hToolTip=NULL;
         }
         break;

      case WM_CHAR:
// ------------------------------- Copy to clipboard // ne èia - WM_KEYDOWN (o gal WM_KEYUP?)
#if FALSE // #ifdef IBSH_RES_MODE_RTF
         if(SUCCEEDED(retc)) if(msg.hwnd == m_ResRichEdit)
         {
#  ifdef Debug
//          DispatchMessage(&msg);
#  endif

#  if FALSE // #ifdef Debug //
{
stringstream str_stream;
str_stream << "DoEdit WM_CHAR: " << retp;
KP_TRACE(KpString(str_stream.str()));
}
#  endif
         } // if(msg.hwnd==m_ResRichEdit)
#endif

// ------------------------------
         if(SUCCEEDED(retc)) if(m_CurList == m_MainList) m_bKbdInput = True;

         if(SUCCEEDED(retc)) switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId!=0L)
               if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            break;

         case Enter:
            m_bKbdInput = False; // kad ieskotu teisingam indekse
            PostMessage
            (
#ifdef KP_USE_WXWIDGETS
                  (HWND)m_hDialogWindow->GetHWND(),
#else
                  m_hDialogWindow,
#endif
               WM_COMMAND, LZDSH_ID_SEARCH, 0
            );
            break;

         case Esc:
//          endfl=True;
// KP_TRACE("DoEdit: SetToSearchStr(\"\")");
            if(SUCCEEDED(retc)) retc = lzdsh_search->SetToSearchStr((const unsigned char *)"", LZDSH_HIST_NONE);
            if(SUCCEEDED(retc)) retc = SetEditControlText((const unsigned char *)"");
            break;
         }
// KP_TRACE("WM_CHAR");

         if(SUCCEEDED(retc)) retc = ProcessInput(LZDSH_HIST_DEPENDENT|LZDSH_HIST_TIMER);

         break; // case WM_CHAR:


      case WM_KEYDOWN:
//    case WM_KEYFIRST:

#ifdef IBSH_RES_MODE_XGECKO
#  if FALSE
         if((msg.hwnd == m_InpEdit) || (msg.hwnd == cur_hwnd)) m_LastFocus = msg.hwnd; // cur_hwnd surastas prie DispachMessage()
// KP_TRACE_2("LzdShDlg::DoEdit(): %s: lzdsh_dlg->m_LastFocus:%lx",
//   (msg.message==WM_KEYDOWN)?"WM_KEYDOWN":((msg.message==WM_KEYUP)?"WM_KEYUP":"WM_CHAR"), lzdsh_dlg->m_LastFocus);
#  endif
#endif

#ifdef IBSH_RES_MODE_XGECKO
         if(SUCCEEDED(retc)) retc = GetCurWindow(&hist_wnd, m_HistList);
         hist_hwnd = NULL;
         if(hist_wnd && SUCCEEDED(retc)) hist_hwnd = hist_wnd->m_hSubListBox;
// KP_TRACE_3("DoEdit: WM_KEYDOWN: m_HistList:%lx hist_hwnd:%lx msg.hwnd:%lx", m_HistList, hist_hwnd, msg.hwnd);

         if((msg.hwnd != hist_hwnd) && SUCCEEDED(retc))
            strcpy((unsigned char *)m_lpszSelDictName, (const unsigned char *)m_lpszCurDictName);
#endif

// ------------------------
// kad á HistList ið karto patektø tik selektinant pele - klaviatûra - po taimerio
//       if(msg.hwnd == cur_hwnd) lzdsh_search->m_iToHistListFlags = LZDSH_HIST_DEPENDENT | LZDSH_HIST_TIMER;

// ------------------------------- Copy to clipboard // o gal WM_KEYUP?
#ifdef IBSH_RES_MODE_RTF // MSHTML neaiðku, XGecko - per clipboardFilter()
         if(SUCCEEDED(retc))
#  ifdef IBSH_RES_MODE_RTF
            if(msg.hwnd==m_ResRichEdit)
#  endif
#  ifdef IBSH_RES_MODE_MSHTML
#     if Compiler != Watcom
            if(m_ResHtml) if(m_ResHtml->hwnd_)
#     endif
#  endif
         {
bool shift_fl = ((GetKeyState(VK_SHIFT) & 0x80) != 0);
bool ctrl_fl = ((GetKeyState(VK_CONTROL) & 0x80) != 0);
static UniChar copied_text_u[LZDSHT_RESULT_BUF_LEN+1];
static KpChar copied_text_i[LZDSHT_RESULT_BUF_LEN+1];
static unsigned char copied_text[LZDSHT_RESULT_BUF_LEN+1];
long ll = 0L;
CHARRANGE ch_rg;
int ctbl = TV_MAIN_CTBL;
bool found_rus = False;

            if(((retp == Ins) || (retp == C_C)) && ctrl_fl) // Ctrl+Ins, Ctrl+'C' (Copy)
            {
// KP_TRACE("DoEdit: Copy");

#  ifdef IBSH_RES_MODE_RTF
//             ll = SendMessage(m_ResRichEdit, KP_WM_GETTEXT, LZDSHT_RESULT_BUF_LEN, (LPARAM)copied_text);
//             ll = SendMessage(m_ResRichEdit, KP_EM_GETSELTEXT, 0, (LPARAM)copied_text);
//             if((ll < 0) || (ll >= LZDSHT_RESULT_BUF_LEN)) ll = LZDSHT_RESULT_BUF_LEN;
//             copied_text[ll] = Nul;

               retc = KpGetWindowUniText(m_ResRichEdit, copied_text_u, LZDSHT_RESULT_BUF_LEN);
#  endif
#  ifdef IBSH_RES_MODE_MSHTML
               copied_text_u[0] = C_Nul; // iðtraukti tekstà ið m_ResHtml->hwnd_ !!!!
#  endif
               if(SUCCEEDED(retc)) ll = wcslen(copied_text_u); // strlen(copied_text_u);

               if(SUCCEEDED(retc))
               {
#  ifdef IBSH_RES_MODE_RTF
                  SendMessage(m_ResRichEdit, EM_EXGETSEL, 0, (LPARAM)&ch_rg);
#  endif
#  ifdef IBSH_RES_MODE_MSHTML
                  ch_rg.cpMin = 0; ch_rg.cpMax = 0; // iðtraukti selektinimà ið m_ResHtml->hwnd_ !!!!
#  endif

#  ifdef Debug
char str_buf[100];
sprintf(str_buf, "%ld [%d,%d]", ll, ch_rg.cpMin, ch_rg.cpMax);
KP_TRACE(str_buf);
#  endif
                  if((ch_rg.cpMin < 0L) || (ch_rg.cpMax < 0L) /* || (ch_rg.cpMin > ll) || (ch_rg.cpMax > ll) */)
                  {
#  ifdef Debug
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, True, __FILE__, __LINE__, 0L, NULL);
#  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
#  endif
                  }
               }
               if((ch_rg.cpMin > ll) && SUCCEEDED(retc)) ch_rg.cpMin = ll;
               if((ch_rg.cpMax > ll) && SUCCEEDED(retc)) ch_rg.cpMax = ll;
               if((ch_rg.cpMin > ch_rg.cpMax) && SUCCEEDED(retc)) ch_rg.cpMin = ch_rg.cpMax;
               if(SUCCEEDED(retc)) copied_text_u[ch_rg.cpMax] = C_Nul;

#  if FALSE // #ifdef Debug
KptUnicodeToStr(copied_text, copied_text_u, ctbl);
KP_TRACE(copied_text);
#  endif

               if(SUCCEEDED(retc)) retc = KptUnicodeToKpCharStr(copied_text_i, copied_text_u+ch_rg.cpMin);

               if(SUCCEEDED(retc)) TvKpStrClearAccents(copied_text_i);

//             if(SUCCEEDED(retc)) retc = KpSpcEolToSpc(copied_text_i);

               found_rus = False;
               if(SUCCEEDED(retc)) retc = TestLang(copied_text_i, KP_LNG_RUS, &found_rus);
               if(found_rus && SUCCEEDED(retc)) ctbl = 77; // Cyrillic without latin // 73; // Windows-1251, Windows Cyrillic

               if(SUCCEEDED(retc)) /* retc = */ KptStrDecode(copied_text, copied_text_i, ctbl);

               if(SUCCEEDED(retc)) retc = SpcEolToSpc(copied_text);

// KP_TRACE(copied_text);

               if(SUCCEEDED(retc)) retc = RemoveSpCharsCom(copied_text);
//             if(SUCCEEDED(retc)) retc = RemoveSpKpCharsCom(copied_text_i);

//             if(SUCCEEDED(retc)) retc = KptKpCharStrToUnicode(copied_text_u, copied_text_i, True);

// int locale = 0;

#  if FALSE // #ifdef Debug
KpGetClipboardData(HWND_DESKTOP /* m_ResRichEdit */, CF_LOCALE, (unsigned char *)&locale, sizeof(locale), True);
stringstream str_stream;
str_stream << "CF_LOCALE prieð: " << hex << locale;
KP_TRACE(KpString(str_stream.str()));
#  endif

#  if FALSE // #ifdef Debug
KP_TRACE("-------------------- prieð KpClearClipboard()");
KpEnumClipboardFormats();
#  endif

            /* if(SUCCEEDED(retc)) retc = */ KpClearClipboard(HWND_DESKTOP /* m_ResRichEdit */);

#  if FALSE // #ifdef Debug
KP_TRACE("-------------------- po KpClearClipboard()");
KpEnumClipboardFormats();
#  endif
//             locale = iKpt2WinLocale[ctbl];
//             if(SUCCEEDED(retc)) retc = KpSetClipboardData(HWND_DESKTOP /* m_ResRichEdit */, CF_LOCALE, (unsigned char *)&locale, sizeof(locale));

#  if FALSE // #if TRUE //
char str_buf[100];
// sprintf(str_buf, "CF_LOCALE: %x", iKpt2WinLocale[ctbl]);
locale = 0;
KpGetClipboardData(HWND_DESKTOP /* m_ResRichEdit */, CF_LOCALE, (unsigned char *)&locale, sizeof(locale), True);
sprintf(str_buf, "CF_LOCALE: %x", locale);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#  endif

               if(SUCCEEDED(retc)) retc = SetClipboardText(HWND_DESKTOP /* m_ResRichEdit */, copied_text, ctbl);
//             if(SUCCEEDED(retc)) retc = KpSetClipboardData(HWND_DESKTOP /* m_ResRichEdit */, CF_UNICODETEXT, copied_text_u, (wcslen(copied_text_u)+1)*sizeof(copied_text_u[0]));


#  if FALSE // #if TRUE // #ifdef Debug
locale = 0;
KpGetClipboardData(HWND_DESKTOP /* m_ResRichEdit */, CF_LOCALE, (unsigned char *)&locale, sizeof(locale), True);
// stringstream str_stream;
// str_stream.str("");
// str_stream << "CF_LOCALE po: " << hex << locale;
// KP_TRACE(KpString(str_stream.str()));
// char str_buf[100];
sprintf(str_buf, "CF_LOCALE: %x", locale);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
#  endif

#  if FALSE // #ifdef Debug
unsigned char str_buf[500];
GetClipboardText(HWND_DESKTOP /* m_ResRichEdit */, str_buf, 500, True);
KP_TRACE(str_buf);
#  endif

#  if FALSE // #ifdef Debug
KP_TRACE("-------------------- po SetClipboardText()");
KpEnumClipboardFormats();
#  endif

            }
            else if(
                     (retp!=Dlt) && (retp != Bs) &&
                     ((retp!=Ins) || (!shift_fl)) &&  // Shift+Ins (Paste)
                     (((retp != C_V) && (retp != C_X)) || (!ctrl_fl)) // Ctrl+'V' (Paste) ir Ctrl+'X' (Cut)
                   )
            {
               DispatchMessage(&msg);
            }

#  if FALSE // #ifdef Debug //
{
stringstream str_stream;
str_stream << "DoEdit WM_KEYDOWN: " << hex << retp;
KP_TRACE(KpString(str_stream.str()));
}
#  endif
         } // if(msg.hwnd==m_ResRichEdit)

#  ifdef IBSH_RES_MODE_MSHTML
#     if Compiler != Watcom
         if((m_ResHtml == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) if(msg.hwnd == m_ResHtml->hwnd_)
            DispatchMessage(&msg);
#     endif
#  endif

#endif // #ifdef IBSH_RES_MODE_RTF

// ------------------------
         if(SUCCEEDED(retc)) if(m_CurList == m_MainList)
         {
            if((retp==Dlt) || (retp==Bs)) m_bKbdInput = True;

#ifndef Debug
// kad neveiktø Copy/Paste
// neveikia ir taip - dar pabandyt visuose Windowsuose
//       /* if(SUCCEEDED(retc)) retc= */ KpClearClipboard(m_ResRichEdit);
#endif
         } // if(m_CurList==m_MainList)

         if(SUCCEEDED(retc)) retc = ProcessInput(LZDSH_HIST_DEPENDENT|LZDSH_HIST_TIMER);

         break; // case WM_KEYDOWN:

      case WM_LBUTTONDOWN:
//       m_bLButPressed = True;

         if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, m_CurList);
         cur_hwnd = NULL;
         if(cur_wnd && SUCCEEDED(retc)) cur_hwnd = cur_wnd->m_hSubListBox;
// KP_TRACE_2("LzdShDlg::DoEdit(): WM_LBUTTONDOWN: cur_hwnd:%lx msg.hwnd:%lx", cur_hwnd, msg.hwnd);
// kad á HistList ið karto patektø tik selektinant pele; klaviatûra - po taimerio
         if((msg.hwnd == cur_hwnd) && SUCCEEDED(retc)) lzdsh_search->m_iToHistListFlags = LZDSH_HIST_DEPENDENT | LZDSH_HIST_IMMEDIATELY;
//    case WM_RBUTTONDOWN:
// KP_TRACE("WM_*BUTTONDOWN");
//       if((m_CurList==m_MainList) && SUCCEEDED(retc)) m_bKbdInput = True; // èia dël komandos Paste á ávedimo laukà - iðkelta á LzdShDialogProc WM_COMMAND.EN_CHANGE
//       if(SUCCEEDED(retc)) retc = ProcessInput(LZDSH_HIST_DEPENDENT|LZDSH_HIST_IMMEDIATELY);
         break;

#ifdef Debug
//    case WM_PASTE:
//KP_TRACE("WM_PASTE");   // neateina // èia dël komandos Paste á ávedimo laukà - ið tikrøjø LzdShDialogProc WM_COMMAND.EN_CHANGE
//       break;
#endif

      case WM_LBUTTONUP:
// KP_TRACE("DoEdit WM_LBUTTONUP");
//       m_bLButPressed = False;
         break;

      case WM_LZDSH_REFRESH_DISPLAY:

#if FALSE // #ifdef Debug
// char str_buf[100];
sprintf(str_buf, "LzdShL: WM_LZDSH_REFRESH_DISPLAY received; ThreadId:%ld", GetCurrentThreadId());
KP_TRACE(str_buf);
#endif

#ifdef LZDSH_EDITOR_BUILD
         if(SUCCEEDED(retc)) retc = SaveTagBeingEdited(False, False);
#endif

// KP_TRACE_1("LzdShDlg::DoEdit(): WM_LZDSH_REFRESH_DISPLAY forwarded to ThreadId:%ld", lzdsh_search->m_lThreadId);
         KP_ASSERT(lzdsh_search->m_lThreadId, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc))
            if(!PostThreadMessage(lzdsh_search->m_lThreadId, WM_LZDSH_REFRESH_DISPLAY, 0, 0L))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
//          if(msg.hwnd==theOptDialog.m_hDialogWindow)
//             if(theOptDialog.m_hDialogWindow!=NULL)
//             {
//                if(!(::DestroyWindow(theOptDialog.m_hDialogWindow)))
//                {
#ifdef Debug
// jau buna uzsidares
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
//                }
//             }

//          endfl=True;
            break;
         case IDCANCEL:
            if(msg.hwnd==
#ifdef KP_USE_WXWIDGETS
                  (HWND)m_hDialogWindow->GetHWND()
#else
                  m_hDialogWindow
#endif
              ) endfl=True;
            break;


//--------------------------------------
//       case EN_CHANGE:
// KP_TRACE("DoEdit: EN_CHANGE"); // cia neateina // èia dël komandos Paste á ávedimo laukà - ið tikrøjø LzdShDialogProc WM_COMMAND.EN_CHANGE
//          break;

         } // switch(retp)


         switch(HIWORD(msg.wParam))
         {
         case LBN_SELCHANGE:
//       case CBN_SELCHANGE:
KP_TRACE("DoEdit: LBN_SELCHANGE");
            break;


#if FALSE // #ifdef Debug //
         default:
{
stringstream str_stream;
str_stream << "DoEdit: WM_COMMAND HIWORD(msg.wParam): " << HIWORD(msg.wParam);
KP_TRACE(KpString(str_stream.str()));
}
            break;
#endif
         }

         break;

#if FALSE // #ifdef Debug //
      case 15:
      case 280:
      case WM_RBUTTONDOWN:
      case WM_NCLBUTTONDOWN:
      case WM_NCRBUTTONDOWN:
      case WM_NCMOUSEMOVE:
      case WM_NCHITTEST:
      case WM_SETCURSOR:
      case WM_SIZING:
      case WM_WINDOWPOSCHANGING:
      case WM_SIZE:
      case WM_KEYUP:
         break;

      case WM_NCCALCSIZE:
KP_TRACE("DoEdit: WM_NCCALCSIZE");
         break;
#endif

#if FALSE // #ifdef Debug //
      default:
{
stringstream str_stream;
str_stream << "DoEdit: " << msg.message;
KP_TRACE(KpString(str_stream.str()));
}
         break;
#endif

      } // if(SUCCEEDED(retc)) switch(msg.message)

   } while((!endfl) && SUCCEEDED(retc));

   m_bWrkFl = False;

// ----------------------
// #if IBSH_SKIN != IBSH_SKIN_STANDART
   if(m_RedrawTimer)
   {
      if(!KillTimer
         (
#ifdef KP_USE_WXWIDGETS
               (HWND)m_hDialogWindow->GetHWND(),
#else
               m_hDialogWindow,
#endif
            m_RedrawTimer
         )
        )
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
      m_RedrawTimer=0;
   }
// #endif

// -------- save window coordinates
   hKey = NULL;

   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );

      if(RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &hKey, &dwDisposition) != ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
      if((retw=RegSetValueEx(hKey, "WndX", 0, REG_DWORD,
         (BYTE *)&m_iWndCurX, sizeof(m_iWndCurX)))!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc))
      if((retw=RegSetValueEx(hKey, "WndY", 0, REG_DWORD,
         (BYTE *)&m_iWndCurY, sizeof(m_iWndCurY)))!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc))
      if((retw=RegSetValueEx(hKey, "WndDX", 0, REG_DWORD,
         (BYTE *)&m_iWndCurDX, sizeof(m_iWndCurDX)))!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc))
      if((retw=RegSetValueEx(hKey, "WndDY", 0, REG_DWORD,
         (BYTE *)&m_iWndCurDY, sizeof(m_iWndCurDY)))!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);

   if(hKey)
   {
      retw=RegCloseKey(hKey);
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
      hKey=0;
   }

// ----------------------
// #if IBSH_SKIN != IBSH_SKIN_STANDART
#ifndef KP_USE_WXWIDGETS
   if(m_hDialogWindow!=NULL)
   {
HWND frame;
      frame = m_hDialogWindow;
      m_hDialogWindow=NULL;
      if(!(::DestroyWindow(frame)))
      {
#  ifdef Debug
// jau buna uzsidares
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#  endif
      }
   }
#endif
// #endif

   if(FAILED(retc)) retp = RET_CODE_WIN(retc);

#endif // #else #ifdef Debug

// return(retc);
return(retp);
}


// ----------------------------------
HRESULT LzdShDlg::InitDictList(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
WIN32_FIND_DATA res_data;
HANDLE hh=NULL;
DWORD /* long */ retd;
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fname[KP_MAX_FNAME_LEN+1];
unsigned char ftype[KP_MAX_FTYPE_LEN+1];
DictListEntry entry;
FILE *idd_file;
unsigned char *pnts;

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

   if(SUCCEEDED(retc))
   {
//    hh=FindFirstFileEx("f:\\kp\\source\\tev\\lzdsh\\*.idd", FindExInfoStandard, &res_data, FindExSearchNameMatch, NULL, 0);
//    hh=FindFirstFile("f:\\kp\\source\\tev\\lzdsh\\*.idd", &res_data);
      hh=FindFirstFile("*.idd", &res_data);
      if(hh==INVALID_HANDLE_VALUE)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) do
   {
      retd=0L;

      if(SUCCEEDED(retc))
         retc=TvFnameSplit(disk, path, fname, ftype, (const unsigned char *)res_data.cFileName);

      if(SUCCEEDED(retc)) strcpy(entry.m_lpszFileName, fname);
      if(SUCCEEDED(retc)) entry.iLanguage=tolower(fname[0]);

// dictionary name
      idd_file=NULL;
      if(SUCCEEDED(retc))
      {
         idd_file=fopen(res_data.cFileName, "r");
         if(idd_file==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, res_data.cFileName, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         fgets((char *)entry.m_lpszDictName, KP_MAX_FILE_LIN_WDT, idd_file);
         if(ferror(idd_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, res_data.cFileName, True, __FILE__, __LINE__, 0L, NULL);
         if(feof(idd_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, res_data.cFileName, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         entry.m_lpszDictName[KP_MAX_FILE_LIN_WDT]=Nul;
         pnts=strchr(entry.m_lpszDictName, '\n');
         if(pnts) *pnts=Nul;
      }
      if(idd_file) fclose(idd_file);

// KpMsgOut(fname, IDI_ASTERISK, KP_MB_TESTI);

      if(SUCCEEDED(retc))
      {
         m_iNumOfDictEntries++;
         if(m_DictList == NULL)
         {
            KP_NEW(m_DictList, KpTreeEntry(&entry, sizeof(entry), NULL));
         }
         else
         {
         /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->BlockSemaphore();
            retc = m_DictList->PutToEnd(&entry, sizeof(entry));
         /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();
         }
      }

      if(SUCCEEDED(retc))
         if(!FindNextFile(hh, &res_data))
         {
            retd=GetLastError();
            if(retd!=ERROR_NO_MORE_FILES)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retd, True, __FILE__, __LINE__, 0L, NULL);
         }

   } while((retd!=ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

   if((hh!=NULL) && (hh!=INVALID_HANDLE_VALUE))
      if(!FindClose(hh))
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::GetCurDictName(void)
{
HRESULT retc=S_OK;
int ii;
KpTreeEntry *cur_dict;
DictListEntry *cur_dict_data;

   if(SUCCEEDED(retc))
   {
      m_lpszCurDictName[0] = Nul;

      ii = m_iCurDictEntry;
      cur_dict = NULL;
   }

   if(SUCCEEDED(retc)) retc = m_DictList->GetEntryPtr(&ii, &cur_dict, 0, NULL);
   if((cur_dict==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) cur_dict_data = (DictListEntry *)cur_dict->GetValue();
   KP_ASSERT(cur_dict_data != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(cur_dict->GetValSize() >= sizeof(DictListEntry), KP_E_SYSTEM_ERROR, null, True);

// if(SUCCEEDED(retc)) if(strlen(cur_dict_data->m_lpszFileName) >= KP_MAX_FNAME_LEN) // TV_XL_MAX_TAG_WDT)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      strcpy((unsigned char *)m_lpszCurDictName, cur_dict_data->m_lpszFileName);

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::ChangeDict(int iDictEntry, bool bCheckFileExist, bool /* bPostPone */)
{
HRESULT retc=S_OK;

bCheckFileExist = False; // ignoruoti visada

// LZDSH_DLG_PTR_INIT;
// LZDSH_SEARCH_PTR_INIT;
KpFileSys *lzdsh_search = m_pKpFileSys;
   KP_ASSERT(lzdsh_search != NULL, E_POINTER, null, True);

   if(((iDictEntry < 0) || (iDictEntry >= m_iNumOfDictEntries)) && SUCCEEDED(retc)) retc = KP_E_OBJ_NOT_FOUND;

// ------------------
   if(SUCCEEDED(retc))
   {
   /* if(SUCCEEDED(retc)) */ retc = lzdsh_search->BlockSemaphore();

      if(SUCCEEDED(retc))
      {
         retc = lzdsh_search->CloseFiles(bCheckFileExist);
         if((!bCheckFileExist) && (retc == KP_E_NO_FILE)) retc = S_OK;
      }

      if(SUCCEEDED(retc)) m_iCurDictEntry = iDictEntry;

      if(SUCCEEDED(retc)) retc = GetCurDictName();
#ifdef IBSH_RES_MODE_XGECKO
      if(SUCCEEDED(retc))
         strcpy((unsigned char *)m_lpszSelDictName, (const unsigned char *)m_lpszCurDictName);
#endif

      if(SUCCEEDED(retc)) retc = lzdsh_search->OpenFiles();

      if(SUCCEEDED(retc)) retc = UpdateList(0L);

   /* if(SUCCEEDED(retc)) retc = */ lzdsh_search->ReleaseSemaphore();
   }

// ---------------
   if(SUCCEEDED(retc)) retc = SelectList(0L);

// -------- save selected dictionary
   if(SUCCEEDED(retc)) retc = SaveCurDict();

// ------------------
   if(/* (!bPostPone) && */ SUCCEEDED(retc))
      retc = SetComboBoxSel(m_DictBox, iDictEntry);

#ifdef IBSH_RES_MODE_XGECKO
   if(SUCCEEDED(retc)) m_bDictChanged = True;
#endif

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::ChangeDict(const unsigned char *lpszDictName, bool bCheckFileExist, bool bPostPone)
{
HRESULT retc=S_OK;
KpTreeEntry *cur_dict;
DictListEntry *cur_dict_data;
int found;
int ii;

   if((lpszDictName == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      found = False;
      cur_dict = m_DictList;

      for(ii = 0; (ii < m_iNumOfDictEntries) && (!found) && SUCCEEDED(retc); ii++)
      {
         if((cur_dict==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) cur_dict_data = (DictListEntry *)cur_dict->GetValue();
         KP_ASSERT(cur_dict_data != NULL, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(cur_dict->GetValSize() >= sizeof(DictListEntry), KP_E_SYSTEM_ERROR, null, True);

// KP_TRACE_2("ChangeDict: lpszDictName:%s cur_dict_data->m_lpszFileName:%s", lpszDictName, cur_dict_data->m_lpszFileName);
         if(SUCCEEDED(retc))
            if(strcmp(lpszDictName, cur_dict_data->m_lpszFileName) == 0)
            {
               found = True;
               retc = ChangeDict(ii, bCheckFileExist, bPostPone);
            }

// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//       if(SUCCEEDED(retc)) retc = cur_dict->GetFirstChild(&cur_dict);
         if(SUCCEEDED(retc)) cur_dict = cur_dict->m_pFirstChild;
      }

      if((!found) && SUCCEEDED(retc))
      {
         retc = ChangeDict(m_iCurDictEntry, bCheckFileExist, bPostPone); // (0, ...
         if(retc == KP_E_OBJ_NOT_FOUND)
            retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         else if(SUCCEEDED(retc)) retc = KP_E_KWD_NOT_FOUND;
      }

   }

return(retc);
}


// ----------------------------------
HRESULT LzdShDlg::SaveCurDict(void)
{
HRESULT retc=S_OK;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver=0;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
HKEY hKey = NULL;
DWORD dwDisposition;
LONG retw=ERROR_SUCCESS;

   hKey = NULL;

   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );

      if(RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
         (LPCTSTR)key_name,
         0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
         &hKey, &dwDisposition)!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

#if FALSE
      if(SUCCEEDED(retc))
         if((retw=RegSetValueEx(hKey, "Dict", 0, REG_DWORD,
            (BYTE *)&m_iCurDictEntry, sizeof(int /* m_iCurDictEntry */)))!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
#endif
      if(SUCCEEDED(retc))
         if((retw=RegSetValueEx(hKey, "DictName", 0, REG_SZ,
            (const unsigned char *)m_lpszCurDictName, strlen((const unsigned char *)m_lpszCurDictName)))!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);

      if(hKey)
      {
         retw=RegCloseKey(hKey);
         if(retw!=ERROR_SUCCESS)
            KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         hKey=0;
      }

   }

return(retc);
}


// ----------------------------------
#ifdef IBSH_RES_MODE_XGECKO
long XKpGecko::onDOMEvent(XGeckoDOMEvent *event)
{
HRESULT retc=S_OK;
long retl = 0;
unsigned char word_c[KP_MAX_FILE_LIN_WDT+1+KP_MAX_FNAME_LEN+1]; // +TV_XL_MAX_TAG_WDT+1];
int ctbl = TV_MAIN_CTBL;
unsigned char attr[KP_MAX_FNAME_LEN+1]; // TV_XL_MAX_TAG_WDT+1];
unsigned char dict[KP_MAX_FNAME_LEN+1];
int ii;
KpTreeEntry *cur_dict;
DictListEntry *cur_dict_data;
unsigned char ch;
int max_match = 0;
int match;
unsigned char max_matched[KP_MAX_FNAME_LEN+1];

   LZDSH_DLG_PTR_INIT;
   LZDSH_SEARCH_PTR_INIT;

   if((event == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// KP_TRACE("--------------- GAUTAS NAUJAS PELES PASPAUDIMO IVYKIS");
// KP_TRACE_1("PASPAUSTAS ZODIS:   %ls", event->word);
// KP_TRACE_1("PELES MYGTUKAS:     %i", event->mouseButton);
// KP_TRACE_1("ATRIBUTU SKAICIUS:  %i", event->numAttributes);

// Parodom atributus
// if(SUCCEEDED(retc)) for(ii = 0; n < event->numAttributes; n++)
//    KP_TRACE_2("%ls='%ls'\n", event->attributes[ii], event->values[ii]);

// -----------
   if(SUCCEEDED(retc)) if(event->mouseButton == 0) // kairys klaviðas
   {
      attr[0] = Nul;

      if(SUCCEEDED(retc)) for(ii = 0; ii < event->numAttributes; ii++)
      {
         if((event->attributes == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         if((event->attributes[ii] == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) if(wcslen(event->attributes[ii]) > TV_XL_MAX_TAG_WDT)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
         {
            /* retc = */ KptUnicodeToStr(attr, event->attributes[ii], TV_MAIN_CTBL);
            attr[TV_XL_MAX_TAG_WDT] = Nul;
         }
         if(SUCCEEDED(retc)) if(strcmp(attr, "class") == 0)
         {
            if((event->values == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            if((event->values[ii] == NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) if(wcslen(event->values[ii]) > TV_XL_MAX_TAG_WDT)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               /* retc = */ KptUnicodeToStr(attr, event->values[ii], TV_MAIN_CTBL);
               attr[TV_XL_MAX_TAG_WDT] = Nul;
            }

            break;

         } // if(strcmp(attr, "class") == 0)

      } // for(int n = 0; n < event->numAttributes; n++)

// -----------
// pagal tago vardà (attr) masyve plpszaXmlttDictTags[] ieðkom tago indekso
      if(SUCCEEDED(retc))
      {
         dict[0] = TV_XM_TagStartCh; // '<'
         strcpy(dict+1, attr); // dict[] - tago vardas su < pradþioje
         retc=GetTagIndex(&ii, dict, plpszaXmlttDictTags);
         if(SUCCEEDED(retc))
         {
// pagal tago indexà ið masyvo lpszaXmlTagIxNames[] iðsitraukiam indeksinio failo vardà - èia bus naujas attr
            if((ii<0) || (ii >= XC_TG_NumOfDictTags00))
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, attr, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) if(lpszaXmlTagIxNames[ii][0])
            {
               if(strlen(lpszaXmlTagIxNames[ii]) >= TV_XL_MAX_TAG_WDT)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszaXmlTagIxNames[ii], True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) strcpy(attr, lpszaXmlTagIxNames[ii]);
            }
         }
         else if(retc==TV_E_UNKN_TAG)
         {
//          retc = S_OK; // neradom - paliekam, koks yra - bus suignoruotas
            retc = KpErrorProc.OutputErrorMessage(retc, attr, False, __FILE__, __LINE__, 0L);
         }
      }

// KP_TRACE_3("onDOMEvent tag:%s ix.:%d attr:%s", dict, ii, attr);

// -----------
// iðtraukiam einamojo þodyno vardà - èia dël "hw" etc.
      if(SUCCEEDED(retc)) strcpy(dict, (const unsigned char *)lzdsh_dlg->m_lpszCurDictName);

// -----------
// apdorojam tik tuos, kuriø attr yra "hw", "le", "ic", "xr" (tolimesnë paieðka aktyviam þodyne, attr priskirti dabartinio þodyno vardà)
// arba "tw" ar "dc" (perjungti á atvirkðtiná þodynà; attr priskirti atvirkðtinio þodyno vardà).
      if(SUCCEEDED(retc))
      {

         if((strcmp(attr, "tw")==0) || (strcmp(attr, "dc")==0))
         {
// ieðkom atvirkðtinio þodyno vardo (indekso?)
            strcpy(attr, dict); // einamasis þodynas
            ch = dict[1]; dict[1] = dict[0]; dict[0] = ch; // sukeièiam pirmas dvi þodyno vardo raides

            max_match = 0; // max sutapusiø raidþiø skaièius
            max_matched[0] = Nul; // max sutapæs þodynas
            cur_dict = lzdsh_dlg->m_DictList;

// KP_TRACE_1("onDOMEvent lzdsh_dlg->m_iNumOfDictEntries:%d", lzdsh_dlg->m_iNumOfDictEntries);
            for(ii = 0; ii < lzdsh_dlg->m_iNumOfDictEntries; ii++)
            {
               KP_ASSERT(cur_dict != NULL, KP_E_SYSTEM_ERROR, null, True);

               if(SUCCEEDED(retc)) cur_dict_data = (DictListEntry *)cur_dict->GetValue();
               KP_ASSERT(cur_dict_data != NULL, KP_E_SYSTEM_ERROR, null, True);
               KP_ASSERT(cur_dict->GetValSize() >= sizeof(DictListEntry), KP_E_SYSTEM_ERROR, null, True);

//             if(SUCCEEDED(retc)) if(strlen(cur_dict_data->m_lpszFileName) >= KP_MAX_FNAME_LEN) // TV_XL_MAX_TAG_WDT)
//                retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
               {
                  match = TvStrMatch(dict, cur_dict_data->m_lpszFileName);
// KP_TRACE_4("onDOMEvent ii:%d cur_dict_data->m_lpszFileName:%s dict:%s match:%d", ii, cur_dict_data->m_lpszFileName, dict, match);
                  if(match > max_match)
                  {
                     max_match = match;
                     strcpy(max_matched, cur_dict_data->m_lpszFileName);
// KP_TRACE_2("onDOMEvent matched: max_match:%d max_matched:%s", max_match, max_matched);
                  }
               }

// meta mistines linkerio klaidas - KpTreeEntry::GetTopWindow(KpTreeEntry **) undefined entry
//             if(SUCCEEDED(retc)) retc = cur_dict->GetFirstChild(&cur_dict);
               if(SUCCEEDED(retc)) cur_dict = cur_dict->m_pFirstChild;
            }

            if((max_match >= 2) && SUCCEEDED(retc)) strcpy(attr, max_matched); // jei neradom panaðaus þodyno - liks einamasis
         }

         else if((strcmp(attr, "hw")==0) || (strcmp(attr, "le")==0) || (strcmp(attr, "ic")==0) || (strcmp(attr, "xr")==0))

            strcpy(attr, dict); // paliekam einamàjá þodynà

         else
            attr[0] = Nul; // likusius ignoruojam

      } // if(SUCCEEDED(retc))

// -----------
      if(attr[0] && SUCCEEDED(retc)) // ignoruojam neleksinius tagus
      {
         if((event->word == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) if(wcslen(event->word) >= KP_MAX_FILE_LIN_WDT)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

// !!!!
//       found_rus = False;
//       if(SUCCEEDED(retc)) retc = TestLang(copied_text_i, KP_LNG_RUS, &found_rus);
//       if(found_rus && SUCCEEDED(retc)) ctbl = 77; // Cyrillic without latin // 73; // Windows-1251, Windows Cyrillic

         if(SUCCEEDED(retc))
         {
            retc = KptUnicodeToStr(word_c, event->word, ctbl);
            if(retc == KP_E_UNKN_CHR) retc = S_OK; // daugumos kirèiuotø raidþiø 71 lentelëje nëra,
         }                                         // KptUnicodeToStr() jas sutvarko - kirèius numeta - bet duoda klaidà

// KP_TRACE_2("%d %s", retc, word_c);

         if(SUCCEEDED(retc)) retc = RemoveSpCharsCom(word_c); // numetam skirtukus gale
         if(SUCCEEDED(retc)) TvStrClearAccents(word_c, ctbl); // numetam kirèius, kurie dar liko po KptUnicodeToStr()

// KP_TRACE_2("%d %s", retc, word_c);

         if(SUCCEEDED(retc))
         {
            strcat(word_c, TECH_DELIM_STR);
            strcat(word_c, attr);

            strcpy((unsigned char *)lzdsh_dlg->m_lpszSelDictName, attr);
            if(strcmp((const unsigned char *)lzdsh_dlg->m_lpszSelDictName, (const unsigned char *)lzdsh_dlg->m_lpszCurDictName) != 0)
            {
               retc = lzdsh_dlg->ChangeDict((const unsigned char *)lzdsh_dlg->m_lpszSelDictName, True);
               if((retc == KP_E_KWD_NOT_FOUND) || (retc == KP_E_OBJ_NOT_FOUND))
                  retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
            }
         }

KP_TRACE("onDOMEvent(): SetToSearchStr()");
         if(SUCCEEDED(retc)) retc = lzdsh_search->SetToSearchStr(word_c, LZDSH_HIST_INDEPENDENT|LZDSH_HIST_IMMEDIATELY);
         if(SUCCEEDED(retc)) lzdsh_search->m_lCurEntryId=(-1L);

#if FALSE
KP_TRACE_5("onDOMEvent(): hist. fl.: %s %s %s %s %s",
   (lzdsh_search->m_iToHistListFlags == LZDSH_HIST_NONE)?"NONE":"",
   (lzdsh_search->m_iToHistListFlags & LZDSH_HIST_DEPENDENT)?"DEPENDENT":"",
   (lzdsh_search->m_iToHistListFlags & LZDSH_HIST_INDEPENDENT)?"INDEPENDENT":"",
   (lzdsh_search->m_iToHistListFlags & LZDSH_HIST_TIMER)?"TIMER":"",
   (lzdsh_search->m_iToHistListFlags & LZDSH_HIST_IMMEDIATELY)?"IMMEDIATELY":"");
   (lzdsh_search->m_iToHistListFlags & LZDSH_HIST_FORCED_NONE)?"FORCED_NONE":"");
#endif

#if FALSE // nustato SetToSearchStr()
         if(SUCCEEDED(retc))
         {
            lzdsh_search->m_lpszToHistStr[KP_MAX_FILE_LIN_WDT]=Nul;
            strncpy((unsigned char *)lzdsh_search->m_lpszToHistStr,
                  (const unsigned char *)lzdsh_search->m_lpszToSearch, KP_MAX_FILE_LIN_WDT);
            lzdsh_search->m_lpszToHistStr[KP_MAX_FILE_LIN_WDT]=Nul;
         }
#endif
         if(SUCCEEDED(retc)) retc = lzdsh_dlg->SetEditControlText((const unsigned char *)lzdsh_search->m_lpszToSearch);

      } // if(attr[0] && SUCCEEDED(retc)) // ignoruojam neleksinius tagus

      retl = 1L;

   } // if(event->mouseButton == 0) // kairys klaviðas

// Jei ivyki apdorojome, graziname 1
// Priesingu atveju - 0
// return 1;
return(retl);
}
#endif


// ----------------------------------
#if Compiler != Watcom
#ifdef IBSH_RES_MODE_XGECKO
int clipboardFilter(IString *dst, const IString *src)
{
HRESULT retc=S_OK;
static UniChar copied_text_u[LZDSHT_RESULT_BUF_LEN+1];
static KpChar copied_text_i[LZDSHT_RESULT_BUF_LEN+1];
int ll = 0;

   if(((dst == NULL) || (src == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      ll = src->length();
      if(ll >= LZDSHT_RESULT_BUF_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
   }

// Parodom koks buvo orginalus tekstas
// DEMESIO: tekstas kartais buna ne NULL-TERMINATED
KP_TRACE("KOPIJUOJAMA:\n");
KP_TRACE_("%d\t%.*ls\n", src->length(), src->getData());

   if(SUCCEEDED(retc))
   {
      wcsncpy(copied_text_u, src->getData(), ll);
      copied_text_u[ll] = C_Nul;
   }

   if(SUCCEEDED(retc)) retc = KptUnicodeToKpCharStr(copied_text_i, copied_text_u);

   if(SUCCEEDED(retc)) TvKpStrClearAccents(copied_text_i);

   if(SUCCEEDED(retc)) retc = KpSpcEolToSpc(copied_text_i);

int lic_id = 0;
   if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&lic_id, KP11_LICID);
// Romy Kadzienë 4L71-13AA-5EE3 nori, kad netrintø tarnybinës informacijos; jos lic_id turëtø bûti 116, kaþkodël 0
// lic_id = 1 – mano
// PutLogMessage_("cbFt() %d %d %d %d", lic_id, KpstRand(0), KpstRand(1), KpstRand(116));
   if( // (lic_id != KpstRand(0) /* 22571 */) && (lic_id != KpstRand(1) /* 53068 */) && (lic_id != KpstRand(116) /* 21279 */) &&
      SUCCEEDED(retc)) retc = RemoveSpKpCharsCom(copied_text_i);

   if(SUCCEEDED(retc)) retc = KptKpCharStrToUnicode(copied_text_u, copied_text_i, True);
// KP_TRACE_1("perkoduota: copied_text_u:%.*ls", copied_text_u);
// KP_TRACE_5("perkoduota: copied_text_u:%.*ls copied_text_i:%ls %d %d %d", copied_text_u, copied_text_i, copied_text_u[0], copied_text_u[1], copied_text_u[2]);
// KP_TRACE_1("perkoduota: copied_text_i:%ls", copied_text_i);
// KP_TRACE_3("perkoduota: copied_text_i:%d %d %d", copied_text_i[0], copied_text_i[1], copied_text_i[2]);
// KP_TRACE_3("perkoduota: copied_text_u:%d %d %d", copied_text_u[0], copied_text_u[1], copied_text_u[2]);
// KP_TRACE_1("perkoduota: copied_text_u:%ls", copied_text_u);
// PutLogMessage_("clipboardFilter() perkoduota: copied_text_u:%ls", copied_text_u);

// Nurodom nauja reiksme.
// dst reiksme reikia nustatyti tik tuomet, jei yra grazinama CLIPBOARD_MODIFY
// dst->setData(L"HEHE");
   if(SUCCEEDED(retc)) dst->setData(copied_text_u);

return(XGecko::CLIPBOARD_MODIFY);
}
#endif
#endif
