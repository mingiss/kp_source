// ==================================================
// xmldep.cpp
// deleting empty tags from XML dictionary
//


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include <iostream.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpttucf.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"

#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlu.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "tvxmle.h"
#include "xmlsty.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmldep.h"


#if Envir!=MSWin32Con
#error Envir!=MSWin32Con
#endif


// -----------------------------------------
KpErrorProc_tag KpErrorProc(True, 71);
XmlDep_tag *pXmlDep;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp" 
}
          

// --------------------------------------------------
HRESULT XmlNode_tag::TestChildContents(int /* iTestTag */, Chars16 *lpiazTestValue, bool *pFoundFlg)
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

// ================================================== public methods of XmlDep_tag
XmlDep_tag::XmlDep_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag()
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
XmlDep_tag::~XmlDep_tag(void)
{
   XmlOI2_tag_destructor();
}



// --------------------------------------------------
HRESULT XmlDep_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if((lpszInFname==NULL) || (lpszOutFname==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpInFileObj, XmlI_tag(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, False));
   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEW(m_lpOutFileObj, XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlNulCodeTables, True, False));

return(retc);
}


// --------------------------------------------------
HRESULT XmlDep_tag::Process(void)
{
HRESULT retc=S_OK;
int in_ch;
XmlTagPars_tag *tag_pars=NULL;
XmlNode_tag *cur_entry = NULL;
long entr_id;
int par_num;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((m_pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) retc=PutXmlHat(m_lpOutFileObj->FilePtr, m_lpszOutFileName);

   while(SUCCEEDED(retc))
   {
      do
      {
         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False);

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

            if((cur_entry!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            KP_NEWO(cur_entry, XmlNode_tag(in_ch, tag_pars, NULL, (const unsigned char *)"", NULL));
         }
         KP_DELETE(tag_pars);
         
      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));

// printf("------------- %d\n", lpOutFileObj->GetFldDepth());

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);

      if(SUCCEEDED(retc)) retc=cur_entry->DelEmptyTags();

      if(SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);

      KP_DELETE(cur_entry);
      
      /* retc= */ KpErrorProc.SetLTxt((const unsigned char *)"");

   } // while(SUCCEEDED(retc))

   if(retc==KP_E_EOF) retc=S_OK;

   if(SUCCEEDED(retc)) retc=PutXmlTail(m_lpOutFileObj->FilePtr);

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

   printf("\nXML dictionary empty tags eliminator\n\n");

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

         l_argv[0]="xmldep";

         l_argv[1]="f:/kp/source/tev/ldz/ldel.out/aaa.xml";
         l_argv[1]="f:/kp/source/tev/ldz/kpn2.xml";

         l_argv[2]="f:/kp/source/tev/ldz/ldel.out1/aaa.xml";
         l_argv[2]="f:/kp/source/tev/ldz/kpn3.xml";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==3)
      {
         KP_NEWO(pXmlDep, XmlDep_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

         if(SUCCEEDED(retc)) retc=pXmlDep->Process();

         if(pXmlDep!=NULL)
         {
            retc0 = pXmlDep->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pXmlDep);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>lvzg2t.exe infile.sgm outfile.xml\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE(retc));
}
                                               
