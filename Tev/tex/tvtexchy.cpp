// ==================================================
// tvtexchy.cpp
// Convert TeX hyphenation table adding all accented combinations


// ================================================== definitions
#include "envir.h"

#include <stdio.h>
#include <string>
#include <windows.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpstring.h"
#include "kpctype.h"
#include "tvmain.h"
#include "tvtex.h"
#include "tvtexchy.h"


// ================================================== objects
KpErrorProc_tag KpErrorProc(TRUE, 71);
TvTexChy_tag *TvTexChy=NULL;
int SortMode=KP_LNG_LIT;
int iLastWordLen=0;


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp" 
}
          

//------------------------------------
const int iaTexTagCtbls[TX_TG_NumOfTags129] =
{
   0,       // \input
   0,       // \firstpage=1
   0,       // \lastpage=1
   0,       // \HPROOF
   0,       // \PROOF
   0,       // \CRC
   0,       // \VIEW
   0,       // \setparameters
   0,       // \lang
   0,       // \heada
   0,       // \titletrue

   0,       // TX_TG_ctbl_off,// switch off any code table
   1,       // \rm
   11,      // \rmr
   1,       // \got
   1,       // \cal

   0,       // \bf
   0,       // \it
   0,       // \mit

   0,       // \endpaper
   0,       // \loadgottrue

   0,       // \over
   0,       // \sqrt
   0,       // \root
   0,       // \of

   0,       // \hat
   0,       // \check
   0,       // \tilde
   0,       // \acute
   0,       // \grave
   0,       // \dot
   0,       // \ddot
   0,       // \breve
   0,       // \bar
   0,       // \vec
   0,       // \not

   0,       // TX_TG_big,
   0,       // TX_TG_bigl,
   0,       // TX_TG_bigr,
   0,       // TX_TG_Big,
   0,       // TX_TG_Bigl,
   0,       // TX_TG_Bigr,
   0,       // TX_TG_bigg,
   0,       // TX_TG_biggr,
   0,       // TX_TG_biggl,
   0,       // TX_TG_Bigg,
   0,       // TX_TG_Biggr,
   0,       // TX_TG_Biggl,

//!!! 0,       // TX_TG_leq,   // \leq    <=
   0,       // TX_TG_geq,   // \geq    >=
   0,       // TX_TG_neq,   // \neq    =/

   0,       // TX_TG_lbrace, // \lbrace  {
   0,       // TX_TG_rbrace, // \rbrace  }
   0,       // TX_TG_lbrack, // \lbrack  [
   0,       // TX_TG_rbrack, // \rbrack  ]

   0,       // TX_TG_to,     // \to -->
   0,       // TX_TG_gets,   // \gets <--
   0,       // TX_TG_owns,   // \owns C_epsilon_var apsukta
   0,       // TX_TG_land,   // logical and, \land C_wedge
   0,       // TX_TG_lor,    // logical or, \lor C_vee
   0,       // TX_TG_lnot,   // logical not, \neg C_Rminbr
   0,       // TX_TG_vert,   // \vert C_Vertl
   0,       // TX_TG_Vert,   // \Vert C_paral
   0,       // TX_TG_paral,  // \| C_paral

   0,       // TX_TG_forc_sp, // forced space "\\ ",

   0,       // TX_TG_def,    // \def

   0,       // TX_TG_pageno, // \pageno

   0,       // TX_TG_begindoublecolumns, // \begindoublecolumns

   0, //   TX_TG_Ad,
   0, //   TX_TG_ad,
   0, //   TX_TG_And,
   0, //   TX_TG_and,
   0, //   TX_TG_Ed,
   0, //   TX_TG_ed,
   0, //   TX_TG_End,
   0, //   TX_TG_end,
   0, //   TX_TG_Etd,
   0, //   TX_TG_etd,
   0, //   TX_TG_Id,
   0, //   TX_TG_id,
   0, //   TX_TG_Ind,
   0, //   TX_TG_ind,
   0, //   TX_TG_Od,
   0, //   TX_TG_od,
   0, //   TX_TG_Ud,
   0, //   TX_TG_ud,
   0, //   TX_TG_Und,
   0, //   TX_TG_und,
   0, //   TX_TG_Ubd,
   0, //   TX_TG_ubd,
   0, //   TX_TG_Yd,
   0, //   TX_TG_yd,
   0, //   TX_TG_Ak,
   0, //   TX_TG_ak,
   0, //   TX_TG_Ank,
   0, //   TX_TG_ank,
   0, //   TX_TG_Ek,
   0, //   TX_TG_ek,
   0, //   TX_TG_Enk,
   0, //   TX_TG_enk,
   0, //   TX_TG_Etk,
   0, //   TX_TG_etk,
   0, //   TX_TG_Ik,
   0, //   TX_TG_ik,
   0, //   TX_TG_Ink,
   0, //   TX_TG_ink,
   0, //   TX_TG_Ok,
   0, //   TX_TG_ok,
   0, //   TX_TG_Uk,
   0, //   TX_TG_uk,
   0, //   TX_TG_Unk,
   0, //   TX_TG_unk,
   0, //   TX_TG_Ubk,
   0, //   TX_TG_ubk,
   0, //   TX_TG_Yk,
   0, //   TX_TG_yk,
   0, //   TX_TG_Ar,
   0, //   TX_TG_ar,
   0, //   TX_TG_Anr,
   0, //   TX_TG_anr,
   0, //   TX_TG_Er,
   0, //   TX_TG_er,
   0, //   TX_TG_Enr,
   0, //   TX_TG_enr,
   0, //   TX_TG_Etr,
   0, //   TX_TG_etr,
   0, //   TX_TG_Ir,
   0, //   TX_TG_ir,
   0, //   TX_TG_Inr,
   0, //   TX_TG_inr,
   0, //   TX_TG_Or,
   0, //   TX_TG_or,
   0, //   TX_TG_Ur,
   0, //   TX_TG_ur,
   0, //   TX_TG_Unr,
   0, //   TX_TG_unr,
   0, //   TX_TG_Ubr,
   0, //   TX_TG_ubr,
   0, //   TX_TG_Yr,
   0, //   TX_TG_yr,
   0, //   TX_TG_Lr,
   0, //   TX_TG_lr,
   0, //   TX_TG_Mr,
   0, //   TX_TG_mr,
   0, //   TX_TG_Nr,
   0, //   TX_TG_nr,
   0, //   TX_TG_Rr,
   0, //   TX_TG_rr,

   0, //   TX_TG_romb,

   0, //   TX_TG_bb,

   0, //   TX_TG_kid
   0, //   TX_TG_Ndash
   0, //   TX_TG_V
   0, //   TX_TG_kam
   0, //   TX_TG_kav

   0, //   TX_TG_enddoublecolumns
   0, //   TX_TG_end_

   0, //   TX_TG_et
   0, //   TX_TG_ub
   0, //   TX_TG_an
   0, //   TX_TG_en
   0, //   TX_TG_in
   0, //   TX_TG_ino
   0, //   TX_TG_un

   0, //   TX_TG_eject
   0, //   TX_TG_zmark

   0, //   TX_TG_ls
   0, //   TX_TG_gs

   0, //   TX_TG_looseness
   0, //   TX_TG_hbox
   0, //   TX_TG_em

   0, //   TX_TG_psl

   0, //   TX_TG_MT

   0, //   TX_TG_vadjust

   0, //   TX_TG_NegQemSpc

   0, //   TX_TG_scriptstyle
   0, //   TX_TG_scriptscriptstyle

   0, //   TX_TG_u_Brev

   0, //   TX_TG_loadscrtrue

   0, //   TX_TG_Project
   0, //   TX_TG_Publisher
   0, //   TX_TG_typesetterid
   0, //   TX_TG_paperid
   0, //   TX_TG_statusno
   0, //   TX_TG_switch

   0, //   TX_TG_long
   0, //   TX_TG_noindent

   0, //   TX_TG_insertplot
   0, //   TX_TG_position
   0, //   TX_TG_bottom
   0, //   TX_TG_pheight
   0, //   TX_TG_pwidth
   0, //   TX_TG_pprocent
   0, //   TX_TG_ptype
   0, //   TX_TG_pname
   0, //   TX_TG_ptext
   0, //   TX_TG_pfile
   0, //   TX_TG_pcorrections
   0, //   TX_TG_pvacor
   0, //   TX_TG_endinsertplot
   0, //   TX_TG_UNI

   0, //   TX_TG_bfi

   0, //   TX_TG_leftskip

   0, //   TX_TG_BTH
   0, //   TX_TG_tableno
   0, //   TX_TG_tname
   0, //   TX_TG_tposition
   0, //   TX_TG_tcorrections
   0, //   TX_TG_ETH
   0, //   TX_TG_BTF
   0, //   TX_TG_LC
   0, //   TX_TG_ETF
   0, //   TX_TG_BrightHorLine
   0, //   TX_TG_BR
   0, //   TX_TG_ThinHorLine
   0, //   TX_TG_CVB
   0, //   TX_TG_NextColumn
   0, //   TX_TG_ER
   0, //   TX_TG_NVS
   0, //   TX_TG_EOT

   0, //   TX_TG_after
   0, //   TX_TG_top
   0, //   TX_TG_mid
   0, //   TX_TG_there
// 0, //   TX_TG_bottom
   0, //   TX_TG_full
   0, //   TX_TG_bpage
   0, //   TX_TG_mpage
   0, //   TX_TG_epage
   0, //   TX_TG_tvacor
   0, //   TX_TG_tvbcor
   0, //   TX_TG_tvccor
   0, //   TX_TG_tvdcor

   0, //   TX_TG_vskip
   0, //   TX_TG_hskip

   0, //   TX_TG_captionbottomtrue

   0, //   TX_TG_alistind
   0, //   TX_TG_alist
   0, //   TX_TG_endlist

   0, //   TX_TG_vfill
   0, //   TX_TG_break
   0, //   TX_TG_hfill

// picture formats
   0, //   TX_TG_None
// 0, //   TX_TG_UNI
   0, //   TX_TG_HPX
   0, //   TX_TG_PCZ
   0, //   TX_TG_PS

   0, //   TX_TG_phcor
// 0, //   TX_TG_pvacor
   0, //   TX_TG_pvbcor
   0, //   TX_TG_pvccor

   0, //   TX_TG_newfam
   0, //   TX_TG_cyrfam
   0, //   TX_TG_font
   0, //   TX_TG_tencyr
   0, //   TX_TG_tencyi
   0, //   TX_TG_cyr
   0, //   TX_TG_cyi

   0, //   TX_TG_INSERT

   0, //   TX_TG_poliplottrue
   0, //   TX_TG_setbox
   0, //   TX_TG_figbox
   0, //   TX_TG_vbox
// 0, //   TX_TG_leftskip
   0, //   TX_TG_rightskip
   0, //   TX_TG_hsize
// 0, //   TX_TG_hbox
   0, //   TX_TG_parindent
   0, //   TX_TG_MakeInsert
// 0, //   TX_TG_hskip
// 0, //   TX_TG_captionbottomtrue
   0, //   TX_TG_plotcomment
   0, //   TX_TG_endplotcomment

   0, //   TX_TG_medskip

   0, //   TX_TG_null

   0, //   TX_TG_headb

   0, //   TX_TG_list
// 0, //   TX_TG_endlist

   0, //   TX_TG_proff
   0, //   TX_TG_pron

   0, //   TX_TG_par

   0, //   TX_TG_vfil
   0, //   TX_TG_hfil
// 0, //   TX_TG_vfill
// 0, //   TX_TG_hfill
   0, //   TX_TG_vfilll
   0, //   TX_TG_hfilll

   0, //   TX_TG_phantom

   0, //   TX_TG_hrulefill

   0, //   TX_TG_eightpoint
   0, //   TX_TG_ninepoint
   0, //   TX_TG_tenpoint
   0, //   TX_TG_twelvepoint

   0, //   TX_TG_ldots

   0, //   TX_TG_smallskip

   0, //   TX_TG_Longe
   0, //   TX_TG_Longm

   0, //   TX_TG_vtop

   0, //   TX_TG_wasy

   0, //   TX_TG_newbox
   0, //   TX_TG_let

   0, //   TX_TG_raise

   0, //   TX_TG_eqalign

   0, //   TX_TG_cr

   0, //   TX_TG_CC
   0, //   TX_TG_VR

   0, //   TX_TG_underbrace
   0, //   TX_TG_Ds
   0, //   TX_TG_mathindent
   0, //   TX_TG_divid
   0, //   TX_TG_co

   0, //   TX_TG_hoffset
   0, //   TX_TG_voffset
   0, //   TX_TG_prulesize
   0, //   TX_TG_newdimen
   0, //   TX_TG_Null
   0, //   TX_TG_leftline
   0, //   TX_TG_DM
   0, //   TX_TG_wd
   0, //   TX_TG_box

   0, //   TX_TG_leavevmode
   0, //   TX_TG_zv

   0, //   TX_TG_nul

   0, //   TX_TG_edef

   0, //   TX_TG_At

   0, //   TX_TG_centerline
   0, //   TX_TG_headt
   0, //   TX_TG_headp

   0, //   TX_TG_foot
   0, //   TX_TG_mod
   0, //   TX_TG_mathop

   0, //   TX_TG_loadboldtrue
   0, //   TX_TG_loadbfcaltrue
// 0, //   TX_TG_loadgottrue
   0, //   TX_TG_loadbfgottrue
// 0, //   TX_TG_loadscrtrue
   0, //   TX_TG_loadbfscrtrue
   0, //   TX_TG_loadcurtrue
   0, //   TX_TG_loadbfcurtrue

   0, //   TX_TG_tt
   0, //   TX_TG_undertext

   0, //   TX_TG_sin
   0, //   TX_TG_cos
   0, //   TX_TG_tg
   0, //   TX_TG_ctg
   0, //   TX_TG_arcsin

   0, //   TX_TG_Ettt
   0, //   TX_TG_Svtt
   0, //   TX_TG_Antt
   0, //   TX_TG_sm

   0, //   TX_TG_An
   0, //   TX_TG_Cv
   0, //   TX_TG_En
   0, //   TX_TG_Et
   0, //   TX_TG_In
   0, //   TX_TG_Sv
   0, //   TX_TG_Un
   0, //   TX_TG_Ub
   0, //   TX_TG_Zv
// 0, //   TX_TG_an
   0, //   TX_TG_cv
// 0, //   TX_TG_en
// 0, //   TX_TG_et
// 0, //   TX_TG_in
   0, //   TX_TG_sv
// 0, //   TX_TG_un
// 0, //   TX_TG_ub
// 0, //   TX_TG_zv
// 0, //   TX_TG_Antt
   0, //   TX_TG_Cvtt
   0, //   TX_TG_Entt
// 0, //   TX_TG_Ettt
   0, //   TX_TG_Intt
// 0, //   TX_TG_Svtt
   0, //   TX_TG_Untt
   0, //   TX_TG_Ubtt
   0, //   TX_TG_Zvtt
   0, //   TX_TG_antt
   0, //   TX_TG_cvtt
   0, //   TX_TG_entt
   0, //   TX_TG_ettt
   0, //   TX_TG_intt
   0, //   TX_TG_svtt
   0, //   TX_TG_untt
   0, //   TX_TG_ubtt
   0, //   TX_TG_zvtt

   0, //   TX_TG_halign
   0, //   TX_TG_noalign

   0, //   TX_TG_cases

   0, //   TX_TG_hangindent
   0, //   TX_TG_hangafter

   0, //   TX_TG_max
   0, //   TX_TG_min

   0, //   TX_TG_char

   0, //   TX_TG_Dal

   0, //   TX_TG_RC
   0, //   TX_TG_me
   0, //   TX_TG_multispan

   0, //   TX_TG_TeX

   0, //   TX_TG_boxitc

   0, //   TX_TG_strut
   0, //   TX_TG_ItCor

   0, //   TX_TG_inott

   0, //   TX_TG_helv
   0, //   TX_TG_helvi
   0, //   TX_TG_helvb
   0, //   TX_TG_helvbi
   0, //   TX_TG_helvm
   0, //   TX_TG_helvim
   0, //   TX_TG_helvbm
   0, //   TX_TG_helvbim

   0, //   TX_TG_kern

   0, //   TX_TG_proofplottrue

   0, //   TX_TG_rhr
   0, //   TX_TG_rhl
   0, //   TX_TG_rightrh
   0, //   TX_TG_leftrh

   0, //   TX_TG_topmatter
   0, //   TX_TG_endtopmatter
   0, //   TX_TG_gdef
   0, //   TX_TG_Title

   0, //   TX_TG_baselineskip

   0, //   TX_TG_everypar

   0, //   TX_TG_skipas

   0, //   TX_TG_bye

   0, //   TX_TG_fxr
   0, //   TX_TG_fxx
   0, //   TX_TG_frxx


   0, //   TX_TG_Stage
   0, //   TX_TG_Pages
   0, //   TX_TG_TID

   0, //   TX_TG_FS

   0, //   TX_TG_BD
   0, //   TX_TG_BS

   0, //   TX_TG_SP_CHAR,          // \^^a1 - defines hex character, like "A1 - what the difference?

   0, //   TX_TG_catcode,          // \catcode`\^^a1=11 - defines categories of characters
   0, //   TX_TG_lccode,           // \lccode`\^^a1=`\^^e1 - defines lowercase pair of the character
   0, //   TX_TG_uccode,           // \uccode`\^^a1=`\^^a1 - defines uppercase pair of the character

   0, //   TX_TG_ifnum
   0, //   TX_TG_ifx

   0, //   TX_TG_inputlineno
   0, //   TX_TG_undefined

   0, //   TX_TG_else
   0, //   TX_TG_fi

   0, //   TX_TG_patterns

   0, //   TX_TG_relax
   0, //   TX_TG_endinput
   0, //   TX_TG_message

   0, //   TX_TG_begingroup
   0, //   TX_TG_endgroup

   0, //   TX_TG_dash
   0, //   TX_TG_dtb

   0, //   TX_TG_settabs,
   0, //   TX_TG_columns,
   0, //   TX_TG_plus,

   0, //   TX_TG_fontdimen,
   0, //   TX_TG_timacn,

   0, //   TX_TG_lastwordinpar,

   0, //   TX_TG_LT,   // language specifiers
   0, //   TX_TG_DE,
   0, //   TX_TG_EN,
   0, //   TX_TG_FR,
   0, //   TX_TG_PL,

   0, //   TX_TG_raide,   
   0, //   TX_TG_theraide,
   0, //   TX_TG_nuleisti,
   0, //   TX_TG_hboxup,  

   0, //   TX_TG_global, 
   0, //   TX_TG_LBOX,   
   0, //   TX_TG_orwidth,
   0, //   TX_TG_hwidth, 

// fonts
   1, // 43, //   TX_TG_xiivirm,
   1, // 43, //   TX_TG_xirm,   
   1, // 43, //   TX_TG_xrm,    
   1, // 43, //   TX_TG_xbf,    
   1, // 43, //   TX_TG_xiivibf,
   1, // 43, //   TX_TG_xit,     

   0, //   TX_TG_Ccedil,
   0, //   TX_TG_ccedil,
   0, //   TX_TG_Sacute,
   0, //   TX_TG_sacute,

   0, //   TX_TG_plainparskip,
   0, //   TX_TG_parskip,

   1, // 43, // 50, //   TX_TG_timacnll,

   0, // TX_TG_thistable
   0, // TX_TG_desiredwidth
   0, // TX_TG_begintable
   0, // TX_TG_begintableformat
   0, // TX_TG_endtableformat
   0, // TX_TG_left
   0, // TX_TG_B
   0, // TX_TG_E

   1, // 43, // TX_TG_bfp

   0, // TX_TG_TRTH
   0, // TX_TG_footnote
   0, // TX_TG_VV
   
   0, // TX_TG_endtable
   0, // TX_TG_maketable

   0, //   TX_TG_endash

   1, // 43, // TX_TG_itp

// latex is HOP projekto   
   0, // TX_TG_BeginFileInfo,       
   0, // TX_TG_Manuscript,          
   0, // TX_TG_Company,             
   0, // TX_TG_ProFile,             
   0, // TX_TG_Compiler_cmd_line,   
   0, // TX_TG_Send_to_DB,          
   0, // TX_EndFileInfo,            
   0, // TX_TG_documentclass,       
   0, // TX_TG_usepackage,          
   0, // TX_TG_vrule,               
   0, // TX_TG_underline,           
   0, // TX_TG_ut,                  
   0, // TX_TG_uline,               
   0, // TX_TG_sut,                 
   0, // TX_TG_sout,                
   0, // TX_TG_overfullrule,        
   0, // TX_TG_INDEX,               
   0, // TX_TG_psdraft,             
   0, // TX_TG_vtexed,              
   0, // TX_TG_volume,              
   0, // TX_TG_issue,               
   0, // TX_TG_pubyear,             
   0, // TX_TG_doublehyphendemerits,
   0, // TX_TG_articletype,         
   0, // TX_TG_begin,               
   0, // TX_TG_Project_macro,       
   0, // TX_TG_pagenumbering,       
   0, // TX_TG_printbookmarks,      
   0, // TX_TG_figlink,             
   0, // TX_TG_caption,             
   0, // TX_TG_label,               
   0, // TX_TG_tablewidth,          
   0, // TX_TG_extracolsep,         
   0, // TX_TG_fill,                
   
   0, // TX_TG_Exindent,            
   0, // TX_TG_ExVK,                
   0, // TX_TG_MySize,              
   0, // TX_TG_ex,                  
   0, // TX_TG_tableft,             
   0, // TX_TG_tabcolsep,           

   1, // 43, // TX_TG_ttfamily,            
      
   0, // TX_TG_ParEnd,              
                                    
                                    
                                    
   1, // 43, // TX_TG_textit,              
   1, // 43, // TX_TG_textsc,              
      
   1, // 43, // TX_TG_tsub,                
   1, // 43, // TX_TG_tsup,                
      
   0, // TX_TG_Ex,                  

   0, // TX_TG_notetext,            

   1, // 43, // TX_TG_textbf,              

   1, // TX_TG_longn, // reikia kitos lenteles !!!

   1, // TX_TG_textgr, // reikia kitos lenteles !!!

   0, // TX_TG_item,                

   0, // TX_TG_textul,              

   0, // TX_TG_endfile,

   0, // TX_TG_bullet,
   
};


