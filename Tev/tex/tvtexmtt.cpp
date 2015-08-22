// ==================================================
// tvtexmtt.cpp
// Make TeX code table conversion tables


// ================================================== definitions
#include "envdef.h"
#include "envir.h"
#include "envsupp.h"

#include <stdio.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kperr.h"
#include "kpstring.h"
#include "tvmain.h"
#include "tvtex.h"
#include "tvxml.h"


// ================================================== objects
KpErrorProc_tag KpErrorProc(TRUE, 71);


//------------------------------------
const int iaTexTagCtbls[TX_TG_NumOfTags92] =
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
   1,       // \rmr
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
// 0, // TX_TG_endlist

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

   0, //   TX_TG_ifnum,
   0, //   TX_TG_ifx,

   0, //   TX_TG_inputlineno,
   0, //   TX_TG_undefined,

   0, //   TX_TG_else,
   0, //   TX_TG_fi,

   0, //   TX_TG_patterns,         // patterns of hyphenation table

   0, //   TX_TG_relax,
   0, //   TX_TG_endinput,
   0, //   TX_TG_message,

   0, //   TX_TG_begingroup,
   0, //   TX_TG_endgroup,

};


// ------------------------------------
int iaUserTexTagVariations[] =
{
   C_Nul,         C_Nul,         0
};


// ------------------------------------
unsigned char *plpszaUserTexTagTable[] =
{
   NULL,
};


// ------------------------------------
int iaUserTexTagArgs[] =
{
   0,
};


//----------------------------------
TexTagTypes iaUserTexTagTypes[] =
{
   TexCtrl,
};


