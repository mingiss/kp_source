// ==================================================
// xmlrdt.cpp
// XML dictionary tag eliminator


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if (Envir==15) || (Envir==16)
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptt.h"
#include "kpttucf.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"

#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "tvxmle.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "xmlrdt.h"


// ================================================== objects
XmlRdt_tag *pXmlRdt=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);
int SortMode=KP_LNG_LIT;
bool bFreeTextInUs=True;

const unsigned char **pplpszaMsgTags = plpszaXmlttDictTagsFull;

// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp" 
}
          

// ================================================== public methods of XmlRdt_tag
XmlRdt_tag::XmlRdt_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2_tag(True)
{
   pTagStack=NULL;

   KpErrorProc.SetLPar(0L);
   m_lhOpenResult=OpenFile(lpszInFname, (const unsigned char *)"rb",
                         lpszOutFname, (const unsigned char *)"w",
                         caIxLangs, iaIxEncodings);
   m_lMaxSeIx=0L;

   bAccFl=Undefined;
   aiXmlAccDeclArr[0]=C_Nul;

   if(SUCCEEDED(m_lhOpenResult))
   {
      pTagStack = new TvXmlTagStack_tag(NULL, C_Nul, NULL, 0);
      if(pTagStack==NULL)
         m_lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
   }
}


// --------------------------------------------------
XmlRdt_tag::~XmlRdt_tag(void)
{
TvXmlTagStack_tag *prev_stack_ptr;
int cur_tag;

   XmlOI2_tag_destructor();

   if(pTagStack!=NULL)
   {
      pTagStack->GetPrevTagPtr(&prev_stack_ptr);
      pTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr!=NULL) || (cur_tag!=C_Nul))
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

      KP_DELETE(pTagStack);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT XmlRdt_tag::AcceptDeclineXmlTag(const unsigned char *lpszTag)
{
HRESULT retc=S_OK;
int ii;
unsigned char tag_buf[TV_XL_MAX_TAG_WDT+1];
unsigned char *pnts;
int ar_ptr;
bool acc_fl;
const unsigned char *in_tag;

   acc_fl=((*lpszTag)!='-');
   if((bAccFl!=Undefined) && (bAccFl!=acc_fl))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (unsigned char *)"Mixed accept/decline parameters", TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      in_tag=acc_fl?lpszTag:(lpszTag+1);
      bAccFl=acc_fl;

      for(ar_ptr=0; ar_ptr<RP_MAX_TAGS; ar_ptr++) if(aiXmlAccDeclArr[ar_ptr]==C_Nul) break;
      if(ar_ptr>=RP_MAX_TAGS)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, lpszTag, TRUE, __FILE__, __LINE__, m_lEntryId);
   }

   if(SUCCEEDED(retc))
   {
      for(ii=0; ii<XC_LastDictTag-XC_FirstDictTag; ii++)
      {
         strncpy((char *)tag_buf, (const char *)plpszaXmlttDictTags[ii], TV_XL_MAX_TAG_WDT);
         tag_buf[TV_XL_MAX_TAG_WDT]=Nul;
         pnts=tag_buf;
         while((*pnts!=Spc) && (*pnts!=TV_XM_TagEndCh) && (*pnts!=Nul)) pnts++;
         *pnts=Nul;
         if(strcmp(tag_buf+1, in_tag)==0)
         {
            aiXmlAccDeclArr[ar_ptr]=XC_FirstDictTag+ii;
            break;
         }
      }

      if(ii>=XC_LastDictTag-XC_FirstDictTag)
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, lpszTag, TRUE, __FILE__, __LINE__, m_lEntryId);

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlRdt_tag::PutTag(int iTag, XmlTagPars_tag *pTagParsObj)
{
HRESULT retc=S_OK;
int ii;
int gr_cnt;
int ch_pos;

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->GetCharPos(&ch_pos);

   if((TvIntStrChr(uiazXmlGrTags, iTag)!=NULL) && (ch_pos>0) && SUCCEEDED(retc))
      retc=m_lpOutFileObj->PutCharProc('\n', NULL);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->GetCharPos(&ch_pos);

   if((ch_pos==0) && SUCCEEDED(retc))
   {
      retc=GetGroupCount(pTagStack, &gr_cnt, uiazXmlGrTags);

// put indent charz
      for(ii=0; (ii<gr_cnt-1) && SUCCEEDED(retc); ii++)
         retc=m_lpOutFileObj->PutStr((const unsigned char *)"   ");
   }

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(iTag, pTagParsObj);

return(retc);
}


