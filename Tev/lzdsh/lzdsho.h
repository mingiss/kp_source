// -----------------------------------------
// lzdsho.h
// zodyno perziuros programa
// parinkciu dialogas
//

#ifndef lzdsho_included
#define lzdsho_included


// ---------------------------------
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

// -----------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
#define LZDSH_OPT_WND_MARGIN_UP 0
#else
#define LZDSH_OPT_WND_MARGIN_UP 25 // KPW_WND_CAPTION_HGT // local caption height
#endif

#define LZDSH_OPT_WND_MARGIN  20 // LZDSH_WND_MARGIN
#define LZDSH_OPT_CTRL_MARGIN KPW_CTRL_MARGIN // LZDSH_WND_MARGIN
#define LZDSH_OPT_GRP_MARGIN  20 // LZDSH_OPT_CTRL_MARGIN

#define LZDSH_OPT_WND_TXT  (/* (const unsigned char *) */ "Parinktys")

#if IBSH_SKIN != IBSH_SKIN_STANDART
#define LZDSH_SKIN_CAPT_TXT_X (LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR + LZDSH_OPT_WND_MARGIN)
#define LZDSH_SKIN_CAPT_TXT_Y (LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR + 1)

#define LZDSH_OPT_BUT_EXIT_X (LZDSH_OPT_WND_DX - LZDSH_WND_BORDER_WDT*2 - LZDSH_WND_BORDER_COR*2 - LZDSH_BUT_WDT - 1)
#define LZDSH_OPT_BUT_EXIT_Y (LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR + 2)
#endif

// -----------------------------
#define LZDSH_SKIN_PROMPT_DX  100

#define LZDSH_SKIN_BOX_DX     120
#define LZDSH_SKIN_BOX_REAL_DX  LZDSH_SKIN_BOX_DX

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#  ifndef LZDSH_DELT

#define LZDSH_SKIN_PROMPT_X   (LZDSH_WND_BORDER_COR+LZDSH_OPT_WND_MARGIN)
#define LZDSH_SKIN_PROMPT_Y   (LZDSH_OPT_WND_MARGIN_UP+LZDSH_OPT_WND_MARGIN)
#define LZDSH_SKIN_PROMPT_DY  (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])

#define LZDSH_SKIN_BOX_REAL_X (LZDSH_SKIN_PROMPT_X+LZDSH_SKIN_PROMPT_DX+LZDSH_CTRL_MARGIN)
#define LZDSH_SKIN_BOX_X      (LZDSH_SKIN_BOX_REAL_X+2)
#define LZDSH_SKIN_BOX_Y      LZDSH_SKIN_PROMPT_Y
#define LZDSH_SKIN_BOX_DY     (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])

#define LZDSH_SKIN_PROMT_TXT  ((const unsigned char *)"Lango stilius:")

#define LZDSH_OPT_SKIN_MARGIN LZDSH_OPT_GRP_MARGIN // intervalas po m_hSkinBox
// #define LZDSH_OPT_SKIN_MARGIN LZDSH_OPT_CTRL_MARGIN

#  else // #ifndef LZDSH_DELT

#define LZDSH_SKIN_BOX_DY     0
#define LZDSH_OPT_SKIN_MARGIN 0

#  endif // #else // #ifndef LZDSH_DELT

#else // #if IBSH_SKIN != IBSH_SKIN_START_GRP

#define LZDSH_SKIN_BOX_DY     0
#define LZDSH_OPT_SKIN_MARGIN 0

#endif // #else // #if IBSH_SKIN != IBSH_SKIN_START_GRP


// -----------------------------
#define LZDSH_CHKBOX_DY             (iaCtrlHeights[iWindowsVersionCut][KPW_CONTROL_STYLE_NORMAL])
#define LZDSH_CHKBOX_MARGIN         LZDSH_OPT_CTRL_MARGIN

#define LZDSH_PROMPT_DX             210

