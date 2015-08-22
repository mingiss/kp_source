// -----------------------------------------
// kpstmsg_ru.h
// programos paleidimo aplikaciju pranesimai
// rusu kalba
// 

#ifndef kpstmsg_ru_included
#define kpstmsg_ru_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

// #define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"Регистрация программы")
// #define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"Регистрация продукта")
#define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"Активация продукта")

// #define KPST_MSG_UNREG_RU           ((const unsigned char *)"Прекращение регистрации")
#define KPST_MSG_UNREG_RU           ((const unsigned char *)"Прекращение активации")
#define KPST_MSG_LIC_RU             ((const unsigned char *)"Лицензия")

// #define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"Для работы программы необходима регистрация лицензии.")
// #define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"Для работы продукта необходима регистрация лицензии.")
#define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"Для работы продукта необходима активация лицензии.")

#define KPST_MSG_IVESK_LIC_RU       ((const unsigned char *)"Введите код лицензии, который Вы получили вместе с продуктом.")
#define KPST_MSG_IVESK_LIC_1_RU     ((const unsigned char *)"(Весь код можно копировать в первую клетку.)")
#define KPST_MSG_REG_CARD_RU        ((const unsigned char *)"")
#define KPST_MSG_LIC_KOD_RU         ((const unsigned char *)"Код лицензии:")
#define KPST_MSG_BLOGAS_LIC_KODAS_RU   ((const unsigned char *)"Ошибочный код лицензии")

// #define KPST_MSG_CHECK_CONN_RU      ((const unsigned char *)"Проверьте связь Вашего компьютера с Интернетом")
#define KPST_MSG_CHECK_CONN_RU      KP_MSG_FIREWALL_RU
// #define KPST_MSG_CHECK_CONN_LOC_RU  ((const unsigned char *)"Проверьте связь Вашего компьютера с компьютерной сетью")
#define KPST_MSG_CHECK_CONN_LOC_RU  ((const unsigned char *)"Доступ к локальной компьютерной сети заблокирован. Проверьте установки Вашего сетевого экрана (firewall) – попробуйте включить %s в список программ, которым дозволен доступ к интернету.")

// #define KPST_MSG_REG_SUCC_RU        ((const unsigned char *)"%s\n                                       \nРегистрация лицензии прошла успешно") 
#define KPST_MSG_REG_SUCC_RU        ((const unsigned char *)"%s\n                                       \nАктивация лицензии прошла успешно") 
// #define KPST_MSG_ALLREADY_REG_RU    ((const unsigned char *)"%s\n                                       \nЛицензия уже зарегистрирована") 
#define KPST_MSG_ALLREADY_REG_RU    ((const unsigned char *)"%s\n                                       \nЛицензия уже активирована") 
// #define KPST_MSG_REG_UNSUC_RU       ((const unsigned char *)"Неудачная попытка регистрации лицензии по Интернету.")
#define KPST_MSG_REG_UNSUC_RU       ((const unsigned char *)"Неудачная попытка активации лицензии по Интернету.")
#define KPST_MSG_REG_UNSUC_0_RU     ((const unsigned char *)"Попробуйте браузером открыть следующий адрес,")
#define KPST_MSG_REG_UNSUC_1_RU     ((const unsigned char *)"а полученный ответ вкопировать в клетки ключа инсталляции.")

// #define KPST_MSG_REG_UNSUC_LOC_RU   ((const unsigned char *)"Неудачная попытка регистрации.")
#define KPST_MSG_REG_UNSUC_LOC_RU   ((const unsigned char *)"Неудачная попытка активации.")
#define KPST_MSG_DIEG_KOD_RU        ((const unsigned char *)"Код инсталляции:")

// #define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"Регистрация лицензии должна быть отменена перед использованием программы на другом компьютере.")
// #define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"Регистрация лицензии отменяется перед переносом программы на другой компьютер.")
// #define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"Регистрация лицензии отменяется перед переносом продукта на другой компьютер.")
#define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"Лицензия деактивируется перед переносом продукта на другой компьютер.")

#define KPST_MSG_UNREG_IVESK_LIC_RU KPST_MSG_IVESK_LIC_RU

// #define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"Зарегистрированная программа будет работать только на этом компьютере!")
// #define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"Зарегистрированный продукт будет работать только на этом компьютере!")
#define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"Активированный продукт будет работать только на этом компьютере!")

