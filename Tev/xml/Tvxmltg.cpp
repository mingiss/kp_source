// ==================================================
// tvxmltg.cpp
// SGM dictionary file tags
// main tvxml format


// ================================================== definitions
#include "envir.h"

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
#include "kpstdio.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kperr.h"
#include "tvmain.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"


//--------------------------------
// apibrezti lokaliai xxxTG.cpp faile
// const unsigned char **pplpszaMsgTags = plpszaSgmDictTags/*plpszaXmlttDictTagsFull*/;

// --------------------------------------------------
const unsigned char *plpszaSgmDictTags[XC_TG_NumOfDictTagsArr68+1] = // Dictionary XML tag names (native)
{
  (unsigned char *)"<di>\n\n",
                // "<di name=\"%s\">\n\n",
                                                // XC_Dict
  (unsigned char *)"</di>\n",                   // XC_Dict_e,

  (unsigned char *)"<ue>\n",                    // XC_NrtEntry,
  (unsigned char *)"</ue>\n\n",                 // XC_NrtEntry_e,
  (unsigned char *)"<se>\n",                    // XC_StEntry,
//                 "<se id=\"%ld\">"
  (unsigned char *)"</se>\n\n",                 // XC_StEntry_e,

  (unsigned char *)"<hw>",                      // XC_HeadWord,
  (unsigned char *)"</hw>",                     // XC_HeadWord_e,   space after not allowed - may be followed by XC_Hom
  (unsigned char *)"<la>",                      // XC_Label,
  (unsigned char *)"</la>",                     // XC_Label_e,      space after not allowed - may be inside of parentheses
  (unsigned char *)"<tw>",                      // XC_TrWord,
  (unsigned char *)"</tw>",                     // XC_TrWord_e,     space after not allowed - may be inside of parentheses
  (unsigned char *)"<un>",                      // XC_UsNoteDst,
  (unsigned char *)"</un>",                     // XC_UsNoteDst_e,
  (unsigned char *)"<xr>",                      // XC_Reference,
//                 "<xr href=\"%s#%ld\">" // TV_XM_HrefDelim // TV_HTM_HrefDelim
  (unsigned char *)"</xr>",                     // XC_Reference_e,  space after not allowed - may be in free text
  (unsigned char *)"<st>",                      // XC_StEntryText,
  (unsigned char *)"</st>",                     // XC_StEntryText_e,

  (unsigned char *)"<p>",                       // XC_Paragraph,
  (unsigned char *)"</p>\n",                    // XC_Paragraph_e,  space after not allowed - may be in free text // tai kad nëra prasmës - po paragrafo vis tiek eilutë lûþta

  (unsigned char *)"",                          // XC_Version,
  (unsigned char *)"",                          // XC_Version_e,

  (unsigned char *)"",                          // XC_DocType,
  (unsigned char *)"",                          // XC_DocType_e,

  (unsigned char *)"<v>",                       // XC_Variant,
  (unsigned char *)"</v>",                      // XC_Variant_e,   space after not allowed - may be in parentheses

  (unsigned char *)"<ps>",                      // XC_PartOfSpeechSrc,
  (unsigned char *)"</ps>",                     // XC_PartOfSpeechSrc_e,

  (unsigned char *)"", // "<hg>\n",             // XC_HeadWordGroup,
  (unsigned char *)"", // "</hg>\n",            // XC_HeadWordGroup_e,
  (unsigned char *)"<tg>",                      // XC_TranslGroup,
  (unsigned char *)"</tg>\n",                   // XC_TranslGroup_e,

  (unsigned char *)"<f>",                       // XC_FormDst,
  (unsigned char *)"</f>",                      // XC_FormDst_e,  space after not allowed - may be in parentheses
  (unsigned char *)"<fs>",                      // XC_FormSrc,
  (unsigned char *)"</fs>",                     // XC_FormSrc_e,  space after not allowed - may be in parentheses

  (unsigned char *)"<ic>",                      // XC_ExplSrc,
  (unsigned char *)"</ic>",                     // XC_ExplSrc_e,  space after not allowed - may be in free text

  (unsigned char *)"<le>",                      // XC_Example,
  (unsigned char *)"</le>",                     // XC_Example_e,  space after not allowed - may be in parentheses
  (unsigned char *)"<eg>",                      // XC_ExampleGroup,
  (unsigned char *)"</eg>\n",                   // XC_ExampleGroup_e,

  (unsigned char *)"<pt>",                      // XC_Parenth,
  (unsigned char *)"</pt>",                     // XC_Parenth_e,  space after not allowed - may be in free text

  (unsigned char *)"<li>",                      // XC_Idiom,
  (unsigned char *)"</li>",                     // XC_Idiom_e,

  (unsigned char *)"<id>",                      // XC_IdiomGroup,
  (unsigned char *)"</id>\n",                   // XC_IdiomGroup_e,

  (unsigned char *)"<s1>",                      // XC_CtgGroup,
//                 "<s1 num=\"%s\">"
  (unsigned char *)"</s1>\n",                   // XC_CtgGroup_e,

  (unsigned char *)"<base>",                    // XC_Base,
  (unsigned char *)"</base> ",                  // XC_Base_e,
  (unsigned char *)"<cg>",                      // XC_CompoundGroup,
  (unsigned char *)"</cg>\n",                   // XC_CompoundGroup_e,
  (unsigned char *)"<lc>",                      // XC_CompoundWord,
  (unsigned char *)"</lc> ",                    // XC_CompoundWord_e,

  (unsigned char *)"<s2>",                      // XC_MngGroup,
//                 "<s2 num=\"%ld\">"
  (unsigned char *)"</s2>\n",                   // XC_MngGroup_e,

  (unsigned char *)"<ast/>",                    // XC_Asterix,
  (unsigned char *)"",                          // XC_Asterix_e,  space after not allowed - may be in free text

  (unsigned char *)"<sp>",                      // XC_CtrlSrc,
  (unsigned char *)"</sp>",                     // XC_CtrlSrc_e,

  (unsigned char *)"<pr>",                      // XC_PrGroup,
  (unsigned char *)"</pr>",                     // XC_PrGroup_e,  space after not allowed - may be inside of parentheses
  (unsigned char *)"<ph>",                      // XC_Pron,
  (unsigned char *)"</ph>",                     // XC_Pron_e,

  (unsigned char *)"<ct>",                      // XC_Abbr,
  (unsigned char *)"</ct>",                     // XC_Abbr_e,  space after not allowed - may be in free text

  (unsigned char *)"<hm>",                      // XC_Hom,
  (unsigned char *)"</hm>",                     // XC_Hom_e,  space after not allowed - may be in free text

  (unsigned char *)"<co>",                      // XC_ContextSrc,
  (unsigned char *)"</co>",                     // XC_ContextSrc_e,

  (unsigned char *)"<pp>",                      // XC_CtrlGroup,
  (unsigned char *)"</pp>",                     // XC_CtrlGroup_e,  space after not allowed - may be in free text

  (unsigned char *)"<gr>",                      // XC_PartOfSpeechDst,
  (unsigned char *)"</gr>",                     // XC_PartOfSpeechDst_e,

  (unsigned char *)"<fg>",                      // XC_FormGroupSrc,
  (unsigned char *)"</fg>",                     // XC_FormGroupSrc_e,  space after not allowed - may be in parentheses

  (unsigned char *)"",                          // XC_StyleSheet,
  (unsigned char *)"",                          // XC_StyleSheet_e,

  (unsigned char *)"<vn>",                      // XC_VarNorm,
  (unsigned char *)"</vn>",                     // XC_VarNorm_e,  space after not allowed - may be in free text

  (unsigned char *)"<cn>",                      // XC_AbbrNorm,
  (unsigned char *)"</cn>",                     // XC_AbbrNorm_e,  space after not allowed - may be in free text

  (unsigned char *)"<s3>",                      // XC_MngNearGroup
//                 "<s3 num=\"%s\">",
  (unsigned char *)"</s3>\n",                   // XC_MngNearGroup_e

  (unsigned char *)"<pd>",                      // XC_PronRed
  (unsigned char *)"</pd>",                     // XC_PronRed_e

  (unsigned char *)"<nul/>",                    // XC_Nul
  (unsigned char *)"",                          // XC_Nul_e

  (unsigned char *)"<sim/>",                    // XC_Similar
  (unsigned char *)"",                          // XC_Similar_e

  (unsigned char *)"<apr/>",                    // XC_Approx
  (unsigned char *)"",                          // XC_Approx_e

  (unsigned char *)"",                          // XC_Text
  (unsigned char *)"",                          // XC_Text_e

  (unsigned char *)"",                          // XC_Info
  (unsigned char *)"",                          // XC_Info_e

  (unsigned char *)"<ef>",                      // XC_Expand
  (unsigned char *)"</ef>",                     // XC_Expand_e

  (unsigned char *)"<sg>",                      // XC_StructGroup
  (unsigned char *)"</sg>",                     // XC_StructGroup_e

  (unsigned char *)"<gl>",                      // XC_Gloss
  (unsigned char *)"</gl>",                     // XC_Gloss_e

  (unsigned char *)"<fun>",                     // XC_FwNote
  (unsigned char *)"</fun>",                    // XC_FwNote_e

  (unsigned char *)"<i>",                       // XC_Italic
  (unsigned char *)"</i>",                      // XC_Italic_e

  (unsigned char *)"<mc>",                      // XC_ModCpdSrc
  (unsigned char *)"</mc>",                     // XC_ModCpdSrc_e

  (unsigned char *)"<symb>",                    // XC_Symb
  (unsigned char *)"</symb>",                   // XC_Symb_e

  (unsigned char *)"<if/>",                     // XC_Inform
  (unsigned char *)"",                          // XC_Inform_e
  (unsigned char *)"<uc/>",                     // XC_Uncount
  (unsigned char *)"",                          // XC_Uncount_e

  (unsigned char *)"<pvp>",                     // XC_PhrGroup
  (unsigned char *)"</pvp>",                    // XC_PhrGroup_e

  (unsigned char *)"",                          // XC_CpdMngGroup
  (unsigned char *)" ",                         // XC_CpdMngGroup_e

  (unsigned char *)"<obs/>",                    // XC_Obs
  (unsigned char *)"",                          // XC_Obs_e
  (unsigned char *)"<arc/>",                    // XC_Arch
  (unsigned char *)"",                          // XC_Arch_e
  (unsigned char *)"<vif/>",                    // XC_VeryInform
  (unsigned char *)"",                          // XC_VeryInform_e
  (unsigned char *)"<vul/>",                    // XC_Vulgar
  (unsigned char *)"",                          // XC_Vulgar_e

  (unsigned char *)"<su>",                      // XC_Super
  (unsigned char *)"</su>",                     // XC_Super_e

  (unsigned char *)"<cnt/>",                    // XC_Count
  (unsigned char *)"",                          // XC_Count_e

  (unsigned char *)"<hl>",                      // XC_HiLight
  (unsigned char *)"</hl>",                     // XC_HiLight_e
  (unsigned char *)"<sb>",                      // XC_SemiBold
  (unsigned char *)"</sb>",                     // XC_SemiBold_e

  (unsigned char *)"<dp>",                      // XC_CtrlDst,
  (unsigned char *)"</dp>",                     // XC_CtrlDst_e,

  (unsigned char *)"<in>",                      // XC_ExplNorm,
  (unsigned char *)"</in>",                     // XC_ExplNorm_e,

  (unsigned char *)"<ls>",                      // XC_Struct,
  (unsigned char *)"</ls>",                     // XC_Struct_e,
  (unsigned char *)"<lo>",                      // XC_OblStruct,
  (unsigned char *)"</lo>",                     // XC_OblStruct_e,

  (unsigned char *)"<lu>",                      // XC_Usage,
  (unsigned char *)"</lu>",                     // XC_Usage_e,

  (unsigned char *)"<hbase>",                   // XC_HBase,
  (unsigned char *)"</hbase> ",                 // XC_HBase_e,

  (unsigned char *)"<mg>",                      // XC_ModCpdGroup
  (unsigned char *)"</mg>",                     // XC_ModCpdGroup_e

  (unsigned char *)"",                          // XC_ExampleTransl
  (unsigned char *)" ",                         // XC_ExampleTransl_e

  (unsigned char *)"",                          // XC_IdiomTransl
  (unsigned char *)" ",                         // XC_IdiomTransl_e

  (unsigned char *)"<ed>",                      // XC_TechNote
  (unsigned char *)"</ed>",                     // XC_TechNote_e

  (unsigned char *)"",                          // XC_IdMngGroup
  (unsigned char *)" ",                         // XC_IdMngGroup_e

  (unsigned char *)"",                          // XC_Refinf
  (unsigned char *)" ",                         // XC_Refinf_e

  (unsigned char *)"<lw>",                      // XC_SrcWord,
  (unsigned char *)"</lw>",                     // XC_SrcWord_e,

  (unsigned char *)"<md>",                      // XC_ModCpdDst
  (unsigned char *)"</md>",                     // XC_ModCpdDst_e

  (unsigned char *)"<cd>",                      // XC_ContextDst
  (unsigned char *)"</cd>",                     // XC_ContextDst_e

  (unsigned char *)"<dc>",                      // XC_ExplDst
  (unsigned char *)"</dc>",                     // XC_ExplDst_e

  (unsigned char *)"<x>",                       // XC_RefWord
  (unsigned char *)"</x>",                      // XC_RefWord_e

  (unsigned char *)"<xs>",                      // XC_RefNum
  (unsigned char *)"</xs>",                     // XC_RefNum_e

  (unsigned char *)"<fx>",                      // XC_RefXWord
  (unsigned char *)"</fx>",                     // XC_RefXWord_e

  (unsigned char *)"<t>",                       // XC_RefTab
  (unsigned char *)"</t>",                      // XC_RefTab_e

  (unsigned char *)"<n>",                       // XC_RefPage
  (unsigned char *)"</n>",                      // XC_RefPage_e

  (unsigned char *)"<hm>",                      // XC_RefHom,  must be converted to XC_Hom
  (unsigned char *)"</hm>",                     // XC_RefHom_e,  space after not allowed - may be in free text

  (unsigned char *)"<cw>",                      // XC_SingleCpdWord
  (unsigned char *)"</cw>",                     // XC_SingleCpdWord_e

  (unsigned char *)"<fd>",                      // XC_FormGroupDst,
  (unsigned char *)"</fd>",                     // XC_FormGroupDst_e,

  (unsigned char *)"<dg>",                      // XC_DerivGroup
  (unsigned char *)"</dg>",                     // XC_DerivGroup_e

  (unsigned char *)"<ld>",                      // XC_Derivative
  (unsigned char *)"</ld>",                     // XC_Derivative_e

  (unsigned char *)"<ag>",                      // XC_StressParGroup
  (unsigned char *)"</ag>",                     // XC_StressParGroup_e

  (unsigned char *)"<ac>",                      // XC_StressPar
  (unsigned char *)"</ac>",                     // XC_StressPar_e

  (unsigned char *)"<cp>",                      // XC_PunctMark
  (unsigned char *)"</cp>",                     // XC_PunctMark_e

  (unsigned char *)"<lg>",                      // XC_LevelGroup
  (unsigned char *)"</lg>",                     // XC_LevelGroup_e

  (unsigned char *)"<lv>",                      // XC_Level
  (unsigned char *)"</lv>",                     // XC_Level_e

// (unsigned char *)"<tx>",                      // XC_TextExpr
// (unsigned char *)"</tx>",                     // XC_TextExpr_e

  (unsigned char *)"<us>",                      // XC_UsNoteSrc,
  (unsigned char *)"</us>",                     // XC_UsNoteSrc_e,

  (unsigned char *)"<img/>",                    // XC_Img
  (unsigned char *)"",                          // XC_Img_e

  (unsigned char *)"<xcg>",                     // XC_RefSecSynGr
  (unsigned char *)"</xcg>",                    // XC_RefSecSynGr_e
  (unsigned char *)"<xc>",                      // XC_RefSecSyn
  (unsigned char *)"</xc>",                     // XC_RefSecSyn_e

  (unsigned char *)"<xpg>",                     // XC_RefPriSynGr
  (unsigned char *)"</xpg>",                    // XC_RefPriSynGr_e
  (unsigned char *)"<xp>",                      // XC_RefPriSyn
  (unsigned char *)"</xp>",                     // XC_RefPriSyn_e

  (unsigned char *)"<xyg>",                     // XC_RefSynGr
  (unsigned char *)"</xyg>",                    // XC_RefSynGr_e
  (unsigned char *)"<xy>",                      // XC_RefSyn
  (unsigned char *)"</xy>",                     // XC_RefSyn_e

  (unsigned char *)"<xeg>",                     // XC_RefExamplGr
  (unsigned char *)"</xeg>",                    // XC_RefExamplGr_e
  (unsigned char *)"<xe>",                      // XC_RefExampl
  (unsigned char *)"</xe>",                     // XC_RefExampl_e

  (unsigned char *)"<xag>",                     // XC_RefAntGr
  (unsigned char *)"</xag>",                    // XC_RefAntGr_e
  (unsigned char *)"<xa>",                      // XC_RefAnt
  (unsigned char *)"</xa>",                     // XC_RefAnt_e

  (unsigned char *)"<xng>",                     // XC_RefExamplSinglGr
  (unsigned char *)"</xng>",                    // XC_RefExamplSinglGr_e

  (unsigned char *)"<sub>",                     // XC_Subscript
  (unsigned char *)"</sub>",                    // XC_Subscript_e

  (unsigned char *)"<ce>",                      // XC_CodeExampleInline
  (unsigned char *)"</ce>",                     // XC_CodeExampleInline_e

  (unsigned char *)"<ng>",                      // XC_EnumGr
  (unsigned char *)"</ng>",                     // XC_EnumGr_e

  (unsigned char *)"<en>",                      // XC_Enum
//(unsigned char *)"<en num="">",     // if num <> "" - additional space should be added after it in delimiter
//(unsigned char *)"<en num="-">",
//(unsigned char *)"<en num="*">",
//(unsigned char *)"<en num="1.">",
  (unsigned char *)"</en>",                     // XC_Enum_e

  (unsigned char *)"<cb>",                      // XC_CodeBaseWord
  (unsigned char *)"</cb>",                     // XC_CodeBaseWord_e

  (unsigned char *)"<cl>",                      // XC_CodeExample
  (unsigned char *)"</cl>",                     // XC_CodeExample_e

  (unsigned char *)"<table>",                   // XC_Table
  (unsigned char *)"</table>",                  // XC_Table_e
  (unsigned char *)"<tr>",                      // XC_TableRow
  (unsigned char *)"</tr>",                     // XC_TableRow_e
  (unsigned char *)"<td>",                      // XC_TableCell
  (unsigned char *)"</td>",                     // XC_TableCell_e

  (unsigned char *)"<eq/>",                     // XC_Equiation
  (unsigned char *)"",                          // XC_Equiation_e

  (unsigned char *)"<br/>",                     // XC_Break
  (unsigned char *)"",                          // XC_Break_e

  (unsigned char *)"<el>",                      // XC_EquInline
  (unsigned char *)"</el>",                     // XC_EquInline_e

  (unsigned char *)"<sl>",                      // XC_Special
  (unsigned char *)"</sl>",                     // XC_Special_e

  (unsigned char *)"<egf>",                     // XC_ExampleGroupForced
  (unsigned char *)"</egf>\n",                  // XC_ExampleGroupForced_e

  (unsigned char *)"<icf>",                     // XC_ExplForced
  (unsigned char *)"</icf>",                    // XC_ExplForced_e

  (unsigned char *)"<vg>",                      // XC_VarGroup
  (unsigned char *)"</vg>",                     // XC_VarGroup_e

  (unsigned char *)"<rel/>",                    // XC_Relatives
  (unsigned char *)"",                          // XC_Relatives_e

  (unsigned char *)"<tn>",                      // XC_Page
  (unsigned char *)"</tn>",                     // XC_Page_e

  (unsigned char *)"<nr>",                      // XC_SemNr
  (unsigned char *)"</nr>",                     // XC_SemNr_e

  (unsigned char *)"<twl>",                     // XC_TrWordLit
  (unsigned char *)"</twl>",                    // XC_TrWordLit_e

  (unsigned char *)"<twe>",                     // XC_TrWordEng
  (unsigned char *)"</twe>",                    // XC_TrWordEng_e

  (unsigned char *)"<twg>",                     // XC_TrWordGer
  (unsigned char *)"</twg>",                    // XC_TrWordGer_e

  (unsigned char *)"<twf>",                     // XC_TrWordFre
  (unsigned char *)"</twf>",                    // XC_TrWordFre_e

  (unsigned char *)"<twp>",                     // XC_TrWordPol
  (unsigned char *)"</twp>",                    // XC_TrWordPol_e

  (unsigned char *)"<twr>",                     // XC_TrWordRus
  (unsigned char *)"</twr>",                    // XC_TrWordRus_e

  (unsigned char *)"<vs>",                      // XC_Species
  (unsigned char *)"</vs>",                     // XC_Species_e

  (unsigned char *)"<sgf>",                     // XC_StructGroupForced
  (unsigned char *)"</sgf>",                    // XC_StructGroupForced_e

  (unsigned char *)"<vb>",                      // XC_VarBold
  (unsigned char *)"</vb>",                     // XC_VarBold_e

  (unsigned char *)"<xtg>",                     // XC_RefAntStrictGr
  (unsigned char *)"</xtg>",                    // XC_RefAntStrictGr_e
  (unsigned char *)"<xt>",                      // XC_RefAntStrict
  (unsigned char *)"</xt>",                     // XC_RefAntStrict_e

  NULL
};


