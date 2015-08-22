#ifndef XGECKO_INPUT_STREAM_HH
#define XGECKO_INPUT_STREAM_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IInputStream.hh"

#include "nsIURI.h"                             // nsIURI
#include "nsIInputStream.h"                     // nsIInputStream

/************************************************************* TX *************************************************************/
/*                                                     XGeckoInputStream                                                      */
/******************************************************************************************************************************/

struct XGeckoInputStream : nsIInputStream
{
  public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIINPUTSTREAM
  public:
    X                     XGeckoInputStream();
    V                     ~XGeckoInputStream();
    X bool                open(nsIURI *a_URI);
  public:
    S IStreamFactory_t    factory;
    X IInputStream        *stream;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /* XGECKO_INPUT_STREAM_HH */
