// ===================================================
//  kpttucc.cpp
//  converting of Kpt style characters to Kpt strings convertable to Unicode
//


// -----------------------
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string>
#include <stdio.h>
#include <fstream>
#if OsGr==MSWin
#include <windows.h>
#endif

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kptt.h"


// -----------------------
KpChar iaszUniStrs[C_CharArrSize44][KPT_UNI_STR_LEN+1] =
{
   C_Nul,            C_Nul,      C_Nul,   C_Nul,   // C_Nul,            /* 0x00 */
   C_Soh,            C_Nul,      C_Nul,   C_Nul,   // C_Soh,            /* 0x01 */
   C_Stx,            C_Nul,      C_Nul,   C_Nul,   // C_Stx,            /* 0x02 */
   C_Etx,            C_Nul,      C_Nul,   C_Nul,   // C_Etx,            /* 0x03 */
   C_Eot,            C_Nul,      C_Nul,   C_Nul,   // C_Eot,            /* 0x04 */
   C_Enq,            C_Nul,      C_Nul,   C_Nul,   // C_Enq,            /* 0x05 */
   C_Ack,            C_Nul,      C_Nul,   C_Nul,   // C_Ack,            /* 0x06 */
   C_Bel,            C_Nul,      C_Nul,   C_Nul,   // C_Bel,            /* 0x07 */
   C_Bs,             C_Nul,      C_Nul,   C_Nul,   // C_Bs,             /* 0x08 */
   C_Ht,             C_Nul,      C_Nul,   C_Nul,   // C_Ht,             /* 0x09 */
   C_Lf,             C_Nul,      C_Nul,   C_Nul,   // C_Lf,             /* 0x0a */
   C_Vt,             C_Nul,      C_Nul,   C_Nul,   // C_Vt,             /* 0x0b */
   C_Ff,             C_Nul,      C_Nul,   C_Nul,   // C_Ff,             /* 0x0c */
   C_Cr,             C_Nul,      C_Nul,   C_Nul,   // C_Cr,             /* 0x0d */
   C_So,             C_Nul,      C_Nul,   C_Nul,   // C_So,             /* 0x0e */
   C_Si,             C_Nul,      C_Nul,   C_Nul,   // C_Si,             /* 0x0f */
   C_Dle,            C_Nul,      C_Nul,   C_Nul,   // C_Dle,            /* 0x10 */
   C_Dc1,            C_Nul,      C_Nul,   C_Nul,   // C_Dc1,            /* 0x11 */
   C_Dc2,            C_Nul,      C_Nul,   C_Nul,   // C_Dc2,            /* 0x12 */
   C_Dc3,            C_Nul,      C_Nul,   C_Nul,   // C_Dc3,            /* 0x13 */
   C_Dc4,            C_Nul,      C_Nul,   C_Nul,   // C_Dc4,            /* 0x14 */
   C_Nak,            C_Nul,      C_Nul,   C_Nul,   // C_Nak,            /* 0x15 */
   C_Syn,            C_Nul,      C_Nul,   C_Nul,   // C_Syn,            /* 0x16 */
   C_Etb,            C_Nul,      C_Nul,   C_Nul,   // C_Etb,            /* 0x17 */
   C_Can,            C_Nul,      C_Nul,   C_Nul,   // C_Can,            /* 0x18 */
   C_Em,             C_Nul,      C_Nul,   C_Nul,   // C_Em,             /* 0x19 */
   C_Sub,            C_Nul,      C_Nul,   C_Nul,   // C_Sub,            /* 0x1a */
   C_Esc,            C_Nul,      C_Nul,   C_Nul,   // C_Esc,            /* 0x1b */
   C_Fs,             C_Nul,      C_Nul,   C_Nul,   // C_Fs,             /* 0x1c */
   C_Gs,             C_Nul,      C_Nul,   C_Nul,   // C_Gs,             /* 0x1d */
   C_Rs,             C_Nul,      C_Nul,   C_Nul,   // C_Rs,             /* 0x1e */
   C_Us,             C_Nul,      C_Nul,   C_Nul,   // C_Us,             /* 0x1f */

   C_Spc,            C_Nul,      C_Nul,   C_Nul,   // C_Spc,            /* Space */
   C_Excl,           C_Nul,      C_Nul,   C_Nul,   // C_Excl,           /* !  Exclamation Mark (s/auktukas) */
   C_Quote,          C_Nul,      C_Nul,   C_Nul,   // C_Quote,          /* "  Quotation Mark (kabute%s) */
   C_Numb,           C_Nul,      C_Nul,   C_Nul,   // C_Numb,           /* #  Number Sign (Numerio zenklas) */
   C_Doll,           C_Nul,      C_Nul,   C_Nul,   // C_Doll,           /* $  Currency Sign (Pinigu zenklas) */
   C_Perc,           C_Nul,      C_Nul,   C_Nul,   // C_Perc,           /* %  Per Cent Sign (procento z/enklas) */
   C_Amp,            C_Nul,      C_Nul,   C_Nul,   // C_Amp,            /* &  Ampersand (Ampersandas) */
   C_Apost,          C_Nul,      C_Nul,   C_Nul,   // C_Apost,          /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   C_Lpar,           C_Nul,      C_Nul,   C_Nul,   // C_Lpar,           /* (  Left Parenthesis (kairysis skliaustas) */
   C_Rpar,           C_Nul,      C_Nul,   C_Nul,   // C_Rpar,           /* )  Right Parenthesis (des/inysis skliaustas) */
   C_Ast,            C_Nul,      C_Nul,   C_Nul,   // C_Ast,            /* *  Asterisk (Zvaigzdute) */
   C_Plus,           C_Nul,      C_Nul,   C_Nul,   // C_Plus,           /* +  Plus Sign (pliusas) */
   C_Comma,          C_Nul,      C_Nul,   C_Nul,   // C_Comma,          /* ,  Comma (kablelis) */
   C_Dash,           C_Nul,      C_Nul,   C_Nul,   // C_Minus,          /* -  Dash, Hyphen, Minus Sign (minusas) */
   C_Point,          C_Nul,      C_Nul,   C_Nul,   // C_Point,          /* .  Full Stop, Period, Point (tas/kas) */
   C_Slash,          C_Nul,      C_Nul,   C_Nul,   // C_Slash,          /* /  Slash, Solidus (Istrizas bruksnys) */
   C_0,              C_Nul,      C_Nul,   C_Nul,   // C_0,              /* 0 */
   C_1,              C_Nul,      C_Nul,   C_Nul,   // C_1,              /* 1 */
   C_2,              C_Nul,      C_Nul,   C_Nul,   // C_2,              /* 2 */
   C_3,              C_Nul,      C_Nul,   C_Nul,   // C_3,              /* 3 */
   C_4,              C_Nul,      C_Nul,   C_Nul,   // C_4,              /* 4 */
   C_5,              C_Nul,      C_Nul,   C_Nul,   // C_5,              /* 5 */
   C_6,              C_Nul,      C_Nul,   C_Nul,   // C_6,              /* 6 */
   C_7,              C_Nul,      C_Nul,   C_Nul,   // C_7,              /* 7 */
   C_8,              C_Nul,      C_Nul,   C_Nul,   // C_8,              /* 8 */
   C_9,              C_Nul,      C_Nul,   C_Nul,   // C_9,              /* 9 */
   C_Colon,          C_Nul,      C_Nul,   C_Nul,   // C_Colon,          /* :  Colon (dvitas/kis) */
   C_Semic,          C_Nul,      C_Nul,   C_Nul,   // C_Semic,          /* ;  Semi-colon (kabliatas/kis) */
   C_Less,           C_Nul,      C_Nul,   C_Nul,   // C_Less,           /* <  Less than Sign (maz/iau) */
   C_Eq,             C_Nul,      C_Nul,   C_Nul,   // C_Eq,             /* =  Equals Sign (lygybe%s z/enklas) */
   C_Great,          C_Nul,      C_Nul,   C_Nul,   // C_Great,          /* >  Greater than Sign (daugiau) */
   C_Quest,          C_Nul,      C_Nul,   C_Nul,   // C_Quest,          /* ?  Question Mark (klaustukas) */

   C_At,             C_Nul,      C_Nul,   C_Nul,   // C_At,             /* @  Commercial At (Prekybinis zenklas "Pas") */
   C_A,              C_Nul,      C_Nul,   C_Nul,   // C_A,              /* A */
   C_B,              C_Nul,      C_Nul,   C_Nul,   // C_B,              /* B */
   C_C,              C_Nul,      C_Nul,   C_Nul,   // C_C,              /* C */
   C_D,              C_Nul,      C_Nul,   C_Nul,   // C_D,              /* D */
   C_E,              C_Nul,      C_Nul,   C_Nul,   // C_E,              /* E */
   C_F,              C_Nul,      C_Nul,   C_Nul,   // C_F,              /* F */
   C_G,              C_Nul,      C_Nul,   C_Nul,   // C_G,              /* G */
   C_H,              C_Nul,      C_Nul,   C_Nul,   // C_H,              /* H */
   C_I,              C_Nul,      C_Nul,   C_Nul,   // C_I,              /* I */
   C_J,              C_Nul,      C_Nul,   C_Nul,   // C_J,              /* J */
   C_K,              C_Nul,      C_Nul,   C_Nul,   // C_K,              /* K */
   C_L,              C_Nul,      C_Nul,   C_Nul,   // C_L,              /* L */
   C_M,              C_Nul,      C_Nul,   C_Nul,   // C_M,              /* M */
   C_N,              C_Nul,      C_Nul,   C_Nul,   // C_N,              /* N */
   C_O,              C_Nul,      C_Nul,   C_Nul,   // C_O,              /* O */
   C_P,              C_Nul,      C_Nul,   C_Nul,   // C_P,              /* P */
   C_Q,              C_Nul,      C_Nul,   C_Nul,   // C_Q,              /* Q */
   C_R,              C_Nul,      C_Nul,   C_Nul,   // C_R,              /* R */
   C_S,              C_Nul,      C_Nul,   C_Nul,   // C_S,              /* S */
   C_T,              C_Nul,      C_Nul,   C_Nul,   // C_T,              /* T */
   C_U,              C_Nul,      C_Nul,   C_Nul,   // C_U,              /* U */
   C_V,              C_Nul,      C_Nul,   C_Nul,   // C_V,              /* V */
   C_W,              C_Nul,      C_Nul,   C_Nul,   // C_W,              /* W */
   C_X,              C_Nul,      C_Nul,   C_Nul,   // C_X,              /* X */
   C_Y,              C_Nul,      C_Nul,   C_Nul,   // C_Y,              /* Y */
   C_Z,              C_Nul,      C_Nul,   C_Nul,   // C_Z,              /* Z */
   C_Lbrack,         C_Nul,      C_Nul,   C_Nul,   // C_Lbrack,         /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   C_Lslash,         C_Nul,      C_Nul,   C_Nul,   // C_Lslash,         /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   C_Rbrack,         C_Nul,      C_Nul,   C_Nul,   // C_Rbrack,         /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   C_Circ,           C_Nul,      C_Nul,   C_Nul,   // C_Circ,           /* ^  Circumflex Accent (Cirkumfleksas), standalone */
   C_Underl,         C_Nul,      C_Nul,   C_Nul,   // C_Underl,         /* _  Underline (Pabraukimas) */

   C_Grave,          C_Nul,      C_Nul,   C_Nul,   // C_Grave,          /* `  Grave Accent (gravis), standalone */
   C_a,              C_Nul,      C_Nul,   C_Nul,   // C_a,              /* a */
   C_b,              C_Nul,      C_Nul,   C_Nul,   // C_b,              /* b */
   C_c,              C_Nul,      C_Nul,   C_Nul,   // C_c,              /* c */
   C_d,              C_Nul,      C_Nul,   C_Nul,   // C_d,              /* d */
   C_e,              C_Nul,      C_Nul,   C_Nul,   // C_e,              /* e */
   C_f,              C_Nul,      C_Nul,   C_Nul,   // C_f,              /* f */
   C_g,              C_Nul,      C_Nul,   C_Nul,   // C_g,              /* g */
   C_h,              C_Nul,      C_Nul,   C_Nul,   // C_h,              /* h */
   C_i,              C_Nul,      C_Nul,   C_Nul,   // C_i,              /* i */
   C_j,              C_Nul,      C_Nul,   C_Nul,   // C_j,              /* j */
   C_k,              C_Nul,      C_Nul,   C_Nul,   // C_k,              /* k */
   C_l,              C_Nul,      C_Nul,   C_Nul,   // C_l,              /* l */
   C_m,              C_Nul,      C_Nul,   C_Nul,   // C_m,              /* m */
   C_n,              C_Nul,      C_Nul,   C_Nul,   // C_n,              /* n */
   C_o,              C_Nul,      C_Nul,   C_Nul,   // C_o,              /* o */
   C_p,              C_Nul,      C_Nul,   C_Nul,   // C_p,              /* p */
   C_q,              C_Nul,      C_Nul,   C_Nul,   // C_q,              /* q */
   C_r,              C_Nul,      C_Nul,   C_Nul,   // C_r,              /* r */
   C_s,              C_Nul,      C_Nul,   C_Nul,   // C_s,              /* s */
   C_t,              C_Nul,      C_Nul,   C_Nul,   // C_t,              /* t */
   C_u,              C_Nul,      C_Nul,   C_Nul,   // C_u,              /* u */
   C_v,              C_Nul,      C_Nul,   C_Nul,   // C_v,              /* v */
   C_w,              C_Nul,      C_Nul,   C_Nul,   // C_w,              /* w */
   C_x,              C_Nul,      C_Nul,   C_Nul,   // C_x,              /* x */
   C_y,              C_Nul,      C_Nul,   C_Nul,   // C_y,              /* y */
   C_z,              C_Nul,      C_Nul,   C_Nul,   // C_z,              /* z */
   C_Lcurl,          C_Nul,      C_Nul,   C_Nul,   // C_Lcurl,          /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   C_Vertl,          C_Nul,      C_Nul,   C_Nul,   // C_Vertl,          /* |  Vertical Line (Vertikali Linija), C_v_b */
   C_Rcurl,          C_Nul,      C_Nul,   C_Nul,   // C_Rcurl,          /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   C_Tilde,          C_Nul,      C_Nul,   C_Nul,   // C_Tilde,          /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje), standalone */

   C_Del,            C_Nul,      C_Nul,   C_Nul,   // C_Del,

   C_AE,             C_Nul,      C_Nul,   C_Nul,   // C_AE,
   C_ae,             C_Nul,      C_Nul,   C_Nul,   // C_ae,
   C_OE,             C_Nul,      C_Nul,   C_Nul,   // C_OE,
   C_oe,             C_Nul,      C_Nul,   C_Nul,   // C_oe,
   C_IJ,             C_Nul,      C_Nul,   C_Nul,   // C_IJ,
   C_ij,             C_Nul,      C_Nul,   C_Nul,   // C_ij,
   C_ss,             C_Nul,      C_Nul,   C_Nul,   // C_ss,             /* sharp s (german, C_beta) */

   C_A_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_A_Cyr,
   C_B_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_B_Cyr,
   C_V_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_V_Cyr,
   C_G_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_G_Cyr,
   C_D_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_D_Cyr,
   C_E_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_E_Cyr,
   C_Zh_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_Zh_Cyr,
   C_Z_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_Z_Cyr,
   C_I_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_I_Cyr,
   C_J_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_J_Cyr,
   C_K_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_K_Cyr,
   C_L_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_L_Cyr,
   C_M_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_M_Cyr,
   C_N_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_N_Cyr,
   C_O_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_O_Cyr,
   C_P_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_P_Cyr,
   C_R_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_R_Cyr,
   C_S_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_S_Cyr,
   C_T_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_T_Cyr,
   C_U_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_U_Cyr,
   C_F_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_F_Cyr,
   C_H_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_H_Cyr,
   C_C_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_C_Cyr,
   C_Ch_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_Ch_Cyr,
   C_Sh_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_Sh_Cyr,
   C_Shch_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_Shch_Cyr,
   C_Hard_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_Hard_Cyr,
   C_Y_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_Y_Cyr,
   C_Soft_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_Soft_Cyr,
   C_Ee_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_Ee_Cyr,
   C_Yu_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_Yu_Cyr,
   C_Ya_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_Ya_Cyr,

   C_a_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_a_Cyr,
   C_b_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_b_Cyr,
   C_v_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_v_Cyr,
   C_g_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_g_Cyr,
   C_d_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_d_Cyr,
   C_e_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_e_Cyr,
   C_zh_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_zh_Cyr,
   C_z_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_z_Cyr,
   C_i_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_i_Cyr,
   C_j_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_j_Cyr,
   C_k_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_k_Cyr,
   C_l_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_l_Cyr,
   C_m_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_m_Cyr,
   C_n_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_n_Cyr,
   C_o_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_o_Cyr,
   C_p_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_p_Cyr,
   C_r_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_r_Cyr,
   C_s_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_s_Cyr,
   C_t_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_t_Cyr,
   C_u_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_u_Cyr,
   C_f_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_f_Cyr,
   C_h_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_h_Cyr,
   C_c_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_c_Cyr,
   C_ch_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_ch_Cyr,
   C_sh_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_sh_Cyr,
   C_shch_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_shch_Cyr,
   C_hard_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_hard_Cyr,
   C_y_Cyr,          C_Nul,      C_Nul,   C_Nul,   // C_y_Cyr,
   C_soft_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_soft_Cyr,
   C_ee_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_ee_Cyr,
   C_yu_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_yu_Cyr,
   C_ya_Cyr,         C_Nul,      C_Nul,   C_Nul,   // C_ya_Cyr,

                                                                        // ----------------------------
                                                                        /* Additional greek chars variations follow later */

   C_Alpha,          C_Nul,      C_Nul,   C_Nul,   // C_Alpha,
   C_Beta,           C_Nul,      C_Nul,   C_Nul,   // C_Beta,
   C_Gamma,          C_Nul,      C_Nul,   C_Nul,   // C_Gamma,
   C_Delta,          C_Nul,      C_Nul,   C_Nul,   // C_Delta,
   C_Epsilon,        C_Nul,      C_Nul,   C_Nul,   // C_Epsilon,
   C_Zeta,           C_Nul,      C_Nul,   C_Nul,   // C_Zeta,
   C_Eta,            C_Nul,      C_Nul,   C_Nul,   // C_Eta,
   C_Theta,          C_Nul,      C_Nul,   C_Nul,   // C_Theta,
   C_Jota,           C_Nul,      C_Nul,   C_Nul,   // C_Jota,
   C_Kappa,          C_Nul,      C_Nul,   C_Nul,   // C_Kappa,
   C_Lambda,         C_Nul,      C_Nul,   C_Nul,   // C_Lambda,
   C_My,             C_Nul,      C_Nul,   C_Nul,   // C_My,
   C_Ny,             C_Nul,      C_Nul,   C_Nul,   // C_Ny,
   C_Xi,             C_Nul,      C_Nul,   C_Nul,   // C_Xi,
   C_Omicron,        C_Nul,      C_Nul,   C_Nul,   // C_Omikron,
   C_Pi,             C_Nul,      C_Nul,   C_Nul,   // C_Pi,
   C_Rho,            C_Nul,      C_Nul,   C_Nul,   // C_Rho,
   C_Sigma,          C_Nul,      C_Nul,   C_Nul,   // C_Sigma,
   C_Tau,            C_Nul,      C_Nul,   C_Nul,   // C_Tau,
   C_Ypsilon,        C_Nul,      C_Nul,   C_Nul,   // C_Ypsilon,
   C_Phi,            C_Nul,      C_Nul,   C_Nul,   // C_Phi,
   C_Chi,            C_Nul,      C_Nul,   C_Nul,   // C_Chi,
   C_Psi,            C_Nul,      C_Nul,   C_Nul,   // C_Psi,
   C_Omega,          C_Nul,      C_Nul,   C_Nul,   // C_Omega,

   C_alpha,          C_Nul,      C_Nul,   C_Nul,   // C_alpha,
   C_beta,           C_Nul,      C_Nul,   C_Nul,   // C_beta,
   C_gamma,          C_Nul,      C_Nul,   C_Nul,   // C_gamma,
   C_delta,          C_Nul,      C_Nul,   C_Nul,   // C_delta,
   C_epsilon,        C_Nul,      C_Nul,   C_Nul,   // C_epsilon,        // curly epsilon
   C_zeta,           C_Nul,      C_Nul,   C_Nul,   // C_zeta,
   C_eta,            C_Nul,      C_Nul,   C_Nul,   // C_eta,
   C_theta,          C_Nul,      C_Nul,   C_Nul,   // C_theta,          // straight theta
   C_jota,           C_Nul,      C_Nul,   C_Nul,   // C_jota,
   C_kappa,          C_Nul,      C_Nul,   C_Nul,   // C_kappa,          // straight kappa
   C_lambda,         C_Nul,      C_Nul,   C_Nul,   // C_lambda,
   C_my,             C_Nul,      C_Nul,   C_Nul,   // C_my,
   C_ny,             C_Nul,      C_Nul,   C_Nul,   // C_ny,
   C_xi,             C_Nul,      C_Nul,   C_Nul,   // C_xi,
   C_omicron,        C_Nul,      C_Nul,   C_Nul,   // C_omikron,
   C_pi,             C_Nul,      C_Nul,   C_Nul,   // C_pi,             // straight pi
   C_rho,            C_Nul,      C_Nul,   C_Nul,   // C_rho,            // straight rho
   C_sigma,          C_Nul,      C_Nul,   C_Nul,   // C_sigma,          // inner sigma
   C_tau,            C_Nul,      C_Nul,   C_Nul,   // C_tau,
   C_ypsilon,        C_Nul,      C_Nul,   C_Nul,   // C_ypsilon,
   C_phi,            C_Nul,      C_Nul,   C_Nul,   // C_phi,            // straight phi
   C_chi,            C_Nul,      C_Nul,   C_Nul,   // C_chi,
   C_psi,            C_Nul,      C_Nul,   C_Nul,   // C_psi,
   C_omega,          C_Nul,      C_Nul,   C_Nul,   // C_omega,

   C_delta_Dash,     C_Nul,      C_Nul,   C_Nul,   // C_delt_Mn,        /* skardi th */

                                                                        // ----------------------------
                                                                        /* All accents have no width (over the next letter) */
                                                                        /* more accents later - C_...Acc */

   C_Acute,          C_Nul,      C_Nul,   C_Nul,   // C_Acute,          /* '  Acute (aku/tas, C_Apost, des/inysis kirtis) */
   C_Dacut,          C_Nul,      C_Nul,   C_Nul,   // C_Dacut,          /* '' Double Acute */
   C_Ogon,           C_Nul,      C_Nul,   C_Nul,   // C_Ogon,           /* ,  Ogonek (nosine) */
   C_Adot,           C_Nul,      C_Nul,   C_Nul,   // C_Adot,           /* .  Dot Above (. virsuje) */
   C_Car,            C_Nul,      C_Nul,   C_Nul,   // C_Car,            /* v  Carron, Caron (Pauksciukas) */
   C_Macr,           C_Nul,      C_Nul,   C_Nul,   // C_Macr,           /* _  Macron, Overline (bruksnys virsuje) */
   C_Diaer,          C_Nul,      C_Nul,   C_Nul,   // C_Diaer,          /* .. Diaeresis (Umlaut) */
   C_Ring,           C_Nul,      C_Nul,   C_Nul,   // C_Ring,           /* o  Ring (Circle) Above (o virsuje, degree) */
   C_Tacom,          C_Nul,      C_Nul,   C_Nul,   // C_Tacom,          /* '  Turned Comma Above */
   C_Bcomma,         C_Nul,      C_Nul,   C_Nul,   // C_Bcomma,         /* ,  Comma Bellow */
   C_Cedil,          C_Nul,      C_Nul,   C_Nul,   // C_Cedil,          /* ,  Cedilla (atbula nosine) */

   C_A_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_A_Ogon,         /* A, */
   C_a_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_a_Ogon,         /* a, */
   C_E_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_E_Ogon,         /* E, */
   C_e_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_e_Ogon,         /* e, */
   C_I_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_I_Ogon,         /* I, */
   C_i_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_i_Ogon,         /* i, */
   C_U_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_U_Ogon,         /* U, */
   C_u_Ogon,         C_Nul,      C_Nul,   C_Nul,   // C_u_Ogon,         /* u, */

   C_E_Adot,         C_Nul,      C_Nul,   C_Nul,   // C_E_Adot,         /* E. */
   C_e_Adot,         C_Nul,      C_Nul,   C_Nul,   // C_e_Adot,         /* e. */
   C_Z_Adot,         C_Nul,      C_Nul,   C_Nul,   // C_Z_Adot,         /* Z. */
   C_z_Adot,         C_Nul,      C_Nul,   C_Nul,   // C_z_Adot,         /* z. */

   C_G_Cyr_Adot,     C_Nul,      C_Nul,   C_Nul,   // C_G_Cyr_Adot,     /* G Cyr . */
   C_g_Cyr_Adot,     C_Nul,      C_Nul,   C_Nul,   // C_g_Cyr_Adot,     /* g Cyr . */

   C_C_Car,          C_Nul,      C_Nul,   C_Nul,   // C_C_Car,          /* Cv */
   C_c_Car,          C_Nul,      C_Nul,   C_Nul,   // C_c_Car,          /* cv */
   C_D_Car,          C_Nul,      C_Nul,   C_Nul,   // C_D_Car,          /* Dv */
   C_d_Car,          C_Nul,      C_Nul,   C_Nul,   // C_d_Car,          /* dv */
   C_E_Car,          C_Nul,      C_Nul,   C_Nul,   // C_E_Car,          /* Ev */
   C_e_Car,          C_Nul,      C_Nul,   C_Nul,   // C_e_Car,          /* ev */
   C_L_Car,          C_Nul,      C_Nul,   C_Nul,   // C_L_Car,          /* Lv */
   C_l_Car,          C_Nul,      C_Nul,   C_Nul,   // C_l_Car,          /* lv */
   C_N_Car,          C_Nul,      C_Nul,   C_Nul,   // C_N_Car,          /* Nv */
   C_n_Car,          C_Nul,      C_Nul,   C_Nul,   // C_n_Car,          /* nv */
   C_R_Car,          C_Nul,      C_Nul,   C_Nul,   // C_R_Car,          /* Rv */
   C_r_Car,          C_Nul,      C_Nul,   C_Nul,   // C_r_Car,          /* rv */
   C_S_Car,          C_Nul,      C_Nul,   C_Nul,   // C_S_Car,          /* Sv */
   C_s_Car,          C_Nul,      C_Nul,   C_Nul,   // C_s_Car,          /* sv */
   C_T_Car,          C_Nul,      C_Nul,   C_Nul,   // C_T_Car,          /* Tv */
   C_t_Car,          C_Nul,      C_Nul,   C_Nul,   // C_t_Car,          /* tv */
   C_Z_Car,          C_Nul,      C_Nul,   C_Nul,   // C_Z_Car,          /* Zv */
   C_z_Car,          C_Nul,      C_Nul,   C_Nul,   // C_z_Car,          /* zv */

   C_A_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_A_Macr,         /* A_ */
   C_a_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_a_Macr,         /* a_ */
   C_E_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_E_Macr,         /* E_ */
   C_e_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_e_Macr,         /* e_ */
   C_I_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_I_Macr,         /* I_ */
   C_i_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_i_Macr,         /* i_ */
   C_O_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_O_Macr,         /* O_ */
   C_o_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_o_Macr,         /* o_ */
   C_U_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_U_Macr,         /* U_ */
   C_u_Macr,         C_Nul,      C_Nul,   C_Nul,   // C_u_Macr,         /* u_ */

   C_A_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_A_Diaer,        /* A.. */
   C_a_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_a_Diaer,        /* a.. */
   C_E_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_E_Diaer,        /* E.. */
   C_e_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_e_Diaer,        /* e.. */
   C_I_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_I_Diaer,        /* I.. */
   C_i_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_i_Diaer,        /* i.. */
   C_O_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_O_Diaer,        /* O.. */
   C_o_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_o_Diaer,        /* o.. */
   C_U_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_U_Diaer,        /* U.. */
   C_u_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_u_Diaer,        /* u.. */
   C_Y_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_Y_Diaer,        /* Y.. */
   C_y_Diaer,        C_Nul,      C_Nul,   C_Nul,   // C_y_Diaer,        /* y.. */

   C_E_Cyr_Diaer,    C_Nul,      C_Nul,   C_Nul,   // C_E_Cyr_Diaer,    /* E.. */
   C_e_Cyr_Diaer,    C_Nul,      C_Nul,   C_Nul,   // C_e_Cyr_Diaer,    /* e.. */

   C_A_Ring,         C_Nul,      C_Nul,   C_Nul,   // C_A_Ring,         /* Ao */
   C_a_Ring,         C_Nul,      C_Nul,   C_Nul,   // C_a_Ring,         /* ao */
   C_U_Ring,         C_Nul,      C_Nul,   C_Nul,   // C_U_Ring,         /* Uo */
   C_u_Ring,         C_Nul,      C_Nul,   C_Nul,   // C_u_Ring,         /* uo */

   C_G_Tacom,        C_Nul,      C_Nul,   C_Nul,   // C_G_Tacom,        /* G' */
   C_g_Tacom,        C_Nul,      C_Nul,   C_Nul,   // C_g_Tacom,        /* g' */

   C_G_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_G_Bcomma,       /* G, */
   C_g_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_g_Bcomma,       /* g, */
   C_K_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_K_Bcomma,       /* K, */
   C_k_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_k_Bcomma,       /* k, */
   C_L_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_L_Bcomma,       /* L, */
   C_l_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_l_Bcomma,       /* l, */
   C_N_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_N_Bcomma,       /* N, */
   C_n_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_n_Bcomma,       /* n, */
   C_R_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_R_Bcomma,       /* R, */
   C_r_Bcomma,       C_Nul,      C_Nul,   C_Nul,   // C_r_Bcomma,       /* r, */

   C_C_Cedil,        C_Nul,      C_Nul,   C_Nul,   // C_C_Cedil,        /* C, */
   C_c_Cedil,        C_Nul,      C_Nul,   C_Nul,   // C_c_Cedil,        /* c, */
   C_S_Cedil,        C_Nul,      C_Nul,   C_Nul,   // C_S_Cedil,        /* S, */
   C_s_Cedil,        C_Nul,      C_Nul,   C_Nul,   // C_s_Cedil,        /* s, */
   C_T_Cedil,        C_Nul,      C_Nul,   C_Nul,   // C_T_Cedil,        /* T, */
   C_t_Cedil,        C_Nul,      C_Nul,   C_Nul,   // C_t_Cedil,        /* t, */

   C_A_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_A_Grave,        /* A` */
   C_a_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_a_Grave,        /* a` */
   C_E_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_E_Grave,        /* E` */
   C_e_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_e_Grave,        /* e` */
   C_I_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_I_Grave,        /* I` */
   C_i_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_i_Grave,        /* i` */
   C_O_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_O_Grave,        /* O` */
   C_o_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_o_Grave,        /* o` */
   C_U_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_U_Grave,        /* U` */
   C_u_Grave,        C_Nul,      C_Nul,   C_Nul,   // C_u_Grave,        /* u` */

   C_A_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_A_Acute,        /* A' */
   C_a_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_a_Acute,        /* a' */
   C_C_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_C_Acute,        /* C' */
   C_c_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_c_Acute,        /* c' */
   C_E_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_E_Acute,        /* E' */
   C_e_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_e_Acute,        /* e' */
   C_I_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_I_Acute,        /* I' */
   C_i_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_i_Acute,        /* i' */
   C_L_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_L_Acute,        /* L' */
   C_l_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_l_Acute,        /* l' */
   C_N_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_N_Acute,        /* N' */
   C_n_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_n_Acute,        /* n' */
   C_O_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_O_Acute,        /* O' */
   C_o_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_o_Acute,        /* o' */
   C_R_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_R_Acute,        /* R' */
   C_r_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_r_Acute,        /* r' */
   C_S_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_S_Acute,        /* S' */
   C_s_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_s_Acute,        /* s' */
   C_U_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_U_Acute,        /* U' */
   C_u_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_u_Acute,        /* u' */
   C_Y_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_Y_Acute,        /* Y' */
   C_y_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_y_Acute,        /* y' */
   C_Z_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_Z_Acute,        /* Z' */
   C_z_Acute,        C_Nul,      C_Nul,   C_Nul,   // C_z_Acute,        /* z' */

   C_K_Cyr_Acute,    C_Nul,      C_Nul,   C_Nul,   // C_K_Cyr_Acute,    /* K Cyr ' */
   C_k_Cyr_Acute,    C_Nul,      C_Nul,   C_Nul,   // C_k_Cyr_Acute,    /* k Cyr ' */

   C_O_Dacut,        C_Nul,      C_Nul,   C_Nul,   // C_O_Dacut,        /* O'' */
   C_o_Dacut,        C_Nul,      C_Nul,   C_Nul,   // C_o_Dacut,        /* o'' */
   C_U_Dacut,        C_Nul,      C_Nul,   C_Nul,   // C_U_Dacut,        /* U'' */
   C_u_Dacut,        C_Nul,      C_Nul,   C_Nul,   // C_u_Dacut,        /* u'' */

   C_A_Tilde,        C_Nul,      C_Nul,   C_Nul,   // C_A_Tilde,        /* A~ */
   C_a_Tilde,        C_Nul,      C_Nul,   C_Nul,   // C_a_Tilde,        /* a~ */
   C_N_Tilde,        C_Nul,      C_Nul,   C_Nul,   // C_N_Tilde,        /* N~ */
   C_n_Tilde,        C_Nul,      C_Nul,   C_Nul,   // C_n_Tilde,        /* n~ */
   C_O_Tilde,        C_Nul,      C_Nul,   C_Nul,   // C_O_Tilde,        /* O~ */
   C_o_Tilde,        C_Nul,      C_Nul,   C_Nul,   // C_o_Tilde,        /* o~ */

   C_L_Slash,        C_Nul,      C_Nul,   C_Nul,   // C_L_Slash,        /* L/ */
   C_l_Slash,        C_Nul,      C_Nul,   C_Nul,   // C_l_Slash,        /* l/ */
   C_O_Slash,        C_Nul,      C_Nul,   C_Nul,   // C_O_Slash,        /* O/ */
   C_o_Slash,        C_Nul,      C_Nul,   C_Nul,   // C_o_Slash,        /* o/ */

   C_A_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_A_Circ,         /* A^ */
   C_a_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_a_Circ,         /* a^ */
   C_E_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_E_Circ,         /* E^ */
   C_e_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_e_Circ,         /* e^ */
   C_I_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_I_Circ,         /* I^ */
   C_i_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_i_Circ,         /* i^ */
   C_O_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_O_Circ,         /* O^ */
   C_o_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_o_Circ,         /* o^ */
   C_U_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_U_Circ,         /* U^ */
   C_u_Circ,         C_Nul,      C_Nul,   C_Nul,   // C_u_Circ,         /* u^ */

   C_D_Dash,         C_Nul,      C_Nul,   C_Nul,   // C_D_Minus,        /* D- Island. */
   C_d_Dash,         C_Nul,      C_Nul,   C_Nul,   // C_d_Minus,        /* d- */
   C_H_Dash,         C_Nul,      C_Nul,   C_Nul,   // C_H_Minus,        /* H- */
   C_h_Dash,         C_Nul,      C_Nul,   C_Nul,   // C_h_Minus,        /* h- */
   C_P_Dash,         C_Nul,      C_Nul,   C_Nul,   // C_P_Minus,        /* P- */
   C_p_Dash,         C_Nul,      C_Nul,   C_Nul,   // C_p_Minus,        /* p- */

   C_NBSP,           C_Nul,      C_Nul,   C_Nul,   // C_NBSP,           /* No break space */

   C_Rouble,         C_Nul,      C_Nul,   C_Nul,   // C_Rouble,         /* rublis, $ Cyr */
   C_Pound,          C_Nul,      C_Nul,   C_Nul,   // C_Pound,          /* svaras, L/ */
   C_Yenna,          C_Nul,      C_Nul,   C_Nul,   // C_Yenna,          /* jena, Y- */
   C_cent,           C_Nul,      C_Nul,   C_Nul,   // C_cent,           /* c/ */

   C_Para,           C_Nul,      C_Nul,   C_Nul,   // C_Para,           /* paragrafas, # engl. */
   C_Pren,           C_Nul,      C_Nul,   C_Nul,   // C_Pren,           /* paragraph end sign (pastraipos pabaiga, C_pi - pi) */
   C_Multipl,        C_Nul,      C_Nul,   C_Nul,   // C_Multipl,        /* x */
   C_Divide,         C_Nul,      C_Nul,   C_Nul,   // C_Divide,         /* -:- */
   C_PlMin,          C_Nul,      C_Nul,   C_Nul,   // C_PlMin,          /* -+- */
   C_1up,            C_Nul,      C_Nul,   C_Nul,   // C_1up,            /* 1 virsuj */
   C_2up,            C_Nul,      C_Nul,   C_Nul,   // C_2up,            /* 2 virsuj, kvadratu */
   C_3up,            C_Nul,      C_Nul,   C_Nul,   // C_3up,            /* 3 virsuj, kubu */
   C_a_up,           C_Nul,      C_Nul,   C_Nul,   // C_a_up,           /* a virsuj */
   C_o_up,           C_Nul,      C_Nul,   C_Nul,   // C_o_up,           /* o virsuj */
   C_Half,           C_Nul,      C_Nul,   C_Nul,   // C_Half,           /* 1/2 */
   C_Quart,          C_Nul,      C_Nul,   C_Nul,   // C_Quart,          /* 1/4 */
   C_34,             C_Nul,      C_Nul,   C_Nul,   // C_34,             /* 3/4 */
   C_Ldopang,        C_Nul,      C_Nul,   C_Nul,   // C_Ldopang,        /* << - rusiska kabute */
   C_Rdopang,        C_Nul,      C_Nul,   C_Nul,   // C_Rdopang,        /* >> - rusiska kabute */
   C_Lang,           C_Nul,      C_Nul,   C_Nul,   // C_Lang,           /* < */
   C_Rang,           C_Nul,      C_Nul,   C_Nul,   // C_Rang,           /* > */
   C_Dvertl,         C_Nul,      C_Nul,   C_Nul,   // C_Dvertl,         /* | Koi-7-0 */
   C_Rminbr,         C_Nul,      C_Nul,   C_Nul,   // C_Rminbr,         /* ^ Koi-7-0 ( neiginys, -| ) */
   C_Lminbr,         C_Nul,      C_Nul,   C_Nul,   // C_Lminbr,         /* |- */
   C_Lpoint,         C_Nul,      C_Nul,   C_Nul,   // C_Lpoint,         /* mazas taskas vidury */
   C_Bpoint,         C_Nul,      C_Nul,   C_Nul,   // C_Bpoint,         /* bullet, didelis taskas vidury */
   C_LBquote,        C_Nul,      C_Nul,   C_Nul,   // C_LBquote,        /* ,, (" left bellow, double comma, liet. kaire) */
   C_LAquote,        C_Nul,      C_Nul,   C_Nul,   // C_LAquote,        /* '' (" left above, double comma above, angl. desine) */
   C_Rquote,         C_Nul,      C_Nul,   C_Nul,   // C_Rquote,         /* `` (" right, reversed double comma above, liet. desine, angl. kaire) */
   C_LBapost,        C_Nul,      C_Nul,   C_Nul,   // C_LBapost,        /* , (' left bellow, comma, liet. kaire) */
   C_LAapost,        C_Nul,      C_Nul,   C_Nul,   // C_LAapost,        /* ' (' left above, comma above, angl. desine) */
   C_Rapost,         C_Nul,      C_Nul,   C_Nul,   // C_Rapost,         /* ` (' right, grave, reversed comma above, liet. desine, angl. kaire) */

   C_Qst_Ov,         C_Nul,      C_Nul,   C_Nul,   // C_Qst_Ov,         /* apverstas ? */
   C_Ex_Ov,          C_Nul,      C_Nul,   C_Nul,   // C_Ex_Ov,          /* apverstas ! */
   C_Dots,           C_Nul,      C_Nul,   C_Nul,   // C_Dots,           /* ... daugtaskis */
   C_Prom,           C_Nul,      C_Nul,   C_Nul,   // C_Prom,           /* %o promiles */
   C_TM,             C_Nul,      C_Nul,   C_Nul,   // C_TM,             /* TM, Trade Mark */
   C_CO,             C_Nul,      C_Nul,   C_Nul,   // C_CO,             /* (C) Copyright */
   C_RO,             C_Nul,      C_Nul,   C_Nul,   // C_RO,             /* (R) */

                                                                        /* Additional greek chars, look SGML DTD */

   C_in,             C_Nul,      C_Nul,   C_Nul,   // C_epsilon_var,    // straight epsilon
   C_theta_var,      C_Nul,      C_Nul,   C_Nul,   // C_theta_var,      // curly theta
   C_DiGamma,        C_Nul,      C_Nul,   C_Nul,   // C_DiGamma,
   C_digamma,        C_Nul,      C_Nul,   C_Nul,   // C_digamma,
   C_kappa_var,      C_Nul,      C_Nul,   C_Nul,   // C_kappa_var,      // curly kappa
   C_DiLambda,       C_Nul,      C_Nul,   C_Nul,   // C_DiLambda,
   C_dilambda,       C_Nul,      C_Nul,   C_Nul,   // C_dilambda,
   C_pi_var,         C_Nul,      C_Nul,   C_Nul,   // C_pi_var,         // curly pi, like C_omega
   C_rho_var,        C_Nul,      C_Nul,   C_Nul,   // C_rho_var,        // curly rho
   C_Sigma_var,      C_Nul,      C_Nul,   C_Nul,   // C_Sigma_var,      // like "S"
   C_sigma_var,      C_Nul,      C_Nul,   C_Nul,   // C_sigma_var,      // final sigma, like "s"
   C_phi_var,        C_Nul,      C_Nul,   C_Nul,   // C_phi_var,        // curly phi

                                                                        // ----------------------------
                                                                        /* additional accents, all of them have no width (over the next letter) */

   C_GraveAcc,       C_Nul,      C_Nul,   C_Nul,   // C_GraveAcc,       /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   C_CircAcc,        C_Nul,      C_Nul,   C_Nul,   // C_CircAcc,        /* ^  Circumflex Accent (C_Circ), over the next letter */
   C_TildeAcc,       C_Nul,      C_Nul,   C_Nul,   // C_TildeAcc,       /* ~  Tilde (C_Tilde), over the next letter */
   C_BreveAcc,       C_Nul,      C_Nul,   C_Nul,   // C_BreveAcc,       /* u  (lankelis virsuje) */
   C_SlashAcc,       C_Nul,      C_Nul,   C_Nul,   // C_SlashAcc,       /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   C_BdotAcc,        C_Nul,      C_Nul,   C_Nul,   // C_BdotAcc,        /* .  Dot bellow */
   C_UnderlAcc,      C_Nul,      C_Nul,   C_Nul,   // C_UnderlAcc,      /* _  Underline (Pabraukimas) */

   C_prim,           C_Nul,      C_Nul,   C_Nul,   // C_prim,           /* strichas prie raides (C_Acute, C_Apost) */
   C_dprim,          C_Nul,      C_Nul,   C_Nul,   // C_dprim,          /* du strichai (C_Dacut) */

   C_Each,           C_Nul,      C_Nul,   C_Nul,   // C_Each,           /* V - "kiekvienam" - apversta A raide */
   C_Exists,         C_Nul,      C_Nul,   C_Nul,   // C_Exists,         /* E - "egzistuoja" - apversta E raide */

   C_Aleph,          C_Nul,      C_Nul,   C_Nul,   // C_Aleph,          /* N - alefas */
   C_Im,             C_Nul,      C_Nul,   C_Nul,   // C_Im,             /* C_I_Got */
   C_Re,             C_Nul,      C_Nul,   C_Nul,   // C_Re,             /* C_R_Got */
   C_wp,             C_Nul,      C_Nul,   C_Nul,   // C_wp,             /* C_p_Got */

   C_le,             C_Nul,      C_Nul,   C_Nul,   // C_le,             /* <= - maziau arba lygu */
   C_ge,             C_Nul,      C_Nul,   C_Nul,   // C_ge,             /* >= - daugiau arba lygu */
   C_ne,             C_Nul,      C_Nul,   C_Nul,   // C_ne,             /* =/= - nelygu */
   C_ll,             C_Nul,      C_Nul,   C_Nul,   // C_ll,             /* << */
   C_gg,             C_Nul,      C_Nul,   C_Nul,   // C_gg,             /* >> */
   C_sim,            C_Nul,      C_Nul,   C_Nul,   // C_sim,            /* ~ - panasu */
   C_simeq,          C_Nul,      C_Nul,   C_Nul,   // C_simeq,          /* ~- - panasu arba sutampa */
   C_approx,         C_Nul,      C_Nul,   C_Nul,   // C_approx,         /* ~~ - apytiksliai lygu */
   C_cong,           C_Nul,      C_Nul,   C_Nul,   // C_cong,           /* ~= - kongruentu */
   C_equiv,          C_Nul,      C_Nul,   C_Nul,   // C_equiv,          /* = - triguba lygybe - ekvivalentu */

   C_sqrt,           C_Nul,      C_Nul,   C_Nul,   // C_sqrt,           /* square root */
   C_int,            C_Nul,      C_Nul,   C_Nul,   // C_int,            /* integralas */
   C_oint,           C_Nul,      C_Nul,   C_Nul,   // C_oint,           /* kreivinis integralas */
   C_Sum,            C_Nul,      C_Nul,   C_Nul,   // C_Sum,            /* sum sign (C_Sigma) */
   C_Prod,           C_Nul,      C_Nul,   C_Nul,   // C_Prod,           /* C_Pi */
   C_O_times,        C_Nul,      C_Nul,   C_Nul,   // C_O_times,        /* OX - O perbraukta kryzmai */
   C_O_plus,         C_Nul,      C_Nul,   C_Nul,   // C_O_plus,         /* O+ - O perbraukta pliusu */

   C_infty,          C_Nul,      C_Nul,   C_Nul,   // C_infty,          /* infinity - begalybe */
   C_propto,         C_Nul,      C_Nul,   C_Nul,   // C_propto,         /* (C_alpha) */
   C_part,           C_Nul,      C_Nul,   C_Nul,   // C_part,           /* partial (C_delta) */
   C_empty,          C_Nul,      C_Nul,   C_Nul,   // C_empty,          /* O/ (C_O_Slash) */
   C_triangle,       C_Nul,      C_Nul,   C_Nul,   // C_triangle,       /* lygiakrastis trikampis, ~C_Delta */
   C_nabla,          C_Nul,      C_Nul,   C_Nul,   // C_nabla,          /* V - C_Delta apversta, lygiasonis siauras trikampis */

   C_perp,           C_Nul,      C_Nul,   C_Nul,   // C_perp,           /* T apversta - statmena */
   C_angle,          C_Nul,      C_Nul,   C_Nul,   // C_angle,          /* < - kampas (geom.) */

   C_langle,         C_Nul,      C_Nul,   C_Nul,   // C_langle,         /* < - skliaustas !!! keisti i C_Lang */
   C_rangle,         C_Nul,      C_Nul,   C_Nul,   // C_rangle,         /* > - skliaustas !!! keisti i C_Rang */

   C_cap,            C_Nul,      C_Nul,   C_Nul,   // C_cap,            /* U apversta - pjuvis */
   C_cup,            C_Nul,      C_Nul,   C_Nul,   // C_cup,            /* U - junginys */

   C_vee,            C_Nul,      C_Nul,   C_Nul,   // C_vee,            /* V */
   C_wedge,          C_Nul,      C_Nul,   C_Nul,   // C_wedge,          /* C_Lambda */

   C_supset,         C_Nul,      C_Nul,   C_Nul,   // C_supset,         /* D - virsaibis */
   C_supseteq,       C_Nul,      C_Nul,   C_Nul,   // C_supseteq,       /* D= - virsaibis arba sutampa */
   C_subset,         C_Nul,      C_Nul,   C_Nul,   // C_subset,         /* C - poaibis */
   C_subseteq,       C_Nul,      C_Nul,   C_Nul,   // C_subseteq,       /* C= - poaibis arba sutampa */
   C_nsubset,        C_Nul,      C_Nul,   C_Nul,   // C_nsubset,        /* C/ - nepoaibis */

   C_in,             C_Nul,      C_Nul,   C_Nul,   // C_in,             /* C_epsilon_var - priklauso */
   C_notin,          C_Nul,      C_Nul,   C_Nul,   // C_notin,          /* C_epsilon_var_Slash - nepriklauso */
   C_ni,             C_Nul,      C_Nul,   C_Nul,   // C_ni,             /* C_epsilon_var apsuktas - apima */

   C_leftarr,        C_Nul,      C_Nul,   C_Nul,   // C_leftarr,        /* <-- */
   C_rightarr,       C_Nul,      C_Nul,   C_Nul,   // C_rightarr,       /* --> */
   C_leftrightarr,   C_Nul,      C_Nul,   C_Nul,   // C_leftrightarr,   /* <--> */
   C_uparr,          C_Nul,      C_Nul,   C_Nul,   // C_uparr,          /* ^| */
   C_downarr,        C_Nul,      C_Nul,   C_Nul,   // C_downarr,        /* |v */
   C_updownarr,      C_Nul,      C_Nul,   C_Nul,   // C_updownarr,      /* ^|v */

   C_Leftarr,        C_Nul,      C_Nul,   C_Nul,   // C_Leftarr,        /* <== */
   C_Rightarr,       C_Nul,      C_Nul,   C_Nul,   // C_Rightarr,       /* ==> */
   C_Leftrightarr,   C_Nul,      C_Nul,   C_Nul,   // C_Leftrightarr,   /* <==> */
   C_Uparr,          C_Nul,      C_Nul,   C_Nul,   // C_Uparr,          /* ^|| */
   C_Downarr,        C_Nul,      C_Nul,   C_Nul,   // C_Downarr,        /* ||v */
   C_Updownarr,      C_Nul,      C_Nul,   C_Nul,   // C_Updownarr,      /* ^||v */

   C_mid,            C_Nul,      C_Nul,   C_Nul,   // C_mid,            /* | */
   C_paral,          C_Nul,      C_Nul,   C_Nul,   // C_paral,          /* || */

   C_diamond,        C_Nul,      C_Nul,   C_Nul,   // C_diamond,        /* tusciaviduris rombas */

   C_Club,           C_Nul,      C_Nul,   C_Nul,   // C_Club,           /* giles */
   C_Diamond,        C_Nul,      C_Nul,   C_Nul,   // C_Diamond,        /* bugnai, pilnaviduris rombas */
   C_Heart,          C_Nul,      C_Nul,   C_Nul,   // C_Heart,          /* cirvai sirdys */
   C_Spade,          C_Nul,      C_Nul,   C_Nul,   // C_Spade,          /* pikai lapai */

   C_hyph,           C_Nul,      C_Nul,   C_Nul,   // C_hyph,           /* hided hyphenation sign ("\-" for TEX) */
   C_break,          C_Nul,      C_Nul,   C_Nul,   // C_break,          /* line break character */

   C_a_Car,          C_Nul,      C_Nul,   C_Nul,   // C_a_Car,          /* av - laikinai, po to ismesti !!! */

   C_euro,           C_Nul,      C_Nul,   C_Nul,   // C_euro,           /* C= euro piniginis vienetas !!! kelti prie pinigu */

   C_deg,            C_Nul,      C_Nul,   C_Nul,   // C_deg,            /* degree - panasiai, kaip C_Ring, tik desineje */
   C_micro,          C_Nul,      C_Nul,   C_Nul,   // C_micro,          /* mikro - panasiai, kaip C_my */
   C_Ohm,            C_Nul,      C_Nul,   C_Nul,   // C_Ohm,            /* Ohm sign - panasiai, kaip C_Omega */
   C_Angst,          C_Nul,      C_Nul,   C_Nul,   // C_Angst,          /* Angstroem - C_A_Ring */

   C_Horl,           C_Nul,      C_Nul,   C_Nul,   // C_Horl,           /* horizontal line --- , C_h_b */

   C_Dag,            C_Nul,      C_Nul,   C_Nul,   // C_Dag,            /* Dagger +| (kryzius) */
   C_Ddag,           C_Nul,      C_Nul,   C_Nul,   // C_Ddag,           /* Double dagger +|+ (Kestucio kryzius) */

   C_ff,             C_Nul,      C_Nul,   C_Nul,   // C_ff,             /* ff ligature */
   C_fi,             C_Nul,      C_Nul,   C_Nul,   // C_fi,             /* fi ligature */
   C_fj,             C_Nul,      C_Nul,   C_Nul,   // C_fj,             /* fj ligature */
   C_ffi,            C_Nul,      C_Nul,   C_Nul,   // C_ffi,            /* ff ligature */
   C_ffl,            C_Nul,      C_Nul,   C_Nul,   // C_ffl,            /* ff ligature */
   C_fl,             C_Nul,      C_Nul,   C_Nul,   // C_fl,             /* ff ligature */

   C_and,            C_Nul,      C_Nul,   C_Nul,   // C_and,            /* ^ logical and */
   C_or,             C_Nul,      C_Nul,   C_Nul,   // C_or,             /* V logical or */

   C_fun,            C_Nul,      C_Nul,   C_Nul,   // C_fun,            /* f function of */

   C_MinPl,          C_Nul,      C_Nul,   C_Nul,   // C_MinPl,          /* -+ minus plus */

   C_EnDash,         C_Nul,      C_Nul,   C_Nul,   // C_EnDash,         /* -- - vidutinio ilgio bruksnys */
   C_EmDash,         C_Nul,      C_Nul,   C_Nul,   // C_EmDash,         /* --- - ilgas bruksnys */

   C_Cdots,          C_Nul,      C_Nul,   C_Nul,   // C_Cdots,          /* ... - daugtaskis per viduri */
   C_WideTilde,      C_Nul,      C_Nul,   C_Nul,   // C_WideTilde,      /* ~ didele tilde */

   C_QemSpc,         C_Nul,      C_Nul,   C_Nul,   // C_QemSpc,         /* 1/4 m space */
   C_EnSpc,          C_Nul,      C_Nul,   C_Nul,   // C_EnSpc,          /* n space */
   C_EmSpc,          C_Nul,      C_Nul,   C_Nul,   // C_EmSpc,          /* m space */
   C_2emSpc,         C_Nul,      C_Nul,   C_Nul,   // C_2emSpc,         /* 2 m space */

   C_NewPar,         C_Nul,      C_Nul,   C_Nul,   // C_NewPar,         /* paragraph end control character */

                                                                        // ----------------------------
                                                                        // lithuanian accented letters

   C_Y,              C_GraveAcc, C_Nul,   C_Nul,   // C_Y_Grave,        // Y`
   C_y,              C_GraveAcc, C_Nul,   C_Nul,   // C_y_Grave,        // y`
   C_E,              C_TildeAcc, C_Nul,   C_Nul,   // C_E_Tilde,        // E~
   C_e,              C_TildeAcc, C_Nul,   C_Nul,   // C_e_Tilde,        // e~
   C_I,              C_TildeAcc, C_Nul,   C_Nul,   // C_I_Tilde,        // I~
   C_i,              C_TildeAcc, C_Nul,   C_Nul,   // C_i_Tilde,        // i~
   C_U,              C_TildeAcc, C_Nul,   C_Nul,   // C_U_Tilde,        // U~
   C_u,              C_TildeAcc, C_Nul,   C_Nul,   // C_u_Tilde,        // u~
   C_Y,              C_TildeAcc, C_Nul,   C_Nul,   // C_Y_Tilde,        // Y~
   C_y,              C_TildeAcc, C_Nul,   C_Nul,   // C_y_Tilde,        // y~
   C_L,              C_TildeAcc, C_Nul,   C_Nul,   // C_L_Tilde,        // L~
   C_l,              C_TildeAcc, C_Nul,   C_Nul,   // C_l_Tilde,        // l~
   C_M,              C_TildeAcc, C_Nul,   C_Nul,   // C_M_Tilde,        // M~
   C_m,              C_TildeAcc, C_Nul,   C_Nul,   // C_m_Tilde,        // m~
   C_R,              C_TildeAcc, C_Nul,   C_Nul,   // C_R_Tilde,        // R~
   C_r,              C_TildeAcc, C_Nul,   C_Nul,   // C_r_Tilde,        // r~
   C_A_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_A_Ogon_Acute,
   C_a_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_a_Ogon_Acute,
   C_E_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_E_Ogon_Acute,
   C_e_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_e_Ogon_Acute,
   C_E_Adot,         C_Acute,    C_Nul,   C_Nul,   // C_E_Adot_Acute,
   C_e_Adot,         C_Acute,    C_Nul,   C_Nul,   // C_e_Adot_Acute,
   C_I_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_I_Ogon_Acute,
   C_i_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_i_Ogon_Acute,
   C_U_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_U_Ogon_Acute,
   C_u_Ogon,         C_Acute,    C_Nul,   C_Nul,   // C_u_Ogon_Acute,
   C_U_Macr,         C_Acute,    C_Nul,   C_Nul,   // C_U_Macr_Acute,
   C_u_Macr,         C_Acute,    C_Nul,   C_Nul,   // C_u_Macr_Acute,
   C_A_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_A_Ogon_Grave,
   C_a_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_a_Ogon_Grave,
   C_E_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_E_Ogon_Grave,
   C_e_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_e_Ogon_Grave,
   C_E_Adot,         C_GraveAcc, C_Nul,   C_Nul,   // C_E_Adot_Grave,
   C_e_Adot,         C_GraveAcc, C_Nul,   C_Nul,   // C_e_Adot_Grave,
   C_I_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_I_Ogon_Grave,
   C_i_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_i_Ogon_Grave,
   C_U_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_U_Ogon_Grave,
   C_u_Ogon,         C_GraveAcc, C_Nul,   C_Nul,   // C_u_Ogon_Grave,
   C_U_Macr,         C_GraveAcc, C_Nul,   C_Nul,   // C_U_Macr_Grave,
   C_u_Macr,         C_GraveAcc, C_Nul,   C_Nul,   // C_u_Macr_Grave,
   C_A_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_A_Ogon_Tilde,
   C_a_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_a_Ogon_Tilde,
   C_E_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_E_Ogon_Tilde,
   C_e_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_e_Ogon_Tilde,
   C_E_Adot,         C_TildeAcc, C_Nul,   C_Nul,   // C_E_Adot_Tilde,
   C_e_Adot,         C_TildeAcc, C_Nul,   C_Nul,   // C_e_Adot_Tilde,
   C_I_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_I_Ogon_Tilde,
   C_i_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_i_Ogon_Tilde,
   C_U_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_U_Ogon_Tilde,
   C_u_Ogon,         C_TildeAcc, C_Nul,   C_Nul,   // C_u_Ogon_Tilde,
   C_U_Macr,         C_TildeAcc, C_Nul,   C_Nul,   // C_U_Macr_Tilde,
   C_u_Macr,         C_TildeAcc, C_Nul,   C_Nul,   // C_u_Macr_Tilde,

                                                                        // ----------------------------
                                                                        // phonetic characters; vowels:

   C_ph_a,           C_Nul,      C_Nul,   C_Nul,   // C_ph_a,           // low back unrounded; a, open a; italic C_a

   C_ph_a_inv,       C_Nul,      C_Nul,   C_Nul,   // C_ph_a_inv,       // low back rounded; oa; inverted italic C_a

   C_ph_a_sh,        C_Nul,      C_Nul,   C_Nul,   // C_ph_a_sh,        // low-mid back unrounded; short a; inverted C_v
   C_ph_o_sh,        C_Nul,      C_Nul,   C_Nul,   // C_ph_o_sh,        // low-mid back rounded; short o, open o; inverted C_c
// C_ph_o,           C_Nul,      C_Nul,   C_Nul,   // C_ph_o,           // mid back rounded?; o, closed o; C_o

   C_ph_u_sh,        C_Nul,      C_Nul,   C_Nul,   // C_ph_u_sh,        // semi-high back rounded; short u, short open u; C_ypsilon
   C_ph_w_sh,        C_Nul,      C_Nul,   C_Nul,   // C_ph_w_sh,        // semi-high back rounded; short u, short open u, obsolete; C_omega
// C_ph_u,           C_Nul,      C_Nul,   C_Nul,   // C_ph_u,           // semi-high central rounded?; u, closed u; C_u
// C_ph_u_soft,      C_Nul,      C_Nul,   C_Nul,   // C_ph_u_soft,      // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   C_ph_e_sh,        C_Nul,      C_Nul,   C_Nul,   // C_ph_e_sh,        // low-mid front unrounded; short e, open e; C_epsilon
   C_ph_ae,          C_Nul,      C_Nul,   C_Nul,   // C_ph_ae,          // low front unrounded?; e, open e; C_ae
// C_ph_e_cl,        C_Nul,      C_Nul,   C_Nul,   // C_ph_e_cl,        // high central unrounded?; closed e, german e; C_e
   C_ph_e_sh_inv,    C_Nul,      C_Nul,   C_Nul,   // C_ph_e_sh_inv,    // low-mid central unrounded; hard e; inverted C_epsilon
   C_ph_e_inv,       C_Nul,      C_Nul,   C_Nul,   // C_ph_e_inv,       // mid central unrounded; reduced e; inverted C_e

   C_ph_i_sh,        C_Nul,      C_Nul,   C_Nul,   // C_ph_i_sh,        // semi-high front unrounded; short i, short open i; C_i without dot
// C_ph_i,           C_Nul,      C_Nul,   C_Nul,   // C_ph_i,           // high front unrounded?; i, closed i; C_i

                                                                        // ----------------------------
                                                                        // phonetic characters; consonants:

   C_ph_sh,          C_Nul,      C_Nul,   C_Nul,   // C_ph_sh,          // sh; C_f, C_int
   C_ph_zh,          C_Nul,      C_Nul,   C_Nul,   // C_ph_zh,          // zh; C_3
   C_ph_tsh,         C_Nul,      C_Nul,   C_Nul,   // C_ph_tsh,         // tsh; C_t C_f, C_t C_int
   C_ph_dzh,         C_Nul,      C_Nul,   C_Nul,   // C_ph_dzh,         // dzh; C_d C_3
   C_ph_th_b,        C_Nul,      C_Nul,   C_Nul,   // C_ph_th_b,        // breath th; C_theta
   C_ph_th_v,        C_Nul,      C_Nul,   C_Nul,   // C_ph_th_v,        // voiced th; C_delt_Mn, (C_delta_Minus)
   C_ph_ng,          C_Nul,      C_Nul,   C_Nul,   // C_ph_ng,          // nasal g; C_eta
   C_ph_g,           C_Nul,      C_Nul,   C_Nul,   // C_ph_g,           // g; italic C_g

                                                                        // ----------------------------
                                                                        // additional phonetic characters:

   C_ph_oe,          C_Nul,      C_Nul,   C_Nul,   // C_ph_oe,          // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   C_ph_o_slash,     C_Nul,      C_Nul,   C_Nul,   // C_ph_o_slash,     // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash; "o/"

   C_ph_a_l,         C_Nul,      C_Nul,   C_Nul,   // C_ph_a_l,         // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   C_ph_e_inv_l,     C_Nul,      C_Nul,   C_Nul,   // C_ph_e_inv_l,     // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   C_ph_i_l,         C_Nul,      C_Nul,   C_Nul,   // C_ph_i_l,         // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   C_ph_o_l,         C_Nul,      C_Nul,   C_Nul,   // C_ph_o_l,         // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   C_ph_u_l,         C_Nul,      C_Nul,   C_Nul,   // C_ph_u_l,         // ; u long; C_u C_Colon

   C_ph_a_n,         C_Nul,      C_Nul,   C_Nul,   // C_ph_a_n,         // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   C_ph_a_str_n,     C_Nul,      C_Nul,   C_Nul,   // C_ph_a_str_n,     // ; straight a nasal; a~, C_a_Tilde
   C_ph_e_n,         C_Nul,      C_Nul,   C_Nul,   // C_ph_e_n,         // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   C_ph_oe_n,        C_Nul,      C_Nul,   C_Nul,   // C_ph_oe_n,        // ; oe nasal; oe~, C_oe C_TildeAcc
   C_ph_o_n,         C_Nul,      C_Nul,   C_Nul,   // C_ph_o_n,         // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   C_ph_ch,          C_Nul,      C_Nul,   C_Nul,   // C_ph_ch,          // german ch; C_c_Cedil

                                                                        // ----------------------------
                                                                        // diphtongs

   C_ph_ai_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_ai_d,        // C_a C_LigaLow C_i
   C_ph_ae_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_ae_d,        // C_a C_LigaLow C_e
   C_ph_ao_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_ao_d,        // C_a C_LigaLow C_o
   C_ph_au_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_au_d,        // C_a C_LigaLow C_u
   C_ph_ei_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_ei_d,        // C_e C_LigaLow C_i
   C_ph_eu_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_eu_d,        // C_e C_LigaLow C_u
   C_ph_ie_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_ie_d,        // C_i C_LigaLow C_e
   C_ph_oe_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_oe_d,        // C_ph_o_sh C_LigaLow C_ph_o_slash
   C_ph_oy_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_oy_d,        // C_ph_o_sh C_LigaLow C_y
   C_ph_uo_d,        C_Nul,      C_Nul,   C_Nul,   // C_ph_uo_d,        // C_u C_LigaLow C_o

                                                                        // ----------------------------
                                                                        // breved phonetics

   C_ph_i_Brev,      C_Nul,      C_Nul,   C_Nul,   // C_ph_i_Brev,      // ; j; C_i_Brev
   C_ph_o_Brev,      C_Nul,      C_Nul,   C_Nul,   // C_ph_o_Brev,      //  C_o_Brev
   C_ph_u_Brev,      C_Nul,      C_Nul,   C_Nul,   // C_ph_u_Brev,      //  C_u_Brev

                                                                        // liga accents (for diphtongs)

   C_LigaUp,         C_Nul,      C_Nul,   C_Nul,   // C_LigaUp,         // lankelis virs dvieju raidziu
   C_LigaLow,        C_Nul,      C_Nul,   C_Nul,   // C_LigaLow,        // lankelis po dviem raidem

   C_MidRing,        C_Nul,      C_Nul,   C_Nul,   // C_MidRing,        // mazas apskritimas viduryje (tusciaviduris bulletas - kaip C_Bpoint)

                                                                        // phonetic accents

   C_ph_acc,         C_Nul,      C_Nul,   C_Nul,   // C_ph_acc,         // C_Apost
   C_ph_acc_low,     C_Nul,      C_Nul,   C_Nul,   // C_ph_acc_low,     // C_Comma

   C_square,         C_Nul,      C_Nul,   C_Nul,   // C_square,         // tusciaviduris kvadratas viduryje

   C_male,           C_Nul,      C_Nul,   C_Nul,   // C_male,           // vyr. lytis, male sex, mars, o^
   C_female,         C_Nul,      C_Nul,   C_Nul,   // C_female,         // mot. lytis, female sex, venus, o+

   C_O_ring,         C_Nul,      C_Nul,   C_Nul,   // C_O_ring,         // Oo - mazas apskritimas O viduje
   C_O_dot,          C_Nul,      C_Nul,   C_Nul,   // C_O_dot,          // O. - taskas O viduje

   C_BigRing,        C_Nul,      C_Nul,   C_Nul,   // C_BigRing,        // didelis apskritimas, C_O

   C_longleftarr,    C_Nul,      C_Nul,   C_Nul,   // C_longleftarr,    /* <---- */
   C_longrightarr,   C_Nul,      C_Nul,   C_Nul,   // C_longrightarr,   /* ----> */

   C_smile,          C_Nul,      C_Nul,   C_Nul,   // C_smile,          // lankas, ~C_LigaLow

   C_box,            C_Nul,      C_Nul,   C_Nul,   // C_box,            // pilnaviduris kvadratas viduryje, square bullet

                                                                        // ----------------------------
                                                                        // DOS frames

   C_v_b,            C_Nul,      C_Nul,   C_Nul,   // C_v_b,            // vert; ne DOS-e - C_Vertl
   C_h_b,            C_Nul,      C_Nul,   C_Nul,   // C_h_b,            // hor; ne DOS-e - C_Horl
   C_vh_b,           C_Nul,      C_Nul,   C_Nul,   // C_vh_b,           // vert hor
   C_vl_b,           C_Nul,      C_Nul,   C_Nul,   // C_vl_b,           // vert left
   C_vr_b,           C_Nul,      C_Nul,   C_Nul,   // C_vr_b,           // vert right
   C_hu_b,           C_Nul,      C_Nul,   C_Nul,   // C_hu_b,           // hor up
   C_hd_b,           C_Nul,      C_Nul,   C_Nul,   // C_hd_b,           // hor down
   C_ul_b,           C_Nul,      C_Nul,   C_Nul,   // C_ul_b,           // up left
   C_dl_b,           C_Nul,      C_Nul,   C_Nul,   // C_dl_b,           // down left
   C_ur_b,           C_Nul,      C_Nul,   C_Nul,   // C_ur_b,           // up right
   C_dr_b,           C_Nul,      C_Nul,   C_Nul,   // C_dr_b,           // down right

   C_2v_b,           C_Nul,      C_Nul,   C_Nul,   // C_2v_b,           // double vert; C_paral
   C_2h_b,           C_Nul,      C_Nul,   C_Nul,   // C_2h_b,           // double hor
   C_2v2h_b,         C_Nul,      C_Nul,   C_Nul,   // C_2v2h_b,         // double vert double hor
   C_2v2l_b,         C_Nul,      C_Nul,   C_Nul,   // C_2v2l_b,         // double vert double left
   C_2v2r_b,         C_Nul,      C_Nul,   C_Nul,   // C_2v2r_b,         // double vert double right
   C_2h2u_b,         C_Nul,      C_Nul,   C_Nul,   // C_2h2u_b,         // double hor double up
   C_2h2d_b,         C_Nul,      C_Nul,   C_Nul,   // C_2h2d_b,         // double hor double down
   C_2u2l_b,         C_Nul,      C_Nul,   C_Nul,   // C_2u2l_b,         // double up double left
   C_2d2l_b,         C_Nul,      C_Nul,   C_Nul,   // C_2d2l_b,         // double down double left
   C_2u2r_b,         C_Nul,      C_Nul,   C_Nul,   // C_2u2r_b,         // double up double right
   C_2d2r_b,         C_Nul,      C_Nul,   C_Nul,   // C_2d2r_b,         // double down double right

   C_2vh_b,          C_Nul,      C_Nul,   C_Nul,   // C_2vh_b,          // double vert hor
   C_2vl_b,          C_Nul,      C_Nul,   C_Nul,   // C_2vl_b,          // double vert left
   C_2vr_b,          C_Nul,      C_Nul,   C_Nul,   // C_2vr_b,          // double vert right
   C_h2u_b,          C_Nul,      C_Nul,   C_Nul,   // C_h2u_b,          // hor double up
   C_h2d_b,          C_Nul,      C_Nul,   C_Nul,   // C_h2d_b,          // hor double down
   C_2ul_b,          C_Nul,      C_Nul,   C_Nul,   // C_2ul_b,          // double up left
   C_2dl_b,          C_Nul,      C_Nul,   C_Nul,   // C_2dl_b,          // double down left
   C_2ur_b,          C_Nul,      C_Nul,   C_Nul,   // C_2ur_b,          // double up right
   C_2dr_b,          C_Nul,      C_Nul,   C_Nul,   // C_2dr_b,          // double down right

   C_v2h_b,          C_Nul,      C_Nul,   C_Nul,   // C_v2h_b,          // vert double hor
   C_v2l_b,          C_Nul,      C_Nul,   C_Nul,   // C_v2l_b,          // vert double left
   C_v2r_b,          C_Nul,      C_Nul,   C_Nul,   // C_v2r_b,          // vert double right
   C_2hu_b,          C_Nul,      C_Nul,   C_Nul,   // C_2hu_b,          // double hor up
   C_2hd_b,          C_Nul,      C_Nul,   C_Nul,   // C_2hd_b,          // double hor down
   C_u2l_b,          C_Nul,      C_Nul,   C_Nul,   // C_u2l_b,          // up double left
   C_d2l_b,          C_Nul,      C_Nul,   C_Nul,   // C_d2l_b,          // down double left
   C_u2r_b,          C_Nul,      C_Nul,   C_Nul,   // C_u2r_b,          // up double right
   C_d2r_b,          C_Nul,      C_Nul,   C_Nul,   // C_d2r_b,          // down double right

   C_block,          C_Nul,      C_Nul,   C_Nul,   // C_block,          // pilnaviduris kvadratas per visa laukeli
   C_dgrblk,         C_Nul,      C_Nul,   C_Nul,   // C_dgrblk,         // tamsiai pilkas ---//--- (75% shaded)
   C_grblk,          C_Nul,      C_Nul,   C_Nul,   // C_grblk,          // pilkas ---//--- (50% shaded)
   C_lgrblk,         C_Nul,      C_Nul,   C_Nul,   // C_lgrblk,         // sviesiai pilkas ---//--- (25% shaded)
   C_uphblk,         C_Nul,      C_Nul,   C_Nul,   // C_uphblk,         // pilnaviduris staciakampis per puse laukelio virsuje
   C_dnhblk,         C_Nul,      C_Nul,   C_Nul,   // C_dnhblk,         // ---//--- apacioje
   C_lthblk,         C_Nul,      C_Nul,   C_Nul,   // C_lthblk,         // ---//--- kaireje
   C_rthblk,         C_Nul,      C_Nul,   C_Nul,   // C_rthblk,         // ---//--- desineje

   C_utrif,          C_Nul,      C_Nul,   C_Nul,   // C_utrif,          // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   C_dtrif,          C_Nul,      C_Nul,   C_Nul,   // C_dtrif,          // pilnaviduris trikampis zemyn
   C_ltrif,          C_Nul,      C_Nul,   C_Nul,   // C_ltrif,          // pilnaviduris trikampis i kaire
   C_rtrif,          C_Nul,      C_Nul,   C_Nul,   // C_rtrif,          // pilnaviduris trikampis i desine

   C_ph_uu_sh,       C_Nul,      C_Nul,   C_Nul,   // C_ph_uu_sh,       // phonetics: semi-high back rounded; short u, short open u; inverted C_Omega

   C_hhyph,          C_Nul,      C_Nul,   C_Nul,   // C_hhyph,          // hard hyphen - zodzio kelimas per prievarta -\break
   C_sbreak,         C_Nul,      C_Nul,   C_Nul,   // C_sbreak,         // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   C_hSpc,           C_Nul,      C_Nul,   C_Nul,   // C_hSpc,           // hard space - technical space after TEX commands - do not process
   C_hbreak,         C_Nul,      C_Nul,   C_Nul,   // C_hbreak,         // break su \hfill, xmlsty keiciamas is C_Cr ("\r")
   C_lSpc,           C_Nul,      C_Nul,   C_Nul,   // C_lSpc,           // last space - space, to be changed to C_NBSP after LAST_WORD_LEN
   C_hlSpc,          C_Nul,      C_Nul,   C_Nul,   // C_hlSpc,          // hard last space - C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   C_utrif_rtf,      C_Nul,      C_Nul,   C_Nul,   // C_utrif_rtf,          // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   C_dtrif_rtf,      C_Nul,      C_Nul,   C_Nul,   // C_dtrif_rtf,          // pilnaviduris trikampis zemyn
   C_ltrif_rtf,      C_Nul,      C_Nul,   C_Nul,   // C_ltrif_rtf,          // pilnaviduris trikampis i kaire
   C_rtrif_rtf,      C_Nul,      C_Nul,   C_Nul,   // C_rtrif_rtf,          // pilnaviduris trikampis i desine

// erdvines rodykles
   C_3DTopLightLeftArrowHead,   C_Nul,      C_Nul,   C_Nul,   // C_3DTopLightLeftArrowHead,
   C_3DBotLightLeftArrowHead,   C_Nul,      C_Nul,   C_Nul,   // C_3DBotLightLeftArrowHead,
   C_3DTopLightRightArrowHead,  C_Nul,      C_Nul,   C_Nul,   // C_3DTopLightRightArrowHead,
   C_3DBotLightRightArrowHead,  C_Nul,      C_Nul,   C_Nul,   // C_3DBotLightRightArrowHead,
   C_3DLeftLightUpArrowHead,    C_Nul,      C_Nul,   C_Nul,   // C_3DLeftLightUpArrowHead,
   C_3DRightLightUpArrowHead,   C_Nul,      C_Nul,   C_Nul,   // C_3DRightLightUpArrowHead,
   C_3DLeftLightDownArrowHead,  C_Nul,      C_Nul,   C_Nul,   // C_3DLeftLightDownArrowHead,
   C_3DRightLightDownArrowHead, C_Nul,      C_Nul,   C_Nul,   // C_3DRightLightDownArrowHead,

   C_MinusMath,      C_Nul,      C_Nul,   C_Nul,   //  C_Minus

   C_ZeroWidthSpace, C_Nul,      C_Nul,   C_Nul,   //  C_ZeroWidthSpace

   C_ph_glot_stop,   C_Nul,      C_Nul,   C_Nul,   //  C_ph_glot_stop

   C_AcuteNcomb,     C_Nul,      C_Nul,   C_Nul,   //  C_AcuteNcomb
   C_CedilNcomb,     C_Nul,      C_Nul,   C_Nul,   //  C_CedilNcomb
   C_MacrNcomb,      C_Nul,      C_Nul,   C_Nul,   //  C_MacrNcomb

   C_DollNctrl,      C_Nul,      C_Nul,   C_Nul,   //  C_DollNctrl

   C_OgonNcomb,      C_Nul,      C_Nul,   C_Nul,   //  C_OgonNcomb

   C_No,             C_Nul,      C_Nul,   C_Nul,   //  C_No

   C_CarNcomb,       C_Nul,      C_Nul,   C_Nul,   // C_CarNcomb
   C_DiaerNcomb,     C_Nul,      C_Nul,   C_Nul,   // C_DiaerNcomb
   C_TildeNcomb,     C_Nul,      C_Nul,   C_Nul,   // C_TildeNcomb

   C_utri,           C_Nul,      C_Nul,   C_Nul,   // C_utri
   C_dtri,           C_Nul,      C_Nul,   C_Nul,   // C_dtri
   C_ltri,           C_Nul,      C_Nul,   C_Nul,   // C_ltri
   C_rtri,           C_Nul,      C_Nul,   C_Nul,   // C_rtri

   C_Oline,          C_Nul,      C_Nul,   C_Nul,   // C_Oline

   C_R_Oline,        C_Nul,      C_Nul,   C_Nul,   // C_R_Oline
   C_X_Oline,        C_Nul,      C_Nul,   C_Nul,   // C_X_Oline

   C_leqslant,       C_Nul,      C_Nul,   C_Nul,   // C_leqslant
   C_geqslant,       C_Nul,      C_Nul,   C_Nul,   // C_geqslant

   C_i_Grave_Dotless, C_Nul,     C_Nul,   C_Nul,   // C_i_Grave_Dotless
   C_i_Acute_Dotless, C_Nul,     C_Nul,   C_Nul,   // C_i_Acute_Dotless
   C_i_Tilde_Dotless, C_Nul,     C_Nul,   C_Nul,   // C_i_Tilde_Dotless

//------------------------- accented cyrillic
   C_A_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_A_Cyr_Acute
   C_E_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_E_Cyr_Acute
   C_I_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_I_Cyr_Acute
   C_O_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_O_Cyr_Acute
   C_U_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_U_Cyr_Acute
   C_Y_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_Y_Cyr_Acute
   C_Ee_Cyr,         C_Acute,    C_Nul,   C_Nul,   // C_Ee_Cyr_Acute
   C_Yu_Cyr,         C_Acute,    C_Nul,   C_Nul,   // C_Yu_Cyr_Acute
   C_Ya_Cyr,         C_Acute,    C_Nul,   C_Nul,   // C_Ya_Cyr_Acute

   C_a_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_a_Cyr_Acute
   C_e_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_e_Cyr_Acute
   C_i_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_i_Cyr_Acute
   C_o_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_o_Cyr_Acute
   C_u_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_u_Cyr_Acute
   C_y_Cyr,          C_Acute,    C_Nul,   C_Nul,   // C_y_Cyr_Acute
   C_ee_Cyr,         C_Acute,    C_Nul,   C_Nul,   // C_ee_Cyr_Acute
   C_yu_Cyr,         C_Acute,    C_Nul,   C_Nul,   // C_yu_Cyr_Acute
   C_ya_Cyr,         C_Acute,    C_Nul,   C_Nul,   // C_ya_Cyr_Acute

   C_NullSpc,        C_Nul,      C_Nul,   C_Nul,   // C_NullSpc

   C_Dash,           C_Diaer,    C_Nul,   C_Nul,   // C_Dash_Diaer

   C_bdiamond,       C_Nul,      C_Nul,   C_Nul,   // C_diamond /* tusciaviduris rombas */

   C_DegCels,        C_Nul,      C_Nul,   C_Nul,   // C_DegCels /* degree Celsius - celsijaus laipsniai, C_deg C_C */

   C_hBpoint,        C_Nul,      C_Nul,   C_Nul,   // C_hBpoint         /* bullet, didelis taskas vidury */

   C_Fita_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_Fita_Cyr
   C_fita_Cyr,       C_Nul,      C_Nul,   C_Nul,   // C_fita_Cyr
   C_Yat_Cyr,        C_Nul,      C_Nul,   C_Nul,   // C_Yat_Cyr
   C_yat_Cyr,        C_Nul,      C_Nul,   C_Nul,   // C_yat_Cyr

   C_checkmark,      C_Nul,      C_Nul,   C_Nul,   // C_checkmark

   C_prim_Ncomb,     C_Nul,      C_Nul,   C_Nul,   // C_prim_Ncomb 
   C_dprim_Ncomb,    C_Nul,      C_Nul,   C_Nul,   // C_dprim_Ncomb
    
};

