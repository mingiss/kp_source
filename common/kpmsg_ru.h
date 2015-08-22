// -----------------------------------------
// kpmsg_ru.h
// programos paleidimo aplikaciju pranesimai
// rusш kalba
//

#ifndef kpmsg_ru_included
#define kpmsg_ru_included

// --------------------------------------- common kp messages

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#define KP_MSG_TITLE_RU             ((const unsigned char *)"Сообщение")
#define KP_INPUT_TITLE_RU           ((const unsigned char *)"Ввод")

#define KP_MSG_YES_RU               ((const unsigned char *)"Да")
#define KP_MSG_TAIP_RU              KP_MSG_YES_RU
#define KP_MSG_NO_RU                ((const unsigned char *)"Нет")
#define KP_MSG_NE_RU                KP_MSG_NO_RU
#define KP_MSG_OK_RU                KP_MSG_TESTI_RU // KP_MSG_YES_RU // ((const unsigned char *)"Хорошо")
#define KP_MSG_GERAI_RU             KP_MSG_TESTI_RU // KP_MSG_OK_RU
#define KP_MSG_CANCEL_RU            ((const unsigned char *)"Отменить")
#define KP_MSG_ATSAUKTI_RU          KP_MSG_CANCEL_RU
#define KP_MSG_TESTI_RU             ((const unsigned char *)"Продолжить") // "Продолжать")
#define KP_MSG_BAIGTI_RU            ((const unsigned char *)"Закончить")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_RU ((const unsigned char *)"Забыли пароль")

#define KP_MSG_ERROR_RU             ((const unsigned char *)"Ошибка")
#define KP_MSG_WARNING_RU           ((const unsigned char *)"Предупреждение")
#define KP_MSG_FILE_LINE_RU         ((const unsigned char *)", ошибка: %lx, файл: %s, строка: %d")
#define KP_MSG_ENTRY_ID_RU          ((const unsigned char *)", Идентификатор записи:%ld")
#define KP_MSG_ENTRY_RU             ((const unsigned char *)", Запись: %s")

#define KP_MSG_NO_STANDARD_PROG_RU  ((const unsigned char *)"Нет стандартной программы для данного типа файлов")
#define KP_MSG_WND_NOT_FOUND_RU     ((const unsigned char *)"Окно не найдено")
#define KP_MSG_PID_NOT_FOUND_RU     ((const unsigned char *)"Не найден идентификатор процесса")
#define KP_MSG_NO_SOCKET_RU         ((const unsigned char *)"Сокет ещё не создан")
#define KP_MSG_SOCK_UNRESOLVED_RU   ((const unsigned char *)"Адрес сервера ещё не найден")

