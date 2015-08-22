// ==================================================
// tvrtfo.cpp
// RTF file for output


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#if OsGr==MSWin
#include <windows.h>
#endif

#include "kpstdlib.h"
#include "kptt.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlsty.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"

// ================================================== private methods of TvRtfO_tag


// ================================================== public methods of TvRtfO_tag
// --------------------------------------------------
TvRtfO_tag::TvRtfO_tag
(
const unsigned char *lpszOutfname,
HRESULT CreateLowLevelObj
(
   KpFile **lppFileObjPtrPtr,
   const unsigned char *lpszFNam,
   const unsigned char *lpszFMod,
   XL_FileTypes uiFTyp,
   bool bMapToPrivate
),
RT_FontDescriptor_tag *pFontTbl
)
{
bool last_entry;
// int rtf_tbl;
int ctbl;
  
#if FALSE  
   KP_NEW(lpfRtfFile, TvXml8File_tag(lpszOutfname, (const unsigned char *)"w", XL_FT_DataFile));
#else      
   lhOpenResult = CreateLowLevelObj(&lpfRtfFile, lpszOutfname, (const unsigned char *)"w", XL_FT_DataFile, False);
#endif

   pFonts=pFontTbl;
   if((pFontTbl==NULL) && SUCCEEDED(lhOpenResult))
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   iStdWinFontIndex=RT_FONT_UNDEFINED;
   iCEFontIndex=RT_FONT_UNDEFINED;
   iPhonFontIndex=RT_FONT_UNDEFINED;
   iLTFontIndex=RT_FONT_UNDEFINED;
   iLTAccFontIndex=RT_FONT_UNDEFINED;
   iSymbolFontIndex=RT_FONT_UNDEFINED;

   iNumOfFonts=0;
   for(iNumOfFonts=0; (iNumOfFonts<RT_MAX_NUM_OF_FONTS) && SUCCEEDED(lhOpenResult); iNumOfFonts++)
   {
      lhOpenResult=pFonts[iNumOfFonts].IsLast(&last_entry);
      if(last_entry) break;

//    if(SUCCEEDED(lhOpenResult)) lhOpenResult=pFonts[iNumOfFonts].GetRtfCodeTable(&rtf_tbl);
//    if(SUCCEEDED(lhOpenResult)) ctbl=ConvertRtf2KptCTbl(rtf_tbl);
//    if(SUCCEEDED(lhOpenResult)) lhOpenResult=iaTypefaces[iNumOfFonts].GetKptCodeTable(&ctbl);
      if(SUCCEEDED(lhOpenResult)) lhOpenResult=pFonts[iNumOfFonts].GetKptCodeTable(&ctbl);

      if(SUCCEEDED(lhOpenResult))
         switch(ctbl)
         {
         case 74: if(iStdWinFontIndex==RT_FONT_UNDEFINED) iStdWinFontIndex=iNumOfFonts; break;
         case 79: if(iCEFontIndex==RT_FONT_UNDEFINED) iCEFontIndex=iNumOfFonts; break;
         case 82: if(iPhonFontIndex==RT_FONT_UNDEFINED) iPhonFontIndex=iNumOfFonts; break;
         case 71: if(iLTFontIndex==RT_FONT_UNDEFINED) iLTFontIndex=iNumOfFonts; break;
         case 80: if(iLTAccFontIndex==RT_FONT_UNDEFINED) iLTAccFontIndex=iNumOfFonts; break;
         case 85: if(iSymbolFontIndex==RT_FONT_UNDEFINED) iSymbolFontIndex=iNumOfFonts; break;
         }
   }

   if(SUCCEEDED(lhOpenResult)) lhOpenResult=SetFont(0);
}


