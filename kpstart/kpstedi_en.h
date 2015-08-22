// -----------------------------------------
// kpstedi_en.h
// kpstedi pranesimai
// anglø kalba
//

#ifndef kpstedi_en_included
#define kpstedi_en_included

#if ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#define KPSTEDI_INI_FILTER_NAME_EN     ((const unsigned char *)"Ini files")
#define KPSTEDI_INI_FILE_PROMPT_EN     ((const unsigned char *)"Select ini file")
#if (KPSTEDI_MODE & OWNER_MODE)
#  define KPSTEDI_USER_DATA_CHANGED_EN ((const unsigned char *)"Password and user data updated successfully.")
#else
#  define KPSTEDI_USER_DATA_CHANGED_EN ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_TAB_PROD_EN          (/* (const unsigned char *) */ "  Product  ")
#  define KPSTEDI_TAB_START_EN         (/* (const unsigned char *) */ "  Launch  ")
#  define KPSTEDI_TAB_BOUND_EN         (/* (const unsigned char *) */ "  Protection  ")
#  define KPSTEDI_TAB_DATA_EN          (/* (const unsigned char *) */ "  Data  ")
#  define KPSTEDI_TAB_OWNER_EN         (/* (const unsigned char *) */ "  User  ")
#else
#  define KPSTEDI_TAB_PROD_EN          (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_START_EN         (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_BOUND_EN         (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_DATA_EN          (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_OWNER_EN         (/* (const unsigned char *) */ "")
#endif

#if ((KPSTEDI_MODE & STARTER_MODE) == 0) // && ((KPSTEDI_MODE & USER_MODE) == 0)
#  if KPSTEDI_MODE & OWNER_MODE
#     define KPSTEDI_TITLE_EN        ((const unsigned char *)"User data and password")
#  else
#     define KPSTEDI_TITLE_EN        ((const unsigned char *)"Program launching parameters")
#  endif
#else
#  define KPSTEDI_TITLE_EN           ((const unsigned char *)"")
#endif


#if KPSTEDI_MODE & STARTER_MODE
#  define KPSTEDI_REZ_NOT_CLOSE_1_EN   ((const unsigned char *)"If this window will not close,")
#  define KPSTEDI_REZ_NOT_CLOSE_2_EN   ((const unsigned char *)"try to change data file name")
#else
#  define KPSTEDI_REZ_NOT_CLOSE_1_EN   ((const unsigned char *)"")
#  define KPSTEDI_REZ_NOT_CLOSE_2_EN   ((const unsigned char *)"")
#endif

// Produktas
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_PROD_PROMPT_EN       ((const unsigned char *)"Product name") // :")
#  define KPSTEDI_WNDNAME_PROMPT_EN    ((const unsigned char *)"Window name") // :")
#  define KPSTEDI_PUBL_PROMPT_EN       ((const unsigned char *)"Producer") // :")
#  define KPSTEDI_PRODVER_PROMPT_EN    ((const unsigned char *)"Product/version (VVPPP)") // :")
#  define KPSTEDI_UPDNUM_PROMPT_EN     ((const unsigned char *)"No. of update (ProdVar + 1)") // :")
#  define KPSTEDI_VOL_PROMPT_EN        ((const unsigned char *)"Code name") // :") // "Disko þymë:")
#  define KPSTEDI_VOL_PROMPT1_EN       ((const unsigned char *)"Used as:")
#  define KPSTEDI_VOL_PROMPT2_EN       ((const unsigned char *)"   - CD label;")
#  define KPSTEDI_VOL_PROMPT3_EN       ((const unsigned char *)"   - first part of the local data server file/service name (in this case should not exceed 5 bytes);")
#  define KPSTEDI_VOL_PROMPT4_EN       ((const unsigned char *)"   - file name of the .dat file, containing the list of files in the MIMOK folder Mano (without an extension \".dat\"); suffix of the folder Mano_...;")
#  define KPSTEDI_VOL_PROMPT5_EN       ((const unsigned char *)"   - file name of the USB flash drive protection file .ini for StartSel.exe (without an extension .ini); file name of the starter .exe file.")
#else
#  define KPSTEDI_PROD_PROMPT_EN       ((const unsigned char *)"")
#  define KPSTEDI_WNDNAME_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_PUBL_PROMPT_EN       ((const unsigned char *)"")
#  define KPSTEDI_PRODVER_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_UPDNUM_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT_EN        ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT1_EN       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT2_EN       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT3_EN       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT4_EN       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT5_EN       ((const unsigned char *)"")
#endif