// ------------------------------------
const unsigned char *plpszaUserTexTagTable[TX_CHY_NumOfTags1+1] =
{
   (unsigned char *)"\\x",
   (unsigned char *)"\\n",
   (unsigned char *)"\\c",    // ignore contents - duplicated pattern for alternative german font
   (unsigned char *)"\\3",
   (unsigned char *)"\\9",

NULL,
};


// ------------------------------------
int iaUserTexTagArgs[TX_CHY_NumOfTags1] =
{
   TX_ARG_TXT_WIDE,     // \x
   1,                   // \n
   1,                   // \c
   0,                   // \3
   0,                   // \9
};


//----------------------------------
TexTagTypes iaUserTexTagTypes[TX_CHY_NumOfTags1] =
{
   TexKey,        // \x
   TexTag,        // \n
   TexTag,        // \c
   TexTag, // TexChar,       // \3
   TexTag, // TexChar,       // \9
};


// ------------------------------------
int iaUserTexTagVariations[] =
{
   C_ss,          TX_CHY_3,  TX_BOTH_TYPES, // \3
   C_ss,          TX_CHY_9,  TX_BOTH_TYPES, // \9
   C_Nul,         C_Nul,     0
};


//---------------------------------------------
TvTexChy_tag::TvTexChy_tag(const unsigned char *lpszInFileName, const unsigned char *lpszOutFileName, bool bLtFlag, int iInTbl, int iOutTbl)
{
   lhOpenResult=S_OK;

   lpInFileObj=NULL;
   lpOutFileObj=NULL;

   iazWordBuf[0]=C_Nul;

   bLtFl=bLtFlag;

   if(
      ((iInTbl<0) || (iInTbl>=KPT_Ctnum)) &&
      SUCCEEDED(lhOpenResult)
     )
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult)) iInKptTbl=iInTbl;

   if(
      ((iOutTbl<0) || (iOutTbl>=KPT_Ctnum)) &&
      SUCCEEDED(lhOpenResult)
     )
      lhOpenResult=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, TRUE, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(lhOpenResult)) iOutKptTbl=iOutTbl;

   strncpy(lpszInFName, lpszInFileName, KP_MAX_FNAME_LEN);
   lpszInFName[KP_MAX_FNAME_LEN]=Nul;

   strncpy(lpszOutFName, lpszOutFileName, KP_MAX_FNAME_LEN);
   lpszOutFName[KP_MAX_FNAME_LEN]=Nul;

   KP_NEW(lpInFileObj, TvTexFile_tag(lpszInFName, (const unsigned char *)"r", sizeof(iaUserTexTagArgs)/sizeof(int)));

   KP_NEW(lpOutFileObj, TvTexFile_tag(lpszOutFName, (const unsigned char *)"w", sizeof(iaUserTexTagArgs)/sizeof(int)));
}


