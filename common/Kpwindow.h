//----------------------------------
// kpwindows.h
// common Win32 things
//

#ifndef kpwindows_included
#define kpwindows_included

// -------------------------------------
#define KPCONS_OLD_STYLE

// -------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ================================================== environment
typedef enum
{
   WinUnkn,   //  0

// Win10,     //  ?  // Windows 1.0

   Win20,     //  1  // Windows 2.0

   Win31c,    //  2  // common Windows 3.1x
   Win31,     //  3  // Win32s on Windows 3.1
   Win311,    //  4  // Windows 3.11 for Workgroups (with Win32s ?)

   Win95c,    //  5  // common Windows 95
   Win95,     //  6  // Windows 95
   Win95OSR2, //  7  // Windows 95 OSR-2

   Win98c,    //  8  // common Windows 98
   Win98,     //  9  // Windows 98
   Win98SE,   // 10  // Windows 98 Second Edition
   WinCE,     // 11  // Windows CE
   WinMe,     // 12  // Windows ME

   WinNT,     // 13  // common Windows NT // skirtukas tarp WinNT ir Win98 platformø

   WinNT35c,  // 14  // common Windows NT 3.5x
   WinNT351,  // 15  // Windows NT 3.51

   WinNT40c,  // 16  // common Windows NT 4.0
   WinNT40,   // 17  // Windows NT Workstation 4.0
   WinNT40s,  // 18  // Windows NT Server 4.0

   Win2000c,  // 19  // common Windows 2000
   Win2000,   // 20  // Windows 2000 Professional // Windows 2000
   Win2000s,  // 21  // Windows 2000 Server  // atsirado nuo 2004.10.01

   WinXPc,    // 22, // =  22, // common Windows XP   // iki 2008.10.22 galvojau, kad visø tolesniø kodai vienu maþesni, nors jau buvo tokie kaip dabar
                                                      // reiðkia, kaþkada jie ir buvo vienu maþesni, tik po to neteisingai pridëjau WinXPc
   WinXP,     // 23  // Windows XP           // buvo 20 iki 2004.10.01
   Win2003s,  // 24  // Windows Server 2003  // buvo 21 iki 2004.10.01
   WinXpStart,// 25  // Windows XP Starter Edition
   WinXpHome, // 26  // Windows XP Home Edition
   WinXpPro,  // 27  // Windows XP Professional
   WinXpMedia,// 28  // Windows XP Media Center Edition
   WinXpTablet,//29  // Windows XP Tablet PC Edition // Windows CE analogas?
   WinXP64,   // 30  // Windows XP Professional x64 Edition
   Win2003sR2,// 31  // Windows Server 2003 R2

   WinVistaC, // 32  // common Windows Vista

   WinVista,  // 33  // Windows Vista
   WinVistaH, // 34  // Windows Vista Home Basic
   WinVistaHP,// 35  // Windows Vista Home Premium
   WinVistaB, // 36  // Windows Vista Business
   WinVistaE, // 37  // Windows Vista Enterprise
   WinVistaU, // 38  // Windows Vista Ultimate
   Win2008s,  // 39  // Windows Server 2008 // Windows Server Longhorn

   Win7,      // 40  // Windows 7

   Win8,      // 41  // Windows 8
   Win81,     // 42  // Windows 8.1

   Win10,     // 43  // Windows 8

   WinNtFuture, // 44 // buvo 42 iki 2015-08-07 // buvo 200 iki 2009.01.27

   WinNumOfCurrentWinVersions,

// WinNtFuture = 200, // buvo 39 iki 2007.11.06  // common Windows NT based future versions

// NumOfWinVersions0,

} MSWin32Version; // windows versions

#define NumOfWinVersions0 WinNumOfCurrentWinVersions
#define NumOfWinVersions11 WinNumOfCurrentWinVersions // NumOfWinVersions0 // masyvø apibrëþimams

#define SM_TABLETPC     86
#define SM_MEDIACENTER  87
#define SM_STARTER      88
#define SM_SERVERR2     89

#if (Compiler == Msvc60)

#define VER_NT_WORKSTATION 1
#define VER_NT_DOMAIN_CONTROLLER 2
#define VER_NT_SERVER 3

typedef struct
{
        DWORD dwOSVersionInfoSize;
        DWORD dwMajorVersion;
        DWORD dwMinorVersion;
        DWORD dwBuildNumber;
        DWORD dwPlatformId;
        CHAR szCSDVersion[128];
        WORD wServicePackMajor;
        WORD wServicePackMinor;
        WORD wSuiteMask;
        BYTE wProductType;
        BYTE wReserved;
} KP_OSVERSIONINFOEX;
#else

#define KP_OSVERSIONINFOEX OSVERSIONINFOEX

#endif

typedef struct 
{
  DWORD dwOSVersionInfoSize;
  DWORD dwMajorVersion;
  DWORD dwMinorVersion;
  DWORD dwBuildNumber;
  DWORD dwPlatformId;
  WCHAR szCSDVersion[128];
  WORD wServicePackMajor;
  WORD wServicePackMinor;
  WORD wSuiteMask;
  BYTE wProductType;
  BYTE wReserved;
} KP_RTL_OSVERSIONINFOEXW;
#if (CompilerGr != Mingw)
#define RTL_OSVERSIONINFOEXW KP_RTL_OSVERSIONINFOEXW
#else
#if MingwVer < 482
#define RTL_OSVERSIONINFOEXW KP_RTL_OSVERSIONINFOEXW
#endif
#endif

extern const unsigned char *lpszaWindowsVerNames[NumOfWinVersions0];

extern HRESULT KpGetSystemVersion(MSWin32Version *piWin32Vers, int *piWinSP);
// in case of KP_E_UNKNOWN_SYSTEM does not output any error message

extern MSWin32Version iWindowsVersion;
// #define iWindowsVersionCut ((iWindowsVersion < WinNumOfCurrentWinVersions)?iWindowsVersion:WinXP)
extern MSWin32Version iWindowsVersionCut; // versija nupjauta iki didþiausios þinomos (< WinNumOfCurrentWinVersions), kad nepersipildytø masyvø indeksai

extern int iWindowsSP;
extern KP_OSVERSIONINFOEX Osvi;

// ---------------------------------
// extern BOOL IsUserAnAdmin(VOID); // turëtø bûti shlobj.h, tik Vistoj?

// extern BOOL IsUserAdmin(VOID);
// extern "C" BOOL IsUserAdmin(VOID);
// extern BOOL _IsUserAdmin@0O(VOID);
// extern BOOL __stdcall IsUserAdmin(VOID);
// BOOL WINAPI IsUserAdmin(void);
#if (CompilerGr!=Watcom) || (__WATCOMC__ < 1202)
extern "C" BOOL WINAPI IsUserAdmin(void);
#else
SHSTDAPI_(BOOL) IsUserAnAdmin(void); // nuwrapinam standartinæ shell32.lib funkcijà – jà iðkvieèia Watcom runtime, bet Win2k jos neturi
#define IsUserAdmin IsUserAnAdmin
#endif

// extern BOOL WINAPI CheckTokenMembership(
// __stdcall WINUSERAPI BOOL WINAPI CheckTokenMembership(
extern "C" BOOL WINAPI CheckTokenMembership(
  /* __in_opt */  HANDLE, // TokenHandle,
  /* __in */      PSID, // SidToCheck,
  /* __out */     PBOOL // IsMember
);

extern bool bAdminFl;

// ---------------------------------
extern bool bServiceFl; // lokaliai apibrezta WinNT serviso veliavele


// ----------------------------- parent window for all application subwindows
// must be defined in main application
#if FALSE
#  if FALSE // Envir==MSWin32Mfc
extern CWnd* MainWindow; // former pMainWindow
#  else
extern HWND MainWindow;
#  endif
#endif

extern HINSTANCE hKpInstance /* =NULL */;
// must be initialized in main application or during KpConsole/KpStap initialization
// former hKpConsoleInstance

extern DWORD iKpMainThread;

// ----------------------------
extern HMODULE hUnicowsLib;

// extern HRESULT LoadUnicowsProc(void);


// ----------------------------
extern HRESULT KpInitWindows(HINSTANCE hKpInst);

extern HRESULT KpFinitWindows(void);

// ==================================================
// wingdi.h:
/* WINGDIAPI */ COLORREF WINAPI GetDCBrushColor(HDC);


//---------------------------- get file name of program being currently executed
//---------------------------- szNameBuf[KP_MAX_FNAME_LEN+1]
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
extern HRESULT GetExeFileName(unsigned char *szNameBuf);
#endif


// =============================================== common functions
#define KPW_MSG_NUMOFCOLUMNS 70 // 60
#define KPW_MSG_BREAK_THRESHOLD 12 // 10 // 15
// enum KpMsgTypes // iðkeltas á kperrno.h

//---------------------------- dialog control styles
typedef enum
{
   KPW_CONTROL_STYLE_NORMAL,
   KPW_CONTROL_STYLE_HEADING_3,
   KPW_CONTROL_STYLE_MONOSPACE, // former KPW_CONTROL_STYLE_COURIER,
   KPW_CONTROL_STYLE_BOLD,
   KPW_CONTROL_STYLE_CAPTION,

   KPW_NUM_OF_CONTROL_STYLES_0
} KpControlStyles; // former ControlStyles

#define KPW_NUM_OF_CONTROL_STYLES_2 KPW_NUM_OF_CONTROL_STYLES_0

//---------------------------- text alignments
// enum KpAlignments // iðkeltas á kperrno.h

// -------------------------
typedef struct
{
   KpMsgTypes m_iMsgTp; // former iMsgTp // message type
   KpAlignments m_iAlign;
   const unsigned char *m_lpszMsgTxt;
   HICON m_hIcon;
} KpMsgData;


extern HRESULT GetButText(KpMsgTypes iMsgTp, const unsigned char **plpszMsgOk, const unsigned char **plpszMsgCancel, const unsigned char **plpszMsgHelp);

extern HRESULT KpMsgOut(const unsigned char *lpszOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut = 0, KpAlignments iAlign = KPW_ALIGN_CENTER, HWND *phDialogWnd = NULL);
extern HRESULT KpMsgOut(const unsigned char *lpszOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, HWND *phDialogWnd);
// extern HRESULT KpMsgOut(const char *lpszOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut = 0, KpAlignments iAlign = KPW_ALIGN_CENTER); // iðkeltas á kperrno.h
// iTimeOut msec
extern HRESULT KpMsgOut(const unsigned char *lpszOutStr);
extern long KpMsgOut(const char *lpszOutStr, LPCTSTR lpszIconID, int iMsgType, int iTimeOut = 0, KpAlignments iAlign = KPW_ALIGN_CENTER);
extern HRESULT KpMsgOut(const char *lpszOutStr);
extern HRESULT KpMsgOut(KpString sOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut = 0, KpAlignments iAlign = KPW_ALIGN_CENTER);
extern HRESULT KpMsgOut(KpString sOutStr);
// extern HRESULT KpMsgOutStr(std::string sOutStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut = 0, KpAlignments iAlign = KPW_ALIGN_CENTER); // iðkeltas á kperrno.h
extern HRESULT KpMsgOut(const KpChar *iazKpStr, LPCTSTR lpszIconID, KpMsgTypes iMsgType, int iTimeOut = 0, KpAlignments iAlign = KPW_ALIGN_CENTER);
extern HRESULT KpMsgOut(const KpChar *iazKpStr);
         // only returns error codes, does not output any messages
         // lpszIconID - look description of LoadIcon
         // lpszIconID could be also of following predefined values:
         //    IDI_APPLICATION Default application icon.
         //    IDI_ASTERISK Same as IDI_INFORMATION.
         //    IDI_ERROR Hand-shaped icon.
         //    IDI_EXCLAMATION Same as IDI_WARNING.
         //    IDI_HAND Same as IDI_ERROR.
         //    IDI_INFORMATION Asterisk icon.
         //    IDI_QUESTION Question mark icon.
         //    IDI_WARNING Exclamation point icon.
         //    IDI_WINLOGO Windows logo icon. Windows XP: Default application icon.
         // iTimeOut - po kiek milisekundziu pranesima uzdaryti; 0 - laukti kol paspaus
