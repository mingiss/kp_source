// ---------------------
// kpsdup2.cpp
// copy images of files
//

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "kpstdlib.h"
#include "kperr.h"
#include "kpstring.h"
#include "kpsdup2.h"

// ------------------------------------------ static data
KpErrorProc_tag KpErrorProc(True, 43);
KpsDup2_tag *KpsDup2Ptr=NULL;


// --------------------------------------------------
KpsDup2_tag::KpsDup2_tag
(
   const unsigned char *szInFile,
   const unsigned char *szOutFile,
   long lInStart,
   long lBytCnt,
   long lOutStart
)
{
int fh;

   lhOpenResult=S_OK;

   strncpy(m_szInFileName, szInFile, KP_MAX_FNAME_LEN);
   m_szInFileName[KP_MAX_FNAME_LEN]=Nul;

   strncpy(m_szOutFileName, szOutFile, KP_MAX_FNAME_LEN);
   m_szOutFileName[KP_MAX_FNAME_LEN]=Nul;

   m_lOutLength=0L;
   fh = _open((const char *)m_szOutFileName, _O_BINARY | _O_RDONLY);
   if(fh==(-1))
      lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      m_lOutLength=_filelength(fh);
      _close(fh);
   }      

   m_pInFile=NULL;
   if(SUCCEEDED(lhOpenResult))
   {
      m_pInFile=fopen((const char *)m_szInFileName, "rb");
      if(m_pInFile==NULL)
         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   m_pOutFile=NULL;
   if(SUCCEEDED(lhOpenResult))
   {
      m_pOutFile=fopen((const char *)m_szOutFileName, "r+b");
      if(m_pOutFile==NULL)
         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   m_lInStart=lInStart;
   m_lBytCnt=lBytCnt;
   m_lOutStart=lOutStart;
}


// --------------------------------------------------
HRESULT KpsDup2_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
KpsDup2_tag::~KpsDup2_tag()
{
   CloseFile(False);
}


// --------------------------------------------------
HRESULT KpsDup2_tag::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(m_pInFile!=NULL) if(fclose(m_pInFile)!=0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   m_pInFile=NULL;

   if(SUCCEEDED(retc)) if(m_pOutFile==NULL)
   {
      retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      if(fclose(m_pOutFile)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
   }

   m_pOutFile=NULL;

return(retc);
}


// --------------------------------------------------
HRESULT KpsDup2_tag::Process(void)
{
HRESULT retc=S_OK;
int ch;
long ll;

   if((m_pInFile==NULL) || (m_pOutFile==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(fseek(m_pInFile, m_lInStart, SEEK_SET)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(fseek(m_pOutFile, m_lOutStart, SEEK_SET)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      for(ll=0; (ll<m_lBytCnt) && !feof(m_pInFile) && SUCCEEDED(retc); ll++)
      {
         ch=fgetc(m_pInFile);
         if(ferror(m_pInFile))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) if(!feof(m_pInFile))
         {
            fputc(ch, m_pOutFile);
            if(ferror(m_pOutFile) || feof(m_pOutFile))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         }
      }

      if(SUCCEEDED(retc)) if(feof(m_pInFile))
         for(ll--; (ll<m_lBytCnt) && SUCCEEDED(retc); ll++)
         {
            fputc(0, m_pOutFile);
            if(ferror(m_pOutFile) || feof(m_pOutFile))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         }
   }

return(retc);
}


// ------------------------------------------ 
int main(int argc, char **argv)
{
HRESULT retc=S_OK;

   printf("File image copy\n\n");

   if(argc==6)
   {
      KP_NEWO(KpsDup2Ptr, KpsDup2_tag
      (
         (const unsigned char *)argv[1],
         (const unsigned char *)argv[2],
         atol(argv[3]), atol(argv[4]), atol(argv[5])
      ));
      
      if(SUCCEEDED(retc)) retc=KpsDup2Ptr->Process();

      if(SUCCEEDED(retc)) retc=KpsDup2Ptr->CloseFile(True);

      KP_DELETE(KpsDup2Ptr);
   }
   else
   {
      retc=E_INVALIDARG;
      printf("Bad number of arguments:\n\n");
      printf("C:\\>kpsdup2.exe infile.typ outfile.typ 100000 20000 300000\n");
      printf("                                          ^      ^     ^\n");
      printf("         start byte of infile ------------'      |     |\n");
      printf("         number of bytes to copy ----------------'     |\n");
      printf("         start position of outfile --------------------'\n\n");
   }

return(RET_CODE(retc));
}
