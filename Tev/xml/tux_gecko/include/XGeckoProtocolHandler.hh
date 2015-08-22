#ifndef XGECKO_PROTOCOL_HANDLER_HH
#define XGECKO_PROTOCOL_HANDLER_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "nsIProtocolHandler.h"

/************************************************************* TX *************************************************************/
/*                                                   XGeckoProtocolHandler                                                    */
/******************************************************************************************************************************/

struct XGeckoProtocolHandler : nsIProtocolHandler
{
  public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIPROTOCOLHANDLER
  public:
    X XGeckoProtocolHandler();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_PROTOCOL_HANDLER_HH */