extern BOOL CALLBACK KpMsgDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern HRESULT WrapMsg(const unsigned char *lpszMsgStr, unsigned char **plpszMsgPtr, int *piMsgLines, int iMsgColumns);
extern HRESULT CalcMsgPars(const unsigned char *lpszMsgStr, unsigned char **plpszMsgPtr, int *piMsgLines,
   int *piMsgX, int *piMsgY, int *piMsgDx, int *piMsgDy,
   int *piWndX, int *piWndY, int *piWndDx, int *piWndDy,
   int *piButX, int *piButY, int *piBut1X, int *piBut1Y, int *piBut2X, int *piBut2Y,
   KpAlignments iAlign);
    // *plpszMsgPtr must be deleted after use

#ifdef Debug
#define KpMsgOut_0(str) KpMsgOut(str, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#define KpMsgOut_1(fmt, par) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOut_2(fmt, par_1, par_2) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOut_3(fmt, par_1, par_2, par_3) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOut_4(fmt, par_1, par_2, par_3, par_4) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3, par_4); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOut_5(fmt, par_1, par_2, par_3, par_4, par_5) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3, par_4, par_5); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOut_6(fmt, par_1, par_2, par_3, par_4, par_5, par_6) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3, par_4, par_5, par_6); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#else
#define KpMsgOut_0(str)
#define KpMsgOut_1(fmt, par)
#define KpMsgOut_2(fmt, par_1, par_2)
#define KpMsgOut_3(fmt, par_1, par_2, par_3)
#define KpMsgOut_4(fmt, par_1, par_2, par_3, par_4)
#define KpMsgOut_5(fmt, par_1, par_2, par_3, par_4, par_5)
#define KpMsgOut_6(fmt, par_1, par_2, par_3, par_4, par_5, par_6)
#endif

#define KpMsgOutF(...) {static char str_buf[2000]; sprintf(str_buf, (const char *)__VA_ARGS__); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOutF_0(str) KpMsgOut(str, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#define KpMsgOutF_1(fmt, par) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOutF_2(fmt, par_1, par_2) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOutF_3(fmt, par_1, par_2, par_3) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOutF_4(fmt, par_1, par_2, par_3, par_4) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3, par_4); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOutF_5(fmt, par_1, par_2, par_3, par_4, par_5) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3, par_4, par_5); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}
#define KpMsgOutF_6(fmt, par_1, par_2, par_3, par_4, par_5, par_6) {static char str_buf[2000]; sprintf(str_buf, (const char *)fmt, par_1, par_2, par_3, par_4, par_5, par_6); KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);}

// -----------------------------------------
#define KP_INPUT_STR_WND_VERT_MARGIN  (KPW_WND_MARGIN*2)
#define KP_INPUT_STR_WND_HOR_MARGIN  (KPW_WND_MARGIN*6)
#define KP_INPUT_STR_CTRL_MARGIN KPW_WND_MARGIN

#define KP_INPUT_STR_PROMPT_X KP_INPUT_STR_WND_HOR_MARGIN
#define KP_INPUT_STR_PROMPT_Y KP_INPUT_STR_WND_VERT_MARGIN

#define KP_INPUT_STR_EDIT_X (KP_INPUT_STR_WND_HOR_MARGIN + KP_INPUT_STR_WND_HOR_MARGIN) // + KP_INPUT_STR_CTRL_MARGIN)
#define KP_INPUT_STR_EDIT_Y (KP_INPUT_STR_WND_VERT_MARGIN + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + KP_INPUT_STR_CTRL_MARGIN)

#define KP_INPUT_STR_BUT_Y (KP_INPUT_STR_WND_VERT_MARGIN + (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + KP_INPUT_STR_CTRL_MARGIN) * 2)
#define KP_INPUT_STR_OK_BUT_Y KP_INPUT_STR_BUT_Y
#define KP_INPUT_STR_CANCEL_BUT_Y KP_INPUT_STR_BUT_Y

class KpInputStrData
{
public:
   const unsigned char *m_lpszPrompt;
   const unsigned char *m_lpszInitVal;
   HWND m_hwEditCtrl;
   int m_iEditWdt;
   DWORD m_dwExStyle;
   DWORD m_dwStyle;
   int m_iWndDx;
   KpMsgTypes m_iMsgTp; // former iMsgTp // message type

   KpInputStrData(const unsigned char *lpszPrompt, const unsigned char *lpszInitVal, int iEditWdt, DWORD dwExStyle, DWORD dwStyle, int iWndDx, KpMsgTypes iMsgTp);
};

// ---------------------------------- KpInputStr() vieno lauko ávedimo dialogo langelis
extern HRESULT KpInputStr(const unsigned char *lpszPrompt, unsigned char *lpszEditBuf, int iBufLen, int iEditWdt, DWORD dwExStyle, DWORD dwStyle, KpMsgTypes iMsgTp = KP_MB_GERAI_ATSAUKTI);


// --------------------------------------------------
// Win98 C:\My Documents\Adobe\Acrobat\JavaScripts
#define MY_DOCS_PATH_98_2 "My Documents\\" // former JS_PATH_98_2
// WinNT C:\WINNT\Profiles\printerl.000\Personal\Adobe\Acrobat\JavaScripts
// #define MY_DOCS_PATH_NT_1 "Profiles\\" // former JS_PATH_NT_1
#define MY_DOCS_PATH_NT_2 "Personal\\" // former JS_PATH_NT_2
// Win2k I:\Documents and Settings\mindaugas\My Documents\Adobe\Acrobat\JavaScripts
// #define MY_DOCS_PATH_2K_1 "Documents and Settings\\" // former JS_PATH_2K_1
#define MY_DOCS_PATH_2K_2 "My Documents\\" // former JS_PATH_2K_2
#define AP_DATA_PATH_2K_2 "Application Data\\"

#define  KP_CUR_DIR ((const unsigned char *)".")

typedef enum
{
   KP_My_Documents,
   KP_Application_Data,
   KP_LocalDir,
   KP_Program_Files,
   KP_Common_Files,
   KP_Temp_Dir,
   KP_Desktop,

} LocalPaths;

extern HRESULT GetLocalPath(unsigned char *lpszFNamBuf, LocalPaths iPathID, bool bAppendSlash = True); // former GetMyDocumentsPath
                     // lpszFNamBuf[KP_MAX_FNAME_LEN + 1]

extern HRESULT TestAdmin(bool *pbAdminFl);


// -----------------------------------------------
// additional clipboard formats
#define KP_CF_RTF_NAME  ("Rich Text Format")
#define KP_CF_HTML_NAME ("HTML Format")

// laukai u_registruotø formatø kodams saugoti
extern UINT KpCfRtfClFormat; // KP_CF_RTF_NAME
extern UINT KpCfHtmlClFormat; // KP_CF_HTML_NAME

extern HRESULT SetClipboardText(HWND hWndNewOwner, const unsigned char *lpszClipData, int iCtbl);
extern HRESULT KpSetClipboardData(HWND hWndNewOwner, UINT uFormat, const unsigned char *lpClipData, int iBufSize, bool bClearBeforeSetting = True);
extern HRESULT GetClipboardText(HWND hWndNewOwner, unsigned char *lpszClipData, int iBufSize, bool bTestErrors);
extern HRESULT KpGetClipboardData(HWND hWndNewOwner, UINT uFormat, unsigned char *lpszClipData, int iBufSize, bool bTestErrors);

extern HRESULT KpClearClipboard(HWND hWndNewOwner, const unsigned char *lpszWndName = NULL); // trinti tik kai aktyvus lpszWndName
                                                                                             // jei lpszWndName == NULL, trinti visada

// ================================================== windows messages
#define WM_ACPT WM_APP+1
#define WM_REC WM_APP+2

// #define KPW_FIRST_USER_MSG WM_USER
#define KPW_FIRST_USER_MSG 10000

#define WM_KP_CREATE (KPW_FIRST_USER_MSG+1)
// additional message sent by window creation routine to main thread
// used also for KPLISTBOX'es to create main control subcontrols,
//    simply WM_CREATE does not fit - at that moment parent control
//    being created is not yet entered to KpWndList

#define KP_LB_GETTEXT         (KPW_FIRST_USER_MSG+2)  // LB_GETTEXT pakaitalas KP_LISTBOX list box'ams

#define KP_LB_SETSTRINGLIST   (KPW_FIRST_USER_MSG+3)  // message for KpListBox'es
// sets pointer KpWnd.m_pEntries - current listbox rows texts list/tree
// pointed object should be kept undeleted until LB_RESETCONTENT or
//    listbox destruction
// copies list/tree text values to KpWnd.m_plpszListEntries
// wParam - ignored
// (KpTreeEntry *)lParam - address of list/tree object

#define WM_KP_REMOTE_CALL (KPW_FIRST_USER_MSG+10)
// message sent by main Win32 application to Hp11 application
// request to execute Hp11 function
// only one remote call at a time
// wParam - ignored
// (KpRcPars *)lParam - address of parameter block
#define WM_KP_REMOTE_CALL_DONE (KPW_FIRST_USER_MSG+11)
// answer to WM_KP_REMOTE_CALL
// wParam - ignored
// (HRESULT)lParam - completion code

#define WM_KP_THREAD_STARTED (KPW_FIRST_USER_MSG+12) // child thread start confirmation


#if TRUE // #if FALSE
// pranesimai thread'ui Lzdsht.LzdShSearch::m_lThreadId,
// ivykdo theSearchThread.m_pCurEntry->SetTagHeadings(LZDSH_NUM_OF_PAR_STYLES, theDialog.m_hDialogWindow);
#define WM_LZDSH_SET_TAG_HEADINGS_FULL (KPW_FIRST_USER_MSG+20) // lParam - siunciancio threado ID
#define WM_LZDSH_FULL_HEADINGS_SET (KPW_FIRST_USER_MSG+21)  // answer to WM_LZDSH_SET_TAG_HEADINGS_FULL
#define WM_LZDSH_SET_TAG_HEADINGS_CURRENT (KPW_FIRST_USER_MSG+22) // lParam - siunciancio threado ID
#define WM_LZDSH_CURRENT_HEADINGS_SET (KPW_FIRST_USER_MSG+23) // ansver to WM_LZDSH_SET_TAG_HEADINGS_CURRENT
#define WM_LZDSH_REFRESH_DISPLAY (KPW_FIRST_USER_MSG+24) // refresh theSearchThread.m_ResRichEdit
#endif


// galima naudoti ir RegisterWindowMessage()

// timers

#define KPW_CONSOLE_REFRESH_TIMER   (KPW_FIRST_USER_MSG+120)
#define KPW_CONSOLE_REFRESH_TIMEOUT 100
extern VOID CALLBACK KpConsoleRefreshTimer(HWND hwndDlg, UINT, UINT, DWORD);

#define KP_SLEEP_TIMER              (KPW_FIRST_USER_MSG+121)

#define KP_POLL_TIMER               (KPW_FIRST_USER_MSG+122)
#define KP_POLL_TIMEOUT             500 // 200

#define KP_REDRAW_TIMER             (KPW_FIRST_USER_MSG+123)
#define KP_REDRAW_TIMEOUT           100 // 200

#define KP_TIMEOUT_TIMER            (KPW_FIRST_USER_MSG+124)
#define KP_TIMEOUT_TIMEOUT          30000 // 15000 // 100000 // 5000

extern volatile DWORD lKphp11ThreadId; // KpHp11 thread ID, if running

extern HWND hMouseOverWnd;
extern HWND hToolTip;
extern int ToolTipTimer;
extern int ToolTipKillTimer;
#define KPW_TOOLTIP_TIMER           (KPW_FIRST_USER_MSG+125)
#define KPW_TOOLTIP_KILL_TIMER      (KPW_FIRST_USER_MSG+126)
#define KPW_TOOLTIP_TIMEOUT 1000
#define KPW_TOOLTIP_KILL_TIMEOUT 5000
#define KPW_TOOLTIP_X (-20) // 20
#define KPW_TOOLTIP_Y (-25) // 20
extern HRESULT ManageToolTipTimer(void);


#define DYMSH_PLAY_TIMER            (KPW_FIRST_USER_MSG+130)
#define DYMSH_BACK_PLAY_TIMER       (KPW_FIRST_USER_MSG+131)
#define DYMSH_FAST_FORWARD_TIMER    (KPW_FIRST_USER_MSG+132)
#define DYMSH_FAST_BACKWARD_TIMER   (KPW_FIRST_USER_MSG+133)

#define KPST_LIC_MANAG_TIMER        (KPW_FIRST_USER_MSG+134)
#define KPST_PROC_CMD_TIMER         (KPW_FIRST_USER_MSG+135)
#define KPST_CHK_FLASH_TIMER        (KPW_FIRST_USER_MSG+136)

