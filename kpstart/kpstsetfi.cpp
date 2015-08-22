// ---------------------------
// kpstsetfi.cpp; former kpstsetfi3.cpp; setup.exe
// individualus atmintuko atnaujintojas
//
// prikabinama priekaba – .ini failas su UserData = "DAT9,DAT10 global.AI_e=SdS('OU04LTYyODAxLTk4Njc=') MT9SVK.ini,MT9SVK.ini.sav,MT10SVK.ini,MT10SVK.ini.sav 2"
//    pirmas elementas – atmintuko pakatalogiø sàraðas (skirtukai kableliai be tarpø), kuriuose reikia koreguoti failus AR6/reader/Javascripts/R__svarbiinfo.js
//    antras – atm. lic. id. kintamojo uþkoduota eilutë, kurià reikia áraðyti á atitinkamus R__svarbiinfo.js
//    treèias – .ini failø vardø sàraðas, kuriuose reikia perkelti senus UserData ir áraðyti atmintukø kodus (AdminPwd ir FlashID) ið prikabinto .ini failo
//       á .sav failus UserData neáraðomi; failø vardai atskirti kableliais, jokiø tarpø 
//    ketvirtas – minimalus ProdVar, randamas ið R__svarbiibfo.js; R__svarbiibfo.js ieðkom ið katalogo pirmo parametro pirmoje dalyje (DAT9) 
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
#include "kpstmsg.h"
#include "kpstmsg_en.h"
#include "kpstmsg_lt.h"
#include "kpstmsg_pl_1250.h"
#include "kpstmsg_pl_1257.h"
#include "kpstmsg_ru.h"

#include "setup_1.h"
#if  NumOfParts >= 2
#include "setup_2.h"
#  if  NumOfParts >= 3
#include "setup_3.h"
#     if  NumOfParts >= 4
#include "setup_4.h"
#     endif
#  endif
#endif

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstsetfi4"; 
int iProdVerGlob = 0;
KpErrorProcClass KpErrorProc(True, 71);
bool bServiceFl = False;   
int iUpdNumGlob = -1;

