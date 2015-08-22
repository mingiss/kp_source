// ==================================================
// tvtex.cpp
// TEX tags and other data


// ================================================== definitions, static fields
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <stdlib.h>
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
// #include "kpctype.h"
// #include "kpsort.h"
// #include "kpstring.h"
// #include "kperr.h"
#include "tvmain.h"
#include "tvtex.h"


// --------------------------------------------------
// const unsigned char lpszTexCtrlChars[] =   "%\\{}$";
const unsigned char lpszTexCtrlChars[] =   "\\%{}$#&_=\'\"`@^";
// order according TX_SpecChars

// --------------------------------------------------
const unsigned char lpszKwdChars[]={"" /* "." */};
const unsigned char lpszTxAccents1[]={"`\'^\"~=."};
const unsigned char lpszTxAccents2[]={"uvHcdb"};
const unsigned char lpszTxAccents3[]={"t"};
const unsigned char lpszTxAccents12[]={"`\'^\"~=.uvHcdb"};
const unsigned char lpszTxAccents123[]={"`\'^\"~=.uvHcdbt"};


//----------------------------------
const KpChar /* TX_TagIds */ iaFontSwitches[] =
{
   (KpChar)TX_TG_ctbl_off,// switch off any code table
   (KpChar)TX_TG_rm,      // switch to roman font
   (KpChar)TX_TG_rmr,     // switch to russian roman font
   (KpChar)TX_TG_got,     // switch to gothic
   (KpChar)TX_TG_cal,     // switch to calligraphic

   (KpChar)TX_TG_bf,      // switch to bold font
   (KpChar)TX_TG_bfi,     // switch to bold italic font
   (KpChar)TX_TG_bfp,
   (KpChar)TX_TG_it,      // switch to italic font
   (KpChar)TX_TG_mit,     // switch to math. italic font
   (KpChar)TX_TG_itp,

   (KpChar)TX_TG_tencyr,           // 10250
   (KpChar)TX_TG_tencyi,           // 10251
   (KpChar)TX_TG_cyr,              // 10252 // switch to russian roman font
   (KpChar)TX_TG_cyi,              // 10253 // switch to russian italic font

   (KpChar)TX_TG_eightpoint,       // 10278 // switch to defined font
   (KpChar)TX_TG_ninepoint,        // 10279 // switch to defined font
   (KpChar)TX_TG_tenpoint,         // 10280 // switch to defined font
   (KpChar)TX_TG_twelvepoint,      // 10281 // switch to defined font

   (KpChar)TX_TG_Longe,            // 10284
   (KpChar)TX_TG_Longm,            // 10285

   (KpChar)TX_TG_wasy,             // 10287

   (KpChar)TX_TG_tt,      // typewriter font

   (KpChar)TX_TG_helv,    // helvetica 10pt srifto ijungimas
   (KpChar)TX_TG_helvi,   // helvetica 10pt italic srifto ijungimas
   (KpChar)TX_TG_helvb,   // helvetica 10pt bold srifto ijungimas
   (KpChar)TX_TG_helvbi,  // helvetica 10pt bold italic srifto ijungimas
   (KpChar)TX_TG_helvm,   // helvetica 8pt srifto ijungimas
   (KpChar)TX_TG_helvim,  // helvetica 8pt italic srifto ijungimas
   (KpChar)TX_TG_helvbm,  // helvetica 8pt bold srifto ijungimas
   (KpChar)TX_TG_helvbim, // helvetica 8pt bold italic srifto ijungimas

   (KpChar)TX_TG_fxr,
   (KpChar)TX_TG_fxx,
   (KpChar)TX_TG_frxx,

   (KpChar)TX_TG_timacn,           // 10436 // times accented font timacn
   (KpChar)TX_TG_timacnll,

   (KpChar)TX_TG_xiivirm,
   (KpChar)TX_TG_xirm,
   (KpChar)TX_TG_xrm,
   (KpChar)TX_TG_xbf,
   (KpChar)TX_TG_xiivibf,
   (KpChar)TX_TG_xit,

// (KpChar)TX_TG_ttfamily,

// (KpChar)TX_TG_textit,
// (KpChar)TX_TG_textbf,
// (KpChar)TX_TG_textsc,
// (KpChar)TX_TG_textgr,
// (KpChar)TX_TG_textul,

   (KpChar)TX_TG_longn,

   (KpChar)TX_TG_Unknown,
};


//----------------------------------
const KpChar /* TX_TagIds */ iaCtblSwitches[] =
{
   (KpChar)TX_TG_ctbl_off,// switch off any code table
   (KpChar)TX_TG_rm,      // switch to roman font
   (KpChar)TX_TG_rmr,     // switch to russian roman font
   (KpChar)TX_TG_got,     // switch to gothic
   (KpChar)TX_TG_cal,     // switch to calligraphic

   (KpChar)TX_TG_Unknown,
};


const unsigned char *plpszaGlueUnitNames[NumOfTexGlueUnits1+1] =
{
   (const unsigned char *)"???",   // NoUnits

   (const unsigned char *)"pt",    // UnitsPt
   (const unsigned char *)"mm",    // UnitsMm
   (const unsigned char *)"cm",    // UnitsCm
   (const unsigned char *)"in",    // UnitsIn
   (const unsigned char *)"en",    // UnitsEn
   (const unsigned char *)"em",    // UnitsEm
   (const unsigned char *)"filll", // UnitsFilll
   (const unsigned char *)"fill",  // UnitsFill
   (const unsigned char *)"fil",   // UnitsFil

   NULL
};