// control window message wrapper, implemented for "KpRichEdit" and "KpRichEditUni" controls only
#define KP_WM_GETTEXT               (KPW_FIRST_USER_MSG+137)   // WM_GETTEXT wrapperis
#define KP_EM_GETSELTEXT            (KPW_FIRST_USER_MSG+138)   // EM_GETSELTEXT wrapperis
#define KP_EM_GETTEXTEX             (KPW_FIRST_USER_MSG+139)   // EM_GETTEXTEX wrapperis
#define KP_EM_STREAMOUT             (KPW_FIRST_USER_MSG+140)   // EM_STREAMOUT wrapperis
#define KP_EM_SETOLECALLBACK        (KPW_FIRST_USER_MSG+141)   // EM_SETOLECALLBACK wrapperis
#define KP_EM_EXGETSEL              (KPW_FIRST_USER_MSG+142)   // EM_EXGETSEL wrapperis

#define KPST_PROLOG_TIMER           (KPW_FIRST_USER_MSG+143)

#define LZDSH_REACT_TIMER           (KPW_FIRST_USER_MSG+144)

#define KP_BLOCKED_SOCK_RELEASED    (KPW_FIRST_USER_MSG+145)

#define KPST_SES_CTRL_TIMER         (KPW_FIRST_USER_MSG+146)
#define KPST_WM_BLOCK_SES           (KPW_FIRST_USER_MSG+147)

#define KPST_REST_MINS_TIMER        (KPW_FIRST_USER_MSG+148) // terminuotø licencijø laiko skaièiavimui
// #define KPST_ID_REST_DAYS_EXCEEDED  (KPW_FIRST_USER_MSG+149) // WM_COMMAND praneðimas apie besibaigiantá dienø skaièiø, lParam – likæs dienø sk.

#define EM_GETIMECOMPTEXT  (WM_USER + 242)   // http://www.purearea.net/pb/CodeArchiv/Includes+Macros/Macros/RichEdit_Macro.pbi

// -------------------
#define DYMSH_EJECT                 (KPW_FIRST_USER_MSG+151) // former KPW_FIRST_USER_MSG+1
#define DYMSH_REWIND                (KPW_FIRST_USER_MSG+152) // former KPW_FIRST_USER_MSG+2
#define DYMSH_FAST_BACKWARD         (KPW_FIRST_USER_MSG+153) // former KPW_FIRST_USER_MSG+3
#define DYMSH_BACK_STEP             (KPW_FIRST_USER_MSG+154) // former KPW_FIRST_USER_MSG+4
#define DYMSH_BACK_PLAY             (KPW_FIRST_USER_MSG+155) // former KPW_FIRST_USER_MSG+5
#define DYMSH_STOP                  (KPW_FIRST_USER_MSG+156) // former KPW_FIRST_USER_MSG+6
#define DYMSH_PLAY                  (KPW_FIRST_USER_MSG+157) // former KPW_FIRST_USER_MSG+7
#define DYMSH_STEP                  (KPW_FIRST_USER_MSG+158) // former KPW_FIRST_USER_MSG+8
#define DYMSH_FAST_FORWARD          (KPW_FIRST_USER_MSG+159) // former KPW_FIRST_USER_MSG+9
#define DYMSH_TO_END                (KPW_FIRST_USER_MSG+160) // former KPW_FIRST_USER_MSG+10


// http://groups.google.de/group/microsoft.public.de.german.entwickler.dotnet.csharp/msg/b047066a634c0863
// defined in imm.h
// #define WM_IME_SETCONTEXT  641
// #define WM_IME_NOTIFY      642


// ================================================== window definitions
// extern HRESULT GetWindowPars(HWND hWindow);
extern HRESULT InitWindowPars(void); // iskviecia KpInitWindows()

#define KPW_WND_CAPTION_HGT_INI ((iWindowsVersion>=WinVistaC)?20:((iWindowsVersion>=WinXPc)?26:19)) // former KPW_WND_CAPTION_HGT // ((iWindowsVersion==WinXP)?25:19) // 17   // jei WS_CAPTION
extern int iWndCaptionHgt; // kepures aukstis kartu su meniu, jei yra
// extern int GetCaptionHgt(HWND hWindow);

#define KPW_WND_TOOLBAR_CAPTION_HGT_INI KPW_WND_CAPTION_HGT_INI

#define KPW_WND_MARGIN 5 // parastes lango krastuose ir tarpai tarp nesusijusiø laukø
#define KPW_WND_HOR_MARGIN (4*KPW_WND_MARGIN)
#define KPW_WND_VER_MARGIN (3*KPW_WND_MARGIN)
#define KPW_CTRL_MARGIN 2 // parastes laukelio krastuose, tarpai tarp susijusiø laukø

// standartinio lango krasciukas, neienantis i vidinius lango matmenis
#define KPW_WND_BORDER_WDT_INI ((iWindowsVersion>=WinVistaC)?8:4) // 3 // former KPW_WND_BORDER_WDT, KPW_BORDER_WDT, jei WS_THICKFRAME
extern int iWndBorderWdt;
// extern int GetBorderWdt(HWND hWindow);

// standartinio lango krasciukas, uzlipantis i vidinius lango matmenis
#define KPW_WND_BORDER_COR ((iWindowsVersion >= WinXPc)?1:0)

#define KPW_WND_THIN_BORDER_WDT 1 // 3 // former KPW_BORDER_WDT, jei WS_BORDER
#define KPW_CTRL_BORDER_WDT 2 // sunken control border width

#define KPW_WND_MENU_HGT_INI ((iWindowsVersion >= WinXPc)?20:19) // 24
extern int iWndMenuHgt;


// ============================================= dialog controls
// ----------------------------------- dialog control definitions
#define KPW_BUTTON_WDT 100 //    80 // tekstinio mygtuko ilgis
#define KPW_FORGET_BUTTON_WDT 130
#define KPW_BUTTON_HGT 20  //    30 // tekstinio mygtuko aukstis
#define KPW_INTER_BUTTON_SPACE 1    // atstumas tarp [irankiu juostos] mygtuku
#define KPW_ICON_WDT   32
#define KPW_ICON_BUTTON_WDT   23 // toolbar mygtuko su piktograma plotis ir aukstis

#define KPW_SCROLLBAR_WDT 18        // mazo mygtuko su piktograma plotis ir aukstis
#define KPW_COMBO_BUT_WDT 15 // (KPW_SCROLLBAR_WDT-3) // KPW_SCROLLBAR_WDT //

#define KPW_CHBOX_HGT   15             // check box width and height
#define KPW_CHBOX_VCOR  4              // checkboxo nuleidimas, kad atsidurtø normalaus teksto prompto lygyje

#define KPW_REC_SEL_WDT KPW_BUTTON_HGT  // datasheet record selector
#define KPW_REC_SEL_HGT KPW_BUTTON_HGT

#define KPW_WND_MIN_DX 300          // minimal window width

#define KPW_SLIDER_HGT 10 // KPW_SCROLLBAR_WDT

#define KPW_BMP_WDT 640 // standartiniai ShowBmp() bitmapo matmenys (be sliderio)
#define KPW_BMP_HGT 480

#define KP_SLIDER_TIMEOUT 30

#define KP_PROGRESS_WDT 500
#define KP_PROGRESS_MSG_WDT 120
#define KP_PROGRESS_HGT KPW_SLIDER_HGT // 10 // ðiaip reikëtø ið bitmapo perskaityt

#define KPW_STATIC_INDENT 30

#define KPW_CALC_STATIC_WDT_FACTOR(str, style) (strlen(str)*iaCtrlTextFactors[style]/(((MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))?9:10) /* + iaCtrlTextFactors[style] / 10 + 5 */)
                                    // average pixels count per static/edit control text character

#define KPW_STATIC_ALIGN(style) 0 // (style==KPW_CONTROL_STYLE_HEADING_3?SS_CENTER:0)


extern int iaCtrlHeights[NumOfWinVersions0][KPW_NUM_OF_CONTROL_STYLES_0];
extern int iaBoxHeights[NumOfWinVersions0][KPW_NUM_OF_CONTROL_STYLES_0]; // height of comboboxes (setup authomatically, not controlled by user)
extern int iaCtrlRowHeights[NumOfWinVersions0][KPW_NUM_OF_CONTROL_STYLES_0];
extern int iaCtrlTextFactors[KPW_NUM_OF_CONTROL_STYLES_0]; // teksto pozicijos tasku skaicius, dalinti is 10, max plotis, kad nenukirptø
extern int iaCtrlTextFactorsMean[KPW_NUM_OF_CONTROL_STYLES_0]; // teksto pozicijos tasku skaicius, dalinti is 10, vidutinis plotis
extern int iaCtrlFntWghts[KPW_NUM_OF_CONTROL_STYLES_0];
extern int iaCtrlFntHghts[NumOfWinVersions0][KPW_NUM_OF_CONTROL_STYLES_0];
extern int iaCtrlFntWdtFactors[KPW_NUM_OF_CONTROL_STYLES_0]; // dalinti is 100
extern LPCTSTR iaCtrlTypefaces[KPW_NUM_OF_CONTROL_STYLES_0];
extern DWORD laCtrlCharSets[KPW_NUM_OF_CONTROL_STYLES_0];
extern DWORD laLangCharSets[KpNumOfLangs];


// ------------------------------------------
typedef enum
{
   TYP_KpWnd,        // 0  // simply common window, type unknown
   TYP_KpConsole,    // 1  // main application console - usually static objects, managed by user application
   TYP_Trace,        // 2  // KpConsole used as trace window (may be several trace windows) - usually static objects, managed by user application
   TYP_Static,       // 3  // static controls - for redrawing of control text - managed authomatically
   TYP_MDI_Frame,    // 4  // multiple document interface frames - managed authomatically
   TYP_ListBox,      // 5  // KP_LISTBOX listbox controls - managed authomatically
   TYP_Button,       // 6  // button controls - managed authomatically
// TYP_SubListBox,   //       listbox subcontrol - the list itself without of slider - managed authomatically
   TYP_ListBoxTree,  // 7  // Tree like KP_LISTBOX with m_iWndType LBS_OWNERDRAWFIXED and expanding/collapsing nodes
                     //       high level not detailed listbox, only group nodes are displayed
   TYP_ListBoxTreeInverted,   // 8  // low level detailed TYP_ListBoxTree, only simply non group nodes are displayed
   TYP_KpRichEditUni,   // 9  // KpCreateRichEditUni() created window // former TYP_KpRichEdit
                        //       KpWnd::m_hWndHandle - apkirpimo tevelis
                        //       KpWnd::m_hMDI_Client - tikrasis KpRichEditUni laukas

   TYP_KpBitmap_obs,    // 10 // TYP_KpBitmap, // bitmapo langas su slideriu // iðmeèiau, dabar naudojam TYP_KpDialog, kad lygiagreèiai veiktø ir KpPubDialogProc() lango stumdymai
   TYP_KpBitmapCtrl,    // 11 // bitapo sliderio controlas TYP_KpBitmap lange

   TYP_KpProgressWndw,  // 12  // langas su praneðimu ir slankikliu

   TYP_KpDialog,        // 13 // paprastas dialogo langas parametrø perdavimui á WM_PAINT
                        //       arba KpPubDlg langas bendravimui su lango CALLBACKu (iBshDialogProc, pvz.)

   TYP_ListBoxChk,      // 14 // tekstiniø eiluèiø listboxas su papildoma èekinimo varnele prad_ioje eilutës

} KpWndType;


// ----------------------------
class KpBmpData // laikina struktûra parametrø perdavimui ið ShowBmp per CreateWindowEx á KpStShBmpProc() WM_CREATE ir jos sukuriamà KpWnd objektà
{               // taip pat naudojama ir KpCreateProgressWnd()
public:
   HBITMAP m_hBitMap;
   HBITMAP m_hPressed;
   HBITMAP m_hHover;
   HWND m_hBitmapCtrl;
   int m_iBmpWdt;
   int m_iBmpHgt;
   int m_iCaptHgt; // StartGrp rëmo kepurës aukðtis

   HDC m_hdcBmpHdc;

   bool m_bShowSlider;
   HBITMAP m_hSliderBmp; // jei naudojamas MuteButton'ui, tai èia perduodamas iðjungto garsiakalbio paveiksliukas (invertuotas, paspaustas)

// tik laikinos rodyklës á masyvus, trinti nieko nereikia
   int m_iBitmapCnt; // filmuko bitmapø skaièius
   unsigned char **m_plpszBmpList; // prologo filmuko bitmapø vardø masyvas
   int *m_iaBmpTimes; // prologo filmuko bitmapø rodymo laikai milisekundëmis

