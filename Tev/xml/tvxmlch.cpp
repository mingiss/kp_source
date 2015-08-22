// ==================================================
// tvxmlch.cpp
// HTML spec. chars entities
//

// ================================================== definitions
#include "stdafx.h"

#include "envir.h"

#if CompilerGr==Msvc
#include <afx.h>
#endif
#include <string.h>
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
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "tvxml.h"

// ===================================================
const unsigned char *plpszaHtmSpecCharTags[C_CharArrSize44] =      // HTML spec char tags for Chars16
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
   (unsigned char *)NULL,    //   C_Lf,      /* 0x0a */  // !!! depends on file system
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

   (unsigned char *)" ",     // "&space;",   //   C_Spc,     /* Space */
   (unsigned char *)"!",     // "&exclam;",  // "&excl;",   // SGML  // C_Excl,    /* !  Exclamation Mark (s/auktukas) */
   (unsigned char *)"&quot;", // =SGML // "\"",    //   C_Quote,   /* "  Quotation Mark (kabute%s) */
   (unsigned char *)"&hash;", // "#",     // "&num;",    // SGML  // C_Numb,    /* #  Number Sign (Numerio zenklas) */
   (unsigned char *)"$",     // "&dlr;",  // "&dollar;", // SGML  // C_Doll,    /* $  Currency Sign (Pinigu zenklas) */
   (unsigned char *)"%",     // "&pct;",  // "&percnt;", // SGML  // C_Perc,    /* %  Per Cent Sign (procento z/enklas) */
   (unsigned char *)"&amp;", // =SGML        //   C_Amp,     /* &  Ampersand (Ampersandas) */
   (unsigned char *)"\'",    // "&apos;", // =SGML //   C_Apost,   /* '  Apostrophe (Apostrofa, apostrofas, kablelio formos) */
   (unsigned char *)"(",     // "&lparen;",  // "&lpar;",   // SGML // C_Lpar,    /* (  Left Parenthesis (kairysis skliaustas) */
   (unsigned char *)")",     // "&rparen;",  // "&rpar;",   // SGML // C_Rpar,    /* )  Right Parenthesis (des/inysis skliaustas) */
   (unsigned char *)"*",     // "&ast;",  // =SGML //   C_Ast,    /* *  Asterisk (Zvaigzdute) */
   (unsigned char *)"+",     // "&plus;", // =SGML //   C_Plus,   /* +  Plus Sign (pliusas) */
   (unsigned char *)",",     // "&comma;",   // =SGML // C_Comma, /* ,  Comma (kablelis) */
   (unsigned char *)"-",     // "&hyph;", // "&hyphen;", // SGML  // "&dash;", // SGML  // "&minus;", // SGML  // C_Minus,   /* -  Hyphen, Minus Sign (minusas) */
   (unsigned char *)".",     // "&per;",  // "&period;", // SGML  // C_Point,   /* .  Full Stop, Period, Point (tas/kas) */
   (unsigned char *)"/",     // "&fwsl;", // "&sol;", // SGML  // C_Slash,   /* /  Slash, Solidus (Istrizas bruksnys) */
   (unsigned char *)"0",     // "&d0;",      //   C_0,       /* 0 */
   (unsigned char *)"1",     // "&d1;",      //   C_1,       /* 1 */
   (unsigned char *)"2",     // "&d2;",      //   C_2,       /* 2 */
   (unsigned char *)"3",     // "&d3;",      //   C_3,       /* 3 */
   (unsigned char *)"4",     // "&d4;",      //   C_4,       /* 4 */
   (unsigned char *)"5",     // "&d5;",      //   C_5,       /* 5 */
   (unsigned char *)"6",     // "&d6;",      //   C_6,       /* 6 */
   (unsigned char *)"7",     // "&d7;",      //   C_7,       /* 7 */
   (unsigned char *)"8",     // "&d8;",      //   C_8,       /* 8 */
   (unsigned char *)"9",     // "&d9;",      //   C_9,       /* 9 */
   (unsigned char *)":",     // "&colon;",   // =SGML //   C_Colon,   /* :  Colon (dvitas/kis) */
   (unsigned char *)";",     // "&semi;",    // =SGML //   C_Semic,   /* ;  Semi-colon (kabliatas/kis) */
   (unsigned char *)"&lt;",  // =SGML        //   C_Less,    /* <  Less than Sign (maz/iau) */
   (unsigned char *)"=",     // "&eq;", // "&equals;",  //  SGML  // C_Eq,      /* =  Equals Sign (lygybe%s z/enklas) */
   (unsigned char *)"&gt;",  // =SGML        //   C_Great,   /* >  Greater than Sign (daugiau) */
   (unsigned char *)"?",     // "&ques;", // "&quest;",  // SGML  // C_Quest,   /* ?  Question Mark (klaustukas) */

   (unsigned char *)"@",     // "&at;", // "&commat;",   // SGML  // C_At,      /* @  Commercial At (Prekybinis zenklas "Pas") */
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
   (unsigned char *)"[",     // "&lsq;",  // "&lsqb;",   // SGML  // C_Lbrack,  /* [  Left Square Bracket (Kairysis lauztinis skliaustas) */
   (unsigned char *)"\\",    // "&bksl;", // "&bsol;",   // SGML  // C_Lslash,  /* \  Reverse Solidus, Reverse Slash (Atvirkscias istrizas bruksnys) */
   (unsigned char *)"]",     // "&rsq;",  // "&rsqb;",   // SGML  // C_Rbrack,  /* ]  Right Square Bracket (Desinysis lauztinis skliaustas) */
   (unsigned char *)"^",     // "&crt;",     //   C_Circ,    /* ^  Circumflex Accent (Cirkumfleksas) */
   (unsigned char *)"_",     // "&hbar;", // "&lowbar;", // SGML  // C_Underl,  /* _  Underline (Pabraukimas) */

   (unsigned char *)"`",     // "&grav;",    //   C_Grave,   /* `  Grave Accent (gravis) */
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
   (unsigned char *)"{",     // "&lcb;",  // "&lcub;",   // SGML //   C_Lcurl,   /* {  Left Curly Bracket (Kairysis riestinis skliaustas) */
   (unsigned char *)"|",     // "&bar;",  // "&verbar;", // SGML    //   C_Vertl,   /* |  Vertical Line (Vertikali Linija) */
   (unsigned char *)"}",     // "&rcb;",  // "&rcub;",   // SGML    //   C_Rcurl,   /* }  Right Curly Bracket (Desinysis riestinis skliaustas) */
   (unsigned char *)"~",     // "&til;",     //   C_Tilde,   /* ~  Tilde (Overline) (Tilde, Bruksnys virsuje) */

   (unsigned char *)NULL,    //   C_Del,

   (unsigned char *)NULL,    //    C_AE,
   (unsigned char *)NULL,    //    C_ae,
   (unsigned char *)"&OElig;", // HTML // C_OE,
   (unsigned char *)"&oelig;", // HTML // C_oe,

   (unsigned char *)NULL,    // SGML // C_IJ,
   (unsigned char *)NULL,    // SGML // C_ij,
   (unsigned char *)NULL,    //    C_ss,      /* sharp s    (german), C_beta - beta */

   (unsigned char *)NULL,    //   C_A_Cyr,
   (unsigned char *)NULL,    //   C_B_Cyr,
   (unsigned char *)NULL,    //   C_V_Cyr,
   (unsigned char *)NULL,    //   C_G_Cyr,
   (unsigned char *)NULL,    //   C_D_Cyr,
   (unsigned char *)NULL,    //   C_E_Cyr,
   (unsigned char *)NULL,    //   C_Zh_Cyr,
   (unsigned char *)NULL,    //   C_Z_Cyr,
   (unsigned char *)NULL,    //   C_I_Cyr,
   (unsigned char *)NULL,    //   C_J_Cyr,
   (unsigned char *)NULL,    //   C_K_Cyr,
   (unsigned char *)NULL,    //   C_L_Cyr,
   (unsigned char *)NULL,    //   C_M_Cyr,
   (unsigned char *)NULL,    //   C_N_Cyr,
   (unsigned char *)NULL,    //   C_O_Cyr,
   (unsigned char *)NULL,    //   C_P_Cyr,
   (unsigned char *)NULL,    //   C_R_Cyr,
   (unsigned char *)NULL,    //   C_S_Cyr,
   (unsigned char *)NULL,    //   C_T_Cyr,
   (unsigned char *)NULL,    //   C_U_Cyr,
   (unsigned char *)NULL,    //   C_F_Cyr,
   (unsigned char *)NULL,    //   C_H_Cyr,
   (unsigned char *)NULL,    //   C_C_Cyr,
   (unsigned char *)NULL,    //   C_Ch_Cyr,
   (unsigned char *)NULL,    //   C_Sh_Cyr,
   (unsigned char *)NULL,    //   C_Shch_Cyr,
   (unsigned char *)NULL,    //   C_Hard_Cyr,
   (unsigned char *)NULL,    //   C_Y_Cyr,
   (unsigned char *)NULL,    //   C_Soft_Cyr,
   (unsigned char *)NULL,    //   C_Ee_Cyr,
   (unsigned char *)NULL,    //   C_Ju_Cyr,
   (unsigned char *)NULL,    //   C_Ja_Cyr,

   (unsigned char *)NULL,    //   C_a_Cyr,
   (unsigned char *)NULL,    //   C_b_Cyr,
   (unsigned char *)NULL,    //   C_v_Cyr,
   (unsigned char *)NULL,    //   C_g_Cyr,
   (unsigned char *)NULL,    //   C_d_Cyr,
   (unsigned char *)NULL,    //   C_e_Cyr,
   (unsigned char *)NULL,    //   C_zh_Cyr,
   (unsigned char *)NULL,    //   C_z_Cyr,
   (unsigned char *)NULL,    //   C_i_Cyr,
   (unsigned char *)NULL,    //   C_j_Cyr,
   (unsigned char *)NULL,    //   C_k_Cyr,
   (unsigned char *)NULL,    //   C_l_Cyr,
   (unsigned char *)NULL,    //   C_m_Cyr,
   (unsigned char *)NULL,    //   C_n_Cyr,
   (unsigned char *)NULL,    //   C_o_Cyr,
   (unsigned char *)NULL,    //   C_p_Cyr,
   (unsigned char *)NULL,    //   C_r_Cyr,
   (unsigned char *)NULL,    //   C_s_Cyr,
   (unsigned char *)NULL,    //   C_t_Cyr,
   (unsigned char *)NULL,    //   C_u_Cyr,
   (unsigned char *)NULL,    //   C_f_Cyr,
   (unsigned char *)NULL,    //   C_h_Cyr,
   (unsigned char *)NULL,    //   C_c_Cyr,
   (unsigned char *)NULL,    //   C_ch_Cyr,
   (unsigned char *)NULL,    //   C_sh_Cyr,
   (unsigned char *)NULL,    //   C_shch_Cyr,
   (unsigned char *)NULL,    //   C_hard_Cyr,
   (unsigned char *)NULL,    //   C_y_Cyr,
   (unsigned char *)NULL,    //   C_soft_Cyr,
   (unsigned char *)NULL,    //   C_ee_Cyr,
   (unsigned char *)NULL,    //   C_ju_Cyr,
   (unsigned char *)NULL,    //   C_ja_Cyr,

                              //    /* Additional greek chars variations follow later */
   (unsigned char *)NULL,  // SGML // "&Alpha;",   // C_Alpha,
   (unsigned char *)NULL,  // SGML // "&Beta;",    // C_Beta,
   (unsigned char *)NULL,  // SGML // "&Gamma;",   // SGML  C_Gamma,
   (unsigned char *)NULL,  // SGML // "&Delta;",   // SGML  C_Delta,
   (unsigned char *)NULL,  // SGML // "&Epsi;",    // C_Epsilon,
   (unsigned char *)NULL,  // SGML // "&Zeta;",    // C_Zeta,
   (unsigned char *)NULL, // SGML // "&Eta;",     // C_Eta,
   (unsigned char *)NULL, // SGML // "&Theta;",   // SGML  C_Theta,
   (unsigned char *)NULL,  // SGML // "&Iota;",    // C_Jota,
   (unsigned char *)NULL,  // SGML // "&Kappa;",   // C_Kappa,
   (unsigned char *)NULL,  // SGML // "&Lambda;",  // SGML  C_Lambda,
   (unsigned char *)NULL,  // SGML // "&Mu;",      // C_My,
   (unsigned char *)NULL,  // SGML // "&Nu;",      // C_Ny,
   (unsigned char *)NULL,  // SGML // "&Xi;",      // SGML  C_Xi,
   (unsigned char *)NULL,  // SGML   C_Omikron,
   (unsigned char *)NULL,  // SGML // "&Pi;",      // SGML  C_Pi,
   (unsigned char *)NULL,  // SGML // "&Rho;",     // C_Rho,
   (unsigned char *)NULL,  // SGML // "&Sigma;",   // SGML  C_Sigma,
   (unsigned char *)NULL,  // SGML // "&Tau;",     // C_Tau,
   (unsigned char *)NULL,  // SGML // "&Upsi;",    // SGML  C_Ypsilon,
   (unsigned char *)NULL, // SGML // "&Phi;",     // SGML  C_Phi,
   (unsigned char *)NULL, // SGML // "&Chi;",     // C_Chi,
   (unsigned char *)NULL, // SGML // "&Psi;",     // SGML  C_Psi,
   (unsigned char *)NULL, // SGML // "&Omega;",   // SGML  C_Omega,

   (unsigned char *)NULL,  // SGML // "&alpha;",   // SGML C_alpha,
   (unsigned char *)NULL,  // SGML // "&beta;",    // SGML  C_beta,
   (unsigned char *)NULL,  // SGML // "&gamma;",   // SGML  C_gamma,
   (unsigned char *)NULL,  // SGML // "&delta;",   // SGML  C_delta,
   (unsigned char *)NULL,// SGML   C_epsilon,    // curly epsilon
   (unsigned char *)NULL,  // SGML // "&zeta;",    // SGML  C_zeta,
   (unsigned char *)NULL, // SGML // "&eta;",     // SGML  C_eta,
   (unsigned char *)NULL,// SGML  C_theta, // straight theta
   (unsigned char *)NULL,  // SGML // "&iota;",    // SGML  C_jota,
   (unsigned char *)NULL,  // SGML // "&kappa;",   // SGML  C_kappa,    // straight kappa
   (unsigned char *)NULL,  // SGML // "&lambda;",  // SGML  C_lambda,
   (unsigned char *)NULL,  // SGML // "&mu;",      // SGML  C_my,
   (unsigned char *)NULL,  // SGML // "&nu;",      // SGML  C_ny,
   (unsigned char *)NULL,  // SGML // "&xi;",      // SGML  C_xi,
   (unsigned char *)NULL,  // SGML   C_omikron,
   (unsigned char *)NULL,  // SGML // "&pi;",      // SGML  C_pi,       // straight pi
   (unsigned char *)NULL,  // SGML // "&rho;",     // SGML  C_rho,      // straight rho
   (unsigned char *)NULL,  // SGML // "&sigma;",   // SGML  C_sigma,    // inner sigma
   (unsigned char *)NULL,  // SGML // "&tau;",     // SGML  C_tau,
   (unsigned char *)NULL,  // SGML // "&upsi;",    // SGML  C_ypsilon,

   (unsigned char *)NULL, // SGML // "&phis;",    // SGML // "&phi;", // C_phi,      // straight phi
   (unsigned char *)NULL, // SGML // "&chi;",     // SGML    C_chi,
   (unsigned char *)NULL, // SGML // "&psi;",     // SGML  C_psi,
   (unsigned char *)NULL, // SGML // "&omega;",   // SGML  C_omega,

   (unsigned char *)NULL,    //   C_delt_Mn, /* delta_Minus    (skardi th) */

   (unsigned char *)NULL,  // "&acute;" // SGML  // C_Acute,   /* '  Acute    (aku/tas, apostrofas, des/inys kirtis) */
   (unsigned char *)NULL,  // SGML  // C_Dacut,   /* '' Double Acute */
   (unsigned char *)NULL,  // "&ogon;", // SGML  // C_Ogon,  /* ,  Ogonek    (nosine) */
   (unsigned char *)NULL,  // SGML  // C_Adot,  /* .  Dot Above    (. virsuje) */
   (unsigned char *)NULL,  // SGML  // C_Car,     /* v  Carron, Caron    (Pauksciukas) */
   (unsigned char *)NULL,  // "&macr;",   // SGML  // C_Macr,  /* _  Macron, Overline    (bruksnys virsuje) */
   (unsigned char *)NULL,  // =SGML // "&die;"  // SGML  // C_Diaer, /* .. Diaeresis    (Umlaut) */
   (unsigned char *)NULL,  // SGML  // C_Ring,  /* o  Ring    (Circle) Above    (o virsuje, degree) */
   (unsigned char *)NULL,  //     C_Tacom,   /* '  Turned Comma Above */
   (unsigned char *)NULL,  //     C_Bcomma,  /* ,  Comma Bellow */
   (unsigned char *)NULL,  // "&cedil;",   // SGML  // C_Cedil,   /* ,  Cedilla    (atbula nosine) */

   (unsigned char *)NULL,//     C_A_Ogon,  /* A, */
   (unsigned char *)NULL,//     C_a_Ogon,  /* a, */
   (unsigned char *)NULL,//     C_E_Ogon,  /* E, */
   (unsigned char *)NULL,//     C_e_Ogon,  /* e, */
   (unsigned char *)NULL,//     C_I_Ogon,  /* I, */
   (unsigned char *)NULL,//     C_i_Ogon,  /* i, */
   (unsigned char *)NULL,//     C_U_Ogon,  /* U, */
   (unsigned char *)NULL,//     C_u_Ogon,  /* u, */

   (unsigned char *)NULL, //     C_E_Adot,  /* E. */
   (unsigned char *)NULL, //     C_e_Adot,  /* e. */
   (unsigned char *)NULL, //     C_Z_Adot,  /* Z. */
   (unsigned char *)NULL, //     C_z_Adot,  /* z. */

   (unsigned char *)NULL, //   C_G_Cyr_Adot, /* G Cyr . */
   (unsigned char *)NULL,    //   C_g_Cyr_Adot, /* g Cyr . */

   (unsigned char *)NULL,//    C_C_Car,   /* Cv */
   (unsigned char *)NULL,//    C_c_Car,   /* cv */
   (unsigned char *)NULL,//    C_D_Car,   /* Dv */
   (unsigned char *)NULL,//    C_d_Car,   /* dv */
   (unsigned char *)NULL,//    C_E_Car,   /* Ev */
   (unsigned char *)NULL,//    C_e_Car,   /* ev */
   (unsigned char *)NULL,//    C_L_Car,   /* Lv */
   (unsigned char *)NULL,//    C_l_Car,   /* lv */
   (unsigned char *)NULL,//    C_N_Car,   /* Nv */
   (unsigned char *)NULL,//    C_n_Car,   /* nv */
   (unsigned char *)NULL,//    C_R_Car,   /* Rv */
   (unsigned char *)NULL,//    C_r_Car,   /* rv */
   (unsigned char *)"&Scaron;", // C_S_Car,   /* Sv */
   (unsigned char *)"&scaron;", // C_s_Car,   /* sv */
   (unsigned char *)NULL,//    C_T_Car,   /* Tv */
   (unsigned char *)NULL,//    C_t_Car,   /* tv */
   (unsigned char *)NULL,//    C_Z_Car,   /* Zv */
   (unsigned char *)NULL,//    C_z_Car,   /* zv */

   (unsigned char *)NULL,//     C_A_Macr,  /* A_ */
   (unsigned char *)NULL,//     C_a_Macr,  /* a_ */
   (unsigned char *)NULL,//     C_E_Macr,  /* E_ */
   (unsigned char *)NULL,//     C_e_Macr,  /* e_ */
   (unsigned char *)NULL,//     C_I_Macr,  /* I_ */
   (unsigned char *)NULL,//     C_i_Macr,  /* i_ */
   (unsigned char *)NULL,//     C_O_Macr,  /* O_ */
   (unsigned char *)NULL,//     C_o_Macr,  /* o_ */
   (unsigned char *)NULL,//     C_U_Macr,  /* U_ */
   (unsigned char *)NULL,//     C_u_Macr,  /* u_ */

   (unsigned char *)NULL,// =SGML      C_A_Diaer, /* A.. */
   (unsigned char *)NULL,// =SGML      C_a_Diaer, /* a.. */
   (unsigned char *)NULL,// =SGML      C_E_Diaer, /* E.. */
   (unsigned char *)NULL,// =SGML      C_e_Diaer, /* e.. */

   (unsigned char *)NULL,// =SGML      C_I_Diaer, /* I.. */
   (unsigned char *)NULL,// =SGML      C_i_Diaer, /* i.. */
   (unsigned char *)NULL,// =SGML      C_O_Diaer, /* O.. */
   (unsigned char *)NULL,// =SGML      C_o_Diaer, /* o.. */
   (unsigned char *)NULL,// =SGML      C_U_Diaer, /* U.. */
   (unsigned char *)NULL,// =SGML      C_u_Diaer, /* u.. */
   (unsigned char *)"&Yuml;",// =HTML  C_Y_Diaer, /* Y.. */
   (unsigned char *)NULL,// =SGML      C_y_Diaer, /* y.. */


   (unsigned char *)NULL,    //      C_E_Cyr_Diaer, /* E.. */
   (unsigned char *)NULL,    //      C_e_Cyr_Diaer, /* e.. */

   (unsigned char *)NULL, //       C_A_Ring,  /* Ao */
   (unsigned char *)NULL, //       C_a_Ring,  /* ao */
   (unsigned char *)NULL, //       C_U_Ring,  /* Uo */
   (unsigned char *)NULL, //       C_u_Ring,  /* uo */

   (unsigned char *)NULL,    //      C_G_Tacom, /* G' */
   (unsigned char *)NULL,    //      C_g_Tacom, /* g' */

   (unsigned char *)NULL,  // kp // C_G_Bcomma,/* G, */
   (unsigned char *)NULL,  // kp // C_g_Bcomma,/* g, */
   (unsigned char *)NULL,  // kp // C_K_Bcomma,/* K, */
   (unsigned char *)NULL,  // kp // C_k_Bcomma,/* k, */
   (unsigned char *)NULL,  // kp // C_L_Bcomma,/* L, */
   (unsigned char *)NULL,  // kp // C_l_Bcomma,/* l, */
   (unsigned char *)NULL,  // kp // C_N_Bcomma,/* N, */
   (unsigned char *)NULL,  // kp // C_n_Bcomma,/* n, */
   (unsigned char *)NULL,  // kp // C_R_Bcomma,/* R, */
   (unsigned char *)NULL,  // kp // C_r_Bcomma,/* r, */

   (unsigned char *)NULL,// =SGML   C_C_Cedil, /* C, */
   (unsigned char *)NULL,// =SGML   C_c_Cedil, /* c, */
   (unsigned char *)NULL,// =SGML   C_S_Cedil, /* S, */
   (unsigned char *)NULL,// =SGML   C_s_Cedil, /* s, */
   (unsigned char *)NULL,// =SGML   C_T_Cedil, /* T, */
   (unsigned char *)NULL,// =SGML   C_t_Cedil, /* t, */

   (unsigned char *)NULL,// =SGML    C_A_Grave, /* A` */
   (unsigned char *)NULL,// =SGML    C_a_Grave, /* a` */
   (unsigned char *)NULL,// =SGML    C_E_Grave, /* E` */
   (unsigned char *)NULL,// =SGML    C_e_Grave, /* e` */
   (unsigned char *)NULL,// =SGML    C_I_Grave, /* I` */
   (unsigned char *)NULL,// =SGML    C_i_Grave, /* i` */
   (unsigned char *)NULL,// =SGML    C_O_Grave, /* O` */
   (unsigned char *)NULL,// =SGML    C_o_Grave, /* o` */
   (unsigned char *)NULL,// =SGML    C_U_Grave, /* U` */
   (unsigned char *)NULL,// =SGML    C_u_Grave, /* u` */

   (unsigned char *)NULL,// =SGML    C_A_Acute, /* A' */
   (unsigned char *)NULL,// =SGML    C_a_Acute, /* a' */
   (unsigned char *)NULL,// =SGML    C_C_Acute, /* C' */
   (unsigned char *)NULL,// =SGML    C_c_Acute, /* c' */
   (unsigned char *)NULL,// =SGML    C_E_Acute, /* E' */
   (unsigned char *)NULL,// =SGML    C_e_Acute, /* e' */
   (unsigned char *)NULL,// =SGML    C_I_Acute, /* I' */
   (unsigned char *)NULL,// =SGML    C_i_Acute, /* i' */
   (unsigned char *)NULL,// =SGML    C_L_Acute, /* L' */
   (unsigned char *)NULL,// =SGML    C_l_Acute, /* l' */
   (unsigned char *)NULL,// =SGML    C_N_Acute, /* N' */
   (unsigned char *)NULL,// =SGML    C_n_Acute, /* n' */
   (unsigned char *)NULL,// =SGML    C_O_Acute, /* O' */
   (unsigned char *)NULL,// =SGML    C_o_Acute, /* o' */
   (unsigned char *)NULL,// =SGML    C_R_Acute, /* R' */
   (unsigned char *)NULL,// =SGML    C_r_Acute, /* r' */
   (unsigned char *)NULL,// =SGML    C_S_Acute, /* S' */
   (unsigned char *)NULL,// =SGML    C_s_Acute, /* s' */
   (unsigned char *)NULL,// =SGML    C_U_Acute, /* U' */
   (unsigned char *)NULL,// =SGML    C_u_Acute, /* u' */
   (unsigned char *)NULL,// =SGML    C_Y_Acute, /* Y' */
   (unsigned char *)NULL,// =SGML    C_y_Acute, /* y' */
   (unsigned char *)NULL,// =SGML    C_Z_Acute, /* Z' */
   (unsigned char *)NULL,// =SGML    C_z_Acute, /* z' */

   (unsigned char *)NULL,    //      C_K_Cyr_Acute, /* K Cyr ' */
   (unsigned char *)NULL,    //      C_k_Cyr_Acute, /* k Cyr ' */

   (unsigned char *)NULL,  // !!!??? SGML // C_O_Dacut, /* O'' */
   (unsigned char *)NULL,  // !!!??? SGML // C_o_Dacut, /* o'' */
   (unsigned char *)NULL,  // !!!??? SGML // C_U_Dacut, /* U'' */
   (unsigned char *)NULL,  // !!!??? SGML // C_u_Dacut, /* u'' */

   (unsigned char *)NULL,// =SGML    C_A_Tilde, /* A~ */
   (unsigned char *)NULL,// =SGML    C_a_Tilde, /* a~ */
   (unsigned char *)NULL,// =SGML    C_N_Tilde, /* N~ */
   (unsigned char *)NULL,// =SGML    C_n_Tilde, /* n~ */
   (unsigned char *)NULL,// =SGML    C_O_Tilde, /* O~ */
   (unsigned char *)NULL,// =SGML    C_o_Tilde, /* o~ */

   (unsigned char *)NULL,  // SGML  // C_L_Slash, /* L/ */
   (unsigned char *)NULL,  // SGML  // C_l_Slash, /* l/ */
   (unsigned char *)NULL,   // =SGML // "&0slash;" !!!??? C_O_Slash, /* O/ */
   (unsigned char *)NULL,  // =SGML // C_o_Slash, /* o/ */

   (unsigned char *)NULL,// =SGML     C_A_Circ,  /* A^ */
   (unsigned char *)NULL,// =SGML     C_a_Circ,  /* a^ */
   (unsigned char *)NULL,// =SGML     C_E_Circ,  /* E^ */
   (unsigned char *)NULL,// =SGML     C_e_Circ,  /* e^ */
   (unsigned char *)NULL,// =SGML     C_I_Circ,  /* I^ */
   (unsigned char *)NULL,// =SGML     C_i_Circ,  /* i^ */
   (unsigned char *)NULL,// =SGML     C_O_Circ,  /* O^ */
   (unsigned char *)NULL,// =SGML     C_o_Circ,  /* o^ */
   (unsigned char *)NULL,// =SGML     C_U_Circ,  /* U^ */
   (unsigned char *)NULL,// =SGML     C_u_Circ,  /* u^ */

   (unsigned char *)NULL,  // SGML  // C_D_Minus, /* D- Island. */
   (unsigned char *)NULL,  // SGML  // C_d_Minus, /* d- */
   (unsigned char *)NULL,  // SGML  // C_H_Minus, /* H- */
   (unsigned char *)NULL,  // SGML  // C_h_Minus, /* h- */
   (unsigned char *)NULL,   // SGML  // C_P_Minus, /* P- */
   (unsigned char *)NULL,   // SGML  // C_p_Minus, /* p- */

   (unsigned char *)"&nbsp;", // SGML  // C_NBSP,   /* No break space */

   (unsigned char *)NULL, // "&curren;", // SGML  C_Rouble,  /* rublis, " Cyr */
   (unsigned char *)NULL, // "&pound;",  // SGML  C_Pound,   /* svaras, L/ */
   (unsigned char *)NULL, // =SGML  C_Yenna,   /* jena, Y- */
   (unsigned char *)NULL, // "&cent;",   // SGML  C_cent,    /* c/ */

   (unsigned char *)NULL, // "&sect;",    // SGML  // C_Para,    /* paragrafas, # engl. */
   (unsigned char *)NULL, // "&para;",    // SGML  // C_Pren,    /* paragraph end sign    (pastraipos pabaiga, C_pi - pi) */
   (unsigned char *)NULL,   // =SGML  C_Multipl, /* x */
   (unsigned char *)NULL,  // =SGML  C_Divide,  /* -:- */
   (unsigned char *)NULL, // "&plusmn;",  // SGML  // C_PlMin,   /* -+- */
   (unsigned char *)NULL,  // "&sup1;",    // SGML  // C_1up,     /* 1 virsuj */
   (unsigned char *)NULL,  // "&sup2;",    // SGML  // C_2up,     /* 2 virsuj, kvadratu */
   (unsigned char *)NULL,  // "&sup3;",    // SGML  // C_3up,     /* 3 virsuj, kubu */
   (unsigned char *)NULL, // "&ordf;",    // SGML  // C_a_up,    /* a virsuj */
   (unsigned char *)NULL, // "&ordm;",    // SGML  // C_o_up,    /* o virsuj */
   (unsigned char *)NULL,  // "&frac12;",  // SGML  // "&half;",   // SGML  C_Half,    /* 1/2 */
   (unsigned char *)NULL,  // "&frac14;",  // SGML  // C_Quart,   /* 1/4 */
   (unsigned char *)NULL, // "&frac34;",  // SGML  // C_34,      /* 3/4 */
   (unsigned char *)NULL, // "&laquo;",   // SGML  // C_Ldopang, /* << */
   (unsigned char *)NULL, // "&raquo;",   // SGML  // C_Rdopang, /* >> */
   (unsigned char *)NULL, // SGML  // C_Lang,  /* < */
   (unsigned char *)NULL, // SGML  // C_Rang,    /* > */
   (unsigned char *)NULL,// "&brvbar;",  // SGML  // C_Dvertl,  /* | Koi-7-0 */
   (unsigned char *)NULL, // =SGML  // C_Rminbr,  /* ^ Koi-7-0    ( -: ) */
   (unsigned char *)NULL,    //      C_Lminbr,  /* :- */
   (unsigned char *)NULL, // "&middot;",  // SGML  C_Lpoint,  /* mazas taskas vidury */
   (unsigned char *)NULL,          // C_Bpoint,  /* bullet, didelis taskas vidury */
   (unsigned char *)NULL,  // SGML  // C_LBquote
   (unsigned char *)NULL,   // SGML  // "&rdquor;", // SGML  // C_LAquote
   (unsigned char *)NULL,   // SGML  // C_Rquote
   (unsigned char *)NULL,  // SGML  // C_LBapost
   (unsigned char *)NULL,   // SGML  // "&rsquor;", // SGML  // C_LAapost
   (unsigned char *)NULL,   // SGML  // C_Rapost

   (unsigned char *)NULL,     // "&iquest;", // SGML  // C_Qst_Ov,  /* apverstas ? */
   (unsigned char *)NULL,     // "&iexcl;",  // SGML  // C_Ex_Ov,   /* apverstas ! */
   (unsigned char *)"&hellip;",  // SGML  // "&mldr;",   // SGML  // C_Dots,  /* ... daugtaskis */
   (unsigned char *)NULL,  // SGML  // C_Prom,    /* %o promiles */
   (unsigned char *)NULL,   // SGML  // C_TM,      /* TM, Trade Mark */
   (unsigned char *)NULL,     // "&copy;", // SGML  // C_CO,      /*    (C) Copyright */
   (unsigned char *)NULL,     // "&reg;",  // SGML  // C_RO,      /*    (R) */

                              //    /* Additional greek chars, look SGML DTD */
   (unsigned char *)NULL,   // SGML // "&egr;", // SGML // "&epsi;", // SGML // C_epsilon_var, // straight epsilon
   (unsigned char *)NULL,  // SGML // "&thgr;" // SGML // "&theta;", // C_theta_var,  // curly theta
   (unsigned char *)NULL,  // SGML  // C_DiGamma,
   (unsigned char *)NULL,  // SGML  // C_digamma,
   (unsigned char *)NULL,  // SGML  // C_kappa_var,  // curly kappa
   (unsigned char *)NULL, // SGML  // C_DiLambda,
   (unsigned char *)NULL, // SGML  // C_dilambda,
   (unsigned char *)NULL,     // SGML  // C_pi_var,     // curly pi, like C_omega
   (unsigned char *)NULL,    // SGML  // C_rho_var,    // curly rho
   (unsigned char *)NULL,  // SGML  // C_Sigma_var,  // like "S"
   (unsigned char *)NULL,  // SGML // "&sfgr;", // SGML // C_sigma_var,  // final sigma, like "s"
   (unsigned char *)NULL,    // SGML  // C_phi_var,    // curly phi

             /* additional accents, all of them have no width (over the next letter) */
   (unsigned char *)NULL,   // SGML  // C_GraveAcc,    /* `  Grave Accent (C_Grave, kairysis kirtis), over the next letter */
   (unsigned char *)"&circ;", // HTML  // C_CircAcc,     /* ^  Circumflex Accent (C_Circ), over the next letter */
   (unsigned char *)NULL,   // SGML  // C_TildeAcc,    /* ~  Tilde (C_Tilde), over the next letter */
   (unsigned char *)NULL,   // SGML  // C_BreveAcc,    /* u  (lankelis virsuje) */
   (unsigned char *)NULL,  //     C_SlashAcc,    /* /  Slash, Solidus (Istrizas bruksnys per raide) */
   (unsigned char *)NULL,     //     C_BdotAcc,     /* .  Dot bellow */
   (unsigned char *)NULL,     //     C_UnderlAcc,   /* _  Underline (Pabraukimas) */

   (unsigned char *)NULL,   // SGML  // C_prim,    /* strichas prie raides (C_Acute, C_Apost) */
   (unsigned char *)NULL,   // SGML  // C_dprim,   /* du strichai (C_Dacut) */

   (unsigned char *)NULL,  // SGML  // C_Each,     /* V - "kiekvienam- apversta A raide */
   (unsigned char *)NULL,   // SGML  // C_Exists,   /* E - "egzistuoja- apversta E raide */

   (unsigned char *)NULL,   // SGML  // C_Aleph, /* N - alefas */
   (unsigned char *)NULL,   // SGML  // C_Im,      /* C_I_Got */
   (unsigned char *)NULL,    // SGML  // C_Re,      /* C_R_Got */
   (unsigned char *)NULL,  // SGML  // C_wp,      /* C_p_Got */


   (unsigned char *)NULL,   // SGML  // C_le,       /* <= - maziau arba lygu */
   (unsigned char *)NULL,   // SGML  // C_ge,       /* >= - daugiau arba lygu */
   (unsigned char *)NULL,   // SGML  // C_ne,       /* =/= - nelygu */
   (unsigned char *)NULL,   // SGML  // C_ll,       /* << */
   (unsigned char *)NULL,   // SGML  // C_gg,       /* >> */
   (unsigned char *)NULL,  // SGML  // C_sim,      /* ~ - panasu */
   (unsigned char *)NULL, // SGML  // C_simeq,    /* ~- - panasu arba sutampa */
   (unsigned char *)NULL,   // SGML  // C_approx,   /* ~~ - apytiksliai lygu */
   (unsigned char *)NULL, // SGML  // C_cong,     /* ~= - kongruentu */
   (unsigned char *)NULL,   // SGML  // C_equiv, /* = - triguba lygybe - ekvivalentumo zenklas */

   (unsigned char *)NULL,   // SGML  //     C_sqrt,    /* square root */
   (unsigned char *)NULL,  // SGML  // C_int,   /* integralas */
   (unsigned char *)NULL,  // SGML  // C_oint,  /* kreivinis integralas */
   (unsigned char *)NULL,  // SGML  //     C_Sum,     /* sum sign (C_Sigma) */
   (unsigned char *)NULL, // SGML  //     C_Prod,    /* C_Pi */
   (unsigned char *)NULL,  // SGML  // C_O_times, /* OX - O perbraukta istrizai */
   (unsigned char *)NULL,   // SGML  // C_O_plus,  /* O+ - O perbraukta pliusu */

   (unsigned char *)NULL,   // SGML  // C_infty,   /* infinity - begalybe */
   (unsigned char *)NULL,    // SGML  // "&vprop;",  // SGML  // C_propto,  /* (C_alpha) */
   (unsigned char *)NULL,    // SGML  // C_part,    /* partial (C_delta) */
   (unsigned char *)NULL,   // SGML  // C_empty,   /* O/ (C_O_Slash) */
   (unsigned char *)NULL,    // SGML  // C_triangle,/* C_Delta - trikampis */
   (unsigned char *)NULL,   // SGML  // C_nabla,   /* V - C_Delta apversta */

   (unsigned char *)NULL, // SGML  // "&bottom;",  // SGML  // C_perp,  /* T apversta - statmena |- |_*/
   (unsigned char *)NULL,  // SGML  // C_angle,   /* < - kampas */


   (unsigned char *)NULL,     //     C_langle,  /* < - skliaustas */
   (unsigned char *)NULL,     //     C_rangle,  /* > - skliaustas */

   (unsigned char *)NULL,  // SGML  // C_cap,     /* U apversta - pjuvis */
   (unsigned char *)NULL,  // SGML  // C_cup,     /* U - junginys */

   (unsigned char *)NULL,     //     C_vee,     /* V */
   (unsigned char *)NULL,     //     C_wedge,   /* C_Lambda */

   (unsigned char *)NULL,  // SGML  //  C_supset,  /* D - virsaibis */
   (unsigned char *)NULL, // SGML  //  C_supseteq,/* D= - virsaibis arba sutampa */
   (unsigned char *)NULL,  // SGML  //  C_subset,  /* C - poaibis */
   (unsigned char *)NULL, // SGML  //  C_subseteq,/* C= - poaibis arba sutampa */
   (unsigned char *)NULL, // SGML  //  C_nsubset, /* C/ - nepoaibis */

   (unsigned char *)NULL, // SGML  //  C_in,      /* C_epsilon_var - priklauso */
   (unsigned char *)NULL,   // SGML  //  C_notin,   /* C_epsilon_var_Slash - nepriklauso */
   (unsigned char *)NULL,  // SGML  // "&bepsi;",  // SGML  //  C_ni,      /* C_epsilon_var apsuktas - apima */

   (unsigned char *)NULL, // SGML  // C_leftarr,       /* <-- */
   (unsigned char *)NULL, // SGML  // C_rightarr,      /* --> */
   (unsigned char *)NULL, // SGML  //  C_leftrightarr,  /* <--> */
   (unsigned char *)NULL, // SGML  // C_uparr,         /* ^| */
   (unsigned char *)NULL, // SGML  // C_downarr,       /* |v */
   (unsigned char *)NULL, // SGML  //  C_updownarr,     /* ^|v */

   (unsigned char *)NULL, // SGML  // C_Leftarr,   /* <== */
   (unsigned char *)NULL, // SGML  //  C_Rightarr,      /* ==> */
   (unsigned char *)NULL, // SGML  // "&iff;",  // SGML  // C_Leftrightarr,  /* <==> */
   (unsigned char *)NULL, // SGML  //  C_Uparr,         /* ^|| */
   (unsigned char *)NULL, // SGML  //  C_Downarr,       /* ||v */
   (unsigned char *)NULL, // SGML  //  C_Updownarr,     /* ^||v */

   (unsigned char *)NULL,  // SGML  //  C_mid,  /* | */
   (unsigned char *)NULL,  // SGML  // "&Verbar;", // SGML  // C_paral, /* || */

   (unsigned char *)NULL, // SGML  //  C_diamond,     /* rombas */

   (unsigned char *)NULL,   // SGML  // C_Club,        /* giles */
   (unsigned char *)NULL,   // SGML  // C_Diamond,     /* bugnai */
   (unsigned char *)NULL,  // SGML  // C_Heart,       /* cirvai sirdys */
   (unsigned char *)NULL,  // SGML  // C_Spade,       /* pikai lapai */

   (unsigned char *)NULL,  // =SGML // soft hyphen - ilgas bruksnys, kodas 173 ISO Latin 1 lenteleje - ???!!! C_hyph,    /* hided hyphenation sign ("\-" for TEX) */
   (unsigned char *)NULL,  // kp // C_break,   /* line break character */

   (unsigned char *)NULL,     // C_a_Car,   /* av - laikinai, po to ismesti !!! */

   (unsigned char *)NULL,     // C_euro,    /* C= euro piniginis vienetas !!! kelti prie pinigu */

   (unsigned char *)NULL,  //  =SGML   // C_deg,   /* degree - panasiai, kaip C_Ring, tik desineje */
   (unsigned char *)NULL,  //  "&micro;", // SGML  // C_micro, /* mikro - panasiai, kaip C_my */
   (unsigned char *)NULL,  //  SGML    // C_Ohm,   /* Ohm sign - panasiai, kaip C_Omega */
   (unsigned char *)NULL,   //  SGML    // C_Angst,   /* Angstroem - C_A_Ring */

   (unsigned char *)NULL,        // C_Horl,  /* horizontal line --- */ nukelta i C_h_b

   (unsigned char *)NULL,  // SGML  // C_Dag,   /* Dagger +| (kryzius) */
   (unsigned char *)NULL,  // SGML  // C_Ddag,  /* Double dagger +|+ (Kestucio kryzius) */

   (unsigned char *)NULL,   // SGML  // C_ff,     /* ff ligature */
   (unsigned char *)NULL,   // SGML  // C_fi,     /* fi ligature */
   (unsigned char *)NULL,   // SGML  // C_fj,     /* fj ligature */
   (unsigned char *)NULL,  // SGML  // C_ffi,    /* ff ligature */
   (unsigned char *)NULL,  // SGML  // C_ffl,    /* ff ligature */
   (unsigned char *)NULL,   // SGML  // C_fl,     /* ff ligature */

   (unsigned char *)NULL,     // SGML  // C_and,   /* ^ logical and */
   (unsigned char *)NULL,     // SGML  // C_or,    /* V logical or */

   (unsigned char *)"&fnof;", // HTML  // C_fun,    /* f function of */

   (unsigned char *)NULL,  // SGML  // C_MinPl,  /* -+ minus plus */

   (unsigned char *)"&ndash;",   // HTML  // C_EnDash, /* -- - vidutinio ilgio bruksnys */
   (unsigned char *)"&mdash;",   // HTML  // C_EmDash, /* --- - ilgas bruksnys */

   (unsigned char *)NULL,        // C_Cdots,  /* ... - daugtaskis per viduri */
   (unsigned char *)NULL,        // C_WideTilde, /* ~ didele tilde */

   (unsigned char *)"&thinsp;",  // HTML // C_QemSpc, /* 1/4 m space */
   (unsigned char *)"&ensp;",    // HTML // C_EnSpc,  /* n space */
   (unsigned char *)"&emsp;",    // HTML // C_EmSpc,  /* m space */
   (unsigned char *)NULL,        // C_2emSpc, /* 2 m space */

   (unsigned char *)NULL,        // C_NewPar, /* paragraph end control character */

   (unsigned char *)NULL,  // =SGML  C_Y_Grave, Y`
   (unsigned char *)NULL,  // =SGML  C_y_Grave, y`
   (unsigned char *)NULL,  // =SGML  C_E_Tilde, E~
   (unsigned char *)NULL,  // =SGML  C_e_Tilde, e~
   (unsigned char *)NULL,  // =SGML  C_I_Tilde, I~
   (unsigned char *)NULL,  // =SGML  C_i_Tilde, i~
   (unsigned char *)NULL,  // =SGML  C_U_Tilde, U~
   (unsigned char *)NULL,  // =SGML  C_u_Tilde, u~
   (unsigned char *)NULL,  // =SGML  C_Y_Tilde, Y~
   (unsigned char *)NULL,  // =SGML  C_y_Tilde, y~
   (unsigned char *)NULL,  // =SGML  C_L_Tilde, L~
   (unsigned char *)NULL,  // =SGML  C_l_Tilde, l~
   (unsigned char *)NULL,  // =SGML  C_M_Tilde, M~
   (unsigned char *)NULL,  // =SGML  C_m_Tilde, m~
   (unsigned char *)NULL,  // =SGML  C_R_Tilde, R~
   (unsigned char *)NULL,  // =SGML  C_r_Tilde, r~
   (unsigned char *)NULL,     // kp // C_A_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_a_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_E_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_e_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_E_Adot_Acute,
   (unsigned char *)NULL,     // kp // C_e_Adot_Acute,
   (unsigned char *)NULL,     // kp // C_I_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_i_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_U_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_u_Ogon_Acute,
   (unsigned char *)NULL,     // kp // C_U_Macr_Acute,
   (unsigned char *)NULL,     // kp // C_u_Macr_Acute,
   (unsigned char *)NULL,     // kp // C_A_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_a_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_E_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_e_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_E_Adot_Grave,
   (unsigned char *)NULL,     // kp // C_e_Adot_Grave,
   (unsigned char *)NULL,     // kp // C_I_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_i_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_U_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_u_Ogon_Grave,
   (unsigned char *)NULL,     // kp // C_U_Macr_Grave,
   (unsigned char *)NULL,     // kp // C_u_Macr_Grave,
   (unsigned char *)NULL,     // kp // C_A_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_a_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_E_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_e_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_E_Adot_Tilde,
   (unsigned char *)NULL,     // kp // C_e_Adot_Tilde,
   (unsigned char *)NULL,     // kp // C_I_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_i_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_U_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_u_Ogon_Tilde,
   (unsigned char *)NULL,     // kp // C_U_Macr_Tilde,
   (unsigned char *)NULL,     // kp // C_u_Macr_Tilde,