// --------------------------------------------------
const unsigned char *plpszaMainTexTagTable[TX_TG_NumOfTags132+1] =
{
   (const unsigned char *)"\\input",
   (const unsigned char *)"\\firstpage",
   (const unsigned char *)"\\lastpage",
   (const unsigned char *)"\\HPROOF",
   (const unsigned char *)"\\PROOF",
   (const unsigned char *)"\\CRC",
   (const unsigned char *)"\\VIEW",
   (const unsigned char *)"\\setparameters",
   (const unsigned char *)"\\lang",
   (const unsigned char *)"\\heada",
   (const unsigned char *)"\\titletrue",

   (const unsigned char *)"",          // TX_TG_ctbl_off
   (const unsigned char *)"\\rm",
   (const unsigned char *)"\\rmr",
   (const unsigned char *)"\\got",
   (const unsigned char *)"\\cal",

   (const unsigned char *)"\\bf",
   (const unsigned char *)"\\it",
   (const unsigned char *)"\\mit",

   (const unsigned char *)"\\endpaper",
   (const unsigned char *)"\\loadgottrue",

   (const unsigned char *)"\\over",
   (const unsigned char *)"\\sqrt", //    TX_TG_sqrt,   // \sqrt
   (const unsigned char *)"\\root", //    TX_TG_root,   // \root
   (const unsigned char *)"\\of",   //    TX_TG_of,     // \of

   (const unsigned char *)"\\hat",
   (const unsigned char *)"\\check",
   (const unsigned char *)"\\tilde",
   (const unsigned char *)"\\acute",
   (const unsigned char *)"\\grave",
   (const unsigned char *)"\\dot",
   (const unsigned char *)"\\ddot",
   (const unsigned char *)"\\breve",
   (const unsigned char *)"\\bar",
   (const unsigned char *)"\\vec",
   (const unsigned char *)"\\not",

   (const unsigned char *)"\\big",
   (const unsigned char *)"\\bigl",
   (const unsigned char *)"\\bigr",
   (const unsigned char *)"\\Big",
   (const unsigned char *)"\\Bigl",
   (const unsigned char *)"\\Bigr",
   (const unsigned char *)"\\bigg",
   (const unsigned char *)"\\biggr",
   (const unsigned char *)"\\biggl",
   (const unsigned char *)"\\Bigg",
   (const unsigned char *)"\\Biggr",
   (const unsigned char *)"\\Biggl",

//!!! (const unsigned char *)"\\leq",
   (const unsigned char *)"\\geq",
   (const unsigned char *)"\\neq",

   (const unsigned char *)"\\lbrace",
   (const unsigned char *)"\\rbrace",
   (const unsigned char *)"\\lbrack", //   TX_TG_lbrack, // [
   (const unsigned char *)"\\rbrack", //   TX_TG_rbrack, // ]

   (const unsigned char *)"\\to",   //   TX_TG_to,     // \to -->
   (const unsigned char *)"\\gets", //   TX_TG_gets,   // \gets <--
   (const unsigned char *)"\\owns", //   TX_TG_owns
   (const unsigned char *)"\\land", //    TX_TG_land,   // logical and, C_wedge
   (const unsigned char *)"\\lor",  //    TX_TG_lor,    // logical or, C_vee
   (const unsigned char *)"\\neg",  //    TX_TG_lnot,   // logical not, C_Rminbr
   (const unsigned char *)"\\vert", //    TX_TG_vert,   // C_Vertl
   (const unsigned char *)"\\Vert", //    TX_TG_Vert,   // C_paral
   (const unsigned char *)"\\|",    //    TX_TG_paral,  // C_paral

   (const unsigned char *)"\\ ",    //    TX_TG_forc_sp,

   (const unsigned char *)"\\def",

   (const unsigned char *)"\\pageno",

   (const unsigned char *)"\\begindoublecolumns",

   (const unsigned char *)"\\Ad", //   TX_TG_Ad,   // \Ad C_A_Acute
   (const unsigned char *)"\\ad", //   TX_TG_ad,   // \ad C_a_Acute
   (const unsigned char *)"\\And", //  TX_TG_And,  // \And C_A_Ogon_Acute
   (const unsigned char *)"\\and", //  TX_TG_and,  // \and C_a_Ogon_Acute
   (const unsigned char *)"\\Ed", //   TX_TG_Ed,   // \Ed C_E_Acute
   (const unsigned char *)"\\ed", //   TX_TG_ed,   // \ed C_e_Acute
   (const unsigned char *)"\\END", // kp // TX_TG_End__,  // \End C_E_Ogon_Acute
   (const unsigned char *)"\\End", //  TX_TG_end__,  // \end C_e_Ogon_Acute
   (const unsigned char *)"\\Etd", //  TX_TG_Etd,  // \Etd C_E_Adot_Acute
   (const unsigned char *)"\\etd", //  TX_TG_etd,  // \etd C_e_Adot_Acute
   (const unsigned char *)"\\Id", //   TX_TG_Id,   // \Id C_I_Acute
   (const unsigned char *)"\\id", //   TX_TG_id,   // \id C_i_Acute
   (const unsigned char *)"\\Ind", //  TX_TG_Ind,  // \Ind C_I_Ogon_Acute
   (const unsigned char *)"\\ind", //  TX_TG_ind,  // \ind C_i_Ogon_Acute
   (const unsigned char *)"\\Od", //   TX_TG_Od,   // \Od C_O_Acute
   (const unsigned char *)"\\od", //   TX_TG_od,   // \od C_o_Acute
   (const unsigned char *)"\\Ud", //   TX_TG_Ud,   // \Ud C_U_Acute
   (const unsigned char *)"\\ud", //   TX_TG_ud,   // \ud C_u_Acute
   (const unsigned char *)"\\Und", //  TX_TG_Und,  // \Und C_U_Ogon_Acute
   (const unsigned char *)"\\und", //  TX_TG_und,  // \und C_u_Ogon_Acute
   (const unsigned char *)"\\Ubd", //  TX_TG_Ubd,  // \Ubd C_U_Macr_Acute
   (const unsigned char *)"\\ubd", //  TX_TG_ubd,  // \ubd C_u_Macr_Acute
   (const unsigned char *)"\\Yd", //   TX_TG_Yd,   // \Yd C_Y_Acute
   (const unsigned char *)"\\yd", //   TX_TG_yd,   // \yd C_y_Acute
   (const unsigned char *)"\\Ak", //   TX_TG_Ak,   // \Ak C_A_Grave
   (const unsigned char *)"\\ak", //   TX_TG_ak,   // \ak C_a_Grave
   (const unsigned char *)"\\Ank", //  TX_TG_Ank,  // \Ank C_A_Ogon_Grave
   (const unsigned char *)"\\ank", //  TX_TG_ank,  // \ank C_a_Ogon_Grave
   (const unsigned char *)"\\Ek", //   TX_TG_Ek,   // \Ek C_E_Grave
   (const unsigned char *)"\\ek", //   TX_TG_ek,   // \ek C_e_Grave
   (const unsigned char *)"\\Enk", //  TX_TG_Enk,  // \Enk C_E_Ogon_Grave
   (const unsigned char *)"\\enk", //  TX_TG_enk,  // \enk C_e_Ogon_Grave
   (const unsigned char *)"\\Etk", //  TX_TG_Etk,  // \Etk C_E_Adot_Grave
   (const unsigned char *)"\\etk", //  TX_TG_etk,  // \etk C_e_Adot_Grave
   (const unsigned char *)"\\Ik", //   TX_TG_Ik,   // \Ik C_I_Grave
   (const unsigned char *)"\\ik", //   TX_TG_ik,   // \ik C_i_Grave
   (const unsigned char *)"\\Ink", //  TX_TG_Ink,  // \Ink C_I_Ogon_Grave
   (const unsigned char *)"\\ink", //  TX_TG_ink,  // \ink C_i_Ogon_Grave
   (const unsigned char *)"\\Ok", //   TX_TG_Ok,   // \Ok C_O_Grave
   (const unsigned char *)"\\ok", //   TX_TG_ok,   // \ok C_o_Grave
   (const unsigned char *)"\\Uk", //   TX_TG_Uk,   // \Uk C_U_Grave
   (const unsigned char *)"\\uk", //   TX_TG_uk,   // \uk C_u_Grave
   (const unsigned char *)"\\Unk", //  TX_TG_Unk,  // \Unk C_U_Ogon_Grave
   (const unsigned char *)"\\unk", //  TX_TG_unk,  // \unk C_u_Ogon_Grave
   (const unsigned char *)"\\Ubk", //  TX_TG_Ubk,  // \Ubk C_U_Macr_Grave
   (const unsigned char *)"\\ubk", //  TX_TG_ubk,  // \ubk C_u_Macr_Grave
   (const unsigned char *)"\\Yk", //   TX_TG_Yk,   // \Yk C_Y_Grave
   (const unsigned char *)"\\yk", //   TX_TG_yk,   // \yk C_y_Grave
   (const unsigned char *)"\\Ar", //   TX_TG_Ar,   // \Ar C_A_Tilde
   (const unsigned char *)"\\ar", //   TX_TG_ar,   // \ar C_a_Tilde
   (const unsigned char *)"\\Anr", //  TX_TG_Anr,  // \Anr C_A_Ogon_Tilde
   (const unsigned char *)"\\anr", //  TX_TG_anr,  // \anr C_a_Ogon_Tilde
   (const unsigned char *)"\\Er", //   TX_TG_Er,   // \Er C_E_Tilde
   (const unsigned char *)"\\er", //   TX_TG_er,   // \er C_e_Tilde
   (const unsigned char *)"\\Enr", //  TX_TG_Enr,  // \Enr C_E_Ogon_Tilde
   (const unsigned char *)"\\enr", //  TX_TG_enr,  // \enr C_e_Ogon_Tilde
   (const unsigned char *)"\\Etr", //  TX_TG_Etr,  // \Etd C_E_Adot_Tilde
   (const unsigned char *)"\\etr", //  TX_TG_etr,  // \etd C_e_Adot_Tilde
   (const unsigned char *)"\\Ir", //   TX_TG_Ir,   // \Ir C_I_Tilde
   (const unsigned char *)"\\ir", //   TX_TG_ir,   // \ir C_i_Tilde
   (const unsigned char *)"\\Inr", //  TX_TG_Inr,  // \Inr C_I_Ogon_Tilde
   (const unsigned char *)"\\inr", //  TX_TG_inr,  // \inr C_i_Ogon_Tilde
   (const unsigned char *)"\\Or", // kp // TX_TG_Or,   // \Or C_O_Tilde
   (const unsigned char *)"\\OR", //   TX_TG_or,   // \or C_o_Tilde
   (const unsigned char *)"\\Ur", //   TX_TG_Ur,   // \Ur C_U_Tilde
   (const unsigned char *)"\\ur", //   TX_TG_ur,   // \ur C_u_Tilde
   (const unsigned char *)"\\Unr", //  TX_TG_Unr,  // \Unr C_U_Ogon_Tilde
   (const unsigned char *)"\\unr", //  TX_TG_unr,  // \unr C_u_Ogon_Tilde
   (const unsigned char *)"\\Ubr", //  TX_TG_Ubr,  // \Ubr C_U_Macr_Tilde
   (const unsigned char *)"\\ubr", //  TX_TG_ubr,  // \ubr C_u_Macr_Tilde
   (const unsigned char *)"\\Yr", //   TX_TG_Yr,   // \Yr C_Y_Tilde
   (const unsigned char *)"\\yr", //   TX_TG_yr,   // \yr C_y_Tilde
   (const unsigned char *)"\\Lr", //   TX_TG_Lr,   // \Lr C_L_Tilde
   (const unsigned char *)"\\lr", //   TX_TG_lr,   // \lr C_l_Tilde
   (const unsigned char *)"\\Mr", //   TX_TG_Mr,   // \Mr C_M_Tilde
   (const unsigned char *)"\\mr", //   TX_TG_mr,   // \mr C_m_Tilde
   (const unsigned char *)"\\Nr", //   TX_TG_Nr,   // \Nr C_N_Tilde
   (const unsigned char *)"\\nr", //   TX_TG_nr,   // \nr C_n_Tilde
   (const unsigned char *)"\\Rr", //   TX_TG_Rr,   // \Rr C_R_Tilde
   (const unsigned char *)"\\rr", //   TX_TG_rr,   // \rr C_r_Tilde

   (const unsigned char *)"\\romb", // TX_TG_romb,
   (const unsigned char *)"\\bb",   // TX_TG_bb,
   (const unsigned char *)"\\kid",  // TX_TG_kid,
   (const unsigned char *)"\\Ndash", // TX_TG_Ndash,
   (const unsigned char *)"\\V",    // TX_TG_V,
   (const unsigned char *)"\\kam",  // TX_TG_kam
   (const unsigned char *)"\\kav",  // TX_TG_kav

   (const unsigned char *)"\\enddoublecolumns",   //  TX_TG_enddoublecolumns
   (const unsigned char *)"\\end",                //  TX_TG_end

   (const unsigned char *)"\\et",                 //  TX_TG_et = C_e_Adot
   (const unsigned char *)"\\ub",                 //  TX_TG_ub = C_u_Macr
   (const unsigned char *)"\\an",                 //  TX_TG_an,      // = C_a_Ogon
   (const unsigned char *)"\\en",                 //  TX_TG_en,      // = C_e_Ogon
   (const unsigned char *)"???",                  //  TX_TG_in,      // = C_i_Ogon  // !!! does not exist
   (const unsigned char *)"\\ino",                //  TX_TG_ino,     // = C_i_Ogon
   (const unsigned char *)"\\un",                 //  TX_TG_un,      // = C_u_Ogon

   (const unsigned char *)"\\eject",              //  TX_TG_eject
   (const unsigned char *)"\\zmark",              //  TX_TG_zmark

   (const unsigned char *)"\\ls", // "\\leqslant" //  TX_TG_ls ~~ C_le
   (const unsigned char *)"\\gs", // "\\geqslant" //  TX_TG_gs ~~ C_ge

   (const unsigned char *)"\\looseness",          // TX_TG_looseness,
   (const unsigned char *)"\\hbox",               // TX_TG_hbox,
   (const unsigned char *)"\\em",                 // TX_TG_em,

   (const unsigned char *)"\\psl",                // TX_TG_psl,

   (const unsigned char *)"\\MT",                 // TX_TG_MT,

   (const unsigned char *)"\\vadjust",            // TX_TG_vadjust

   (const unsigned char *)"\\!",                  // TX_TG_NegQemSpc,

   (const unsigned char *)"\\scriptstyle",        // TX_TG_scriptstyle,
   (const unsigned char *)"\\scriptscriptstyle",  // TX_TG_scriptscriptstyle,

   (const unsigned char *)"\\u u",                // TX_TG_u_Brev

   (const unsigned char *)"\\loadscrtrue",

   (const unsigned char *)"%Project",             // TX_TG_Project
   (const unsigned char *)"%Publisher",
   (const unsigned char *)"\\typesetterid",
   (const unsigned char *)"\\paperid",
   (const unsigned char *)"\\statusno",
   (const unsigned char *)"\\switch",

   (const unsigned char *)"\\long",
   (const unsigned char *)"\\noindent",

   (const unsigned char *)"\\insertplot",
   (const unsigned char *)"\\position",
   (const unsigned char *)"\\bottom",
   (const unsigned char *)"\\pheight",
   (const unsigned char *)"\\pwidth",
   (const unsigned char *)"\\pprocent",
   (const unsigned char *)"\\ptype",
   (const unsigned char *)"\\pname",
   (const unsigned char *)"\\ptext",
   (const unsigned char *)"\\pfile",
   (const unsigned char *)"\\pcorrections",
   (const unsigned char *)"\\pvacor",
   (const unsigned char *)"\\endinsertplot",
   (const unsigned char *)"\\UNI",

   (const unsigned char *)"\\bfi",

   (const unsigned char *)"\\leftskip",

   (const unsigned char *)"\\BTH",
   (const unsigned char *)"\\tableno",
   (const unsigned char *)"\\tname",
   (const unsigned char *)"\\tposition",
   (const unsigned char *)"\\tcorrections",
   (const unsigned char *)"\\ETH",
   (const unsigned char *)"\\BTF",
   (const unsigned char *)"\\LC",
   (const unsigned char *)"\\ETF",
   (const unsigned char *)"\\=",
   (const unsigned char *)"\\BR",
   (const unsigned char *)"\\_",
   (const unsigned char *)"\\CVB",
   (const unsigned char *)"", // "\\|",  TX_TG_paral !!
   (const unsigned char *)"\\ER",
   (const unsigned char *)"\\NVS",
   (const unsigned char *)"\\EOT",

   (const unsigned char *)"\\after",
   (const unsigned char *)"\\top",
   (const unsigned char *)"\\mid",
   (const unsigned char *)"\\there",
// (const unsigned char *)"\\bottom",
   (const unsigned char *)"\\full",
   (const unsigned char *)"\\bpage",
   (const unsigned char *)"\\mpage",
   (const unsigned char *)"\\epage",
   (const unsigned char *)"\\tvacor",
   (const unsigned char *)"\\tvbcor",
   (const unsigned char *)"\\tvccor",
   (const unsigned char *)"\\tvdcor",

   (const unsigned char *)"\\vskip",
   (const unsigned char *)"\\hskip",

   (const unsigned char *)"\\captionbottomtrue",

   (const unsigned char *)"\\alistind",
   (const unsigned char *)"\\alist",
   (const unsigned char *)"\\endlist",

   (const unsigned char *)"\\vfill",
   (const unsigned char *)"\\break",
   (const unsigned char *)"\\hfill",

   (const unsigned char *)"\\None",
// (const unsigned char *)"\\UNI",
   (const unsigned char *)"\\HPX",
   (const unsigned char *)"\\PCZ",
   (const unsigned char *)"\\PS",

   (const unsigned char *)"\\phcor",
// (const unsigned char *)"\\pvacor",
   (const unsigned char *)"\\pvbcor",
   (const unsigned char *)"\\pvccor",

   (const unsigned char *)"\\newfam",
   (const unsigned char *)"\\cyrfam",
   (const unsigned char *)"\\font",
   (const unsigned char *)"\\tencyr",
   (const unsigned char *)"\\tencyi",
   (const unsigned char *)"\\cyr",
   (const unsigned char *)"\\cyi",

   (const unsigned char *)"\\INSERT",

   (const unsigned char *)"\\poliplottrue",
   (const unsigned char *)"\\setbox",
   (const unsigned char *)"\\figbox",
   (const unsigned char *)"\\vbox",
// (const unsigned char *)"\\leftskip",
   (const unsigned char *)"\\rightskip",
   (const unsigned char *)"\\hsize",
// (const unsigned char *)"\\hbox",
   (const unsigned char *)"\\parindent",
   (const unsigned char *)"\\MakeInsert",
// (const unsigned char *)"\\hskip",
// (const unsigned char *)"\\captionbottomtrue",
   (const unsigned char *)"\\plotcomment",
   (const unsigned char *)"\\endplotcomment",

   (const unsigned char *)"\\medskip",

   (const unsigned char *)"\\null",

   (const unsigned char *)"\\headb",

   (const unsigned char *)"\\list",
// (const unsigned char *)"\\endlist",

   (const unsigned char *)"\\proff",
   (const unsigned char *)"\\pron",

   (const unsigned char *)"\\par",

   (const unsigned char *)"\\vfil",
   (const unsigned char *)"\\hfil",
// (const unsigned char *)"\\vfill",
// (const unsigned char *)"\\hfill",
   (const unsigned char *)"\\vfilll",
   (const unsigned char *)"\\hfilll",

   (const unsigned char *)"\\phantom",

   (const unsigned char *)"\\hrulefill",

   (const unsigned char *)"\\eightpoint",
   (const unsigned char *)"\\ninepoint",
   (const unsigned char *)"\\tenpoint",
   (const unsigned char *)"\\twelvepoint",

   (const unsigned char *)"\\ldots",

   (const unsigned char *)"\\smallskip",

   (const unsigned char *)"\\Longe",
   (const unsigned char *)"\\Longm",

   (const unsigned char *)"\\vtop",

   (const unsigned char *)"\\wasy",

   (const unsigned char *)"\\newbox",
   (const unsigned char *)"\\let",

   (const unsigned char *)"\\raise",

   (const unsigned char *)"\\eqalign",

   (const unsigned char *)"\\cr",

   (const unsigned char *)"\\CC",
   (const unsigned char *)"\\VR",

   (const unsigned char *)"\\underbrace",
   (const unsigned char *)"\\Ds",
   (const unsigned char *)"\\mathindent",
   (const unsigned char *)"\\divid",
   (const unsigned char *)"\\co",

   (const unsigned char *)"\\hoffset",
   (const unsigned char *)"\\voffset",
   (const unsigned char *)"\\prulesize",
   (const unsigned char *)"\\newdimen",
   (const unsigned char *)"\\Null",
   (const unsigned char *)"\\leftline",
   (const unsigned char *)"\\DM",
   (const unsigned char *)"\\wd",
   (const unsigned char *)"\\box",

   (const unsigned char *)"\\leavevmode",
   (const unsigned char *)"\\zv",

   (const unsigned char *)"",       // TX_TG_nul

   (const unsigned char *)"\\edef",

   (const unsigned char *)"\\@",    // TX_TG_At

   (const unsigned char *)"\\centerline",
   (const unsigned char *)"\\headt",
   (const unsigned char *)"\\headp",

   (const unsigned char *)"\\foot",
   (const unsigned char *)"\\mod",
   (const unsigned char *)"\\mathop",

   (const unsigned char *)"\\loadboldtrue",
   (const unsigned char *)"\\loadbfcaltrue",
// (const unsigned char *)"\\loadgottrue",
   (const unsigned char *)"\\loadbfgottrue",
// (const unsigned char *)"\\loadscrtrue",
   (const unsigned char *)"\\loadbfscrtrue",
   (const unsigned char *)"\\loadcurtrue",
   (const unsigned char *)"\\loadbfcurtrue",

   (const unsigned char *)"\\tt",
   (const unsigned char *)"\\undertext",

   (const unsigned char *)"\\sin",
   (const unsigned char *)"\\cos",
   (const unsigned char *)"\\tg",
   (const unsigned char *)"\\ctg",
   (const unsigned char *)"\\arcsin",

   (const unsigned char *)"\\Ettt",
   (const unsigned char *)"\\Svtt",
   (const unsigned char *)"\\Antt",
   (const unsigned char *)"\\sm",

   (const unsigned char *)"\\An",
   (const unsigned char *)"\\Cv",
   (const unsigned char *)"\\En",
   (const unsigned char *)"\\Et",
   (const unsigned char *)"\\In",
   (const unsigned char *)"\\Sv",
   (const unsigned char *)"\\Un",
   (const unsigned char *)"\\Ub",
   (const unsigned char *)"\\Zv",
// (const unsigned char *)"\\an",
   (const unsigned char *)"\\cv",
// (const unsigned char *)"\\en",
// (const unsigned char *)"\\et",
// (const unsigned char *)"???",                  //  TX_TG_in,      // = C_i_Ogon  // !!! does not exist
   (const unsigned char *)"\\sv",
// (const unsigned char *)"\\un",
// (const unsigned char *)"\\ub",
// (const unsigned char *)"\\zv",
// (const unsigned char *)"\\Antt",
   (const unsigned char *)"\\Cvtt",
   (const unsigned char *)"\\Entt",
// (const unsigned char *)"\\Ettt",
   (const unsigned char *)"\\Intt",
// (const unsigned char *)"\\Svtt",
   (const unsigned char *)"\\Untt",
   (const unsigned char *)"\\Ubtt",
   (const unsigned char *)"\\Zvtt",
   (const unsigned char *)"\\antt",
   (const unsigned char *)"\\cvtt",
   (const unsigned char *)"\\entt",
   (const unsigned char *)"\\ettt",
   (const unsigned char *)"\\intt",
   (const unsigned char *)"\\svtt",
   (const unsigned char *)"\\untt",
   (const unsigned char *)"\\ubtt",
   (const unsigned char *)"\\zvtt",

   (const unsigned char *)"\\halign",
   (const unsigned char *)"\\noalign",

   (const unsigned char *)"\\cases",

   (const unsigned char *)"\\hangindent",
   (const unsigned char *)"\\hangafter",

   (const unsigned char *)"\\max",
   (const unsigned char *)"\\min",

   (const unsigned char *)"\\char",

   (const unsigned char *)"\\Dal",

   (const unsigned char *)"\\RC",
   (const unsigned char *)"\\me",
   (const unsigned char *)"\\multispan",

   (const unsigned char *)"\\TeX",

   (const unsigned char *)"\\boxitc",

   (const unsigned char *)"\\strut",
   (const unsigned char *)"\\/",    // TX_TG_ItCor

   (const unsigned char *)"\\inott",

   (const unsigned char *)"\\helv",
   (const unsigned char *)"\\helvi",
   (const unsigned char *)"\\helvb",
   (const unsigned char *)"\\helvbi",
   (const unsigned char *)"\\helvm",
   (const unsigned char *)"\\helvim",
   (const unsigned char *)"\\helvbm",
   (const unsigned char *)"\\helvbim",

   (const unsigned char *)"\\kern",

   (const unsigned char *)"\\proofplottrue",

   (const unsigned char *)"\\rhr",
   (const unsigned char *)"\\rhl",
   (const unsigned char *)"\\rightrh",
   (const unsigned char *)"\\leftrh",

   (const unsigned char *)"\\topmatter",
   (const unsigned char *)"\\endtopmatter",
   (const unsigned char *)"\\gdef",
   (const unsigned char *)"\\Title",

   (const unsigned char *)"\\baselineskip",

   (const unsigned char *)"\\everypar",

   (const unsigned char *)"\\skipas",

   (const unsigned char *)"\\bye",

   (const unsigned char *)"\\fxr",
   (const unsigned char *)"\\fxx",
   (const unsigned char *)"\\frxx",

   (const unsigned char *)"%Stage",
   (const unsigned char *)"%Pages",
   (const unsigned char *)"%TID",

   (const unsigned char *)"\\FS",

   (const unsigned char *)"\\BD",
   (const unsigned char *)"\\BS",

   (const unsigned char *)"\\^^",   // TX_TG_SP_CHAR

   (const unsigned char *)"\\catcode",
   (const unsigned char *)"\\lccode",
   (const unsigned char *)"\\uccode",

   (const unsigned char *)"\\ifnum",
   (const unsigned char *)"\\ifx",

   (const unsigned char *)"\\inputlineno",
   (const unsigned char *)"\\undefined",

   (const unsigned char *)"\\else",
   (const unsigned char *)"\\fi",

   (const unsigned char *)"\\patterns",

   (const unsigned char *)"\\relax",
   (const unsigned char *)"\\endinput",
   (const unsigned char *)"\\message",

   (const unsigned char *)"\\begingroup",
   (const unsigned char *)"\\endgroup",

   (const unsigned char *)"\\dash",
   (const unsigned char *)"\\dtb",

   (const unsigned char *)"\\settabs",
   (const unsigned char *)"\\columns",
   (const unsigned char *)"\\+", //   TX_TG_plus,

   (const unsigned char *)"\\lastwordinpar",

   (const unsigned char *)"\\fontdimen",
   (const unsigned char *)"\\timacn",

   (const unsigned char *)"\\LT",
   (const unsigned char *)"\\DE",
   (const unsigned char *)"\\EN",
   (const unsigned char *)"\\FR",
   (const unsigned char *)"\\PL",

   (const unsigned char *)"\\raide",
   (const unsigned char *)"\\theraide",
   (const unsigned char *)"\\nuleisti",
   (const unsigned char *)"\\hboxup",

   (const unsigned char *)"\\global",
   (const unsigned char *)"\\LBOX",
   (const unsigned char *)"\\orwidth",
   (const unsigned char *)"\\hwidth",

   (const unsigned char *)"\\xiivirm",
   (const unsigned char *)"\\xirm",
   (const unsigned char *)"\\xrm",
   (const unsigned char *)"\\xbf",
   (const unsigned char *)"\\xiivibf",
   (const unsigned char *)"\\xit",

   (const unsigned char *)"\\Ccedil",
   (const unsigned char *)"\\ccedil",
   (const unsigned char *)"\\Sacute",
   (const unsigned char *)"\\sacute",

   (const unsigned char *)"\\plainparskip",
   (const unsigned char *)"\\parskip",

   (const unsigned char *)"\\timacnll",

   (const unsigned char *)"\\thistable",
   (const unsigned char *)"\\desiredwidth",
   (const unsigned char *)"\\begintable",
   (const unsigned char *)"\\begintableformat",
   (const unsigned char *)"\\endtableformat",
   (const unsigned char *)"\\left",
   (const unsigned char *)"\\B",
   (const unsigned char *)"\\E",

   (const unsigned char *)"\\bfp",

   (const unsigned char *)"\\TRTH",
   (const unsigned char *)"\\footnote",
   (const unsigned char *)"\\VV",

   (const unsigned char *)"\\endtable",
   (const unsigned char *)"\\maketable",

   (const unsigned char *)"\\endash",

   (const unsigned char *)"\\itp",

   (const unsigned char *)"%BeginFileInfo",
   (const unsigned char *)"%Manuscript",
   (const unsigned char *)"%Company",
   (const unsigned char *)"%ProFile",
   (const unsigned char *)"%Compiler cmd line",
   (const unsigned char *)"%Send to DB",
   (const unsigned char *)"%EndFileInfo",
   (const unsigned char *)"\\documentclass",
   (const unsigned char *)"\\usepackage",
   (const unsigned char *)"\\vrule",
   (const unsigned char *)"\\underline",
   (const unsigned char *)"\\ut",
   (const unsigned char *)"\\uline",
   (const unsigned char *)"\\sut",
   (const unsigned char *)"\\sout",
   (const unsigned char *)"\\overfullrule",
   (const unsigned char *)"\\INDEX",
   (const unsigned char *)"\\psdraft",
   (const unsigned char *)"\\vtexed",
   (const unsigned char *)"\\volume",
   (const unsigned char *)"\\issue",
   (const unsigned char *)"\\pubyear",
   (const unsigned char *)"\\doublehyphendemerits",
   (const unsigned char *)"\\articletype",
   (const unsigned char *)"\\begin",
   (const unsigned char *)"\\Project",       // TX_TG_Project_macro
   (const unsigned char *)"\\pagenumbering",
   (const unsigned char *)"\\printbookmarks",
   (const unsigned char *)"\\figlink",
   (const unsigned char *)"\\caption",
   (const unsigned char *)"\\label",
   (const unsigned char *)"\\tablewidth",
   (const unsigned char *)"\\extracolsep",
   (const unsigned char *)"\\fill",

   (const unsigned char *)"\\Exindent",
   (const unsigned char *)"\\ExVK",
   (const unsigned char *)"\\MySize",
   (const unsigned char *)"\\ex",
   (const unsigned char *)"\\tableft",
   (const unsigned char *)"\\tabcolsep",

   (const unsigned char *)"\\ttfamily",

   (const unsigned char *)"\\\\",      // TX_TG_ParEnd
      
   (const unsigned char *)"\\textit",
   (const unsigned char *)"\\textsc",
      
   (const unsigned char *)"\\tsub",
   (const unsigned char *)"\\tsup",
      
   (const unsigned char *)"\\Ex",

   (const unsigned char *)"\\notetext",

   (const unsigned char *)"\\textbf",

   (const unsigned char *)"\\longn",

   (const unsigned char *)"\\textgr",

   (const unsigned char *)"\\item",

   (const unsigned char *)"\\textul",
   
   (const unsigned char *)"\\endfile",

   (const unsigned char *)"$\\bullet$",   // bus blogai, jei jau matematiniam rezime !!!

   (const unsigned char *)"\\ecirc",

   (const unsigned char *)"\\Ncedil",  // C_N_Bcomma
   (const unsigned char *)"\\ncedil",  // C_n_Bcomma
   (const unsigned char *)"\\Rcedil",  // C_R_Bcomma
   (const unsigned char *)"\\rcedil",  // C_r_Bcomma

   (const unsigned char *)"\\amp",  // "\\&",   // C_Amp  
   (const unsigned char *)"\\apos", // "\'",    // C_Apost
   (const unsigned char *)"\\ast",  // "*",     // C_Ast  

   (const unsigned char *)"\\lapos", //  C_LAapost
   (const unsigned char *)"\\rapos", //  C_Rapost

   NULL
};


