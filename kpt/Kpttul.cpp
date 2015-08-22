/*
 * Kpttul.c  upper-/lowercase conversion table
 */


#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kptt.h"


// must be entered all letter characters, independently, have they lower/upper case or not
KpChar KptUpLowTbl[] =
{
   C_A, C_a,      /* A */
   C_B, C_b,      /* B */
   C_C, C_c,      /* C */
   C_D, C_d,      /* D */
   C_E, C_e,      /* E */
   C_F, C_f,      /* F */
   C_G, C_g,      /* G */
   C_H, C_h,      /* H */
   C_I, C_i,      /* I */
   C_J, C_j,      /* J */
   C_K, C_k,      /* K */
   C_L, C_l,      /* L */
   C_M, C_m,      /* M */
   C_N, C_n,      /* N */
   C_O, C_o,      /* O */
   C_P, C_p,      /* P */
   C_Q, C_q,      /* Q */
   C_R, C_r,      /* R */
   C_S, C_s,      /* S */
   C_T, C_t,      /* T */
   C_U, C_u,      /* U */
   C_V, C_v,      /* V */
   C_W, C_w,      /* W */
   C_X, C_x,      /* X */
   C_Y, C_y,      /* Y */
   C_Z, C_z,      /* Z */

   C_AE, C_ae,
   C_OE, C_oe,
   C_IJ, C_ij,
   C_ss, C_ss,

   C_A_Cyr,    C_a_Cyr,
   C_B_Cyr,    C_b_Cyr,
   C_V_Cyr,    C_v_Cyr,
   C_G_Cyr,    C_g_Cyr,
   C_D_Cyr,    C_d_Cyr,
   C_E_Cyr,    C_e_Cyr,
   C_Zh_Cyr,   C_zh_Cyr,
   C_Z_Cyr,    C_z_Cyr,
   C_I_Cyr,    C_i_Cyr,
   C_J_Cyr,    C_j_Cyr,
   C_K_Cyr,    C_k_Cyr,
   C_L_Cyr,    C_l_Cyr,
   C_M_Cyr,    C_m_Cyr,
   C_N_Cyr,    C_n_Cyr,
   C_O_Cyr,    C_o_Cyr,
   C_P_Cyr,    C_p_Cyr,
   C_R_Cyr,    C_r_Cyr,
   C_S_Cyr,    C_s_Cyr,
   C_T_Cyr,    C_t_Cyr,
   C_U_Cyr,    C_u_Cyr,
   C_F_Cyr,    C_f_Cyr,
   C_H_Cyr,    C_h_Cyr,
   C_C_Cyr,    C_c_Cyr,
   C_Ch_Cyr,   C_ch_Cyr,
   C_Sh_Cyr,   C_sh_Cyr,
   C_Shch_Cyr, C_shch_Cyr,
   C_Hard_Cyr, C_hard_Cyr,
   C_Y_Cyr,    C_y_Cyr,
   C_Soft_Cyr, C_soft_Cyr,
   C_Ee_Cyr,   C_ee_Cyr,
   C_Yu_Cyr,   C_yu_Cyr,
   C_Ya_Cyr,   C_ya_Cyr,

   C_Alpha,    C_alpha,
   C_Beta,     C_beta,
   C_Gamma,    C_gamma,
   C_Delta,    C_delta,
   C_Epsilon,  C_epsilon,
   C_Zeta,     C_zeta,
   C_Eta,      C_eta,
   C_Theta,    C_theta,
   C_Jota,     C_jota,
   C_Kappa,    C_kappa,
   C_Lambda,   C_lambda,
   C_My,       C_my,
   C_Ny,       C_ny,
   C_Xi,       C_xi,
   C_Omicron,  C_omicron,
   C_Pi,       C_pi,
   C_Rho,      C_rho,
   C_Sigma,    C_sigma,
   C_Tau,      C_tau,
   C_Ypsilon,  C_ypsilon,
   C_Phi,      C_phi,
   C_Chi,      C_chi,
   C_Psi,      C_psi,
   C_Omega,    C_omega,

   C_Epsilon,  C_epsilon_var,
   C_Theta,    C_theta_var,
   C_DiGamma,  C_digamma,
   C_Kappa,    C_kappa_var,
   C_DiLambda, C_dilambda,
   C_Pi,       C_pi_var,
   C_Rho,      C_rho_var,
   C_Sigma_var,C_sigma_var,
   C_Phi,      C_phi_var,

   C_A_Ogon,   C_a_Ogon,  /* a, */
   C_E_Ogon,   C_e_Ogon,  /* e, */
   C_I_Ogon,   C_i_Ogon,  /* i, */
   C_U_Ogon,   C_u_Ogon,  /* u, */

   C_E_Adot,   C_e_Adot,  /* e. */
   C_Z_Adot,   C_z_Adot,  /* z. */

   C_G_Cyr_Adot, C_g_Cyr_Adot, /* g Cyr . */

   C_C_Car,   C_c_Car,   /* cv */
   C_D_Car,   C_d_Car,   /* dv */
   C_E_Car,   C_e_Car,   /* ev */
   C_L_Car,   C_l_Car,   /* lv */
   C_N_Car,   C_n_Car,   /* nv */
   C_R_Car,   C_r_Car,   /* rv */
   C_S_Car,   C_s_Car,   /* sv */
   C_T_Car,   C_t_Car,   /* tv */
   C_Z_Car,   C_z_Car,   /* zv */

   C_A_Macr,  C_a_Macr,  /* a_ */
   C_E_Macr,  C_e_Macr,  /* e_ */
   C_I_Macr,  C_i_Macr,  /* i_ */
   C_O_Macr,  C_o_Macr,  /* o_ */
   C_U_Macr,  C_u_Macr,  /* u_ */

   C_A_Diaer, C_a_Diaer, /* a.. */
   C_E_Diaer, C_e_Diaer, /* e.. */
   C_I_Diaer, C_i_Diaer, /* i.. */
   C_O_Diaer, C_o_Diaer, /* o.. */
   C_U_Diaer, C_u_Diaer, /* u.. */
   C_Y_Diaer, C_y_Diaer, /* y.. */

   C_E_Cyr_Diaer, C_e_Cyr_Diaer, /* e.. */

   C_A_Ring,  C_a_Ring,  /* ao */
   C_U_Ring,  C_u_Ring,  /* uo */

   C_G_Tacom, C_g_Tacom, /* g' */

   C_G_Bcomma,C_g_Bcomma,/* g, */
   C_K_Bcomma,C_k_Bcomma,/* k, */
   C_L_Bcomma,C_l_Bcomma,/* l, */
   C_N_Bcomma,C_n_Bcomma,/* n, */
   C_R_Bcomma,C_r_Bcomma,/* r, */

   C_C_Cedil, C_c_Cedil, /* c, */
   C_S_Cedil, C_s_Cedil, /* s, */
   C_T_Cedil, C_t_Cedil, /* t, */

   C_A_Grave, C_a_Grave, /* a` */
   C_E_Grave, C_e_Grave, /* e` */
   C_I_Grave, C_i_Grave, /* i` */
   C_O_Grave, C_o_Grave, /* o` */
   C_U_Grave, C_u_Grave, /* u` */

   C_A_Acute, C_a_Acute, /* a' */
   C_C_Acute, C_c_Acute, /* c' */
   C_E_Acute, C_e_Acute, /* e' */
   C_I_Acute, C_i_Acute, /* i' */
   C_L_Acute, C_l_Acute, /* l' */
   C_N_Acute, C_n_Acute, /* n' */
   C_O_Acute, C_o_Acute, /* o' */
   C_R_Acute, C_r_Acute, /* r' */
   C_S_Acute, C_s_Acute, /* s' */
   C_U_Acute, C_u_Acute, /* u' */
   C_Y_Acute, C_y_Acute, /* y' */
   C_Z_Acute, C_z_Acute, /* z' */

   C_K_Cyr_Acute,C_k_Cyr_Acute, /* k Cyr ' */

   C_O_Dacut, C_o_Dacut, /* o'' */
   C_U_Dacut, C_u_Dacut, /* u'' */

   C_A_Tilde, C_a_Tilde, /* a~ */
   C_N_Tilde, C_n_Tilde, /* n~ */
   C_O_Tilde, C_o_Tilde, /* o~ */

   C_L_Slash, C_l_Slash, /* l/ */
   C_O_Slash, C_o_Slash, /* o/ */

   C_A_Circ,  C_a_Circ,  /* a^ */
   C_E_Circ,  C_e_Circ,  /* e^ */
   C_I_Circ,  C_i_Circ,  /* i^ */
   C_O_Circ,  C_o_Circ,  /* o^ */
   C_U_Circ,  C_u_Circ,  /* u^ */

   C_D_Dash,  C_d_Dash,  /* d- */
   C_H_Dash,  C_h_Dash,  /* h- */
   C_P_Dash,  C_p_Dash,  /* p- */

   C_Y_Grave, C_y_Grave,   // y`
   C_E_Tilde, C_e_Tilde,   // e~
   C_I_Tilde, C_i_Tilde,   // i~
   C_U_Tilde, C_u_Tilde,   // u~
   C_Y_Tilde, C_y_Tilde,   // y~
   C_L_Tilde, C_l_Tilde,   // l~
   C_M_Tilde, C_m_Tilde,   // m~
   C_R_Tilde, C_r_Tilde,   // r~
   C_A_Ogon_Acute, C_a_Ogon_Acute,
   C_E_Ogon_Acute, C_e_Ogon_Acute,
   C_E_Adot_Acute, C_e_Adot_Acute,
   C_I_Ogon_Acute, C_i_Ogon_Acute,
   C_U_Ogon_Acute, C_u_Ogon_Acute,
   C_U_Macr_Acute, C_u_Macr_Acute,
   C_A_Ogon_Grave, C_a_Ogon_Grave,
   C_E_Ogon_Grave, C_e_Ogon_Grave,
   C_E_Adot_Grave, C_e_Adot_Grave,
   C_I_Ogon_Grave, C_i_Ogon_Grave,
   C_U_Ogon_Grave, C_u_Ogon_Grave,
   C_U_Macr_Grave, C_u_Macr_Grave,

   C_A_Ogon_Tilde, C_a_Ogon_Tilde,
   C_E_Ogon_Tilde, C_e_Ogon_Tilde,
   C_E_Adot_Tilde, C_e_Adot_Tilde,
   C_I_Ogon_Tilde, C_i_Ogon_Tilde,
   C_U_Ogon_Tilde, C_u_Ogon_Tilde,
   C_U_Macr_Tilde, C_u_Macr_Tilde,

   C_Y_Grave,       C_y_Grave,   // y`
   C_E_Tilde,       C_e_Tilde,   // e~
   C_I_Tilde,       C_i_Tilde,   // i~
   C_U_Tilde,       C_u_Tilde,   // u~
   C_Y_Tilde,       C_y_Tilde,   // y~
   C_L_Tilde,       C_l_Tilde,   // l~
   C_M_Tilde,       C_m_Tilde,   // m~
   C_R_Tilde,       C_r_Tilde,   // r~

   C_A_Ogon_Acute,   C_a_Ogon_Acute,
   C_E_Ogon_Acute,   C_e_Ogon_Acute,
   C_E_Adot_Acute,   C_e_Adot_Acute,
   C_I_Ogon_Acute,   C_i_Ogon_Acute,
   C_U_Ogon_Acute,   C_u_Ogon_Acute,
   C_U_Macr_Acute,   C_u_Macr_Acute,
   C_A_Ogon_Grave,   C_a_Ogon_Grave,
   C_E_Ogon_Grave,   C_e_Ogon_Grave,
   C_E_Adot_Grave,   C_e_Adot_Grave,
   C_I_Ogon_Grave,   C_i_Ogon_Grave,
   C_U_Ogon_Grave,   C_u_Ogon_Grave,
   C_U_Macr_Grave,   C_u_Macr_Grave,
   C_A_Ogon_Tilde,   C_a_Ogon_Tilde,
   C_E_Ogon_Tilde,   C_e_Ogon_Tilde,
   C_E_Adot_Tilde,   C_e_Adot_Tilde,
   C_I_Ogon_Tilde,   C_i_Ogon_Tilde,
   C_U_Ogon_Tilde,   C_u_Ogon_Tilde,
   C_U_Macr_Tilde,   C_u_Macr_Tilde,

// phonetic characters; vowels:
   C_ph_a,        C_ph_a,        // low back unrounded; a, open a; italic C_a
   C_ph_a_inv,    C_ph_a_inv,    // low back rounded; oa; inverted italic C_a

   C_ph_a_sh,     C_ph_a_sh,     // low-mid back unrounded; short a; inverted C_v
   C_ph_o_sh,     C_ph_o_sh,     // low-mid back rounded; short o, open o; inverted C_c
// C_ph_o,        C_ph_o,        // mid back rounded?; o, closed o; C_o
// C_ph_o_soft,   C_ph_o_soft,   // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
// C_ph_o_soft_cl,C_ph_o_soft_cl,// high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   C_ph_u_sh,     C_ph_u_sh,     // semi-high back rounded; short u, short open u; C_ypsilon
   C_ph_w_sh,     C_ph_w_sh,     // semi-high back rounded; short u, short open u, obsolete; C_omega
// C_ph_u,        C_ph_u,        // semi-high central rounded?; u, closed u; C_u
// C_ph_u_soft,   C_ph_u_soft,   // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   C_ph_e_sh,     C_ph_e_sh,     // low-mid front unrounded; short e, open e; C_epsilon
   C_ph_ae,       C_ph_ae,       // low front unrounded?; e, open e; C_ae
// C_ph_e_cl,     C_ph_e_cl,     // high central unrounded?; closed e, german e; C_e
   C_ph_e_sh_inv, C_ph_e_sh_inv, // low-mid central unrounded; hard e; inverted C_epsilon
   C_ph_e_inv,    C_ph_e_inv,    // mid central unrounded; reduced e; inverted C_e

   C_ph_i_sh,     C_ph_i_sh,     // semi-high front unrounded; short i, short open i; C_i without dot
// C_ph_i,        C_ph_i,        // high front unrounded?; i, closed i; C_i
   C_ph_i_Brev,   C_ph_i_Brev,   // ; j; C_i_Brev

// phonetic characters; consonants:
   C_ph_sh,       C_ph_sh,       // sh; C_f, C_int
   C_ph_zh,       C_ph_zh,       // zh; C_3
   C_ph_tsh,      C_ph_tsh,      // tsh; C_t C_f, C_t C_int
   C_ph_dzh,      C_ph_dzh,      // dzh; C_d C_3
   C_ph_th_b,     C_ph_th_b,     // breath th; C_theta
   C_ph_th_v,     C_ph_th_v,     // voiced th; C_delt_Mn, (C_delta_Minus)
   C_ph_ng,       C_ph_ng,       // nasal g; C_eta
   C_ph_g,        C_ph_g,        // g; italic C_g

// additional phonetic characters:
   C_ph_oe,       C_ph_oe,       // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   C_ph_o_slash,  C_ph_o_slash,  // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   C_ph_a_l,      C_ph_a_l,      // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   C_ph_e_inv_l,  C_ph_e_inv_l,  // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   C_ph_i_l,      C_ph_i_l,      // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   C_ph_o_l,      C_ph_o_l,      // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   C_ph_u_l,      C_ph_u_l,      // ; u long; C_u C_Colon

   C_ph_a_n,      C_ph_a_n,      // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   C_ph_a_str_n,  C_ph_a_str_n,  // ; straight a nasal; a~, C_a_Tilde
   C_ph_e_n,      C_ph_e_n,      // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   C_ph_oe_n,     C_ph_oe_n,     // ; oe nasal; oe~, C_oe C_TildeAcc
   C_ph_o_n,      C_ph_o_n,      // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   C_ph_ch,       C_ph_ch,       // german ch; C_c_Cedil

// diphtongs
   C_ph_ai_d,     C_ph_ai_d,     //  C_a C_LigaLow C_i
   C_ph_ae_d,     C_ph_ae_d,     //  C_a C_LigaLow C_e
   C_ph_ao_d,     C_ph_ao_d,     //  C_a C_LigaLow C_o
   C_ph_au_d,     C_ph_au_d,     //  C_a C_LigaLow C_u
   C_ph_ei_d,     C_ph_ei_d,     //  C_e C_LigaLow C_i
   C_ph_eu_d,     C_ph_eu_d,     //  C_e C_LigaLow C_u
   C_ph_ie_d,     C_ph_ie_d,     //  C_i C_LigaLow C_e
   C_ph_oe_d,     C_ph_oe_d,     //  C_ph_o_sh C_LigaLow C_ph_o_slash
   C_ph_oy_d,     C_ph_oy_d,     //  C_ph_o_sh C_LigaLow C_y
   C_ph_uo_d,     C_ph_uo_d,     //  C_u C_LigaLow C_o

// breved phonetics
   C_ph_i_Brev,   C_ph_i_Brev,  // ; j; C_i_Brev
   C_ph_o_Brev,   C_ph_o_Brev,  //  C_o_Brev
   C_ph_u_Brev,   C_ph_u_Brev,  //  C_u_Brev

   C_Nul, C_Nul
};


