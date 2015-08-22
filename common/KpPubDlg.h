// ---------------------------------------
// KpPubDlg.h
// dialogas su publishinimo langu (tux_gecko, MSHTML, RichEdit) - dël lzdshl ir arkshl
// apibrëþimai
//

#ifndef KpPubDlg_included
#define KpPubDlg_included

#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef lzdshn_included
#error lzdshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif

// -----------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define IBSH_WND_STYLE  (WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME /* | WS_VISIBLE| WS_BORDER| WS_POPUP */)
#else
#define IBSH_WND_STYLE  (WS_POPUP /* | WS_SYSMENU */ /* | WS_VISIBLE */)
#endif

// stumiam uþ ekrano kraðto, kad po KpPubDlg::RestoreSavedCoords() nustatytø á desktopo vidurá
// kai po RestoreSavedCoords() atsiverèia naujas failas su kitu dokumento dydþiu (StartGrp naujai parsiøstas meniu), centravimas sugenda
#define IBSH_DEF_WND_X (-10) // 100 // former IBSH_WND_X
#define IBSH_DEF_WND_Y (-10) // 100 // former IBSH_WND_Y

// ----------------------------------
#define IBSH_DEF_WND_DX 800 // former KP_SHOWXGECKO_DX, IBSH_WND_DX
#define IBSH_DEF_WND_DY 600 // former KP_SHOWXGECKO_DY // former IBSH_WND_DY

#define IBSH_DEF_WND_MIN_DX 100
#define IBSH_DEF_WND_MIN_DY 100
#define IBSH_DEF_WND_MAX_DX 1600 // Maxint
#define IBSH_DEF_WND_MAX_DY 1200 // Maxint

#define IBSH_DEF_SRC_X (IBSH_WND_SOFT_BORDER_WDT)
#define IBSH_DEF_SRC_Y (IBSH_WND_SOFT_BORDER_WDT + IBSH_WND_SOFT_CAPTION_HGT)

// tokius nustatom fono dydþius .htm failo <img> tage:
// <img id="background" src="./index_files/slatel.jpg" width="720.000000" height="450.000000"/>
// (nors faktiðki IBSH_PROJ_TEVT backgroundo bitmapo failo matmenys yra 1440x900)
#define IBSH_DEF_SRC_DX (IBSH_DEF_WND_DX - IBSH_WND_BORDER_WDT * 2 - IBSH_WND_SOFT_BORDER_WDT * 2)
#define IBSH_DEF_SRC_DY (IBSH_DEF_WND_DX - IBSH_WND_BORDER_WDT * 2 - IBSH_WND_SOFT_BORDER_WDT * 2 - IBSH_WND_CAPTION_HGT - IBSH_WND_SOFT_CAPTION_HGT)

// ---------------
#define IBSH_SCROLLBAR_WDT KPW_SCROLLBAR_WDT // former KPGECKO_SCROLLBAR_WDT

// kad neatsirastø scrollbarø – apvalinimo paklaidoms
#define IBSH_RES_DX_COR 0 // 40
#define IBSH_RES_DY_COR 0 // 40

// Standartinës Gecko lango paraðtës 8 px, tvarkom HTML-e:
//
// <style>
// img#background
// {
//    margin-left: -8px;
//    margin-top: -8px;
// }
//
// tada deðiniam ir apatiniam kraðtuose lieka dvigubos paraðtës, reikia prie IBSH_RES_DX_ENL/IBSH_RES_DY_ENL pridët po 16
// geriau:
//
// <body ...
//

// ----------------------------------
#if IBSH_PROJ == IBSH_PROJ_MIKO_VIEW
// naikinam – reikia rodyti scrollbarà, nes rankytë neleidþia paþymëti teksto kopijavimui
#define IBSH_RES_DX_ENL  0
#define IBSH_RES_DY_ENL  0
#else
#define IBSH_RES_DX_ENL  ((2 * 8) + IBSH_SCROLLBAR_WDT + IBSH_RES_DX_COR)
#define IBSH_RES_DY_ENL  ((2 * 8) + IBSH_SCROLLBAR_WDT + IBSH_RES_DY_COR)
#endif