// --------------------------------------------------
HRESULT XmlRdt_tag::PutOpenTag(int iTag, XmlTagPars_tag *pTagParsObj, bool bOutFl)
{
HRESULT retc=S_OK;

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(bOutFl && SUCCEEDED(retc)) retc=PutTag(iTag, pTagParsObj);

   if(SUCCEEDED(retc)) retc=PushTag(&pTagStack, iTag, NULL, 0);
   if(SUCCEEDED(retc)) retc=pTagStack->SetOutFl(bOutFl);

return(retc);
}


// --------------------------------------------------
HRESULT XmlRdt_tag::PutClosingTag(int iTag, XmlTagPars_tag *pTagParsObj, bool bOutFl)
{
HRESULT retc=S_OK;
int tmp_tag;
int out_tag;

   if(pTagStack==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   out_tag=iTag|1;
   if(SUCCEEDED(retc)) retc=PopTag(&pTagStack, &tmp_tag);

   if((tmp_tag!=(out_tag&(~1))) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(bOutFl && SUCCEEDED(retc)) retc=PutTag(out_tag, pTagParsObj);

return(retc);
}


// --------------------------------------------------
HRESULT XmlRdt_tag::Process(void)
{
HRESULT retc=S_OK;
int in_ch;
XmlTagPars_tag *tag_pars=NULL;
int cur_tag;
bool emb_fl;
bool out_fl;
bool acc_decl_fl;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {

// input character
      retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, FALSE);

      if(SUCCEEDED(retc)) retc=pTagStack->GetOutFl(&out_fl);

      if(SUCCEEDED(retc))
      {
// tag processing
         if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag))
         {
// test whether tag contents must be output
            acc_decl_fl=(TvIntStrChr(aiXmlAccDeclArr, in_ch)!=NULL);
            if((bAccFl && (!acc_decl_fl)) || ((!bAccFl) && acc_decl_fl)) out_fl=False;
            if(
               (in_ch==XC_Dict) || (in_ch==XC_Dict_e) ||
               (in_ch==XC_Version) || (in_ch==XC_DocType) ||
               (in_ch==XC_DocType) || (in_ch==XC_StyleSheet)
              ) out_fl=True;

// tag output
            if(strcmp((const char *)plpszaXmlttDictTagsFull[(in_ch&(~1))+1-XC_FirstDictTag], "")!=0)
            {
               if((in_ch & 0x01) == 0) retc=PutOpenTag(in_ch, tag_pars, out_fl);
               else retc=PutClosingTag(in_ch, tag_pars, out_fl);
            }
            else if(out_fl) retc=m_lpOutFileObj->PutCharProc(in_ch, tag_pars);
         }
// ordinary character
         else
         {
            retc=pTagStack->GetCurTag(&cur_tag);
            if(SUCCEEDED(retc)) retc=XmltTestEmbedded('A', cur_tag, &emb_fl);
            if(SUCCEEDED(retc))
            {
               if(emb_fl){ if(out_fl) retc=m_lpOutFileObj->PutCharProc(in_ch, tag_pars); }
               else
               {
                  if(TvStrChr(lpszSpcEol, in_ch)==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT,
                        (unsigned char *)"Free text outside tag", FALSE, __FILE__, __LINE__, 0L);
               }
            }
         }
      }

      KP_DELETE(tag_pars);

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
char *l_argv[3+RP_MAX_TAGS+1];
int ii;

   printf("\nXML dictionary tag eliminator\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc>3)
   {
      for(ii=0; (ii<argc) && (ii<3+RP_MAX_TAGS+1); ii++) l_argv[ii]=argv[ii];
   }
#ifdef Debug
   else
   {
      l_argc=5;
      l_argv[0]="xmlrdt";
      l_argv[1]="/home/kp/source/tev/ohe/ohe.xml";
      l_argv[2]="/home/kp/source/tev/ohe/ohe1.xml";
      l_argv[3]="-pr";
      l_argv[4]="-tw";
   }
#endif

   if(l_argc>=3)
   {
      if(SUCCEEDED(retc))
      {
         pXmlRdt = new XmlRdt_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
         if(pXmlRdt!=NULL)
         {
            retc=pXmlRdt->GetOpenResult();

            if(SUCCEEDED(retc))
               for(ii=3; (ii<l_argc) && SUCCEEDED(retc); ii++)
                  retc=pXmlRdt->AcceptDeclineXmlTag((const unsigned char *)(l_argv[ii]));

            if(SUCCEEDED(retc)) retc=pXmlRdt->Process();

            retc0=pXmlRdt->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;

            KP_DELETE(pXmlRdt);

            if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>xmlrdt.exe infile.xml outfile.xml hw base v tg tw -eg -id\n");
      printf("                                                    `----------------' \n");
      printf("                                                             |\n");
      printf("                                  tags to extract -----------'\n");
      printf("                                  tags to eliminate ---.\n");
      printf("                                                       |\n");
      printf("                                                    ,-----.\n");
      printf("               c:>xmlrdt.exe infile.xml outfile.xml -pr -tg\n\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