// -----------------------------
#define LZDSH_UPD_PROMPT_X       (LZDSH_WND_BORDER_COR + LZDSH_OPT_WND_MARGIN)
#define LZDSH_UPD_PROMPT_Y       (LZDSH_OPT_WND_MARGIN_UP + LZDSH_OPT_WND_MARGIN + \
                                    LZDSH_SKIN_BOX_DY + LZDSH_OPT_SKIN_MARGIN)
#define LZDSH_UPD_PROMPT_DX      LZDSH_PROMPT_DX
// #define LZDSH_UPD_PROMT_TXT      ((const unsigned char *)"Automatinis versijos tikrinimas:")
#define LZDSH_UPD_PROMT_TXT      ((const unsigned char *)"Automatinis atnaujinimø tikrinimas:")
#define LZDSH_UPD_BOX_X          (LZDSH_UPD_PROMPT_X+LZDSH_UPD_PROMPT_DX)
#define LZDSH_UPD_BOX_Y          LZDSH_UPD_PROMPT_Y
#define LZDSH_UPD_BOX_DY         LZDSH_CHKBOX_DY      

// -----------------------------
#if IBSH_SKIN != IBSH_SKIN_START_GRP

#define LZDSH_ONTOP_PROMPT_X     (LZDSH_WND_BORDER_COR + LZDSH_OPT_WND_MARGIN)
#define LZDSH_ONTOP_PROMPT_Y     (LZDSH_OPT_WND_MARGIN_UP + LZDSH_OPT_WND_MARGIN + \
                                    LZDSH_SKIN_BOX_DY + LZDSH_OPT_SKIN_MARGIN + \
                                    LZDSH_CHKBOX_DY + LZDSH_CHKBOX_MARGIN)
#define LZDSH_ONTOP_PROMPT_DX    LZDSH_PROMPT_DX
#define LZDSH_ONTOP_PROMT_TXT    ((const unsigned char *)"Visada virðuje:")
#define LZDSH_ONTOP_BOX_X        (LZDSH_ONTOP_PROMPT_X + LZDSH_ONTOP_PROMPT_DX)
#define LZDSH_ONTOP_BOX_Y        LZDSH_ONTOP_PROMPT_Y
#define LZDSH_ONTOP_BOX_DY       LZDSH_CHKBOX_DY
#define LZDSH_ONTOP_BOX_MARGIN   LZDSH_CHKBOX_MARGIN // intervalas prieð m_hOnTopBox

// -----------------------------
#define LZDSH_REACT_PROMPT_X     (LZDSH_WND_BORDER_COR + LZDSH_OPT_WND_MARGIN)
#define LZDSH_REACT_PROMPT_Y     (LZDSH_OPT_WND_MARGIN_UP + LZDSH_OPT_WND_MARGIN + \
                                 LZDSH_SKIN_BOX_DY + LZDSH_OPT_SKIN_MARGIN + \
                                 (LZDSH_CHKBOX_DY + LZDSH_CHKBOX_MARGIN)*2)
#define LZDSH_REACT_PROMPT_DX    LZDSH_PROMPT_DX
// #define LZDSH_REACT_PROMT_TXT    ((const unsigned char *)"Reaguoti á paþymëjimus:")
#define LZDSH_REACT_PROMT_TXT    ((const unsigned char *)"Reaguoti á iðkarpinæ:")
#define LZDSH_REACT_BOX_X        (LZDSH_REACT_PROMPT_X + LZDSH_REACT_PROMPT_DX)
#define LZDSH_REACT_BOX_Y        LZDSH_REACT_PROMPT_Y
#define LZDSH_REACT_BOX_DY       LZDSH_CHKBOX_DY
#define LZDSH_REACT_BOX_MARGIN   LZDSH_CHKBOX_MARGIN // intervalas prieð m_hReactBox

#else // #if IBSH_SKIN != IBSH_SKIN_START_GRP

#define LZDSH_ONTOP_BOX_DY       0
#define LZDSH_ONTOP_BOX_MARGIN   0

#define LZDSH_REACT_BOX_DY       0
#define LZDSH_REACT_BOX_MARGIN   0

