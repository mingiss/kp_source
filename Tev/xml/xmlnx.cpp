// ==================================================
// xmlnx.cpp
// XML dictionary entry node TEX functions
//


// ==================================== definitions
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
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
#include "kperr.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
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
#include "xmlu.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "xmlsty.h"
#include "KpFileSys.h"
#include "xmln.h"
#include "tvxmls.h"


//-----------------------------------
KpChar CvtToTex(KpChar iInCh)
{
KpChar out_chr=iInCh;

   switch(iInCh)
   {
   case DOUBLE_ENTRIES_KPCHAR: // C_Bpoint, bullet - anksciau buvo naudojamas vietoj TV_XM_CompDelim,
      out_chr=C_Nul;          //    dabar - homonimu ir kt. panasiu zodziu rusiavimui
      break;

// case TV_XM_CompDelim:      // C_Vertl, '|' - vidiniam formate jau TV_KP_CompDelim
   case TV_KP_CompDelim:      // C_Dvertl
      out_chr=(KpChar)TX_TG_BD;
      break;
   case C_Vertl:
      out_chr=(KpChar)TX_TG_vert;
      break;
   case TV_XM_CompBaseChar:   // '~'
      out_chr=(KpChar)TX_TG_BS;
      break;

   case C_Dash:               // '-'
      out_chr=(KpChar)TX_TG_dash;
      break;

#if FALSE // kai kur reikia pavieniø, be to AKLZ C_Rapost pavirsta paprastu programuotojiðku apostrofu
   case C_LAapost:            // '''
      out_chr=C_Grave;
      break;
   case C_Rapost:            // '\''
      out_chr=C_Apost;
      break;
#endif

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

// OTEL --> LED
   case C_ph_e_sh_inv:
      out_chr=C_ph_e_inv;
      break;
   case C_ph_a_inv:
      out_chr=C_ph_o_sh;
      break;

   case C_Cr:              // '\r'
      out_chr=C_hbreak;
      break;

// case C_Lslash:          // '\\' - vidiniam formate jau C_hyph, o C_Lslash jau interpretuotas ið "$\\" 
//    out_chr=C_hyph;
//    break;

// case C_Amp:             // '&' --> '-' + C_hbreak
//    out_chr=C_hhyph;
//    break;

// case C_Numb:            // '#' - vidiniam formate jau C_QemSpc, o C_Numb jau interpretuotas ið "$#"
//    out_chr=C_QemSpc;
//    break;

// kol kas tik RLZ, tik <ct> ir realizuota TeX'o stiliuje
// case C_Lbrack:       // '[' --> \rm
//    out_chr=(KpChar)TX_TG_rm;
//    break;
// case C_Rbrack:       // ']' --> end of \rm
//    out_chr=(KpChar)TX_SP_FieldEnd; // blogai, jei atidarantis TX_TG_rm neijungia m_bCtblSwitched, tada reiketu
//                            // buvusio fonto atstatymo, greiciausiai TX_TG_it
//    break;

   case C_Lcurl:        // '{' --> \bf
      out_chr=(KpChar)TX_TG_bf;
      break;
   case C_Rcurl:        // '}' --> end of \bf
      out_chr=(KpChar)TX_SP_FieldEnd; // blogai, jei atidarantis TX_TG_bf neijungia m_bCtblSwitched, tada reiketu
                              // paprasto TX_TG_rm
      break;

// case XC_EquInline:
// case XC_EquInline_e:
//    out_chr=(KpChar)TX_SP_MathField; // TX_CH_MathField; // '$'
//    break;

   case C_Dash_Diaer:
      out_chr = (KpChar)TX_TG_dtb; 
      break;
   }

return(out_chr);
}

