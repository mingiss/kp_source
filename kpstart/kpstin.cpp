// ---------------------------
// kpstin.cpp, 
// aplikacijos inicializavimas
// leidzia rasyti i CompID faila
// perskaito ir iraso CompID
// paleidziamas iskart po diegimo, kad pagrindinei aplikacijai (ne AllwaysCid)
//    nereiketu knistis po CompID
//
// atskiri projektai:
//    kpstin.exe
//    kpstind.exe - #ifdef Debug
//    kpstinl.exe - #ifdef Debug Logging DebugStop
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
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kpcapp.h"
#include "kpstmsg.h"
#include "kpstap.h"
#include "kpstart.h"

#define INIT_PREF ("init_")

#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
KpStartApp theApp;
KpStApp *theKpStAppPtr = static_cast<KpStApp *> (&theApp);
#ifdef Logging
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
unsigned char lpszLogFileName[]={"c:\\arkim\\rezultatai\\kpstart.log"};
#endif

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------------
HRESULT GetIniIniFname(unsigned char *lpszIniFnameBuf)
{                           
HRESULT retc=S_OK;
#ifndef Debug
unsigned char *ini_fname_ptr;
#endif
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char name[KP_MAX_FNAME_LEN+1];
unsigned char type[KP_MAX_FTYPE_LEN+1];
   
   if(lpszIniFnameBuf==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) retc=GetAppName(lpszIniFnameBuf);
   
   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, lpszIniFnameBuf);

#ifndef Debug
   if(SUCCEEDED(retc))
   {
      ini_fname_ptr=strstr(name, INIT_PREF);      
      if(ini_fname_ptr!=name)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }
#endif

   if(SUCCEEDED(retc))
   {
      strcpy(lpszIniFnameBuf, disk);
      strcat(lpszIniFnameBuf, path);
      if(strlen(path)>0) strcat(lpszIniFnameBuf, "\\");
#ifndef Debug
      strcat(lpszIniFnameBuf, name+strlen(INIT_PREF));      
#endif      
      strcat(lpszIniFnameBuf, ".ini");
   }
   
#ifdef Debug
   strcpy(lpszIniFnameBuf, "kpstin.ini");
#endif   

return(retc);   
}


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK; 
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
KpStartApp *app_ptr=NULL;

   app_ptr=(&theApp);
   
// ------------------------------- 
   if(SUCCEEDED(retc)) retc=GetIniIniFname(ini_fname);

   if(SUCCEEDED(retc)) retc=app_ptr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStEditMode);

   if(SUCCEEDED(retc)) retc=app_ptr->SetIniCiDirect(True);
   
   if(SUCCEEDED(retc)) retc=app_ptr->GetCommonCompID();
   
   if(SUCCEEDED(retc)) retc=app_ptr->SaveCompID(True);

   /* if(SUCCEEDED(retc)) */ retc0=app_ptr->CloseStApp(retc, KP_My_Documents); if(SUCCEEDED(retc)) retc=retc0;

return(RET_CODE(retc));
}