// #define KPST_MSG_BUT_REG_RU         ((const unsigned char *)"Как будете регистрировать?")
#define KPST_MSG_BUT_REG_RU         ((const unsigned char *)"Как будете активировать?")
// #define KPST_MSG_BUT_UNREG_RU       ((const unsigned char *)"Как будете прекращать регистрацию?")
#define KPST_MSG_BUT_UNREG_RU       ((const unsigned char *)"Как будете деактивировать продукт?")

#define KPST_MSG_INTERNETU_RU       ((const unsigned char *)"По Интернету")
#define KPST_MSG_TELEFONU_RU        ((const unsigned char *)"По телефону")
#define KPST_MSG_CANCEL_REG_RU      ((const unsigned char *)"Отмена")
// #define KPST_MSG_CANCEL_UNREG_RU    ((const unsigned char *)"Не отменять")
#define KPST_MSG_CANCEL_UNREG_RU    ((const unsigned char *)"Отмена")

#define KPST_MSG_SIUSK_PASTU_RU     ((const unsigned char *)"Код инсталляции должен быть выслан по электронной почте,")
#define KPST_MSG_DARBO_LAIKAS_RU    ((const unsigned char *)"адрес tech@tev.lt, или продиктован оператору в рабочее время")
#define KPST_MSG_DIKT_TELEF_RU      ((const unsigned char *)"с 9 до 16 часов EET по телефону, номер +370-5-2729318.")

#define KPST_MSG_IVESK_RAKTA_RU     ((const unsigned char *)"Введите полученный ответ – ключ инсталляции.")
#define KPST_MSG_IVESK_RAKTA_1_RU   ((const unsigned char *)"(Весь ключ можно копировать в первую клетку.)")
#define KPST_MSG_DIEG_RAKTAS_RU     ((const unsigned char *)"Ключ инсталляции:")
#define KPST_MSG_DIEG_RAKTAS_1_RU   ((const unsigned char *)"Ключ инсталляции")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_RU ((const unsigned char *)"Ошибочный ключ инсталляции")
#define KPST_MSG_START_FROM_CD_RU   ((const unsigned char *)"Программу запускайте прямо из компакт-диска")
#define KPST_MSG_BAD_CD_RU          ((const unsigned char *)"Плохой компакт-диск")

#define KPST_MSG_REZ_NESUFORM_RU    ((const unsigned char *)"Генерация результатов неуспешна.\nЗа технической помощью обращайтесь по электронной почте, адрес tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_RU    ((const unsigned char *)"Результаты не найдены.\nЗа технической помощью обращайтесь по электронной почте, адрес tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_2_RU    ((const unsigned char *)" Результаты не найдены.\nВы являетесь пользователем %s, ОС %s.\nПопробуйте зарегистрироваться администратором системы.")
#define KPST_MSG_REZ_SUCCESS_RU     ((const unsigned char *)". Результаты успешно перенесены в ")

// #define KPST_MSG_REG_NOT_ADMIN_RU   ((const unsigned char *)"Для регистрации лицензии необходимы права администратора системы")
#define KPST_MSG_REG_NOT_ADMIN_RU   ((const unsigned char *)"Для активации лицензии необходимы права администратора системы")
// #define KPST_MSG_UNREG_NOT_ADMIN_RU ((const unsigned char *)"Для отмены регистрации лицензии необходимы права администратора системы")
#define KPST_MSG_UNREG_NOT_ADMIN_RU ((const unsigned char *)"Для деактивации лицензии необходимы права администратора системы")
// #define KPST_MSG_NOT_REG_RU         ((const unsigned char *)"Лицензия продукта ещё не зарегистрирована")
#define KPST_MSG_NOT_REG_RU         ((const unsigned char *)"Лицензия продукта ещё не активирована")
#define KPST_MSG_INVALID_REG_RU     ((const unsigned char *)"Лицензионные коды обновления и обновляемого продукта отличаются. Повторите установку продукта.")

// #define KPST_MSG_UNREG_KOD_1_RU     ((const unsigned char *)"Код отмены")
#define KPST_MSG_UNREG_KOD_1_RU     ((const unsigned char *)"Код деактивации")
// #define KPST_MSG_UNREG_KOD_RU       ((const unsigned char *)"Код отмены лицензии:                    \n")
#define KPST_MSG_UNREG_KOD_RU       ((const unsigned char *)"Код деактивации лицензии:                    \n")
#define KPST_MSG_ALLREADY_REMOVED_RU   ((const unsigned char *)"%s\n                                       \nПродукт уже удалён")
// #define KPST_MSG_UNREG_SUCC_RU      ((const unsigned char *)"Регистрация лицензии отменена успешно") 
#define KPST_MSG_UNREG_SUCC_RU      ((const unsigned char *)"Лицензия успешно деактивирована") 
// #define KPST_MSG_UNREG_UNSUCC_RU    ((const unsigned char *)"Неудачная попытка отменить регистрацию по Интернету.")
#define KPST_MSG_UNREG_UNSUCC_RU    ((const unsigned char *)"Неудачная попытка деактивации лиценции по Интернету.")
#define KPST_MSG_UNREG_UNSUCC_1_RU   ((const unsigned char *)" Попробуйте браузером открыть следующий адрес.")

