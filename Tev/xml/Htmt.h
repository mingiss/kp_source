// ==================================================
// htmt.h
// Html tag definitions
//

#ifndef htmt_included
#define htmt_included


#define XM_HTM_Charset_Prefix ((const unsigned char *)"text/html; charset=")
#define XM_XHTML_Charset_Prefix ((const unsigned char *)"application/xhtml+xml; charset=")

// --------------------------------------------------- HTML tags
#define HTM_TG_NumOfTags0 (HTM_TG_LastTag-HTM_TG_FirstTag)
#define HTM_TG_NumOfTags37 HTM_TG_NumOfTags0

#define HTM_TG_NoTag      (-1)

enum HTML_Chars                         // HTML tag characters
{
   HTM_TG_FirstTag       = XH_FirstHtmTagCode, // 6000
   
   HTM_TG_HTML           = XH_FirstHtmTagCode, // 6000
   HTM_TG_HTML_e,     /*  6001 */

   HTM_TG_P,          /*  6002 */
   HTM_TG_P_e,        /*  6003 */

   HTM_TG_SPAN,       /*  6004 */
   HTM_TG_SPAN_e,     /*  6005 */

   HTM_TG_HEAD,       /*  6006 */
   HTM_TG_HEAD_e,     /*  6007 */

   HTM_TG_TITLE,      /*  6008 */
   HTM_TG_TITLE_e,    /*  6009 */

   HTM_TG_META,       /*  6010 */
   HTM_TG_META_e,     /*  6011 */

   HTM_TG_STYLE,      /*  6012 */
   HTM_TG_STYLE_e,    /*  6013 */

      HTM_TG_Comment_obs,    /*  6014 */ // obsolete, moved to XL_Comment
      HTM_TG_Comment_obs_e,  /*  6015 */

      HTM_TG_DOCTYPE_obs,    /*  6016 */ // obsolete, moved to XL_DocType
      HTM_TG_DOCTYPE_obs_e,  /*  6017 */

   HTM_TG_SCRIPT,     /*  6018 */
   HTM_TG_SCRIPT_e,   /*  6019 */

   HTM_TG_BODY,       /*  6020 */
   HTM_TG_BODY_e,     /*  6021 */

   HTM_TG_LINK,       /*  6022 */
   HTM_TG_LINK_e,     /*  6023 */

   HTM_TG_SUP,        /*  6024 */
   HTM_TG_SUP_e,      /*  6025 */

   HTM_TG_A,          /*  6026 */
   HTM_TG_A_e,        /*  6027 */

   HTM_TG_TABLE,      /*  6028 */
   HTM_TG_TABLE_e,    /*  6029 */
   HTM_TG_TR,         /*  6030 */
   HTM_TG_TR_e,       /*  6031 */
   HTM_TG_TD,         /*  6032 */
   HTM_TG_TD_e,       /*  6033 */

   HTM_TG_BR,         /*  6034 */
   HTM_TG_BR_e,       /*  6035 */

   HTM_TG_TBODY,      /*  6036 */
   HTM_TG_TBODY_e,    /*  6037 */

   HTM_TG_IMG,        /*  6038 */
   HTM_TG_IMG_e,      /*  6039 */

   HTM_TG_TH,         /*  6040 */
   HTM_TG_TH_e,       /*  6041 */

   HTM_TG_NOBR,       /*  6042 */
   HTM_TG_NOBR_e,     /*  6043 */

   HTM_TG_B,          /*  6044 */
   HTM_TG_B_e,        /*  6045 */

   HTM_TG_DIV,        /*  6046 */
   HTM_TG_DIV_e,      /*  6047 */

   HTM_TG_PRE,        /*  6048 */
   HTM_TG_PRE_e,      /*  6049 */

   HTM_TG_FONT,       /*  6050 */
   HTM_TG_FONT_e,     /*  6051 */

   HTM_TG_I,          /*  6052 */
   HTM_TG_I_e,        /*  6053 */

