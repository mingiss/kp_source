#ifndef XEVENT_HH
#define XEVENT_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "XWidget.hh"

/************************************************************* TX *************************************************************/
/*                                                           XEvent                                                           */
/******************************************************************************************************************************/

struct XEvent
{
  public:
    enum EType
    {
      Unknown,
      DOMEvent
    };
  public:
    X         XEvent(int type = 0);
    V         ~XEvent();
    X void    post(XWidget *widget);
    X long    send(XWidget *widget);
  public:
    X int     type;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XEVENT_HH */
