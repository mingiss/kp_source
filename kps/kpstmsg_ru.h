// -----------------------------------------
// kpstmsg_ru.h
// programos paleidimo aplikaciju pranesimai
// rusu kalba
// 

#ifndef kpstmsg_ru_included
#define kpstmsg_ru_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

// #define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"����������� ���������")
// #define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"����������� ��������")
#define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"��������� ��������")

// #define KPST_MSG_UNREG_RU           ((const unsigned char *)"����������� �����������")
#define KPST_MSG_UNREG_RU           ((const unsigned char *)"����������� ���������")
#define KPST_MSG_LIC_RU             ((const unsigned char *)"��������")

// #define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"��� ������ ��������� ���������� ����������� ��������.")
// #define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"��� ������ �������� ���������� ����������� ��������.")
#define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"��� ������ �������� ���������� ��������� ��������.")

#define KPST_MSG_IVESK_LIC_RU       ((const unsigned char *)"������� ��� ��������, ������� �� �������� ������ � ���������.")
#define KPST_MSG_IVESK_LIC_1_RU     ((const unsigned char *)"(���� ��� ����� ���������� � ������ ������.)")
#define KPST_MSG_REG_CARD_RU        ((const unsigned char *)"")
#define KPST_MSG_LIC_KOD_RU         ((const unsigned char *)"��� ��������:")
#define KPST_MSG_BLOGAS_LIC_KODAS_RU   ((const unsigned char *)"��������� ��� ��������")

// #define KPST_MSG_CHECK_CONN_RU      ((const unsigned char *)"��������� ����� ������ ���������� � ����������")
#define KPST_MSG_CHECK_CONN_RU      KP_MSG_FIREWALL_RU
// #define KPST_MSG_CHECK_CONN_LOC_RU  ((const unsigned char *)"��������� ����� ������ ���������� � ������������ �����")
#define KPST_MSG_CHECK_CONN_LOC_RU  ((const unsigned char *)"������ � ��������� ������������ ���� ������������. ��������� ��������� ������ �������� ������ (firewall) � ���������� �������� %s � ������ ��������, ������� �������� ������ � ���������.")

// #define KPST_MSG_REG_SUCC_RU        ((const unsigned char *)"%s\n                                       \n����������� �������� ������ �������") 
#define KPST_MSG_REG_SUCC_RU        ((const unsigned char *)"%s\n                                       \n��������� �������� ������ �������") 
// #define KPST_MSG_ALLREADY_REG_RU    ((const unsigned char *)"%s\n                                       \n�������� ��� ����������������") 
#define KPST_MSG_ALLREADY_REG_RU    ((const unsigned char *)"%s\n                                       \n�������� ��� ������������") 
// #define KPST_MSG_REG_UNSUC_RU       ((const unsigned char *)"��������� ������� ����������� �������� �� ���������.")
#define KPST_MSG_REG_UNSUC_RU       ((const unsigned char *)"��������� ������� ��������� �������� �� ���������.")
#define KPST_MSG_REG_UNSUC_0_RU     ((const unsigned char *)"���������� ��������� ������� ��������� �����,")
#define KPST_MSG_REG_UNSUC_1_RU     ((const unsigned char *)"� ���������� ����� ����������� � ������ ����� �����������.")

// #define KPST_MSG_REG_UNSUC_LOC_RU   ((const unsigned char *)"��������� ������� �����������.")
#define KPST_MSG_REG_UNSUC_LOC_RU   ((const unsigned char *)"��������� ������� ���������.")
#define KPST_MSG_DIEG_KOD_RU        ((const unsigned char *)"��� �����������:")

// #define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"����������� �������� ������ ���� �������� ����� �������������� ��������� �� ������ ����������.")
// #define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"����������� �������� ���������� ����� ��������� ��������� �� ������ ���������.")
// #define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"����������� �������� ���������� ����� ��������� �������� �� ������ ���������.")
#define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"�������� �������������� ����� ��������� �������� �� ������ ���������.")

#define KPST_MSG_UNREG_IVESK_LIC_RU KPST_MSG_IVESK_LIC_RU

// #define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"������������������ ��������� ����� �������� ������ �� ���� ����������!")
// #define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"������������������ ������� ����� �������� ������ �� ���� ����������!")
#define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"�������������� ������� ����� �������� ������ �� ���� ����������!")