// ==================================== class XmlNode methods
//-----------------------------------
HRESULT XmlNode::PutTexChar(TvTexFile *lpOutFile, KpChar iOutChar, KpChar *piLastChar, bool bTestLastChar, KpChar iFatherTag, 
int *piCurCharPos, int iLastWordPos, int iLastWordRest, KpChar *piDelayedChar/* , KpChar iFirstTag, KpChar iLastTag */)
{
HRESULT retc=S_OK;
bool last_char_simply_space=False;
bool out_char_simply_space=False;
bool last_char_space=False;
bool out_char_space=False;
bool last_char_punct=False;
bool last_char_open_punct=False;
bool out_char_punct=False;
bool last_char_diacr=False;
bool put_tag;
KpChar tex_tag = C_Nul;

#ifdef Debug
// if((KpErrorProc.lMsgPar==183) && (iOutChar==C_Dots))
// KpErrorProc.lMsgPar=183;

// if((KpErrorProc.lMsgPar==24) && (iOutChar==C_sbreak))
// KpErrorProc.lMsgPar=24;

if(iOutChar==C_Eq) // '='
iOutChar=C_Eq;
#endif

   if(
      (
         (lpOutFile==NULL) || (piLastChar==NULL) // ||
//       (!( 
//          ((iFatherTag >= m_iFirstTag /* iFirstTag */) && (!CheckLastTag(iFatherTag)) /* (iFatherTag < iLastTag) */) ||
//          ((iFatherTag >= XL_FirstSysTag) && (iFatherTag < XL_LastSysTag))
//       ))
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if((*piLastChar < 0) || (iOutChar < 0))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(piDelayedChar!=NULL) *piDelayedChar=C_Nul;

#ifdef Debug
if(iOutChar==C_Point)
{
iOutChar=C_Point;
}
#endif

   if(SUCCEEDED(retc))
   {
      if(
         (TvKpStrChr(iazSimplySpaces, *piLastChar)!=NULL) ||
         (*piLastChar==C_NBSP) // || // reikia VLZ08e - NBSP yra po reikðmiø skaièiukø, turi bûti suvalgyti po to einanèiø skirtukø, pvz., ':', abbiegen
//       (*piLastChar==C_NullSpc)
        ) last_char_simply_space=True;

      if(
         (TvKpStrChr(iazSimplySpaces, iOutChar)!=NULL) ||
         (iOutChar==C_NBSP) // || // reikia VLZ08e
//       (iOutChar==C_NullSpc)
        ) out_char_simply_space=True;

      if(
         (TvKpStrChr(iazSpaces, *piLastChar)!=NULL) // &&
//       (*piLastChar!=C_NBSP) &&
//       (*piLastChar!=C_NullSpc)
        ) last_char_space=True;

      if(
         (TvKpStrChr(iazSpaces, iOutChar)!=NULL) // &&
//       (iOutChar!=C_NBSP) &&
//       (iOutChar!=C_NullSpc)
        ) out_char_space=True;

      if(
         (iFatherTag != XC_Pron) &&
         (TvKpStrChr(iazPunctuators, *piLastChar)!=NULL) &&
         ((*piLastChar!=C_Point) || (iOutChar==C_Point)) &&     // '.'
         ((*piLastChar!=C_Dots) || (iOutChar==C_Point)) // &&      // '...'
//       (iOutChar!=C_Excl) &&         // '!'
//       (iOutChar!=C_Quest)           // '?'
        ) last_char_punct=True;

      if(
            (*piLastChar==C_Lpar) ||     // '('
            (*piLastChar==C_Lbrack) ||   // '['
            (*piLastChar==C_Lcurl) ||   // '{'
            (*piLastChar==C_LBquote) // ||   // ',,'
        ) last_char_open_punct=True;

      if(
         (TvKpStrChr(iazPunctuators, iOutChar)!=NULL) &&
         (iOutChar!=C_Dots) // '...'
        ) out_char_punct=True;
   
      if(*piLastChar < C_CharSize0) if(iaTexSpecCharTypes[*piLastChar] == TexDiacr) last_char_diacr = True;
   }

#ifdef Debug
if(iOutChar==C_NBSP)
iOutChar=C_NBSP;

if(iOutChar==C_Colon) // ':'
iOutChar=C_Colon;

if(iOutChar==C_Macr)
iOutChar=C_Macr;
#endif

   if(last_char_simply_space /* last_char_space */ && (!out_char_space) &&
      (!out_char_punct) && SUCCEEDED(retc))
   {
      retc=lpOutFile->PutCharProc(*piLastChar, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//    *piLastChar=C_Nul;
   }

   if(last_char_diacr && SUCCEEDED(retc))
   {
      if(out_char_simply_space) iOutChar = TX_TG_forc_sp;
      else if(!out_char_space) retc=lpOutFile->PutChar(C_Spc, False);
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
         ((!out_char_simply_space) || last_char_diacr) // (!out_char_space)
        )
      {
         if(iOutChar==C_sbreak)
         {
//          tex_tag = iaXml2Tex[iFatherTag - m_iFirstTag /* iFirstTag */];
            tex_tag = GetXml2Tex(iFatherTag);
            
            if((tex_tag != C_Nul) && SUCCEEDED(retc))
               if(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]!=NULL)
                  if(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0)
                     retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(iOutChar, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if((tex_tag != C_Nul) && SUCCEEDED(retc))
            {
               put_tag = (plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
               if(put_tag) put_tag = (strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
               if(put_tag)
               {
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//                if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               }
               else
               {
// jei kitas simbolis tarpas - isvesti pries iaUserTexTagPrefixes[] !!!
                  if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
                     retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
            }
         }
         else
         {
#ifdef Debug
if(iOutChar==C_Point) // '.'
iOutChar=C_Point;

if(iOutChar==C_Colon) // ':'
iOutChar=C_Colon;
#endif
            if(SUCCEEDED(retc))
            {
               if(piDelayedChar!=NULL)
                  *piDelayedChar=iOutChar;
               else
               {
#ifdef Debug
// lpOutFile->PutChar('[', False);
#endif
                  retc=lpOutFile->PutCharProc(iOutChar, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
#ifdef Debug
// lpOutFile->PutChar(']', False);
#endif
               }
            }
         }
//       *piLastChar=iOutChar;
      }

      if(
#if FALSE
         (
            (!out_char_punct) ||
            (!last_char_punct) ||
//          ((*piLastChar==C_Point) && (iOutChar==C_Comma)) || // delimiters between labels
            (!bTestLastChar)
         ) &&
#endif
         ((!last_char_space) || (!out_char_simply_space /* !out_char_space */)) &&
         ((!last_char_open_punct) || (!out_char_simply_space /* !out_char_space */))
        )
      {
         if(piDelayedChar==NULL) *piLastChar=iOutChar;
         else *piLastChar=C_Nul;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::MoveTwo(TvTexFile *lpOutFile, KpChar *piLastChar, KpChar iFatherTag, int *piCurCharPos, 
int iLastWordPos, int iLastWordRest, /* KpChar iFirstTag, KpChar iLastTag, */ bool test_last_char)
{
HRESULT retc=S_OK;

// if((lpOutFile==NULL) || (piLastChar==NULL) || (iFatherTag < m_iFirstTag) || CheckLastTag(iFatherTag) || (piCurCharPos==NULL))
//    retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc)) if((*piCurCharPos==iLastWordPos) && (iLastWordPos>0))
            {
//             if(TvStrChr(lpszSpcEol, *pnts)==NULL)
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#ifdef AUTO_LASTWORD
               if(SUCCEEDED(retc))
                  retc=PutTexChar(lpOutFile, C_sbreak, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
#endif
            }
            if(SUCCEEDED(retc)) (*piCurCharPos)++;
            if(SUCCEEDED(retc)) if(*piCurCharPos==iLastWordPos)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) (*piCurCharPos)++;

return(retc);
}

HRESULT XmlNode::PutTexIntStr(TvTexFile *lpOutFile, const KpChar *iaOutStr, KpChar *piLastChar, KpChar iFatherTag, 
XmlNode *pnCurNode, bool bTagFormat, int *piCurCharPos, int iLastWordPos, int iNumOfChars, int iLastWordRest
/*, KpChar iFirstTag, KpChar iLastTag */)
{
const KpChar *pnts;
const KpChar *ends;
KpChar out_chr;
HRESULT retc=S_OK;
bool test_last_char=True;
unsigned char *ind_ptr=(unsigned char *)"";
int start_pos;
int cur_pos;
int ii;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned char *pntd;
int outstr_len;
bool put_space;
bool put_tag;
bool math_fl = False;
KpChar tex_tag = C_Nul;

   if(
      (
         (lpOutFile==NULL) || (iaOutStr==NULL) || (piLastChar==NULL) || (pnCurNode==NULL) || (piCurCharPos==NULL) // ||
//       (!( 
//          ((iFatherTag >= m_iFirstTag /* iFirstTag */) && (!CheckLastTag(iFatherTag)) /* (iFatherTag < iLastTag) */)
//          ((iFatherTag >= XL_FirstSysTag) && (iFatherTag < XL_LastSysTag))
//       ))
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      outstr_len=TvKpStrLen(iaOutStr);

      retc=pnCurNode->GetIndentPtr(&ind_ptr);
      if(ind_ptr==NULL) ind_ptr=(unsigned char *)"";
   }

   if(SUCCEEDED(retc))
   {
      start_pos=((strlen(ind_ptr)/XN_POS_PER_INDENT-1) + XN_VAL_START_TAB) * XN_POS_PER_TAB;
      cur_pos=start_pos;
   }

   if(SUCCEEDED(retc))
   {
      pnts = iaOutStr;
      ends = pnts + TvKpStrLen(pnts);
   } 
   
#if FALSE
   if((iFatherTag==XC_CodeExample) && SUCCEEDED(retc)) // praleidþiam pirmà ir paskutiná Lf
   {
      while(TvStrChr(lpszSpaces, *pnts) != NULL) pnts++;
      if(*pnts == C_Lf) pnts++;
      else pnts = iaOutStr;
      
      while(ends > pnts)
      {
         ends--;
         if(TvStrChr(lpszSpaces, *ends) == NULL) break;
      }
      if(*ends != C_Lf) ends++;
   }
#endif
   
   if(SUCCEEDED(retc)) while((*pnts) && (pnts < ends) && SUCCEEDED(retc))
   {
      if((iFatherTag!=XC_Special) /* && (iFatherTag!=XC_CodeExample) */)
      {
         if(
            ((*pnts==C_Acute) || (*pnts==C_Apost) || (*pnts==C_Plus)) &&
            (iFatherTag!=XC_TechNote) &&
            (iFatherTag!=XC_UsNoteSrc) && (iFatherTag!=XC_UsNoteDst) &&
            (iFatherTag!=XC_CodeExampleInline)
                )
         {
            if(SUCCEEDED(retc)) switch(*(pnts+1))
            {
               case C_A:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_A_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E_Adot:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Adot_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Y_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_O:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_O_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U_Macr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Macr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e_Adot:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Adot_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_y_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_o:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_o_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Ogon_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u_Macr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Macr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_A_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_O_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_O_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Y_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Y_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Ee_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Ee_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Yu_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Yu_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Ya_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Ya_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_o_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_o_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_y_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_y_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_ee_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_ee_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_yu_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_yu_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_ya_Cyr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_ya_Cyr_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               default:
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, (*pnts++), piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) (*piCurCharPos)++;
                  test_last_char=False;
                  break;
            }
         }
         else if(
            ((*pnts==C_TildeAcc) || (*pnts==C_Tilde)) &&
            (iFatherTag!=XC_TechNote) &&
            (iFatherTag!=XC_UsNoteSrc) && (iFatherTag!=XC_UsNoteDst) &&
            (iFatherTag!=XC_CodeExampleInline)
                )
         {
            if(SUCCEEDED(retc)) switch(*(pnts+1))
            {
               case C_A:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_A_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E_Adot:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Adot_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Y_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_O:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_O_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U_Macr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Macr_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e_Adot:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Adot_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_y_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_o:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_o_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u_Ogon:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Ogon_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u_Macr:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Macr_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_l:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_l_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_m:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_m_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_n:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_n_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_r:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_r_Tilde, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               default:
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, (*pnts++), piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) (*piCurCharPos)++;
                  test_last_char=False;
                  break;
            }
         }
         else if(
            ((*pnts==C_GraveAcc) || (*pnts==C_Grave)) &&
            (iFatherTag!=XC_TechNote) &&
            (iFatherTag!=XC_UsNoteSrc) && (iFatherTag!=XC_UsNoteDst) &&
            (iFatherTag!=XC_CodeExampleInline)
                )
         {
            if(SUCCEEDED(retc)) switch(*(pnts+1))
            {
               case C_A:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Y_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_O:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_O_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_y_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_o:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_o_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Grave, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               default:
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, (*pnts++), piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) (*piCurCharPos)++;
                  test_last_char=False;
                  break;
            }
         }
         else if(
            ((*pnts==C_Quote) || (*pnts==C_Diaer)) && // '\"'
            (iFatherTag!=XC_TechNote) &&
            (iFatherTag!=XC_UsNoteSrc) && (iFatherTag!=XC_UsNoteDst) &&
            (iFatherTag!=XC_CodeExampleInline)
                )
         {
            if(SUCCEEDED(retc)) switch(*(pnts+1))
            {
               case C_A:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_A_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_E:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_E_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_I:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_I_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_Y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Y_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_O:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_O_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_U:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_U_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_a:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_a_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_e:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_e_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_i:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_i_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_y:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_y_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_o:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_o_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               case C_u:
                  if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_u_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  test_last_char=False;
                  pnts+=2;
                  break;
               default:
                  if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, (*pnts++), piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) (*piCurCharPos)++;
                  test_last_char=False;
                  break;
            }
         }
         else if(
            (*(pnts+1)==C_Quote) &&  // '\"'
            (iFatherTag!=XC_TechNote) &&
            (iFatherTag!=XC_UsNoteSrc) && (iFatherTag!=XC_UsNoteDst) &&
            (iFatherTag!=XC_CodeExampleInline)
           )
         {
            if(SUCCEEDED(retc)) retc=MoveTwo(lpOutFile, piLastChar, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, test_last_char);

            if(SUCCEEDED(retc)) switch(*pnts)
            {
// invert diaresis
            case C_Dash: // '-'
               retc=PutTexChar(lpOutFile, (KpChar)TX_TG_dtb, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL); // C_Dash_Diaer
               test_last_char=False;
               pnts+=2;
               break;

            case C_C: // 'C'
               retc=PutTexChar(lpOutFile, C_C_Cedil, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;
            case C_c: // 'c':
               retc=PutTexChar(lpOutFile, C_c_Cedil, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;

            case C_S: // 'S':
               retc=PutTexChar(lpOutFile, C_S_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;
            case C_s: // 's':
               retc=PutTexChar(lpOutFile, C_s_Acute, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;

            case C_Y: // 'Y':
               retc=PutTexChar(lpOutFile, C_Y_Grave /* C_Y_Diaer */, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;
            case C_y: // 'y':
               retc=PutTexChar(lpOutFile, C_y_Grave /* C_y_Diaer */, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;

            case C_e: // 'e':
               retc=PutTexChar(lpOutFile, C_e_Circ, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;

            case C_a: // 'a':
               retc=PutTexChar(lpOutFile, C_alpha, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;

            case C_g: // 'g':
               retc=PutTexChar(lpOutFile, C_gamma, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               test_last_char=False;
               pnts+=2;
               break;

            default:
//             if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Diaer, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
//             test_last_char=False;
               if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, *pnts++, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
//             pnts++;
               break;
            }
         }
         else if(*pnts==(KpChar)NS_CTRL_START) // '$' // if((*(pnts+1)=='\"') && (iFatherTag!=XC_TechNote))
         {
            put_space=False;

            pntd=sty_buf;
            (*pntd++)=(unsigned char)(*pnts++);
            (*pntd++)=(unsigned char)(*pnts++);
            switch(*(pnts-1))
            {
// font style
            case 'f':
               for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++)
                  (*pntd++)=(unsigned char)(*pnts++);
               put_space=True;
               break;

// paragraph style
            case 's':
               for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++)
                  (*pntd++)=(unsigned char)(*pnts++);
               break;

// unicode character
            case 'u':
               for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit(*pnts)); ii++)
                  (*pntd++)=(unsigned char)(*pnts++);
               break;

// condensed font
            case 'q':
               for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++)
                  (*pntd++)=(unsigned char)(*pnts++);
               put_space=True;
               break;

// output of spec. chars
#if FALSE // jau nebe, vidiniam formate ðitos $-poros jau konvertuotos á KpChar
            case NS_CTRL_START:  // '$' itself
            case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
//          case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
            case C_Numb:         // '#' itself, single '#' --> C_QemSpc

            case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstø á TX_TG_BD
            case C_Bpoint:       // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR

// formatting symbols
            case C_Underl:       // "$_" --> C_NBSP
            case C_At:           // "$@" --> C_Ff
            case C_Circ:         // "$^" --> C_hbreak
            case C_Point:        // "$." --> C_NullSpc, \Null
#endif            
            case C_Lbrack:       // '[' itself, single '[' --> \rm
            case C_Rbrack:       // ']' itself, single ']' --> end of \rm
            case C_Lcurl:        // '{' itself, single '{' --> \bf
            case C_Rcurl:        // '}' itself, single '}' --> end of \bf
//             (*pntd++)=(*pnts++);
               break;
            default:
               retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L);
//             (*pntd++)=(*pnts++);
//             (*pntd++)=(KpChar)TX_SP_Doll; // NS_CTRL_START;
               break;
            }

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
            if((TvStrChr(lpszSpcEol, *pnts)!=NULL) && put_space && SUCCEEDED(retc))
               retc=PutTexChar(lpOutFile, C_Spc, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

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

//             if(TvStrChr(lpszSpcEol, *pnts)==NULL)
//                retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#ifdef AUTO_LASTWORD
               if(SUCCEEDED(retc))
                  retc=PutTexChar(lpOutFile, C_sbreak, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
#endif
            }
            if(SUCCEEDED(retc)) (*piCurCharPos)++;

            out_chr=(*pnts++);

            if((iFatherTag==XC_CodeExample) && SUCCEEDED(retc)) switch(out_chr)
            {
            case C_Lf:
#ifdef Debug
// printf("*piLastChar: %d %c\n", *piLastChar, *piLastChar);
#endif            
//             if(*piLastChar != XC_CodeExample)
               {
                  retc=PutTexChar(lpOutFile, (KpChar)TX_TG_hfill, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc))
                     retc=PutTexChar(lpOutFile, (KpChar)TX_TG_break, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               }
               break;
               
            case C_Tab:
               for(ii = 0; (ii < 7) && SUCCEEDED(retc); ii++)
               {
                  retc=PutTexChar(lpOutFile, (KpChar)TX_TG_Null, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  if(SUCCEEDED(retc)) 
                     retc=PutTexChar(lpOutFile, C_Spc, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               }
               if(SUCCEEDED(retc)) 
                  retc=PutTexChar(lpOutFile, (KpChar)TX_TG_Null, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
               out_chr = C_Spc; // TX_TG_forc_sp;
               break;

            case C_Spc:
               retc=PutTexChar(lpOutFile, (KpChar)TX_TG_Null, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
//             out_chr = C_NBSP; // TX_TG_forc_sp;
               break;
            }
            
            if((TvStrChr(lpszSpaces, out_chr)!=NULL) && (cur_pos>=XN_POS_PER_COL-8) &&
               (*piCurCharPos < iLastWordPos /* iNumOfChars-LAST_WORD_LEN */) && bTagFormat && SUCCEEDED(retc))
            {
//             tex_tag = iaXml2Tex[iFatherTag - m_iFirstTag /* iFirstTag */];
               tex_tag = GetXml2Tex(iFatherTag);
               
               if((tex_tag != C_Nul) && SUCCEEDED(retc))
                  if(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL)
                     if(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0)
                        retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_TG_cr, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_Lf, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_TG_plus, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

               if((ind_ptr!=NULL) && SUCCEEDED(retc))
                  for(ii=0; (ii<start_pos/XN_POS_PER_TAB-1) && SUCCEEDED(retc); ii++)
                     retc=lpOutFile->PutCharProc((KpChar)TX_SP_Amp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

               if((tex_tag != C_Nul) && SUCCEEDED(retc))
               {
                  put_tag = (plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
                  if(put_tag) put_tag = (strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
                  if(put_tag)
                  {
//                   if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, (KpChar)XC_Nul, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

                     if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  }
                  else
                  {
// jei kitas simbolis tarpas - isvesti pries iaUserTexTagPrefixes[] !!!
                     if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
                        retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  }
               }

               cur_pos=start_pos;
            }
            else
            {
               cur_pos++;

#ifdef Debug
if(out_chr==C_Rcurl) // '}'
out_chr=C_Rcurl;
#endif

               out_chr=CvtToTex(out_chr);

               switch(out_chr)
               {
               case C_hbreak:
//                retc=PutTexChar(lpOutFile, (KpChar)TX_TG_hfill, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  out_chr=C_break;
                  break;

               case C_hhyph:
                  retc=PutTexChar(lpOutFile, C_Dash, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                  out_chr=C_break;
                  break;

// #ifdef AUTO_LASTWORD
               case C_Spc:
                  if(*piCurCharPos>=iNumOfChars-LAST_WORD_LEN)
                     out_chr=C_NBSP;
                  break;

//             case C_EnSpc:
//             case C_QemSpc:
//                if(*piCurCharPos>=iNumOfChars-LAST_WORD_LEN)
//                {
//                   retc=PutTexChar(lpOutFile, C_NBSP, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
//                   out_chr=C_NBSP;
//                }
//                break;

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
// #endif
               case C_Lf:
//                if(iFatherTag == XC_CodeExample) out_chr = (KpChar)TX_TG_break; // XC_Break;
                  out_chr = TX_SP_Lf;
                  break;
               }

// last single letter in control tags
               if(
                  ((out_chr==C_Spc) || (out_chr==C_hSpc)) &&
                  ((iFatherTag==XC_CtrlSrc) || (iFatherTag==XC_CtrlDst)) &&
                  (pnts-iaOutStr==outstr_len-1) &&
                  SUCCEEDED(retc)
                 )
                  out_chr=C_NBSP;

               if(SUCCEEDED(retc)) switch(out_chr)
               {
// convert italic parentheses to straight ones
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
                     if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc('n', TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//                   if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_Spc, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                     if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, out_chr, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                     if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
                     if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
                  }
                  else
#endif
                  if((iFatherTag==XC_ExplSrc) || (iFatherTag==XC_ExplDst))
                  {
                     if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                     if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_TG_FS, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_B /* 'B' */, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//                   if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(C_Spc, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                     if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, out_chr, piLastChar, test_last_char, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
                     if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
                     if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
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
               test_last_char=True;

            } // else // if((TvStrChr(lpszSpaces, out_chr)!=NULL) && (cur_pos>=XN_POS_PER_COL-5) && bTagFormat)

         } // else // if(*pnts==NS_CTRL_START) // '$' // if((*(pnts+1)=='\"') && (iFatherTag!=XC_TechNote))

      }
      else // if(iFatherTag!=XC_Special)
      {
         out_chr=*pnts++;
         if((out_chr>=KPT_FirstKptChar) && SUCCEEDED(retc))
         {
            retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, False, __FILE__, __LINE__, 0L);
            out_chr=C_Quest; // '?';
         }
            
         if(SUCCEEDED(retc)) switch(out_chr)
         {
         case TX_CH_FieldStart: retc = lpOutFile->OpenField(False, True); break;
         case TX_CH_FieldEnd: retc = lpOutFile->CloseField(False, True); break; 
         case TX_CH_MathField:
            retc=lpOutFile->PutCharProc(TX_SP_MathField, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            break;
         default:
            if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(out_chr, False);
            break;
         }
      }

   } // while((*pnts) && SUCCEEDED(retc))

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::FlushSpaces(TvTexFile *lpOutFile, bool bSkipLineOnSpace, KpChar *piLastChar, int iLastWordRest, int *piCurCharPos, int iLastWordPos)
{
HRESULT retc=S_OK;

   if(((lpOutFile==NULL) || (piLastChar==NULL) || (piCurCharPos==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if((TvKpStrChr(iazSpaces, *piLastChar)!=NULL) && (*piLastChar!=C_NBSP))
   {
      retc=lpOutFile->PutCharProc(*piLastChar, TexNoType, bSkipLineOnSpace, iLastWordRest);
      *piLastChar=C_Nul;
   }

   if(SUCCEEDED(retc)) retc=lpOutFile->FlushSpaces(*piCurCharPos < iLastWordPos);

return(retc);
}


// --------------------------------------------------
HRESULT XmlNode::CloseField(TvTexFile *lpOutFile, bool bFlushFl, bool bSkipLineOnSpace, KpChar *piLastChar, int iLastWordRest, int *piCurCharPos, int iLastWordPos)
{
HRESULT retc=S_OK;

   if((lpOutFile==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(bFlushFl && SUCCEEDED(retc)) retc = FlushSpaces(lpOutFile, bSkipLineOnSpace, piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

   if(SUCCEEDED(retc)) retc=lpOutFile->CloseField(bFlushFl, bSkipLineOnSpace);

return(retc);
}


//-----------------------------------
// font style code for TeX command TX_TG_FS (\FS)
KpChar CalcStyCode(KPS_FontStyles iStyNo)
{
HRESULT retc=S_OK;
KpChar sty_code=C_0; // '0';

   if((iStyNo<0) || (iStyNo>=2*('Z'-'A'+1)))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, (long)iStyNo /* 0L */);

   if(SUCCEEDED(retc))
   {
      if(iStyNo<'Z'-'A'+1) sty_code=(KpChar)(iStyNo+C_A); // 'A'
      else sty_code=(KpChar)(iStyNo+C_a-(C_Z-C_A+1)); // 'a'-('Z'-'A'+1)
   }

return(sty_code);
}


//-----------------------------------
// iazOutBuf[KP_MAX_FILE_LIN_LEN+1]
// lpszFormatStr - formato eilute is lpszXmlTagDelimiters[][]
// derint su SkipDelimCtrlChars()
// derint su GenXmlDelimStr
HRESULT XmlNode::GenTexDelimStr(KpChar *iazOutBuf, const unsigned char *lpszFormatStr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
const unsigned char *pnts0;
KpChar *pntd;
int sty_no;
bool font_changed=False;
// int code_table=NS_DELIM_CTBL;
// int font_id;
unsigned char sty_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned int uni_code;
int cond_fnt;
int ii;
KpChar post_char;

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

            if(strlen(pnts)>=KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            strcpy(sty_buf, pnts);
            sty_buf[NS_STY_NO_WDT]=Nul;
            sty_no=(-1);
            sscanf((char *)sty_buf, "%d", &sty_no);

            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
            if(TvStrChr(lpszSpcEol, (KpChar)*pnts)!=NULL) *(pntd++)=C_Spc;

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

//          if(SUCCEEDED(retc)) if(((pntd-iazOutBuf)+1+MAX_LONG_DIGITS+1+1)>=KP_MAX_FILE_LIN_LEN)
            if(SUCCEEDED(retc)) if(((pntd-iazOutBuf)+1+1+1)>=KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

//          if(((sty_no<0) || (sty_no>=10+'Z'-'A'+1+'z'-'a'+1)) && SUCCEEDED(retc))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
// tarpus perkeliam toliau, kad suveiktu XmlNode::PutTexChar() tarpu/skirtuku apjungimas
// jei *(pntd-1) skirtukas - negerai !!!
               post_char=C_Nul;
               if(pntd>iazOutBuf)
//                if(TvIntStrChr((const int *)iazSimplySpaces, *(pntd-1))!=NULL)
                  if(*(pntd-1)==C_NBSP)
                     post_char=(*(--pntd));

               *(pntd++)=(KpChar)TX_TG_FS;
               *(pntd++)=CalcStyCode((KPS_FontStyles)sty_no);
               *(pntd++)=C_hSpc;

               if(post_char!=C_Nul) *(pntd++)=post_char;
            }

            break;

// paragraph style
         case 's':
            if(strlen(pnts)>=KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            strcpy(sty_buf, pnts);
            sty_buf[NS_PAR_STY_WDT]=Nul;
            sty_no=(-1);
            sscanf((char *)sty_buf, "%d", &sty_no);

            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
            if(TvStrChr(lpszSpcEol, (KpChar)*pnts)!=NULL) *(pntd++)=C_Spc;

            sty_no-=KPP_FIRST_PAR_STYLE;

            if(((sty_no<0) || (sty_no>=iNumOfParagraphStyles)) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if((((pntd-iazOutBuf)+strlen(lpszaParStyTexInlineCmds[sty_no]) + 1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  pnts0=lpszaParStyTexInlineCmds[sty_no];
                  while(*pnts0)
                  {
                     if(*pnts0==TX_CH_KeywordStart)
                     {
                        *(pntd++)=(KpChar)TX_SP_KeywordStart;
                        pnts0++;
                     }
                     else *(pntd++)=(KpChar)(*pnts0++);
                  }
               }
            }

            break;

// unicode character
         case 'u':
            if((((pntd-iazOutBuf)+1+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               if(strlen(pnts)>=KP_MAX_FILE_LIN_LEN)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               strcpy(sty_buf, pnts);
               sty_buf[NS_UNI_CODE_WDT]=Nul;
               uni_code=0xFFFFFFFF; // (-1);
               sscanf((char *)sty_buf, "%x", &uni_code);

#ifdef Debug
if(uni_code==0xE2D7)
uni_code=0xE2D7;
#endif

               for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit((KpChar)(*pnts))); ii++) pnts++;

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
            if(SUCCEEDED(retc)) *(pntd++)=(KpChar)ii;
            break;

// condensed font
         case 'q':
            if(strlen(pnts)>=KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
            {
               strcpy(sty_buf, pnts);
               sty_buf[NS_COND_FNT_WDT]=Nul;
               cond_fnt=0;
               sscanf((char *)sty_buf, "%d", &cond_fnt);

               for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
               if(TvStrChr(lpszSpcEol, (KpChar)*pnts)!=NULL) *(pntd++)=C_Spc;

               if((cond_fnt<0) || (cond_fnt>=100)) // 9.9 pt - max condension
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) if(((pntd-iazOutBuf)+1+MAX_LONG_DIGITS+1+1)>=KP_MAX_FILE_LIN_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
// tarpus perkeliam toliau, kad suveiktu XmlNode::PutTexChar() tarpu/skirtuku apjungimas
// jei *(pntd-1) skirtukas - negerai !!!
               post_char=C_Nul;
               if(pntd>iazOutBuf)
//                if(TvIntStrChr((const int *)iazSimplySpaces, *(pntd-1))!=NULL)
                  if(*(pntd-1)==C_NBSP)
                     post_char=(*(--pntd));

               cond_fnt=(cond_fnt*10)+117; // 1.17 pt (0.85 pt ?) - no condension

// \fontdimen4\timacn=1.23pt // shrink interword
               *(pntd++)=(KpChar)TX_TG_fontdimen;
               *(pntd++)=C_4; // '4'
               *(pntd++)=(KpChar)TX_TG_timacn;
               *(pntd++)=(KpChar)TX_SP_Eq; // C_Eq; // '='
               *(pntd++)=(KpChar)(C_0 + (cond_fnt/100)); cond_fnt%=100;
               *(pntd++)=C_Point; // '.'
               *(pntd++)=(KpChar)(C_0 + (cond_fnt/10)); cond_fnt%=10;
               *(pntd++)=(KpChar)(C_0 + cond_fnt);
               *(pntd++)=C_p;
               *(pntd++)=C_t;
               *(pntd++)=C_hSpc;

               if(post_char!=C_Nul) *(pntd++)=post_char;
            }

            break;

// output of spec. chars
         case NS_CTRL_START:  // '$' itself
            *(pntd++)=(KpChar)TX_SP_Doll;
            break;

         case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
            *(pntd++)=(KpChar)TX_SP_Lslash;
            break;

//       case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
//          *(pntd++)=(KpChar)TX_SP_Amp;
//          break;

         case C_Numb:         // '#' itself, single '#' --> C_QemSpc
            *(pntd++)=(KpChar)TX_SP_Numb;
            break;

         case C_Lbrack:       // '[' itself, single '[' --> \rm
            *(pntd++)=(KpChar)TX_SP_Lbrack;
            break;
         case C_Rbrack:       // ']' itself, single ']' --> end of \rm
            *(pntd++)=(KpChar)TX_SP_Rbrack;
            break;

         case C_Lcurl:        // '{' itself, single '{' --> \bf
            *(pntd++)=(KpChar)TX_SP_Lcurl;
            break;
         case C_Rcurl:        // '}' itself, single '}' --> end of \bf
            *(pntd++)=(KpChar)TX_SP_Rcurl;
            break;
         case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstø á TX_TG_BD
            *(pntd++)=(KpChar)TX_TG_vert;
            break;
#if FALSE // èia tik char, ne KpChar
         case C_Bpoint:       // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR
// KP_TRACE("GenTexDelimStr: C_Bpoint");          
            *(pntd++)=C_hBpoint;
            break;
#endif
// formatting symbols
         case C_Underl:       // "$_" --> C_NBSP
            *(pntd++)=C_NBSP;
            break;
         case C_At:           // "$@" --> C_Ff
            *(pntd++)=C_Ff;
            break;
         case C_Circ:         // "$^" --> C_hbreak
            *(pntd++)=C_hbreak; // C_break;
            break;
         case C_Point:        // "$." --> C_NullSpc
            *(pntd++)=C_NullSpc;
            break;

         default:
// KP_TRACE_1("GenTexDelimStr: *(pnts-1):%d", *(pnts-1));          
//          retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L);
            *(pntd++)=(KpChar)TX_SP_Doll; // NS_CTRL_START;   // '$'
            *(pntd++)=(KpChar)*(pnts-1);
            break;
         }
      }
      else
      {
         if((((pntd-iazOutBuf)+1)>=KP_MAX_FILE_LIN_LEN) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            retc=KptCharEncode(pntd++, *pnts++, iDelimCtbl /* NS_DELIM_CTBL */ /* code_table */);
            if(FAILED(retc))
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         }
      }
   }

   if(font_changed && SUCCEEDED(retc))
   {
// tarpus perkeliam toliau, kad suveiktu XmlNode::PutTexChar() tarpu/skirtuku apjungimas
// jei *(pntd-1) skirtukas - negerai !!!
      post_char=C_Nul;
         if(pntd>iazOutBuf)
//          if(TvIntStrChr((const int *)iazSimplySpaces, *(pntd-1))!=NULL)
            if(*(pntd-1)==C_NBSP)
               post_char=(*(--pntd));

      if(SUCCEEDED(retc)) if(((pntd-iazOutBuf)+1+1+1+1)>=KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
// cia reikia tarpo, jei po atskyreju eilutes is karto bus tarpas !!!
         *(pntd++)=(KpChar)TX_TG_FS;
         *(pntd++)=CalcStyCode(NS_DEFAULT_TEXT_STYLE);
         *(pntd++)=C_hSpc;

         if(post_char!=C_Nul) *(pntd++)=post_char;
      }
   }

   if(SUCCEEDED(retc)) *pntd=C_Nul;

return(retc);
}


//-----------------------------------
HRESULT XmlNode::WriteTexDelim(TvTexFile *lpOutFile, const unsigned char *lpszDelimStr,
                                   KpChar *piLastChar, int *piCurCharPos,
                                   int iLastWordPos, int iLastWordRest, int iNumOfChars // ,
                                // KpChar iFirstTag, KpChar iLastTag
                                   )
{
HRESULT retc=S_OK;
int str_len;
bool new_par=False;
unsigned char delim_str1[KP_MAX_FILE_LIN_LEN+1];
unsigned char delim_str2[KP_MAX_FILE_LIN_LEN+1];
KpChar i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
const unsigned char *lf_ptr;
// const int *pnti;
// int ii;
// int tmp_str[KP_MAX_FILE_LIN_WDT+1];
bool put_tag;
KpChar tex_tag = C_Nul;

   if((lpOutFile==NULL) || (lpszDelimStr==NULL) || (piLastChar==NULL) || (piCurCharPos==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      if(strlen(lpszDelimStr)>=KP_MAX_FILE_LIN_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) lf_ptr=TvStrChr(lpszDelimStr, C_Lf);
   if((lf_ptr!=NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc))
      {
         strcpy(delim_str1, lpszDelimStr);
         delim_str1[lf_ptr-lpszDelimStr]=Nul;
         strcpy(delim_str2, lf_ptr+1);
         retc=WriteTexDelim(lpOutFile, delim_str1, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
         if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, C_Lf, piLastChar, True, (KpChar)XC_PunctMark, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

#ifdef AUTO_LASTWORD
         if(SUCCEEDED(retc)) if((*piCurCharPos==iLastWordPos) && (iLastWordPos>0))
            retc=PutTexChar(lpOutFile, C_sbreak, piLastChar, True, (KpChar)XC_PunctMark, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
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
         if(TvKpStrLen(i_delim_buf)>0)
         {

//       TvIntStrNCpy(tmp_str, i_delim_buf, KP_MAX_FILE_LIN_WDT);
//       tmp_str[KP_MAX_FILE_LIN_WDT]=C_Nul;
//       retc=CutInitTrailSpcsInt(tmp_str);
//       if(SUCCEEDED(retc))
//       {
            put_tag=False;

//          tex_tag = iaXml2Tex[XC_PunctMark - m_iFirstTag /* iFirstTag */];
            tex_tag = GetXml2Tex(XC_PunctMark);

//          ii=TvIntStrLen(tmp_str);
//          if(ii>0)
            {
               if((tex_tag != C_Nul) && SUCCEEDED(retc))
               {
                  put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]!=NULL);
                  if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
                  if(put_tag) if((i_delim_buf[0]==C_Spc) && (i_delim_buf[1]==C_Nul)) put_tag=False;
                  if(put_tag)
                  {
//                   if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, (KpChar)XC_Nul /* iFatherTag */, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

                     if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  }
                  else
                  {
                     if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
                     {
//                      if(TvStrChr(lpszSpcEol, *i_delim_buf)!=NULL)
//                         retc=lpOutFile->PutCharProc(C_Spc, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc))
                           retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     }
                  }
               }
            }

            if(SUCCEEDED(retc))
            {
// jei i_delim_buf baigiasi fonto perjungimu ir po atskyreju eilutes is karto bus tarpas,
// pries ta fonto perjungima irgi reikia tarpo !!!
               retc=PutTexIntStr(lpOutFile, i_delim_buf, piLastChar, (KpChar)XC_PunctMark, this, False, piCurCharPos, iLastWordPos, iNumOfChars, iLastWordRest);

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

//          if((tex_tag != NULL) && SUCCEEDED(retc))
//             if(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL)
//                if(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0)
////                 if(ii>0)
                     if(put_tag && SUCCEEDED(retc))
                        retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
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
const KpChar iazColon[]={C_Colon, C_Nul}; // ":"
// const int iazEllipsis[]={C_Dots, C_Nul}; // "..."
long ncols=0;
long border=1;

// destroys m_iPrevOutTag
HRESULT XmlNode::WriteTex(TvTexFile *lpOutFile, int *piCurCharPos,
                              int iLastWordPos, int iLastWordRest, int iNumOfChars,
                              KpChar iFatherTag, 
                           // KpChar iFirstTag, KpChar iLastTag, 
                              KpChar iPrevTag, KpChar *piLastChar,
                              bool bTagFormat)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *br1=NULL;
XmlNode *br2=NULL;
XmlNode *first_child=NULL;
XmlTagPars *tag_pars=NULL;
KpChar *cont_ptr=NULL;
KpChar cur_tag=C_Nul;
int par_num;
int ii;
unsigned char par_name[TV_TAG_LEN+1];

unsigned char *par_str = null;
   KP_NEWA(par_str, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

KpChar *par_str_i = NULL;
   KP_NEWA(par_str_i, KpChar, MAX_XML_PAR_VAL_LEN + 1);

unsigned char *delim_str = null;
   KP_NEWA(delim_str, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

const unsigned char *delim_ptr=(unsigned char *)"";
unsigned char *ind_ptr=NULL;
KpChar fath_sty_tag;
bool last_w_fl;
int delayed_char=C_Nul;
// KpChar tmp_str[KP_MAX_FILE_LIN_WDT+1];
KpChar chld_tag;
KpChar *chld_cont=NULL;
KpChar prev_out_tag_sav;
static KpChar err_txt_i[KP_MSG_LEN+1];
static unsigned char err_txt[KP_MSG_LEN+1];
const KpChar *pnts=NULL;
unsigned char *pntd=NULL;
static unsigned char out_str[TV_XL_HW_IX_LEN+KP_MSG_LEN+KP_MAX_FILE_LIN_WDT+1];
bool put_tag;
long ll;
bool err_fl;
KpChar fath_sty_gr_tag;
bool math_fl = False;
KpChar tex_tag = C_Nul;
KpChar tex_gr_tag = C_Nul;

   if(
      (
         (lpOutFile==NULL) || 
         (piCurCharPos==NULL) || (piLastChar==NULL) // ||
//       (!(
//          ((iPrevTag >= m_iFirstTag) && (!CheckLastTag(iPrevTag))) ||
//          ((iPrevTag >= XL_FirstSysTag) && (iPrevTag < XL_LastSysTag))
//       )) ||
//       (!(
//          ((iFatherTag >= m_iFirstTag /* iFirstTag */) && (!CheckLastTag(iFatherTag)) /* (iFatherTag < iLastTag) */) ||
//          ((iFatherTag >= XL_FirstSysTag) && (iFatherTag < XL_LastSysTag))
//       ))
      ) &&
      SUCCEEDED(retc) 
     )
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fath_sty_tag=iFatherTag;
      if((fath_sty_tag==XC_Reference) && bTagFormat) fath_sty_tag=(KpChar)XC_HeadWord;

      m_iPrevOutTag = iPrevTag;
   }

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);

      if((iFatherTag==XC_PhrGroup) && (cur_tag==XC_MngGroup)) cur_tag=(KpChar)XC_CpdMngGroup;
      if((iFatherTag==XC_IdiomGroup) && (cur_tag==XC_MngGroup)) cur_tag=(KpChar)XC_IdMngGroup;

#ifdef Debug
// if(cur_tag==XC_Nul)
// cur_tag=XC_Nul;

// if(cur_tag==XC_PartOfSpeechSrc)
// cur_tag=XC_PartOfSpeechSrc;

// if(cur_tag==XC_Img)
// cur_tag=XC_Img;

if(KpErrorProc.lMsgPar==14)
KpErrorProc.lMsgPar=14;

if(cur_tag==(KpChar)XC_Similar)
cur_tag=(KpChar)XC_Similar;
#endif

// -------------
      if((cur_tag==XC_StEntry) && SUCCEEDED(retc))
      {
         if(bTagFormat && SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));

         par_str[0]=Nul;
         if(SUCCEEDED(retc))
         {
            if(tag_pars!=NULL)
            {
               retc=tag_pars->SeekTextPar("id", par_str, &par_num);
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(retc, "id", True, __FILE__, __LINE__, 0L);
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
         }

         put_tag=False;

         if(SUCCEEDED(retc))
         {
//          tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
            tex_tag = GetXml2Tex(cur_tag);
         }
         
         if((tex_tag != C_Nul) && SUCCEEDED(retc))
         {
            put_tag = (plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
            if(put_tag) put_tag = (strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
            if(put_tag)
            {
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

               if(SUCCEEDED(retc))
                  if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] > 0)
                     retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
            }
            else
            {
               if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
               {
//                if(TvStrChr(lpszSpcEol, *par_str)!=NULL)
//                   retc=lpOutFile->PutCharProc(C_Spc, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  if(SUCCEEDED(retc))
                     retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
            }
         }

         if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);

//       if((tex_tag != C_Nul) && SUCCEEDED(retc))
//          if(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL)
//             if(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0)
//                if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] > 0)
                  if(put_tag && SUCCEEDED(retc))
                     retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

         if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(TX_CH_CommentStart, (*piCurCharPos < iLastWordPos)); // '%'
         if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));
      }

      if((!bTagFormat) && SUCCEEDED(retc))
      {
// delimiters
         if((iFatherTag == XC_TranslGroup) && ((cur_tag == XC_MngGroup) || (cur_tag == XC_CpdMngGroup)))
         {
// RLZ06
//          delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(m_iPrevOutTag - m_iFirstTag /* iFirstTag */)/2][(XC_IdMngGroup - m_iFirstTag /* iFirstTag */)/2];
            delim_ptr = GetTagDelimiter(m_iPrevOutTag, XC_IdMngGroup);
         }
         else
         {
//          delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(m_iPrevOutTag - m_iFirstTag /* iFirstTag */)/2][(cur_tag - m_iFirstTag /* iFirstTag */)/2];
            delim_ptr = GetTagDelimiter(m_iPrevOutTag, cur_tag);
         }
//
         if(delim_ptr==NULL) delim_ptr=(unsigned char *)"";

         if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, delim_ptr, cur_tag, tag_pars);

// !!!!
// lpOutFile->PutChar('+', False);
// printf("XC_MngGroup: %d cur_tag: %d >>>%s<<<\n", XC_MngGroup, cur_tag, delim_str);
         if(SUCCEEDED(retc)) retc=WriteTexDelim(lpOutFile, delim_str, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
// lpOutFile->PutChar('+', False);
// lpOutFile->PutChar('+', False);
      }
      else
      {
// Tag names for tagged format
         if((
//          plpszaDictTagOutNames[cur_tag - m_iFirstTag /* iFirstTag */] 
            GetTagOutName(cur_tag)
            == null) && SUCCEEDED(retc))
            retc=loop_brother->ReduceIndentNested();

         if(SUCCEEDED(retc)) retc=loop_brother->GetPrevBrother((KpTreeEntry **)&br1);
         if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&br2);
         if(
            ((cur_tag!=XL_Text) || (br1!=NULL) || (br2!=NULL)) &&
            (
//             plpszaDictTagOutNames[cur_tag - m_iFirstTag /* iFirstTag */] 
               GetTagOutName(cur_tag)
               != NULL) &&
            SUCCEEDED(retc)
           )
         {

            if(cur_tag!=XC_StEntry)
            {
               if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_TG_cr, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(TX_TG_break, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }

            if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc((KpChar)TX_TG_plus, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if(SUCCEEDED(retc)) retc=loop_brother->GetIndentPtr(&ind_ptr);
            if((ind_ptr!=NULL) && SUCCEEDED(retc))
               for(ii=0; (ii<(int)strlen(ind_ptr)/XN_POS_PER_INDENT-1) && SUCCEEDED(retc); ii++)
                  retc=lpOutFile->PutCharProc((KpChar)TX_SP_Amp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            put_tag=False;

            if(SUCCEEDED(retc))
            {
//             tex_tag = iaXml2Tex[XC_FwNote - m_iFirstTag /* iFirstTag */];
               tex_tag = GetXml2Tex(XC_FwNote);

               if(tex_tag != C_Nul)
               {
                  put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
                  if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
                  if(put_tag)
                  {
//                   if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

                     if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  }
                  else
                  {
// jei kitas simbolis tarpas - isvesti pries iaUserTexTagPrefixes[] !!!
                     if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
                        retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  }
               }
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
                        retc=lpOutFile->PutStr(
//                         plpszaDictTagOutNames[XC_Symb - m_iFirstTag /* iFirstTag */] 
                           GetTagOutName(XC_Symb)
                           , (*piCurCharPos < iLastWordPos));
                        break;
                     default:
                        retc=lpOutFile->PutStr(
//                         plpszaDictTagOutNames[cur_tag - m_iFirstTag /* iFirstTag */] 
                           GetTagOutName(cur_tag)
                           , (*piCurCharPos < iLastWordPos));
                        break;
                     }
                  }
                  if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Colon, (*piCurCharPos < iLastWordPos));
//                if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Spc, (*piCurCharPos < iLastWordPos));
//                if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Tab, (*piCurCharPos < iLastWordPos));
               }
               else retc=lpOutFile->PutCharProc((KpChar)TX_TG_forc_sp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }

            if((tex_tag != C_Nul) && SUCCEEDED(retc))
               if(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL)
                  if(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0)
                     retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

            for(ii=0; (ii<XN_VAL_START_TAB) && SUCCEEDED(retc); ii++)
               retc=lpOutFile->PutCharProc((KpChar)TX_SP_Amp, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

            if((cur_tag==XC_Asterix) && SUCCEEDED(retc))
            {
//             tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
               tex_tag = GetXml2Tex(cur_tag);
               
               if(tex_tag != C_Nul)
                  retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }
         }
      }

// -------------------- images
      if((cur_tag==XC_Img) && SUCCEEDED(retc))
      {
         put_tag=False;

//       tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(cur_tag);

         if(tex_tag != C_Nul)
         {
            put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
            if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
            if(put_tag)
            {
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

               if(SUCCEEDED(retc))
                  if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] != 5)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

               if((tag_pars==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
// ---- src
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekTextPar("src", par_str, &par_num);
                  if(retc==KP_E_KWD_NOT_FOUND)
                     retc=KpErrorProc.OutputErrorMessage(retc, "src", True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc))
               {
                  if((TvKpStrChr(iazSpaces, *piLastChar)!=NULL) && (*piLastChar!=C_NBSP))
                     *piLastChar=C_Nul;
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
               }
// ---- height
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekNumPar("height", &ll, &par_num);
                  if(retc==KP_E_KWD_NOT_FOUND)
                     retc=KpErrorProc.OutputErrorMessage(retc, "height", True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)par_str, "%.2f", ll*2.54/300.);
                  retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
// ---- width
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekNumPar("width", &ll, &par_num);
                  if(retc==KP_E_KWD_NOT_FOUND)
                     retc=KpErrorProc.OutputErrorMessage(retc, "width", True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)par_str, "%.2f", ll*2.54/300.);
                  retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
                  retc=lpOutFile->PutStrProc((const unsigned char *)"-0.5", (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
// ---- scale
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekNumPar("scale", &ll, &par_num);
                  if(retc==KP_E_KWD_NOT_FOUND)
                     retc=KpErrorProc.OutputErrorMessage(retc, "scale", True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)par_str, "%d", ll);
                  retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
// ---- pvacor
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekTextPar("pvacor", par_str, &par_num);
                  if(SUCCEEDED(retc))
                     retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  else if(retc==KP_E_KWD_NOT_FOUND)
                     retc=lpOutFile->PutStrProc((const unsigned char *)"-8pt", (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
// ---- pvbcor
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekTextPar("pvbcor", par_str, &par_num);
                  if(SUCCEEDED(retc))
                     retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  else if(retc==KP_E_KWD_NOT_FOUND)
                     retc=lpOutFile->PutStrProc((const unsigned char *)"0pt", (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
// ---- pvccor
               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekTextPar("pvccor", par_str, &par_num);
                  if(SUCCEEDED(retc))
                     retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
                  else if(retc==KP_E_KWD_NOT_FOUND)
                     retc=lpOutFile->PutStrProc((const unsigned char *)"-10pt", (*piCurCharPos < iLastWordPos), iLastWordRest);
               }
               if(SUCCEEDED(retc))
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
            }
         }

      } // if((cur_tag==XC_Img) && SUCCEEDED(retc))

// -------------------- equiations
      if((cur_tag==XC_Equiation) && SUCCEEDED(retc))
      {
         put_tag=False;

//       tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(cur_tag);

         if(tex_tag != C_Nul)
         {
            put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
            if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
            if(put_tag)
            {
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

               if(SUCCEEDED(retc))
                  if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] != 1)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

               if((tag_pars==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
                  retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc))
               {
                  retc=tag_pars->SeekTextPar("src", par_str, &par_num);
                  if(retc==KP_E_KWD_NOT_FOUND)
                     retc=KpErrorProc.OutputErrorMessage(retc, "src", True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc))
               {
                  if((TvKpStrChr(iazSpaces, *piLastChar)!=NULL) && (*piLastChar!=C_NBSP))
                     *piLastChar=C_Nul;
                  retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
               }
            }
         }

      } // if((cur_tag==XC_Equiation) && SUCCEEDED(retc))

// -------------------- lists
      if((cur_tag==XC_Enum) && SUCCEEDED(retc))
      {
         put_tag=False;

//       tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(cur_tag);

         if(tex_tag != C_Nul)
         {
            put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
            if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
            if(put_tag)
            {
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

               if((tag_pars!=NULL) && SUCCEEDED(retc))
               {
                  if(SUCCEEDED(retc))
                  {
                     retc=tag_pars->SeekTextPar("class", par_str, &par_num);
                     if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                     else
                     {
                        if(SUCCEEDED(retc))
                           retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                        if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc))
                        {
                           if((TvKpStrChr(iazSpaces, *piLastChar)!=NULL) && (*piLastChar!=C_NBSP))
                              *piLastChar=C_Nul;
                           retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
                        }
                     }
                  }

                  if(SUCCEEDED(retc))
                  {
//                   retc=tag_pars->SeekTextPar("num", par_str, &par_num);
                     retc=tag_pars->SeekKpTextPar("num", par_str_i, &par_num); // gali buti bulletai
                     if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                     else
                     {
                        if(SUCCEEDED(retc))
                           retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
//                      if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc)) retc=lpOutFile->PutKpStrProc(par_str_i, (*piCurCharPos < iLastWordPos), iLastWordRest);
                        if(SUCCEEDED(retc))
                        {
                           if((TvKpStrChr(iazSpaces, *piLastChar)!=NULL) && (*piLastChar!=C_NBSP))
                              *piLastChar=C_Nul;
                           retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
                        }
                     }
                  }
               }

// dedam {}, nes blogai, kai saraso elementas prasideda ne tekstu, o, pavyzdziui, nuoroda
               if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
            }
         }

      } // if((cur_tag==XC_Enum) && SUCCEEDED(retc))

// -------------------- tables
      if((cur_tag==XC_Table) && SUCCEEDED(retc))
      {
//       tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(cur_tag);

         retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

         if((tag_pars==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            retc=tag_pars->SeekNumPar("ncols", &ncols, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
               retc=KpErrorProc.OutputErrorMessage(retc, "ncols", True, __FILE__, __LINE__, 0L);
         }
         if(SUCCEEDED(retc)) retc=FormatRoman(par_str, ncols);
         if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);

         if(SUCCEEDED(retc))
         {
            retc=tag_pars->SeekNumPar("border", &border, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
            {
               border=1;
//             retc=KpErrorProc.OutputErrorMessage(retc, "border", True, __FILE__, __LINE__, 0L);
               retc = S_OK;
            }
         }
         if(SUCCEEDED(retc))
            retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
         if(SUCCEEDED(retc))
         {
            sprintf((char *)par_str, "%ld", border);
            retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
         }
         if(SUCCEEDED(retc))
            retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

         for(ii=0; (ii<ncols) && SUCCEEDED(retc); ii++)
         {
            sprintf((char *)par_name, "width%d", ii+1);
            retc=tag_pars->SeekTextPar(par_name, par_str, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND)
               retc=KpErrorProc.OutputErrorMessage(retc, par_name, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc))
               retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
            if(SUCCEEDED(retc))
               retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
            if(SUCCEEDED(retc))
               retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
         }
         if(SUCCEEDED(retc))
            retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
         if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Lf, False);

      } // if((cur_tag==XC_Table) && SUCCEEDED(retc))

// ----
      if((cur_tag==XC_TableRow) && SUCCEEDED(retc))
      {
//       tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(cur_tag);

         retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

         if(SUCCEEDED(retc)) retc=FormatRoman(par_str, ncols);
         if(SUCCEEDED(retc)) retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);

         if(SUCCEEDED(retc))
            retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
         if(SUCCEEDED(retc))
         {
            sprintf((char *)par_str, "%ld", border);
            retc=lpOutFile->PutStrProc(par_str, (*piCurCharPos < iLastWordPos), iLastWordRest);
         }
         if(SUCCEEDED(retc))
            retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
      }

      if((cur_tag==XC_TableCell) && SUCCEEDED(retc))
         retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));


// --------------------
      prev_out_tag_sav = m_iPrevOutTag;
      m_iPrevOutTag = cur_tag;

// contents start
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;
      
      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// ------ single tags
      if((first_child==NULL) && (cont_ptr==NULL) && (cur_tag!=XC_Img) && (cur_tag!=XC_Equiation) && SUCCEEDED(retc))
      {
//       tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(cur_tag);

         if(tex_tag != C_Nul)
         {
            put_tag=True;
            if((tex_tag >= TX_FirstUserTagCode) && (tex_tag <= TX_LastUserTagCode))
            {
               put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
               if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
            }
            if(put_tag) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
         }
      }

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc))
      {
         if((cont_ptr!=NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

         put_tag=False;

#ifdef Debug
if(cur_tag==(KpChar)XC_Nul)
cur_tag=(KpChar)XC_Nul;
#endif

         if(SUCCEEDED(retc))
         {
//          tex_tag = iaXml2Tex[cur_tag - m_iFirstTag /* iFirstTag */];
            tex_tag = GetXml2Tex(cur_tag);

            if(tex_tag != C_Nul)
            {
               if((tex_tag >= TX_FirstUserTagCode) && (tex_tag <= TX_LastUserTagCode))
               {
                  put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
                  if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
               }
               if(put_tag) put_tag=(TvKpStrChr(uiazXmlGrTags, cur_tag)!=NULL); // !!!! kazkodel veikia, nors turetu buti ==NULL???
               if(cur_tag==XC_StEntry) put_tag=False;
               if(put_tag)
               {
                  if((cur_tag!=XC_Enum) && SUCCEEDED(retc))
                  {
//                   if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                     if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);
//                   if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                  }

                  if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               }
            }
         }

         if(SUCCEEDED(retc)) retc = lpOutFile->GetMathFlag(&math_fl);

         if(
            ((cur_tag==XC_EquInline) || ((cur_tag==XC_Super) && (!math_fl))) && 
            SUCCEEDED(retc)
           )
            retc=PutTexChar(lpOutFile, (KpChar)TX_SP_MathField, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

         if(cur_tag==XC_Paragraph) retc=first_child->WriteTex(lpOutFile, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars, iFatherTag, (KpChar)XC_Nul, piLastChar, bTagFormat);
         else retc=first_child->WriteTex(lpOutFile, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars, cur_tag, (KpChar)XC_Nul, piLastChar, bTagFormat);

         if(
            ((cur_tag==XC_EquInline) || ((cur_tag==XC_Super) && (!math_fl))) && 
            SUCCEEDED(retc)
           )
            retc=PutTexChar(lpOutFile, (KpChar)TX_SP_MathField, piLastChar, True, iFatherTag, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

         if(put_tag && SUCCEEDED(retc))
            retc=lpOutFile->CloseField(True, (*piCurCharPos < iLastWordPos));
      }

// dvitaskis po kategoriju - prilipdyti prie toliau esancio teksto

// if(iFatherTag==XC_CtgGroup)
// iFatherTag=XC_CtgGroup;

      if(
         ((iFatherTag==XC_CtgGroup) || (iFatherTag==XC_MngGroup)) &&
         (cur_tag==XC_PunctMark) &&
         (prev_out_tag_sav==XC_Nul) &&
         SUCCEEDED(retc)
        )
      {
         if(first_child==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=first_child->GetNodeTag(&chld_tag);
         if((chld_tag!=XL_Text) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) retc=first_child->GetContentsPtr(&chld_cont);
         if((chld_cont==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            if(TvKpStrCmp(chld_cont, iazColon)==0)
               retc=PutTexChar(lpOutFile, C_NBSP, piLastChar, True, fath_sty_tag,
                  piCurCharPos, iLastWordPos, iLastWordRest, NULL);
         }
      }

// current tag with contents
      if((cont_ptr!=NULL) && SUCCEEDED(retc)) if(cont_ptr[0]!=C_Nul)
      {
#ifdef Debug
if(cont_ptr[0]==C_Vertl) // '|'
ii=C_Vertl;
#endif
         if(cur_tag!=XL_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

// contents
         if(SUCCEEDED(retc))
         {
//          if(iFatherTag!=XC_TechNote)
            {
//             tex_tag = iaXml2Tex[fath_sty_tag - m_iFirstTag /* iFirstTag */];
               tex_tag = GetXml2Tex(fath_sty_tag);

               if((tex_tag == C_Nul) && (iFatherTag != XC_LevelGroup) && (iFatherTag != XC_Special))
               {
                  fath_sty_gr_tag = 
//                   uiazXmlParGrTags[fath_sty_tag - m_iFirstTag /* iFirstTag */];
                     GetXmlParGrTag(fath_sty_tag);

//                tex_gr_tag = C_Nul;
//                if(fath_sty_gr_tag != C_Nul) tex_gr_tag = iaXml2Tex[fath_sty_gr_tag - m_iFirstTag /* iFirstTag */];
                  tex_gr_tag = GetXml2Tex(fath_sty_gr_tag);

                  err_fl = False;
                  if(fath_sty_gr_tag == C_Nul) err_fl = True;
                  else if(tex_gr_tag == C_Nul) err_fl = True;
                  else if(!
//                   baXmlDictTagsFreeText[fath_sty_tag - m_iFirstTag /* iFirstTag */]
                     TestTagFreeText(fath_sty_tag)
                     ) err_fl = True;
                  if(err_fl)
                  {
//                   if(TvIntStrCmp(cont_ptr, iazEllipsis)!=0)
                     {
//                      retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, (const unsigned char *)"Laisvas tekstas", FALSE, __FILE__, __LINE__, 0L);
                        TvKpStrNCpy(err_txt_i, cont_ptr, KP_MSG_LEN);
                        err_txt_i[KP_MSG_LEN]=C_Nul;
                        TvKpStrLat(err_txt_i);
                        pnts=err_txt_i;
                        pntd=err_txt;
                        while(*pnts) *(pntd++)=(unsigned char)(*pnts++);
                        *pntd=Nul;
                        sprintf((char *)out_str, "Lizdas %ld, hw:\"%s\" tag:%d laisvas tekstas: \"%s\"; File: %s Line: %d\n",
                           KpErrorProc.lMsgPar, KpErrorProc.szaMsgText, fath_sty_gr_tag, err_txt, __FILE__, __LINE__);
                        printf((const char *)out_str);
                     }
                  }
               }

               if(SUCCEEDED(retc))
               {
//                TvIntStrNCpy(tmp_str, cont_ptr, KP_MAX_FILE_LIN_WDT);
//                tmp_str[KP_MAX_FILE_LIN_WDT]=C_Nul;
//                retc=CutInitTrailSpcsInt(tmp_str);
                  if(SUCCEEDED(retc))
                  {
// !!!!
// lpOutFile->PutChar('*', False);

                     // flush spaces - o kam?
//                   delayed_char=C_Nul;
//                   retc=PutTexChar(lpOutFile, *cont_ptr, piLastChar, True, fath_sty_tag,
//                      piCurCharPos, iLastWordPos, iLastWordRest, &delayed_char);

// lpOutFile->PutChar('*', False);
// lpOutFile->PutChar('*', False);

//                   ii = TvIntStrLen(tmp_str);
//                   if(tex_tag == C_Nul) ii = 0;

//                   if(ii > 0)
                     {
                        put_tag = False;

                        if(tex_tag != C_Nul)
                        {
                           put_tag = (plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
                           if(put_tag) put_tag = (strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
                           if(put_tag)
                           {
//                            if(SUCCEEDED(retc)) retc = FlushSpaces(lpOutFile, bSkipLineOnSpace, piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

                              if((fath_sty_tag != XC_Enum) && SUCCEEDED(retc))
                              {
//                               if(SUCCEEDED(retc)) retc = lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                                 if(SUCCEEDED(retc)) retc = PutTexChar(lpOutFile, tex_tag, piLastChar, True, (KpChar)XC_Nul, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

//                               if(SUCCEEDED(retc))
//                                  if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] > 0)
//                                     retc = lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                              }

                              if(SUCCEEDED(retc))
                                 if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] > 0)
                                    retc = lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
                           }
                           else
                           {
                              if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
                              {
//                               if(TvStrChr(lpszSpcEol, *cont_ptr)!=NULL)
//                                  retc=lpOutFile->PutCharProc(C_Spc, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                                 if(SUCCEEDED(retc))
                                    retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
                              }
                           }
                        }
                     }

//                   if((delayed_char!=C_Nul) && SUCCEEDED(retc))
//                   {
//                      (*piCurCharPos)++;
//                      retc=lpOutFile->PutCharProc(delayed_char, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
//                   }

                     if((fath_sty_tag==XC_Special) && SUCCEEDED(retc))
                        retc = FlushSpaces(lpOutFile, True, piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

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
                        if((tex_tag != C_Nul) && SUCCEEDED(retc))
                           if(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL)
                              if(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0)
                                 if(iaUserTexTagArgs[tex_tag - TX_FirstUserTagCode] > 0)
                                    retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
                  }
               }
            }
         }
      }

// --------------------------- tables completion
      if((cur_tag==XC_TableCell) && SUCCEEDED(retc))
         retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);

      if((cur_tag==XC_TableRow) && SUCCEEDED(retc))
         if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Lf, False);

      if((cur_tag==XC_Table) && SUCCEEDED(retc))
      {
         ncols=0;
         border=1;
         retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
         if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(C_Lf, False);
      }

// to next brother
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))

#ifdef Debug
if((cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup))
{
ii=0;
}
#endif

// -------------
// last tag in group - delimiter
   if((!bTagFormat || (cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup)) && SUCCEEDED(retc))
   {
//    delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(cur_tag - m_iFirstTag /* iFirstTag */)/2][(XC_Nul - m_iFirstTag /* iFirstTag */)/2];
      delim_ptr = GetTagDelimiter(cur_tag, XC_Nul);
      if(delim_ptr==NULL) delim_ptr=(unsigned char *)"";

      if(SUCCEEDED(retc))
         if(strlen(delim_ptr)>=KP_MAX_FILE_LIN_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc)) strcpy(delim_str, delim_ptr);

// !!!!
// lpOutFile->PutChar('!', False);
      if(SUCCEEDED(retc)) retc=WriteTexDelim(lpOutFile, delim_str, piLastChar, piCurCharPos, iLastWordPos, iLastWordRest, iNumOfChars);
// lpOutFile->PutChar('!', False);
// lpOutFile->PutChar('!', False);

   }

// -------------
   if((cur_tag==XC_HeadWordGroup) && SUCCEEDED(retc))
   {
      retc=lpOutFile->GetLastWordInParFl(&last_w_fl);
      if(last_w_fl && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, False, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
         if(SUCCEEDED(retc)) retc=lpOutFile->SetLastWordInParFl(False);
      }

      if(bTagFormat && SUCCEEDED(retc))
         retc=lpOutFile->PutCharProc((KpChar)TX_TG_cr, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);

      if(SUCCEEDED(retc)) if(*piLastChar!=C_Nul)
      {
//       if(TvIntStrChr((const int *)iazSpaces, *piLastChar)==NULL)
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         *piLastChar=C_Nul;
      }
   }

   if((cur_tag==XC_StEntry) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=lpOutFile->PutChar(Lf, (*piCurCharPos < iLastWordPos));

      put_tag=False;

      if(SUCCEEDED(retc))
      {
//       tex_tag = iaXml2Tex[XC_StEntry_e - m_iFirstTag /* iFirstTag */];
         tex_tag = GetXml2Tex(XC_StEntry_e);

         if(tex_tag != C_Nul)
         {
            put_tag=(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode] != NULL);
            if(put_tag) put_tag=(strlen(plpszaUserTexTagTable[tex_tag - TX_FirstUserTagCode]) > 0);
            if(put_tag)
            {
//             if(SUCCEEDED(retc)) retc=lpOutFile->PutCharProc(tex_tag, TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
               if(SUCCEEDED(retc)) retc=PutTexChar(lpOutFile, tex_tag, piLastChar, True, (KpChar)XC_Nul, piCurCharPos, iLastWordPos, iLastWordRest, NULL);

               if(SUCCEEDED(retc)) retc=lpOutFile->OpenField(True, (*piCurCharPos < iLastWordPos));
               if(SUCCEEDED(retc)) retc=CloseField(lpOutFile, True, (*piCurCharPos < iLastWordPos), piLastChar, iLastWordRest, piCurCharPos, iLastWordPos);
            }
            else
            {
// jei kitas simbolis tarpas - isvesti pries iaUserTexTagPrefixes[] !!!
               if(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode] != C_Nul)
                  retc=lpOutFile->PutCharProc(iaUserTexTagPrefixes[tex_tag - TX_FirstUserTagCode], TexNoType, (*piCurCharPos < iLastWordPos), iLastWordRest);
            }
         }
      }
   }

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc))
//    retc=pNextBrother->WriteTex(lpOutFile, piCurCharPos, iLastWordPos, iLastWordRest, cur_tag, cur_tag, piLastChar, bTagFormat, iLastWordRest);

   KP_DELETEA(par_str);
   KP_DELETEA(par_str_i);
   KP_DELETEA(delim_str);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::CountCharactersTex(int *piNumOfChars, /* KpChar iFirstTag, */ KpChar iPrevTag, bool bTagFormat)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
KpChar *cont_ptr=NULL;
KpChar cur_tag=C_Nul;
XmlTagPars *tag_pars=NULL;
const unsigned char *delim_ptr=(unsigned char *)"";

   if(
      (
         (piNumOfChars == NULL) // ||
//       (!(
//          ((iPrevTag >= m_iFirstTag) && (!CheckLastTag(iPrevTag))) ||
//          ((iPrevTag >= XL_FirstSysTag) && (iPrevTag < XL_LastSysTag))
//       ))
      ) && 
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) m_iPrevOutTag = iPrevTag;

// loop on brothers
   loop_brother=this;
   while((loop_brother!=NULL) && SUCCEEDED(retc))
   {
      retc=loop_brother->GetNodeTag(&cur_tag);
      if(SUCCEEDED(retc)) retc=loop_brother->GetTagParsPtr(&tag_pars);

// delimiters
      if((!bTagFormat) && SUCCEEDED(retc))
      {
//       delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(m_iPrevOutTag - m_iFirstTag /* iFirstTag */)/2][(cur_tag - m_iFirstTag /* iFirstTag */)/2];
         delim_ptr = GetTagDelimiter(m_iPrevOutTag, cur_tag);
         if((delim_ptr!=NULL) && SUCCEEDED(retc))
         {
            *piNumOfChars+=DelimStrLenTex(delim_ptr, cur_tag, tag_pars);

// int ii;
// printf("1---- %d\n", DelimStrLenTex(delim_ptr, cur_tag, tag_pars));
// if((DelimStrLenTex(delim_ptr, cur_tag, tag_pars)==8) && (KpErrorProc.lMsgPar==19))
// ii=DelimStrLenTex(delim_ptr, cur_tag, tag_pars);

         }
      }

      m_iPrevOutTag = cur_tag;

// contents start
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;
      
      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc))
         retc=first_child->CountCharactersTex(piNumOfChars, (KpChar)XC_Nul, bTagFormat);

// contents
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XL_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            *piNumOfChars+=XmlnKpStrLen(cont_ptr);

// printf("2---- %d\n", TvIntStrLen(cont_ptr));

         }
      }

// to next brother
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))


// last tag in group - delimiter
   if((!bTagFormat || (cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup)) && SUCCEEDED(retc))
   {
//    delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(cur_tag - m_iFirstTag /* iFirstTag */)/2][(XC_Nul - m_iFirstTag /* iFirstTag */)/2];
      delim_ptr = GetTagDelimiter(cur_tag, XC_Nul);
      if((delim_ptr!=NULL) && SUCCEEDED(retc))
      {
         *piNumOfChars+=DelimStrLenTex(delim_ptr, (KpChar)XC_Nul, NULL);

// printf("3---- %d\n", DelimStrLenTex(delim_ptr, (KpChar)XC_Nul, NULL));

      }
   }

// recursion on brothers
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->CountCharacters(piNumOfChars, cur_tag, bTagFormat);

return(retc);
}


//-----------------------------------
HRESULT XmlNode::GetLastWordPosTex(int *piLastWordPos, int *piLastWordRest, int *piCurCharPos, int iNumOfChars, 
/* KpChar iFirstTag, */ KpChar iPrevTag, bool bTagFormat)
{
HRESULT retc=S_OK;
XmlNode *loop_brother=NULL;
XmlNode *first_child=NULL;
KpChar *cont_ptr=NULL;
KpChar cur_tag=C_Nul;
XmlTagPars *tag_pars=NULL;
const unsigned char *delim_ptr=(unsigned char *)"";
const KpChar *pnti=NULL;
static KpChar i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
static unsigned char delim_str[KP_MAX_FILE_LIN_LEN+1];
int ii;

   if(
      (
         (piLastWordPos==NULL) || (piLastWordRest==NULL) || (piCurCharPos==NULL) // ||
//       (iPrevTag < m_iFirstTag) || CheckLastTag(iPrevTag)
      ) &&
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) m_iPrevOutTag = iPrevTag;

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
//       delim_ptr=(const unsigned char *)lpszXmlTagDelimiters[(m_iPrevOutTag - m_iFirstTag /* iFirstTag */)/2][(cur_tag - m_iFirstTag /* iFirstTag */)/2];
         delim_ptr = GetTagDelimiter(m_iPrevOutTag, cur_tag);
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
                  if(TvKpStrChr(iazSpcEol, *pnti)!=NULL)
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

      m_iPrevOutTag = cur_tag;

// contents start
//    if(SUCCEEDED(retc)) retc = loop_brother->GetFirstChild((KpTreeEntry **)&first_child);
      if(SUCCEEDED(retc)) first_child = (XmlNode *)loop_brother->m_pFirstChild;
      
      if(SUCCEEDED(retc)) retc=loop_brother->GetContentsPtr(&cont_ptr);
      if((first_child!=NULL) && (cont_ptr!=NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

// recursion on children
      if((first_child!=NULL) && SUCCEEDED(retc))
         retc=first_child->GetLastWordPosTex(piLastWordPos, piLastWordRest, piCurCharPos, iNumOfChars, (KpChar)XC_Nul, bTagFormat);

// contents
      if((cont_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(cur_tag!=XL_Text)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            pnti=cont_ptr;
            while((*pnti) && SUCCEEDED(retc))
            {
               if(*pnti==(KpChar)NS_CTRL_START) // '$'
               {
                  pnti++;
                  switch(*pnti++)
                  {
// font style
                  case 'f':
                     for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnti)); ii++) pnti++;
                     (*piCurCharPos)+=3;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
                     if(TvStrChr(lpszSpcEol, *pnti)!=NULL) (*piCurCharPos)++;
                     break;

// paragraph style
                  case 's':
                     for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnti)); ii++) pnti++;
                     break;

// unicode character
                  case 'u':
                     for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit(*pnti)); ii++) pnti++;
                     (*piCurCharPos)++;
                     break;

// condensed font
                  case 'q':
                     for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnti)); ii++) pnti++;
                     (*piCurCharPos)+=11;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
                     if(TvStrChr(lpszSpcEol, *pnti)!=NULL) (*piCurCharPos)++;
                     break;

#if FALSE // jau nebe, vidiniam formate ðitos $-poros jau konvertuotos á KpChar
// output of spec. chars
                  case NS_CTRL_START:  // '$' itself
                  case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
//                case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
                  case C_Numb:         // '#' itself, single '#' --> C_QemSpc
                  case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstø á TX_TG_BD
                  case C_Bpoint:       // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR
// formatting symbols
                  case C_Underl:       // "$_" --> C_NBSP
                  case C_At:           // "$@" --> C_Ff
                  case C_Circ:         // "$^" --> C_hbreak
                  case C_Point:        // "$." --> C_NullSpc
#endif
                  case C_Lbrack:       // '[' itself, single '[' --> \rm
                  case C_Rbrack:       // ']' itself, single ']' --> end of \rm
                  case C_Lcurl:        // '{' itself, single '{' --> \bf
                  case C_Rcurl:        // '}' itself, single '}' --> end of \bf
                     (*piCurCharPos)++;
                     break;

                  default:
                     (*piCurCharPos)+=2;
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
                     break;
                  }
               }
               else // if(*pnti==NS_CTRL_START) // '$'
               {
                  if(TvKpStrChr(iazSpcEol, *pnti)!=NULL)
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
      if(SUCCEEDED(retc)) retc=loop_brother->GetNextBrother((KpTreeEntry **)&loop_brother);

   } // while((loop_brother!=NULL) && SUCCEEDED(retc))


// last tag in group - delimiter
   if((!bTagFormat || (cur_tag==XC_StEntry) || (cur_tag==XC_HeadWordGroup)) && SUCCEEDED(retc))
   {
//    delim_ptr = (const unsigned char *)lpszXmlTagDelimiters[(cur_tag - m_iFirstTag /* iFirstTag */)/2][(XC_Nul - m_iFirstTag /* iFirstTag */)/2];
      delim_ptr = GetTagDelimiter(cur_tag, XC_Nul);
      if((delim_ptr!=NULL) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, delim_ptr, (KpChar)XC_Nul, NULL);
         if(SUCCEEDED(retc)) retc=GenTexDelimStr(i_delim_buf, delim_str);

         pnti=i_delim_buf;
         while((*pnti) && SUCCEEDED(retc))
         {
//          retc=SkipDelimCtrlChars(&pnts);
            if(SUCCEEDED(retc))
            {
               if(TvKpStrChr(iazSpcEol, *pnti)!=NULL)
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
// if((pNextBrother!=NULL) && SUCCEEDED(retc)) retc=pNextBrother->GetLastWordPos(piLastWordPos, piCurCharPos, iNumOfChars, cur_tag, bTagFormat)

return(retc);
}


//-----------------------------------
int XmlNode::DelimStrLenTex(const unsigned char *lpszDelimPtr, KpChar iCurTag, XmlTagPars *pTagPars)
{
HRESULT retc=S_OK;
int str_len=0;
KpChar i_delim_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned char delim_str[KP_MAX_FILE_LIN_LEN+1];


   if(
      (
         (lpszDelimPtr == NULL) // || 
//       (iCurTag < m_iFirstTag) || CheckLastTag(iCurTag)
      ) && 
      SUCCEEDED(retc)
     )
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

/*
const unsigned char *pnts;

   if(SUCCEEDED(retc))
   {
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
   }
*/

   if(SUCCEEDED(retc)) retc=ExpParDelimStr(delim_str, lpszDelimPtr, iCurTag, pTagPars);
   if(SUCCEEDED(retc)) retc=GenTexDelimStr(i_delim_buf, delim_str);
   if(SUCCEEDED(retc)) str_len=TvKpStrLen(i_delim_buf);

return(str_len);
}


//-----------------------------------
int XmlNode::XmlnKpStrLen(const KpChar *piValPtr)
{
HRESULT retc=S_OK;
const KpChar *pnts;
int retv=0;
int ii;

   pnts=piValPtr;
   while((*pnts) && SUCCEEDED(retc))
   {
      if((*pnts++)==(KpChar)NS_CTRL_START) // '$'
      {
         switch(*pnts++)
         {
// font style
         case 'f':
            for(ii=0; (ii<NS_STY_NO_WDT) && (isdigit(*pnts)); ii++) pnts++;
            retv+=3;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
            if(TvStrChr(lpszSpcEol, *pnts)!=NULL) retv++;
            break;

// paragraph style
         case 's':
            for(ii=0; (ii<NS_PAR_STY_WDT) && (isdigit(*pnts)); ii++) pnts++;
            break;

// unicode character
         case 'u':
            for(ii=0; (ii<NS_UNI_CODE_WDT) && (TvIsHexDigit(*pnts)); ii++) pnts++;
            retv++;
            break;

// condensed font
         case 'q':
            for(ii=0; (ii<NS_COND_FNT_WDT) && (isdigit(*pnts)); ii++) pnts++;
            retv+=11;

// isvedamas tarpas pries TexCmd tipo Tex komandas, jei po to yra tarpas
// !!! nesuveiks, jei eilute jau pasibaige
            if(TvStrChr(lpszSpcEol, *pnts)!=NULL) retv++;
            break;

#if FALSE // jau nebe, vidiniam formate ðitos $-poros jau konvertuotos á KpChar
// output of spec. chars
         case NS_CTRL_START:  // '$' itself
         case C_Lslash:       // '\\' itself, single '\\' --> C_hyph
//       case C_Amp:          // '&' itself, single '&' --> '-' + C_hbreak
         case C_Numb:         // '#' itself, single '#' --> C_QemSpc

         case C_Vertl:        // '|' itself, kad TV_XM_CompDelim nepaverstø á TX_TG_BD
         case C_Bpoint:       // bullet itself, kad nenumestø DOUBLE_ENTRIES_KPCHAR
// formatting symbols
         case C_Underl:       // "$_" --> C_NBSP
         case C_At:           // "$@" --> C_Ff
         case C_Circ:         // "$^" --> C_hbreak
         case C_Point:        // "$." --> C_NullSpc
#endif
         case C_Lbrack:       // '[' itself, single '[' --> \rm
         case C_Rbrack:       // ']' itself, single ']' --> end of \rm
         case C_Lcurl:        // '{' itself, single '{' --> \bf
         case C_Rcurl:        // '}' itself, single '}' --> end of \bf
            retv++;
            break;

         default:
//          retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, null, False, __FILE__, __LINE__, 0L);
            retv+=2;
            break;
         }
      }
      else // if((*pnts++)==NS_CTRL_START) // '$'
         retv++;
   }

return(retv);
}


// --------------------------------------------
KpChar GetXml2Tex(KpChar iTag)
{
HRESULT retc = S_OK;
KpChar tex_tag = C_Nul;

   if((iTag >= XC_FirstDictTag) && (iTag < XC_LastDictTag))
   {
      tex_tag = iaXml2Tex[iTag - XC_FirstDictTag];
      if(((tex_tag < TX_FirstUserTagCode) || (tex_tag > TX_LastUserTagCode)) && (tex_tag != C_Nul) && SUCCEEDED(retc))
      {
         tex_tag = C_Nul;
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
      }
   }

// return(retc);      
return(tex_tag);
}