KpChar KptLatUpLowTbl[] =
{
   C_A, C_a,      /* A */
   C_B, C_b,      /* B */
   C_C, C_c,      /* C */
   C_D, C_d,      /* D */
   C_E, C_e,      /* E */
   C_F, C_f,      /* F */
   C_G, C_g,      /* G */
   C_H, C_h,      /* H */
   C_I, C_i,      /* I */
   C_J, C_j,      /* J */
   C_K, C_k,      /* K */
   C_L, C_l,      /* L */
   C_M, C_m,      /* M */
   C_N, C_n,      /* N */
   C_O, C_o,      /* O */
   C_P, C_p,      /* P */
   C_Q, C_q,      /* Q */
   C_R, C_r,      /* R */
   C_S, C_s,      /* S */
   C_T, C_t,      /* T */
   C_U, C_u,      /* U */
   C_V, C_v,      /* V */
   C_W, C_w,      /* W */
   C_X, C_x,      /* X */
   C_Y, C_y,      /* Y */
   C_Z, C_z,      /* Z */

   C_Nul, C_Nul
};

KpChar KptToLatTbl[C_CharArrSize44] =
{
   C_Nul,     /* 0x00 */
   C_Soh,     /* 0x01 */
   C_Stx,     /* 0x02 */
   C_Etx,     /* 0x03 */
   C_Eot,     /* 0x04 */
   C_Enq,     /* 0x05 */
   C_Ack,     /* 0x06 */
   C_Bel,     /* 0x07 */
   C_Bs,      /* 0x08 */
   C_Ht,      /* 0x09 */
   C_Lf,      /* 0x0a */
   C_Vt,      /* 0x0b */
   C_Ff,      /* 0x0c */
   C_Cr,      /* 0x0d */
   C_So,      /* 0x0e */
   C_Si,      /* 0x0f */
   C_Dle,     /* 0x10 */
   C_Dc1,     /* 0x11 */
   C_Dc2,     /* 0x12 */
   C_Dc3,     /* 0x13 */
   C_Dc4,     /* 0x14 */
   C_Nak,     /* 0x15 */
   C_Syn,     /* 0x16 */
   C_Etb,     /* 0x17 */
   C_Can,     /* 0x18 */
   C_Em,      /* 0x19 */
   C_Sub,     /* 0x1a */
   C_Esc,     /* 0x1b */
   C_Fs,      /* 0x1c */
   C_Gs,      /* 0x1d */
   C_Rs,      /* 0x1e */
   C_Us,      /* 0x1f */

   C_Spc,     /* Space */
   C_Excl,    /* !  Exclamation Mark (s/auktukas) */
   C_Quote,   /* "  Quotation Mark (kabute%s) */
   C_Numb,    /* #  Number Sign (Numerio zenklas) */
   C_Doll,    /* $  Currency Sign (Pinigu zenklas) */
   C_Perc,    /* %  Per Cent Sign (procento z/enklas) */
   C_Amp,     /* &  Ampersand (Ampersandas) */
   C_Apost,   /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   C_Lpar,    /* (  Left Parenthesis (kairysis skliaustas) */
   C_Rpar,    /* )  Right Parenthesis (des/inysis skliaustas) */
   C_Ast,     /* *  Asterisk (Zvaigzdute) */
   C_Plus,    /* +  Plus Sign (pliusas) */
   C_Comma,   /* ,  Comma (kablelis) */
   C_Dash,    /* -  Dash, Hyphen, Minus Sign (minusas) */
   C_Point,   /* .  Full Stop, Period, Point (tas/kas) */
   C_Slash,   /* /  Slash, Solidus (Istrizas bruksnys) */
   C_0,       /* 0 */
   C_1,       /* 1 */
   C_2,       /* 2 */
   C_3,       /* 3 */
   C_4,       /* 4 */
   C_5,       /* 5 */
   C_6,       /* 6 */
   C_7,       /* 7 */
   C_8,       /* 8 */
   C_9,       /* 9 */
   C_Colon,   /* :  Colon (dvitas/kis) */
   C_Semic,   /* ;  Semi-colon (kabliatas/kis) */
   C_Less,    /* <  Less than Sign (maz/iau) */
   C_Eq,      /* =  Equals Sign (lygybe%s z/enklas) */
   C_Great,   /* >  Greater than Sign (daugiau) */
   C_Quest,   /* ?  Question Mark (klaustukas) */

   C_At,      /* @  Commercial At (Prekybinis zenklas "Pas") */
   C_A,       /* A */
   C_B,       /* B */
   C_C,       /* C */
   C_D,       /* D */
   C_E,       /* E */
   C_F,       /* F */
   C_G,       /* G */
   C_H,       /* H */
   C_I,       /* I */
   C_J,       /* J */
   C_K,       /* K */
   C_L,       /* L */
   C_M,       /* M */
   C_N,       /* N */
   C_O,       /* O */
   C_P,       /* P */
   C_Q,       /* Q */
   C_R,       /* R */
   C_S,       /* S */
   C_T,       /* T */
   C_U,       /* U */
   C_V,       /* V */
   C_W,       /* W */
   C_X,       /* X */
   C_Y,       /* Y */
   C_Z,       /* Z */
   C_Lbrack,  /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   C_Lslash,  /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   C_Rbrack,  /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   C_Circ,    /* ^  Circumflex Accent (Cirkumfleksas), standalone */
   C_Underl,  /* _  Underline (Pabraukimas) */

   C_Grave,   /* `  Grave Accent (gravis), standalone */
   C_a,       /* a */
   C_b,       /* b */
   C_c,       /* c */
   C_d,       /* d */
   C_e,       /* e */
   C_f,       /* f */
   C_g,       /* g */
   C_h,       /* h */
   C_i,       /* i */
   C_j,       /* j */
   C_k,       /* k */
   C_l,       /* l */
   C_m,       /* m */
   C_n,       /* n */
   C_o,       /* o */
   C_p,       /* p */
   C_q,       /* q */
   C_r,       /* r */
   C_s,       /* s */
   C_t,       /* t */
   C_u,       /* u */
   C_v,       /* v */
   C_w,       /* w */
   C_x,       /* x */
   C_y,       /* y */
   C_z,       /* z */
   C_Lcurl,   /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   C_Vertl,   /* |  Vertical Line (Vertikali Linija) */
   C_Rcurl,   /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   C_Tilde,   /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje), standalone */

   C_Del,

   C_A, // C_AE,
   C_a, // C_ae,
   C_O, // C_OE,
   C_o, // C_oe,
   C_I, // C_IJ,
   C_i, // C_ij,
   C_s, // C_ss,      /* sharp s (german, C_beta) */

   C_A, // C_A_Cyr,
   C_B, // C_B_Cyr,
   C_V, // C_V_Cyr,
   C_G, // C_G_Cyr,
   C_D, // C_D_Cyr,
   C_E, // C_E_Cyr,
   C_Z, // C_Zh_Cyr,
   C_Z, // C_Z_Cyr,
   C_I, // C_I_Cyr,
   C_J, // C_J_Cyr,
   C_K, // C_K_Cyr,
   C_L, // C_L_Cyr,
   C_M, // C_M_Cyr,
   C_N, // C_N_Cyr,
   C_O, // C_O_Cyr,
   C_P, // C_P_Cyr,
   C_R, // C_R_Cyr,
   C_S, // C_S_Cyr,
   C_T, // C_T_Cyr,
   C_U, // C_U_Cyr,
   C_F, // C_F_Cyr,
   C_H, // C_H_Cyr,
   C_C, // C_C_Cyr,
   C_C, // C_Ch_Cyr,
   C_S, // C_Sh_Cyr,
   C_C, // C_Shch_Cyr,
   C_Apost, // C_Hard_Cyr,
   C_Y, // C_Y_Cyr,
   C_Apost, // C_Soft_Cyr,
   C_E, // C_Ee_Cyr,
   C_U, // C_Yu_Cyr,
   C_A, // C_Ya_Cyr,

   C_a, // C_a_Cyr,
   C_b, // C_b_Cyr,
   C_v, // C_v_Cyr,
   C_g, // C_g_Cyr,
   C_d, // C_d_Cyr,
   C_e, // C_e_Cyr,
   C_z, // C_zh_Cyr,
   C_z, // C_z_Cyr,
   C_i, // C_i_Cyr,
   C_j, // C_j_Cyr,
   C_k, // C_k_Cyr,
   C_l, // C_l_Cyr,
   C_m, // C_m_Cyr,
   C_n, // C_n_Cyr,
   C_o, // C_o_Cyr,
   C_p, // C_p_Cyr,
   C_r, // C_r_Cyr,
   C_s, // C_s_Cyr,
   C_t, // C_t_Cyr,
   C_u, // C_u_Cyr,
   C_f, // C_f_Cyr,
   C_h, // C_h_Cyr,
   C_c, // C_c_Cyr,
   C_c, // C_ch_Cyr,
   C_s, // C_sh_Cyr,
   C_c, // C_shch_Cyr,
   C_Apost, // C_hard_Cyr,
   C_y, // C_y_Cyr,
   C_Apost, // C_soft_Cyr,
   C_e, // C_ee_Cyr,
   C_u, // C_yu_Cyr,
   C_a, // C_ya_Cyr,

