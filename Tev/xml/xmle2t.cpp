// ==================================================
// xmle2t.cpp
// SGML CTBL-43 to XMLT (delimited) converter
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#if OsGr==MSWin
#include <windows.h>
#endif
#include <time.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kpsock.h"
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
#include "kpcapp.h"
#include "kpstap.h"
#include "xmle2t.h"


// ================================================== objects
const unsigned char lpszProdName[] = "xmle2t";
int iProdVerGlob=0;
KpErrorProc_tag KpErrorProc(TRUE, 71);
bool bServiceFl=False;

XmlE2T_tag *pXmlE2T=NULL;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------------------------
HRESULT XmlNode_tag::TestChildContents(int /* iTestTag */, KpChar *lpiazTestValue, bool *pFoundFlg)
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


// ================================================== public methods of XmlE2T_tag
XmlE2T_tag::XmlE2T_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(False)
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlE2T_tag::~XmlE2T_tag(void)
{
   CloseFilesLocal(FALSE);
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlE2T_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if(((lpszInFname==NULL) || (lpszOutFname==NULL)) && SUCCEEDED(retc))
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
                                       XC_FirstDictTag, plpszaSgmDictTags,
                                       XM_VERS_SGML_TAGE, iaSgmCodeTablesEdi, True, False, False);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

// if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_UTF_PlainText, TV_MAIN_SGM_CTBL, TV_MAIN_SGM_CTBL);
   if(SUCCEEDED(retc)) retc=m_lpInFileObj->SetEncoding(UC_PlainText, TV_CTBL_TRANSPARENT, TV_CTBL_TRANSPARENT);


   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpOutFileObj = new XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, False, False);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

//------------------------
   if(SUCCEEDED(retc)) retc=PutXmlHatI(m_lpOutFileObj, m_lpszOutFileName);

return(retc);
}


// --------------------------------------------------
HRESULT XmlE2T_tag::CloseFilesLocal(bool bCheckFileExist)
{
HRESULT retc=S_OK;
                                        
   if((m_lpOutFileObj==NULL) && bCheckFileExist && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   
   if((m_lpOutFileObj!=NULL) && SUCCEEDED(retc)) retc=PutXmlTailI(m_lpOutFileObj);

   if(SUCCEEDED(retc)) retc=CloseFiles(bCheckFileExist);

return(retc);
}


// --------------------------------------------------
HRESULT XmlE2T_tag::Process(bool bInsDelim)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars_tag *tag_pars=NULL;
XmlNode_tag *cur_entry=NULL;
long ll;
int par_num;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {    
      do
      {     
         KP_DELETE(tag_pars);

         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, True);
         
      } while((in_ch!=XC_HeadWordGroup) && SUCCEEDED(retc));
                      
//    if((tag_pars!=NULL) && SUCCEEDED(retc))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         if(tag_pars!=NULL)
         {
            retc=tag_pars->SeekNumPar("id", &ll, &par_num);
            if(SUCCEEDED(retc)) m_lEntryId=ll;
            else if(retc==KP_E_KWD_NOT_FOUND)
            {       
               retc=S_OK;
               m_lEntryId++;
               retc=tag_pars->AddNumPar((const unsigned char *)"id", m_lEntryId);
            }
         }
         else
         {
            m_lEntryId++;
            tag_pars=new XmlTagPars_tag((const unsigned char *)"id", m_lEntryId);
            if(tag_pars==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
         }
      }
      
      KpErrorProc.SetLPar(m_lEntryId);
         
      if(SUCCEEDED(retc))
      {                                                      
         cur_entry=new XmlNode_tag(in_ch, NULL, NULL, (const unsigned char *)"", NULL);
         if(cur_entry==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) retc=cur_entry->GetOpenResult();

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);
      if(SUCCEEDED(retc)) retc=cur_entry->IncreaseIndent(); 
      
      if(SUCCEEDED(retc)) retc=cur_entry->CreateGrpCounters(); 

      if(bInsDelim && SUCCEEDED(retc))
         retc=cur_entry->InsertDelimiters(XC_FirstDictTag, XC_LastDictTag, XM_VERS_XML10);

// -----------------
      if(SUCCEEDED(retc))
      {
         retc=m_lpOutFileObj->PutCharProc(XC_StEntry, tag_pars);
         KP_DELETE(tag_pars);
      }
      if(SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);
      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(XC_StEntry_e, NULL);

      if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL);
                                               
      KP_DELETE(tag_pars);

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
char *l_argv[4];

   printf("\nXML to SGML Tage dictionary converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc==4)
      {
         l_argv[0]=argv[0];
         l_argv[1]=argv[1];
         l_argv[2]=argv[2];
         l_argv[3]=argv[3];
      }
#ifdef Debug
      else // if(strstr(strlwr(argv[0]), "debug")>0)
      {
         l_argc=4;

         l_argv[0]="xmle2t";

//       l_argv[1]="f:/kp/source/tev/vltt/vltt1_43.sgm";
//       l_argv[1]="f:/kp/source/tev/vltt/wrk/pvz.sgm";
//       l_argv[1]="f:/kp/source/tev/vltt/vlttre.sgm";
//       l_argv[1]="f:/kp/source/tev/vltt/vltt1e.sgm";
//       l_argv[1]="f:/kp/source/tev/lvtt/lvtte.sgm";
//       l_argv[1]="f:/kp/source/tev/lvtt/lvt_pvze.sgm";
//       l_argv[1]="g:/kp/source/tev/aklz/aklz_a.sgm";
//       l_argv[1]="f:/kp/source/tev/aklz/kpn1.sgm";
         l_argv[1]="g:/kp/source/tev/mcm/mac_a.sgm";

//       l_argv[2]="f:/kp/source/tev/vltt/vltt1_res.xml";
//       l_argv[2]="f:/kp/source/tev/vltt/wrk/temp.xml";
//       l_argv[2]="f:/kp/source/tev/vltt/vlttr.xml";
//       l_argv[2]="f:/kp/source/tev/vltt/vltt1.xml";
//       l_argv[2]="f:/kp/source/tev/lvtt/lvtt.xml";
//       l_argv[2]="f:/kp/source/tev/lvtt/lvt_pvz.xml";
//       l_argv[2]="g:/kp/source/tev/aklz/aklz_a.xml";
//       l_argv[2]="f:/kp/source/tev/aklz/kpn1.xml";
         l_argv[2]="g:/kp/source/tev/mcm/mac_a.xml";

//       l_argv[3]="y";
         l_argv[3]="n";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==4)
      {
         pXmlE2T = new XmlE2T_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
         if(pXmlE2T!=NULL)
         {
            retc=pXmlE2T->GetOpenResult();

            if(SUCCEEDED(retc)) retc=pXmlE2T->Process((l_argv[3][0]=='y') || (l_argv[3][0]=='Y'));

            retc0=pXmlE2T->CloseFilesLocal(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;

            KP_DELETE(pXmlE2T);

            if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmle2t.exe infile.xml outfile.sgm y\n");
         printf("                                                    ^\n");
         printf("                      insert delimiters? (y/n) -----'\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE_MAIN(retc));
}

