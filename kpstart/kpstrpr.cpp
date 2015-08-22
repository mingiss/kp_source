// ---------------------------
// kpstrpr.cpp; Pradzia.exe
// flash'o TevAutoRun.ini vienkartinis paleidejas
//

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
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
#include "xmlg.h"
#include "kpstap.h"

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstrpr"; 
int iProdVerGlob = 0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;   
int iUpdNumGlob = -1;

int KpHp11NumOfExtFun = 0;
KpHp11ExtFun KpHp11ExtFunTab[1] =
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[] =
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
#if FALSE
FILE *autorun_file = NULL;
unsigned char in_str[KP_MAX_FILE_LIN_LEN+1];
unsigned char cmd_str[KP_MAX_FILE_LIN_LEN+1];
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
#endif
TevAutorunPars autorun_pars;

// ------------------------------- 
   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);
   
// --------------------------------
#if FALSE
   if(SUCCEEDED(retc))
   {
//    strcpy(cmd_str, "autorun.inf");
      strcpy(cmd_str, "TevAutorun.inf");
      autorun_file = fopen((const char *)cmd_str, "r");
      if(!autorun_file)
         retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null, True, __FILE__, __LINE__, 0L, NULL);
   }      

   if(SUCCEEDED(retc)) do
   {
      fgets((char *)in_str, KP_MAX_FILE_LIN_LEN, autorun_file);
      if(ferror(autorun_file))
         retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) if(feof(autorun_file)) retc = KP_E_EOF;

      if(SUCCEEDED(retc))
      {
         pnts = in_str;
         pntd = cmd_str;
         while((*pnts) && (*pnts != '='))
         {
            if(*pnts != Spc) *pntd++ = tolower(*pnts);
            pnts++; 
         }
         *pntd = Nul;
      }         
      
      if(SUCCEEDED(retc)) if((strcmp(cmd_str, "open")==0) && (*pnts == '='))
      {
         pnts++;
         while(*pnts == Spc) pnts++;
               
         pntd = (unsigned char *)pnts;
               
         while((*pntd) && (*pntd != Cr) && (*pntd!=Lf)) pntd++;
         *pntd = Nul;

         strcpy(cmd_str, pnts);
         retc=StartProcess(cmd_str, KPST_CUR_DIR, NULL, NULL, SW_SHOWNORMAL); // SW_SHOW);
      }
                                 
   } while(SUCCEEDED(retc));
   
   if(retc == KP_E_EOF) retc = S_OK;
      
   if(autorun_file)
   {
      fclose(autorun_file);
      autorun_file = NULL;
   }
#endif

   if(SUCCEEDED(retc)) retc = ParseTevAutorun(KPST_CUR_DIR, &autorun_pars, False);

   if((autorun_pars.m_lpszOpen[0] != Nul) && SUCCEEDED(retc))
   {
static unsigned char cmd_line[KP_MAX_FNAME_LEN + 1];
      strcpy(cmd_line, autorun_pars.m_lpszOpen);
       
static unsigned char dir_buf[KP_MAX_FNAME_LEN + 1];
      strcpy(dir_buf, KPST_CUR_DIR);
      if(strchr(cmd_line, '\\') != null)
      {
static unsigned char cmd_disk[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_path[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_name[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_type[KP_MAX_FTYPE_LEN + 1];

         retc = TvFnameSplit(cmd_disk, cmd_path, cmd_name, cmd_type, cmd_line);
         if(SUCCEEDED(retc))
         { 
            strcpy(dir_buf, cmd_disk);
            strcat(dir_buf, cmd_path);
         } 
      }
PutLogMessage_("WinMain(): [%s] [%s]", cmd_line, dir_buf);
   
      retc = StartProcess(cmd_line, (autorun_pars.m_lpszStartIn[0] != Nul)?autorun_pars.m_lpszStartIn:dir_buf, NULL, NULL, SW_SHOWNORMAL); // SW_SHOW);
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_WIN(retc));
}

