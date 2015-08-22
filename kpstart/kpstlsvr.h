// -------------------------
// kpstlsvr.h
// definitions of licence server
//


//-------------------------------------------------------------------------
#ifndef kpstlsvr_included
#define kpstlsvr_included


#define KPSTLSVR_MIN_ROW_CNT 21
#define KPST_NUM_OF_CONSOLE_LINES (KPSTLSVR_MIN_ROW_CNT-3)

#define KPST_EXERC_WRAP_THRESHOLD 10

#define KPSTLSVR_REQUEST  ((const unsigned char *)"Kpstlsvr-Request") // datagramm broadcast request
#define KPSTLSVR_ANSWER_OK  ((const unsigned char *)"Kpstlsvr-Ok:")


// --------------------------------------- kpstlsvr messages
enum
{
KPSTLSVR_MSG_SERVER_STARTED_IX,              // "Serveris paleistas"
KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_IX,  // "nutrauktas ankstesnis seansas"
KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_IX,  // "áraðyti nepilni rezultatai"
KPSTLSVR_MSG_RECEIVED_RESULTS_IX,            // " atsiuntë"
KPSTLSVR_MSG_INTERMEDIATE_RES_IX,            // " tarpinius"
KPSTLSVR_MSG_FINAL_RES_IX,                   // " galutinius"
KPSTLSVR_MSG_RESULTS_RECEIVED_IX,            // " rezultatus"
KPSTLSVR_MSG_REGISTERED_IX,                  // " prisiregistravo testo sprendimui"
KPSTLSVR_MSG_SURE_DELETE_MARKED_IX,          // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_IX,     // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
KPSTLSVR_MSG_ERROR_IX,                       // "Klaida: "
KPSTLSVR_MSG_WARNING_IX,                     // "Perspëjimas: "
KPSTLSVR_MSG_CLIENT_STATUS_IX,               // "Kliento bûsena" // "Lic. bûsena"
KPSTLSVR_MSG_STATUS_IX,                      // " busena"
KPSTLSVR_MSG_CLIENTS_STATUS_IX,              // "Klientø bûsena" // "Licencijø bûsena"
KPSTLSVR_MSG_TAB_STATUS_IX,                  // "Bûsena"
KPSTLSVR_MSG_TAB_CLIENTS_IX,                 // "Klientai" // "Licencijos"
KPSTLSVR_MSG_TAB_RESULTS_IX,                 // "Rezultatai"
KPSTLSVR_MSG_TAB_MESSAGES_IX,                // "Praneðimai"
KPSTLSVR_MSG_TAB_NETWORK_IX,                 // "Tinklai"
KPSTLSVR_MSG_TAB_ADMINS_IX,                  // "Administratoriai"
KPSTLSVR_MSG_ORDER_NO_IX,                    // "Eil. Nr."
KPSTLSVR_MSG_SESSION_ID_IX,                  // "Seanso ID"
KPSTLSVR_MSG_CLIENT_IP_IX,                   // "Kliento IP adresas"
KPSTLSVR_MSG_REST_MIN_IX,                    // "Liko min."
KPSTLSVR_MSG_SESSION_ACTIVE_IX,              // " seansas aktyvus," // " licencija uþimta,"
KPSTLSVR_MSG_LOST_CONNECTION_IX,             // " prarastas ryðys su klientu,"
KPSTLSVR_MSG_SLOT_FREE_IX,                   // " galima registruotis." // " licencija laisva."
KPSTLSVR_MSG_REST_MIN__IX,                   // "Liko min. "
KPSTLSVR_MSG_LOST_CLI_TIME_IX,               // " prarastø klientø gyvavimo laikas"
KPSTLSVR_MSG_RESULTS_IX,                     // " rezultatai"
KPSTLSVR_MSG_TEST_RESULTS_IX,                // "Testo rezultatai"
KPSTLSVR_MSG_CLASS_PREFIX_IX,                // "cl. "
KPSTLSVR_MSG_CLASS_POSTFIX_IX,               // " kl."
KPSTLSVR_MSG_RES_FILE_IX,                    // "Rezultatai kaupiami faile "
KPSTLSVR_MSG_BAD_RES_IX,                     // " sugedæ ar kito testo rezultatai;" // " sugedæ ar kito srauto rezultatai;"
KPSTLSVR_MSG_BAD_RES_REC_IX,                 // " sugadintas rezultatø áraðas;" 
KPSTLSVR_MSG_TEST_TIMEOUT_IX,                // " baigësi sprendimo laikas."
KPSTLSVR_MSG_MESSAGES__IX,                   // " pranesimai"
KPSTLSVR_MSG_ERROR_HELP_IX,                  // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
KPSTLSVR_MSG_SESSION_STATUS_IX,              // "Ryðio seanso bûsena"
KPSTLSVR_MSG_NETWORKS_IX,                    // " tinklai"
KPSTLSVR_MSG_ADMINS_IX,                      // " administratoriai"
KPSTLSVR_MSG_STATUS__IX,                     // " busena"
KPSTLSVR_MSG_IP_LIST_IX,                     // "Sàraðas IP adresø, ið kuriø leidþiama "
KPSTLSVR_MSG_IP_LIST_SEND_IX,                // "siøsti duomenis"
KPSTLSVR_MSG_IP_LIST_REGISTER_IX,            // "registruotis"
KPSTLSVR_MSG_IP_LIST_ADMIN_IX,               // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
KPSTLSVR_MSG_CONNECTIONS_LIST_IX,            // "Prisijungimø sàraðas"
KPSTLSVR_MSG_SESSION_STARTED_IX,             // " seansas pradëtas,"
KPSTLSVR_MSG_RESULTS_BEING_SENT_IX,          // " siunèiami tarpiniai rezultatai,"
KPSTLSVR_MSG_FINAL_RESULTS_SENT_IX,          // " atsiøsti galutiniai rezultatai,"
KPSTLSVR_MSG_SESSION_ABORTED_IX,             // " seansas nutrauktas."
KPSTLSVR_MSG_ABORT_PROMPT_IX,                // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
KPSTLSVR_MSG_IP_HINT_IX,                     // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255"
KPSTLSVR_MSG_PORT_BUSSY_IX,                  // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
KPSTLSVR_MSG_MAINTENANCE_STARTED_IX,         // "prisijungë administruoti serverá"
KPSTLSVR_MSG_MAINTENANCE_REFUSED_IX,         // "atmestas bandymas administruoti serverá"
KPSTLSVR_MSG_UNLOGGED_RESULTS_IX,            // " atsiuntë duomenis neuþsiregistravæs"
KPSTLSVR_MSG_EXCERCISE_IX,                   // "sprendþia uþdaviná "
KPSTLSVR_MSG_EXERCISE_DONE_IX,               // "baigë uþdaviná "
KPSTLSVR_MSG_CLIENT_LOGGED_IN_IX,            // "klientas uþregistruotas"
KPSTLSVR_MSG_LOGGING_REFUSED_IX,             // "kliento registravimas atmestas"
KPSTLSVR_MSG_CLIENT_LOGGED_OFF_IX,           // "klientas iðregistruotas"
KPSTLSVR_MSG_RES_LOG_REFUSED_IX,             // "rezultatø registravimas/priëmimas atmestas"
KPSTLSVR_MSG_SERVER_STOPPED_IX,              // "Serveris sustabdytas"
KPSTLSVR_MSG_SERVER_ABORTED_IX,              // "Serveris sustabdytas avariniu bûdu" 
KPSTLSVR_MSG_SERVER_ASKED_IX,                // "ieðko serverio"
KPSTLSVR_MSG_LOG_PROMPT_IX,                  // "Iðsamesni praneðimai kaupiami faile %s"

NumOfKpStlSvrMessages
};

#define NumOfKpStlSvrMessages_1 NumOfKpStlSvrMessages
 
extern const unsigned char *lpszaKpStlSvrMessages[NumOfKpStlSvrMessages][KpNumOfLangs];

