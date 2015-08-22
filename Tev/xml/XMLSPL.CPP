// ==================================================
// xmlspl.cpp
// splitting of comma-delimited xml tag contents to separate tags


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

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
#include "xmlt.h"
#include "xmlo2.h"
#include "xmlspl.h"


// ================================================== objects
XmlSpl_tag *pXmlSpl=NULL;
KpErrorProc_tag KpErrorProc(TRUE, 71);


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


// ================================================== public methods of XmlSpl_tag
XmlSpl_tag::XmlSpl_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlO2_tag()
{
   pTagStack=NULL;

   KpErrorProc.SetLPar(0L);
   lhOpenResult=OpenFile(lpszInFname, (const unsigned char *)"rb",
                           lpszOutFname, (const unsigned char *)"w");
   lMaxSeIx=0L;
}


// --------------------------------------------------
XmlSpl_tag::~XmlSpl_tag(void)
{
   XmlO2_tag_destructor();

   if(pTagStack!=NULL)
   {
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
      KP_DELETE(pTagStack);
   }
}


// --------------------------------------------------
HRESULT XmlSpl_tag::PutTag(int iTag, XmlTagPars_tag *pTagParsObj)
{
HRESULT retc=S_OK;
int ii;
int gr_cnt;
int ch_pos;

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, lEntryId);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->GetCharPos(&ch_pos, XL_IX_DataFile);

   if((TvIstrInt(uiazXmlGrTags, iTag)!=NULL) && (ch_pos>0) && SUCCEEDED(retc))
      retc=lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->GetCharPos(&ch_pos, XL_IX_DataFile);

   if((ch_pos==0) && SUCCEEDED(retc))
   {
      retc=GetGroupCount(pTagStack, &gr_cnt, uiazXmlGrTags);

// put indent charz
      for(ii=0; (ii<gr_cnt-1) && SUCCEEDED(retc); ii++)
         retc=lpOutFileObj->PutStr((const unsigned char *)"   ", XL_IX_DataFile);
   }

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(iTag, pTagParsObj, XL_IX_DataFile);

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpl_tag::PutOpenTag(int iTag, XmlTagPars_tag *pTagParsObj)
{
HRESULT retc=S_OK;

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, lEntryId);

   if(SUCCEEDED(retc)) retc=PutTag(iTag, pTagParsObj);

   if(SUCCEEDED(retc)) retc=PushTag(&pTagStack, iTag, NULL, 0);

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpl_tag::PutClosingTag(int iTag, XmlTagPars_tag *pTagParsObj)
{
HRESULT retc=S_OK;
int tmp_tag;
int out_tag;

   if(pTagStack==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, TRUE, __FILE__, __LINE__, lEntryId);

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, lEntryId);

   out_tag=iTag|1;
   if(SUCCEEDED(retc)) retc=PopTag(&pTagStack, &tmp_tag);
   if((tmp_tag==XC_Variant) && (out_tag==XC_HeadWord_e) && SUCCEEDED(retc)) out_tag=XC_Variant_e;

   if((tmp_tag!=(out_tag&(~1))) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, TRUE, __FILE__, __LINE__, lEntryId);

   if(SUCCEEDED(retc)) retc=PutTag(out_tag, pTagParsObj);

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpl_tag::Process(void)
{
HRESULT retc=S_OK;
int in_ch;
XmlTagPars_tag *tag_pars=NULL;
int tmp_tag;
bool emb_fl;
bool first_ch=True;
int exampl_lev=0;
bool cont_fl;


   if((lpInFileObj==NULL) || (lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {
      retc=lpInFileObj->GetCharProc(&in_ch, &tag_pars, XL_IX_DataFile, FALSE);

      if(SUCCEEDED(retc))
      {
         switch(in_ch)
         {
         case XC_StEntry:
            tmp_tag=C_Nul;
            if(pTagStack!=NULL) retc=GetStackTag(pTagStack, 0, &tmp_tag);
            if(tmp_tag!=XC_Dict)
            {
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, TRUE, __FILE__, __LINE__, lEntryId);
               while((pTagStack!=NULL) && SUCCEEDED(retc)) retc=PopTag(&pTagStack, &tmp_tag);
               if(SUCCEEDED(retc)) retc=PushTag(&pTagStack, XC_Dict, NULL, 0);
            }
            break;

         case XC_ExampleGroup:
         case XC_IdiomGroup:
            exampl_lev++;
            break;
         case XC_ExampleGroup_e:
         case XC_IdiomGroup_e:
            exampl_lev--;
            break;
         }

         tmp_tag=C_Nul;
         if(pTagStack!=NULL) retc=GetStackTag(pTagStack, 0, &tmp_tag);

         cont_fl=True;

         if(SUCCEEDED(retc)) switch(in_ch)
         {
         case ',':
            if(exampl_lev==0) switch(tmp_tag)
            {
            case XC_HeadWord:
               retc=PutClosingTag(tmp_tag|1, NULL);
               if(SUCCEEDED(retc)) retc=PutOpenTag(XC_Variant, NULL);
               first_ch=True;
               cont_fl=False;
               break;
            case XC_Variant:
            case XC_VarNorm:
//          case XC_CompoundWord:
            case XC_Pron:
            case XC_FormDst:
            case XC_FormSrc:
            case XC_Control:
            case XC_TrWord:
               retc=PutClosingTag(tmp_tag|1, NULL);
               if(SUCCEEDED(retc)) retc=PutOpenTag(tmp_tag&(~1), NULL);
               first_ch=True;
               cont_fl=False;
               break;
            }
            break;

         case ';':
            if(exampl_lev==0) switch(tmp_tag)
            {
            case XC_TrWord:
               retc=PutClosingTag(XC_TrWord_e, NULL);
               if(SUCCEEDED(retc)) retc=PutClosingTag(XC_TranslGroup_e, NULL);
               if(SUCCEEDED(retc)) retc=PutOpenTag(XC_TranslGroup, NULL);
               if(SUCCEEDED(retc)) retc=PutOpenTag(XC_TrWord, NULL);
               first_ch=True;
               cont_fl=False;
            }
            break;

         } // if(SUCCEEDED(retc)) switch(in_ch)


         if(cont_fl && SUCCEEDED(retc))
         {
            if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag))
            {
               if(strlen(plpszaXmlttDictTags[(in_ch|1)-XC_FirstDictTag])>0)
               {
                  if((in_ch&1)==0)
                  {
                     first_ch=True;
                     retc=PutOpenTag(in_ch, tag_pars);
                  }
                  else
                  {
                     retc=PutClosingTag(in_ch, tag_pars);

                     tmp_tag=C_Nul;
                     if((pTagStack!=NULL) && SUCCEEDED(retc)) retc=GetStackTag(pTagStack, 0, &tmp_tag);

                     if(SUCCEEDED(retc))
                     {
                        retc=XmltTestEmbedded('A', tmp_tag, &emb_fl);
                        first_ch=(!emb_fl);
                     }
                  }
               }
               else retc=lpOutFileObj->PutCharProc(in_ch, tag_pars, XL_IX_DataFile);
            }
            else
            {
               if(SUCCEEDED(retc)) retc=XmltTestEmbedded(in_ch, tmp_tag, &emb_fl);

               if(SUCCEEDED(retc))
               {
                  if(emb_fl)
                  {
                     if(TvStrChr(lpszSpcEol, in_ch)!=NULL)
                     {
                        if(!first_ch)
                           retc=lpOutFileObj->PutCharProc(in_ch, tag_pars, XL_IX_DataFile);
                     }
                     else
                     {
                        first_ch=False;
                        retc=lpOutFileObj->PutCharProc(in_ch, tag_pars, XL_IX_DataFile);
                     }
                  }
                  else
                  {
                     if(TvStrChr(lpszSpcEol, in_ch)!=NULL)
                     {
                        if((!first_ch) && SUCCEEDED(retc))
                           retc=lpOutFileObj->PutCharProc(in_ch, tag_pars, XL_IX_DataFile);
                     }
                     else
                     {
                        first_ch=False;
                        if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(in_ch, tag_pars, XL_IX_DataFile);
                        if(SUCCEEDED(retc))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, NULL, TRUE, __FILE__, __LINE__, lEntryId);
                     }

                  } // else // if(emb_fl)

               } // if(SUCCEEDED(retc))

            } // else // if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag))

         } // if(cont_fl && SUCCEEDED(retc))

      } // if(SUCCEEDED(retc))

   } while(SUCCEEDED(retc));

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

   printf("\nXML tag splitter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==3)
   {
      l_argv[0]=argv[0];
      l_argv[1]=argv[1];
      l_argv[2]=argv[2];
   }
#ifdef Debug
   else
   {
      l_argc=3;
      l_argv[0]="xmlspl";
      l_argv[1]="/home/kp/source/tev/alk/alk.xml";
      l_argv[2]="/home/kp/source/tev/alk/spl.xml";
   }
#endif

   if(l_argc==3)
   {
      if(SUCCEEDED(retc))
      {
         KP_NEWO(pXmlSpl, XmlSpl_tag((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]));

         if(SUCCEEDED(retc)) retc=pXmlSpl->Process();

         if(pXmlSpl!=NULL)
         {
            retc0=pXmlSpl->CloseFiles(SUCCEEDED(retc));
            if(SUCCEEDED(retc)) retc=retc0;
         }

         KP_DELETE(pXmlSpl);
      }
   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("               c:>XmlSpl.exe infile.xml outfile.xml\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