   int m_iProlShowTime; // KPST_ACRO_LOAD_TIME + dar ka_kiek - kiek ið viso rodysim filmukà sekundëmis

   long m_lFullSize; // pilnas kopijuojamo failo dydis slankiklio vëlesniam absoliuèiam pozicionavimui

   const unsigned char *m_lpszMsgTxt; // tekstas termometro langelyje KpCreateProgressWnd()

   KpBmpData *m_pMuteButtonBmpData; // NULL reiðkia, kad mute mygtuko nereikia // former HBITMAP m_hMuteButtonBmp; // NULL reiðkia, kad mute mygtuko nereikia // former bool m_bShowMuteButton;

private:
   void InitMembers(int iBmpWdt, int iBmpHgt);
public:
   KpBmpData(void);
   KpBmpData(int iBmpWdt, int iBmpHgt);
// destruktoriaus nereikia, nes visi bitmapai pereina á langus ir po to turëtø bûti sunaikinti kartu su KpWndList naikinimu.
// o jei destruktorius bus, tai turës nenaikinti m_hBitMap ir m_hSliderBmp
// !!! TODO patirint, ar visi m_hBitMap ir m_hSliderBmp pereina á KpWndList

   ~KpBmpData();

   HRESULT LoadImageFromFile(const unsigned char *lpszBmpFileName);
   HRESULT CalcDimensions(void);
};

// =================================== simply windows
class KpWnd     /* common class for a list of all Kp-windows */
{
public:
   HRESULT m_lhOpenResult;
   KpWndType m_iWndType;
   KpWnd *m_pNextWindow;
#if TRUE // Envir==MSWin32
   HWND m_hWndHandle;    // jei m_iWndType==TYP_KpRichEditUni, ne pats laukas, o jo apkirpimo tevelis
#endif
   HWND m_hParent;
   HINSTANCE m_hInstance;
   unsigned char m_lpszWndText[KP_MAX_FILE_LIN_LEN+1];
   HICON m_hIcon;
   HFONT m_hFont;
   KpControlStyles m_iKpCtrlStyle;

   int m_iWndX;      // window position in pixels inside of parent window
   int m_iWndY;

   int m_iWndX_10;   // lango prad_ios koordinatës x 10
   int m_iWndY_10;

   int m_iWndXStep_10; // m_iWndX_10 inkrementas
   int m_iWndYStep_10; // m_iWndY_10 inkrementas

   int m_iWdtDots;   // window size in pixels // slideriams m_hMDI_Client plotis
   int m_iHgtDots;   // slideriams m_hMDI_Client aukðtis

   int m_iParentWdtDots;   // parent window size in pixels // slideriams tëvo bitmapo plotis
   int m_iParentHgtDots;   // parent window size in pixels

   int m_iNumOfCols; // window width in text positions, former m_iWdt
   int m_iNumOfRows; // window height in text lines, former m_iHgt

   DWORD m_dwExStyle;
   DWORD m_dwStyle;
   int m_iKpWndStyle;

// --------------- TYP_MDI_Frame, TYP_KpRichEditUni, TYP_KpBitmap, TYP_KpProgressWndw
   HWND m_hMDI_Client;  // MDI client handle // former HWND *m_phMDI_Client - kam saugoti kazkur, kai galima cia?
                        // jei m_iWndType==TYP_KpRichEditUni, tikrasis KpRichEditUni laukas
                        // jei TYP_KpBitmap - slankiklio bitmapo controlas, kurá reikia judint, jo tipas TYP_KpBitmapCtrl
                        // jei TYP_KpProgressWndw - praneðimo teksto static controlas

// --------------- TYP_KpRichEditUni
   CHARFORMATW *m_pFontFmt;

// --------------- TYP_ListBox
   KpTreeEntry *m_pEntries;            // pointer to list/tree of ListBox rows
                                       // value of m_pEntries is changed and text values
                                       //    copied to m_plpszListEntries by KpCreateListBox() or
                                       //    by KP_LB_SETSTRINGLIST message handler

   unsigned char **m_plpszListEntries; // pointer to array of pointers to ListBox row texts
   int m_iNumOfListEntries;            // m_plpszListEntries[m_iNumOfListEntries] - max. galimas items skaièius
   int m_iListEntriesCount;            // current number of ListBox entries
   unsigned char *m_lpszListEntriesBuf; // buffer to store ListBox row texts
   int m_iListEntriesBufSize;          // m_lpszListEntriesBuf[m_iListEntriesBufSize]
   // start of still unused region of m_lpszListEntriesBuf:
   //    m_plpszListEntries[m_iListEntriesCount-1]+strlen(m_plpszListEntries[m_iListEntriesCount-1])+1

   HWND m_hSubListBox; // handle of subcontrol listbox // TYP_KpProgressWndw – progreso teksto statinis controlas
   HWND m_hSubLBoxScrollBar; // handle of scrollbar of subcontrol listbox

   int m_iCurSel;    // current listbox selection 0..m_iListEntriesCount-1; -1 - no selection
   int m_iCurStartEntry; // entry currently displayed at first row of listbox 0..m_iListEntriesCount-1-m_iNumOfRows
                        // -1 = no start entry

// --------------- TYP_Button
   HBITMAP m_hBmpReleased;
   HDC m_hdcReleased;
   HBITMAP m_hBmpIlluminated;
   HDC m_hdcIlluminated;
   HBITMAP m_hBmpPressed;
   HDC m_hdcPressed;

// HPEN *m_hPenScheme; // m_hPenScheme[KpNumOfShadows0]
   COLORREF *m_iaColorScheme; // m_iKpColorScheme[KpNumOfShadows0];

   bool m_bPressed;

   int m_iMessage;

// --------------- TYP_KpBitmap
   KpBmpData *m_pBmpPars;  // pagrindiniai bitmapo parametrai, kreivokai interpretuojami:
                           //    m_iParentWdtDots = m_pBmpPars->m_iBmpWdt;
                           //    m_iParentHgtDots = m_pBmpPars->m_iBmpHgt;
                           //    m_phBmpList[0] = m_pBmpPars->m_hBitmap;
                           //    _r. KpWnd::InitBmpMembers();

   // HWND m_hBitmapCtrl; // iðkeltas á m_pBmpPars->m_hBitmapCtrl // jei TYP_KpProgressWndw - slankiklio controlas, kurio tipas TYP_KpBitmap

   // int m_iBitmapCnt; // iðkeltas á m_pBmpPars->m_iBitmapCnt // filmuko bitmapø skaièius
   volatile int m_iCurBmp; // dabar rodomas filmuko bitmapas
// masyvai m_plpszBmpList ir m_iaBmpTimes – tik rodyklës, perduotos ið pagrindinës programos sukuriant KpWnd
// naikinti paèius masyvus turi pagrindinë programa
   // unsigned char **m_plpszBmpList; // iðkeltas á m_pBmpPars->m_plpszBmpList // prologo filmuko bitmapø failø vardø masyvas
   // int *m_iaBmpTimes;   // iðkeltas á m_pBmpPars->m_iaBmpTimes // prologo filmuko bitmapø rodymo laikai milisekundëmis
   HBITMAP *m_phBmpList;   // masyvas, kuriamas dinamiðkai – ið prad_iø nuliniai bitmapai, po to dinamiðkai pildomas
                           // iðeinant reikia naikinti

   long m_lFullSliderSize; // pilnas slankiklio dydis absoliuèiam pozicionavimui
   long m_lCurSliderPos; // dabartinë slankiklio pozicija pozicionuojant absoliuèiai
   long m_lCurFileStartPos; // dabar kopijuojamo failo pradinë m_lCurSliderPos reikðmë – inkremento suskaièiavimui failo viduje

// ---------------
   KpWnd(void);   /* konstruktorius */
   KpWnd(HWND hWnd, KpWndType iWndType, const unsigned char *lpszWndText, HWND hParent,
      HINSTANCE hInstance, HFONT hFont, HICON hIcon, KpControlStyles iKpCtrlStyle,
      int iWdt, int iHgt, int iNumOfCols, int iNumOfRows, DWORD dwExStyle, DWORD dwStyle,
      HWND hMDI_Client,
      HWND hBitmapCtrl = NULL, HBITMAP hBitmap = NULL, int iBitmapCnt = 0, unsigned char **plpszBmpList = NULL, int *iaBmpTimes = NULL,
      int iParentWdt = KPW_BMP_WDT, int iParentHgt = KPW_BMP_HGT,
      long lFullSliderSize = 10000L);
//    hWnd can be NULL
//    lpszWndText - static control text, will be copied to pWndPnt->m_lpszWndText, so
//          can be deleted after call to WndPreg(); can be NULL
   HRESULT GetOpenResult(void);  // Returns value of OpenResult -
                                 //    object creation error code
private:
   HRESULT InitMembers(void);
public:
   HRESULT InitBmpMembers(HWND hBitmapCtrl, HBITMAP hBitMap, int iBitmapCnt, unsigned char **plpszBmpList, int *iaBmpTimes, int iBmpWdt, int iBmpHgt);
   HRESULT InitBmpMembers(KpBmpData *pBmpPars); // pBmpPars sukurtas su new, po iðkvietimo naikinti negalima 

   virtual ~KpWnd(void);  /* destruktorius */

   HRESULT KpWndDestructor(void);  /* destruktorius */

   HRESULT DestroyWindow(void);

   HRESULT SetCurScrolPos(void); // renew position of m_hSubLBoxScrollBar

// mest lauk !!!!
   HRESULT SetListEntriesCount(int iListEntriesCount);   // nustato m_iListEntriesCount
                                                         // tik TYP_ListBoxTree ir TYP_ListBoxTreeInverted listboxams -
                                                         //    nuresetina m_lpszListEntriesBuf ir
                                                         //    m_plpszListEntries[]
   HRESULT ResetListBoxContents(int iMaxNumOfEntries, int iEntrySize, bool bSetEntries = False, KpTreeEntry *pEntries = NULL);
         // inicializuoja listboxa, jei m_pEntries!=NULL, nusiuncia reiksmes
         // vietoj SetListEntriesCount()

// -------- progress sliderio funkcijos
   void InitSliderCoords(void);
   void CalcSliderSteps(int iProlTime); // , bool test_msg = False);
         // former this->m_iWndXStep_10 = KPST_SLIDER_HSTEP_10(this, iProlTime); this->m_iWndYStep_10 = KPST_SLIDER_VSTEP_10(this, iProlTime);
         // iProlTime = KPST_ACRO_LOAD_TIME + dar ka_kiek - kiek ið viso rodysim filmukà sekundëmis
         // iProlTime == Maxint – taimerio valdymas neájungiamas
};

HRESULT ResetListBoxContents(HWND hWnd, int iMaxNumOfEntries, int iEntrySize, bool bSetEntries = False, KpTreeEntry *pEntries = NULL);
         // iesko hWnd, tada KpWnd::ResetListBoxContents()


class KpWndList
{
public:
   KpWnd *m_W_first;

   KpWndList(void);
   ~KpWndList();

   void DeleteList();
};

extern KpWndList KpWndListObj;


extern HRESULT WndPreg(KpWnd *pWndPnt, KpWndType iWndType, HINSTANCE hInstance,
                        const unsigned char *lpszLogFileName, bool bOpenWindow);
/* naujo lango uzregistravimas, inicializavimas ir itraukimas i sarasa */
//    bOpenWindow - open window after registering

extern HRESULT DeleteWnd(const KpWnd *pWndPnt);
// removes window from list, object will remain on the heap (if dynamically created)

extern HRESULT GetCurWindow(KpWnd **pCurWnd, HWND hWndHandle);
/* lango hWndHandle suradimas registruotu langu sarase pagal KpWnd::m_hWndHandle */
// jei neranda, klaidos nemeta

extern HRESULT GetCurChildWindow(KpWnd **pCurWnd, HWND hWndHandle);
/* lango hWndHandle suradimas registruotu langu sarase pagal KpWnd::m_hMDI_Client */

extern HRESULT GetWindowsCount(int *piWndCnt);
/* langu skaicius sarase */

