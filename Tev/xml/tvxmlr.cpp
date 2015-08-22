// ==================================================
// tvxmlr.cpp
// XML file references creator
// general XML to XML
// part of XmlO2


// ================================================== definitions
#include "envir.h"

#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlo2.h"
#include "xmlis.h"
#include "tvxmlrm.h"
#include "tvxmle.h"
#include "tvxmls.h"
// #include "mcmt.h"


// ======================================================
// --------------------------------------------------
HRESULT XmlO2::StartReferenceProcessing(bool bRefFl)
{
   iRefBufIdx=0;
   iLWordBufIdx=0;
   bTextToBuffer=TRUE;
   bCollectReference=bRefFl;

return(S_OK);
}


// --------------------------------------------------
HRESULT XmlO2::StopReferenceProcessing(XmlTagPars *pTagPar)
{
HRESULT retc=S_OK;

   retc=FlushRefVal(pTagPar);

   iRefBufIdx=0;
   iLWordBufIdx=0;
   bTextToBuffer=FALSE;

   bCollectReference=FALSE;

return(retc);
}


// ------------------------------------------------------
HRESULT XmlO2::PutRefChar(KpChar uiChOut, XmlTagPars *pTagPar)
{
HRESULT retc=S_OK;

   if(m_lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lLastIdx);

   if(SUCCEEDED(retc))
   {
      if(bCollectReference)
      {
         if(pTagPar!=NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

         if(iRefBufIdx<TV_XL_MAX_IX_LEN) auiRefBuf[iRefBufIdx++]=uiChOut;
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, lLastIdx);
      }
      else
      {
         if(SUCCEEDED(retc)) retc=FlushRefVal(NULL);
         if(SUCCEEDED(retc))
            retc=m_lpOutFileObj->PutCharProc(uiChOut, pTagPar, XL_IX_DataFile);
      }
   }

return(retc);
}


// ------------------------------------------------------
HRESULT XmlO2::SeparateLastRefWord(bool /* bWrdFlg */)
{
return(S_OK);
}


// ------------------------------------------------------
HRESULT XmlO2::FlushRefVal(XmlTagPars *pTagPar)
{
HRESULT retc=S_OK;
int ii;
bool put_fl;
KpChar out_ch;
long entr_idx;
long offset;

unsigned char *str_buf = null;
   KP_NEWA(str_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1); // [TV_XL_MAX_IX_LEN+1];

KpChar str_buf_i[TV_XL_MAX_IX_LEN+1];
// unsigned char str_tmp[TV_XL_MAX_IX_LEN+1];
XmlTagPars *tag_par=NULL;
unsigned char par_val[KP_MAX_FNAME_LEN+MAX_LONG_DIGITS+1+1];
const unsigned char *pntn;
bool ref_par;
bool proc_ref;
bool search_fl;
int par_num;
int found_file_ix=(-1);

   if((m_lpInFileObjs[0]==NULL) || (m_iNumOfInFiles<1) || (m_lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lLastIdx);
   if((m_iNumOfInFiles>MAX_NUM_OF_LIST_ENTRIES) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   for(ii=0; (ii<m_iNumOfInFiles) && SUCCEEDED(retc); ii++)
      if((m_lpInFileObjs[ii]==NULL) || (m_lpszInFileNames[ii]==NULL))
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, lLastIdx);

   auiRefBuf[TV_XL_MAX_IX_LEN] = C_Nul;
   if(iRefBufIdx>=TV_XL_MAX_IX_LEN)
      retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, lLastIdx);
   if(SUCCEEDED(retc)) auiRefBuf[iRefBufIdx] = C_Nul;

// gal yra parametruose?
   ref_par=False;
   proc_ref=False;
   search_fl=True;
   ii=0;

   if(pTagPar && SUCCEEDED(retc))
   {
      retc=pTagPar->SeekTextPar("href", str_buf, &par_num);
      if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
      else
      {
         ref_par=True;
         proc_ref=True;

         if(str_buf[0]==TV_XM_HrefDelim)
         {
            sscanf((const char *)str_buf+1, "%d", &entr_idx);
            search_fl=False;
            ii=0;
         }
         else
         {
            if(TvIsNumber(str_buf))
            {
               sscanf((const char *)str_buf, "%d", &entr_idx);
               search_fl=False;
               ii=0;
            }
            else
            {
               retc=KptStrEncode(str_buf_i, str_buf, 71);
               if(retc==KP_E_UNKN_CHR) retc=S_OK;
               str_buf_i[ii]=C_Nul;
               search_fl=True;
            }
         }
      }
   }

// ne - auiRefBuf i str_buf_i
   if((!ref_par) && SUCCEEDED(retc))
   {
      proc_ref=(iRefBufIdx>TV_XR_REF_THRESHOLD);
      if(proc_ref)
      {
         if((iRefBufIdx>=TV_XL_MAX_IX_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, lLastIdx);

         if(SUCCEEDED(retc)) TvKpStrCpy(str_buf_i, auiRefBuf);
       }
   }

// search keyword
   if(proc_ref && search_fl && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc))
      {
         retc=KP_E_KWD_NOT_FOUND;
         found_file_ix=(-1);
         for(ii=m_iNumOfInFiles-1; (ii>=0) && (retc==KP_E_KWD_NOT_FOUND); ii--)
         {
            found_file_ix=ii;

            if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;

#if FALSE // #ifdef Debug //
{
int kk;
static int VertPhilKreiv[]={
// 'V', 'E', 'R', 'T', C_Nul,
'V', 'E', 'R', 'T', 'I', 'K', 'A', 'L', 'I', 'O', 'J', 'I', ' ',
'P', 'H', 'I', 'L', 'L', 'I', 'P', 'S', 'o', ' ',
'K', 'R', 'E', 'I', 'V', C_E_Adot, C_Nul
};
if(TvIntStrCmp((const int *)str_buf_i, VertPhilKreiv)==0)
// if((TvIntStrStr(str_buf_i, VertPhilKreiv)!=NULL) && (lLastIdx>=36))
// if(lLastIdx>=36)
kk=ii;
}
#endif

#if FALSE // #ifdef Debug //
static int HipTikr[]={
'H', 'I', 'P', 'O', 'T', 'E', 'Z', 'I', C_U_Ogon, ' ',
'T', 'I', 'K', 'R', 'I', 'N', 'I', 'M', 'E', C_Nul};
TvIntStrCpy((int *)str_buf_i, HipTikr);
iRefBufIdx=TvIntStrLen(HipTikr);
#endif
            str_buf_i[iRefBufIdx]=C_Nul;

            if(SUCCEEDED(retc))
               retc=KpCharToIndexEntry(str_buf, str_buf_i, iRefBufIdx, TV_XL_MAX_IX_LEN, caIxLangs[XL_IX_HwIndex], iaIxEncodings[XL_IX_HwIndex]);

            if(SUCCEEDED(retc))
               retc=m_lpInFileObjs[ii]->SearchEntry(&entr_idx, &offset, str_buf, XL_IX_HwIndex, FALSE);
            if(retc==KP_E_KWD_NOT_FOUND)
            {
               retc=S_OK;

               if(SUCCEEDED(retc))
                  retc=KpCharToIndexEntry(str_buf, str_buf_i, iRefBufIdx, TV_XL_MAX_IX_LEN, caIxLangs[XL_IX_TwIndex], iaIxEncodings[XL_IX_HwIndex]);
               if(SUCCEEDED(retc))
                  retc=m_lpInFileObjs[ii]->SearchEntry(&entr_idx, &offset, str_buf, XL_IX_TwIndex, FALSE);
            }
         }
      }
      if(!SUCCEEDED(retc))
      {
         if(retc==KP_E_KWD_NOT_FOUND)
         {
            retc=S_OK;
            entr_idx=0;
            if(SUCCEEDED(retc)) retc=KpErrorProc.StrDecode(str_buf, auiRefBuf);
            if(SUCCEEDED(retc)) retc=SpcEolToSpc(str_buf);

            if(SUCCEEDED(retc))
            {
               /*retc=*/KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, str_buf, FALSE, __FILE__, __LINE__, lLastIdx);

//             KpErrorProc.Message((const unsigned char *)"Keyword not found: ");
//             KpErrorProc.Message(str_buf);
//             KpErrorProc.Message((const unsigned char *)"\n");
            }
         }
         else
            retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, lLastIdx);
      }
   }

