// ==================================================
// htmt.cpp
// HTML tags


// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#include <time.h>
#include <richedit.h>
#include <Richole.h>
#endif
#include <string>

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpctype.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpwindow.h"
#include "kpstring.h"
#include "kperr.h"
#include "kpsort.h"
#include "tvmain.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "kpttucf.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"


// -------------------------------------------------
const unsigned char *plpszaHtmlTags[HTM_TG_NumOfTags37+1] =
{
  (unsigned char *)"<html>\n\n",          //   HTM_TG_HTML
  (unsigned char *)"</html>\n",           //   HTM_TG_HTML_e

  (unsigned char *)"<p>",                 //   HTM_TG_P
  (unsigned char *)"</p>\n",   // "</p>", //   HTM_TG_P_e

  (unsigned char *)"<span>",              //   HTM_TG_SPAN
  (unsigned char *)"</span>",             //   HTM_TG_SPAN_e

  (unsigned char *)"<head>\n",            //   HTM_TG_HEAD
  (unsigned char *)"</head>\n\n",         //   HTM_TG_HEAD_e

  (unsigned char *)"<title>",             //   HTM_TG_TITLE
  (unsigned char *)"</title>\n",          //   HTM_TG_TITLE_e

  (unsigned char *)"<meta/>\n",           //   HTM_TG_META
  (unsigned char *)"",                    //   HTM_TG_META_e

  (unsigned char *)"<style>\n",           //   HTM_TG_STYLE
  (unsigned char *)"</style>\n\n",        //   HTM_TG_STYLE_e

  (unsigned char *)"",                    //   HTM_TG_Comment
  (unsigned char *)"",                    //   HTM_TG_Comment_e

  (unsigned char *)"",                    //   HTM_TG_DOCTYPE
  (unsigned char *)"",                    //   HTM_TG_DOCTYPE_e

  (unsigned char *)"<script>\n",          //   HTM_TG_SCRIPT
  (unsigned char *)"</script>\n\n",       //   HTM_TG_SCRIPT_e

  (unsigned char *)"<body>\n",            //   HTM_TG_BODY
  (unsigned char *)"</body>\n\n",         //   HTM_TG_BODY_e

  (unsigned char *)"<link/>\n",           //   HTM_TG_LINK
  (unsigned char *)"",                    //   HTM_TG_LINK_e

  (unsigned char *)"<sup>",               //   HTM_TG_SUP
  (unsigned char *)"</sup>",              //   HTM_TG_SUP_e

  (unsigned char *)"<a>",                 //   HTM_TG_A
  (unsigned char *)"</a>",                //   HTM_TG_A_e

  (unsigned char *)"<table>\n",           //   HTM_TG_TABLE
  (unsigned char *)"</table>\n",          //   HTM_TG_TABLE_e
  (unsigned char *)"<tr>\n",              //   HTM_TG_TR
  (unsigned char *)"</tr>\n",             //   HTM_TG_TR_e
  (unsigned char *)"<td>",                //   HTM_TG_TD
  (unsigned char *)"</td>\n",             //   HTM_TG_TD_e

  (unsigned char *)"<br/>\n",             //   HTM_TG_BR
  (unsigned char *)"",                    //   HTM_TG_BR_e

  (unsigned char *)"<tbody>\n",           //   HTM_TG_TBODY
  (unsigned char *)"</tbody>\n",          //   HTM_TG_TBODY_e

  (unsigned char *)"<img/>",              //   HTM_TG_IMG
  (unsigned char *)"",                    //   HTM_TG_IMG_e

  (unsigned char *)"<th>",                //   HTM_TG_TH
  (unsigned char *)"</th>\n",             //   HTM_TG_TH_e

  (unsigned char *)"<nobr>",              //   HTM_TG_NOBR
  (unsigned char *)"</nobr>",             //   HTM_TG_NOBR_e

  (unsigned char *)"<b>",                 //   HTM_TG_B
  (unsigned char *)"</b>",                //   HTM_TG_B_e

  (unsigned char *)"<div>",               //   HTM_TG_DIV
  (unsigned char *)"</div>",              //   HTM_TG_DIV_e

  (unsigned char *)"<pre>",               //   HTM_TG_PRE
  (unsigned char *)"</pre>",              //   HTM_TG_PRE_e

  (unsigned char *)"<font>",              //   HTM_TG_FONT
  (unsigned char *)"</font>",             //   HTM_TG_FONT_e

  (unsigned char *)"<i>",                 //   HTM_TG_I
  (unsigned char *)"</i>",                //   HTM_TG_I_e

  (unsigned char *)"<sub>",               //   HTM_TG_SUB
  (unsigned char *)"</sub>",              //   HTM_TG_SUB_e

  (unsigned char *)"<tt>",                //   HTM_TG_TT
  (unsigned char *)"</tt>",               //   HTM_TG_TT_e

  (unsigned char *)"<hr/>",               //   HTM_TG_HR
  (unsigned char *)"",                    //   HTM_TG_HR_e

  (unsigned char *)"<ul>",                //   HTM_TG_UL
  (unsigned char *)"</ul>",               //   HTM_TG_UL_e

  (unsigned char *)"<li>",                //   HTM_TG_LI
  (unsigned char *)"</li>",               //   HTM_TG_LI_e

  (unsigned char *)"<center>",            //   HTM_TG_CENTER
  (unsigned char *)"</center>",           //   HTM_TG_CENTER_e

  (unsigned char *)"<caption>",           //   HTM_TG_CAPTION
  (unsigned char *)"</caption>",          //   HTM_TG_CAPTION_e

  (unsigned char *)"<samp>",              //   HTM_TG_SAMP
  (unsigned char *)"</samp>",             //   HTM_TG_SAMP_e

  (unsigned char *)"<big>",               //   HTM_TG_BIG
  (unsigned char *)"</big>",              //   HTM_TG_BIG_e

  (unsigned char *)"<form>\n",            //   HTM_TG_FORM
  (unsigned char *)"</form>\n",           //   HTM_TG_FORM_e

  (unsigned char *)"<input/>\n",          //   HTM_TG_INPUT
  (unsigned char *)"",                    //   HTM_TG_INPUT_e

  (unsigned char *)"<object>", // "<object/>", //   HTM_TG_OBJECT
  (unsigned char *)"</object>", // "",    //   HTM_TG_OBJECT_e

  (unsigned char *)"<embed>", // "<embed/>", //   HTM_TG_EMBED
  (unsigned char *)"</embed>", // "",     //   HTM_TG_EMBED_e

  (unsigned char *)"<iframe>",            //   HTM_TG_IFRAME
  (unsigned char *)"</iframe>",           //   HTM_TG_IFRAME_e

  (unsigned char *)"<marquee>",           //   HTM_TG_MARQUEE
  (unsigned char *)"</marquee>",          //   HTM_TG_MARQUEE_e

  (unsigned char *)"<code>",              //   HTM_TG_CODE
  (unsigned char *)"</code>",             //   HTM_TG_CODE_e

  (unsigned char *)"<ol>",                //   HTM_TG_OL
  (unsigned char *)"</ol>",               //   HTM_TG_OL_e

  (unsigned char *)"<h1>",                //   HTM_TG_H1
  (unsigned char *)"</h1>",               //   HTM_TG_H1_e

  (unsigned char *)"<h2>",                //   HTM_TG_H2
  (unsigned char *)"</h2>",               //   HTM_TG_H2_e

  (unsigned char *)"<h3>",                //   HTM_TG_H3
  (unsigned char *)"</h3>",               //   HTM_TG_H3_e

  (unsigned char *)"<h4>",                //   HTM_TG_H4
  (unsigned char *)"</h4>",               //   HTM_TG_H4_e

  (unsigned char *)"<h5>",                //   HTM_TG_H5
  (unsigned char *)"</h5>",               //   HTM_TG_H5_e

  (unsigned char *)"<h6>",                //   HTM_TG_H6
  (unsigned char *)"</h6>",               //   HTM_TG_H6_e

// MS Word HTML
  (unsigned char *)"<xml>",               //   HTM_TG_xml
  (unsigned char *)"</xml>",              //   HTM_TG_xml_e

  (unsigned char *)"<o:DocumentProperties>",    //   HTM_TG_o_DocumentProperties
  (unsigned char *)"</o:DocumentProperties>",   //   HTM_TG_o_DocumentProperties_e

  (unsigned char *)"<o:Author>",          //   HTM_TG_o_Author
  (unsigned char *)"</o:Author>",         //   HTM_TG_o_Author_e

  (unsigned char *)"<o:LastAuthor>",      //   HTM_TG_o_LastAuthor
  (unsigned char *)"</o:LastAuthor>",     //   HTM_TG_o_LastAuthor_e

  (unsigned char *)"<o:Revision>",        //   HTM_TG_o_Revision
  (unsigned char *)"</o:Revision>",       //   HTM_TG_o_Revision_e

  (unsigned char *)"<o:TotalTime>",       //   HTM_TG_o_TotalTime
  (unsigned char *)"</o:TotalTime>",      //   HTM_TG_o_TotalTime_e

  (unsigned char *)"<o:Created>",         //   HTM_TG_o_Created
  (unsigned char *)"</o:Created>",        //   HTM_TG_o_Created_e

  (unsigned char *)"<o:LastSaved>",       //   HTM_TG_o_LastSaved
  (unsigned char *)"</o:LastSaved>",      //   HTM_TG_o_LastSaved_e

  (unsigned char *)"<o:Pages>",           //   HTM_TG_o_Pages
  (unsigned char *)"</o:Pages>",          //   HTM_TG_o_Pages_e

  (unsigned char *)"<o:Characters>",      //   HTM_TG_o_Characters
  (unsigned char *)"</o:Characters>",     //   HTM_TG_o_Characters_e

  (unsigned char *)"<o:Company>",         //   HTM_TG_o_Company
  (unsigned char *)"</o:Company>",        //   HTM_TG_o_Company_e

  (unsigned char *)"<o:Lines>",           //   HTM_TG_o_Lines
  (unsigned char *)"</o:Lines>",          //   HTM_TG_o_Lines_e

  (unsigned char *)"<o:Paragraphs>",      //   HTM_TG_o_Paragraphs
  (unsigned char *)"</o:Paragraphs>",     //   HTM_TG_o_Paragraphs_e

  (unsigned char *)"<o:CharactersWithSpaces>",  //   HTM_TG_o_CharactersWithSpaces
  (unsigned char *)"</o:CharactersWithSpaces>", //   HTM_TG_o_CharactersWithSpaces_e

  (unsigned char *)"<o:Version>",         //   HTM_TG_o_Version
  (unsigned char *)"</o:Version>",        //   HTM_TG_o_Version_e


  (unsigned char *)"<o:shapedefaults>",   //   HTM_TG_o_shapedefaults
  (unsigned char *)"</o:shapedefaults>",  //   HTM_TG_o_shapedefaults_e

  (unsigned char *)"<o:colormenu/>",      //   HTM_TG_o_colormenu
  (unsigned char *)"",                    //   HTM_TG_o_colormenu_e

  (unsigned char *)"<o:shapelayout>",     //   HTM_TG_o_shapelayout
  (unsigned char *)"</o:shapelayout>",    //   HTM_TG_o_shapelayout_e

  (unsigned char *)"<o:idmap/>",          //   HTM_TG_o_idmap
  (unsigned char *)"",                    //   HTM_TG_o_idmap_e


  (unsigned char *)"<v:background>",      //   HTM_TG_v_background
  (unsigned char *)"</v:background>",     //   HTM_TG_v_background_e

  (unsigned char *)"<v:fill/>",           //   HTM_TG_v_fill
  (unsigned char *)"",                    //   HTM_TG_v_fill_e

  (unsigned char *)"<v:shapetype>",       //   HTM_TG_v_shapetype
  (unsigned char *)"</v:shapetype>",      //   HTM_TG_v_shapetype_e

  (unsigned char *)"<v:stroke/>",         //   HTM_TG_v_stroke
  (unsigned char *)"",                    //   HTM_TG_v_stroke_e

  (unsigned char *)"<v:path/>",           //   HTM_TG_v_path
  (unsigned char *)"",                    //   HTM_TG_v_path_e

  (unsigned char *)"<v:shape>",           //   HTM_TG_v_shape // "<v:shape/>"
  (unsigned char *)"</v:shape>",          //   HTM_TG_v_shape_e

  (unsigned char *)"<w:wrap/>",           //   HTM_TG_w_wrap
  (unsigned char *)"",                    //   HTM_TG_w_wrap_e

  (unsigned char *)"<v:textbox>",         //   HTM_TG_v_textbox
  (unsigned char *)"</v:textbox>",        //   HTM_TG_v_textbox_e

  (unsigned char *)"<o:p>",               //   HTM_TG_o_p
  (unsigned char *)"</o:p>",              //   HTM_TG_o_p_e

  (unsigned char *)"<v:formulas>",        //   HTM_TG_v_formulas
  (unsigned char *)"</v:formulas>",       //   HTM_TG_v_formulas_e

  (unsigned char *)"<v:f/>",              //   HTM_TG_v_f
  (unsigned char *)"",                    //   HTM_TG_v_f_e

  (unsigned char *)"<o:lock/>",           //   HTM_TG_o_lock
  (unsigned char *)"",                    //   HTM_TG_o_lock_e

  (unsigned char *)"<v:imagedata/>",      //   HTM_TG_v_imagedata
  (unsigned char *)"",                    //   HTM_TG_v_imagedata_e

  (unsigned char *)"<v:line>",            //   HTM_TG_v_line
  (unsigned char *)"</v:line>",           //   HTM_TG_v_line_e

  (unsigned char *)"<v:oval/>",           //   HTM_TG_v_oval
  (unsigned char *)"",                    //   HTM_TG_v_oval_e

  (unsigned char *)"<w:WordDocument>",    //   HTM_TG_w_WordDocument
  (unsigned char *)"</w:WordDocument>",   //   HTM_TG_w_WordDocument_e

  (unsigned char *)"<w:FormsDesign/>",    //   HTM_TG_w_FormsDesign
  (unsigned char *)"",                    //   HTM_TG_w_FormsDesign_e

  (unsigned char *)"<o:Words>",           //   HTM_TG_o_Words
  (unsigned char *)"</o:Words>",          //   HTM_TG_o_Words_e

  (unsigned char *)"<w:ValidateAgainstSchemas/>",           //   HTM_TG_w_ValidateAgainstSchemas
  (unsigned char *)"",                                      //   HTM_TG_w_ValidateAgainstSchemas_e

  (unsigned char *)"<w:SaveIfXMLInvalid>",                  //   HTM_TG_w_SaveIfXMLInvalid
  (unsigned char *)"</w:SaveIfXMLInvalid>",                 //   HTM_TG_w_SaveIfXMLInvalid_e

  (unsigned char *)"<w:IgnoreMixedContent>",                //   HTM_TG_w_IgnoreMixedContent
  (unsigned char *)"</w:IgnoreMixedContent>",               //   HTM_TG_w_IgnoreMixedContent_e

  (unsigned char *)"<w:AlwaysShowPlaceholderText>",         //   HTM_TG_w_AlwaysShowPlaceholderText
  (unsigned char *)"</w:AlwaysShowPlaceholderText>",        //   HTM_TG_w_AlwaysShowPlaceholderText_e

  (unsigned char *)"<w:Compatibility>",                     //   HTM_TG_w_Compatibility
  (unsigned char *)"</w:Compatibility>",                    //   HTM_TG_w_Compatibility_e

  (unsigned char *)"<w:SelectEntireFieldWithStartOrEnd/>",  //   HTM_TG_w_SelectEntireFieldWithStartOrEnd
  (unsigned char *)"",                                      //   HTM_TG_w_SelectEntireFieldWithStartOrEnd_e

  (unsigned char *)"<w:UseWord2002TableStyleRules/>",       //   HTM_TG_w_UseWord2002TableStyleRules
  (unsigned char *)"",                                      //   HTM_TG_w_UseWord2002TableStyleRules_e

  (unsigned char *)"<w:BrowserLevel>",                      //   HTM_TG_w_BrowserLevel
  (unsigned char *)"</w:BrowserLevel>",                     //   HTM_TG_w_BrowserLevel_e

  (unsigned char *)"<w:LatentStyles>",                      //   HTM_TG_w_LatentStyles
  (unsigned char *)"</w:LatentStyles>",                     //   HTM_TG_w_LatentStyles_e

  (unsigned char *)"<w:SpellingState>",                     //   HTM_TG_w_SpellingState
  (unsigned char *)"</w:SpellingState>",                    //   HTM_TG_w_SpellingState_e

  (unsigned char *)"<w:GrammarState>",                      //   HTM_TG_w_GrammarState
  (unsigned char *)"</w:GrammarState>",                     //   HTM_TG_w_GrammarState_e

// HTML
   (unsigned char *)"<thead>",            //   HTM_TG_THEAD
   (unsigned char *)"</thead>",           //   HTM_TG_THEAD_e

   (unsigned char *)"<tfoot>",            //   HTM_TG_TFOOT
   (unsigned char *)"</tfoot>",           //   HTM_TG_TFOOT_e

// FlashPageFlip.com
   (unsigned char *)"<noscript>",         //   HTM_TG_NOSCRIPT
   (unsigned char *)"</noscript>",        //   HTM_TG_NOSCRIPT_e

   (unsigned char *)"<param/>",           //   HTM_TG_PARAM
   (unsigned char *)"",                   //   HTM_TG_PARAM_e

  NULL
};


