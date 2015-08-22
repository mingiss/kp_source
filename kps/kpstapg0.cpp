// ---------------------------
// kpstapg0.cpp
// grupinių leidinių / prenumeratų / update tvarkymas
// standartinės lokalios funkcijos
//

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <ctype.h>
#include <stdio.h>
#include <string>
#include <iostream>
#if Compiler != Watcom
#include <sstream>
#endif
#include <fstream>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <winuser.h> // buvo kažkodėl užkomentuotas, reikalingas Watcom 1.8
#include <windowsx.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <richedit.h>
#include <Richole.h>
#include <psapi.h>

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#if CompilerGr == Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif

#include "md5.h"

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpctypp.h"
#include "kpstdlib.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpttucf.h"
#include "kpsock.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlb.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlg.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "KpGecko.h"
#include "KpMsHtml.h"
#include "KpRtfDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstlsvr.h"
#include "kpstmsg.h"
#include "kpstmsg_en.h"
#include "kpstmsg_lt.h"
#include "kpstmsg_pl_1250.h"
#include "kpstmsg_pl_1257.h"
#include "kpstmsg_ru.h"
#include "iBsh.h"
#include "iBshl.h"
#include "iBsht.h"
#include "kpstedi.h"
#include "kpsttre.h"
#include "kpsttrg.h"
#include "kpstapa.h"
#include "kpstaps.h"


// --------------------------------
#ifndef iBshn_included
#error iBshn.h not included
#endif

#ifndef IBSH_SKIN
#error IBSH_SKIN undefined
#endif


// -----------------------------------------
long StartGrp_fonas_len = 0L;
unsigned char StartGrp_fonas[] = {Nul};


// -----------------------------------------
HRESULT KpStApp::GetGrpLocalDir(unsigned char *lpszLocalDir)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszLocalDir != null, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc)) retc = GetLocalPath(lpszLocalDir, KP_Temp_Dir);

return(retc);
}
