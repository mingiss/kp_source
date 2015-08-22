/*
 *
 * Kptt2.c   Kodu lenteles
 *
 */

#include "stdafx.h"

/* #define KpInc */   /* Kp* projektai */
#define TvInc         /* Tev C++ projektai */


#ifdef TvInc
#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kptree.h"
#include "kpcolors.h"
#include "kpctype.h"
#include "kpstring.h"
#include "res_com.h"
#include "kpstdio.h"
#include "kpwindow.h"
#include "kperr.h"
#endif

#ifdef KpInc
#include "kpxe.h"
#if FileSys==MSDos
#include "..\kpt\kptt.h"
#elif FileSys==Unix
#include "../kpt/kptt.h"
#else
#include "kptt.h"
#endif
#endif

int LangToCtbl[KpNumOfLangs] =
{
   0,  // KpLangEn
   71, // KpLangLt
   79, // KpLangPl_1250
   71, // KpLangPl_1257
   73, // KpLangRu_1251
   73, // KpLangRu_0
};

const KpChar iNullStr[]={C_Nul};

KpChar Ct01l[Ctbsiz/2]={   /*  ISO-646, IRV version (basic Latin set) (Ascii anglu k.) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct02l[Ctbsiz/2]={   /*  (Koi-7-0, Koi-8 apatine dalis) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Rouble, C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Rminbr, C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Dvertl, C_Rcurl,  C_Macr,   C_Del
  };

KpChar Ct02n[Ctbsiz/2]={   /*  ISO Registration #37 (basic Cyrillic set) (Koi-7-1) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Rouble, C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_yu_Cyr, C_a_Cyr,  C_b_Cyr,  C_c_Cyr,  C_d_Cyr,  C_e_Cyr,  C_f_Cyr,  C_g_Cyr,
  C_h_Cyr,  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,
  C_p_Cyr,  C_ya_Cyr, C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_zh_Cyr, C_v_Cyr,
  C_soft_Cyr,C_y_Cyr, C_z_Cyr,  C_sh_Cyr, C_ee_Cyr, C_shch_Cyr,C_ch_Cyr,C_hard_Cyr,
  C_Yu_Cyr, C_A_Cyr,  C_B_Cyr,  C_C_Cyr,  C_D_Cyr,  C_E_Cyr,  C_F_Cyr,  C_G_Cyr,
  C_H_Cyr,  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,
  C_P_Cyr,  C_Ya_Cyr, C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_Zh_Cyr, C_V_Cyr,
  C_Soft_Cyr,C_Y_Cyr, C_Z_Cyr,  C_Sh_Cyr, C_Ee_Cyr, C_Shch_Cyr,C_Ch_Cyr,/* C_Hard_Cyr */ C_Del
  };

KpChar Ct02h[Ctbsiz/2]={   /*  ISO Registration #37 (basic Cyrillic set) (Koi-8) */
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_yu_Cyr, C_a_Cyr,  C_b_Cyr,  C_c_Cyr,  C_d_Cyr,  C_e_Cyr,  C_f_Cyr,  C_g_Cyr,
  C_h_Cyr,  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,
  C_p_Cyr,  C_ya_Cyr, C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_zh_Cyr, C_v_Cyr,
  C_soft_Cyr,C_y_Cyr, C_z_Cyr,  C_sh_Cyr, C_ee_Cyr, C_shch_Cyr,C_ch_Cyr,C_hard_Cyr,
  C_Yu_Cyr, C_A_Cyr,  C_B_Cyr,  C_C_Cyr,  C_D_Cyr,  C_E_Cyr,  C_F_Cyr,  C_G_Cyr,
  C_H_Cyr,  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,
  C_P_Cyr,  C_Ya_Cyr, C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_Zh_Cyr, C_V_Cyr,
  C_Soft_Cyr,C_Y_Cyr, C_Z_Cyr,  C_Sh_Cyr, C_Ee_Cyr, C_Shch_Cyr,C_Ch_Cyr,C_Hard_Cyr
  };

KpChar Ct03l[Ctbsiz/2]={   /*  ISO-5426 (extended Latin set) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Ex_Ov,  C_LBquote,C_Pound,  C_Doll,   C_Yenna,  C_Unkn,   C_Para,
  C_Unkn,   C_Tacom,  C_LAquote, C_Ldopang,C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Noch,   C_Noch,   C_Noch,   C_Unkn,   C_Lpoint,
  C_Dacut,  C_Unkn,   C_Rquote,C_Rdopang,C_Numb,   C_Unkn,   C_Unkn,   C_Qst_Ov,
  C_Unkn,   C_Grave,  C_Acute,  C_Circ,   C_Tilde,  C_Macr,   C_Unkn,   C_Adot,
  C_Diaer,  C_Unkn,   C_Ring,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Car,
  C_Cedil,  C_Ogon,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Underl, C_Unkn,   C_Bcomma, C_Unkn,   C_Noch,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Noch,   C_AE,     C_D_Dash,C_Noch,   C_Noch,   C_Noch,   C_IJ,     C_Noch,
  C_L_Slash,C_O_Slash,C_OE,     C_Noch,   C_P_Dash,C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_ae,     C_d_Dash,C_delta_Dash,C_Noch,   C_Unkn,   C_ij,     C_Noch,
  C_l_Slash,C_o_Slash,C_oe,     C_ss,     C_p_Dash,C_Noch,   C_Noch,   C_Noch
  };

KpChar Ct04l[Ctbsiz/2]={   /*  ISO-DIS-5427 (extended Cyrillic set) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Unkn,   C_Unkn,   C_g_Cyr_Adot,C_Unkn,C_e_Cyr_Diaer,C_s,  C_i,      C_i_Diaer,
  C_j,      C_Unkn,   C_Unkn,   C_Unkn,   C_k_Cyr_Acute,C_Unkn,C_Unkn,  C_Noch,
  C_Unkn,   C_Unkn,   C_v,      C_Unkn,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Lbrack, C_Noch,   C_Rbrack, C_Noch,   C_Underl,
  C_Unkn,   C_Unkn,   C_G_Cyr_Adot,C_Unkn,C_E_Cyr_Diaer,C_S,  C_I,      C_I_Diaer,
  C_J,      C_Unkn,   C_Unkn,   C_Unkn,   C_K_Cyr_Acute,C_Unkn,C_Unkn,  C_Hard_Cyr,
  C_Unkn,   C_Unkn,   C_V,      C_Unkn,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch
  };

KpChar Ct05l[Ctbsiz/2]={   /*  ISO-5428 (Greek set) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Grave,  C_Acute,  C_LBquote,C_Tilde,  C_Unkn,   C_Unkn,   C_Unkn,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Unkn,   C_Unkn,   C_LAquote,C_Rquote, C_Unkn,   C_Unkn,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Point,  C_Noch,   C_Noch,   C_Noch,   C_Semic,
  C_Noch,   C_Alpha,  C_Beta,   C_Noch,   C_Gamma,  C_Delta,  C_Epsilon,C_Sigma_var,
  C_DiGamma,C_Zeta,   C_Eta,    C_Theta,  C_Jota,   C_Kappa,  C_Lambda, C_My,
  C_Ny,     C_Xi,     C_Omicron,C_Pi,     C_Q,      C_Rho,    C_Sigma,  C_Noch,
  C_Tau,    C_Ypsilon,C_Phi,    C_Chi,    C_Psi,    C_Omega,  C_DiLambda,C_Noch,
  C_Noch,   C_alpha,  C_beta,   C_b,      C_gamma,  C_delta,  C_epsilon,C_sigma_var,
  C_digamma,C_zeta,   C_eta,    C_theta,  C_jota,   C_kappa,  C_lambda, C_my,
  C_ny,     C_xi,     C_omicron,C_pi,     C_q,      C_rho,    C_sigma,  C_sigma_var,
  C_tau,    C_ypsilon,C_phi,    C_chi,    C_psi,    C_omega,  C_dilambda,C_Noch
  };

KpChar Ct10h[Ctbsiz/2]={   /*  TeX TEV output characterset */
  C_A_Tilde,C_A_Ogon, C_C_Acute,C_C_Car,  C_E_Adot, C_Noch,   C_E_Ogon, C_Noch,
  C_Noch,   C_I_Ogon, C_L_Slash,C_N_Acute,C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_S_Acute,C_S_Car,  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Y_Diaer,
  C_U_Ogon, C_Z_Acute,C_Z_Car,  C_Z_Adot, C_Dag,    C_cent,   C_Yenna,  C_Para,
  C_a_Tilde,C_a_Ogon, C_c_Acute,C_c_Car,  C_e_Adot, C_Noch,   C_e_Ogon, C_Noch,
  C_Noch,   C_i_Ogon, C_l_Slash,C_n_Acute,C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_s_Acute,C_s_Car,  C_Noch,   C_Noch,   C_Noch,   C_Pren,   C_y_Diaer,
  C_u_Ogon, C_z_Acute,C_z_Car,  C_z_Adot, C_Ddag,   C_Ex_Ov,  C_Qst_Ov, C_Pound,
  C_A_Grave,C_A_Acute,C_A_Circ, C_U_Macr, C_A_Diaer,C_A_Ring, C_AE,     C_C_Cedil,
  C_E_Grave,C_E_Acute,C_E_Circ, C_E_Diaer,C_I_Grave,C_I_Acute,C_I_Circ, C_I_Diaer,
  C_Noch,   C_N_Tilde,C_O_Grave,C_O_Acute,C_O_Circ, C_O_Tilde,C_O_Diaer,C_OE,
  C_O_Slash,C_U_Grave,C_U_Acute,C_U_Circ, C_U_Diaer,C_Y_Acute,C_Noch,   C_Noch,
  C_a_Grave,C_a_Acute,C_a_Circ, C_u_Macr, C_a_Diaer,C_a_Ring, C_ae,     C_c_Cedil,
  C_e_Grave,C_e_Acute,C_e_Circ, C_e_Diaer,C_i_Grave_Dotless,C_i_Acute_Dotless,C_i_Circ, C_i_Diaer,
  C_Noch,   C_n_Tilde,C_o_Grave,C_o_Acute,C_o_Circ, C_o_Tilde,C_o_Diaer,C_oe,
  C_o_Slash,C_u_Grave,C_u_Acute,C_u_Circ, C_u_Diaer,C_y_Acute,C_Noch,   C_hyph
  };

KpChar Ct11l[Ctbsiz/2]={   /*  TeX TEV Cyrillic character set */
  C_Unkn,   C_Unkn,   C_Unkn,   C_Ee_Cyr, C_I,      C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_ee_Cyr, C_i,      C_Unkn,   C_Unkn,   C_Unkn,
  C_Yu_Cyr, C_Zh_Cyr, C_J_Cyr,C_E_Cyr_Diaer,C_Noch, C_Noch,   C_Noch,   C_Ya_Cyr,
  C_yu_Cyr, C_zh_Cyr, C_j_Cyr,C_e_Cyr_Diaer,C_Noch, C_Noch,   C_s,      C_ya_Cyr,
  C_Spc,    C_Excl,   C_Quote,  C_Noch,   C_Noch,   C_Perc,   C_Noch,   C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Noch,   C_Comma,  C_Dash,   C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Ldopang,C_Noch,   C_Rdopang,C_Quest,
  C_Noch,   C_A_Cyr,  C_B_Cyr,  C_C_Cyr,  C_D_Cyr,  C_E_Cyr,  C_F_Cyr,  C_G_Cyr,
  C_H_Cyr,  C_I_Cyr,  C_J,      C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,
  C_P_Cyr,  C_Ch_Cyr, C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_V_Cyr,  C_Shch_Cyr,
  C_Sh_Cyr, C_Y_Cyr,  C_Z_Cyr,  C_Lbrack, C_LAquote,C_Rbrack,C_Soft_Cyr,C_Hard_Cyr,
  C_LAapost,C_a_Cyr,  C_b_Cyr,  C_c_Cyr,  C_d_Cyr,  C_e_Cyr,  C_f_Cyr,  C_g_Cyr,
  C_h_Cyr,  C_i_Cyr,  C_j,      C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,
  C_p_Cyr,  C_ch_Cyr, C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_v_Cyr,  C_shch_Cyr,
  C_sh_Cyr, C_y_Cyr,  C_z_Cyr,  C_EnDash, C_EmDash, C_No,    C_soft_Cyr,C_hard_Cyr,
  };

KpChar Ct11h[Ctbsiz/2]={   /*  TeX TEV Cyrillic character set - upper codepage - accented chars */
C_A_Cyr_Acute,C_E_Cyr_Acute,C_I_Cyr_Acute,C_O_Cyr_Acute,C_U_Cyr_Acute,C_Y_Cyr_Acute,C_Ee_Cyr_Acute,C_Yu_Cyr_Acute,
C_Ya_Cyr_Acute,C_Noch,C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
C_a_Cyr_Acute,C_e_Cyr_Acute,C_i_Cyr_Acute,C_o_Cyr_Acute,C_u_Cyr_Acute,C_y_Cyr_Acute,C_ee_Cyr_Acute,C_yu_Cyr_Acute,
C_ya_Cyr_Acute,C_Noch,C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  };

KpChar Ct12l[Ctbsiz/2]={   /*  TeX TEV Cyrillic character set for hyphenation patterns */
  C_Unkn,   C_Unkn,   C_Unkn,   C_Ee_Cyr, C_I,      C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Noch,   C_i,      C_Unkn,   C_Unkn,   C_Unkn,
  C_Yu_Cyr, C_Zh_Cyr, C_J_Cyr,C_E_Cyr_Diaer,C_Noch, C_Noch,   C_Noch,   C_Ya_Cyr,
  C_Noch,   C_Noch,   C_Noch,C_e_Cyr_Diaer,C_Noch,  C_Noch,   C_s,      C_Noch,
  C_Spc,    C_Excl,   C_Quote,  C_Noch,   C_Noch,   C_Perc,   C_Noch,   C_Apost,
  C_ee_Cyr, C_yu_Cyr, C_zh_Cyr, C_j_Cyr,  C_ya_Cyr,C_hard_Cyr,C_Point,  C_soft_Cyr,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Ldopang,C_Noch,   C_Rdopang,C_Quest,
  C_Noch,   C_A_Cyr,  C_B_Cyr,  C_C_Cyr,  C_D_Cyr,  C_E_Cyr,  C_F_Cyr,  C_G_Cyr,
  C_H_Cyr,  C_I_Cyr,  C_J,      C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,
  C_P_Cyr,  C_Ch_Cyr, C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_V_Cyr,  C_Shch_Cyr,
  C_Sh_Cyr, C_Y_Cyr,  C_Z_Cyr,  C_Lbrack, C_LAquote,C_Rbrack,C_Soft_Cyr,C_Hard_Cyr,
  C_LAapost,C_a_Cyr,  C_b_Cyr,  C_c_Cyr,  C_d_Cyr,  C_e_Cyr,  C_f_Cyr,  C_g_Cyr,
  C_h_Cyr,  C_i_Cyr,  C_j,      C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,
  C_p_Cyr,  C_ch_Cyr, C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_v_Cyr,  C_shch_Cyr,
  C_sh_Cyr, C_y_Cyr,  C_z_Cyr,  C_EnDash, C_EmDash, C_No,     C_Noch,   C_Noch,
  };

