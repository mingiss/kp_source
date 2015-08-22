// ---------------------------
// kpstw.cpp
// winword paleidimas PDF-iniø projektø redaktoriui
// nustato Wordo User Templates katalogà á aktyvø katalogà - èia yra lokalus Normal.dot
// pervadinti i stword.exe
// stword.exe -w    sukuria tik paleidimo failà stword.ini, kuriame áraðo registre rastà paskutinio ofiso numerá.
// Jeigu reikia, stword.ini galima pataisyt (pvz., jei ofisas 8.0, o papildomai koks nors 9.0 MS Exchange be Wordo
// Jeigu stword.ini nëra - tada stword.exe ieðko registre per visus ámanomus MS Office, kaip ir stword.exe -w
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <string>
#include <fstream>
#if CompilerGr != Watcom
#include <sstream>
#endif
#include <unistd.h>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kperr.h"
#include "kpsock.h"
#include "kpcapp.h"
#include "kpstap.h"



// -----------------------------------------
#define KPSTW_INI_FNAME ("stword.ini") // ("kpstw.ini")
#define AT_PDF_INI_FNAME ("A-T-PDF.ini")
#define PDF_MAKER_INI_FNAME ("PDF-T-Maker.ini")
#define PDF_MAKER_DOT_FNAME ("PDF-T-Maker.dot")
#define NORMAL_DOT_FNAME ("normal")
#define NORMAL_DOT_FTYPE ("dot")

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstw";
int iProdVerGlob = 0;
KpErrorProc_tag KpErrorProc(True, 71);
bool bServiceFl=False;

// -----------------------------------------
KpCommonApp KpStWord;


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
unsigned char cmd_buf[KP_MAX_FNAME_LEN+1];
   cmd_buf[0]=Nul;
unsigned char key_name[KP_MAX_FNAME_LEN+1];
int off_num = 0;
int off_num_min = 1;
int off_num_max = 20;
HANDLE proc_id = NULL;
DWORD exit_code;
LONG retw=ERROR_SUCCESS;
HKEY hKey=NULL;
DWORD dwBufLen;
DWORD dwValType;
DWORD dwDisposition;
// UniChar templ_path_buf[KP_MAX_FNAME_LEN+1];
// KpChar templ_path_buf[KP_MAX_FNAME_LEN+1];
static unsigned char templ_path_buf[KP_MAX_FNAME_LEN+50+1];
static unsigned char app_data_path_buf[KP_MAX_FNAME_LEN+50+1];
static unsigned char src_fname[KP_MAX_FNAME_LEN+100+1];
static unsigned char dest_fname[KP_MAX_FNAME_LEN+100+1];
// static unsigned char cmd_buf[2*KP_MAX_FNAME_LEN+100+1];
char opt;
bool write_ini_only = False;
bool retb;
DWORD retv;
DWORD ll;
// extern char *optarg;
static unsigned char prod_name[KP_MAX_FNAME_LEN+1]; // parametras ið cmd line


   if(SUCCEEDED(retc)) retc = KpStWord.GetOpenResult();

// if(SUCCEEDED(retc)) retc = KpInitWindows(hInstance);
   if(SUCCEEDED(retc)) retc = KpStWord.InitCommonApp(hInstance, GetCommandLine() /* lpCmdLine */);

   write_ini_only = False;
   prod_name[0] = Nul;

   while (((opt = getopt(KpStWord.m_iArgc, (char * const *)KpStWord.m_plpszArgv, "wp:")) != EOF) && SUCCEEDED(retc))
   {
      switch (opt)
      {
         case 'w':
            write_ini_only = True;
            break;
         case 'p':
            if((prod_name[0]) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            if((optarg == NULL) && SUCCEEDED(retc))
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
// stringstream str_stream;
// str_stream << hex << (long)prod_name_ptr;
// KpMsgOut(str_stream.str(), IDI_ASTERISK, KP_MB_TESTI);

               strncpy(prod_name, optarg, KP_MAX_FNAME_LEN);
               prod_name[KP_MAX_FNAME_LEN] = Nul;
            }
            break;
         default:
            retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);
            break;
      }
   }


// --------------------------- ieskom wordo, diegimo vieta --> cmd_buf, ofiso numeris --> off_num
   if(SUCCEEDED(retc))
   {
fstream in_file(KPSTW_INI_FNAME, ios::in);
      if(!in_file.fail())
      {
         in_file >> off_num;
         if(!in_file.fail()) off_num_min = off_num_max = off_num;
         else
            retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, KPSTW_INI_FNAME, True, __FILE__, __LINE__, 0L, NULL);
         in_file.close();
      }
      else
      {
         off_num_min = 1;
         off_num_max = 20;
      }
   }


