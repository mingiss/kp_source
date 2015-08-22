// ----------------------
// kpsclc.cpp, perdarytas is kpswkl.cpp
// kalkuliatoriaus lango uzdarymas
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>

#include "kpstdlib.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpcapp.h"
#include "kpstap.h"

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif
       
       
// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
KpCommonApp theApp;
int iProdVerGlob=0;
const unsigned char lpszProdName[] = "kpsclc"; 
int SortMode=KP_LNG_ENG;
        
        
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

// ---------------------------
   if(SUCCEEDED(retc))
   {
      retc = KpCloseWindow((const unsigned char *)"Calculator", False);
      if (retc == KP_E_OBJ_NOT_FOUND) retc = S_OK;

      retc = KpCloseWindow((const unsigned char *)"Skaièiuotuvas", False);
      if (retc == KP_E_OBJ_NOT_FOUND) retc = S_OK;
   }

// -----------------------------
   if(SUCCEEDED(retc)) retc=theApp.CloseCommonApp();

return(RET_CODE(retc));
}