// #define IBSH_DEF_RES_DX (IBSH_DEF_SRC_DX + IBSH_RES_DX_ENL) // former KPGECKO_INIT_ORIG_REZ_WDT
// #define IBSH_DEF_RES_DY (IBSH_DEF_SRC_DX + IBSH_RES_DY_ENL) // former KPGECKO_INIT_ORIG_REZ_HGT

// ----------------------------------
#define KPPUBDLG_RESIZE_WDT_SENS 20 // former IBSH_RESIZE_WDT_SENS

// ------------------------------- m_hPubIcon
#define IBSH_ICON_X     IBSH_BUT_MARGIN
#define IBSH_ICON_Y     IBSH_BUT_MARGIN
#define IBSH_ICON_WDT   IBSH_BUT_WDT // 24

// ------------------------------- m_hCaption
#define IBSH_CAPT_STYLE KPW_CONTROL_STYLE_CAPTION // KPW_CONTROL_STYLE_BOLD // KPW_CONTROL_STYLE_HEADING_3 // KPW_CONTROL_STYLE_NORMAL
#define IBSH_CAPT_X     (IBSH_ICON_X + IBSH_BUT_WDT + IBSH_BUT_MARGIN) // (IBSH_BUT_SAVE_AS_X + IBSH_BUT_WDT + IBSH_BUT_MARGIN) // (IBSH_BUT_MARGIN /* IBSH_WND_MARGIN */ + 20)
#define IBSH_CAPT_Y     (IBSH_BUT_MARGIN /* IBSH_WND_MARGIN */ + (IBSH_BUT_WDT/2) - (IBSH_CAPT_DY/2))
#define IBSH_CAPT_DX    500 // 200
#define IBSH_CAPT_DY    20 // (iaCtrlHeights[iWindowsVersionCut][IBSH_CAPT_STYLE]) // IBSH_BUT_WDT

// ----------------------------- m_ButExit
#define  IBSH_BUT_EXIT_X(dlg_ptr) ((dlg_ptr)->m_iWndCurDX /* - (dlg_ptr)->m_iWndSoftBorderWdt */ - IBSH_BUT_MARGIN - (dlg_ptr)->m_ButExitBmpData.m_iBmpWdt /* IBSH_BUT_WDT */)
#define  IBSH_BUT_EXIT_Y(dlg_ptr) (/* (dlg_ptr)->m_iWndSoftBorderWdt + */ IBSH_BUT_MARGIN)

// ----------------------------- m_ButMinimize
#define  IBSH_BUT_MIN_X(dlg_ptr) ((dlg_ptr)->m_iWndCurDX /* - (dlg_ptr)->m_iWndSoftBorderWdt */ - IBSH_BUT_MARGIN - (dlg_ptr)->m_ButExitBmpData.m_iBmpWdt /* IBSH_BUT_WDT */ - IBSH_BUT_MARGIN - (dlg_ptr)->m_ButMinBmpData.m_iBmpWdt /* IBSH_BUT_WDT */)
#define  IBSH_BUT_MIN_Y(dlg_ptr) (/* (dlg_ptr)->m_iWndSoftBorderWdt + */ IBSH_BUT_MARGIN)

#if IBSH_SKIN==IBSH_SKIN_MIKO
#define  IBSH_BUT_EXIT_TOOLTIP_TXT  ((const unsigned char *)"  Uþverti")
#endif

#if IBSH_SKIN==IBSH_SKIN_START_GRP
#define  IBSH_BUT_EXIT_TOOLTIP_TXT  ((const unsigned char *)"  Uþverti")
#endif


#ifdef IBSH_RES_MODE_XGECKO
class XKpGecko;
#endif