// =================================== console window
#if TRUE // Envir==MSWin32
#define KPW_CONSOLE_CTRL_NUMOFLINES 24
#define KPW_CONSOLE_CTRL_NUMOFCOLUMNS 80
#define KPW_CONSOLE_CTRL_INIT_STR ((const unsigned char *)"                                                                                ")
#define KPW_CONSOLE_CTRL_X KPW_WND_MARGIN
#define KPW_CONSOLE_CTRL_Y KPW_WND_MARGIN
// #define KPW_CONSOLE_CHAR_WDT(style) ((KPW_CALC_STATIC_WDT_FACTOR(" ", style) * 11 / 10))
#define KPW_CONSOLE_CHAR_WDT(style) ((iaCtrlTextFactors[style] / 8))
// #define KPW_CONSOLE_CTRL_WDT(style) (KPW_CTRL_BORDER_WDT + KPW_CALC_STATIC_WDT_FACTOR(KPW_CONSOLE_CTRL_INIT_STR, style) + KPW_CTRL_BORDER_WDT)
#define KPW_CONSOLE_CTRL_WDT(style) ((KPW_CTRL_BORDER_WDT + strlen(KPW_CONSOLE_CTRL_INIT_STR) * KPW_CONSOLE_CHAR_WDT(style) + KPW_CTRL_BORDER_WDT))
#define KPW_CONSOLE_CTRL_HGT(style) (KPW_CTRL_BORDER_WDT + KPW_CONSOLE_CTRL_NUMOFLINES * iaCtrlRowHeights[iWindowsVersionCut][style] + KPW_CTRL_BORDER_WDT)
// #define KPW_CONSOLE_CHAR_HPOS(style, xx) (KPW_CONSOLE_CTRL_X + KPW_CTRL_BORDER_WDT + (xx * KPW_CALC_STATIC_WDT_FACTOR(" ", style)))
#define KPW_CONSOLE_CHAR_HPOS(style, xx) (KPW_CONSOLE_CTRL_X + KPW_CTRL_BORDER_WDT + (xx * KPW_CONSOLE_CHAR_WDT(style)))
#define KPW_CONSOLE_CHAR_VPOS(style, xx) ((KPW_CONSOLE_CTRL_Y + KPW_CTRL_BORDER_WDT + (xx * iaCtrlRowHeights[iWindowsVersionCut][style])))

#define KPW_CONSOLE_WND_X 300
#define KPW_CONSOLE_WND_Y 300
#ifdef KPCONS_OLD_STYLE
#define KPW_CONSOLE_WND_WDT(style) (KPW_WND_BORDER_WDT_INI + KPW_WND_BORDER_COR + KPW_WND_MARGIN + KPW_CONSOLE_CTRL_WDT(style) + KPW_WND_MARGIN + KPW_WND_BORDER_COR + KPW_WND_BORDER_WDT_INI + (/*(iWindowsVersion == WinXP)?(-5):*/(-5)))
#define KPW_CONSOLE_WND_HGT(style) (KPW_WND_BORDER_WDT_INI + KPW_WND_BORDER_COR + KPW_WND_CAPTION_HGT_INI + KPW_WND_MARGIN + KPW_CONSOLE_CTRL_HGT(style) + KPW_WND_MARGIN + KPW_WND_BORDER_COR + KPW_WND_BORDER_WDT_INI + (/*(iWindowsVersion == WinXP)?3:*/3))
#else
#define KPW_CONSOLE_WND_WDT(style) (iWndBorderWdt + KPW_WND_BORDER_COR + KPW_WND_MARGIN + KPW_CONSOLE_CTRL_WDT(style) + KPW_WND_MARGIN + iWndBorderWdt)
#define KPW_CONSOLE_WND_HGT(style) (iWndBorderWdt + KPW_WND_BORDER_COR + iWndCaptionHgt + KPW_WND_MARGIN + KPW_CONSOLE_CTRL_HGT(style) + KPW_WND_MARGIN + iWndBorderWdt)
#endif

#define KPW_KB_BUF_SIZE 200
#endif

// -----------------------------------
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
class KpConsole // former KpCListBox
   : public KpWnd
#if FALSE // Envir==MSWin32Mfc
   , public CListBox
#endif
{
protected:
   FILE *m_pLogFile;
   HRESULT m_lhOpenResult;

public:
   UINT_PTR m_hRefreshTimer;

// edit control for text output inside of dialog window
// former extern HWND hKpConsoleCtrl;
   HWND m_hDisplayCtrl;

protected:
   int m_iKbBufTail;
   int m_iKbBufHead;
   int m_iaKbBuf[KPW_KB_BUF_SIZE+1];

#if TRUE // Envir==MSWin32
public:
   unsigned char m_lpszaConsoleBuf[KPW_CONSOLE_CTRL_NUMOFLINES][KPW_CONSOLE_CTRL_NUMOFCOLUMNS + 1];
protected:
   int m_iCurConsoleBufRow; // pointer to console topmost row in cyclic buffer lpszaConsoleBuf[][]
#endif
public:
   unsigned char m_lpszFNameBuf[KP_MAX_FNAME_LEN+1];

   KpControlStyles m_iKpCtrlStyle; // style of display control
   bool m_bRefreshFlg; // ar reikia atnaujint

#if FALSE // Envir==MSWin32Mfc
   int m_iWdt;    // window size in text positions
   int m_iHgt;
#endif

   int m_iCurX;   // current cursor coordinates
   int m_iCurY;

   bool m_bCurOn; // cursor status

   COLORREF *m_ColorScheme;
   
   KpConsole(void);
   virtual ~KpConsole(void);
   HRESULT KpConsoleDestructor(void);
   HRESULT GetOpenResult(void);
   HRESULT Init(HINSTANCE hInstance, const unsigned char *lpszLogFileName, const unsigned char *lpszHat = null);

   HRESULT SetColorScheme(COLORREF *pColorScheme);
   HRESULT SetCtrlStyle(KpControlStyles iKpCtrlStyle);
   
   HRESULT wkbtobuf(unsigned char iInChar); /* simboli i kl. buferi */

   int wgetchar(void); /* simbolio ivedimas is klaviaturos nelaukiant */
   unsigned char *wgetstr(unsigned char *buf); /* eilutes ivedimas, buf[KPW_KB_BUF_SIZE+1] */

   HRESULT wbcolor(KpColor col, KpColor bcol, KpColor fcol); /* simb.,fono spalvu nustatymas */
   HRESULT wcrsor(int onflg); /* zymio junginejimas, atsimenant busena i m_bCurOn */
   HRESULT wloc(int xx,int yy); /* zymio pozicionavimas tekst. koordinatemis */

   HRESULT DoRefresh(void); // repaints text of console window
   HRESULT Refresh(void); // marks window for refreshing

#if Envir==MSWin32Mfc
   HRESULT AddString(CString &sItem);
#endif
   HRESULT AddString(const unsigned char *lpszoutStr);
   HRESULT AddString(const char *lpszoutStr /* LPCTSTR lpszItem */);
   HRESULT AddString(KpString vStr);
   HRESULT AddStringNoMessage(const unsigned char *lpszoutStr /* LPCTSTR lpszItem */); // for use in KpErrorProc_tag

   HRESULT wputchar(int iOutCh);
      // puts char at current console possitionn (m_iCurX, m_iCurY)

   HRESULT wputstr(const unsigned char *lpszOutStr);
   HRESULT wputstr(const char *lpszOutStr);
      // puts string at current console possitionn (m_iCurX, m_iCurY)
   HRESULT wclreol(void); /* eilutes galo isvalymas */
};
#else // #if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
typedef void KpConsole;
#endif

#if TRUE // Envir==MSWin32
extern BOOL CALLBACK KpConsoleDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);
#endif


// =================================== debug / trace
#ifdef Debug
#if ((Envir == MSWin32) || (Envir == MSWin32Mfc))
extern KpConsole KpTraceWindow;
extern KpConsole KpTraceWindow1;
extern KpConsole KpTraceWindow2;
#define KP_TRACE_WINDOW (&KpTraceWindow)
#else
#define KP_TRACE_WINDOW NULL
#endif
#else
#define KP_TRACE_WINDOW NULL
#endif


// ============================================= dialog control functions
// ----------------------------------- dialog control creation
// #define KpRichEdit20 // use Riched20.dll instead of Riched32.dll
// #define KpRichEditClipboard // set rich edit control contents through the clipboard instead of direct KpSetCtrlText()
                // used in KpSetRichCtrlText() in case of ancient Riched32.dll of Win98

#define KP_LISTBOX // use local LISTBOX control window class

//-----------------------------------
#if FALSE // Compiler==Watcom
// EM_SETTEXTEX, EM_GETTEXTEX parametrai
// turi buti jau apibrezti richedit.h
typedef struct _settextex {
    DWORD flags;
    UINT codepage;
} SETTEXTEX;
#define ST_DEFAULT   0
#define ST_KEEPUNDO  1
#define ST_SELECTION    2
#define ST_NEWCHARS     4

#ifndef WM_UNICHAR
#define WM_UNICHAR                              0x0109
#endif
#endif
//-----------------------------------
#define CP_UNICODE 1200 // SETTEXTEX::codepage for unicode

// ---------------------- TYP_ListBoxTree/TYP_ListBoxTreeInverted icons
extern HBITMAP hbmpNodeBypass;      // KP_IDI_NODE_BYPASS_BMP
extern HBITMAP hbmpNodeBypassEmpty; // KP_IDI_NODE_BYPASS_EMPTY_BMP
extern HBITMAP hbmpNodeBottom;      // KP_IDI_NODE_BOTTOM_BMP
extern HBITMAP hbmpNodeBottomLast;  // KP_IDI_NODE_BOTTOM_LAST_BMP
extern HBITMAP hbmpNodeOpen;        // KP_IDI_NODE_OPEN_BMP
extern HBITMAP hbmpNodeOpenLast;    // KP_IDI_NODE_OPEN_LAST_BMP
extern HBITMAP hbmpNodeClosed;      // KP_IDI_NODE_CLOSED_BMP
extern HBITMAP hbmpNodeClosedLast;  // KP_IDI_NODE_CLOSED_LAST_BMP

// ---------------------- TYP_ListBoxChk icons
extern HBITMAP hbmpChecked;      // KP_IDI_CHECKED_BMP
extern HBITMAP hbmpUnChecked;    // KP_IDI_UNCHECKED_BMP

// ----------------------------------- colors
// extern HBRUSH KpWhiteBrush;

// extern HPEN aPenSchemeWin[KpNumOfShadows0]; // jei nëra lokalios paletës - kurti pen dinamiðkai pagal iaColorMap[]
extern int iaColorMap[KpNumOfShadows0];

extern HRESULT InitPalette(void);


// ----------------------------------- dialog control creation
extern HRESULT CrFont(HFONT *phFont, KpControlStyles iKpCtrlStyle, int iKpWndStyle = 0);
extern HRESULT SetCtrlFont(HWND hCtrlWnd, KpControlStyles iKpCtrlStyle);