#define KP_MSG_ERR_OK_RU            ((const unsigned char *)"Операция прошла успешно")
#define KP_MSG_INVALIDARG_RU        ((const unsigned char *)"Ошибочный параметр")
#define KP_MSG_NOTIMPL_RU           ((const unsigned char *)"Функция ещё не реализирована")
#define KP_MSG_UNEXPECTED_RU        ((const unsigned char *)"Неожиданный вызов функции")
#define KP_MSG_FERROR_RU            ((const unsigned char *)"Ошибка чтения/записи файла")
#define KP_MSG_SYSTEM_ERROR_RU      ((const unsigned char *)"Внутренняя ошибка")
#define KP_MSG_EOF_RU               ((const unsigned char *)"Неожиданный конец файла")
#define KP_MSG_FILE_FORMAT_RU       ((const unsigned char *)"Неправильный формат файла")
#define KP_MSG_FILE_NOT_FOUND_RU    ((const unsigned char *)"Файл не найден")
#define KP_MSG_DIR_ERROR_RU         ((const unsigned char *)"Неудачная попытка создания файла")
#define KP_MSG_OUTOFMEM_RU          ((const unsigned char *)"Переполнение памяти")
#define KP_MSG_NO_FILE_RU           ((const unsigned char *)"Файл неоткрыт")
#define KP_MSG_DOUBLE_UNGET_RU      ((const unsigned char *)"Двойной возврат ввода")
#define KP_MSG_UNKN_CHR_RU          ((const unsigned char *)"Неопознанный символ")
#define KP_MSG_COMMAND_ERROR_RU     ((const unsigned char *)"Внешняя ошибка")
#define KP_MSG_BUFFER_OVERFLOW_RU   ((const unsigned char *)"Переполнение буфера")
#define KP_MSG_FONT_UNDEF_RU        ((const unsigned char *)"Шрифт неопознан")
#define KP_MSG_KWD_NOT_FOUND_RU     ((const unsigned char *)"Ключевое слово не найдено")
#define KP_MSG_UNKNOWN_SYSTEM_RU    ((const unsigned char *)"Неопознанная версия ОС")
// #define KP_MSG_ILL_CODE_RU          ((const unsigned char *)"Ошибочный код регистрации")
#define KP_MSG_ILL_CODE_RU          ((const unsigned char *)"Ошибочный код активации")
#define KP_MSG_CANCELLED_RU         ((const unsigned char *)"Операция прекрашена")
#define KP_MSG_DOUBLE_CALL_RU       ((const unsigned char *)"Двойной вызов")
#define KP_MSG_TIMEOUT_RU           ((const unsigned char *)"Таймоут")
#define KP_MSG_OBJ_NOT_FOUND_RU     ((const unsigned char *)"Объект ненайден")
#define KP_MSG_NO_CONN_RU           ((const unsigned char *)"Нет связи")

#define KP_MSG_TRANS_ERR_RU         ((const unsigned char *)"Ошибка передачи")
#define KP_MSG_TRANS_ERR_1_RU       ((const unsigned char *)"Ошибка передачи, запустите скачивание ещё раз")

// #define KP_MSG_REFUSED_RU           ((const unsigned char *)"Отказ предоставления регистрации")
#define KP_MSG_REFUSED_RU           ((const unsigned char *)"Отказ предоставления активации")
#define KP_MSG_ACCESS_DENIED_RU     ((const unsigned char *)"Нет доступа")
#define KP_MSG_ILLEGAL_CHARACTER_RU ((const unsigned char *)"Неожиданный символ")
#define KP_MSG_DIV_ZERO_RU          ((const unsigned char *)"Деление на ноль")
#define KP_MSG_ILLMATHARG_RU        ((const unsigned char *)"Ошибочный аргумент математической операции")
#define KP_MSG_ILLFUNC_RU           ((const unsigned char *)"Ошибочный вызов функции")

#define KP_MSG_NOTINST_RU           ((const unsigned char *)"Программа ещё не установлена или её установка повреждена, повторите процедуру инсталляции")
#define KP_MSG_NOTINST_S_RU         ((const unsigned char *)"Программа «%s» ещё не установлена или её установка повреждена, повторите процедуру инсталляции")
#define KP_MSG_NOTINST_DELETE_RU    ((const unsigned char *)"Программа ещё не установлена или её установка повреждена. Удалите программу и повторите процедуру инсталляции.")

#define KP_MSG_MSG_FORMAT_RU        ((const unsigned char *)"Ошибочный формат сообщения")
#define KP_MSG_OBSOLETE_RU          ((const unsigned char *)"Устаревший вызов функции")

//#define KP_MSG_ERROR_HELP_RU      ((const unsigned char *)".  За технической помощью обращайтесь по адресу tech@tev.lt   Для более подробной информации см. файл %s")
//#define KP_MSG_ERROR_HELP_RU      ((const unsigned char *)".  За технической помощью обращайтесь по электронной почте, адрес tech@tev.lt   К сообщению присоедините файл %s")
#define KP_MSG_ERROR_HELP_RU        ((const unsigned char *)".  За технической помощью обращайтесь по электронной почте, адрес pagalba@tev.lt")
#define KP_MSG_ERROR_HELP_REST_RU   ((const unsigned char *)"   К сообщению присоедините файл %s с Вашего рабочего стола.")