// -----------------------------------------
#define KPSTLSVR_MSG_SERVER_STARTED             lpszaKpStlSvrMessages[KPSTLSVR_MSG_SERVER_STARTED_IX             ][iMsgLangOff] // "Serveris paleistas"
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED lpszaKpStlSvrMessages[KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_IX ][iMsgLangOff] // "nutrauktas ankstesnis seansas"
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN lpszaKpStlSvrMessages[KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_IX ][iMsgLangOff] // "áraðyti nepilni rezultatai"
#define KPSTLSVR_MSG_RECEIVED_RESULTS           lpszaKpStlSvrMessages[KPSTLSVR_MSG_RECEIVED_RESULTS_IX           ][iMsgLangOff] // " atsiuntë"
#define KPSTLSVR_MSG_INTERMEDIATE_RES           lpszaKpStlSvrMessages[KPSTLSVR_MSG_INTERMEDIATE_RES_IX           ][iMsgLangOff] // " tarpinius"
#define KPSTLSVR_MSG_FINAL_RES                  lpszaKpStlSvrMessages[KPSTLSVR_MSG_FINAL_RES_IX                  ][iMsgLangOff] // " galutinius"
#define KPSTLSVR_MSG_RESULTS_RECEIVED           lpszaKpStlSvrMessages[KPSTLSVR_MSG_RESULTS_RECEIVED_IX           ][iMsgLangOff] // " rezultatus"
#define KPSTLSVR_MSG_REGISTERED                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_REGISTERED_IX                 ][iMsgLangOff] // " prisiregistravo testo sprendimui"
#define KPSTLSVR_MSG_SURE_DELETE_MARKED         lpszaKpStlSvrMessages[KPSTLSVR_MSG_SURE_DELETE_MARKED_IX         ][iMsgLangOff] // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS    lpszaKpStlSvrMessages[KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_IX    ][iMsgLangOff] // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
#define KPSTLSVR_MSG_ERROR                      lpszaKpStlSvrMessages[KPSTLSVR_MSG_ERROR_IX                      ][iMsgLangOff] // "Klaida: "
#define KPSTLSVR_MSG_WARNING                    lpszaKpStlSvrMessages[KPSTLSVR_MSG_WARNING_IX                    ][iMsgLangOff] // "Perspëjimas: "
#define KPSTLSVR_MSG_CLIENT_STATUS              lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLIENT_STATUS_IX              ][iMsgLangOff] // "Kliento bûsena"
#define KPSTLSVR_MSG_STATUS                     lpszaKpStlSvrMessages[KPSTLSVR_MSG_STATUS_IX                     ][iMsgLangOff] // " busena"
#define KPSTLSVR_MSG_CLIENTS_STATUS             lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLIENTS_STATUS_IX             ][iMsgLangOff] // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_STATUS                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_STATUS_IX                 ][iMsgLangOff] // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_CLIENTS                lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_CLIENTS_IX                ][iMsgLangOff] // "Klientai"
#define KPSTLSVR_MSG_TAB_RESULTS                lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_RESULTS_IX                ][iMsgLangOff] // "Rezultatai"
#define KPSTLSVR_MSG_TAB_MESSAGES               lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_MESSAGES_IX               ][iMsgLangOff] // "Praneðimai"
#define KPSTLSVR_MSG_MESSAGES                   KPSTLSVR_MSG_TAB_MESSAGES
#define KPSTLSVR_MSG_TAB_NETWORK                lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_NETWORK_IX                ][iMsgLangOff] // "Tinklai"
#define KPSTLSVR_MSG_TAB_ADMINS                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_ADMINS_IX                 ][iMsgLangOff] // "Administratoriai"
#define KPSTLSVR_MSG_ORDER_NO                   lpszaKpStlSvrMessages[KPSTLSVR_MSG_ORDER_NO_IX                   ][iMsgLangOff] // "Eil. Nr."
#define KPSTLSVR_MSG_SESSION_ID                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_SESSION_ID_IX                 ][iMsgLangOff] // "Seanso ID"
#define KPSTLSVR_MSG_CLIENT_IP                  lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLIENT_IP_IX                  ][iMsgLangOff] // "Kliento IP adresas"
#define KPSTLSVR_MSG_REST_MIN                   lpszaKpStlSvrMessages[KPSTLSVR_MSG_REST_MIN_IX                   ][iMsgLangOff] // "Liko min."
#define KPSTLSVR_MSG_SESSION_ACTIVE             lpszaKpStlSvrMessages[KPSTLSVR_MSG_SESSION_ACTIVE_IX             ][iMsgLangOff] // " seansas aktyvus,"
#define KPSTLSVR_MSG_LOST_CONNECTION            lpszaKpStlSvrMessages[KPSTLSVR_MSG_LOST_CONNECTION_IX            ][iMsgLangOff] // " prarastas ryðys su klientu,"
#define KPSTLSVR_MSG_SLOT_FREE                  lpszaKpStlSvrMessages[KPSTLSVR_MSG_SLOT_FREE_IX                  ][iMsgLangOff] // " galima registruotis."
#define KPSTLSVR_MSG_REST_MIN_                  lpszaKpStlSvrMessages[KPSTLSVR_MSG_REST_MIN__IX                  ][iMsgLangOff] // "Liko min. "
#define KPSTLSVR_MSG_LOST_CLI_TIME              lpszaKpStlSvrMessages[KPSTLSVR_MSG_LOST_CLI_TIME_IX              ][iMsgLangOff] // " prarastø klientø gyvavimo laikas"
#define KPSTLSVR_MSG_RESULTS                    lpszaKpStlSvrMessages[KPSTLSVR_MSG_RESULTS_IX                    ][iMsgLangOff] // " rezultatai"
#define KPSTLSVR_MSG_TEST_RESULTS               lpszaKpStlSvrMessages[KPSTLSVR_MSG_TEST_RESULTS_IX               ][iMsgLangOff] // "Testo rezultatai"
#define KPSTLSVR_MSG_CLASS_PREFIX               lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLASS_PREFIX_IX               ][iMsgLangOff] // "cl. "
#define KPSTLSVR_MSG_CLASS_POSTFIX              lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLASS_POSTFIX_IX              ][iMsgLangOff] // " kl."
#define KPSTLSVR_MSG_RES_FILE                   lpszaKpStlSvrMessages[KPSTLSVR_MSG_RES_FILE_IX                   ][iMsgLangOff] // "Rezultatai kaupiami faile "
#define KPSTLSVR_MSG_BAD_RES                    lpszaKpStlSvrMessages[KPSTLSVR_MSG_BAD_RES_IX                    ][iMsgLangOff] // " sugedæ ar kito testo rezultatai;"
#define KPSTLSVR_MSG_BAD_RES_REC                lpszaKpStlSvrMessages[KPSTLSVR_MSG_BAD_RES_REC_IX                ][iMsgLangOff] // " sugadintas rezultatø áraðas;"
#define KPSTLSVR_MSG_TEST_TIMEOUT               lpszaKpStlSvrMessages[KPSTLSVR_MSG_TEST_TIMEOUT_IX               ][iMsgLangOff] // " baigësi sprendimo laikas."
#define KPSTLSVR_MSG_MESSAGES_                  lpszaKpStlSvrMessages[KPSTLSVR_MSG_MESSAGES__IX                  ][iMsgLangOff] // " pranesimai"
#define KPSTLSVR_MSG_ERROR_HELP                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_ERROR_HELP_IX                 ][iMsgLangOff] // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
#define KPSTLSVR_MSG_SESSION_STATUS             lpszaKpStlSvrMessages[KPSTLSVR_MSG_SESSION_STATUS_IX             ][iMsgLangOff] // "Ryðio seanso bûsena"
#define KPSTLSVR_MSG_NETWORKS                   lpszaKpStlSvrMessages[KPSTLSVR_MSG_NETWORKS_IX                   ][iMsgLangOff] // " tinklai"
#define KPSTLSVR_MSG_ADMINS                     lpszaKpStlSvrMessages[KPSTLSVR_MSG_ADMINS_IX                     ][iMsgLangOff] // " administratoriai"
#define KPSTLSVR_MSG_STATUS_                    lpszaKpStlSvrMessages[KPSTLSVR_MSG_STATUS__IX                    ][iMsgLangOff] // " busena"
#define KPSTLSVR_MSG_IP_LIST                    lpszaKpStlSvrMessages[KPSTLSVR_MSG_IP_LIST_IX                    ][iMsgLangOff] // "Sàraðas IP adresø, ið kuriø leidþiama "
#define KPSTLSVR_MSG_IP_LIST_SEND               lpszaKpStlSvrMessages[KPSTLSVR_MSG_IP_LIST_SEND_IX               ][iMsgLangOff] // "siøsti duomenis"
#define KPSTLSVR_MSG_IP_LIST_REGISTER           lpszaKpStlSvrMessages[KPSTLSVR_MSG_IP_LIST_REGISTER_IX           ][iMsgLangOff] // "registruotis"
#define KPSTLSVR_MSG_IP_LIST_ADMIN              lpszaKpStlSvrMessages[KPSTLSVR_MSG_IP_LIST_ADMIN_IX              ][iMsgLangOff] // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
#define KPSTLSVR_MSG_CONNECTIONS_LIST           lpszaKpStlSvrMessages[KPSTLSVR_MSG_CONNECTIONS_LIST_IX           ][iMsgLangOff] // "Prisijungimø sàraðas"
#define KPSTLSVR_MSG_SESSION_STARTED            lpszaKpStlSvrMessages[KPSTLSVR_MSG_SESSION_STARTED_IX            ][iMsgLangOff] // " seansas pradëtas,"
#define KPSTLSVR_MSG_RESULTS_BEING_SENT         lpszaKpStlSvrMessages[KPSTLSVR_MSG_RESULTS_BEING_SENT_IX         ][iMsgLangOff] // " siunèiami tarpiniai rezultatai,"
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT         lpszaKpStlSvrMessages[KPSTLSVR_MSG_FINAL_RESULTS_SENT_IX         ][iMsgLangOff] // " atsiøsti galutiniai rezultatai,"
#define KPSTLSVR_MSG_SESSION_ABORTED            lpszaKpStlSvrMessages[KPSTLSVR_MSG_SESSION_ABORTED_IX            ][iMsgLangOff] // " seansas nutrauktas."
#define KPSTLSVR_MSG_ABORT_PROMPT               lpszaKpStlSvrMessages[KPSTLSVR_MSG_ABORT_PROMPT_IX               ][iMsgLangOff] // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
#define KPSTLSVR_MSG_IP_HINT                    lpszaKpStlSvrMessages[KPSTLSVR_MSG_IP_HINT_IX                    ][iMsgLangOff] // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255"
#define KPSTLSVR_MSG_PORT_BUSSY                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_PORT_BUSSY_IX                 ][iMsgLangOff] // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
#define KPSTLSVR_MSG_MAINTENANCE_STARTED        lpszaKpStlSvrMessages[KPSTLSVR_MSG_MAINTENANCE_STARTED_IX        ][iMsgLangOff] // "prisijungë administruoti serverá"
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED        lpszaKpStlSvrMessages[KPSTLSVR_MSG_MAINTENANCE_REFUSED_IX        ][iMsgLangOff] // "atmestas bandymas administruoti serverá"
#define KPSTLSVR_MSG_UNLOGGED_RESULTS           lpszaKpStlSvrMessages[KPSTLSVR_MSG_UNLOGGED_RESULTS_IX           ][iMsgLangOff] // " atsiuntë duomenis neuþsiregistravæs"
#define KPSTLSVR_MSG_EXCERCISE                  lpszaKpStlSvrMessages[KPSTLSVR_MSG_EXCERCISE_IX                  ][iMsgLangOff] // "sprendþia uþdaviná "
#define KPSTLSVR_MSG_EXERCISE_DONE              lpszaKpStlSvrMessages[KPSTLSVR_MSG_EXERCISE_DONE_IX              ][iMsgLangOff] // "baigë uþdaviná "
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN           lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLIENT_LOGGED_IN_IX           ][iMsgLangOff] // "klientas uþregistruotas"
#define KPSTLSVR_MSG_LOGGING_REFUSED            lpszaKpStlSvrMessages[KPSTLSVR_MSG_LOGGING_REFUSED_IX            ][iMsgLangOff] // "kliento registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF          lpszaKpStlSvrMessages[KPSTLSVR_MSG_CLIENT_LOGGED_OFF_IX          ][iMsgLangOff] // "klientas iðregistruotas"
#define KPSTLSVR_MSG_RES_LOG_REFUSED            lpszaKpStlSvrMessages[KPSTLSVR_MSG_RES_LOG_REFUSED_IX            ][iMsgLangOff] // "rezultatø registravimas/priëmimas atmestas"
#define KPSTLSVR_MSG_SERVER_STOPPED             lpszaKpStlSvrMessages[KPSTLSVR_MSG_SERVER_STOPPED_IX             ][iMsgLangOff] // "Serveris sustabdytas"
#define KPSTLSVR_MSG_SERVER_ABORTED             lpszaKpStlSvrMessages[KPSTLSVR_MSG_SERVER_ABORTED_IX             ][iMsgLangOff] // "Serveris sustabdytas avariniu bûdu"
#define KPSTLSVR_MSG_SERVER_ASKED               lpszaKpStlSvrMessages[KPSTLSVR_MSG_SERVER_ASKED_IX               ][iMsgLangOff] // "ieðko serverio"
#define KPSTLSVR_MSG_LOG_PROMPT                 lpszaKpStlSvrMessages[KPSTLSVR_MSG_LOG_PROMPT_IX                 ][iMsgLangOff] // "Iðsamesni praneðimai kaupiami faile %s"