KpChar Ct21l[Ctbsiz/2]={   /*  Ascii german */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_A_Diaer,C_O_Diaer,C_U_Diaer,C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_a_Diaer,C_o_Diaer,C_u_Diaer,C_ss,     C_Del
  };

KpChar Ct22l[Ctbsiz/2]={   /*  Ascii french */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Pound,  C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_a_Grave,C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Ring,   C_c_Cedil,C_Para,   C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_e_Acute,C_u_Grave,C_e_Grave,C_Diaer,  C_Del
  };

KpChar Ct23l[Ctbsiz/2]={   /*  Ascii norvegian/danish */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_AE,     C_O_Slash,C_A_Ring, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_ae,     C_o_Slash,C_a_Ring, C_Tilde,  C_Del
  };

KpChar Ct24l[Ctbsiz/2]={   /*  Ascii swedish/finnish */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_A_Diaer,C_O_Diaer,C_A_Ring, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_a_Diaer,C_o_Diaer,C_a_Ring, C_Tilde,  C_Del
  };

KpChar Ct31h[Ctbsiz/2]={   /*  IBM-437 Multilingual (Latin I) */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_a_Diaer,C_a_Grave,C_a_Ring, C_c_Cedil,
  C_e_Circ, C_e_Diaer,C_e_Grave,C_i_Diaer,C_i_Circ, C_i_Grave_Dotless,C_A_Diaer,C_A_Ring,
  C_E_Acute,C_ae,     C_AE,     C_o_Circ, C_o_Diaer,C_o_Grave,C_u_Circ, C_u_Grave,
  C_y_Diaer,C_O_Diaer,C_U_Diaer,C_cent,   C_Pound,  C_Yenna,  C_Unkn,   C_fun,
  C_a_Acute,C_i_Acute_Dotless,C_o_Acute,C_u_Acute,C_n_Tilde,C_N_Tilde,C_a_up,   C_o_up,
  C_Qst_Ov, C_Lminbr, C_Rminbr, C_Half,   C_Quart,  C_Ex_Ov,  C_Ldopang,C_Rdopang,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_alpha,  C_beta,   C_Gamma,  C_pi,     C_Sigma,  C_sigma,  C_my,     C_tau,
  C_Phi,    C_Theta,  C_Omega,  C_delta,  C_infty,  C_phi /* C_empty */, C_epsilon_var /* C_in */, C_cap,
  C_equiv,  C_PlMin,  C_ge,     C_le,     C_Unkn,   C_Unkn,   C_Divide, C_approx,
  C_deg,    C_Bpoint, C_Lpoint, C_sqrt,   C_Unkn,   C_2up,    C_box,    C_NBSP
  };

KpChar Ct32h[Ctbsiz/2]={   /*  IBM-852 Slavic (Latin II) */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_a_Diaer,C_u_Ring, C_c_Acute,C_c_Cedil,
  C_l_Slash,C_e_Diaer,C_O_Dacut,C_o_Dacut,C_i_Circ, C_Z_Acute,C_A_Diaer,C_C_Acute,
  C_E_Acute,C_L_Acute,C_l_Acute,C_o_Circ, C_o_Diaer,C_L_Car,  C_l_Car,  C_S_Acute,
  C_s_Acute,C_O_Diaer,C_U_Diaer,C_T_Car,  C_t_Car,  C_L_Slash,C_Multipl,C_c_Car,
  C_a_Acute,C_i_Acute_Dotless,C_o_Acute,C_u_Acute,C_A_Ogon, C_a_Ogon, C_Z_Car,  C_z_Car,
  C_E_Ogon, C_e_Ogon, C_Rminbr, C_z_Acute,C_C_Car,  C_s_Cedil,C_Ldopang,C_Rdopang,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_A_Acute,C_A_Circ, C_E_Car,
  C_S_Cedil,C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_Z_Adot, C_z_Adot, C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_Rouble,
  C_d_Dash,C_D_Dash,C_D_Car,  C_E_Diaer,C_d_Car,  C_N_Car,  C_I_Acute,C_I_Circ,
  C_e_Car,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_T_Cedil,C_U_Ring, C_uphblk,
  C_O_Acute,C_ss,     C_O_Circ, C_N_Acute,C_n_Acute,C_n_Car,  C_S_Car,  C_s_Car,
  C_R_Acute,C_U_Acute,C_r_Acute,C_U_Dacut,C_y_Acute,C_Y_Acute,C_t_Cedil,C_Acute,
  C_Macr,   C_Dacut,  C_Ogon,   C_Car,    C_BreveAcc,C_Para,  C_Divide, C_Cedil,
  C_deg,    C_Diaer,  C_Lpoint, C_u_Dacut,C_R_Car,  C_r_Car,  C_box,    C_NBSP
  };

KpChar Ct33h[Ctbsiz/2]={   /*  IBM-850 Multilingual (Latin I+) */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_a_Diaer,C_a_Grave,C_a_Ring, C_c_Cedil,
  C_e_Circ, C_e_Diaer,C_e_Grave,C_i_Diaer,C_i_Circ, C_i_Grave_Dotless,C_A_Diaer,C_A_Ring,
  C_E_Acute,C_ae,     C_AE,     C_o_Circ, C_o_Diaer,C_o_Grave,C_u_Circ, C_u_Grave,
  C_y_Diaer,C_O_Diaer,C_U_Diaer,C_o_Slash,C_Pound,  C_O_Slash,C_Multipl,C_fun,
  C_a_Acute,C_i_Acute_Dotless,C_o_Acute,C_u_Acute,C_n_Tilde,C_N_Tilde,C_a_up,   C_o_up,
  C_Qst_Ov, C_RO,     C_Rminbr, C_Half,   C_Quart,  C_Ex_Ov,  C_Ldopang,C_Rdopang,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_A_Acute,C_A_Circ, C_A_Grave,
  C_CO,     C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_cent,   C_Yenna,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_a_Tilde,C_A_Tilde,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_Rouble,
  C_delta_Dash,C_D_Dash,C_E_Circ, C_E_Diaer,C_E_Grave,C_1up,    C_I_Acute,C_I_Circ,
  C_I_Diaer,C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_Dvertl, C_I_Grave,C_uphblk,
  C_O_Acute,C_ss,     C_O_Circ, C_O_Grave,C_o_Tilde,C_O_Tilde,C_micro,  C_p_Dash,
  C_P_Dash,C_U_Acute,C_U_Circ, C_U_Grave,C_y_Acute,C_Y_Acute,C_Macr,   C_Acute,
  C_hyph,   C_PlMin,  C_Unkn,   C_34,     C_Pren,   C_Para,   C_Divide, C_Cedil,
  C_deg,    C_Diaer,  C_Lpoint, C_1up,    C_3up,    C_2up,    C_box,    C_NBSP
  };

KpChar Ct34h[Ctbsiz/2]={   /*  IBM-863 Canadian-French */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_A_Circ, C_a_Grave,C_Pren,   C_c_Cedil,
  C_e_Circ, C_e_Diaer,C_e_Grave,C_i_Diaer,C_i_Circ, C_Unkn,   C_A_Grave,C_Para,
  C_E_Acute,C_E_Grave,C_E_Circ, C_o_Circ, C_E_Diaer,C_I_Diaer,C_u_Circ, C_u_Acute,
  C_Rouble, C_O_Circ, C_U_Diaer,C_cent,   C_Pound,  C_U_Grave,C_U_Circ, C_fun,
  C_Dvertl, C_Acute,  C_o_Acute,C_u_Acute,C_Diaer,  C_Cedil,  C_3up,    C_Macr,
  C_I_Circ, C_Lminbr, C_Rminbr, C_Half,   C_Quart,  C_34,     C_Ldopang,C_Rdopang,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_alpha,  C_beta,   C_Gamma,  C_pi,     C_Sigma,  C_sigma,  C_my,     C_tau,
  C_Phi,    C_Theta,  C_Omega,  C_delta,  C_infty,  C_phi /* C_empty */, C_epsilon_var /* C_in */, C_cap,
  C_equiv,  C_PlMin,  C_ge,     C_le,     C_Unkn,   C_Unkn,   C_Divide, C_approx,
  C_deg,    C_Bpoint, C_Lpoint, C_sqrt,   C_Unkn,   C_2up,    C_box,    C_NBSP
  };

