// -----------------------------------------
// StartSel_ru.h
// Keliш programш paleidimas iр meniu
// pranesimai rusш k.
//


#ifndef StartSel_ru_included
#define StartSel_ru_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#define STARTSEL_MSG_NOT_ADMIN_RU ((const unsigned char *)"Для этой операции необходимо подключиться администратором.")
#define STARTSEL_MSG_SURE_RESTORING_RU ((const unsigned char *)"Будут отменены все Ваши изменения, удалены все файлы из каталогов «Mano_...» и уничтожены данные пользователя.\n \nВы согласны?")
#define STARTSEL_MSG_RESTORING_RU ((const unsigned char *)"Восстанавливается файл...")
#define STARTSEL_MSG_RESTORING_FILE_RU ((const unsigned char *)"Восстанавливается файл %s.%s...")
#define STARTSEL_MSG_RESTORED_RU ((const unsigned char *)"Изначальные данные успешно восстановлены.")
#define STARTSEL_MSG_ARC_EXIST_RU ((const unsigned char *)"Резервная копия, записанная %02d.%02d.%04d, уже имеется. Желаете её перезаписать?")
#define STARTSEL_MSG_ARC_CREATED_RU ((const unsigned char *)"Файлы пользователя успешно перекопированы из флэш-накопителя в %s.")
#define STARTSEL_MSG_LOW_DISK_SPACE_RU ((const unsigned char *)"Копирование файла не удалось, проверьте наличие свободного места на диске %s.")
#define STARTSEL_MSG_DIR_ACCESS_ERROR_RU ((const unsigned char *)"Создание каталога не удалось, проверьте права записи на %s.")
#define STARTSEL_MSG_NO_ARC_RU ((const unsigned char *)"В этом компьютере резервная копия флэш-накопителя ещё не создана.")
#define STARTSEL_MSG_ARC_FOUND_RU ((const unsigned char *)"Желаете восстановить резервную копию от %02d.%02d.%04d? Все последующие изменения в флэш-накопителе будут потеряны.")
#define STARTSEL_MSG_ARC_RESTORED_RU ((const unsigned char *)"Резервная копия успешно восстановлена.")
#define STARTSEL_MSG_LOW_FLASH_SPACE_RU ((const unsigned char *)"Копирование файла не удалось, проверьте наличие свободного места в флэш-накопителе.")
#define STARTSEL_MSG_FLASH_ACCESS_ERROR_RU ((const unsigned char *)"Создание каталога не удалось, проверьте права записи в флэш-накопитель. ")
#define STARTSEL_MSG_RECOMEND_TO_CLOSE_MIKO_RU ((const unsigned char *)"Закройте все окна книги MIKO.")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#endif // #ifndef StartSel_ru_included
