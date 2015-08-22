#ifndef XGECKO_INIT_HH
#define XGECKO_INIT_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "IInputStream.hh"
#include "XGecko.hh"

/************************************************************* TX *************************************************************/
/*                                                         XGeckoInit                                                         */
/******************************************************************************************************************************/

struct XGeckoInit
{
  public:
    X           XGeckoInit();
    X           ~XGeckoInit();
    X void      initEmbedding();
    X void      registerFactory();
    X void      registerWindowCreator();
    X void      setProtocolIStreamFactory(IStreamFactory_t factory);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_INIT_HH */