// --------------------------- ieskom wordo, diegimo vieta --> cmd_buf, ofiso numeris --> off_num
   if(SUCCEEDED(retc))
   {
      for(off_num = off_num_max; off_num >= off_num_min; off_num--)
      {
         retc=S_OK;
         sprintf((char *)key_name, "SOFTWARE\\Microsoft\\Office\\%d.0\\Common\\InstallRoot", off_num); // "SOFTWARE\\Microsoft\\Office\\Common\\InstallRoot", jei Office 97, off_num == 7 ? 
         retw=RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, KEY_QUERY_VALUE, &hKey);
         if(retw==ERROR_SUCCESS) break;
         else retc=KP_E_KWD_NOT_FOUND;
      }
      if((hKey == NULL) || (retc==KP_E_KWD_NOT_FOUND))
      {
         KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         if(off_num_min > 1)
         {
stringstream str_stream;
            str_stream << "Nerandu Microsoft Office " << off_num_min << ".0";
            KpMsgOut(str_stream.str(), IDI_ERROR, KP_MB_BAIGTI);
         }
         else KpMsgOut("Jûsø kompiuteryje nëra në vienos paþástamos Microsoft Office versijos.", IDI_ERROR, KP_MB_BAIGTI);
      }
   }

   if(SUCCEEDED(retc))
   {
      dwBufLen=KP_MAX_FNAME_LEN;
      retw=RegQueryValueEx(hKey, "Path", NULL, &dwValType, (LPBYTE)cmd_buf, &dwBufLen);
      if((dwValType != REG_SZ) || (retw != ERROR_SUCCESS))
      {
         cmd_buf[0]=Nul;
         retc = KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(hKey)
   {
      retw=RegCloseKey(hKey);
#ifdef Debug
      if(retw!=ERROR_SUCCESS)
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
#endif
      hKey=NULL;
   }


// ---------------------------
   if(SUCCEEDED(retc))
   {
      if(write_ini_only)
      {
fstream out_file(KPSTW_INI_FNAME, ios::out);
         if(out_file.fail())
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, KPSTW_INI_FNAME, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            out_file << off_num << endl;
            if(out_file.fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, KPSTW_INI_FNAME, True, __FILE__, __LINE__, 0L);
            out_file.close();
            if(out_file.fail())
               retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, KPSTW_INI_FNAME, True, __FILE__, __LINE__, 0L);
         }
      }
      else // if(write_ini_only)
      {

// --------------------------- UserTemplates raktas
         if(SUCCEEDED(retc))
         {
            retc = S_OK;
            sprintf((char *)key_name, "SOFTWARE\\Microsoft\\Office\\%d.0\\Common\\General", off_num);
            retw = RegOpenKeyEx(HKEY_CURRENT_USER, (LPCTSTR)key_name, 0, KEY_QUERY_VALUE|KEY_SET_VALUE, &hKey);
            if(retw != ERROR_SUCCESS)
            {
               retw = RegCreateKeyEx(HKEY_CURRENT_USER, (LPCTSTR)key_name, 0, NULL, REG_OPTION_NON_VOLATILE,
                  KEY_READ | KEY_WRITE, NULL, &hKey, &dwDisposition);
               if(retw != ERROR_SUCCESS)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, True, __FILE__, __LINE__, 0L, NULL);
            }
         }

#if TRUE
// --------------------------- nauja UserTemplates reikðmë - aktyvus katalogas
//       if(SUCCEEDED(retc))
//       {
//          ll = GetFullPathName(".", KP_MAX_FNAME_LEN, (char *)templ_path_buf, NULL);
//          if(!ll)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//          else(ll >= KP_MAX_FNAME_LEN)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
//       }

// --------------------------- nauja UserTemplates reikðmë - "C:\Users\xxx\AppData\Roaming\Microsoft\Templates\" + "TEV\"
         if(SUCCEEDED(retc))
         {
            retc = GetLocalPath(templ_path_buf, KP_Application_Data);
// KpMsgOut(templ_path_buf, IDI_ASTERISK, KP_MB_TESTI);
         }
         if(SUCCEEDED(retc))
         {
            strcat(templ_path_buf, "Microsoft\\Templates\\"); // standartinë Templates vieta
            strcat(templ_path_buf, "TEV\\");
            if(prod_name[0]){ strcat(templ_path_buf, prod_name); strcat(templ_path_buf, "\\"); }
            retc = CreatePath(templ_path_buf, False);
         }
         if(SUCCEEDED(retc))
         {
            strcpy(src_fname, NORMAL_DOT_FNAME);
            if(prod_name[0]){ strcat(src_fname, "_"); strcat(src_fname, prod_name); }
            strcat(src_fname, ".");
            strcat(src_fname, NORMAL_DOT_FTYPE);

            strcpy(dest_fname, templ_path_buf);
            strcat(dest_fname, NORMAL_DOT_FNAME);
            strcat(dest_fname, ".");
            strcat(dest_fname, NORMAL_DOT_FTYPE);

            if(!CopyFile((const char *)src_fname, (const char *)dest_fname, False))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }

// --------------------------- iðsaugojam senà ir áraðom naujà UserTemplates
         if(SUCCEEDED(retc))
         {
            templ_path_buf[KP_MAX_FNAME_LEN] = Nul;
            retc = KpRegSetValue(hKey, "UserTemplates", REG_EXPAND_SZ, (LPBYTE)templ_path_buf, strlen(templ_path_buf) + 1);
         }

#else // #if TRUE
         if(SUCCEEDED(retc))
         {
            dwBufLen = KP_MAX_FNAME_LEN; // *sizeof(KpChar); // *sizeof(UniChar);
            retw = RegQueryValueEx(hKey, "UserTemplates_sav", NULL, &dwValType, (LPBYTE)templ_path_buf, &dwBufLen);
            if(retw != ERROR_SUCCESS)
            {
// -------------- seno UserTemplates_sav dar nëra - saugojam
               dwBufLen = KP_MAX_FNAME_LEN; // *sizeof(KpChar); // *sizeof(UniChar);
               retw = RegQueryValueEx(hKey, "UserTemplates", NULL, &dwValType, (LPBYTE)templ_path_buf, &dwBufLen);
               if(retw == ERROR_SUCCESS) // jei dar nëra nustatyto - nër kà saugot
               {

// char str_buf[100];
// sprintf(str_buf, "%x %x %x", dwValType, REG_EXPAND_SZ, retw);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);

                  if((dwValType != REG_EXPAND_SZ) || (retw != ERROR_SUCCESS))
                  {
                     templ_path_buf[0]=Nul;
                     retc = KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, True, __FILE__, __LINE__, 0L, NULL);
                  }

                  if(SUCCEEDED(retc))
                  {
                     retw = RegSetValueEx(hKey, "UserTemplates_sav", 0L, dwValType, (LPBYTE)templ_path_buf, dwBufLen);
                     if(retw != ERROR_SUCCESS)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                  }
               }
            }
         }


