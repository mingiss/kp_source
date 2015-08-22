// -----------------------------------------
// kpstlsvr_lt.h
// licencij�/rezultat� serverio prane�imai
// liet. kalba
// 

#ifndef kpstlsvr_lt_included
#define kpstlsvr_lt_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#define KPSTLSVR_MSG_SERVER_STARTED_LT             ((const unsigned char *)"Serveris paleistas")
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_LT ((const unsigned char *)"nutrauktas ankstesnis seansas")
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_LT ((const unsigned char *)"�ra�yti nepilni rezultatai")
#define KPSTLSVR_MSG_RECEIVED_RESULTS_LT           ((const unsigned char *)" atsiunt�")
#define KPSTLSVR_MSG_INTERMEDIATE_RES_LT           ((const unsigned char *)" tarpinius")
#define KPSTLSVR_MSG_FINAL_RES_LT                  ((const unsigned char *)" galutinius")
#define KPSTLSVR_MSG_RESULTS_RECEIVED_LT           ((const unsigned char *)" rezultatus")
#define KPSTLSVR_MSG_REGISTERED_LT                 ((const unsigned char *)" prisiregistravo testo sprendimui")
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_LT         ((const unsigned char *)"            confirm(\"Ar tikrai norite i�mesti visus pa�ym�tus �ra�us?\");\n")
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_LT    ((const unsigned char *)"   confirm(\"Ar tikrai norite i�mesti visus prisijungim� �ra�us?\");\n")
#define KPSTLSVR_MSG_ERROR_LT                      ((const unsigned char *)"Klaida: ")
#define KPSTLSVR_MSG_WARNING_LT                    ((const unsigned char *)"Persp�jimas: ")
#define KPSTLSVR_MSG_CLIENT_STATUS_LT              ((const unsigned char *)"Kliento b�sena")
#define KPSTLSVR_MSG_STATUS_LT                     ((const unsigned char *)" busena")
#define KPSTLSVR_MSG_CLIENTS_STATUS_LT             ((const unsigned char *)"Klient� b�sena")
#define KPSTLSVR_MSG_TAB_STATUS_LT                 ((const unsigned char *)"B�sena")
#define KPSTLSVR_MSG_TAB_CLIENTS_LT                ((const unsigned char *)"Klientai")
#define KPSTLSVR_MSG_TAB_RESULTS_LT                ((const unsigned char *)"Rezultatai")
#define KPSTLSVR_MSG_TAB_MESSAGES_LT               ((const unsigned char *)"Prane�imai")
#define KPSTLSVR_MSG_TAB_NETWORK_LT                ((const unsigned char *)"Tinklai")
#define KPSTLSVR_MSG_TAB_ADMINS_LT                 ((const unsigned char *)"Administratoriai")
#define KPSTLSVR_MSG_ORDER_NO_LT                   ((const unsigned char *)"Eil. Nr.")
#define KPSTLSVR_MSG_SESSION_ID_LT                 ((const unsigned char *)"Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_LT                  ((const unsigned char *)"Kliento IP adresas")
#define KPSTLSVR_MSG_REST_MIN_LT                   ((const unsigned char *)"Liko min.")
#define KPSTLSVR_MSG_SESSION_ACTIVE_LT             ((const unsigned char *)" seansas aktyvus,")
#define KPSTLSVR_MSG_LOST_CONNECTION_LT            ((const unsigned char *)" prarastas ry�ys su klientu,")
#define KPSTLSVR_MSG_SLOT_FREE_LT                  ((const unsigned char *)" galima registruotis.")
#define KPSTLSVR_MSG_REST_MIN__LT                  ((const unsigned char *)"Liko min. ")
#define KPSTLSVR_MSG_LOST_CLI_TIME_LT              ((const unsigned char *)" prarast� klient� gyvavimo laikas")
#define KPSTLSVR_MSG_RESULTS_LT                    ((const unsigned char *)" rezultatai")
#define KPSTLSVR_MSG_TEST_RESULTS_LT               ((const unsigned char *)"Testo rezultatai")
#define KPSTLSVR_MSG_CLASS_PREFIX_LT               ((const unsigned char *)"")
#define KPSTLSVR_MSG_CLASS_POSTFIX_LT              ((const unsigned char *)" kl.")
#define KPSTLSVR_MSG_RES_FILE_LT                   ((const unsigned char *)"Rezultatai kaupiami faile ")
#define KPSTLSVR_MSG_BAD_RES_LT                    ((const unsigned char *)" suged� ar kito testo rezultatai;")
#define KPSTLSVR_MSG_BAD_RES_REC_LT                ((const unsigned char *)" sugadintas rezultat� �ra�as;") 
#define KPSTLSVR_MSG_TEST_TIMEOUT_LT               ((const unsigned char *)" baig�si sprendimo laikas.")
#define KPSTLSVR_MSG_MESSAGES__LT                  ((const unsigned char *)" pranesimai")
#ifdef KPST_ARKIM
#define KPSTLSVR_MSG_ERROR_HELP_LT                 ((const unsigned char *)"Apie pasteb�tas klaidas ar persp�jimus prane�kite adresu arkim@tev.lt")
#else
#define KPSTLSVR_MSG_ERROR_HELP_LT                 ((const unsigned char *)"Apie pasteb�tas klaidas ar persp�jimus prane�kite adresu tech@tev.lt")
#endif                  
#define KPSTLSVR_MSG_SESSION_STATUS_LT             ((const unsigned char *)"Ry�io seanso b�sena")
#define KPSTLSVR_MSG_NETWORKS_LT                   ((const unsigned char *)" tinklai")
#define KPSTLSVR_MSG_ADMINS_LT                     ((const unsigned char *)" administratoriai")
#define KPSTLSVR_MSG_STATUS__LT                    ((const unsigned char *)" busena")
#define KPSTLSVR_MSG_IP_LIST_LT                    ((const unsigned char *)"S�ra�as IP adres�, i� kuri� leid�iama ")
#define KPSTLSVR_MSG_IP_LIST_SEND_LT               ((const unsigned char *)"si�sti duomenis") // "S�ra�as IP adres�, i� kuri� leid�iama si�sti rezultatus"
// #define KPSTLSVR_MSG_IP_LIST_REGISTER_LT           ((const unsigned char *)"registruotis") // "S�ra�as IP adres�, i� kuri� leid�iama registruoti licencijas"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_LT           ((const unsigned char *)"aktyvuoti darbo vietas")
#define KPSTLSVR_MSG_IP_LIST_ADMIN_LT              ((const unsigned char *)"S�ra�as IP adres�, i� kuri� leid�iama administruoti server�")
#define KPSTLSVR_MSG_CONNECTIONS_LIST_LT           ((const unsigned char *)"Prisijungim� s�ra�as")
#define KPSTLSVR_MSG_SESSION_STARTED_LT            ((const unsigned char *)" seansas prad�tas,")
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_LT         ((const unsigned char *)" siun�iami tarpiniai rezultatai,")
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_LT         ((const unsigned char *)" atsi�sti galutiniai rezultatai,")
#define KPSTLSVR_MSG_SESSION_ABORTED_LT            ((const unsigned char *)" seansas nutrauktas.") // " seansas baigtas."
#define KPSTLSVR_MSG_ABORT_PROMPT_LT               ((const unsigned char *)"Jei norite �ra�yti neu�baigtus rezultatus, spauskite mygtuk� \"I�saugoti\", jei visus �ra�us i�mesti � \"I�valyti\"")
#define KPSTLSVR_MSG_IP_HINT_LT                    ((const unsigned char *)"Jei norite prid�ti vis� potinkl�, naudokite IP adreso oktet� 255")
#define KPSTLSVR_MSG_PORT_BUSSY_LT                 ((const unsigned char *)"Ry�io kanalas u�imtas, serverio paleisti nepavyko")
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_LT        ((const unsigned char *)"prisijung� administruoti server�")
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_LT        ((const unsigned char *)"atmestas bandymas administruoti server�")
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_LT           ((const unsigned char *)" atsiunt� duomenis neu�siregistrav�s")
#define KPSTLSVR_MSG_EXCERCISE_LT                  ((const unsigned char *)"sprend�ia u�davin� ")
#define KPSTLSVR_MSG_EXERCISE_DONE_LT              ((const unsigned char *)"baig� u�davin� ")
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_LT           ((const unsigned char *)"klientas u�registruotas") // "licencija priregistruota"
#define KPSTLSVR_MSG_LOGGING_REFUSED_LT            ((const unsigned char *)"kliento registracija atmesta") // "licencijos registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_LT          ((const unsigned char *)"klientas i�registruotas") // "licencijos registravimas panaikintas"
// #define KPSTLSVR_MSG_RES_LOG_REFUSED_LT            ((const unsigned char *)"rezultat� registravimas/pri�mimas atmestas")
#define KPSTLSVR_MSG_RES_LOG_REFUSED_LT            ((const unsigned char *)"rezultatai atmesti")
#define KPSTLSVR_MSG_SERVER_STOPPED_LT             ((const unsigned char *)"Serveris sustabdytas")
#define KPSTLSVR_MSG_SERVER_ABORTED_LT             ((const unsigned char *)"Serveris sustabdytas avariniu b�du") 
#define KPSTLSVR_MSG_SERVER_ASKED_LT               ((const unsigned char *)"ie�ko serverio")
#define KPSTLSVR_MSG_LOG_PROMPT_LT                 ((const unsigned char *)"I�samesni prane�imai kaupiami faile %s")
                                                     
#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef kpstlsvr_lt_included