   HTM_TG_SUB,        /*  6054 */
   HTM_TG_SUB_e,      /*  6055 */

   HTM_TG_TT,         /*  6056 */
   HTM_TG_TT_e,       /*  6057 */

   HTM_TG_HR,         /*  6058 */
   HTM_TG_HR_e,       /*  6059 */

   HTM_TG_UL,         /*  6060 */
   HTM_TG_UL_e,       /*  6061 */

   HTM_TG_LI,         /*  6062 */
   HTM_TG_LI_e,       /*  6063 */

   HTM_TG_CENTER,     /*  6064 */
   HTM_TG_CENTER_e,   /*  6065 */

   HTM_TG_CAPTION,    /*  6066 */  // lenteles kepure
   HTM_TG_CAPTION_e,  /*  6067 */

   HTM_TG_SAMP,       /*  6068 */  // kodo pavyzdziai
   HTM_TG_SAMP_e,     /*  6069 */

   HTM_TG_BIG,        /*  6070 */  // tekstas stambiom raidem
   HTM_TG_BIG_e,      /*  6071 */

   HTM_TG_FORM,       /*  6072 */
   HTM_TG_FORM_e,     /*  6073 */

   HTM_TG_INPUT,      /*  6074 */
   HTM_TG_INPUT_e,    /*  6075 */

   HTM_TG_OBJECT,     /*  6076 */
   HTM_TG_OBJECT_e,   /*  6077 */

   HTM_TG_EMBED,      /*  6078 */
   HTM_TG_EMBED_e,    /*  6079 */

   HTM_TG_IFRAME,     /*  6080 */
   HTM_TG_IFRAME_e,   /*  6081 */

   HTM_TG_MARQUEE,    /*  6082 */
   HTM_TG_MARQUEE_e,  /*  6083 */

   HTM_TG_CODE,       /*  6084 */
   HTM_TG_CODE_e,     /*  6085 */

   HTM_TG_OL,         /*  6086 */
   HTM_TG_OL_e,       /*  6087 */

   HTM_TG_H1,         /*  6088 */
   HTM_TG_H1_e,       /*  6089 */

   HTM_TG_H2,         /*  6090 */
   HTM_TG_H2_e,       /*  6091 */

   HTM_TG_H3,         /*  6092 */
   HTM_TG_H3_e,       /*  6093 */

   HTM_TG_H4,         /*  6094 */
   HTM_TG_H4_e,       /*  6095 */

   HTM_TG_H5,         /*  6096 */
   HTM_TG_H5_e,       /*  6097 */

   HTM_TG_H6,         /*  6098 */
   HTM_TG_H6_e,       /*  6099 */

// MS Word HTML
   HTM_TG_xml,             /*  6100 */
   HTM_TG_xml_e,           /*  6101 */

   HTM_TG_o_DocumentProperties,     /*  6102 */
   HTM_TG_o_DocumentProperties_e,   /*  6103 */

   HTM_TG_o_Author,        /*  6104 */
   HTM_TG_o_Author_e,      /*  6105 */

   HTM_TG_o_LastAuthor,    /*  6106 */
   HTM_TG_o_LastAuthor_e,  /*  6107 */

   HTM_TG_o_Revision,      /*  6108 */
   HTM_TG_o_Revision_e,    /*  6109 */

   HTM_TG_o_TotalTime,     /*  6110 */
   HTM_TG_o_TotalTime_e,   /*  6111 */

   HTM_TG_o_Created,       /*  6112 */
   HTM_TG_o_Created_e,     /*  6113 */

   HTM_TG_o_LastSaved,     /*  6114 */
   HTM_TG_o_LastSaved_e,   /*  6115 */

   HTM_TG_o_Pages,         /*  6116 */
   HTM_TG_o_Pages_e,       /*  6117 */

   HTM_TG_o_Characters,    /*  6118 */
   HTM_TG_o_Characters_e,  /*  6119 */

