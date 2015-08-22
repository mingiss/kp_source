#ifndef XGECKO_HH
#define XGECKO_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XGECKO_VER                    "1.3.2"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XWidget.hh"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct IString;
struct XGeckoClipboardDragDropHooks;
struct XGeckoDOMEvent;
struct XGeckoWebBrowserChrome;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef int                           (*XClipboardFilter_t)(IString *dst, const IString *src);

/************************************************************* TX *************************************************************/
/*                                                           XGecko                                                           */
/******************************************************************************************************************************/

struct XGecko : XWidget
{
  enum
  {
    CLIPBOARD_ALLOW   = 0,
    CLIPBOARD_DENY    = 1,
    CLIPBOARD_MODIFY  = 2
  };

  public:
    X                                 XGecko(u32_t a_chromeFlags = 0);
    V                                 ~XGecko();
    X void                            activate(bool act);
    X bool                            canCopySelection();
    X void                            copySelection();
    X void                            goBack();
    X void                            goForward();
    X void                            loadURI(cwstr_t uri);
    X long                            onCreate();
    X long                            onDestroy0();
    X long                            onDestroy1();
    X long                            onEvent(XEvent *event);
    X long                            onResize(long type, int w, int h);
    X void                            setClipboardFilter(XClipboardFilter_t filter);
    X void                            setZoom(float zoom);
    X long                            wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  public:
    V long                            onDOMEvent(XGeckoDOMEvent *event);
  public:
    X XGeckoWebBrowserChrome*         m_chrome;
    X u32_t                           m_chromeFlags;
    X XGeckoClipboardDragDropHooks*   m_clipboardHooks;
    X HWND                            m_focus;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_HH */