/* Additional greek chars variations follow later */

   C_A, // C_Alpha,
   C_B, // C_Beta,
   C_G, // C_Gamma,
   C_D, // C_Delta,
   C_E, // C_Epsilon,
   C_Z, // C_Zeta,
   C_H, // C_Eta,
   C_T, // C_Theta,
   C_I, // C_Jota,
   C_K, // C_Kappa,
   C_L, // C_Lambda,
   C_M, // C_My,
   C_N, // C_Ny,
   C_X, // C_Xi,
   C_O, // C_Omicron,
   C_P, // C_Pi,
   C_R, // C_Rho,
   C_S, // C_Sigma,
   C_T, // C_Tau,
   C_Y, // C_Ypsilon,
   C_F, // C_Phi,
   C_K, // C_Chi,
   C_P, // C_Psi,
   C_O, // C_Omega,

   C_a, // C_alpha,
   C_b, // C_beta,
   C_g, // C_gamma,
   C_d, // C_delta,
   C_e, // C_epsilon,  // curly epsilon
   C_z, // C_zeta,
   C_h, // C_eta,
   C_t, // C_theta,    // straight theta
   C_i, // C_jota,
   C_k, // C_kappa,    // straight kappa
   C_l, // C_lambda,
   C_m, // C_my,
   C_n, // C_ny,
   C_x, // C_xi,
   C_o, // C_omicron,
   C_p, // C_pi,       // straight pi
   C_r, // C_rho,      // straight rho
   C_s, // C_sigma,    // inner sigma
   C_t, // C_tau,
   C_y, // C_ypsilon,
   C_f, // C_phi,      // straight phi
   C_k, // C_chi,
   C_p, // C_psi,
   C_o, // C_omega,

   C_d, // C_delt_Mn, /* delta_Minus (skardi th) */

             /* All accents have no width (over the next letter) */
             /* more accents later - C_...Acc */
   C_Apost, // C_Acute,   /* '  Acute (aku/tas, C_Apost, des/inysis kirtis) */
   C_Quote, // C_Dacut,   /* '' Double Acute */
   C_Comma, // C_Ogon,    /* ,  Ogonek (nosine) */
   C_Point, // C_Adot,    /* .  Dot Above (. virsuje) */
   C_Circ, // C_Car,     /* v  Carron, Caron (Pauksciukas) */
   C_Underl, // C_Macr,    /* _  Macron, Overline (bruksnys virsuje) */
   C_Colon, // C_Diaer,   /* .. Diaeresis (Umlaut) */
   C_Point, // C_Ring,    /* o  Ring (Circle) Above (o virsuje, degree) */
   C_Comma, // C_Tacom,   /* '  Turned Comma Above */
   C_Comma, // C_Bcomma,  /* ,  Comma Bellow */
   C_Comma, // C_Cedil,   /* ,  Cedilla (atbula nosine) */

   C_A, // C_A_Ogon,  /* A, */
   C_a, // C_a_Ogon,  /* a, */
   C_E, // C_E_Ogon,  /* E, */
   C_e, // C_e_Ogon,  /* e, */
   C_I, // C_I_Ogon,  /* I, */
   C_i, // C_i_Ogon,  /* i, */
   C_U, // C_U_Ogon,  /* U, */
   C_u, // C_u_Ogon,  /* u, */

   C_E, // C_E_Adot,  /* E. */
   C_e, // C_e_Adot,  /* e. */
   C_Z, // C_Z_Adot,  /* Z. */
   C_z, // C_z_Adot,  /* z. */

   C_G, // C_G_Cyr_Adot, /* G Cyr . */
   C_g, // C_g_Cyr_Adot, /* g Cyr . */

   C_C, // C_C_Car,   /* Cv */
   C_c, // C_c_Car,   /* cv */
   C_D, // C_D_Car,   /* Dv */
   C_d, // C_d_Car,   /* dv */
   C_E, // C_E_Car,   /* Ev */
   C_e, // C_e_Car,   /* ev */
   C_L, // C_L_Car,   /* Lv */
   C_l, // C_l_Car,   /* lv */
   C_N, // C_N_Car,   /* Nv */
   C_n, // C_n_Car,   /* nv */
   C_R, // C_R_Car,   /* Rv */
   C_r, // C_r_Car,   /* rv */
   C_S, // C_S_Car,   /* Sv */
   C_s, // C_s_Car,   /* sv */
   C_T, // C_T_Car,   /* Tv */
   C_t, // C_t_Car,   /* tv */
   C_Z, // C_Z_Car,   /* Zv */
   C_z, // C_z_Car,   /* zv */


   C_A, // C_A_Macr,  /* A_ */
   C_a, // C_a_Macr,  /* a_ */
   C_E, // C_E_Macr,  /* E_ */
   C_e, // C_e_Macr,  /* e_ */
   C_I, // C_I_Macr,  /* I_ */
   C_i, // C_i_Macr,  /* i_ */
   C_O, // C_O_Macr,  /* O_ */
   C_o, // C_o_Macr,  /* o_ */
   C_U, // C_U_Macr,  /* U_ */
   C_u, // C_u_Macr,  /* u_ */

   C_A, // C_A_Diaer, /* A.. */
   C_a, // C_a_Diaer, /* a.. */
   C_E, // C_E_Diaer, /* E.. */
   C_e, // C_e_Diaer, /* e.. */
   C_I, // C_I_Diaer, /* I.. */
   C_i, // C_i_Diaer, /* i.. */
   C_O, // C_O_Diaer, /* O.. */
   C_o, // C_o_Diaer, /* o.. */
   C_U, // C_U_Diaer, /* U.. */
   C_u, // C_u_Diaer, /* u.. */
   C_Y, // C_Y_Diaer, /* Y.. */
   C_y, // C_y_Diaer, /* y.. */

   C_E, // C_E_Cyr_Diaer, /* E.. */
   C_e, // C_e_Cyr_Diaer, /* e.. */

   C_A, // C_A_Ring,  /* Ao */
   C_a, // C_a_Ring,  /* ao */
   C_U, // C_U_Ring,  /* Uo */
   C_u, // C_u_Ring,  /* uo */

   C_G, // C_G_Tacom, /* G' */
   C_g, // C_g_Tacom, /* g' */

   C_G, // C_G_Bcomma,/* G, */
   C_g, // C_g_Bcomma,/* g, */
   C_K, // C_K_Bcomma,/* K, */
   C_k, // C_k_Bcomma,/* k, */
   C_L, // C_L_Bcomma,/* L, */
   C_l, // C_l_Bcomma,/* l, */
   C_N, // C_N_Bcomma,/* N, */
   C_n, // C_n_Bcomma,/* n, */
   C_R, // C_R_Bcomma,/* R, */
   C_r, // C_r_Bcomma,/* r, */

   C_C, // C_C_Cedil, /* C, */
   C_c, // C_c_Cedil, /* c, */
   C_S, // C_S_Cedil, /* S, */
   C_s, // C_s_Cedil, /* s, */
   C_T, // C_T_Cedil, /* T, */
   C_t, // C_t_Cedil, /* t, */

   C_A, // C_A_Grave, /* A` */
   C_a, // C_a_Grave, /* a` */
   C_E, // C_E_Grave, /* E` */
   C_e, // C_e_Grave, /* e` */
   C_I, // C_I_Grave, /* I` */
   C_i, // C_i_Grave, /* i` */
   C_O, // C_O_Grave, /* O` */
   C_o, // C_o_Grave, /* o` */
   C_U, // C_U_Grave, /* U` */
   C_u, // C_u_Grave, /* u` */

   C_A, // C_A_Acute, /* A' */
   C_a, // C_a_Acute, /* a' */
   C_C, // C_C_Acute, /* C' */
   C_c, // C_c_Acute, /* c' */
   C_E, // C_E_Acute, /* E' */
   C_e, // C_e_Acute, /* e' */
   C_I, // C_I_Acute, /* I' */
   C_i, // C_i_Acute, /* i' */
   C_L, // C_L_Acute, /* L' */
   C_l, // C_l_Acute, /* l' */
   C_N, // C_N_Acute, /* N' */
   C_n, // C_n_Acute, /* n' */
   C_O, // C_O_Acute, /* O' */
   C_o, // C_o_Acute, /* o' */
   C_R, // C_R_Acute, /* R' */
   C_r, // C_r_Acute, /* r' */
   C_S, // C_S_Acute, /* S' */
   C_s, // C_s_Acute, /* s' */
   C_U, // C_U_Acute, /* U' */
   C_u, // C_u_Acute, /* u' */
   C_Y, // C_Y_Acute, /* Y' */
   C_y, // C_y_Acute, /* y' */
   C_Z, // C_Z_Acute, /* Z' */
   C_z, // C_z_Acute, /* z' */

   C_K, // C_K_Cyr_Acute, /* K Cyr ' */
   C_k, // C_k_Cyr_Acute, /* k Cyr ' */

   C_O, // C_O_Dacut, /* O'' */
   C_o, // C_o_Dacut, /* o'' */
   C_U, // C_U_Dacut, /* U'' */
   C_u, // C_u_Dacut, /* u'' */

   C_A, // C_A_Tilde, /* A~ */
   C_a, // C_a_Tilde, /* a~ */
   C_N, // C_N_Tilde, /* N~ */
   C_n, // C_n_Tilde, /* n~ */
   C_O, // C_O_Tilde, /* O~ */
   C_o, // C_o_Tilde, /* o~ */

   C_L, // C_L_Slash, /* L/ */
   C_l, // C_l_Slash, /* l/ */
   C_O, // C_O_Slash, /* O/ */
   C_o, // C_o_Slash, /* o/ */

   C_A, // C_A_Circ,  /* A^ */
   C_a, // C_a_Circ,  /* a^ */
   C_E, // C_E_Circ,  /* E^ */
   C_e, // C_e_Circ,  /* e^ */
   C_I, // C_I_Circ,  /* I^ */
   C_i, // C_i_Circ,  /* i^ */
   C_O, // C_O_Circ,  /* O^ */
   C_o, // C_o_Circ,  /* o^ */
   C_U, // C_U_Circ,  /* U^ */
   C_u, // C_u_Circ,  /* u^ */

   C_D, // C_D_Minus, /* D- Island. */
   C_d, // C_d_Minus, /* d- */
   C_H, // C_H_Minus, /* H- */
   C_h, // C_h_Minus, /* h- */
   C_P, // C_P_Minus, /* P- */
   C_p, // C_p_Minus, /* p- */

   C_Spc, // C_NBSP,   /* No break space */

   C_Doll, // C_Rouble,  /* rublis, $ Cyr */
   C_L, // C_Pound,   /* svaras, L/ */
   C_Y, // C_Yenna,   /* jena, Y- */
   C_c, // C_cent,    /* c/ */

   C_Numb, // C_Para,    /* paragrafas, # engl. */
   C_P, // C_Pren,    /* paragraph end sign (pastraipos pabaiga, C_pi - pi) */
   C_Ast, // C_Multipl, /* x */
   C_Slash, // C_Divide,  /* -:- */
   C_Plus, // C_PlMin,   /* -+- */
   C_1, // C_1up,     /* 1 virsuj */
   C_2, // C_2up,     /* 2 virsuj, kvadratu */
   C_3, // C_3up,     /* 3 virsuj, kubu */
   C_a, // C_a_up,    /* a virsuj */
   C_o, // C_o_up,    /* o virsuj */
   C_2, // C_Half,    /* 1/2 */
   C_4, // C_Quart,   /* 1/4 */
   C_3, // C_34,      /* 3/4 */
   C_Less, // C_Ldopang, /* << - rusiska kabute */
   C_Great, // C_Rdopang, /* >> - rusiska kabute */
   C_Less, // C_Lang,    /* < */
   C_Great, // C_Rang,    /* > */
   C_Vertl, // C_Dvertl,  /* | Koi-7-0 */
   C_Circ, // C_Rminbr,  /* ^ Koi-7-0 ( neiginys, -| ) */
   C_Circ, // C_Lminbr,  /* |- */
   C_Point, // C_Lpoint,  /* mazas taskas vidury */
   C_Ast, // C_Bpoint,  /* bullet, didelis taskas vidury */
   C_Quote, // C_LBquote, /* ,, (" left bellow, double comma, liet. kaire) */
   C_Quote, // C_LAquote, /* '' (" left above, double comma above, angl. desine) */
   C_Quote, // C_Rquote,  /* `` (" right, reversed double comma above, liet. desine, angl. kaire) */
   C_Apost, // C_LBapost, /* , (' left bellow, comma, liet. kaire) */
   C_Apost, // C_LAapost, /* ' (' left above, comma above, angl. desine) */
   C_Apost, // C_Rapost,  /* ` (' right, grave, reversed comma above, liet. desine, angl. kaire) */

   C_Quest, // C_Qst_Ov,  /* apverstas ? */
   C_Excl, // C_Ex_Ov,   /* apverstas ! */
   C_Point, // C_Dots,    /* ... daugtaskis */
   C_Perc, // C_Prom,    /* %o promiles */
   C_T, // C_TM,      /* TM, Trade Mark */
   C_C, // C_CO,      /* (C) Copyright */
   C_R, // C_RO,      /* (R) */