const int iaHtmNulCodeTables[HTM_TG_NumOfTags37] = // HTML Unicode file fictive code tables
{
  KPT_NoCodeTable, //           //   HTM_TG_HTML
  KPT_NoCodeTable, //           //   HTM_TG_HTML_e

  KPT_NoCodeTable, //           //   HTM_TG_P
  KPT_NoCodeTable, //           //   HTM_TG_P_e

  KPT_NoCodeTable, //           //   HTM_TG_SPAN
  KPT_NoCodeTable, //           //   HTM_TG_SPAN_e

  KPT_NoCodeTable, //           //   HTM_TG_HEAD
  KPT_NoCodeTable, //           //   HTM_TG_HEAD_e

  KPT_NoCodeTable, //           //   HTM_TG_TITLE
  KPT_NoCodeTable, //           //   HTM_TG_TITLE_e

  KPT_NoCodeTable, //           //   HTM_TG_META
  KPT_NoCodeTable, //           //   HTM_TG_META_e

  KPT_NoCodeTable, //           //   HTM_TG_STYLE
  KPT_NoCodeTable, //           //   HTM_TG_STYLE_e

  KPT_NoCodeTable, //           //   HTM_TG_Comment
  KPT_NoCodeTable, //           //   HTM_TG_Comment_e

  KPT_NoCodeTable, //           //   HTM_TG_DOCTYPE
  KPT_NoCodeTable, //           //   HTM_TG_DOCTYPE_e

  KPT_NoCodeTable, //           //   HTM_TG_SCRIPT
  KPT_NoCodeTable, //           //   HTM_TG_SCRIPT_e

  KPT_NoCodeTable, //           //   HTM_TG_BODY
  KPT_NoCodeTable, //           //   HTM_TG_BODY_e

  KPT_NoCodeTable, //           //   HTM_TG_LINK
  KPT_NoCodeTable, //           //   HTM_TG_LINK_e

  KPT_NoCodeTable, //           //   HTM_TG_SUP
  KPT_NoCodeTable, //           //   HTM_TG_SUP_e

  KPT_NoCodeTable, //           //   HTM_TG_A
  KPT_NoCodeTable, //           //   HTM_TG_A_e

  KPT_NoCodeTable, //           //   HTM_TG_TABLE
  KPT_NoCodeTable, //           //   HTM_TG_TABLE_e
  KPT_NoCodeTable, //           //   HTM_TG_TR
  KPT_NoCodeTable, //           //   HTM_TG_TR_e
  KPT_NoCodeTable, //           //   HTM_TG_TD
  KPT_NoCodeTable, //           //   HTM_TG_TD_e

  KPT_NoCodeTable, //           //   HTM_TG_BR
  KPT_NoCodeTable, //           //   HTM_TG_BR_e

  KPT_NoCodeTable, //           //   HTM_TG_TBODY
  KPT_NoCodeTable, //           //   HTM_TG_TBODY_e

  KPT_NoCodeTable, //           //   HTM_TG_IMG
  KPT_NoCodeTable, //           //   HTM_TG_IMG_e

  KPT_NoCodeTable, //           //   HTM_TG_TH
  KPT_NoCodeTable, //           //   HTM_TG_TH_e

  KPT_NoCodeTable, //           //   HTM_TG_NOBR
  KPT_NoCodeTable, //           //   HTM_TG_NOBR_e

  KPT_NoCodeTable, //           //   HTM_TG_B
  KPT_NoCodeTable, //           //   HTM_TG_B_e

  KPT_NoCodeTable, //           //   HTM_TG_DIV
  KPT_NoCodeTable, //           //   HTM_TG_DIV_e

  KPT_NoCodeTable, //           //   HTM_TG_PRE
  KPT_NoCodeTable, //           //   HTM_TG_PRE_e

  KPT_NoCodeTable, //           //   HTM_TG_FONT
  KPT_NoCodeTable, //           //   HTM_TG_FONT_e

  KPT_NoCodeTable, //           //   HTM_TG_I
  KPT_NoCodeTable, //           //   HTM_TG_I_e

  KPT_NoCodeTable, //           //   HTM_TG_SUB
  KPT_NoCodeTable, //           //   HTM_TG_SUB_e

  KPT_NoCodeTable, //           //   HTM_TG_TT
  KPT_NoCodeTable, //           //   HTM_TG_TT_e

  KPT_NoCodeTable, //           //   HTM_TG_HR
  KPT_NoCodeTable, //           //   HTM_TG_HR_e

  KPT_NoCodeTable, //           //   HTM_TG_UL
  KPT_NoCodeTable, //           //   HTM_TG_UL_e

  KPT_NoCodeTable, //           //   HTM_TG_LI
  KPT_NoCodeTable, //           //   HTM_TG_LI_e

  KPT_NoCodeTable, //           //   HTM_TG_CENTER
  KPT_NoCodeTable, //           //   HTM_TG_CENTER_e

  KPT_NoCodeTable, //           //   HTM_TG_CAPTION
  KPT_NoCodeTable, //           //   HTM_TG_CAPTION_e

  KPT_NoCodeTable, //           //   HTM_TG_SAMP
  KPT_NoCodeTable, //           //   HTM_TG_SAMP_e

  KPT_NoCodeTable, //           //   HTM_TG_BIG
  KPT_NoCodeTable, //           //   HTM_TG_BIG_e

  KPT_NoCodeTable, //           //   HTM_TG_FORM
  KPT_NoCodeTable, //           //   HTM_TG_FORM_e

  KPT_NoCodeTable, //           //   HTM_TG_INPUT
  KPT_NoCodeTable, //           //   HTM_TG_INPUT_e

  KPT_NoCodeTable, //           //   HTM_TG_OBJECT
  KPT_NoCodeTable, //           //   HTM_TG_OBJECT_e

  KPT_NoCodeTable, //           //   HTM_TG_EMBED
  KPT_NoCodeTable, //           //   HTM_TG_EMBED_e

  KPT_NoCodeTable, //           //   HTM_TG_IFRAME
  KPT_NoCodeTable, //           //   HTM_TG_IFRAME_e

  KPT_NoCodeTable, //           //   HTM_TG_MARQUEE
  KPT_NoCodeTable, //           //   HTM_TG_MARQUEE_e

  KPT_NoCodeTable, //           //   HTM_TG_CODE
  KPT_NoCodeTable, //           //   HTM_TG_CODE_e

  KPT_NoCodeTable, //           //   HTM_TG_OL
  KPT_NoCodeTable, //           //   HTM_TG_OL_e

  KPT_NoCodeTable, //           //   HTM_TG_H1
  KPT_NoCodeTable, //           //   HTM_TG_H1_e

  KPT_NoCodeTable, //           //   HTM_TG_H2
  KPT_NoCodeTable, //           //   HTM_TG_H2_e

  KPT_NoCodeTable, //           //   HTM_TG_H3
  KPT_NoCodeTable, //           //   HTM_TG_H3_e

  KPT_NoCodeTable, //           //   HTM_TG_H4
  KPT_NoCodeTable, //           //   HTM_TG_H4_e

  KPT_NoCodeTable, //           //   HTM_TG_H5
  KPT_NoCodeTable, //           //   HTM_TG_H5_e

  KPT_NoCodeTable, //           //   HTM_TG_H6
  KPT_NoCodeTable, //           //   HTM_TG_H6_e

// MS Word HTML
   KPT_NoCodeTable, //           //   HTM_TG_xml
   KPT_NoCodeTable, //           //   HTM_TG_xml_e

   KPT_NoCodeTable, //           //   HTM_TG_o_DocumentProperties
   KPT_NoCodeTable, //           //   HTM_TG_o_DocumentProperties_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Author
   KPT_NoCodeTable, //           //   HTM_TG_o_Author_e

   KPT_NoCodeTable, //           //   HTM_TG_o_LastAuthor
   KPT_NoCodeTable, //           //   HTM_TG_o_LastAuthor_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Revision
   KPT_NoCodeTable, //           //   HTM_TG_o_Revision_e

   KPT_NoCodeTable, //           //   HTM_TG_o_TotalTime
   KPT_NoCodeTable, //           //   HTM_TG_o_TotalTime_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Created
   KPT_NoCodeTable, //           //   HTM_TG_o_Created_e

   KPT_NoCodeTable, //           //   HTM_TG_o_LastSaved
   KPT_NoCodeTable, //           //   HTM_TG_o_LastSaved_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Pages
   KPT_NoCodeTable, //           //   HTM_TG_o_Pages_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Characters
   KPT_NoCodeTable, //           //   HTM_TG_o_Characters_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Company
   KPT_NoCodeTable, //           //   HTM_TG_o_Company_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Lines
   KPT_NoCodeTable, //           //   HTM_TG_o_Lines_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Paragraphs
   KPT_NoCodeTable, //           //   HTM_TG_o_Paragraphs_e

   KPT_NoCodeTable, //           //   HTM_TG_o_CharactersWithSpaces
   KPT_NoCodeTable, //           //   HTM_TG_o_CharactersWithSpaces_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Version
   KPT_NoCodeTable, //           //   HTM_TG_o_Version_e


   KPT_NoCodeTable, //           //   HTM_TG_o_shapedefaults
   KPT_NoCodeTable, //           //   HTM_TG_o_shapedefaults_e

   KPT_NoCodeTable, //           //   HTM_TG_o_colormenu
   KPT_NoCodeTable, //           //   HTM_TG_o_colormenu_e

   KPT_NoCodeTable, //           //   HTM_TG_o_shapelayout
   KPT_NoCodeTable, //           //   HTM_TG_o_shapelayout_e

   KPT_NoCodeTable, //           //   HTM_TG_o_idmap
   KPT_NoCodeTable, //           //   HTM_TG_o_idmap_e


   KPT_NoCodeTable, //           //   HTM_TG_v_background
   KPT_NoCodeTable, //           //   HTM_TG_v_background_e

   KPT_NoCodeTable, //           //   HTM_TG_v_fill
   KPT_NoCodeTable, //           //   HTM_TG_v_fill_e

   KPT_NoCodeTable, //           //   HTM_TG_v_shapetype
   KPT_NoCodeTable, //           //   HTM_TG_v_shapetype_e

   KPT_NoCodeTable, //           //   HTM_TG_v_stroke
   KPT_NoCodeTable, //           //   HTM_TG_v_stroke_e

   KPT_NoCodeTable, //           //   HTM_TG_v_path
   KPT_NoCodeTable, //           //   HTM_TG_v_path_e

   KPT_NoCodeTable, //           //   HTM_TG_v_shape
   KPT_NoCodeTable, //           //   HTM_TG_v_shape_e

   KPT_NoCodeTable, //           //   HTM_TG_w_wrap
   KPT_NoCodeTable, //           //   HTM_TG_w_wrap_e

   KPT_NoCodeTable, //           //   HTM_TG_v_textbox
   KPT_NoCodeTable, //           //   HTM_TG_v_textbox_e

   KPT_NoCodeTable, //           //   HTM_TG_o_p
   KPT_NoCodeTable, //           //   HTM_TG_o_p_e

   KPT_NoCodeTable, //           //   HTM_TG_v_formulas
   KPT_NoCodeTable, //           //   HTM_TG_v_formulas_e

   KPT_NoCodeTable, //           //   HTM_TG_v_f
   KPT_NoCodeTable, //           //   HTM_TG_v_f_e

   KPT_NoCodeTable, //           //   HTM_TG_o_lock
   KPT_NoCodeTable, //           //   HTM_TG_o_lock_e

   KPT_NoCodeTable, //           //   HTM_TG_v_imagedata
   KPT_NoCodeTable, //           //   HTM_TG_v_imagedata_e

   KPT_NoCodeTable, //           //   HTM_TG_v_line
   KPT_NoCodeTable, //           //   HTM_TG_v_line_e

   KPT_NoCodeTable, //           //   HTM_TG_v_oval
   KPT_NoCodeTable, //           //   HTM_TG_v_oval_e

   KPT_NoCodeTable, //           //   HTM_TG_w_WordDocument
   KPT_NoCodeTable, //           //   HTM_TG_w_WordDocument_e

   KPT_NoCodeTable, //           //   HTM_TG_w_FormsDesign
   KPT_NoCodeTable, //           //   HTM_TG_w_FormsDesign_e

   KPT_NoCodeTable, //           //   HTM_TG_o_Words
   KPT_NoCodeTable, //           //   HTM_TG_o_Words_e

   KPT_NoCodeTable, //           //   HTM_TG_w_ValidateAgainstSchemas
   KPT_NoCodeTable, //           //   HTM_TG_w_ValidateAgainstSchemas_e

   KPT_NoCodeTable, //           //   HTM_TG_w_SaveIfXMLInvalid
   KPT_NoCodeTable, //           //   HTM_TG_w_SaveIfXMLInvalid_e

   KPT_NoCodeTable, //           //   HTM_TG_w_IgnoreMixedContent
   KPT_NoCodeTable, //           //   HTM_TG_w_IgnoreMixedContent_e

   KPT_NoCodeTable, //           //   HTM_TG_w_AlwaysShowPlaceholderText
   KPT_NoCodeTable, //           //   HTM_TG_w_AlwaysShowPlaceholderText_e

   KPT_NoCodeTable, //           //   HTM_TG_w_Compatibility
   KPT_NoCodeTable, //           //   HTM_TG_w_Compatibility_e

   KPT_NoCodeTable, //           //   HTM_TG_w_SelectEntireFieldWithStartOrEnd
   KPT_NoCodeTable, //           //   HTM_TG_w_SelectEntireFieldWithStartOrEnd_e

   KPT_NoCodeTable, //           //   HTM_TG_w_UseWord2002TableStyleRules
   KPT_NoCodeTable, //           //   HTM_TG_w_UseWord2002TableStyleRules_e

   KPT_NoCodeTable, //           //   HTM_TG_w_BrowserLevel
   KPT_NoCodeTable, //           //   HTM_TG_w_BrowserLevel_e

   KPT_NoCodeTable, //           //   HTM_TG_w_LatentStyles
   KPT_NoCodeTable, //           //   HTM_TG_w_LatentStyles_e

   KPT_NoCodeTable, //           //   HTM_TG_w_SpellingState
   KPT_NoCodeTable, //           //   HTM_TG_w_SpellingState_e

   KPT_NoCodeTable, //           //   HTM_TG_w_GrammarState
   KPT_NoCodeTable, //           //   HTM_TG_w_GrammarState_e

   KPT_NoCodeTable, //           //   HTM_TG_THEAD
   KPT_NoCodeTable, //           //   HTM_TG_THEAD_e

   KPT_NoCodeTable, //           //   HTM_TG_TFOOT
   KPT_NoCodeTable, //           //   HTM_TG_TFOOT_e

   KPT_NoCodeTable, //           //   HTM_TG_NOSCRIPT
   KPT_NoCodeTable, //           //   HTM_TG_NOSCRIPT_e

   KPT_NoCodeTable, //           //   HTM_TG_PARAM
   KPT_NoCodeTable, //           //   HTM_TG_PARAM_e
};