KpChar Ct40l[Ctbsiz/2]={   /*  IBM-437 apatine dalis */
  C_Nul,    C_Unkn,   C_Unkn, // C_Heart,  C_Diamond,C_Club,   C_Spade,  C_Bpoint, // naudoti virðutinës lentelës dalies simbolius
                                C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,C_Ht/*C_BigRing*/,C_Lf/*C_Unkn*/,C_Vt/*C_male*/,C_Ff/*C_female*/,C_Cr/*C_Unkn*/,C_Unkn,C_Unkn,
//C_rtrif,  C_ltrif,C_updownarr,C_Unkn,   C_Pren,  C_Para,   C_Unkn,   C_Unkn, // naudoti virðutinës lentelës dalies simbolius
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
//C_uparr - AKLZ nuorodoms nesuveikia, reikia, kad generuotÅ³ texinÄ™ komandÄ… */,
//          C_downarr,Eof/*C_rightarr*/,C_leftarr,C_Unkn/*C_Lminbr*/,C_leftrightarr,C_utrif,C_dtrif, // naudoti virðutinës lentelës dalies simbolius
  C_Unkn,   C_Unkn,   Eof,      C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,   C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct41h[Ctbsiz/2]={   /*  IBM-774 Lithuanian standard (IBM-437 pagrindu) */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_a_Diaer,C_a_Grave,C_a_Ring, C_c_Cedil,
  C_e_Circ, C_e_Diaer,C_e_Grave,C_i_Diaer,C_i_Circ, C_i_Grave_Dotless,C_A_Diaer,C_A_Ring,
  C_E_Acute,C_ae,     C_AE,     C_o_Circ, C_o_Diaer,C_o_Grave,C_u_Circ, C_u_Grave,
  C_y_Diaer,C_O_Diaer,C_U_Diaer,C_cent,   C_Pound,  C_Yenna,  C_Unkn,   C_fun,
  C_a_Acute,C_i_Acute_Dotless,C_o_Acute,C_u_Acute,C_n_Tilde,C_N_Tilde,C_a_up,   C_o_up,
  C_Qst_Ov, C_Lminbr, C_Rminbr, C_Half,   C_Quart,  C_Ex_Ov,  C_Ldopang,C_Rdopang,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_A_Ogon, C_C_Car,  C_E_Ogon,
  C_E_Adot, C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_I_Ogon, C_S_Car,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_U_Ogon, C_U_Macr,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_Z_Car,
  C_a_Ogon, C_c_Car,  C_e_Ogon, C_e_Adot, C_i_Ogon, C_s_Car,  C_u_Ogon, C_u_Macr,
  C_z_Car,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_alpha,  C_beta,   C_Gamma,  C_pi,     C_Sigma,  C_sigma,  C_my,     C_tau,
  C_Phi,    C_Theta,  C_Omega,  C_delta,  C_infty,  C_phi /* C_empty */, C_epsilon_var /* C_in */, C_cap,
  C_equiv,  C_PlMin,  C_ge,     C_le,     C_LBquote,C_Rquote, C_Divide, C_approx,
  C_deg,    C_Bpoint, C_Lpoint, C_sqrt,   C_Unkn,   C_2up,    C_box,    C_NBSP
  };

KpChar Ct42h[Ctbsiz/2]={   /*  IBM-772 Lithuanian standard with Cyrillic (IBM-855 pagrindu) */
  C_A_Cyr,  C_B_Cyr,  C_V_Cyr,  C_G_Cyr,  C_D_Cyr,  C_E_Cyr,  C_Zh_Cyr, C_Z_Cyr,
  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,  C_P_Cyr,
  C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_F_Cyr,  C_H_Cyr,  C_C_Cyr,  C_Ch_Cyr,
  C_Sh_Cyr, C_Shch_Cyr,C_Hard_Cyr,C_Y_Cyr,C_Soft_Cyr,C_Ee_Cyr,C_Yu_Cyr, C_Ya_Cyr,
  C_a_Cyr,  C_b_Cyr,  C_v_Cyr,  C_g_Cyr,  C_d_Cyr,  C_e_Cyr,  C_zh_Cyr, C_z_Cyr,
  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_A_Ogon, C_C_Car,  C_E_Ogon,
  C_E_Adot, C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_I_Ogon, C_S_Car,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_U_Ogon, C_U_Macr,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_Z_Car,
  C_a_Ogon, C_c_Car,  C_e_Ogon, C_e_Adot, C_i_Ogon, C_s_Car,  C_u_Ogon, C_u_Macr,
  C_z_Car,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_f_Cyr,  C_h_Cyr,  C_c_Cyr,  C_ch_Cyr,
  C_sh_Cyr, C_shch_Cyr,C_hard_Cyr,C_y_Cyr,C_soft_Cyr,C_ee_Cyr,C_yu_Cyr, C_ya_Cyr,
  C_E_Cyr_Diaer,C_e_Cyr_Diaer,C_ge,C_le,  C_LBquote,C_Rquote, C_Divide, C_approx,
  C_deg,    C_Bpoint, C_Lpoint, C_sqrt,   C_Unkn,   C_2up,    C_box,    C_NBSP
  };

KpChar Ct43h[Ctbsiz/2]={   /*  IBM-773 (IBM-Kbl) Lithuanian (IBM-855 pagrindu) */
  C_A_Cyr,  C_B_Cyr,  C_V_Cyr,  C_G_Cyr,  C_D_Cyr,  C_E_Cyr,  C_Zh_Cyr, C_Z_Cyr,
  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,  C_P_Cyr,
  C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_F_Cyr,  C_H_Cyr,  C_C_Cyr,  C_Ch_Cyr,
  C_Sh_Cyr, C_Shch_Cyr,C_Hard_Cyr,C_Y_Cyr,C_Soft_Cyr,C_Ee_Cyr,C_Yu_Cyr, C_Ya_Cyr,
  C_a_Cyr,  C_b_Cyr,  C_v_Cyr,  C_g_Cyr,  C_d_Cyr,  C_e_Cyr,  C_zh_Cyr, C_z_Cyr,
  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_A_Ogon, C_a_Ogon, C_C_Car,  C_c_Car,
  C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_f_Cyr,  C_h_Cyr,  C_c_Cyr,  C_ch_Cyr,
  C_sh_Cyr, C_shch_Cyr,C_hard_Cyr,C_y_Cyr,C_soft_Cyr,C_ee_Cyr,C_yu_Cyr, C_ya_Cyr,
  C_E_Ogon, C_e_Ogon, C_E_Adot, C_e_Adot, C_I_Ogon, C_i_Ogon, C_S_Car,  C_s_Car,
  C_U_Ogon, C_u_Ogon, C_U_Macr, C_u_Macr, C_Z_Car,  C_z_Car,  C_box,    C_Noch /* C_NBSP */
  };

KpChar Ct44h[Ctbsiz/2]={   /*  IBM-770 (Baltic, Fotonija, RST 1095-89, LT, LV, EE, D) */
  C_C_Car,  C_u_Diaer,C_e_Adot, C_a_Macr, C_a_Diaer,C_a_Ogon, C_l_Bcomma,C_c_Car,
  C_e_Macr, C_E_Macr, C_e_Ogon, C_E_Ogon, C_i_Macr, C_i_Ogon, C_A_Diaer,C_A_Ogon,
  C_E_Adot, C_z_Car,  C_Z_Car,  C_o_Tilde,C_o_Diaer,C_O_Tilde,C_u_Macr, C_u_Ogon,
C_g_Bcomma/*C_g_Tacom*/,C_O_Diaer,C_U_Diaer,C_cent,   C_L_Bcomma,C_LBquote,C_s_Car, C_S_Car,
  C_A_Macr, C_I_Macr, C_k_Bcomma,C_K_Bcomma,C_n_Bcomma,C_N_Bcomma,C_U_Macr,C_U_Ogon,
  C_G_Bcomma,C_LAquote,C_Rminbr,C_Half,   C_Quart,  C_I_Ogon, C_Ldopang,C_Rdopang,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_alpha,  C_beta,   C_Gamma,  C_pi,     C_Sigma,  C_sigma,  C_my,     C_tau,
  C_Phi,    C_Theta,  C_Omega,  C_delta,  C_infty,  C_phi /* C_empty */, C_epsilon_var /* C_in */, C_cap,
  C_equiv,  C_PlMin,  C_ge,     C_le,     C_Unkn,   C_Unkn,   C_Divide, C_approx,
  C_deg,    C_Bpoint, C_Lpoint, C_sqrt,   C_Unkn,   C_2up,    C_box,    C_NBSP
  };

KpChar Ct45h[Ctbsiz/2]={   /*  ISO-8859-4 (Baltic-RIM senas, DK,SE,NO,SF,grenl.,EE,LV,LT,PL,D); non DOS*/
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_NBSP,   C_Rquote, C_cent,   C_Pound,  C_Rouble, C_Yenna,  C_Dvertl, C_Para,
  C_O_Slash,C_CO,     C_LBquote,C_Ldopang,C_Rminbr, C_hyph,   C_RO,     C_AE,
  C_deg,    C_PlMin,  C_2up,    C_3up, C_LAapost /*C_prim */,C_micro, C_Pren, C_Lpoint,
  C_o_Slash,C_1up,    C_LAquote,C_Rdopang,C_Quart,  C_Half,   C_34,     C_ae,
  C_I_Ogon, C_E_Adot, C_A_Macr, C_C_Acute,C_A_Diaer,C_A_Ring, C_A_Ogon, C_C_Car,
  C_G_Bcomma,C_E_Acute,C_Z_Car, C_E_Ogon, C_E_Macr, C_K_Bcomma,C_I_Macr,C_L_Bcomma,
  C_L_Slash,C_N_Bcomma,C_N_Acute,C_O_Acute,C_O_Macr,C_O_Tilde,C_O_Diaer,C_Multipl,
  C_U_Ogon, C_S_Car,  C_S_Acute,C_U_Macr, C_U_Diaer,C_Z_Adot, C_Z_Acute,C_ss,
  C_i_Ogon, C_e_Adot, C_a_Macr, C_c_Acute,C_a_Diaer,C_a_Ring, C_a_Ogon, C_c_Car,
C_g_Bcomma/*C_g_Tacom*/,C_e_Acute,C_z_Car,  C_e_Ogon, C_e_Macr, C_k_Bcomma,C_i_Macr,C_l_Bcomma,
  C_l_Slash,C_n_Bcomma,C_n_Acute,C_o_Acute,C_o_Macr,C_o_Tilde,C_o_Diaer,C_Divide,
  C_u_Ogon, C_s_Car,  C_s_Acute,C_u_Macr, C_u_Diaer,C_z_Adot, C_z_Acute,C_k_Cyr
  };

KpChar Ct46h[Ctbsiz/2]={   /*  IBM-773 (IBM-Kbl, IBM-771?) Lithuanian, without cyrillic  */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_a_Diaer,C_a_Grave,C_a_Ring, C_c_Cedil,
  C_e_Circ, C_e_Diaer,C_e_Grave,C_i_Diaer,C_i_Circ, C_i_Grave_Dotless,C_A_Diaer,C_A_Ring,
  C_E_Acute,C_ae,     C_Unkn /* C_AE - neveikia AKLZ Minion ðrifte */,
                                          C_o_Circ, C_o_Diaer,C_o_Grave,C_u_Circ, C_u_Grave,
  C_y_Diaer,C_O_Diaer,C_U_Diaer,C_cent,   C_Pound,  C_Yenna,  C_Unkn,   C_fun,
  C_a_Acute,C_i_Acute_Dotless,C_o_Acute,C_u_Acute,C_n_Tilde,C_N_Tilde,C_a_up,   C_o_up,
  C_Qst_Ov, C_Lminbr, C_Unkn /* C_Rminbr - neveikia AKLZ Minion ðrifte */,
                                C_Half,   C_Quart,  C_Ex_Ov,  C_Unkn /* C_Ldopang */, C_Unkn /* C_Rdopang */,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_A_Ogon, C_a_Ogon, C_C_Car,  C_c_Car,
  C_alpha,  C_beta,   C_Gamma,  C_pi,     C_Sigma,  C_sigma,  C_my,     C_tau,
  C_Phi,    C_Theta,  C_Omega,  C_delta,  C_infty,  C_phi /* C_empty */, C_epsilon_var /* C_in */, C_cap,
  C_E_Ogon, C_e_Ogon, C_E_Adot, C_e_Adot, C_I_Ogon, C_i_Ogon, C_S_Car,  C_s_Car,
  C_U_Ogon, C_u_Ogon, C_U_Macr, C_u_Macr, C_Z_Car,  C_z_Car,  C_box,    C_NBSP
  };

KpChar Ct47l[Ctbsiz/2]={   /*  ISO-646, IRV version, only sp. chars, without latin */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct47h[Ctbsiz/2]={   /*  IBM-855 (IBM-866, IBM Cyr)  */
  C_A_Cyr,  C_B_Cyr,  C_V_Cyr,  C_G_Cyr,  C_D_Cyr,  C_E_Cyr,  C_Zh_Cyr, C_Z_Cyr,
  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,  C_P_Cyr,
  C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_F_Cyr,  C_H_Cyr,  C_C_Cyr,  C_Ch_Cyr,
  C_Sh_Cyr, C_Shch_Cyr,C_Hard_Cyr,C_Y_Cyr,C_Soft_Cyr,C_Ee_Cyr,C_Yu_Cyr, C_Ya_Cyr,
  C_a_Cyr,  C_b_Cyr,  C_v_Cyr,  C_g_Cyr,  C_d_Cyr,  C_e_Cyr,  C_zh_Cyr, C_z_Cyr,
  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_f_Cyr,  C_h_Cyr,  C_c_Cyr,  C_ch_Cyr,
  C_sh_Cyr, C_shch_Cyr,C_hard_Cyr,C_y_Cyr,C_soft_Cyr,C_ee_Cyr,C_yu_Cyr, C_ya_Cyr,
  C_E_Cyr_Diaer,C_e_Cyr_Diaer,C_Unkn,C_Unkn,C_Unkn, C_Unkn,   C_rightarr,C_leftarr,
  C_downarr,C_uparr,  C_Divide, C_PlMin,  C_Unkn,   C_Rouble, C_box,    C_NBSP
  };

KpChar Ct49l[Ctbsiz/2]={   /*  ISO-646 + Polish (T.Szeibak) */
  C_Nul,    C_C_Acute,C_c_Acute,C_L_Slash,C_l_Slash,C_N_Acute,C_n_Acute,C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_O_Acute,C_o_Acute,C_Cr,     C_S_Acute,C_s_Acute,
  C_Dle,    C_Dc1,    C_Dc2,    C_Z_Acute,C_z_Acute,C_Z_Adot, C_z_Adot, C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct50h[Ctbsiz/2]={   /* DOS Lithuanian accented, based on IBM-Kbl */
  C_A_Acute,C_u_Diaer,C_e_Acute,C_a_Grave,C_a_Diaer,C_e_Tilde,C_a_Tilde,C_a_Acute,
  C_u_Grave,C_a_Ogon_Acute,C_E_Adot_Tilde,C_e_Adot_Tilde,C_i_Acute,C_E_Grave,C_A_Diaer,C_A_Tilde,
  C_E_Acute,C_u_Macr_Acute,C_U_Macr_Acute,C_y_Acute,C_o_Diaer,C_E_Tilde,C_E_Ogon_Acute, C_U_Acute,
  C_u_Acute,C_O_Diaer,C_U_Diaer,C_e_Adot_Acute,C_E_Ogon_Tilde,C_E_Adot_Acute,C_U_Tilde,C_i_Tilde,
  C_A_Grave,C_I_Acute,C_o_Acute,C_Y_Tilde,C_y_Tilde,C_e_Grave,C_L_Tilde,C_M_Tilde,
  C_N_Tilde,C_U_Macr_Tilde,C_U_Ogon_Acute,C_U_Ogon_Tilde,C_u_Ogon_Acute,C_U_Grave,C_R_Tilde,C_r_Tilde,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_ph_a,   C_a_Ogon_Tilde,C_ph_a_sh,C_Rquote,
  C_u_Macr_Tilde,C_ph_o_sh,C_2v_b,C_2d2l_b,C_2u2l_b,C_A_Ogon_Tilde,C_m_Tilde,C_dl_b,
  C_ur_b,   C_ph_e_inv,C_ph_e_sh_inv,C_ph_g,C_h_b,  C_ph_i_sh,C_u_Tilde,C_ph_zh,
  C_2u2r_b, C_2d2r_b, C_ph_ng,  C_ph_th_b,C_ph_sh,  C_2h_b,   C_ph_uu_sh,C_ph_acc,
  C_I_Tilde,C_ph_acc_low,C_ph_ae,C_ph_th_v,C_n_Tilde,C_LBquote,C_e_Ogon_Tilde,C_hyph,
  C_e_Ogon_Acute,C_ul_b,C_dr_b, C_block,  C_A_Ogon, C_a_Ogon, C_C_Car,  C_c_Car,
  C_O_Acute,C_ss,     C_Y_Acute,C_I_Ogon_Tilde,C_o_Tilde,C_O_Tilde,C_l_Tilde,C_i_Ogon_Tilde,
  C_I_Grave,C_i_Grave,C_I_Ogon_Acute,C_i_Ogon_Acute,C_o_Grave,C_A_Ogon_Acute,C_O_Grave,C_u_Ogon_Tilde,
  C_E_Ogon, C_e_Ogon, C_E_Adot, C_e_Adot, C_I_Ogon, C_i_Ogon, C_S_Car,  C_s_Car,
  C_U_Ogon, C_u_Ogon, C_U_Macr, C_u_Macr, C_Z_Car,  C_z_Car,  C_box,    C_NBSP
  };

KpChar Ct52h[Ctbsiz/2]={   /*  ISO-K, Iskra-10.30 (Rus.) */
  C_2hu_b,  C_h2u_b,  C_2hd_b,  C_v2l_b,  C_2vl_b,  C_2dl_b,  C_d2l_b,  C_h2d_b,
  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2ul_b,  C_u2l_b,  C_v2r_b,  C_2vr_b,  C_2dr_b,
  C_2d2r_b, C_2d2l_b, C_2u2l_b, C_2u2r_b, C_2h_b,   C_2v_b,   C_2h2d_b, C_2v2l_b,
  C_2h2u_b, C_2v2r_b, C_2v2h_b, C_lgrblk, C_grblk,  C_dgrblk, C_2vh_b,  C_v2h_b,
  C_dr_b,   C_dl_b,   C_ul_b,   C_ur_b,   C_h_b,    C_v_b,    C_hd_b,   C_vl_b,
  C_hu_b,   C_vr_b,   C_vh_b,   C_block,  C_dnhblk, C_lthblk, C_rthblk, C_uphblk,
  C_A_Cyr,  C_B_Cyr,  C_V_Cyr,  C_G_Cyr,  C_D_Cyr,  C_E_Cyr,  C_Zh_Cyr, C_Z_Cyr,
  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,  C_P_Cyr,
  C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_F_Cyr,  C_H_Cyr,  C_C_Cyr,  C_Ch_Cyr,
  C_Sh_Cyr, C_Shch_Cyr,C_Hard_Cyr,C_Y_Cyr,C_Soft_Cyr,C_Ee_Cyr,C_Yu_Cyr, C_Ya_Cyr,
  C_a_Cyr,  C_b_Cyr,  C_v_Cyr,  C_g_Cyr,  C_d_Cyr,  C_e_Cyr,  C_zh_Cyr, C_z_Cyr,
  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_f_Cyr,  C_h_Cyr,  C_c_Cyr,  C_ch_Cyr,
  C_sh_Cyr, C_shch_Cyr,C_hard_Cyr,C_y_Cyr,C_soft_Cyr,C_ee_Cyr,C_yu_Cyr, C_ya_Cyr,
  C_E_Cyr_Diaer,C_e_Cyr_Diaer,C_Unkn,C_Unkn,C_Unkn, C_Unkn,   C_rightarr,C_leftarr,
  C_downarr,C_uparr,  C_Divide, C_PlMin,  C_Unkn,   C_Rouble, C_box,    C_NBSP
  };

KpChar Ct53l[Ctbsiz/2]={   /*  IBM-437 apatine dalis be keliu simboliu TEX-ui */
  C_Nul,    C_Unkn,   C_Unkn,   C_Heart,  C_Diamond,C_Club,   C_Spade,  C_Bpoint,
  C_Unkn,C_Ht/*C_BigRing*/,C_Lf/*C_Unkn*/,C_Vt/*C_male*/,C_Ff/*C_female*/,C_Cr/*C_Unkn*/,C_Unkn,C_Unkn,
  C_rtrif,  C_ltrif,C_updownarr,C_Unkn,C_Unkn/*C_Pren*/,C_Para,C_Unkn,  C_Unkn,
  C_uparr, C_downarr,Eof/*C_rightarr*/,C_leftarr,C_Unkn/*C_Lminbr*/,C_leftrightarr,C_utrif,C_dtrif,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct53h[Ctbsiz/2]={   /*  IBM-773 (IBM-Kbl) Lithuanian (IBM-855 pagrindu) be keliu rusisku raidziu TEVo TEX-ui, padaryta is 43 */
  C_A_Cyr,  C_B_Cyr,  C_V_Cyr,  C_G_Cyr,  C_D_Cyr,  C_E_Cyr,  C_Zh_Cyr, C_Z_Cyr,
  C_I_Cyr,C_Noch/*C_J_Cyr*/,C_K_Cyr,C_L_Cyr,C_M_Cyr,C_N_Cyr,  C_O_Cyr,  C_P_Cyr,
  C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_F_Cyr,C_Noch/*C_H_Cyr*/,C_C_Cyr,C_Ch_Cyr,
  C_Sh_Cyr, C_Shch_Cyr,C_Noch/*C_Hard_Cyr*/,C_Y_Cyr,C_Noch/*C_Soft_Cyr*/,C_Noch/*C_Ee_Cyr*/,C_Yu_Cyr, C_Ya_Cyr,
  C_a_Cyr,  C_b_Cyr,  C_v_Cyr,  C_g_Cyr,  C_d_Cyr,  C_e_Cyr,  C_zh_Cyr, C_z_Cyr,
  C_i_Cyr,C_Noch/*C_j_Cyr*/,C_k_Cyr,C_l_Cyr,C_m_Cyr,C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_A_Ogon, C_a_Ogon, C_C_Car,  C_c_Car,
  C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_f_Cyr,C_Noch/*C_h_Cyr*/,C_c_Cyr,C_ch_Cyr,
  C_sh_Cyr, C_shch_Cyr,C_Noch/*C_hard_Cyr*/,C_y_Cyr,C_Noch/*C_soft_Cyr*/,C_Noch/*C_ee_Cyr*/,C_yu_Cyr, C_ya_Cyr,
  C_E_Ogon, C_e_Ogon, C_E_Adot, C_e_Adot, C_I_Ogon, C_i_Ogon, C_S_Car,  C_s_Car,
  C_U_Ogon, C_u_Ogon, C_U_Macr, C_u_Macr, C_Z_Car,  C_z_Car,  C_box,    C_Noch /* C_NBSP */
  };

KpChar Ct54h[Ctbsiz/2]={   /*  IBM-773 (IBM-Kbl, IBM-771?) Lithuanian, without cyrillic, be keliu raidziu TEVo TEX-ui, padaryta is 46 */
  C_C_Cedil,C_u_Diaer,C_e_Acute,C_a_Circ, C_a_Diaer,C_a_Grave,C_a_Ring, C_c_Cedil,
  C_Noch/*C_e_Circ*/,C_Noch/*C_e_Diaer*/,C_e_Grave,C_i_Diaer,C_i_Circ, C_i_Grave_Dotless,C_A_Diaer,C_A_Ring,
  C_E_Acute,C_ae,     C_AE,     C_o_Circ, C_o_Diaer,C_o_Grave,C_u_Circ, C_u_Grave,
  C_y_Diaer,C_O_Diaer,C_U_Diaer,C_cent,   C_Pound,  C_Yenna,  C_Unkn,   C_fun,
  C_a_Acute,C_i_Acute_Dotless,C_o_Acute,C_u_Acute,C_n_Tilde,C_N_Tilde,C_a_up,   C_o_up,
  C_Qst_Ov, C_Lminbr, C_Rminbr, C_Half,   C_Quart,  C_Ex_Ov,C_Noch/*C_Ldopang*/,C_Noch/*C_Rdopang*/,
  C_lgrblk, C_grblk,  C_dgrblk, C_v_b,    C_vl_b,   C_v2l_b,  C_2vl_b,  C_2dl_b,
  C_d2l_b,  C_2v2l_b, C_2v_b,   C_2d2l_b, C_2u2l_b, C_2ul_b,  C_u2l_b,  C_dl_b,
  C_ur_b,   C_hu_b,   C_hd_b,   C_vr_b,   C_h_b,    C_vh_b,   C_v2r_b,  C_2vr_b,
  C_2u2r_b, C_2d2r_b, C_2h2u_b, C_2h2d_b, C_2v2r_b, C_2h_b,   C_2v2h_b, C_2hu_b,
  C_h2u_b,  C_2hd_b,  C_h2d_b,  C_2ur_b,  C_u2r_b,  C_d2r_b,  C_2dr_b,  C_2vh_b,
  C_v2h_b,  C_ul_b,   C_dr_b,   C_block,  C_A_Ogon, C_a_Ogon, C_C_Car,  C_c_Car,
C_Noch/*C_alpha*/,C_beta,C_Gamma,C_pi,    C_Sigma,  C_sigma,  C_my,     C_tau,
  C_Phi,    C_Theta,  C_Omega,  C_delta,  C_infty,  C_phi /* C_empty */, C_epsilon_var /* C_in */, C_cap,
  C_E_Ogon, C_e_Ogon, C_E_Adot, C_e_Adot, C_I_Ogon, C_i_Ogon, C_S_Car,  C_s_Car,
  C_U_Ogon, C_u_Ogon, C_U_Macr, C_u_Macr, C_Z_Car,  C_z_Car,  C_box,    C_NBSP
  };

KpChar Ct61l[Ctbsiz/2]={   /*  DKOI (EBCDIC) */
  C_Nul,    C_Soh,    C_Stx,    C_Sub,    C_Unkn,   C_Ht,     C_Unkn,   C_Del,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Vt,     C_Ff,     C_Unkn,   C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Unkn,   C_Unkn,   C_Cr,     C_Bs,     C_Unkn,
  C_Can,    C_Em,     C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Fs,     C_Noch,   C_Unkn,   C_Lf,     C_Unkn,   C_Esc,
  C_Noch,   C_Noch,   C_Unkn,   C_Unkn,   C_Noch,   C_Enq,    C_Ack,    C_Bel,
  C_Noch,   C_Noch,   C_Unkn,   C_Noch,   C_Unkn,   C_Rs,     C_Unkn,   C_Eot,
  C_Noch,   C_Noch,   C_Noch,   C_Unkn,   C_Dc4,    C_Nak,    C_Noch,   C_Sub,
  C_Spc,    C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Lbrack, C_Point,  C_Less,   C_Lpar,   C_Plus,   C_Excl,
  C_Amp,    C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Rbrack, C_Rouble, C_Ast,    C_Rpar,   C_Semic,  C_Rminbr,
  C_Dash,  C_Slash,  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Vertl,  C_Comma,  C_Perc,   C_Underl, C_Great,  C_Quest,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_yu_Cyr, C_a_Cyr,
  C_b_Cyr,  C_Grave,  C_Colon,  C_Numb,   C_At,     C_Apost,  C_Eq,     C_Quote
  };

KpChar Ct61h[Ctbsiz/2]={   /*  DKOI (EBCDIC) */
  C_c_Cyr,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_d_Cyr,  C_e_Cyr,  C_f_Cyr,  C_g_Cyr,  C_h_Cyr,  C_i_Cyr,
  C_j_Cyr,  C_j,      C_k,      C_l,      C_m,      C_n,      C_o,      C_p,
  C_q,      C_r,      C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_ya_Cyr, C_Tilde,  C_s,      C_t,      C_u,      C_v,      C_w,      C_x,
  C_y,      C_z,      C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_zh_Cyr, C_v_Cyr,
  C_soft_Cyr,C_y_Cyr, C_z_Cyr,  C_sh_Cyr, C_ee_Cyr, C_shch_Cyr,C_ch_Cyr,C_hard_Cyr,
  C_Yu_Cyr, C_A_Cyr,  C_B_Cyr,  C_C_Cyr,  C_D_Cyr,  C_E_Cyr,  C_F_Cyr,  C_G_Cyr,
  C_Lcurl,  C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_H_Cyr,  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,
  C_Rcurl,  C_J,      C_K,      C_L,      C_M,      C_N,      C_O,      C_P,
  C_Q,      C_R,      C_N_Cyr,  C_O_Cyr,  C_P_Cyr,  C_Ya_Cyr, C_R_Cyr,  C_S_Cyr,
  C_Lslash, C_Noch,   C_S,      C_T,      C_U,      C_V,      C_W,      C_X,
  C_Y,      C_Z,      C_T_Cyr,  C_U_Cyr,  C_Zh_Cyr, C_V_Cyr,  C_Soft_Cyr,C_Y_Cyr,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Z_Cyr,  C_Sh_Cyr, C_Ee_Cyr, C_Shch_Cyr,C_Ch_Cyr,C_Unkn
  };

KpChar Ct71h[Ctbsiz/2]={   /*  MS Windows-1257, MS Windows Baltic, ISO-8859-13, Baltic-RIM, LT, LST 1282-93, MS-Windows liet. stand. */
  C_euro,   C_Noch,   C_LBapost,C_fun,    C_LBquote,C_Dots,   C_Dag,    C_Ddag,
  C_Noch,   C_Prom,   C_Noch,   C_Lang,   C_Noch,C_DiaerNcomb/*!!!*/,C_CarNcomb/*!!!*/,C_CedilNcomb/*!!!*/,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote,C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_Noch,   C_TM,     C_Noch,   C_Rang,   C_Noch,   C_Macr,C_OgonNcomb/*!!!*/,C_Noch,
  C_NBSP,   C_LAquote,C_cent,   C_Pound,  C_Rouble, C_LBquote,C_Dvertl, C_Para,
  C_O_Slash,C_CO,     C_R_Bcomma,C_Ldopang,C_Rminbr,C_hyph/*!!!*/,C_RO, C_AE, // C_hyph - LZDSH_TECH_DELIM
  C_deg,    C_PlMin,  C_2up,    C_3up,C_AcuteNcomb/*C_Acute C_prim*/,C_micro,C_Pren, C_Lpoint,
  C_o_Slash,C_1up,    C_r_Bcomma,C_Rdopang,C_Quart, C_Half,   C_34,     C_ae,
  C_A_Ogon, C_I_Ogon, C_A_Macr, C_C_Acute,C_A_Diaer,C_A_Ring, C_E_Ogon, C_E_Macr,
  C_C_Car,  C_E_Acute,C_Z_Acute,C_E_Adot, C_G_Bcomma,C_K_Bcomma,C_I_Macr,C_L_Bcomma,
  C_S_Car,  C_N_Acute,C_N_Bcomma,C_O_Acute,C_O_Macr,C_O_Tilde,C_O_Diaer,C_Multipl,
  C_U_Ogon, C_L_Slash,C_S_Acute,C_U_Macr, C_U_Diaer,C_Z_Adot, C_Z_Car,  C_ss,
  C_a_Ogon, C_i_Ogon, C_a_Macr, C_c_Acute,C_a_Diaer,C_a_Ring, C_e_Ogon, C_e_Macr,
  C_c_Car,  C_e_Acute,C_z_Acute,C_e_Adot,C_g_Bcomma/*C_g_Tacom*/,C_k_Bcomma,C_i_Macr,C_l_Bcomma,
  C_s_Car,  C_n_Acute,C_n_Bcomma,C_o_Acute,C_o_Macr,C_o_Tilde,C_o_Diaer,C_Divide,
  C_u_Ogon, C_l_Slash,C_s_Acute,C_u_Macr, C_u_Diaer,C_z_Adot, C_z_Car,  C_LAapost
  };

KpChar Ct72h[Ctbsiz/2]={   /*  MS Windows SC  */
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_LAapost,C_Rapost, C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_NBSP,   C_Ex_Ov,  C_cent,   C_Pound,  C_Rouble, C_Yenna,  C_Dvertl, C_Para,
  C_Rquote, C_CO,     C_a_up,   C_Ldopang,C_Rminbr,C_hyph/*!!!*/,C_RO,  C_Macr,
  C_deg,    C_PlMin,  C_2up,    C_3up,    C_prim,   C_micro,  C_Pren,   C_Lpoint,
  C_Cedil,  C_1up,    C_o_up,   C_Rdopang,C_Quart,  C_Half,   C_34,     C_Qst_Ov,
  C_A_Ogon, C_A_Acute,C_A_Circ, C_A_Tilde,C_A_Diaer,C_A_Ring, C_C_Car,  C_C_Cedil,
  C_E_Ogon, C_E_Adot, C_E_Circ, C_E_Diaer,C_I_Ogon, C_I_Acute,C_I_Circ, C_I_Diaer,
  C_D_Dash,C_N_Tilde,C_O_Grave,C_O_Acute,C_O_Circ, C_O_Tilde,C_S_Car,  C_Multipl,
  C_O_Slash,C_U_Ogon, C_U_Macr, C_Z_Car,  C_U_Diaer,C_Y_Acute,C_P_Dash,C_ss,
  C_a_Ogon, C_a_Acute,C_a_Circ, C_a_Tilde,C_a_Diaer,C_a_Ring, C_c_Car,  C_c_Cedil,
  C_e_Ogon, C_e_Adot, C_e_Circ, C_e_Diaer,C_i_Ogon, C_i_Acute_Dotless,C_i_Circ, C_i_Diaer,
  C_delta_Dash,C_n_Tilde,C_o_Grave,C_o_Acute,C_o_Circ, C_o_Tilde,C_s_Car,  C_Divide,
  C_o_Slash,C_u_Ogon, C_u_Macr, C_z_Car,  C_u_Diaer,C_y_Acute,C_p_Dash,C_y_Diaer
  };

KpChar Ct73h[Ctbsiz/2]={   /*  MS Windows-1251, MS Windows Cyrillic upper part (without spec. chars) */
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_LBquote,C_Dots,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_LAquote,C_Rquote, C_Bpoint, C_EnDash,C_EmDash,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_E_Cyr_Diaer,C_Unkn,C_Unkn,  C_Ldopang,C_Unkn,C_hyph/*C_Unkn*/,C_Unkn,C_Unkn, // C_hyph - LZDSH_TECH_DELIM
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_e_Cyr_Diaer,C_Unkn,C_Unkn,  C_Rdopang,C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_A_Cyr,  C_B_Cyr,  C_V_Cyr,  C_G_Cyr,  C_D_Cyr,  C_E_Cyr,  C_Zh_Cyr, C_Z_Cyr,
  C_I_Cyr,  C_J_Cyr,  C_K_Cyr,  C_L_Cyr,  C_M_Cyr,  C_N_Cyr,  C_O_Cyr,  C_P_Cyr,
  C_R_Cyr,  C_S_Cyr,  C_T_Cyr,  C_U_Cyr,  C_F_Cyr,  C_H_Cyr,  C_C_Cyr,  C_Ch_Cyr,
  C_Sh_Cyr, C_Shch_Cyr,C_Hard_Cyr,C_Y_Cyr,C_Soft_Cyr,C_Ee_Cyr,C_Yu_Cyr, C_Ya_Cyr,
  C_a_Cyr,  C_b_Cyr,  C_v_Cyr,  C_g_Cyr,  C_d_Cyr,  C_e_Cyr,  C_zh_Cyr, C_z_Cyr,
  C_i_Cyr,  C_j_Cyr,  C_k_Cyr,  C_l_Cyr,  C_m_Cyr,  C_n_Cyr,  C_o_Cyr,  C_p_Cyr,
  C_r_Cyr,  C_s_Cyr,  C_t_Cyr,  C_u_Cyr,  C_f_Cyr,  C_h_Cyr,  C_c_Cyr,  C_ch_Cyr,
  C_sh_Cyr, C_shch_Cyr,C_hard_Cyr,C_y_Cyr,C_soft_Cyr,C_ee_Cyr,C_yu_Cyr, C_ya_Cyr,
  };

KpChar Ct74h[Ctbsiz/2]={   /*  ISO Latin 1 (ECMA Latin 1, MS Windows-1252 ANSI, ISO-8859-1) */
  C_euro,   C_Noch,   C_LBapost,C_fun,    C_LBquote,C_Dots,   C_Dag,    C_Ddag,
  C_Circ,   C_Prom,   C_S_Car,  C_Lang,   C_OE,     C_Noch,C_Z_Car/*!!!C_Noch*/,C_Noch,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote, C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_Tilde,  C_TM,     C_s_Car,  C_Rang,   C_oe,     C_Noch,C_z_Car/*!!!C_Noch*/,C_Y_Diaer,
  C_NBSP,   C_Ex_Ov,  C_cent,   C_Pound,  C_Rouble, C_Yenna,  C_Dvertl, C_Para,
  C_Diaer,  C_CO,     C_a_up,   C_Ldopang,C_Rminbr, C_hyph,   C_RO,     C_Macr,
  C_deg,    C_PlMin,  C_2up,    C_3up,    C_prim,   C_micro,  C_Pren,   C_Lpoint,
  C_Cedil,  C_1up,    C_o_up,   C_Rdopang,C_Quart,  C_Half,   C_34,     C_Qst_Ov,
  C_A_Grave,C_A_Acute,C_A_Circ, C_A_Tilde,C_A_Diaer,C_A_Ring, C_AE,     C_C_Cedil,
  C_E_Grave,C_E_Acute,C_E_Circ, C_E_Diaer,C_I_Grave,C_I_Acute,C_I_Circ, C_I_Diaer,
  C_D_Dash,C_N_Tilde,C_O_Grave,C_O_Acute,C_O_Circ, C_O_Tilde,C_O_Diaer,C_Multipl,
  C_O_Slash,C_U_Grave,C_U_Acute,C_U_Circ, C_U_Diaer,C_Y_Acute,C_P_Dash,C_ss,
  C_a_Grave,C_a_Acute,C_a_Circ, C_a_Tilde,C_a_Diaer,C_a_Ring, C_ae,     C_c_Cedil,
  C_e_Grave,C_e_Acute,C_e_Circ, C_e_Diaer,C_i_Grave_Dotless,C_i_Acute_Dotless,C_i_Circ, C_i_Diaer,
  C_d_Dash,C_n_Tilde,C_o_Grave,C_o_Acute,C_o_Circ, C_o_Tilde,C_o_Diaer,C_Divide,
  C_o_Slash,C_u_Grave,C_u_Acute,C_u_Circ, C_u_Diaer,C_y_Acute,C_p_Dash,C_y_Diaer
  };

KpChar Ct75l[Ctbsiz/2]={   /*  MS Windows Symbol Font, lower part, for TEX formula fields */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Each,   C_Numb,   C_Exists, C_Perc,   C_Amp,    C_ni,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At /* reikia del Unimarc su Tex - formuliu pabaigos simbolis, siaip C_cong */,
            C_Alpha,  C_Beta,   C_Chi,    C_Delta,  C_Epsilon,C_Phi,    C_Gamma,
  C_Eta,    C_Jota, C_theta_var,C_Kappa,  C_Lambda, C_My,     C_Ny,     C_Omicron,
  C_Pi,     C_Theta,  C_Rho,    C_Sigma,  C_Tau,    C_Ypsilon,C_sigma_var,C_Omega,
  C_Xi,     C_Psi,    C_Zeta,   C_Lbrack, C_Unkn,   C_Rbrack, C_perp,   C_Underl,
  C_Unkn,   C_alpha,  C_beta,   C_chi,    C_delta,  C_epsilon,C_phi,    C_gamma,
  C_eta,    C_jota,  C_phi_var, C_kappa,  C_lambda, C_my,     C_ny,     C_omicron,
  C_pi,     C_theta,  C_rho,    C_sigma,  C_tau,    C_ypsilon,C_pi_var, C_omega,
  C_xi,     C_psi,    C_zeta,   C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Noch
  };

KpChar Ct75h[Ctbsiz/2]={   /*  MS Windows Symbol Font, upper part */
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Unkn,   C_prim,   C_le,     C_Unkn,   C_infty,  C_fun,    C_Club,
  C_Diamond,C_Heart,C_Spade,C_leftrightarr,C_leftarr,C_uparr,C_rightarr,C_downarr,
  C_deg,    C_PlMin,  C_dprim,  C_ge,     C_Multipl,C_propto, C_part,   C_Bpoint,
  C_Divide, C_ne,     C_equiv,  C_approx, C_Dots,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Aleph,  C_Im,     C_Re,     C_wp,     C_O_times,C_O_plus, C_empty,  C_cap,
  C_cup,    C_supset, C_supseteq,C_nsubset,C_subset,C_subseteq,C_in,    C_notin,
  C_angle,C_nabla,C_RO/*times*/,C_CO/*times*/,C_TM/*times*/,C_Prod,C_sqrt,C_Lpoint,
  C_Rminbr,C_wedge,C_vee,C_Leftrightarr,C_Leftarr,  C_Uparr, C_Rightarr,C_Downarr,
  C_diamond,C_langle,C_RO/*helv*/,C_CO/*helv*/,C_TM/*helv*/,C_Sum,C_Unkn,C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_rangle, C_int,    C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn
  };

KpChar Ct76h[Ctbsiz/2]={   /*  Baltic-RIM, RTF */
  C_euro,   C_Noch,   C_LBapost,C_fun,    C_LBquote,C_Dots,   C_Dag,    C_Ddag,
  C_Noch,   C_Prom,   C_S_Car,  C_Lang,   C_Noch,   C_Noch,   C_Z_Car,  C_Noch,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote, C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_Noch,   C_TM,     C_s_Car,  C_Rang,   C_Noch,   C_Noch,   C_z_Car,  C_Noch,
  C_NBSP,   C_LAquote,C_cent,   C_Pound,  C_Rouble, C_LBquote,C_Dvertl, C_Para,
  C_O_Slash,C_CO,     C_R_Bcomma,C_Ldopang,C_Rminbr,C_hyph/*!!!*/,C_RO, C_AE,
  C_deg,    C_PlMin,  C_2up,    C_3up,    C_prim,   C_micro,  C_Pren,   C_Lpoint,
  C_o_Slash,C_1up,    C_r_Bcomma,C_Rdopang,C_Quart, C_Half,   C_34,     C_ae,
  C_A_Ogon, C_I_Ogon, C_A_Macr, C_C_Acute,C_A_Diaer,C_A_Ring, C_E_Ogon, C_E_Macr,
  C_C_Car,  C_E_Acute,C_Z_Acute,C_E_Adot,C_G_Bcomma,C_K_Bcomma,C_I_Macr,C_L_Bcomma,
  C_S_Car,  C_N_Acute,C_N_Bcomma,C_O_Acute,C_O_Macr,C_O_Tilde,C_O_Diaer,C_Multipl,
  C_U_Ogon, C_L_Slash,C_S_Acute,C_U_Macr, C_U_Diaer,C_Z_Adot, C_Z_Car,  C_ss,
  C_a_Ogon, C_i_Ogon, C_a_Macr, C_c_Acute,C_a_Diaer,C_a_Ring, C_e_Ogon, C_e_Macr,
  C_c_Car,  C_e_Acute,C_z_Acute,C_e_Adot,C_g_Bcomma/*C_g_Tacom*/,C_k_Bcomma,C_i_Macr,C_l_Bcomma,
  C_s_Car,  C_n_Acute,C_n_Bcomma,C_o_Acute,C_o_Macr,C_o_Tilde,C_o_Diaer,C_Divide,
  C_u_Ogon, C_l_Slash,C_s_Acute,C_u_Macr, C_u_Diaer,C_z_Adot, C_z_Car,  C_LAapost
  };

KpChar Ct77l[Ctbsiz/2]={   /*  MS Windows 1251, MS Windows Cyrillic lower part (without latin and spec. chars) */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote, C_Unkn/*C_Numb*/,C_Unkn/*C_Rouble*/,C_Perc,C_Unkn/*C_Amp*/,C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic, C_Unkn /*C_Less*/, C_Eq, C_Unkn /*C_Great*/, C_Quest,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn/*C_Circ*/,C_Unkn/*C_Underl*/,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn/*C_Tilde*/,C_Unkn
  };

#if 0
KpChar Ct77l[Ctbsiz/2]={   /*  MS Windows Cyrillic lower part with spec. chars */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At,     C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };
#endif

KpChar Ct78h[Ctbsiz/2]={   /*  MS Windows-1253 Greek CharSet */
  C_euro,   C_Noch,   C_LBapost,C_fun,    C_LBquote,C_Dots,   C_Dag,    C_Ddag,
  C_CircAcc,C_Prom,   C_S_Car,  C_Lang,   C_OE,     C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote, C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_TildeAcc,C_TM,    C_s_Car,  C_Rang,   C_oe,     C_Noch,   C_Noch,   C_Y_Diaer,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Pound,  C_Rouble, C_Yenna,  C_Dvertl, C_Para,
  C_Diaer,  C_CO,     C_a_up,   C_Ldopang,C_Rminbr, C_hyph/*!!!*/,C_RO, C_Noch,
  C_deg,    C_PlMin,  C_2up,    C_3up,    C_prim,   C_micro,  C_Pren,C_Lpoint,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Rdopang,C_Unkn,   C_Half,   C_Unkn,   C_Unkn,

  C_Unkn,   C_Alpha,  C_Beta,   C_Gamma,  C_Delta,  C_Epsilon,C_Zeta,   C_Eta,
  C_Theta,  C_Jota,   C_Kappa,  C_Lambda, C_My,     C_Ny,     C_Xi,     C_Omicron,
  C_Pi,     C_Rho,    C_Noch,   C_Sigma,  C_Tau,    C_Ypsilon,C_Phi,    C_Chi,
  C_Psi,    C_Omega,  C_I_Diaer,C_Y_Diaer,C_Unkn/*C_alpha_Acute*/,C_Unkn/*C_epsilon_Acute*/,C_Unkn/*C_eta_Acute*/,C_Unkn/*C_jota_Acute*/,

  C_Unkn,   C_alpha,  C_beta,   C_gamma,  C_delta,  C_epsilon,C_zeta,   C_eta,
  C_theta,  C_jota,   C_kappa,  C_lambda, C_my,     C_ny,     C_xi,     C_omicron,
  C_pi,     C_rho,    C_sigma_var,C_sigma,C_tau,    C_ypsilon,C_phi,    C_chi,
  C_psi,    C_omega,  C_i_Diaer,C_u_Diaer,C_o_Acute,C_u_Acute,C_Unkn/*C_omega_Acute*/,C_Noch
  };

KpChar Ct79h[Ctbsiz/2]={   /*  MS Windows-1250 CE (ANSI-2, Central Europe) Win-1250 */
  C_euro,   C_Noch,   C_LBapost,C_fun,    C_LBquote,C_Dots,   C_Dag,    C_Ddag,
  C_Circ,   C_Prom,   C_S_Car,  C_Lang,   C_S_Acute,C_T_Car,  C_Z_Car,  C_Z_Acute,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote, C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_Tilde,  C_TM,     C_s_Car,  C_Rang,   C_s_Acute,C_Unkn/*C_t_Acomma*/,C_z_Car,  C_z_Acute,
  C_NBSP,   C_Car,    C_BreveAcc,C_L_Slash,C_Rouble,C_A_Ogon, C_Dvertl, C_Para,
  C_Diaer,  C_CO,     C_S_Cedil,C_Ldopang,C_Rminbr, C_hyph,   C_RO,     C_Z_Adot,
  C_deg,    C_PlMin,  C_Ogon,   C_l_Slash,C_AcuteNcomb,C_micro,C_Pren,  C_Lpoint,
  C_Cedil,  C_a_Ogon, C_s_Cedil,C_Rdopang,C_Unkn/*C_L_Acomma*/,C_Dacut,C_Unkn/*C_l_Acomma*/,C_z_Adot,
  C_R_Acute,C_A_Acute,C_A_Circ, C_Unkn/*C_A_Breve*/,C_A_Diaer,C_L_Acute,C_C_Acute,C_C_Cedil,
  C_C_Car,  C_E_Acute,C_E_Ogon, C_E_Diaer,C_E_Car,  C_I_Acute,C_I_Circ, C_D_Car,
  C_D_Dash,C_N_Acute,C_N_Car,  C_O_Acute,C_O_Circ, C_O_Dacut,C_O_Diaer,C_Multipl,
  C_R_Car,  C_U_Ring, C_U_Acute,C_U_Dacut,C_U_Diaer,C_Y_Acute,C_Unkn/*C_T_Bcomma*/,C_ss,
  C_r_Acute,C_a_Acute,C_a_Circ, C_Unkn/*C_a_Breve*/,C_a_Diaer,C_l_Acute,C_c_Acute,C_c_Cedil,
  C_c_Car,  C_e_Acute,C_e_Ogon, C_e_Diaer,C_e_Car,  C_i_Acute_Dotless,C_i_Circ, C_Unkn/*C_d_Acomma*/,
  C_d_Dash,C_n_Acute,C_n_Car,  C_o_Acute,C_o_Circ, C_o_Dacut,C_o_Diaer,C_Divide,
  C_r_Car,  C_u_Ring, C_u_Acute,C_u_Dacut,C_u_Diaer,C_y_Acute,C_Unkn/*C_t_Bcomma*/,C_Adot
  };

KpChar Ct80l[Ctbsiz/2]={   /*  MS Windows lithuanian accented charset + phonetic (), lower part */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_At /* buvo C_ph_oe? reikia C_At LVZG2T puslapio pabaigai */,
            C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct80h[Ctbsiz/2]={   /*  MS Windows lithuanian accented charset + phonetic () "TimesLT Accented" */
  C_euro,C_square/*???*/,C_ph_a,C_ph_o_sh,C_LBquote,C_ph_e_inv,C_ph_e_sh_inv,C_ph_g,
  C_ph_i_sh,C_ph_ng,  C_ph_th_b,C_ph_acc, C_ph_sh,  C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote, C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_ph_uu_sh,C_ph_a_sh,C_ph_zh, C_ph_acc_low,C_ph_ae,C_Noch,  C_Noch,   C_ph_th_v,
  C_NBSP,C_A_Ogon_Tilde,C_E_Ogon_Acute,C_E_Ogon_Tilde,C_i_Tilde,C_L_Tilde,C_M_Tilde,C_m_Tilde,
  C_E_Adot_Acute,C_N_Tilde,C_E_Adot_Tilde,C_R_Tilde,C_U_Ogon_Acute,C_hyph/*!!!*/,C_U_Macr_Tilde,C_U_Macr_Acute,
  C_I_Tilde,C_a_Ogon_Tilde,C_e_Ogon_Acute,C_e_Ogon_Tilde,C_AcuteNcomb,C_l_Tilde,C_Pren,C_Lpoint,
  C_e_Adot_Acute,C_n_Tilde,C_e_Adot_Tilde,C_r_Tilde,C_u_Ogon_Acute,C_U_Ogon_Tilde,C_u_Macr_Tilde,C_u_Macr_Acute,
  C_A_Ogon, C_I_Ogon, C_A_Grave,C_A_Acute,C_A_Diaer,C_A_Tilde,C_E_Ogon, C_A_Ogon_Acute,
  C_C_Car,  C_E_Acute,C_E_Grave,C_E_Adot, C_E_Tilde,C_I_Grave,C_I_Acute,C_I_Ogon_Acute,
  C_S_Car,C_I_Ogon_Tilde,C_O_Grave,C_O_Acute,C_Y_Acute,C_O_Tilde,C_O_Diaer,C_U_Tilde,
  C_U_Ogon, C_U_Grave,C_U_Acute,C_U_Macr, C_U_Diaer,C_Y_Tilde, C_Z_Car,  C_ss,
  C_a_Ogon, C_i_Ogon, C_a_Grave,C_a_Acute,C_a_Diaer,C_a_Tilde,C_e_Ogon, C_a_Ogon_Acute,
  C_c_Car,  C_e_Acute,C_e_Grave,C_e_Adot, C_e_Tilde,C_i_Grave,C_i_Acute,C_i_Ogon_Acute,
  C_s_Car,C_i_Ogon_Tilde,C_o_Grave,C_o_Acute,C_y_Acute,C_o_Tilde,C_o_Diaer,C_u_Tilde,
  C_u_Ogon, C_u_Grave,C_u_Acute,C_u_Macr, C_u_Diaer,C_y_Tilde, C_z_Car,  C_u_Ogon_Tilde
  };

KpChar Ct81l[Ctbsiz/2]={   /*  Phonetic basic charset + '<' and '>' for XML + '{', '\' and '}' for RTF "PhoneticTM" */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Noch,C_ph_acc_low,C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_ph_acc,
  C_Lpar,   C_Rpar,   C_Noch,   C_Noch,   C_Comma,  C_Dash,  C_Point,  C_Noch,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
  C_Noch,   C_Noch,   C_Colon,  C_Semic,C_Less/*C_Noch*/,C_Noch,C_Great/*C_Noch*/,C_Noch,
  C_Noch,   C_ph_a_sh,C_Noch,   C_ph_tsh, C_ph_th_v,C_ph_e_sh_inv,C_ph_e_sh,C_ph_dzh,
  C_ph_u_l, C_ph_i_sh,C_ph_i_l, C_Noch,   C_ph_o_l, C_Noch,   C_ph_ng,  C_ph_o_sh,
  C_ph_a_inv,C_ph_a,  C_ph_a_l, C_ph_sh,  C_ph_th_b,C_Noch,   C_ph_u_sh,C_ph_e_inv_l,
  C_Noch,   C_Noch,   C_ph_zh,  C_Lbrack, C_Lslash, C_Rbrack, C_Noch,   C_Noch,
  C_Grave,  C_a,      C_b,      C_Noch,   C_d,      C_e,      C_f,      C_ph_g /* C_g */,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_ph_e_inv,C_r,     C_s,      C_t,      C_u,      C_v,      C_w,
  C_ph_ae,  C_Noch,   C_z,      C_Lcurl,  C_Noch,   C_Rcurl,  C_Noch,   C_Noch
  };

KpChar Ct82l[Ctbsiz/2]={   /*  Phonetic extended (Universal) charset "PhoneticTMUniv" */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,C_ph_acc_low,C_Numb,   C_Unkn,   C_ph_o_l, C_ph_a_n, C_ph_acc,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_ph_a_sh,C_ph_ae,C_ph_a_inv,C_ph_e_sh_inv,C_ph_uu_sh,C_Unkn,C_Unkn,  C_ph_tsh,
  C_ph_dzh, C_ph_u_l, C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_ph_a,C_ph_a_str_n,C_ph_ao_d,C_ph_oe_d,C_ph_th_v,C_ph_e_sh,C_Unkn,C_ph_oe,
  C_ph_oe_n,C_ph_i_sh,C_ph_i_Brev,C_Unkn,C_ph_o_Brev,C_Unkn,C_ph_ng,C_ph_o_sh,
  C_ph_o_n,C_ph_o_slash,C_Unkn,C_ph_sh,C_ph_th_b,C_ph_u_Brev,C_ph_u_sh,C_ph_e_n,
  C_ph_ae_d,C_Unkn,C_ph_zh,  C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Grave,  C_a,      C_b,      C_ph_ch,  C_d,      C_e,      C_f,      C_ph_g /* C_g ??? */,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_ph_e_inv,C_r,     C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  };

KpChar Ct82h[Ctbsiz/2]={   /*  Phonetic extended (Universal) charset "PhoneticTMUniv" upper part*/
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Dots,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,  C_Unkn,
  };



KpChar Ct83l[Ctbsiz/2]={   /*  MS Windows Symbol Font, lower part */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Each,   C_Numb,   C_Exists, C_Perc,   C_Amp,    C_ni,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_cong,   C_Alpha,  C_Beta,   C_Chi,    C_Delta,  C_Epsilon,C_Phi,    C_Gamma,
  C_Eta,    C_Jota, C_theta_var,C_Kappa,  C_Lambda, C_My,     C_Ny,     C_Omicron,
  C_Pi,     C_Theta,  C_Rho,    C_Sigma,  C_Tau,    C_Ypsilon,C_sigma_var,C_Omega,
  C_Xi,     C_Psi,    C_Zeta,   C_Lbrack, C_Unkn,   C_Rbrack, C_perp,   C_Underl,
  C_Unkn,   C_alpha,  C_beta,   C_chi,    C_delta,  C_epsilon,C_phi,    C_gamma,
  C_eta,    C_jota,  C_phi_var, C_kappa,  C_lambda, C_my,     C_ny,     C_omicron,
  C_pi,     C_theta,  C_rho,    C_sigma,  C_tau,    C_ypsilon,C_pi_var, C_omega,
  C_xi,     C_psi,    C_zeta,   C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Noch
  };


KpChar Ct84h[Ctbsiz/2]={   /*  MS Windows Verdana Font, 8-bit encoding, higher part, keisti i 74 !!! */
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Dots,   C_Dag,    C_Ddag,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_cent,   C_Pound,  C_Rouble, C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_RO,     C_Unkn,
  C_deg,    C_PlMin,  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_o_Slash,C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Multipl,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn
  };


KpChar Ct85l[Ctbsiz/2]={   /*  MS Windows Symbol Font lower part characters, for RTF */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Each,   C_Numb,   C_Exists, C_Perc,   C_Amp,    C_Apost/* C_ni */,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_cong,   C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_X,      C_Y,      C_Z,C_Lbrack,C_Lslash/* C_Unkn */,C_Rbrack,C_perp,C_Underl,
  C_Unkn,   C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Noch
  };

KpChar Ct86l[Ctbsiz/2]={   /*  MS Windows Wingdings font */
  C_Noch,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  };

KpChar Ct86h[Ctbsiz/2]={   /*  MS Windows Wingdings font */
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn, C_3DTopLightLeftArrowHead,
 C_3DTopLightRightArrowHead, C_3DRightLightUpArrowHead, C_3DLeftLightDownArrowHead,
                                C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_leftarr,
 C_rightarr,C_uparr,  C_downarr,C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Leftarr,
C_Rightarr,C_Uparr,C_Downarr,C_Leftrightarr,C_Updownarr,C_Unkn,C_Unkn,  C_Unkn,
  C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,   C_Unkn,
  };

KpChar Ct87l[Ctbsiz/2]={   /*  LED Phonetic charset, prideti '<', '>' - tagu skirtukai */
// 0
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
// 1
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
// 2
//C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Spc,    C_Noch,   C_ph_acc_low,C_ph_ae,C_Noch,  C_Noch,   C_Noch,   C_ph_acc, // C_ph_ae=# laikinai
//C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_Lpar,   C_Rpar,   C_Noch,   C_Noch,   C_Noch,   C_Dash,  C_Point,  C_Noch,
// 3
//C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
//C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_Noch,   C_Noch,   C_Colon,  C_Comma,  C_Less,   C_Noch,   C_Great,  C_Noch,
// 4
//C_At,     C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_Noch,   C_ph_a,   C_Noch,   C_Noch,   C_Noch,   C_ph_e_inv,C_Noch,  C_Noch,
//C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_Noch,   C_ph_i_sh,C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_ph_ng,  C_ph_o_sh,
// 5
//C_P,      C_Q,      C_R,      C_S,      C_T,      C_U,      C_V,      C_W,
  C_Noch,   C_ph_th_b,C_Noch,   C_ph_sh,  C_ph_th_v,C_Noch,   C_ph_a_sh,C_ph_e_sh,
//C_X,      C_Y,      C_Z,      C_Lbrack, C_Lslash, C_Rbrack, C_Circ,   C_Underl,
  C_Noch,   C_Noch,   C_ph_zh,  C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch,
// 6
//C_Grave,  C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_Noch,   C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
//C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
// 7
//C_p,      C_q,      C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
  C_p,      C_Noch,   C_r,      C_s,      C_t,      C_u,      C_v,      C_w,
//C_x,      C_y,      C_z,      C_Lcurl,  C_Vertl,  C_Rcurl,  C_Tilde,  C_Del
  C_x,      C_Noch,   C_z,      C_Noch,   C_Noch,   C_Noch,   C_Noch,   C_Noch
  };

KpChar Ct88h[Ctbsiz/2]={   /*  Baltic-RIM, OTEL (Arvydas su Jonu pririnko visokiu simboliu - C_oe, C_Circ) */
  C_euro,   C_square/*???C_Noch*/,   C_LBapost,C_fun,    C_LBquote,C_Dots,   C_Dag,    C_Ddag,
  C_Circ,   C_Prom,   C_S_Car/*C_Noch*/,   C_Lang,   C_OE /* C_Noch */,C_DiaerNcomb/*!!!*/,C_CarNcomb/*!!!*/,C_Cedil,
  C_Noch,   C_LAapost,C_Rapost, C_LAquote,C_Rquote,C_Bpoint,C_EnDash/*C_DashMath*/,C_EmDash,
  C_Noch,   C_TM,     C_s_Car /* C_Noch */,   C_Rang,   C_oe /* C_Noch */,   C_Macr,C_OgonNcomb/*!!!*/,C_Y_Diaer/*C_Noch*/,
  C_NBSP,   C_LAquote,C_cent,   C_Pound,  C_Rouble, C_LBquote,C_Dvertl, C_Para,
  C_O_Slash,C_CO,     C_R_Bcomma,C_Ldopang,C_Rminbr,C_hyph/*!!!*/,C_RO, C_AE,
  C_deg,    C_PlMin,  C_2up,    C_3up,C_AcuteNcomb/*C_Acute C_prim*/,C_micro,C_Pren, C_Lpoint,
  C_o_Slash,C_1up,    C_r_Bcomma,C_Rdopang,C_Quart, C_Half,   C_34,     C_ae,
  C_A_Ogon, C_I_Ogon, C_A_Macr, C_C_Acute,C_A_Diaer,C_A_Ring, C_E_Ogon, C_E_Macr,
  C_C_Car,  C_E_Acute,C_Z_Acute,C_E_Adot, C_G_Bcomma,C_K_Bcomma,C_I_Macr,C_L_Bcomma,
  C_S_Car,  C_N_Acute,C_N_Bcomma,C_O_Acute,C_O_Macr,C_O_Tilde,C_O_Diaer,C_Multipl,
  C_U_Ogon, C_L_Slash,C_S_Acute,C_U_Macr, C_U_Diaer,C_Z_Adot, C_Z_Car,  C_ss,
  C_a_Ogon, C_i_Ogon, C_a_Macr, C_c_Acute,C_a_Diaer,C_a_Ring, C_e_Ogon, C_e_Macr,
  C_c_Car,  C_e_Acute,C_z_Acute,C_e_Adot,C_g_Bcomma/*C_g_Tacom*/,C_k_Bcomma,C_i_Macr,C_l_Bcomma,
  C_s_Car,  C_n_Acute,C_n_Bcomma,C_o_Acute,C_o_Macr,C_o_Tilde,C_o_Diaer,C_Divide,
  C_u_Ogon, C_l_Slash,C_s_Acute,C_u_Macr, C_u_Diaer,C_z_Adot, C_z_Car,  C_LAapost
  };

KpChar Ct91l[Ctbsiz/2]={   /*  Norsk Data lithuanian */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_a_Ogon, C_Eq,     C_A_Ogon, C_Quest,
  C_i_Ogon, C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_E_Ogon, C_R,      C_S,      C_T,      C_U,      C_V,      C_E_Adot,
  C_S_Car,  C_Y,      C_Z,      C_Z_Car,  C_C_Car,  C_U_Macr, C_u_Ogon, C_Underl,
  C_I_Ogon, C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_e_Ogon, C_r,      C_s,      C_t,      C_u,      C_v,      C_e_Adot,
  C_s_Car,  C_y,      C_z,      C_z_Car,  C_c_Car,  C_u_Macr, C_U_Ogon, C_Del
  };

KpChar Ct92l[Ctbsiz/2]={   /*  7-bitis lit. standart.*/
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_Less,   C_Eq,     C_Great,  C_Quest,
  C_U_Ogon, C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_A_Ogon, C_R,      C_S,      C_T,      C_U,      C_V,      C_Z_Car,
  C_I_Ogon, C_Y,      C_Z,      C_S_Car,  C_E_Adot, C_E_Ogon, C_C_Car,  C_U_Macr,
  C_u_Ogon, C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_a_Ogon, C_r,      C_s,      C_t,      C_u,      C_v,      C_z_Car,
  C_i_Ogon, C_y,      C_z,      C_s_Car,  C_e_Adot, C_e_Ogon, C_c_Car,  C_u_Macr
  };

KpChar Ct93l[Ctbsiz/2]={   /*  Norsk Data polish */
  C_Nul,    C_Soh,    C_Stx,    C_Etx,    C_Eot,    C_Enq,    C_Ack,    C_Bel,
  C_Bs,     C_Ht,     C_Lf,     C_Vt,     C_Ff,     C_Cr,     C_So,     C_Si,
  C_Dle,    C_Dc1,    C_Dc2,    C_Dc3,    C_Dc4,    C_Nak,    C_Syn,    C_Etb,
  C_Can,    C_Em,  Eof/*C_Sub*/,C_Esc,    C_Fs,     C_Gs,     C_Rs,     C_Us,
  C_Spc,    C_Excl,   C_Quote,  C_Numb,   C_Doll,   C_Perc,   C_Amp,    C_Apost,
  C_Lpar,   C_Rpar,   C_Ast,    C_Plus,   C_Comma,  C_Dash,  C_Point,  C_Slash,
  C_0,      C_1,      C_2,      C_3,      C_4,      C_5,      C_6,      C_7,
  C_8,      C_9,      C_Colon,  C_Semic,  C_a_Ogon, C_Eq,     C_A_Ogon, C_Quest,
  C_l_Slash,C_A,      C_B,      C_C,      C_D,      C_E,      C_F,      C_G,
  C_H,      C_I,      C_J,      C_K,      C_L,      C_M,      C_N,      C_O,
  C_P,      C_E_Ogon, C_R,      C_S,      C_T,      C_U,      C_N_Acute,C_W,
  C_S_Acute,C_Y,      C_Z,      C_Z_Adot, C_C_Acute,C_O_Acute,C_z_Acute,C_Underl,
  C_L_Slash,C_a,      C_b,      C_c,      C_d,      C_e,      C_f,      C_g,
  C_h,      C_i,      C_j,      C_k,      C_l,      C_m,      C_n,      C_o,
  C_p,      C_e_Ogon, C_r,      C_s,      C_t,      C_u,      C_n_Acute,C_w,
  C_s_Acute,C_y,      C_z,      C_z_Adot, C_c_Acute,C_o_Acute,C_Z_Acute,C_Del
  };

int Ct99l[Ctbsiz/2]={   /*  Transparent code table, lower part */
  0x00,     0x01,     0x02,     0x03,     0x04,     0x05,     0x06,     0x07,
  0x08,     0x09,     0x0a,     0x0b,     0x0c,     0x0d,     0x0e,     0x0f,
  0x10,     0x11,     0x12,     0x13,     0x14,     0x15,     0x16,     0x17,
  0x18,     0x19,     0x1a,     0x1b,     0x1c,     0x1d,     0x1e,     0x1f,
  0x20,     0x21,     0x22,     0x23,     0x24,     0x25,     0x26,     0x27,
  0x28,     0x29,     0x2a,     0x2b,     0x2c,     0x2d,     0x2e,     0x2f,
  0x30,     0x31,     0x32,     0x33,     0x34,     0x35,     0x36,     0x37,
  0x38,     0x39,     0x3a,     0x3b,     0x3c,     0x3d,     0x3e,     0x3f,
  0x40,     0x41,     0x42,     0x43,     0x44,     0x45,     0x46,     0x47,
  0x48,     0x49,     0x4a,     0x4b,     0x4c,     0x4d,     0x4e,     0x4f,
  0x50,     0x51,     0x52,     0x53,     0x54,     0x55,     0x56,     0x57,
  0x58,     0x59,     0x5a,     0x5b,     0x5c,     0x5d,     0x5e,     0x5f,
  0x60,     0x61,     0x62,     0x63,     0x64,     0x65,     0x66,     0x67,
  0x68,     0x69,     0x6a,     0x6b,     0x6c,     0x6d,     0x6e,     0x6f,
  0x70,     0x71,     0x72,     0x73,     0x74,     0x75,     0x76,     0x77,
  0x78,     0x79,     0x7a,     0x7b,     0x7c,     0x7d,     0x7e,     0x7f
  };

int Ct99h[Ctbsiz/2]={   /*  Transparent code table, upper part */
  0x80,     0x81,     0x82,     0x83,     0x84,     0x85,     0x86,     0x87,
  0x88,     0x89,     0x8a,     0x8b,     0x8c,     0x8d,     0x8e,     0x8f,
  0x90,     0x91,     0x92,     0x93,     0x94,     0x95,     0x96,     0x97,
  0x98,     0x99,     0x9a,     0x9b,     0x9c,     0x9d,     0x9e,     0x9f,
  0xa0,     0xa1,     0xa2,     0xa3,     0xa4,     0xa5,     0xa6,     0xa7,
  0xa8,     0xa9,     0xaa,     0xab,     0xac,     0xad,     0xae,     0xaf,
  0xb0,     0xb1,     0xb2,     0xb3,     0xb4,     0xb5,     0xb6,     0xb7,
  0xb8,     0xb9,     0xba,     0xbb,     0xbc,     0xbd,     0xbe,     0xbf,
  0xc0,     0xc1,     0xc2,     0xc3,     0xc4,     0xc5,     0xc6,     0xc7,
  0xc8,     0xc9,     0xca,     0xcb,     0xcc,     0xcd,     0xce,     0xcf,
  0xd0,     0xd1,     0xd2,     0xd3,     0xd4,     0xd5,     0xd6,     0xd7,
  0xd8,     0xd9,     0xda,     0xdb,     0xdc,     0xdd,     0xde,     0xdf,
  0xe0,     0xe1,     0xe2,     0xe3,     0xe4,     0xe5,     0xe6,     0xe7,
  0xe8,     0xe9,     0xea,     0xeb,     0xec,     0xed,     0xee,     0xef,
  0xf0,     0xf1,     0xf2,     0xf3,     0xf4,     0xf5,     0xf6,     0xf7,
  0xf8,     0xf9,     0xfa,     0xfb,     0xfc,     0xfd,     0xfe,     0xff
  };


KpChar *Ctptr7[Ctnum*2]={
  NULL,NULL,   Ct01l,NULL,  Ct02n,NULL,  Ct03l,NULL,  Ct04l,NULL,
  Ct05l,NULL,  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  Ct01l,Ct10h, Ct11l,Ct11h, Ct12l,Ct11h, NULL,NULL,   NULL,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct21l,NULL,  Ct22l,NULL,  Ct23l,NULL,  Ct24l,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct01l,Ct31h, Ct01l,Ct32h, Ct01l,Ct33h, Ct01l,Ct34h,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct40l,Ct41h, Ct40l,Ct42h, Ct40l,Ct43h, Ct40l,Ct44h,
  Ct40l,Ct45h, Ct40l,Ct46h, Ct47l,Ct47h, Ct40l,Ct47h, Ct49l,Ct43h,

  Ct01l,Ct50h, Ct02l,Ct02h, Ct02l,Ct52h, Ct53l,Ct53h, Ct40l,Ct54h,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct61l,Ct61h, NULL,NULL,   NULL,NULL,   NULL,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct01l,Ct71h, Ct01l,Ct72h, Ct01l,Ct73h, Ct01l,Ct74h,
  Ct75l,Ct75h, Ct01l,Ct76h, Ct77l,Ct73h, Ct01l,Ct78h, Ct01l,Ct79h,

  Ct80l,Ct80h, Ct81l,NULL,  Ct82l,Ct82h, Ct83l,Ct75h, Ct01l,Ct84h,
  Ct85l,Ct75h, Ct01l/*Ct86l*/,Ct86h, Ct87l,NULL,   Ct01l,Ct88h,   NULL,NULL, // XXXX

  NULL,NULL,   Ct91l,NULL,  Ct92l,NULL,  Ct93l,NULL,  NULL,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   (KpChar*)Ct99l,(KpChar*)Ct99h
  };


KpChar *Ctptr8[Ctnum*2]={
  NULL,NULL,   Ct01l,NULL,  Ct02l,Ct02h, Ct01l,Ct03l, Ct01l,Ct04l,
  Ct01l,Ct05l, NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  Ct01l,Ct10h, Ct11l,Ct11h, Ct12l,Ct11h, NULL,NULL,   NULL,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct21l,NULL,  Ct22l,NULL,  Ct23l,NULL,  Ct24l,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct01l,Ct31h, Ct01l,Ct32h, Ct01l,Ct33h, Ct01l,Ct34h,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct40l,Ct41h, Ct40l,Ct42h, Ct40l,Ct43h, Ct40l,Ct44h,
  Ct40l,Ct45h, Ct40l,Ct46h, Ct47l,Ct47h, Ct40l,Ct47h, Ct49l,Ct43h,

  Ct01l,Ct50h, Ct02l,Ct02h, Ct02l,Ct52h, Ct53l,Ct53h, Ct40l,Ct54h,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct61l,Ct61h, NULL,NULL,   NULL,NULL,   NULL,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,

  NULL,NULL,   Ct01l,Ct71h, Ct01l,Ct72h, Ct01l,Ct73h, Ct01l,Ct74h,
  Ct75l,Ct75h, Ct01l,Ct76h, Ct77l,Ct73h, Ct01l,Ct78h, Ct01l,Ct79h,

  Ct80l,Ct80h, Ct81l,NULL,  Ct82l,Ct82h, Ct83l,Ct75h, Ct01l,Ct84h,
  Ct85l,Ct75h, Ct01l/*Ct86l*/,Ct86h, Ct87l,NULL,   Ct01l,Ct88h,   NULL,NULL, // XXXX

  NULL,NULL,   Ct91l,NULL,  Ct92l,NULL,  Ct93l,NULL,  NULL,NULL,
  NULL,NULL,   NULL,NULL,   NULL,NULL,   NULL,NULL,   (KpChar*)Ct99l,(KpChar*)Ct99h
  };


// -------------------------------------------------
const unsigned char *lpszaKptCtabExpl[KPT_Ctnum+1] =
{
  (unsigned char *)"",                                      //  0    // Null code table, no encoding (Unicode)
  (unsigned char *)"IRV version, basic Latin, ASCII",       //  1   ISO-646
  (unsigned char *)"ISO Registration #37, basic Cyrillic, KOI-7-1",
                                                            //  2   KOI-7
  (unsigned char *)"Extended Latin, based on ASCII",        //  3   ISO-5426
  (unsigned char *)"Extended Cyrillic, based on ASCII",     //  4   ISO-5427
  (unsigned char *)"Greek, based on ASCII",                 //  5   ISO-5428
  (unsigned char *)"African coded character set, based on ASCII",
                                                            //  6   ISO-6438
  (unsigned char *)"",                                      //  7
  (unsigned char *)"",                                      //  8
  (unsigned char *)"",                                      //  9
  (unsigned char *)"TeX TEV output character set",          // 10
  (unsigned char *)"TeX TEV Cyrillic character set",        // 11
  (unsigned char *)"TeX TEV Cyrillic character set for hyphenation patterns",
                                                            // 12
  (unsigned char *)"",                                      // 13
  (unsigned char *)"",                                      // 14
  (unsigned char *)"",                                      // 15
  (unsigned char *)"",                                      // 16
  (unsigned char *)"",                                      // 17
  (unsigned char *)"",                                      // 18
  (unsigned char *)"",                                      // 19
  (unsigned char *)"",                                      // 20
  (unsigned char *)"German, based on ASCII",                // 21
  (unsigned char *)"French, based on ASCII",                // 22
  (unsigned char *)"Norvegian/danish, based on ASCII",      // 23
  (unsigned char *)"Swedish/finnish, based on ASCII",       // 24
  (unsigned char *)"",                                      // 25
  (unsigned char *)"",                                      // 26
  (unsigned char *)"",                                      // 27
  (unsigned char *)"",                                      // 28
  (unsigned char *)"",                                      // 29
  (unsigned char *)"",                                      // 30
  (unsigned char *)"DOS Multilingual, Latin I, PC-8",       // 31  IBM-437
  (unsigned char *)"DOS Central European, Slavic, Latin II",// 32  IBM-852
  (unsigned char *)"DOS Western, Multilingual, Latin I+",   // 33  IBM-850
  (unsigned char *)"DOS Canadian-French",                   // 34  IBM-863
  (unsigned char *)"",                                      // 35
  (unsigned char *)"",                                      // 36
  (unsigned char *)"",                                      // 37
  (unsigned char *)"",                                      // 38
  (unsigned char *)"",                                      // 39
  (unsigned char *)"",                                      // 40
  (unsigned char *)"DOS Lithuanian standard, based on IBM-437",
                                                            // 41  IBM-774
  (unsigned char *)"DOS Lithuanian standard, based on IBM-855 Cyrillic",
                                                            // 42  IBM-772
  (unsigned char *)"DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic",
                                                            // 43  IBM-773
  (unsigned char *)"Baltic, Fotonija, RST 1095-89",         // 44  IBM-770
  (unsigned char *)"Baltic, old variant of Baltic-RIM",     // 45  ISO-8859-4
  (unsigned char *)"DOS Lithuanian, IBM-Kbl, based on IBM-437",
                                                            // 46  IBM-771
  (unsigned char *)"DOS Cyrillic only, without Latin",      // 47  IBM-855
  (unsigned char *)"DOS Cyrillic",                          // 48  IBM-855
  (unsigned char *)"DOS Lithuanian with Polish letters (TEV), IBM-Kbl, based on IBM-855 Cyrillic",
                                                            // 49  IBM-773
  (unsigned char *)"DOS Lithuanian accented, based on IBM-Kbl",
                                                            // 50
  (unsigned char *)"DOS Cyrillic",                          // 51  KOI8-R
  (unsigned char *)"DOS Cyrillic, ISO-K, code set of russian made PC",
                                                            // 52  ISO-IR-111
  (unsigned char *)"DOS Lithuanian, IBM-Kbl, based on IBM-855 Cyrillic TEX TEV",
                                                            // 53  IBM-773(-)
  (unsigned char *)"DOS Lithuanian, IBM-Kbl, based on IBM-437 TEX TEV",
                                                            // 54  IBM-771(-)
  (unsigned char *)"",                                      // 55
  (unsigned char *)"",                                      // 56
  (unsigned char *)"",                                      // 57
  (unsigned char *)"",                                      // 58
  (unsigned char *)"",                                      // 59
  (unsigned char *)"",                                      // 60
  (unsigned char *)"",                                      // 61  DKOI, EBCDIC
  (unsigned char *)"",                                      // 62
  (unsigned char *)"",                                      // 63
  (unsigned char *)"",                                      // 64
  (unsigned char *)"",                                      // 65
  (unsigned char *)"",                                      // 66
  (unsigned char *)"",                                      // 67
  (unsigned char *)"",                                      // 68
  (unsigned char *)"",                                      // 69
  (unsigned char *)"",                                      // 70
  (unsigned char *)"Baltic RIM, LST 1282-93, ISO-8859-13",  // 71  Windows-1257
  (unsigned char *)"Windows SC",                            // 72
  (unsigned char *)"Windows Cyrillic",                      // 73  Windows-1251
  (unsigned char *)"Windows-1252, ANSI, ECMA Latin 1",      // 74  ISO-Latin-1, Windows-1252
  (unsigned char *)"Windows Symbol Font for TEX formula fields",
                                                            // 75
  (unsigned char *)"Baltic-RIM, some RTF accented characters added",
                                                            // 76  (Windows-1257)
  (unsigned char *)"Cyrillic without latin, with spec. chars (for TEX tags)",
                                                            // 77  (Windows-1251)
  (unsigned char *)"Greek",                                 // 78  Windows-1253
  (unsigned char *)"CE, ANSI-2, Central European",          // 79  Windows-1250
  (unsigned char *)"Windows lithuanian accented charset",   // 80 // "TimesLT Accented" (Windows-1257)
  (unsigned char *)"Windows Phonetic basic charset",        // 81 // "PhoneticTM"
  (unsigned char *)"Windows Phonetic full (Universal) charset",
                                                            // 82 // "PhoneticTMUniv"
  (unsigned char *)"Windows Symbol Font",                   // 83
  (unsigned char *)"Windows Verdana Font 8-bit encoding",   // 84
  (unsigned char *)"Windows Symbol Font with ASCII lowerpart for RTF output",
                                                            // 85
  (unsigned char *)"Windows Wingdings",                     // 86
  (unsigned char *)"LED Phonetic charset",                  // 87
  (unsigned char *)"Baltic-RIM, OTEL",                      // 88  (Windows-1257)
  (unsigned char *)"",                                      // 89
  (unsigned char *)"",                                      // 90
  (unsigned char *)"Norsk Data lithuanian",                 // 91
  (unsigned char *)"Lithuanian ASCII based standart",       // 92
  (unsigned char *)"Norsk Data polish",                     // 93
  (unsigned char *)"",                                      // 94
  (unsigned char *)"",                                      // 95
  (unsigned char *)"",                                      // 96
  (unsigned char *)"",                                      // 97
  (unsigned char *)"",                                      // 98
  (unsigned char *)"Transparent code table for i/o of 8-bit codes without decoding",
                                                            // 99
  NULL
};


// --------------------------------------------------
HRESULT KptCharDecode(unsigned char *pcOutChar, KpChar uiInChar, int iKptTbl)
{
HRESULT retc=S_OK;
bool found=False;
int ii;
KpChar *conv_tbl;

   if((pcOutChar == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *pcOutChar=Nul;

   if(SUCCEEDED(retc)) if((iKptTbl<0) || (iKptTbl>=KPT_Ctnum))
      retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) if((uiInChar<0) || (uiInChar>=C_CharSize0))
   {
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG /* KP_E_UNKN_CHR */, null, True, __FILE__, __LINE__, uiInChar);
//    retc=E_INVALIDARG; // KP_E_UNKN_CHR;
   }

   if(SUCCEEDED(retc))
   {
      if(uiInChar == C_hyph) *pcOutChar = Hyp;
      else
      {
         if(iKptTbl>1)
         {
            conv_tbl=Ctptr8[iKptTbl*2];
            if(conv_tbl!=NULL)
            {
               for(ii=0; ii<Ctbsiz/2; ii++)
               {
                  if(uiInChar==conv_tbl[ii])
                  {
                     found=True;
                     *pcOutChar=ii;
                     break;
                  }
               }
            }
            if(!found)
            {
               conv_tbl=Ctptr8[iKptTbl*2+1];
               if(conv_tbl==NULL)
               {
//                retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, NULL, True, __FILE__, __LINE__, 0L);
                  retc=KP_E_UNKN_CHR;
               }
               else
               {
                  for(ii=0; ii<Ctbsiz/2; ii++)
                  {
                     if(uiInChar==conv_tbl[ii])
                     {
                        found=True;
                        *pcOutChar=ii+Ctbsiz/2;
                        break;
                     }
                  }

               }
            }
         }
         else // if(iKptTbl>1)
         {
            if(uiInChar>=KPT_FirstKptChar)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
               retc=KP_E_UNKN_CHR;
            }
            else
            {
               *pcOutChar=(unsigned char)uiInChar;
               found=True;
            }
         }

      } // else // if(uiInChar == C_hyph)

   } // if(SUCCEEDED(retc))

   if(!found && SUCCEEDED(retc))
   {
//    retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, NULL, True, __FILE__, __LINE__, 0L);
      retc=KP_E_UNKN_CHR;
   }

   if(retc == KP_E_UNKN_CHR)
   {
      if(KptToLatTbl[uiInChar] != uiInChar) KptCharDecode(pcOutChar, KptToLatTbl[uiInChar], iKptTbl);
      else *pcOutChar = '?'; // C_Quest; //
   }

return(retc);
}


// --------------------------------------------------
HRESULT KptCharEncode(KpChar *puiOutChar, unsigned char cInChar, int iKptTbl)
{
HRESULT retc=S_OK;
KpChar *conv_tbl;

   if((puiOutChar == NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) *puiOutChar=(KpChar)C_Quest;

   if(SUCCEEDED(retc)) if(/* (iKptTbl < 0) || */ (iKptTbl >= KPT_Ctnum))
      retc = KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) if(cInChar >= KPT_Ctbsiz)
//    retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      if((iKptTbl < 0) || (iKptTbl == TV_CTBL_TRANSPARENT)) *puiOutChar = cInChar;
      else
      {

      if(cInChar == Hyp) *puiOutChar = C_hyph;
      else
      {
         if(iKptTbl>1)
         {
            if(cInChar<KPT_Ctbsiz/2)
            {
               conv_tbl=Ctptr8[iKptTbl*2];
               if(conv_tbl==NULL)
               {
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);
                  retc=KP_E_UNKN_CHR;
               }
               if(SUCCEEDED(retc))
               {
                  *puiOutChar=conv_tbl[cInChar];
                  if((*puiOutChar)<0)
                  {
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
                     retc=KP_E_UNKN_CHR;
                  }
               }
            }
            else
            {
               conv_tbl=Ctptr8[iKptTbl*2+1];
               if(conv_tbl==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  *puiOutChar=conv_tbl[cInChar-KPT_Ctbsiz/2];
                  if((*puiOutChar)<0)
                  {
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
                     retc=KP_E_UNKN_CHR;
                  }
               }
            }
         }
         else // if(iKptTbl>1)
         {
            if(cInChar>=KPT_Ctbsiz/2)
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_UNKN_CHR, null, True, __FILE__, __LINE__, 0L);
               retc=KP_E_UNKN_CHR;
            }
            else *puiOutChar=(KpChar)cInChar;
         }

      } // else // if(cInChar == Hyp)

      } // else // if((iKptTbl < 0) || (iKptTbl == TV_CTBL_TRANSPARENT))

   }

   if(retc == KP_E_UNKN_CHR) *puiOutChar = C_Quest; // '?'; //

return(retc);
}


