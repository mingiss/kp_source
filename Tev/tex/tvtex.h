// ==================================================
// tvtex.h
// TEX file definitions


#ifndef tvtex_included
#define tvtex_included


// =================================================== definitions
#define TX_CHAR_POS_THRESHOLD 60
#define TX_UNGET_BUF_SIZ KP_MAX_FILE_LIN_WDT // (10 /*TV_MSG_LEN + TV_TAG_LEN*/ /*TX_CHAR_POS_THRESHOLD*/)


extern const unsigned char lpszTexCtrlChars[];
extern const unsigned char lpszTexKwdDelim[];

// --------------------------------------------------
// spec. chars of TEX file
#define TX_CH_KeywordStart ('\\')
#define TX_CH_CommentStart ('%')
#define TX_CH_FieldStart   ('{')
#define TX_CH_FieldEnd     ('}')
#define TX_CH_MathField    ('$')
#define TX_CH_Hash         ('#')
#define TX_CH_Amp          ('&')
#define TX_CH_UnderL       ('_')
#define TX_CH_Eq           ('=')
#define TX_CH_Apost        ('\'')
#define TX_CH_Quot         ('\"')
#define TX_CH_Grave        ('`')
#define TX_CH_At           ('@')
#define TX_CH_Circ         ('^')

#define TX_CH_Ast          ('*') // aklz minion ðrifte paprasta þvaigþdutë penkiakampë - reikia komandos

#define TX_CH_NBSP         ('~')
#define TX_CH_Lf           ('\n')

#define TX_FirstSpecCharCode  (9000)    // code of first spec. char

typedef enum
{
   TX_SP_FirstSpChar                   =TX_FirstSpecCharCode,

   TX_SP_KeywordStart   /* ('\\')   // 9000 */   =TX_FirstSpecCharCode,
   TX_SP_CommentStart,  // ('%')    // 9001
   TX_SP_FieldStart,    // ('{')    // 9002
   TX_SP_FieldEnd,      // ('}')    // 9003
   TX_SP_MathField,     // ('$')    // 9004
   TX_SP_Hash,          // ('#')    // 9005
   TX_SP_Amp,           // ('&')    // 9006
   TX_SP_UnderL,        // ('_')    // 9007
   TX_SP_Eq,            // ('=')    // 9008
   TX_SP_Apost,         // ('\'')   // 9009
   TX_SP_Quot,          // ('\"')   // 9010
   TX_SP_Grave,         // ('`')    // 9011
   TX_SP_At,            // ('@')    // 9012
   TX_SP_Circ,          // ('^')    // 9013

   TX_SP_NBSP,          // ('~')    // 9014
   TX_SP_Lf,            // ('\n')   // 9015

// xmlnx text formatting chars as normal TEX commands to skip formatter level converter
   TX_SP_Lslash,        // ('\\')   // 9016
   TX_SP_Numb,          // ('#')    // 9017
   TX_SP_Doll,          // ('$')    // 9018

   TX_SP_Lbrack,        // ('[')    // 9019
   TX_SP_Rbrack,        // (']')    // 9020
   TX_SP_Lcurl,         // ('{')    // 9021
   TX_SP_Rcurl,         // ('}')    // 9022

   TX_SP_LastSpChar

} TX_SpecChars;

#define TX_FirstMainTagCode   (10000)   // code of first entry of plpszaMainTexTagTable
                                        //    as character
#define TX_FirstUserTagCode   (12000)   // code of first entry of plpszaUserTexTagTable as character
#define TX_LastUserTagCode    (13999)   // last code

#define TX_TG_NumOfTags0 (TX_TG_LastTag-TX_TG_FirstTag)
#define TX_TG_NumOfTags132 TX_TG_NumOfTags0