const int iaHtmCodeTables71[HTM_TG_NumOfTags37] = // HTML Windows 1257 file code tables
{
  TV_MAIN_HTML_CTBL,           //   HTM_TG_HTML
  TV_MAIN_HTML_CTBL,           //   HTM_TG_HTML_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_P
  TV_MAIN_HTML_CTBL,           //   HTM_TG_P_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_SPAN
  TV_MAIN_HTML_CTBL,           //   HTM_TG_SPAN_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_HEAD
  TV_MAIN_HTML_CTBL,           //   HTM_TG_HEAD_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_TITLE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TITLE_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_META
  TV_MAIN_HTML_CTBL,           //   HTM_TG_META_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_STYLE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_STYLE_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_Comment
  TV_MAIN_HTML_CTBL,           //   HTM_TG_Comment_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_DOCTYPE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_DOCTYPE_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_SCRIPT
  TV_MAIN_HTML_CTBL,           //   HTM_TG_SCRIPT_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_BODY
  TV_MAIN_HTML_CTBL,           //   HTM_TG_BODY_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_LINK
  TV_MAIN_HTML_CTBL,           //   HTM_TG_LINK_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_SUP
  TV_MAIN_HTML_CTBL,           //   HTM_TG_SUP_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_A
  TV_MAIN_HTML_CTBL,           //   HTM_TG_A_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_TABLE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TABLE_e
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TR
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TR_e
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TD
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TD_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_BR
  TV_MAIN_HTML_CTBL,           //   HTM_TG_BR_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_TBODY
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TBODY_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_IMG
  TV_MAIN_HTML_CTBL,           //   HTM_TG_IMG_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_TH
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TH_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_NOBR
  TV_MAIN_HTML_CTBL,           //   HTM_TG_NOBR_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_B
  TV_MAIN_HTML_CTBL,           //   HTM_TG_B_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_DIV
  TV_MAIN_HTML_CTBL,           //   HTM_TG_DIV_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_PRE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_PRE_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_FONT
  TV_MAIN_HTML_CTBL,           //   HTM_TG_FONT_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_I
  TV_MAIN_HTML_CTBL,           //   HTM_TG_I_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_SUB
  TV_MAIN_HTML_CTBL,           //   HTM_TG_SUB_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_TT
  TV_MAIN_HTML_CTBL,           //   HTM_TG_TT_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_HR
  TV_MAIN_HTML_CTBL,           //   HTM_TG_HR_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_UL
  TV_MAIN_HTML_CTBL,           //   HTM_TG_UL_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_LI
  TV_MAIN_HTML_CTBL,           //   HTM_TG_LI_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_CENTER
  TV_MAIN_HTML_CTBL,           //   HTM_TG_CENTER_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_CAPTION
  TV_MAIN_HTML_CTBL,           //   HTM_TG_CAPTION_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_SAMP
  TV_MAIN_HTML_CTBL,           //   HTM_TG_SAMP_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_BIG
  TV_MAIN_HTML_CTBL,           //   HTM_TG_BIG_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_FORM
  TV_MAIN_HTML_CTBL,           //   HTM_TG_FORM_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_INPUT
  TV_MAIN_HTML_CTBL,           //   HTM_TG_INPUT_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_OBJECT
  TV_MAIN_HTML_CTBL,           //   HTM_TG_OBJECT_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_EMBED
  TV_MAIN_HTML_CTBL,           //   HTM_TG_EMBED_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_IFRAME
  TV_MAIN_HTML_CTBL,           //   HTM_TG_IFRAME_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_MARQUEE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_MARQUEE_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_CODE
  TV_MAIN_HTML_CTBL,           //   HTM_TG_CODE_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_OL
  TV_MAIN_HTML_CTBL,           //   HTM_TG_OL_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_H1
  TV_MAIN_HTML_CTBL,           //   HTM_TG_H1_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_H2
  TV_MAIN_HTML_CTBL,           //   HTM_TG_H2_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_H3
  TV_MAIN_HTML_CTBL,           //   HTM_TG_H3_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_H4
  TV_MAIN_HTML_CTBL,           //   HTM_TG_H4_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_H5
  TV_MAIN_HTML_CTBL,           //   HTM_TG_H5_e

  TV_MAIN_HTML_CTBL,           //   HTM_TG_H6
  TV_MAIN_HTML_CTBL,           //   HTM_TG_H6_e

// MS Word HTML
   TV_MAIN_HTML_CTBL,          //   HTM_TG_xml
   TV_MAIN_HTML_CTBL,          //   HTM_TG_xml_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_DocumentProperties
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_DocumentProperties_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Author
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Author_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_LastAuthor
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_LastAuthor_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Revision
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Revision_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_TotalTime
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_TotalTime_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Created
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Created_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_LastSaved
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_LastSaved_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Pages
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Pages_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Characters
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Characters_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Company
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Company_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Lines
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Lines_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Paragraphs
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Paragraphs_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_CharactersWithSpaces
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_CharactersWithSpaces_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Version
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Version_e


   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_shapedefaults
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_shapedefaults_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_colormenu
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_colormenu_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_shapelayout
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_shapelayout_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_idmap
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_idmap_e


   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_background
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_background_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_fill
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_fill_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_shapetype
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_shapetype_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_stroke
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_stroke_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_path
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_path_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_shape
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_shape_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_wrap
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_wrap_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_textbox
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_textbox_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_p
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_p_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_formulas
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_formulas_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_f
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_f_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_lock
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_lock_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_imagedata
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_imagedata_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_line
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_line_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_oval
   TV_MAIN_HTML_CTBL,          //   HTM_TG_v_oval_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_WordDocument
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_WordDocument_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_FormsDesign
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_FormsDesign_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Words
   TV_MAIN_HTML_CTBL,          //   HTM_TG_o_Words_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_ValidateAgainstSchemas
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_ValidateAgainstSchemas_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_SaveIfXMLInvalid
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_SaveIfXMLInvalid_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_IgnoreMixedContent
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_IgnoreMixedContent_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_AlwaysShowPlaceholderText
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_AlwaysShowPlaceholderText_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_Compatibility
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_Compatibility_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_SelectEntireFieldWithStartOrEnd
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_SelectEntireFieldWithStartOrEnd_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_UseWord2002TableStyleRules
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_UseWord2002TableStyleRules_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_BrowserLevel
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_BrowserLevel_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_LatentStyles
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_LatentStyles_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_SpellingState
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_SpellingState_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_GrammarState
   TV_MAIN_HTML_CTBL,          //   HTM_TG_w_GrammarState_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_THEAD
   TV_MAIN_HTML_CTBL,          //   HTM_TG_THEAD_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_TFOOT
   TV_MAIN_HTML_CTBL,          //   HTM_TG_TFOOT_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_NOSCRIPT
   TV_MAIN_HTML_CTBL,          //   HTM_TG_NOSCRIPT_e

   TV_MAIN_HTML_CTBL,          //   HTM_TG_PARAM
   TV_MAIN_HTML_CTBL,          //   HTM_TG_PARAM_e
};


const KpChar uiazHtmlGrTags[]=
{
  (KpChar)HTM_TG_HTML,
  (KpChar)HTM_TG_HTML_e,

  (KpChar)HTM_TG_HEAD,
  (KpChar)HTM_TG_HEAD_e,

  (KpChar)HTM_TG_TITLE,
  (KpChar)HTM_TG_TITLE_e,

  (KpChar)HTM_TG_META,
  (KpChar)HTM_TG_META_e,

  (KpChar)HTM_TG_STYLE,
  (KpChar)HTM_TG_STYLE_e,

  (KpChar)HTM_TG_SCRIPT,
  (KpChar)HTM_TG_SCRIPT_e,

  (KpChar)HTM_TG_BODY,
  (KpChar)HTM_TG_BODY_e,

  (KpChar)HTM_TG_LINK,
  (KpChar)HTM_TG_LINK_e,

  (KpChar)HTM_TG_TABLE,
  (KpChar)HTM_TG_TABLE_e,

  (KpChar)HTM_TG_TR,
  (KpChar)HTM_TG_TR_e,

  (KpChar)HTM_TG_TBODY,
  (KpChar)HTM_TG_TBODY_e,

  (KpChar)HTM_TG_P,
  (KpChar)HTM_TG_P_e,

  C_Nul
};


