// -----------------------------------------
// rez.cpp, perdarytas is test_md.cpp
// dabar rez.exe reikia pervadinti i test_kd.exe
// glob.js gelbetojas (starteris kai nuluzta ir nesurenka duomenu)
// pervadinti i rez.exe
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <windows.h>

#include "kpstdlib.h"
#include "kpstdio.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpcapp.h"
#include "kpstap.h"


// -----------------------------------------
// #define LOG_FILE_NAME  ((const unsigned char *)"rez.log")
#define LOG_FILE_NAME  ((const unsigned char *)"test_kd.log")


class test : public KpStApp
{
public:
   HRESULT PrintCompData(FILE *log_file);

} test_app;


// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
int SortMode=KP_LNG_LIT;
KpStApp theApp;
KpStApp *theKpStAppPtr = &theApp;

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// -----------------------------------------
void dump_string(FILE *log_file, const unsigned char *str_buf)
{
const unsigned char *pnts=str_buf;

   while(*pnts) fprintf(log_file, "%03o", (*pnts++)+100);
   fprintf(log_file, "\n");
}


// -----------------------------------------
HRESULT test::PrintCompData(FILE *log_file)
{
HRESULT retc=S_OK;
unsigned char str_buf[KP_MAX_FNAME_LEN*2+100];
DWORD ll;

   fprintf(log_file, "------------------------------\n");

// kompo ID                                                                                    
   retc=GetSavedCompID();
   if((m_iCompId==0) && SUCCEEDED(retc)) retc=GetPhysCompId();
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+m_iCompId);

// kompo vardas            
   if(SUCCEEDED(retc))
   {
      ll=KP_MAX_FNAME_LEN;
      if(!GetComputerName((char *)str_buf, &ll))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc))
   {
      str_buf[KP_MAX_FNAME_LEN]=Nul;
//    fprintf(log_file, (char *)str_buf);
//    fprintf(log_file, "\n");
      dump_string(log_file, str_buf);
   }

// user name            
   if(SUCCEEDED(retc))
   {
      ll=KP_MAX_FNAME_LEN;
      if(!GetUserName((char *)str_buf, &ll))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc))
   {
      str_buf[KP_MAX_FNAME_LEN]=Nul;
//    fprintf(log_file, (char *)str_buf);
//    fprintf(log_file, "\n");
      dump_string(log_file, str_buf);
   }
              
// windows version
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+iWindowsVersion);

// service pack
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+iWindowsSP);

// os platform OSVERSIONINFOEX
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+Osvi.dwPlatformId);

// os major version OSVERSIONINFOEX
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+Osvi.dwMajorVersion);

// os minor version OSVERSIONINFOEX
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+Osvi.dwMinorVersion);

// os version OSVERSIONINFOEX
// if(SUCCEEDED(retc)) fprintf(log_file, Osvi.szCSDVersion);
// if(SUCCEEDED(retc)) fprintf(log_file, "\n");
   if(SUCCEEDED(retc)) dump_string(log_file, (const unsigned char *)Osvi.szCSDVersion);

// os build no OSVERSIONINFOEX
   if(SUCCEEDED(retc)) fprintf(log_file, "%o\n", 10000+Osvi.dwBuildNumber);

return(retc);
}


// -----------------------------------------
int main(void)
{
HRESULT retc=S_OK;
FILE *log_file=NULL;

unsigned char full_js_name[KP_MAX_FNAME_LEN+1];
FILE *glob_js_file=NULL;
unsigned char in_ch;
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char name[KP_MAX_FNAME_LEN+1];
unsigned char type[KP_MAX_FTYPE_LEN+1];

   if(SUCCEEDED(retc)) retc=KpInitWindows(NULL);


// -----------------------
   if(SUCCEEDED(retc)) 
   {
      log_file=fopen((const char *)LOG_FILE_NAME, "w");
      if(log_file==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
   }
   
// -----------------------
   if(SUCCEEDED(retc)) retc=theApp.GetGlobalJsName(full_js_name);

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- Main file:\n");
      glob_js_file=fopen((const char *)full_js_name, "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, full_js_name);
   if(SUCCEEDED(retc))
   {
      strcpy(full_js_name, disk);
      strcat(full_js_name, path);
      strcat(full_js_name, "\\");
      strcat(full_js_name, name);
      strcat(full_js_name, ".sav");
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- Saved file:\n");
      glob_js_file=fopen((const char *)full_js_name, "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- bebreg_b.dat:\n");
      glob_js_file=fopen((const char *)"C:\\arkim\\rezultatai\\bebreg_b.dat", "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- bebreg_j.dat:\n");
      glob_js_file=fopen((const char *)"C:\\arkim\\rezultatai\\bebreg_j.dat", "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- bebreg_s.dat:\n");
      glob_js_file=fopen((const char *)"C:\\arkim\\rezultatai\\bebreg_s.dat", "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- bebras_b.dat:\n");
      glob_js_file=fopen((const char *)"C:\\arkim\\rezultatai\\bebras_b.dat", "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- bebras_j.dat:\n");
      glob_js_file=fopen((const char *)"C:\\arkim\\rezultatai\\bebras_j.dat", "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc))
   {
      fprintf(log_file, "-------------- bebras_s.dat:\n");
      glob_js_file=fopen((const char *)"C:\\arkim\\rezultatai\\bebras_s.dat", "r");
      if(glob_js_file==NULL) fprintf(log_file, "--------------    not found.\n");
      else
      {
         while(SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) in_ch=fgetc(glob_js_file);
            
            if(SUCCEEDED(retc)) if(ferror(glob_js_file))
            {
               fprintf(log_file, "\n-------------    input error.\n");
               retc=KP_E_FERROR;
            }
            if(SUCCEEDED(retc)) if(feof(glob_js_file)) retc=KP_E_EOF;

            if(SUCCEEDED(retc)) fputc(in_ch, log_file);

            if(SUCCEEDED(retc)) if(ferror(log_file) || feof(log_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
         }

         fclose(glob_js_file);
         glob_js_file=NULL;
      }
      retc=S_OK;   
   }

// -----------------------
   if(SUCCEEDED(retc)) retc=test_app.PrintCompData(log_file);

// -----------------------
   fprintf(log_file, "------------------------------\n");

   if(log_file!=NULL) if(fclose(log_file))
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
   log_file=NULL;

// -----------------------
   Sleep(1000);

// -----------------------
   system("ver >> test_kd.log"); // rez.log"); // LOG_FILE_NAME !!!!

// -----------------------
   system("echo ------------------------- >> test_kd.log"); // rez.log"); // LOG_FILE_NAME !!!!
   system("dir C:\\arkim\\rezultatai >> test_kd.log"); // rez.log"); // LOG_FILE_NAME !!!!

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

// -----------------------
   system("pause");

   
return(RET_CODE(retc));
}