// --------------------------- nauja UserTemplates reikðmë - aktyvus katalogas
         if(SUCCEEDED(retc))
         {
            ll = GetFullPathName(".", KP_MAX_FNAME_LEN, (char *)templ_path_buf, NULL);
            if(!ll)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            else if(ll >= KP_MAX_FNAME_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L, NULL);
         }

// --------------------------- áraðom naujà UserTemplates

// unsigned char str_buf[100];
// KptUnicodeToStr(str_buf, templ_path_buf, 71);
// KptStrDecode(str_buf, templ_path_buf, 71);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
// KpMsgOut(templ_path_buf, IDI_ASTERISK, KP_MB_TESTI);

         if(SUCCEEDED(retc))
         {
            dwValType = REG_EXPAND_SZ;
            templ_path_buf[KP_MAX_FNAME_LEN] = Nul;
            dwBufLen = strlen(templ_path_buf)+1;

            retw = RegSetValueEx(hKey, "UserTemplates", 0L, dwValType, (LPBYTE)templ_path_buf, dwBufLen);
            if(retw != ERROR_SUCCESS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
         }
#endif // #else // #if TRUE

// --------------------------- kopijuojam A-T-PDF.ini ir PDF-T-Maker.dot
         if(SUCCEEDED(retc))
         {
            retc = GetLocalPath(app_data_path_buf, KP_Application_Data);
// KpMsgOut(app_data_path_buf, IDI_ASTERISK, KP_MB_TESTI);
         }
         if(SUCCEEDED(retc))
         {
            strcat(app_data_path_buf, "Microsoft\\Word\\");
            retc = CreatePath(app_data_path_buf, False);
         }
         if(SUCCEEDED(retc))
         {
            strcpy(dest_fname, app_data_path_buf);
            strcat(dest_fname, AT_PDF_INI_FNAME);
// fstream at_pdf_ini_file(dest_fname, ios_base::in);
//          if(at_pdf_ini_file.failed())
               retb = CopyFile(AT_PDF_INI_FNAME, (const char *)dest_fname, True);
            if(!retb)
            {
               retv = GetLastError();
               if(retv != ERROR_FILE_EXISTS)
                  /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_FERROR, retv, True, __FILE__, __LINE__, 0L, NULL);
            }
         }
         if(SUCCEEDED(retc))
         {
            strcpy(dest_fname, app_data_path_buf);

            strcat(dest_fname, PDF_MAKER_INI_FNAME);
            if(!CopyFile(PDF_MAKER_INI_FNAME, (const char *)dest_fname, False))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(retc))
         {
            strcpy(dest_fname, app_data_path_buf);
            strcat(dest_fname, "STARTUP\\");
            retc = CreatePath(dest_fname, False);
         }
         if(SUCCEEDED(retc))
         {
            strcat(dest_fname, PDF_MAKER_DOT_FNAME);
            if(!CopyFile(PDF_MAKER_DOT_FNAME, (const char *)dest_fname, False))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }


// --------------------------- paleidþiam Wordà
         if(SUCCEEDED(retc))
         {
            strcat(cmd_buf, "winword.exe");
            retc=StartCmdProcess(cmd_buf, KPST_CUR_DIR, NULL, &proc_id, True, SW_SHOWDEFAULT);
         }
         if((proc_id==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

         if(SUCCEEDED(retc)) do
         {
            if(!GetExitCodeProcess(proc_id, &exit_code))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         } while((exit_code==STILL_ACTIVE) && SUCCEEDED(retc));


// --------------------------- atstatom UserTemplates
#if TRUE
         if(hKey /* && SUCCEEDED(retc) */)
         {
            retc0 = KpRegRestore(hKey, "UserTemplates");
            if(SUCCEEDED(retc)) retc = retc0;
         }

#else // #if TRUE
         retc0 = S_OK;
         if(SUCCEEDED(retc0))
         {
            dwBufLen = KP_MAX_FNAME_LEN; // *sizeof(KpChar); // *sizeof(UniChar);
            retw = RegQueryValueEx(hKey, "UserTemplates_sav", NULL, &dwValType, (LPBYTE)templ_path_buf, &dwBufLen);
            if(retw == ERROR_SUCCESS)
            {
               if((dwValType != REG_EXPAND_SZ) || (retw != ERROR_SUCCESS))
               {
                  templ_path_buf[0]=Nul;
                  retc0 = KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, True, __FILE__, __LINE__, 0L, NULL);
               }

               if(SUCCEEDED(retc0))
               {
                  retw = RegSetValueEx(hKey, "UserTemplates", 0L, dwValType, (LPBYTE)templ_path_buf, dwBufLen);
                  if(retw != ERROR_SUCCESS)
                     retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
               }

               if(SUCCEEDED(retc0))
               {
                  retw = RegDeleteValue(hKey, "UserTemplates_sav");
                  if(retw != ERROR_SUCCESS)
                     retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
               }
            }
            else // if(retw == ERROR_SUCCESS)
            {
// ----------------------- UserTemplates nebuvo - tai ir vël iðtrinam
               retw = RegDeleteValue(hKey, "UserTemplates");
               if(retw != ERROR_SUCCESS)
                  retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
            }
         }

         if(SUCCEEDED(retc)) retc = retc0;

#endif // #else // #if TRUE


// -----------------------
         if(hKey)
         {
            retw=RegCloseKey(hKey);
#ifdef Debug
            if(retw!=ERROR_SUCCESS)
               KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
#endif
            hKey=NULL;
         }

// -----------------------
      } // else // if(write_ini_only)

   } // if(SUCCEEDED(retc))


// -----------------------
// retc0 = KpFinitWindows();
   retc0 = KpStWord.CloseCommonApp();
   if(SUCCEEDED(retc)) retc = retc0;

// -----------------------
// if(SUCCEEDED(retc)) retc = KpMsgOut("Jau", IDI_ASTERISK, KP_MB_TESTI);

return(RET_CODE_WIN(retc));
}