// -----------------------------------------------
#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define KPSTLSVR_MSG_SERVER_STARTED_EN             ((const unsigned char *)"") // "Serveris paleistas"
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_EN ((const unsigned char *)"") // "nutrauktas ankstesnis seansas"
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_EN ((const unsigned char *)"") // "áraðyti nepilni rezultatai"
#define KPSTLSVR_MSG_RECEIVED_RESULTS_EN           ((const unsigned char *)"") // " atsiuntë"
#define KPSTLSVR_MSG_INTERMEDIATE_RES_EN           ((const unsigned char *)"") // " tarpinius"
#define KPSTLSVR_MSG_FINAL_RES_EN                  ((const unsigned char *)"") // " galutinius"
#define KPSTLSVR_MSG_RESULTS_RECEIVED_EN           ((const unsigned char *)"") // " rezultatus"
#define KPSTLSVR_MSG_REGISTERED_EN                 ((const unsigned char *)"") // " prisiregistravo testo sprendimui"
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_EN         ((const unsigned char *)"            confirm(\"\");\n") // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_EN    ((const unsigned char *)"   confirm(\"\");\n") // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
#define KPSTLSVR_MSG_ERROR_EN                      ((const unsigned char *)"") // "Klaida: "
#define KPSTLSVR_MSG_WARNING_EN                    ((const unsigned char *)"") // "Perspëjimas: "
#define KPSTLSVR_MSG_CLIENT_STATUS_EN              ((const unsigned char *)"") // "Kliento bûsena"
#define KPSTLSVR_MSG_STATUS_EN                     ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_CLIENTS_STATUS_EN             ((const unsigned char *)"") // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_STATUS_EN                 ((const unsigned char *)"") // "Bûsena"
#define KPSTLSVR_MSG_TAB_CLIENTS_EN                ((const unsigned char *)"") // "Klientai"
#define KPSTLSVR_MSG_TAB_RESULTS_EN                ((const unsigned char *)"") // "Rezultatai"
#define KPSTLSVR_MSG_TAB_MESSAGES_EN               ((const unsigned char *)"") // "Praneðimai"
#define KPSTLSVR_MSG_TAB_NETWORK_EN                ((const unsigned char *)"") // "Tinklai"
#define KPSTLSVR_MSG_TAB_ADMINS_EN                 ((const unsigned char *)"") // "Administratoriai"
#define KPSTLSVR_MSG_ORDER_NO_EN                   ((const unsigned char *)"") // "Eil. Nr."
#define KPSTLSVR_MSG_SESSION_ID_EN                 ((const unsigned char *)"") // "Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_EN                  ((const unsigned char *)"") // "Kliento IP adresas"
#define KPSTLSVR_MSG_REST_MIN_EN                   ((const unsigned char *)"") // "Liko min."
#define KPSTLSVR_MSG_SESSION_ACTIVE_EN             ((const unsigned char *)"") // " seansas aktyvus,"
#define KPSTLSVR_MSG_LOST_CONNECTION_EN            ((const unsigned char *)"") // " prarastas ryðys su klientu,"
#define KPSTLSVR_MSG_SLOT_FREE_EN                  ((const unsigned char *)"") // " galima registruotis."
#define KPSTLSVR_MSG_REST_MIN__EN                  ((const unsigned char *)"") // "Liko min. "
#define KPSTLSVR_MSG_LOST_CLI_TIME_EN              ((const unsigned char *)"") // " prarastø klientø gyvavimo laikas"
#define KPSTLSVR_MSG_RESULTS_EN                    ((const unsigned char *)"") // " rezultatai"
#define KPSTLSVR_MSG_TEST_RESULTS_EN               ((const unsigned char *)"") // "Testo rezultatai"
#define KPSTLSVR_MSG_CLASS_PREFIX_EN               ((const unsigned char *)"") // "cl. "
#define KPSTLSVR_MSG_CLASS_POSTFIX_EN              ((const unsigned char *)"") // " kl."
#define KPSTLSVR_MSG_RES_FILE_EN                   ((const unsigned char *)"") // "Rezultatai kaupiami faile "
#define KPSTLSVR_MSG_BAD_RES_EN                    ((const unsigned char *)"") // " sugedæ ar kito testo rezultatai;"
#define KPSTLSVR_MSG_BAD_RES_REC_EN                ((const unsigned char *)"") // " sugadintas rezultatø áraðas;" 
#define KPSTLSVR_MSG_TEST_TIMEOUT_EN               ((const unsigned char *)"") // " baigësi sprendimo laikas."
#define KPSTLSVR_MSG_MESSAGES__EN                  ((const unsigned char *)"") // " pranesimai"
#define KPSTLSVR_MSG_ERROR_HELP_EN                 ((const unsigned char *)"") // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
#define KPSTLSVR_MSG_SESSION_STATUS_EN             ((const unsigned char *)"") // "Ryðio seanso bûsena"
#define KPSTLSVR_MSG_NETWORKS_EN                   ((const unsigned char *)"") // " tinklai"
#define KPSTLSVR_MSG_ADMINS_EN                     ((const unsigned char *)"") // " administratoriai"
#define KPSTLSVR_MSG_STATUS__EN                    ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_IP_LIST_EN                    ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama "
#define KPSTLSVR_MSG_IP_LIST_SEND_EN               ((const unsigned char *)"") // "siøsti duomenis"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_EN           ((const unsigned char *)"") // "registruotis"
#define KPSTLSVR_MSG_IP_LIST_ADMIN_EN              ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
#define KPSTLSVR_MSG_CONNECTIONS_LIST_EN           ((const unsigned char *)"") // "Prisijungimø sàraðas"
#define KPSTLSVR_MSG_SESSION_STARTED_EN            ((const unsigned char *)"") // " seansas pradëtas,"
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_EN         ((const unsigned char *)"") // " siunèiami tarpiniai rezultatai,"
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_EN         ((const unsigned char *)"") // " atsiøsti galutiniai rezultatai,"
#define KPSTLSVR_MSG_SESSION_ABORTED_EN            ((const unsigned char *)"") // " seansas nutrauktas."
#define KPSTLSVR_MSG_ABORT_PROMPT_EN               ((const unsigned char *)"") // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
#define KPSTLSVR_MSG_IP_HINT_EN                    ((const unsigned char *)"") // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255")
#define KPSTLSVR_MSG_PORT_BUSSY_EN                 ((const unsigned char *)"") // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_EN        ((const unsigned char *)"") // "prisijungë administruoti serverá"
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_EN        ((const unsigned char *)"") // "atmestas bandymas administruoti serverá"
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_EN           ((const unsigned char *)"") // " atsiuntë duomenis neuþsiregistravæs"
#define KPSTLSVR_MSG_EXCERCISE_EN                  ((const unsigned char *)"") // "sprendþia uþdaviná "
#define KPSTLSVR_MSG_EXERCISE_DONE_EN              ((const unsigned char *)"") // "baigë uþdaviná "
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_EN           ((const unsigned char *)"") // "klientas uþregistruotas"
#define KPSTLSVR_MSG_LOGGING_REFUSED_EN            ((const unsigned char *)"") // "kliento registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_EN          ((const unsigned char *)"") // "klientas iðregistruotas"
#define KPSTLSVR_MSG_RES_LOG_REFUSED_EN            ((const unsigned char *)"") // "rezultatø registravimas/priëmimas atmestas"
#define KPSTLSVR_MSG_SERVER_STOPPED_EN             ((const unsigned char *)"") // "Serveris sustabdytas"
#define KPSTLSVR_MSG_SERVER_ABORTED_EN             ((const unsigned char *)"") // "Serveris sustabdytas avariniu bûdu" 
#define KPSTLSVR_MSG_SERVER_ASKED_EN               ((const unsigned char *)"") // "ieðko serverio"
#define KPSTLSVR_MSG_LOG_PROMPT_EN                 ((const unsigned char *)"") // "Iðsamesni praneðimai kaupiami faile %s"