   HTM_TG_o_Company,       /*  6120 */
   HTM_TG_o_Company_e,     /*  6121 */

   HTM_TG_o_Lines,         /*  6122 */
   HTM_TG_o_Lines_e,       /*  6123 */

   HTM_TG_o_Paragraphs,    /*  6124 */
   HTM_TG_o_Paragraphs_e,  /*  6125 */

   HTM_TG_o_CharactersWithSpaces,   /*  6126 */
   HTM_TG_o_CharactersWithSpaces_e, /*  6127 */

   HTM_TG_o_Version,       /*  6128 */
   HTM_TG_o_Version_e,     /*  6129 */


   HTM_TG_o_shapedefaults,    /*  6130 */
   HTM_TG_o_shapedefaults_e,  /*  6131 */

   HTM_TG_o_colormenu,     /*  6132 */
   HTM_TG_o_colormenu_e,   /*  6133 */

   HTM_TG_o_shapelayout,   /*  6134 */
   HTM_TG_o_shapelayout_e, /*  6135 */

   HTM_TG_o_idmap,         /*  6136 */
   HTM_TG_o_idmap_e,       /*  6137 */


   HTM_TG_v_background,    /*  6138 */
   HTM_TG_v_background_e,  /*  6139 */

   HTM_TG_v_fill,          /*  6140 */
   HTM_TG_v_fill_e,        /*  6141 */

   HTM_TG_v_shapetype,     /*  6142 */
   HTM_TG_v_shapetype_e,   /*  6143 */

   HTM_TG_v_stroke,        /*  6144 */
   HTM_TG_v_stroke_e,      /*  6145 */

   HTM_TG_v_path,          /*  6146 */
   HTM_TG_v_path_e,        /*  6147 */

   HTM_TG_v_shape,         /*  6148 */
   HTM_TG_v_shape_e,       /*  6149 */

   HTM_TG_w_wrap,          /*  6150 */
   HTM_TG_w_wrap_e,        /*  6151 */

   HTM_TG_v_textbox,       /*  6152 */
   HTM_TG_v_textbox_e,     /*  6153 */

   HTM_TG_o_p,             /*  6154 */
   HTM_TG_o_p_e,           /*  6155 */

   HTM_TG_v_formulas,      /*  6156 */
   HTM_TG_v_formulas_e,    /*  6157 */

   HTM_TG_v_f,             /*  6158 */
   HTM_TG_v_f_e,           /*  6159 */

   HTM_TG_o_lock,          /*  6160 */
   HTM_TG_o_lock_e,        /*  6161 */

   HTM_TG_v_imagedata,     /*  6162 */
   HTM_TG_v_imagedata_e,   /*  6163 */

   HTM_TG_v_line,          /*  6164 */
   HTM_TG_v_line_e,        /*  6165 */

   HTM_TG_v_oval,          /*  6166 */
   HTM_TG_v_oval_e,        /*  6167 */

   HTM_TG_w_WordDocument,     /*  6168 */
   HTM_TG_w_WordDocument_e,   /*  6169 */

   HTM_TG_w_FormsDesign,   /*  6170 */
   HTM_TG_w_FormsDesign_e, /*  6171 */

   HTM_TG_o_Words,         /*  6172 */
   HTM_TG_o_Words_e,       /*  6173 */

   HTM_TG_w_ValidateAgainstSchemas,             /*  6174 */
   HTM_TG_w_ValidateAgainstSchemas_e,           /*  6175 */

   HTM_TG_w_SaveIfXMLInvalid,                   /*  6176 */
   HTM_TG_w_SaveIfXMLInvalid_e,                 /*  6177 */

   HTM_TG_w_IgnoreMixedContent,                 /*  6178 */
   HTM_TG_w_IgnoreMixedContent_e,               /*  6179 */

   HTM_TG_w_AlwaysShowPlaceholderText,          /*  6180 */
   HTM_TG_w_AlwaysShowPlaceholderText_e,        /*  6181 */

