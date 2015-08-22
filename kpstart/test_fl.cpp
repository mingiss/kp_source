// -----------------------------------------
// test_fl
// flash serial no test
//
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kpstdio.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstap.h"


// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
int iProdVerGlob=0;
const unsigned char lpszProdName[] = "test_fl";
KpStApp theApp;
bool bServiceFl=False;
#ifdef Logging
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
unsigned char lpszLogFileName[20]; // ={"test_fl.log"};
#endif
int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   NULL
};

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
KpStApp *app_ptr=NULL;
unsigned char add_data[KP_MAX_FILE_LIN_LEN+100];
bool data_fl[KPSTAP_NUM_OF_SETS];
int ii;

// "test_fl.log"
   lpszLogFileName[0] = 't';
   lpszLogFileName[1] = 'e';
   lpszLogFileName[2] = 's';
   lpszLogFileName[3] = 't';
   lpszLogFileName[4] = '_';
   lpszLogFileName[5] = 'f';
   lpszLogFileName[6] = 'l';
   lpszLogFileName[7] = '.';
   lpszLogFileName[8] = 'l';
   lpszLogFileName[9] = 'o';
   lpszLogFileName[10] = 'g';
   lpszLogFileName[11] = Nul;

   app_ptr = &theApp;
   theKpStAppPtr = &theApp;

   if(SUCCEEDED(retc)) retc = app_ptr->InitStApp(hInstance, (const unsigned char *)"MaTau5e.ini" /* "test_fl.ini" */, lpCmdLine, KpStEditMode);

   /* if(SUCCEEDED(retc)) retc = */ app_ptr->TestFlash();

   for(ii = 0; ii < KPSTAP_NUM_OF_SETS; ii++) data_fl[ii] = False;
   /* if(SUCCEEDED(retc)) retc = */ app_ptr->FormAddData(add_data, data_fl, 0, 0, False);
fstream out_file((char *)lpszLogFileName, ios::out | ios::ate);
   out_file << add_data << endl;
   out_file.close();

return(RET_CODE_WIN(retc));
}
