// ==================================================
// tvxmltt.cpp, sena versija del vlz 2001.11
// XML dictionary file tags
// main tvxml format


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kperr.h"

#include "tvmain.h"
#include "kpttucf.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlo1.h"
#include "xmlt.h"


// --------------------------------------------------
const unsigned char *plpszaXmlttDictTags[XC_TG_NumOfDictTagsArr39+1] = // Dictionary XML tag names (native)
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
  (unsigned char *)"<un>",                      // XC_UsNote,
  (unsigned char *)"</un>",                     // XC_UsNote_e,
  (unsigned char *)"<xr>",                      // XC_Reference,
//                 "<xr href=\"%s#%ld\">" // TV_XM_HrefDelim // TV_HTM_HrefDelim
  (unsigned char *)"</xr>",                     // XC_Reference_e,  space after not allowed - may be in free text
  (unsigned char *)"<st>",                      // XC_StEntryText,
  (unsigned char *)"</st>",                     // XC_StEntryText_e,
  
  (unsigned char *)"<p>",                       // XC_Paragraph,
  (unsigned char *)"</p>",                      // XC_Paragraph_e,  space after not allowed - may be in free text
  
                   XM_Version_STR,              // XC_Version,
                // "<?xml ?>\n",
                // "<?xml version=\'1.0\' encoding=\"UTF-8\" ?>\n",
                // "<?XML VERSION=\"1.0\" RMD=\"ALL\" ?>\n",
                // "<?XML ENCODING=\"UTF-8\" ?>\n",
  (unsigned char *)"",                          // XC_Version_e,

                   XM_DOCTYPE_STR,              // XC_DocType,
                // "<!DOCTYPE di SYSTEM>\n",
                // "<!DOCTYPE di SYSTEM \"%s\">\n",
  (unsigned char *)"",                          // XC_DocType_e,
  
  (unsigned char *)"<v>",                       // XC_Variant,
  (unsigned char *)"</v> ",                     // XC_Variant_e,

  (unsigned char *)"<ps>",                      // XC_PartOfSpeechSrc,
  (unsigned char *)"</ps> ",                    // XC_PartOfSpeechSrc_e,

  (unsigned char *)"<hg>",                      // XC_HeadWordGroup,
  (unsigned char *)"</hg>\n",                   // XC_HeadWordGroup_e,
  (unsigned char *)"<tg>",                      // XC_TranslGroup,
  (unsigned char *)"</tg>\n",                   // XC_TranslGroup_e,

  (unsigned char *)"<f>",                       // XC_FormDst,
  (unsigned char *)"</f>",                      // XC_FormDst_e,  space after not allowed - may be in parentheses
  (unsigned char *)"<fs>",                      // XC_FormSrc,
  (unsigned char *)"</fs>",                     // XC_FormSrc_e,  space after not allowed - may be in parentheses

  (unsigned char *)"<ic>",                      // XC_ExplSrc,
  (unsigned char *)"</ic>",                     // XC_ExplSrc_e,  space after not allowed - may be in free text

  (unsigned char *)"<le>",                      // XC_Example,
  (unsigned char *)"</le> ",                    // XC_Example_e,
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

  (unsigned char *)"<bhw>",   // "<base>",      // XC_Base,
  (unsigned char *)"</bhw> ", // "</base> ",    // XC_Base_e,
  (unsigned char *)"<cg>",                      // XC_CompoundGroup,
  (unsigned char *)"</cg>\n",                   // XC_CompoundGroup_e,
  (unsigned char *)"<scw>",    // "<lc>",       // XC_CompoundWord,
  (unsigned char *)"</scw> ",  // "</lc> ",     // XC_CompoundWord_e,

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

                   XM_Stylesheet_STR,           // XC_StyleSheet,
                // "<?xml-stylesheet ?>\n",
                // "<?xml-stylesheet href=\"%s\" type=\"text/css\" ?>\n",
  (unsigned char *)"",                          // XC_StyleSheet_e,

  (unsigned char *)"<vn>",                      // XC_VarNorm,
  (unsigned char *)"</vn> ",                    // XC_VarNorm_e,

  (unsigned char *)"<cn>",                      // XC_AbbrNorm,
  (unsigned char *)"</cn>",                     // XC_AbbrNorm_e,  space after not allowed - may be in free text

  (unsigned char *)"<s3>",                      // XC_MngNearGroup
