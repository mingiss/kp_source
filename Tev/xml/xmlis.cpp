// ==================================================
// xmlis.cpp, former tvxmlx.cpp
// XML file index splitter/inverter, text mode


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <ctype.h>
#include <string.h>
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
#include "kpctype.h"
#include "kpstdio.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "tvxmle.h"
#include "tvxmls.h"


// --------------------------------------------------
const KpChar lpszaAbbrExp_l[][2][TV_X_MAX_ABBR_LENGTH] =
{
   C_Z_Car, C_Point, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Z_Car, C_E, C_M, C_E_Adot, C_S, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,

   C_S_Car, C_N, C_E, C_K, C_Point, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Spc, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,

   C_N, C_T, C_K, C_Point, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Spc, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,

   C_Z_Car, C_R, C_Point, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Spc, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,

   C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul
};

const KpChar lpszaAbbrExp_e[][2][TV_X_MAX_ABBR_LENGTH] =
{
   C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul
};

const KpChar lpszaAbbrExp_v[][2][TV_X_MAX_ABBR_LENGTH] =
{
   C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul
};

const KpChar lpszaAbbrExp_f[][2][TV_X_MAX_ABBR_LENGTH] =
{
   C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul
};

const KpChar lpszaAbbrExp_r[][2][TV_X_MAX_ABBR_LENGTH] =
{
   C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul,
      C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul, C_Nul
};


// --------------------------------------------------
const unsigned char *lpszaCjt_l[] =
{
// (const unsigned char *)".CCARONIA",
   (const unsigned char *)".CIA",
// (const unsigned char *)".ZCARONR",
   (const unsigned char *)".ZR",
// (const unsigned char *)".SCARONNEK",
   (const unsigned char *)".SNEK",
   (const unsigned char *)".SEN",
   (const unsigned char *)".AB",
   (const unsigned char *)".T P", // !!! ???
   (const unsigned char *)".SEE",
   NULL
};

const unsigned char *lpszaCjt_e[] = { NULL };
const unsigned char *lpszaCjt_v[] = { NULL };
const unsigned char *lpszaCjt_f[] = { NULL };
const unsigned char *lpszaCjt_r[] = { NULL };


// ======================================================
// --------------------------------------------------
XmlIs_IndexRecord::XmlIs_IndexRecord
(
XmlO1 *lpXmlFileOb,
const int /* XL_Indexes */ uiIxFileIdx,
const long lMainKeyValue,
bool bTstInverted,
bool bTstCombinedLeft,
bool bTstCombinedRight,
bool bProcessSubkeys,
unsigned char ucLanguage,
// EC_Types iEcType,
int iMinEntryLength
)
{
   lpXmlFilObj=lpXmlFileOb;
   uiIxFIdx=uiIxFileIdx;
   lMainKeyVal=lMainKeyValue;
   m_iMinEntryLength=iMinEntryLength;

   uiLastChar=C_Nul;
   iParLev=0;
   m_bAfterApost=False;

   iValIdx=0;

   bTestInverted=bTstInverted;
   bTestCombinedLeft=bTstCombinedLeft;
   bTestCombinedRight=bTstCombinedRight;
   m_bProcessSubkeys=bProcessSubkeys;

   m_ucIxLang=ucLanguage;
// m_iEcTyp=iEcType;
}