// --------------------------------------------------
const unsigned char *plpszaSgmDictTagsFull[XC_TG_NumOfDictTagsArr68+1] = // Dictionary XML tag names with sgml Tage tags
{
  (unsigned char *)"<di>\n\n",
                // "<di name=\"%s\">\n\n",
                                                // XC_Dict
  (unsigned char *)"</di>\n",                   // XC_Dict_e,

  (unsigned char *)"<ue>\n",                    // XC_NrtEntry,
  (unsigned char *)"</ue>\n\n",                 // XC_NrtEntry_e,
  (unsigned char *)"<se>\n",                    // XC_StEntry,
//                 "<se id=\"%ld\">"
  (unsigned char *)"</se>\n\n",                 // XC_StEntry_e,

  (unsigned char *)"<hw>",                      // XC_HeadWord,
  (unsigned char *)"</hw>",                     // XC_HeadWord_e,   space after not allowed - may be followed by XC_Hom
  (unsigned char *)"<la>",                      // XC_Label,
  (unsigned char *)"</la>",                     // XC_Label_e,      space after not allowed - may be inside of parentheses
  (unsigned char *)"<tw>",                      // XC_TrWord,
  (unsigned char *)"</tw>",                     // XC_TrWord_e,     space after not allowed - may be inside of parentheses
  (unsigned char *)"<un>",                      // XC_UsNoteDst,
  (unsigned char *)"</un>",                     // XC_UsNoteDst_e,
  (unsigned char *)"<xr>",                      // XC_Reference,
//                 "<xr href=\"%s#%ld\">" // TV_XM_HrefDelim // TV_HTM_HrefDelim
  (unsigned char *)"</xr>",                     // XC_Reference_e,  space after not allowed - may be in free text
  (unsigned char *)"<st>",                      // XC_StEntryText,
  (unsigned char *)"</st>",                     // XC_StEntryText_e,

  (unsigned char *)"<p>",                       // XC_Paragraph,
  (unsigned char *)"</p>\n",                    // XC_Paragraph_e,  space after not allowed - may be in free text // tai kad nëra prasmës - po paragrafo vis tiek eilutë lûþta

  (unsigned char *)"",                          // XC_Version,
  (unsigned char *)"",                          // XC_Version_e,

  (unsigned char *)"",                          // XC_DocType,
  (unsigned char *)"",                          // XC_DocType_e,

  (unsigned char *)"<v>",                       // XC_Variant,
  (unsigned char *)"</v>",                      // XC_Variant_e,   space after not allowed - may be in parentheses

  (unsigned char *)"<ps>",                      // XC_PartOfSpeechSrc,
  (unsigned char *)"</ps>",                     // XC_PartOfSpeechSrc_e,

  (unsigned char *)"<!!!hg>\n", // "<hg>\n",    // XC_HeadWordGroup,
  (unsigned char *)"</!!!hg>\n", // "</hg>\n",  // XC_HeadWordGroup_e,
  (unsigned char *)"<tg>",                      // XC_TranslGroup,
  (unsigned char *)"</tg>\n",                   // XC_TranslGroup_e,

  (unsigned char *)"<f>",                       // XC_FormDst,
  (unsigned char *)"</f>",                      // XC_FormDst_e,  space after not allowed - may be in parentheses
  (unsigned char *)"<fs>",                      // XC_FormSrc,
  (unsigned char *)"</fs>",                     // XC_FormSrc_e,  space after not allowed - may be in parentheses

  (unsigned char *)"<ic>",                      // XC_ExplSrc,
  (unsigned char *)"</ic>",                     // XC_ExplSrc_e,  space after not allowed - may be in free text

  (unsigned char *)"<le>",                      // XC_Example,
  (unsigned char *)"</le>",                     // XC_Example_e,  space after not allowed - may be in parentheses
  (unsigned char *)"<eg>",                      // XC_ExampleGroup,
  (unsigned char *)"</eg>\n",                   // XC_ExampleGroup_e,

  (unsigned char *)"<pt>",                      // XC_Parenth,
  (unsigned char *)"</pt>",                     // XC_Parenth_e,  space after not allowed - may be in free text

  (unsigned char *)"<li>",                      // XC_Idiom,
  (unsigned char *)"</li>",                     // XC_Idiom_e,

  (unsigned char *)"<id>",                      // XC_IdiomGroup,
  (unsigned char *)"</id>\n",                   // XC_IdiomGroup_e,

  (unsigned char *)"<s1>",                      // XC_CtgGroup,
//                 "<s1 num=\"%s\">"
  (unsigned char *)"</s1>\n",                   // XC_CtgGroup_e,

  (unsigned char *)"<base>",                    // XC_Base,
  (unsigned char *)"</base> ",                  // XC_Base_e,
  (unsigned char *)"<cg>",                      // XC_CompoundGroup,
  (unsigned char *)"</cg>\n",                   // XC_CompoundGroup_e,
  (unsigned char *)"<lc>",                      // XC_CompoundWord,
  (unsigned char *)"</lc> ",                    // XC_CompoundWord_e,

  (unsigned char *)"<s2>",                      // XC_MngGroup,
//                 "<s2 num=\"%ld\">"
  (unsigned char *)"</s2>\n",                   // XC_MngGroup_e,

  (unsigned char *)"<ast/>",                    // XC_Asterix,
  (unsigned char *)"",                          // XC_Asterix_e,  space after not allowed - may be in free text

  (unsigned char *)"<sp>",                      // XC_CtrlSrc,
  (unsigned char *)"</sp>",                     // XC_CtrlSrc_e,

  (unsigned char *)"<pr>",                      // XC_PrGroup,
  (unsigned char *)"</pr>",                     // XC_PrGroup_e,  space after not allowed - may be inside of parentheses
  (unsigned char *)"<ph>",                      // XC_Pron,
  (unsigned char *)"</ph>",                     // XC_Pron_e,

  (unsigned char *)"<ct>",                      // XC_Abbr,
  (unsigned char *)"</ct>",                     // XC_Abbr_e,  space after not allowed - may be in free text

  (unsigned char *)"<hm>",                      // XC_Hom,
  (unsigned char *)"</hm>",                     // XC_Hom_e,  space after not allowed - may be in free text

  (unsigned char *)"<co>",                      // XC_ContextSrc,
  (unsigned char *)"</co>",                     // XC_ContextSrc_e,

  (unsigned char *)"<pp>",                      // XC_CtrlGroup,
  (unsigned char *)"</pp>",                     // XC_CtrlGroup_e,  space after not allowed - may be in free text

  (unsigned char *)"<gr>",                      // XC_PartOfSpeechDst,
  (unsigned char *)"</gr>",                     // XC_PartOfSpeechDst_e,

  (unsigned char *)"<fg>",                      // XC_FormGroupSrc,
  (unsigned char *)"</fg>",                     // XC_FormGroupSrc_e,  space after not allowed - may be in parentheses

  (unsigned char *)"",                          // XC_StyleSheet,
  (unsigned char *)"",                          // XC_StyleSheet_e,

  (unsigned char *)"<vn>",                      // XC_VarNorm,
  (unsigned char *)"</vn>",                     // XC_VarNorm_e,  space after not allowed - may be in free text

  (unsigned char *)"<cn>",                      // XC_AbbrNorm,
  (unsigned char *)"</cn>",                     // XC_AbbrNorm_e,  space after not allowed - may be in free text

  (unsigned char *)"<s3>",                      // XC_MngNearGroup
//                 "<s3 num=\"%s\">",
  (unsigned char *)"</s3>\n",                   // XC_MngNearGroup_e

  (unsigned char *)"<pd>",                      // XC_PronRed
  (unsigned char *)"</pd>",                     // XC_PronRed_e

  (unsigned char *)"<nul/>",                    // XC_Nul
  (unsigned char *)"",                          // XC_Nul_e

  (unsigned char *)"<sim/>",                    // XC_Similar
  (unsigned char *)"",                          // XC_Similar_e

  (unsigned char *)"<apr/>",                    // XC_Approx
  (unsigned char *)"",                          // XC_Approx_e

  (unsigned char *)"<!!!tx>",                   // XC_Text
  (unsigned char *)"</!!!tx>",                  // XC_Text_e

  (unsigned char *)"<!!!info>",                 // XC_Info
  (unsigned char *)"</!!!info>",                // XC_Info_e

  (unsigned char *)"<ef>",                      // XC_Expand
  (unsigned char *)"</ef>",                     // XC_Expand_e

  (unsigned char *)"<sg>",                      // XC_StructGroup
  (unsigned char *)"</sg>",                     // XC_StructGroup_e

  (unsigned char *)"<gl>",                      // XC_Gloss
  (unsigned char *)"</gl>",                     // XC_Gloss_e

  (unsigned char *)"<fun>",                     // XC_FwNote
  (unsigned char *)"</fun>",                    // XC_FwNote_e

  (unsigned char *)"<i>",                       // XC_Italic
  (unsigned char *)"</i>",                      // XC_Italic_e

  (unsigned char *)"<mc>",                      // XC_ModCpdSrc
  (unsigned char *)"</mc>",                     // XC_ModCpdSrc_e

  (unsigned char *)"<!!!symb>",                 // XC_Symb
  (unsigned char *)"</!!!symb>",                // XC_Symb_e

  (unsigned char *)"<if/>",                     // XC_Inform
  (unsigned char *)"",                          // XC_Inform_e
  (unsigned char *)"<uc/>",                     // XC_Uncount
  (unsigned char *)"",                          // XC_Uncount_e

  (unsigned char *)"<pvp>",                     // XC_PhrGroup
  (unsigned char *)"</pvp>",                    // XC_PhrGroup_e

  (unsigned char *)"<s2c>",  // "<!!!s2>",      // XC_CpdMngGroup
  (unsigned char *)"</s2c>", // "</!!!s2>",     // XC_CpdMngGroup_e

  (unsigned char *)"<obs/>",                    // XC_Obs
  (unsigned char *)"",                          // XC_Obs_e
  (unsigned char *)"<arc/>",                    // XC_Arch
  (unsigned char *)"",                          // XC_Arch_e
  (unsigned char *)"<vif/>",                    // XC_VeryInform
  (unsigned char *)"",                          // XC_VeryInform_e
  (unsigned char *)"<vul/>",                    // XC_Vulgar
  (unsigned char *)"",                          // XC_Vulgar_e

  (unsigned char *)"<su>",                      // XC_Super
  (unsigned char *)"</su>",                     // XC_Super_e

  (unsigned char *)"<cnt/>",                    // XC_Count
  (unsigned char *)"",                          // XC_Count_e

  (unsigned char *)"<hl>",                      // XC_HiLight
  (unsigned char *)"</hl>",                     // XC_HiLight_e
  (unsigned char *)"<sb>",                      // XC_SemiBold
  (unsigned char *)"</sb>",                     // XC_SemiBold_e

  (unsigned char *)"<dp>",                      // XC_CtrlDst,
  (unsigned char *)"</dp>",                     // XC_CtrlDst_e,

  (unsigned char *)"<in>",                      // XC_ExplNorm,
  (unsigned char *)"</in>",                     // XC_ExplNorm_e,

  (unsigned char *)"<ls>",                      // XC_Struct,
  (unsigned char *)"</ls>",                     // XC_Struct_e,
  (unsigned char *)"<lo>",                      // XC_OblStruct,
  (unsigned char *)"</lo>",                     // XC_OblStruct_e,

  (unsigned char *)"<lu>",                      // XC_Usage,
  (unsigned char *)"</lu>",                     // XC_Usage_e,

  (unsigned char *)"<hbase>",                   // XC_Base,
  (unsigned char *)"</hbase> ",                 // XC_Base_e,

  (unsigned char *)"<mg>",                      // XC_ModCpdGroup
  (unsigned char *)"</mg>",                     // XC_ModCpdGroup_e

  (unsigned char *)"<!!!te>",                   // XC_ExampleTransl
  (unsigned char *)"</!!!te>",                  // XC_ExampleTransl_e

  (unsigned char *)"<!!!ti>",                   // XC_IdiomTransl
  (unsigned char *)"</!!!ti>",                  // XC_IdiomTransl_e

  (unsigned char *)"<ed>",                      // XC_TechNote
  (unsigned char *)"</ed>",                     // XC_TechNote_e

  (unsigned char *)"<s2i>",  // "<!!!s2>",      // XC_IdMngGroup
  (unsigned char *)"</s2i>", // "</!!!s2>",     // XC_IdMngGroup_e

  (unsigned char *)"<!!!xr>",                   // XC_Refinf
  (unsigned char *)"</!!!xr>",                  // XC_Refinf_e, space after not allowed - may be in free text

  (unsigned char *)"<lw>",                      // XC_SrcWord,
  (unsigned char *)"</lw>",                     // XC_SrcWord_e,

  (unsigned char *)"<md>",                      // XC_ModCpdDst
  (unsigned char *)"</md>",                     // XC_ModCpdDst_e

  (unsigned char *)"<cd>",                      // XC_ContextDst
  (unsigned char *)"</cd>",                     // XC_ContextDst_e

  (unsigned char *)"<dc>",                      // XC_ExplDst
  (unsigned char *)"</dc>",                     // XC_ExplDst_e

  (unsigned char *)"<x>",                       // XC_RefWord
  (unsigned char *)"</x>",                      // XC_RefWord_e

  (unsigned char *)"<xs>",                      // XC_RefNum
  (unsigned char *)"</xs>",                     // XC_RefNum_e

  (unsigned char *)"<fx>",                      // XC_RefXWord
  (unsigned char *)"</fx>",                     // XC_RefXWord_e

  (unsigned char *)"<t>",                       // XC_RefTab
  (unsigned char *)"</t>",                      // XC_RefTab_e

  (unsigned char *)"<n>",                       // XC_RefPage
  (unsigned char *)"</n>",                      // XC_RefPage_e

  (unsigned char *)"<hm!!!>",                   // XC_RefHom,  must be converted to XC_Hom
  (unsigned char *)"</hm!!!>",                  // XC_RefHom_e,  space after not allowed - may be in free text

  (unsigned char *)"<cw>",                      // XC_SingleCpdWord
  (unsigned char *)"</cw>",                     // XC_SingleCpdWord_e

  (unsigned char *)"<fd>",                      // XC_FormGroupDst,
  (unsigned char *)"</fd>",                     // XC_FormGroupDst_e,

  (unsigned char *)"<dg>",                      // XC_DerivGroup
  (unsigned char *)"</dg>",                     // XC_DerivGroup_e

  (unsigned char *)"<ld>",                      // XC_Derivative
  (unsigned char *)"</ld>",                     // XC_Derivative_e

  (unsigned char *)"<ag>",                      // XC_StressParGroup
  (unsigned char *)"</ag>",                     // XC_StressParGroup_e

  (unsigned char *)"<ac>",                      // XC_StressPar
  (unsigned char *)"</ac>",                     // XC_StressPar_e

  (unsigned char *)"<cp>",                      // XC_PunctMark
  (unsigned char *)"</cp>",                     // XC_PunctMark_e

  (unsigned char *)"<lg>",                      // XC_LevelGroup
  (unsigned char *)"</lg>",                     // XC_LevelGroup_e

  (unsigned char *)"<lv>",                      // XC_Level
  (unsigned char *)"</lv>",                     // XC_Level_e

// (unsigned char *)"<tx>",                      // XC_TextExpr
// (unsigned char *)"</tx>",                     // XC_TextExpr_e

  (unsigned char *)"<us>",                      // XC_UsNoteSrc,
  (unsigned char *)"</us>",                     // XC_UsNoteSrc_e,

  (unsigned char *)"<img/>",                    // XC_Img
  (unsigned char *)"",                          // XC_Img_e

  (unsigned char *)"<xcg>",                     // XC_RefSecSynGr
  (unsigned char *)"</xcg>",                    // XC_RefSecSynGr_e
  (unsigned char *)"<xc>",                      // XC_RefSecSyn
  (unsigned char *)"</xc>",                     // XC_RefSecSyn_e

  (unsigned char *)"<xpg>",                     // XC_RefPriSynGr
  (unsigned char *)"</xpg>",                    // XC_RefPriSynGr_e
  (unsigned char *)"<xp>",                      // XC_RefPriSyn
  (unsigned char *)"</xp>",                     // XC_RefPriSyn_e

  (unsigned char *)"<xyg>",                     // XC_RefSynGr
  (unsigned char *)"</xyg>",                    // XC_RefSynGr_e
  (unsigned char *)"<xy>",                      // XC_RefSyn
  (unsigned char *)"</xy>",                     // XC_RefSyn_e

  (unsigned char *)"<xeg>",                     // XC_RefExamplGr
  (unsigned char *)"</xeg>",                    // XC_RefExamplGr_e
  (unsigned char *)"<xe>",                      // XC_RefExampl
  (unsigned char *)"</xe>",                     // XC_RefExampl_e

  (unsigned char *)"<xag>",                     // XC_RefAntGr
  (unsigned char *)"</xag>",                    // XC_RefAntGr_e
  (unsigned char *)"<xa>",                      // XC_RefAnt
  (unsigned char *)"</xa>",                     // XC_RefAnt_e

  (unsigned char *)"<xng>",                     // XC_RefExamplSinglGr
  (unsigned char *)"</xng>",                    // XC_RefExamplSinglGr_e

  (unsigned char *)"<sub>",                     // XC_Subscript
  (unsigned char *)"</sub>",                    // XC_Subscript_e

  (unsigned char *)"<ce>",                      // XC_CodeExampleInline
  (unsigned char *)"</ce>",                     // XC_CodeExampleInline_e

  (unsigned char *)"<ng>",                      // XC_EnumGr
  (unsigned char *)"</ng>",                     // XC_EnumGr_e

  (unsigned char *)"<en>",                      // XC_Enum
//(unsigned char *)"<en num="">",     // if num <> "" - additional space should be added after it in delimiter
//(unsigned char *)"<en num="-">",
//(unsigned char *)"<en num="*">",
//(unsigned char *)"<en num="1.">",
  (unsigned char *)"</en>",                     // XC_Enum_e

  (unsigned char *)"<cb>",                      // XC_CodeBaseWord
  (unsigned char *)"</cb>",                     // XC_CodeBaseWord_e

  (unsigned char *)"<cl>",                      // XC_CodeExample
  (unsigned char *)"</cl>",                     // XC_CodeExample_e

   (unsigned char *)"<table>",                  // XC_Table
   (unsigned char *)"</table>",                 // XC_Table_e
   (unsigned char *)"<tr>",                     // XC_TableRow
   (unsigned char *)"</tr>",                    // XC_TableRow_e
   (unsigned char *)"<td>",                     // XC_TableCell
   (unsigned char *)"</td>",                    // XC_TableCell_e

  (unsigned char *)"<eq/>",                    // XC_Equiation
  (unsigned char *)"",                         // XC_Equiation_e

  (unsigned char *)"<br/>",                    // XC_Break
  (unsigned char *)"",                         // XC_Break_e

  (unsigned char *)"<el>",                     // XC_EquInline
  (unsigned char *)"</el>",                    // XC_EquInline_e

  (unsigned char *)"<sl>",                      // XC_Special
  (unsigned char *)"</sl>",                     // XC_Special_e

  (unsigned char *)"<egf>",                     // XC_ExampleGroupForced
  (unsigned char *)"</egf>\n",                  // XC_ExampleGroupForced_e

  (unsigned char *)"<icf>",                     // XC_ExplForced
  (unsigned char *)"</icf>",                    // XC_ExplForced_e

  (unsigned char *)"<vg>",                      // XC_VarGroup
  (unsigned char *)"</vg>",                     // XC_VarGroup_e

  (unsigned char *)"<rel/>",                    // XC_Relatives
  (unsigned char *)"",                          // XC_Relatives_e

  (unsigned char *)"<tn>",                      // XC_Page
  (unsigned char *)"</tn>",                     // XC_Page_e

  (unsigned char *)"<nr>",                      // XC_SemNr
  (unsigned char *)"</nr>",                     // XC_SemNr_e

  (unsigned char *)"<twl>",                     // XC_TrWordLit
  (unsigned char *)"</twl>",                    // XC_TrWordLit_e

  (unsigned char *)"<twe>",                     // XC_TrWordEng
  (unsigned char *)"</twe>",                    // XC_TrWordEng_e

  (unsigned char *)"<twg>",                     // XC_TrWordGer
  (unsigned char *)"</twg>",                    // XC_TrWordGer_e

  (unsigned char *)"<twf>",                     // XC_TrWordFre
  (unsigned char *)"</twf>",                    // XC_TrWordFre_e

  (unsigned char *)"<twp>",                     // XC_TrWordPol
  (unsigned char *)"</twp>",                    // XC_TrWordPol_e

  (unsigned char *)"<twr>",                     // XC_TrWordRus
  (unsigned char *)"</twr>",                    // XC_TrWordRus_e

  (unsigned char *)"<vs>",                      // XC_Species
  (unsigned char *)"</vs>",                     // XC_Species_e

  (unsigned char *)"<sgf>",                     // XC_StructGroupForced
  (unsigned char *)"</sgf>",                    // XC_StructGroupForced_e

  (unsigned char *)"<vb>",                      // XC_VarBold
  (unsigned char *)"</vb>",                     // XC_VarBold_e

  (unsigned char *)"<xtg>",                     // XC_RefAntStrictGr
  (unsigned char *)"</xtg>",                    // XC_RefAntStrictGr_e
  (unsigned char *)"<xt>",                      // XC_RefAntStrict
  (unsigned char *)"</xt>",                     // XC_RefAntStrict_e

  NULL
};