// --------------------------------------------------
HRESULT TvTexChy_tag::GetOpenResult(void)
{
return(lhOpenResult);
}


// --------------------------------------------------
TvTexChy_tag::~TvTexChy_tag(void)
{
   CloseFiles(False);
}


//---------------------------
HRESULT TvTexChy_tag::CloseFiles(bool bCheckFileExist)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;

   if(lpOutFileObj!=NULL)
   {
      retc0=lpOutFileObj->CloseFile(bCheckFileExist);
      if(SUCCEEDED(retc)) retc=retc0;

      KP_DELETE(lpOutFileObj);
   }
   else
   {
      if(!bCheckFileExist) retc=KP_E_NO_FILE;
      else retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

   if(lpInFileObj!=NULL)
   {
      KP_DELETE(lpInFileObj);
   }
   else
   {
      if(SUCCEEDED(retc)) retc=KP_E_NO_FILE;
      if(bCheckFileExist)
         retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}


//---------------------------------------------
HRESULT TvTexChy_tag::GetChar(KpChar *piInCh)
{
HRESULT retc=S_OK;
bool eol_fl;

   if((piInCh==NULL) && SUCCEEDED(retc))
     retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if((lpInFileObj==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) retc=lpInFileObj->GetCharProc(piInCh, False, &eol_fl, NULL);

return(retc);
}


//---------------------------------------------
HRESULT TvTexChy_tag::PutChar(KpChar iOutCh)
{
HRESULT retc=S_OK;

   if((lpOutFileObj==NULL) && SUCCEEDED(retc))
     retc=KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc)) retc=lpOutFileObj->PutCharProc(iOutCh, TexNoType, False, 0);

return(retc);
}


