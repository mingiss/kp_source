// ---------------------------
// kpstlsvi.cpp
// licenciju serverio diegimas ir inicializavimas
// serverio varda pasiima is kpstlsvu.ini VolName + "svr.exe"
// cmd line parametras - sekundziu skaicius iki pasimetusiu licenciju islaisvinimo 
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <winbase.h>
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
const unsigned char lpszProdName[] = "kpstlsvi"; 
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
                     LPSTR
#ifndef Debug
                          lpCmdLine
#endif                          
                          ,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
int num_of_lics=0;
int ii;
int time_left=KPST_INI_SECS_TO_KILL;
KpstLicStates state=KpstLicBusy;
const unsigned char *par_ptr=NULL;
unsigned char svr_name[KP_MAX_FNAME_LEN+1];
unsigned char cmd_str[KP_MAX_FNAME_LEN*2+1];
unsigned char cur_dir[KP_MAX_FNAME_LEN+1];
static unsigned char cur_disk[KP_MAX_FNAME_LEN+1];
static unsigned char cur_path[KP_MAX_FNAME_LEN+1];
static unsigned char cur_name[KP_MAX_FNAME_LEN+1];
static unsigned char cur_type[KP_MAX_FTYPE_LEN+1];
static unsigned char svr_fname[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_disk[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_path[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_name[KP_MAX_FNAME_LEN+1];
// static unsigned char ini_type[KP_MAX_FTYPE_LEN+1];
HKEY res_key=0;
DWORD dwDisposition;
LONG retw=ERROR_SUCCESS;
FILE *url_file=NULL;
int prod_ver=0;
int port=0;
   
// ------------------------------- 
   theKpStAppPtr = &theApp;

// ------------------------------- 
#ifdef Debug
// if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);
// if(SUCCEEDED(retc)) strcpy(ini_fname, "e:\\kp\\source\\kpstart\\kpstlsvi.ini");
// if(SUCCEEDED(retc)) strcpy(ini_fname, "c:\\progra~1\\tev\\matema~1\\kpstlsve.ini");
   if(SUCCEEDED(retc)) strcpy(ini_fname, "c:\\arkim\\bebras_j\\kpstlsvi.ini");

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_fname, "180", KpStEditMode);
#else
   if(SUCCEEDED(retc)) retc=GetIniFname(ini_fname);

   if(SUCCEEDED(retc)) retc=theApp.InitStApp(hInstance, ini_fname, lpCmdLine, KpStEditMode);
#endif

   if(SUCCEEDED(retc)) retc=theApp.GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc=theApp.GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc=theApp.GetIniVolName(svr_name);
   if(SUCCEEDED(retc)) strcat(svr_name, "svr");

   if(SUCCEEDED(retc)) retc = theApp.GetServerPort(&port);
      
// =====================================================
   if(SUCCEEDED(retc)) 
   {
      time_left=KPST_INI_SECS_TO_KILL;
      state=KpstLicBusy;
      
      if(theApp.m_plCmdLineArgs)  
      {
         par_ptr=(const unsigned char *)theApp.m_plCmdLineArgs->GetValue();
         if(par_ptr) if(sscanf((const char *)par_ptr, "%d", &time_left)>=1)
         {
            if((time_left>KPST_INI_SECS_TO_KILL) || (time_left<0)) time_left=KPST_INI_SECS_TO_KILL;
            if(time_left<=KPST_INI_SECS_TO_KILL-KP_SECS_PER_MIN) state=KpstLicLost;
            if(time_left==0) state=KpstLicFree;
         }
      }
   }   

// unsigned char str_buf[100];
// sprintf((char *)str_buf, "%d %d", state, time_left);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);

   if(num_of_lics && SUCCEEDED(retc))
   { 
      if((theApp.m_pLicArray==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   
      for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
      {
         theApp.m_pLicArray[ii].m_iLicState=state;
         theApp.m_pLicArray[ii].m_iSecondsToKill=time_left;

// unsigned char str_buf[100];
// sprintf((char *)str_buf, "%d %d %d", ii, theApp.m_pLicArray[ii].m_iLicState, theApp.m_pLicArray[ii].m_iSecondsToKill);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
      }

      if(SUCCEEDED(retc)) retc=theApp.SaveLicences(True);
   
   } // if(num_of_lics && SUCCEEDED(retc))
   
   
// =============================================================
// if(SUCCEEDED(retc)) retc=TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, ini_fname);

   if(SUCCEEDED(retc)) if(!GetCurrentDirectory(KP_MAX_FNAME_LEN-1, (char *)cur_dir))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   if(SUCCEEDED(retc)) strcat(cur_dir, "\\");
   if(SUCCEEDED(retc)) retc=TvFnameSplit(cur_disk, cur_path, cur_name, cur_type, cur_dir);


   if(SUCCEEDED(retc))
   {
      strcpy(svr_fname, cur_disk);
      strcat(svr_fname, cur_path);
      if(strlen(svr_fname)>0) strcat(svr_fname, "\\");
      else retc=KP_E_DIR_ERROR;
      strcat(svr_fname, svr_name);
      strcat(svr_fname, ".exe");
      if(retc==KP_E_DIR_ERROR)
         retc=KpErrorProc.OutputErrorMessage(retc, svr_fname, True, __FILE__, __LINE__, 0L, NULL);
   }         

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
               KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
#endif               
            }
         }

         if(SUCCEEDED(retc))
         {   
            retw=RegSetValueEx(res_key,
               (const char *)svr_name,
               0L, REG_SZ,
               (const BYTE *)svr_fname,
               strlen(svr_fname));
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
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
            strcat(cmd_str, svr_name);
            strcat(cmd_str, " \"");
            strcat(cmd_str, cur_disk);
            strcat(cmd_str, cur_path);
            strcat(cmd_str, "\\WinNT\\SRVANY.EXE\"");
         }
// ------------------------------------
// Win2K      
         else
         {
// E:\kp\source\Tev\mokmat\Matau5e_v1.10b.serv\files\Win2K\INSTSRV.EXE matau5esvr E:\kp\source\Tev\mokmat\Matau5e_v1.10b.serv\files\Win2K\SRVANY.EXE
            strcat(cmd_str, "\\Win2K\\INSTSRV.EXE\" ");
            strcat(cmd_str, svr_name);
            strcat(cmd_str, " \"");
            strcat(cmd_str, cur_disk);
            strcat(cmd_str, cur_path);
            strcat(cmd_str, "\\Win2K\\SRVANY.EXE\"");
         }
// ------------------------------------
// WinNT & Win2K         

         if(SUCCEEDED(retc)) retc=StartCmdProcess(cmd_str, KPST_CUR_DIR, NULL, NULL, True, SW_MINIMIZE /* SW_SHOWDEFAULT */);

// ------------------------------------
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
               KpErrorProc.OutputErrorMessage(retc, retw, False, __FILE__, __LINE__, 0L, NULL);
#endif               
            }
         }