typedef enum
{
   TX_TG_Unknown,

   TX_TG_FirstTag    =TX_FirstMainTagCode,

   TX_TG_input       =TX_FirstMainTagCode,  // 10000 // \input init.sty  // include external (style) definitions
   TX_TG_firstpage,        // 10001 // \firstpage=1  // define first page
   TX_TG_lastpage,         // 10002
   TX_TG_HPROOF,           // 10003 // \HPROOF  // switch on frame border
   TX_TG_PROOF,            // 10004
   TX_TG_CRC,              // 10005 // \CRC  // switch on frame edge marks (?)
   TX_TG_VIEW,             // 10006
   TX_TG_setparameters,    // 10007
   TX_TG_lang,             // 10008
   TX_TG_heada,            // 10009 // \heada{...} // define chapter (?) title and right running header
   TX_TG_titletrue,        // 10010

   TX_TG_ctbl_off,         // 10011 // \ctbl_off  // switch off any code table
   TX_TG_rm,               // 10012 // \rm  // switch to roman font
   TX_TG_rmr,              // 10013 // \rmr  // switch to russian roman font
   TX_TG_got,              // 10014 // \got  // switch to gothic
   TX_TG_cal,              // 10015 // \cal  // switch to calligraphic

   TX_TG_bf,               // 10016 // \bf  // switch to bold font
   TX_TG_it,               // 10017 // \it  // switch to italic font
   TX_TG_mit,              // 10018 // \mit  // switch to math. italic font

   TX_TG_endpaper,         // 10019
   TX_TG_loadgottrue,      // 10020 // \loadgottrue  // load gothic font

   TX_TG_over,             // 10021
   TX_TG_sqrt,             // 10022 // \sqrt
   TX_TG_root,             // 10023 // \root
   TX_TG_of,               // 10024 // \of

   TX_TG_hat,              // 10025 // \hat
   TX_TG_check,            // 10026 // \check
   TX_TG_tilde,            // 10027 // \tilde
   TX_TG_acute,            // 10028 // \acute
   TX_TG_grave,            // 10029 // \grave
   TX_TG_dot,              // 10030 // \dot
   TX_TG_ddot,             // 10031 // \ddot
   TX_TG_breve,            // 10032 // \breve
   TX_TG_bar,              // 10033 // \bar
   TX_TG_vec,              // 10034 // \vec
   TX_TG_not,              // 10035 // \not

   TX_TG_big,              // 10036
   TX_TG_bigl,             // 10037
   TX_TG_bigr,             // 10038
   TX_TG_Big,              // 10039
   TX_TG_Bigl,             // 10040
   TX_TG_Bigr,             // 10041
   TX_TG_bigg,             // 10042
   TX_TG_biggr,            // 10043
   TX_TG_biggl,            // 10044
   TX_TG_Bigg,             // 10045
   TX_TG_Biggr,            // 10046
   TX_TG_Biggl,            // 10047

//!!! TX_TG_leq,                    // \leq    <=
   TX_TG_geq,              // 10048 // \geq    >=
   TX_TG_neq,              // 10049 // \neq    =/

   TX_TG_lbrace,           // 10050 // \lbrace  {
   TX_TG_rbrace,           // 10051 // \rbrace  }
   TX_TG_lbrack,           // 10052 // \lbrack  [
   TX_TG_rbrack,           // 10053 // \rbrack  ]

   TX_TG_to,               // 10054 // \to -->
   TX_TG_gets,             // 10055 // \gets <--
   TX_TG_owns,             // 10056 // \owns C_epsilon_var apsukta
   TX_TG_land,             // 10057 // logical and, \land C_wedge
   TX_TG_lor,              // 10058 // logical or, \lor C_vee
   TX_TG_lnot,             // 10059 // logical not, \neg C_Rminbr
   TX_TG_vert,             // 10060 // \vert C_Vertl
   TX_TG_Vert,             // 10061 // \Vert C_paral
   TX_TG_paral,            // 10062 // \| C_paral

   TX_TG_forc_sp,          // 10063 // >>>\ <<<  // forced space "\\ ",

   TX_TG_def,              // 10064 // \def // define macro

   TX_TG_pageno,           // 10065 // \pageno

   TX_TG_begindoublecolumns, // 10066 // \begindoublecolumns

   TX_TG_Ad,               // 10067 // \Ad  // C_A_Acute
   TX_TG_ad,               // 10068 // \ad  // C_a_Acute
   TX_TG_And,              // 10069 // \And  // C_A_Ogon_Acute
   TX_TG_and,              // 10070 // \and  // C_a_Ogon_Acute
   TX_TG_Ed,               // 10071 // \Ed  // C_E_Acute
   TX_TG_ed,               // 10072 // \ed  // C_e_Acute
   TX_TG_End__,            // 10073 // \End  // C_E_Ogon_Acute
   TX_TG_end__,            // 10074 // \end  // C_e_Ogon_Acute
   TX_TG_Etd,              // 10075 // \Etd  // C_E_Adot_Acute
   TX_TG_etd,              // 10076 // \etd  // C_e_Adot_Acute
   TX_TG_Id,               // 10077 // \Id  // C_I_Acute
   TX_TG_id,               // 10078 // \id  // C_i_Acute
   TX_TG_Ind,              // 10079 // \Ind  // C_I_Ogon_Acute
   TX_TG_ind,              // 10080 // \ind  // C_i_Ogon_Acute
   TX_TG_Od,               // 10081 // \Od  // C_O_Acute
   TX_TG_od,               // 10082 // \od  // C_o_Acute
   TX_TG_Ud,               // 10083 // \Ud  // C_U_Acute
   TX_TG_ud,               // 10084 // \ud  // C_u_Acute
   TX_TG_Und,              // 10085 // \Und  // C_U_Ogon_Acute
   TX_TG_und,              // 10086 // \und  // C_u_Ogon_Acute
   TX_TG_Ubd,              // 10087 // \Ubd  // C_U_Macr_Acute
   TX_TG_ubd,              // 10088 // \ubd  // C_u_Macr_Acute
   TX_TG_Yd,               // 10089 // \Yd  // C_Y_Acute
   TX_TG_yd,               // 10090 // \yd  // C_y_Acute
   TX_TG_Ak,               // 10091 // \Ak  // C_A_Grave
   TX_TG_ak,               // 10092 // \ak  // C_a_Grave
   TX_TG_Ank,              // 10093 // \Ank  // C_A_Ogon_Grave
   TX_TG_ank,              // 10094 // \ank  // C_a_Ogon_Grave
   TX_TG_Ek,               // 10095 // \Ek  // C_E_Grave
   TX_TG_ek,               // 10096 // \ek  // C_e_Grave
   TX_TG_Enk,              // 10097 // \Enk  // C_E_Ogon_Grave
   TX_TG_enk,              // 10098 // \enk  // C_e_Ogon_Grave
   TX_TG_Etk,              // 10099 // \Etk  // C_E_Adot_Grave
   TX_TG_etk,              // 10100 // \etk  // C_e_Adot_Grave
   TX_TG_Ik,               // 10101 // \Ik  // C_I_Grave
   TX_TG_ik,               // 10102 // \ik  // C_i_Grave
   TX_TG_Ink,              // 10103 // \Ink  // C_I_Ogon_Grave
   TX_TG_ink,              // 10104 // \ink  // C_i_Ogon_Grave
   TX_TG_Ok,               // 10105 // \Ok  // C_O_Grave
   TX_TG_ok,               // 10106 // \ok  // C_o_Grave
   TX_TG_Uk,               // 10107 // \Uk  // C_U_Grave
   TX_TG_uk,               // 10108 // \uk  // C_u_Grave
   TX_TG_Unk,              // 10109 // \Unk  // C_U_Ogon_Grave
   TX_TG_unk,              // 10110 // \unk  // C_u_Ogon_Grave
   TX_TG_Ubk,              // 10111 // \Ubk  // C_U_Macr_Grave
   TX_TG_ubk,              // 10112 // \ubk  // C_u_Macr_Grave
   TX_TG_Yk,               // 10113 // \Yk  // C_Y_Grave
   TX_TG_yk,               // 10114 // \yk  // C_y_Grave
   TX_TG_Ar,               // 10115 // \Ar  // C_A_Tilde
   TX_TG_ar,               // 10116 // \ar  // C_a_Tilde
   TX_TG_Anr,              // 10117 // \Anr  // C_A_Ogon_Tilde
   TX_TG_anr,              // 10118 // \anr  // C_a_Ogon_Tilde
   TX_TG_Er,               // 10119 // \Er  // C_E_Tilde
   TX_TG_er,               // 10120 // \er  // C_e_Tilde
   TX_TG_Enr,              // 10121 // \Enr  // C_E_Ogon_Tilde
   TX_TG_enr,              // 10122 // \enr  // C_e_Ogon_Tilde
   TX_TG_Etr,              // 10123 // \Etr  // C_E_Adot_Tilde
   TX_TG_etr,              // 10124 // \etr  // C_e_Adot_Tilde
   TX_TG_Ir,               // 10125 // \Ir  // C_I_Tilde
   TX_TG_ir,               // 10126 // \ir  // C_i_Tilde
   TX_TG_Inr,              // 10127 // \Inr  // C_I_Ogon_Tilde
   TX_TG_inr,              // 10128 // \inr  // C_i_Ogon_Tilde
   TX_TG_Or,               // 10129 // \Or  // C_O_Tilde
   TX_TG_or,               // 10130 // \or  // C_o_Tilde
   TX_TG_Ur,               // 10131 // \Ur  // C_U_Tilde
   TX_TG_ur,               // 10132 // \ur  // C_u_Tilde
   TX_TG_Unr,              // 10133 // \Unr  // C_U_Ogon_Tilde
   TX_TG_unr,              // 10134 // \unr  // C_u_Ogon_Tilde
   TX_TG_Ubr,              // 10135 // \Ubr  // C_U_Macr_Tilde
   TX_TG_ubr,              // 10136 // \ubr  // C_u_Macr_Tilde
   TX_TG_Yr,               // 10137 // \Yr  // C_Y_Tilde
   TX_TG_yr,               // 10138 // \yr  // C_y_Tilde
   TX_TG_Lr,               // 10139 // \Lr  // C_L_Tilde
   TX_TG_lr,               // 10140 // \lr  // C_l_Tilde
   TX_TG_Mr,               // 10141 // \Mr  // C_M_Tilde
   TX_TG_mr,               // 10142 // \mr  // C_m_Tilde
   TX_TG_Nr,               // 10143 // \Nr  // C_N_Tilde
   TX_TG_nr,               // 10144 // \nr  // C_n_Tilde
   TX_TG_Rr,               // 10145 // \Rr  // C_R_Tilde
   TX_TG_rr,               // 10146 // \rr  // C_r_Tilde

   TX_TG_romb,             // 10147 // \romb  // = C_Diamond
   TX_TG_bb,               // 10148 // \bb  // = C_simeq

   TX_TG_kid,              // 10149 // \kid  // = C_Acute
   TX_TG_Ndash,            // 10150 // \Ndash  // = C_EnDash
   TX_TG_V,                // 10151 // \V  // = C_paral
   TX_TG_kam,              // 10152 // \kam  // = C_LBquote, /* ,,    (left bellow, double comma, liet. kaire) */
   TX_TG_kav,              // 10153 // \kav  // = C_Rquote,  /* ``    (right, reversed double comma above, liet. desine, angl. kaire) */

   TX_TG_enddoublecolumns, // 10154
   TX_TG_end,              // 10155

   TX_TG_et,               // 10156 // \et  // = C_e_Adot
   TX_TG_ub,               // 10157 // \ub  // = C_u_Macr
   TX_TG_an,               // 10158 // \an  // = C_a_Ogon
   TX_TG_en,               // 10159 // \en  // = C_e_Ogon
   TX_TG_in,               // 10160 // \in  // = C_i_Ogon   // does not exist !!!
   TX_TG_ino,              // 10161 // \ino // = C_i_Ogon
   TX_TG_un,               // 10162 // \un  // = C_u_Ogon

   TX_TG_eject,            // 10163 // \eject  // pagebreak
   TX_TG_zmark,            // 10164

   TX_TG_ls,               // 10165 // \ls  // ~~ C_le, istriza lygybe
   TX_TG_gs,               // 10166 // \gs  // ~~ C_ge, istriza lygybe

   TX_TG_looseness,        // 10167
   TX_TG_hbox,             // 10168
   TX_TG_em,               // 10169 // \em{...}  // like TX_TG_it - switch to italic, only for parameter

   TX_TG_psl,              // 10170

   TX_TG_MT,               // 10171

   TX_TG_vadjust,          // 10172

   TX_TG_NegQemSpc,        // 10173

   TX_TG_scriptstyle,      // 10174
   TX_TG_scriptscriptstyle,// 10175

   TX_TG_u_Brev,           // 10176 // \u_Brev ??? // = C_u_Brev

   TX_TG_loadscrtrue,      // 10177 // \loadgottrue  // load handscript font

   TX_TG_Project,          // 10178 // %Project=PROJID
   TX_TG_Publisher,        // 10179 // %Publisher=PUBLISHER
   TX_TG_typesetterid,     // 10180
   TX_TG_paperid,          // 10181
   TX_TG_statusno,         // 10182
   TX_TG_switch,           // 10183

   TX_TG_long,             // 10184
   TX_TG_noindent,         // 10185

   TX_TG_insertplot,       // 10186
   TX_TG_position,         // 10187
   TX_TG_bottom,           // 10188
   TX_TG_pheight,          // 10189
   TX_TG_pwidth,           // 10190
   TX_TG_pprocent,         // 10191
   TX_TG_ptype,            // 10192
   TX_TG_pname,            // 10193
   TX_TG_ptext,            // 10194
   TX_TG_pfile,            // 10195
   TX_TG_pcorrections,     // 10196
   TX_TG_pvacor,           // 10197
   TX_TG_endinsertplot,    // 10198
   TX_TG_UNI,              // 10199

   TX_TG_bfi,              // 10200 // \bfi  // switch to bold italic font

   TX_TG_leftskip,         // 10201

   TX_TG_BTH,              // 10202 // start of table definition
   TX_TG_tableno,          // 10203 // \tableno=1  // table order no
   TX_TG_tname,            // 10204 // \tname=text // table heading
   TX_TG_tposition,        // 10205 // \tposition=\there
   TX_TG_tcorrections,     // 10206 // \tcorrections
   TX_TG_ETH,              // 10207 // end of table definition
   TX_TG_BTF,              // 10208 // start of column definition
   TX_TG_LC,               // 10209 // \LC{4.8cm}|\LC{0.3cm}|\LC{4.8cm} // column widths
   TX_TG_ETF,              // 10210 // end of column definition
   TX_TG_BrightHorLine,    // 10211 // \=
   TX_TG_BR,               // 10212 // start of row
   TX_TG_ThinHorLine,      // 10213 // \_
   TX_TG_CVB,              // 10214 // cell text, may be also free text, without \CVB
   TX_TG_NextColumn,       // 10215 // \| // column delimiter // ==TX_TG_paral !!!
   TX_TG_ER,               // 10216 // end of row
   TX_TG_NVS,              // 10217 // \NVS{6pt}   // verticl skip
   TX_TG_EOT,              // 10218 // \EOT{\vskip-12pt} // end of table

// objekto pozicija (pvz., po \tposition)
   TX_TG_after,            // 10219 // po
   TX_TG_top,              // 10220 // virsuje
   TX_TG_mid,              // 10221 // cia?
   TX_TG_there,            // 10222 // cia!
// TX_TG_bottom,                    // apacioje
   TX_TG_full,             // 10223 // visas puslapis
   TX_TG_bpage,            // 10224 // pirma puslapyje
   TX_TG_mpage,            // 10225 // puslapio viduryje
   TX_TG_epage,            // 10226 // paskutine puslapyje
   TX_TG_tvacor,           // 10227 // \tvacor=
   TX_TG_tvbcor,           // 10228 // \tvbcor=
   TX_TG_tvccor,           // 10229 // \tvccor=
   TX_TG_tvdcor,           // 10230 // \tvdcor=

   TX_TG_vskip,            // 10231 // \vskip50pt  // skip vertically
   TX_TG_hskip,            // 10232 // \hskip6cm   // skip horizontally

   TX_TG_captionbottomtrue,// 10233

   TX_TG_alistind,         // 10234
   TX_TG_alist,            // 10235
   TX_TG_endlist,          // 10236

   TX_TG_vfill,            // 10237 // fill page end with empty lines (before \eject), do not adjust bottom of the page
   TX_TG_break,            // 10238 // linebreak, not end ot the paragraph
   TX_TG_hfill,            // 10239 // fill end of the line with spaces (before \break), do not adjust right border of the line

// picture formats
   TX_TG_None,             // 10240
// TX_TG_UNI,
   TX_TG_HPX,              // 10241
   TX_TG_PCZ,              // 10242
   TX_TG_PS,               // 10243

// picture corrections po \pcorrections
   TX_TG_phcor,            // 10244
// TX_TG_pvacor,
   TX_TG_pvbcor,           // 10245
   TX_TG_pvccor,           // 10246

   TX_TG_newfam,           // 10247
   TX_TG_cyrfam,           // 10248
   TX_TG_font,             // 10249 // define font (name+size)
                                    // \font\twelvepoint=dctira at 12pt      // font definition
                                    // \font\twelvepointbf=dctiba at 12pt    // font definition
                                    // \font\twelvepointit=dctiia at 12pt    // font definition
// fonts
   TX_TG_tencyr,           // 10250
   TX_TG_tencyi,           // 10251
   TX_TG_cyr,              // 10252 // switch to russian roman font
   TX_TG_cyi,              // 10253 // switch to russian italic font

   TX_TG_INSERT,           // 10254

   TX_TG_poliplottrue,     // 10255 // \poliplottrue
   TX_TG_setbox,           // 10256 // \setbox
   TX_TG_figbox,           // 10257 // \figbox=
   TX_TG_vbox,             // 10258 // \vbox{}
// TX_TG_leftskip,                  // \leftskip=0pt plus 1fill
   TX_TG_rightskip,        // 10259 // \rightskip=0pt plus 1fill
   TX_TG_hsize,            // 10260 // \hsize=8cm // teksto plotis // page
// TX_TG_hbox,                      // \hbox{}
   TX_TG_parindent,        // 10261 // \parindent=0pt  // indent of first paragraph line
   TX_TG_MakeInsert,       // 10262 // \MakeInsert{C}
// TX_TG_hskip,                     // \hskip 0.3cm
// TX_TG_captionbottomtrue,         // \captionbottomtrue
   TX_TG_plotcomment,      // 10263 // \plotcomment %Komentaras tarp brezinio ir pavadinimo
   TX_TG_endplotcomment,   // 10264 // \endplotcomment

   TX_TG_medskip,          // 10265

   TX_TG_null,             // 10266

   TX_TG_headb,            // 10267 // \headb{...}

   TX_TG_list,             // 10268 // \list{1)} textas
// TX_TG_endlist,

   TX_TG_proff,            // 10269
   TX_TG_pron,             // 10270

   TX_TG_par,              // 10271

   TX_TG_vfil,             // 10272 // fill page end with empty lines (before \eject), do not adjust bottom of the page
   TX_TG_hfil,             // 10273 // fill end of the line with spaces (before \break), do not adjust right border of the line
// TX_TG_vfill,
// TX_TG_hfill,
   TX_TG_vfilll,           // 10274 // fill page end with empty lines (before \eject), do not adjust bottom of the page
   TX_TG_hfilll,           // 10275 // fill end of the line with spaces (before \break), do not adjust right border of the line

   TX_TG_phantom,          // 10276 // attach sublist to list // \list{\phantom{III. }}1. Skriptoriai -- perra÷inótojai.

   TX_TG_hrulefill,        // 10277

   TX_TG_eightpoint,       // 10278 // switch to defined font
   TX_TG_ninepoint,        // 10279 // switch to defined font
   TX_TG_tenpoint,         // 10280 // switch to defined font
   TX_TG_twelvepoint,      // 10281 // switch to defined font

   TX_TG_ldots,            // 10282 // ...

   TX_TG_smallskip,        // 10283

// some fonts
   TX_TG_Longe,            // 10284
   TX_TG_Longm,            // 10285

   TX_TG_vtop,             // 10286

// font
   TX_TG_wasy,             // 10287

   TX_TG_newbox,           // 10288
   TX_TG_let,              // 10289

   TX_TG_raise,            // 10290   // \raise5pt  - like \vskip

   TX_TG_eqalign,          // 10291

   TX_TG_cr,               // 10292

   TX_TG_CC,               // 10293 // ~TX_TG_LC
   TX_TG_VR,               // 10294

   TX_TG_underbrace,       // 10295
   TX_TG_Ds,               // 10296
   TX_TG_mathindent,       // 10297
   TX_TG_divid,            // 10298
   TX_TG_co,               // 10299

   TX_TG_hoffset,          // 10300          // isdestymas puslapyje // page
   TX_TG_voffset,          // 10301          // isdestymas puslapyje // page
   TX_TG_prulesize,        // 10302
   TX_TG_newdimen,         // 10303
   TX_TG_Null,             // 10304
   TX_TG_leftline,         // 10305
   TX_TG_DM,               // 10306
   TX_TG_wd,               // 10307
   TX_TG_box,              // 10308

   TX_TG_leavevmode,       // 10309
   TX_TG_zv,               // 10310 // C_z_Car

   TX_TG_nul,              // 10311    // fictive tag for no tag identification

   TX_TG_edef,             // 10312

   TX_TG_At,               // 10313

   TX_TG_centerline,       // 10314 // adjust to center
   TX_TG_headt,            // 10315
   TX_TG_headp,            // 10316

   TX_TG_foot,             // 10317
   TX_TG_mod,              // 10318
   TX_TG_mathop,           // 10319

   TX_TG_loadboldtrue,     // 10320 // matematiniai bold simboliai ir raides
   TX_TG_loadbfcaltrue,    // 10321 // kaligrafines raides
// TX_TG_loadgottrue,      //       // gotiskos raides
   TX_TG_loadbfgottrue,    // 10322 // gotiskos bold raides
// TX_TG_loadscrtrue,      //       // rasytines raides
   TX_TG_loadbfscrtrue,    // 10323 // rasytines bold raides
   TX_TG_loadcurtrue,      // 10324 // kursivines raides
   TX_TG_loadbfcurtrue,    // 10325 // kursivines bold raides

   TX_TG_tt,               // 10326 // typewriter fonto ijungimas
   TX_TG_undertext,        // 10327 // parametras su ijungtu pabraukimu

   TX_TG_sin,              // 10328
   TX_TG_cos,              // 10329
   TX_TG_tg,               // 10330
   TX_TG_ctg,              // 10331
   TX_TG_arcsin,           // 10332

   TX_TG_Ettt,             // 10333 // C_E_Adot truetype
   TX_TG_Svtt,             // 10334 // C_S_Car truetype
   TX_TG_Antt,             // 10335 // C_A_Ogon truetype
   TX_TG_sm,               // 10336 // C_smile

   TX_TG_An,               // 10337 // C_A_Ogon
   TX_TG_Cv,               // 10338 // C_C_Car
   TX_TG_En,               // 10339 // C_E_Ogon
   TX_TG_Et,               // 10340 // C_E_Adot
   TX_TG_In,               // 10341 // C_I_Ogon
   TX_TG_Sv,               // 10342 // C_S_Car
   TX_TG_Un,               // 10343 // C_U_Ogon
   TX_TG_Ub,               // 10344 // C_U_Macr
   TX_TG_Zv,               // 10345 // C_Z_Car
// TX_TG_an,                        // C_a_Ogon
   TX_TG_cv,               // 10346 // C_c_Car
// TX_TG_en,                        // C_e_Ogon
// TX_TG_et,                        // C_e_Adot
// TX_TG_in,                        // C_i_Ogon    // does not exist !!!
   TX_TG_sv,               // 10347 // C_s_Car
// TX_TG_un,                        // C_u_Ogon
// TX_TG_ub,                        // C_u_Macr
// TX_TG_zv,                        // C_z_Car
// TX_TG_Antt,                      // C_A_Ogon truetype
   TX_TG_Cvtt,             // 10348 // C_C_Car truetype
   TX_TG_Entt,             // 10349 // C_E_Ogon truetype
// TX_TG_Ettt,                      // C_E_Adot truetype
   TX_TG_Intt,             // 10350 // C_I_Ogon truetype
// TX_TG_Svtt,                      // C_S_Car truetype
   TX_TG_Untt,             // 10351 // C_U_Ogon truetype
   TX_TG_Ubtt,             // 10352 // C_U_Macr truetype
   TX_TG_Zvtt,             // 10353 // C_Z_Car truetype
   TX_TG_antt,             // 10354 // C_a_Ogon truetype
   TX_TG_cvtt,             // 10355 // C_c_Car truetype
   TX_TG_entt,             // 10356 // C_e_Ogon truetype
   TX_TG_ettt,             // 10357 // C_e_Adot truetype
   TX_TG_intt,             // 10358 // C_i_Ogon truetype
   TX_TG_svtt,             // 10359 // C_s_Car truetype
   TX_TG_untt,             // 10360 // C_u_Ogon truetype
   TX_TG_ubtt,             // 10361 // C_u_Macr truetype
   TX_TG_zvtt,             // 10362 // C_z_Car truetype

   TX_TG_halign,           // 10363
   TX_TG_noalign,          // 10364

   TX_TG_cases,            // 10365

   TX_TG_hangindent,       // 10366
   TX_TG_hangafter,        // 10367

   TX_TG_max,              // 10368
   TX_TG_min,              // 10369

   TX_TG_char,             // 10370

   TX_TG_Dal,              // 10371

   TX_TG_RC,               // 10372 // ~TX_TG_LC
   TX_TG_me,               // 10373
   TX_TG_multispan,        // 10374

   TX_TG_TeX,              // 10375

   TX_TG_boxitc,           // 10376

   TX_TG_strut,            // 10377
   TX_TG_ItCor,            // 10378 // "\/"

   TX_TG_inott,            // 10379 // C_i_Ogon typewriter

// fonts
   TX_TG_helv,             // 10380 // helvetica 10pt srifto ijungimas
   TX_TG_helvi,            // 10381 // helvetica 10pt italic srifto ijungimas
   TX_TG_helvb,            // 10382 // helvetica 10pt bold srifto ijungimas
   TX_TG_helvbi,           // 10383 // helvetica 10pt bold italic srifto ijungimas
   TX_TG_helvm,            // 10384 // helvetica 8pt srifto ijungimas
   TX_TG_helvim,           // 10385 // helvetica 8pt italic srifto ijungimas
   TX_TG_helvbm,           // 10386 // helvetica 8pt bold srifto ijungimas
   TX_TG_helvbim,          // 10387 // helvetica 8pt bold italic srifto ijungimas

   TX_TG_kern,             // 10388

   TX_TG_proofplottrue,    // 10389

   TX_TG_rhr,              // 10390
   TX_TG_rhl,              // 10391
   TX_TG_rightrh,          // 10392 // LMR // defines right running header, uses \rightheadline
   TX_TG_leftrh,           // 10393 // LMR // defines left running header, uses \leftheadline

   TX_TG_topmatter,        // 10394 // LMR
   TX_TG_endtopmatter,     // 10395 // LMR
   TX_TG_gdef,             // 10396 // LMR // define global macro
   TX_TG_Title,            // 10397 // LMR

   TX_TG_baselineskip,     // 10398

   TX_TG_everypar,         // 10399

   TX_TG_skipas,           // 10400

   TX_TG_bye,              // 10401

   TX_TG_fxr,              // 10402 // font
   TX_TG_fxx,              // 10403 // font
   TX_TG_frxx,             // 10404 // font

   TX_TG_Stage,            // 10405 // %Stage=200
   TX_TG_Pages,            // 10406 // %Pages=
   TX_TG_TID,              // 10407 // %TID=ZAL_ALD   - typesetter id.

   TX_TG_FS,               // 10408 // \FSnn - set font style NS_FontStyle number nn

   TX_TG_BD,               // 10409 // zodynu antrastinio zodzio pagrindines dalies atskyrejas - du vertikalus bruksniai, C_paral, '||'
   TX_TG_BS,               // 10410 // zodynu pagrindines atitikmens dalies pakeitimo simbolis - tilde '~'

   TX_TG_SP_CHAR,          // 10411 // \^^a1 - defines hex character, like "A1 - what the difference?

   TX_TG_catcode,          // 10412 // \catcode`\^^a1=11 - defines categories of characters
                                    // \catcode`\@=11 // enables using of forbidden characters (@)
                                    // \catcode`\@=13 // disables using of forbidden characters (@)
   TX_TG_lccode,           // 10413 // \lccode`\^^a1=`\^^e1 - defines lowercase pair of the character
   TX_TG_uccode,           // 10414 // \uccode`\^^a1=`\^^a1 - defines uppercase pair of the character

   TX_TG_ifnum,            // 10415
   TX_TG_ifx,              // 10416

   TX_TG_inputlineno,      // 10417
   TX_TG_undefined,        // 10418

   TX_TG_else,             // 10419
   TX_TG_fi,               // 10420

   TX_TG_patterns,         // 10421 // patterns of hyphenation table

   TX_TG_relax,            // 10422
   TX_TG_endinput,         // 10423
   TX_TG_message,          // 10424

   TX_TG_begingroup,       // 10425
   TX_TG_endgroup,         // 10426

   TX_TG_dash,             // 10427 // nonbreaking dash character (C_Minus)
   TX_TG_dtb,              // 10428 // dash with diaeresis  C_Diaer+C_Minus

   TX_TG_settabs,          // 10429 // set tabulators, look LvzT2X_tag::WriteHeader()
   TX_TG_columns,          // 10430
   TX_TG_plus,             // 10431

   TX_TG_lastwordinpar,    // 10432

   TX_TG_fontdimen,        // 10433 // \fontdimen4\timacn=4pt // shrink interword
   TX_TG_timacn,           // 10434 // times accented font timacn

   TX_TG_LT,               // 10435 // language specifiers
   TX_TG_DE,               // 10436
   TX_TG_EN,               // 10437
   TX_TG_FR,               // 10438
   TX_TG_PL,               // 10439

// LVZ, VLZ tags
   TX_TG_raide,            // 10440 // former LV_TG_raide,
   TX_TG_theraide,         // 10441 // former LV_TG_theraide,
   TX_TG_nuleisti,         // 10442 // former LV_TG_nuleisti,
   TX_TG_hboxup,           // 10443 // former LV_TG_hboxup,

   TX_TG_global,           // 10444
   TX_TG_LBOX,             // 10445
   TX_TG_orwidth,          // 10446
   TX_TG_hwidth,           // 10447

// fonts
   TX_TG_xiivirm,          // 10448
   TX_TG_xirm,             // 10449
   TX_TG_xrm,              // 10450
   TX_TG_xbf,              // 10451
   TX_TG_xiivibf,          // 10452
   TX_TG_xit,              // 10453

   TX_TG_Ccedil,           // 10454
   TX_TG_ccedil,           // 10455
   TX_TG_Sacute,           // 10456
   TX_TG_sacute,           // 10457

   TX_TG_plainparskip,     // 10458
   TX_TG_parskip,          // 10459

   TX_TG_timacnll,         // 10460

   TX_TG_thistable,        // 10461
   TX_TG_desiredwidth,     // 10462
   TX_TG_begintable,       // 10463
   TX_TG_begintableformat, // 10464
   TX_TG_left,             // 10465
   TX_TG_endtableformat,   // 10466
   TX_TG_B,                // 10467
   TX_TG_E,                // 10468

   TX_TG_bfp,              // 10469

   TX_TG_TRTH,             // 10470
   TX_TG_footnote,         // 10471
   TX_TG_VV,               // 10472

   TX_TG_endtable,         // 10473
   TX_TG_maketable,        // 10474

   TX_TG_endash,           // 10475 // = TX_TG_Ndash  // = C_EnDash

   TX_TG_itp,              // 10476

// latex is HOP projekto
   TX_TG_BeginFileInfo,       // 10477
   TX_TG_Manuscript,          // 10478
   TX_TG_Company,             // 10479
   TX_TG_ProFile,             // 10480
   TX_TG_Compiler_cmd_line,   // 10481
   TX_TG_Send_to_DB,          // 10482
   TX_EndFileInfo,            // 10483
   TX_TG_documentclass,       // 10484
   TX_TG_usepackage,          // 10485
   TX_TG_vrule,               // 10486
   TX_TG_underline,           // 10487
   TX_TG_ut,                  // 10488
   TX_TG_uline,               // 10489
   TX_TG_sut,                 // 10490
   TX_TG_sout,                // 10491
   TX_TG_overfullrule,        // 10492
   TX_TG_INDEX,               // 10493
   TX_TG_psdraft,             // 10494
   TX_TG_vtexed,              // 10495
   TX_TG_volume,              // 10496
   TX_TG_issue,               // 10497
   TX_TG_pubyear,             // 10498
   TX_TG_doublehyphendemerits,// 10499
   TX_TG_articletype,         // 10500
   TX_TG_begin,               // 10501
   TX_TG_Project_macro,       // 10502
   TX_TG_pagenumbering,       // 10503
   TX_TG_printbookmarks,      // 10504
   TX_TG_figlink,             // 10505
   TX_TG_caption,             // 10506
   TX_TG_label,               // 10507
   TX_TG_tablewidth,          // 10508
   TX_TG_extracolsep,         // 10509
   TX_TG_fill,                // 10510

   TX_TG_Exindent,            // 10511
   TX_TG_ExVK,                // 10512
   TX_TG_MySize,              // 10513
   TX_TG_ex,                  // 10514
   TX_TG_tableft,             // 10515
   TX_TG_tabcolsep,           // 10516

   TX_TG_ttfamily,            // 10517

   TX_TG_ParEnd,              // 10518 // "\\" // paragraph end ??? (does not work, usually used empty line)
                                       //    naudojamas latexiniu lenteliu eiluciu galuose
                                       //    "1& CT &how can I help you?\\"

   TX_TG_textit,              // 10519 // \it - italic
   TX_TG_textsc,              // 10520 // small caps

   TX_TG_tsub,                // 10521
   TX_TG_tsup,                // 10522

   TX_TG_Ex,                  // 10523

   TX_TG_notetext,            // 10524

   TX_TG_textbf,              // 10525 // \bf - bold

   TX_TG_longn,               // 10526

   TX_TG_textgr,              // 10527 // greek font

   TX_TG_item,                // 10528 // listo irasas Benjamins latex projektuose, \begin{itemize}

   TX_TG_textul,              // 10529 // underlined text

   TX_TG_endfile,             // 10530 // failo pabaiga  // \endfile{aztek}{A}

   TX_TG_bullet,              // 10531 // tas pats, kaip ir C_Bpoint

   TX_TG_ecirc,               // 10532 // ^e tas pats, kaip ir C_e_Circ

   TX_TG_Ncedil,              // 10533 // C_N_Bcomma, /* N, */  // AKLZ minion nesusitvarko
   TX_TG_ncedil,              // 10534 // C_n_Bcomma, /* n, */
   TX_TG_Rcedil,              // 10535 // C_R_Bcomma, /* R, */
   TX_TG_rcedil,              // 10536 // C_r_Bcomma, /* r, */  // AKLZ minion nesusitvarko

   TX_TG_amp,                 // 10537 // C_Amp    /* &  Ampersand (Ampersandas) */ // AKLZ Minion fonte negraþus, reikia keisti á Times
   TX_TG_apos,                // 10538 // C_Apost  /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */ // minion ðrifte pasviræs, reikia stataus
   TX_TG_ast,                 // 10539 // C_Ast    /* *  Asterisk (Zvaigzdute) */ // aklz minion ðrifte paprasta þveigþdutë penkiakampë

   TX_TG_lapos,               // 10540 // C_LAapost
   TX_TG_rapos,               // 10541 //  C_Rapost

TX_TG_LastTag

} TX_TagIds;




