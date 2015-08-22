// ---------------------------
// kpstlsvu.cpp
// licenciju serverio ismetimas
// serverio varda pasiima is kpstlsvu.ini VolName + "svr.exe"
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
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
#include "kpfonts.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpmsg.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstmsg.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlb.h"
#include "xmlu.h"
#include "htmt.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "kpstap.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstlsvu"; 
int iProdVerGlob=0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl=False;
int iUpdNumGlob = -1;

KpStApp theApp;

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


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR        lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
const unsigned char *par_ptr=NULL;
unsigned char svr_name[KP_MAX_FNAME_LEN+1];
unsigned char cmd_str[KP_MAX_FNAME_LEN*2+1];
unsigned char cur_dir[KP_MAX_FNAME_LEN+1];
static unsigned char cur_disk[KP_MAX_FNAME_LEN+1];
static unsigned char cur_path[KP_MAX_FNAME_LEN+1];
static unsigned char cur_name[KP_MAX_FNAME_LEN+1];
static unsigned char cur_type[KP_MAX_FTYPE_LEN+1];
// static unsigned char ini_disk[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_path[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_name[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_type[KP_MAX_FTYPE_LEN+1];
HKEY res_key=0;
DWORD dwDisposition;
LONG retw=ERROR_SUCCESS;
FILE *url_file=NULL;

   
// ------------------------------- 
   theKpStAppPtr = &theApp;

// ------------------------------- 
#ifdef Debug
// if(SUCCEEDED(retc)) strcpy(ini_fname, "e:\\kp\\source\\kpstart\\kpstlsvi.ini");
// if(SUCCEEDED(retc)) strcpy(ini_fname, "c:\\progra~1\\tev\\matema~1\\kpstlsve.ini");
   if(SUCCEEDED(retc)) strcpy(ini_fname, "e:\\progra~1\\arkim\\bebras_b\\kpstlsvu.ini");
#else
   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);
#endif

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_fname, lpCmdLine, KpStEditMode);

   if(SUCCEEDED(retc)) retc=theApp.GetIniVolName(svr_name);
   if(SUCCEEDED(retc)) strcat(svr_name, "svr");


// =====================================================
// if(SUCCEEDED(retc)) retc=TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, ini_fname);

   if(SUCCEEDED(retc)) if(!GetCurrentDirectory(KP_MAX_FNAME_LEN-1, (char *)cur_dir))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) strcat(cur_dir, "\\");
   if(SUCCEEDED(retc)) retc=TvFnameSplit(cur_disk, cur_path, cur_name, cur_type, cur_dir);

// iWindowsVersion=Win98;
   
   if(SUCCEEDED(retc))
   {
// ------------------------------------
// Win98
      if(iWindowsVersion<WinNT)
      {
         if(SUCCEEDED(retc))
         {   
            retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
               0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &res_key, &dwDisposition);
      
            if(retw!=ERROR_SUCCESS)
            {
               retc=KP_E_ACCESS_DENIED;
#ifdef Debug               
               retc=KpErrorProc.OutputErrorMessage(retc, retw, True, __FILE__, __LINE__, 0L, NULL);
#else
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
#endif               
            }
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, (const char *)svr_name);
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(res_key)
         {
            retw=RegCloseKey(res_key);
            if(retw!=ERROR_SUCCESS)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }
            res_key=0;
         }

      } // if(iWindowsVersion<WinNT)
      
