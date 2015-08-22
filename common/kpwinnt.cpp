//----------------------------------
// kpwinnt.cpp
// common WinNT things
//


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <ctype.h>
#include <string>
#include <stdio.h>
#include <iostream.h>
#include <fstream>
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
#include <windows.h>
// #include <windowsx.h>
#include <richedit.h>
#include <Richole.h>
#include <psapi.h>
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"


// ----------------------------
#if Compiler != Msvc60
int GetProcessIdByName(const unsigned char *lpszExeFName)
{
HRESULT retc=S_OK;
static DWORD proc_id_arr[400];
DWORD ret_size;
int num_of_proc = 0;
int ret_val = 0;
HANDLE proc;
static unsigned char exefname[KP_MAX_FNAME_LEN+1];
int ii;
const unsigned char *pnts;

   if(SUCCEEDED(retc))
      if(!EnumProcesses(proc_id_arr, sizeof(proc_id_arr), &ret_size))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) num_of_proc = ret_size / sizeof(proc_id_arr[0]);
   
   for(ii=0; (ii < num_of_proc) && (!ret_val) && SUCCEEDED(retc); ii++)
   {
      proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ /* PROCESS_QUERY_LIMITED_INFORMATION */, 
         True, proc_id_arr[ii]);
      if(proc != 0)
      {
#if FALSE
// tik Vistoj
         ret_size = KP_MAX_FNAME_LEN;
         if(QueryFullProcessImageName(proc, 0, exefname, &ret_size))
#else          
         if(GetModuleFileNameEx(proc, 0, (char *)exefname, KP_MAX_FNAME_LEN))
#endif         
         {   
// KpMsgOut(exefname, IDI_ASTERISK, KP_MB_TESTI);
            pnts = strstr(exefname, lpszExeFName);
            if(pnts) if(strlen(pnts) == strlen(lpszExeFName)) 
            {
               if(pnts > exefname)
               {
                  if(*(pnts-1) == '\\')
                  {
                     ret_val = proc_id_arr[ii];
                     break;
                  }
               }
               else
               {
                  ret_val = proc_id_arr[ii];
                  break;
               }
            }
         }
      }
   }

return(ret_val);
}
#endif