class KpPubDlg : public KpWnd
{
// -----------------------
public:
   KpFileSys *m_pKpFileSys; // turinio skaitymo objektas, tik nuoroda perduodama á konstruktoriø; trinti nereikia, trinti turi motininë aplikacija

// -----------------------
   XmlVersions m_iXmlVers;    // rodomo failo XML version identifier - HTML v4.0, XML v1.0, etc.
private:
   UC_Modes m_iEncMode;

// -----------------------
public:
   volatile HWND m_hDialogWindow; // visas dialogo langas

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   HWND m_hBackGround;
   HWND m_hPubIcon;
#endif

// -------------------------------------------------------------------
// atkelti ið LzdShDlg, tipo, virtualûs laukai, naudojami LzdShSearch objekte, kreipiantis per pointerá á KpPubDlg

// reikalingi LzdShSearch::SetToSearchStr()
   /* volatile */ HWND m_MainList; // former m_ResList
   /* volatile */ HWND m_SearchList;
   /* volatile */ HWND m_HistList;
   volatile HWND m_CurList;

// naudojamas LzdShSearch::FormatEntry()
   /* volatile */ KpTreeEntry *m_DictList;
   volatile int m_iCurDictEntry; // aktyvaus þodyno indeksas liste

#ifdef LZDSHT_DISPLAY_SINGLE_THREAD
public:
   bool m_bNewContentReady;   // atkeltas ið LzdShSearch, tikrinti (pDialogPtr != NULL) vietoj (pLzdSearch != NULL)
#endif

// naudojamas LzdShSearch::SearchForEntry()
   volatile int m_iCtrlCtbl;

#ifdef IBSH_RES_MODE_XGECKO
   volatile bool m_bDictChanged;
#endif

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   KpBmpData m_BgrBmpData; // XG_BackGround <background> lango fono parametrai; jei m_BgrBmpData.m_hBitMap != NULL – fonas yra // former HBITMAP m_hBckGrndBmp; HWND m_hBckGrnd; HDC m_hdcBckGrnd;
#endif

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   KpBmpData m_LogoBmpData; // XG_BackGround <background> lango fono parametrai; jei m_BgrBmpData.m_hBitMap != NULL – fonas yra // former HBITMAP m_hLogoBmp; ir HDC m_hdcLogo; 
#endif

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   KpBmpData m_ButExitBmpData;
   KpBmpData m_ButMinBmpData;
#endif

// HWND m_MenuButFile;
   HWND m_MenuButOpt;
   HWND m_MenuButHelp;

   /* volatile */ HWND m_InpEdit;

   /* volatile */ HWND m_TabMain;
   /* volatile */ HWND m_TabSearch;
   /* volatile */ HWND m_TabHist;

   int m_iNumOfDictEntries;
   int m_iNumOfLines;
   volatile int m_iNumOfHistEntries;

#ifdef IBSH_RES_MODE_XGECKO
   HWND m_ButBack;
   HWND m_ButForward;
#endif

   HWND m_ButSearch;
   HWND m_ButFontZoom;
   HWND m_ButNarrow;
   HWND m_ButAcc;

#if (IBSH_SKIN == IBSH_SKIN_MIKO) || (IBSH_SKIN == IBSH_SKIN_START_GRP) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) || (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   HWND m_ButExit;
   HWND m_ButMinimize;
#endif

   HWND m_DictBox;

   bool m_bDiagOnTop;
   int m_iDiagOnTopCnt;

   HCURSOR m_hCurSav;

#ifdef LZDSHT_SEARCH_SINGLE_THREAD
   volatile bool m_bButSearchPressed;
#endif