KpStApp theApp;

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_5+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,

   CheckResRequest_RC,
   CheckRelRequest_RC,

   InitRestDays_RC,
   ResumeRestDays_RC,
   ProcessRestDays_RC,

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
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
static unsigned char cmd_str[KP_MAX_FNAME_LEN * 2 + 1];
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
#endif
#endif
#endif
FILE *exe_file = NULL;
const unsigned char *pnts = null;
unsigned char *pntd = null;
static unsigned char prod_name_orig[KP_MAX_FNAME_LEN + 1];
static unsigned char vol_name_orig[KP_MAX_FNAME_LEN + 1];
int prod_ver_orig = 0;
int prod_ver_found = 0;
long flash_id_upd = 0L;
long flash_id_found = 0L;
static unsigned char flash_lic_upd[KP_KWD_LEN + 1];
static unsigned char flash_lic_found[KP_KWD_LEN + 1];
static unsigned char upd_pars[KP_MAX_FILE_LIN_WDT + 1]; // èia parametrai updeitinimui ið prikabinto .ini failo
static unsigned char user_data_found[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char str_buf[200];
unsigned char *ini_list_ptr;
unsigned char **ini_fnames_arr = NULL; // atnaujinamø .ini failø vardø porø masyvas ("MT9>MT9SVK", "MT10>MT10SVK")
int f_num; // atnaujinamø .ini failø vardø porø skaièius
int ii;
unsigned char *prodvar_ptr = null;
int prod_var_upd = 0;
int prod_var_found = 0;
static unsigned char js_fname[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1]; // m_lpszFlashDevName[] ir upd_pars[] (m_lpszUserData[]) ilgiø suma 
unsigned char *js_cont = NULL;
long js_len = 0L;


// --------------------------------
   theKpStAppPtr = &theApp;

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetOpenResult();

   if(SUCCEEDED(retc)) retc = GetIniFname(ini_fname);

// if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);
// kpstsetfi*.ini prie nieko nepririðtas, dabar atmintuko dar neieðkos
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->InitStApp(hInstance, ini_fname, lpCmdLine, KpStarterMode);

// -------------------------------- atsimenam hardkodintus kpstsetfi*.ini seno ieðkomo projekto duomenis
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdName(prod_name_orig);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdVer(&prod_ver_orig);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniVolName(vol_name_orig); // èia ieðkomo produkto ProjID (*.ini failo atmintuke vardas)

#if FALSE // èia dar nieko neieðkojom
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniFlashId(&flash_id_found);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniAdminPwd(flash_lic_found);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniUserData(user_data_found);
#endif

// --------------------------------
// skaitom prikabintà .ini failà su ieðkomo konkretaus atmintuko duomenø
   if(SUCCEEDED(retc))
   {
      strcpy(ini_fname, theKpStAppPtr->m_lpszAttFname);
      strcat(ini_fname, KPST_INI_FILE_TYPE); // gal reikëtø iðsitraukti ið m_Ini.m_lpszAttExt[] su GetIniAttExt()

      retc = theKpStAppPtr->LoadIniFile(ini_fname, True);
      if(SUCCEEDED(retc))
      {
// ------------------- skaitom updeito duomenis
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniFlashId(&flash_id_upd);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniAdminPwd(flash_lic_upd);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniUserData(upd_pars);
      
// surandam atnaujinamo projekto ProjID (.ini failo vardà)
//       if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniVolName(vol_name_orig);
         strcpy(theKpStAppPtr->m_lpszIniFName, vol_name_orig);
         strcat(theKpStAppPtr->m_lpszIniFName, KPST_INI_FILE_TYPE);

// ------------------------
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniProdName(prod_name_orig); // atstatom source projekto vardà
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniProdVer(prod_ver_orig);

         if(SUCCEEDED(retc)) retc = theKpStAppPtr->TestFlash();

// skaitom rasto atmintuko duomenis
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniFlashId(&flash_id_found);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniAdminPwd(flash_lic_found);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniUserData(user_data_found);

// ----------------------------- tikrinam userio parametrus (po TestFlash() .ini perskaitytas ið atmintuko)
         if(SUCCEEDED(retc)) if((flash_id_upd != flash_id_found) || (strcmp(flash_lic_upd, flash_lic_found) != 0))
         {
            sprintf((char *)str_buf, (const char *)KPST_MSG_BAD_FLASH, flash_lic_upd); 
//          KP_ERROR(KP_E_SYSTEM_ERROR, str_buf);
            KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
            retc = KP_E_FILE_NOT_FOUND;
         } 
         
#if FALSE // atnaujinsim visus failus ið sàraðo treèiam parametre upd_pars 
         if(SUCCEEDED(retc)) // papildom flash .ini failo vardà vëlesniam kopijavimui
         {
            strcpy(theKpStAppPtr->m_lpszIniFName, theKpStAppPtr->m_lpszFlashDevName);
            strcat(theKpStAppPtr->m_lpszIniFName, "\\");
            strcat(theKpStAppPtr->m_lpszIniFName, vol_name_orig);
            strcat(theKpStAppPtr->m_lpszIniFName, KPST_INI_FILE_TYPE);
         }
                  
// gràþinam atgal á hardkodiná
         retc0 = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, // èia tik fiktyvus vardas, reikia, kad theKpStAppPtr->m_lpszIniFName nepasikeistø 
                                                False); if(SUCCEEDED(retc)) retc = retc0;
#endif
      
      } // if(SUCCEEDED(retc)) // retc = theKpStAppPtr->LoadIniFile(ini_fname, True); 
   }

