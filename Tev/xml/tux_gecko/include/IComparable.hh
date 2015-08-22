#ifndef ICOMPARABLE_HH
#define ICOMPARABLE_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IObject.hh"

/************************************************************* TX *************************************************************/
/*                                                        IComparable                                                         */
/******************************************************************************************************************************/

interface IComparable
{
  public:
    V int   compareTo(IComparable *object) const = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* ICOMPARABLE_HH */