// ================================================== free xmlt functions
HRESULT PutHtmHat
(
   TvXmlFile *pOutFile,
   const unsigned char *lpszTitle,
   const unsigned char *lpszIcon,
   const unsigned char *lpszCSS,
   int iLang,
   int iRefresh,
   const unsigned char *lpszPageStyle,
   const unsigned char *lpszJavaScript
)
{
HRESULT retc = S_OK;
XmlTagPars *tag_par = NULL;
UC_Modes enc_mode;
int ctbl, def_ctbl;
XmlVersions version;
unsigned char *val_buf = NULL;
const unsigned char *lang_str = NULL;
KpChar *i_str_buf = NULL;
int ii;
KpChar *pnts;
static unsigned char css_name[KP_MAX_FNAME_LEN+1];

   if(pOutFile == NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(val_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

   if(SUCCEEDED(retc)) retc = pOutFile->GetVersion(&version);
   if((version >= XM_VERS_XML) && SUCCEEDED(retc)) KP_ERROR(KP_E_FILE_FORMAT, null);

// <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
   KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"html", (const unsigned char *)"", NULL));

   if(SUCCEEDED(retc)) retc = tag_par->AddTextPar((const unsigned char *)"PUBLIC", (const unsigned char *)""); // buvo "public", bet xhtml parseriui lovercase nepatinka
   if(SUCCEEDED(retc)) retc = tag_par->AddTextPar((const unsigned char *)"", plpszaHtmlVersionIds[version]);
   if(SUCCEEDED(retc)) retc = pOutFile->PutCharProc((KpChar)XL_DocType /* HTM_TG_DOCTYPE */, tag_par, False);

   KP_DELETE(tag_par);

   if(SUCCEEDED(retc)) retc = pOutFile->PutChar(Lf, False); // PutCharProc(C_Lf, NULL, False);

// <HTML>

   if(SUCCEEDED(retc))
   {
      lang_str=NULL;
      switch(iLang)
      {
      case KP_LNG_LIT:
      case KP_LNG_LIX:
      case KP_LNG_LIS: lang_str=(const unsigned char *)"lt"; break;
      case KP_LNG_ENG: lang_str=(const unsigned char *)"en"; break;
      case KP_LNG_GER: lang_str=(const unsigned char *)"de"; break;
      case KP_LNG_FRE: lang_str=(const unsigned char *)"fr"; break;
      case KP_LNG_RUS: lang_str=(const unsigned char *)"ru"; break;
      case KP_LNG_POL: lang_str=(const unsigned char *)"pl"; break;
      case KP_LNG_NO: lang_str=NULL; break;
      default:
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         break;
      }

      tag_par=NULL;
      if(lang_str && SUCCEEDED(retc))
         KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"lang", lang_str, NULL));

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HTML, tag_par, False);

      KP_DELETE(tag_par);

      if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <HEAD>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HEAD, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// <LINK REL="SHORTCUT ICON" HREF="http://www.site.net/icon.ico">
   if(SUCCEEDED(retc))
      if(lpszIcon!=NULL)
         if(strlen(lpszIcon)>0)
         {
            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"rel", (const unsigned char *)"shortcut icon", NULL));

            if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"href", lpszIcon);
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_LINK, tag_par, False);

            KP_DELETE(tag_par);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <LINK REL=stylesheet TYPE="text/css" HREF="http://www.site.net/styles.css">
   if(SUCCEEDED(retc))
      if(lpszCSS!=NULL)
         if(strlen(lpszCSS)>0)
         {
XL_PathMode path_mode = pOutFile->GetPathMode();
            css_name[0] = Nul;

            if(path_mode == XL_TuxPath) strcpy(css_name, TV_XL_TUX_PATH_PREFIX);

            if(path_mode == XL_AbsolutePath) if((strchr(lpszCSS, '/')==NULL) && (strchr(lpszCSS, '\\')==NULL) && SUCCEEDED(retc))
               retc = GetAppPath(css_name, True);

            if(strlen(css_name) + strlen(lpszCSS) >= KP_MAX_FNAME_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) strcat(css_name, lpszCSS);

// KpMsgOut(css_name, IDI_ASTERISK, KP_MB_TESTI);

            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"rel", (const unsigned char *)"stylesheet", NULL));

            if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"text/css");
            if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"href", css_name); // lpszCSS);
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_LINK, tag_par, False);

            KP_DELETE(tag_par);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <TITLE>
   if(SUCCEEDED(retc))
      if(lpszTitle!=NULL)
         if(strlen(lpszTitle)>0)
         {
            retc=pOutFile->PutCharProc((KpChar)HTM_TG_TITLE, NULL, False);
            if(SUCCEEDED(retc)) retc=pOutFile->PutStr(lpszTitle);
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_TITLE_e, NULL, False);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <META HTTP-EQUIV="Content-Type" CONTENT="text/html; CHARSET=windows-1257">
   if(SUCCEEDED(retc))
   {
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"http-equiv", (const unsigned char *)"content-type", NULL));

      if(SUCCEEDED(retc)) retc=pOutFile->GetEncoding(&enc_mode, &ctbl, &def_ctbl);
      if(SUCCEEDED(retc))
      {
         strcpy(val_buf, XM_HTM_Charset_Prefix);
         if(enc_mode<UC_Unicode)
         {
            if(lpszaXmlCtblNames[ctbl][0]) strcat(val_buf, lpszaXmlCtblNames[ctbl]);
            else if(lpszaXmlCtblNamesWin[ctbl][0]) strcat(val_buf, lpszaXmlCtblNamesWin[ctbl]);
            else KP_ERROR(KP_E_SYSTEM_ERROR, null);
         }
         else strcat(val_buf, lpszaXmlCodingModes[enc_mode]);
         retc=tag_par->AddTextPar((const unsigned char *)"content", val_buf);
      }

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_META, tag_par, False);

      KP_DELETE(tag_par);

      if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <meta http-equiv="refresh" content="5">
   if(iRefresh && SUCCEEDED(retc))
   {
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"http-equiv", (const unsigned char *)"refresh", NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddNumPar((const unsigned char *)"content", iRefresh);

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_META, tag_par, False);

      KP_DELETE(tag_par);

      if(SUCCEEDED(retc)) retc = pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <style type="text/css">
// A:link {text-decoration: none; color: grey;}
// A:visited {text-decoration: none; color: grey;}
// A:active {text-decoration: none; color: grey;}
// A:hover {text-decoration: none; color: grey;}
// </style>
   if(SUCCEEDED(retc))
      if(lpszPageStyle!=NULL)
         if(strlen(lpszPageStyle)>0)
         {
            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"type", (const unsigned char *)"text/css", NULL));

            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_STYLE, tag_par, False);

            KP_DELETE(tag_par);

            if(SUCCEEDED(retc)) retc=pOutFile->PutStr(lpszPageStyle);

            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_STYLE_e, tag_par, False);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <script language="JavaScript">
//    function submitas(arg) {
//      document.IP_adresai.ButNum.value = arg;
//      if (arg == 1) {
//          var tikrinam = confirm("Ar tikrai norite trinti ðiuos áraðus?");
//          if (tikrinam) document.IP_adresai.submit();
//      }
//      else document.IP_adresai.submit();
//    }
// </script>
   if(SUCCEEDED(retc))
      if(lpszJavaScript!=NULL)
      {
         ii=strlen(lpszJavaScript);
         if(ii>0)
         {
            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"language", (const unsigned char *)"JavaScript", NULL));
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_SCRIPT, tag_par, False);
            KP_DELETE(tag_par);

            KP_NEWA(i_str_buf, KpChar, ii + 1);
            if(SUCCEEDED(retc))
            {
               retc = KptStrEncode(i_str_buf, lpszJavaScript, TV_CPP_SOURCE_CTBL);
               if(FAILED(retc))
                  retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
            }

//          if(SUCCEEDED(retc)) retc=pOutFile->PutStr(lpszJavaScript);
//          if(SUCCEEDED(retc)) retc=pOutFile->PutKpStr(i_str_buf);
            if(SUCCEEDED(retc))
            {
               pnts=i_str_buf;
               while((*pnts) && SUCCEEDED(retc))
               {
                  switch(*pnts)
                  {
                  case C_Less:   // TV_XM_TagStartCh ('<')
                  case C_Great:  // TV_XM_TagEndCh  ('>')
                  case C_Amp:    // TV_XM_SpCharSt  ('&')
                     retc=pOutFile->PutChar(*pnts, True);
                     break;
                  default:
                     retc=pOutFile->PutCharProc(*pnts, NULL, False);
                     break;
                  }
                  pnts++;
               }
            }

            KP_DELETEA(i_str_buf);

            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_SCRIPT_e, tag_par, False);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }
      }


// </HEAD>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HEAD_e, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// <body>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_BODY, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

   KP_DELETEA(val_buf);

return(retc);
}


HRESULT PutXhtmlHat
(
   TvXmlFile *pOutFile,
   const unsigned char *lpszTitle,
   const unsigned char *lpszIcon,
   const unsigned char *lpszCSS,
   int iLang,
   int iRefresh,
   const unsigned char *lpszPageStyle,
   const unsigned char *lpszJavaScript
)
{
HRESULT retc=S_OK;
XmlTagPars *tag_par;
UC_Modes enc_mode;
int ctbl, def_ctbl;
XmlVersions version;
unsigned char *val_buf=NULL;
const unsigned char *lang_str=NULL;
KpChar *i_str_buf=NULL;
int ii;
KpChar *pnts;
static unsigned char css_name[KP_MAX_FNAME_LEN+1];

   if(pOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   KP_NEWA(val_buf, unsigned char, KP_MAX_FILE_LIN_LEN + 1);

   if(SUCCEEDED(retc)) retc = pOutFile->GetVersion(&version);
   if((version >= XM_VERS_XML) && SUCCEEDED(retc)) KP_ERROR(KP_E_FILE_FORMAT, null);

// <?xml version="1.0"?>
   if(SUCCEEDED(retc))
   {
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"version", (const unsigned char *)"1.0", NULL));
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_Version /* HTM_TG_DOCTYPE */, tag_par, False);
      KP_DELETE(tag_par);
      if(SUCCEEDED(retc)) retc=pOutFile->PutChar(Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <!DOCTYPE html PUBLIC
//   "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN"
//   "http://www.w3.org/TR/MathML2/dtd/xhtml-math11-f.dtd"
// [
//   <!ENTITY mathml "http://www.w3.org/1998/Math/MathML">
// ]>
   if(SUCCEEDED(retc))
   {
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"html", (const unsigned char *)"", NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"PUBLIC", (const unsigned char *)"");
//    if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"\n ", (const unsigned char *)"");
      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"", plpszaHtmlVersionIds[version]);
//    if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"\n ", (const unsigned char *)"");
      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"", plpszaHtmlDtds[version]);
//    if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"\n[\n  <!ENTITY mathml \"http://www.w3.org/1998/Math/MathML\">\n]", (const unsigned char *)"");
      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"[<!ENTITY mathml \"http://www.w3.org/1998/Math/MathML\">]", (const unsigned char *)"");
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)XL_DocType /* HTM_TG_DOCTYPE */, tag_par, False);

      KP_DELETE(tag_par);

      if(SUCCEEDED(retc)) retc=pOutFile->PutChar(Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <html xmlns="http://www.w3.org/1999/xhtml">

   if(SUCCEEDED(retc))
   {
      lang_str=NULL;
      switch(iLang)
      {
      case KP_LNG_LIT:
      case KP_LNG_LIX:
      case KP_LNG_LIS: lang_str=(const unsigned char *)"lt"; break;
      case KP_LNG_ENG: lang_str=(const unsigned char *)"en"; break;
      case KP_LNG_GER: lang_str=(const unsigned char *)"de"; break;
      case KP_LNG_FRE: lang_str=(const unsigned char *)"fr"; break;
      case KP_LNG_RUS: lang_str=(const unsigned char *)"ru"; break;
      case KP_LNG_POL: lang_str=(const unsigned char *)"pl"; break;
      case KP_LNG_NO: lang_str=NULL; break;
      default:
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         break;
      }

      tag_par=NULL;
      if(lang_str && SUCCEEDED(retc))
         KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"lang", lang_str, NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"xmlns", (const unsigned char *)"http://www.w3.org/1999/xhtml");

      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HTML, tag_par, False);

      KP_DELETE(tag_par);

      if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <HEAD>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HEAD, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// <LINK REL="SHORTCUT ICON" HREF="http://www.site.net/icon.ico">
   if(SUCCEEDED(retc))
      if(lpszIcon!=NULL)
         if(strlen(lpszIcon) > 0)
         {
            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"rel", (const unsigned char *)"shortcut icon", NULL));

            if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"href", lpszIcon);
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_LINK, tag_par, False);

            KP_DELETE(tag_par);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <LINK REL=stylesheet TYPE="text/css" HREF="http://www.site.net/styles.css">
   if(SUCCEEDED(retc))
      if(lpszCSS!=NULL)
         if(strlen(lpszCSS)>0)
         {
XL_PathMode path_mode = pOutFile->GetPathMode();
            css_name[0] = Nul;

            if(path_mode == XL_TuxPath) strcpy(css_name, TV_XL_TUX_PATH_PREFIX);

            if(path_mode == XL_AbsolutePath) if((strchr(lpszCSS, '/')==NULL) && (strchr(lpszCSS, '\\')==NULL) && SUCCEEDED(retc))
               retc = GetAppPath(css_name, True);

            if(strlen(css_name) + strlen(lpszCSS) >= KP_MAX_FNAME_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) strcat(css_name, lpszCSS);

// KpMsgOut(css_name, IDI_ASTERISK, KP_MB_TESTI);

            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"rel", (const unsigned char *)"stylesheet", NULL));

            if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"type", (const unsigned char *)"text/css");
            if(SUCCEEDED(retc)) retc=tag_par->AddTextPar((const unsigned char *)"href", css_name); // lpszCSS);
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_LINK, tag_par, False);

            KP_DELETE(tag_par);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <TITLE>
   if(SUCCEEDED(retc))
      if(lpszTitle!=NULL)
         if(strlen(lpszTitle)>0)
         {
            retc=pOutFile->PutCharProc((KpChar)HTM_TG_TITLE, NULL, False);
            if(SUCCEEDED(retc)) retc=pOutFile->PutStr(lpszTitle);
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_TITLE_e, NULL, False);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <META HTTP-EQUIV="Content-Type" CONTENT="text/html; CHARSET=windows-1257">
// <META HTTP-EQUIV="Content-Type" CONTENT="application/xhtml+xml; CHARSET=UTF-8">
   KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"http-equiv", (const unsigned char *)"content-type", NULL));

   if(SUCCEEDED(retc)) retc=pOutFile->GetEncoding(&enc_mode, &ctbl, &def_ctbl);
   if(SUCCEEDED(retc))
   {
      strcpy(val_buf, XM_XHTML_Charset_Prefix);
      if(enc_mode<UC_Unicode)
      {
         if(lpszaXmlCtblNames[ctbl][0]) strcat(val_buf, lpszaXmlCtblNames[ctbl]);
         else if(lpszaXmlCtblNamesWin[ctbl][0]) strcat(val_buf, lpszaXmlCtblNamesWin[ctbl]);
         else KP_ERROR(KP_E_SYSTEM_ERROR, null);
      }
      else strcat(val_buf, lpszaXmlCodingModes[enc_mode]);
      retc=tag_par->AddTextPar((const unsigned char *)"content", val_buf);
   }

   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_META, tag_par, False);

   KP_DELETE(tag_par);

   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// <meta http-equiv="refresh" content="5">
   if(iRefresh && SUCCEEDED(retc))
   {
      KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"http-equiv", (const unsigned char *)"refresh", NULL));

      if(SUCCEEDED(retc)) retc=tag_par->AddNumPar((const unsigned char *)"content", iRefresh);
      if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_META, tag_par, False);

      KP_DELETE(tag_par);

      if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
   }

