// ==================================================
// tvxmlrm.cpp
// McMillan dictionary RTF to XML converter
// XML file references creator


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
#include "kpctype.h"
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
#include "xmlis.h"
#include "tvxmlrm.h"


// --------------------------------------------------
unsigned char lpszTvRefSpaces[] =      " \t\n\r/-";         // also C_NBSP, C_EnDash, C_break  // " \t\n\r/-()";
unsigned char lpszTvXmlNoSpcChars[] =  " \t\n\r/";          // also C_NBSP, C_break
unsigned char lpszTvRefCtrls[] =       "/\'\"-()";          // also C_LAapost, C_Rapost, ...  // " \t\n\r/\'-()"; // " \t\n\r/\'-"; // also C_NBSP, C_EnDash
unsigned char lpszTvRefCtrlsAndPar[] = "/\'\"-()";          // also C_LAapost, C_Rapost, ...  // " \t\n\r/\'-()"; // " \t\n\r/\'-"; // " \t\n\r/\'-()"; // also C_NBSP, C_EnDash
unsigned char lpszTvRefDelims[] =      ".,:;!?<>+={}";      // ".,:;!?<>+=[]{}"; // ".,:;!?<>+=[]{}()";  // ".,:;!?<>+=";
KpChar iazTvCommentDelims[] = {/* (KpChar)MCM_COMMENT_START, (KpChar)MCM_COMMENT_END, */ (KpChar)XC_TechNote, (KpChar)XC_TechNote_e, C_Nul}; // '[', ']', ...


// ======================================================
// --------------------------------------------------
TvXmlR_DataRecord_tag::TvXmlR_DataRecord_tag
(
XmlO1 *lpOutFileOb,
bool bRefFl
)
{
   lpOutFilObj=lpOutFileOb;

   iRefBufIdx=0;
   iLWordBufIdx=0;
   bTextToBuffer=TRUE;
   m_iLastWordLength=0;

   bCollectReference=bRefFl;

   bInsideComent=False;

   iUnGetCnt=0;
}


// --------------------------------------------------
TvXmlR_DataRecord_tag::~TvXmlR_DataRecord_tag(void)
{
   FlushRefVal();
}