// --------------------------------------------------
TvRtfO_tag::~TvRtfO_tag()
{
   CloseFile(False);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutChar(Chars16 iOutch, bool bRtfFlag)
{
HRESULT retc=S_OK;
RT_FieldTypes fld_typ;
int cur_fnt;
bool font_defined;
// int rtf_tbl;
UC_Modes enc_mode;
int ctbl;
int new_ctbl;
int i_out_ch;
unsigned char out_ch;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if((pCurrentField==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if(((iOutch<0) || (iOutch>=C_CharSize0)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   i_out_ch=iOutch;
   switch(i_out_ch)
   {
   case C_hhyph: i_out_ch=C_hyph; break;
   case C_sbreak:
   case C_hSpc:
   case C_lSpc:
   case C_hlSpc:
      i_out_ch=C_Spc;
      break;
   case C_hbreak:
      i_out_ch=C_Lf;
      break;
   }

// --------------
   if((i_out_ch==RT_FieldStart) && SUCCEEDED(retc)) retc=PushField(&fld_typ, &cur_fnt);

// --------------
   if((i_out_ch==RT_FieldEnd) && SUCCEEDED(retc))
   {
      retc=PopField(&fld_typ, &cur_fnt);
      if(((fld_typ==RT_TT_Text) || (fld_typ==RT_TT_Table)) && SUCCEEDED(retc))
      {
         if(((cur_fnt>iNumOfFonts) || (cur_fnt<0)) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) retc=pFonts[cur_fnt].IsDefined(&font_defined);
         if((!font_defined) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=lpfRtfFile->GetEncoding(&enc_mode, &ctbl);

//       if(SUCCEEDED(retc)) retc=pFonts[cur_fnt].GetRtfCodeTable(&rtf_tbl);
//       if(SUCCEEDED(retc)) ctbl=ConvertRtf2KptCTbl(rtf_tbl);
//       if(SUCCEEDED(retc)) retc=iaTypefaces[cur_fnt].GetKptCodeTable(&ctbl);
         if(SUCCEEDED(retc)) retc=pFonts[cur_fnt].GetKptCodeTable(&ctbl);

         if(SUCCEEDED(retc)) retc=lpfRtfFile->SetEncoding(enc_mode, ctbl);
      }
   }

// --------------
   if(SUCCEEDED(retc))
   {
      if(i_out_ch==RC_KeywordStart) out_ch=RC_KeywordStart;
      else
      {
         if(SUCCEEDED(retc)) retc=lpfRtfFile->GetEncoding(&enc_mode, &ctbl);
         if(SUCCEEDED(retc)) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, ctbl);
      }
   }
   if(SUCCEEDED(retc))
   {
      if((out_ch>=KPT_FirstKptChar) && bRtfFlag) retc=PutKwrd(RT_TG_SpecChr, out_ch);
      else retc=lpfRtfFile->PutChar((Chars16)i_out_ch, False);
   }
   else if(retc==KP_E_UNKN_CHR)
   {
// ------------------- simbolio nera dabartineje lenteleje
// ieskom tinkancio fonto is lenteles
// paprastiems raidziu fontams negerai - keiciasi typeface
// paliekam tik simboliniu/fonetiniu fontu paieska
      cur_fnt=RT_FONT_UNDEFINED;

//    if(iLTFontIndex!=RT_FONT_UNDEFINED) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 71);
//    if(SUCCEEDED(retc)) cur_fnt=iLTFontIndex;
//    else if(retc==KP_E_UNKN_CHR)
      {

// if(i_out_ch==C_ph_acc)
// i_out_ch=C_ph_acc;

//       if(iStdWinFontIndex!=RT_FONT_UNDEFINED) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 74);
//       if(SUCCEEDED(retc)) cur_fnt=iStdWinFontIndex;
//       else if(retc==KP_E_UNKN_CHR)
         {
//          if(iCEFontIndex!=RT_FONT_UNDEFINED) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 79);
//          if(SUCCEEDED(retc)) cur_fnt=iCEFontIndex;
//          else if(retc==KP_E_UNKN_CHR)
            {
               if(iPhonFontIndex!=RT_FONT_UNDEFINED) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 82);
               if(SUCCEEDED(retc)) cur_fnt=iPhonFontIndex;
               else if(retc==KP_E_UNKN_CHR)
               {
//                if(iLTAccFontIndex!=RT_FONT_UNDEFINED) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 80);
//                if(SUCCEEDED(retc)) cur_fnt=iLTAccFontIndex;
//                else if(retc==KP_E_UNKN_CHR)
                  {
                     if(iSymbolFontIndex!=RT_FONT_UNDEFINED) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 85);
                     if(SUCCEEDED(retc)) cur_fnt=iSymbolFontIndex;
                     else if(retc==KP_E_UNKN_CHR)
                     {
#if FALSE // #ifdef Debug
unsigned char str_buf[100];
sprintf((char *)str_buf, "[%d]", i_out_ch);
KP_TRACE(str_buf);
#endif                        
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

                        retc=S_OK;
//                      cur_fnt=iLTFontIndex; // iStdWinFontIndex;
//                      i_out_ch=C_Quest;
                     }
                  }
               }
            }
         }
      }

// ------------------------------------------
      if(SUCCEEDED(retc))
      {
         if(cur_fnt!=RT_FONT_UNDEFINED)
         {
            if(SUCCEEDED(retc)) retc=OpenField();
            if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_Font, cur_fnt);
            if(SUCCEEDED(retc)) retc=PutChar((Chars16)i_out_ch, bRtfFlag);
            if(SUCCEEDED(retc)) retc=CloseField();
         }
         else
         {
// -------------- spec fontai netiko - keiciam kalba

            new_ctbl=0;
            if(ctbl!=71) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 71); // LT
            if(SUCCEEDED(retc)) new_ctbl=71;
            else if(retc==KP_E_UNKN_CHR)
            {
               if(ctbl!=74) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 74); // STD Win
               if(SUCCEEDED(retc)) new_ctbl=74;
//             else if(retc==KP_E_UNKN_CHR)
//             {
//                if(ctbl!=79) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 79); // CE - dar neaiski iaKpt2RtfLangCodesArr[]
//                if(SUCCEEDED(retc)) new_ctbl=79;
//                else if(retc==KP_E_UNKN_CHR)
//                {
//                   if(ctbl!=80) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 80); // LTAcc - dar neaiski iaKpt2RtfLangCodesArr[]
//                   if(SUCCEEDED(retc)) new_ctbl=80;
//                   else if(retc==KP_E_UNKN_CHR)
//                   {
//                      if(ctbl!=82) retc=KptCharDecode(&out_ch, (Chars16)i_out_ch, 82); // PhoneticTMUniv - dar neaiski iaKpt2RtfLangCodesArr[]
//                      if(SUCCEEDED(retc)) new_ctbl=82;
//                   }
//                }
//             }
            }

            if((new_ctbl!=0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=OpenField();
               if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_lang, iaKpt2RtfLangCodesArr[new_ctbl]);
               if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_langnp, iaKpt2RtfLangCodesArr[new_ctbl]);
               if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_SpecChr, out_ch);
               if(SUCCEEDED(retc)) retc=CloseField();
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, False, __FILE__, __LINE__, i_out_ch);
         }
      }
   }
   