// #define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"Лицензия продукта еще не зарегистрирована. Процедура регистрации должна быть продолжена вызовом комманды меню «Регистрация».")
// #define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"Лицензия продукта еще не активирована. Процедура активации должна быть продолжена вызовом комманды меню «Активация».")
#define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"Лицензия продукта еще не активирована. Процедура активации будет продолжена при следующем запуске.")

// #define KPST_MSG_REG_NOT_YET_RU_0   ((const unsigned char *)"Лицензия продукта еще не зарегистрирована. Процедура регистрации должна быть продолжена вызовом комманды меню «Registration».")
// #define KPST_MSG_REG_NOT_YET_RU_0   ((const unsigned char *)"Лицензия продукта еще не активирована. Процедура активации должна быть продолжена вызовом комманды меню «Activation».")
#define KPST_MSG_REG_NOT_YET_RU_0   KPST_MSG_REG_NOT_YET_RU

#define KPST_MSG_INI_NOT_ADMIN_RU   ((const unsigned char *)"Ресурсы системы недоступны, зарегистрируйтесь администратором")

// #define KPST_MSG_UNREG_PASTU_RU        ((const unsigned char *)"Код отмены должен быть выслан по электронной почте,")
#define KPST_MSG_UNREG_PASTU_RU        ((const unsigned char *)"Код деактивации должен быть выслан по электронной почте,")
#define KPST_MSG_UNREG_DARBO_LAIKAS_RU ((const unsigned char *)"адрес tech@tev.lt, или продиктован оператору в рабочее время")
#define KPST_MSG_UNREG_DIKT_TELEF_RU   ((const unsigned char *)"с 9 до 16 часов EET по телефону, номер +370-5-2729318.")

//#define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"Не выполнив этой процедуры, программу не сможете запустить на другом компьютере!")
// #define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"Не выполнив этого, программа на другом компьютере не запустится!")
#define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"Не выполнив этого, продукт на другом компьютере работать не будет!")

#define KPST_MSG_INSERT_FLOPPY_RU   ((const unsigned char *)"Вставьте гибкий диск")
#define KPST_MSG_UNABLE_OPEN_REZFILE_RU   ((const unsigned char *)"Не удалось открыть Файл с результатами.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_RU  ((const unsigned char *)"Не удалось записать Файл с результатами.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_RU  ((const unsigned char *)"Не удалось закрыть Файл с результатами.")
#define KP_MSG_UNABLE_READ_WRITTEN_RU     ((const unsigned char *)"Не удалось прочесть записанный файл.")
#define KPST_MSG_COULDNT_WRITE_RU   ((const unsigned char *)"Не удалось записать данные.")
#define KPST_MSG_REFUSE_RESULTS_RU  ((const unsigned char *)"Вы уверены в том, что хотите отказаться от результатов?")
#define KPST_MSG_TEST_SUCC_RU       ((const unsigned char *)"Тестовая программа на этом компьютере прошла успешно")

#define KPST_MSG_TEST_UNSUC_RU      ((const unsigned char *)"Результаты несформированы.\nСархивируйте, пожалуйста, файлы из каталога c:\\arkim\\rezultatai и вышлите по электронной почте, адрес tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_RU    ((const unsigned char *)"Вставьте USB-флеш-накопитель с «")
#define KPST_MSG_INSERT_FLASH_1_RU  ((const unsigned char *)"»")

#define KPST_MSG_ENTER_PWD_RU       ((const unsigned char *)"Введите пароль:")
#define KPST_MSG_BAD_PWD_RU         ((const unsigned char *)"Ошибка в пароли")
#define KPST_MSG_ENTER_PUK_RU       ((const unsigned char *)"Введите лицанзионный код USB-флеш-накопителя:")
#define KPST_MSG_BAD_PUK_RU         ((const unsigned char *)"Ошибочный код лицензии")

