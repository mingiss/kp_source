#ifndef XGECKO_REQUEST_SUSPENDER_HH
#define XGECKO_REQUEST_SUSPENDER_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>

#include "nsIRequest.h"                   // nsIRequest

/************************************************************* TX *************************************************************/
/*                                                   XGeckoRequestSuspender                                                   */
/******************************************************************************************************************************/

struct XGeckoRequestSuspender
{
  public:
    X               XGeckoRequestSuspender(nsIRequest *request);
    X               ~XGeckoRequestSuspender();
  private:
    X nsIRequest*   m_request;
};

/******************************************************************************************************************************/

XGeckoRequestSuspender :: XGeckoRequestSuspender(nsIRequest *request):
  m_request(request)
{
  if (NS_FAILED(m_request->Suspend()))
  {
    XDEBUG_S(L"WARNING: couldn't suspend pump");
    m_request = nsnull;
  }
}

XGeckoRequestSuspender :: ~XGeckoRequestSuspender()
{
  if (m_request)
    m_request->Resume();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_REQUEST_SUSPENDER_HH */