// ------------------------------------
HRESULT MakeMtc(int iCtblFrom, int iCtblTo, const unsigned char *lpszMtcFileName)
{
HRESULT retc=S_OK;
FILE *out_file;
const Chars16 *tab_from;
int ii;
int out_ch;
unsigned char out_ch1;

   printf("Generating file %s\n\n", lpszMtcFileName);

   if((iCtblFrom<0) || (iCtblFrom>=KPT_Ctnum) || (iCtblTo<0) || (iCtblTo>=KPT_Ctnum))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, NULL, TRUE, __FILE__, __LINE__, 0L);

   out_file=fopen((const char *)lpszMtcFileName, "w");
   if(out_file==NULL) 
      retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      fputc(TX_CH_CommentStart, out_file);
      fprintf(out_file, " -------------------------------------------------\n", iaKptCtabExpl[iCtblFrom]);
      fputc(TX_CH_CommentStart, out_file);
      fprintf(out_file, " Decoding table from %s \n", iaKptCtabExpl[iCtblFrom]);
      fputc(TX_CH_CommentStart, out_file);
      fprintf(out_file, "    to %s\n", iaKptCtabExpl[iCtblTo]);
      fputc(TX_CH_CommentStart, out_file);
      fprintf(out_file, " Generated by tvtexmtt.exe\n\n");
      if(ferror(out_file) || feof(out_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      tab_from=Ctptr8[iCtblFrom*2+1];
      if(tab_from==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

   for(ii=0x80; (ii<KPT_Ctbsiz) && SUCCEEDED(retc); ii++)
   {
      out_ch=tab_from[ii-0x80];
      if((out_ch>=0) && (out_ch<=C_CharSize0))
      {
         switch(out_ch)
         {
         case C_O_Tilde:
            
         case C_NBSP:
         case C_hyph:

         case C_box:
                              // DOS frames
         case C_v_b:          // vert; ne DOS-e - C_Vertl
         case C_h_b:       // hor; ne DOS-e - C_Horl
         case C_vh_b:      // vert hor
         case C_vl_b:      // vert left
         case C_vr_b:      // vert right
         case C_hu_b:      // hor up
         case C_hd_b:      // hor down
         case C_ul_b:      // up left
         case C_dl_b:      // down left
         case C_ur_b:      // up right
         case C_dr_b:      // down right

         case C_2v_b:      // double vert; C_paral
         case C_2h_b:      // double hor
         case C_2v2h_b:    // double vert double hor
         case C_2v2l_b:    // double vert double left
         case C_2v2r_b:    // double vert double right
         case C_2h2u_b:    // double hor double up
         case C_2h2d_b:    // double hor double down
         case C_2u2l_b:    // double up double left
         case C_2d2l_b:    // double down double left
         case C_2u2r_b:    // double up double right
         case C_2d2r_b:    // double down double right

         case C_2vh_b:     // double vert hor
         case C_2vl_b:     // double vert left
         case C_2vr_b:     // double vert right
         case C_h2u_b:     // hor double up
         case C_h2d_b:     // hor double down
         case C_2ul_b:     // double up left
         case C_2dl_b:     // double down left
         case C_2ur_b:     // double up right
         case C_2dr_b:     // double down right

         case C_v2h_b:     // vert double hor
         case C_v2l_b:     // vert double left
         case C_v2r_b:     // vert double right
         case C_2hu_b:     // double hor up
         case C_2hd_b:     // double hor down
         case C_u2l_b:     // up double left
         case C_d2l_b:     // down double left
         case C_u2r_b:     // up double right
         case C_d2r_b:     // down double right

         case C_block:     // pilnaviduris kvadratas per visa laukeli
         case C_dgrblk:    // tamsiai pilkas ---//--- (75% shaded)
         case C_grblk:     // pilkas ---//--- (50% shaded)
         case C_lgrblk:    // sviesiai pilkas ---//--- (25% shaded)
         case C_uphblk:    // pilnaviduris staciakampis per puse laukelio virsuje
         case C_dnhblk:    // ---//--- apacioje
         case C_lthblk:    // ---//--- kaireje
         case C_rthblk:    // ---//--- desineje

            break;

         default:
            retc=KptCharDecode(&out_ch1, tab_from[ii-0x80], iCtblTo);
            if(retc==KP_E_UNKN_CHR)
            {
               if(plpszaTexSpecCharTags[out_ch]!=NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, plpszaTexSpecCharTags[out_ch], False, __FILE__, __LINE__, 0L);
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, plpszaXmlSpecCharTags[out_ch], False, __FILE__, __LINE__, 0L);
               retc=S_OK;
            }
            else
            {
//  ^^A1 -> ^^C5
               fputs((const char *)plpszaMainTexTagTable[TX_TG_SP_CHAR-TX_FirstMainTagCode]+1, out_file);
               fprintf(out_file, "%02x -> ", ii);
               fputs((const char *)plpszaMainTexTagTable[TX_TG_SP_CHAR-TX_FirstMainTagCode]+1, out_file);
               fprintf(out_file, "%02x ", out_ch1);
               fputc(TX_CH_CommentStart, out_file);
               if(plpszaTexSpecCharTags[out_ch]!=NULL)
                  fputs((const char *)plpszaTexSpecCharTags[out_ch], out_file);
               fputc(Lf, out_file);

               if(ferror(out_file) || feof(out_file))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
            }

            break;

         } // switch(out_ch)
    
      } // if((out_ch>=0) && (out_ch<=C_CharSize0))

   } // for(ii=0x80; (ii<KPT_Ctbsiz) && SUCCEEDED(retc); ii++)

   if(SUCCEEDED(retc))
   {
      if(fclose(out_file)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, NULL, TRUE, __FILE__, __LINE__, 0L);
   }

return(retc);
}


//---------------------------------------------
HRESULT MakeTex(int iCtblTo, const unsigned char *lpszTexFileName)
{
HRESULT retc=S_OK;
TvTexFile_tag *out_file=NULL;
int ii;
int out_ch;
int lc_ch;
int uc_ch;
unsigned char out_ch1;
unsigned char lc_ch1;
unsigned char uc_ch1;
unsigned char out_buf[10];
unsigned char out_buf1[10];

   printf("Generating file %s\n\n", lpszTexFileName);

   KP_NEW(out_file, TvTexFile_tag(lpszTexFileName, (const unsigned char *)"w", 0));

   if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_CommentStart, TexNoType);
   if(SUCCEEDED(retc)) retc=out_file->PutStr((const unsigned char *)" -------------------------------------------------\n", False);
   if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_CommentStart, TexNoType);
   if(SUCCEEDED(retc)) retc=out_file->PutStr((const unsigned char *)" \\catcode's and definition of accented lithuanian letters\n", False);
   if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_CommentStart, TexNoType);
   if(SUCCEEDED(retc)) retc=out_file->PutStr((const unsigned char *)" for ", False);
   if(SUCCEEDED(retc)) retc=out_file->PutStr(iaKptCtabExpl[iCtblTo], False);
   if(SUCCEEDED(retc)) retc=out_file->PutStr((const unsigned char *)"\n", False);
   if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_CommentStart, TexNoType);
   if(SUCCEEDED(retc)) retc=out_file->PutStr((const unsigned char *)" Generated by tvtexmtt.exe\n\n", False);