#define KP_MSG_WSAEACCES_RU               KP_MSG_ACCESS_DENIED_RU
#define KP_MSG_WSAEADDRINUSE_RU           ((const unsigned char *)"Адрес занят")
#define KP_MSG_WSAEADDRNOTAVAIL_RU        ((const unsigned char *)"Неудачная попытка присвоить адрес")
#define KP_MSG_WSAEAFNOSUPPORT_RU         ((const unsigned char *)"Адресная группа протоколом не поддерживается")
#define KP_MSG_WSAEALREADY_RU             ((const unsigned char *)"Операция уже выполняется")
#define KP_MSG_WSAECONNABORTED_RU         ((const unsigned char *)"Программное прекращение связи")
#define KP_MSG_WSAECONNREFUSED_RU         ((const unsigned char *)"Отказ предоставления соединения")
#define KP_MSG_WSAECONNRESET_RU           ((const unsigned char *)"Прекращение соединения")
#define KP_MSG_WSAEDESTADDRREQ_RU         ((const unsigned char *)"Необходим адрес назначения")
#define KP_MSG_WSAEFAULT_RU               ((const unsigned char *)"Ошибочный адрес")
#define KP_MSG_WSAEHOSTDOWN_RU            ((const unsigned char *)"Сервер выключен")
#define KP_MSG_WSAEHOSTUNREACH_RU         ((const unsigned char *)"Сервер недоступен")
#define KP_MSG_WSAEINPROGRESS_RU          ((const unsigned char *)"Операция выполняется")
#define KP_MSG_WSAEINTR_RU                ((const unsigned char *)"Вызов функции прерывания")
#define KP_MSG_WSAEINVAL_RU               ((const unsigned char *)"Ошибочный аргумент")
#define KP_MSG_WSAEISCONN_RU              ((const unsigned char *)"Сокет занят")
#define KP_MSG_WSAEMFILE_RU               ((const unsigned char *)"Переполнение числа открытых файлов") // "Слишком много открытых файлов")
#define KP_MSG_WSAEMSGSIZE_RU             ((const unsigned char *)"Переполнение длины сообщения") // "Сообщение слишком длинное")
#define KP_MSG_WSAENETDOWN_RU             ((const unsigned char *)"Сеть не работает")
#define KP_MSG_WSAENETRESET_RU            ((const unsigned char *)"Сеть отключилась")
#define KP_MSG_WSAENETUNREACH_RU          ((const unsigned char *)"Сеть недоступна")
#define KP_MSG_WSAENOBUFS_RU              ((const unsigned char *)"Недостаток места в буфере")
#define KP_MSG_WSAENOPROTOOPT_RU          ((const unsigned char *)"Ошибочная опция протокола")
#define KP_MSG_WSAENOTCONN_RU             ((const unsigned char *)"Сокет неподключен")
#define KP_MSG_WSAENOTSOCK_RU             ((const unsigned char *)"Операция сокета не для сокета")
#define KP_MSG_WSAEOPNOTSUPP_RU           ((const unsigned char *)"Операция не поддерживается")
#define KP_MSG_WSAEPFNOSUPPORT_RU         ((const unsigned char *)"Группа протоколов не поддерживается")
#define KP_MSG_WSAEPROCLIM_RU             ((const unsigned char *)"Переполнение числа процессов") // "Слишком много процессов")
#define KP_MSG_WSAEPROTONOSUPPORT_RU      ((const unsigned char *)"Протокол не поддерживается")
#define KP_MSG_WSAEPROTOTYPE_RU           ((const unsigned char *)"Ошибочный тип сокета для данного протокола")
#define KP_MSG_WSAESHUTDOWN_RU            ((const unsigned char *)"После закрытия сокета передача невозможна")
#define KP_MSG_WSAESOCKTNOSUPPORT_RU      ((const unsigned char *)"Тип сокета не поддерживается")
#define KP_MSG_WSAETIMEDOUT_RU            ((const unsigned char *)"Таймоут в соединении")
#define KP_MSG_WSATYPE_NOT_FOUND_RU       ((const unsigned char *)"Тип класса ненайден")
#define KP_MSG_WSAEWOULDBLOCK_RU          ((const unsigned char *)"Ресурс временно не доступен")
#define KP_MSG_WSAHOST_NOT_FOUND_RU       ((const unsigned char *)"Сервер ненайден")
#define KP_MSG_WSA_INVALID_HANDLE_RU      ((const unsigned char *)"Ошибочный указатель объекта") // "Specified event object handle is invalid")
#define KP_MSG_WSA_INVALID_PARAMETER_RU   ((const unsigned char *)"Ошибочные параметры") // "One or more parameters are invalid")
#define KP_MSG_WSAINVALIDPROCTABLE_RU     ((const unsigned char *)"Ошибочная таблица процедур") // "Invalid procedure table from service provider")
#define KP_MSG_WSAINVALIDPROVIDER_RU      ((const unsigned char *)"Ошибочный код провайдера") // "Invalid service provider version number")
#define KP_MSG_WSA_IO_INCOMPLETE_RU       ((const unsigned char *)"Объекты перекрывающихся событий ещё активны") // "Overlapped I/O event object not in signaled state")
#define KP_MSG_WSA_IO_PENDING_RU          ((const unsigned char *)"Перекрывающиеся операции будут выполнены позже") // Overlapped operations will complete later")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_RU   ((const unsigned char *)"Переполнение памяти")
#define KP_MSG_WSANOTINITIALISED_RU       ((const unsigned char *)"Сетевая подсистема ещё не активирована") // "Successful WSAStartup not yet performed")
#define KP_MSG_WSANO_DATA_RU              ((const unsigned char *)"Имя правильное, но отсутствует запись данных необходимого типа")
#define KP_MSG_WSANO_RECOVERY_RU          ((const unsigned char *)"неисправимая ошибка")
#define KP_MSG_WSAPROVIDERFAILEDINIT_RU   ((const unsigned char *)"Неудачная попытка инициализировать провайдера услуги")
#define KP_MSG_WSASYSCALLFAILURE_RU       ((const unsigned char *)"Ошибка системного вызова")
#define KP_MSG_WSASYSNOTREADY_RU          ((const unsigned char *)"Сетевая система недоступна")
#define KP_MSG_WSATRY_AGAIN_RU            ((const unsigned char *)"Ненайден неавторизированный сервер") // "Non-authoritative host not found")
#define KP_MSG_WSAVERNOTSUPPORTED_RU      ((const unsigned char *)"Неопознанная версия WINSOCK.DLL")
#define KP_MSG_WSAEDISCON_RU              ((const unsigned char *)"Начата процедура выключения системы")
#define KP_MSG_WSA_OPERATION_ABORTED_RU   ((const unsigned char *)"Перекрывающаяся операция прекращена")

