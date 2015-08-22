// -----------------------------------------
// lzdsh.h
// zodyno perziuros programa ir XMLT redaktorius
// dialogas
//

#ifndef lzdshl_included
#define lzdshl_included


// ------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef lzdshn_included
#error lzdshn.h not included
#endif

#ifndef lzdsh_included
#error lzdsh.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// --------------------------
extern int LzdShResDyCor[NumOfWinVersions0];

// --------------------------
#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif

#ifdef KP_GECKO_PRESERVE_RATIO
#error KP_GECKO_PRESERVE_RATIO defined
#endif

// --------------------------
// #ifdef IBSH_RES_MODE_XGECKO
#define LZDSHT_RESULT_BUF_LEN KP_FILESYS_RESULT_BUF_LEN
// #else
// #define LZDSHT_RESULT_BUF_LEN XMLN_RICH_BUF_LEN // former LZDSHT_RICH_BUF_LEN
// #endif

// --------------------------
#define LZDSH_MAX_NUM_OF_SEARCH_ITEMS 300
#define LZDSH_MAX_LIST_ITEM_WDT 20  /* TV_XL_HW_IX_LEN */ /* TV_XL_MAX_IX_LEN */

#if DialogLang==KP_LNG_LIT
#define LZDSH_MSG_TOO_MANY_SEARCH_RESULTS ("Rezultatø labai daug  - paieðka nutraukiama")
#elif DialogLang==KP_LNG_ENG
#define LZDSH_MSG_TOO_MANY_SEARCH_RESULTS ("Too many results - search aborted")
#endif

// -----------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_WND_MARGIN (KPW_WND_MARGIN/2+1)
#define LZDSH_WND_BORDER_WDT iWndBorderWdt // GetBorderWdt(lzdsh_dlg->m_hDialogWindow) // KPW_WND_BORDER_WDT // 1 //
#define LZDSH_WND_BORDER_COR KPW_WND_BORDER_COR
#define LZDSH_WND_CAPTION_HGT iWndCaptionHgt // GetCaptionHgt(lzdsh_dlg->m_hDialogWindow) // KPW_WND_CAPTION_HGT // windows caption height
#define LZDSH_CTRL_MARGIN (KPW_WND_MARGIN+((iWindowsVersion==WinXP)?(-1):0))
#else
#define LZDSH_WND_MARGIN 10 // 12 // 14
#define LZDSH_WND_BORDER_WDT 0
#define LZDSH_WND_BORDER_COR 2
#define LZDSH_WND_CAPTION_HGT 0
#define LZDSH_CTRL_MARGIN KPW_WND_MARGIN
#endif

#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_WND_STYLE (WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME /* | WS_VISIBLE | WS_BORDER | WS_POPUP */)
#else
#define LZDSH_WND_STYLE (WS_POPUP | WS_SYSMENU /* WS_VISIBLE */)
#endif

#if IBSH_SKIN == IBSH_SKIN_STANDART
#ifdef LZDSH_MENU
#define LZDSH_WND_MARGIN_UP 1
#else
#define LZDSH_WND_MARGIN_UP (KPW_WND_BORDER_COR+LZDSH_CTRL_MARGIN) // tarpas pries linija
#endif
#elif IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON
#define LZDSH_WND_MARGIN_UP 42 // local caption height
#else
#define LZDSH_WND_MARGIN_UP 38
#endif

#if (IBSH_SKIN == IBSH_SKIN_STANDART)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)
#define LZDSH_MENU_DY 0 // meniu vartotojo srityje nera - visas uz vartotojo srities ribu
#else
#define LZDSH_MENU_DY (LZDSH_BUT_WDT+LZDSH_CTRL_MARGIN) // meniu vartotojo srityje aukstis
#endif


// ---------------------- background
// #if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#define LZDSH_BCKGRND_X LZDSH_WND_BORDER_COR
#define LZDSH_BCKGRND_DX (lzdsh_dlg->m_iWndCurDX-2*LZDSH_WND_BORDER_COR)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#ifdef LZDSH_MENU
#define LZDSH_BCKGRND_Y 0
#define LZDSH_BCKGRND_DY (lzdsh_dlg->m_iWndCurDY-LZDSH_WND_BORDER_COR)
#else
#define LZDSH_BCKGRND_Y LZDSH_WND_BORDER_COR
#define LZDSH_BCKGRND_DY (lzdsh_dlg->m_iWndCurDY-2*LZDSH_WND_BORDER_COR)
#endif
#else
#define LZDSH_BCKGRND_Y LZDSH_WND_BORDER_COR
#define LZDSH_BCKGRND_DY (lzdsh_dlg->m_iWndCurDY-2*LZDSH_WND_BORDER_COR)
#endif
// #endif

// ----------------------- logo WinLED
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#define LZDSH_LOGO_DX 190 // 198 // 160 // 162
#define LZDSH_LOGO_DY 30 // 31
#define LZDSH_LOGO_X (lzdsh_dlg->m_iWndCurDX-2*LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-LZDSH_WND_MARGIN-LZDSH_LOGO_DX-5)
#define LZDSH_LOGO_Y 2 // 1 // (LZDSH_WND_BORDER_COR+LZDSH_CTRL_MARGIN)
#endif

// ----------------------- faked menu
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) // ||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#define LZDSH_FMENU_DX 124 // 125
#define LZDSH_FMENU_DY 17
#define LZDSH_FMENU_X (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+LZDSH_WND_MARGIN)
#define LZDSH_FMENU_Y LZDSH_BUT_EXIT_Y
#endif

