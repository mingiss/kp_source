// ==================================================
// xmlg2t.cpp, former lvzg2t.cpp, former xmll2t.cpp
// LVZ LzdSGML to XMLT converter


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif
#include <richedit.h>
#include <Richole.h>
#include <time.h>

#include "kpstdlib.h"
#include "kptree.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kperr.h"
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindows.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
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
#include "xmlsty.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "kpcapp.h"
#include "kpstap.h"
#include "xmlg2t.h"


#define IN_FILE_FORMAT XM_VERS_SGML_TAGE


// ================================================== objects
const unsigned char lpszProdName[] = "xmlg2t";
XmlG2T *pXmlG2T=NULL;
KpErrorProcClass KpErrorProc(TRUE, 71);
bool bServiceFl=False;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// ================================================== public methods of XmlG2T
XmlG2T::XmlG2T(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
: XmlOI2(False)
{
   KpErrorProc.SetLPar(0L);
   if(SUCCEEDED(m_lhOpenResult))
      m_lhOpenResult=OpenFileLocal(lpszInFname, lpszOutFname);
}


// --------------------------------------------------
HRESULT XmlG2T::OpenFileLocal(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
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
      m_lpInFileObj = new XmlI(m_lpszInFileName, (const unsigned char *)"rb", CreateNew8File,
                                       plpszaXmlSpecCharTagsEdi,
                                       NULL, NULL, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaSgmDictTags,
                                       IN_FILE_FORMAT, iaSgmDictCodeTables, True, False, False);

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
      m_lpOutFileObj = new XmlI(m_lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                                       plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, caIxLangs, iaIxEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                       XM_VERS_XML10, iaXmlDictNulCodeTables, True, True, False);
      if(m_lpOutFileObj!=NULL)
         retc=m_lpOutFileObj->GetOpenResult();
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlG2T::Process(bool bTrimSpaces)
{
HRESULT retc=S_OK;
KpChar in_ch;
XmlTagPars *tag_pars=NULL;
XmlTagPars *tag_pars_tmp=NULL;
KpChar cur_tag;
KpChar prev_tag;
int smb_cnt=2;
bool first=True;
bool tag_fl=False;
KpChar last_char=C_Nul;
bool emb_fl;
int ii;

#if FALSE

KpChar test_ch;
KpChar test_tag;
KpChar tag_sav;

unsigned char ch_tag_buf[TV_XL_MAX_TAG_WDT+1]; // contents of XC_Info for further scanning in tag names table
int ch_tag_buf_idx=0; // index to ch_tag_buf

int sav_buf[KP_MAX_FILE_LIN_LEN+1]; // buffer for saving tag contents for further XC_Info processing
int buf_ix=0; // sav_buf index

#endif


KpChar in_ch_tmp;

int ctg_cnt=0;
int mng_cnt=0;
int mng_cpd_cnt=0;
int mng_id_cnt=0;
int mng_near_cnt=0;
unsigned char out_str[TV_XL_HW_IX_LEN+KP_MAX_FILE_LIN_WDT+1];
const unsigned char *form_str;

int conv_tag_end=0;

   m_lEntryId=0L;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((m_pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutXmlHatI(m_lpOutFileObj, m_lpszOutFileName);
   if(SUCCEEDED(retc)) retc=PushTag(&m_pTagStack, (KpChar)XC_Dict, NULL, 0);

   if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(XC_StEntry>=m_lpInFileObj->iLastDictTag)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) do
   {

// input character
      retc=m_lpInFileObj->GetCharProc(&in_ch, &tag_pars, False, True);

// if(m_lEntryId==10795)
// m_lEntryId=10795;

if(in_ch==XC_Parenth)
in_ch=(KpChar)XC_Parenth;

// if(in_ch==XC_Parenth_e)
// in_ch=XC_Parenth_e;

// convert tags according to following XC_Info
#if FALSE
      if(
         (
            (in_ch==XC_HeadWord) ||
            (in_ch==XC_Variant) ||
            (in_ch==XC_FormDst) ||
//          (in_ch==XC_TrWord) ||
            (in_ch==XC_Text)
         ) &&
         (IN_FILE_FORMAT==XM_VERS_SGML_TAGE) &&
         SUCCEEDED(retc)
        )
      {

// if((m_lEntryId==263) && (in_ch==XC_Text))
// m_lEntryId=263;

// save tag contents
         buf_ix=0;
         do
         {
            retc=m_lpInFileObj->GetCharProc(sav_buf+buf_ix, &tag_pars_tmp, FALSE);
            if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
            buf_ix++;
            if((buf_ix>=KP_MAX_FILE_LIN_LEN-2) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
         } while((sav_buf[buf_ix-1]!=(in_ch|0x01)) && SUCCEEDED(retc));

         conv_tag_end=buf_ix-1;

// next tag
         if(SUCCEEDED(retc))
         {
            do
            {
               retc=m_lpInFileObj->GetCharProc(sav_buf+buf_ix, &tag_pars_tmp, FALSE);
//             if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
            }
            while((TvStrChr(lpszSpcEol, sav_buf[buf_ix])!=NULL) && SUCCEEDED(retc));

            buf_ix++;

// input spec symbol or homonym number
            test_tag=sav_buf[buf_ix-1];
            if(
               ((test_tag==XC_Symb) || (test_tag==XC_Hom)) &&
               (IN_FILE_FORMAT==XM_VERS_SGML_TAGE) &&
               SUCCEEDED(retc)
              )
            {
               if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) do
               {
                  retc=m_lpInFileObj->GetCharProc(sav_buf+buf_ix, &tag_pars_tmp, FALSE);
                  if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  buf_ix++;
                  if((buf_ix>=KP_MAX_FILE_LIN_LEN-2) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
               } while((sav_buf[buf_ix-1]!=(test_tag|0x01)) && SUCCEEDED(retc));

               if(SUCCEEDED(retc)) test_ch=sav_buf[buf_ix-2];
// next tag
               if(SUCCEEDED(retc)) do
               {
                  retc=m_lpInFileObj->GetCharProc(sav_buf+buf_ix, &tag_pars_tmp, FALSE);
//                if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, NULL, TRUE, __FILE__, __LINE__, 0L);
               }
               while((TvStrChr(lpszSpcEol, sav_buf[buf_ix])!=NULL) && SUCCEEDED(retc));

               buf_ix++;

// enclose trailing spec symbols to contents of variant (etc.)
               if(
               /* (sav_buf[buf_ix-1]==XC_Info) && */
                  (
                     (
                        (test_ch!=C_o_Slash) && // XC_Inform
                        ((test_ch!=C_Multipl) || (!bMultiplToVeryInform)) && // XC_VeryInform
                        (test_ch!=C_Rouble) &&  // XC_Vulgar
                        (test_ch!=C_cent) &&    // XC_Uncount
                        (test_ch!=C_c) &&       // XC_Count
                        (test_ch!=C_PlMin) &&   // XC_Approx
                        (test_ch!=C_Dag) &&     // XC_Obs
                        (test_ch!=C_Ddag)       // XC_Arch
                     ) ||
                     (test_tag!=XC_Symb)
                  ) &&
                  SUCCEEDED(retc)
                 )
               {
                  conv_tag_end=buf_ix-1;

                  tag_sav=sav_buf[buf_ix-1];
                  sav_buf[buf_ix-1]=(in_ch|0x01);
                  sav_buf[buf_ix++]=tag_sav;

                  ii=buf_ix;
                  do{ --ii; } while((sav_buf[ii]!=test_tag) && (ii>1));
                  if((ii<1) || (sav_buf[ii]!=test_tag))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc))
                  {
                     ii--;
                     if(sav_buf[ii]!=(in_ch|0x01))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc))
                  {
                     if(test_tag==XC_Symb) sav_buf[ii]=C_Spc;
                     else sav_buf[ii]=C_Nul;
                  }
               }

            } // if(((test_tag==XC_Symb) || (test_tag==XC_Hom)) && (IN_FILE_FORMAT==XM_VERS_SGML_TAGE) && SUCCEEDED(retc))

// input contents of XC_Info
            if((sav_buf[buf_ix-1]==XC_Info) && SUCCEEDED(retc))
            {
               if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

               buf_ix--;
               ch_tag_buf_idx=0;
               ch_tag_buf[ch_tag_buf_idx++]=TV_XM_TagStartCh;
               do
               {
                  retc=m_lpInFileObj->GetCharProc(&in_ch_tmp, &tag_pars_tmp, FALSE);
                  if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  if(in_ch_tmp!=XC_Info_e)
                  {
                     if((ch_tag_buf_idx>=TV_XL_MAX_TAG_WDT) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
                     if((in_ch_tmp>=KPT_Ctbsiz) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                     if(SUCCEEDED(retc)) ch_tag_buf[ch_tag_buf_idx++]=in_ch_tmp;
                  }
               } while((in_ch_tmp!=XC_Info_e) && SUCCEEDED(retc));

// scan new tag
               ch_tag_buf[ch_tag_buf_idx]=Nul;
               if(SUCCEEDED(retc))
               {     
                  retc=GetTagIndex(&in_ch_tmp, ch_tag_buf, plpszaXmlttDictTagsFull);
                  if(SUCCEEDED(retc)) in_ch_tmp += XC_FirstDictTag;
                  else
                     retc=KpErrorProc.OutputErrorMessage(retc, tag_buf, True, __FILE__, __LINE__, 0L);
               }

// convert saved tag
               if(SUCCEEDED(retc))
               {
                  if(
                     (
                        (in_ch==XC_HeadWord) &&
                           (in_ch_tmp!=XC_Base) &&
                           (in_ch_tmp!=XC_HBase)
                     ) ||
                     (
                        (in_ch==XC_Variant) &&
                           (in_ch_tmp!=XC_CompoundWord) &&
                           (in_ch_tmp!=XC_Struct) &&
                           (in_ch_tmp!=XC_OblStruct) &&
                           (in_ch_tmp!=XC_Derivative) &&
                           (in_ch_tmp!=XC_Example) &&
                           (in_ch_tmp!=XC_Usage) &&
                           (in_ch_tmp!=XC_SrcWord)
                     ) ||
                     (
                        (in_ch==XC_FormDst) &&
                           (in_ch_tmp!=XC_FormDst) &&
                           (in_ch_tmp!=XC_FormSrc) &&
                           (in_ch_tmp!=XC_Variant)
                     )
                    )
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

                           if((sav_buf[conv_tag_end]!=(in_ch|0x01)) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
                           
                  in_ch=in_ch_tmp;
                  sav_buf[conv_tag_end]=in_ch|0x01;
               }

            } // if((sav_buf[buf_ix-1]==XC_Info) && SUCCEEDED(retc))

         } // if(SUCCEEDED(retc))

// return back converted tag
         while((buf_ix>0) && SUCCEEDED(retc))
            retc=m_lpInFileObj->UnGetCharProc(sav_buf[--buf_ix], NULL);

      } // if(((in_ch==XC_HeadWord) || (in_ch==XC_Variant) || (in_ch==XC_FormDst)) && (IN_FILE_FORMAT==XM_VERS_SGML_TAGE) && SUCCEEDED(retc))
#endif


#if FALSE
if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag))
   printf("%s\n", plpszaXmlttDictTagsFull[in_ch-XC_FirstDictTag]);
else printf("%c %d\n", in_ch, in_ch);
#endif

// if(in_ch==XC_Symb)
// in_ch=XC_Symb;

// tag processing
      tag_fl=False;

      KP_DELETE(tag_pars):

//    if(SUCCEEDED(retc)) switch(in_ch)
//    {
//    case C_Lpar: in_ch=XC_Parenth; break; // '('
//    case C_Rpar: in_ch=XC_Parenth_e; break; // ')'
//    }

      if(
         (
            ((in_ch >= XC_FirstDictTag) && (in_ch < XC_LastDictTag)) ||
            ((in_ch >= XL_FirstSysTag) && (in_ch < XL_LastSysTag))
         ) && 
         SUCCEEDED(retc)
        )
      {
// ---------
         if(SUCCEEDED(retc)) retc=m_pTagStack->GetCurTag(&cur_tag);
         if(SUCCEEDED(retc)) retc=GetStackTag(m_pTagStack, 1, &prev_tag);
         if(SUCCEEDED(retc)) switch(in_ch)
         {
         case XC_StEntry:
            if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames[XC_StEntry-m_lpInFileObj->iFirstDictTag][0])
            {
               m_lEntryId++;
               retc=KpErrorProc.SetLPar(m_lEntryId);
               if(SUCCEEDED(retc))
               {
                  if(tag_pars==NULL)
                  {
                     tag_pars=new XmlTagPars((const unsigned char *)"id", m_lEntryId);
                     if(tag_pars==NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
                  }
               }
            }

//          m_lpszHwSav[0]=Nul;
            KpErrorProc.szaMsgText[0]=Nul;

            ctg_cnt=0;
            mng_cnt=0;
            mng_cpd_cnt=0;
            mng_id_cnt=0;
            mng_near_cnt=0;

            break;

         case XC_HeadWordGroup:
            if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames[XC_StEntry-m_lpInFileObj->iFirstDictTag][0]==Nul)
            {
               m_lEntryId++;
               retc=KpErrorProc.SetLPar(m_lEntryId);

               if(SUCCEEDED(retc))
               {
                  tag_pars_tmp=new XmlTagPars((const unsigned char *)"id", m_lEntryId);
                  if(tag_pars_tmp==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc)) retc=PutOpenTag((KpChar)XC_StEntry, tag_pars_tmp);
               KP_DELETE(tag_pars_tmp);
            }
//       case XC_StEntry:
         case XC_NrtEntry:
         case XC_HeadWord:
//          m_lpszHwSav[0]=Nul;
            KpErrorProc.szaMsgText[0]=Nul;

            ctg_cnt=0;
            mng_cnt=0;
            mng_cpd_cnt=0;
            mng_id_cnt=0;
            mng_near_cnt=0;
            break;

         case XC_CompoundGroup:
         case XC_CompoundWord:
         case XC_DerivGroup:
         case XC_Derivative:
//       case XC_SrcWord:
            ctg_cnt=0;  // ???
            mng_cnt=0;  // ???
            mng_cpd_cnt=0;
            mng_id_cnt=0;  // ???
            mng_near_cnt=0;
            break;

         case XC_IdiomGroup:
         case XC_Idiom:
            mng_id_cnt=0;
            mng_near_cnt=0;
            break;
                        
         case XC_StructGroup:
         case XC_StructGroupForced:
         case XC_Struct:
         case XC_OblStruct:
//       case XC_SrcWord:
            mng_cpd_cnt=0;
            mng_near_cnt=0;
            break;


         case XC_ExampleGroup:                        
         case XC_ExampleGroupForced:                        
//       case XC_Example:        // look later
//       case XC_Usage:
            mng_near_cnt=0;
            break;

         case XC_CtgGroup:
            ctg_cnt++;
            mng_cnt=0;
            mng_cpd_cnt=0;
            mng_id_cnt=0;
            mng_near_cnt=0;

            if(tag_pars!=NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=FormatRoman(out_str, ctg_cnt);
            if(SUCCEEDED(retc))
            {
               tag_pars=new XmlTagPars((const unsigned char *)"num", out_str);
               if(tag_pars==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
            }
            break;

         case XC_CpdMngGroup:
//          in_ch=(KpChar)XC_MngGroup;

            mng_cpd_cnt++;
            mng_near_cnt=0;

            if(tag_pars!=NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               tag_pars=new XmlTagPars((const unsigned char *)"num", mng_cpd_cnt);
               if(tag_pars==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
            }
            break;

         case XC_IdMngGroup:
//          in_ch=(KpChar)XC_MngGroup;

            mng_id_cnt++;
            mng_near_cnt=0;

            if(tag_pars!=NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               tag_pars=new XmlTagPars((const unsigned char *)"num", mng_id_cnt);
               if(tag_pars==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
            }
            break;

         case XC_MngGroup:
            mng_cnt++;
            mng_cpd_cnt=0;
            mng_id_cnt=0;
            mng_near_cnt=0;

            if(tag_pars!=NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               tag_pars=new XmlTagPars((const unsigned char *)"num", mng_cnt);
               if(tag_pars==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
            }
            break;

         case XC_CpdMngGroup_e:
         case XC_IdMngGroup_e:
//          in_ch=(KpChar)XC_MngGroup_e;
            break;

         case XC_MngNearGroup:
            mng_near_cnt++;

            if(tag_pars!=NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               out_str[0]='a'-1+mng_near_cnt;
               out_str[1]=Nul;
            }
            if(SUCCEEDED(retc))
            {
               tag_pars=new XmlTagPars((const unsigned char *)"num", out_str);
               if(tag_pars==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
            }
            break;

         case XL_Text:
         case XL_Text_e:
            in_ch=C_Nul;
            break;
#if FALSE
         case XL_Text:
            switch(cur_tag)
            {
            case XC_CtgGroup:
            case XC_MngGroup:
               in_ch=XC_ExplNorm;
               break;
            case XC_TranslGroup: in_ch=XC_TrWord; break;
            case XC_Parenth:
               if(prev_tag==XC_TranslGroup) in_ch=XC_TrWord;
               else in_ch=C_Nul;
               break;
            case XC_CtrlGroup:
               in_ch=XC_CtrlDst;
               break;
            case XC_Variant:
            case XC_CompoundWord:
            case XC_Struct:
            case XC_OblStruct:
            case XC_Derivative:
            case XC_Example:
            case XC_Usage:
            case XC_Idiom:
            case XC_SrcWord:
            case XC_ExplSrc:
            case XC_ExplDst:
            case XC_FwNote:
            case XC_UsNote:
            case XC_Gloss:
            case XC_Expand:
            case XC_CtrlSrc:
            case XC_FormSrc:
            case XC_FormDst:
            case XC_PartOfSpeechSrc:
            case XC_PartOfSpeechDst:
            case XC_StressPar:
            case XC_Paragraph:
            case XC_Italic:
               in_ch=C_Nul;
               break;
            case XC_PrGroup:
               in_ch=XC_ExplSrc;
               break;
            }
            break;

         case XL_Text_e:
            switch(cur_tag)
            {
            case XC_ExplNorm:
               if((prev_tag==XC_CtgGroup) || (prev_tag==XC_MngGroup)) in_ch=XC_ExplNorm_e;
               break;
            case XC_Parenth: in_ch=C_Nul; break;
            case XC_TrWord:
               if((prev_tag==XC_TranslGroup) || (prev_tag==XC_Parenth)) in_ch=XC_TrWord_e;
               break;
            case XC_CtrlDst:
               if(prev_tag==XC_CtrlGroup) in_ch=XC_CtrlDst_e;
               break;
            case XC_Variant:
            case XC_CompoundWord:
            case XC_Struct:
            case XC_OblStruct:
            case XC_Derivative:
            case XC_SrcWord:
            case XC_Example:
            case XC_Usage:
            case XC_Idiom:
            case XC_FwNote:
            case XC_UsNote:
            case XC_Gloss:
            case XC_Expand:
            case XC_CtrlSrc:
            case XC_FormSrc:
            case XC_FormDst:
            case XC_PartOfSpeechDst:
            case XC_PartOfSpeechSrc:
            case XC_StressPar:
            case XC_Paragraph:
            case XC_Italic:
               in_ch=C_Nul;
               break;
            case XC_ExplSrc:
               if(prev_tag==XC_PrGroup) in_ch=XC_ExplSrc_e;
               else in_ch=C_Nul;
               break;
            }
            break;
#endif

//       case XC_PrGroup_e:
//          if((cur_tag==XC_Pron) && (IN_FILE_FORMAT==XM_VERS_SGML_TAGE))
//             retc=PutClosingTag(XC_Pron_e, NULL);
//          break;

//       case XC_CtrlGroup:
//          if((cur_tag!=XC_Parenth) && (IN_FILE_FORMAT==XM_VERS_SGML_TAGE))
//          {
//             if(last_char)
//             {
//                retc=m_lpOutFileObj->PutCharProc(last_char, NULL);
//                last_char=C_Nul;
//             }
//             retc=PutOpenTag(XC_Parenth, NULL);
//          }
//          break;

         case XC_ModCpdSrc:
         case XC_ModCpdDst:
            if(cur_tag!=XC_ModCpdGroup) retc=PutOpenTag((KpChar)XC_ModCpdGroup, NULL);
            break;

         case XC_ModCpdSrc_e:
         case XC_ModCpdDst_e:
            if(SUCCEEDED(retc)) do
            {
               retc=m_lpInFileObj->GetCharProc(&in_ch_tmp, &tag_pars_tmp, False, True);
               if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
            }
            while((TvStrChr(lpszSpcEol, in_ch_tmp)!=NULL) && SUCCEEDED(retc));
            if(SUCCEEDED(retc))
               retc=m_lpInFileObj->UnGetCharProc(in_ch_tmp, NULL);
            if((in_ch_tmp!=XC_ModCpdSrc) && (in_ch_tmp!=XC_ModCpdDst) && SUCCEEDED(retc))
               retc=m_lpInFileObj->UnGetCharProc((KpChar)XC_ModCpdGroup_e, NULL);
            break;

         case XC_Variant:
         case XC_SrcWord:
//          if(cur_tag==XC_ExampleGroup) in_ch=(KpChar)XC_Example;
//          if(cur_tag==XC_IdiomGroup) in_ch=(KpChar)XC_Idiom;
//          if(cur_tag==XC_StructGroup) in_ch=(KpChar)XC_Struct;
            if(cur_tag==XC_CompoundGroup) in_ch=(KpChar)XC_CompoundWord;
            if(cur_tag==XC_DerivGroup) in_ch=(KpChar)XC_Derivative;
            break;
         case XC_Variant_e:
         case XC_SrcWord_e:
//          if(cur_tag==XC_Example) in_ch=(KpChar)XC_Example_e;
//          if(cur_tag==XC_Idiom) in_ch=(KpChar)XC_Idiom_e;
//          if(cur_tag==XC_Struct) in_ch=(KpChar)XC_Struct_e;
            if(cur_tag==XC_CompoundWord) in_ch=(KpChar)XC_CompoundWord_e;
            if(cur_tag==XC_Derivative) in_ch=(KpChar)XC_Derivative_e;
            break;

         case XC_Example:
            mng_near_cnt=0;

            if(cur_tag==XC_IdiomGroup) in_ch=(KpChar)XC_Idiom;
            if(cur_tag==XC_StructGroup) in_ch=(KpChar)XC_Struct;
            break;
         case XC_Example_e:
            if(cur_tag==XC_Idiom) in_ch=(KpChar)XC_Idiom_e;
            if(cur_tag==XC_Struct) in_ch=(KpChar)XC_Struct_e;
            break;

         case XC_PartOfSpeechSrc:
            if(
               (cur_tag==XC_TranslGroup) ||
               (cur_tag==XC_TrWord) ||
               (
                  (
                     (cur_tag==XC_Parenth) ||
                     (cur_tag==XC_CtrlGroup)
                  ) &&
                  (
                     (prev_tag==XC_TranslGroup) ||
                     (prev_tag==XC_TrWord)
                  )
               )
              )
               in_ch=(KpChar)XC_PartOfSpeechDst;
            break;
         case XC_PartOfSpeechSrc_e:
            if(cur_tag==XC_PartOfSpeechDst) in_ch=(KpChar)XC_PartOfSpeechDst_e;
            break;

         case XC_FormDst:
            if((cur_tag!=XC_FormGroupDst) && (prev_tag!=XC_FormGroupDst))
               retc=PutOpenTag((KpChar)XC_FormGroupDst, NULL);
            break;
//       case XC_FormSrc:
//          if(cur_tag!=XC_FormGroupSrc)
//             retc=PutOpenTag(XC_FormGroupSrc, NULL);
//          break;
         case XC_FormDst_e:
         case XC_Parenth_e:
            if(SUCCEEDED(retc)) do
            {
               retc=m_lpInFileObj->GetCharProc(&in_ch_tmp, &tag_pars_tmp, False, True);
               if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
            }
            while((TvStrChr(lpszSpcEol, in_ch_tmp)!=NULL) && SUCCEEDED(retc));
            if(SUCCEEDED(retc))
               retc=m_lpInFileObj->UnGetCharProc(in_ch_tmp, NULL);
            if((in_ch_tmp!=XC_FormDst) && (in_ch_tmp!=XC_FormGroupDst_e) &&
               (in_ch_tmp!=XC_Parenth) && (in_ch_tmp!=XC_PunctMark) &&
               (in_ch_tmp!=XC_Abbr) && 
               (in_ch_tmp!=XC_Level) &&
//                (in_ch_tmp!=XC_LevelGroup) &&
//             (cur_tag!=XC_FormGroupDst) &&
               (prev_tag==XC_FormGroupDst) &&
               SUCCEEDED(retc))
               retc=m_lpInFileObj->UnGetCharProc((KpChar)XC_FormGroupDst_e, NULL);
            break;
                     
         case XC_LevelGroup_e:
         case XC_TranslGroup_e:
            if((cur_tag==XC_FormGroupDst) && SUCCEEDED(retc))
            {
               retc=m_lpInFileObj->UnGetCharProc(in_ch /* (KpChar)XC_LevelGroup_e */, NULL);
               in_ch = (KpChar)XC_FormGroupDst_e;
            }
            break;

//       case XC_FormSrc_e:
//          if(SUCCEEDED(retc)) do
//          {
//             retc=m_lpInFileObj->GetCharProc(&in_ch_tmp, &tag_pars_tmp, FALSE);
//             if((tag_pars_tmp!=NULL) && SUCCEEDED(retc))
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
//          }
//          while((TvStrChr(lpszSpcEol, in_ch_tmp)!=NULL) && SUCCEEDED(retc));
//          if(SUCCEEDED(retc))
//             retc=m_lpInFileObj->UnGetCharProc(in_ch_tmp, NULL);
//          if((in_ch_tmp!=XC_FormSrc) && (in_ch_tmp!=XC_FormGroupSrc_e) &&
//             (cur_tag!=XC_FormGroupSrc) && SUCCEEDED(retc))
//             retc=m_lpInFileObj->UnGetCharProc(XC_FormGroupSrc_e, NULL);
//          break;

         case XC_RefInf:
            in_ch=(KpChar)XC_Reference;
            break;
         case XC_RefInf_e:
            in_ch=(KpChar)XC_Reference_e;
            break;

         case XC_RefHom:
            in_ch=(KpChar)XC_Hom;
            break;
         case XC_RefHom_e:
            in_ch=(KpChar)XC_Hom_e;
            break;

         case XC_Symb:
         case XC_PunctMark:
            smb_cnt=0; 
            break;

         }

// tag output
         if(in_ch && SUCCEEDED(retc))
         {
            if(
//             (strcmp((const char *)plpszaXmlttDictTagsFull[(in_ch&(~1))+1-XC_FirstDictTag], "")!=0) ||
               (strcmp((const char *)GetTagName((in_ch&(~1))+1, plpszaXmlttDictTagsFull), "")!=0) ||
               ((in_ch & (~0x01)) == XC_Symb)
              )
            {
               tag_fl=True;

               if((in_ch & 0x01) == 0)
               {
                  first=True;
                  if(last_char!=C_Nul) retc=m_lpOutFileObj->PutCharProc(last_char, NULL);
                  if(SUCCEEDED(retc)) retc=PutOpenTag(in_ch, tag_pars);
               }
               else 
               {
                  if(last_char!=C_Nul)
                  {
                     if((cur_tag!=XC_TechNote) && (cur_tag!=XC_PunctMark) && (cur_tag!=XC_LevelGroup))
                     {
                        sprintf((char *)out_str, "Lizdas %ld, hw:%s : tarpai %s gale\n",
                           m_lEntryId, KpErrorProc.szaMsgText /* m_lpszHwSav */,
//                         plpszaSgmDictTags[cur_tag-XC_FirstDictTag]);
                           GetTagName(cur_tag, plpszaSgmDictTags)); 
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, out_str, FALSE, __FILE__, __LINE__, m_lEntryId);
                        printf((const char *)out_str);
                     }
                     
                     if((!bTrimSpaces) && SUCCEEDED(retc))
                        retc=m_lpOutFileObj->PutCharProc(last_char, NULL);
                  }
                  if(SUCCEEDED(retc)) retc=PutClosingTag(in_ch, tag_pars);
               }

               last_char=C_Nul;
            }
         }

         KP_DELETE(tag_pars);

         if(SUCCEEDED(retc)) retc=m_pTagStack->GetCurTag(&cur_tag);

// ---------
         if(in_ch && SUCCEEDED(retc)) switch(in_ch)
         {
         case XC_HeadWordGroup_e:
            if(SUCCEEDED(retc)) if(m_lpInFileObj->plpszaTagNames[XC_StEntry-m_lpInFileObj->iFirstDictTag][0]==Nul)
               retc=PutClosingTag((KpChar)XC_StEntry_e, NULL);
            break;

//       case XC_CtrlGroup_e:
//          if((cur_tag==XC_Parenth) && (IN_FILE_FORMAT==XM_VERS_SGML_TAGE))
//             retc=PutClosingTag(XC_Parenth_e, NULL);
//          break;
         }

      } // if((in_ch>=XC_FirstDictTag) && (in_ch<XC_LastDictTag) && SUCCEEDED(retc))

// -------------
      if(SUCCEEDED(retc)) retc=m_pTagStack->GetCurTag(&cur_tag);

// -------------
      if(SUCCEEDED(retc)) switch(cur_tag)
      {
      case XC_PrGroup:
      case XC_Pron:
      case XC_PronRed:
         if(in_ch==C_Grave) in_ch=C_ph_acc;  // '`'
         break;

      case XC_Symb:
         switch(in_ch)
         {
         case XC_Symb: break;    // ??? !!!

         case C_o_Slash: in_ch=(KpChar)XC_Inform; break;
         case C_Multipl: if(bMultiplToVeryInform) in_ch=(KpChar)XC_VeryInform; break; // dar patikrint popieriniam ohe - "bastard"
         case C_Rouble: in_ch=(KpChar)XC_Vulgar; break; // dar patikrint popieriniam ohe - "crap"

         case C_cent: in_ch=(KpChar)XC_Uncount; break;
         case C_c: in_ch=(KpChar)XC_Count; break;

         case C_PlMin: in_ch=(KpChar)XC_Approx; break;
         case C_Eq: in_ch=(KpChar)XC_Similar; break;

         case C_Dag: in_ch=(KpChar)XC_Obs; break;
         case C_Ddag: in_ch=(KpChar)XC_Arch; break;

         case C_Ast: in_ch=(KpChar)XC_Asterix; break;

         case C_Dots:
         case C_RO:
         case C_Pound:
         case C_Doll:
         case C_deg:
         case C_Perc:

         case C_C_Cedil:
         case C_c_Cedil:
            break;

         case XC_Symb_e:
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, "Tuscias <symb>", FALSE, __FILE__, __LINE__, 0L);
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
            break;
         }

         if((++smb_cnt>2) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         break;

      case XC_PunctMark:
//       if(in_ch==C_Spc) in_ch=C_Nul;

//       if((++smb_cnt>2) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         break;

      }

      if(SUCCEEDED(retc))
      {
         form_str=NULL;

         switch(in_ch)
         {
#if FALSE
// dabar su prefiksu '$' - konvertavimo i TEX stadijoje
         case C_Circ:   /*'^'*/
            in_ch=C_break;
#ifdef AUTO_LASTWORD
            form_str=(const unsigned char *)"Lizdas %ld, hw:%s : dirbtinis elutes lauzymas \'^\'\n";
#endif
            break;
#endif
#if FALSE
// dabar su prefiksu '$' - konvertavimo i TEX stadijoje
         case C_At:     /*'@'*/  
            in_ch=C_Ff;
            break;
#endif
         case C_Lslash: /*'\\'*/ in_ch=C_hyph; break;
         case C_Amp:    /*'&'*/
            in_ch=C_hhyph;
#ifdef AUTO_LASTWORD
            form_str=(const unsigned char *)"Lizdas %ld, hw:%s : dirbtinis kelimas \'&\'\n";
#endif
            break;
#if FALSE
// dabar su prefiksu '$' - konvertavimo i TEX stadijoje
         case C_Underl: /*'_'*/
//          in_ch=C_EnSpc;
//          form_str=(const unsigned char *)"Lizdas %ld, hw:%s : dirbtinis n-tarpas \'_\'\n";
            in_ch=C_NBSP;
            form_str=(const unsigned char *)"Lizdas %ld, hw:%s : dirbtinis NBSP \'_\'\n";
            break;
#endif
         case C_Numb:   /*'#'*/
            in_ch=C_QemSpc;
            form_str=(const unsigned char *)"Lizdas %ld, hw:%s : dirbtinis 1/4m-tarpas \'#\'\n";
            break;
         }

         if(form_str)
         {
            sprintf((char *)out_str, (const char *)form_str, m_lEntryId, KpErrorProc.szaMsgText /* m_lpszHwSav */);
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, out_str, FALSE, __FILE__, __LINE__, m_lEntryId);
            printf((const char *)out_str);
         }
      }

// ordinary character or symbol tags
      if((!tag_fl) && in_ch && SUCCEEDED(retc))
      {
//       if((cur_tag==XC_PrGroup) && (IN_FILE_FORMAT==XM_VERS_SGML_TAGE))
//       {
//          retc=PutOpenTag(XC_Pron, NULL);
//          if(SUCCEEDED(retc)) retc=m_pTagStack->GetCurTag(&cur_tag);
//       }

         if(SUCCEEDED(retc)) retc=XmltTestEmbedded(in_ch /* 'A' */, cur_tag, &emb_fl);

         if(SUCCEEDED(retc))
         {
            if(TvStrChr(lpszSpcEol, in_ch)!=NULL)
            {
               if(first && emb_fl)
               {
                  if((cur_tag!=XC_TechNote) && (cur_tag!=XC_PunctMark))
                  {
                     sprintf((char *)out_str, "Lizdas %ld, hw:%s : tarpai %s pradþioje\n",
                        m_lEntryId, KpErrorProc.szaMsgText /* m_lpszHwSav */,
//                      plpszaSgmDictTags[cur_tag-XC_FirstDictTag]);
                        GetTagName(cur_tag, plpszaSgmDictTags)); 
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, out_str, FALSE, __FILE__, __LINE__, m_lEntryId);
                     printf((const char *)out_str);
                  }
               }
               if(((!first) || (!bTrimSpaces)) && emb_fl) last_char=C_Spc;
            }
            else
            {
// output character
               first=False;

               if((!emb_fl) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False /* TRUE */, __FILE__, __LINE__, 0L);

// save current headword
               if(
                  (
                     (cur_tag==XC_HeadWord) ||
                     (cur_tag==XC_Base) ||
                     (cur_tag==XC_HBase)
                  ) &&
                  SUCCEEDED(retc)
                 )
               {
                  ii=(-1);
                  while(KpErrorProc.szaMsgText/*m_lpszHwSav*/[++ii]!=Nul);
                  if(ii>=KP_MSG_LEN/*TV_XL_HW_IX_LEN*/-3)
                    retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
               }

               if((last_char!=C_Nul) && SUCCEEDED(retc))
               {
                  retc=m_lpOutFileObj->PutCharProc(last_char, NULL);
                  if((cur_tag==XC_HeadWord) && SUCCEEDED(retc)) KpErrorProc.szaMsgText/*m_lpszHwSav*/[ii++]=(unsigned char)last_char;
                  last_char=C_Nul;
               }

               if(SUCCEEDED(retc)) retc=m_lpOutFileObj->PutCharProc(in_ch, tag_pars);
               if((cur_tag==XC_HeadWord) && SUCCEEDED(retc))
               {
                  KpErrorProc.szaMsgText/*m_lpszHwSav*/[ii++]=(unsigned char)TvToLat(in_ch);
                  KpErrorProc.szaMsgText/*m_lpszHwSav*/[ii++]=Nul;
               }

if(in_ch==C_a_Grave)
in_ch=C_a_Grave;

            }
         }
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
char *l_argv[3];
unsigned char disk[KP_MAX_FNAME_LEN+1];
unsigned char path[KP_MAX_FNAME_LEN+1];
unsigned char fname[KP_MAX_FNAME_LEN+1];
unsigned char ftype[KP_MAX_FTYPE_LEN+1];

   printf("\nSGML Tage to XML dictionary converter\n\n");

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

         l_argv[0]="lvzg2t";
//       l_argv[0]="vlzg2t";

//       l_argv[1]="/home/kp/source/tev/ohe/ohe.sgm";
//       l_argv[1]="f:/wrk/kp/source/tev/lvz/lvza.sgm";
//       l_argv[1]="D:/kp/source/tev/lvz/lvz_comp.sgm";
//       l_argv[1]="f:/wrk/kp/source/tev/lvz/inv_exp/lvzj.sgm";
//       l_argv[1]="f:/kp/source/tev/lvz/lvzb.sgm";
//       l_argv[1]="f:/kp/source/tev/vlz/vlza.sgm";
//       l_argv[1]="f:/kp/source/tev/lvz/lvz.sgm";
//       l_argv[1]="f:/kp/source/tev/vlz04/vlzh.sgm";
//       l_argv[1]="g:/kp/source/tev/lvz/lvzc.sgm";
//       l_argv[1]="g:/kp/source/tev/elz/bac.sgm";
//       l_argv[1]="g:/kp/source/tev/vlz04/vlzf.sgm";
//       l_argv[1]="d:/Local/tev/elz05e/aaa/aaa.sgm";
//       l_argv[1]="d:/Local/tev/rlz06/rlza/rlza.sgm";
//       l_argv[1]="f:/kp/source/tev/rlz/kpn1.sgm";
//       l_argv[1]="d:/Local/tev/rlz06/rlza_01/rlza_01.sgm";
//       l_argv[1]="d:/Local/tev/pavz/visata/visata.sgm";
//       l_argv[1]="f:/kp/source/tev/lvz/kpn1.sgm";
//       l_argv[1]="f:/kp/source/tev/vlz/kpn1.sgm";
         l_argv[1]="f:/kp/source/tev/ldz/kpn1.sgm";

//       l_argv[2]="/home/kp/source/tev/ohe/ohe.xml";
//       l_argv[2]="f:/wrk/kp/source/tev/lvz/lvza.xml";
//       l_argv[2]="D:/kp/source/tev/lvz/lvz_comp.xml";
//       l_argv[2]="f:/wrk/kp/source/tev/lvz/inv_exp/lvzj.xml";
//       l_argv[2]="f:/kp/source/tev/lvz/lvzb.xml";
//       l_argv[2]="f:/kp/source/tev/vlz/vlza.xml";
//       l_argv[2]="f:/kp/source/tev/lvz/lvz.xml";
//       l_argv[2]="f:/kp/source/tev/vlz04/vlzh.xml";
//       l_argv[2]="g:/kp/source/tev/lvz/lvzc.xml";
//       l_argv[2]="g:/kp/source/tev/elz/bac.xml";
//       l_argv[2]="g:/kp/source/tev/vlz04/vlzf.xml";
//       l_argv[2]="d:/Local/tev/elz05e/aaa/aaa.xml";
//       l_argv[2]="d:/Local/tev/rlz06/rlza/rlza.xml";
//       l_argv[2]="f:/kp/source/tev/rlz/kpn1.xml";
//       l_argv[2]="d:/Local/tev/rlz06/rlza_01/rlza_01.xml";
//       l_argv[2]="d:/Local/tev/pavz/visata/visata.xml";
//       l_argv[2]="f:/kp/source/tev/lvz/kpn1.xml";
//       l_argv[2]="f:/kp/source/tev/vlz/kpn1.xml";
         l_argv[2]="f:/kp/source/tev/ldz/kpn1.xml";
      }
#endif
   }
   
   if(SUCCEEDED(retc))
   {
      if(l_argc==3)
      {

// vokiskiems projektams indeksuose praleisti '/' (Abessini/en) (MCM '/' - variantu atskyrejas, 
//    angliskuose - sutrumpinimai ("AC/DC"))
         if(SUCCEEDED(retc))
            retc=TvFnameSplit(disk, path, fname, ftype, (const unsigned char *)l_argv[1]);
         if(SUCCEEDED(retc)) if((tolower(fname[0]) == 'v') || (tolower(fname[1]) == 'v'))
         {            
            lpszIxSpcEolPtr = lpszIxSpcEol+1;
            lpszIxSpCharsPtr = lpszIxSpChars+1;
         }
         
         if(SUCCEEDED(retc))
         {            
            pXmlG2T = new XmlG2T((unsigned char *)l_argv[1], (unsigned char *)l_argv[2]);
            if(pXmlG2T!=NULL)
            {
               retc=pXmlG2T->GetOpenResult();

               if(SUCCEEDED(retc)) retc=pXmlG2T->Process(False);

               retc0=pXmlG2T->CloseFiles(SUCCEEDED(retc));
               if(SUCCEEDED(retc)) retc=retc0;

               KP_DELETE(pXmlG2T);

//             if(SUCCEEDED(retc)) retc=XmlIcv((unsigned char *)l_argv[2]);

            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, TRUE, __FILE__, __LINE__, 0L);
         }
      }
      else
      {
         printf("Bad number of parameters:\n");
         printf("               c:>xmlg2t.exe infile.sgm outfile.xml\n");
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