/* Additional greek chars, look SGML DTD */
   C_e, // C_epsilon_var, // straight epsilon
   C_t, // C_theta_var,  // curly theta
   C_G, // C_DiGamma,
   C_g, // C_digamma,
   C_k, // C_kappa_var,  // curly kappa
   C_L, // C_DiLambda,
   C_l, // C_dilambda,
   C_p, // C_pi_var,     // curly pi, like C_omega
   C_r, // C_rho_var,    // curly rho
   C_S, // C_Sigma_var,  // like "S"
   C_s, // C_sigma_var,  // final sigma, like "s"
   C_f, // C_phi_var,    // curly phi

         /* additional accents, all of them have no width (over the next letter) */
   C_Grave, // C_GraveAcc,    /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   C_Circ, // C_CircAcc,     /* ^  Circumflex Accent (C_Circ), over the next letter */
   C_Tilde, // C_TildeAcc,    /* ~  Tilde (C_Tilde), over the next letter */
   C_Circ, // C_BreveAcc,    /* u  (lankelis virsuje) */
   C_Slash, // C_SlashAcc,    /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   C_Point, // C_BdotAcc,     /* .  Dot bellow */
   C_Underl, // C_UnderlAcc,   /* _  Underline (Pabraukimas) */

   C_Apost, // C_prim,    /* strichas prie raides (C_Acute, C_Apost) */
   C_Quote, // C_dprim,   /* du strichai (C_Dacut) */

   C_V, // C_Each,    /* V - "kiekvienam" - apversta A raide */
   C_E, // C_Exists,  /* E - "egzistuoja" - apversta E raide */

   C_A, // C_Aleph,   /* N - alefas */
   C_I, // C_Im,      /* C_I_Got */
   C_R, // C_Re,      /* C_R_Got */
   C_p, // C_wp,      /* C_p_Got */

   C_Less, // C_le,      /* <= - maziau arba lygu */
   C_Great, // C_ge,      /* >= - daugiau arba lygu */
   C_Eq, // C_ne,      /* =/= - nelygu */
   C_Less, // C_ll,      /* << */
   C_Great, // C_gg,      /* >> */
   C_Tilde, // C_sim,     /* ~ - panasu */
   C_Eq, // C_simeq,   /* ~- - panasu arba sutampa */
   C_Tilde, // C_approx,  /* ~~ - apytiksliai lygu */
   C_Eq, // C_cong,    /* ~= - kongruentu */
   C_Tilde, // C_equiv,   /* = - triguba lygybe - ekvivalentu */

   C_V, // C_sqrt,    /* square root */
   C_S, // C_int,     /* integralas */
   C_S, // C_oint,    /* kreivinis integralas */
   C_S, // C_Sum,     /* sum sign (C_Sigma) */
   C_P, // C_Prod,    /* C_Pi */
   C_O, // C_O_times, /* OX - O perbraukta kryzmai */
   C_O, // C_O_plus,  /* O+ - O perbraukta pliusu */

   C_8, // C_infty,   /* infinity - begalybe */
   C_a, // C_propto,  /* (C_alpha) */
   C_d, // C_part,    /* partial (C_delta) */
   C_0, // C_empty,   /* O/ (C_O_Slash) */
   C_D, // C_triangle,/* C_Delta - trikampis */
   C_V, // C_nabla,   /* V - C_Delta apversta */

   C_T, // C_perp,    /* T apversta - statmena */
   C_Less, // C_angle,   /* < - kampas (geom.) */

   C_Less, // C_langle,  /* < - skliaustas !!! keisti i C_Lang */
   C_Great, // C_rangle,  /* > - skliaustas !!! keisti i C_Rang */

   C_P, // C_cap,     /* U apversta - pjuvis */
   C_U, // C_cup,     /* U - junginys */

   C_V, // C_vee,     /* V */
   C_L, // C_wedge,   /* C_Lambda */

   C_D, // C_supset,  /* D - virsaibis */
   C_D, // C_supseteq,/* D= - virsaibis arba sutampa */
   C_C, // C_subset,  /* C - poaibis */
   C_C, // C_subseteq,/* C= - poaibis arba sutampa */
   C_C, // C_nsubset, /* C/ - nepoaibis */

   C_e, // C_in,      /* C_epsilon_var - priklauso */
   C_e, // C_notin,   /* C_epsilon_var_Slash - nepriklauso */
   C_e, // C_ni,      /* C_epsilon_var apsuktas - apima */

   C_Less, // C_leftarr,       /* <-- */
   C_Great, // C_rightarr,      /* --> */
   C_Dash, // C_leftrightarr,  /* <--> */
   C_Circ, // C_uparr,         /* ^| */
   C_v, // C_downarr,       /* |v */
   C_Vertl, // C_updownarr,     /* ^|v */

   C_Less, // C_Leftarr,       /* <== */
   C_Great, // C_Rightarr,      /* ==> */
   C_Eq, // C_Leftrightarr,  /* <==> */
   C_Circ, // C_Uparr,         /* ^|| */
   C_v, // C_Downarr,       /* ||v */
   C_Vertl, // C_Updownarr,     /* ^||v */

   C_Vertl, // C_mid,           /* | */
   C_Vertl, // C_paral,         /* || */

   C_o, // C_diamond,     /* rombas */

   C_t, // C_Club,        /* giles */
   C_o, // C_Diamond,     /* bugnai */
   C_v, // C_Heart,       /* cirvai sirdys */
   C_p, // C_Spade,       /* pikai lapai */

   C_Dash, // C_hyph,    /* hided hyphenation sign ("\-" for TEX) */
   C_Lf, // C_break,   /* line break character */

   C_a, // C_a_Car,   /* av - laikinai, po to ismesti !!! */

   C_E, // C_euro,    /* C= euro piniginis vienetas !!! kelti prie pinigu */

   C_o, // C_deg,     /* degree - panasiai, kaip C_Ring, tik desineje */
   C_m, // C_micro,   /* micro - panasiai, kaip C_my */
   C_O, // C_Ohm,     /* Ohm sign - panasiai, kaip C_Omega */
   C_A, // C_Angst,   /* Angstroem - C_A_Ring */

   C_Dash, // C_Horl,    /* horizontal line --- */

   C_T, // C_Dag,    /* Dagger +| (kryzius) */
   C_T, // C_Ddag,   /* Double dagger +|+ (Kestucio kryzius) */

   C_f, // C_ff,     /* ff ligature */
   C_f, // C_fi,     /* fi ligature */
   C_f, // C_fj,     /* fj ligature */
   C_f, // C_ffi,    /* ff ligature */
   C_f, // C_ffl,    /* ff ligature */
   C_f, // C_fl,     /* ff ligature */

   C_Circ, // C_and,    /* ^ logical and */
   C_V, // C_or,     /* V logical or */

   C_f, // C_fun,    /* f function of */

   C_Dash, // C_MinPl,  /* -+ minus plus */

   C_Dash, // C_EnDash, /* -- - vidutinio ilgio bruksnys */
   C_Dash, // C_EmDash, /* --- - ilgas bruksnys */

   C_Point, // C_Cdots,  /* ... - daugtaskis per viduri */
   C_Tilde, // C_WideTilde, /* ~ didele tilde */

   C_Spc, // C_QemSpc, /* 1/4 m space */
   C_Spc, // C_EnSpc,  /* n space */
   C_Spc, // C_EmSpc,  /* m space */
   C_Spc, // C_2emSpc, /* 2 m space */

   C_Lf, // C_NewPar, /* paragraph end control character */

// lithuanian accented letters
   C_Y, // C_Y_Grave,   // Y`
   C_y, // C_y_Grave,   // y`
   C_E, // C_E_Tilde,   // E~
   C_e, // C_e_Tilde,   // e~
   C_I, // C_I_Tilde,   // I~
   C_i, // C_i_Tilde,   // i~
   C_U, // C_U_Tilde,   // U~
   C_u, // C_u_Tilde,   // u~
   C_Y, // C_Y_Tilde,   // Y~
   C_y, // C_y_Tilde,   // y~
   C_L, // C_L_Tilde,   // L~
   C_l, // C_l_Tilde,   // l~
   C_M, // C_M_Tilde,   // M~
   C_m, // C_m_Tilde,   // m~
   C_R, // C_R_Tilde,   // R~
   C_r, // C_r_Tilde,   // r~
   C_A, // C_A_Ogon_Acute,
   C_a, // C_a_Ogon_Acute,
   C_E, // C_E_Ogon_Acute,
   C_e, // C_e_Ogon_Acute,
   C_E, // C_E_Adot_Acute,
   C_e, // C_e_Adot_Acute,
   C_I, // C_I_Ogon_Acute,
   C_i, // C_i_Ogon_Acute,
   C_U, // C_U_Ogon_Acute,
   C_u, // C_u_Ogon_Acute,
   C_U, // C_U_Macr_Acute,
   C_u, // C_u_Macr_Acute,
   C_A, // C_A_Ogon_Grave,
   C_a, // C_a_Ogon_Grave,
   C_E, // C_E_Ogon_Grave,
   C_e, // C_e_Ogon_Grave,
   C_E, // C_E_Adot_Grave,
   C_e, // C_e_Adot_Grave,
   C_I, // C_I_Ogon_Grave,
   C_i, // C_i_Ogon_Grave,
   C_U, // C_U_Ogon_Grave,
   C_u, // C_u_Ogon_Grave,
   C_U, // C_U_Macr_Grave,
   C_u, // C_u_Macr_Grave,
   C_A, // C_A_Ogon_Tilde,
   C_a, // C_a_Ogon_Tilde,
   C_E, // C_E_Ogon_Tilde,
   C_e, // C_e_Ogon_Tilde,
   C_E, // C_E_Adot_Tilde,
   C_e, // C_e_Adot_Tilde,
   C_I, // C_I_Ogon_Tilde,
   C_i, // C_i_Ogon_Tilde,
   C_U, // C_U_Ogon_Tilde,
   C_u, // C_u_Ogon_Tilde,
   C_U, // C_U_Macr_Tilde,
   C_u, // C_u_Macr_Tilde,