// ----------------------- button menu
#define LZDSH_MENU_ITEM_HGT 18 // LZDSH_BUT_WDT

#define LZDSH_MENU_X (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+LZDSH_WND_MARGIN)
#define LZDSH_MENU_Y LZDSH_BUT_EXIT_Y

// #define LZDSH_MENU_FILE_X LZDSH_MENU_X
#define LZDSH_MENU_OPTIONS_X LZDSH_MENU_X // (LZDSH_MENU_X+LZDSH_MENU_ITEM_WDT) // +LZDSH_CTRL_MARGIN)
#define LZDSH_MENU_HELP_X (LZDSH_MENU_X + LZDSH_MENU_ITEM_WDT + LZDSH_CTRL_MARGIN*2)

#define LZDSH_MENU_ITEM_WDT 60

#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
// #define LZDSH_MENU_FILE_TXT LZDSH_MSG_DICT
#define LZDSH_MENU_OPTIONS_TXT LZDSH_MSG_OPT
#define LZDSH_MENU_HELP_TXT LZDSH_MSG_HELP
#endif

// ------------------------------- control buttons
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON
#define LZDSH_BUT_EXIT_Y   (LZDSH_WND_BORDER_COR+LZDSH_CTRL_MARGIN)
#else
#define LZDSH_BUT_EXIT_Y   (LZDSH_WND_MARGIN_UP+LZDSH_CTRL_MARGIN)
#endif
#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#define LZDSH_BUT_EXIT_X   (lzdsh_dlg->m_iWndCurDX-2*LZDSH_WND_BORDER_WDT-LZDSH_WND_BORDER_COR-LZDSH_WND_MARGIN-LZDSH_BUT_WDT-2)

#define LZDSH_BUT_MINIMIZE_X  (LZDSH_BUT_EXIT_X-LZDSH_BUT_WDT-LZDSH_BUT_MARGIN)
#define LZDSH_BUT_MINIMIZE_Y  LZDSH_BUT_EXIT_Y
#endif


// ---------------------------------
#define LZDSH_LINE_X    (0)
#define LZDSH_LINE_DX   (lzdsh_dlg->m_iWndCurDX-2*LZDSH_WND_BORDER_WDT-2*LZDSH_WND_BORDER_COR+((iWindowsVersion==WinXP)?2:0))

#define LZDSH_LINE_1_Y  (LZDSH_WND_MARGIN_UP-1)

#define LZDSH_LEFT_PART_DX 203 // 200
#define LZDSH_LEFT_PART_X  (LZDSH_WND_BORDER_COR+LZDSH_WND_MARGIN)


// ------------------------------- m_InpEdit
#define LZDSH_INP_X     LZDSH_LEFT_PART_X
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_INP_X_CREATE LZDSH_INP_X
#else
#define LZDSH_INP_X_CREATE LZDSH_INP_X+KPW_CTRL_BORDER_WDT
#endif

#define LZDSH_INP_Y     (LZDSH_WND_MARGIN_UP+LZDSH_MENU_DY+LZDSH_CTRL_MARGIN)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_INP_Y_CREATE LZDSH_INP_Y
#else
#define LZDSH_INP_Y_CREATE (LZDSH_INP_Y+KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_INP_DX    150 // LZDSH_LEFT_PART_DX //
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_INP_DX_CREATE LZDSH_INP_DX
#else
#define LZDSH_INP_DX_CREATE (LZDSH_INP_DX-2*KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_INP_DY    (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])

// ---------------------------------
#define LZDSH_LINE_2_Y  (LZDSH_INP_Y+LZDSH_INP_DY+LZDSH_CTRL_MARGIN-1)


// ---------------------------------
#define LZDSH_TAB_X     LZDSH_LEFT_PART_X

#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_TAB_Y     (LZDSH_INP_Y+LZDSH_INP_DY+2*LZDSH_CTRL_MARGIN)
#define LZDSH_TAB_DX    LZDSH_LEFT_PART_DX // (LZDSH_LEFT_PART_DX - 2*LZDSH_BUT_WDT - 2*LZDSH_BUT_MARGIN)
#define LZDSH_ONE_TAB_DX 55
#define LZDSH_TAB_DY    KPW_ICON_BUTTON_WDT // 18 // (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_TAB_NUM_OF_TABS 3

#define LZDSH_TAB_MAIN_X   LZDSH_TAB_X
#define LZDSH_TAB_SEARCH_X (LZDSH_TAB_X+LZDSH_ONE_TAB_DX)
#define LZDSH_TAB_HIST_X   (LZDSH_TAB_X+2*LZDSH_ONE_TAB_DX)

#else
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON
#define LZDSH_TAB_Y     (LZDSH_INP_Y+LZDSH_INP_DY+LZDSH_CTRL_MARGIN)
#else
#define LZDSH_TAB_Y     (LZDSH_INP_Y+LZDSH_INP_DY+LZDSH_CTRL_MARGIN)
#endif
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
#define LZDSH_TAB_DX    41
#define LZDSH_TAB_DY    19
#else
#define LZDSH_TAB_DX    51
#define LZDSH_TAB_DY    (KPW_ICON_BUTTON_WDT+1)
#endif

