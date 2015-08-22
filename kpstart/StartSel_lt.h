// -----------------------------------------
// StartSel_lt.h
// Keliø programø paleidimas ið meniu
// pranesimai lietuviu k.
//


#ifndef StartSel_lt_included
#define StartSel_lt_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#define STARTSEL_MSG_NOT_ADMIN_LT ((const unsigned char *)"Ðiam veiksmui turite bûti prisijungæs administratorium.")
// #define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"Ar tikrai norite panaikinti visus pakeitimus?")
// #define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"Bus panaikinti visi Jûsø padaryti pakeitimai ir iðtrinti visi aplankø Mano_... failai.\n \nAr sutinkate?")
#define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"Bus panaikinti visi Jûsø padaryti pakeitimai, iðtrinti visi aplankø „Mano_...“ failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING_LT ((const unsigned char *)"Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE_LT ((const unsigned char *)"Atstatomas failas %s.%s...")
// #define STARTSEL_MSG_SAVING_LT ((const unsigned char *)"Iðsaugojamas failas...")
// #define STARTSEL_MSG_SAVING_FILE_LT (/* (const unsigned char *) */ "Iðsaugojamas failas %s...")
#define STARTSEL_MSG_RESTORED_LT ((const unsigned char *)"Pradiniai duomenys sëkmingai atstatyti.")
// #define STARTSEL_MSG_ARC_EXIST_LT (/* (const unsigned char *) */ "Jau yra atsarginë kopija, iðsaugota %04d.%02d.%02d. Ar norite jà perraðyti?")
#define STARTSEL_MSG_ARC_EXIST_LT ((const unsigned char *)"Atsarginë kopija, áraðyta %04d-%02d-%02d, jau yra. Ar norite jà pakeisti?")
#define STARTSEL_MSG_ARC_CREATED_LT ((const unsigned char *)"Naudotojo failai sëkmingai nukopijuoti ið atmintuko á %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_LT ((const unsigned char *)"Nepavyko nukopijuoti failo, patikrinkite, ar diske %s uþtenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_LT ((const unsigned char *)"Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos %s raðymo teisës.")
// #define STARTSEL_MSG_NO_ARC_LT ((const unsigned char *)"Atmintuko atsarginës kopijos dar nëra.")
#define STARTSEL_MSG_NO_ARC_LT ((const unsigned char *)"Atmintuko atsarginës kopijos ðiame kompiuteryje nëra.")
// #define STARTSEL_MSG_ARC_FOUND_LT (/* (const unsigned char *) */ "Ar norite atstatyti %04d.%02d.%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_FOUND_LT ((const unsigned char *)"Ar norite atstatyti %04d-%02d-%02d sukurtà kopijà? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED_LT ((const unsigned char *)"Atsarginë kopija sëkmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_LT ((const unsigned char *)"Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke uþtenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_LT ((const unsigned char *)"Nepavyko sukurti aplanko, patikrinkite, ar neuþdraustos raðymo á atmintukà teisës.")
// #define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"Jei ðiuo metu naudojatës MIKO knyga ir jos langas aktyvus, uþverkite já.")
// #define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"Uþverkite visus MIKO knygos failus.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"Uþverkite MIKO knygos failà, jei jis ðiuo metu atviras.")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef StartSel_lt_included
