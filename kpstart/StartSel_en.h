// -----------------------------------------
// StartSel_en.h
// Keliø programø paleidimas ið meniu
// pranesimai anglu k.
//


#ifndef StartSel_en_included
#define StartSel_en_included

#if TRUE // ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#define STARTSEL_MSG_NOT_ADMIN_EN ((const unsigned char *)"For this function you should be logged as privileged user.")
#define STARTSEL_MSG_SURE_RESTORING_EN ((const unsigned char *)"All your changes will be lost, all files of the folders “Mano_...” and user data will be destroyed.\n \nAre you sure?")
#define STARTSEL_MSG_RESTORING_EN ((const unsigned char *)"Restoring file...")
#define STARTSEL_MSG_RESTORING_FILE_EN ((const unsigned char *) "Restoring file %s.%s...")
#define STARTSEL_MSG_RESTORED_EN ((const unsigned char *)"Initial data successfully restored.")
#define STARTSEL_MSG_ARC_EXIST_EN ((const unsigned char *)"Reserve copy, created %02d.%02d.%04d, already exists. Do you want to overwrite it?")
#define STARTSEL_MSG_ARC_CREATED_EN ((const unsigned char *)"User files successfully copied from USB flash drive to %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_EN ((const unsigned char *)"Unable to copy a file, check free space available on disk %s.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_EN ((const unsigned char *)"Unable to create a folder, check writing access rights to %s.")
#define STARTSEL_MSG_NO_ARC_EN ((const unsigned char *)"Reserve copy of USB flash drive was not found on this computer.")
#define STARTSEL_MSG_ARC_FOUND_EN ((const unsigned char *)"Do you want to restore copy from %02d.%02d.%04d? All later changes to the USB flash drive will be lost.")
#define STARTSEL_MSG_ARC_RESTORED_EN ((const unsigned char *) "Reserve copy successfully restored.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_EN ((const unsigned char *)"Unable to copy a file, check free space available on the USB flash drive.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_EN ((const unsigned char *)"Unable to create a folder, check writing access rights to the USB flash drive.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_EN ((const unsigned char *)"Close all files of the MIKO book.")

#endif // #if ((MsgLang == KpLangNo_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangEn_p))

#endif // #ifndef StartSel_en_included
