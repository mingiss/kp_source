// ==================================================
// tvtexc.cpp
// TEX spec. chars tags


// ================================================== definitions
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

#if Compiler != Watcom
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptt.h"
#include "kpsort.h"
#include "tvmain.h"
#include "tvtex.h"


// ===================================================
unsigned const char *plpszaTexSpecCharTags[C_CharArrSize44] =      // TEX spec char tags for Chars16
{
   (unsigned char *)NULL,    //   C_Nul,     /* 0x00 */
   (unsigned char *)NULL,    //   C_Soh,     /* 0x01 */
   (unsigned char *)NULL,    //   C_Stx,     /* 0x02 */
   (unsigned char *)NULL,    //   C_Etx,     /* 0x03 */
   (unsigned char *)NULL,    //   C_Eot,     /* 0x04 */
   (unsigned char *)NULL,    //   C_Enq,     /* 0x05 */
   (unsigned char *)NULL,    //   C_Ack,     /* 0x06 */
   (unsigned char *)NULL,    //   C_Bel,     /* 0x07 */
   (unsigned char *)NULL,    //   C_Bs,      /* 0x08 */
   (unsigned char *)NULL,    //   C_Ht,      /* 0x09 */
   (unsigned char *)"\\\n",  //   C_Lf,      /* 0x0a */  // !!! depends on file system
   (unsigned char *)NULL,    //   C_Vt,      /* 0x0b */
   (unsigned char *)NULL,    //   C_Ff,      /* 0x0c */
   (unsigned char *)NULL,    //   C_Cr,      /* 0x0d */
   (unsigned char *)NULL,    //   C_So,      /* 0x0e */
   (unsigned char *)NULL,    //   C_Si,      /* 0x0f */
   (unsigned char *)NULL,    //   C_Dle,     /* 0x10 */
   (unsigned char *)NULL,    //   C_Dc1,     /* 0x11 */
   (unsigned char *)NULL,    //   C_Dc2,     /* 0x12 */
   (unsigned char *)NULL,    //   C_Dc3,     /* 0x13 */
   (unsigned char *)NULL,    //   C_Dc4,     /* 0x14 */
   (unsigned char *)NULL,    //   C_Nak,     /* 0x15 */
   (unsigned char *)NULL,    //   C_Syn,     /* 0x16 */
   (unsigned char *)NULL,    //   C_Etb,     /* 0x17 */
   (unsigned char *)NULL,    //   C_Can,     /* 0x18 */
   (unsigned char *)NULL,    //   C_Em,      /* 0x19 */
   (unsigned char *)NULL,    //   C_Sub,     /* 0x1a */
   (unsigned char *)NULL,    //   C_Esc,     /* 0x1b */
   (unsigned char *)NULL,    //   C_Fs,      /* 0x1c */
   (unsigned char *)NULL,    //   C_Gs,      /* 0x1d */
   (unsigned char *)NULL,    //   C_Rs,      /* 0x1e */
   (unsigned char *)NULL,    //   C_Us,      /* 0x1f */

   (unsigned char *)" ",     //   C_Spc,     /* Space */
   (unsigned char *)"!",     //   C_Excl,    /* !  Exclamation Mark (s/auktukas) */
   (unsigned char *)"\"",    //   C_Quote,   /* "  Quotation Mark (kabute%s) */
   (unsigned char *)"\\#",   //   C_Numb,    /* #  Number Sign (Numerio zenklas) */
   (unsigned char *)"\\$",   //   C_Doll,    /* $  Currency Sign (Pinigu zenklas) */
   (unsigned char *)"\\%",   //   C_Perc,    /* %  Per Cent Sign (procento z/enklas) */
   (unsigned char *)"\\&",   //   C_Amp,     /* &  Ampersand (Ampersandas) */
   (unsigned char *)"\'",    //   C_Apost,   /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   (unsigned char *)"(",     //   C_Lpar,    /* (  Left Parenthesis (kairysis skliaustas) */
   (unsigned char *)")",     //   C_Rpar,    /* )  Right Parenthesis (des/inysis skliaustas) */
   (unsigned char *)"*",     // !!! C_Ast,   /* *  Asterisk (Zvaigzdute) */
   (unsigned char *)"+",     //   C_Plus,    /* +  Plus Sign (pliusas) */
   (unsigned char *)",",     //   C_Comma,   /* ,  Comma (kablelis) */
   (unsigned char *)"-",     // "\\dash", nereikia - ir taip jau keièia á TX_TG_dash // "-" negerai, nes per já lûþta eilutë;  C_Minus,   /* -  Hyphen, Minus Sign (minusas) */
   (unsigned char *)".",     //   C_Point,   /* .  Full Stop, Period, Point (tas/kas) */
   (unsigned char *)"/",     //   C_Slash,   /* /  Slash, Solidus (Istrizas bruksnys) */
   (unsigned char *)"0",     //   C_0,       /* 0 */
   (unsigned char *)"1",     //   C_1,       /* 1 */
   (unsigned char *)"2",     //   C_2,       /* 2 */
   (unsigned char *)"3",     //   C_3,       /* 3 */
   (unsigned char *)"4",     //   C_4,       /* 4 */
   (unsigned char *)"5",     //   C_5,       /* 5 */
   (unsigned char *)"6",     //   C_6,       /* 6 */
   (unsigned char *)"7",     //   C_7,       /* 7 */
   (unsigned char *)"8",     //   C_8,       /* 8 */
   (unsigned char *)"9",     //   C_9,       /* 9 */
   (unsigned char *)"\\colon", //   C_Colon,   /* :  Colon (dvitas/kis) */
   (unsigned char *)";",     //   C_Semic,   /* ;  Semi-colon (kabliatas/kis) */
   (unsigned char *)"<",     //   C_Less,    /* <  Less than Sign (maz/iau) */
   (unsigned char *)"=",     //   C_Eq,      /* =  Equals Sign (lygybe%s z/enklas) */

   (unsigned char *)">",     //   C_Great,   /* >  Greater than Sign (daugiau) */
   (unsigned char *)"?",     //   C_Quest,   /* ?  Question Mark (klaustukas) */

   (unsigned char *)"\\@",   //   C_At,      /* @  Commercial At (Prekybinis zenklas "Pas") */
   (unsigned char *)"A",     //   C_A,       /* A */
   (unsigned char *)"B",     //   C_B,       /* B */
   (unsigned char *)"C",     //   C_C,       /* C */
   (unsigned char *)"D",     //   C_D,       /* D */
   (unsigned char *)"E",     //   C_E,       /* E */
   (unsigned char *)"F",     //   C_F,       /* F */
   (unsigned char *)"G",     //   C_G,       /* G */
   (unsigned char *)"H",     //   C_H,       /* H */
   (unsigned char *)"I",     //   C_I,       /* I */
   (unsigned char *)"J",     //   C_J,       /* J */
   (unsigned char *)"K",     //   C_K,       /* K */
   (unsigned char *)"L",     //   C_L,       /* L */
   (unsigned char *)"M",     //   C_M,       /* M */
   (unsigned char *)"N",     //   C_N,       /* N */
   (unsigned char *)"O",     //   C_O,       /* O */
   (unsigned char *)"P",     //   C_P,       /* P */
   (unsigned char *)"Q",     //   C_Q,       /* Q */
   (unsigned char *)"R",     //   C_R,       /* R */
   (unsigned char *)"S",     //   C_S,       /* S */
   (unsigned char *)"T",     //   C_T,       /* T */
   (unsigned char *)"U",     //   C_U,       /* U */
   (unsigned char *)"V",     //   C_V,       /* V */
   (unsigned char *)"W",     //   C_W,       /* W */
   (unsigned char *)"X",     //   C_X,       /* X */
   (unsigned char *)"Y",     //   C_Y,       /* Y */
   (unsigned char *)"Z",     //   C_Z,       /* Z */
   (unsigned char *)"[",     //   C_Lbrack,  /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   (unsigned char *)"\\backslash",//  C_Lslash,  /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   (unsigned char *)"]",     //   C_Rbrack,  /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   (unsigned char *)"\\^{}", //   C_Circ,    /* ^  Circumflex Accent (Cirkumfleksas) */
   (unsigned char *)"\\_",   //   C_Underl,  /* _  Underline (Pabraukimas) */

   (unsigned char *)"`",     //   C_Grave,   /* `  Grave Accent (gravis) */
   (unsigned char *)"a",     //   C_a,       /* a */
   (unsigned char *)"b",     //   C_b,       /* b */
   (unsigned char *)"c",     //   C_c,       /* c */
   (unsigned char *)"d",     //   C_d,       /* d */
   (unsigned char *)"e",     //   C_e,       /* e */
   (unsigned char *)"f",     //   C_f,       /* f */
   (unsigned char *)"g",     //   C_g,       /* g */
   (unsigned char *)"h",     //   C_h,       /* h */
   (unsigned char *)"i",     //   C_i,       /* i */
   (unsigned char *)"j",     //   C_j,       /* j */
   (unsigned char *)"k",     //   C_k,       /* k */
   (unsigned char *)"l",     //   C_l,       /* l */
   (unsigned char *)"m",     //   C_m,       /* m */
   (unsigned char *)"n",     //   C_n,       /* n */
   (unsigned char *)"o",     //   C_o,       /* o */
   (unsigned char *)"p",     //   C_p,       /* p */
   (unsigned char *)"q",     //   C_q,       /* q */
   (unsigned char *)"r",     //   C_r,       /* r */
   (unsigned char *)"s",     //   C_s,       /* s */
   (unsigned char *)"t",     //   C_t,       /* t */
   (unsigned char *)"u",     //   C_u,       /* u */
   (unsigned char *)"v",     //   C_v,       /* v */
   (unsigned char *)"w",     //   C_w,       /* w */
   (unsigned char *)"x",     //   C_x,       /* x */
   (unsigned char *)"y",     //   C_y,       /* y */
   (unsigned char *)"z",     //   C_z,       /* z */
   (unsigned char *)"\\{",   //   C_Lcurl,   /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   (unsigned char *)"|",     //   C_Vertl,   /* |  Vertical Line (Vertikali Linija) */
   (unsigned char *)"\\}",   //   C_Rcurl,   /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   (unsigned char *)"\\Tilde",// "\\~{}", //  C_Tilde,   /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje) */

   (unsigned char *)NULL,    //   C_Del,

   (unsigned char *)"\\AE",  //   C_AE,
   (unsigned char *)"\\ae",  //   C_ae,
   (unsigned char *)"\\OE",  //   C_OE,
   (unsigned char *)"\\oe",  //   C_oe,
   (unsigned char *)NULL,    //   C_IJ,
   (unsigned char *)NULL,    //   C_ij,
   (unsigned char *)"\\ss",  //   C_ss,      /* sharp s    (german) (C_beta) */

   (unsigned char *)"\\Acy",     //     C_A_Cyr,
   (unsigned char *)"\\Bcy",     //     C_B_Cyr,
   (unsigned char *)"\\Vcy",     //     C_V_Cyr,
   (unsigned char *)"\\Gcy",     //     C_G_Cyr,
   (unsigned char *)"\\Dcy",     //     C_D_Cyr,
   (unsigned char *)"\\IEcy",    //     C_E_Cyr,
   (unsigned char *)"\\ZHcy",    //     C_Zh_Cyr,
   (unsigned char *)"\\Zcy",     //     C_Z_Cyr,
   (unsigned char *)"\\Icy",     //     C_I_Cyr,
   (unsigned char *)"\\Jcy",     //     C_J_Cyr,
   (unsigned char *)"\\Kcy",     //     C_K_Cyr,
   (unsigned char *)"\\Lcy",     //     C_L_Cyr,
   (unsigned char *)"\\Mcy",     //     C_M_Cyr,
   (unsigned char *)"\\Ncy",     //     C_N_Cyr,
   (unsigned char *)"\\Ocy",     //     C_O_Cyr,
   (unsigned char *)"\\Pcy",     //     C_P_Cyr,
   (unsigned char *)"\\Rcy",     //     C_R_Cyr,
   (unsigned char *)"\\Scy",     //     C_S_Cyr,
   (unsigned char *)"\\Tcy",     //     C_T_Cyr,
   (unsigned char *)"\\Ucy",     //     C_U_Cyr,
   (unsigned char *)"\\Fcy",     //     C_F_Cyr,
   (unsigned char *)"\\KHcy",    //     C_H_Cyr,
   (unsigned char *)"\\TScy",    //     C_C_Cyr,
   (unsigned char *)"\\CHcy",    //     C_Ch_Cyr,
   (unsigned char *)"\\SHcy",    //     C_Sh_Cyr,
   (unsigned char *)"\\SHCHcy",  //     C_Shch_Cyr,
   (unsigned char *)"\\HARDcy",  //     C_Hard_Cyr,
   (unsigned char *)"\\Ycy",     //     C_Y_Cyr,
   (unsigned char *)"\\SOFTcy",  //     C_Soft_Cyr,
   (unsigned char *)"\\Ecy",     //     C_Ee_Cyr,
   (unsigned char *)"\\YUcy",    //     C_Ju_Cyr,
   (unsigned char *)"\\YAcy",    //     C_Ja_Cyr,

   (unsigned char *)"\\acy",     //     C_a_Cyr,
   (unsigned char *)"\\bcy",     //     C_b_Cyr,
   (unsigned char *)"\\vcy",     //     C_v_Cyr,
   (unsigned char *)"\\gcy",     //     C_g_Cyr,
   (unsigned char *)"\\dcy",     //     C_d_Cyr,
   (unsigned char *)"\\iecy",    //     C_e_Cyr,
   (unsigned char *)"\\zhcy",    //     C_zh_Cyr,
   (unsigned char *)"\\zcy",     //     C_z_Cyr,
   (unsigned char *)"\\icy",     //     C_i_Cyr,
   (unsigned char *)"\\jcy",     //     C_j_Cyr,
   (unsigned char *)"\\kcy",     //     C_k_Cyr,
   (unsigned char *)"\\lcy",     //     C_l_Cyr,
   (unsigned char *)"\\mcy",     //     C_m_Cyr,
   (unsigned char *)"\\ncy",     //     C_n_Cyr,
   (unsigned char *)"\\ocy",     //     C_o_Cyr,
   (unsigned char *)"\\pcy",     //     C_p_Cyr,
   (unsigned char *)"\\rcy",     //     C_r_Cyr,
   (unsigned char *)"\\scy",     //     C_s_Cyr,
   (unsigned char *)"\\tcy",     //     C_t_Cyr,
   (unsigned char *)"\\ucy",     //     C_u_Cyr,
   (unsigned char *)"\\fcy",     //     C_f_Cyr,
   (unsigned char *)"\\khcy",    //     C_h_Cyr,
   (unsigned char *)"\\tscy",    //     C_c_Cyr,
   (unsigned char *)"\\chcy",    //     C_ch_Cyr,
   (unsigned char *)"\\shcy",    //     C_sh_Cyr,
   (unsigned char *)"\\shchcy",  //     C_shch_Cyr,
   (unsigned char *)"\\hardcy",  //     C_hard_Cyr,
   (unsigned char *)"\\ycy",     //     C_y_Cyr,
   (unsigned char *)"\\softcy",  //     C_soft_Cyr,
   (unsigned char *)"\\ecy",     //     C_ee_Cyr,
   (unsigned char *)"\\yucy",    //     C_ju_Cyr,
   (unsigned char *)"\\yacy",    //     C_ja_Cyr,

                              //    /* Additional greek chars variations follow later */
   (unsigned char *)NULL,     //     C_Alpha,
   (unsigned char *)NULL,     //     C_Beta,
   (unsigned char *)"\\Gamma",   //     C_Gamma,
   (unsigned char *)"\\Delta",   //     C_Delta,
   (unsigned char *)NULL,     //     C_Epsilon,
   (unsigned char *)NULL,     //     C_Zeta,
   (unsigned char *)NULL,     //     C_Eta,
   (unsigned char *)"\\Theta",   //     C_Theta,
   (unsigned char *)NULL,     //     C_Jota,
   (unsigned char *)NULL,     //     C_Kappa,
   (unsigned char *)"\\Lambda",  //     C_Lambda,
   (unsigned char *)NULL,     //     C_My,
   (unsigned char *)NULL,     //     C_Ny,
   (unsigned char *)"\\Xi",      //     C_Xi,
   (unsigned char *)NULL,     //     C_Omikron,
   (unsigned char *)"\\Pi",      //     C_Pi,
   (unsigned char *)NULL,     //     C_Rho,
   (unsigned char *)"\\Sigma",   //     C_Sigma,
   (unsigned char *)NULL,     //     C_Tau,
   (unsigned char *)"\\Upsilon", //     C_Ypsilon,
   (unsigned char *)"\\Phi",     //     C_Phi,
   (unsigned char *)NULL,     //     C_Chi,
   (unsigned char *)"\\Psi",     //     C_Psi,
   (unsigned char *)"\\Omega",   //     C_Omega,

   (unsigned char *)"\\alpha",   //     C_alpha,
   (unsigned char *)"\\beta",    //     C_beta,
   (unsigned char *)"\\gamma",   //     C_gamma,
   (unsigned char *)"\\delta",   //     C_delta,
   (unsigned char *)"\\varepsilon",//   C_epsilon,
   (unsigned char *)"\\zeta",    //     C_zeta,
   (unsigned char *)"\\eta",     //     C_eta,
   (unsigned char *)"\\theta",   //     C_theta,
   (unsigned char *)"\\iota",    //     C_jota,
   (unsigned char *)"\\kappa",   //     C_kappa,
   (unsigned char *)"\\lambda",  //     C_lambda,
   (unsigned char *)"\\mu",      //     C_my,
   (unsigned char *)"\\nu",      //     C_ny,
   (unsigned char *)"\\xi",      //     C_xi,
   (unsigned char *)"\\omicron", //   C_omicron, mano sugalvotas
   (unsigned char *)"\\pi",      //     C_pi,
   (unsigned char *)"\\rho",     //     C_rho,
   (unsigned char *)"\\sigma",   //     C_sigma,
   (unsigned char *)"\\tau",     //     C_tau,
   (unsigned char *)"\\upsilon", //     C_ypsilon,

   (unsigned char *)"\\phi",     //     C_phi,
   (unsigned char *)"\\chi",     //     C_chi,
   (unsigned char *)"\\psi",     //     C_psi,
   (unsigned char *)"\\omega",   //     C_omega,

   (unsigned char *)"\\eth",     //     C_delt_Mn, /* delta_Minus    (skardi th) */

// diacritics
   (unsigned char *)"\\\' ",   // "\\\'\\null",   //     C_Acute,   /* '  Acute    (aku/tas, apostrofas, des/inys kirtis) */
   (unsigned char *)"\\H ",    // "\\H\\null",    //     C_Dacut,   /* '' Double Acute */
   (unsigned char *)"\\ogon",  // NULL,           //     C_Ogon,    /* ,  Ogonek    (nosine) */
   (unsigned char *)"\\. ",    // "\\.\\null",    //     C_Adot,    /* .  Dot Above    (. virsuje) */
   (unsigned char *)"\\v ",    // "\\v\\null",    //     C_Car,     /* v  Carron    (Pauksciukas) */
   (unsigned char *)"\\= ",    // "\\=\\null",    //     C_Macr,    /* _  Macron, Overline    (bruksnys virsuje) */
   (unsigned char *)"\\\" ",   // "\\\"\\null",   //     C_Diaer,   /* .. Diaeresis    (Umlaut) */
   (unsigned char *)NULL,                         //     C_Ring,    /* o  Ring    (Circle) Above    (o virsuje, degree) */
   (unsigned char *)NULL,                         //     C_Tacom,   /* '  Turned Comma Above */
   (unsigned char *)NULL,                         //     C_Bcomma,  /* ,  Comma Bellow */
   (unsigned char *)"\\c ",    // "\\c\\enspace", //     C_Cedil,   /* ,  Cedilla    (atbula nosine) */

   (unsigned char *)NULL,      //    C_A_Ogon,  /* A, */
   (unsigned char *)NULL,      //    C_a_Ogon,  /* a, */
   (unsigned char *)NULL,      //    C_E_Ogon,  /* E, */
   (unsigned char *)NULL,      //    C_e_Ogon,  /* e, */
   (unsigned char *)NULL,      //    C_I_Ogon,  /* I, */
   (unsigned char *)NULL,      //    C_i_Ogon,  /* i, */
   (unsigned char *)NULL,      //    C_U_Ogon,  /* U, */
   (unsigned char *)NULL,      //    C_u_Ogon,  /* u, */

   (unsigned char *)"\\. E",   //    C_E_Adot,  /* E. */
   (unsigned char *)"\\. e",   //    C_e_Adot,  /* e. */
   (unsigned char *)"\\. Z",   //    C_Z_Adot,  /* Z. */
   (unsigned char *)"\\. z",   //    C_z_Adot,  /* z. */

   (unsigned char *)"\\. \\Gcy", //     C_G_Cyr_Adot, /* G Cyr . */
   (unsigned char *)"\\. \\gcy", //     C_g_Cyr_Adot, /* g Cyr . */

   (unsigned char *)"\\v C",   //    C_C_Car,   /* Cv */
   (unsigned char *)"\\v c",   //    C_c_Car,   /* cv */
   (unsigned char *)"\\v D",   //    C_D_Car,   /* Dv */
   (unsigned char *)"\\v d",   //    C_d_Car,   /* dv */
   (unsigned char *)"\\v E",   //    C_E_Car,   /* Ev */
   (unsigned char *)"\\v e",   //    C_e_Car,   /* ev */
   (unsigned char *)"\\v L",   //    C_L_Car,   /* Lv */
   (unsigned char *)"\\v l",   //    C_l_Car,   /* lv */
   (unsigned char *)"\\v N",   //    C_N_Car,   /* Nv */
   (unsigned char *)"\\v n",   //    C_n_Car,   /* nv */
   (unsigned char *)"\\v R",   //    C_R_Car,   /* Rv */
   (unsigned char *)"\\v r",   //    C_r_Car,   /* rv */
   (unsigned char *)"\\v S",   //    C_S_Car,   /* Sv */
   (unsigned char *)"\\v s",   //    C_s_Car,   /* sv */
   (unsigned char *)"\\v T",   //    C_T_Car,   /* Tv */
   (unsigned char *)"\\v t",   //    C_t_Car,   /* tv */
   (unsigned char *)"\\v Z",   //    C_Z_Car,   /* Zv */
   (unsigned char *)"\\v z",   //    C_z_Car,   /* zv */

   (unsigned char *)"\\= A",   //    C_A_Macr,  /* A_ */
   (unsigned char *)"\\= a",   //    C_a_Macr,  /* a_ */
   (unsigned char *)"\\= E",   //    C_E_Macr,  /* E_ */
   (unsigned char *)"\\= e",   //    C_e_Macr,  /* e_ */
   (unsigned char *)"\\= I",   //    C_I_Macr,  /* I_ */
   (unsigned char *)"\\= i",   //    C_i_Macr,  /* i_ */
   (unsigned char *)"\\= O",   //    C_O_Macr,  /* O_ */
   (unsigned char *)"\\= o",   //    C_o_Macr,  /* o_ */
   (unsigned char *)"\\= U",   //    C_U_Macr,  /* U_ */
   (unsigned char *)"\\= u",   //    C_u_Macr,  /* u_ */

   (unsigned char *)"\\\" A",  //    C_A_Diaer, /* A.. */
   (unsigned char *)"\\\" a",  //    C_a_Diaer, /* a.. */
   (unsigned char *)"\\\" E",  //    C_E_Diaer, /* E.. */
   (unsigned char *)"\\eu",    // "\\\" e",  //    C_e_Diaer, /* e.. */
   (unsigned char *)"\\\" I",  //    C_I_Diaer, /* I.. */
   (unsigned char *)"\\\" i",  //    C_i_Diaer, /* i.. */
   (unsigned char *)"\\\" O",  //    C_O_Diaer, /* O.. */
   (unsigned char *)"\\\" o",  //    C_o_Diaer, /* o.. */
   (unsigned char *)"\\\" U",  //    C_U_Diaer, /* U.. */
   (unsigned char *)"\\\" u",  //    C_u_Diaer, /* u.. */
   (unsigned char *)"\\Yu",    // "\\\" Y",  //    C_Y_Diaer, /* Y.. */
   (unsigned char *)"\\yu",    // "\\\" y",  //    C_y_Diaer, /* y.. */

   (unsigned char *)"\\IEcyu", // "\\\" \\IEcy", //   C_E_Cyr_Diaer, /* E.. */
   (unsigned char *)"\\iecyu", // "\\\" \\iecy", //   C_e_Cyr_Diaer, /* e.. */

   (unsigned char *)"\\AA",   //     C_A_Ring,  /* Ao */
   (unsigned char *)"\\aa",   //     C_a_Ring,  /* ao */
   (unsigned char *)NULL,     //     C_U_Ring,  /* Uo */
   (unsigned char *)NULL,     //     C_u_Ring,  /* uo */

   (unsigned char *)NULL,     //     C_G_Tacom, /* G' */
   (unsigned char *)NULL,     //     C_g_Tacom, /* g' */

   (unsigned char *)"\\c G",  //     C_G_Bcomma,/* G, */
   (unsigned char *)"\\c g",  //     C_g_Bcomma,/* g, */
   (unsigned char *)"\\c K",  //     C_K_Bcomma,/* K, */
   (unsigned char *)"\\c k",  //     C_k_Bcomma,/* k, */
   (unsigned char *)"\\c L",  //     C_L_Bcomma,/* L, */
   (unsigned char *)"\\c l",  //     C_l_Bcomma,/* l, */
   (unsigned char *)"\\c N",  //     C_N_Bcomma,/* N, */
   (unsigned char *)"\\c n",  //     C_n_Bcomma,/* n, */
   (unsigned char *)"\\c R",  //     C_R_Bcomma,/* R, */
   (unsigned char *)"\\c r",  //     C_r_Bcomma,/* r, */

   (unsigned char *)"\\c C",  //     C_C_Cedil, /* C, */
   (unsigned char *)"\\c c",  //     C_c_Cedil, /* c, */
   (unsigned char *)"\\c S",  //     C_S_Cedil, /* S, */
   (unsigned char *)"\\c s",  //     C_s_Cedil, /* s, */
   (unsigned char *)"\\c T",  //     C_T_Cedil, /* T, */
   (unsigned char *)"\\c t",  //     C_t_Cedil, /* t, */

   (unsigned char *)"\\` A",   //    C_A_Grave, /* A` */
   (unsigned char *)"\\` a",   //    C_a_Grave, /* a` */
   (unsigned char *)"\\` E",   //    C_E_Grave, /* E` */
   (unsigned char *)"\\` e",   //    C_e_Grave, /* e` */
   (unsigned char *)"\\` I",   //    C_I_Grave, /* I` */
   (unsigned char *)"\\` i",   //    C_i_Grave, /* i` */
   (unsigned char *)"\\` O",   //    C_O_Grave, /* O` */
   (unsigned char *)"\\` o",   //    C_o_Grave, /* o` */
   (unsigned char *)"\\` U",   //    C_U_Grave, /* U` */
   (unsigned char *)"\\` u",   //    C_u_Grave, /* u` */

   (unsigned char *)"\\\' A",  //    C_A_Acute, /* A' */
   (unsigned char *)"\\\' a",  //    C_a_Acute, /* a' */
   (unsigned char *)"\\\' C",  //    C_C_Acute, /* C' */
   (unsigned char *)"\\\' c",  //    C_c_Acute, /* c' */
   (unsigned char *)"\\\' E",  //    C_E_Acute, /* E' */
   (unsigned char *)"\\\' e",  //    C_e_Acute, /* e' */
   (unsigned char *)"\\\' I",  //    C_I_Acute, /* I' */
   (unsigned char *)"\\\' i",  //    C_i_Acute, /* i' */
   (unsigned char *)"\\\' L",  //    C_L_Acute, /* L' */
   (unsigned char *)"\\\' l",  //    C_l_Acute, /* l' */
   (unsigned char *)"\\\' N",  //    C_N_Acute, /* N' */
   (unsigned char *)"\\\' n",  //    C_n_Acute, /* n' */
   (unsigned char *)"\\\' O",  //    C_O_Acute, /* O' */
   (unsigned char *)"\\\' o",  //    C_o_Acute, /* o' */
   (unsigned char *)"\\\' R",  //    C_R_Acute, /* R' */
   (unsigned char *)"\\\' r",  //    C_r_Acute, /* r' */

   (unsigned char *)"\\\' S",  //    C_S_Acute, /* S' */
   (unsigned char *)"\\\' s",  //    C_s_Acute, /* s' */
   (unsigned char *)"\\\' U",  //    C_U_Acute, /* U' */
   (unsigned char *)"\\\' u",  //    C_u_Acute, /* u' */
   (unsigned char *)"\\\' Y",  //    C_Y_Acute, /* Y' */
   (unsigned char *)"\\\' y",  //    C_y_Acute, /* y' */
   (unsigned char *)"\\\' Z",  //    C_Z_Acute, /* Z' */
   (unsigned char *)"\\\' z",  //    C_z_Acute, /* z' */

   (unsigned char *)"\\\' \\Kcy",  //      C_K_Cyr_Acute, /* K Cyr ' */
   (unsigned char *)"\\\' \\kcy",  //      C_k_Cyr_Acute, /* k Cyr ' */

   (unsigned char *)"\\H O",   //       C_O_Dacut, /* O'' */
   (unsigned char *)"\\H o",   //       C_o_Dacut, /* o'' */
   (unsigned char *)"\\H U",   //       C_U_Dacut, /* U'' */
   (unsigned char *)"\\H u",   //       C_u_Dacut, /* u'' */

   (unsigned char *)"\\~ A",   //       C_A_Tilde, /* A~ */
   (unsigned char *)"\\~ a",   //       C_a_Tilde, /* a~ */
   (unsigned char *)"\\~ N",   //       C_N_Tilde, /* N~ */
   (unsigned char *)"\\~ n",   //       C_n_Tilde, /* n~ */
   (unsigned char *)"\\~ O",   //       C_O_Tilde, /* O~ */
   (unsigned char *)"\\~ o",   //       C_o_Tilde, /* o~ */

   (unsigned char *)"\\L", //   C_L_Slash, /* L/ */
   (unsigned char *)"\\l", //   C_l_Slash, /* l/ */
   (unsigned char *)"\\O", //   C_O_Slash, /* O/ */
   (unsigned char *)"\\o", //   C_o_Slash, /* o/ */

   (unsigned char *)"\\^ A",   //       C_A_Circ,  /* A^ */
   (unsigned char *)"\\^ a",   //       C_a_Circ,  /* a^ */
   (unsigned char *)"\\^ E",   //       C_E_Circ,  /* E^ */
   (unsigned char *)"\\^ e",   //       C_e_Circ,  /* e^ */
   (unsigned char *)"\\^ I",   //       C_I_Circ,  /* I^ */
   (unsigned char *)"\\^ i",   //       C_i_Circ,  /* i^ */
   (unsigned char *)"\\^ O",   //       C_O_Circ,  /* O^ */
   (unsigned char *)"\\^ o",   //       C_o_Circ,  /* o^ */
   (unsigned char *)"\\^ U",   //       C_U_Circ,  /* U^ */
   (unsigned char *)"\\^ u",   //       C_u_Circ,  /* u^ */

   (unsigned char *)NULL,     //        C_D_Minus, /* D- Island. */
   (unsigned char *)NULL,     //        C_d_Minus, /* d- */
   (unsigned char *)NULL,     //        C_H_Minus, /* H- */
   (unsigned char *)"\\hbar", //        C_h_Minus, /* h- */
   (unsigned char *)NULL,     //        C_P_Minus, /* P- */
   (unsigned char *)NULL,     //        C_p_Minus, /* p- */

   (unsigned char *)"~", // "\\enspace", // n-width no break space - C_NBSP,   /* No break space */
// (unsigned char *)"\\thinspace",    // thin no break space, width = 1/4 m ???
// (unsigned char *)"\\negthinspace", // negative thin no break space, width = -1/4 m ???

   (unsigned char *)"\\cur",  // kp //  C_Rouble,  /* rublis, " Cyr */
   (unsigned char *)"\\pound",//        C_Pound,   /* svaras, L/ */
   (unsigned char *)"\\yen",  //        C_Yenna,   /* jena, Y- */
   (unsigned char *)"\\cent", //        C_cent,    /* c/ */  TEX komanda mano sugalvota

   (unsigned char *)"\\S",    //        C_Para,    /* paragrafas, # engl. */
   (unsigned char *)"\\P",    //        C_Pren,    /* paragraph end sign    (pastraipos pabaiga, C_pi - pi) */
   (unsigned char *)"\\times",//        C_Multipl, /* x */
   (unsigned char *)"\\div",  //        C_Divide,  /* -:- */
   (unsigned char *)"\\pm",   //        C_PlMin,   /* -+- */
   (unsigned char *)"^1",     //        C_1up,     /* 1 virsuj */
   (unsigned char *)"^2",     //        C_2up,     /* 2 virsuj, kvadratu */
   (unsigned char *)"^3",     //        C_3up,     /* 3 virsuj, kubu */
   (unsigned char *)"^a",     //        C_a_up,    /* a virsuj */
   (unsigned char *)"^o",     //        C_o_up,    /* o virsuj */
   (unsigned char *)"\\half", // kp     C_Half,    /* 1/2 */
   (unsigned char *)NULL,     //        C_Quart,   /* 1/4 */
   (unsigned char *)NULL,     //        C_34,      /* 3/4 */
   (unsigned char *)"\\glf",  // kp     C_Ldopang, /* << */
   (unsigned char *)"\\glr",  // kp     C_Rdopang, /* >> */
   (unsigned char *)"\\langle", //      C_Lang,    /* < */
   (unsigned char *)"\\rangle", //      C_Rang,    /* > */
   (unsigned char *)NULL,     //        C_Dvertl,  /* | Koi-7-0 */
   (unsigned char *)"\\neg",  //        C_Rminbr,  /* ^ Koi-7-0    (neiginys,  -| ) */
   (unsigned char *)NULL,     //        C_Lminbr,  /* |- */
   (unsigned char *)"\\cdot", // !!! "\\centerdot", // C_Lpoint,  /* mazas taskas vidury */
   (unsigned char *)NULL,     // "\\bullet",//       C_Bpoint,  /* didelis taskas vidury */ // iðkeltas á C_hBpoint 
   (unsigned char *)NULL,     // ",," ???  C_LBquote
   (unsigned char *)"``",     //        C_LAquote
   (unsigned char *)"\'\'",   //        C_Rquote
   (unsigned char *)NULL,     // ",",   C_LBapost
   (unsigned char *)NULL,     // "`",   C_LAapost
   (unsigned char *)NULL,     // "\'",  C_Rapost
   (unsigned char *)"?`",     //        C_Qst_Ov,  /* apverstas ? */
   (unsigned char *)"!`",     //        C_Ex_Ov,   /* apverstas ! */
   (unsigned char *)"\\dots", // !!! "\\ldots", // C_Dots,    /* ... daugtaskis */
   (unsigned char *)"\\permil",// kp    C_Prom,    /* %o promiles */
   (unsigned char *)"\\TM",   // kp     C_TM,      /* TM, Trade Mark */
   (unsigned char *)"\\copyright",//    C_CO,      /*    (C) Copyright */
   (unsigned char *)"\\circledR", //    C_RO,      /*    (R) */

                              //    /* Additional greek chars, look SGML DTD */
   (unsigned char *)"\\epsilon",    //     C_epsilon_var,
   (unsigned char *)"\\vartheta",   //     C_theta_var,
   (unsigned char *)NULL,     //     C_DiGamma,
   (unsigned char *)NULL,     //     C_digamma,
   (unsigned char *)"\\varkappa", // C_kappa_var,
   (unsigned char *)NULL,     //     C_DiLambda,
   (unsigned char *)NULL,     //     C_dilambda,
   (unsigned char *)"\\varpi",      //     C_pi_var,
   (unsigned char *)"\\varrho",     //     C_rho_var,
   (unsigned char *)NULL,     //     C_Sigma_var,
   (unsigned char *)"\\varsigma",   //     C_sigma_var,
   (unsigned char *)"\\varphi",     //     C_phi_var,

             /* additional diacritics accents, all of them have no width (over the next letter) */
   (unsigned char *)"\\`",    //     C_GraveAcc,    /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   (unsigned char *)"\\^",    //     C_CircAcc,     /* ^  Circumflex Accent (C_Circ), over the next letter */
   (unsigned char *)"\\~",    //     C_TildeAcc,    /* ~  Tilde (C_Tilde), over the next letter */
   (unsigned char *)"\\u",    //     C_BreveAcc,    /* u  (lankelis virsuje) */
   (unsigned char *)"\\not",  //     C_SlashAcc,    /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   (unsigned char *)"\\d",    //     C_BdotAcc,     /* .  Dot bellow */
   (unsigned char *)"\\b",    //     C_UnderlAcc,   /* _  Underline (Pabraukimas) */

   (unsigned char *)"\\prime",//     C_prim,    /* strichas prie raides (renkamas po raides) (C_Acute, C_Apost) */
   (unsigned char *)NULL,     //     C_dprim,   /* du strichai (C_Dacut) */

   (unsigned char *)"\\forall",//    C_Each,    /* V - "kiekvienam- apversta A raide */
   (unsigned char *)"\\exists",//    C_Exists,  /* E - "egzistuoja- apversta E raide */

   (unsigned char *)"\\aleph",  //   C_Aleph,   /* N - alefas */
   (unsigned char *)"\\Im",     //   C_Im,      /* C_I_Got */
   (unsigned char *)"\\Re",     //   C_Re,      /* C_R_Got */
   (unsigned char *)"\\wp",     //   C_wp,      /* C_p_Got */

   (unsigned char *)"\\leq",  // !!! "\\le",   //     C_le,      /* <= - maziau arba lygu */
   (unsigned char *)"\\ge",   //     C_ge,      /* >= - daugiau arba lygu */
   (unsigned char *)"\\ne",   //     C_ne,      /* =/= - nelygu */
   (unsigned char *)"\\ll",   //     C_ll,      /* << */
   (unsigned char *)"\\gg",   //     C_gg,      /* >> */
   (unsigned char *)"\\sim",  //     C_sim,     /* ~ - panasu */
   (unsigned char *)"\\simeq",//     C_simeq,   /* ~- - panasu arba sutampa */
   (unsigned char *)"\\approx",//    C_approx,  /* ~~ - apytiksliai lygu */
   (unsigned char *)"\\cong", //     C_cong,    /* ~= - kongruentu */
   (unsigned char *)"\\equiv",//     C_equiv,   /* = - triguba lygybe - ekvivalentu */

   (unsigned char *)NULL, // !!! "\\sqrt"  //     C_sqrt,    /* square root */
   (unsigned char *)"\\int",      // C_int,     /* integralas */
   (unsigned char *)"\\oint",     // C_oint,    /* kreivinis integralas */
   (unsigned char *)"\\sum",      // C_Sum,     /* sum sign (C_Sigma) */
   (unsigned char *)"\\prod",     // C_Prod,    /* C_Pi */
   (unsigned char *)"\\otimes",   // C_O_times, /* OX - O perbraukta istrizai */
   (unsigned char *)"\\oplus",    // C_O_plus,  /* O+ - O perbraukta pliusu */

   (unsigned char *)"\\infty",//     C_infty,   /* infinity - begalybe */
   (unsigned char *)"\\propto", // !!! "varpropto", // C_propto,  /* (C_alpha) */
   (unsigned char *)"\\partial",//   C_part,    /* partial - C_delta */
   (unsigned char *)"\\emptyset", // !!! "\\varnothing", // C_empty,   /* O/ (C_O_Slash) */
   (unsigned char *)"\\triangle", // !!! "\\vartriangle", //  C_triangle,/* C_Delta - trikampis */
   (unsigned char *)"\\nabla",//     C_nabla,   /* V - C_Delta apversta */

   (unsigned char *)"\\perp", //     C_perp,    /* T apversta - statmena */
   (unsigned char *)"\\angle",//     C_angle,   /* < - kampas */

   (unsigned char *)NULL,     //    C_langle,  /* < - skliaustas */
   (unsigned char *)NULL,     //    C_rangle,  /* > - skliaustas */

   (unsigned char *)"\\cap",  //     C_cap,     /* U apversta - pjuvis */
   (unsigned char *)"\\cup",  //     C_cup,     /* U - junginys */

   (unsigned char *)"\\vee",  //     C_vee,     /* V */
   (unsigned char *)"\\wedge", //    C_wedge,   /* C_Lambda */

   (unsigned char *)"\\supset",     // C_supset,  /* D - virsaibis */
   (unsigned char *)"\\supseteq",   // C_supseteq,/* D= - virsaibis arba sutampa */
   (unsigned char *)"\\subset",     // C_subset,  /* C - poaibis */
   (unsigned char *)"\\subseteq",   // C_subseteq,/* C= - poaibis arba sutampa */
   (unsigned char *)"\\not\\subset",// C_nsubset, /* C/ - nepoaibis */

   (unsigned char *)"\\in",         // C_in,      /* C_epsilon_var - priklauso */
   (unsigned char *)"\\not\\in",    // C_notin,   /* C_epsilon_var_Slash - nepriklauso */
   (unsigned char *)"\\ni",         // C_ni,      /* C_epsilon_var apsuktas - apima */

   (unsigned char *)"\\leftarrow",     //  "\\leftarrowfill",  // "\\leftarrowtail",  // C_leftarr,       /* <-- */
   (unsigned char *)"\\rightarrow",    //  "\\rightarrowfill", // "\\rightarrowtail", // C_rightarr,      /* --> */
   (unsigned char *)"\\leftrightarrow",//  C_leftrightarr,  /* <--> */
   (unsigned char *)"\\uparrow",       //  C_uparr,         /* ^| */
   (unsigned char *)"\\downarrow",     //  C_downarr,       /* |v */
   (unsigned char *)"\\updownarrow",   //  C_updownarr,     /* ^|v */

   (unsigned char *)"\\Leftarrow",     //  C_Leftarr,       /* <== */
   (unsigned char *)"\\Rightarrow",    //  C_Rightarr,      /* ==> */
   (unsigned char *)"\\Leftrightarrow",//  C_Leftrightarr,  /* <==> */
   (unsigned char *)"\\Uparrow",       //  C_Uparr,         /* ^|| */
   (unsigned char *)"\\Downarrow",     //  C_Downarr,       /* ||v */
   (unsigned char *)"\\Updownarrow",   //  C_Updownarr,     /* ^||v */

   (unsigned char *)"\\mid",           //  C_mid,             /* | */
   (unsigned char *)"\\parallel", // !!! "\\Vert", // !!! "\\|", //  C_paral,           /* || */

   (unsigned char *)"\\diamond", // !!! "\\lozenge", // C_diamond,     /* rombas */

   (unsigned char *)"\\clubsuit",   //     C_Club,        /* giles */
   (unsigned char *)"\\diamondsuit",//     C_Diamond,     /* bugnai */
   (unsigned char *)"\\heartsuit",  //     C_Heart,       /* cirvai sirdys */
   (unsigned char *)"\\spadesuit",  //     C_Spade,       /* pikai lapai */

   (unsigned char *)"\\-",    //     C_hyph,    /* hided hyphenation sign ("\-" for TEX) */
   (unsigned char *)"\\break",//     C_break,   /* line break character */

   (unsigned char *)"\\v a",  //     C_a_Car,   /* av - laikinai, po to ismesti !!! */

   (unsigned char *)"\\euro", //     C_euro,    /* C= euro piniginis vienetas !!! kelti prie pinigu */

   (unsigned char *)"\\deg",  //     C_deg,     /* degree - panasiai, kaip C_Ring, tik desineje */
   (unsigned char *)"\\micro", // kp C_micro,   /* mikro - panasiai, kaip C_my */
   (unsigned char *)"\\ohm",  // kp  C_Ohm,     /* Ohm sign - panasiai, kaip C_Omega */
   (unsigned char *)NULL,     //     C_Angst,   /* Angstroem - C_A_Ring */

   (unsigned char *)NULL,     //     C_Horl,    /* horizontal line --- */

   (unsigned char *)"\\dagger",  //  C_Dag,    /* Dagger +| (kryzius) */
   (unsigned char *)"\\ddagger", //  C_Ddag,   /* Double dagger +|+ (Kestucio kryzius) */

   (unsigned char *)"ff",     //     C_ff,     /* ff ligature */
   (unsigned char *)"fi",     //     C_fi,     /* fi ligature */
   (unsigned char *)NULL,     //     C_fj,     /* fj ligature */
   (unsigned char *)"ffi",    //     C_ffi,    /* ff ligature */
   (unsigned char *)"ffl",    //     C_ffl,    /* ff ligature */
   (unsigned char *)"fl",     //     C_fl,     /* ff ligature */

   (unsigned char *)"\\land", //     C_and,    /* ^ logical and */
   (unsigned char *)"\\lor",  //     C_or,     /* V logical or */

   (unsigned char *)NULL,     //     C_fun,    /* f function of */

   (unsigned char *)"\\mp",   //     C_MinPl,  /* -+ minus plus */

   (unsigned char *)"--",     //     C_EnDash, /* -- - vidutinio ilgio bruksnys */
   (unsigned char *)"---",    //     C_EmDash, /* --- - ilgas bruksnys */

   (unsigned char *)"\\cdots", //    C_Cdots,  /* ... - daugtaskis per viduri */
   (unsigned char *)"\\widetilde", // C_WideTilde, /* ~ didele tilde */

   (unsigned char *)"\\,",    //     C_QemSpc, /* 1/4 m space */
// (unsigned char *)"\\>",    //                  1/3 m space
// (unsigned char *)"\\;",    //                  5/12 m space
// (unsigned char *)"\\!",    //                 -1/4 m space (negative)
   (unsigned char *)"\\enskip", //   C_EnSpc,  /* n space */, eilute gali luzti
   (unsigned char *)"\\quad", //     C_EmSpc,  /* m space */, eilute gali luzti
   (unsigned char *)"\\qquad", //    C_2emSpc, /* 2 m space */, eilute gali luzti

   (unsigned char *)"\\\\",   //     C_NewPar, /* paragraph end control character */

   (unsigned char *)"\\` Y",   //     C_Y_Grave,  Y`
   (unsigned char *)"\\` y",   //     C_y_Grave,  y`
   (unsigned char *)"\\~ E",   //     C_E_Tilde,  E~
   (unsigned char *)"\\~ e",   //     C_e_Tilde,  e~
   (unsigned char *)"\\~ I",   //     C_I_Tilde,  I~
   (unsigned char *)"\\~ i",   //     C_i_Tilde,  i~
   (unsigned char *)"\\~ U",   //     C_U_Tilde,  U~
   (unsigned char *)"\\~ u",   //     C_u_Tilde,  u~
   (unsigned char *)"\\~ Y",   //     C_Y_Tilde,  Y~
   (unsigned char *)"\\~ y",   //     C_y_Tilde,  y~
   (unsigned char *)"\\~ L",   //     C_L_Tilde,  L~
   (unsigned char *)"\\~ l",   //     C_l_Tilde,  l~
   (unsigned char *)"\\~ M",   //     C_M_Tilde,  M~
   (unsigned char *)"\\~ m",   //     C_m_Tilde,  m~
   (unsigned char *)"\\~ R",   //     C_R_Tilde,  R~
   (unsigned char *)"\\~ r",   //     C_r_Tilde,  r~
   (unsigned char *)NULL,     //     C_A_Ogon_Acute,
   (unsigned char *)NULL,     //     C_a_Ogon_Acute,
   (unsigned char *)NULL,     //     C_E_Ogon_Acute,
   (unsigned char *)NULL,     //     C_e_Ogon_Acute,
   (unsigned char *)NULL,     //     C_E_Adot_Acute,
   (unsigned char *)NULL,     //     C_e_Adot_Acute,
   (unsigned char *)NULL,     //     C_I_Ogon_Acute,
   (unsigned char *)NULL,     //     C_i_Ogon_Acute,
   (unsigned char *)NULL,     //     C_U_Ogon_Acute,
   (unsigned char *)NULL,     //     C_u_Ogon_Acute,
   (unsigned char *)NULL,     //     C_U_Macr_Acute,
   (unsigned char *)NULL,     //     C_u_Macr_Acute,
   (unsigned char *)NULL,     //     C_A_Ogon_Grave,
   (unsigned char *)NULL,     //     C_a_Ogon_Grave,
   (unsigned char *)NULL,     //     C_E_Ogon_Grave,
   (unsigned char *)NULL,     //     C_e_Ogon_Grave,
   (unsigned char *)NULL,     //     C_E_Adot_Grave,
   (unsigned char *)NULL,     //     C_e_Adot_Grave,
   (unsigned char *)NULL,     //     C_I_Ogon_Grave,
   (unsigned char *)NULL,     //     C_i_Ogon_Grave,
   (unsigned char *)NULL,     //     C_U_Ogon_Grave,
   (unsigned char *)NULL,     //     C_u_Ogon_Grave,
   (unsigned char *)NULL,     //     C_U_Macr_Grave,
   (unsigned char *)NULL,     //     C_u_Macr_Grave,
   (unsigned char *)NULL,     //     C_A_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_a_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_E_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_e_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_E_Adot_Tilde,
   (unsigned char *)NULL,     //     C_e_Adot_Tilde,
   (unsigned char *)NULL,     //     C_I_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_i_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_U_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_u_Ogon_Tilde,
   (unsigned char *)NULL,     //     C_U_Macr_Tilde,
   (unsigned char *)NULL,     //     C_u_Macr_Tilde,

// phonetic characters; vowels:
   (unsigned char *)"\\ah",   // kp  C_ph_a,        // low back unrounded; a, open a; italic C_a
   (unsigned char *)NULL,     //     C_ph_a_inv,    // low back rounded; oa; inverted italic C_a

   (unsigned char *)"\\w",    //     C_ph_a_sh,     // low-mid back unrounded; short a; inverted C_v
   (unsigned char *)"\\ilo",  //     C_ph_o_sh,     // low-mid back rounded; short o, open o; inverted C_c
// (unsigned char *)NULL,     //     C_ph_o,        // mid back rounded?; o, closed o; C_o
// (unsigned char *)NULL,     //     C_ph_o_soft,   // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
// (unsigned char *)NULL,     //     C_ph_o_soft_cl,// high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   (unsigned char *)"\\vv",   //     C_ph_u_sh,     // semi-high back rounded; short u, short open u; C_ypsilon
   (unsigned char *)NULL,     //     C_ph_w_sh,     // semi-high back rounded; short u, short open u, obsolete; C_omega
// (unsigned char *)NULL,     //     C_ph_u,        // semi-high central rounded?; u, closed u; C_u
// (unsigned char *)NULL,     //     C_ph_u_soft,   // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   (unsigned char *)"\\ep",   //     C_ph_e_sh,     // low-mid front unrounded; short e, open e; C_epsilon
   (unsigned char *)NULL,     //     C_ph_ae,       // low front unrounded?; e, open e; C_ae
// (unsigned char *)NULL,     //     C_ph_e_cl,     // high central unrounded?; closed e, german e; C_e
   (unsigned char *)NULL,     //     C_ph_e_sh_inv, // low-mid central unrounded; hard e; inverted C_epsilon
   (unsigned char *)"\\ate",  //     C_ph_e_inv,    // mid central unrounded; reduced e; inverted C_e

   (unsigned char *)"\\i",    //     C_ph_i_sh,     // semi-high front unrounded; short i, short open i; C_i without dot
// (unsigned char *)NULL,     //     C_ph_i,        // high front unrounded?; i, closed i; C_i

// phonetic characters; consonants:
   (unsigned char *)"\\s",    //     C_ph_sh,       // sh; C_f, C_int
   (unsigned char *)"\\ilz",  //     C_ph_zh,       // zh; C_3
   (unsigned char *)NULL,     //     C_ph_tsh,      // tsh; C_t C_f, C_t C_int
   (unsigned char *)NULL,     //     C_ph_dzh,      // dzh; C_d C_3
   (unsigned char *)"\\th",   //     C_ph_th_b,     // breath th; C_theta
   (unsigned char *)"\\dh", // kp // "\\le", // C_ph_th_v, // voiced th; C_delt_Mn, (C_delta_Minus)
   (unsigned char *)"\\ng",   //     C_ph_ng,       // nasal g; C_eta
// (unsigned char *)NULL,     //     C_ph_ch,       // german ch; C_c_Cedil
   (unsigned char *)NULL,     //     C_ph_g,        // g; italic C_g

// additional phonetic characters:
   (unsigned char *)NULL,     //     C_ph_oe,       // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   (unsigned char *)NULL,     //     C_ph_o_slash,  // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   (unsigned char *)NULL,     //     C_ph_a_l,      // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   (unsigned char *)NULL,     //     C_ph_e_inv_l,  // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   (unsigned char *)NULL,     //     C_ph_i_l,      // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   (unsigned char *)NULL,     //     C_ph_o_l,      // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   (unsigned char *)NULL,     //     C_ph_u_l,      // ; u long; C_u C_Colon

   (unsigned char *)NULL,     //     C_ph_a_n,      // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   (unsigned char *)"\\at",   //     C_ph_a_str_n,  // ; a~; C_a_Tilde
   (unsigned char *)"\\ept",  //     C_ph_e_n,      // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   (unsigned char *)"\\oet",  //     C_ph_oe_n,     // ; oe nasal; oe~, C_oe C_TildeAcc
   (unsigned char *)"\\ilot", //     C_ph_o_n,      // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   (unsigned char *)"\\ch",   // kp  C_ph_ch,       // german ch; C_c_Cedil

// diphtongs
   (unsigned char *)"\\lai",  //     C_ph_ai_d,     //  C_a C_LigaLow C_i
   (unsigned char *)"\\lae",  //     C_ph_ae_d,     //  C_a C_LigaLow C_e
   (unsigned char *)"\\lao",  //     C_ph_ao_d,     //  C_a C_LigaLow C_o
   (unsigned char *)"\\lau",  //     C_ph_au_d,     //  C_a C_LigaLow C_u
   (unsigned char *)NULL,     //     C_ph_ei_d,     //  C_e C_LigaLow C_i
   (unsigned char *)NULL,     //     C_ph_eu_d,     //  C_e C_LigaLow C_u
   (unsigned char *)NULL,     //     C_ph_ie_d,     //  C_i C_LigaLow C_e
   (unsigned char *)NULL,     //     C_ph_oe_d,     //  C_ph_o_sh C_LigaLow C_ph_o_slash
   (unsigned char *)"\\loy",  //     C_ph_oy_d,     //  C_ph_o_sh C_LigaLow C_y
   (unsigned char *)NULL,     //     C_ph_uo_d,     //  C_u C_LigaLow C_o

// breved phonetics
   (unsigned char *)"\\isl",  //     C_ph_i_Brev,  // ; j; C_i_Brev
   (unsigned char *)"\\osl",  //     C_ph_o_Brev,  //  C_o_Brev
   (unsigned char *)"\\usl",  //     C_ph_u_Brev,  //  C_u_Brev

// liga accents (for diphtongs)
   (unsigned char *)"\\t",    //     C_LigaUp,      // lankelis virs dvieju raidziu
   (unsigned char *)NULL,     //     C_LigaLow,     // lankelis po dviem raidem

   (unsigned char *)"\\circ", //     C_MidRing,     // mazas apskritimas viduryje (tusciaviduris bulletas - kaip C_Bpoint)

   (unsigned char *)"\\ki",   //     C_ph_acc,       // C_Apost
   (unsigned char *)"\\kia",  //     C_ph_acc_low,   // C_Comma

   (unsigned char *)"\\square",//    C_square,       // tusciaviduris kvadratas viduryje

   (unsigned char *)"\\vyr",  //     C_male,         // vyr. lytis, male sex, mars, o^
   (unsigned char *)"\\mot",  //     C_female,       // mot. lytis, female sex, venus, o+

   (unsigned char *)"\\circledcirc",   //    C_O_ring
   (unsigned char *)"\\odot",          //    C_O_dot

   (unsigned char *)"\\bigcirc",       //    C_BigRing,     // didelis apskritimas, C_O

   (unsigned char *)"\\longleftarrow", //    C_longleftarr,       /* <---- */
   (unsigned char *)"\\longrightarrow", //   C_longrightarr,      /* ----> */

   (unsigned char *)"\\smile",   //   C_smile

   (unsigned char *)"\\blacksquare",   //     C_box,         // pilnaviduris kvadratas viduryje

// DOS frames
   (unsigned char *)NULL,     //     C_v_b,       // vert; ne DOS-e - C_Vertl
   (unsigned char *)NULL,     //     C_h_b,       // hor; ne DOS-e - C_Horl
   (unsigned char *)NULL,     //     C_vh_b,      // vert hor
   (unsigned char *)NULL,     //     C_vl_b,      // vert left
   (unsigned char *)NULL,     //     C_vr_b,      // vert right
   (unsigned char *)NULL,     //     C_hu_b,      // hor up
   (unsigned char *)NULL,     //     C_hd_b,      // hor down
   (unsigned char *)NULL,     //     C_ul_b,      // up left
   (unsigned char *)NULL,     //     C_dl_b,      // down left
   (unsigned char *)NULL,     //     C_ur_b,      // up right
   (unsigned char *)NULL,     //     C_dr_b,      // down right

   (unsigned char *)NULL,     //     C_2v_b,      // double vert; C_paral
   (unsigned char *)NULL,     //     C_2h_b,      // double hor
   (unsigned char *)NULL,     //     C_2v2h_b,    // double vert double hor
   (unsigned char *)NULL,     //     C_2v2l_b,    // double vert double left
   (unsigned char *)NULL,     //     C_2v2r_b,    // double vert double right
   (unsigned char *)NULL,     //     C_2h2u_b,    // double hor double up
   (unsigned char *)NULL,     //     C_2h2d_b,    // double hor double down
   (unsigned char *)NULL,     //     C_2u2l_b,    // double up double left
   (unsigned char *)NULL,     //     C_2d2l_b,    // double down double left
   (unsigned char *)NULL,     //     C_2u2r_b,    // double up double right
   (unsigned char *)NULL,     //     C_2d2r_b,    // double down double right

   (unsigned char *)NULL,     //     C_2vh_b,     // double vert hor
   (unsigned char *)NULL,     //     C_2vl_b,     // double vert left
   (unsigned char *)NULL,     //     C_2vr_b,     // double vert right
   (unsigned char *)NULL,     //     C_h2u_b,     // hor double up
   (unsigned char *)NULL,     //     C_h2d_b,     // hor double down
   (unsigned char *)NULL,     //     C_2ul_b,     // double up left
   (unsigned char *)NULL,     //     C_2dl_b,     // double down left
   (unsigned char *)NULL,     //     C_2ur_b,     // double up right
   (unsigned char *)NULL,     //     C_2dr_b,     // double down right

   (unsigned char *)NULL,     //     C_v2h_b,     // vert double hor
   (unsigned char *)NULL,     //     C_v2l_b,     // vert double left
   (unsigned char *)NULL,     //     C_v2r_b,     // vert double right
   (unsigned char *)NULL,     //     C_2hu_b,     // double hor up
   (unsigned char *)NULL,     //     C_2hd_b,     // double hor down
   (unsigned char *)NULL,     //     C_u2l_b,     // up double left
   (unsigned char *)NULL,     //     C_d2l_b,     // down double left
   (unsigned char *)NULL,     //     C_u2r_b,     // up double right
   (unsigned char *)NULL,     //     C_d2r_b,     // down double right

   (unsigned char *)NULL,     //     C_block,     // pilnaviduris kvadratas per visa laukeli
   (unsigned char *)NULL,     //     C_dgrblk,    // tamsiai pilkas ---//--- (75% shaded)
   (unsigned char *)NULL,     //     C_grblk,     // pilkas ---//--- (50% shaded)
   (unsigned char *)NULL,     //     C_lgrblk,    // sviesiai pilkas ---//--- (25% shaded)
   (unsigned char *)NULL,     //     C_uphblk,    // pilnaviduris staciakampis per puse laukelio virsuje
   (unsigned char *)NULL,     //     C_dnhblk,    // ---//--- apacioje
   (unsigned char *)NULL,     //     C_lthblk,    // ---//--- kaireje
   (unsigned char *)NULL,     //     C_rthblk,    // ---//--- desineje

   (unsigned char *)"\\blacktriangle",       //     C_utrif,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   (unsigned char *)"\\blacktriangledown",   //     C_dtrif,     // pilnaviduris trikampis zemyn
   (unsigned char *)"\\blacktriangleleft",   //     C_ltrif,     // pilnaviduris trikampis i kaire
   (unsigned char *)"\\blacktriangleright",  //     C_rtrif,     // pilnaviduris trikampis i desine

                                                       // ----------------------------
   (unsigned char *)NULL,     //     C_ph_uu_sh,       // phonetics: semi-high back rounded; short u, short open u; inverted C_Omega

   (unsigned char *)NULL,     //     C_hhyph,          // hard hyphen - zodzio kelimas per prievarta -\break
   (unsigned char *)NULL,     //     C_sbreak,         // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   (unsigned char *)NULL,     //     C_hSpc,           // hard space - technical space after TEX commands - do not process
   (unsigned char *)NULL,     //     C_hbreak,         // break su \hfill, xmlsty keiciamas is C_Cr ("\r")
   (unsigned char *)NULL,     //     C_lSpc,           // last space - space, to be changed to C_NBSP after LAST_WORD_LEN
   (unsigned char *)NULL,     //     C_hlSpc,          // hard last space - C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   (unsigned char *)NULL,     //     C_utrif_rtf,      // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   (unsigned char *)NULL,     //     C_dtrif_rtf,      // pilnaviduris trikampis zemyn
   (unsigned char *)NULL,     //     C_ltrif_rtf,      // pilnaviduris trikampis i kaire
   (unsigned char *)NULL,     //     C_rtrif_rtf,      // pilnaviduris trikampis i desine

// erdvines rodykles - zr. mcm_src.48d mac_p.rtf lizdas 2231
   (unsigned char *)NULL,     //     C_3DTopLightLeftArrowHead,    // 733
   (unsigned char *)NULL,     //     C_3DBotLightLeftArrowHead,    // 734
   (unsigned char *)NULL,     //     C_3DTopLightRightArrowHead,   // 735
   (unsigned char *)NULL,     //     C_3DBotLightRightArrowHead,   // 736
   (unsigned char *)NULL,     //     C_3DLeftLightUpArrowHead,     // 737
   (unsigned char *)NULL,     //     C_3DRightLightUpArrowHead,    // 738
   (unsigned char *)NULL,     //     C_3DLeftLightDownArrowHead,   // 739
   (unsigned char *)NULL,     //     C_3DRightLightDownArrowHead,  // 740

   (unsigned char *)"-", // "\\minus",// kp  C_MinusMath

   (unsigned char *)NULL,     //     C_ZeroWidthSpace

   (unsigned char *)"\\glstop",        // C_ph_glot_stop, TEX komanda mano sugalvota

   (unsigned char *)"\\\'\\null",      // C_AcuteNcomb
   (unsigned char *)"\\c\\enspace",    // C_CedilNcomb
   (unsigned char *)"\\=\\null",       // C_MacrNcomb

   (unsigned char *)NULL,     // "\\$",   //   C_DollNctrl

   (unsigned char *)"\\ogon\\null", //     C_OgonNcomb

   (unsigned char *)"\\nom",      //     C_No

   (unsigned char *)"\\v\\null",  //     C_CarNcomb
   (unsigned char *)"\\\"\\null", //     C_DiaerNcomb
   (unsigned char *)"\\tilde",    //     C_TildeAcc

   (unsigned char *)NULL,         //     C_utri
   (unsigned char *)NULL,         //     C_dtri
   (unsigned char *)NULL,         //     C_ltri
   (unsigned char *)NULL,         //     C_rtri

   (unsigned char *)NULL,         //     C_Oline

   (unsigned char *)"\\Roline",   //     C_R_Oline
   (unsigned char *)"\\Xoline",   //     C_X_Oline

   (unsigned char *)"\\leqslant", //     C_leqslant
   (unsigned char *)"\\geqslant", //     C_geqslant

   (unsigned char *)NULL,         //     C_i_Grave_Dotless
   (unsigned char *)NULL,         //     C_i_Acute_Dotless
   (unsigned char *)NULL,         //     C_i_Tilde_Dotless

   (unsigned char *)"\\Acyd",     //     C_A_Cyr_Acute,
   (unsigned char *)"\\IEcyd",    //     C_E_Cyr_Acute,
   (unsigned char *)"\\Icyd",     //     C_I_Cyr_Acute,
   (unsigned char *)"\\Ocyd",     //     C_O_Cyr_Acute,
   (unsigned char *)"\\Ucyd",     //     C_U_Cyr_Acute,
   (unsigned char *)"\\Ycyd",     //     C_Y_Cyr_Acute,
   (unsigned char *)"\\Ecyd",     //     C_Ee_Cyr_Acute,
   (unsigned char *)"\\YUcyd",    //     C_Ju_Cyr_Acute,
   (unsigned char *)"\\YAcyd",    //     C_Ja_Cyr_Acute,

   (unsigned char *)"\\acyd",     //     C_a_Cyr_Acute,
   (unsigned char *)"\\iecyd",    //     C_e_Cyr_Acute,
   (unsigned char *)"\\icyd",     //     C_i_Cyr_Acute,
   (unsigned char *)"\\ocyd",     //     C_o_Cyr_Acute,
   (unsigned char *)"\\ucyd",     //     C_u_Cyr_Acute,
   (unsigned char *)"\\ycyd",     //     C_y_Cyr_Acute,
   (unsigned char *)"\\ecyd",     //     C_ee_Cyr_Acute,
   (unsigned char *)"\\yucyd",    //     C_ju_Cyr_Acute,
   (unsigned char *)"\\yacyd",    //     C_ja_Cyr_Acute,

   (unsigned char *)"\\Null",     //     C_NullSpc

   (unsigned char *)NULL,         //     C_Dash_Diaer

   (unsigned char *)NULL,         //     C_bdiamond

   (unsigned char *)"\\degC",     // kp? C_DegCels

   (unsigned char *)"\\bullet",   //     C_hBpoint,  /* didelis taskas vidury */ // atkeltas ið C_Bpoint 

// ----------------------- old style cyrillic
   (unsigned char *)"\\Fita",    // kp // C_Fita_Cyr
   (unsigned char *)"\\fita",    // kp // C_fita_Cyr
   (unsigned char *)"\\Yat",     // kp // C_Yat_Cyr
   (unsigned char *)"\\yat",     // kp // C_yat_Cyr

   (unsigned char *)"\\checkmark", // C_checkmark

   (unsigned char *)NULL,        // C_prim_Ncomb
   (unsigned char *)NULL,        // C_dprim_Ncomb
};


