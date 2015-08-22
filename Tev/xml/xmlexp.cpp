// ==================================================
// xmlexp.cpp, former xmlspt.cpp
// extracts compounds to separate entries (for electronic browsing)
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#if OsGr==MSWin
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#endif
#include <string>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpstring.h"
#include "kpstdio.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kperr.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmloi2.h"
#include "xmlexp.h"


// ================================================== objects
XmlExp_tag *pXmlExp=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);
bool bServiceFl=False;
const unsigned char lpszProdName[] = "xmlexp";
int iProdVerGlob=0;


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


// ================================================== public methods of XmlExp_tag
XmlExp_tag::XmlExp_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(False)
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlExp_tag::~XmlExp_tag(void)
{
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlExp_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if((lpszInFname==NULL) || (lpszOutFname==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEW(m_lpInFileObj, XmlI_tag(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, True, False));
   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEW(m_lpOutFileObj, XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs,  iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, True, False);

return(retc);
}


// --------------------------------------------------
HRESULT XmlExp_tag::Process(int iLevel)
{
HRESULT retc=S_OK;
KpChar in_ch;
KpChar cur_tag;
XmlTagPars_tag *tag_pars=NULL;
XmlNode_tag *cur_entry;
KpChar *base_ptr;
bool empty;
bool empty_after;
KpChar skip_tag_arr[] = {(KpChar)XC_HeadWord, (KpChar)XC_HeadWordGroup, C_Nul};

   m_lEntryId=0L;
   KpErrorProc.SetLPar(m_lEntryId);

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((m_pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutXmlHatI(m_lpOutFileObj, m_lpszOutFileName);
   if(SUCCEEDED(retc)) retc=PushTag(&m_pTagStack, (KpChar)XC_Dict, NULL, 0);

   if(SUCCEEDED(retc)) do
   {
// skip input until <se>
      retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, FALSE);
                               
      if((in_ch==XC_StEntry) && SUCCEEDED(retc))
      {
         KP_NEWO(cur_entry, XmlNode_tag(in_ch, tag_pars, NULL, (const unsigned char *)"", NULL));

         if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);
                                                                    
// -------------------------------------
         if(SUCCEEDED(retc)) retc=cur_entry->ProcessLevel(iLevel, False);

// -------------------------------------
         if(SUCCEEDED(retc))
         {
            base_ptr=NULL;
            retc=cur_entry->GetBase(&base_ptr);
         }
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
KptStrDecode(str_buf, base_ptr, 71);
KP_TRACE(str_buf);
#endif
//       if(SUCCEEDED(retc)) retc=cur_entry->SubstBase(base_ptr, False);

// -------------------------------------
         empty = True;
         if(SUCCEEDED(retc)) retc=cur_entry->TestNotSignificant(&empty, skip_tag_arr);

// -------------------------------------
bool found_fl;
         if(SUCCEEDED(retc)) retc=cur_entry->DelTagsByValue((KpChar)XC_Label, (const unsigned char *)"geogr. vard.", &found_fl);

// -------------------------------------
         if(SUCCEEDED(retc)) retc=cur_entry->WriteEmbeddedCompounds(base_ptr, m_lpOutFileObj, &m_lEntryId, False);

// -------------------------------------
         if(SUCCEEDED(retc)) retc=cur_entry->SubstBase(base_ptr, True);
         if(SUCCEEDED(retc)) retc=cur_entry->SubstBase(base_ptr, False);
         if(SUCCEEDED(retc)) retc=cur_entry->DelCompDelim();

// increase entry id
         if(SUCCEEDED(retc))
         {
            m_lEntryId++;
            KpErrorProc.SetLPar(m_lEntryId);
         }
// create <se> tag pars
         KP_NEW(tag_pars, XmlTagPars_tag((const unsigned char *)"id", m_lEntryId));

         if(SUCCEEDED(retc))
         {
            retc=cur_entry->SetTagParsPtr(tag_pars);
            if(FAILED(retc)) KP_DELETE(tag_pars);
         }
         tag_pars=NULL;

         empty_after = True;
         if(SUCCEEDED(retc)) retc=cur_entry->TestNotSignificant(&empty_after, skip_tag_arr);

         if(((!empty_after) || empty) && SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);

// -------------------------------------
         KP_DELETE(cur_entry);
      }                        
                               
      KP_DELETE(tag_pars);

   } while(SUCCEEDED(retc));

   KpErrorProc.SetLPar(0L);
   if(retc==KP_E_EOF) retc=S_OK;

   if(SUCCEEDED(retc)) retc=PutXmlTailI(m_lpOutFileObj);
   if(SUCCEEDED(retc)) retc=PopTag(&m_pTagStack, &cur_tag);
   if((cur_tag!=XC_Dict) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, m_lEntryId);

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
int level;

   printf("\nXML dictionary compounds extractor\n\n");

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

         l_argv[0]="xmlexp";

//       l_argv[1]="f:/kp/source/tev/lvz/lvz.xml";
         l_argv[1]="f:/kp/source/tev/ldz/kpn1.xml";

//       l_argv[2]="f:/kp/source/tev/lvz/lvz1.xml";
         l_argv[2]="f:/kp/source/tev/ldz/kpn1_x.xml";

         l_argv[3]=(unsigned char *)"2";
      }
#endif
   }
   
   level=0;
   if(SUCCEEDED(retc)) if(l_argc>3) if(sscanf((const char *)l_argv[3], "%d", &level)<1)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(l_argc==4)
      {
         KP_NEWO(pXmlExp, XmlExp_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

         if(SUCCEEDED(retc)) retc=pXmlExp->Process(level);

         if(pXmlExp!=NULL)
         {
            retc0 = pXmlExp->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc = retc0;
         }

         if(SUCCEEDED(retc)) retc = XmlIcv((unsigned char *)l_argv[2]);
         
         KP_DELETE(pXmlExp);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmlexp.exe infile.sgm outfile.xml 2\n");
         printf("                                                    ^\n");
         printf("      [dictionary level] ---------------------------'\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
#if (Compiler==Watcom)
system("pause");
#endif
#endif

return(RET_CODE_MAIN(retc));
}
