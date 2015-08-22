// -----------------------------------------
// StartSel_lt.h
// Keli� program� paleidimas i� meniu
// pranesimai lietuviu k.
//


#ifndef StartSel_lt_included
#define StartSel_lt_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#define STARTSEL_MSG_NOT_ADMIN_LT ((const unsigned char *)"�iam veiksmui turite b�ti prisijung�s administratorium.")
// #define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"Ar tikrai norite panaikinti visus pakeitimus?")
// #define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"Bus panaikinti visi J�s� padaryti pakeitimai ir i�trinti visi aplank� Mano_... failai.\n \nAr sutinkate?")
#define STARTSEL_MSG_SURE_RESTORING_LT ((const unsigned char *)"Bus panaikinti visi J�s� padaryti pakeitimai, i�trinti visi aplank� �Mano_...� failai ir naudotojo duomenys.\n \nAr sutinkate?")
#define STARTSEL_MSG_RESTORING_LT ((const unsigned char *)"Atstatomas failas...")
#define STARTSEL_MSG_RESTORING_FILE_LT ((const unsigned char *)"Atstatomas failas %s.%s...")
// #define STARTSEL_MSG_SAVING_LT ((const unsigned char *)"I�saugojamas failas...")
// #define STARTSEL_MSG_SAVING_FILE_LT (/* (const unsigned char *) */ "I�saugojamas failas %s...")
#define STARTSEL_MSG_RESTORED_LT ((const unsigned char *)"Pradiniai duomenys s�kmingai atstatyti.")
// #define STARTSEL_MSG_ARC_EXIST_LT (/* (const unsigned char *) */ "Jau yra atsargin� kopija, i�saugota %04d.%02d.%02d. Ar norite j� perra�yti?")
#define STARTSEL_MSG_ARC_EXIST_LT ((const unsigned char *)"Atsargin� kopija, �ra�yta %04d-%02d-%02d, jau yra. Ar norite j� pakeisti?")
#define STARTSEL_MSG_ARC_CREATED_LT ((const unsigned char *)"Naudotojo failai s�kmingai nukopijuoti i� atmintuko � %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_LT ((const unsigned char *)"Nepavyko nukopijuoti failo, patikrinkite, ar diske %s u�tenka vietos.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_LT ((const unsigned char *)"Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos %s ra�ymo teis�s.")
// #define STARTSEL_MSG_NO_ARC_LT ((const unsigned char *)"Atmintuko atsargin�s kopijos dar n�ra.")
#define STARTSEL_MSG_NO_ARC_LT ((const unsigned char *)"Atmintuko atsargin�s kopijos �iame kompiuteryje n�ra.")
// #define STARTSEL_MSG_ARC_FOUND_LT (/* (const unsigned char *) */ "Ar norite atstatyti %04d.%02d.%02d sukurt� kopij�? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_FOUND_LT ((const unsigned char *)"Ar norite atstatyti %04d-%02d-%02d sukurt� kopij�? Visi po to atmintuke padaryti pakeitimai bus panaikinti.")
#define STARTSEL_MSG_ARC_RESTORED_LT ((const unsigned char *)"Atsargin� kopija s�kmingai atstatyta.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_LT ((const unsigned char *)"Nepavyko nukopijuoti failo, patikrinkite, ar atmintuke u�tenka vietos.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_LT ((const unsigned char *)"Nepavyko sukurti aplanko, patikrinkite, ar neu�draustos ra�ymo � atmintuk� teis�s.")
// #define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"Jei �iuo metu naudojat�s MIKO knyga ir jos langas aktyvus, u�verkite j�.")
// #define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"U�verkite visus MIKO knygos failus.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_LT ((const unsigned char *)"U�verkite MIKO knygos fail�, jei jis �iuo metu atviras.")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef StartSel_lt_included
