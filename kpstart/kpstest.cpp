// ---------------------------
// kpstest.cpp
// kpstart.exe rezultatu irasymo tikrinimas
//
// kpstest.exe kopijuojamas i ivairius  test.exe, test*.exe
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


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// #define DebugStop

// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
KpStartApp theApp;
KpStApp *theKpStAppPtr = static_cast<KpStApp *> (&theApp);
KpStdApp *theKpStdAppPtr = static_cast<KpStdApp *> (&theApp);
unsigned char lpszLogFileName[]={"c:\\arkim\\rezultatai\\kpstest.log"};

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
HRESULT retc0=S_OK; 
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
unsigned char *ini_fname_ptr;
unsigned char clip_buf[KP_MAX_FNAME_LEN];
unsigned char file_name[KP_MAX_FNAME_LEN];
int retv;

// ------------------------------- 
   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);
   
   if(SUCCEEDED(retc))
   {             
      ini_fname_ptr = ini_fname + strlen(ini_fname);
      do
      {                       
         if(*(--ini_fname_ptr)=='\\') break;
      } while(ini_fname_ptr>ini_fname);
      if(*ini_fname_ptr=='\\') ini_fname_ptr++;
   }

#ifdef Debug
#ifdef DebugStop
KpMsgOut("1. InitStApp", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_fname_ptr, lpCmdLine, KpStarterMode);

   /* retc0= */ theApp.GetSavedCompID(); // if(SUCCEEDED(retc)) retc=retc0;
   if(theApp.m_iCompId==0) retc0=theApp.GetPhysCompId(); if(SUCCEEDED(retc)) retc=retc0;
   /* if(SUCCEEDED(retc)) retc= */ theApp.SaveCompID();

#ifdef Debug
#ifdef DebugStop
KpMsgOut("2. StartCmdProcess", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// ---------------------- start main process
   if(SUCCEEDED(retc)) retc=StartCmdProcess(theApp.m_Ini.lpszCmdStr, NULL, &(theApp.m_hCmdProcess), True, SW_SHOWDEFAULT);
                   
#ifdef Debug
#ifdef DebugStop
KpMsgOut("3. StartComplete", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc=theApp.StartComplete();

// -------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4. CloseStApp", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

// -------------------- delete rez file
   if(SUCCEEDED(retc)) retc=theApp.GetRezFileName(file_name);
   if(SUCCEEDED(retc)) if(!DeleteFile((char *)file_name))
   {
      retv=GetLastError();
//    retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retv, True, __FILE__, __LINE__, 0L);
   }                
  
   if(SUCCEEDED(retc)) retc=theApp.ProcessCmds();
                 
/* if(SUCCEEDED(retc)) */ retc=theApp.CloseStApp(retc, KP_My_Documents);
                 
#ifdef Debug                                               
{                
char str_buf[200];

Sleep(500);

sprintf(str_buf, "copy \"%s\" c:\\arkim\\rezultatai >> mydocs.dir", file_name);
system(str_buf);

Sleep(500);

GetMyDocumentsPath(file_name);
sprintf(str_buf, "dir \"%s\" >> c:\\arkim\\rezultatai\\mydocs.dir", file_name);
system(str_buf);

Sleep(500);
}
#endif

                 
                 
// ------------------------------- test if returned right parameters
   clip_buf[0]=Nul;
   if(SUCCEEDED(retc))
   {
      retc=GetClipboardText(HWND_DESKTOP, clip_buf, KP_MAX_FNAME_LEN, False);
      if(FAILED(retc)) switch(retc)
      {
      case KP_E_OBJ_NOT_FOUND:
         retc=S_OK;
         clip_buf[0]=Nul;
         break;
      case KP_E_BUFFER_OVERFLOW:        
//    /* retc= */ KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         retc=S_OK;
//       clip_buf[KP_MAX_FNAME_LEN]=Nul;
         clip_buf[0]=Nul;
         break;
      default:
      /* retc= */ KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         retc=S_OK;
         clip_buf[0]=Nul;
         break;
      }            
   }
   
   if(SUCCEEDED(retc))
   {
      if(strcmp(clip_buf, "12345678")!=0)
         retc=KpMsgOut(KPST_MSG_TEST_UNSUC, IDI_ERROR, KP_MB_BAIGTI);      
      else   
         retc=KpMsgOut(KPST_MSG_TEST_SUCC, IDI_ASTERISK, KP_MB_BAIGTI);      
   }
   else if((retc==KP_E_OBJ_NOT_FOUND) && (!theApp.m_Ini.bKumul))
   {
      retc=KpMsgOut(KPST_MSG_TEST_UNSUC, IDI_ERROR, KP_MB_BAIGTI);      
   }
   
#ifdef Debug
#ifdef DebugStop
KpMsgOut("5. Exit", IDI_ASTERISK, KP_MB_TESTI);
#endif
#endif

return(RET_CODE(retc));
}