// #define KPST_MSG_BUT_REG_RU         ((const unsigned char *)"��� ������ ��������������?")
#define KPST_MSG_BUT_REG_RU         ((const unsigned char *)"��� ������ ������������?")
// #define KPST_MSG_BUT_UNREG_RU       ((const unsigned char *)"��� ������ ���������� �����������?")
#define KPST_MSG_BUT_UNREG_RU       ((const unsigned char *)"��� ������ �������������� �������?")

#define KPST_MSG_INTERNETU_RU       ((const unsigned char *)"�� ���������")
#define KPST_MSG_TELEFONU_RU        ((const unsigned char *)"�� ��������")
#define KPST_MSG_CANCEL_REG_RU      ((const unsigned char *)"������")
// #define KPST_MSG_CANCEL_UNREG_RU    ((const unsigned char *)"�� ��������")
#define KPST_MSG_CANCEL_UNREG_RU    ((const unsigned char *)"������")

#define KPST_MSG_SIUSK_PASTU_RU     ((const unsigned char *)"��� ����������� ������ ���� ������ �� ����������� �����,")
#define KPST_MSG_DARBO_LAIKAS_RU    ((const unsigned char *)"����� tech@tev.lt, ��� ����������� ��������� � ������� �����")
#define KPST_MSG_DIKT_TELEF_RU      ((const unsigned char *)"� 9 �� 16 ����� EET �� ��������, ����� +370-5-2729318.")

#define KPST_MSG_IVESK_RAKTA_RU     ((const unsigned char *)"������� ���������� ����� � ���� �����������.")
#define KPST_MSG_IVESK_RAKTA_1_RU   ((const unsigned char *)"(���� ���� ����� ���������� � ������ ������.)")
#define KPST_MSG_DIEG_RAKTAS_RU     ((const unsigned char *)"���� �����������:")
#define KPST_MSG_DIEG_RAKTAS_1_RU   ((const unsigned char *)"���� �����������")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_RU ((const unsigned char *)"��������� ���� �����������")
#define KPST_MSG_START_FROM_CD_RU   ((const unsigned char *)"��������� ���������� ����� �� �������-�����")
#define KPST_MSG_BAD_CD_RU          ((const unsigned char *)"������ �������-����")

#define KPST_MSG_REZ_NESUFORM_RU    ((const unsigned char *)"��������� ����������� ���������.\n�� ����������� ������� ����������� �� ����������� �����, ����� tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_RU    ((const unsigned char *)"���������� �� �������.\n�� ����������� ������� ����������� �� ����������� �����, ����� tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_2_RU    ((const unsigned char *)" ���������� �� �������.\n�� ��������� ������������� %s, �� %s.\n���������� ������������������ ��������������� �������.")
#define KPST_MSG_REZ_SUCCESS_RU     ((const unsigned char *)". ���������� ������� ���������� � ")

// #define KPST_MSG_REG_NOT_ADMIN_RU   ((const unsigned char *)"��� ����������� �������� ���������� ����� �������������� �������")
#define KPST_MSG_REG_NOT_ADMIN_RU   ((const unsigned char *)"��� ��������� �������� ���������� ����� �������������� �������")
// #define KPST_MSG_UNREG_NOT_ADMIN_RU ((const unsigned char *)"��� ������ ����������� �������� ���������� ����� �������������� �������")
#define KPST_MSG_UNREG_NOT_ADMIN_RU ((const unsigned char *)"��� ����������� �������� ���������� ����� �������������� �������")
// #define KPST_MSG_NOT_REG_RU         ((const unsigned char *)"�������� �������� ��� �� ����������������")
#define KPST_MSG_NOT_REG_RU         ((const unsigned char *)"�������� �������� ��� �� ������������")
#define KPST_MSG_INVALID_REG_RU     ((const unsigned char *)"������������ ���� ���������� � ������������ �������� ����������. ��������� ��������� ��������.")

// #define KPST_MSG_UNREG_KOD_1_RU     ((const unsigned char *)"��� ������")
#define KPST_MSG_UNREG_KOD_1_RU     ((const unsigned char *)"��� �����������")
// #define KPST_MSG_UNREG_KOD_RU       ((const unsigned char *)"��� ������ ��������:                    \n")
#define KPST_MSG_UNREG_KOD_RU       ((const unsigned char *)"��� ����������� ��������:                    \n")
#define KPST_MSG_ALLREADY_REMOVED_RU   ((const unsigned char *)"%s\n                                       \n������� ��� �����")
// #define KPST_MSG_UNREG_SUCC_RU      ((const unsigned char *)"����������� �������� �������� �������") 
#define KPST_MSG_UNREG_SUCC_RU      ((const unsigned char *)"�������� ������� ��������������") 
// #define KPST_MSG_UNREG_UNSUCC_RU    ((const unsigned char *)"��������� ������� �������� ����������� �� ���������.")
#define KPST_MSG_UNREG_UNSUCC_RU    ((const unsigned char *)"��������� ������� ����������� �������� �� ���������.")
#define KPST_MSG_UNREG_UNSUCC_1_RU   ((const unsigned char *)" ���������� ��������� ������� ��������� �����.")