//                 "<s3 num=\"%s\">",
  (unsigned char *)"</s3>\n",                   // XC_MngNearGroup_e

  (unsigned char *)"<pd>",                      // XC_PronRed
  (unsigned char *)"</pd>",                     // XC_PronRed_e

  (unsigned char *)"",                          // XC_Nul
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

  (unsigned char *)"",                          // XC_Symb
  (unsigned char *)"",                          // XC_Symb_e

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

  NULL
};


// --------------------------------------------------
const unsigned char *plpszaXmlttDictTagsFull[XC_TG_NumOfDictTagsArr39+1] = // Dictionary XML tag names with sgml Tage tags
{
  (unsigned char *)"<di>\n\n",
                // "<di name=\"%s\">\n\n",
                                                // XC_Dict
  (unsigned char *)"</di>\n",                   // XC_Dict_e,

  (unsigned char *)"<ue> ",                     // XC_NrtEntry,
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
  (unsigned char *)"<un> ",                     // XC_UsNote,
  (unsigned char *)"</un>",                     // XC_UsNote_e,
  (unsigned char *)"<xr>",                      // XC_Reference,
//                 "<xr href=\"%s#%ld\">" // TV_XM_HrefDelim // TV_HTM_HrefDelim
  (unsigned char *)"</xr>",                     // XC_Reference_e,  space after not allowed - may be in free text
  (unsigned char *)"<st>",                      // XC_StEntryText,
  (unsigned char *)"</st>",                     // XC_StEntryText_e,

  (unsigned char *)"<p>",                       // XC_Paragraph,
  (unsigned char *)"</p>",                      // XC_Paragraph_e,  space after not allowed - may be in free text

                   XM_Version_STR,              // XC_Version,
                // "<?xml ?>\n",
                // "<?xml version=\'1.0\' encoding=\"UTF-8\" ?>\n",
                // "<?XML VERSION=\"1.0\" RMD=\"ALL\" ?>\n",
                // "<?XML ENCODING=\"UTF-8\" ?>\n",
  (unsigned char *)"",                          // XC_Version_e,

                   XM_DOCTYPE_STR,              // XC_DocType,
                // "<!DOCTYPE di SYSTEM>\n",
                // "<!DOCTYPE di SYSTEM \"%s\">\n",
  (unsigned char *)"",                          // XC_DocType_e,

  (unsigned char *)"<v>",                       // XC_Variant,
  (unsigned char *)"</v> ",                     // XC_Variant_e,

  (unsigned char *)"<ps>",                      // XC_PartOfSpeechSrc,
  (unsigned char *)"</ps> ",                    // XC_PartOfSpeechSrc_e,

  (unsigned char *)"<hg>",                      // XC_HeadWordGroup,
  (unsigned char *)"</hg>\n",                   // XC_HeadWordGroup_e,
  (unsigned char *)"<tg>",                      // XC_TranslGroup,
  (unsigned char *)"</tg>\n",                   // XC_TranslGroup_e,

  (unsigned char *)"<f>",                       // XC_FormDst,
  (unsigned char *)"</f>",                      // XC_FormDst_e,  space after not allowed - may be in parentheses
  (unsigned char *)"<fs>",                      // XC_FormSrc,
  (unsigned char *)"</fs>",                     // XC_FormSrc_e,  space after not allowed - may be in parentheses

  (unsigned char *)"<ic>",                      // XC_ExplSrc,
  (unsigned char *)"</ic>",                     // XC_ExplSrc_e,  space after not allowed - may be in free text

  (unsigned char *)"<le>",                      // XC_Example,
  (unsigned char *)"</le> ",                    // XC_Example_e,
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

  (unsigned char *)"<bhw>",    // "<base>",     // XC_Base,
  (unsigned char *)"</bhw> ",  // "</base> ",   // XC_Base_e,
  (unsigned char *)"<cg>",                      // XC_CompoundGroup,
  (unsigned char *)"</cg>\n",                   // XC_CompoundGroup_e,
  (unsigned char *)"<scw>",    // "<lc>",       // XC_CompoundWord,
  (unsigned char *)"</scw> ",  // "</lc> ",     // XC_CompoundWord_e,

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

                   XM_Stylesheet_STR,           // XC_StyleSheet,
                // "<?xml-stylesheet ?>\n",
                // "<?xml-stylesheet href=\"%s\" type=\"text/css\" ?>\n",
  (unsigned char *)"",                          // XC_StyleSheet_e,

  (unsigned char *)"<vn>",                      // XC_VarNorm,
  (unsigned char *)"</vn> ",                    // XC_VarNorm_e,

  (unsigned char *)"<cn>",                      // XC_AbbrNorm,
  (unsigned char *)"</cn>",                     // XC_AbbrNorm_e,  space after not allowed - may be in free text

  (unsigned char *)"<s3>",                      // XC_MngNearGroup
//                 "<s3 num=\"%s\">",
  (unsigned char *)"</s3>\n",                   // XC_MngNearGroup_e

  (unsigned char *)"<pd>",                      // XC_PronRed
  (unsigned char *)"</pd>",                     // XC_PronRed_e

  (unsigned char *)"",                          // XC_Nul
  (unsigned char *)"",                          // XC_Nul_e

  (unsigned char *)"<sim/>",                    // XC_Similar
  (unsigned char *)"",                          // XC_Similar_e

  (unsigned char *)"<apr/>",                    // XC_Approx
  (unsigned char *)"",                          // XC_Approx_e

  (unsigned char *)"<!!!text>",                 // XC_Text
  (unsigned char *)"</!!!text>",                // XC_Text_e

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

  (unsigned char *)"", // "<!!!symb>",          // XC_Symb
  (unsigned char *)"", // "</!!!symb>",         // XC_Symb_e

  (unsigned char *)"<if/>",                     // XC_Inform
  (unsigned char *)"",                          // XC_Inform_e
  (unsigned char *)"<uc/>",                     // XC_Uncount
  (unsigned char *)"",                          // XC_Uncount_e

  (unsigned char *)"<pvp>",                     // XC_PhrGroup
  (unsigned char *)"</pvp>",                    // XC_PhrGroup_e

  (unsigned char *)"<!!!s2>",                   // XC_CpdMngGroup
  (unsigned char *)"</!!!s2>",                  // XC_CpdMngGroup_e

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

  (unsigned char *)"<!!!s2>",                   // XC_IdMngGroup
  (unsigned char *)"</!!!s2>",                  // XC_IdMngGroup_e

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

  NULL
};


