// -----------------------------------------
// lzdshh.h
// zodyno perziuros programa
// pagalbos dialogas
//

#ifndef lzdshh_included
#define lzdshh_included


// -------------------------------------
#ifndef lzdshn_included
#error lzdshn.h not included
#endif

#ifndef lzdsh_included
#error lzdsh.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// -----------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_HELP_WND_MARGIN_UP 0
#else
#define LZDSH_HELP_WND_MARGIN_UP 25 // KPW_WND_CAPTION_HGT // local caption height
#endif

#define LZDSH_HELP_WND_MARGIN  20 // LZDSH_WND_MARGIN
#define LZDSH_HELP_CTRL_MARGIN KPW_CTRL_MARGIN // LZDSH_WND_MARGIN
#define LZDSH_HELP_GRP_MARGIN  20 // LZDSH_HELP_CTRL_MARGIN

#define LZDSH_HELP_WND_TXT  (/* (const unsigned char *) */"Pagalba")

#if IBSH_SKIN != IBSH_SKIN_STANDART
#define LZDSH_HELP_CAPT_TXT_X (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+LZDSH_HELP_WND_MARGIN)
#define LZDSH_HELP_CAPT_TXT_Y (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+1)

#define LZDSH_HELP_BUT_EXIT_X (LZDSH_HELP_WND_DX-LZDSH_WND_BORDER_WDT*2-LZDSH_WND_BORDER_COR*2-LZDSH_BUT_WDT-1)
#define LZDSH_HELP_BUT_EXIT_Y (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+2)
#endif

// -----------------------------
#define LZDSH_GUIDE_BUT_X     (LZDSH_WND_BORDER_COR + LZDSH_HELP_WND_MARGIN)
#define LZDSH_GUIDE_BUT_Y     (LZDSH_HELP_WND_MARGIN_UP + LZDSH_HELP_WND_MARGIN)
#define LZDSH_GUIDE_BUT_WDT   150
#define LZDSH_GUIDE_BUT_HGT   (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_GUIDE_TXT       ((const unsigned char *)"Vartotojo vadovas")
#define LZDSH_GUIDE_MARGIN    LZDSH_HELP_GRP_MARGIN

// -----------------------------
#define LZDSH_ABOUT_BUT_X     (LZDSH_WND_BORDER_COR + LZDSH_HELP_WND_MARGIN)
#define LZDSH_ABOUT_BUT_Y     (LZDSH_HELP_WND_MARGIN_UP + LZDSH_HELP_WND_MARGIN + \
                                 LZDSH_GUIDE_BUT_HGT + LZDSH_GUIDE_MARGIN)
#define LZDSH_ABOUT_BUT_WDT   150
#define LZDSH_ABOUT_BUT_HGT   (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_ABOUT_TXT       ((const unsigned char *)"Versija")
#define LZDSH_ABOUT_MARGIN    LZDSH_HELP_GRP_MARGIN // LZDSH_HELP_CTRL_MARGIN

// -----------------------------
#define LZDSH_UPD_BUT_WDT     100
#define LZDSH_UPD_BUT_HGT     (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
// #define LZDSH_UPD_BUT_X       (LZDSH_WND_BORDER_COR + LZDSH_HELP_WND_MARGIN)
#define LZDSH_UPD_BUT_X       (LZDSH_WND_BORDER_COR + LZDSH_HELP_WND_DX/2 - LZDSH_UPD_BUT_WDT/2)
#define LZDSH_UPD_BUT_Y       (LZDSH_HELP_WND_MARGIN_UP + LZDSH_HELP_WND_MARGIN + \
                                 LZDSH_GUIDE_BUT_HGT + LZDSH_GUIDE_MARGIN + \
                                 LZDSH_ABOUT_BUT_HGT + LZDSH_ABOUT_MARGIN)
#define LZDSH_UPD_BUT_TXT     ((const unsigned char *)"Tikrinti versijà")

// -----------------------------
#define LZDSH_HELP_WND_X (lzdsh_dlg->m_iWndCurX + LZDSH_MENU_HELP_X + 20)
#define LZDSH_HELP_WND_Y (lzdsh_dlg->m_iWndCurY + LZDSH_MENU_Y + LZDSH_MENU_ITEM_HGT + LZDSH_CTRL_MARGIN)

#define LZDSH_HELP_WND_DX (LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR + \
                              LZDSH_HELP_WND_MARGIN + LZDSH_GUIDE_BUT_WDT + LZDSH_HELP_WND_MARGIN + \
                              LZDSH_WND_BORDER_COR + LZDSH_WND_BORDER_WDT)
#define LZDSH_HELP_WND_DY (LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + \
                              LZDSH_HELP_WND_MARGIN_UP + LZDSH_HELP_WND_MARGIN + \
                              LZDSH_GUIDE_BUT_HGT + LZDSH_GUIDE_MARGIN + \
                              LZDSH_ABOUT_BUT_HGT + LZDSH_ABOUT_MARGIN + \
                              LZDSH_UPD_BUT_HGT + \
                              LZDSH_HELP_WND_MARGIN + LZDSH_WND_BORDER_COR + LZDSH_WND_BORDER_WDT)

// ------------------------------ linijos
#define LZDSH_HELP_LINE_X      (0)
#define LZDSH_HELP_LINE_DX     (LZDSH_HELP_WND_DX - 2*(LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR))
#define LZDSH_HELP_LINE_1_Y    (LZDSH_GUIDE_BUT_Y - LZDSH_HELP_GRP_MARGIN/2)
#define LZDSH_HELP_LINE_2_Y    (LZDSH_ABOUT_BUT_Y - LZDSH_HELP_GRP_MARGIN/2)
#define LZDSH_HELP_LINE_3_Y    (LZDSH_UPD_BUT_Y + LZDSH_UPD_BUT_HGT + LZDSH_HELP_GRP_MARGIN/2)


// -----------------------------
class LzdShHelpDlg
{
   HRESULT m_lhOpenResult;

   HINSTANCE m_hInstance;

public:
   HWND m_hDialogWindow;
   bool m_bWindowOpen;

   int m_iWndCurX;
   int m_iWndCurY;

   HWND m_GuideButton;
   HWND m_AboutButton;

   HWND m_UpdButton;

// bool m_bLButPressed; // left mouse button pressed flag, used for draging
   int m_iMouseX;
   int m_iMouseY;
   bool m_bCaptured;

   HWND m_ButExit;

   LzdShHelpDlg(void);
   HRESULT GetOpenResult(void){ return(m_lhOpenResult); }

   HRESULT OpenWindow(HINSTANCE hInst); // sukuria ir atidaro dialogo langa
};

extern BOOL CALLBACK LzdShHelpDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// extern LzdShHelpDlg theHelpDialog;
extern LzdShHelpDlg *pHelpDialog;
#define theHelpDialog (*pHelpDialog)

#endif
