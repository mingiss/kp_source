// ---------------------------
// kpstdlr.cpp
// rezultatai.txt trynimas
//
// kpstdlr.exe kopijuojamas i delrez.exe
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>
#include <richedit.h>
#include <string>
#include <fstream>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kpcapp.h"
#include "kpstap.h"
// #include "kpstart.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif


// -----------------------------------------
const unsigned char lpszProdName[] = "kpstdlr"; 
int iProdVerGlob = 0;
int iUpdNumGlob = -1;
bool bServiceFl = False;

KpErrorProcClass KpErrorProc(True, 71);
/* KpStartApp */ KpCommonApp theApp;                 

int KpHp11NumOfExtFun = KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_3 + 1]=
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


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
static unsigned char js_log_fname[KP_MAX_FNAME_LEN+1];
static unsigned char arc_file_name[KP_MAX_FNAME_LEN+20+1];

//-----------------
   if(SUCCEEDED(retc)) retc=theApp.InitCommonApp(hInstance, lpCmdLine);

//-----------------
// if(SUCCEEDED(retc)) retc=GetGlobalJsName(js_fname);

//-----------------
   if(SUCCEEDED(retc)) retc=GetLocalPath(js_log_fname, KP_Application_Data);
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname)+strlen(JS_SUB_PATH_1)<KP_MAX_FNAME_LEN)
         strcat(js_log_fname, JS_SUB_PATH_1);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }      
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname)+strlen(JS_SUB_PATH_2_60)<KP_MAX_FNAME_LEN)
         strcat(js_log_fname, JS_SUB_PATH_2_60);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname) + strlen(JS_SUB_PATH_3) + 1 < KP_MAX_FNAME_LEN)
      {
         strcat(js_log_fname, JS_SUB_PATH_3);
         strcat(js_log_fname, "\\");
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }  
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname)+strlen(GLOB_JS_HIST_FILE_NAME)<KP_MAX_FNAME_LEN)
         strcat(js_log_fname, GLOB_JS_HIST_FILE_NAME);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   
   if(SUCCEEDED(retc)) retc = CreatePath(js_log_fname, True);
   if(SUCCEEDED(retc))
      if(!DeleteFile((const char *)js_log_fname))
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);


//-----------------
   if(SUCCEEDED(retc)) retc=GetLocalPath(js_log_fname, KP_Application_Data);
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname)+strlen(JS_SUB_PATH_1)<KP_MAX_FNAME_LEN)
         strcat(js_log_fname, JS_SUB_PATH_1);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }      
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname)+strlen(JS_SUB_PATH_2_70)<KP_MAX_FNAME_LEN)
         strcat(js_log_fname, JS_SUB_PATH_2_70);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname) + strlen(JS_SUB_PATH_3) + 1 < KP_MAX_FNAME_LEN)
      {
         strcat(js_log_fname, JS_SUB_PATH_3);
         strcat(js_log_fname, "\\");
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }  
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname) + strlen(GLOB_JS_HIST_FILE_NAME) < KP_MAX_FNAME_LEN)
         strcat(js_log_fname, GLOB_JS_HIST_FILE_NAME);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   
   if(SUCCEEDED(retc)) retc = CreatePath(js_log_fname, True);
   if(SUCCEEDED(retc))
      if(!DeleteFile((const char *)js_log_fname))
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

  
//-----------------
   if(SUCCEEDED(retc)) retc=GetLocalPath(js_log_fname, KP_My_Documents);
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname) + strlen(JS_SUB_PATH_1) < KP_MAX_FNAME_LEN)
         strcat(js_log_fname, JS_SUB_PATH_1);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }      
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname) + strlen(JS_SUB_PATH_3) + 1 < KP_MAX_FNAME_LEN)
      {
         strcat(js_log_fname, JS_SUB_PATH_3);
         strcat(js_log_fname, "\\");
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }  
   if(SUCCEEDED(retc))
   {
      if(strlen(js_log_fname) + strlen(GLOB_JS_HIST_FILE_NAME) < KP_MAX_FNAME_LEN)
         strcat(js_log_fname, GLOB_JS_HIST_FILE_NAME);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   
   if(SUCCEEDED(retc)) retc = CreatePath(js_log_fname, True);
   if(SUCCEEDED(retc))
      if(!DeleteFile((const char *)js_log_fname))
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   
   
//-----------------
   if(SUCCEEDED(retc)) retc=GetLocalPath(arc_file_name, KP_My_Documents);
   
   if(SUCCEEDED(retc))
   {
      strcat(arc_file_name, KPST_REZ_FILE_NAME);
      
      if(!DeleteFile((const char *)arc_file_name))
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   }

//-----------------
   if(SUCCEEDED(retc)) retc=GetLocalPath(arc_file_name, KP_My_Documents);
   
   if(SUCCEEDED(retc))
   {
      strcat(arc_file_name, KPST_REZ_LOG_FILE_NAME);
      
      if(!DeleteFile((const char *)arc_file_name))
         retc = KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   }

return(RET_CODE_WIN(retc));
}