// Paleistis
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_CMD_STR_PROMPT_EN    ((const unsigned char *)"Start commandline") // :")
#  define KPSTEDI_CMD_STR_PROMPT1_EN   ((const unsigned char *)"All commands could be just name of the data file, which extension is assigned to default processing tool.")
#  define KPSTEDI_CMD_STR_PROMPT2_EN   ((const unsigned char *)"Macrocommands could be used in the start command:")
#  define KPSTEDI_CMD_STR_PROMPT3_EN   ((const unsigned char *)"   {att} - generated file name of the attachment with the full path, but without the extension;")
#  define KPSTEDI_CMD_STR_PROMPT4_EN   ((const unsigned char *)"   {prog} - file name of the starter program (just name, without the path and extension);")
#  define KPSTEDI_CMD_STR_PROMPT5_EN   ((const unsigned char *)"   {user} - path to the parent folder of the folder, where the starter program is located;")
#  define KPSTEDI_CMD_STR_PROMPT6_EN   ((const unsigned char *)"      (used for dynamic launching in USB flash drives).")
#  define KPSTEDI_ATTOFF_PROMPT_EN     ((const unsigned char *)"Starting address of the attachment") // :")
#  define KPSTEDI_ATTEXT_PROMPT_EN     ((const unsigned char *)"Extension of the attachment") // :")
#  define KPSTEDI_PROL_PROMPT_EN       ((const unsigned char *)"Prologue command") // :")
#  define KPSTEDI_PROL_TIME_PROMPT_EN  ((const unsigned char *)"Prologue duration") // :")
#  define KPSTEDI_SEC_PROMPT_EN        ((const unsigned char *)"sec")
#  define KPSTEDI_BMP_PROMPT_EN        ((const unsigned char *)"Splash picture") // :")
#  define KPSTEDI_BMP_SIZ_PROMPT_EN    ((const unsigned char *)"Picture size") // :")
#  define KPSTEDI_TIMES_PROMPT_EN      ((const unsigned char *)"x")
#  define KPSTEDI_BMP_PIX_PROMPT_EN    ((const unsigned char *)"pixels")
#  define KPSTEDI_MUTE_PROMPT_EN       ((const unsigned char *)"Sound is off") // :")
#  define KPSTEDI_EPIL_PROMPT_EN       ((const unsigned char *)"Epilogue command") // :")
#  define KPSTEDI_EPIL_TIME_PROMPT_EN  ((const unsigned char *)"Epilogue duration") // :")
#  define KPSTEDI_ONTOP_PROMPT_EN      ((const unsigned char *)"Prohibit launching of other programs") // :")
#  define KPSTEDI_FULLSCR_PROMPT_EN    ((const unsigned char *)"Full screen mode") // :")
#  define KPSTEDI_CLRCLIPBRD_PROMPT_EN ((const unsigned char *)"Clear clipboard") // :")
#  define KPSTEDI_SUBST_PROMPT_EN      ((const unsigned char *)"Start in virtual disk") // :")
#  define KPSTEDI_EBOARD_PROMPT_EN     ((const unsigned char *)"Electronic board") // :")
#  define KPSTEDI_SHIE_PROMPT_EN       ((const unsigned char *)"Launch IE") // :")
#  define KPSTEDI_HBMARKS_PROMPT_EN    ((const unsigned char *)"Hide bookmarks") // :")
#  define KPSTEDI_SNDMUT_PROMPT_EN     ((const unsigned char *)"Sound muted")   // "Garsas iðjungtas"
#  define KPSTEDI_FINDBUT_PROMPT_EN    ((const unsigned char *)"Find button") // :")
#else
#  define KPSTEDI_CMD_STR_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT1_EN   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT2_EN   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT3_EN   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT4_EN   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT5_EN   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT6_EN   ((const unsigned char *)"")
#  define KPSTEDI_ATTOFF_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_ATTEXT_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_PROL_PROMPT_EN       ((const unsigned char *)"")
#  define KPSTEDI_PROL_TIME_PROMPT_EN  ((const unsigned char *)"")
#  define KPSTEDI_SEC_PROMPT_EN        ((const unsigned char *)"")
#  define KPSTEDI_BMP_PROMPT_EN        ((const unsigned char *)"")
#  define KPSTEDI_BMP_SIZ_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_TIMES_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_BMP_PIX_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_MUTE_PROMPT_EN       ((const unsigned char *)"")
#  define KPSTEDI_EPIL_PROMPT_EN       ((const unsigned char *)"")
#  define KPSTEDI_EPIL_TIME_PROMPT_EN  ((const unsigned char *)"")
#  define KPSTEDI_ONTOP_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_FULLSCR_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_CLRCLIPBRD_PROMPT_EN ((const unsigned char *)"")
#  define KPSTEDI_SUBST_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_EBOARD_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_SHIE_PROMPT_EN       ((const unsigned char *)"")
#  define KPSTEDI_HBMARKS_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_SNDMUT_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_FINDBUT_PROMPT_EN    ((const unsigned char *)"")
#endif