// KpMsgOut(svr_fname, IDI_ASTERISK, KP_MB_TESTI);

         if(SUCCEEDED(retc))
         {   
            retw=RegSetValueEx(res_key,
               "Application",
               0, REG_SZ,
               svr_fname,
               strlen(svr_fname));
            if(retw!=ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
         
      } // else // if(iWindowsVersion<WinNT)
   
   } // if(SUCCEEDED(retc))

   if(res_key)
   {
      retw=RegCloseKey(res_key);
      if(retw!=ERROR_SUCCESS)
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
      }
      res_key=0;
   }

// ==================================================
   if(SUCCEEDED(retc))
   {
      strcpy(svr_fname, cur_disk);
      strcat(svr_fname, cur_path);
      if(strlen(svr_fname)>0) strcat(svr_fname, "\\");
      strcat(svr_fname, svr_name);
      strcat(svr_fname, ".url");

      url_file=fopen((const char *)svr_fname, "w");
      if(url_file==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      fprintf(url_file, "[InternetShortcut]\n");
      fprintf(url_file, "URL=http://127.0.0.1:%d/\n", port);
      fprintf(url_file, "Modified=904D423E86BCC60166\n");
   
      if(ferror(url_file) || feof(url_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
      if(fclose(url_file)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      
// ===========================================         
   /* if(SUCCEEDED(retc)) */ retc0=theApp.CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc=retc0;

return(RET_CODE_WIN(retc));
}