// ------------------------------------------ Tikrinam ProdVar
   if(SUCCEEDED(retc))
   {
// skanuojam min. ProdVar
      prodvar_ptr = strchr(upd_pars, Spc);
      if(prodvar_ptr)
      {
         prodvar_ptr = strchr(prodvar_ptr + 1, Spc);
         if(prodvar_ptr)
         {
            prodvar_ptr = strchr(prodvar_ptr + 1, Spc);
            if(prodvar_ptr)
            {
               *prodvar_ptr++ = Nul;
               sscanf((char *)prodvar_ptr, "%d", &prod_var_upd);

// ----- ieðkom atmintuko ProdVar
// produkto katalogas               
               strcpy(js_fname, theKpStAppPtr->m_lpszFlashDevName);
               strcat(js_fname, "\\");

               pnts = js_fname + strlen(js_fname); 
               strcat(js_fname, upd_pars);
               pntd = strchr(pnts, ',');
               if(pntd) *pntd = Nul;                
               pntd = strchr(pnts, Spc);
               if(pntd) *pntd = Nul;                
            
               KP_ASSERT(strlen(js_fname) + 1 + strlen(KPST_ACROREAD60_PATHNAME_SHORT) + strlen(JS_SUB_PATH_4) + strlen(JS_SVARBIINFO_FLASH) <= KP_MAX_FNAME_LEN,
                  KP_E_BUFFER_OVERFLOW, null, True);

// R__svarbiinfo.js kelias
               if(SUCCEEDED(retc))
               {
                  strcat(js_fname, "\\");
                  strcat(js_fname, KPST_ACROREAD60_PATHNAME_SHORT);
                  strcat(js_fname, JS_SUB_PATH_4);
                  strcat(js_fname, JS_SVARBIINFO_FLASH);
               }

// skaitom R__svarbiinfo.js
               if(SUCCEEDED(retc)) retc = ReadFileContents(js_fname, &js_cont, &js_len, True, False);
               KP_ASSERT(js_cont, KP_E_SYSTEM_ERROR, null, True);

// skanuojam atmintuko ProdVer
               if(SUCCEEDED(retc))
               {
                  prodvar_ptr = strstr(js_cont, JS_PRODVER_NAME);
                  if(prodvar_ptr)
                  {
                     prodvar_ptr += strlen(JS_PRODVER_NAME);
                     sscanf((char *)prodvar_ptr, "%d", &prod_ver_found);

                  } // if(prodvar_ptr)
            
               } // if(SUCCEEDED(retc))

// skanuojam atmintuko ProdVar
               if(SUCCEEDED(retc))
               {
                  prodvar_ptr = strstr(js_cont, JS_PRODVAR_NAME);
                  if(prodvar_ptr)
                  {
                     prodvar_ptr += strlen(JS_PRODVAR_NAME);
                     sscanf((char *)prodvar_ptr, "%d", &prod_var_found);
                  
                     if((prod_ver_found == prod_ver_orig) && (prod_var_found < prod_var_upd))
                     {
                        KpMsgOut(KPST_MSG_BAD_PRODVAR, IDI_ERROR, KP_MB_BAIGTI);
                        retc = KP_E_FILE_FORMAT;
                     }
            
                  } // if(prodvar_ptr)
            
               } // if(SUCCEEDED(retc))
               
               KP_DELETEA(js_cont);
            
            } // if(prodvar_ptr)
      
         } // if(prodvar_ptr)

      } // if(prodvar_ptr)

   } // if(SUCCEEDED(retc))

// -------------------------------- atkabinam áhardkodintà updeito setupà
   if(SUCCEEDED(retc)) retc = GetLocalPath(cur_dir, KP_Temp_Dir, False);

   if(SUCCEEDED(retc))
   {
      strcpy(cmd_str, cur_dir);
      pntd = cmd_str + strlen(cmd_str);
      *pntd++ = '\\'; // strcat(cmd_str, "\\");
      
      if(SUCCEEDED(retc)) retc = TvUniFname.Generate(pntd);
      if(SUCCEEDED(retc))
      {
         pntd = strchr(pntd, '.');
         if(pntd) strcpy(pntd, ".exe"); // ".bin"); // kaþkodël vël neveikia .bin
      }
      
      exe_ptr_1 = setup_1;
      size_1 = sizeof(setup_1); 
#if  NumOfParts >= 2
      exe_ptr_2 = setup_2;
      size_2 = sizeof(setup_2); 
#if  NumOfParts >= 3
      exe_ptr_3 = setup_3;
      size_3 = sizeof(setup_3); 
#if  NumOfParts >= 3
      exe_ptr_4 = setup_4;
      size_4 = sizeof(setup_4); 
#endif      
#endif      
#endif      
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
#endif      
#endif      
#endif      
      if(ferror(exe_file) || feof(exe_file)) KP_ERROR(KP_E_FERROR, GetLastError());
   }
   KP_ASSERT(!fclose(exe_file), KP_E_DIR_ERROR, GetLastError(), True); 