// #define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"�������� �������� ��� �� ����������������. ��������� ����������� ������ ���� ���������� ������� �������� ���� �������������.")
// #define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"�������� �������� ��� �� ������������. ��������� ��������� ������ ���� ���������� ������� �������� ���� �����������.")
#define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"�������� �������� ��� �� ������������. ��������� ��������� ����� ���������� ��� ��������� �������.")

// #define KPST_MSG_REG_NOT_YET_RU_0   ((const unsigned char *)"�������� �������� ��� �� ����������������. ��������� ����������� ������ ���� ���������� ������� �������� ���� �Registration�.")
// #define KPST_MSG_REG_NOT_YET_RU_0   ((const unsigned char *)"�������� �������� ��� �� ������������. ��������� ��������� ������ ���� ���������� ������� �������� ���� �Activation�.")
#define KPST_MSG_REG_NOT_YET_RU_0   KPST_MSG_REG_NOT_YET_RU

#define KPST_MSG_INI_NOT_ADMIN_RU   ((const unsigned char *)"������� ������� ����������, ����������������� ���������������")

// #define KPST_MSG_UNREG_PASTU_RU        ((const unsigned char *)"��� ������ ������ ���� ������ �� ����������� �����,")
#define KPST_MSG_UNREG_PASTU_RU        ((const unsigned char *)"��� ����������� ������ ���� ������ �� ����������� �����,")
#define KPST_MSG_UNREG_DARBO_LAIKAS_RU ((const unsigned char *)"����� tech@tev.lt, ��� ����������� ��������� � ������� �����")
#define KPST_MSG_UNREG_DIKT_TELEF_RU   ((const unsigned char *)"� 9 �� 16 ����� EET �� ��������, ����� +370-5-2729318.")

//#define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"�� �������� ���� ���������, ��������� �� ������� ��������� �� ������ ����������!")
// #define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"�� �������� �����, ��������� �� ������ ���������� �� ����������!")
#define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"�� �������� �����, ������� �� ������ ���������� �������� �� �����!")

#define KPST_MSG_INSERT_FLOPPY_RU   ((const unsigned char *)"�������� ������ ����")
#define KPST_MSG_UNABLE_OPEN_REZFILE_RU   ((const unsigned char *)"�� ������� ������� ���� � ������������.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_RU  ((const unsigned char *)"�� ������� �������� ���� � ������������.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_RU  ((const unsigned char *)"�� ������� ������� ���� � ������������.")
#define KP_MSG_UNABLE_READ_WRITTEN_RU     ((const unsigned char *)"�� ������� �������� ���������� ����.")
#define KPST_MSG_COULDNT_WRITE_RU   ((const unsigned char *)"�� ������� �������� ������.")
#define KPST_MSG_REFUSE_RESULTS_RU  ((const unsigned char *)"�� ������� � ���, ��� ������ ���������� �� �����������?")
#define KPST_MSG_TEST_SUCC_RU       ((const unsigned char *)"�������� ��������� �� ���� ���������� ������ �������")

#define KPST_MSG_TEST_UNSUC_RU      ((const unsigned char *)"���������� ��������������.\n������������, ����������, ����� �� �������� c:\\arkim\\rezultatai � ������� �� ����������� �����, ����� tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_RU    ((const unsigned char *)"�������� USB-����-���������� � �")
#define KPST_MSG_INSERT_FLASH_1_RU  ((const unsigned char *)"�")

#define KPST_MSG_ENTER_PWD_RU       ((const unsigned char *)"������� ������:")
#define KPST_MSG_BAD_PWD_RU         ((const unsigned char *)"������ � ������")
#define KPST_MSG_ENTER_PUK_RU       ((const unsigned char *)"������� ������������ ��� USB-����-����������:")
#define KPST_MSG_BAD_PUK_RU         ((const unsigned char *)"��������� ��� ��������")

