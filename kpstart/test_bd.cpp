// -----------------------------------------
// test_bd
// bios date test
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <windows.h>

#include "kpstdlib.h"
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
const unsigned char lpszProdName[] = "test_bd"; 
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
KpStApp theApp;
KpStApp *theKpStAppPtr = &theApp;
bool bServiceFl=False;
#ifdef Logging
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
unsigned char lpszLogFileName[]={"test_bd.log"};
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
HRESULT retc0=S_OK;
KpStApp *app_ptr=NULL;

   app_ptr=(&theApp);

KP_TRACE("----");
   
// if(SUCCEEDED(retc)) retc=app_ptr->InitStApp(hInstance, NULL, lpCmdLine, KpStarterMode);
  
   if(SUCCEEDED(retc)) retc=app_ptr->InitCommonApp(hInstance, lpCmdLine);
   app_ptr->m_iKpStMode=KpStRegMode;
   if(SUCCEEDED(retc)) retc=app_ptr->StartHp11(hInstance);
   app_ptr->m_iKpstRand0=KpstRand(0);

// retc0=app_ptr->GetCommonCompID(); if(SUCCEEDED(retc)) retc=retc0;
   if(SUCCEEDED(retc)) retc=app_ptr->SetIniProdVer(2010);
   if(SUCCEEDED(retc)) retc=app_ptr->SetIniCiDirect(True);
   retc0=app_ptr->GetSavedCompID(); if(SUCCEEDED(retc)) retc=retc0;
   retc0=app_ptr->GetPhysCompId(); if(SUCCEEDED(retc)) retc=retc0;

// /* if(SUCCEEDED(retc)) */ retc0=app_ptr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

   retc0=EmuTv.StopThread();
   if(SUCCEEDED(retc)) retc=retc0;

   retc0=app_ptr->CloseCommonApp();
   if(SUCCEEDED(retc)) retc=retc0;

return(RET_CODE(retc));
}

