// -----------------------------------------
// kpstedi_ru.h
// kpstedi pranesimai
// rusш kalba
//

#ifndef kpstedi_ru_included
#define kpstedi_ru_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#if (KPSTEDI_MODE & OWNER_MODE)
#  define KPSTEDI_USER_DATA_CHANGED_RU ((const unsigned char *)"Пароль и данные пользователя изменены.")
#else
#  define KPSTEDI_USER_DATA_CHANGED_RU ((const unsigned char *)"")
#endif

#if ((KPSTEDI_MODE & STARTER_MODE) == 0) // && ((KPSTEDI_MODE & USER_MODE) == 0)
#  if KPSTEDI_MODE & OWNER_MODE
#     define KPSTEDI_TITLE_RU        ((const unsigned char *)"Пароль и данные пользователя ")
#  endif
#else
#  define KPSTEDI_TITLE_RU           ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
#  define KPSTEDI_USER_PWD_PROMPT_RU   ((const unsigned char *)"Пароль")
#  define KPSTEDI_REPEAT_PWD_PROMPT_RU ((const unsigned char *)"Повторите пароль")
#else
#  define KPSTEDI_USER_PWD_PROMPT_RU   ((const unsigned char *)"")
#  define KPSTEDI_REPEAT_PWD_PROMPT_RU ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
#  define KPSTEDI_USER_DATA_PROMPT_RU  ((const unsigned char *)"Пользователь")
#else
#  define KPSTEDI_USER_DATA_PROMPT_RU  ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_SURE_CHANGE_PWD_RU    ((const unsigned char *)"Вы указали пароль, ввод которого будет необходим при каждом запуске программы.\n \nВы согласны?")
#  define KPSTEDI_PWD_NOT_MATCH_RU      ((const unsigned char *)"Указанные пароли не совпадают.")
#else
#  define KPSTEDI_SURE_CHANGE_PWD_RU    ((const unsigned char *)"")
#  define KPSTEDI_PWD_NOT_MATCH_RU      ((const unsigned char *)"")
#endif
#  define KPSTEDI_USER_PWD_NOT_MATCH_RU  KPSTEDI_PWD_NOT_MATCH_RU

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#endif // #ifndef kpstedi_ru_included