//---------------------------------------------
HRESULT TvTexChy_tag::PutWord(void)
{
HRESULT retc=S_OK;
KpChar *pnts;
unsigned char ch1;
unsigned char out_buf[10];

   if(TvKpStrLen(iazWordBuf)>0)
   {
      pnts=iazWordBuf;
      while(*pnts && SUCCEEDED(retc))
      {
         retc=KptCharDecode(&ch1, *pnts++, iOutKptTbl);
         if(retc==KP_E_UNKN_CHR)
         {
            retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr((const unsigned char *)"!!!", False);
         }
         else
         {
            if(SUCCEEDED(retc))
            {
               if(ch1 < KPT_FirstKptChar) retc=PutChar((KpChar)ch1);
               else
               {
                  sprintf((char *)out_buf, "%02x", ch1);
               
                  retc=PutChar((KpChar)TX_SP_Circ);
                  if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Circ);
                  if(SUCCEEDED(retc)) retc=lpOutFileObj->PutStr(out_buf, False);
               }
            }
         }
      }
      if(SUCCEEDED(retc)) retc=PutChar(C_Spc);
   }

return(retc);
}


//---------------------------------------------
HRESULT TvTexChy_tag::ProcessWord(void)
{
HRESULT retc=S_OK;
KpChar *pnts;
KpChar ch_sav;
int ch_pos;

   if(TvKpStrLen(iazWordBuf)>0)
   {
      if(SUCCEEDED(retc)) retc=PutWord();

      pnts=iazWordBuf;

      while((*pnts) && SUCCEEDED(retc))
      {
         ch_sav=*pnts;

         switch(*pnts)
         {
         case C_A:
            if(SUCCEEDED(retc)){ *pnts=C_A_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_A_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_A_Tilde; retc=PutWord(); }
            }
            break;
         case C_a:
            if(SUCCEEDED(retc)){ *pnts=C_a_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_a_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_a_Tilde; retc=PutWord(); }
            }
            break;
         case C_A_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_A_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_A_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_a_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_a_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_a_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_E:
            if(SUCCEEDED(retc)){ *pnts=C_E_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_E_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_E_Tilde; retc=PutWord(); }
            }
            break;
         case C_e:
            if(SUCCEEDED(retc)){ *pnts=C_e_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_e_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_e_Tilde; retc=PutWord(); }
            }
            break;
         case C_E_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_E_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_E_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_e_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_e_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_e_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_E_Adot:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_E_Adot_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_E_Adot_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_e_Adot:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_e_Adot_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_e_Adot_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_I:
            if(SUCCEEDED(retc)){ *pnts=C_I_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_I_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_I_Tilde; retc=PutWord(); }
            }
            break;
         case C_i:
            if(SUCCEEDED(retc)){ *pnts=C_i_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_i_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_i_Tilde; retc=PutWord(); }
            }
            break;
         case C_I_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_I_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_I_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_i_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_i_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_i_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_O:
            if(SUCCEEDED(retc)){ *pnts=C_O_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_O_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_O_Tilde; retc=PutWord(); }
            }
            break;
         case C_o:
            if(SUCCEEDED(retc)){ *pnts=C_o_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_o_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_o_Tilde; retc=PutWord(); }
            }
            break;
         case C_U:
            if(SUCCEEDED(retc)){ *pnts=C_U_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_U_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_U_Tilde; retc=PutWord(); }
            }
            break;
         case C_u:
            if(SUCCEEDED(retc)){ *pnts=C_u_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_u_Grave; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_u_Tilde; retc=PutWord(); }
            }
            break;
         case C_U_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_U_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_U_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_u_Ogon:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_u_Ogon_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_u_Ogon_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_U_Macr:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_U_Macr_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_U_Macr_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_u_Macr:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_u_Macr_Acute; retc=PutWord(); }
               if(SUCCEEDED(retc)){ *pnts=C_u_Macr_Tilde; retc=PutWord(); }
            }
            else
               retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
            break;
         case C_Y:
            if(SUCCEEDED(retc)){ *pnts=C_Y_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_Y_Tilde; retc=PutWord(); }
            }
            break;
         case C_y:
            if(SUCCEEDED(retc)){ *pnts=C_y_Acute; retc=PutWord(); }
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_y_Tilde; retc=PutWord(); }
            }
            break;
         case C_L:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_L_Tilde; retc=PutWord(); }
            }
            break;
         case C_l:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_l_Tilde; retc=PutWord(); }
            }
            break;
         case C_M:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_M_Tilde; retc=PutWord(); }
            }
            break;
         case C_m:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_m_Tilde; retc=PutWord(); }
            }
            break;
         case C_N:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_N_Tilde; retc=PutWord(); }
            }
            break;
         case C_n:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_n_Tilde; retc=PutWord(); }
            }
            break;
         case C_R:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_R_Tilde; retc=PutWord(); }
            }
            break;
         case C_r:
            if(bLtFl)
            {
               if(SUCCEEDED(retc)){ *pnts=C_r_Tilde; retc=PutWord(); }
            }
            break;
   
         case C_a_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_a_Cyr_Acute; retc=PutWord(); }
            break;
         case C_e_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_e_Cyr_Acute; retc=PutWord(); }
            break;
