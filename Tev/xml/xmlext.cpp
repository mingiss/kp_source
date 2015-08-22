// ==================================================
// xmlext.cpp
// XML nodes extractor depending on criteria
// like xmlque.exe, but does not need indexes, uses sequential testing


// ================================================== definitions
#include "envir.h"

#include <windows.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tvmain.h"
#include "kpttucf.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "tvxmle.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "tvxmls.h"
#include "xml8.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmln.h"
#include "xmlext.h"
// #include "mcmt.h"


// ================================================== objects
XmlExt_tag *pXmlExt=NULL;
// TvXmlFmse_tag *pTvXmlFmse=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);


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


// ================================================== public methods of XmlExt_tag
XmlExt_tag::XmlExt_tag
(
const unsigned char *lpszInFname,
const unsigned char *lpszOutFname,
const unsigned char *lpszTagName,
const unsigned char *lpszMinValue,
const unsigned char *lpszMaxValue,
const unsigned char *lpszExtractSubNodes
): XmlOI2_tag()
{
int ii;

   KpErrorProc.SetLPar(0L);

   m_iSearchTag=XC_Nul;
   m_lpszMinValue[0]=Nul;
   m_lpszMaxValue[0]=Nul;
   m_bExtractSubNodes=False;

   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFile(lpszInFname, (const unsigned char *)"rb",
                           lpszOutFname, (const unsigned char *)"w",
                           caIxLangs, iaIxEncodings);

// ------------------------------
   if(SUCCEEDED(m_lhOpenResult))
   {
      for(ii=0; ii<XC_TG_NumOfDictTags00; ii++)
         if(strncmp((const char *)plpszaXmlttDictTags[ii]+1, (const char *)lpszTagName, strlen(lpszTagName))==0)
         {
            m_iSearchTag=XC_FirstDictTag+ii;
            break;
         }
      if(m_iSearchTag==XC_Nul)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

// ------------------------------
   if(SUCCEEDED(m_lhOpenResult))
      if((lpszMinValue==NULL) || (lpszMaxValue==NULL))
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(m_lhOpenResult))
   {
      strncpy(m_lpszMinValue, lpszMinValue, TV_TAG_LEN);
      m_lpszMinValue[TV_TAG_LEN]=Nul;
      strncpy(m_lpszMaxValue, lpszMaxValue, TV_TAG_LEN);
      m_lpszMaxValue[TV_TAG_LEN]=Nul;
      if((lpszExtractSubNodes[0]=='y') || (lpszExtractSubNodes[0]=='Y'))
         m_bExtractSubNodes=True;
   }
}


// --------------------------------------------------
XmlExt_tag::~XmlExt_tag(void)
{
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlExt_tag::Process(void)
{
HRESULT retc=S_OK;
XmlNode_tag *cur_entry=NULL;
int in_ch;
XmlTagPars_tag *tag_pars=NULL;
long entr_id;
int par_num;
bool found_fl;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(m_lpInFileObj->FilePtr==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

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
            KpErrorProc.SetLPar(entr_id);
//          KpErrorProc.SetLPar(m_lEntryId);

            if((cur_entry!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            KP_NEWO(cur_entry, XmlNode_tag(in_ch, tag_pars, NULL, (const unsigned char *)"", NULL));
         }
         
         KP_DELETE(tag_pars);

      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);

      found_fl=False;
      if(SUCCEEDED(retc)) retc=cur_entry->TestQuery(m_iSearchTag, m_lpszMinValue, m_lpszMaxValue, &found_fl);

      if(found_fl && SUCCEEDED(retc))
      {
         if(m_bExtractSubNodes) retc=cur_entry->DeleteUnmatchedSubNodes(m_iSearchTag, m_lpszMinValue, m_lpszMaxValue);

         if(SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);
      }

      KP_DELETE(cur_entry);

   } // while(SUCCEEDED(retc))

   if(retc==KP_E_EOF) retc=S_OK;

   KpErrorProc.SetLPar(0L);

   if(SUCCEEDED(retc)) retc=PutXmlTail(m_lpOutFileObj->FilePtr);

return(retc);
}


// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
HRESULT retc0;
int l_argc;
const unsigned char *l_argv[7];
int ii;

   printf("\nXML query\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if((argc>=4) && (argc<=7))
      for(ii=0; ii<argc; ii++) l_argv[ii]=(const unsigned char *)argv[ii];
#ifdef Debug
   else // if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=7;

      l_argv[0]=(const unsigned char *)"xmlext";
      
//    l_argv[1]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcm1.xml";
//    l_argv[1]=(const unsigned char *)"d:\\kp\\source\\tev\\vlz\\kpn1.xml";
//    l_argv[1]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlz_xmlt\\vlz_o.xml";
      l_argv[1]=(const unsigned char *)"g:\\kp\\source\\tev\\vlz05\\vlzg.xml";

//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\mcm\\mcm_out\\mcm2.xml";
//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlz_ast\\vlza_%1.xml";
//    l_argv[2]=(const unsigned char *)"d:\\kp\\source\\tev\\vlz\\kpn2.xml";
//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlza_a.xml";
//    l_argv[2]=(const unsigned char *)"f:\\wrk\\kp\\source\\tev\\vlz\\vlz_o.xml";
      l_argv[2]=(const unsigned char *)"g:\\kp\\source\\tev\\vlz05\\geo\\vlzg_geo.xml";

//    l_argv[3]=(const unsigned char *)"ed";
//    l_argv[3]=(const unsigned char *)"ast";
      l_argv[3]=(const unsigned char *)"la";

//    l_argv[4]=(const unsigned char *)"2003.11.14";
//    l_argv[4]=(const unsigned char *)"2000.01.01";
//    l_argv[4]=(const unsigned char *)"A";
//    l_argv[4]=(const unsigned char *)"teis";
      l_argv[4]=(const unsigned char *)"geogr. vard.";

//    l_argv[5]=(const unsigned char *)"2003.11.24";
//    l_argv[5]=(const unsigned char *)"2003.12.03";
//    l_argv[5]=(const unsigned char *)"zzzzzz";
//    l_argv[5]=(const unsigned char *)"teis";
      l_argv[5]=(const unsigned char *)"geogr. vard.";

//    l_argv[6]=(const unsigned char *)"y";
      l_argv[6]=(const unsigned char *)"n";
   }
#endif

   if((l_argc>=4) && (l_argc<=7))
   {
      if(l_argc<7) l_argv[6]=NULL;
      if(l_argc<6) l_argv[5]=NULL;
      if(l_argc<5) l_argv[4]=NULL;

      KP_NEWO(pXmlExt, XmlExt_tag(l_argv[1], l_argv[2], l_argv[3], l_argv[4], l_argv[5], l_argv[6]));

      if(SUCCEEDED(retc)) retc=pXmlExt->Process();
      
      if(pXmlExt!=NULL)
      {
         retc0=pXmlExt->CloseFiles(SUCCEEDED(retc));
         if(SUCCEEDED(retc)) retc=retc0;
      }
      
      KP_DELETE(pXmlExt);
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlext.exe infile.xml outfile.xml ed 2000.01.01 2003.12.03 n\n");
      printf("                                                     ^       ^          ^    ^\n");
      printf("                         querying tag ---------------'       !          !    !\n");
      printf("                         min value (ed>=2000.01.01) ---------'          !    !\n");
      printf("                         max value (ed<=2003.12.03) --------------------'    !\n");
      printf("                         extract only subnodes containing query tag (y/n) ---'\n\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
system("pause");
#endif

return(RET_CODE(retc));
}
