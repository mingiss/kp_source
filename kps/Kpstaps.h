// -------------------------------------
// kpstaps.h
// klasės KpStSelDownload aprašas
// prenumeratos komponentų / atnaujinimų (?) parsisiuntimo selektinimo dialogas
//


#define KPST_SELDOWN_HMARGIN        (KPW_WND_MARGIN * 6)
#define KPST_SELDOWN_VMARGIN        (KPW_WND_MARGIN * 2)

#define KPST_SELDOWN_CTRL_X         KPST_SELDOWN_HMARGIN

#define KPST_SELDOWN_LINE_X1        0
#define KPST_SELDOWN_LINE_X2        (KPST_SELDOWN_WND_DX - (iWndBorderWdt * 2))

#define KPST_SELDOWN_ICON_X         KPST_SELDOWN_HMARGIN
#define KPST_SELDOWN_ICON_Y         KPST_SELDOWN_VMARGIN
#define KPST_SELDOWN_ICON_WDT       KPW_ICON_WDT

#define KPST_SELDOWN_HEAD_Y         (KPST_SELDOWN_VMARGIN * 2)
#define KPST_SELDOWN_HEAD_X         (KPST_SELDOWN_ICON_X + KPW_ICON_WDT + KPST_SELDOWN_HMARGIN)

#define KPST_SELDOWN_SUBHEAD_Y      (KPST_SELDOWN_HEAD_Y + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_BOLD] + KPST_SELDOWN_VMARGIN) 
#define KPST_SELDOWN_SUBHEAD_X      KPST_SELDOWN_HEAD_X 

#define KPST_SELDOWN_LINE1_Y        (KPST_SELDOWN_SUBHEAD_Y + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + KPST_SELDOWN_VMARGIN)

#define KPST_SELDOWN_PROMPT_Y       (KPST_SELDOWN_LINE1_Y + KPST_SELDOWN_VMARGIN)
#define KPST_SELDOWN_PROMPT_NUMLINES 2
#define KPST_SELDOWN_PROMPT_X       KPST_SELDOWN_CTRL_X

#define KPST_SELDOWN_LISTBOX_WDT    600
#define KPST_SELDOWN_LISTBOX_NUM_OF_ENTRIES  7
#define KPST_SELDOWN_LISTBOX_HGT    (iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] * KPST_SELDOWN_LISTBOX_NUM_OF_ENTRIES + 2 * KPW_CTRL_BORDER_WDT)
#define KPST_SELDOWN_LISTBOX_MAX_NUM_OF_ROWS    50
#define KPST_SELDOWN_LISTBOX_Y      (KPST_SELDOWN_PROMPT_Y + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + ((KPST_SELDOWN_PROMPT_NUMLINES - 1) * iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]) + KPST_SELDOWN_VMARGIN)
#define KPST_SELDOWN_LISTBOX_X      KPST_SELDOWN_HMARGIN

#define KPST_SELDOWN_NOMORE_Y       (KPST_SELDOWN_LISTBOX_Y + KPST_SELDOWN_LISTBOX_HGT + KPST_SELDOWN_VMARGIN)
#define KPST_SELDOWN_NOMORE_PROMPT_X KPST_SELDOWN_CTRL_X
#define KPST_SELDOWN_NOMORE_PROMPT_DX 300 // 250

#define KPST_SELDOWN_NOMORE_BOX_Y   (KPST_SELDOWN_NOMORE_Y + KPW_CHBOX_VCOR)
#define KPST_SELDOWN_NOMORE_BOX_X   (KPST_SELDOWN_NOMORE_PROMPT_X + KPST_SELDOWN_NOMORE_PROMPT_DX + KPST_SELDOWN_HMARGIN)

#define KPST_SELDOWN_LINE2_Y        (KPST_SELDOWN_NOMORE_Y + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + KPST_SELDOWN_VMARGIN)

#define KPST_SELDOWN_BUT_PROMPT_Y   (KPST_SELDOWN_LINE2_Y + KPST_SELDOWN_VMARGIN)
#define KPST_SELDOWN_BUT_PROMPT_NUMLINES 2
#define KPST_SELDOWN_BUT_PROMPT_X   KPST_SELDOWN_CTRL_X

#define KPST_SELDOWN_BUT_Y          (KPST_SELDOWN_BUT_PROMPT_Y + iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL] + ((KPST_SELDOWN_BUT_PROMPT_NUMLINES - 1) * iaCtrlRowHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL]) + KPST_SELDOWN_VMARGIN)
#define KPST_SELDOWN_OK_BUT_X       (KPST_SELDOWN_WND_DX - (2 * iWndBorderWdt) - KPST_SELDOWN_HMARGIN - KPW_BUTTON_WDT - KPW_CTRL_MARGIN - KPW_BUTTON_WDT)
#define KPST_SELDOWN_CANCEL_BUT_X   (KPST_SELDOWN_WND_DX - (2 * iWndBorderWdt) - KPST_SELDOWN_HMARGIN - KPW_BUTTON_WDT)                                                                                                                                                                                                                                                                                                                                                                                          

#define KPST_SELDOWN_WND_X    100
#define KPST_SELDOWN_WND_Y    50
#define KPST_SELDOWN_WND_DX   (iWndBorderWdt + KPST_SELDOWN_HMARGIN + KPST_SELDOWN_LISTBOX_WDT + KPST_SELDOWN_HMARGIN + iWndBorderWdt)
#define KPST_SELDOWN_WND_DY   (iWndBorderWdt + iWndCaptionHgt + KPST_SELDOWN_BUT_Y + KPW_BUTTON_HGT + KPST_SELDOWN_VMARGIN + iWndBorderWdt)

struct KpStSelDownloadPars
{
   int m_iProdVer;
   unsigned char m_lpszProdName[KP_MAX_FNAME_LEN + 1]; // produkto pavadinimas
   bool m_bUpdFl; // jei True – update, jei False – serija
};

class KpStSelDownload
{
   HRESULT m_lhOpenResult;

public:
   HWND m_hDialogWindow;
   
   HWND m_DownListBox;
   
   HWND m_NoMoreBox; // do not test updates (!m_bTestUpdates)
// bool m_bTestUpdates;
   
   HWND m_OkButton;
   HWND m_CancelButton;

   int m_iProdVer;
private:
   bool m_bShiftFl;

// -------------------
public:
   KpStSelDownload(void);
   void ClearControls(void); // išvalo kintamuosius, konstruktoriaus paprogramė
   HRESULT GetOpenResult(void);

   HRESULT OpenWindow(int iProdVer = 0, const unsigned char *lpszProdName = null, bool bUpdFl = False);
                                                         // jei iProdVer == 0, ima lokalų KpStIniData::m_iProdVer
                                                         // jei lpszProdName == null – pasiima iš lokalaus KpStIniData::m_lpszProdName[]
                                                         // bUpdFl – ar updeitas, jei ne – tada serija
   HRESULT CloseWindow(void);

   HRESULT DoEdit(void);
};

extern BOOL CALLBACK KpStSelDownDialogProc
(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
);

extern KpStSelDownload *KpStSelDownDialogPtr; // TODO: išmest, kad būtų multitaskinis (pekelt į KpStSelDownloadPars ir į KpWndList, 
                                                // iš kurio išsitraukiam pagal KpStSelDownDialogProc() parametrą hwndDlg