// Pririðimas
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_BOUND_PROMPT_EN      ((const unsigned char *)"Bind to computer") // :")
#  define KPSTEDI_BOUND_PROMPT1_EN     ((const unsigned char *)"(local licence server)")
#  define KPSTEDI_CITYP_PROMPT_EN      ((const unsigned char *)"Computer ID") // :")
#  define KPSTEDI_CITYP_PROMPT_B_EN    ((const unsigned char *)"BIOS date")
#  define KPSTEDI_CITYP_PROMPT_D_EN    ((const unsigned char *)"HD serial No.")
#  define KPSTEDI_CITYP_PROMPT_P_EN    ((const unsigned char *)"Processor ID")
#  define KPSTEDI_CITYP_PROMPT_N_EN    ((const unsigned char *)"Processor name")
#  define KPSTEDI_CITYP_PROMPT_M_EN    ((const unsigned char *)"MAC address")
#  define KPSTEDI_CITYP_PROMPT_V_EN    ((const unsigned char *)"Soft „bolt“")
#  define KPSTEDI_CIDIR_PROMPT_EN      ((const unsigned char *)"Read compiuter ID") // :")
#  define KPSTEDI_CIDIR_PROMPT1_EN     ((const unsigned char *)"directly from HW")
#  define KPSTEDI_CIDIR_PROMPT2_EN     ((const unsigned char *)"from hidden file")
#else
#  define KPSTEDI_BOUND_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_BOUND_PROMPT1_EN     ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_B_EN    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_D_EN    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_P_EN    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_N_EN    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_M_EN    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_V_EN    ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT1_EN     ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT2_EN     ((const unsigned char *)"")
#endif

#if (KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)) && ((KPSTEDI_MODE & STARTER_MODE) == 0)
#  if KPSTEDI_MODE & USER_MODE
#     define KPSTEDI_REGURL_PROMPT_EN  ((const unsigned char *)"Server address") // :") 
#     define KPSTEDI_REGURL_PROMPT1_EN ((const unsigned char *)"")
#  else
#     define KPSTEDI_REGURL_PROMPT_EN  ((const unsigned char *)"Registering URL or")
#     define KPSTEDI_REGURL_PROMPT1_EN ((const unsigned char *)"address of local server") // :")
#  endif                
#else
#  define KPSTEDI_REGURL_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_REGURL_PROMPT1_EN    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_LICNUM_PROMPT_EN     ((const unsigned char *)"Max. count of local licences") // :")
#  define KPSTEDI_BOUND_FL_PROMPT_EN   ((const unsigned char *)"Bind to the USB flash drive") // :")
#  define KPSTEDI_LIC_FL_PROMPT_EN     ((const unsigned char *)"Licenced USB flash drive")
#else
#  define KPSTEDI_LICNUM_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_BOUND_FL_PROMPT_EN   ((const unsigned char *)"")
#  define KPSTEDI_LIC_FL_PROMPT_EN     ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_FLASH_ID_PROMPT_EN   ((const unsigned char *)"USB flash drive ID") // :")
#  define KPSTEDI_LIC_ID_PROMPT_EN     ((const unsigned char *)"Licence code") // :")
#  define KPSTEDI_LIC_ID_PROMPT1_EN    ((const unsigned char *)"Used for binding the update to the partial licence.")
#else
#  define KPSTEDI_FLASH_ID_PROMPT_EN   ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT_EN     ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT1_EN    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_PWD_WND_PROMPT_EN    ((const unsigned char *)"Window of the password/program") // :")
#  define KPSTEDI_PWD_WND_PROMPT1_EN   ((const unsigned char *)"After appearing of this window the prologue is being stopped and splash picture destroyed.")
#  define KPSTEDI_PWD_PROMPT_EN        ((const unsigned char *)"Password") // :")
#  define KPSTEDI_OLD_PWD_PROMPT_EN    ((const unsigned char *)"Old password") // :")
#  define KPSTEDI_PWD_EDIT_PROMPT_EN   ((const unsigned char *)"Id. of the password field") // :")
#  define KPSTEDI_PWD_BUT_PROMPT_EN    ((const unsigned char *)"Id. of the \"OK\" button") // :")
#  define KPSTEDI_CHCD_PROMPT_EN       ((const unsigned char *)"Deamnd a CD") // :")
#else
#  define KPSTEDI_PWD_WND_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_PWD_WND_PROMPT1_EN   ((const unsigned char *)"")
#  define KPSTEDI_PWD_PROMPT_EN        ((const unsigned char *)"")
#  define KPSTEDI_OLD_PWD_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_PWD_EDIT_PROMPT_EN   ((const unsigned char *)"")
#  define KPSTEDI_PWD_BUT_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_CHCD_PROMPT_EN       ((const unsigned char *)"")
#endif

