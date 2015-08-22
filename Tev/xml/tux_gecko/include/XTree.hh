#ifndef XTREE_HH
#define XTREE_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IComparable.hh"
#include "IObject.hh"

/************************************************************* TX *************************************************************/
/*                                                           XTree                                                            */
/******************************************************************************************************************************/

struct XTree
{
  public:
    X             XTree();
    X             XTree(IComparable *key, IObject *data);
    X             ~XTree();
  public:
    IComparable   *key;
    IObject       *data;
    XTree         *nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XTREE_HH */
