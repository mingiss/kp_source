// -----------------------------------------
// kpstmsg_en.h
// programos paleidimo aplikaciju pranesimai
// anglø kalba
// 

#ifndef kpstmsg_en_included
#define kpstmsg_en_included

#if TRUE // ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

// #define KPST_MSG_PROD_REG_EN        ((const unsigned char *)"Program registration")
#define KPST_MSG_PROD_REG_EN        ((const unsigned char *)"Product activation")
// #define KPST_MSG_UNREG_EN           ((const unsigned char *)"Registration cancellation")
// #define KPST_MSG_UNREG_EN           ((const unsigned char *)"Registration cancellation")
#define KPST_MSG_UNREG_EN           ((const unsigned char *)"Product deactivation")
#define KPST_MSG_LIC_EN             ((const unsigned char *)"Licence")
// #define KPST_MSG_REG_INFO_EN        ((const unsigned char *)"To keep program running, licence should be registered.")
#define KPST_MSG_REG_INFO_EN        ((const unsigned char *)"To keep program running, licence should be activated.")
#define KPST_MSG_IVESK_LIC_EN       ((const unsigned char *)"Enter licence code acquired together with the product.")
#define KPST_MSG_IVESK_LIC_1_EN     ((const unsigned char *)"(Whole code could be copied into the very first field.)")
#define KPST_MSG_REG_CARD_EN        ((const unsigned char *)"")
#define KPST_MSG_LIC_KOD_EN         ((const unsigned char *)"Licence code:")
#define KPST_MSG_BLOGAS_LIC_KODAS_EN   ((const unsigned char *)"Invalid licence code")
// #define KPST_MSG_CHECK_CONN_EN      ((const unsigned char *)"Check your computer Internet connection")
#define KPST_MSG_CHECK_CONN_EN      KP_MSG_FIREWALL_EN
// #define KPST_MSG_CHECK_CONN_LOC_EN  ((const unsigned char *)"Check your computer network connection")
#define KPST_MSG_CHECK_CONN_LOC_EN  ((const unsigned char *)"Access to local computer network rejected. Check your firewall settings – try to add %s to the list of programs with allowed internet access.")
// #define KPST_MSG_REG_SUCC_EN        ((const unsigned char *)"%s\n                                       \nLicence registered successfully") 
#define KPST_MSG_REG_SUCC_EN        ((const unsigned char *)"%s\n                                       \nLicence activated successfully") 
// #define KPST_MSG_ALLREADY_REG_EN    ((const unsigned char *)"%s\n                                       \nLicence already registered") 
#define KPST_MSG_ALLREADY_REG_EN    ((const unsigned char *)"%s\n                                       \nLicence already activated") 
// #define KPST_MSG_REG_UNSUC_EN       ((const unsigned char *)"Unsuccessful licence registration by Internet.")
#define KPST_MSG_REG_UNSUC_EN       ((const unsigned char *)"Unsuccessful licence activation over the Internet.")
#define KPST_MSG_REG_UNSUC_0_EN     ((const unsigned char *)"Try to open following link")
#define KPST_MSG_REG_UNSUC_1_EN     ((const unsigned char *)"using a browser and copy the answer into the fields of instlallation code below.")
// #define KPST_MSG_REG_UNSUC_LOC_EN   ((const unsigned char *)"Registration unsuccessful.")
#define KPST_MSG_REG_UNSUC_LOC_EN   ((const unsigned char *)"Activation unsuccessful.")
#define KPST_MSG_DIEG_KOD_EN        ((const unsigned char *)"Installation code:")

// #define KPST_MSG_UNREG_INFO_EN      ((const unsigned char *)"Licence registration should be cancelled before moving the program to another computer.")
#define KPST_MSG_UNREG_INFO_EN      ((const unsigned char *)"Licence should be deactivated before moving the program to another computer.")
#define KPST_MSG_UNREG_IVESK_LIC_EN KPST_MSG_IVESK_LIC_EN

// #define KPST_MSG_REG_PERSPEJ_EN     ((const unsigned char *)"Registered program will run on this computer only!")
#define KPST_MSG_REG_PERSPEJ_EN     ((const unsigned char *)"Activated program will run on this computer only!")

