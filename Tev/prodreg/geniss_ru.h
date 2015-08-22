// ===================================================
// geniss_ru.cpp
// Inno Setup scriptu generatorius
// rusiрki praneрimai
//


#ifndef geniss_ru_included
#define geniss_ru_included

#if TRUE // ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#define GENISS_MSG_START_PROG_RU          ((const unsigned char *)"Запустить программу") 
#define GENISS_MSG_UNSUCC_START_RU        ((const unsigned char *)"Неудачная попытка запустить файл")
#define GENISS_MSG_PROG_NOT_ISTALLED_RU   ((const unsigned char *)"Программа «\' + GetFirstVerName + \'» в этом компьютере ещё не установлена")
#define GENISS_MSG_UPD_NOT_ISTALLED_RU    ((const unsigned char *) /* update */ "«\' + GetPrevVerName + \'» в компьютере ещё не установлено")

#define GENISS_MSG_RESTART_ADMIN_RU       ((const unsigned char *)"запустите программу ещё раз, зарегистрировавшись администратором системы")
#define GENISS_MSG_INST_ADMIN_RU          ((const unsigned char *)"Для установки необходимы права администратора системы")
#define GENISS_MSG_UNINST_ADMIN_RU        ((const unsigned char *)"Для удалении программы необходимы права администратора системы")

#define GENISS_MSG_FLASH_PLAYER_RU        ((const unsigned char *)"Сейчас будет установлен Macromedia Flash плеер. Следуйте указаниям программы установки плеера.")
#define GENISS_MSG_CABRI_RU               ((const unsigned char *)"Сейчас будет установлен Cabri 3D плагин. Следуйте указаниям программы установки плагина.")

#define GENISS_MSG_NAT_LET_RU             ((const unsigned char *)"Буквы национального альфавита в именах файлов могут быть использованы лишь в случае правильных региональных установок Вашей ОС Windows.\'+Chr(10)+Chr(10)+\'Желаете ли Вы использовать национальный альфавит в именах файлов?")

#define GENISS_MSG_ATM_KOD_TIT_RU         ((const unsigned char *)"Лицензионный код USB-флеш-накопителя")
#define GENISS_MSG_ATM_KOD_MAIN_RU        ((const unsigned char *)"Введите лицензионный код USB-флеш-накопителя.")
#define GENISS_MSG_ATM_KOD_PROMPT_RU      GENISS_MSG_ATM_KOD_TIT_RU

#define GENISS_MSG_CHK_UPD_TIT_RU         ((const unsigned char *)"Автоматическая проверка обновлений")
#define GENISS_MSG_CHK_UPD_MAIN_RU        ((const unsigned char *)"Очистите флажок, если Вы не желаете автоматической проверки обновлений по Интернету.")
#define GENISS_MSG_CHK_UPD_PROMPT_RU      GENISS_MSG_CHK_UPD_TIT_RU
    
// produktш pavadinimш priesagos
#define GENISS_PROD_FLASH_RU              ((const unsigned char *)"на USB-флеш-накопителе") // atmintukinл produkto versija
#define GENISS_PROD_LAN_RU                ((const unsigned char *)"сетевая") // tinklinл produkto versija
#define GENISS_PROD_SERVER_RU             ((const unsigned char *)"сервер") // produkto duomenш/licencijш serveris LAN-e   
 
// ikonш/katalogш pavadinimai ir jш priesagos
#define GENISS_LINK_OPTIONS_RU            ((const unsigned char *)"Установки")
// #define GENISS_LINK_REG_RU                ((const unsigned char *)"Регистрация")
#define GENISS_LINK_REG_RU                ((const unsigned char *)"Активация")
#define GENISS_LINK_UNREG_RU              ((const unsigned char *)"Удаление")
#define GENISS_LINK_FLASH_RU              GENISS_PROD_FLASH_RU
#define GENISS_LINK_FLASH_CHK_RU          ((const unsigned char *)"проверка USB-флеш-накопителя")
#define GENISS_LINK_LAN_RU                GENISS_PROD_LAN_RU
#define GENISS_LINK_SERVER_RU             GENISS_PROD_SERVER_RU
#define GENISS_LINK_SERVER_MANAGEMENT_RU  ((const unsigned char *)"Управление сервером")
#define GENISS_LINK_CLEAN_NAT_RU          ((const unsigned char *)"Удаление старых результатов")
#define GENISS_LINK_CLEAN_LAT_RU          GENISS_LINK_CLEAN_NAT_RU

#define GENISS_INSERT_FLASH_KEY_RU        ((const unsigned char *)"Вставьте USB-флеш-накопитель с программой ")

#define GENISS_LINK_DIAG_MSG_NAT_RU       ((const unsigned char *)"Посылка диагностического сообщения")
#define GENISS_LINK_DIAG_MSG_LAT_RU       ((const unsigned char *)"Send error report")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#endif // #ifndef geniss_ru_included