// --------------------------------------------------
HRESULT KptStrDecode(unsigned char *lpszOutStr, const KpChar *uiaMsg, int iKptTbl)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
const KpChar *pnti;
unsigned char *pntc;

   if((lpszOutStr==NULL) || (uiaMsg==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnti = uiaMsg;
      pntc = lpszOutStr;

      if(SUCCEEDED(retc)) if((iKptTbl<0) || (iKptTbl>=KPT_Ctnum))
         retc = KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, iKptTbl);

      if(SUCCEEDED(retc)) while(*pnti /* && SUCCEEDED(retc)) */)
      {
         retc0 = KptCharDecode(pntc, *pnti, iKptTbl);
         if(FAILED(retc0))
         {
//          *pntc='?';
//          KptCharDecode(pntc, KptToLatTbl[*pnti], iKptTbl);
KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, *pnti, NULL, False, False);
KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, iKptTbl, NULL, False, False);
            if(SUCCEEDED(retc)) retc=retc0;
         }

         pnti++;
         pntc++;
      }

      *pntc = Nul;
   }

// if((retc==KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
//    /* retc = */ KpErrorProc.OutputErrorMessage(retc, NULL, False, __FILE__, __LINE__, lLastIdx);

return(retc);
}


// --------------------------------------------------
HRESULT KptStrEncode(KpChar *uiaMsg, const unsigned char *lpszInStr, int iKptTbl)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
const unsigned char *pntc = null;
KpChar *pnti = NULL;

   KP_ASSERT(uiaMsg != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszInStr != NULL, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pntc = lpszInStr;
      pnti = uiaMsg;

      if(SUCCEEDED(retc)) if((iKptTbl<0) || (iKptTbl >= KPT_Ctnum))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) while((*pntc) /* && SUCCEEDED(retc) */)
      {
         retc0=KptCharEncode(pnti, *pntc, iKptTbl);
         if(FAILED(retc0))
         {
//          *pnti = C_Quest; // '?'
            if(SUCCEEDED(retc)) retc=retc0;
         }

         pntc++;
         pnti++;
      }

      *pnti = C_Nul;
   }