// phonetic characters; vowels:
   C_a, // C_ph_a,        // low back unrounded; a, open a; italic C_a
   C_a, // C_ph_a_inv,    // low back rounded; oa; inverted italic C_a

   C_a, // C_ph_a_sh,     // low-mid back unrounded; short a; inverted C_v
   C_o, // C_ph_o_sh,     // low-mid back rounded; short o, open o; inverted C_c
// C_ph_o,        // mid back rounded?; o, closed o; C_o

   C_u, // C_ph_u_sh,     // semi-high back rounded; short u, short open u; C_ypsilon
   C_u, // C_ph_w_sh,     // semi-high back rounded; short u, short open u, obsolete; C_omega
// C_ph_u,        // semi-high central rounded?; u, closed u; C_u
// C_ph_u_soft,   // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   C_e, // C_ph_e_sh,     // low-mid front unrounded; short e, open e; C_epsilon
   C_a, // C_ph_ae,       // low front unrounded?; e, open e; C_ae
// C_ph_e_cl,     // high central unrounded?; closed e, german e; C_e
   C_e, // C_ph_e_sh_inv, // low-mid central unrounded; hard e; inverted C_epsilon
   C_e, // C_ph_e_inv,    // mid central unrounded; reduced e; inverted C_e

   C_i, // C_ph_i_sh,     // semi-high front unrounded; short i, short open i; C_i without dot
// C_ph_i,        // high front unrounded?; i, closed i; C_i

// phonetic characters; consonants:
   C_s, // C_ph_sh,       // sh; C_f, C_int
   C_z, // C_ph_zh,       // zh; C_3
   C_c, // C_ph_tsh,      // tsh; C_t C_f, C_t C_int
   C_d, // C_ph_dzh,      // dzh; C_d C_3
   C_t, // C_ph_th_b,     // breath th; C_theta
   C_d, // C_ph_th_v,     // voiced th; C_delt_Mn, (C_delta_Minus)
   C_n, // C_ph_ng,       // nasal g; C_eta
   C_g, // C_ph_g,        // g; italic C_g

// additional phonetic characters:
   C_o,  // C_ph_oe,       // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   C_o,  // C_ph_o_slash,  // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   C_a,  // C_ph_a_l,      // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   C_e,  // C_ph_e_inv_l,  // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   C_i,  // C_ph_i_l,      // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   C_o,  // C_ph_o_l,      // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   C_u,  // C_ph_u_l,      // ; u long; C_u C_Colon

   C_a,  // C_ph_a_n,      // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   C_a,  // C_ph_a_str_n,  // ; straight a nasal; a~, C_a_Tilde
   C_e,  // C_ph_e_n,      // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   C_o,  // C_ph_oe_n,     // ; oe nasal; oe~, C_oe C_TildeAcc
   C_o,  // C_ph_o_n,      // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   C_c,  // C_ph_ch,       // german ch; C_c_Cedil

// diphtongs
   C_a,  // C_ph_ai_d,     //  C_a C_LigaLow C_i
   C_a,  // C_ph_ae_d,     //  C_a C_LigaLow C_e
   C_a,  // C_ph_ao_d,     //  C_a C_LigaLow C_o
   C_a,  // C_ph_au_d,     //  C_a C_LigaLow C_u
   C_e,  // C_ph_ei_d,     //  C_e C_LigaLow C_i
   C_e,  // C_ph_eu_d,     //  C_e C_LigaLow C_u
   C_i,  // C_ph_ie_d,     //  C_i C_LigaLow C_e
   C_o,  // C_ph_oe_d,     //  C_ph_o_sh C_LigaLow C_ph_o_slash
   C_o,  // C_ph_oy_d,     //  C_ph_o_sh C_LigaLow C_y
   C_u,  // C_ph_uo_d,     //  C_u C_LigaLow C_o

// breved phonetics
   C_i,     // C_ph_i_Brev,  // ; j; C_i_Brev
   C_o,     // C_ph_o_Brev,  //  C_o_Brev
   C_u,     // C_ph_u_Brev,  //  C_u_Brev

// liga accents (for diphtongs)
   C_Tilde, // C_LigaUp,      // lankelis virs dvieju raidziu
   C_Tilde, // C_LigaLow,     // lankelis po dviem raidem

   C_o,     // C_MidRing,     // mazas apskritimas viduryje (tusciaviduris bulletas - kaip C_Bpoint)

// phonetic accents
   C_Apost, // C_ph_acc,       // C_Apost
   C_Comma, // C_ph_acc_low,   // C_Comma

   C_o,     // C_square

   C_o,     // C_male
   C_o,     // C_female

   C_O,     // C_O_ring
   C_O,     // C_O_dot

   C_O,     // C_BigRing

   C_Less,  // C_longleftarr,       /* <---- */
   C_Great, // C_longrightarr,      /* ----> */

   C_Tilde, // C_smile

   C_Point, // C_box,         // pilnaviduris kvadratas viduryje

// DOS frames
   C_Vertl,     //  C_v_b,       // vert; ne DOS-e - C_Vertl
   C_Dash,      //  C_h_b,       // hor; ne DOS-e - C_Horl
   C_Plus,      //  C_vh_b,      // vert hor
   C_Plus,      //  C_vl_b,      // vert left
   C_Plus,      //  C_vr_b,      // vert right
   C_Plus,      //  C_hu_b,      // hor up
   C_Plus,      //  C_hd_b,      // hor down
   C_Plus,      //  C_ul_b,      // up left
   C_Plus,      //  C_dl_b,      // down left
   C_Plus,      //  C_ur_b,      // up right
   C_Plus,      //  C_dr_b,      // down right

   C_Vertl,     //  C_2v_b,      // double vert; C_paral
   C_Dash,      //  C_2h_b,      // double hor
   C_Plus,      //  C_2v2h_b,    // double vert double hor
   C_Plus,      //  C_2v2l_b,    // double vert double left
   C_Plus,      //  C_2v2r_b,    // double vert double right
   C_Plus,      //  C_2h2u_b,    // double hor double up
   C_Plus,      //  C_2h2d_b,    // double hor double down
   C_Plus,      //  C_2u2l_b,    // double up double left
   C_Plus,      //  C_2d2l_b,    // double down double left
   C_Plus,      //  C_2u2r_b,    // double up double right
   C_Plus,      //  C_2d2r_b,    // double down double right

   C_Plus,      //  C_2vh_b,     // double vert hor
   C_Plus,      //  C_2vl_b,     // double vert left
   C_Plus,      //  C_2vr_b,     // double vert right
   C_Plus,      //  C_h2u_b,     // hor double up
   C_Plus,      //  C_h2d_b,     // hor double down
   C_Plus,      //  C_2ul_b,     // double up left
   C_Plus,      //  C_2dl_b,     // double down left
   C_Plus,      //  C_2ur_b,     // double up right
   C_Plus,      //  C_2dr_b,     // double down right

   C_Plus,      //  C_v2h_b,     // vert double hor
   C_Plus,      //  C_v2l_b,     // vert double left
   C_Plus,      //  C_v2r_b,     // vert double right
   C_Plus,      //  C_2hu_b,     // double hor up
   C_Plus,      //  C_2hd_b,     // double hor down
   C_Plus,      //  C_u2l_b,     // up double left
   C_Plus,      //  C_d2l_b,     // down double left
   C_Plus,      //  C_u2r_b,     // up double right
   C_Plus,      //  C_d2r_b,     // down double right

   C_Point, // C_block,     // pilnaviduris kvadratas per visa laukeli
   C_Point, // C_dgrblk,    // tamsiai pilkas ---//--- (75% shaded)
   C_Point, // C_grblk,     // pilkas ---//--- (50% shaded)
   C_Point, // C_lgrblk,    // sviesiai pilkas ---//--- (25% shaded)
   C_Point, // C_uphblk,    // pilnaviduris staciakampis per puse laukelio virsuje
   C_Point, // C_dnhblk,    // ---//--- apacioje
   C_Point, // C_lthblk,    // ---//--- kaireje
   C_Point, // C_rthblk,    // ---//--- desineje

   C_Point, // C_utrif,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   C_Point, // C_dtrif,     // pilnaviduris trikampis zemyn
   C_Point, // C_ltrif,     // pilnaviduris trikampis i kaire
   C_Point, // C_rtrif,     // pilnaviduris trikampis i desine

   C_u,     // C_ph_uu_sh

   C_Dash,  // C_hhyph,          // hard hyphen - zodzio kelimas per prievarta -\break
   C_Lf,    // C_sbreak,         // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   C_Spc,   // C_hSpc,           // hard space - technical space after TEX commands - do not process
   C_Lf,    // C_hbreak,         // break su \hfill, xmlsty keiciamas is C_Cr ("\r")
   C_Spc,   // C_lSpc,           // last space - space, to be changed to C_NBSP after LAST_WORD_LEN
   C_Spc,   // C_hlSpc,          // hard last space - C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   C_Point, // C_utrif_rtf,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   C_Point, // C_dtrif_rtf,     // pilnaviduris trikampis zemyn
   C_Point, // C_ltrif_rtf,     // pilnaviduris trikampis i kaire
   C_Point, // C_rtrif_rtf,     // pilnaviduris trikampis i desine

// erdvines rodykles
   C_Less,  // '<' // C_3DTopLightLeftArrowHead,
   C_Less,  // '<' // C_3DBotLightLeftArrowHead,
   C_Great, // '>' // C_3DTopLightRightArrowHead,
   C_Great, // '>' // C_3DBotLightRightArrowHead,
   C_Circ,  // '^' // C_3DLeftLightUpArrowHead,
   C_Circ,  // '^' // C_3DRightLightUpArrowHead,
   C_v,     // 'v' // C_3DLeftLightDownArrowHead,
   C_v,     // 'v' // C_3DRightLightDownArrowHead,

   C_Dash,  // '-' // C_MinusMath

   C_Spc,   // ' ' // C_ZeroWidthSpace

   C_Quest, // '?' // C_ph_glot_stop

   C_Apost,    // '\'' //  C_AcuteNcomb
   C_Comma,    // ','  //  C_CedilNcomb
   C_Underl,   // '_' //  C_MacrNcomb

   C_Doll,     // C_DollNctrl

   C_Comma,    // C_OgonNcomb

   C_N,        // C_No

   C_Circ,     // C_CarNcomb
   C_Colon,    // C_DiaerNcomb
   C_Tilde,    // C_TildeNcomb

   C_Point, // C_utri
   C_Point, // C_dtri
   C_Point, // C_ltri
   C_Point, // C_rtri

   C_Underl,// C_Oline

   C_R,     // C_R_Oline
   C_X,     // C_X_Oline

   C_Less,  // C_leqslant
   C_Great, // C_geqslant

   C_i,     // C_i_Grave_Dotless
   C_i,     // C_i_Acute_Dotless
   C_i,     // C_i_Tilde_Dotless

   C_A, // C_A_Cyr_Acute,
   C_E, // C_E_Cyr_Acute,
   C_I, // C_I_Cyr_Acute,
   C_O, // C_O_Cyr_Acute,
   C_U, // C_U_Cyr_Acute,
   C_Y, // C_Y_Cyr_Acute,
   C_E, // C_Ee_Cyr_Acute,
   C_U, // C_Ju_Cyr_Acute,
   C_A, // C_Ja_Cyr_Acute,

   C_a, // C_a_Cyr_Acute,
   C_e, // C_e_Cyr_Acute,
   C_i, // C_i_Cyr_Acute,
   C_o, // C_o_Cyr_Acute,
   C_u, // C_u_Cyr_Acute,
   C_y, // C_y_Cyr_Acute,
   C_e, // C_ee_Cyr_Acute,
   C_u, // C_ju_Cyr_Acute,
   C_a, // C_ja_Cyr_Acute,

   C_Spc, // C_NullSpc

   C_Dash, // C_Dash_Diaer

   C_o, // C_bdiamond

   C_C, // C_DegCels

   C_Ast, // C_hBpoint,  /* bullet, didelis taskas vidury */

