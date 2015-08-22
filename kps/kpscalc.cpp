// kpscalc.cpp
// calc.exe paleidimas nepriklausomai nuo OS


// ------------------------------
#define STANDARD_VIEW // standard/scientific view

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpcolors.h"
#include "kpfonts.h"
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
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "kpstap.h"


// ----------------------------------------
const unsigned char lpszProdName[] = "kpscalc"; 
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
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
unsigned char cmd_dir[KP_MAX_FNAME_LEN+40+1];
const unsigned char *sys_boot;
DWORD thread_id;
HANDLE h_proc;
HWND wnd=NULL;
HDC dc;
int ii;
int wnd_x, wnd_y, wnd_dx, wnd_dy;
RECT rect;
FILE *in_file = NULL;
  
// --------------------------
   retc=KpInitWindows(hInstance);

// --------------------------
   if(SUCCEEDED(retc)) wnd=GetWindowByName((const unsigned char *)"Calculator", True);
      
   if((!wnd) && SUCCEEDED(retc))
   {
// --------------------------
      if(SUCCEEDED(retc)) retc = GetAppPath(cmd_dir, True);
      if(SUCCEEDED(retc))
      {
         strcat(cmd_dir, "calc.exe");
// KpMsgOut(cmd_dir, IDI_ASTERISK, KP_MB_TESTI);

         in_file = fopen((const char *)cmd_dir, "r");
         if(in_file)
         {
            fclose(in_file);

            retc = StartProcess(cmd_dir, (const unsigned char *)".", &thread_id, &h_proc, SW_SHOWNORMAL); // SW_SHOWDEFAULT);
         }
         else
         {
// --------------------------
            if(iWindowsVersion>=WinNT) sys_boot=(const unsigned char *)getenv("SystemRoot");
            else sys_boot=(const unsigned char *)getenv("WINBOOTDIR");
            if(sys_boot==NULL)
            {
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null /* GetLastError() */, False, __FILE__, __LINE__, 0L, NULL);
               retc = KP_E_SYSTEM_ERROR;
            }
      
            if(SUCCEEDED(retc))
            {
               strncpy(cmd_dir, sys_boot, KP_MAX_FNAME_LEN);
               cmd_dir[KP_MAX_FNAME_LEN]=Nul;
   
               if(iWindowsVersion>=WinNT) strcat(cmd_dir, "\\System32");
   
               strcat(cmd_dir, "\\calc.exe");
   
// --------------------------
               retc=StartProcess(cmd_dir, (const unsigned char *)".", &thread_id, &h_proc, SW_SHOWNORMAL); // SW_SHOWDEFAULT);
            }

         } // else // if(in_file)
         
      } // if(SUCCEEDED(retc))

   } // if((!wnd) && SUCCEEDED(retc))
   
// -------------------------- ieskom lango
   const unsigned char *wnd_name = (const unsigned char *)"Calculator";
   for (ii=0, wnd=NULL; (wnd==NULL) && (ii<10) && SUCCEEDED(retc); ii++)
   {
      Sleep(500);
      wnd = GetWindowByName(wnd_name, True);
   }
   if ((ii>=10) && SUCCEEDED(retc))
   {
      wnd_name = (const unsigned char *)"Skaièiuotuvas";
      for(ii=0, wnd=NULL; (wnd==NULL) && (ii<10) && SUCCEEDED(retc); ii++)
      {
         Sleep(500);
         wnd = GetWindowByName(wnd_name, True);
      }
   }
   if ((ii>=10) && SUCCEEDED(retc))
   {
      wnd_name = (const unsigned char *)"Kalkuliatorius";
      for(ii=0, wnd=NULL; (wnd==NULL) && (ii<10) && SUCCEEDED(retc); ii++)
      {
         Sleep(500);
         wnd = GetWindowByName(wnd_name, True);
      }
   }
   if ((ii>=10) && SUCCEEDED(retc))
   {
      KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, wnd_name, False, __FILE__, __LINE__, 0L, NULL);
      retc = KP_E_FILE_NOT_FOUND;
   }

