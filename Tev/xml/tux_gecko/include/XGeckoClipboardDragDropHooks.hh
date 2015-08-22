#ifndef XGECKO_CLIPBOARD_DRAG_DROP_HOOKS_HH
#define XGECKO_CLIPBOARD_DRAG_DROP_HOOKS_HH

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <XTux.hh>

#include "nsIClipboardDragDropHooks.h"          // nsIClipboardDragDropHooks

#include "XGecko.hh"

/************************************************************* TX *************************************************************/
/*                                                XGeckoClipboardDragDropHooks                                                */
/******************************************************************************************************************************/

struct XGeckoClipboardDragDropHooks :  nsIClipboardDragDropHooks
{
  public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSICLIPBOARDDRAGDROPHOOKS
  public:
    X                                 XGeckoClipboardDragDropHooks();
    V                                 ~XGeckoClipboardDragDropHooks();
  public:
    XClipboardFilter_t                m_filter;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* XGECKO_CLIPBOARD_DRAG_DROP_HOOKS_HH */