// ----------------------- old style cyrillic
   C_F,  // C_Fita_Cyr
   C_f,  // C_fita_Cyr
   C_E,  // C_Yat_Cyr
   C_e,  // C_yat_Cyr

   C_v,  // C_checkmark

   C_Apost, // C_prim_Ncomb
   C_Quote, // C_dprim_Ncomb
};


// ---------------------------------------
KpChar KptNoAccTbl[C_CharArrSize44] =
{
   C_Nul,     /* 0x00 */
   C_Soh,     /* 0x01 */
   C_Stx,     /* 0x02 */
   C_Etx,     /* 0x03 */
   C_Eot,     /* 0x04 */
   C_Enq,     /* 0x05 */
   C_Ack,     /* 0x06 */
   C_Bel,     /* 0x07 */
   C_Bs,      /* 0x08 */
   C_Ht,      /* 0x09 */
   C_Lf,      /* 0x0a */
   C_Vt,      /* 0x0b */
   C_Ff,      /* 0x0c */
   C_Cr,      /* 0x0d */
   C_So,      /* 0x0e */
   C_Si,      /* 0x0f */
   C_Dle,     /* 0x10 */
   C_Dc1,     /* 0x11 */
   C_Dc2,     /* 0x12 */
   C_Dc3,     /* 0x13 */
   C_Dc4,     /* 0x14 */
   C_Nak,     /* 0x15 */
   C_Syn,     /* 0x16 */
   C_Etb,     /* 0x17 */
   C_Can,     /* 0x18 */
   C_Em,      /* 0x19 */
   C_Sub,     /* 0x1a */
   C_Esc,     /* 0x1b */
   C_Fs,      /* 0x1c */
   C_Gs,      /* 0x1d */
   C_Rs,      /* 0x1e */
   C_Us,      /* 0x1f */

   C_Spc,     /* Space */
   C_Excl,    /* !  Exclamation Mark (s/auktukas) */
   C_Quote,   /* "  Quotation Mark (kabute%s) */
   C_Numb,    /* #  Number Sign (Numerio zenklas) */
   C_Doll,    /* $  Currency Sign (Pinigu zenklas) */
   C_Perc,    /* %  Per Cent Sign (procento z/enklas) */
   C_Amp,     /* &  Ampersand (Ampersandas) */
   C_Apost,   /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   C_Lpar,    /* (  Left Parenthesis (kairysis skliaustas) */
   C_Rpar,    /* )  Right Parenthesis (des/inysis skliaustas) */
   C_Ast,     /* *  Asterisk (Zvaigzdute) */
   C_Plus,    /* +  Plus Sign (pliusas) */
   C_Comma,   /* ,  Comma (kablelis) */
   C_Dash,    /* -  Hyphen, Minus Sign (minusas) */
   C_Point,   /* .  Full Stop, Period, Point (tas/kas) */
   C_Slash,   /* /  Slash, Solidus (Istrizas bruksnys) */
   C_0,       /* 0 */
   C_1,       /* 1 */
   C_2,       /* 2 */
   C_3,       /* 3 */
   C_4,       /* 4 */
   C_5,       /* 5 */
   C_6,       /* 6 */
   C_7,       /* 7 */
   C_8,       /* 8 */
   C_9,       /* 9 */
   C_Colon,   /* :  Colon (dvitas/kis) */
   C_Semic,   /* ;  Semi-colon (kabliatas/kis) */
   C_Less,    /* <  Less than Sign (maz/iau) */
   C_Eq,      /* =  Equals Sign (lygybe%s z/enklas) */
   C_Great,   /* >  Greater than Sign (daugiau) */
   C_Quest,   /* ?  Question Mark (klaustukas) */

   C_At,      /* @  Commercial At (Prekybinis zenklas "Pas") */
   C_A,       /* A */
   C_B,       /* B */
   C_C,       /* C */
   C_D,       /* D */
   C_E,       /* E */
   C_F,       /* F */
   C_G,       /* G */
   C_H,       /* H */
   C_I,       /* I */
   C_J,       /* J */
   C_K,       /* K */
   C_L,       /* L */
   C_M,       /* M */
   C_N,       /* N */
   C_O,       /* O */
   C_P,       /* P */
   C_Q,       /* Q */
   C_R,       /* R */
   C_S,       /* S */
   C_T,       /* T */
   C_U,       /* U */
   C_V,       /* V */
   C_W,       /* W */
   C_X,       /* X */
   C_Y,       /* Y */
   C_Z,       /* Z */
   C_Lbrack,  /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   C_Lslash,  /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   C_Rbrack,  /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   C_Circ,    /* ^  Circumflex Accent (Cirkumfleksas), standalone */
   C_Underl,  /* _  Underline (Pabraukimas) */

   C_Grave,   /* `  Grave Accent (gravis), standalone */
   C_a,       /* a */
   C_b,       /* b */
   C_c,       /* c */
   C_d,       /* d */
   C_e,       /* e */
   C_f,       /* f */
   C_g,       /* g */
   C_h,       /* h */
   C_i,       /* i */
   C_j,       /* j */
   C_k,       /* k */
   C_l,       /* l */
   C_m,       /* m */
   C_n,       /* n */
   C_o,       /* o */
   C_p,       /* p */
   C_q,       /* q */
   C_r,       /* r */
   C_s,       /* s */
   C_t,       /* t */
   C_u,       /* u */
   C_v,       /* v */
   C_w,       /* w */
   C_x,       /* x */
   C_y,       /* y */
   C_z,       /* z */
   C_Lcurl,   /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   C_Vertl,   /* |  Vertical Line (Vertikali Linija) */
   C_Rcurl,   /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   C_Tilde,   /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje), standalone */

   C_Del,

   C_AE,
   C_ae,
   C_OE,
   C_oe,
   C_IJ,
   C_ij,
   C_ss,      /* sharp s (german, C_beta) */

   C_A_Cyr,
   C_B_Cyr,
   C_V_Cyr,
   C_G_Cyr,
   C_D_Cyr,
   C_E_Cyr,
   C_Zh_Cyr,
   C_Z_Cyr,
   C_I_Cyr,
   C_J_Cyr,
   C_K_Cyr,
   C_L_Cyr,
   C_M_Cyr,
   C_N_Cyr,
   C_O_Cyr,
   C_P_Cyr,
   C_R_Cyr,
   C_S_Cyr,
   C_T_Cyr,
   C_U_Cyr,
   C_F_Cyr,
   C_H_Cyr,
   C_C_Cyr,
   C_Ch_Cyr,
   C_Sh_Cyr,
   C_Shch_Cyr,
   C_Hard_Cyr,
   C_Y_Cyr,
   C_Soft_Cyr,
   C_Ee_Cyr,
   C_Yu_Cyr,
   C_Ya_Cyr,

   C_a_Cyr,
   C_b_Cyr,
   C_v_Cyr,
   C_g_Cyr,
   C_d_Cyr,
   C_e_Cyr,
   C_zh_Cyr,
   C_z_Cyr,
   C_i_Cyr,
   C_j_Cyr,
   C_k_Cyr,
   C_l_Cyr,
   C_m_Cyr,
   C_n_Cyr,
   C_o_Cyr,
   C_p_Cyr,
   C_r_Cyr,
   C_s_Cyr,
   C_t_Cyr,
   C_u_Cyr,
   C_f_Cyr,
   C_h_Cyr,
   C_c_Cyr,
   C_ch_Cyr,
   C_sh_Cyr,
   C_shch_Cyr,
   C_hard_Cyr,
   C_y_Cyr,
   C_soft_Cyr,
   C_ee_Cyr,
   C_yu_Cyr,
   C_ya_Cyr,