// \folio // page number // romeniskas, jei pageno<0
// \leftheadline{...}  // defines left running header, page numbering, used in \leftrh
// \rightheadline{...}  // defines right running header, page numbering, used in \rightrh
// \vsize=202mm // teksto aukstis (be running heado?) // page
// \showhyphens{...} - parodo kelimo zenklus .log faile

extern const unsigned char *plpszaMainTexTagTable[TX_TG_NumOfTags0+1];
                     // predefined command names, NULL - end of table

extern const unsigned char *plpszaUserTexTagTable[/* LV_TG_NumOfTags0+1 */];
                     // user defined command names, NULL - end of table
                     // may be dynamically loaded at runtime (later)
                     // for output files NULL entryes mean also untagged plain text tags

extern const KpChar /* TX_TagIds */ iaUserTexTagPrefixes[/* LV_TG_NumOfTags0 */];
                     // prefix tags before output of untagged plain text tag contents;
                     // can be exclusively TeX tags of type TexCtrl
                     // additional space will be output before, when text begins with space

extern const int /* KpChar */ /* TX_TagIds */ iaTexTagCtbls[TX_TG_NumOfTags0];
                     // user defined code tables for Tex commands (not 0 only for
                     //    font switching commands - TX_TG_rm, TX_TG_rmr, TX_TG_got, TX_TG_bf, TX_TG_it, TX_TG_mit

