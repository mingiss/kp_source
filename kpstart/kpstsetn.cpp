// ---------------------------
// kpstsetn.cpp; former kpstset3.cpp; setup.exe
// setup\setup.exe paleidëjas
// parenka setup_pl_1250.exe ar setup_pl_1257.exe
// 

// -----------------------------------------
#include "envir.h"

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
#include "kpcapp.h"
#include "tvmain.h"
#include "xmlp.h"
#include "kpstap.h"

// -----------------------------------------
#if NumOfParts > 9
#error NumOfParts > 9
#endif

#if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */)
#include "setup_pl_1250_1.h"
#include "setup_pl_1257_1.h"
#if  NumOfParts >= 2
#include "setup_pl_1250_2.h"
#include "setup_pl_1257_2.h"
#if  NumOfParts >= 3
#include "setup_pl_1250_3.h"
#include "setup_pl_1257_3.h"
#if  NumOfParts >= 4
#include "setup_pl_1250_4.h"
#include "setup_pl_1257_4.h"
#if  NumOfParts >= 5
#include "setup_pl_1250_5.h"
#include "setup_pl_1257_5.h"
#if  NumOfParts >= 6
#include "setup_pl_1250_6.h"
#include "setup_pl_1257_6.h"
#if  NumOfParts >= 7
#include "setup_pl_1250_7.h"
#include "setup_pl_1257_7.h"
#if  NumOfParts >= 8
#include "setup_pl_1250_8.h"
#include "setup_pl_1257_8.h"
#if  NumOfParts >= 9
#include "setup_pl_1250_9.h"
#include "setup_pl_1257_9.h"
#endif      
#endif      
#endif      
#endif      
#endif      
#endif      
#endif
#endif
#endif

#if((MsgLang == KpLangRu_p) /* || (MsgLang == KpLangRu_0_p) || (MsgLang == KpLangRu_1251_p) */)
#include "setup_ru_0_1.h"
#include "setup_ru_1251_1.h"
#if  NumOfParts >= 2
#include "setup_ru_0_2.h"
#include "setup_ru_1251_2.h"
#if  NumOfParts >= 3
#include "setup_ru_0_3.h"
#include "setup_ru_1251_3.h"
#if  NumOfParts >= 4
#include "setup_ru_0_4.h"
#include "setup_ru_1251_4.h"
#if  NumOfParts >= 5
#include "setup_ru_0_5.h"
#include "setup_ru_1251_5.h"
#if  NumOfParts >= 6
#include "setup_ru_0_6.h"
#include "setup_ru_1251_6.h"
#if  NumOfParts >= 7
#include "setup_ru_0_7.h"
#include "setup_ru_1251_7.h"
#if  NumOfParts >= 8
#include "setup_ru_0_8.h"
#include "setup_ru_1251_8.h"
#if  NumOfParts >= 9
#include "setup_ru_0_9.h"
#include "setup_ru_1251_9.h"
#endif      
#endif      
#endif      
#endif      
#endif      
#endif      
#endif
#endif
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
unsigned char *exe_ptr_1 = null;
int size_1 = 0;
#if  NumOfParts >= 2
unsigned char *exe_ptr_2 = null;
int size_2 = 0;
#if  NumOfParts >= 3
unsigned char *exe_ptr_3 = null;
int size_3 = 0;
#if  NumOfParts >= 4
unsigned char *exe_ptr_4 = null;
int size_4 = 0;
#if  NumOfParts >= 5
unsigned char *exe_ptr_5 = null;
int size_5 = 0;
#if  NumOfParts >= 6
unsigned char *exe_ptr_6 = null;
int size_6 = 0;
#if  NumOfParts >= 7
unsigned char *exe_ptr_7 = null;
int size_7 = 0;
#if  NumOfParts >= 8
unsigned char *exe_ptr_8 = null;
int size_8 = 0;
#if  NumOfParts >= 9
unsigned char *exe_ptr_9 = null;
int size_9 = 0;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
FILE *exe_file = NULL;

// --------------------------------
   if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);

// --------------------------------
// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir), KP_E_SYSTEM_ERROR, GetLastError(), True);
// cur_dir – ne darbinis, o kpstsel.exe paleidimo katalogas
//  if(SUCCEEDED(retc)) retc = GetAppPath(cur_dir, False);
   