// phonetic characters; vowels:
   (unsigned char *)NULL,          // kp // C_ph_a,        // low back unrounded; a, open a; italic C_a
   (unsigned char *)NULL,      // kp // C_ph_a_inv,    // low back rounded; oa; inverted italic C_a

   (unsigned char *)NULL,       // kp // C_ph_a_sh,     // low-mid back unrounded; short a; inverted C_v
   (unsigned char *)NULL,       // kp // C_ph_o_sh,     // low-mid back rounded; short o, open o; inverted C_c
// (unsigned char *)NULL,          // kp // C_ph_o,        // mid back rounded?; o, closed o; C_o
// (unsigned char *)NULL,     // kp // C_ph_o_soft,   // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
// (unsigned char *)NULL,  // kp // C_ph_o_soft_cl,// high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   (unsigned char *)NULL,       // kp // C_ph_u_sh,     // semi-high back rounded; short u, short open u; C_ypsilon
   (unsigned char *)NULL,       // kp // C_ph_w_sh,     // semi-high back rounded; short u, short open u, obsolete; C_omega
// (unsigned char *)NULL,        // kp // C_ph_u,        // semi-high central rounded?; u, closed u; C_u
// (unsigned char *)NULL,     // kp // C_ph_u_soft,   // high central rounded; soft u, iu, german C_u_Diaer; C_y,

   (unsigned char *)NULL,       // kp // C_ph_e_sh,     // low-mid front unrounded; short e, open e; C_epsilon
   (unsigned char *)NULL,         // kp // C_ph_ae,       // low front unrounded?; e, open e; C_ae
