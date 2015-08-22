#ifndef XGECKO_WINDOW_CREATOR_HH
#define XGECKO_WINDOW_CREATOR_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "nsIWindowCreator.h"

/************************************************************* TX *************************************************************/
/*                                                    XGeckoWindowCreator                                                     */
/******************************************************************************************************************************/

struct XGeckoWindowCreator : nsIWindowCreator
{
  public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIWINDOWCREATOR
  public:
    X XGeckoWindowCreator();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_WINDOW_CREATOR_HH */