// --------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::PutChar(KpChar iOutch, XmlTagPars *pTagPars, int iFileIndex)
{
HRESULT retc=S_OK;

#if FALSE
   switch(iOutch)
   {
   case MCM_COMMENT_START: // '['
      retc=lpOutFilObj->PutCharProc(XC_TechNote, pTagPars, iFileIndex);
      break;
   case MCM_COMMENT_END: // ']'
      retc=lpOutFilObj->PutCharProc(XC_TechNote_e, pTagPars, iFileIndex);
      break;
   default:
#endif
      retc=lpOutFilObj->PutCharProc(iOutch, pTagPars, iFileIndex);
#if FALSE
      break;
   }
#endif

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::PutCharProc(KpChar uiChOut, bool bProcRef, /* const */ XmlTagPars *pTagPars)
{
HRESULT retc=S_OK;
bool delim_fl;

   if(lpOutFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if((uiChOut==XC_TechNote) /* || (uiChOut==MCM_COMMENT_START) */) bInsideComent=True; // '['

#ifdef Debug
// if((KpErrorProc.lMsgPar==1570) && (uiChOut==C_rtri)) // C_rtrif
// KpErrorProc.lMsgPar=1570;

// if((KpErrorProc.lMsgPar==1551) && (TvIntStrChr(iazTvCommentDelims,uiChOut)!=NULL))
// KpErrorProc.lMsgPar=1551;

// if(uiChOut==C_hyph)
// uiChOut=C_hyph;

if(uiChOut==C_Lpar) // '('
uiChOut=C_Lpar;
#endif

   if(SUCCEEDED(retc))
   {
      if(
         (
// #if FALSE
// cia kad komentarai nepertrauktu nuorodos vientisumo
            (
               (
                  (TvKpStrChr(iazTvCommentDelims, uiChOut)!=NULL) ||
                  bInsideComent
               ) &&
               bTextToBuffer &&
               (iRefBufIdx>0)
            ) ||
// #endif
            (
               (
                  TvIsUpper(uiChOut) ||
                  (TvIsAlpha(uiChOut) && (m_iLastWordLength>=2)) || // kad suveiktu STEVEo ir STEVE'o
                  (TvStrChr(lpszTvRefCtrlsAndPar,uiChOut)!=NULL) ||
                  (uiChOut==C_LBapost) || (uiChOut==C_LAapost) || (uiChOut==C_Rapost) ||
                  (uiChOut==C_LBquote) || (uiChOut==C_LAquote) || (uiChOut==C_Rquote) ||
                  (TvStrChr(lpszTvRefSpaces,uiChOut)!=NULL) ||
                  (uiChOut==C_NBSP) ||
                  (uiChOut==C_break) ||
//                (uiChOut==C_EnDash) ||
//                (uiChOut==C_hyph) || // reference separator !!!
                  (uiChOut==C_rtri) // C_rtrif
               ) &&
               (!bInsideComent)
            )
         ) &&
         bCollectReference
        )
      {
         if(TvIsAlpha(uiChOut)) m_iLastWordLength++;
         else m_iLastWordLength=0;

         if(uiChOut==C_rtri) bTextToBuffer=bProcRef; // C_rtrif

         if(
            (bTextToBuffer) &&
            (
               (iRefBufIdx>0) ||
               (
//                (TvStrChr(lpszTvRefCtrls,uiChOut)==NULL) &&
//                (uiChOut!=C_LBapost) && (uiChOut!=C_LAapost) && (uiChOut!=C_Rapost) &&
//                (uiChOut!=C_LBquote) && (uiChOut!=C_LAquote) && (uiChOut!=C_Rquote) &&
//                (TvIntStrChr(iazTvCommentDelims,uiChOut)==NULL) &&
                  (TvStrChr(lpszTvRefSpaces,uiChOut)==NULL) &&
                  (uiChOut!=C_NBSP) &&
//                (uiChOut!=C_EnDash) &&
                  (uiChOut!=C_break)
               )
            )
           )
         {
            if(iRefBufIdx<TV_XL_MAX_IX_LEN) aiRefBuf[iRefBufIdx++]=uiChOut;
            else
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
         }
         else
            retc=PutChar(uiChOut, pTagPars, XL_IX_DataFile);

//       if((!TvIsAlpha((Chars16)uiChOut)) && (!TvIsDigit((Chars16)uiChOut)))
         if(
            (TvStrChr(lpszTvRefSpaces, uiChOut)!=NULL) ||
            (uiChOut==C_NBSP) ||
            (uiChOut==C_break) ||
//          (uiChOut==C_EnDash) ||
            (TvStrChr(lpszTvRefCtrlsAndPar, uiChOut)!=NULL) ||
            (uiChOut==C_LBapost) || (uiChOut==C_LAapost) || (uiChOut==C_Rapost) ||
            (uiChOut==C_LBquote) || (uiChOut==C_LAquote) || (uiChOut==C_Rquote) // ||
//          (TvIntStrChr(iazTvCommentDelims,uiChOut)!=NULL)
           )
            bTextToBuffer=bProcRef;
      }
      else // if((TvIsUpper((Chars16)uiChOut) || (TvStrChr(lpszTvRefCtrlsAndPar,uiChOut)!=NULL)) && ...
      {
         m_iLastWordLength=0;

         if(bCollectReference)
         {
            delim_fl=(TvStrChr(lpszTvRefDelims, uiChOut)!=NULL);
            if((uiChOut>=XC_FirstDictTag) && (uiChOut<XC_LastDictTag)) delim_fl=TRUE;
            if(uiChOut==C_hyph) delim_fl=TRUE;

            retc=SeparateLastWord(!delim_fl);
            if(SUCCEEDED(retc)) retc=FlushRefVal();
            if(SUCCEEDED(retc)) retc=FlushLastWord();

            bTextToBuffer=(delim_fl && bProcRef);
         }

         if(SUCCEEDED(retc))
            retc=PutChar(uiChOut, pTagPars, XL_IX_DataFile);
      } // else if((TvIsUpper((Chars16)uiChOut) || (TvStrChr(lpszTvRefCtrlsAndPar,uiChOut)!=NULL)) && ...

   } // if(SUCCEEDED(retc))

   if((uiChOut==XC_TechNote_e) || (uiChOut==(KpChar)MCM_COMMENT_END)) bInsideComent=False; // ']'

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::SeparateLastWord(bool bWrdFlg)
{
HRESULT retc=S_OK;
int ii,lw_idx;
bool to_move;

   if(iLWordBufIdx>0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      lw_idx=0;

// last word start character
      to_move=bWrdFlg;
      for(ii=0; ii<iRefBufIdx; ii++)
      {
         if((aiRefBuf[ii]==XC_TechNote) /* || (aiRefBuf[ii]==MCM_COMMENT_START) */) // '['
         {
            do ii++;
            while((aiRefBuf[ii]!=XC_TechNote_e) /* && (aiRefBuf[ii]!=MCM_COMMENT_END) */ && (ii<iRefBufIdx)); //  ']'
         }
         else
         {
//          if((!TvIsAlpha((Chars16)aiRefBuf[ii])) && (!TvIsDigit((Chars16)aiRefBuf[ii])))
            if(
               (TvStrChr(lpszTvRefSpaces, aiRefBuf[ii])!=NULL) ||
//             (aiRefBuf[ii]==C_EnDash) ||
               (aiRefBuf[ii]==C_break) ||
               (aiRefBuf[ii]==C_NBSP)
              )
            {
               lw_idx=ii;
               to_move=TRUE;
            }
            else to_move=bWrdFlg;
         }
      }

// trailing spec. chars and spaces - to last word
      while(TRUE)
      {

         if(lw_idx>0)
         {
            if(aiRefBuf[lw_idx-1]==C_Apost) break; // '\''
            if(
//             (TvStrChr(lpszTvRefCtrlsAndPar, aiRefBuf[lw_idx-1])!=NULL) ||
//             (aiRefBuf[lw_idx-1]==C_LBapost) || (aiRefBuf[lw_idx-1]==C_LAapost) || (aiRefBuf[lw_idx-1]==C_Rapost) ||
//             (aiRefBuf[lw_idx-1]==C_LBquote) || (aiRefBuf[lw_idx-1]==C_LAquote) || (aiRefBuf[lw_idx-1]==C_Rquote) ||
//             (TvIntStrChr(iazTvCommentDelims,uiChOut)!=NULL) ||
               (TvStrChr(lpszTvRefSpaces, aiRefBuf[lw_idx-1])!=NULL) ||
//             (aiRefBuf[lw_idx-1]==C_EnDash) ||
               (aiRefBuf[lw_idx-1]==C_break) ||
               (aiRefBuf[lw_idx-1]==C_NBSP)
              )
               lw_idx--;
            else break;
         }
         else break;
      }

// move word/spaces
      if(to_move)
      {
         for(ii=lw_idx; ii<iRefBufIdx; ii++) auiLWordBuf[ii-lw_idx]=aiRefBuf[ii];

         iLWordBufIdx=iRefBufIdx-lw_idx;
         iRefBufIdx=lw_idx;
      }
   }

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::FlushRefVal()
{
HRESULT retc=S_OK;
int ii;
bool put_fl;
KpChar out_ch;

   if(lpOutFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=TestFreeParentheses();

   if((iRefBufIdx>TV_XR_REF_THRESHOLD) && SUCCEEDED(retc))
      retc=PutChar((KpChar)XC_Reference, NULL, XL_IX_DataFile);

   for(ii=0; (ii<iRefBufIdx) && SUCCEEDED(retc); ii++)
   {
      out_ch=aiRefBuf[ii];
      put_fl=TRUE;

      if(TvStrChr(lpszSpcEol, out_ch)!=NULL) out_ch=C_Spc;

      if(out_ch==C_Spc)
      {
         if(ii<iRefBufIdx-1)
            if((TvStrChr(lpszTvXmlNoSpcChars, aiRefBuf[ii+1])!=NULL) || (aiRefBuf[ii+1]==C_NBSP))
               put_fl=FALSE;

         if(ii==0) put_fl=FALSE;

         if(ii>0)
            if((TvStrChr(lpszTvXmlNoSpcChars, aiRefBuf[ii-1])!=NULL) || (aiRefBuf[ii-1]==C_NBSP))
               put_fl=FALSE;
      }

      if(put_fl)
         retc=PutChar(aiRefBuf[ii], NULL, XL_IX_DataFile);
   }

   if((iRefBufIdx>TV_XR_REF_THRESHOLD) && SUCCEEDED(retc))
      retc=PutChar((KpChar)XC_Reference_e, NULL, XL_IX_DataFile);

   iRefBufIdx=0;
   m_iLastWordLength=0;

   while((iUnGetCnt>0) && SUCCEEDED(retc))
      retc=PutChar((KpChar)ucaUnGetBuf[--iUnGetCnt], NULL, XL_IX_DataFile);

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::FlushLastWord(void)
{
HRESULT retc=S_OK;
int ii;

   if(lpOutFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   for(ii=0; (ii<iLWordBufIdx) && SUCCEEDED(retc); ii++)
      retc=PutChar(auiLWordBuf[ii], NULL, XL_IX_DataFile);
   iLWordBufIdx=0;

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::PutFirstBufChar(void)
{
HRESULT retc=S_OK;
int ii;
int jj;

   if(lpOutFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=PutChar(aiRefBuf[0], NULL, XL_IX_DataFile);
   ii=1;
   while((TvStrChr(lpszTvRefSpaces, aiRefBuf[ii])!=NULL) && (ii<iRefBufIdx) &&
                   SUCCEEDED(retc))
      retc=PutChar(aiRefBuf[ii++], NULL, XL_IX_DataFile);

   if(SUCCEEDED(retc))
   {
      iRefBufIdx-=ii;
      for(jj=0; jj<iRefBufIdx; jj++) aiRefBuf[jj]=aiRefBuf[ii+jj];
   }

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::UnGetLastBufChar()
{
HRESULT retc=S_OK;
int ii;

   if((iRefBufIdx<=0) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=UnGetChar(aiRefBuf[iRefBufIdx-1]);

   ii=iRefBufIdx-1;
   while((ii>0) && SUCCEEDED(retc))
   {
      if(TvStrChr(lpszTvRefSpaces, aiRefBuf[ii-1])==NULL) break;
      retc=UnGetChar(aiRefBuf[--ii]);
   }
   iRefBufIdx=ii;

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::UnGetChar(unsigned char ucChar)
{
HRESULT retc=S_OK;

   if(iUnGetCnt>=TV_XR_UNGET_WDT)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) ucaUnGetBuf[iUnGetCnt++]=ucChar;

return(retc);
}


// ------------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::TestFreeParentheses()
{
HRESULT retc=S_OK;
int ii;
int par_cnt;

// single closing parenthese in start of the buffer
   while((aiRefBuf[0]==(KpChar)MC_RightParenthese) && (iRefBufIdx>0) && SUCCEEDED(retc))
      retc=PutFirstBufChar();

// single opening parenthese in bottom of the buffer
   while((iRefBufIdx>0) && SUCCEEDED(retc))
   {
      if(aiRefBuf[iRefBufIdx-1]!=(KpChar)MC_LeftParenthese) break;
      retc=UnGetLastBufChar();
   }

// buffer enclosed in parentheses
   while((iRefBufIdx>0) && SUCCEEDED(retc))
   {
      if((aiRefBuf[0]==(KpChar)MC_LeftParenthese) && (aiRefBuf[iRefBufIdx-1]==(KpChar)MC_RightParenthese))
      {
         retc=PutFirstBufChar();
         retc=UnGetLastBufChar();
      }
      else break;
   }

// check parenthese count
   while(SUCCEEDED(retc))
   {
      par_cnt=0;
      for(ii=0; ii<iRefBufIdx; ii++)
      {
         if(aiRefBuf[ii]==(KpChar)MC_LeftParenthese) par_cnt++;  // '('
         if(aiRefBuf[ii]==(KpChar)MC_RightParenthese) par_cnt--;  // ')'
      }

// single opening parenthese in start of the buffer
      if((par_cnt>0) && (aiRefBuf[0]==(KpChar)MC_LeftParenthese) && SUCCEEDED(retc))
         retc=PutFirstBufChar();
      else
      {

// single closing parenthese in bottom of the buffer
         if((par_cnt<0) && (iRefBufIdx>0) && SUCCEEDED(retc))
         {
            if(aiRefBuf[iRefBufIdx-1]==(KpChar)MC_RightParenthese)
               retc=UnGetLastBufChar();
            else break;
         }
         else break;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvXmlR_DataRecord_tag::GetCurTag(/* enum XmlDictChars */ KpChar *piCurTag)
{
HRESULT retc=S_OK;

   if(piCurTag==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if((lpOutFilObj==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpOutFilObj->GetCurTag(piCurTag);

return(retc);
}
