#ifndef XGECKO_STRING_HH
#define XGECKO_STRING_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IString.hh"

#include "nsEmbedString.h"                      // nsEmbedString

/************************************************************* TX *************************************************************/
/*                                                        XGeckoString                                                        */
/******************************************************************************************************************************/

struct XGeckoString : IString
{
  public:
    X                 XGeckoString(nsEmbedString *string);
    V                 ~XGeckoString();
    V cwstr_t         getData() const;
    V int             length() const;
    V void            setData(cwstr_t a_data);
  public:
    X nsEmbedString*  m_string;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_STRING_HH */
