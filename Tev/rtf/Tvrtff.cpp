// ==================================================
// tvrtff.cpp
// RTF file formatting according to C formatting rules


// ================================================== definitions
#include "envir.h"
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include "kpmain.h"
#include "kptt.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfi.h"
#include "tvrtfo.h"
#include "tvrtff.h"

// ================================================== objects
TvRtfFm_tag TvRtfFm;

TvErrorProc_tag TvErrorProc(TRUE, 71);


// ================================================== private methods of TvRtfFm_tag
// --------------------------------------------------
HRESULT TvRtfFm_tag::PurgeInputFile(void)
{
HRESULT retc=TV_S_OK;

   if(lpRtfInputFileObj != NULL)
   {
      KP_DELETE(lpRtfInputFileObj);
   }
// else
//    retc=TvErrorProc.OutputErrorMessage(TV_E_NO_FILE, (const unsigned char *)"", TRUE, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfFm_tag::CloseOutputFile(bool bCheckFileExist)
{
HRESULT retc=TV_S_OK;

   if(lpRtfOutputFileObj!=NULL)
   {
      retc=lpRtfOutputFileObj->CloseFile(TRUE);
      KP_DELETE(lpRtfOutputFileObj);
   }
   else
   {
      retc=TV_E_NO_FILE;
      if(bCheckFileExist)
         retc=TvErrorProc.OutputErrorMessage(retc, (const unsigned char *)"", TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfFm_tag::FillStr(unsigned char *lpszOutStr, const unsigned char *lpszFillStr, const int iCount)
{
int ii;

   lpszOutStr[0]='\0';
   for(ii=0; ii<iCount; ii++) strcat((char *)lpszOutStr, (const char *)lpszFillStr);

return(TV_S_OK);
}


// --------------------------------------------------
HRESULT TvRtfFm_tag::FormatRtf(void)
{
HRESULT retc=TV_S_OK;
unsigned char ch2;
int level=0;
int max_indent;
int ii;
unsigned char indent_str[TV_MSG_LEN+1];
unsigned char indent_tpl[TV_MSG_LEN+1];

   strcpy((char *)indent_tpl,"   ");

   max_indent=TV_MSG_LEN/strlen((const char *)indent_tpl);
   indent_str[0]='\0';

   if((lpRtfInputFileObj==NULL) || (lpRtfOutputFileObj==NULL))
      retc=TvErrorProc.OutputErrorMessage(TV_E_NO_FILE, (const unsigned char *)"", TRUE, __FILE__, __LINE__, 0L);

   while(SUCCEEDED(retc))
   {
      retc=lpRtfInputFileObj->GetChar(&ch2, FALSE);

      if(SUCCEEDED(retc))
      {
         switch(ch2)
         {
         case '{':
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar('\n');
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutStr(indent_str);

            level++;
         
            ii=level; if(ii>=max_indent) ii=max_indent;
            FillStr(indent_str, indent_tpl, ii);

            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar(ch2);

            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar('\n');
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutStr(indent_str);

            break;

         case '}':
            level--; if(level<0) level=0;
         
            ii=level; if(ii>=max_indent) ii=max_indent;
            FillStr(indent_str, indent_tpl, ii);
         
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar('\n');
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutStr(indent_str);

            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar(ch2);

            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar('\n');
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutStr(indent_str);

            break;

         default:
            if(SUCCEEDED(retc)) retc=lpRtfOutputFileObj->PutChar(ch2);

            break;
         }
            
         if(SUCCEEDED(retc))
            if(ch2=='\n')
            {
               retc=lpRtfOutputFileObj->PutStr(indent_str);
               if(SUCCEEDED(retc))
                  retc=lpRtfInputFileObj->SkipSpaces();
            }
      }
   }

return(retc);
}


// ================================================== public methods of TvRtfFm_tag
// --------------------------------------------------
TvRtfFm_tag::TvRtfFm_tag(void)
{
   lpRtfInputFileObj=NULL;
   lpRtfOutputFileObj=NULL;
}


// --------------------------------------------------
TvRtfFm_tag::~TvRtfFm_tag(void)
{
   CloseOutputFile(FALSE);
   PurgeInputFile();
}


// --------------------------------------------------
HRESULT TvRtfFm_tag::Process(const unsigned char *lpszInfname, const unsigned char *lpszOutfname)
{
HRESULT retc=TV_S_OK;
HRESULT retc0;

   KP_NEWO(lpRtfInputFileObj, TvRtfI_tag(lpszInfname));

   KP_NEWO(lpRtfOutputFileObj, TvRtfO_tag(lpszOutfname));

   if(SUCCEEDED(retc)) retc=FormatRtf();

   retc0=CloseOutputFile(SUCCEEDED(retc));
   if(SUCCEEDED(retc)) retc=retc0;

   retc0=PurgeInputFile();
   if(SUCCEEDED(retc)) retc=retc0;

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=TV_S_OK;
int l_argc;
char *l_argv[3];

   printf("\nRTF file formatter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==3)
   {
      l_argv[0]=argv[0];
      l_argv[1]=argv[1];
      l_argv[2]=argv[2];
   }
// #ifdef Debug
   else if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=3;
      l_argv[0]="tvrtff";
      l_argv[1]="/home/kp/source/tev/mcm/src/macmil~2.rtf";
      l_argv[2]="/home/kp/source/tev/mcm/src/mcm2f.txt";
   }
// #endif

   if(l_argc==3)
      retc=TvRtfFm.Process((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>tvrtff.exe infile.rtf outfile.rtf\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