   volatile unsigned char m_lpszCurDictName[KP_MAX_FNAME_LEN + 2]; // TV_XL_MAX_TAG_WDT+2]; // aktyvaus þodyno vardas
#ifdef IBSH_RES_MODE_XGECKO
   volatile unsigned char m_lpszSelDictName[KP_MAX_FNAME_LEN + 2]; // TV_XL_MAX_TAG_WDT+2]; // ieðkomo þodþio þodyno vardas
#endif                                                             // pagal tai, kokio tago zodis paspaustas HTML lange
                                                                   // arba iðtrauktas ið m_HistList áraðo techninës dalies
// ---------------------------------------------------------------------

// -------------------------
// atkelti ið KpGeckoDialog

#ifdef IBSH_RES_MODE_XGECKO
// XGecko m_ResCtrl;
// XKpGecko m_ResCtrl; // former m_ResGecko;
   XKpGecko *m_pResCtrl; // rezultato laukas, apkirpimo controlo m_hScreen vaikas
#endif
// -------------------------

// -------------------------
// atkelta ið LzdShDlg
#ifdef IBSH_RES_MODE_RTF
   /* volatile */ HWND m_ResRichEdit;
#  ifdef LZDSH_EDITOR_BUILD
#     ifdef Debug
// HWND m_ResRichTest;
#     endif
#  endif
#endif
// -------------------------

// -------------------------
// atkelti ið LzdShSearch

   volatile bool m_bWrkFl;    // ar gyvas tevo langas (pries uzsidarydamas tevas pranesa, kad jau viskas)

   volatile bool m_bKbdInput; // value of theDialog.m_InpEdit changed - search entry entered from keyboard or pasted - do search using main HW index

#if IBSH_SKIN == IBSH_SKIN_STANDART
   volatile HWND m_TabCtrl;
   HIMAGELIST m_hTabImgList;
#endif

   HBITMAP m_hMainBmp;
   HBITMAP m_hSearchBmp;
   HBITMAP m_hHistBmp;
   HBITMAP m_hMainMaskBmp;
   HBITMAP m_hSearchMaskBmp;
   HBITMAP m_hHistMaskBmp;
// -------------------------

   HWND m_hCaption; // lango antraðtës static controlas – jei ne IBSH_SKIN_STANDART
   unsigned char m_lpszCaption[KP_MAX_FNAME_LEN + 1]; // TV_XL_MAX_IX_LEN + 1]; // m_hCaption turinys

   int m_RedrawTimer; // lzdshl naudojamas lango iðvedimo uþlaikymui, kad neiðvedinëtø be perstojo draginant listboxà
                     // iBshl naudojamas sinchronizavimui su spinner.gif sukimusi
   int m_iDoRedraw;  // èia gal tik lzdshl 
                     // po keliø taimerio m_RedrawTimer (KP_REDRAW_TIMER, KP_REDRAW_TIMEOUT) ciklø perpieðti langà -
                     // kad galima bûtø uþdelsti perpieðimà po lango vaizdo suformavimo, kad neperpieðinëtø du kartus
                     // 0 - perpieðti nereikia
                     // former bool m_bDoRedraw; // poþymis, kad reikia perpieðt langà - pasikeitë lango dydis, etc.

   DWORD m_dwStyle; // windowsinis lango stilius

// ------------------ viso lango matmenys
   int m_iWndCurX; // lango pradþios koordinatës
   int m_iWndCurY;

private:
// ----------
   int m_iWndDX;  // pradiniai lango matmenys, naudojami skeilinimo faktoriaus skaièiavimui;
   int m_iWndDY;  // turi bûti nustatomi po naujo þinomo dydþio failo perskaitymo

public:
   int m_iWndCurDXprec; // dinamiðki matmenys nuo WM_SIZE po patampymo pele,
   int m_iWndCurDYprec; // perduodami á Resize(), kad paskaièiuotø skeilinimo faktoriø – santyká su m_iWndDX/m_iWndDY

