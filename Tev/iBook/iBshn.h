// -----------------------------------------
// iBshn.h
// el. knygø perþiûros programa
// aplinkos nuostatos
//

// Paveldëjimo hierarchijos variantai:
//
//    iBshFileSys: public KpFileSys    // paprasta failo paieðka per vienà (hx) indeksà
//    LzdShSearch: public KpFileSys    // sudëtinga lizdo paieðka per kelis (hx, hw) indeksus
//
//    iBshDlg:  public KpGeckoDialog:  public KpPubDlg: public KpWnd    // paprastas dialogas su pora mygtukø ir rezultato controlu per visà langà
//    LzdShDlg: public KpGeckoDialog:  public KpPubDlg: public KpWnd    // þodyno langas su þodyno valdymo mygtukais, xGecko
//    LzdShDlg: public KpRtfDialog:    public KpPubDlg: public KpWnd          // RichEdit
//    LzdShDlg: public KpMsHtmlDialog: public KpPubDlg: public KpWnd          // MSHTML
//
// Algoritmas:
//
//    p_file_sys = new iBshFileSys();   // sukuriam failø sistemà
//
//    p_file_sys->OpenFiles(); // atidarom archyvà
//
//       p_dialog = new iBshDlg(p_file_sys);
//
//       p_dialog->OpenWindow();
//          // p_dialog->RestoreSavedCoords();
//             // p_dialog->Resize();
//                // p_dialog->ResizeCommon();
//          // p_dialog->OpenWindowLocal();
//             // p_dialog->InitGecko(); // KpGecko
//                // p_dialog->m_pResCtrl = new XKpGecko;
//                // p_dialog->m_pGeckoInit = new XGeckoInit;
//                // p_dialog->m_pGeckoInit->setProtocolIStreamFactory(KpGeckoStreamFactory);
//             // p_dialog->CreateResCtrl();
//                // p_dialog->m_pResCtrl->create()
//                // p_dialog->m_pResCtrl->setClipboardFilter(clipboardFilter);
//
//    p_file_sys->SearchForEntry(p_dialog);
//       // p_file_sys->FormatEntry()
//          // pCurEntry->GetBgrDim() // iðtraukia dokumento dydá
//          // p_dialog->Resize(); // jeigu IBSH_TRANSPARENT
//                // p_dialog->ResizeCommon();
//          // pCurEntry->SetCtrls();
//          // p_dialog->DisplayResult();
//             // p_dialog->DisplayResultCommon();
//          // p_dialog->RedrawWindow();
//             // p_dialog->RedrawWindowLocal();
//
//       p_dialog->ShowDialog();
//
//       p_dialog->DoEdit();
//
//       p_dialog->HideDialog();
//
//       delete p_dialog;
//          // p_dialog->FinitGecko(); // KpGecko
//
//    delete p_file_sys;
//       // p_file_sys->CloseFiles();
//
//
//    KpGeckoStreamFactory()
//       // ret_p = new XKpGeckoStream(NULL, (const unsigned char *)url); // jeigu standartinis failo vardas – rodom paskutiná surastà lizdà/failà
//       // p_file_sys->CreateGeckoStream(fname_ptr, url, &ret_p); // jeigu reikia pakraut naujà failà; èia be jokios paieðkos
//


#ifndef iBshn_included
#define iBshn_included

// ----------------------------- projektai
#define IBSH_PROJ_TEVT        0  // MKRI testas
#define IBSH_PROJ_MIKO_VIEW   1  // ArkSh SZIPP MIKO projektuose
#define IBSH_PROJ_LZDSH       2  // WinLED
#define IBSH_PROJ_START_GRP   3  // StartGrp meniu/lentyna
#define IBSH_PROJ_SPLASH      4  // KPWindow: ShowBmp()
#define IBSH_PROJ_REG_ATM     5  // RegAtm.exe atmintukø registratorius

// <<<<<<<<<<<<<<<<<<< keisti èia
// #define IBSH_PROJ IBSH_PROJ_TEVT
// #define IBSH_PROJ IBSH_PROJ_MIKO_VIEW
// #define IBSH_PROJ IBSH_PROJ_LZDSH
// #define IBSH_PROJ IBSH_PROJ_START_GRP
#define IBSH_PROJ IBSH_PROJ_SPLASH
// #define IBSH_PROJ IBSH_PROJ_REG_ATM