#define LZDSH_TAB_MAIN_X   LZDSH_TAB_X
#define LZDSH_TAB_SEARCH_X (LZDSH_TAB_X+LZDSH_TAB_DX+LZDSH_BUT_MARGIN)
#define LZDSH_TAB_HIST_X   (LZDSH_TAB_X+2*(LZDSH_TAB_DX+LZDSH_BUT_MARGIN))
#endif

#define LZDSH_TAB_MAIN_Y   LZDSH_TAB_Y
#define LZDSH_TAB_SEARCH_Y LZDSH_TAB_Y
#define LZDSH_TAB_HIST_Y   LZDSH_TAB_Y

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT)||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
#define LZDSH_TAB_EXT_X1   (LZDSH_TAB_X+3*LZDSH_TAB_DX)
#define LZDSH_TAB_EXT_X2   (LZDSH_TAB_X+LZDSH_LIST_DX)
#define LZDSH_TAB_EXT_Y    (LZDSH_TAB_Y+LZDSH_TAB_DY-1)
#endif

#define LZDSH_BUT_BACK_X      (LZDSH_BUT_FORWARD_X-LZDSH_BUT_MARGIN-LZDSH_BUT_BACK_DX)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_BUT_BACK_Y      LZDSH_TAB_Y+4
#define LZDSH_BUT_BACK_DX     KPW_SCROLLBAR_WDT
#define LZDSH_BUT_BACK_DY     KPW_SCROLLBAR_WDT
#else
#define LZDSH_BUT_BACK_Y      LZDSH_TAB_Y
#define LZDSH_BUT_BACK_DX     LZDSH_BUT_WDT
#define LZDSH_BUT_BACK_DY     LZDSH_BUT_WDT
#endif

#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_BUT_FORWARD_X   (LZDSH_TAB_X+LZDSH_LIST_DX-2-LZDSH_BUT_FORWARD_DX)
#define LZDSH_BUT_FORWARD_Y   LZDSH_TAB_Y+4
#define LZDSH_BUT_FORWARD_DX  KPW_SCROLLBAR_WDT
#define LZDSH_BUT_FORWARD_DY  KPW_SCROLLBAR_WDT
#else
#define LZDSH_BUT_FORWARD_X   (LZDSH_TAB_X+LZDSH_LIST_DX-LZDSH_BUT_FORWARD_DX)
#define LZDSH_BUT_FORWARD_Y   LZDSH_TAB_Y
#define LZDSH_BUT_FORWARD_DX  LZDSH_BUT_WDT
#define LZDSH_BUT_FORWARD_DY  LZDSH_BUT_WDT
#endif

// ------------------------------- m_MainList
// ------------------------------- m_SearchList
// ------------------------------- m_HistList
#define LZDSH_LIST_X    LZDSH_LEFT_PART_X
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_LIST_X_CREATE LZDSH_LIST_X
#else
#define LZDSH_LIST_X_CREATE (LZDSH_LIST_X+KPW_CTRL_BORDER_WDT)
#endif

#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT
#define LZDSH_LIST_Y    (LZDSH_TAB_Y+LZDSH_TAB_DY-2)
#elif IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
#define LZDSH_LIST_Y    (LZDSH_TAB_Y+LZDSH_TAB_DY+LZDSH_CTRL_MARGIN-2)
#else
#define LZDSH_LIST_Y    (LZDSH_TAB_Y+LZDSH_TAB_DY)
#endif
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_LIST_Y_CREATE LZDSH_LIST_Y
#else
#define LZDSH_LIST_Y_CREATE (LZDSH_LIST_Y+KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_LIST_DX   LZDSH_LEFT_PART_DX
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_LIST_DX_CREATE LZDSH_LIST_DX
#else
#define LZDSH_LIST_DX_CREATE (LZDSH_LIST_DX-2*KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_LIST_NUM_LINES 16
#define LZDSH_LIST_DY_MAIN      (LZDSH_LIST_NUM_LINES * iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_LIST_DY_DYN_MAIN  (lzdsh_dlg->m_iNumOfLines * iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#ifdef KP_LISTBOX
#define LZDSH_LIST_DY      (LZDSH_LIST_DY_MAIN     + 2 * KPW_CTRL_BORDER_WDT)
#define LZDSH_LIST_DY_DYN  (LZDSH_LIST_DY_DYN_MAIN + 2 * KPW_CTRL_BORDER_WDT)
#else
#define LZDSH_LIST_DY      LZDSH_LIST_DY_MAIN
#define LZDSH_LIST_DY_DYN  LZDSH_LIST_DY_DYN_MAIN
#endif
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_LIST_DY_DYN_CREATE LZDSH_LIST_DY_DYN
#else
#define LZDSH_LIST_DY_DYN_CREATE (LZDSH_LIST_DY_DYN - 2 * KPW_CTRL_BORDER_WDT)
#endif


// ------------------------------- m_TagList
#ifdef LZDSH_EDITOR_BUILD

#define LZDSH_TAGLIST_X    LZDSH_LEFT_PART_X
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_TAGLIST_X_CREATE LZDSH_TAGLIST_X
#else
#define LZDSH_TAGLIST_X_CREATE (LZDSH_TAGLIST_X+KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_TAGLIST_Y_DYN_CREATE (LZDSH_LIST_Y_CREATE + LZDSH_LIST_DY_DYN_CREATE + KPW_CTRL_BORDER_WDT)

#define LZDSH_TAGLIST_DX_DYN_CREATE (LZDSH_LIST_DX_CREATE + KPW_CTRL_BORDER_WDT + LZDSH_RES_DX_DYN_CREATE)

