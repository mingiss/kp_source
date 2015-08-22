// ==================================================
// xmlspc.cpp
// splittind of compounds and derivatives to different nodes
//


// ================================================== definitions

#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "xmlspc.h"


// ================================================== objects
XmlSpC_tag *pXmlSpC=NULL;
KpErrorProc_tag KpErrorProc(True, 71);

// !!! enter dynamically from parameters
unsigned char caXmlSpCIxLangs[XL_IX_NumOfIndexes] =
{
   KP_LNG_NO,   // XL_IX_DataFile,      // XML data file
   KP_LNG_NO,   // XL_IX_SeIndex,       // standard entry index file
   KP_LNG_NO,   // XL_IX_HwIndex,       // headword index file
   KP_LNG_NO,   // XL_IX_TwIndex,       // translated headword index file
   KP_LNG_NO,   // XL_IX_LaIndex,       // label index file
   KP_LNG_NO,   // XL_IX_StIndex,       // standard entry text index file
};

// --------------------------------------------------
HRESULT XmlNode_tag::TestChildContents(int iTestTag, Chars16 *lpiazTestValue, bool *pFoundFlg)
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

// ================================================== public methods of XmlSpC_tag
XmlSpC_tag::XmlSpC_tag(const unsigned char *lpszInFname, const unsigned char *lpszOutFname)
{
   lhOpenResult=S_OK;

   lEntryId=0L;
   KpErrorProc.SetLPar(0L);

   iaLastHw[0]=C_Nul;

// --------------------------
   lpszInFileName[0]=Nul;
   lpInFileObj=NULL;
   if(lpszInFname==NULL)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult)) if(strlen(lpszInFname)>=KP_MAX_FNAME_LEN)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      strcpy(lpszInFileName, lpszInFname);
      KP_NEWO(lpInFileObj, XmlI_tag(lpszInFileName, (const unsigned char *)"rb", CreateNewUniFile,
                                       alpszIndexNames, aiIndexWidths, caXmlSpCIxLangs,
                                       XC_FirstDictTag, plpszaXmlttDictTags,
                                       XM_VERS_XML10, iaXmlNulCodeTables));
   }

// --------------------------
   if(lpszOutFname==NULL)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      if(strlen((const char *)lpszOutFname)<KP_MAX_FNAME_LEN) strcpy(lpszOutFileName, lpszOutFname);
      else lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   }

   KP_NEWO(lpOutFileObj, XmlI_tag(lpszOutFileName, (const unsigned char *)"w", CreateNewUniFile,
                              alpszIndexNames, aiIndexWidths, caLvzG2TIxLangs, XC_FirstDictTag, plpszaXmlttDictTagsFull,
                                 XM_VERS_XML10, iaXmlNulCodeTables));

// --------------------------
   lpszOutFileName[0]=Nul;
   lpOutFileObj=NULL;
   if((lpszOutFname==NULL) && SUCCEEDED(lhOpenResult))
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult)) if(strlen(lpszOutFname)>=KP_MAX_FNAME_LEN)
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult))
   {
      strcpy(lpszOutFileName, lpszOutFname);
      KP_NEWO(lpOutFileObj, TvTexFile_tag(lpszOutFileName, (const unsigned char *)"w", LV_TG_NumOfTags0));
   }

   pTagStack=NULL;
   KP_NEW(pTagStack, TvXmlTagStack_tag(NULL, C_Nul, NULL, 0));
}


// --------------------------------------------------
XmlSpC_tag::~XmlSpC_tag(void)
{
TvXmlTagStack_tag *prev_stack_ptr;
int cur_tag;

   CloseFiles(False);

   if(pTagStack!=NULL)
   {
      pTagStack->GetPrevTagPtr(&prev_stack_ptr);
      pTagStack->GetCurTag(&cur_tag);
      if((prev_stack_ptr!=NULL) || (cur_tag!=C_Nul))
         KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      KP_DELETE(pTagStack);
   }
   else
      KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
}