#endif // #if ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

// -----------------------------------------------
#if (((MsgLang) != KpLangSel_p) && ((MsgLang) != KpLangLt_p))

#define KPSTLSVR_MSG_SERVER_STARTED_LT             ((const unsigned char *)"") // "Serveris paleistas")
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_LT ((const unsigned char *)"") // "nutrauktas ankstesnis seansas"
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_LT ((const unsigned char *)"") // "áraðyti nepilni rezultatai"
#define KPSTLSVR_MSG_RECEIVED_RESULTS_LT           ((const unsigned char *)"") // " atsiuntë"
#define KPSTLSVR_MSG_INTERMEDIATE_RES_LT           ((const unsigned char *)"") // " tarpinius"
#define KPSTLSVR_MSG_FINAL_RES_LT                  ((const unsigned char *)"") // " galutinius"
#define KPSTLSVR_MSG_RESULTS_RECEIVED_LT           ((const unsigned char *)"") // " rezultatus"
#define KPSTLSVR_MSG_REGISTERED_LT                 ((const unsigned char *)"") // " prisiregistravo testo sprendimui"
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_LT         ((const unsigned char *)"            confirm(\"\");\n") // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_LT    ((const unsigned char *)"   confirm(\"\");\n") // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
#define KPSTLSVR_MSG_ERROR_LT                      ((const unsigned char *)"") // "Klaida: "
#define KPSTLSVR_MSG_WARNING_LT                    ((const unsigned char *)"") // "Perspëjimas: "
#define KPSTLSVR_MSG_CLIENT_STATUS_LT              ((const unsigned char *)"") // "Kliento bûsena"
#define KPSTLSVR_MSG_STATUS_LT                     ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_CLIENTS_STATUS_LT             ((const unsigned char *)"") // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_STATUS_LT                 ((const unsigned char *)"") // "Bûsena"
#define KPSTLSVR_MSG_TAB_CLIENTS_LT                ((const unsigned char *)"") // "Klientai"
#define KPSTLSVR_MSG_TAB_RESULTS_LT                ((const unsigned char *)"") // "Rezultatai"
#define KPSTLSVR_MSG_TAB_MESSAGES_LT               ((const unsigned char *)"") // "Praneðimai"
#define KPSTLSVR_MSG_TAB_NETWORK_LT                ((const unsigned char *)"") // "Tinklai"
#define KPSTLSVR_MSG_TAB_ADMINS_LT                 ((const unsigned char *)"") // "Administratoriai"
#define KPSTLSVR_MSG_ORDER_NO_LT                   ((const unsigned char *)"") // "Eil. Nr."
#define KPSTLSVR_MSG_SESSION_ID_LT                 ((const unsigned char *)"") // "Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_LT                  ((const unsigned char *)"") // "Kliento IP adresas"
#define KPSTLSVR_MSG_REST_MIN_LT                   ((const unsigned char *)"") // "Liko min."
#define KPSTLSVR_MSG_SESSION_ACTIVE_LT             ((const unsigned char *)"") // " seansas aktyvus,"
#define KPSTLSVR_MSG_LOST_CONNECTION_LT            ((const unsigned char *)"") // " prarastas ryðys su klientu,"
#define KPSTLSVR_MSG_SLOT_FREE_LT                  ((const unsigned char *)"") // " galima registruotis."
#define KPSTLSVR_MSG_REST_MIN__LT                  ((const unsigned char *)"") // "Liko min. "
#define KPSTLSVR_MSG_LOST_CLI_TIME_LT              ((const unsigned char *)"") // " prarastø klientø gyvavimo laikas"
#define KPSTLSVR_MSG_RESULTS_LT                    ((const unsigned char *)"") // " rezultatai"
#define KPSTLSVR_MSG_TEST_RESULTS_LT               ((const unsigned char *)"") // "Testo rezultatai"
#define KPSTLSVR_MSG_CLASS_PREFIX_LT               ((const unsigned char *)"") // "cl. "
#define KPSTLSVR_MSG_CLASS_POSTFIX_LT              ((const unsigned char *)"") // " kl."
#define KPSTLSVR_MSG_RES_FILE_LT                   ((const unsigned char *)"") // "Rezultatai kaupiami faile "
#define KPSTLSVR_MSG_BAD_RES_LT                    ((const unsigned char *)"") // " sugedæ ar kito testo rezultatai;"
#define KPSTLSVR_MSG_BAD_RES_REC_LT                ((const unsigned char *)"") // " sugadintas rezultatø áraðas;" 
#define KPSTLSVR_MSG_TEST_TIMEOUT_LT               ((const unsigned char *)"") // " baigësi sprendimo laikas."
#define KPSTLSVR_MSG_MESSAGES__LT                  ((const unsigned char *)"") // " pranesimai"
#define KPSTLSVR_MSG_ERROR_HELP_LT                 ((const unsigned char *)"") // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
#define KPSTLSVR_MSG_SESSION_STATUS_LT             ((const unsigned char *)"") // "Ryðio seanso bûsena"
#define KPSTLSVR_MSG_NETWORKS_LT                   ((const unsigned char *)"") // " tinklai"
#define KPSTLSVR_MSG_ADMINS_LT                     ((const unsigned char *)"") // " administratoriai"
#define KPSTLSVR_MSG_STATUS__LT                    ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_IP_LIST_LT                    ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama "
#define KPSTLSVR_MSG_IP_LIST_SEND_LT               ((const unsigned char *)"") // "siøsti duomenis"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_LT           ((const unsigned char *)"") // "registruotis"
#define KPSTLSVR_MSG_IP_LIST_ADMIN_LT              ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
#define KPSTLSVR_MSG_CONNECTIONS_LIST_LT           ((const unsigned char *)"") // "Prisijungimø sàraðas"
#define KPSTLSVR_MSG_SESSION_STARTED_LT            ((const unsigned char *)"") // " seansas pradëtas,"
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_LT         ((const unsigned char *)"") // " siunèiami tarpiniai rezultatai,"
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_LT         ((const unsigned char *)"") // " atsiøsti galutiniai rezultatai,"
#define KPSTLSVR_MSG_SESSION_ABORTED_LT            ((const unsigned char *)"") // " seansas nutrauktas."
#define KPSTLSVR_MSG_ABORT_PROMPT_LT               ((const unsigned char *)"") // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
#define KPSTLSVR_MSG_IP_HINT_LT                    ((const unsigned char *)"") // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255")
#define KPSTLSVR_MSG_PORT_BUSSY_LT                 ((const unsigned char *)"") // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_LT        ((const unsigned char *)"") // "prisijungë administruoti serverá")
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_LT        ((const unsigned char *)"") // "atmestas bandymas administruoti serverá"
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_LT           ((const unsigned char *)"") // " atsiuntë duomenis neuþsiregistravæs"
#define KPSTLSVR_MSG_EXCERCISE_LT                  ((const unsigned char *)"") // "sprendþia uþdaviná "
#define KPSTLSVR_MSG_EXERCISE_DONE_LT              ((const unsigned char *)"") // "baigë uþdaviná "
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_LT           ((const unsigned char *)"") // "klientas uþregistruotas"
#define KPSTLSVR_MSG_LOGGING_REFUSED_LT            ((const unsigned char *)"") // "kliento registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_LT          ((const unsigned char *)"") // "klientas iðregistruotas"
#define KPSTLSVR_MSG_RES_LOG_REFUSED_LT            ((const unsigned char *)"") // "rezultatø registravimas/priëmimas atmestas"
#define KPSTLSVR_MSG_SERVER_STOPPED_LT             ((const unsigned char *)"") // "Serveris sustabdytas"
#define KPSTLSVR_MSG_SERVER_ABORTED_LT             ((const unsigned char *)"") // "Serveris sustabdytas avariniu bûdu" 
#define KPSTLSVR_MSG_SERVER_ASKED_LT               ((const unsigned char *)"") // "ieðko serverio"
#define KPSTLSVR_MSG_LOG_PROMPT_LT                 ((const unsigned char *)"") // "Iðsamesni praneðimai kaupiami faile %s"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