// (unsigned char *)NULL,       // kp // C_ph_e_cl,     // high central unrounded?; closed e, german e; C_e
   (unsigned char *)NULL,   // kp // C_ph_e_sh_inv, // low-mid central unrounded; hard e; inverted C_epsilon
   (unsigned char *)NULL,      // kp // C_ph_e_inv,    // mid central unrounded; reduced e; inverted C_e

   (unsigned char *)NULL,       // kp // C_ph_i_sh,     // semi-high front unrounded; short i, short open i; C_i without dot
// (unsigned char *)NULL,          // kp // C_ph_i,        // high front unrounded?; i, closed i; C_i

// phonetic characters; consonants:
   (unsigned char *)NULL,         // kp // C_ph_sh,       // sh; C_f, C_int
   (unsigned char *)NULL,         // kp // C_ph_zh,       // zh; C_3
   (unsigned char *)NULL,        // kp // C_ph_tsh,      // tsh; C_t C_f, C_t C_int
   (unsigned char *)NULL,        // kp // C_ph_dzh,      // dzh; C_d C_3
   (unsigned char *)NULL,       // kp // C_ph_th_b,     // breath th; C_theta
   (unsigned char *)NULL,       // kp // C_ph_th_v,     // voiced th; C_delt_Mn, (C_delta_Minus)
   (unsigned char *)NULL,         // kp // C_ph_ng,       // nasal g; C_eta
