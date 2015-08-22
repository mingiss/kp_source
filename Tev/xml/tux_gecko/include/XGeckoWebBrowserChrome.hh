#ifndef XGECKO_WEB_BROWSER_CHROME_HH
#define XGECKO_WEB_BROWSER_CHROME_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "nsCOMPtr.h"                           // nsCOMPtr
//#include "nsIContextMenuListener.h"
#include "nsIEmbeddingSiteWindow.h"             // nsIEmbeddingSiteWindow
#include "nsIInterfaceRequestor.h"              // do_GetInterface
#include "nsIWebBrowser.h"                      // nsIWebBrowser
#include "nsIWebBrowserChrome.h"                // nsIWebBrowserChrome
#include "nsWeakReference.h"                    // nsSupportsWeakReference, nsWeakReference
#include "nsIWebNavigation.h"                   // nsIWebNavigation
#include "nsIWebProgressListener.h"             // nsIWebProgressListener
#include "nsIClipboardCommands.h"               // nsIClipboardCommands
#include "nsITooltipListener.h"                 // nsITooltipListener
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XGecko.hh"

/************************************************************* TX *************************************************************/
/*                                                   XGeckoWebBrowserChrome                                                   */
/******************************************************************************************************************************/

struct XGeckoWebBrowserChrome : //nsIContextMenuListener,
                                nsIEmbeddingSiteWindow,
                                nsIInterfaceRequestor,
                                nsIWebBrowserChrome,
                                nsIWebProgressListener,
                                nsSupportsWeakReference,
                                nsITooltipListener
{
  public:
    NS_DECL_ISUPPORTS
    //NS_DECL_NSICONTEXTMENULISTENER
    NS_DECL_NSIEMBEDDINGSITEWINDOW
    NS_DECL_NSIINTERFACEREQUESTOR
    NS_DECL_NSIWEBBROWSERCHROME
    NS_DECL_NSIWEBPROGRESSLISTENER
    NS_DECL_NSITOOLTIPLISTENER

  public:
    X                                 XGeckoWebBrowserChrome(XGecko *widget, u32_t chromeFlags);
    V                                 ~XGeckoWebBrowserChrome();
    X void                            create();
    X void                            initEventListeners();
    X void                            initWebProgressListener();
    X void                            loadURI(cwstr_t uri);
    X void                            setZoom(float zoom);

  public:
    X u32_t                           chromeFlags;
    X nsCOMPtr<nsIClipboardCommands>  m_clipboardCommands;
    X nsCOMPtr<nsIWebBrowser>         m_webBrowser;
    X nsCOMPtr<nsIWebNavigation>      m_webNavigation;
    X XGecko*                         m_widget;
    X HWND                            m_toolTip;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /* XGECKO_WEB_BROWSER_CHROME_HH */