//       case C_e_Cyr_Diaer:
//          if(SUCCEEDED(retc)){ *pnts=C_e_Cyr_Diaer_Acute; retc=PutWord(); }
//          break;
         case C_i_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_i_Cyr_Acute; retc=PutWord(); }
            break;
         case C_o_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_o_Cyr_Acute; retc=PutWord(); }
            break;
         case C_u_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_u_Cyr_Acute; retc=PutWord(); }
            break;
         case C_y_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_y_Cyr_Acute; retc=PutWord(); }
            break;
         case C_ee_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_ee_Cyr_Acute; retc=PutWord(); }
            break;
         case C_yu_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_yu_Cyr_Acute; retc=PutWord(); }
            break;
         case C_ya_Cyr:
            if(SUCCEEDED(retc)){ *pnts=C_ya_Cyr_Acute; retc=PutWord(); }
            break;
         }

         (*pnts++)=ch_sav;
      }

      if(SUCCEEDED(retc)) retc=lpOutFileObj->GetCharPos(&ch_pos);
      if((ch_pos>0) && SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
   }

return(retc);
}


//---------------------------------------------
HRESULT TvTexChy_tag::PutCharProc(KpChar iOutCh)
{
HRESULT retc=S_OK;
int ii;

   if(TvStrChr(lpszSpcEol, iOutCh)!=NULL)
   {
      retc=ProcessWord();
      iazWordBuf[0]=C_Nul;
   }
   else
   {
      ii=TvKpStrLen(iazWordBuf);
      if(ii>=KP_KWD_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         iazWordBuf[ii]=iOutCh;
         iazWordBuf[ii+1]=C_Nul;
      }
   }

return(retc);
}