// <style type="text/css">
// A:link {text-decoration: none; color: grey;}
// A:visited {text-decoration: none; color: grey;}
// A:active {text-decoration: none; color: grey;}
// A:hover {text-decoration: none; color: grey;}
// </style>
   if(SUCCEEDED(retc))
      if(lpszPageStyle!=NULL)
         if(strlen(lpszPageStyle)>0)
         {
            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"type", (const unsigned char *)"text/css", NULL));
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_STYLE, tag_par, False);
            KP_DELETE(tag_par);

            if(SUCCEEDED(retc)) retc=pOutFile->PutStr(lpszPageStyle);

            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_STYLE_e, tag_par, False);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }

// <script language="JavaScript">
//    function submitas(arg) {
//      document.IP_adresai.ButNum.value = arg;
//      if (arg == 1) {
//          var tikrinam = confirm("Ar tikrai norite trinti ðiuos áraðus?");
//          if (tikrinam) document.IP_adresai.submit();
//      }
//      else document.IP_adresai.submit();
//    }
// </script>
   if(SUCCEEDED(retc))
      if(lpszJavaScript!=NULL)
      {
         ii=strlen(lpszJavaScript);
         if(ii>0)
         {
            KP_NEWO(tag_par, XmlTagPars((const unsigned char *)"language", (const unsigned char *)"JavaScript", NULL));
            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_SCRIPT, tag_par, False);
            KP_DELETE(tag_par);

            KP_NEWA(i_str_buf, KpChar, ii + 1);

            if(SUCCEEDED(retc))
            {
               retc=KptStrEncode(i_str_buf, lpszJavaScript, TV_CPP_SOURCE_CTBL);
               if(FAILED(retc))
                  retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
            }

//          if(SUCCEEDED(retc)) retc=pOutFile->PutStr(lpszJavaScript);
//          if(SUCCEEDED(retc)) retc=pOutFile->PutKpStr(i_str_buf);
            if(SUCCEEDED(retc))
            {
               pnts=i_str_buf;
               while((*pnts) && SUCCEEDED(retc))
               {
                  switch(*pnts)
                  {
                  case C_Less:   // TV_XM_TagStartCh ('<')
                  case C_Great:  // TV_XM_TagEndCh  ('>')
                  case C_Amp:    // TV_XM_SpCharSt  ('&')
                     retc=pOutFile->PutChar(*pnts, True);
                     break;
                  default:
                     retc=pOutFile->PutCharProc(*pnts, NULL, False);
                     break;
                  }
                  pnts++;
               }
            }

            KP_DELETEA(i_str_buf);

            if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_SCRIPT_e, tag_par, False);

            if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);
         }
      }


// </HEAD>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HEAD_e, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// <body>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_BODY, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

   KP_DELETEA(val_buf);

return(retc);
}


HRESULT PutHtmTail(TvXmlFile *pOutFile)
{
HRESULT retc=S_OK;

   if(pOutFile==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// </body>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_BODY_e, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

// </HTML>
   if(SUCCEEDED(retc)) retc=pOutFile->PutCharProc((KpChar)HTM_TG_HTML_e, NULL, False);
   if(SUCCEEDED(retc)) retc=pOutFile->PutChar(C_Lf, False); // PutCharProc(C_Lf, NULL, False);

return(retc);
}


// --------------------------------------------------
HRESULT HtmtTestEmbedded(int iChar, int iParentTag, bool *bEmbFlPtr)
{
HRESULT retc=S_OK;

   *bEmbFlPtr=False;

   switch(iParentTag)
   {
   case HTM_TG_HTML:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_HEAD) ||
         (iChar==HTM_TG_STYLE) ||
         (iChar==HTM_TG_SCRIPT) ||
         (iChar==HTM_TG_BODY)
      );
      break;

   case HTM_TG_HEAD:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_TITLE) ||
         (iChar==HTM_TG_META)
      );
      break;

   case HTM_TG_TITLE:

   case HTM_TG_H1:
   case HTM_TG_H2:
   case HTM_TG_H3:
   case HTM_TG_H4:
   case HTM_TG_H5:
   case HTM_TG_H6:

   case HTM_TG_P:
   case HTM_TG_DIV:
   case HTM_TG_SPAN:
   case HTM_TG_CENTER:

   case HTM_TG_B:
   case HTM_TG_I:
   case HTM_TG_TT:
   case HTM_TG_SUB:
   case HTM_TG_SUP:
   case HTM_TG_FONT:

   case HTM_TG_BIG:
   case HTM_TG_SAMP:

   case HTM_TG_A:

   case HTM_TG_CAPTION:
   case HTM_TG_TD:
   case HTM_TG_TH:

   case HTM_TG_NOBR:
   case HTM_TG_PRE:
   case HTM_TG_CODE:

   case HTM_TG_LI:

   case HTM_TG_o_Author:
   case HTM_TG_o_LastAuthor:
   case HTM_TG_o_Revision:
   case HTM_TG_o_TotalTime:
   case HTM_TG_o_Created:
   case HTM_TG_o_LastSaved:
   case HTM_TG_o_Pages:
   case HTM_TG_o_Words:
   case HTM_TG_o_Characters:
   case HTM_TG_o_Company:
   case HTM_TG_o_Lines:
   case HTM_TG_o_Paragraphs:
   case HTM_TG_o_CharactersWithSpaces:
   case HTM_TG_o_Version:
   case HTM_TG_o_p:
   case HTM_TG_w_SpellingState:
   case HTM_TG_w_GrammarState:
   case HTM_TG_w_SaveIfXMLInvalid:
   case HTM_TG_w_IgnoreMixedContent:
   case HTM_TG_w_AlwaysShowPlaceholderText:
   case HTM_TG_w_BrowserLevel:

      *bEmbFlPtr=
      (
         ((iChar>=0) && (iChar<KPT_Ctbsiz/* C_Charsize */))
      );
      break;

   case HTM_TG_STYLE:
      *bEmbFlPtr=
      (
         (iChar==XL_Comment) ||
         ((iChar>=0) && (iChar<KPT_Ctbsiz/* C_Charsize */))
      );
      break;

   case HTM_TG_SCRIPT:
      *bEmbFlPtr=
      (
         (iChar==XL_Comment)
      );
      break;

   case HTM_TG_BODY:
   case HTM_TG_IFRAME:
   case HTM_TG_MARQUEE:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_H1) ||
         (iChar==HTM_TG_H2) ||
         (iChar==HTM_TG_H3) ||
         (iChar==HTM_TG_H4) ||
         (iChar==HTM_TG_H5) ||
         (iChar==HTM_TG_H6) ||
         (iChar==HTM_TG_P) ||
         (iChar==HTM_TG_SPAN) ||
         (iChar==HTM_TG_DIV) ||
         (iChar==HTM_TG_TABLE) ||
         (iChar==HTM_TG_IMG) // ||
//    || ((iChar>=0) && (iChar<KPT_Ctbsiz/* C_Charsize */))
      );
      break;

   case HTM_TG_TABLE:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_CAPTION) ||
         (iChar==HTM_TG_THEAD) ||
         (iChar==HTM_TG_TBODY) ||
         (iChar==HTM_TG_TFOOT) ||
         (iChar==HTM_TG_TR)
      );
      break;

   case HTM_TG_THEAD:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_TR)
      );
      break;

   case HTM_TG_TBODY:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_TR)
      );
      break;

   case HTM_TG_TFOOT:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_TR)
      );
      break;

   case HTM_TG_TR:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_TH) ||
         (iChar==HTM_TG_TD)
      );
      break;

   case HTM_TG_UL:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_LI)
      );
      break;

   case HTM_TG_FORM:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_H1) ||
         (iChar==HTM_TG_H2) ||
         (iChar==HTM_TG_H3) ||
         (iChar==HTM_TG_H4) ||
         (iChar==HTM_TG_H5) ||
         (iChar==HTM_TG_H6) ||
         (iChar==HTM_TG_P) ||
         (iChar==HTM_TG_SPAN) ||
         (iChar==HTM_TG_DIV) ||
         (iChar==HTM_TG_TABLE) ||
         (iChar==HTM_TG_IMG) ||

         (iChar==HTM_TG_INPUT) // ||
//    || ((iChar>=0) && (iChar<KPT_Ctbsiz/* C_Charsize */))
      );
      break;

   case HTM_TG_xml:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_o_DocumentProperties)
      );
      break;

   case HTM_TG_o_DocumentProperties:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_o_Author) ||
         (iChar==HTM_TG_o_LastAuthor) ||
         (iChar==HTM_TG_o_Revision) ||
         (iChar==HTM_TG_o_TotalTime) ||
         (iChar==HTM_TG_o_Created) ||
         (iChar==HTM_TG_o_LastSaved) ||
         (iChar==HTM_TG_o_Pages) ||
         (iChar==HTM_TG_o_Words) ||
         (iChar==HTM_TG_o_Characters) ||
         (iChar==HTM_TG_o_Company) ||
         (iChar==HTM_TG_o_Lines) ||
         (iChar==HTM_TG_o_Paragraphs) ||
         (iChar==HTM_TG_o_CharactersWithSpaces) ||
         (iChar==HTM_TG_o_Version)
      );
      break;

   case HTM_TG_o_shapedefaults:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_o_colormenu)
      );
      break;

   case HTM_TG_o_shapelayout:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_o_idmap)
      );
      break;

   case HTM_TG_v_background:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_v_fill)
      );
      break;

   case HTM_TG_v_shapetype:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_v_stroke) ||
         (iChar==HTM_TG_v_path)
      );
      break;

   case HTM_TG_v_formulas:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_v_f)
      );
      break;

   case HTM_TG_w_WordDocument:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_w_SpellingState) ||
         (iChar==HTM_TG_w_GrammarState) ||
         (iChar==HTM_TG_w_FormsDesign) ||
         (iChar==HTM_TG_w_ValidateAgainstSchemas) ||
         (iChar==HTM_TG_w_SaveIfXMLInvalid) ||
         (iChar==HTM_TG_w_IgnoreMixedContent) ||
         (iChar==HTM_TG_w_AlwaysShowPlaceholderText) ||
         (iChar==HTM_TG_w_Compatibility) ||
         (iChar==HTM_TG_w_BrowserLevel)
      );
      break;

   case HTM_TG_w_Compatibility:
      *bEmbFlPtr=
      (
         (iChar==HTM_TG_w_SelectEntireFieldWithStartOrEnd) ||
         (iChar==HTM_TG_w_UseWord2002TableStyleRules)
      );
      break;

   }

return(retc);
}


// --------------------------------------------------
// darbinë funkcija iðkvieèiama ið HtmtTestPars()
// lpszStrBuf[TV_TAG_LEN*2+KP_MAX_FILE_LIN_WDT+100]
unsigned char *HtmtFormatMsg(unsigned char *lpszStrBuf, const unsigned char *lpszTagName, const unsigned char *lpszPar, const unsigned char *lpszVal)
{
unsigned char *pntd;

   pntd = lpszStrBuf;

   strncpy(pntd, lpszTagName, TV_TAG_LEN);
   pntd[TV_TAG_LEN] = Nul;
   strcat(pntd, ": ");
   pntd += strlen(pntd);

   strncpy(pntd, lpszPar?lpszPar:(const unsigned char *)"", TV_TAG_LEN);
   pntd[TV_TAG_LEN] = Nul;
   strcat(pntd, "=\"");
   pntd += strlen(pntd);

   strncpy(pntd, lpszVal?lpszVal:(const unsigned char *)"", KP_MAX_FILE_LIN_WDT);
   pntd[KP_MAX_FILE_LIN_WDT] = Nul;
   strcat(pntd, "\"");

return(lpszStrBuf);
}


