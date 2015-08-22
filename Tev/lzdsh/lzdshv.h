// -----------------------------------------
// lzdshv.h
// zodyno perziuros programa
// versijos (About) langelis
//

#ifndef lzdshv_included
#define lzdshv_included

// --------------------------------
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
#define LZDSH_ABOUT_WND_MARGIN_UP 0
#else
#define LZDSH_ABOUT_WND_MARGIN_UP 25 // KPW_WND_CAPTION_HGT // local caption height
#endif

#define LZDSH_ABOUT_WND_MARGIN  20 // LZDSH_WND_MARGIN
#define LZDSH_ABOUT_CTRL_MARGIN KPW_CTRL_MARGIN // LZDSH_WND_MARGIN
#define LZDSH_ABOUT_GRP_MARGIN  20 // LZDSH_ABOUT_CTRL_MARGIN

#define LZDSH_ABOUT_WND_TXT  (/* (const unsigned char *) */"Versija")

#if IBSH_SKIN != IBSH_SKIN_STANDART
#define LZDSH_ABOUT_CAPT_TXT_X (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+LZDSH_ABOUT_WND_MARGIN)
#define LZDSH_ABOUT_CAPT_TXT_Y (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+1)

#define LZDSH_ABOUT_BUT_EXIT_X (LZDSH_ABOUT_WND_DX-LZDSH_WND_BORDER_WDT*2-LZDSH_WND_BORDER_COR*2-LZDSH_BUT_WDT-1)
#define LZDSH_ABOUT_BUT_EXIT_Y (LZDSH_WND_BORDER_WDT+LZDSH_WND_BORDER_COR+2)
#endif

// -----------------------------
#define LZDSH_VERSION_X       (LZDSH_WND_BORDER_COR + LZDSH_ABOUT_WND_MARGIN)
#define LZDSH_VERSION_Y       (LZDSH_ABOUT_WND_MARGIN_UP + LZDSH_ABOUT_WND_MARGIN)
#define LZDSH_VERSION_DX      150
#define LZDSH_VERSION_DY      (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_VERSION_MARGIN  LZDSH_VERSION_GRP_MARGIN

// -----------------------------
#define LZDSH_ABOUT_WND_X (lzdsh_dlg->m_iWndCurX + 100)
#define LZDSH_ABOUT_WND_Y (lzdsh_dlg->m_iWndCurY + 100)

#define LZDSH_ABOUT_WND_DX (LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR + \
                              LZDSH_ABOUT_WND_MARGIN + LZDSH_VERSION_DX + LZDSH_ABOUT_WND_MARGIN + \
                              LZDSH_WND_BORDER_COR + LZDSH_WND_BORDER_WDT)
#define LZDSH_ABOUT_WND_DY (LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + \
                              LZDSH_ABOUT_WND_MARGIN_UP + LZDSH_ABOUT_WND_MARGIN + \
                              LZDSH_VERSION_DY + \
                              LZDSH_ABOUT_WND_MARGIN + LZDSH_WND_BORDER_COR + LZDSH_WND_BORDER_WDT)

// -----------------------------
class LzdShAboutDlg
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

   LzdShAboutDlg(void);
   HRESULT GetOpenResult(void){ return(m_lhOpenResult); }

   HRESULT OpenWindow(HINSTANCE hInst); // sukuria ir atidaro dialogo langa

// HRESULT DoEdit(void); // sukuria ir atidaro dialogo langa, perima pranesimu apdorojima

};

extern BOOL CALLBACK LzdShAboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// extern LzdShAboutDlg theAboutDialog;
extern LzdShAboutDlg *pAboutDialog;
#define theAboutDialog (*pAboutDialog)

#endif