// if((retc==KP_E_UNKN_CHR) || (retc == KP_E_FONT_UNDEF))
//    /* retc = */ KpErrorProc.OutputErrorMessage(retc, NULL, False, __FILE__, __LINE__, lLastIdx);

return(retc);
}


// --------------------------------------------------
HRESULT KptStrToUnicode(UniChar *saMsg, const unsigned char *lpszInStr, int iKptTbl)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
const unsigned char *pntc;
UniChar *pntu;
KpChar kp_char;

   if(SUCCEEDED(retc)) if((saMsg==NULL) || (lpszInStr==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntc=lpszInStr;
      pntu=saMsg;

      if(SUCCEEDED(retc)) if((iKptTbl<0) || (iKptTbl>=KPT_Ctnum))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) while((*pntc) /* && SUCCEEDED(retc) */)
      {
         retc0=KptCharEncode(&kp_char, *pntc, iKptTbl);
         if(FAILED(retc0))
         {
//          *pntu='?';
            if(SUCCEEDED(retc)) retc=retc0;
         }
         else
         {
            if(iaUniChars[kp_char]) *pntu=iaUniChars[kp_char];
            else
            {
               *pntu='?';
               if(SUCCEEDED(retc)) retc=KP_E_UNKN_CHR;
            }
         }

         pntc++;
         pntu++;
      }

      *pntu=0;
   }

