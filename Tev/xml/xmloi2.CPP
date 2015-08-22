// ==================================================
// xmloi2.cpp, former xmlioi2.cpp
// base class for XML applications with two (input and output) files and index support


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <richedit.h>
#include <Richole.h>
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpctype.h"
#include "kpstring.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmlu.h"
#include "xmloi2.h"
#include "tvxmle.h"


// ================================================== public members of XmlO_tag
XmlOI2::XmlOI2(bool bProcessSubkeys)
{
HRESULT retc = S_OK;
    
   m_lhOpenResult=S_OK;

   m_lpszInFileName[0]=Nul;
   m_lpszOutFileName[0]=Nul;

   m_lpInFileObj=NULL;
   m_lpOutFileObj=NULL;

   m_pTagStack=NULL;

   m_lLastIdx=0L;

   m_lMaxSeIx=0L;

   m_iRefBufIdx=0;
   m_iLWordBufIdx=0;
   m_bTextToBuffer=FALSE;
   m_bCollectReference=FALSE;

// m_lpszHwSav[0]=Nul;

   m_lEntryId=0L;
   KpErrorProc.SetLPar(m_lEntryId);

   m_acIndexLanguages=NULL;
   m_aiIndexEncodings=NULL;

   KP_NEW(m_pTagStack, TvXmlTagStack(NULL, C_Nul, NULL, 0));

   m_bProcessSubkeys=bProcessSubkeys;
}


// --------------------------------------------------
XmlOI2::~XmlOI2(void)
{
TvXmlTagStack *prev_stack_ptr;
KpChar cur_tag;

   CloseFiles(FALSE);

   if(m_pTagStack!=NULL)
   {
      m_pTagStack->GetPrevTagPtr(&prev_stack_ptr);
      m_pTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr!=NULL) || (cur_tag!=C_Nul))
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, FALSE, __FILE__, __LINE__, 0L);

      KP_DELETE(m_pTagStack);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
}



// --------------------------------------------------
HRESULT XmlOI2::OpenFile
(
const unsigned char *lpszInFname, const unsigned char *lpszInMode,
const unsigned char *lpszOutFname, const unsigned char *lpszOutMode,
const unsigned char *acIndexLangs, const EC_Types *aiIndexEncs
)
{
HRESULT retc=S_OK;

   m_acIndexLanguages=acIndexLangs;
   m_aiIndexEncodings=aiIndexEncs;
   if(
      (
         (m_acIndexLanguages==NULL) ||
         (m_aiIndexEncodings==NULL) ||
         (lpszInFname==NULL) || (lpszOutFname==NULL)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszInFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszInFileName, lpszInFname);
      else retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpInFileObj, XmlI(m_lpszInFileName, lpszInMode, CreateNewUniFile, plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, m_acIndexLanguages, m_aiIndexEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlDictNulCodeTables, True, False, m_bProcessSubkeys));

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(m_lpszOutFileName, lpszOutFname);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(m_lpOutFileObj, XmlI(m_lpszOutFileName, lpszOutMode, CreateNewUniFile, plpszaXmlSpecCharTagsMain,
                                       alpszIndexNames, aiIndexWidths, m_acIndexLanguages, m_aiIndexEncodings,
                                       (KpChar)XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlDictNulCodeTables, True, False, m_bProcessSubkeys));

return(retc);
}