extern const KpChar /* TX_TagIds */ iaFontSwitches[];  // Null-terminated array of font switches
extern const KpChar /* TX_TagIds */ iaCtblSwitches[];  // Null-terminated array of font switches,
                                          //    related with code table switching


//------------------------------------------------
extern const unsigned char *plpszaTexSpecCharTags[C_CharSize0];
                     // TEX spec char tags for KpChar

//------------------------------------------------
#define TX_ARG_NUM      (-2)     // one numeric argument after '=' ("\firstpage=1")
#define TX_ARG_TXT      (-3)     // text arguments after '=' ("%Publisher=TEV"),
                                 //    number of args undefined
#define TX_ARG_TXT_WIDE (-1)     // undefined number of text arguments
#define TX_ARG_GLUE     (-4)     // glue argument, without '=' ("\hskip -1.5cm plus 1")
#define TX_ARG_VAR      (-5)     // variable tag - if '=' - assignment, do not output
#define TX_ARG_REG      (-6)     // register - variable with index: \box3=...
#define TX_ARG_NUM_GLUE (-7)     // glue argument, with '=' ("\TRTH=0.8pt")


// number of command arguments
// positive number or 0 means exact number of symbolic arguments
// number 0 is used for switching commands, effecting all text to the end
//    of current group
// number of entries must exactly match number of command names in plpszaTexTagTable
extern const int iaMainTexTagArgs[TX_TG_NumOfTags0];
extern int iaUserTexTagArgs[];