#define LZDSH_TAGLIST_NUM_LINES 10
#define LZDSH_TAGLIST_DY_CREATE (LZDSH_TAGLIST_NUM_LINES*iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_TAGLIST_DY LZDSH_TAGLIST_DY_CREATE
#define LZDSH_TAGLIST_DY_DYN LZDSH_TAGLIST_DY_CREATE

#define LZDSH_TAGLIST_DY_FULL (KPW_CTRL_BORDER_WDT + LZDSH_TAGLIST_DY) // pilnas aukstis su tarpeliu po LZDSH_LIST
#define LZDSH_TAGLIST_DY_FULL_DYN (KPW_CTRL_BORDER_WDT + LZDSH_TAGLIST_DY_DYN)

#define LZDSH_MAX_NUM_OF_EDIT_TAGS 300
#define LZDSH_MAX_EDIT_TAG_WDT 200

#else

#define LZDSH_TAGLIST_DY_FULL 0
#define LZDSH_TAGLIST_DY_FULL_DYN 0

#endif



// ------------------------------- toolbar buttons
#define LZDSH_BUT_Y           LZDSH_INP_Y
#define LZDSH_BUT_X           (LZDSH_INP_X+LZDSH_INP_DX+LZDSH_CTRL_MARGIN)
#if IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D
#define LZDSH_BUT_WDT         20
#define LZDSH_BUT_MARGIN      2
#define LZDSH_BUT_Y_REAL      LZDSH_BUT_Y+1
#else
#define LZDSH_BUT_WDT         KPW_ICON_BUTTON_WDT
#define LZDSH_BUT_MARGIN      0
#define LZDSH_BUT_Y_REAL      LZDSH_BUT_Y
#endif
#define LZDSH_TXT_BUT_WDT     60
#define LZDSH_TXT_BUT_HGT     KPW_ICON_BUTTON_WDT

#define LZDSH_BUT_SEARCH_X    LZDSH_BUT_X
#define LZDSH_BUT_SEARCH_Y    LZDSH_BUT_Y_REAL
// #if IBSH_SKIN == IBSH_SKIN_STANDART
// #define LZDSH_BUT_SEARCH_DX   KPW_ICON_BUTTON_WDT
// #else
#define LZDSH_BUT_SEARCH_DX   28
// #endif

#define LZDSH_BUT_FONT_ZOOM_X (LZDSH_BUT_X+LZDSH_BUT_SEARCH_DX+LZDSH_BUT_MARGIN)
#define LZDSH_BUT_FONT_ZOOM_Y LZDSH_BUT_Y_REAL

#define LZDSH_BUT_NARROW_X    (LZDSH_BUT_X+LZDSH_BUT_SEARCH_DX+LZDSH_BUT_MARGIN+LZDSH_BUT_WDT+LZDSH_BUT_MARGIN)
#define LZDSH_BUT_NARROW_Y    LZDSH_BUT_Y_REAL

#define LZDSH_BUT_ACCENTS_X   (LZDSH_BUT_X+LZDSH_BUT_SEARCH_DX+LZDSH_BUT_MARGIN+2*(LZDSH_BUT_WDT+LZDSH_BUT_MARGIN))
#define LZDSH_BUT_ACCENTS_Y   LZDSH_BUT_Y_REAL


// ------------------------------- combo box of dictionaries
#define LZDSH_DICT_BOX_X      (LZDSH_BUT_X+LZDSH_BUT_SEARCH_DX+LZDSH_BUT_MARGIN+2*(LZDSH_BUT_WDT+LZDSH_BUT_MARGIN)+LZDSH_BUT_WDT+LZDSH_CTRL_MARGIN)
#define LZDSH_DICT_BOX_Y      LZDSH_BUT_Y
#define LZDSH_DICT_BOX_DX     (LZDSH_WND_DX-2*LZDSH_WND_BORDER_WDT-LZDSH_DICT_BOX_X-LZDSH_NODLIST_DX_FULL-LZDSH_WND_MARGIN) // -LZDSH_WND_BORDER_COR)
#define LZDSH_DICT_BOX_DY     (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])


// ------------------------------- m_ResRichEdit
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RES_MARGIN (LZDSH_CTRL_MARGIN-2) // LZDSH_CTRL_MARGIN // = (KPW_WND_MARGIN+((iWindowsVersion==WinXP)?(-1):0))
#else
// #define LZDSH_RES_MARGIN 8
#define LZDSH_RES_MARGIN (KPW_WND_MARGIN+((iWindowsVersion==WinXP)?(-2):0)-1)
#endif

// Rezultato lauko koordinatës (be rëmelio)?
#ifdef LZDSH_TEST_REZ_BMP
#define LZDSH_PICT_X    (LZDSH_LEFT_PART_X + LZDSH_LEFT_PART_DX + LZDSH_RES_MARGIN)
#define LZDSH_RES_X     (LZDSH_PICT_X + LZDSH_RES_DX_REAL + LZDSH_RES_MARGIN)
#else
#define LZDSH_RES_X     (LZDSH_LEFT_PART_X + LZDSH_LEFT_PART_DX + LZDSH_RES_MARGIN)
#endif

// Rezultato lauko rëmelio koordinatës?
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RES_X_CREATE LZDSH_RES_X
#else
#define LZDSH_RES_X_CREATE (LZDSH_RES_X + KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_WND_SOFT_CAPTION_HGT (LZDSH_WND_MARGIN_UP+LZDSH_MENU_DY+LZDSH_CTRL_MARGIN+LZDSH_INP_DY)