// (unsigned char *)NULL,         // kp // C_ph_ch,       // german ch; C_c_Cedil
   (unsigned char *)NULL,          // kp // C_ph_g,        // g; italic C_g

// additional phonetic characters:
   (unsigned char *)NULL,         // kp // C_ph_oe,       // high back rounded?; soft o, open soft o, io, german C_o_Diaer; C_oe,
   (unsigned char *)NULL,    // kp // C_ph_o_slash,  // high back rounded?; soft o, closed soft o, io, german C_o_Diaer; C_o_Slash

   (unsigned char *)NULL,        // kp // C_ph_a_l,      // low back unrounded long; a long, open a long; a:, italic C_a C_Colon
   (unsigned char *)NULL,    // kp // C_ph_e_inv_l,  // mid central unrounded long; reduced e long; e:, inverted C_e C_Colon
   (unsigned char *)NULL,        // kp // C_ph_i_l,      // high front unrounded long?; i long, closed i long; i:, C_i C_Colon
   (unsigned char *)NULL,        // kp // C_ph_o_l,      // low-mid back rounded long; o long, open o long; o:, inverted C_c C_Colon
   (unsigned char *)NULL,        // kp // C_ph_u_l,      // ; u long; C_u C_Colon

   (unsigned char *)NULL,        // kp // C_ph_a_n,      // low back unrounded nasal; a nasal, open a nasal; a~, italic C_a C_TildeAcc
   (unsigned char *)NULL,    // kp // C_ph_a_str_n,  // ; a straight nasal; a~, C_a_Tilde
   (unsigned char *)NULL,        // kp // C_ph_e_n,      // low-mid front unrounded nasal; short e nasal, open e nasal; e~, C_epsilon C_TildeAcc
   (unsigned char *)NULL,       // kp // C_ph_oe_n,     // ; oe nasal; oe~, C_oe C_TildeAcc
   (unsigned char *)NULL,        // kp // C_ph_o_sh_n,   // low-mid back rounded nasal; open o nasal; o~, inverted C_c + C_TildeAcc

   (unsigned char *)NULL,         // kp // C_ph_ch,       // german ch; C_c_Cedil

