// ==================================================
// xmlg.h
// XML grupinių produktų parametrų / meniu tagai (StartGrp.exe)
//

// ---------------------------------------------------
// 2011.08.30 mp  Failo sukūrimas
//

// --------------------------
#include "envir.h"

#include <string>
#include <fstream>
#include <windows.h>

#include "kpstdlib.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "tvxml.h"
#include "xmlg.h"

// -------------------------- XG_Status reikšmės
KpChar iazXGS_None[] = { C_Nul };

KpChar iazXGS_Wait[] = { C_W, C_a, C_i, C_t, C_Nul };
// KpChar iazXGS_Ready[] = { C_R, C_e, C_a, C_d, C_y, C_Nul };
KpChar iazXGS_Free[] = { C_F, C_r, C_e, C_e, C_Nul };
// KpChar iazXGS_Busy[] = { C_B, C_u, C_s, C_y, C_Nul };
KpChar iazXGS_Available[] = { C_A, C_v, C_a, C_i, C_l, C_a, C_b, C_l, C_e, C_Nul };
KpChar iazXGS_Unavailable[] = { C_U, C_n, C_a, C_v, C_a, C_i, C_l, C_a, C_b, C_l, C_e, C_Nul };

KpChar *piazGrpStuses[XGS_NumOfStat02 + 1] =
{
   iazXGS_None,

   iazXGS_Wait,
   iazXGS_Free,
   iazXGS_Available,
   iazXGS_Unavailable,

   NULL
};

// --------------------------------------------------- group XML tags
const unsigned char *plpszaGrpTags[XG_NumOfGrpTagsArr08 + 1] =
{
   (unsigned char *)"<pr>",            // XG_GrPars
   (unsigned char *)"</pr>",           // XG_GrPars_e

   (unsigned char *)"<resp>",          // XG_Responce
   (unsigned char *)"</resp>",         // XG_Responce_e

   (unsigned char *)"<file>",          // XG_File
   (unsigned char *)"</file>",         // XG_File_e

// --------------------
   (unsigned char *)"<item>",          // XG_Item
   (unsigned char *)"</item>",         // XG_Item_e

      (unsigned char *)"<appname>",    // XG_AppName
      (unsigned char *)"</appname>",   // XG_AppName_e

      (unsigned char *)"<lic>",        // XG_Licence
      (unsigned char *)"</lic>",       // XG_Licence_e

      (unsigned char *)"<setup>",      // XG_Setup
      (unsigned char *)"</setup>",     // XG_Setup_e

      (unsigned char *)"<launch>",     // XG_Launch
      (unsigned char *)"</launch>",    // XG_Launch_e

//    (unsigned char *)"<file>",       // XG_File
//    (unsigned char *)"</file>",      // XG_File_e

      (unsigned char *)"<mpar>",       // XG_MPar
      (unsigned char *)"</mpar>",      // XG_MPar_e

// --------------------
   (unsigned char *)"<mhead>",         // XG_MHead
   (unsigned char *)"</mhead>",        // XG_MHead_e

   (unsigned char *)"<mitem>",         // XG_MItem
   (unsigned char *)"</mitem>",        // XG_MItem_e

   (unsigned char *)"<mwait>",         // XG_MWait
   (unsigned char *)"</mwait>",        // XG_MWait_e

   (unsigned char *)"<mfree>",         // XG_MFree
   (unsigned char *)"</mfree>",        // XG_MFree_e

   (unsigned char *)"<mpend>",         // XG_MPend
   (unsigned char *)"</mpend>",        // XG_MPend_e

   (unsigned char *)"<munavail>",      // XG_MUnavail // former <mbusy>
   (unsigned char *)"</munavail>",     // XG_MUnavail_e

   (unsigned char *)"<mtail>",         // XG_MTail
   (unsigned char *)"</mtail>",        // XG_MTail_e

      (unsigned char *)"<vers>",       // XG_Vers,
      (unsigned char *)"</vers>",      // XG_Vers_e,

      (unsigned char *)"<prodvar>",    // XG_ProdVar,
      (unsigned char *)"</prodvar>",   // XG_ProdVar_e,

      (unsigned char *)"<comm>",       // XG_Comments,
      (unsigned char *)"</comm>",      // XG_Comments_e,

      (unsigned char *)"<status>",     // XG_Comments,
      (unsigned char *)"</status>",    // XG_Comments_e,

      (unsigned char *)"<prc>",        // XG_Prc,
      (unsigned char *)"</prc>",       // XG_Prc_e,

      (unsigned char *)"<updname>",    // XG_UpdName
      (unsigned char *)"</updname>",   // XG_UpdName_e

// --------------------
   (unsigned char *)"<background>",    // XG_BackGround
   (unsigned char *)"</background>",   // XG_BackGround_e

   (unsigned char *)"<button>",        // XG_Button  
   (unsigned char *)"</button>",       // XG_Button_e  

   (unsigned char *)"<butimg>",        // XG_ButImg  
   (unsigned char *)"</butimg>",       // XG_ButImg_e  

   (unsigned char *)"<butpressed>",    // XG_ButPressed
   (unsigned char *)"</butpressed>",   // XG_ButPressed_e

   (unsigned char *)"<buthover>",      // XG_ButHover
   (unsigned char *)"</buthover>",     // XG_ButHover_e

// --------------------
   null                                // XG_LastGrpTag
};
