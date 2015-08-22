// ==================================================
// kpt71toU8.cpp, HTML Windows 1257 to UTF-8 converter
//

// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <windows.h>
#include <string>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xml8.h"
#include "htmt.h"
#include "xmlo1.h"
#include "xmlt.h"

#include "kpt71toU8.h"

// ================================================== objects
Kpt71toU8_tag *pKpt71toU8;
KpErrorProc_tag KpErrorProc(TRUE, 71);
int SortMode=KP_LNG_LIT;
bool bFreeTextInUs=True;
int iCurFontSize=22;
bool bServiceFl=False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ================================================== public methods of Kpt71toU8_tag
Kpt71toU8_tag::Kpt71toU8_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
   m_lhOpenResult=S_OK;
   m_lpszInFileName[0]=Nul;  // file names
   m_lpszOutFileName[0]=Nul;
   m_lpInFileObj=NULL;
   m_lpOutFileObj=NULL;

   KpErrorProc.SetLPar(0L);

   m_lhOpenResult=OpenFile(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
Kpt71toU8_tag::~Kpt71toU8_tag(void)
{
   CloseFiles(False);
}


// --------------------------------------------------
HRESULT Kpt71toU8_tag::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT Kpt71toU8_tag::OpenFile(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if((lpszInFname==NULL) || (lpszOutFname==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpInFileObj, TvXmlFile_tag
         (
            m_lpszInFileName,             // const unsigned char *lpszFileName,
            (const unsigned char *)"r",   // const unsigned char *lpszMode,
            XL_FT_DataFile,               // XL_FileTypes uiFileType,
            CreateNew8File,               // HRESULT CreateLowLevelObj(),
            plpszaXmlSpecCharTagsMain,    // const unsigned char **plpszaXmlSpCharTags,
            0,                            // int iIndexWidth,
            (KpChar)HTM_TG_FirstTag,      // int iFirstTag,
            plpszaHtmlTags,               // const unsigned char **plpszaTags,   
            XM_VERS_HTML401_TRANS,        // XmlVersions iVersion,
            iaHtmCodeTables71,            // const int *piaCodeTables,
            True,                         // bool bMultiLine,
            False                         // bool bMapToPrivate
         ));

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpOutFileObj, TvXmlFile_tag
         (
            m_lpszOutFileName,            // const unsigned char *lpszFileName,
            (const unsigned char *)"w",   // const unsigned char *lpszMode,
            XL_FT_DataFile,               // XL_FileTypes uiFileType,
            CreateNewUniFile,             // HRESULT CreateLowLevelObj(),
            plpszaXmlSpecCharTagsMain,    // const unsigned char **plpszaXmlSpCharTags,
            0,                            // int iIndexWidth,
            (KpChar)XC_FirstDictTag, // HTM_TG_FirstTag,     // int iFirstTag,
            plpszaXmlttDictTags, // plpszaHtmlTags,      // const unsigned char **plpszaTags,   
            XM_VERS_HTML401_TRANS,        // XmlVersions iVersion,
            iaXmlNulCodeTables,  // iaHtmNulCodeTables,  // const int *piaCodeTables,
            True,                         // bool bMultiLine,
            False                         // bool bMapToPrivate
         ));

return(retc);
}


// --------------------------------------------------
HRESULT Kpt71toU8_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(m_lpOutFileObj!=NULL)
   {
      retc = m_lpOutFileObj->CloseFile(bCheckFileExist);
      KP_DELETE(m_lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(m_lpInFileObj != NULL)
   {
      KP_DELETE(m_lpInFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT Kpt71toU8_tag::Process(void)
{
HRESULT retc=S_OK;
XmlTagPars_tag *tag_pars=NULL;
KpChar in_ch;
int char_pos;

   if(((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {
      retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->GetCharPos(&char_pos);

      if(((in_ch!=C_Spc) || (char_pos>0)) && SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc(in_ch, tag_pars, False);

      KP_DELETE(tag_pars);

   } while(SUCCEEDED(retc));

   if(retc == KP_E_EOF) retc = S_OK;
   KpErrorProc.SetLPar(0L);

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
char *l_argv[3];

   printf("\nHTML Windows 1257 to UTF-8 converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc>=3)
      {
         l_argv[0]=argv[0];
         l_argv[1]=argv[1];
         l_argv[2]=argv[2];
      }
#ifdef Debug
      else // if(strstr(strlwr(argv[0]), "debug")>0)
      {
         l_argc=3;

         l_argv[0]="kpt71tou8";

//       l_argv[1]="f:/kp/source/tev/mokyk/paraisk.htm";
         l_argv[1]="f:/kp/source/tev/mokyk/parais01.htm";

         l_argv[2]="f:/kp/source/tev/mokyk/paraisk1.htm";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc>=3)
      {
         KP_NEWO(pKpt71toU8, Kpt71toU8_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

         if(SUCCEEDED(retc)) retc=pKpt71toU8->Process();
         if(pKpt71toU8!=NULL)
         {
            retc0 = pKpt71toU8->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc = retc0;
         }
         
         KP_DELETE(pKpt71toU8);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>kpt71tou8.exe infile.htm outfile.htm\n");
      }
   }

#ifdef Debug
#if (Compiler==Watcom)
system("pause");
#endif
#endif

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE_MAIN(retc));
}