const int iaMainTexTagArgs[TX_TG_NumOfTags132] =
{
   TX_ARG_TXT_WIDE,  // \input
   TX_ARG_NUM,       // \firstpage=1
   TX_ARG_NUM,       // \lastpage=1
   0,                // \HPROOF
   0,                // \PROOF
   0,                // \CRC
   0,                // \VIEW
   0,                // \setparameters
   TX_ARG_NUM,       // \lang
   1,                // \heada
   0,                // \titletrue

   0,                // TX_TG_ctbl_off,// switch off any code table
   0,                // \rm         // switch to roman font
   0,                // \rmr        // switch to russian roman font
   0,                // \got        // switch to gothic
   0,                // \cal        // switch to gothic

   0,                // \bf         // switch to bold font
   0,                // \it
   0,                // \mit

   0,                // \endpaper
   0,                // \loadgottrue

   1,                // \over
   1,                //    TX_TG_sqrt,   // \sqrt
   0,                //    TX_TG_root,   // \root
   1,                //    TX_TG_of,     // \of

   1,                // \hat
   1,                // \check
   1,                // \tilde
   1,                // \acute
   1,                // \grave
   1,                // \dot
   1,                // \ddot
   1,                // \breve
   1,                // \bar
   1,                // \vec
   1,                // \not

   1,                // \big",
   1,                // \bigl",
   1,                // \bigr",
   1,                // \Big",
   1,                // \Bigl",
   1,                // \Bigr",
   1,                // \bigg",
   1,                // \biggr",
   1,                // \biggl",
   1,                // \Bigg",
   1,                // \Biggr",
   1,                // \Biggl",

//!!! 0,                // \leq
   0,                // \geq
   0,                // \neq

   0,                // \lbrace  {
   0,                // \rbrace  }
   0,                // \lbrack  [
   0,                // \rbrack  ]

   0,                // \to -->
   0,                // \gets <--
   0,                // \owns
   0,                //    TX_TG_land,   // logical and, \land C_wedge
   0,                //    TX_TG_lor,    // logical or, \lor C_vee
   0,                //    TX_TG_lnot,   // logical not, \neg C_Rminbr
   0,                //    TX_TG_vert,   // \vert C_Vertl
   0,                //    TX_TG_Vert,   // \Vert C_paral
   0,                //    TX_TG_paral,  // \| C_paral

   0,                //    TX_TG_forc_sp,

   TX_ARG_TXT_WIDE,  // \def

   TX_ARG_NUM,       // \pageno

   0,                // \begindoublecolumns

   0, //   TX_TG_Ad,   // C_A_Acute
   0, //   TX_TG_ad,   // C_a_Acute
   0, //   TX_TG_And,  // C_A_Ogon_Acute
   0, //   TX_TG_and,  // C_a_Ogon_Acute
   0, //   TX_TG_Ed,   // C_E_Acute
   0, //   TX_TG_ed,   // C_e_Acute
   0, //   TX_TG_End__,  // C_E_Ogon_Acute
   0, //   TX_TG_end__,  // C_e_Ogon_Acute
   0, //   TX_TG_Etd,  // C_E_Adot_Acute
   0, //   TX_TG_etd,  // C_e_Adot_Acute
   0, //   TX_TG_Id,   // C_I_Acute
   0, //   TX_TG_id,   // C_i_Acute
   0, //   TX_TG_Ind,  // C_I_Ogon_Acute
   0, //   TX_TG_ind,  // C_i_Ogon_Acute
   0, //   TX_TG_Od,   // C_O_Acute
   0, //   TX_TG_od,   // C_o_Acute
   0, //   TX_TG_Ud,   // C_U_Acute
   0, //   TX_TG_ud,   // C_u_Acute
   0, //   TX_TG_Und,  // C_U_Ogon_Acute
   0, //   TX_TG_und,  // C_u_Ogon_Acute
   0, //   TX_TG_Ubd,  // C_U_Macr_Acute
   0, //   TX_TG_ubd,  // C_u_Macr_Acute
   0, //   TX_TG_Yd,   // C_Y_Acute
   0, //   TX_TG_yd,   // C_y_Acute
   0, //   TX_TG_Ak,   // C_A_Grave
   0, //   TX_TG_ak,   // C_a_Grave
   0, //   TX_TG_Ank,  // C_A_Ogon_Grave
   0, //   TX_TG_ank,  // C_a_Ogon_Grave
   0, //   TX_TG_Ek,   // C_E_Grave
   0, //   TX_TG_ek,   // C_e_Grave
   0, //   TX_TG_Enk,  // C_E_Ogon_Grave
   0, //   TX_TG_enk,  // C_e_Ogon_Grave
   0, //   TX_TG_Etk,  // C_E_Adot_Grave
   0, //   TX_TG_etk,  // C_e_Adot_Grave
   0, //   TX_TG_Ik,   // C_I_Grave
   0, //   TX_TG_ik,   // C_i_Grave
   0, //   TX_TG_Ink,  // C_I_Ogon_Grave
   0, //   TX_TG_ink,  // C_i_Ogon_Grave
   0, //   TX_TG_Ok,   // C_O_Grave
   0, //   TX_TG_ok,   // C_o_Grave
   0, //   TX_TG_Uk,   // C_U_Grave
   0, //   TX_TG_uk,   // C_u_Grave
   0, //   TX_TG_Unk,  // C_U_Ogon_Grave
   0, //   TX_TG_unk,  // C_u_Ogon_Grave
   0, //   TX_TG_Ubk,  // C_U_Macr_Grave
   0, //   TX_TG_ubk,  // C_u_Macr_Grave
   0, //   TX_TG_Yk,   // C_Y_Grave
   0, //   TX_TG_yk,   // C_y_Grave
   0, //   TX_TG_Ar,   // C_A_Tilde
   0, //   TX_TG_ar,   // C_a_Tilde
   0, //   TX_TG_Anr,  // C_A_Ogon_Tilde
   0, //   TX_TG_anr,  // C_a_Ogon_Tilde
   0, //   TX_TG_Er,   // C_E_Tilde
   0, //   TX_TG_er,   // C_e_Tilde
   0, //   TX_TG_Enr,  // C_E_Ogon_Tilde
   0, //   TX_TG_enr,  // C_e_Ogon_Tilde
   0, //   TX_TG_Etr,  // C_E_Adot_Tilde
   0, //   TX_TG_etr,  // C_e_Adot_Tilde
   0, //   TX_TG_Ir,   // C_I_Tilde
   0, //   TX_TG_ir,   // C_i_Tilde
   0, //   TX_TG_Inr,  // C_I_Ogon_Tilde
   0, //   TX_TG_inr,  // C_i_Ogon_Tilde
   0, //   TX_TG_Or,   // C_O_Tilde
   0, //   TX_TG_or,   // C_o_Tilde
   0, //   TX_TG_Ur,   // C_U_Tilde
   0, //   TX_TG_ur,   // C_u_Tilde
   0, //   TX_TG_Unr,  // C_U_Ogon_Tilde
   0, //   TX_TG_unr,  // C_u_Ogon_Tilde
   0, //   TX_TG_Ubr,  // C_U_Macr_Tilde
   0, //   TX_TG_ubr,  // C_u_Macr_Tilde
   0, //   TX_TG_Yr,   // C_Y_Tilde
   0, //   TX_TG_yr,   // C_y_Tilde
   0, //   TX_TG_Lr,   // C_L_Tilde
   0, //   TX_TG_lr,   // C_l_Tilde
   0, //   TX_TG_Mr,   // C_M_Tilde
   0, //   TX_TG_mr,   // C_m_Tilde
   0, //   TX_TG_Nr,   // C_N_Tilde
   0, //   TX_TG_nr,   // C_n_Tilde
   0, //   TX_TG_Rr,   // C_R_Tilde
   0, //   TX_TG_rr,   // C_r_Tilde

   0,                // TX_TG_romb,
   0,                // TX_TG_bb,
   0,                // TX_TG_kid,
   0,                // TX_TG_Ndash,
   0,                // TX_TG_V,
   0,                // TX_TG_kam
   0,                // TX_TG_kav

   0,                // TX_TG_enddoublecolumns
   1,                // TX_TG_end

   0,                // TX_TG_et
   0,                // TX_TG_ub
   0,                // TX_TG_an
   0,                // TX_TG_en
   0,                // TX_TG_in // !!! does not exist
   0,                // TX_TG_ino
   0,                // TX_TG_un

   0,                // TX_TG_eject
   1,                // TX_TG_zmark

   0,                // TX_TG_ls
   0,                // TX_TG_gs

   TX_ARG_NUM,       // TX_TG_looseness,
   TX_ARG_GLUE,// 1, // TX_TG_hbox, // \hbox{}  // \hbox to10.6cm{...}
   1,                // TX_TG_em,

   1,                // TX_TG_psl,

   0,                // TX_TG_MT,

   0,                // TX_TG_vadjust

   0,                // TX_TG_NegQemSpc,

   1,                // TX_TG_scriptstyle,
   1,                // TX_TG_scriptscriptstyle,

   0,                // TX_TG_u_Brev

   0,                // \loadscrtrue

   TX_ARG_TXT,       // %Project=LMR40
   TX_ARG_TXT,       // %Publisher=TEV
   TX_ARG_TXT,       // \typesetterid={NP}
   TX_ARG_TXT,       // \paperid={info101}
   TX_ARG_NUM,       // \statusno=0
   TX_ARG_NUM,       // \switch=0

   0,                // \long
   0,                // \noindent

   0,                // \insertplot
   0,                // \position
   0,                // \bottom
   TX_ARG_NUM,       // \pheight=5 truecm
   TX_ARG_NUM,       // \pwidth=6 truecm
   TX_ARG_NUM,       // \pprocent=50
   TX_ARG_TXT,       // \ptype=\UNI
   TX_ARG_TXT,       // \pname=1 pav.
   TX_ARG_TXT,       // \ptext=tekstas tekstas   // text - up to next tag
   TX_ARG_TXT,       // \pfile=failovardas
   0,                // \pcorrections
   TX_ARG_NUM,       // \pvacor=-4cm
   0,                // \endinsertplot
   0,                // \UNI

   0,                // \bfi

   TX_ARG_NUM_GLUE,  // \leftskip=0.0cm   \leftskip=0pt plus 1fill

   0,                // TX_TG_BTH      // start of table definition
   TX_ARG_NUM,       // \tableno=1  // table order no
   TX_ARG_TXT,       // \tname=text // table heading
   TX_ARG_TXT,       // \tposition=\there
   0,                // \tcorrections
   0,                // \ETH      // end of table definition
   0,                // \BTF      // start of column definition
   1,                // \LC       // \LC{4.8cm}|\LC{0.3cm}|\LC{4.8cm} // column widths
   0,                // \ETF      // end of column definition
   0,                // TX_TG_BrightHorLine  // \=
   0,                // \BR       // start of row
   0,                // TX_TG_ThinHorLine  \_
   1,                // \CVB      // cell text, may be also free text, without \CVB
   0,                // TX_TG_NextColumn  // \| // column delimiter
   0,                // \ER       // end of row
   1,                // \NVS{6pt}   // verticl skip // TX_ARG_GLUE, but with as 1-st argument
   0,                // \EOT{\vskip-12pt} // end of table

   0,                // \after   // po
   0,                // \top     // virsuje
   0,                // \mid     // cia?
   0,                // \there   // cia!
// 0,                // \bottom  // apacioje
   0,                // \full    // visas puslapis
   0,                // \bpage   // pirma puslapyje
   0,                // \mpage   // puslapio viduryje
   0,                // \epage   // paskutine puslapyje
   TX_ARG_NUM,       // \tvacor=
   TX_ARG_NUM,       // \tvbcor=
   TX_ARG_NUM,       // \tvccor=
   TX_ARG_NUM,       // \tvdcor=

   TX_ARG_GLUE,      // \vskip50pt // skip vertically // pars - up to next tag
   TX_ARG_GLUE,      // \hskip6cm  // \hskip 0.3cm  // skip horizontally // pars - up to next tag

   0,                // \captionbottomtrue

   1,                // \alistind{2.}...  // list idn
   1,                // \alist{1.}...     // list entry idn
   0,                // \endlist

   0,                // \vfill
   0,                // \break
   0,                // \hfill

   0,                // \None
// 0,                // \UNI
   0,                // \HPX
   0,                // \PCZ
   0,                // \PS

   TX_ARG_NUM,       // \phcor
// TX_ARG_NUM,       // \pvacor
   TX_ARG_NUM,       // \pvbcor
   TX_ARG_NUM,       // \pvccor

   0,                // \newfam
   0,                // \cyrfam
   0,                // \font
   TX_ARG_TXT,       // \tencyr
   TX_ARG_TXT,       // \tencyi
   0,                // \cyr
   0,                // \cyi

   5,                // \INSERT

   0,                // \poliplottrue
   TX_ARG_REG,       // \setbox
   TX_ARG_TXT,       // \figbox=
   1,                // \vbox{}
// TX_ARG_NUM_GLUE,  // \leftskip=0pt plus 1fill
   TX_ARG_NUM_GLUE,  // \rightskip=0pt plus 1fill
   TX_ARG_NUM_GLUE,  // \hsize=8cm
// 1,                // \hbox{}
   TX_ARG_NUM_GLUE,  // \parindent=0pt  // indent of first paragraph line
   1,                // \MakeInsert{C}
// TX_ARG_GLUE,      // \hskip 0.3cm
// 0,                // \captionbottomtrue
   0,                // \plotcomment %Komentaras tarp brezinio ir pavadinimo
   0,                // \endplotcomment

   0,                // \medskip

   0,                // \null

   1,                // \headb{...}

   1,                // \list{1)} textas
// 0,

   0,                // \proff
   0,                // \pron

   0,                // \par

   0,                // \vfil
   0,                // \hfil
// 0,                // \vfill
// 0,                // \hfill
   0,                // \vfilll
   0,                // \hfilll

   1,                // \phantom // attach sublist to list // \list{\phantom{III. }}1. Skriptoriai -- perra÷inótojai.

   0,                // \hrulefill

   0,                // \eightpoint
   0,                // \ninepoint
   0,                // \tenpoint
   0,                // \twelvepoint

   0,                // \ldots

   0,                // \smallskip

   TX_ARG_TXT,       // \Longe
   TX_ARG_TXT,       // \Longm

   0,                // \vtop

   TX_ARG_TXT,       // \wasy

   0,                // \newbox
   0,                // \let

   TX_ARG_GLUE,      // \raise

   1,                // \eqalign

   0,                // \cr

   1,                // \CC
   0,                // \VR

   0,                // \underbrace
   0,                // \Ds
   TX_ARG_NUM_GLUE,  // \mathindent=-2cm
   2,                // \divid13 --> 1/3
   0,                // \co

   TX_ARG_NUM_GLUE,  // \hoffset
   TX_ARG_NUM_GLUE,  // \voffset
   TX_ARG_NUM_GLUE,  // \prulesize
   0,                // \newdimen
   0,                // \Null
   1,                // \leftline
   0,                // \DM
   TX_ARG_REG,       // \wd
   TX_ARG_REG,       // \box

   0,                // \leavevmode
   0,                // \zv

   0,                // TX_TG_nul

   0,                // \edef

   0,                // TX_TG_At

   0,                // \centerline
   1,                // \headt
   1,                // \headp

   2,                // \foot
   0,                // \mod
   1,                // \mathop

   0,                // \loadboldtrue
   0,                // \loadbfcaltrue
// 0,                // \loadgottrue
   0,                // \loadbfgottrue
// 0,                // \loadscrtrue
   0,                // \loadbfscrtrue
   0,                // \loadcurtrue
   0,                // \loadbfcurtrue

   0,                // \tt
   1,                // \undertext

   0,                // \sin
   0,                // \cos
   0,                // \tg
   0,                // \ctg
   0,                // \arcsin

   0,                // \Ettt
   0,                // \Svtt
   0,                // \Antt
   0,                // \sm

   0,                // \An
   0,                // \Cv
   0,                // \En
   0,                // \Et
   0,                // \In
   0,                // \Sv
   0,                // \Un
   0,                // \Ub
   0,                // \Zv
// 0,                // \an
   0,                // \cv
// 0,                // \en
// 0,                // \et
// 0,                // ???",                  //  TX_TG_in,      // = C_i_Ogon  // !!! does not exist
   0,                // \sv
// 0,                // \un
// 0,                // \ub
// 0,                // \zv
// 0,                // \Antt
   0,                // \Cvtt
   0,                // \Entt
// 0,                // \Ettt
   0,                // \Intt
// 0,                // \Svtt
   0,                // \Untt
   0,                // \Ubtt
   0,                // \Zvtt
   0,                // \antt
   0,                // \cvtt
   0,                // \entt
   0,                // \ettt
   0,                // \intt
   0,                // \svtt
   0,                // \untt
   0,                // \ubtt
   0,                // \zvtt

   1,                // \halign
   1,                // \noalign

   1,                // \cases

   TX_ARG_NUM_GLUE,  // \hangindent
   TX_ARG_NUM_GLUE,  // \hangafter

   0,                // \max
   0,                // \min

   TX_ARG_TXT_WIDE,  // \char

   2,                // \Dal

   1,                // \RC
   0,                // \me
   2,                // \multispan

   0,                // \TeX

   2,                // \boxitc

   0,                // \strut

   0,                // TX_TG_ItCor // "\/"

   0,                // \inott

   0,                // \helv
   0,                // \helvi
   0,                // \helvb
   0,                // \helvbi
   0,                // \helvm
   0,                // \helvim
   0,                // \helvbm
   0,                // \helvbim

   TX_ARG_GLUE,      // \kern

   0,                // \proofplottrue

   1,                // \rhr  // right running header
   1,                // \rhl  // left running header
   1,                // \rightrh  // right running header   // LMR
   1,                // \leftrh  // left running header   // LMR

   0,                // \topmatter   // LMR
   0,                // \endtopmatter   // LMR
   0,                // \gdef   // LMR
   0,                // \Title   // LMR

   TX_ARG_NUM_GLUE,  // \baselineskip=9pt plus.5pt minus.5pt

   1,                // \everypar

   0,                // \skipas

   0,                // \bye

   0,                // \fxr
   0,                // \fxx
   0,                // \frxx

   TX_ARG_TXT,       // %Stage=200
   TX_ARG_TXT,       // %Pages=15
   TX_ARG_TXT,       // %TID=ZAL_ALD   - typesetter id.

   TX_ARG_REG,       // 0, // \FS0, ... \FS9, \FSA, ... \FSZ, \FSa, ... \FSz

   0,                // \BD
   0,                // \BS

   2,                // \^^a1   // TX_TG_SP_CHAR

   TX_ARG_TXT_WIDE,  // TX_TG_catcode     \catcode`\^^a1=11
   TX_ARG_TXT_WIDE,  // TX_TG_lccode      \lccode`\^^a1=`\^^e1
   TX_ARG_TXT_WIDE,  // TX_TG_uccode      \uccode`\^^a1=`\^^a1

   TX_ARG_TXT_WIDE,  // TX_TG_ifnum
   TX_ARG_TXT_WIDE,  // TX_TG_ifx

   0,                // TX_TG_inputlineno
   0,                // TX_TG_undefined

   TX_ARG_TXT_WIDE,  // TX_TG_else
   0,                // TX_TG_fi

   1,                // TX_TG_patterns

   TX_ARG_TXT_WIDE,  // TX_TG_relax
   0,                // TX_TG_endinput
   1,                // TX_TG_message

   0,                // TX_TG_begingroup
   0,                // TX_TG_endgroup

   0,                // TX_TG_dash
   0,                // TX_TG_dtb

   0,                // TX_TG_settabs
   0,                // TX_TG_columns
   0,                // TX_TG_plus

   2,                // TX_TG_lastwordinpar

   TX_ARG_REG,       // TX_TG_fontdimen
   TX_ARG_NUM_GLUE,  // TX_TG_timacn

   0,                // TX_TG_LT
   0,                // TX_TG_DE
   0,                // TX_TG_EN
   0,                // TX_TG_FR
   0,                // TX_TG_PL

   1,                // TX_TG_raide
   1,                // TX_TG_theraide
   0,                // TX_TG_nuleisti
   1,                // TX_TG_hboxup

   0,                // TX_TG_global
   TX_ARG_TXT,       // TX_TG_LBOX // \global\setbox\LBOX=\hbox{}
   1,                // TX_TG_orwidth
   TX_ARG_TXT,       // TX_TG_hbox

   TX_ARG_TXT,       // TX_TG_xiivirm
   TX_ARG_TXT,       // TX_TG_xirm
   TX_ARG_TXT,       // TX_TG_xrm
   TX_ARG_TXT,       // TX_TG_xbf
   TX_ARG_TXT,       // TX_TG_xiivibf
   TX_ARG_TXT,       // TX_TG_xit

   0,                // TX_TG_Ccedil
   0,                // TX_TG_ccedil
   0,                // TX_TG_Sacute
   0,                // TX_TG_sacute

   0,                // TX_TG_plainparskip
   0,                // TX_TG_parskip

   0,                // TX_TG_timacnll

   1,                // TX_TG_thistable // \thistable{\desiredwidth=13.8cm}
   TX_ARG_NUM_GLUE,  // TX_TG_desiredwidth // \desiredwidth=13.8cm
   0,                // TX_TG_begintable
   0,                // TX_TG_begintableformat // \begintableformat&\left\endtableformat
   0,                // TX_TG_endtableformat
   0,                // TX_TG_left
   2,                // TX_TG_B // \B"+ {\bfp befehlen} " befehle, befiehlst, befiehlt " befahl " \E" 
   1,                // TX_TG_E

   0,                // TX_TG_bfp

   TX_ARG_NUM_GLUE,  // TX_TG_TRTH // \TRTH=0.8pt
   2,                // TX_TG_footnote
   0,                // TX_TG_VV

   0,                // TX_TG_endtable
   0,                // TX_TG_maketable

   0,                // TX_TG_endash

   0,                // TX_TG_itp

   0,                // TX_TG_BeginFileInfo
   TX_ARG_TXT,       // TX_TG_Manuscript
   TX_ARG_TXT,       // TX_TG_Company
   TX_ARG_TXT,       // TX_TG_ProFile
   TX_ARG_TXT,       // TX_TG_Compiler_cmd_line    // %%Compiler cmd line=LATEX612.BAT BENJAMIN PBNS %N
   TX_ARG_TXT,       // TX_TG_Send_to_DB
   0,                // TX_EndFileInfo
   2,                // TX_TG_documentclass     // \documentclass[pagframe,nameyear]{pbnsp} 
   1,                // TX_TG_usepackage        // \usepackage{draft}      // \usepackage[none]{draft}
   TX_ARG_GLUE,      // TX_TG_vrule       // \vrule height8pt depth3pt width0pt
   1,                // TX_TG_underline
   1,                // TX_TG_ut
   0,                // TX_TG_uline
   1,                // TX_TG_sut
   0,                // TX_TG_sout
   TX_ARG_NUM_GLUE,  // TX_TG_overfullrule  // \overfullrule=0pt
   0,                // TX_TG_INDEX
   0,                // TX_TG_psdraft
   1,                // TX_TG_vtexed
   1,                // TX_TG_volume
   1,                // TX_TG_issue
   1,                // TX_TG_pubyear
   TX_ARG_NUM,       // TX_TG_doublehyphendemerits    // \doublehyphendemerits=100000
   1,                // TX_TG_articletype
   1,                // TX_TG_begin    // \begin{document}
   0,                // TX_TG_Project_macro  // \def\Project{pbns143}
   1,                // TX_TG_pagenumbering // \pagenumbering{roman}
   0,                // TX_TG_printbookmarks
   1,                // TX_TG_figlink  // \figlink{0f0}
   1,                // TX_TG_caption
   1,                // TX_TG_label
   0,                // TX_TG_tablewidth
   1,                // TX_TG_extracolsep
   0,                // TX_TG_fill

   TX_ARG_GLUE,      // TX_TG_Exindent    // \Exindent-0.75cm
   1,                // TX_TG_ExVK        // \ExVK.[]
   2,                // TX_TG_MySize      // \MySize{8}{11}
   1,                // TX_TG_ex          // \ex.[]
   TX_ARG_NUM_GLUE,  // TX_TG_tableft     // \tableft=0cm
   TX_ARG_NUM_GLUE,  // TX_TG_tabcolsep   // \tabcolsep=0pt

   0,                // TX_TG_ttfamily

   0,                // TX_TG_ParEnd

   1,                // TX_TG_textit
   1,                // TX_TG_textsc
      
   1,                // TX_TG_tsub
   1,                // TX_TG_tsup
      
   1,                // TX_TG_Ex          // \Ex.[\phantom{(1)}]

   2,                // notetext          // \notetext[1.]{...}

   1,                // TX_TG_textbf

   0,                // TX_TG_longn

   1,                // TX_TG_textgr

   0,                // TX_TG_item

   1,                // TX_TG_textlt

   2,                // TX_TG_endfile

   0,                // TX_TG_bullet

   0,                // TX_TG_ecirc

   0,                // TX_TG_Ncedil
   0,                // TX_TG_ncedil
   0,                // TX_TG_Rcedil
   0,                // TX_TG_rcedil

   0,                // TX_TG_amp                    
   0,                // TX_TG_apos  
   0,                // TX_TG_ast                     

   0,                // TX_TG_lapos
   0,                // TX_TG_rapos
};


