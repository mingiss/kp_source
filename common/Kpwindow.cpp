//----------------------------------
// kpwindow.cpp
// common Win32 things
//
// 2012.10.02 mp Raktinis _odis nerastas: AppData – Mano emuliatoriuj WinXP Administrator neturi %AppData%, ignoruojam klaidas GetLocalPath()
//


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

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
#include <windowsx.h> // reikia d?l GET_X_LPARAM()/GET_Y_LPARAM() jeigu (CompilerGr == Watcom)
#include <RichEdit.h>
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
#include <Richole.h>
#endif
#if ((CompilerGr==Watcom) && (__WATCOMC__ > 1202)) || (CompilerGr == Mingw)
#include <shlobj.h>
#endif


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


#if Compiler != Watcom
using namespace std;
#endif

#include "res_com.h"

// #ifdef TEST_WATCOM
// #include <afxwin.h>
// #include <wtypes.h>
// #include <afxdlgs.h>
// #include <afximpl.h>
// #include <winhand_.h>
// #endif

#endif
#if (Envir!=MSWin32Mfc)
#include <stdio.h>
#endif
#include <string.h>

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
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpmsg.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "tvxmls.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "iBsht.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "xmln.h"
#include "kpstap.h"

// #include "lzdshl.h"

// ----------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// ------------------------------------------
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

#if FALSE // kelti ? lokal¸ kiekvieno projekto, naudojan?io ShowBmp(), pagrindin? C fail?
#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif
#if IBSH_SKIN == IBSH_SKIN_STANDART // ShowBmp() langas – nestandartinis lokaliai apdorojamas
#error IBSH_SKIN == IBSH_SKIN_STANDART
#endif
#endif

// =================================================================
const unsigned char *lpszaWindowsVerNames[NumOfWinVersions11]=
{
   (const unsigned char *)"Unknown",                       // WinUnkn,   //  0

   (const unsigned char *)"MS Windows 2.0",                // Win20,     //  1

   (const unsigned char *)"MS Windows 3.1x",               // Win31c,    //  2 // common Windows 3.1x
   (const unsigned char *)"MS Windows 3.1",                // Win31,     //  3 // Win32s on Windows 3.1
   (const unsigned char *)"MS Windows 3.11 for Workgroups",// Win311,    //  4 // Windows 3.11 for Workgroups (with Win32s ?)

   (const unsigned char *)"MS Windows 95x",                // Win95c,    //  5 // common Windows 95
   (const unsigned char *)"MS Windows 95",                 // Win95,     //  6
   (const unsigned char *)"MS Windows 95 OSR2",            // Win95OSR2, //  7

   (const unsigned char *)"MS Windows 98x",                // Win98c,    //  8 // common Windows 98
   (const unsigned char *)"MS Windows 98",                 // Win98,     //  9
   (const unsigned char *)"MS Windows 98 SE",              // Win98SE,   // 10 // Windows 98 Second Edition
   (const unsigned char *)"MS Windows CE",                 // WinCE,     // 11
   (const unsigned char *)"MS Windows ME",                 // WinMe,     // 12

   (const unsigned char *)"MS Windows NT",                 // WinNT,     // 13  // for distinguishing between WinNT and Win98 clones

   (const unsigned char *)"MS Windows NT 3.5x",            // WinNT35c,  // 14  // common Windows NT 3.5x
   (const unsigned char *)"MS Windows NT 3.51",            // WinNT351,  // 15  // Windows NT 3.51

   (const unsigned char *)"MS Windows NT 4.0x",            // WinNT40c,  // 16  // common Windows 4.0
   (const unsigned char *)"MS Windows NT Workstation 4.0", // WinNT40,   // 17  // Windows NT Workstation 4.0
   (const unsigned char *)"MS Windows NT Server 4.0",      // WinNT40s,  // 18  // Windows NT Server 4.0

   (const unsigned char *)"MS Windows 2000x",              // Win2000c,  // 19  // common Windows 2000
   (const unsigned char *)"MS Windows 2000",               // Win2000,   // 20  // Windows 2000 Professional // Windows 2000
   (const unsigned char *)"MS Windows 2000 Server",        // Win2000s,  // 21  // Windows 2000 Server  // atsirado nuo 2004.10.01

   (const unsigned char *)"MS Windows XP x",               // WinXPc,    // 22  // common Windows XP // prid?jau 2008.10.22, iki tol nuo WinXPc atsiradimo visi tolesni kodai buvo vienu didesni, negu galvojau

   (const unsigned char *)"MS Windows XP",                 // WinXP,     // 23  // Windows XP           // 22 before 2007.08.23 // 20 before 2004.10.01
   (const unsigned char *)"MS Windows Server 2003",        // Win2003s,  // 24  // Windows Server 2003  // 23 before 2007.08.23 // 21 before 2004.10.01
   (const unsigned char *)"MS Windows XP Starter Edition",    // WinXpStart,// 25  // Windows XP Starter Edition
   (const unsigned char *)"MS Windows XP Home Edition",    // WinXpHome, // 26  // Windows XP Home Edition
   (const unsigned char *)"MS Windows XP Professional",    // WinXpPro,  // 27  // Windows XP Professional
   (const unsigned char *)"MS Windows XP Media Center Edition",//WinXpMedia,// 28  // Windows XP Media Center Edition
   (const unsigned char *)"MS Windows XP Tablet PC Edition",//WinXpTablet,// 29 // Windows XP Tablet PC Edition // Windows CE analogas?
   (const unsigned char *)"MS Windows XP Professional x64 Edition", // WinXP64,   // 30  // Windows XP Professional x64 Edition
   (const unsigned char *)"MS Windows Server 2003 R2",     // Win2003sR2,// 31  // Windows Server 2003 R2

   (const unsigned char *)"MS Windows Vista x",            // WinVistaC, // 32  // common Windows Vista
   (const unsigned char *)"MS Windows Vista",              // WinVista,  // 33  // Windows Vista
   (const unsigned char *)"MS Windows Vista Home Basic",   // WinVistaH, // 34  // Windows Vista Home Basic
   (const unsigned char *)"MS Windows Vista Home Premium", // WinVistaHP,// 35  // Windows Vista Home Premium
   (const unsigned char *)"MS Windows Vista Business",     // WinVistaB, // 36  // Windows Vista Business
   (const unsigned char *)"MS Windows Vista Enterprise",   // WinVistaE, // 37  // Windows Vista Enterprise
   (const unsigned char *)"MS Windows Vista Ultimate",     // WinVistaU, // 38  // Windows Vista Ultimate
   (const unsigned char *)"MS Windows Server 2008",        // Win2008s,  // 39  // Windows Server 2008 // Windows Server Longhorn

   (const unsigned char *)"MS Windows 7",                  // Win7,      // 40  // Windows 7

   (const unsigned char *)"MS Windows 8",                  // Win8,      // 41  // Windows 8
   (const unsigned char *)"MS Windows 8.1",                // Win81,     // 42  // Windows 8

   (const unsigned char *)"MS Windows 10",                 // Win10,     // 43  // Windows 8

   (const unsigned char *)"MS Windows Future NT based",    // WinNtFuture,//44 // common Windows NT based future versions
};

MSWin32Version iWindowsVersion = WinUnkn;
MSWin32Version iWindowsVersionCut = WinUnkn;
int iWindowsSP = 0;
KP_OSVERSIONINFOEX Osvi;

// --------------
HINSTANCE hKpInstance = NULL;
DWORD iKpMainThread = 0;
bool bAdminFl = False;
HWND hMouseOverWnd = NULL;
int ToolTipTimer = 0;
int ToolTipKillTimer = 0;
HWND hToolTip = NULL;
HMODULE hRichEditLib = NULL;
DWORD volatile lKphp11ThreadId = 0L;
KpWndList KpWndListObj;


// ==================================================================
// ---------------------- TYP_ListBoxTree/TYP_ListBoxTreeInverted icons
HBITMAP hbmpNodeBypass = 0;      // KP_IDI_NODE_BYPASS_BMP
HBITMAP hbmpNodeBypassEmpty = 0; // KP_IDI_NODE_BYPASS_EMPTY_BMP
HBITMAP hbmpNodeBottom = 0;      // KP_IDI_NODE_BOTTOM_BMP
HBITMAP hbmpNodeBottomLast = 0;  // KP_IDI_NODE_BOTTOM_LAST_BMP
HBITMAP hbmpNodeOpen = 0;        // KP_IDI_NODE_OPEN_BMP
HBITMAP hbmpNodeOpenLast = 0;    // KP_IDI_NODE_OPEN_LAST_BMP
HBITMAP hbmpNodeClosed = 0;      // KP_IDI_NODE_CLOSED_BMP
HBITMAP hbmpNodeClosedLast = 0;  // KP_IDI_NODE_CLOSED_LAST_BMP

// ---------------------- TYP_ListBoxChk icons
HBITMAP hbmpChecked = 0;      // KP_IDI_CHECKED_BMP
HBITMAP hbmpUnChecked = 0;    // KP_IDI_UNCHECKED_BMP

#if FALSE
COLORREF KpColorSchemeVista[KpNumOfShadows3]={
RGB(200,200,200), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor,   // URL nuorodos spalva
};

COLORREF KpColorSchemeXP[KpNumOfShadows3]={
RGB(236,233,216), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor,   // URL nuorodos spalva
};

COLORREF KpColorScheme2k[KpNumOfShadows3]={
RGB(214,211,206), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor,   // URL nuorodos spalva
};

COLORREF KpColorScheme[KpNumOfShadows3]={ // Win98
RGB(191,191,191), // RGB(236,233,216), // RGB_Gray,      // KpShadowNorm,  // normal (gray) background - normalus fonas
RGB_White,     // KpShadowLight, // light background - sviesus seseliai, sviesus tekstas
RGB_Black, // RGB_Darkgray,  // KpShadowDark,  // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
RGB_Black,     // KpShadowBlack, // black background - juodi seseliai
RGB_Gray,      // KpShadowBackground, // fonas apie mygtuka etc.
RGB_Gray,      // KpShadowForeground, // paties mygtuko, etc. fonas
RGB_Darkblue,  // KpCaptionColor, // lango antrastes spalva
RGB_Blue,      // KpLinkColor,   // URL nuorodos spalva
};
#endif

// HBRUSH KpWhiteBrush = NULL; // (HBRUSH)COLOR_3DHILIGHT; // (HBRUSH)iaColorMap[KpShadowLight]; // (HBRUSH)COLOR_3DFACE; // COLOR_APPWORKSPACE, // COLOR_BACKGROUND, // (HBRUSH)iaColorMap[KpShadowNorm];

#if FALSE
HPEN aPenSchemeWin[KpNumOfShadows3] =
{
   NULL, // KpShadowNorm
   NULL, // KpShadowLight
   NULL, // KpShadowDark
   NULL, // KpShadowBlack
   NULL, // KpShadowBackground
   NULL, // KpShadowForeground
   NULL, // KpCaptionColor
   NULL, // KpLinkColor
};
#endif

int iaColorMap[KpNumOfShadows3] =
{
   COLOR_3DFACE, // COLOR_3DLIGHT, // COLOR_APPWORKSPACE, // COLOR_BACKGROUND, // KpShadowNorm
   COLOR_3DHILIGHT, // KpShadowLight
   COLOR_WINDOWTEXT, // COLOR_3DSHADOW, // KpShadowDark
   COLOR_3DDKSHADOW, // KpShadowBlack
   COLOR_3DFACE, // COLOR_BTNSHADOW, // KpShadowBackground
   COLOR_3DFACE, // COLOR_BTNFACE, // KpShadowForeground
   COLOR_ACTIVECAPTION, // KpCaptionColor
   COLOR_3DDKSHADOW, // KpLinkColor
};


// ==================================================================
// ------------------------------------------
HRESULT KpInitWindows(HINSTANCE hKpInst)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HINSTANCE hinst=NULL;
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
INITCOMMONCONTROLSEX init_ctrls;
#endif
HKEY key = NULL;
LONG retw = ERROR_SUCCESS;
#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangRu_p))
DWORD buf_len;
unsigned char key_buf[KP_KWD_LEN + 1];
DWORD val_type;
#endif
const unsigned char *env_par;

   if(StackTop == NULL) StackTop = &hKpInst;

   if(SUCCEEDED(retc)) retc = KpInit();

// ------------------------
   iKpMainThread = GetCurrentThreadId();
// KP_TRACE_1("KpInitWindows(): iKpMainThread: %d", iKpMainThread);

// ------------------------
   hinst = hKpInst;
   if(hinst == NULL) hinst = GetModuleHandle(NULL);

   if(hKpInstance == NULL) // tik pirm? kart?
   {
      if(SUCCEEDED(retc)) retc = KpGetSystemVersion(&iWindowsVersion, &iWindowsSP);

// ---------------------
//    if(SUCCEEDED(retc)) retc = LoadUnicowsProc();

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// Ensure that the common-control DLL is loaded.
// used for, by instance, WC_TREEVIEW controls
//    InitCommonControls();
      init_ctrls.dwSize=sizeof(init_ctrls);
      init_ctrls.dwICC=ICC_TREEVIEW_CLASSES;
      if(SUCCEEDED(retc))
         if(!InitCommonControlsEx(&init_ctrls))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

      if(SUCCEEDED(retc))
      {
         env_par = (const unsigned char *)getenv("KP_CRASH_TEST");
         if(env_par) if(strcmp(env_par, "TRUE") == 0) KP_ERROR(KP_E_SYSTEM_ERROR, null);
      }
   }
   hKpInstance = hinst;

   if(SUCCEEDED(retc)) retc=TestAdmin(&bAdminFl);

#ifdef MsgLang
   if(SUCCEEDED(retc))
   {
#  if (MsgLang == KpLangNo_p)
      iMsgLangOff = KpLangEn;

#  elif (MsgLang == KpLangSel_p)
      KP_ERROR(E_NOTIMPL, null);

#  elif ((MsgLang == KpLangEn_p) || (MsgLang == KpLangLt_p) || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))
      iMsgLangOff = (KpLang)MsgLang;

#  elif ((MsgLang == KpLangPl_p) || (MsgLang == KpLangRu_p))
      retc0 = S_OK;
      if(SUCCEEDED(retc0))
      {
         retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Nls\\CodePage", 0, KEY_QUERY_VALUE, &key);
         if(retw != ERROR_SUCCESS)
         {
            retc0 = KP_E_KWD_NOT_FOUND;
            KP_WARNING(retc0, retw);
         }
      }
      if((key == NULL) && SUCCEEDED(retc0))
      {
         retc0 = KP_E_SYSTEM_ERROR;
         KP_WARNING(retc0, null);
      }
      if(SUCCEEDED(retc0))
      {
         buf_len = KP_KWD_LEN;
         retw = RegQueryValueEx(key, "ACP", NULL, &val_type, key_buf, &buf_len);
         if(retw != ERROR_SUCCESS)
         {
            retc0 = KP_E_KWD_NOT_FOUND;
            KP_WARNING(retc0, retw);
         }
      }
      if((val_type != REG_SZ) && SUCCEEDED(retc0))
      {
         retc0 = KP_E_KWD_NOT_FOUND;
         KP_WARNING(retc0, retw);
      }
      if(SUCCEEDED(retc0))
      {
         key_buf[buf_len] = Nul;
         CutInitTrailSpcs(key_buf);
#     if (MsgLang == KpLangPl_p)
         if(strcmp(key_buf, "1257") == 0) iMsgLangOff = KpLangPl_1257;
         else /* if(strcmp(key_buf, "1250") == 0) */  iMsgLangOff = KpLangPl_1250;

#     elif (MsgLang == KpLangRu_p)
         if(strcmp(key_buf, "1251") == 0) iMsgLangOff = KpLangRu_1251;
         else iMsgLangOff = KpLangRu_0;

#     else
         KP_ERROR(E_INVALIDARG, null);
#     endif
      }
      if(key) RegCloseKey(key);
      key = NULL;

#  else
      KP_ERROR(E_INVALIDARG, null); break;

#  endif // #  elif ((MsgLang == KpLangPl_p) || (MsgLang == KpLangRu_p))

   } // if(SUCCEEDED(retc))
#endif // #ifdef MsgLang

   KP_ASSERT((iMsgLangOff >= 0) && (iMsgLangOff < KpNumOfLangs), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = InitWindowPars();

   if(SUCCEEDED(retc)) retc = InitPalette();

return(retc);
}


HRESULT KpFinitWindows(void)
{
HRESULT retc = S_OK;

#if FALSE
int ii;

   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
      if(aPenSchemeWin[ii]!=NULL)
         if(!DeleteObject(aPenSchemeWin[ii]))
         {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
         }
      aPenSchemeWin[ii]=NULL;
   }
#endif

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(retc);
}


/////////////////////////////////////////////////////////////////////////////
// kpmsg inplementation
#if 0

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)

kpmsg::kpmsg(const unsigned char *lpszOutStr, CWnd* pParent /*=NULL*/)
        : CDialog(kpmsg::IDD, pParent)
{
   lhOpenResult=S_OK;

   if(strlen(lpszOutStr)>KP_MAX_FILE_LIN_WDT) lhOpenResult=E_INVALIDARG;

   strncpy(m_lpszOutStr, lpszOutStr, KP_MAX_FILE_LIN_WDT);
   m_lpszOutStr[KP_MAX_FILE_LIN_WDT]=Nul;

   //{{AFX_DATA_INIT(kpmsg)
                // HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
        //}}AFX_DATA_INIT

}


HRESULT kpmsg::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
BOOL kpmsg::OnInitDialog()
{
        CDialog::OnInitDialog();
//
//      // Symbol für dieses Dialogfeld festlegen. Wird automatisch erledig
//      //  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
//      SetIcon(m_hIcon, TRUE);                 // Großes Symbol verwenden
//      SetIcon(m_hIcon, FALSE);                // Kleines Symbol verwenden
//
//      // ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
   SetDlgItemText(IDC_EDIT1, (const char *)m_lpszOutStr);

return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}


void kpmsg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(kpmsg)
                // HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(kpmsg, CDialog)
        //{{AFX_MSG_MAP(kpmsg)
                // HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten kpmsg

#endif

#endif

// -----------------------------------------
HRESULT ManageToolTipTimer(void)
{
HRESULT retc=S_OK;

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

   if(ToolTipTimer && SUCCEEDED(retc)) if(!KillTimer(HWND_DESKTOP, ToolTipTimer))
   {
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
   }
   ToolTipTimer=0;

   if(ToolTipKillTimer && SUCCEEDED(retc)) if(!KillTimer(HWND_DESKTOP, ToolTipKillTimer))
   {
#ifdef Debug
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
   }
   ToolTipKillTimer=0;

   if(hMouseOverWnd && SUCCEEDED(retc))
   {
      ToolTipTimer = SetTimer(HWND_DESKTOP, KPW_TOOLTIP_TIMER, KPW_TOOLTIP_TIMEOUT, NULL);
#ifdef Debug
      if(ToolTipTimer == 0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
   }
#if FALSE
char str_buf[100];
sprintf(str_buf, "%d", ToolTipTimer);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

return(retc);
}


// -----------------------------------------
HMODULE hUnicowsLib=NULL;
//
// HRESULT LoadUnicowsProc(void)
// {
// HRESULT retc=S_OK;
//
// if(hUnicowsLib==NULL)
// {
//    hUnicowsLib=LoadLibraryA("unicows.dll")
//    if(hUnicowsLib==NULL)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// }
//
// return(retc);
// }


// ----------------------------------------- KpWnd implementation
KpWndList::KpWndList(void)
{
   m_W_first=NULL;
}

KpWndList::~KpWndList()
{
DeleteList();
}

void KpWndList::DeleteList()
{
HRESULT retc = S_OK;
KpWnd *cur_wnd;
KpWnd *next_wnd;

// KP_DELETE(m_W_first); // !!! only certain types of windows must be deleted

   cur_wnd = m_W_first;
   while(cur_wnd)
   {
      m_W_first = next_wnd = cur_wnd->m_pNextWindow;

      switch(cur_wnd->m_iWndType)
      {
         case TYP_Static:
         case TYP_MDI_Frame:
         case TYP_ListBox:
//       case TYP_SubListBox:
         case TYP_ListBoxTree:
         case TYP_ListBoxTreeInverted:
         case TYP_ListBoxChk:
         case TYP_Button:
//       case TYP_KpBitmap:
         case TYP_KpBitmapCtrl:
// PutLogMessage_("KpWndList::DeleteList() %d", cur_wnd->m_iWndType);
            KP_DELETE(cur_wnd);
            break;

         case TYP_KpProgressWndw: // !!!! TODO: ðità gal ir reiktø trint, jeigu ShowBmp() slankiklis tvarkomas ne ðituo tipu; tada panaikint iðmetimà ið KillProgressWnd()
         case TYP_KpDialog:
            cur_wnd->DestroyWindow();
// netrinam – èia yra iBshDlg langas, bus iðtrintas vëliau.
//          KP_DELETE(cur_wnd);
            break;
      }

      cur_wnd = next_wnd;
   }
}


KpWnd::KpWnd(void)
{
   InitMembers();
}


KpWnd::KpWnd
(
HWND hWnd,
KpWndType iWndType,
const unsigned char *lpszWndText,
HWND hParent,
HINSTANCE hInstance,
HFONT hFont,
HICON hIcon,
KpControlStyles iKpCtrlStyle,
int iWdt, int iHgt,
int iNumOfCols, int iNumOfRows,
DWORD dwExStyle, DWORD dwStyle,
HWND hMDI_Client,
HWND hBitmapCtrl,
HBITMAP hBitMap,
int iBitmapCnt,
unsigned char **plpszBmpList,
int *iaBmpTimes,
int iParentWdt, int iParentHgt,
long lFullSliderSize
)
{
HRESULT retc = S_OK;

   InitMembers();

#if TRUE // Envir==MSWin32
   m_hWndHandle=hWnd;
#endif
// PutLogMessage_("HWND KpWnd::KpWnd() m_hWndHandle %x", m_hWndHandle);

   m_iWndType = iWndType;

   m_lpszWndText[0] = Nul;
   if(lpszWndText != NULL)
   {
      if(strlen(lpszWndText) >= KP_MAX_FILE_LIN_LEN)
         retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         strncpy(m_lpszWndText, lpszWndText, KP_MAX_FILE_LIN_LEN);
         m_lpszWndText[KP_MAX_FILE_LIN_LEN] = Nul;
      }
   }

   m_hParent = hParent;

   m_hInstance = hInstance;

   m_hFont = hFont;
   m_hIcon = hIcon;
   m_iKpCtrlStyle = iKpCtrlStyle;

// -----------------------
   m_iWdtDots = iWdt;
   m_iHgtDots = iHgt;

   m_iWndX_10 = m_iWndX * 10;
   m_iWndY_10 = m_iWndY * 10;

// -----------------------
   m_iNumOfCols = iNumOfCols;
   m_iNumOfRows = iNumOfRows;

   m_dwExStyle = dwExStyle;
   m_dwStyle = dwStyle;

   m_hMDI_Client = hMDI_Client;

// PutLogMessage_("KpWnd::KpWnd() %x %d", this, m_iWndType);
// KP_STACK_DUMP;
   if(SUCCEEDED(retc)) retc = InitBmpMembers(hBitmapCtrl, hBitMap, iBitmapCnt, plpszBmpList, iaBmpTimes, iParentWdt, iParentHgt);

// -----------------------
   CalcSliderSteps(Maxint); // 0);

   m_lFullSliderSize = lFullSliderSize;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;
}


HRESULT KpWnd::InitMembers(void)
{
   m_lhOpenResult=S_OK;
   m_iWndType=TYP_KpWnd;
   m_hParent=NULL;
   m_pNextWindow=NULL;
#if TRUE // Envir==MSWin32
   m_hWndHandle=NULL;
#endif
   m_hInstance=NULL;
   m_lpszWndText[0]=Nul;
   m_hFont=NULL;
   m_hIcon=NULL;
   m_iKpCtrlStyle=KPW_CONTROL_STYLE_NORMAL;

   m_iWndX = 0;
   m_iWndY = 0;

   m_iWdtDots = KPW_BMP_WDT;
   m_iHgtDots = KPW_SLIDER_HGT;

   m_iParentWdtDots = KPW_BMP_WDT;
   m_iParentHgtDots = KPW_BMP_HGT;

   m_iNumOfCols = m_iWdtDots*(((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?9:10)/iaCtrlTextFactors[m_iKpCtrlStyle];
   m_iNumOfRows = m_iHgtDots/iaCtrlRowHeights[iWindowsVersionCut][m_iKpCtrlStyle];

   m_dwExStyle = 0L;
   m_dwStyle = 0L;

   m_hMDI_Client = 0;

   m_pFontFmt = NULL;

   m_hSubListBox = NULL;
   m_hSubLBoxScrollBar = NULL;

   m_pEntries = NULL;

   m_plpszListEntries = NULL;
   m_iNumOfListEntries = 0;
   m_iListEntriesCount = 0;
   m_lpszListEntriesBuf = NULL;
   m_iListEntriesBufSize = 0;

   m_iCurSel = (-1);
   m_iCurStartEntry = (-1);

   m_hBmpReleased = NULL;
   m_hdcReleased = NULL;
   m_hBmpIlluminated = NULL;
   m_hdcIlluminated = NULL;
   m_hBmpPressed = NULL;
   m_hdcPressed = NULL;

// m_hPenScheme = NULL;
   m_iaColorScheme = NULL;

   m_bPressed = False;

   m_pBmpPars = NULL;

// i?kelti ? m_pBmpPars
// m_hBitmapCtrl = NULL;
// m_iBitmapCnt = 0;
// m_plpszBmpList = NULL;
// m_iaBmpTimes = NULL;

   m_phBmpList = NULL;
   m_iCurBmp = 0;

   m_lFullSliderSize = 10000L;
   m_lCurSliderPos = 0;
   m_lCurFileStartPos = 0;

return(m_lhOpenResult);
}


HRESULT KpWnd::InitBmpMembers(HWND hBitmapCtrl, HBITMAP hBitMap, int iBitmapCnt, unsigned char **plpszBmpList, int *iaBmpTimes, int iBmpWdt, int iBmpHgt)
{
HRESULT retc = m_lhOpenResult;

KpBmpData *bmp_pars = NULL;

   KP_NEW(bmp_pars, KpBmpData(iBmpWdt, iBmpHgt));
// PutLogMessage_("KpWnd::InitBmpMembers() %? %? %d", bmp_pars, this, m_iWndType);
// KP_STACK_DUMP;

   if(SUCCEEDED(retc))
   {
      bmp_pars->m_hBitmapCtrl = hBitmapCtrl;
      bmp_pars->m_iBitmapCnt = iBitmapCnt;
      bmp_pars->m_plpszBmpList = plpszBmpList;
      bmp_pars->m_iaBmpTimes = iaBmpTimes;

//    bmp_pars->m_iBmpWdt = iBmpWdt;
//    bmp_pars->iBmpHgt = iBmpHgt;

      bmp_pars->m_hBitMap = hBitMap;

      retc = InitBmpMembers(bmp_pars);
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;

return(retc);
}


HRESULT KpWnd::InitBmpMembers(KpBmpData *pBmpPars)
{
HRESULT retc = m_lhOpenResult;

   KP_DELETE(m_pBmpPars);
   KP_DELETEA(m_phBmpList);

   if(SUCCEEDED(retc))
   {

      m_pBmpPars = pBmpPars;

      if(m_pBmpPars != NULL)
      {
         m_iParentWdtDots = m_pBmpPars->m_iBmpWdt;
         m_iParentHgtDots = m_pBmpPars->m_iBmpHgt;

         if(m_pBmpPars->m_iBitmapCnt > 1) KP_NEWA(m_phBmpList, HBITMAP, m_pBmpPars->m_iBitmapCnt)
         else KP_NEWA(m_phBmpList, HBITMAP, 1);

// PutLogMessage_("new\t%x\tKpWnd::InitBmpMembers() m_phBmpList", m_phBmpList);

         if(SUCCEEDED(retc))
         {
            m_phBmpList[0] = m_pBmpPars->m_hBitMap;
            for(int ii = 1; ii < m_pBmpPars->m_iBitmapCnt; ii++) m_phBmpList[ii] = NULL;
         }
      }
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = retc;

return(retc);
}


HRESULT KpWnd::GetOpenResult(void)
{
return(m_lhOpenResult);
}


KpWnd::~KpWnd(void)
{
// PutLogMessage_("KpWnd::~KpWnd() %x", this);
   KpWndDestructor();
}


HRESULT KpWnd::KpWndDestructor(void)
{
HRESULT retc = S_OK;

   retc = DestroyWindow();

   KP_DELETEA(m_plpszListEntries);
   m_iNumOfListEntries = 0;
   m_iListEntriesCount = 0;
   KP_DELETEA(m_lpszListEntriesBuf);
   m_iListEntriesBufSize = 0;

   if(m_hFont) DeleteObject(m_hFont);
   m_hFont = 0;

// ----------------------
   if(m_hBmpReleased != NULL)
      if(!DeleteObject(m_hBmpReleased))
      {
#ifdef Debug
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hBmpReleased=NULL;
   if(m_hdcReleased != NULL)
      if(!DeleteDC(m_hdcReleased))
      {
#ifdef Debug
         /* retc = */KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hdcReleased = NULL;

   if(m_hBmpIlluminated != NULL)
      if(!DeleteObject(m_hBmpIlluminated))
      {
#ifdef Debug
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hBmpIlluminated = NULL;
   if(m_hdcIlluminated != NULL)
      if(!DeleteDC(m_hdcIlluminated))
      {
#ifdef Debug
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hdcIlluminated = NULL;

   if(m_hBmpPressed != NULL)
      if(!DeleteObject(m_hBmpPressed))
      {
#ifdef Debug
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hBmpPressed = NULL;
   if(m_hdcPressed != NULL)
      if(!DeleteDC(m_hdcPressed))
      {
#ifdef Debug
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hdcPressed = NULL;

// --------------------------------
   if(m_phBmpList != NULL)
   {
      KP_ASSERT(m_pBmpPars != NULL, E_POINTER, null, False);
      if(m_pBmpPars != NULL)
      {
         for(int ii = 0; ii < m_pBmpPars->m_iBitmapCnt; ii++) if(m_phBmpList[ii])
            KP_ASSERT(DeleteObject(m_phBmpList[ii]), KP_E_SYSTEM_ERROR, GetLastError(), False);
         KP_DELETEA(m_phBmpList);
      }
   }

   KP_DELETE(m_pBmpPars);

return(retc);
}


HRESULT KpWnd::DestroyWindow(void)
{
HRESULT retc=S_OK;

   if(m_hMDI_Client != NULL)
   {
HWND wnd = m_hMDI_Client;
      m_hMDI_Client = NULL;

      ::DestroyWindow(wnd);
   }

#if TRUE // Envir==MSWin32
   if(m_hWndHandle!=NULL)
   {
HWND wnd = m_hWndHandle;
      m_hWndHandle = NULL;

      if(!(::DestroyWindow(wnd)))
      {
// blogai, jei jau sunaikintas - iskraudami procesa windowsai automatiskai naikina visus child
// langus, o jei uzdarinejam tik child thread'a, child langa reikia uzdaryti paciam
//       /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
//    if(SUCCEEDED(retc)) retc=KpSleep(500, HWND_DESKTOP); // Sleep(5000);

// PutLogMessage_("HWND KpWnd::DestroyWindow() m_hWndHandle %x", wnd);
   }

   switch(m_iWndType)
   {
   case TYP_KpConsole:
   case TYP_Trace:
      (static_cast<KpConsole *>(this))->m_hDisplayCtrl=NULL;
      break;
   }
#endif

return(retc);
}

HRESULT WndPreg(
                  KpWnd *pWndPnt,
                  KpWndType iWndType,
                  HINSTANCE hInstance,
                  const unsigned char *
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
                     lpszLogFileName
#endif
                     ,
                  bool bOpenWindow
               )
{
HRESULT retc=S_OK;
KpWnd *last_wnd;

   if(KpWndListObj.m_W_first==NULL) KpWndListObj.m_W_first=pWndPnt;
   else
   {
      last_wnd=KpWndListObj.m_W_first;
      while(last_wnd->m_pNextWindow!=NULL) last_wnd=last_wnd->m_pNextWindow;
      last_wnd->m_pNextWindow=pWndPnt;
   }

   if(pWndPnt!=NULL)
   {
      pWndPnt->m_hInstance=hInstance;
      pWndPnt->m_iWndType=iWndType;

      if(bOpenWindow && SUCCEEDED(retc)) switch(iWndType)
      {
      case TYP_KpConsole:
      case TYP_Trace:
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
         retc=(static_cast<KpConsole *>(pWndPnt))->Init(hInstance, lpszLogFileName);
#endif
         break;
      }
   }

return(retc);
}


HRESULT DeleteWnd(const KpWnd *pWndPnt)
{
HRESULT retc=S_OK;
KpWnd *prev_wnd;
KpWnd *cur_wnd;
bool found;

   cur_wnd=KpWndListObj.m_W_first;
   prev_wnd=NULL;
   found=False;
   while(cur_wnd)
   {
      if(cur_wnd==pWndPnt)
      {
         if(prev_wnd) prev_wnd->m_pNextWindow=cur_wnd->m_pNextWindow;
         else KpWndListObj.m_W_first=cur_wnd->m_pNextWindow;

         cur_wnd->m_pNextWindow=NULL;
         found=True;
         break;
      }
      prev_wnd=cur_wnd;
      cur_wnd=cur_wnd->m_pNextWindow;
   }

   if(!found)
      retc=KpErrorProc.OutputErrorMessage(KP_E_OBJ_NOT_FOUND, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(cur_wnd->m_iWndType)
   {
      case TYP_Static:
      case TYP_MDI_Frame:
      case TYP_ListBox:
//    case TYP_SubListBox:
      case TYP_ListBoxTree:
      case TYP_ListBoxTreeInverted:
      case TYP_ListBoxChk:
      case TYP_Button:
//    case TYP_KpBitmap:
      case TYP_KpBitmapCtrl:
// PutLogMessage_("DeleteWnd()");
         KP_DELETE(cur_wnd);
         break;

      case TYP_KpProgressWndw: // !!!! TODO: ðità gal ir reiktø trint, jeigu ShowBmp() slankiklis tvarkomas ne ðituo tipu; tada panaikint iðmetimà ið KillProgressWnd()
      case TYP_KpDialog:
         cur_wnd->DestroyWindow();
// netrinam – èia yra iBshDlg langas, bus iðtrintas vëliau.
//       KP_DELETE(cur_wnd);
         break;
   }

return(retc);
}


#if TRUE // Envir==MSWin32
HRESULT GetCurWindow(KpWnd **pCurWnd, HWND hWndHandle)
{
HRESULT retc = S_OK;
KpWnd *retval = NULL;

   if(pCurWnd==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      retval=KpWndListObj.m_W_first;
      while(retval!=NULL)
      {
         if(retval->m_hWndHandle == hWndHandle) break;
         retval = retval->m_pNextWindow;
      }

      *pCurWnd=retval;
   }

#if FALSE
if(retval == NULL)
{
HRESULT retc0 = S_OK;
PutLogMessage_("HWND GetCurWindow hWndHandle %x", hWndHandle);
KP_ASSERT0E(retval != NULL, KP_E_OBJ_NOT_FOUND, null, False);
// KpErrorProc.lhLastRetc = S_OK; // numuðam apsaugà nuo pasikartojimo – kad bûtø galima siøsti pakartotinai
}
#endif

return(retc);
}
#endif


HRESULT GetCurChildWindow(KpWnd **pCurWnd, HWND hWndHandle)
{
HRESULT retc=S_OK;
KpWnd *retval=NULL;

   if(pCurWnd==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      retval=KpWndListObj.m_W_first;
      while(retval!=NULL)
      {
         if(retval->m_hMDI_Client==hWndHandle) break;
         retval=retval->m_pNextWindow;
      }

      *pCurWnd=retval;
   }

return(retc);
}


HRESULT GetWindowsCount(int *piWndCnt)
{
HRESULT retc=S_OK;
int ii;
KpWnd *cur_wnd=NULL;

   if(piWndCnt==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      ii=0;
      cur_wnd=KpWndListObj.m_W_first;
      while(cur_wnd!=NULL)
      {
         cur_wnd=cur_wnd->m_pNextWindow;
         ii++;
      }

      *piWndCnt=ii;
   }

return(retc);
}


// -----------------------------
#if TRUE // FALSE
HRESULT KpWnd::SetListEntriesCount(int iListEntriesCount)
{
HRESULT retc = S_OK;
int ii;

   if(((iListEntriesCount < 0) || (iListEntriesCount > m_iNumOfListEntries)) && SUCCEEDED(retc))
   {
char str_buf[100];
      sprintf(str_buf, "%d %d", iListEntriesCount, m_iNumOfListEntries);
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, str_buf, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(((m_plpszListEntries == NULL) || (m_lpszListEntriesBuf==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      m_iListEntriesCount = iListEntriesCount;

      m_lpszListEntriesBuf[0] = Nul;
      for(ii = 0; ii < m_iListEntriesCount; ii++)
         m_plpszListEntries[ii] = m_lpszListEntriesBuf;
   }

   if(SUCCEEDED(retc)) retc=SetListBoxSel(m_hWndHandle, m_iCurSel);

   if(SUCCEEDED(retc)) if(!InvalidateRect(m_hWndHandle, NULL, True))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

return(retc);
}
#endif


// -----------------------------
HRESULT KpWnd::ResetListBoxContents(int iMaxNumOfEntries, int iEntrySize, bool bSetEntries, KpTreeEntry *pEntries)
{
HRESULT retc = S_OK;
KpTreeEntry *entries_sav=NULL;
int cur_sel_sav = 0;
int retv;

   KP_ASSERT(iEntrySize >= 0, E_INVALIDARG, null, True);
   KP_ASSERT(m_hWndHandle !=NULL, KP_E_SYSTEM_ERROR, null, True);

int entr_num = 0;
   if((pEntries != NULL) && SUCCEEDED(retc)) retc = pEntries->CountEntries(&entr_num, (m_iWndType==TYP_ListBoxTree)?1:0, pEntries);

int max_entr_num = iMaxNumOfEntries;
   if((max_entr_num < 0) && SUCCEEDED(retc))
   {
      KP_ASSERT(pEntries != NULL, E_INVALIDARG, null, True);
      max_entr_num = entr_num;
   }

   if(SUCCEEDED(retc))
   {
      entries_sav = m_pEntries;
      cur_sel_sav = m_iCurSel;
   }

   if(SUCCEEDED(retc))
      if(SendMessage(m_hWndHandle, LB_RESETCONTENT, 0, 0L) == CB_ERR)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// if(SUCCEEDED(retc)) retc = ResetListBoxContents(list_field, iNumOfRows, 300 /* lbox_wdt */, False, pEntries);

   if(SUCCEEDED(retc))
   {
      retv=SendMessage(m_hWndHandle, LB_INITSTORAGE, max_entr_num, max_entr_num*iEntrySize);
      if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
      if((retv==LB_ERR) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) m_pEntries = entries_sav;

   if(bSetEntries && SUCCEEDED(retc)) m_pEntries = pEntries;

   if(SUCCEEDED(retc)) if(m_pEntries)
   {
      retv = SendMessage(m_hWndHandle, KP_LB_SETSTRINGLIST, 0, (LPARAM)m_pEntries);
      switch(retv)
      {
      case CB_ERR:
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
      case CB_ERRSPACE:
         retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
      }

      if(((m_lpszListEntriesBuf == NULL) || (m_plpszListEntries == NULL)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

      entr_num = 0; // jei !bSetEntries, tada reikia ankstesnio m_pEntries element¸ skai?ius, pEntries naudojamas tik kaip ?ablonas ?ra?¸ skai?iui nustatyti
      if((m_pEntries != NULL) && SUCCEEDED(retc)) retc = m_pEntries->CountEntries(&entr_num, (m_iWndType==TYP_ListBoxTree)?1:0, m_pEntries);

      if(SUCCEEDED(retc))
      {
         m_iListEntriesCount = entr_num;

         m_lpszListEntriesBuf[0] = Nul;
         for(int ii = 0; ii < m_iListEntriesCount; ii++)
            m_plpszListEntries[ii] = m_lpszListEntriesBuf;
      }
   }

   if(SUCCEEDED(retc)) retc = SetListBoxSel(m_hWndHandle, cur_sel_sav /* m_iCurSel */);

   if(SUCCEEDED(retc)) if(!InvalidateRect(m_hWndHandle, NULL, True))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

return(retc);
}


HRESULT ResetListBoxContents(HWND hWnd, int iMaxNumOfEntries, int iEntrySize, bool bSetEntries, KpTreeEntry *pEntries)
{
HRESULT retc = S_OK;
KpWnd *cur_wnd=NULL;

   if(SUCCEEDED(retc))
   {
      retc = GetCurWindow(&cur_wnd, hWnd);
      if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) retc = cur_wnd->ResetListBoxContents(iMaxNumOfEntries, iEntrySize, bSetEntries, pEntries);

return(retc);
}


// ----------------------------------------------- common functions
HRESULT KpMsgOut(
                  const unsigned char *lpszOutStr,
                  LPCTSTR
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
                     lpszIconID
#endif
                  ,
                  KpMsgTypes
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
                     iMsgType
#endif
                  , int
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
                     iTimeOut
#endif
                  , KpAlignments
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
                     iAlign
#endif
                  , HWND *
#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
                  phDialogWnd
#endif
                  )
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
WNDCLASSEX wcx;
HWND dlg_wnd = NULL;
int wnd_x = 0;
int wnd_y = 0;
int wnd_dx = 0;
int wnd_dy = 0;
int msg_x = 0;
int msg_y = 0;
int msg_dx = 0;
int msg_dy = 0;
int but_x = 0;
int but_y = 0;
int but1_x = 0;
int but1_y = 0;
int but2_x = 0;
int but2_y = 0;
int msg_lines = 1;
MSG msg;
int retp;
DWORD ex_style = 0L;
DWORD style = 0L;
bool endfl = False;
HICON icon = NULL;
// KpWnd *wnd_ptr = NULL;
UINT close_timer = 0;
#endif
#if (Envir == MSWin32) || (Envir == MSWin32Mfc)
HBRUSH brush;
// HPEN pen = NULL;
// EXTLOGPEN log_pen;
#endif

// kpmsg *msg_ptr;
unsigned char *msg_ptr = null;
KpMsgData *msg_data_ptr = NULL;

#ifdef Debug
#if (Envir == MSWin32) || (Envir == MSWin32Mfc)
// unsigned char str_buf[KP_MAX_FNAME_LEN + 100];
#endif
#endif

   if((lpszOutStr != NULL) && (!bServiceFl))
   {
#if (Envir == MSWin32) || (Envir == MSWin32Mfc)


#if FALSE

      if(pMainWindow != NULL) KP_NEWO(msg_ptr, kpmsg(lpszOutStr, pMainWindow))
      else KP_NEWO(msg_ptr, kpmsg(lpszOutStr));

      if(SUCCEEDED(retc))
      {
         msg_ptr->DoModal();
         msg_ptr->DestroyWindow();
      }

      KP_DELETE(msg_ptr);

      if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP); // Sleep(100);


#else // #if FALSE

      if(SUCCEEDED(retc))
      {
// ------------------------------
         if(hKpInstance==NULL)
         {
//          ::MessageBox(NULL, (const char *)lpszOutStr, (const char *)KP_MSG_TITLE, MB_OK);
            ::MessageBoxEx(NULL, (const char *)lpszOutStr, (const char *)KP_MSG_TITLE, MB_OK, LANG_LITHUANIAN /* LANG_ENGLISH */);
         }

         else
         {

// ------------------------------
            brush = NULL;

#  if FALSE
            pen = NULL;

            if(SUCCEEDED(retc))
            {
               pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#  else
            brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));
#  endif

// --------------------------
            if(SUCCEEDED(retc))
            {
// gali buti tik standartines ikonos
// jei noresiu kitokiu - reiks dar vieno parametro - hInst
               icon = LoadIcon(NULL /* hKpInstance */, lpszIconID);
               if(icon == NULL)
               {
#ifdef Debug
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
                  retc = KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, icon: %d, inst: %d, File: %s line: %d", lpszIconID, hKpInstance, __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
               }
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "KpMsgOut icon:%d", icon);
KP_TRACE(str_buf);
#endif
            }

// ------------------------------
            if(SUCCEEDED(retc))
            {
               wcx.hInstance     = hKpInstance;
               wcx.lpszClassName = "KPMSG",
               wcx.lpfnWndProc   = (WNDPROC)KpMsgDialogProc;
               wcx.style         = CS_DBLCLKS;
               wcx.cbSize        = sizeof(WNDCLASSEX);
               wcx.hIcon         = icon; // LoadIcon(NULL /* hKpInstance */, IDI_INFORMATION /* IDI_ASTERISK */); // MAKEINTRESOURCE(/* lpszIconID */ IDI_INFORMATION /* IDI_ASTERISK */));
               wcx.hIconSm       = icon; // LoadIcon(NULL /* hKpInstance */, IDI_INFORMATION /* IDI_ASTERISK */); // MAKEINTRESOURCE(/* lpszIconID */ IDI_INFORMATION /* IDI_ASTERISK */));
               wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
               wcx.lpszMenuName  = 0;
               wcx.cbClsExtra    = 0;
               wcx.cbWndExtra    = 0;
               wcx.hbrBackground = brush; // (HBRUSH)iaColorMap[KpShadowNorm];

               if(!RegisterClassEx(&wcx))
               {
                  long ll = GetLastError();
                  if(ll != ERROR_CLASS_ALREADY_EXISTS)
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL, False);
               }

            }

//          if(brush) if(!DeleteObject(brush))
//             /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            brush = NULL;

// ------------------------------
            msg_ptr = NULL;
            if(SUCCEEDED(retc))
               retc = CalcMsgPars(lpszOutStr, &msg_ptr, &msg_lines,
                  &msg_x, &msg_y, &msg_dx, &msg_dy, &wnd_x, &wnd_y, &wnd_dx, &wnd_dy,
                  &but_x, &but_y, &but1_x, &but1_y, &but2_x, &but2_y,
                  iAlign);

// --------------------------
            if(SUCCEEDED(retc))
            {
               ex_style = WS_EX_TOPMOST;
               style = WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME; // |WS_BORDER|WS_POPUP
            }
            KP_NEW(msg_data_ptr, KpMsgData);
            if(SUCCEEDED(retc))
            {
               msg_data_ptr->m_iMsgTp = iMsgType;
               msg_data_ptr->m_iAlign = iAlign;
               msg_data_ptr->m_lpszMsgTxt = lpszOutStr;
               msg_data_ptr->m_hIcon = icon;

               dlg_wnd = CreateWindowEx
                  (
                     ex_style,               // DWORD dwExStyle,      // extended window style
                     "KPMSG",
                     (const char *)KP_MSG_TITLE,   // LPCTSTR lpWindowName, // pointer to window name
                     style,                  // DWORD dwStyle,        // window style
                     wnd_x, // CW_USEDEFAULT // int x,               // horizontal position of window
                     wnd_y, // CW_USEDEFAULT // int y,               // vertical position of window
                     wnd_dx,                 // int nWidth,           // window width
                     wnd_dy,                 // int nHeight,          // window height
                     NULL, // HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
                     0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
                     hKpInstance,
                     (LPVOID)msg_data_ptr    // LPVOID lpParam        // pointer to window-creation data
                  );

               if(dlg_wnd==NULL)
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
                  retc=KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
               }
            }

            if((phDialogWnd != NULL) && SUCCEEDED(retc)) *phDialogWnd = dlg_wnd;

// --------------------------
#if FALSE
            if(SUCCEEDED(retc)) if(!SetActiveWindow(dlg_wnd))
            {
#  ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#  endif
            }
#endif

#if FALSE // kurti ir registruoti reikia WM_CREATE evente
            if(SUCCEEDED(retc))
            {
               KP_NEWO(wnd_ptr, KpWnd(dlg_wnd, TYP_KpDialog, KP_MSG_TITLE, NULL, hKpInstance,
                                 NULL, icon, KPW_CONTROL_STYLE_NORMAL, wnd_dx, wnd_dy, 1, 1, ex_style, style, NULL));
               if(FAILED(retc)) KP_DELETE(wnd_ptr);
            }
            if(SUCCEEDED(retc))
            {
               retc = WndPreg(wnd_ptr, TYP_KpDialog /* TYP_Static */, hKpInstance, NULL, False);
#  if FALSE // #ifdef Debug
sprintf((char *)str_buf, "KpMsgOut window: %d %d", dlg_wnd, wnd_ptr);
KP_TRACE(str_buf);
#  endif
            }
#endif

#if FALSE // i?kelta ? WM_CREATE event?
            if(SUCCEEDED(retc))
               retc = KpCreateIcon(hKpInstance, dlg_wnd, NULL, icon, 4 * KPW_WND_MARGIN, msg_y, KPW_ICON_WDT, KPW_ICON_WDT, 0);
#endif

// --------------------------- i?keliam ? vir?¸ – kpstisvr.exe ChkUpd prane?imas ka?ko minimizuojasi
#if FALSE // dabar jau padariau kpstisvr.bin paleidim? SW_SHOW vietoj SW_SHOWMINIMIZED
WINDOWPLACEMENT wnd_pl;
            if(SUCCEEDED(retc)) KpSleep(500);
            retc0 = S_OK;
            KP_ASSERT00(GetWindowPlacement(dlg_wnd, &wnd_pl), KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc0)) wnd_pl.showCmd = SW_SHOWNORMAL;
            KP_ASSERT00(SetWindowPlacement(dlg_wnd, &wnd_pl), KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT00(SetWindowPos(dlg_wnd, HWND_TOPMOST, 0, 0, 100, 100, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE), KP_E_SYSTEM_ERROR, null, True);
#endif

// ---------------------------
            if(iTimeOut && SUCCEEDED(retc))
            {
               close_timer = SetTimer(HWND_DESKTOP, KP_TIMEOUT_TIMER, iTimeOut, NULL);
               if(close_timer == 0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
            }

            endfl = (iMsgType == KP_MB_NONE);

            if((!endfl) && SUCCEEDED(retc)) do
            {
               if(GetMessage(&msg, NULL, 0, 0)<0)
               {
#ifdef Debug
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
                  retc = KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
               }

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
// sprintf((char *)str_buf, "W  WM_QUIT     %x %x", msg.wParam, msg.lParam); KP_TRACE(str_buf);
// KpSleep(2000, HWND_DESKTOP); // Sleep(2000);
                  break;

               case WM_CLOSE:
                  retc = KP_E_CANCEL;
                  endfl = True;
// sprintf((char *)str_buf, "W  WM_CLOSE    %x %x", msg.wParam, msg.lParam); KP_TRACE(str_buf);
// KpSleep(2000, HWND_DESKTOP); // Sleep(2000);
                  break;

               case WM_CHAR:
                  switch(retp)
                  {
                  case KP_HP11_TOGGLE_CONSOLE:
                     if(lKphp11ThreadId!=0L)
                        if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                        {
#ifdef Debug
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
                           retc=KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
                        }
                     break;

                  case Enter:
                  case Esc:
                     endfl = True;
                     break;
                  }
                  break;

               case WM_COMMAND:
                  switch(retp)
                  {
                  case IDCANCEL:
                     retc = KP_E_CANCEL;
                  case IDOK:
                     endfl = True;
                     break;
                  }
// KP_TRACE_3("W  WM_COMMAND    %x %x %d", msg.wParam, msg.lParam, retc);
                  break;

               case WM_TIMER:
                  if((close_timer != 0) && (retp == close_timer) && SUCCEEDED(retc))
                  {
                     retc = KP_E_TIMEOUT;
                     endfl = True;
                  }
                  break;

#if FALSE
               case 0xF:
               case 0x113:
               case 0xa0:
               case 0x200:
                  break;
#endif
               default:
// sprintf((char *)str_buf, "W  %x          %x %x", msg.message, msg.wParam, msg.lParam); KP_TRACE(str_buf);
                  break;
               }

            } while((!endfl) && SUCCEEDED(retc));

            if(close_timer) KillTimer(dlg_wnd, close_timer);
            close_timer=0;

            if((dlg_wnd != NULL) && (iMsgType != KP_MB_NONE))
            {
               if(!(::DestroyWindow(dlg_wnd)))
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
               }
               dlg_wnd = NULL;
            }

            if(SUCCEEDED(retc)) retc = KpSleep(100, HWND_DESKTOP); // Sleep(100);

         } // else // if(hKpInstance==NULL)

      } // if(SUCCEEDED(retc))


#endif // #else // #if FALSE


#else // #if (Envir==MSWin32) || (Envir==MSWin32Mfc)

      printf((const char *)lpszOutStr);
      printf("\n");

#endif

   } // if((lpszOutStr!=NULL) && (!bServiceFl))

   KP_DELETE(msg_ptr);
   KP_DELETE(msg_data_ptr);

return(retc);
}

extern HRESULT KpMsgOut(const unsigned char *lpszOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, HWND *phDialogWnd)
{
return(KpMsgOut(lpszOutStr, lpszIconID, iMsgType, 0, KPW_ALIGN_CENTER, phDialogWnd));
}

extern HRESULT KpMsgOut(const unsigned char *lpszOutStr){ return(KpMsgOut(lpszOutStr, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI)); }

#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
HRESULT KpMsgOut(const char *lpszOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut, KpAlignments iAlign)
{
return(KpMsgOut((const unsigned char *)lpszOutStr, lpszIconID, iMsgType, iTimeOut, iAlign));
}

long KpMsgOut(const char *lpszOutStr, LPCTSTR lpszIconID, int iMsgType, int iTimeOut, KpAlignments iAlign)
{
return((long)KpMsgOut((const unsigned char *)lpszOutStr, lpszIconID, (KpMsgTypes)iMsgType, iTimeOut, iAlign));
}

extern HRESULT KpMsgOut(const char *lpszOutStr){ return(KpMsgOut(lpszOutStr, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI)); }

HRESULT KpMsgOut(KpString sOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut, KpAlignments iAlign)
{
return(KpMsgOut(sOutStr.ExtractUnsignedValueA(), lpszIconID, iMsgType, iTimeOut, iAlign));
}

#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
HRESULT KpMsgOutStr(string sOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut, KpAlignments iAlign)
{
HRESULT retc = S_OK;
KpString out_str(sOutStr);
return(KpMsgOut(out_str, lpszIconID, iMsgType, iTimeOut, iAlign));
}

extern HRESULT KpMsgOut(KpString sOutStr){ return(KpMsgOut(sOutStr, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI)); }

HRESULT KpMsgOut(const KpChar *iazKpStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut, KpAlignments iAlign)
{
HRESULT retc = S_OK;
unsigned char *str_buf = null;

   KP_ASSERT(iazKpStr != NULL, E_INVALIDARG, null, True);
   KP_NEWA(str_buf, unsigned char, TvKpStrLen(iazKpStr) + 1);
   if(SUCCEEDED(retc)) KptStrDecode(str_buf, iazKpStr, LangToCtbl[iMsgLangOff]); // TV_MAIN_CTBL);

   if(SUCCEEDED(retc)) KpMsgOut(str_buf, lpszIconID, iMsgType, iTimeOut, iAlign);

   KP_DELETEA(str_buf);

return(retc);
}

HRESULT KpMsgOut(const KpChar *iazKpStr){ return(KpMsgOut(iazKpStr, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI)); }


HRESULT GetButText(KpMsgTypes iMsgTp, const unsigned char **plpszMsgOk, const unsigned char **plpszMsgCancel, const unsigned char **plpszMsgHelp)
{
HRESULT retc=S_OK;
const unsigned char *msg_ok = (const unsigned char *)"";
const unsigned char *msg_cancel = (const unsigned char *)"";
const unsigned char *msg_help = (const unsigned char *)"";

   if(SUCCEEDED(retc)) switch(iMsgTp)
   {
   case KP_MB_OK:
      msg_ok=KP_MSG_OK;
      break;
   case KP_MB_GERAI:
      msg_ok=KP_MSG_GERAI;
      break;
   case KP_MB_TESTI:
      msg_ok=KP_MSG_TESTI;
      break;
   case KP_MB_BAIGTI:
      msg_ok=KP_MSG_BAIGTI;
      break;
   case KP_MB_OK_CANCEL:
      msg_ok=KP_MSG_OK;
      msg_cancel=KP_MSG_CANCEL;
      break;
   case KP_MB_GERAI_ATSAUKTI:
      msg_ok=KP_MSG_GERAI;
      msg_cancel=KP_MSG_ATSAUKTI;
      break;
   case KP_MB_TESTI_ATSAUKTI:
      msg_ok=KP_MSG_TESTI;
      msg_cancel=KP_MSG_ATSAUKTI;
      break;
   case KP_MB_YES_NO:
      msg_ok=KP_MSG_YES;
      msg_cancel=KP_MSG_NO;
      break;
   case KP_MB_TAIP_NE:
      msg_ok=KP_MSG_TAIP;
      msg_cancel=KP_MSG_NE;
      break;
   case KP_MB_GERAI_ATSAUKTI_PAMIRSAU:
      msg_ok = KP_MSG_GERAI;
      msg_cancel = KP_MSG_ATSAUKTI;
      msg_help = KP_MSG_PAMIRSAU_SLAPTAZODI;
      break;
   case KP_MB_NONE:
      break;
   default:
      KP_ERROR(E_INVALIDARG, null);
      break;
   }

   if(plpszMsgOk) *plpszMsgOk = msg_ok;
   if(plpszMsgCancel) *plpszMsgCancel = msg_cancel;
   if(plpszMsgHelp) *plpszMsgHelp = msg_help;

return(retc);
}


#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
BOOL CALLBACK KpMsgDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;
CREATESTRUCT *csp=NULL;
int wnd_x=0;
int wnd_y=0;
int wnd_dx=0;
int wnd_dy=0;
int msg_x=0;
int msg_y=0;
int msg_dx=0;
int msg_dy=0;
int msg_lines=1;
int but_x=0;
int but_y=0;
int but1_x=0;
int but1_y=0;
int but2_x=0;
int but2_y=0;
int retp;
const unsigned char *msg_ok = NULL;
const unsigned char *msg_cancel = NULL;
HWND but_ok_ctrl = NULL;
HWND but_cancel_ctrl = NULL;
bool endfl=False;
unsigned char *msg_ptr = NULL;
KpMsgData *msg_data_ptr = NULL;
KpWnd *cur_wnd = NULL;
#ifdef Debug
// unsigned char str_buf[KP_MAX_FNAME_LEN+100];
#endif
// HWND prew_mouse_over=NULL;
HDC hdc = NULL;
PAINTSTRUCT ps;
int line_y;

   retp=LOWORD(wParam);
   endfl=False;

#if FALSE
   if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "KpMsgDialogProc window:%d %d", hwndDlg, cur_wnd);
KP_TRACE(str_buf);
#endif
#endif

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
      if((hKpInstance==NULL) && SUCCEEDED(retc))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL, False);
         retc=KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
      }

      if(SUCCEEDED(retc)) csp = (LPCREATESTRUCT)lParam;
      if((csp == NULL) && SUCCEEDED(retc))
      {
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL, False);
         retc = KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
      }

      if(SUCCEEDED(retc)) msg_data_ptr=(KpMsgData *)csp->lpCreateParams;

      msg_ptr = NULL;
      if(SUCCEEDED(retc))
         retc = CalcMsgPars(msg_data_ptr->m_lpszMsgTxt, &msg_ptr, &msg_lines,
            &msg_x, &msg_y, &msg_dx, &msg_dy, &wnd_x, &wnd_y, &wnd_dx, &wnd_dy,
            &but_x, &but_y, &but1_x, &but1_y, &but2_x, &but2_y, msg_data_ptr->m_iAlign);

// ------
      KP_NEWO(cur_wnd, KpWnd(hwndDlg, TYP_KpDialog, null, NULL,
            hKpInstance, NULL, NULL, KPW_CONTROL_STYLE_NORMAL,
            wnd_dx, wnd_dy, 1, msg_lines, 0L, 0L,
            NULL));

      if(SUCCEEDED(retc)) retc = WndPreg(cur_wnd, TYP_KpDialog, hKpInstance, null, False);

// -------------
#if FALSE
      if((cur_wnd != NULL) && SUCCEEDED(retc))
      {
         if(cur_wnd->m_hIcon != NULL)
         {
            retc = KpCreateIcon(hKpInstance, hwndDlg, NULL, cur_wnd->m_hIcon, KPW_WND_MARGIN, msg_y, KPW_ICON_WDT, KPW_ICON_WDT, 0);
         }
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "KpMsgDialogProc icon:%d", cur_wnd->m_hIcon);
KP_TRACE(str_buf);
#endif
      }
#endif

      if(SUCCEEDED(retc)) retc = KpCreateIcon(hKpInstance, hwndDlg, NULL, msg_data_ptr->m_hIcon, 4 * KPW_WND_MARGIN, msg_y, KPW_ICON_WDT, KPW_ICON_WDT, 0);

      if(SUCCEEDED(retc)) retc = GetButText(msg_data_ptr->m_iMsgTp, &msg_ok, &msg_cancel, NULL);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, msg_ptr, msg_x, msg_y, msg_dx, msg_lines,
                                    KPW_CONTROL_STYLE_NORMAL, 0 /* WS_EX_STATICEDGE */,
                                    (msg_data_ptr->m_iAlign & KPW_ALIGN_CENTER)?SS_CENTER:0, NULL);

      if(SUCCEEDED(retc)) switch(msg_data_ptr->m_iMsgTp)
      {
      case KP_MB_OK:
      case KP_MB_GERAI:
      case KP_MB_TESTI:
      case KP_MB_BAIGTI:
         if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg, &but_ok_ctrl, IDOK, msg_ok, but_x, but_y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         if((but_ok_ctrl==NULL) && SUCCEEDED(retc))
         {
//          retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL, False);
            retc = KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
         }
         break;
      case KP_MB_OK_CANCEL:
      case KP_MB_GERAI_ATSAUKTI:
      case KP_MB_TESTI_ATSAUKTI:
      case KP_MB_YES_NO:
      case KP_MB_TAIP_NE:
         if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg, &but_ok_ctrl, IDOK, msg_ok, but1_x, but1_y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         if((but_ok_ctrl == NULL) && SUCCEEDED(retc)) retc = KP_E_SYSTEM_ERROR;

         if(SUCCEEDED(retc)) retc = KpCreateButton(hKpInstance, hwndDlg, &but_cancel_ctrl, IDCANCEL, msg_cancel, but2_x, but2_y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         if((but_cancel_ctrl == NULL) && SUCCEEDED(retc)) retc = KP_E_SYSTEM_ERROR;
         break;
      case KP_MB_GERAI_ATSAUKTI_PAMIRSAU:
         KP_ERROR(E_NOTIMPL, null);
         break;
      case KP_MB_NONE:
         break;
      default:
         KP_ERROR(E_INVALIDARG, null);
         break;
      }

      if((but_ok_ctrl != NULL) && SUCCEEDED(retc))
         if(!SetFocus(but_ok_ctrl))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
            retc=KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
         }

      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
      if(SUCCEEDED(retc)) retc = GetCurWindow(&cur_wnd, hwndDlg);
      if(cur_wnd && SUCCEEDED(retc))
      {
         wnd_dx = cur_wnd->m_iWdtDots;
         wnd_dy = cur_wnd->m_iHgtDots;

         line_y = wnd_dy - iWndCaptionHgt - iWndBorderWdt - iWndBorderWdt - (2 * KPW_WND_MARGIN) - KPW_BUTTON_HGT - (2 * KPW_WND_MARGIN);

         hdc = BeginPaint(hwndDlg, &ps);
         if(hdc)
         {
            KpDrawLine(hdc, 0, line_y, wnd_dx, line_y, KP_WND_SUNKEN, NULL);

            EndPaint(hwndDlg, &ps);
         }
      }


      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_CLOSE:
      retc = KP_E_CANCEL;
      endfl = True;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   case WM_QUIT:
      switch(retp)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
      }
      endfl=True;
      break;

#if FALSE
   case WM_MOUSEMOVE:
// ----------------- mygtuku gesinimas
      prew_mouse_over = hMouseOverWnd;
      if(prew_mouse_over) // !=hwndDlg)
      {
         hMouseOverWnd = NULL; // hwndDlg;
//       if(prew_mouse_over)
            if(!InvalidateRect(prew_mouse_over, 0, TRUE))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
            }
      }
      break;
#endif

   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case IDCANCEL:
         retc = KP_E_CANCEL;
      case IDOK:
         endfl = True;
         break;
      }
      break;

#if FALSE
   case 0xf:
   case 0x20:
   case 0x200:
   case 0x84:
   case 0xa0:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
#endif
   default:
// sprintf((char *)str_buf, "D  %x          %x %x", uMsg, wParam, lParam); KP_TRACE(str_buf);
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   KP_DELETEA(msg_ptr);

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = TRUE;
   }

// paprastam endfl nereikia - tada lau?ia tolesn? prane?im¸ cikl? (KpSleep() KpMsgOut() gale)
   if(/* endfl || */ FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


HRESULT WrapMsg(const unsigned char *lpszMsgStr, unsigned char **plpszMsgPtr, int *piMsgLines, int iMsgColumns)
{
HRESULT retc = S_OK;
int xpos = 0;
const unsigned char *pnts = null;
unsigned char *pntd = null;
int num_lines = 1;

   KP_ASSERT(lpszMsgStr, E_INVALIDARG, null, True);
   KP_ASSERT(plpszMsgPtr, E_INVALIDARG, null, True);

   KP_NEWA(*plpszMsgPtr, unsigned char, strlen(lpszMsgStr) + 1);
   if(SUCCEEDED(retc))
   {
      xpos = 0;
      pnts = lpszMsgStr;
      pntd = *plpszMsgPtr;
      while(*pnts)
      {
         if((*pnts == Spc) && (xpos > iMsgColumns - KPW_MSG_BREAK_THRESHOLD))
         {
            *pntd++ = Lf;
            pnts++;
            xpos = 0;
            num_lines++;
         }
         else
         {
            if(*pnts == Lf)
            {
               xpos = 0;
               num_lines++;
            }
            else xpos++;

            *pntd++ = *pnts++;
         }
      }
      *pntd = Nul;
   }

   if(piMsgLines) *piMsgLines = num_lines;

return(retc);
}


HRESULT CalcMsgPars(const unsigned char *lpszMsgStr, unsigned char **plpszMsgPtr,
   int *piMsgLines,
   int *piMsgX, int *piMsgY, int *piMsgDx, int *piMsgDy,
   int *piWndX, int *piWndY, int *piWndDx, int *piWndDy,
   int *piButX, int *piButY, int *piBut1X, int *piBut1Y, int *piBut2X, int *piBut2Y,
   KpAlignments iAlign)
{
HRESULT retc=S_OK;
const unsigned char *msg=NULL;
int ll;
int mm;
// int rest;
// int jj;
const unsigned char *pnts;
unsigned char *pntd;
int pos_x=0;
HDC dc;
int msg_dx;
#ifdef Debug
// unsigned char str_buf[KP_MAX_FNAME_LEN+100];
#endif
int max_wdt;

   if(
      (plpszMsgPtr==NULL) || (piMsgLines==NULL) ||
      (piMsgX==NULL) || (piMsgY==NULL) || (piMsgDx==NULL) || (piMsgDy==NULL) ||
      (piWndX==NULL) || (piWndY==NULL) || (piWndDx==NULL) || (piWndDy==NULL) ||
      (piButX==NULL) || (piButY==NULL) || (piBut1X==NULL) || (piBut1Y==NULL) ||
      (piBut2X==NULL) || (piBut2Y==NULL)
     )
   {
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);
      retc=E_INVALIDARG;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
   }

   if(SUCCEEDED(retc))
   {
      msg = lpszMsgStr;
      if(msg == NULL) msg = (const unsigned char *)"";

      ll = strlen(msg);

// mm – eilu?i¸ skai?ius
      mm = ll/KPW_MSG_NUMOFCOLUMNS;
      pnts = msg;
      while(*pnts) // pridedam \n skai?i¸
      {
         if(/* (*pnts == Cr) || */ (*pnts == Lf)) mm++;
         pnts++;
      }

// mm – formatuoto prane?imo buferio dydis
      mm = (mm + 1) * KPW_MSG_NUMOFCOLUMNS * 2 + 1;
      KP_NEWA(*plpszMsgPtr, unsigned char, mm);
   }

#if FALSE
   if(SUCCEEDED(retc))
   {
      *piMsgLines=ll/KPW_MSG_NUMOFCOLUMNS;
      if(*piMsgLines<1) *piMsgLines=1;
   }
#endif

   if(SUCCEEDED(retc))
   {
      pnts = msg;
      pos_x = 0;
      pntd = *plpszMsgPtr;
      *piMsgLines = 1;
      max_wdt = 0;

// *pntd++ = '[';

      while(*pnts)
      {
         if(
            ((*pnts == Spc) && (pos_x > KPW_MSG_NUMOFCOLUMNS - KPW_MSG_BREAK_THRESHOLD)) ||
            (pos_x >= KPW_MSG_NUMOFCOLUMNS) || (*pnts==Cr) || (*pnts==Lf)
           )
         {
#if FALSE
// eulut?s galas, ypa? tu??ios
            if(iAlign & KPW_ALIGN_LEFT)
            {
               while(pos_x < KPW_MSG_NUMOFCOLUMNS)
               {
                  (*pntd++) = Spc;
                  pos_x++;
               }
            }
#endif

            if(pos_x > max_wdt) max_wdt = pos_x;

            (*piMsgLines)++;
            pos_x = 0;

            if(*pnts == Spc) pnts++;
            if(*pnts == Cr) pnts++;
            if(*pnts == Lf) pnts++;

            (*pntd++) = Cr;
            (*pntd++) = Lf;

#if FALSE
// paskutines eilutes pradzia
            if(iAlign & KPW_ALIGN_CENTER)
            {
               rest = ll - (pnts - msg); if(rest < 0) rest = 0;
               if((rest < ((KPW_MSG_NUMOFCOLUMNS - KPW_MSG_BREAK_THRESHOLD) + KPW_MSG_NUMOFCOLUMNS) / 2))
               {
                  for(jj=0; jj < (KPW_MSG_NUMOFCOLUMNS - rest) / 2; jj++)
                  {
                     (*pntd++) = Spc;
                     pos_x++;
                  }
               }
            }
#endif
         }
         else
         {
            (*pntd++) = (*pnts++);
            pos_x++;
         }
      }

#if FALSE
// paskutines eilutes galas // KPW_ALIGN_LEFT irgi reikia, kad teisingai skai?iuot¸ msg_dx
   /* if(iAlign & KPW_ALIGN_CENTER) */ if(*piMsgLines > 1)
      {
         while(pos_x < KPW_MSG_NUMOFCOLUMNS)
         {
            (*pntd++) = Spc;
            pos_x++;
         }
      }
#endif

// *pntd++ = ']';

      if(pos_x > max_wdt) max_wdt = pos_x;

      *pntd = Nul;
   }


   if(SUCCEEDED(retc))
   {
      dc = GetDC(HWND_DESKTOP);
      if(dc == NULL)
      {
#ifdef Debug
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         retc = KP_E_SYSTEM_ERROR;
#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "Error, File: %s line: %d", __FILE__, __LINE__);
KP_TRACE(str_buf);
#endif
      }
   }

   if(SUCCEEDED(retc))
   {
//    msg_dx = max_lin_len*iaCtrlTextFactors[KPW_CONTROL_STYLE_NORMAL]/(((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?9:10);
//    msg_dx = KPW_CALC_STATIC_WDT_FACTOR(msg, KPW_CONTROL_STYLE_NORMAL)/(*piMsgLines);
//    msg_dx = KPW_CALC_STATIC_WDT_FACTOR(*plpszMsgPtr, KPW_CONTROL_STYLE_NORMAL)/(*piMsgLines);
      msg_dx = KPW_CALC_STATIC_WDT_FACTOR("n", KPW_CONTROL_STYLE_NORMAL) * max_wdt;

      *piMsgDx = msg_dx;
      if(*piMsgDx < KPW_BUTTON_WDT) *piMsgDx = KPW_BUTTON_WDT;

//    *piMsgDy = iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] * (*piMsgLines);
      *piMsgDy = iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL];
      if(*piMsgLines > 1) *piMsgDy +=
         iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] * (*piMsgLines - 1);

//    *piWndDx = KPW_WND_BORDER_WDT_INI + KPW_WND_BORDER_COR + 3 * KPW_WND_MARGIN + KPW_ICON_WDT + KPW_WND_MARGIN + (*piMsgDx) + KPW_WND_MARGIN + KPW_WND_BORDER_COR + KPW_WND_BORDER_WDT_INI;
//    *piWndDx = iWndBorderWdt + 3 * KPW_WND_MARGIN + KPW_ICON_WDT + KPW_WND_MARGIN + (*piMsgDx) + KPW_WND_MARGIN + iWndBorderWdt;
//    *piWndDx = iWndBorderWdt + 3 * KPW_WND_MARGIN + KPW_ICON_WDT + KPW_WND_MARGIN + (*piMsgDx) + (KPW_WND_MARGIN * 3) + iWndBorderWdt;
      *piWndDx = iWndBorderWdt + 3 * KPW_WND_MARGIN + KPW_ICON_WDT + KPW_WND_MARGIN + (*piMsgDx) + (KPW_ICON_WDT / 2) + iWndBorderWdt;

      if(iAlign & KPW_ALIGN_LEFT) *piWndDx -= 20; // 100;
//    if(iAlign & KPW_ALIGN_CENTER) *piWndDx -= 20;
      if(*piWndDx < KPW_WND_MIN_DX) *piWndDx = KPW_WND_MIN_DX;

//    *piWndDy = KPW_WND_BORDER_WDT_INI + KPW_WND_BORDER_COR + KPW_WND_CAPTION_HGT_INI + 4 * KPW_WND_MARGIN + (*piMsgDy) + 4 * KPW_WND_MARGIN + KPW_BUTTON_HGT + 2 * KPW_WND_MARGIN + KPW_WND_BORDER_COR + KPW_WND_BORDER_WDT_INI;
      *piWndDy = iWndBorderWdt + iWndCaptionHgt + 4 * KPW_WND_MARGIN + (*piMsgDy) + 6 * KPW_WND_MARGIN + KPW_BUTTON_HGT + 2 * KPW_WND_MARGIN + iWndBorderWdt;

      *piWndX=(GetDeviceCaps(dc, HORZRES)-(*piWndDx))/2;
      *piWndY=(GetDeviceCaps(dc, VERTRES)-(*piWndDy))/2;
      if(iAlign & KPW_ALIGN_UP) *piWndY /= 2; // antro ketvir?io vir?us

//    *piMsgX=((*piWndDx)-KPW_WND_BORDER_WDT_INI-KPW_WND_BORDER_COR-KPW_WND_BORDER_WDT_INI-KPW_WND_BORDER_COR-msg_dx)/2 + KPW_ICON_WDT;
//    *piMsgX = ((*piWndDx) - 2 * iWndBorderWdt - msg_dx)/2 + KPW_ICON_WDT;
      *piMsgX = 3 * KPW_WND_MARGIN + KPW_ICON_WDT + KPW_WND_MARGIN;
      if(iAlign & KPW_ALIGN_LEFT) *piMsgX += 20; // 70;
//    if(iAlign & KPW_ALIGN_CENTER) *piMsgX -= 20;
      *piMsgY=4*KPW_WND_MARGIN;

//    *piButX = ((*piWndDx) - KPW_WND_BORDER_WDT_INI - KPW_WND_BORDER_COR - KPW_WND_BORDER_COR - KPW_WND_BORDER_WDT_INI - KPW_BUTTON_WDT) / 2;
//    *piBut1X = (*piButX) - (KPW_BUTTON_WDT + KPW_WND_MARGIN) / 2;
//    *piBut2X = (*piButX) + (KPW_BUTTON_WDT + KPW_WND_MARGIN) / 2;

      *piBut2X = *piButX = ((*piWndDx) - KPW_WND_BORDER_WDT_INI - KPW_WND_BORDER_COR - KPW_WND_BORDER_COR - KPW_WND_BORDER_WDT_INI) - (2 * KPW_WND_MARGIN) - KPW_BUTTON_WDT;
      *piBut1X = (*piBut2X) - KPW_BUTTON_WDT - KPW_WND_MARGIN;

      (*piButY) = (*piBut1Y) = (*piBut2Y) = 4 * KPW_WND_MARGIN + (*piMsgDy) + 6 * KPW_WND_MARGIN;
//    (*piButY) = (*piBut1Y) = (*piBut2Y) = *piWndDy - iWndBorderWdt - iWndCaptionHgt - KPW_BUTTON_HGT - 2 * KPW_WND_MARGIN - iWndBorderWdt;
   }

return(retc);
}


// -----------------------------------------
KpInputStrData::KpInputStrData(const unsigned char *lpszPrompt, const unsigned char *lpszInitVal, int iEditWdt, DWORD dwExStyle, DWORD dwStyle, int iWndDx, KpMsgTypes iMsgTp)
{
   m_hwEditCtrl = NULL;
   m_lpszPrompt = lpszPrompt;
   m_lpszInitVal = lpszInitVal;
   m_iEditWdt = iEditWdt;
   m_dwExStyle = dwExStyle;
   m_dwStyle = dwStyle;
   m_iWndDx = iWndDx;
   m_iMsgTp = iMsgTp;
}


// -----------------------------------------
BOOL CALLBACK KpInputStrProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
BOOL retw = FALSE;
CREATESTRUCT *csp = NULL;
KpInputStrData *in_str_ptr = NULL;
int but_x;
int retp;
bool endfl = False;
const unsigned char *msg_ok = NULL;
const unsigned char *msg_cancel = NULL;
const unsigned char *msg_help = NULL;

   retp = LOWORD(wParam);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
      if(SUCCEEDED(retc)) csp = (LPCREATESTRUCT)lParam;
      KP_ASSERT(csp, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) in_str_ptr = (KpInputStrData *)csp->lpCreateParams;
      KP_ASSERT(in_str_ptr, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(in_str_ptr->m_lpszPrompt, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT(in_str_ptr->m_lpszInitVal, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, hwndDlg, NULL, in_str_ptr->m_lpszPrompt, KP_INPUT_STR_PROMPT_X, KP_INPUT_STR_PROMPT_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, 0);
      if(SUCCEEDED(retc))
      {
         if(in_str_ptr->m_iEditWdt)
            retc = KpCreateEdit(hKpInstance, hwndDlg, &(in_str_ptr->m_hwEditCtrl), in_str_ptr->m_lpszInitVal, in_str_ptr->m_iEditWdt,
               KP_INPUT_STR_EDIT_X, KP_INPUT_STR_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE | in_str_ptr->m_dwExStyle, in_str_ptr->m_dwStyle, 1);
         else
            retc = KpCreateEdit(hKpInstance, hwndDlg, &(in_str_ptr->m_hwEditCtrl), in_str_ptr->m_lpszInitVal,
               KP_INPUT_STR_EDIT_X, KP_INPUT_STR_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE | in_str_ptr->m_dwExStyle, in_str_ptr->m_dwStyle, 1);
      }

      if(SUCCEEDED(retc)) retc = GetButText(in_str_ptr->m_iMsgTp, &msg_ok, &msg_cancel, &msg_help);

      if(SUCCEEDED(retc)) switch(in_str_ptr->m_iMsgTp)
      {
      case KP_MB_OK:
      case KP_MB_GERAI:
      case KP_MB_TESTI:
      case KP_MB_BAIGTI:
         if(SUCCEEDED(retc))
         {
            but_x = (in_str_ptr->m_iWndDx - 2 * iWndBorderWdt) / 2 - KPW_BUTTON_WDT / 2;
            /* retc= */ KpCreateButton(hKpInstance, hwndDlg, NULL, IDOK, msg_ok, but_x, KP_INPUT_STR_OK_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         }
         break;
      case KP_MB_OK_CANCEL:
      case KP_MB_GERAI_ATSAUKTI:
      case KP_MB_TESTI_ATSAUKTI:
      case KP_MB_YES_NO:
      case KP_MB_TAIP_NE:
         if(SUCCEEDED(retc))
         {
            but_x = (in_str_ptr->m_iWndDx - 2 * iWndBorderWdt) / 2 - KP_INPUT_STR_CTRL_MARGIN / 2 - KPW_BUTTON_WDT;
            /* retc= */ KpCreateButton(hKpInstance, hwndDlg, NULL, IDOK, msg_ok /* KP_MSG_GERAI */, but_x, KP_INPUT_STR_OK_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         }
         if(SUCCEEDED(retc))
         {
            but_x = (in_str_ptr->m_iWndDx - 2 * iWndBorderWdt) / 2 + KP_INPUT_STR_CTRL_MARGIN / 2;
            /* retc= */ KpCreateButton(hKpInstance, hwndDlg, NULL, IDCANCEL, msg_cancel /* KP_MSG_ATSAUKTI */, but_x, KP_INPUT_STR_CANCEL_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         }
         break;
      case KP_MB_GERAI_ATSAUKTI_PAMIRSAU:
         if(SUCCEEDED(retc))
         {
            but_x = (in_str_ptr->m_iWndDx - 2 * iWndBorderWdt) / 2 - KPW_BUTTON_WDT / 2 - KP_INPUT_STR_CTRL_MARGIN / 2 - KPW_BUTTON_WDT;
            /* retc= */ KpCreateButton(hKpInstance, hwndDlg, NULL, IDOK, msg_ok /* KP_MSG_GERAI */, but_x, KP_INPUT_STR_OK_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         }
         if(SUCCEEDED(retc))
         {
            but_x = (in_str_ptr->m_iWndDx - 2 * iWndBorderWdt) / 2 - KPW_BUTTON_WDT / 2;
            /* retc= */ KpCreateButton(hKpInstance, hwndDlg, NULL, IDCANCEL, msg_cancel /* KP_MSG_ATSAUKTI */, but_x, KP_INPUT_STR_CANCEL_BUT_Y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
         }
         if(SUCCEEDED(retc))
         {
            but_x = (in_str_ptr->m_iWndDx - 2 * iWndBorderWdt) / 2 + KPW_BUTTON_WDT / 2 + KP_INPUT_STR_CTRL_MARGIN / 2;
            /* retc= */ KpCreateButton(hKpInstance, hwndDlg, NULL, IDHELP, msg_help, but_x, KP_INPUT_STR_CANCEL_BUT_Y, KPW_FORGET_BUTTON_WDT /* KPW_BUTTON_WDT */, KPW_BUTTON_HGT, 0, 0);
         }
         break;
      default:
         KP_ERROR(E_INVALIDARG, null);
         break;
      }

      if(SUCCEEDED(retc))
         if(!SetFocus(in_str_ptr->m_hwEditCtrl))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

      retw = 0;
      break; // case WM_CREATE:

   case WM_CLOSE:
      retc = KP_E_CANCEL;
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

   case WM_COMMAND:
      switch(retp)
      {
      case IDOK:
         PostMessage(NULL, uMsg, wParam, lParam);
//       endfl = True;
         break;
      case IDHELP:
         retc = KP_E_HELP;
         endfl = True;
         break;
      case IDCANCEL:
         retc = KP_E_CANCEL;
         endfl = True;
         break;
      }
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw = True;
   }

   switch(retc) // if(FAILED(retc))
   {
      case S_OK: break;
      case KP_E_CANCEL: PostQuitMessage(IDCANCEL); break;
      case KP_E_HELP: PostQuitMessage(IDHELP); break;
      default: PostQuitMessage(IDABORT); break;
   }

return(retw);
}


// ---------------------------------- KpInputStr() vieno lauko ?vedimo dialogo langelis
HRESULT KpInputStr(const unsigned char *lpszPrompt, unsigned char *lpszEditBuf, int iBufLen, int iEditWdt, DWORD dwExStyle, DWORD dwStyle, KpMsgTypes iMsgTp)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
KpInputStrData *in_str_ptr = NULL;
HWND dlg_wnd = NULL;
HDC dc;
int wnd_x, wnd_y, wnd_dx, wnd_dy;
MSG msg;
int retp;
bool endfl=False;
HBRUSH brush;

   KP_ASSERT(lpszEditBuf, E_INVALIDARG, null, True);

// OpenWindow()
   if(SUCCEEDED(retc))
   {
      brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));

      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "KpInputStr",
      wcx.lpfnWndProc   = (WNDPROC)KpInputStrProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, IDI_APPLICATION);
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, IDI_APPLICATION);
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush; // (HBRUSH)COLOR_BACKGROUND;

      if(!RegisterClassEx(&wcx))
      {
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      wnd_dx = max(KPW_CALC_STATIC_WDT_FACTOR(lpszPrompt, KPW_CONTROL_STYLE_NORMAL), KPW_CALC_STATIC_WDT_FACTOR(lpszEditBuf, KPW_CONTROL_STYLE_NORMAL));
      wnd_dx = max(wnd_dx, KP_INPUT_STR_EDIT_X - KP_INPUT_STR_WND_HOR_MARGIN + iEditWdt);
      wnd_dx = max(wnd_dx, 2 * KPW_BUTTON_WDT + KP_INPUT_STR_CTRL_MARGIN);
      wnd_dx += 2*(KP_INPUT_STR_WND_HOR_MARGIN + iWndBorderWdt);

      wnd_dy = iWndCaptionHgt + 2 * KP_INPUT_STR_WND_VERT_MARGIN + 3 * iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + 2 * KP_INPUT_STR_CTRL_MARGIN + iWndBorderWdt;
   }

   if(SUCCEEDED(retc))
   {
      dc = GetDC(HWND_DESKTOP);
      KP_ASSERT(dc, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(SUCCEEDED(retc))
   {
      wnd_x = (GetDeviceCaps(dc, HORZRES) - wnd_dx) / 2;
      wnd_y = (GetDeviceCaps(dc, VERTRES) - wnd_dy) / 2;
   }

   KP_NEW(in_str_ptr, KpInputStrData(lpszPrompt, lpszEditBuf, iEditWdt, dwExStyle, dwStyle, wnd_dx, iMsgTp));

   if(SUCCEEDED(retc))
   {
      dlg_wnd = CreateWindowEx
      (
         0L,            // DWORD dwExStyle,      // extended window style
         "KpInputStr",
         (LPCTSTR)KP_INPUT_TITLE, // (LPCTSTR)lpszPrompt,    // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         wnd_x, // CW_USEDEFAULT, // int x,               // horizontal position of window
         wnd_y, // CW_USEDEFAULT, // int y,               // vertical position of window
         wnd_dx, // int nWidth,           // window width
         wnd_dy, // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,       // HMENU hMenu,          // handle to menu, or child-window identifier
         hKpInstance,
         (LPVOID)in_str_ptr // lpszPrompt // LPVOID lpParam // pointer to window-creation data
      );

      KP_ASSERT(dlg_wnd, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(SUCCEEDED(retc)) ShowWindow(dlg_wnd, SW_SHOW);
   KP_ASSERT(SetWindowPos(dlg_wnd, HWND_TOPMOST, 0, 0, 100, 100, SWP_NOMOVE|SWP_NOSIZE), KP_E_SYSTEM_ERROR, GetLastError(), False);

// DoEdit()

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0) < 0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp = LOWORD(msg.wParam);
      }

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         case IDHELP: retc = KP_E_HELP; break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
         endfl = True;
         break;

      case WM_CHAR:
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam);
            break;

         case Enter:
            PostMessage(NULL, WM_COMMAND, IDOK, 0L);
//          endfl = True;
            break;
         case Esc:
            retc = KP_E_CANCEL;
            endfl = True;
            break;
         }
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
            KP_ASSERT(in_str_ptr, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(in_str_ptr->m_hwEditCtrl, KP_E_SYSTEM_ERROR, null, True);

            if(SUCCEEDED(retc))
            {
               SendMessage(in_str_ptr->m_hwEditCtrl, WM_GETTEXT, iBufLen, (LPARAM)lpszEditBuf);
               lpszEditBuf[iBufLen] = Nul;
            }
            endfl = True;
            break;
         case IDHELP:
            if(msg.hwnd == dlg_wnd)
            {
               endfl = True;
               retc = KP_E_HELP;
            }
            break;
         case IDCANCEL:
            if(msg.hwnd == dlg_wnd)
            {
               endfl = True;
               retc = KP_E_CANCEL;
            }
            break;
         } // switch(retp)
         break;

      } // switch(msg.message)

   } while((!endfl) && SUCCEEDED(retc));

// CloseWindow()

   if(dlg_wnd)
   {
      DestroyWindow(dlg_wnd);
      dlg_wnd = 0;
   }

   KP_DELETE(in_str_ptr);

return(retc);
}


//--------------------------
// W2k
// iWindowsVersion: [20]
// iWindowsSP: [4]
// Osvi.dwPlatformId: [2]
// Osvi.dwMajorVersion: [5]
// Osvi.dwMinorVersion: [0]
// Osvi.szCSDVersion: [Service Pack 4]
// Osvi.dwBuildNumber: [2195]
//
// Vista
// iWindowsVersion: [20]
// iWindowsSP: [0]
// Osvi.dwPlatformId: [2]
// Osvi.dwMajorVersion: [6]
// Osvi.dwMinorVersion: [0]
// Osvi.szCSDVersion: []
// Osvi.dwBuildNumber: [6000]

//
// Windows versions:
//
// 4.0.950 Windows 95
// 4.0.1111 Windows 95 OSR 2 & OSR 2.1
// 4.0.1212 Windows 95 OSR 2.5
// 4.10.1998 Windows 98
// 4.10.2222 Windows 98 Second Edition
// 4.90.3000 Windows Me
//
// Windows NT versions:
//
// 4.0.1381 Windows NT 4.0
// 5.0.2195 Windows 2000
// 5.1.2600 Windows XP
// or Windows XP 64-Bit Edition Version 2002 (Itanium)
// 5.2.3790 Windows Server 2003
// or Windows XP x64 Edition (AMD64/EM64T)
// or Windows XP 64-Bit Edition Version 2003 (Itanium)
// 6.0.6000 Windows Vista
// 6.0.6001 Windows Vista with Service Pack 1
// or Windows Server 2008
// 6.1.7600 Windows 7
// or Windows Server 2008 R2
//
// Note that there is normally no need to specify the build numbers (i.e., you may simply use "5.1" for Windows XP).
//
// If a major version number less than 5 is specified in combination with a one-digit minor version number, the minor version number will be multiplied by 10. Therefore, 4.1 (Windows 98) is equivalent to 4.10.
//


// RTL_OSVERSIONINFOEXW is defined in winnt.h
BOOL GetOsVersion(RTL_OSVERSIONINFOEXW* pk_OsVer)
{
    typedef LONG (WINAPI* tRtlGetVersion)(RTL_OSVERSIONINFOEXW*);

    memset(pk_OsVer, 0, sizeof(RTL_OSVERSIONINFOEXW));
    pk_OsVer->dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOEXW);

    HMODULE h_NtDll = GetModuleHandleW(L"ntdll.dll");
    tRtlGetVersion f_RtlGetVersion = (tRtlGetVersion)GetProcAddress(h_NtDll, "RtlGetVersion");

    if (!f_RtlGetVersion)
        return FALSE; // This will never happen (all processes load ntdll.dll)

    LONG Status = f_RtlGetVersion(pk_OsVer);
    return Status == 0; // STATUS_SUCCESS;
}

HRESULT KpGetSystemVersion(MSWin32Version *piWin32Vers, int *piWinSP)
{
HRESULT retc=S_OK;
BOOL bOsVersionInfoEx;
MSWin32Version retval=WinUnkn;
int ret_sp=0;
bool exit_fl=False;
const unsigned char *pnts;

   if((piWin32Vers==NULL) || (piWinSP==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
// Try calling GetVersionEx using the OSVERSIONINFOEX structure,
// which is supported on Windows 2000.
//
// If that fails, try using the OSVERSIONINFO structure.

      ZeroMemory(&Osvi, sizeof(OSVERSIONINFOEX));
      Osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

      bOsVersionInfoEx=GetVersionEx((OSVERSIONINFO *)&Osvi);
      if(!bOsVersionInfoEx)
      {
// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

         Osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
         if (!GetVersionEx((OSVERSIONINFO *)&Osvi))
            exit_fl=True;

         Osvi.szCSDVersion[127]=Nul;
      }

      if(!exit_fl)
      {
         switch(Osvi.dwPlatformId)
         {
         case VER_PLATFORM_WIN32s:
            retval=Win31;
            break;

         case VER_PLATFORM_WIN32_WINDOWS:
/*
            if(
               (osvi.dwMajorVersion > 4) ||
               ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion > 0))
              )
               retval=Win98;
            else
               retval=Win95;
            break;
*/
            switch(Osvi.dwMajorVersion)
            {
            case 4:
               switch(Osvi.dwMinorVersion)
               {
               case 0:
                  if(strchr(Osvi.szCSDVersion, 'C')!=NULL) retval=Win95OSR2; // " C "
                  else  retval=Win95;
               case 10:
                  if(strchr(Osvi.szCSDVersion, 'A')!=NULL) retval=Win98SE; // " A "
                  else  retval=Win98;
                  break;
               case 90: retval=WinMe; break;

               default: retval=Win98c; break;
               }
               break;

            default: retval=Win95c; break;
            }

            break;

         case VER_PLATFORM_WIN32_NT:

// Test for the product.
            if ((Osvi.dwMajorVersion >= 6) && (Osvi.dwMinorVersion >= 2))
            {
               RTL_OSVERSIONINFOEXW rtl_osver;
               if (GetOsVersion(&rtl_osver))
               {
                  Osvi.dwMajorVersion = rtl_osver.dwMajorVersion;
                  Osvi.dwMinorVersion = rtl_osver.dwMinorVersion;
                  Osvi.dwBuildNumber = rtl_osver.dwBuildNumber;
                  Osvi.dwPlatformId = rtl_osver.dwPlatformId;
                  KptUnicodeToStr((uchar *)Osvi.szCSDVersion, rtl_osver.szCSDVersion, 71);
                  Osvi.wServicePackMajor = rtl_osver.wServicePackMajor;
                  Osvi.wServicePackMinor = rtl_osver.wServicePackMinor;
                  Osvi.wSuiteMask = rtl_osver.wSuiteMask;
                  Osvi.wProductType = rtl_osver.wProductType;
               }
            }

            switch(Osvi.dwMajorVersion)
            {
            case 0:
            case 1:
            case 2: retval=WinNT40c; break;

            case 3:
               switch(Osvi.dwMinorVersion)
               {
               case 51: retval=WinNT351; break;

               default: retval=WinNT35c; break;
               }
               break;

            case 4:
               switch(Osvi.dwMinorVersion)
               {
               case 0: retval=WinNT40; break;

               default: retval=WinNT40c; break;
               }
               break;

            case 5:
               switch(Osvi.dwMinorVersion)
               {
               case 0: retval=Win2000; break;
               case 1:
                  if(GetSystemMetrics(SM_STARTER)) retval=WinXpStart;
                  else if(GetSystemMetrics(SM_TABLETPC)) retval=WinXpTablet;
                  else if(GetSystemMetrics(SM_MEDIACENTER)) retval=WinXpMedia;
                  else retval=WinXP;
                  break;
               case 2:
                  switch(Osvi.wProductType)
                  {
                  case VER_NT_WORKSTATION: retval=WinXP64; break;

                  case VER_NT_SERVER:
                  case VER_NT_DOMAIN_CONTROLLER:
                  default:
                     if(GetSystemMetrics(SM_SERVERR2)) retval=Win2003sR2;
                     else retval=Win2003s;
                     break;
                  }
                  break;

               default: retval=Win2000c; break;
               }
               break;

            case 6:
               switch(Osvi.dwMinorVersion)
               {
               case 0:
                  switch(Osvi.wProductType)
                  {
                  case VER_NT_SERVER:
                  case VER_NT_DOMAIN_CONTROLLER:
                      retval = Win2008s;
                      break;

                  case VER_NT_WORKSTATION:
                  default:
                      retval = WinVista;
                      break;
                  }
                  break;

               case 1:
                  retval = Win7;
                  break;

               case 2:
                  retval = Win8;
                  break;

               case 3:
                  retval = Win81;
                  break;

               default:
PutLogMessage_("KpGetSystemVersion() Osvi.dwMinorVersion: %d", Osvi.dwMinorVersion);
                  retval = WinVistaC;
                  break;
               }
               break;

            case 10:
               switch(Osvi.dwMinorVersion)
               {
               case 0: // Win10 demo
               default:
                  retval = Win10;
                  break;
               }
               break;
               
            default:
PutLogMessage_("KpGetSystemVersion() Osvi.dwMajorVersion: %d", Osvi.dwMajorVersion);
               retval = WinNtFuture;
               break;
            }

// Test for workstation versus server.
//          if(bOsVersionInfoEx)
//          {
//             if(osvi.wProductType == VER_NT_WORKSTATION)
//                printf("Professional ");
//
//             if (osvi.wProductType == VER_NT_SERVER)
//                printf ("Server ");
//          }
//          else
//          {
//             HKEY hKey;
//             char szProductType[80+1];
//             DWORD dwBufLen;
//
//             RegOpenKeyEx( HKEY_LOCAL_MACHINE,
//                "SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
//                0, KEY_QUERY_VALUE, &hKey );
//             dwBufLen=80;
//             retv=RegQueryValueEx(hKey, "ProductType", NULL, NULL,
//                (LPBYTE) szProductType, &dwBufLen);
//             if(retv==...
//             RegCloseKey(hKey);
//             if(lstrcmpi("WINNT", szProductType)==0)
//                printf("Workstation ");
//             if(lstrcmpi("SERVERNT", szProductType)==0)
//                printf("Server ");
//          }

// Display version, service pack (if any), and build number.

//          printf("version %d.%d %s (Build %d)\n",
//             osvi.dwMajorVersion,
//             osvi.dwMinorVersion,
//             osvi.szCSDVersion,
//             osvi.dwBuildNumber & 0xFFFF);

            break;

         } // switch(osvi.dwPlatformId)


// --------------------- service pack
         pnts=(const unsigned char *)strstr(Osvi.szCSDVersion, "Service Pack ");
         if(pnts!=NULL)
         {
            pnts+=strlen("Service Pack ");
            sscanf((const char *)pnts, "%d", &ret_sp);
         }

      } // if(!exit_fl)

      *piWin32Vers = retval;
      iWindowsVersion = retval;
      iWindowsVersionCut = ((retval < WinNumOfCurrentWinVersions)?retval:WinXP);

      *piWinSP=ret_sp;
      iWindowsSP=ret_sp;

      if(retval==WinUnkn) retc=KP_E_UNKNOWN_SYSTEM;
   }

// if(SUCCEEDED(retc)) switch(retval)
// {
// case Win95: KpMsgOut((const unsigned char *)"Win95"); break;
// case Win98: KpMsgOut((const unsigned char *)"Win98"); break;
// case WinNT40: KpMsgOut((const unsigned char *)"WinNT40"); break;
// case Win2000: KpMsgOut((const unsigned char *)"Win2000"); break;
// }

   KP_ASSERT(iWindowsVersion < WinNumOfCurrentWinVersions, KP_E_SYSTEM_ERROR, null, False);

return(retc);
}


//---------------------------- get file name of currently executed program
//---------------------------- szNameBuf[KP_MAX_FNAME_LEN+1]
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
HRESULT GetExeFileName(unsigned char *szNameBuf)
{
HRESULT retc=S_OK;
HINSTANCE hInstance;
DWORD retw;

   hInstance=GetModuleHandle(NULL);
   if(hInstance==NULL)
   {
      retw=GetLastError();
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      if(GetModuleFileName(hInstance, (char *)szNameBuf, KP_MAX_FNAME_LEN)==0)
      {
         retw=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

// if(SUCCEEDED(retc))
// {
//    if(_getcwd(szNameBuf, KP_MAX_FNAME_LEN)==NULL)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYS_ERROR, null, True, __FILE__, __LINE__, 0L);
// }

   if(SUCCEEDED(retc)) szNameBuf[KP_MAX_FNAME_LEN]=Nul;

return(retc);
}


// change to FindWindow()
HWND GetWindowByName(const unsigned char *lpszWinName, bool bFullName, HWND hPreviousFound)
{
HWND cur_wnd = NULL;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
// fstream out_file("kpswkl.lst", ios::out);

// out_file << lpszWinName << endl << endl;

   if(hPreviousFound) cur_wnd = GetWindow(hPreviousFound, GW_HWNDNEXT);
   else cur_wnd = GetTopWindow(NULL);

   while(cur_wnd != NULL)
   {
      if(GetWindowText(cur_wnd, (char *)str_buf, KP_MAX_FNAME_LEN) > 0)
      {
// out_file << str_buf << endl;
         if(bFullName)
         {
            if(strcmp(str_buf, lpszWinName) == 0)
               break;
         }
         else
         {
            if(strstr(str_buf, lpszWinName) != NULL)
               break;
         }
      }

      cur_wnd = GetWindow(cur_wnd, GW_HWNDNEXT);
   }

// if(cur_wnd) out_file << "----- radom" << endl;
// out_file.close();

return(cur_wnd);
}


HWND GetChildWindow(HWND wParent, int iOrderNumber)
{
HRESULT retc=S_OK;
HWND cur_wnd=NULL;
int ii;
#if FALSE // #if TRUE // #ifdef Debug
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
#endif

   if(wParent!=NULL)
   {

#if FALSE // #if TRUE // #ifdef Debug
str_buf[0] = Nul;
GetWindowText(wParent, (char *)str_buf, KP_MAX_FNAME_LEN);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

      cur_wnd=GetWindow(wParent, GW_CHILD);
#if FALSE // #if TRUE // #ifdef Debug
// KP_TRACE("-----");
if(cur_wnd!=NULL)
{
str_buf[0] = Nul;
GetWindowText(cur_wnd, (char *)str_buf, KP_MAX_FNAME_LEN);
// KP_TRACE(str_buf);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
}
#endif
      for(ii=0; (ii<iOrderNumber) && (cur_wnd!=NULL); ii++)
      {
         cur_wnd=GetWindow(cur_wnd, GW_HWNDNEXT);
#if FALSE // #if TRUE // #ifdef Debug
if(cur_wnd!=NULL)
{
str_buf[0] = Nul;
GetWindowText(cur_wnd, (char *)str_buf, KP_MAX_FNAME_LEN);
// KP_TRACE(str_buf);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
}
#endif
      }
   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(cur_wnd);
}


HWND GetThreadWindow(DWORD lThreadId, HWND hPreviousFound)
{
HWND cur_wnd = NULL;

   if(hPreviousFound) cur_wnd = GetWindow(hPreviousFound, GW_HWNDNEXT);
   else cur_wnd = GetTopWindow(NULL);

   while(cur_wnd != NULL)
   {
      if(lThreadId == GetWindowThreadProcessId(cur_wnd, NULL)) break;
      cur_wnd = GetWindow(cur_wnd, GW_HWNDNEXT);
   }

return(cur_wnd);
}


HWND GetProcessWindow(DWORD lProcId, HWND hPreviousFound)
{
HWND cur_wnd = NULL;
DWORD proc_id;

   if(hPreviousFound) cur_wnd = GetWindow(hPreviousFound, GW_HWNDNEXT);
   else cur_wnd = GetTopWindow(NULL);

   while(cur_wnd != NULL)
   {
      GetWindowThreadProcessId(cur_wnd, &proc_id);
#if FALSE // #ifdef Debug
static unsigned char win_name[KP_MAX_FNAME_LEN + 1];
if(!GetWindowText(cur_wnd, (char *)win_name, KP_MAX_FNAME_LEN)) win_name[0] = Nul;
KP_TRACE_3("GetProcessWindow(): %5ld %5ld [%s]", proc_id, lProcId, win_name);
#endif
      if(lProcId == proc_id) break;
      cur_wnd = GetWindow(cur_wnd, GW_HWNDNEXT);
   }

return(cur_wnd);
}


HRESULT SendStringToWindow(HWND wWindow, const unsigned char *lpszOutStr, HWND /* hTopWindow */)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
#if FALSE // #ifdef Debug
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+100];
#endif

// KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

   if((wWindow!=NULL) && (lpszOutStr!=NULL))
   {
      pnts=lpszOutStr;
      while(*pnts)
      {
//       if(SUCCEEDED(retc)) retc = theKpStAppPtr->KpBringToTop(hTopWindow);

         if(SUCCEEDED(retc))
         {
//          SendMessage(wWindow, WM_CHAR, *pnts++, 0L);
            PostMessage(wWindow, WM_CHAR, *pnts++, 0L);
         }
         if(SUCCEEDED(retc)) retc = KpSleep(100, HWND_DESKTOP); // Sleep(100); // 200 // 20
      }

#if FALSE // #ifdef Debug
sprintf((char *)str_buf, "%d %s", wWindow, lpszOutStr);
KP_TRACE(str_buf);
#endif

   }
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}


// ============================================
int iWndCaptionHgt = KPW_WND_CAPTION_HGT_INI;
int iWndMenuHgt = KPW_WND_MENU_HGT_INI;
int iWndBorderWdt = KPW_WND_BORDER_WDT_INI;


HRESULT InitWindowPars(void)
{
HRESULT retc=S_OK;
WNDCLASSEX wcx;
HWND test_wnd=NULL;
RECT cli_rect;
RECT wnd_rect;
HMENU menu=NULL;
HBRUSH brush;
// HPEN pen = NULL;
// EXTLOGPEN log_pen;

// --------------------------
   brush = NULL;

#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#else

   brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));
#endif

// ---------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "KPTEST",
      wcx.lpfnWndProc   = DefWindowProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
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

// ---------------------------------
   if(SUCCEEDED(retc))
   {
      test_wnd=CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPTEST",
         "KpTest",      // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX |WS_THICKFRAME
//       |WS_MINIMIZE
#ifdef Debug
//       |WS_VISIBLE
#endif
         , // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         200, // CW_USEDEFAULT, // int x,               // horizontal position of window
         200, // CW_USEDEFAULT, // int y,               // vertical position of window
         200, // CW_USEDEFAULT, // int nWidth,           // window width
         200, // CW_USEDEFAULT, // int nHeight,          // window height
         HWND_DESKTOP,  // HWND hWndParent,      // handle to parent or owner window
         NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
         hKpInstance,
         NULL           // LPVOID lpParam        // pointer to window-creation data
      );

      if(test_wnd==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// if(SUCCEEDED(retc)) ShowWindow(test_wnd, SW_SHOW);

// --------------------------------
   if(SUCCEEDED(retc)) if(!GetClientRect(test_wnd, &cli_rect))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(!GetWindowRect(test_wnd, &wnd_rect))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      iWndBorderWdt=((wnd_rect.right-wnd_rect.left)-(cli_rect.right-cli_rect.left))/2;
      iWndCaptionHgt=((wnd_rect.bottom-wnd_rect.top)-(cli_rect.bottom-cli_rect.top))-2*iWndBorderWdt;
   }

#if TRUE // #ifndef Debug
   if(test_wnd!=NULL) ::DestroyWindow(test_wnd);
#endif
   test_wnd=NULL;

// ------------------------------- menu
   if(SUCCEEDED(retc))
   {
      menu=CreateMenu();
      if(menu==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      if(!AppendMenu(menu, MF_STRING, KP_ID_FILE, "File"))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// ---------------------------------
   if(SUCCEEDED(retc))
   {
      test_wnd=CreateWindowEx
      (
         0,                      // DWORD dwExStyle,      // extended window style
         "KPTEST",
         "KpTest",      // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX |WS_THICKFRAME
//       |WS_MINIMIZE
#ifdef Debug
//       |WS_VISIBLE
#endif
         , // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
         200, // CW_USEDEFAULT, // int x,               // horizontal position of window
         200, // CW_USEDEFAULT, // int y,               // vertical position of window
         200, // CW_USEDEFAULT, // int nWidth,           // window width
         200, // CW_USEDEFAULT, // int nHeight,          // window height
         HWND_DESKTOP,  // HWND hWndParent,      // handle to parent or owner window
         menu,          // HMENU hMenu,          // handle to menu, or child-window identifier
         hKpInstance,
         NULL           // LPVOID lpParam        // pointer to window-creation data
      );

      if(test_wnd==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

// if(SUCCEEDED(retc)) ShowWindow(test_wnd, SW_SHOW);

// --------------------------------
   if(SUCCEEDED(retc)) if(!GetClientRect(test_wnd, &cli_rect))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(!GetWindowRect(test_wnd, &wnd_rect))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      iWndMenuHgt=((wnd_rect.bottom-wnd_rect.top)-(cli_rect.bottom-cli_rect.top))-2*iWndBorderWdt
         -iWndCaptionHgt;
   }

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "InitWindowPars %d %d", iWndCaptionHgt, ((wnd_rect.bottom-wnd_rect.top)-(cli_rect.bottom-cli_rect.top))-2*iWndBorderWdt /* iWndMenuHgt */);
KP_TRACE(str_buf);
#endif

#if TRUE // #ifndef Debug
   if(test_wnd!=NULL) ::DestroyWindow(test_wnd);
#endif
   test_wnd=NULL;

return(retc);
}


#if FALSE
HRESULT GetWindowPars(HWND hWindow)
{
HRESULT retc=S_OK;
RECT cli_rect;
RECT wnd_rect;

#if FALSE // #ifdef Debug // #if FALSE
int capt_hgt_sav=iWndCaptionHgt;
int brd_wdt_sav=iWndBorderWdt;
#endif

   if(hWindow==NULL) retc=E_INVALIDARG;

   if(SUCCEEDED(retc)) if(!GetClientRect(hWindow, &cli_rect))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(!GetWindowRect(hWindow, &wnd_rect))
   {
      retc=KP_E_SYSTEM_ERROR;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      iWndBorderWdt=((wnd_rect.right-wnd_rect.left)-(cli_rect.right-cli_rect.left))/2;
      iWndCaptionHgt=((wnd_rect.bottom-wnd_rect.top)-(cli_rect.bottom-cli_rect.top))-2*iWndBorderWdt;
   }

#if FALSE // #ifdef Debug //
// if(SUCCEEDED(retc))
if((capt_hgt_sav!=iWndCaptionHgt) || (brd_wdt_sav!=iWndBorderWdt))
{
char str_buf[100];
// sprintf(str_buf, "%d %d", rect.left, rect.top);
sprintf(str_buf, "%d %d", iWndBorderWdt, iWndCaptionHgt);
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
KP_TRACE(str_buf);
}
#endif

return(retc);
}
#endif


#if FALSE
int GetCaptionHgt(HWND hWindow)
{
HRESULT retc=S_OK;
int capt_hgt;

   capt_hgt=KPW_WND_CAPTION_HGT_INI+KPW_WND_MENU_HGT;

   retc=GetWindowPars(hWindow);
   if(SUCCEEDED(retc)) capt_hgt=iWndCaptionHgt;

return(capt_hgt);
}
#endif


#if FALSE
int GetBorderWdt(HWND hWindow)
{
HRESULT retc=S_OK;
int border_wdt;

   border_wdt=KPW_WND_BORDER_WDT_INI;

   retc=GetWindowPars(hWindow);
   if(SUCCEEDED(retc)) border_wdt=iWndBorderWdt;

return(border_wdt);
}
#endif


//======================================
HRESULT InitPalette(void)
{
HRESULT retc=S_OK;

// ------------------------
#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
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
            brush = (HBRUSH)iaColorMap[KpShadowLight];
         }
      }
      else
         brush = (HBRUSH)iaColorMap[KpShadowLight];
   }

   if(pen) if(!DeleteObject(pen))
      /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen = NULL;
#endif

//  if(SUCCEEDED(retc)) KpWhiteBrush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowLight])); // brush; // CreateSolidBrush(RGB_White);


// ------------------------
#if FALSE // TRUE //
fstream out_file("colors.txt", ios::out);
out_file << "COLOR_3DDKSHADOW              : " << hex << GetSysColor(COLOR_3DDKSHADOW) << endl;
out_file << "COLOR_3DFACE                  : " << hex << GetSysColor(COLOR_3DFACE) << endl;
out_file << "COLOR_3DHIGHLIGHT             : " << hex << GetSysColor(COLOR_3DHIGHLIGHT) << endl;
out_file << "COLOR_3DHILIGHT               : " << hex << GetSysColor(COLOR_3DHILIGHT) << endl;
out_file << "COLOR_3DLIGHT                 : " << hex << GetSysColor(COLOR_3DLIGHT) << endl;
out_file << "COLOR_3DSHADOW                : " << hex << GetSysColor(COLOR_3DSHADOW) << endl;
out_file << "COLOR_ACTIVEBORDER            : " << hex << GetSysColor(COLOR_ACTIVEBORDER) << endl;
out_file << "COLOR_ACTIVECAPTION           : " << hex << GetSysColor(COLOR_ACTIVECAPTION) << endl;
out_file << "COLOR_APPWORKSPACE            : " << hex << GetSysColor(COLOR_APPWORKSPACE) << endl;
out_file << "COLOR_BACKGROUND              : " << hex << GetSysColor(COLOR_BACKGROUND) << endl;
out_file << "COLOR_BTNFACE                 : " << hex << GetSysColor(COLOR_BTNFACE) << endl;
out_file << "COLOR_BTNHIGHLIGHT            : " << hex << GetSysColor(COLOR_BTNHIGHLIGHT) << endl;
out_file << "COLOR_BTNHILIGHT              : " << hex << GetSysColor(COLOR_BTNHILIGHT) << endl;
out_file << "COLOR_BTNSHADOW               : " << hex << GetSysColor(COLOR_BTNSHADOW) << endl;
out_file << "COLOR_BTNTEXT                 : " << hex << GetSysColor(COLOR_BTNTEXT) << endl;
out_file << "COLOR_CAPTIONTEXT             : " << hex << GetSysColor(COLOR_CAPTIONTEXT) << endl;
out_file << "COLOR_DESKTOP                 : " << hex << GetSysColor(COLOR_DESKTOP) << endl;
// out_file << "COLOR_GRADIENTACTIVECAPTION   : " << hex << GetSysColor(COLOR_GRADIENTACTIVECAPTION) << endl;
// out_file << "COLOR_GRADIENTINACTIVECAPTION : " << hex << GetSysColor(COLOR_GRADIENTINACTIVECAPTION) << endl;
out_file << "COLOR_GRAYTEXT                : " << hex << GetSysColor(COLOR_GRAYTEXT) << endl;
out_file << "COLOR_HIGHLIGHT               : " << hex << GetSysColor(COLOR_HIGHLIGHT) << endl;
out_file << "COLOR_HIGHLIGHTTEXT           : " << hex << GetSysColor(COLOR_HIGHLIGHTTEXT) << endl;
// out_file << "COLOR_HOTLIGHT                : " << hex << GetSysColor(COLOR_HOTLIGHT) << endl;
out_file << "COLOR_INACTIVEBORDER          : " << hex << GetSysColor(COLOR_INACTIVEBORDER) << endl;
out_file << "COLOR_INACTIVECAPTION         : " << hex << GetSysColor(COLOR_INACTIVECAPTION) << endl;
out_file << "COLOR_INACTIVECAPTIONTEXT     : " << hex << GetSysColor(COLOR_INACTIVECAPTIONTEXT) << endl;
out_file << "COLOR_INFOBK                  : " << hex << GetSysColor(COLOR_INFOBK) << endl;
out_file << "COLOR_INFOTEXT                : " << hex << GetSysColor(COLOR_INFOTEXT) << endl;
out_file << "COLOR_MENU                    : " << hex << GetSysColor(COLOR_MENU) << endl;
// out_file << "COLOR_MENUHILIGHT             : " << hex << GetSysColor(COLOR_MENUHILIGHT) << endl;
// out_file << "COLOR_MENUBAR                 : " << hex << GetSysColor(COLOR_MENUBAR) << endl;
out_file << "COLOR_MENUTEXT                : " << hex << GetSysColor(COLOR_MENUTEXT) << endl;
out_file << "COLOR_SCROLLBAR               : " << hex << GetSysColor(COLOR_SCROLLBAR) << endl;
out_file << "COLOR_WINDOW                  : " << hex << GetSysColor(COLOR_WINDOW) << endl;
out_file << "COLOR_WINDOWFRAME             : " << hex << GetSysColor(COLOR_WINDOWFRAME) << endl;
out_file << "COLOR_WINDOWTEXT              : " << hex << GetSysColor(COLOR_WINDOWTEXT) << endl;
out_file.close();
#endif // #if FALSE // TRUE //

// ------------------------
#if FALSE
int ii, jj;

   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
#  if TRUE // FALSE //
#     if FALSE
      jj=(iWindowsVersion>=WinVistaC)?KpColorSchemeVista[ii]:
         ((iWindowsVersion>=WinXPc) && (iWindowsVersion<WinVistaC))?KpColorSchemeXP[ii]:
         ((iWindowsVersion>=Win2000c) && (iWindowsVersion<WinXPc))?KpColorScheme2k[ii]:
         KpColorScheme[ii];

#     else // #     if FALSE
      switch(ii)
      {                                                                 // Vista  // Win2k  // Win98
      case KpShadowNorm:                                                // C8C8C8 // D6D3CE // A0A0A0 // RGB_Gray // normal (gray) background - normalus fonas
//       jj = GetSysColor(COLOR_APPWORKSPACE);
//       jj = GetSysColor(COLOR_BACKGROUND);
//       jj=(iWindowsVersion>=WinVistaC)?RGB(200,200,200):  // C8C8C8
//          ((iWindowsVersion>=WinXPc) && (iWindowsVersion<WinVistaC))?RGB(236,233,216):
//          ((iWindowsVersion>=Win2000c) && (iWindowsVersion<WinXPc))?RGB(214,211,206): // D6D3CE
//          RGB_Gray;
         jj= // (iWindowsVersion>=WinVistaC)?RGB(200,200,200):  // C8C8C8
            GetSysColor(COLOR_3DFACE);
         break;
      case KpShadowLight: jj = GetSysColor(COLOR_3DHILIGHT); break;     // FFFFFF // FFFFFF // FFFFFF // RGB_White // light background - sviesus seseliai, sviesus tekstas
      case KpShadowDark: jj = GetSysColor(COLOR_WINDOWTEXT); break;     // 000000 // 000000 // 000000 // RGB_Black // dark background - tamsus seseliai, tamsus tekstas, invertuoto teksto fonas
                           // GetSysColor(COLOR_3DSHADOW);
      case KpShadowBlack: jj = GetSysColor(COLOR_3DDKSHADOW); break;    // 000000 // 000000 // 000000 // RGB_Black // black background - juodi seseliai
      case KpShadowBackground: jj = GetSysColor(COLOR_3DFACE); break;// A0A0A0 // A0A0A0 // A0A0A0 // RGB_Gray // fonas apie mygtuka etc.
                                 // GetSysColor(COLOR_BTNSHADOW);
      case KpShadowForeground: jj = GetSysColor(COLOR_3DFACE); break;  // A0A0A0 // A0A0A0 // A0A0A0 // RGB_Gray // paties mygtuko, etc. fonas
                                 // GetSysColor(COLOR_BTNFACE);
      case KpCaptionColor: jj = GetSysColor(COLOR_ACTIVECAPTION); break;// 800000 // 800000 // 800000 // RGB_Darkblue // lango antrastes spalva
      default: jj = RGB_Black; break;
      }

//    jj = RGB_Black;

//                               Vista     Vista     Win2k    Win98
//                                        AeroGlas standard (Win2k classic)
// COLOR_3DDKSHADOW             : 696969 : 696969 : 404040 : 0
// COLOR_3DFACE                 : f0f0f0 : f0f0f0 : c8d0d4 : c0c0c0
// COLOR_3DHIGHLIGHT            : ffffff : ffffff : ffffff : ffffff
// COLOR_3DHILIGHT              : ffffff : ffffff : ffffff : ffffff
// COLOR_3DLIGHT                : e3e3e3 : e3e3e3 : c8d0d4 : c0c0c0
// COLOR_3DSHADOW               : a0a0a0 : a0a0a0 : 808080 : 808080
// COLOR_ACTIVEBORDER           : b4b4b4 : b4b4b4 : c8d0d4 : c0c0c0
// COLOR_ACTIVECAPTION          : d1b499 : d1b499 : 6a240a : 800000
// COLOR_APPWORKSPACE           : ababab : ababab : 808080 : 808080
// COLOR_BACKGROUND             : 0      : 0      : a56e3a : a56e3a
// COLOR_BTNFACE                : f0f0f0 : f0f0f0 : c8d0d4 : c0c0c0
// COLOR_BTNHIGHLIGHT           : ffffff : ffffff : ffffff : ffffff
// COLOR_BTNHILIGHT             : ffffff : ffffff : ffffff : ffffff
// COLOR_BTNSHADOW              : a0a0a0 : a0a0a0 : 808080 : 808080
// COLOR_BTNTEXT                : 0      : 0      : 0      : 0
// COLOR_CAPTIONTEXT            : 0      : 0      : ffffff : ffffff
// COLOR_DESKTOP                : 0      : 0      : a56e3a : a56e3a
// COLOR_GRAYTEXT               : 808080 : 808080 : 808080 : 808080
// COLOR_HIGHLIGHT              : ff9933 : ff9933 : 6a240a : 800000
// COLOR_HIGHLIGHTTEXT          : ffffff : ffffff : ffffff : ffffff
// COLOR_INACTIVEBORDER         : fcf7f4 : fcf7f4 : c8d0d4 : c0c0c0
// COLOR_INACTIVECAPTION        : dbcdbf : dbcdbf : 808080 : 808080
// COLOR_INACTIVECAPTIONTEXT    : 544e43 : 544e43 : c8d0d4 : c0c0c0
// COLOR_INFOBK                 : e1ffff : e1ffff : e1ffff : e1ffff
// COLOR_INFOTEXT               : 0      : 0      : 0      : 0
// COLOR_MENU                   : f0f0f0 : f0f0f0 : c8d0d4 : c0c0c0
// COLOR_MENUTEXT               : 0      : 0      : 0      : 0
// COLOR_SCROLLBAR              : c8c8c8 : c8c8c8 : c8d0d4 : c0c0c0
// COLOR_WINDOW                 : ffffff : ffffff : ffffff : ffffff
// COLOR_WINDOWFRAME            : 646464 : 646464 : 0      : 0
// COLOR_WINDOWTEXT             : 0      : 0      : 0      : 0

COLOR_3DDKSHADOW
COLOR_3DFACE
COLOR_3DHIGHLIGHT
COLOR_3DHILIGHT
COLOR_3DLIGHT
COLOR_3DSHADOW
COLOR_ACTIVEBORDER
COLOR_ACTIVECAPTION
COLOR_APPWORKSPACE
COLOR_BACKGROUND
COLOR_BTNFACE
COLOR_BTNHIGHLIGHT
COLOR_BTNHILIGHT
COLOR_BTNSHADOW
COLOR_BTNTEXT
COLOR_CAPTIONTEXT
COLOR_DESKTOP
COLOR_GRAYTEXT
COLOR_HIGHLIGHT
COLOR_HIGHLIGHTTEXT
COLOR_INACTIVEBORDER
COLOR_INACTIVECAPTION
COLOR_INACTIVECAPTIONTEXT
COLOR_INFOBK
COLOR_INFOTEXT
COLOR_MENU
COLOR_MENUTEXT
COLOR_SCROLLBAR
COLOR_WINDOW
COLOR_WINDOWFRAME
COLOR_WINDOWTEXT
#     endif // #     else // #     if FALSE

#     if FALSE // #ifdef Debug
char str_buf[200];
sprintf(str_buf, "iWindowsVersion:%d WinXP:%d", iWindowsVersion, WinXP);

// sprintf(str_buf, "ii:%d jj:%x KpColorSchemeXP: %x KpColorScheme:%x",
//                   ii, jj, KpColorSchemeXP[ii], KpColorScheme[ii]);
KP_TRACE(str_buf);
#     endif

// ------------------------
      if(aPenSchemeWin[ii]!=NULL)
         if(!DeleteObject(aPenSchemeWin[ii]))
         /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      aPenSchemeWin[ii]=NULL;

      aPenSchemeWin[ii]=CreatePen(PS_SOLID, 1, jj);
      if(aPenSchemeWin[ii]==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

#  else // #  if TRUE // FALSE //
      aPenSchemeWin[ii]=NULL;

#  endif // #else // #  if TRUE // FALSE //
   }

#endif // #if FALSE

return(retc);
}


//======================================
int iaCtrlHeights[NumOfWinVersions11][KPW_NUM_OF_CONTROL_STYLES_2] =
#if FALSE
{
   18,                     22,   20,   18,   18,   //   WinUnkn,

   18,                     22,   20,   18,   18,   //   Win20,

   18,                     22,   20,   18,   18,   //   Win31c,  // common Windows 3.1x
   18,                     22,   20,   18,   18,   //   Win31,   // Win32s on Windows 3.1
   18,                     22,   20,   18,   18,   //   Win311,  // Windows 3.11 for Workgroups (with Win32s ?)

   18,                     22,   20,   18,   18,   //   Win95c,  // common Windows 95
   18,                     22,   20,   18,   18,   //   Win95,
   18,                     22,   20,   18,   18,   //   Win95OSR2,

   18,                     22,   20,   18,   18,   //   Win98c,  // common Windows 98
   18,                     22,   20,   18,   18,   //   Win98,
   18 /* 16 */ /* 20 */,   22,   20,   18,   18,   //   Win98SE, // Windows 98 Second Edition
   18,                     22,   20,   18,   18,   //   WinCE,
   18,                     22,   20,   18,   18,   //   WinMe,

   18,                     22,   20,   18,   18,   //   WinNT,

   18,                     22,   20,   18,   18,   //   WinNT35c, // common Windows NT 3.5x
   18,                     22,   20,   18,   18,   //   WinNT351,

   18,                     22,   20,   18,   18,   //   WinNT40c, // common Windows 4.0
   18,                     22,   20,   18,   18,   //   WinNT40,
   18,                     22,   20,   18,   18,   //   WinNT40s, // Windows NT 4.0 server

   18,                     22,   20,   18,   18,   //   Win2000c, // common Windows 2000
   18,                     22,   20,   18,   18,   //   Win2000,
   18,                     22,   20,   18,   18,   //   Win2000s,
   18,                     22,   20,   18,   18,   //   WinXP,
   18,                     22,   20,   18,   18,   //   Win2003s, // Windows Server 2003
};
#endif
{
   24, 24, 24, 24, 24,   //   WinUnkn,

   24, 24, 24, 24, 24,   //   Win20,

   24, 24, 24, 24, 24,   //   Win31c,  // common Windows 3.1x
   24, 24, 24, 24, 24,   //   Win31,   // Win32s on Windows 3.1
   24, 24, 24, 24, 24,   //   Win311,  // Windows 3.11 for Workgroups (with Win32s ?)

   24, 24, 24, 24, 24,   //   Win95c,  // common Windows 95
   24, 24, 24, 24, 24,   //   Win95,
   24, 24, 24, 24, 24,   //   Win95OSR2,

   24, 24, 24, 24, 24,   //   Win98c,  // common Windows 98
   24, 24, 24, 24, 24,   //   Win98,
   24, 24, 24, 24, 24,   //   Win98SE, // Windows 98 Second Edition
   24, 24, 24, 24, 24,   //   WinCE,
   24, 24, 24, 24, 24,   //   WinMe,

   24, 24, 24, 24, 24,   //   WinNT,

   24, 24, 24, 24, 24,   //   WinNT35c,     // common Windows NT 3.5x
   24, 24, 24, 24, 24,   //   WinNT351,

   24, 24, 24, 24, 24,   //   WinNT40c,     // common Windows 4.0
   24, 24, 24, 24, 24,   //   WinNT40,
   24, 24, 24, 24, 24,   //   WinNT40s,     // Windows NT 4.0 server

   24, 24, 24, 24, 24,   //   Win2000c,     // common Windows 2000
   24, 24, 24, 24, 24,   //   Win2000,      // Windows 2000 Professional // Windows 2000
   24, 24, 24, 24, 24,   //   Win2000s,     // Windows 2000 Server  // atsirado nuo 2004.10.01

   24, 24, 24, 24, 24,   //   WinXPc,       // common Windows XP

   24, 24, 24, 24, 24,   //   WinXP,        // Windows XP
   24, 24, 24, 24, 24,   //   Win2003s,     // Windows Server 2003
   24, 24, 24, 24, 24,   //   WinXpStart,   // Windows XP Starter Edition
   24, 24, 24, 24, 24,   //   WinXpHome,    // Windows XP Home Edition
   24, 24, 24, 24, 24,   //   WinXpPro,     // Windows XP Professional
   24, 24, 24, 24, 24,   //   WinXpMedia,   // Windows XP Media Center Edition
   24, 24, 24, 24, 24,   //   WinXpTablet,  // Windows XP Tablet PC Edition // Windows CE analogas?
   24, 24, 24, 24, 24,   //   WinXP64,      // Windows XP Professional x64 Edition
   24, 24, 24, 24, 24,   //   Win2003sR2,   // Windows Server 2003 R2

   24, 24, 24, 24, 24,   //   WinVistaC,    // common Windows Vista
   24, 24, 24, 24, 24,   //   WinVista,     // Windows Vista
   24, 24, 24, 24, 24,   //   WinVistaH,    // Windows Vista Home Basic
   24, 24, 24, 24, 24,   //   WinVistaHP,   // Windows Vista Home Premium
   24, 24, 24, 24, 24,   //   WinVistaB,    // Windows Vista Business
   24, 24, 24, 24, 24,   //   WinVistaE,    // Windows Vista Enterprise
   24, 24, 24, 24, 24,   //   WinVistaU,    // Windows Vista Ultimate
   24, 24, 24, 24, 24,   //   Win2008s,     // Windows Server 2008 // Windows Server Longhorn

   24, 24, 24, 24, 24,   //   Win7,         // Windows 7
   24, 24, 24, 24, 24,   //   Win8,         // Windows 8
   24, 24, 24, 24, 24,   //   Win81,        // Windows 8.1
   24, 24, 24, 24, 24,   //   Win10,        // Windows 10

   24, 24, 24, 24, 24,   //   WinNtFuture,  // common Windows NT based future versions
};


int iaBoxHeights[NumOfWinVersions11][KPW_NUM_OF_CONTROL_STYLES_2] =
{
   24, 24, 24, 24, 24,   //   WinUnkn,

   24, 24, 24, 24, 24,   //   Win20,

   24, 24, 24, 24, 24,   //   Win31c,  // common Windows 3.1x
   24, 24, 24, 24, 24,   //   Win31,   // Win32s on Windows 3.1
   24, 24, 24, 24, 24,   //   Win311,  // Windows 3.11 for Workgroups (with Win32s ?)

   24, 24, 24, 24, 24,   //   Win95c,  // common Windows 95
   24, 24, 24, 24, 24,   //   Win95,
   24, 24, 24, 24, 24,   //   Win95OSR2,

   24, 24, 24, 24, 24,   //   Win98c,  // common Windows 98
   24, 24, 24, 24, 24,   //   Win98,
   24, 24, 24, 24, 24,   //   Win98SE, // Windows 98 Second Edition
   24, 24, 24, 24, 24,   //   WinCE,
   24, 24, 24, 24, 24,   //   WinMe,

   24, 24, 24, 24, 24,   //   WinNT,

   24, 24, 24, 24, 24,   //   WinNT35c, // common Windows NT 3.5x
   24, 24, 24, 24, 24,   //   WinNT351,

   24, 24, 24, 24, 24,   //   WinNT40c, // common Windows 4.0
   24, 24, 24, 24, 24,   //   WinNT40,
   24, 24, 24, 24, 24,   //   WinNT40s, // Windows NT 4.0 server

   24, 24, 24, 24, 24,   //   Win2000c,  // 19  // common Windows 2000
   24, 24, 24, 24, 24,   //   Win2000,   // 20  // Windows 2000 Professional // Windows 2000
   24, 24, 24, 24, 24,   //   Win2000s,  // 21  // Windows 2000 Server  // atsirado nuo 2004.10.01

   24, 24, 24, 24, 24,   //   WinXPc,    // 22  // common Windows XP

   24, 24, 24, 24, 24,   //   WinXP,     // 23  // Windows XP           // 20 before 2004.10.01
   24, 24, 24, 24, 24,   //   Win2003s,  // 24  // Windows Server 2003  // 21 before 2004.10.01
   24, 24, 24, 24, 24,   //   WinXpStart,// 25  // Windows XP Starter Edition
   24, 24, 24, 24, 24,   //   WinXpHome, // 26  // Windows XP Home Edition
   24, 24, 24, 24, 24,   //   WinXpPro,  // 27  // Windows XP Professional
   24, 24, 24, 24, 24,   //   WinXpMedia,// 28  // Windows XP Media Center Edition
   24, 24, 24, 24, 24,   //   WinXpTablet,// 29 // Windows XP Tablet PC Edition // Windows CE analogas?
   24, 24, 24, 24, 24,   //   WinXP64,   // 30  // Windows XP Professional x64 Edition
   24, 24, 24, 24, 24,   //   Win2003sR2,// 31  // Windows Server 2003 R2

   24, 24, 24, 24, 24,   //   WinVistaC, // 32  // common Windows Vista

   24, 24, 24, 24, 24,   //   WinVista,  // 33  // Windows Vista
   24, 24, 24, 24, 24,   //   WinVistaH, // 34  // Windows Vista Home Basic
   24, 24, 24, 24, 24,   //   WinVistaHP,// 35  // Windows Vista Home Premium
   24, 24, 24, 24, 24,   //   WinVistaB, // 36  // Windows Vista Business
   24, 24, 24, 24, 24,   //   WinVistaE, // 37  // Windows Vista Enterprise
   24, 24, 24, 24, 24,   //   WinVistaU, // 38  // Windows Vista Ultimate
   24, 24, 24, 24, 24,   //   Win2008s,  // 39  // Windows Server 2008 // Windows Server Longhorn

   24, 24, 24, 24, 24,   //   Win7,      // 40  // Windows 7
   24, 24, 24, 24, 24,   //   Win8,      // 41  // Windows 8
   24, 24, 24, 24, 24,   //   Win81,     // 42  // Windows 8.1
   24, 24, 24, 24, 24,   //   Win10,     // 43  // Windows 10

   24, 24, 24, 24, 24,   //   WinNtFuture,// 44 // common Windows NT based future versions
};


int iaCtrlRowHeights[NumOfWinVersions11][KPW_NUM_OF_CONTROL_STYLES_2] =
{
#if FALSE
   17,          18,      17,   17,   17,   //   WinUnkn,

   17,          18,      17,   17,   17,   //   Win20,

   17,          18,      17,   17,   17,   //   Win31c,  // common Windows 3.1x
   17,          18,      17,   17,   17,   //   Win31,   // Win32s on Windows 3.1
   17,          18,      17,   17,   17,   //   Win311,  // Windows 3.11 for Workgroups (with Win32s ?)

   17,          18,      17,   17,   17,   //   Win95c,  // common Windows 95
   17,          18,      17,   17,   17,   //   Win95,
   17,          18,      17,   17,   17,   //   Win95OSR2,

   17,          18,      17,   17,   17,   //   Win98c,  // common Windows 98
   17,          18,      17,   17,   17,   //   Win98,
   17,          18,      17,   17,   17,   //   Win98SE, // Windows 98 Second Edition
   17,          18,      17,   17,   17,   //   WinCE,
   17,          18,      17,   17,   17,   //   WinMe,

   17,          18,      17,   17,   17,   //   WinNT,

   17,          18,      17,   17,   17,   //   WinNT35c,   // common Windows NT 3.5x
   17,          18,      17,   17,   17,   //   WinNT351,

   17,          18,      17,   17,   17,   //   WinNT40c,   // common Windows 4.0
   17,          18,      17,   17,   17,   //   WinNT40,
   17,          18,      17,   17,   17,   //   WinNT40s,   // Windows NT 4.0 server

   17,          18,      17,   17,   17,   //   Win2000c,   // common Windows 2000
   17,          18,      17,   17,   17,   //   Win2000,    // Windows 2000 Professional // Windows 2000
   17,          18,      17,   17,   17,   //   Win2000s,   // Windows 2000 Server  // atsirado nuo 2004.10.01

   17,          18,      17,   17,   17,   //   WinXPc,     // common Windows XP

   17,          18,      17,   17,   17,   //   WinXP,      // Windows XP
   17,          18,      17,   17,   17,   //   Win2003s,   // Windows Server 2003
   17,          18,      17,   17,   17,   //   WinXpStart, // Windows XP Starter Edition
   17,          18,      17,   17,   17,   //   WinXpHome,  // Windows XP Home Edition
   17,          18,      17,   17,   17,   //   WinXpPro,   // Windows XP Professional
   17,          18,      17,   17,   17,   //   WinXpMedia, // Windows XP Media Center Edition
   17,          18,      17,   17,   17,   //   WinXpTablet,// Windows XP Tablet PC Edition // Windows CE analogas?
   17,          18,      17,   17,   17,   //   WinXP64,    // Windows XP Professional x64 Edition
   17,          18,      17,   17,   17,   //   Win2003sR2, // Windows Server 2003 R2

   17,          18,      17,   17,   17,   //   WinVistaC,  // common Windows Vista

   17,          18,      17,   17,   17,   //   WinVista,   // Windows Vista
   17,          18,      17,   17,   17,   //   WinVistaH,  // Windows Vista Home Basic
   17,          18,      17,   17,   17,   //   WinVistaHP, // Windows Vista Home Premium
   17,          18,      17,   17,   17,   //   WinVistaB,  // Windows Vista Business
   17,          18,      17,   17,   17,   //   WinVistaE,  // Windows Vista Enterprise
   17,          18,      17,   17,   17,   //   WinVistaU,  // Windows Vista Ultimate
   17,          18,      17,   17,   17,   //   Win2008s,   // Windows Server 2008 // Windows Server Longhorn

   17,          18,      17,   17,   17,   //   Win7,       // Windows 7

   17,          18,      17,   17,   17,   //   WinNtFuture,// common Windows NT based future versions
#endif
// svarbu – listams lzdshp.exe reikia 16
   16,          18,      17,   17,   17,   //   WinUnkn,

   16,          18,      17,   17,   17,   //   Win20,

   16,          18,      17,   17,   17,   //   Win31c,  // common Windows 3.1x
   16,          18,      17,   17,   17,   //   Win31,   // Win32s on Windows 3.1
   16,          18,      17,   17,   17,   //   Win311,  // Windows 3.11 for Workgroups (with Win32s ?)

   16,          18,      17,   17,   17,   //   Win95c,  // common Windows 95
   16,          18,      17,   17,   17,   //   Win95,
   16,          18,      17,   17,   17,   //   Win95OSR2,

   16,          18,      17,   17,   17,   //   Win98c,  // common Windows 98
   16,          18,      17,   17,   17,   //   Win98,
   16,          18,      17,   17,   17,   //   Win98SE, // Windows 98 Second Edition
   16,          18,      17,   17,   17,   //   WinCE,
   16,          18,      17,   17,   17,   //   WinMe,

   16,          18,      17,   17,   17,   //   WinNT,

   16,          18,      17,   17,   17,   //   WinNT35c,   // common Windows NT 3.5x
   16,          18,      17,   17,   17,   //   WinNT351,

   16,          18,      17,   17,   17,   //   WinNT40c,   // common Windows 4.0
   16,          18,      17,   17,   17,   //   WinNT40,
   16,          18,      17,   17,   17,   //   WinNT40s,   // Windows NT 4.0 server

   16,          18,      17,   17,   17,   //   Win2000c,   // common Windows 2000
   16,          18,      17,   17,   17,   //   Win2000,    // Windows 2000 Professional // Windows 2000
   16,          18,      17,   17,   17,   //   Win2000s,   // Windows 2000 Server  // atsirado nuo 2004.10.01

   16,          18,      17,   17,   17,   //   WinXPc,     // common Windows XP

   16,          18,      17,   17,   17,   //   WinXP,      // Windows XP
   16,          18,      17,   17,   17,   //   Win2003s,   // Windows Server 2003
   16,          18,      17,   17,   17,   //   WinXpStart, // Windows XP Starter Edition
   16,          18,      17,   17,   17,   //   WinXpHome,  // Windows XP Home Edition
   16,          18,      17,   17,   17,   //   WinXpPro,   // Windows XP Professional
   16,          18,      17,   17,   17,   //   WinXpMedia, // Windows XP Media Center Edition
   16,          18,      17,   17,   17,   //   WinXpTablet,// Windows XP Tablet PC Edition // Windows CE analogas?
   16,          18,      17,   17,   17,   //   WinXP64,    // Windows XP Professional x64 Edition
   16,          18,      17,   17,   17,   //   Win2003sR2, // Windows Server 2003 R2

   16,          18,      17,   17,   17,   //   WinVistaC,  // common Windows Vista

   16,          18,      17,   17,   17,   //   WinVista,   // Windows Vista
   16,          18,      17,   17,   17,   //   WinVistaH,  // Windows Vista Home Basic
   16,          18,      17,   17,   17,   //   WinVistaHP, // Windows Vista Home Premium

   16,          18,      17,   17,   17,   //   WinVistaB,  // Windows Vista Business
   16,          18,      17,   17,   17,   //   WinVistaE,  // Windows Vista Enterprise
   16,          18,      17,   17,   17,   //   WinVistaU,  // Windows Vista Ultimate
   16,          18,      17,   17,   17,   //   Win2008s,   // Windows Server 2008 // Windows Server Longhorn

   16,          18,      17,   17,   17,   //   Win7,       // Windows 7
   16,          18,      17,   17,   17,   //   Win8,       // Windows 8
   16,          18,      17,   17,   17,   //   Win81,      // Windows 8.1
   16,          18,      17,   17,   17,   //   Win10,      // Windows 10

   16,          18,      17,   17,   17,   //   WinNtFuture,// common Windows NT based future versions
};

int iaCtrlTextFactors[KPW_NUM_OF_CONTROL_STYLES_2] =
{
   75, // 65, // 85, // 75, // KPW_CONTROL_STYLE_NORMAL
   115, // 120, // 105, // 95, // KPW_CONTROL_STYLE_HEADING_3
   92, // KPW_CONTROL_STYLE_MONOSPACE
   90, // KPW_CONTROL_STYLE_BOLD
   75, // KPW_CONTROL_STYLE_CAPTION
};

int iaCtrlTextFactorsMean[KPW_NUM_OF_CONTROL_STYLES_2] =
{
   60, // KPW_CONTROL_STYLE_NORMAL
   115, // KPW_CONTROL_STYLE_HEADING_3
   92, // KPW_CONTROL_STYLE_MONOSPACE
   75, // KPW_CONTROL_STYLE_BOLD
   75, // KPW_CONTROL_STYLE_CAPTION
};

int iaCtrlFntWghts[KPW_NUM_OF_CONTROL_STYLES_2] =
{
   FW_NORMAL,     // KPW_CONTROL_STYLE_NORMAL
   FW_SEMIBOLD,   // KPW_CONTROL_STYLE_HEADING_3
   FW_NORMAL,     // KPW_CONTROL_STYLE_MONOSPACE
   FW_SEMIBOLD,   // KPW_CONTROL_STYLE_BOLD
   FW_SEMIBOLD,   // KPW_CONTROL_STYLE_CAPTION
};

int iaCtrlFntHghts[NumOfWinVersions11][KPW_NUM_OF_CONTROL_STYLES_2] =
{
   16,            18,            16,     16,  16, //   WinUnkn,

   16,            18,            16,     16,  16, //   Win20,

   16,            18,            16,     16,  16, //   Win31c,  // common Windows 3.1x
   16,            18,            16,     16,  16, //   Win31,   // Win32s on Windows 3.1
   16,            18,            16,     16,  16, //   Win311,  // Windows 3.11 for Workgroups (with Win32s ?)

   16,            18,            16,     16,  16, //   Win95c,  // common Windows 95
   16,            18,            16,     16,  16, //   Win95,
   16,            18,            16,     16,  16, //   Win95OSR2,

   16,            18,            16,     16,  16, //   Win98c,      // common Windows 98
   16,            18,            16,     16,  16, //   Win98,
   16 /* 18 */,   18 /* 20 */,   16,     16,  16, //   Win98SE,     // Windows 98 Second Edition
   16,            18,            16,     16,  16, //   WinCE,
   16,            18,            16,     16,  16, //   WinMe,

   16,            18,            16,     16,  16, //   WinNT,

   16,            18,            16,     16,  16, //   WinNT35c,    // common Windows NT 3.5x
   16,            18,            16,     16,  16, //   WinNT351,

   16,            18,            16,     16,  16, //   WinNT40c,    // common Windows 4.0
   16,            18,            16,     16,  16, //   WinNT40,
   16,            18,            16,     16,  16, //   WinNT40s,    // Windows NT 4.0 server

   16,            18,            16,     16,  16, //   Win2000c,    // common Windows 2000
   16,            18,            16,     16,  16, //   Win2000,     // Windows 2000 Professional // Windows 2000
   16,            18,            16,     16,  16, //   Win2000s,    // Windows 2000 Server  // atsirado nuo 2004.10.01

   16,            18,            16,     16,  16, //   WinXPc,      // common Windows XP

   16,            18,            16,     16,  16, //   WinXP,       // Windows XP           // 20 before 2004.10.01
   16,            18,            16,     16,  16, //   Win2003s,    // Windows Server 2003  // 21 before 2004.10.01
   16,            18,            16,     16,  16, //   WinXpStart,  // Windows XP Starter Edition
   16,            18,            16,     16,  16, //   WinXpHome,   // Windows XP Home Edition
   16,            18,            16,     16,  16, //   WinXpPro,    // Windows XP Professional
   16,            18,            16,     16,  16, //   WinXpMedia,  // Windows XP Media Center Edition
   16,            18,            16,     16,  16, //   WinXpTablet, // Windows XP Tablet PC Edition // Windows CE analogas?
   16,            18,            16,     16,  16, //   WinXP64,     // Windows XP Professional x64 Edition
   16,            18,            16,     16,  16, //   Win2003sR2,  // Windows Server 2003 R2

   16,            18,            16,     16,  16, //   WinVistaC,   // common Windows Vista
   16,            18,            16,     16,  16, //   WinVista,    // Windows Vista
   16,            18,            16,     16,  16, //   WinVistaH,   // Windows Vista Home Basic
   16,            18,            16,     16,  16, //   WinVistaHP,  // Windows Vista Home Premium
   16,            18,            16,     16,  16, //   WinVistaB,   // Windows Vista Business
   16,            18,            16,     16,  16, //   WinVistaE,   // Windows Vista Enterprise
   16,            18,            16,     16,  16, //   WinVistaU,   // Windows Vista Ultimate
   16,            18,            16,     16,  16, //   Win2008s,    // Windows Server 2008 // Windows Server Longhorn

   16,            18,            16,     16,  16, //   Win7,        // Windows 7
   16,            18,            16,     16,  16, //   Win8,        // Windows 8
   16,            18,            16,     16,  16, //   Win81,       // Windows 8.1
   16,            18,            16,     16,  16, //   Win10,       // Windows 10

   16,            18,            16,     16,  16, //   WinNtFuture, // common Windows NT based future versions
};


int iaCtrlFntWdtFactors[KPW_NUM_OF_CONTROL_STYLES_2] =
{
   40, // KPW_CONTROL_STYLE_NORMAL
   45, // KPW_CONTROL_STYLE_HEADING_3
   50, // KPW_CONTROL_STYLE_MONOSPACE
   40, // KPW_CONTROL_STYLE_BOLD
   40, // KPW_CONTROL_STYLE_CAPTION
};

LPCTSTR iaCtrlTypefaces[KPW_NUM_OF_CONTROL_STYLES_2] =
{
   "Tahoma", // "HelveticaLT", // "Arial", // "Verdana"  // KPW_CONTROL_STYLE_NORMAL
   "Tahoma", // "HelveticaLT", // "Arial",               // KPW_CONTROL_STYLE_HEADING_3
   "LucidaConsole", // "Courier", // "MonospaceLT", //   // KPW_CONTROL_STYLE_MONOSPACE
   "Tahoma", // "HelveticaLT", // "Arial", // "Verdana"  // KPW_CONTROL_STYLE_BOLD
   "Tahoma", // "HelveticaLT", // "Arial", // "Verdana"  // KPW_CONTROL_STYLE_CAPTION
};

DWORD laCtrlCharSets[KPW_NUM_OF_CONTROL_STYLES_2] =
{
   BALTIC_CHARSET,   // KPW_CONTROL_STYLE_NORMAL
   BALTIC_CHARSET,   // KPW_CONTROL_STYLE_HEADING_3
   ANSI_CHARSET,     // KPW_CONTROL_STYLE_MONOSPACE
   BALTIC_CHARSET,   // KPW_CONTROL_STYLE_BOLD
   BALTIC_CHARSET,   // KPW_CONTROL_STYLE_CAPTION
};

DWORD laLangCharSets[KpNumOfLangs_2] =
{
   BALTIC_CHARSET,      // KpLangEn
   BALTIC_CHARSET,      // KpLangLt
   EASTEUROPE_CHARSET,  // KpLangPl_1250
   BALTIC_CHARSET,      // KpLangPl_1257
   RUSSIAN_CHARSET,     // KpLangRu_1251
   RUSSIAN_CHARSET,     // KpLangRu_0
};

// -----------------------------------------
HRESULT CrFont(HFONT *phFont, KpControlStyles iKpCtrlStyle, int iKpWndStyle)
{
HRESULT retc=S_OK;
int height;
int width;

   if((phFont==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      height=iaCtrlFntHghts[iWindowsVersionCut][iKpCtrlStyle];
      width=iaCtrlFntHghts[iWindowsVersionCut][iKpCtrlStyle]*iaCtrlFntWdtFactors[iKpCtrlStyle]/100;
      *phFont=CreateFont
         (
            height,                     // int nHeight,               // logical height of font
            width,                      // int nWidth,                // logical average character width
            0,                          // int nEscapement,           // angle of escapement
            0,                          // int nOrientation,          // base-line orientation angle
            iaCtrlFntWghts[iKpCtrlStyle], // int fnWeight,              // font weight
            False,                      // DWORD fdwItalic,           // italic attribute flag
            ((iKpWndStyle & KP_WND_URL) != 0), // DWORD fdwUnderline,        // underline attribute flag
            False,                      // DWORD fdwStrikeOut,        // strikeout attribute flag
            laLangCharSets[iMsgLangOff], // laCtrlCharSets[iKpCtrlStyle], // DWORD fdwCharSet,          // character set identifier
            OUT_DEFAULT_PRECIS,         // DWORD fdwOutputPrecision,  // output precision
            CLIP_DEFAULT_PRECIS,        // DWORD fdwClipPrecision,    // clipping precision
            DEFAULT_QUALITY,            // DWORD fdwQuality,          // output quality
            DEFAULT_PITCH, // |FF_SWISS, // DWORD fdwPitchAndFamily,   // pitch and family
            iaCtrlTypefaces[iKpCtrlStyle] // LPCTSTR lpszFace           // pointer to typeface name string
         );
      if(*phFont==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


HRESULT SetCtrlFont(HWND hCtrlWnd, KpControlStyles iKpCtrlStyle)
{
HRESULT retc=S_OK;
HFONT hfont=NULL;

   retc=CrFont(&hfont, iKpCtrlStyle);

// HGDIOBJ hObj = GetStockObject(DEFAULT_GUI_FONT);
// Set the font on each control
// SendMessage(editField, WM_SETFONT,(WPARAM)hObj, true);
// SendMessage(newButton, WM_SETFONT,(WPARAM)hObj, true);

   if(SUCCEEDED(retc))
      if(!PostMessage(hCtrlWnd, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True, 0)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

return(retc);
}


// ----------------------
HRESULT KpCreateStaticRaw(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, int iWdt, int iHgt, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
HRESULT retc=S_OK;
HWND static_field=NULL;
KpWnd *wnd_ptr=NULL;
WNDCLASSEX wcx;
// HDC hdc=NULL;
HFONT hfont=NULL;
DWORD ex_style;
DWORD style;
// EXTLOGPEN log_pen;
HBRUSH brush;
unsigned char class_name[KP_MAX_FNAME_LEN+1];
int line_count = 1;
int ii;

// if(hInst==NULL)
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

// if((phStaticControl==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);
// if(SUCCEEDED(retc)) *phStaticControl=NULL;

   if(((iKpCtrlStyle<0) || (iKpCtrlStyle >= KPW_NUM_OF_CONTROL_STYLES_0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc))
   {
      line_count = 1;
      if(lpszText)
      {
         ii = KPW_CALC_STATIC_WDT_FACTOR(lpszText, iKpCtrlStyle);
         if(ii > 0) line_count = iHgt / ii; // if(ii > 0) line_count = iWdt / ii; // !!!!?????
         if(ii == 0) ii = 1; // if(line_count == 0) line_count = 1; // !!!!????
      }
   }

// --------------------------
   brush = NULL;

#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
      if(!pen)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }

   cur_pen = pen;
   if(SUCCEEDED(retc))
      if(aPenScheme)
         if(aPenScheme[KpShadowNorm]) cur_pen = aPenScheme[KpShadowNorm];

   if(SUCCEEDED(retc))
   {
      if(cur_pen)
      {
         if(GetObject(cur_pen, sizeof(log_pen), &log_pen))
            brush = CreateSolidBrush(log_pen.elpColor);
         else
         {
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];
         }
      }
      else
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
         brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];
      }
   }

   if(pen) if(!DeleteObject(pen))
      /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen = NULL;

#else // #if FALSE

   brush = CreateSolidBrush(iaColorScheme?iaColorScheme[KpShadowNorm]:GetSysColor(iaColorMap[KpShadowNorm]));

#endif // #else // #if FALSE

// --------------------------
   sprintf((char *)class_name, "KPSTATIC_%x", iaColorScheme); // aPenScheme);

   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hInst;
      wcx.lpszClassName = (const char *)class_name,
      wcx.lpfnWndProc   = (WNDPROC)KpStaticDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hInst */, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
      wcx.hIconSm       = LoadIcon(NULL /* hInst */, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = brush;

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL, False);
      }
   }

// if(brush) if(!DeleteObject(brush))
//    /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   brush = NULL;

// --------------------------------
   if(SUCCEEDED(retc))
   {
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "WS_POPUP:%x dwStyle:%x dwStyle&WS_POPUP:%x (dwStyle&WS_POPUP)?0:WS_CHILD:%x", WS_POPUP, dwStyle, dwStyle&WS_POPUP, ((dwStyle&WS_POPUP)?0:WS_CHILD));
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
KP_TRACE(str_buf);
#endif

      ex_style=dwExStyle; /* | WS_EX_TRANSPARENT */
      style=dwStyle|((dwStyle&WS_POPUP)?0:WS_CHILD)|
            ES_READONLY|DS_SETFONT|KPW_STATIC_ALIGN(iKpCtrlStyle); // |WS_VISIBLE|WS_BORDER|SS_GRAYRECT|WS_DISABLED|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT

      static_field = CreateWindowEx(ex_style,
                  (const char *)class_name, // "KPSTATIC", // "EDIT", // "STATIC", //
// #ifdef TEST_WATCOM
//                (LPCTSTR)"",
// #else
                  (LPCTSTR)lpszText,
// #endif
                  style,
                  iPosX, iPosY, iWdt, iHgt, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!static_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// if(SUCCEEDED(retc)) retc=SetCtrlFont(static_field, iKpCtrlStyle);
   if(SUCCEEDED(retc)) retc=CrFont(&hfont, iKpCtrlStyle);

   if(SUCCEEDED(retc))
   {
      KP_NEWO(wnd_ptr, KpWnd(static_field, TYP_Static, lpszText, hParent, hInst, hfont, wcx.hIcon, iKpCtrlStyle, iWdt, iaCtrlFntHghts[iWindowsVersionCut][iKpCtrlStyle]*line_count, iWdt*(((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?9:10)/iaCtrlTextFactors[iKpCtrlStyle], line_count, ex_style, style, NULL));
      if(FAILED(retc)) KP_DELETE(wnd_ptr);
   }
   if(SUCCEEDED(retc))
   {
      wnd_ptr->m_iWndX = iPosX;
      wnd_ptr->m_iWndY = iPosY;
      retc = WndPreg(wnd_ptr, TYP_Static, hInst, NULL, False);
   }

// if(SUCCEEDED(retc)) wnd_ptr->m_hPenScheme=aPenScheme;
   if(SUCCEEDED(retc)) wnd_ptr->m_iaColorScheme = iaColorScheme;

#if FALSE
   if(SUCCEEDED(retc))
   {
      SetClassLong(static_field, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0xFF, 0, 0)));
      if(!InvalidateRect(static_field, 0, TRUE))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
      }
   }
#endif

#if FALSE
   if(SUCCEEDED(retc))
   {
//    hdc=GetWindowDC(static_field);
      hdc=GetDC(static_field);
      if(!hdc)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }
#endif

#if FALSE
   if(SUCCEEDED(retc))
      if(SetBkColor(hdc, 0x0000ff /* 0x00bbggrr  */)==CLR_INVALID)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc))
      if(SetTextColor(hdc, 0x00ff00)==CLR_INVALID)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc))
      if(!InvalidateRect(static_field, 0, TRUE))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
      }
#endif

#if FALSE
   if(SUCCEEDED(retc))
      if(!TextOut(hdc, 0, 0, (LPCTSTR)lpszText, strlen(lpszText)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif

   if((phStaticControl!=NULL) && SUCCEEDED(retc)) *phStaticControl=static_field;

   if(SUCCEEDED(retc)) ShowWindow(static_field, SW_SHOWNA);

return(retc);
}


HRESULT KpCreateStatic(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, int iWdt, int iLineCount, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
// int ii=KPW_CALC_STATIC_WDT_FACTOR(lpszText, iKpCtrlStyle)/iLineCount;

return(KpCreateStaticRaw(hInst, hParent, phStaticControl, lpszText, iPosX, iPosY, iWdt,
         (
            (iLineCount > 0)?
            iaCtrlHeights[iWindowsVersionCut][iKpCtrlStyle]:
            0
         ) +
         (
            (iLineCount > 1)?
            iaCtrlRowHeights[iWindowsVersionCut][iKpCtrlStyle] * (iLineCount - 1):
            0
         ) - 1,
         iKpCtrlStyle, dwExStyle, dwStyle|((iLineCount>1)?ES_MULTILINE:0), iaColorScheme)); // aPenScheme));
}


HRESULT KpCreateStatic(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, int iLineCount, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
return(KpCreateStatic(hInst, hParent, phStaticControl, lpszText, iPosX, iPosY, KPW_CALC_STATIC_WDT_FACTOR(lpszText, iKpCtrlStyle)/iLineCount, iLineCount, iKpCtrlStyle, dwExStyle, dwStyle, iaColorScheme)); // aPenScheme));
}


// -----------------------------------------
BOOL CALLBACK KpStaticDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
BOOL retw = FALSE;
int retp;
bool endfl = FALSE;
HDC hdc = NULL;
PAINTSTRUCT ps;
RECT rect;
KpWnd *cur_wnd = NULL;
unsigned char *str_buf = null;
const unsigned char *str_ptr = null;
unsigned char *pnts = null;
unsigned char *pntc = null;
int cur_x;
int cur_y;
// UINT text_align;
int text_width;
// HWND prew_mouse_over=NULL;
// EXTLOGPEN log_pen;
// HPEN pen = NULL;

   retp=LOWORD(wParam);

   switch(uMsg)
   {
   case WM_CREATE:
   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

#if FALSE // #ifdef Debug
{
char str_buf_1[100];
KP_TRACE("WM_PAINT");
if(cur_wnd)
{
sprintf(str_buf_1, "%x %x %x", hwndDlg, cur_wnd, cur_wnd->m_iaColorScheme); // cur_wnd->m_hPenScheme);
KP_TRACE(str_buf_1);
}
}
#endif

      if(cur_wnd!=NULL)
      {
         if(GetUpdateRect(hwndDlg, &rect, FALSE))
         {
//          hdc=GetDC(hwndDlg);
            hdc=BeginPaint(hwndDlg, &ps);
            if(hdc==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

#if FALSE
            pen = NULL;
            if(SUCCEEDED(retc))
            {
               if(cur_wnd->m_hPenScheme == NULL)
               {
                  pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowDark]));
                  if(pen == NULL)
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
               }
               else if(cur_wnd->m_hPenScheme[KpShadowDark] == NULL)
               {
                  pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowDark]));
                  if(pen == NULL)
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
               }
            }

            if(SUCCEEDED(retc))
            {
               if(GetObject(pen?pen:cur_wnd->m_hPenScheme[KpShadowDark], sizeof(log_pen), &log_pen))
               {
                  if(SetTextColor(hdc, log_pen.elpColor)==CLR_INVALID)
//                if(SetTextColor(hdc, 0)==CLR_INVALID)
//                if(SetBkColor(hdc, 0x0000ff /* 0x00bbggrr  */)==CLR_INVALID)
                  {
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
               }
               else
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
            }

            if(pen) if(!DeleteObject(pen))
               /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            pen = NULL;

#else // #if FALSE

            if(SUCCEEDED(retc))
               if(SetTextColor(hdc, cur_wnd->m_iaColorScheme?cur_wnd->m_iaColorScheme[KpShadowDark]:GetSysColor(iaColorMap[KpShadowDark]))==CLR_INVALID)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);

#endif // #else // #if FALSE

            if(SUCCEEDED(retc))
               if(SetBkMode(hdc, TRANSPARENT)==0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

            if(SUCCEEDED(retc))
               if(cur_wnd->m_hFont != NULL)
                  if(SelectObject(hdc, cur_wnd->m_hFont) == NULL)
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

            KP_NEWA(str_buf, unsigned char, strlen(cur_wnd->m_lpszWndText) + 1);

            if(SUCCEEDED(retc))
            {
               strcpy(str_buf, cur_wnd->m_lpszWndText);
               pntc = str_buf;
               pnts = str_buf;
               cur_y = 1;
               while((*pntc) && SUCCEEDED(retc))
               {
                  while((*pntc) && (strchr(lpszEols, *pntc) == NULL)) pntc++;
                  if(*pntc)
                  {
                     *(pntc++) = Nul;
                     while((strchr(lpszEols, *pntc)!=NULL) && (*pntc)) pntc++;
                  }

                  cur_x = 1;

//                text_align = GetTextAlign(hdc);
//                if(text_align == GDI_ERROR)
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

//                if((text_align & TA_CENTER) && SUCCEEDED(retc))
                  if((cur_wnd->m_dwStyle & SS_CENTER) && SUCCEEDED(retc))
                  {
                     retc = GetStrWidth(pnts, &text_width, hdc);
                     if(SUCCEEDED(retc)) cur_x = (cur_wnd->m_iWdtDots - text_width) / 2;
                  }

                  if(SUCCEEDED(retc))
                     if(!TextOut(hdc, cur_x, cur_y, (const char *)pnts, strlen(pnts)))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

                  if(SUCCEEDED(retc))
                  {
                     pnts = pntc;
                     cur_y += iaCtrlFntHghts[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle];
                  }

               } // while((*pntc) && SUCCEEDED(retc))

            } // if(SUCCEEDED(retc))

            KP_DELETEA(str_buf);

            EndPaint(hwndDlg, &ps);

         } // if(GetUpdateRect(hwndDlg, &rect, FALSE))

      } // if(cur_wnd!=NULL)

      retw=TRUE;
      break;

   case WM_GETTEXT:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      retw=0;
      str_buf=(unsigned char *)lParam;
      if((str_buf==NULL) || (wParam<1))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);
      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL, False);
      if(SUCCEEDED(retc))
      {
         strncpy(str_buf, cur_wnd->m_lpszWndText, wParam-1);
         str_buf[wParam-1]=Nul;
         retw=strlen(str_buf);
      }
      break;

   case WM_SETTEXT:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL, False);
      if(SUCCEEDED(retc))
      {
         str_ptr = (const unsigned char *)lParam;
         if(str_ptr == NULL) str_ptr = (const unsigned char *)"";

         strncpy(cur_wnd->m_lpszWndText, str_ptr, KP_MAX_FILE_LIN_LEN);
         cur_wnd->m_lpszWndText[KP_MAX_FILE_LIN_LEN] = Nul;
      }
      if(SUCCEEDED(retc))
         if(!InvalidateRect(hwndDlg, NULL, True))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
      if(SUCCEEDED(retc)) SendMessage(hwndDlg, WM_PAINT, 0, 0L);

      retw=SUCCEEDED(retc);
      break;

   case WM_MOUSEMOVE:
#if FALSE
// ----------------- mygtuku gesinimas
      prew_mouse_over = hMouseOverWnd;
      if(prew_mouse_over) // !=hwndDlg)
      {
         hMouseOverWnd = NULL; // hwndDlg;
//       if(prew_mouse_over)
            if(!InvalidateRect(prew_mouse_over, 0, TRUE))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
            }
      }
#endif
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      if(cur_wnd != NULL)
         PostMessage(cur_wnd->m_hParent, uMsg, wParam,
            ((GET_X_LPARAM(lParam) + cur_wnd->m_iWndX) & 0xFFFF) | (((GET_Y_LPARAM(lParam) + cur_wnd->m_iWndY) << 16) & 0xFFFF0000));
      break;

   case WM_QUIT:
   case WM_CLOSE:
      endfl=TRUE;
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      if(cur_wnd != NULL)
      {
// PutLogMessage_("HWND KpStaticDialogProc() WM_CLOSE m_hWndHandle %x", cur_wnd->m_hWndHandle);
         cur_wnd->m_hWndHandle = NULL;
      }
      break;

   case WM_COMMAND:
      if(retp==IDCANCEL) endfl=TRUE;
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl)
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if((endfl || FAILED(retc)) && (cur_wnd!=NULL))
   {
// PutLogMessage_("KpStaticDialogProc(): DeleteWnd()");
      retc0 = DeleteWnd(cur_wnd);
      if(SUCCEEDED(retc)) retc=retc0;

//    KP_DELETE(cur_wnd);
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// ----------------------
HRESULT KpCreateEdit(HINSTANCE /* hInst */, HWND hParent, HWND *phEditControl,
   const unsigned char *lpszText, int iWdt, int iPosX, int iPosY,
   KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, int iLineCount)
{
HRESULT retc=S_OK;
HWND edit_field=NULL;
// WNDCLASSEX wcx;
// HDC hdc;

// if(hInst==NULL)
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// if((phEditControl==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
// if(SUCCEEDED(retc)) *phEditControl=NULL;

   if(((iKpCtrlStyle<0) || (iKpCtrlStyle >= KPW_NUM_OF_CONTROL_STYLES_0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((iLineCount<1) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// ------------------- wrapinam EDIT klas¿ - keisim fon? - ?itokiu b?du neveikia
#if FALSE
   KP_ASSERT(GetClassInfoEx(hKpInstance, "EDIT", &wcx), KP_E_SYSTEM_ERROR, GetLastError(), True);

   if(SUCCEEDED(retc))
   {
      wcx.hInstance = hKpInstance;
      wcx.lpszClassName = "KpEdit";
      wcx.cbSize = sizeof(WNDCLASSEX);
      if(dwStyle & ES_READONLY)
      {
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;
         wcx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
      }

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS) KP_WARNING(KP_E_SYSTEM_ERROR, ll);
      }
   }
#endif

// ------------------ kuriam lang?
   if(SUCCEEDED(retc))
   {
      edit_field=CreateWindowEx(dwExStyle|WS_EX_TRANSPARENT/*|WS_EX_CLIENTEDGE*/,
                  "EDIT", // "KpEdit", //
                  (LPCTSTR)lpszText,
                  dwStyle|((iLineCount>1)?ES_MULTILINE:0)|
                  ES_AUTOHSCROLL|WS_VISIBLE|WS_CHILD|DS_SETFONT, // |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  iPosX, iPosY, iWdt,
                  ((dwExStyle&WS_EX_CLIENTEDGE)?2*KPW_CTRL_BORDER_WDT:0)+iLineCount*iaCtrlRowHeights[iWindowsVersionCut][iKpCtrlStyle]+3,
                  hParent, 0, GetModuleHandle(NULL), 0);
      if(!edit_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) retc=SetCtrlFont(edit_field, iKpCtrlStyle);

// ----------------- kei?iam fon? – ir taip nei?eina
#if FALSE
   if((dwStyle & ES_READONLY) && SUCCEEDED(retc))
   {
      hdc = GetDC(edit_field);
      KP_ASSERT(hdc, KP_E_SYSTEM_ERROR, GetLastError(), False);

      if(hdc)
      {
//       KP_ASSERT(SetBkColor(hdc, 0) != CLR_INVALID, KP_E_SYSTEM_ERROR, GetLastError(), False);
         KP_ASSERT(SetTextColor(hdc, 0xFFFFFF) != CLR_INVALID, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
   }
#endif

// ------------------------
   if((phEditControl!=NULL) && SUCCEEDED(retc)) *phEditControl=edit_field;

return(retc);
}


// ----------------------
HRESULT KpCreateEdit(HINSTANCE hInst, HWND hParent, HWND *phEditControl,
   const unsigned char *lpszText, int iPosX, int iPosY,
   KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, int iLineCount)
{
HRESULT retc=S_OK;

   if(lpszText==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      retc=KpCreateEdit(hInst, hParent, phEditControl, lpszText, KPW_CALC_STATIC_WDT_FACTOR(lpszText, iKpCtrlStyle)/iLineCount, iPosX, iPosY, iKpCtrlStyle, dwExStyle, dwStyle, iLineCount);

return(retc);
}


// ==========================
UINT KpCfRtfClFormat = 0; // KP_CF_RTF_NAME
UINT KpCfHtmlClFormat = 0; // KP_CF_HTML_NAME


// ----------------------
HRESULT KpSetCtrlText(HWND hControl, const unsigned char *lpszText)
{
HRESULT retc=S_OK;
int retv;

   if(hControl==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      retv=SendMessage(hControl, WM_SETTEXT, 0, (LPARAM)lpszText);
      if((retv==CB_ERR) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if((/* (retv==FALSE) || */ (retv==LB_ERRSPACE) || (retv==CB_ERRSPACE)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#ifdef Debug
      if((!retv) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
   }

return(retc);
}


// ----------------------
HRESULT KpGetCtrlText(HWND hControl, unsigned char *lpszTextBuf, int iBufSize)
{
HRESULT retc=S_OK;

   if((hControl==NULL) || (lpszTextBuf==NULL) || (iBufSize<1))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      lpszTextBuf[0]=Nul;
      SendMessage(hControl, WM_GETTEXT, iBufSize, (LPARAM)lpszTextBuf);
      lpszTextBuf[iBufSize-1]=Nul;
   }

return(retc);
}


// ----------------------
HRESULT KpGetRtfCtrlText(HWND hControl, unsigned char *lpszTextBuf, int iBufSize)
{
HRESULT retc=S_OK;

   if((hControl==NULL) || (lpszTextBuf==NULL) || (iBufSize<1))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      lpszTextBuf[0]=Nul;
      SendMessage(hControl, KP_WM_GETTEXT, iBufSize, (LPARAM)lpszTextBuf);
      lpszTextBuf[iBufSize-1]=Nul;
   }

return(retc);
}


// ----------------------
HRESULT KpSetCtrlRtfText
(
HWND hControl, const unsigned char *lpszText,
bool
#ifdef KpRichEditClipboard // #if FALSE // #ifndef KpRichEdit20
 bEnabled
#endif
)
{
HRESULT retc=S_OK;
#ifdef KpRichEditClipboard // #if FALSE // #ifndef KpRichEdit20
UINT clip_format;
#endif
// REPASTESPECIAL rp;
#ifdef Debug
// unsigned char str_buf[100];
#endif

   if(hControl==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((lpszText!=NULL) && SUCCEEDED(retc))
   {

#ifdef KpRichEditClipboard // #if FALSE // #ifndef KpRichEdit20 // #if TRUE //

#ifdef Debug
#error KpRichEditClipboard defined
#endif

#if TRUE // FALSE //
      clip_format=RegisterClipboardFormat(KP_CF_RTF_NAME); // !!!??? gal kelt i kokia nors inicializavimo procedura?
      if(clip_format==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         KpCfRtfClFormat = clip_format;
         retc=KpSetClipboardData(hControl, clip_format, lpszText, strlen(lpszText)+1);
      }

#else
      if(SUCCEEDED(retc))
         retc=KpSetClipboardData(hControl, CF_TEXT, lpszText, strlen(lpszText)+1);
#endif

#ifdef Debug
if(SUCCEEDED(retc))
retc=KpSetClipboardData(hControl, CF_TEXT, lpszText, strlen(lpszText)+1);
#endif


      if(SUCCEEDED(retc)) retc=KpSetCtrlText(hControl, (const unsigned char *)"");

      if(SUCCEEDED(retc))
      {
         if(!SendMessage(hControl, EM_CANPASTE, (WPARAM)clip_format, (LPARAM)NULL))
         {
// !!!??? kazkodel duoda klaida, kai greitai spaudi klaviatura
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
#endif
         }
         else
         {
            if(SUCCEEDED(retc))
            {
               EnableWindow(hControl, True);

//             rp.dwAspect=DVASPECT_CONTENT;
//             rp.dwParam=(DWORD_PTR)rtf_buf;
               SendMessage(hControl, EM_PASTESPECIAL, (WPARAM)clip_format, (LPARAM)NULL /* &rp */);

               EnableWindow(hControl, bEnabled);

#ifdef Debug
// sprintf((char *)str_buf, "clip_format: %d", clip_format);
// KP_TRACE(str_buf);
#endif

//             retc=KpSleep(500, hControl);

            }

            if(SUCCEEDED(retc))
            {
#ifndef Debug
//             retc=KpSetClipboardData(hControl, clip_format, (const unsigned char *)"", 0);
               retc=KpClearClipboard(hControl);
#endif
            }
         }
      }

#else // #ifdef KpRichEditClipboard //

#if FALSE // #ifdef Debug
if(SUCCEEDED(retc))
retc=KpSetClipboardData(hControl, CF_TEXT, lpszText, strlen(lpszText)+1);
#endif

      if(SUCCEEDED(retc)) retc=KpSetCtrlText(hControl, lpszText);
#endif

   } // if((lpszText!=NULL) && SUCCEEDED(retc))

return(retc);
}


// ----------------------
unsigned char rtf_head[] =
{
#if FALSE
// Verdana MSWord 2000
"{\\rtf1\\ansi\\ansicpg1252\\uc1 \\deff0\\deflang1033\\deflangfe1033{\\fonttbl{\\f0\\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f39\\fswiss\\fcharset0\\fprq2{\\*\\panose 020b0604030504040204}Verdana;}\n"
"{\\f221\\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\f222\\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\f224\\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f225\\froman\\fcharset162\\fprq2 Times New Roman Tur;}\n"
"{\\f226\\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\f227\\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\f228\\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\f533\\fswiss\\fcharset238\\fprq2 Verdana CE;}\n"
"{\\f534\\fswiss\\fcharset204\\fprq2 Verdana Cyr;}{\\f536\\fswiss\\fcharset161\\fprq2 Verdana Greek;}{\\f537\\fswiss\\fcharset162\\fprq2 Verdana Tur;}{\\f540\\fswiss\\fcharset186\\fprq2 Verdana Baltic;}}{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;\n"
"\\red0\\green255\\blue255;\\red0\\green255\\blue0;\\red255\\green0\\blue255;\\red255\\green0\\blue0;\\red255\\green255\\blue0;\\red255\\green255\\blue255;\\red0\\green0\\blue128;\\red0\\green128\\blue128;\\red0\\green128\\blue0;\\red128\\green0\\blue128;\\red128\\green0\\blue0;\n"
"\\red128\\green128\\blue0;\\red128\\green128\\blue128;\\red192\\green192\\blue192;}{\\stylesheet{\\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\fs24\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 \\snext0 Normal;}{\\*\\cs10 \\additive \n"
"Default Paragraph Font;}}{\\info{\\upr{\\title TITLE}{\\*\\ud\\uc0{\\title AAA{\\uc1\\u280 E\\u280 E\\u280 ERRR}}}}{\\author a}{\\operator a}{\\creatim\\yr2004\\mo6\\dy30\\hr19\\min29}{\\revtim\\yr2004\\mo6\\dy30\\hr19\\min29}{\\version1}{\\edmins0}{\\nofpages1}{\\nofwords0}\n"
"{\\nofchars0}{\\*\\company a}{\\nofcharsws0}{\\vern8269}}\\paperw11906\\paperh16838 \\widowctrl\\ftnbj\\aenddoc\\noxlattoyen\\expshrtn\\noultrlspc\\dntblnsbdb\\nospaceforul\\formshade\\horzdoc\\dgmargin\\dghspace180\\dgvspace180\\dghorigin1800\\dgvorigin1440\\dghshow1\\dgvshow1\n"
"\\jexpand\\viewkind1\\viewscale100\\pgbrdrhead\\pgbrdrfoot\\splytwnine\\ftnlytwnine\\htmautsp\\nolnhtadjtbl\\useltbaln\\alntblind\\lytcalctblwd\\lyttblrtgr\\lnbrkrule \\fet0\\sectd \\linex0\\headery708\\footery708\\colsx708\\endnhere\\sectlinegrid360\\sectdefaultcl \n"
"{\\*\\pnseclvl1\\pnucrm\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl2\\pnucltr\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl4\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxta )}}{\\*\\pnseclvl5\n"
"\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl6\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl7\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang\n"
"{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}\\pard\\plain \\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\fs24\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 {\\f540\\lang1063\\langfe1033\\langnp1063"
#endif

#if FALSE
// HelveticaLT MSWord 2000
"{\\rtf1\\ansi\\ansicpg1252\\uc1 \\deff0\\deflang1033\\deflangfe1033{\\fonttbl{\\f0\\froman\\fcharset0\\fprq2{\\*\\panose 02020603050405020304}Times New Roman;}{\\f52\\fswiss\\fcharset0\\fprq2{\\*\\panose 020b0604020202020204}HelveticaLT;}\n"
"{\\f219\\froman\\fcharset238\\fprq2 Times New Roman CE;}{\\f220\\froman\\fcharset204\\fprq2 Times New Roman Cyr;}{\\f222\\froman\\fcharset161\\fprq2 Times New Roman Greek;}{\\f223\\froman\\fcharset162\\fprq2 Times New Roman Tur;}\n"
"{\\f224\\froman\\fcharset177\\fprq2 Times New Roman (Hebrew);}{\\f225\\froman\\fcharset178\\fprq2 Times New Roman (Arabic);}{\\f226\\froman\\fcharset186\\fprq2 Times New Roman Baltic;}{\\f635\\fswiss\\fcharset238\\fprq2 HelveticaLT CE;}\n"
"{\\f636\\fswiss\\fcharset204\\fprq2 HelveticaLT Cyr;}{\\f638\\fswiss\\fcharset161\\fprq2 HelveticaLT Greek;}{\\f639\\fswiss\\fcharset162\\fprq2 HelveticaLT Tur;}{\\f642\\fswiss\\fcharset186\\fprq2 HelveticaLT Baltic;}}{\\colortbl;\\red0\\green0\\blue0;\\red0\\green0\\blue255;\n"
"\\red0\\green255\\blue255;\\red0\\green255\\blue0;\\red255\\green0\\blue255;\\red255\\green0\\blue0;\\red255\\green255\\blue0;\\red255\\green255\\blue255;\\red0\\green0\\blue128;\\red0\\green128\\blue128;\\red0\\green128\\blue0;\\red128\\green0\\blue128;\\red128\\green0\\blue0;\n"
"\\red128\\green128\\blue0;\\red128\\green128\\blue128;\\red192\\green192\\blue192;}{\\stylesheet{\\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\fs24\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 \\snext0 Normal;}{\\*\\cs10 \\additive \n"
"Default Paragraph Font;}}{\\info{\\upr{\\title AAAEEERRR}{\\*\\ud\\uc0{\\title AAA{\\uc1\\u280 E\\u280 E\\u280 ERRR}}}}{\\author a}{\\operator a}{\\creatim\\yr2004\\mo6\\dy30\\hr19\\min29}{\\revtim\\yr2004\\mo7\\dy1\\hr9\\min52}{\\version2}{\\edmins2}{\\nofpages1}{\\nofwords0}\n"
"{\\nofchars0}{\\*\\company a}{\\nofcharsws0}{\\vern8269}}\\paperw11906\\paperh16838 \\widowctrl\\ftnbj\\aenddoc\\noxlattoyen\\expshrtn\\noultrlspc\\dntblnsbdb\\nospaceforul\\hyphcaps0\\formshade\\horzdoc\\dgmargin\\dghspace180\\dgvspace180\\dghorigin1800\\dgvorigin1440\\dghshow1\n"
"\\dgvshow1\\jexpand\\viewkind1\\viewscale100\\pgbrdrhead\\pgbrdrfoot\\splytwnine\\ftnlytwnine\\htmautsp\\nolnhtadjtbl\\useltbaln\\alntblind\\lytcalctblwd\\lyttblrtgr\\lnbrkrule \\fet0\\sectd \\linex0\\headery708\\footery708\\colsx708\\endnhere\\sectlinegrid360\\sectdefaultcl \n"
"{\\*\\pnseclvl1\\pnucrm\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl2\\pnucltr\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}{\\*\\pnseclvl4\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxta )}}{\\*\\pnseclvl5\n"
"\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl6\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl7\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang\n"
"{\\pntxtb (}{\\pntxta )}}{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}\\pard\\plain \\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0 \\fs24\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 {\n"
"\\f642\\lang1063\\langfe1033\\langnp1063"
#endif

#if FALSE
// Verdana WordPad 9pt
"{\\rtf1\\ansi\\ansicpg1251\\deff0\\deflang1063{\\fonttbl{\\f0\\fswiss\\fprq2\\fcharset0 Verdana;}{\\f1\\fswiss\\fprq2\\fcharset186 Verdana;}{\\f2\\fnil\\fcharset204{\\*\\fname Times New Roman;}Times New Roman Cyr;}}\n"
"\\viewkind4\\uc1\\pard\\lang1063\\f1"
#endif

// HelveticaLT WordPad 11pt
"{\\rtf1\\ansi\\ansicpg1251\\deff0\\deflang1063{\\fonttbl{\\f0\\fswiss\\fprq2\\fcharset186 HelveticaLT;}{\\f1\\fnil\\fcharset204{\\*\\fname Times New Roman;}Times New Roman Cyr;}}\n"
"\\viewkind4\\uc1\\pard\\f0" // "\\fs22{"
};

unsigned char rtf_tail[] =
{
#if FALSE
// Verdana MSWord 2000
"}{\\f39\\fs20\\lang1063\\langfe1033\\langnp1063 \n"
"\\par }}\n"
#endif

#if FALSE
// HelveticaLT MSWord 2000
"\\par }}\n"
#endif

#if FALSE
// Verdana WordPad
"\\f2\\par\n"
"}\n"
#endif

// HelveticaLT WordPad
"}\\f1\\par\n"
"}\n"
};

HRESULT KpSetRichCtrlText(HWND hControl, const unsigned char *lpszText, bool bEnabled)
{
HRESULT retc=S_OK;
unsigned char *str_buf = null;
const unsigned char *in_str;
int out_str_len;
unsigned char *pntd;
int weight;

   in_str=lpszText;
   if(in_str==NULL) in_str=(const unsigned char *)"";

   out_str_len = strlen(in_str)*6;
   KP_NEWA(str_buf, unsigned char, strlen(rtf_head) + out_str_len + strlen(rtf_tail) + 10 + 1);

   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, rtf_head);

      pntd=str_buf+strlen(str_buf);
      *(pntd++)=RC_KeywordStart;
      strcpy(pntd, plpszaRtfTagTable[RT_TG_fs]);

      switch(iWindowsVersion)
      {
      case WinUnkn:
      case Win95c:
      case Win95:
      case Win95OSR2:
      case Win98c:
      case Win98:
      case Win98SE:
      case WinCE:
      case WinMe:
         weight=22;
         break;
      case WinNT40c:
      case WinNT40:
      case WinNT40s:
         weight=16;
         break;
      case Win2000c:
      case Win2000:
      case Win2003s:
         weight=20;
         break;
      case WinXP:
      default:
         weight=22;
         break;
      }
      pntd=str_buf+strlen(str_buf);
      sprintf((char *)pntd, "%d{", weight);

      pntd=str_buf+strlen(str_buf);
      retc=CvtToRtfCtlStr(pntd, in_str, out_str_len);
   }
// KP_TRACE(str_buf+strlen(rtf_head));
   if(SUCCEEDED(retc))
   {
      strcat(str_buf, rtf_tail);

#if FALSE // #ifdef Debug
KP_TRACE(str_buf);
FILE *out_file;
out_file=fopen("kpn1.rtf", "w");
fputs((const char *)str_buf, out_file);
fclose(out_file);
#endif

      retc=KpSetCtrlRtfText(hControl, str_buf, bEnabled);
   }

   KP_DELETEA(str_buf);

return(retc);
}


//================================================
HRESULT KpGetWindowUniText(HWND hCtrl, UniChar *szaUniBuf /* unsigned char *lpszTxtBuf */, int iBufLen)
{
HRESULT retc = S_OK;

   if(((szaUniBuf == NULL) || (hCtrl == 0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

#if TRUE // #if FALSE //
GETTEXTEX gettex;

   if(SUCCEEDED(retc))
   {
      gettex.cb = iBufLen;
      gettex.flags = GT_DEFAULT;
      gettex.codepage = CP_UNICODE;
      gettex.lpDefaultChar = NULL;

#  if ((Compiler==Watcom) && (__WATCOMC__ < 1202)) || ((Compiler==Mingw) && (__GNUC__ <= 3)) // (__GNUC__ < 3)) //
      gettex.lpUsedDefaultChar = NULL;
#  else
      gettex.lpUsedDefChar = NULL;
#  endif
      if(!SendMessage(hCtrl,
         KP_EM_GETTEXTEX, // EM_GETTEXTEX, // WM_GETTEXT,
         (WPARAM)&gettex, // (WPARAM)iBufLen,
         (LPARAM)szaUniBuf)) // (LPARAM)lpszTxtBuf))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#else
   if(SUCCEEDED(retc))
      if(!GetWindowTextW(hCtrl, szaUniBuf, iBufLen))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

   if(SUCCEEDED(retc)) szaUniBuf[iBufLen] = 0;

return(retc);
}


// --------------------------------
HRESULT KpSetWindowUniText(HWND hCtrl, const UniChar *szaUniStr /* const unsigned char *lpszWndTxt */, const unsigned char *lpszFontName)
{
HRESULT retc = S_OK;
static unsigned char *rtf_buf[KP_MAX_FILE_LIN_LEN+1];
// static UniChar *rtf_uni_buf[KP_MAX_FILE_LIN_LEN+1];

   if(((szaUniStr == NULL) || (hCtrl == 0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      retc = RtUnicodeToRtf((unsigned char *)rtf_buf, szaUniStr, KP_MAX_FILE_LIN_LEN, lpszFontName);
// if(SUCCEEDED(retc))
// {
//    retc = KptStrToUnicode((UniChar *)rtf_uni_buf, (const unsigned char *)rtf_buf, 1);
//    if(FAILED(retc))
//       retc = KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
// }

// if(SUCCEEDED(retc)) strcat(cont_buf, "\\u57344\\\'3f\\u260\\\'3f\\u1044\\\'3f\\u1041\\\'3f\\u9658\\\'3f\\u945\\\'3f}}");
// if(SUCCEEDED(retc)) wcscat(cont_buf, L"\\u57344\\\'3f\\u260\\\'3f\\u1044\\\'3f\\u1041\\\'3f\\u9658\\\'3f\\u945\\\'3f}}");

// vis?i [n??nieko] nenusiman?ti api? k? nórs

#if TRUE // #if FALSE //
#  if FALSE // #if TRUE //
   if(SUCCEEDED(retc))
   {
SETTEXTEX settex;
      settex.flags=ST_DEFAULT;
      settex.codepage=CP_UNICODE;

      if(!SendMessage(hCtrl,
         EM_SETTEXTEX,
         (WPARAM)&settex,
         (LPARAM)szaUniStr)) // (LPARAM)rtf_uni_buf)) //
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#  else
   if(SUCCEEDED(retc))
      if(!SendMessage(hCtrl, WM_SETTEXT, 0, (LPARAM)rtf_buf))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#  endif
#else
   if(SUCCEEDED(retc))
      if(!SetWindowTextW(hCtrl, szaUniStr))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

return(retc);
}


// ===========================================================================
// ----------------------
HRESULT KpCreateListBox
(
   HINSTANCE
#ifdef KP_LISTBOX
      hInst
#endif
   ,
   HWND hParent, HWND *phListControl, const unsigned char *lpszText,
   int iWdt, int iHgt, int iPosX, int iPosY,
   KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, KpTreeEntry *pEntries,
   int iInitSel, KpWndType iWndType, int iNumOfRows
)
{
HRESULT retc=S_OK;
HWND list_field=NULL;
LRESULT retv;
#ifdef KP_LISTBOX
WNDCLASSEX wcx;
KpWnd *cur_wnd=NULL;
DWORD ex_style=0L;
DWORD style=0L;
#else
KpTreeEntry *cur_entry;
KpTreeEntry *next_entry;
const unsigned char *cur_str;
#endif
HBRUSH brush = NULL;

   if(
      (
         (iKpCtrlStyle<0) || (iKpCtrlStyle >= KPW_NUM_OF_CONTROL_STYLES_0) ||
         ((iWndType!=TYP_ListBox) && (iWndType!=TYP_ListBoxTree) && (iWndType!=TYP_ListBoxChk) && (iWndType!=TYP_ListBoxTreeInverted))
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);


#ifdef KP_LISTBOX
// ----------------------
   if(((iWndType == TYP_ListBoxTree) || (iWndType == TYP_ListBoxTreeInverted)) && SUCCEEDED(retc))
   {
      if((hbmpNodeBypass == 0) && SUCCEEDED(retc))
      {
// KP_TRACE_2("KpCreateListBox: %ld %ld", GetCurrentProcessId(), GetCurrentThreadId());
         hbmpNodeBypass = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_BYPASS_BMP));
         if(hbmpNodeBypass == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeBypassEmpty == 0) && SUCCEEDED(retc))
      {
         hbmpNodeBypassEmpty = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_BYPASS_EMPTY_BMP));
         if(hbmpNodeBypassEmpty == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeBottom == 0) && SUCCEEDED(retc))
      {
         hbmpNodeBottom = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_BOTTOM_BMP));
         if(hbmpNodeBottom == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeBottomLast == 0) && SUCCEEDED(retc))
      {
         hbmpNodeBottomLast = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_BOTTOM_LAST_BMP));
         if(hbmpNodeBottomLast == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeOpen == 0) && SUCCEEDED(retc))
      {
         hbmpNodeOpen = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_OPEN_BMP));
         if(hbmpNodeOpen == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeOpenLast == 0) && SUCCEEDED(retc))
      {
         hbmpNodeOpenLast = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_OPEN_LAST_BMP));
         if(hbmpNodeOpenLast == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeClosed == 0) && SUCCEEDED(retc))
      {
         hbmpNodeClosed = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_CLOSED_BMP));
         if(hbmpNodeClosed == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
      if((hbmpNodeClosedLast == 0) && SUCCEEDED(retc))
      {
         hbmpNodeClosedLast = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_NODE_CLOSED_LAST_BMP));
         if(hbmpNodeClosedLast == 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

// -----------------------------
   if((iWndType == TYP_ListBoxChk) && SUCCEEDED(retc))
   {
      if((hbmpChecked == 0) && SUCCEEDED(retc))
      {
         hbmpChecked = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_CHECKED_BMP));
         KP_ASSERT(hbmpChecked != 0, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }
      if((hbmpUnChecked == 0) && SUCCEEDED(retc))
      {
         hbmpUnChecked = LoadBitmap(hInst, MAKEINTRESOURCE(KP_IDI_UNCHECKED_BMP));
         KP_ASSERT(hbmpUnChecked != 0, KP_E_SYSTEM_ERROR, GetLastError(), True);
      }
   }

// -----------------------------
   brush = NULL;

#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#else

   brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));
#endif


// ------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hInst;
      wcx.lpszClassName = "KPLISTBOX",
      wcx.lpfnWndProc   = (WNDPROC)KpListBoxDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hIconSm       = LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
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

// ------------------------------------
   if(SUCCEEDED(retc))
   {
      ex_style=dwExStyle/*|WS_EX_CLIENTEDGE|ES_SUNKEN*/; /* | WS_EX_TRANSPARENT */
      style=dwStyle|(((iWndType==TYP_ListBoxTree)||(iWndType==TYP_ListBoxTreeInverted)||(iWndType==TYP_ListBoxChk))?LBS_OWNERDRAWFIXED:0)|WS_CHILD|WS_VISIBLE|DS_SETFONT; // |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT|WS_BORDER|WS_DISABLED

      list_field=CreateWindowEx(ex_style,
                  "KPLISTBOX",
                  (LPCTSTR)lpszText,
                  style,
                  iPosX, iPosY, iWdt, iHgt,
                  hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!list_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

int lbox_wdt = 0;
   if(SUCCEEDED(retc))
      lbox_wdt = iWdt * (((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?9:10)/iaCtrlTextFactors[iKpCtrlStyle];

   KP_NEWO(cur_wnd, KpWnd(list_field, iWndType, lpszText, hParent, hInst, NULL,
         LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION)), iKpCtrlStyle,
         iWdt, iHgt,
         lbox_wdt,
         iHgt/iaCtrlRowHeights[iWindowsVersionCut][iKpCtrlStyle],
         ex_style, style, NULL));

   if(SUCCEEDED(retc)) retc = WndPreg(cur_wnd, iWndType, hInst, NULL, False);

   if(SUCCEEDED(retc)) SendMessage(list_field, WM_KP_CREATE, 0, 0L);

   if(((iNumOfRows > 0) || (pEntries != NULL)) && SUCCEEDED(retc))
   {
// -------- inicializuojam viet? reik?m?ms
//    if((iWndType == TYP_ListBoxTree) || (iWndType == TYP_ListBoxTreeInverted) || (iWndType == TYP_ListBoxChk))
//       retc = cur_wnd->ResetListBoxContents(iNumOfRows, lbox_wdt, True, pEntries); // reik?mes si¸sim v?liau KP_LB_SETSTRINGLIST
//    else if(iWndType == TYP_ListBox)
         retc = cur_wnd->ResetListBoxContents(iNumOfRows, lbox_wdt, False, pEntries);
   }

#else // #ifdef KP_LISTBOX
// ------------------------
   if(SUCCEEDED(retc))
   {
      list_field=CreateWindowEx(
                  dwExStyle|WS_EX_TRANSPARENT/*|WS_EX_CLIENTEDGE|ES_SUNKEN*/,
                  "LISTBOX",
                  (LPCTSTR)lpszText,
                  (dwStyle|WS_CHILD|WS_VISIBLE|DS_SETFONT|LBS_HASSTRINGS|LBS_DISABLENOSCROLL|LBS_NOTIFY|WS_VSCROLL)&(~LBS_SORT), // |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  iPosX+((dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?1:0),
                  iPosY+((dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?1:0),
                  iWdt-((dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?2:0),
                  iHgt-((dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?2:0),
                  hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!list_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#endif // #ifdef KP_LISTBOX

// KP_TRACE_1("KpCreateListBox(): list_field:%lx", list_field);

#if FALSE
   if(SUCCEEDED(retc))
   {
      if(LB_ERR==SendMessage(list_field, LB_SETLOCALE, (WPARAM)MAKELCID(MAKELANGID(LANG_LITHUANIAN, SUBLANG_DEFAULT), SORT_DEFAULT), 0L))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#endif

#ifndef KP_LISTBOX
   if(SUCCEEDED(retc)) retc=SetCtrlFont(list_field, iKpCtrlStyle);
#endif

   if((phListControl!=NULL) && SUCCEEDED(retc)) *phListControl=list_field;

// ---------------------- set box entries
#ifdef KP_LISTBOX
   if(SUCCEEDED(retc))
   {
      retv = SendMessage(list_field, KP_LB_SETSTRINGLIST, 0, (LPARAM)pEntries);
      switch(retv)
      {
      case CB_ERR:
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
      case CB_ERRSPACE:
         retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
         break;
      }
   }
#else
   if(SUCCEEDED(retc)) cur_entry=cur_wnd->m_pEntries=pEntryes;
   while(cur_entry && SUCCEEDED(retc))
   {
      cur_str=(const unsigned char *)cur_entry->GetValue();
      if(cur_str)
      {
         retv=SendMessage(list_field, LB_ADDSTRING, 0, (LPARAM)cur_str);
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

//    if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild(&next_entry);
      if(SUCCEEDED(retc)) next_entry = cur_entry->m_pFirstChild;

      if(SUCCEEDED(retc)) cur_entry = next_entry;
   }
#endif

   if(SUCCEEDED(retc)) retc=SetListBoxSel(list_field, iInitSel);

return(retc);
}


// -----------------------------------------
HRESULT KpWnd::SetCurScrolPos(void)
{
HRESULT retc=S_OK;
SCROLLINFO scroll_info={0};
int scroll_pos;

   scroll_info.cbSize = sizeof(scroll_info);
   scroll_info.fMask = SIF_ALL; // SIF_POS|SIF_RANGE;
   scroll_info.nMin=0;
   scroll_info.nMax=m_iListEntriesCount+m_iNumOfRows-2;  // -1 ??
   scroll_info.nPage=m_iNumOfRows;
   scroll_pos=(m_iCurSel<0)?0:m_iCurSel;
   scroll_info.nPos=scroll_pos;
   scroll_info.nTrackPos=scroll_pos;
   SetScrollInfo(m_hSubLBoxScrollBar, SB_CTL, &scroll_info, TRUE);

return(retc);
}


// -----------------------------------------
#ifdef KP_LISTBOX
BOOL CALLBACK KpListBoxDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HWND list_sub_field=NULL;
HWND scroll_bar=NULL;
int retp;
int retw=FALSE;
int retv;
bool endfl=False;
KpWnd *cur_wnd=NULL;
KpWnd *new_wnd=NULL;
unsigned char *cur_ptr;
int direction;
int new_pos;
WPARAM w_par;
// DWORD w_par;
// HWND prew_mouse_over=NULL;
LPMEASUREITEMSTRUCT p_measure_item = (LPMEASUREITEMSTRUCT)lParam;
LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;

KpTreeEntry *cur_node = NULL;
KpTreeEntry *cur_father = NULL;
KpTreeEntry *new_father = NULL;
KpTreeEntry *next_brother = NULL;
// int text_pos;
int trck_pos;
void *val_ptr = NULL;
int ii = 0;

#if FALSE // #ifdef Debug
if((uMsg==LB_GETTEXT) || (uMsg==KP_LB_GETTEXT))
   KP_TRACE_2("KpListBoxDialogProc: lParam: %lx uMsg: %d", lParam, uMsg);
#endif

   retp=LOWORD(wParam);

// --------------------------
   switch(uMsg)
   {
   case WM_CREATE:
      retw=TRUE;
      break;

   case WM_KP_CREATE:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if((!cur_wnd) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         list_sub_field=CreateWindowEx(
                  0,
                  "LISTBOX",
                  (LPCTSTR)"",
                  ((cur_wnd->m_dwStyle & LBS_OWNERDRAWFIXED)|WS_CHILD|WS_VISIBLE|DS_SETFONT|LBS_HASSTRINGS|LBS_DISABLENOSCROLL|LBS_NOTIFY)&(~LBS_SORT), // |WS_VSCROLL|WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  1,
                  1,
                  cur_wnd->m_iWdtDots-KPW_SCROLLBAR_WDT-
                     ((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?2*KPW_CTRL_BORDER_WDT:0)-2,
                  cur_wnd->m_iHgtDots-
                     ((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?2*KPW_CTRL_BORDER_WDT-2:0),
                  cur_wnd->m_hWndHandle, 0,
                  GetModuleHandle(NULL), 0);
         if(!list_sub_field)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

#if FALSE
      KP_NEWO(new_wnd, KpWnd(*cur_wnd));

      if(SUCCEEDED(retc))
      {
         new_wnd->m_iWndType = TYP_SubListBox;
         new_wnd->m_pNextWindow = NULL;
         new_wnd->m_hParent = new_wnd->m_hWndHandle;
         new_wnd->m_hWndHandle = list_sub_field;

         retc = WndPreg(new_wnd, TYP_SubListBox, cur_wnd->m_hInstance, NULL, False);
         if(FAILED(retc)) KP_DELETE(new_wnd);
      }
#endif

      if(SUCCEEDED(retc)) cur_wnd->m_hSubListBox=list_sub_field;

// KP_TRACE_2("KpListBoxDialogProc(): WM_KP_CREATE: hwndDlg:%lx list_sub_field:%lx", hwndDlg, list_sub_field);

      if(SUCCEEDED(retc)) retc=CrFont(&cur_wnd->m_hFont, cur_wnd->m_iKpCtrlStyle);
      if(SUCCEEDED(retc)) retc=SetCtrlFont(list_sub_field, cur_wnd->m_iKpCtrlStyle);

// PutLogMessage_("KpListBoxDialogProc() 1: %d", cur_wnd->m_iNumOfRows);

      if(SUCCEEDED(retc))
      {
         retv=SendMessage(list_sub_field, LB_INITSTORAGE, 3*cur_wnd->m_iNumOfRows, 3*cur_wnd->m_iNumOfRows*(cur_wnd->m_iNumOfCols+1));
         if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
         if((retv==LB_ERR) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc)) retc=KpCreateScrollBar(cur_wnd->m_hInstance, hwndDlg, &scroll_bar,
         cur_wnd->m_iWdtDots-KPW_SCROLLBAR_WDT-
            ((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?2*KPW_CTRL_BORDER_WDT:0), 1,
         cur_wnd->m_iHgtDots-
            ((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?2*KPW_CTRL_BORDER_WDT:0)-2, 0, SBS_VERT);
      if((scroll_bar==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) cur_wnd->m_hSubLBoxScrollBar=scroll_bar;

      retw=TRUE;
      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_QUIT:
   case WM_CLOSE:
      endfl = TRUE;
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      if(cur_wnd != NULL) cur_wnd->m_hWndHandle = NULL;
      break;

#if FALSE
   case WM_MOUSEMOVE:
#ifdef Debug
unsigned char str_buf[100];
sprintf((char *)str_buf, "WM_MOUSEMOVE: x: %d y: %d", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
KP_TRACE((const char *)str_buf);
#endif
// ----------------- mygtuku gesinimas
      prew_mouse_over = hMouseOverWnd;
      if(prew_mouse_over) // !=hwndDlg)
      {
         hMouseOverWnd = NULL; // hwndDlg;
//       if(prew_mouse_over)
            if(!InvalidateRect(prew_mouse_over, 0, TRUE))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
      }
      break;
#endif

   case WM_COMMAND:
      retw=0;
      if(retp==IDCANCEL) endfl=TRUE;
      switch(HIWORD(wParam))
      {
// ----------------------------- m_hSubListBox notification messages
      case LBN_SELCHANGE:
// KP_TRACE_1("KpListBoxDialogProc: LBN_SELCHANGE hwndDlg:%d", hwndDlg);
         if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

         if((cur_wnd==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) if((HWND)lParam==cur_wnd->m_hSubListBox)
         {
// ---------------------------- stumt rodoma segmenta
            if(SUCCEEDED(retc)) new_pos = SendMessage(cur_wnd->m_hSubListBox, LB_GETCURSEL, 0, 0L);
            KP_ASSERT(new_pos != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);

            if(SUCCEEDED(retc)) if(cur_wnd->m_iCurStartEntry < 0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, True, __FILE__, __LINE__, 0L, NULL);

//          if(SUCCEEDED(retc))
//             if((new_pos<cur_wnd->m_iNumOfRows) || (new_pos>=2*cur_wnd->m_iNumOfRows))
//                retc=SetListBoxSel(hwndDlg, new_pos + cur_wnd->m_iCurStartEntry);

            direction=1;
            if(SUCCEEDED(retc))
               if((new_pos<cur_wnd->m_iNumOfRows) && (cur_wnd->m_iCurStartEntry>0))
               {
                  if(new_pos==0) retc=SetKpListBoxSel(cur_wnd, 0, 1, False);
                  else direction=0;
               }
            if(SUCCEEDED(retc))
               if(
                  (new_pos>=2*cur_wnd->m_iNumOfRows) &&
                  (cur_wnd->m_iCurStartEntry + 3 * cur_wnd->m_iNumOfRows < cur_wnd->m_iListEntriesCount)
                 )
               {
                  if(new_pos>=3*cur_wnd->m_iNumOfRows-1)
                     retc=SetKpListBoxSel(cur_wnd, cur_wnd->m_iListEntriesCount-1, 1, False);
                  else direction=2;
               }
// KP_TRACE_3("LBN_SELCHANGE: new_pos: %d m_iNumOfRows: %d total rows: %d", new_pos, cur_wnd->m_iNumOfRows, 3*cur_wnd->m_iNumOfRows-1);

// ------------------------------------------------
            if(SUCCEEDED(retc))
            {
               if(direction!=1)
                  retc=SetKpListBoxSel(cur_wnd, cur_wnd->m_iCurStartEntry + new_pos, direction, False);
               else cur_wnd->m_iCurSel = cur_wnd->m_iCurStartEntry + new_pos;
            }
            if(SUCCEEDED(retc)) retc=cur_wnd->SetCurScrolPos();


// ---------------------------- perduot notifikacija tevui
// anksciau buvo gale, bet LzdShE netinka mazgai jau cia sukolapsinti/expandinti, o tevas dar po to kuiciasi
//    su tokiu, koks buvo pries tai
            if(SUCCEEDED(retc))
               if(cur_wnd->m_hParent==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
               retw=SendMessage(cur_wnd->m_hParent, uMsg, wParam, (LPARAM)cur_wnd->m_hWndHandle);


// ----------------------------------- tree node properties in listbox
            if(SUCCEEDED(retc)) if(cur_wnd) if(cur_wnd->m_pEntries)
            {
               if(SUCCEEDED(retc)) if((cur_wnd->m_iWndType == TYP_ListBoxTree) || (cur_wnd->m_iWndType == TYP_ListBoxTreeInverted))
               {
POINT point;
RECT rect;
// int trck_pos = 0; // KP_TREE_LBOX_MARGIN; // tarpelis jau yra ikoneleje
int trck_pos = -KP_TREE_LBOX_TRCK_WDT; // vyriausio prosenelio pliusiukas uz lango ribu
KpTreeEntry *cur_node;
KpTreeEntry *cur_father;
KpTreeEntry *new_father;
int ii;
                  if(SUCCEEDED(retc)) if(cur_wnd->m_iCurStartEntry<0)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc))
                  {
                     ii = new_pos + cur_wnd->m_iCurStartEntry;
                     cur_node = NULL;
                     retc = cur_wnd->m_pEntries->GetEntryPtr(&ii, &cur_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_wnd->m_pEntries);
// PutLogMessage_("KpListBoxDialogProc() 2: %d %d %s", ii, new_pos, cur_node?(const char *)cur_node->GetValue():"null");
                  }

// ------------------------------------ skaiciuojam mazgo gyli - boksiuko pozicija
                  if(cur_node && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc = cur_node->GetFather(&cur_father);
                     while(cur_father && SUCCEEDED(retc))
                     {
                        retc = cur_father->GetFather(&new_father);
                        if(SUCCEEDED(retc)) if(cur_father==cur_wnd->m_pEntries) new_father = NULL;

//                      if(new_father && SUCCEEDED(retc)) // vyriausias prosenelis pliusiuko neturi
                           trck_pos += KP_TREE_LBOX_TRCK_WDT;

                        cur_father = new_father;
                     }
                  }

// ----------------------------------- expand/collapse tree node in listbox
int status = 0;
int flag = 0;
                  if(cur_node && SUCCEEDED(retc))
                  {
                     status = cur_node->m_iStatus;
                     if(cur_wnd->m_iWndType == TYP_ListBoxTree) status = status >> KpNodeLevelShift;
                  }

                  if(cur_node && SUCCEEDED(retc))
#if FALSE
                     if(
                        (
                           ((cur_node->m_iStatus==KpHighExpandedNode) || (cur_node->m_iStatus==KpHighCollapsedNode)) &&
                           (cur_wnd->m_iWndType == TYP_ListBoxTree)
                        ) ||
                        (
                           (
                              (cur_node->m_iStatus==KpLowExpandedNode) || (cur_node->m_iStatus==KpLowCollapsedNode) ||
                              (cur_node->m_iStatus==KpHighExpandedNode) || (cur_node->m_iStatus==KpHighCollapsedNode)
                           ) &&
                           (cur_wnd->m_iWndType == TYP_ListBoxTreeInverted)
                        )
                       )
#else
                     if((status & KpNodeHasChildren) != 0)
#endif
                  {
#if FALSE
MOUSEMOVEPOINT mpoint;
                     if(SUCCEEDED(retc))
                     {
                        ii=GetMouseMovePointsEx(sizeof(mpoint),
    LPMOUSEMOVEPOINT lppt,
    LPMOUSEMOVEPOINT lpptBuf,
    int nBufPoints,
    DWORD resolution
);
#endif
                     if(SUCCEEDED(retc)) if(!GetCursorPos(&point)) // get current mouse possition
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                     if(SUCCEEDED(retc)) if(!GetWindowRect(hwndDlg, &rect))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
// sprintf((char *)str_buf, "LBN_SELCHANGE: wParam: %x lParam: %lx", wParam, lParam);
sprintf((char *)str_buf, "LBN_SELCHANGE: x: %d y: %d", point.x-rect.left, point.y-rect.top);
KP_TRACE((const char *)str_buf);
#endif
                     if(
                        (point.x-rect.left >= trck_pos) &&
                        (point.x-rect.left <= trck_pos + KP_TREE_LBOX_TRCK_WDT) &&
                        SUCCEEDED(retc))
                     {
#if FALSE
                        switch(cur_node->m_iStatus)
                        {
                        case KpHighExpandedNode: cur_node->m_iStatus=KpHighCollapsedNode; break;
                        case KpHighCollapsedNode: cur_node->m_iStatus=KpHighExpandedNode; break;
                        case KpLowExpandedNode: cur_node->m_iStatus=KpLowCollapsedNode; break;
                        case KpLowCollapsedNode: cur_node->m_iStatus=KpLowExpandedNode; break;
                        }
#else
                        flag = KpNodeExpanded;
                        if(cur_wnd->m_iWndType == TYP_ListBoxTree) flag = flag << KpNodeLevelShift;

                        if((cur_node->m_iStatus & flag) != 0) cur_node->m_iStatus &= (~flag);
                        else cur_node->m_iStatus |= flag;
#endif

#if FALSE
int ii = 0;
                        if(SUCCEEDED(retc)) retc=cur_wnd->m_pEntries->CountEntries(&ii, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_wnd->m_pEntries);
                        if(SUCCEEDED(retc)) retc = cur_wnd->SetListEntriesCount(ii);
#else
                       if(SUCCEEDED(retc)) retc = cur_wnd->ResetListBoxContents(cur_wnd->m_iNumOfListEntries, cur_wnd->m_iListEntriesBufSize/cur_wnd->m_iNumOfListEntries);
#endif
                     }

                  } // if(cur_node && SUCCEEDED(retc))

               } // if((cur_wnd->m_iWndType == TYP_ListBoxTree) || (cur_wnd->m_iWndType == TYP_ListBoxTreeInverted))

// --------------------- TYP_ListBoxChk ?ra?o invertavimas
               if(SUCCEEDED(retc)) if(cur_wnd->m_iWndType == TYP_ListBoxChk)
               {
                  KP_ASSERT(cur_wnd->m_iCurStartEntry >= 0, KP_E_SYSTEM_ERROR, null, True);

                  if(SUCCEEDED(retc))
                  {
                     ii = new_pos + cur_wnd->m_iCurStartEntry;
                     cur_node = NULL;
                     retc = cur_wnd->m_pEntries->GetEntryPtr(&ii, &cur_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_wnd->m_pEntries);
                  }

                  if(SUCCEEDED(retc))
                  {
KpTextChk *text_chk_ptr = (KpTextChk *)cur_node->GetValue();
                     KP_ASSERT(text_chk_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
                     KP_ASSERT(cur_node->GetValSize() >= sizeof(KpTextChk), KP_E_SYSTEM_ERROR, null, True);

                     if(SUCCEEDED(retc)) text_chk_ptr->m_bChecked = !text_chk_ptr->m_bChecked;
                  }

                  KP_ASSERT(InvalidateRect(cur_wnd->m_hWndHandle, NULL, True), KP_E_SYSTEM_ERROR, GetLastError(), False);

               } // if(SUCCEEDED(retc)) if(cur_wnd->m_iWndType == TYP_ListBoxChk)

            } // if(SUCCEEDED(retc)) if(cur_wnd) if(cur_wnd->m_pEntries)

         } // if(SUCCEEDED(retc)) if((HWND)lParam==cur_wnd->m_hSubListBox)

         if(FAILED(retc) && (retw>=0)) retw=LB_ERR;

         break; // case LBN_SELCHANGE

      } // switch(HIWORD(wParam))

      break;

// -------------------------------
#if FALSE
   case WM_LBUTTONDOWN:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

int x_pos;
int y_pos;

      if(SUCCEEDED(retc))
      {
         x_pos = LOWORD(lParam);
         y_pos = HIWORD(lParam);
      }

#if FALSE // #ifdef Debug
unsigned char str_buf[100];
sprintf((char *)str_buf, "WM_LBUTTONDOWN: x_pos: %d y_pos: %d", x_pos, y_pos);
KP_TRACE((const char *)str_buf);
#endif

      break;
#endif

// ----------------------------- m_hSubListBox messages
   case WM_SETREDRAW:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg)))
      {
         cur_wnd=NULL;
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
      }
      retw=0;
      if((cur_wnd!=NULL) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc))
            if(cur_wnd->m_hSubListBox==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            retw=SendMessage(cur_wnd->m_hSubListBox, uMsg, wParam, lParam);
      }
      break;

   case WM_SIZE:
// KP_TRACE("KpListBoxDialogProc: WM_SIZE");

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg)))
      {
         cur_wnd=NULL;
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
      if((cur_wnd!=NULL) && SUCCEEDED(retc))
      {
         cur_wnd->m_iWdtDots=LOWORD(lParam);
         cur_wnd->m_iHgtDots=HIWORD(lParam);

         cur_wnd->m_iNumOfRows=cur_wnd->m_iHgtDots/iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle];

//       if(cur_wnd->m_plpszListEntries!=NULL)
         {
            if(SUCCEEDED(retc))
               if(!SetWindowPos(cur_wnd->m_hSubLBoxScrollBar, HWND_TOP,
                  cur_wnd->m_iWdtDots-KPW_SCROLLBAR_WDT
//                   -((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?KPW_CTRL_BORDER_WDT-1:0)
                     ,
                  0, // 1,
                  KPW_SCROLLBAR_WDT,
                  cur_wnd->m_iHgtDots
                     -((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?KPW_CTRL_BORDER_WDT-1:0)
//                   -2
                     ,
                  0))
                  {
#ifdef Debug
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                  }

            if((cur_wnd->m_hSubListBox!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(cur_wnd->m_hSubListBox, LB_RESETCONTENT, 0, 0L);

               retv=SendMessage(cur_wnd->m_hSubListBox, LB_INITSTORAGE, 3*cur_wnd->m_iNumOfRows, 3*cur_wnd->m_iNumOfRows*(cur_wnd->m_iNumOfCols+1));
               if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                  retc=KP_E_SYSTEM_ERROR;
               }
            }

            if((cur_wnd->m_hSubListBox!=NULL) && SUCCEEDED(retc))
            {
               if(!SetWindowPos(cur_wnd->m_hSubListBox, HWND_TOP,
                  0, // 1,
                  0, // ((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?0:KPW_CTRL_BORDER_WDT), // 1,
                  cur_wnd->m_iWdtDots-KPW_SCROLLBAR_WDT
//                   -((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?KPW_CTRL_BORDER_WDT:0)
//                   -2
                     ,
                  cur_wnd->m_iHgtDots
//                   -((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?KPW_CTRL_BORDER_WDT-1:0)
//                   +((cur_wnd->m_dwExStyle&(WS_EX_CLIENTEDGE|ES_SUNKEN))?0:KPW_CTRL_BORDER_WDT)
                     ,
                  0))
                  {
#ifdef Debug
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                  }
            }

            if((cur_wnd->m_plpszListEntries!=NULL) && SUCCEEDED(retc))
               if(SUCCEEDED(retc))
                  retc=SetKpListBoxSel(cur_wnd, cur_wnd->m_iCurSel, 1, True);

         } // if(cur_wnd->m_plpszListEntries!=NULL)

      } // if((cur_wnd!=NULL) && SUCCEEDED(retc))

      break;

   case LB_INITSTORAGE:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      retw=wParam;
      retc0=retc; // kodel retc0 ???

      if((cur_wnd==NULL) && SUCCEEDED(retc0))
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#if FALSE
      if(SUCCEEDED(retc0))
         if(cur_wnd->m_hSubListBox==NULL)
            retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc0))
      {
         retv=SendMessage(cur_wnd->m_hSubListBox, uMsg, wParam, lParam);
         if(retv == LB_ERRSPACE)
            retc0 = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), TRUE, __FILE__, __LINE__, 0L);
      }
#endif

      if(SUCCEEDED(retc)) cur_wnd->m_pEntries = NULL;

      if(SUCCEEDED(retc0))
         if(
            (cur_wnd->m_plpszListEntries!=NULL) ||
            (cur_wnd->m_iNumOfListEntries!=0) ||
            (cur_wnd->m_iListEntriesCount!=0) ||
            (cur_wnd->m_lpszListEntriesBuf!=NULL) ||
            (cur_wnd->m_iListEntriesBufSize!=0)
           )
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, null, TRUE, __FILE__, __LINE__, 0L);
            retw=LB_ERR;
         }

      if(SUCCEEDED(retc0))
      {
         KP_NEWA(cur_wnd->m_plpszListEntries, unsigned char *, wParam);
         if(cur_wnd->m_plpszListEntries == NULL) retw = LB_ERRSPACE;
      }

      if(SUCCEEDED(retc0)) cur_wnd->m_iNumOfListEntries=wParam;
      if(SUCCEEDED(retc0))
         for(int ii=0; ii < cur_wnd->m_iNumOfListEntries; ii++)
            cur_wnd->m_plpszListEntries[ii] = NULL;

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "m_iNumOfListEntries: %d", cur_wnd->m_iNumOfListEntries);
KP_TRACE(str_buf);
#endif


      if(SUCCEEDED(retc0))
      {
         KP_NEWA(cur_wnd->m_lpszListEntriesBuf, unsigned char, lParam);
         if(cur_wnd->m_lpszListEntriesBuf == NULL) retw = LB_ERRSPACE;
      }

      if(SUCCEEDED(retc0)) cur_wnd->m_iListEntriesBufSize = lParam;

      if(FAILED(retc0) && (retw>=0)) retw=LB_ERR;

      break;


   case LB_RESETCONTENT:
      retw=0;

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) cur_wnd->m_pEntries = NULL;

      if(SUCCEEDED(retc))
         if(cur_wnd->m_hSubListBox==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         retw = SendMessage(cur_wnd->m_hSubListBox, uMsg, wParam, lParam);

      if(SUCCEEDED(retc))
      {
         KP_DELETEA(cur_wnd->m_plpszListEntries);
         cur_wnd->m_iNumOfListEntries=0;
         cur_wnd->m_iListEntriesCount=0;
         KP_DELETEA(cur_wnd->m_lpszListEntriesBuf);
         cur_wnd->m_iListEntriesBufSize = 0;

// ----- kazko buvo uzkomentuota
         cur_wnd->m_iCurStartEntry=(-1);
         cur_wnd->m_iCurSel=(-1);
// -----
      }

      if(FAILED(retc)) retw=LB_ERR;

      break;

   case KP_LB_SETSTRINGLIST:
KpTreeEntry *cur_entry;

      cur_entry = NULL;
      cur_wnd = NULL;
      retw = 0;

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      if((cur_wnd == NULL) && SUCCEEDED(retc0))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) cur_entry = cur_wnd->m_pEntries = (KpTreeEntry *)lParam;
      if((cur_entry != NULL) && SUCCEEDED(retc))
      {
//       if(SUCCEEDED(retc)) retc = cur_entry->FormListBox(hwndDlg /* cur_wnd->m_hWndHandle */);

#ifdef Debug
if(SUCCEEDED(retc)) if(cur_wnd->m_iWndType==TYP_ListBoxTree)
   cur_wnd->m_iWndType=TYP_ListBoxTree;
#endif

         if(SUCCEEDED(retc))
         {
            if((cur_wnd->m_iWndType == TYP_ListBoxTree) || (cur_wnd->m_iWndType == TYP_ListBoxTreeInverted))
            {
#if TRUE // FALSE
int ii = 0;
               if(SUCCEEDED(retc)) retc = cur_entry->CountEntries(&ii, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_entry);
               if(SUCCEEDED(retc)) retc = cur_wnd->SetListEntriesCount(ii);
#else
// negalima - gausis rekursija
//             if(SUCCEEDED(retc)) retc = cur_wnd->ResetListBoxContents(cur_wnd->m_iNumOfListEntries);
#endif
            }
            else if((cur_wnd->m_iWndType == TYP_ListBox) || (cur_wnd->m_iWndType == TYP_ListBoxChk))
            {
               if(SUCCEEDED(retc)) SendMessage(hwndDlg, WM_SETREDRAW, FALSE, 0L);
LRESULT retv;
//             if(SUCCEEDED(retc)) retc = ResetListBoxContents(hwndDlg, 0, 300, False, cur_entry);

               while((cur_entry != NULL) && SUCCEEDED(retc))
               {
const unsigned char *str_ptr = (const unsigned char *)cur_entry->GetValue();

// PutLogMessage_("KP_LB_SETSTRINGLIST: >>>%s<<<", str_ptr);
                  if(SUCCEEDED(retc))
                  {
                     retv = SendMessage(hwndDlg, LB_ADDSTRING, 0, (LPARAM)str_ptr);
                     KP_ASSERT(retv != LB_ERR, KP_E_SYSTEM_ERROR, GetLastError(), True);
                     KP_ASSERT(retv != LB_ERRSPACE, KP_E_OUTOFMEM, GetLastError(), True);
                  }

//                if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild(&cur_entry);
                  if(SUCCEEDED(retc)) cur_entry = cur_entry->m_pFirstChild;
               }

               if(SUCCEEDED(retc)) SendMessage(hwndDlg, WM_SETREDRAW, TRUE, 0L);

            } // else if(iWndType == TYP_ListBox)

         } // if(SUCCEEDED(retc))

      } // if((cur_entry != NULL) && SUCCEEDED(retc))

#if FALSE // #ifdef Debug
// char str_buf[100];
sprintf(str_buf, "m_iListEntriesCount: %d", cur_wnd->m_iListEntriesCount);
KP_TRACE(str_buf);
#endif

      if(SUCCEEDED(retc)) if(cur_wnd->m_pEntries) retc = SetListBoxSel(hwndDlg, -1);

      if(FAILED(retc) && (retw>=0)) retw = LB_ERR;
      break;

   case LB_ADDSTRING:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

#if FALSE // #ifdef Debug
// char str_buf[100];
if(SUCCEEDED(retc))
{
if((cur_wnd->m_iWndType == TYP_ListBoxTree) || (cur_wnd->m_iWndType == TYP_ListBoxTreeInverted))
{
sprintf(str_buf, "LB_ADDSTRING %s %d", lParam, hwndDlg);
KP_TRACE(str_buf);
}
}
#endif

      retw=0;
      retc0=retc; // kodel retc0 ???

      if((cur_wnd==NULL) && SUCCEEDED(retc0))
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if((lParam==0) && SUCCEEDED(retc0))
      {
         retc0=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
         retw=LB_ERR;
      }

      if(SUCCEEDED(retc0))
         if(
            (cur_wnd->m_plpszListEntries==NULL) ||
            (cur_wnd->m_iNumOfListEntries<=0) ||
            (cur_wnd->m_iListEntriesCount<0) ||
            (cur_wnd->m_lpszListEntriesBuf==NULL) ||
            (cur_wnd->m_iListEntriesBufSize<=0)
           )
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            retw=LB_ERR;
         }

// TODO !!!!!! RRRRRRR - persipildo lzdshp pDialogPtr->m_HistList, reikt¸ i?metin?t po vien? (pirm?) (LB_DELETESTRING)
//                         kol kas dar nemoku, i?metu visus (?r. lzdshl.cpp LzdshAppendStrToList())
      if(SUCCEEDED(retc0))
         if(cur_wnd->m_iListEntriesCount>=cur_wnd->m_iNumOfListEntries)
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
            retw=LB_ERRSPACE;
         }

      if(SUCCEEDED(retc0))
      {
         cur_ptr=cur_wnd->m_lpszListEntriesBuf;
         if(cur_wnd->m_iListEntriesCount>0)
         {
            if(cur_wnd->m_plpszListEntries[cur_wnd->m_iListEntriesCount-1]==NULL)
               retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc0))
               cur_ptr=cur_wnd->m_plpszListEntries[cur_wnd->m_iListEntriesCount-1]+
                  strlen(cur_wnd->m_plpszListEntries[cur_wnd->m_iListEntriesCount-1])+1;
         }
         if((lParam==0) && SUCCEEDED(retc0))
            retc0=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc0))
            if(cur_ptr+strlen((const unsigned char *)lParam) >=
               cur_wnd->m_lpszListEntriesBuf+cur_wnd->m_iListEntriesBufSize)
               {
                  retc0=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
                  retw=LB_ERRSPACE;
               }
      }
      if(SUCCEEDED(retc0))
      {
         strcpy(cur_ptr, (const unsigned char *)lParam);
         cur_wnd->m_plpszListEntries[cur_wnd->m_iListEntriesCount++]=cur_ptr;
         if(SUCCEEDED(retc)) if(cur_wnd->m_iListEntriesCount > cur_wnd->m_iNumOfListEntries)
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            cur_wnd->m_iListEntriesCount = cur_wnd->m_iNumOfListEntries;
            retw=LB_ERRSPACE;
         }
      }

#if FALSE // #ifdef Debug
// char str_buf[100];
sprintf(str_buf, "m_iListEntriesCount: %d", cur_wnd->m_iListEntriesCount);
KP_TRACE(str_buf);
#endif

// KP_TRACE_2("KpListBoxDialogProc: m_iListEntriesCount:%d 3*m_iNumOfRows:%d", cur_wnd->m_iListEntriesCount, 3*cur_wnd->m_iNumOfRows);

      if(SUCCEEDED(retc0)) if(cur_wnd->m_iListEntriesCount <= 3*cur_wnd->m_iNumOfRows) // ?ia tik pradin?j stadijoj, kol listas pustu?tis
      {                                                                                // po to visk? valdo selektinimas - dabar
// KP_TRACE("KpListBoxDialogProc: SendMessage(m_hSubListBox)");                        // m_hSubListBox-e matosi netoliau prie?paskutinio ?ra?o
         if(cur_wnd->m_hSubListBox==NULL)
            retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc0))
         {
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *pntd = NULL;

            if(SUCCEEDED(retc0))
               if(strlen((const unsigned char *)lParam) >= KP_MAX_FILE_LIN_WDT)
                  retc0=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL);

// ------------ nukandam technin_ ?ra?o dal?
            if(SUCCEEDED(retc0))
            {
               strncpy(str_buf, (const unsigned char *)lParam, KP_MAX_FILE_LIN_WDT);
               str_buf[KP_MAX_FILE_LIN_WDT] = Nul;

               pntd = strchr(str_buf, TECH_DELIM_CHR);
               if(pntd) *pntd = Nul;
            }

            retv=SendMessage(cur_wnd->m_hSubListBox, uMsg, wParam, (LPARAM)str_buf);
            if((retv==LB_ERR) && SUCCEEDED(retc0))
               retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if((retv==LB_ERRSPACE) && SUCCEEDED(retc0))
               retc0=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc0))
         retw=cur_wnd->m_iListEntriesCount-1;
      else if(retw>=0) retw=LB_ERR;

//    if(SUCCEEDED(retc)) retc=cur-wnd->SetCurScrolPos();

      break;

   case LB_DELETESTRING:
      KP_ERROR(E_NOTIMPL, null);
#if FALSE
      retw = 0;
      retc0 = retc; // kodel retc0 ???

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      KP_ASSERT0(cur_wnd, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT0(wParam >= 0, E_INVALIDARG, null, True);

// PutLogMessage_("LB_DELETESTRING %d", wParam);

      KP_ASSERT0(cur_wnd->m_plpszListEntries, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT0(cur_wnd->m_iNumOfListEntries > 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT0(cur_wnd->m_iListEntriesCount >= 0, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT0(cur_wnd->m_lpszListEntriesBuf, KP_E_SYSTEM_ERROR, null, True);
      KP_ASSERT0(cur_wnd->m_iListEntriesBufSize > 0, KP_E_SYSTEM_ERROR, null, True);

      KP_ASSERT0(cur_wnd->m_iListEntriesCount < wParam, E_INVALIDARG, null, True);

      if(SUCCEEDED(retc0)) if(cur_wnd->m_iListEntriesCount > wParam)
      {

      }
#endif
      if(FAILED(retc0)) retw = LB_ERR;
      break;

   case WM_MEASUREITEM:
      retw=TRUE;

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;
      if((/* (cur_wnd==NULL) || */ (p_measure_item==NULL)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if((cur_wnd!=NULL) && SUCCEEDED(retc))
      {
         if(
            (
               (wParam!=0) ||
//             (!(cur_wnd->m_dwStyle & LBS_OWNERDRAWFIXED)) ||
               ((cur_wnd->m_iWndType != TYP_ListBoxTree) && (cur_wnd->m_iWndType != TYP_ListBoxTreeInverted) && (cur_wnd->m_iWndType != TYP_ListBoxChk))
            ) &&
            SUCCEEDED(retc)
           )
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) if((cur_wnd->m_iKpCtrlStyle<0) || (cur_wnd->m_iKpCtrlStyle >= KPW_NUM_OF_CONTROL_STYLES_0))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) p_measure_item->itemHeight = iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle];

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "WM_MEASUREITEM %d %d %d %d", iWindowsVersion, cur_wnd->m_iKpCtrlStyle, iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle], hwndDlg);
KP_TRACE(str_buf);
#endif

         if(SUCCEEDED(retc)) retw=TRUE;
      }
      break;


   case LB_GETITEMRECT:
      retw=TRUE;

int sel;
RECT *rect_ptr;
      sel = wParam;
      rect_ptr = (RECT *)lParam;
      if((rect_ptr == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;
      if((cur_wnd==NULL) & SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) if((sel < 0) || (sel >= cur_wnd->m_iListEntriesCount))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) if((cur_wnd->m_hSubListBox == NULL) || (cur_wnd->m_pEntries == NULL))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(SendMessage(cur_wnd->m_hSubListBox, LB_GETITEMRECT, wParam, lParam) == LB_ERR)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      ii = 0;
      if(SUCCEEDED(retc))
      {
         ii = sel + cur_wnd->m_iCurStartEntry;
         cur_node = NULL;
         retc = cur_wnd->m_pEntries->GetEntryPtr(&ii, &cur_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_wnd->m_pEntries);
      }
      if((cur_node == NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// ------------------------- skaiciuojam x pozicija
      trck_pos = 0; // KP_TREE_LBOX_MARGIN; // tarpelis jau bus is ikoneles
      if(SUCCEEDED(retc)) trck_pos = rect_ptr->left;

// ----------------------- individuali mazgo ikonele
      val_ptr = NULL;
      if(SUCCEEDED(retc)) val_ptr = cur_node->GetValue();
// PutLogMessage_("KpListBoxDialogProc() WM_GETITEMRECT: ", ii, sel, (const char *)val_ptr);
      if(SUCCEEDED(retc)) if((cur_node->m_iRecType == KpRecType_TextBmp) || (cur_node->m_iRecType == KpRecType_BmpBmp))
      {
         KP_ASSERT(val_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(cur_node->GetValSize() >= sizeof(KpTextBmp), KP_E_SYSTEM_ERROR, null, True);

         if(SUCCEEDED(retc)) if(cur_node->m_iRecType == KpRecType_TextBmp)
            if(((KpTextBmp *)val_ptr)->m_hBmp) trck_pos += KP_TREE_LBOX_TRCK_WDT;

         if(SUCCEEDED(retc)) if(cur_node->m_iRecType == KpRecType_BmpBmp)
            if(((KpBmpBmp *)val_ptr)->m_hBmp) trck_pos += KP_TREE_LBOX_TRCK_WDT;

// ----------------------- pagrindinis medzio boksiukas (pliusiukas/minusiukas/kampukas)
         if(SUCCEEDED(retc)) retc = cur_node->GetFather(&cur_father);
         if(cur_father && SUCCEEDED(retc)) // vyriausiam proseneliui pliusiuko nereikia
            trck_pos += KP_TREE_LBOX_TRCK_WDT;

// ----------------------- kiti tevu bruksniukai
         while(cur_father && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = cur_father->GetFather(&new_father);
            if(SUCCEEDED(retc)) if(cur_father == cur_wnd->m_pEntries) new_father = NULL;
// vyriausiam proseneliui pliusiuko nereikia
            if(new_father && SUCCEEDED(retc))
               trck_pos += KP_TREE_LBOX_TRCK_WDT;

            if(SUCCEEDED(retc)) cur_father = new_father;
         }

      } // if((cur_node->m_iRecType == KpRecType_TextBmp) || (cur_node->m_iRecType == KpRecType_BmpBmp))

      if(SUCCEEDED(retc)) rect_ptr->left = trck_pos;

      break;

   case WM_DRAWITEM:
      retw=TRUE;

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;
      if((/* (cur_wnd==NULL) || */ (lpdis==NULL)) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if((cur_wnd!=NULL) && SUCCEEDED(retc)) if(lpdis->itemID != -1)
      {
         switch (lpdis->itemAction)
         {
         case ODA_FOCUS:
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
sprintf((char *)str_buf, "ODA_FOCUS: wParam: %x lParam: %lx", wParam, lParam);
KP_TRACE((const char *)str_buf);
#endif
            break;

         case ODA_SELECT:
#if FALSE // #ifdef Debug
// unsigned char str_buf[100];
sprintf((char *)str_buf, "ODA_SELECT: wParam: %x lParam: %lx", wParam, lParam);
KP_TRACE((const char *)str_buf);
#endif
         case ODA_DRAWENTIRE:

// ---------------------- tree tracks
HBITMAP bmp_arr[KP_MAX_TREE_DEPTH];
int bmp_arr_ix;

int status = 0;
int brother_status = 0;

int ii;
HBITMAP hbmp = 0;
HGDIOBJ /* HBITMAP */ hbmp_old = 0;
HDC hdc_mem = 0;
KpBmpBmp *bmp_bmp_value = NULL;

            trck_pos = KP_TREE_LBOX_MARGIN; // grynai tekstinis listboxas ka?kod?l i?lenda u? kairio kra?to

            if(SUCCEEDED(retc))
               if(
//                (!(cur_wnd->m_dwStyle & LBS_OWNERDRAWFIXED)) ||
                  ((cur_wnd->m_iWndType != TYP_ListBoxTree) && (cur_wnd->m_iWndType != TYP_ListBoxTreeInverted) && (cur_wnd->m_iWndType != TYP_ListBoxChk)) ||
                  (cur_wnd->m_pEntries == NULL) ||
                  (cur_wnd->m_iCurStartEntry < 0)
                 )
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               ii = lpdis->itemID + cur_wnd->m_iCurStartEntry;
               cur_node = NULL;
               retc = cur_wnd->m_pEntries->GetEntryPtr(&ii, &cur_node, (cur_wnd->m_iWndType==TYP_ListBoxTree)?1:0, cur_wnd->m_pEntries);
            }

            if((cur_node != NULL) && /* (lpdis->itemID>=0) && (lpdis->itemID<7) && */ SUCCEEDED(retc))
            {
// PutLogMessage_("ODA_DRAWENTIRE: %d %d %s", lpdis->itemID + cur_wnd->m_iCurStartEntry, cur_node->m_iRecType, (const unsigned char *)cur_node->GetValue());
               bmp_arr_ix = 0;
//             text_pos = KP_TREE_LBOX_MARGIN;

// ----------------------- individuali mazgo ikonele
               val_ptr = NULL;
               if(SUCCEEDED(retc)) val_ptr = cur_node->GetValue();
               if(SUCCEEDED(retc)) switch(cur_node->m_iRecType)
               {
               case KpRecType_Text:
                  break;

               case KpRecType_TextChk:
                  KP_ASSERT(val_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
                  KP_ASSERT(cur_node->GetValSize() >= sizeof(KpTextChk), KP_E_SYSTEM_ERROR, null, True);

                  if(SUCCEEDED(retc))
                  {
                     bmp_arr[bmp_arr_ix] = ((KpTextChk *)val_ptr)->m_bChecked?hbmpChecked:hbmpUnChecked;
                     KP_ASSERT(bmp_arr[bmp_arr_ix] != NULL, KP_E_SYSTEM_ERROR, null, True);
                     KP_ASSERT(bmp_arr_ix < KP_MAX_TREE_DEPTH - 1, KP_E_BUFFER_OVERFLOW, null, True);
                     if(SUCCEEDED(retc)) bmp_arr_ix++;
                  }
                  break;

               case KpRecType_TextBmp:
                  KP_ASSERT(val_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
                  KP_ASSERT(cur_node->GetValSize() >= sizeof(KpTextBmp), KP_E_SYSTEM_ERROR, null, True);

                  if(SUCCEEDED(retc))
                  {
                     bmp_arr[bmp_arr_ix] = ((KpTextBmp *)val_ptr)->m_hBmp;
                     if(bmp_arr[bmp_arr_ix])
                     {
                        KP_ASSERT(bmp_arr_ix < KP_MAX_TREE_DEPTH - 1, KP_E_BUFFER_OVERFLOW, null, True);
                        if(SUCCEEDED(retc)) bmp_arr_ix++;
                     }
                  }
                  break;

               case KpRecType_BmpBmp:
                  KP_ASSERT(val_ptr != NULL, KP_E_SYSTEM_ERROR, null, True);
                  KP_ASSERT(cur_node->GetValSize() >= sizeof(KpBmpBmp), KP_E_SYSTEM_ERROR, null, True);

                  if(SUCCEEDED(retc))
                  {
                     bmp_arr[bmp_arr_ix] = ((KpBmpBmp *)val_ptr)->m_hBmp;
                     if(bmp_arr[bmp_arr_ix])
                     {
                        KP_ASSERT(bmp_arr_ix < KP_MAX_TREE_DEPTH - 1, KP_E_BUFFER_OVERFLOW, null, True);
                        if(SUCCEEDED(retc)) bmp_arr_ix++;
                     }
                  }
                  break;

               default:
                  KP_ERROR(KP_E_SYSTEM_ERROR, null);
                  break;
               }

               if((cur_wnd->m_iWndType==TYP_ListBoxTree) || (cur_wnd->m_iWndType==TYP_ListBoxTreeInverted))
               {
// ----------------------- pagrindinis medzio boksiukas (pliusiukas/minusiukas/kampukas)
                  if(SUCCEEDED(retc)) retc = cur_node->GetFather(&cur_father);
                  if(cur_father && SUCCEEDED(retc)) // vyriausiam proseneliui pliusiuko nereikia
                  {
                     bmp_arr[bmp_arr_ix] = 0;

                     status = cur_node->m_iStatus;
                     if(cur_wnd->m_iWndType==TYP_ListBoxTree) status = status >> KpNodeLevelShift;
#if FALSE
                     if(cur_node->m_pFirstChild)
                     {
                        if(cur_node->m_pNextBrother)
                        {
                           switch(cur_node->m_iStatus)
                           {
                           case KpHighChildlessNode:

//                            if(SUCCEEDED(retc)) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                              bmp_arr[bmp_arr_ix] = hbmpNodeBottom;
                              break;
                           case KpHighExpandedNode: bmp_arr[bmp_arr_ix] = hbmpNodeOpen; break;
                           case KpHighCollapsedNode: bmp_arr[bmp_arr_ix] = hbmpNodeClosed; break;

                           case KpLowChildlessNode: bmp_arr[bmp_arr_ix] = hbmpNodeBottom; break;
                           case KpLowExpandedNode:
                              if(cur_wnd->m_iWndType==TYP_ListBoxTreeInverted) bmp_arr[bmp_arr_ix] = hbmpNodeOpen;
                              else bmp_arr[bmp_arr_ix] = hbmpNodeBottom;
                              break;
                           case KpLowCollapsedNode:
                              if(cur_wnd->m_iWndType==TYP_ListBoxTreeInverted) bmp_arr[bmp_arr_ix] = hbmpNodeClosed;
                              else bmp_arr[bmp_arr_ix] = hbmpNodeBottom;
                              break;
                           }
                        }
                        else
                        {
                           switch(cur_node->m_iStatus)
                           {
                           case KpHighChildlessNode:
//                            if(SUCCEEDED(retc)) retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                              bmp_arr[bmp_arr_ix] = hbmpNodeBottomLast;
                              break;
                           case KpHighExpandedNode: bmp_arr[bmp_arr_ix] = hbmpNodeOpenLast; break;
                           case KpHighCollapsedNode: bmp_arr[bmp_arr_ix] = hbmpNodeClosedLast; break;

                           case KpLowChildlessNode: bmp_arr[bmp_arr_ix] = hbmpNodeBottomLast; break;

                           case KpLowExpandedNode:
                              if(cur_wnd->m_iWndType==TYP_ListBoxTreeInverted) bmp_arr[bmp_arr_ix] = hbmpNodeOpenLast;
                              else bmp_arr[bmp_arr_ix] = hbmpNodeBottomLast;
                              break;
                           case KpLowCollapsedNode:
                              if(cur_wnd->m_iWndType==TYP_ListBoxTreeInverted) bmp_arr[bmp_arr_ix] = hbmpNodeClosedLast;
                              else bmp_arr[bmp_arr_ix] = hbmpNodeBottomLast;
                              break;
                           }
                        }
                     }
                     else
                     {
                        if(
                           (cur_node->m_iStatus!=KpHighChildlessNode) &&
                           (cur_node->m_iStatus!=KpLowChildlessNode) &&
                           SUCCEEDED(retc)
                          )
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

                        if(cur_node->m_pNextBrother) bmp_arr[bmp_arr_ix] = hbmpNodeBottom;
                        else bmp_arr[bmp_arr_ix] = hbmpNodeBottomLast;
                     }
#else
                     next_brother = cur_node->m_pNextBrother;
                     if(next_brother)
                     {
                        brother_status = next_brother->m_iStatus;
                        if(cur_wnd->m_iWndType==TYP_ListBoxTree) brother_status = brother_status >> KpNodeLevelShift;
                        if((brother_status & KpNodeVisible) == 0) next_brother = NULL; // neuztenka - reikia, kad visi tolesni broliai butu nematomi (priklausytu kitam lygmeniui)
                     }

                     if(next_brother)
                     {
                        if((status & KpNodeHasChildren) != 0)
                        {
                           if((status & KpNodeExpanded) != 0) bmp_arr[bmp_arr_ix] = hbmpNodeOpen;
                           else bmp_arr[bmp_arr_ix] = hbmpNodeClosed;
                        }
                        else bmp_arr[bmp_arr_ix] = hbmpNodeBottom;
                     }
                     else
                     {
                        if((status & KpNodeHasChildren) != 0)
                        {
                           if((status & KpNodeExpanded) != 0) bmp_arr[bmp_arr_ix] = hbmpNodeOpenLast;
                           else bmp_arr[bmp_arr_ix] = hbmpNodeClosedLast;
                        }
                        else bmp_arr[bmp_arr_ix] = hbmpNodeBottomLast;
                     }
#endif
                     if(SUCCEEDED(retc))
                     {
                        if(bmp_arr_ix<KP_MAX_TREE_DEPTH-1) bmp_arr_ix++;
                        else
                           retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
                     }

//                   text_pos += KP_TREE_LBOX_TRCK_WDT;
                  }

// ----------------------- kiti tevu bruksniukai
//                if(SUCCEEDED(retc)) retc = cur_node->GetFather(&cur_father);
                  while(cur_father && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc = cur_father->GetFather(&new_father);
                     if(SUCCEEDED(retc)) if(cur_father == cur_wnd->m_pEntries) new_father = NULL;
// vyriausiam proseneliui pliusiuko nereikia
                     if(new_father && SUCCEEDED(retc))
                     {
                        next_brother = cur_father->m_pNextBrother;
                        if(next_brother)
                        {
                           brother_status = next_brother->m_iStatus;
                           if(cur_wnd->m_iWndType==TYP_ListBoxTree) brother_status = brother_status >> KpNodeLevelShift;
                           if((brother_status & KpNodeVisible) == 0) next_brother = NULL; // neuztenka - reikia, kad visi tolesni broliai butu nematomi (priklausytu kitam lygmeniui)
                        }

                        if(next_brother) bmp_arr[bmp_arr_ix] = hbmpNodeBypass;
                        else bmp_arr[bmp_arr_ix] = hbmpNodeBypassEmpty;

                        if(SUCCEEDED(retc))
                        {
                           if(bmp_arr_ix<KP_MAX_TREE_DEPTH-1) bmp_arr_ix++;
                           else
                              retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
                        }

//                      text_pos += KP_TREE_LBOX_TRCK_WDT;
                     }

                     if(SUCCEEDED(retc)) cur_father = new_father;
                  }

               } // if((cur_wnd->m_iWndType==TYP_ListBoxTree) || (cur_wnd->m_iWndType==TYP_ListBoxTreeInverted))

// ----------------------- parodom visas ikoneles
               if((cur_wnd->m_iWndType==TYP_ListBoxTree) || (cur_wnd->m_iWndType==TYP_ListBoxTreeInverted) || (cur_wnd->m_iWndType==TYP_ListBoxChk))
               {
                  hdc_mem = 0;
                  if(SUCCEEDED(retc))
                  {
                     hdc_mem = CreateCompatibleDC(lpdis->hDC);
                     if((hdc_mem==0) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }

                  trck_pos = 0; // KP_TREE_LBOX_MARGIN; // tarpelis jau bus is ikoneles
                  while((--bmp_arr_ix>=0) && SUCCEEDED(retc))
                  {
                     hbmp = bmp_arr[bmp_arr_ix];
                     if(hbmp == 0)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                     hbmp_old = 0;
                     if(SUCCEEDED(retc))
                     {
                        hbmp_old = SelectObject(hdc_mem, hbmp);
                        if(hbmp_old==NULL)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                     }

                     if(SUCCEEDED(retc))
                        if(!BitBlt(lpdis->hDC,
                              trck_pos + lpdis->rcItem.left, lpdis->rcItem.top,
                              lpdis->rcItem.right - lpdis->rcItem.left,
                              lpdis->rcItem.bottom - lpdis->rcItem.top,
                              hdc_mem, 0, 0, SRCCOPY))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

                     trck_pos += KP_TREE_LBOX_TRCK_WDT;

                     if(hdc_mem && hbmp_old) SelectObject(hdc_mem, hbmp_old);
                     hbmp_old = 0;

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "ODA_DRAWENTIRE: %ld %ld", GetCurrentProcessId(), GetCurrentThreadId());
KP_TRACE(str_buf);
#endif
                  } // while((--bmp_arr_ix>=0) && SUCCEEDED(retc))

               } // if((cur_wnd->m_iWndType==TYP_ListBoxTree) || (cur_wnd->m_iWndType==TYP_ListBoxTreeInverted))

            } // if((cur_node!=NULL) ...


// ---------------------- node text bitmap
            if(
               (cur_node!=NULL) &&
               (
                  ((status & KpNodeHasChildren) == 0) ||
                  ((status & KpNodeExpanded) == 0) ||
                  (cur_wnd->m_iWndType==TYP_ListBoxTree)
               ) &&
               SUCCEEDED(retc)
              )
               if(cur_node->m_iRecType == KpRecType_BmpBmp)
               {
                  bmp_bmp_value = (KpBmpBmp *)cur_node->GetValue();
                  if((bmp_bmp_value != NULL) && SUCCEEDED(retc))
                  {
                     KP_ASSERT(cur_node->GetValSize() >= sizeof(KpBmpBmp), KP_E_SYSTEM_ERROR, null, True);

                     if(SUCCEEDED(retc)) if(bmp_bmp_value->m_hTextBmp)
                     {
                        hbmp_old = 0;
                        if(SUCCEEDED(retc))
                        {
                           hbmp_old = SelectObject(hdc_mem, bmp_bmp_value->m_hTextBmp);
                           if(hbmp_old==NULL)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                        }

                        if(SUCCEEDED(retc))
                           if(!BitBlt(lpdis->hDC,
                              trck_pos + lpdis->rcItem.left, lpdis->rcItem.top,
                              lpdis->rcItem.right - lpdis->rcItem.left,
                              lpdis->rcItem.bottom - lpdis->rcItem.top,
                              hdc_mem, 0, 0, (lpdis->itemState & ODS_SELECTED)?NOTSRCCOPY:SRCCOPY))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

//                      trck_pos += 100;

                        if(hdc_mem && hbmp_old) SelectObject(hdc_mem, hbmp_old);
                        hbmp_old = 0;
                     }
                  }
               }


            if(hdc_mem) DeleteDC(hdc_mem); hdc_mem = 0;


// ---------------------- node text
unsigned char text_buf[KP_MAX_FILE_LIN_WDT+1];
TEXTMETRIC tm;
int yy;

            if((cur_node!=NULL) && SUCCEEDED(retc))
               if((cur_node->m_iRecType == KpRecType_Text) || (cur_node->m_iRecType == KpRecType_TextBmp) || (cur_node->m_iRecType == KpRecType_TextChk))
               {
                  text_buf[0] = Nul;
#if FALSE // #if TRUE
// TODO: LB_GETTEXTLEN
                  if(SUCCEEDED(retc))
                     if(SendMessage(lpdis->hwndItem, LB_GETTEXT, lpdis->itemID, (LPARAM)text_buf)==LB_ERR)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#else
                  strncpy(text_buf, (const char *)(cur_node->GetValue()), KP_MAX_FILE_LIN_WDT);
                  text_buf[KP_MAX_FILE_LIN_WDT] = Nul;
#endif

#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "WM_DRAWITEM %d %d %s", wParam, hwndDlg, text_buf);
KP_TRACE(str_buf);
#endif


                  if(SUCCEEDED(retc))
                     if(!GetTextMetrics(lpdis->hDC, &tm))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc))
                  {
//                   text_pos += KP_TREE_LBOX_MARGIN;
//                   trck_pos += KP_TREE_LBOX_MARGIN; // tarpelis jau bus is ikoneles
                     yy = (lpdis->rcItem.bottom + lpdis->rcItem.top - tm.tmHeight) / 2;

COLORREF prev_color;
COLORREF prev_back_color;

                     if(SUCCEEDED(retc)) if((lpdis->itemState & ODS_SELECTED) && (cur_wnd->m_iWndType != TYP_ListBoxChk))
                     {
                        prev_color = SetTextColor(lpdis->hDC, RGB_White);
                        if(prev_color == CLR_INVALID)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                        if(SUCCEEDED(retc))
                        {
                           prev_back_color = SetBkColor(lpdis->hDC, cur_node->m_iRecType == KpRecType_TextBmp?RGB(0, 0, 0x60):RGB_Darkblue);
                           if(prev_back_color == CLR_INVALID)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                        }
                     }

                     if(SUCCEEDED(retc))
                     {
int rest;
                        rest = cur_wnd->m_iWdtDots - trck_pos;
                        if(rest>0)
                        {
                           if(((cur_wnd->m_iKpCtrlStyle<0) || (cur_wnd->m_iKpCtrlStyle>=KPW_NUM_OF_CONTROL_STYLES_0)) && SUCCEEDED(retc))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                           if(SUCCEEDED(retc))
                           {
                              rest = rest * (((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?13:17 /* 15 */) /* 15 */ /* 10 */ /iaCtrlTextFactors[cur_wnd->m_iKpCtrlStyle]; // teksto pozijos nuo bitmapo iki listboxo krasto
                              ii = strlen(text_buf);
                              rest-=ii; // teksto pozicijos nuo teksto pabaigos iki listboxo krasto
                              if(rest>0)
                              {
                                 if((ii + rest) >= KP_MAX_FILE_LIN_WDT)
                                    retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
                                 if(SUCCEEDED(retc))
                                 {
                                    memset(text_buf+ii, Spc, rest);
                                    text_buf[ii+rest]=Nul;
                                 }
                              }
                           }
                        }

                        if(!TextOut(lpdis->hDC, trck_pos /* text_pos */, yy, (const char *)text_buf, strlen(text_buf)))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                     }

                     if(SUCCEEDED(retc)) if((lpdis->itemState & ODS_SELECTED) && (cur_wnd->m_iWndType != TYP_ListBoxChk))
                     {
                        if(SetTextColor(lpdis->hDC, prev_color) == CLR_INVALID)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                        if(SUCCEEDED(retc))
                        {
                           if(SetBkColor(lpdis->hDC, prev_back_color) == CLR_INVALID)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                        }
                     }
                  }

               } // if((cur_node->m_iRecType == KpRecType_Text) || (cur_node->m_iRecType == KpRecType_TextBmp))

            break;

         } // switch (lpdis->itemAction)

      } // if(lpdis->itemID != -1)

      break;


#if FALSE
// ------------------------ draw listbox item
   case WM_DRAWITEM:
LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;

// pries TextOut
            if(SUCCEEDED(retc))
            {
               if(lpdis->itemState & ODS_SELECTED)
               {
                  if(SetTextColor(lpdis->hDC, RGB_White) == CLR_INVALID)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                     if(SetBkColor(lpdis->hDC, RGB_Darkblue) == CLR_INVALID)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }
               else
               {
                  if(SetTextColor(lpdis->hDC, RGB_Black) == CLR_INVALID)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                     if(SetBkColor(lpdis->hDC, RGB_White) == CLR_INVALID)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }
            }

      break;

   case WM_COMPAREITEM:
KpMsgOut("WM_COMPAREITEM", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
      break;
#endif


   case LB_SETCURSEL:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      retw=wParam;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(cur_wnd->m_hSubListBox==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         if(lParam /* wParam */ ==(-1)) retc=SetListBoxSel(cur_wnd->m_hSubListBox, lParam); // wParam); //
         else
         {
//          retc=SetKpListBoxSel(cur_wnd, wParam, 1, False);
            retc=SetKpListBoxSel(cur_wnd, lParam, 1, False);
         }
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "LB_SETCURSEL %ld", lParam); // wParam);
KP_TRACE(str_buf);
#endif
      }
//    if(SUCCEEDED(retc)) retc=cur_wnd->SetCurScrolPos();

      if(FAILED(retc)) retw=LB_ERR;
      break;

// case LB_GETTEXT:
   case KP_LB_GETTEXT:
      retw=FALSE;

      if((lParam == 0L) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(cur_wnd->m_hSubListBox==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         if(cur_wnd->m_iCurStartEntry < 0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, True, __FILE__, __LINE__, 0L, NULL);
         else
         {
#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "lParam: %x", lParam);
KP_TRACE(str_buf);
#endif

#if FALSE // reikia su technine priesaga, hSubListBox-e jau nuk?sta
            retw=SendMessage(cur_wnd->m_hSubListBox, LB_GETTEXT /* uMsg */, wParam - cur_wnd->m_iCurStartEntry, lParam);
            if(retw==LB_ERR)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#  if FALSE // #ifdef Debug
            else
            {
int ii;
char str_buf[100];
str_buf[0]=Nul;
for(ii=0; ii<retw; ii++)
   sprintf(str_buf+ii*2, "%02x", ((const char *)lParam)[ii]);
str_buf[ii*2]=Nul;
KP_TRACE((const char *)lParam);
KP_TRACE(str_buf);
            }
#  endif
#endif

#if FALSE // naudoti m_iCurSel // reikia ne aktyvaus ?ra?o, o wParam
int ii = 0;
            if(SUCCEEDED(retc))
            {
               ii=SendMessage(cur_wnd->m_hSubListBox, LB_GETCURSEL, 0, 0L);
               if(ii==LB_ERR)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc)) if((ii < 0) || (cur_wnd->m_iCurStartEntry + ii >= cur_wnd->m_iListEntriesCount))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) if(cur_wnd->m_plpszListEntries == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) if(cur_wnd->m_plpszListEntries[cur_wnd->m_iCurStartEntry + ii] == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               strcpy((unsigned char *)lParam, cur_wnd->m_plpszListEntries[cur_wnd->m_iCurStartEntry + ii]);
               retw = strlen((unsigned char *)lParam); // cur_wnd->m_plpszListEntries[cur_wnd->m_iCurStartEntry + ii]);
            }
#endif

#if FALSE // reikia ne aktyvaus ?ra?o, o wParam
            if(SUCCEEDED(retc))
            {
               if(cur_wnd->m_iCurSel < 0)
               {
                  ((unsigned char *)lParam)[0] = Nul;
                  retw = LB_ERR;
               }
               else
               {
                  if(SUCCEEDED(retc)) if(cur_wnd->m_iCurSel >= cur_wnd->m_iListEntriesCount)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc)) if(cur_wnd->m_plpszListEntries == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc)) if(cur_wnd->m_plpszListEntries[cur_wnd->m_iCurSel] == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                  {
                     strcpy((unsigned char *)lParam, cur_wnd->m_plpszListEntries[cur_wnd->m_iCurSel]);
                     retw = strlen((unsigned char *)lParam); // cur_wnd->m_plpszListEntries[cur_wnd->m_iCurSel]);
                  }
               }
            }
#endif

            if(SUCCEEDED(retc)) if(/* (wParam < 0) || */ (wParam >= cur_wnd->m_iListEntriesCount))
               retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) if(cur_wnd->m_plpszListEntries == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) if(cur_wnd->m_plpszListEntries[wParam] == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               strcpy((unsigned char *)lParam, cur_wnd->m_plpszListEntries[wParam]);
               retw = strlen((unsigned char *)lParam); // cur_wnd->m_plpszListEntries[wParam]);
            }

         }
      }

      if(FAILED(retc)) retw=LB_ERR;
      break;

   case LB_GETCOUNT:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      retw=LB_ERR;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) retw = cur_wnd->m_iListEntriesCount;


      if(FAILED(retc) && (retw>=0)) retw=LB_ERR;

      break;

   case LB_GETCURSEL:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      retw=LB_ERR;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(cur_wnd->m_hSubListBox==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         if(cur_wnd->m_iCurStartEntry < 0)
         {
            retw=LB_ERR;
            retc=KpErrorProc.OutputErrorMessage(KP_E_ILLFUNC, null, True, __FILE__, __LINE__, 0L, NULL);
         }
         else
         {
            retw=SendMessage(cur_wnd->m_hSubListBox, uMsg, wParam, lParam);
            if(retw==LB_ERR)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               retw+=cur_wnd->m_iCurStartEntry;
#ifdef Debug
               if(cur_wnd->m_iCurSel!=retw)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
#endif
            }
         }
      }

      if(FAILED(retc) && (retw>=0)) retw=LB_ERR;

      break;

// case WM_KEYDOWN:
// case WM_CHAR:
//    retw=0;
//    break;


   case WM_VSCROLL:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if((cur_wnd==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) if((HWND)lParam==cur_wnd->m_hSubLBoxScrollBar)
      {
         new_pos = cur_wnd->m_iCurSel;
         direction = (-1);

         switch(LOWORD(wParam))
         {
         case SB_PAGEDOWN:
            new_pos+=cur_wnd->m_iNumOfRows-1;
            if(new_pos>=cur_wnd->m_iListEntriesCount)
               new_pos=cur_wnd->m_iListEntriesCount-1;
            direction=2;
            break;
         case SB_PAGEUP:
            new_pos-=cur_wnd->m_iNumOfRows-1;
            if(new_pos<0) new_pos=0;
            direction=0;
            break;
         case SB_LINEDOWN:
            new_pos++;
            if(new_pos>=cur_wnd->m_iListEntriesCount)
               new_pos=cur_wnd->m_iListEntriesCount-1;
            direction=1;
            break;
         case SB_LINEUP:
            new_pos--;
            if(new_pos<0) new_pos=0;
            direction=1;
            break;
         case SB_THUMBPOSITION:
         case SB_THUMBTRACK:
#if FALSE
            new_pos=(int) HIWORD(wParam);
#else
SCROLLINFO scroll_info; // ={0};

            scroll_info.cbSize = sizeof(scroll_info);
            scroll_info.fMask = SIF_ALL; // SIF_POS|SIF_RANGE;

            if(!GetScrollInfo(cur_wnd->m_hSubLBoxScrollBar, SB_CTL, &scroll_info))
            {
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               new_pos = 0;
            }
            else new_pos = scroll_info.nTrackPos; // scroll_info.nPos;
#endif
            if(new_pos>=cur_wnd->m_iListEntriesCount)
               new_pos=cur_wnd->m_iListEntriesCount-1;
            direction=1;


#if FALSE // #ifdef Debug
char str_buf[100];
sprintf(str_buf, "SB_THUMBTRACK %d", new_pos);
KP_TRACE(str_buf);
#endif
            break;
         default:
            break;
         }

         if(SUCCEEDED(retc) && (direction>=0))
         {
            if(SUCCEEDED(retc)) retc=SetKpListBoxSel(cur_wnd, new_pos, direction, False);
//          if(SUCCEEDED(retc)) retc=cur_wnd->SetCurScrolPos();

// ---------------------------- perduot notifikacija tevui
            if(SUCCEEDED(retc))
               if(cur_wnd->m_hParent==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
//             HIWORD(w_par)=LBN_SELCHANGE;
//             LOWORD(w_par)=0; // list box identifier ??? !!!
               w_par=(LBN_SELCHANGE<<16) | 0;
               retw=SendMessage(cur_wnd->m_hParent, WM_COMMAND, w_par, (LPARAM)cur_wnd->m_hWndHandle);
            }

         } // if(SUCCEEDED(retc) && (direction>=0))

      } // if(SUCCEEDED(retc)) if((HWND)lParam==cur_wnd->m_hSubLBoxScrollBar)

      break;

// --------------------------
   case WM_CHAR:
   case WM_KEYDOWN:
   case WM_KEYUP:
// KP_TRACE_2("KpListBoxDialogProc(): %s: hwndDlg:%lx",
//   (uMsg==WM_KEYDOWN)?"WM_KEYDOWN":((uMsg==WM_KEYUP)?"WM_KEYUP":"WM_CHAR"), hwndDlg);
   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   } // switch(uMsg)

//    if((cur_wnd!=NULL) && SUCCEEDED(retc))
//       if(cur_wnd->m_hSubListBox!=NULL)
//          SendMessage(cur_wnd->m_hSubListBox, uMsg, wParam, lParam);

// --------------------------
   if(endfl)
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if((endfl || FAILED(retc)) && (cur_wnd!=NULL))
   {
      retc0=DeleteWnd(cur_wnd);
      if(SUCCEEDED(retc)) retc=retc0;

//    KP_DELETE(cur_wnd);
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


// ----------------------
HRESULT KpCreateComboBox(HINSTANCE /* hInst */, HWND hParent, HWND *phBoxControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, KpTreeEntry *pEntries, int iInitSel)
{
HRESULT retc=S_OK;
HWND box_field=NULL;
KpTreeEntry *cur_entry;
KpTreeEntry *next_entry;
LRESULT retv;
const unsigned char *cur_str;
// RECT box_rect;

   if(((iKpCtrlStyle<0) || (iKpCtrlStyle>=KPW_NUM_OF_CONTROL_STYLES_0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      box_field=CreateWindowEx(dwExStyle|WS_EX_TRANSPARENT/*|WS_EX_CLIENTEDGE|ES_SUNKEN*/,
                  "COMBOBOX",
                  (LPCTSTR)lpszText,
                  dwStyle|WS_VISIBLE|WS_CHILD|DS_SETFONT|CBS_DROPDOWN|CBS_HASSTRINGS/*|CBS_DISABLENOSCROLL*/|WS_VSCROLL, // |CBS_NOTIFY ??? |CBS_SIMPLE |CBS_DROPDOWNLIST |ES_MULTILINE|LBS_NOTIFY|WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  iPosX+1, iPosY, iWdt-2, iHgt, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!box_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) retc=SetCtrlFont(box_field, iKpCtrlStyle);

   if((phBoxControl!=NULL) && SUCCEEDED(retc)) *phBoxControl=box_field;

#if FALSE // #if TRUE //
unsigned char str_buf[100];
sprintf((char *)str_buf, "box_field: %lx", box_field);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

// set box entries
#if FALSE
   if(SUCCEEDED(retc))
   {
      retv=SendMessage(box_field, KP_LB_SETSTRINGLIST, 0, (LPARAM)pEntries);
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
#else
   if(SUCCEEDED(retc)) cur_entry = /* cur_wnd->m_pEntries = */ pEntries;
   while(cur_entry && SUCCEEDED(retc))
   {
      cur_str = (const unsigned char *)cur_entry->GetValue();
      if(cur_str != null)
      {
         retv = SendMessage(box_field, CB_ADDSTRING, 0, (LPARAM)cur_str);
         switch(retv)
         {
         case CB_ERR:
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            break;
         case CB_ERRSPACE:
            retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
            break;
         }
      }

//    if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild(&next_entry);
      if(SUCCEEDED(retc)) next_entry = cur_entry->m_pFirstChild;

      if(SUCCEEDED(retc)) cur_entry = next_entry;
   }
#endif

#if FALSE
// set count of visible entries
   if(SUCCEEDED(retc))
      if(!SendMessage(box_field, CB_SETMINVISIBLE, 8, 0L))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!SendMessage(box_field, CB_SHOWDROPDOWN, True, 0L))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      box_rect.left=100;
      box_rect.top=150;
      box_rect.right=200;
      box_rect.bottom=200;

      if(!SendMessage(box_field, CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&box_rect))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
#endif

   if(SUCCEEDED(retc)) retc=SetComboBoxSel(box_field, iInitSel);

return(retc);
}


// ----------------------
HRESULT KpCreateListComboBox(HINSTANCE /* hInst */, HWND hParent, HWND *phListBoxControl, HWND *phBoxBkgdControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, KpTreeEntry *pEntries, WNDPROC lpfnBoxBkgdProc, int iInitSel)
{
HRESULT retc=S_OK;
HWND box_field=NULL;
HWND background_wnd=NULL;
KpTreeEntry *cur_entry;
KpTreeEntry *next_entry;
LRESULT retv;
const unsigned char *cur_str;
// RECT box_rect;
RECT par_rect;
WNDCLASSEX wcx;
// WINDOWINFO win_info;
HBRUSH brush = NULL;


   if(((iKpCtrlStyle<0) || (iKpCtrlStyle>=KPW_NUM_OF_CONTROL_STYLES_0) || (hKpInstance==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// ------------------------------
// if(SUCCEEDED(retc))
//    if(!GetWindowInfo(hParent, &win_info))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!GetWindowRect(hParent, &par_rect))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// -----------------------------
   brush = NULL;

#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#else

   brush = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));
#endif

// ------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "LBOXBKGD",
      wcx.lpfnWndProc   = lpfnBoxBkgdProc; // (WNDPROC)ListComboBoxBkgdProc; //
      wcx.style         = 0;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
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

// -----------------------------------
   if(SUCCEEDED(retc))
   {
      background_wnd=CreateWindowEx
         (
            dwExStyle,  // WS_EX_TOPMOST|ES_SUNKEN|WS_EX_CLIENTEDGE   // DWORD dwExStyle,      // extended window style
            "LBOXBKGD",
            "", // LPCTSTR lpWindowName, // pointer to window name
            dwStyle|WS_VISIBLE|WS_POPUP|WS_BORDER, // WS_CHILD|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CAPTION|WS_THICKFRAME, // WS_POPUPWINDOW, // DWORD dwStyle,        // window style
            par_rect.left+iPosX+1, // par_rect.left+iPosX+1, // iPosX+1, // CW_USEDEFAULT,          // int x,                // horizontal position of window
            par_rect.top+iPosY, // par_rect.top+iPosY, // iPosY, // CW_USEDEFAULT,          // int y,                // vertical position of window
            iWdt-2+2, // iWdt-2, // int nWidth, // window width
            iHgt+2, // iHgt, // int nHeight,    // window height
            hParent, // HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
            0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            0                       // LPVOID lpParam        // pointer to window-creation data
         );

      if(background_wnd==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phBoxBkgdControl!=NULL) && SUCCEEDED(retc)) *phBoxBkgdControl=background_wnd;

// KpSleep(1000, HWND_DESKTOP); // Sleep(1000);

//  if(SUCCEEDED(retc))
//    if(!SetWindowPos(background_wnd, HWND_TOP, iPosX+1, iPosY, iWdt-2, iHgt, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// KpSleep(1000, HWND_DESKTOP); // Sleep(1000);

// -------------------------
   if(SUCCEEDED(retc))
   {
      box_field=CreateWindowEx(dwExStyle, // |WS_EX_TOPMOST|WS_EX_TRANSPARENT|ES_SUNKEN|WS_EX_CLIENTEDGE
                  "LISTBOX",
                  (LPCTSTR)lpszText,
                  dwStyle|WS_CHILD|WS_VISIBLE|DS_SETFONT|LBS_HASSTRINGS|LBS_DISABLENOSCROLL|LBS_NOTIFY|WS_VSCROLL, // |WS_POPUP|CBS_DROPDOWN|CBS_SIMPLE |CBS_DROPDOWNLIST |ES_MULTILINE|WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  0, // 1, // par_rect.left+iPosX+1, // iPosX+1, // win_info.rcWindow.left+iPosX+1, //
                  0, // 1, // par_rect.top+iPosY, // iPosY, // win_info.rcWindow.top+iPosY, //
                  iWdt-2,
                  iHgt,
                  background_wnd, // hParent, // NULL, // HWND_DESKTOP, //
                  0,
                  GetModuleHandle(NULL), 0);
      if(!box_field)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phListBoxControl!=NULL) && SUCCEEDED(retc)) *phListBoxControl=box_field;

   if(SUCCEEDED(retc)) retc=SetCtrlFont(box_field, iKpCtrlStyle);

// set box entries
#if FALSE
   if(SUCCEEDED(retc))
   {
      retv=SendMessage(box_field, KP_LB_SETSTRINGLIST, 0, (LPARAM)pEntries);
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
#else
   if(SUCCEEDED(retc)) cur_entry = /* cur_wnd->m_pEntries = */ pEntries;
   while(cur_entry && SUCCEEDED(retc))
   {
      cur_str = (const unsigned char *)cur_entry->GetValue();
      if(cur_str != null)
      {
         retv = SendMessage(box_field, LB_ADDSTRING, 0, (LPARAM)cur_str);
         switch(retv)
         {
         case CB_ERR:
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            break;
         case CB_ERRSPACE:
            retc = KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
            break;
         }
      }

//    if(SUCCEEDED(retc)) retc = cur_entry->GetFirstChild(&next_entry);
      if(SUCCEEDED(retc)) next_entry = cur_entry->m_pFirstChild;

      if(SUCCEEDED(retc)) cur_entry = next_entry;
   }
#endif

   if(SUCCEEDED(retc)) retc=SetListBoxSel(box_field, iInitSel);

// -----------------------

// KpSleep(1000, HWND_DESKTOP); // Sleep(1000);

// if(SUCCEEDED(retc))
//    if(!InvalidateRect(background_wnd /* box_field */, NULL, True))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

//  if(SUCCEEDED(retc))
//    if(!SetWindowPos(box_field, HWND_TOP, iPosX+1, iPosY, iWdt-2, iHgt, 0 /* SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW */))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// KpSleep(1000, HWND_DESKTOP); // Sleep(1000);

// if(SUCCEEDED(retc))
//    if(!SetWindowPos(box_field, HWND_TOP, 1, 1, iWdt-2-1, iHgt-1, 0 /* SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW */))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// if(SUCCEEDED(retc)) SetActiveWindow(box_field);

// if(SUCCEEDED(retc)) ShowWindow(box_field, SW_SHOWNORMAL);

// KpSleep(1000, HWND_DESKTOP); // Sleep(1000);

// if(SUCCEEDED(retc)) SendMessage(background_wnd /* box_field */, WM_PAINT, 0, 0L);

return(retc);
}


// ----------------------
HRESULT SetComboBoxSel(HWND hBoxControl, int iInitSel)
{
HRESULT retc=S_OK;

   if((SendMessage(hBoxControl, CB_SETCURSEL,   iInitSel, 0L)==CB_ERR) && (iInitSel!=(-1)))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

return(retc);
}


// ----------------------
HRESULT SetListBoxSel(HWND hBoxControl, int iInitSel)
{
HRESULT retc=S_OK;
int retv;
KpWnd *cur_wnd = NULL;

   if(SUCCEEDED(retc)) retv=SendMessage(hBoxControl, LB_SETCURSEL, iInitSel, iInitSel); // lParam reikia KpListBox Win98 - kai iInitSel > 32767
   if((retv==CB_ERR) && (iInitSel!=(-1)) && SUCCEEDED(retc))
   {
      if(iInitSel==0)
      {
//       if(SUCCEEDED(retc)) retc=GetCurWindow(&cur_wnd, hBoxControl);
//       if((cur_wnd==NULL) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//       if(SUCCEEDED(retc)) if(cur_wnd->m_iListEntriesCount>0)
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) retv=SendMessage(hBoxControl, LB_GETCOUNT, 0, 0L);
         if((retv>0) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      else
      {
#if FALSE
unsigned char str_buf[200];
retv=SendMessage(hBoxControl, LB_GETCOUNT, 0, 0L);
KpWnd *kp_wnd = NULL;
GetCurWindow(&kp_wnd, theDialog.m_MainList);
sprintf((char *)str_buf, "%lx %lx %0x %d %lx %d]", hBoxControl, theDialog.m_MainList, iInitSel, retv, kp_wnd, SetKpListBoxSel_n);
retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, False, __FILE__, __LINE__, 0L, NULL);
#endif
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}


// ----------------------
HRESULT SetKpListBoxSel(KpWnd *pKpBoxControl, long lSelPos, int iDirection, bool bForced)
{
HRESULT retc=S_OK;
int ii;
int new_start_entry;
int retv;
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char *pntd = NULL;

   if((pKpBoxControl==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

// --------------------
   if(SUCCEEDED(retc)) if((lSelPos!=pKpBoxControl->m_iCurSel) || bForced)
   {
      pKpBoxControl->m_iCurSel=lSelPos;

      new_start_entry=pKpBoxControl->m_iCurSel - (2+iDirection) * pKpBoxControl->m_iNumOfRows / 2 + iDirection/2;
      if(new_start_entry + 3 * pKpBoxControl->m_iNumOfRows > pKpBoxControl->m_iListEntriesCount)
         new_start_entry = pKpBoxControl->m_iListEntriesCount - 3 * pKpBoxControl->m_iNumOfRows;
      if(new_start_entry<0) new_start_entry=0;

      if((new_start_entry != pKpBoxControl->m_iCurStartEntry) || bForced)
      {
         if((pKpBoxControl->m_plpszListEntries == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
         {
            pKpBoxControl->m_iCurStartEntry = new_start_entry;

            SendMessage(pKpBoxControl->m_hSubListBox, LB_RESETCONTENT, 0, 0L);

            for(ii=0; (ii < 3 * pKpBoxControl->m_iNumOfRows) && SUCCEEDED(retc); ii++)
            {
               if(pKpBoxControl->m_iCurStartEntry+ii < pKpBoxControl->m_iListEntriesCount)
               {
                  if(pKpBoxControl->m_plpszListEntries[pKpBoxControl->m_iCurStartEntry+ii] == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc))
                     if(strlen(pKpBoxControl->m_plpszListEntries[pKpBoxControl->m_iCurStartEntry+ii]) >= KP_MAX_FILE_LIN_WDT)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL);

// ------------ nukandam technin_ ?ra?o dal?
                  if(SUCCEEDED(retc))
                  {
                     strncpy(str_buf, pKpBoxControl->m_plpszListEntries[pKpBoxControl->m_iCurStartEntry+ii], KP_MAX_FILE_LIN_WDT);
                     str_buf[KP_MAX_FILE_LIN_WDT] = Nul;

                     pntd = strchr(str_buf, TECH_DELIM_CHR);
                     if(pntd) *pntd = Nul;
                  }

                  if(SUCCEEDED(retc))
                  {
                     retv=SendMessage(pKpBoxControl->m_hSubListBox, LB_ADDSTRING, 0, (LPARAM)str_buf);
                     if((retv==LB_ERR) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                     if((retv==LB_ERRSPACE) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
               }
            }
         }

      } // if(new_start_entry != pKpBoxControl->m_iCurStartEntry)
      else
         retc=SetListBoxSel(pKpBoxControl->m_hSubListBox, 0);


// -------------------------
#if TRUE // #if FALSE //
#ifdef Debug
// unsigned char *str_buf[100];
#endif

      if(SUCCEEDED(retc))
      {
#ifdef Debug
// if(pKpBoxControl->m_iListEntriesCount>100) KP_TRACE("LB_SETCURSEL");
#endif

//       ii=pKpBoxControl->m_iCurStartEntry + 2*pKpBoxControl->m_iNumOfRows-1;
         ii=pKpBoxControl->m_iCurSel + (2-iDirection) * pKpBoxControl->m_iNumOfRows / 2 - 1;

#if FALSE // #ifdef Debug //
sprintf((char *)str_buf, "ii: %d  m_iCurStartEntry: %d", ii, pKpBoxControl->m_iCurStartEntry);
if(pKpBoxControl->m_iListEntriesCount>100) KP_TRACE((const char *)str_buf);
#endif
         if(ii>=pKpBoxControl->m_iListEntriesCount) ii=pKpBoxControl->m_iListEntriesCount-1;

#if FALSE // #ifdef Debug //
sprintf((char *)str_buf, "ii: %d  m_iListEntriesCount: %d", ii, pKpBoxControl->m_iListEntriesCount);
if(pKpBoxControl->m_iListEntriesCount>100) KP_TRACE((const char *)str_buf);
#endif
      }

      if(SUCCEEDED(retc))
      {
#if FALSE
if(ii - pKpBoxControl->m_iCurStartEntry < 0)
{
char str_buf[200];
sprintf(str_buf, "---> %d %d %lx", pKpBoxControl->m_iCurSel, pKpBoxControl->m_iCurStartEntry, pKpBoxControl);
KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, str_buf, False, __FILE__, __LINE__, 0L, NULL);
}
#endif
         retc=SetListBoxSel(pKpBoxControl->m_hSubListBox, ii - pKpBoxControl->m_iCurStartEntry);

#if FALSE // #ifdef Debug //
sprintf((char *)str_buf, "ii-m_iCurStartEntry: %d  3*m_iNumOfRows: %d", ii-pKpBoxControl->m_iCurStartEntry, 3*pKpBoxControl->m_iNumOfRows);
if(pKpBoxControl->m_iListEntriesCount>100) KP_TRACE((const char *)str_buf);
#endif
      }

#ifdef Debug
// KpSleep(300, HWND_DESKTOP); // Sleep(300);
#endif

#endif

      if(SUCCEEDED(retc))
      {
         retc=SetListBoxSel(pKpBoxControl->m_hSubListBox, pKpBoxControl->m_iCurSel-pKpBoxControl->m_iCurStartEntry);
#if FALSE // #ifdef Debug //
sprintf((char *)str_buf, "m_iCurSel: %d  m_iCurSel-m_iCurStartEntry: %d", pKpBoxControl->m_iCurSel, pKpBoxControl->m_iCurSel-pKpBoxControl->m_iCurStartEntry);
if(pKpBoxControl->m_iListEntriesCount>100) KP_TRACE((char *)str_buf);
#endif
      }

// ------------------------------
      if(SUCCEEDED(retc)) retc=pKpBoxControl->SetCurScrolPos();

   } // if(iSelPos != pKpBoxControl->m_iCurSel)

return(retc);
}


// ----------------------
HRESULT FormatListString(unsigned char *lpszOutStr,
                         const unsigned char *lpszInStr1, const unsigned char *lpszInStr2,
                         int iInStr1MaxLen, int iMaxAllign,
                         KpControlStyles iKpCtrlStyle) //  HDC hDc) //
{
HRESULT retc=S_OK;
int text_wdt;
int sp_wdt;
int num_sp;
int max_wdt;
int cur_wdt;
int rest_wdt;
int ii;

   if((lpszOutStr==NULL) || (lpszInStr1==NULL) || (lpszInStr2==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      strcpy(lpszOutStr, lpszInStr1);

   if(SUCCEEDED(retc))
   {
//    retc=GetStrWidth((const unsigned char *)"   ", &sp_wdt, hDc);
//    retc=GetStrWidthABC((const unsigned char *)" ", &sp_wdt, hDc);
      retc=GetStrWidthKp((const unsigned char *)" ", &sp_wdt, iKpCtrlStyle);
   }

#if TRUE // FALSE //

   if(SUCCEEDED(retc))
   {
//    retc=GetStrWidth(lpszOutStr, &text_wdt, hDc);
//    retc=GetStrWidthABC(lpszOutStr, &text_wdt, hDc);
      retc=GetStrWidthKp(lpszOutStr, &text_wdt, iKpCtrlStyle);
   }
   if(SUCCEEDED(retc))
   {
      cur_wdt=strlen(lpszOutStr);
      max_wdt=(sp_wdt*(iInStr1MaxLen+iMaxAllign/2)); // /3;
      rest_wdt=max_wdt-text_wdt;
      num_sp=0;
      if(sp_wdt!=0) num_sp=(rest_wdt+(sp_wdt/2))/sp_wdt; // (rest_wdt*3+(sp_wdt/2))/sp_wdt; //
      if(cur_wdt+num_sp>iInStr1MaxLen+iMaxAllign)
         num_sp=iInStr1MaxLen+iMaxAllign-cur_wdt;

#if FALSE
char str_buf[100];
sprintf(str_buf, ">>>%s<<< text_wdt: %d, sp_wdt: %d, max_wdt: %d, rest_wdt: %d, num_sp: %d", text_wdt, sp_wdt, max_wdt, rest_wdt, num_sp);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

   }

   for(ii=0; ii<num_sp; ii++) strcat(lpszOutStr, " ");

#else
   if(SUCCEEDED(retc)) do
   {
      strcat(lpszOutStr, " ");
//    retc=GetStrWidth(lpszOutStr, &text_wdt, hDc);
//    retc=GetStrWidthABC(lpszOutStr, &text_wdt, hDc);
      retc=GetStrWidthKp(lpszOutStr, &text_wdt, iKpCtrlStyle);

   } while(
            (strlen(lpszOutStr)<iInStr1MaxLen+iMaxAllign) &&
            (text_wdt+sp_wdt/2<sp_wdt*iMaxAllign) &&
            SUCCEEDED(retc)
          );
#endif

   if(SUCCEEDED(retc))
   {
//    strcat(lpszOutStr, "   ");
      strcat(lpszOutStr, lpszInStr2);
   }

return(retc);
}


// ==========================
HRESULT KpCreateBitmap(HINSTANCE /* hInst */, HWND hParent, HWND *phBitmapCtrl, HBITMAP hBitMap, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle)
{
HRESULT retc=S_OK;
HWND bitmap_control=NULL;
unsigned char bitmap_name[200];
KpWnd *kp_wnd = NULL;

// if(/* (hInst==NULL) || */ (hBitMap==NULL))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)bitmap_name, "KP_BITMAP_%d", hBitMap);

      bitmap_control=CreateWindowEx(dwExStyle, "STATIC", (LPCTSTR)bitmap_name,
                  WS_VISIBLE|WS_CHILD|SS_BITMAP, // |SS_CENTERIMAGE,
                  iPosX, iPosY, iWdtX, iWdtY, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(bitmap_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(/* (hBitMap!=NULL) && */ SUCCEEDED(retc))
      SendMessage(bitmap_control, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitMap);

   if((phBitmapCtrl!=NULL) && SUCCEEDED(retc)) *phBitmapCtrl=bitmap_control;

// if(SUCCEEDED(retc)) if(!SetWindowLong(bitmap_control, GWL_EXSTYLE, dwExStyle/*WS_EX_TRANSPARENT*/))
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// registruojam, kad kai nereik?s, sunaikint¸ bitmap?
   KP_NEWO(kp_wnd, KpWnd(bitmap_control, TYP_KpBitmapCtrl, null, hParent, hKpInstance, NULL, NULL,
                                       KPW_CONTROL_STYLE_NORMAL, iWdtX, iWdtY, 1, 1, 0, 0, NULL,
                                       NULL, hBitMap));
   if(SUCCEEDED(retc))
   {
      retc = WndPreg(kp_wnd, TYP_KpBitmapCtrl, hKpInstance, NULL, False);
      if(SUCCEEDED(retc)) kp_wnd = NULL;
   }

return(retc);
}


HRESULT KpCreateBitmap(HINSTANCE hInst, HWND hParent, HWND *phBitmapCtrl, int iBitmapId, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle)
{
HRESULT retc=S_OK;
HBITMAP bitmap=NULL;

   if(hInst==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if((iBitmapId!=0) && SUCCEEDED(retc))
   {
      bitmap=LoadBitmap(hInst, (LPCTSTR)iBitmapId);
      KP_ASSERT(bitmap != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
      if(FAILED(retc)) PutLogMessage_("KpCreateBitmap() %d", iBitmapId);
   }

   if(SUCCEEDED(retc))
      retc=KpCreateBitmap(hInst, hParent, phBitmapCtrl, bitmap, iPosX, iPosY, iWdtX, iWdtY, dwExStyle);

return(retc);
}


// ==========================
HRESULT KpCreateIcon(HINSTANCE hInst, HWND hParent, HWND *phIconCtrl, HICON hIcon, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle)
{
HRESULT retc=S_OK;
HWND icon_control=NULL;
unsigned char icon_name[200];
// DWORD cur_style;
WNDCLASSEX wcx;
KpWnd *wnd_ptr=NULL;
DWORD ex_style=0L;
DWORD style=0L;

   if(SUCCEEDED(retc))
      sprintf((char *)icon_name, "KPW_ICON_%d", hIcon);

// if(/* (hInst==NULL) || */ (hIcon==NULL))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

#if FALSE // #if TRUE //
   if(SUCCEEDED(retc))
   {
      ex_style=dwExStyle|WS_EX_TRANSPARENT;
      style=WS_VISIBLE|WS_CHILD|SS_ICON; // |SS_BITMAP|SS_CENTERIMAGE

      icon_control=CreateWindowEx(ex_style, "STATIC", (LPCTSTR)icon_name, style,
                  iPosX, iPosY, iWdtX, iWdtY, hParent, 0,
                  GetModuleHandle(NULL), 0);

      if(icon_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(/* (hIcon!=NULL) && */ SUCCEEDED(retc))
      SendMessage(icon_control, STM_SETIMAGE /* BM_SETIMAGE */, IMAGE_ICON, (LPARAM)hIcon);

#endif

#if FALSE // #if TRUE //
   if(SUCCEEDED(retc))
   {
      ex_style=dwExStyle;

//    style=WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON|WS_TABSTOP|BS_ICON; // |BS_BITMAP|WS_BORDER,
//    style=WS_CHILD|WS_VISIBLE|BS_BITMAP;
      style=WS_CHILD|WS_VISIBLE|BS_ICON|BS_FLAT; // |WS_DISABLED

      icon_control=CreateWindowEx(ex_style, "BUTTON", (LPCTSTR)icon_name, style,
                  iPosX, iPosY, iWdtX, iWdtY, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(icon_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

#if FALSE
   if(SUCCEEDED(retc))
   {
      cur_style=GetWindowLong(icon_control, GWL_STYLE);
      if(cur_style==0L)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }
   if(SUCCEEDED(retc))
      if(SetWindowLong(icon_control, GWL_STYLE, cur_style&(~WS_TABSTOP)&(~WS_BORDER )&(~WS_THICKFRAME))==0L)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif

#if FALSE
   if(SUCCEEDED(retc))
   {
      cur_style=GetWindowLong(icon_control, GWL_EXSTYLE);
//    if(cur_style==0L)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }
   if(SUCCEEDED(retc))
      if(SetWindowLong(icon_control, GWL_EXSTYLE, cur_style&(~BS_DEFPUSHBUTTON))==0L)
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
      }
#endif

   if(SUCCEEDED(retc))
      SendMessage(icon_control, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);

#endif


#if TRUE // #if FALSE //
// -----------------------------
#  if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#  endif

// ------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hInst;
      wcx.lpszClassName = "KPICON",
      wcx.lpfnWndProc   = (WNDPROC)KpIconDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hIconSm       = LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // brush; // (HBRUSH)iaColorMap[KpShadowNorm];

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL, False);
      }
   }

   if(SUCCEEDED(retc))
   {
      ex_style=dwExStyle;
      style=WS_VISIBLE|WS_CHILD;

      icon_control=CreateWindowEx(dwExStyle, "KPICON", (LPCTSTR)icon_name, style,
                  iPosX, iPosY, iWdtX, iWdtY, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!icon_control)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }
#endif

   if(SUCCEEDED(retc))
   {
      KP_NEWO(wnd_ptr, KpWnd(icon_control, TYP_Static, icon_name, hParent, hInst, NULL, hIcon, KPW_CONTROL_STYLE_NORMAL,
         iWdtX, iWdtY, 1, 1, ex_style, style, NULL));
      if(FAILED(retc)) KP_DELETE(wnd_ptr);
   }
   if(SUCCEEDED(retc)) retc = WndPreg(wnd_ptr, TYP_Static, hInst, NULL, False);


   if((phIconCtrl!=NULL) && SUCCEEDED(retc)) *phIconCtrl=icon_control;

return(retc);
}

HRESULT KpCreateIcon(HINSTANCE hInst, HWND hParent, HWND *phIconCtrl, int iIconId, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle)
{
HRESULT retc=S_OK;
HICON icon = NULL;

   KP_ASSERT(hInst, E_INVALIDARG, null, True);
   KP_ASSERT(iIconId,  E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
//    icon = LoadIcon(hInst, MAKEINTRESOURCE(iIconId));
      icon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(iIconId), IMAGE_ICON, iWdtX, iWdtY, 0);

      KP_ASSERT(icon, KP_E_SYSTEM_ERROR, GetLastError(), True);
      if(FAILED(retc)) PutLogMessage_("%d", iIconId);
   }

   if(SUCCEEDED(retc))
      retc = KpCreateIcon(hInst, hParent, phIconCtrl, icon, iPosX, iPosY, iWdtX, iWdtY, dwExStyle);

return(retc);
}


// -----------------------------------------
BOOL CALLBACK KpIconDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
BOOL retw=FALSE;
int retp;
bool endfl=FALSE;
HDC hdc=NULL;
PAINTSTRUCT ps;
RECT rect;
KpWnd *cur_wnd=NULL;
// HWND prew_mouse_over=NULL;

   retp=LOWORD(wParam);

   switch(uMsg)
   {
   case WM_CREATE:
   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if(cur_wnd!=NULL)
      {
         if(GetUpdateRect(hwndDlg, &rect, FALSE))
         {
//          hdc=GetDC(hwndDlg);
            hdc=BeginPaint(hwndDlg, &ps);
            if(hdc==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
            if(SUCCEEDED(retc))
            {
//             if(SetTextColor(hdc, 0)==CLR_INVALID)
//             if(SetBkColor(hdc, 0x0000ff /* 0x00bbggrr  */)==CLR_INVALID)
               if(SetBkMode(hdc, TRANSPARENT)==0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

               if(SUCCEEDED(retc))
                  if(!DrawIcon(hdc, 0, 0, cur_wnd->m_hIcon))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

               EndPaint(hwndDlg, &ps);
            }
         }
      }

      retw=TRUE;
      break;

#if FALSE
   case WM_MOUSEMOVE:
// ----------------- mygtuku gesinimas
      prew_mouse_over = hMouseOverWnd;
      if(prew_mouse_over) // !=hwndDlg)
      {
         hMouseOverWnd = NULL; // hwndDlg;
//       if(prew_mouse_over)
            if(!InvalidateRect(prew_mouse_over, 0, TRUE))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
            }
      }
      break;
#endif

   case WM_QUIT:
   case WM_CLOSE:
      endfl = TRUE;
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      if(cur_wnd != NULL) cur_wnd->m_hWndHandle = NULL;
      break;

   case WM_COMMAND:
      if(retp==IDCANCEL) endfl=TRUE;
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl)
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if((endfl || FAILED(retc)) && (cur_wnd!=NULL))
   {
      retc0 = DeleteWnd(cur_wnd);
      if(SUCCEEDED(retc)) retc=retc0;

//    KP_DELETE(cur_wnd);
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// ----------------------
HRESULT KpCreateScrollBar(HINSTANCE /* hInst */, HWND hParent, HWND *phScrollBarCtrl, int iPosX, int iPosY, int iLen, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc=S_OK;
HWND scrollbar_control=NULL;
unsigned char scrollbar_name[200];

// if(hInst==NULL)
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)scrollbar_name, "KPW_SCROLLBAR_%d_%d", iPosX, iPosY);

      scrollbar_control=CreateWindowEx(dwExStyle /* |WS_EX_CLIENTEDGE */, "SCROLLBAR", (LPCTSTR)scrollbar_name,
                  WS_VISIBLE|WS_CHILD|dwStyle,
                  iPosX, iPosY, (dwStyle&SBS_VERT)?KPW_SCROLLBAR_WDT:iLen, (dwStyle&SBS_VERT)?iLen:KPW_SCROLLBAR_WDT, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(scrollbar_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phScrollBarCtrl!=NULL) && SUCCEEDED(retc)) *phScrollBarCtrl=scrollbar_control;

return(retc);
}


// ----------------------
#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButton(HINSTANCE /* hInst */, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc=S_OK;
HWND button_control=NULL;
int height;
int width;
HFONT hfont=NULL;

// if(hInst==NULL)
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc))
   {
      button_control=CreateWindowEx(
                  dwExStyle,
                  "BUTTON", (LPCTSTR)lpszText,
//                WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON|WS_TABSTOP, // |BS_BITMAP|WS_BORDER,
//                WS_CHILD|WS_VISIBLE|BS_BITMAP,
                  dwStyle| WS_CHILD|WS_VISIBLE, // |BS_FLAT
                  iPosX, iPosY, iWdtX, iWdtY, hParent, (HMENU)iId,
                  GetModuleHandle(NULL), 0);
      if(button_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc))
   {
      height=iaCtrlFntHghts[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL];
      width=iaCtrlFntHghts[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]*iaCtrlFntWdtFactors[KPW_CONTROL_STYLE_NORMAL]/100;
      hfont=CreateFont
         (
            height,                     // int nHeight,               // logical height of font
            width,                      // int nWidth,                // logical average character width
            0,                          // int nEscapement,           // angle of escapement
            0,                          // int nOrientation,          // base-line orientation angle
            iaCtrlFntWghts[KPW_CONTROL_STYLE_NORMAL], // int fnWeight,              // font weight
            False,                      // DWORD fdwItalic,           // italic attribute flag
            False,                      // DWORD fdwUnderline,        // underline attribute flag
            False,                      // DWORD fdwStrikeOut,        // strikeout attribute flag
            laCtrlCharSets[KPW_CONTROL_STYLE_NORMAL], // DWORD fdwCharSet,          // character set identifier
            OUT_DEFAULT_PRECIS,         // DWORD fdwOutputPrecision,  // output precision
            CLIP_DEFAULT_PRECIS,        // DWORD fdwClipPrecision,    // clipping precision
            DEFAULT_QUALITY,            // DWORD fdwQuality,          // output quality
            DEFAULT_PITCH|FF_SWISS,     // DWORD fdwPitchAndFamily,   // pitch and family
            iaCtrlTypefaces[KPW_CONTROL_STYLE_NORMAL] // LPCTSTR lpszFace           // pointer to typeface name string
         );
      if(hfont==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc))
      if(!PostMessage(button_control, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True, 0)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

   if((phButtonControl!=NULL) && SUCCEEDED(retc)) *phButtonControl=button_control;

return(retc);
}
#endif

#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, int iPosX, int iPosY)
{
return(KpCreateButton(hInst, hParent, phButtonControl, iId, lpszText, iPosX, iPosY, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0));
}
#endif

// ----------------------
#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, int iIconId, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc=S_OK;
HWND button_control=NULL;
// HBITMAP bitmap=NULL;
HICON icon=NULL;

   if(hInst==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc))
   {
      button_control=CreateWindowEx(dwExStyle, "BUTTON", (LPCTSTR)NULL,
//                WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON|WS_TABSTOP|BS_ICON, // |BS_BITMAP|WS_BORDER,
//                WS_CHILD|WS_VISIBLE|BS_BITMAP,
                  dwStyle| WS_CHILD|WS_VISIBLE|BS_ICON, // |BS_FLAT
                  iPosX, iPosY, iWdtX, iWdtY, hParent, (HMENU)iId,
                  GetModuleHandle(NULL), 0);
      if(button_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

#if FALSE
   if(SUCCEEDED(retc))
   {
      bitmap=LoadBitmap(hInst, (LPCTSTR)iBitmapId);
      if(bitmap==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc))
   {
      bitmap=(HBITMAP)LoadImage(GetModuleHandle(0), "back_ste.bmp",
                                        IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
      if(bitmap==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc))
      SendMessage(button_control, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

#endif

   if(SUCCEEDED(retc))
   {
      icon=LoadIcon(hInst, MAKEINTRESOURCE(iIconId));
      if(icon==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc))
      SendMessage(button_control, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);

   if((phButtonControl!=NULL) && SUCCEEDED(retc)) *phButtonControl=button_control;

return(retc);
}
#endif

#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, int iIconId, int iPosX, int iPosY)
{
return(KpCreateButton(hInst, hParent, phButtonControl, iId, iIconId, iPosX, iPosY,
   KPW_ICON_BUTTON_WDT /* KPW_BUTTON_HGT */ /* KPW_SCROLLBAR_WDT */,
   KPW_ICON_BUTTON_WDT /* KPW_BUTTON_HGT */ /* KPW_SCROLLBAR_WDT */,
   0, 0));
}
#endif

// ----------------------
#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, KpBmpData *pButBitmap, int iPosX, int iPosY, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc = S_OK;
HWND button_control = NULL;
KpWnd *wnd_ptr = NULL;

   if(((hInst==NULL) || (pButBitmap == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc)) if(pButBitmap->m_hBitMap == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

   if(SUCCEEDED(retc))
   {
      button_control = CreateWindowEx(dwExStyle, "BUTTON", (LPCTSTR)NULL,
                  dwStyle| WS_CHILD|WS_VISIBLE|BS_BITMAP,
                  iPosX, iPosY, pButBitmap->m_iBmpWdt, pButBitmap->m_iBmpHgt, hParent, (HMENU)iId,
                  GetModuleHandle(NULL), 0);
      if(button_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc))

      SendMessage(button_control, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)pButBitmap->m_hBitMap);

   if((phButtonControl!=NULL) && SUCCEEDED(retc)) *phButtonControl = button_control;

   KP_NEWO(wnd_ptr, KpWnd(button_control, TYP_Button, null, hParent, hInst, NULL, NULL,
         KPW_CONTROL_STYLE_NORMAL, pButBitmap->m_iBmpWdt, pButBitmap->m_iBmpHgt, 1, 1, dwExStyle, dwStyle, NULL,
         NULL, pButBitmap->m_hBitMap));

   if(SUCCEEDED(retc)) wnd_ptr->m_phBmpList[1] = pButBitmap->m_hSliderBmp; // paspausto mygtuko bitmapas

   if(SUCCEEDED(retc)) retc = WndPreg(wnd_ptr, TYP_Button, hInst, NULL, False);

return(retc);
}
#endif


// ----------------------
#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId,
   const unsigned char *lpszText,
   HBITMAP hBitmapReleased, HBITMAP hBitmapIlluminated, HBITMAP hBitmapPressed,
   int iPosX, int iPosY, int iWdtX, int iWdtY,
   int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0], // HPEN aPenScheme[KpNumOfShadows0],
   KpControlStyles iKpCtrlStyle)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
HWND button_ctrl = NULL;
DWORD ex_style = 0L;
DWORD style = 0L;
unsigned char button_name[200];
KpWnd *wnd_ptr = NULL;
HDC hdc = NULL;
HFONT hfont = NULL;

// ------------------------------
   if(
      (
         ((iKpWndStyle&(~(KP_WND_TAB|KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB|KP_WND_UNPROC_BUT|KP_WND_PROC_CURS|KP_WND_URL)))!=0) ||
         ((dwStyle&(~BS_PUSHLIKE))!=0L)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL, False);

// -----------------------------
#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#endif

// ------------------------------
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hInst;
      wcx.lpszClassName = "KPBUTTON",
      wcx.lpfnWndProc   = (WNDPROC)KpButtonDialogProc;
      wcx.style         = 0; // CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hIconSm       = LoadIcon(NULL /* hInst */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, (iKpWndStyle & (KP_WND_PROC_CURS | KP_WND_URL))?IDC_HAND:IDC_ARROW); // visiems mygtukams vienodas !!!
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // brush; // (HBRUSH)iaColorMap[KpShadowNorm];

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL, False);
      }
   }

   if(SUCCEEDED(retc))
   {
      ex_style = WS_EX_TRANSPARENT;
      style = (dwStyle & (~BS_PUSHLIKE)) | WS_VISIBLE | WS_CHILD; // WM_SETFONT|WS_BORDER|SS_GRAYRECT|WS_DISABLED|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT

      sprintf((char *)button_name, "KP_BUTTON_%d", iId);

      button_ctrl = CreateWindowEx(ex_style,
                     "KPBUTTON",
                     (LPCTSTR)button_name,
                     style,
                     iPosX, iPosY, iWdtX, iWdtY, hParent, 0,
                     GetModuleHandle(NULL), 0);
      if(!button_ctrl)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

   if(SUCCEEDED(retc)) retc = CrFont(&hfont, iKpCtrlStyle /* KPW_CONTROL_STYLE_NORMAL */, iKpWndStyle);

   if(SUCCEEDED(retc))
   {
      KP_NEWO(wnd_ptr, KpWnd(button_ctrl, TYP_Button, lpszText, hParent, hInst, hfont, wcx.hIcon,
         iKpCtrlStyle /* KPW_CONTROL_STYLE_NORMAL */, iWdtX, iWdtY, 1, 1, ex_style, style|dwStyle, NULL));
      if(FAILED(retc)) KP_DELETE(wnd_ptr);
   }

// ------------------- bitmaps
   hdc = NULL;
   if(SUCCEEDED(retc))
   {
      hdc = GetDC(button_ctrl);
      if(hdc == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// -----------------  BitmapReleased
// if((hBitmapReleased == NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL, False);

   if(hBitmapReleased)
   {
      if(SUCCEEDED(retc)) if(wnd_ptr->m_hBmpReleased == NULL)
         wnd_ptr->m_hBmpReleased = hBitmapReleased;

      if(SUCCEEDED(retc)) if(wnd_ptr->m_hdcReleased==NULL)
      {
         wnd_ptr->m_hdcReleased = CreateCompatibleDC(hdc);
         if(wnd_ptr->m_hdcReleased==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(wnd_ptr->m_hdcReleased, wnd_ptr->m_hBmpReleased))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// -----------------  BitmapIlluminated
   if(hBitmapIlluminated)
   {
      if(SUCCEEDED(retc)) if(wnd_ptr->m_hBmpIlluminated == NULL)
         wnd_ptr->m_hBmpIlluminated = hBitmapIlluminated?hBitmapIlluminated:hBitmapReleased;

      if(SUCCEEDED(retc)) if(wnd_ptr->m_hdcIlluminated == NULL)
      {
         wnd_ptr->m_hdcIlluminated = CreateCompatibleDC(hdc);
         if(wnd_ptr->m_hdcIlluminated == NULL)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(wnd_ptr->m_hdcIlluminated, wnd_ptr->m_hBmpIlluminated))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// -----------------  BitmapPressed
   if(hBitmapPressed)
   {
      if(SUCCEEDED(retc)) if(wnd_ptr->m_hBmpPressed == NULL)
         wnd_ptr->m_hBmpPressed = hBitmapPressed?hBitmapPressed:hBitmapReleased;

      if(SUCCEEDED(retc)) if(wnd_ptr->m_hdcPressed == NULL)
      {
         wnd_ptr->m_hdcPressed=CreateCompatibleDC(hdc);
         if(wnd_ptr->m_hdcPressed == NULL)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
      }
      if(SUCCEEDED(retc)) if(!SelectObject(wnd_ptr->m_hdcPressed, wnd_ptr->m_hBmpPressed))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// --------------------
   if(hdc != NULL) ReleaseDC(button_ctrl, hdc);
   hdc = NULL;

// --------------------
// if(SUCCEEDED(retc)) wnd_ptr->m_hPenScheme = aPenScheme;
   if(SUCCEEDED(retc)) wnd_ptr->m_iaColorScheme = iaColorScheme;

   if(SUCCEEDED(retc))
   {
      wnd_ptr->m_iKpWndStyle = iKpWndStyle;
      if((wnd_ptr->m_iKpWndStyle & KP_WND_URL) != 0) wnd_ptr->m_iKpWndStyle |= KP_WND_PROC_CURS | KP_WND_UNPROC_BUT;
   }

   if(SUCCEEDED(retc)) wnd_ptr->m_iMessage = iId;

   if(SUCCEEDED(retc)) retc = WndPreg(wnd_ptr, TYP_Button, hInst, NULL, False);

   if((phButtonControl!=NULL) && SUCCEEDED(retc)) *phButtonControl = button_ctrl;

return(retc);
}
#endif


// ----------------------
#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId,
   const unsigned char *lpszText,
   int iBitmapReleasedId, int iBitmapIlluminatedId, int iBitmapPressedId,
   int iPosX, int iPosY, int iWdtX, int iWdtY,
   int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0], // HPEN aPenScheme[KpNumOfShadows0],
   KpControlStyles iKpCtrlStyle)
{
HRESULT retc = S_OK;
HBITMAP bmp_released = NULL;
HBITMAP bmp_illuminated = NULL;
HBITMAP bmp_pressed = NULL;

// -----------------  BitmapReleased
   if(iBitmapReleasedId && SUCCEEDED(retc))
   {
      bmp_released = LoadBitmap(hInst, MAKEINTRESOURCE(iBitmapReleasedId));
      if(bmp_released == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// -----------------  BitmapIlluminated
   if(iBitmapIlluminatedId && SUCCEEDED(retc))
   {
      bmp_illuminated = LoadBitmap(hInst, MAKEINTRESOURCE(iBitmapIlluminatedId));
      if(bmp_illuminated == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// -----------------  BitmapPressed
   if(iBitmapPressedId && SUCCEEDED(retc))
   {
      bmp_pressed = LoadBitmap(hInst, MAKEINTRESOURCE(iBitmapPressedId));
      if(bmp_pressed == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
   }

// ----------------------
   if(SUCCEEDED(retc)) retc = KpCreateButtonLoc(hInst, hParent, phButtonControl, iId, lpszText,
      bmp_released, bmp_illuminated, bmp_pressed,
      iPosX, iPosY, iWdtX, iWdtY, iKpWndStyle, dwStyle, iaColorScheme, iKpCtrlStyle);

return(retc);
}
#endif


#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId,
   int iBitmapReleasedId, int iBitmapIlluminatedId, int iBitmapPressedId,
   int iPosX, int iPosY, int iWdtX, int iWdtY,
   int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0], // HPEN aPenScheme[KpNumOfShadows0],
   KpControlStyles iKpCtrlStyle)
{
return(KpCreateButtonLoc(hInst, hParent, phButtonControl, iId,
   null,
   iBitmapReleasedId, iBitmapIlluminatedId, iBitmapPressedId,
   iPosX, iPosY, iWdtX, iWdtY,
   iKpWndStyle, dwStyle, iaColorScheme, iKpCtrlStyle));
}
#endif


#if (Envir!=MSWin32ConMfc)
HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId,
   const unsigned char *lpszText,
   int iPosX, int iPosY, int iWdtX, int iWdtY,
   int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0], // HPEN aPenScheme[KpNumOfShadows0],
   KpControlStyles iKpCtrlStyle)
{
return(KpCreateButtonLoc(hInst, hParent, phButtonControl, iId,
   lpszText,
   0, 0, 0,
   iPosX, iPosY, iWdtX, iWdtY,
   iKpWndStyle, dwStyle, iaColorScheme, iKpCtrlStyle));
}
#endif


// -----------------------------------------
#if (Envir!=MSWin32ConMfc)
BOOL CALLBACK KpButtonDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
BOOL retw=FALSE;
int retp;
bool endfl=FALSE;
HDC hdc=NULL;
PAINTSTRUCT ps;
// RECT rect;
KpWnd *cur_wnd=NULL;
HDC bmp_hdc;
int posx, posy, shift_left, shift_up;
int border_sty;
HWND prew_mouse_over=NULL;
TRACKMOUSEEVENT mouse_trck;
int cur_x, cur_y;
int text_width;
// EXTLOGPEN log_pen;
// HPEN pen = NULL;
// HPEN pen_norm = NULL;
// HPEN pen_dark = NULL;
// HPEN pen_light = NULL;
HBRUSH brush = NULL;
COLORREF color = RGB_Black;
COLORREF color_norm = RGB_Black;
COLORREF color_dark = RGB_Black;
COLORREF color_light = RGB_Black;
COLORREF color_url = RGB_Blue;
RECT rect;

   retp=LOWORD(wParam);

   switch(uMsg)
   {
   case WM_CREATE:
   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_PAINT:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;

      if(cur_wnd != NULL)
      {
//       if(GetUpdateRect(hwndDlg, &rect, FALSE))
         {
            hdc = BeginPaint(hwndDlg, &ps);
            if(hdc == NULL)
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

// ----------------------- bitmap
            bmp_hdc = NULL;
            if(SUCCEEDED(retc))
            {
               if(cur_wnd->m_bPressed) bmp_hdc = cur_wnd->m_hBmpPressed?cur_wnd->m_hdcPressed:cur_wnd->m_hdcReleased;
               else
               {
                  if(hMouseOverWnd == hwndDlg) bmp_hdc = cur_wnd->m_hBmpIlluminated?cur_wnd->m_hdcIlluminated:cur_wnd->m_hdcReleased;
                  else bmp_hdc = cur_wnd->m_hdcReleased;
               }
               if(cur_wnd->m_iKpWndStyle & KP_WND_UNPROC_BUT)
               {
                  posx = 0; posy = 0;
                  shift_left = 0; shift_up = 0;
               }
               else
               {
                  if(cur_wnd->m_iKpWndStyle&KP_WND_TAB)
                  {
                     posx = 0;
                     if(cur_wnd->m_bPressed) posy = KPW_CTRL_BORDER_WDT;
                     else posy=KPW_CTRL_BORDER_WDT + 2;
                     shift_left=0; shift_up = 0;
                  }
                  else
                  {
                     posx=KPW_CTRL_BORDER_WDT;
                     posy=KPW_CTRL_BORDER_WDT;
                     if(cur_wnd->m_bPressed){ shift_left=0; shift_up=0; }
                     else{ shift_left=1; shift_up=1; }
                  }
               }

//             if(bmp_hdc==NULL)
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL, False);
            }

            if(bmp_hdc && SUCCEEDED(retc))
               if(!StretchBlt(ps.hdc, posx, posy, cur_wnd->m_iWdtDots, cur_wnd->m_iHgtDots,
                  bmp_hdc, shift_left, shift_up, cur_wnd->m_iWdtDots, cur_wnd->m_iHgtDots,
                  SRCCOPY))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);

// ----------------------- text button
// ---------- background
#if FALSE
            pen_norm = NULL;
            pen_dark = NULL;
            pen_light = NULL;

            if(SUCCEEDED(retc))
            {
               if(cur_wnd->m_hPenScheme == NULL)
               {
                  if(SUCCEEDED(retc))
                  {
                     pen_norm = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
                     if(pen_norm == NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
                  if(SUCCEEDED(retc))
                  {
                     pen_dark = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowDark]));
                     if(pen_dark == NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
                  if(SUCCEEDED(retc))
                  {
                     pen_light = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
                     if(pen_light == NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
               }
               else // if(cur_wnd->m_hPenScheme == NULL)
               {
                  if((cur_wnd->m_hPenScheme[KpShadowNorm] == NULL) && SUCCEEDED(retc))
                  {
                     pen_norm = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
                     if(pen_norm == NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
                  if((cur_wnd->m_hPenScheme[KpShadowDark] == NULL) && SUCCEEDED(retc))
                  {
                     pen_dark = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowDark]));
                     if(pen_dark == NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
                  if((cur_wnd->m_hPenScheme[KpShadowLight] == NULL) && SUCCEEDED(retc))
                  {
                     pen_light = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
                     if(pen_light == NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }

               } // else // if(cur_wnd->m_hPenScheme == NULL)

            } // if(SUCCEEDED(retcw) && SUCCEEDED(retc))

#else // #if FALSE

            color_norm = cur_wnd->m_iaColorScheme?cur_wnd->m_iaColorScheme[KpShadowNorm]:GetSysColor(iaColorMap[KpShadowNorm]);
            color_dark = cur_wnd->m_iaColorScheme?cur_wnd->m_iaColorScheme[KpShadowDark]:GetSysColor(iaColorMap[KpShadowDark]);
            color_light = cur_wnd->m_iaColorScheme?cur_wnd->m_iaColorScheme[KpShadowLight]:GetSysColor(iaColorMap[KpShadowLight]);
            color_url = cur_wnd->m_iaColorScheme?cur_wnd->m_iaColorScheme[KpLinkColor]:RGB_Blue /* GetSysColor(iaColorMap[KpLinkColor]) */;

#endif // #else // #if FALSE

            if(SUCCEEDED(retc))
            {
//             if(cur_wnd->m_lpszWndText[0])
               if(
                  (
                     ((hMouseOverWnd == hwndDlg) && (!cur_wnd->m_bPressed) && (cur_wnd->m_hdcIlluminated == NULL)) ||
                     ((hMouseOverWnd != hwndDlg) && (!cur_wnd->m_bPressed) && (cur_wnd->m_hdcReleased == NULL)) ||
                     ((cur_wnd->m_bPressed) && (cur_wnd->m_hdcPressed == NULL))
                  ) &&
                  (cur_wnd->m_hdcReleased == NULL) // ?ia mygtukams su vienu bmp - nieko nedaryti, StartSel.exe
                 )
               {
//                if(!SelectObject(hdc, (hMouseOverWnd == hwndDlg)?
//                                        (pen_dark?pen_dark:cur_wnd->m_hPenScheme[KpShadowDark]):
//                                        (pen_norm?pen_norm:cur_wnd->m_hPenScheme[KpShadowNorm])))
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);

//                pen = pen_norm?pen_norm:cur_wnd->m_hPenScheme[KpShadowNorm];
                  color = color_norm;
                  if(hMouseOverWnd == hwndDlg)
                  {
                     if((cur_wnd->m_iKpWndStyle&KP_WND_UNPROC_BUT) && ((cur_wnd->m_iKpWndStyle & KP_WND_URL) == 0))
                     {
//                      pen = pen_dark?pen_dark:cur_wnd->m_hPenScheme[KpShadowDark];
                        color = color_dark;
                     }
                     else
                     {
//                      pen = pen_light?pen_light:cur_wnd->m_hPenScheme[KpShadowNorm]; // [KpShadowLight];
                        color = color_norm; // color_light;
                     }
                  }

                  if(SUCCEEDED(retc))
                  {
//                   if(GetObject(pen, sizeof(log_pen), &log_pen))
                     {
//                      if(SUCCEEDED(retc))
                        {
//                         GetUpdateRect(hwndDlg, &rect, FALSE);

                           rect.left=0L;
                           rect.top=0L;
                           rect.right=cur_wnd->m_iWdtDots;
                           rect.bottom=cur_wnd->m_iHgtDots;
                        }

                        brush = NULL;
                        brush = CreateSolidBrush(color);

                        if(SUCCEEDED(retc))
                           if(!FillRect(hdc, &rect, brush)) // log_pen.elpColor)))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);

                        if(brush) if(!DeleteObject(brush))
                           /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                        brush = NULL;
                     }
//                   else
//                      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
               }

// ---------- teksto spalva
               if(cur_wnd->m_lpszWndText[0])
               {
//                pen = pen_dark?pen_dark:cur_wnd->m_hPenScheme[KpShadowDark];
                  color = color_dark;
                  if((hMouseOverWnd == hwndDlg) && (cur_wnd->m_iKpWndStyle&KP_WND_UNPROC_BUT) && ((cur_wnd->m_iKpWndStyle & KP_WND_URL) == 0))
                  {
//                   pen = pen_norm?pen_norm:cur_wnd->m_hPenScheme[KpShadowNorm];
                     color = color_norm;
                  }
                  if((cur_wnd->m_iKpWndStyle & KP_WND_URL) != 0)
                  {
//                   pen = pen_url?pen_url:cur_wnd->m_hPenScheme[KpLinkColor];
                     color = color_url;
                  }
// PutLogMessage_("KpButtonDialogProc() %x %x %x %s", color, color_url, cur_wnd->m_iaColorScheme?cur_wnd->m_iaColorScheme[KpLinkColor]:(-1), cur_wnd->m_lpszWndText);
                  if(SUCCEEDED(retc))
                  {
//                   if(GetObject(pen, sizeof(log_pen), &log_pen))
                     {
//                      if(SUCCEEDED(retc))
                           if(SetTextColor(hdc, color /* log_pen.elpColor */)==CLR_INVALID)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                     }
//                   else
//                      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                  }
               }

            } // if(cur_wnd->m_hPenScheme && SUCCEEDED(retc))

#if FALSE
            if(pen_norm) if(!DeleteObject(pen_norm))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            pen_norm = NULL;
            if(pen_dark) if(!DeleteObject(pen_dark))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            pen_dark = NULL;
            if(pen_light) if(!DeleteObject(pen_light))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            pen_light = NULL;
#endif

// ---------- text itself
            if(SUCCEEDED(retc)) if(cur_wnd->m_lpszWndText[0])
            {
//             if(SetTextColor(hdc, 0) == CLR_INVALID)
//             if(SetBkColor(hdc, 0x0000ff /* 0x00bbggrr */) == CLR_INVALID)
               if(SetBkMode(hdc, TRANSPARENT) == 0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

               if(SUCCEEDED(retc))
                  if(cur_wnd->m_hFont != NULL)
                     if(SelectObject(hdc, cur_wnd->m_hFont) == NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);

               cur_x = KPW_CTRL_MARGIN;
               if(SUCCEEDED(retc)) if((cur_wnd->m_iKpWndStyle & KP_WND_URL) == 0)
               {
                  retc = GetStrWidth(cur_wnd->m_lpszWndText, &text_width, hdc);
                  if(SUCCEEDED(retc)) cur_x = (cur_wnd->m_iWdtDots-text_width)/2;
               }
               cur_y = KPW_CTRL_MARGIN;
               if(SUCCEEDED(retc))
                  cur_y = (cur_wnd->m_iHgtDots - iaCtrlRowHeights[iWindowsVersionCut][cur_wnd->m_iKpCtrlStyle]) / 2;

               if((cur_wnd->m_bPressed) && (!(cur_wnd->m_iKpWndStyle&KP_WND_UNPROC_BUT)) && SUCCEEDED(retc))
               {
//                cur_x+=2; cur_y+=2;
                  cur_x++; cur_y++;
               }

               if(SUCCEEDED(retc))
                  if(!TextOut(hdc, cur_x, cur_y, (const char *)cur_wnd->m_lpszWndText, strlen(cur_wnd->m_lpszWndText)))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
            }

// -----------------------
            if(SUCCEEDED(retc)) if(!(cur_wnd->m_iKpWndStyle & (KP_WND_UNPROC_BUT | KP_WND_URL)))
            {
               if(cur_wnd->m_iKpWndStyle&KP_WND_TAB)
               {
                  if(cur_wnd->m_bPressed) border_sty=KP_WND_RAISED_BUTTON;
                  else border_sty=KP_WND_SUNKEN_BUTTON;
               }
               else
               {
                  if(cur_wnd->m_bPressed) border_sty=KP_WND_SUNKEN_BUTTON;
                  else border_sty=KP_WND_RAISED_BUTTON;
               }
               border_sty|=cur_wnd->m_iKpWndStyle&(~KP_WND_UNPROC_BUT);

               retc=KpDrawRect(ps.hdc, 0, 0, cur_wnd->m_iWdtDots, cur_wnd->m_iHgtDots, border_sty, cur_wnd->m_iaColorScheme); // cur_wnd->m_hPenScheme);
            }

            if(hdc!=NULL) EndPaint(hwndDlg, &ps);
            hdc=NULL;

         } // if(GetUpdateRect(hwndDlg, &rect, FALSE))

      } // if(cur_wnd!=NULL)

      retw=TRUE;
      break;

   case WM_LBUTTONDOWN:
// KP_TRACE("WM_LBUTTONDOWN");
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if(cur_wnd!=NULL)
      {
         if(cur_wnd->m_dwStyle&BS_PUSHLIKE)
            cur_wnd->m_bPressed=(!cur_wnd->m_bPressed);
         else cur_wnd->m_bPressed=True;
         if(!InvalidateRect(hwndDlg, 0, TRUE))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }
      }
      break;

   case WM_LBUTTONUP:
// KP_TRACE("WM_LBUTTONUP");
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if(cur_wnd!=NULL)
      {
         if(!((cur_wnd->m_dwStyle&BS_PUSHLIKE) || (cur_wnd->m_iKpWndStyle&KP_WND_TAB)))
            cur_wnd->m_bPressed=False;
         if(!InvalidateRect(hwndDlg, 0, TRUE))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }

         if(!PostMessage(cur_wnd->m_hParent, WM_COMMAND, cur_wnd->m_iMessage, 0L))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }
      }
      break;

   case WM_MOUSEMOVE:
      prew_mouse_over = hMouseOverWnd;
      if(prew_mouse_over != hwndDlg)
      {
// KpMsgOutF_2("%d %d", hMouseOverWnd, hwndDlg);
// KP_TRACE_2("WM_MOUSEMOVE: hMouseOverWnd: %d hwndDlg: %d", hMouseOverWnd, hwndDlg);
         hMouseOverWnd = hwndDlg;
// KP_TRACE_2("WM_MOUSEMOVE 2: hMouseOverWnd: %d hwndDlg: %d", hMouseOverWnd, hwndDlg);

//       if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;

         if(SUCCEEDED(retc)) retc = ManageToolTipTimer();

//---------------------
#if FALSE
         if(SUCCEEDED(retc)) if(prew_mouse_over) if(!InvalidateRect(prew_mouse_over, 0, TRUE))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }
#endif
         if(SUCCEEDED(retc)) if(!InvalidateRect(hwndDlg, 0, TRUE))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }

         if(SUCCEEDED(retc))
         {
            mouse_trck.cbSize=sizeof(mouse_trck);
            mouse_trck.dwFlags=TME_LEAVE;
            mouse_trck.hwndTrack=hwndDlg;
            mouse_trck.dwHoverTime=HOVER_DEFAULT;

            if(!TrackMouseEvent(&mouse_trck))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
            }
         }

#if FALSE
//       if(cur_wnd && SUCCEEDED(retc))
         {
//          if(cur_wnd->m_iKpWndStyle & KP_WND_PROC_CURS)
            {
HCURSOR cursor;
               cursor = LoadCursor(NULL, IDC_HAND);
KpMsgOut_1("move: %d", cursor);
               SetCursor(cursor);
            }
         }
#endif
      }
      break;

   case WM_MOUSELEAVE:
// KpMsgOutF_2("%d %d", hMouseOverWnd, hwndDlg);
// KP_TRACE_2("WM_MOUSELEAVE: hMouseOverWnd: %d hwndDlg: %d", hMouseOverWnd, hwndDlg);
//    if(hMouseOverWnd == hwndDlg)
      {
//       if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;

         if(hMouseOverWnd == hwndDlg) hMouseOverWnd = NULL;

         if(SUCCEEDED(retc)) retc = ManageToolTipTimer();

#if FALSE
//       if(cur_wnd && SUCCEEDED(retc))
         {
//          if(cur_wnd->m_iKpWndStyle & KP_WND_PROC_CURS)
            {
HCURSOR cursor;
               cursor = LoadCursor(NULL, IDC_ARROW);
KpMsgOut_1("leave: %d", cursor);
               SetCursor(cursor);
            }
         }
#endif

         if(!InvalidateRect(hwndDlg, 0, TRUE))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }
      }

      break;

   case BM_SETCHECK:
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd=NULL;

      if(cur_wnd!=NULL)
      {
         switch(retp)
         {
            case BST_CHECKED: cur_wnd->m_bPressed=True; break;
            case BST_UNCHECKED: cur_wnd->m_bPressed=False; break;
         }

         if(cur_wnd->m_iKpWndStyle&KP_WND_TAB)
         {
            cur_wnd->m_iKpWndStyle&=(~(KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB));
            cur_wnd->m_iKpWndStyle|=(lParam&(KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB));
         }

         if(!InvalidateRect(hwndDlg, 0, TRUE))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         }
      }
      retw=0;
      break;

   case WM_QUIT:
   case WM_CLOSE:
      endfl = TRUE;
      if(FAILED(GetCurWindow(&cur_wnd, hwndDlg))) cur_wnd = NULL;
      if(cur_wnd != NULL) cur_wnd->m_hWndHandle = NULL;
      break;

   case WM_COMMAND:
      if(retp==IDCANCEL) endfl=TRUE;
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(endfl)
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if((endfl || FAILED(retc)) && (cur_wnd!=NULL))
   {
      retc0 = DeleteWnd(cur_wnd);
      if(SUCCEEDED(retc)) retc = retc0;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif // #if (Envir!=MSWin32ConMfc)


// ----------------------
HRESULT KpCreateCheckBox(HINSTANCE /* hInst */, HWND hParent, HWND *phChBoxControl, int iPosX, int iPosY, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc=S_OK;
HWND ch_box=NULL;

   if(SUCCEEDED(retc))
   {
      ch_box=CreateWindowEx(dwExStyle|WS_EX_CLIENTEDGE /* |WS_EX_TRANSPARENT */, "BUTTON", (LPCTSTR)NULL,
                  dwStyle|BS_AUTOCHECKBOX|WS_VISIBLE|WS_CHILD, // BS_CHECKBOX &(~SS_GRAYFRAME)&(~WS_BORDER) |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  iPosX, iPosY, KPW_CHBOX_HGT, KPW_CHBOX_HGT, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!ch_box)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phChBoxControl!=NULL) && SUCCEEDED(retc)) *phChBoxControl=ch_box;

return(retc);
}


// ----------------------
HRESULT KpCreateRadioBut(HINSTANCE /* hInst */, HWND hParent, HWND *phRbutControl, int iPosX, int iPosY, DWORD dwExStyle, DWORD dwStyle)
{
HRESULT retc=S_OK;
HWND r_but=NULL;
WNDCLASSEX wcx;
// HPEN pen;
// EXTLOGPEN log_pen;
HBRUSH brush;

#if FALSE
   if(SUCCEEDED(retc))
   {
      pen=CreatePen(PS_SOLID, 1, RGB_Red);

      if(GetObject(pen, sizeof(log_pen), &log_pen))
         brush = CreateSolidBrush(log_pen.elpColor);
      else
      {
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         brush = (HBRUSH)iaColorMap[KpShadowNorm];
      }
   }
#endif

   if(SUCCEEDED(retc)) brush = CreateSolidBrush(RGB_Red);

   if(SUCCEEDED(retc))
      if(!GetClassInfoEx(hKpInstance, "BUTTON", &wcx))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      ButtonProcSav = wcx.lpfnWndProc;

      wcx.lpszClassName = "KPRADBUT",
      wcx.lpfnWndProc =
      wcx.lpfnWndProc = (WNDPROC)KpRadButProc;
      wcx.hbrBackground = brush;
      wcx.cbSize        = sizeof(WNDCLASSEX);

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      r_but=CreateWindowEx(dwExStyle|WS_EX_TRANSPARENT /* |WS_EX_CLIENTEDGE */, "KPRADBUT" /* "BUTTON" */, (LPCTSTR)NULL,
                  dwStyle|BS_AUTORADIOBUTTON|WS_VISIBLE|WS_CHILD, // |BS_RADIOBUTTON BS_CHECKBOX &(~SS_GRAYFRAME)&(~WS_BORDER) |WS_TABSTOP|SS_CENTER|SS_GRAYFRAME|SS_GRAYRECT,
                  iPosX, iPosY, KPW_CHBOX_HGT, KPW_CHBOX_HGT, hParent, 0,
                  GetModuleHandle(NULL), 0);
      if(!r_but)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phRbutControl!=NULL) && SUCCEEDED(retc)) *phRbutControl=r_but;

return(retc);
}


WNDPROC ButtonProcSav = NULL;

BOOL CALLBACK KpRadButProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;
HDC hdc = NULL;
// PAINTSTRUCT ps;
HPEN pen = NULL;

   if((ButtonProcSav == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_LBUTTONDOWN:
   case WM_LBUTTONUP:
   case BM_SETCHECK:
   case WM_PAINT:
      retw=(*ButtonProcSav)(hwndDlg, uMsg, wParam, lParam);

#if TRUE // #if FALSE
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
//       hdc=BeginPaint(hwndDlg, &ps);
         hdc=GetDC(hwndDlg);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// kol kas tik standartiniam langui
         pen = NULL;
         if(SUCCEEDED(retc))
         {
            pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
            if(pen == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
            if(!SelectObject(hdc, pen))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 0, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 0))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 1, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 5, 1))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 9, 1, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 1))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 2, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 3, 2))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 11, 2, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 2))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 3, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 2, 3))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 11, 3, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 3))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 4, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 2, 4))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 12, 4, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 4))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 5, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 1, 5))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 13, 5, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 5))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 6, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 1, 6))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 13, 6, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 6))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 7, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 1, 7))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 13, 7, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 7))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 8, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 1, 8))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 13, 8, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 8))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 9, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 2, 9))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 12, 9, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 9))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 10, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 2, 10))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 12, 10, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 10))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 11, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 3, 11)) // if(!LineTo(hdc, 5, 11))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 11, 11, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 11))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 12, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, 5, 12))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 9, 12, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 12))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 13, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 13))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);


         if(SUCCEEDED(retc))
            if(!MoveToEx(hdc, 0, 14, NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            if(!LineTo(hdc, KPW_CHBOX_HGT, 14))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         if(pen) DeleteObject(pen);
         pen = NULL;

//       /* if(SUCCEEDED(retc)) */ EndPaint(hwndDlg, &ps);
      }
#endif

      break;

   default:
      retw=(*ButtonProcSav)(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


//================================================
HRESULT KpCreateFrame(HINSTANCE hInst, HWND hParent, HWND *phFrameCtrl, int iPosX, int iPosY, int iWdtX, int iWdtY)
{
HRESULT retc=S_OK;
HWND frame_control=NULL;
HWND mdi_cli=NULL;
HWND frame_child=NULL;
WNDCLASSEX wcx;
CLIENTCREATESTRUCT ccs;
HICON icon;
int xx, yy, dx, dy;
DWORD ex_style;
DWORD style;
KpWnd *mdi_wnd=NULL;


// -----------------------------
#if FALSE
   pen = NULL;

   if(SUCCEEDED(retc))
   {
      pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
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
#endif

// --------------------------- create frame control
   if(SUCCEEDED(retc))
   {
      icon = LoadIcon(NULL /* hKpInstance */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));;

      wcx.hInstance     = hInst; // GetModuleHandle(NULL);
      wcx.lpszClassName = "KPFRAME",
      wcx.lpfnWndProc   = (WNDPROC)KpFrameDialogProc;
      wcx.style         = 0; // CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = icon;
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, /* MAKEINTRESOURCE */ (IDI_APPLICATION));
      wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // brush; // (HBRUSH)iaColorMap[KpShadowNorm];

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      xx=iPosX;
      yy=iPosY;
      dx=iWdtX;
      dy=iWdtY;

      ex_style=0; // WS_EX_CLIENTEDGE // |WS_EX_RIGHTSCROLLBAR, // WS_EX_MDICHILD // WS_EX_LEFT|WS_EX_LTRREADING
      style=WS_VISIBLE|WS_CLIPCHILDREN|WS_CHILD; // WS_OVERLAPPEDWINDOW| WS_VSCROLL|WS_HSCROLL, // |MDIS_ALLCHILDSTYLES|WS_OVERLAPPED

      frame_control=CreateWindowEx(
                  ex_style,
                  "KPFRAME",
                  NULL, // "KpFrame"
                  style,
                  xx, yy, dx, dy,
                  hParent,
                  (HMENU)NULL,
                  hInst, // GetModuleHandle(NULL),
                  NULL);
      if(frame_control==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phFrameCtrl!=NULL) && SUCCEEDED(retc)) *phFrameCtrl=frame_control;


// --------------------- create MDI client
   if(SUCCEEDED(retc))
   {
      ccs.hWindowMenu  = 0; // GetSubMenu(GetMenu(hParent), 2);
      ccs.idFirstChild = ID_MDI_FIRSTCHILD;

      mdi_cli=CreateWindowEx(
//                WS_EX_LEFT|WS_EX_LTRREADING|
                  WS_EX_CLIENTEDGE, // |WS_EX_RIGHTSCROLLBAR, // WS_EX_MDICHILD
                  "MDICLIENT", // "mdiclient" // "EDIT"
                  NULL, // "KpFrame"
                  WS_VISIBLE|WS_CHILD|WS_VSCROLL|WS_HSCROLL|WS_CLIPCHILDREN| MDIS_ALLCHILDSTYLES, // |WS_OVERLAPPED
                  CW_USEDEFAULT,
                  CW_USEDEFAULT,
                  CW_USEDEFAULT,
                  CW_USEDEFAULT,
                  frame_control,
                  (HMENU)NULL,
                  GetModuleHandle(NULL),
                  (LPVOID)&ccs);
      if(mdi_cli==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }


// ---------------------
   KP_NEWO(mdi_wnd, KpWnd(frame_control, TYP_MDI_Frame, NULL, hParent, hInst, NULL, icon, KPW_CONTROL_STYLE_NORMAL,
         dx, dy,
         dx*(((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?9:10)/iaCtrlTextFactors[KPW_CONTROL_STYLE_NORMAL],
         dy/iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL],
         ex_style, style, mdi_cli));

   if(SUCCEEDED(retc)) retc = WndPreg(mdi_wnd, TYP_MDI_Frame, hInst, null, False);

// kazkodel MDI kliento is karto neparodo - reikia pajudint
   if(SUCCEEDED(retc))
   {
      if(!SetWindowPos(mdi_cli, HWND_TOPMOST,
         0, 0, iWdtX-2*KPW_WND_BORDER_WDT_INI-2*KPW_WND_BORDER_COR, iWdtY-2*KPW_WND_BORDER_WDT_INI-2*KPW_WND_BORDER_COR,
         SWP_NOZORDER))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

return(retc);
}


#if FALSE

         ccs.hWindowMenu  = GetSubMenu(GetMenu(hWnd), 2);
         ccs.idFirstChild = StartChildrenNo;

         hWndChildFrame = CreateWindowEx(WS_EX_CLIENTEDGE,
                                       "MDICLIENT",
                                 NULL,
                                 WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL
                                          | WS_HSCROLL | WS_VISIBLE,
                                       CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 680,
                                 460,
                                 hWnd,
                                 (HMENU)IDM_FILE_NEW,
                                 GetModuleHandle(NULL),
                                 (LPVOID)&ccs);


CLIENTCREATESTRUCT ccs;

    ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 2);
    ccs.idFirstChild = ID_MDI_FIRSTCHILD;

    g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL,
        WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        hwnd, (HMENU)IDC_MAIN_MDI, GetModuleHandle(NULL), (LPVOID)&ccs);


hWndClient = CreateWindowEx(WS_EX_LEFT | WS_EX_LTRREADING |
WS_EX_RIGHTSCROLLBAR | WS_EX_CLIENTEDGE,
"MDICLIENT", NULL,
WS_OVERLAPPED | WS_CHILD | MDIS_ALLCHILDSTYLES |
WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
0, 0, 0, 0,
hWndparent,
(HMENU)NULL,
hInst,
(LPVOID)&ccs);
#endif


//================================================
HRESULT KpCreateFrameChild(HINSTANCE hInst, HWND hMDIClient, HWND *phFrameChild, int iChildPosX, int iChildPosY, int iChildWdtX, int iChildWdtY, unsigned char *lpszClassName, WNDPROC lpfnFrameProc)
{
HRESULT retc=S_OK;
HWND frame_child=NULL;
KpWnd *mdi_wnd=NULL;
WNDCLASSEX wc;
// MDICREATESTRUCT mcs;
// char str_buf[100];

#if FALSE // TRUE //
sprintf(str_buf, "KpCreateFrameChild: %d", iChildWdtY);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

// ------------------- create MDI child
   if(SUCCEEDED(retc))
   {
      wc.hInstance     = hInst;
      wc.lpszClassName = (const char *)lpszClassName;
      wc.lpfnWndProc   = lpfnFrameProc;
      wc.style         = CS_HREDRAW | CS_VREDRAW; // 0
      wc.cbSize        = sizeof(WNDCLASSEX);
      wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // LoadIcon(hKpInstance, MAKEINTRESOURCE(IDI_APPLICATION));
      wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // LoadIcon(hKpInstance, MAKEINTRESOURCE(IDI_APPLICATION));
      wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
      wc.lpszMenuName  = NULL;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = 0;
      wc.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm]; // (HBRUSH)(COLOR_3DFACE+1);

      if(!RegisterClassEx(&wc))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
#if FALSE // TRUE //
      mcs.szTitle = NULL; // "DarbListFrameChild";
      mcs.szClass = lpszClassName;
      mcs.hOwner  = hInst; // GetModuleHandle(NULL);
      mcs.x =  iChildPosX; // 0; // CW_USEDEFAULT;
      mcs.cx = iChildWdtX; // 1000; // CW_USEDEFAULT;
      mcs.y =  iChildPosY; // 0; // CW_USEDEFAULT;
      mcs.cy = iChildWdtY; // 1000; // CW_USEDEFAULT;
      mcs.style = 0; // WS_VISIBLE; // MDIS_ALLCHILDSTYLES;

      frame_child=(HWND)SendMessage(mdi_cli, WM_MDICREATE, 0, (LONG)&mcs);
#else
      frame_child=CreateMDIWindow(
               (char *)lpszClassName,
               NULL, // "DarbListFrameChild",
               WS_VISIBLE, // MDIS_ALLCHILDSTYLES, //
               iChildPosX, // 0; // CW_USEDEFAULT;
               iChildPosY, // 0; // CW_USEDEFAULT;
               iChildWdtX, // 1000; // CW_USEDEFAULT;
               iChildWdtY, // 1000; // CW_USEDEFAULT;
               hMDIClient,
               hKpInstance,
               0);
#endif
      if(frame_child==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if((phFrameChild!=NULL) && SUCCEEDED(retc)) *phFrameChild=frame_child;

return(retc);
}

#if FALSE
// Create the MDI child
hWndChild = CreateWindowEx(WS_EX_MDICHILD | WS_EX_CLIENTEDGE,
"MdiChildWndClass", strTitle,
WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION,
CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
g_hWndClient, NULL, g_hInst, 0);

#endif


// -------------------------------------------
BOOL CALLBACK KpFrameDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;
KpWnd *frame_wnd=NULL;
HWND mdi_cli=0;
// HWND prew_mouse_over=NULL;

#if FALSE
char str_buf[100];
if(uMsg==WM_COMMAND)
{
sprintf(str_buf, "KpFrameDialogProc WM_COMMAND: %d:%d %ld", HIWORD(wParam), LOWORD(wParam), lParam);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
}
#endif

   if(SUCCEEDED(retc)) switch(uMsg)
   {
      case WM_INITDIALOG:
         retw=TRUE;
         break;

#if FALSE
      case WM_MOUSEMOVE:
// ----------------- mygtuku gesinimas
         prew_mouse_over = hMouseOverWnd;
         if(prew_mouse_over) // !=hwndDlg)
         {
            hMouseOverWnd = NULL; // hwndDlg;
//          if(prew_mouse_over)
               if(!InvalidateRect(prew_mouse_over, 0, TRUE))
               {
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
               }
         }
         break;
#endif

      case WM_COMMAND:
         switch(LOWORD(wParam))
         {
         case IDOK:
         case IDCANCEL:
            ::PostQuitMessage(IDCANCEL);
            retw=TRUE;
            break;
         }
         break;

      case WM_CLOSE:
         ::PostQuitMessage(IDCANCEL);
         break;

//    case WM_PAINT:
//       retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
//       break;

      default:
         if(SUCCEEDED(retc)) switch(uMsg)
         {
         case WM_MOUSEMOVE: // !!!! lango ieskoti tik reikalingiems pranesimams, kad nestabdytu daznu pranesimu
            break;
         default:
            if(SUCCEEDED(retc))
               retc=GetCurWindow(&frame_wnd, hwndDlg);
            if(SUCCEEDED(retc))
               if(frame_wnd!=NULL)
                  mdi_cli=frame_wnd->m_hMDI_Client;
            break;
         }

//       retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);

         retw=DefFrameProc(hwndDlg, mdi_cli, uMsg, wParam, lParam);

//       if(LOWORD(wParam) >= ID_MDI_FIRSTCHILD)
//          retw=DefFrameProc(hwndDlg, DarbaiApp.m_pDarbDialogPtr->m_hFrameCtrl, uMsg, wParam, lParam);
//       else
//       {
//          hChild=(HWND)SendMessage(DarbaiApp.m_pDarbDialogPtr->m_hFrameCtrl, WM_MDIGETACTIVE,0,0L);
//          if(hChild)
//             SendMessage(hChild, WM_COMMAND, wParam, lParam);
//       }
         break;
   }

   if(FAILED(retc))
      ::PostQuitMessage(IDABORT);

return(retw);
}


//================================================
KpBmpData::KpBmpData(void)
{
   InitMembers(200, 100);
}

KpBmpData::KpBmpData(int iBmpWdt, int iBmpHgt)
{
   InitMembers(iBmpWdt, iBmpHgt);
}


void KpBmpData::InitMembers(int iBmpWdt, int iBmpHgt)
{
   m_hBitMap = NULL;
   m_hPressed = NULL;
   m_hHover = NULL;

   m_hBitmapCtrl = NULL;
   m_iBmpWdt = iBmpWdt;
   m_iBmpHgt = iBmpHgt;
   m_iCaptHgt = IBSH_WND_SOFT_CAPTION_HGT;

   m_hdcBmpHdc = NULL;

   m_bShowSlider = False;
   m_hSliderBmp = NULL;

   m_iBitmapCnt = 0;
// m_iCurBmp = 0;
   m_plpszBmpList = NULL;
   m_iaBmpTimes = NULL;

   m_iProlShowTime = 0;
   m_lFullSize = 10000L; // kad nety?ia neb?t¸ dalybos i? 0

   m_lpszMsgTxt = null;

// m_bShowMuteButton = False;
// m_hMuteButtonBmp = NULL;
   m_pMuteButtonBmpData = NULL;
}


KpBmpData::~KpBmpData(void)
{
HRESULT retc = S_OK;

// -------------------
   if(m_hBitMap != NULL)
      if(!DeleteObject(m_hBitMap))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hBitMap = NULL;

   if(m_hdcBmpHdc != NULL)
      if(!DeleteDC(m_hdcBmpHdc))
      {
#ifdef Debug
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
      }
   m_hdcBmpHdc = NULL;

// -------------------
   KP_DELETE(m_pMuteButtonBmpData);
}


//------------------------------------------------
HRESULT KpBmpData::LoadImageFromFile(const unsigned char *lpszBmpFileName)
{
HRESULT retc=S_OK;

   m_hBitMap = (HBITMAP)LoadImage(GetModuleHandle(0), (const char *)lpszBmpFileName,
                                       IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
   if(m_hBitMap == NULL)
   {
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, lpszBmpFileName, True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc)) retc = CalcDimensions();

return(retc);
}


// -------------------------------
HRESULT KpBmpData::CalcDimensions(void)
{
HRESULT retc=S_OK;
// HDC hdc;
// SIZE bmp_size;
// HDC bmp_hdc;
// HBITMAP bmp_tmp;
// HGDIOBJ bmp_obj;
BITMAP bmp_data;

   if(m_hBitMap == NULL)
   {
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
   else
   {
#if FALSE
      if(SUCCEEDED(retc))
         if(!GetBitmapDimensionEx(m_hBitMap, &bmp_size))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         m_iBmpWdt = bmp_size.cx;
         m_iBmpHgt = bmp_size.cy;
      }
#endif

#if FALSE
      if(SUCCEEDED(retc))
      {
         hdc=GetDC(HWND_DESKTOP);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         bmp_hdc = CreateCompatibleDC(hdc);
         if(!bmp_hdc)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         bmp_tmp = (HBITMAP)LoadImage(GetModuleHandle(0), (const char *)m_lpszBackground,
                                          IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
         if(bmp_tmp == NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         bmp_obj = SelectObject(bmp_hdc, bmp_tmp /* m_hBitMap */);
         if(!bmp_obj)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
         if(!GetObject(bmp_obj, sizeof(bmp_data), &bmp_data))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

      if(SUCCEEDED(retc))
         if(!GetObject(m_hBitMap, sizeof(bmp_data), &bmp_data))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         m_iBmpWdt = bmp_data.bmWidth;
         m_iBmpHgt = bmp_data.bmHeight;
      }

   } // else // if(m_hBitMap == NULL)

return(retc);
}


void KpWnd::InitSliderCoords(void)
{
   m_iWndX_10 = (m_iParentWdtDots <= m_iWdtDots / 2)?
                     (-(m_iWdtDots * 10 / 2)):
                     ((m_iParentWdtDots - m_iWdtDots) * 10);
   m_iWndX = m_iWndX_10 / 10;

// KP_TRACE_("InitSliderCoords() m_iParentWdtDots: %d m_iWdtDots: %d m_iWndX_10: %d", m_iParentWdtDots, m_iWdtDots, m_iWndX_10);
}


void KpWnd::CalcSliderSteps(int iProlTime) // , bool test_msg)
{
int prol_time_msec = 0;

   prol_time_msec = iProlTime * 1000;
   if(prol_time_msec <= 0) prol_time_msec = 1;

   m_iWndXStep_10 =
      (
         (m_iParentWdtDots <= m_iWdtDots / 2)?
            (m_iParentWdtDots):
            (m_iParentWdtDots - m_iWdtDots)
      ) * KP_SLIDER_TIMEOUT * 10 / prol_time_msec;

// if(test_msg) KpMsgOutF_4("%d %d %d %d", m_iParentWdtDots, KP_SLIDER_TIMEOUT, prol_time_msec, m_iParentWdtDots * KP_SLIDER_TIMEOUT * 10 / prol_time_msec);
// if(test_msg) KpMsgOutF_1("%d", m_iWndXStep_10);
   if(m_iWndXStep_10 >= -m_iWndX * 10) m_iWndXStep_10 = -m_iWndX * 10 - 1;
   if(m_iWndXStep_10 >= (m_iWdtDots - m_iParentWdtDots) * 10) m_iWndXStep_10 = (m_iWdtDots - m_iParentWdtDots) * 10 - 1;
   if(m_iWndXStep_10 <= 0) m_iWndXStep_10 = 1;
   if(iProlTime == Maxint) m_iWndXStep_10 = 0; // parametru iProlTime == Maxint nusodinamas taimerio valdymas
// if(test_msg) KpMsgOutF_1("%d", m_iWndXStep_10);

   m_iWndYStep_10 = (m_iHgtDots - KPW_SLIDER_HGT) * KP_SLIDER_TIMEOUT * 10 / prol_time_msec;
}


//------------------------------------------------
HRESULT ShowBmp(const unsigned char *lpszBmpFileName, int iBmpWdt,int iBmpHgt,
                  HWND *phBitmapWindow, bool bShowSlider,
                  int iBitmapCnt, unsigned char **plpszBmpList, int *iaBmpTimes, int iSliderId, int iProlShowTime,
                  HWND hParent, int iBmpX, int iBmpY, KpBmpData *pMuteButtonBmpData,
                  const unsigned char *lpszWndName, LPSTR lpszIcon)
{
HRESULT retc=S_OK;
WNDCLASSEX wcx;
// RECT wnd_rect;
HDC hdc;
int wnd_x = 0;
int wnd_y = 0;
int wnd_dx = 100;
int wnd_dy = 100;
DWORD wnd_style;
// unsigned char fnam_buf[KP_MAX_FNAME_LEN + 1];
// unsigned char *pnt_ext;
// unsigned char *pnt_next;
KpBmpData *bmp_pars = NULL;
HWND bmp_wnd = NULL;
static unsigned char bmp_fname[KP_MAX_FNAME_LEN + 1];
KpPubDlg *pub_dlg = NULL;

   KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);

   bmp_fname[0] = Nul;
   if(lpszBmpFileName)
   {
      KP_ASSERT(strlen(lpszBmpFileName) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(bmp_fname, lpszBmpFileName);
         retc = CutInitTrailSpcs(bmp_fname);
      }
   }

   if((bmp_fname[0] || bShowSlider) && SUCCEEDED(retc))
   {
//    strcpy(fnam_buf, m_Ini.lpszBmpFName);
//    strlwr((char *)fnam_buf);

//    pnt_ext=strchr(fnam_buf, '.');
//    if(pnt_ext!=NULL)
      {
//       do
//       {
//          pnt_next=strchr(pnt_ext+1, '.');
//          if(pnt_next!=NULL) pnt_ext=pnt_next;
//       } while(pnt_next!=NULL);

//       if(strcmp(pnt_ext, ".bmp")==0)
         {
            KP_NEW(bmp_pars, KpBmpData(iBmpWdt, iBmpHgt));

            if(SUCCEEDED(retc)) bmp_pars->m_hBitMap = NULL;
            if(bmp_fname[0] && SUCCEEDED(retc))
            {
               bmp_pars->m_hBitMap=(HBITMAP)LoadImage(GetModuleHandle(0), (const char *)bmp_fname,
                                              IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
//             KP_ASSERT(bmp_pars->m_hBitMap, KP_E_FILE_NOT_FOUND, GetLastError(), True);
               KP_ASSERT(bmp_pars->m_hBitMap, KP_E_FILE_NOT_FOUND, bmp_fname, True);
            }

            if(((bmp_pars->m_iBmpWdt <= 0) || (bmp_pars->m_iBmpHgt <= 0)) && SUCCEEDED(retc))
               retc = bmp_pars->CalcDimensions();

            if(SUCCEEDED(retc)) bmp_pars->m_bShowSlider = bShowSlider;
            if(bShowSlider && SUCCEEDED(retc))
            {
               bmp_pars->m_hSliderBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(iSliderId));
               if(bmp_pars->m_hSliderBmp == 0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc))  bmp_pars->m_iProlShowTime = iProlShowTime;

// ------------------------------
            if(SUCCEEDED(retc))
            {
               bmp_pars->m_iBitmapCnt = iBitmapCnt;
//             bmp_pars->m_iCurBmp = 0;
               bmp_pars->m_plpszBmpList = plpszBmpList;
               bmp_pars->m_iaBmpTimes = iaBmpTimes;

//             bmp_pars->m_bShowMuteButton = bShowMuteButton;
               bmp_pars->m_pMuteButtonBmpData = pMuteButtonBmpData;
            }

            if((iBitmapCnt > 1) && SUCCEEDED(retc))
            {
               KP_ASSERT(plpszBmpList, E_INVALIDARG, null, True);
               KP_ASSERT(iaBmpTimes, E_INVALIDARG, null, True);
               KP_ASSERT(strcmp(plpszBmpList[0], bmp_fname) == 0, E_INVALIDARG, null, False);
            }

// ---------------------------------
#if TRUE
            if(SUCCEEDED(retc))
            {
               wcx.hInstance     = hKpInstance;
               wcx.lpszClassName = "KPSBMP",
               wcx.lpfnWndProc   = (WNDPROC)KpStShBmpProc;
               wcx.style         = CS_DBLCLKS;
               wcx.cbSize        = sizeof(WNDCLASSEX);
               wcx.hIcon         = LoadIcon(hKpInstance, lpszIcon);
               wcx.hIconSm       = LoadIcon(hKpInstance, lpszIcon);
               wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
               wcx.lpszMenuName  = 0;
               wcx.cbClsExtra    = 0;
               wcx.cbWndExtra    = 0;
               wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];

               if(!RegisterClassEx(&wcx))
               {
                  long ll = GetLastError();
                  if(ll != ERROR_CLASS_ALREADY_EXISTS)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
               }
            }

            if(SUCCEEDED(retc))
            {
               if(hParent == HWND_DESKTOP)
               {
                  hdc = GetDC(hParent); // (HWND_DESKTOP);
                  if(hdc==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                  {
                     wnd_x = (GetDeviceCaps(hdc, HORZRES) - KPSBMP_WND_WDT(bmp_pars->m_iBmpWdt))/2;
                     wnd_y = (GetDeviceCaps(hdc, VERTRES) - KPSBMP_WND_HGT(bmp_pars->m_iBmpHgt) - (bShowSlider?KPW_SLIDER_HGT:0))/2;
                  }
               }
               else
               {
                  wnd_x = iBmpX;
                  wnd_y = iBmpY;
               }
            }

            if(SUCCEEDED(retc))
            {
               wnd_dx = KPSBMP_WND_WDT(bmp_pars->m_iBmpWdt);
               wnd_dy = KPSBMP_WND_HGT(bmp_pars->m_iBmpHgt) + (bShowSlider?KPW_SLIDER_HGT:0);
            }

            if(SUCCEEDED(retc)) wnd_style = ((hParent == HWND_DESKTOP)?WS_POPUP /* WS_POPUPWINDOW */ : WS_CHILD)|WS_VISIBLE|WS_BORDER; // |WS_THICKFRAME|WS_CAPTION|WS_POPUP

// ---------------------------- kp_wnd/pub_dlg k?rimas atkeltas i? KpStShBmpProc() WM_CREATE; inicijavimas ir registravimas – vis dar ten
//          if(/* (hParent == HWND_DESKTOP) && */ SUCCEEDED(retc))
            {
iBshFileSys *file_sys_obj = NULL; // fiktyvi fail¸ sistema d?l pub_dlg
               KP_NEWO(file_sys_obj, iBshFileSys);

               KP_NEWO(pub_dlg, KpPubDlg(file_sys_obj, IBSH_OUT_VERS, UC_PlainText, IBSH_WND_CAPTION,
                  IBSH_DEF_WND_MIN_DX, IBSH_DEF_WND_MAX_DX, IBSH_DEF_WND_MIN_DY, IBSH_DEF_WND_MAX_DY,
                  IBSH_WND_SOFT_BORDER_WDT, IBSH_WND_SOFT_CAPTION_HGT, IBSH_WND_BORDER_WDT, IBSH_WND_CAPTION_HGT,
                  IBSH_DEF_SRC_X, IBSH_DEF_SRC_Y, IBSH_DEF_SRC_DX, IBSH_DEF_SRC_DY, IBSH_RES_DX_ENL, IBSH_RES_DY_ENL,
                  wnd_style, wnd_x, wnd_y, wnd_dx, wnd_dy, hParent));
               if(SUCCEEDED(retc)) retc = pub_dlg->InitBmpMembers(bmp_pars);
            }

            if(SUCCEEDED(retc))
            {
               bmp_wnd = CreateWindowEx
                  (
                     0,                         // DWORD dwExStyle,     // extended window style
                     "KPSBMP",
                     (const char *)lpszWndName, // LPCTSTR lpWindowName, // pointer to window name
                     wnd_style,                 // DWORD dwStyle,        // window style
                     wnd_x, // CW_USEDEFAULT,   // int x,              // horizontal position of window
                     wnd_y, // CW_USEDEFAULT,   // int y,              // vertical position of window
                     wnd_dx,                    // int nWidth,           // window width
                     wnd_dy,                    // int nHeight,          // window height
                     hParent, // HWND_DESKTOP,  // HWND hWndParent,   // handle to parent or owner window
                     0,                         // HMENU hMenu,         // handle to menu, or child-window identifier
                     hKpInstance,
                     pub_dlg // bmp_pars  // this  /* KpStApp */  // LPVOID lpParam  // pointer to window-creation data
                  );

               KP_ASSERT(bmp_wnd, KP_E_SYSTEM_ERROR, GetLastError(), True);
            }
#else
            if(SUCCEEDED(retc))
               retc=KpCreateBitmap(hKpInstance, HWND_DESKTOP, &bmp_wnd,
                  bmp_pars->m_hBitMap, KPSBMP_BMP_X, KPSBMP_BMP_Y, bmp_pars->m_iBmpWdt, bmp_pars->m_iBmpHgt,
                  0 /* WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE */);

#endif
            if(phBitmapWindow && SUCCEEDED(retc)) *phBitmapWindow = bmp_wnd;
            if(pub_dlg && SUCCEEDED(retc)) pub_dlg->m_hDialogWindow = bmp_wnd;

            if(SUCCEEDED(retc)) retc = KpSleep(200, bmp_wnd);

         } // if(strcmp(pnt_ext, ".bmp")==0)

      } // if(pnt_ext!=NULL)

   } // if((lpszBmpFileName!=NULL) && SUCCEEDED(retc)) if(strlen(lpszBmpFileName)>0)

return(retc);
}


// -------------------------------------------
BOOL CALLBACK KpStShBmpProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
BOOL retw=FALSE;
CREATESTRUCT *csp = NULL;
// KpStApp *cur_app = NULL;
KpBmpData *bmp_pars = NULL; // dabar per lParam perduodamas ne *bmp_pars, o *pub_dlg, pointer? i?sitraukiam i? jo
// KpBmpData but_bmp_pars;
// HWND prew_mouse_over = NULL;
KpWnd *pub_dlg = NULL; // KpWnd *kp_wnd = NULL;
KpWnd *kp_slider_wnd = NULL;
RECT rect;
HBITMAP bitmap = NULL;

   if(SUCCEEDED(retc)) switch(uMsg)
   {
// #if FALSE
   case WM_CREATE:
      if(SUCCEEDED(retc))
      {
         csp = (LPCREATESTRUCT)lParam;
         KP_ASSERT(csp != NULL, KP_E_SYSTEM_ERROR, null, True);
      }

//    if(SUCCEEDED(retc)) cur_app=(KpStApp *)csp->lpCreateParams;
//    if((cur_app==NULL) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
//    if(SUCCEEDED(retc)) if((cur_app->m_hInstance==NULL) || (cur_app->m_hBitMap==NULL))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// ------------------ dabar per lParam perduodamas ne *bmp_pars, o *pub_dlg, duomenis i?sitraukiam i? jo
#if FALSE
      if(SUCCEEDED(retc)) bmp_pars = (KpBmpData *)csp->lpCreateParams;
#else
      if(SUCCEEDED(retc)) pub_dlg = (KpPubDlg *)csp->lpCreateParams;
      KP_ASSERT(pub_dlg != NULL, E_POINTER, null, True);

      if(SUCCEEDED(retc)) bmp_pars = pub_dlg->m_pBmpPars;
#endif
      KP_ASSERT(bmp_pars != NULL, E_POINTER, null, True);

      KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);
//    KP_ASSERT(bmp_pars->m_hBitMap, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) if(bmp_pars->m_hBitMap)
      {
         retc = KpCreateBitmap(hKpInstance, hwndDlg, &bmp_pars->m_hBitmapCtrl,
               bmp_pars->m_hBitMap, KPSBMP_BMP_X, KPSBMP_BMP_Y,
               bmp_pars->m_iBmpWdt, bmp_pars->m_iBmpHgt - (bmp_pars->m_bShowSlider?KPW_SLIDER_HGT:0),
               0 /* WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE */);

         KP_ASSERT(bmp_pars->m_hBitmapCtrl, KP_E_SYSTEM_ERROR, null, False);

         if(SUCCEEDED(retc)) if(bmp_pars->m_pMuteButtonBmpData /* bmp_pars->m_hMuteButtonBmp */ /* bmp_pars->m_bShowMuteButton */ && bmp_pars->m_hBitmapCtrl)
         {
//          but_bmp_pars.m_hBitMap = bmp_pars->m_hMuteButtonBmp;

//          if(SUCCEEDED(retc)) retc = but_bmp_pars.CalcDimensions();

            KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(theKpStAppPtr->m_hMuteButton == NULL, KP_E_SYSTEM_ERROR, null, True);

            if(/* but_bmp_pars.m_hBitMap && */ SUCCEEDED(retc))
               retc = KpCreateButton(hKpInstance, hwndDlg /* bmp_pars->m_hBitmapCtrl */,
                  &theKpStAppPtr->m_hMuteButton, KP_ID_MUTE,
                  bmp_pars->m_pMuteButtonBmpData, // &but_bmp_pars,
                  bmp_pars->m_iBmpWdt - KPW_WND_HOR_MARGIN - bmp_pars->m_pMuteButtonBmpData->m_iBmpWdt, // but_bmp_pars.m_iBmpWdt,
                  bmp_pars->m_iBmpHgt - KPW_WND_VER_MARGIN - bmp_pars->m_pMuteButtonBmpData->m_iBmpHgt, // but_bmp_pars.m_iBmpHgt,
                  0L, 0L);
         }
      }


      if(SUCCEEDED(retc)) if((bmp_pars->m_bShowSlider) || (bmp_pars->m_iBitmapCnt > 1))
      {
#if TRUE
static BITMAPINFO bmp_info;
#else
SIZE bmp_dim;
#endif
HWND slider_bmp = NULL;

         slider_bmp = NULL;

#if TRUE
         bmp_info.bmiHeader.biSize = sizeof(bmp_info);
         bmp_info.bmiHeader.biHeight = 0;
#else
         bmp_dim.cx = 640;
         bmp_dim.cy = 152;
#endif

         if(bmp_pars->m_bShowSlider)
         {
HDC hdc;
// SIZE slider_size;
HWND slider_ctrl = NULL;

            retc = KpCreateStaticRaw(hKpInstance, hwndDlg, &slider_ctrl, null,
               KPSBMP_BMP_X, bmp_pars->m_iBmpHgt, bmp_pars->m_iBmpWdt, KP_PROGRESS_HGT /* KPW_SLIDER_HGT */, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

// ----------------------
//          if(SUCCEEDED(retc))
//             if(!GetBitmapDimensionEx(bmp_pars->m_hSliderBmp, &slider_size))
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc)) hdc=GetWindowDC(hwndDlg /* HWND_DESKTOP */);

#if TRUE // FALSE
            if(SUCCEEDED(retc))
            {
               memset(&bmp_info, 0 , sizeof(bmp_info));
               bmp_info.bmiHeader.biSize = sizeof(bmp_info);
#ifdef Debug
// PutLogMessage_("%lx %lx", hdc, bmp_pars->m_hSliderBmp);
#endif
               if(!GetDIBits(hdc, bmp_pars->m_hSliderBmp, 0, 0, NULL, &bmp_info, DIB_RGB_COLORS))
               {
// Win98 pas ?ydr?n_ neveikia
// pas mane nesuveikia antr? kart? // dabar jau veikia – pad?jo bmp_info i?valymas
// pas ?ydr?n_ meta ? ekran?
#ifdef Debug
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
                  bmp_info.bmiHeader.biWidth = 2000; // 1280; // 640;
                  bmp_info.bmiHeader.biHeight = KP_PROGRESS_HGT; // 10; // 152;
               }
            }
#else
            if(SUCCEEDED(retc))
               if(!GetBitmapDimensionEx(bmp_pars->m_hSliderBmp, &bmp_dim))
               {
// Win98 pas ?ydr?n_ neveikia
// pas ?ydr?n_ meta ? ekran?
//                retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                  bmp_dim.cx = 1280; // 640;
                  bmp_dim.cy = KP_PROGRESS_HGT; // 10; // 152;
               }
#endif

// --------------
            if(SUCCEEDED(retc))
               retc = KpCreateBitmap(hKpInstance, slider_ctrl, &slider_bmp,
                  bmp_pars->m_hSliderBmp,
                  (bmp_pars->m_iBmpWdt < bmp_info.bmiHeader.biWidth / 2)?
                     (-(bmp_info.bmiHeader.biWidth / 2)):
                     (bmp_pars->m_iBmpWdt - bmp_info.bmiHeader.biWidth), // bmp_dim.cx,
                  0,
                  bmp_pars->m_iBmpWdt,
                  bmp_info.bmiHeader.biHeight /* bmp_dim.cy */, // slider_size.cy,
                  0 /* WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE */);

         } // if(bmp_pars->m_bShowSlider)

#if FALSE
// ------------------------------------ kp_wnd/pub_dlg k?rimas i?keltas ? ShowBmp(); inicijavimas ir registravimas – ?ia
         KP_NEWO(kp_wnd, KpWnd(hwndDlg, TYP_KpBitmap, null, NULL,
               hKpInstance, NULL, NULL, KPW_CONTROL_STYLE_NORMAL,
               bmp_info.bmiHeader.biWidth, // bmp_dim.cx, // bmp_pars->m_iBmpWdt,
               bmp_info.bmiHeader.biHeight, // bmp_dim.cy, // slider_size.cy,
               1, 1, 0, 0, slider_bmp,
               bmp_pars->m_hBitmapCtrl, bmp_pars->m_hBitMap, bmp_pars->m_iBitmapCnt, bmp_pars->m_plpszBmpList, bmp_pars->m_iaBmpTimes,
               bmp_pars->m_iBmpWdt, bmp_pars->m_iBmpHgt));
#else
         if(SUCCEEDED(retc))
         {
            pub_dlg->m_hWndHandle = hwndDlg;
            pub_dlg->m_hMDI_Client = slider_bmp;

            pub_dlg->m_iWdtDots = bmp_info.bmiHeader.biWidth; // wnd_dx // bmp_dim.cx // bmp_pars->m_iBmpWdt
            pub_dlg->m_iHgtDots = bmp_info.bmiHeader.biHeight; // wnd_dy // bmp_dim.cy, // slider_size.cy
         }
#endif

         if(SUCCEEDED(retc)) pub_dlg /* kp_wnd */->InitSliderCoords();
         if(SUCCEEDED(retc)) pub_dlg /* kp_wnd */->CalcSliderSteps(bmp_pars->m_iProlShowTime); // , True);

         if(SUCCEEDED(retc)) if(bmp_pars /* pub_dlg */ /* kp_wnd */->m_iBitmapCnt > 1)
         {
            KP_ASSERT(bmp_pars /* pub_dlg */ /* kp_wnd */->m_plpszBmpList != NULL, E_INVALIDARG, null, True);
            KP_ASSERT(bmp_pars /* pub_dlg */ /* kp_wnd */->m_iaBmpTimes != NULL, E_INVALIDARG, null, True);
            pub_dlg /* kp_wnd */->m_iCurBmp = 0;
            if(SUCCEEDED(retc)) /* m_iPrologTimer = */ SetTimer(hwndDlg /* HWND_DESKTOP */, KPST_PROLOG_TIMER, bmp_pars /* pub_dlg */ /* kp_wnd */->m_iaBmpTimes[pub_dlg /* kp_wnd */->m_iCurBmp], NULL);
//          KP_ASSERT(m_iPrologTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
         }

         if(SUCCEEDED(retc))
         {
            retc = WndPreg(pub_dlg /* kp_wnd */, TYP_KpDialog /* TYP_KpBitmap */, hKpInstance, NULL, False);
            if(SUCCEEDED(retc)) pub_dlg /* kp_wnd */ = NULL;
         }

      } // if((bmp_pars->m_bShowSlider) || (bmp_pars->m_iBitmapCnt > 1))

      if(SUCCEEDED(retc)) if(SetTimer(hwndDlg, KP_REDRAW_TIMER, KP_SLIDER_TIMEOUT /* 30 */ /* 50 */ /* KP_REDRAW_TIMEOUT */, NULL)==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

// ----------------- ?ia tik nuoroda ? pub_dlg->m_pBmpPars, trinamas naikinant pub_dlg
//    KP_DELETE(bmp_pars);

// ----- kp_wnd/pub_dlg k?rimas i?keltas ? ShowBmp(); inicijavimas ir registravimas – ?ia
//    KP_DELETE(kp_wnd);

      break;
// #endif


   case WM_TIMER:
      if((LOWORD(wParam) == KP_REDRAW_TIMER) && SUCCEEDED(retc))
      {
         retc = GetCurWindow(&pub_dlg /* kp_wnd */, hwndDlg);
//       KP_ASSERT(pub_dlg /* kp_wnd */ != NULL, KP_E_SYSTEM_ERROR, null, True);
         if(pub_dlg != NULL)
         {
            KP_ASSERT(pub_dlg /* kp_wnd */->m_iWndType == TYP_KpDialog /* TYP_KpBitmap */, KP_E_SYSTEM_ERROR, null, True);

            KP_ASSERT(pub_dlg /* kp_wnd */->m_hMDI_Client, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc))
            {
//             pub_dlg /* kp_wnd */->m_iWndX += 3; // 1;
//             if(pub_dlg /* kp_wnd */->m_iWndX > 0) pub_dlg /* kp_wnd */->m_iWndX = pub_dlg /* kp_wnd */->m_iParentWdtDots - pub_dlg /* kp_wnd */->m_iWdtDots;
               pub_dlg /* kp_wnd */->m_iWndX_10 += pub_dlg /* kp_wnd */->m_iWndXStep_10;
               if((pub_dlg /* kp_wnd */->m_iWndX_10 > 0) || (pub_dlg /* kp_wnd */->m_iWndX_10 > pub_dlg /* kp_wnd */->m_iParentWdtDots * 10 - pub_dlg /* kp_wnd */->m_iWdtDots * 10 / 2))
               {
                  if(pub_dlg /* kp_wnd */->m_iWndXStep_10) pub_dlg /* kp_wnd */->InitSliderCoords(); // sukam nuo prad?i¸ tik kai valdo taimeris
                  else pub_dlg /* kp_wnd */->m_iWndX_10 = 0;
               }
               pub_dlg /* kp_wnd */->m_iWndX = pub_dlg /* kp_wnd */->m_iWndX_10 / 10;

//             pub_dlg /* kp_wnd */->m_iWndY -= 1; // 2;
//             if(pub_dlg /* kp_wnd */->m_iWndY < -(pub_dlg /* kp_wnd */->m_iHgtDots - KPW_SLIDER_HGT)) pub_dlg /* kp_wnd */->m_iWndY = 0;
               pub_dlg /* kp_wnd */->m_iWndY_10 -= pub_dlg /* kp_wnd */->m_iWndYStep_10;
               if(pub_dlg /* kp_wnd */->m_iWndY_10 < -(pub_dlg /* kp_wnd */->m_iHgtDots - KPW_SLIDER_HGT) * 10) pub_dlg /* kp_wnd */->m_iWndY_10 = 0;
               pub_dlg /* kp_wnd */->m_iWndY = pub_dlg /* kp_wnd */->m_iWndY_10 / 10;

               if(!SetWindowPos(pub_dlg /* kp_wnd */->m_hMDI_Client, 0,
                  pub_dlg /* kp_wnd */->m_iWndX, pub_dlg /* kp_wnd */->m_iWndY,
                  pub_dlg /* kp_wnd */->m_iWdtDots, KPW_SLIDER_HGT, SWP_NOREPOSITION|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREDRAW))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc))
            {
               rect.left = 0;
               rect.top = - pub_dlg /* kp_wnd */->m_iWndY; // 0;
               rect.right = pub_dlg /* kp_wnd */->m_iWdtDots;
               rect.bottom = - pub_dlg /* kp_wnd */->m_iWndY + KPW_SLIDER_HGT; // pub_dlg /* kp_wnd */->m_iHgtDots;
               if(!InvalidateRect(pub_dlg /* kp_wnd */->m_hMDI_Client, &rect, False))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
            }

         } // if(pub_dlg != NULL)
      }

      if((LOWORD(wParam) == KPST_PROLOG_TIMER) && SUCCEEDED(retc))
      {
         retc = GetCurWindow(&pub_dlg /* kp_wnd */, hwndDlg);
//       KP_ASSERT(pub_dlg /* kp_wnd */ != NULL, KP_E_SYSTEM_ERROR, null, True);
         if(pub_dlg != NULL)
         {
            KP_ASSERT(pub_dlg /* kp_wnd */->m_iWndType == TYP_KpDialog /* TYP_KpBitmap */, KP_E_SYSTEM_ERROR, null, True);

            KP_ASSERT(pub_dlg /* kp_wnd */->m_pBmpPars != NULL, KP_E_SYSTEM_ERROR, null, True);

            KP_ASSERT(pub_dlg /* kp_wnd */->m_pBmpPars->m_plpszBmpList != NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(pub_dlg /* kp_wnd */->m_phBmpList != NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(pub_dlg /* kp_wnd */->m_pBmpPars->m_hBitmapCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);
            KP_ASSERT(pub_dlg /* kp_wnd */->m_pBmpPars->m_iaBmpTimes != NULL, KP_E_SYSTEM_ERROR, null, True);
            if(SUCCEEDED(retc))
            {
               pub_dlg /* kp_wnd */->m_iCurBmp++;
               if(pub_dlg /* kp_wnd */->m_iCurBmp >= pub_dlg /* kp_wnd */->m_pBmpPars->m_iBitmapCnt) pub_dlg /* kp_wnd */->m_iCurBmp = 0;

               bitmap = pub_dlg /* kp_wnd */->m_phBmpList[pub_dlg /* kp_wnd */->m_iCurBmp];
               if(bitmap == NULL)
               {
                  KP_ASSERT(pub_dlg /* kp_wnd */->m_pBmpPars->m_plpszBmpList[pub_dlg /* kp_wnd */->m_iCurBmp] != NULL, KP_E_SYSTEM_ERROR, null, True);
                  bitmap = (HBITMAP)LoadImage(GetModuleHandle(0), (const char *)(pub_dlg /* kp_wnd */->m_pBmpPars->m_plpszBmpList[pub_dlg /* kp_wnd */->m_iCurBmp]),
                                                 IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
                  KP_ASSERT(bitmap, KP_E_FILE_NOT_FOUND, GetLastError(), True);
if(FAILED(retc))
{
static unsigned char dir_buf[KP_MAX_FNAME_LEN+1];
GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf);
PutLogMessage_("%d %d [%s] [%s] [%s]", pub_dlg /* kp_wnd */->m_iCurBmp, pub_dlg /* kp_wnd */->m_pBmpPars->m_iBitmapCnt, (const unsigned char *)(pub_dlg /* kp_wnd */->m_pBmpPars->m_plpszBmpList[pub_dlg /* kp_wnd */->m_iCurBmp]), (const unsigned char *)(pub_dlg /* kp_wnd */->m_pBmpPars->m_plpszBmpList[0]), dir_buf);
}

                  if(SUCCEEDED(retc)) pub_dlg /* kp_wnd */->m_phBmpList[pub_dlg /* kp_wnd */->m_iCurBmp] = bitmap;
               }
            }
            if(SUCCEEDED(retc)) SendMessage(pub_dlg /* kp_wnd */->m_pBmpPars->m_hBitmapCtrl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap);

            if(SUCCEEDED(retc)) SetTimer(hwndDlg /* HWND_DESKTOP */, KPST_PROLOG_TIMER, pub_dlg /* kp_wnd */->m_pBmpPars->m_iaBmpTimes[pub_dlg /* kp_wnd */->m_iCurBmp], NULL);

         } // if(pub_dlg != NULL)

      }
      break;


#if FALSE
   case WM_MOUSEMOVE:
// ----------------- mygtuku gesinimas
      prew_mouse_over = hMouseOverWnd;
      if(prew_mouse_over) // !=hwndDlg)
      {
         hMouseOverWnd = NULL; // hwndDlg;
//       if(prew_mouse_over)
            if(!InvalidateRect(prew_mouse_over, 0, TRUE))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif
            }
      }
      break;
#endif

// -------------------
   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case KP_ID_MUTE: // ?ia mute apdoroti negalima – dvigubi kreipiniai i? kito threado nulau?ia kphp11
         PostThreadMessage(iKpMainThread, uMsg, wParam, lParam);
         break;
      }
      break;

// -------------------
   case WM_CLOSE:
      PostQuitMessage(IDCANCEL);
   case WM_DESTROY: // ateina tik ?itas
   case WM_QUIT:
// KP_WARNING(S_OK, (uMsg == WM_CLOSE)?"KpStShBmpProc(): WM_CLOSE":((uMsg == WM_DESTROY)?"KpStShBmpProc(): WM_DESTROY":"KpStShBmpProc(): WM_QUIT"));

      KillTimer(hwndDlg, KP_REDRAW_TIMER);

// KpMsgOut("KpStShBmpProc:WM_CLOSE", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// naikinam visus susijusius KpWnd su bitmapais
// nereikia – naikinamas KpWndList::~KpWndList(), jeigu ?iuo metu baigin?jasi ir programa – susidubliuoja
// reikia – KpWndList::~KpWndList() nenaikina TYP_KpDialog tipo langø
// !!!!!!! TODO: ka_kaip pasemaforuot KpWndList::~KpWndList() ar palaukt, kol ShowBmp() langas u_sidarys
#if FALSE
      kp_wnd = NULL;
      if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hwndDlg);
      if(kp_wnd && SUCCEEDED(retc))
      {
//       KP_ASSERT(kp_wnd, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(kp_wnd->m_hMDI_Client, KP_E_SYSTEM_ERROR, null, False);

         kp_slider_wnd = NULL;
         if(kp_wnd->m_hMDI_Client && SUCCEEDED(retc))
         {
            retc = GetCurWindow(&kp_slider_wnd, kp_wnd->m_hMDI_Client);
            KP_ASSERT(kp_slider_wnd, KP_E_SYSTEM_ERROR, null, False);
            if((kp_slider_wnd != NULL) && SUCCEEDED(retc))
            {
               retc = DeleteWnd(kp_slider_wnd);
               KP_DELETE(kp_slider_wnd);
               kp_wnd->m_hMDI_Client = NULL;
            }
         }

         kp_wnd->m_hWndHandle = NULL;

         if(SUCCEEDED(retc)) retc = DeleteWnd(kp_wnd);
         KP_DELETE(kp_wnd);
      }
#elseif FALSE
      pub_dlg = NULL;
      if(FAILED(GetCurWindow(&pub_dlg, hwndDlg))) pub_dlg = NULL;
      if(pub_dlg != NULL)
      {
         pub_dlg->m_hWndHandle = NULL;

         retc = DeleteWnd(pub_dlg);
         KP_DELETE(pub_dlg);
      }
#endif
      break;

   default:
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(SUCCEEDED(retc)) /* retb = */ KpPubDialogProc(hwndDlg, uMsg, wParam, lParam);

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


// =======================================
extern HRESULT KpCreateProgressWnd(HWND *phProgressWnd, const unsigned char *lpszMsgTxt, int iSliderShowTime, long lFullSize)
{
HRESULT retc = S_OK;
WNDCLASSEX wcx;
int wnd_x = 0;
int wnd_y = 0;
int wnd_dx = 0;
int wnd_dy = 0;
HDC hdc;
KpBmpData *bmp_pars = NULL;
// static BITMAPINFO bmp_info;
// SIZE bmp_dim;

// --------------------------
   KP_ASSERT(hKpInstance, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(phProgressWnd, E_INVALIDARG, null, True);

// -------------------------- lango klas?
   if(SUCCEEDED(retc))
   {
      wcx.hInstance     = hKpInstance;
      wcx.lpszClassName = "KPPROGRESS",
      wcx.lpfnWndProc   = (WNDPROC)KpProgressDialogProc;
      wcx.style         = CS_DBLCLKS;
      wcx.cbSize        = sizeof(WNDCLASSEX);
      wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, IDI_INFORMATION /* IDI_ASTERISK */); // MAKEINTRESOURCE(/* lpszIconID */ IDI_INFORMATION /* IDI_ASTERISK */));
      wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, IDI_INFORMATION /* IDI_ASTERISK */); // MAKEINTRESOURCE(/* lpszIconID */ IDI_INFORMATION /* IDI_ASTERISK */));
      wcx.hCursor       = LoadCursor(NULL, IDC_WAIT); // IDC_ARROW);
      wcx.lpszMenuName  = 0;
      wcx.cbClsExtra    = 0;
      wcx.cbWndExtra    = 0;
      wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm]));

      if(!RegisterClassEx(&wcx))
      {
         long ll = GetLastError();
         if(ll != ERROR_CLASS_ALREADY_EXISTS)
            KP_ERROR(KP_E_SYSTEM_ERROR, ll);
      }
   }

// -------------------------- slankiklio bitmapas
   KP_NEW(bmp_pars, KpBmpData(KP_PROGRESS_WDT, KPW_SLIDER_HGT));

#if FALSE
   if(SUCCEEDED(retc))
   {
      bmp_pars->m_hSliderBmp = (hKpInstance, MAKEINTRESOURCE(KP_IDI_SLIDER_2_BMP));
//    bmp_pars->m_hSliderBmp = (HBITMAP)LoadImage(hKpInstance, MAKEINTRESOURCE(KP_IDI_SLIDER_2_BMP), IMAGE_BITMAP,
//                                  0, 0, LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
      KP_ASSERT(bmp_pars->m_hSliderBmp, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }
#endif
   if(SUCCEEDED(retc))
   {
      bmp_pars->m_lpszMsgTxt = lpszMsgTxt;
      bmp_pars->m_iProlShowTime = iSliderShowTime;
      bmp_pars->m_lFullSize = lFullSize;
   }

// -------------------------- hdc
   if(SUCCEEDED(retc))
   {
      hdc = GetDC(HWND_DESKTOP);
      if(hdc == NULL)
      {
#ifdef Debug
         KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());
#endif
         retc = KP_E_SYSTEM_ERROR;
      }
   }

// -------------------------- slankiklio dydis
#if FALSE
#if TRUE // FALSE
   bmp_info.bmiHeader.biSize = sizeof(bmp_info);

   if(SUCCEEDED(retc))
      if(!GetDIBits(hdc, bmp_pars->m_hSliderBmp, 0, 0, NULL, &bmp_info, DIB_RGB_COLORS))
      {
// Win98 pas ?ydr?n_ neveikia
// pas ?ydr?n_ meta ? ekran?
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         bmp_info.bmiHeader.biWidth = 1280;
         bmp_info.bmiHeader.biHeight = KP_PROGRESS_HGT; // 10;
      }

   if(SUCCEEDED(retc))
   {
      bmp_pars->m_iBmpWdt = bmp_info.bmiHeader.biWidth;
      bmp_pars->m_iBmpHgt = bmp_info.bmiHeader.biHeight;
   }
#else
   if(SUCCEEDED(retc))
      if(!GetBitmapDimensionEx(bmp_pars->m_hSliderBmp, &bmp_dim))
      {
// Win98 pas ?ydr?n_ neveikia
// pas ?ydr?n_ meta ? ekran?
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         bmp_dim.cx = 1280;
         bmp_dim.cy = KP_PROGRESS_HGT; // 10;
      }

   if(SUCCEEDED(retc))
   {
      bmp_pars->m_iBmpWdt = bmp_dim.cx;
      bmp_pars->m_iBmpHgt = bmp_dim.cy;
   }
#endif
#endif

// -------------------------- lango dydis
   if(SUCCEEDED(retc))
   {
      wnd_dx = iWndBorderWdt + KPW_WND_HOR_MARGIN + KP_PROGRESS_WDT + KPW_WND_HOR_MARGIN + iWndBorderWdt;
      wnd_dy = iWndBorderWdt + iWndCaptionHgt + KPW_WND_VER_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] +
         KPW_CTRL_MARGIN + KP_PROGRESS_HGT /* bmp_pars->m_iBmpHgt */ + KPW_WND_VER_MARGIN + iWndBorderWdt;
      wnd_x = (GetDeviceCaps(hdc, HORZRES) - wnd_dx)/2;
      wnd_y = (GetDeviceCaps(hdc, VERTRES) - wnd_dy)/2;
   }


// if(SUCCEEDED(retc)) KP_TRACE_("KpCreateProgressWnd() %d", bmp_pars->m_iBmpWdt);

// -------------------------- kuriam lang?
   if(SUCCEEDED(retc))
   {
      *phProgressWnd = CreateWindowEx
      (
         0,               // DWORD dwExStyle,      // extended window style
         "KPPROGRESS",
         (const char *)KP_PROGRESS_TITLE,   // LPCTSTR lpWindowName, // pointer to window name
         WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME,   // DWORD dwStyle,        // window style
         wnd_x, // CW_USEDEFAULT // int x,               // horizontal position of window

         wnd_y, // CW_USEDEFAULT // int y,               // vertical position of window
         wnd_dx,                 // int nWidth,           // window width
         wnd_dy,                 // int nHeight,          // window height
         HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
         0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
         hKpInstance,
         bmp_pars  // LPVOID lpParam        // pointer to window-creation data
      );

      if(*phProgressWnd == NULL)
      {
#ifdef Debug
         KP_ERROR(KP_E_SYSTEM_ERROR, GetLastError());
#endif
         retc = KP_E_SYSTEM_ERROR;
      }
   }

return(retc);
}


BOOL CALLBACK KpProgressDialogProc(
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
CREATESTRUCT *csp = NULL;
KpBmpData *bmp_pars = NULL;
HWND msg_ctrl = NULL;
HWND progress_msg_ctrl = NULL;
HWND slider_bmp = NULL;
KpWnd *kp_wnd = NULL;

   retp = LOWORD(wParam);
   endfl = False;

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
      if((hKpInstance == NULL) && SUCCEEDED(retc))
      {
//       KP_ERROR(KP_E_SYSTEM_ERROR, null, True);
         retc = KP_E_SYSTEM_ERROR;
      }

// -----------------
      if(SUCCEEDED(retc))
      {
         csp = (LPCREATESTRUCT)lParam;
         KP_ASSERT(csp, KP_E_SYSTEM_ERROR, null, True);
      }
      if(SUCCEEDED(retc))
      {
         bmp_pars = (KpBmpData *)csp->lpCreateParams;
         KP_ASSERT(bmp_pars, KP_E_SYSTEM_ERROR, null, True);
      }

// -----------------
      if(SUCCEEDED(retc)) retc = KpCreateStaticRaw(hKpInstance, hwndDlg, &msg_ctrl, bmp_pars->m_lpszMsgTxt,
                                    KPW_WND_HOR_MARGIN, KPW_WND_VER_MARGIN,
                                    KP_PROGRESS_WDT - KP_PROGRESS_MSG_WDT, iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL],
                                    KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      KP_ASSERT(msg_ctrl != NULL, KP_E_SYSTEM_ERROR, null, True);

#if FALSE
      if(SUCCEEDED(retc)) retc = KpCreateStaticRaw(hKpInstance, hwndDlg, &progress_msg_ctrl, (const unsigned char *)"",
                                    KPW_WND_HOR_MARGIN + (KP_PROGRESS_WDT - KP_PROGRESS_MSG_WDT), KPW_WND_VER_MARGIN,
                                    KP_PROGRESS_MSG_WDT, iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL], // KPW_CONTROL_STYLE_MONOSPACE
                                    KPW_CONTROL_STYLE_NORMAL, 0, SS_RIGHT, NULL); // KPW_CONTROL_STYLE_MONOSPACE
      KP_ASSERT(progress_msg_ctrl != NULL, KP_E_SYSTEM_ERROR, null, True);
#else
      if(SUCCEEDED(retc)) progress_msg_ctrl = CreateWindowEx(0L, "STATIC", "", WS_VISIBLE|WS_CHILD|SS_RIGHT,
                                    KPW_WND_HOR_MARGIN + (KP_PROGRESS_WDT - KP_PROGRESS_MSG_WDT), KPW_WND_VER_MARGIN,
                                    KP_PROGRESS_MSG_WDT, iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL],
                                    hwndDlg, NULL, hKpInstance, NULL);
      KP_ASSERT(progress_msg_ctrl != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc))
      {
HFONT hfont = NULL;
         if(SUCCEEDED(retc)) retc = CrFont(&hfont, KPW_CONTROL_STYLE_NORMAL);
         KP_ASSERT(hfont != NULL, KP_E_SYSTEM_ERROR, null, False);
         if(hfont != NULL)
            KP_ASSERT(PostMessage(progress_msg_ctrl, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(True, 0)),
               KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
#endif

#if FALSE
      if(SUCCEEDED(retc))
         retc = KpCreateBitmap(hKpInstance, hwndDlg, &slider_bmp, bmp_pars->m_hSliderBmp,
                                 KPW_WND_HOR_MARGIN,
                                 KPW_WND_VER_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + KPW_CTRL_MARGIN,
                                 KP_PROGRESS_WDT, bmp_pars->m_iBmpHgt,
                                 0 /* WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE */);
#else
      if(SUCCEEDED(retc)) retc = ShowBmp(null, KP_PROGRESS_WDT, 0, &slider_bmp, True,
                                    0, NULL, NULL, KP_IDI_SLIDER_2_BMP,
                                    bmp_pars->m_iProlShowTime,
                                    hwndDlg,
                                    KPW_WND_HOR_MARGIN,
                                    KPW_WND_VER_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + KPW_CTRL_MARGIN);
#endif
      KP_ASSERT(slider_bmp, KP_E_SYSTEM_ERROR, null, True);

      KP_NEWO(kp_wnd, KpWnd(hwndDlg, TYP_KpProgressWndw, null, NULL,
            hKpInstance, NULL, NULL, KPW_CONTROL_STYLE_NORMAL,
            100, 100, 1, 1, 0, 0,
            msg_ctrl, slider_bmp,
            NULL, 0, NULL, NULL, bmp_pars->m_iBmpWdt /* KPW_BMP_WDT */, bmp_pars->m_iBmpHgt /* KPW_BMP_HGT */,
            bmp_pars->m_lFullSize));

      if(SUCCEEDED(retc)) kp_wnd->m_hSubListBox = progress_msg_ctrl;

// if(SUCCEEDED(retc)) KP_TRACE_("KpProgressDialogProc() %lx %d %d", hwndDlg, bmp_pars->m_iBmpWdt, kp_wnd->m_iWdtDots);

      if(SUCCEEDED(retc))
      {
         retc = WndPreg(kp_wnd, TYP_KpProgressWndw, hKpInstance, NULL, False);
         if(SUCCEEDED(retc)) kp_wnd = NULL;
      }

// if(SUCCEEDED(retc)) KP_TRACE_("KpProgressDialogProc() %d %d", bmp_pars->m_iBmpWdt, kp_wnd->m_iWdtDots);

      KP_DELETE(bmp_pars);

      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

   case WM_CLOSE:
      retc = KP_E_CANCEL;
      endfl = True;
      retw = DefWindowProc(hwndDlg, uMsg, wParam, lParam);
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
      case IDCANCEL:
         retc=KP_E_CANCEL;
      case IDOK:
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

// paprastam endfl nereikia - tada lau?ia tolesn? prane?im¸ cikl? (KpSleep() KpMsgOut() gale)
   if(/* endfl || */ FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


HRESULT KillProgressWnd(HWND hProgressWnd)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
KpWnd *kp_wnd = NULL;

   if(hProgressWnd != NULL)
   {
      retc0 = GetCurWindow(&kp_wnd, hProgressWnd);
// PutLogMessage_("KillProgressWnd() %x", kp_wnd);
      if(SUCCEEDED(retc0)) if(kp_wnd) retc0 = DeleteWnd(kp_wnd);

//    ::DestroyWindow(hProgressWnd);

      KP_DELETE(kp_wnd); // DeleteWnd() neiðtrina, nes lango tipas TYP_KpProgressWndw
   }

return(retc);
}


HRESULT KpSetProgressTxt(HWND hProgressWnd, const unsigned char *lpszMsgTxt, const unsigned char *lpszProgressTxt)
{
HRESULT retc = S_OK;
KpWnd *kp_wnd = NULL;

   KP_ASSERT(hProgressWnd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hProgressWnd);
   KP_ASSERT(kp_wnd, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpProgressWndw, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_hMDI_Client, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_hSubListBox, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) if(!SetWindowText(kp_wnd->m_hMDI_Client, (const char *)lpszMsgTxt))
      KP_ERROR(KP_E_SYSTEM_ERROR, null);
   if(SUCCEEDED(retc)) if(!SetWindowText(kp_wnd->m_hSubListBox, (const char *)lpszProgressTxt))
      KP_ERROR(KP_E_SYSTEM_ERROR, null);

// if(SUCCEEDED(retc)) KP_TRACE_1("KpSetProgressTxt() %s", lpszMsgTxt);

return(retc);
}


HRESULT KpSetProgressTime(HWND hProgressWnd, int iProlTime)
{
HRESULT retc = S_OK;
KpWnd *kp_wnd = NULL;

   KP_ASSERT(hProgressWnd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hProgressWnd);
   KP_ASSERT(kp_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpProgressWndw, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(kp_wnd->m_pBmpPars != NULL, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(kp_wnd->m_pBmpPars->m_hBitmapCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);
   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, kp_wnd->m_pBmpPars->m_hBitmapCtrl);
   KP_ASSERT(kp_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpDialog /* TYP_KpBitmap */, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) kp_wnd->CalcSliderSteps(iProlTime); // , True);

return(retc);
}


HRESULT KpSetProgressPos(HWND hProgressWnd, int iPerCent)
{
HRESULT retc = S_OK;
KpWnd *kp_wnd = NULL;
RECT rect;
int perc;

// KP_ASSERT((iPerCent >= 0) && (iPerCent <= 100), E_INVALIDARG, null, True);
   perc = iPerCent;
   if(perc < 0) perc = 0;
   if(perc > 100) perc = 100;

   KP_ASSERT(hProgressWnd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hProgressWnd);
   KP_ASSERT(kp_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpProgressWndw, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(kp_wnd->m_pBmpPars != NULL, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(kp_wnd->m_pBmpPars->m_hBitmapCtrl != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_hSubListBox != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, kp_wnd->m_pBmpPars->m_hBitmapCtrl);
   KP_ASSERT(kp_wnd != NULL, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpDialog /* TYP_KpBitmap */, KP_E_SYSTEM_ERROR, null, True);

   KP_ASSERT(kp_wnd->m_hMDI_Client != NULL, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
// KP_TRACE_("KpSetProgressPos() %d %d %d", iPerCent, kp_wnd->m_iParentWdtDots, kp_wnd->m_iWdtDots);

      kp_wnd->m_iWndX_10 = (kp_wnd->m_iParentWdtDots <= kp_wnd->m_iWdtDots / 2)?
                              (
                                 -kp_wnd->m_iWdtDots * 10 / 2 +
                                 kp_wnd->m_iParentWdtDots * 10 * perc / 100
                              ):
                              (
                                 (kp_wnd->m_iParentWdtDots - kp_wnd->m_iWdtDots) * 10 * (100 - perc) / 100
                              );
      kp_wnd->m_iWndX = kp_wnd->m_iWndX_10 / 10;
   }

   if(SUCCEEDED(retc))
      if(!SetWindowPos(kp_wnd->m_hMDI_Client, 0,
         kp_wnd->m_iWndX, kp_wnd->m_iWndY,
         kp_wnd->m_iWdtDots, KPW_SLIDER_HGT, SWP_NOREPOSITION|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREDRAW))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      rect.left = 0;
      rect.top = -kp_wnd->m_iWndY; // 0;
      rect.right = kp_wnd->m_iWdtDots;
      rect.bottom = -kp_wnd->m_iWndY + KPW_SLIDER_HGT; // kp_wnd->m_iHgtDots;
      if(!InvalidateRect(kp_wnd->m_hMDI_Client, &rect, False))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
   }

// KpMsgOutF_3("%d %d %d", iPerCent, (kp_wnd->m_iWdtDots * 10 / 2), kp_wnd->m_iWndX_10);
// if(SUCCEEDED(retc)) KP_TRACE_1("KpSetProgressPos() percent: %d", iPerCent);

   if(SUCCEEDED(retc)) retc = KpProcMsgSimple();

return(retc);
}


HRESULT KpSetProgressPosAbs(HWND hProgressWnd, long lProcessedSize, long lFullSize)
{
HRESULT retc = S_OK;
KpWnd *kp_wnd = NULL;

   KP_ASSERT(hProgressWnd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hProgressWnd);
   KP_ASSERT(kp_wnd, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpProgressWndw, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      kp_wnd->m_lCurSliderPos = lProcessedSize;
      kp_wnd->m_lFullSliderSize = lFullSize;
      retc = KpSetProgressPos(hProgressWnd, (int)((lProcessedSize < Maxlong / 100L)? lProcessedSize * 100L / lFullSize : lProcessedSize / (lFullSize / 100L)));
   }

// if(SUCCEEDED(retc)) KP_TRACE_3("KpSetProgressPosAbs() cur_pos: %ld  full_size: %ld  percent: %ld", kp_wnd->m_lCurSliderPos, kp_wnd->m_lFullSliderSize, kp_wnd->m_lCurSliderPos * 100L / kp_wnd->m_lFullSliderSize);

return(retc);
}


HRESULT KpSetProgressPosInc(HWND hProgressWnd, long lIncrement)
{
HRESULT retc = S_OK;
KpWnd *kp_wnd = NULL;

   KP_ASSERT(hProgressWnd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hProgressWnd);
   KP_ASSERT(kp_wnd, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpProgressWndw, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
      retc = KpSetProgressPosAbs(hProgressWnd, kp_wnd->m_lCurFileStartPos + lIncrement, kp_wnd->m_lFullSliderSize);

// if(SUCCEEDED(retc)) KP_TRACE_3("KpSetProgressPosInc() cur_pos: %ld  full_size: %ld  percent: %ld", kp_wnd->m_lCurSliderPos, kp_wnd->m_lFullSliderSize, kp_wnd->m_lCurSliderPos * 100L / kp_wnd->m_lFullSliderSize);

return(retc);
}


HRESULT KpSetProgressFileStartPos(HWND hProgressWnd)
{
HRESULT retc = S_OK;
KpWnd *kp_wnd = NULL;

   KP_ASSERT(hProgressWnd, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetCurWindow(&kp_wnd, hProgressWnd);
   KP_ASSERT(kp_wnd, KP_E_SYSTEM_ERROR, null, True);
   KP_ASSERT(kp_wnd->m_iWndType == TYP_KpProgressWndw, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) kp_wnd->m_lCurFileStartPos = kp_wnd->m_lCurSliderPos;

// if(SUCCEEDED(retc)) KP_TRACE_1("KpSetProgressFileStartPos() file_start: %ld", kp_wnd->m_lCurFileStartPos);

return(retc);
}


// ------------------------
HRESULT KpProcMsgSimple(void)
{
HRESULT retc = S_OK;
MSG msg;

   Sleep(100);

   while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && SUCCEEDED(retc))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      if(msg.message == WM_QUIT)
      {
         switch(LOWORD(msg.wParam))
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         default: KP_ERROR(KP_E_SYSTEM_ERROR, null); break;
         }
      }
   }

return(retc);
}


DWORD CALLBACK KpCopyFileCallBack
(
  LARGE_INTEGER /* TotalFileSize */,
  LARGE_INTEGER TotalBytesTransferred,
  LARGE_INTEGER /* StreamSize */,
  LARGE_INTEGER /* StreamBytesTransferred */,
  DWORD /* dwStreamNumber */,
  DWORD /* dwCallbackReason */,
  HANDLE /* hSourceFile */,
  HANDLE /* hDestinationFile */,
  LPVOID lpData
)
{
// KP_TRACE("KpCopyFileCallBack");
   if(lpData)
   {
// KP_TRACE_1("KpCopyFileCallBack %lx", *(HWND *)lpData);
   /* retc = */ KpSetProgressPosInc(*(HWND *)lpData, TotalBytesTransferred.LowPart / 1000L);
   }

   KpProcMsgSimple();

return(PROGRESS_CONTINUE);
}


// ======================================= text
extern HDC GetDCSelFont(HWND hWnd)
{
HRESULT retc=S_OK;
HDC hdc;
KpWnd *cur_wnd;

   hdc=GetDC(hWnd);

   retc=GetCurWindow(&cur_wnd, hWnd);
   if(SUCCEEDED(retc))
      if(cur_wnd->m_iWndType==TYP_Static)
         if(cur_wnd->m_hFont!=NULL)
            if(SelectObject(hdc, cur_wnd->m_hFont)==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

return(hdc);
}


// -----------------------------------
HRESULT GetStrWidth(const unsigned char *lpszString, int *piWidth, HDC hdc)
{
HRESULT retc=S_OK;
int widths[KPT_Ctbsiz];
const unsigned char *pnts;

   if(piWidth==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!GetCharWidth(hdc, Nul, KPT_Ctbsiz-1, widths))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      *piWidth=0;
      if(lpszString!=NULL)
      {
         pnts=lpszString;
         while(*pnts) *piWidth+=widths[*pnts++];
      }
   }

return(retc);
}


// --------------------------------
HRESULT GetStrWidthABC(const unsigned char *lpszString, int *piWidth, HDC hdc)
{
HRESULT retc=S_OK;
int text_width;
ABC cur_wdt[2];
const unsigned char *pnts=NULL;
DWORD retw;

   if(piWidth==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      text_width=0;
      pnts=lpszString;
      if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc))
      {
         cur_wdt[0].abcA=0;
         cur_wdt[0].abcB=0;
         cur_wdt[0].abcC=0;
         if(GetCharABCWidths(hdc, *pnts, (*pnts)+1, cur_wdt))
            text_width+=cur_wdt[0].abcA+cur_wdt[0].abcB+cur_wdt[0].abcC;
         else
         {
            retw=GetLastError();
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }

         pnts++;
      }

      *piWidth=text_width;
   }

return(retc);
}


// --------------------------------
HRESULT GetStrWidthKp(const unsigned char *lpszString, int *piWidth, KpControlStyles iKpCtrlStyle)
{
HRESULT retc=S_OK;
int text_width;
const unsigned char *pnts=NULL;

   if((piWidth==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      text_width=0;
      pnts=lpszString;
      if(pnts!=NULL) while(*pnts)
      {
         text_width+=KpCharWidths[*pnts][iKpCtrlStyle];
         pnts++;
      }

      *piWidth=text_width;
   }

return(retc);
}


// --------------------------------
// charset 71, ISO 8859-13, Windows-1257
// 20 simboliu eilutes plotis milimetrais Worde
// srifto punktai - iaCtrlFntHghts[]/2 ???
// (siaip KPW_CONTROL_STYLE_NORMAL yra 10 pt, o iaCtrlFntHghts[]=16 ???)
// !!! dar nepabaigta
// pamatuoti KPW_CONTROL_STYLE_NORMAL pazymeti su N
// KPW_CONTROL_STYLE_COURIER jau teisingi visi
int KpCharWidths[KPT_Ctbsiz][KPW_NUM_OF_CONTROL_STYLES_2] =
{
   0,    0,    0,     0,   0,   //   C_Nul,            //   0 /* 0x00 */
   0,    0,    0,     0,   0,   //   C_Soh,            //   1 /* 0x01 */
   0,    0,    0,     0,   0,   //   C_Stx,            //   2 /* 0x02 */
   0,    0,    0,     0,   0,   //   C_Etx,            //   3 /* 0x03 */
   0,    0,    0,     0,   0,   //   C_Eot,            //   4 /* 0x04 */
   0,    0,    0,     0,   0,   //   C_Enq,            //   5 /* 0x05 */
   0,    0,    0,     0,   0,   //   C_Ack,            //   6 /* 0x06 */
   0,    0,    0,     0,   0,   //   C_Bel,            //   7 /* 0x07 */
   0,    0,    0,     0,   0,   //   C_Bs,             //   8 /* 0x08 */
   0,    0,    0,     0,   0,   //   C_Ht,             //   9 /* 0x09 */
   0,    0,    0,     0,   0,   //   C_Lf,             //  10 /* 0x0a */
   0,    0,    0,     0,   0,   //   C_Vt,             //  11 /* 0x0b */
   0,    0,    0,     0,   0,   //   C_Ff,             //  12 /* 0x0c */
   0,    0,    0,     0,   0,   //   C_Cr,             //  13 /* 0x0d */
   0,    0,    0,     0,   0,   //   C_So,             //  14 /* 0x0e */
   0,    0,    0,     0,   0,   //   C_Si,             //  15 /* 0x0f */
   0,    0,    0,     0,   0,   //   C_Dle,            //  16 /* 0x10 */
   0,    0,    0,     0,   0,   //   C_Dc1,            //  17 /* 0x11 */
   0,    0,    0,     0,   0,   //   C_Dc2,            //  18 /* 0x12 */
   0,    0,    0,     0,   0,   //   C_Dc3,            //  19 /* 0x13 */
   0,    0,    0,     0,   0,   //   C_Dc4,            //  20 /* 0x14 */
   0,    0,    0,     0,   0,   //   C_Nak,            //  21 /* 0x15 */
   0,    0,    0,     0,   0,   //   C_Syn,            //  22 /* 0x16 */
   0,    0,    0,     0,   0,   //   C_Etb,            //  23 /* 0x17 */
   0,    0,    0,     0,   0,   //   C_Can,            //  24 /* 0x18 */
   0,    0,    0,     0,   0,   //   C_Em,             //  25 /* 0x19 */
   0,    0,    0,     0,   0,   //   C_Sub,            //  26 /* 0x1a */
   0,    0,    0,     0,   0,   //   C_Esc,            //  27 /* 0x1b */
   0,    0,    0,     0,   0,   //   C_Fs,             //  28 /* 0x1c */
   0,    0,    0,     0,   0,   //   C_Gs,             //  29 /* 0x1d */
   0,    0,    0,     0,   0,   //   C_Rs,             //  30 /* 0x1e */
   0,    0,    0,     0,   0,   //   C_Us,             //  31 /* 0x1f */

   18,   43,   38,    18,  18,  // N  C_Spc,            //  32 /* Space */
   19,   43,   38,    19,  19,  // N  C_Excl,           //  33 /* !  Exclamation Mark (s/auktukas) */
   23,   43,   38,    23,  23,  // N  C_Quote,          //  34 /* "  Quotation Mark (kabute%s) */
   41,   43,   38,    41,  41,  // N  C_Numb,           //  35 /* #  Number Sign (Numerio zenklas) */
   31,   43,   38,    31,  31,  // N  C_Doll,           //  36 /* $  Currency Sign (Pinigu zenklas) */
   55,   43,   38,    55,  55,  // N  C_Perc,           //  37 /* %  Per Cent Sign (procento z/enklas) */
   38,   43,   38,    38,  38,  // N  C_Amp,            //  38 /* &  Ampersand (Ampersandas) */
   12,   43,   38,    12,  12,  // N  C_Apost,          //  39 /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   22,   43,   38,    22,  22,  // N  C_Lpar,           //  40 /* (  Left Parenthesis (kairysis skliaustas) */
   22,   43,   38,    22,  22,  // N  C_Rpar,           //  41 /* )  Right Parenthesis (des/inysis skliaustas) */
   31,   43,   38,    31,  31,  // N  C_Ast,            //  42 /* *  Asterisk (Zvaigzdute) */
   41,   43,   38,    41,  41,  // N  C_Plus,           //  43 /* +  Plus Sign (pliusas) */
   17,   43,   38,    17,  17,  // N  C_Comma,          //  44 /* ,  Comma (kablelis) */
   21,   43,   38,    21,  21,  // N  C_Minus,          //  45 /* -  Hyphen, Minus Sign (minusas) */
   17,   43,   38,    17,  17,  // N  C_Point,          //  46 /* .  Full Stop, Period, Point (tas/kas) */
   22,   43,   38,    22,  22,  // N  C_Slash,          //  47 /* /  Slash, Solidus (Istrizas bruksnys) */
   31,   43,   38,    31,  31,  // N  C_0,              //  48 /* 0 */
   31,   43,   38,    31,  31,  // N  C_1,              //  49 /* 1 */
   31,   43,   38,    31,  31,  // N  C_2,              //  50 /* 2 */
   31,   43,   38,    31,  31,  // N  C_3,              //  51 /* 3 */
   31,   43,   38,    31,  31,  // N  C_4,              //  52 /* 4 */
   31,   43,   38,    31,  31,  // N  C_5,              //  53 /* 5 */
   31,   43,   38,    31,  31,  // N  C_6,              //  54 /* 6 */
   31,   43,   38,    31,  31,  // N  C_7,              //  55 /* 7 */
   31,   43,   38,    31,  31,  // N  C_8,              //  56 /* 8 */
   31,   43,   38,    31,  31,  // N  C_9,              //  57 /* 9 */
   20,   43,   38,    20,  20,  // N  C_Colon,          //  58 /* :  Colon (dvitas/kis) */
   20,   43,   38,    20,  20,  // N  C_Semic,          //  59 /* ;  Semi-colon (kabliatas/kis) */
   41,   43,   38,    41,  41,  // N  C_Less,           //  60 /* <  Less than Sign (maz/iau) */
   41,   43,   38,    41,  41,  // N  C_Eq,             //  61 /* =  Equals Sign (lygybe%s z/enklas) */
   41,   43,   38,    41,  41,  // N  C_Great,          //  62 /* >  Greater than Sign (daugiau) */
   27,   43,   38,    27,  27,  // N  C_Quest,          //  63 /* ?  Question Mark (klaustukas) */

   51,   43,   38,    51,  51,  // N  C_At,             //  64 /* @  Commercial At (Prekybinis zenklas "Pas") */
   34,   43,   38,    34,  34,  // N  C_A,              //  65 /* A */
   33,   43,   38,    33,  33,  // N  C_B,              //  66 /* B */
   34,   43,   38,    34,  34,  // N  C_C,              //  67 /* C */
   38,   43,   38,    38,  38,  // N  C_D,              //  68 /* D */
   32,   43,   38,    32,  32,  // N  C_E,              //  69 /* E */
   29,   43,   38,    29,  29,  // N  C_F,              //  70 /* F */
   38,   43,   38,    38,  38,  // N  C_G,              //  71 /* G */
   38,   43,   38,    38,  38,  // N  C_H,              //  72 /* H */
   22,   43,   38,    22,  22,  // N  C_I,              //  73 /* I */
   24,   43,   38,    24,  24,  // N  C_J,              //  74 /* J */
   33,   43,   38,    33,  33,  // N  C_K,              //  75 /* K */
   28,   43,   38,    28,  28,  // N  C_L,              //  76 /* L */
   43,   43,   38,    43,  43,  // N  C_M,              //  77 /* M */
   37,   43,   38,    37,  37,  // N  C_N,              //  78 /* N */
   40,   43,   38,    40,  40,  // N  C_O,              //  79 /* O */
   31,   43,   38,    31,  31,  // N  C_P,              //  80 /* P */
   40,   43,   38,    40,  40,  // N  C_Q,              //  81 /* Q */
   35,   43,   38,    35,  35,  // N  C_R,              //  82 /* R */
   33,   43,   38,    33,  33,  // N  C_S,              //  83 /* S */
   33,   43,   38,    33,  33,  // N  C_T,              //  84 /* T */
   37,   43,   38,    37,  37,  // N  C_U,              //  85 /* U */
   34,   43,   38,    34,  34,  // N  C_V,              //  86 /* V */
   51,   43,   38,    51,  51,  // N  C_W,              //  87 /* W */
   33,   43,   38,    33,  33,  // N  C_X,              //  88 /* X */
   33,   43,   38,    33,  33,  // N  C_Y,              //  89 /* Y */
   32,   43,   38,    32,  32,  // N  C_Z,              //  90 /* Z */
   22,   43,   38,    22,  22,  // N  C_Lbrack,         //  91 /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   22,   43,   38,    22,  22,  // N  C_Lslash,         //  92 /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   22,   43,   38,    22,  22,  // N  C_Rbrack,         //  93 /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   41,   43,   38,    41,  41,  // N  C_Circ,           //  94 /* ^  Circumflex Accent (Cirkumfleksas), standalone */
   31,   43,   38,    31,  31,  // N  C_Underl,         //  95 /* _  Underline (Pabraukimas) */

   31,   43,   38,    31,  31,  // N  C_Grave,          //  96 /* `  Grave Accent (gravis), standalone */
   29,   43,   38,    29,  29,  // N  C_a,              //  97 /* a */
   31,   43,   38,    31,  31,  // N  C_b,              //  98 /* b */
   26,   43,   38,    26,  26,  // N  C_c,              //  99 /* c */
   31,   43,   38,    31,  31,  // N  C_d,              // 100 /* d */
   30,   43,   38,    30,  30,  // N  C_e,              // 101 /* e */
   18,   43,   38,    18,  18,  // N  C_f,              // 102 /* f */
   31,   43,   38,    31,  31,  // N  C_g,              // 103 /* g */
   31,   43,   38,    31,  31,  // N  C_h,              // 104 /* h */
   13,   43,   38,    13,  13,  // N  C_i,              // 105 /* i */
   16,   43,   38,    16,  16,  // N  C_j,              // 106 /* j */
   28,   43,   38,    28,  28,  // N  C_k,              // 107 /* k */
   13,   43,   38,    13,  13,  // N  C_l,              // 108 /* l */
   48,   43,   38,    48,  48,  // N  C_m,              // 109 /* m */
   32,   43,   38,    32,  32,  // N  C_n,              // 110 /* n */
   31,   43,   38,    31,  31,  // N  C_o,              // 111 /* o */
   32,   43,   38,    32,  32,  // N  C_p,              // 112 /* p */
   32,   43,   38,    32,  32,  // N  C_q,              // 113 /* q */
   21,   43,   38,    21,  21,  // N  C_r,              // 114 /* r */
   25,   43,   38,    25,  25,  // N  C_s,              // 115 /* s */
   19,   43,   38,    19,  19,  // N  C_t,              // 116 /* t */
   32,   43,   38,    32,  32,  // N  C_u,              // 117 /* u */
   28,   43,   38,    28,  28,  // N  C_v,              // 118 /* v */
   42,   43,   38,    42,  42,  // N  C_w,              // 119 /* w */
   28,   43,   38,    28,  28,  // N  C_x,              // 120 /* x */
   28,   43,   38,    28,  28,  // N  C_y,              // 121 /* y */
   25,   43,   38,    25,  25,  // N  C_z,              // 122 /* z */
   27,   43,   38,    27,  27,  // N  C_Lcurl,          // 123 /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   21,   43,   38,    21,  21,  // N  C_Vertl,          // 124 /* |  Vertical Line (Vertikali Linija), C_v_b */
   27,   43,   38,    27,  27,  // N  C_Rcurl,          // 125 /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   41,   43,   38,    41,  41,  // N  C_Tilde,          // 126 /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje), standalone */

   40,   43,   38,    40,  40,  // N  C_Del,            // 127


   40,   43,   38,    40,  40,  //   C_euro,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_LBapost,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_LBquote,
   40,   43,   38,    40,  40,  //   C_Dots,
   40,   43,   38,    40,  40,  //   C_Dag,
   40,   43,   38,    40,  40,  //   C_Ddag,

   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Prom,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Lang,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Noch,

   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Rapost,
   40,   43,   38,    40,  40,  //   C_LAapost,
   40,   43,   38,    40,  40,  //   C_Rquote,
   40,   43,   38,    40,  40,  //   C_LAquote,
   40,   43,   38,    40,  40,  //   C_Bpoint,
   40,   43,   38,    40,  40,  //   C_EnDash,
   40,   43,   38,    40,  40,  //   C_EmDash,

   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_TM,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Rang,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Noch,
   40,   43,   38,    40,  40,  //   C_Noch,

   40,   43,   38,    40,  40,  //   C_NBSP,
   40,   43,   38,    40,  40,  //   C_LAquote,
   40,   43,   38,    40,  40,  //   C_cent,
   40,   43,   38,    40,  40,  //   C_Pound,
   40,   43,   38,    40,  40,  //   C_Rouble,
   40,   43,   38,    40,  40,  //   C_LBquote,
   40,   43,   38,    40,  40,  //   C_Dvertl,
   40,   43,   38,    40,  40,  //   C_Para,

   40,   43,   38,    40,  40,  //   C_O_Slash,
   40,   43,   38,    40,  40,  //   C_CO,
   40,   43,   38,    40,  40,  //   C_R_Bcomma,
   40,   43,   38,    40,  40,  //   C_Ldopang,
   40,   43,   38,    40,  40,  //   C_Rminbr,
   40,   43,   38,    40,  40,  //   C_hyph/*!!!*/,
   40,   43,   38,    40,  40,  //   C_RO,
   40,   43,   38,    40,  40,  //   C_AE,

   40,   43,   38,    40,  40,  //   C_deg,
   40,   43,   38,    40,  40,  //   C_PlMin,
   40,   43,   38,    40,  40,  //   C_2up,
   40,   43,   38,    40,  40,  //   C_3up,
   40,   43,   38,    40,  40,  //   C_Rquote,
   40,   43,   38,    40,  40,  //   C_micro,
   40,   43,   38,    40,  40,  //   C_Pren,
   40,   43,   38,    40,  40,  //   C_Lpoint,

   40,   43,   38,    40,  40,  //   C_o_Slash,
   40,   43,   38,    40,  40,  //   C_1up,
   40,   43,   38,    40,  40,  //   C_r_Bcomma,
   40,   43,   38,    40,  40,  //   C_Rdopang,
   40,   43,   38,    40,  40,  //   C_Quart,
   40,   43,   38,    40,  40,  //   C_Half,
   40,   43,   38,    40,  40,  //   C_34,
   40,   43,   38,    40,  40,  //   C_ae,

   40,   43,   38,    40,  40,  //   C_A_Ogon,
   40,   43,   38,    40,  40,  //   C_I_Ogon,
   40,   43,   38,    40,  40,  //   C_A_Macr,
   40,   43,   38,    40,  40,  //   C_C_Acute,
   40,   43,   38,    40,  40,  //   C_A_Diaer,
   40,   43,   38,    40,  40,  //   C_A_Ring,
   40,   43,   38,    40,  40,  //   C_E_Ogon,
   40,   43,   38,    40,  40,  //   C_E_Macr,

   40,   43,   38,    40,  40,  //   C_C_Car,
   40,   43,   38,    40,  40,  //   C_E_Acute,
   40,   43,   38,    40,  40,  //   C_Z_Acute,
   40,   43,   38,    40,  40,  //   C_E_Adot,
   40,   43,   38,    40,  40,  //   C_G_Bcomma,
   40,   43,   38,    40,  40,  //   C_K_Bcomma,
   40,   43,   38,    40,  40,  //   C_I_Macr,
   40,   43,   38,    40,  40,  //   C_L_Bcomma,

   40,   43,   38,    40,  40,  //   C_S_Car,
   40,   43,   38,    40,  40,  //   C_N_Acute,
   40,   43,   38,    40,  40,  //   C_N_Bcomma,
   40,   43,   38,    40,  40,  //   C_O_Acute,
   40,   43,   38,    40,  40,  //   C_O_Macr,
   40,   43,   38,    40,  40,  //   C_O_Tilde,
   40,   43,   38,    40,  40,  //   C_O_Diaer,
   40,   43,   38,    40,  40,  //   C_Multipl,

   40,   43,   38,    40,  40,  //   C_U_Ogon,
   40,   43,   38,    40,  40,  //   C_L_Slash,
   40,   43,   38,    40,  40,  //   C_S_Acute,
   40,   43,   38,    40,  40,  //   C_U_Macr,
   40,   43,   38,    40,  40,  //   C_U_Diaer,
   40,   43,   38,    40,  40,  //   C_Z_Adot,
   40,   43,   38,    40,  40,  //   C_Z_Car,
   40,   43,   38,    40,  40,  //   C_ss,

   40,   43,   38,    40,  40,  //   C_a_Ogon,
   40,   43,   38,    40,  40,  //   C_i_Ogon,
   40,   43,   38,    40,  40,  //   C_a_Macr,
   40,   43,   38,    40,  40,  //   C_c_Acute,
   40,   43,   38,    40,  40,  //   C_a_Diaer,
   40,   43,   38,    40,  40,  //   C_a_Ring,
   40,   43,   38,    40,  40,  //   C_e_Ogon,
   40,   43,   38,    40,  40,  //   C_e_Macr,

   40,   43,   38,    40,  40,  //   C_c_Car,
   40,   43,   38,    40,  40,  //   C_e_Acute,
   40,   43,   38,    40,  40,  //   C_z_Acute,
   40,   43,   38,    40,  40,  //   C_e_Adot,
   40,   43,   38,    40,  40,  //   C_g_Bcomma/*C_g_Tacom*/,
   40,   43,   38,    40,  40,  //   C_k_Bcomma,
   40,   43,   38,    40,  40,  //   C_i_Macr,
   40,   43,   38,    40,  40,  //   C_l_Bcomma,

   40,   43,   38,    40,  40,  //   C_s_Car,
   40,   43,   38,    40,  40,  //   C_n_Acute,
   40,   43,   38,    40,  40,  //   C_n_Bcomma,
   40,   43,   38,    40,  40,  //   C_o_Acute,
   40,   43,   38,    40,  40,  //   C_o_Macr,
   40,   43,   38,    40,  40,  //   C_o_Tilde,
   40,   43,   38,    40,  40,  //   C_o_Diaer,
   40,   43,   38,    40,  40,  //   C_Divide,

   40,   43,   38,    40,  40,  //   C_u_Ogon,
   40,   43,   38,    40,  40,  //   C_l_Slash,
   40,   43,   38,    40,  40,  //   C_s_Acute,
   40,   43,   38,    40,  40,  //   C_u_Macr,
   40,   43,   38,    40,  40,  //   C_u_Diaer,
   40,   43,   38,    40,  40,  //   C_z_Adot,
   40,   43,   38,    40,  40,  //   C_z_Car,
   40,   43,   38,    40,  40,  //   C_LAapost
};


//================================================ mouse
HRESULT ExtractMouseXY(long lMouseXY, int *piMouseX, int *piMouseY)
{
HRESULT retc=S_OK;
int mouse_x=0;
int mouse_y=0;

   mouse_x=(lMouseXY&KPW_MOUSE_X_MASK)>>KPW_MOUSE_X_POS;
   mouse_y=(lMouseXY&KPW_MOUSE_Y_MASK)>>KPW_MOUSE_Y_POS;

   if(piMouseX!=NULL) *piMouseX=mouse_x;
   if(piMouseY!=NULL) *piMouseY=mouse_y;

return(retc);
}


// ============================================================ process functions
bool IsSoundFile(const unsigned char *lpszCmdLine)
{
HRESULT retc=S_OK;
bool retv = False;

   KP_ASSERT(lpszCmdLine, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
      if(strstr(lpszCmdLine, ".mp3") || strstr(lpszCmdLine, ".wma") || strstr(lpszCmdLine, ".wav") ||
         strstr(lpszCmdLine, ".m3u") || strstr(lpszCmdLine, ".wvl"))
            retv = True;

return(retv);
}


bool IsSoundFileProcessed(const unsigned char *lpszCmdLine)
{
HRESULT retc=S_OK;
bool retv = False;

   KP_ASSERT(lpszCmdLine, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
      if( // strstr(lpszCmdLine, ".mp3") || strstr(lpszCmdLine, ".wma") ||
         strstr(lpszCmdLine, ".wav") ||
//       strstr(lpszCmdLine, ".m3u") ||
         strstr(lpszCmdLine, ".wvl"))
            retv = True;

return(retv);
}


bool IsPlainTextFile(const unsigned char *lpszFName)
{
HRESULT retc=S_OK;
bool retv = False;

   KP_ASSERT(lpszFName, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
      if(strstr(lpszFName, ".txt") || strstr(lpszFName, ".inf") || strstr(lpszFName, ".log") ||
         strstr(lpszFName, ".csv") ||
         strstr(lpszFName, ".htm") || strstr(lpszFName, ".xml") || strstr(lpszFName, ".css") ||
         strstr(lpszFName, ".c") || strstr(lpszFName, ".h") || strstr(lpszFName, ".cc") || strstr(lpszFName, ".hh") ||
         strstr(lpszFName, ".pas") ||
         strstr(lpszFName, ".js") || strstr(lpszFName, ".java") ||
         strstr(lpszFName, ".iss") || strstr(lpszFName, ".isl"))
            retv = True;

return(retv);
}


HRESULT StartCmdProcess(unsigned char *lpszCmdLine, const unsigned char *lpszCurDir, DWORD *plThreadId, HANDLE *phProcess, bool bShowErrorMessages,
            WORD iWndShowType, WORD /* iSoundShowType */, bool bUseInternalViewer, const unsigned char *lpszStartCmdLine, bool bForceAcroMaximize
#if FALSE
            ,
#if CompilerGr==Mingw
               KpGeckoDialog
#else
               void
#endif
                  **ppDlgPtr
#endif
            , bool bOutMsg)
{
HRESULT retc = S_OK;
// WNDCLASSEX wcx;
// RECT wnd_rect;
// HDC dc;
int wnd_x = 0;
int wnd_y = 0;
static unsigned char fnam_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char full_fnam_buf[KP_MAX_FNAME_LEN + 1];
// static unsigned char ftype_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char key_name_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char key_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_buf[KP_MAX_FNAME_LEN * 2 + 1];
// static unsigned char rest_buf[KP_MAX_FNAME_LEN * 2 + 1];
static unsigned char dest_fname[KP_MAX_FNAME_LEN * 2 + 1];
static unsigned char src_fname[KP_MAX_FNAME_LEN * 2 + 1];
static unsigned char viewer_path[KP_MAX_FNAME_LEN * 2 + 1];
HKEY key;
HKEY key1;
// const unsigned char *pnt_ext;
static unsigned char pnt_ext[KP_MAX_FNAME_LEN+1];
// const unsigned char *pnt_next;
unsigned char *pntd;
const unsigned char *pnts;
unsigned char *pnt_par;
unsigned char *pnt_par_end;
const unsigned char *env_par;
DWORD buf_len;
DWORD val_type;
WORD show_type = iWndShowType;
bool processed = False;
int cmd_idx = -1;
BOOL cancel = False;

// PutLogMessage_("StartCmdProcess(): [%s] [%s]", lpszCmdLine, lpszCurDir);

   if(hKpInstance==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if((lpszCmdLine==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if((strlen(lpszCmdLine) == 0) || (strlen(lpszCmdLine) >= KP_MAX_FNAME_LEN))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

#ifdef Debug
// KpMsgOut("2.1 StartProcess", IDI_INFORMATION /* IDI_ASTERISK */);
#endif

   if(SUCCEEDED(retc))
   {
// -------------- fnam_buf
      strcpy(fnam_buf, lpszCmdLine);
      strlwr((char *)fnam_buf);

// -------------- full_fnam_buf
      if(strstr(fnam_buf, "http://") || strstr(fnam_buf, "https://") || strstr(fnam_buf, "ftp://") || strstr(fnam_buf, "sftp://") ||
         strstr(fnam_buf, "://"))
      {
         strncpy(full_fnam_buf, lpszCmdLine, KP_MAX_FNAME_LEN);
         full_fnam_buf[KP_MAX_FNAME_LEN] = Nul;
      }
      else
         KP_ASSERT(GetFullPathName((const char *)lpszCmdLine, KP_MAX_FNAME_LEN, (char *)full_fnam_buf, NULL), KP_E_SYSTEM_ERROR, GetLastError(), False);
   }

   if(SUCCEEDED(retc))
   {
// -------------- pnt_ext
      pnt_ext[0] = Nul;

      if(strstr(fnam_buf, ".exe") || strstr(fnam_buf, ".bin") || strstr(fnam_buf, ".com") || strstr(fnam_buf, ".bat"))
         strcpy(pnt_ext, ".exe");
      else if(strstr(fnam_buf, ".pdf") || strstr(fnam_buf, ".fdf") || strstr(fnam_buf, ".tev"))
         strcpy(pnt_ext, ".pdf");
      else if(strstr(fnam_buf, "http://") || strstr(fnam_buf, "https://") || strstr(fnam_buf, "ftp://") || strstr(fnam_buf, "sftp://") ||
          strstr(fnam_buf, ".htm") || strstr(fnam_buf, ".xhtm") || strstr(fnam_buf, ".php") || strstr(fnam_buf, ".asp"))
            strcpy(pnt_ext, ".htm");
      else if(strstr(fnam_buf, "dvd://") || strstr(fnam_buf, "mms://")) // "dvd://1" // "mms://..."
         strcpy(pnt_ext, ".wav");
      else
#if FALSE
      {
         pnt_ext = strchr(fnam_buf, '.');
#  if FALSE
         if(pnt_ext != NULL)
         {
// ie?kom paskutinio ta?ko
            do
            {
               pnt_next = strchr(pnt_ext+1, '.');
               if(pnt_next != NULL) pnt_ext = pnt_next;
            } while(pnt_next != NULL);

            strcpy(ftype_buf, pnt_ext);
            pnt_ext = ftype_buf;
            pntd = strchr(ftype_buf, Spc);
            if(pntd) *pntd = Nul;
         }
#  endif
      }

      if(pnt_ext == NULL) pnt_ext = (const unsigned char *)"";
#endif
#if FALSE
      {
// ie?kom pirmo ta?ko
         pnts = strchr(fnam_buf, '.');
         if(pnts)
         {
// bet ne "..\xxxx"
            if(*(pnts + 1) == '.') pnts++;
            if(*(pnts + 1) == '\\') pnts = strchr(pnts + 1, '.');
         }
         if(pnts)
         {
            strcpy(pnt_ext, pnts);

            pntd = strchr(pnt_ext, Spc); // ' '
            if(pntd) *pntd = Nul;
         }
         else pnt_ext[0] = Nul;
      }
#endif
#if FALSE
      {
         pnts = pntd = fnam_buf;
// ie?kom paskutinio ta?ko prie? tarp?
         do
         {
            if(*pntd == '.') pnts = pntd;

            if(*pntd == Spc) break; // ' '
            else pntd++;

         } while(*pntd);

         if(*pnts != '.') pnts = pntd;
         strcpy(pnt_ext, pnts);

         pntd = strchr(pnt_ext, Spc); // ' '
         if(pntd) *pntd = Nul;
      }
#endif
      {
         pnts = strchr(fnam_buf, '.');
// ie?kom paskutinio ta?ko
         if(pnts)
         {
            do
            {
               pntd = strchr(pnts + 1, '.');
               if(pntd) pnts = pntd;

            } while(pntd);

            strcpy(pnt_ext, pnts);

            pntd = strchr(pnt_ext, Spc); // ' '
            if(pntd) *pntd = Nul;
         }
         else pnt_ext[0] = Nul;
      }

   } // if(SUCCEEDED(retc))

// -------------- show_type
   if(SUCCEEDED(retc))
   {
      show_type = iWndShowType;
//    if(IsSoundFile(pnt_ext)) show_type = iSoundShowType /* SW_SHOWMINIMIZED */;
   }

// -------------------------
   processed = False;

// ----------------------------- internal viewers
// --------------------------------- .bmp
   if((!processed) && SUCCEEDED(retc)) if((strcmp(pnt_ext, ".bmp")==0) && bUseInternalViewer)
   {
#if FALSE
      if(SUCCEEDED(retc))
      {
         m_hBitMap=(HBITMAP)LoadImage(GetModuleHandle(0), (const char *)(m_Ini.lpszProlFName),
                                        IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
         if(m_hBitMap==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// ------------------------------
#  if TRUE
      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = m_hInstance;
         wcx.lpszClassName = "KPSBMP",
         wcx.lpfnWndProc   = (WNDPROC)KpStShBmpProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(NULL /* m_hInstance */, MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hIconSm       = LoadIcon(NULL /* m_hInstance */, MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hCursor       = LoadCursor(NULL, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)iaColorMap[KpShadowNorm];

            if(!RegisterClassEx(&wcx))
            {
               long ll = GetLastError();
               if(ll != ERROR_CLASS_ALREADY_EXISTS)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
            }
         }

         if(SUCCEEDED(retc))
         {
            dc=GetDC(HWND_DESKTOP);
            if(dc==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         wnd_x=(GetDeviceCaps(dc, HORZRES) - KPSBMP_WND_WDT(bmp_pars->m_iBmpWdt)) / 2;
         wnd_y=(GetDeviceCaps(dc, VERTRES) - KPSBMP_WND_HGT(bmp_pars->m_iBmpHgt)) / 2;

         m_hBitmapWindow=CreateWindowEx
            (
               0,                      // DWORD dwExStyle,      // extended window style
               "KPSBMP",
               "",                     // LPCTSTR lpWindowName, // pointer to window name
               WS_POPUPWINDOW|WS_VISIBLE|WS_BORDER, // |WS_THICKFRAME|WS_CAPTION|WS_POPUP, // DWORD dwStyle,        // window style
               wnd_x, // CW_USEDEFAULT, // int x,               // horizontal position of window
               wnd_y, // CW_USEDEFAULT, // int y,               // vertical position of window
               KPSBMP_WND_WDT(bmp_pars->m_iBmpWdt),         // int nWidth,           // window width
               KPSBMP_WND_HGT(bmp_pars->m_iBmpHgt),         // int nHeight,          // window height
               HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
               0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
               m_hInstance,
               this                    // LPVOID lpParam        // pointer to window-creation data
            );

         if(m_hBitmapWindow==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

#  else // #if TRUE
      if(SUCCEEDED(retc))
         retc=KpCreateBitmap(m_hInstance, HWND_DESKTOP, &m_hBitmapWindow,
            m_hBitMap, KPSBMP_BMP_X, KPSBMP_BMP_Y, bmp_pars->m_iBmpWdt, bmp_pars->m_iBmpHgt,
            0 /* WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE */);

#  endif // #else // #if TRUE

      if(SUCCEEDED(retc)) retc=KpSleep(200, HWND_DESKTOP);

#else // #if FALSE

// reikia ka?kaip ka?kada gesint bmp lang?, nes ?iaip pakimba
// be to, pasislepia po Acrobato langu
// gal u?komentuot visai?
      retc = ShowBmp(full_fnam_buf /* lpszCmdLine */, 0, 0, NULL, False);

#endif // else // #if FALSE

      processed = True;

   } // if((strcmp(pnt_ext, ".bmp")==0) && bUseInternalViewer && (!processed))

// --------------------------------- .htm
#if FALSE
#if CompilerGr==Mingw
   if((!processed) && SUCCEEDED(retc)) if((strcmp(pnt_ext, ".htm") == 0) && bUseInternalViewer)
   {
//    KP_ASSERT(ppDlgPtr != NULL, E_INVALIDARG, null, True);

      if(SUCCEEDED(retc))
      {
// TODO: perdaryt su iBshl
         KP_ERROR(E_NOTIMPL, null);
//       retc = ShowHtmXGecko(full_fnam_buf); // , ppDlgPtr);
         processed = True;
      }

   } // if((strcmp(pnt_ext, ".htm") == 0) && bUseInternalViewer && (!processed))
#endif
#endif

// -------------------------------- .wav
   if((!processed) && SUCCEEDED(retc)) if(IsSoundFileProcessed(pnt_ext) && bUseInternalViewer)
   {
      PlaySound((const char *)fnam_buf, NULL, SND_FILENAME|SND_ASYNC);
      if(plThreadId) *plThreadId = 0L;
      if(phProcess) *phProcess = NULL;

      processed = True;
   }

// -------------------------------- .pdf
   if((!processed) && SUCCEEDED(retc)) if(strcmp(pnt_ext, ".pdf") == 0)
   {
      if(SUCCEEDED(retc)) if(strlen(lpszStartCmdLine) >= KP_MAX_FNAME_LEN)
         retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszStartCmdLine, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_buf, lpszStartCmdLine);
         pntd = strstr(cmd_buf, KPST_ACROREAD_FNAME_SHORT);
         if(pntd != null)
         {
#if TRUE
            pntd += strlen(KPST_ACROREAD_FNAME);
            *pntd = Nul;

            strcat(cmd_buf, " /n \""); // " /n/h \"");
            strcat(cmd_buf, /* full_fnam_buf */ lpszCmdLine);
            strcat(cmd_buf, "\"");

#else // #if TRUE
            pntd = strstr(cmd_buf, ".pdf");
            if(pntd == null)
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               pnts = pntd + strlen(".pdf");
               if(*pnts == '\"'){ pnts++; while((*pntd != '\"') && (pntd > cmd_buf)) pntd--; }
               while((*pntd != Spc) && (pntd > cmd_buf)) pntd--;

               if(pntd == cmd_buf)
                  retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               *pntd = Nul;
               strcpy(rest_buf, pnts);

               if(strlen(cmd_buf) + strlen(/* full_fnam_buf */ lpszCmdLine) + strlen(rest_buf) + 1 >= KP_MAX_FNAME_LEN)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               strcat(cmd_buf, " \"");
               strcat(cmd_buf, /* full_fnam_buf */ lpszCmdLine);
               strcat(cmd_buf, "\"");
               strcat(cmd_buf, rest_buf);
            }
#endif
            if(SUCCEEDED(retc))
            {
// PutLogMessage((const unsigned char *)"StartCmdProcess() 1", null);
// PutLogMessage(cmd_buf, null);
// KpMsgOutF("StartCmdProcess() AcroRd32.exe: %s", cmd_buf);
// PutLogMessage_("StartCmdProcess() pdf: StartProcess(%s, %d)", cmd_buf, bForceAcroMaximize);
               retc = StartProcess(cmd_buf, lpszCurDir, plThreadId, phProcess, show_type /* iWndShowType */, bForceAcroMaximize, True, bOutMsg);

               processed = True;
            }

         } // if(pntd != null) // pntd = strstr(cmd_buf, KPST_ACROREAD_FNAME_SHORT);

      } // if(SUCCEEDED(retc))

   } // if((!processed) && SUCCEEDED(retc)) if(strcmp(pnt_ext, ".pdf") == 0)

// ----------------------------- external portable viewers
#if TRUE // FALSE
// -------------------------------- .exe
   if((!processed) && SUCCEEDED(retc)) if(strcmp(pnt_ext, ".exe") == 0)
   {
#if FALSE
PutLogMessage((const unsigned char *)"StartCmdProcess() 2", null);
PutLogMessage(lpszCmdLine, null);
PutLogMessage(lpszCurDir, null);
static unsigned char dir_buf[KP_MAX_FNAME_LEN + 1];
GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf);
PutLogMessage(dir_buf, null);

KpMsgOutF("StartCmdProcess() .exe: %s", lpszCmdLine);
#endif
      retc = StartProcess(/* full_fnam_buf */ lpszCmdLine, lpszCurDir, plThreadId, phProcess, show_type /* iWndShowType */, bForceAcroMaximize, True, bOutMsg);

      processed = True;
   }
#endif

#if FALSE
// ----------------------------- .jpg
   if((!processed) && SUCCEEDED(retc)) if(/* (strcmp(pnt_ext, ".bmp")==0) || */ (strcmp(pnt_ext, ".jpg")==0) || (strcmp(pnt_ext, ".tif")==0) || (strcmp(pnt_ext, ".gif")==0))
   {
      strcpy(cmd_buf, "i_view32.exe \"");
      strcat(cmd_buf, full_fnam_buf /* lpszCmdLine */);
      strcat(cmd_buf, "\"");

      retc = StartProcess(cmd_buf, lpszCurDir, plThreadId, phProcess, show_type /* iWndShowType */, bForceAcroMaximize, True, bOutMsg);

      processed = True;

   } // if((strcmp(pnt_ext, ".bmp")==0) || (strcmp(pnt_ext, ".jpg")==0) || (strcmp(pnt_ext, ".tif")==0) || (strcmp(pnt_ext, ".gif")==0))
#endif

   if((!processed) && SUCCEEDED(retc))
   {
      if(theKpStAppPtr) if(theKpStAppPtr->m_lpszaExtProcessed && theKpStAppPtr->m_lpszaExtViewers)
      {
         retc = GetKwrdIndex(&cmd_idx, pnt_ext, theKpStAppPtr->m_lpszaExtProcessed, -1, True, True);
         if(SUCCEEDED(retc))
         {
FILE *in_file = NULL;
            viewer_path[0] = Nul;
            strcpy(cmd_buf, viewer_path);
            strcat(cmd_buf, theKpStAppPtr->m_lpszaExtViewers[cmd_idx]);

//          if(theKpStAppPtr->m_lpszaExtViewers[cmd_idx][0]) // ne .exe
            {
               in_file = fopen((const char *)cmd_buf, "r"); // ie?kom ?alia

               if((in_file == NULL) /* && theKpStAppPtr */) // ie?kom dar ir atmintuko DAT0 kataloge
               {
                  strcpy(viewer_path, theKpStAppPtr->m_lpszFlashDevName);
                  strcat(viewer_path, "\\DAT0\\");

                  strcpy(cmd_buf, viewer_path);
                  strcat(cmd_buf, theKpStAppPtr->m_lpszaExtViewers[cmd_idx]);

                  in_file = fopen((const char *)cmd_buf, "r");
               }
            }

            if(in_file /* || (theKpStAppPtr->m_lpszaExtViewers[cmd_idx][0] == Nul) */) // arba .exe
            {
               if(in_file) fclose(in_file);

               if(strcmp(theKpStAppPtr->m_lpszaExtViewers[cmd_idx], "TMViewer\\TMViewer.dat") == 0)
               {
                  retc = GetLocalPath(dest_fname, KP_My_Documents, True);
                  if(SUCCEEDED(retc))
                  {
                     strcat(dest_fname, "SoftMaker\\Settings\\tmv09config.ini");

                     strcpy(src_fname, viewer_path);
                     strcat(src_fname, "TMViewer\\SoftMaker\\Settings\\tmv09config.ini");
                  }

                  if(SUCCEEDED(retc)) retc = CreatePath(dest_fname, False);
//                if(SUCCEEDED(retc)) if(!CopyFile((const char *)src_fname, (const char *)dest_fname, False))
//                   retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  KP_ASSERT(CopyFileEx((const char *)src_fname, (const char *)dest_fname, KpCopyFileCallBack, NULL, &cancel, 0L), KP_E_FERROR, GetLastError(), False);

                  retc = S_OK;
               }

            /* if(theKpStAppPtr->m_lpszaExtViewers[cmd_idx][0]) */ strcat(cmd_buf, " \""); // ne .exe
               strcat(cmd_buf, full_fnam_buf /* lpszCmdLine */);
            /* if(theKpStAppPtr->m_lpszaExtViewers[cmd_idx][0]) */ strcat(cmd_buf, "\""); // ne .exe

               retc = StartProcess(cmd_buf, lpszCurDir, plThreadId, phProcess, show_type /* iWndShowType */, bForceAcroMaximize, True, bOutMsg);

               processed = True;
            }

         } // if(SUCCEEDED(retc))

         if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;

      } // if(theKpStAppPtr) if(theKpStAppPtr->m_lpszaExtProcessed && theKpStAppPtr->m_lpszaExtViewers)

   } // if(!processed) // external portable viewers


// ------------------------------ the rest, default OS viewers
   if((!processed) && SUCCEEDED(retc))
   {
      if(ERROR_SUCCESS!=RegOpenKeyEx(HKEY_CLASSES_ROOT, (const char *)pnt_ext, 0, KEY_QUERY_VALUE, &key))
      {
         retc=KP_E_KWD_NOT_FOUND;
         if(bShowErrorMessages)
            retc=KpErrorProc.OutputErrorMessage(retc, pnt_ext, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      {
         buf_len=KP_MAX_FNAME_LEN;
         if(ERROR_SUCCESS==RegQueryValueEx(key, NULL, NULL, &val_type, key_buf, &buf_len))
            key_buf[buf_len]=Nul;
         else
         {
            retc=KP_E_KWD_NOT_FOUND;
            if(bShowErrorMessages)
               retc=KpErrorProc.OutputErrorMessage(retc, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(retc))
         {
// PutLogMessage_("StartCmdProcess() HKEY_CLASSES_ROOT: %s [%s]", pnt_ext, key_buf);
            sprintf((char *)key_name_buf, "%s\\shell\\open\\command", key_buf);
            if(ERROR_SUCCESS!=RegOpenKeyEx(HKEY_CLASSES_ROOT, (const char *)key_name_buf, 0, KEY_QUERY_VALUE, &key1))
            {
               retc=KP_E_KWD_NOT_FOUND;
               if(bShowErrorMessages)
                  retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc))
            {
               buf_len=KP_MAX_FNAME_LEN;
               if(ERROR_SUCCESS==RegQueryValueEx(key1, NULL, NULL, &val_type, key_buf, &buf_len))
                  key_buf[buf_len]=Nul;
               else
               {
                  retc=KP_E_KWD_NOT_FOUND;
                  if(bShowErrorMessages)
                     retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
                  if(strlen(full_fnam_buf /* lpszCmdLine */) + strlen(key_buf) + 1 >= KP_MAX_FNAME_LEN)
                     retc=KpErrorProc.OutputErrorMessage(E_OUTOFMEMORY, null, True, __FILE__, __LINE__, 0L, NULL);
// if(SUCCEEDED(retc)) PutLogMessage_("StartCmdProcess() %s: [%s]", key_name_buf, key_buf);

// %SystemRoot%, etc. (env. parametrai)
               if(SUCCEEDED(retc)) do
               {
                  pnt_par = strstr(key_buf, "%");
                  if(pnt_par == NULL) break;

                  if(isdigit(*(pnt_par + 1))) break;

                  pnt_par_end = strstr(pnt_par + 1, "%");
                  if(pnt_par_end == NULL)
                  {
                     KP_WARNING(E_INVALIDARG, null);
                     break;
                  }

                  *pnt_par++ = Nul;
                  *pnt_par_end++ = Nul;
                  env_par = (const unsigned char *)getenv((const char *)pnt_par);
                  if(env_par == null)
                  {
                     KP_WARNING(E_INVALIDARG, null);
                     env_par = (const unsigned char *)"";
                  }
                  if(strlen(key_buf) + strlen(env_par) + strlen(pnt_par_end) + 1 >= KP_MAX_FNAME_LEN)
                     retc=KpErrorProc.OutputErrorMessage(E_OUTOFMEMORY, null, True, __FILE__, __LINE__, 0L, NULL);
                  if(SUCCEEDED(retc))
                  {
                     strcpy(key_name_buf, key_buf);
                     strcat(key_name_buf, env_par);
                     strcat(key_name_buf, pnt_par_end);

                     strcpy(key_buf, key_name_buf);
                  }

               } while(True);

// %1 - parametras - atveriamo failo vardas
               if(SUCCEEDED(retc))
               {
                  pnt_par=strstr(key_buf, "%1");
                  if(pnt_par==NULL)
                  {
//                   retc=KP_E_KWD_NOT_FOUND;
//                   if(bShowErrorMessages)
//                      retc=KpErrorProc.OutputErrorMessage(retc, KP_MSG_NO_STANDARD_PROG, True, __FILE__, __LINE__, 0L, NULL);

                     strcpy(cmd_buf, key_buf);
                     strcat(cmd_buf, " ");
                     strcat(cmd_buf, full_fnam_buf /* lpszCmdLine */);
                  }
//                if(SUCCEEDED(retc))
                  else // if(pnt_par==NULL)
                  {
                     *(pnt_par+1)='s';
                     sprintf((char *)cmd_buf, (const char *)key_buf, full_fnam_buf /* lpszCmdLine */);

                  } // else // if(pnt_par==NULL)

                  strncpy(lpszCmdLine, cmd_buf, KP_MAX_FNAME_LEN);
                  lpszCmdLine[KP_MAX_FNAME_LEN] = Nul;

// KpMsgOutF("StartCmdProcess() default: %s", cmd_buf);
// PutLogMessage_("StartCmdProcess() default: StartProcess(%s, %d)", cmd_buf, bForceAcroMaximize);
                  retc = StartProcess(cmd_buf, lpszCurDir, plThreadId, phProcess, show_type /* iWndShowType */, bForceAcroMaximize, True, bOutMsg);

               } // if(ERROR_SUCCESS==RegQueryValueEx(key1, "@", NULL, &val_type, key_buf, &buf_len))

               RegCloseKey(key1);

            } // if(ERROR_SUCCESS==RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name_buf, 0, KEY_QUERY_VALUE, &key1))

         } // if(ERROR_SUCCESS==RegQueryValueEx(key, "@", NULL, &val_type, key_buf, &buf_len))

         RegCloseKey(key);

      } // if(ERROR_SUCCESS==RegOpenKeyEx(HKEY_LOCAL_MACHINE, key_name_buf, 0, KEY_QUERY_VALUE, &key))

   } // if(!processed && SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
HRESULT StartProcess(const unsigned char *lpszCmdLine, const unsigned char *lpszCurDir, DWORD *plThreadId, HANDLE *phProcess, WORD iWndShowType,
              bool bForceAcroMaximize, bool bDoSetPlacement, bool bOutMsg)
{
HRESULT retc = S_OK;
static unsigned char cmd_line[KP_MAX_FNAME_LEN + 1];
STARTUPINFO startup_info;
PROCESS_INFORMATION proc_inf;
int retv = ERROR_SUCCESS;
#ifndef Debug
static unsigned char str_buf[KP_MAX_FNAME_LEN + 200];
#endif
HWND hwnd;
WINDOWPLACEMENT wndpl;
static unsigned char win_name[KP_MAX_FNAME_LEN + 1];
bool process;
static unsigned char dir_buf[KP_MAX_FNAME_LEN + 1]; // lpszCurDir kopija – parametras CreateProcess()
static unsigned char cur_dir[KP_MAX_FNAME_LEN + 1]; // paleidimo komandos lpszCmdLine kelias, ? j? nustatin?jam aktyv¸ katalog?, o lpszCmdLine paliekam tik failo vard?
int act_time;
SECURITY_ATTRIBUTES sec_atr_proc, sec_atr_thread;

// KpMsgOutF_4("StartProcess(): %d %d %d %s", iWndShowType, SW_SHOWNORMAL, bForceAcroMaximize, lpszCmdLine);
// PutLogMessage_("StartProcess(): [%s] [%s]", lpszCmdLine, lpszCurDir);

   KP_ASSERT(lpszCmdLine != null, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszCmdLine) < KP_MAX_FNAME_LEN, E_INVALIDARG, null, True);

// ----------------------------------------
// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf)), KP_E_SYSTEM_ERROR, GetLastError(), True);
// KP_ASSERTE(GetFullPathName((const char *)lpszCurDir, KP_MAX_FNAME_LEN, (char *)dir_buf, NULL), KP_E_FILE_NOT_FOUND, GetLastError(), bOutMsg);
   KP_ASSERT(GetFullPathName((const char *)lpszCurDir, KP_MAX_FNAME_LEN, (char *)dir_buf, NULL) != 0, KP_E_FILE_NOT_FOUND, null, bOutMsg);

// ----------------------------------------
   if(SUCCEEDED(retc))
   {
      strcpy(cmd_line, lpszCmdLine);
      strlwr(cmd_line); // nes b?na "IEXPLORE"
   }

// ---------------------------- lpszCmdLine paliekam tik failo vard? – XFS.exe kitaip neveikia
// ---------------------------- lpszCmdLine keli? perkeliam ? cur_dir – ? j? nustatysim darbin? katalog?
   if(SUCCEEDED(retc)) strcpy(cur_dir, dir_buf);
   if(SUCCEEDED(retc)) // if(strchr(cmd_line, '\\') != null) if(cmd_line[1] != ':') // if(cmd_line[0] != '\\') // komandoms nuo ?akninio katalogo ar su disko vardu – tur?t¸ veikt, bent jau kai diskas sutampa su aktyviu
      if(strstr(cmd_line, "\"") == null) if(strstr(cmd_line, " ") == null) // komandoms su fail¸ vardais su tarpais (d?l to su kabut?m)  TvFnameSplit() neveikia
      if(strchr(cmd_line, '/') == null) if(strstr(cmd_line, ".exe ") == null) if(strstr(cmd_line, ".bin ") == null) // tik komandoms be parametr¸
      if(strstr(cmd_line, ".exe\" ") == null) if(strstr(cmd_line, ".bin\" ") == null)
   {
static unsigned char full_cmd[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_disk[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_path[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_name[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_type[KP_MAX_FTYPE_LEN + 1];

      if(GetFullPathName((const char *)cmd_line, KP_MAX_FNAME_LEN, (char *)full_cmd, NULL) == 0)
      {
         retc = KP_E_FILE_NOT_FOUND;
#ifndef Debug
         if(bOutMsg)
         {
            sprintf((char *)str_buf, (char *)KP_MSG_UNABLE_TO_EXECUTE,
                     (strstr(cmd_line, "\\tv")==NULL)?lpszCmdLine:(unsigned char *)""); // nerodyt laikinu slaptu failu
            KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
         }
#else
         KP_ERROR(retc, null /* retv */);
#endif
      }


      retc = TvFnameSplit(cmd_disk, cmd_path, cmd_name, cmd_type, full_cmd);
//    KP_ASSERT(strlen(dir_buf) + strlen(cmd_path) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
//       strcat(dir_buf, cmd_path); // permetam lpszCmdLine keli? ? lpszCurDir gal? – ne, lpszCurDir turi b?ti tiksliai tas, kurio reikia
         strcpy(cur_dir, cmd_disk);
         strcat(cur_dir, cmd_path);

         strcpy(cmd_line, cmd_name);
         if(cmd_type[0] != Nul)
         {
            strcat(cmd_line, ".");
            strcat(cmd_line, cmd_type);
         }
      }
   }

// ------------------------ i?saugojam path
char dir_buf_sav[KP_MAX_FNAME_LEN + 1];
   GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf_sav);

// ----------------------------
   if(SUCCEEDED(retc))
   {
      startup_info.cb=sizeof(startup_info);
      startup_info.lpReserved=NULL;
      startup_info.lpDesktop=NULL;
      startup_info.lpTitle=NULL;
      startup_info.dwX=0;
      startup_info.dwY=0;
      startup_info.dwXSize=300;
      startup_info.dwYSize=300;
      startup_info.dwXCountChars=80;
      startup_info.dwYCountChars=25;
      startup_info.dwFillAttribute=0;
      startup_info.dwFlags=STARTF_USESHOWWINDOW;
      startup_info.wShowWindow=iWndShowType;
      startup_info.cbReserved2=0;
      startup_info.lpReserved2=NULL;
      startup_info.hStdInput=0;
      startup_info.hStdOutput=0;
      startup_info.hStdError=0;

      sec_atr_proc.nLength = sizeof(sec_atr_proc);
      sec_atr_proc.lpSecurityDescriptor = NULL;
      sec_atr_proc.bInheritHandle = True;

      sec_atr_thread.nLength = sizeof(sec_atr_thread);
      sec_atr_thread.lpSecurityDescriptor = NULL;
      sec_atr_thread.bInheritHandle = True;

// ------------------------ nustatom path – XFS.exe kitaip neveikia; jei paleidimo diskas kitas – neu?teks !!!!
      SetCurrentDirectory((const char *)cur_dir);

// char dir_buf_tmp[KP_MAX_FNAME_LEN + 1];
// GetCurrentDirectory(KP_MAX_FNAME_LEN, dir_buf_tmp);
// PutLogMessage_("StartProcess(): [%s] [%s] [%s] %d %d", cmd_line, dir_buf, dir_buf_tmp, iWndShowType, SW_SHOWNORMAL);

      if(!CreateProcess(NULL /* (const char *)m_szAcroReadPath */, (char *)cmd_line /* m_lpszCmdStr */,
         &sec_atr_proc /* NULL */, &sec_atr_thread /* NULL */, True /* False */,
         0L /* NORMAL_PRIORITY_CLASS */, NULL, (char *)cur_dir /* dir_buf */ /* lpszCurDir */, &startup_info, &proc_inf))
      {
         retv = GetLastError();
         retc = KP_E_SYSTEM_ERROR;
         KpErrorProc.OutputErrorMessage(retc, retv, False, __FILE__, __LINE__, 0L);
         KpErrorProc.OutputErrorMessage(retc, dir_buf, False, __FILE__, __LINE__, 0L);
         KpErrorProc.OutputErrorMessage(retc, cmd_line, False, __FILE__, __LINE__, 0L);
         if((retv == ERROR_FILE_NOT_FOUND) || (retv == ERROR_PATH_NOT_FOUND))
         {
            retc = KP_E_FILE_NOT_FOUND;
#ifndef Debug
            if(bOutMsg)
            {
               sprintf((char *)str_buf, (char *)KP_MSG_UNABLE_TO_EXECUTE,
                  (
                     (strstr(cmd_line, "\\tv")==NULL) && // nerodyt laikinu slaptu failu
                     (strstr(cmd_line, "cert")==NULL) && // ir sertifikatø slaptaþodþiø
                     (strstr(cmd_line, "pfx")==NULL)
                  )?cmd_line:(unsigned char *)"");
               KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
            }
#else
            KP_ERROR(retc, retv);
#endif
         }
         else
#ifndef Debug
            if(bOutMsg)
#endif
               KP_ERROR(retc, retv);
      }
   }

// ------------------------ atstatom buvus? path
   SetCurrentDirectory((const char *)dir_buf_sav);

// PutLogMessage_("StartProcess() 112: %s %x", cmd_line, retc);

   if(plThreadId && SUCCEEDED(retc)) *plThreadId = proc_inf.dwThreadId;
   if(phProcess && SUCCEEDED(retc)) *phProcess = proc_inf.hProcess;

#if FALSE
sprintf(str_buf, "%d %s", startup_info.wShowWindow, cmd_line);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

// ------------------------ nustatom lango pozicija
// AcroRd procesinamas atskirai paleid?iant taimeryje
// PutLogMessage_("StartProcess() %s", cmd_line);
   if(SUCCEEDED(retc)) if(bDoSetPlacement) if((strstr(cmd_line, "acrord") // (cmd_line, "AcroRd")
                                                   == null) || bForceAcroMaximize)
   {
      act_time = 0;
      if(SUCCEEDED(retc)) do
      {
         if(SUCCEEDED(retc)) Sleep(KP_BRING_TO_TOP_INTERVAL);
         act_time += KP_BRING_TO_TOP_INTERVAL;

         hwnd = NULL;
         if(SUCCEEDED(retc)) do
         {

//          hwnd = GetThreadWindow(proc_inf.dwThreadId, hwnd);
//          hwnd = GetProcessWindow(GetProcessId(proc_inf.hProcess), hwnd); // neveikia Win2000
            hwnd = GetProcessWindow(proc_inf.dwProcessId, hwnd);

// 7-zip ir NotePad++ neranda nei vieno lango

            if(hwnd && SUCCEEDED(retc))
            {
               process = False;

               if(!GetWindowText(hwnd, (char *)win_name, KP_MAX_FNAME_LEN))
               {
//                retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

                  win_name[0] = Nul;

                  if(
                     (strstr(cmd_line, "i_view") == 0) &&       // (cmd_line, "i_view")
                     (strstr(cmd_line, "iexplore") == 0) &&     // (cmd_line, "iexplore")
                     (strstr(cmd_line, "winword") == 0) &&      // (cmd_line, "WINWORD")
                     (strstr(cmd_line, "acrord") == 0) &&       // (cmd_line, "AcroRd")
                     (strstr(cmd_line, "smplayer") == 0) &&     // (cmd_line, "smplayer")
                     (strstr(cmd_line, "fps") == 0) &&          // (cmd_line, "Fps")
                     (strstr(cmd_line, "lzdsh") == 0)           // (cmd_line, "lzdshp_mahd.exe")
                    ) process = True;

// PutLogMessage_("StartProcess() cmd_line: %s", cmd_line);
// PutLogMessage_("StartProcess() negavom %d [%s]", process, cmd_line);
               }
               else
               {
                  if(strstr(cmd_line, "i_view")){ if(strstr(win_name, "IrfanView")) process = True; }
                  else if(strstr(cmd_line, "iexplore")){ if(strstr(win_name, KPST_IE_WINDOW_NAME)) process = True; }
                  else if(strstr(cmd_line, "winword" /* "WINWORD" */)){ if(strstr(win_name, "Microsoft Word")) process = True; }
                  else if(strstr(cmd_line, "acrord" /* "AcroRd" */)){ if(strstr(win_name, KPST_ACROREAD_WINDOW_NAME)) process = True; }
                  else if(strstr(cmd_line, "smplayer")){ if(strstr(win_name, "SMPlayer")) process = True; }
                  else if(strstr(cmd_line, "fps" /* "Fps" */)){ if(strstr(win_name, "FPS")) process = True; }
                  else if(strstr(win_name, "IME")) process = False; // "MSCTFIME UI", "Default IME"
                  else if(strstr(win_name, "MCI")) process = False; // "MCI command handling window"
                  else if(strstr(win_name, "LzdshTabHist")) process = False; // Lzdshwp.exe
                  else if(strstr(win_name, "NetscapeDispatchWnd")) process = False; // Lzdshwp.exe
                  else if(strstr(win_name, "nsAppShell")) process = False; // "nsAppShell:EventWindow" // Lzdshwp.exe
                  else if(strstr(win_name, "InnoSetupLdrWindow")) process = False;
                  else if(strstr(win_name, "LzdshTabMain")) process = False;
                  else if(strstr(win_name, "LzdshTabSearch")) process = False;
                  else if(strstr(win_name, "LzdshTabHist")) process = False;
                  else process = True;

// PutLogMessage_("StartProcess() gavom %d [%s] [%s]", process, win_name, cmd_line);
               }
// KP_TRACE_2(process?"StartProcess() jau: %d %s":"StartProcess() dar ne: %d %s", proc_inf.dwProcessId, win_name);
// PutLogMessage_("StartProcess() %s %s", process?"max":"min", win_name);

               if(process && SUCCEEDED(retc))
               {
// PutLogMessage_("StartProcess() win_name: >>>%s<<<", win_name);

                  // lang? jau radom, trumpinam aktyvavimo laik?
                  if(act_time < KP_BRING_TO_TOP_TIME - KP_BRING_TO_TOP_WINDOW_TIME) act_time = KP_BRING_TO_TOP_TIME - KP_BRING_TO_TOP_WINDOW_TIME;

// ---------------
                  wndpl.length = sizeof(wndpl);

                  if(!GetWindowPlacement(hwnd, &wndpl))
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  else
                  {
// PutLogMessage_("StartProcess() %x %d [%s] [%s]", wndpl.flags, wndpl.showCmd, win_name, cmd_line);
                     wndpl.flags = 0;
                     wndpl.showCmd = (iWndShowType == SW_SHOWNORMAL)?SW_SHOWNORMAL /* SW_SHOWMAXIMIZED */ /* SW_RESTORE */ : SW_SHOWMINNOACTIVE;
// PutLogMessage_("StartProcess() %x %d [%s] [%s]", wndpl.flags, wndpl.showCmd, win_name, cmd_line);

// KpMsgOutF("StartProcess(): %d %d %s", wndpl.showCmd, SW_SHOW, win_name);

                     KP_ASSERT(SetWindowPlacement(hwnd, &wndpl), KP_E_SYSTEM_ERROR, GetLastError(), False);
                  }

// ---------------
//                if(iWndShowType == SW_SHOWNORMAL) KP_ASSERT(SetForegroundWindow(hwnd), KP_E_SYSTEM_ERROR, GetLastError(), False);

// ---------------
                  KP_ASSERT
                  (
                     SetWindowPos
                     (
                        hwnd, (iWndShowType == SW_SHOWNORMAL)?HWND_TOPMOST /* HWND_TOP */ : HWND_BOTTOM, 100, 100, 100, 100,
                        (
                           (iWndShowType == SW_SHOWNORMAL)? SWP_SHOWWINDOW : SWP_NOACTIVATE /* SWP_HIDEWINDOW */
                        ) | SWP_NOMOVE | SWP_NOSIZE
                     ),
                     KP_E_SYSTEM_ERROR, GetLastError(), False
                  );

                  if(SUCCEEDED(retc)) Sleep(KP_BRING_TO_TOP_INTERVAL);
                  act_time += KP_BRING_TO_TOP_INTERVAL;

                  KP_ASSERT
                  (
                     SetWindowPos
                     (
                        hwnd, (iWndShowType == SW_SHOWNORMAL)?HWND_NOTOPMOST /* HWND_TOP */ : HWND_BOTTOM, 100, 100, 100, 100,
                        (
                           (iWndShowType == SW_SHOWNORMAL)? SWP_SHOWWINDOW : SWP_NOACTIVATE /* SWP_HIDEWINDOW */
                        ) | SWP_NOMOVE | SWP_NOSIZE
                     ),
                     KP_E_SYSTEM_ERROR, GetLastError(), False
                  );

                  break; // tik pirm? lang? maksimizuojam – o gal neu?tenka, gal pirmi kokie nors tarnybiniai?

               } // if(process && SUCCEEDED(retc))

            } // if(hwnd && SUCCEEDED(retc))

         } while(hwnd && SUCCEEDED(retc));

      } while((act_time < KP_BRING_TO_TOP_TIME) && SUCCEEDED(retc)); // lang? bandom aktyvinti i? viso

   } // if(SUCCEEDED(retc)) if(strstr(cmd_line, "AcroRd") == null)

return(retc);
}


//---------------------------
HRESULT WaitForProcessEnd(HANDLE hProcess, HANDLE hThread)
{
HRESULT retc=S_OK;
DWORD exit_code;

   if(hProcess)
   {
      do
      {
         if(!GetExitCodeProcess(hProcess, &exit_code))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         KpSleep(500, HWND_DESKTOP);

      } while((exit_code==STILL_ACTIVE) && SUCCEEDED(retc));
   }
   else if(hThread)
   {
      do
      {
         if(!GetExitCodeThread(hThread, &exit_code))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         KpSleep(500, HWND_DESKTOP);

      } while((exit_code==STILL_ACTIVE) && SUCCEEDED(retc));
   }

return(retc);
}


// -------------------------------------------
HRESULT CloseProcess(const unsigned char *lpszCmdLine, DWORD lThreadId)
{
HRESULT retc=S_OK;
HWND real_wnd=NULL;
bool closed=False;

   if(lpszCmdLine!=NULL)
   {
      if(strstr(lpszCmdLine, "Real")!=NULL)
      {
         real_wnd = GetWindowByName((const unsigned char *)"Real", False);
         if(real_wnd!=NULL)
         {
            if(!PostMessage(real_wnd, WM_CLOSE, 0L, 0L))
            {
// threadas gali buti paleides kita vaika, o pats jau pasibaiges - blogai
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }
            if(!PostMessage(real_wnd, WM_QUIT, IDCANCEL, 0L))
            {
// threadas gali buti paleides kita vaika, o pats jau pasibaiges - blogai
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }
            closed=True;
         }
      }

      if(!closed) if(IsSoundFile(lpszCmdLine))
      {
         real_wnd = GetWindowByName((const unsigned char *)"Winamp", False);
         if(real_wnd!=NULL)
         {
            if(!PostMessage(real_wnd, WM_CLOSE, 0L, 0L))
            {
// threadas gali buti paleides kita vaika, o pats jau pasibaiges - blogai
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            }
            if(!PostMessage(real_wnd, WM_QUIT, IDCANCEL, 0L))
            {
// threadas gali buti paleides kita vaika, o pats jau pasibaiges - blogai
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            }
            closed=True;
         }
      }
   }

   if((lThreadId!=0L) && (!closed))
   {
      if(!PostThreadMessage(lThreadId, WM_CLOSE, 0L, 0L))
      {
// threadas gali buti paleides kita vaika, o pats jau pasibaiges - blogai
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      if(!PostThreadMessage(lThreadId, WM_QUIT, IDCANCEL, 0L))
      {
// threadas gali buti paleides kita vaika, o pats jau pasibaiges - blogai
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}


// -------------------------------------------
HRESULT KpCloseWindow(const unsigned char *lpszWndName, bool bCheckError)
{
HRESULT retc=S_OK;
HWND hwnd=NULL;
DWORD wnd_thread;
DWORD wnd_pid;
HANDLE wnd_phandle;

   if(lpszWndName==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      hwnd=GetWindowByName(lpszWndName, True);
      if(hwnd==NULL)
      {
         retc=KP_E_OBJ_NOT_FOUND;
         if(bCheckError) retc=KpErrorProc.OutputErrorMessage(retc, KP_MSG_WND_NOT_FOUND, True, __FILE__, __LINE__, 0L, NULL);
      }
   }


// ---------------------------
   if(SUCCEEDED(retc))
   {
      wnd_thread=GetWindowThreadProcessId(hwnd, &wnd_pid);
      if((wnd_thread==0L) || (wnd_pid==0L))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, KP_MSG_PID_NOT_FOUND, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      wnd_phandle=OpenProcess(PROCESS_TERMINATE, False, wnd_pid);
      if(wnd_phandle==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
      if(!TerminateProcess(wnd_phandle, 0))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);


return(retc);
}


// -------------------------------------------
HRESULT KpSleep(long lMilliseconds, HWND hCurWnd)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
bool endfl = False;
MSG msg;
unsigned int retw;
UINT sleep_timer_id = 0;

   if((lMilliseconds != 0L) && SUCCEEDED(retc))
   {
      sleep_timer_id = SetTimer(hCurWnd, KP_SLEEP_TIMER, lMilliseconds, NULL);
      if(!sleep_timer_id)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0) < 0)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retw = LOWORD(msg.wParam);
      }

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_CHAR:
         switch(retw)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId!=0L)
               if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            break;
         case C_Etx: // Ctrl C
            retc=KP_E_CANCEL;
            endfl=True;
            break;
         }
         break;

      case WM_QUIT:
         switch(retw)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl = True;
         break;

      case WM_TIMER:
//       if(retw==KP_SLEEP_TIMER) // neveikia, kai m_hBitmapWindow jau uzdarytas
//       if(retw!=KPW_CONSOLE_REFRESH_TIMER)
         if(retw==sleep_timer_id)
         {
//          if(!KillTimer(hCurWnd, retw))
//          {
// #ifdef Debug
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// #endif
//          }

            endfl = True;
         }
         break;

      case WM_COMMAND:
         switch(LOWORD(msg.wParam))
         {
         case KP_ID_MUTE:
            if(iKpMainThread == GetCurrentThreadId()) // kad nenulau?t¸ kphp11 dvigubais i?kvietimais i? kito threado
            {
               KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SwitchMute();
            }
            break;
         }
         break;

      default:
         break;
      }

   } while((!endfl) && SUCCEEDED(retc));

   if(sleep_timer_id)
   {
      if(!KillTimer(hCurWnd, sleep_timer_id)) // tik warningas - gali buti pagrindinis langas jau uzsidares
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      sleep_timer_id = 0;
   }

return(retc);
}


// -------------------------------------------
HRESULT KpSetClipboardData(HWND hWndNewOwner, UINT uFormat, const unsigned char *lpClipData, int iBufSize, bool bClearBeforeSetting)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HGLOBAL h_mem=NULL;
unsigned char *pntd=NULL;
DWORD err=NO_ERROR;

   if(!OpenClipboard(hWndNewOwner))
   {
// !!!!??? buna jeigu daznai spaudi klaviatura
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   }
   else
   {

#if TRUE // #if FALSE // #ifndef Debug
      if(bClearBeforeSetting && SUCCEEDED(retc))
         if(!EmptyClipboard())
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif

      if(SUCCEEDED(retc))
      {
         if(lpClipData!=NULL)
         {
            if(iBufSize>0)
            {
               if(SUCCEEDED(retc))
               {
                  h_mem=GlobalAlloc(GMEM_SHARE|GMEM_MOVEABLE, iBufSize);
                  if(h_mem==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, GetLastError(), False, __FILE__, __LINE__, 0L);
                  else
                  {
                     if(SUCCEEDED(retc))
                     {
                        pntd=(unsigned char *)GlobalLock(h_mem);
                        if(pntd==NULL)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                     }

                     if(SUCCEEDED(retc)) memcpy(pntd, lpClipData, iBufSize);

                     if(/* pntd!=NULL */ h_mem!=NULL)
                     {
                        if(!GlobalUnlock(h_mem))
                        {
#if FALSE
                           err=GetLastError();
                           if(err!=NO_ERROR)
                           {
// !!!!??? kazko nesuveikia, kai pries tai buna buvus kita kokia klaida, bet neiskviestas GetLastError()
#ifdef Debug
                              retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, err, False, __FILE__, __LINE__, 0L);
                              if(SUCCEEDED(retc)) retc=retc0;
#endif
                           }
#endif
                        }
                     }

                     if(SUCCEEDED(retc))
                     {
                        if(NULL==SetClipboardData(uFormat, h_mem))
                        {
// !!!??? kazkodel duoda klaida, kai greitai spaudi klaviatura
#ifdef Debug
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
                        }
                     }


// CF_LOCALE !!!!!


                  } // else // if(h_mem==NULL)

               } // if(SUCCEEDED(retc))

            }
         }
      }

      if(!CloseClipboard())
      {
// !!!??? kazkodel duoda klaida, kai greitai spaudi klaviatura
#ifdef Debug
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=retc0;
#endif
      }

//    if(h_mem!=NULL)
//    {
//       if(GlobalFree(h_mem))
//       {
//          retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
//          if(SUCCEEDED(retc)) retc=retc0;
//       }
//    }

   } // else // if(OpenClipboard(hWndNewOwner)==NULL)

return(retc);
}


// -------------------------------------------
HRESULT SetClipboardText(HWND hWndNewOwner, const unsigned char *lpszClipData, int iCtbl)
{
HRESULT retc=S_OK;
int locale = 0;

   if(((iCtbl < 0) || (iCtbl >= KPT_Ctnum)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      locale = iKpt2WinLocale[iCtbl];
      retc = KpSetClipboardData(hWndNewOwner, CF_LOCALE, (unsigned char *)&locale, sizeof(locale));
   }

   if(SUCCEEDED(retc)) retc = KpSetClipboardData(hWndNewOwner, CF_TEXT, lpszClipData, strlen(lpszClipData)+1, False);

return(retc);
}


// -------------------------------------------
HRESULT KpGetClipboardData(HWND hWndNewOwner, UINT uFormat, unsigned char *lpszClipData, int iBufSize, bool bTestErrors)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HGLOBAL h_mem=NULL;
const unsigned char *pnts=NULL;
DWORD err=NO_ERROR;

   if((lpszClipData==NULL) || (iBufSize<=0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(!OpenClipboard(hWndNewOwner))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      else
      {
         if(SUCCEEDED(retc)) lpszClipData[0]=Nul;

         if(SUCCEEDED(retc))
         {
            h_mem=GetClipboardData(uFormat);
            if(h_mem==NULL)
            {
               retc=KP_E_OBJ_NOT_FOUND;
               if(bTestErrors)
                  retc=KpErrorProc.OutputErrorMessage(retc, GetLastError(), True, __FILE__, __LINE__, 0L);
            }
         }

         if(SUCCEEDED(retc))
         {
            pnts=(const unsigned char *)GlobalLock(h_mem);
            if(pnts==NULL)
            {
               retc=KP_E_OBJ_NOT_FOUND;
               if(bTestErrors)
                  retc=KpErrorProc.OutputErrorMessage(retc, GetLastError(), True, __FILE__, __LINE__, 0L);
            }
            else
            {
               if(SUCCEEDED(retc))
               {
                  strncpy(lpszClipData, pnts, iBufSize-1);
                  lpszClipData[iBufSize-1]=Nul;
                  retc=SkipCr(lpszClipData);
               }

               if(SUCCEEDED(retc))
               {
                  if(strlen(pnts)>=iBufSize-1)
                  {
                     retc=KP_E_BUFFER_OVERFLOW;
                     if(bTestErrors)
                        retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
               }

            } // else // if(pnts==NULL)

            if(/* pnts!=NULL */ h_mem!=NULL)
            {
               if(!GlobalUnlock(h_mem))
               {
                  err=GetLastError();
//                if(err!=NO_ERROR)
//                {
//                   retc0=KP_E_SYSTEM_ERROR;
//                   if(bTestErrors)
//                      retc0=KpErrorProc.OutputErrorMessage(retc0, err, True, __FILE__, __LINE__, 0L);
//                   if(SUCCEEDED(retc)) retc=retc0;
//                }
               }
            }

         } // if(SUCCEEDED(retc))

         if(!CloseClipboard())
         {
            err=GetLastError();
            if(err!=NO_ERROR)
            {
               retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, err, False, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) retc=retc0;
            }
         }

      } // else // if(OpenClipboard(hWndNewOwner)==NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
HRESULT GetClipboardText(HWND hWndNewOwner, unsigned char *lpszClipData, int iBufSize, bool bTestErrors)
{
return(KpGetClipboardData(hWndNewOwner, CF_TEXT, lpszClipData, iBufSize, bTestErrors));
}


// -------------------------------------------
HRESULT KpClearClipboard(HWND hWndNewOwner, const unsigned char *lpszWndName)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
// UINT clip_format;
long val = 0L;
DWORD err=NO_ERROR;

#if FALSE
   if(SUCCEEDED(retc))
   {
      clip_format=RegisterClipboardFormat(KP_CF_RTF_NAME);
      if(clip_format==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      else
      {
         KpCfRtfClFormat = clip_format;
         retc=KpSetClipboardData(hWndNewOwner, clip_format, (const unsigned char *)"", 0);
      }
   }

   if(SUCCEEDED(retc))
   {
      clip_format=RegisterClipboardFormat(KP_CF_HTML_NAME);
      if(clip_format==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      else
      {
         KpCfHtmlClFormat = clip_format;
         retc=KpSetClipboardData(hWndNewOwner, clip_format, (const unsigned char *)"", 0);
      }
   }

   if(SUCCEEDED(retc)) retc=KpSetClipboardData(hWndNewOwner, CF_TEXT, (const unsigned char *)&val /* "" */, sizeof(val) /* 0 */);
   if(SUCCEEDED(retc)) retc=KpSetClipboardData(hWndNewOwner, CF_DSPTEXT, (const unsigned char *)&val /* "" */, sizeof(val) /* 0 */);
   if(SUCCEEDED(retc))
   {

#if FALSE // #ifdef Debug
unsigned char str_buf[100+1];
stringstream str_stream;

str_buf[0]= Nul;
str_stream.str("");
KpGetClipboardData(hWndNewOwner /* HWND_DESKTOP */, CF_OEMTEXT, str_buf, 100, True);
str_buf[100] = Nul;
RemoveSpChars(str_buf);
str_stream << "prie? KpSetClipboardData(hWndNewOwner, CF_OEMTEXT, ...): " << str_buf;
KP_TRACE(KpString(str_stream.str()));
#endif

      retc=KpSetClipboardData(hWndNewOwner, CF_OEMTEXT, (const unsigned char *)&val /* "" */, sizeof(val) /* 0 */);

#if FALSE // #ifdef Debug
str_buf[0]= Nul;
str_stream.str("");
KpGetClipboardData(hWndNewOwner /* HWND_DESKTOP */, CF_OEMTEXT, str_buf, 100, True);
str_buf[100] = Nul;
RemoveSpChars(str_buf);
str_stream << "po KpSetClipboardData(hWndNewOwner, CF_OEMTEXT, ...): " << str_buf;
KP_TRACE(KpString(str_stream.str()));
#endif
   }
   if(SUCCEEDED(retc)) retc=KpSetClipboardData(hWndNewOwner, CF_UNICODETEXT, (const unsigned char *)&val /* "" */, sizeof(val) /* 0 */);
#endif

// ---------------------------------------
bool proceed = False;

   if(SUCCEEDED(retc))
   {
      if(lpszWndName == null) proceed = True;
      else
      {
HWND top_wnd = GetForegroundWindow();
unsigned char wnd_name[KP_MAX_FNAME_LEN + 1];
         if(top_wnd != NULL) if(GetWindowText(top_wnd, (char *)wnd_name, KP_MAX_FNAME_LEN) > 0)
            if(strcmp(wnd_name, lpszWndName) == 0)
               proceed = True;
      }
   }

// -----------------------
   if(proceed && SUCCEEDED(retc))
   {
      if(!OpenClipboard(hWndNewOwner))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      else
      {
         if(SUCCEEDED(retc)) if(!EmptyClipboard())
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

         if(!CloseClipboard())
         {
            err = GetLastError();
            if(err != NO_ERROR)
            {
               retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, err, False, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) retc = retc0;
            }
         }
      }
   }

return(retc);
}


// -------------------------------------------
HRESULT GetLocalPath(unsigned char *lpszFNamBuf, LocalPaths iPathID, bool bAppendSlash)
{
HRESULT retc=S_OK;
MSWin32Version vers;
// int sp;
// const unsigned char *user_profile;
// unsigned char *pntd;
unsigned char user_name[KP_MAX_FNAME_LEN+1];
DWORD ll;
#if FALSE // #ifdef Debug // Logging //
unsigned char str_buf[KP_MAX_FNAME_LEN+100];
#endif
const char *val_name = NULL;
HKEY key=NULL;
DWORD buf_len;
DWORD val_type;
const unsigned char *nam_ptr = NULL;
unsigned char *pntd = NULL;
int CSIDL_folder = 0;

// ---------------------------------
   KP_ASSERT(lpszFNamBuf, E_INVALIDARG, null, True);

// TODO: Win98 negerai, reikia per getenv("windir"), getenv("SystemRoot"), getenv("SystemRoot"), getenv("ProgramFiles")
// TODO: be to, jeigu multiuserinis variantas – per C:\Windows\Profiles
   if(SUCCEEDED(retc)) switch(iPathID)
   {
      case KP_My_Documents:
         strcpy(lpszFNamBuf, "C:\\My Documents");
         val_name = "Personal";
         CSIDL_folder = CSIDL_PERSONAL;
         break;
      case KP_Application_Data:
         strcpy(lpszFNamBuf, "C:\\Windows\\Application Data");
         val_name = "AppData";
         CSIDL_folder = CSIDL_APPDATA;
         break;
      case KP_Desktop:
         strcpy(lpszFNamBuf, "C:\\Windows\\Desktop");
         val_name = "Desktop";
         CSIDL_folder = CSIDL_DESKTOP;
         break;
      case KP_LocalDir:
         strcpy(lpszFNamBuf, ".");
         val_name = "";
         break;
      case KP_Program_Files:
         strcpy(lpszFNamBuf, "C:\\Program Files");
         val_name = "ProgramFiles";
         break;
      case KP_Common_Files:
         strcpy(lpszFNamBuf, "C:\\Program Files\\Common Files");
         val_name = "CommonProgramFiles";
         break;
      case KP_Temp_Dir:
         strcpy(lpszFNamBuf, "C:\\Temp");
         break;
      default:
         KP_ERROR(E_INVALIDARG, null);
         break;
   }

// ---------------------------------
   vers = iWindowsVersion;

#if FALSE // #ifdef Logging // Debug
sprintf((char *)str_buf, "### 4.2.1.1 Windows version: %d", vers);
KP_TRACE(str_buf);
#  ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#  endif
#endif

   if(SUCCEEDED(retc))
   {
      strcpy(user_name, "Unknown");
      ll = KP_MAX_FNAME_LEN;
      if((vers >= WinNT40c) && SUCCEEDED(retc))
         if(!GetUserName((char *)user_name, &ll))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      user_name[KP_MAX_FNAME_LEN]=Nul;
   }

#if FALSE // #ifdef Logging // Debug
sprintf((char *)str_buf, "### 4.2.1.1.1 User name: %s", user_name);
KP_TRACE(str_buf);
#  ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#  endif
#endif

#if FALSE
   if(SUCCEEDED(retc))
   {
      if(!GetWindowsDirectory((char *)lpszFNamBuf, KP_MAX_FNAME_LEN))
        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      lpszFNamBuf[KP_MAX_FNAME_LEN]=Nul;
   }

   if((vers!=WinNT40c) && (vers!=WinNT40) && (vers!=WinNT40s) && SUCCEEDED(retc))
   {
      pntd=lpszFNamBuf;
      while((*pntd!=':') && (*pntd)) pntd++;
      if(*pntd==':') pntd++;
      *pntd=Nul;
   }

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf)+1<KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, "\\");
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(((vers==WinNT40c) || (vers==WinNT40) || (vers==WinNT40s)) && SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_NT_1)<KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, MY_DOCS_PATH_NT_1);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if((vers>=Win2000c) && SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_2K_1)<KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, MY_DOCS_PATH_2K_1);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if((vers>=WinNT40c) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc))
      {
         if(strlen(lpszFNamBuf)+strlen(user_name)+1<KP_MAX_FNAME_LEN)
         {
            strcat(lpszFNamBuf, user_name);
            strcat(lpszFNamBuf, "\\");
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if((vers<WinNT40c) && SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_98_2)<KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, MY_DOCS_PATH_98_2);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(((vers==WinNT40c) || (vers==WinNT40) || (vers==WinNT40s)) && SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_NT_2)<KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, MY_DOCS_PATH_NT_2);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if((vers>=Win2000c) && SUCCEEDED(retc)) switch(iPathID)
   {
      case KP_My_Documents:
         if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_2K_2)<KP_MAX_FNAME_LEN)
            strcat(lpszFNamBuf, MY_DOCS_PATH_2K_2);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         break;
      case KP_Application_Data:
         if(strlen(lpszFNamBuf)+strlen(AP_DATA_PATH_2K_2)<KP_MAX_FNAME_LEN)
            strcat(lpszFNamBuf, AP_DATA_PATH_2K_2);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         break;
   }

#elif FALSE

   if(SUCCEEDED(retc))
   {
      if((vers!=WinNT40c) && (vers!=WinNT40) && (vers!=WinNT40s))
      {
         retc = SHGetSpecialFolderPath(HWND_DESKTOP, (char *)lpszFNamBuf, CSIDL_PERSONAL, False);
      }
      else
      {
// hr = psfDeskTop->ParseDisplayName(NULL,
//                                  NULL,
//                                  L"::{450d8fba-ad25-11d0-98a8-0800361b1103}",
//                                  &chEaten,
//                                  &pidlDocFiles,
//                                  NULL);
         if(SUCCEEDED(retc))
         {
            user_profile = (unsigned char *)getenv("USERPROFILE");
            if(user_profile == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            if(strlen(user_profile) < KP_MAX_FNAME_LEN)
               strcpy(lpszFNamBuf, user_profile);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf) + 1 < KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, "\\");
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(((vers==WinNT40c) || (vers==WinNT40) || (vers==WinNT40s)) && SUCCEEDED(retc))
   {
      if(strlen(lpszFNamBuf) + strlen(MY_DOCS_PATH_NT_2)<KP_MAX_FNAME_LEN)
         strcat(lpszFNamBuf, MY_DOCS_PATH_NT_2);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

#elif FALSE

   if(SUCCEEDED(retc))
   {
      if(vers<WinNT40c)
      {
         if(SUCCEEDED(retc))
         {
            if(!GetWindowsDirectory((char *)lpszFNamBuf, KP_MAX_FNAME_LEN))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            lpszFNamBuf[KP_MAX_FNAME_LEN]=Nul;
         }

#  if FALSE // #ifdef Logging // Debug
sprintf((char *)str_buf, "### 4.2.1.2 Windows dir: %s", lpszFNamBuf);
KP_TRACE(str_buf);
#     ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#     endif
#  endif
         if(SUCCEEDED(retc))
         {
            pntd=lpszFNamBuf;
            while((*pntd!=':') && (*pntd)) pntd++;
            if(*pntd==':') pntd++;
            *pntd=Nul;
         }

#  if FALSE // #ifdef Logging // Debug
sprintf((char *)str_buf, "### 4.2.1.3 Windows drive: %s", lpszFNamBuf);
KP_TRACE(str_buf);
#     ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#     endif
#  endif
         if(SUCCEEDED(retc))
         {
            if(strlen(lpszFNamBuf)+1<KP_MAX_FNAME_LEN)
               strcat(lpszFNamBuf, "\\");
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_98_2)<KP_MAX_FNAME_LEN)
               strcat(lpszFNamBuf, MY_DOCS_PATH_98_2);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }
      }
      else // if(vers<WinNT40c)
      {
         if(SUCCEEDED(retc))
         {
            user_profile=(unsigned char *)getenv("USERPROFILE");
            if(user_profile==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            if(strlen(user_profile)<KP_MAX_FNAME_LEN)
               strcpy(lpszFNamBuf, user_profile);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

#  if FALSE // #ifdef Logging // Debug
sprintf((char *)str_buf, "### 4.2.1.4 User profile: %s", lpszFNamBuf);
KP_TRACE(str_buf);
#     ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#     endif
#  endif

         if(SUCCEEDED(retc))
         {
            if(strlen(lpszFNamBuf) + 1 < KP_MAX_FNAME_LEN)
               strcat(lpszFNamBuf, "\\");
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            if((vers==WinNT40c) || (vers==WinNT40) || (vers==WinNT40s))
            {
               if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_NT_2)<KP_MAX_FNAME_LEN)
                  strcat(lpszFNamBuf, MY_DOCS_PATH_NT_2);
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            }
            else switch(iPathID)
            {
               case KP_My_Documents:
                  if(strlen(lpszFNamBuf)+strlen(MY_DOCS_PATH_2K_2)<KP_MAX_FNAME_LEN)
                     strcat(lpszFNamBuf, MY_DOCS_PATH_2K_2);
                  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
                  break;
               case KP_Application_Data:
                  if(strlen(lpszFNamBuf)+strlen(AP_DATA_PATH_2K_2)<KP_MAX_FNAME_LEN)
                     strcat(lpszFNamBuf, AP_DATA_PATH_2K_2);
                  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
                  break;
            }
         }

      } // else // if(vers < WinNT40c)

   } // if(SUCCEEDED(retc))

// ----------------------------------------------
#else // #elif FALSE

// --------------
   if(((iPathID == KP_My_Documents) || (iPathID == KP_Desktop)) && (vers >= WinNT) && SUCCEEDED(retc))
   {
      if(vers < WinXPc)
      {
         if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER,
            "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
            0, KEY_QUERY_VALUE, &key))
         {
            retc = KP_E_KWD_NOT_FOUND;
            KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }

         if(SUCCEEDED(retc))
         {
            buf_len = KP_MAX_FNAME_LEN;
            if(ERROR_SUCCESS == RegQueryValueEx(key, val_name, NULL, &val_type, lpszFNamBuf, &buf_len))
               lpszFNamBuf[buf_len] = Nul;
            else
            {
               retc = KP_E_KWD_NOT_FOUND;
               KpErrorProc.OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            }
         }

         if(SUCCEEDED(retc)) if(val_type != REG_SZ)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
      }
      else // if(vers < WinXPc)
      {
#if KP_MAX_FNAME_LEN < MAX_PATH
#error KP_MAX_FNAME_LEN < MAX_PATH
#endif
unsigned char nam_buf_sav[KP_MAX_FNAME_LEN + 1];
         strcpy(nam_buf_sav, lpszFNamBuf);
         if(SUCCEEDED(retc))
         {
            retc = SHGetFolderPath(NULL, CSIDL_folder, NULL, 0L, (char *)lpszFNamBuf);
            if(FAILED(retc))
            {
// PK910v/klaida_20120911_Algimantas_Lazauskas: duoda E_NOT_READY 0x80070015 "_renginys nëra pasirengæs"
               KP_WARNING0(retc, nam_buf_sav);
               KP_ERROR(retc, GetLastError());
            }
         }
      }

   } // if(((iPathID == KP_My_Documents) || (iPathID == KP_Application_Data)) && (vers >= WinNT) && SUCCEEDED(retc))

// --------------
   if(((iPathID == KP_Program_Files) || (iPathID == KP_Common_Files) || (iPathID == KP_Application_Data)) && SUCCEEDED(retc))
   {
      nam_ptr = (unsigned char *)getenv(val_name);
      KP_ASSERTE(nam_ptr, KP_E_KWD_NOT_FOUND, val_name, False); // Mano emuliatoriuj WinXP Administrator neturi AddData – lû_ta UpdateTMGrpPrm()

      KP_ASSERT(strlen(nam_ptr) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcpy(lpszFNamBuf, nam_ptr);
   }

// -------------
   if((iPathID == KP_Temp_Dir) && SUCCEEDED(retc))
   {
      KP_ASSERT(GetTempPath(KP_MAX_FNAME_LEN, (char *)lpszFNamBuf), KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if((iPathID == KP_LocalDir) && SUCCEEDED(retc))
   {
      KP_ASSERT(GetFullPathName(".", KP_MAX_FNAME_LEN, (char *)lpszFNamBuf, NULL),
         KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(((iPathID == KP_Temp_Dir) || (iPathID == KP_LocalDir)) && SUCCEEDED(retc))
   {
// numetam sle?? gale
      pntd = lpszFNamBuf + strlen(lpszFNamBuf);
      if(pntd > lpszFNamBuf) if(*(--pntd) == '\\') *pntd = Nul;
   }

#endif


// -------------
   if(retc == KP_E_KWD_NOT_FOUND) retc = S_OK;

// --------------
// TODO !!!!! KP_LocalDir gr??ina ".", o tas kartais negerai, pvz. StartProcess()
// KP_ASSERT(GetFullPathName(lpszCurDir, KP_MAX_FNAME_LEN, (char *)dir_buf, NUL), KP_E_SYSTEM_ERROR, GetLastError(), True);


// --------------
   if(bAppendSlash && SUCCEEDED(retc)) strcat(lpszFNamBuf, "\\");

#if FALSE // #ifdef Logging // Debug
sprintf((char *)str_buf, "### 4.2.1.5 User files path: %s", lpszFNamBuf);
KP_TRACE(str_buf);
#ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

// KpMsgOut(lpszFNamBuf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


// ----------------------------------------
HRESULT TestAdmin(bool *pbAdminFl)
{
HRESULT retc=S_OK;
unsigned char user_name[KP_MAX_FNAME_LEN+1];
DWORD ll;
bool admin_fl = False;

   if(SUCCEEDED(retc))
   {
      if(iWindowsVersion<WinNT40c) admin_fl=True;
      else
      {
         if(iWindowsVersion < Win2000c)
         {
            strcpy(user_name, "Unknown");
            ll=KP_MAX_FNAME_LEN;
               if(!GetUserName((char *)user_name, &ll))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            user_name[KP_MAX_FNAME_LEN]=Nul;

            if(SUCCEEDED(retc))
            {
               TvStrLwrLat(user_name);
               if(strcmp(user_name, "administrator")==0) admin_fl=True;
               else admin_fl=False;
            }
         }
         else admin_fl = IsUserAdmin();

#if FALSE
// is msdn.microsoft.com CheckTokenMembership()
// BOOL IsUserAdmin(VOID)
/*++
Routine Description: This routine returns TRUE if the caller's
process is a member of the Administrators local group. Caller is NOT
expected to be impersonating anyone and is expected to be able to
open its own process and process token.
Arguments: None.
Return Value:
   TRUE - Caller has Administrators local group.
   FALSE - Caller does not have Administrators local group. --
*/
{
BOOL b;
SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
PSID AdministratorsGroup;
b = AllocateAndInitializeSid(
    &NtAuthority,
    2,
    SECURITY_BUILTIN_DOMAIN_RID,
    DOMAIN_ALIAS_RID_ADMINS,
    0, 0, 0, 0, 0, 0,
    &AdministratorsGroup);
if(b)
{
    if (!CheckTokenMembership( NULL, AdministratorsGroup, &b))
    {
         b = FALSE;
    }
    FreeSid(AdministratorsGroup);
}

// return(b);
   admin_fl = b;
}
#endif

      }
   }

   bAdminFl = admin_fl;
   if(pbAdminFl!=NULL) *pbAdminFl = bAdminFl;

return(retc);
}


#if (CompilerGr==Watcom) && (__WATCOMC__ >= 1202)

// http://www.governmentsecurity.org/forum/index.php?showtopic=3669

typedef bool (WINAPI *IsUserAdminFunPtr)(void);

// nuwrapinam standartin_ shell32.lib funkcij? – j? i?kvie?ia Watcom runtime, bet Win2k neturi dll ??jimo IsUserAnAdmin
SHSTDAPI_(BOOL) IsUserAnAdmin(void)
{
HRESULT retc = S_OK;
HMODULE hmod = NULL;
IsUserAdminFunPtr proc_ptr = NULL;
bool retv = False;
int sp;
MSWin32Version ver;

   if(SUCCEEDED(retc)) retc = KpGetSystemVersion(&ver, &sp);

   if(SUCCEEDED(retc))
   {
   }

   if(SUCCEEDED(retc))
   {
      if(ver /* iWindowsVersion */ < WinXPc) // Win2k
      {
         hmod = LoadLibrary("setupapi.dll");
         KP_ASSERT(hmod, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            proc_ptr = (IsUserAdminFunPtr)::GetProcAddress(hmod, "IsUserAdmin");
      }
      else // XP, Vista
      {
         hmod = LoadLibrary("shell32.dll");
         KP_ASSERT(hmod, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc))
            proc_ptr = (IsUserAdminFunPtr)::GetProcAddress(hmod, "IsUserAnAdmin");
      }

      KP_ASSERT(proc_ptr, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(SUCCEEDED(retc)) retv = proc_ptr();

   if(hmod) FreeLibrary(hmod);
   hmod = NULL;

return(retv);
}
#endif


// =============================================== drawing
// ---------------------------
HRESULT KpDrawLine(HDC hDC, int iX1, int iY1, int iX2, int iY2, int iKpWndStyle, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
HRESULT retc=S_OK;
HPEN pen_light = NULL;
HPEN pen_black = NULL;

// if((aPenScheme == NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

   if((iKpWndStyle!=KP_WND_SUNKEN) && (iKpWndStyle!=KP_WND_RAISED) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);

   pen_black = NULL;
   pen_light = NULL;

   if(SUCCEEDED(retc))
   {
//    if(aPenScheme == NULL)
      if(iaColorScheme == NULL)
      {
         if(SUCCEEDED(retc))
         {
            pen_black = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowBlack]));
            if(pen_black == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(retc))
         {
            pen_light = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
            if(pen_light == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
      }
      else
      {
#if FALSE
         if((aPenScheme[KpShadowBlack] == NULL) && SUCCEEDED(retc))
         {
            pen_black = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowBlack]));
            if(pen_black == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
         if((aPenScheme[KpShadowLight] == NULL) && SUCCEEDED(retc))
         {
            pen_light = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
            if(pen_light == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
#else
         if(SUCCEEDED(retc))
         {
            pen_black = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowBlack]);
            if(pen_black == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(retc))
         {
            pen_light = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowLight]);
            if(pen_light == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
#endif
      }

   } // if(SUCCEEDED(retc))

// -------------------
   if(SUCCEEDED(retc))
      if(!SelectObject(hDC, (iKpWndStyle&KP_WND_SUNKEN)?
                              (pen_black /* ?pen_black:aPenScheme[KpShadowBlack] */):
                              (pen_light /* ?pen_light:aPenScheme[KpShadowLight] */)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!MoveToEx(hDC, iX1, iY1, NULL))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!LineTo(hDC, iX2, iY2))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

// -------------------
   if(SUCCEEDED(retc))
      if(!SelectObject(hDC, (iKpWndStyle&KP_WND_SUNKEN)?
                              (pen_light /* ?pen_light:aPenScheme[KpShadowLight] */):
                              (pen_black /* ?pen_black:aPenScheme[KpShadowBlack] */)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!MoveToEx(hDC, iX1+1, iY1+1, NULL))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!LineTo(hDC, iX2+1, iY2+1))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

   if(pen_black) if(!DeleteObject(pen_black))
      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_black = NULL;

   if(pen_light) if(!DeleteObject(pen_light))
      /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_light = NULL;

return(retc);
}


// ---------------------------
HRESULT KpDrawRect(HDC hDC, int iX1, int iY1, int iX2, int iY2, int iKpWndStyle, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
HRESULT retc=S_OK;
HPEN pens[4]={NULL, NULL, NULL, NULL};
HPEN pen;
HPEN pen_norm = NULL;
HPEN pen_light = NULL;
HPEN pen_dark = NULL;
HPEN pen_black = NULL;
HPEN pen_back = NULL;
int test_sty;
int down, down0, down1, down2, down3, down4, right, right1, left, left1, wide, up_left, up_right;

// if((aPenScheme==NULL) && SUCCEEDED(retc))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   pen_norm = NULL;
   pen_light = NULL;
   pen_dark = NULL;
   pen_black = NULL;
   pen_back = NULL;

   if(SUCCEEDED(retc))
   {
      if(iKpWndStyle == KP_WND_SUNKEN)
      {
// paprastas idubes staciakampis
         if(SUCCEEDED(retc)) retc=KpDrawLine(hDC, iX1, iY1, iX2,   iY1, KP_WND_SUNKEN, iaColorScheme); // aPenScheme);
         if(SUCCEEDED(retc)) retc=KpDrawLine(hDC, iX1, iY1, iX1,   iY2, KP_WND_SUNKEN, iaColorScheme); // aPenScheme);
         if(SUCCEEDED(retc)) retc=KpDrawLine(hDC, iX1, iY2, iX2+1, iY2, KP_WND_SUNKEN, iaColorScheme); // aPenScheme);
         if(SUCCEEDED(retc)) retc=KpDrawLine(hDC, iX2, iY1, iX2,   iY2, KP_WND_SUNKEN, iaColorScheme); // aPenScheme);
      }
      else
      {
         if(SUCCEEDED(retc))
         {
//          if(aPenScheme == NULL)
            if(iaColorScheme == NULL)
            {
               if(SUCCEEDED(retc))
               {
                  pen_norm = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
                  if(pen_norm == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_light = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
                  if(pen_light == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_dark = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowDark]));
                  if(pen_dark == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_black = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowBlack]));
                  if(pen_black == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_back = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowBackground]));
                  if(pen_back == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
            }
            else // if(aPenScheme == NULL)
            {
#if FALSE
               if((aPenScheme[KpShadowNorm]==NULL) && SUCCEEDED(retc))
               {
                  pen_norm = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowNorm]));
                  if(pen_norm == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if((aPenScheme[KpShadowLight]==NULL) && SUCCEEDED(retc))
               {
                  pen_light = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowLight]));
                  if(pen_light == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if((aPenScheme[KpShadowDark]==NULL) && SUCCEEDED(retc))
               {
                  pen_dark = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowDark]));
                  if(pen_dark == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if((aPenScheme[KpShadowBlack]==NULL) && SUCCEEDED(retc))
               {
                  pen_black = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowBlack]));
                  if(pen_black == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if((aPenScheme[KpShadowBackground]==NULL) && SUCCEEDED(retc))
               {
                  pen_back = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[KpShadowBackground]));
                  if(pen_back == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
#else
               if(SUCCEEDED(retc))
               {
                  pen_norm = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowNorm]);
                  if(pen_norm == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_light = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowLight]);
                  if(pen_light == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_dark = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowDark]);
                  if(pen_dark == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_black = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowBlack]);
                  if(pen_black == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  pen_back = CreatePen(PS_SOLID, 1, iaColorScheme[KpShadowBackground]);
                  if(pen_back == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }
#endif
            } // else // if(aPenScheme == NULL)

         } // if(SUCCEEDED(retc))

         if(SUCCEEDED(retc))
         {
            test_sty = iKpWndStyle & (~(KP_WND_TAB|KP_WND_LEFT_TAB|KP_WND_RIGHT_TAB|KP_WND_NO_TOP|KP_WND_URL));
            if(
               (test_sty != KP_WND_RAISED_BORDER) &&
               (test_sty != KP_WND_SUNKEN_BORDER) &&
               (test_sty != KP_WND_RAISED_BUTTON) &&
               (test_sty != KP_WND_SUNKEN_BUTTON) &&
               (test_sty != KP_WND_TOOLBAR)
              )
               retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);
         }

// =======================
         if((iKpWndStyle&KP_WND_RAISED_BORDER) && SUCCEEDED(retc))
         {
            pens[0] = pen_norm; // pen_norm?pen_norm:aPenScheme[KpShadowNorm];
            pens[1] = pen_light; // pen_light?pen_light:aPenScheme[KpShadowLight];
            pens[2] = pen_dark; // pen_dark?pen_dark:aPenScheme[KpShadowDark];
            pens[3] = pen_black; // pen_black?pen_black:aPenScheme[KpShadowBlack];
         }
         if((iKpWndStyle&(KP_WND_RAISED_BUTTON|KP_WND_TAB|KP_WND_TOOLBAR)) && SUCCEEDED(retc)
           )
         {
            pens[0] = pen_light; // pen_light?pen_light:aPenScheme[KpShadowLight];
            pens[1] = pen_norm; // pen_norm?pen_norm:aPenScheme[KpShadowNorm];
            pens[2] = pen_dark; // pen_dark?pen_dark:aPenScheme[KpShadowDark];
            pens[3] = pen_black; // pen_black?pen_black:aPenScheme[KpShadowBlack];
         }
         if(
            (
               (
                  ((iKpWndStyle&(KP_WND_SUNKEN_BUTTON|KP_WND_TAB))==KP_WND_SUNKEN_BUTTON) ||
                  (iKpWndStyle&KP_WND_SUNKEN_BORDER)
               ) &&
               SUCCEEDED(retc)
            )
           )
         {
            pens[0] = pen_dark; // pen_dark?pen_dark:aPenScheme[KpShadowDark];
            pens[1] = pen_black; // pen_black?pen_black:aPenScheme[KpShadowBlack];
            pens[2] = pen_norm; // pen_norm?pen_norm:aPenScheme[KpShadowNorm];
            pens[3] = pen_light; // pen_light?pen_light:aPenScheme[KpShadowLight];
         }
         if(((pens[0]==NULL) || (pens[1]==NULL) || (pens[2]==NULL) || (pens[3]==NULL)) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

         down=down0=down1=down2=down3=down4=right=right1=left=left1=wide=up_left=up_right=0;

         if(((iKpWndStyle&(KP_WND_SUNKEN_BUTTON|KP_WND_TAB))==(KP_WND_SUNKEN_BUTTON|KP_WND_TAB)) && SUCCEEDED(retc))
         {
            down=2;
            wide=1;
            if(!(iKpWndStyle&KP_WND_LEFT_TAB)) left=1;
            if(!(iKpWndStyle&KP_WND_RIGHT_TAB)) right=1;
         }

         if(
            (
               (
                  (iKpWndStyle&KP_WND_TAB) &&
                  (
                     (iKpWndStyle&KP_WND_RAISED_BUTTON) ||
                     (iKpWndStyle&KP_WND_LEFT_TAB)
                  )
               ) ||
               (iKpWndStyle&KP_WND_TOOLBAR)
            ) &&
            SUCCEEDED(retc)
           ){ left1=1; up_left=1; }

         if(
            (
               (
                  (iKpWndStyle&KP_WND_TAB) &&
                  (
                     (iKpWndStyle&KP_WND_RAISED_BUTTON) ||
                     (iKpWndStyle&KP_WND_RIGHT_TAB)
                  )
               ) ||
               (iKpWndStyle&KP_WND_TOOLBAR)
            ) &&
            SUCCEEDED(retc)
           ){ right1=1; up_right=1; }

         if(SUCCEEDED(retc))
         {
            if(iKpWndStyle&(KP_WND_TAB|KP_WND_TOOLBAR))
            {
               if(
                  (iKpWndStyle&(KP_WND_RAISED_BUTTON|KP_WND_TAB))==(KP_WND_RAISED_BUTTON|KP_WND_TAB) ||
                  (iKpWndStyle&KP_WND_TOOLBAR)
                 )
                  { down0=0; down1=0; down2=1; down3=1; }
//             else { down0=0; down1=1; down2=2; down3=1; }
               else { down0=KPW_CTRL_BORDER_WDT; down1=KPW_CTRL_BORDER_WDT; down2=KPW_CTRL_BORDER_WDT; down3=KPW_CTRL_BORDER_WDT;}
            }
            else { down0=0; down1=1; down2=2; down3=1; }
         }
         if((iKpWndStyle&KP_WND_NO_TOP) && SUCCEEDED(retc)) down4=1;


// ======================= fonelis virs virsutinio krasto
         if(SUCCEEDED(retc))
            if(!SelectObject(hDC, pen_back /* pen_back?pen_back:aPenScheme[KpShadowBackground]) */)) // pens[1]))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         if(((iKpWndStyle&(KP_WND_SUNKEN_BUTTON|KP_WND_TAB))==(KP_WND_SUNKEN_BUTTON|KP_WND_TAB)) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1, iY1, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2, iY1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1, iY1+1, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2, iY1+1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }

// ----------------------- tab'o uzapvalinimai
         if(left1 && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1+left1, iY1+down, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX1, iY1+down))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX1, iY1+down+up_left+1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
         if(right1 && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX2-1-right1, iY1+down, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-1, iY1+down))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-1, iY1+down+up_right+1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }

// ======================= virsutinis krastas
         if((!(iKpWndStyle&KP_WND_NO_TOP)) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[0])) // aPenScheme[KpShadowNorm])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1+2*left1, iY1+down, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-1+right-right1, iY1+down))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }

// ---------------- taskas kairiam kampe
         if(left1 && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1+left1, iY1+down+up_left, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX1+left1-1, iY1+down+up_left-1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }

// --------------------- pilka linija zemiau virsutines
         if((!(iKpWndStyle&KP_WND_NO_TOP)) /* && (!(iKpWndStyle&KP_WND_TOOLBAR)) */ && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[1])) // aPenScheme[KpShadowLight])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1+1-left+left1, iY1+1+down, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-2+2*right, iY1+1+down))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }

// ======================= kairys krastas
         if(
            (
               (!(iKpWndStyle&KP_WND_TAB)) ||
               (iKpWndStyle&KP_WND_RAISED_BUTTON) ||
               (iKpWndStyle&KP_WND_LEFT_TAB) ||
               (iKpWndStyle&KP_WND_TOOLBAR)
            ) &&
            SUCCEEDED(retc)
           )
         {
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[0])) // aPenScheme[KpShadowNorm])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1, iY1+down+2*up_left+2*down4, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX1, iY2-down1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// ---------------------
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[1])) // aPenScheme[KpShadowLight])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1+1, iY1+1+down+up_left+down4, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX1+1, iY2-down2))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         } // if(((!(iKpWndStyle&KP_WND_TAB)) || (iKpWndStyle&KP_WND_RAISED_BUTTON) || (iKpWndStyle&KP_WND_LEFT_TAB)) && SUCCEEDED(retc))

// ======================= desinys krastas
         if(
            (
               (!(iKpWndStyle&KP_WND_TAB)) ||
               (iKpWndStyle&KP_WND_RAISED_BUTTON) ||
               (iKpWndStyle&KP_WND_RIGHT_TAB) ||
               (iKpWndStyle&KP_WND_TOOLBAR)
            ) &&
            SUCCEEDED(retc)
           )
         {
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[3])) // aPenScheme[KpShadowBlack])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX2-1, iY1+down+2*up_right+2*down4, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-1, iY2-down0))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// ---------------- taskas desiniam kampe
            if(right1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX2-1-right1, iY1+down+up_right, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX2-1-right1+1, iY1+down+up_right-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

// --------------------- desinio krasto tesinys
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[2])) // aPenScheme[KpShadowDark])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX2-2, iY1+1+down+up_right+down4, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-2, iY2-down3))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         } // if(((!(iKpWndStyle&KP_WND_TAB)) || (iKpWndStyle&KP_WND_RAISED_BUTTON) || (iKpWndStyle&KP_WND_RIGHT_TAB)) && SUCCEEDED(retc))

// ======================= apatinis krastas
         if(((iKpWndStyle&(KP_WND_RAISED_BUTTON|KP_WND_TAB))!=(KP_WND_RAISED_BUTTON|KP_WND_TAB)) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc))
            {
               if((iKpWndStyle&(KP_WND_SUNKEN_BUTTON|KP_WND_TAB))==(KP_WND_SUNKEN_BUTTON|KP_WND_TAB)) pen=pens[1];
               else pen=pens[3]; // aPenScheme[KpShadowBlack])) //

               if(!SelectObject(hDC, pen))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1, iY2-1, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2, iY2-1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// ---------------------
            if(SUCCEEDED(retc))
            {
               if((iKpWndStyle&(KP_WND_SUNKEN_BUTTON|KP_WND_TAB))==(KP_WND_SUNKEN_BUTTON|KP_WND_TAB)) pen=pens[0];
               else pen=pens[2]; // aPenScheme[KpShadowDark])) //

               if(!SelectObject(hDC, pen)) // aPenScheme[KpShadowBlack])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
               if(!MoveToEx(hDC, iX1+1-wide, iY2-2, NULL))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
               if(!LineTo(hDC, iX2-1+wide, iY2-2))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

         } // if(((iKpWndStyle&(KP_WND_RAISED_BUTTON|KP_WND_TAB))!=(KP_WND_RAISED_BUTTON|KP_WND_TAB)) && SUCCEEDED(retc))

// ----------------------- toolbar'o uzapvalinimai
         if((iKpWndStyle&KP_WND_TOOLBAR) && SUCCEEDED(retc))
         {
// ---------------
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pen_back)) // aPenScheme[KpShadowBackground])) // pens[2])) // aPenScheme[KpShadowDark])) //, pen_back /* pen_back?pen_back:aPenScheme[KpShadowBackground]) */)) // pens[1]))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(left1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX1+left1, iY2-down-1, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX1, iY2-down-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX1, iY2-down-up_left-1-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

// ---------------
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[3])) // aPenScheme[KpShadowBlack])) // pens[2])) // aPenScheme[KpShadowDark])) // pen_back)) // aPenScheme[KpShadowBackground])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(right1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX2-1-right1, iY2-down-1, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX2-1, iY2-down-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX2-1, iY2-down-up_right-1-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

// ---------------- taskas kairiam apatiniam kampe
#if FALSE
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[3])) // aPenScheme[KpShadowBlack])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(left1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX1+left1, iY2-down-up_left-1, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX1+left1+1, iY2-down-up_left-1-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pen_back)) // aPenScheme[KpShadowBackground])) // pens[3])) // aPenScheme[KpShadowBlack])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(left1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX1, iY2-1, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX1+1, iY2-1-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }
#endif

// ---------------- taskas desiniam apatiniam kampe
            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[3])) // aPenScheme[KpShadowBlack])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(right1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX2-1-right1, iY2-down-up_left-1, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX2-1-right1-1, iY2-down-up_left-1-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }


            if(SUCCEEDED(retc))
               if(!SelectObject(hDC, pens[2])) // aPenScheme[KpShadowDark])) // pens[3])) // aPenScheme[KpShadowBlack])) //
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(left1 && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc))
                  if(!MoveToEx(hDC, iX2-1, iY2-1, NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  if(!LineTo(hDC, iX2-1, iY2-1-1))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

         } // if((iKpWndStyle&KP_WND_TOOLBAR) && SUCCEEDED(retc))

      } // else // if(iKpWndStyle == KP_WND_SUNKEN)

   } // if(SUCCEEDED(retc))

   if(pen_norm) if(!DeleteObject(pen_norm))
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_norm = NULL;
   if(pen_light) if(!DeleteObject(pen_light))
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_light = NULL;
   if(pen_dark) if(!DeleteObject(pen_dark))
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_dark = NULL;
   if(pen_black) if(!DeleteObject(pen_black))
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_black = NULL;
   if(pen_back) if(!DeleteObject(pen_back))
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   pen_back = NULL;

return(retc);
}


HRESULT KpDrawRect(HDC hDC, RECT Rect, int iKpWndStyle, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
return(KpDrawRect(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom, iKpWndStyle, iaColorScheme));
}


// ---------------------------
HRESULT KpDrawBox(HDC hDC, int iX1, int iY1, int iX2, int iY2, KpShadow iShadow, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HPEN pen = NULL;

// KP_ASSERT(PenScheme != NULL, E_INVALIDARG, GetLastError(), True);

   KP_ASSERT((iShadow >= 0) && (iShadow < KpNumOfShadows0), E_INVALIDARG, GetLastError(), True);

   pen = NULL;

   if(SUCCEEDED(retc))
   {
//    if(aPenScheme == NULL)
      if(iaColorScheme == NULL)
      {
         if(SUCCEEDED(retc))
            pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[iShadow]));
         KP_ASSERT(pen != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);
      }
      else
      {
#if FALSE
         if((aPenScheme[iShadow] == NULL) && SUCCEEDED(retc))
            pen = CreatePen(PS_SOLID, 1, GetSysColor(iaColorMap[iShadow]));
         KP_ASSERT(pen != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);
#else
         if(SUCCEEDED(retc))
            pen = CreatePen(PS_SOLID, 1, iaColorScheme[iShadow]);
         KP_ASSERT(pen != NULL, KP_E_SYSTEM_ERROR, GetLastError(), False);
#endif
      }

   } // if(SUCCEEDED(retc))

// -------------------
   KP_ASSERT(SelectObject(hDC, pen), KP_E_SYSTEM_ERROR, GetLastError(), False);

   for(int jj = iY1; (jj <= iY2) && SUCCEEDED(retc); jj++)
   {
      KP_ASSERT(MoveToEx(hDC, iX1, jj, NULL), KP_E_SYSTEM_ERROR, GetLastError(), False);
      KP_ASSERT(LineTo(hDC, iX2, jj), KP_E_SYSTEM_ERROR, GetLastError(), False);
   }

   if(pen != NULL) KP_ASSERT0(DeleteObject(pen), KP_E_SYSTEM_ERROR, GetLastError(), False);
   pen = NULL;

return(retc);
}


HRESULT KpDrawBox(HDC hDC, RECT Rect, KpShadow iShadow, COLORREF iaColorScheme[KpNumOfShadows0]) // HPEN aPenScheme[KpNumOfShadows0])
{
return(KpDrawBox(hDC, Rect.left, Rect.top, Rect.right, Rect.bottom, iShadow, iaColorScheme));
}


//================================================
#if FALSE
// #ifdef TEST_WATCOM


// ----------------------
// winhand.cpp:
CObject* CHandleMap::FromHandle(HANDLE h)
{
HRESULT retc=S_OK;
CObject* pTemp=NULL; // return value
CObject* pObject=NULL;
HANDLE* ph=NULL;

   if(SUCCEEDED(retc))
   {
//    ASSERT(m_pClass != NULL);
//    ASSERT(m_nHandles == 1 || m_nHandles == 2);
      if((m_pClass==NULL) || ((m_nHandles!=1) && (m_nHandles!=2)))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      if(h==NULL)
//       return NULL
         ;
      else
      {
         pObject=LookupPermanent(h);
         if(pObject!=NULL) pTemp=pObject;   // return permanent one
         else if((pObject=LookupTemporary(h))!=NULL)
         {
            ph=(HANDLE*)((BYTE*)pObject + m_nOffset);
//          ASSERT((ph[0]==h) || (ph[0]==NULL));
            if((ph[0]!=h) && (ph[0]!=NULL))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               ph[0]=h;
               if(m_nHandles==2)
               {
//                ASSERT((ph[1]==h) || (ph[1]==NULL));
                  if((ph[1]!=h) && (ph[1]!=NULL))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc)) ph[1]=h;
               }

               if(SUCCEEDED(retc)) pTemp=pObject;   // return current temporary one
            }
         }
         else
         {
// This handle wasn't created by us, so we must create a temporary
// C++ object to wrap it.  We don't want the user to see this memory
// allocation, so we turn tracing off.

//          BOOL bEnable = AfxEnableMemoryTracking(FALSE);
// #ifndef _AFX_PORTABLE
//          _PNH pnhOldHandler = AfxSetNewHandler(&AfxCriticalNewHandler);
// #endif

//          TRY
            {
               pTemp = m_pClass->CreateObject();
               if(pTemp==NULL)
//             AfxThrowMemoryException();
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               if(SUCCEEDED(retc))
                  m_temporaryMap.SetAt((LPVOID)h, pTemp);
            }
//          CATCH_ALL(e)
//          {
// #ifndef _AFX_PORTABLE
//             AfxSetNewHandler(pnhOldHandler);
// #endif
//             AfxEnableMemoryTracking(bEnable);
//             THROW_LAST();
//          }
//          END_CATCH_ALL

// #ifndef _AFX_PORTABLE
//          AfxSetNewHandler(pnhOldHandler);
// #endif
//          AfxEnableMemoryTracking(bEnable);

// now set the handle in the object
            if(SUCCEEDED(retc))
            {
               ph=(HANDLE*)((BYTE*)pTemp + m_nOffset);  // after CObject
               ph[0]=h;
               if(m_nHandles == 2)
                  ph[1]=h;
            }

         } // else // else if((pObject=LookupTemporary(h))!=NULL)

      } // else // if(h==NULL)

   } // if(SUCCEEDED(retc))

return(pTemp);
}


// ----------------------
// wingdi.cpp:
CDC* PASCAL CDC::FromHandle(HDC hDC)
{
HRESULT retc=S_OK;
CHandleMap* pMap=NULL;
CDC* pDC=NULL;

   if(SUCCEEDED(retc))
   {
      pMap = afxMapHDC(TRUE); //create map if not exist
//    ASSERT(pMap != NULL);
      if(pMap==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      pDC=(CDC*)pMap->FromHandle(hDC);
//    ASSERT(pDC == NULL || pDC->m_hDC == hDC);
      if(pDC!=NULL)
         if(pDC->m_hDC!=hDC)
         {
            pDC=NULL;
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
   }

return pDC;
}





// ----------------------
// wingdi.h:
COLORREF WINAPI GetDCBrushColor(HDC hdc)
{
// DC *dc;
CDC *pdc;
COLORREF dcBrushColor = CLR_INVALID;

//  TRACE("hdc(%p)", hdc);


   pdc = CDC::FromHandle(hdc);


//   dc = DC_GetDCPtr( hdc );
//   if (dc)
//   {
//      dcBrushColor = dc->dcBrushColor;
//   }

return dcBrushColor;
}

#endif // #ifdef TEST_WATCOM

#endif // #if (Envir==MSWin32) || (Envir==MSWin32Mfc)


//------------------------------------------------------------
// registro rakto security atverimas rasymui
// http://support.microsoft.com/kb/146906
HRESULT SetRegKeyAccess(unsigned char *lpszKeyName)
{
HRESULT retc = S_OK;
LONG retw=ERROR_SUCCESS;
HKEY hKey=0;
SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
PSID pInteractiveSid = NULL;
PSID pAdministratorsSid = NULL;
SECURITY_DESCRIPTOR sd;
PACL pDacl = NULL;
DWORD dwAclSize;

   if(SUCCEEDED(retc))
   {
      retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)lpszKeyName, 0, WRITE_DAC /* STANDARD_RIGHTS_READ */, &hKey);
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }


#if FALSE
SECURITY_DESCRIPTOR sec_desc[10];
DWORD sec_size = sizeof(sec_desc);
   if(SUCCEEDED(retc))
   {
      retw=RegGetKeySecurity(hKey, DACL_SECURITY_INFORMATION, sec_desc, &sec_size);
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }
// if(SUCCEEDED(retc))
// {
//    retw=RegSetKeySecurity(hKey, DACL_SECURITY_INFORMATION, &sec_desc);
//    if(retw!=ERROR_SUCCESS)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
// }
#endif


// prepare a Sid representing any Interactively logged-on user
   if(SUCCEEDED(retc))
      if(!AllocateAndInitializeSid(
         &sia,
         1,
         SECURITY_INTERACTIVE_RID,
         0, 0, 0, 0, 0, 0, 0,
         &pInteractiveSid
         ))
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);

// prepare a Sid representing the well-known admin group
   if(SUCCEEDED(retc))
      if(!AllocateAndInitializeSid(
         &sia,
         2,
         SECURITY_BUILTIN_DOMAIN_RID,
         DOMAIN_ALIAS_RID_ADMINS,
         0, 0, 0, 0, 0, 0,
         &pAdministratorsSid
         ))
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
// compute size of new acl
      dwAclSize = sizeof(ACL) +
         2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) +
         GetLengthSid(pInteractiveSid) +
         GetLengthSid(pAdministratorsSid) ;

// allocate storage for Acl
      pDacl = (PACL)HeapAlloc(GetProcessHeap(), 0, dwAclSize);
      if(pDacl == NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
      if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// grant the Interactive Sid KEY_READ access to the key
   if(SUCCEEDED(retc))
      if(!AddAccessAllowedAce(
            pDacl,
            ACL_REVISION,
            KEY_READ,
            pInteractiveSid
         ))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// grant the Administrators Sid GENERIC_ALL access to the key
   if(SUCCEEDED(retc))
      if(!AddAccessAllowedAce(
            pDacl,
            ACL_REVISION,
            KEY_ALL_ACCESS,
            pAdministratorsSid
         ))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// apply the security descriptor to the registry key
   if(SUCCEEDED(retc))
   {
      retw = RegSetKeySecurity(
            hKey,
            (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION,
            &sd
            );
      if(retw!=ERROR_SUCCESS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
   }

// free open key
   if(hKey)
   {
      retw=RegCloseKey(hKey);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      hKey=0;
   }

// close root key to refresh security attributes
   if(SUCCEEDED(retc))
   {
      retw = RegCloseKey(HKEY_LOCAL_MACHINE);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
   }

// free allocated resources
   if(pDacl != NULL) HeapFree(GetProcessHeap(), 0, pDacl);
   if(pInteractiveSid != NULL) FreeSid(pInteractiveSid);
   if(pAdministratorsSid != NULL) FreeSid(pAdministratorsSid);


// -------------------------------------------------------
// rekursinam vaikams
bool done;
int cur_key = 0;
DWORD key_len;
unsigned char *sub_key_name = null;
unsigned char *cur_key_name = null;

   KP_NEWA(sub_key_name, unsigned char, KP_MAX_FNAME_LEN + 1);
   KP_NEWA(cur_key_name, unsigned char, KP_MAX_FNAME_LEN + 1);

   if(SUCCEEDED(retc)) retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (const char *)lpszKeyName, 0, KEY_ENUMERATE_SUB_KEYS, &hKey);
   KP_ASSERT(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, True);

   if(SUCCEEDED(retc))
   {
      done = False;
      cur_key = 0;
      while((!done) && SUCCEEDED(retc))
      {
         key_len = KP_MAX_FNAME_LEN;
         retw=RegEnumKeyEx(
            hKey, // HKEY hKey,
            cur_key, // DWORD dwIndex,
            (char *)sub_key_name, // LPTSTR lpName,
            &key_len, // LPDWORD lpcName,
            NULL, // LPDWORD lpReserved,
            NULL, // LPTSTR lpClass,
            NULL, // LPDWORD lpcClass,
            NULL // PFILETIME lpftLastWriteTime
            );
         if(retw == ERROR_NO_MORE_ITEMS) done = True;
         else if(retw!=ERROR_SUCCESS)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);

         if((!done) && SUCCEEDED(retc))
         {
// KpMsgOut(sub_key_name, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

            if(strlen(lpszKeyName) + strlen(sub_key_name) + 2 >= KP_MAX_FNAME_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);

            if(SUCCEEDED(retc))
            {
               strcpy(cur_key_name, lpszKeyName);
               strcat(cur_key_name, "\\");
               strcat(cur_key_name, sub_key_name);

               retc = SetRegKeyAccess(cur_key_name);
            }

         } // if((!done) && (retw==ERROR_SUCCESS))

         cur_key++;

      } // while((!done) && SUCCEEDED(retc))

   } // if(SUCCEEDED(retc))

   if(hKey)
   {
      retw=RegCloseKey(hKey);
//    if(retw!=ERROR_SUCCESS) retc=KP_E_KWD_NOT_FOUND;
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      hKey=NULL;
   }

   KP_DELETEA(sub_key_name);
   KP_DELETEA(cur_key_name);

return(retc);
}


//------------------------------------------------------------
/* LONG */ HRESULT KpRegDeleteTree(HKEY hKey, const unsigned char *lpszSubKey, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
HKEY hSubKey = 0;
LONG retw = ERROR_SUCCESS;
bool done;
// int cur_key = 0;
DWORD key_len;
unsigned char *sub_key_name = NULL;

   KP_NEWA(sub_key_name, unsigned char, KP_MAX_FNAME_LEN + 1);

//-------------------------
   if(lpszSubKey == NULL)
   {
      if(SUCCEEDED(retc))
      {
         done = False;
//       cur_key = 0;
         while((!done) && SUCCEEDED(retc))
         {
            key_len = KP_MAX_FNAME_LEN;
            retw = RegEnumKeyEx(
               hKey, // HKEY hKey,
               0, // cur_key, // DWORD dwIndex, // visada pirma - nes ankstesnis jau istrintas ir visi pasistume
               (char *)sub_key_name, // LPTSTR lpName,
               &key_len, // LPDWORD lpcName,
               NULL, // LPDWORD lpReserved,
               NULL, // LPTSTR lpClass,
               NULL, // LPDWORD lpcClass,
               NULL // PFILETIME lpftLastWriteTime
               );
            if(retw == ERROR_NO_MORE_ITEMS) done = True;
            else KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, !bIgnoreErrors);

            if((!done) && SUCCEEDED(retc))
            {
// KpMsgOut(sub_key_name, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

               retc = KpRegDeleteTree(hKey, sub_key_name, bIgnoreErrors);
            }

//          cur_key++;

         } // while((!done) && SUCCEEDED(retc))

      } // if(SUCCEEDED(retc))

   }
   else // if(lpszSubKey == NULL)
   {
      if(SUCCEEDED(retc))
      {
         retw = RegOpenKeyEx(hKey, (const char *)lpszSubKey, 0,
            DELETE | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE, &hSubKey);
         KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, !bIgnoreErrors);
      }

      if(SUCCEEDED(retc)) retc = KpRegDeleteTree(hSubKey, NULL, bIgnoreErrors);

      if(hSubKey)
      {
         retw = RegCloseKey(hSubKey);
#ifdef Debug
         KP_ASSERT(retw == ERROR_SUCCESS, KP_E_KWD_NOT_FOUND, null, False);
#endif
         hSubKey=NULL;
      }

      if(SUCCEEDED(retc))
      {
         retw = RegDeleteKey(hKey, (const char *)lpszSubKey);
//       KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, !bIgnoreErrors);
         KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, lpszSubKey, !bIgnoreErrors);
      }
   }

// -----------------------------
   KP_DELETEA(sub_key_name);

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


// --------------------------------------
HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpValueName, DWORD dwValType, const LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors)
{
HRESULT retc=S_OK;
unsigned char key_name_sav[KP_MAX_FNAME_LEN+1];
   key_name_sav[0] = Nul;
DWORD buf_len;
DWORD val_type;
BYTE data_buf[KP_MAX_FNAME_LEN+1];
LONG retw=ERROR_SUCCESS;

// -------------------------
   KP_ASSERT(lpValueName != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpDataBuf != NULL, E_INVALIDARG, null, True);
   KP_ASSERTE(strlen(lpValueName) + strlen("_sav") < KP_MAX_FNAME_LEN, E_INVALIDARG, null, !bIgnoreErrors);

   if(SUCCEEDED(retc))
   {
      strcpy(key_name_sav, lpValueName);
      strcat(key_name_sav, "_sav");
   }

// --------------------------- i?saugojam buvusi? reik?m_
   if(SUCCEEDED(retc))
   {
      buf_len = KP_MAX_FNAME_LEN;
      retw = RegQueryValueEx(hKey, (const char *)key_name_sav, NULL, &val_type, data_buf, &buf_len);
      if((retw != ERROR_SUCCESS) && (retw != ERROR_MORE_DATA))
      {
// -------------- senos i?saugotos reik?m?s dar n?ra - saugojam
         buf_len = KP_MAX_FNAME_LEN;
         retw = RegQueryValueEx(hKey, lpValueName, NULL, &val_type, data_buf, &buf_len);
         KP_ASSERTE(retw != ERROR_MORE_DATA, KP_E_BUFFER_OVERFLOW, retw, !bIgnoreErrors);
         if(SUCCEEDED(retc))
         {
            if(retw != ERROR_SUCCESS) // jei dar n?ra nustatyto - n?r k? saugot
            {
//             if(val_type == dwValType) // ???
                  KP_WARNING(KP_E_KWD_NOT_FOUND, null);
            }
            else
            {
               retw = RegSetValueEx(hKey, (const char *)key_name_sav, 0L, val_type, data_buf, buf_len);
               KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_FERROR, retw, !bIgnoreErrors);
            }
         }
      }
   }

// --------------------------- ?ra?om nauj? reik?m_
   if(SUCCEEDED(retc))
   {
      retw = RegSetValueEx(hKey, lpValueName, 0L, dwValType, lpDataBuf, dwBufLen);
      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_FERROR, retw, !bIgnoreErrors);

#if FALSE // #ifdef Debug
if(strcmp(lpValueName, "iDockPosition") == 0)
{
char str_buf[400];
sprintf(str_buf, "------- KpRegSetValue(HKEY, LPCTSTR lpValueName, ...) %s %d %d",
   (hKey==HKEY_LOCAL_MACHINE)?"HKEY_LOCAL_MACHINE":((hKey==HKEY_CURRENT_USER)?"HKEY_CURRENT_USER":"HKEY_???"),
   retw, ERROR_SUCCESS);
KP_TRACE(str_buf);
}
#endif
   }

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwValType, const LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors)
{
HRESULT retc=S_OK;
HKEY key = NULL;

   KP_ASSERTE(ERROR_SUCCESS == RegCreateKeyEx(hKey, lpSubKey,
      0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &key, NULL),
         KP_E_KWD_NOT_FOUND, GetLastError(), !bIgnoreErrors);

   if(SUCCEEDED(retc))
      retc = KpRegSetValue(key, lpValueName, dwValType, lpDataBuf, dwBufLen, bIgnoreErrors);

   if(key) RegCloseKey(key);
   key = NULL;

#if FALSE // #ifdef Debug
if(strcmp(lpValueName, "iDockPosition") == 0)
{
char str_buf[400];
sprintf(str_buf, "------- KpRegSetValue(HKEY, LPCTSTR lpSubKey, ...) %s %d %d",
   (hKey==HKEY_LOCAL_MACHINE)?"HKEY_LOCAL_MACHINE":((hKey==HKEY_CURRENT_USER)?"HKEY_CURRENT_USER":"HKEY_???"),
// lpSubKey, lpValueName,
   bIgnoreErrors, retc);
KP_TRACE(str_buf);
}
#endif

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, bool bIgnoreErrors, DWORD dwValType)
{
HRESULT retc = S_OK;
const unsigned char *str_val;

   str_val = lpszData;
   retc = KpRegSetValue(hKey, lpSubKey, lpValueName, dwValType /* REG_BINARY */, (LPBYTE)str_val, strlen(str_val) + 1, bIgnoreErrors);

return(retc);
}


HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpszSubKey, LPCTSTR lpValueName, const char *lpszData, bool bIgnoreErrors, DWORD dwValType)
{
return(KpRegSetValue(hKey, lpszSubKey, lpValueName, (const unsigned char *)lpszData, bIgnoreErrors, dwValType));
}


HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
DWORD data_val;

   data_val = iData;
   retc = KpRegSetValue(hKey, lpSubKey, lpValueName, REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), bIgnoreErrors);

return(retc);
}


HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwValType, const LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors)
{
HRESULT retc = S_OK;

   if(((iKey & KP_HKEY_LOCAL_MACHINE) == KP_HKEY_LOCAL_MACHINE) && SUCCEEDED(retc))
      retc = KpRegSetValue(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName, dwValType, lpDataBuf, dwBufLen, ((iKey & KP_HKEY_CURRENT_USER) == KP_HKEY_CURRENT_USER) || bIgnoreErrors);

   if(((iKey & KP_HKEY_CURRENT_USER) == KP_HKEY_CURRENT_USER) && SUCCEEDED(retc))
      retc = KpRegSetValue(HKEY_CURRENT_USER, lpSubKey, lpValueName, dwValType, lpDataBuf, dwBufLen, bIgnoreErrors);

   if(((iKey & KP_HKEY_NONE) != 0) && SUCCEEDED(retc))
      retc = KpRegSetValue((HKEY)(iKey & KP_HKEY_CLEAR), lpSubKey, lpValueName, dwValType, lpDataBuf, dwBufLen, bIgnoreErrors);

return(retc);
}


HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, bool bIgnoreErrors, DWORD dwValType)
{
HRESULT retc = S_OK;
const unsigned char *str_val;

   str_val = lpszData;
   retc = KpRegSetValue(iKey, lpSubKey, lpValueName, dwValType /* REG_BINARY */ /* REG_SZ */, (const LPBYTE)str_val, strlen(str_val) + 1, bIgnoreErrors);

return(retc);
}


HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, bool bIgnoreErrors, DWORD dwValType)
{
return(KpRegSetValue(iKey, lpSubKey, lpValueName, (const unsigned char *)lpszData, bIgnoreErrors, dwValType));
}


HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
DWORD data_val;

   data_val = iData;
   retc = KpRegSetValue(iKey, lpSubKey, lpValueName, REG_DWORD, (LPBYTE)&data_val, sizeof(data_val), bIgnoreErrors);

return(retc);
}


HRESULT KpRegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData, bool bIgnoreErrors)
{
return(KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, lpSubKey, lpValueName, iData, bIgnoreErrors));
}


HRESULT KpRegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, bool bIgnoreErrors, DWORD dwValType)
{
return(KpRegSetValue(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, lpSubKey, lpValueName, lpszData, bIgnoreErrors, dwValType));
}


HRESULT KpRegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, bool bIgnoreErrors, DWORD dwValType)
{
return(KpRegSetValue(lpSubKey, lpValueName, (const unsigned char *)lpszData, bIgnoreErrors, dwValType));
}


HRESULT KpRegSetValueAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, DWORD dwValType)
{
HRESULT retc = S_OK;
/* unsigned */ char key_name[KP_MAX_FNAME_LEN+1];

   sprintf(key_name, "SOFTWARE\\Adobe\\Acrobat Reader\\%d.%d\\%s", iVers / 100, iVers % 100, lpSubKey);
   retc = KpRegSetValue(key_name, lpValueName, lpszData, True, dwValType);

return(retc);
}


HRESULT KpRegSetValueAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, DWORD dwValType)
{
return(KpRegSetValueAcro(iVers, lpSubKey, lpValueName, (const unsigned char *)lpszData, dwValType));
}


HRESULT KpRegSetValueAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData)
{
HRESULT retc = S_OK;
/* unsigned */ char key_name[KP_MAX_FNAME_LEN+1];

   sprintf(key_name, "SOFTWARE\\Adobe\\Acrobat Reader\\%d.%d\\%s", iVers / 100, iVers % 100, lpSubKey);
   retc = KpRegSetValue(key_name, lpValueName, iData);

return(retc);
}

HRESULT KpRegSetValueAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, DWORD dwValType)
{
HRESULT retc = S_OK;
/* unsigned */ char key_name[KP_MAX_FNAME_LEN + 1];

   sprintf(key_name, "SOFTWARE\\Adobe\\Acrobat Reader\\%s\\%s", lpszVers, lpSubKey);
   retc = KpRegSetValue(key_name, lpValueName, lpszData, True, dwValType);

return(retc);
}

HRESULT KpRegSetValueAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, DWORD dwValType)
{
return KpRegSetValueAcro(lpszVers, lpSubKey, lpValueName, (const unsigned char *)lpszData, dwValType);
}

HRESULT KpRegSetValueAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData)
{
HRESULT retc = S_OK;
/* unsigned */ char key_name[KP_MAX_FNAME_LEN+1];

   sprintf(key_name, "SOFTWARE\\Adobe\\Acrobat Reader\\%s\\%s", lpszVers, lpSubKey);
   retc = KpRegSetValue(key_name, lpValueName, iData);

return(retc);
}


// --------------------------------------
HRESULT KpRegRestore(HKEY hKey, LPCTSTR lpValueName, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
unsigned char key_name_sav[KP_MAX_FNAME_LEN + 1];
   key_name_sav[0] = Nul;
DWORD buf_len;
DWORD val_type;
BYTE data_buf[KP_MAX_FNAME_LEN + 1];
LONG retw = ERROR_SUCCESS;

// -------------------------
   KP_ASSERT(lpValueName != NULL, E_INVALIDARG, null, True);
   KP_ASSERTE(strlen(lpValueName) + strlen("_sav") < KP_MAX_FNAME_LEN, E_INVALIDARG, null, !bIgnoreErrors);

   if(SUCCEEDED(retc))
   {
      strcpy(key_name_sav, lpValueName);
      strcat(key_name_sav, "_sav");
   }

// --------------------------- atstatom i?saugot? reik?m_
   if(SUCCEEDED(retc))
   {
      buf_len = KP_MAX_FNAME_LEN;
      retw = RegQueryValueEx(hKey, (const char *)key_name_sav, NULL, &val_type, data_buf, &buf_len);
      if(retw == ERROR_MORE_DATA) KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_BUFFER_OVERFLOW, retw, !bIgnoreErrors)
      else if(retw == ERROR_SUCCESS)
// ------------------------- i?saugot? reik?m_ radom - atstatom
      {
         retw = RegSetValueEx(hKey, lpValueName, 0L, val_type, data_buf, buf_len);
         KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_FERROR, retw, !bIgnoreErrors);

         if(SUCCEEDED(retc))
         {
            retw = RegDeleteValue(hKey, (const char *)key_name_sav);
            if(retw != ERROR_SUCCESS) KP_WARNING(KP_E_FERROR, retw);
         }
      }
      else // if(retw == ERROR_SUCCESS)
      {
// ----------------------- i?saugotos reik?m?s nebuvo - tai ir v?l i?trinam
         retw = RegDeleteValue(hKey, lpValueName);
         if(retw != ERROR_SUCCESS)
         {
#ifdef Debug
// matyt, i?trina pats Acrobatas
//          retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
#endif
         }
      }
   }

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


HRESULT KpRegRestore(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
HKEY key = NULL;

   KP_ASSERTE(ERROR_SUCCESS == RegCreateKeyEx(hKey, lpSubKey,
      0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &key, NULL),
         KP_E_KWD_NOT_FOUND, GetLastError(), !bIgnoreErrors);

   if(SUCCEEDED(retc)) retc = KpRegRestore(key, lpValueName, bIgnoreErrors);

   if(key) RegCloseKey(key);
   key = NULL;

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


HRESULT KpRegRestore(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bIgnoreErrors)
{
HRESULT retc = S_OK;

   if(((iKey & KP_HKEY_LOCAL_MACHINE) == KP_HKEY_LOCAL_MACHINE) && SUCCEEDED(retc))
      retc = KpRegRestore(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName, ((iKey & KP_HKEY_CURRENT_USER) == KP_HKEY_CURRENT_USER) || bIgnoreErrors);

   if(((iKey & KP_HKEY_CURRENT_USER) == KP_HKEY_CURRENT_USER) && SUCCEEDED(retc))
      retc = KpRegRestore(HKEY_CURRENT_USER, lpSubKey, lpValueName, bIgnoreErrors);

   if(((iKey & KP_HKEY_NONE) != 0) && SUCCEEDED(retc))
      retc = KpRegRestore((HKEY)(iKey & KP_HKEY_CLEAR), lpSubKey, lpValueName, bIgnoreErrors);

return(retc);
}


extern HRESULT KpRegRestore(LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bIgnoreErrors)
{
return(KpRegRestore(/* KP_HKEY_LOCAL_MACHINE | KP_ */ HKEY_CURRENT_USER, lpSubKey, lpValueName, bIgnoreErrors));
}


extern HRESULT KpRegRestoreAcro(int iVers, const char *lpszSubKey, LPCTSTR lpValueName)
{
HRESULT retc = S_OK;
/* unsigned */ char key_name[KP_MAX_FNAME_LEN+1];

   sprintf(key_name, "SOFTWARE\\Adobe\\Acrobat Reader\\%d.%d\\%s", iVers / 100, iVers % 100, lpszSubKey);
   retc = KpRegRestore(key_name, lpValueName, True);

return(retc);
}


extern HRESULT KpRegRestoreAcro(const char *lpszVers, const char *lpszSubKey, LPCTSTR lpValueName)
{
HRESULT retc = S_OK;
/* unsigned */ char key_name[KP_MAX_FNAME_LEN+1];

   sprintf(key_name, "SOFTWARE\\Adobe\\Acrobat Reader\\%s\\%s", lpszVers, lpszSubKey);
   retc = KpRegRestore(key_name, lpValueName, True);

return(retc);
}


// -------------------------------
HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpValueName, DWORD dwValType, LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
DWORD buf_len;
DWORD val_type;
LONG retw = ERROR_SUCCESS;

// -------------------------
   KP_ASSERT(lpValueName != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpDataBuf != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) memset(lpDataBuf, 0, dwBufLen);

// ---------------------------
   if(SUCCEEDED(retc))
   {
      buf_len = dwBufLen;
      retw = RegQueryValueEx(hKey, lpValueName, NULL, &val_type, lpDataBuf, &buf_len);
//    KP_ASSERTE(retw == ERROR_SUCCESS, (retw == ERROR_MORE_DATA)?KP_E_BUFFER_OVERFLOW:KP_E_KWD_NOT_FOUND, retw, (!bIgnoreErrors) && (retw == ERROR_MORE_DATA));
//    KP_ASSERT0(retw == ERROR_SUCCESS, retc, lpValueName, False);
      KP_ASSERTE(retw != ERROR_MORE_DATA, KP_E_BUFFER_OVERFLOW, retw, !bIgnoreErrors);
      if(SUCCEEDED(retc)) if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
   }
   if(SUCCEEDED(retc))
   {
      if((val_type == REG_SZ) || (val_type == REG_BINARY))
      {
         KP_ASSERTE(buf_len < dwBufLen, KP_E_BUFFER_OVERFLOW, null, !bIgnoreErrors);
         if(buf_len < dwBufLen) lpDataBuf[buf_len] = Nul;
      }
      if((dwValType == REG_SZ) || (dwValType == REG_BINARY))
         KP_ASSERTE((val_type == REG_SZ) || (val_type == REG_BINARY), KP_E_FILE_FORMAT, null, !bIgnoreErrors)
      else
         KP_ASSERTE(val_type == dwValType, KP_E_FILE_FORMAT, null, !bIgnoreErrors);
   }

   if((lpDataBuf != null) && FAILED(retc)) memset(lpDataBuf, 0, dwBufLen);

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwValType, LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors)
{
HRESULT retc = S_OK;
HKEY key = NULL;
LONG retw = ERROR_SUCCESS;

   KP_ASSERT(lpSubKey != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpValueName != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpDataBuf != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) memset(lpDataBuf, 0, dwBufLen);

   if(SUCCEEDED(retc))
   {
//    retw = RegCreateKeyEx(hKey, lpSubKey, 0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL);
      retw = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_QUERY_VALUE, &key);
//    KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_KWD_NOT_FOUND, GetLastError(), False /* !bIgnoreErrors */);
      if(retw != ERROR_SUCCESS) retc = KP_E_KWD_NOT_FOUND;
      if(retw != ERROR_SUCCESS) key = NULL;
   }

   if(SUCCEEDED(retc)) retc = KpRegQueryValue(key, lpValueName, dwValType, lpDataBuf, dwBufLen, bIgnoreErrors);

   if(key != NULL) RegCloseKey(key);
   key = NULL;

   if(bIgnoreErrors) retc = S_OK;

return(retc);
}


HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, unsigned char *lpszData, DWORD dwBufLen, bool bIgnoreErrors)
{
return(KpRegQueryValue(hKey, lpSubKey, lpValueName, /* REG_SZ */ REG_BINARY, (const LPBYTE)lpszData, dwBufLen, bIgnoreErrors));
}


HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, char *lpszData, DWORD dwBufLen, bool bIgnoreErrors)
{
return(KpRegQueryValue(hKey, lpSubKey, lpValueName, (unsigned char *)lpszData, dwBufLen, bIgnoreErrors));
}


HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, PDWORD *piData, bool bIgnoreErrors)
{
return(KpRegQueryValue(hKey, lpSubKey, lpValueName, REG_DWORD, (LPBYTE)piData, sizeof(DWORD), bIgnoreErrors));
}


// -------------------------------
HRESULT KpRegExportBranch(fstream *pOutFstream, HKEY hQueryKey, unsigned const char *lpszKeyName, bool bEncode)
{
HRESULT retc = S_OK;
HKEY hKey = NULL;
unsigned char key_name[200 + 1];
unsigned char sub_key_name[400 + 1];
unsigned char class_name[200 + 1];
union
{
   char text[200 + 1];
   DWORD num;
} val_buf;
DWORD key_ix;
DWORD name_len;
DWORD class_len;
LONG retw = ERROR_SUCCESS;
DWORD dwBufLen;
DWORD dwValType;
unsigned char *str_buf = null;
int str_buf_len = 0;

   KP_ASSERT(pOutFstream, E_INVALIDARG, null, True);
   KP_ASSERT(lpszKeyName, E_INVALIDARG, null, True);

   KP_NEWA(str_buf, unsigned char, /* KP_MAX_FNAME_LEN + 100 */ 10000);

   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "\n%s\n", lpszKeyName); str_buf_len = strlen(str_buf);
      if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, str_buf_len);
      pOutFstream->write((const char *)str_buf, str_buf_len);

      retw = RegOpenKeyEx(hQueryKey, (const char *)lpszKeyName, 0, KEY_QUERY_VALUE|KEY_ENUMERATE_SUB_KEYS, &hKey);
      if(retw != ERROR_SUCCESS)
      {
         sprintf((char *)str_buf, "------------ neatsidaro retw = %d\n", retw); str_buf_len = strlen(str_buf);
         if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, str_buf_len);
         pOutFstream->write((const char *)str_buf, str_buf_len);
      }
      else
      {
// ---------------------------------- enum values
         key_ix = 0;
         do
         {
            name_len = 200;
            dwBufLen = 200;

//          retw = RegQueryValueEx(hKey, key_name, NULL, &dwValType,
            retw = RegEnumValue(hKey, key_ix++, (char *)key_name, &name_len, NULL, &dwValType, (LPBYTE)&val_buf, &dwBufLen);
            if(retw == ERROR_NO_MORE_ITEMS) break;
            else if(retw != ERROR_SUCCESS)
            {
               sprintf((char *)str_buf, "------------ neskaito retw = %d %d\n", retw, key_ix - 1); str_buf_len = strlen(str_buf);
               if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, str_buf_len);
               pOutFstream->write((const char *)str_buf, str_buf_len);
            }
            else
            {
               switch(dwValType)
               {
               case REG_DWORD: sprintf((char *)str_buf, "%s %x\n", key_name, val_buf.num); break;
               case REG_SZ: sprintf((char *)str_buf, "%s %s\n", key_name, val_buf.text); break;
               default: sprintf((char *)str_buf, ": ------------- dwValType = %ld", dwValType); break;
               }
               str_buf_len = strlen(str_buf);
               if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, str_buf_len);
               pOutFstream->write((const char *)str_buf, str_buf_len);
            }

         } while(TRUE); // (retw == ERROR_SUCCESS);

// ---------------------------------- enum subkeys
         key_ix = 0;
         do
         {
            name_len = 200;
            class_len = 200;
            retw = RegEnumKeyEx(hKey, key_ix++, (char *)key_name, &name_len, NULL, (char *)class_name, &class_len, NULL);
            if(retw == ERROR_NO_MORE_ITEMS) break;
            else if(retw != ERROR_SUCCESS)
            {
               sprintf((char *)str_buf, "------------ nesinumeruoja retw = %d %d\n", retw, key_ix - 1); str_buf_len = strlen(str_buf);
               if(bEncode && SUCCEEDED(retc)) retc = EncodeLogBuf(str_buf, str_buf_len);
               pOutFstream->write((const char *)str_buf, str_buf_len);
            }
            else
            {
//             *pOutFstream << lpszKeyName << "\\" key_name << " ["  << class_name <<  "] ";

               strcpy(sub_key_name, lpszKeyName);
               strcat(sub_key_name, "\\");
               strcat(sub_key_name, key_name);

               /* retc = */ KpRegExportBranch(pOutFstream, hQueryKey, sub_key_name, bEncode);
            }

         } while(TRUE); // (retw == ERROR_SUCCESS);
      }

      if(hKey) RegCloseKey(hKey);
   }

   KP_DELETEA(str_buf);

return(retc);
}


// ============================================================================= Windows I/O
// -------------------------------------------------
int iKpt2WinLocale[KPT_Ctnum] =
{
  0,     //                                                             //  0
  0,     // "IRV version, basic Latin, ASCII",                          //  1   ISO-646
  0,     // "ISO Registration #37, basic Cyrillic, KOI-7-1",            //  2   KOI-7
  0,     // "Extended Latin, based on ASCII",                           //  3   ISO-5426
  0,     // "Extended Cyrillic, based on ASCII",                        //  4   ISO-5427
  0,     // "Greek, based on ASCII",                                    //  5   ISO-5428
  0,     // "African coded character set, based on ASCII",              //  6   ISO-6438
  0,     //                                                             //  7
  0,     //                                                             //  8
  0,     //                                                             //  9
  0,     // "TeX TEV output character set",                             // 10
  0,     // "TeX TEV Cyrillic character set",                           // 11
  0,     // "TeX TEV Cyrillic character set for hyphenation patterns",  // 12
  0,     //                                                             // 13
  0,     //                                                             // 14
  0,     //                                                             // 15
  0,     //                                                             // 16
  0,     //                                                             // 17
  0,     //                                                             // 18
  0,     //                                                             // 19
  0,     //                                                             // 20
  0,     // "German, based on ASCII",                                   // 21
  0,     // "French, based on ASCII",                                   // 22
  0,     // "Norvegian/danish, based on ASCII",                         // 23
  0,     // "Swedish/finnish, based on ASCII",                          // 24
  0,     //                                                             // 25
  0,     //                                                             // 26
  0,     //                                                             // 27
  0,     //                                                             // 28
  0,     //                                                             // 29
  0,     //                                                             // 30
  0,     // "DOS Multilingual, Latin I, PC-8",                          // 31  IBM-437
  0,     // "DOS Central European, Slavic, Latin II",                   // 32  IBM-852
  0,     // "DOS Western, Multilingual, Latin I+",                      // 33  IBM-850
  0,     // "DOS Canadian-French",                                      // 34  IBM-863
  0,     //                                                             // 35
  0,     //                                                             // 36
  0,     //                                                             // 37
  0,     //                                                             // 38
  0,     //                                                             // 39
  0,     //                                                             // 40
  0,     // "DOS Lithuanian standard, based on IBM-437",                // 41  IBM-774
  0,     // "DOS Lithuanian standard, based on IBM-855 Cyrillic",       // 42  IBM-772
  0,     // "DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic",       // 43  IBM-773
  0,     // "Baltic, Fotonija, RST 1095-89",                            // 44  IBM-770
  0,     // "Baltic, old variant of Baltic-RIM",                        // 45  ISO-8859-4
  0,     // "DOS Lithuanian, IBM-Kbl, based on IBM-437",                // 46  IBM-771
  0,     // "DOS Cyrillic only, without Latin",                         // 47  IBM-855
  0,     // "DOS Cyrillic",                                             // 48  IBM-855
  0,     // "DOS Lithuanian with Polish letters (TEV), IBM-Kbl, based on IBM-855 Cyrillic",    // 49  IBM-773
  0,     // "DOS Lithuanian accented, based on IBM-Kbl",                // 50
  0,     // "DOS Cyrillic",                                             // 51  KOI8-R
  0,     // "DOS Cyrillic, ISO-K, code set of russian made PC",         // 52  ISO-IR-111
  0,     // "DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic TEX TEV",  // 53  IBM-773(-)
  0,     // "DOS Lithuanian, IBM-Kbl, based on IBM-437 TEX TEV",        // 54  IBM-771(-)
  0,     //                                                             // 55
  0,     //                                                             // 56
  0,     //                                                             // 57
  0,     //                                                             // 58
  0,     //                                                             // 59
  0,     //                                                             // 60
  0,     //                                                             // 61  DKOI, EBCDIC
  0,     //                                                             // 62
  0,     //                                                             // 63
  0,     //                                                             // 64
  0,     //                                                             // 65
  0,     //                                                             // 66
  0,     //                                                             // 67
  0,     //                                                             // 68
  0,     //                                                             // 69
  0,     //                                                             // 70
  0x427, // "Baltic RIM, LST 1282-93, ISO-8859-13",                     // 71  Windows-1257
  0,     // "Windows SC",                                               // 72
  0x419, // "Windows Cyrillic",                                         // 73  Windows-1251
  0x409, // "Windows-1252, ANSI, ECMA Latin 1",                         // 74  ISO-Latin-1, Windows-1252
  0,     // "Windows Symbol Font for TEX formula fields",               // 75
  0x427, // "Baltic-RIM, some RTF accented characters added",           // 76  (Windows-1257)
  0x419, // "Cyrillic without latin, with spec. chars (for TEX tags)",  // 77  (Windows-1251)
  0,     // "Greek",                                                    // 78  Windows-1253
  0,     // "CE, ANSI-2, Central European",                             // 79  Windows-1250
  0x427, // "Windows lithuanian accented charset",                      // 80 // "TimesLT Accented" (Windows-1257)
  0,     // "Windows Phonetic basic charset",                           // 81 // "PhoneticTM"
  0,     // "Windows Phonetic full (Universal) charset",                // 82 // "PhoneticTMUniv"
  0,     // "Windows Symbol Font",                                      // 83
  0,     // "Windows Verdana Font 8-bit encoding",                      // 84
  0,     // "Windows Symbol Font with ASCII lowerpart for RTF output",  // 85
  0,     // "Windows Wingdings",                                        // 86
  0,     // "LED Phonetic charset",                                     // 87
  0x427, // "Baltic-RIM, OTEL",                                         // 88  (Windows-1257)
  0,     //                                                             // 89
  0,     //                                                             // 90
  0,     // "Norsk Data lithuanian",                                    // 91
  0,     // "Lithuanian ASCII based standart",                          // 92
  0,     // "Norsk Data polish",                                        // 93
  0,     //                                                             // 94
  0,     //                                                             // 95
  0,     //                                                             // 96
  0,     //                                                             // 97
  0,     //                                                             // 98
  0,     // "Transparent code table for i/o of 8-bit codes without decoding", // 99
};


#if FALSE
// ------------------------------------------------------------------
int getDevID(HANDLE h_dev)
{
STORAGE_DEVICE_NUMBER deviceNumber;
DWORD block;
int id_dev = 0;

	memset((void*) &deviceNumber, 0, sizeof(deviceNumber));
	if(DeviceIoControl(h_dev, IOCTL_STORAGE_GET_DEVICE_NUMBER, 0, 0, &deviceNumber, sizeof(STORAGE_DEVICE_NUMBER), &block, 0) == 0)
	   xlogf(7, L"KP DeviceIoControl(h_dev, ...) == 0");
	else
      id_dev = (deviceNumber.DeviceType << 8) | deviceNumber.DeviceNumber;

return(id_dev);
}
#endif


#if FALSE
// ------------------------------------------------------------------
#define SP_DEVICE_INTERFACE_DETAIL_DATA_BUF_LEN 1024

// ------------------------------------------------------------------
// darbinio katalogo suradimas device interface formatu "\\Device\\HarddiskVolume2\\Program Files (x86)\\KTU\\Kalbos akustika glaustai"
// char lpszDirBuf[MAX_PATH + 1] – gr??inamo kelio buferis
void GetCurDevPath(char *lpszDirBuf)
{
static char dir_buf[MAX_PATH + 1];
static char path[MAX_PATH + 1];
HANDLE h_dev = INVALID_HANDLE_VALUE;
int id_dev = 0;
HANDLE h_info = INVALID_HANDLE_VALUE;
SP_DEVICE_INTERFACE_DATA interfaceData;
static char buffer[SP_DEVICE_INTERFACE_DETAIL_DATA_BUF_LEN+1];
SP_DEVICE_INTERFACE_DETAIL_DATA *interfaceDetailData = (SP_DEVICE_INTERFACE_DETAIL_DATA*) buffer;
DWORD block;
static char str_buf[MAX_PATH + 200];
static TCHAR tstr_buf[MAX_PATH + 200];

   if(lpszDirBuf == NULL) xlogf(7, L"KP lpszDirBuf == NULL");
   else
   {
      lpszDirBuf[0] = 0;

      if(GetCurrentDirectoryA(MAX_PATH, dir_buf) == 0) xlogf(7, L"KP GetCurrentDirectoryA() klaida");
      else
      {
         strcpy(lpszDirBuf, dir_buf);

         if(strlen(dir_buf) >= 3)
         {
// -----------------------
// atpjaunam disko vard? ? dir_buf ("C:"), dir_buf + 3 lieka aktyvus kelias be pradinio sle?o
            dir_buf[2] = 0;

            sprintf(path, "\\\\.\\%s", dir_buf);
            h_dev = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
            if(h_dev == INVALID_HANDLE_VALUE)
            {
               sprintf(str_buf, "KP CreateFile(\"%s\")", path);
               ctstrcpy(tstr_buf, str_buf);
               xlogf(7, tstr_buf);
            }
            else
            {
               id_dev = getDevID(h_dev);
               if(id_dev == 0) xlogf(7, L"KP getDevID()");

               CloseHandle(h_dev);
            }

// ----------------------- ie?kom device, kopijuojam ? path
            path[0] = 0;
            if(id_dev != 0)
            {
            	h_info = SetupDiGetClassDevs(&GUID_DEVINTERFACE_DISK, 0, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
               if(h_info == INVALID_HANDLE_VALUE) xlogf(7, L"KP SetupDiGetClassDevs()");
               else
               {
                  for(int nn = 0; ; nn++)
                  {
                     interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
                     if(SetupDiEnumDeviceInterfaces(h_info, 0, &GUID_DEVINTERFACE_DISK, nn, &interfaceData) == 0)
                        xlogf(7, L"KP SetupDiEnumDeviceInterfaces()");
                     else
                     {
                        interfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
                        if(SetupDiGetDeviceInterfaceDetail(h_info, &interfaceData, interfaceDetailData,
                           SP_DEVICE_INTERFACE_DETAIL_DATA_BUF_LEN, &block, 0) == 0)
                              xlogf(7, L"KP SetupDiGetDeviceInterfaceDetail()");
                        else
                        {
                           h_dev = CreateFile(interfaceDetailData->DevicePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
                           if(h_dev == INVALID_HANDLE_VALUE) xlogf(7, L"KP CreateFile(interfaceDetailData->DevicePath)");
                           else
                           {
                              if(getDevID(h_dev) == id_dev)
                              {
                                 if(interfaceDetailData->DevicePath == NULL) xlogf(7, L"KP interfaceDetailData->DevicePath == NULL");
                                 else
                                 {
                                    if(wcslen(interfaceDetailData->DevicePath) > MAX_PATH)
                                       xlogf(7, L"KP wcslen(interfaceDetailData->DevicePath) > MAX_PATH");
                                    else
                                       tcstrcpy(path, interfaceDetailData->DevicePath);
                                 }
                                 break;
                              }

                           } // else // if(h_dev == INVALID_HANDLE_VALUE)

                        } // else // if(SetupDiGetDeviceInterfaceDetail(h_info, ...) == 0)

                     } // else // if(SetupDiEnumDeviceInterfaces(h_info, ...) == 0)

                  } // for(int nn = 0; ; nn++)

                  SetupDiDestroyDeviceInfoList(h_info);

                  if(h_dev != INVALID_HANDLE_VALUE) CloseHandle(h_dev);
                  h_dev = INVALID_HANDLE_VALUE;

               } // else // if(h_info == INVALID_HANDLE_VALUE)

            } // if(id_dev != 0)

// -----------------------
            if(strlen(path) + 1 + strlen(dir_buf + 3) > MAX_PATH)
               xlogf(7, L"KP strlen(path) + strlen(dir_buf + 3) > MAX_PATH");
            else
            {
               strcpy(lpszDirBuf, path);
               strcat(lpszDirBuf, "\\");
               strcat(lpszDirBuf, dir_buf + 3);
            }

         } // if(strlen(dir_buf) >= 3)

      } // else // if(GetCurrentDirectoryA(MAX_PATH, lpszDirBuf) == 0)

   } // else // if(lpszDirBuf == NULL)

}
#endif