   int m_iWndCurDX; // lango matmenys po Resize(), einamieji lango matmenys
   int m_iWndCurDY;

// viso lango matmenø ribos
   int m_iWndDXmin;
   int m_iWndDXmax;
   int m_iWndDYmin;
   int m_iWndDYmax;

// -----------------
// int m_iWndSoftBorderWdt; // nestandartinio lango rëmelio plotis // iðskaidytas á m_iWndSoftHorBorderWdt, m_iWndSoftTopBorderWdt ir m_iWndSoftBotBorderWdt
   int m_iWndSoftHorBorderWdt; // ðonø rëmelio plotis
   int m_iWndSoftTopBorderWdt; // virðaus rëmelio plotis
   int m_iWndSoftBotBorderWdt; // apaèios rëmelio plotis
   int m_iWndSoftCaptHgt; // nestandartinës lango antraðtës aukðtis
   int m_iWndHardBorderWdt; // standartinio Windows lango rëmelio plotis, nepriskaièiuojamas prie lango atvaizdavimo srities (jei naudojamas pagal skinà)
   int m_iWndHardCaptHgt; // standartinës Windows lango antraðtës aukðtis, nepriskaièiuojamas prie lango atvaizdavimo srities (jei naudojamas pagal skinà)

// ----------------- apkirpimo controlas
   HWND m_hScreen;   // XKpGecko tëvas, apkerpantis scrollbarus
                     // jo dydis turi tiksliai sutapti su rodomo HTML dydþiu

   int m_iScrX;      // pradinës apkirpimo langelio koordinatës // former m_iWndResX
   int m_iScrY;
private:
   int m_iScrCurX;   // einamosios apkirpimo langelio pradþios koordinatës
   int m_iScrCurY;   // former m_iWndCurResY
public:
   int m_iScrDX;     // pradiniai apkirpimo langelio m_hScreen matmenys // former iBshFileSys::m_iCtrlDX;
   int m_iScrDY;     // former iBshFileSys::m_iCtrlDY;

// ið HTML failo iðtraukti controlo matmenys nusëda èia
   int m_iScrCurDX;  // einamieji apkirpimo langelio m_hScreen matmenys // former m_iCurRezWdt, m_iWndCurResDX
   int m_iScrCurDY;  // former m_iCurRezHgt, m_iWndCurResDY // m_iWndCurResDX/m_iWndCurResDY buvo vidinio rez. langelio – su prisumuotais m_iResDXenl/m_iResDYenl ir m_iResDXcor/m_iResDYcor

public:
   int m_iFact;      // tampymo koeficientas * 1000 // santykis tarp einamøjø ir pradiniø m_hScreen matmenø, perskaièiuotø ið m_iWndCurDX ir m_iWndDX
                     // naudojamas rezultato HTML koeficientø perskaièiavimui, tiesiog viskas dauginama ið m_iFact/1000
                     // rezultatas turi tiksliai tilpti á m_hScreen
                     // jeigu lango paraðtës tampomos – dinaminës m_hScreen koordinatës m_iScrCurX/m_iScrCurY irgi perskaièiuojami dinamiðkai ið pradiniø m_iScrX/m_iScrY

// ----------------- rezultato laukas m_hScreen viduje, su prisumuotais m_iResDXenl/m_iResDYenl
   int m_iResX; // pradinë rezultato langelio pozicija m_hScreen atþvilgiu // former m_iWndCurResX, m_iWndCurResX
   int m_iResY; // former m_iWndResY, m_iWndCurResY

// int m_iResDX; // pradiniai rezultato langelio matmenys // former m_iOrigRezWdt // naudojam m_iScrDX + m_iResDXenl
// int m_iResDY; // former m_iOrigRezHgt // naudojam m_iScrDY + m_iResDYenl

// int m_iResCurDX; // einamieji rezultato langelio matmenys // naudojam m_iScrCurDX + m_iResDXenl
// int m_iResCurDY; // naudojam m_iScrCurDY + m_iResDYenl

