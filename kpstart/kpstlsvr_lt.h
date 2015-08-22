// -----------------------------------------
// kpstlsvr_lt.h
// licencijø/rezultatø serverio praneðimai
// liet. kalba
// 

#ifndef kpstlsvr_lt_included
#define kpstlsvr_lt_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#define KPSTLSVR_MSG_SERVER_STARTED_LT             ((const unsigned char *)"Serveris paleistas")
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_LT ((const unsigned char *)"nutrauktas ankstesnis seansas")
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_LT ((const unsigned char *)"áraðyti nepilni rezultatai")
#define KPSTLSVR_MSG_RECEIVED_RESULTS_LT           ((const unsigned char *)" atsiuntë")
#define KPSTLSVR_MSG_INTERMEDIATE_RES_LT           ((const unsigned char *)" tarpinius")
#define KPSTLSVR_MSG_FINAL_RES_LT                  ((const unsigned char *)" galutinius")
#define KPSTLSVR_MSG_RESULTS_RECEIVED_LT           ((const unsigned char *)" rezultatus")
#define KPSTLSVR_MSG_REGISTERED_LT                 ((const unsigned char *)" prisiregistravo testo sprendimui")
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_LT         ((const unsigned char *)"            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n")
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_LT    ((const unsigned char *)"   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n")
#define KPSTLSVR_MSG_ERROR_LT                      ((const unsigned char *)"Klaida: ")
#define KPSTLSVR_MSG_WARNING_LT                    ((const unsigned char *)"Perspëjimas: ")
#define KPSTLSVR_MSG_CLIENT_STATUS_LT              ((const unsigned char *)"Kliento bûsena")
#define KPSTLSVR_MSG_STATUS_LT                     ((const unsigned char *)" busena")
#define KPSTLSVR_MSG_CLIENTS_STATUS_LT             ((const unsigned char *)"Klientø bûsena")
#define KPSTLSVR_MSG_TAB_STATUS_LT                 ((const unsigned char *)"Bûsena")
#define KPSTLSVR_MSG_TAB_CLIENTS_LT                ((const unsigned char *)"Klientai")
#define KPSTLSVR_MSG_TAB_RESULTS_LT                ((const unsigned char *)"Rezultatai")
#define KPSTLSVR_MSG_TAB_MESSAGES_LT               ((const unsigned char *)"Praneðimai")
#define KPSTLSVR_MSG_TAB_NETWORK_LT                ((const unsigned char *)"Tinklai")
#define KPSTLSVR_MSG_TAB_ADMINS_LT                 ((const unsigned char *)"Administratoriai")
#define KPSTLSVR_MSG_ORDER_NO_LT                   ((const unsigned char *)"Eil. Nr.")
#define KPSTLSVR_MSG_SESSION_ID_LT                 ((const unsigned char *)"Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_LT                  ((const unsigned char *)"Kliento IP adresas")
#define KPSTLSVR_MSG_REST_MIN_LT                   ((const unsigned char *)"Liko min.")
#define KPSTLSVR_MSG_SESSION_ACTIVE_LT             ((const unsigned char *)" seansas aktyvus,")
#define KPSTLSVR_MSG_LOST_CONNECTION_LT            ((const unsigned char *)" prarastas ryðys su klientu,")
#define KPSTLSVR_MSG_SLOT_FREE_LT                  ((const unsigned char *)" galima registruotis.")
#define KPSTLSVR_MSG_REST_MIN__LT                  ((const unsigned char *)"Liko min. ")
#define KPSTLSVR_MSG_LOST_CLI_TIME_LT              ((const unsigned char *)" prarastø klientø gyvavimo laikas")
#define KPSTLSVR_MSG_RESULTS_LT                    ((const unsigned char *)" rezultatai")
#define KPSTLSVR_MSG_TEST_RESULTS_LT               ((const unsigned char *)"Testo rezultatai")
#define KPSTLSVR_MSG_CLASS_PREFIX_LT               ((const unsigned char *)"")
#define KPSTLSVR_MSG_CLASS_POSTFIX_LT              ((const unsigned char *)" kl.")
#define KPSTLSVR_MSG_RES_FILE_LT                   ((const unsigned char *)"Rezultatai kaupiami faile ")
#define KPSTLSVR_MSG_BAD_RES_LT                    ((const unsigned char *)" sugedæ ar kito testo rezultatai;")
#define KPSTLSVR_MSG_BAD_RES_REC_LT                ((const unsigned char *)" sugadintas rezultatø áraðas;") 
#define KPSTLSVR_MSG_TEST_TIMEOUT_LT               ((const unsigned char *)" baigësi sprendimo laikas.")
#define KPSTLSVR_MSG_MESSAGES__LT                  ((const unsigned char *)" pranesimai")
#ifdef KPST_ARKIM
#define KPSTLSVR_MSG_ERROR_HELP_LT                 ((const unsigned char *)"Apie pastebëtas klaidas ar perspëjimus praneðkite adresu arkim@tev.lt")
#else
#define KPSTLSVR_MSG_ERROR_HELP_LT                 ((const unsigned char *)"Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt")
#endif                  
#define KPSTLSVR_MSG_SESSION_STATUS_LT             ((const unsigned char *)"Ryðio seanso bûsena")
#define KPSTLSVR_MSG_NETWORKS_LT                   ((const unsigned char *)" tinklai")
#define KPSTLSVR_MSG_ADMINS_LT                     ((const unsigned char *)" administratoriai")
#define KPSTLSVR_MSG_STATUS__LT                    ((const unsigned char *)" busena")
#define KPSTLSVR_MSG_IP_LIST_LT                    ((const unsigned char *)"Sàraðas IP adresø, ið kuriø leidþiama ")
#define KPSTLSVR_MSG_IP_LIST_SEND_LT               ((const unsigned char *)"siøsti duomenis") // "Sàraðas IP adresø, ið kuriø leidþiama siøsti rezultatus"
// #define KPSTLSVR_MSG_IP_LIST_REGISTER_LT           ((const unsigned char *)"registruotis") // "Sàraðas IP adresø, ið kuriø leidþiama registruoti licencijas"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_LT           ((const unsigned char *)"aktyvuoti darbo vietas")
#define KPSTLSVR_MSG_IP_LIST_ADMIN_LT              ((const unsigned char *)"Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá")
#define KPSTLSVR_MSG_CONNECTIONS_LIST_LT           ((const unsigned char *)"Prisijungimø sàraðas")
#define KPSTLSVR_MSG_SESSION_STARTED_LT            ((const unsigned char *)" seansas pradëtas,")
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_LT         ((const unsigned char *)" siunèiami tarpiniai rezultatai,")
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_LT         ((const unsigned char *)" atsiøsti galutiniai rezultatai,")
#define KPSTLSVR_MSG_SESSION_ABORTED_LT            ((const unsigned char *)" seansas nutrauktas.") // " seansas baigtas."
#define KPSTLSVR_MSG_ABORT_PROMPT_LT               ((const unsigned char *)"Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\"")
#define KPSTLSVR_MSG_IP_HINT_LT                    ((const unsigned char *)"Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255")
#define KPSTLSVR_MSG_PORT_BUSSY_LT                 ((const unsigned char *)"Ryðio kanalas uþimtas, serverio paleisti nepavyko")
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_LT        ((const unsigned char *)"prisijungë administruoti serverá")
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_LT        ((const unsigned char *)"atmestas bandymas administruoti serverá")
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_LT           ((const unsigned char *)" atsiuntë duomenis neuþsiregistravæs")
#define KPSTLSVR_MSG_EXCERCISE_LT                  ((const unsigned char *)"sprendþia uþdaviná ")
#define KPSTLSVR_MSG_EXERCISE_DONE_LT              ((const unsigned char *)"baigë uþdaviná ")
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_LT           ((const unsigned char *)"klientas uþregistruotas") // "licencija priregistruota"
#define KPSTLSVR_MSG_LOGGING_REFUSED_LT            ((const unsigned char *)"kliento registracija atmesta") // "licencijos registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_LT          ((const unsigned char *)"klientas iðregistruotas") // "licencijos registravimas panaikintas"
// #define KPSTLSVR_MSG_RES_LOG_REFUSED_LT            ((const unsigned char *)"rezultatø registravimas/priëmimas atmestas")
#define KPSTLSVR_MSG_RES_LOG_REFUSED_LT            ((const unsigned char *)"rezultatai atmesti")
#define KPSTLSVR_MSG_SERVER_STOPPED_LT             ((const unsigned char *)"Serveris sustabdytas")
#define KPSTLSVR_MSG_SERVER_ABORTED_LT             ((const unsigned char *)"Serveris sustabdytas avariniu bûdu") 
#define KPSTLSVR_MSG_SERVER_ASKED_LT               ((const unsigned char *)"ieðko serverio")
#define KPSTLSVR_MSG_LOG_PROMPT_LT                 ((const unsigned char *)"Iðsamesni praneðimai kaupiami faile %s")
                                                     
#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef kpstlsvr_lt_included