//------------------------------------------------
// tag text parameter end rule
// if none of following - than up to tag with code, given as end rule
#define TX_ARG_END_TAG (-1)      // up to next TEX tag
#define TX_ARG_END_LINE (-2)     // up to end of current line
#define TX_ARG_END_CUR_LEV_TAG (-3) // up to next TEX tag of current grouping level,
                                    //    all tags of deeper levels are processed as parameter

//------------------------------------------------
// tex tag types (for output)
typedef enum
{
   TexNoType,

   TexCtrl,          // commands with 0 arguments sequentially in the
                     //    text - font switches, skips, spaces etc.
                     //    put space after tag keyword
   TexGlue,          // tags with glue (TX_ARG_GLUE) arguments: \hskip -1.5cm plus 1
                     //    put space after tag keyword
   TexKey,           // tags with arguments after '=' (TX_ARG_NUM or TX_ARG_TXT),
                     //    definition tags with following tags as parameters (\def \char ...),
                     //    variables in expressions, operators (\if...);
                     //    do not put any punctuation
   TexTag,           // tags with arguments (usually in curly brackets)
                     //    do not put any punctuation
   TexReg,           // tags with arguments as single characters only (TX_ARG_REG)
                     //    register - variable with index: \box3=...
                     //    do not put any punctuation
   TexDiacr,         // tags of diacritics, affects next character -
                     //    do not put any punctuation
   TexChar,          // character tags - enclose them into curly brackets
   TexMathChar,      // mathematical character tags - enclose them into '$'
   TexVar,           // tags of variables, may have assignment = after it, may not have
                     //    currently TX_ARG_TXT used as type of parameters
   TexFont,          // font tags - in definition like TexKey, later - without args
                     //    currently TX_ARG_TXT used as type of parameters

} TexTagTypes;

