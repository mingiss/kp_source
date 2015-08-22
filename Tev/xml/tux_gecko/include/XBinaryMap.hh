#ifndef XBINARY_MAP_HH
#define XBINARY_MAP_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IMap.hh"
#include "XObject.hh"
#include "XTree.hh"

/************************************************************* TX *************************************************************/
/*                                                         XBinaryMap                                                         */
/******************************************************************************************************************************/

struct XBinaryMap : IMap,
                    XObject
{
  public:
    XIMPL_RELEASE();
    XIMPL_RETAIN();
  public:
    X             XBinaryMap();
    X             ~XBinaryMap();
    X void        add(IComparable *key, IObject *data);
    X bool        equals(IObject *object);
    X XTree       **findNode(const IComparable *key);
    X IObject     *operator[] (const IComparable *key);
  public:
    X int         length;
    X XTree       *tree;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XBINARY_MAP_HH */
