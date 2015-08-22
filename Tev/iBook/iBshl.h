// -----------------------------------------
// iBshl.h
// el. knygø perþiûros programa
// paprastas dialogas su keliais mygtukais (uþdarymo, SaveAs etc.)
//

#ifndef iBshl_included
#define iBshl_included

// ---------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef iBsh_included
// #error iBsh.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif

// ----------------
#define IBSH_TOOL_BCOL  (RGB(227, 229, 228))

// ----------------------------- m_ButSaveAs
#if IBSH_SKIN==IBSH_SKIN_MIKO
#  ifdef IBSH_SAVE_AS
#define  IBSH_BUT_SAVE_AS_X(dlg_ptr) (IBSH_BUT_EXIT_X(dlg_ptr) - IBSH_BUT_MARGIN - IBSH_BUT_WDT - IBSH_BUT_MARGIN - IBSH_BUT_WDT - IBSH_BUT_MARGIN) // (IBSH_BUT_MARGIN /* IBSH_WND_MARGIN */ + 20) // (IBSH_CAPT_X + IBSH_CAPT_DX + IBSH_BUT_MARGIN)
#define  IBSH_BUT_SAVE_AS_Y(dlg_ptr) (/* (dlg_ptr)->m_iWndSoftBorderWdt + */ IBSH_BUT_MARGIN)
#define  IBSH_BUT_SAVE_AS_TOOLTIP_TXT ((const unsigned char *)"  Áraðyti")
#  endif
#endif

// -----------------------------
#if IBSH_SKIN == IBSH_SKIN_STANDART
extern COLORREF KpColorSchemeToolTip[KpNumOfShadows0];
extern COLORREF KpColorSchemeLocal[KpNumOfShadows0];
#else
extern COLORREF KpColorSchemeLocal[KpNumOfShadows0];
#endif


#ifdef DebugStartGrp
#define KP_IBSHL_REDRAW_TIMEOUT 300
#else
#define KP_IBSHL_REDRAW_TIMEOUT 1150
#endif

// ----------------
class iBshDlg
#ifdef IBSH_RES_MODE_XGECKO
#  if CompilerGr == Mingw
: public KpGeckoDialog
#  else
: public KpPubDlg
#  endif
#else
#  ifdef IBSH_RES_MODE_MSHTML
: public KpMsHtmlDlg
#  else
#     ifdef IBSH_RES_MODE_RTF
: public KpRtfDlg
#     else
: public KpPubDlg
#     endif
#  endif
#endif
{
public:
#  if IBSH_SKIN==IBSH_SKIN_MIKO
#     ifdef IBSH_SAVE_AS
   HWND m_ButSaveAs;
#     endif
#  endif

// ----------------
   iBshDlg(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers = IBSH_OUT_VERS, UC_Modes iEncMode = UC_PlainText,
      const unsigned char *lpszCaption = IBSH_WND_CAPTION,
      int iWndDXmin = IBSH_DEF_WND_MIN_DX, int iWndDXmax = IBSH_DEF_WND_MAX_DX, int iWndDYmin = IBSH_DEF_WND_MIN_DY, int iWndDYmax = IBSH_DEF_WND_MAX_DY,
      int iWndSoftBorderWdt = IBSH_WND_SOFT_BORDER_WDT, int iWndSoftCaptHgt = IBSH_WND_SOFT_CAPTION_HGT, int iWndHardBorderWdt = IBSH_WND_BORDER_WDT, int iWndHardCaptHgt = IBSH_WND_CAPTION_HGT,
      int iScrX = IBSH_DEF_SRC_X, int iScrY = IBSH_DEF_SRC_Y, int iScrDX = IBSH_DEF_SRC_DX, int iScrDY = IBSH_DEF_SRC_DY,
      int iResDXenl = IBSH_RES_DX_ENL, int iResDYenl = IBSH_RES_DY_ENL,
      DWORD dwStyle = IBSH_WND_STYLE, 
      int iInitWndX = IBSH_DEF_WND_X, int iInitWndY = IBSH_DEF_WND_Y, int iInitWndDX = IBSH_DEF_WND_DX, int iInitWndDY = IBSH_DEF_WND_DY);

   virtual HRESULT Resize(void); // perskaièiuoja langø koordinates, lango neperpieðia, fiziniø lango matmenø nekeièia

   virtual HRESULT OpenWindow(HINSTANCE hInst, bool bShowWindow = True); // sukuria ir atidaro dialogo langa

   virtual HRESULT RedrawWindow(void); // pakeièia langeliø dydá ir perpaiðo langa

   virtual int DoEdit(void); // perima dialogo praneðimø apdorojimà; gràþina kodà, kurá reikia gràþinti ið WinMain()
};

extern BOOL CALLBACK iBshDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