// --------------------------------------------------
HRESULT XmlSpC_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(lpOutFileObj!=NULL)
   {
      retc0=lpOutFileObj->CloseFile(bCheckFileExist);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   if(lpInFileObj!=NULL)
   {
      KP_DELETE(lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpC_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
HRESULT XmlSpC_tag::WriteHeader(const unsigned char *lpszLetId, const unsigned char *PageNo, int iBoxWdt)
{
HRESULT retc=S_OK;
unsigned char str_buf[20];
const unsigned char *pnts;
Chars16 out_ch;

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_Project, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"LVZ03\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_Publisher, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"TEV\n", False);
   
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_Stage, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"200\n", False);
   
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_Pages, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_TID, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"lvzt2x\n\n", False);
   
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"---------------------------------------\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"öitas failas sugeneruotas automati÷kai\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"Originalai - X:\\Dict_DB\\Tev\\lvz03\\lvz*\\lvz*.mdb\n\n", False);
   
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(LV_TG_theraide, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);

// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszLetId, False);
   if(SUCCEEDED(retc))
   {
      pnts=lpszLetId;
      while((*pnts) && SUCCEEDED(retc))
      {
         if(*pnts==Spc) retc=lpOutFileObj->PutCharProc(C_NBSP, TexNoType, False, LAST_WORD_LEN);
         else
         {
            retc=KptCharEncode(&out_ch, *pnts, 50);
            if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(out_ch, TexNoType, False, LAST_WORD_LEN);
         }
         pnts++;
      }
   }

   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(LV_TG_hboxup, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"#1", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_hbox, TexNoType, False, LAST_WORD_LEN);
   sprintf((char *)str_buf, "to %dcm", iBoxWdt);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(str_buf, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"#1", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_def, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(LV_TG_nuleisti, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"7.0mm", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_input, TexNoType, False, LAST_WORD_LEN);
//// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"init.sty", False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_input, TexNoType, False, LAST_WORD_LEN);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"lvz03.sty", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_HPROOF, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_CommentStart, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_CRC, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_pageno, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(TX_CH_Eq, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(PageNo, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_begindoublecolumns, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(LV_TG_raide, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszLetId, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

   if(bTagOutFormat && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_settabs, TexNoType, False, LAST_WORD_LEN);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)str_buf, " %d ", XN_TABS_PER_COL);
         retc=lpOutFileObj->PutStr(str_buf, False);
      }
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_columns, TexNoType, False, LAST_WORD_LEN);
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);

//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_plus, TexNoType, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_SP_Amp, TexNoType, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_SP_Amp, TexNoType, False, LAST_WORD_LEN);
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpC_tag::WriteTail(const unsigned char *lpszLetId, const unsigned char *lpszLastMark)
{
HRESULT retc=S_OK;
int last_char=C_Nul;
int char_pos=0;
const int *pnts;

   if(lpOutFileObj==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

// if(bTagOutFormat && SUCCEEDED(retc))
// {
//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_cr, TexNoType, False, LAST_WORD_LEN);
//
////  if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_break, TexNoType, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);
//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);
// }


   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_zmark, TexNoType, False, LAST_WORD_LEN);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->OpenField(True, False);

// if(TvIntStrLen(lpszLastMark)==0)
   if(strlen(lpszLastMark)==0)
   {
//    if(SUCCEEDED(retc)) retc=lpOutFileObj->PutIntStrProc(iaLastHw, False, LAST_WORD_LEN);
//    if(SUCCEEDED(retc)) retc=PutTexIntStr(lpOutFileObj, iaLastHw, &last_char, XC_Dict, NULL, bTagOutFormat, &char_pos, 0, TvIntStrLen(iaLastHw), LAST_WORD_LEN);
      pnts=iaLastHw;
      if(SUCCEEDED(retc)) if(pnts) while(*pnts)
         retc=lpOutFileObj->PutCharProc(CvtToTex(*pnts++), TexNoType, False, LAST_WORD_LEN);
   }
   else
      if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszLastMark, False);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->CloseField(True, False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);


   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_input, TexNoType, False, LAST_WORD_LEN);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Spc, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"lvz", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(lpszLetId, False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)".app", False);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_enddoublecolumns, TexNoType, False, LAST_WORD_LEN);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(TX_TG_end, TexNoType, False, LAST_WORD_LEN);