// #define KPST_MSG_BUT_REG_EN         ((const unsigned char *)"How would you register?")
#define KPST_MSG_BUT_REG_EN         ((const unsigned char *)"How would you activate?")
// #define KPST_MSG_BUT_UNREG_EN       ((const unsigned char *)"How would you cancel registration?")
#define KPST_MSG_BUT_UNREG_EN       ((const unsigned char *)"How would you deactivate?")

// #define KPST_MSG_INTERNETU_EN       ((const unsigned char *)"By Internet")
#define KPST_MSG_INTERNETU_EN       ((const unsigned char *)"Over the Internet")
#define KPST_MSG_TELEFONU_EN        ((const unsigned char *)"By phone")
#define KPST_MSG_CANCEL_REG_EN      ((const unsigned char *)"Cancel")
#define KPST_MSG_CANCEL_UNREG_EN    ((const unsigned char *)"Do not deactivate")

#define KPST_MSG_SIUSK_PASTU_EN     ((const unsigned char *)"Installation code should be sent by an e-mail, address tech@tev.lt or told")
#define KPST_MSG_DARBO_LAIKAS_EN    ((const unsigned char *)"to the operator at working hours from 9 to 16 EET by phone, number")
#define KPST_MSG_DIKT_TELEF_EN      ((const unsigned char *)"+370-5-2729318.")

#define KPST_MSG_IVESK_RAKTA_EN     ((const unsigned char *)"Enter received answer - installation key.")
#define KPST_MSG_IVESK_RAKTA_1_EN   ((const unsigned char *)"(Whole key could be copied into the very first field.)")
#define KPST_MSG_DIEG_RAKTAS_EN     ((const unsigned char *)"Installation key:")
#define KPST_MSG_DIEG_RAKTAS_1_EN   ((const unsigned char *)"Installation key")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_EN ((const unsigned char *)"Invalid installation key")
// #define KPST_MSG_START_FROM_CD_EN   ((const unsigned char *)"Run the program directly from CD")
#define KPST_MSG_START_FROM_CD_EN   ((const unsigned char *)"Run the program directly from the CD")
#define KPST_MSG_BAD_CD_EN          ((const unsigned char *)"Invalid CD")

#define KPST_MSG_REZ_NESUFORM_EN    ((const unsigned char *)"Results were not generated.\nAsk for the technical support by e-mail, address tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_EN    ((const unsigned char *)"Results were not found.\nAsk for the technical support by e-mail, address tech@tev.lt")
// #define KPST_MSG_REZ_NFOUND_2_EN    ((const unsigned char *)"Results were not found.\nYou are %s, OS %s.\nTry login to the privileged user.")
#define KPST_MSG_REZ_NFOUND_2_EN    ((const unsigned char *)"Results were not found.\nYou are %s, OS %s.\nTry login as system administrator.")
#define KPST_MSG_REZ_SUCCESS_EN     ((const unsigned char *)". Results were successfully moved to ")

// #define KPST_MSG_REG_NOT_ADMIN_EN   ((const unsigned char *)"Licence registration requires rights of privileged user")
// #define KPST_MSG_REG_NOT_ADMIN_EN   ((const unsigned char *)"Licence registration requires rights of system administrator")
#define KPST_MSG_REG_NOT_ADMIN_EN   ((const unsigned char *)"Licence activation requires privileged user rights")
// #define KPST_MSG_UNREG_NOT_ADMIN_EN ((const unsigned char *)"Licence cancellation requires\nrights of privileged user")
// #define KPST_MSG_UNREG_NOT_ADMIN_EN ((const unsigned char *)"Licence cancellation requires\nrights of system administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_EN ((const unsigned char *)"Licence deactivation requires\nprivileged user rights")
// #define KPST_MSG_NOT_REG_EN         ((const unsigned char *)"Product licence not yet registered")
#define KPST_MSG_NOT_REG_EN         ((const unsigned char *)"Product licence not activated yet")
#define KPST_MSG_INVALID_REG_EN     ((const unsigned char *)"Licence codes of the update and the main product are different. Repeat installation of the product.")