// netinka – neiðeina padaryt nebylaus Inno setupo be parametro /SILENT
#if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */ || (MsgLang == KpLangRu_p) /* || (MsgLang == KpLangRu_0_p) || (MsgLang == KpLangRu_1251_p) */)
   if(SUCCEEDED(retc)) retc = GetLocalPath(cur_dir, KP_Temp_Dir, False);

   if(SUCCEEDED(retc))
   {
      strcpy(cmd_str, cur_dir);
      exe_ptr_1 = null;
#if  NumOfParts >= 2
      exe_ptr_2 = null;
#if  NumOfParts >= 3
      exe_ptr_3 = null;
#if  NumOfParts >= 4
      exe_ptr_4 = null;
#if  NumOfParts >= 5
      exe_ptr_5 = null;
#if  NumOfParts >= 6
      exe_ptr_6 = null;
#if  NumOfParts >= 7
      exe_ptr_7 = null;
#if  NumOfParts >= 8
      exe_ptr_8 = null;
#if  NumOfParts >= 9
      exe_ptr_9 = null;
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
      
      switch(iMsgLangOff)
      {
#if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */)
      case KpLangPl_1250: 
         strcat(cmd_str, "\\setup_pl_1250.exe");

         exe_ptr_1 = setup_pl_1250_1;
         size_1 = sizeof(setup_pl_1250_1); 
#if  NumOfParts >= 2
         exe_ptr_2 = setup_pl_1250_2;
         size_2 = sizeof(setup_pl_1250_2); 
#if  NumOfParts >= 3
         exe_ptr_3 = setup_pl_1250_3;
         size_3 = sizeof(setup_pl_1250_3); 
#if  NumOfParts >= 4
         exe_ptr_4 = setup_pl_1250_4;
         size_4 = sizeof(setup_pl_1250_4); 
#if  NumOfParts >= 5
         exe_ptr_5 = setup_pl_1250_5;
         size_5 = sizeof(setup_pl_1250_5); 
#if  NumOfParts >= 6
         exe_ptr_6 = setup_pl_1250_6;
         size_6 = sizeof(setup_pl_1250_6); 
#if  NumOfParts >= 7
         exe_ptr_7 = setup_pl_1250_7;
         size_7 = sizeof(setup_pl_1250_7); 
#if  NumOfParts >= 8
         exe_ptr_8 = setup_pl_1250_8;
         size_8 = sizeof(setup_pl_1250_8); 
#if  NumOfParts >= 9
         exe_ptr_9 = setup_pl_1250_9;
         size_9 = sizeof(setup_pl_1250_9); 
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
         break;

      case KpLangPl_1257: 
         strcat(cmd_str, "\\setup_pl_1257.exe"); 

         exe_ptr_1 = setup_pl_1257_1; 
         size_1 = sizeof(setup_pl_1257_1); 
#if  NumOfParts >= 2
         exe_ptr_2 = setup_pl_1257_2; 
         size_2 = sizeof(setup_pl_1257_2); 
#if  NumOfParts >= 3
         exe_ptr_3 = setup_pl_1257_3; 
         size_3 = sizeof(setup_pl_1257_3); 
#if  NumOfParts >= 4
         exe_ptr_4 = setup_pl_1257_4; 
         size_4 = sizeof(setup_pl_1257_4); 
#if  NumOfParts >= 5
         exe_ptr_5 = setup_pl_1257_5; 
         size_5 = sizeof(setup_pl_1257_5); 
#if  NumOfParts >= 6
         exe_ptr_6 = setup_pl_1257_6; 
         size_6 = sizeof(setup_pl_1257_6); 
#if  NumOfParts >= 7
         exe_ptr_7 = setup_pl_1257_7; 
         size_7 = sizeof(setup_pl_1257_7); 
#if  NumOfParts >= 8
         exe_ptr_8 = setup_pl_1257_8; 
         size_8 = sizeof(setup_pl_1257_8); 
#if  NumOfParts >= 9
         exe_ptr_9 = setup_pl_1257_9; 
         size_9 = sizeof(setup_pl_1257_9); 
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
         break;
#endif // #if((MsgLang == KpLangPl_p) /* || (MsgLang == KpLangPl_1250_p) || (MsgLang == KpLangPl_1257_p) */)

#if((MsgLang == KpLangRu_p) /* || (MsgLang == KpLangRu_0_p) || (MsgLang == KpLangRu_1251_p) */)
      case KpLangRu_0: 
         strcat(cmd_str, "\\setup_ru_0.exe");

         exe_ptr_1 = setup_ru_0_1;
         size_1 = sizeof(setup_ru_0_1); 
#if  NumOfParts >= 2
         exe_ptr_2 = setup_ru_0_2;
         size_2 = sizeof(setup_ru_0_2); 
#if  NumOfParts >= 3
         exe_ptr_3 = setup_ru_0_3;
         size_3 = sizeof(setup_ru_0_3); 
#if  NumOfParts >= 4
         exe_ptr_4 = setup_ru_0_4;
         size_4 = sizeof(setup_ru_0_4); 
#if  NumOfParts >= 5
         exe_ptr_5 = setup_ru_0_5;
         size_5 = sizeof(setup_ru_0_5); 
#if  NumOfParts >= 6
         exe_ptr_6 = setup_ru_0_6;
         size_6 = sizeof(setup_ru_0_6); 
#if  NumOfParts >= 7
         exe_ptr_7 = setup_ru_0_7;
         size_7 = sizeof(setup_ru_0_7); 
#if  NumOfParts >= 8
         exe_ptr_8 = setup_ru_0_8;
         size_8 = sizeof(setup_ru_0_8); 
#if  NumOfParts >= 9
         exe_ptr_9 = setup_ru_0_9;
         size_9 = sizeof(setup_ru_0_9); 
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
         break;

      case KpLangRu_1251: 
         strcat(cmd_str, "\\setup_ru_1251.exe"); 

         exe_ptr_1 = setup_ru_1251_1; 
         size_1 = sizeof(setup_ru_1251_1); 
#if  NumOfParts >= 2
         exe_ptr_2 = setup_ru_1251_2; 
         size_2 = sizeof(setup_ru_1251_2); 
#if  NumOfParts >= 3
         exe_ptr_3 = setup_ru_1251_3; 
         size_3 = sizeof(setup_ru_1251_3); 
#if  NumOfParts >= 4
         exe_ptr_4 = setup_ru_1251_4; 
         size_4 = sizeof(setup_ru_1251_4); 
#if  NumOfParts >= 5
         exe_ptr_5 = setup_ru_1251_5; 
         size_5 = sizeof(setup_ru_1251_5); 
#if  NumOfParts >= 6
         exe_ptr_6 = setup_ru_1251_6; 
         size_6 = sizeof(setup_ru_1251_6); 
#if  NumOfParts >= 7
         exe_ptr_7 = setup_ru_1251_7; 
         size_7 = sizeof(setup_ru_1251_7); 
#if  NumOfParts >= 8
         exe_ptr_8 = setup_ru_1251_8; 
         size_8 = sizeof(setup_ru_1251_8); 
#if  NumOfParts >= 9
         exe_ptr_9 = setup_ru_1251_9; 
         size_9 = sizeof(setup_ru_1251_9); 
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
         break;
#endif // #if((MsgLang == KpLangRu_p) /* || (MsgLang == KpLangRu_0_p) || (MsgLang == KpLangRu_1251_p) */)

      default: KP_ERROR(E_INVALIDARG, null); break;
      }
   }

   if(SUCCEEDED(retc))
   {
      exe_file = fopen((const char *)cmd_str, "wb");
      KP_ASSERT(exe_file, KP_E_DIR_ERROR, GetLastError(), True);
   }
   if(SUCCEEDED(retc)) 
   {
      fwrite(exe_ptr_1, 1, size_1, exe_file);
#if  NumOfParts >= 2
      fwrite(exe_ptr_2, 1, size_2, exe_file);
#if  NumOfParts >= 3
      fwrite(exe_ptr_3, 1, size_3, exe_file);
#if  NumOfParts >= 4
      fwrite(exe_ptr_4, 1, size_4, exe_file);
#if  NumOfParts >= 5
      fwrite(exe_ptr_5, 1, size_5, exe_file);
#if  NumOfParts >= 6
      fwrite(exe_ptr_6, 1, size_6, exe_file);
#if  NumOfParts >= 7
      fwrite(exe_ptr_7, 1, size_7, exe_file);
#if  NumOfParts >= 8
      fwrite(exe_ptr_8, 1, size_8, exe_file);
#if  NumOfParts >= 9
      fwrite(exe_ptr_9, 1, size_9, exe_file);
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
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