// ===========================================================================
// -------------------------- failø sistemos kodavimas
// KpFileSys:
//
// #define IBSHT_ARCHIVE   // failai supakuoti á archyvà, jei neapibrëþtas – failai palaidi
// #define IBSHT_ENCODED   // duomenys archyve uzkoduoti - naudojam failø sistemà .xdb (nekoduotas archyvas – .xml failas, kurio áraðai – .htm failai ar þodyno áraðai)
                           // jei ne IBSHT_ARCHIVE – tada koduoti pavieniai failai
                           // pavieniai failai koduojami EnctBufInc(), lzdshp lizdai – KP_RC_ENCODE_ENTRY 
// #define IBSHT_EXT_FILES_ARCHIVED // visi iðoriniai failai (.jpg, .flv, .swf) irgi archyve

#if (IBSH_PROJ == IBSH_PROJ_MIKO_VIEW) || (IBSH_PROJ == IBSH_PROJ_LZDSH)
#define IBSHT_ARCHIVE
#define IBSHT_ENCODED
#endif

#if (IBSH_PROJ == IBSH_PROJ_MIKO_VIEW)
#define IBSHT_EXT_FILES_ARCHIVED
#endif

#if (IBSH_PROJ == IBSH_PROJ_START_GRP)
// #define IBSHT_ENCODED
#endif

// ===========================================================================
// -------------------------- output lango reþimai
// KpPubDlg:
//
#if CompilerGr == Mingw
#define IBSH_RES_MODE_XGECKO  // output per Gecko TUX // former RES_MODE_XGECKO // former DYMSH_XGECKO // kà rodom – ar .bmp, ar komponuojam ið .svg sàraðiuko .mcl
#else
#define IBSH_RES_MODE_RTF     // former RES_MODE_RTF
// #define IBSH_RES_MODE_MSHTML  // output per MSHTML // former RES_MODE_MSHTML
#endif


// ------------------------------
#if CompilerGr != Mingw
#undef IBSH_RES_MODE_XGECKO
#define IBSH_RES_MODE_RTF
#endif

#if CompilerGr != Mingw
#ifdef IBSH_RES_MODE_XGECKO
#error IBSH_RES_MODE_XGECKO defined
#endif
#endif

// ---------------------------
#ifdef IBSH_RES_MODE_RTF
#ifdef IBSH_RES_MODE_MSHTML
#error IBSH_RES_MODE_RTF and IBSH_RES_MODE_MSHTML conflict
#endif
#endif

#ifdef IBSH_RES_MODE_MSHTML
#ifdef IBSH_RES_MODE_XGECKO
#error IBSH_RES_MODE_MSHTML and IBSH_RES_MODE_XGECKO conflict
#endif
#endif

#ifdef IBSH_RES_MODE_XGECKO
#ifdef IBSH_RES_MODE_RTF
#error IBSH_RES_MODE_XGECKO and IBSH_RES_MODE_RTF conflict
#endif
#endif


// ===========================================================================
// -------------------------- skinai; galioja tik konstruktoriaus iðkvietime, toliau – per KpPubDlg laukus
// KpPubDlg:
//
#define IBSH_SKIN_STANDART    0 // former KPPUB_SKIN_STANDART

#define IBSH_SKIN_MIKO        1
#define IBSH_SKIN_START_GRP   2

// #define IBSH_SKIN_LZDSH    3 // former KPPUB_SKIN_INTERNAL // nëra tokio, naudoti #if IBSH_SKIN != IBSH_SKIN_STANDART

// #define IBSH_SKIN_LZDSH_STANDART 4       // lzdsh_cla.exe (classic) // former LZDSH_SKIN_STANDART 0 // pakeistas á IBSH_SKIN_STANDART
#define IBSH_SKIN_LZDSH_MAHAGON  5       // obslete // lzdsh_mah.exe // former LZDSH_SKIN_MAHAGON 1
#define IBSH_SKIN_LZDSH_MAHAGON_LIGHT 6  // obslete // lzdsh_mahl.exe // former LZDSH_SKIN_MAHAGON_LIGHT 2
#define IBSH_SKIN_LZDSH_MAHAGON_3D 7     // lzdsh_mahd.exe // former LZDSH_SKIN_MAHAGON_3D 3

#define IBSH_SKIN_SPLASH      8     // KpWindow: ShowBmp() – Splash bitmapo skinas – plikas staèiakampis langas be jokiø rëmelio;
                                    // Ðità skinà naudoti ir tada, kai reikia keliø KpPubDlg controlø, tada jø tëvas ne HWND_DESKTOP, o tas grupinis langas.
                                    // Tampymas/stumdymas tada atskirai, ne per iBshl
                                    // Ðità skinà galima naudoti ir nepriklausomai nuo nustatyto projekto/skino –
                                    // KpPubDlg konstruktoriuj nurodant konstantas su prieðdëliais IBSH_SPLASH_...