// -----------------------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define KPSTLSVR_MSG_SERVER_STARTED_PL_1250              ((const unsigned char *)"") // "Serveris paleistas")
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_PL_1250  ((const unsigned char *)"") // "nutrauktas ankstesnis seansas"
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_PL_1250  ((const unsigned char *)"") // "áraðyti nepilni rezultatai"
#define KPSTLSVR_MSG_RECEIVED_RESULTS_PL_1250            ((const unsigned char *)"") // " atsiuntë"
#define KPSTLSVR_MSG_INTERMEDIATE_RES_PL_1250            ((const unsigned char *)"") // " tarpinius"
#define KPSTLSVR_MSG_FINAL_RES_PL_1250                   ((const unsigned char *)"") // " galutinius"
#define KPSTLSVR_MSG_RESULTS_RECEIVED_PL_1250            ((const unsigned char *)"") // " rezultatus"
#define KPSTLSVR_MSG_REGISTERED_PL_1250                  ((const unsigned char *)"") // " prisiregistravo testo sprendimui"
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_PL_1250          ((const unsigned char *)"            confirm(\"\");\n") // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_PL_1250     ((const unsigned char *)"   confirm(\"\");\n") // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
#define KPSTLSVR_MSG_ERROR_PL_1250                       ((const unsigned char *)"") // "Klaida: "
#define KPSTLSVR_MSG_WARNING_PL_1250                     ((const unsigned char *)"") // "Perspëjimas: "
#define KPSTLSVR_MSG_CLIENT_STATUS_PL_1250               ((const unsigned char *)"") // "Kliento bûsena"
#define KPSTLSVR_MSG_STATUS_PL_1250                      ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_CLIENTS_STATUS_PL_1250              ((const unsigned char *)"") // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_STATUS_PL_1250                  ((const unsigned char *)"") // "Bûsena"
#define KPSTLSVR_MSG_TAB_CLIENTS_PL_1250                 ((const unsigned char *)"") // "Klientai"
#define KPSTLSVR_MSG_TAB_RESULTS_PL_1250                 ((const unsigned char *)"") // "Rezultatai"
#define KPSTLSVR_MSG_TAB_MESSAGES_PL_1250                ((const unsigned char *)"") // "Praneðimai"
#define KPSTLSVR_MSG_TAB_NETWORK_PL_1250                 ((const unsigned char *)"") // "Tinklai"
#define KPSTLSVR_MSG_TAB_ADMINS_PL_1250                  ((const unsigned char *)"") // "Administratoriai"
#define KPSTLSVR_MSG_ORDER_NO_PL_1250                    ((const unsigned char *)"") // "Eil. Nr."
#define KPSTLSVR_MSG_SESSION_ID_PL_1250                  ((const unsigned char *)"") // "Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_PL_1250                   ((const unsigned char *)"") // "Kliento IP adresas"
#define KPSTLSVR_MSG_REST_MIN_PL_1250                    ((const unsigned char *)"") // "Liko min."
#define KPSTLSVR_MSG_SESSION_ACTIVE_PL_1250              ((const unsigned char *)"") // " seansas aktyvus,"
#define KPSTLSVR_MSG_LOST_CONNECTION_PL_1250             ((const unsigned char *)"") // " prarastas ryðys su klientu,"
#define KPSTLSVR_MSG_SLOT_FREE_PL_1250                   ((const unsigned char *)"") // " galima registruotis."
#define KPSTLSVR_MSG_REST_MIN__PL_1250                   ((const unsigned char *)"") // "Liko min. "
#define KPSTLSVR_MSG_LOST_CLI_TIME_PL_1250               ((const unsigned char *)"") // " prarastø klientø gyvavimo laikas"
#define KPSTLSVR_MSG_RESULTS_PL_1250                     ((const unsigned char *)"") // " rezultatai"
#define KPSTLSVR_MSG_TEST_RESULTS_PL_1250                ((const unsigned char *)"") // "Testo rezultatai"
#define KPSTLSVR_MSG_CLASS_PREFIX_PL_1250                ((const unsigned char *)"") // "cl. "
#define KPSTLSVR_MSG_CLASS_POSTFIX_PL_1250               ((const unsigned char *)"") // " kl."
#define KPSTLSVR_MSG_RES_FILE_PL_1250                    ((const unsigned char *)"") // "Rezultatai kaupiami faile "
#define KPSTLSVR_MSG_BAD_RES_PL_1250                     ((const unsigned char *)"") // " sugedæ ar kito testo rezultatai;"
#define KPSTLSVR_MSG_BAD_RES_REC_PL_1250                 ((const unsigned char *)"") // " sugadintas rezultatø áraðas;" 
#define KPSTLSVR_MSG_TEST_TIMEOUT_PL_1250                ((const unsigned char *)"") // " baigësi sprendimo laikas."
#define KPSTLSVR_MSG_MESSAGES__PL_1250                   ((const unsigned char *)"") // " pranesimai"
#define KPSTLSVR_MSG_ERROR_HELP_PL_1250                  ((const unsigned char *)"") // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
#define KPSTLSVR_MSG_SESSION_STATUS_PL_1250              ((const unsigned char *)"") // "Ryðio seanso bûsena"
#define KPSTLSVR_MSG_NETWORKS_PL_1250                    ((const unsigned char *)"") // " tinklai"
#define KPSTLSVR_MSG_ADMINS_PL_1250                      ((const unsigned char *)"") // " administratoriai"
#define KPSTLSVR_MSG_STATUS__PL_1250                     ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_IP_LIST_PL_1250                     ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama "
#define KPSTLSVR_MSG_IP_LIST_SEND_PL_1250                ((const unsigned char *)"") // "siøsti duomenis"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_PL_1250            ((const unsigned char *)"") // "registruotis"
#define KPSTLSVR_MSG_IP_LIST_ADMIN_PL_1250               ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
#define KPSTLSVR_MSG_CONNECTIONS_LIST_PL_1250            ((const unsigned char *)"") // "Prisijungimø sàraðas"
#define KPSTLSVR_MSG_SESSION_STARTED_PL_1250             ((const unsigned char *)"") // " seansas pradëtas,"
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_PL_1250          ((const unsigned char *)"") // " siunèiami tarpiniai rezultatai,"
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_PL_1250          ((const unsigned char *)"") // " atsiøsti galutiniai rezultatai,"
#define KPSTLSVR_MSG_SESSION_ABORTED_PL_1250             ((const unsigned char *)"") // " seansas nutrauktas."
#define KPSTLSVR_MSG_ABORT_PROMPT_PL_1250                ((const unsigned char *)"") // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
#define KPSTLSVR_MSG_IP_HINT_PL_1250                     ((const unsigned char *)"") // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255")
#define KPSTLSVR_MSG_PORT_BUSSY_PL_1250                  ((const unsigned char *)"") // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_PL_1250         ((const unsigned char *)"") // "prisijungë administruoti serverá")
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_PL_1250         ((const unsigned char *)"") // "atmestas bandymas administruoti serverá"
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_PL_1250            ((const unsigned char *)"") // " atsiuntë duomenis neuþsiregistravæs"
#define KPSTLSVR_MSG_EXCERCISE_PL_1250                   ((const unsigned char *)"") // "sprendþia uþdaviná "
#define KPSTLSVR_MSG_EXERCISE_DONE_PL_1250               ((const unsigned char *)"") // "baigë uþdaviná "
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_PL_1250            ((const unsigned char *)"") // "klientas uþregistruotas"
#define KPSTLSVR_MSG_LOGGING_REFUSED_PL_1250             ((const unsigned char *)"") // "kliento registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_PL_1250           ((const unsigned char *)"") // "klientas iðregistruotas"
#define KPSTLSVR_MSG_RES_LOG_REFUSED_PL_1250             ((const unsigned char *)"") // "rezultatø registravimas/priëmimas atmestas"
#define KPSTLSVR_MSG_SERVER_STOPPED_PL_1250              ((const unsigned char *)"") // "Serveris sustabdytas"
#define KPSTLSVR_MSG_SERVER_ABORTED_PL_1250              ((const unsigned char *)"") // "Serveris sustabdytas avariniu bûdu" 
#define KPSTLSVR_MSG_SERVER_ASKED_PL_1250                ((const unsigned char *)"") // "ieðko serverio"
#define KPSTLSVR_MSG_LOG_PROMPT_PL_1250                  ((const unsigned char *)"") // "Iðsamesni praneðimai kaupiami faile %s"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

