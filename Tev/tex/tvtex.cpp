// ==================================================
// tvtex.cpp
// TEX file I/O


// ================================================== definitions, static fields
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
#endif
#include <string>

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kperr.h"

#include "tvmain.h"

#include "tvtex.h"


// ================================================== methods of GlueDescriptor_tag
GlueDescriptor_tag::GlueDescriptor_tag(void)
{
   ResetFields();
}

void GlueDescriptor_tag::ResetFields(void)
{
   dSize=.0;
   iUnits=NoUnits;
   dPlusSize=.0;
   iPlusUnits=NoUnits;
   dMinusSize=.0;
   iMinusUnits=NoUnits;
   dToSize=.0;
   iToUnits=NoUnits;
   dSpreadSize=.0;
   iSpreadUnits=NoUnits;
}


// ================================================== methods of TexFieldDescriptor_tag
// --------------------------------------------------
TexFieldDescriptor_tag::TexFieldDescriptor_tag(TexFieldDescriptor_tag *pPField)
{
// TRACE("%snew %lx %s %d\n", TvSpcs(2*AllCnt++), this, __FILE__, __LINE__);

   pParentField=pPField;

   if(pParentField==NULL) iCtbl=iaTexTagCtbls[TX_TG_rm-TX_TG_FirstTag];
   else iCtbl=pParentField->iCtbl;

   iFldLenInd=TX_WIDE_FIELD;

   iParNum=0;
   bParEnd=TRUE;


   uiFont=(KpChar)TX_TG_rm;

   bMathField=FALSE;
   bTransparent=FALSE;

   m_bCtblSwitched=False;
   m_bFirstChar=True;
}