return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutCharCrLf(Chars16 iOutch, bool bRtfFlag)
{
HRESULT retc=S_OK;

   switch(iOutch)
   {
   case C_Cr:
      retc=PutKwrd(RT_TG_line);
      if(SUCCEEDED(retc)) retc=PutChar(C_Lf, True);
      break;
   case C_Lf:
      retc=PutKwrd(RT_TG_Par);
      if(SUCCEEDED(retc)) retc=PutChar(iOutch, True);
      break;
   default: retc=PutChar(iOutch, bRtfFlag); break;
   }

return(retc);
}

// --------------------------------------------------
HRESULT TvRtfO_tag::OpenField(void)
{
HRESULT retc=S_OK;

   retc=PutChar((Chars16)RT_FieldStart, False);
//   iFldDepth+=1;

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::CloseField(void)
{
HRESULT retc=S_OK;

   retc=PutChar((Chars16)RT_FieldEnd, False);
//   if(iFldDepth>0) iFldDepth-=1;
//   else if(SUCCEEDED(retc))
//      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutKwrd(RT_TagIds iOutTag)
{
HRESULT retc=S_OK;

   if(((iOutTag<0) || (iOutTag>=RT_TG_NumOfTags00)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutChar((Chars16)RC_KeywordStart, False);
   if(SUCCEEDED(retc)) retc=PutStr(plpszaRtfTagTable[iOutTag]);

   if((iOutTag!=RT_TG_Ast) && SUCCEEDED(retc)) retc=PutChar(C_Spc, False);

//--------------------------
   if((iOutTag==RT_TG_FontTbl) && SUCCEEDED(retc)) retc=pCurrentField->SetFieldType(RT_TT_FontTable);

//--------------------------
   if((iOutTag==RT_TG_Font) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

//--------------------------
   if((iOutTag==RT_TG_SpecChr) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutKwrd(RT_TagIds iOutTag, int iPar)
{
HRESULT retc=S_OK;
unsigned char str_buf[80];
RT_FieldTypes fld_typ;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if((pCurrentField==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if(((iOutTag<0) || (iOutTag>=RT_TG_NumOfTags00)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=PutChar((Chars16)RC_KeywordStart, False);
   if(SUCCEEDED(retc)) retc=PutStr(plpszaRtfTagTable[iOutTag]);

   if(SUCCEEDED(retc))
   {
      str_buf[0]=Nul;
      if(iOutTag==RT_TG_SpecChr)
      {
         if((iPar<0) || (iPar>=KPT_Ctbsiz))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) sprintf((char *)str_buf, "%02x", iPar);
         if(SUCCEEDED(retc)) retc=PutStr(str_buf);
      }
      else
      {
         sprintf((char *)str_buf, "%d ", iPar);
         if(SUCCEEDED(retc)) retc=PutStr(str_buf);
//       if(SUCCEEDED(retc)) retc=PutChar(C_Spc);
      }
   }


//--------------------------
   if((iOutTag==RT_TG_FontTbl) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

//--------------------------
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&fld_typ);
   if((iOutTag==RT_TG_Font) && ((fld_typ==RT_TT_Text) || (fld_typ==RT_TT_Table)) && SUCCEEDED(retc))
      retc=SetFont(iPar);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutStr(const unsigned char *lpszOutStr)
{
HRESULT retc=S_OK;
// const unsigned char *pnts;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=lpfRtfFile->PutStr(lpszOutStr);

// pnts=lpszOutStr;
// if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc))
//    retc=PutChar((Chars16)(*pnts++), True);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutStrCtbl(const unsigned char *lpszOutStr, int iCtbl)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
Chars16 kpt_char;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   pnts=lpszOutStr;
   if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc))
   {
      retc=KptCharEncode(&kpt_char, (*pnts++), iCtbl);
      if(SUCCEEDED(retc)) retc=PutCharCrLf(kpt_char, True);
   }

// if(SUCCEEDED(retc)) retc=lpfRtfFile->PutStrCtbl(lpszOutStr, iCtbl);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::WriteHeader(RGB_Color *plColorTbl, int iSizeOfCtbl)
{
HRESULT retc=S_OK;
int ii;
bool font_defined;
RT_TagIds font_type;
unsigned char *fnam_ptr;
int rtf_ctbl;
// bool last_entry;

   retc=OpenField();

   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_Rtf, 1);
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_Ansi);
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_Deff, 0);
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_deftab, 720);
   if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False);

// fonttbl
   if(SUCCEEDED(retc)) retc=OpenField();
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_FontTbl);
   if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False);

   if(pFonts!=NULL) for(ii=0; (ii<iNumOfFonts) && SUCCEEDED(retc); ii++)
   {
//    retc=pFonts[ii].IsLast(&last_entry);
//    if(last_entry) break;

      if(SUCCEEDED(retc)) retc=pFonts[ii].IsDefined(&font_defined);
      if(font_defined && SUCCEEDED(retc))
      {
         retc=OpenField();
         if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_Font, ii);

         if(SUCCEEDED(retc)) retc=pFonts[ii].GetFontType(&font_type);
         if(SUCCEEDED(retc)) retc=PutKwrd(font_type);
//       if(SUCCEEDED(retc)) retc=PutChar(C_Spc, False);

// ------
// necessary for lizdynas, don't know what about regular RTF files
         if(SUCCEEDED(retc)) retc=pFonts[ii].GetRtfCodeTable(&rtf_ctbl);
         if(rtf_ctbl!=RT_NoCodeTable)
         {
            if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_CharSet, rtf_ctbl);
//          if(SUCCEEDED(retc)) retc=PutChar(C_Spc, False);
         }
// ------

         if(SUCCEEDED(retc)) retc=pFonts[ii].GetFontName(&fnam_ptr);
         if((fnam_ptr!=NULL) && SUCCEEDED(retc)) retc=PutStr(fnam_ptr);

         if(SUCCEEDED(retc)) retc=PutChar(C_Semic, False);

         if(SUCCEEDED(retc)) retc=CloseField();
         if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False);
      }
   }

   if(SUCCEEDED(retc)) retc=CloseField();
   if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False);