/* Additional greek chars variations follow later */

   C_Alpha,
   C_Beta,
   C_Gamma,
   C_Delta,
   C_Epsilon,
   C_Zeta,
   C_Eta,
   C_Theta,
   C_Jota,
   C_Kappa,
   C_Lambda,
   C_My,
   C_Ny,
   C_Xi,
   C_Omicron,
   C_Pi,
   C_Rho,
   C_Sigma,
   C_Tau,
   C_Ypsilon,
   C_Phi,
   C_Chi,
   C_Psi,
   C_Omega,

   C_alpha,
   C_beta,
   C_gamma,
   C_delta,
   C_epsilon,  // curly epsilon
   C_zeta,
   C_eta,
   C_theta,    // straight theta
   C_jota,
   C_kappa,    // straight kappa
   C_lambda,
   C_my,
   C_ny,
   C_xi,
   C_omicron,
   C_pi,       // straight pi
   C_rho,      // straight rho
   C_sigma,    // inner sigma
   C_tau,
   C_ypsilon,
   C_phi,      // straight phi
   C_chi,
   C_psi,
   C_omega,

   C_delta_Dash, /* delta_Minus (skardi th) */

             /* All accents have no width (over the next letter) */
             /* more accents later - C_...Acc */
   C_Acute,   /* '  Acute (aku/tas, C_Apost, des/inysis kirtis) */
   C_Dacut,   /* '' Double Acute */
   C_Ogon,    /* ,  Ogonek (nosine) */
   C_Adot,    /* .  Dot Above (. virsuje) */
   C_Car,     /* v  Carron, Caron (Pauksciukas) */
   C_Macr,    /* _  Macron, Overline (bruksnys virsuje) */
   C_Diaer,   /* .. Diaeresis (Umlaut) */
   C_Ring,    /* o  Ring (Circle) Above (o virsuje, degree) */
   C_Tacom,   /* '  Turned Comma Above */
   C_Bcomma,  /* ,  Comma Bellow */
   C_Cedil,   /* ,  Cedilla (atbula nosine) */

   C_A_Ogon,  /* A, */
   C_a_Ogon,  /* a, */
   C_E_Ogon,  /* E, */
   C_e_Ogon,  /* e, */
   C_I_Ogon,  /* I, */
   C_i_Ogon,  /* i, */
   C_U_Ogon,  /* U, */
   C_u_Ogon,  /* u, */

   C_E_Adot,  /* E. */
   C_e_Adot,  /* e. */
   C_Z_Adot,  /* Z. */
   C_z_Adot,  /* z. */

   C_G_Cyr_Adot, /* G Cyr . */
   C_g_Cyr_Adot, /* g Cyr . */

   C_C_Car,   /* Cv */
   C_c_Car,   /* cv */
   C_D_Car,   /* Dv */
   C_d_Car,   /* dv */
   C_E_Car,   /* Ev */
   C_e_Car,   /* ev */
   C_L_Car,   /* Lv */
   C_l_Car,   /* lv */
   C_N_Car,   /* Nv */
   C_n_Car,   /* nv */
   C_R_Car,   /* Rv */
   C_r_Car,   /* rv */
   C_S_Car,   /* Sv */
   C_s_Car,   /* sv */
   C_T_Car,   /* Tv */
   C_t_Car,   /* tv */
   C_Z_Car,   /* Zv */
   C_z_Car,   /* zv */

   C_A_Macr,  /* A_ */
   C_a_Macr,  /* a_ */
   C_E_Macr,  /* E_ */
   C_e_Macr,  /* e_ */
   C_I_Macr,  /* I_ */
   C_i_Macr,  /* i_ */
   C_O_Macr,  /* O_ */
   C_o_Macr,  /* o_ */
   C_U_Macr,  /* U_ */
   C_u_Macr,  /* u_ */

   C_A_Diaer, /* A.. */
   C_a_Diaer, /* a.. */
   C_E_Diaer, /* E.. */
   C_e_Diaer, /* e.. */
   C_I_Diaer, /* I.. */
   C_i_Diaer, /* i.. */
   C_O_Diaer, /* O.. */
   C_o_Diaer, /* o.. */
   C_U_Diaer, /* U.. */
   C_u_Diaer, /* u.. */
   C_Y_Diaer, /* Y.. */
   C_y_Diaer, /* y.. */

   C_E_Cyr_Diaer, /* E.. */
   C_e_Cyr_Diaer, /* e.. */

   C_A_Ring,  /* Ao */
   C_a_Ring,  /* ao */
   C_U_Ring,  /* Uo */
   C_u_Ring,  /* uo */

   C_G_Tacom, /* G' */
   C_g_Tacom, /* g' */

   C_G_Bcomma,/* G, */
   C_g_Bcomma,/* g, */
   C_K_Bcomma,/* K, */
   C_k_Bcomma,/* k, */
   C_L_Bcomma,/* L, */
   C_l_Bcomma,/* l, */
   C_N_Bcomma,/* N, */
   C_n_Bcomma,/* n, */
   C_R_Bcomma,/* R, */
   C_r_Bcomma,/* r, */

   C_C_Cedil, /* C, */
   C_c_Cedil, /* c, */
   C_S_Cedil, /* S, */
   C_s_Cedil, /* s, */
   C_T_Cedil, /* T, */
   C_t_Cedil, /* t, */

   C_A, // C_A_Grave, /* A` */
   C_a, // C_a_Grave, /* a` */
   C_E, // C_E_Grave, /* E` */
   C_e, // C_e_Grave, /* e` */
   C_I, // C_I_Grave, /* I` */
   C_i, // C_i_Grave, /* i` */
   C_O, // C_O_Grave, /* O` */
   C_o, // C_o_Grave, /* o` */
   C_U, // C_U_Grave, /* U` */
   C_u, // C_u_Grave, /* u` */

   C_A, // C_A_Acute, /* A' */
   C_a, // C_a_Acute, /* a' */
   C_C_Acute, /* C' */
   C_c_Acute, /* c' */
   C_E, // C_E_Acute, /* E' */
   C_e, // C_e_Acute, /* e' */
   C_I, // C_I_Acute, /* I' */
   C_i, // C_i_Acute, /* i' */
   C_L_Acute, /* L' */
   C_l_Acute, /* l' */
   C_N_Acute, /* N' */
   C_n_Acute, /* n' */
   C_O, // C_O_Acute, /* O' */
   C_o, // C_o_Acute, /* o' */
   C_R_Acute, /* R' */
   C_r_Acute, /* r' */
   C_S_Acute, /* S' */
   C_s_Acute, /* s' */
   C_U, // C_U_Acute, /* U' */
   C_u, // C_u_Acute, /* u' */
   C_Y, // C_Y_Acute, /* Y' */
   C_y, // C_y_Acute, /* y' */
   C_Z_Acute, /* Z' */
   C_z_Acute, /* z' */

   C_K_Cyr_Acute, /* K Cyr ' */
   C_k_Cyr_Acute, /* k Cyr ' */

   C_O_Dacut, /* O'' */
   C_o_Dacut, /* o'' */
   C_U_Dacut, /* U'' */
   C_u_Dacut, /* u'' */

   C_A, // C_A_Tilde, /* A~ */
   C_a, // C_a_Tilde, /* a~ */
   C_N, // C_N_Tilde, /* N~ */
   C_n, // C_n_Tilde, /* n~ */
   C_O, // C_O_Tilde, /* O~ */
   C_o, // C_o_Tilde, /* o~ */

   C_L_Slash, /* L/ */
   C_l_Slash, /* l/ */
   C_O_Slash, /* O/ */
   C_o_Slash, /* o/ */

   C_A_Circ,  /* A^ */
   C_a_Circ,  /* a^ */
   C_E_Circ,  /* E^ */
   C_e_Circ,  /* e^ */
   C_I_Circ,  /* I^ */
   C_i_Circ,  /* i^ */
   C_O_Circ,  /* O^ */
   C_o_Circ,  /* o^ */
   C_U_Circ,  /* U^ */
   C_u_Circ,  /* u^ */

   C_D_Dash, /* D- Island. */
   C_d_Dash, /* d- */
   C_H_Dash, /* H- */
   C_h_Dash, /* h- */
   C_P_Dash, /* P- */
   C_p_Dash, /* p- */

   C_NBSP,   /* No break space */

   C_Rouble,  /* rublis, $ Cyr */
   C_Pound,   /* svaras, L/ */
   C_Yenna,   /* jena, Y- */
   C_cent,    /* c/ */

   C_Para,    /* paragrafas, # engl. */
   C_Pren,    /* paragraph end sign (pastraipos pabaiga, C_pi - pi) */
   C_Multipl, /* x */
   C_Divide,  /* -:- */
   C_PlMin,   /* -+- */
   C_1up,     /* 1 virsuj */
   C_2up,     /* 2 virsuj, kvadratu */
   C_3up,     /* 3 virsuj, kubu */
   C_a_up,    /* a virsuj */
   C_o_up,    /* o virsuj */
   C_Half,    /* 1/2 */
   C_Quart,   /* 1/4 */
   C_34,      /* 3/4 */
   C_Ldopang, /* << - rusiska kabute */
   C_Rdopang, /* >> - rusiska kabute */
   C_Lang,    /* < */
   C_Rang,    /* > */
   C_Dvertl,  /* | Koi-7-0 */
   C_Rminbr,  /* ^ Koi-7-0 ( neiginys, -| ) */
   C_Lminbr,  /* |- */
   C_Lpoint,  /* mazas taskas vidury */
   C_Bpoint,  /* bullet, didelis taskas vidury */
   C_LBquote, /* ,, (" left bellow, double comma, liet. kaire) */
   C_LAquote, /* '' (" left above, double comma above, angl. desine) */
   C_Rquote,  /* `` (" right, reversed double comma above, liet. desine, angl. kaire) */
   C_LBapost, /* , (' left bellow, comma, liet. kaire) */
   C_LAapost, /* ' (' left above, comma above, angl. desine) */
   C_Rapost,  /* ` (' right, grave, reversed comma above, liet. desine, angl. kaire) */

   C_Qst_Ov,  /* apverstas ? */
   C_Ex_Ov,   /* apverstas ! */
   C_Dots,    /* ... daugtaskis */
   C_Prom,    /* %o promiles */
   C_TM,      /* TM, Trade Mark */
   C_CO,      /* (C) Copyright */
   C_RO,      /* (R) */

/* Additional greek chars, look SGML DTD */
   C_epsilon_var, // straight epsilon
   C_theta_var,  // curly theta
   C_DiGamma,
   C_digamma,
   C_kappa_var,  // curly kappa
   C_DiLambda,
   C_dilambda,
   C_pi_var,     // curly pi, like C_omega
   C_rho_var,    // curly rho
   C_Sigma_var,  // like "S"
   C_sigma_var,  // final sigma, like "s"
   C_phi_var,    // curly phi

         /* additional accents, all of them have no width (over the next letter) */
   C_GraveAcc,    /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   C_CircAcc,     /* ^  Circumflex Accent (C_Circ), over the next letter */
   C_TildeAcc,    /* ~  Tilde (C_Tilde), over the next letter */
   C_BreveAcc,    /* u  (lankelis virsuje) */
   C_SlashAcc,    /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   C_BdotAcc,     /* .  Dot bellow */
   C_UnderlAcc,   /* _  Underline (Pabraukimas) */

   C_prim,    /* strichas prie raides (C_Acute, C_Apost) */
   C_dprim,   /* du strichai (C_Dacut) */

   C_Each,    /* V - "kiekvienam" - apversta A raide */
   C_Exists,  /* E - "egzistuoja" - apversta E raide */

   C_Aleph,   /* N - alefas */
   C_Im,      /* C_I_Got */
   C_Re,      /* C_R_Got */
   C_wp,      /* C_p_Got */

   C_le,      /* <= - maziau arba lygu */
   C_ge,      /* >= - daugiau arba lygu */
   C_ne,      /* =/= - nelygu */
   C_ll,      /* << */
   C_gg,      /* >> */
   C_sim,     /* ~ - panasu */
   C_simeq,   /* ~- - panasu arba sutampa */
   C_approx,  /* ~~ - apytiksliai lygu */
   C_cong,    /* ~= - kongruentu */
   C_equiv,   /* = - triguba lygybe - ekvivalentu */

   C_sqrt,    /* square root */
   C_int,     /* integralas */
   C_oint,    /* kreivinis integralas */
   C_Sum,     /* sum sign (C_Sigma) */
   C_Prod,    /* C_Pi */
   C_O_times, /* OX - O perbraukta kryzmai */
   C_O_plus,  /* O+ - O perbraukta pliusu */

   C_infty,   /* infinity - begalybe */
   C_propto,  /* (C_alpha) */
   C_part,    /* partial (C_delta) */
   C_empty,   /* O/ (C_O_Slash) */
   C_triangle,/* C_Delta - trikampis */
   C_nabla,   /* V - C_Delta apversta */

   C_perp,    /* T apversta - statmena */
   C_angle,   /* < - kampas (geom.) */

   C_langle,  /* < - skliaustas !!! keisti i C_Lang */
   C_rangle,  /* > - skliaustas !!! keisti i C_Rang */

   C_cap,     /* U apversta - pjuvis */
   C_cup,     /* U - junginys */

   C_vee,     /* V */
   C_wedge,   /* C_Lambda */

   C_supset,  /* D - virsaibis */
   C_supseteq,/* D= - virsaibis arba sutampa */
   C_subset,  /* C - poaibis */
   C_subseteq,/* C= - poaibis arba sutampa */
   C_nsubset, /* C/ - nepoaibis */

   C_in,      /* C_epsilon_var - priklauso */
   C_notin,   /* C_epsilon_var_Slash - nepriklauso */
   C_ni,      /* C_epsilon_var apsuktas - apima */

   C_leftarr,       /* <-- */
   C_rightarr,      /* --> */
   C_leftrightarr,  /* <--> */
   C_uparr,         /* ^| */
   C_downarr,       /* |v */
   C_updownarr,     /* ^|v */

   C_Leftarr,       /* <== */
   C_Rightarr,      /* ==> */
   C_Leftrightarr,  /* <==> */
   C_Uparr,         /* ^|| */
   C_Downarr,       /* ||v */
   C_Updownarr,     /* ^||v */

   C_mid,           /* | */
   C_paral,         /* || */

   C_diamond,     /* rombas */

   C_Club,        /* giles */
   C_Diamond,     /* bugnai */
   C_Heart,       /* cirvai sirdys */
   C_Spade,       /* pikai lapai */

   C_hyph,    /* hided hyphenation sign ("\-" for TEX) */
   C_break,   /* line break character */

   C_a_Car,   /* av - laikinai, po to ismesti !!! */

   C_euro,    /* C= euro piniginis vienetas !!! kelti prie pinigu */

   C_deg,     /* degree - panasiai, kaip C_Ring, tik desineje */
   C_micro,   /* micro - panasiai, kaip C_my */
   C_Ohm,     /* Ohm sign - panasiai, kaip C_Omega */
   C_Angst,   /* Angstroem - C_A_Ring */

   C_Horl,    /* horizontal line --- */

   C_Dag,    /* Dagger +| (kryzius) */
   C_Ddag,   /* Double dagger +|+ (Kestucio kryzius) */

   C_ff,     /* ff ligature */
   C_fi,     /* fi ligature */
   C_fj,     /* fj ligature */
   C_ffi,    /* ff ligature */
   C_ffl,    /* ff ligature */
   C_fl,     /* ff ligature */

   C_and,    /* ^ logical and */
   C_or,     /* V logical or */

   C_fun,    /* f function of */

   C_MinPl,  /* -+ minus plus */

   C_EnDash, /* -- - vidutinio ilgio bruksnys */
   C_EmDash, /* --- - ilgas bruksnys */

   C_Cdots,  /* ... - daugtaskis per viduri */
   C_WideTilde, /* ~ didele tilde */

   C_QemSpc, /* 1/4 m space */
   C_EnSpc,  /* n space */
   C_EmSpc,  /* m space */
   C_2emSpc, /* 2 m space */

   C_NewPar, /* paragraph end control character */

