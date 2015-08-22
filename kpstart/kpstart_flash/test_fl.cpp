//--------------------------------------------------
// test_fl.cpp
// testing flash ID


//--------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include "envir.h"
#include "kpstdlib.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstap.h"


//--------------------------------------------------
KpErrorProc_tag KpErrorProc(TRUE, 71);
int SortMode=KP_LNG_ENG;
KpStApp theApp;
KpStApp *theKpStAppPtr = &theApp;
int iProdVerGlob=0;
int KpHp11NumOfExtFun=0;
KpHp11ExtFun KpHp11ExtFunTab[]={NULL};
const unsigned char lpszProdName[] = "test_fl"; 


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


//--------------------------------------------------
// unsigned short 
// CONST WCHAR
// const wchar_t 
// const long char drv_name[]={'F',':','\\','W','I','N','N','T','\\','S','y','s','t','e','m','3','2','\\','D','R','I','V','E','R','S','\\','u','s','b','h','u','b','.','s','y','s',0};


//--------------------------------------------------
int main(void)
{
HRESULT retc=S_OK;
// HDRVR drv;
// long err;
// HANDLE dev_hdl;
KpStApp *app_ptr=NULL;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];

//   if(SUCCEEDED(retc)) retc=KpInit();

//   if(SUCCEEDED(retc))
//   {
////    drv=OpenDriver(L"F:\\WINNT\\System32\\DRIVERS\\usbhub.sys", NULL, 0L);
////    drv=OpenDriver(L"usbhub", NULL, 0L);
//      drv=OpenDriver(drv_name, NULL, 0L);
//
//      err=GetLastError();
//      
//      printf("%d %ld\n", err, drv);
//      
//      if(drv==0)
//         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, err, TRUE, __FILE__, __LINE__, 0L);
//   }


//   if(SUCCEEDED(retc))
//   {
//      dev_hdl=CreateFile(
//      LPCTSTR lpFileName,
//  DWORD dwDesiredAccess,
//  DWORD dwShareMode,
//  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//  DWORD dwCreationDisposition,
//  DWORD dwFlagsAndAttributes,
//  HANDLE hTemplateFile
//);



//BOOL DeviceIoControl(
//  HANDLE hDevice,
//  DWORD dwIoControlCode,
//  LPVOID lpInBuffer,
//  DWORD nInBufferSize,
//  LPVOID lpOutBuffer,
//  DWORD nOutBufferSize,
//  LPDWORD lpBytesReturned,
//  LPOVERLAPPED lpOverlapped
//);



   app_ptr=(&theApp);

   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);

   if(SUCCEEDED(retc)) retc=app_ptr->InitStApp(hKpInstance, ini_fname, "" /* lpCmdLine */, KpStarterMode);
   
// if(SUCCEEDED(retc)) retc=app_ptr->TestFlash();
   
// /* if(SUCCEEDED(retc)) retc = */ KpFinit();

system("pause");
return(RET_CODE(retc));
}
