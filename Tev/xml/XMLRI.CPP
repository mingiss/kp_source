// ==================================================
// xmlri.cpp
// XML file references creator
// general XML to XML
// part of XmlOI2_tag


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

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
#include "xmlis.h"
#include "xmli.h"
#include "xmloi2.h"
#include "tvxmlrm.h"
#include "tvxmle.h"
#include "tvxmls.h"


// ======================================================
// --------------------------------------------------
HRESULT XmlOI2_tag::StartReferenceProcessing(bool bRefFl)
{
   iRefBufIdx=0;
   iLWordBufIdx=0;
   bTextToBuffer=TRUE;
   bCollectReference=bRefFl;

return(S_OK);
}


// --------------------------------------------------
HRESULT XmlOI2_tag::StopReferenceProcessing(void)
{
HRESULT retc=S_OK;

   retc=FlushRefVal();

   iRefBufIdx=0;
   iLWordBufIdx=0;
   bTextToBuffer=FALSE;

   bCollectReference=FALSE;

return(retc);
}


// ------------------------------------------------------
HRESULT XmlOI2_tag::PutRefChar(int uiChOut)
{
HRESULT retc=S_OK;

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, lLastIdx);

   if(SUCCEEDED(retc))
   {
      if(bCollectReference)
      {
         if(iRefBufIdx<TV_XL_MAX_IX_LEN) auiRefBuf[iRefBufIdx++]=uiChOut;
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, NULL, TRUE, __FILE__, __LINE__, lLastIdx);
      }
      else
      {
         if(SUCCEEDED(retc)) retc=FlushRefVal();
         if(SUCCEEDED(retc))
            retc=lpOutFileObj->PutCharProc(uiChOut, NULL);
      }
   }

return(retc);
}


// ------------------------------------------------------
HRESULT XmlOI2_tag::SeparateLastRefWord(bool bWrdFlg)
{
return(S_OK);
}


// ------------------------------------------------------
HRESULT XmlOI2_tag::FlushRefVal(void)
{
HRESULT retc=S_OK;
int ii;
bool put_fl;
int out_ch;
long entr_idx;
int str_buf_i[TV_XL_MAX_IX_LEN+1];
int str_buf_ii[TV_XL_MAX_IX_LEN+1];
unsigned char str_buf[TV_XL_MAX_IX_LEN+1];
XmlTagPars_tag *tag_par=NULL;
unsigned char par_val[KP_MAX_FILE_LIN_LEN+1];

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, NULL, TRUE, __FILE__, __LINE__, lLastIdx);