// diphtongs
   (unsigned char *)NULL,       // kp // C_ph_ai_diph,  //  C_a C_LigaLow C_i
   (unsigned char *)NULL,       // kp // C_ph_ae_diph,  //  C_a C_LigaLow C_e
   (unsigned char *)NULL,       // kp // C_ph_ao_diph,  //  C_a C_LigaLow C_o
   (unsigned char *)NULL,       // kp // C_ph_au_diph,  //  C_a C_LigaLow C_u
   (unsigned char *)NULL,       // kp // C_ph_ei_diph,  //  C_e C_LigaLow C_i
   (unsigned char *)NULL,       // kp // C_ph_eu_diph,  //  C_e C_LigaLow C_u
   (unsigned char *)NULL,       // kp // C_ph_ie_diph,  //  C_i C_LigaLow C_e
   (unsigned char *)NULL,       // kp // C_ph_oe_diph,  //  C_ph_o_sh C_LigaLow C_ph_o_slash
   (unsigned char *)NULL,       // kp // C_ph_oy_diph,  //  C_ph_o_sh C_LigaLow C_y
   (unsigned char *)NULL,       // kp // C_ph_uo_diph,  //  C_u C_LigaLow C_o

// breved phonetics
   (unsigned char *)NULL,     // kp // C_ph_i_Brev,   // ; j; C_i_Brev
   (unsigned char *)NULL,     // kp // C_ph_o_Brev,   //  C_o_Brev
   (unsigned char *)NULL,     // kp // C_ph_u_Brev,   //  C_u_Brev