// #define KPST_MSG_UNREG_KOD_1_EN     ((const unsigned char *)"Cancellation code")
#define KPST_MSG_UNREG_KOD_1_EN     ((const unsigned char *)"Deactivation code")
// #define KPST_MSG_UNREG_KOD_EN       ((const unsigned char *)"Licence cancellation code:              \n")
#define KPST_MSG_UNREG_KOD_EN       ((const unsigned char *)"Licence deactivation code:              \n")
#define KPST_MSG_ALLREADY_REMOVED_EN   ((const unsigned char *)"%s\n                                       \nProduct already removed")
// #define KPST_MSG_UNREG_SUCC_EN      ((const unsigned char *)"Licence registration cancelled successfully") 
#define KPST_MSG_UNREG_SUCC_EN      ((const unsigned char *)"Licence deactivated successfully") 
// #define KPST_MSG_UNREG_UNSUCC_EN    ((const unsigned char *)"Unsuccessful licence cancellation by Internet.")
#define KPST_MSG_UNREG_UNSUCC_EN    ((const unsigned char *)"Unsuccessful licence deactivation over the Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_EN  ((const unsigned char *)"Try to open following link using a browser.")

// #define KPST_MSG_REG_NOT_YET_EN     ((const unsigned char *)"Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command “Registration”.")
// #define KPST_MSG_REG_NOT_YET_EN     ((const unsigned char *)"Product licence not activated yet. Procedure of the activation should be proceeded using Start Menu command “Activate”.")
#define KPST_MSG_REG_NOT_YET_EN     ((const unsigned char *)"Product licence not activated yet. Procedure of the activation should be proceeded later.")

//#define KPST_MSG_INI_NOT_ADMIN_EN   ((const unsigned char *)"System resources inaccessible, login as privileged user")
#define KPST_MSG_INI_NOT_ADMIN_EN   ((const unsigned char *)"System resources inaccessible, login as system administrator")

// #define KPST_MSG_UNREG_PASTU_EN     ((const unsigned char *)"Cancellation code should be sent by e-mail, address tech@tev.lt or told")
#define KPST_MSG_UNREG_PASTU_EN     ((const unsigned char *)"Deactivation code should be sent by e-mail, address tech@tev.lt or told")
#define KPST_MSG_UNREG_DARBO_LAIKAS_EN ((const unsigned char *)"to the operator at working hours from 9 to 16 EET by phone, number")
#define KPST_MSG_UNREG_DIKT_TELEF_EN   ((const unsigned char *)"+370-5-2729318.")

#define KPST_MSG_UNREG_NEGALESIT_EN /* KPST_MSG_UNREG_TELEF_EN */ ((const unsigned char *)"Without doing it you will be unable to run the program on another computer!")

#define KPST_MSG_INSERT_FLOPPY_EN   ((const unsigned char *)"Insert floppy disk")
#define KPST_MSG_UNABLE_OPEN_REZFILE_EN   ((const unsigned char *)"Result file could not be opened.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_EN  ((const unsigned char *)"Result file could not be written.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_EN  ((const unsigned char *)"Result file could not be closed.")
#define KP_MSG_UNABLE_READ_WRITTEN_EN     ((const unsigned char *)"Written file could not be read.")
#define KPST_MSG_COULDNT_WRITE_EN   ((const unsigned char *)"Data could not be written.")
#define KPST_MSG_REFUSE_RESULTS_EN  ((const unsigned char *)"Are you sure you want to discard results?")
#define KPST_MSG_TEST_SUCC_EN       ((const unsigned char *)"Software of the test does work on this computer properly")

#define KPST_MSG_TEST_UNSUC_EN      ((const unsigned char *)"Results were not generated.\nPlease pack files of the folder c:\\arkim\\rezultatai to the archive and send it by e-mail, address tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_EN    ((const unsigned char *)"Insert USB flash drive with “")
#define KPST_MSG_INSERT_FLASH_1_EN  ((const unsigned char *)"”")

#define KPST_MSG_ENTER_PWD_EN       ((const unsigned char *)"Enter the password:")
#define KPST_MSG_BAD_PWD_EN         ((const unsigned char *)"Password incorrect")
#define KPST_MSG_ENTER_PUK_EN       ((const unsigned char *)"Enter the USB flash drive licence code:")
#define KPST_MSG_BAD_PUK_EN         ((const unsigned char *)"Licence code invalid")

