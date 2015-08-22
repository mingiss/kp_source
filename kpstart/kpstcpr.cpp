// ---------------------------
// kpstest.cpp
// kpstart.exe rezultatu irasymo tikrinimas
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>

#include "kpstdlib.h"
#include "kpstdio.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpcapp.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
class KpCommonApp theApp;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc=theApp.InitCommonApp(hInstance, lpCmdLine);

KpMsgOut(lpCmdLine, IDI_ASTERISK, KP_MB_TESTI);
   

return(RET_CODE(retc));
}

