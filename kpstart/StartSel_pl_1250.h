// -----------------------------------------
// StartSel_pl_1250.h
// Keli? program? paleidimas i� meniu
// pranesimai lenku k. Central European
//


#ifndef StartSel_pl_1250_included
#define StartSel_pl_1250_included

#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1250_p))

#define STARTSEL_MSG_NOT_ADMIN_PL_1250 ((const unsigned char *)"Do wykonania tej czynno�ci musisz zalogowa� si� do systemu jako administrator.")
#define STARTSEL_MSG_SURE_RESTORING_PL_1250 ((const unsigned char *)"Wszystkie dokonane zmiany b�d� usuni�te, wykasowane wszystkie pliki z katalogu �Mano_...� i dane u�ytkownika.\n \nCzy wyra�asz na to zgod�?")
#define STARTSEL_MSG_RESTORING_PL_1250 ((const unsigned char *)"Przywracanie pliku...")
#define STARTSEL_MSG_RESTORING_FILE_PL_1250 ((const unsigned char *)"Przywracanie pliku %s.%s...")
#define STARTSEL_MSG_RESTORED_PL_1250 ((const unsigned char *)"Przywr�cono pierwotne dane.")
#define STARTSEL_MSG_ARC_EXIST_PL_1250 ((const unsigned char *)"Zapasowa kopia, zapisana %02d.%02d.%04d, ju� istnieje. Czy chcesz j� zamieni�?")
#define STARTSEL_MSG_ARC_CREATED_PL_1250 ((const unsigned char *)"Pliki u�ytkownika skopiowano z no�nika USB na %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_PL_1250 ((const unsigned char *)"Nie uda�o si� skopiowa� pliku. Sprawd� czy na dysku %s jest wystarczaj�co miejsca.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_PL_1250 ((const unsigned char *)"Nie uda�o si� stworzy� katalogu. Sprawd�, czy plik %s ma prawo zapisywania.")
#define STARTSEL_MSG_NO_ARC_PL_1250 ((const unsigned char *)"Na tym komputerze nie ma zapasowej kopii ksi��ki MIKO.")
#define STARTSEL_MSG_ARC_FOUND_PL_1250 ((const unsigned char *)"Czy chcesz przywr�ci� kopi� stworzon� %02d.%02d.%04d? Wszystkie zmiany dokonane po tej dacie, b�d� usuni�te.")
#define STARTSEL_MSG_ARC_RESTORED_PL_1250 ((const unsigned char *)"Przywr�cono zapasow� kopi�.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_PL_1250 ((const unsigned char *)"Nie uda�o si� skopiowa� pliku. Sprawd� czy na no�niku USB jest wystarczaj�co miejsca na kopi�.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_PL_1250 ((const unsigned char *)"Nie uda�o si� stworzy� katalogu. Sprawd�, czy na no�niku USB nie s� zabronione prawa zapisywania.")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_PL_1250 ((const unsigned char *)"Zamknij wszystkie pliki ksi��ki MIKO.")

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1250_p))

#endif // #ifndef StartSel_pl_1250_included