// colortbl
   if(SUCCEEDED(retc)) retc=OpenField();
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_ColorTbl);
   for(ii=0; ii<iSizeOfCtbl; ii++)
   {
      if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_red, plColorTbl[ii]&0xFF);
      if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_green, (plColorTbl[ii]&0xFF00)>>8);
      if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_blue, (plColorTbl[ii]&0xFF0000)>>16);
      if(SUCCEEDED(retc)) retc=PutChar(C_Semic, False);
   }
   if(SUCCEEDED(retc)) retc=CloseField();
   if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False);

// stylesheet
   if(SUCCEEDED(retc)) retc=PutStyleSheet();

// --------------------
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_DefLang, 1033);
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_pard);
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_plain);
   if(SUCCEEDED(retc)) retc=PutKwrd(RT_TG_fs, 24);
   if(SUCCEEDED(retc)) retc=PutChar(C_Lf, False);

// -------------------- // open first paragraph
   if(SUCCEEDED(retc)) retc=OpenField();

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::WriteTail(void)
{
HRESULT retc=S_OK;

   retc=CloseField(); // close last paragraph

   retc=CloseField(); // close file 

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::CloseFile(bool bCheckFileExist)
{
HRESULT retc=S_OK;

   if(lpfRtfFile!=NULL)
   {
      retc=lpfRtfFile->CloseFile(bCheckFileExist);
      KP_DELETE(lpfRtfFile);
   }
   else
   {
      retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         retc=KpErrorProc.OutputErrorMessage(retc, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);
   }

   lpfRtfFile=NULL;

return(retc);
}

// ==================================================
// --------------------------------------------------
HRESULT TvRtfO_tag::PutCharProc(Chars16 iOutch, bool bRtfFlag)
{
HRESULT retc=S_OK;

   switch(iOutch)
   {
   case '{': // RT_FieldStart
      retc=PutKwrd(RT_TG_left_curly);
      break;
   case '}': // RT_FieldEnd
      retc=PutKwrd(RT_TG_right_curly);
      break;
   
   case TX_SP_KeywordStart:
      retc=PutChar((Chars16)RC_KeywordStart, bRtfFlag);
      break;
   case TX_SP_FieldStart:
      retc=OpenField();
//    retc=PutChar((Chars16)RT_FieldStart, bRtfFlag);
      break;
   case TX_SP_FieldEnd:
      retc=CloseField();
//    retc=PutChar((Chars16)RT_FieldEnd, bRtfFlag);
      break;
   
   default:
      retc=PutCharCrLf(iOutch, bRtfFlag);
      break;
   }

return(retc);
}

// --------------------------------------------------
HRESULT TvRtfO_tag::PutStrProc(const unsigned char *lpszOutStr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   pnts=lpszOutStr;
   if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc))
      retc=PutCharProc((Chars16)(*pnts++), True);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfO_tag::PutIntStr(const Chars16 *lpaizOutStr, bool bRtfFlg)
{
HRESULT retc=S_OK;
const Chars16 *pnts;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, (const unsigned char *)"", True, __FILE__, __LINE__, 0L);

   pnts=lpaizOutStr;
   if(pnts!=NULL) while((*pnts) && SUCCEEDED(retc)) retc=PutCharProc(*pnts++, bRtfFlg);

return(retc);
}