// #define KPST_MSG_OBJ_REG_RU         ((const unsigned char *)"Регистрация документа")
#define KPST_MSG_OBJ_REG_RU         ((const unsigned char *)"Активация документа")
// #define KPST_MSG_OBJ_REG_INFO_RU    ((const unsigned char *)"Перед использованием документа необходима регистрация лицензии.")
#define KPST_MSG_OBJ_REG_INFO_RU    ((const unsigned char *)"Перед использованием документа необходима активация лицензии.")
// #define KPST_MSG_OBJ_UNREG_INFO_RU  ((const unsigned char *)"Регистрация лицензии должна быть отменена перед использованием документа на другом компьютере.")
#define KPST_MSG_OBJ_UNREG_INFO_RU  ((const unsigned char *)"Лицензия должна быть деактивирована перед использованием документа на другом компьютере.")
// #define KPST_MSG_OBJ_REG_PERSPEJ_RU ((const unsigned char *)"Зарегистрированный документ будет открываться только на этом компьютере!")
#define KPST_MSG_OBJ_REG_PERSPEJ_RU ((const unsigned char *)"Активированный документ будет открываться только на этом компьютере!")

// #define KPST_MSG_OBJ_REG_NOT_YET_RU     ((const unsigned char *)"Регистрация документа отменена.")
#define KPST_MSG_OBJ_REG_NOT_YET_RU     ((const unsigned char *)"Документ деактивирован.")
#define KPST_MSG_OBJ_UNREG_NEGALESIT_RU ((const unsigned char *)"Не выполнив этой процедуры, на другом компьютере документ открываться не будет!")

#define KPST_MSG_BAD_FLASH_RU ((const unsigned char *)"Это обновление предназначено для USB-флеш-накопителя %s")

#define KPST_MSG_LICENCE_EXPIRED_RU ((const unsigned char *)"%s\n                                       \nСрок действия лицензии кончился")
#define KPST_MSG_REST_MONTHS_RU     ((const unsigned char *)"%s\n                                       \nСрок действия лицензии кончится после %d месяцев")
#define KPST_MSG_REST_LAST_MONTH_RU ((const unsigned char *)"%s\n                                       \nСрок действия лицензии истекает в следующем месяце")
#define KPST_MSG_REST_DAYS_RU       ((const unsigned char *)"%s\n                                       \nСрок действия лицензии кончится после %d дней")
#define KPST_MSG_REST_DAY_RU        ((const unsigned char *)"%s\n                                       \nСрок действия лицензии истекает завтра")
#define KPST_MSG_REST_TODAY_RU      ((const unsigned char *)"%s\n                                       \nСрок действия лицензии истекает сегодня")
#define KPST_MSG_TIME_CHEAT_RU      ((const unsigned char *)"Правильно установьте системные часы компьютера")

#define KPST_MSG_BAD_PRODVAR_RU     ((const unsigned char *)"Вы пользуетесь устаревшей версией продукта. Запустите продукт, нажмите кнопку проверки версии «i», скачайте предложеное обновление и его запустите.")

#define KPST_MSG_UPDATE_FINISHED_RU ((const unsigned char *)"         Нажмите кнопку «Закончить».           \n     После этого запустите книгу MIKO.       ")

// #define KPST_MSG_SELDOWN_TITLE_RU   ((const unsigned char *)"Загрузка компонентов продукта")
#define KPST_MSG_SELDOWN_TITLE_RU   ((const unsigned char *)"Загрузка частей серийного издания")
#define KPST_MSG_SELDOWN_PROMPT_RU  ((const unsigned char *)"У серийного издания появились новые части.\nУдалите галочки у тех из них, которых загрузить не желаете:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_RU ((const unsigned char *)"Появления новых частей серийного издания больше не проверять:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_RU ((const unsigned char *)"Для загрузки отмеченных новых частей нажмите «Хорошо»,\nдля пересмотра только уже имеющихся – «Отменить».")

#define KPST_MSG_SELUPD_TITLE_RU   ((const unsigned char *)"Загрузка обновлений продукта")
#define KPST_MSG_SELUPD_PROMPT_RU  ((const unsigned char *)"У продукта есть обновления.                       \n"\
                                                           "Удалите галочки у тех из них, которых загрузить не желаете:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_RU ((const unsigned char *)"Обновлений продукта в будущем не проверять:")
#define KPST_MSG_SELUPD_BUT_PROMPT_RU ((const unsigned char *)"Если желаете загрузить отмеченные обновления, щелкните кнопку «Хорошо»,\n"\
                                                              "если нет – «Отменить».                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_RU ((const unsigned char *)"Если желаете продолжить инсталляцию обновления, закройте окно программы «%s»")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#endif // #ifndef kpstmsg_ru_included