HRESULT HtmtTestPars(int iChar, XmlTagPars *pTagParsObj, UC_Modes *piEncMode, int *piCodeTable, int *piDefCodeTable,
   const unsigned char * const *plpszTagNames /* = NULL */, KpChar iFirstDictTag /* = C_Nul */, KpChar iLastDictTag /* = C_Nul */)
{
HRESULT retc=S_OK;

int par_cnt;
#ifdef Debug
unsigned char par_nam[TV_TAG_LEN+1];
#endif
unsigned char *par_val = NULL;
const unsigned char *test_str;
int ii;
int par_num;
unsigned char *test_val = NULL;
const unsigned char *tag_name = (const unsigned char *)"";
static unsigned char str_buf[TV_TAG_LEN*2+KP_MAX_FILE_LIN_WDT+100];

   if((piEncMode==NULL) || (piCodeTable==NULL) || (piDefCodeTable==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if(plpszTagNames == NULL) plpszTagNames = plpszaHtmlTags;
      if(iFirstDictTag == C_Nul)
      {
         iFirstDictTag = HTM_TG_FirstTag;
         if(iLastDictTag == C_Nul)
            iLastDictTag = HTM_TG_LastTag;
         else
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         if(iLastDictTag == 0)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
         else if((iLastDictTag < iFirstDictTag) || (iLastDictTag >= iFirstDictTag + XL_MaxNumOfTags))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc)) tag_name = GetTagName(iChar, plpszTagNames, iFirstDictTag, iLastDictTag);

   KP_NEWA(par_val, unsigned char, MAX_XML_PAR_VAL_LEN + 1);
   KP_NEWA(test_val, unsigned char, MAX_XML_PAR_VAL_LEN + 1);

// if(SUCCEEDED(retc))
// {
//    *piEncMode=UC_No_Mode;
//    *piCodeTable=1;
// }

   if(SUCCEEDED(retc)) switch(iChar)
   {
#ifdef Debug
   case XL_DocType:
   case XL_Comment:
      break;

   case HTM_TG_HEAD:
   case HTM_TG_TITLE:
   case HTM_TG_SUP:
   case HTM_TG_SUB:
   case HTM_TG_NOBR:
   case HTM_TG_B:
   case HTM_TG_I:
   case HTM_TG_BR:
   case HTM_TG_TT:
   case HTM_TG_PRE:
   case HTM_TG_LI:
   case HTM_TG_TBODY:
   case HTM_TG_CENTER:
   case HTM_TG_CAPTION:
   case HTM_TG_SAMP:
   case HTM_TG_CODE:
   case HTM_TG_FORM:

   case HTM_TG_H1:
   case HTM_TG_H2:
   case HTM_TG_H3:
   case HTM_TG_H4:
   case HTM_TG_H5:
   case HTM_TG_H6:

   case HTM_TG_THEAD:
   case HTM_TG_TFOOT:

   case HTM_TG_xml:
   case HTM_TG_o_DocumentProperties:
   case HTM_TG_o_Author:
   case HTM_TG_o_LastAuthor:
   case HTM_TG_o_Revision:
   case HTM_TG_o_TotalTime:
   case HTM_TG_o_Created:
   case HTM_TG_o_LastSaved:
   case HTM_TG_o_Pages:
   case HTM_TG_o_Words:
   case HTM_TG_o_Characters:
   case HTM_TG_o_Company:
   case HTM_TG_o_Lines:
   case HTM_TG_o_Paragraphs:
   case HTM_TG_o_CharactersWithSpaces:
   case HTM_TG_o_Version:
   case HTM_TG_o_p:
   case HTM_TG_v_formulas:

   case HTM_TG_w_WordDocument:
   case HTM_TG_w_FormsDesign:

   case HTM_TG_w_ValidateAgainstSchemas:
   case HTM_TG_w_SaveIfXMLInvalid:
   case HTM_TG_w_IgnoreMixedContent:
   case HTM_TG_w_AlwaysShowPlaceholderText:
   case HTM_TG_w_Compatibility:
   case HTM_TG_w_SelectEntireFieldWithStartOrEnd:
   case HTM_TG_w_UseWord2002TableStyleRules:
   case HTM_TG_w_BrowserLevel:

   case HTM_TG_w_SpellingState:
   case HTM_TG_w_GrammarState:

   case HTM_TG_NOSCRIPT:

   case HTM_TG_HTML_e:
   case HTM_TG_HEAD_e:
   case HTM_TG_TITLE_e:
   case HTM_TG_BODY_e:
   case HTM_TG_STYLE_e:
   case HTM_TG_SCRIPT_e:
   case HTM_TG_P_e:
   case HTM_TG_SPAN_e:
   case HTM_TG_A_e:
   case HTM_TG_SUP_e:
   case HTM_TG_SUB_e:
   case HTM_TG_TABLE_e:
   case HTM_TG_TR_e:
   case HTM_TG_TH_e:
   case HTM_TG_TD_e:
   case HTM_TG_NOBR_e:
   case HTM_TG_B_e:
   case HTM_TG_I_e:
   case HTM_TG_DIV_e:
   case HTM_TG_TT_e:
   case HTM_TG_PRE_e:
   case HTM_TG_UL_e:
   case HTM_TG_OL_e:
   case HTM_TG_LI_e:
   case HTM_TG_TBODY_e:
   case HTM_TG_CENTER_e:
   case HTM_TG_CAPTION_e:
   case HTM_TG_SAMP_e:
   case HTM_TG_FONT_e:
   case HTM_TG_MARQUEE_e:
   case HTM_TG_CODE_e:
   case HTM_TG_FORM_e:

   case HTM_TG_H1_e:
   case HTM_TG_H2_e:
   case HTM_TG_H3_e:
   case HTM_TG_H4_e:
   case HTM_TG_H5_e:
   case HTM_TG_H6_e:

   case HTM_TG_THEAD_e:
   case HTM_TG_TFOOT_e:

   case HTM_TG_xml_e:
   case HTM_TG_o_DocumentProperties_e:
   case HTM_TG_o_Author_e:
   case HTM_TG_o_LastAuthor_e:
   case HTM_TG_o_Revision_e:
   case HTM_TG_o_TotalTime_e:
   case HTM_TG_o_Created_e:
   case HTM_TG_o_LastSaved_e:
   case HTM_TG_o_Pages_e:
   case HTM_TG_o_Words_e:
   case HTM_TG_o_Characters_e:
   case HTM_TG_o_Company_e:
   case HTM_TG_o_Lines_e:
   case HTM_TG_o_Paragraphs_e:
   case HTM_TG_o_CharactersWithSpaces_e:
   case HTM_TG_o_Version_e:
   case HTM_TG_o_shapedefaults_e:
   case HTM_TG_o_shapelayout_e:

   case HTM_TG_v_background_e:
   case HTM_TG_v_shapetype_e:
   case HTM_TG_v_shape_e:
   case HTM_TG_v_textbox_e:
   case HTM_TG_o_p_e:
   case HTM_TG_v_formulas_e:

   case HTM_TG_v_line_e:

   case HTM_TG_w_WordDocument_e:

   case HTM_TG_w_SaveIfXMLInvalid_e:
   case HTM_TG_w_IgnoreMixedContent_e:
   case HTM_TG_w_AlwaysShowPlaceholderText_e:
   case HTM_TG_w_Compatibility_e:
   case HTM_TG_w_BrowserLevel_e:
   case HTM_TG_w_LatentStyles_e:
   case HTM_TG_w_SpellingState_e:
   case HTM_TG_w_GrammarState_e:

   case HTM_TG_OBJECT_e:
   case HTM_TG_NOSCRIPT_e:
   case HTM_TG_EMBED_e:

      if(pTagParsObj!=NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name);
      break;

   case HTM_TG_HTML:
      if(SUCCEEDED(retc)) if(pTagParsObj != NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

         for(ii=0; (ii < par_cnt) && (SUCCEEDED(retc)); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
// MS-Word HTML
// <html xmlns:v="urn:schemas-microsoft-com:vml" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:w="urn:schemas-microsoft-com:office:word" xmlns="http://www.w3.org/TR/REC-html40">
                  (strcmp(par_nam, "xmlns:v") != 0) &&
                  (strcmp(par_nam, "xmlns:o") != 0) &&
                  (strcmp(par_nam, "xmlns:w") != 0) &&
                  (strcmp(par_nam, "xmlns") != 0)
                 )
                  KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));

            } // if(SUCCEEDED(retc)) // retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);

         } // for(ii=0; (ii<par_cnt) && (SUCCEEDED(retc)); ii++)

      } // if(pTagParsObj != NULL)

      break;
#endif // #ifdef Debug

   case HTM_TG_META:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

// <META HTTP-EQUIV="Content-Type" CONTENT="text/html; CHARSET=windows-1257">
// <meta http-equiv="content-language" content="lt">
         if((par_cnt!=2) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, tag_name);

         if(SUCCEEDED(retc))
         {
            test_str=(const unsigned char *)"http-equiv";
            retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
            if(SUCCEEDED(retc))
            {
               if((/* (par_num!=0) || */ (par_val==NULL)) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

               if(SUCCEEDED(retc)) if(strlen(par_val) >= KP_MAX_FILE_LIN_LEN) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

               if(SUCCEEDED(retc))
               {
                  strcpy(test_val, par_val);
                  TvStrLwrLat(test_val);

                  if(strcmp(test_val, "content-type")==0)
                  {
                     test_str=(const unsigned char *)"content";
                     retc = pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
                     if(FAILED(retc))
                     {
                        if(retc==KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(retc, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
                     }
                     else
                     {
                        if((/* (par_num!=1) || */ (par_val==NULL)) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
                        if(SUCCEEDED(retc))
                        {
                           test_str=XM_HTM_Charset_Prefix;
                           ii=strlen(test_str);
                           strncpy(test_val, par_val, ii);
                           test_val[ii]=Nul;
                           if(strcmp(test_val, test_str)!=0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val))
                           else
                           {
                              *piDefCodeTable=0;
                              strcpy(test_val, par_val+ii);
                              retc=GetKwrdIndex((int *)piEncMode, test_val, lpszaXmlCodingModes, UC_Num_Of_Modes, False, True);
                              if(retc==KP_E_KWD_NOT_FOUND)
                              {
                                 *piEncMode=UC_No_Mode;
                                 retc=GetKwrdIndex(piDefCodeTable, test_val, lpszaXmlCtblNames, KPT_Ctnum, False, True);
                                 if(retc==KP_E_KWD_NOT_FOUND)
                                 {
                                    retc=GetKwrdIndex(piDefCodeTable, test_val, lpszaXmlCtblNamesWin, KPT_Ctnum, False, True);
                                    if(retc==KP_E_KWD_NOT_FOUND)
                                    {
                                       *piEncMode=UC_No_Mode;
                                       *piDefCodeTable=1;
                                       retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, par_val), False, __FILE__, __LINE__, 0L);
                                    }
                                 }
                                 *piCodeTable=(*piDefCodeTable);
                              }
                           }
                        }
                     }

                  } // if(strcmp(test_val, "content-type")==0)

                  else if(strcmp(test_val, "content-language")==0)
                  {
                     test_str=(const unsigned char *)"content";
                     retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
                     if(FAILED(retc))
                     {
                        if(retc==KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(retc, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
                     }
                     else
                     {
                        if(((par_num!=1) || (par_val==NULL)) && SUCCEEDED(retc))
                           KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

                        if(SUCCEEDED(retc))
                        {
                           strncpy(test_val, par_val, KP_MAX_FILE_LIN_LEN);
                           test_val[KP_MAX_FILE_LIN_LEN]=Nul;
                           TvStrLwrLat(test_val);

                           if(
                              (strcmp(test_val, "en")!=0) &&
                              (strcmp(test_val, "de")!=0) &&
                              (strcmp(test_val, "fr")!=0) &&
                              (strcmp(test_val, "lt")!=0) &&
                              (strcmp(test_val, "nl")!=0) &&
                              (strcmp(test_val, "ru")!=0)
                             )
                              KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
                        }

                     } // else // if(FAILED(retc))
                  }
                  else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
               }
            }
            else if(retc==KP_E_KWD_NOT_FOUND) // if(SUCCEEDED(retc)) // "http-equiv"
            {
               retc=S_OK;

// <meta name="description" content="...">
// <meta name="keywords" content="...">
// MS Word HTML
// <meta name="ProgId" content="Word.Document"/>
// <meta name="Generator" content="Microsoft Word 9"/>
// <meta name="Originator" content="Microsoft Word 9"/>
               test_str=(unsigned char *)"name";
               retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
               if(FAILED(retc))
               {
                  if(retc==KP_E_KWD_NOT_FOUND)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
               }
               else
               {
                  if(((par_num!=0) || (par_cnt!=2)) && SUCCEEDED(retc))
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

                  if(SUCCEEDED(retc))
                  {
                     strcpy(test_val, par_val);
                     TvStrLwrLat(test_val);
                  }

                  if(SUCCEEDED(retc))
                     if(
                        (strcmp(test_val, "description") != 0) &&
                        (strcmp(test_val, "keywords") != 0) &&
                        (strcmp(test_val, "generator") != 0) &&
// MS Word HTML
                        (strcmp(test_val, "progid") != 0) &&
                        (strcmp(test_val, "generator") != 0) &&
                        (strcmp(test_val, "originator") != 0)
                       )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

                  if(SUCCEEDED(retc))
                  {
                     test_str=(unsigned char *)"content";
                     retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
                     if(FAILED(retc))
                     {
                        if(retc==KP_E_KWD_NOT_FOUND)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
                     }
                     else
                        if(((par_num!=1) || (strlen(par_val)==0)) && SUCCEEDED(retc))
                           KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
                  }

               } // else // if(FAILED(retc)) // retc=pTagParsObj->SeekTextPar("name", par_val, &par_num);

            } // else // if(SUCCEEDED(retc)) // "http-equiv"

         } // if(SUCCEEDED(retc))

      } // else // if(pTagParsObj==NULL)
      break;

#ifdef Debug
// <body bgcolor="#FFFFFF" text="#000000" link="#0000CC" vlink="#000099" alink="#FF0000" leftmargin=0 topmargin=6 marginwidth=0 marginheight=6>
// <body bgcolor="white" lang="EN-US" style="tab-interval:18.000000pt;">
// <body bgcolor=white background="./p1_files/image001.jpg" lang=EN-US style='tab-interval:36.0pt'>
   case HTM_TG_BODY:
      if(pTagParsObj==NULL)
      {
//       KP_WARNING(KP_E_FILE_FORMAT, tag_name);
      }
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

         for(ii=0; (ii<par_cnt) && (SUCCEEDED(retc)); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "bgcolor")==0) ||
                  (strcmp(par_nam, "text")==0) ||
                  (strcmp(par_nam, "link")==0) ||
                  (strcmp(par_nam, "vlink")==0) ||
                  (strcmp(par_nam, "alink")==0)
                 )
               {
                  if(!TvIsColor(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                        (strcmp(par_nam, "leftmargin")==0) ||
                        (strcmp(par_nam, "topmargin")==0) ||
                        (strcmp(par_nam, "marginwidth")==0) ||
                        (strcmp(par_nam, "marginheight")==0)
                      )
               {
                  if(!TvIsNumber(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                        (strcmp(par_nam, "onload")==0) ||
                        (strcmp(par_nam, "lang")==0) ||
                        (strcmp(par_nam, "style")==0) ||
                        (strcmp(par_nam, "background")==0)
                      )
               {
                  if(strlen(par_val)==0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));

            } // if(SUCCEEDED(retc)) // retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);

         } // for(ii=0; (ii<par_cnt) && (SUCCEEDED(retc)); ii++)

      } // else // if(pTagParsObj==NULL)

      break;

   case HTM_TG_LINK:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

         if(SUCCEEDED(retc))
         {
            test_str=(const unsigned char *)"rel";
            retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
            if(FAILED(retc))
            {
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
            }
            else
            {
//             if((par_num!=0) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, null);

               if(SUCCEEDED(retc))
               {
// <LINK REL="SHORTCUT ICON" HREF="http://www.site.net/icon.ico">
// MS Word HTML
// <link rel="File-List" href="./p21_files/filelist.xml"/>
// <link rel="Edit-Time-Data" href="./p21_files/editdata.mso"/>
                  if(SUCCEEDED(retc))
                  {
                     strcpy(test_val, par_val);
                     TvStrLwrLat(test_val);
                  }

                  if(
                     (strcmp(test_val, "shortcut icon") == 0) ||
                     (strcmp(test_val, "file-list") == 0) ||
                     (strcmp(test_val, "edit-time-data") == 0)
                    )
                  {
                     if(par_cnt!=2) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

                     if(SUCCEEDED(retc))
                     {
                        test_str=(const unsigned char *)"href";
                        retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
                        if(FAILED(retc))
                        {
                           if(retc==KP_E_KWD_NOT_FOUND)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
                        }
                        else
                           if(((par_num!=1) || (strlen(par_val)==0)) && SUCCEEDED(retc))
                              KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
                     }

                  }
// <LINK REL=stylesheet TYPE="text/css" HREF="http://www.site.net/styles.css">
                  else if(strcmp(par_val,"stylesheet")==0)
                  {
                     if(par_cnt!=3) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

                     if(SUCCEEDED(retc))
                     {
                        test_str=(const unsigned char *)"type";
                        retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
                        if(FAILED(retc))
                        {
                           if(retc==KP_E_KWD_NOT_FOUND)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
                        }
                        else
                           if((/* (par_num!=1) || */ (strcmp(par_val,"text/css")!=0)) && SUCCEEDED(retc))
                              KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
                     }

                     if(SUCCEEDED(retc))
                     {
                        test_str=(const unsigned char *)"href";
                        retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
                        if(FAILED(retc))
                        {
                           if(retc==KP_E_KWD_NOT_FOUND)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
                        }
                        else
                           if((/* (par_num!=2) || */ (strlen(par_val)==0)) && SUCCEEDED(retc))
                              KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
                     }
                  }
                  else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

               } // if(SUCCEEDED(retc))

            } // else // if(FAILED(retc)) // retc=pTagParsObj->SeekTextPar("rel", par_val, &par_num);

         } // if(SUCCEEDED(retc))

      } // else // if(pTagParsObj==NULL)

      break;

   case HTM_TG_STYLE:
