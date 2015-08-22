// ==================================================
// tvrtfi.cpp
// RTF file for input


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

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kperr.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlh.h"
#include "xmlp.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "tvrtf.h"
#include "tvrtfi.h"


// ================================================== private methods of TvRtfI
// --------------------------------------------------
HRESULT TvRtfI::SkipChars(const unsigned char *lpszChars)
{
HRESULT retc=S_OK;
unsigned char ch1;
bool reached=FALSE;
bool eof_fl=FALSE;

   do
   {
      retc=GetChar(&ch1, FALSE);
      if(SUCCEEDED(retc))
      {
         reached=(TvStrChr(lpszChars, (KpChar)ch1)==NULL);
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
HRESULT TvRtfI::SkipCharsProc(const unsigned char *lpszChars)
{
HRESULT retc=S_OK;
KpChar ch1;
bool reached=FALSE;
bool eof_fl=FALSE;

   do
   {
      retc=GetCharProc(&ch1, FALSE);
      if(SUCCEEDED(retc))
      {
         reached=(TvStrChr(lpszChars, ch1)==NULL);
         if(reached) retc=UnGetCharProc(ch1);
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
HRESULT TvRtfI::CharEncode(KpChar *puiOutChar, const unsigned char cInChar)
{
HRESULT retc=S_OK;
int cur_font;
int kpt_tbl;
KpChar *conv_tbl;

   *puiOutChar=C_Nul;

// no conversion if cInChar<Spc (cInChar<0x80 ???!!!)
// if(cInChar<Spc /* KPT_FirstKptChar */) *puiOutChar=(KpChar)cInChar;
// else
   {
      if(pCurrentField==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

      if(pFonts==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         retc=pCurrentField->GetFont(&cur_font);
         if(cur_font==RT_FONT_UNDEFINED) cur_font=0;
      }

      if(SUCCEEDED(retc))
         if(((cur_font<0) || (cur_font>=RT_MAX_NUM_OF_FONTS)) && (cur_font!=RT_FONT_UNDEFINED))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         if(cur_font!=RT_FONT_UNDEFINED)
            retc=pFonts[cur_font].GetKptCodeTable(&kpt_tbl);
         else kpt_tbl=1; // ASCII
      }
      if(SUCCEEDED(retc)) if((kpt_tbl<0) || (kpt_tbl>=KPT_Ctnum))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);

//    if(SUCCEEDED(retc)) if(cInChar>=KPT_Ctbsiz)
//       retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         if(cInChar<KPT_Ctbsiz/2)
         {
            conv_tbl=Ctptr8[kpt_tbl*2];
            if(conv_tbl==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) *puiOutChar=conv_tbl[cInChar];
         }
         else
         {
            conv_tbl=Ctptr8[kpt_tbl*2+1];
            if(conv_tbl==NULL)
            {
//             if((cInChar<C_CharSize0) && (cInChar>=0))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
//             else
//                retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
            }
            if(SUCCEEDED(retc)) *puiOutChar=conv_tbl[cInChar-KPT_Ctbsiz/2];
         }
      }

   } // if(cInChar<KPT_FirstKptChar) *puiOutChar=cInChar;

   if((retc==KP_E_FONT_UNDEF) || (retc==KP_E_UNKN_CHR))
   {
//    *puiOutChar=(KpChar)cInChar;
      *puiOutChar=C_Quest;
      retc=S_OK;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::ProcessKeyword
(
KpChar *puiInChar,
bool *pbInChFlg,
RT_FieldTypes *piFieldType,
int *piCurFont,
const unsigned char *lpszKeywrd,
const long lNumVal,
const unsigned char *lpszTextVal
)
{
HRESULT retc=S_OK;
int idx;
RT_FieldTypes field_type;
RT_RTF_FieldTypes rtf_field_type;
int cur_font;
bool font_defined;
int kpt_cset;
long tb_wdt;
int col_num;

   *pbInChFlg=FALSE;
   *puiInChar=C_Nul;

   if((pCurrentField==NULL) || (pFonts==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFont(&cur_font);

   if(SUCCEEDED(retc))
      retc=GetKwrdIndex(&idx, lpszKeywrd, (const unsigned char **)plpszaRtfTagTable, -1, False, True);

   if(SUCCEEDED(retc))
   {
// --------------------------------------------------
      switch(idx)
      {

// ----------------------- unprocessed tags
      case RT_TG_Rtf:
      case RT_TG_Ansi:
      case RT_TG_AnsiCpg:
      case RT_TG_Uc:
      case RT_TG_Deff:
      case RT_TG_DefLang:
      case RT_TG_DefLangFe:
      case RT_TG_FRoman:
      case RT_TG_FSwiss:
      case RT_TG_FModern:
      case RT_TG_FNil:
      case RT_TG_Fprq:
      case RT_TG_Ast:
      case RT_TG_Panose:
      case RT_TG_FAlt:
      case RT_TG_List:
      case RT_TG_ListTemplateId:
      case RT_TG_ListSimple:
      case RT_TG_ListLevel:
      case RT_TG_LevelNfc:
      case RT_TG_LevelNfcn:
      case RT_TG_LevelJc:
      case RT_TG_LevelJcn:
      case RT_TG_LevelFollow:
      case RT_TG_LevelStartAt:
      case RT_TG_LevelSpace:
      case RT_TG_LevelIndent:
      case RT_TG_LevelText:
      case RT_TG_PaperW:
      case RT_TG_PaperH:
      case RT_TG_WidowCtrl:
      case RT_TG_Ftnbj:
      case RT_TG_AendDoc:
      case RT_TG_NoxLatToYen:

      case RT_TG_expshrtn:
      case RT_TG_noultrlspc:
      case RT_TG_dntblnsbdb:
      case RT_TG_nospaceforul:
      case RT_TG_hyphcaps:
      case RT_TG_formshade:
      case RT_TG_horzdoc:
      case RT_TG_dghspace:
      case RT_TG_dgvspace:
      case RT_TG_dghorigin:
      case RT_TG_dgvorigin:
      case RT_TG_dghshow:
      case RT_TG_dgvshow:
      case RT_TG_jexpand:
      case RT_TG_viewkind:
      case RT_TG_viewscale:
      case RT_TG_pgbrdrhead:
      case RT_TG_pgbrdrfoot:
      case RT_TG_nolnhtadjtbl:
      case RT_TG_fet:
      case RT_TG_sectd:
      case RT_TG_linex:
      case RT_TG_endnhere:
      case RT_TG_sectdefaultcl:
      case RT_TG_s:
      case RT_TG_ql:
      case RT_TG_li:
      case RT_TG_ri:
      case RT_TG_widctlpar:
      case RT_TG_tqc:
      case RT_TG_tx:
      case RT_TG_tqr:
      case RT_TG_aspalpha:
      case RT_TG_aspnum:
      case RT_TG_faauto:
      case RT_TG_adjustright:
      case RT_TG_rin:
      case RT_TG_lin:
      case RT_TG_itap:
      case RT_TG_fs:
      case RT_TG_lang:
      case RT_TG_langfe:
      case RT_TG_cgrid:
      case RT_TG_landnp:
      case RT_TG_langfenp:
      case RT_TG_fldrslt:
      case RT_TG_noproof:
      case RT_TG_langnp:
      case RT_TG_cf:
      case RT_TG_qc:
      case RT_TG_keepn:
      case RT_TG_outlinelevel:
      case RT_TG_highlight:
      case RT_TG_scaps:
      case RT_TG_sect:
      case RT_TG_sbknone:
      case RT_TG_cols:
      case RT_TG_colno:
      case RT_TG_colw:
      case RT_TG_colsr:
      case RT_TG_pntext:
//    case RT_TG_pnf: // XXXX
      case RT_TG_hich:
      case RT_TG_af:
      case RT_TG_dbch:
      case RT_TG_loch:
      case RT_TG_fi:
      case RT_TG_jclisttab:
//    case RT_TG_pn: // XXXX
      case RT_TG_pnlvlbody:
      case RT_TG_ilvl:
      case RT_TG_ls:
      case RT_TG_pnrnot:
      case RT_TG_pnlcrm:
      case RT_TG_pni:
      case RT_TG_pncf:
      case RT_TG_pnstart:
      case RT_TG_pnindent:
      case RT_TG_pnsp:
      case RT_TG_pnhang:
      case RT_TG_trgaph:
      case RT_TG_trrh:
      case RT_TG_trleft:
      case RT_TG_trftsWidth:
      case RT_TG_trpaddl:
      case RT_TG_trpaddr:
      case RT_TG_trpaddfl:
      case RT_TG_trpaddfr:
      case RT_TG_clvertalt:
      case RT_TG_clbrdrt:
      case RT_TG_brdrnone:
      case RT_TG_clbrdrl:
      case RT_TG_clbrdrb:
      case RT_TG_clbrdrr:
      case RT_TG_clbrdrtb:
      case RT_TG_clftsWidth:
      case RT_TG_clwWidth:
      case RT_TG_cl:
      case RT_TG_brdrs:
      case RT_TG_brdrw:
      case RT_TG_cltxlrtb:
      case RT_TG_qr:
      case RT_TG_sl:
      case RT_TG_slmult:
      case RT_TG_qj:
      case RT_TG_ul:
      case RT_TG_ulnone:
      case RT_TG_dn:
      case RT_TG_objemb:
      case RT_TG_objw:
      case RT_TG_objh:
      case RT_TG_objclass:
      case RT_TG_objdata:
      case RT_TG_result:
      case RT_TG_picprop:
      case RT_TG_shplid:
      case RT_TG_sp:
      case RT_TG_sn:
      case RT_TG_sv:
      case RT_TG_picscalex:
      case RT_TG_picscaley:
      case RT_TG_piccropl:
      case RT_TG_piccropr:
      case RT_TG_piccropt:
      case RT_TG_piccropb:
      case RT_TG_picw:
      case RT_TG_pich:
      case RT_TG_picwgoal:
      case RT_TG_pichgoal:
      case RT_TG_pngblip:
      case RT_TG_bliptag:
      case RT_TG_blipuid:
      case RT_TG_blipupi:
      case RT_TG_wmetafile:
      case RT_TG_listtext:
      case RT_TG_u:
      case RT_TG_strike:
      case RT_TG_flddirty:
      case RT_TG_trqr:
      case RT_TG_trbrdrt:
      case RT_TG_trbrdrl:
      case RT_TG_trbrdrb:
      case RT_TG_trbrdrr:
      case RT_TG_trbrdrh:
      case RT_TG_trbrdrv:
      case RT_TG_trftsWidthB:
      case RT_TG_trwWidthB:
      case RT_TG_trftsWidthA:
      case RT_TG_trwWidthA:
      case RT_TG_nowidctlpar:
      case RT_TG_shad:
      case RT_TG_pndec:
      case RT_TG_fscript:
      case RT_TG_fdecor:
      case RT_TG_trwWidth:
      case RT_TG_pnucltr:
      case RT_TG_pntxtb:
      case RT_TG_pgwsxn:
      case RT_TG_pghsxn:
      case RT_TG_marglsxn:
      case RT_TG_margrsxn:
      case RT_TG_margtsxn:
      case RT_TG_margbsxn:
      case RT_TG_psz:
      case RT_TG_headery:
      case RT_TG_footery:
      case RT_TG_fldedit:

      case RT_TG_pnlvlcont:
      case RT_TG_pnlvlblt:

      case RT_TG_cs:

      case RT_TG_Nil:

      case RT_TG_margl:
      case RT_TG_margr:
      case RT_TG_margt:
      case RT_TG_margb:
      case RT_TG_margmirror:
      case RT_TG_dgmargins:
      case RT_TG_dgmargin:
      case RT_TG_lndscpsxn:
      case RT_TG_titlepg:
      case RT_TG_sectlinegrid:

      case RT_TG_nestcell:
      case RT_TG_nonesttables:
      case RT_TG_nesttableprops:
      case RT_TG_nestrow:

      case RT_TG_revised:         // ijungti kokia raudona spalva - naujai ivestas tekstas
      case RT_TG_revauth:
      case RT_TG_revdttm:

      case RT_TG_deftab:
      case RT_TG_hyphhotz:
      case RT_TG_hyphauto:
      case RT_TG_viewzk:
      case RT_TG_bdrrlswsix:
      case RT_TG_pgnrestart:
      case RT_TG_colsx:
      case RT_TG_expnd:
      case RT_TG_expndtw:
      case RT_TG_sb:
      case RT_TG_sa:
      case RT_TG_kerning:
      case RT_TG_splytwnine:
      case RT_TG_ftnlytwnine:
      case RT_TG_htmautsp:
      case RT_TG_useltbaln:
      case RT_TG_alntblind:
      case RT_TG_lytcalctblwd:
      case RT_TG_lyttblrtgr:
      case RT_TG_lnbrkrule:
      case RT_TG_trqc:

      case RT_TG_c:
      case RT_TG_z:

      case RT_TG_tldot:
      case RT_TG_charscalex:

      case RT_TG_brdrb:
      case RT_TG_brsp:

      case RT_TG_tdfrmtxtLeft:
      case RT_TG_tdfrmtxtRight:
      case RT_TG_tpvpara:
      case RT_TG_tphmrg:
      case RT_TG_tposy:

      case RT_TG_column:

      case RT_TG_chatn:
      case RT_TG_annotation:

         break;

// --------------------------------------------------
      case RT_TG_ColorTbl:
      case RT_TG_StyleSheet:
      case RT_TG_ListTable:
      case RT_TG_ListOverrideTable:
      case RT_TG_RevTbl:
      case RT_TG_Info:
      case RT_TG_PnsecLvl:

      case RT_TG_pntxta:

// header and footer - to some different tag
      case RT_TG_header:
      case RT_TG_footer:
      case RT_TG_footerf:

      case RT_TG_deleted:         // ijungti perbraukta fonta - ismestas tekstas

      case RT_TG_datafield:

      case RT_TG_bkmkstart:
      case RT_TG_bkmkend:

      case RT_TG_userprops:
      case RT_TG_propname:
      case RT_TG_proptype:
      case RT_TG_staticval:

      case RT_TG_pn: // XXXX

      case RT_TG_atrfstart:
      case RT_TG_atrfend:
      case RT_TG_atnid:
      case RT_TG_atnauthor:
      case RT_TG_atnref:

         retc=SkipCurrLevel();
         break;

// --------------------------------------------------
      case RT_TG_FontTbl:
         if(field_type==RT_TT_Text)
            retc=pCurrentField->SetFieldType(field_type=RT_TT_FontTable);
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
         break;

// --------------------------------------------------
      case RT_TG_Font:
      case RT_TG_pnf: // XXXX
         switch(field_type)
         {
         case RT_TT_FontDefinition:
            if((cur_font==RT_FONT_UNDEFINED) || (cur_font==0) || (cur_font==lNumVal))
               retc=pCurrentField->SetFont(cur_font=lNumVal);
            else
                retc=KpErrorProc.OutputErrorMessage(TV_E_DOUBLE_FONT_DEF, null, TRUE, __FILE__, __LINE__, 0L);
            break;

         case RT_TT_RTF_Field:
         case RT_TT_Text:
         case RT_TT_Table:
            if(lNumVal==RT_FONT_UNDEFINED)
            {
               if(strlen((const char *)lpszTextVal)==0)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
               else retc=SearchFont(&cur_font, lpszTextVal);

               if((cur_font==RT_FONT_UNDEFINED) && SUCCEEDED(retc))
               {
                  cur_font=0;
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, lpszTextVal, FALSE, __FILE__, __LINE__, 0L);
               }
            }
            else cur_font=lNumVal;

            if(SUCCEEDED(retc))
            {
               if((cur_font<0) || (cur_font>=RT_MAX_NUM_OF_FONTS))
                  retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
               else
               {
                  retc=pFonts[cur_font].IsDefined(&font_defined);
                  if(SUCCEEDED(retc)) retc=pFonts[cur_font].GetKptCodeTable(&kpt_cset);
                  if(SUCCEEDED(retc))
                  {
                     if((font_defined) && (kpt_cset>0) && (kpt_cset<KPT_Ctnum))
                        retc=pCurrentField->SetFont(cur_font);
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);
                  }
               }
            }

// return character from symbolic field
            if((field_type==RT_TT_RTF_Field) && bFieldCharPresent && SUCCEEDED(retc))
            {
               retc=CharEncode((KpChar*)puiInChar, cFieldChar);
               *pbInChFlg=TRUE;

               cFieldChar=Nul;
               bFieldCharPresent=FALSE;
            }
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
            break;
         }
         break;

// --------------------------------------------------
      case RT_TG_CharSet:
         switch(field_type)
         {
         case RT_TT_FontDefinition:
            if((cur_font<0) || (cur_font>=RT_MAX_NUM_OF_FONTS))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);
            else
            {
               retc=pFonts[cur_font].SetRtfCodeTable(lNumVal);
               if(SUCCEEDED(retc)) retc=pFonts[cur_font].SetDefined(TRUE);
            }
            break;

         default:
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
            break;
         }
         break;

// --------------------------------------------------
      case RT_TG_b:
         retc=pCurrentField->SetBold(lNumVal!=0);
         break;

      case RT_TG_i:
         retc=pCurrentField->SetIt(lNumVal!=0);
         break;

      case RT_TG_sub:
         retc=pCurrentField->SetSub(lNumVal!=0 /* True */);
         break;

      case RT_TG_super:
         retc=pCurrentField->SetSuper(lNumVal!=0 /* True */);
         break;

// --------------------------------------------------
      case RT_TG_v:               // ijungti hidden fonta
//       retc=SkipCurrLevel();
         retc=pCurrentField->SetHidden(lNumVal!=0);
         break;

// --------------------------------------------------
      case RT_TG_xe:               // ijungti nuorodos pozymi
//       retc=SkipCurrLevel();
//       *puiInChar=XC_Reference;
//       *pbInChFlg=TRUE;
         retc=pCurrentField->SetXref(True);
//       if(SUCCEEDED(retc)) retc=pCurrentField->SetRTFieldType(RT_TT_RTF_HypField);
         break;

// --------------------------------------------------
      case RT_TG_SpecChr:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            retc=CharEncode((KpChar*)puiInChar, (const unsigned char)lNumVal);
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_NBSP:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_NBSP;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_endash:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_EnDash;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_emdash:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_EmDash;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_tab:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_Spc;
//          *puiInChar=C_Ht;
            *pbInChFlg=TRUE;
         }
         break;

// --------------------------------------------------
      case RT_TG_pard:
         retc=pCurrentField->SetFieldType(field_type=RT_TT_Text);
//       if(SUCCEEDED(retc)) retc=pCurrentField->SetTablePars(0, 0);
//       if(SUCCEEDED(retc)) retc=pCurrentField->SetFont(cur_font=0 /* RT_FONT_UNDEFINED */);
         if(SUCCEEDED(retc)) retc=pCurrentField->SetBold(False);
         if(SUCCEEDED(retc)) retc=pCurrentField->SetIt(False);
         break;

      case RT_TG_plain:
         retc=pCurrentField->SetFieldType(field_type=RT_TT_Text);
//       if(SUCCEEDED(retc)) retc=pCurrentField->SetTablePars(0, 0);
         break;

// --------------------------------------------------
      case RT_TG_page:
         retc=SkipSpcEol();
         *puiInChar=RC_PageBreak; // C_Ff
         *pbInChFlg=TRUE;
         break;

// --------------------------------------------------
      case RT_TG_Par:
         retc=SkipSpcEol();
         *puiInChar=RC_NewPar; // C_Lf
         *pbInChFlg=TRUE;
         break;

      case RT_TG_line:
         retc=SkipSpcEol();
         if((field_type!=RT_TT_RTF_Field) && SUCCEEDED(retc)) // XXXX
         {
            *puiInChar=RC_LineBreak; // C_break // C_Cr
            *pbInChFlg=TRUE;
         }
         break;

// --------------------------------------------------
      case RT_TG_trowd:
//         retc=pCurrentField->SetFieldType(field_type=RT_TT_Table);
           if(SUCCEEDED(retc)) retc=pCurrentField->SetTablePars(0, 0);
           if(SUCCEEDED(retc)) retc=SkipSpcEol();
//         *puiInChar=RC_TblDelim; // C_Ff // !!! ne - cia eilutes pradzia
//         *pbInChFlg=TRUE;
         break;

      case RT_TG_cellx:
//       if(field_type!=RT_TT_Table)
//          retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
//       else
         {
            retc=pCurrentField->GetTablePars(&tb_wdt, &col_num);
            if(SUCCEEDED(retc)) retc=pCurrentField->SetTablePars(tb_wdt+lNumVal, col_num+1);
         }
         break;

      case RT_TG_intbl:
         retc=pCurrentField->SetFieldType(field_type=RT_TT_Table);
         break;

      case RT_TG_Cell:
         if(field_type!=RT_TT_Table)
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
         else
         {
            retc=SkipSpcEol();
            *puiInChar=RC_CellDelim; // C_Ht
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_Row:
         if(field_type!=RT_TT_Table)
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
         else
         {
            retc=SkipSpcEol();
            *puiInChar=RC_RowDelim; // C_Vt
            *pbInChFlg=TRUE;
         }
         break;

// --------------------------------------------------
      case RT_TG_fldinst:
         if(SUCCEEDED(retc)) retc=pCurrentField->SetRTFieldType(RT_TT_RTF_FieldUnknown);
         break;

      case RT_TG_Field:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || (field_type==RT_TT_RTF_Field))
         {
            retc=pCurrentField->SetFieldType(field_type=RT_TT_RTF_Field);
//          if(SUCCEEDED(retc)) retc=pCurrentField->SetRTFieldType(RT_TT_RTF_FieldUnknown);
         }
         else
            retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_UNEXPECTED, null, TRUE, __FILE__, __LINE__, 0L);
         break;

      case RT_TG_LQuote:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_Rapost;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_RQuote:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_LAapost;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_LDblQuote:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_Rquote;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_RDblQuote:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_LAquote;
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_Caps:
         retc=pCurrentField->SetCaps(VT_ToUpper);
         break;

      case RT_TG_left_curly:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_Lcurl; // '{';
            *pbInChFlg=TRUE;
         }
         break;

      case RT_TG_right_curly:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_Rcurl; // '}';
            *pbInChFlg=TRUE;
         }
         break;


      case RT_TG_opt_hyph:
         if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
         {
            *puiInChar=C_hyph;
            *pbInChFlg=TRUE;
         }
         break;


      case RT_TG_object:
         retc=SkipCurrLevel();
         if(SUCCEEDED(retc))
//          if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
            {
               *puiInChar=(KpChar)XC_Equiation;
               *pbInChFlg=TRUE;
            }
         break;

      case RT_TG_pict:
         retc=SkipCurrLevel();
         if(m_bShowPict && SUCCEEDED(retc))
//          if((field_type==RT_TT_Text) || (field_type==RT_TT_Table) || ((field_type==RT_TT_RTF_Field) && (rtf_field_type==RT_TT_RTF_HypField)))
            {
               *puiInChar=(KpChar)XC_Img;
               *pbInChFlg=TRUE;
            }
         m_bShowPict=True;
         break;

      case RT_TG_shppict:
         m_bShowPict=True;
         break;

      case RT_TG_nonshppict:
         m_bShowPict=False;
         break;

// unknown tags
      case RT_TG_xxx:
      default:
         retc=KpErrorProc.OutputErrorMessage(TV_E_UNKN_TAG, lpszKeywrd, FALSE, __FILE__, __LINE__, 0L); // !!!!
         break;

      } // switch(idx)
   }

   if(SUCCEEDED(retc))
   {
      *piFieldType=field_type;
      *piCurFont=cur_font;
   }

return(retc);
}


// ================================================== public methods of TvRtfI
// --------------------------------------------------
TvRtfI::TvRtfI(const unsigned char *lpszInfname)
{
HRESULT retc = S_OK;

   ucUnGetBuf=Nul;
   bUnGetPresent=FALSE;

   iUnGetProcCnt=0;

   cFieldChar=Nul;
   bFieldCharPresent=FALSE;

   m_bShowPict=True;

   iNumOfFonts=0;
   KP_NEWA(pFonts, RT_FontDescriptor_tag, RT_MAX_NUM_OF_FONTS);
   if(SUCCEEDED(m_lhOpenResult)) iNumOfFonts=RT_MAX_NUM_OF_FONTS;

   KP_NEW(lpfRtfFile, TvXml8File(lpszInfname, (const unsigned char *)"r", XL_FT_DataFile, False));
}


// --------------------------------------------------
TvRtfI::~TvRtfI()
{
HRESULT retc0=S_OK;

   if(lpfRtfFile!=NULL)
   {
      retc0=lpfRtfFile->CloseFile(False);
      KP_DELETE(lpfRtfFile);
   }
   lpfRtfFile=NULL;

   KP_DELETE(pFonts);
}


// --------------------------------------------------
HRESULT TvRtfI::SetTablePars(long lTableWidth, int iNumOfCols)
{
HRESULT retc=S_OK;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->SetTablePars(lTableWidth, iNumOfCols);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::GetTablePars(long *plTableWidth, int *piNumOfCols)
{
HRESULT retc=S_OK;

   if(pCurrentField==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
      retc=pCurrentField->GetTablePars(plTableWidth, piNumOfCols);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::GetChar(unsigned char *pcInch, bool bCheckFeof)
{
HRESULT retc=S_OK;
KpChar in_ch;

   *pcInch=C_Nul;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(bUnGetPresent)
      {
         *pcInch=ucUnGetBuf;
         bUnGetPresent=FALSE;
         ucUnGetBuf=Nul;
      }
      else
      {
         retc=lpfRtfFile->GetChar(&in_ch);
         if((retc==KP_E_EOF) && bCheckFeof)
            retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, 0L);
         if((in_ch>=KPT_Ctbsiz) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) *pcInch=(unsigned char)in_ch;
      }
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::UnGetChar(unsigned char cChar)
{
HRESULT retc=S_OK;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if(bUnGetPresent)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      bUnGetPresent=TRUE;
      ucUnGetBuf=cChar;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::GetCharProc(KpChar *puiInch, bool bCheckFeof)
{
HRESULT retc=S_OK;
bool char_ready=FALSE;
unsigned char ch2;
bool ctrl_char;
unsigned char cc;
unsigned char keywrd[TV_TAG_LEN+1];
unsigned char textval[TV_TAG_LEN+1];
long ll;
bool eof_fl=FALSE;
RT_FieldTypes field_type;
RT_RTF_FieldTypes rtf_field_type;
RT_FieldTypes prev_field_type;
RT_RTF_FieldTypes prev_rtf_field_type;
int cur_font;
bool end_of_font_name=FALSE;
CapsIndicators caps_ind;
int rtf_tbl;
int rtf_tbl_new;
unsigned char *font_name_ptr;
int idx;

   *puiInch=C_Nul;

   if((pCurrentField==NULL) || (pFonts==NULL))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetFont(&cur_font);

   if(SUCCEEDED(retc))
   {
      if(iUnGetProcCnt>0) *puiInch=iaUnGetProcBuf[--iUnGetProcCnt];
      else
      {
         do
         {
            retc=GetChar(&ch2, FALSE);
            if(retc==KP_E_EOF)
            {
               retc=S_OK;
               eof_fl=TRUE;
            }

// ctrl. char.?
            ctrl_char=FALSE;
            if(!eof_fl && SUCCEEDED(retc))
               ctrl_char=(TvStrChr(lpszRtfCtrlChars, (KpChar)ch2)!=NULL);

            if(!ctrl_char && (field_type==RT_TT_RTF_Field) && (rtf_field_type!=RT_TT_RTF_HypField) && !eof_fl && SUCCEEDED(retc))
            {
               if(TvStrChr(lpszSpcEol, (KpChar)ch2)==NULL)
               {
                  ctrl_char=TRUE;
                  retc=UnGetChar(ch2);
               }
            }

// ctrl. char.
            if(ctrl_char && !eof_fl && SUCCEEDED(retc))
            {
               switch(ch2)
               {
// start of keyword '\\'
               case RC_KeywordStart:
                  retc=GetWord(keywrd, &ll, textval, &cc, lpszRtfCtrlsSpacesAndDelims);
                  if(cc==Nul) eof_fl=TRUE;

// if(SUCCEEDED(retc))
// if(strcmp(keywrd, "f")==0)
// if(ll==15)
// ll=15;

// if(SUCCEEDED(retc))
// if(strcmp(keywrd, "margl")==0)
// ll=ll;

                  if(SUCCEEDED(retc))
                  {
                     retc=ProcessKeyword(puiInch, &char_ready, &field_type, &cur_font,
                                          keywrd, ll, textval);
                     if(retc==KP_E_KWD_NOT_FOUND)
                     {
                        retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, keywrd, False, __FILE__, __LINE__, 0L);
                        *puiInch=C_Nul;
                        char_ready=False;
                     }
//                   if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
                     if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);
                  }
                  break;

// opening parenthese '{'
               case RT_FieldStart:
                  retc=PushField(&field_type, &cur_font);
                  break;

// closing parenthese '}'
               case RT_FieldEnd:
//                if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
//                if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);
                  prev_field_type=field_type;
                  prev_rtf_field_type=rtf_field_type;

                  end_of_font_name=FALSE;
                  retc=PopField(&field_type, &cur_font);

                  if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
                  if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);

                  if((prev_field_type==RT_TT_RTF_Field) &&
                     (prev_rtf_field_type==RT_TT_RTF_HypField) && (rtf_field_type!=RT_TT_RTF_HypField) &&
                     SUCCEEDED(retc))
                  {
                     if((field_type!=RT_TT_RTF_Field) && SUCCEEDED(retc))
                     {
                        *puiInch=(KpChar)XC_Reference_e;
                        retc=SetXref(False);
                        char_ready=True;
                     }
                  }
                  break;

// keywords inside of RTF /field's begin with space
               default:
                  retc=GetWord(keywrd, &ll, textval, &cc, lpszRtfCtrlsSpacesAndDelims);
                  if(cc==Nul) eof_fl=TRUE;

                  if(SUCCEEDED(retc))
                  {
                     retc=GetKwrdIndex(&idx, keywrd, (const unsigned char **)lpszaRtfFieldTypesTags, -1, True, True);
                     if(retc==KP_E_KWD_NOT_FOUND)
                     {
                        idx=RT_TT_RTF_FieldUnknown;
                        retc=S_OK;
                     }
                  }

                  if(SUCCEEDED(retc)) retc=SetRTFieldType(rtf_field_type=(RT_RTF_FieldTypes)idx);

                  if(SUCCEEDED(retc)) switch(idx)
                  {
                  case RT_TT_RTF_SymField:
                     if(bFieldCharPresent)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                     if(SUCCEEDED(retc))
                        if((ll<0) || (ll>=KPT_Ctbsiz))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, TRUE, __FILE__, __LINE__, 0L);
                     if(SUCCEEDED(retc))
                     {
                        cFieldChar=(unsigned char)ll;
                        bFieldCharPresent=TRUE;
                     }
                     break;

                  case RT_TT_RTF_HypField:
                     strcpy(m_lpszTextVal, textval);
                     *puiInch=(KpChar)XC_Reference;
                     retc=SetXref(True);
                     char_ready=True;
                     break;

                  default:
                     break;
                  }

                  break;
               } // switch(ch2)
            }

// spaces
            if(!ctrl_char && !char_ready && !eof_fl && SUCCEEDED(retc))
            {
               switch(ch2)
               {
                  case RC_CellDelim: // C_Ht
                  case RC_RowDelim:  // C_Vt
                  case RC_TblDelim:  // C_Ff
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, FALSE, __FILE__, __LINE__, 0L);
                     ch2=Spc;
                     break;
               }

               if(TvStrChr(lpszSpaces, (KpChar)ch2)!=NULL)
               {
//                retc=SkipSpcEol();
                  ch2=Spc;
               }
            }

            if(!ctrl_char && !char_ready && !eof_fl && SUCCEEDED(retc))
            {

// eol's - must be simply skipped, not changed to spaces
               if(TvStrChr(lpszEols, (KpChar)ch2)!=NULL)
                  retc=SkipEols();
               else
// ordinary char.
               {
                  switch(field_type)
                  {
                  case RT_TT_Text:
                  case RT_TT_Table:
                     retc=CharEncode((KpChar*)puiInch, ch2);
                     char_ready=TRUE;
                     break;

                  case RT_TT_RTF_Field:
                     if(rtf_field_type==RT_TT_RTF_HypField)
                     {
                        retc=CharEncode((KpChar*)puiInch, ch2);
                        char_ready=TRUE;
                     }
                     break;

                  case RT_TT_FontDefinition:
                     if((cur_font<0) || (cur_font>=RT_MAX_NUM_OF_FONTS))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, TRUE, __FILE__, __LINE__, 0L);
                     else
                     {
                        if(ch2==';')
                        {
                           end_of_font_name=TRUE;

                           rtf_tbl_new=0;
                           retc=pFonts[cur_font].GetRtfCodeTable(&rtf_tbl);
                           if(SUCCEEDED(retc))
                              retc=pFonts[cur_font].GetFontName(&font_name_ptr);
                           if(SUCCEEDED(retc))
                           {
                              if(strstr(font_name_ptr, "Arial BlackLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "BookmanLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "BrushScriptLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "CourierLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "ErasLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "Garamond_LT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "HelveticaLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "MonospaceLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "OptimaLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "SchoolbookLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "TimesLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "VakarinisLT")==font_name_ptr) rtf_tbl_new=186;
                              else if(strstr(font_name_ptr, "VogueLT")==font_name_ptr) rtf_tbl_new=186;

                              if(strstr(font_name_ptr, "Wingdings")!=null) rtf_tbl_new=251;
                              if(strstr(font_name_ptr, "Symbol")!=null) rtf_tbl_new=252;
                              if(strstr(font_name_ptr, "MTMI")!=null) rtf_tbl_new=252;

                              if(strstr(font_name_ptr, " CE")!=null) rtf_tbl_new=238;
                              if(strstr(font_name_ptr, " Cyr")!=null) rtf_tbl_new=204;
                              if(strstr(font_name_ptr, " Greek")!=null) rtf_tbl_new=161;
                              if(strstr(font_name_ptr, " Tur")!=null) rtf_tbl_new=162;

                              if(strcmp(font_name_ptr, "TimesLT Accented")==0) rtf_tbl_new=254;

                              if(
                                 (rtf_tbl!=0) && (rtf_tbl_new!=0) && (rtf_tbl!=rtf_tbl_new) &&
                                 (
                                    (rtf_tbl!=2) ||
                                    (
                                       (rtf_tbl_new!=186) && (rtf_tbl_new!=251) && (rtf_tbl_new!=252)
                                    )
                                 )
                                )
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                           }
                           if((rtf_tbl_new!=0) && SUCCEEDED(retc))
                              retc=pFonts[cur_font].SetRtfCodeTable(rtf_tbl_new);
                        }
                        if(!end_of_font_name)
                           retc=pFonts[cur_font].PutCharToName(ch2);
                     }
                     break;
                  }
               }
            }

         } while(!char_ready && !eof_fl && SUCCEEDED(retc) && !eof_fl);

      } // else if(bUnGetProcPresent)
   }

// caps processing
   if(char_ready && SUCCEEDED(retc))
   {
      retc=pCurrentField->GetCaps(&caps_ind);
      if(SUCCEEDED(retc))
      {
         switch(caps_ind)
         {
         case VT_ToUpper: *puiInch=TvKpToUpper((KpChar) *puiInch); break;
         case VT_ToLower: *puiInch=TvKpToLower((KpChar) *puiInch); break;
         }
      }
   }

   if(eof_fl && SUCCEEDED(retc))
   {
      if(!bCheckFeof) retc=KP_E_EOF;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_EOF, null, TRUE, __FILE__, __LINE__, 0L);
   }


return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::UnGetCharProc(KpChar iChar)
{
HRESULT retc=S_OK;

   if(lpfRtfFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(iUnGetProcCnt>=RT_UNGET_BUF_SIZ)
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_UNGET, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      iaUnGetProcBuf[iUnGetProcCnt]=iChar;
      iUnGetProcCnt++;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::GetCharProcSkipSpc(KpChar *puiInch)
{
HRESULT retc=S_OK;
KpChar ch2;
bool xr_fl;
bool prev_xr_fl;
bool hid_fl;
bool prev_hid_fl;

   *puiInch=C_Nul;

   if(SUCCEEDED(retc)) retc=pCurrentField->GetXref(&prev_xr_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetHidden(&prev_hid_fl);
   if(SUCCEEDED(retc)) retc=GetCharProc(&ch2, FALSE);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetXref(&xr_fl);
   if(SUCCEEDED(retc)) retc=pCurrentField->GetHidden(&hid_fl);

// spaces, eol's
   if((TvStrChr(lpszRtfProcSpcs, ch2)!=NULL) && ((!prev_xr_fl) || xr_fl) && ((!prev_hid_fl) || hid_fl) && SUCCEEDED(retc))
      retc=SkipSpacesProc();

// ordinary char.
   if(SUCCEEDED(retc)) *puiInch=ch2;

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::SkipToChar(unsigned char *pcDelimCh, const unsigned char *lpszDelim)
{
HRESULT retc=S_OK;
unsigned char ch1;
bool reached=FALSE;
bool eof_fl=FALSE;

   *pcDelimCh=Nul;

   do
   {
      retc=GetChar(&ch1, FALSE);
      if(SUCCEEDED(retc))
      {
         reached=(TvStrChr(lpszDelim, (KpChar)ch1)!=NULL);
         if(reached)
         {
            *pcDelimCh=ch1;
            retc=UnGetChar(ch1);
         }
      }
      else
      {
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }
      }
   } while((!reached) && SUCCEEDED(retc) && (!eof_fl));

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::SkipSpaces(void)
{
return(SkipChars(lpszSpaces));
}


// --------------------------------------------------
HRESULT TvRtfI::SkipSpcEol(void)
{
return(SkipChars(lpszSpcEol));
}


// --------------------------------------------------
HRESULT TvRtfI::SkipEols(void)
{
return(SkipChars(lpszEols));
}


// --------------------------------------------------
HRESULT TvRtfI::SkipSpacesProc(void)
{
return(SkipCharsProc((const unsigned char *)lpszRtfProcSpcs/*" "*/));
                           // not lpszSpaces (== " \t") - '\t' - cell delimiter
}


// --------------------------------------------------
HRESULT TvRtfI::SkipSpcEolProc(void)
{
return(SkipCharsProc((const unsigned char *)lpszRtfProcSpcEol/*" \r\n"*/));
                           // not lpszSpcEol (== " \t\r\n\f") - '\t' - cell delimiter
}


// --------------------------------------------------
HRESULT TvRtfI::GetWord
(
unsigned char *lpszKeywrd,
long *plNumVal,
unsigned char *lpszTextVal,
unsigned char *pcDelimCh,
const unsigned char *lpszDelim
)
{
HRESULT retc=S_OK;
unsigned char ch1;
bool reached=FALSE;
bool sng_chr=FALSE; // single char keyword
bool eof_fl=FALSE;
int keyidx=0;
int numidx=0;
bool numfl=FALSE;
unsigned char numbuf[TV_TAG_LEN+1];
int hexidx=0;
bool hexfl=FALSE;
int textidx=0;
bool textfl=FALSE;
unsigned char hexbuf[TV_TAG_LEN+1];
RT_FieldTypes field_type;
RT_RTF_FieldTypes rtf_field_type;
bool first_fl;

   *pcDelimCh=Nul;
   *plNumVal=RT_NO_VALUE;

   first_fl=True;

   do
   {
      retc=GetChar(&ch1, FALSE);

      if(first_fl && SUCCEEDED(retc))
      {
         if(ch1==C_Lf) retc=GetChar(&ch1, FALSE);
         first_fl=True;
      }

if((keyidx==0) && (ch1=='{'))
keyidx=0; // !!!

      if(SUCCEEDED(retc))
      {

// test word end
         if(textfl && (ch1=='\"') && !reached && SUCCEEDED(retc))
            reached=TRUE;

         if(!reached && SUCCEEDED(retc))
         {
            reached=((TvStrChr(lpszDelim, (KpChar)ch1)!=NULL) && (!textfl));
            if((ch1=='-') && (keyidx==0)) sng_chr=TRUE;
            if(reached && (keyidx==0) && (ch1!=RC_KeywordStart /* '\\' */))
            {
               reached=FALSE;
               sng_chr=TRUE;
            }
         }

// input text value
         if(textfl && !reached && SUCCEEDED(retc))
         {
            if(textidx >= TV_TAG_LEN-1)
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
            else lpszTextVal[textidx++]=ch1;
         }

// input tail hex number
         if(hexfl && !reached && SUCCEEDED(retc))
         {
            if(hexidx<2) hexbuf[hexidx++]=ch1;
            if(hexidx >= 2) reached=TRUE;
         }

// delimiter
         if(reached && SUCCEEDED(retc))
         {

// skip delimition space and '\"' at the end of text parameters
            if((TvStrChr(lpszSpcEol, (KpChar)ch1)==NULL) && !hexfl && !textfl && !sng_chr)
               retc=UnGetChar(ch1);

// switch to entering of numeric/text values in symbolic field
            if(SUCCEEDED(retc)) retc=pCurrentField->GetFieldType(&field_type);
            if(SUCCEEDED(retc)) retc=pCurrentField->GetRTFieldType(&rtf_field_type);
            if(SUCCEEDED(retc))
            {
               if((field_type==RT_TT_RTF_Field) && (rtf_field_type!=RT_TT_RTF_HypField))
               {
// numeric value follows in next word after space/eol
                  retc=SkipSpcEol();
                  if(SUCCEEDED(retc)) retc=GetChar(&ch1, FALSE);

                  if(SUCCEEDED(retc))
                  {
                     if(isdigit(ch1) || (ch1=='-'))
                     {
                        if(numidx==0) reached=FALSE;   // continue to enter numeric value
                        else
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                                                       // duplicated numeric values
                     }
                     else
                     {
                        if(ch1=='\"')
                        {
                           if(textfl==FALSE)
                           {
                              reached=FALSE;
                              textfl=TRUE;
                           }
                           else
                              retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                                                      // duplicated text values
                        }
                        else
                        {
                           retc=UnGetChar(ch1);         // no more numeric/text values
                           *pcDelimCh=ch1;
                        }
                     } // else if(isdigit(ch1))

                  } // if(SUCCEEDED(retc))
               }
               else *pcDelimCh=ch1; // if(field_type==RT_TT_RTF_Field)

            } // if(SUCCEEDED(retc))

         } // if(reached && SUCCEEDED(retc))

// input tail decimal digits
         if(!reached && !hexfl && !textfl && SUCCEEDED(retc))
         {
            if((!numfl) && (ch1=='-') && (keyidx>0)) numfl=TRUE;
            if(isdigit(ch1)) numfl=TRUE;
            if(numfl)
            {
               if(numidx >= TV_TAG_LEN-1)
                  retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, False, __FILE__, __LINE__, 0L);
               else numbuf[numidx++]=ch1;
            }
         }

// input key text
         if(!reached && !hexfl && !numfl && !textfl && SUCCEEDED(retc))
         {
            if(keyidx >= TV_TAG_LEN-1)
               retc=KpErrorProc.OutputErrorMessage(TV_E_TAG_OVERFL, null, TRUE, __FILE__, __LINE__, 0L);
            else lpszKeywrd[keyidx++]=ch1;

            if(sng_chr)
            {
               reached=TRUE;
               *pcDelimCh=ch1;
            }
         }

// test whether hex number reached
         if(!reached && !hexfl && !numfl && !textfl && SUCCEEDED(retc))
            hexfl=(TvStrChr(plpszaRtfTagTable[RT_TG_SpecChr], (KpChar)ch1)!=NULL);

// test whether C_NBSP character is reached
         if(!reached && !hexfl && !numfl && !textfl && SUCCEEDED(retc))
         {
            reached=(TvStrChr(plpszaRtfTagTable[RT_TG_NBSP], (KpChar)ch1)!=NULL);
            if(reached)
            {
               retc=GetChar(&ch1, FALSE);
               if(SUCCEEDED(retc))
               {
                  retc=UnGetChar(ch1);
                  *pcDelimCh=ch1;
               }
               else if(retc==KP_E_EOF)
               {
                  retc=S_OK;
                  eof_fl=TRUE;
               }
            }
         }
      }
      else
      {
         if(retc==KP_E_EOF)
         {
            retc=S_OK;
            eof_fl=TRUE;
         }

      } // else if(SUCCEEDED(retc))

   } while(!reached && !eof_fl && SUCCEEDED(retc));

   *plNumVal=RT_NO_VALUE;      // no value

   if(hexidx>0)
   {
      hexbuf[hexidx]=0;
      sscanf((const char *)hexbuf, "%lx", plNumVal);
   }

   if(numidx>0)
   {
      numbuf[numidx]=0;
      sscanf((const char *)numbuf, "%ld", plNumVal);
   }

   lpszTextVal[textidx]=Nul;

   lpszKeywrd[keyidx]=Nul;

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::SkipCurrLevel(void)
{
HRESULT retc=S_OK;
unsigned char ch1;
int level=0;

   do
   {
      retc=GetChar(&ch1, TRUE);
      if(SUCCEEDED(retc))
      {
         if(ch1==RT_FieldStart) level++;
         if(ch1==RT_FieldEnd) level--;
      }
   } while((level>=0) && SUCCEEDED(retc));

   if(SUCCEEDED(retc)) UnGetChar(ch1);

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::SearchFont(int *piFontNumber, const unsigned char *lpszFontName)
{
HRESULT retc=S_OK;
int ii;
unsigned char *fnam;

   if(pFonts==NULL)
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, TRUE, __FILE__, __LINE__, 0L);

   if(strlen((const char *)lpszFontName)==0)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      for(ii=0; (ii<RT_MAX_NUM_OF_FONTS) && SUCCEEDED(retc); ii++)
      {
         retc=pFonts[ii].GetFontName(&fnam);
         if(SUCCEEDED(retc))
            if(strcmp((const char *)lpszFontName, (const char *)fnam)==0)
               break;
      }
   }

   if(SUCCEEDED(retc))
   {
      if(ii<RT_MAX_NUM_OF_FONTS) *piFontNumber=ii;
      else ii=RT_FONT_UNDEFINED;
   }

return(retc);
}


// --------------------------------------------------
HRESULT TvRtfI::GetWordProc(KpChar *piazWordBuf, int iBufSize)
{
HRESULT retc=S_OK;
KpChar in_ch;
bool eol_fl=False;
KpChar *pntd;

   if((piazWordBuf==NULL) || iBufSize<1)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   eol_fl=False;

   if(SUCCEEDED(retc))
   {
      do
      {
         retc=GetCharProc(&in_ch, False);
         if(SUCCEEDED(retc))
            if(TvStrChr(lpszEols, in_ch)!=NULL) eol_fl=True;

      } while((TvStrChr(lpszSpcEol, in_ch)!=NULL) && SUCCEEDED(retc));
   }

   if(SUCCEEDED(retc))
   {
      if(eol_fl)
      {
         retc=UnGetCharProc(in_ch);
         *piazWordBuf=C_Nul;
      }
      else
      {
         pntd=piazWordBuf;
         do
         {
            if((pntd-piazWordBuf)>=iBufSize)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               *(pntd++)=in_ch;
               retc=GetCharProc(&in_ch, False);
            }

         } while((TvStrChr(lpszSpcEol, in_ch)==NULL) && SUCCEEDED(retc));

         *pntd=C_Nul;

         if(SUCCEEDED(retc)) retc=UnGetCharProc(in_ch);
      }
   }

return(retc);
}