//-------------------------------------------
TexTagTypes iaMainTexTagTypes[TX_TG_NumOfTags132] =      // types of main TEX tags
{
   TexCtrl,          // TX_ARG_TXT_WIDE,  // \input
   TexKey,           // TX_ARG_NUM,       // \firstpage=1
   TexKey,           // TX_ARG_NUM,       // \lastpage=1
   TexCtrl,          // 0,                // \HPROOF
   TexCtrl,          // 0,                // \PROOF
   TexCtrl,          // 0,                // \CRC
   TexCtrl,          // 0,                // \VIEW
   TexCtrl,          // 0,                // \setparameters
   TexKey,           // TX_ARG_NUM,       // \lang
   TexTag,           // 1,                // \heada
   TexCtrl,          // 0,                // \titletrue

   TexCtrl,          // 0,                // TX_TG_ctbl_off,// switch off any code table
   TexCtrl,          // 0,                // \rm         // switch to roman font
   TexCtrl,          // 0,                // \rmr        // switch to russian roman font
   TexCtrl,          // 0,                // \got        // switch to gothic
   TexCtrl,          // 0,                // \cal        // switch to gothic

   TexCtrl,          // 0,                // \bf         // switch to bold font
   TexCtrl,          // 0,                // \it
   TexCtrl,          // 0,                // \mit

   TexCtrl,          // 0,                // \endpaper
   TexCtrl,          // 0,                // \loadgottrue

   TexCtrl,          // 1,                // \over
   TexCtrl,          // 1,                //    TX_TG_sqrt,   // \sqrt
   TexCtrl,          // 0,                //    TX_TG_root,   // \root
   TexCtrl,          // 1,                //    TX_TG_of,     // \of

   TexCtrl,  // TexDiacr, // 1,           // \hat
   TexCtrl,  // TexDiacr, // 1,           // \check
   TexCtrl,  // TexDiacr, // 1,           // \tilde
   TexCtrl,  // TexDiacr, // 1,           // \acute
   TexCtrl,  // TexDiacr, // 1,           // \grave
   TexCtrl,  // TexDiacr, // 1,           // \dot
   TexCtrl,  // TexDiacr, // 1,           // \ddot
   TexCtrl,  // TexDiacr, // 1,           // \breve
   TexCtrl,  // TexDiacr, // 1,           // \bar
   TexCtrl,  // TexDiacr, // 1,           // \vec
   TexCtrl,  // TexDiacr, // 1,           // \not

   TexTag,           // 1,                // \big",
   TexTag,           // 1,                // \bigl",
   TexTag,           // 1,                // \bigr",
   TexTag,           // 1,                // \Big",
   TexTag,           // 1,                // \Bigl",
   TexTag,           // 1,                // \Bigr",
   TexTag,           // 1,                // \bigg",
   TexTag,           // 1,                // \biggr",
   TexTag,           // 1,                // \biggl",
   TexTag,           // 1,                // \Bigg",
   TexTag,           // 1,                // \Biggr",
   TexTag,           // 1,                // \Biggl",

//!!! TexChar,       // 0,                // \leq
   TexChar,          // 0,                // \geq
   TexChar,          // 0,                // \neq

   TexChar,          // 0,                // \lbrace  {
   TexChar,          // 0,                // \rbrace  }
   TexChar,          // 0,                // \lbrack  [
   TexChar,          // 0,                // \rbrack  ]

   TexChar,          // 0,                // \to -->
   TexChar,          // 0,                // \gets <--
   TexChar,          // 0,                // \owns
   TexChar,          // 0,                //    TX_TG_land,   // logical and, \land C_wedge
   TexChar,          // 0,                //    TX_TG_lor,    // logical or, \lor C_vee
   TexChar,          // 0,                //    TX_TG_lnot,   // logical not, \neg C_Rminbr
   TexChar,          // 0,                //    TX_TG_vert,   // \vert C_Vertl
   TexChar,          // 0,                //    TX_TG_Vert,   // \Vert C_paral
   TexChar,          // 0,                //    TX_TG_paral,  // \| C_paral

   TexChar, // TexCtrl, // 0,             //    TX_TG_forc_sp,

   TexKey, // TexCtrl // 0,               // \def

   TexKey,           // TX_ARG_NUM,       // \pageno

   TexCtrl,          // 0,                // \begindoublecolumns

   TexChar, // 0, //   TX_TG_Ad,   // C_A_Acute
   TexChar, // 0, //   TX_TG_ad,   // C_a_Acute
   TexChar, // 0, //   TX_TG_And,  // C_A_Ogon_Acute
   TexChar, // 0, //   TX_TG_and,  // C_a_Ogon_Acute
   TexChar, // 0, //   TX_TG_Ed,   // C_E_Acute
   TexChar, // 0, //   TX_TG_ed,   // C_e_Acute
   TexChar, // 0, //   TX_TG_End__,// C_E_Ogon_Acute
   TexChar, // 0, //   TX_TG_end__,// C_e_Ogon_Acute
   TexChar, // 0, //   TX_TG_Etd,  // C_E_Adot_Acute
   TexChar, // 0, //   TX_TG_etd,  // C_e_Adot_Acute
   TexChar, // 0, //   TX_TG_Id,   // C_I_Acute
   TexChar, // 0, //   TX_TG_id,   // C_i_Acute
   TexChar, // 0, //   TX_TG_Ind,  // C_I_Ogon_Acute
   TexChar, // 0, //   TX_TG_ind,  // C_i_Ogon_Acute
   TexChar, // 0, //   TX_TG_Od,   // C_O_Acute
   TexChar, // 0, //   TX_TG_od,   // C_o_Acute
   TexChar, // 0, //   TX_TG_Ud,   // C_U_Acute
   TexChar, // 0, //   TX_TG_ud,   // C_u_Acute
   TexChar, // 0, //   TX_TG_Und,  // C_U_Ogon_Acute
   TexChar, // 0, //   TX_TG_und,  // C_u_Ogon_Acute
   TexChar, // 0, //   TX_TG_Ubd,  // C_U_Macr_Acute
   TexChar, // 0, //   TX_TG_ubd,  // C_u_Macr_Acute
   TexChar, // 0, //   TX_TG_Yd,   // C_Y_Acute
   TexChar, // 0, //   TX_TG_yd,   // C_y_Acute
   TexChar, // 0, //   TX_TG_Ak,   // C_A_Grave
   TexChar, // 0, //   TX_TG_ak,   // C_a_Grave
   TexChar, // 0, //   TX_TG_Ank,  // C_A_Ogon_Grave
   TexChar, // 0, //   TX_TG_ank,  // C_a_Ogon_Grave
   TexChar, // 0, //   TX_TG_Ek,   // C_E_Grave
   TexChar, // 0, //   TX_TG_ek,   // C_e_Grave
   TexChar, // 0, //   TX_TG_Enk,  // C_E_Ogon_Grave
   TexChar, // 0, //   TX_TG_enk,  // C_e_Ogon_Grave
   TexChar, // 0, //   TX_TG_Etk,  // C_E_Adot_Grave
   TexChar, // 0, //   TX_TG_etk,  // C_e_Adot_Grave
   TexChar, // 0, //   TX_TG_Ik,   // C_I_Grave
   TexChar, // 0, //   TX_TG_ik,   // C_i_Grave
   TexChar, // 0, //   TX_TG_Ink,  // C_I_Ogon_Grave
   TexChar, // 0, //   TX_TG_ink,  // C_i_Ogon_Grave
   TexChar, // 0, //   TX_TG_Ok,   // C_O_Grave
   TexChar, // 0, //   TX_TG_ok,   // C_o_Grave
   TexChar, // 0, //   TX_TG_Uk,   // C_U_Grave
   TexChar, // 0, //   TX_TG_uk,   // C_u_Grave
   TexChar, // 0, //   TX_TG_Unk,  // C_U_Ogon_Grave
   TexChar, // 0, //   TX_TG_unk,  // C_u_Ogon_Grave
   TexChar, // 0, //   TX_TG_Ubk,  // C_U_Macr_Grave
   TexChar, // 0, //   TX_TG_ubk,  // C_u_Macr_Grave
   TexChar, // 0, //   TX_TG_Yk,   // C_Y_Grave
   TexChar, // 0, //   TX_TG_yk,   // C_y_Grave
   TexChar, // 0, //   TX_TG_Ar,   // C_A_Tilde
   TexChar, // 0, //   TX_TG_ar,   // C_a_Tilde
   TexChar, // 0, //   TX_TG_Anr,  // C_A_Ogon_Tilde
   TexChar, // 0, //   TX_TG_anr,  // C_a_Ogon_Tilde
   TexChar, // 0, //   TX_TG_Er,   // C_E_Tilde
   TexChar, // 0, //   TX_TG_er,   // C_e_Tilde
   TexChar, // 0, //   TX_TG_Enr,  // C_E_Ogon_Tilde
   TexChar, // 0, //   TX_TG_enr,  // C_e_Ogon_Tilde
   TexChar, // 0, //   TX_TG_Etr,  // C_E_Adot_Tilde
   TexChar, // 0, //   TX_TG_etr,  // C_e_Adot_Tilde
   TexChar, // 0, //   TX_TG_Ir,   // C_I_Tilde
   TexChar, // 0, //   TX_TG_ir,   // C_i_Tilde
   TexChar, // 0, //   TX_TG_Inr,  // C_I_Ogon_Tilde
   TexChar, // 0, //   TX_TG_inr,  // C_i_Ogon_Tilde
   TexChar, // 0, //   TX_TG_Or,   // C_O_Tilde
   TexChar, // 0, //   TX_TG_or,   // C_o_Tilde
   TexChar, // 0, //   TX_TG_Ur,   // C_U_Tilde
   TexChar, // 0, //   TX_TG_ur,   // C_u_Tilde
   TexChar, // 0, //   TX_TG_Unr,  // C_U_Ogon_Tilde
   TexChar, // 0, //   TX_TG_unr,  // C_u_Ogon_Tilde
   TexChar, // 0, //   TX_TG_Ubr,  // C_U_Macr_Tilde
   TexChar, // 0, //   TX_TG_ubr,  // C_u_Macr_Tilde
   TexChar, // 0, //   TX_TG_Yr,   // C_Y_Tilde
   TexChar, // 0, //   TX_TG_yr,   // C_y_Tilde
   TexChar, // 0, //   TX_TG_Lr,   // C_L_Tilde
   TexChar, // 0, //   TX_TG_lr,   // C_l_Tilde
   TexChar, // 0, //   TX_TG_Mr,   // C_M_Tilde
   TexChar, // 0, //   TX_TG_mr,   // C_m_Tilde
   TexChar, // 0, //   TX_TG_Nr,   // C_N_Tilde
   TexChar, // 0, //   TX_TG_nr,   // C_n_Tilde
   TexChar, // 0, //   TX_TG_Rr,   // C_R_Tilde
   TexChar, // 0, //   TX_TG_rr,   // C_r_Tilde

   TexChar,          // 0,                // TX_TG_romb,
   TexChar,          // 0,                // TX_TG_bb,
   TexChar,          // 0,                // TX_TG_kid,
   TexChar,          // 0,                // TX_TG_Ndash,
   TexChar,          // 0,                // TX_TG_V,
   TexChar,          // 0,                // TX_TG_kam
   TexChar,          // 0,                // TX_TG_kav

   TexCtrl,          // 0,                // TX_TG_enddoublecolumns
   TexTag,           // 0,                // TX_TG_end

   TexChar,          // 0,                // TX_TG_et
   TexChar,          // 0,                // TX_TG_ub
   TexChar,          // 0,                // TX_TG_an
   TexChar,          // 0,                // TX_TG_en
   TexChar,          // 0,                // TX_TG_in // !!! does not exist
   TexChar,          // 0,                // TX_TG_ino
   TexChar,          // 0,                // TX_TG_un

   TexCtrl,          // 0,                // TX_TG_eject
   TexTag,           // 1,                // TX_TG_zmark

   TexChar,          // 0,                // TX_TG_ls
   TexChar,          // 0,                // TX_TG_gs

   TexKey,           // TX_ARG_NUM,       // TX_TG_looseness,
   TexGlue,          // TX_ARG_GLUE,// 1, // TX_TG_hbox, // \hbox{}  // \hbox to10.6cm{...}
   TexTag,           // 1,                // TX_TG_em,

   TexTag,           // 1,                // TX_TG_psl,

   TexCtrl,          // 0,                // TX_TG_MT,

   TexTag, // TexCtrl, // 0,              // TX_TG_vadjust

   TexCtrl,          // 0,                // TX_TG_NegQemSpc,

   TexTag,           // 1,                // TX_TG_scriptstyle,
   TexTag,           // 1,                // TX_TG_scriptscriptstyle,

   TexChar,          // 0,                // TX_TG_u_Brev

   TexCtrl,          // 0,                // \loadscrtrue

   TexKey,           // TX_ARG_TXT,       // %Project=LMR40
   TexKey,           // TX_ARG_TXT,       // %Publisher=TEV
   TexKey,           // TX_ARG_TXT,       // \typesetterid={NP}
   TexKey,           // TX_ARG_TXT,       // \paperid={info101}
   TexKey,           // TX_ARG_NUM,       // \statusno=0
   TexKey,           // TX_ARG_NUM,       // \switch=0

   TexCtrl,          // 0,                // \long
   TexCtrl,          // 0,                // \noindent

   TexCtrl,          // 0,                // \insertplot
   TexCtrl,          // 0,                // \position
   TexCtrl,          // 0,                // \bottom
   TexKey,           // TX_ARG_NUM,       // \pheight=5 truecm
   TexKey,           // TX_ARG_NUM,       // \pwidth=6 truecm
   TexKey,           // TX_ARG_NUM,       // \pprocent=50
   TexKey,           // TX_ARG_TXT,       // \ptype=\UNI
   TexKey,           // TX_ARG_TXT,       // \pname=1 pav.
   TexKey,           // TX_ARG_TXT,       // \ptext=tekstas tekstas   // text - up to next tag
   TexKey,           // TX_ARG_TXT,       // \pfile=failovardas
   TexCtrl,          // 0,                // \pcorrections
   TexKey,           // TX_ARG_NUM,       // \pvacor=-4cm
   TexCtrl,          // 0,                // \endinsertplot
   TexCtrl,          // 0,                // \UNI

   TexCtrl,          // 0,                // \bfi

   TexKey,           // TX_ARG_NUM_GLUE,  // \leftskip=0.0cm   \leftskip=0pt plus 1fill

   TexCtrl,          // 0,                // TX_TG_BTH      // start of table definition
   TexKey,           // TX_ARG_NUM,       // \tableno=1  // table order no
   TexKey,           // TX_ARG_TXT,       // \tname=text // table heading
   TexKey,           // TX_ARG_TXT,       // \tposition=\there
   TexCtrl,          // 0,                // \tcorrections
   TexCtrl,          // 0,                // \ETH      // end of table definition
   TexCtrl,          // 0,                // \BTF      // start of column definition
   TexTag,           // 1,                // \LC       // \LC{4.8cm}|\LC{0.3cm}|\LC{4.8cm} // column widths
   TexCtrl,          // 0,                // \ETF      // end of column definition
   TexCtrl,          // 0,                // TX_TG_BrightHorLine  // \=
   TexCtrl,          // 0,                // \BR       // start of row
   TexChar,          // 0,                // TX_TG_ThinHorLine  \_
   TexTag,           // 1,                // \CVB      // cell text, may be also free text, without \CVB
   TexCtrl,          // 0,                // TX_TG_NextColumn  // \| // column delimiter
   TexCtrl,          // 0,                // \ER       // end of row
   TexTag,           // 1,                // \NVS{6pt}   // verticl skip // TX_ARG_GLUE, but with as 1-st argument
   TexCtrl,          // 0,                // \EOT{\vskip-12pt} // end of table

   TexCtrl,          // 0,                // \after   // po
   TexCtrl,          // 0,                // \top     // virsuje
   TexCtrl,          // 0,                // \mid     // cia?
   TexCtrl,          // 0,                // \there   // cia!
// TexCtrl,          // 0,                // \bottom  // apacioje
   TexCtrl,          // 0,                // \full    // visas puslapis
   TexCtrl,          // 0,                // \bpage   // pirma puslapyje
   TexCtrl,          // 0,                // \mpage   // puslapio viduryje
   TexCtrl,          // 0,                // \epage   // paskutine puslapyje
   TexKey,           // TX_ARG_NUM,       // \tvacor=
   TexKey,           // TX_ARG_NUM,       // \tvbcor=
   TexKey,           // TX_ARG_NUM,       // \tvccor=
   TexKey,           // TX_ARG_NUM,       // \tvdcor=

   TexGlue,          // TX_ARG_GLUE,      // \vskip50pt // skip vertically // pars - up to next tag
   TexGlue,          // TX_ARG_GLUE,      // \hskip6cm  // \hskip 0.3cm  // skip horizontally // pars - up to next tag

   TexCtrl,          // 0,                // \captionbottomtrue

   TexTag,           // 1,                // \alistind{2.}...  // list idn
   TexTag,           // 1,                // \alist{1.}...     // list entry idn
   TexCtrl,          // 0,                // \endlist

   TexCtrl,          // 0,                // \vfill
   TexCtrl,          // 0,                // \break
   TexCtrl,          // 0,                // \hfill

   TexCtrl,          // 0,                // \None
// TexCtrl,          // 0,                // \UNI
   TexCtrl,          // 0,                // \HPX
   TexCtrl,          // 0,                // \PCZ
   TexCtrl,          // 0,                // \PS

   TexKey,           // TX_ARG_NUM,       // \phcor
// TexKey,           // TX_ARG_NUM,       // \pvacor
   TexKey,           // TX_ARG_NUM,       // \pvbcor
   TexKey,           // TX_ARG_NUM,       // \pvccor

   TexCtrl,          // 0,                // \newfam
   TexCtrl,          // 0,                // \cyrfam
   TexCtrl,          // 0,                // \font
   TexFont,          // TX_ARG_TXT,       // \tencyr
   TexFont,          // TX_ARG_TXT,       // \tencyi
   TexCtrl,          // 0,                // \cyr
   TexCtrl,          // 0,                // \cyi

   TexTag,           // 5,                // \INSERT

   TexCtrl,          // 0,                // \poliplottrue
   TexReg,           // TX_ARG_REG,       // \setbox
   TexKey,           // TX_ARG_TXT,       // \figbox=
   TexTag,           // 1,                // \vbox{}
// TexKey,           // TX_ARG_NUM_GLUE,  // \leftskip=0pt plus 1fill
   TexKey,           // TX_ARG_NUM_GLUE,  // \rightskip=0pt plus 1fill
   TexKey,           // TX_ARG_NUM_GLUE,  // \hsize=8cm
// TexTag,           // 1,                // \hbox{}
   TexKey,           // TX_ARG_NUM_GLUE,  // \parindent=0pt  // indent of first paragraph line
   TexTag,           // 1,                // \MakeInsert{C}
// TexGlue,          // TX_ARG_GLUE,      // \hskip 0.3cm
// TexCtrl,          // 0,                // \captionbottomtrue
   TexCtrl,          // 0,                // \plotcomment %Komentaras tarp brezinio ir pavadinimo
   TexCtrl,          // 0,                // \endplotcomment

   TexCtrl,          // 0,                // \medskip

   TexCtrl,          // 0,                // \null

   TexTag,           // 1,                // \headb{...}

   TexTag,           // 1, //  0,         // \list{1)} textas

   TexCtrl,          // 0,                // \proff
   TexCtrl,          // 0,                // \pron

   TexCtrl,          // 0,                // \par

   TexCtrl,          // 0,                // \vfil
   TexCtrl,          // 0,                // \hfil
// TexCtrl,          // 0,                // \vfill
// TexCtrl,          // 0,                // \hfill
   TexCtrl,          // 0,                // \vfilll
   TexCtrl,          // 0,                // \hfilll

   TexTag,           // 1,                // \phantom // attach sublist to list // \list{\phantom{III. }}1. Skriptoriai -- perra÷inótojai.

   TexCtrl,          // 0,                // \hrulefill

   TexCtrl,          // 0,                // \eightpoint
   TexCtrl,          // 0,                // \ninepoint
   TexCtrl,          // 0,                // \tenpoint
   TexCtrl,          // 0,                // \twelvepoint

   TexChar,          // 0,                // \ldots

   TexCtrl,          // 0,                // \smallskip

   TexFont,          // TX_ARG_TXT,       // \Longe
   TexFont,          // TX_ARG_TXT,       // \Longm

   TexCtrl,          // 0,                // \vtop

   TexFont,          // TX_ARG_TXT,       // \wasy

   TexCtrl,          // 0,                // \newbox
   TexCtrl,          // 0,                // \let

   TexGlue,          // TX_ARG_GLUE,      // \raise

   TexTag,           // 1,                // \eqalign

   TexCtrl,          // 0,                // \cr

   TexTag,           // 1,                // \CC
   TexCtrl,          // 0,                // \VR

   TexChar,          // 0,                // \underbrace
   TexCtrl,          // 0,                // \Ds
   TexKey,           // TX_ARG_NUM_GLUE,  // \mathindent=-2cm
   TexTag,           // 2,                // \divid13 --> 1/3
   TexCtrl,          // 0,                // \co

   TexKey,           // TX_ARG_NUM_GLUE,  // \hoffset
   TexKey,           // TX_ARG_NUM_GLUE,  // \voffset
   TexKey,           // TX_ARG_NUM_GLUE,  // \prulesize
   TexCtrl,          // 0,                // \newdimen
   TexCtrl,          // 0,                // \Null
   TexTag,           // 1,                // \leftline
   TexChar,          // 0,                // \DM
   TexReg,           // TX_ARG_REG,       // \wd
   TexReg,           // TX_ARG_REG,       // \box

   TexCtrl,          // 0,                // \leavevmode
   TexChar,          // 0,                // \zv

   TexCtrl,          // 0,                // TX_TG_nul

   TexCtrl,          // 0,                // \edef

   TexChar,          // 0,                // TX_TG_At

   TexChar,          // 0,                // \centerline
   TexTag,           // 1,                // \headt
   TexTag,           // 1,                // \headp

   TexTag,           // 2,                // \foot
   TexChar,          // 0,                // \mod
   TexTag,           // 1,                // \mathop

   TexCtrl,          // 0,                // \loadboldtrue
   TexCtrl,          // 0,                // \loadbfcaltrue
// TexCtrl,          // 0,                // \loadgottrue
   TexCtrl,          // 0,                // \loadbfgottrue
// TexCtrl,          // 0,                // \loadscrtrue
   TexCtrl,          // 0,                // \loadbfscrtrue
   TexCtrl,          // 0,                // \loadcurtrue
   TexCtrl,          // 0,                // \loadbfcurtrue

   TexCtrl,          // 0,                // \tt
   TexTag,           // 1,                // \undertext

   TexCtrl,          // 0,                // \sin
   TexCtrl,          // 0,                // \cos
   TexCtrl,          // 0,                // \tg
   TexCtrl,          // 0,                // \ctg
   TexCtrl,          // 0,                // \arcsin

   TexChar,          // 0,                // \Ettt
   TexChar,          // 0,                // \Svtt
   TexChar,          // 0,                // \Antt
   TexChar,          // 0,                // \sm

   TexChar,          // 0,                // \An
   TexChar,          // 0,                // \Cv
   TexChar,          // 0,                // \En
   TexChar,          // 0,                // \Et
   TexChar,          // 0,                // \In
   TexChar,          // 0,                // \Sv
   TexChar,          // 0,                // \Un
   TexChar,          // 0,                // \Ub
   TexChar,          // 0,                // \Zv
// TexChar,          // 0,                // \an
   TexChar,          // 0,                // \cv
// TexChar,          // 0,                // \en
// TexChar,          // 0,                // \et
// TexChar,          // 0,                // ???",                  //  TX_TG_in,      // = C_i_Ogon  // !!! does not exist
   TexChar,          // 0,                // \sv
// TexChar,          // 0,                // \un
// TexChar,          // 0,                // \ub
// TexChar,          // 0,                // \zv
// TexChar,          // 0,                // \Antt
   TexChar,          // 0,                // \Cvtt
   TexChar,          // 0,                // \Entt
// TexChar,          // 0,                // \Ettt
   TexChar,          // 0,                // \Intt
// TexChar,          // 0,                // \Svtt
   TexChar,          // 0,                // \Untt
   TexChar,          // 0,                // \Ubtt
   TexChar,          // 0,                // \Zvtt
   TexChar,          // 0,                // \antt
   TexChar,          // 0,                // \cvtt
   TexChar,          // 0,                // \entt
   TexChar,          // 0,                // \ettt
   TexChar,          // 0,                // \intt
   TexChar,          // 0,                // \svtt
   TexChar,          // 0,                // \untt
   TexChar,          // 0,                // \ubtt
   TexChar,          // 0,                // \zvtt

   TexTag,           // 1,                // \halign
   TexTag,           // 1,                // \noalign

   TexTag,           // 1,                // \cases

   TexKey,           // TX_ARG_NUM_GLUE,  // \hangindent
   TexKey,           // TX_ARG_NUM_GLUE,  // \hangafter

   TexCtrl,          // 0,                // \max
   TexCtrl,          // 0,                // \min

   TexKey,           // 0,                // \char

   TexTag,           // 2,                // \Dal

   TexTag,           // 1,                // \RC
   TexCtrl,          // 0,                // \me
   TexTag,           // 2,                // \multispan

   TexChar,          // 0,                // \TeX

   TexTag,           // 2,                // \boxitc

   TexCtrl,          // 0,                // \strut

   TexCtrl,          // 0,                // TX_TG_ItCor // "\/"

   TexCtrl,          // 0,                // \inott

   TexCtrl,          // 0,                // \helv
   TexCtrl,          // 0,                // \helvi
   TexCtrl,          // 0,                // \helvb
   TexCtrl,          // 0,                // \helvbi
   TexCtrl,          // 0,                // \helvm
   TexCtrl,          // 0,                // \helvim
   TexCtrl,          // 0,                // \helvbm
   TexCtrl,          // 0,                // \helvbim

   TexGlue,          // TX_ARG_GLUE,      // \kern

   TexCtrl,          // 0,                // \proofplottrue

   TexTag,           // 1,                // \rhr  // right running header
   TexTag,           // 1,                // \rhl  // left running header
   TexTag,           // 1,                // \rightrh  // right running header   // LMR
   TexTag,           // 1,                // \leftrh  // left running header   // LMR

   TexCtrl,          // 0,                // \topmatter   // LMR
   TexCtrl,          // 0,                // \endtopmatter   // LMR
   TexCtrl,          // 0,                // \gdef   // LMR
   TexCtrl,          // 0,                // \Title   // LMR

   TexKey,           // TX_ARG_NUM_GLUE,  // \baselineskip=9pt plus.5pt minus.5pt

   TexTag,           // 1,                // \everypar

   TexCtrl,          // 0,                // \skipas

   TexCtrl,          // 0,                // \bye

   TexCtrl,          // 0,                // \fxr
   TexCtrl,          // 0,                // \fxx
   TexCtrl,          // 0,                // \frxx

   TexKey,           // TX_ARG_TXT,       // %Stage=200
   TexKey,           // TX_ARG_TXT,       // %Pages=15
   TexKey,           // TX_ARG_TXT,       // %TID=ZAL_ALD   - typesetter id.

   TexReg,           // TX_ARG_REG,       // \FS0, ... \FS9, \FSA, ... \FSZ, \FSa, ... \FSz

   TexChar,          // 0,                // \BD
   TexChar,          // 0,                // \BS

   TexKey,           // 2,                // \^^a1   // TX_TG_SP_CHAR

   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_catcode
   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_lccode
   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_uccode

   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_ifnum
   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_ifx

   TexKey,           // 0,                // TX_TG_inputlineno
   TexKey,           // 0,                // TX_TG_undefined

   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_else
   TexKey,           // 0,                // TX_TG_fi

   TexTag,           // 1,                // TX_TG_patterns

   TexKey,           // TX_ARG_TXT_WIDE,  // TX_TG_relax
   TexCtrl,          // 0,                // TX_TG_endinput
   TexTag,           // 1,                // TX_TG_message

   TexCtrl,          // 0,                // TX_TG_begingroup
   TexCtrl,          // 0,                // TX_TG_endgroup

   TexChar,          // 0,                // TX_TG_dash
   TexChar,          // 0,                // TX_TG_dtb

   TexCtrl,          // 0,                // TX_TG_settabs
   TexCtrl,          // 0,                // TX_TG_columns
   TexCtrl,          // 0,                // TX_TG_plus

   TexTag,           // 2,                // TX_TG_lastwordinpar

   TexReg,           // TX_ARG_REG,       // TX_TG_fontdimen
   TexKey,           // TX_ARG_NUM_GLUE,  // TX_TG_timacn

   TexCtrl,          // 0,                // TX_TG_LT
   TexCtrl,          // 0,                // TX_TG_DE
   TexCtrl,          // 0,                // TX_TG_EN
   TexCtrl,          // 0,                // TX_TG_FR
   TexCtrl,          // 0,                // TX_TG_PL

   TexTag,           // 1,                // TX_TG_raide
   TexTag,           // 1,                // TX_TG_theraide
   TexCtrl,          // 0,                // TX_TG_nuleisti
   TexTag,           // 1,                // TX_TG_hboxup

   TexCtrl,          // 0,                // TX_TG_global
   TexVar,           // TX_ARG_TXT,       // TX_TG_LBOX // \global\setbox\LBOX=\hbox{}
   TexTag,           // 1,                // TX_TG_orwidth
   TexVar,           // TX_ARG_TXT,       // TX_TG_hbox

   TexFont,          // TX_ARG_TXT,       // TX_TG_xiivirm
   TexFont,          // TX_ARG_TXT,       // TX_TG_xirm
   TexFont,          // TX_ARG_TXT,       // TX_TG_xrm
   TexFont,          // TX_ARG_TXT,       // TX_TG_xbf
   TexFont,          // TX_ARG_TXT,       // TX_TG_xiivibf
   TexFont,          // TX_ARG_TXT,       // TX_TG_xit

   TexChar,          // 0,                // TX_TG_Ccedil
   TexChar,          // 0,                // TX_TG_ccedil
   TexChar,          // 0,                // TX_TG_Sacute
   TexChar,          // 0,                // TX_TG_sacute

   TexCtrl,          // 0,                // TX_TG_plainparskip
   TexCtrl,          // 0,                // TX_TG_parskip

   TexCtrl,          // 0,                // TX_TG_timacnll

   TexTag,           // 1,                // TX_TG_thistable // \thistable{\desiredwidth=13.8cm}
   TexKey,           // TX_ARG_NUM_GLUE,  // TX_TG_desiredwidth // \desiredwidth=13.8cm
   TexCtrl,          // 0,                // TX_TG_begintable
   TexCtrl,          // 0,                // TX_TG_begintableformat // \begintableformat&\left\endtableformat
   TexCtrl,          // 0,                // TX_TG_endtableformat
   TexCtrl,          // 0,                // TX_TG_left
   TexTag,           // 2,                // TX_TG_B // \B"+ {\bfp befehlen} " befehle, befiehlst, befiehlt " befahl " \E" 
   TexTag,           // 1,                // TX_TG_E

   TexCtrl,          // 0,                // TX_TG_bfp

   TexKey,           // TX_ARG_NUM_GLUE,  // TX_TG_TRTH // \TRTH=0.8pt
   TexTag,           // 2,                // TX_TG_footnote
   TexCtrl,          // 0,                // TX_TG_VV

   TexCtrl,          // 0,                // TX_TG_endtable
   TexCtrl,          // 0,                // TX_TG_maketable

   TexChar,          // 0,                // TX_TG_endash,

   TexCtrl,          // 0,                // TX_TG_itp

   TexCtrl,          // 0,                // TX_TG_BeginFileInfo
   TexKey,           // TX_ARG_TXT,       // TX_TG_Manuscript
   TexKey,           // TX_ARG_TXT,       // TX_TG_Company
   TexKey,           // TX_ARG_TXT,       // TX_TG_ProFile
   TexKey,           // TX_ARG_TXT,       // TX_TG_Compiler_cmd_line    // %%Compiler cmd line=LATEX612.BAT BENJAMIN PBNS %N
   TexKey,           // TX_ARG_TXT,       // TX_TG_Send_to_DB
   TexCtrl,          // 0,                // TX_EndFileInfo
   TexTag,           // 2,                // TX_TG_documentclass     // \documentclass[pagframe,nameyear]{pbnsp} 
   TexTag,           // 1,                // TX_TG_usepackage        // \usepackage{draft}      // \usepackage[none]{draft}
   TexGlue,          // TX_ARG_GLUE,      // TX_TG_vrule       // \vrule height8pt depth3pt width0pt
   TexTag,           // 1,                // TX_TG_underline
   TexTag,           // 1,                // TX_TG_ut
   TexCtrl,          // 0,                // TX_TG_uline
   TexTag,           // 1,                // TX_TG_sut
   TexCtrl,          // 0,                // TX_TG_sout
   TexKey,           // TX_ARG_NUM_GLUE,  // TX_TG_overfullrule  // \overfullrule=0pt
   TexCtrl,          // 0,                // TX_TG_INDEX
   TexCtrl,          // 0,                // TX_TG_psdraft
   TexTag,           // 1,                // TX_TG_vtexed
   TexTag,           // 1,                // TX_TG_volume
   TexTag,           // 1,                // TX_TG_issue
   TexTag,           // 1,                // TX_TG_pubyear
   TexKey,           // TX_ARG_NUM,       // TX_TG_doublehyphendemerits    // \doublehyphendemerits=100000
   TexTag,           // 1,                // TX_TG_articletype
   TexTag,           // 1,                // TX_TG_begin    // \begin{document}
   TexCtrl,          // 1,                // TX_TG_Project_macro  // \def\Project{pbns143}
   TexTag,           // 1,                // TX_TG_pagenumbering // \pagenumbering{roman}
   TexCtrl,          // 0,                // TX_TG_printbookmarks
   TexTag,           // 1,                // TX_TG_figlink  // \figlink{0f0}
   TexTag,           // 1,                // TX_TG_caption
   TexTag,           // 1,                // TX_TG_label
   TexCtrl,          // 0,                // TX_TG_tablewidth
   TexTag,           // 1,                // TX_TG_extracolsep
   TexCtrl,          // 0,                // TX_TG_fill

   TexGlue,          // TX_ARG_GLUE,      // TX_TG_Exindent    // \Exindent-0.75cm
   TexTag,           // 1,                // TX_TG_ExVK        // \ExVK.[]
   TexTag,           // 2,                // TX_TG_MySize      // \MySize{8}{11}
   TexTag,           // 1,                // TX_TG_ex          // \ex.[]
   TexKey,           // TX_ARG_GLUE,      // TX_TG_tableft     // \tableft=0cm
   TexKey,           // TX_ARG_GLUE,      // TX_TG_tabcolsep   // \tabcolsep=0pt

   TexCtrl,          // 0,                // TX_TG_ttfamily

   TexCtrl,          // 0,                // TX_TG_ParEnd

   TexTag,           // 1,                // TX_TG_textit
   TexTag,           // 1,                // TX_TG_textsc

   TexTag,           // 1,                // TX_TG_tsub
   TexTag,           // 1,                // TX_TG_tsup

   TexTag,           // 1,                // TX_TG_Ex          // \Ex.[\phantom{(1)}]

   TexTag,           // 2,                // notetext          // \notetext[1.]{...}

   TexTag,           // 1,                // TX_TG_textbf

   TexCtrl,          // 0,                // TX_TG_longn

   TexTag,           // 1,                // TX_TG_textgr

   TexCtrl,          // 0,                // TX_TG_item

   TexTag,           // 1,                // TX_TG_textul

   TexTag,           // 2,                // TX_TG_endfile

   TexChar,          // 0,                // TX_TG_bullet

   TexChar,          // 0,                // TX_TG_ecirc

   TexChar,          // 0,                // TX_TG_Ncedil
   TexChar,          // 0,                // TX_TG_ncedil
   TexChar,          // 0,                // TX_TG_Rcedil
   TexChar,          // 0,                // TX_TG_rcedil

   TexChar,          // 0,                // TX_TG_amp                    
   TexChar,          // 0,                // TX_TG_apos  
   TexChar,          // 0,                // TX_TG_ast                     

   TexChar,          // 0,                // TX_TG_lapos
   TexChar,          // 0,                // TX_TG_rapos
};


