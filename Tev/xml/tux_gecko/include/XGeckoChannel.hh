#ifndef XGECKO_CHANNEL_HH
#define XGECKO_CHANNEL_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "nsCOMPtr.h"                           // nsCOMPtr
#include "nsIChannel.h"                         // nsIChannel
#include "nsIRequestObserver.h"                 // nsIRequestObserver
#include "nsIStreamListener.h"                  // nsIStreamListener
#include "nsEmbedString.h"                      // nsEmbedCString
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct nsIInputStreamPump;

/************************************************************* TX *************************************************************/
/*                                                       XGeckoChannel                                                        */
/******************************************************************************************************************************/

struct XGeckoChannel :  nsIChannel,
                        nsIStreamListener
{
  public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSICHANNEL
    NS_DECL_NSIREQUEST
    NS_DECL_NSIREQUESTOBSERVER
    NS_DECL_NSISTREAMLISTENER
  public:
    X                                 XGeckoChannel(nsIURI *a_URI);
    V                                 ~XGeckoChannel();
    X nsIURI*                         getOriginalURI();
  public:
    bool                              m_opened;
    u32_t                             m_status;
    nsCOMPtr<nsIInterfaceRequestor>   m_callbacks;
    nsCString                         m_contentCharset;
    nsCString                         m_contentType;
    nsCOMPtr<nsIStreamListener>       m_listener;
    nsCOMPtr<nsISupports>             m_listenerContext;
    nsLoadFlags                       m_loadFlags;
    nsCOMPtr<nsILoadGroup>            m_loadGroup;
    nsCOMPtr<nsIURI>                  m_originalURI;
    nsCOMPtr<nsISupports>             m_owner;
    nsCOMPtr<nsIInputStreamPump>      m_pump;
    nsCOMPtr<nsISupports>             m_securityInfo;
    nsCOMPtr<nsIURI>                  m_URI;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_CHANNEL_HH */