//---------------------------------------------
HRESULT TvTexChy_tag::Process(void)
{
HRESULT retc=S_OK;
KpChar in_ch;
int grp_lev;
bool par_end;
int par_num;
int grp_lev1;
bool par_end1;
int par_num1;
unsigned char str_buf[10];
int ii;

   printf("Converting file %s --> %s\n\n", lpszInFName, lpszOutFName);

   while(SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=GetChar(&in_ch);

      if(SUCCEEDED(retc))
      {
         if(in_ch==TX_TG_patterns)
         {
            if(SUCCEEDED(retc)) retc = lpInFileObj->SetCodeTable(iInKptTbl);
            
         
         
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);

            if(SUCCEEDED(retc)) retc=PutChar(in_ch);

// -----------------
            if(SUCCEEDED(retc)) retc=lpInFileObj->GetGrpLev(&grp_lev);
            if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num, &par_end, grp_lev);

//          while((in_ch!=TX_SP_FieldStart) && SUCCEEDED(retc))
            while(
                  (
                     ((par_num!=1) && (par_end)) ||
                     (in_ch==TX_SP_FieldStart)
                  ) && SUCCEEDED(retc)
                 )
            {
               if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
               if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num, &par_end, grp_lev);
               if(
                  (
                     ((par_num!=1) && (par_end)) ||
                     (in_ch==TX_SP_FieldStart)
                  ) && SUCCEEDED(retc)
                 )
                  retc=PutChar(in_ch);
            }

// -----------------
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_CommentStart);
            if(SUCCEEDED(retc))
               retc=lpOutFileObj->PutStr((const unsigned char *)" -------------------------------", False);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);

