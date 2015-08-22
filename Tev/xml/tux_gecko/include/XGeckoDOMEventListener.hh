#ifndef XGECKO_DOM_EVENT_LISTENER_HH
#define XGECKO_DOM_EVENT_LISTENER_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XGecko.hh"
#include "nsEmbedString.h"                      // nsEmbedString
#include "nsIDOMEventListener.h"                // nsIDOMEventListener

/************************************************************* TX *************************************************************/
/*                                                   XGeckoDOMEventListener                                                   */
/******************************************************************************************************************************/

struct XGeckoDOMEventListener : nsIDOMEventListener
{
  public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIDOMEVENTLISTENER
  public:
    X           XGeckoDOMEventListener(XGecko *widget);
    X wstr_t    copyString(nsEmbedString *string);
    X nsresult  dispatchNativeEvent(nsIDOMEvent *a_event, nsIDOMNode *domNode);
    X wstr_t    extractSubstring(cwstr_t string, int offset, int length);
  public:
    X XGecko*   m_widget;
    X void*     m_lastNode;
    X int       m_lastOffset;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /* XGECKO_DOM_EVENT_LISTENER_HH */
