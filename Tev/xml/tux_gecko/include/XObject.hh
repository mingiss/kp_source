#ifndef XOBJECT_HH
#define XOBJECT_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IObject.hh"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XIMPL_RELEASE()           \
  void release()                  \
  {                               \
    if (this)                     \
      if (--numRefs == 0)         \
        delete this;              \
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define XIMPL_RETAIN()            \
  void retain()                   \
  {                               \
    if (this)                     \
      numRefs++;                  \
  }

/************************************************************* TX *************************************************************/
/*                                                          XObject                                                           */
/******************************************************************************************************************************/

struct XObject : IObject
{
  public:
    X         XObject();
    V         ~XObject();
    V bool    equals(IObject *object);
    X void    release();
    X void    retain();
  protected:
    X int     numRefs;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XOBJECT_HH */
