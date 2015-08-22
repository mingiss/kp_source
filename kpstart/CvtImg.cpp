#include "envir.h"
#include "iBshn.h"

#include <string>
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
/*
#include "kpstdlib.h"
#include "kpsort.h"
*/
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstmsg.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "CvtImg";
int iProdVerGlob = 0;
int iUpdNumGlob = -1;

KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;

int KpHp11NumOfExtFun = 0;
KpHp11ExtFun KpHp11ExtFunTab[1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   NULL
};


KpCommonApp theApp;


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
HANDLE proc = NULL;

// ------------------------
   theApp.InitCommonApp(hInstance, lpCmdLine);

HWND msg_wnd = NULL;
   KpMsgOut((const unsigned char *)"Paveikslëliai konvertuojami...", IDI_INFORMATION, KP_MB_NONE, &msg_wnd);

// ------------------------
HCURSOR cur_sav;
   cur_sav = GetCursor();
HCURSOR cursor;
   cursor = LoadCursor(hInstance, IDC_WAIT);
   SetCursor(cursor);

// ------------------------
unsigned char dir_buf[KP_MAX_FNAME_LEN + 1];
   GetAppPath(dir_buf, False);

const unsigned char *src_dir = null;
const unsigned char *dest_dir = null;
const unsigned char *dest_img_dir = null;
   if(theApp.m_plCmdLineArgs != NULL)
   {
      src_dir = (const unsigned char *)theApp.m_plCmdLineArgs->GetValue();
      KP_ASSERT(src_dir != null, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc))
      {
         if(strlen(src_dir) <= KP_MAX_FNAME_LEN) strcpy(dir_buf, src_dir);
      
KpTreeEntry *dest_dir_par = NULL;
//    theApp.m_plCmdLineArgs->GetFirstChild(&dest_dir_par);
         dest_dir_par = theApp.m_plCmdLineArgs->m_pFirstChild; 
      
         if(dest_dir_par != NULL)
         {
            dest_dir = (const unsigned char *)dest_dir_par->GetValue();

//          dest_dir_par->GetFirstChild(&dest_dir_par);
            dest_dir_par = dest_dir_par->m_pFirstChild; 

            if(dest_dir_par != NULL)
               dest_img_dir = (const unsigned char *)dest_dir_par->GetValue();
         }
      }
   }
   
   SetCurrentDirectory((const char *)dir_buf);

// ------------------------
   StartProcess((const unsigned char *)"\\DAT0\\ImageMagick-6.7.3-1\\mogrify.exe -format pdf *.jpg", KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED); 
   if(proc != NULL) WaitForProcessEnd(proc, NULL);
#if FALSE
   StartProcess((const unsigned char *)"\\DAT0\\ImageMagick-6.7.3-1\\mogrify.exe -format pdf *.tif", KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
   if(proc != NULL) WaitForProcessEnd(proc, NULL);
   StartProcess((const unsigned char *)"\\DAT0\\ImageMagick-6.7.3-1\\mogrify.exe -format pdf *.bmp", KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
   if(proc != NULL) WaitForProcessEnd(proc, NULL);
   StartProcess((const unsigned char *)"\\DAT0\\ImageMagick-6.7.3-1\\mogrify.exe -format pdf *.png", KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
   if(proc != NULL) WaitForProcessEnd(proc, NULL);
   StartProcess((const unsigned char *)"\\DAT0\\ImageMagick-6.7.3-1\\mogrify.exe -format pdf *.gif", KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
   if(proc != NULL) WaitForProcessEnd(proc, NULL);
#endif

// apjungimo failas
SYSTEMTIME sys_time;
   GetSystemTime(&sys_time);

unsigned char comb_file[KP_MAX_FNAME_LEN + 1];
   sprintf((char *)comb_file, "Nuotraukos_%04d.%02d.%02d_%02d%02d%02d.pdf", 
      sys_time.wYear, sys_time.wMonth, sys_time.wDay,
      sys_time.wHour + 2, sys_time.wMinute, sys_time.wSecond);

// apjungiam
unsigned char cmd_line[KP_MAX_FNAME_LEN + 200];
   strcpy(cmd_line, "\\DAT0\\pdftk-1.44\\pdftk.exe *.pdf cat output ");
   strcat(cmd_line, comb_file); 
   
   StartProcess(cmd_line, KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
   if(proc != NULL) WaitForProcessEnd(proc, NULL);

// ------------------------
   if((src_dir != null) && (dest_dir != null) && (dest_img_dir != null))
   {
      strcpy(cmd_line, "move /Y \"");
      strcat(cmd_line, src_dir);
      strcat(cmd_line, "\\"); 
      strcat(cmd_line, comb_file); // strcat(cmd_line, "*.pdf"); 
      strcat(cmd_line, "\" \"");
      strcat(cmd_line, dest_dir);
      strcat(cmd_line, "\"");
      
//    StartProcess(cmd_line, KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
//    if(proc != NULL) WaitForProcessEnd(proc, NULL);
      system((const char *)cmd_line);

// ------------------------
      strcpy(cmd_line, "move /Y \"");
      strcat(cmd_line, src_dir);
      strcat(cmd_line, "\\*\" \"");
      strcat(cmd_line, dest_img_dir);
      strcat(cmd_line, "\"");
      
//    StartProcess(cmd_line, KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
//    if(proc != NULL) WaitForProcessEnd(proc, NULL);
      system((const char *)cmd_line);

// ------------------------
      strcpy(cmd_line, "del /Q \"");
      strcat(cmd_line, dest_img_dir);
      strcat(cmd_line, "\\*.pdf\"");
      
//    StartProcess(cmd_line, KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
//    if(proc != NULL) WaitForProcessEnd(proc, NULL);
      system((const char *)cmd_line);
   }

// ------------------------
   else if((src_dir != null) && (dest_dir != null))
   {
unsigned char cmd_line[KP_MAX_FNAME_LEN + 1];
      strcpy(cmd_line, "move /Y \"");
      strcat(cmd_line, src_dir);
      strcat(cmd_line, "\\*\" \"");
      strcat(cmd_line, dest_dir);
      strcat(cmd_line, "\"");
      
//    StartProcess(cmd_line, KP_CUR_DIR, NULL, &proc, SW_SHOWMINIMIZED);
//    if(proc != NULL) WaitForProcessEnd(proc, NULL);
      system((const char *)cmd_line);
   }

// ------------------------
   SetCursor(cur_sav);

// ------------------------
   if(msg_wnd != NULL) ::DestroyWindow(msg_wnd);
   KpMsgOut((const unsigned char *)"Konvertavimas baigtas", IDI_INFORMATION, KP_MB_BAIGTI);

   theApp.CloseCommonApp();

return(RET_CODE_WIN(S_OK));
}
