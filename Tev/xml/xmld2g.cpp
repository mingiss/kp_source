// ==================================================
// xmld2g.cpp
// LzdData file to LzdSgm converter


// ================================================== definitions
#if CompilerGr==Msvc
#include "stdafx.h"
#include <afx.h>
#endif

#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "tvxmle.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmld2g.h"
#include "lzdlstp.h"


// ================================================== objects
XmlD2G_tag *pXmlD2G=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);
bool bServiceFl=False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------------------------
HRESULT XmlNode_tag::TestChildContents(KpChar /* iTestTag */, KpChar *lpiazTestValue, bool *pFoundFlg)
{
HRESULT retc=S_OK;

   if(pFoundFlg==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pFoundFlg=False;
      if(lpiazTestValue==NULL) *pFoundFlg=True;
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode_tag::RenumCtgMng(void)
{
return(S_OK);
}


// ================================================== public methods of XmlD2G_tag
XmlD2G_tag::XmlD2G_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(False)
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlD2G_tag::~XmlD2G_tag(void)
{
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlD2G_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if((lpszInFname==NULL) || (lpszOutFname==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpInFileObj = new XmlI_tag(m_lpszInFileName, (const unsigned char *)"rb", CreateNew8File,
                                       plpszaXmlSpecCharTagsEdi,
                                       NULL, NULL, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaSgmDictTags,
                                       XM_VERS_SGML_TAGE, iaSgmCodeTables, True, False, False);

      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

// if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_PlainText, TV_MAIN_SGM_CTBL, TV_MAIN_SGM_CTBL);
   if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_PlainText, TV_CTBL_TRANSPARENT, TV_CTBL_TRANSPARENT);


   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpOutFileObj = new XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNew8File,
                                       plpszaXmlSpecCharTagsEdi,
                                       NULL, NULL, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaSgmDictTags,
                                       XM_VERS_SGML_TAGE, iaSgmCodeTables, False, False, False);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlD2G_tag::Process(bool bTrimSpaces)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars_tag *tag_pars=NULL;
XmlNode_tag *cur_entry = NULL;
KpChar entry_tag=C_Nul;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((m_pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   entry_tag=(KpChar)XC_StEntry;
   if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(entry_tag>=m_lpInFileObj->iLastDictTag)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames[entry_tag-m_lpInFileObj->iFirstDictTag]==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames[entry_tag-m_lpInFileObj->iFirstDictTag][0]==Nul)
      entry_tag=(KpChar)XC_HeadWordGroup;

   if(SUCCEEDED(retc)) do
   {
      if(SUCCEEDED(retc)) do
      {
         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, FALSE);
         KP_DELETE(tag_pars);

      } while((in_ch!=entry_tag) && SUCCEEDED(retc));

      if((cur_entry!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         cur_entry = new XmlNode_tag(in_ch, tag_pars, NULL, (const unsigned char *)"", NULL);
         if(cur_entry==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) retc=cur_entry->GetOpenResult();

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);

      if(SUCCEEDED(retc)) retc=cur_entry->ReplaceLists();

      if(SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);

      KP_DELETE(cur_entry);

   } while(SUCCEEDED(retc));

   KpErrorProc.SetLPar(0L);
   if(retc==KP_E_EOF) retc=S_OK;

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

   printf("\nLizdynas internal data to SGML Tage converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc==3)
      {
         l_argv[0]=argv[0];
         l_argv[1]=argv[1];
         l_argv[2]=argv[2];
      }
#ifdef Debug
      else // if(strstr(strlwr(argv[0]), "debug")>0)
      {
         l_argc=3;

         l_argv[0]="vlzd2g";

//       l_argv[1]="g:/kp/source/tev/vlz05/vlzc.dat";
//       l_argv[1]="f:/kp/source/tev/vlz/kpn1.dat";
//       l_argv[1]="g:/kp/source/tev/elz05e/bac.dat";
//       l_argv[1]="d:/Local/tev/elz05e/aaa/aaa.dat";
//       l_argv[1]="d:/Local/tev/rlz06/rlza/rlza.dat";
//       l_argv[1]="d:/Local/tev/rlz06/rlzb_01/rlzb_01.dat";
//       l_argv[1]="e:/kp/source/tev/rlz/kpn1.dat";
         l_argv[1]="d:/Local/tev/pavz/visata/visata.dat";

//       l_argv[2]="g:/kp/source/tev/vlz05/vlzc.sgm";
//       l_argv[2]="f:/kp/source/tev/vlz/kpn1.sgm";
//       l_argv[2]="g:/kp/source/tev/elz05e/bac.sgm";
//       l_argv[2]="d:/Local/tev/elz05e/aaa/aaa.sgm";
//       l_argv[2]="d:/Local/tev/rlz06/rlza/rlza.sgm";
//       l_argv[2]="d:/Local/tev/rlz06/rlzb_01/rlzb_01.sgm";
//       l_argv[2]="e:/kp/source/tev/rlz/kpn1.sgm";
         l_argv[2]="d:/Local/tev/pavz/visata/visata.sgm";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==3)
      {
         pXmlD2G = new XmlD2G_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
         if(pXmlD2G!=NULL)
         {
            retc=pXmlD2G->GetOpenResult();

            if(SUCCEEDED(retc)) retc=SarasPazymObj.Load();
            if(SUCCEEDED(retc)) retc=SarasKalbDalysObj.Load();
            if(SUCCEEDED(retc)) retc=SarasIterptObj.Load();
            if(SUCCEEDED(retc)) retc=SarasSkirtukObj.Load();
            if(SUCCEEDED(retc)) retc=SarasIndeksObj.Load();

            if(SUCCEEDED(retc)) retc=pXmlD2G->Process(False);

            retc0=pXmlD2G->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;

            KP_DELETE(pXmlD2G);

         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmld2g.exe infile.sgm outfile.xml\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}