// --------------------------------------------------
HRESULT XmlOI2::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(m_lpOutFileObj!=NULL)
   {
      retc = m_lpOutFileObj->CloseFile(bCheckFileExist);
      KP_DELETE(m_lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(m_lpInFileObj!=NULL)
   {
      KP_DELETE(m_lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlOI2::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlOI2::PutTag(KpChar iTag, XmlTagPars *pTagParsObj)
{
HRESULT retc=S_OK;
int ii;
int gr_cnt;
int ch_pos;

   if((m_lpOutFileObj==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);
   if(SUCCEEDED(retc)) if(m_lpOutFileObj->FilePtr == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);
   if(SUCCEEDED(retc)) if(m_lpOutFileObj->FilePtr->m_fFiles[XL_IX_DataFile] == NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->GetCharPos(&ch_pos);

   if((TvKpStrChr(uiazXmlGrTags, iTag)!=NULL) && (ch_pos>0) && SUCCEEDED(retc))
      retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL); // '\n'

   if(SUCCEEDED(retc)) retc=m_lpOutFileObj->GetCharPos(&ch_pos);

   if((ch_pos==0) && SUCCEEDED(retc))
   {
      retc=GetGroupCount(m_pTagStack, &gr_cnt, uiazXmlGrTags);

// put indent charz
// !!! use SetIndent()
      for(ii=0; (ii<gr_cnt-1) && SUCCEEDED(retc); ii++)
      {
//       retc=m_lpOutFileObj->PutStr((const unsigned char *)"   ");
         retc=m_lpOutFileObj->FilePtr->m_fFiles[XL_IX_DataFile]->PutStr((const unsigned char *)"   ");
      }
   }

   if((iTag!=XC_Symb) && (iTag!=XC_Symb_e) && SUCCEEDED(retc))
      retc=m_lpOutFileObj->PutCharProc(iTag, pTagParsObj);

return(retc);
}


// --------------------------------------------------
HRESULT XmlOI2::PutOpenTag(KpChar iTag, XmlTagPars *pTagParsObj)
{
HRESULT retc=S_OK;
KpChar cur_tag;
KpChar new_tag;
bool emb_fl;
unsigned char out_str[TV_XL_HW_IX_LEN+KP_MAX_FILE_LIN_WDT+1];
int ii;

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(SUCCEEDED(retc))
   {
      if((iTag>=XC_FirstDictTag) && (iTag<XC_LastDictTag))
      {
         if((TvKpStrChr(uiazXmlGrTags, iTag)!=NULL) || (iTag == XC_Paragraph))
         {
            retc = m_lpOutFileObj->GetCharPos(&ii);
            if((ii > 0) && SUCCEEDED(retc)) 
               retc=m_lpOutFileObj->PutCharProc(C_Lf, NULL); // '\n'
         }
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, iTag);
   }

   if(SUCCEEDED(retc)) retc=PutTag(iTag, pTagParsObj);
   
   if(SUCCEEDED(retc)) retc=m_pTagStack->GetCurTag(&cur_tag);
   if((cur_tag==XC_Parenth) && SUCCEEDED(retc)) retc=GetStackTag(m_pTagStack, 1, &cur_tag);
   if(SUCCEEDED(retc)) retc=XmltTestEmbedded(iTag, cur_tag, &emb_fl);
   if(SUCCEEDED(retc))
   {
      new_tag=iTag;
      if(new_tag==XC_StEntry) new_tag=(KpChar)XC_HeadWordGroup;
      sprintf((char *)out_str, "Lizdas %ld, hw:%s : %s viduje %s\n",
         m_lEntryId, KpErrorProc.szaMsgText /* m_lpszHwSav */,
         (new_tag!=C_Nul)?pplpszaMsgTags[new_tag-XC_FirstDictTag]:(const unsigned char *)"Null",
         (cur_tag!=C_Nul)?pplpszaMsgTags[cur_tag-XC_FirstDictTag]:(const unsigned char *)"Null");

//    if(
//       ((iTag==XC_Gloss) && (cur_tag==XC_HeadWordGroup)) ||
//       False
//      )
//    {
//       printf((const char *)out_str);
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, out_str, FALSE, __FILE__, __LINE__, m_lEntryId);
//    }
//    else
      {
         if(!emb_fl)
         {
            printf((const char *)out_str);
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, out_str, TRUE, __FILE__, __LINE__, m_lEntryId);
         }

      } // else // if(((iTag==XC_Gloss) && (cur_tag==XC_HeadWordGroup)) || ...

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc)) retc=PushTag(&m_pTagStack, iTag, NULL, 0);

return(retc);
}


// --------------------------------------------------
HRESULT XmlOI2::PutClosingTag(KpChar iTag, XmlTagPars *pTagParsObj)
{
HRESULT retc=S_OK;
KpChar tmp_tag;
KpChar out_tag;

   if(m_pTagStack==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   out_tag=(KpChar)(iTag|1);
   if(SUCCEEDED(retc)) retc=PopTag(&m_pTagStack, &tmp_tag);
   if((tmp_tag==XC_Variant) && (out_tag==XC_HeadWord_e) && SUCCEEDED(retc)) out_tag=(KpChar)XC_Variant_e;

   if((tmp_tag!=(out_tag&(~1))) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, m_lEntryId);

   if(SUCCEEDED(retc)) retc=PutTag(out_tag, pTagParsObj);

return(retc);
}


#if FALSE
// --------------------------------------------------
HRESULT XmlOI2::TransferField
(
const int uiStartTag,
const int uiEndTag,
const XL_Indexes uiIxFileIdx,
const long lMainKeyValue,
bool bTstInverted,
bool bTstCombined,
XmlTagPars *pTagPar
)
{
HRESULT retc=S_OK;
int ch2, ch;
long ch_num;
int ch_pos;
bool text_available=FALSE;
XmlIs_IndexRecord_tag *ind_rec;
int par_lev;
XmlTagPars *tag_par=NULL;
XmlTagPars *tag_par1=NULL;
long entry_id=0L;
int par_num;

   if((m_lpInFileObj==NULL) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, m_lLastIdx);

// put se index entry
   if((uiIxFileIdx==XL_IX_SeIndex) && SUCCEEDED(retc))
   {
      if(pTagPar==NULL)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, m_lLastIdx);
      if(SUCCEEDED(retc))
      {
         retc=pTagPar->SeekNumPar("id", &entry_id, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, TRUE, __FILE__, __LINE__, m_lLastIdx);
      }
      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutNumVal(entry_id, uiIxFileIdx);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->GetCharNum(&ch_num, XL_IX_DataFile);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutNumVal(ch_num, uiIxFileIdx);

      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc('\n', NULL, uiIxFileIdx);
   }

// text index object
   KP_NEW(ind_rec, XmlIs_IndexRecord_tag(m_lpOutFileObj, uiIxFileIdx, lMainKeyValue,
                           bTstInverted, bTstCombined, bTstCombined, caIxLangs[uiIxFileIdx]));

// reference object
   if(SUCCEEDED(retc))
      retc=StartReferenceProcessing(uiStartTag==XC_Reference);

   if(SUCCEEDED(retc))
   {
      do
      {
// input character
         retc=m_lpInFileObj->GetCharProc(&ch2, &tag_par, XL_IX_DataFile, TRUE);

// start tag output
         if((!text_available) && (uiStartTag!=0) && (uiStartTag!=XC_Reference) && SUCCEEDED(retc))
         {
            retc=m_lpOutFileObj->PutCharProc(uiStartTag, pTagPar, XL_IX_DataFile);
            text_available=TRUE;
         }

// character analyze
         if(SUCCEEDED(retc))
         {
            if(ch2 != uiEndTag)
            {
               switch(ch2)
               {
               case XC_Dict:
               case XC_Dict_e:
               case XC_NrtEntry:
               case XC_NrtEntry_e:
               case XC_StEntry:
               case XC_StEntry_e:
               case XC_HeadWord_e:
               case XC_Label_e:
               case XC_TrWord_e:
               case XC_UsNote_e:
//!!!          case XC_Reference_e:
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, m_lLastIdx);
                  break;

               case XC_HeadWordGroup:
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"\n   ", XL_IX_DataFile);
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  break;

               case XC_HeadWordGroup_e:
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"\n", XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  break;

               case XC_TranslGroup:
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"\n      ", XL_IX_DataFile);
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  break;

               case XC_TranslGroup_e:
                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObj->GetCharProc(&ch, &tag_par1, XL_IX_DataFile, TRUE);
                  if((TvStrChr(lpszSpaces, ch)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObj->UnGetCharProc(ch, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"\n   ", XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc(ch2, tag_par, XL_IX_DataFile);
                  break;

               case XC_HeadWord:
                  retc=TransferField(XC_HeadWord, XC_HeadWord_e, XL_IX_HwIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    TRUE, TRUE, tag_par);
                  break;

               case XC_Label:
                  retc=TransferField(XC_Label, XC_Label_e, XL_IX_LaIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, FALSE, tag_par);
                  break;

               case XC_TrWord:
                  retc=TransferField(XC_TrWord, XC_TrWord_e, XL_IX_TwIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, TRUE, tag_par);
                  break;

               case XC_UsNote:
                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"\n      ", XL_IX_DataFile);
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutStr((const unsigned char *)"   ", XL_IX_DataFile);

                  if(SUCCEEDED(retc))
                     retc=TransferField(XC_UsNote, XC_UsNote_e, XL_IX_DataFile /* XL_IX_NoIndex */,
                                       0L, FALSE, FALSE, tag_par);

                  if(SUCCEEDED(retc))
                     retc=m_lpInFileObj->GetCharProc(&ch2, &tag_par1, XL_IX_DataFile, TRUE);
                  if((TvStrChr(lpszSpaces, ch2)==NULL) && SUCCEEDED(retc))
                     retc=m_lpInFileObj->UnGetCharProc(ch2, tag_par1, XL_IX_DataFile);
                  KP_DELETE(tag_par1);

                  if(SUCCEEDED(retc)) retc=m_lpOutFileObj->SetIndent((const unsigned char *)"\n   ", XL_IX_DataFile);
                  if(SUCCEEDED(retc))
                     retc=m_lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);
                  break;

               case XC_Reference:
                  retc=TransferField(XC_Reference, XC_Reference_e, XL_IX_DataFile /* XL_IX_NoIndex */,
                                    0L, FALSE, FALSE, tag_par);
                  break;

               case XC_StEntryText:
                  retc=TransferField(XC_StEntryText, XC_StEntryText_e, XL_IX_StIndex,
                                    (uiIxFileIdx==XL_IX_SeIndex)?entry_id:lMainKeyValue,
                                    FALSE, FALSE, tag_par);
                  break;

               default:
// ordinary chars

// to data file
                  retc=PutRefChar(ch2);

// split index list to different records
                  if(SUCCEEDED(retc)) retc=ind_rec->GetParLev(&par_lev);
                  if((ch2==';') && (par_lev<1) && SUCCEEDED(retc))
                  {
                     retc=ind_rec->CompleteIndexRecord();
                     KP_DELETE(ind_rec);

                     KP_NEW(ind_rec, XmlIs_IndexRecord_tag(m_lpOutFileObj,
                                       uiIxFileIdx, lMainKeyValue,
                                       bTstInverted, bTstCombined, bTstCombined,
                                       caIxLangs[uiIxFileIdx]));
                  }

// to index file
//!!!             if(TvIsAlpha(uiChOut) || uiChOut==C_Spc || uiChOut=='\'')
                  if(ch2!=';')
                     if(SUCCEEDED(retc)) retc=ind_rec->PutChar(ch2);

                  break;

               } // switch(ch2)

            } // if(ch2 != cFieldLimiter)
         }

         KP_DELETE(tag_par);

      } while((ch2 != uiEndTag) && SUCCEEDED(retc));

   } // if(SUCCEEDED(retc))

// complete index entry
   if(SUCCEEDED(retc) /* && !bEofFlg */)
   {
      retc=ind_rec->CompleteIndexRecord();
      KP_DELETE(ind_rec);
   }

// complete reference
   if(SUCCEEDED(retc) /* && !bEofFlg */)
      retc=StopReferenceProcessing(); // FlushRefVal();

// end tag
   if(text_available && (uiEndTag!=0) && (uiStartTag!=XC_Reference) && SUCCEEDED(retc))
      retc=m_lpOutFileObj->PutCharProc(uiEndTag, NULL, XL_IX_DataFile);

// two eol's between main entries
   if(
         ((uiStartTag==XC_StEntry) || (uiStartTag==XC_NrtEntry)) &&
         SUCCEEDED(retc)
     )
   {
      retc=m_lpOutFileObj->GetCharPos(&ch_pos, XL_IX_DataFile);
      if((ch_pos!=0) && SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);
      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc('\n', NULL, XL_IX_DataFile);
      KP_DELETE(tag_par1);
   }

return(retc);
}
#endif