// -----------------------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define KPSTLSVR_MSG_SERVER_STARTED_PL_1257              ((const unsigned char *)"") // "Serveris paleistas")
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_PL_1257  ((const unsigned char *)"") // "nutrauktas ankstesnis seansas"
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_PL_1257  ((const unsigned char *)"") // "áraðyti nepilni rezultatai"
#define KPSTLSVR_MSG_RECEIVED_RESULTS_PL_1257            ((const unsigned char *)"") // " atsiuntë"
#define KPSTLSVR_MSG_INTERMEDIATE_RES_PL_1257            ((const unsigned char *)"") // " tarpinius"
#define KPSTLSVR_MSG_FINAL_RES_PL_1257                   ((const unsigned char *)"") // " galutinius"
#define KPSTLSVR_MSG_RESULTS_RECEIVED_PL_1257            ((const unsigned char *)"") // " rezultatus"
#define KPSTLSVR_MSG_REGISTERED_PL_1257                  ((const unsigned char *)"") // " prisiregistravo testo sprendimui"
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_PL_1257          ((const unsigned char *)"            confirm(\"\");\n") // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_PL_1257     ((const unsigned char *)"   confirm(\"\");\n") // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
#define KPSTLSVR_MSG_ERROR_PL_1257                       ((const unsigned char *)"") // "Klaida: "
#define KPSTLSVR_MSG_WARNING_PL_1257                     ((const unsigned char *)"") // "Perspëjimas: "
#define KPSTLSVR_MSG_CLIENT_STATUS_PL_1257               ((const unsigned char *)"") // "Kliento bûsena"
#define KPSTLSVR_MSG_STATUS_PL_1257                      ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_CLIENTS_STATUS_PL_1257              ((const unsigned char *)"") // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_STATUS_PL_1257                  ((const unsigned char *)"") // "Bûsena"
#define KPSTLSVR_MSG_TAB_CLIENTS_PL_1257                 ((const unsigned char *)"") // "Klientai"
#define KPSTLSVR_MSG_TAB_RESULTS_PL_1257                 ((const unsigned char *)"") // "Rezultatai"
#define KPSTLSVR_MSG_TAB_MESSAGES_PL_1257                ((const unsigned char *)"") // "Praneðimai"
#define KPSTLSVR_MSG_TAB_NETWORK_PL_1257                 ((const unsigned char *)"") // "Tinklai"
#define KPSTLSVR_MSG_TAB_ADMINS_PL_1257                  ((const unsigned char *)"") // "Administratoriai"
#define KPSTLSVR_MSG_ORDER_NO_PL_1257                    ((const unsigned char *)"") // "Eil. Nr."
#define KPSTLSVR_MSG_SESSION_ID_PL_1257                  ((const unsigned char *)"") // "Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_PL_1257                   ((const unsigned char *)"") // "Kliento IP adresas"
#define KPSTLSVR_MSG_REST_MIN_PL_1257                    ((const unsigned char *)"") // "Liko min."
#define KPSTLSVR_MSG_SESSION_ACTIVE_PL_1257              ((const unsigned char *)"") // " seansas aktyvus,"
#define KPSTLSVR_MSG_LOST_CONNECTION_PL_1257             ((const unsigned char *)"") // " prarastas ryðys su klientu,"
#define KPSTLSVR_MSG_SLOT_FREE_PL_1257                   ((const unsigned char *)"") // " galima registruotis."
#define KPSTLSVR_MSG_REST_MIN__PL_1257                   ((const unsigned char *)"") // "Liko min. "
#define KPSTLSVR_MSG_LOST_CLI_TIME_PL_1257               ((const unsigned char *)"") // " prarastø klientø gyvavimo laikas"
#define KPSTLSVR_MSG_RESULTS_PL_1257                     ((const unsigned char *)"") // " rezultatai"
#define KPSTLSVR_MSG_TEST_RESULTS_PL_1257                ((const unsigned char *)"") // "Testo rezultatai"
#define KPSTLSVR_MSG_CLASS_PREFIX_PL_1257                ((const unsigned char *)"") // "cl. "
#define KPSTLSVR_MSG_CLASS_POSTFIX_PL_1257               ((const unsigned char *)"") // " kl."
#define KPSTLSVR_MSG_RES_FILE_PL_1257                    ((const unsigned char *)"") // "Rezultatai kaupiami faile "
#define KPSTLSVR_MSG_BAD_RES_PL_1257                     ((const unsigned char *)"") // " sugedæ ar kito testo rezultatai;"
#define KPSTLSVR_MSG_BAD_RES_REC_PL_1257                 ((const unsigned char *)"") // " sugadintas rezultatø áraðas;" 
#define KPSTLSVR_MSG_TEST_TIMEOUT_PL_1257                ((const unsigned char *)"") // " baigësi sprendimo laikas."
#define KPSTLSVR_MSG_MESSAGES__PL_1257                   ((const unsigned char *)"") // " pranesimai"
#define KPSTLSVR_MSG_ERROR_HELP_PL_1257                  ((const unsigned char *)"") // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
#define KPSTLSVR_MSG_SESSION_STATUS_PL_1257              ((const unsigned char *)"") // "Ryðio seanso bûsena"
#define KPSTLSVR_MSG_NETWORKS_PL_1257                    ((const unsigned char *)"") // " tinklai"
#define KPSTLSVR_MSG_ADMINS_PL_1257                      ((const unsigned char *)"") // " administratoriai"
#define KPSTLSVR_MSG_STATUS__PL_1257                     ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_IP_LIST_PL_1257                     ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama "
#define KPSTLSVR_MSG_IP_LIST_SEND_PL_1257                ((const unsigned char *)"") // "siøsti duomenis"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_PL_1257            ((const unsigned char *)"") // "registruotis"
#define KPSTLSVR_MSG_IP_LIST_ADMIN_PL_1257               ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
#define KPSTLSVR_MSG_CONNECTIONS_LIST_PL_1257            ((const unsigned char *)"") // "Prisijungimø sàraðas"
#define KPSTLSVR_MSG_SESSION_STARTED_PL_1257             ((const unsigned char *)"") // " seansas pradëtas,"
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_PL_1257          ((const unsigned char *)"") // " siunèiami tarpiniai rezultatai,"
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_PL_1257          ((const unsigned char *)"") // " atsiøsti galutiniai rezultatai,"
#define KPSTLSVR_MSG_SESSION_ABORTED_PL_1257             ((const unsigned char *)"") // " seansas nutrauktas."
#define KPSTLSVR_MSG_ABORT_PROMPT_PL_1257                ((const unsigned char *)"") // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
#define KPSTLSVR_MSG_IP_HINT_PL_1257                     ((const unsigned char *)"") // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255")
#define KPSTLSVR_MSG_PORT_BUSSY_PL_1257                  ((const unsigned char *)"") // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_PL_1257         ((const unsigned char *)"") // "prisijungë administruoti serverá")
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_PL_1257         ((const unsigned char *)"") // "atmestas bandymas administruoti serverá"
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_PL_1257            ((const unsigned char *)"") // " atsiuntë duomenis neuþsiregistravæs"
#define KPSTLSVR_MSG_EXCERCISE_PL_1257                   ((const unsigned char *)"") // "sprendþia uþdaviná "
#define KPSTLSVR_MSG_EXERCISE_DONE_PL_1257               ((const unsigned char *)"") // "baigë uþdaviná "
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_PL_1257            ((const unsigned char *)"") // "klientas uþregistruotas"
#define KPSTLSVR_MSG_LOGGING_REFUSED_PL_1257             ((const unsigned char *)"") // "kliento registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_PL_1257           ((const unsigned char *)"") // "klientas iðregistruotas"
#define KPSTLSVR_MSG_RES_LOG_REFUSED_PL_1257             ((const unsigned char *)"") // "rezultatø registravimas/priëmimas atmestas"
#define KPSTLSVR_MSG_SERVER_STOPPED_PL_1257              ((const unsigned char *)"") // "Serveris sustabdytas"
#define KPSTLSVR_MSG_SERVER_ABORTED_PL_1257              ((const unsigned char *)"") // "Serveris sustabdytas avariniu bûdu" 
#define KPSTLSVR_MSG_SERVER_ASKED_PL_1257                ((const unsigned char *)"") // "ieðko serverio"
#define KPSTLSVR_MSG_LOG_PROMPT_PL_1257                  ((const unsigned char *)"") // "Iðsamesni praneðimai kaupiami faile %s"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