// aukstis grafinëm eilutëm
extern HRESULT KpCreateStaticRaw(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, int iWdt, int iHgt, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
// aukstis teksto eilutëm
extern HRESULT KpCreateStatic(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, int iWdt, int iLineCount, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
// former extern HRESULT KpCreateStatic(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iWdt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, int iLineCount, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
// plotá skaièiuoja automatiðkai pagal tekstà
extern HRESULT KpCreateStatic(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, int iLineCount, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
// former extern HRESULT KpCreateStatic(HINSTANCE hInst, HWND hParent, HWND *phStaticControl, const unsigned char *lpszText, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, int iLineCount, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
         // creates a static control
extern BOOL CALLBACK KpStaticDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern HRESULT KpCreateEdit(HINSTANCE hInst, HWND hParent, HWND *phEditControl, const unsigned char *lpszText, int iWdt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, int iLineCount);
extern HRESULT KpCreateEdit(HINSTANCE hInst, HWND hParent, HWND *phEditControl, const unsigned char *lpszText,           int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, int iLineCount);
         // creates an edit control
         // in second variant lpszText must contain max number of characters (spaces) to return for field length calculation

// ----------------------------------------- KpRichEdit
extern HMODULE hRichEditLib;

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
// "RichEdit" controlo callback funkcijos saugojimo laukas
// naudojamas "KpRichEdit" ir "KpRichEditUni"
extern WNDPROC RichEditProcSav;

// "KpRichEdit" controlo wrapinta callback valdimo funkcija
extern BOOL CALLBACK KpRichEditProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// "KpRichEditUni" klaviaturos peremimas - neveikia rusiskos klav. fonetinis isdestymas
extern KpChar KbCyrScanCodesArr[KPT_Ctbsiz]; // rusiskos klaviaturos skankodai
extern BOOL CALLBACK KpRichEditUniProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

// ==============================================================================================================================
#if FALSE
http://www.codeguru.com/Cpp/controls/richedit/comments.php/c5383/?thread=58860

If you want object insertion operations to work in your RichEdit Control,
you have to supply an IRichEditOleCallback interface
and implement the GetNewStorage method.


// Set-up the OLE Callback

IRichEditOleCallback* mREOLECallback = new REOLECallback;
::SendMessage(mHWnd, EM_SETOLECALLBACK, 0, (LPARAM) mREOLECallback);

// Class definition

class REOLECallback : IRichEditOleCallback
{
public:
// Constructor / Destructor
REOLECallback () { mRefCounter = 0; }
~REOLECallback () {}

// Methods of the IUnknown interface
STDMETHOD_(ULONG, AddRef) (void) { mRefCounter++; return mRefCounter; }
STDMETHOD_(ULONG, Release) (void) { if ( --mRefCounter == 0 ) delete this; return mRefCounter; }
STDMETHOD(QueryInterface) (REFIID iid, void** ppvObject)
{
if (iid == IID_IUnknown || iid == IID_IRichEditOleCallback) { *ppvObject = this; AddRef(); return S_OK; }
else return E_NOINTERFACE;
}

// Methods of the IRichEditOleCallback interface
STDMETHOD(ContextSensitiveHelp) (BOOL fEnterMode) { return E_NOTIMPL; }
STDMETHOD(DeleteObject) (LPOLEOBJECT lpoleobj) { return E_NOTIMPL; }
STDMETHOD(GetClipboardData) (CHARRANGE FAR *lpchrg, DWORD reco, LPDATAOBJECT FAR *lplpdataobj) { return E_NOTIMPL; }
STDMETHOD(GetContextMenu) (WORD seltype, LPOLEOBJECT lpoleobj, CHARRANGE FAR *lpchrg, HMENU FAR *lphmenu) { return E_NOTIMPL; }
STDMETHOD(GetDragDropEffect) (BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect) { return E_NOTIMPL; }
STDMETHOD(GetInPlaceContext) (LPOLEINPLACEFRAME FAR *lplpFrame, LPOLEINPLACEUIWINDOW FAR *lplpDoc, LPOLEINPLACEFRAMEINFO lpFrameInfo) { return E_NOTIMPL; }
STDMETHOD(GetNewStorage) (LPSTORAGE FAR *lplpstg);
STDMETHOD(QueryAcceptData) (LPDATAOBJECT lpdataobj, CLIPFORMAT FAR *lpcfFormat, DWORD reco, BOOL fReally, HGLOBAL hMetaPict) { return E_NOTIMPL; }
STDMETHOD(QueryInsertObject) (LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp) { return S_OK; }
STDMETHOD(ShowContainerUI) (BOOL fShow) { return E_NOTIMPL; }

// Data
private:
udword mRefCounter;
};

// Class implementation

STDMETHODIMP REOLECallback::GetNewStorage(LPSTORAGE FAR *lplpstg)
{
// Initialize a Storage Object from a DocFile in memory
LPLOCKBYTES lpLockBytes = NULL;
SCODE sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
if (sc != S_OK) return sc;
sc = ::StgCreateDocfileOnILockBytes(lpLockBytes, STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, lplpstg);
if (sc != S_OK) lpLockBytes->Release();
return sc;
}
#endif
// ==============================================================================================================================

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
typedef class IKpRichEditOleCallback_tag : public IRichEditOleCallback
{
public:
// Constructor / Destructor
IKpRichEditOleCallback_tag () { /* KP_TRACE("IKpRichEditOleCallback:IKpRichEditOleCallback_tag"); */ mRefCounter = 0; }
// ~IKpRichEditOleCallback_tag () {} // { KP_TRACE("IKpRichEditOleCallback:~IKpRichEditOleCallback_tag"); }

// Methods of the IUnknown interface
STDMETHOD_(ULONG, AddRef) (void) { /* KP_TRACE("IKpRichEditOleCallback:AddRef"); */ mRefCounter++; return mRefCounter; }
STDMETHOD_(ULONG, Release) (void) { /* KP_TRACE("IKpRichEditOleCallback:Release"); */ if ( --mRefCounter == 0 ) delete this; return mRefCounter; }
STDMETHOD(QueryInterface) (REFIID iid, void** ppvObject)
{
// KP_TRACE("IKpRichEditOleCallback:QueryInterface");
if (iid == IID_IUnknown || iid == IID_IRichEditOleCallback) { *ppvObject = this; AddRef(); return S_OK; }
else return E_NOINTERFACE;
}

// Methods of the IRichEditOleCallback interface
STDMETHOD(ContextSensitiveHelp) (BOOL /* fEnterMode */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:ContextSensitiveHelp"); return E_NOTIMPL; }
STDMETHOD(DeleteObject) (LPOLEOBJECT /* lpoleobj */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:DeleteObject"); return E_NOTIMPL; }
STDMETHOD(GetClipboardData) (CHARRANGE FAR * /* lpchrg */, DWORD /* reco */, LPDATAOBJECT FAR * /* lplpdataobj */) { KP_TRACE("IKpRichEditOleCallback:GetClipboardData"); return E_NOTIMPL; }
STDMETHOD(GetContextMenu) (WORD /* seltype */, LPOLEOBJECT /* lpoleobj */, CHARRANGE FAR * /* lpchrg */, HMENU FAR * /* lphmenu */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:GetContextMenu"); return E_NOTIMPL; }
STDMETHOD(GetDragDropEffect) (BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect);
STDMETHOD(GetInPlaceContext) (LPOLEINPLACEFRAME FAR * /* lplpFrame */, LPOLEINPLACEUIWINDOW FAR * /* lplpDoc */, LPOLEINPLACEFRAMEINFO /* lpFrameInfo */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:GetInPlaceContext"); return E_NOTIMPL; }
STDMETHOD(GetNewStorage) (LPSTORAGE FAR * /* lplpstg */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:GetNewStorage"); return E_NOTIMPL; }
STDMETHOD(QueryAcceptData) (LPDATAOBJECT /* lpdataobj */, CLIPFORMAT FAR * /* lpcfFormat */, DWORD /* reco */, BOOL /* fReally */, HGLOBAL /* hMetaPict */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:QueryAcceptData"); return E_NOTIMPL; }
STDMETHOD(QueryInsertObject) (LPCLSID /* lpclsid */, LPSTORAGE /* lpstg */, LONG /* cp */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:QueryInsertObject"); return E_NOTIMPL; }
STDMETHOD(ShowContainerUI) (BOOL /* fShow */) { return E_NOTIMPL; } // { KP_TRACE("IKpRichEditOleCallback:ShowContainerUI"); return E_NOTIMPL; }

// Data
private:
ULONG mRefCounter;

} IKpRichEditOleCallback;

// extern IKpRichEditOleCallback IKpRichEditOleCallbackObj;
extern IRichEditOleCallback *pIKpRichEditOleCallbackObj;
#endif

#if (Envir==MSWin32) || (Envir==MSWin32Mfc)
extern HRESULT KpCreateRichEdit(HINSTANCE /* hInst */, HWND hParent, HWND *phEditControl, const unsigned char *lpszText, int iWdt, int iHeight, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle);

// sukuria RichEdit lauka Unicode redagavimui, popup, su apkarpymo teveliu
extern HRESULT KpCreateRichEditUni(HINSTANCE hInst, HWND hParent,
   KpWnd **pEditControl,    // sukuria su new, iskviecianti programa turi sunaikinti, kai nebereikia
                           // pEditControl->m_hWndHandle - apkarpymo tevelis
                           // pEditControl->m_phMDI_Client - pats RichEdit laukas, pEditControl->m_hWndHandle vaikas
   const UniChar *sazText, // lauko pradinis tekstas, gali buti NULL
   int iWdt, int iHeight,
   int iPosX, int iPosY,   // ne kliento srities atzvilgiu, o nuo paties dialogo lango krasto -
                           //    iskaitant ir remelius bei kepures
   KpControlStyles iKpCtrlStyle, // dar nerealizuota
   DWORD dwExStyle, DWORD dwStyle,
   const unsigned char *lpszFontName,   // typeface "Times New Roman", etc.
   int iFontSize,          // fonto dydis punktais * 2
   int iFlags,             // fonto atributai - KPS_BoldFl, KPS_ItalicFl, etc.
   RGB_Color iFontColor,
   CHARFORMATW *pFontFmt   // statisko objekto adresas, objektas uzpildomas ir po to
                           //    naudojamas per visa lauko gyvavimo laika fonto atsatytmui po WM_CHAR
   );
#endif

// extern BOOL CALLBACK KpEditFrameProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


// -----------------------------
extern HRESULT KpSetCtrlText(HWND hControl, const unsigned char *lpszText);
extern HRESULT KpGetCtrlText(HWND hControl, unsigned char *lpszTextBuf, int iBufSize); // netinka "KpRichEdit" ir "KpRichEditUni" controlams
extern HRESULT KpGetRtfCtrlText(HWND hControl, unsigned char *lpszTextBuf, int iBufSize); // "KpRichEdit" ir "KpRichEditUni" controlams
extern HRESULT KpSetCtrlRtfText(HWND hControl, const unsigned char *lpszText, bool bEnabled);
                     // lpszText - text in RTF format
                     // gal kazkaip apjungti su KpSetWindowUniText() ar gal naudoti RtUnicodeToRtf() is tvrtf.cpp?
extern HRESULT KpSetRichCtrlText(HWND hControl, const unsigned char *lpszText, bool bEnabled);
                     // lpszText - plain text in 71 codetable
                     // function encloses lpszText into RTF and calls KpSetCtrlRtfText()

extern HRESULT KpGetWindowUniText(HWND hCtrl, UniChar *szaUniBuf /* unsigned char *lpszTxtBuf */, int iBufLen);

// naudoja statinius buferius - multithread-sensitive
// konvertuoja i RTF - tik RichEdit controlams
// gal kazkaip apjungti su KpSetRichCtrlText()?
extern HRESULT KpSetWindowUniText(HWND hCtrl, const UniChar *szaUniStr /* const unsigned char *lpszWndTxt */, const unsigned char *lpszFontName);

// ------------------------
#define KP_TREE_LBOX_TRCK_WDT 16 // tree listbox track icon width
#define KP_TREE_LBOX_MARGIN 4    // tree listbox track and text margins
extern HRESULT KpCreateListBox(HINSTANCE hInst, HWND hParent, HWND *phListControl, const unsigned char *lpszText,
                                 int iWdt, int iHgt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle,
                                 DWORD dwExStyle, DWORD dwStyle, KpTreeEntry *pEntries, int iInitSel=(-1),
                                 KpWndType iWndType = TYP_ListBox, int iNumOfRows = -1); // former KpCreateList()
                                 // iWndType could be TYP_ListBoxTree or TYP_ListBoxTreeInverted for
                                 //    expanding/collapsing LBS_OWNERDRAWFIXED listboxes
                                 // iNumOfRows – max. eiluèiø skaièius, jei -1 – tiek kiek iKpCtrlStyle stiliaus eiluèiø telpa á iHgt
#ifdef KP_LISTBOX
BOOL CALLBACK KpListBoxDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

extern HRESULT KpCreateComboBox(HINSTANCE hInst, HWND hParent, HWND *phBoxControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, KpTreeEntry *pEntries, int iInitSel=(-1)); // former KpCreateBox()
extern HRESULT KpCreateListComboBox(HINSTANCE hInst, HWND hParent, HWND *phListBoxControl, HWND *phBoxBkgdControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, KpControlStyles iKpCtrlStyle, DWORD dwExStyle, DWORD dwStyle, KpTreeEntry *pEntries, WNDPROC lpfnBoxBkgdProc, int iInitSel=(-1));

extern HRESULT SetComboBoxSel(HWND hBoxControl, int iInitSel); // sets combobox selection, former SetBoxSel()
extern HRESULT SetListBoxSel(HWND hBoxControl, int iInitSel); // sets listbox selection
extern HRESULT SetKpListBoxSel(KpWnd *pKpBoxControl, long lSelPos, int iDirection, bool bForced);
                     // iDirection: 0 - most upper entry, 1 - middle, 2 - lowest
                     // bForced - nustato net jei padetis ir nesikeicia

// formats listbox line of two parts inserting allignment spaces
extern HRESULT FormatListString(unsigned char *lpszOutStr,
                         const unsigned char *lpszInStr1, const unsigned char *lpszInStr2,
                         int iInStr1MaxLen, int iMaxAllign,
                         KpControlStyles iKpCtrlStyle); // HDC hDc); //

extern HRESULT KpCreateBitmap(HINSTANCE hInst, HWND hParent, HWND *phBitmapCtrl, HBITMAP hBitMap, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle);
extern HRESULT KpCreateBitmap(HINSTANCE hInst, HWND hParent, HWND *phBitmapCtrl, int iBitmapId, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle);
         // creates bitmap
extern HRESULT KpCreateIcon(HINSTANCE /* hInst */, HWND hParent, HWND *phIconCtrl, HICON hIcon, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle);
extern HRESULT KpCreateIcon(HINSTANCE hInst, HWND hParent, HWND *phIconCtrl, int iIconId, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle);
         // creates bitmap control based on icon
extern BOOL CALLBACK KpIconDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern HRESULT KpCreateScrollBar(HINSTANCE hInst, HWND hParent, HWND *phScrollBarCtrl, int iPosX, int iPosY, int iLen, DWORD dwExStyle, DWORD dwStyle);
         // creates scrollbar
         // DWORD dwStyle must contain either SBS_HORZ or SBS_VERT
extern HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle, DWORD dwStyle);
extern HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, int iPosX, int iPosY);
extern HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, int iIconId, int iPosX, int iPosY, int iWdtX, int iWdtY, DWORD dwExStyle, DWORD dwStyle);
extern HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, int iIconId, int iPosX, int iPosY);
extern HRESULT KpCreateButton(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, KpBmpData *pButBitmap, int iPosX, int iPosY, DWORD dwExStyle, DWORD dwStyle);
// internal kpwindow function, called by both partial KpCreateButtonLoc() functions
extern HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, int iBitmapReleasedId, int iBitmapIlluminatedId, int iBitmapPressedId, int iPosX, int iPosY, int iWdtX, int iWdtY, int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0] /* HPEN aPenScheme[KpNumOfShadows0] */, KpControlStyles iKpCtrlStyle = KPW_CONTROL_STYLE_NORMAL);
extern HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, int iBitmapReleasedId, int iBitmapIlluminatedId, int iBitmapPressedId, int iPosX, int iPosY, int iWdtX, int iWdtY, int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0] /* HPEN aPenScheme[KpNumOfShadows0] */, KpControlStyles iKpCtrlStyle = KPW_CONTROL_STYLE_NORMAL);
extern HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, int iPosX, int iPosY, int iWdtX, int iWdtY, int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0] /* HPEN aPenScheme[KpNumOfShadows0] */, KpControlStyles iKpCtrlStyle = KPW_CONTROL_STYLE_NORMAL);
extern HRESULT KpCreateButtonLoc(HINSTANCE hInst, HWND hParent, HWND *phButtonControl, int iId, const unsigned char *lpszText, HBITMAP hBitmapReleased, HBITMAP hBitmapIlluminated, HBITMAP hBitmapPressed, int iPosX, int iPosY, int iWdtX, int iWdtY, int iKpWndStyle, DWORD dwStyle, COLORREF iaColorScheme[KpNumOfShadows0] /* HPEN aPenScheme[KpNumOfShadows0] */, KpControlStyles iKpCtrlStyle = KPW_CONTROL_STYLE_NORMAL);
extern BOOL CALLBACK KpButtonDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

         // creates press-button
         // iId - button return value - IDOK, IDCANCEL etc.