// #define KPST_MSG_OBJ_REG_RU         ((const unsigned char *)"����������� ���������")
#define KPST_MSG_OBJ_REG_RU         ((const unsigned char *)"��������� ���������")
// #define KPST_MSG_OBJ_REG_INFO_RU    ((const unsigned char *)"����� �������������� ��������� ���������� ����������� ��������.")
#define KPST_MSG_OBJ_REG_INFO_RU    ((const unsigned char *)"����� �������������� ��������� ���������� ��������� ��������.")
// #define KPST_MSG_OBJ_UNREG_INFO_RU  ((const unsigned char *)"����������� �������� ������ ���� �������� ����� �������������� ��������� �� ������ ����������.")
#define KPST_MSG_OBJ_UNREG_INFO_RU  ((const unsigned char *)"�������� ������ ���� �������������� ����� �������������� ��������� �� ������ ����������.")
// #define KPST_MSG_OBJ_REG_PERSPEJ_RU ((const unsigned char *)"������������������ �������� ����� ����������� ������ �� ���� ����������!")
#define KPST_MSG_OBJ_REG_PERSPEJ_RU ((const unsigned char *)"�������������� �������� ����� ����������� ������ �� ���� ����������!")

// #define KPST_MSG_OBJ_REG_NOT_YET_RU     ((const unsigned char *)"����������� ��������� ��������.")
#define KPST_MSG_OBJ_REG_NOT_YET_RU     ((const unsigned char *)"�������� �������������.")
#define KPST_MSG_OBJ_UNREG_NEGALESIT_RU ((const unsigned char *)"�� �������� ���� ���������, �� ������ ���������� �������� ����������� �� �����!")

#define KPST_MSG_BAD_FLASH_RU ((const unsigned char *)"��� ���������� ������������� ��� USB-����-���������� %s")

#define KPST_MSG_LICENCE_EXPIRED_RU ((const unsigned char *)"%s\n                                       \n���� �������� �������� ��������")
#define KPST_MSG_REST_MONTHS_RU     ((const unsigned char *)"%s\n                                       \n���� �������� �������� �������� ����� %d �������")
#define KPST_MSG_REST_LAST_MONTH_RU ((const unsigned char *)"%s\n                                       \n���� �������� �������� �������� � ��������� ������")
#define KPST_MSG_REST_DAYS_RU       ((const unsigned char *)"%s\n                                       \n���� �������� �������� �������� ����� %d ����")
#define KPST_MSG_REST_DAY_RU        ((const unsigned char *)"%s\n                                       \n���� �������� �������� �������� ������")
#define KPST_MSG_REST_TODAY_RU      ((const unsigned char *)"%s\n                                       \n���� �������� �������� �������� �������")
#define KPST_MSG_TIME_CHEAT_RU      ((const unsigned char *)"��������� ���������� ��������� ���� ����������")

#define KPST_MSG_BAD_PRODVAR_RU     ((const unsigned char *)"�� ����������� ���������� ������� ��������. ��������� �������, ������� ������ �������� ������ �i�, �������� ����������� ���������� � ��� ���������.")

#define KPST_MSG_UPDATE_FINISHED_RU ((const unsigned char *)"         ������� ������ �����������.           \n     ����� ����� ��������� ����� MIKO.       ")

// #define KPST_MSG_SELDOWN_TITLE_RU   ((const unsigned char *)"�������� ����������� ��������")
#define KPST_MSG_SELDOWN_TITLE_RU   ((const unsigned char *)"�������� ������ ��������� �������")
#define KPST_MSG_SELDOWN_PROMPT_RU  ((const unsigned char *)"� ��������� ������� ��������� ����� �����.\n������� ������� � ��� �� ���, ������� ��������� �� �������:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_RU ((const unsigned char *)"��������� ����� ������ ��������� ������� ������ �� ���������:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_RU ((const unsigned char *)"��� �������� ���������� ����� ������ ������� �������,\n��� ���������� ������ ��� ��������� � ����������.")

#define KPST_MSG_SELUPD_TITLE_RU   ((const unsigned char *)"�������� ���������� ��������")
#define KPST_MSG_SELUPD_PROMPT_RU  ((const unsigned char *)"� �������� ���� ����������.                       \n"\
                                                           "������� ������� � ��� �� ���, ������� ��������� �� �������:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_RU ((const unsigned char *)"���������� �������� � ������� �� ���������:")
#define KPST_MSG_SELUPD_BUT_PROMPT_RU ((const unsigned char *)"���� ������� ��������� ���������� ����������, �������� ������ �������,\n"\
                                                              "���� ��� � ����������.                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_RU ((const unsigned char *)"���� ������� ���������� ����������� ����������, �������� ���� ��������� �%s�")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangRu_p) || (MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p))

#endif // #ifndef kpstmsg_ru_included