//--------------------------------
   for(out_ch=KPT_FirstKptChar; (out_ch<C_CharSize0) && SUCCEEDED(retc); out_ch++)
   {

      if(SUCCEEDED(retc))
         retc=KptCharDecode(&out_ch1, (Chars16)out_ch, iCtblTo);
      if(retc==KP_E_UNKN_CHR) retc=S_OK;
      else if(SUCCEEDED(retc))
      {
         if(
            (plpszaTexSpecCharTags[out_ch]!=NULL) || 

            (out_ch==C_LBquote) ||

            (out_ch==C_A_Ogon) ||
            (out_ch==C_a_Ogon) ||
            (out_ch==C_E_Ogon) ||
            (out_ch==C_e_Ogon) ||
            (out_ch==C_I_Ogon) ||
            (out_ch==C_i_Ogon) ||
            (out_ch==C_U_Ogon) ||
            (out_ch==C_u_Ogon) ||

            (out_ch==C_A_Ogon_Acute) ||
            (out_ch==C_a_Ogon_Acute) ||
            (out_ch==C_E_Ogon_Acute) ||
            (out_ch==C_e_Ogon_Acute) ||
            (out_ch==C_E_Adot_Acute) ||
            (out_ch==C_e_Adot_Acute) ||
            (out_ch==C_I_Ogon_Acute) ||
            (out_ch==C_i_Ogon_Acute) ||
            (out_ch==C_U_Ogon_Acute) ||
            (out_ch==C_u_Ogon_Acute) ||
            (out_ch==C_U_Macr_Acute) ||
            (out_ch==C_u_Macr_Acute) ||
            (out_ch==C_A_Ogon_Grave) ||
            (out_ch==C_a_Ogon_Grave) ||
            (out_ch==C_E_Ogon_Grave) ||
            (out_ch==C_e_Ogon_Grave) ||
            (out_ch==C_E_Adot_Grave) ||
            (out_ch==C_e_Adot_Grave) ||
            (out_ch==C_I_Ogon_Grave) ||
            (out_ch==C_i_Ogon_Grave) ||
            (out_ch==C_U_Ogon_Grave) ||
            (out_ch==C_u_Ogon_Grave) ||
            (out_ch==C_U_Macr_Grave) ||
            (out_ch==C_u_Macr_Grave) ||
            (out_ch==C_A_Ogon_Tilde) ||
            (out_ch==C_a_Ogon_Tilde) ||
            (out_ch==C_E_Ogon_Tilde) ||
            (out_ch==C_e_Ogon_Tilde) ||
            (out_ch==C_E_Adot_Tilde) ||
            (out_ch==C_e_Adot_Tilde) ||
            (out_ch==C_I_Ogon_Tilde) ||
            (out_ch==C_i_Ogon_Tilde) ||
            (out_ch==C_U_Ogon_Tilde) ||
            (out_ch==C_u_Ogon_Tilde) ||
            (out_ch==C_U_Macr_Tilde) ||
            (out_ch==C_u_Macr_Tilde)
           )
         {
            switch(out_ch)
            {
//          case C_A_Diaer:
//          case C_a_Diaer:
//          case C_O_Diaer:
//          case C_o_Diaer:
//          case C_U_Diaer:
//          case C_u_Diaer:
//          case C_ss:

            case C_O_Tilde:
            case C_E_Ogon_Acute:
            
            case C_LAquote:

            case C_NBSP:
            case C_hyph:

            case C_box:
               break;

            default:

// hex view of out_ch
               sprintf((char *)out_buf, "%02x", out_ch1);

// up/low case pairs
               ii=0;
               while((KptUpLowTbl[ii]!=NULL) && (KptUpLowTbl[ii]!=out_ch)) ii++;
               if(KptUpLowTbl[ii]!=NULL)
               {
                  lc_ch=KptUpLowTbl[ii - (ii % 2) + 1];
                  uc_ch=KptUpLowTbl[ii - (ii % 2)];
               }
               else lc_ch=uc_ch=out_ch;

               if(SUCCEEDED(retc))
               {
                  retc=KptCharDecode(&lc_ch1, (Chars16)lc_ch, iCtblTo);
                  if(retc==KP_E_UNKN_CHR)
                  {
                     retc=KpErrorProc.OutputErrorMessage(retc, plpszaTexSpecCharTags[lc_ch], False, __FILE__, __LINE__, 0L);
                     lc_ch1=out_ch1;
                  }
               }

               if(SUCCEEDED(retc))
               {
                  retc=KptCharDecode(&uc_ch1, (Chars16)uc_ch, iCtblTo);
                  if(retc==KP_E_UNKN_CHR)
                  {
                     retc=KpErrorProc.OutputErrorMessage(retc, plpszaTexSpecCharTags[uc_ch], False, __FILE__, __LINE__, 0L);
                     uc_ch1=out_ch1;
                  }
               }

//  \catcode`\^^a1=11\lccode`\^^a1=`\^^a1% a ogonek
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_catcode, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Grave, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_SP_CHAR, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutStr(out_buf, False);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Eq, TexNoType);
               if(SUCCEEDED(retc))
                  retc=out_file->PutStr((const unsigned char *)"11", False);

               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_lccode, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Grave, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_SP_CHAR, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutStr(out_buf, False);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Eq, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Grave, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_SP_CHAR, TexNoType);
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)out_buf1, "%02x", lc_ch1);
                  retc=out_file->PutStr(out_buf1, False);
               }
         
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_uccode, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Grave, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_SP_CHAR, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutStr(out_buf, False);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Eq, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Grave, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_SP_CHAR, TexNoType);
               if(SUCCEEDED(retc))
               {
                  sprintf((char *)out_buf1, "%02x", uc_ch1);
                  retc=out_file->PutStr(out_buf1, False);
               }

               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_CommentStart, TexNoType);
               if(SUCCEEDED(retc))
               {
                  retc=out_file->PutCharProc(out_ch, TexNoType);
                  if(retc==KP_E_UNKN_CHR)
                  {
                     retc=S_OK;
                     retc=out_file->PutStr((const unsigned char *)"???", False);
                  }
               }

               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Lf, TexNoType);

               break;
            
            } // switch(out_ch)
         
         } // if(plpszaTexSpecCharTags[out_ch]!=NULL)

      } // else // if(retc==KP_E_UNKN_CHR) retc=S_OK;

   } // for(out_ch=KPT_FirstKptChar; (out_ch<C_CharSize0) && SUCCEEDED(retc); out_ch++)

   
   if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Lf, TexNoType);