extern HRESULT KpCreateCheckBox(HINSTANCE /* hInst */, HWND hParent, HWND *phChBoxControl, int iPosX, int iPosY, DWORD dwExStyle, DWORD dwStyle);
         // creates a check box

extern HRESULT KpCreateRadioBut(HINSTANCE /* hInst */, HWND hParent, HWND *phChBoxControl, int iPosX, int iPosY, DWORD dwExStyle, DWORD dwStyle);
         // creates a radio button
extern WNDPROC ButtonProcSav;
extern BOOL CALLBACK KpRadButProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// DWORD dwStyle - window style for CreateWindowEx()
// DWORD dwExStyle - extended window style for CreateWindowEx()

extern HRESULT KpCreateFrame(HINSTANCE hInst, HWND hParent, HWND *phFrameCtrl, /* HWND *phMDIClient, */ int iPosX, int iPosY, int iWdtX, int iWdtY);
// *phMDIClient perkeltas i KpWnd:m_hMDI_Client
// gal dar grazinti ir naujai sukurta ir uzregsitruota KpWnd?

extern BOOL CALLBACK KpFrameDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern HRESULT KpCreateFrameChild(HINSTANCE hInst, HWND hMDIClient, HWND *phFrameChild, int iChildPosX, int iChildPosY, int iChildWdtX, int iChildWdtY, unsigned char *lpszClassName, WNDPROC lpfnFrameProc);

// -------------------------------------
#define KPSBMP_BMP_X 0
#define KPSBMP_BMP_Y 0
// #define KPSBMP_BMP_WDT (bmp_pars->m_iBmpWdt) // (cur_app->m_Ini.iBitmapWdt)
// #define KPSBMP_BMP_HGT (bmp_pars->m_iBmpHgt) // (cur_app->m_Ini.iBitmapHgt)
// #define KPSBMP_WND_WDT (KPW_WND_THIN_BORDER_WDT + KPSBMP_BMP_WDT + KPW_WND_THIN_BORDER_WDT)
#define KPSBMP_WND_WDT(bmp_wdt) (KPW_WND_THIN_BORDER_WDT + (bmp_wdt) + KPW_WND_THIN_BORDER_WDT)
// #define KPSBMP_WND_HGT (KPW_WND_THIN_BORDER_WDT + KPSBMP_BMP_HGT + KPW_WND_THIN_BORDER_WDT)
#define KPSBMP_WND_HGT(bmp_hgt) (KPW_WND_THIN_BORDER_WDT + (bmp_hgt) + KPW_WND_THIN_BORDER_WDT)

extern HRESULT ShowBmp(const unsigned char *lpszBmpFileName, int iBmpWdt, int iBmpHgt,
                HWND *phBitmapWindow, bool bShowSlider,
                int iBitmapCnt = 0, unsigned char **plpszBmpList = NULL, int *iaBmpTimes = NULL,
                int iSliderId = KP_IDI_SLIDER_2_BMP, // = KP_IDI_SLIDER_1_BMP,
                int iProlShowTime = 0,
                HWND hParent = HWND_DESKTOP, int iBmpX = 0, int iBmpY = 0,
                KpBmpData *pMuteButtonBmpData = NULL, // HBITMAP hMuteButtonBmp = NULL); // bool bShowMuteButton = False); // garso gesinimo mygtukas
                const unsigned char *lpszWndName = (const unsigned char *)"", LPSTR lpszIcon = IDI_APPLICATION);
                // jei pMuteButtonBmpData == NULL – mute mygtuko nerodom
                // iProlShowTime = KPST_ACRO_LOAD_TIME + dar ka_kiek - kiek ið viso rodysim filmukà sekundëmis

extern BOOL CALLBACK KpStShBmpProc( // callback procedure for m_hBitmapWindow creation by ShowBitmap()
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);

// --------------------- termometras
extern HRESULT KpCreateProgressWnd(HWND *phProgressWnd, const unsigned char *lpszMsgTxt, int iSliderShowTime, long lFullSize);
// iSliderShowTime sekundëmis
// lFullSize - pilnas kopijuojamo failo dydis slankiklio absoliuèiam (ne procentiniam) pozicionavimui
extern HRESULT KillProgressWnd(HWND hProgressWnd); // sunaikina slankiklio langà

extern BOOL CALLBACK KpProgressDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);

// nustato slankiklio pozicijà procentais
extern HRESULT KpSetProgressPos(HWND hProgressWnd, int iPerCent);
extern HRESULT KpSetProgressPosAbs(HWND hProgressWnd, long lProcessedSize, long lFullSize);
extern HRESULT KpSetProgressPosInc(HWND hProgressWnd, long lIncrement);
// pastumia slankiklá KpWnd::m_lFullSliderSize at_vilgiu, inkrementuoja KpWnd::m_lCurSliderPos
// lIncrement – einamojo failo áraðytø KBaitø skaièius
extern HRESULT KpSetProgressFileStartPos(HWND hProgressWnd);
// nustato pradinæ failo slankinklio pozicijà KpWnd::m_lCurFileStartPos

extern HRESULT KpSetProgressTxt(HWND hProgressWnd, const unsigned char *lpszMsgTxt, const unsigned char *lpszProgressTxt = (const unsigned char *)"");

// koreguoja slankiklio greièio inkrementus, kad slankiklio persistûmimas per visà ilgá bûtø iSliderShowTime (sekundëmis)
extern HRESULT KpSetProgressTime(HWND hProgressWnd, int iSliderShowTime);

// perduoda susikaupusius praneðimus (slankiklio langui), grá_ta kai praneðimø nebelieka
extern HRESULT KpProcMsgSimple(void);
DWORD CALLBACK KpCopyFileCallBack
(
  LARGE_INTEGER /* TotalFileSize */,
  LARGE_INTEGER /* TotalBytesTransferred */,
  LARGE_INTEGER /* StreamSize */,
  LARGE_INTEGER /* StreamBytesTransferred */,
  DWORD /* dwStreamNumber */,
  DWORD /* dwCallbackReason */,
  HANDLE /* hSourceFile */,
  HANDLE /* hDestinationFile */,
  LPVOID /* lpData */
);


// ================================================== process functione
// opens file with standard browser or executes command line
// starts child thread, uses StartProcess()
// lpszCmdLine - file name to open or simply full command line with .exe, .com or .bat inside
// returns generated command line with standard browser .exe inside to lpszCmdLine
// buffer lpszCmdLine must be not less than KP_MAX_FNAME_LEN + 1 bytes long
// lpszStartCmdLine - pradinio kpstart failo paleidimo eilutë (KpStIniData::m_lpszCmdStr[]) – jei pdf-us reikia paleidinët su tuo paèiu readeriu
extern HRESULT StartCmdProcess(unsigned char *lpszCmdLine, const unsigned char *lpszCurDir, DWORD *plThreadId, HANDLE *phProcess, bool bShowErrorMessages,
                  WORD iWndShowType, // gali bûti SW_SHOWNORMAL arba ne (visi kiti suveikia kaip SW_SHOWMINNOACTIVE)
                  WORD iSoundShowType = SW_SHOWMINIMIZED, bool bUseInternalViewer = True, const unsigned char *lpszStartCmdLine = (const unsigned char *)"",
                  bool bForceAcroMaximize = True // visus AcroRd procesus maksimizuoti, iðskyrus paleid_iamus ið m_Ini.m_lpszCmdStr
#if FALSE
                  ,
#if CompilerGr==Mingw
                     KpGeckoDialog
#else
                     void
#endif
                        **ppDlgPtr = NULL
#endif
                     , bool bOutMsg = True); // neiðveda praneðimø apie nerastà failà, bet grà_ina klaidà KP_E_FILE_NOT_FOUND

extern bool IsSoundFile(const unsigned char *lpszCmdLine); // ar yra ".mp3", ".wma", ".wav", ".m3u", ".wvl" (wav'ø sàraðas)
extern bool IsSoundFileProcessed(const unsigned char *lpszCmdLine); // ar yra ".wav", ".wvl"

extern bool IsPlainTextFile(const unsigned char *lpszFName);

#define KP_BRING_TO_TOP_TIME        5000  // kiek milisekund_iø bandom iðkeldinëti paleistos programos langà
#define KP_BRING_TO_TOP_WINDOW_TIME 2000  // kiek milisekund_iø bandom iðkeldinëti paleistos programos langà, kai jis jau atsirado
#define KP_BRING_TO_TOP_INTERVAL    500   // kas kiek milisekund_iø bandom iðkeldinëti paleistos programos langà (bandymø intervalai)
// executes command line
// starts child thread
extern HRESULT StartProcess(const unsigned char *lpszCmdStr, const unsigned char *lpszCurDir, DWORD *plThreadId, HANDLE *phProcess,
                  WORD iWndShowType, // gali bûti SW_SHOWNORMAL arba ne (visi kiti suveikia kaip SW_SHOWMINNOACTIVE)
                  bool bForceAcroMaximize = False, bool bDoSetPlacement = True,
                  bool bOutMsg = True); // neiðveda praneðimø apie nerastà failà, bet grà_ina klaidà KP_E_FILE_NOT_FOUND

extern HRESULT WaitForProcessEnd(HANDLE hProcess, HANDLE hThread);