// search keyword
   if(iRefBufIdx>TV_XR_REF_THRESHOLD)
   {
      if(SUCCEEDED(retc)) retc=ExpandAbbr(str_buf_i, (const Chars16 *)auiRefBuf, &chr_cnt, iStrBufSize, ucLang);
//    if(SUCCEEDED(retc)) retc=DelComments(str_buf_i, &chr_cnt);

      if(SUCCEEDED(retc))
      {
         retc=TvXmlEs.CutEndingsDelCjts(str_buf_ii, str_buf_i, acIndexLanguages[XL_IX_HwIndex], True);
         if(SUCCEEDED(retc))
         {
            if(iRefBufIdx<TV_XL_MAX_IX_LEN)
            {
               retc=Chars16ToStrNoCtrl(str_buf, str_buf_ii, TvIntStrLen(str_buf_ii)/* iRefBufIdx */, TV_XL_MAX_IX_LEN);
               if(SUCCEEDED(retc)) retc=CutInitSpcs(str_buf);
               if(SUCCEEDED(retc)) retc=CutTrailSpcs(str_buf);
            }
            else retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, NULL, TRUE, __FILE__, __LINE__, lLastIdx);

            if(SUCCEEDED(retc))
               retc=lpInFileObj->SearchEntry(&entr_idx, str_buf, XL_IX_HwIndex, FALSE);
         }
         if(retc==KP_E_KWD_NOT_FOUND)
         {      
            retc=TvXmlEs.CutEndingsDelCjts(str_buf_ii, str_buf_i, acIndexLanguages[XL_IX_TwIndex], True);
            if(SUCCEEDED(retc))
            {
               if(iRefBufIdx<TV_XL_MAX_IX_LEN)
               {
                  retc=Chars16ToStrNoCtrl(str_buf, str_buf_ii, TvIstrLen(str_buf_ii) /* iRefBufIdx */, TV_XL_MAX_IX_LEN);
                  if(SUCCEEDED(retc)) retc=CutInitSpcs(str_buf);
                  if(SUCCEEDED(retc)) retc=CutTrailSpcs(str_buf);
               }
               else retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, NULL, TRUE, __FILE__, __LINE__, lLastIdx);

               if(SUCCEEDED(retc))
                  retc=lpInFileObj->SearchEntry(&entr_idx, str_buf, XL_IX_TwIndex, FALSE);
            }
         }
      }
      

      if(!SUCCEEDED(retc))
      {
         if(retc==KP_E_KWD_NOT_FOUND)
         {
            retc=S_OK;
            if(iRefBufIdx>=TV_XL_MAX_IX_LEN)
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, NULL, TRUE, __FILE__, __LINE__, lLastIdx);
            if(SUCCEEDED(retc))
               retc=KpErrorProc.StrDecode(str_buf, auiRefBuf, iRefBufIdx);
            if(SUCCEEDED(retc))
               retc=SpcEolToSpc(str_buf);

            if(SUCCEEDED(retc))
            {
               /*retc=*/KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, str_buf, FALSE, __FILE__, __LINE__, lLastIdx);

//             KpErrorProc.Message((const unsigned char *)"Keyword not found: ");
//             KpErrorProc.Message(str_buf);
//             KpErrorProc.Message((const unsigned char *)"\n");
            }
         }
         else
            retc=KpErrorProc.OutputErrorMessage(retc, NULL, TRUE, __FILE__, __LINE__, lLastIdx);
      }
   }

// reference field start tag
   if((iRefBufIdx>TV_XR_REF_THRESHOLD) && SUCCEEDED(retc))
   {
      sprintf((char *)par_val, "%c%ld", TV_HTM_HrefDelim, entr_idx);
      KP_NEW(tag_par, XmlTagPars_tag((const unsigned char *)"href", par_val));

      retc = lpOutFileObj->PutCharProc(XC_Reference, tag_par);

      KP_DELETE(tag_par);
   }

// field value
   for(ii=0; (ii<iRefBufIdx) && SUCCEEDED(retc); ii++)
   {
      out_ch=auiRefBuf[ii];
      put_fl=TRUE;

      if(TvStrChr(lpszSpcEol, out_ch)!=NULL) out_ch=' ';

      if(out_ch==' ')
      {
         if(ii<iRefBufIdx-1)
            if(
               (TvStrChr(lpszTvXmlNoSpcChars, auiRefBuf[ii+1])!=NULL) ||
               (auiRefBuf[ii+1]==C_NBSP)
              )
               put_fl=FALSE;

         if(ii==0) put_fl=FALSE;

         if(ii>0)
            if(
               (TvStrChr(lpszTvXmlNoSpcChars, auiRefBuf[ii-1])!=NULL) ||
               (auiRefBuf[ii-1]==C_NBSP)
              )
               put_fl=FALSE;
      }

      if(put_fl)
         retc=lpOutFileObj->PutCharProc(auiRefBuf[ii], NULL);
   }

// reference field end tag
   if((iRefBufIdx>TV_XR_REF_THRESHOLD) && SUCCEEDED(retc))
      retc=lpOutFileObj->PutCharProc(XC_Reference_e, NULL);

   iRefBufIdx=0;

return(retc);
}


// ------------------------------------------------------
HRESULT XmlOI2_tag::FlushLastRefWord(void)
{
return(S_OK);
}