// Duomenys
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_INI_PROMPT_EN        ((const unsigned char *)"Initialization file") // :")
#  define KPSTEDI_INI_PROMPT1_EN       ((const unsigned char *)"Its contents are transfered to the clipboard before launching the main application.")
#else
#  define KPSTEDI_INI_PROMPT_EN        ((const unsigned char *)"")
#  define KPSTEDI_INI_PROMPT1_EN       ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  define KPSTEDI_REZ_PROMPT_EN        ((const unsigned char *)"Results file") // :")
#else
#  define KPSTEDI_REZ_PROMPT_EN        ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_REZ_VAR_PROMPT_EN    ((const unsigned char *)"Results variables") // :")
#  define KPSTEDI_SHUFF_PROMPT_EN      ((const unsigned char *)"Number of toggled fields (max. 9)") // :")
#  define KPSTEDI_CUMUL_PROMPT_EN      ((const unsigned char *)"Attach results to the end of the existing file") // :")
#  define KPSTEDI_TESTC_PROMPT_EN      ((const unsigned char *)"Test identifier") // :")
#else
#  define KPSTEDI_REZ_VAR_PROMPT_EN    ((const unsigned char *)"")
#  define KPSTEDI_SHUFF_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_CUMUL_PROMPT_EN      ((const unsigned char *)"")
#  define KPSTEDI_TESTC_PROMPT_EN      ((const unsigned char *)"")
#endif

// Naudotojas
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
#        if KPSTEDI_MODE & LOGIN_MODE
#           define KPSTEDI_USER_PWD_PROMPT_EN  ((const unsigned char *)"Password:")
#        else
#           define KPSTEDI_USER_PWD_PROMPT_EN  ((const unsigned char *)"Password") // :")
#        endif
#  define KPSTEDI_TESTUPD_PROMPT_EN    ((const unsigned char *)"Check updates")   // "Tikrinti atnaujinimus"
#else
#  define KPSTEDI_TESTUPD_PROMPT_EN    ((const unsigned char *)"")   // "Tikrinti atnaujinimus"
#  define KPSTEDI_USER_PWD_PROMPT_EN  ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_REPEAT_PWD_PROMPT_EN ((const unsigned char *)"Repeate password") // :")
#else
#  define KPSTEDI_REPEAT_PWD_PROMPT_EN ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_ADMIN_PWD_PROMPT_EN  ((const unsigned char *)"USB flash drive licence")
#  define KPSTEDI_NO_FLASH_LIC_EN      ((const unsigned char *)"USB flash drive licence missing or swapped parameters")
#else
#  define KPSTEDI_ADMIN_PWD_PROMPT_EN  ((const unsigned char *)"")
#  define KPSTEDI_NO_FLASH_LIC_EN      ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
#  if KPSTEDI_MODE & LOGIN_MODE
#     define KPSTEDI_USER_DATA_PROMPT_EN  ((const unsigned char *)"User:")
#  else
#     define KPSTEDI_USER_DATA_PROMPT_EN  ((const unsigned char *)"User")
#  endif
#else
#  define KPSTEDI_USER_DATA_PROMPT_EN  ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  define KPSTEDI_SEL_REZ_FILE_EN      ((const unsigned char *)"Select results file")
#else
#  define KPSTEDI_SEL_REZ_FILE_EN      ((const unsigned char *)"")
#endif

// !!!!

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_SURE_CHANGE_PWD_EN    ((const unsigned char *)"You have just entered program launch password. It will be asked before each start of the program.\n \nAre you sure?")
#  define KPSTEDI_PWD_NOT_MATCH_EN      ((const unsigned char *)"Passwords do not fit.")
#else
#  define KPSTEDI_SURE_CHANGE_PWD_EN    ((const unsigned char *)"")
#  define KPSTEDI_PWD_NOT_MATCH_EN      ((const unsigned char *)"")
#endif
#  define KPSTEDI_USER_PWD_NOT_MATCH_EN  KPSTEDI_PWD_NOT_MATCH_EN

#define KPSTEDI_REZ_FILES_EN            ((const unsigned char *)"Result files (*.txt)") // "Resultatø failai"

#endif // #if ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#endif // #ifndef kpstedi_en_included