// ------------------------------------
// WinNT
      else
      {
         strcpy(cmd_str, "\"");
         strcat(cmd_str, cur_disk);
         strcat(cmd_str, cur_path);
         if(iWindowsVersion<Win2000c)
         {
// E:\kp\source\Tev\mokmat\Matau5e_v1.10b.serv\files\WinNT\INSTSRV.EXE matau5esvr E:\kp\source\Tev\mokmat\Matau5e_v1.10b.serv\files\WinNT\SRVANY.EXE
            strcat(cmd_str, "\\WinNT\\INSTSRV.EXE\" ");
         }
// ------------------------------------
// Win2K      
         else
         {
// E:\kp\source\Tev\mokmat\Matau5e_v1.10b.serv\files\Win2K\INSTSRV.EXE matau5esvr E:\kp\source\Tev\mokmat\Matau5e_v1.10b.serv\files\Win2K\SRVANY.EXE
            strcat(cmd_str, "\\Win2K\\INSTSRV.EXE\" ");
         }
// ------------------------------------
// WinNT & Win2K         
         strcat(cmd_str, svr_name);
         strcat(cmd_str, " REMOVE");

// nera prasmes - servisas dar veikia, ismest neleis
         if(SUCCEEDED(retc)) retc=StartCmdProcess(cmd_str, KPST_CUR_DIR, NULL, NULL, True, SW_MINIMIZE /* SW_SHOWDEFAULT */);

// --------------------------------
         if(SUCCEEDED(retc))
         {   
            strcpy(cmd_str, "SYSTEM\\CurrentControlSet\\Services\\");
            strcat(cmd_str, svr_name);
            strcat(cmd_str, "\\Parameters");
            retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE, (const char *)cmd_str,
               0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &res_key, &dwDisposition);
      
            if(retw!=ERROR_SUCCESS)
            {
               retc=KP_E_ACCESS_DENIED;
#ifdef Debug               
               retc=KpErrorProc.OutputErrorMessage(retc, retw, True, __FILE__, __LINE__, 0L, NULL);
#else
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
#endif               
            }
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "Application");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(res_key)
         {
            retw=RegCloseKey(res_key);
            if(retw!=ERROR_SUCCESS)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }
            res_key=0;
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteKey(HKEY_LOCAL_MACHINE, (const char *)cmd_str);
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
// --------------------------------
         if(SUCCEEDED(retc))
         {   
            strcpy(cmd_str, "SYSTEM\\CurrentControlSet\\Services\\");
            strcat(cmd_str, svr_name);
            strcat(cmd_str, "\\Security");
            retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE, (const char *)cmd_str,
               0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &res_key, &dwDisposition);
      
            if(retw!=ERROR_SUCCESS)
            {
               retc=KP_E_ACCESS_DENIED;
#ifdef Debug               
               retc=KpErrorProc.OutputErrorMessage(retc, retw, True, __FILE__, __LINE__, 0L, NULL);
#else
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
#endif               
            }
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "Security");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(res_key)
         {
            retw=RegCloseKey(res_key);
            if(retw!=ERROR_SUCCESS)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }
            res_key=0;
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteKey(HKEY_LOCAL_MACHINE, (const char *)cmd_str);
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
// --------------------------------
         if(SUCCEEDED(retc))
         {   
            strcpy(cmd_str, "SYSTEM\\CurrentControlSet\\Services\\");
            strcat(cmd_str, svr_name);
            strcat(cmd_str, "\\Enum");
            retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE, (const char *)cmd_str,
               0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &res_key, &dwDisposition);
      
            if(retw!=ERROR_SUCCESS)
            {
               retc=KP_E_ACCESS_DENIED;
#ifdef Debug               
               retc=KpErrorProc.OutputErrorMessage(retc, retw, True, __FILE__, __LINE__, 0L, NULL);
#else
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
#endif               
            }
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "0");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "Count");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "NextInstance");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(res_key)
         {
            retw=RegCloseKey(res_key);
            if(retw!=ERROR_SUCCESS)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }
            res_key=0;
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteKey(HKEY_LOCAL_MACHINE, (const char *)cmd_str);
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
// --------------------------------
         if(SUCCEEDED(retc))
         {   
            strcpy(cmd_str, "SYSTEM\\CurrentControlSet\\Services\\");
            strcat(cmd_str, svr_name);
            retw=RegCreateKeyEx(HKEY_LOCAL_MACHINE, (const char *)cmd_str,
               0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &res_key, &dwDisposition);
      
            if(retw!=ERROR_SUCCESS)
            {
               retc=KP_E_ACCESS_DENIED;
#ifdef Debug               
               retc=KpErrorProc.OutputErrorMessage(retc, retw, True, __FILE__, __LINE__, 0L, NULL);
#else
               KpMsgOut(KPST_MSG_INI_NOT_ADMIN, IDI_ERROR, KP_MB_BAIGTI);
#endif               
            }
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "Type");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "Start");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "ErrorControl");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "ImagePath");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "DisplayName");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteValue(res_key, "ObjectName");
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
         if(res_key)
         {
            retw=RegCloseKey(res_key);
            if(retw!=ERROR_SUCCESS)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }
            res_key=0;
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegDeleteKey(HKEY_LOCAL_MACHINE, (const char *)cmd_str);
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         }
         
      } // else // if(iWindowsVersion<WinNT)
   
   } // if(SUCCEEDED(retc))

// ===========================================         
   /* if(SUCCEEDED(retc)) */ retc0=theApp.CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

return(RET_CODE_WIN(retc));
}