// former KPPUB_SKIN
// #define KPPUB_SKIN KPPUB_SKIN_STANDART
// #define KPPUB_SKIN KPPUB_SKIN_INTERNAL

#if IBSH_PROJ == IBSH_PROJ_TEVT
#define IBSH_SKIN IBSH_SKIN_STANDART
#endif

#if (IBSH_PROJ == IBSH_PROJ_MIKO_VIEW) || (IBSH_PROJ == IBSH_PROJ_REG_ATM)
// #define IBSH_SKIN IBSH_SKIN_STANDART
#define IBSH_SKIN IBSH_SKIN_MIKO
#endif

#if IBSH_PROJ == IBSH_PROJ_START_GRP
#define IBSH_SKIN IBSH_SKIN_START_GRP
#endif

#if IBSH_PROJ == IBSH_PROJ_LZDSH
// #define IBSH_SKIN IBSH_SKIN_LZDSH

// former LZDSH_SKIN
// #define LZDSH_SKIN LZDSH_SKIN_STANDART
// // #define LZDSH_SKIN LZDSH_SKIN_MAHAGON
// // #define LZDSH_SKIN LZDSH_SKIN_MAHAGON_LIGHT
// #define LZDSH_SKIN LZDSH_SKIN_MAHAGON_3D

#define IBSH_SKIN IBSH_SKIN_STANDART                  // <<<<<<< keisti èia
// // #define IBSH_SKIN IBSH_SKIN_LZDSH_MAHAGON
// // #define IBSH_SKIN IBSH_SKIN_LZDSH_MAHAGON_LIGHT
// #define IBSH_SKIN IBSH_SKIN_LZDSH_MAHAGON_3D          // <<<<<<< keisti èia
#endif

#if IBSH_PROJ == IBSH_PROJ_SPLASH
#define IBSH_SKIN IBSH_SKIN_SPLASH
#endif

// ===========================================================================
#define IBSH_TRANSPARENT      // jei neapibrëþtas, pridedami papildomi IBSH_PROJ_TEVT controlai, java scriptai

#define IBSH_NOZOOM           // dokumentas nezoominamas, rodomas originaliam mastelyje; KpPubDlg::m_iFact visada 1000;
                              //    failo keitimas suveikia kaip lango resizinimas – iðtraukti ið HTML dokumento matmenys perskaièiuojami á lango matmenis;
                              //    jei dokumento dydþio iðtraukti nepavyksta – langas paliekamas koks buvo
                              // jei neapibrëþtas – failo keitimas tik perskaièiuoja zoomo faktoriø KpPubDlg::m_iFact, lango dydþio nekeièia
                              //    m_iFact sukalamas atgal á HTML, kad visas sutilptø á buvusá lauko dydá

// #define IBSH_MARGINS       // Palikti baltus laukelius aplink darbiná langà.
                              // Jei IBSH_MARGINS neapibrëþtas, darbinis þiûrëjimo langas nuo pat kairio virðutinio kampo

// #define IBSH_PRESERVE_RATIO // Skeilinti ir pagal X, ir pagal Y. Lieka balti laukai arba ið ðonø, arba virðuj ir apaèioj.
                               // Jei IBSH_PRESERVE_RATIO neapibrëþtas, skeilina tik pagal X, o pagal Y uþpildo visà aukðtá
                               // former KP_GECKO_PRESERVE_RATIO

// --------------------------------
#if IBSH_PROJ == IBSH_PROJ_TEVT
#define IBSH_MARGINS
#define IBSH_PRESERVE_RATIO
#endif

// ===========================================================================
// -------------------------- Save As mygtukas
// iBshl:
//
#if IBSH_PROJ == IBSH_PROJ_MIKO_VIEW
#define IBSH_SAVE_AS
#endif


// ===========================================================================
// -------------------------------- archyvo failo vardas
// KpFileSys:

#define IBSHT_ARCFNAME  ((const unsigned char *)"arksh")

