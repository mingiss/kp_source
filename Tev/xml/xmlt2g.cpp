// ==================================================
// xmlt2g.cpp, former lvzg2t.cpp, former xmll2t.cpp
// XMLT to SGML converter
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if OsGr==MSWin
#include <windows.h>
#endif
#include <string>

#include "kpstdlib.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
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
#include "xmlt2g.h"


#define OUT_FILE_FORMAT XM_VERS_SGML_TAGE


// ================================================== objects
KpErrorProc_tag KpErrorProc(TRUE, 71);
XmlT2G_tag *pXmlT2G=NULL;
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

// ================================================== public methods of XmlT2G_tag
XmlT2G_tag::XmlT2G_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(False)
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlT2G_tag::~XmlT2G_tag(void)
{
   CloseFilesLocal(FALSE);
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlT2G_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
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
      m_lpInFileObj = new XmlI_tag(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, True, False);
      if(m_lpInFileObj!=NULL)
         retc=m_lpInFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }


   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      m_lpOutFileObj = new XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNew8File,
                                       NULL,
                                       NULL, NULL, caIxLangs,  iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaSgmDictTags,
                                       OUT_FILE_FORMAT, iaSgmCodeTables, True, False, False);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

// if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetEncoding(UC_UTF_PlainText, TV_MAIN_SGM_CTBL, TV_MAIN_SGM_CTBL);
   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetEncoding(UC_PlainText, TV_CTBL_TRANSPARENT, TV_CTBL_TRANSPARENT);

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2G_tag::CloseFilesLocal(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   retc=CloseFiles(bCheckFileExist);

return(retc);
}


// --------------------------------------------------
HRESULT XmlT2G_tag::Process(void)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars_tag *tag_pars=NULL;
XmlNode_tag *cur_entry=NULL;
long entr_id;
int par_num;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {    
      do
      {     
         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, FALSE);
                                                    
         if((in_ch==XC_StEntry) && SUCCEEDED(retc))
         {
            m_lEntryId++;
            entr_id=0L;
            if(tag_pars!=NULL) retc=tag_pars->SeekNumPar("id", &entr_id, &par_num);
            if(entr_id!=0L)
            {
               KpErrorProc.SetLPar(entr_id);
               m_lEntryId=entr_id;
            }
            else KpErrorProc.SetLPar(m_lEntryId);
         }
         
         KP_DELETE(tag_pars);
         
      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));
                      
      if(SUCCEEDED(retc))
      {                                                      
         cur_entry=new XmlNode_tag(in_ch, NULL, NULL, (const unsigned char *)"", NULL);
         if(cur_entry==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) retc=cur_entry->GetOpenResult();

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);
      
      if(SUCCEEDED(retc)) retc=cur_entry->ReduceIndent();
      if(SUCCEEDED(retc)) retc=cur_entry->DelEmptyTags();
//    if(SUCCEEDED(retc)) retc=cur_entry->EncloseTextToTx(); // nereikia - gerai ir be to
      
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

   printf("\nXML to SGML Tage dictionary converter\n\n");

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

//       l_argv[0]="vltt2g";
         l_argv[0]="lvz07e_t2g";

//       l_argv[1]="f:/kp/source/tev/vltt/vltt1.xml";
//       l_argv[1]="f:/kp/source/tev/lvtt/lvtt.xml";
         l_argv[1]="f:/kp/source/tev/lvz/kpn1.xml";

//       l_argv[2]="f:/kp/source/tev/vltt/vltt1.sgm";
//       l_argv[2]="f:/kp/source/tev/lvtt/lvtt.sgm";
         l_argv[2]="f:/kp/source/tev/lvz/kpn1.sgm";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==3)
      {
         pXmlT2G = new XmlT2G_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
         if(pXmlT2G!=NULL)
         {
            retc=pXmlT2G->GetOpenResult();

            if(SUCCEEDED(retc)) retc=pXmlT2G->Process();

            retc0=pXmlT2G->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;

            KP_DELETE(pXmlT2G);

            if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmlt2g.exe infile.xml outfile.sgm\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
unsigned char str_buf[100];
printf("\nPress any key:");
gets((char *)str_buf);
printf("\n");
#endif

return(RET_CODE_MAIN(retc));
}