// lithuanian accented letters
   C_Y, // C_Y_Grave,   // Y`
   C_y, // C_y_Grave,   // y`
   C_E, // C_E_Tilde,   // E~
   C_e, // C_e_Tilde,   // e~
   C_I, // C_I_Tilde,   // I~
   C_i, // C_i_Tilde,   // i~
   C_U, // C_U_Tilde,   // U~
   C_u, // C_u_Tilde,   // u~
   C_Y, // C_Y_Tilde,   // Y~
   C_y, // C_y_Tilde,   // y~
   C_L, // C_L_Tilde,   // L~
   C_l, // C_l_Tilde,   // l~
   C_M, // C_M_Tilde,   // M~
   C_m, // C_m_Tilde,   // m~
   C_R, // C_R_Tilde,   // R~
   C_r, // C_r_Tilde,   // r~
   C_A_Ogon, // C_A_Ogon_Acute,
   C_a_Ogon, // C_a_Ogon_Acute,
   C_E_Ogon, // C_E_Ogon_Acute,
   C_e_Ogon, // C_e_Ogon_Acute,
   C_E_Adot, // C_E_Adot_Acute,
   C_e_Adot, // C_e_Adot_Acute,
   C_I_Ogon, // C_I_Ogon_Acute,
   C_i_Ogon, // C_i_Ogon_Acute,
   C_U_Ogon, // C_U_Ogon_Acute,
   C_u_Ogon, // C_u_Ogon_Acute,
   C_U_Macr, // C_U_Macr_Acute,
   C_u_Macr, // C_u_Macr_Acute,
   C_A_Ogon, // C_A_Ogon_Grave,
   C_a_Ogon, // C_a_Ogon_Grave,
   C_E_Ogon, // C_E_Ogon_Grave,
   C_e_Ogon, // C_e_Ogon_Grave,
   C_E_Adot, // C_E_Adot_Grave,
   C_e_Adot, // C_e_Adot_Grave,
   C_I_Ogon, // C_I_Ogon_Grave,
   C_i_Ogon, // C_i_Ogon_Grave,
   C_U_Ogon, // C_U_Ogon_Grave,
   C_u_Ogon, // C_u_Ogon_Grave,
   C_U_Macr, // C_U_Macr_Grave,
   C_u_Macr, // C_u_Macr_Grave,
   C_A_Ogon, // C_A_Ogon_Tilde,
   C_a_Ogon, // C_a_Ogon_Tilde,
   C_E_Ogon, // C_E_Ogon_Tilde,
   C_e_Ogon, // C_e_Ogon_Tilde,
   C_E_Adot, // C_E_Adot_Tilde,
   C_e_Adot, // C_e_Adot_Tilde,
   C_I_Ogon, // C_I_Ogon_Tilde,
   C_i_Ogon, // C_i_Ogon_Tilde,
   C_U_Ogon, // C_U_Ogon_Tilde,
   C_u_Ogon, // C_u_Ogon_Tilde,
   C_U_Macr, // C_U_Macr_Tilde,
   C_u_Macr, // C_u_Macr_Tilde,

// phonetic characters; vowels:
   C_ph_a,        // low back unrounded; a, open a; italic C_a
   C_ph_a_inv,    // low back rounded; oa; inverted italic C_a

   C_ph_a_sh,     // low-mid back unrounded; short a; inverted C_v
   C_ph_o_sh,     // low-mid back rounded; short o, open o; inverted C_c
// C_ph_o,        // mid back rounded?; o, closed o; C_o

   C_ph_u_sh,     // semi-high back rounded; short u, short open u; C_ypsilon
   C_ph_w_sh,     // semi-high back rounded; short u, short open u, obsolete; C_omega
// C_ph_u,        // semi-high central rounded?; u, closed u; C_u
// C_ph_u_soft,   // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   C_ph_e_sh,     // low-mid front unrounded; short e, open e; C_epsilon
   C_ph_ae,       // low front unrounded?; e, open e; C_ae
// C_ph_e_cl,     // high central unrounded?; closed e, german e; C_e
   C_ph_e_sh_inv, // low-mid central unrounded; hard e; inverted C_epsilon
   C_ph_e_inv,    // mid central unrounded; reduced e; inverted C_e

   C_ph_i_sh,     // semi-high front unrounded; short i, short open i; C_i without dot
// C_ph_i,        // high front unrounded?; i, closed i; C_i

// phonetic characters; consonants:
   C_ph_sh,       // sh; C_f, C_int
   C_ph_zh,       // zh; C_3
   C_ph_tsh,      // tsh; C_t C_f, C_t C_int
   C_ph_dzh,      // dzh; C_d C_3
   C_ph_th_b,     // breath th; C_theta
   C_ph_th_v,     // voiced th; C_delt_Mn, (C_delta_Minus)
   C_ph_ng,       // nasal g; C_eta
   C_ph_g,        // g; italic C_g

// additional phonetic characters:
   C_ph_oe,       // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   C_ph_o_slash,  // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   C_ph_a_l,      // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   C_ph_e_inv_l,  // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   C_ph_i_l,      // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   C_ph_o_l,      // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   C_ph_u_l,      // ; u long; C_u C_Colon

   C_ph_a_n,      // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   C_ph_a_str_n,  // ; straight a nasal; a~, C_a_Tilde
   C_ph_e_n,      // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   C_ph_oe_n,     // ; oe nasal; oe~, C_oe C_TildeAcc
   C_ph_o_n,      // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   C_ph_ch,       // german ch; C_c_Cedil

// diphtongs
   C_ph_ai_d,     //  C_a C_LigaLow C_i
   C_ph_ae_d,     //  C_a C_LigaLow C_e
   C_ph_ao_d,     //  C_a C_LigaLow C_o
   C_ph_au_d,     //  C_a C_LigaLow C_u
   C_ph_ei_d,     //  C_e C_LigaLow C_i
   C_ph_eu_d,     //  C_e C_LigaLow C_u
   C_ph_ie_d,     //  C_i C_LigaLow C_e
   C_ph_oe_d,     //  C_ph_o_sh C_LigaLow C_ph_o_slash
   C_ph_oy_d,     //  C_ph_o_sh C_LigaLow C_y
   C_ph_uo_d,     //  C_u C_LigaLow C_o

// breved phonetics
   C_ph_i_Brev,  // ; j; C_i_Brev
   C_ph_o_Brev,  //  C_o_Brev
   C_ph_u_Brev,  //  C_u_Brev

// liga accents (for diphtongs)
   C_LigaUp,      // lankelis virs dvieju raidziu
   C_LigaLow,     // lankelis po dviem raidem

   C_MidRing,     // mazas apskritimas viduryje (tusciaviduris bulletas - kaip C_Bpoint)

// phonetic accents
   C_ph_acc,       // C_Apost
   C_ph_acc_low,   // C_Comma

   C_square,

   C_male,
   C_female,

   C_O_ring,
   C_O_dot,

   C_BigRing,

   C_longleftarr,       /* <---- */
   C_longrightarr,      /* ----> */

   C_smile,

   C_box,         // pilnaviduris kvadratas viduryje

// DOS frames
   C_v_b,       // vert; ne DOS-e - C_Vertl
   C_h_b,       // hor; ne DOS-e - C_Horl
   C_vh_b,      // vert hor
   C_vl_b,      // vert left
   C_vr_b,      // vert right
   C_hu_b,      // hor up
   C_hd_b,      // hor down
   C_ul_b,      // up left
   C_dl_b,      // down left
   C_ur_b,      // up right
   C_dr_b,      // down right

   C_2v_b,      // double vert; C_paral
   C_2h_b,      // double hor
   C_2v2h_b,    // double vert double hor
   C_2v2l_b,    // double vert double left
   C_2v2r_b,    // double vert double right
   C_2h2u_b,    // double hor double up
   C_2h2d_b,    // double hor double down
   C_2u2l_b,    // double up double left
   C_2d2l_b,    // double down double left
   C_2u2r_b,    // double up double right
   C_2d2r_b,    // double down double right

   C_2vh_b,     // double vert hor
   C_2vl_b,     // double vert left
   C_2vr_b,     // double vert right
   C_h2u_b,     // hor double up
   C_h2d_b,     // hor double down
   C_2ul_b,     // double up left
   C_2dl_b,     // double down left
   C_2ur_b,     // double up right
   C_2dr_b,     // double down right

   C_v2h_b,     // vert double hor
   C_v2l_b,     // vert double left
   C_v2r_b,     // vert double right
   C_2hu_b,     // double hor up
   C_2hd_b,     // double hor down
   C_u2l_b,     // up double left
   C_d2l_b,     // down double left
   C_u2r_b,     // up double right
   C_d2r_b,     // down double right

   C_block,     // pilnaviduris kvadratas per visa laukeli
   C_dgrblk,    // tamsiai pilkas ---//--- (75% shaded)
   C_grblk,     // pilkas ---//--- (50% shaded)
   C_lgrblk,    // sviesiai pilkas ---//--- (25% shaded)
   C_uphblk,    // pilnaviduris staciakampis per puse laukelio virsuje
   C_dnhblk,    // ---//--- apacioje
   C_lthblk,    // ---//--- kaireje
   C_rthblk,    // ---//--- desineje

   C_utrif,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   C_dtrif,     // pilnaviduris trikampis zemyn
   C_ltrif,     // pilnaviduris trikampis i kaire
   C_rtrif,     // pilnaviduris trikampis i desine

   C_ph_uu_sh,

   C_hhyph,          // hard hyphen - zodzio kelimas per prievarta -\break
   C_sbreak,         // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   C_hSpc,           // hard space - technical space after TEX commands - do not process
   C_hbreak,         // break su \hfill, xmlsty keiciamas is C_Cr ("\r")
   C_lSpc,           // last space - space, to be changed to C_NBSP after LAST_WORD_LEN
   C_hlSpc,          // hard last space - C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   C_utrif_rtf,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   C_dtrif_rtf,     // pilnaviduris trikampis zemyn
   C_ltrif_rtf,     // pilnaviduris trikampis i kaire
   C_rtrif_rtf,     // pilnaviduris trikampis i desine

// erdvines rodykles
   C_3DTopLightLeftArrowHead,
   C_3DBotLightLeftArrowHead,
   C_3DTopLightRightArrowHead,
   C_3DBotLightRightArrowHead,
   C_3DLeftLightUpArrowHead,
   C_3DRightLightUpArrowHead,
   C_3DLeftLightDownArrowHead,
   C_3DRightLightDownArrowHead,

   C_MinusMath,

   C_ZeroWidthSpace,

   C_ph_glot_stop,

   C_AcuteNcomb,
   C_CedilNcomb,
   C_MacrNcomb,

   C_DollNctrl,

   C_OgonNcomb,

   C_No,

   C_CarNcomb,
   C_DiaerNcomb,
   C_TildeNcomb,

   C_utri,
   C_dtri,
   C_ltri,
   C_rtri,

   C_Oline,

   C_R,     // C_R_Oline
   C_X,     // C_X_Oline

   C_leqslant,
   C_geqslant,

   C_i,     // C_i_Grave_Dotless
   C_i,     // C_i_Acute_Dotless
   C_i,     // C_i_Tilde_Dotless

   C_A_Cyr,  // C_A_Cyr_Acute,
   C_E_Cyr,  // C_E_Cyr_Acute,
   C_I_Cyr,  // C_I_Cyr_Acute,
   C_O_Cyr,  // C_O_Cyr_Acute,
   C_U_Cyr,  // C_U_Cyr_Acute,
   C_Y_Cyr,  // C_Y_Cyr_Acute,
   C_Ee_Cyr, // C_Ee_Cyr_Acute,
   C_Yu_Cyr, // C_Ju_Cyr_Acute,
   C_Ya_Cyr, // C_Ja_Cyr_Acute,

   C_a_Cyr,  // C_a_Cyr_Acute,
   C_e_Cyr,  // C_e_Cyr_Acute,
   C_i_Cyr,  // C_i_Cyr_Acute,
   C_o_Cyr,  // C_o_Cyr_Acute,
   C_u_Cyr,  // C_u_Cyr_Acute,
   C_y_Cyr,  // C_y_Cyr_Acute,
   C_ee_Cyr, // C_ee_Cyr_Acute,
   C_yu_Cyr, // C_ju_Cyr_Acute,
   C_ya_Cyr, // C_ja_Cyr_Acute,

   C_NullSpc, // C_NullSpc

   C_Dash_Diaer, // C_Dash_Diaer

   C_bdiamond,

   C_DegCels,

   C_hBpoint,  /* bullet, didelis taskas vidury */

// ----------------------- old style cyrillic
   C_Fita_Cyr,
   C_fita_Cyr,
   C_Yat_Cyr,
   C_yat_Cyr,

   C_checkmark,

   C_prim_Ncomb,
   C_dprim_Ncomb,
};
