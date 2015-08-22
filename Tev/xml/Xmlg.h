// ==================================================
// xmlg.h
// XML apibrėžimai grupinių produktų parametrų / meniu failams (StartGrp.exe)
//

// ---------------------------------------------------
// 2011.08.30 mp  Failo sukūrimas
//


#ifndef xmlg_included
#define xmlg_included


// -------------------------- XG_Status reikšmės
enum XmlGrpStatus
{
   XGS_None,        // 0

   XGS_Wait,        // 1
   XGS_Free,        // 2 // former XGS_Ready
   XGS_Available,   // 3 // former XGS_Busy
   XGS_Unavailable, // 4

   XGS_NumOfStat
};

#define XGS_NumOfStat02 XGS_NumOfStat


extern KpChar *piazGrpStuses[XGS_NumOfStat + 1];

// --------------------------------------------------- group XML tags
#define XG_NumOfGrpTags00    (XG_LastGrpTag-XG_FirstGrpTag)
#define XG_NumOfGrpTagsArr08 XG_NumOfGrpTags00

enum XmlGrpTagChars                        // Group XML tag characters
{
   XG_FirstGrpTag    = XG_FirstGrpTagCode, // = 8000,

// --------------------
   XG_GrPars         = XG_FirstGrpTagCode, // = 8000, // <pr>
   XG_GrPars_e,      /*  8001 */

   XG_Responce,      /*  8002 */ // <resp>
   XG_Responce_e,    /*  8003 */

   XG_File,          /*  8004 */ // <file size="297995" date="2011.10.05">
   XG_File_e,        /*  8005 */

// --------------------
   XG_Item,          /*  8006 */ // <item>
   XG_Item_e,        /*  8007 */

      XG_AppName,    /*  8008 */ // <appname>
      XG_AppName_e,  /*  8009 */

      XG_Licence,    /*  8010 */ // <lic>
      XG_Licence_e,  /*  8011 */

      XG_Setup,      /*  8012 */ // <setup size="29914445">
      XG_Setup_e,    /*  8013 */

      XG_Launch,     /*  8014 */ // <launch>
      XG_Launch_e,   /*  8015 */

//    XG_File,       /*  8016 */ // <file size="297995">
//    XG_File_e,     /*  8017 */

      XG_MPar,       /*  8018 */ // <mpar>
      XG_MPar_e,     /*  8019 */

// --------------------
   XG_MHead,         /*  8020 */ // <mhead>
   XG_MHead_e,       /*  8021 */

   XG_MItem,         /*  8022 */ // <mitem>
   XG_MItem_e,       /*  8023 */

   XG_MWait,         /*  8024 */ // <mwait>
   XG_MWait_e,       /*  8025 */

   XG_MFree,         /*  8026 */ // <mfree> // former XG_MReady // <mready>
   XG_MFree_e,       /*  8027 */

   XG_MPend,         /*  8028 */ // <mpend>
   XG_MPend_e,       /*  8029 */

   XG_MUnavail,      /*  8030 */ // <munavail> // former XG_MBusy // <mbusy>
   XG_MUnavail_e,    /*  8031 */

   XG_MTail,         /*  8032 */ // <mtail>
   XG_MTail_e,       /*  8033 */

// -------------------- papildomi tagai XG_Item viduje
      XG_Vers,       /*  8034 */ // <vers>   // atnaujinimo versijos pavadinimas: <vers>v2.11a.5</vers>
      XG_Vers_e,     /*  8035 */             // atnaujinimų selektinimo lange rodomas šitas vietoj XG_AppName,
                                             // pastarasis visiems vieno produkto atnaujinimams tas pats
      XG_ProdVar,    /*  8036 */ // <prodvar> // atnaujinimo eilės numeris ProdVar: <prodvar>1</prodvar>, pagrindinio produkto ProdVar = 0
      XG_ProdVar_e,  /*  8037 */

      XG_Comments,   /*  8038 */ // <comm>   // komentarai
      XG_Comments_e, /*  8039 */

      XG_Status,     /*  8040 */ // <status> // <item>-o būsena
      XG_Status_e,   /*  8041 */

      XG_Prc,        /*  8042 */ // <prc> // termometriuko prie ikonos progresas (makrokomandos {prc} generavimui naudojant šabloną <mpend>)
      XG_Prc_e,      /*  8043 */

      XG_UpdName,    /*  8044 */ // <updname> // updeito vardas, konkatenuojamas su <appname> ir išvedamas updeito pasirinkimo meniu
      XG_UpdName_e,  /*  8045 */

// --------------------
   XG_BackGround,    /*  8046 */ // <background size="297995" date="2012.08.20" caption="40">
   XG_BackGround_e,  /*  8047 */

   XG_Button,        /*  8048 */ // <button id="exit"> // <button id="minimize">
   XG_Button_e,      /*  8049 */

   XG_ButImg,        /*  8050 */ // <butimg size="297995" date="2012.08.20">
   XG_ButImg_e,      /*  8051 */

   XG_ButPressed,    /*  8052 */ // <butpressed size="297995" date="2012.08.20">
   XG_ButPressed_e,  /*  8053 */

   XG_ButHover,      /*  8054 */ // <buthover size="297995" date="2012.08.20">
   XG_ButHover_e,    /*  8055 */

// --------------------
   XG_LastGrpTag      // ne paskutinis, o pirmas jau nebe XmlGrpTagChars
};

// -------------------------
extern const unsigned char *plpszaGrpTags[XG_NumOfGrpTags00 + 1];  // grupinių tagų vardai

#endif