//--------------------------------
   for(out_ch=KPT_FirstKptChar; (out_ch<C_CharSize0) && SUCCEEDED(retc); out_ch++)
   {
      if(SUCCEEDED(retc))
         retc=KptCharDecode(&out_ch1, (Chars16)out_ch, iCtblTo);
      if(retc==KP_E_UNKN_CHR) retc=S_OK;
      else if(SUCCEEDED(retc))
      {
         if(
            (plpszaTexSpecCharTags[out_ch]!=NULL) ||
            
            (out_ch==C_LBquote) ||

            (out_ch==C_A_Ogon) ||
            (out_ch==C_a_Ogon) ||
            (out_ch==C_E_Ogon) ||
            (out_ch==C_e_Ogon) ||
            (out_ch==C_I_Ogon) ||
            (out_ch==C_i_Ogon) ||
            (out_ch==C_U_Ogon) ||
            (out_ch==C_u_Ogon) ||

            (out_ch==C_A_Ogon_Acute) ||
            (out_ch==C_a_Ogon_Acute) ||
            (out_ch==C_E_Ogon_Acute) ||
            (out_ch==C_e_Ogon_Acute) ||
            (out_ch==C_E_Adot_Acute) ||
            (out_ch==C_e_Adot_Acute) ||
            (out_ch==C_I_Ogon_Acute) ||
            (out_ch==C_i_Ogon_Acute) ||
            (out_ch==C_U_Ogon_Acute) ||
            (out_ch==C_u_Ogon_Acute) ||
            (out_ch==C_U_Macr_Acute) ||
            (out_ch==C_u_Macr_Acute) ||
            (out_ch==C_A_Ogon_Grave) ||
            (out_ch==C_a_Ogon_Grave) ||
            (out_ch==C_E_Ogon_Grave) ||
            (out_ch==C_e_Ogon_Grave) ||
            (out_ch==C_E_Adot_Grave) ||
            (out_ch==C_e_Adot_Grave) ||
            (out_ch==C_I_Ogon_Grave) ||
            (out_ch==C_i_Ogon_Grave) ||
            (out_ch==C_U_Ogon_Grave) ||
            (out_ch==C_u_Ogon_Grave) ||
            (out_ch==C_U_Macr_Grave) ||
            (out_ch==C_u_Macr_Grave) ||
            (out_ch==C_A_Ogon_Tilde) ||
            (out_ch==C_a_Ogon_Tilde) ||
            (out_ch==C_E_Ogon_Tilde) ||
            (out_ch==C_e_Ogon_Tilde) ||
            (out_ch==C_E_Adot_Tilde) ||
            (out_ch==C_e_Adot_Tilde) ||
            (out_ch==C_I_Ogon_Tilde) ||
            (out_ch==C_i_Ogon_Tilde) ||
            (out_ch==C_U_Ogon_Tilde) ||
            (out_ch==C_u_Ogon_Tilde) ||
            (out_ch==C_U_Macr_Tilde) ||
            (out_ch==C_u_Macr_Tilde)
           )
         {
            switch(out_ch)
            {
            case C_A_Diaer:
            case C_a_Diaer:
            case C_O_Diaer:
            case C_o_Diaer:
            case C_U_Diaer:
            case C_u_Diaer:
//          case C_ss:

            case C_O_Tilde:
            case C_E_Ogon_Acute:
            
            case C_LAquote:

            case C_NBSP:
            case C_hyph:

            case C_box:
               break;

            default:

// hex view of out_ch
               sprintf((char *)out_buf, "%02X", out_ch1);

// \def\Ant{{\^^A1}}
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_def, TexNoType);
               if(SUCCEEDED(retc))
               {
                  retc=out_file->PutCharProc(out_ch, TexTag);
                  if(retc==KP_E_UNKN_CHR)
                  {
                     retc=S_OK;
                     retc=out_file->PutStr((const unsigned char *)"\\???", False);
                  }
               }
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_FieldStart, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_FieldStart, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_TG_char, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Quot, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutStr(out_buf, False);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_FieldEnd, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_FieldEnd, TexNoType);
               if(SUCCEEDED(retc)) retc=out_file->PutCharProc(TX_SP_Lf, TexNoType);

               break;

            } // switch(out_ch)

         } // if(plpszaTexSpecCharTags[out_ch]!=NULL)

      } // else // if(retc==KP_E_UNKN_CHR) retc=S_OK;

   } // for(out_ch=KPT_FirstKptChar; (out_ch<C_CharSize0) && SUCCEEDED(retc); out_ch++)