// liga accents (for diphtongs)
   (unsigned char *)NULL,              // C_LigaUp,      // lankelis virs dvieju raidziu
   (unsigned char *)NULL,              // C_LigaLow,     // lankelis po dviem raidem

   (unsigned char *)NULL,       // C_MidRing,     // mazas apskritimas viduryje (tusciaviduris bulletas - kaip C_Bpoint)

   (unsigned char *)NULL,        // kp // C_ph_acc,       // C_Apost
   (unsigned char *)NULL,    // kp // C_ph_acc_low,   // C_Comma

   (unsigned char *)NULL,        // SGML // "&squ;" // SGML // C_square

   (unsigned char *)NULL,          // C_male,         // vyr. lytis, male sex, mars, o^
   (unsigned char *)NULL,        // C_female,       // mot. lytis, female sex, venus, o+

   (unsigned char *)NULL,          // SGML // C_O_ring,      // Oo - mazas apskritimas O viduje
   (unsigned char *)NULL,          // SGML // C_O_dot,       // O. - taskas O viduje

   (unsigned char *)NULL,           // SGML // C_BigRing,     // didelis apskritimas, C_O

   (unsigned char *)NULL,              //   C_longleftarr,       /* <---- */
   (unsigned char *)NULL,              //   C_longrightarr,      /* ----> */

   (unsigned char *)NULL,              //   C_smile

   (unsigned char *)NULL,          // SGML // C_box