const int iaSgmDictCodeTables[XC_TG_NumOfDictTagsArr68] = // SGML Tage file code tables
{
  0,     // XC_Dict,
  0,     // XC_Dict_e,
  TV_MAIN_SGM_CTBL,    // XC_NrtEntry,
  0,     // XC_NrtEntry_e,
  0,     // XC_StEntry,
  0,     // XC_StEntry_e,
  TV_MAIN_SGM_CTBL,    // XC_HeadWord,
  0,     // XC_HeadWord_e,
  TV_MAIN_SGM_CTBL,    // XC_Label,
  0,     // XC_Label_e,
  TV_MAIN_SGM_CTBL,    // XC_TrWord,
  0,     // XC_TrWord_e,
  TV_MAIN_SGM_CTBL,    // XC_UsNoteDst,
  0,     // XC_UsNoteDst_e,
  TV_MAIN_SGM_CTBL,    // XC_Reference,
  0,     // XC_Reference_e,
  TV_MAIN_SGM_CTBL,    // XC_StEntryText,
  0,     // XC_StEntryText_e,

  TV_MAIN_SGM_CTBL,    // XC_Paragraph,
  0,     // XC_Paragraph_e,

  0,     // XC_Version,
  0,     // XC_Version_e,
  0,     // XC_DocType,
  0,     // XC_DocType_e,

  TV_MAIN_SGM_CTBL,    // XC_Variant,
  0,     // XC_Variant_e,
  TV_MAIN_SGM_CTBL,    // XC_PartOfSpeechSrc,
  0,     // XC_PartOfSpeechSrc_e,

  0,     // XC_HeadWordGroup,
  0,     // XC_HeadWordGroup_e,
  0,     // XC_TranslGroup,
  0,     // XC_TranslGroup_e,

  TV_MAIN_SGM_CTBL,    // XC_FormDst,
  0,     // XC_FormDst_e,
  TV_MAIN_SGM_CTBL,    // XC_FormSrc,
  0,     // XC_FormSrc_e,

  TV_MAIN_SGM_CTBL,    // XC_ExplSrc,
  0,     // XC_ExplSrc_e,
  TV_MAIN_SGM_CTBL,    // XC_Example,
  0,     // XC_Example_e,

  0,     // XC_ExampleGroup,
  0,     // XC_ExampleGroup_e,

  TV_MAIN_SGM_CTBL,    // XC_Parenth,
  0,     // XC_Parenth_e,

  TV_MAIN_SGM_CTBL,    // XC_Idiom,
  0,     // XC_Idiom_e,

  0,     // XC_IdiomGroup,
  0,     // XC_IdiomGroup_e,

  0,     // XC_CtgGroup,
  0,     // XC_CtgGroup_e,

  TV_MAIN_SGM_CTBL,    // XC_Base,
  0,     // XC_Base_e,
  0,     // XC_CompoundGroup,
  0,     // XC_CompoundGroup_e,
  TV_MAIN_SGM_CTBL,    // XC_CompoundWord,
  0,     // XC_CompoundWord_e,

  0,     // XC_MngGroup,
  0,     // XC_MngGroup_e,

  0,     // XC_Asterix,
  0,     // XC_Asterix_e,

  TV_MAIN_SGM_CTBL,    // XC_CtrlSrc,
  0,     // XC_CtrlSrc_e,

  0,     // XC_PrGroup,
  0,     // XC_PrGroup_e,
  82,    // XC_Pron,
  0,     // XC_Pron_e,

  TV_MAIN_SGM_CTBL,    // XC_Abbr,
  0,     // XC_Abbr_e,

  TV_MAIN_SGM_CTBL,    // XC_Hom,
  0,     // XC_Hom_e,

  TV_MAIN_SGM_CTBL,    // XC_ContextSrc,
  0,     // XC_ContextSrc_e,

  0,     // XC_CtrlGroup,
  0,     // XC_CtrlGroup_e,

  TV_MAIN_SGM_CTBL,    // XC_PartOfSpeechDst,
  0,     // XC_PartOfSpeechDst_e,

  0,     // XC_FormGroupSrc,
  0,     // XC_FormGroupSrc_e,

  0,     // XC_StyleSheet,
  0,     // XC_StyleSheet_e,

  TV_MAIN_SGM_CTBL,    // XC_VarNorm,
  0,     // XC_VarNorm_e,

  TV_MAIN_SGM_CTBL,    // XC_AbbrNorm,
  0,     // XC_AbbrNorm_e,

  0,     // XC_MngNearGroup
  0,     // XC_MngNearGroup_e

  82,    // XC_PronRed
  0,     // XC_PronRed_e

  0,     // XC_Nul
  0,     // XC_Nul_e

  0,     // XC_Similar
  0,     // XC_Similar_e

  0,     // XC_Approx
  0,     // XC_Approx_e

  TV_MAIN_SGM_CTBL,    // XC_Text
  0,     // XC_Text_e

  TV_MAIN_SGM_CTBL,    // XC_Info
  0,     // XC_Info_e

  TV_MAIN_SGM_CTBL,    // XC_Expand
  0,     // XC_Expand_e

  0,     // XC_StructGroup
  0,     // XC_StructGroup_e

  TV_MAIN_SGM_CTBL,    // XC_Gloss
  0,     // XC_Gloss_e

  TV_MAIN_SGM_CTBL,    // XC_FwNote
  0,     // XC_FwNote_e

  TV_MAIN_SGM_CTBL,    // XC_Italic
  0,     // XC_Italic_e

  TV_MAIN_SGM_CTBL,    // XC_ModCpdSrc
  0,     // XC_ModCpdSrc_e

  84,    // XC_Symb // Verdana encoding
  0,     // XC_Symb_e

  0,     // XC_Inform
  0,     // XC_Inform_e
  0,     // XC_Uncount
  0,     // XC_Uncount_e

  0,     // XC_PhrGroup
  0,     // XC_PhrGroup_e

  0,     // XC_CpdMngGroup
  0,     // XC_CpdMngGroup_e

  0,     // XC_Obs
  0,     // XC_Obs_e
  0,     // XC_Arch
  0,     // XC_Arch_e
  0,     // XC_VeryInform
  0,     // XC_VeryInform_e
  0,     // XC_Vulgar
  0,     // XC_Vulgar_e

  TV_MAIN_SGM_CTBL,    // XC_Super
  0,     // XC_Super_e

  0,     // XC_Count
  0,     // XC_Count_e

  TV_MAIN_SGM_CTBL,    // XC_HiLight
  0,     // XC_HiLight_e
  TV_MAIN_SGM_CTBL,    // XC_SemiBold
  0,     // XC_SemiBold_e

  TV_MAIN_SGM_CTBL,    // XC_CtrlDst
  0,     // XC_CtrlDst_e

  TV_MAIN_SGM_CTBL,    // XC_ExplNorm
  0,     // XC_ExplNorm_e

  TV_MAIN_SGM_CTBL,    // XC_Struct,
  0,     // XC_Struct_e,
  TV_MAIN_SGM_CTBL,    // XC_OblStruct,
  0,     // XC_OblStruct_e,

  TV_MAIN_SGM_CTBL,    // XC_Usage,
  0,     // XC_Usage_e,

  TV_MAIN_SGM_CTBL,    // XC_HBase,
  0,     // XC_HBase_e,

  0,     // XC_ModCpdGroup
  0,     // XC_ModCpdGroup_e

  TV_MAIN_SGM_CTBL,    // XC_ExampleTransl
  0,     // XC_ExampleTransl_e

  TV_MAIN_SGM_CTBL,    // XC_IdiomTransl
  0,     // XC_IdiomTransl_e

  TV_MAIN_SGM_CTBL,    // XC_TechNote
  0,     // XC_TechNote_e

  0,     // XC_IdMngGroup
  0,     // XC_IdMngGroup_e

  TV_MAIN_SGM_CTBL,    // XC_Refinf,
  0,     // XC_Refinf_e,

  TV_MAIN_SGM_CTBL,    // XC_SrcWord,
  0,     // XC_SrcWord_e,

  TV_MAIN_SGM_CTBL,    // XC_ModCpdDst
  0,     // XC_ModCpdDst_e

  TV_MAIN_SGM_CTBL,    // XC_ContextDst
  0,     // XC_ContextDst_e

  TV_MAIN_SGM_CTBL,    // XC_ExplDst
  0,     // XC_ExplDst_e

  TV_MAIN_SGM_CTBL,    // XC_RefWord
  0,     // XC_RefWord_e

  TV_MAIN_SGM_CTBL,    // XC_RefNum
  0,     // XC_RefNum_e

  TV_MAIN_SGM_CTBL,    // XC_RefXWord
  0,     // XC_RefXWord_e

  TV_MAIN_SGM_CTBL,    // XC_RefTab
  0,     // XC_RefTab_e

  TV_MAIN_SGM_CTBL,    // XC_RefPage
  0,     // XC_RefPage_e

  TV_MAIN_SGM_CTBL,    // XC_RefHom
  0,     // XC_RefHom_e

  TV_MAIN_SGM_CTBL,    // XC_SingleCpdWord
  0,     // XC_SingleCpdWord_e

  TV_MAIN_SGM_CTBL,    // XC_FormGroupDst
  0,     // XC_FormGroupDst_e

  TV_MAIN_SGM_CTBL,    // XC_DerivGroup
  0,     // XC_DerivGroup_e

  TV_MAIN_SGM_CTBL,    // XC_Derivative
  0,     // XC_Derivative_e

  TV_MAIN_SGM_CTBL,    // XC_StressParGroup
  0,     // XC_StressParGroup_e

  TV_MAIN_SGM_CTBL,    // XC_StressPar
  0,     // XC_StressPar_e

  TV_MAIN_SGM_CTBL,    // XC_PunctMark
  0,     // XC_PunctMark_e

  KPT_UpCodeTable,     // XC_LevelGroup
  0,     // XC_LevelGroup_e

  TV_MAIN_SGM_CTBL,    // XC_Level
  0,     // XC_Level_e

  TV_MAIN_SGM_CTBL,    // XC_UsNoteSrc,
  0,     // XC_UsNoteSrc_e,

  0,     // XC_Img,
  0,     // XC_Img_e,

  0,     // XC_RefSecSynGr
  0,     // XC_RefSecSynGr_e
  TV_MAIN_SGM_CTBL,    // XC_RefSecSyn
  0,     // XC_RefSecSyn_e

  0,     // XC_RefPriSynGr
  0,     // XC_RefPriSynGr_e
  TV_MAIN_SGM_CTBL,    // XC_RefPriSyn
  0,     // XC_RefPriSyn_e

  0,     // XC_RefSynGr
  0,     // XC_RefSynGr_e
  TV_MAIN_SGM_CTBL,    // XC_RefSyn
  0,     // XC_RefSyn_e

  0,     // XC_RefExamplGr
  0,     // XC_RefExamplGr_e
  TV_MAIN_SGM_CTBL,    // XC_RefExampl
  0,     // XC_RefExampl_e

  0,     // XC_RefAntGr
  0,     // XC_RefAntGr_e
  TV_MAIN_SGM_CTBL,    // XC_RefAnt
  0,     // XC_RefAnt_e

  0,     // XC_RefExamplSinglGr
  0,     // XC_RefExamplSinglGr_e

  TV_MAIN_SGM_CTBL,    // XC_Subscript
  0,     // XC_Subscript_e

  TV_MAIN_SGM_CTBL,    // XC_CodeExampleInline
  0,     // XC_CodeExampleInline_e

  0,     // XC_EnumGr
  0,     // XC_EnumGr_e

  TV_MAIN_SGM_CTBL,    // XC_Enum
  0,     // XC_Enum_e

  TV_MAIN_SGM_CTBL,    // XC_CodeBaseWord
  0,     // XC_CodeBaseWord_e

  TV_MAIN_SGM_CTBL,    // XC_CodeExample
  0,     // XC_CodeExample_e

  0,     // XC_Table
  0,     // XC_Table_e
  0,     // XC_TableRow
  0,     // XC_TableRow_e
  TV_MAIN_SGM_CTBL,    // XC_TableCell
  0,     // XC_TableCell_e

  0,     // XC_Equiation
  0,     // XC_Equiation_e

  0,     // XC_Break
  0,     // XC_Break_e

  1,     // XC_EquInline
  0,     // XC_EquInline_e

  0,     // XC_Special
  0,     // XC_Special_e

  0,     // XC_ExampleGroupForced
  0,     // XC_ExampleGroupForced_e

  TV_MAIN_SGM_CTBL,    // XC_ExplForced
  0,     // XC_ExplForced_e

  0,     // XC_VarGroup
  0,     // XC_VarGroup_e

  0,     // XC_Relatives
  0,     // XC_Relatives_e

  TV_MAIN_SGM_CTBL,    // XC_Page
  0,                   // XC_Page_e

  TV_MAIN_SGM_CTBL,    // XC_SemNr
  0,                   // XC_SemNr_e

  TV_MAIN_SGM_CTBL,    // XC_TrWordLit
  0,                   // XC_TrWordLit_e

  TV_MAIN_SGM_CTBL,    // XC_TrWordEng
  0,                   // XC_TrWordEng_e

  TV_MAIN_SGM_CTBL,    // XC_TrWordGer
  0,                   // XC_TrWordGer_e

  TV_MAIN_SGM_CTBL,    // XC_TrWordFre
  0,                   // XC_TrWordFre_e

  TV_MAIN_SGM_CTBL,    // XC_TrWordPol
  0,                   // XC_TrWordPol_e

  TV_MAIN_SGM_CTBL,    // XC_TrWordRus
  0,                   // XC_TrWordRus_e

  TV_MAIN_SGM_CTBL,    // XC_VarNorm,
  0,     // XC_VarNorm_e,

  0,     // XC_StructGroupForced
  0,     // XC_StructGroupForced_e

  TV_MAIN_SGM_CTBL,    // XC_VarBold
  0,     // XC_VarBold_e

  0,                   // XC_RefAntStrictGr
  0,                   // XC_RefAntStrictGr_e
  TV_MAIN_SGM_CTBL,    // XC_RefAntStrict
  0,                   // XC_RefAntStrict_e

};