// -----------------
            while((par_num==1) && (!par_end) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) switch(in_ch)
               {
               case TX_SP_Quot:
                  if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                  if(SUCCEEDED(retc)) switch(in_ch)
                  {
                     case C_A: in_ch=C_A_Diaer; break;
                     case C_a: in_ch=C_a_Diaer; break;
                     case C_O: in_ch=C_O_Diaer; break;
                     case C_o: in_ch=C_o_Diaer; break;
                     case C_U: in_ch=C_U_Diaer; break;
                     case C_u: in_ch=C_u_Diaer; break;
                     default:
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                        break;
                  }
                  break;

               case TX_SP_Circ:
                  if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                  if((in_ch!=TX_SP_Circ) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                  if((!TvIsHexDigit(in_ch)) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  if((in_ch >= KPT_FirstKptChar) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc))
                  {
                     str_buf[0]=(unsigned char)in_ch;
                     retc=GetChar(&in_ch);
                  }
                  if((!TvIsHexDigit(in_ch)) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  if((in_ch >= KPT_FirstKptChar) && SUCCEEDED(retc))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, TRUE, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc))
                  {
                     str_buf[1]=(unsigned char)in_ch;
                     str_buf[2]=Nul;
                     sscanf((const char *)str_buf, "%x", &ii);

                     retc=KptCharEncode(&in_ch, ii, iInKptTbl);
                     if(retc==KP_E_UNKN_CHR)
                        retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, 0L);
                  }
                  break;

               case TX_CHY_c: // skip contents
                  if(SUCCEEDED(retc)) retc=lpInFileObj->GetGrpLev(&grp_lev1);
                  if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num1, &par_end1, grp_lev1);
                  
                  while(
                        (
                           ((par_num1!=1) && (par_end1)) ||
                           (in_ch==TX_SP_FieldStart)
                        ) && SUCCEEDED(retc)
                     )
                  {
                     if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                     if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num1, &par_end1, grp_lev1);
                  }

                  while((par_num1==1) && (!par_end1) && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                     if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num1, &par_end1, grp_lev1);
                  }
                  if((in_ch==TX_SP_FieldEnd) && SUCCEEDED(retc))
                     retc=GetChar(&in_ch);

                  break;

               case TX_CHY_n: // put contents transparently
