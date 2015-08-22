// ---------------------------
// kpstrtc.cpp; PradziaTc.exe
// TrueCrypt tomo montuotojas
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>
#include <richedit.h>
#include <richedit.h>
#include <time.h>
#include <string>

#include "kpstdlib.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpstdio.h"
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

#include "kpstrtc.h"


// -----------------------------------------
const unsigned char lpszProdName[] = "kpstrtc"; 
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
bool bServiceFl=False;   
int iCurFontSize=22;

int KpHp11NumOfExtFun=0;
KpHp11ExtFun KpHp11ExtFunTab[1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
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
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
static unsigned char temp_path[KP_MAX_FNAME_LEN+1];
static unsigned char tc_exe_fname[KP_MAX_FNAME_LEN+1];
static unsigned char tc_sys_fname[KP_MAX_FNAME_LEN+1];
static unsigned char fnam_buf[KP_MAX_FNAME_LEN+1];
static unsigned char par_buf[KP_MAX_FNAME_LEN+1];
FILE *out_file=NULL;
unsigned char *pnts;

// ------------------------------- 
   if(SUCCEEDED(retc)) retc=KpInitWindows(hInstance);
   
// --------------------------------
   if(SUCCEEDED(retc)) retc = GetLocalPath(temp_path, KP_Temp_Dir, True);
   
// --------------------------------
   if(SUCCEEDED(retc)) strcpy(tc_exe_fname, temp_path);
 
   if(SUCCEEDED(retc)) retc=TvUniFname.Generate(fnam_buf);
   if(SUCCEEDED(retc))
   {
      pnts=strchr(fnam_buf, '.');
      if(pnts) *pnts=Nul;
   }
   
   if(SUCCEEDED(retc)) if(strlen(tc_exe_fname) + strlen(fnam_buf) >= KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) strcat(tc_exe_fname, fnam_buf);

   if(SUCCEEDED(retc))
   {
      pnts = (unsigned char *)".exe";
      if(strlen(tc_exe_fname) + strlen(pnts) >= KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcat(tc_exe_fname, pnts);
   
   if(SUCCEEDED(retc))
   {
      out_file=fopen((const char *)tc_exe_fname, "wb");
      if(out_file==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null /* tc_exe_fname */, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(fwrite(TrueCryptExeImg, 1, sizeof(TrueCryptExeImg), out_file) != sizeof(TrueCryptExeImg))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if(feof(out_file) || ferror(out_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   
   if(out_file!=NULL)
      if(fclose(out_file)!=0)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   out_file=NULL;   

// --------------------------------
   if(SUCCEEDED(retc)) strcpy(tc_sys_fname, temp_path);
 
   if(SUCCEEDED(retc))
   {
      pnts = (unsigned char *)"truecrypt.sys";
      if(strlen(tc_sys_fname) + strlen(pnts) >= KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcat(tc_sys_fname, pnts);
   
   if(SUCCEEDED(retc))
   {
      out_file=fopen((const char *)tc_sys_fname, "wb");
      if(out_file==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null /* tc_sys_fname */, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
      if(fwrite(TrueCryptSysImg, 1, sizeof(TrueCryptSysImg), out_file) != sizeof(TrueCryptSysImg))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      if(feof(out_file) || ferror(out_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   
   if(out_file!=NULL)
      if(fclose(out_file)!=0)
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=retc0;
      }
   out_file=NULL;   

// --------------------------------
   if(SUCCEEDED(retc)) strcpy(fnam_buf, tc_exe_fname);

   if(SUCCEEDED(retc))
   {
      par_buf[0] = ' '; 
      par_buf[1] = '/'; 
      par_buf[2] = 'a'; 
      par_buf[3] = ' '; 
      par_buf[4] = '/'; 
      par_buf[5] = 'q'; 
      par_buf[6] = ' '; 
      par_buf[7] = '/'; 
      par_buf[8] = 's'; 
      par_buf[9] = ' ';  
      par_buf[10] = '/';  
      par_buf[11] = 'v';  
      par_buf[12] = ' ';  
      par_buf[13] = 'v';  
      par_buf[14] = 'o';  
      par_buf[15] = 'l';  
      par_buf[16] = '.';  
      par_buf[17] = 't';  
      par_buf[18] = 'c';  
      par_buf[19] = ' ';  
      par_buf[20] = '/';  
      par_buf[21] = 'p';  
      par_buf[22] = ' ';  
      par_buf[23] = 'a';  
      par_buf[24] = '7';  
      par_buf[25] = 'Y';  
      par_buf[26] = 'f';  
      par_buf[27] = '3';  
      par_buf[28] = 'L';  
      par_buf[29] = 'E';  
      par_buf[30] = 'u';  
      par_buf[31] = '9';  
      par_buf[32] = 'w';  
      par_buf[33] = 'k';  
      par_buf[34] = ' ';  
      par_buf[35] = '/';  
      par_buf[36] = 'm';  
      par_buf[37] = ' ';   
      par_buf[38] = 'r';  
      par_buf[39] = 'o';  
      par_buf[40] = Nul;  
       
      if(strlen(fnam_buf) + strlen(par_buf) >= KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcat(fnam_buf, par_buf);

   if(SUCCEEDED(retc)) retc = StartProcess(fnam_buf, KPST_CUR_DIR, NULL, NULL, SW_SHOWMINIMIZED);
      

// !!! TODO:   sulaukt, kol pasibaigs.
//             tada ismontuot ir ismest failus tc_exe_fname ir tc_sys_fname 

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_WIN(retc));
}