// ===================================================
TexTagTypes iaTexSpecCharTypes[C_CharArrSize44] =      // TEX spec char types
{
   TexCtrl,    //   C_Nul,     /* 0x00 */
   TexCtrl,    //   C_Soh,     /* 0x01 */
   TexCtrl,    //   C_Stx,     /* 0x02 */
   TexCtrl,    //   C_Etx,     /* 0x03 */
   TexCtrl,    //   C_Eot,     /* 0x04 */
   TexCtrl,    //   C_Enq,     /* 0x05 */
   TexCtrl,    //   C_Ack,     /* 0x06 */
   TexCtrl,    //   C_Bel,     /* 0x07 */
   TexCtrl,    //   C_Bs,      /* 0x08 */
   TexCtrl,    //   C_Ht,      /* 0x09 */
   TexCtrl,    //   C_Lf,      /* 0x0a */  // !!! depends on file system
   TexCtrl,    //   C_Vt,      /* 0x0b */
   TexCtrl,    //   C_Ff,      /* 0x0c */
   TexCtrl,    //   C_Cr,      /* 0x0d */
   TexCtrl,    //   C_So,      /* 0x0e */
   TexCtrl,    //   C_Si,      /* 0x0f */
   TexCtrl,    //   C_Dle,     /* 0x10 */
   TexCtrl,    //   C_Dc1,     /* 0x11 */
   TexCtrl,    //   C_Dc2,     /* 0x12 */
   TexCtrl,    //   C_Dc3,     /* 0x13 */
   TexCtrl,    //   C_Dc4,     /* 0x14 */
   TexCtrl,    //   C_Nak,     /* 0x15 */
   TexCtrl,    //   C_Syn,     /* 0x16 */
   TexCtrl,    //   C_Etb,     /* 0x17 */
   TexCtrl,    //   C_Can,     /* 0x18 */
   TexCtrl,    //   C_Em,      /* 0x19 */
   TexCtrl,    //   C_Sub,     /* 0x1a */
   TexCtrl,    //   C_Esc,     /* 0x1b */
   TexCtrl,    //   C_Fs,      /* 0x1c */
   TexCtrl,    //   C_Gs,      /* 0x1d */
   TexCtrl,    //   C_Rs,      /* 0x1e */
   TexCtrl,    //   C_Us,      /* 0x1f */

   TexChar,    //   C_Spc,     /* Space */
   TexChar,    //   C_Excl,    /* !  Exclamation Mark (s/auktukas) */
   TexChar,    //   C_Quote,   /* "  Quotation Mark (kabute%s) */
   TexChar,    //   C_Numb,    /* #  Number Sign (Numerio zenklas) */
   TexChar,    //   C_Doll,    /* $  Currency Sign (Pinigu zenklas) */
   TexChar,    //   C_Perc,    /* %  Per Cent Sign (procento z/enklas) */
   TexChar,    //   C_Amp,     /* &  Ampersand (Ampersandas) */
   TexChar,    //   C_Apost,   /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   TexChar,    //   C_Lpar,    /* (  Left Parenthesis (kairysis skliaustas) */
   TexChar,    //   C_Rpar,    /* )  Right Parenthesis (des/inysis skliaustas) */
   TexChar,    //   C_Ast,     /* *  Asterisk (Zvaigzdute) */
   TexChar,    //   C_Plus,    /* +  Plus Sign (pliusas) */
   TexChar,    //   C_Comma,   /* ,  Comma (kablelis) */
   TexChar,    //   C_Minus,   /* -  Hyphen, Minus Sign (minusas) */
   TexChar,    //   C_Point,   /* .  Full Stop, Period, Point (tas/kas) */
   TexChar,    //   C_Slash,   /* /  Slash, Solidus (Istrizas bruksnys) */
   TexChar,    //   C_0,       /* 0 */
   TexChar,    //   C_1,       /* 1 */
   TexChar,    //   C_2,       /* 2 */
   TexChar,    //   C_3,       /* 3 */
   TexChar,    //   C_4,       /* 4 */
   TexChar,    //   C_5,       /* 5 */
   TexChar,    //   C_6,       /* 6 */
   TexChar,    //   C_7,       /* 7 */
   TexChar,    //   C_8,       /* 8 */
   TexChar,    //   C_9,       /* 9 */
   TexChar,    //   C_Colon,   /* :  Colon (dvitas/kis) */
   TexChar,    //   C_Semic,   /* ;  Semi-colon (kabliatas/kis) */
   TexChar,    //   C_Less,    /* <  Less than Sign (maz/iau) */
   TexChar,    //   C_Eq,      /* =  Equals Sign (lygybe%s z/enklas) */

   TexChar,    //   C_Great,   /* >  Greater than Sign (daugiau) */
   TexChar,    //   C_Quest,   /* ?  Question Mark (klaustukas) */

   TexChar,    //   C_At,      /* @  Commercial At (Prekybinis zenklas "Pas") */
   TexChar,    //   C_A,       /* A */
   TexChar,    //   C_B,       /* B */
   TexChar,    //   C_C,       /* C */
   TexChar,    //   C_D,       /* D */
   TexChar,    //   C_E,       /* E */
   TexChar,    //   C_F,       /* F */
   TexChar,    //   C_G,       /* G */
   TexChar,    //   C_H,       /* H */
   TexChar,    //   C_I,       /* I */
   TexChar,    //   C_J,       /* J */
   TexChar,    //   C_K,       /* K */
   TexChar,    //   C_L,       /* L */
   TexChar,    //   C_M,       /* M */
   TexChar,    //   C_N,       /* N */
   TexChar,    //   C_O,       /* O */
   TexChar,    //   C_P,       /* P */
   TexChar,    //   C_Q,       /* Q */
   TexChar,    //   C_R,       /* R */
   TexChar,    //   C_S,       /* S */
   TexChar,    //   C_T,       /* T */
   TexChar,    //   C_U,       /* U */
   TexChar,    //   C_V,       /* V */
   TexChar,    //   C_W,       /* W */
   TexChar,    //   C_X,       /* X */
   TexChar,    //   C_Y,       /* Y */
   TexChar,    //   C_Z,       /* Z */
   TexChar,    //   C_Lbrack,  /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   TexMathChar,//   C_Lslash,  /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   TexChar,    //   C_Rbrack,  /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   TexChar,    //   C_Circ,    /* ^  Circumflex Accent (Cirkumfleksas) */
   TexChar,    //   C_Underl,  /* _  Underline (Pabraukimas) */

   TexChar,    //   C_Grave,   /* `  Grave Accent (gravis) */
   TexChar,    //   C_a,       /* a */
   TexChar,    //   C_b,       /* b */
   TexChar,    //   C_c,       /* c */
   TexChar,    //   C_d,       /* d */
   TexChar,    //   C_e,       /* e */
   TexChar,    //   C_f,       /* f */
   TexChar,    //   C_g,       /* g */
   TexChar,    //   C_h,       /* h */
   TexChar,    //   C_i,       /* i */
   TexChar,    //   C_j,       /* j */
   TexChar,    //   C_k,       /* k */
   TexChar,    //   C_l,       /* l */
   TexChar,    //   C_m,       /* m */
   TexChar,    //   C_n,       /* n */
   TexChar,    //   C_o,       /* o */
   TexChar,    //   C_p,       /* p */
   TexChar,    //   C_q,       /* q */
   TexChar,    //   C_r,       /* r */
   TexChar,    //   C_s,       /* s */
   TexChar,    //   C_t,       /* t */
   TexChar,    //   C_u,       /* u */
   TexChar,    //   C_v,       /* v */
   TexChar,    //   C_w,       /* w */
   TexChar,    //   C_x,       /* x */
   TexChar,    //   C_y,       /* y */
   TexChar,    //   C_z,       /* z */
   TexMathChar,//   C_Lcurl,   /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   TexChar,    //   C_Vertl,   /* |  Vertical Line (Vertikali Linija) */
   TexMathChar,//   C_Rcurl,   /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   TexChar,    //   C_Tilde,   /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje) */

   TexCtrl,    //   C_Del,

   TexChar,    //     C_AE,
   TexChar,    //     C_ae,
   TexChar,    //     C_OE,
   TexChar,    //     C_oe,
   TexChar,    //     C_IJ,
   TexChar,    //     C_ij,
   TexChar,    //     C_ss,      /* sharp s    (german) (C_beta) */

   TexChar,                      //     C_A_Cyr,
   TexChar,                      //     C_B_Cyr,
   TexChar,                      //     C_V_Cyr,
   TexChar,                      //     C_G_Cyr,
   TexChar,                      //     C_D_Cyr,
   TexChar,                      //     C_E_Cyr,
   TexChar,                      //     C_Zh_Cyr,
   TexChar,                      //     C_Z_Cyr,
   TexChar,                      //     C_I_Cyr,
   TexChar,                      //     C_J_Cyr,
   TexChar,                      //     C_K_Cyr,
   TexChar,                      //     C_L_Cyr,
   TexChar,                      //     C_M_Cyr,
   TexChar,                      //     C_N_Cyr,
   TexChar,                      //     C_O_Cyr,
   TexChar,                      //     C_P_Cyr,
   TexChar,                      //     C_R_Cyr,
   TexChar,                      //     C_S_Cyr,
   TexChar,                      //     C_T_Cyr,
   TexChar,                      //     C_U_Cyr,
   TexChar,                      //     C_F_Cyr,
   TexChar,                      //     C_H_Cyr,
   TexChar,                      //     C_C_Cyr,
   TexChar,                      //     C_Ch_Cyr,
   TexChar,                      //     C_Sh_Cyr,
   TexChar,                      //     C_Shch_Cyr,
   TexChar,                      //     C_Hard_Cyr,
   TexChar,                      //     C_Y_Cyr,
   TexChar,                      //     C_Soft_Cyr,
   TexChar,                      //     C_Ee_Cyr,
   TexChar,                      //     C_Ju_Cyr,
   TexChar,                      //     C_Ja_Cyr,

   TexChar,                      //     C_a_Cyr,
   TexChar,                      //     C_b_Cyr,
   TexChar,                      //     C_v_Cyr,
   TexChar,                      //     C_g_Cyr,
   TexChar,                      //     C_d_Cyr,
   TexChar,                      //     C_e_Cyr,
   TexChar,                      //     C_zh_Cyr,
   TexChar,                      //     C_z_Cyr,
   TexChar,                      //     C_i_Cyr,
   TexChar,                      //     C_j_Cyr,
   TexChar,                      //     C_k_Cyr,
   TexChar,                      //     C_l_Cyr,
   TexChar,                      //     C_m_Cyr,
   TexChar,                      //     C_n_Cyr,
   TexChar,                      //     C_o_Cyr,
   TexChar,                      //     C_p_Cyr,
   TexChar,                      //     C_r_Cyr,
   TexChar,                      //     C_s_Cyr,
   TexChar,                      //     C_t_Cyr,
   TexChar,                      //     C_u_Cyr,
   TexChar,                      //     C_f_Cyr,
   TexChar,                      //     C_h_Cyr,
   TexChar,                      //     C_c_Cyr,
   TexChar,                      //     C_ch_Cyr,
   TexChar,                      //     C_sh_Cyr,
   TexChar,                      //     C_shch_Cyr,
   TexChar,                      //     C_hard_Cyr,
   TexChar,                      //     C_y_Cyr,
   TexChar,                      //     C_soft_Cyr,
   TexChar,                      //     C_ee_Cyr,
   TexChar,                      //     C_ju_Cyr,
   TexChar,                      //     C_ja_Cyr,

// gal TexMathChar?              //    /* Additional greek chars variations follow later */
   TexChar,                      //     C_Alpha,
   TexChar,                      //     C_Beta,
   TexChar,                      //     C_Gamma,
   TexChar,                      //     C_Delta,
   TexChar,                      //     C_Epsilon,
   TexChar,                      //     C_Zeta,
   TexChar,                      //     C_Eta,
   TexChar,                      //     C_Theta,
   TexChar,                      //     C_Jota,
   TexChar,                      //     C_Kappa,
   TexChar,                      //     C_Lambda,
   TexChar,                      //     C_My,
   TexChar,                      //     C_Ny,
   TexChar,                      //     C_Xi,
   TexChar,                      //     C_Omikron,
   TexChar,                      //     C_Pi,
   TexChar,                      //     C_Rho,
   TexChar,                      //     C_Sigma,
   TexChar,                      //     C_Tau,
   TexChar,                      //     C_Ypsilon,
   TexChar,                      //     C_Phi,
   TexChar,                      //     C_Chi,
   TexChar,                      //     C_Psi,
   TexChar,                      //     C_Omega,

   TexChar,                      //     C_alpha,
   TexChar,                      //     C_beta,
   TexChar,                      //     C_gamma,
   TexChar,                      //     C_delta,
   TexChar,                      //     C_epsilon,
   TexChar,                      //     C_zeta,
   TexChar,                      //     C_eta,
   TexChar,                      //     C_theta,
   TexChar,                      //     C_jota,
   TexChar,                      //     C_kappa,
   TexChar,                      //     C_lambda,
   TexChar,                      //     C_my,

   TexChar,                      //     C_ny,
   TexChar,                      //     C_xi,
   TexChar,                      //     C_omikron,
   TexChar,                      //     C_pi,
   TexChar,                      //     C_rho,
   TexChar,                      //     C_sigma,
   TexChar,                      //     C_tau,
   TexChar,                      //     C_ypsilon,
   TexChar,                      //     C_phi,
   TexChar,                      //     C_chi,
   TexChar,                      //     C_psi,
   TexChar,                      //     C_omega,

   TexChar,                      //     C_delt_Mn, /* delta_Minus    (skardi th) */

   TexDiacr, // TexChar, //      // "\\\'",  //     C_Acute,   /* '  Acute    (aku/tas, apostrofas, des/inys kirtis) */
   TexDiacr, // TexChar, // TexCtrl,  // "\\H", //  C_Dacut,   /* '' Double Acute */
   TexDiacr, // TexChar, //      // NULL,    //     C_Ogon,    /* ,  Ogonek    (nosine) */
   TexDiacr, // TexChar, //      // "\\.",   //     C_Adot,    /* .  Dot Above    (. virsuje) */
   TexDiacr, // TexChar, // TexCtrl,  // "\\v", //  C_Car,     /* v  Carron    (Pauksciukas) */
   TexDiacr, // TexChar,         // "\\=",   //     C_Macr,    /* _  Macron, Overline    (bruksnys virsuje) */
   TexDiacr, // TexChar, //      // "\\\"",  //     C_Diaer,   /* .. Diaeresis    (Umlaut) */
   TexDiacr, // TexChar, //      // NULL,    //     C_Ring,    /* o  Ring    (Circle) Above    (o virsuje, degree) */
   TexDiacr, // TexChar, //      // NULL,    //     C_Tacom,   /* '  Turned Comma Above */
   TexDiacr, // TexChar, //      // NULL,    //     C_Bcomma,  /* ,  Comma Bellow */
   TexDiacr, // TexChar, // TexCtrl,  // "\\c", //  C_Cedil,   /* ,  Cedilla    (atbula nosine) */

   TexChar,                    //    C_A_Ogon,  /* A, */
   TexChar,                    //    C_a_Ogon,  /* a, */
   TexChar,                    //    C_E_Ogon,  /* E, */
   TexChar,                    //    C_e_Ogon,  /* e, */
   TexChar,                    //    C_I_Ogon,  /* I, */
   TexChar,                    //    C_i_Ogon,  /* i, */
   TexChar,                    //    C_U_Ogon,  /* U, */
   TexChar,                    //    C_u_Ogon,  /* u, */

   TexChar,                    //    C_E_Adot,  /* E. */
   TexChar,                    //    C_e_Adot,  /* e. */
   TexChar,                    //    C_Z_Adot,  /* Z. */
   TexChar,                    //    C_z_Adot,  /* z. */

   TexChar,                    //    C_G_Cyr_Adot, /* G Cyr . */
   TexChar,                    //    C_g_Cyr_Adot, /* g Cyr . */

   TexChar,                    //    C_C_Car,   /* Cv */
   TexChar,                    //    C_c_Car,   /* cv */
   TexChar,                    //    C_D_Car,   /* Dv */
   TexChar,                    //    C_d_Car,   /* dv */
   TexChar,                    //    C_E_Car,   /* Ev */
   TexChar,                    //    C_e_Car,   /* ev */
   TexChar,                    //    C_L_Car,   /* Lv */
   TexChar,                    //    C_l_Car,   /* lv */
   TexChar,                    //    C_N_Car,   /* Nv */
   TexChar,                    //    C_n_Car,   /* nv */
   TexChar,                    //    C_R_Car,   /* Rv */
   TexChar,                    //    C_r_Car,   /* rv */
   TexChar,                    //    C_S_Car,   /* Sv */
   TexChar,                    //    C_s_Car,   /* sv */
   TexChar,                    //    C_T_Car,   /* Tv */
   TexChar,                    //    C_t_Car,   /* tv */
   TexChar,                    //    C_Z_Car,   /* Zv */
   TexChar,                    //    C_z_Car,   /* zv */

   TexChar,                    //    C_A_Macr,  /* A_ */
   TexChar,                    //    C_a_Macr,  /* a_ */
   TexChar,                    //    C_E_Macr,  /* E_ */
   TexChar,                    //    C_e_Macr,  /* e_ */
   TexChar,                    //    C_I_Macr,  /* I_ */
   TexChar,                    //    C_i_Macr,  /* i_ */
   TexChar,                    //    C_O_Macr,  /* O_ */
   TexChar,                    //    C_o_Macr,  /* o_ */
   TexChar,                    //    C_U_Macr,  /* U_ */
   TexChar,                    //    C_u_Macr,  /* u_ */

   TexChar,                    //    C_A_Diaer, /* A.. */
   TexChar,                    //    C_a_Diaer, /* a.. */
   TexChar,                    //    C_E_Diaer, /* E.. */
   TexChar,                    //    C_e_Diaer, /* e.. */
   TexChar,                    //    C_I_Diaer, /* I.. */
   TexChar,                    //    C_i_Diaer, /* i.. */
   TexChar,                    //    C_O_Diaer, /* O.. */
   TexChar,                    //    C_o_Diaer, /* o.. */
   TexChar,                    //    C_U_Diaer, /* U.. */
   TexChar,                    //    C_u_Diaer, /* u.. */
   TexChar,                    //    C_Y_Diaer, /* Y.. */
   TexChar,                    //    C_y_Diaer, /* y.. */

   TexChar,                        //   C_E_Cyr_Diaer, /* E.. */
   TexChar,                        //   C_e_Cyr_Diaer, /* e.. */

   TexChar,                   //     C_A_Ring,  /* Ao */
   TexChar,                   //     C_a_Ring,  /* ao */
   TexChar,                   //     C_U_Ring,  /* Uo */
   TexChar,                   //     C_u_Ring,  /* uo */

   TexChar,                   //     C_G_Tacom, /* G' */
   TexChar,                   //     C_g_Tacom, /* g' */

   TexChar,                   //     C_G_Bcomma,/* G, */
   TexChar,                   //     C_g_Bcomma,/* g, */
   TexChar,                   //     C_K_Bcomma,/* K, */
   TexChar,                   //     C_k_Bcomma,/* k, */
   TexChar,                   //     C_L_Bcomma,/* L, */
   TexChar,                   //     C_l_Bcomma,/* l, */
   TexChar,                   //     C_N_Bcomma,/* N, */
   TexChar,                   //     C_n_Bcomma,/* n, */
   TexChar,                   //     C_R_Bcomma,/* R, */
   TexChar,                   //     C_r_Bcomma,/* r, */

   TexChar,                   //     C_C_Cedil, /* C, */
   TexChar,                   //     C_c_Cedil, /* c, */
   TexChar,                   //     C_S_Cedil, /* S, */
   TexChar,                   //     C_s_Cedil, /* s, */
   TexChar,                   //     C_T_Cedil, /* T, */
   TexChar,                   //     C_t_Cedil, /* t, */

   TexChar,                    //    C_A_Grave, /* A` */
   TexChar,                    //    C_a_Grave, /* a` */
   TexChar,                    //    C_E_Grave, /* E` */
   TexChar,                    //    C_e_Grave, /* e` */
   TexChar,                    //    C_I_Grave, /* I` */
   TexChar,                    //    C_i_Grave, /* i` */
   TexChar,                    //    C_O_Grave, /* O` */
   TexChar,                    //    C_o_Grave, /* o` */
   TexChar,                    //    C_U_Grave, /* U` */
   TexChar,                    //    C_u_Grave, /* u` */

   TexChar,                    //    C_A_Acute, /* A' */
   TexChar,                    //    C_a_Acute, /* a' */
   TexChar,                    //    C_C_Acute, /* C' */
   TexChar,                    //    C_c_Acute, /* c' */
   TexChar,                    //    C_E_Acute, /* E' */
   TexChar,                    //    C_e_Acute, /* e' */
   TexChar,                    //    C_I_Acute, /* I' */
   TexChar,                    //    C_i_Acute, /* i' */
   TexChar,                    //    C_L_Acute, /* L' */
   TexChar,                    //    C_l_Acute, /* l' */
   TexChar,                    //    C_N_Acute, /* N' */
   TexChar,                    //    C_n_Acute, /* n' */
   TexChar,                    //    C_O_Acute, /* O' */
   TexChar,                    //    C_o_Acute, /* o' */
   TexChar,                    //    C_R_Acute, /* R' */
   TexChar,                    //    C_r_Acute, /* r' */

   TexChar,                    //    C_S_Acute, /* S' */
   TexChar,                    //    C_s_Acute, /* s' */
   TexChar,                    //    C_U_Acute, /* U' */
   TexChar,                    //    C_u_Acute, /* u' */
   TexChar,                    //    C_Y_Acute, /* Y' */
   TexChar,                    //    C_y_Acute, /* y' */
   TexChar,                    //    C_Z_Acute, /* Z' */
   TexChar,                    //    C_z_Acute, /* z' */

   TexChar,                    //       C_K_Cyr_Acute, /* K Cyr ' */
   TexChar,                    //       C_k_Cyr_Acute, /* k Cyr ' */

   TexChar,                    //       C_O_Dacut, /* O'' */
   TexChar,                    //       C_o_Dacut, /* o'' */
   TexChar,                    //       C_U_Dacut, /* U'' */
   TexChar,                    //       C_u_Dacut, /* u'' */

   TexChar,                    //       C_A_Tilde, /* A~ */
   TexChar,                    //       C_a_Tilde, /* a~ */
   TexChar,                    //       C_N_Tilde, /* N~ */
   TexChar,                    //       C_n_Tilde, /* n~ */
   TexChar,                    //       C_O_Tilde, /* O~ */
   TexChar,                    //       C_o_Tilde, /* o~ */

   TexChar,                    //       C_L_Slash, /* L/ */
   TexChar,                    //       C_l_Slash, /* l/ */
   TexChar,                    //       C_O_Slash, /* O/ */
   TexChar,                    //       C_o_Slash, /* o/ */

   TexChar,                    //       C_A_Circ,  /* A^ */
   TexChar,                    //       C_a_Circ,  /* a^ */
   TexChar,                    //       C_E_Circ,  /* E^ */
   TexChar,                    //       C_e_Circ,  /* e^ */
   TexChar,                    //       C_I_Circ,  /* I^ */
   TexChar,                    //       C_i_Circ,  /* i^ */
   TexChar,                    //       C_O_Circ,  /* O^ */
   TexChar,                    //       C_o_Circ,  /* o^ */
   TexChar,                    //       C_U_Circ,  /* U^ */
   TexChar,                    //       C_u_Circ,  /* u^ */

   TexChar,                   //        C_D_Minus, /* D- Island. */
   TexChar,                   //        C_d_Minus, /* d- */
   TexChar,                   //        C_H_Minus, /* H- */
   TexChar,                   //        C_h_Minus, /* h- */
   TexChar,                   //        C_P_Minus, /* P- */
   TexChar,                   //        C_p_Minus, /* p- */

   TexChar, // TexCtrl,       // "\\enspace", // n-width no break space - C_NBSP,   /* No break space */
// (unsigned char *)"\\thinspace",    // thin no break space, width = 1/4 m ???
// (unsigned char *)"\\negthinspace", // negative thin no break space, width = -1/4 m ???

   TexChar,                   //        C_Rouble,  /* rublis, " Cyr */
   TexChar,                   //        C_Pound,   /* svaras, L/ */
   TexChar,                   //        C_Yenna,   /* jena, Y- */
   TexChar,                   //        C_cent,    /* c/ */

   TexChar,                   //        C_Para,    /* paragrafas, # engl. */
   TexChar,                   //        C_Pren,    /* paragraph end sign    (pastraipos pabaiga, C_pi - pi) */
   TexMathChar,   // TexChar, //        C_Multipl, /* x */ AKLZ reikëjo maþesnio, o matematiniam reþime fontai nerodo // RLZ vël gràþinau matematiná
   TexMathChar,               //        C_Divide,  /* -:- */
   TexMathChar,               //        C_PlMin,   /* -+- */
   TexMathChar,               //        C_1up,     /* 1 virsuj */
   TexMathChar,               //        C_2up,     /* 2 virsuj, kvadratu */
   TexMathChar,               //        C_3up,     /* 3 virsuj, kubu */
   TexMathChar,               //        C_a_up,    /* a virsuj */
   TexMathChar,               //        C_o_up,    /* o virsuj */
   TexChar,                   //        C_Half,    /* 1/2 */
   TexChar,                   //        C_Quart,   /* 1/4 */
   TexChar,                   //        C_34,      /* 3/4 */
   TexChar,                   //        C_Ldopang, /* << */
   TexChar,                   //        C_Rdopang, /* >> */
   TexChar,                   //        C_Lang,    /* < */
   TexChar,                   //        C_Rang,    /* > */
   TexChar,                   //        C_Dvertl,  /* | Koi-7-0 */
   TexChar,                   //        C_Rminbr,  /* ^ Koi-7-0    (neiginys,  -| ) */
   TexChar,                   //        C_Lminbr,  /* |- */
   TexChar,                   //        C_Lpoint,  /* mazas taskas vidury */
   TexCtrl,       // TexChar, //        C_Bpoint,  /* didelis taskas vidury */ // TexCtrl, nes naudojamas kaip DOUBLE_ENTRIES_KPCHAR, þr. C_hBpoint
   TexChar,                   // ",," ???  C_LBquote, /* ,,    (left bellow, double comma, liet. kaire) */
   TexChar,                   //        C_LAquote, /* ''    (left above, double comma above, angl. desine) */

   TexChar,                   //        C_Rquote,  /* ``    (right, reversed double comma above, liet. desine, angl. kaire) */
   TexChar,                   // ",",   C_LBapost, /* ,    (' left bellow, comma, liet. kaire) */
   TexChar,                   // "\'",  C_LAapost, /* '    (' left above, comma above, angl. desine) */
   TexChar,                   // "`",   C_Rapost,  /* `    (' right, grave, reversed comma above, liet. desine, angl. kaire) */
   TexChar,                   //        C_Qst_Ov,  /* apverstas ? */
   TexChar,                   //        C_Ex_Ov,   /* apverstas ! */
   TexChar,                   //        C_Dots,    /* ... daugtaskis */
   TexChar,                   //        C_Prom,    /* %o promiles */
   TexChar,                   //        C_TM,      /* TM, Trade Mark */
   TexChar,                   //    C_CO,      /*    (C) Copyright */
   TexChar, /* TexMathChar, */ //    C_RO,      /*    (R) */ // AKLZ matematiniam reþime nerodo

// gal TexMathChar?           //    /* Additional greek chars, look SGML DTD */
   TexChar,                   //     C_epsilon_var,
   TexChar,                   //     C_theta_var,
   TexChar,                   //     C_DiGamma,
   TexChar,                   //     C_digamma,
   TexChar,                   //     C_kappa_var,
   TexChar,                   //     C_DiLambda,
   TexChar,                   //     C_dilambda,
   TexChar,                   //     C_pi_var,
   TexChar,                   //     C_rho_var,
   TexChar,                   //     C_Sigma_var,
   TexChar,                   //     C_sigma_var,
   TexChar,                   //     C_phi_var,

             /* additional accents, all of them have no width (over the next letter) */
   TexDiacr,         // "\\`",   // C_GraveAcc,    /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   TexDiacr,         // "\\^",   // C_CircAcc,     /* ^  Circumflex Accent (C_Circ), over the next letter */
   TexDiacr,         // "\\~",   // C_TildeAcc,    /* ~  Tilde (C_Tilde), over the next letter */
   TexDiacr, // TexCtrl, // "\\u", // C_BreveAcc,    /* u  (lankelis virsuje) */
   TexDiacr, // TexCtrl, // "\\not", // C_SlashAcc,    /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   TexDiacr, // TexCtrl, // "\\d", // C_BdotAcc,     /* .  Dot bellow */
   TexDiacr, // TexCtrl, // "\\b", // C_UnderlAcc,   /* _  Underline (Pabraukimas) */

   TexChar, // TexMathChar,   //     C_prim,    /* strichas prie raides (renkamas po raides) (C_Acute, C_Apost) */
   TexChar, // TexMathChar,   //     C_dprim,   /* du strichai (C_Dacut) */

   TexMathChar, // TexChar,   //     C_Each,    /* V - "kiekvienam- apversta A raide */
   TexMathChar, // TexChar,   //     C_Exists,  /* E - "egzistuoja- apversta E raide */

   TexMathChar,               //     C_Aleph,   /* N - alefas */
   TexMathChar,               //     C_Im,      /* C_I_Got */
   TexMathChar,               //     C_Re,      /* C_R_Got */
   TexMathChar,               //     C_wp,      /* C_p_Got */

   TexMathChar, // TexChar,   //     C_le,      /* <= - maziau arba lygu */
   TexMathChar, // TexChar,   //     C_ge,      /* >= - daugiau arba lygu */
   TexMathChar, // TexChar,   //     C_ne,      /* =/= - nelygu */ // AKLZ_08 mat. reþime nesuveikia fonto maþinimas
   TexMathChar, // TexChar,   //     C_ll,      /* << */
   TexMathChar, // TexChar,   //     C_gg,      /* >> */
   TexMathChar, // TexChar,   //     C_sim,     /* ~ - panasu */
   TexMathChar, // TexChar,   //     C_simeq,   /* ~- - panasu arba sutampa */
   TexMathChar, // TexChar,   //     C_approx,  /* ~~ - apytiksliai lygu */
   TexMathChar, // TexChar,   //     C_cong,    /* ~= - kongruentu */
   TexMathChar, // TexChar,   //     C_equiv,   /* = - triguba lygybe - ekvivalentu */

   TexMathChar,               //     C_sqrt,    /* square root */
   TexMathChar,               //     C_int,     /* integralas */
   TexMathChar,               //     C_oint,    /* kreivinis integralas */
   TexMathChar,               //     C_Sum,     /* sum sign (C_Sigma) */
   TexMathChar,               //     C_Prod,    /* C_Pi */
   TexMathChar,               //     C_O_times, /* OX - O perbraukta istrizai */
   TexMathChar,               //     C_O_plus,  /* O+ - O perbraukta pliusu */

   TexMathChar,               //     C_infty,   /* infinity - begalybe */
   TexMathChar,               //     C_propto,  /* (C_alpha) */
   TexMathChar,               //     C_part,    /* partial - C_delta */
   TexMathChar,               //     C_empty,   /* O/ (C_O_Slash) */
   TexMathChar,               //     C_triangle,/* C_Delta - trikampis */
   TexMathChar,               //     C_nabla,   /* V - C_Delta apversta */

   TexMathChar,               //     C_perp,    /* T apversta - statmena */
   TexMathChar,               //     C_angle,   /* < - kampas */

   TexChar,                   //     C_langle,  /* < - skliaustas */
   TexChar,                   //     C_rangle,  /* > - skliaustas */

   TexMathChar,               //     C_cap,     /* U apversta - pjuvis */
   TexMathChar,               //     C_cup,     /* U - junginys */

   TexMathChar,               //     C_vee,     /* V */
   TexMathChar,               //     C_wedge,   /* C_Lambda */

   TexMathChar,               //     C_supset,  /* D - virsaibis */
   TexMathChar,               //     C_supseteq,/* D= - virsaibis arba sutampa */
   TexMathChar,               //     C_subset,  /* C - poaibis */
   TexMathChar,               //     C_subseteq,/* C= - poaibis arba sutampa */
   TexMathChar,               //     C_nsubset, /* C/ - nepoaibis */

   TexMathChar,               //     C_in,      /* C_epsilon_var - priklauso */
   TexMathChar,               //     C_notin,   /* C_epsilon_var_Slash - nepriklauso */
   TexMathChar,               //     C_ni,      /* C_epsilon_var apsuktas - apima */

   TexMathChar,                        //  C_leftarr,       /* <-- */
   TexMathChar,                        //  C_rightarr,      /* --> */
   TexMathChar,                        //  C_leftrightarr,  /* <--> */
   TexMathChar,                        //  C_uparr,         /* ^| */
   TexMathChar,                        //  C_downarr,       /* |v */
   TexMathChar,                        //  C_updownarr,     /* ^|v */

   TexChar,                            //  C_Leftarr,       /* <== */
   TexChar,                            //  C_Rightarr,      /* ==> */
   TexChar,                            //  C_Leftrightarr,  /* <==> */
   TexChar,                            //  C_Uparr,         /* ^|| */
   TexChar,                            //  C_Downarr,       /* ||v */
   TexChar,                            //  C_Updownarr,     /* ^||v */

   TexChar,                            //  C_mid,             /* | */
   TexChar,                            //  C_paral,           /* || */

   TexChar,                            // C_diamond,     /* rombas */

   TexChar,                         //     C_Club,        /* giles */
   TexChar,                         //     C_Diamond,     /* bugnai */
   TexChar,                         //     C_Heart,       /* cirvai sirdys */
   TexChar,                         //     C_Spade,       /* pikai lapai */

   TexChar,       // TexCtrl, // TexChar suveikia, o TexCtrl kaþkodël duoda tarpà RLZ06 // Nijolë P. sakë apskliaustas nesuveikia VLZ08e //     C_hyph,    /* hided hyphenation sign ("\-" for TEX) */
   TexCtrl,       // TexChar, //     C_break,   /* line break character */

   TexChar,                   //     C_a_Car,   /* av - laikinai, po to ismesti !!! */

   TexChar,                   //     C_euro,    /* C= euro piniginis vienetas !!! kelti prie pinigu */

   TexChar,                   //     C_deg,     /* degree - panasiai, kaip C_Ring, tik desineje */
   TexChar,                   //     C_micro,   /* mikro - panasiai, kaip C_my */
   TexChar,                   //     C_Ohm,     /* Ohm sign - panasiai, kaip C_Omega */
   TexChar,                   //     C_Angst,   /* Angstroem - C_A_Ring */

   TexChar,                   //     C_Horl,    /* horizontal line --- */

   TexMathChar,               //     C_Dag,    /* Dagger +| (kryzius) */
   TexMathChar,               //     C_Ddag,   /* Double dagger +|+ (Kestucio kryzius) */

   TexChar,                   //     C_ff,     /* ff ligature */
   TexChar,                   //     C_fi,     /* fi ligature */
   TexChar,                   //     C_fj,     /* fj ligature */
   TexChar,                   //     C_ffi,    /* ff ligature */
   TexChar,                   //     C_ffl,    /* ff ligature */
   TexChar,                   //     C_fl,     /* ff ligature */

   TexChar,                   //     C_and,    /* ^ logical and */
   TexChar,                   //     C_or,     /* V logical or */

   TexChar,                   //     C_fun,    /* f function of */

   TexChar,                   //     C_MinPl,  /* -+ minus plus */

   TexChar,                   //     C_EnDash, /* -- - vidutinio ilgio bruksnys */
   TexChar,                   //     C_EmDash, /* --- - ilgas bruksnys */

   TexChar,                   //     C_Cdots,  /* ... - daugtaskis per viduri */
   TexChar,                   //     C_WideTilde, /* ~ didele tilde */

   TexMathChar, // TexCtrl,   //     C_QemSpc, /* 1/4 m space */
// (unsigned char *)"\\>",    //                  1/3 m space
// (unsigned char *)"\\;",    //                  5/12 m space
// (unsigned char *)"\\!",    //                 -1/4 m space (negative)
   TexChar, // TexCtrl,       //     C_EnSpc,  /* n space */, eilute gali luzti
   TexChar, // TexCtrl,       //     C_EmSpc,  /* m space */, eilute gali luzti
   TexChar, // TexCtrl,       //     C_2emSpc, /* 2 m space */, eilute gali luzti

   TexCtrl,                   //     C_NewPar, /* paragraph end control character */

   TexChar,                   //     C_Y_Grave,  Y`
   TexChar,                   //     C_y_Grave,  y`
   TexChar,                   //     C_E_Tilde,  E~
   TexChar,                   //     C_e_Tilde,  e~
   TexChar,                   //     C_I_Tilde,  I~
   TexChar,                   //     C_i_Tilde,  i~
   TexChar,                   //     C_U_Tilde,  U~
   TexChar,                   //     C_u_Tilde,  u~
   TexChar,                   //     C_Y_Tilde,  Y~
   TexChar,                   //     C_y_Tilde,  y~
   TexChar,                   //     C_L_Tilde,  L~
   TexChar,                   //     C_l_Tilde,  l~
   TexChar,                   //     C_M_Tilde,  M~
   TexChar,                   //     C_m_Tilde,  m~
   TexChar,                   //     C_R_Tilde,  R~
   TexChar,                   //     C_r_Tilde,  r~
   TexChar,                   //     C_A_Ogon_Acute,
   TexChar,                   //     C_a_Ogon_Acute,
   TexChar,                   //     C_E_Ogon_Acute,
   TexChar,                   //     C_e_Ogon_Acute,
   TexChar,                   //     C_E_Adot_Acute,
   TexChar,                   //     C_e_Adot_Acute,
   TexChar,                   //     C_I_Ogon_Acute,
   TexChar,                   //     C_i_Ogon_Acute,
   TexChar,                   //     C_U_Ogon_Acute,
   TexChar,                   //     C_u_Ogon_Acute,
   TexChar,                   //     C_U_Macr_Acute,
   TexChar,                   //     C_u_Macr_Acute,
   TexChar,                   //     C_A_Ogon_Grave,
   TexChar,                   //     C_a_Ogon_Grave,
   TexChar,                   //     C_E_Ogon_Grave,
   TexChar,                   //     C_e_Ogon_Grave,
   TexChar,                   //     C_E_Adot_Grave,
   TexChar,                   //     C_e_Adot_Grave,
   TexChar,                   //     C_I_Ogon_Grave,
   TexChar,                   //     C_i_Ogon_Grave,
   TexChar,                   //     C_U_Ogon_Grave,
   TexChar,                   //     C_u_Ogon_Grave,
   TexChar,                   //     C_U_Macr_Grave,
   TexChar,                   //     C_u_Macr_Grave,
   TexChar,                   //     C_A_Ogon_Tilde,
   TexChar,                   //     C_a_Ogon_Tilde,
   TexChar,                   //     C_E_Ogon_Tilde,
   TexChar,                   //     C_e_Ogon_Tilde,
   TexChar,                   //     C_E_Adot_Tilde,
   TexChar,                   //     C_e_Adot_Tilde,
   TexChar,                   //     C_I_Ogon_Tilde,
   TexChar,                   //     C_i_Ogon_Tilde,
   TexChar,                   //     C_U_Ogon_Tilde,
   TexChar,                   //     C_u_Ogon_Tilde,
   TexChar,                   //     C_U_Macr_Tilde,
   TexChar,                   //     C_u_Macr_Tilde,

// phonetic characters; vowels:
   TexChar,                   //     C_ph_a,        // low back unrounded; a, open a; italic C_a
   TexChar,                   //     C_ph_a_inv,    // low back rounded; oa; inverted italic C_a

   TexChar,                   //     C_ph_a_sh,     // low-mid back unrounded; short a; inverted C_v
   TexChar,                   //     C_ph_o_sh,     // low-mid back rounded; short o, open o; inverted C_c
// TexChar,                   //     C_ph_o,        // mid back rounded?; o, closed o; C_o

   TexChar,                   //     C_ph_u_sh,     // semi-high back rounded; short u, short open u; C_ypsilon
   TexChar,                   //     C_ph_w_sh,     // semi-high back rounded; short u, short open u, obsolete; C_omega
// TexChar,                   //     C_ph_u,        // semi-high central rounded?; u, closed u; C_u
// TexChar,                   //     C_ph_u_soft,   // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   TexChar,                   //     C_ph_e_sh,     // low-mid front unrounded; short e, open e; C_epsilon
   TexChar,                   //     C_ph_ae,       // low front unrounded?; e, open e; C_ae
// TexChar,                   //     C_ph_e_cl,     // high central unrounded?; closed e, german e; C_e
   TexChar,                   //     C_ph_e_sh_inv, // low-mid central unrounded; hard e; inverted C_epsilon
   TexChar,                   //     C_ph_e_inv,    // mid central unrounded; reduced e; inverted C_e

   TexChar,                   //     C_ph_i_sh,     // semi-high front unrounded; short i, short open i; C_i without dot
// TexChar,                   //     C_ph_i,        // high front unrounded?; i, closed i; C_i

// phonetic characters; consonants:
   TexChar,                   //     C_ph_sh,       // sh; C_f, C_int
   TexChar,                   //     C_ph_zh,       // zh; C_3
   TexChar,                   //     C_ph_tsh,      // tsh; C_t C_f, C_t C_int
   TexChar,                   //     C_ph_dzh,      // dzh; C_d C_3
   TexChar,                   //     C_ph_th_b,     // breath th; C_theta
   TexChar,                   //     C_ph_th_v,     // voiced th; C_delt_Mn, (C_delta_Minus)
   TexChar,                   //     C_ph_ng,       // nasal g; C_eta
   TexChar,                   //     C_ph_g,        // g; italic C_g

// additional phonetic characters:
   TexChar,                   //     C_ph_oe,       // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   TexChar,                   //     C_ph_o_slash,  // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   TexChar,                   //     C_ph_a_l,      // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   TexChar,                   //     C_ph_e_inv_l,  // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   TexChar,                   //     C_ph_i_l,      // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   TexChar,                   //     C_ph_o_l,      // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   TexChar,                   //     C_ph_u_l,      // ; u long; C_u C_Colon

   TexChar,                   //     C_ph_a_n,      // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   TexChar,                   //     C_ph_a_str_n,  // ; a~; C_a_Tilde
   TexChar,                   //     C_ph_e_n,      // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   TexChar,                   //     C_ph_oe_n,     // ; oe nasal; oe~, C_oe C_TildeAcc
   TexChar,                   //     C_ph_o_n,      // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   TexChar,                   //     C_ph_ch,       // german ch; C_c_Cedil

// diphtongs
   TexChar,                   //     C_ph_ai_d,     //  C_a C_LigaLow C_i
   TexChar,                   //     C_ph_ae_d,     //  C_a C_LigaLow C_e
   TexChar,                   //     C_ph_ao_d,     //  C_a C_LigaLow C_o
   TexChar,                   //     C_ph_au_d,     //  C_a C_LigaLow C_u
   TexChar,                   //     C_ph_ei_d,     //  C_e C_LigaLow C_i
   TexChar,                   //     C_ph_eu_d,     //  C_e C_LigaLow C_u
   TexChar,                   //     C_ph_ie_d,     //  C_i C_LigaLow C_e
   TexChar,                   //     C_ph_oe_d,     //  C_ph_o_sh C_LigaLow C_ph_o_slash
   TexChar,                   //     C_ph_oy_d,     //  C_ph_o_sh C_LigaLow C_y
   TexChar,                   //     C_ph_uo_d,     //  C_u C_LigaLow C_o

// breved phonetics
   TexChar,                   //     C_ph_i_Brev,  // ; j; C_i_Brev
   TexChar,                   //     C_ph_o_Brev,  //  C_o_Brev
   TexChar,                   //     C_ph_u_Brev,  //  C_u_Brev

// liga accents (for diphtongs)
   TexDiacr,                  //     C_LigaUp,      // lankelis virs dvieju raidziu
   TexDiacr,                  //     C_LigaLow,     // lankelis po dviem raidem

   TexMathChar,               //     C_MidRing,     // mazas apskritimas viduryje (tusciaviduris bulletas - kaip C_Bpoint)

   TexChar,                   //     C_ph_acc,       // C_Apost
   TexChar,                   //     C_ph_acc_low,   // C_Comma

   TexChar,                   //    C_square,       // tusciaviduris kvadratas viduryje

   TexChar,                   //     C_male,         // vyr. lytis, male sex, mars, o^
   TexChar,                   //     C_female,       // mot. lytis, female sex, venus, o+

   TexChar,                            //    C_O_ring
   TexChar,                            //    C_O_dot

   TexChar,                            //    C_BigRing,     // didelis apskritimas, C_O

   TexChar,                            //    C_longleftarr,       /* <---- */
   TexChar,                            //   C_longrightarr,      /* ----> */

   TexChar,                            //   C_smile

   TexChar,                            //     C_box,         // pilnaviduris kvadratas viduryje

// DOS frames
   TexChar,                   //     C_v_b,       // vert; ne DOS-e - C_Vertl
   TexChar,                   //     C_h_b,       // hor; ne DOS-e - C_Horl
   TexChar,                   //     C_vh_b,      // vert hor
   TexChar,                   //     C_vl_b,      // vert left
   TexChar,                   //     C_vr_b,      // vert right
   TexChar,                   //     C_hu_b,      // hor up
   TexChar,                   //     C_hd_b,      // hor down
   TexChar,                   //     C_ul_b,      // up left
   TexChar,                   //     C_dl_b,      // down left
   TexChar,                   //     C_ur_b,      // up right
   TexChar,                   //     C_dr_b,      // down right

   TexChar,                   //     C_2v_b,      // double vert; C_paral
   TexChar,                   //     C_2h_b,      // double hor
   TexChar,                   //     C_2v2h_b,    // double vert double hor
   TexChar,                   //     C_2v2l_b,    // double vert double left
   TexChar,                   //     C_2v2r_b,    // double vert double right
   TexChar,                   //     C_2h2u_b,    // double hor double up
   TexChar,                   //     C_2h2d_b,    // double hor double down
   TexChar,                   //     C_2u2l_b,    // double up double left
   TexChar,                   //     C_2d2l_b,    // double down double left
   TexChar,                   //     C_2u2r_b,    // double up double right
   TexChar,                   //     C_2d2r_b,    // double down double right

   TexChar,                   //     C_2vh_b,     // double vert hor
   TexChar,                   //     C_2vl_b,     // double vert left
   TexChar,                   //     C_2vr_b,     // double vert right
   TexChar,                   //     C_h2u_b,     // hor double up
   TexChar,                   //     C_h2d_b,     // hor double down
   TexChar,                   //     C_2ul_b,     // double up left
   TexChar,                   //     C_2dl_b,     // double down left
   TexChar,                   //     C_2ur_b,     // double up right
   TexChar,                   //     C_2dr_b,     // double down right

   TexChar,                   //     C_v2h_b,     // vert double hor
   TexChar,                   //     C_v2l_b,     // vert double left
   TexChar,                   //     C_v2r_b,     // vert double right
   TexChar,                   //     C_2hu_b,     // double hor up
   TexChar,                   //     C_2hd_b,     // double hor down
   TexChar,                   //     C_u2l_b,     // up double left
   TexChar,                   //     C_d2l_b,     // down double left
   TexChar,                   //     C_u2r_b,     // up double right
   TexChar,                   //     C_d2r_b,     // down double right

   TexChar,                   //     C_block,     // pilnaviduris kvadratas per visa laukeli
   TexChar,                   //     C_dgrblk,    // tamsiai pilkas ---//--- (75% shaded)
   TexChar,                   //     C_grblk,     // pilkas ---//--- (50% shaded)
   TexChar,                   //     C_lgrblk,    // sviesiai pilkas ---//--- (25% shaded)
   TexChar,                   //     C_uphblk,    // pilnaviduris staciakampis per puse laukelio virsuje
   TexChar,                   //     C_dnhblk,    // ---//--- apacioje
   TexChar,                   //     C_lthblk,    // ---//--- kaireje
   TexChar,                   //     C_rthblk,    // ---//--- desineje

   TexChar,                   //     C_utrif,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   TexChar,                   //     C_dtrif,     // pilnaviduris trikampis zemyn
   TexChar,                   //     C_ltrif,     // pilnaviduris trikampis i kaire
   TexChar,                   //     C_rtrif,     // pilnaviduris trikampis i desine

   TexChar,                   //     C_ph_uu_sh,       // phonetics: semi-high back rounded; short u, short open u; inverted C_Omega

   TexChar, // TexCtrl,       //     C_hhyph,          // hard hyphen - zodzio kelimas per prievarta -\break
   TexTag, // TexChar,        //     C_sbreak,         // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   TexChar,                   //     C_hSpc,           // hard space - technical space after TEX commands - do not process
   TexChar,                   //     C_hbreak,         // break su \hfill, xmlsty keiciamas is C_Cr ("\r")
   TexChar,                   //     C_lSpc,           // last space - space, to be changed to C_NBSP after LAST_WORD_LEN
   TexChar,                   //     C_hlSpc,          // hard last space - C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   TexChar,                   //     C_utrif_rtf,      // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   TexChar,                   //     C_dtrif_rtf,      // pilnaviduris trikampis zemyn
   TexChar,                   //     C_ltrif_rtf,      // pilnaviduris trikampis i kaire
   TexChar,                   //     C_rtrif_rtf,      // pilnaviduris trikampis i desine

// erdvines rodykles - zr. mcm_src.48d mac_p.rtf lizdas 2231
   TexChar,                   //     C_3DTopLightLeftArrowHead,
   TexChar,                   //     C_3DBotLightLeftArrowHead,
   TexChar,                   //     C_3DTopLightRightArrowHead,
   TexChar,                   //     C_3DBotLightRightArrowHead,
   TexChar,                   //     C_3DLeftLightUpArrowHead,
   TexChar,                   //     C_3DRightLightUpArrowHead,
   TexChar,                   //     C_3DLeftLightDownArrowHead,
   TexChar,                   //     C_3DRightLightDownArrowHead,

   TexMathChar,               //     C_MinusMath

   TexChar,                   //     C_ZeroWidthSpace

   TexChar,                   //     C_ph_glot_stop

   TexChar,                   //     C_AcuteNcomb
   TexChar,                   //     C_CedilNcomb
   TexChar,                   //     C_MacrNcomb

   TexChar,    //   C_DollNctrl

   TexChar,                   //     C_OgonNcomb

   TexChar,                   //     C_No

   TexChar,                   //     C_CarNcomb
   TexChar,                   //     C_DiaerNcomb
   TexChar,                   //     C_TildeNcomb

   TexChar,                   //     C_utri
   TexChar,                   //     C_dtri
   TexChar,                   //     C_ltri
   TexChar,                   //     C_rtri

   TexChar,                   //     C_Oline

   TexChar,                   //     C_R_Oline
   TexChar,                   //     C_X_Oline

   TexChar,   // TexMathChar, //     C_leqslant
   TexChar,   // TexMathChar, //     C_geqslant

   TexChar,                   //     C_i_Grave_Dotless
   TexChar,                   //     C_i_Acute_Dotless
   TexChar,                   //     C_i_Tilde_Dotless

   TexChar,                   //     C_A_Cyr_Acute,
   TexChar,                   //     C_E_Cyr_Acute,
   TexChar,                   //     C_I_Cyr_Acute,
   TexChar,                   //     C_O_Cyr_Acute,
   TexChar,                   //     C_U_Cyr_Acute,
   TexChar,                   //     C_Y_Cyr_Acute,
   TexChar,                   //     C_Ee_Cyr_Acute,
   TexChar,                   //     C_Ju_Cyr_Acute,
   TexChar,                   //     C_Ja_Cyr_Acute,

   TexChar,                   //     C_a_Cyr_Acute,
   TexChar,                   //     C_e_Cyr_Acute,
   TexChar,                   //     C_i_Cyr_Acute,
   TexChar,                   //     C_o_Cyr_Acute,
   TexChar,                   //     C_u_Cyr_Acute,
   TexChar,                   //     C_y_Cyr_Acute,
   TexChar,                   //     C_ee_Cyr_Acute,
   TexChar,                   //     C_ju_Cyr_Acute,
   TexChar,                   //     C_ja_Cyr_Acute,

   TexChar, // TexTag,        //     C_NullSpc

   TexChar,                   //     C_Dash_Diaer

   TexChar,                   //     C_bdiamond

   TexChar,                   //     C_DegCels

   TexChar, // TexMathChar,   //     C_hBpoint,  /* didelis taskas vidury */ // ðiaip \bullet yra TexMathChar, bet aklz08 kaþko neiðëjo padaryt

// ----------------------- old style cyrillic
   TexChar,                   //     C_Fita_Cyr
   TexChar,                   //     C_fita_Cyr
   TexChar,                   //     C_Yat_Cyr
   TexChar,                   //     C_yat_Cyr

   TexChar, // TexMathChar,   //     C_checkmark

   TexChar, // TexMathChar,   //     C_prim_Ncomb
   TexChar, // TexMathChar,   //     C_dprim_Ncomb
};

