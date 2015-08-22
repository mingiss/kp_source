// ---------------------------------------
// KpMsHtml.h
// dialogas su MSHTML langu
// apibrëþimai
//

#ifndef KpMsHtml_included
#define KpMsHtml_included

#ifndef iBshn_included
#error iBshn.h not included
#endif

class KpMsHtmlDlg : public KpPubDlg
{
#ifdef IBSH_RES_MODE_MSHTML
#  if Compiler != Watcom
   HTMLWindow *m_ResHtml;
#  endif
#endif

public:
   KpMsHtmlDlg(KpFileSys *pKpFileSys,
      XmlVersions iXmlVers = IBSH_OUT_VERS, UC_Modes iEncMode = UC_PlainText,
      const unsigned char *lpszCaption = IBSH_WND_CAPTION, 
      int iWndDXmin = IBSH_DEF_WND_MIN_DX, int iWndDXmax = IBSH_DEF_WND_MAX_DX, int iWndDYmin = IBSH_DEF_WND_MIN_DY, int iWndDYmax = IBSH_DEF_WND_MAX_DY, 
      int iWndSoftBorderWdt = IBSH_WND_SOFT_BORDER_WDT, int iWndSoftCaptHgt = IBSH_WND_SOFT_CAPTION_HGT, int iWndHardBorderWdt = IBSH_WND_BORDER_WDT, int iWndHardCaptHgt = IBSH_WND_CAPTION_HGT,
      int iScrX = IBSH_DEF_SRC_X, int iScrY = IBSH_DEF_SRC_Y, int iScrDX = IBSH_DEF_SRC_DX, int iScrDY = IBSH_DEF_SRC_DY, 
      int iResDXenl = IBSH_RES_DX_ENL, int iResDYenl = IBSH_RES_DY_ENL,
      DWORD dwStyle = IBSH_WND_STYLE, int iInitWndX = IBSH_DEF_WND_X, int iInitWndY = IBSH_DEF_WND_Y, int iInitWndDX = IBSH_DEF_WND_DX, int iInitWndDY = IBSH_DEF_WND_DY);

   virtual ~KpMsHtmlDlg(void);

   virtual HRESULT RedrawWindowLocal(void);

   virtual HRESULT DisplayResult(void);
};

#endif // #ifndef KpGecko_included
