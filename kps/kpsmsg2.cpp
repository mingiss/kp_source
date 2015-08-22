// kpsmsg2.cpp
// Pranešimo išvedimas. Parametras – pranešimo tekstas


// -----------------------------------------
#include "envir.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kpcolors.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kpstap.h"


// ----------------------------------------
const unsigned char lpszProdName[] = "kpsmsg2"; 
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;

int KpHp11NumOfExtFun = 0;
KpHp11ExtFun KpHp11ExtFunTab[1] =
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ----------------------------------------
KpCommonApp theKpCommonAppPtr;


// ----------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
  
   retc = theKpCommonAppPtr.InitCommonApp(hInstance, lpCmdLine);

   if(SUCCEEDED(retc))
   {    
fstream in_file((const char *)theKpCommonAppPtr.m_plCmdLineArgs->GetValue(), ios::in);
      KP_ASSERT(!in_file.fail(), KP_E_FILE_NOT_FOUND, null, True);
   
      if(SUCCEEDED(retc))
      {
static unsigned char in_str[KP_MAX_FILE_LIN_LEN +1];
         in_file.getline(in_str, KP_MAX_FILE_LIN_LEN);       
         KP_ASSERT(!in_file.fail(), KP_E_FERROR, null, True);
         
         if(SUCCEEDED(retc)) KpMsgOutF(in_str);
      }
      
      in_file.close();
   }
   
   /* if(SUCCEEDED(retc)) retc = */ theKpCommonAppPtr.CloseCommonApp();

return(RET_CODE_WIN(retc));
}
