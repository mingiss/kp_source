// ==================================================
// xmlspt.cpp, former vlzspt.cpp, obsolete, use xmlexp.cpp
// Dictionary XML file nodes splitter
// splits derivatives, compounds and collocations to different nodes
//

// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if (Envir==MSWin32Con) || (Envir==MSWin32) || (Envir==MSWin32Mfc) || (Envir==MSWin32ConMfc)
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
// #include "vlzt.h"
#include "xmlspt.h"


// ================================================== objects
XmlSpt_tag *pXmlSpt=NULL;

KpErrorProc_tag KpErrorProc(TRUE, 71);

const unsigned char **pplpszaMsgTags = plpszaXmlttDictTagsFull;

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


// ================================================== public methods of XmlSpt_tag
XmlSpt_tag::XmlSpt_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(True)
{
   KpErrorProc.SetLPar(0L);
   m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
   m_lMaxSeIx=0L;
}


// --------------------------------------------------
XmlSpt_tag::~XmlSpt_tag(void)
{
   XmlOI2_tag_destructor();
}


// --------------------------------------------------
HRESULT XmlSpt_tag::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
HRESULT retc=S_OK;

   if((lpszInFname==NULL) || (lpszOutFname==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpInFileObj, XmlI_tag(m_lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                    plpszaXmlSpecCharTagsMain,
                                    alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings, XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                    XM_VERS_XML10, iaXmlNulCodeTables, True, False, True));

   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpOutFileObj, XmlI_tag(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                              plpszaXmlSpecCharTagsMain,
                                 alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings, XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                 XM_VERS_XML10, iaXmlNulCodeTables, True, False, True));

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpt_tag::Process(int iLevel)
{
HRESULT retc=S_OK;
XmlTagPars_tag *tag_pars = NULL;
XmlNode_tag *cur_entry = NULL;
XmlNode_tag *first_child = NULL;
XmlNode_tag *next_brother = NULL;
int in_ch;
const int *hw_ptr;
const Chars16 *base_ptr;
unsigned char out_str[KP_KWD_LEN+1];
int ii;
// int par_num;
bool written;

   m_lEntryId=0L;
   KpErrorProc.SetLPar(m_lEntryId);

   if(((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutXmlHatI(m_lpOutFileObj, m_lpszOutFileName);

   if(SUCCEEDED(retc)) do
   {
      if(SUCCEEDED(retc)) do
      {
         retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False);
         if((in_ch!=XC_StEntry) && SUCCEEDED(retc))
         {
            if(
               (in_ch!=C_Spc) &&
               (in_ch!=XC_Version) &&
               (in_ch!=XC_DocType) &&
               (in_ch!=XC_StyleSheet) &&
               (in_ch!=XC_Dict) &&
               (in_ch!=XC_Dict_e)
              )
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            KP_DELETE(tag_pars);
         }

      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));

// -------------------------------------
//    m_lEntryId=0L;
//    if((tag_pars!=NULL) && SUCCEEDED(retc))
//       retc=tag_pars->SeekNumPar("id", &m_lEntryId, &par_num);
      m_lEntryId++;
      KpErrorProc.SetLPar(m_lEntryId);

      KP_DELETE(tag_pars);

      KP_NEW(tag_pars, XmlTagPars_tag((const unsigned char *)"id", m_lEntryId));
      
// -------------------------------------
      if(SUCCEEDED(retc))
      {
         KP_NEWO(cur_entry, XmlNode_tag(in_ch, tag_pars, NULL, (const unsigned char *)"", NULL));
         if(FAILED(retc))
         {
            KP_DELETE(tag_pars);
         }
         tag_pars=NULL;
      }

// -------------------------------------
      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(m_lpInFileObj);

// ------------------------- process level
//    if(SUCCEEDED(retc)) retc=cur_entry->SupressToLevel(iLevel);
// // if(SUCCEEDED(retc)) retc=cur_entry->DelLevelTags(iLevel);
// ------------------------- delete author remarks
//    if(SUCCEEDED(retc)) retc=cur_entry->DelTags(XC_TechNote);
      if(iLevel && SUCCEEDED(retc)) retc=cur_entry->ProcessLevel(iLevel, False);
                                      
      if(SUCCEEDED(retc))
      {
         hw_ptr=NULL;
         retc=cur_entry->GetHw((const Chars16 **)&hw_ptr);
      }
      if(SUCCEEDED(retc))
      {
         if(hw_ptr!=NULL)
         {
            ii=TvIntStrLen(hw_ptr);
            if(ii>KP_KWD_LEN) ii=KP_KWD_LEN;
            retc=KptStrDecode(out_str, hw_ptr, ii, 71);
            if(retc==KP_E_UNKN_CHR) retc=S_OK;

            if(SUCCEEDED(retc)) retc=KpErrorProc.SetLTxt(out_str);
         }
         else retc=KpErrorProc.SetLTxt((const unsigned char *)"");
      }

// -------------------------------------
      if(SUCCEEDED(retc))
      {
         base_ptr=NULL;
         retc=cur_entry->GetBase(&base_ptr);
      }
//    if(SUCCEEDED(retc)) retc=cur_entry->SubstBase(base_ptr, False);

// -------------------------------------
      if(SUCCEEDED(retc)) retc=cur_entry->WriteEmbeddedCompounds(base_ptr, m_lpOutFileObj, &m_lEntryId, False);
      KpErrorProc.SetLPar(m_lEntryId);

      if(SUCCEEDED(retc)) retc=cur_entry->SubstBase(base_ptr, False);
      if(SUCCEEDED(retc)) retc=cur_entry->DelCompDelim();

      if(SUCCEEDED(retc)) retc=cur_entry->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) retc=cur_entry->GetNextBrother(&next_brother);
      if(((first_child!=NULL) || (next_brother!=NULL)) && SUCCEEDED(retc))
      {                                    
         written=False;
         retc=cur_entry->WriteGroupVariants(cur_entry, m_lpOutFileObj, &m_lEntryId, &written, False);
         if((!written) && SUCCEEDED(retc)) retc=cur_entry->WriteNode(m_lpOutFileObj);
      }
   
      KP_DELETE(cur_entry);

   } while(SUCCEEDED(retc));

   if(retc==KP_E_EOF) retc=S_OK;
   KpErrorProc.SetLPar(0L);

   if(SUCCEEDED(retc)) retc=PutXmlTailI(m_lpOutFileObj);

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

   printf("\nXML dictionary splitter of grouped nodes\n\n");

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

         l_argv[0]="xmlspt";

//       l_argv[1]="f:/kp/source/tev/lvz/lvz.xml";
//       l_argv[1]="f:/kp/source/tev/lvz/kpn1.xml";
//       l_argv[1]="g:/kp/source/tev/lvz/lvz.xml";
//       l_argv[1]="f:/kp/source/tev/lzdsh/kpn0.xml";
         l_argv[1]="f:/kp/source/tev/lzdsh/vlzd0.xml";

//       l_argv[2]="f:/kp/source/tev/lvz/lvz1.xml";
//       l_argv[2]="f:/kp/source/tev/lvz/kpn2.xml";
//       l_argv[2]="g:/kp/source/tev/lvz/lvz1.xml";
//       l_argv[2]="f:/kp/source/tev/lzdsh/kpn1.xml";
         l_argv[2]="f:/kp/source/tev/lzdsh/vlzd1.xml";

//       l_argv[3]="2";
         l_argv[3]="0";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==4)
      {
         sscanf(l_argv[3], "%d", &level);

printf(">>>%d<<<\n", level);
               
         KP_NEWO(pXmlSpt, XmlSpt_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

         if(SUCCEEDED(retc)) retc=pXmlSpt->Process(level);

         if(pXmlSpt!=NULL)
         {
            retc0=pXmlSpt->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }
         
//       if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

         KP_DELETE(pXmlSpt);
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmlspt.exe infile.xml outfile.xml 4\n");
         printf("                                                    ^\n");
         printf("             level (0 means no level processing) ---'\n");
      }
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
#if (Compiler==Watcom)
system("pause");
#endif
#endif

return(RET_CODE(retc));
}