#if FALSE
                  if(SUCCEEDED(retc)) retc=lpInFileObj->GetGrpLev(&grp_lev1);
                  if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num1, &par_end1, grp_lev1);
                  
                  while(
                        (
                           ((par_num1!=1) && (par_end1)) ||
                           (in_ch==TX_SP_FieldStart)
                        ) && SUCCEEDED(retc)
                     )
                  {
                     if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                     if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num1, &par_end1, grp_lev1);
                  }

                  while((par_num1==1) && (!par_end1) && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc=PutCharProc(in_ch);
                     if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                     if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num1, &par_end1, grp_lev1);
                  }
                  if((in_ch==TX_SP_FieldEnd) && SUCCEEDED(retc))
                     retc=GetChar(&in_ch);
#else
                  if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                  if((in_ch==TX_SP_FieldStart) && SUCCEEDED(retc))
                     retc=GetChar(&in_ch);
#endif
                  break;

               case TX_SP_FieldStart:
               case TX_SP_FieldEnd:
                  if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
                  break;

               case TX_CHY_3:
               case TX_CHY_9:
                  in_ch=C_ss;
                  break;
               
               default:
                  ii = in_ch;
                  retc=KptCharEncode(&in_ch, ii, iInKptTbl);
                  if(retc==KP_E_UNKN_CHR)
                     retc=KpErrorProc.OutputErrorMessage(retc, null, TRUE, __FILE__, __LINE__, 0L);
                  break;
               }

               if(in_ch<C_CharSize0)
               {
                  if(SUCCEEDED(retc)) retc=PutCharProc(in_ch);
                  if(SUCCEEDED(retc)) retc=GetChar(&in_ch);
               }
               if(SUCCEEDED(retc)) retc=lpInFileObj->GetParNum(&par_num, &par_end, grp_lev);
            }

            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_CommentStart);
            if(SUCCEEDED(retc))
               retc=lpOutFileObj->PutStr((const unsigned char *)" -------------------------------", False);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);
            if(SUCCEEDED(retc)) retc=PutChar((KpChar)TX_SP_Lf);

            if(SUCCEEDED(retc)) retc=PutChar(in_ch);
         }
         else // if((in_ch==TX_TG_patterns)
            retc=PutChar(in_ch);
      }

   }
   if(retc==KP_E_EOF) retc=S_OK;

return(retc);
}

// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
int l_argc;
unsigned char *l_argv[6];
unsigned char str_buf[KP_MAX_FILE_LIN_WDT+1];
bool lt_fl;

   printf("\nConvert TeX hyphenation file adding all possible accented combinations\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==6)
   {
      l_argv[0]=(unsigned char *)argv[0];
      l_argv[1]=(unsigned char *)argv[1];
      l_argv[2]=(unsigned char *)argv[2];
      l_argv[3]=(unsigned char *)argv[3];
      l_argv[4]=(unsigned char *)argv[4];
      l_argv[5]=(unsigned char *)argv[5];
   }
#ifdef Debug
   else // if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=6;
      l_argv[0]=(unsigned char *)"tvtexchy.exe";

//    l_argv[1]=(unsigned char *)"dehyph.tex";
//    l_argv[2]=(unsigned char *)"dehypha.tex";
//    l_argv[3]=(unsigned char *)"de";

//    l_argv[1]=(unsigned char *)"lthyphen.tex";
//    l_argv[2]=(unsigned char *)"lthypha.tex";
//    l_argv[3]=(unsigned char *)"lt";

      l_argv[1]=(unsigned char *)"timescya/hyphen/rhyphen.tex";
      l_argv[2]=(unsigned char *)"timescya/hyphen/ruhypha.tex";
      l_argv[3]=(unsigned char *)"ru";

//    l_argv[4]=(unsigned char *)"10";
//    l_argv[5]=(unsigned char *)"80";

      l_argv[4]=(unsigned char *)"11";
      l_argv[5]=(unsigned char *)"11";
   }
#endif

   if(l_argc==6)
   {
      strncpy(str_buf, l_argv[3], KP_MAX_FILE_LIN_WDT);
      str_buf[KP_MAX_FILE_LIN_WDT]=Nul;
      strlwr((char *)str_buf);
      lt_fl=(strcmp(str_buf, "lt")==0);

      KP_NEWO(TvTexChy, TvTexChy_tag(
            (const unsigned char *)l_argv[1], (const unsigned char *)l_argv[2], lt_fl, 
            atoi((const char *)l_argv[4]), atoi((const char *)l_argv[5])));

      if(SUCCEEDED(retc)) retc=TvTexChy->Process();

      if(SUCCEEDED(retc)) retc=TvTexChy->CloseFiles(True);

   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("   c:>tvtexchy.exe infile.tex outfile.tex lt 10 80\n");
      printf("                                          ^  ^  ^\n");
      printf("                                          |  |  |\n");
      printf("                  Language identifier ----'  |  |\n");
      printf("                  Input codetable -----------'  |\n");
      printf("                  Output codetable -------------'\n\n");
   }


   KP_DELETE(TvTexChy);

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

#ifdef Debug
// system("pause");
#endif

return(RET_CODE_MAIN(retc));
}