// --------------------------------- paleidþiam atkabintà updeito setupà
   if(SUCCEEDED(retc)) /* retc = */ StartProcess(cmd_str, cur_dir, NULL, &proc_id, SW_SHOWNORMAL, False, False);
// if(SUCCEEDED(retc)) retc = StartCmdProcess(cmd_str, cur_dir, NULL, &proc_id, True, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);

// -------------------- reikia sulaukti, kol diegimas pasibaigs pilnai – po to trinsim
// if(SUCCEEDED(retc)) /* retc = */ WaitForProcessEnd(proc_id, NULL);
   if(SUCCEEDED(retc))
   {
      do
      {
         Sleep(1000);
      
         KP_ASSERT(GetExitCodeProcess(proc_id, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), True);

      } while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));

      Sleep(5000);
      
      retc = S_OK;
   }
   

// -----------------------------------------  kopijuojam priekabos pririðtà .ini
#if FALSE // nekopijuosim, o taisysim suinstaliuotus naujus pagal sàraðà ið treèio parametro upd_pars
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(ini_fname, True);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUserData(user_data_found);
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile(ini_fname);

   KP_ASSERT(SetFileAttributes((const char *)theKpStAppPtr->m_lpszIniFName, FILE_ATTRIBUTE_NORMAL), KP_E_DIR_ERROR, GetLastError(), True);
   KP_ASSERT(CopyFile((const char *)ini_fname, (const char *)theKpStAppPtr->m_lpszIniFName, False), KP_E_FERROR, GetLastError(), True);
   KP_ASSERT(SetFileAttributes((const char *)theKpStAppPtr->m_lpszIniFName, FILE_ATTRIBUTE_HIDDEN /* | FILE_ATTRIBUTE_READONLY */), KP_E_DIR_ERROR, GetLastError(), True);
   
   if(SUCCEEDED(retc)) strcat(theKpStAppPtr->m_lpszIniFName, ".sav");   
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUserData((const unsigned char *)"");
   if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile(ini_fname);

   KP_ASSERT(SetFileAttributes((const char *)theKpStAppPtr->m_lpszIniFName, FILE_ATTRIBUTE_NORMAL), KP_E_DIR_ERROR, GetLastError(), True);
   KP_ASSERT(CopyFile((const char *)ini_fname, (const char *)theKpStAppPtr->m_lpszIniFName, False), KP_E_FERROR, GetLastError(), True);
   KP_ASSERT(SetFileAttributes((const char *)theKpStAppPtr->m_lpszIniFName, FILE_ATTRIBUTE_HIDDEN /* | FILE_ATTRIBUTE_READONLY */), KP_E_DIR_ERROR, GetLastError(), True);
#endif