// if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
//    /* retc= */ KpErrorProc.OutputErrorMessage(retc, NULL, False, __FILE__, __LINE__, lLastIdx);

return(retc);
}


// --------------------------------------------------
HRESULT KptUnicodeToStr(unsigned char *lpszOutStr, const UniChar *saMsg, int iKptTbl)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
const UniChar *pntu;
unsigned char *pntc;
KpChar kp_char;
int ii;

   if(SUCCEEDED(retc)) if((lpszOutStr==NULL) || (saMsg==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntu = saMsg;
      pntc = lpszOutStr;

      if(SUCCEEDED(retc)) if((iKptTbl<0) || (iKptTbl>=KPT_Ctnum))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FONT_UNDEF, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) while(*pntu /* && SUCCEEDED(retc) */)
      {
         kp_char=C_Unkn;
         for(ii=0; ii<C_CharSize0; ii++)
            if(iaUniChars[ii]==*pntu)
            {
               kp_char=(KpChar)ii;
               break;
            }

         if(kp_char==C_Unkn)
         {
            kp_char=C_Quest; // '?'
            if(SUCCEEDED(retc)) retc=KP_E_UNKN_CHR;
         }

         retc0=KptCharDecode(pntc, kp_char, iKptTbl);
         if(FAILED(retc0))
         {
//          *pntc='?';
            if(SUCCEEDED(retc)) retc=retc0;
         }

         pntu++;
         pntc++;
      }

      *pntc=Nul;
   }