// TEX spec char types
extern TexTagTypes iaTexSpecCharTypes[C_CharSize0];
// types of main TEX tags
extern TexTagTypes iaMainTexTagTypes[TX_TG_NumOfTags0];
// types of local TEX tags
extern TexTagTypes iaUserTexTagTypes[];

//------------------------------------------------
// tag variations (aliases) array
extern int iaTexTagVariations[];
// each entry consists of 3 elements: tag (or Kpt char) variation, main tag (or Kpt
//    char) of all variations, usage area of that variation:
//    TX_TG_hat,     C_CircAcc,     TX_FORMULA_FIELD,
//    ...
//    C_Nul,         C_Nul,         0
// by intput column 1 characters must be converted to column 2 characters, by output - vice versa
extern int iaUserTexTagVariations[];
// like iaTexTagVariations[], but has higher priority

// usage areas of tags
#define TX_TEXT_FIELD      (-1)     // only in text fields
#define TX_FORMULA_FIELD   (-2)     // only in formula fields and subfields of formulas
#define TX_BOTH_TYPES      0        // both types of fields


//------------------------------------------------
// field length identifiers
#define TX_WIDE_FIELD      (-1)  // field contents up to '}'
#define TX_ONE_LETTER_FIELD 1    // field of only one character
// #define TX_FORMULA_FIELD   (-2)  // formula field between '$'


//------------------------------------------------
extern const unsigned char lpszKwdChars[];
extern const unsigned char lpszTxAccents1[];    // accents with one additional character
extern const unsigned char lpszTxAccents2[];    // accents with two additional characters
extern const unsigned char lpszTxAccents3[];    // accents with three additional characters
extern const unsigned char lpszTxAccents12[];
extern const unsigned char lpszTxAccents123[];


// =================================================== class GlueDescriptor_tag
#define TX_GLUE_TAG_LEN 20

typedef enum
{
   NoUnits,

   UnitsPt,
   UnitsMm,
   UnitsCm,
   UnitsIn,
   UnitsEn,
   UnitsEm,
   UnitsFilll,
   UnitsFill,
   UnitsFil,

   NumOfTexGlueUnits1,
} TexGlueUnits;


// --------------------------------------------------
class GlueDescriptor_tag
{
public:
   float dSize;
   TexGlueUnits iUnits;
   float dPlusSize;
   TexGlueUnits iPlusUnits;
   float dMinusSize;
   TexGlueUnits iMinusUnits;

   float dToSize;
   TexGlueUnits iToUnits;
   float dSpreadSize;
   TexGlueUnits iSpreadUnits;

   GlueDescriptor_tag(void);
   void ResetFields(void);
};

extern const unsigned char *plpszaGlueUnitNames[NumOfTexGlueUnits1+1];


// =================================================== class TexFieldDescriptor_tag
class TexFieldDescriptor_tag
{
   TexFieldDescriptor_tag *pParentField;  // Pointer to previous field. NULL - the first level
                                          //    of the file

   int iFldLenInd;      // Field length indicator, values TX_WIDE_FIELD or TX_ONE_LETTER_FIELD

   int iCtbl;           // Current Kpt code table number

   int iParNum;         // Command parameter order number - number of character or
                        //    grouped char. group from the command keyword or
                        //    beginning of the group

   bool bParEnd;        // Command parameter end flag

   KpChar /* TX_TagIds */ uiFont;    // current field font (TX_TG_rm, TX_TG_rmr, TX_TG_got, TX_TG_bf, TX_TG_it, TX_TG_mit)

   bool bMathField;     // flag of subfield of formula field
   bool bTransparent;   // flag of subfield with transparent transfer of field delimiters


public:
   bool m_bCtblSwitched;           // indicates, that current output field has had
                                 //    code table switches
   bool m_bFirstChar;              // indicates, that current output field is empty yet

   TexFieldDescriptor_tag(TexFieldDescriptor_tag *pPField);
                                          // pPField - pointer to parent field,
                                          //    may be NULL
   ~TexFieldDescriptor_tag(void);

   HRESULT SetParField(TexFieldDescriptor_tag *pParField);
                                          // Set ponter to parrent field
   HRESULT GetParField(TexFieldDescriptor_tag **ppParField);
                                          // Get ponter to parrent field