#endif // #else // #if IBSH_SKIN != IBSH_SKIN_START_GRP

// -----------------------------
#define LZDSH_OPT_OK_BUT_TXT     ((const unsigned char *)"Gerai")
#define LZDSH_OPT_CANCEL_BUT_TXT ((const unsigned char *)"Atðaukti")

#define LZDSH_OPT_BUT_MARGIN LZDSH_OPT_GRP_MARGIN // LZDSH_OPT_CTRL_MARGIN

#define LZDSH_OPT_BUT_Y          (LZDSH_OPT_WND_MARGIN_UP + LZDSH_OPT_WND_MARGIN + \
                                    LZDSH_SKIN_BOX_DY + LZDSH_OPT_SKIN_MARGIN + \
                                    LZDSH_UPD_BOX_DY + \
                                    LZDSH_ONTOP_BOX_MARGIN + LZDSH_ONTOP_BOX_DY + \
                                    LZDSH_REACT_BOX_MARGIN + LZDSH_REACT_BOX_DY + \
                                    LZDSH_OPT_BUT_MARGIN)
//#define LZDSH_OPT_CANCEL_BUT_X (LZDSH_OPT_WND_DX/2 + LZDSH_OPT_WND_MARGIN)
//#define LZDSH_OPT_OK_BUT_X     (LZDSH_OPT_WND_DX/2 - LZDSH_OPT_WND_MARGIN - LZDSH_TXT_BUT_WDT)
#define LZDSH_OPT_CANCEL_BUT_X   (LZDSH_OPT_WND_DX - LZDSH_WND_BORDER_WDT*2 - LZDSH_WND_BORDER_COR - LZDSH_WND_MARGIN - LZDSH_TXT_BUT_WDT)
#define LZDSH_OPT_OK_BUT_X       (LZDSH_OPT_WND_DX - LZDSH_WND_BORDER_WDT*2 - LZDSH_WND_BORDER_COR - LZDSH_WND_MARGIN - LZDSH_TXT_BUT_WDT-LZDSH_CTRL_MARGIN-LZDSH_TXT_BUT_WDT)

// -----------------------------
#if IBSH_SKIN != IBSH_SKIN_START_GRP
// #define LZDSH_OPT_WND_X (lzdsh_dlg->m_iWndCurX + LZDSH_MENU_OPTIONS_X + 20) // (lzdsh_dlg->m_iWndCurX+60) // (LZDSH_WND_X+60)
#define LZDSH_OPT_WND_X_OFFSET (LZDSH_MENU_OPTIONS_X + 20) // (lzdsh_dlg->m_iWndCurX+60) // (LZDSH_WND_X+60)
#else
// #define LZDSH_OPT_WND_X (lzdsh_dlg->m_iWndCurX + lzdsh_dlg->m_iWndCurDX - LZDSH_OPT_WND_DX - 20)
#define LZDSH_OPT_WND_X_OFFSET (- LZDSH_OPT_WND_DX - 20)
#endif
// #define LZDSH_OPT_WND_Y (lzdsh_dlg->m_iWndCurY + LZDSH_MENU_Y + LZDSH_MENU_ITEM_HGT + LZDSH_CTRL_MARGIN) // (lzdsh_dlg->m_iWndCurY+60) // (LZDSH_WND_Y+60)
#define LZDSH_OPT_WND_Y_OFFSET (LZDSH_MENU_Y + LZDSH_MENU_ITEM_HGT + LZDSH_CTRL_MARGIN) // (lzdsh_dlg->m_iWndCurY+60) // (LZDSH_WND_Y+60)

#define LZDSH_OPT_WND_DX         (LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR + \
                                    LZDSH_OPT_WND_MARGIN + LZDSH_SKIN_PROMPT_DX + LZDSH_CTRL_MARGIN + \
                                    LZDSH_SKIN_BOX_REAL_DX + LZDSH_OPT_WND_MARGIN + LZDSH_WND_BORDER_COR + LZDSH_WND_BORDER_WDT)