// --------------------------------------------------
HRESULT XmlttTestPars(int iChar, XmlTagPars_tag *pTagParsObj)
{
HRESULT retc=S_OK;
int par_cnt;
unsigned char *par_val=NULL;
int par_num;
const unsigned char *test_str;

   KP_NEWA(par_val, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

   if(SUCCEEDED(retc)) switch(iChar)
   {
   case XC_Version:
   case XC_DocType:
   case XC_StyleSheet:
      break;

   case XC_Dict:
      if((pTagParsObj==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

      if((par_cnt!=1)  && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         test_str=(unsigned char *)"name";
         retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
         if(((par_num!=0) || (strlen(par_val)==0)) && SUCCEEDED(retc))
             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      break;

   case XC_StEntry:
      if((pTagParsObj==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

      if((par_cnt!=1)  && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         test_str=(unsigned char *)"id";
         retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
         if(((par_num!=0) || (strlen(par_val)==0) || (!TvIsNumber(par_val))) && SUCCEEDED(retc))
             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      break;

   case XC_CtgGroup:
      if((pTagParsObj==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

      if((par_cnt!=1)  && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         test_str=(unsigned char *)"num";
         retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
         if(((par_num!=0) || (strlen(par_val)==0) || (!TvIsRomanNumber(par_val))) && SUCCEEDED(retc))
             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      break;

   case XC_MngGroup:
      if((pTagParsObj==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

      if((par_cnt!=1)  && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         test_str=(unsigned char *)"num";
         retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
         if(((par_num!=0) || (strlen(par_val)==0) || (!TvIsNumber(par_val))) && SUCCEEDED(retc))
             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      break;

   case XC_MngNearGroup:
      if((pTagParsObj==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

      if((par_cnt!=1)  && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         test_str=(unsigned char *)"num";
         retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
         if(((par_num!=0) || (strlen(par_val)==0) || (!TvIsLatinLowerStr(par_val))) && SUCCEEDED(retc))
             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      break;

   case XC_Reference:
      if((pTagParsObj==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

      if((par_cnt!=1)  && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         test_str=(unsigned char *)"href";
         retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
            retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, test_str, True, __FILE__, __LINE__, 0L);
         if(((par_num!=0) || (strlen(par_val)==0)) && SUCCEEDED(retc))
             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      break;

   default:
      if((iChar>=XC_FirstDictTag) && (iChar<XC_LastDictTag))
      {
         if(pTagParsObj!=NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      break;

   } // switch(iChar)

   KP_DELETE(par_val);

return(retc);
}