   HRESULT SetFieldLength(int iFieldLengthIndicator);
                                          // sets iFldLenInd
   HRESULT GetFieldLength(int *piFieldLengthIndicator);
                                          // gets iFldLenInd

   HRESULT GetCodeTable(int *piCodeTable); // Get current Kpt code table number
   HRESULT SetCodeTable(int iCodeTable);  // Set current Kpt code table number

   HRESULT ClearParNum(void);             // Reset number of command parameter

   HRESULT GetParNum(int *piParNumPtr, bool *pbParEndPtr);
                                          // Get order number of current command
                                          //    parameter (value of iParNum)
                                          // Get "outside of parameter" flag (bParEnd)
                                          //    value

   HRESULT IncParNum(void);               // Move to next parameter (increment iParNum)

   HRESULT SetParEnd(void);               // Marks command parameter end (spaces region
                                          //    between parameters), i.e., sets bParEnd

   HRESULT GetFont(KpChar /* TX_TagIds */ *puiFntPtr);
   HRESULT SetFont(const KpChar /* TX_TagIds */ uiFnt);
                                          // Get/Set uiFont

   HRESULT SetMathFlag(const bool bMathFl);
   HRESULT GetMathFlag(bool *pbMathFl);   // Get/Set bMathField

   HRESULT SetTransparent(const bool bTrnsprFl);
   HRESULT GetTransparent(bool *pbTrnsprFl);   // Get/Set bTransparent
};


// =================================================== class TvUserClass0_tag
class TvUserClass0_tag
{
public:

   virtual HRESULT ProcessKeyword(KpChar *piInChar, KpChar **ppStrBuf)=0;
                                 // TEX command user processing
                                 // Input:
                                 //    *puiInChar - command code
                                 // Output:
                                 //    *pcInChar - input char, if changed
                                 // Uses pCurrentField

};


// =================================================== class TvTexFile
// --------------------------------------------------
class TvTexFile
{
   HRESULT lhOpenResult;

   unsigned char lpszFName[KP_MAX_FNAME_LEN+1]; // file name
   unsigned char lpszFMode[TV_TAG_LEN+1];       // file open mode (like fopen())

   FILE *lpfFilePtr;             // file itself

   int iCharPos;                 // Output character position in the output text row

   long lCharNum;                // Current char number in output TEX file

   unsigned char caUnGetBuf[TX_UNGET_BUF_SIZ];// UnGetChar() variables
   int iUnGetCnt;

   KpChar iaUnGetProcBuf[TX_UNGET_BUF_SIZ];// UnGetCharProc() variables
   int iUnGetProcCnt;

   int iGrpLev;                  // Level of subgroup of grouped character fields

   bool bCommentFlg;             // start of comment

   TexFieldDescriptor_tag *pCurrentField;  // pointer to current TEX field descriptor

   int iNumOfUserTags;

   bool bLastWordInParFl;        // =True, when \lastwordinpar is active; will be reset on LF

// ------------------------------- fields for high level output
   KpChar iLastChar;                // variable for accumulating of multiple spaces
   KpChar iLastOutChar;             // variable for storing of last char output
   KpChar /* TX_TagIds */ iLastSwitch;        // variable for accumulating of multiple code table swich
   KpChar /* TX_TagIds */ iCurFont;           // current font (TX_TG_rm, TX_TG_rmr, TX_TG_got, TX_TG_bf, TX_TG_it, TX_TG_mit)
   KpChar /* TX_TagIds */ iCurFontSav;        // saved font of parent field (for formula fields)
   int iCurCtbl;                 // Current Kpt code table number
   bool bTransparent;            // flag of subfield with transparent transfer of field delimiters

   bool m_bInsideTableRow;

// -----------------------------------------------
   unsigned char lpszProject[TV_TAG_LEN+1];
   unsigned char lpszPublisher[TV_TAG_LEN+1];

// -----------------------------------------------
   HRESULT PushField
   (
      KpChar *puiInch,
      bool *bCharPresent,
      const int iFieldLengthIndicator,
      bool bMathFl
   );
                                 // Creates new field definitions, puts them to the
                                 //    top of the record.
                                 // Input:
                                 //    iFieldLengthIndicator - values TX_WIDE_FIELD
                                 //       and TX_ONE_LETTER_FIELD
                                 //    bMathFl means start of formula field
                                 // Output:
                                 //    puiInch contains returned character if
                                 //       bCharPresent==TRUE
                                 // Uses pCurrentField

   HRESULT PopField
   (
      KpChar *puiInch,
      bool *bCharPresent
   );
                                 // Returns back parrent field definitions, deletes
                                 //    current field from top of the record.
                                 // Output:
                                 //    puiInch contains returned character if
                                 //       bCharPresent==TRUE
                                 // Uses pCurrentField

   HRESULT CharEncode(KpChar *puiOutChar, unsigned char cInChar);
                                 // Converts cInChar to Kpt char *puiOutChar

   HRESULT CharDecode(unsigned char *pcOutChar, KpChar uiInChar);
                                 // Decode Kpt character for output, according to
                                 //    current Kpt code table
                                 // Does not output error message, if character not found

   HRESULT SkipChars(const unsigned char *lpszCharsToSkip, bool *pbCharsSkipped);
                                 // Skips chars from input file.
                                 // Input:
                                 //    lpszCharsToSkip - null terminated string
                                 //    with chars to skip.
                                 //    Uses GetChar() and UnGetChar().

   HRESULT TxTo7BitStr(unsigned char *lpszStr);
                                 // Converts 8-bit string to 7-bit string of Tex
                                 //    commands
                                 // Uses CharEncode()
public:

// ------------------------------------- file open
   TvTexFile
   (
      const unsigned char *lpszFileName,
      const unsigned char *lpszMode,
      int iNumberOfUserTags
   );                            // Opens file for input/output, depending on lpszMode
                                 //    (like fopen())

   ~TvTexFile();

   HRESULT GetOpenResult(void);        // Returns value of OpenResult -
                                       //    object creation error code

   HRESULT CloseFile(bool bCheckFileExist);
                                       // Closes current TEX file
                                       //   this call makes sence only for result code retrieving,
                                       //   after CloseFile() no other calls except ~TvTexFile()
                                       //   are acceptable
                                       // bCheckFileExist - if not set, no file
                                       //    presence will be tested



   HRESULT GetCharPos(int *piCharPos);

   HRESULT GetCodeTable(int *piCodeTable);
                                       // Get current Kpt code table number
   HRESULT SetCodeTable(int iCodeTable);
                                       // Set current Kpt code table number

   HRESULT GetGrpLev(int *piGrLevelPtr);
                                       // gets level of subgroup (value of iGrpLev)


   HRESULT GetParNum(int *piParNumPtr, bool *pbParEndPtr, const int iGrLevel);
                                          // Get order number of current command
                                          //    parameter
                                          // Get "outside of parameter" flag (bParEnd)
                                          //    value
                                          // iGrLevel - wich char group level must
                                          //    be looked over, -1 - current group
                                          //    level

   HRESULT GetCurFont(KpChar /* TX_TagIds */ *puiFntPtr);
   HRESULT SetCurFont(const KpChar /* TX_TagIds */ uiFnt);
                                          // Get/Set font of current field

   HRESULT GetMathFlag(bool *pbMathFl);   // Get/Set pCurrentField->bMathField
   HRESULT SetMathFlag(bool bMathFl);

   HRESULT GetTransparent(bool *pbTrnsprFl);   // Get/Set pCurrentField->bTransparent
   HRESULT SetTransparent(bool bTrnsprFl);

   HRESULT GetLastWordInParFl(bool *pbLastWInPFl);   // Get/Set bLastWordInParFl
   HRESULT SetLastWordInParFl(bool bLastWInPFl);


// -------------------------------------------------- low level input
   HRESULT GetChar(unsigned char *pcInch, bool bCheckFeof);
                                 // Gets current char. from file
                                 // bCheckFeof is used to swith on end of file error
                                 //    output
                                 //    Uses lpfFilePtr

   HRESULT UnGetChar(unsigned char cChar);
                                 // Put char. back to input stream for GetChar()

   HRESULT UnGetStr(unsigned char *lpszString);
                                 // Put string back to input stream for GetChar()