// Rezultato lauko koordinatës (be rëmelio)
#define LZDSH_RES_Y_MAIN (LZDSH_WND_SOFT_CAPTION_HGT + LZDSH_CTRL_MARGIN) // (LZDSH_WND_MARGIN_UP+LZDSH_MENU_DY+LZDSH_CTRL_MARGIN+LZDSH_INP_DY+LZDSH_CTRL_MARGIN)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RES_Y     (LZDSH_RES_Y_MAIN+5)
#else
#define LZDSH_RES_Y     LZDSH_RES_Y_MAIN
#endif

// Rezultato lauko rëmelio koordinatës?
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RES_Y_CREATE LZDSH_RES_Y
#else
#define LZDSH_RES_Y_CREATE (LZDSH_RES_Y+KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_RES_DX 260
// Rezultato lauko rëmelio koordinatës
#define LZDSH_RES_DX_DYN   (lzdsh_dlg->m_iWndCurDX - (LZDSH_WND_DX - LZDSH_RES_DX) + 0) // ((iWindowsVersion==WinXP)?(-2):0))

// Rezultato lauko koordinatës (be rëmelio)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RES_DX_DYN_CREATE LZDSH_RES_DX_DYN
#else
#define LZDSH_RES_DX_DYN_CREATE (LZDSH_RES_DX_DYN - 2 * KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_RES_DY_MAIN (LZDSH_WND_DY - \
                           (LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + LZDSH_WND_DY_COR)- \
                           LZDSH_RES_Y - \
                           LZDSH_TAGLIST_DY_FULL - \
                           (LZDSH_WND_MARGIN+LZDSH_WND_BORDER_COR)- \
                           LZDSH_WND_BORDER_WDT)

#define LZDSH_RES_DY    LZDSH_RES_DY_MAIN
// Rezultato lauko rëmelio koordinatës?
#define LZDSH_RES_DY_DYN   (lzdsh_dlg->m_iWndCurDY - (LZDSH_WND_DY - LZDSH_RES_DY))

// Rezultato lauko koordinatës (be rëmelio)?
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RES_DY_DYN_CREATE LZDSH_RES_DY_DYN
#else
#define LZDSH_RES_DY_DYN_CREATE (LZDSH_RES_DY_DYN - 2 * KPW_CTRL_BORDER_WDT)
#endif


// ------------------------------- m_ResRichTest
#ifdef LZDSH_EDITOR_BUILD

#define LZDSH_RTF_TEST_X_DYN   (LZDSH_NODLIST_X_DYN_CREATE - KPW_CTRL_BORDER_WDT)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RTF_TEST_X_DYN_CREATE LZDSH_RTF_TEST_X_DYN
#else
#define LZDSH_RTF_TEST_X_DYN_CREATE (LZDSH_RTF_TEST_X_DYN + KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_RTF_TEST_Y_DYN (LZDSH_TAGLIST_Y_DYN_CREATE - KPW_CTRL_BORDER_WDT)
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_RTF_TEST_Y_DYN_CREATE LZDSH_RTF_TEST_Y_DYN
#else
#define LZDSH_RTF_TEST_Y_DYN_CREATE (LZDSH_RTF_TEST_Y_DYN + KPW_CTRL_BORDER_WDT)
#endif

#define LZDSH_RTF_TEST_DX LZDSH_NODLIST_DX_CREATE

#define LZDSH_RTF_TEST_DY LZDSH_TAGLIST_DY_FULL

#endif

// ------------------------------- m_NodList
#ifdef LZDSH_EDITOR_BUILD

#define LZDSH_NODLIST_X_DYN_CREATE (LZDSH_RES_X_CREATE + LZDSH_RES_DX_DYN_CREATE + KPW_CTRL_BORDER_WDT)

#define LZDSH_NODLIST_Y_CREATE LZDSH_RES_Y_CREATE

#define LZDSH_NODLIST_DX_CREATE 200
#define LZDSH_NODLIST_DX   LZDSH_NODLIST_DX_CREATE

#define LZDSH_NODLIST_DX_FULL (KPW_CTRL_BORDER_WDT + LZDSH_NODLIST_DX) // pilnas plotis su tarpeliu po LZDSH_RES
#define LZDSH_NODLIST_DX_FULL_DYN (KPW_CTRL_BORDER_WDT + LZDSH_NODLIST_DX_DYN)

#define LZDSH_NODLIST_NUM_LINES (LZDSH_LIST_NUM_LINES + 1)
#define LZDSH_NODLIST_DY_DYN_CREATE (LZDSH_LIST_DY_DYN_CREATE + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])

#define LZDSH_MAX_NUM_OF_EDIT_NODES 300
#define LZDSH_MAX_EDIT_NODE_WDT 100

#else

#define LZDSH_NODLIST_DX_FULL 0
#define LZDSH_NODLIST_DX_FULL_DYN 0

#endif


// --------------- viso lango matmenys
#define LZDSH_WND_X 100
#define LZDSH_WND_Y 100