// #ifdef IBSHT_ENCODED
//#define IBSHT_FIRST_ENTRY  ((const unsigned char *)"p.xdb")
// #else
//#define IBSHT_FIRST_ENTRY  ((const unsigned char *)"p22.htm")
//#define IBSHT_FIRST_ENTRY  ((const unsigned char *)"m9/index.html")
//#define IBSHT_FIRST_ENTRY  ((const unsigned char *)"index.html")
//#define IBSHT_FIRST_ENTRY  ((const unsigned char *)"file.doc")
#define IBSHT_FIRST_ENTRY  ((const unsigned char *)"index.htm") // m_lpszHtmlFileName[] pradinë reikðmë
// #endif


// ===========================================================================
// ------------------------
#define IBSH_OUT_VERS XM_VERS_HTML401_TRANS
// #define IBSH_OUT_VERS XM_VERS_XHTML


// --------------------------------
// #define TEST_NO_THREADS

// ------------------------------------
#define IBSH_BUT_MARGIN KPW_CTRL_MARGIN

// ----------------------------- galioja tik konstruktoriuj, vëliau – tik per KpPubDlg laukus
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define IBSH_BUT_WDT 20
#  if IBSH_PROJ == IBSH_PROJ_LZDSH
#     define IBSH_WND_CAPTION ((const unsigned char *)"WinLED")
#     define IBSH_WND_BORDER_WDT iWndBorderWdt
#     define IBSH_WND_SOFT_BORDER_WDT 0
#     define IBSH_WND_CAPTION_HGT (iWndCaptionHgt + iWndMenuHgt)
#     define IBSH_WND_SOFT_CAPTION_HGT 0
#  else
#     define IBSH_WND_CAPTION ((const unsigned char *)"ArkSh")
#     define IBSH_WND_BORDER_WDT iWndBorderWdt
#     define IBSH_WND_SOFT_BORDER_WDT 0
#     define IBSH_WND_CAPTION_HGT iWndCaptionHgt
#     define IBSH_WND_SOFT_CAPTION_HGT 0
#  endif
#endif

#if IBSH_SKIN == IBSH_SKIN_MIKO
#define IBSH_BUT_WDT    29 // KPW_ICON_BUTTON_WDT
#define IBSH_WND_CAPTION ((const unsigned char *)"MIKO þiûryklë")
#define IBSH_WND_BORDER_WDT 0
#define IBSH_WND_SOFT_BORDER_WDT 2 // iWndBorderWdt
#define IBSH_WND_CAPTION_HGT 0 // (IBSH_BUT_WDT + 2*IBSH_BUT_MARGIN) // KPW_WND_CAPTION_HGT_INI
#define IBSH_WND_SOFT_CAPTION_HGT (IBSH_BUT_WDT + IBSH_BUT_MARGIN)
#endif

#if IBSH_SKIN == IBSH_SKIN_START_GRP
#define IBSH_BUT_WDT 20
#define IBSH_WND_CAPTION ((const unsigned char *)"StartGrp")
#define IBSH_WND_BORDER_WDT 0
#define IBSH_WND_SOFT_BORDER_WDT 0 // 2 // iWndBorderWdt
#define IBSH_WND_CAPTION_HGT 0 // (IBSH_BUT_WDT + 2 * IBSH_BUT_MARGIN) // KPW_WND_CAPTION_HGT_INI
#define IBSH_WND_SOFT_CAPTION_HGT (IBSH_BUT_WDT + 2 * IBSH_BUT_MARGIN) // (IBSH_BUT_WDT + IBSH_BUT_MARGIN)
#endif

#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
#define IBSH_BUT_WDT 20
#define IBSH_WND_CAPTION ((const unsigned char *)"WinLED")
#define IBSH_WND_BORDER_WDT 0
#define IBSH_WND_SOFT_BORDER_WDT 2 // iWndBorderWdt
#define IBSH_WND_CAPTION_HGT 0 // (IBSH_BUT_WDT + 2*IBSH_BUT_MARGIN) // KPW_WND_CAPTION_HGT_INI
#define IBSH_WND_SOFT_CAPTION_HGT (IBSH_BUT_WDT + IBSH_BUT_MARGIN)
#endif

#if IBSH_SKIN == IBSH_SKIN_SPLASH
#define IBSH_BUT_WDT 20
#define IBSH_WND_CAPTION ((const unsigned char *)"Atsklanda")
#define IBSH_WND_BORDER_WDT 1 // 0
#define IBSH_WND_SOFT_BORDER_WDT 0 // 1
#define IBSH_WND_CAPTION_HGT 0
#define IBSH_WND_SOFT_CAPTION_HGT 0
#endif

#endif // #ifndef iBshn_included