//----------------------------------------------
// alias table
int iaTexTagVariations[] =
{
#if FALSE
   TX_TG_hat,     C_CircAcc,     TX_FORMULA_FIELD,
   TX_TG_check,   C_Car,         TX_FORMULA_FIELD,
   TX_TG_tilde,   C_TildeAcc,    TX_FORMULA_FIELD,
   TX_TG_acute,   C_Acute,       TX_FORMULA_FIELD,
   TX_TG_grave,   C_GraveAcc,    TX_FORMULA_FIELD,
   TX_TG_dot,     C_Adot,        TX_FORMULA_FIELD,
   TX_TG_ddot,    C_Diaer,       TX_FORMULA_FIELD,
   TX_TG_breve,   C_BreveAcc,    TX_FORMULA_FIELD,
   TX_TG_bar,     C_Macr,        TX_FORMULA_FIELD,
   TX_TG_vec,     C_Nul,         TX_FORMULA_FIELD,
   TX_TG_not,     C_SlashAcc,    TX_FORMULA_FIELD,
#endif

#if FALSE
   C_CircAcc,     TX_TG_hat,     TX_TEXT_FIELD,
   C_Car,         TX_TG_check,   TX_TEXT_FIELD,
   C_TildeAcc,    TX_TG_tilde,   TX_TEXT_FIELD,
   C_Acute,       TX_TG_acute,   TX_TEXT_FIELD,
   C_GraveAcc,    TX_TG_grave,   TX_TEXT_FIELD,
   C_Adot,        TX_TG_dot,     TX_TEXT_FIELD,
   C_Diaer,       TX_TG_ddot,    TX_TEXT_FIELD,
   C_BreveAcc,    TX_TG_breve,   TX_TEXT_FIELD,
   C_Macr,        TX_TG_bar,     TX_TEXT_FIELD,
   C_SlashAcc,    TX_TG_not,     TX_TEXT_FIELD,
   C_Dacut,       C_Nul,         TX_TEXT_FIELD,
   C_Ring,        C_Nul,         TX_TEXT_FIELD,
#endif

#if FALSE
   C_Alpha,       C_Nul,         TX_FORMULA_FIELD,
   C_Beta,        C_Nul,         TX_FORMULA_FIELD,
   C_Gamma,       C_Nul,         TX_FORMULA_FIELD,
   C_Delta,       C_Nul,         TX_FORMULA_FIELD,
   C_Epsilon,     C_Nul,         TX_FORMULA_FIELD,
   C_Zeta,        C_Nul,         TX_FORMULA_FIELD,
   C_Eta,         C_Nul,         TX_FORMULA_FIELD,
   C_Theta,       C_Nul,         TX_FORMULA_FIELD,
   C_Jota,        C_Nul,         TX_FORMULA_FIELD,
   C_Kappa,       C_Nul,         TX_FORMULA_FIELD,
   C_Lambda,      C_Nul,         TX_FORMULA_FIELD,
   C_My,          C_Nul,         TX_FORMULA_FIELD,
   C_Ny,          C_Nul,         TX_FORMULA_FIELD,
   C_Xi,          C_Nul,         TX_FORMULA_FIELD,
   C_Omikron,     C_Nul,         TX_FORMULA_FIELD,
   C_Pi,          C_Nul,         TX_FORMULA_FIELD,
   C_Rho,         C_Nul,         TX_FORMULA_FIELD,
   C_Sigma,       C_Nul,         TX_FORMULA_FIELD,
   C_Tau,         C_Nul,         TX_FORMULA_FIELD,
   C_Ypsilon,     C_Nul,         TX_FORMULA_FIELD,
   C_Phi,         C_Nul,         TX_FORMULA_FIELD,
   C_Chi,         C_Nul,         TX_FORMULA_FIELD,
   C_Psi,         C_Nul,         TX_FORMULA_FIELD,
   C_Omega,       C_Nul,         TX_FORMULA_FIELD,

   C_alpha,       C_Nul,         TX_FORMULA_FIELD,
   C_beta,        C_Nul,         TX_FORMULA_FIELD,
   C_gamma,       C_Nul,         TX_FORMULA_FIELD,
   C_delta,       C_Nul,         TX_FORMULA_FIELD,
   C_epsilon,     C_Nul,         TX_FORMULA_FIELD,
   C_zeta,        C_Nul,         TX_FORMULA_FIELD,
   C_eta,         C_Nul,         TX_FORMULA_FIELD,
   C_theta,       C_Nul,         TX_FORMULA_FIELD,
   C_jota,        C_Nul,         TX_FORMULA_FIELD,
   C_kappa,       C_Nul,         TX_FORMULA_FIELD,
   C_lambda,      C_Nul,         TX_FORMULA_FIELD,
   C_my,          C_Nul,         TX_FORMULA_FIELD,
   C_ny,          C_Nul,         TX_FORMULA_FIELD,
   C_xi,          C_Nul,         TX_FORMULA_FIELD,
   C_omikron,     C_Nul,         TX_FORMULA_FIELD,
   C_pi,          C_Nul,         TX_FORMULA_FIELD,
   C_rho,         C_Nul,         TX_FORMULA_FIELD,
   C_sigma,       C_Nul,         TX_FORMULA_FIELD,
   C_tau,         C_Nul,         TX_FORMULA_FIELD,
   C_ypsilon,     C_Nul,         TX_FORMULA_FIELD,
   C_phi,         C_Nul,         TX_FORMULA_FIELD,
   C_chi,         C_Nul,         TX_FORMULA_FIELD,
   C_psi,         C_Nul,         TX_FORMULA_FIELD,
   C_omega,       C_Nul,         TX_FORMULA_FIELD,

   C_epsilon_var, C_Nul,         TX_FORMULA_FIELD,
   C_theta_var,   C_Nul,         TX_FORMULA_FIELD,
   C_DiGamma,     C_Nul,         TX_FORMULA_FIELD,
   C_digamma,     C_Nul,         TX_FORMULA_FIELD,
   C_kappa_var,   C_Nul,         TX_FORMULA_FIELD,
   C_DiLambda,    C_Nul,         TX_FORMULA_FIELD,
   C_dilambda,    C_Nul,         TX_FORMULA_FIELD,
   C_pi_var,      C_Nul,         TX_FORMULA_FIELD,
   C_rho_var,     C_Nul,         TX_FORMULA_FIELD,
   C_Sigma_var,   C_Nul,         TX_FORMULA_FIELD,
   C_sigma_var,   C_Nul,         TX_FORMULA_FIELD,
   C_phi_var,     C_Nul,         TX_FORMULA_FIELD,

   C_Lpoint,      C_Nul,         TX_FORMULA_FIELD,
// C_Dots,        C_Nul,         TX_FORMULA_FIELD,
   C_Multipl,     C_Nul,         TX_FORMULA_FIELD,
   C_Divide,      C_Nul,         TX_FORMULA_FIELD,
   C_PlMin,       C_Nul,         TX_FORMULA_FIELD,
   C_Rminbr,      C_Nul,         TX_FORMULA_FIELD,
   C_prim,        C_Nul,         TX_FORMULA_FIELD,
// C_dprim,       C_Nul,         TX_FORMULA_FIELD,
   C_Each,        C_Nul,         TX_FORMULA_FIELD,
   C_Exists,      C_Nul,         TX_FORMULA_FIELD,
   C_Aleph,       C_Nul,         TX_FORMULA_FIELD,
   C_Im,          C_Nul,         TX_FORMULA_FIELD,
   C_Re,          C_Nul,         TX_FORMULA_FIELD,
   C_wp,          C_Nul,         TX_FORMULA_FIELD,
   C_le,          C_Nul,         TX_FORMULA_FIELD,
   C_ge,          C_Nul,         TX_FORMULA_FIELD,
   C_ne,          C_Nul,         TX_FORMULA_FIELD,
   C_ll,          C_Nul,         TX_FORMULA_FIELD,
   C_gg,          C_Nul,         TX_FORMULA_FIELD,
   C_sim,         C_Nul,         TX_FORMULA_FIELD,
   C_simeq,       C_Nul,         TX_FORMULA_FIELD,
   C_approx,      C_Nul,         TX_FORMULA_FIELD,
   C_cong,        C_Nul,         TX_FORMULA_FIELD,
   C_equiv,       C_Nul,         TX_FORMULA_FIELD,
// C_sqrt,        C_Nul,         TX_FORMULA_FIELD,
   C_int,         C_Nul,         TX_FORMULA_FIELD,
   C_oint,        C_Nul,         TX_FORMULA_FIELD,
   C_Sum,         C_Nul,         TX_FORMULA_FIELD,
   C_Prod,        C_Nul,         TX_FORMULA_FIELD,
   C_O_times,     C_Nul,         TX_FORMULA_FIELD,
   C_O_plus,      C_Nul,         TX_FORMULA_FIELD,
   C_infty,       C_Nul,         TX_FORMULA_FIELD,
   C_infty,       C_Nul,         TX_FORMULA_FIELD,
   C_propto,      C_Nul,         TX_FORMULA_FIELD,
   C_part,        C_Nul,         TX_FORMULA_FIELD,
   C_empty,       C_Nul,         TX_FORMULA_FIELD,
   C_triangle,    C_Nul,         TX_FORMULA_FIELD,
   C_nabla,       C_Nul,         TX_FORMULA_FIELD,
   C_perp,        C_Nul,         TX_FORMULA_FIELD,
   C_angle,       C_Nul,         TX_FORMULA_FIELD,
   C_langle,      C_Nul,         TX_FORMULA_FIELD,
   C_rangle,      C_Nul,         TX_FORMULA_FIELD,
   C_cap,         C_Nul,         TX_FORMULA_FIELD,
   C_cup,         C_Nul,         TX_FORMULA_FIELD,
   C_vee,         C_Nul,         TX_FORMULA_FIELD,
   C_wedge,       C_Nul,         TX_FORMULA_FIELD,
   C_supset,      C_Nul,         TX_FORMULA_FIELD,
   C_supseteq,    C_Nul,         TX_FORMULA_FIELD,
   C_subset,      C_Nul,         TX_FORMULA_FIELD,
   C_subseteq,    C_Nul,         TX_FORMULA_FIELD,
   C_nsubset,     C_Nul,         TX_FORMULA_FIELD,
   C_in,          C_Nul,         TX_FORMULA_FIELD,
   C_notin,       C_Nul,         TX_FORMULA_FIELD,
   C_ni,          C_Nul,         TX_FORMULA_FIELD,
   C_leftarr,     C_Nul,         TX_FORMULA_FIELD,
   C_rightarr,    C_Nul,         TX_FORMULA_FIELD,
   C_leftrightarr,C_Nul,         TX_FORMULA_FIELD,
   C_uparr,       C_Nul,         TX_FORMULA_FIELD,
   C_downarr,     C_Nul,         TX_FORMULA_FIELD,
   C_updownarr,   C_Nul,         TX_FORMULA_FIELD,
   C_Leftarr,     C_Nul,         TX_FORMULA_FIELD,
   C_Rightarr,    C_Nul,         TX_FORMULA_FIELD,
   C_Leftrightarr,C_Nul,         TX_FORMULA_FIELD,
   C_Uparr,       C_Nul,         TX_FORMULA_FIELD,
   C_Downarr,     C_Nul,         TX_FORMULA_FIELD,
   C_Updownarr,   C_Nul,         TX_FORMULA_FIELD,
   C_mid,         C_Nul,         TX_FORMULA_FIELD,
   C_paral,       C_Nul,         TX_FORMULA_FIELD,
#endif

//!!!   TX_TG_leq,     C_le,          TX_FORMULA_FIELD,
   TX_TG_geq,     C_ge,          TX_FORMULA_FIELD,
   TX_TG_neq,     C_ne,          TX_FORMULA_FIELD,
   TX_TG_ls,      C_le,          TX_FORMULA_FIELD,
   TX_TG_gs,      C_ge,          TX_FORMULA_FIELD,

   TX_TG_lbrace,  C_Lcurl,       TX_FORMULA_FIELD,
   TX_TG_rbrace,  C_Rcurl,       TX_FORMULA_FIELD,
   TX_TG_lbrack,  C_Lbrack,      TX_FORMULA_FIELD, // \lbrack  [
   TX_TG_rbrack,  C_Rbrack,      TX_FORMULA_FIELD, // \rbrack  ]

   TX_TG_to,      C_rightarr,    TX_FORMULA_FIELD,
   TX_TG_gets,    C_leftarr,     TX_FORMULA_FIELD,
   TX_TG_owns,    C_ni,          TX_FORMULA_FIELD,
   TX_TG_land,    C_wedge,       TX_FORMULA_FIELD,
   TX_TG_lor,     C_vee,         TX_FORMULA_FIELD,
   TX_TG_lnot,    C_Rminbr,      TX_FORMULA_FIELD,
   TX_TG_vert,    C_Vertl,       TX_FORMULA_FIELD,
   TX_TG_Vert,    C_paral,       TX_FORMULA_FIELD,
   TX_TG_paral,   C_paral,       TX_FORMULA_FIELD,

   TX_TG_Ad,      C_A_Acute,     TX_TEXT_FIELD,
   TX_TG_ad,      C_a_Acute,     TX_TEXT_FIELD,
   TX_TG_And,     C_A_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_and,     C_a_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_Ed,      C_E_Acute,     TX_TEXT_FIELD,
   TX_TG_ed,      C_e_Acute,     TX_TEXT_FIELD,
   TX_TG_End__,   C_E_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_end__,   C_e_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_Etd,     C_E_Adot_Acute, TX_TEXT_FIELD,
   TX_TG_etd,     C_e_Adot_Acute, TX_TEXT_FIELD,
   TX_TG_Id,      C_I_Acute,     TX_TEXT_FIELD,
   TX_TG_id,      C_i_Acute,     TX_TEXT_FIELD,
   TX_TG_Ind,     C_I_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_ind,     C_i_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_Od,      C_O_Acute,     TX_TEXT_FIELD,
   TX_TG_od,      C_o_Acute,     TX_TEXT_FIELD,
   TX_TG_Ud,      C_U_Acute,     TX_TEXT_FIELD,
   TX_TG_ud,      C_u_Acute,     TX_TEXT_FIELD,
   TX_TG_Und,     C_U_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_und,     C_u_Ogon_Acute, TX_TEXT_FIELD,
   TX_TG_Ubd,     C_U_Macr_Acute, TX_TEXT_FIELD,
   TX_TG_ubd,     C_u_Macr_Acute, TX_TEXT_FIELD,
   TX_TG_Yd,      C_Y_Acute,     TX_TEXT_FIELD,
   TX_TG_yd,      C_y_Acute,     TX_TEXT_FIELD,
   TX_TG_Ak,      C_A_Grave,     TX_TEXT_FIELD,
   TX_TG_ak,      C_a_Grave,     TX_TEXT_FIELD,
   TX_TG_Ank,     C_A_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_ank,     C_a_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_Ek,      C_E_Grave,     TX_TEXT_FIELD,
   TX_TG_ek,      C_e_Grave,     TX_TEXT_FIELD,
   TX_TG_Enk,     C_E_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_enk,     C_e_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_Etk,     C_E_Adot_Grave, TX_TEXT_FIELD,
   TX_TG_etk,     C_e_Adot_Grave, TX_TEXT_FIELD,
   TX_TG_Ik,      C_I_Grave,     TX_TEXT_FIELD,
   TX_TG_ik,      C_i_Grave,     TX_TEXT_FIELD,
   TX_TG_Ink,     C_I_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_ink,     C_i_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_Ok,      C_O_Grave,     TX_TEXT_FIELD,
   TX_TG_ok,      C_o_Grave,     TX_TEXT_FIELD,
   TX_TG_Uk,      C_U_Grave,     TX_TEXT_FIELD,
   TX_TG_uk,      C_u_Grave,     TX_TEXT_FIELD,
   TX_TG_Unk,     C_U_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_unk,     C_u_Ogon_Grave, TX_TEXT_FIELD,
   TX_TG_Ubk,     C_U_Macr_Grave, TX_TEXT_FIELD,
   TX_TG_ubk,     C_u_Macr_Grave, TX_TEXT_FIELD,
   TX_TG_Yk,      C_Y_Grave,     TX_TEXT_FIELD,
   TX_TG_yk,      C_y_Grave,     TX_TEXT_FIELD,
   TX_TG_Ar,      C_A_Tilde,     TX_TEXT_FIELD,
   TX_TG_ar,      C_a_Tilde,     TX_TEXT_FIELD,
   TX_TG_Anr,     C_A_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_anr,     C_a_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_Er,      C_E_Tilde,     TX_TEXT_FIELD,
   TX_TG_er,      C_e_Tilde,     TX_TEXT_FIELD,
   TX_TG_Enr,     C_E_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_enr,     C_e_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_Etr,     C_E_Adot_Tilde, TX_TEXT_FIELD,
   TX_TG_etr,     C_e_Adot_Tilde, TX_TEXT_FIELD,
   TX_TG_Ir,      C_I_Tilde,     TX_TEXT_FIELD,
   TX_TG_ir,      C_i_Tilde,     TX_TEXT_FIELD,
   TX_TG_Inr,     C_I_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_inr,     C_i_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_Or,      C_O_Tilde,     TX_TEXT_FIELD, // !!!
   TX_TG_or,      C_o_Tilde,     TX_TEXT_FIELD,
   TX_TG_Ur,      C_U_Tilde,     TX_TEXT_FIELD,
   TX_TG_ur,      C_u_Tilde,     TX_TEXT_FIELD,
   TX_TG_Unr,     C_U_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_unr,     C_u_Ogon_Tilde, TX_TEXT_FIELD,
   TX_TG_Ubr,     C_U_Macr_Tilde, TX_TEXT_FIELD,
   TX_TG_ubr,     C_u_Macr_Tilde, TX_TEXT_FIELD,
   TX_TG_Yr,      C_Y_Tilde,     TX_TEXT_FIELD,
   TX_TG_yr,      C_y_Tilde,     TX_TEXT_FIELD,
   TX_TG_Lr,      C_L_Tilde,     TX_TEXT_FIELD,
   TX_TG_lr,      C_l_Tilde,     TX_TEXT_FIELD,
   TX_TG_Mr,      C_M_Tilde,     TX_TEXT_FIELD,
   TX_TG_mr,      C_m_Tilde,     TX_TEXT_FIELD,
   TX_TG_Nr,      C_N_Tilde,     TX_TEXT_FIELD,
   TX_TG_nr,      C_n_Tilde,     TX_TEXT_FIELD,
   TX_TG_Rr,      C_R_Tilde,     TX_TEXT_FIELD,
   TX_TG_rr,      C_r_Tilde,     TX_TEXT_FIELD,

   TX_TG_romb,    C_Diamond,     TX_TEXT_FIELD,
   TX_TG_bb,      C_simeq,       TX_TEXT_FIELD,
   TX_TG_kid,     C_Acute,       TX_TEXT_FIELD,
   TX_TG_Ndash,   C_EnDash,      TX_TEXT_FIELD,
   TX_TG_endash,  C_EnDash,      TX_TEXT_FIELD,
   TX_TG_V,       C_paral,       TX_TEXT_FIELD,
   TX_TG_kam,     C_LBquote,     TX_TEXT_FIELD,
   TX_TG_kav,     C_LAquote,     TX_TEXT_FIELD,

   TX_TG_lapos,   C_LAapost,     TX_TEXT_FIELD,
   TX_TG_rapos,   C_Rapost,      TX_TEXT_FIELD,

// #if FALSE // jei reikia, apibrëþti lokaliame iaUserTexTagVariations[]
   TX_TG_An,      C_A_Ogon,      TX_TEXT_FIELD,
   TX_TG_Cv,      C_C_Car,       TX_TEXT_FIELD,
   TX_TG_En,      C_E_Ogon,      TX_TEXT_FIELD,
   TX_TG_Et,      C_E_Adot,      TX_TEXT_FIELD,
   TX_TG_In,      C_I_Ogon,      TX_TEXT_FIELD,
   TX_TG_Sv,      C_S_Car,       TX_TEXT_FIELD,
   TX_TG_Un,      C_U_Ogon,      TX_TEXT_FIELD,
   TX_TG_Ub,      C_U_Macr,      TX_TEXT_FIELD,
   TX_TG_Zv,      C_Z_Car,       TX_TEXT_FIELD,
   TX_TG_an,      C_a_Ogon,      TX_TEXT_FIELD,
   TX_TG_cv,      C_c_Car,       TX_TEXT_FIELD,
   TX_TG_en,      C_e_Ogon,      TX_TEXT_FIELD,
   TX_TG_et,      C_e_Adot,      TX_TEXT_FIELD,
   TX_TG_ino,     C_i_Ogon,      TX_TEXT_FIELD,
   TX_TG_sv,      C_s_Car,       TX_TEXT_FIELD,
   TX_TG_un,      C_u_Ogon,      TX_TEXT_FIELD,
   TX_TG_ub,      C_u_Macr,      TX_TEXT_FIELD,
   TX_TG_zv,      C_z_Car,       TX_TEXT_FIELD,
// #endif

   TX_TG_Antt,    C_A_Ogon,      TX_TEXT_FIELD,
   TX_TG_Cvtt,    C_C_Car,       TX_TEXT_FIELD,
   TX_TG_Entt,    C_E_Ogon,      TX_TEXT_FIELD,
   TX_TG_Ettt,    C_E_Adot,      TX_TEXT_FIELD,
   TX_TG_Intt,    C_I_Ogon,      TX_TEXT_FIELD,
   TX_TG_Svtt,    C_S_Car,       TX_TEXT_FIELD,
   TX_TG_Untt,    C_U_Ogon,      TX_TEXT_FIELD,
   TX_TG_Ubtt,    C_U_Macr,      TX_TEXT_FIELD,
   TX_TG_Zvtt,    C_Z_Car,       TX_TEXT_FIELD,
   TX_TG_antt,    C_a_Ogon,      TX_TEXT_FIELD,
   TX_TG_cvtt,    C_c_Car,       TX_TEXT_FIELD,
   TX_TG_entt,    C_e_Ogon,      TX_TEXT_FIELD,
   TX_TG_ettt,    C_e_Adot,      TX_TEXT_FIELD,
   TX_TG_intt,    C_i_Ogon,      TX_TEXT_FIELD,
   TX_TG_inott,   C_i_Ogon,      TX_TEXT_FIELD,
   TX_TG_svtt,    C_s_Car,       TX_TEXT_FIELD,
   TX_TG_untt,    C_u_Ogon,      TX_TEXT_FIELD,
   TX_TG_ubtt,    C_u_Macr,      TX_TEXT_FIELD,
   TX_TG_zvtt,    C_z_Car,       TX_TEXT_FIELD,

   TX_TG_MT,      C_simeq,       TX_TEXT_FIELD,

   TX_TG_u_Brev,  C_ph_u_Brev /* C_u_Brev */, TX_TEXT_FIELD,
// C_c_Cedil,     C_ph_ch,       TX_TEXT_FIELD,

   TX_TG_ldots,   C_Dots,        TX_FORMULA_FIELD,
   TX_TG_DM,      C_EmDash,      TX_TEXT_FIELD, // !!! gal is lenteliu ??? // AKLZ neveikia ---
   TX_TG_At,      C_At,          TX_TEXT_FIELD,
   TX_TG_sm,      C_smile,       TX_TEXT_FIELD,

   TX_TG_Dal,     TX_TG_divid,   TX_TEXT_FIELD,

   TX_TG_sqrt,    C_sqrt,        TX_FORMULA_FIELD, // !!! why tex tag, why not character in tvtexc.cpp ???

   TX_TG_break,   C_Cr,          TX_BOTH_TYPES,
// TX_TG_par,     C_Lf,          TX_BOTH_TYPES,
// TX_CH_NBSP,    C_NBSP,        TX_BOTH_TYPES,
   TX_TG_romb,    C_Diamond,     TX_BOTH_TYPES,

   TX_TG_lastwordinpar, C_sbreak, TX_BOTH_TYPES,

   TX_TG_Ccedil,  C_C_Cedil,     TX_TEXT_FIELD,
   TX_TG_ccedil,  C_c_Cedil,     TX_TEXT_FIELD,
   TX_TG_Sacute,  C_S_Acute,     TX_TEXT_FIELD,
   TX_TG_sacute,  C_s_Acute,     TX_TEXT_FIELD,

   TX_TG_bullet,  C_Bpoint,      TX_TEXT_FIELD,

   C_i_Acute,     C_i_Acute_Dotless, TX_BOTH_TYPES,
   C_i_Grave,     C_i_Grave_Dotless, TX_BOTH_TYPES,
   C_i_Tilde,     C_i_Tilde_Dotless, TX_BOTH_TYPES,

   TX_TG_ecirc,   C_e_Circ,     TX_TEXT_FIELD,

   C_Nul,         C_Nul,         0

};