   int m_iResDXenl; // XKpGecko controlo padidinimas, kad deðinio ir apatinio kraðtø marginai ir, galbût, atsiradæ scrollbarai pasislëptø po m_hScreen deðiniu/apatiniu kraðtais
   int m_iResDYenl;

// ------------------
public:
   int m_iMouseX; // dabartinës pelës koordinatës
   int m_iMouseY;

   bool m_bLButPressed; // left mouse button pressed flag // formerly used for draging
   bool m_bCaptured;
   bool m_bResizing; // ar vyksta lango tampymas, jei taip, reikia performuoti langeliø dydþius

   bool volatile m_bClose; // baigti darbà (vietoj WM_QUIT praneðimo, kuris kaþko nenueina)
   bool volatile m_bLogoff; // StartGrp.exe uþdaryti meniu langà ir pradëti nuo Login()

   bool volatile m_bRefresh;  // uþsakyti output controlo refreðinimà (KpGeckoDialog::m_pResCtrl) (nes ið kito threado nesirefreðina?)
                              // sinchronizuojant su spinerio sukimusi
   bool volatile m_bRefreshing;  // refreðinimas dabar vyksta

   bool volatile m_bXGeckoPending; // XGecko semaforas – kad iðvedimo failas nebûtø keièiamas, kol XGecko jo dar neiðvedë; naudoti WaitForXGecko() 

   KpPubDlg(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers = IBSH_OUT_VERS, UC_Modes iEncMode = UC_PlainText,
      const unsigned char *lpszCaption = IBSH_WND_CAPTION,
      int iWndDXmin = IBSH_DEF_WND_MIN_DX, int iWndDXmax = IBSH_DEF_WND_MAX_DX, int iWndDYmin = IBSH_DEF_WND_MIN_DY, int iWndDYmax = IBSH_DEF_WND_MAX_DY,
      int iWndSoftBorderWdt = IBSH_WND_SOFT_BORDER_WDT, int iWndSoftCaptHgt = IBSH_WND_SOFT_CAPTION_HGT, int iWndHardBorderWdt = IBSH_WND_BORDER_WDT, int iWndHardCaptHgt = IBSH_WND_CAPTION_HGT,
      int iScrX = IBSH_DEF_SRC_X, int iScrY = IBSH_DEF_SRC_Y, int iScrDX = IBSH_DEF_SRC_DX, int iScrDY = IBSH_DEF_SRC_DY,
      int iResDXenl = IBSH_RES_DX_ENL, int iResDYenl = IBSH_RES_DY_ENL,
      DWORD dwStyle = IBSH_WND_STYLE, int iInitWndX = IBSH_DEF_WND_X, int iInitWndY = IBSH_DEF_WND_Y, int iInitWndDX = IBSH_DEF_WND_DX, int iInitWndDY = IBSH_DEF_WND_DY,
      HWND hParent = HWND_DESKTOP);
   virtual ~KpPubDlg();

   HRESULT RestoreSavedCoords(void); // atstato iðsaugotas ankstesnes lango koordinates, iðkvieèia Resize()
   HRESULT SaveCoords(void); // iðsaugo lango koordinates

   virtual HRESULT Resize(void){ return(S_OK); }  // perskaièiuoja langø koordinates
                                      // áëjimas: m_iWndCurDXprec, m_iWndCurDYprec
                                      // iðëjimas:   m_iFact,
                                      //             m_iScrCurDX, m_iScrCurDY,
                                      //             m_iScrCurX, m_iScrCurY
                                      //             m_iResDX, m_iResDY,
                                      //             nustato m_iDoRedraw
   HRESULT ResizeCommon(void); // KpGeckoDialog::Resize() uþbaigimas // former CompleteResize()

   virtual HRESULT OpenWindow(HINSTANCE /* hInst */, bool /* bShowWindow */ = True){ OpenWindowLocal(); return(S_OK); } // sukuria ir atidaro dialogo langa
   virtual HRESULT OpenWindowLocal(void){ return(S_OK); } // papildymai ið vidurinio lygio paveldëtos klasës (KpGeckoDlg ar MsHtmlDlg) // former CompleteOpenWindow()