#define KP_MSG_OUT_OF_MEM_RES_RU          ((const unsigned char *)"Переполнение памяти или ресурсов операционной системы")
#define KP_MSG_ERROR_FILE_NOT_FOUND_RU    ((const unsigned char *)"Указанный файл не найден")
#define KP_MSG_ERROR_PATH_NOT_FOUND_RU    ((const unsigned char *)"Указанный путь не найден")
#define KP_MSG_ERROR_BAD_FORMAT_RU        ((const unsigned char *)"Испорчен или неопознан файл .exe")
#define KP_MSG_SE_ERR_ACCESSDENIED_RU     ((const unsigned char *)"Операционная система отказала в доступе к указанному файлу")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_RU  ((const unsigned char *)"Ассоциация имени файла неполная или ошибочна")
#define KP_MSG_SE_ERR_DDEBUSY_RU          ((const unsigned char *)"Транзакция DDE не может быть завершена, так как имеются другие активные транзакции DDE")
#define KP_MSG_SE_ERR_DDEFAIL_RU          ((const unsigned char *)"Транзакция DDE прекращена")
#define KP_MSG_SE_ERR_DDETIMEOUT_RU       ((const unsigned char *)"Таймоут в транзакции DDE")
#define KP_MSG_SE_ERR_DLLNOTFOUND_RU      ((const unsigned char *)"Указанная динамическая библиотека не найдена")
#define KP_MSG_SE_ERR_FNF_RU              ((const unsigned char *)"Указанный файл не найден")
#define KP_MSG_SE_ERR_NOASSOC_RU          ((const unsigned char *)"Указанный тип файла не имеет ассоциированной программы")
#define KP_MSG_SE_ERR_OOM_RU              ((const unsigned char *)"Недостаточный объём памяти для завершения операции")
#define KP_MSG_SE_ERR_PNF_RU              ((const unsigned char *)"Указанный путь не найден")
#define KP_MSG_SE_ERR_SHARE_RU            ((const unsigned char *)"Ошибка совместного использования") // "Нарушение ...") // "A sharing violation occurred")