// reference field start tag
   if(proc_ref && SUCCEEDED(retc))
   {
      if(found_file_ix<0) found_file_ix=0;
      if(SUCCEEDED(retc))
      {
         pntn=m_lpszInFileNames[found_file_ix]+strlen(m_lpszInFileNames[found_file_ix]);
         if((found_file_ix>0) && (entr_idx>0)) while(pntn>m_lpszInFileNames[found_file_ix])
         {
            if((*(pntn-1)!='\\') && (*(pntn-1)!='/')) pntn--;
            else break;
         }
         sprintf((char *)par_val, "%s%c%ld", pntn, TV_XM_HrefDelim, entr_idx);
         KP_NEW(tag_par, XmlTagPars((const unsigned char *)"href", par_val, NULL));
      }
      if(SUCCEEDED(retc))
         retc=tag_par->AddTextPar((const unsigned char *)"class", (const unsigned char *)"entry");
      if(SUCCEEDED(retc))
         retc=m_lpOutFileObj->PutCharProc((KpChar)XC_Reference, tag_par, XL_IX_DataFile);

      KP_DELETE(tag_par);
   }

// field value
   for(ii=0; (ii<iRefBufIdx) && SUCCEEDED(retc); ii++)
   {
      out_ch=auiRefBuf[ii];
      put_fl=TRUE;

      if(TvStrChr(lpszSpcEol, out_ch)!=NULL) out_ch=C_Spc; // ' '

      if(out_ch==C_Spc) // ' '
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
         retc=m_lpOutFileObj->PutCharProc(auiRefBuf[ii], NULL, XL_IX_DataFile);
   }

// reference field end tag
   if(proc_ref && SUCCEEDED(retc))
      retc=m_lpOutFileObj->PutCharProc((KpChar)XC_Reference_e, NULL, XL_IX_DataFile);

   iRefBufIdx=0;

   KP_DELETEA(str_buf);

return(retc);
}


// ------------------------------------------------------
HRESULT XmlO2::FlushLastRefWord(void)
{
return(S_OK);
}