//---------------------------
   if(SUCCEEDED(retc)) retc=out_file->CloseFile(True);

   KP_DELETE(out_file);

return(retc);
}

// ================================================== main
//---------------------------------------------
int main(int argc, char **argv)
{
HRESULT retc=S_OK;
int l_argc;
unsigned char *l_argv[3];
unsigned char mtc_f_name[KP_MAX_FNAME_LEN+1];
unsigned char tex_f_name[KP_MAX_FNAME_LEN+1];
int ii;

   printf("\nMake TeX character conversion tables\n\n");

   if(SUCCEEDED(retc)) retc=KpInit();

   l_argc=argc;
   if(argc==3)
   {
      l_argv[0]=(unsigned char *)argv[0];
      l_argv[1]=(unsigned char *)argv[1];
      l_argv[2]=(unsigned char *)argv[2];
   }
// #ifdef Debug
   else if(strstr(strlwr(argv[0]), "debug")>0)
   {
      l_argc=3;
      l_argv[0]=(unsigned char *)"tvtexmtt.exe";
      l_argv[1]=(unsigned char *)"50";
      l_argv[2]=(unsigned char *)"80";
   }
// #endif

   if(l_argc==3)
   {
      strncpy(mtc_f_name, l_argv[1], KP_MAX_FNAME_LEN);
      mtc_f_name[KP_MAX_FNAME_LEN]=Nul;
      ii=strlen(mtc_f_name);
      strncpy(mtc_f_name+ii, "to", KP_MAX_FNAME_LEN-ii);
      mtc_f_name[KP_MAX_FNAME_LEN]=Nul;
      ii=strlen(mtc_f_name);
      strncpy(mtc_f_name+ii, l_argv[2], KP_MAX_FNAME_LEN-ii);
      mtc_f_name[KP_MAX_FNAME_LEN]=Nul;
      ii=strlen(mtc_f_name);
      strncpy(mtc_f_name+ii, ".mtc", KP_MAX_FNAME_LEN-ii);
      mtc_f_name[KP_MAX_FNAME_LEN]=Nul;

      retc=MakeMtc(atoi((const char *)l_argv[1]), atoi((const char *)l_argv[2]), mtc_f_name);

      if(SUCCEEDED(retc))
      {
         strncpy(tex_f_name, "plain", KP_MAX_FNAME_LEN);
         tex_f_name[KP_MAX_FNAME_LEN]=Nul;
         ii=strlen(tex_f_name);
         strncpy(tex_f_name+ii, l_argv[1], KP_MAX_FNAME_LEN-ii);
         tex_f_name[KP_MAX_FNAME_LEN]=Nul;
         ii=strlen(tex_f_name);
         strncpy(tex_f_name+ii, ".tex", KP_MAX_FNAME_LEN-ii);
         tex_f_name[KP_MAX_FNAME_LEN]=Nul;

         retc=MakeTex(atoi((const char *)l_argv[2]), tex_f_name);
      }

   }
   else
   {
      printf("Bad number of parameters:\n");
      printf("                                  c:>tvtexmtt.exe 50 80\n");
      printf("                                                ^  ^\n");
      printf("                                                |  |\n");
      printf("     KPT code table number of source TeX file --'  |\n");
      printf("     KPT code table number of output font ---------'\n\n");
   }

/* if(SUCCEEDED(retc)) retc = */ KpFinit();

return(RET_CODE(retc));
}