#define KP_MSG_FIRST_TIME_ADMIN_RU        ((const unsigned char *)"Для запуска программы первый раз необходимы\n права администратора. Зарегистрируйтесь администратором и запустите программу ещё раз.")
#define KP_MSG_NOW_NOT_ADMIN_RU           KP_MSG_NOT_ADMIN
#define KP_MSG_NOT_ADMIN_RU               ((const unsigned char *)"Зарегистрируйтесь рядовым пользователем и запустите программу ещё раз")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_RU ((const unsigned char *)"Неудачная попытка копировать файл, зарегистрируйтесь администратором и запустите программу ещё раз")

#define KP_PROGRESS_TITLE_RU              ((const unsigned char *)"Подождите...")
#define KP_MSG_DELETING_FILE_RU           ((const unsigned char *)"Удаляется файл %s.%s...")
#define KP_MSG_COPYING_RU                 ((const unsigned char *)"Копируется файл...")
#define KP_MSG_COPYING_FILE_RU            ((const unsigned char *)"Копируется файл %s.%s...")
#define KP_MSG_COPYING_DIR_RU             ((const unsigned char *)"Копируется каталог %s.%s...")

#define KP_MSG_DOWNLOADING_RU             ((const unsigned char *)"Передача файла...")
#define KP_MSG_DOWNLOADING_FILE_RU        ((const unsigned char *)"Передача файла %s.%s...")

#define KP_MSG_NEG_ANSW_RU                ((const unsigned char *)"Отирцательный ответ")

#define KP_MSG_UNABLE_TO_EXECUTE_RU       ((const unsigned char *)"Не могу выполнить комманду %s – проверьте, правильно ли установлены все компоненты системы")

#define KP_MSG_FLASH_PLAYER_INSTALL_RU    ((const unsigned char *)"Сейчас будет установлен Macromedia Flash плеер. Следуйте дальнейшим указаниям программы установки плеера.")

#define KP_MSG_FILE_CHANGED_RU            ((const unsigned char *)"Файл изменился")

#define KP_MSG_ALL_FILES_RU               ((const unsigned char *)"Все файлы (*.*)")
#define KP_MSG_SAVE_AS_RU                 ((const unsigned char *)"Записать как")

#define KP_MSG_FILE_EXISTS_RU             ((const unsigned char *)"Файл %s уже есть, переписать?")

#define KP_MSG_DIAG_MSG_RU                ((const unsigned char *)"Подготовка диагностического сообщения")
#define KP_MSG_DIAG_MSG_TITLE_RU          ((const unsigned char *)"Диагностическое сообщение")