// if((retc==KP_E_UNKN_CHR) || (retc==KP_E_FONT_UNDEF))
//    /* retc= */ KpErrorProc.OutputErrorMessage(retc, NULL, False, __FILE__, __LINE__, lLastIdx);

return(retc);
}


// ------------------------
HRESULT KptKpCharStrToUnicode(UniChar *saMsg, const KpChar *iaInStr, bool bDotLessToDot)
{
HRESULT retc=S_OK;
const KpChar *pnti;
KpChar kp_char;
UniChar *pntu;

   if(SUCCEEDED(retc)) if((saMsg==NULL) || (iaInStr==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pnti=iaInStr;
      pntu=saMsg;

      while((*pnti) /* && SUCCEEDED(retc) */)
      {
         kp_char = *pnti;

         if(bDotLessToDot) switch(kp_char)
         {
            case C_i_Grave_Dotless: kp_char=C_i_Grave; break;
            case C_i_Acute_Dotless: kp_char=C_i_Acute; break;
            case C_i_Tilde_Dotless: kp_char=C_i_Tilde; break;
         }

         if(SUCCEEDED(retc))
         {
            if((kp_char < 0) || (kp_char >= C_CharSize0))
            {
               *pntu='?';
               if(SUCCEEDED(retc)) retc=KP_E_UNKN_CHR;
            }
            else if(!iaUniChars[kp_char])
            {
               *pntu='?';
               if(SUCCEEDED(retc)) retc=KP_E_UNKN_CHR;
            }
            else *pntu=iaUniChars[kp_char];
         }
// KP_TRACE_2("KptKpCharStrToUnicode: %d --> %d", *pnti, *pntu);

         pnti++;
         pntu++;
      }

      *pntu=0;
   }

return(retc);
}


// ------------------------
HRESULT KptUnicodeToKpCharStr(KpChar *iaOutStr, const UniChar *saMsg)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
const UniChar *pntu = NULL;
KpChar *pnti = NULL;
KpChar kp_char;
int ii;

   if(SUCCEEDED(retc)) if((iaOutStr==NULL) || (saMsg==NULL))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntu = saMsg;
      pnti = iaOutStr;

      if(SUCCEEDED(retc)) while(*pntu /* && SUCCEEDED(retc) */)
      {
         kp_char=C_Unkn;
         for(ii=0; ii<C_CharSize0; ii++)
            if(iaUniChars[ii]==*pntu)
            {
               kp_char=(KpChar)ii;
               break;
            }

         if(kp_char==C_Unkn)
         {
            kp_char=C_Quest; // '?'
            if(SUCCEEDED(retc)) retc=KP_E_UNKN_CHR;
         }

         *pnti = kp_char;

         pntu++;
         pnti++;
      }

      *pnti=C_Nul;
   }

