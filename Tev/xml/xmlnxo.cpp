// ==================================================
// xmlnx.cpp
// XML dictionary entry node TEX functions
// sustabdytas 2003.12.22 lvz03 projektui
//


// ==================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdlib.h>
#include <stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"

#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xml8.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlsty.h"
#include "xmln.h"


//-----------------------------------
int CvtToTex(int iInCh)
{
int out_chr=iInCh;

   switch(iInCh)
   {
   case C_Bpoint:             // bullet - anksciau buvo naudojamas vietoj TV_XM_CompDelim,
      out_chr=C_Nul;          //    dabar - homonimu ir kt. panasiu zodziu rusiavimui
      break;

   case TV_XM_CompDelim:      // '|'
      out_chr=TX_TG_BD;
      break;
   case TV_XM_CompBaseChar:   // '~'
      out_chr=TX_TG_BS;
      break;

   case C_Minus:              // '-'
      out_chr=TX_TG_dash;
      break;

   case C_LAapost:            // '\''
      out_chr=C_Apost;
      break;

   case C_ph_ae:
      out_chr=C_ae;
      break;
   case C_ph_g:
      out_chr=C_g;
      break;
   case C_ph_o_slash:
      out_chr=C_o_Slash;
      break;
   case C_ph_o_n:
      out_chr=C_o_Tilde;
      break;
   case C_ph_oe:
      out_chr=C_oe;
      break;

   case C_Cr:              // '\r'
      out_chr=C_hbreak;
      break;
   }

return(out_chr);
}