// --------------------------------------------------
TexFieldDescriptor_tag::~TexFieldDescriptor_tag(void)
{
   KP_DELETE(pParentField);

// TRACE("%sdel %lx %s %d\n", TvSpcs(--AllCnt*2), this, __FILE__, __LINE__);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetParField(TexFieldDescriptor_tag *pParField)
{
   pParentField=pParField;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetParField(TexFieldDescriptor_tag **ppParField)
{
   *ppParField=pParentField;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetFieldLength(int iFieldLengthIndicator)
{
HRESULT retc=S_OK;

   switch(iFieldLengthIndicator)
   {
   case TX_WIDE_FIELD:
   case TX_ONE_LETTER_FIELD:
   case TX_FORMULA_FIELD:
      iFldLenInd=iFieldLengthIndicator;
      break;
   default:
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
      break;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetFieldLength(int *piFieldLengthIndicator)
{
   *piFieldLengthIndicator=iFldLenInd;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetCodeTable(int *piCodeTable)
{
   *piCodeTable=iCtbl;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetFont(KpChar /* TX_TagIds */ *puiFntPtr)
{
   *puiFntPtr=uiFont;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetCodeTable(int iCodeTable)
{
HRESULT retc=S_OK;

   if((iCodeTable<0) || (iCodeTable>=KPT_Ctnum))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);
   else
      if(iCodeTable!=0) iCtbl=iCodeTable;

return(retc);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetFont(const KpChar /* TX_TagIds */ uiFnt)
{
HRESULT retc=S_OK;

   if(TvKpStrChr((KpChar *)iaFontSwitches, (KpChar)uiFnt)==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   else
   {
     uiFont=uiFnt;
     retc=SetCodeTable(iaTexTagCtbls[uiFnt-TX_TG_FirstTag]);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::ClearParNum(void)
{
   iParNum=0;
   bParEnd=TRUE;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetParNum(int *piParNumPtr, bool *pbParEndPtr)
{
   *piParNumPtr=iParNum;
   *pbParEndPtr=bParEnd;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::IncParNum(void)
{
   iParNum++;
   bParEnd=FALSE;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetParEnd(void)
{
   bParEnd=TRUE;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetMathFlag(const bool bMathFl)
{
   bMathField=bMathFl;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetMathFlag(bool *pbMathFl)

{
   *pbMathFl=bMathField;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::SetTransparent(const bool bTrnsprntFl)
{
   bTransparent=bTrnsprntFl;

return(S_OK);
}


// --------------------------------------------------
HRESULT TexFieldDescriptor_tag::GetTransparent(bool *pbTrnsprntFl)
{
   *pbTrnsprntFl=bTransparent;

return(S_OK);
}


// ================================================== private methods of TvTexFile
// --------------------------------------------------
HRESULT TvTexFile::CharEncode(KpChar *piOutChar, unsigned char cInChar)
{
HRESULT retc=S_OK;
int kpt_tbl;

   *piOutChar=C_Nul;

   if(SUCCEEDED(retc)) retc=GetCodeTable(&kpt_tbl);

   if(SUCCEEDED(retc))
   {
      retc=KptCharEncode(piOutChar, cInChar, kpt_tbl);
      if(retc==KP_E_UNKN_CHR)
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::CharDecode(unsigned char *pcOutChar, KpChar iInChar)
{
HRESULT retc=S_OK;
int kpt_tbl;

   if(SUCCEEDED(retc)) retc=GetCodeTable(&kpt_tbl);

   if(SUCCEEDED(retc))
   {
      retc=KptCharDecode(pcOutChar, iInChar, kpt_tbl);
//    if(retc==KP_E_UNKN_CHR) retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SkipChars(const unsigned char *lpszChars, bool *pbCharsSkipped)
{
HRESULT retc=S_OK;
unsigned char ch1;
bool reached=FALSE;
bool eof_fl=FALSE;

   if(pbCharsSkipped==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pbCharsSkipped=False;
      do
      {
         retc=GetChar(&ch1, FALSE);
         if(SUCCEEDED(retc))
         {
            reached=(TvStrChr(lpszChars, (KpChar)ch1)==NULL);
            if(reached) retc=UnGetChar(ch1);
            else *pbCharsSkipped=True;
         }
         else
         {
            if(retc==KP_E_EOF)
            {
               retc=S_OK;
               eof_fl=TRUE;
            }
         }

      } while((!reached) && (!eof_fl) && SUCCEEDED(retc));
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PushField
(
KpChar * /* piInch */,
bool * /* bCharPresent */,
const int iFieldLengthIndicator,
bool bMathFl
)
{
HRESULT retc=S_OK;
TexFieldDescriptor_tag *par_field;
KpChar /* TX_TagIds */ cur_fnt;
bool math_fld;
bool transpar_fl;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pCurrentField->IncParNum();

   if(SUCCEEDED(retc)) retc=pCurrentField->GetFont(&cur_fnt);

   if(SUCCEEDED(retc))
   {
      retc=GetMathFlag(&math_fld);
      if(bMathFl) math_fld=TRUE;
   }

   if(SUCCEEDED(retc))
   {
      retc=GetTransparent(&transpar_fl);
      if(math_fld) transpar_fl=TRUE;
   }

   if(SUCCEEDED(retc))
   {
      par_field = pCurrentField;
      KP_NEW(pCurrentField, TexFieldDescriptor_tag(par_field));
      if(pCurrentField == NULL) pCurrentField = par_field;
   }

   if(SUCCEEDED(retc)) retc=pCurrentField->SetTransparent(transpar_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetMathFlag(math_fld);
   if(SUCCEEDED(retc)) retc=pCurrentField->SetFont(cur_fnt);

   if(SUCCEEDED(retc)) retc=pCurrentField->SetFieldLength(iFieldLengthIndicator);

   if(SUCCEEDED(retc)) iGrpLev++;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PopField
(
KpChar *piInch,
bool *bCharPresent
)
{
HRESULT retc=S_OK;
TexFieldDescriptor_tag *par_field;
KpChar /* TX_TagIds */ cur_fnt;
KpChar /* TX_TagIds */ par_fnt;
// bool math_fl;
bool transpar_fl;

   if((pCurrentField == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pCurrentField->GetParField(&par_field);

   if(par_field==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

   *piInch=C_Nul;
   *bCharPresent=FALSE;
   if(SUCCEEDED(retc)) retc=par_field->GetFont(&par_fnt);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFont(&cur_fnt);
   if(SUCCEEDED(retc)) retc=par_field->GetTransparent(&transpar_fl);
// if(SUCCEEDED(retc)) retc=par_field->GetMathFlag(&math_fl); // !!! retc=GetMathFlag(&math_fl);
   if((par_fnt!=cur_fnt) && (!transpar_fl) && SUCCEEDED(retc))
   {
      *piInch=par_fnt;
      *bCharPresent=TRUE;
   }

   if(SUCCEEDED(retc)) retc=pCurrentField->SetParField(NULL);

   KP_DELETE(pCurrentField);

   if(SUCCEEDED(retc)) iGrpLev--;

   if(SUCCEEDED(retc)) retc=pCurrentField->SetParEnd();

   if(SUCCEEDED(retc)) retc=SetCurFont(par_fnt);

   iLastSwitch=par_fnt;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::TxTo7BitStr(unsigned char *lpszStr)
{
HRESULT retc=S_OK;
unsigned char str_buf[TV_TAG_LEN+1];
unsigned char *pnts, *pntd;
KpChar Ch2;
int ii;
bool math_fl = False;

   pnts=lpszStr;
   pntd=str_buf;

   if((pCurrentField == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc = pCurrentField->GetMathFlag(&math_fl);

   while(*pnts && SUCCEEDED(retc))
   {
      retc=CharEncode(&Ch2, *pnts++);
      if(SUCCEEDED(retc))
      {
         if(Ch2<KPT_FirstKptChar) *(pntd++)=(unsigned char)Ch2;
         else
         {
            if(plpszaTexSpecCharTags[Ch2]!=NULL)
            {
               ii=strlen((const char *)plpszaTexSpecCharTags[Ch2]) +2;
               if(pntd-str_buf+ii<=TV_TAG_LEN)
               {
//                *(pntd++)=TX_CH_FieldStart;
#if FALSE
                  switch(Ch2)
                  {
                     case C_QemSpc:
                     case C_Multipl:
                     case C_uparr:
                     case C_Sum:
                     case C_Bpoint:
                     case C_MinusMath:
// nereikia, jei jau matematiniam rezime !!!!
                        *(pntd++)=TX_CH_MathField; // TX_SP_MathField; // '$'
                        StrCpySqDiacr(pntd, plpszaTexSpecCharTags[Ch2]);
                        *(pntd++)=TX_CH_MathField; // TX_SP_MathField; // '$'
                        break;
                     default:
                        StrCpySqDiacr(pntd, plpszaTexSpecCharTags[Ch2]);
                        break;
                  }
#else
                  if((iaTexSpecCharTypes[Ch2] == TexMathChar) && (!math_fl)) *(pntd++)=TX_CH_MathField; // TX_SP_MathField;
                  else *(pntd++)=TX_CH_FieldStart;
                  StrCpySqDiacr(pntd, plpszaTexSpecCharTags[Ch2]);
                  while(*pntd) pntd++;
                  if((iaTexSpecCharTypes[Ch2] == TexMathChar) && (!math_fl)) *(pntd++)=TX_CH_MathField; // TX_SP_MathField;
                  else *(pntd++)=TX_CH_FieldEnd;
#endif
//                pntd+=ii; // squeezed diacrytics - length is shorter than ii

//                *(pntd++)=TX_CH_FieldEnd;
               }
               else
                  retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
            }
            else
            {
               (*pntd++)=pnts[-1];
               retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, lpszStr, FALSE, __FILE__, __LINE__, 0L);
            }
         }
      }
   }

   *pntd=Nul;

   strcpy((char *)lpszStr, (const char *)str_buf);

return(retc);
}


// ================================================== public methods of TvTexFile
// ================================================== file opening
// --------------------------------------------------
TvTexFile::TvTexFile
(
const unsigned char *lpszFileName,
const unsigned char *lpszMode,
int iNumberOfUserTags
)
{
HRESULT retc = S_OK;

// TRACE("%snew %lx %s %d\n", TvSpcs(2*AllCnt++), this, __FILE__, __LINE__);

   lhOpenResult=S_OK;

   iCharPos=0;
   lCharNum=0L;

   iUnGetCnt=C_Nul;
   iUnGetProcCnt=0;

   bCommentFlg=FALSE;

   iGrpLev=0;

   iNumOfUserTags=iNumberOfUserTags;
   if(iNumOfUserTags<0)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszMode, TRUE, __FILE__, __LINE__, 0L);

   lpszFName[0]=Nul;
   lpszFMode[0]=Nul;

   lpfFilePtr=NULL;

   iLastChar=C_Nul;
   iLastOutChar=C_Nul;
   iLastSwitch=(KpChar)TX_TG_ctbl_off;

   bLastWordInParFl=False;

   bTransparent=FALSE;

   m_bInsideTableRow=False;

   iCurFont=(KpChar)TX_TG_rm;
   iCurFontSav=/* (TX_TagIds) */ C_Nul;
   iCurCtbl=iaTexTagCtbls[TX_TG_rm-TX_TG_FirstTag];

   lpszProject[0]=Nul;
   lpszPublisher[0]=Nul;

   if(SUCCEEDED(lhOpenResult))
   {
      if(strlen((const char *)lpszFileName)<KP_MAX_FNAME_LEN) strcpy((char *)lpszFName, (const char *)lpszFileName);
      else lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszFileName, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(lhOpenResult))
   {
      if(strlen((const char *)lpszMode)<TV_TAG_LEN) strcpy((char *)lpszFMode, (const char *)lpszMode);
      else lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, lpszMode, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(lhOpenResult))
   {
      lpfFilePtr=fopen((const char *)lpszFName, (const char *)lpszFMode);
//    /*TRACE*/printf("%sfopen lpfFilePtr %lx %s %d\n", TvSpcs(2*FopenCnt++), lpfFilePtr, __FILE__, __LINE__);
      if(lpfFilePtr==NULL)
         lhOpenResult=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszFName, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEW(pCurrentField, TexFieldDescriptor_tag(NULL));
}


// --------------------------------------------------
TvTexFile::~TvTexFile()
{
   CloseFile(FALSE);

// TRACE("%sdel %lx %s %d\n", TvSpcs(--AllCnt*2), this, __FILE__, __LINE__);
}


// --------------------------------------------------
HRESULT TvTexFile::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT TvTexFile::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0;
TexFieldDescriptor_tag *p_ptr;

   if(lpfFilePtr!=NULL)
   {
      if(fclose(lpfFilePtr)!=0) if(SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, TRUE, __FILE__, __LINE__, 0L);
//    TRACE("%sclose %lx %s %d\n", TvSpcs(--FopenCnt*2), lpfFilePtr, __FILE__, __LINE__);
      lpfFilePtr=NULL;
   }
   else
   {
      retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, 0L);
   }

   if(pCurrentField!=NULL)
   {
//    KP_DELETE(pCurrentField);

// gal nereikia? Turetu rekursiskai issinaikinti, tik atbula tvarka
      do
      {
         retc0=pCurrentField->GetParField(&p_ptr);
         if(SUCCEEDED(retc0))
         {
            retc0=pCurrentField->SetParField(NULL);
            KP_DELETE(pCurrentField);
            pCurrentField = p_ptr;
         }
      } while((pCurrentField != NULL) && SUCCEEDED(retc0));
      if(SUCCEEDED(retc)) retc = retc0;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetCharPos(int *piCharPos)
{
HRESULT retc=S_OK;

   if(piCharPos==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *piCharPos=iCharPos;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetCodeTable(int *piCodeTable)
{
HRESULT retc=S_OK;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->GetCodeTable(piCodeTable);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetCurFont(KpChar /* TX_TagIds */ *puiFntPtr)
{
HRESULT retc=S_OK;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->GetFont(puiFntPtr);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SetCodeTable(int iCodeTable)
{
HRESULT retc=S_OK;

   if((iCodeTable<0) || (iCodeTable>=KPT_Ctnum))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->SetCodeTable(iCodeTable);

   if((iCurCtbl!=0) && SUCCEEDED(retc)) iCurCtbl=iCodeTable;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SetCurFont(const KpChar /* TX_TagIds */ uiFnt)
{
HRESULT retc=S_OK;

   if(TvKpStrChr(iaFontSwitches, uiFnt)==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->SetFont(uiFnt);

   if(SUCCEEDED(retc))
   {
      iCurFont=uiFnt;
      retc=SetCodeTable(iaTexTagCtbls[uiFnt-TX_TG_FirstTag]);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetGrpLev(int *piGrLevelPtr)
{
   *piGrLevelPtr=iGrpLev;

return(S_OK);
}


// --------------------------------------------------
HRESULT TvTexFile::GetParNum(int *piParNumPtr, bool *pbParEndPtr, const int iGrLevel)
{
HRESULT retc=S_OK;
int test_gr_lev;
int ii;
TexFieldDescriptor_tag *fld_ptr;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      test_gr_lev=iGrLevel;
      if(test_gr_lev<0) test_gr_lev=iGrpLev;

      fld_ptr=pCurrentField;
      for(ii=iGrpLev; ii>test_gr_lev && SUCCEEDED(retc); ii--)
      {
         if(SUCCEEDED(retc)) retc=fld_ptr->GetParField(&fld_ptr);
         if(fld_ptr==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
      retc=fld_ptr->GetParNum(piParNumPtr, pbParEndPtr);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetMathFlag(bool *pbMathFl)
{
HRESULT retc=S_OK;

   if(pCurrentField!=NULL)
      retc=pCurrentField->GetMathFlag(pbMathFl);
   else
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SetMathFlag(bool bMathFl)
{
HRESULT retc=S_OK;

   if(pCurrentField!=NULL)
      retc=pCurrentField->SetMathFlag(bMathFl);
   else
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetTransparent(bool *pbTrnsprntFl)
{
HRESULT retc=S_OK;

   if(pCurrentField!=NULL)
      retc=pCurrentField->GetTransparent(pbTrnsprntFl);
   else
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SetTransparent(bool bTrnsprntFl)
{
HRESULT retc=S_OK;

   if(pCurrentField!=NULL)
      retc=pCurrentField->SetTransparent(bTrnsprntFl);
   else
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   bTransparent=bTrnsprntFl;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetLastWordInParFl(bool *pbLastWInPFl)
{
HRESULT retc=S_OK;

   if(pbLastWInPFl!=NULL) *pbLastWInPFl=bLastWordInParFl;
   else
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

return(retc);
}

// --------------------------------------------------
HRESULT TvTexFile::SetLastWordInParFl(bool bLastWInPFl)
{
HRESULT retc=S_OK;

   bLastWordInParFl=bLastWInPFl;

return(retc);
}


// ================================================== low level input
// --------------------------------------------------
HRESULT TvTexFile::GetChar(unsigned char *pcInch, bool bCheckFeof)
{
HRESULT retc=S_OK;

   *pcInch=Nul;

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(iUnGetCnt>0) *pcInch=(unsigned char)caUnGetBuf[--iUnGetCnt];
      else
      {
         *pcInch=(unsigned char)getc(lpfFilePtr);
         if(feof(lpfFilePtr))
         {
            if(!bCheckFeof) retc=KP_E_EOF;
            else retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, null, TRUE, __FILE__, __LINE__, 0L);
         }
         if(ferror(lpfFilePtr))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, TRUE, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::UnGetChar(unsigned char cChar)
{
HRESULT retc=S_OK;

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(iUnGetCnt>=TX_UNGET_BUF_SIZ-1)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) caUnGetBuf[iUnGetCnt++]=cChar;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::UnGetStr(unsigned char *lpszStr)
{
HRESULT retc=S_OK;
unsigned char *pnts;

   if(lpszStr!=NULL)
   {
      pnts=lpszStr+strlen(lpszStr);

      while((pnts!=lpszStr) && SUCCEEDED(retc)) retc=UnGetChar(*(--pnts));
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SkipSpaces(bool *pbSpFl)
{
return(SkipChars(lpszSpaces, pbSpFl));
}


// --------------------------------------------------
HRESULT TvTexFile::SkipSpcEol(int *piEolCnt)
{
HRESULT retc=S_OK;
unsigned char ch1;
bool reached=FALSE;
bool eof_fl=FALSE;

// return(SkipChars(lpszSpcEol));

   *piEolCnt=0;

   do
   {
      retc=GetChar(&ch1, FALSE);
      if(SUCCEEDED(retc))
      {
         if(ch1==C_Lf) (*piEolCnt)++;

         reached=(TvStrChr(lpszSpcEol, (KpChar)ch1)==NULL);
         if(reached) retc=UnGetChar(ch1);
      }
      else
      {
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }
      }
   } while((!reached) && (!eof_fl) && SUCCEEDED(retc));

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetWord
(
unsigned char *lpszKeywrd,
KpChar *piDelimCh,
bool bOnlyAlpha
)
{
HRESULT retc=S_OK;
unsigned char ch1;
int keyidx=0;
KpChar Ch2;
bool reached=FALSE;
bool sp_fl;

   *piDelimCh=C_Nul;

   do
   {
      retc=GetChar(&ch1, FALSE);
      if(retc==KP_E_EOF)
      {
         ch1=Nul;
         Ch2=C_Nul;
         reached=TRUE;
         retc=S_OK;
      }
      else if(SUCCEEDED(retc)) retc=CharEncode(&Ch2, ch1);

      if((TvStrChr(lpszSpcEol, Ch2)!=NULL) && SUCCEEDED(retc))
      {
         if(ch1==Lf)
         {
            retc=UnGetChar(ch1);
            reached=TRUE;
         }
         ch1=Spc;
         Ch2=C_Spc;
      }

if((ch1=='\\') && (lpszKeywrd[-1]=='\\')) // !!!
ch1='\\';

      if((!reached) && SUCCEEDED(retc))
      {
// test word end
         if((!bOnlyAlpha) && (Ch2!=C_Spc) && (ch1!=TX_CH_FieldEnd) && (ch1!=TX_CH_KeywordStart))
         {
            if(keyidx >= TV_TAG_LEN-1)
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
            else lpszKeywrd[keyidx++]=ch1;
         }

         else if(
                  bOnlyAlpha &&
                  (
                     (
                        TvIsAlpha(Ch2) &&
                        (
                           TvIsAlpha((KpChar)(lpszKeywrd[0])) ||
                           (TvStrChr(lpszTxAccents123, (KpChar)lpszKeywrd[0])!=NULL) ||
                           (keyidx==0)
                        )
                     ) ||

                     (TvStrChr(lpszKwdChars, Ch2)!=NULL) ||
                     (
                  /*    (TvStrChr(lpszTxAccents123, Ch2)!=NULL) && */
                        (keyidx==0)
                     ) ||

                     (
                        (Ch2==C_Spc) &&
                        (keyidx<=2) &&
                        (
                           (TvStrChr(lpszTxAccents123, (KpChar)lpszKeywrd[0])!=NULL) ||
                           (keyidx==0)
                        ) &&
                        (
                           (lpszKeywrd[1]==C_Spc) ||
                           (keyidx<=1)
                        )
                     )
                  )
                )
         {
// input key text
            if((Ch2!=C_Spc) || (keyidx<=1))
            {
               if(keyidx >= TV_TAG_LEN-1)
                  retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
               else lpszKeywrd[keyidx++]=ch1;
            }

// add space to accents
            if((keyidx==1) && (TvStrChr(lpszTxAccents1, (KpChar)lpszKeywrd[0])!=NULL))
               lpszKeywrd[keyidx++]=Spc;

            if((lpszKeywrd[0]==Spc) && (keyidx>=1)) reached=TRUE;
            if((TvStrChr(lpszTxAccents12, (KpChar)lpszKeywrd[0])!=NULL) && (lpszKeywrd[1]==Spc) && (keyidx>=3)) reached=TRUE;
            if((TvStrChr(lpszTxAccents3, (KpChar)lpszKeywrd[0])!=NULL) && (lpszKeywrd[1]==Spc) && (keyidx>=4)) reached=TRUE;
         }

         else // else if(bOnlyAlpha && ...
         {
            reached=TRUE;
// skip delimition spaces
            if(Ch2==C_Spc) retc=SkipSpaces(&sp_fl);
            else retc=UnGetChar(ch1);
         }

      } // if((!reached) && SUCCEEDED(retc))

   } while(!reached && SUCCEEDED(retc));

   lpszKeywrd[keyidx]=Nul;
   *piDelimCh=Ch2;

   if(SUCCEEDED(retc))
      retc=TxTo7BitStr(lpszKeywrd);

return(retc);
}


// ================================================== high level input
// --------------------------------------------------
HRESULT TvTexFile::GetCharProc(KpChar *piInch, bool bCheckFeof, bool *pbEolFl, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
bool char_ready=FALSE;
unsigned char ch2;
bool ctrl_char;
KpChar cc;
unsigned char keywrd[TV_TAG_LEN+1+1];
bool eof_fl=FALSE;
int eol_cnt=0;
KpChar cch;
int fld_typ;
int gr_lev;
int grl;
unsigned char ch;
int *pnti;
bool math_fl;
int ii;

   *piInch=C_Nul;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   if(pbEolFl==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      *pbEolFl=False;

      do
      {
         if(iUnGetProcCnt!=0)
         {
            if(iUnGetProcCnt<0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

            iUnGetProcCnt--;
            cch=iaUnGetProcBuf[iUnGetProcCnt];

// !!! may return other character
// allready processed by first input
//          retc=ProcessKeyword(&cch, NULL, pUserObj);
            if(SUCCEEDED(retc))
            {
               *piInch=cch;
               if(cch==C_Lf) *pbEolFl=True;
               char_ready=True;
            }
         }

         else  // if(iUnGetProcCnt!=0)
         {
            eol_cnt=0;

            retc=GetChar(&ch2, FALSE);
#ifdef Debug
if(ch2=='\"')
ch2='\"';
#endif
            if(retc==KP_E_EOF)
            {
               retc=S_OK;
               eof_fl=TRUE;
            }

// eol's
            if(!eof_fl && SUCCEEDED(retc))
               if(TvStrChr(lpszEols, (KpChar)ch2)!=NULL)
               {
                  bCommentFlg=FALSE;
                  *pbEolFl=True;
               }

            if(!bCommentFlg)
            {
// ctrl. char.?
               ctrl_char=FALSE;
               if(!eof_fl && SUCCEEDED(retc))
                  ctrl_char=(TvStrChr(lpszTexCtrlChars, (KpChar)ch2)!=NULL);
// ctrl. char.
               if(ctrl_char && !eof_fl && SUCCEEDED(retc))
               {
                  switch(ch2)
                  {
// start of keyword '\\' ('%')
                  case TX_CH_KeywordStart:
// start of comment '%'
                  case TX_CH_CommentStart:
                     keywrd[0]=ch2;
                     retc=GetWord(keywrd+1, &cc, True);
                     if(cc==C_Nul) eof_fl=TRUE;

// user defined commands
#ifdef Debug
if(strcmp(keywrd, "\\TRTH")==C_Nul)
cch=C_Nul;
#endif
                     if(SUCCEEDED(retc))
                        retc=GetKwrdIndexSkipSpc(&ii, keywrd,
                             (const unsigned char **)plpszaUserTexTagTable, -1, True, True);

                     if(SUCCEEDED(retc)) //  (1.)
                     {
                        retc=pCurrentField->ClearParNum();
                        ii+=TX_FirstUserTagCode;
                        cch=(KpChar)ii;

// !!! may return other character
                        if(SUCCEEDED(retc)) retc=ProcessKeyword(&cch, NULL, pUserObj);

                        if((cch!=C_Nul) && SUCCEEDED(retc))
                        {
                           *piInch=cch;
                           char_ready=TRUE;

                           if(SUCCEEDED(retc)) switch(iaUserTexTagTypes[cch-TX_FirstUserTagCode])
                           {
                           case TexCtrl:
                           case TexGlue:
                           case TexDiacr:
                           case TexChar:
                           case TexMathChar:
                              retc=SkipSpcEol(&eol_cnt);
                              break;
                           default:
                              if(strchr(lpszSpcEol, cc)!=NULL) retc=UnGetChar(Spc);
                              break;
                           }
                        }
                     }
                     else if(retc==KP_E_KWD_NOT_FOUND)
                     {
                        retc=S_OK;
// main commands
                        retc=GetKwrdIndexSkipSpc(&ii, keywrd,
                                    (const unsigned char **)plpszaMainTexTagTable, -1, True, True);

                        if(SUCCEEDED(retc)) //  (2.)
                        {
                           retc=pCurrentField->ClearParNum();
                           ii+=TX_FirstMainTagCode;
                           cch=(KpChar)ii;

// !!! may return other character
                           if(SUCCEEDED(retc)) retc=ProcessKeyword(&cch, NULL, pUserObj);

                           if((cch!=C_Nul) && SUCCEEDED(retc))
                           {
                              *piInch=cch;
                              char_ready=TRUE;

                              if(SUCCEEDED(retc)) switch(iaMainTexTagTypes[cch-TX_FirstMainTagCode])
                              {
                              case TexCtrl:
                              case TexGlue:
                              case TexDiacr:
                              case TexChar:
                              case TexMathChar:
                                 retc=SkipSpcEol(&eol_cnt);
                                 break;
                              default:
                                 if(strchr(lpszSpcEol, cc)!=NULL) retc=UnGetChar(Spc);
                                 break;
                              }
                           }
                        }
                        else if(retc==KP_E_KWD_NOT_FOUND)
                        {
                           retc=S_OK;
// special TeX characters
                           retc=GetKwrdIndexSkipSpc((int *)&cch, keywrd, plpszaTexSpecCharTags, C_CharSize0, True, True);
                           if(SUCCEEDED(retc))
                           {
//                            if(cch>=0)
                              {
                                 *piInch=cch;
                                 char_ready=TRUE;
                                 retc=pCurrentField->IncParNum();
//if(cch==C_R_Acute)
//cch=C_R_Acute; // !!!
//if(cch==C_o_Acute)
//cch=C_o_Acute; // !!!
                                 if(SUCCEEDED(retc)) switch(iaTexSpecCharTypes[cch])
                                 {
                                 case TexCtrl:
                                 case TexGlue:
                                 case TexDiacr:
                                 case TexChar:
                                 case TexMathChar:
                                    retc=SkipSpcEol(&eol_cnt);
                                    break;
                                 default:
                                    if(strchr(lpszSpcEol, cc)!=NULL) retc=UnGetChar(Spc);
                                    break;
                                 }
                                 if(SUCCEEDED(retc)) retc=SkipSpcEol(&eol_cnt);
                              }
                           }
                           else
                           {
                              if(ch2==TX_CH_CommentStart)
                              {
                                 retc=S_OK;
                                 if(eol_cnt==0) bCommentFlg=TRUE;
                              }
                              else retc=KpErrorProc.OutputErrorMessage(TV_E_UNKN_TAG, keywrd, TRUE, __FILE__, __LINE__, 0L);
                           }

                        } // if(SUCCEEDED(retc)) (2.)

                     } // if(SUCCEEDED(retc)) (1.)

                     if(char_ready && SUCCEEDED(retc))
                     {
                        if(eol_cnt>=2)
                        {
                           if(SUCCEEDED(retc)) retc=UnGetChar(Lf);
                           if(SUCCEEDED(retc)) retc=UnGetChar(Lf);
                        }

// search for aliases
                        retc=pCurrentField->GetMathFlag(&math_fl);

                        if(SUCCEEDED(retc))
                        {
                           pnti=iaUserTexTagVariations;
                           while(*pnti)
                           {
                              if(
                                 ((*pnti)==(*piInch)) &&
                                 (
                                    ((*(pnti+2)==TX_FORMULA_FIELD)==math_fl) ||
                                    (*(pnti+2)==TX_BOTH_TYPES)
                                 )
                                )
                              {
                                 (*piInch)=(KpChar)(*(pnti+1));
                                 break;
                              }
                              pnti+=3;
                           }
                        }

                        if((*pnti==0) && SUCCEEDED(retc))
                        {
                           pnti=iaTexTagVariations;
                           while(*pnti)
                           {
                              if(
                                 ((*pnti)==(*piInch)) &&
                                 (
                                    ((*(pnti+2)==TX_FORMULA_FIELD)==math_fl) ||
                                    (*(pnti+2)==TX_BOTH_TYPES)
                                 )
                                )
                              {
                                 (*piInch)=(KpChar)(*(pnti+1));
                                 break;
                              }
                              pnti+=3;
                           }
                        }

                     }

                     break;
// opening parenthese '{'
                  case TX_CH_FieldStart:
                     retc=PushField(piInch, &char_ready, TX_WIDE_FIELD, FALSE);
                     if(char_ready && SUCCEEDED(retc))
                     {
                        retc=ProcessKeyword(piInch, NULL, pUserObj);
                        if((*piInch!=C_Nul) && SUCCEEDED(retc)) retc=UnGetCharProc(*piInch);
                     }
                     char_ready=TRUE;
                     *piInch=(KpChar)TX_SP_FieldStart;
                     break;

// closing parenthese '}'
                  case TX_CH_FieldEnd:
                     retc=PopField(piInch, &char_ready);
                     if(char_ready && SUCCEEDED(retc))
                     {
                        retc=ProcessKeyword(piInch, NULL, pUserObj);
                        if((*piInch!=C_Nul) && SUCCEEDED(retc)) retc=UnGetCharProc(*piInch);
                     }
                     char_ready=TRUE;
                     *piInch=(KpChar)TX_SP_FieldEnd;
                     break;

// formula delimiter '$'
                  case TX_CH_MathField:
                     retc=pCurrentField->GetFieldLength(&fld_typ);
                     if(SUCCEEDED(retc))
                     {
                        if(fld_typ!=TX_FORMULA_FIELD)
                        {
                           retc=PushField(piInch, &char_ready, TX_FORMULA_FIELD, TRUE);
//                         if(SUCCEEDED(retc)) retc=ProcessKeyword(piInch, NULL, pUserObj);
//                         if((*piInch!=C_Nul) && SUCCEEDED(retc)) retc=UnGetCharProc(TX_TG_rm);
                        }
                        else
                           retc=PopField(piInch, &char_ready);

                        if(char_ready && SUCCEEDED(retc))
                        {
                           retc=ProcessKeyword(piInch, NULL, pUserObj);
                           if((*piInch!=C_Nul) && SUCCEEDED(retc)) retc=UnGetCharProc(*piInch);
                           char_ready=FALSE;
                        }
                     }

                     if(SUCCEEDED(retc))
                     {
                        *piInch=(KpChar)TX_SP_MathField;
                        char_ready=TRUE;
                     }

                     break;

                  case TX_CH_Hash:
                     *piInch=(KpChar)TX_SP_Hash;
                     char_ready=TRUE;
                     break;

                  case TX_CH_Amp:
                     *piInch=(KpChar)TX_SP_Amp;
                     char_ready=TRUE;
                     break;

                  case TX_CH_UnderL:
                     *piInch=(KpChar)TX_SP_UnderL;
                     char_ready=TRUE;
                     break;

                  case TX_CH_Eq:
                     *piInch=(KpChar)TX_SP_Eq;
                     char_ready=TRUE;
                     break;

                  case TX_CH_Apost:
                     *piInch=(KpChar)TX_SP_Apost;
                     char_ready=TRUE;
                     break;

                  case TX_CH_Quot:
                     if(m_bInsideTableRow) *piInch=C_Ht; // '\"'   // table columns splitter
                     else *piInch=(KpChar)TX_SP_Quot;
                     char_ready=TRUE;
                     break;

                  case TX_CH_Grave:
                     *piInch=(KpChar)TX_SP_Grave;
                     char_ready=TRUE;
                     break;

                  case TX_CH_At:
                     *piInch=(KpChar)TX_SP_At;
                     char_ready=TRUE;
                     break;

                  case TX_CH_Circ:
                     *piInch=(KpChar)TX_SP_Circ;
                     char_ready=TRUE;
                     break;

                  default:
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
                     break;
                  } // switch(ch2)

               } // if(ctrl_char && !eof_fl && SUCCEEDED(retc))

// spaces
               if(!ctrl_char && !char_ready && !eof_fl && SUCCEEDED(retc))
               {
                  if(TvStrChr(lpszSpcEol, (KpChar)ch2)!=NULL)
                  {
                     retc=SkipSpcEol(&eol_cnt);
                     if(SUCCEEDED(retc))
                     {
                        if((eol_cnt>1) || ((ch2==Lf) && (eol_cnt>0))) *piInch=C_Lf;
                        else *piInch=C_Spc;
                        char_ready=TRUE;
                        retc=pCurrentField->SetParEnd();
                     }
                  }
               }

               if(!ctrl_char && !char_ready && !eof_fl && SUCCEEDED(retc))
               {
// ---------------------------------
// '~', "--", "---", ",,", "``", "&" etc.

                  if(SUCCEEDED(retc)) switch(ch2)
                  {
                  case '-':
                     retc=GetChar(&ch2, FALSE);
                     if(SUCCEEDED(retc))
                     {
                        if(ch2=='-')
                        {
                           retc=GetChar(&ch2, FALSE);
                           if(SUCCEEDED(retc))
                           {
                              if(ch2=='-')
                              {
                                 *piInch=C_EmDash; // "---"
                              }
                              else
                              {
                                 *piInch=C_EnDash; // "--"
                                 retc=UnGetChar(ch2);
                              }
                           }
                           else
                           {
                              if(retc==KP_E_EOF)
                              {
                                 *piInch=C_EnDash; // "--"
                                 retc=S_OK;
                              }
                           }
                        }
                        else
                        {
                           *piInch=C_Dash; // '-'
                           retc=UnGetChar(ch2);
                        }
                     }
                     else
                     {
                        if(retc==KP_E_EOF)
                        {
                           *piInch=C_Dash; // '-'
                           retc=S_OK;
                        }
                     }
                     break;

                  case ',':
                     retc=GetChar(&ch2, FALSE);
                     if(SUCCEEDED(retc))
                     {
                        if(ch2==',')
                        {
                           *piInch=C_LBquote; // ",,"
                        }
                        else
                        {
                           *piInch=C_Comma; // ','
                           retc=UnGetChar(ch2);
                        }
                     }
                     else
                     {
                        if(retc==KP_E_EOF)
                        {
                           *piInch=C_Comma; // ','
                           retc=S_OK;
                        }
                     }
                     break;

                  case '`':
                     retc=GetChar(&ch2, FALSE);
                     if(SUCCEEDED(retc))
                     {
                        if(ch2=='`')
                        {
                           *piInch=C_Rquote; // "``"
                        }
                        else
                        {
                           *piInch=C_Grave; // '`'
                           retc=UnGetChar(ch2);
                        }
                     }
                     else
                     {
                        if(retc==KP_E_EOF)
                        {
                           *piInch=C_Grave; // '`'
                           retc=S_OK;
                        }
                     }
                     break;

// ordinary char.
                  default:
                     retc=CharEncode((KpChar*)piInch, ch2);
                     break;
                  }

// !!! may return other character
                  if(SUCCEEDED(retc)) retc=ProcessKeyword(piInch, NULL, pUserObj);

                  if(SUCCEEDED(retc))
                  {
                     char_ready=TRUE;
                     retc=pCurrentField->IncParNum();
                  }
               }

            } // if(!bCommentFlg)

         } // else // if(iUnGetProcCnt!=0)

      } while(!char_ready && !eof_fl && SUCCEEDED(retc));
   }

//----------------------------------------
   if(eof_fl && SUCCEEDED(retc))
   {
      if(!bCheckFeof) retc=KP_E_EOF;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, null, TRUE, __FILE__, __LINE__, 0L);
   }

//---------------------------------------- process some characters
   if(char_ready && SUCCEEDED(retc))
   {
      switch(*piInch)
      {
      case TX_TG_def:
      case TX_TG_edef:
         retc=GetGrpLev(&gr_lev);
         grl=gr_lev;

         if(SUCCEEDED(retc)) do
         {
            retc=GetChar(&ch, bCheckFeof);
            if(SUCCEEDED(retc)) switch(ch)
            {
            case TX_CH_FieldStart: grl++; break;
            case TX_CH_FieldEnd: grl--; break;
            }
         } while((grl==gr_lev) && SUCCEEDED(retc));

         if(SUCCEEDED(retc))
         {
            if(grl>gr_lev)
            {
               do
               {
                  retc=GetChar(&ch, bCheckFeof);
                  if(SUCCEEDED(retc)) switch(ch)
                  {
                  case TX_CH_FieldStart: grl++; break;
                  case TX_CH_FieldEnd: grl--; break;
                  }
               } while((grl>gr_lev) && SUCCEEDED(retc));
            }
            else retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         }

         *piInch=(KpChar)TX_TG_nul;
         break;

      } // switch(*piInch)

   } // if(char_ready && SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
// Here is not necessary to decrement iParNum or set bParEnd - status is left the same
// and next GetCharProc() does not change it.
HRESULT TvTexFile::UnGetCharProc(KpChar iChar)
{
HRESULT retc=S_OK;

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(iUnGetProcCnt>=TX_UNGET_BUF_SIZ)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      iaUnGetProcBuf[iUnGetProcCnt]=iChar;
      iUnGetProcCnt++;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetCharProcSkipSpc(KpChar *piInch, bool bCheckFeof, bool *pbEolFl, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
bool eol_fl;

   *pbEolFl=False;
   do
   {
      retc=GetCharProc(piInch, bCheckFeof, &eol_fl, pUserObj);
      *pbEolFl|=eol_fl;
   }
   while((*piInch==C_Spc) && SUCCEEDED(retc));

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetStrProc(unsigned char *lpszStrBuf, int iBufSize, int iEndTag, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
bool reached;
int cur_gr_lev;
int gr_lev;
// int cur_par_num;
// int par_num;
int str_ix=0;
KpChar in_ch;
bool eol_fl;
bool font_sw;

   reached=FALSE;
   retc=GetGrpLev(&cur_gr_lev);
// if(SUCCEEDED(retc))
//    retc=GetParNum(&cur_par_num, &par_end, -1);

   if(SUCCEEDED(retc)) do{

      retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
      if(SUCCEEDED(retc))
         retc=GetGrpLev(&gr_lev);
//    if(SUCCEEDED(retc))
//       retc=GetParNum(&par_num, &par_end, -1);

      if(SUCCEEDED(retc))
      {
// eof
         if(in_ch==C_Nul) reached=TRUE;

         if(eol_fl && (iEndTag==TX_ARG_END_LINE)) reached=TRUE;

         if(in_ch==iEndTag)
         {
            reached=TRUE;
            retc=UnGetCharProc(in_ch);
         }

// next command
         if(
            (
               ((in_ch>=TX_FirstUserTagCode) && (in_ch<TX_FirstUserTagCode+iNumOfUserTags)) ||
               ((in_ch>=TX_TG_FirstTag) && (in_ch<TX_TG_LastTag))
            ) &&
            (!reached) &&
            SUCCEEDED(retc)
           )
         {
            font_sw=(TvKpStrChr(iaFontSwitches, in_ch)!=NULL);

            if((iEndTag==TX_ARG_END_TAG) && (!font_sw))
            {
               reached=TRUE;
               retc=UnGetCharProc(in_ch);
            }

            if(!reached)
            {
               if((gr_lev>cur_gr_lev) || (iEndTag!=TX_ARG_END_CUR_LEV_TAG) || font_sw) retc=ProcessKeyword(&in_ch, NULL, pUserObj);
               else
               {
                  reached=TRUE;
                  retc=UnGetCharProc(in_ch);
               }
            }
         }

// end of current group
         if((gr_lev<cur_gr_lev) && (!reached) && SUCCEEDED(retc))
         {
            reached=TRUE;
            retc=UnGetCharProc(in_ch);
         }

// end of current parameter
//       if((gr_lev==cur_gr_lev) && (par_num>cur_par_num) && SUCCEEDED(retc))
//       {
//          reached=TRUE;
//          retc=UnGetCharProc(in_ch);
//         }

// put char. to buffer
         if((!reached) && (in_ch!=C_Nul) && (in_ch!=TX_SP_FieldStart) && (in_ch!=TX_SP_FieldEnd))
         {
            if(str_ix>=iBufSize-1)
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
            else
               lpszStrBuf[str_ix++]=(unsigned char)in_ch;
         }
      }
   } while(!reached && SUCCEEDED(retc));

   lpszStrBuf[str_ix]=Nul;
   if(SUCCEEDED(retc))
      retc=CutTrailSpcs(lpszStrBuf);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetKpStrProc(KpChar *lpiazStrBuf, int iBufSize, KpChar iEndTag, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
bool reached;
int cur_gr_lev;
int gr_lev;
// int cur_par_num;
// int par_num;
int str_ix=0;
KpChar in_ch;
bool eol_fl;
bool font_sw;

   reached=FALSE;
   retc=GetGrpLev(&cur_gr_lev);
// if(SUCCEEDED(retc))
//    retc=GetParNum(&cur_par_num, &par_end, -1);

   if(SUCCEEDED(retc)) do{

      retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
      if(SUCCEEDED(retc))
         retc=GetGrpLev(&gr_lev);
//    if(SUCCEEDED(retc))
//       retc=GetParNum(&par_num, &par_end, -1);

      if(SUCCEEDED(retc))
      {
// eof
         if(in_ch==C_Nul) reached=TRUE;

         if(eol_fl && (iEndTag==TX_ARG_END_LINE)) reached=TRUE;

         if(in_ch==iEndTag)
         {
            reached=TRUE;
            retc=UnGetCharProc(in_ch);
         }

// next command
         if(
            (
               ((in_ch>=TX_FirstUserTagCode) && (in_ch<TX_FirstUserTagCode+iNumOfUserTags)) ||
               ((in_ch>=TX_TG_FirstTag) && (in_ch<TX_TG_LastTag))
            ) &&
            (!reached) &&
            SUCCEEDED(retc)
           )
         {
            font_sw=(TvKpStrChr(iaFontSwitches, in_ch)!=NULL);

            if((iEndTag==TX_ARG_END_TAG) && (!font_sw))
            {
               reached=TRUE;
               retc=UnGetCharProc(in_ch);
            }

            if(!reached)
            {
               if((gr_lev>cur_gr_lev) || (iEndTag!=TX_ARG_END_CUR_LEV_TAG) || font_sw)
                  retc=ProcessKeyword(&in_ch, NULL, pUserObj);
               else
               {
                  reached=TRUE;
                  retc=UnGetCharProc(in_ch);
               }
            }
         }

// end of current group
         if((gr_lev<cur_gr_lev) && (!reached) && SUCCEEDED(retc))
         {
            reached=TRUE;
            retc=UnGetCharProc(in_ch);
         }

// end of current parameter
//       if((gr_lev==cur_gr_lev) && (par_num>cur_par_num) && SUCCEEDED(retc))
//       {
//          reached=TRUE;
//          retc=UnGetCharProc(in_ch);
//         }

// put char. to buffer
         if((!reached) && (in_ch!=C_Nul) && (in_ch!=TX_SP_FieldStart) && (in_ch!=TX_SP_FieldEnd))
         {
            if(str_ix>=iBufSize-1)
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
            else
               lpiazStrBuf[str_ix++]=in_ch;
         }
      }
   } while(!reached && SUCCEEDED(retc));

   lpiazStrBuf[str_ix]=C_Nul;
// if(SUCCEEDED(retc)) retc=CutTrailSpcs(lpszStrBuf);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::ProcessKeyword(KpChar *piInChar, KpChar **ppStrBuf, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
int arg_typ;
KpChar in_ch;
// KpChar in_ch_1;
bool eol_fl;
// bool eol_fl_1;
GlueDescriptor_tag glue;
unsigned char *in_str=NULL;
unsigned char c_ch;
// int par_num;
// bool par_end;
// int gr_lev;

//?? retc=ResetCommentFlag();

#ifdef Debug
if(*piInChar==TX_TG_hoffset)
*piInChar=(KpChar)TX_TG_hoffset;
#endif

   KP_NEWA(in_str, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

   arg_typ=0;
   if((*piInChar>=TX_TG_FirstTag) && (*piInChar<TX_TG_LastTag) && SUCCEEDED(retc))
      arg_typ=iaMainTexTagArgs[*piInChar-TX_TG_FirstTag];
   if((*piInChar>=TX_FirstUserTagCode) && (*piInChar<TX_FirstUserTagCode+iNumOfUserTags) && SUCCEEDED(retc))
      arg_typ=iaUserTexTagArgs[*piInChar-TX_FirstUserTagCode];

   if(((arg_typ==TX_ARG_TXT) || (arg_typ==TX_ARG_NUM)|| (arg_typ==TX_ARG_NUM_GLUE)) && SUCCEEDED(retc))
   {
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, FALSE, &eol_fl, pUserObj);
      if((in_ch!=TX_SP_Eq) && SUCCEEDED(retc)) // '=' 9008
      {
// !!! \pvacor-24pt is info310.tex
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         retc=UnGetCharProc(in_ch);
      }
   }

   if((arg_typ==TX_ARG_REG) && SUCCEEDED(retc))
   {
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      do retc=GetChar(&c_ch, True);
      while(isdigit(c_ch) && SUCCEEDED(retc));

      if(SUCCEEDED(retc)) retc=UnGetChar(c_ch);
   }

   if(((arg_typ==TX_ARG_VAR) || (arg_typ==TX_ARG_REG)) && SUCCEEDED(retc))
   {
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, FALSE, &eol_fl, pUserObj);
      if(SUCCEEDED(retc))
         if(in_ch==C_Eq) // '='
         {
// !!! remember assignments
// //       retc=GetStrProc(in_str, KP_MAX_FILE_LIN_LEN, TX_ARG_END_LINE, NULL);
//          do retc=GetChar(&c_ch, True);
//          while((c_ch!=Lf) && SUCCEEDED(retc));
         }
         else
         {
            if(eol_fl) retc=UnGetCharProc(C_Lf);
            else retc=UnGetCharProc(in_ch);
         }
   }

   if((TvKpStrChr(iaFontSwitches, *piInChar)!=NULL) && SUCCEEDED(retc))
   {
      retc=SetCurFont(*piInChar);
      *piInChar=(KpChar)TX_TG_nul;
   }

// processing of user tags
   if((pUserObj!=NULL) && SUCCEEDED(retc)) retc=pUserObj->ProcessKeyword(piInChar, ppStrBuf);

   if(SUCCEEDED(retc)) switch(*piInChar)
   {
   case TX_TG_Project:
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetStrProc(lpszProject, TV_TAG_LEN, TX_ARG_END_LINE, NULL);
      *piInChar=(KpChar)TX_TG_nul;
      break;

   case TX_TG_Publisher:
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetStrProc(lpszPublisher, TV_TAG_LEN, TX_ARG_END_LINE, NULL);
      *piInChar=(KpChar)TX_TG_nul;
      break;

   case TX_TG_Stage:
   case TX_TG_Pages:
   case TX_TG_TID:
   case TX_TG_typesetterid:
   case TX_TG_paperid:
   case TX_TG_statusno:

   case TX_TG_input:

   case TX_TG_catcode:

   case TX_TG_pageno:
   case TX_TG_firstpage:
   case TX_TG_lastpage:
   case TX_TG_switch:

   case TX_TG_insertplot:
   case TX_TG_position:
   case TX_TG_bottom:
   case TX_TG_pheight:
   case TX_TG_pwidth:
   case TX_TG_pprocent:
   case TX_TG_ptype:
// case TX_TG_pname:
// case TX_TG_ptext:
   case TX_TG_pfile:
   case TX_TG_pcorrections:
   case TX_TG_phcor:
   case TX_TG_pvacor:
   case TX_TG_pvbcor:
   case TX_TG_pvccor:
// case TX_TG_endinsertplot:

   case TX_TG_None:
   case TX_TG_UNI:
   case TX_TG_HPX:
   case TX_TG_PCZ:
   case TX_TG_PS:

   case TX_TG_BTH:
   case TX_TG_tposition:
   case TX_TG_tcorrections:
   case TX_TG_ETH:
   case TX_TG_BTF:
   case TX_TG_LC:
   case TX_TG_CC:
   case TX_TG_RC:
   case TX_TG_ETF:
   case TX_TG_BrightHorLine:
   case TX_TG_ThinHorLine:
// case TX_TG_CVB:
// case TX_TG_NextColumn:
// case TX_TG_ER:
   case TX_TG_NVS:
   case TX_TG_EOT:

   case TX_TG_after:
   case TX_TG_top:
   case TX_TG_mid:
   case TX_TG_there:
// case TX_TG_bottom:
   case TX_TG_full:
   case TX_TG_bpage:
   case TX_TG_mpage:
   case TX_TG_epage:
   case TX_TG_tvacor:
   case TX_TG_tvbcor:
   case TX_TG_tvccor:
   case TX_TG_tvdcor:

   case TX_TG_tencyr:
   case TX_TG_tencyi:
   case TX_TG_Longe:
   case TX_TG_Longm:

   case TX_TG_medskip:

   case TX_TG_looseness:

      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetStrProc(in_str, KP_MAX_FILE_LIN_LEN, TX_ARG_END_TAG, NULL);
      *piInChar=(KpChar)TX_TG_nul;
      break;

   case TX_TG_parindent:
   case TX_TG_rightskip:
   case TX_TG_leftskip:
   case TX_TG_hskip:
   case TX_TG_vskip:

   case TX_TG_hsize:
// case TX_TG_vsize:

// case TX_TG_baselineskip:
// case TX_TG_lineskip:
// case TX_TG_lineskiplimit:

   case TX_TG_raise:

   case TX_TG_hbox:

   case TX_TG_hoffset:
   case TX_TG_voffset:
   case TX_TG_prulesize:

   case TX_TG_hangindent:
   case TX_TG_hangafter:

   case TX_TG_kern:

   case TX_TG_baselineskip:

   case TX_TG_TRTH:
   case TX_TG_desiredwidth:

      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetGlue(&glue);
      *piInChar=(KpChar)TX_TG_nul;
      break;

#if FALSE
   case TX_TG_TRTH:

      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);

//    if(SUCCEEDED(retc)) do retc=GetCharProc(&in_ch_1, FALSE, &eol_fl_1, pUserObj);
//    while((c_ch!=C_Eq) && SUCCEEDED(retc)); // '='

      if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch_1, FALSE, &eol_fl_1, pUserObj);
      if((in_ch_1!=C_Eq) && SUCCEEDED(retc)) // '='
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=GetGlue(&glue);
      *piInChar=(KpChar)TX_TG_nul;
      break;
#endif

   case TX_TG_newdimen:

      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
//    if(SUCCEEDED(retc)) retc=GetStrProc(in_str, KP_MAX_FILE_LIN_LEN, TX_ARG_END_LINE, NULL);
      if(SUCCEEDED(retc)) do retc=GetChar(&c_ch, True);
      while((c_ch!=Lf) && SUCCEEDED(retc));

      *piInChar=(KpChar)TX_TG_nul;
      break;

   case TX_TG_cr:
   case TX_TG_par:
   case TX_TG_break:
      *piInChar=C_Lf;
      break;

   case TX_TG_forc_sp:
      *piInChar=C_Spc;
      break;

// -----------------------------
// paprasti simboliai cia neateina ??? !!!
   case TX_CH_At:  // '@'   // indent supresser
// !!! *piInChar=C_Nul;
      *piInChar=C_Spc;
      break;

   case TX_CH_Hash:  // '#'
// !!! *piInChar=C_Nul;
      *piInChar=C_Spc;
      break;

   case TX_CH_UnderL:  // '_' // lower index
      *piInChar=C_Underl;
      break;

   case TX_CH_Circ:  // '^' // upper index
      *piInChar=C_Circ;
      break;

   case TX_CH_NBSP: // '~'
      *piInChar=C_NBSP;
      break;
// -----------------------------

   case TX_TG_newbox:
   case TX_TG_let:
   case TX_TG_font:
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
//    if(SUCCEEDED(retc)) retc=GetStrProc(in_str, KP_MAX_FILE_LIN_LEN, TX_ARG_END_LINE, NULL);
      if(SUCCEEDED(retc)) do retc=GetChar(&c_ch, True);
      while((c_ch!=Lf) && SUCCEEDED(retc));
      *piInChar=(KpChar)TX_TG_nul;
      break;

   case TX_TG_char:
      if(ppStrBuf!=NULL)
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) retc=GetWord(in_str, &in_ch, False);
      if(SUCCEEDED(retc)) switch(in_str[0])
      {
      case '\"':  // hex number
         if(!TvIsHexNum(in_str+1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) sscanf((const char *)(in_str+1), "%x", piInChar);
         break;
      case '\'':  // octal number
         if(!TvIsOctNum(in_str+1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) sscanf((const char *)(in_str+1), "%o", piInChar);
         break;
      default:
         if(!TvIsNumber(in_str))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) sscanf((const char *)in_str, "%d", piInChar);
         break;
      }
      break;

   case TX_TG_begintable:
      retc=UnGetCharProc(C_Lf);
      m_bInsideTableRow=False;
      break;

   case TX_TG_B:
      m_bInsideTableRow=True;

#if FALSE // atstatyt, jei padarysiu, kad GetParNum() veiktu ir su pavieniais simboliais, ne tik su {} fields !!!
      retc=GetGrpLev(&gr_lev);
      if(SUCCEEDED(retc)) do
      {
         if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
         if(SUCCEEDED(retc)) retc=GetParNum(&par_num, &par_end, gr_lev);
      } while((!par_end) && SUCCEEDED(retc));
      if(SUCCEEDED(retc)) retc=UnGetCharProc(in_ch);
#else
      if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
      if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
#endif
      break;

// -----------------------------
// paprasti simboliai cia neateina ??? !!!
   case TX_CH_Quot: // '"'   // table columns splitter
      if(!m_bInsideTableRow) break;
   case TX_CH_Amp:  // '&'   // table columns splitter
      *piInChar=C_Ht;
      break;
// -----------------------------

   case TX_TG_E:
#if FALSE // atstatyt, jei padarysiu, kad GetParNum() veiktu ir su pavieniais simboliais, ne tik su {} fields !!!
      retc=GetGrpLev(&gr_lev);
      if(SUCCEEDED(retc)) do
      {
         if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
         if(SUCCEEDED(retc)) retc=GetParNum(&par_num, &par_end, gr_lev);
      } while((!par_end) && SUCCEEDED(retc));
      if(SUCCEEDED(retc)) retc=UnGetCharProc(in_ch);
#else
      if(SUCCEEDED(retc)) retc=GetCharProc(&in_ch, False, &eol_fl, pUserObj);
#endif

      retc=UnGetCharProc(C_Lf);
      m_bInsideTableRow=False;

      break;
   }

   KP_DELETEA(in_str);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::ResetCommentFlag(void)
{
   bCommentFlg=FALSE;

return(S_OK);
}


// --------------------------------------------------
HRESULT TvTexFile::GetNumArg(long *lArgPtr)
{
HRESULT retc;
unsigned char str_buf[TV_TAG_LEN+1];

   retc=GetTextArg(str_buf, TV_TAG_LEN);
   if(SUCCEEDED(retc)) sscanf((const char *)str_buf, "%ld", lArgPtr);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetTextArg(unsigned char *lpszOutStr, int iBufLen)
{
HRESULT retc=S_OK;
unsigned char in_ch;
bool endfl;
unsigned char *pntd;

// retc=GetChar(&in_ch, True);
// if(SUCCEEDED(retc))
//    if(in_ch!='=')
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

   endfl=False;
   pntd=lpszOutStr;
   if(SUCCEEDED(retc)) do
   {
      retc=GetChar(&in_ch, True);
      if(SUCCEEDED(retc))
      {
         if(
            (TvStrChr(lpszSpcEol, (KpChar)in_ch)==NULL) &&
            (TvStrChr(lpszTexCtrlChars, (KpChar)in_ch)==NULL) &&
            (pntd-lpszOutStr<iBufLen-1)
           )
            (*pntd++)=in_ch;
         else
         {
            endfl=True;
            retc=UnGetChar(in_ch);
            if(pntd-lpszOutStr>=iBufLen-1)
            {
               KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc)) retc=TV_E_TAG_OVERFL;
            }
         }
      }
   } while((!endfl) && SUCCEEDED(retc));

   if(pntd-lpszOutStr<iBufLen) *pntd=C_Nul;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetNumPar(long *plValue, bool bCheckFeof, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
KpChar in_ch;
unsigned char num_buf[TV_TAG_LEN+1];
int num_buf_ix=0;
int cur_par_num;
int par_num;
bool par_end;
int gr_lev;
bool efl;
bool first_ch=True;
bool eol_fl;
bool unget_fl;

   *plValue=0L;

   retc=GetGrpLev(&gr_lev);
   if(SUCCEEDED(retc)) retc=GetParNum(&cur_par_num, &par_end, gr_lev);

   if(SUCCEEDED(retc)) do
   {
      do
      {
         if(first_ch) retc=GetCharProcSkipSpc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
         else retc=GetCharProc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
         first_ch=False;

         if(SUCCEEDED(retc)) retc=GetParNum(&par_num, &par_end, gr_lev);
         efl=(par_num!=cur_par_num+1);
         if((!TvIsDigit((const KpChar)in_ch)) && (in_ch!=TX_SP_FieldEnd) && (in_ch!=TX_SP_FieldStart)) efl=True;
         unget_fl=efl;
         if(!efl) if(par_end)
         {
            efl=True;
            unget_fl=(in_ch!=TX_SP_FieldEnd);
         }
      } while(((in_ch==TX_SP_FieldEnd) || (in_ch==TX_SP_FieldStart)) && (!efl) && SUCCEEDED(retc));

      if(!efl)
      {
         if((num_buf_ix<TV_TAG_LEN) && (in_ch!=TX_SP_FieldEnd) && (in_ch!=TX_SP_FieldStart))
            num_buf[num_buf_ix++]=(unsigned char)in_ch;
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
         if(unget_fl && SUCCEEDED(retc))
            retc=UnGetCharProc(in_ch);

   } while((!efl) && SUCCEEDED(retc));

   if(SUCCEEDED(retc) || (retc==KP_E_EOF))
   {
      num_buf[num_buf_ix]=Nul;
      sscanf((char *)num_buf, "%ld", plValue);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetTextPar(unsigned char *lpszChBuf, int iBufLen, bool bCheckFeof, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
KpChar in_ch;
int buf_ix=0;
int cur_par_num;
int par_num;
bool par_end;
int gr_lev;
bool efl;
bool first_ch=True;
bool eol_fl;
bool unget_fl;

   retc=GetGrpLev(&gr_lev);
   if(SUCCEEDED(retc)) retc=GetParNum(&cur_par_num, &par_end, gr_lev);

   if(SUCCEEDED(retc)) do
   {
      do
      {
         if(first_ch) retc=GetCharProcSkipSpc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
         else retc=GetCharProc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
         first_ch=False;

         if(SUCCEEDED(retc)) retc=GetParNum(&par_num, &par_end, gr_lev);
         efl=(par_num!=cur_par_num+1);
         unget_fl=efl;
         if(!efl) if(par_end)
         {
            efl=True;
            unget_fl=(in_ch!=TX_SP_FieldEnd);
         }
      } while(((in_ch==TX_SP_FieldEnd) || (in_ch==TX_SP_FieldStart)) && (!efl) && SUCCEEDED(retc));

      if(!efl)
      {
         if((buf_ix<iBufLen-1) && (in_ch!=TX_SP_FieldEnd) && (in_ch!=TX_SP_FieldStart))
            lpszChBuf[buf_ix++]=(unsigned char)in_ch;
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
         if(unget_fl && SUCCEEDED(retc))
            retc=UnGetCharProc(in_ch);

   } while((!efl) && SUCCEEDED(retc));

   lpszChBuf[buf_ix]=Nul;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetKpTextPar(KpChar *iazChBuf, int iBufLen, bool bCheckFeof, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
KpChar in_ch;
int buf_ix=0;
int cur_par_num;
int par_num;
bool par_end;
int gr_lev;
bool efl;
bool first_ch=True;
bool eol_fl;
bool unget_fl;

   retc=GetGrpLev(&gr_lev);
   if(SUCCEEDED(retc)) retc=GetParNum(&cur_par_num, &par_end, gr_lev);

   if(SUCCEEDED(retc)) do
   {
      do
      {
         if(first_ch) retc=GetCharProcSkipSpc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
         else retc=GetCharProc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
         first_ch=False;
         if(SUCCEEDED(retc)) retc=GetParNum(&par_num, &par_end, gr_lev);
         efl=(par_num!=cur_par_num+1);
         unget_fl=efl;
         if(!efl) if(par_end)
         {
            efl=True;
            unget_fl=(in_ch!=TX_SP_FieldEnd);
         }
      } while(((in_ch==TX_SP_FieldEnd) || (in_ch==TX_SP_FieldStart)) && (!efl) && SUCCEEDED(retc));

      if(!efl)
      {
         if((buf_ix<iBufLen-1) && (in_ch!=TX_SP_FieldEnd) && (in_ch!=TX_SP_FieldStart))
            iazChBuf[buf_ix++]=in_ch;
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
         if(unget_fl && SUCCEEDED(retc))
            retc=UnGetCharProc(in_ch);

   } while((!efl) && SUCCEEDED(retc));

   iazChBuf[buf_ix]=C_Nul;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SkipCmdPars(bool bCheckFeof, TvUserClass0_tag *pUserObj)
{
HRESULT retc=S_OK;
KpChar in_ch;
int par_num;
bool par_end;
int gr_lev;
bool eol_fl;

   retc=GetGrpLev(&gr_lev);
   if(SUCCEEDED(retc)) do
   {
      retc=GetCharProc(&in_ch, bCheckFeof, &eol_fl, pUserObj);
      if(SUCCEEDED(retc)) retc=GetParNum(&par_num, &par_end, gr_lev);
   } while((par_num!=0) && SUCCEEDED(retc));

   if(SUCCEEDED(retc)) retc=UnGetCharProc(in_ch);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetGlueSize(float *pdSize, TexGlueUnits *piUnits, bool *pEndFl)
{
HRESULT retc=S_OK;
unsigned char str_buf[TV_TAG_LEN+1];
unsigned char size_buf[TX_GLUE_TAG_LEN+1];
unsigned char units_buf[TX_GLUE_TAG_LEN+1];
KpChar end_ch=C_Nul;
unsigned char *pnts;
unsigned char *pnte;
bool sp_fl=False;

   if((pdSize==NULL) || (piUnits==NULL) || (pEndFl==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   size_buf[0]=Nul;
   units_buf[0]=Nul;

   if(SUCCEEDED(retc))
   {
      *pdSize=.0;
      *piUnits=NoUnits;
      *pEndFl=False;
   }

// get size (and eventually units)
   if(SUCCEEDED(retc)) retc=SkipSpaces(&sp_fl);
   if(SUCCEEDED(retc)) retc=GetWord(str_buf, &end_ch, False);

// units ptr
   if(SUCCEEDED(retc))
   {
      pnts=str_buf;
      while(TvIsRealDigit((KpChar)(*pnts++)));
      --pnts;

      pnte=pnts;
      while(isalpha(*pnte++));
      if((end_ch==C_Spc) && SUCCEEDED(retc)) retc=UnGetChar(Spc); end_ch=C_Nul;
      if(SUCCEEDED(retc)) retc=UnGetStr(--pnte);
      *pnte=Nul;

      if(SUCCEEDED(retc))
      {
         if(strlen(pnts)<TX_GLUE_TAG_LEN) strcpy(units_buf, pnts);
         else
         {
            retc=UnGetStr(pnts);
            *pEndFl=True;
         }
         *pnts=Nul;
      }
   }

// size text
   if(SUCCEEDED(retc))
   {
      if(strlen(str_buf)<TX_GLUE_TAG_LEN) strcpy(size_buf, str_buf);
      else
      {
         retc=UnGetStr(str_buf);
         if(sp_fl && SUCCEEDED(retc)) retc=UnGetChar(Spc); sp_fl=False;
         *pEndFl=True;
      }
   }

// scan size
   if(SUCCEEDED(retc))
   {
      if(strlen((const char *)size_buf)>0) sscanf((const char *)size_buf, "%f", pdSize);
      else
      {
         retc=UnGetStr(units_buf);
         if(sp_fl && SUCCEEDED(retc)) retc=UnGetChar(Spc); sp_fl=False;
         units_buf[0]=Nul;
         *pEndFl=True;
      }
      size_buf[0]=Nul;
   }

// get units
   if((strlen(units_buf)==0) && (!(*pEndFl)) && SUCCEEDED(retc))
   {
      retc=SkipSpaces(&sp_fl);
      if(SUCCEEDED(retc)) retc=GetWord(str_buf, &end_ch, False);
      if(SUCCEEDED(retc))
      {
         if(strlen(str_buf)<TX_GLUE_TAG_LEN) strcpy(units_buf, str_buf);
         else
         {
            if((end_ch==C_Spc) && SUCCEEDED(retc)) retc=UnGetChar(Spc); end_ch=C_Nul;
            if(SUCCEEDED(retc)) retc=UnGetStr(str_buf);
            if(sp_fl && SUCCEEDED(retc)) retc=UnGetChar(Spc); sp_fl=False;
            *pEndFl=True;
         }
      }
   }

// scan units
   if((strlen(units_buf)>0) && (!(*pEndFl)) && SUCCEEDED(retc))
   {
      retc=GetKwrdIndexSkipSpc((int *)piUnits, units_buf, plpszaGlueUnitNames, -1, True, False);
      if(SUCCEEDED(retc))
      {
         pnte=units_buf+strlen(plpszaGlueUnitNames[*piUnits]);
         retc=UnGetStr(pnte);
         *pnte=Nul;
      }
      else if(retc==KP_E_KWD_NOT_FOUND)
      {
         retc=S_OK;
         *piUnits=NoUnits;
         if((end_ch==C_Spc) && SUCCEEDED(retc)) retc=UnGetChar(Spc); end_ch=C_Nul;
         retc=UnGetStr(units_buf);
         if(sp_fl && SUCCEEDED(retc)) retc=UnGetChar(Spc); sp_fl=False;
         *pEndFl=True;
      }
      units_buf[0]=Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetGlue(GlueDescriptor_tag *lpGlueDescript)
{
HRESULT retc=S_OK;
unsigned char str_buf[TV_TAG_LEN+1];
bool end_fl=False;
KpChar end_ch=C_Nul;
bool sp_fl=False;

   if(lpGlueDescript==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) lpGlueDescript->ResetFields();

// get size and units
   if(SUCCEEDED(retc)) retc=GetGlueSize(&lpGlueDescript->dSize, &lpGlueDescript->iUnits, &end_fl);

   if(/* (!end_fl) && */ SUCCEEDED(retc))
   {
// plus?
      retc=SkipSpaces(&sp_fl);
      if(SUCCEEDED(retc)) retc=GetWord(str_buf, &end_ch, True);
      if(SUCCEEDED(retc)) if(strcmp(str_buf, "plus")==0)
      {
// get plus size and units
         retc=GetGlueSize(&lpGlueDescript->dPlusSize, &lpGlueDescript->iPlusUnits, &end_fl);

// get next word - possible combination with "minus"
         if((!end_fl) && SUCCEEDED(retc))
         {
            retc=SkipSpaces(&sp_fl);
            if(SUCCEEDED(retc)) retc=GetWord(str_buf, &end_ch, True);
         }
      }
// minus?
      if(SUCCEEDED(retc))
      {
         if(strcmp(str_buf, "minus")==0)
         {
            retc=GetGlueSize(&lpGlueDescript->dMinusSize, &lpGlueDescript->iMinusUnits, &end_fl);
            str_buf[0]=Nul;
         }
      }
// "to"?
      if(SUCCEEDED(retc))
      {
         if(strcmp(str_buf, "to")==0)
         {
            retc=GetGlueSize(&lpGlueDescript->dToSize, &lpGlueDescript->iToUnits, &end_fl);
            str_buf[0]=Nul;
         }
      }
// spread?
      if(SUCCEEDED(retc))
      {
         if(strcmp(str_buf, "spread")==0)
            retc=GetGlueSize(&lpGlueDescript->dSpreadSize, &lpGlueDescript->iSpreadUnits, &end_fl);
         else
         {
            if((end_ch==C_Spc) && SUCCEEDED(retc)) retc=UnGetChar(Spc); end_ch=C_Nul;
            retc=UnGetStr(str_buf);
            if(sp_fl && SUCCEEDED(retc)) retc=UnGetChar(Spc); sp_fl=False;
         }
      }
   }

return(retc);
}


// ================================================== low level output
// --------------------------------------------------
HRESULT TvTexFile::PutChar(const unsigned char ucOutch, bool bSkipLineOnSpace)
{
HRESULT retc=S_OK;
bool char_present=False;
KpChar out_chr=(KpChar)ucOutch;

   if((ucOutch==TX_CH_FieldStart) && SUCCEEDED(retc)) retc=PushField(&out_chr, &char_present, TX_WIDE_FIELD, False);

   if(lpfFilePtr==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if((ucOutch==Spc) && (iCharPos>=TX_CHAR_POS_THRESHOLD) && bSkipLineOnSpace)
      {
         fputc(Lf, lpfFilePtr);
         iCharPos=0;
      }
      else
      {
         if(ucOutch==Lf) iCharPos=0;
         else iCharPos++;
         if(ucOutch!=Nul) fputc(ucOutch, lpfFilePtr);
      }

      if(feof(lpfFilePtr) || ferror(lpfFilePtr))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszFName, TRUE, __FILE__, __LINE__, 0L);
   }

   if((ucOutch==TX_CH_FieldEnd) && SUCCEEDED(retc)) retc=PopField(&out_chr, &char_present);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PutStr(const unsigned char *lpszOutstr, bool bSkipLineOnSpace)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   pnts=lpszOutstr;
   while(*pnts && SUCCEEDED(retc)) retc=PutChar(*pnts++, bSkipLineOnSpace);

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PutStrSqDiacr(const unsigned char *lpszOutstr, bool bSkipLineOnSpace)
{
HRESULT retc=S_OK;
unsigned char str_buf[TV_TAG_LEN+1];

   if(strlen((const char *)lpszOutstr)>=TV_TAG_LEN)
      retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=StrCpySqDiacr(str_buf, lpszOutstr);

   if(SUCCEEDED(retc)) retc=PutStr(str_buf, bSkipLineOnSpace);

return(retc);
}


// ================================================== high level output
// --------------------------------------------------
HRESULT TvTexFile::SetCtblSwitched(const bool bValue)
{
HRESULT retc=S_OK;

   if((pCurrentField==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) pCurrentField->m_bCtblSwitched=bValue;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetCtblSwitched(bool *pbValue)
{
HRESULT retc=S_OK;

   if((pbValue==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if((pCurrentField==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pbValue=pCurrentField->m_bCtblSwitched;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::SetFirstChar(const bool bValue)
{
HRESULT retc=S_OK;

   if((pCurrentField==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) pCurrentField->m_bFirstChar=bValue;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::GetFirstChar(bool *pbValue)
{
HRESULT retc=S_OK;

   if((pbValue==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if((pCurrentField==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) *pbValue=pCurrentField->m_bFirstChar;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::ResetLastChar(void)
{
   iLastChar=C_Nul;
   iLastOutChar=C_Nul;
   iLastSwitch=(KpChar)TX_TG_ctbl_off;

return(S_OK);
}


// --------------------------------------------------
HRESULT TvTexFile::OpenField(bool bFlushFl, bool bSkipLineOnSpace)
{
HRESULT retc=S_OK;
KpChar out_chr;

   out_chr=(KpChar)TX_CH_FieldStart;

   if(bFlushFl) retc=FlushSpaces(bSkipLineOnSpace);
   if(SUCCEEDED(retc)) retc=PutChar(out_chr, bSkipLineOnSpace);
   if(iLastChar==TX_TG_forc_sp) iLastChar=C_Spc;
   iLastOutChar=(KpChar)TX_SP_FieldStart;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::CloseField(bool bFlushFl, bool bSkipLineOnSpace)
{
HRESULT retc=S_OK;
KpChar out_chr;

   out_chr=(KpChar)TX_CH_FieldEnd;

   if(bFlushFl) retc=FlushSpaces(bSkipLineOnSpace);
   if(SUCCEEDED(retc)) retc=PutChar(out_chr, bSkipLineOnSpace);
   if(iLastChar==TX_TG_forc_sp) iLastChar=C_Spc;
   iLastOutChar=out_chr;

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::FlushSpaces(bool bSkipLineOnSpace)
{
HRESULT retc=S_OK;

   if((iLastChar==C_Spc) || (iLastChar==TX_TG_forc_sp))
   {
      if((iLastChar>=TX_TG_FirstTag) && (iLastChar<TX_TG_LastTag))
      {
         if(plpszaMainTexTagTable[iLastChar-TX_TG_FirstTag]!=NULL)
            retc=PutStr(plpszaMainTexTagTable[iLastChar-TX_TG_FirstTag], False);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else if((iLastChar>=TX_FirstUserTagCode) && (iLastChar<TX_FirstUserTagCode+iNumOfUserTags))
      {
         if(plpszaUserTexTagTable[iLastChar-TX_FirstUserTagCode]!=NULL)
         {
            if(strlen(plpszaUserTexTagTable[iLastChar-TX_FirstUserTagCode])>0)
               retc=PutStr(plpszaUserTexTagTable[iLastChar-TX_FirstUserTagCode], False);
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else if((iLastChar>=0) && (iLastChar<C_CharSize0))
      {
         if(plpszaTexSpecCharTags[iLastChar]!=NULL)
            retc=PutStr(plpszaTexSpecCharTags[iLastChar], bSkipLineOnSpace /* False */);
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);

//    retc=PutChar(iLastChar, bSkipLineOnSpace);
      iLastChar=C_Nul;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PutCharProc(KpChar iOutch, TexTagTypes iTagType, bool bSkipLineOnSpace, int iLastWordRest)
{
HRESULT retc=S_OK;
unsigned char ch;
const int *pnt_var;
int /* bool */ check_var;
bool math_fl;
TexTagTypes tag_type;
unsigned char out_str[MAX_LONG_DIGITS+1];
int prev_ctbl;
bool ctbl_switched=False;
bool first_char;

// if(iOutch==12010) // VL_TG_LX
// iOutch=12010;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pCurrentField->GetMathFlag(&math_fl);

   if(SUCCEEDED(retc))
   {
      pnt_var=iaUserTexTagVariations;
      check_var=True;
      while((*pnt_var) && SUCCEEDED(retc))
      {
         if(
            (*(pnt_var+1)==iOutch) &&
            (
               ((*(pnt_var+2)==TX_FORMULA_FIELD)==math_fl) ||
               (*(pnt_var+2)==TX_BOTH_TYPES)
            )
           )
         {
            if(*pnt_var!=iOutch) retc=PutCharProc((KpChar)*pnt_var, iTagType, bSkipLineOnSpace, iLastWordRest);
            else
            {
               check_var=False;
               pnt_var=&check_var;
            }
            break;
         }
         pnt_var+=3;
      }
   }

   if((*pnt_var==C_Nul) && check_var && SUCCEEDED(retc))
   {
      pnt_var=iaTexTagVariations;
      while((*pnt_var) && SUCCEEDED(retc))
      {
         if(
            (*(pnt_var+1)==iOutch) &&
            (
               ((*(pnt_var+2)==TX_FORMULA_FIELD)==math_fl) ||
               (*(pnt_var+2)==TX_BOTH_TYPES)
            )
           )
         {
            retc=PutCharProc((KpChar)*pnt_var, iTagType, bSkipLineOnSpace, iLastWordRest);
            break;
         }
         pnt_var+=3;
      }
   }

   if((*pnt_var==C_Nul) && SUCCEEDED(retc))
   {
      if(iOutch==C_Spc)
      {
         if(
            ((iLastOutChar>=TX_TG_FirstTag) && (iLastOutChar<TX_TG_LastTag)) ||
            ((iLastOutChar>=TX_FirstUserTagCode) && (iLastOutChar<TX_FirstUserTagCode+iNumOfUserTags)) ||
            (iLastOutChar==C_hSpc)
           )
            iLastChar=(KpChar)TX_TG_forc_sp;
         else
            iLastChar=iOutch;
      }
      else
      {
         if(TvKpStrChr(iaFontSwitches, iOutch)!=NULL)
            iLastSwitch=iOutch;
         else
         {
            iLastOutChar=iOutch;

            if((iLastChar==C_Spc) || (iLastChar==TX_TG_forc_sp))
               if((iOutch!=TX_SP_Lf) && (iOutch!=C_Ff))
                  retc=FlushSpaces(bSkipLineOnSpace);

            if(iLastSwitch!=TX_TG_ctbl_off)
            {
               if(iCurFont!=iLastSwitch)
               {
                  prev_ctbl=iCurCtbl;

                  if(!bTransparent)
                  {
                     if(SUCCEEDED(retc)) retc=GetCtblSwitched(&ctbl_switched);
                     if(ctbl_switched && SUCCEEDED(retc))
                     {
//                      retc=PutChar(TX_CH_FieldEnd, bSkipLineOnSpace);
                        retc=CloseField(False, bSkipLineOnSpace);
                     }
                     if(SUCCEEDED(retc)) retc=GetFirstChar(&first_char);
                     if(!first_char && (prev_ctbl!=iaTexTagCtbls[iLastSwitch-TX_TG_FirstTag] /* iCurCtbl */) && SUCCEEDED(retc))
                     {
//                      if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldStart, bSkipLineOnSpace);
                        if(SUCCEEDED(retc)) retc=OpenField(False, bSkipLineOnSpace);

                        if(SUCCEEDED(retc)) retc=SetCtblSwitched(True);
                     }
                     if(SUCCEEDED(retc)) retc=PutStr(plpszaMainTexTagTable[iLastSwitch-TX_TG_FirstTag], False);
                     if(SUCCEEDED(retc)) retc=PutChar(Spc, False);

//                   iCurFont=(TX_TagIds)iLastSwitch;
//                   iCurCtbl=iaTexTagCtbls[iLastSwitch-TX_TG_FirstTag];
                     if(SUCCEEDED(retc)) retc=SetCurFont(iLastSwitch);
                  }
               }

               iLastSwitch=(KpChar)TX_TG_ctbl_off;
            }

            if(SUCCEEDED(retc)) switch(iOutch)
            {
            case TX_SP_KeywordStart:
               retc=PutChar(TX_CH_KeywordStart, False);
               break;

            case TX_SP_CommentStart:
               retc=PutChar(TX_CH_CommentStart, False);
               break;

#if TRUE // FALSE
            case TX_SP_FieldStart:
//             retc=PutChar(TX_CH_FieldStart, bSkipLineOnSpace);
               retc=OpenField(False, bSkipLineOnSpace);

//             bFirstChar=FALSE;
               break;

            case TX_SP_FieldEnd:
//             retc=PutChar(TX_CH_FieldEnd, bSkipLineOnSpace);
               retc=CloseField(False, bSkipLineOnSpace);

//             if(SUCCEEDED(retc)) retc=SetFirstChar(False);
//             if(SUCCEEDED(retc)) retc=SetCtblSwitched(False);
               break;
#endif

            case TX_SP_MathField:
               if(iCurFontSav==(TX_TagIds)C_Nul)
               {
                  iCurFontSav=iCurFont;
                  iCurFont=(KpChar)TX_TG_rm;
//                bFirstChar=False;
               }
               else
               {
                  iCurFont=iCurFontSav;
                  iCurFontSav=C_Nul;
                  retc=SetFirstChar(False);
               }

               if(SUCCEEDED(retc)) retc = GetMathFlag(&math_fl);
               if(SUCCEEDED(retc)) retc = SetMathFlag(!math_fl);

               if(SUCCEEDED(retc)) retc=PutChar(TX_CH_MathField, False);
               break;

            case TX_SP_NBSP:
               retc=PutChar(TX_CH_NBSP, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Hash:
               retc=PutChar(TX_CH_Hash, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Amp:
               retc=PutChar(TX_CH_Amp, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_UnderL:
               retc=PutChar(TX_CH_UnderL, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Eq:
               retc=PutChar(TX_CH_Eq, False);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Apost:
               retc=PutChar(TX_CH_Apost, False);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Grave:
               retc=PutChar(TX_CH_Grave, False);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_At:
               retc=PutChar(TX_CH_At, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Circ:
               retc=PutChar(TX_CH_Circ, False);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Quot:
               retc=PutChar(TX_CH_Quot, False);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case TX_SP_Lf:
               retc=PutChar(TX_CH_Lf, bSkipLineOnSpace);
//             if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            case C_Lf:
               if(bLastWordInParFl)
               {
                  bLastWordInParFl=False;
                  retc=CloseField(False, bSkipLineOnSpace);
               }

               if(SUCCEEDED(retc)) retc=PutChar(TX_CH_Lf, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=PutChar(TX_CH_Lf, bSkipLineOnSpace);
//             if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

// nukelta toliau del tarpo spec. apdorojimo
//          case C_hSpc:
//             retc=PutChar(Spc, bSkipLineOnSpace);
//             if(SUCCEEDED(retc)) retc=SetFirstChar(False);
//             break;

            case C_Ff:
//             retc=PutCharProc(TX_TG_vadjust, iaMainTexTagTypes[TX_TG_vadjust-TX_FirstMainTagCode], bSkipLineOnSpace, iLastWordRest);
//             if(SUCCEEDED(retc)) retc=OpenField(False, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=PutCharProc((KpChar)TX_TG_eject, iaMainTexTagTypes[TX_TG_eject-TX_FirstMainTagCode], bSkipLineOnSpace, iLastWordRest);
//             if(SUCCEEDED(retc)) retc=CloseField(False, bSkipLineOnSpace);
               if(SUCCEEDED(retc)) retc=SetFirstChar(False);
               break;

            default:

               if(iOutch==C_hSpc) iOutch=C_Spc;
               if(iOutch==C_DollNctrl) iOutch=C_Doll;
//             if(iOutch==C_Ldopang) iOutch=C_ll;
//             if(iOutch==C_Rdopang) iOutch=C_gg;
               if(iOutch==TX_SP_Lslash) iOutch=C_Lslash;
               if(iOutch==TX_SP_Numb) iOutch=C_Numb;
               if(iOutch==TX_SP_Doll) iOutch=C_Doll;
               if(iOutch==TX_SP_Lbrack) iOutch=C_Lbrack;
               if(iOutch==TX_SP_Rbrack) iOutch=C_Rbrack;
               if(iOutch==TX_SP_Lcurl) iOutch=C_Lcurl;
               if(iOutch==TX_SP_Rcurl) iOutch=C_Rcurl;

// TeX tag
               if((iOutch>=TX_TG_FirstTag) && (iOutch<TX_TG_LastTag))
               {
                  if(plpszaMainTexTagTable[iOutch-TX_TG_FirstTag]==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);

                  if(SUCCEEDED(retc))
                  {
//                   if(iaMainTexTagArgs[iOutch-TX_TG_FirstTag]==0) ...
                     tag_type=iaMainTexTagTypes[iOutch-TX_TG_FirstTag];
                     if(iTagType!=TexNoType) tag_type=iTagType;
                     switch(tag_type)
                     {
                     case TexCtrl:
                     case TexGlue:
                        if(SUCCEEDED(retc)) retc=PutStr(plpszaMainTexTagTable[iOutch-TX_TG_FirstTag], False);
                        if(SUCCEEDED(retc)) retc=PutChar(Spc, False);
                        break;
                     case TexKey:
                     case TexTag:
                     case TexReg:
                     case TexDiacr:
                        if(SUCCEEDED(retc)) retc=PutStr(plpszaMainTexTagTable[iOutch-TX_TG_FirstTag], False);
                        break;
                     case TexMathChar:
                        if(SUCCEEDED(retc))
                        {
                           if(!math_fl) retc = PutChar(TX_CH_MathField, False); // '$'
                           else retc = OpenField(False, bSkipLineOnSpace);
                        }

                        if(SUCCEEDED(retc)) retc=PutStr(plpszaMainTexTagTable[iOutch-TX_TG_FirstTag], False);

                        if(SUCCEEDED(retc)) 
                        {
                           if(!math_fl) retc = PutChar(TX_CH_MathField, False); // '$'
                           else retc = CloseField(False, bSkipLineOnSpace);
                        }
                        break;
                     case TexChar:
//                      if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldStart, bSkipLineOnSpace);
                        if(SUCCEEDED(retc)) retc=OpenField(False, bSkipLineOnSpace);

                        if(SUCCEEDED(retc)) retc=PutStr(plpszaMainTexTagTable[iOutch-TX_TG_FirstTag], False);

//                      if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldEnd, bSkipLineOnSpace);
                        if(SUCCEEDED(retc)) retc=CloseField(False, bSkipLineOnSpace);
                        break;
                     }
                  }

                  if((iOutch==TX_TG_lastwordinpar) && SUCCEEDED(retc))
                  {
                     if(!bLastWordInParFl) bLastWordInParFl=True;
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc)) retc=OpenField(False, bSkipLineOnSpace);
                     sprintf((char *)out_str, "%d", iLastWordRest);
                     if(SUCCEEDED(retc)) retc=PutStr(out_str, False);
                     if(SUCCEEDED(retc)) retc=CloseField(False, bSkipLineOnSpace);

                     if(SUCCEEDED(retc)) retc=OpenField(False, bSkipLineOnSpace);
                  }
               }

               else
               {
                  if((iOutch>=TX_FirstUserTagCode) && (iOutch<TX_FirstUserTagCode+iNumOfUserTags))
                  {
//                   if(iaUserTexTagArgs[iOutch-TX_FirstUserTagCode]==0)
                     tag_type=iaUserTexTagTypes[iOutch-TX_FirstUserTagCode];
                     if(iTagType!=TexNoType) tag_type=iTagType;
                     switch(tag_type)
                     {
                     case TexCtrl:
                     case TexGlue:
                        if(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode]!=NULL)
                           if(strlen(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode])>0)
                           {
                              if(SUCCEEDED(retc)) retc=PutStr(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode], False);
                              if(SUCCEEDED(retc)) retc=PutChar(Spc, False);
                           }
                        break;
                     case TexKey:
                     case TexTag:
                     case TexReg:
                     case TexDiacr:
                        if(SUCCEEDED(retc))
                           if(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode]!=NULL)
                              if(strlen(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode])>0)
                                 retc=PutStr(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode], False);
                        break;

                     case TexMathChar:
                        if(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode]!=NULL)
                           if(strlen(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode])>0)
                           {
                              if(SUCCEEDED(retc))
                              {
                                 if(!math_fl) retc=PutChar(TX_CH_MathField, False); // '$'
                                 else retc=OpenField(False, bSkipLineOnSpace);
                              }

                              if(SUCCEEDED(retc)) retc=PutStr(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode], False);

                              if(SUCCEEDED(retc))
                              {
                                 if(!math_fl) retc=PutChar(TX_CH_MathField, False); // '$'
                                 else retc=CloseField(False, bSkipLineOnSpace);
                              }
                           }
                        break;

                     case TexChar:
                        if(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode]!=NULL)
                           if(strlen(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode])>0)
                           {
//                            if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldStart, bSkipLineOnSpace);
                              if(SUCCEEDED(retc)) retc=OpenField(False, bSkipLineOnSpace);

                              if(SUCCEEDED(retc)) retc=PutStr(plpszaUserTexTagTable[iOutch-TX_FirstUserTagCode], False);

//                            if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldEnd, bSkipLineOnSpace);
                              if(SUCCEEDED(retc)) retc=CloseField(False, bSkipLineOnSpace);
                           }
                        break;
                     }
                  }
                  else
                  {
// ordinary char.
// if(iOutch<0)
// ch=0;
                     if((iOutch<0) || (iOutch>=C_CharSize0))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc))
                     {
// spec Tex character?
                        retc=CharDecode(&ch, (KpChar)iOutch);
                        if
                        (
//                         (
//                            (iOutch!=C_Spc) &&
//                            (iOutch!=C_Lf) &&
// //                         (!TvIsAlpha((KpChar)iOutch)) &&
//                            SUCCEEDED(retc)
//                         ) ||

                           (iOutch==(KpChar)TX_CH_KeywordStart) ||
                           (iOutch==(KpChar)TX_CH_CommentStart) ||
                           (iOutch==(KpChar)TX_CH_FieldStart) ||
                           (iOutch==(KpChar)TX_CH_FieldEnd) ||
                           (iOutch==(KpChar)TX_CH_MathField) ||
                           (iOutch==(KpChar)TX_CH_Hash) ||
                           (iOutch==(KpChar)TX_CH_Amp) ||
                           (iOutch==(KpChar)TX_CH_Ast) ||
                           (iOutch==(KpChar)TX_CH_UnderL) ||
//                         (iOutch==(KpChar)TX_CH_Eq) ||
                           (iOutch==(KpChar)TX_CH_Apost) ||
                           (iOutch==(KpChar)TX_CH_Quot) ||
                           (iOutch==(KpChar)TX_CH_Grave) ||
                           (iOutch==(KpChar)TX_CH_At) ||
                           (iOutch==(KpChar)TX_CH_Circ) ||
                           (iOutch==(KpChar)TX_CH_NBSP) ||
                           (iOutch==C_NBSP) ||
                           (iOutch==C_Ff) ||
//                         (iOutch==C_Grave) ||

                           (retc==KP_E_UNKN_CHR)
                        )
                        {
                           if(plpszaTexSpecCharTags[iOutch]!=NULL)
                           {
                              retc=S_OK;

                              if(SUCCEEDED(retc))
                              {
                                 tag_type=iaTexSpecCharTypes[iOutch];
                                 if(iTagType!=TexNoType) tag_type=iTagType;
                                 switch(tag_type)
                                 {
                                 case TexCtrl:
                                 case TexGlue:
                                    if(SUCCEEDED(retc))
                                       retc=PutStrSqDiacr(plpszaTexSpecCharTags[iOutch], False);
                                    if
                                    (
//                                     (
//                                        TvIsAlpha((KpChar)(plpszaTexSpecCharTags[iOutch][1])) ||
//                                        (strlen((const char *)plpszaTexSpecCharTags[iOutch])>3)
//                                     ) &&
//                                     (plpszaTexSpecCharTags[iOutch][2]!=Spc) &&
                                       SUCCEEDED(retc)
                                    )
                                       retc=PutChar(Spc, False);
                                    break;
                                 case TexKey:
                                 case TexTag:
                                 case TexReg:
                                 case TexDiacr:
                                    if(SUCCEEDED(retc))
                                       retc=PutStrSqDiacr(plpszaTexSpecCharTags[iOutch], False);
                                    break;

                                 case TexMathChar:
                                    if(SUCCEEDED(retc))
                                    {
                                       if(!math_fl) retc=PutChar(TX_CH_MathField, False); // '$'
                                       else retc=OpenField(False, bSkipLineOnSpace);
                                    }

                                    if(SUCCEEDED(retc)) retc=PutStrSqDiacr(plpszaTexSpecCharTags[iOutch], False);

                                    if(SUCCEEDED(retc))
                                    {
                                       if(!math_fl) retc=PutChar(TX_CH_MathField, False); // '$'
                                       else retc=CloseField(False, bSkipLineOnSpace);
                                    }
                                    break;

                                 case TexChar:
//                                  if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldStart, bSkipLineOnSpace);
                                    if(
                                       /* (iOutch!=TX_CH_NBSP) && */ (iOutch!=C_NBSP) &&  // apskliaudus {~} neveikia RLZ iterptiniu konvertavimo i \rm makrokomanda
                                       SUCCEEDED(retc)
                                      )
                                       retc = OpenField(False, bSkipLineOnSpace);
                                    
                                    if(SUCCEEDED(retc)) // switch(iOutch)
                                    {
#if FALSE
                                       case C_QemSpc:
                                       case TX_CH_FieldStart: // èia nepatenka ???
                                       case TX_CH_FieldEnd: // èia nepatenka ???
                                       case C_Multipl:
                                       case C_uparr:
                                       case C_Sum:

                                          if(SUCCEEDED(retc)) retc=PutChar(TX_CH_MathField, False); // '$'
                                          if(SUCCEEDED(retc)) retc=PutStrSqDiacr(plpszaTexSpecCharTags[iOutch], False);
                                          if(SUCCEEDED(retc)) retc=PutChar(TX_CH_MathField, False); // '$'
                                          break;
#endif
#if FALSE
                                       case C_Acute:
                                       case C_Dacut:
                                       case C_Ogon:
                                       case C_Adot:
                                       case C_Car:
                                       case C_Macr:
                                       case C_Diaer:
                                       case C_Ring:
                                       case C_Tacom:
                                       case C_Bcomma:
                                       case C_Cedil:
                                          if(SUCCEEDED(retc)) retc=PutStr(plpszaTexSpecCharTags[iOutch], False);
                                          break;
#endif
//                                     default:
                                          if(SUCCEEDED(retc)) retc=PutStrSqDiacr(plpszaTexSpecCharTags[iOutch], False);
//                                        break;
                                    }

//                                  if(SUCCEEDED(retc)) retc=PutChar(TX_CH_FieldEnd, bSkipLineOnSpace);
                                    if(
                                       /* (iOutch!=TX_CH_NBSP) && */ (iOutch!=C_NBSP) &&  // apskliaudus {~} neveikia RLZ iterptiniu konvertavimo i \rm makrokomanda
                                       SUCCEEDED(retc)
                                      ) retc=CloseField(False, bSkipLineOnSpace);
                                    break;
                                 }
                              }


                           } // if(plpszaTexSpecCharTags[iOutch]!=NULL)
                           else
                           {
                              retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, False, __FILE__, __LINE__, 0L);
                              PutStr((const unsigned char *)"<?>", False);
                           }

                        } // if(retc==KP_E_UNKN_CHR)
                        else
                           retc=PutChar(ch, bSkipLineOnSpace);

                     } // if(SUCCEEDED(retc))

                  } // else // if((iOutch>=TX_FirstUserTagCode) && (iOutch<TX_FirstUserTagCode+iNumOfUserTags))

               if(SUCCEEDED(retc)) retc=SetFirstChar(False);

               } // else // if((iOutch>=TX_TG_FirstTag) && (iOutch<TX_TG_LastTag))

               break;

            } // switch(iOutch)

            if(
               ((iLastOutChar>=TX_TG_FirstTag) && (iLastOutChar<TX_TG_LastTag)) ||
               ((iLastOutChar>=TX_FirstUserTagCode) && (iLastOutChar<TX_FirstUserTagCode+iNumOfUserTags)) ||
               (iLastOutChar==C_hSpc)
              )
            {
               if((iLastChar==C_Spc) || (iLastChar==TX_TG_forc_sp))
                  iLastChar=(KpChar)TX_TG_forc_sp;
            }

         } // else if(TvKpStrChr(iaFontSwitches, iOutch)!=NULL)

      } // else if(iOutch==C_Spc)

   } // if((*pnt_var==C_Nul) && SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PutStrProc(const unsigned char *lpszOutstr, bool bSkipLineOnSpace, int iLastWordRest)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   pnts=lpszOutstr;
   while(*pnts && SUCCEEDED(retc))
   {
      if(*pnts<KPT_FirstKptChar) retc=PutCharProc((KpChar)(*pnts++), TexNoType, bSkipLineOnSpace, iLastWordRest);
      else retc=PutChar(*pnts++, bSkipLineOnSpace);
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvTexFile::PutKpStrProc(const KpChar *iaOutStr, bool bSkipLineOnSpace, int iLastWordRest)
{
const KpChar *pnts;
HRESULT retc=S_OK;

   pnts=iaOutStr;
   while((*pnts) && SUCCEEDED(retc)) retc=PutCharProc(*pnts++, TexNoType, bSkipLineOnSpace, iLastWordRest);

return(retc);
}


// =================================================== free functions
// --------------------------------------------------
HRESULT StrCpySqDiacr(unsigned char *lpszDestStr, const unsigned char *lpszSrcStr)
{
const unsigned char *pnts;
unsigned char *pntd;
bool skip_sp;
int slen;

   skip_sp=FALSE;
   slen=strlen((const char *)lpszSrcStr);
   if(
      ((slen==3) || (slen==4)) &&
      (lpszSrcStr[0]==TX_CH_KeywordStart) &&
      (TvStrChr(lpszTxAccents1, (KpChar)lpszSrcStr[1])!=NULL) &&
      (lpszSrcStr[2]==Spc)
     ) skip_sp=TRUE;

   pnts=lpszSrcStr;
   pntd=lpszDestStr;
   while(*pnts)
   {
      if((pnts-lpszSrcStr!=2) || !skip_sp) (*pntd++)=(*pnts);
      pnts++;
   }
   *pntd=Nul;

return(S_OK);
}


// --------------------------------------------------
HRESULT WriteLatexHeader(TvTexFile *lpOutFileObj, const unsigned char *lpszPublisher,
                     const unsigned char *lpszProject, const unsigned char *lpszManuscript)
{
HRESULT retc=S_OK;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_BeginFileInfo, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Publisher, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszPublisher, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Project, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszProject, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Manuscript, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszManuscript, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Company, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"TEV", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_TID, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"KP", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Stage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"100", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_ProFile, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszProject);
      strlwr(str_buf);
      retc=lpOutFileObj->PutStr(str_buf, False);
   }
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)".pro", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Compiler_cmd_line, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"LATEX612.BAT", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszPublisher, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszProject, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Perc, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"N", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Send_to_DB, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"FALSE", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_EndFileInfo, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_documentclass, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Lbrack, False); // '['
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"pagframe", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Comma, False); // ','
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"nameyear", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Rbrack, False); // ']'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszProject);
      strlwr(str_buf);
      retc=lpOutFileObj->PutStr(str_buf, False);
   }
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_documentclass, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Lbrack, False); // '['
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"xiicm", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Comma, False); // ','
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"pagframe", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Comma, False); // ','
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"nameyear", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Rbrack, False); // ']'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszProject);
      strlwr(str_buf);
      retc=lpOutFileObj->PutStr(str_buf, False);
   }
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"12X20cm teksto ismatavimu", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"draft", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Lbrack, False); // '['
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"none", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Rbrack, False); // ']'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"draft", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"figlinks", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"400p", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"harvard", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Lbrack, False); // '['
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"normalem", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Rbrack, False); // ']'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"ulem", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"tslrot", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"amssymb", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"rotating", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_usepackage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"linguex", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Comma, False); // ','
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"lingapp", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(C_Comma, False); // ','
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"natbib", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_FieldEnd, False); // '}'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_VR, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_vrule, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"height8pt", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, True);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"depth3pt", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, True);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"width0pt", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_undertext, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Hash, True); // '#'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"1", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_MathField, True); // '$'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_underline, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_hbox, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Hash, True); // '#'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"1", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_MathField, True); // '$'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_ut, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_uline, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_sut, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_sout, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_HPROOF, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_overfullrule, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"0pt", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_PROOF, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_CRC, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_INDEX, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_psdraft, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_vtexed, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_volume, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"0", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_issue, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"0", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_pubyear, TexNoType, False, LAST_WORD_LEN);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"2005", False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_doublehyphendemerits, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False); // '='
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"100000", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_articletype, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_begin, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"document", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_Project_macro, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, lpszProject);
      strlwr(str_buf);
      retc=lpOutFileObj->PutStr(str_buf, False);
   }
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_pagenumbering, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"roman", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

#if FALSE
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_begin, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"frontmatter", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_firstpage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"39", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_lastpage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"63", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);
#endif

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

return(retc);
}


// --------------------------------------------------
HRESULT WriteLatexTail(TvTexFile *lpOutFileObj)
{
HRESULT retc=S_OK;

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False); // '%'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_printbookmarks, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_end, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"document", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_begin, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"thebibliography", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"xx", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_end, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"thebibliography", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_begin, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"figure", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_figlink, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"0f0", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_caption, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_label, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"figure", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_end, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"figure", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_tablewidth, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_At, False); // '@'
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_extracolsep, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc((KpChar)TX_TG_fill, TexTag, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

return(retc);
}