// <STYLE>
      if(pTagParsObj!=NULL)
      {
// <STYLE type=text/css>
         retc=pTagParsObj->GetParCnt(&par_cnt);
         if((par_cnt!=1) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, tag_name);

         if(SUCCEEDED(retc))
         {
            test_str=(const unsigned char *)"type";
            retc=pTagParsObj->SeekTextPar(test_str, par_val, &par_num);
            if(FAILED(retc))
            {
               if(retc==KP_E_KWD_NOT_FOUND)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, HtmtFormatMsg(str_buf, tag_name, test_str, (const unsigned char *)""), False, __FILE__, __LINE__, 0L);
            }
            else
            {
               if(((par_num!=0) || (strcmp(par_val, "text/css")!=0)) && SUCCEEDED(retc))
                  KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
            }
         }

      } // if(pTagParsObj!=NULL)

      break;

   case HTM_TG_SCRIPT:
// <SCRIPT>
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
// <SCRIPT LANGUAGE="JavaScript">
// <script language="JavaScript" type="text/javascript">
// FlashPageFlip.com: <script type="text/javascript">
         retc=pTagParsObj->GetParCnt(&par_cnt);
         if((par_cnt==0) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, tag_name);

//       found = False;

         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(strcmp(par_nam, "language")==0)
               {
//                found = True;
                  strlwr(par_val);
                  if((strcmp(par_val, "javascript")!=0) && SUCCEEDED(retc))
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "type")==0)
               {
//                found = True;
                  if((strcmp(par_val, "text/javascript")!=0) && SUCCEEDED(retc))
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "src")==0)
               {
//                found = True;
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));
            }
         }

//       if((!found) && SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, test_str, par_val));

      } // else // if(pTagParsObj==NULL)

      break;

// <P CLASS=HP>
// <p align='right'>
   case HTM_TG_P:
      if(pTagParsObj!=NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "class")==0) ||
                  (strcmp(par_nam, "style")==0)
                 )
               {
                  if(strlen(par_val)==0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "align")==0)
               {
                  if(
                     (strcmp(par_val, "left")!=0) &&
                     (strcmp(par_val, "right")!=0) &&
                     (strcmp(par_val, "top")!=0) &&
                     (strcmp(par_val, "bottom")!=0) &&
                     (strcmp(par_val, "center")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }
         }
      }
      break;

// <SPAN CLASS=HW>
// <SPAN ONMOUSEOVER="LtAbbrAdvise(this)", ONMOUSEOUT="LtAbbrOut(this)", CLASS=LtAbbr>
// <span lang="LT" style="mso-ansi-language:LT;">
   case HTM_TG_SPAN:
      if(pTagParsObj!=NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "class")==0) ||
                  (strcmp(par_nam, "title")==0) ||

                  (strcmp(par_nam, "onmouseover")==0) ||
                  (strcmp(par_nam, "onmouseout")==0) ||
                  (strcmp(par_nam, "style")==0) ||
                  (strcmp(par_nam, "lang")==0)
                 )
               {
                  if(strlen(par_val)==0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else
               {
// KP_TRACE_4("HtmtTestPars: %s *piEncMode:%d *piCodeTable:%d *piDefCodeTable:%d", tag_name, *piEncMode, *piCodeTable, *piDefCodeTable);
                  KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
            }
         }

      } // if(pTagParsObj!=NULL)

      break;

// <A href="abdicate.htm">
// <A name="abdicate"> - zyme kitai nuorodai
// <a href="slenkantis tekstas2.html" target="blank">
   case HTM_TG_A:
      if(pTagParsObj==NULL) KP_ERROR(KP_E_FILE_FORMAT, tag_name)
      else
      {
         retc=pTagParsObj->SeekTextPar("href", par_val, &par_num);
         if(retc==KP_E_KWD_NOT_FOUND)
         {
            retc=pTagParsObj->SeekTextPar("name", par_val, &par_num);
            if(retc==KP_E_KWD_NOT_FOUND) KP_WARNING(KP_E_FILE_FORMAT, tag_name);
         }

         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);

            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "href")==0)
                 )
               {
                  if(ii!=0) KP_WARNING(KP_E_FILE_FORMAT, par_nam);
                  if(SUCCEEDED(retc))
                  {
                     retc=pTagParsObj->SeekTextPar("name", par_val, &par_num);
                     if(SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val))
                     else if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                  }
               }
               else if(
                  (strcmp(par_nam, "name")==0)
                      )
               {
                  if(ii!=0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  if(SUCCEEDED(retc))
                  {
                     retc=pTagParsObj->SeekTextPar("href", par_val, &par_num);
                     if(SUCCEEDED(retc)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val))
                     else if(retc==KP_E_KWD_NOT_FOUND) retc=S_OK;
                  }
               }
               else if(
                  (strcmp(par_nam, "target")==0)
                      )
               {
                  if(
                     (strcmp(par_val, "blank")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                  (strcmp(par_nam, "onmouseover")==0) || // "onMouseOver"
                  (strcmp(par_nam, "onmouseout")==0)     // "onMouseOut"
                      )
               {
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }

            if(SUCCEEDED(retc))
               if(strlen(par_val)==0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
         }
      }
      break;

// <img src="img.gif" height="128" width="369" alt="abipusû lygiuotû.gif - 487 kb" border="0">
// <img src="../pav/kalendorius.gif" align="left" hspace="15" vspace="10"></p><p class="t">
// <img id="background" src="./p21_files/image001.jpg" width="720.000000" height="450.000000"/>
// <img width="190.000000" height="186.000000" src="./p21_0_files/image004.bmp" v:shapes="_x0000_i1127"/>
   case HTM_TG_IMG:
      if(pTagParsObj==NULL) KP_ERROR(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);

            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "src")==0)
                 )
               {
//                if(ii!=0) KP_WARNING(KP_E_FILE_FORMAT, par_nam);
               }
               else if(
                  (strcmp(par_nam, "height")==0) ||
                  (strcmp(par_nam, "width")==0) ||
                  (strcmp(par_nam, "hspace")==0) ||
                  (strcmp(par_nam, "vspace")==0) ||
                  (strcmp(par_nam, "alt")==0) ||
                  (strcmp(par_nam, "border")==0) ||

                  (strcmp(par_nam, "name")==0) ||
                  (strcmp(par_nam, "id")==0) ||
                  (strcmp(par_nam, "v:shapes")==0)
                      )
               {
               }
               else if(strcmp(par_nam, "align")==0)
               {
                  if(
                     (strcmp(par_val, "left")!=0) &&
                     (strcmp(par_val, "right")!=0) &&
                     (strcmp(par_val, "top")!=0) &&
                     (strcmp(par_val, "bottom")!=0) &&
                     (strcmp(par_val, "center")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "loop")==0)
               {
                  if(
                     (strcmp(par_val, "infinite")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }

            if(SUCCEEDED(retc))
               if(strlen(par_val)==0)
                  KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
         }
      }
      break;

// <hr width="80%" align="center" size="4" color="#00FF00">
   case HTM_TG_HR:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);

         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);

            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "size")==0)
                 )
               {
                  if(!TvIsNumber(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                  (strcmp(par_nam, "width")==0) ||
                  (strcmp(par_nam, "color")==0)
                      )
               {
               }
               else if(strcmp(par_nam, "align")==0)
               {
                  if(
                     (strcmp(par_val, "left")!=0) &&
                     (strcmp(par_val, "right")!=0) &&
                     (strcmp(par_val, "top")!=0) &&
                     (strcmp(par_val, "bottom")!=0) &&
                     (strcmp(par_val, "center")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else
                  KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }

            if(SUCCEEDED(retc))
               if(strlen(par_val)==0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
         }
      }
      break;

// <table border='1' align='center' cellpadding='2' >
// <table border="0" cellspacing="0" cellpadding="0" width="0">
// <TABLE BORDER="0" CELLSPACING="0" CELLPADDING="0" WIDTH="0">
// <table border="0" cellpadding="5" width="60%">
// <table border="1" cellspacing="0" cellpadding="2" width="500" bgcolor="FFFFFF">
// <table class=MsoNormalTable border=0 cellspacing=0 cellpadding=0 width=866 style='width:649.3pt;border-collapse:collapse;mso-padding-alt:0cm 5.4pt 0cm 5.4pt'>
   case HTM_TG_TABLE:
      if(pTagParsObj!=NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "border")==0) ||
                  (strcmp(par_nam, "cellpadding")==0) ||
                  (strcmp(par_nam, "cellspacing")==0)
                 )
               {
                  if(!TvIsNumber(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "align")==0)
               {
                  if(
                     (strcmp(par_val, "left")!=0) &&
                     (strcmp(par_val, "right")!=0) &&
                     (strcmp(par_val, "top")!=0) &&
                     (strcmp(par_val, "bottom")!=0) &&
                     (strcmp(par_val, "center")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                        (strcmp(par_nam, "width")==0) ||
                        (strcmp(par_nam, "style")==0) ||
                        (strcmp(par_nam, "class")==0)
                      )
               {
               }
               else if(strcmp(par_nam, "bgcolor")==0)
               {
                  if(!TvIsColor(par_val))
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }
         }

      } // if(pTagParsObj!=NULL)

      break;

// <tr style="height:12.800000pt;">
// <tr height="0.000000">
   case HTM_TG_TR:
      if(pTagParsObj!=NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "style") == 0) ||
                  (strcmp(par_nam, "height") == 0)
                 )
               {
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }
         }

      } // if(pTagParsObj!=NULL)

      break;