// DOS frames
   (unsigned char *)NULL,        // SGML   C_v_b,       // vert; ne DOS-e - C_Vertl
   (unsigned char *)NULL,        // SGML   C_h_b,       // hor; ne DOS-e - C_Horl
   (unsigned char *)NULL,              //   C_vh_b,      // vert hor
   (unsigned char *)NULL,              //   C_vl_b,      // vert left
   (unsigned char *)NULL,              //   C_vr_b,      // vert right
   (unsigned char *)NULL,              //   C_hu_b,      // hor up
   (unsigned char *)NULL,              //   C_hd_b,      // hor down
   (unsigned char *)NULL,        // SGML   C_ul_b,      // up left
   (unsigned char *)NULL,        // SGML   C_dl_b,      // down left
   (unsigned char *)NULL,        // SGML   C_ur_b,      // up right
   (unsigned char *)NULL,        // SGML   C_dr_b,      // down right

   (unsigned char *)NULL,              //   C_2v_b,      // double vert; C_paral
   (unsigned char *)NULL,              //   C_2h_b,      // double hor
   (unsigned char *)NULL,              //   C_2v2h_b,    // double vert double hor
   (unsigned char *)NULL,              //   C_2v2l_b,    // double vert double left
   (unsigned char *)NULL,              //   C_2v2r_b,    // double vert double right
   (unsigned char *)NULL,              //   C_2h2u_b,    // double hor double up
   (unsigned char *)NULL,              //   C_2h2d_b,    // double hor double down
   (unsigned char *)NULL,              //   C_2u2l_b,    // double up double left
   (unsigned char *)NULL,              //   C_2d2l_b,    // double down double left
   (unsigned char *)NULL,              //   C_2u2r_b,    // double up double right
   (unsigned char *)NULL,              //   C_2d2r_b,    // double down double right

   (unsigned char *)NULL,              //   C_2vh_b,     // double vert hor
   (unsigned char *)NULL,              //   C_2vl_b,     // double vert left
   (unsigned char *)NULL,              //   C_2vr_b,     // double vert right
   (unsigned char *)NULL,              //   C_h2u_b,     // hor double up
   (unsigned char *)NULL,              //   C_h2d_b,     // hor double down
   (unsigned char *)NULL,              //   C_2ul_b,     // double up left
   (unsigned char *)NULL,              //   C_2dl_b,     // double down left
   (unsigned char *)NULL,              //   C_2ur_b,     // double up right
   (unsigned char *)NULL,              //   C_2dr_b,     // double down right

   (unsigned char *)NULL,              //   C_v2h_b,     // vert double hor
   (unsigned char *)NULL,              //   C_v2l_b,     // vert double left
   (unsigned char *)NULL,              //   C_v2r_b,     // vert double right
   (unsigned char *)NULL,              //   C_2hu_b,     // double hor up
   (unsigned char *)NULL,              //   C_2hd_b,     // double hor down
   (unsigned char *)NULL,              //   C_u2l_b,     // up double left
   (unsigned char *)NULL,              //   C_d2l_b,     // down double left
   (unsigned char *)NULL,              //   C_u2r_b,     // up double right
   (unsigned char *)NULL,              //   C_d2r_b,     // down double right

   (unsigned char *)NULL,         // SGML  C_block,     // pilnaviduris kvadratas per visa laukeli
   (unsigned char *)NULL,         // SGML  C_dgrblk,    // tamsiai pilkas ---//--- (75% shaded)
   (unsigned char *)NULL,         // SGML  C_grblk,     // pilkas ---//--- (50% shaded)
   (unsigned char *)NULL,         // SGML  C_lgrblk,    // sviesiai pilkas ---//--- (25% shaded)
   (unsigned char *)NULL,         // SGML  C_uphblk,    // pilnaviduris staciakampis per puse laukelio virsuje
   (unsigned char *)NULL,         // SGML  C_dnhblk,    // ---//--- apacioje
   (unsigned char *)NULL,              //   C_lthblk,    // ---//--- kaireje
   (unsigned char *)NULL,              //   C_rthblk,    // ---//--- desineje

   (unsigned char *)NULL,   //     C_utrif,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   (unsigned char *)NULL,   //     C_dtrif,     // pilnaviduris trikampis zemyn
   (unsigned char *)NULL,   //     C_ltrif,     // pilnaviduris trikampis i kaire
   (unsigned char *)NULL,   //     C_rtrif,     // pilnaviduris trikampis i desine

   (unsigned char *)NULL,        //   C_ph_uu_sh

   (unsigned char *)NULL,        //   C_hhyph,          // hard hyphen - zodzio kelimas per prievarta -\break
   (unsigned char *)NULL,        //   C_sbreak,         // soft break \lastwordinpar{5}{...} iki pastraipos (lizdo) pabaigos
   (unsigned char *)NULL,        //   C_hSpc,           // hard space - technical space after TEX commands - do not process
   (unsigned char *)NULL,        //   C_hbreak,         // break su \hfill, xmlsty keiciamas is C_Cr ("\r")
   (unsigned char *)NULL,        //   C_lSpc,           // last space - space, to be changed to C_NBSP after LAST_WORD_LEN
   (unsigned char *)NULL,        //   C_hlSpc,          // hard last space - C_hSpc, to be changed to C_NBSP after LAST_WORD_LEN

   (unsigned char *)NULL,        //     C_utrif_rtf,     // pilnaviduris lygiakrastis trikampis smaigaliu i virsu
   (unsigned char *)NULL,        //     C_dtrif_rtf,     // pilnaviduris trikampis zemyn
   (unsigned char *)NULL,        //     C_ltrif_rtf,     // pilnaviduris trikampis i kaire
   (unsigned char *)NULL,        //     C_rtrif_rtf,     // pilnaviduris trikampis i desine