   HRESULT GetWord
   (
      unsigned char *lpszKeywrd,
      KpChar *piDelimCh,
      bool bOnlyAlpha
   );                            // Reads current word from file until not
                                 //    alphabetical charatcer is reached.
                                 //    This char is returned in pcDelimCh.
                                 //    Spaces and eol's after word are skipped.
                                 //    If no alphabetical charatcers are found,
                                 //    one very first character is returned (in Kpt
                                 //    notation). In this case spaces and eol's are
                                 //    converted to one space.
                                 // Output:
                                 //    lpszKeywrd - address of buffer for keyword -
                                 //       not shorter, than TV_TAG_LEN+1 bytes;
                                 //    Uses GetChar() and UnGetChar().


   HRESULT SkipSpaces(bool *pbSpFl);
   HRESULT SkipSpcEol(int *piEolCnt);
                                 // Skips spaces, tabs and ends of lines
                                 //    Uses GetChar() and UnGetChar().


   HRESULT ResetCommentFlag(void);
                                 // Clear comment state for entering of copmment
                                 //    command argument

// -------------------------------------------------- high level input
   HRESULT GetCharProc(KpChar *puiInch, bool bCheckFeof, bool *pbEolFl, TvUserClass0_tag *pUserObj);
                                 // Get current char. from file, taking into account
                                 //    TEX commands processing.  Converts to Kpt
                                 //     charset.
                                 // bCheckFeof is used to swith on end of file error
                                 //    output
                                 // Uses GetChar(), GetWord(), ProcessKeyword(),
                                 //    GetKwrdIndex().

   HRESULT UnGetCharProc(KpChar iChar);
                                 // Put char. back to input stream for GetCharProc()

   HRESULT GetCharProcSkipSpc(KpChar *puiInch, bool bCheckFeof, bool *pbEolFl, TvUserClass0_tag *pUserObj);
                                 // Get first char not space
                                 // Uses GetCharProc()

   HRESULT ProcessKeyword(KpChar *piInChar, KpChar **ppStrBuf, TvUserClass0_tag *pUserObj);
                                 // TEX command processing
                                 // Input:
                                 //    *puiInChar - command code
                                 // Output:
                                 //    *pcInChar - input char, if changed
                                 // Uses pCurrentField
                                 // pUserObj - for ProcessKeyword(), if ==NULL - no user object

   HRESULT GetNumArg(long *lArgPtr);
                                 // gets one numeric command argument, followed after '='

   HRESULT GetTextArg(unsigned char *lpszOutStr, int iBufLen);
                                 // gets one textual command argument, followed after '='

   HRESULT GetNumPar(long *plValue, bool bCheckFeof, TvUserClass0_tag *pUserObj);
                                 // gets one numeric command parameter, consisting of
                                 //    one numeric char or one char group
                                 // bCheckFeof - test eof flag

   HRESULT GetTextPar(unsigned char *lpszChBuf, int iBufLen, bool bCheckFeof, TvUserClass0_tag *pUserObj);
                                 // gets one command parameter to lpszChBuf
                                 // iBufLen - max size of lpszChBuf
                                 // bCheckFeof - test eof flag

   HRESULT GetKpTextPar(KpChar *iazChBuf, int iBufLen, bool bCheckFeof, TvUserClass0_tag *pUserObj); // former GetIntTextPar
                                 // gets one command parameter to iazChBuf as Kpt char
                                 //    C_Nul-terminated string
                                 // iBufLen - max size of iazChBuf
                                 // bCheckFeof - test eof flag

   HRESULT SkipCmdPars(bool bCheckFeof, TvUserClass0_tag *pUserObj);
                                 // skips all command parameters at current group
                                 //    level (up to next command or current group end
                                 // bCheckFeof - test eof flag

   HRESULT GetStrProc(unsigned char *lpszStrBuf, int iBufSize, int iEndTag, TvUserClass0_tag *pUserObj);
                                 // gets char. string, consisting of all parameters of
                                 //    current command (up to the next command)
                                 // tag processing
                                 // cuts characters to 8-bit length, so only ASCII
                                 //    chars are allowed.
                                 //    (convert them to some 8-bit table ???!!!)
                                 // (move to tvtex.cpp !!!)
                                 // Does not process controll chars (Ctbl switching)
                                 // pUserObj - for ProcessKeyword(), if ==NULL - no user object
   HRESULT GetKpStrProc(KpChar *lpiazStrBuf, int iBufSize, KpChar iEndTag, TvUserClass0_tag *pUserObj); // former GetIntStrProc

   HRESULT GetGlueSize(float *pdSize, TexGlueUnits *piUnits, bool *pEndFl);  // used in GetGlue()
   HRESULT GetGlue(GlueDescriptor_tag *lpGlueDescript);

// -------------------------------------------------- low level output
   HRESULT PutChar(const unsigned char ucOutch, bool bSkipLineOnSpace);
                                  // Put char to Tex file
                                  // bSkipLineOnSpace - wrap flag

   HRESULT PutStr(const unsigned char *lpszOutstr, bool bSkipLineOnSpace);
                                  // puts null terminated string to output Tex file
                                  // uses PutChar()
                                  // bSkipLineOnSpace - wrap flag

   HRESULT PutStrSqDiacr(const unsigned char *lpszOutstr, bool bSkipLineOnSpace);
                                  // like PutStr(), but skips space after nonalphabetic
                                  //    diacritics
                                  // bSkipLineOnSpace - wrap flag

// -------------------------------------------------- high level output
   HRESULT SetCtblSwitched(const bool bValue);  // set pCurrentField->m_bCtblSwitched
   HRESULT GetCtblSwitched(bool *pbValue);      // get pCurrentField->m_bCtblSwitched
   HRESULT SetFirstChar(const bool bValue);     // set pCurrentField->m_bFirstChar
   HRESULT GetFirstChar(bool *pbValue);         // get pCurrentField->m_bFirstChar
   HRESULT ResetLastChar(void);                 // reset uiLastChar and uiLastSwitch

   HRESULT OpenField(bool bFlushFl, bool bSkipLineOnSpace);   // put '{'; bFlushFl - put delimitting spaces from buffer
   HRESULT CloseField(bool bFlushFl, bool bSkipLineOnSpace);  // put '}'
                                  // bSkipLineOnSpace - wrap flag

   HRESULT FlushSpaces(bool bSkipLineOnSpace);

   HRESULT PutCharProc(KpChar iOutch, TexTagTypes iTagType, bool bSkipLineOnSpace, int iLastWordRest);
                                 // Put char to Tex file with tag processing and
                                 //    code table switching
                                 // iTagType if not 0 (TexNoType) overrides default
                                 //    tag type  of spec. character
                                 // bSkipLineOnSpace - wrap flag
                                 // iLastWordRest - parameter for \lastwordinpar by output of C_sbreak, usually LAST_WORD_LEN

   HRESULT PutStrProc(const unsigned char *lpszOutstr, bool bSkipLineOnSpace, int iLastWordRest);
      // put character string with processing of special codes.
      // !!! dar nerealizuotas >0x80 kodu konvertavimas
                                 // bSkipLineOnSpace - wrap flag
                                 // iLastWordRest - parameter for \lastwordinpar by output of C_sbreak, usually LAST_WORD_LEN

   HRESULT PutKpStrProc(const KpChar *lpaizOutStr, bool bSkipLineOnSpace, int iLastWordRest); // former PutIntStrProc
                                 // Put 16-bit Kpt string to file;
                                 // bSkipLineOnSpace - wrap flag
                                 // iLastWordRest - parameter for \lastwordinpar by output of C_sbreak, usually LAST_WORD_LEN
};


// =================================================== free functions
extern HRESULT StrCpySqDiacr(unsigned char *lpszDestStr, const unsigned char *lpszSrcStr);
                                 // like strcpy(), but skips space after nonalphabetic
                                 //    diacritics

extern HRESULT WriteLatexHeader(TvTexFile *lpOutFileObj, const unsigned char *lpszPublisher,
                     const unsigned char *lpszProject, const unsigned char *lpszManuscript);
extern HRESULT WriteLatexTail(TvTexFile *lpOutFileObj);

#endif