#define LZDSH_WND_DX_COR 0 // ((iWindowsVersion==WinXP)?(-4):0)
#ifdef LZDSH_TEST_REZ_BMP
#define LZDSH_WND_DX (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+LZDSH_WND_MARGIN+LZDSH_LIST_DX+LZDSH_RES_MARGIN+LZDSH_RES_DX+LZDSH_NODLIST_DX_FULL+LZDSH_RES_MARGIN+LZDSH_RES_DX_REAL+LZDSH_WND_MARGIN+LZDSH_WND_BORDER_COR+LZDSH_WND_BORDER_WDT)
#else
#define LZDSH_WND_DX (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+LZDSH_WND_MARGIN+LZDSH_LIST_DX+LZDSH_RES_MARGIN+LZDSH_RES_DX+LZDSH_NODLIST_DX_FULL+LZDSH_WND_MARGIN+LZDSH_WND_BORDER_COR+LZDSH_WND_BORDER_WDT+LZDSH_WND_DX_COR)
#endif
#define LZDSH_WND_DX_MIN LZDSH_WND_DX
#define LZDSH_WND_DX_MAX (1200+LZDSH_WND_BORDER_WDT*2+LZDSH_WND_BORDER_COR*2)

#if IBSH_SKIN == IBSH_SKIN_STANDART
#ifdef LZDSH_MENU
#define LZDSH_WND_DY_COR  iWndMenuHgt // KPW_WND_MENU_HGT
#else
#define LZDSH_WND_DY_COR 0 // ((iWindowsVersion==WinXP)?5:0)
#endif
#else
#define LZDSH_WND_DY_COR 0
#endif

#define LZDSH_WND_DY_MAIN (LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + LZDSH_WND_DY_COR + \
                           LZDSH_LIST_Y + \
                           LZDSH_LIST_DY + \
                           LZDSH_TAGLIST_DY_FULL + \
                           LZDSH_WND_MARGIN + LZDSH_WND_BORDER_COR + \
                           LZDSH_WND_BORDER_WDT)
#define LZDSH_WND_DY_DYN_MAIN (LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + LZDSH_WND_DY_COR + \
                           LZDSH_LIST_Y + \
                           LZDSH_LIST_DY_DYN + \
                           LZDSH_TAGLIST_DY_FULL_DYN + \
                           LZDSH_WND_MARGIN + LZDSH_WND_BORDER_COR + \
                           LZDSH_WND_BORDER_WDT)
#define LZDSH_WND_DY LZDSH_WND_DY_MAIN
#define LZDSH_WND_DY_DYN LZDSH_WND_DY_DYN_MAIN
#define LZDSH_WND_DY_MIN (200 + LZDSH_TAGLIST_DY_FULL)
#define LZDSH_WND_DY_MAX (711+LZDSH_WND_BORDER_WDT*2+LZDSH_WND_BORDER_COR*2)

#define LZDSH_GRID 10

// ---------------- tampymo laukas
#define LZDSH_RESIZE_WDT 10
#define LZDSH_RESIZE_WDT_SENS 20

// ----------------
#define LZDSH_ID_FONT_ZOOM    131
#define LZDSH_ID_NARROW       132
#define LZDSH_ID_ACCENTS      133
#define LZDSH_ID_SEARCH       134

#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_ID_MAIN_TAB     0
#define LZDSH_ID_SEARCH_TAB   1
#define LZDSH_ID_HIST_TAB     2
#else
#define LZDSH_ID_MAIN_TAB     135
#define LZDSH_ID_SEARCH_TAB   136
#define LZDSH_ID_HIST_TAB     137
#endif

#ifdef IBSH_RES_MODE_XGECKO
#define LZDSH_ID_BACK         138
#define LZDSH_ID_FORWARD      139
#endif

#define LZDSH_ID_GUIDE        140

// -----------------------------
#if DialogLang==KP_LNG_LIT
// #define LZDSH_MSG_DICT  ((const unsigned char *)"Þodynas")
#define LZDSH_MSG_OPT   ((const unsigned char *)"Parinktys")
// #define LZDSH_MSG_OPEN  ((const unsigned char *)"Atverti")
// #define LZDSH_MSG_EXIT  ((const unsigned char *)"Baigti")
#define LZDSH_MSG_HELP  ((const unsigned char *)"Pagalba")
#endif
#if DialogLang==KP_LNG_ENG
// #define LZDSH_MSG_DICT  ((const unsigned char *)"Dictionary")
#define LZDSH_MSG_OPT   ((const unsigned char *)"Options")
// #define LZDSH_MSG_OPEN  ((const unsigned char *)"Open")
// #define LZDSH_MSG_EXIT  ((const unsigned char *)"Exit")
#define LZDSH_MSG_HELP  ((const unsigned char *)"Help")
#endif

// ---------------------------------
#ifdef KP_USE_WXWIDGETS
class LzdShFrame_tag : public wxFrame
{
public:
   LzdShFrame_tag(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE /* wxDEFAULT_DIALOG_STYLE */, const wxString& name = "dialogBox")
      : wxFrame(parent, id, title, pos, size, style, name) {};

   void OnExit(wxCommandEvent& event);
   void LzdShDialogProc(wxCommandEvent& event);

   DECLARE_EVENT_TABLE()
};
#endif


// -----------------------------
struct DictListEntry
{
   unsigned char m_lpszDictName[KP_MAX_FILE_LIN_WDT + 1];
   unsigned char m_lpszFileName[KP_MAX_FNAME_LEN + 1]; // tik failo vardas be tipo
   int iLanguage; // pagrindines kalbos rusiavimo tipas
};