#define LZDSH_OPT_WND_DY         (LZDSH_WND_BORDER_WDT + LZDSH_WND_CAPTION_HGT + \
                                    LZDSH_OPT_WND_MARGIN_UP + LZDSH_OPT_WND_MARGIN + \
                                    LZDSH_SKIN_BOX_DY + LZDSH_OPT_SKIN_MARGIN + \
                                    LZDSH_UPD_BOX_DY + \
                                    LZDSH_ONTOP_BOX_MARGIN + LZDSH_ONTOP_BOX_DY + \
                                    LZDSH_REACT_BOX_MARGIN + LZDSH_REACT_BOX_DY + \
                                    LZDSH_OPT_BUT_MARGIN + \
                                    LZDSH_TXT_BUT_HGT + \
                                    LZDSH_WND_MARGIN + LZDSH_WND_BORDER_COR + LZDSH_WND_BORDER_WDT)

// ------------------------------ linijos
#define LZDSH_OPT_LINE_X      (0)
#define LZDSH_OPT_LINE_DX     (LZDSH_OPT_WND_DX - 2*(LZDSH_WND_BORDER_WDT + LZDSH_WND_BORDER_COR))
#define LZDSH_OPT_LINE_1_Y    (LZDSH_SKIN_PROMPT_Y - LZDSH_OPT_WND_MARGIN/2) // LZDSH_OPT_GRP_MARGIN/2)
#define LZDSH_OPT_LINE_2_Y    (LZDSH_UPD_PROMPT_Y - LZDSH_OPT_SKIN_MARGIN/2)
#define LZDSH_OPT_LINE_3_Y    (LZDSH_OPT_BUT_Y - LZDSH_OPT_BUT_MARGIN/2)

// ----------------------------
#define LZDSH_SKIN_STA_TXT ("Standartinis")
#define LZDSH_SKIN_MAHD_TXT ("Medinis")


// -----------------------------
typedef enum{

   LzdshSkinSta,
   LzdshSkinMahd,

   LzdshNumOfSkins

} LzdshSkins;

// -----------------------------
class LzdShOptDlg
{
   HRESULT m_lhOpenResult;
   
   HINSTANCE m_hInstance;

public:
   KpPubDlg *m_pOffsetWnd;

   HWND m_hDialogWindow;
   bool m_bWindowOpen;

   int m_iWndCurX;
   int m_iWndCurY;

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
   HWND m_hSkinBox;
#endif
#endif
   HWND m_hUpdBox;
#if IBSH_SKIN != IBSH_SKIN_START_GRP
   HWND m_hOnTopBox;
   HWND m_hReactBox;
#endif

// bool m_bLButPressed; // left mouse button pressed flag, used for draging
   int m_iMouseX;
   int m_iMouseY;
   bool m_bCaptured;

   HWND m_ButExit;

#if IBSH_SKIN != IBSH_SKIN_START_GRP
#ifndef LZDSH_DELT
   KpTreeEntry *m_SkinList;
   DWORD /* int */ m_iCurSkin;
   int m_iCurSkinTmp;
#endif
#endif
   
   bool m_bTestUpdates;
#if IBSH_SKIN != IBSH_SKIN_START_GRP
   bool m_bOnTop;
   bool m_bReactToSel;
#endif

   HWND m_OkButton;
   HWND m_CancelButton;

   LzdShOptDlg(KpPubDlg *pOffsetWnd, int iWndCurX = 100, int iWndCurY = 100);
   ~LzdShOptDlg(void);

   HRESULT GetOpenResult(void);
   
   HRESULT OpenWindow(HINSTANCE hInst); // sukuria ir atidaro dialogo langa

// HRESULT DoEdit(void); // sukuria ir atidaro dialogo langa, perima pranesimu apdorojima

};

extern BOOL CALLBACK LzdShOptDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// extern LzdShOptDlg theOptDialog;
extern LzdShOptDlg *pOptDialog;
#define theOptDialog (*pOptDialog)

#endif