// -----------------------------------------------
#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define KPSTLSVR_MSG_SERVER_STARTED_RU             ((const unsigned char *)"") // "Serveris paleistas")
#define KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_RU ((const unsigned char *)"") // "nutrauktas ankstesnis seansas"
#define KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_RU ((const unsigned char *)"") // "áraðyti nepilni rezultatai"
#define KPSTLSVR_MSG_RECEIVED_RESULTS_RU           ((const unsigned char *)"") // " atsiuntë"
#define KPSTLSVR_MSG_INTERMEDIATE_RES_RU           ((const unsigned char *)"") // " tarpinius"
#define KPSTLSVR_MSG_FINAL_RES_RU                  ((const unsigned char *)"") // " galutinius"
#define KPSTLSVR_MSG_RESULTS_RECEIVED_RU           ((const unsigned char *)"") // " rezultatus"
#define KPSTLSVR_MSG_REGISTERED_RU                 ((const unsigned char *)"") // " prisiregistravo testo sprendimui"
#define KPSTLSVR_MSG_SURE_DELETE_MARKED_RU         ((const unsigned char *)"            confirm(\"\");\n") // "            confirm(\"Ar tikrai norite iðmesti visus paþymëtus áraðus?\");\n"
#define KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_RU    ((const unsigned char *)"   confirm(\"\");\n") // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
#define KPSTLSVR_MSG_ERROR_RU                      ((const unsigned char *)"") // "Klaida: "
#define KPSTLSVR_MSG_WARNING_RU                    ((const unsigned char *)"") // "Perspëjimas: "
#define KPSTLSVR_MSG_CLIENT_STATUS_RU              ((const unsigned char *)"") // "Kliento bûsena"
#define KPSTLSVR_MSG_STATUS_RU                     ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_CLIENTS_STATUS_RU             ((const unsigned char *)"") // "Klientø bûsena"
#define KPSTLSVR_MSG_TAB_STATUS_RU                 ((const unsigned char *)"") // "Bûsena"
#define KPSTLSVR_MSG_TAB_CLIENTS_RU                ((const unsigned char *)"") // "Klientai"
#define KPSTLSVR_MSG_TAB_RESULTS_RU                ((const unsigned char *)"") // "Rezultatai"
#define KPSTLSVR_MSG_TAB_MESSAGES_RU               ((const unsigned char *)"") // "Praneðimai"
#define KPSTLSVR_MSG_TAB_NETWORK_RU                ((const unsigned char *)"") // "Tinklai"
#define KPSTLSVR_MSG_TAB_ADMINS_RU                 ((const unsigned char *)"") // "Administratoriai"
#define KPSTLSVR_MSG_ORDER_NO_RU                   ((const unsigned char *)"") // "Eil. Nr."
#define KPSTLSVR_MSG_SESSION_ID_RU                 ((const unsigned char *)"") // "Seanso ID")
#define KPSTLSVR_MSG_CLIENT_IP_RU                  ((const unsigned char *)"") // "Kliento IP adresas"
#define KPSTLSVR_MSG_REST_MIN_RU                   ((const unsigned char *)"") // "Liko min."
#define KPSTLSVR_MSG_SESSION_ACTIVE_RU             ((const unsigned char *)"") // " seansas aktyvus,"
#define KPSTLSVR_MSG_LOST_CONNECTION_RU            ((const unsigned char *)"") // " prarastas ryðys su klientu,"
#define KPSTLSVR_MSG_SLOT_FREE_RU                  ((const unsigned char *)"") // " galima registruotis."
#define KPSTLSVR_MSG_REST_MIN__RU                  ((const unsigned char *)"") // "Liko min. "
#define KPSTLSVR_MSG_LOST_CLI_TIME_RU              ((const unsigned char *)"") // " prarastø klientø gyvavimo laikas"
#define KPSTLSVR_MSG_RESULTS_RU                    ((const unsigned char *)"") // " rezultatai"
#define KPSTLSVR_MSG_TEST_RESULTS_RU               ((const unsigned char *)"") // "Testo rezultatai"
#define KPSTLSVR_MSG_CLASS_PREFIX_RU               ((const unsigned char *)"") // "cl. "
#define KPSTLSVR_MSG_CLASS_POSTFIX_RU              ((const unsigned char *)"") // " kl."
#define KPSTLSVR_MSG_RES_FILE_RU                   ((const unsigned char *)"") // "Rezultatai kaupiami faile "
#define KPSTLSVR_MSG_BAD_RES_RU                    ((const unsigned char *)"") // " sugedæ ar kito testo rezultatai;"
#define KPSTLSVR_MSG_BAD_RES_REC_RU                ((const unsigned char *)"") // " sugadintas rezultatø áraðas;" 
#define KPSTLSVR_MSG_TEST_TIMEOUT_RU               ((const unsigned char *)"") // " baigësi sprendimo laikas."
#define KPSTLSVR_MSG_MESSAGES__RU                  ((const unsigned char *)"") // " pranesimai"
#define KPSTLSVR_MSG_ERROR_HELP_RU                 ((const unsigned char *)"") // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
#define KPSTLSVR_MSG_SESSION_STATUS_RU             ((const unsigned char *)"") // "Ryðio seanso bûsena"
#define KPSTLSVR_MSG_NETWORKS_RU                   ((const unsigned char *)"") // " tinklai"
#define KPSTLSVR_MSG_ADMINS_RU                     ((const unsigned char *)"") // " administratoriai"
#define KPSTLSVR_MSG_STATUS__RU                    ((const unsigned char *)"") // " busena"
#define KPSTLSVR_MSG_IP_LIST_RU                    ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama "
#define KPSTLSVR_MSG_IP_LIST_SEND_RU               ((const unsigned char *)"") // "siøsti duomenis"
#define KPSTLSVR_MSG_IP_LIST_REGISTER_RU           ((const unsigned char *)"") // "registruotis"
#define KPSTLSVR_MSG_IP_LIST_ADMIN_RU              ((const unsigned char *)"") // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
#define KPSTLSVR_MSG_CONNECTIONS_LIST_RU           ((const unsigned char *)"") // "Prisijungimø sàraðas"
#define KPSTLSVR_MSG_SESSION_STARTED_RU            ((const unsigned char *)"") // " seansas pradëtas,"
#define KPSTLSVR_MSG_RESULTS_BEING_SENT_RU         ((const unsigned char *)"") // " siunèiami tarpiniai rezultatai,"
#define KPSTLSVR_MSG_FINAL_RESULTS_SENT_RU         ((const unsigned char *)"") // " atsiøsti galutiniai rezultatai,"
#define KPSTLSVR_MSG_SESSION_ABORTED_RU            ((const unsigned char *)"") // " seansas nutrauktas."
#define KPSTLSVR_MSG_ABORT_PROMPT_RU               ((const unsigned char *)"") // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
#define KPSTLSVR_MSG_IP_HINT_RU                    ((const unsigned char *)"") // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255")
#define KPSTLSVR_MSG_PORT_BUSSY_RU                 ((const unsigned char *)"") // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
#define KPSTLSVR_MSG_MAINTENANCE_STARTED_RU        ((const unsigned char *)"") // "prisijungë administruoti serverá")
#define KPSTLSVR_MSG_MAINTENANCE_REFUSED_RU        ((const unsigned char *)"") // "atmestas bandymas administruoti serverá"
#define KPSTLSVR_MSG_UNLOGGED_RESULTS_RU           ((const unsigned char *)"") // " atsiuntë duomenis neuþsiregistravæs"
#define KPSTLSVR_MSG_EXCERCISE_RU                  ((const unsigned char *)"") // "sprendþia uþdaviná "
#define KPSTLSVR_MSG_EXERCISE_DONE_RU              ((const unsigned char *)"") // "baigë uþdaviná "
#define KPSTLSVR_MSG_CLIENT_LOGGED_IN_RU           ((const unsigned char *)"") // "klientas uþregistruotas"
#define KPSTLSVR_MSG_LOGGING_REFUSED_RU            ((const unsigned char *)"") // "kliento registravimas atmestas"
#define KPSTLSVR_MSG_CLIENT_LOGGED_OFF_RU          ((const unsigned char *)"") // "klientas iðregistruotas"
#define KPSTLSVR_MSG_RES_LOG_REFUSED_RU            ((const unsigned char *)"") // "rezultatø registravimas/priëmimas atmestas"
#define KPSTLSVR_MSG_SERVER_STOPPED_RU             ((const unsigned char *)"") // "Serveris sustabdytas"
#define KPSTLSVR_MSG_SERVER_ABORTED_RU             ((const unsigned char *)"") // "Serveris sustabdytas avariniu bûdu" 
#define KPSTLSVR_MSG_SERVER_ASKED_RU               ((const unsigned char *)"") // "ieðko serverio"
#define KPSTLSVR_MSG_LOG_PROMPT_RU                 ((const unsigned char *)"") // "Iðsamesni praneðimai kaupiami faile %s"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))


