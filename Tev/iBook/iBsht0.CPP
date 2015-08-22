// ---------------------------------------
// iBsht0.cpp
// iBsht visiðkas uþblokavimas
//

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <string>
#include <fstream>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#if Compiler != Watcom
using namespace std;
#endif

#if CompilerGr != Mingw
// #error CompilerGr != Mingw
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11y.h"
#include "kphp11m.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kphp11t.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpMsHtml.h"
#include "KpRtfDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBsht.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif



// ----------------------------------
iBshFileSys::iBshFileSys(const unsigned char *){}

iBshFileSys::~iBshFileSys(void){}

HRESULT iBshFileSys::OpenFiles
(
   const unsigned char *,
   XmlVersions,
   HRESULT
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   ),
   HRESULT
   (
      KpFile **lppFileObjPtrPtr,
      const unsigned char *lpszFNam,
      const unsigned char *lpszFMod,
      XL_FileTypes uiFTyp,
      bool bMapToPrivate
   )
)
{
return(S_OK);
}

HRESULT iBshFileSys::CloseFiles(bool){ return(S_OK); }

HRESULT iBshFileSys::SearchForEntry(KpPubDlg *, const unsigned char *, XmlO1 **, unsigned char **){ return(S_OK); }

HRESULT iBshFileSys::FormatEntry(XmlNode *, KpPubDlg *){ return(S_OK); }