// ------------------------------------------ updeitinam .ini failus ið sàraðo upd_pars gale
#if FALSE // dabar jau kitaip, èia buvo tik dvigubø atmintukø antros dalies .ini failø pakoregavimas – "DAT9,DAT10 global.AI_e=SdS('OU04LTYyODAxLTk4Njc=') MT10.ini,MT10.ini.sav"
   if(SUCCEEDED(retc))
   {
      ini_list_ptr = strchr(upd_pars, Spc);
      if(ini_list_ptr)
      {
         ini_list_ptr = strchr(ini_list_ptr + 1, Spc);
         if(ini_list_ptr)
         {
            *ini_list_ptr++ = Nul;
            
            retc = SplitStrings(&ini_fnames_arr, &f_num, ini_list_ptr, (const unsigned char *)",", True);
            
            for(ii = 0; (ii < f_num) && SUCCEEDED(retc); ii++)
            {
               strcpy(ini_fname, theKpStAppPtr->m_lpszFlashDevName);
               strcat(ini_fname, ini_fnames_arr[ii]);

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(ini_fname, True);

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniFlashId(flash_id_upd);
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniAdminPwd(flash_lic_upd);

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile(ini_fname);

               KP_ASSERT(SetFileAttributes((const char *)ini_fname, FILE_ATTRIBUTE_HIDDEN /* | FILE_ATTRIBUTE_READONLY */), KP_E_DIR_ERROR, GetLastError(), True);
            
            } // for(ii = 0; (ii < f_num) && SUCCEEDED(retc); ii++)
         
            KP_DELETEA(ini_fnames_arr);
         
         } // if(ini_list_ptr)
         
      } // if(ini_list_ptr)
   
   } // if(SUCCEEDED(retc))   
#endif

// analizuojam upd_pars atnaujinamø .ini failø sàraðo 
   if(SUCCEEDED(retc))
   {
      ini_list_ptr = strchr(upd_pars, Spc);
      if(ini_list_ptr)
      {
         ini_list_ptr = strchr(ini_list_ptr + 1, Spc);
         if(ini_list_ptr)
         {
            *ini_list_ptr++ = Nul;
// skaidom sàraðà
            retc = SplitStrings(&ini_fnames_arr, &f_num, ini_list_ptr, (const unsigned char *)",", True);
            
            for(ii = 0; (ii < f_num) && SUCCEEDED(retc); ii++)
            {
// skaidom updeitinamø .ini failø sàraðà

               strcpy(ini_fname, theKpStAppPtr->m_lpszFlashDevName);
               strcat(ini_fname, "\\");
               strcat(ini_fname, ini_fnames_arr[ii]);
            
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->LoadIniFile(ini_fname, True, True);

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniFlashId(flash_id_upd);
               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniAdminPwd(flash_lic_upd);
               
               if(SUCCEEDED(retc)) if(strstr(ini_fname, ".sav") == null)  
                  retc = theKpStAppPtr->SetIniUserData(user_data_found);
PutLogMessage_("--- 1 %s %x %s %x", ini_fname, retc, flash_lic_upd, flash_id_upd);

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile(ini_fname);

               KP_ASSERT(SetFileAttributes((const char *)ini_fname, FILE_ATTRIBUTE_HIDDEN /* | FILE_ATTRIBUTE_READONLY */), KP_E_DIR_ERROR, GetLastError(), True);

            } // for(ii = 0; (ii < f_num) && SUCCEEDED(retc); ii++)
         
            KP_DELETEA(ini_fnames_arr);
         
         } // if(ini_list_ptr)
         
      } // if(ini_list_ptr)
   
   } // if(SUCCEEDED(retc))   


// -----------------------------------------  trinam update setupo failà
   KP_ASSERT(DeleteFile((const char *)cmd_str), KP_E_DIR_ERROR, GetLastError(), True);

// gràþinam atgal á hardkodiná
   retc0 = theKpStAppPtr->LoadIniFile(theKpStAppPtr->m_lpszIniFName, // èia tik fiktyvus vardas, reikia, kad theKpStAppPtr->m_lpszIniFName nepasikeistø 
                                          False); if(SUCCEEDED(retc)) retc = retc0;

// ----------------------------------------- áraðom uþkoduotà lic. kodà á R__svarbiinfo.js
   if(SUCCEEDED(retc)) theKpStAppPtr->CorFlashUpdLicId(upd_pars);     

// -----------------------------------------   
/* if(SUCCEEDED(retc)) */ retc0 = theKpStAppPtr->CloseStApp(retc, KP_My_Documents);  if(SUCCEEDED(retc)) retc = retc0;
// /* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

   if(SUCCEEDED(retc)) KpMsgOut(KPST_MSG_UPDATE_FINISHED, IDI_ASTERISK, KP_MB_BAIGTI);

return(RET_CODE_WIN(retc));
}