#if FALSE
#define KP_MSG_DIAG_MSG_EXPL_RU           ((const unsigned char *)"Для того, чтобы послать диагностическое сообщение производителю, необходимо " \
                                                                  "заполнить предоставленные поля. Сообщение с конфигурацией компьютера, продукта и " \
                                                                  "детальной информацией об ошибке будет выслано по интернету в сервер производителя " \
                                                                  "продукта. Если после некоторого времени с Вами не будет установлена связь по " \
                                                                  "указанному адресу, обращайтесь за консультацией по адресу pagalba@tev.lt")
#define KP_MSG_DIAG_MSG_EXPL_RU           ((const unsigned char *)"Для того, чтобы послать диагностическое сообщение производителю, необходимо " \
                                                                  "заполнить предоставленные поля. Сообщение с конфигурацией компьютера, продукта и " \
                                                                  "детальной информацией об ошибке будет выслано по интернету в сервер производителя " \
                                                                  "продукта. Если после некоторого времени с Вами не будет установлена связь, " \
                                                                  "обращайтесь по адресу pagalba@tev.lt")
#endif
// #define KP_MSG_DIAG_MSG_EXPL_RU           ((const unsigned char *)"Для того, чтобы послать диагностическое сообщение производителю, необходимо заполнить предоставленные поля.")
// #define KP_MSG_DIAG_MSG_EXPL_RU           ((const unsigned char *)"Если при использовании данного продукта возникли проблемы, можете выслать диагностическое сообщение производителю. Заполните предоставленные поля.")
#define KP_MSG_DIAG_MSG_EXPL_RU           ((const unsigned char *)"Если при использовании данного продукта возникли проблемы, можете выслать сообщение производителю. Заполните предоставленные поля.")
#define KP_MSG_DIAG_MSG_EXPL1_RU          ((const unsigned char *)"Для того, чтобы послать диагностическое сообщение, нажмите кнопку «Послать», в противном случае – «Отменить».")
#define KP_MSG_DIAG_MSG_EXPL2_RU          ((const unsigned char *)"Для того, чтобы послать диагностическое сообщение производителю, необходимо заполнить поле адреса Вашей электронной почты и нажать кнопку «Послать».")

// #define KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU   ((const unsigned char *)"Адрес Вашего почтового ящика электронной почты:")
#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_RU   ((const unsigned char *)"Ваш адрес электронной почты:")
// #define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU ((const unsigned char *)"Ваши заметки по поводу обстоятельств возникновения ошибки:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_RU ((const unsigned char *)"Ваши заметки про обстоятельства возникновения ошибки:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_RU    ((const unsigned char *)"Дополнительный файл, который Вы хотели бы выслать\n(например, картинка копии екрана):")

#define KP_MSG_BAD_EMAIL_ADDRESS_RU       ((const unsigned char *)"Ошибочный адрес электронной почты")

#define KP_MSG_DIAG_MSG_SEL_FILE_RU       ((const unsigned char *)"Выберите файл для отправления")

#define KP_MSG_DIAG_MSG_SUCCEEDED_RU      ((const unsigned char *)"Диагностическое сообщение выслано успешно")

#define KP_MSG_SIUSTI_RU                  ((const unsigned char *)"Послать")

#define KP_MSG_FIREWALL_RU                ((const unsigned char *)"Доступ к интернету заблокирован. Проверьте установки Вашего сетевого экрана (firewall) – попробуйте включить %s в список программ, которым дозволен доступ к интернету.")

#define KP_MSG_POINTER_RU                 ((const unsigned char *)"Неправильный указатель")

// TODO: iрversti
#define KP_MSG_LOG_STARTED_RU             ((const unsigned char *)"Юurnalas iрvedamas ir б failа %s")
#define KP_MSG_CONS_TITLE_RU              ((const unsigned char *)"%s: Praneрimш юurnalas") // ((const unsigned char *)"Pulto terminalas") // ((const unsigned char *)"Pultas")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#endif // #ifndef kpmsg_ru_included
