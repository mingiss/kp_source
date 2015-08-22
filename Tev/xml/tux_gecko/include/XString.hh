#ifndef XSTRING_HH
#define XSTRING_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>
#include "IComparable.hh"
#include "XObject.hh"

/************************************************************* TX *************************************************************/
/*                                                          XString                                                           */
/******************************************************************************************************************************/

struct XString :  IComparable,
                  XObject
{
  public:
    XIMPL_RELEASE();
    XIMPL_RETAIN();
  public:
    X           XString();
    X           XString(cwstr_t string);
    X           ~XString();
    X int       compareTo(IComparable *object) const;
    X bool      equals(IObject *object);
    X void      free();
    X void      set(cwstr_t string);
    X           operator cwstr_t() const;
  public:
    X int       m_capacity;
    X int       m_length;
    X wstr_t    m_string;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XSTRING_HH */