// -----------------------------
class LzdShDlg
#if TRUE // FALSE
#  ifdef IBSH_RES_MODE_XGECKO
#     if CompilerGr==Mingw
: public KpGeckoDialog
#     else
: public KpPubDlg
#     endif
#  else
#     ifdef IBSH_RES_MODE_MSHTML
: public KpMsHtmlDlg
#     else
#        ifdef IBSH_RES_MODE_RTF
: public KpRtfDlg
#        else
: public KpPubDlg
#        endif
#     endif
#  endif
#else
: public iBshDlg
#endif
{
   HINSTANCE m_hInstance;

public:
#ifdef KP_USE_WXWIDGETS
// volatile LzdShFrame_tag *m_hDialogWindow;
#else
// volatile HWND m_hDialogWindow; // iðkeltas á KpPubDlg // KpGeckoDialog
#endif

#if FALSE // iðkelti á KpPubDlg
   int m_iWndCurX;
   int m_iWndCurY;
   int m_iWndCurDX;
   int m_iWndCurDY;
   int m_iWndCurDXprec;
   int m_iWndCurDYprec;
#endif

#ifdef LZDSH_EDITOR_BUILD
#ifdef KP_USE_WXWIDGETS
// wxListBox *m_pNodList;
// wxSizer *m_pNodListSizer;

   wxWindow *m_pNodList;
#else
   /* volatile */ HWND m_NodList;
#endif

   /* volatile */ HWND m_TagList;
   /* volatile */ KpWnd * /* HWND */ m_TagEditCtrl;
   bool m_bTagEditChanged; // saugo tago pasikeitimo pozymi po m_ResRichEdit refreshinimo iki lizdo headeriu refreshinimo

   int m_iCurEditSel;
// unsigned char m_TagEditFontName[LF_FACESIZE+1];
/* CHARFORMAT */ CHARFORMATW m_TagEditFontFmt;
#endif

// -----------------------------
// iðkeltas á KpPubDlg
#if FALSE
#ifdef IBSH_RES_MODE_RTF
   /* volatile */ HWND m_ResRichEdit;
#  ifdef LZDSH_EDITOR_BUILD
#     ifdef Debug
// HWND m_ResRichTest;
#     endif
#  endif
#endif
#endif

// -----------------------------
#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   HTMLWindow *m_ResHtml;
#  endif
#endif

#if FALSE // ifndef IBSH_RES_MODE_XGECKO
#  ifdef IBSH_RES_MODE_RTF
private:
   unsigned char
#  else
#     ifdef LZDSH_RES_CODING_UTF8
   unsigned char
#     else
   UniChar
#     endif
#  endif                      // atkeltas ið LzdShSearch
      m_pResBuf[LZDSHT_RESULT_BUF_LEN+1]; // former LzdShSearch::m_lpszResultFormatted
                              // search result converted to RTF or HTML, former m_lpszResultRtfText
#endif                        // IBSH_RES_MODE_XGECKO tikrinti dar ir (m_pResBuf != NULL), nes ten dinaminis

public:
   HMENU m_Menu;

// HMENU m_DictMenu;

#if (IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_LIGHT) // ||(IBSH_SKIN == IBSH_SKIN_LZDSH_MAHAGON_3D)
   HBITMAP m_hFMenuBmp;
   HDC m_hdcFMenu;
#endif

#if IBSH_SKIN != IBSH_SKIN_STANDART
// HPEN m_aPenScheme[KpNumOfShadows0];
#endif
// HPEN m_aPenSchemeToolTip[KpNumOfShadows0];

   int m_iNumOfListEntries;

#ifdef LZDSHT_DIFF_KWDS
#ifdef LZDSHT_FULL_LIST
   unsigned char (*m_lpszaListKeywords)[TV_XL_MAX_IX_LEN+1];
#else
   volatile unsigned char m_lpszaListKeywords[LZDSH_LIST_NUM_LINES][TV_XL_MAX_IX_LEN+1];
#endif
#endif
// volatile unsigned char m_lpszaListTexts[LZDSH_LIST_NUM_LINES][TV_XL_MAX_IX_LEN+1];

   bool m_bShiftFl; // keyboard shift key pressed, used for backward tab jumping

#if FALSE // iðkelti á KpPubDlg
   bool m_bLButPressed; // left mouse button pressed flag // formerly used for draging
   int m_iMouseX;
   int m_iMouseY;
   bool m_bCaptured;
   bool m_bResizing;
#endif

// int m_RedrawTimer; // iðkeltas á KpGeckoDialog
// bool m_bDoRedraw;  // iðkeltas á KpGeckoDialog

// ----------------
   LzdShDlg(KpFileSys *pKpFileSys);
   ~LzdShDlg();

   virtual HRESULT InitDisplay(void); // konstruktoriaus tæsinys
   virtual HRESULT FinitDisplay(void); // destruktoriaus pradþia
   virtual HRESULT InitThreadDisplay(void); // konstruktoriaus tæsinys, iðkvieèiamas tam threade, kuriame po to bus rodomas vaizdas
   virtual HRESULT FinitThreadDisplay(void); // destruktoriaus pradþia, iðkvieèiama tam threade, kuriame buvo iðkviestas InitThreadDisplay()

   virtual HRESULT InitDictList(void);
   HRESULT GetCurDictName(void);
   virtual HRESULT ChangeDict(int iDictEntry, bool bCheckFileExist, bool bPostPone = False);
                                                               // iDictEntry - þodyno indeksas liste, nauja m_iCurDictEntry reikðmë
                                                               // jei nerado - KP_E_OBJ_NOT_FOUND, praneðimø neiðveda
                                                               // bCheckFileExist - parametras LzdShSearch::CloseFiles()
                                                               // bPostPone == True – m_DictBox neselektina, SetComboBoxSel() nukelia á WM_TIMER m_RedrawTimer po m_iDiagOnTopCnt kartu su BringToTop()
                                                               //    dël iððokanèio komboboxo ekrano kampe nepadeda
   virtual HRESULT ChangeDict(const unsigned char *lpszDictName, bool bCheckFileExist, bool bPostPone = False);
                                                               // lpszDictName - þodyno failo vardas,
                                                               // DictListEntry::m_lpszFileName, m_lpszCurDictName
                                                               // jei nerado - KP_E_KWD_NOT_FOUND arba KP_E_OBJ_NOT_FOUND, praneðimø neiðveda
                                                               // bCheckFileExist - parametras LzdShSearch::CloseFiles()
                                                               // bPostPone == True – SetComboBoxSel() nukelia á WM_TIMER m_RedrawTimer po m_iDiagOnTopCnt
   HRESULT SaveCurDict(void); // iðsaugoja selektintà þodynà á registrà

   HRESULT RestoreSavedCoords(void);

   virtual HRESULT OpenWindow(HINSTANCE hInst, bool bShowWindow = True); // sukuria ir atidaro dialogo langa

   HRESULT UpdateList(long lOffset);
   virtual HRESULT SelectList(long lOffset); // isijungia lzdsh_search->m_bSemBlocked semafora
   virtual HRESULT GetCurListSel(/* HWND hListCtrl, */ int iToHistListFlags); // perraso listo lzdsh_dlg->m_CurList teksta i lzdsh_search->m_lpszToSearch
                                               // iToHistListFlags - nustato lzdsh_search->m_iToHistListFlags

   int /* HRESULT */ DoEdit(void); // sukuria ir atidaro dialogo langa, perima pranesimu apdorojima

   virtual HRESULT ProcessInput(int iToHistListFlags); // DoEdit() paprogramë, iðkvieèiama po m_InpEdit pasikeitimo
                                               // iToHistListFlags - nustato lzdsh_search->m_iToHistListFlags

   virtual HRESULT SetEditControlText(const unsigned char *lpszInStr); // sets value of m_InpEdit
#ifdef LZDSH_EDITOR_BUILD
   HRESULT SaveTagBeingEdited(bool bSetHeadings, bool bDestroyEditCtrl);
                                                   // issaugoja redaguojama taga lzdsh_dlg->m_TagEditCtrl ir
                                                   //    refreshina m_ResRichEdit
                                                   // bSetHeadings = True - dar ir atnaujina einamojo lizdo
                                                   //    antrastes m_NodList'ui ir m_TagList'ui
                                                   // bDestroyEditCtrl = True - gale sunaikina m_TagEditCtrl
   HRESULT RefreshCurNodeHeads(void); // funkcija iskvieciama is theSearchThread reaguojant i WM_LZDSH_SET_TAG_HEADINGS_CURRENT
#endif

   HRESULT Resize(void); // pakeicia lauku dydzius pagal atnaujintus lzdsh_dlg->m_iWndCurDXprec, lzdsh_dlg->m_iWndCurDYprec // paliekam èia // iðkelta á KpGeckoDialog
// HRESULT CompleteResize(void); // KpGeckoDialog::Resize() uþbaigimas

   HRESULT CompleteDrag(void); // KpPubDialogProc() WM_EXITSIZEMOVE uþbaigimas

   HRESULT RedrawWindow(void); // perpaiso langa
#if TRUE // #ifdef IBSH_RES_MODE_XGECKO
   virtual HRESULT RefreshResCtrl(void); // perpaiðo m_pResCtrl
#endif

   virtual HRESULT GetOnTop(bool *pbAlwaysOnTop);
   virtual HRESULT BringToTop(bool bAlwaysOnTop);
};