   HTM_TG_w_Compatibility,                      /*  6182 */
   HTM_TG_w_Compatibility_e,                    /*  6183 */

   HTM_TG_w_SelectEntireFieldWithStartOrEnd,    /*  6184 */
   HTM_TG_w_SelectEntireFieldWithStartOrEnd_e,  /*  6185 */

   HTM_TG_w_UseWord2002TableStyleRules,         /*  6186 */
   HTM_TG_w_UseWord2002TableStyleRules_e,       /*  6187 */

   HTM_TG_w_BrowserLevel,                       /*  6188 */
   HTM_TG_w_BrowserLevel_e,                     /*  6189 */

   HTM_TG_w_LatentStyles,                       /*  6190 */
   HTM_TG_w_LatentStyles_e,                     /*  6191 */
      
   HTM_TG_w_SpellingState,                      /*  6192 */
   HTM_TG_w_SpellingState_e,                    /*  6193 */

   HTM_TG_w_GrammarState,                       /*  6194 */
   HTM_TG_w_GrammarState_e,                     /*  6195 */

   HTM_TG_THEAD,                                /*  6196 */
   HTM_TG_THEAD_e,                              /*  6197 */
   
   HTM_TG_TFOOT,                                /*  6198 */
   HTM_TG_TFOOT_e,                              /*  6199 */

   HTM_TG_NOSCRIPT,                             /*  6200 */
   HTM_TG_NOSCRIPT_e,                           /*  6201 */

   HTM_TG_PARAM,                                /*  6202 */
   HTM_TG_PARAM_e,                              /*  6203 */

   HTM_TG_LastTag
};

//=================================================== htmt data arrays
extern const unsigned char *plpszaHtmlTags[HTM_TG_NumOfTags0 + 1]; // HTML tag names

extern const int iaHtmNulCodeTables[HTM_TG_NumOfTags0]; // HTML Unicode file fictive code tables
extern const int iaHtmCodeTables71[HTM_TG_NumOfTags0]; // HTML Windows 1257 file code tables

extern const KpChar uiazHtmlGrTags[];  // grupiniø gairiø sàraðas, prieð jas lauþiama eilutë

//=================================================== htmt free functions
HRESULT PutHtmHat
(
   TvXmlFile *pOutFile,
   const unsigned char *lpszTitle,
   const unsigned char *lpszIcon,
   const unsigned char *lpszCSS,
   int iLang,  // kalba, KP_LNG_LIT etc.
   int iRefresh, // >0 - refreshinti puslapi kas iRefresh sekundziu
   const unsigned char *lpszPageStyle,
   const unsigned char *lpszJavaScript
);
HRESULT PutXhtmlHat
(
   TvXmlFile *pOutFile,
   const unsigned char *lpszTitle,
   const unsigned char *lpszIcon,
   const unsigned char *lpszCSS,
   int iLang,  // kalba, KP_LNG_LIT etc.
   int iRefresh, // >0 - refreshinti puslapi kas iRefresh sekundziu
   const unsigned char *lpszPageStyle,
   const unsigned char *lpszJavaScript
);
HRESULT PutHtmTail(TvXmlFile *pOutFile);

// parse from DTD, move to xmlf together with XmltTestEmbedded()
extern HRESULT HtmtTestEmbedded(int iChar, int iParentTag, bool *bEmbFlPtr); // parse from DTD !!!

// checks some tag parameters
// on entering *piEncMode, *piCodeTable && *piDefCodeTable must be set to legal (previous) values
extern HRESULT HtmtTestPars(int iChar, XmlTagPars *pTagParsObj, UC_Modes *piEncMode, int *piCodeTable, int *piDefCodeTable,
                  const unsigned char * const *plpszTagNames = NULL, KpChar iFirstDictTag = C_Nul, KpChar iLastDictTag = C_Nul);

#endif