// erdvines rodykles
   (unsigned char *)NULL,        // C_3DTopLightLeftArrowHead,
   (unsigned char *)NULL,        // C_3DBotLightLeftArrowHead,
   (unsigned char *)NULL,        // C_3DTopLightRightArrowHead,
   (unsigned char *)NULL,        // C_3DBotLightRightArrowHead,
   (unsigned char *)NULL,        // C_3DLeftLightUpArrowHead,
   (unsigned char *)NULL,        // C_3DRightLightUpArrowHead,
   (unsigned char *)NULL,        // C_3DLeftLightDownArrowHead,
   (unsigned char *)NULL,        // C_3DRightLightDownArrowHead,

   (unsigned char *)NULL,        // C_MinusMath

   (unsigned char *)NULL,        // C_ZeroWidthSpace

   (unsigned char *)NULL,        // C_ph_glot_stop

   (unsigned char *)NULL,  // "&nacc;"    // kp // C_AcuteNcomb
   (unsigned char *)NULL,  // "&ncd;"     // kp // C_CedilNcomb
   (unsigned char *)NULL,  // "&nmac;",   // kp // C_MacrNcomb

   (unsigned char *)"&dlr;",  // "$",  // "&dollar;", // SGML  // C_DollNctrl

   (unsigned char *)NULL, //  "&nogon;",  // kp // C_OgonNcomb

   (unsigned char *)NULL, //  "&nom;",    // kp // C_No

   (unsigned char *)NULL,  // "&ncaron;" // kp  // C_CarNcomb
   (unsigned char *)NULL,  // "&umln;"   // kp  // C_DiaerNcomb
   (unsigned char *)"&tilde;", // HTML // "&ntilde;" // kp  // C_TildeNcomb

   (unsigned char *)NULL,   //     C_utri
   (unsigned char *)NULL,   //     C_dtri
   (unsigned char *)NULL,   //     C_ltri
   (unsigned char *)NULL,   //     C_rtri

   (unsigned char *)NULL,  // "&oline;",// html // C_Oline

   (unsigned char *)NULL,  // "&Roline;",// kp // C_R_Oline
   (unsigned char *)NULL,  // "&Xoline;",// kp // C_X_Oline

   (unsigned char *)NULL,  // "&les;",  // C_leqslant
   (unsigned char *)NULL,  // "&ges;",  // C_geqslant

   (unsigned char *)NULL,  // C_i_Grave_Dotless
   (unsigned char *)NULL,  // C_i_Acute_Dotless
   (unsigned char *)NULL,  // C_i_Tilde_Dotless

   (unsigned char *)NULL,  // TEX //   C_A_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_E_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_I_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_O_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_U_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_Y_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_Ee_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_Ju_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_Ja_Cyr_Acute,

   (unsigned char *)NULL,  // TEX //   C_a_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_e_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_i_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_o_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_u_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_y_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_ee_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_ju_Cyr_Acute,
   (unsigned char *)NULL,  // TEX //   C_ja_Cyr_Acute,

   (unsigned char *)"&zwnj;", // "&zwj;", // HTML // C_NullSpc

   (unsigned char *)NULL,         // "-\""  C_Dash_Diaer

   (unsigned char *)NULL,         //  C_bdiamond,     /* juodas rombas */

   (unsigned char *)NULL,         //   C_DegCels

   (unsigned char *)NULL,         // C_hBpoint,  /* bullet, didelis taskas vidury */

// ----------------------- old style cyrillic
   (unsigned char *)NULL,              //   C_Fita_Cyr
   (unsigned char *)NULL,              //   C_fita_Cyr
   (unsigned char *)NULL,              //   C_Yat_Cyr
   (unsigned char *)NULL,              //   C_yat_Cyr

   (unsigned char *)NULL, // "&checkmark;", // KP //   C_checkmark

   (unsigned char *)NULL,              // C_prim_Ncomb
   (unsigned char *)NULL,              // C_dprim_Ncomb
};

