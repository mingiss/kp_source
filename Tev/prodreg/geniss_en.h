// ===================================================
// geniss.cpp
// Inno Setup scriptu generatorius
// angliski praneðimai
//


#ifndef geniss_en_included
#define geniss_en_included

#if TRUE // ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#define GENISS_MSG_START_PROG_EN          ((const unsigned char *)"Run program")
#define GENISS_MSG_UNSUCC_START_EN        ((const unsigned char *)"Unable to run file")
#define GENISS_MSG_PROG_NOT_ISTALLED_EN   ((const unsigned char *)"Program “\' + GetFirstVerName + \'” not yet installed")
#define GENISS_MSG_UPD_NOT_ISTALLED_EN    ((const unsigned char *) /* update */ "“\' + GetPrevVerName + \'” not yet installed")

#define GENISS_MSG_RESTART_ADMIN_EN       ((const unsigned char *)"run the program again under privileged user rights")
#define GENISS_MSG_INST_ADMIN_EN          ((const unsigned char *)"Privileged user rights are required for the installation")
#define GENISS_MSG_UNINST_ADMIN_EN        ((const unsigned char *)"Privileged user rights are required for the uninstallation")

#define GENISS_MSG_FLASH_PLAYER_EN        ((const unsigned char *)"Macromedia Flash player will be installed. Follow further instructions of the installation program.")
#define GENISS_MSG_CABRI_EN               ((const unsigned char *)"Cabri 3D plugin will be installed. Follow further instructions of the installation program.")

#define GENISS_MSG_NAT_LET_EN             ((const unsigned char *)"National letters with diacritical marks in file names could be used only in case of proper settings of the Regional Options of your Windows OS.\'+Chr(10)+Chr(10)+\'Do you want to use such letters in file names?")

#define GENISS_MSG_ATM_KOD_TIT_EN         ((const unsigned char *)"USB flash drive licence code")
#define GENISS_MSG_ATM_KOD_MAIN_EN        ((const unsigned char *)"Enter USB flash drive licence code.")
#define GENISS_MSG_ATM_KOD_PROMPT_EN      GENISS_MSG_ATM_KOD_TIT_EN

#define GENISS_MSG_CHK_UPD_TIT_EN         ((const unsigned char *)"Automatic checking of updates")
// #define GENISS_MSG_CHK_UPD_MAIN_EN        ((const unsigned char *)"Clear the checkbox, if you don\'t want updates to be checked automatically by Internet.")
#define GENISS_MSG_CHK_UPD_MAIN_EN        ((const unsigned char *)"Clear the checkbox, if you don\'t want updates to be checked automatically over the Internet.")
#define GENISS_MSG_CHK_UPD_PROMPT_EN      GENISS_MSG_CHK_UPD_TIT_EN
    
// produktø pavadinimø priesagos
#define GENISS_PROD_FLASH_EN              ((const unsigned char *)"USB flash") // atmintukinë produkto versija
#define GENISS_PROD_LAN_EN                ((const unsigned char *)"network") // tinklinë produkto versija
#define GENISS_PROD_SERVER_EN             ((const unsigned char *)"server") // produkto duomenø/licencijø serveris LAN-e   
 
// ikonø/katalogø pavadinimai ir jø priesagos
#define GENISS_LINK_OPTIONS_EN            ((const unsigned char *)"Options")
// #define GENISS_LINK_REG_EN                ((const unsigned char *)"Registration")
#define GENISS_LINK_REG_EN                ((const unsigned char *)"Activate")
#define GENISS_LINK_UNREG_EN              ((const unsigned char *)"Remove")
#define GENISS_LINK_FLASH_EN              GENISS_PROD_FLASH_EN
#define GENISS_LINK_FLASH_CHK_EN          ((const unsigned char *)"USB flash chek")
#define GENISS_LINK_LAN_EN                GENISS_PROD_LAN_EN
#define GENISS_LINK_SERVER_EN             GENISS_PROD_SERVER_EN
#define GENISS_LINK_SERVER_MANAGEMENT_EN  ((const unsigned char *)"Server management")
#define GENISS_LINK_CLEAN_NAT_EN          ((const unsigned char *)"Clean obsolete results")
#define GENISS_LINK_CLEAN_LAT_EN          GENISS_LINK_CLEAN_NAT_EN

#define GENISS_INSERT_FLASH_KEY_EN        ((const unsigned char *)"Insert flash drive with the program ")

#define GENISS_LINK_DIAG_MSG_NAT_EN       ((const unsigned char *)"Send error report")
#define GENISS_LINK_DIAG_MSG_LAT_EN       ((const unsigned char *)"Send error report")

#endif // #if TRUE // ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#endif // #ifndef geniss_en_included