// --------------------------------------------------
XmlIs_IndexRecord::~XmlIs_IndexRecord(void)
{
   if(iValIdx>0) CompleteIndexRecord(False);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutChar(KpChar uiChOut)
{
HRESULT retc=S_OK;
XL_FileTypes f_typ;
KpChar c_out;

   c_out=uiChOut;

   if(lpXmlFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpXmlFilObj->GetFileType(&f_typ, uiIxFIdx);

   if(
      ((f_typ==XL_FT_MainIxFile) || (f_typ==XL_FT_IxFile)) &&
      SUCCEEDED(retc)
     )
   {
// intern side of brackets or comments - do not output to index files
      if((c_out==(KpChar)MC_LeftBracket) || (c_out==(KpChar)XC_TechNote) || (c_out==(KpChar)XC_Level)) iParLev++; // '['

      if(c_out==C_Apost) m_bAfterApost=True;

      if(iParLev<1)
      {
// tab's, eol's, C_NBSP's to spaces
         if(TvStrChr(lpszSpcEol, c_out)!=NULL) c_out=C_Spc;
         if(c_out==C_NBSP) c_out=C_Spc;

         if(c_out==C_Spc) m_bAfterApost=False;

         if((!m_bAfterApost) || (!bCutEndingsAfterApostrophe))
         {

// skip multiple spaces and spaces before and after
            if(c_out==C_Spc) uiLastChar=c_out;
            else
            {
               if((uiLastChar!=C_Nul) && (iValIdx>0) &&
                  (uiLastChar > 0) && (uiLastChar < C_CharSize0))
               {
                  if(iValIdx<TV_XL_MAX_IX_LEN)
                  {
//                   auiValue[iValIdx++]=TvToLower((KpChar)uiLastChar);
                     auiValue[iValIdx++]=(KpChar)uiLastChar;
                  }
                  else
                     retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
               }
               uiLastChar=C_Nul;

// to buffer
               if((c_out > 0) && (c_out < C_CharSize0) && SUCCEEDED(retc))
               {
                  if(iValIdx<TV_XL_MAX_IX_LEN)
                  {
//                   auiValue[iValIdx++]=TvToLower((KpChar)c_out);
                     auiValue[iValIdx++]=(KpChar)c_out;
                  }
                  else
                     retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
               }

            } // else if(c_out==C_Spc)

         } // if(!m_bAfterApost)

      } // if(iParLev<1)

      if((c_out==(KpChar)MC_RightBracket) || (c_out==(KpChar)XC_TechNote_e) || (c_out==(KpChar)XC_Level_e)) iParLev--; // ']'

   } // if(((f_typ== ...

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::GetParLev(int *piParLev)
{
   *piParLev=iParLev;

return(S_OK);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutValueSingle(int iIxFileIdx, int iLanguage)
{
HRESULT retc=S_OK;
unsigned char str_buf[TV_XL_MAX_IX_LEN+2];
KpChar val_buf[TV_XL_MAX_IX_LEN+1];
unsigned char val_str[TV_XL_MAX_IX_LEN+2];
const unsigned char *sub_str;
int entr_len;
int len;

   if((iIxFileIdx>=XL_IX_NumOfIndexes0) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((lpXmlFilObj==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=KpCharToIndexEntry(str_buf, auiValue, iValIdx, TV_XL_MAX_IX_LEN+1, iLanguage, iaIxEncodings[iIxFileIdx] /* iEcTyp */);

// VLZ "sich" metam lauk
   if(SUCCEEDED(retc))
   {
      entr_len = strlen(str_buf);
      sub_str = (const unsigned char *)"sich ";
      len = strlen(sub_str);
      if(strstr(str_buf, sub_str) == str_buf) TvStrCpy(str_buf, str_buf + len);

      entr_len = strlen(str_buf);
      sub_str = (const unsigned char *)", sich#";
      len = strlen(sub_str);
      if(strstr(str_buf, sub_str) == str_buf + entr_len - len)
      {
         str_buf[entr_len - len] = EXACT_ENTRY_CHR; // '#'
         str_buf[entr_len - len + 1] = Nul;
      }

      entr_len = strlen(str_buf);
      sub_str = (const unsigned char *)", sich";
      len = strlen(sub_str);
      if(strstr(str_buf, sub_str) == str_buf + entr_len - len) str_buf[entr_len - len] = Nul;

      entr_len = strlen(str_buf);
      sub_str = (const unsigned char *)" sich#";
      len = strlen(sub_str);
      if(strstr(str_buf, sub_str) == str_buf + entr_len - len)
      {
         str_buf[entr_len - len] = EXACT_ENTRY_CHR; // '#'
         str_buf[entr_len - len + 1] = Nul;
      }

      entr_len = strlen(str_buf);
      sub_str = (const unsigned char *)" sich";
      len = strlen(sub_str);
      if(strstr(str_buf, sub_str) == str_buf + entr_len - len) str_buf[entr_len - len] = Nul;
   }

   if(SUCCEEDED(retc))
   {
      entr_len=strlen(str_buf);
      if(entr_len>0) if(str_buf[entr_len-1]==EXACT_ENTRY_CHR) // '#'
         entr_len--;
   }

   if(SUCCEEDED(retc))
      if((entr_len>=m_iMinEntryLength) &&
         (auiValue[0] != C_Dash) &&  // '-' // nereikia variantu "-a", "-e" etc.
         (!TvIsDigit(auiValue[0])))  // nereikia prasidedanciu skaitmenim
      {
         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutStr(str_buf, iIxFileIdx);

         if(SUCCEEDED(retc)) retc=lpXmlFilObj->CompleteIndexEntry(iIxFileIdx);
         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutNumVal(lMainKeyVal, iIxFileIdx);

//       if(SUCCEEDED(retc)) retc=PutEol();
         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutCharProc(C_Lf, NULL, iIxFileIdx); // '\n'

// report entry
         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutRepCharProc((KpChar)iLanguage, iIxFileIdx); // '\t'
         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutRepCharProc(C_Tab, iIxFileIdx); // '\t'

         if(SUCCEEDED(retc))
         {
            len=iValIdx;
            if(len>0) if(auiValue[len-1]==EXACT_ENTRY_CHR) len--; // '#'
            if(len>TV_XL_MAX_IX_LEN) len=TV_XL_MAX_IX_LEN;

            TvKpStrNCpy(val_buf, auiValue, len);
            val_buf[len]=C_Nul;
            TvKpStrClearAccents(val_buf);
            retc=KptStrDecode(val_str, val_buf, TV_XE_CTBL);
            if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
            {
               retc=S_OK;
#ifdef Debug
// !!!         retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
#endif
            }
         }
         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutRepStr(val_str, iIxFileIdx);
//       if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutRepIntStr(val_buf, iIxFileIdx);

         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutRepCharProc(C_Tab, iIxFileIdx); // '\t'


         if(SUCCEEDED(retc))
         {
            str_buf[entr_len]=Nul;
            retc=lpXmlFilObj->PutRepStr(str_buf, iIxFileIdx);
         }

         if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutRepCharProc(C_Lf, iIxFileIdx); // '\n'

      } // if((entr_len>=m_iMinEntryLength) && (auiValue[0] != C_Dash))

return(retc);
}


HRESULT XmlIs_IndexRecord::PutValue(void)
{
HRESULT retc=S_OK;

   if((uiIxFIdx==XL_IX_HwIndex) && SUCCEEDED(retc))
      retc=PutValueSingle(XL_IX_HxIndex, caIxLangs[XL_IX_HxIndex]);

   if(SUCCEEDED(retc)) retc=PutValueSingle(uiIxFIdx, m_ucIxLang);

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutSpace(void)
{
HRESULT retc=S_OK;

   if(lpXmlFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutCharProc(C_Spc, NULL, uiIxFIdx);

return(retc);
}


// --------------------------------------------------
#if FALSE
HRESULT XmlIs_IndexRecord::PutEol(void)
{
HRESULT retc=S_OK;

   if(lpXmlFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpXmlFilObj->PutCharProc('\n', NULL, uiIxFIdx);

return(retc);
}
#endif


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutDelLeftComb(int iCutPos, bool bPutDelim)
{
HRESULT retc=S_OK;
XmlIs_IndexRecord *ind_rec=NULL;
int ii;
int jj;
bool entry_ready=True;

   if(iCutPos>=iValIdx)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(auiValue[iCutPos]!=(KpChar)MC_CombDelimiter)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(/* ((iCutPos>0) || (!bPutDelim)) && */ SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                           bTestInverted, bTestCombinedLeft, (!bPutDelim) /* && bTestCombinedRight*/,  m_bProcessSubkeys,
                           m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

      if(SUCCEEDED(retc))
      {
         ii=iCutPos;
         if(ii>0) ii--;
         if(ii>0) if(auiValue[ii]==C_Spc) ii--;
         while(ii>0)
         {
            if(auiValue[ii]==C_Spc) break;
            ii--;
         }

         if((ii==0) && bPutDelim) entry_ready=False;
      }

      if(entry_ready && SUCCEEDED(retc))
      {
         for(jj=0; (jj<ii) && SUCCEEDED(retc); jj++)
            retc=ind_rec->PutChar(auiValue[jj]);
         if((auiValue[ii]==C_Spc) && SUCCEEDED(retc)) retc=ind_rec->PutChar(auiValue[ii]);

         if(bPutDelim && SUCCEEDED(retc)) retc=ind_rec->PutChar(auiValue[iCutPos]);

         for(jj=iCutPos+1; (jj<iValIdx) && SUCCEEDED(retc); jj++)
            retc=ind_rec->PutChar(auiValue[jj]);

         if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);
      }

      KP_DELETE(ind_rec);

   } // if(/* ((iCutPos>0) || (!bPutDelim)) && */ SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutDelRightComb(int iCutPos, bool bPutDelim)
{
HRESULT retc=S_OK;
XmlIs_IndexRecord *ind_rec=NULL;
int ii;
int jj;
bool entry_ready=True;

   if(iCutPos>=iValIdx)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(auiValue[iCutPos]!=(KpChar)MC_CombDelimiter)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(/* ((iCutPos<iValIdx-1) || (!bPutDelim)) && */ SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                           bTestInverted, (!bPutDelim) /* && bTestCombinedLeft */, bTestCombinedRight,  m_bProcessSubkeys,
                           m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

      if(SUCCEEDED(retc))
      {
         ii=iCutPos+1;
         if(ii<iValIdx) if(auiValue[ii]==C_Spc) ii++;
         while(ii<iValIdx)
         {
            if((auiValue[ii]==C_Spc) || (auiValue[ii]==(KpChar)MC_CombDelimiter)) break;
            ii++;
         }

         jj=ii;
         while(jj<iValIdx)
         {
            if(auiValue[jj]==C_Spc) jj++;
            else break;
         }

         if(jj<iValIdx)
            if(bPutDelim && (auiValue[jj]==(KpChar)MC_CombDelimiter))
               entry_ready=False;

         if(bPutDelim && (ii>=iValIdx)) entry_ready=False;
      }

      if(entry_ready && SUCCEEDED(retc))
      {
         for(jj=0; (jj<iCutPos) && SUCCEEDED(retc); jj++)
            retc=ind_rec->PutChar(auiValue[jj]);

         if(bPutDelim && SUCCEEDED(retc)) retc=ind_rec->PutChar(auiValue[iCutPos]);

         if(SUCCEEDED(retc))
            for(jj=ii; (jj<iValIdx) && SUCCEEDED(retc); jj++)
               retc=ind_rec->PutChar(auiValue[jj]);

         if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);
      }

      KP_DELETE(ind_rec);

   } // if(/* ((iCutPos<iValIdx-1) || (!bPutDelim)) && */ SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutOptional(int iCutPos, bool bPutWith)
{
HRESULT retc=S_OK;
XmlIs_IndexRecord *ind_rec=NULL;
int ii;
int par_lev;
bool out_of_pars=True;

   if(iCutPos>=iValIdx)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(auiValue[iCutPos]!=(KpChar)MC_LeftParenthese)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                           bTestInverted, bTestCombinedLeft, bTestCombinedRight, m_bProcessSubkeys,
                           m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

      for(ii=0; (ii<iCutPos) && SUCCEEDED(retc); ii++)
         retc=ind_rec->PutChar(auiValue[ii]);

      out_of_pars=False;
      par_lev=1;
      for(ii=iCutPos+1; (ii<iValIdx) && SUCCEEDED(retc); ii++)
      {
         if(auiValue[ii]==(KpChar)MC_LeftParenthese) par_lev++;
         if(auiValue[ii]==(KpChar)MC_RightParenthese)
         {
            par_lev--;
            if((par_lev!=0) || out_of_pars)
               retc=ind_rec->PutChar(auiValue[ii]);
            if(par_lev==0) out_of_pars=True;
         }
         else if(bPutWith || out_of_pars) retc=ind_rec->PutChar(auiValue[ii]);
      }
      if((par_lev!=0) && (uiIxFIdx!=XL_IX_TxIndex) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

      KP_DELETE(ind_rec);

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutDiffValParetheses(int iCutPos)
{
HRESULT retc=S_OK;
XmlIs_IndexRecord *ind_rec=NULL;
int ii;
int par_lev;
int par_end;

   if(iCutPos>=iValIdx)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(auiValue[iCutPos]!=(KpChar)MC_LeftParenthese)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      par_lev=1;
      for(par_end=iCutPos+1; (par_end<iValIdx) && (par_lev>0); par_end++)
      {
         if(auiValue[par_end]==(KpChar)MC_LeftParenthese) par_lev++;
         if(auiValue[par_end]==(KpChar)MC_RightParenthese) par_lev--;
      }

// not only on the end of string - necessary for inverted personal names
//    if(par_end>=iValIdx)
      {
#if FALSE
// first part - not needed, allready put by PutOptional()
         KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                              bTestInverted, bTestCombinedLeft, bTestCombinedRight, ucIxLang, iEcTyp, m_iMinEntryLength));

         for(ii = 0; (ii < iCutPos) && SUCCEEDED(retc); ii++)
            retc = ind_rec->PutChar(auiValue[ii]);

         if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

         KP_DELETE(ind_rec);
#endif

// rest
         KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                              bTestInverted, bTestCombinedLeft, bTestCombinedRight, m_bProcessSubkeys,
                              m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

         for(ii=iCutPos+1; (ii<par_end-1) && SUCCEEDED(retc); ii++)
           retc=ind_rec->PutChar(auiValue[ii]);

         if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

         KP_DELETE(ind_rec);

      } // if(ii>=iValIdx)

   } // if(SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutDiffVal(int iCutPos)
{
HRESULT retc=S_OK;
XmlIs_IndexRecord *ind_rec=NULL;
int ii;

   if(iCutPos>=iValIdx)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if((auiValue[iCutPos]!=(KpChar)MC_IndEntrDelimiter) && (auiValue[iCutPos]!=(KpChar)MC_InvertDelimiter))
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// first part
   if(/*(auiValue[iCutPos]!=MC_InvertDelimiter) &&*/ SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                              bTestInverted, bTestCombinedLeft, bTestCombinedRight, m_bProcessSubkeys,
                              m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

      for(ii=0; (ii<iCutPos) && SUCCEEDED(retc); ii++)
         retc=ind_rec->PutChar(auiValue[ii]);

      if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

      KP_DELETE(ind_rec);
   }

// rest
   if(SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                              bTestInverted, bTestCombinedLeft, bTestCombinedRight, m_bProcessSubkeys,
                              m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

      for(ii=iCutPos+1; (ii<iValIdx) && SUCCEEDED(retc); ii++)
        retc=ind_rec->PutChar(auiValue[ii]);

      if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

      KP_DELETE(ind_rec);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::PutSwapped(int iCutPos)
{
HRESULT retc=S_OK;
XmlIs_IndexRecord *ind_rec=NULL;
int ii;

   if(iCutPos>=iValIdx)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(auiValue[iCutPos]!=(KpChar)MC_InvertDelimiter)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

#if FALSE
// first part - not needed - allready put by PutDiffVal()
   if(SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                  bTestInverted, bTestCombinedLeft, bTestCombinedRight, ucIxLang, iEcTyp, m_iMinEntryLength));

      for(ii=0; (ii<iCutPos) && SUCCEEDED(retc); ii++)
         retc=ind_rec->PutChar(auiValue[ii]);

      if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

      KP_DELETE(ind_rec);
   }
#endif

// combined
   if(SUCCEEDED(retc))
   {
      KP_NEW(ind_rec, XmlIs_IndexRecord(lpXmlFilObj, uiIxFIdx, lMainKeyVal,
                              bTestInverted, bTestCombinedLeft, bTestCombinedRight, m_bProcessSubkeys,
                              m_ucIxLang, /* m_iEcTyp, */ m_iMinEntryLength));

      for(ii=iCutPos+1; (ii<iValIdx) && SUCCEEDED(retc); ii++)
        retc=ind_rec->PutChar(auiValue[ii]);

      if(SUCCEEDED(retc)) retc=ind_rec->PutChar(C_Spc);

      for(ii=0; (ii<iCutPos) && SUCCEEDED(retc); ii++)
         retc=ind_rec->PutChar(auiValue[ii]);

      if(SUCCEEDED(retc)) retc=ind_rec->CompleteIndexRecord(False);

      KP_DELETE(ind_rec);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlIs_IndexRecord::CompleteIndexRecord(bool bWholeRecord)
{
HRESULT retc=S_OK;
int ii;
bool put_whole=True;
// unsigned char str_buf[200];

// KpCharToStrNoCtrl(str_buf, auiValue, iValIdx, 200, plpszaXmlSpecCharTagsMain /* ??? !!! */);

   if(lpXmlFilObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((iValIdx>0) && (SUCCEEDED(retc)))
   {


// 1-st priority: '(' and ')'
      if(m_bProcessSubkeys) for(ii=0; (ii<iValIdx) && SUCCEEDED(retc); ii++)
      {
         if((auiValue[ii]==(KpChar)MC_LeftParenthese) && SUCCEEDED(retc))
         {
// optional fragments
            retc=PutOptional(ii, False);
            if(SUCCEEDED(retc)) retc=PutOptional(ii, True);

// different meanings - split to different entries
            if(SUCCEEDED(retc)) retc=PutDiffValParetheses(ii);

// rest of the line will be tested in child objects
            break;
         }
      }

// nothing found - 2-nd priority: ';'
      if(m_bProcessSubkeys) if(ii>=iValIdx) for(ii=0; (ii<iValIdx) && SUCCEEDED(retc); ii++)
      {
// different meanings - split to different entries
         if((auiValue[ii]==(KpChar)MC_IndEntrDelimiter) && SUCCEEDED(retc))
         {
            put_whole=False;
            retc=PutDiffVal(ii);
// rest of the line will be tested in child objects
            break;
         }
      }

// nothing found - 3-d priority: '/'
      if(m_bProcessSubkeys) if(ii>=iValIdx) for(ii=0; (ii<iValIdx) && SUCCEEDED(retc); ii++)
      {
         if(auiValue[ii]==(KpChar)MC_CombDelimiter)
         {
// optional ending ("mazas/-a") - should not be used
//!!!       retc=PutOptComma(ii);

// alternative phrases
            if(bTestCombinedLeft) retc=PutDelLeftComb(ii, False);
            if(bTestCombinedLeft && (SUCCEEDED(retc))) retc=PutDelLeftComb(ii, True);
            if(bTestCombinedRight && (SUCCEEDED(retc))) retc=PutDelRightComb(ii, False);
            if(bTestCombinedRight && (SUCCEEDED(retc))) retc=PutDelRightComb(ii, True);

// rest of the line will be tested in child objects
            break;
         }
      }

// nothing found - 4-th priority: ','
      if(m_bProcessSubkeys) if(ii>=iValIdx) for(ii=0; (ii<iValIdx) && SUCCEEDED(retc); ii++)
      {
         if((auiValue[ii]==(KpChar)MC_InvertDelimiter) && SUCCEEDED(retc))
         {
// optional ending ("mazas, -a") - should not be used
//!!!       retc=PutOptComma(ii);

// different meanings - split to different entries
            retc=PutDiffVal(ii);

// swapped personal names
            if(bTestInverted && SUCCEEDED(retc)) retc=PutSwapped(ii);

// rest of the line will be tested in child objects
            break;
         }
      }

#if FALSE // already processed in PutChar(), look m_bAfterApost
// nothing found - 5-th priority: "'"
      if(ii>=iValIdx) for(ii=0; (ii<iValIdx) && SUCCEEDED(retc); ii++)
      {
         if((auiValue[ii]=='\'') && SUCCEEDED(retc))
         {
// lithuanian ending in foreign names ("Clinton'as") - should not be used
//!!!       retc=PutOptComma(ii);

// rest of the line will be tested in child objects
//!!!       break;
         }
      }
#endif

// put whole value without changes
      if(put_whole && SUCCEEDED(retc))
      {
//       if(SUCCEEDED(retc)) retc=PutValue();
         if(bWholeRecord && SUCCEEDED(retc))
         {
#if FALSE
            if(iValIdx<TV_XL_MAX_IX_LEN) auiValue[iValIdx]=C_Nul;
            else
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=CutTrailSpcsInt((int *)auiValue);
            if(SUCCEEDED(retc)) iValIdx=TvIntStrLen((int *)auiValue);
#endif
            if(SUCCEEDED(retc)) retc=PutChar(EXACT_ENTRY_CHR); // '#' gale - tikslaus atitikmens paieskai
         }
         if(SUCCEEDED(retc)) retc=PutValue();
      }

// clear value
      iValIdx=0;

   } // if((iValIdx>0) && (SUCCEEDED(retc)))

   iParLev=0;
   m_bAfterApost=False;

return(retc);
}


HRESULT /* XmlIs_IndexRecord:: */ ExpandAbbr
(
   KpChar *auiDest,
   const KpChar *auiSrc,
   int *iValIdx,
   int iStrBuifSize,
   unsigned char ucLang
)
{
HRESULT retc=S_OK;
const KpChar (*s_tbl)[2][TV_X_MAX_ABBR_LENGTH]=NULL;
const KpChar *tbl_ptr;
const KpChar *pnts;
KpChar *pntd;
KpChar *wrd_start;
bool found;

   if((auiDest==NULL) || (auiSrc==NULL) || (iValIdx==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) switch(ucLang)
   {
   case KP_LNG_LIT:
   case KP_LNG_LIS:
   case KP_LNG_LIX: s_tbl=lpszaAbbrExp_l; break;
   case KP_LNG_ENG: s_tbl=lpszaAbbrExp_e; break;
   case KP_LNG_GER: s_tbl=lpszaAbbrExp_v; break;
   case KP_LNG_FRE: s_tbl=lpszaAbbrExp_f; break;
   case KP_LNG_RUS: s_tbl=lpszaAbbrExp_r; break;
   case KP_LNG_NO: break;
   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      break;
   }

   if(SUCCEEDED(retc))
   {
      pnts=auiSrc;
      pntd=wrd_start=auiDest;

      while((pnts - auiSrc < *iValIdx) && SUCCEEDED(retc))
      {
// put ordinary word
         while((TvStrChr(lpszSpcEol, *pnts)==0) && (pnts - auiSrc < *iValIdx) && SUCCEEDED(retc))
         {
            if(pntd-auiDest<iStrBuifSize-1) *(pntd++)=(*pnts++);
            else
            {
               pnts++;
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);
            }
         }
         if(pntd-auiDest<iStrBuifSize) *pntd=C_Nul;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);

// search for abbreviation
         if(s_tbl!=NULL)
         {
            tbl_ptr=(const KpChar *)s_tbl;
            found=False;
            while((*tbl_ptr) && (!found) && SUCCEEDED(retc))
            {
               if(TvKpStrCmp(wrd_start, tbl_ptr)==0)
               {
                  tbl_ptr+=TV_X_MAX_ABBR_LENGTH;
                  found=True;

                  if(wrd_start + TvKpStrLen(tbl_ptr) - auiDest < iStrBuifSize-1)
                     TvKpStrCpy(wrd_start, tbl_ptr);
                  else
                     retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

                  tbl_ptr+=TV_X_MAX_ABBR_LENGTH;
               }
               else
                  tbl_ptr+=TV_X_MAX_ABBR_LENGTH*2;
            }
         }

// skip current word
         while(*wrd_start) wrd_start++;
         pntd=wrd_start;

// copy spaces
         while((TvStrChr(lpszSpcEol, *pnts)!=0) && (pnts - auiSrc < *iValIdx) && SUCCEEDED(retc))
         {
            if(pntd-auiDest<iStrBuifSize-1) *(pntd++)=(*pnts++);
            else
            {
               pnts++;
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);
            }
         }
         if(pntd-auiDest<iStrBuifSize) *pntd=C_Nul;
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);
         wrd_start=pntd;
      }

      if(pntd-auiDest<iStrBuifSize) *pntd=C_Nul;
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);

      *iValIdx=pntd-auiDest;
   }

return(retc);
}


// --------------------------------------------------
HRESULT /* XmlIs_IndexRecord:: */ DelComments
(
KpChar *auiValBuf,
int *iValIdx
)
{
HRESULT retc=S_OK;
const KpChar *pnts;
KpChar *pntd;
KpChar ii;
bool inside_comment;
bool sub_xref;

   if((auiValBuf==NULL) || (iValIdx==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pnts=pntd=auiValBuf;
   inside_comment=False;
   sub_xref=False;

   if(SUCCEEDED(retc)) while((*pnts) && SUCCEEDED(retc))
   {
      ii=(*pnts++);
      switch(ii)
      {
      case C_Lbrack:
      case XC_TechNote:
         inside_comment=True;
         break;
      case C_Rbrack:
      case XC_TechNote_e:
         inside_comment=False;
         break;
      case XC_Reference:
      case XC_RefWord:
         if(inside_comment) sub_xref=True;
         break;
      case XC_Reference_e:
      case XC_RefWord_e:
         if(inside_comment) sub_xref=False;
         break;
      default:
         if(((!inside_comment) || sub_xref) && (ii!=C_rtri)) *(pntd++)=ii; // C_rtrif
         break;
      }
   }

   if(SUCCEEDED(retc))
   {
      *pntd=C_Nul;
      *iValIdx=pntd-auiValBuf;
   }

return(retc);
}


// --------------------------------------------------
HRESULT /* XmlIs_IndexRecord:: */ DelCjts(unsigned char *lpszDest, const unsigned char *lpszSrc, unsigned char ucLanguage, EC_Types iEcType)
{
HRESULT retc=S_OK;
const unsigned char **s_tbl=NULL;
const unsigned char *pnts;
unsigned char *pntd;
const unsigned char **tbl_ptr;
int ii;

   switch(ucLanguage)
   {
   case KP_LNG_LIT:
   case KP_LNG_LIS:
   case KP_LNG_LIX: s_tbl=lpszaCjt_l; break;
   case KP_LNG_ENG: s_tbl=lpszaCjt_e; break;
   case KP_LNG_GER: s_tbl=lpszaCjt_v; break;
   case KP_LNG_FRE: s_tbl=lpszaCjt_f; break;
   case KP_LNG_RUS: s_tbl=lpszaCjt_r; break;
   case KP_LNG_NO: break;
   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      break;
   }

   if(SUCCEEDED(retc))
   {
      pnts=lpszSrc;
      pntd=lpszDest;

      do
      {
// to the end of the word
         while((!cisnotalpha(*pnts)) && *pnts) *(pntd++)=(*pnts++);

         if(s_tbl!=NULL)
         {
            tbl_ptr=s_tbl;
            while(*tbl_ptr)
            {
               retc=/*TvXmlEs_tag::*/EndCmp(pntd, lpszDest, -1, *tbl_ptr, &ii, ucLanguage, iEcType);
               if((ii==0) && SUCCEEDED(retc))
               {
                  pntd-=strlen((const char *)*tbl_ptr)-(**tbl_ptr==WORD_START_CHR?1:0); // '.'
                  while(cisnotalpha(*pnts) && (*pnts)) pnts++;
                  break;
               }

               tbl_ptr++;
            }
         }

         while(cisnotalpha(*pnts) && (*pnts) && SUCCEEDED(retc)) *(pntd++)=(*pnts++);

      } while(*pnts && SUCCEEDED(retc));

      *pntd=Nul;
   }

return(retc);
}


// -------------------------------------------------
HRESULT CutEndingsApost(KpChar *iaBuffer)
{
HRESULT retc=S_OK;
KpChar *pnts;
KpChar *pntd;

   if(iaBuffer==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(bCutEndingsAfterApostrophe && SUCCEEDED(retc))
   {
      pntd=pnts=iaBuffer;
      while(*pnts)
      {
         if(*pnts==C_Apost)
         {
            pnts++;
            while(TvIsAlpha(*pnts)) pnts++;
         }
         else *(pntd++)=(*pnts++);
      }
      *pntd=C_Nul;
   }

return(retc);
}


// -------------------------------------------------
HRESULT CutEndingsSmall(KpChar *iaBuffer)
{
HRESULT retc=S_OK;
KpChar *pnts;
KpChar *pntd;
KpChar *buf_ptr=NULL;

   if(iaBuffer==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(buf_ptr, KpChar, TvKpStrLen(iaBuffer) + 1);

   if(SUCCEEDED(retc))
   {
      pnts=iaBuffer;
      pntd=buf_ptr;

      while(*pnts)
      {
         if(TvIsLower(*pnts) && pnts>=iaBuffer+2)
         {
            if(TvIsUpper(*(pnts-1)) && TvIsUpper(*(pnts-2)))
               while(TvIsAlpha(*pnts)) pnts++;
            else *(pntd++)=(*pnts++);
         }
         else *(pntd++)=(*pnts++);
      }

      *pntd=C_Nul;
      TvKpStrCpy(iaBuffer, buf_ptr);
   }

   KP_DELETE(buf_ptr);

return(retc);
}


// -------------------------------------------------
HRESULT KpCharToIndexEntry(unsigned char *lpszStrBuf, const KpChar *auiValue, int iValLen, int iStrBufSize, unsigned char ucLang, EC_Types iEcType)
{
HRESULT retc=S_OK;
int chr_cnt;
KpChar *val_buf=NULL;
KpChar *val_buf_1=NULL;

   KP_NEWA(val_buf, KpChar, iStrBufSize + 1);
   KP_NEWA(val_buf_1, KpChar, iStrBufSize + 1);

#if FALSE // #ifdef Debug
printf(">>>");
int ii;
for(ii=0; ii<iValLen; ii++)
{
if(auiValue[ii]<0x80) printf("%c", auiValue[ii]);
else printf("<%d>", auiValue[ii]);
}
printf("<<<\n");
#endif

   chr_cnt=iValLen;
   if((chr_cnt>=iStrBufSize) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=ExpandAbbr(val_buf, auiValue, &chr_cnt, iStrBufSize, ucLang);
   if(SUCCEEDED(retc)) retc=DelComments(val_buf, &chr_cnt);
   if(SUCCEEDED(retc)) val_buf[chr_cnt]=C_Nul;

   if(SUCCEEDED(retc)) retc=CutEndingsApost(val_buf);
// if(SUCCEEDED(retc)) retc=CutEndingsSmall(val_buf);
   if(SUCCEEDED(retc))
   {
      if(ucLang != KP_LNG_NO)
         retc=TvXmlEs.CutEndingsDelCjts(val_buf_1, val_buf, ucLang, (EC_Types)TV_XE_CTBL /* (iEcType<EC_First_Type)?iEcType:(EC_Types)TV_XE_CTBL */, True);
      else TvKpStrCpy(val_buf_1, val_buf);
   }

// if((iEcType == EC_ASCII) && SUCCEEDED(retc)) TvKpStrLwr(val_buf_1);

   if(SUCCEEDED(retc)) chr_cnt=TvKpStrLen(val_buf_1);

   if(SUCCEEDED(retc)) retc=KpCharToStrNoCtrl(lpszStrBuf, val_buf_1, chr_cnt, iStrBufSize, plpszaXmlSpecCharTagsMain /* ??? !!! */, iEcType);

   if(SUCCEEDED(retc)) retc=CutInitSpcs(lpszStrBuf);
   if(SUCCEEDED(retc)) retc=CutTrailSpcs(lpszStrBuf);

   KP_DELETEA(val_buf);
   KP_DELETEA(val_buf_1);

return(retc);
}


// -------------------------------------------------
HRESULT IndexEntryToCompareStr(unsigned char *lpszStrBuf, const unsigned char *lpszIndexEntry, bool bClearDoubleEntriesChr, bool bClearExactEntryChr, EC_Types iEncoding)
{
HRESULT retc=S_OK;
int pos;
unsigned char *pnts;
unsigned char *pntd;

   if(((lpszStrBuf == NULL) || (lpszIndexEntry == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(lpszStrBuf != lpszIndexEntry) strcpy(lpszStrBuf, lpszIndexEntry);

// if(SUCCEEDED(retc)) retc = RemoveSpaces(lpszStrBuf);

// if(SUCCEEDED(retc)) retc = RemoveSpCharsSpc(lpszStrBuf);
   if(SUCCEEDED(retc))
   {
      pnts=lpszStrBuf;
      pntd=lpszStrBuf;
      while(*pnts)
      {
         while(
               (*pnts) &&
               (
                  (strchr((const char *)lpszSpCharsSpcEol /* lpszSpChars */, *pnts)!=NULL) ||
                  ((*pnts == '\'') && (iEncoding == EC_ASCII)) // C_Apost
               )
              ) pnts++;
         if(*pnts) *(pntd++)=(*pnts++);
      }
      *pntd=Nul;
   }


   if(SUCCEEDED(retc)) pos = strlen(lpszStrBuf) - 1;

   if(bClearExactEntryChr && (pos >= 0) && SUCCEEDED(retc))
   {
      if(lpszStrBuf[pos] == EXACT_ENTRY_CHR) // '#'
         lpszStrBuf[pos--] = Nul;
   }

   if(bClearDoubleEntriesChr) while((pos>=0) && SUCCEEDED(retc))
   {
      if(lpszStrBuf[pos] == DOUBLE_ENTRIES_CHR) // '*'
         lpszStrBuf[pos--] = Nul;
      else break;
   }

// reikia VLZ ieðkant "Bach" kad nerastø "Bache"
   if(SUCCEEDED(retc)) TvStrLwr(lpszStrBuf, TV_IX_CTBL);

return(retc);
}

// -------------------------------------------------
HRESULT KpIndexEntryToCompareKpStr(KpChar *iazStrBuf, const KpChar *iazIndexEntry, bool bClearDoubleEntriesChr, bool bClearExactEntryChr)
{
HRESULT retc=S_OK;
int pos;

   if(((iazStrBuf == NULL) || (iazIndexEntry == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iazStrBuf != iazIndexEntry) TvKpStrCpy(iazStrBuf, iazIndexEntry);

   if(SUCCEEDED(retc)) retc = RemoveSpKpCharsSpc(iazStrBuf);

   if(SUCCEEDED(retc)) pos = TvKpStrLen(iazStrBuf) - 1;

   if(bClearExactEntryChr && (pos >= 0) && SUCCEEDED(retc))
   {
      if(iazStrBuf[pos] == EXACT_ENTRY_CHR) // '#'
         iazStrBuf[pos--] = C_Nul;
   }

   if(bClearDoubleEntriesChr) while((pos>=0) && SUCCEEDED(retc))
   {
      if(iazStrBuf[pos] == DOUBLE_ENTRIES_KPCHAR) // C_Bpoint // bullet // DOUBLE_ENTRIES_CHR) // '*'
         iazStrBuf[pos--] = C_Nul;
      else break;
   }

// reikia VLZ ieðkant "Bach" kad nerastø "Bache"
   if(SUCCEEDED(retc)) TvKpStrLwr(iazStrBuf);

return(retc);
}