// <td width="100%">
// <td bgcolor=#c0c0c0>
// <td colspan=8>
// <td valign="top" rowspan=2>
// <td width="33.500000" style="width:25.300000pt; padding:0.000000cm 2.700000pt 0.000000cm 2.700000pt;" align="center">
   case HTM_TG_TD:
// <th bgcolor=#c0c0c0>
   case HTM_TG_TH:
      if(pTagParsObj!=NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "width")==0) ||
                  (strcmp(par_nam, "height")==0)
                 )
               {
//                if(!TvIsNumValue(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                        (strcmp(par_nam, "bgcolor")==0)
                      )
               {
                  if(!TvIsColor(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(
                        (strcmp(par_nam, "colspan")==0) ||
                        (strcmp(par_nam, "rowspan")==0)
                      )
               {
                  if(!TvIsNumber(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "valign") == 0)
               {
                  if(
                     (strcmp(par_val, "top")!=0) &&
                     (strcmp(par_val, "bottom")!=0) &&
                     (strcmp(par_val, "center")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "align") == 0)
               {
                  if(
                     (strcmp(par_val, "left")!=0) &&
                     (strcmp(par_val, "right")!=0) &&
                     (strcmp(par_val, "center")!=0)
                    )
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else if(strcmp(par_nam, "style") == 0)
               {
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }
         }

      } // if(pTagParsObj!=NULL)

      break;

   case HTM_TG_DIV:
      if(pTagParsObj!=NULL)
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
         {
            retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
            if(SUCCEEDED(retc))
            {
               if(
                  (strcmp(par_nam, "class")==0) ||
                  (strcmp(par_nam, "align")==0) ||
                  (strcmp(par_nam, "v:shape")==0) ||
                  (strcmp(par_nam, "style")==0)
                 )
               {
                  if(strlen(par_val)==0) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
               else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
            }
         }

      } // if(pTagParsObj!=NULL)

      break;

   case HTM_TG_UL:
      if(pTagParsObj==NULL)
      {
//       KP_WARNING(KP_E_FILE_FORMAT, tag_name);
      }
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt>2) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(strcmp(par_nam, "compact")==0)
                     {
                     }
                     else if(strcmp(par_nam, "type")==0)
                     {
                        if(
                           (strcmp(par_val, "disc")!=0) &&
                           (strcmp(par_val, "square")!=0) &&
                           (strcmp(par_val, "circle")!=0)
                          )
                           KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                     }
                     else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

   case HTM_TG_OL:
      if(pTagParsObj==NULL)
      {
//       KP_WARNING(KP_E_FILE_FORMAT, tag_name);
      }
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt>2) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(strcmp(par_nam, "compact")==0)
                     {
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                     }
                     else if(strcmp(par_nam, "start")==0)
                     {
                     }
                     else if(strcmp(par_nam, "type")==0)
                     {
                        if(
                           (strcmp(par_val, "A")!=0) &&
                           (strcmp(par_val, "a")!=0) &&
                           (strcmp(par_val, "I")!=0) &&
                           (strcmp(par_val, "i")!=0) &&
                           (strcmp(par_val, "1")!=0)
                          )
                           KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

   case HTM_TG_FONT:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt>3) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(strcmp(par_nam, "color")==0)
                     {
                     }
                     else if(strcmp(par_nam, "face")==0)
                     {
                     }
                     else if(strcmp(par_nam, "size")==0)
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

   case HTM_TG_MARQUEE:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt > 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii<par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(strcmp(par_nam, "bgcolor")==0)
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <o:shapedefaults v:ext="edit" spidmax="2050">
   case HTM_TG_o_shapedefaults:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "v:ext") == 0) ||
                        (strcmp(par_nam, "spidmax") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <o:colormenu v:ext="edit" fillcolor="none"/>
   case HTM_TG_o_colormenu:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 2) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "v:ext") == 0) ||
                        (strcmp(par_nam, "fillcolor") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <o:shapelayout v:ext="edit">
   case HTM_TG_o_shapelayout:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt != 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "v:ext") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <o:idmap v:ext="edit" data="1"/>
   case HTM_TG_o_idmap:
      if(pTagParsObj == NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt != 2) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "v:ext") == 0) ||
                        (strcmp(par_nam, "data") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:background id="_x0000_s1032" o:bwmode="white" o:targetscreensize="800,600">
   case HTM_TG_v_background:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "id") == 0) ||
                        (strcmp(par_nam, "o:bwmode") == 0) ||
                        (strcmp(par_nam, "o:targetscreensize") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:fill src="./p21_files/image002.png" o:title="fonas" type="frame"/>
   case HTM_TG_v_fill:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "src") == 0) ||
                        (strcmp(par_nam, "o:title") == 0) ||
                        (strcmp(par_nam, "type") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:shapetype id="_x0000_t202" coordsize="21600,21600" o:spt="202" path="m0,0l0,21600,21600,21600,21600,0xe">
// <v:shapetype id="_x0000_t75" coordsize="21600,21600" o:spt="75" o:preferrelative="t" path="m@4@5l@4@11@9@11@9@5xe" filled="f" stroked="f">
   case HTM_TG_v_shapetype:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "id") == 0) ||
                        (strcmp(par_nam, "coordsize") == 0) ||
                        (strcmp(par_nam, "o:spt") == 0) ||
                        (strcmp(par_nam, "o:preferrelative") == 0) ||
                        (strcmp(par_nam, "path") == 0) ||
                        (strcmp(par_nam, "filled") == 0) ||
                        (strcmp(par_nam, "stroked") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:stroke joinstyle="miter"/>
// <v:stroke endarrow="block"/>
   case HTM_TG_v_stroke:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "joinstyle") == 0) ||
                        (strcmp(par_nam, "endarrow") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:path gradientshapeok="t" o:connecttype="rect"/>
// <v:path o:extrusionok="f" gradientshapeok="t" o:connecttype="rect"/>
   case HTM_TG_v_path:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "gradientshapeok") == 0) ||
                        (strcmp(par_nam, "o:connecttype") == 0) ||
                        (strcmp(par_nam, "o:extrusionok") == 0) ||
                        (strcmp(par_nam, "gradientshapeok") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:shape id="_x0000_s1029" type="#_x0000_t202" style="position:absolute; left:0.000000; text-align:left; margin-left:-1.725000pt; margin-top:179.000000pt; width:519.525000pt; height:130.525000pt; z-index:1;"
//    filled="f" stroked="f">
// <v:shape id="_x0000_s1026" type="#_x0000_t202" style='position:absolute; margin-left:1.5pt;margin-top:421.5pt;width:666pt;height:36pt;z-index:1; mso-wrap-edited:f;mso-position-vertical-relative:line'
//    wrapcoords="-24 0 -24 21600 21624 21600 21624 0 -24 0" filled="f" stroked="f"/>
   case HTM_TG_v_shape:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "id") == 0) ||
                        (strcmp(par_nam, "type") == 0) ||
                        (strcmp(par_nam, "style") == 0) ||
                        (strcmp(par_nam, "filled") == 0) ||
                        (strcmp(par_nam, "stroked") == 0) ||
                        (strcmp(par_nam, "wrapcoords") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <w:wrap anchorx="page"/>
   case HTM_TG_w_wrap:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "anchorx") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:textbox style="mso-next-textbox:#_x0000_s1030;">
// <v:textbox inset=",3.3mm">
   case HTM_TG_v_textbox:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
            {
               retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
               if(SUCCEEDED(retc))
               {
                  if(
                     (strcmp(par_nam, "inset") == 0) ||
                     (strcmp(par_nam, "style") == 0)
                    )
                  {
                  }
                  else
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:f eqn="if lineDrawn pixelLineWidth 0"/>
   case HTM_TG_v_f:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "eqn") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <o:lock v:ext="edit" aspectratio="t"/>
   case HTM_TG_o_lock:
      if(pTagParsObj == NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "v:ext") == 0) ||
                        (strcmp(par_nam, "aspectratio") == 0)
                       )
                     {
                     }
                     else KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:imagedata src="./p21_files/image003.png" o:title="p21_1"/>
   case HTM_TG_v_imagedata:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "src") == 0) ||
                        (strcmp(par_nam, "o:title") == 0)
                       )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <input type="RADIO" name="a1" onclick="sel_task('p1', 'a1')"/>
// <input type="SUBMIT" value="1" name="p1" onclick="sel_task('p1', '')" style="color:blue;"/>
   case HTM_TG_INPUT:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if((strcmp(par_nam, "type") == 0))
                     {
                        strlwr(par_val);
                        if(
                           (strcmp(par_val, "submit") == 0) ||
                           (strcmp(par_val, "radio") == 0) ||
                           (strcmp(par_val, "text") == 0)
                          )
                        {
                        }
                        else
                           KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                     }
                     else if
                     (
                        (strcmp(par_nam, "name") == 0) ||
                        (strcmp(par_nam, "value") == 0) ||
                        (strcmp(par_nam, "onclick") == 0) ||
                        (strcmp(par_nam, "style") == 0) ||
                        (strcmp(par_nam, "size") == 0)
                     )
                     {
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:line id="_x0000_s1033" style="position:absolute; left:0.000000; text-align:left; z-index:3; mso-position-horizontal:absolute; mso-position-vertical:absolute;" from="302.55pt,160pt" to="617.55pt,241pt" coordsize="21600,21600" strokecolor="blue" strokeweight="3pt">
   case HTM_TG_v_line:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "id") == 0) ||
                        (strcmp(par_nam, "style") == 0) ||
                        (strcmp(par_nam, "from") == 0) ||
                        (strcmp(par_nam, "to") == 0) ||
                        (strcmp(par_nam, "coordsize") == 0) ||
                        (strcmp(par_nam, "strokeweight") == 0)
                       )
                     {
                     }
                     else if(strcmp(par_nam, "strokecolor") == 0)
                     {
                        if(!TvIsColor(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <v:oval id="_x0000_s1035" style="position:absolute; left:0.000000; text-align:left; margin-left:295.275000pt; margin-top:21.475000pt; width:1.000000in; height:49.500000pt; z-index:4; mso-position-horizontal:absolute; mso-position-vertical:absolute;" filled="f" strokecolor="red" strokeweight="3pt"/>
   case HTM_TG_v_oval:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            if(par_cnt < 1) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
            else
            {
               for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
               {
                  retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
                  if(SUCCEEDED(retc))
                  {
                     if(
                        (strcmp(par_nam, "id") == 0) ||
                        (strcmp(par_nam, "style") == 0) ||
                        (strcmp(par_nam, "filled") == 0) ||
                        (strcmp(par_nam, "strokeweight") == 0)
                       )
                     {
                     }
                     else if(strcmp(par_nam, "strokecolor") == 0)
                     {
                        if(!TvIsColor(par_val)) KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                     }
                     else
                        KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
                  }
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// MS Word HTML
// <w:LatentStyles DefLockedState="false" LatentStyleCount="156">
   case HTM_TG_w_LatentStyles:
      if(pTagParsObj == NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
            {
               retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
               if(SUCCEEDED(retc))
               {
                  if(
                     (strcmp(par_nam, "deflockedstate") == 0) ||
                     (strcmp(par_nam, "latentstylecount") == 0)
                    )
                  {
                  }
                  else
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// FlashPageFlip.com
// <object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=8,0,0,0" width="100%" height="100%">
   case HTM_TG_OBJECT:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
            {
               retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
               if(SUCCEEDED(retc))
               {
                  if(
                     (strcmp(par_nam, "classid") == 0) ||
                     (strcmp(par_nam, "codebase") == 0) ||
                     (strcmp(par_nam, "width") == 0) ||
                     (strcmp(par_nam, "height") == 0)
                    )
                  {
                  }
                  else
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// FlashPageFlip.com
// <param name="movie" value="swf/Magazine.swf" />
   case HTM_TG_PARAM:
      if(pTagParsObj==NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
            {
               retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
               if(SUCCEEDED(retc))
               {
                  if(
                     (strcmp(par_nam, "name") == 0) ||
                     (strcmp(par_nam, "value") == 0)
                    )
                  {
                  }
                  else
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

// FlashPageFlip.com
// <embed src="swf/Magazine.swf" width="100%" height="100%" quality="high" pluginspage="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" wmode="transparent" allowFullScreen="true" allowScriptAccess="sameDomain"></embed>
   case HTM_TG_EMBED:
      if(pTagParsObj == NULL) KP_WARNING(KP_E_FILE_FORMAT, tag_name)
      else
      {
         if(SUCCEEDED(retc)) retc=pTagParsObj->GetParCnt(&par_cnt);
         if(SUCCEEDED(retc))
         {
            for(ii=0; (ii < par_cnt) && SUCCEEDED(retc); ii++)
            {
               retc=pTagParsObj->GetTextPar(par_nam, par_val, ii);
               if(SUCCEEDED(retc))
               {
                  if(
                     (strcmp(par_nam, "src") == 0) ||
                     (strcmp(par_nam, "width") == 0) ||
                     (strcmp(par_nam, "height") == 0) ||
                     (strcmp(par_nam, "quality") == 0) ||
                     (strcmp(par_nam, "pluginspage") == 0) ||
                     (strcmp(par_nam, "type") == 0) ||
                     (strcmp(par_nam, "wmode") == 0) ||
                     (strcmp(par_nam, "allowfullscreen") == 0) ||
                     (strcmp(par_nam, "allowscriptaccess") == 0)
                    )
                  {
                  }
                  else
                     KP_WARNING(KP_E_FILE_FORMAT, HtmtFormatMsg(str_buf, tag_name, par_nam, par_val));
               }
            }
         }

      } // else // if(pTagParsObj==NULL)

      break;

   default:
      KP_WARNING(KP_E_FILE_FORMAT, tag_name);
      break;

#endif // #ifdef Debug

   } // switch(iChar)

   KP_DELETEA(par_val);
   KP_DELETEA(test_val);

return(retc);
}