   virtual HRESULT CloseWindow(void); // kol kas tik sunaikina taimerius
   
   HRESULT CreateBackground(void);

   HRESULT GetXmlVersion(XmlVersions *piVersion);     // Gets XML version - value of m_iXmlVers
   HRESULT GetEncoding(UC_Modes *piEncMode);

   HRESULT ShowDialog(void); // parodo dialogo langà
   HRESULT HideDialog(void); // laikinai paslepia dialogo langà

   HRESULT WaitForXGecko(void);

   virtual HRESULT RedrawWindow(void){ RedrawWindowLocal(); return(S_OK); } // pakeièia langeliø dydá ir perpaiðo langa
   virtual HRESULT RedrawWindowLocal(void){ return(S_OK); } // papildymai ið vidurinio lygio paveldëtos klasës (KpGeckoDlg ar MsHtmlDlg)

   virtual HRESULT DisplayResult(void){ DisplayResultCommon(); return(S_OK); } // former KpGeckoDialog::Load()
      // isijungia m_bSemBlocked semafora
   HRESULT DisplayResultCommon(void); // iðkvieèiamas ið DisplayResult()
      // paleidþia HTML buferio m_pKpFileSys->m_pResBuf[] ákëlimà á browserá (KpGeckoDialog::Load())
      // pazoomina Gecko controlà

   virtual int DoEdit(void){ return(S_OK); }; // perima dialogo praneðimø apdorojimà; gràþina kodà, kurá reikia gràþinti ið WinMain()

   HRESULT ExitCapture(void);
   virtual HRESULT CompleteDrag(void) { return(S_OK); } // paveldëtos klasës WM_EXITSIZEMOVE uþbaigimas

// -------------------------
// atkelti ið LzdShDlg
   virtual HRESULT RefreshResCtrl(void){ return(S_OK); } // perpaiðo m_pResCtrl
   virtual HRESULT GetOnTop(bool *pbAlwaysOnTop);
   virtual HRESULT BringToTop(bool /* bAlwaysOnTop */){ return(S_OK); }

   virtual HRESULT SelectList(long /* lOffset */){ return(S_OK); }

   virtual HRESULT InitDisplay(void){ return(S_OK); } // konstruktoriaus tæsinys
   virtual HRESULT FinitDisplay(void){ return(S_OK); } // destruktoriaus pradþia
   virtual HRESULT InitThreadDisplay(void){ return(S_OK); } // konstruktoriaus tæsinys, iðkvieèiamas tam threade, kuriame po to bus rodomas vaizdas
   virtual HRESULT FinitThreadDisplay(void){ return(S_OK); } // destruktoriaus pradþia, iðkvieèiama tam threade, kuriame buvo iðkviestas InitThreadDisplay()

   virtual HRESULT InitDictList(void){ return(S_OK); }
   virtual HRESULT ProcessInput(int /* iToHistListFlags */){ return(S_OK); }

   virtual HRESULT ChangeDict(int /* iDictEntry */, bool /* bCheckFileExist */, bool /* bPostPone */ = False){ return(S_OK); }
   virtual HRESULT ChangeDict(const unsigned char * /* lpszDictName */, bool /* bCheckFileExist */, bool /* bPostPone */ = False){ return(S_OK); }

   virtual HRESULT GetCurListSel(/* HWND hListCtrl, */ int /* iToHistListFlags */){ return(S_OK); }

   virtual HRESULT SetEditControlText(const unsigned char * /* lpszInStr */){ return(S_OK); }
// -------------------------
};


// ---------------------------------------------
// lango stumdymas etc.
extern BOOL CALLBACK KpPubDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);


#endif // #ifndef KpPubDlg_included