// if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutChar(Lf, True);

return(retc);
}


// --------------------------------------------------
HRESULT XmlSpC_tag::Process(const int *piazFromHw, const int *piazToHw)
{
HRESULT retc=S_OK;
int in_ch;
XmlTagPars_tag *tag_pars=NULL;
XmlNode_tag *cur_entry = NULL;
long entr_id;
int par_num;
int *hw_ptr=NULL;
int hw_lwr[TV_XL_MAX_IX_LEN+1];
int prev_tag=XC_Nul;
int last_char=C_Nul;
int num_of_chars;
int l_word_start;
int l_word_rest;
int char_pos;

   if((lpInFileObj==NULL) || (lpOutFileObj==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);

   if((pTagStack==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
   
   while(SUCCEEDED(retc))
   {
      do
      {
         retc=lpInFileObj->GetCharProc(&in_ch, &tag_pars, False);
         if((in_ch==XC_StEntry) && SUCCEEDED(retc))
         {
            lEntryId++;
            entr_id=0L;
            if(tag_pars!=NULL) retc=tag_pars->SeekNumPar("id", &entr_id, &par_num);
//          KpErrorProc.SetLPar(entr_id);
            KpErrorProc.SetLPar(lEntryId);

// unsigned char out_buf[TV_XM_MAX_TAG_CONTENTS_WDT+1];
// printf("-------------------- %ld   %ld\n",lEntryId, entr_id);
// if(lEntryId==5L)
// lEntryId=5L;

            if((cur_entry!=NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

            KP_NEWO(cur_entry, XmlNode_tag(in_ch, tag_pars, NULL, (const unsigned char *)""));
         }
         KP_DELETE(tag_pars);

      } while((in_ch!=XC_StEntry) && SUCCEEDED(retc));

// printf("------------- %d\n", lpOutFileObj->GetFldDepth());

      if(SUCCEEDED(retc)) retc=cur_entry->ReadNode(lpInFileObj);

// if(SUCCEEDED(retc)) retc=cur_entry->TestNode();

      if(SUCCEEDED(retc)) retc=cur_entry->DelTags(XC_StEntryText);

// if(SUCCEEDED(retc)) retc=cur_entry->TestNode();

      hw_ptr=NULL;
      if(SUCCEEDED(retc)) retc=cur_entry->GetHw((Chars16 **)&hw_ptr);
      if((hw_ptr==NULL) && SUCCEEDED(retc))
      {
         hw_ptr=(int *)iNullStr;
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
      {
         TvIntStrNCpy(iaLastHw, hw_ptr, TV_XL_MAX_IX_LEN);
         iaLastHw[TV_XL_MAX_IX_LEN]=C_Nul;
      }

// if(SUCCEEDED(retc))
// {
// KptStrDecode(out_buf, hw_ptr, TvIntStrLen(hw_ptr), 71);
// printf("%s\n", out_buf);
// }

      if(SUCCEEDED(retc))
      {
         TvIntStrNCpy(hw_lwr, hw_ptr, TV_XL_MAX_IX_LEN);
         hw_lwr[TV_XL_MAX_IX_LEN]=C_Nul;
         TvIStrLwr(hw_lwr);

         if(TvIntStrCmp(hw_lwr, piazToHw)>=0) retc=KP_E_EOF;

         if((TvIntStrCmp(hw_lwr, piazFromHw)>=0) && SUCCEEDED(retc))
         {
            num_of_chars=0;
            retc=cur_entry->CountCharactersTex(&num_of_chars, XC_FirstDictTag, prev_tag, bTagOutFormat);
            
            l_word_start=0;
            l_word_rest=LAST_WORD_LEN;
            if(SUCCEEDED(retc))
            {
               char_pos=0;
               retc=cur_entry->GetLastWordPosTex(&l_word_start, &l_word_rest, &char_pos, num_of_chars, XC_FirstDictTag, prev_tag, bTagOutFormat);
            }

            if(SUCCEEDED(retc))
            {
               char_pos=0;
               retc=cur_entry->WriteTex(lpOutFileObj, &char_pos, l_word_start, l_word_rest, num_of_chars, XC_Dict, XC_FirstDictTag, prev_tag, &last_char, bTagOutFormat);
            }

// printf("%d %d %d %d\n", num_of_chars, char_pos, l_word_start, l_word_rest);

// patikrint DelimStrLenTex() - issiderino su WriteTex()
            if((num_of_chars!=char_pos) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) retc=cur_entry->GetNodeTag(&prev_tag);
         }

      }

      KP_DELETE(cur_entry);

   } // while(SUCCEEDED(retc))

   if(retc==KP_E_EOF) retc=S_OK;

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
unsigned char *l_argv[8];
int str_len;
int from_hw[TV_XL_MAX_IX_LEN+1];
int to_hw[TV_XL_MAX_IX_LEN+1];
// int last_mark[TV_XL_MAX_IX_LEN+1];
unsigned char last_mark[TV_XL_MAX_IX_LEN+1];
const unsigned char *pnt_let;
unsigned char letter[10];
unsigned char letl[10];
int ii;
bool tag_frm;

   printf("\nXMLT dictionary to TeX converter\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   StackTop=&argc;

   retc=InitNodesArray();

   if(SUCCEEDED(retc))
   {
      l_argc=argc;
      if(argc>=4)
      {
         for(ii=0; (ii<8) && (ii<argc); ii++)
         {
            l_argv[ii]=(unsigned char *)argv[ii];
// printf("%s\n", l_argv[ii]);
         }
      }

// #ifdef Debug
      else if(strstr(strlwr(argv[0]), "debug")>0)
      {
         l_argc=8;
         l_argv[0]=(unsigned char *)"lvzt2x";

//       l_argv[1]=(unsigned char *)"d:/kp/source/tev/liz/Pavyzdys.xml";
//       l_argv[1]=(unsigned char *)"d:/kp/source/tev/lvz/lvzp.xml";
         l_argv[1]=(unsigned char *)"d:/kp/source/tev/lvz/lvz_comp.xml";

//       l_argv[2]=(unsigned char *)"d:/kp/source/tev/liz/Pavyzdys.tex";
//       l_argv[2]=(unsigned char *)"d:/kp/source/tev/lvz/lvza_y.tex";
//       l_argv[2]=(unsigned char *)"d:/kp/source/tev/lvz/lvzp.tex";
         l_argv[2]=(unsigned char *)"d:/kp/source/tev/lvz/lvz_comp.tex";

         l_argv[3]=(unsigned char *)"1";

         l_argv[4]=(unsigned char *)"n";

//       l_argv[5]=(unsigned char *)"\\an\\cv\\en\\et\\ino\\sv\\un\\ub\\zv\\An\\Cv\\En\\Et\\In\\Sv\\Un\\Ub\\Zv";
         l_argv[5]=(unsigned char *)"formatas";

         l_argv[6]=(unsigned char *)"a";
         
         l_argv[7]=(unsigned char *)"zzzzzz";
      }
// #endif

      tag_frm=False;
      if(SUCCEEDED(retc)) if(l_argc>4)
         tag_frm=((strlen(l_argv[4])==1) && ((l_argv[4][0]=='y') || (l_argv[4][0]=='Y')));

      last_mark[0]=C_Nul;
      if(SUCCEEDED(retc)) if(l_argc>5)
      {
//       str_len=TV_XL_MAX_IX_LEN;
//       retc=KptStrEncode(last_mark, (unsigned char *)l_argv[5], &str_len, 43 /* kbl codetable */);

         strncpy(last_mark, l_argv[5], TV_XL_MAX_IX_LEN);
         last_mark[TV_XL_MAX_IX_LEN]=Nul;
      }

      from_hw[0]=C_Nul;
      to_hw[0]=C_CharSize0;
      to_hw[1]=C_Nul;
      if(SUCCEEDED(retc)) if(l_argc>6)
      {
         str_len=TV_XL_MAX_IX_LEN;
         retc=KptStrEncode(from_hw, (unsigned char *)l_argv[6], &str_len, 1);
         TvIStrLwr(from_hw);
         to_hw[0]=from_hw[0]+1;
      }

      if(SUCCEEDED(retc)) if(l_argc>7)
      {
         str_len=TV_XL_MAX_IX_LEN;
         retc=KptStrEncode(to_hw, (unsigned char *)l_argv[7], &str_len, 1);
         TvIStrLwr(to_hw);
      }

      if(SUCCEEDED(retc))
      {
         if(l_argc>=4)
         {
            KP_NEWO(pXmlSpC, XmlSpC_tag(l_argv[1], l_argv[2], tag_frm));

            if(SUCCEEDED(retc))
            {
               strcpy(letl, "A");
               strcpy(letter, "A");

               pnt_let=strchr(l_argv[2], '.');
               if(pnt_let!=NULL)
               {
                  if(pnt_let>l_argv[2])
                  {
                     if(*(pnt_let-1)=='_')
                     {
                        if(pnt_let>l_argv[2]+1)
                        {
                           letl[0]=toupper(*(pnt_let-2));
                           strcpy(letl+1, "_");

                           switch(toupper(*(pnt_let-2)))
                           {
                           case 'C': letter[0]='Þ'; break;
                           case 'S': letter[0]='ö'; break;
                           case 'Z': letter[0]='ü'; break;
                           }
                        }
                     }
                     else letl[0]=letter[0]=toupper(*(pnt_let-1));
                  }
               }

               switch(letter[0])
               {
               case 'A': strcpy(letter, "A, Ü"); retc=pXmlSpC->WriteHeader(letter, l_argv[3], 4); break;
//             case 'E': strcpy(letter, "E, ð, ò"); retc=pXmlSpC->WriteHeader(letter, l_argv[3], 5); break;
               case 'E': strcpy(letter, "E, ò"); retc=pXmlSpC->WriteHeader(letter, l_argv[3], 4); break;
               case 'I': strcpy(letter, "I, ô, Y"); retc=pXmlSpC->WriteHeader(letter, l_argv[3], 5); break;
//             case 'U': strcpy(letter, "U, ø, ú"); retc=pXmlSpC->WriteHeader(letter, l_argv[3], 5); break;
               case 'U': strcpy(letter, "U, ú"); retc=pXmlSpC->WriteHeader(letter, l_argv[3], 4); break;
               default: retc=pXmlSpC->WriteHeader(letter, l_argv[3], 3); break;
               }             

               if(SUCCEEDED(retc)) retc=pXmlSpC->Process(from_hw, to_hw);

               if(SUCCEEDED(retc)) retc=pXmlSpC->WriteTail(letl, last_mark);

               retc0=pXmlSpC->CloseFiles(SUCCEEDED(retc));
               if(SUCCEEDED(retc)) retc=retc0;
            }
         }
         else // if(l_argc>=4)
         {
            printf("Bad number of parameters:\n");
            printf("   c:>lvzt2x.exe infile.xml outfile.tex 15 y {\\ino}va{\\zv}iavimas a akzzz\n");
            printf("                                        ^  ^ `---------.--------' ^ `-.-'\n");
            printf("       start page ----------------------'  |           |          |   |\n");
            printf("      [tagged output format flag (y/n)] ---'           |          |   |\n");
            printf("      [last page mark (plain ASCII string -------------'          |   |\n");
            printf("       with possible TeX commands)]                               |   |\n");
            printf("      [start headword] -------------------------------------------'   |\n");
            printf("      [end headword] -------------------------------------------------'\n");
            printf("   (input file can be without punctuations between tags)\n");
            if(SUCCEEDED(retc)) retc=E_INVALIDARG;
         }

      } // if(SUCCEEDED(retc))

      KP_DELETE(pXmlSpC);

   } // if(SUCCEEDED(retc))

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