extern HRESULT CloseProcess(const unsigned char *lpszCmdLine, DWORD lThreadId);

extern HRESULT KpCloseWindow(const unsigned char *lpszWndName, bool bCheckError);
               // if bCheckError==False does not output error message if window not found
               //    returns only KP_E_OBJ_NOT_FOUND error code in that case

// -----------------------------------------------
extern HRESULT KpSleep(long lMilliseconds, HWND hCurWnd = HWND_DESKTOP); // jei lMilliseconds == 0L, tiesiog pakimba standartinëj praneðimø eilëj (pvz., kol bus u_darytas konsolës langas) 


// -----------------------------------------------
extern HWND GetThreadWindow(DWORD lThreadId, HWND hPreviousFound = NULL);
extern HWND GetProcessWindow(DWORD lProcId, HWND hPreviousFound = NULL);
extern HWND GetWindowByName(const unsigned char *lpszWinName, bool bFullName, HWND hPreviousFound = NULL);
// if !bFullName - only substring of full window name
// hPreviousFound - pratesti paieska nuo jau anksciau rasto lango; == NULL - nuo top lango

extern HWND GetChildWindow(HWND wParent, int iOrderNumber); // iOrderNumber - vienu mazesnis uz ta, kuri isveda kpswls.exe - palikta taip, kad nereiktu perdarinet visu paleideju
extern HRESULT SendStringToWindow(HWND wWindow, const unsigned char *lpszOutStr,
                  HWND hTopWindow = NULL); // langas, kuriuo reikia u_stori slapta_od_io langà

extern int GetProcessIdByName(const unsigned char *lpszExeFName); // lpszExeFName - tikslus .exe failo vardas su tipu be kelio


// tik Vistoj
// #define THREAD_MODE_BACKGROUND_BEGIN 0x00010000


// ======================================= text
extern HDC GetDCSelFont(HWND hWnd);

extern HRESULT GetStrWidth(const unsigned char *lpszString, int *piWidth, HDC hdc);
extern HRESULT GetStrWidthABC(const unsigned char *lpszString, int *piWidth, HDC hdc);
   // calculates text width in pixels

extern HRESULT GetStrWidthKp(const unsigned char *lpszString, int *piWidth, KpControlStyles iKpCtrlStyle);
   // calculates text width in milimeters
   // encoding 71 Windows-1257

extern int KpCharWidths[KPT_Ctbsiz][KPW_NUM_OF_CONTROL_STYLES_0];


// ======================================= mouse
#define KPW_MOUSE_X_MASK 0x0000FFFF
#define KPW_MOUSE_X_POS  0
#define KPW_MOUSE_Y_MASK 0xFFFF0000
#define KPW_MOUSE_Y_POS  16

extern HRESULT ExtractMouseXY(long lMouseXY, int *piMouseX, int *piMouseY); // lMouseXY - lParam from WM_MOUSEFIRST

// istraukia peles koordinates is WM_MOUSEMOVE lParam
// siaip jau apibrezti windowsx.h, bet tada kazko sugenda KpTreeEntry::GetTopWindow()
// #if (Compiler!=Watcom) || (__WATCOMC__ != 1202) // kai __WATCOMC__ == 1280 (2010.08.10), vël reikia
#if (Compiler!=Watcom) // jau nebereikia
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

// ======================================= drawing
// window styles iKpWndStyle
#define KP_WND_SUNKEN        0x0001
#define KP_WND_RAISED        0x0002
#define KP_WND_SUNKEN_BORDER 0x0004
#define KP_WND_RAISED_BORDER 0x0008
#define KP_WND_SUNKEN_BUTTON 0x0010
#define KP_WND_RAISED_BUTTON 0x0020
#define KP_WND_TAB           0x0040 // siaip asele
#define KP_WND_LEFT_TAB      0x0080 // asele su matomu kairiu krastu
#define KP_WND_RIGHT_TAB     0x0100 // asele su matomu desiniu krastu
#define KP_WND_NO_TOP        0x0200 // bet virsutinio krasto - kai virs lango yra aseles, pavyzdziui
#define KP_WND_UNPROC_BUT    0x0400 // mygtuko maigymas neapdorojamas, viskas paveiksliukuose
#define KP_WND_PROC_CURS     0x0800 // mygtukuose pelës kursorius keièiamas á pirðtà
#define KP_WND_TOOLBAR       0x1000
#define KP_WND_URL           0x2000

extern HRESULT KpDrawLine(HDC hDC, int iX1, int iY1, int iX2, int iY2, int iKpWndStyle, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
extern HRESULT KpDrawRect(HDC hDC, int iX1, int iY1, int iX2, int iY2, int iKpWndStyle, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
extern HRESULT KpDrawRect(HDC hDC, RECT Rect, int iKpWndStyle, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
extern HRESULT KpDrawBox(HDC hDC, int iX1, int iY1, int iX2, int iY2, KpShadow iShadow, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);
extern HRESULT KpDrawBox(HDC hDC, RECT Rect, KpShadow iShadow, COLORREF iaColorScheme[KpNumOfShadows0]); // HPEN aPenScheme[KpNumOfShadows0]);

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld kpmsg
#if FALSE

#if Envir==MSWin32Mfc

class kpmsg : public CDialog
{

   HRESULT lhOpenResult;
   unsigned char m_lpszOutStr[KP_MAX_FILE_LIN_WDT+1];

   BOOL OnInitDialog(void);

// Konstruktion
public:
   kpmsg(const unsigned char *lpszOutStr, CWnd* pParent = NULL); // constructor with output text initialization
         // only collects error codes to lhOpenResult, does not output any messages


   HRESULT GetOpenResult(void); // collected errors from lhOpenResult


// Dialogfelddaten
   //{{AFX_DATA(kpmsg)
   enum { IDD = IDD_MSGBOX };
      // HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
   //}}AFX_DATA


// _berschreibungen
   // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
   //{{AFX_VIRTUAL(kpmsg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
   //}}AFX_VIRTUAL

// Implementierung
protected:

   // Generierte Nachrichtenzuordnungsfunktionen
   //{{AFX_MSG(kpmsg)
      // HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif

#endif


// ==================================================== Windows I/O
// defined only in WinVista
#if FALSE
#define IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER CTL_CODE(IOCTL_STORAGE_BASE, 0x0304, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _MEDIA_SERIAL_NUMBER_DATA {
  ULONG SerialNumberLength;
  ULONG Result;
  ULONG Reserved[2];
  UCHAR SerialNumberData[];
} MEDIA_SERIAL_NUMBER_DATA,
 *PMEDIA_SERIAL_NUMBER_DATA;
#endif


#if FALSE // (Compiler==Mingw)
// turetu buti apibrezta winuser.h, bet suveikia #if (_WIN32_WINNT >= 0x0403) ?

#define INPUT_MOUSE 0x00000000
#define INPUT_KEYBOARD 0x00000001
#define INPUT_HARDWARE 0x00000002

typedef struct tagMOUSEINPUT {
  LONG dx;
  LONG dy;
  DWORD mouseData;
  DWORD dwFlags;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} MOUSEINPUT,*PMOUSEINPUT;
typedef struct tagKEYBDINPUT {
  WORD wVk;
  WORD wScan;
  DWORD dwFlags;
  DWORD time;
  ULONG_PTR dwExtraInfo;
} KEYBDINPUT,*PKEYBDINPUT;
typedef struct tagHARDWAREINPUT {
  DWORD uMsg;
  WORD wParamL;
  WORD wParamH;
} HARDWAREINPUT,*PHARDWAREINPUT;
typedef struct tagINPUT {
  DWORD type;
  _ANONYMOUS_UNION union {
                MOUSEINPUT mi;
                KEYBDINPUT ki;
                HARDWAREINPUT hi;
  } DUMMYUNIONNAME;
} INPUT,*PINPUT,*LPINPUT;

WINUSERAPI UINT WINAPI SendInput(UINT,LPINPUT,int);
#endif


// ----------------------------------------------
// atitinkamybë tarp Kp kodø lenteliø ir Windows Locale numerio, naudojamo, pvz., clipboard'o duomenø tipui CF_LOCALE kartu su CF_TEXT
extern int iKpt2WinLocale[KPT_Ctnum];

// ==================================================== Windows registry
extern HRESULT SetRegKeyAccess(unsigned char *lpszKeyName);

// ------------------------------
// rekursinis RegDeleteKey()
// defined only in WinVista
extern /* LONG */ HRESULT KpRegDeleteTree(HKEY hKey, const unsigned char *lpszSubKey, bool bIgnoreErrors = True);

// ------------------------------
// áraðo registro rakto reikðmæ
// ankstesnæ reikðmæ iðsaugoja á lpValueName + "_sav"
// jei reikðmës tokiu vardu dar nëra - neiðsaugoja (lpValueName + "_sav" nesukuria)
// jei reikðmë lpValueName + "_sav" jau yra - nesaugoja (reiðkia, ankstesnë sesija nulû_o nespëjus atstatyt)
//
extern HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpValueName, DWORD dwValType, const LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors = True);
extern HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwValType, const LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors = True);

extern HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, bool bIgnoreErrors = True, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, bool bIgnoreErrors = True, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData, bool bIgnoreErrors = True);

extern HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwValType, const LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors = True);
extern HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, bool bIgnoreErrors = True, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, bool bIgnoreErrors = True, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValue(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData, bool bIgnoreErrors = True);
// ðitose funkcijose vietoj hKey galima naudot tokiø raktø kombinacijà:
#define KP_HKEY_CURRENT_USER  (0x80000010)   // HKEY_CURRENT_USER
#define KP_HKEY_LOCAL_MACHINE (0x80000020)   // HKEY_LOCAL_MACHINE

#define KP_HKEY_NONE (~(KP_HKEY_CURRENT_USER | KP_HKEY_LOCAL_MACHINE))
#define KP_HKEY_CLEAR (KP_HKEY_NONE | 0x80000000)

// nustato raktus abiejose db - KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER
extern HRESULT KpRegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, bool bIgnoreErrors = True, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, bool bIgnoreErrors = True, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData, bool bIgnoreErrors = True);

// nustato KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER AcroReader'io raktus, iVers versija * 100 (6.00 --> 600)
extern HRESULT KpRegSetValueAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValueAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, DWORD dwValType = REG_BINARY);
extern HRESULT KpRegSetValueAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData);
extern HRESULT KpRegSetValueAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const unsigned char *lpszData, DWORD dwValType);
extern HRESULT KpRegSetValueAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, const char *lpszData, DWORD dwValType);
extern HRESULT KpRegSetValueAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD iData);

// ------------------------------
// atstato iðsaugotà rakto reikðmæ
// jei iðsaugota nebuvo (nëra reikðmës vardu lpValueName + "_sav") - reikðmæ iðtrina
//
extern HRESULT KpRegRestore(HKEY hKey, LPCTSTR lpValueName, bool bIgnoreErrors = True);
extern HRESULT KpRegRestore(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bIgnoreErrors = True);

extern HRESULT KpRegRestore(int iKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bIgnoreErrors = True);
// paskutinëj funkcijoj galima naudoti KP_HKEY_... kombinacijas

// atstato raktus abiejose db - KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER
extern HRESULT KpRegRestore(LPCTSTR lpSubKey, LPCTSTR lpValueName, bool bIgnoreErrors = True);

// atstato KP_HKEY_LOCAL_MACHINE | KP_HKEY_CURRENT_USER AcroReader'io raktus, iVers versija * 100 (6.00 --> 600)
extern HRESULT KpRegRestoreAcro(int iVers, LPCTSTR lpSubKey, LPCTSTR lpValueName);
extern HRESULT KpRegRestoreAcro(const char *lpszVers, LPCTSTR lpSubKey, LPCTSTR lpValueName);

// -------------------------------
extern HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpValueName, DWORD dwValType, LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors = True);
extern HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwValType, LPBYTE lpDataBuf, DWORD dwBufLen, bool bIgnoreErrors = True);

extern HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, unsigned char *lpszData, DWORD dwBufLen, bool bIgnoreErrors = True);
extern HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, char *lpszData, DWORD dwBufLen, bool bIgnoreErrors = True);
extern HRESULT KpRegQueryValue(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, PDWORD *piData, bool bIgnoreErrors = True);

// -------------------------------
extern HRESULT KpRegExportBranch(fstream *out_file, HKEY hQueryKey, unsigned const char *lpszKeyName, bool bEncode = False);

#endif // #ifndef kpwindows_included