// #define KPST_MSG_OBJ_REG_EN         ((const unsigned char *)"Document registration")
#define KPST_MSG_OBJ_REG_EN         ((const unsigned char *)"Document activation") // KPST_MSG_PROD_REG_EN
// #define KPST_MSG_OBJ_REG_INFO_EN    ((const unsigned char *)"Before using the document licence should be registered.")
#define KPST_MSG_OBJ_REG_INFO_EN    ((const unsigned char *)"Before using the document licence should be activated.") // KPST_MSG_REG_INFO_EN
// #define KPST_MSG_OBJ_UNREG_INFO_EN  ((const unsigned char *)"Licence registration should be cancelled before moving the document to another computer.") // KPST_MSG_UNREG_INFO_EN 
#define KPST_MSG_OBJ_UNREG_INFO_EN  ((const unsigned char *)"Licence should be deactivated before moving the document to another computer.") // KPST_MSG_UNREG_INFO_EN 
// #define KPST_MSG_OBJ_REG_PERSPEJ_EN ((const unsigned char *)"Registered document will open on this computer only!")
#define KPST_MSG_OBJ_REG_PERSPEJ_EN ((const unsigned char *)"Activated document will open on this computer only!") // KPST_MSG_REG_PERSPEJ_EN

// #define KPST_MSG_OBJ_REG_NOT_YET_EN     ((const unsigned char *)"Document registration canceled.")
#define KPST_MSG_OBJ_REG_NOT_YET_EN     ((const unsigned char *)"Document deactivated.") // KPST_MSG_REG_NOT_YET_EN
#define KPST_MSG_OBJ_UNREG_NEGALESIT_EN ((const unsigned char *)"Without doing it you will be unable to open the document on another computer!") // KPST_MSG_UNREG_NEGALESIT_EN

#define KPST_MSG_BAD_FLASH_EN       ((const unsigned char *)"This update is for USB flash drive licence %s")

#define KPST_MSG_LICENCE_EXPIRED_EN ((const unsigned char *)"%s\n                                       \nLicence expired")
#define KPST_MSG_REST_MONTHS_EN     ((const unsigned char *)"%s\n                                       \nLicence expires after %ld months")
#define KPST_MSG_REST_LAST_MONTH_EN ((const unsigned char *)"%s\n                                       \nLicence expires next month")
#define KPST_MSG_REST_DAYS_EN       ((const unsigned char *)"%s\n                                       \nLicence will expire after %ld days")
#define KPST_MSG_REST_DAY_EN        ((const unsigned char *)"%s\n                                       \nTomorow licence will expire")
#define KPST_MSG_REST_TODAY_EN      ((const unsigned char *)"%s\n                                       \nLicence expires today")
#define KPST_MSG_TIME_CHEAT_EN      ((const unsigned char *)"Set the system clock properly")

#define KPST_MSG_BAD_PRODVAR_EN     ((const unsigned char *)"You are using obsolete version of the product. Launch the product, press version check button „i“, download proposed update and install it, please.")

#define KPST_MSG_UPDATE_FINISHED_EN ((const unsigned char *)"       Press the „Finish“ button.         \n       Then launch the book MIKO.         ")

#define KPST_MSG_SELDOWN_TITLE_EN   ((const unsigned char *)"Download product components")
#define KPST_MSG_SELDOWN_PROMPT_EN  ((const unsigned char *)"The serial has new items issued.                             \n"\
                                                            "Uncheck items of the serial, you don't want to be downloaded:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_EN ((const unsigned char *)"Don't check new items of the serial in the future:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_EN ((const unsigned char *)"Press “OK” to download selected items,             \n"\
                                                               "“Cancel” – to proceed using items you already have.")

#define KPST_MSG_SELUPD_TITLE_EN   ((const unsigned char *)"Download product updates")
#define KPST_MSG_SELUPD_PROMPT_EN  ((const unsigned char *)"For the product you have there are updates issued.\n"\
                                                           "Uncheck updates, you don't want to be downloaded: ")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_EN ((const unsigned char *)"Don't check updates of the product in the future:")
#define KPST_MSG_SELUPD_BUT_PROMPT_EN ((const unsigned char *)"Press “OK” to download selected items,\n"\
                                                              "“Cancel” – otherwise.                 ")
#define KPST_MSG_CLOSE_PROG_WND_EN ((const unsigned char *)"To continue with installation of the update, close the program „%s“, please")

#endif // #if ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#endif // #ifndef kpstmsg_en_included
