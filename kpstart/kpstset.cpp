// ---------------------------
// kpstset.cpp; setup.exe
// setup\setup.exe paleidëjas
// parenka setup_pl_1250.exe ar setup_pl_1257.exe
// 

// -----------------------------------------
#include "envir.h"
#include "iBshn.h"

#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>
#include <string>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
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
#if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */)
#include "setup_pl_1250.h"
#include "setup_pl_1257.h"
#endif

// -----------------------------------------
#if(MsgLang == KpLangRu_p)
#include "setup_ru_1251.h"
#include "setup_en.h"
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstset"; 
int iProdVerGlob = 0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;   
int iUpdNumGlob = -1;

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
HRESULT retc = S_OK;
static unsigned char cmd_str[KP_MAX_FNAME_LEN + 100];
static unsigned char cur_dir[KP_MAX_FNAME_LEN + 100];
HANDLE proc_id = NULL;
DWORD exit_code = 0L;
unsigned char *exe_ptr = null;
int size = 0;
FILE *exe_file = NULL;

// --------------------------------
   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);

// --------------------------------
// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir), KP_E_SYSTEM_ERROR, GetLastError(), True);
// cur_dir – ne darbinis, o kpstsel.exe paleidimo katalogas
   if(SUCCEEDED(retc)) retc = GetAppPath(cur_dir, False);
   
// netinka – neiðeina padaryt nebylaus Inno setupo be parametro /SILENT
#if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */ || (MsgLang == KpLangRu_p))
   if(SUCCEEDED(retc)) retc = GetLocalPath(cur_dir, KP_Temp_Dir, False);

   if(SUCCEEDED(retc))
   {
      strcpy(cmd_str, cur_dir);
      exe_ptr = null;
      
      switch(iMsgLangOff)
      {
#if(MsgLang == KpLangPl_p)
      case KpLangPl_1250: 
         strcat(cmd_str, "\\setup_pl_1250.exe");
         exe_ptr = setup_pl_1250;
         size = sizeof(setup_pl_1250); 
         break;
      case KpLangPl_1257: 
         strcat(cmd_str, "\\setup_pl_1257.exe"); 
         exe_ptr = setup_pl_1257; 
         size = sizeof(setup_pl_1257); 
         break;
      default: KP_ERROR(E_INVALIDARG, null); break;
#endif         
#if(MsgLang == KpLangRu_p)
      case KpLangRu_1251: 
         strcat(cmd_str, "\\setup_ru_1251.exe");
         exe_ptr = setup_ru_1251;
         size = sizeof(setup_ru_1251); 
         break;
      default: 
         strcat(cmd_str, "\\setup_en.exe"); 
         exe_ptr = setup_en; 
         size = sizeof(setup_en); 
         break;
#endif         
      }
   }

   if(SUCCEEDED(retc))
   {
      exe_file = fopen((const char *)cmd_str, "wb");
      KP_ASSERT(exe_file, KP_E_DIR_ERROR, GetLastError(), True);
   }
   if(SUCCEEDED(retc)) 
   {
      fwrite(exe_ptr, 1, size, exe_file);
      if(ferror(exe_file) || feof(exe_file)) KP_ERROR(KP_E_FERROR, GetLastError());
   }
   KP_ASSERT(!fclose(exe_file), KP_E_DIR_ERROR, GetLastError(), True); 

#else // #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p))

   if(SUCCEEDED(retc))
   {
      strcat(cur_dir, "\\setup");
      strcpy(cmd_str, cur_dir);

//    switch(iMsgLangOff)
      {
//    case KpLangPl_1250: strcat(cmd_str, "\\setup_pl_1250.exe"); break;
//    case KpLangPl_1257: strcat(cmd_str, "\\setup_pl_1257.exe"); break;
//    default: 
         strcat(cmd_str, "\\setup.exe"); 
//       break;
      }
   }
#endif // #else // #if((MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p))

   if(SUCCEEDED(retc)) retc = StartProcess(cmd_str, cur_dir, NULL, &proc_id, SW_SHOWNORMAL, False, False);

// Inno setupui reikia sulaukti, kol diegimas pasibaigs pilnai
// ir dël (MsgLang == KpLangPl_p) – po to trinsim 
   if(SUCCEEDED(retc)) do
   {
      Sleep(1000);
      
      KP_ASSERT(GetExitCodeProcess(proc_id, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), True);

   } while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));

#if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */)
   KP_ASSERT(DeleteFile((const char *)cmd_str), KP_E_DIR_ERROR, GetLastError(), True);
#endif
   
   /* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

return(RET_CODE_WIN(retc));
}
