// ==================================================
// xmlt0.cpp
// Dummy xmlt.cpp calls for xmln applications
//


// ==================================== definitions
#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif
#include <richedit.h>
#include <Richole.h>

#include "res_com.h"
#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "tvtex.h"
#include "tvxmle.h"
#include "xmlsty.h"


// --------------------------------
HRESULT XmltTestEmbeddedLocal(KpChar /* iTagCh */, KpChar /* iPrevTag */, bool *pbEmbedded)
{
HRESULT retc=S_OK;

   if(pbEmbedded==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

return(retc);
}