return(retc);
}


// ------------------------
HRESULT EncodeWideStr(unsigned char *lpszStrBuf, long lBufLen, int iKptTbl)
{
HRESULT retc = S_OK;
HRESULT reta = S_OK;
HRESULT retc0 = S_OK;
const unsigned char *pnts = null;
unsigned char *pntd = null;
unsigned char *buf_tmp = null;

   KP_ASSERT(lpszStrBuf != null, E_INVALIDARG, null, True);
   
   KP_NEWA(buf_tmp, unsigned char, lBufLen);
   pnts = lpszStrBuf;
   pntd = buf_tmp;
   
   if(SUCCEEDED(retc)) while((*pnts != Nul) && SUCCEEDED(retc))
   {
      if(*pnts < KPT_FirstKptChar) *pntd++ = *pnts++;
      else
      {
KpChar kp_ch;
         retc0 = KptCharEncode(&kp_ch, *pnts++, iKptTbl);
         if(FAILED(retc0))
         {
            *pntd++ = '?';
            if(SUCCEEDED(reta)) reta = retc0;
         }
         else
         {
            if(iaUniChars[kp_ch] != 0)
            {
unsigned char str_buf[MAX_LONG_HEX_DIGITS + 20];
int str_buf_len;
               sprintf((char *)str_buf, "\\x0%x", iaUniChars[kp_ch]);
               str_buf_len = strlen(str_buf);
               KP_ASSERT((pntd - buf_tmp) + str_buf_len < lBufLen, KP_E_BUFFER_OVERFLOW, null, True);
               if(SUCCEEDED(retc))
               { 
                  strcpy(pntd, str_buf);
                  pntd += str_buf_len;
               }
            }             
            else
            {
               *pntd++ = '?';
               if(SUCCEEDED(reta)) reta = KP_E_UNKN_CHR;
            }
         }
      }
   }

   if(SUCCEEDED(retc)) 
   {
      *pntd = Nul;
      strcpy(lpszStrBuf, buf_tmp);      
   }      
   
   if(SUCCEEDED(retc)) retc = reta;
      
return(retc);
}
 