// ==================================== class XmlNode_tag methods
//-----------------------------------
HRESULT XmlNode_tag::PutTexChar(TvTexFile_tag *lpOutFile, int iOutChar, int *piLastChar, bool bTestLastChar, int iFatherTag, int *piCurCharPos, int iLastWordPos, int iLastWordRest, int *piDelayedChar)
{
HRESULT retc=S_OK;
bool last_char_simply_space=False;
bool out_char_simply_space=False;
bool last_char_space=False;
bool out_char_space=False;
bool last_char_punct=False;
bool out_char_punct=False;


// if((KpErrorProc.lMsgPar==183) && (iOutChar==C_Dots))
// KpErrorProc.lMsgPar=183;

// if((KpErrorProc.lMsgPar==24) && (iOutChar==C_sbreak))
// KpErrorProc.lMsgPar=24;

   if((lpOutFile==NULL) || (piLastChar==NULL) || (iFatherTag<XC_FirstDictTag) || (iFatherTag>=XC_LastDictTag))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(piDelayedChar!=NULL) *piDelayedChar=C_Nul;

   if(SUCCEEDED(retc))
   {
      if(TvIntStrChr((const int *)iazSimplySpaces, *piLastChar)!=NULL) last_char_simply_space=True;
      if(TvIntStrChr((const int *)iazSimplySpaces, iOutChar)!=NULL) out_char_simply_space=True;
      if(TvIntStrChr((const int *)iazSpaces, *piLastChar)!=NULL) last_char_space=True;
      if(TvIntStrChr((const int *)iazSpaces, iOutChar)!=NULL) out_char_space=True;
      if((TvIntStrChr((const int *)iazPunctuators, *piLastChar)!=NULL) && (*piLastChar!=C_Point)) // '.'
         last_char_punct=True;
      if(TvIntStrChr((const int *)iazPunctuators, iOutChar)!=NULL) out_char_punct=True;
   }

   if(last_char_simply_space /* last_char_space */ && (!out_char_space) &&
      (!out_char_punct) && SUCCEEDED(retc))
   {
      retc=lpOutFile->PutCharProc(*piLastChar, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//    *piLastChar=C_Nul;
   }

// if(iOutChar==C_QemSpc)
// iOutChar=C_QemSpc;

   if(SUCCEEDED(retc))
   {
      if(
         (
            (!out_char_punct) ||
            (!last_char_punct) ||
//          ((*piLastChar==C_Point) && (iOutChar==C_Comma)) || // delimiters between labels
            (!bTestLastChar)
         ) &&
         (!out_char_simply_space) // (!out_char_space)
        )
      {
         if(iOutChar==C_sbreak)
         {
            if(SUCCEEDED(retc)) 
               if(iaXml2Tex[iFatherTag-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                        retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
            
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iOutChar, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if(SUCCEEDED(retc)) 
               if(iaXml2Tex[iFatherTag-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                     {
                        if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iaXml2Tex[iFatherTag-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                     }
         }
         else
         {
// if(iOutChar=='.')
// iOutChar='.';

            if(SUCCEEDED(retc)) 
            {
               if(piDelayedChar!=NULL)
                  *piDelayedChar=iOutChar;
               else
                  retc=lpOutFile->PutCharProc(iOutChar, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }
         }
//       *piLastChar=iOutChar;
      }

   if((!last_char_space) || (!out_char_simply_space /* !out_char_space */))
      *piLastChar=iOutChar;
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode_tag::PutTexIntStr(TvTexFile_tag *lpOutFile, const int *iaOutStr, int *piLastChar, int iFatherTag, XmlNode_tag *pnCurNode, bool bTagFormat, int *piCurCharPos, int iLastWordPos, int iNumOfChars, int iLastWordRest)
{
const int *pnts;
int out_chr;
HRESULT retc=S_OK;
bool test_last_char=True;
unsigned char *ind_ptr=(unsigned char *)"";
int start_pos;
int cur_pos;
int ii;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned char *pntd;

   if((lpOutFile==NULL) || (iaOutStr==NULL) || (piLastChar==NULL) || (pnCurNode==NULL) || (iFatherTag<XC_FirstDictTag) || (iFatherTag>=XC_LastDictTag) || (piCurCharPos==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      retc=pnCurNode->GetIndentPtr(&ind_ptr);
      if(ind_ptr==NULL) ind_ptr=(unsigned char *)"";
   }

   if(SUCCEEDED(retc))
   {
      start_pos=((strlen(ind_ptr)/XN_POS_PER_INDENT-1) + XN_VAL_START_TAB) * XN_POS_PER_TAB;
      cur_pos=start_pos;
   }

   pnts=iaOutStr;
   while((*pnts) && SUCCEEDED(retc))
   {
      if((*(pnts+1)=='\"') && (iFatherTag!=XC_TechNote))
      {
         if(SUCCEEDED(retc)) if((*piCurCharPos==iLastWordPos) && (iLastWordPos>0))
         {
//          if(TvStrChr(lpszSpcEol, *pnts)==NULL)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#ifdef AUTO_LASTWORD
            if(SUCCEEDED(retc))
               retc=PutTexChar(lpOutFile, C_sbreak, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
#endif
         }
         if(SUCCEEDED(retc)) (*piCurCharPos)++;
         if(SUCCEEDED(retc)) if(*piCurCharPos==iLastWordPos)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) (*piCurCharPos)++;

// invert diaresis
         if(*pnts==C_Minus)
         {
            retc=PutTexChar(lpOutFile, TX_TG_dtb, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
            test_last_char=False;
            pnts+=2;
         }
         else
         {
            retc=PutTexChar(lpOutFile, C_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
            test_last_char=False;
            if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, *pnts++, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
            pnts++;
         }
      }
      else if(*pnts==NS_CTRL_START) // '$' // if((*(pnts+1)=='\"') && (iFatherTag!=XC_TechNote))
      {
         pntd=sty_buf;
         (*pntd++)=(*pnts++);
         (*pntd++)=(*pnts++);
         switch(*(pnts-1))
         {
// font style
         case 'f':
            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++)
               (*pntd++)=(*pnts++);
            break;

// paragraph style
         case 's':
            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++)
               (*pntd++)=(*pnts++);
            break;

// unicode character
         case 'u':
            for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((Chars16)(*pnts))); ii++)
               (*pntd++)=(*pnts++);
            break;
         
// condensed font
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++)
               (*pntd++)=(*pnts++);
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
            break;
         }

         if(SUCCEEDED(retc))
         {
            *pntd=Nul;
            retc=WriteTexDelim(lpOutFile, sty_buf, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
         }
      }
      else // if(*pnts==NS_CTRL_START) // '$' // if((*(pnts+1)=='\"') && (iFatherTag!=XC_TechNote))
      {
         if(SUCCEEDED(retc)) if((*piCurCharPos==iLastWordPos) && (iLastWordPos>0))
         {

// if(KpErrorProc.lMsgPar==406)
// KpErrorProc.lMsgPar=406;

//          if(TvStrChr(lpszSpcEol, *pnts)==NULL)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#ifdef AUTO_LASTWORD
            if(SUCCEEDED(retc))
               retc=PutTexChar(lpOutFile, C_sbreak, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
#endif
         }
         if(SUCCEEDED(retc)) (*piCurCharPos)++;

         out_chr=(*pnts++);

         if((TvStrChr(lpszSpaces, out_chr)!=NULL) && (cur_pos>=XN_POS_PER_COL-8) && 
            (*piCurCharPos < iLastWordPos /* iNumOfChars-LAST_WORD_LEN */) && bTagFormat)
         {
            if(SUCCEEDED(retc))
               if(iaXml2Tex[iFatherTag-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                        retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_cr, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_Lf, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_plus, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if((ind_ptr!=NULL) && SUCCEEDED(retc))
               for(ii=0; (ii<start_pos/XN_POS_PER_TAB-1) && SUCCEEDED(retc); ii++)
                  retc=lpOutFile->PutCharProc(TX_SP_Amp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            
            if(SUCCEEDED(retc))
               if(iaXml2Tex[iFatherTag-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[iFatherTag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                     {
                        if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iaXml2Tex[iFatherTag-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                     }

            cur_pos=start_pos;
         }
         else
         {
            cur_pos++;

if(out_chr=='}')
out_chr='}';

            out_chr=CvtToTex(out_chr);

            switch(out_chr)
            {
            case C_hbreak:
               retc=PutTexChar(lpOutFile, TX_TG_hfill, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               out_chr=C_break;
               break;

            case C_hhyph:
               retc=PutTexChar(lpOutFile, C_Minus, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               out_chr=C_break;
               break;

#ifdef AUTO_LASTWORD
//          case C_Spc:
//             if(*piCurCharPos>=iNumOfChars-LAST_WORD_LEN)
//                out_chr=C_NBSP;
//             break;

//          case C_EnSpc:
//          case C_QemSpc:
//             if(*piCurCharPos>=iNumOfChars-LAST_WORD_LEN)
//             {
//                retc=PutTexChar(lpOutFile, C_NBSP, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
//                out_chr=C_NBSP;
//             }
//             break;

            case C_lSpc:
               if(*piCurCharPos>=iNumOfChars-LAST_WORD_LEN)
                  out_chr=C_NBSP;
               else
                  out_chr=C_Spc;
               break;

            case C_hlSpc:
               if(*piCurCharPos>=iNumOfChars-LAST_WORD_LEN)
                  out_chr=C_NBSP;
               else
                  out_chr=C_hSpc;
               break;
#endif
            }

// convert italic parentheses to straight
            if(SUCCEEDED(retc)) switch(out_chr)
            {
            case C_Lpar:              // '('
            case C_Rpar:              // ')'
            case C_Lbrack:            // '['
            case C_Rbrack:            // ']'
#ifdef BOLD_IT_EXAMPLES
               if((iFatherTag==XC_Example) || (iFatherTag==XC_Idiom) || 
                  (iFatherTag==XC_Struct) || (iFatherTag==XC_OblStruct))
                 {
                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_FS, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc('d', TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, out_chr, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
               }
               else 
#endif
               if((iFatherTag==XC_ExplSrc) || (iFatherTag==XC_ExplDst))
               {
                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_FS, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc('1', TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, out_chr, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
               }
               else
                  retc=PutTexChar(lpOutFile, out_chr, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               break;

#ifdef AUTO_LASTWORD
            case C_sbreak:
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, False, __FILE__, __LINE__, 0L);
               break;
#endif

            default:
               retc=PutTexChar(lpOutFile, out_chr, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               break;
            }
            test_last_char=False; // =True; !!! ???
         
         } // else // if((TvStrChr(lpszSpaces, out_chr)!=NULL) && (cur_pos>=XN_POS_PER_COL-5) && bTagFormat)
      
      } // else // if(*pnts==NS_CTRL_START) // '$' // if((*(pnts+1)=='\"') && (iFatherTag!=XC_TechNote))

   } // while((*pnts) && SUCCEEDED(retc))

return(retc);
}


//-----------------------------------
// font style code for TeX command TX_TG_FS (\FS)
int CalcStyCode(KPS_FontStyles iStyNo)
{
int sty_code='0';

   if(iStyNo<10) sty_code=iStyNo+'0';
   else
   {
      if(iStyNo<10+'Z'-'A'+1) sty_code=iStyNo+'A'-10;
      else sty_code=iStyNo+'a'-(10+'Z'-'A'+1);
   }

return(sty_code);
}


//-----------------------------------
// iazOutBuf[KP_MAX_FILE_LIN_LEN+1]
// lpszFormatStr - formato eilute is lpszXmlTagDelimiters[][]
// derint su SkipDelimCtrlChars()
HRESULT XmlNode_tag::GenTexDelimStr(int *iazOutBuf, const unsigned char *lpszFormatStr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
int *pntd;
int sty_no;
bool font_changed=False;
// int code_table=NS_DELIM_CTBL;
// int font_id;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned int uni_code;
int cond_fnt;
int ii;

   if((lpszFormatStr==NULL) || (iazOutBuf==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszFormatStr)>=KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   pntd=iazOutBuf;
   pnts=lpszFormatStr;

   while((*pnts) && SUCCEEDED(retc))
   {
      if(*pnts==NS_CTRL_START)   // '$'
      {
         pnts++;
         switch(*pnts++)
         {
// font style
         case 'f':
            font_changed=True;

            strcpy(sty_buf, pnts);
            sty_buf[NS_STY_NO_WDT]=Nul;
            sty_no=(-1);
            sscanf((char *)sty_buf, "%d", &sty_no);

            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;

            if((sty_no<0) || (sty_no>=KPS_NumOfFontStyles00))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

//          if(SUCCEEDED(retc))
//          {
//             font_id=aFontStyles[sty_no].GetTypeface();
//             if((font_id<0) || (font_id>=KPT_NumOfTypefaces0))
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
//          }
//          if(SUCCEEDED(retc))
//             retc=iaTypefaces[font_id].GetKptCodeTable(&code_table);

            if(SUCCEEDED(retc)) if(((pntd-iazOutBuf)+1+MAX_LONG_DIGITS+1+1)>=KP_MAX_FILE_LIN_LEN) 
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            
            if(((sty_no<0) || (sty_no>=10+'Z'-'A'+1+'z'-'a'+1)) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               *(pntd++)=TX_TG_FS;
               *(pntd++)=CalcStyCode((KPS_FontStyles)sty_no);
               *(pntd++)=C_hSpc;
            }

            break;

// paragraph style
         case 's':
            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;
            break;

// unicode character
         case 'u':
            if((((pntd-iazOutBuf)+1+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc)) 
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               strcpy(sty_buf, pnts);
               sty_buf[NS_UNI_CODE_WDT]=Nul;
               uni_code=(-1);
               sscanf((char *)sty_buf, "%x", &uni_code);

               for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((Chars16)(*pnts))); ii++) pnts++;

               if((uni_code>=KPT_UniPrivateStart) && (uni_code<=KPT_UniPrivateEnd))
                  ii=uni_code-KPT_UniPrivateStart;
               else
               {
                  for(ii=0; ii<C_CharSize0; ii++)
                     if(iaUniChars[ii]==uni_code) break;
               }

               if(((ii<0) || (ii>=C_CharSize0)) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) *(pntd++)=ii;
            break;
         
// condensed font
         case 'q':
            strcpy(sty_buf, pnts);
            sty_buf[NS_COND_FNT_WDT]=Nul;
            cond_fnt=0;
            sscanf((char *)sty_buf, "%d", &cond_fnt);

            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;

            if((cond_fnt<0) || (cond_fnt>=100)) // 9.9 pt - max condension
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) if(((pntd-iazOutBuf)+1+MAX_LONG_DIGITS+1+1)>=KP_MAX_FILE_LIN_LEN) 
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            
            if(SUCCEEDED(retc))
            {
               cond_fnt=(cond_fnt*10)+117; // 1.17 pt (0.85 pt ?) - no condension

// \fontdimen4\timacn=1.23pt // shrink interword
               *(pntd++)=TX_TG_fontdimen;
               *(pntd++)=C_4; // '4'
               *(pntd++)=TX_TG_timacn;
               *(pntd++)=TX_SP_Eq; // C_Eq; // '='
               *(pntd++)=C_0 + (cond_fnt/100); cond_fnt%=100;
               *(pntd++)=C_Point; // '.'
               *(pntd++)=C_0 + (cond_fnt/10); cond_fnt%=10;
               *(pntd++)=C_0 + cond_fnt;
               *(pntd++)=C_p;
               *(pntd++)=C_t;
               *(pntd++)=C_hSpc;
            }

            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
            break;
         }
      }
      else
      {
         if((((pntd-iazOutBuf)+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc)) 
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            retc=KptCharEncode((Chars16 *)pntd++, *pnts++, iDelimCtbl /* NS_DELIM_CTBL */ /* code_table */);
            if(FAILED(retc))
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         }
      }
   }

   if(font_changed && SUCCEEDED(retc))
   {
      *(pntd++)=TX_TG_FS;
      *(pntd++)=CalcStyCode(NS_DEFAULT_TEXT_STYLE);
      *(pntd++)=C_hSpc;
   }

   if(SUCCEEDED(retc)) *pntd=Nul;

return(retc);
}


//-----------------------------------
HRESULT XmlNode_tag::WriteTexDelim(TvTexFile_tag *lpOutFile, const unsigned char *lpszDelimStr,
                                   int *piLastChar, int *piCurCharPos,
                                   int iLastWordPos, int iLastWordRest, int iNumOfChars)
{
HRESULT retc=S_OK;
int str_len;
bool new_par=False;
unsigned char delim_str1[KP_MAX_FILE_LIN_LEN+1];
unsigned char delim_str2[KP_MAX_FILE_LIN_LEN+1];
int i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
const unsigned char *lf_ptr;
// const int *pnti;
// int ii;
// int tmp_str[KP_MAX_FILE_LIN_WDT+1];

   if((lpOutFile==NULL) || (lpszDelimStr==NULL) || (piLastChar==NULL) || (piCurCharPos==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszDelimStr)>=KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) lf_ptr=strchr(lpszDelimStr, C_Lf);
   if((lf_ptr!=NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc))
      {
         strcpy(delim_str1, lpszDelimStr);
         delim_str1[lf_ptr-lpszDelimStr]=Nul;
         strcpy(delim_str2, lf_ptr+1);
         retc=WriteTexDelim(lpOutFile, delim_str1, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
         if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, Lf, piLastChar, True, XC_PunctMark, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

#ifdef AUTO_LASTWORD
         if(SUCCEEDED(retc)) if((*piCurCharPos==iLastWordPos) && (iLastWordPos>0))
            retc=PutTexChar(lpOutFile, C_sbreak, piLastChar, True, XC_PunctMark, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
#endif
         if(SUCCEEDED(retc)) (*piCurCharPos)++;

// printf("6---- %d\n", 1);

         if(SUCCEEDED(retc)) retc=WriteTexDelim(lpOutFile, delim_str2, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
      }
   }
   else
   {
      strcpy(delim_str1, lpszDelimStr);

      new_par=False;
      str_len=strlen(delim_str1);
//    if(str_len>0)
//    {
//       if(delim_str1[str_len-1]==Spc)
//       {
//          new_par=True;
//          delim_str1[--str_len]=Nul;
//       }
//    }

      if(SUCCEEDED(retc)) retc=GenTexDelimStr(i_delim_buf, delim_str1);

// if(((TvIntStrLen(i_delim_buf)==7) || (TvIntStrLen(i_delim_buf)==8)) && (KpErrorProc.lMsgPar==19))
// retc=retc;

      if(SUCCEEDED(retc))
      {
         if(TvIntStrLen(i_delim_buf)>0)
         {

//       TvIntStrNCpy(tmp_str, i_delim_buf, KP_MAX_FILE_LIN_WDT);
//       tmp_str[KP_MAX_FILE_LIN_WDT]=C_Nul;
//       retc=CutInitTrailSpcsInt(tmp_str);
//       if(SUCCEEDED(retc))
//       {
//          ii=TvIntStrLen(tmp_str);
//          if(ii>0)
            {
               if(SUCCEEDED(retc)) 
                  if(iaXml2Tex[XC_PunctMark-XC_FirstDictTag]!=NULL)
                     if(plpszaUserTexTagTable[iaXml2Tex[XC_PunctMark-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                        if(strlen(plpszaUserTexTagTable[iaXml2Tex[XC_PunctMark-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                        {
                           if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iaXml2Tex[XC_PunctMark-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                           if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                        }
            }

            if(SUCCEEDED(retc))
            {
               retc=PutTexIntStr(lpOutFile, i_delim_buf, piLastChar, XC_PunctMark, this, False, piCurCharPos, iLastWordPos, iNumOfChars, iLastWordRest);

// (*piCurCharPos)+=TvIntStrLen(i_delim_buf);

// printf("4---- %d\n", TvIntStrLen(i_delim_buf));
// if((TvIntStrLen(i_delim_buf)==7) && (KpErrorProc.lMsgPar==19))
// retc=retc;

//             pnti=i_delim_buf;
//             while((*pnti) && SUCCEEDED(retc))
//             {
//                retc=lpOutFile->PutCharProc(*pnti++, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//                (*piCurCharPos)++;
//             }

            }

            if(SUCCEEDED(retc))
               if(iaXml2Tex[XC_PunctMark-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[XC_PunctMark-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[XC_PunctMark-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
//                      if(ii>0)
                           retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
         }

      } // if(SUCCEEDED(retc))              

      if(new_par && SUCCEEDED(retc))
      {
         if(*piLastChar!=C_Nul)
         {
//          if(TvIntStrChr((const int *)iazSpcEol, *piLastChar)==NULL)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            retc=lpOutFile->PutChar(C_Lf, (*piCurCharPos < iLastWordPos));
         }
         *piLastChar=C_Nul;
      }
   
   } // else // if(lf_ptr!=NULL)

return(retc);
}


//-----------------------------------
// destroys iPrevOutTag
HRESULT XmlNode_tag::WriteTex(TvTexFile_tag *lpOutFile, int *piCurCharPos,
                              int iLastWordPos, int iLastWordRest, int iNumOfChars,
                              int iFatherTag, int iFirstTag, int iPrevTag, int *piLastChar,
                              bool bTagFormat)
{
HRESULT retc=S_OK;
XmlNode_tag *loop_brother;
XmlNode_tag *br1;
XmlNode_tag *br2;
XmlNode_tag *first_child;
XmlTagPars_tag *tag_pars;
const int /* const Chars16 */ *cont_ptr;
int cur_tag=C_Nul;

unsigned char *delim_str = new unsigned char [MAX_XML_PAR_VAL_LEN + 1];
   KP_ASSERT(delim_str != null, KP_E_OUTOFMEM, null, True);
unsigned char *par_str = new unsigned char [MAX_XML_PAR_VAL_LEN + 1];
   KP_ASSERT(par_str != null, KP_E_OUTOFMEM, null, True);

int par_num;
int ii;
const unsigned char *delim_ptr=(unsigned char *)"";
XmlTagPars_tag *par_ptr;
unsigned char *ind_ptr;
int fath_sty_tag;
bool last_w_fl;
int delayed_char=C_Nul;
// int tmp_str[KP_MAX_FILE_LIN_WDT+1];

   if((lpOutFile==NULL) || (iFatherTag<XC_FirstDictTag) || (iFatherTag>=XC_LastDictTag) || (piCurCharPos==NULL) || (piLastChar==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   fath_sty_tag=iFatherTag;
   if((fath_sty_tag==XC_Reference) && bTagFormat) fath_sty_tag=XC_HeadWord;

   iPrevOutTag=iPrevTag;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);

// if(cur_tag==XC_PartOfSpeechSrc)
// cur_tag=XC_PartOfSpeechSrc;
         
// if(KpErrorProc.lMsgPar==167)
// KpErrorProc.lMsgPar=167;

// -------------
      if((cur_tag==XC_StEntry) && SUCCEEDED(retc))
      {
         if(bTagFormat && SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));

         retc=GetTagParsPtr(&par_ptr);
         if((par_ptr==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
            retc=par_ptr->SeekTextPar("id", par_str, &par_num);

         if(SUCCEEDED(retc))
            if(iaXml2Tex[cur_tag-XC_FirstDictTag]!=NULL)
               if(plpszaUserTexTagTable[iaXml2Tex[cur_tag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                  if(strlen(plpszaUserTexTagTable[iaXml2Tex[cur_tag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                  {
                     if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iaXml2Tex[cur_tag-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

                     if(SUCCEEDED(retc))
                        if(iaUserTexTagArgs[iaXml2Tex[cur_tag-XC_FirstDictTag]-TX_FirstUserTagCode]>0)
                           retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  }
         if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);

         if(SUCCEEDED(retc))
            if(iaXml2Tex[cur_tag-XC_FirstDictTag]!=NULL)
               if(plpszaUserTexTagTable[iaXml2Tex[cur_tag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                  if(strlen(plpszaUserTexTagTable[iaXml2Tex[cur_tag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                     if(iaUserTexTagArgs[iaXml2Tex[cur_tag-XC_FirstDictTag]-TX_FirstUserTagCode]>0)
                        retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));

         if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));
      }

      if(!bTagFormat)
      {
// delimiters
         delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(iPrevOutTag-iFirstTag)/2][(cur_tag-iFirstTag)/2];
         if(delim_ptr==NULL) delim_ptr=(unsigned char *)"";

         if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, delim_ptr, cur_tag, tag_pars);

         if(SUCCEEDED(retc)) retc=WriteTexDelim(lpOutFile, delim_str, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
      }
      else
      {
// Tag names for tagged format
         if((plpszaTagOutNames[cur_tag-XC_FirstDictTag]==NULL) && SUCCEEDED(retc))
            retc=loop_brother->ReduceIndentNested();

         if(SUCCEEDED(retc)) retc=loop_brother->GetPrevBrother(&br1);
         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&br2);
         if(
            ((cur_tag!=XC_Text) || (br1!=NULL) || (br2!=NULL)) &&
            (plpszaTagOutNames[cur_tag-XC_FirstDictTag]!=NULL) &&
            SUCCEEDED(retc)
           )
         {
            if(cur_tag!=XC_StEntry)
            {
               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_cr, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_break, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_plus, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if(SUCCEEDED(retc)) retc=loop_brother->GetIndentPtr(&ind_ptr);
            if((ind_ptr!=NULL) && SUCCEEDED(retc))
               for(ii=0; (ii<(int)strlen(ind_ptr)/XN_POS_PER_INDENT-1) && SUCCEEDED(retc); ii++)
                  retc=lpOutFile->PutCharProc(TX_SP_Amp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if(SUCCEEDED(retc))
               if(iaXml2Tex[XC_FwNote-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[XC_FwNote-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[XC_FwNote-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                     {
                        if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iaXml2Tex[XC_FwNote-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                     }
            
            if(SUCCEEDED(retc))
            {
               if(cur_tag!=XC_StEntry)
               {
                  if(SUCCEEDED(retc))
                  {
                     switch(cur_tag)
                     {
                     case XC_Asterix:
                        retc=lpOutFile->PutStr(plpszaTagOutNames[XC_Symb-XC_FirstDictTag], (*piCurCharPos < iLastWordPos));
                        break;
                     default:
                        retc=lpOutFile->PutStr(plpszaTagOutNames[cur_tag-XC_FirstDictTag], (*piCurCharPos < iLastWordPos));
                        break;
                     }
                  }
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Colon, (*piCurCharPos < iLastWordPos));
//                if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Spc, (*piCurCharPos < iLastWordPos));
//                if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Tab, (*piCurCharPos < iLastWordPos));
               }
               else retc=lpOutFile->PutCharProc(TX_TG_forc_sp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }

            if(SUCCEEDED(retc)) 
               if(iaXml2Tex[XC_FwNote-XC_FirstDictTag]!=NULL)
                  if(plpszaUserTexTagTable[iaXml2Tex[XC_FwNote-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                     if(strlen(plpszaUserTexTagTable[iaXml2Tex[XC_FwNote-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                        retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));

            for(ii=0; (ii<XN_VAL_START_TAB) && SUCCEEDED(retc); ii++)
               retc=lpOutFile->PutCharProc(TX_SP_Amp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if((cur_tag==XC_Asterix) && SUCCEEDED(retc))
               if(iaXml2Tex[cur_tag-XC_FirstDictTag]!=NULL)
                  retc=lpOutFile->PutCharProc(iaXml2Tex[cur_tag-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
         }
      }

      iPrevOutTag=cur_tag;

// contents start
      if(SUCCEEDED(retc)) retc=loop_brother->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr((const Chars16 **)&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc)) 
      {
         if(cur_tag==XC_Paragraph) retc=first_child->WriteTex(lpOutFile, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars, iFatherTag, iFirstTag, XC_Nul, piLastChar, bTagFormat);
         else retc=first_child->WriteTex(lpOutFile, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars, cur_tag, iFirstTag, XC_Nul, piLastChar, bTagFormat);
      }

// current tag
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XC_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// contents
         if(SUCCEEDED(retc))
         {
//          if(iFatherTag!=XC_TechNote)
            {
               if(iaXml2Tex[fath_sty_tag-XC_FirstDictTag]==C_Nul)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, (const unsigned char *)"Laisvas tekstas", FALSE, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
               {
//                TvIntStrNCpy(tmp_str, cont_ptr, KP_MAX_FILE_LIN_WDT);
//                tmp_str[KP_MAX_FILE_LIN_WDT]=C_Nul;
//                retc=CutInitTrailSpcsInt(tmp_str);
                  if(SUCCEEDED(retc))
                  {
// flush spaces
//                   delayed_char=C_Nul;
//                   retc=PutTexChar(lpOutFile, *cont_ptr, piLastChar, True, fath_sty_tag,
//                      piCurCharPos, iLastWordPos, iLastWordRest, &delayed_char);

//                   ii=TvIntStrLen(tmp_str);
//                   if(iaXml2Tex[fath_sty_tag-XC_FirstDictTag]==C_Nul) ii=0;

//                   if(ii>0)
                        if(iaXml2Tex[fath_sty_tag-XC_FirstDictTag]!=NULL)
                           if(plpszaUserTexTagTable[iaXml2Tex[fath_sty_tag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                              if(strlen(plpszaUserTexTagTable[iaXml2Tex[fath_sty_tag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                              {
//                               if(SUCCEEDED(retc)) retc=lpOutFile->FlushSpaces(*piCurCharPos < iLastWordPos);
                                 if(SUCCEEDED(retc))
                                    retc=lpOutFile->PutCharProc(iaXml2Tex[fath_sty_tag-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                                 if(SUCCEEDED(retc))
                                    if(iaUserTexTagArgs[iaXml2Tex[fath_sty_tag-XC_FirstDictTag]-TX_FirstUserTagCode]>0)
                                       retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                              }

//                   if((delayed_char!=C_Nul) && SUCCEEDED(retc))
//                   {
//                      (*piCurCharPos)++;
//                      retc=lpOutFile->PutCharProc(delayed_char, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//                   }

                     if(SUCCEEDED(retc))
                     {
                        if(*cont_ptr!=C_Nul)
                           retc=PutTexIntStr(lpOutFile, cont_ptr /*+1 */, piLastChar, fath_sty_tag, 
                              loop_brother, bTagFormat, piCurCharPos, iLastWordPos, iNumOfChars,
                              iLastWordRest);
                     }

// (*piCurCharPos)+=TvIntStrLen(cont_ptr);

// printf("5---- %d\n", TvIntStrLen(cont_ptr));

//                   if(ii>0)
                        if(SUCCEEDED(retc)) 
                           if(iaXml2Tex[fath_sty_tag-XC_FirstDictTag]!=NULL)
                              if(plpszaUserTexTagTable[iaXml2Tex[fath_sty_tag-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
                                 if(strlen(plpszaUserTexTagTable[iaXml2Tex[fath_sty_tag-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
                                    if(iaUserTexTagArgs[iaXml2Tex[fath_sty_tag-XC_FirstDictTag]-TX_FirstUserTagCode]>0)
                                       retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
                  }
               }
            }
         }
      }

// to next brother
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

// -------------
   if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc))
   {
      retc=lpOutFile->GetLastWordInParFl(&last_w_fl);
      if(last_w_fl && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(False, (*piCurCharPos < iLastWordPos));
         if(SUCCEEDED(retc)) retc=lpOutFile->SetLastWordInParFl(False);
      }

      if(bTagFormat && SUCCEEDED(retc))
         retc=lpOutFile->PutCharProc(TX_TG_cr, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
      
      if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));

      if(SUCCEEDED(retc)) 
         if(iaXml2Tex[XC_StEntry_e-XC_FirstDictTag]!=NULL)
            if(plpszaUserTexTagTable[iaXml2Tex[XC_StEntry_e-XC_FirstDictTag]-TX_FirstUserTagCode]!=NULL)
               if(strlen(plpszaUserTexTagTable[iaXml2Tex[XC_StEntry_e-XC_FirstDictTag]-TX_FirstUserTagCode])>0)
               {
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iaXml2Tex[XC_StEntry_e-XC_FirstDictTag], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
               }

      if(SUCCEEDED(retc)) if(*piLastChar!=C_Nul)
      {
//       if(TvIntStrChr((const int *)iazSpaces, *piLastChar)==NULL)
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         *piLastChar=C_Nul;
      }
   }

// last tag in group - delimiter
   if((!bTagFormat || (cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup)) && SUCCEEDED(retc))
   {
      delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(cur_tag-iFirstTag)/2][(XC_Nul-iFirstTag)/2];
      if(delim_ptr==NULL) delim_ptr=(unsigned char *)"";
   
      if(SUCCEEDED(retc))
         if(strlen(delim_ptr)>=KP_MAX_FILE_LIN_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) strcpy(delim_str, delim_ptr);

      if(SUCCEEDED(retc)) retc=WriteTexDelim(lpOutFile, delim_str, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
   }

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc))
//    retc=pNextBrother->WriteTex(lpOutFile, piCurCharPos, iLastWordPos, iLastWordRest, cur_tag, iFirstTag, cur_tag, piLastChar, bTagFormat, iLastWordRest);

   KP_DELETEA(delim_str);
   KP_DELETEA(par_str);

return(retc);
}

//-----------------------------------
HRESULT XmlNode_tag::CountCharactersTex(int *piNumOfChars, int iFirstTag, int iPrevTag, bool bTagFormat)
{
HRESULT retc=S_OK;
XmlNode_tag *loop_brother;
XmlNode_tag *first_child;
const int /* const Chars16 */ *cont_ptr;
int cur_tag=C_Nul;
XmlTagPars_tag *tag_pars;
const unsigned char *delim_ptr=(unsigned char *)"";

   iPrevOutTag=iPrevTag;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);

// delimiters
      if((!bTagFormat) && SUCCEEDED(retc))
      {
         delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(iPrevOutTag-iFirstTag)/2][(cur_tag-iFirstTag)/2];
         if((delim_ptr!=NULL) && SUCCEEDED(retc))
         {
            *piNumOfChars+=DelimStrLenTex(delim_ptr, cur_tag, tag_pars);

// int ii;
// printf("1---- %d\n", DelimStrLenTex(delim_ptr, cur_tag, tag_pars));
// if((DelimStrLenTex(delim_ptr, cur_tag, tag_pars)==8) && (KpErrorProc.lMsgPar==19))
// ii=DelimStrLenTex(delim_ptr, cur_tag, tag_pars);

         }
      }

      iPrevOutTag=cur_tag;

// contents start
      if(SUCCEEDED(retc)) retc=loop_brother->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr((const Chars16 **)&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc))
         retc=first_child->CountCharactersTex(piNumOfChars, iFirstTag, XC_Nul, bTagFormat);

// contents
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XC_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            *piNumOfChars+=XmlnIntStrLen(cont_ptr);

// printf("2---- %d\n", TvIntStrLen(cont_ptr));

         }
      }

// to next brother
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))


// last tag in group - delimiter
   if((!bTagFormat || (cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup)) && SUCCEEDED(retc))
   {
      delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(cur_tag-iFirstTag)/2][(XC_Nul-iFirstTag)/2];
      if((delim_ptr!=NULL) && SUCCEEDED(retc)) 
      {
         *piNumOfChars+=DelimStrLenTex(delim_ptr, XC_Nul, NULL);

// printf("3---- %d\n", DelimStrLenTex(delim_ptr, XC_Nul, NULL));

      }
   }

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->CountCharacters(piNumOfChars, iFirstTag, cur_tag, bTagFormat);

return(retc);
}


//-----------------------------------
HRESULT XmlNode_tag::GetLastWordPosTex(int *piLastWordPos, int *piLastWordRest, int *piCurCharPos, int iNumOfChars, int iFirstTag, int iPrevTag, bool bTagFormat)
{
HRESULT retc=S_OK;
XmlNode_tag *loop_brother;
XmlNode_tag *first_child;
const int /* const Chars16 */ *cont_ptr;
int cur_tag=C_Nul;
XmlTagPars_tag *tag_pars;
const unsigned char *delim_ptr=(unsigned char *)"";
const int *pnti;
int i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned char delim_str[KP_MAX_FILE_LIN_LEN+1];
int ii;

   if((piLastWordPos==NULL) || (piLastWordRest==NULL) || (piCurCharPos==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   iPrevOutTag=iPrevTag;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);

      if(*piCurCharPos<iNumOfChars-LAST_WORD_RECOGN_PTR) *piLastWordPos=*piCurCharPos;

// delimiters
      if((!bTagFormat) && SUCCEEDED(retc))
      {
         delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(iPrevOutTag-iFirstTag)/2][(cur_tag-iFirstTag)/2];
         if((delim_ptr!=NULL) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, delim_ptr, cur_tag, tag_pars);
            if(SUCCEEDED(retc)) retc=GenTexDelimStr(i_delim_buf, delim_str);

            pnti=i_delim_buf;
            while((*pnti) && SUCCEEDED(retc))
            {
//             retc=SkipDelimCtrlChars(&pnts);
               if(SUCCEEDED(retc))
               {
                  if(TvIntStrChr((const int *)iazSpcEol, *pnti)!=NULL)
                  {
                     if(*piCurCharPos<iNumOfChars-LAST_WORD_RECOGN_PTR)
                        *piLastWordPos=*piCurCharPos;

// if((KpErrorProc.lMsgPar==30) && (*piLastWordPos>0))
// retc=retc;

                     ii=(*piCurCharPos)-(iNumOfChars-LAST_WORD_LEN);
                     if((ii>=0) && (*piLastWordRest>ii)) *piLastWordRest=ii;
                  }

                  (*piCurCharPos)++;
                  pnti++;
               }
            
            } // while((*pnti) && SUCCEEDED(retc))
         
         } // if((delim_ptr!=NULL) && SUCCEEDED(retc))
      
      } // if((!bTagFormat) && SUCCEEDED(retc))

      iPrevOutTag=cur_tag;

// contents start
      if(SUCCEEDED(retc)) retc=loop_brother->GetFirstChild(&first_child);
      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr((const Chars16 **)&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc))
         retc=first_child->GetLastWordPosTex(piLastWordPos, piLastWordRest, piCurCharPos, iNumOfChars, iFirstTag, XC_Nul, bTagFormat);

// contents
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XC_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) 
         {
            pnti=cont_ptr;
            while((*pnti) && SUCCEEDED(retc))
            {
               if(*pnti==NS_CTRL_START) // '$'
               {
                  pnti++;
                  switch(*pnti++)
                  {
// font style
                  case 'f':
                     for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnti)); ii++) pnti++;
                     (*piCurCharPos)+=3;
                     break;

// paragraph style
                  case 's':
                     for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnti)); ii++) pnti++;
                     break;

// unicode character
                  case 'u':
                     for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((Chars16)(*pnti))); ii++) pnti++;
                     (*piCurCharPos)++;
                     break;
         
// condensed font
                  case 'q':
                     for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnti)); ii++) pnti++;
                     (*piCurCharPos)+=11;
                     break;

                  default:
                     retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
                     break;
                  }
               }
               else // if(*pnti==NS_CTRL_START) // '$'
               {
                  if(TvIntStrChr((const int *)iazSpcEol, *pnti)!=NULL)
                  {
                     if(*piCurCharPos<iNumOfChars-LAST_WORD_RECOGN_PTR)
                        *piLastWordPos=*piCurCharPos;

// if((KpErrorProc.lMsgPar==30) && (*piLastWordPos>0))
// retc=retc;

                     ii=(*piCurCharPos)-(iNumOfChars-LAST_WORD_LEN);
                     if((ii>=0) && (*piLastWordRest>ii)) *piLastWordRest=ii;
                  }

                  (*piCurCharPos)++;
                  pnti++;
               
               } // else // if(*pnti==NS_CTRL_START) // '$'
            
            } // while((*pnti) && SUCCEEDED(retc))
         
         } // if(SUCCEEDED(retc)) 
      
      } // if((cont_ptr!=NULL) && SUCCEEDED(retc))

// to next brother
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother(&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))


// last tag in group - delimiter
   if((!bTagFormat || (cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup)) && SUCCEEDED(retc))
   {
      delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(cur_tag-iFirstTag)/2][(XC_Nul-iFirstTag)/2];
      if((delim_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, delim_ptr, XC_Nul, NULL);
         if(SUCCEEDED(retc)) retc=GenTexDelimStr(i_delim_buf, delim_str);

         pnti=i_delim_buf;
         while((*pnti) && SUCCEEDED(retc))
         {
//          retc=SkipDelimCtrlChars(&pnts);
            if(SUCCEEDED(retc))
            {
               if(TvIntStrChr((const int *)iazSpcEol, *pnti)!=NULL)
               {
                  if(*piCurCharPos<iNumOfChars-LAST_WORD_RECOGN_PTR)
                     *piLastWordPos=*piCurCharPos;

// if((KpErrorProc.lMsgPar==30) && (*piLastWordPos>0))
// retc=retc;

                  ii=(*piCurCharPos)-(iNumOfChars-LAST_WORD_LEN);
                  if((ii>=0) && (*piLastWordRest>ii)) *piLastWordRest=ii;
               }

               (*piCurCharPos)++;
               pnti++;
            }
         }
      }
   }

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->GetLastWordPos(piLastWordPos, piCurCharPos, iNumOfChars, iFirstTag, cur_tag, bTagFormat)

return(retc);
}


//-----------------------------------
int XmlNode_tag::DelimStrLenTex(const unsigned char *lpszDelimPtr, int iCurTag, XmlTagPars_tag *pTagPars)
{
HRESULT retc=S_OK;
int str_len=0;
int i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned char delim_str[KP_MAX_FILE_LIN_LEN+1];

/*
const unsigned char *pnts;

   pnts=lpszDelimPtr;
   while((*pnts) && SUCCEEDED(retc))
   {
      retc=SkipDelimCtrlChars(&pnts);
      if(SUCCEEDED(retc))
      {
         str_len++;
         pnts++;
      }
   }
*/

   if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, lpszDelimPtr, iCurTag, pTagPars);
   if(SUCCEEDED(retc)) retc=GenTexDelimStr(i_delim_buf, delim_str);
   if(SUCCEEDED(retc)) str_len=TvIntStrLen(i_delim_buf);
   
return(str_len);
}

//-----------------------------------
int XmlNode_tag::XmlnIntStrLen(const int *piValPtr)
{
HRESULT retc=S_OK;
const int *pnts;
int retv=0;
int ii;

   pnts=piValPtr;
   while((*pnts) && SUCCEEDED(retc))
   {
      if((*pnts++)==NS_CTRL_START) // '$'
      {
         switch(*pnts++)
         {
// font style
         case 'f':
            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;
            retv+=3;
            break;

// paragraph style
         case 's':
            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;
            break;

// unicode character
         case 'u':
            for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((Chars16)(*pnts))); ii++) pnts++;
            retv++;
            break;
         
// condensed font
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;
            retv+=11;
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
            break;
         }
      }
      else // if((*pnts++)==NS_CTRL_START) // '$'
         retv++;
   }

return(retv);
}