// ---------------------------------------------- 
typedef enum
{
   KPSTLSVR_FRIENDS,
   KPSTLSVR_ADMINS,
   KPSTLSVR_LINKS
   
} KpStLisSvrEnvirs;


typedef enum
{
   KPST_STAT_UNKNOWN = -1,
   KPST_SES_OPEN,          // po inicializacijos pranesimo
   KPST_SES_ACTIVE,        // eina tarpiniai duomenys
   KPST_SES_DONE,          // atejo galutiniai duomenys, sesija pasibaige tvarkingai
   KPST_SES_CLOSED,        // sesija uzdaryta per jega

   KPST_NUM_OF_SES_STATES
   
} KpstSesStats;

#define KPST_NUM_OF_SES_STATES_1 KPST_NUM_OF_SES_STATES
extern const unsigned char *lpszSesStates[KPST_NUM_OF_SES_STATES];


typedef struct // m_pLinkList elementas
{
   IN_ADDR m_lIpAddr;
   time_t m_lTimeStamp;
   KpstSesStats m_iSesStatus;
   unsigned char m_lpszData[KP_MAX_FILE_LIN_LEN+1];

} KpstSesData;


// ----------------------------------- 
class KpStLicSvr: public KpStApp
{
   DWORD m_lBroadcastThreadId;
   DWORD m_lLicListThreadId;
   
   long m_lLastWindowsError;
   
   KpTreeEntry *m_pFriendList;      // sarasas adresu, is kuriu galima registruoti licencijas, elementai - IN_ADDR 
   KpTreeEntry *m_pFriendVarList;   // friends.htm formos lauku paskutines ivestos reiksmes, elementai - PostVarRec
   KpTreeEntry *m_pAdminList;       // sarasas adresu, is kuriu galima administruoti, elementai - IN_ADDR
   KpTreeEntry *m_pAdminVarList;    // admins.htm formos lauku paskutines ivestos reiksmes, elementai - PostVarRec
   KpTreeEntry *m_pLinkList;        // klientø sàraðas 

   KpTreeEntry *m_pConsole;         // konsoles pranesimu sarasas, elementai - lpsz eilutes 

   KpTreeEntry *m_pCurAdmins;       // prisijungusiu administratoriu sarasas, elementai - IN_ADDR

public:
   int m_iNumOfPages; // serverio valdymo HTML puslapiu skaicius (Bûsena/Rezultatai/Tinklai/Administratoriai)

   DWORD m_lParentProcess;

private:
   HRESULT GetCfgFname(unsigned char *lpszIniFnameBuf);
   HRESULT ReadConfig(void);
public:
   HRESULT SaveConfig(void);

   KpStLicSvr(void);
   ~KpStLicSvr(void);
   HRESULT GetOpenResult(void);

   HRESULT Init(HINSTANCE hInstance, const unsigned char *lpszIniFName, LPSTR lpCmdLine);
      // iskviecia InitStApp()

   HRESULT StartBroadcastThread(HINSTANCE hInstance);

   HRESULT CreateLicSockThread(HINSTANCE hInstance);
// HRESULT CheckLicSockCmd(void);
   
   HRESULT RefreshLicDisplay(void);

// prideda pranesima prie konsoles saraso m_pConsole
   HRESULT AddConsMsg(const unsigned char *lpszMsg); 

// prideda pranesima apie IP adresa is m_pLicListSocket->m_PackedUrl prie konsoles saraso m_pConsole
   HRESULT AddIPConsMsg(const unsigned char *lpszMsg, bool bLogMessage, KpSocket *pKpSocket);

// KpErrorProc.OutputErrorMessage() analogas
   HRESULT OutputErrorMessageLocal // tik i konsole
   (
   HRESULT lhRetc, 
   const unsigned char *lpszMessageText, 
   bool bSevereError,
   bool bLogMessage  // tada, kai nëra standartinio klaidø apdorojimo - kai iðkvieèiamas be OutputErrorMessage()  
   );

   HRESULT OutputErrorMessage // i konsole ir i KpErrorProc
   (
   HRESULT lhRetc,
   const unsigned char *lpszMessageText,
   bool bSevereError,
   const char *lpszSourceFile,
   int iSourceLine,
   long lMainKeyId,
   KpConsole *pListBox = NULL
   );

   HRESULT OutputErrorMessage
   (
   HRESULT lhRetc,
   LONG lWindowsErrorCode,
   bool bSevereError,
   const char *lpszSourceFile,
   int iSourceLine,
   long lMainKeyId,
   KpConsole *pListBox = NULL
   );

// isveda i faila + pranesima i konsole
   HRESULT PutChar(TvXmlFile *pOutFile, KpChar iOutCh, bool bCheckFlg);
   HRESULT PutCharProc(TvXmlFile *pOutFile, KpChar iOutCh, XmlTagPars *pTagPar, bool bCheckIndex);
   HRESULT PutStr(TvXmlFile *pOutFile, const unsigned char *lpszOutStr);
   HRESULT PutKpStr(TvXmlFile *pOutFile, const KpChar *iazOutStr);

// suformuoja HTML licences puslapi nuotoliniam monitoringui
// isskiria vieta *plpszPagePtrPtr, po panaudojimo isvalyti
   HRESULT FormatLicencesPage(unsigned char **plpszPagePtrPtr);
   HRESULT FormatResultsPage(unsigned char **plpszPagePtrPtr);
   HRESULT FormatConsolePage(unsigned char **plpszPagePtrPtr);
   HRESULT FormatIpListPage(KpStLisSvrEnvirs iCurEnv, unsigned char **plpszPagePtrPtr);

   HRESULT CheckName(unsigned long ulNameVal, unsigned char *lpszNameBuf, const unsigned char *lpszNamePtr, unsigned char *lpszNameBufOut, int *piErrLine);
            // uþpildo lpszNameBuf[KPST_TXTCD_CHARS_PER_VAL_NAME+1] ið uþkoduoto vardo lauko iNameVal,
            // palygina su nekoduotu vardu lpszNamePtr

   HRESULT ProcessVars(KpStLisSvrEnvirs iCurEnv, KpTreeEntry *p_VarList);
            // analizuoja per POST gautas formos lauku reiksmes
            // tvarko m_pFriendList/m_pAdminList atsizvelgiant i iCurEnv
            // p_VarList reikia arba issaugoja i m_pFriendVarList/m_pAdminVarList arba sunaikina (delete)  

   HRESULT CheckClientIP(/* IN_ADDR *pClientHost, */ KpStLisSvrEnvirs iCurEnv);
            // former CheckClientIP(&stap_ptr->m_pLicListSocket->m_PackedUrl.m_Addr, ...

   HRESULT ScanPostData(unsigned char *lpszPostMsgBuf, unsigned char *lpszLogBuf); // vidine funkcija Tado POST  pranesimams analizuoti; , lpszLogBuf gali bûti NULL

   HRESULT UpdateLinkList(KpstSesStats iSessionStatus, const unsigned char *lpszResultData); 
      // raso duomenis i m_pLinkList
      // lpszResultData - duomenu iraso m_lpszData turinys - laukai, atskirti '|', pirmi du - vardas ir pavarde
      // jei lpszResultData == NULL - neraso nieko, tik uzdaro visus atvirus 

   HRESULT SearchLinkList(KpTreeEntry **ppEntryPtr, KpstSesData *pNewRecordData);
      // iesko iraso su tuo paciu IP, pavarde ir m_iSesStatus <= pNewRecordData->m_iSesStatus
      // jei strlen(pNewRecordData->m_lpszData) == 0, nei IP, nei pavardes nelygina, duoda pirma su
      //    tinkamu m_iSesStatus    

   HRESULT GetNameFromResults(unsigned char *lpszOutNameBuf, int iBufLen, const unsigned char *lpszResults);
      // istraukia varda pavarde is rezultatu eilutes (laukai atskirti tabuliacijom)

};

extern KpStLicSvr theApp;

extern HRESULT AppendLogMessage(unsigned char *lpszLogMsgBuf, const unsigned char *lpszNewMessage);

extern DWORD WINAPI LicSockListenProc(LPVOID lpParameter);  // paleidþia CreateLicSockThread() atskiram threade m_lLicListThreadId
                                                            // klausosi HTTP porto m_pLicListSocket  

extern DWORD WINAPI LicSockBroadcastListenProc(LPVOID lpParameter);  // paleidþia StartBroadcastThread() atskiram threade m_lBroadcastThreadId
                                                                     // klausosi HTTP porto m_pListSocket

#define KP_SVR_ASSERT(bCond, lhErrCode, Msg, bFatal)  { if(SUCCEEDED(retc)) if(!(bCond)) retc = OutputErrorMessage(lhErrCode, Msg, bFatal, __FILE__, __LINE__, 0L, NULL); }

#endif
