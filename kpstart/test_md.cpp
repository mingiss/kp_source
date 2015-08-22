// -----------------------------------------
// test_md
// My Documents test
//
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
#define LOG_FILE_NAME  ((const unsigned char *)"test_md.log")


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
int main(void)
{
HRESULT retc=S_OK;
unsigned char my_docs_path[KP_MAX_FNAME_LEN+1];
unsigned char cmd_buf[KP_MAX_FNAME_LEN+1];
FILE *log_file=NULL;

   if(SUCCEEDED(retc)) retc=KpInitWindows(NULL);

   if(SUCCEEDED(retc)) 
   {          
      strcpy(cmd_buf, "dir c:\\ > ");
      strcat(cmd_buf, LOG_FILE_NAME);
      system((const char *)cmd_buf);
      Sleep(1000);
   }

   if(SUCCEEDED(retc)) 
   {
      log_file=fopen((const char *)LOG_FILE_NAME, "a");
      if(log_file==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);
   }
   
   if(SUCCEEDED(retc)) 
   {
      fseek(log_file, 0, SEEK_END);

      fprintf(log_file, "----------------------------\n");
      fprintf(log_file, (const char *)lpszaWindowsVerNames[iWindowsVersionCut]);
      fprintf(log_file, "\n\n");
   }

   if(SUCCEEDED(retc)) retc=GetMyDocumentsPath(my_docs_path);
   if(SUCCEEDED(retc)) 
   {
      fprintf(log_file, "----------------------------\n");
      fprintf(log_file, (const char *)my_docs_path);
      fprintf(log_file, "\n");
   }

   if(SUCCEEDED(retc)) 
      if(ferror(log_file) || feof(log_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(fclose(log_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, LOG_FILE_NAME, True, __FILE__, __LINE__, 0L);

/* if(SUCCEEDED(retc)) retc = */ KpFinitWindows();

   system("pause");
   
return(RET_CODE(retc));
}