extern HRESULT LzdshAppendStrToList(HWND hwndListBox, const unsigned char *lpszInStr);

// extern HRESULT KpCreateLzdshListBox(HINSTANCE hInst, HWND hParent, HWND *phListControl, const unsigned char *lpszText, int iWdt, int iHgt, int iPosX, int iPosY, ControlStyles iCtrlStyle, DWORD dwExStyle, DWORD dwStyle, RecListEntry *pEntryes, int iInitSel);
#define KpCreateLzdshListBox KpCreateListBox

extern BOOL CALLBACK LzdShDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// extern LzdShDlg theDialog;
// #define pDialogPtr ((LzdShDlg *)KpGeckoDialogPtr)
// #define pDialogPtr ((LzdShDlg *)KpPubDlgPtr)
// #define theDialog (*pDialogPtr)
// extern LzdShDlg *pDialogPtr;
// #define pDialogPtr (theKpStAppPtr->m_pGrpKpPubDlg)

// lzdsh_dlg inicializavimas
#define LZDSH_DLG_PTR_INIT \
   KP_ASSERT(theKpStAppPtr != NULL, E_POINTER, null, True); \
KpPubDlg *lzdsh_dlg = NULL; \
   if(SUCCEEDED(retc)) lzdsh_dlg = theKpStAppPtr->m_pGrpKpPubDlg; \
   KP_ASSERT(lzdsh_dlg != NULL, E_POINTER, null, True);


#ifdef Debug
extern int iDictBoxStep;
#endif

#ifdef Debug
#ifdef KP_USE_WXWIDGETS
// extern wxDialog *pTestWindow;
// extern wxDialog TestWindow;
#endif
#endif

#endif