// -------------------------- perjungiam i standard view
   if(SUCCEEDED(retc))
   {
//    PostMessage(wnd, WM_CHAR, '1', 0);
//    PostMessage(wnd, WM_CHAR, '2', 0);
//    PostMessage(wnd, WM_CHAR, '3', 0);

//    PostMessage(wnd, WM_KEYDOWN, VK_MENU, 1);
//    PostMessage(wnd, WM_SYSKEYDOWN, VK_MENU, 0x20380001);
//    Sleep(500);   

//    PostMessage(wnd, WM_CHAR, 'V', 0x20000000);
//    PostMessage(wnd, WM_KEYDOWN, 'V', 1); // 
//    PostMessage(wnd, WM_SYSKEYDOWN, 'V', 0x202f0001);
      PostMessage(wnd, WM_SYSCHAR, 0x76, 0x202f0001);
      PostMessage(wnd, WM_SYSCOMMAND, 0xf100, 0x76);
//    Sleep(100);   

//    PostMessage(wnd, WM_KEYUP, 'V', 0xC0000001); // 
//    PostMessage(wnd, WM_SYSKEYUP, 'V', 0xe02f0001);
//    Sleep(500);   

//    PostMessage(wnd, WM_KEYUP, VK_MENU, 0xC0000001);
//    PostMessage(wnd, WM_KEYUP, VK_MENU, 0xc0380001);
//    Sleep(500);
   
// -------------- standard view
#ifdef STANDARD_VIEW
//    PostMessage(wnd, WM_CHAR, 'T', 0);
      PostMessage(wnd, WM_SYSCHAR, 0x74, 0x20140001);
      PostMessage(wnd, WM_SYSCOMMAND, 0xf100, 0x74);
//    Sleep(100);   
#else
//    PostMessage(wnd, WM_CHAR, 'S', 0);
      PostMessage(wnd, WM_SYSCHAR, 0x73, 0x201F0001);
      PostMessage(wnd, WM_SYSCOMMAND, 0xf100, 0x73);
//    Sleep(100);   
#endif
   }

// -------------------------- ieskom lango dar karta
   wnd_name = (const unsigned char *)"Calculator";
   for(ii=0, wnd=NULL; (wnd==NULL) && (ii<10) && SUCCEEDED(retc); ii++)
   {
      Sleep(500);
      wnd = GetWindowByName(wnd_name, True);
   }
   if ((ii>=10) && SUCCEEDED(retc))
   {
      wnd_name = (const unsigned char *)"Skaièiuotuvas";
      for(ii=0, wnd=NULL; (wnd==NULL) && (ii<10) && SUCCEEDED(retc); ii++)
      {
         Sleep(500);
         wnd = GetWindowByName(wnd_name, True);
      }
   }
   if ((ii>=10) && SUCCEEDED(retc))
   {
      wnd_name = (const unsigned char *)"Kalkuliatorius";
      for(ii=0, wnd=NULL; (wnd==NULL) && (ii<10) && SUCCEEDED(retc); ii++)
      {
         Sleep(500);
         wnd = GetWindowByName(wnd_name, True);
      }
   }
   if ((ii>=10) && SUCCEEDED(retc))
   {
      KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, wnd_name, False, __FILE__, __LINE__, 0L, NULL);
      retc = KP_E_FILE_NOT_FOUND;
   }

// --------------------------
#if FALSE
   if(SUCCEEDED(retc))
   {
      dc=GetDC(wnd);
      if(dc==NULL)
      {
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         retc = KP_E_SYSTEM_ERROR;
      }
   }

   if(SUCCEEDED(retc))
   {
      wnd_dx=GetDeviceCaps(dc, HORZRES);
      wnd_dy=GetDeviceCaps(dc, VERTRES);
   }            
#endif

   if(SUCCEEDED(retc))
      if(!GetWindowRect(wnd, &rect))
      {
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         retc = KP_E_SYSTEM_ERROR;
      }

   if(SUCCEEDED(retc))
   {
      wnd_dx = rect.right-rect.left+1;
      wnd_dy = rect.bottom-rect.top+1;
   }


// --------------------------
   if(SUCCEEDED(retc))
   {
      dc = GetDC(HWND_DESKTOP);
      if(dc == NULL)
      {
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         retc = KP_E_SYSTEM_ERROR;
      }
   }

   if(SUCCEEDED(retc))
   {
      wnd_x = (GetDeviceCaps(dc, HORZRES)-wnd_dx);
      wnd_y = (GetDeviceCaps(dc, VERTRES)-wnd_dy);
   }            

// --------------------------
   if(SUCCEEDED(retc))
      if(!SetWindowPos(wnd, HWND_TOPMOST, wnd_x, wnd_y /* 0 */, wnd_dx, wnd_dy, SWP_SHOWWINDOW))
      {
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         retc = KP_E_SYSTEM_ERROR;
      }
   
/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_WIN(retc));
}
