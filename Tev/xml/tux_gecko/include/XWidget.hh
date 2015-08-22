#ifndef XWIDGET_HH
#define XWIDGET_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XWIDGET_CLASS_NAME  "XWidget"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XWM_ON_EVENT        (WM_USER + 1)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct XEvent;

/************************************************************* TX *************************************************************/
/*                                                          XWidget                                                           */
/******************************************************************************************************************************/

struct XWidget
{
  public:
    X           XWidget();
    X           XWidget(HWND hWnd);
    V           ~XWidget();
    X bool      create(cstr_t windowName, u32_t style, int x, int y, int w, int h, HWND hWndParent);
    X bool      create(cstr_t windowName, u32_t style, int x, int y, int w, int h, HWND hWndParent, HMENU hMenu,
                       HINSTANCE hInstance, void *param);
    X bool      create(u32_t exStyle, cstr_t className, cstr_t windowName, u32_t style, int x, int y, int w, int h,
                       HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, void *param);
    X void      destroy();
    X void      getGeometry(int *x, int *y, int *w, int *h);
    X bool      isVisible();
    V long      onCreate();
    V long      onDestroy0();
    V long      onDestroy1();
    V long      onEvent(XEvent *event);
    V long      onKillFocus(HWND hNewFocus);
    V long      onResize(long type, int w, int h);
    V long      onSetFocus(HWND hOldFocus);
    X void      setFocus();
    X void      setGeometry(int x, int y, int w, int h);
    X void      setSize(int w, int h);
    X void      setText(cwstr_t text);
    X void      setVisible(bool visible);
    V long      wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    S bool      registerGenericWndClass(cstr_t className, WNDPROC wndProc);
    S long      __stdcall staticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  public:
    S bool      __initialized__;
    X HWND      m_hWnd;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XWIDGET_HH */
