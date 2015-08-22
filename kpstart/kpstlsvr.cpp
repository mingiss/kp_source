// ---------------------------
// kpstlsvr.cpp
// lokalus licenciju serveris
//

// -----------------------------------------
#include "envir.h"

#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <richedit.h>
#include <Richole.h>

#include "kpstdlib.h"
#include "kperrno.h"
#include "kptree.h"
#include "kptt.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kperr.h"
#include "kpmsg.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11y.h"
#include "kphp11d.h"
#include "kphp11rc.h"
#include "kpcapp.h"
#include "kpstmsg.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "htmt.h"
#include "xmlis.h"
#include "xmli.h"
#include "xmln.h"
#include "xmlg.h"
#include "kpstap.h"
#include "kpstlsvr.h"
#include "kpstlsvr_lt.h"
#include "kpstlsvr_en.h"


#if Envir!=MSWin32
#error Envir!=MSWin32
#endif

#define KPSTLSVR_TEST_CODE_NAME // iðvedam rezultatø slaptus laukus – testo kodà, uþkoduotà pavardæ

// -----------------------------------------
const unsigned char lpszProdName[] = "kpstlsvr"; 
int iProdVerGlob=0;
KpErrorProcClass KpErrorProc(True, 71);
#ifdef Debug
bool bServiceFl=False; // True; //   
#else
bool bServiceFl=True;
#endif
int iUpdNumGlob = -1;

KpStLicSvr theApp;

#ifdef Debug
KpConsole KpStLicSvrCons;
#endif

int KpHp11NumOfExtFun=KP_RC_CBIX_NumOfCommonIxs;
KpHp11ExtFun KpHp11ExtFunTab[KP_RC_CBIX_NumOfCommonIxs_5+1]=
// HRESULT (*KpHp11ExtFunTab)(void *pPars)[]=
{
   GetCommonCompID_RC,
   TestFlashID_RC,
   TestIniChSum_RC,
   SetIniChSum_RC,
   
   CheckResRequest_RC,
   CheckRelRequest_RC,

   InitRestDays_RC,
   ResumeRestDays_RC,
   ProcessRestDays_RC,

   NULL
};


// ------------------------------------ kpstart programø praneðimai
const unsigned char *lpszaKpStlSvrMessages[NumOfKpStlSvrMessages_1][KpNumOfLangs_2] =
{
KPSTLSVR_MSG_SERVER_STARTED_EN,             KPSTLSVR_MSG_SERVER_STARTED_LT,             KPSTLSVR_MSG_SERVER_STARTED_PL_1250,             KPSTLSVR_MSG_SERVER_STARTED_PL_1257,             KPSTLSVR_MSG_SERVER_STARTED_RU,             KPST_MSG_PROD_REG_RU,                       // "Serveris paleistas"
KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_EN, KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_LT, KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_PL_1250, KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_PL_1257, KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_RU, KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED_RU, // "nutrauktas ankstesnis seansas" 
KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_EN, KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_LT, KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_PL_1250, KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_PL_1257, KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_RU, KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN_RU, // "áraðyti nepilni rezultatai"
KPSTLSVR_MSG_RECEIVED_RESULTS_EN,           KPSTLSVR_MSG_RECEIVED_RESULTS_LT,           KPSTLSVR_MSG_RECEIVED_RESULTS_PL_1250,           KPSTLSVR_MSG_RECEIVED_RESULTS_PL_1257,           KPSTLSVR_MSG_RECEIVED_RESULTS_RU,           KPSTLSVR_MSG_RECEIVED_RESULTS_RU,           // " atsiuntë"
KPSTLSVR_MSG_INTERMEDIATE_RES_EN,           KPSTLSVR_MSG_INTERMEDIATE_RES_LT,           KPSTLSVR_MSG_INTERMEDIATE_RES_PL_1250,           KPSTLSVR_MSG_INTERMEDIATE_RES_PL_1257,           KPSTLSVR_MSG_INTERMEDIATE_RES_RU,           KPSTLSVR_MSG_INTERMEDIATE_RES_RU,           // " tarpinius"
KPSTLSVR_MSG_FINAL_RES_EN,                  KPSTLSVR_MSG_FINAL_RES_LT,                  KPSTLSVR_MSG_FINAL_RES_PL_1250,                  KPSTLSVR_MSG_FINAL_RES_PL_1257,                  KPSTLSVR_MSG_FINAL_RES_RU,                  KPSTLSVR_MSG_FINAL_RES_RU,                  // " galutinius"
KPSTLSVR_MSG_RESULTS_RECEIVED_EN,           KPSTLSVR_MSG_RESULTS_RECEIVED_LT,           KPSTLSVR_MSG_RESULTS_RECEIVED_PL_1250,           KPSTLSVR_MSG_RESULTS_RECEIVED_PL_1257,           KPSTLSVR_MSG_RESULTS_RECEIVED_RU,           KPSTLSVR_MSG_RESULTS_RECEIVED_RU,           // " rezultatus"
KPSTLSVR_MSG_REGISTERED_EN,                 KPSTLSVR_MSG_REGISTERED_LT,                 KPSTLSVR_MSG_REGISTERED_PL_1250,                 KPSTLSVR_MSG_REGISTERED_PL_1257,                 KPSTLSVR_MSG_REGISTERED_RU,                 KPSTLSVR_MSG_REGISTERED_RU,                 // " prisiregistravo testo sprendimui"
KPSTLSVR_MSG_SURE_DELETE_MARKED_EN,         KPSTLSVR_MSG_SURE_DELETE_MARKED_LT,         KPSTLSVR_MSG_SURE_DELETE_MARKED_PL_1250,         KPSTLSVR_MSG_SURE_DELETE_MARKED_PL_1257,         KPSTLSVR_MSG_SURE_DELETE_MARKED_RU,         KPSTLSVR_MSG_SURE_DELETE_MARKED_RU,         // "            confirm(\"Ar tikrai norite iðmesti paþymëtus áraðus?\");\n"
KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_EN,    KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_LT,    KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_PL_1250,    KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_PL_1257,    KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_RU,    KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_RU,    // "   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n"
KPSTLSVR_MSG_ERROR_EN,                      KPSTLSVR_MSG_ERROR_LT,                      KPSTLSVR_MSG_ERROR_PL_1250,                      KPSTLSVR_MSG_ERROR_PL_1257,                      KPSTLSVR_MSG_ERROR_RU,                      KPSTLSVR_MSG_ERROR_RU,                      // "Klaida: "
KPSTLSVR_MSG_WARNING_EN,                    KPSTLSVR_MSG_WARNING_LT,                    KPSTLSVR_MSG_WARNING_PL_1250,                    KPSTLSVR_MSG_WARNING_PL_1257,                    KPSTLSVR_MSG_WARNING_RU,                    KPSTLSVR_MSG_WARNING_RU,                    // "Perspëjimas: "
KPSTLSVR_MSG_CLIENT_STATUS_EN,              KPSTLSVR_MSG_CLIENT_STATUS_LT,              KPSTLSVR_MSG_CLIENT_STATUS_PL_1250,              KPSTLSVR_MSG_CLIENT_STATUS_PL_1257,              KPSTLSVR_MSG_CLIENT_STATUS_RU,              KPSTLSVR_MSG_CLIENT_STATUS_RU,              // "Kliento bûsena"
KPSTLSVR_MSG_STATUS_EN,                     KPSTLSVR_MSG_STATUS_LT,                     KPSTLSVR_MSG_STATUS_PL_1250,                     KPSTLSVR_MSG_STATUS_PL_1257,                     KPSTLSVR_MSG_STATUS_RU,                     KPSTLSVR_MSG_STATUS_RU,                     // " busena"
KPSTLSVR_MSG_CLIENTS_STATUS_EN,             KPSTLSVR_MSG_CLIENTS_STATUS_LT,             KPSTLSVR_MSG_CLIENTS_STATUS_PL_1250,             KPSTLSVR_MSG_CLIENTS_STATUS_PL_1257,             KPSTLSVR_MSG_CLIENTS_STATUS_RU,             KPSTLSVR_MSG_CLIENTS_STATUS_RU,             // "Klientø bûsena"
KPSTLSVR_MSG_TAB_STATUS_EN,                 KPSTLSVR_MSG_TAB_STATUS_LT,                 KPSTLSVR_MSG_TAB_STATUS_PL_1250,                 KPSTLSVR_MSG_TAB_STATUS_PL_1257,                 KPSTLSVR_MSG_TAB_STATUS_RU,                 KPSTLSVR_MSG_TAB_STATUS_RU,                 // "Bûsena"
KPSTLSVR_MSG_TAB_CLIENTS_EN,                KPSTLSVR_MSG_TAB_CLIENTS_LT,                KPSTLSVR_MSG_TAB_CLIENTS_PL_1250,                KPSTLSVR_MSG_TAB_CLIENTS_PL_1257,                KPSTLSVR_MSG_TAB_CLIENTS_RU,                KPSTLSVR_MSG_TAB_CLIENTS_RU,                // "Klientai"
KPSTLSVR_MSG_TAB_RESULTS_EN,                KPSTLSVR_MSG_TAB_RESULTS_LT,                KPSTLSVR_MSG_TAB_RESULTS_PL_1250,                KPSTLSVR_MSG_TAB_RESULTS_PL_1257,                KPSTLSVR_MSG_TAB_RESULTS_RU,                KPSTLSVR_MSG_TAB_RESULTS_RU,                // "Rezultatai"
KPSTLSVR_MSG_TAB_MESSAGES_EN,               KPSTLSVR_MSG_TAB_MESSAGES_LT,               KPSTLSVR_MSG_TAB_MESSAGES_PL_1250,               KPSTLSVR_MSG_TAB_MESSAGES_PL_1257,               KPSTLSVR_MSG_TAB_MESSAGES_RU,               KPSTLSVR_MSG_TAB_MESSAGES_RU,               // "Praneðimai"
KPSTLSVR_MSG_TAB_NETWORK_EN,                KPSTLSVR_MSG_TAB_NETWORK_LT,                KPSTLSVR_MSG_TAB_NETWORK_PL_1250,                KPSTLSVR_MSG_TAB_NETWORK_PL_1257,                KPSTLSVR_MSG_TAB_NETWORK_RU,                KPSTLSVR_MSG_TAB_NETWORK_RU,                // "Tinklai"
KPSTLSVR_MSG_TAB_ADMINS_EN,                 KPSTLSVR_MSG_TAB_ADMINS_LT,                 KPSTLSVR_MSG_TAB_ADMINS_PL_1250,                 KPSTLSVR_MSG_TAB_ADMINS_PL_1257,                 KPSTLSVR_MSG_TAB_ADMINS_RU,                 KPSTLSVR_MSG_TAB_ADMINS_RU,                 // "Administratoriai"
KPSTLSVR_MSG_ORDER_NO_EN,                   KPSTLSVR_MSG_ORDER_NO_LT,                   KPSTLSVR_MSG_ORDER_NO_PL_1250,                   KPSTLSVR_MSG_ORDER_NO_PL_1257,                   KPSTLSVR_MSG_ORDER_NO_RU,                   KPSTLSVR_MSG_ORDER_NO_RU,                   // "Eil. Nr."
KPSTLSVR_MSG_SESSION_ID_EN,                 KPSTLSVR_MSG_SESSION_ID_LT,                 KPSTLSVR_MSG_SESSION_ID_PL_1250,                 KPSTLSVR_MSG_SESSION_ID_PL_1257,                 KPSTLSVR_MSG_SESSION_ID_RU,                 KPSTLSVR_MSG_SESSION_ID_RU,                 // "Seanso ID"
KPSTLSVR_MSG_CLIENT_IP_EN,                  KPSTLSVR_MSG_CLIENT_IP_LT,                  KPSTLSVR_MSG_CLIENT_IP_PL_1250,                  KPSTLSVR_MSG_CLIENT_IP_PL_1257,                  KPSTLSVR_MSG_CLIENT_IP_RU,                  KPSTLSVR_MSG_CLIENT_IP_RU,                  // "Kliento IP adresas"
KPSTLSVR_MSG_REST_MIN_EN,                   KPSTLSVR_MSG_REST_MIN_LT,                   KPSTLSVR_MSG_REST_MIN_PL_1250,                   KPSTLSVR_MSG_REST_MIN_PL_1257,                   KPSTLSVR_MSG_REST_MIN_RU,                   KPSTLSVR_MSG_REST_MIN_RU,                   // "Liko min."
KPSTLSVR_MSG_SESSION_ACTIVE_EN,             KPSTLSVR_MSG_SESSION_ACTIVE_LT,             KPSTLSVR_MSG_SESSION_ACTIVE_PL_1250,             KPSTLSVR_MSG_SESSION_ACTIVE_PL_1257,             KPSTLSVR_MSG_SESSION_ACTIVE_RU,             KPSTLSVR_MSG_SESSION_ACTIVE_RU,             // " seansas aktyvus,"
KPSTLSVR_MSG_LOST_CONNECTION_EN,            KPSTLSVR_MSG_LOST_CONNECTION_LT,            KPSTLSVR_MSG_LOST_CONNECTION_PL_1250,            KPSTLSVR_MSG_LOST_CONNECTION_PL_1257,            KPSTLSVR_MSG_LOST_CONNECTION_RU,            KPSTLSVR_MSG_LOST_CONNECTION_RU,            // " prarastas ryðys su klientu,"
KPSTLSVR_MSG_SLOT_FREE_EN,                  KPSTLSVR_MSG_SLOT_FREE_LT,                  KPSTLSVR_MSG_SLOT_FREE_PL_1250,                  KPSTLSVR_MSG_SLOT_FREE_PL_1257,                  KPSTLSVR_MSG_SLOT_FREE_RU,                  KPSTLSVR_MSG_SLOT_FREE_RU,                  // " galima registruotis."
KPSTLSVR_MSG_REST_MIN__EN,                  KPSTLSVR_MSG_REST_MIN__LT,                  KPSTLSVR_MSG_REST_MIN__PL_1250,                  KPSTLSVR_MSG_REST_MIN__PL_1257,                  KPSTLSVR_MSG_REST_MIN__RU,                  KPSTLSVR_MSG_REST_MIN__RU,                  // "Liko min. "
KPSTLSVR_MSG_LOST_CLI_TIME_EN,              KPSTLSVR_MSG_LOST_CLI_TIME_LT,              KPSTLSVR_MSG_LOST_CLI_TIME_PL_1250,              KPSTLSVR_MSG_LOST_CLI_TIME_PL_1257,              KPSTLSVR_MSG_LOST_CLI_TIME_RU,              KPSTLSVR_MSG_LOST_CLI_TIME_RU,              // " prarastø klientø gyvavimo laikas"
KPSTLSVR_MSG_RESULTS_EN,                    KPSTLSVR_MSG_RESULTS_LT,                    KPSTLSVR_MSG_RESULTS_PL_1250,                    KPSTLSVR_MSG_RESULTS_PL_1257,                    KPSTLSVR_MSG_RESULTS_RU,                    KPSTLSVR_MSG_RESULTS_RU,                    // " rezultatai"
KPSTLSVR_MSG_TEST_RESULTS_EN,               KPSTLSVR_MSG_TEST_RESULTS_LT,               KPSTLSVR_MSG_TEST_RESULTS_PL_1250,               KPSTLSVR_MSG_TEST_RESULTS_PL_1257,               KPSTLSVR_MSG_TEST_RESULTS_RU,               KPSTLSVR_MSG_TEST_RESULTS_RU,               // "Testo rezultatai"
KPSTLSVR_MSG_CLASS_PREFIX_EN,               KPSTLSVR_MSG_CLASS_PREFIX_LT,               KPSTLSVR_MSG_CLASS_PREFIX_PL_1250,               KPSTLSVR_MSG_CLASS_PREFIX_PL_1257,               KPSTLSVR_MSG_CLASS_PREFIX_RU,               KPSTLSVR_MSG_CLASS_PREFIX_RU,               // "cl. "
KPSTLSVR_MSG_CLASS_POSTFIX_EN,              KPSTLSVR_MSG_CLASS_POSTFIX_LT,              KPSTLSVR_MSG_CLASS_POSTFIX_PL_1250,              KPSTLSVR_MSG_CLASS_POSTFIX_PL_1257,              KPSTLSVR_MSG_CLASS_POSTFIX_RU,              KPSTLSVR_MSG_CLASS_POSTFIX_RU,              // " kl."
KPSTLSVR_MSG_RES_FILE_EN,                   KPSTLSVR_MSG_RES_FILE_LT,                   KPSTLSVR_MSG_RES_FILE_PL_1250,                   KPSTLSVR_MSG_RES_FILE_PL_1257,                   KPSTLSVR_MSG_RES_FILE_RU,                   KPSTLSVR_MSG_RES_FILE_RU,                   // "Rezultatai kaupiami faile "
KPSTLSVR_MSG_BAD_RES_EN,                    KPSTLSVR_MSG_BAD_RES_LT,                    KPSTLSVR_MSG_BAD_RES_PL_1250,                    KPSTLSVR_MSG_BAD_RES_PL_1257,                    KPSTLSVR_MSG_BAD_RES_RU,                    KPSTLSVR_MSG_BAD_RES_RU,                    // " sugedæ ar kito testo rezultatai;"
KPSTLSVR_MSG_BAD_RES_REC_EN,                KPSTLSVR_MSG_BAD_RES_REC_LT,                KPSTLSVR_MSG_BAD_RES_REC_PL_1250,                KPSTLSVR_MSG_BAD_RES_REC_PL_1257,                KPSTLSVR_MSG_BAD_RES_REC_RU,                KPSTLSVR_MSG_BAD_RES_REC_RU,                // " sugadintas rezultatø áraðas;" 
KPSTLSVR_MSG_TEST_TIMEOUT_EN,               KPSTLSVR_MSG_TEST_TIMEOUT_LT,               KPSTLSVR_MSG_TEST_TIMEOUT_PL_1250,               KPSTLSVR_MSG_TEST_TIMEOUT_PL_1257,               KPSTLSVR_MSG_TEST_TIMEOUT_RU,               KPSTLSVR_MSG_TEST_TIMEOUT_RU,               // " baigësi sprendimo laikas."
KPSTLSVR_MSG_MESSAGES__EN,                  KPSTLSVR_MSG_MESSAGES__LT,                  KPSTLSVR_MSG_MESSAGES__PL_1250,                  KPSTLSVR_MSG_MESSAGES__PL_1257,                  KPSTLSVR_MSG_MESSAGES__RU,                  KPSTLSVR_MSG_MESSAGES__RU,                  // " pranesimai"
KPSTLSVR_MSG_ERROR_HELP_EN,                 KPSTLSVR_MSG_ERROR_HELP_LT,                 KPSTLSVR_MSG_ERROR_HELP_PL_1250,                 KPSTLSVR_MSG_ERROR_HELP_PL_1257,                 KPSTLSVR_MSG_ERROR_HELP_RU,                 KPSTLSVR_MSG_ERROR_HELP_RU,                 // "Apie pastebëtas klaidas ar perspëjimus praneðkite adresu tech@tev.lt"
KPSTLSVR_MSG_SESSION_STATUS_EN,             KPSTLSVR_MSG_SESSION_STATUS_LT,             KPSTLSVR_MSG_SESSION_STATUS_PL_1250,             KPSTLSVR_MSG_SESSION_STATUS_PL_1257,             KPSTLSVR_MSG_SESSION_STATUS_RU,             KPSTLSVR_MSG_SESSION_STATUS_RU,             // "Ryðio seanso bûsena"
KPSTLSVR_MSG_NETWORKS_EN,                   KPSTLSVR_MSG_NETWORKS_LT,                   KPSTLSVR_MSG_NETWORKS_PL_1250,                   KPSTLSVR_MSG_NETWORKS_PL_1257,                   KPSTLSVR_MSG_NETWORKS_RU,                   KPSTLSVR_MSG_NETWORKS_RU,                   // " tinklai"
KPSTLSVR_MSG_ADMINS_EN,                     KPSTLSVR_MSG_ADMINS_LT,                     KPSTLSVR_MSG_ADMINS_PL_1250,                     KPSTLSVR_MSG_ADMINS_PL_1257,                     KPSTLSVR_MSG_ADMINS_RU,                     KPSTLSVR_MSG_ADMINS_RU,                     // " administratoriai"
KPSTLSVR_MSG_STATUS__EN,                    KPSTLSVR_MSG_STATUS__LT,                    KPSTLSVR_MSG_STATUS__PL_1250,                    KPSTLSVR_MSG_STATUS__PL_1257,                    KPSTLSVR_MSG_STATUS__RU,                    KPSTLSVR_MSG_STATUS__RU,                    // " busena"
KPSTLSVR_MSG_IP_LIST_EN,                    KPSTLSVR_MSG_IP_LIST_LT,                    KPSTLSVR_MSG_IP_LIST_PL_1250,                    KPSTLSVR_MSG_IP_LIST_PL_1257,                    KPSTLSVR_MSG_IP_LIST_RU,                    KPSTLSVR_MSG_IP_LIST_RU,                    // "Sàraðas IP adresø, ið kuriø leidþiama "
KPSTLSVR_MSG_IP_LIST_SEND_EN,               KPSTLSVR_MSG_IP_LIST_SEND_LT,               KPSTLSVR_MSG_IP_LIST_SEND_PL_1250,               KPSTLSVR_MSG_IP_LIST_SEND_PL_1257,               KPSTLSVR_MSG_IP_LIST_SEND_RU,               KPSTLSVR_MSG_IP_LIST_SEND_RU,               // "siøsti duomenis"
KPSTLSVR_MSG_IP_LIST_REGISTER_EN,           KPSTLSVR_MSG_IP_LIST_REGISTER_LT,           KPSTLSVR_MSG_IP_LIST_REGISTER_PL_1250,           KPSTLSVR_MSG_IP_LIST_REGISTER_PL_1257,           KPSTLSVR_MSG_IP_LIST_REGISTER_RU,           KPSTLSVR_MSG_IP_LIST_REGISTER_RU,           // "registruotis"
KPSTLSVR_MSG_IP_LIST_ADMIN_EN,              KPSTLSVR_MSG_IP_LIST_ADMIN_LT,              KPSTLSVR_MSG_IP_LIST_ADMIN_PL_1250,              KPSTLSVR_MSG_IP_LIST_ADMIN_PL_1257,              KPSTLSVR_MSG_IP_LIST_ADMIN_RU,              KPSTLSVR_MSG_IP_LIST_ADMIN_RU,              // "Sàraðas IP adresø, ið kuriø leidþiama administruoti serverá"
KPSTLSVR_MSG_CONNECTIONS_LIST_EN,           KPSTLSVR_MSG_CONNECTIONS_LIST_LT,           KPSTLSVR_MSG_CONNECTIONS_LIST_PL_1250,           KPSTLSVR_MSG_CONNECTIONS_LIST_PL_1257,           KPSTLSVR_MSG_CONNECTIONS_LIST_RU,           KPSTLSVR_MSG_CONNECTIONS_LIST_RU,           // "Prisijungimø sàraðas"
KPSTLSVR_MSG_SESSION_STARTED_EN,            KPSTLSVR_MSG_SESSION_STARTED_LT,            KPSTLSVR_MSG_SESSION_STARTED_PL_1250,            KPSTLSVR_MSG_SESSION_STARTED_PL_1257,            KPSTLSVR_MSG_SESSION_STARTED_RU,            KPSTLSVR_MSG_SESSION_STARTED_RU,            // " seansas pradëtas,"
KPSTLSVR_MSG_RESULTS_BEING_SENT_EN,         KPSTLSVR_MSG_RESULTS_BEING_SENT_LT,         KPSTLSVR_MSG_RESULTS_BEING_SENT_PL_1250,         KPSTLSVR_MSG_RESULTS_BEING_SENT_PL_1257,         KPSTLSVR_MSG_RESULTS_BEING_SENT_RU,         KPSTLSVR_MSG_RESULTS_BEING_SENT_RU,         // " siunèiami tarpiniai rezultatai,"
KPSTLSVR_MSG_FINAL_RESULTS_SENT_EN,         KPSTLSVR_MSG_FINAL_RESULTS_SENT_LT,         KPSTLSVR_MSG_FINAL_RESULTS_SENT_PL_1250,         KPSTLSVR_MSG_FINAL_RESULTS_SENT_PL_1257,         KPSTLSVR_MSG_FINAL_RESULTS_SENT_RU,         KPSTLSVR_MSG_FINAL_RESULTS_SENT_RU,         // " atsiøsti galutiniai rezultatai,"
KPSTLSVR_MSG_SESSION_ABORTED_EN,            KPSTLSVR_MSG_SESSION_ABORTED_LT,            KPSTLSVR_MSG_SESSION_ABORTED_PL_1250,            KPSTLSVR_MSG_SESSION_ABORTED_PL_1257,            KPSTLSVR_MSG_SESSION_ABORTED_RU,            KPSTLSVR_MSG_SESSION_ABORTED_RU,            // " seansas nutrauktas."
KPSTLSVR_MSG_ABORT_PROMPT_EN,               KPSTLSVR_MSG_ABORT_PROMPT_LT,               KPSTLSVR_MSG_ABORT_PROMPT_PL_1250,               KPSTLSVR_MSG_ABORT_PROMPT_PL_1257,               KPSTLSVR_MSG_ABORT_PROMPT_RU,               KPSTLSVR_MSG_ABORT_PROMPT_RU,               // "Jei norite áraðyti neuþbaigtus rezultatus, spauskite mygtukà \"Iðsaugoti\", jei visus áraðus iðmesti – \"Iðvalyti\""
KPSTLSVR_MSG_IP_HINT_EN,                    KPSTLSVR_MSG_IP_HINT_LT,                    KPSTLSVR_MSG_IP_HINT_PL_1250,                    KPSTLSVR_MSG_IP_HINT_PL_1257,                    KPSTLSVR_MSG_IP_HINT_RU,                    KPSTLSVR_MSG_IP_HINT_RU,                    // "Jei norite pridëti visà potinklá, naudokite IP adreso oktetà 255"
KPSTLSVR_MSG_PORT_BUSSY_EN,                 KPSTLSVR_MSG_PORT_BUSSY_LT,                 KPSTLSVR_MSG_PORT_BUSSY_PL_1250,                 KPSTLSVR_MSG_PORT_BUSSY_PL_1257,                 KPSTLSVR_MSG_PORT_BUSSY_RU,                 KPSTLSVR_MSG_PORT_BUSSY_RU,                 // "Ryðio kanalas uþimtas, serverio paleisti nepavyko"
KPSTLSVR_MSG_MAINTENANCE_STARTED_EN,        KPSTLSVR_MSG_MAINTENANCE_STARTED_LT,        KPSTLSVR_MSG_MAINTENANCE_STARTED_PL_1250,        KPSTLSVR_MSG_MAINTENANCE_STARTED_PL_1257,        KPSTLSVR_MSG_MAINTENANCE_STARTED_RU,        KPSTLSVR_MSG_MAINTENANCE_STARTED_RU,        // "prisijungë administruoti serverá"
KPSTLSVR_MSG_MAINTENANCE_REFUSED_EN,        KPSTLSVR_MSG_MAINTENANCE_REFUSED_LT,        KPSTLSVR_MSG_MAINTENANCE_REFUSED_PL_1250,        KPSTLSVR_MSG_MAINTENANCE_REFUSED_PL_1257,        KPSTLSVR_MSG_MAINTENANCE_REFUSED_RU,        KPSTLSVR_MSG_MAINTENANCE_REFUSED_RU,        // "atmestas bandymas administruoti serverá"
KPSTLSVR_MSG_UNLOGGED_RESULTS_EN,           KPSTLSVR_MSG_UNLOGGED_RESULTS_LT,           KPSTLSVR_MSG_UNLOGGED_RESULTS_PL_1250,           KPSTLSVR_MSG_UNLOGGED_RESULTS_PL_1257,           KPSTLSVR_MSG_UNLOGGED_RESULTS_RU,           KPSTLSVR_MSG_UNLOGGED_RESULTS_RU,           // " atsiuntë duomenis neuþsiregistravæs"
KPSTLSVR_MSG_EXCERCISE_EN,                  KPSTLSVR_MSG_EXCERCISE_LT,                  KPSTLSVR_MSG_EXCERCISE_PL_1250,                  KPSTLSVR_MSG_EXCERCISE_PL_1257,                  KPSTLSVR_MSG_EXCERCISE_RU,                  KPSTLSVR_MSG_EXCERCISE_RU,                  // "sprendþia uþdaviná "
KPSTLSVR_MSG_EXERCISE_DONE_EN,              KPSTLSVR_MSG_EXERCISE_DONE_LT,              KPSTLSVR_MSG_EXERCISE_DONE_PL_1250,              KPSTLSVR_MSG_EXERCISE_DONE_PL_1257,              KPSTLSVR_MSG_EXERCISE_DONE_RU,              KPSTLSVR_MSG_EXERCISE_DONE_RU,              // "baigë uþdaviná "
KPSTLSVR_MSG_CLIENT_LOGGED_IN_EN,           KPSTLSVR_MSG_CLIENT_LOGGED_IN_LT,           KPSTLSVR_MSG_CLIENT_LOGGED_IN_PL_1250,           KPSTLSVR_MSG_CLIENT_LOGGED_IN_PL_1257,           KPSTLSVR_MSG_CLIENT_LOGGED_IN_RU,           KPSTLSVR_MSG_CLIENT_LOGGED_IN_RU,           // "klientas uþregistruotas"
KPSTLSVR_MSG_LOGGING_REFUSED_EN,            KPSTLSVR_MSG_LOGGING_REFUSED_LT,            KPSTLSVR_MSG_LOGGING_REFUSED_PL_1250,            KPSTLSVR_MSG_LOGGING_REFUSED_PL_1257,            KPSTLSVR_MSG_LOGGING_REFUSED_RU,            KPSTLSVR_MSG_LOGGING_REFUSED_RU,            // "kliento registravimas atmestas"
KPSTLSVR_MSG_CLIENT_LOGGED_OFF_EN,          KPSTLSVR_MSG_CLIENT_LOGGED_OFF_LT,          KPSTLSVR_MSG_CLIENT_LOGGED_OFF_PL_1250,          KPSTLSVR_MSG_CLIENT_LOGGED_OFF_PL_1257,          KPSTLSVR_MSG_CLIENT_LOGGED_OFF_RU,          KPSTLSVR_MSG_CLIENT_LOGGED_OFF_RU,          // "klientas iðregistruotas"
KPSTLSVR_MSG_RES_LOG_REFUSED_EN,            KPSTLSVR_MSG_RES_LOG_REFUSED_LT,            KPSTLSVR_MSG_RES_LOG_REFUSED_PL_1250,            KPSTLSVR_MSG_RES_LOG_REFUSED_PL_1257,            KPSTLSVR_MSG_RES_LOG_REFUSED_RU,            KPSTLSVR_MSG_RES_LOG_REFUSED_RU,            // "rezultatø registravimas/priëmimas atmestas"
KPSTLSVR_MSG_SERVER_STOPPED_EN,             KPSTLSVR_MSG_SERVER_STOPPED_LT,             KPSTLSVR_MSG_SERVER_STOPPED_PL_1250,             KPSTLSVR_MSG_SERVER_STOPPED_PL_1257,             KPSTLSVR_MSG_SERVER_STOPPED_RU,             KPSTLSVR_MSG_SERVER_STOPPED_RU,             // "Serveris sustabdytas"
KPSTLSVR_MSG_SERVER_ABORTED_EN,             KPSTLSVR_MSG_SERVER_ABORTED_LT,             KPSTLSVR_MSG_SERVER_ABORTED_PL_1250,             KPSTLSVR_MSG_SERVER_ABORTED_PL_1257,             KPSTLSVR_MSG_SERVER_ABORTED_RU,             KPSTLSVR_MSG_SERVER_ABORTED_RU,             // "Serveris sustabdytas avariniu bûdu" 
KPSTLSVR_MSG_SERVER_ASKED_EN,               KPSTLSVR_MSG_SERVER_ASKED_LT,               KPSTLSVR_MSG_SERVER_ASKED_PL_1250,               KPSTLSVR_MSG_SERVER_ASKED_PL_1257,               KPSTLSVR_MSG_SERVER_ASKED_RU,               KPSTLSVR_MSG_SERVER_ASKED_RU,               // "ieðko serverio"
KPSTLSVR_MSG_LOG_PROMPT_EN,                 KPSTLSVR_MSG_LOG_PROMPT_LT,                 KPSTLSVR_MSG_LOG_PROMPT_PL_1250,                 KPSTLSVR_MSG_LOG_PROMPT_PL_1257,                 KPSTLSVR_MSG_LOG_PROMPT_RU,                 KPSTLSVR_MSG_LOG_PROMPT_RU,                 // "Iðsamesni praneðimai kaupiami faile %s"
};


// ---------------------------------------------------
const unsigned char *lpszSesStates[KPST_NUM_OF_SES_STATES_1] =
{
   (unsigned char *)"SES_OPEN",
   (unsigned char *)"SES_ACTIVE",
   (unsigned char *)"SES_DONE",
   (unsigned char *)"SES_CLOSED"
};


// ---------------------------------------------------
unsigned char lpszEmptyFdf[]=
{
"%FDF-1.2\n"
// "1 0 obj<</FDF<</Fields[<</T(PI)/V 3 0 R>>]>>>>\n"
// "endobj\n"
"1 0 obj<</FDF<</Fields[]>>>>\n"
"endobj\n"
// "3 0 obj\n"
// "<</Filter[/A85]>>\n"
// "stream\n"
// "3&=6%/MoCB2(^aD1c-dX2`+D=1eKS_/M]=Y8hF%879(or;H5X^0aUun6<Z$(.5<h:.P#s20KOYU3@ZL90K1LK0f:XG4Xi<Q.r\Ba6;]%X=t_rd0f^p;.maOr#quZ?#r+7o0f988;K6MjBlQuV;)L$g4Xi<Q.g[sb#rDrD#rN#C#tm90-oF(HISN$f1Oa'F1,1dH#qu~>>\n"
// "endstream\n"
// "endobj\n"
"trailer\n"
"<</Root 1 0 R>>\n"
"%%EOF\n"
};


// ---------------------------------------------------
unsigned char lpszPageStyle[]=
{
"A:link {text-decoration: none; color: black;}\n"
"A:visited {text-decoration: none; color: black;}\n"
"A:active {text-decoration: none; color: black;}\n"
"A:hover {text-decoration: none; color: black;}\n"
"TABLE.top {\n"
"  width: 500px;\n"
"  border-collapse: collapse;\n"
"  border: 1px solid black;\n" // "  border: 2px solid black;\n"
"}\n"
"TABLE.ip {\n"
"  width: 300px;\n"
"  border-collapse: collapse;\n"
"  border: 1px solid black;\n" // "  border: 2px solid black;\n"
"}\n"
"TABLE.cons {\n"
"  width: 450px;\n"
"  border-collapse: collapse;\n"
"  border: 1px solid black;\n" // "  border: 2px solid black;\n"
"}\n"
"TD {\n" 
"    text-align: center;\n"
"   }\n"
"big { color: darkred; }\n"
"\n"
"td.ipai {\n"
"  border: 1px solid black;\n"
"  margin-left: 10px;\n"
"  margin-right: 10px;\n"
"}\n"
"td.check {\n"
"  border: 1px solid black;\n"
"  width: 24px;\n"
"}\n"
"td.rez {\n"
#ifndef Debug
"  width: 60%%;\n"
#endif
"  border: 1px solid black;\n"
"  text-align: left;\n"
// "  margin-left: 20px;\n"
"}\n"
"td.name {\n"
"  width: 45%%;\n"
"  border: 1px solid black;\n"
"  text-align: left;\n"
// "  margin-left: 20px;\n"
"}\n"
"td.msgi {\n"
"  text-align: left;\n"
// "  margin-left: 20px;\n"
"}\n"
"\n"
"td.form {\n"
"  border: 1px solid black;\n"
"  text-align: right;\n"
"  text-vertical-align: middle\n"
"}\n"
"\n"
"input.button {\n"
"   background-color:#ffffff;\n"
"   border: 2px solid;\n"
"   border-color:#000;\n"
"   width: 60 px;\n"
"}\n"
"TD.tab_a {\n"    // aktyvi asele 
"  width: %d%%;\n"
// "  border-top: 2px solid black;\n"
// "  border-bottom: 1px solid white;\n"
"  border-left: 1px solid black;\n" // "  border-left: 2px solid black;\n"
"  border-right: 1px solid black;\n" // "  border-right: 2px solid black;\n"
"}\n"
"TD.tab_n {\n"   // neaktyvi asele 
"  width: %d%%;\n"
"  background-color: #CCCCCC;\n"
"  border-bottom: 1px solid black;\n" // "  border-bottom: 2px solid black;\n"
"  border-left: 1px solid black;\n" // "  border-left: 2px solid black;\n"
"  border-right: 1px solid black;\n" // "  border-right: 2px solid black;\n"
"}\n"
"DIV.foot {\n"
"  text-align: left;\n"
"  margin-left: 20px;\n"
"}\n"
};


unsigned char lpszJavaScript[]=
{
"   function submitas(arg) {\n"
"     document.IP_adresai.ButNum.value = arg;\n"
"     if (arg == 1) {\n"
"         var tikrinam =\n"
#if (MsgLang == KpLangLt_p)
"            confirm(\"Ar tikrai norite iðmesti paþymëtus áraðus?\");\n" // KPSTLSVR_MSG_SURE_DELETE_MARKED_LT 
#elif (MsgLang == KpLangEn_p)
"            confirm(\"Are you sure you want to delete all marked records?\");\n" // KPSTLSVR_MSG_SURE_DELETE_MARKED_EN
#elif (MsgLang == KpLangPl_1250_p)
#error Reikia iðversti
#elif (MsgLang == KpLangPl_1257_p)
#error Reikia iðversti
#elif ((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
#error Reikia iðversti
#else
// praneðimai nutolusiame kliente – neiðeina iðtraukti kodø lentelës (be to kiekvienam atskiros dinamiðkai)
// be to reikëtø implementuoti dinaminá lpszJavaScript[] uþpildymà
#error Pasirenkamos kalbos nepalaikomos
#endif
"         if (tikrinam) document.IP_adresai.submit();\n"
"     }\n"
"     else document.IP_adresai.submit();\n"
"   }\n"
"\n"
"   function checkUncheckAll(theElement) {\n"
"     var theForm = theElement.form, z = 0;\n"
"     for(z=0; z<theForm.length;z++)\n"
"     if(theForm[z].type == 'checkbox') theForm[z].checked = theElement.checked;\n"
"   }\n"
};

unsigned char lpszJavaScriptLinks[]=
{
"   function submitas(arg) {\n"
"     document.IP_adresai.ButNum.value = arg;\n"
"     if (arg == 1) {\n"
"         var tikrinam =\n"
#if (MsgLang == KpLangLt_p)
"   confirm(\"Ar tikrai norite iðmesti visus prisijungimø áraðus?\");\n" // KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_LT
#elif (MsgLang == KpLangEn_p)
"   confirm(\"Are you sure you want to delete all records of connections?\");\n" // KPSTLSVR_MSG_SURE_DELETE_CONNECTIONS_EN
#elif (MsgLang == KpLangPl_1250_p)
#error Reikia iðversti
#elif (MsgLang == KpLangPl_1257_p)
#error Reikia iðversti
#elif ((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
#error Reikia iðversti
#else
// praneðimai nutolusiame kliente – neiðeina iðtraukti kodø lentelës (be to kiekvienam atskiros dinamiðkai)
// be to reikëtø implementuoti dinaminá lpszJavaScriptLinks[] uþpildymà
#error Pasirenkamos kalbos nepalaikomos
#endif
"         if (tikrinam) document.IP_adresai.submit();\n"
"     }\n"
"     else document.IP_adresai.submit();\n"
"   }\n"
};


XmlTagPars main_div_style((const unsigned char *)"align", (const unsigned char *)"center");
XmlTagPars tabs_table_style((const unsigned char *)"class", (const unsigned char *)"top");
XmlTagPars tab_a_table_cell_style((const unsigned char *)"class", (const unsigned char *)"tab_a");
XmlTagPars tab_n_table_cell_style((const unsigned char *)"class", (const unsigned char *)"tab_n");
XmlTagPars console_ref((const unsigned char *)"href", (const unsigned char *)"/console.htm");
XmlTagPars licences_ref((const unsigned char *)"href", (const unsigned char *)"/clients.htm"); // "/licences.htm");
XmlTagPars results_ref((const unsigned char *)"href", (const unsigned char *)"/results.htm");
XmlTagPars friends_ref((const unsigned char *)"href", (const unsigned char *)"/friends.htm");
XmlTagPars admins_ref((const unsigned char *)"href", (const unsigned char *)"/admins.htm");
XmlTagPars links_ref((const unsigned char *)"href", (const unsigned char *)"/links.htm");
// XmlTagPars table_style((const unsigned char *)"border", 1);
XmlTagPars table_caption_style((const unsigned char *)"bgcolor", (const unsigned char *)"#c0c0c0");
XmlTagPars *body_table_cell_centered_style_ptr=NULL;
XmlTagPars *body_table_cell_left_style_ptr=NULL;
// XmlTagPars head_style((const unsigned char *)"style", (const unsigned char *)"color: darkred; margin-left: 20px");
XmlTagPars ip_div_style((const unsigned char *)"align", (const unsigned char *)"center");
XmlTagPars ip_table_style((const unsigned char *)"class", (const unsigned char *)"ip");
XmlTagPars cons_table_style((const unsigned char *)"class", (const unsigned char *)"cons");
XmlTagPars friends_form_pars((const unsigned char *)"action", (const unsigned char *)"friends.htm");
XmlTagPars admins_form_pars((const unsigned char *)"action", (const unsigned char *)"admins.htm");
XmlTagPars links_form_pars((const unsigned char *)"action", (const unsigned char *)"links.htm");
XmlTagPars ButNum_control_description((const unsigned char *)"name", (const unsigned char *)"ButNum");

#if (MsgLang == KpLangLt_p)
const KpChar del_but_name[]={C_I, C_s_Car, C_m, C_e, C_s, C_t, C_i, C_Nul}; // "Iðmesti"
#elif (MsgLang == KpLangEn_p)
const KpChar del_but_name[]={C_D, C_e, C_l, C_e, C_t, C_e, C_Nul}; // "Delete"
#elif (MsgLang == KpLangPl_1250_p)
#error Reikia iðversti
#elif (MsgLang == KpLangPl_1257_p)
#error Reikia iðversti
#elif ((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
#error Reikia iðversti
#else
// praneðimai nutolusiame kliente – neiðeina iðtraukti kodø lentelës (be to kiekvienam atskiros dinamiðkai)
// be to reikëtø implementuoti dinaminá delete_button_description uþpildymà
#error Pasirenkamos kalbos nepalaikomos
#endif
XmlTagPars delete_button_description((const unsigned char *)"value", del_but_name);

#if (MsgLang == KpLangLt_p)
const KpChar clean_but_name[]={C_I, C_s_Car, C_v, C_a, C_l, C_y, C_t, C_i, C_Nul}; // "Iðvalyti"
#elif (MsgLang == KpLangEn_p)
const KpChar clean_but_name[]={C_C, C_l, C_e, C_a, C_r, C_Nul}; // "Clear"
#elif (MsgLang == KpLangPl_1250_p)
#error Reikia iðversti
#elif (MsgLang == KpLangPl_1257_p)
#error Reikia iðversti
#elif ((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
#error Reikia iðversti
#else
// praneðimai nutolusiame kliente – neiðeina iðtraukti kodø lentelës (be to kiekvienam atskiros dinamiðkai)
// be to reikëtø implementuoti dinaminá clean_button_description uþpildymà
#error Pasirenkamos kalbos nepalaikomos
#endif
XmlTagPars clean_button_description((const unsigned char *)"value", clean_but_name);

XmlTagPars check_all_chbox_description((const unsigned char *)"type", (const unsigned char *)"checkbox");

#if (MsgLang == KpLangLt_p)
const KpChar add_but_name[]={C_P, C_r, C_i, C_d, C_e_Adot, C_t, C_i, C_Nul}; // "Pridëti"
#elif (MsgLang == KpLangEn_p)
const KpChar add_but_name[]={C_A, C_d, C_d, C_Nul}; // "Add"
#elif (MsgLang == KpLangPl_1250_p)
#error Reikia iðversti
#elif (MsgLang == KpLangPl_1257_p)
#error Reikia iðversti
#elif ((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
#error Reikia iðversti
#else
// praneðimai nutolusiame kliente – neiðeina iðtraukti kodø lentelës (be to kiekvienam atskiros dinamiðkai)
// be to reikëtø implementuoti dinaminá add_button_description uþpildymà
#error Pasirenkamos kalbos nepalaikomos
#endif
XmlTagPars add_button_description((const unsigned char *)"value", add_but_name);

#if (MsgLang == KpLangLt_p)
const KpChar save_but_name[]={C_I, C_s_Car, C_s, C_a, C_u, C_g, C_o, C_t, C_i, C_Nul}; // "Iðsaugoti"
#elif (MsgLang == KpLangEn_p)
const KpChar save_but_name[]={C_S, C_a, C_v, C_e, C_Nul}; // "Save"
#elif (MsgLang == KpLangPl_1250_p)
#error Reikia iðversti
#elif (MsgLang == KpLangPl_1257_p)
#error Reikia iðversti
#elif ((MsgLang == KpLangRu_1251_p) || (MsgLang == KpLangRu_0_p)) 
#error Reikia iðversti
#else
// praneðimai nutolusiame kliente – neiðeina iðtraukti kodø lentelës (be to kiekvienam atskiros dinamiðkai)
// be to reikëtø implementuoti dinaminá save_button_description uþpildymà
#error Pasirenkamos kalbos nepalaikomos
#endif
XmlTagPars save_button_description((const unsigned char *)"value", save_but_name);

XmlTagPars ip_table_cell_style((const unsigned char *)"class", (const unsigned char *)"ipai");
XmlTagPars rez_table_cell_style((const unsigned char *)"class", (const unsigned char *)"rez");
XmlTagPars name_table_cell_style((const unsigned char *)"class", (const unsigned char *)"name");
XmlTagPars msgi_table_cell_style((const unsigned char *)"class", (const unsigned char *)"msgi");

XmlTagPars form_cell_style((const unsigned char *)"class", (const unsigned char *)"form");

// XmlTagPars checkbox_cell_style((const unsigned char *)"class", (const unsigned char *)"ipai");
XmlTagPars checkbox_cell_style((const unsigned char *)"class", (const unsigned char *)"check");

// XmlTagPars footnote_div_style((const unsigned char *)"align", (const unsigned char *)"left");
XmlTagPars footnote_div_style((const unsigned char *)"class", (const unsigned char *)"foot");
XmlTagPars error_div_style((const unsigned char *)"align", (const unsigned char *)"left");
XmlTagPars footnote_list_style((const unsigned char *)"style", (const unsigned char *)"list-style-type: none");


// -----------------------------------------
HRESULT TestCompilerSettingsLocal(void)
{
#include "kpstcs.cpp"
}


// --------------------------------------------
KpStLicSvr::KpStLicSvr(void)
{
HRESULT retc0;
IN_ADDR ini_adr;

// m_lhOpenResult = S_OK;

   m_lLastWindowsError = 0L;

   m_lParentProcess = 0L;
   m_lLicListThreadId = 0L;
   m_lBroadcastThreadId = 0L;
   m_pFriendList = NULL;   
   m_pFriendVarList = NULL;
   m_pAdminList = NULL;    
   m_pAdminVarList = NULL;
   m_pLinkList = NULL;
   
   m_pConsole = NULL; 
   
   m_pCurAdmins = NULL;
   
   m_iNumOfPages = 4;
   
   retc0=ReadConfig();
   if(FAILED(retc0))
   {
//    m_pAdminList=NULL;    
//    m_pLinkList=NULL;

      if(m_pFriendList == NULL)
      {
         ini_adr.S_un.S_addr = INADDR_BROADCAST; // 255.255.255.255 // INADDR_NONE;
         KP_NEW(m_pFriendList, KpTreeEntry(&ini_adr, sizeof(ini_adr), NULL));
         if((m_pFriendList == NULL) && SUCCEEDED(m_lhOpenResult))
         {
            m_lhOpenResult = KP_E_OUTOFMEM;
            KpErrorProc.OutputErrorMessage(m_lhOpenResult, null, False, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = m_pFriendList->GetOpenResult();
      
         if(SUCCEEDED(m_lhOpenResult))
         { 
            ini_adr.S_un.S_addr = KP_INADDR_LOOPBACK; // 127.0.0.1
            m_lhOpenResult = m_pFriendList->PutToEnd(&ini_adr, sizeof(ini_adr));
         }
      }
   }

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=AddConsMsg(KPSTLSVR_MSG_SERVER_STARTED);
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=PutLogMessage(KPSTLSVR_MSG_SERVER_STARTED, NULL);
}


KpStLicSvr::~KpStLicSvr(void)
{
   KP_DELETE(m_pFriendList);   
   KP_DELETE(m_pFriendVarList);
   KP_DELETE(m_pAdminList);    
   KP_DELETE(m_pAdminVarList);
   KP_DELETE(m_pLinkList);

   KP_DELETE(m_pConsole);
   
   KP_DELETE(m_pCurAdmins);
}


//-----------------------------------
HRESULT KpStLicSvr::Init(HINSTANCE hInstance, const unsigned char *lpszIniFName, LPSTR lpCmdLine)
{
HRESULT retc=S_OK;
int num_of_lics=0;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
   rez_fname[0]=Nul;

   if(SUCCEEDED(retc))
   {
      retc=InitStApp(hInstance, lpszIniFName, lpCmdLine, KpStLicSvrMode);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniRezFName(rez_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc)) 
   {
      retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
      
   m_iNumOfPages = 4 + (strlen(rez_fname)>0) + (num_of_lics>0);

return(retc);
}

//-----------------------------------
HRESULT KpStLicSvr::RefreshLicDisplay(void)
{
HRESULT retc=S_OK;
#if FALSE
int num_of_lics=0;
#ifdef Debug      
int ii;
unsigned char out_str[100];
#endif

   if(SUCCEEDED(retc))
   {
      retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   
   if(num_of_lics && SUCCEEDED(retc))
   {
      if((m_pLicArray==NULL) && SUCCEEDED(retc))
      {
         retc=KP_E_SYSTEM_ERROR;
         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   
#if FALSE // #ifdef Debug      
sprintf((char *)out_str, "SessionID: %d  LicID: %d  ProdVer: %d",
   cMemBank[KP11_REM_SESID/2] /* m_iRemSesID */,
   cMemBank[KP11_REM_LICID/2] /* m_iRemLicID */,
   cMemBank[KP11_REM_PRODVER/2] /* m_iRemProdVer */);
KpStLicSvrCons.AddString(out_str);
#endif      

#if FALSE // #ifdef Debug
      if(SUCCEEDED(retc)) retc=KpStLicSvrCons.AddString("------------------------------");
   
      for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
      {
         sprintf((char *)out_str, "Busy: %d  SessionID: %5d    Host: %s  Timeout: %2d:%02d", 
                                 m_pLicArray[ii].m_iLicState, 
                                             m_pLicArray[ii].m_iSessionID, 
                                                   inet_ntoa(m_pLicArray[ii].m_Host), 
                                                         m_pLicArray[ii].m_iSecondsToKill/KP_SECS_PER_MIN, 
                                                               m_pLicArray[ii].m_iSecondsToKill%KP_SECS_PER_MIN);
         retc=KpStLicSvrCons.AddString(out_str);
      }
   
      if(SUCCEEDED(retc)) retc=KpStLicSvrCons.AddString("------------------------------");
#endif
   
   } // if(num_of_lics && SUCCEEDED(retc))
#endif
   
return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::AddConsMsg(const unsigned char *lpszMsg)
{
HRESULT retc=S_OK;
KpTreeEntry *cur_top;
struct tm *tm_time=NULL;
time_t t_time;
// unsigned char *pntd;
unsigned char out_msg[KP_MAX_FILE_LIN_LEN+1];

   if((lpszMsg==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      time(&t_time);
      tm_time=localtime(&t_time);
      if((tm_time==NULL) && SUCCEEDED(retc))
      {
         retc=KP_E_SYSTEM_ERROR;
         KpErrorProc.OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
   }
   if(SUCCEEDED(retc))
   {
//    strcpy(out_msg, asctime(tm_time));
      sprintf((char *)out_msg, "%d.%02d.%02d %02d:%02d:%02d \xA0\xA0", // C_NBSP 
         tm_time->tm_year+1900, tm_time->tm_mon+1, tm_time->tm_mday,
         tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);   
//    pntd=strchr(out_msg, '\n');
//    if(pntd) *pntd=Nul;
   }

   if(SUCCEEDED(retc)) if(strlen(out_msg)+strlen(lpszMsg)+3 >= KP_MAX_FILE_LIN_LEN)
   {
      retc=KP_E_BUFFER_OVERFLOW;
      KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   { 
//    strcat(out_msg, ": ");
      strcat(out_msg, lpszMsg);
   }
   
   if(m_pConsole != NULL) retc = m_pConsole->PutToEnd(out_msg);
   else
   {
      KP_NEWO(m_pConsole, KpTreeEntry(out_msg, NULL));
   }
   
   if(SUCCEEDED(retc))
   {
int ii = 0;
      retc = m_pConsole->CountEntries(&ii, 0, m_pConsole);
      if((ii > KPST_NUM_OF_CONSOLE_LINES) && SUCCEEDED(retc))
      {
         retc = m_pConsole->GetFirstChild(&cur_top);
         if(SUCCEEDED(retc)) retc = m_pConsole->SetFirstChild(NULL);
      }
   }

   KP_DELETE(m_pConsole);

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::OutputErrorMessageLocal
(
HRESULT lhRetc,
const unsigned char *lpszMessageText,
bool bSevereError,
bool bLogMessage
)
{
HRESULT retc=S_OK;
unsigned char out_msg[2*KP_MSG_LEN+1];

   if(SUCCEEDED(retc)) strcpy(out_msg, bSevereError?KPSTLSVR_MSG_ERROR:KPSTLSVR_MSG_WARNING);
   
   if(SUCCEEDED(retc)) retc=KpErrorProc.FormatErrorMessage(lhRetc, out_msg+strlen(out_msg));
   
   if(lpszMessageText && SUCCEEDED(retc))
   {
      if(strlen(out_msg)+strlen(lpszMessageText)+3 >= 2*KP_MSG_LEN)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
      { 
         strcat(out_msg, "; ");
         strcat(out_msg, lpszMessageText);
      }
   }
   if(SUCCEEDED(retc)) retc=AddConsMsg(out_msg);

   if(bLogMessage && SUCCEEDED(retc)) retc=PutLogMessage(out_msg, NULL);
   
return(retc);
}


HRESULT KpStLicSvr::OutputErrorMessage
(
HRESULT lhRetc,
const unsigned char *lpszMessageText,
bool bSevereError,
const char *lpszSourceFile,
int iSourceLine,
long lMainKeyId,
KpConsole *pListBox
)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc))
      retc=OutputErrorMessageLocal(lhRetc, lpszMessageText, bSevereError, False);
   
   if(SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(lhRetc, lpszMessageText, bSevereError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox);

return(retc);
}


HRESULT KpStLicSvr::OutputErrorMessage
(
HRESULT lhRetc,
LONG lWindowsErrorCode,
bool bSevereError,
const char *lpszSourceFile,
int iSourceLine,
long lMainKeyId,
KpConsole *pListBox
)
{
HRESULT retc=S_OK;
unsigned char out_msg[KP_MAX_FILE_LIN_LEN+1];

   retc=KpErrorProc.FormatErrorMessageSystem(lWindowsErrorCode, out_msg, False); 
   
   if(SUCCEEDED(retc))
      retc=OutputErrorMessage(lhRetc, out_msg, bSevereError, lpszSourceFile, iSourceLine, lMainKeyId, pListBox);

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::PutChar(TvXmlFile *pOutFile, KpChar iOutCh, bool bCheckFlg)
{
HRESULT retc=S_OK;

   if((pOutFile==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {   
      retc=pOutFile->PutChar(iOutCh, bCheckFlg);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }

return(retc);
}


HRESULT KpStLicSvr::PutCharProc(TvXmlFile *pOutFile, KpChar iOutCh, XmlTagPars *pTagPar, bool bCheckIndex)
{
HRESULT retc=S_OK;

   if((pOutFile==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {   
      retc=pOutFile->PutCharProc(iOutCh, pTagPar, bCheckIndex);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }

return(retc);
}


HRESULT KpStLicSvr::PutStr(TvXmlFile *pOutFile, const unsigned char *lpszOutStr)
{
HRESULT retc=S_OK;

   if((pOutFile==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {   
      retc=pOutFile->PutStr(lpszOutStr);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }

return(retc);
}


HRESULT KpStLicSvr::PutKpStr(TvXmlFile *pOutFile, const KpChar *iazOutStr)
{
HRESULT retc=S_OK;

   if((pOutFile==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {   
      retc=pOutFile->PutKpStr(iazOutStr);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::AddIPConsMsg(const unsigned char *lpszMsg, bool bLogMessage, KpSocket *pKpSocket)
{
HRESULT retc=S_OK;
unsigned char out_msg[KP_MAX_FILE_LIN_LEN+1];

   if(((lpszMsg==NULL) || (pKpSocket == NULL)) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   if((m_pLicListSocket==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }
   
   if(SUCCEEDED(retc))
      if(strlen(m_pLicListSocket->m_PackedUrl.lpszServerName)+strlen(lpszMsg)+1 > KP_MAX_FILE_LIN_LEN)
      {
         retc=KP_E_BUFFER_OVERFLOW;
         KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   
   if(SUCCEEDED(retc))
   {
      strcpy(out_msg, pKpSocket->m_PackedUrl.lpszServerName);
      strcat(out_msg, " ");
      strcat(out_msg, lpszMsg);
      retc=AddConsMsg(out_msg);
   }

   if(bLogMessage && SUCCEEDED(retc)) retc=PutLogMessage(out_msg, NULL);
   
return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::FormatLicencesPage(unsigned char **plpszPagePtrPtr)
{
HRESULT retc=S_OK;
unsigned char title[KP_MAX_FNAME_LEN+100];
KpChar i_title[KP_MAX_FNAME_LEN+100];
KpChar l_title[KP_MAX_FNAME_LEN+100];
KpChar i_heading[KP_MAX_FNAME_LEN+100];
long buf_len=0L;
unsigned char *buf_ptr=NULL;
TvXmlFile *out_file=NULL;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
KpChar i_str_buf[KP_MAX_FNAME_LEN+1];
// int len;
XmlTagPars *tag_pars=NULL;
int ii;
KpTreeEntry *cur_ip_entry=NULL; // rodykle po *ip_list_ptr 
unsigned char *page_style=NULL;
KpTreeEntry *var_rec_entry_ptr=NULL;  // rodykle po *saved_var_list_ptr
PostVarRec *var_rec_ptr=NULL;          // rodykle i kintamojo aprasa irase var_rec_entry_ptr
const unsigned char *val_ptr=NULL;
const unsigned char *pnts;
int num_of_lics=0;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
   rez_fname[0]=Nul;
KpChar lic_bus_txt[KP_MAX_FNAME_LEN+1];
   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN;
      retc=KptStrEncode(lic_bus_txt, KPSTLSVR_MSG_CLIENT_STATUS, /* &len, */ TV_CPP_SOURCE_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

   if((plpszPagePtrPtr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniRezFName(rez_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   
   if(SUCCEEDED(retc))
   {
      retc=GetIniProdName(title);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
         
   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(title);
      retc=KptStrEncode(i_title, title, /* &len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) TvKpStrCpy(l_title, i_title);
   if(SUCCEEDED(retc)) TvKpStrLat(l_title);
   if(SUCCEEDED(retc))
   {
      retc=KptStrDecode(title, l_title, /* len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcat(title, KPSTLSVR_MSG_STATUS);

   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(heading);
      retc=KptStrEncode(i_heading, KPSTLSVR_MSG_CLIENTS_STATUS, /* &len, */ TV_CPP_SOURCE_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      buf_len=KP_MAX_FILE_LIN_LEN*(num_of_lics+1); // !!!! tiksliau pamatuot
      KP_NEWA(buf_ptr, unsigned char, buf_len);
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%x %x", buf_ptr, buf_len);
      KP_NEWO(out_file, TvXmlFile(str_buf, (const unsigned char *)"w", XL_FT_DataFile,
                        CreateNewUniBFile, plpszaHtmSpecCharTags,
                        TV_XL_NUM_LEN, (KpChar)HTM_TG_FirstTag, plpszaHtmlTags, True, 
                        XM_VERS_HTML401_TRANS, iaHtmNulCodeTables /* iaHtmCodeTables71 */, True, False));
   }


   if(SUCCEEDED(retc)) 
   {
//    retc=out_file->SetEncoding(UC_No_Mode, TV_CTBL_ASCII, TV_CTBL_ASCII);
      retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_NO_CTBL);
//    retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_CPP_SOURCE_CTBL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }

// ----------------------------------
   KP_NEWA(page_style, unsigned char, strlen(lpszPageStyle) + 1);
   if(SUCCEEDED(retc))
   {
      sprintf((char *)page_style, (const char *)lpszPageStyle, 100/m_iNumOfPages, 100/m_iNumOfPages);
      retc=PutHtmHat(out_file, title, NULL, NULL, KP_LNG_LIT, KPST_SRV_REFRESH_TIMEOUT, page_style, NULL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   
   KP_DELETEA(page_style);

// ----------------------------------
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &main_div_style, False);

// ----------------------------------
      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &tabs_table_style, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
   
// ---------------------------------- tabs
            if((strlen(rez_fname)>0) && SUCCEEDED(retc)) // !!!! TODO kaþkà rodyt ir licencijø serverio reþime
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &links_ref, False);
                     if(SUCCEEDED(retc))
                     {
                        retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_STATUS, TV_CPP_SOURCE_CTBL);
                        if(FAILED(retc))
                           retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if((num_of_lics>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_a_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_CLIENTS);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
            
            if((strlen(rez_fname)>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &results_ref, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_RESULTS);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &console_ref, False);
                  if(SUCCEEDED(retc))
                  {
//                   len=KP_MAX_FNAME_LEN+100-1;
                     retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_MESSAGES, /* &len, */ TV_CPP_SOURCE_CTBL);
                     if(FAILED(retc))
                        retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &friends_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_NETWORK);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &admins_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_ADMINS);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
   
// ---------------------------- heading
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_heading);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

// ---------------------------- licenciju lenteles kepure
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &ip_div_style, False);

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &ip_table_style, False);

                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, &table_caption_style, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                           if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_ORDER_NO);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                           if(SUCCEEDED(retc)) retc=PutKpStr(out_file, lic_bus_txt);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                           if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_SESSION_ID);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                           if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_CLIENT_IP);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                           if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_REST_MIN);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

// ---------------------------- licenciju lentele
                     for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
                     {
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                              if(SUCCEEDED(retc)) sprintf((char *)str_buf, "%d", ii+1);
                              if(SUCCEEDED(retc)) retc=PutStr(out_file, str_buf);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                                 if(SUCCEEDED(retc)) switch(m_pLicArray[ii].m_iLicState)
                                 {
                                 case KpstLicFree:
                                    retc=PutCharProc(out_file, C_NBSP, NULL, False);
                                    break;
                                 case KpstLicLost:
                                    retc=PutCharProc(out_file, C_MidRing, NULL, False);
                                    break;
                                 case KpstLicBusy:
                                    retc=PutCharProc(out_file, C_Bpoint, NULL, False);
                                    break;
                                 }
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                              if(SUCCEEDED(retc)) sprintf((char *)str_buf, "%d", m_pLicArray[ii].m_iSessionID);
                              if(SUCCEEDED(retc)) retc=PutStr(out_file, str_buf);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                              if(SUCCEEDED(retc))
                              {
                                 pnts=(const unsigned char *)inet_ntoa(m_pLicArray[ii].m_Host);
                                 if(pnts==NULL)
                                 {
                                    retc=E_INVALIDARG;
                                    OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
                                 }
                              }
                              if(SUCCEEDED(retc)) retc=PutStr(out_file, pnts);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                              if(SUCCEEDED(retc)) sprintf((char *)str_buf, "%d", (m_pLicArray[ii].m_iSecondsToKill+KP_SECS_PER_MIN/2)/KP_SECS_PER_MIN);
                              if(SUCCEEDED(retc)) retc=PutStr(out_file, str_buf);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                     
                     } // for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
   
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

// ------------------------------------
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, lic_bus_txt);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Colon, NULL, False); // ':'
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_UL, &footnote_list_style, False);

                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Bpoint, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                        if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                        if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                        if(SUCCEEDED(retc))
                        {
//                         len=KP_MAX_FNAME_LEN;
                           retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_SESSION_ACTIVE, /* &len, */ TV_CPP_SOURCE_CTBL);
                           if(FAILED(retc))
                              retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                        }
                        if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);
   
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_MidRing, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                        if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                        if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                        if(SUCCEEDED(retc))
                        {
//                         len=KP_MAX_FNAME_LEN;
                           retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_LOST_CONNECTION, /* &len, */ TV_CPP_SOURCE_CTBL);
                           if(FAILED(retc))
                              retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                        }
                        if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);

                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                        if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                        if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                        if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_SLOT_FREE);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_UL_e, NULL, False);

               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_REST_MIN_);
                  if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                  if(SUCCEEDED(retc))
                  {
//                   len=KP_MAX_FNAME_LEN;
                     retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_LOST_CLI_TIME, /* &len, */ TV_CPP_SOURCE_CTBL);
                     if(FAILED(retc))
                        retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);

// ------------------------------------
   if(SUCCEEDED(retc))
   {
      retc=PutHtmTail(out_file);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   
// ------------------------------------
   KP_DELETE(out_file);
   
   if(SUCCEEDED(retc)) *plpszPagePtrPtr = buf_ptr;
   else
   {
      KP_DELETEA(buf_ptr);
   }

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::CheckName(unsigned long ulNameVal, unsigned char *lpszNameBuf, const unsigned char *lpszNamePtr, unsigned char *lpszNameBufOut, 
   int *
#ifdef KPSTLSVR_TEST_CODE_NAME
      piErrLine
#endif
   )
{
HRESULT retc = S_OK;
int ii;
int jj;
unsigned long out_ch;
unsigned char nam_buf[KPST_TXTCD_CHARS_PER_VAL_NAME * 2 + 1];
unsigned char *pntd = null;

   KP_SVR_ASSERT(lpszNameBuf, E_INVALIDARG, null, True);
   KP_SVR_ASSERT(lpszNamePtr, E_INVALIDARG, null, True);
// KP_SVR_ASSERT(lpszNameBufOut, E_INVALIDARG, null, True);
                                 
   if(lpszNameBuf) lpszNameBuf[0] = Nul;

// kontrolinis bitas
   ii = ulNameVal & 0x3;
   if((ii != 0x1) && (ii != 0x2))
   {
      retc = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME
      if(piErrLine) *piErrLine = __LINE__;
#endif      
   }  

// iðkoduojam
   if(SUCCEEDED(retc))
   {
      if(ulNameVal && SUCCEEDED(retc))
      {
         for(ii=0; (ii < KPST_TXTCD_CHARS_PER_VAL_NAME) && SUCCEEDED(retc); ii++)
         {
            out_ch = ulNameVal / 2; // dar numetam jauniausia bita - ch. suma
            for(jj = ii; jj < KPST_TXTCD_CHARS_PER_VAL_NAME - 1; jj++) out_ch /= KPST_TXTCD_RADIX_NAME;
            out_ch %= KPST_TXTCD_RADIX_NAME;
            out_ch += KPST_TXTCD_BASE_NAME; 
            lpszNameBuf[ii] = (unsigned char)out_ch;
         }
         lpszNameBuf[KPST_TXTCD_CHARS_PER_VAL_NAME] = Nul;
      }
   }

// tikrinam
   if(SUCCEEDED(retc))
   {
      strncpy(nam_buf, lpszNamePtr, KPST_TXTCD_CHARS_PER_VAL_NAME);
      nam_buf[KPST_TXTCD_CHARS_PER_VAL_NAME] = Nul;
      retc = CutInitTrailSpcs(nam_buf);
#ifdef KPSTLSVR_TEST_CODE_NAME
      if(piErrLine && FAILED(retc)) *piErrLine = __LINE__;
#endif      
   }
   if(SUCCEEDED(retc))
   {
      strcat(nam_buf, "@@@@@@"); // KPST_TXTCD_CHARS_PER_VAL_NAME
      nam_buf[KPST_TXTCD_CHARS_PER_VAL_NAME] = Nul;
      TvStrLat(nam_buf, KPST_DATA_FILE_CTBL);
      TvStrUprLat(nam_buf);
      
// ' ' --> '@'
      pntd = nam_buf;
      while(*pntd)
      {
         if(*pntd == Spc) *pntd = '@'; // ' '
         pntd++;
      }
      
      if(strcmp(nam_buf, lpszNameBuf) != 0) retc = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME
      if(piErrLine && FAILED(retc)) *piErrLine = __LINE__;
#endif
      if(lpszNameBufOut) strcpy(lpszNameBufOut, nam_buf);      
   } 
   
return(retc);   
}
                        

//-----------------------------------
HRESULT KpStLicSvr::FormatResultsPage(unsigned char **plpszPagePtrPtr)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HRESULT reta=S_OK;
unsigned char title[KP_MAX_FNAME_LEN+100];
KpChar i_title[KP_MAX_FNAME_LEN+100];
KpChar l_title[KP_MAX_FNAME_LEN+100];
KpChar i_heading[KP_MAX_FNAME_LEN+100];
long buf_len=0L;
unsigned char *buf_ptr=NULL;
TvXmlFile *out_file=NULL;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
// int len;
XmlTagPars *tag_pars=NULL;
unsigned char *page_style=NULL;
const unsigned char *pnts;
unsigned char *pntd;
unsigned char *pntd1;
const unsigned char *name_ptr = (const unsigned char *)"";
const unsigned char *surname_ptr = (const unsigned char *)"";
const unsigned char *klas_ptr = NULL;
unsigned char *rez_file_buf = NULL;
int row_cnt=0;
int add_row=0;
long rez_flen;
int num_of_lics=0;
int field_cnt=0;
int shuff_cnt=0;
int name1_pos=0; // vardo pirmu 4 baitu lauko numeris
int name2_pos=0; // vardo tolesniu 4 baitu lauko numeris
int testc_pos=0; // testo ID lauko numeris
int date_pos=0; // datos lauko numeris
unsigned long name1_val=0; // vardo pirmu 4 baitu lauko reiksme
unsigned char name1_buf[KPST_TXTCD_CHARS_PER_VAL_NAME+1];
// static unsigned char name_buf_out[KPST_TXTCD_CHARS_PER_VAL_NAME+1];
//    name_buf_out[0] = Nul;
unsigned long name2_val=0; // vardo tolesniu 4 baitu lauko reiksme
unsigned char name2_buf[KPST_TXTCD_CHARS_PER_VAL_NAME+1];
unsigned long testc_val=0; // testo ID lauko reiksme
unsigned long date_val=0; // datos lauko reiksme
unsigned char testc_str[KPST_TXTCD_CHARS_PER_VAL_TID+1];
   testc_str[0]=Nul;
unsigned char testc[KPST_TXTCD_CHARS_PER_VAL_TID+1];
int ii;
int jj;
unsigned char sav_ch;
long out_ch;
struct tm *tm_time=NULL;
time_t t_time;
unsigned char rez_vars[KP_MAX_FNAME_LEN+1];
   rez_vars[0]=Nul;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
   rez_fname[0]=Nul;
// #ifdef KPSTLSVR_TEST_CODE_NAME                  
int err_line = 0;
// #endif


   if((plpszPagePtrPtr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniRezFName(rez_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniRezVar(rez_vars);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   { 
      retc=GetIniShuffCnt(&shuff_cnt);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   { 
      retc=GetIniTestCid(testc);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
      if(SUCCEEDED(retc)) retc = CutTrailSpcs(testc);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniProdName(title);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(title);
      retc=KptStrEncode(i_title, title, /* &len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) TvKpStrCpy(l_title, i_title);
   if(SUCCEEDED(retc)) TvKpStrLat(l_title);
   if(SUCCEEDED(retc))
   { 
      retc=KptStrDecode(title, l_title, /* len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcat(title, KPSTLSVR_MSG_RESULTS);

   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(heading);
      retc=KptStrEncode(i_heading, KPSTLSVR_MSG_TEST_RESULTS, /* &len, */ TV_CPP_SOURCE_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

// --------------- lauku skaicius
   if(SUCCEEDED(retc))
   {
      retc=CutInitTrailSpcs(rez_vars);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      if(rez_vars[0]==Nul) field_cnt=0;
      else
      {
         retc=CountStrings(&field_cnt, rez_vars, (const unsigned char *)" ", True);
         if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
      }
   }
   if(field_cnt && SUCCEEDED(retc))
      if(field_cnt - 3 /* -(shuff_cnt?1:0) */ < shuff_cnt) // be vardo, pavardes, klases ir sumaisymu kaukes
      {                                                  // shuff_val i field_cnt neieina 
         retc = KP_E_SYSTEM_ERROR;
         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, field_cnt);
      }


// -------------------------
   if(SUCCEEDED(retc)) if(strlen(rez_fname)==0)
   {
      retc=KP_E_ILLFUNC;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc))
   {
      retc=ReadFileContents(rez_fname, &rez_file_buf, &rez_flen, False, False);
      if(retc==KP_E_FILE_NOT_FOUND)
      {
         retc = S_OK;
         KP_NEWA(rez_file_buf, unsigned char, 1);
         if(SUCCEEDED(retc))
         {
            rez_file_buf[0] = Nul;
            rez_flen = 1;
         }
      }
      else if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }         
   
// -------------------------
   if(SUCCEEDED(retc))
   {
      buf_len=KP_MAX_FILE_LIN_LEN+rez_flen*10; // !!!! tiksliau pamatuot
      KP_NEWA(buf_ptr, unsigned char, buf_len);
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%x %x", buf_ptr, buf_len);
      KP_NEWO(out_file, TvXmlFile(str_buf, (const unsigned char *)"w", XL_FT_DataFile,
                        CreateNewUniBFile, plpszaHtmSpecCharTags,
                        TV_XL_NUM_LEN, (KpChar)HTM_TG_FirstTag, plpszaHtmlTags, True, 
                        XM_VERS_HTML401_TRANS, iaHtmNulCodeTables /* iaHtmCodeTables71 */, True, False));
   }

#if FALSE
UC_Modes enc_mode;
int ctbl, def_ctbl; // = out_file->m_lpLowLevelFile->m_iCodeTable;
out_file->GetEncoding(&enc_mode, &ctbl, &def_ctbl); 
#endif         

   if(SUCCEEDED(retc))
   {
//    retc=out_file->SetEncoding(UC_No_Mode, TV_CTBL_ASCII, TV_CTBL_ASCII);
      retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_NO_CTBL);
//    retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_CPP_SOURCE_CTBL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
         
// ----------------------------------
   KP_NEWA(page_style, unsigned char, strlen(lpszPageStyle) + 1);
   if(SUCCEEDED(retc))
   {
      sprintf((char *)page_style, (const char *)lpszPageStyle, 100/m_iNumOfPages, 100/m_iNumOfPages);
      retc=PutHtmHat(out_file, title, NULL, NULL, KP_LNG_LIT, KPST_SRV_REFRESH_TIMEOUT, page_style, NULL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   KP_DELETEA(page_style);


#if FALSE
sprintf((char *)str_buf, "=== %d %d %d ===\n", enc_mode, ctbl, def_ctbl);   
out_file->PutStr(str_buf);

out_file->GetEncoding(&enc_mode, &ctbl, &def_ctbl); 
sprintf((char *)str_buf, "=== %d %d %d ===\n", enc_mode, ctbl, def_ctbl);   
out_file->PutStr(str_buf);
#endif

// ----------------------------------
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &main_div_style, False);

// ----------------------------------
      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &tabs_table_style, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
   
// ---------------------------------- tabs
            if((strlen(rez_fname)>0) && SUCCEEDED(retc)) // !!!! TODO kaþkà rodyt ir licencijø serverio reþime
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &links_ref, False);
                     if(SUCCEEDED(retc))
                     {
                        retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_STATUS, TV_CPP_SOURCE_CTBL);
                        if(FAILED(retc))
                           retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if((num_of_lics>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &licences_ref, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_CLIENTS);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
            
            if((strlen(rez_fname)>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_a_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_RESULTS);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &console_ref, False);
                  if(SUCCEEDED(retc))
                  {
//                   len=KP_MAX_FNAME_LEN+100-1;
                     retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_MESSAGES, /* &len, */ TV_CPP_SOURCE_CTBL);
                     if(FAILED(retc))
                        retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &friends_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_NETWORK);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &admins_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_ADMINS);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         row_cnt++;
   
// ---------------------------- heading
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_heading);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         row_cnt++;

         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &ip_div_style, False);

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &cons_table_style, False);

// ---------------------------- rezultatu lentele
                     if(SUCCEEDED(retc))
                     {
// formatuoti, koduoti, sumaisyti arkim duomenys
                        if(field_cnt)
                        {
                           pnts=rez_file_buf;
                           while((*pnts) && SUCCEEDED(retc))
                           {
                              reta = S_OK;
                           
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);

                                 pntd = (unsigned char *)pnts;
// vardo-pavardes ptr
                                 name_ptr = pntd;
                                 while((*pntd!=C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
//                               if(*pntd==C_Ht) *pntd++ = Spc;
                                 if(*pntd==C_Ht) *pntd++ = Nul;
                                 surname_ptr = pntd;
                                 while((*pntd!=C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
                                 if(*pntd) *pntd++=Nul;
// praleidziam klase/asm. koda
                                 pnts = pntd;
                                 while((*pntd!=C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
                                 if(*pntd) *pntd++=Nul;
// ---------- klasës ptr
                                 klas_ptr = pnts;
                                 pntd1 = strstr(pnts, "kl");
                                 if(pntd1)
                                 {
                                    *pntd1++ = Nul;
//                                  klas_fl = True;                                    
                                 }                                    
                                 else klas_ptr = NULL;
// -----------                                    
                                 pnts = pntd;
                              
                                 if(shuff_cnt)
                                 {
// --------- praleidþiam nemaiðytus laukus
                                    for(ii = 0; ii < field_cnt-3-shuff_cnt; ii++) // be vardo, pavardes ir klases
                                    {
                                       while((*pntd != C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
                                       if(*pntd == C_Ht) *pntd++;
                                    }

                                    if(SUCCEEDED(retc))
                                    {
                                       name1_pos = 0;
                                       name2_pos = 0;
                                       testc_pos = 0;
                                       date_pos = 0;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                       err_line = 0; 
#endif
                                       
// -------- ieðkom po sumaiðymø kaukæ 
                                       for(ii=0; (ii<shuff_cnt) && SUCCEEDED(retc); ii++)
                                       {
                                          if(pntd[ii]-'0' == shuff_cnt - 3 /* 4 */) // uzkoduotas vardas - ketvirtas laukas
                                          {
                                             if(name1_pos!=0)
                                             {
                                                reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                                err_line = __LINE__; 
#endif
#ifdef Debug
                                                KpErrorProc.OutputErrorMessage(reta, null, False, __FILE__, __LINE__, 0L);
#endif
                                             }
                                             else name1_pos=ii+1;
                                          }
                                          if(pntd[ii]-'0' == shuff_cnt - 2 /* 5 */) // uzkoduota pavarde - penktas laukas
                                          {
                                             if(name2_pos!=0)
                                             {
                                                reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                                err_line = __LINE__; 
#endif
#ifdef Debug
                                                KpErrorProc.OutputErrorMessage(reta, null, False, __FILE__, __LINE__, 0L);
#endif
                                             }
                                             else name2_pos=ii+1;
                                          }
                                          if(pntd[ii]-'0' == shuff_cnt - 1 /* 6 */) // testo ID laukas priespaskutinis
                                          {
                                             if(testc_pos!=0)
                                             {
                                                reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                                err_line = __LINE__; 
#endif
#ifdef Debug
                                                KpErrorProc.OutputErrorMessage(reta, null, False, __FILE__, __LINE__, 0L);
#endif
                                             }
                                             else testc_pos=ii+1;
                                          }
                                          if(pntd[ii]-'0' == shuff_cnt /* 7 */) // datos laukas paskutinis
                                          {
                                             if(date_pos!=0)
                                             {
                                                reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                                err_line = __LINE__; 
#endif
#ifdef Debug
                                                KpErrorProc.OutputErrorMessage(reta, null, False, __FILE__, __LINE__, 0L);
#endif
                                             }
                                             else date_pos=ii+1;
                                          }
                                       }  
                                       if(
                                          (
                                             (name1_pos==0) ||
                                             (name2_pos==0) ||
                                             (testc_pos==0) ||
                                             (date_pos==0)
                                          ) && 
                                          SUCCEEDED(retc) &&
                                          SUCCEEDED(reta)
                                         )
                                       {
                                          reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                          err_line = __LINE__; 
#endif
#ifdef Debug
                                          KpErrorProc.OutputErrorMessage(reta, null, False, __FILE__, __LINE__, 0L);
#endif
                                       }
                                    }
// ------------ praleidþiam sumaiðymø kaukæ                               
                                    if(SUCCEEDED(retc) && SUCCEEDED(reta))
                                    {
                                       while((*pntd!=C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
                                       if(*pntd==C_Ht) *pntd++;
                                    }
                                 }
                                 else // if(shuff_cnt)
                                 {
                                 // be vardo, pavardes ir klases
                                    name1_pos = field_cnt - 3 - 4; // 1;
                                    name2_pos = field_cnt - 3 - 3; // 2;
                                    testc_pos = field_cnt - 3 - 2;
                                    date_pos = field_cnt - 3 - 1; 
                                 }

// ---------- skaitom laukø reikðmes
                                 if(SUCCEEDED(retc) && SUCCEEDED(reta))
                                 {
                                    name1_val = 0;
                                    name2_val = 0;
                                    testc_val = 0;
                                    date_val = 0; 
                        
                                    for(ii = 0; ii<(shuff_cnt?shuff_cnt:(field_cnt - 3)); ii++) // be vardo, pavardes ir klases
                                    {
                                       if(ii + 1 == name1_pos)
                                          if(sscanf((const char *)pntd, "%lu", &name1_val)<1)
                                          {
                                             name1_val = 0L;
                                             reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                             err_line = __LINE__; 
#endif
#ifdef Debug
                                             KpErrorProc.OutputErrorMessage(reta, pntd, False, __FILE__, __LINE__, 0L);
#endif
                                          }
                                       if(ii + 1 == name2_pos)
                                          if(sscanf((const char *)pntd, "%lu", &name2_val)<1)
                                          {
                                             name2_val = 0L;
                                             reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                             err_line = __LINE__; 
#endif
#ifdef Debug
                                             KpErrorProc.OutputErrorMessage(reta, pntd, False, __FILE__, __LINE__, 0L);
#endif
                                          }
                                       if(ii + 1 == testc_pos)
                                          if(sscanf((const char *)pntd, "%lu", &testc_val)<1)
                                          {
                                             testc_val = 0L;
                                             reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                             err_line = __LINE__; 
#endif
#ifdef Debug
                                             KpErrorProc.OutputErrorMessage(reta, pntd, False, __FILE__, __LINE__, 0L);
#endif
                                          }
                                       if(ii + 1 == date_pos)
                                          if(sscanf((const char *)pntd, "%lu", &date_val)<1)
                                          {
                                             date_val = 0L;
                                             reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                             err_line = __LINE__; 
#endif
#ifdef Debug
                                             KpErrorProc.OutputErrorMessage(reta, pntd, False, __FILE__, __LINE__, 0L);
#endif
                                          }
                                       
                                       while((*pntd != C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
                                       if(*pntd == C_Ht) *pntd++;
                                    }
                                 }
// ------------- iðvedam datà                                 
                                 if(SUCCEEDED(retc))
                                 {
                                    time(&t_time);
                                    tm_time=localtime(&t_time);
                                    if((tm_time==NULL) && SUCCEEDED(retc))
                                    {
                                       retc=KP_E_SYSTEM_ERROR;
                                       OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                                    }
                                 }
                                 strcpy(str_buf, "???");
                                 if((date_val!=0) && SUCCEEDED(retc))
                                 {
                                    sprintf((char *)str_buf, "%04d.%02d.%02d %02d:%02d",
                                          tm_time->tm_year+1900, (date_val / 32) % 16 + 1, date_val % 32,
                                          (date_val / (32 * 16)) % 32, (date_val / (32 * 16 * 32)) % 64); 
                                 }
                              
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                    if(SUCCEEDED(retc)) retc=PutStr(out_file, str_buf);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                        
// -------- iðvedam vardà, pavardæ      
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, 
                                       /* (testc[0])?&name_table_cell_style: */ &rez_table_cell_style, False); // name_table_cell_style siauresnë - lieka vietos ðauktukui
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
                                    if(SUCCEEDED(retc))
                                    {
//                                     len=KP_MAX_FNAME_LEN+100-1;
                                       retc0 = KptStrEncode(l_title, name_ptr, /* &len, */ KPST_DATA_FILE_CTBL);
                                       if(FAILED(retc0))
                                       {
                                          reta = retc0;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                          err_line = __LINE__; 
#endif
#ifdef Debug
                                          KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L);
#endif
                                       }
                                    }
                                    if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);

                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);

                                    if(SUCCEEDED(retc))
                                    {
//                                     len=KP_MAX_FNAME_LEN+100-1;
                                       retc0 = KptStrEncode(l_title, surname_ptr, /* &len, */ KPST_DATA_FILE_CTBL);
                                       if(FAILED(retc0))
                                       {
                                          reta = retc0;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                          err_line = __LINE__; 
#endif
#ifdef Debug
                                          KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L);
#endif
                                       }
                                    }
                                    if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

// -------- tikrinam uþkoduotus vardà, pavardæ      
                                 retc0 = CheckName(name1_val, name1_buf, name_ptr, null /* name_buf_out */, &err_line);
                                 if(SUCCEEDED(retc) && SUCCEEDED(reta))
                                 {
                                    reta = retc0; 
#ifdef KPSTLSVR_TEST_CODE_NAME                  
//                                  if(FAILED(retc0)) err_line = __LINE__;
#endif
                                 } 
                                 retc0 = CheckName(name2_val, name2_buf, surname_ptr, null /* name_buf_out */, &err_line);
                                 if(SUCCEEDED(retc) && SUCCEEDED(reta))
                                 {
                                    reta = retc0; 
#ifdef KPSTLSVR_TEST_CODE_NAME                  
//                                  if(FAILED(retc0)) err_line = __LINE__;
#endif
                                 }
                                                                  
// -------- iðvedam klasæ/kodà                
                                 if(SUCCEEDED(retc)) if(klas_ptr)
                                 {
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                       if(SUCCEEDED(retc))
                                       {
                                          if(/* klas_fl && */ SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_CLASS_PREFIX);
                                          if(SUCCEEDED(retc)) retc=PutStr(out_file, klas_ptr);
                                          if(/* klas_fl && */ SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_CLASS_POSTFIX);
                                       }
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                                 }
                        
// --------- tikrinam testo kodà          
                                 if(SUCCEEDED(retc)) if(testc[0]) // tikrinam, tik jei testc<>""
                                 {
                                    testc_str[0]=Nul;
                                    if((testc_val != 0) && SUCCEEDED(retc))
                                       for(ii = 0; (ii < KPST_TXTCD_CHARS_PER_VAL_TID) && SUCCEEDED(retc); ii++)
                                       {
                                          out_ch=testc_val;
                                          for(jj=ii; jj<KPST_TXTCD_CHARS_PER_VAL_TID-1; jj++) out_ch/=KPST_TXTCD_RADIX_TID;
                                          out_ch%=KPST_TXTCD_RADIX_TID;
                                          out_ch+=KPST_TXTCD_BASE_TID; 
                                          testc_str[ii]=(unsigned char)out_ch;
                                       }
                                    testc_str[KPST_TXTCD_CHARS_PER_VAL_TID]=Nul;
                                    if(SUCCEEDED(retc)) retc = CutTrailSpcs(testc_str);

                                    if(SUCCEEDED(retc)) if(SUCCEEDED(reta))
                                       if(strcmp(testc_str, testc)!=0)
                                       { 
                                          reta = KP_E_MSG_FORMAT;
#ifdef KPSTLSVR_TEST_CODE_NAME                  
                                          err_line = __LINE__;
#endif
                                       }
                                 }
                                 
// ------------- isvedam áraðo kontroliná simbolá                         
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &checkbox_cell_style, False);
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                                       if(SUCCEEDED(retc))
                                       {
// testc_str[0] = '8'; testc_str[2] = 'T';   
// PutStr(out_file, testc_str);                                             
// PutCharProc(out_file, '/', NULL, False);
// PutStr(out_file, testc);                                             
                                          if(SUCCEEDED(reta))
                                          {
//                                           if(date_val & 0x80000000)
//                                              retc=PutCharProc(out_file, C_MidRing, NULL, False);
//                                           else 
                                                retc=PutCharProc(out_file, C_NBSP, NULL, False);
                                          }
                                          else
                                          {
#ifdef KPSTLSVR_TEST_CODE_NAME                  
unsigned char str_buf[100];
                                             sprintf((char *)str_buf, "%d", err_line);                                             
                                             retc = PutStr(out_file, str_buf);

//                                           retc = PutStr(out_file, name_buf_out);
#else
                                             retc = PutCharProc(out_file, C_Excl, NULL, False); // '!'
#endif
// if(SUCCEEDED(retc)) retc=PutStr(out_file, testc_str);
                                          }
                                       }
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                        
#ifdef KPSTLSVR_TEST_CODE_NAME                  
// -------- iðvedam testo kodà
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
//                                  if(SUCCEEDED(retc)) retc=PutStr(out_file, (const unsigned char *)"[");
                                    if(SUCCEEDED(retc)) retc=PutStr(out_file, testc_str);
//                                  if(SUCCEEDED(retc)) retc=PutStr(out_file, (const unsigned char *)"][");
//                                  if(SUCCEEDED(retc)) retc=PutStr(out_file, testc);
//                                  if(SUCCEEDED(retc)) retc=PutStr(out_file, (const unsigned char *)"]");
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

// -------- iðvedam koduotà pavardæ, vardà      
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                    if(SUCCEEDED(retc)) retc=PutStr(out_file, name1_buf);
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
                                    if(SUCCEEDED(retc)) retc=PutStr(out_file, name2_buf);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
#endif                  
                        
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                              row_cnt++;
                        
                              while(*pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++;
                              while(*pntd==Cr) pntd++;
                              if(*pntd==Lf) pntd++;
                              pnts=pntd;
                           
                           } // while((*pnts) && SUCCEEDED(retc))
                        
                        } // if(field_cnt)

// laisvi duomenys su kintamuju vardais kepureje
                        else
                        {
                           pnts=rez_file_buf;

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
                           add_row=1;

                              while((*pnts) && SUCCEEDED(retc))
                              {
                                 if(strchr(lpszEols, *pnts)!=NULL)
                                 {
                                    while(*pnts==Cr) pnts++;
                                    if(*pnts==Lf) pnts++;

                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                                    row_cnt+=add_row;
                                    add_row=1;
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
                                 }
                                 else // if(*pnts)
                                 {
                                    pntd = (unsigned char *)pnts;
                                    while((*pntd!=C_Ht) && *pntd && (strchr(lpszEols, *pntd)==NULL)) pntd++; // '\t'
                                    sav_ch = *pntd;
                                    *pntd = Nul;
   
                                       if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                          if(SUCCEEDED(retc))
                                          {
                                             if(pnts[0]!=Nul)
                                             {
//                                              len=KP_MAX_FNAME_LEN+100-1;
                                                retc0=KptStrEncode(l_title, pnts, /* &len, */ KPST_DATA_FILE_CTBL);
                                                if(FAILED(retc0))
                                                   /* reta= */ OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L);
                                                if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                                             }
                                             else retc=PutChar(out_file, C_NBSP, False);
                                          }
                                          if(strlen(pnts)>KPST_EXERC_WRAP_THRESHOLD) add_row=1;
                                       if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                                    *pntd = sav_ch;
                                    if(*pntd==C_Ht)
                                    {
                                       pntd++;
                                       if((*pntd==Nul) || (strchr(lpszEols, *pntd)!=NULL))
                                       {
                                          if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                             if(SUCCEEDED(retc)) retc=PutChar(out_file, C_NBSP, False);
                                          if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                                       }
                                    }
                                    pnts = pntd;                                                               
                                 }

                              } // while((*pnts) && SUCCEEDED(retc))

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                           row_cnt++;
                        
                        } // else // if(field_cnt)
                     
                     } // if(SUCCEEDED(retc))
                     
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

// -------------------------
         while((row_cnt<KPSTLSVR_MIN_ROW_CNT-((field_cnt && testc[0])?1/*2*/:0)-1) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
            row_cnt++;
         }
         
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_RES_FILE);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, rez_fname);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

         if(field_cnt && testc[0]) // isvedam, tik jei testc<>""
         {
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Excl, NULL, False); // '!'
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                     if(SUCCEEDED(retc)) retc=PutChar(out_file, C_Spc, False);
                     if(SUCCEEDED(retc)) retc=PutChar(out_file, C_EnDash, False);
                     if(SUCCEEDED(retc))
                     {
//                      len=KP_MAX_FNAME_LEN+100-1;
                        retc=KptStrEncode(l_title, 
                           testc[0]?KPSTLSVR_MSG_BAD_RES:KPSTLSVR_MSG_BAD_RES_REC,
                           /* &len, */ TV_CPP_SOURCE_CTBL);
                        if(FAILED(retc))
                           retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

#if FALSE
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_MidRing, NULL, False);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                     if(SUCCEEDED(retc)) retc=PutChar(out_file, C_Spc, False);
                     if(SUCCEEDED(retc)) retc=PutChar(out_file, C_EnDash, False);
                     if(SUCCEEDED(retc))
                     {
                        len=KP_MAX_FNAME_LEN+100-1;
                        retc=KptStrEncode(l_title, KPSTLSVR_MSG_TEST_TIMEOUT, &len, TV_CPP_SOURCE_CTBL);
                        if(FAILED(retc))
                           retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
#endif
         }

      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);

// ------------------------------------
   if(SUCCEEDED(retc))
   { 
      retc=PutHtmTail(out_file);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }

// ------------------------------------
   KP_DELETE(out_file);

   KP_DELETEA(rez_file_buf);
      
   if(SUCCEEDED(retc)) *plpszPagePtrPtr = buf_ptr;
   else
   {
      KP_DELETEA(buf_ptr);
   }

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::FormatConsolePage(unsigned char **plpszPagePtrPtr)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char title[KP_MAX_FNAME_LEN+100];
KpChar i_title[KP_MAX_FNAME_LEN+100];
KpChar l_title[KP_MAX_FNAME_LEN+100];
KpChar i_heading[KP_MAX_FNAME_LEN+100];
long buf_len=0L;
unsigned char *buf_ptr=NULL;
TvXmlFile *out_file=NULL;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
KpTreeEntry *cur_line;
// int len;
XmlTagPars *tag_pars=NULL;
unsigned char *page_style=NULL;
const unsigned char *val_ptr=NULL;
int row_cnt=0;
int num_of_lics=0;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
   rez_fname[0]=Nul;

   if((plpszPagePtrPtr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {
      retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   { 
      retc=GetIniRezFName(rez_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   { 
      retc=GetIniProdName(title);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(title);
      retc=KptStrEncode(i_title, title, /* &len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) TvKpStrCpy(l_title, i_title);
   if(SUCCEEDED(retc)) TvKpStrLat(l_title);
   if(SUCCEEDED(retc))
   { 
      retc=KptStrDecode(title, l_title, /* len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) strcat(title, KPSTLSVR_MSG_MESSAGES);

   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(heading);
      retc=KptStrEncode(i_heading, KPSTLSVR_MSG_MESSAGES_, /* &len, */ TV_CPP_SOURCE_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }

// -------------------------
   if(SUCCEEDED(retc))
   {
      buf_len=KP_MAX_FILE_LIN_LEN*(1+KPST_NUM_OF_CONSOLE_LINES); // !!!! tiksliau pamatuot
      KP_NEWA(buf_ptr, unsigned char, buf_len);
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%x %x", buf_ptr, buf_len);
      KP_NEWO(out_file, TvXmlFile(str_buf, (const unsigned char *)"w", XL_FT_DataFile,
                        CreateNewUniBFile, plpszaHtmSpecCharTags,
                        TV_XL_NUM_LEN, (KpChar)HTM_TG_FirstTag, plpszaHtmlTags, True, 
                        XM_VERS_HTML401_TRANS, iaHtmNulCodeTables /* iaHtmCodeTables71 */, True, False));
   }


   if(SUCCEEDED(retc))
   { 
//    retc=out_file->SetEncoding(UC_No_Mode, TV_CTBL_ASCII, TV_CTBL_ASCII);
      retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_NO_CTBL);
//    retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_CPP_SOURCE_CTBL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
         
// ----------------------------------
   KP_NEWA(page_style, unsigned char, strlen(lpszPageStyle) + 1);
   if(SUCCEEDED(retc))
   {
      sprintf((char *)page_style, (const char *)lpszPageStyle, 100/m_iNumOfPages, 100/m_iNumOfPages);
      retc=PutHtmHat(out_file, title, NULL, NULL, KP_LNG_LIT, KPST_SRV_REFRESH_TIMEOUT, page_style, NULL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   KP_DELETEA(page_style);

// ----------------------------------
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &main_div_style, False);

// ----------------------------------
      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &tabs_table_style, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
   
// ---------------------------------- tabs
            if((strlen(rez_fname)>0) && SUCCEEDED(retc)) // !!!! TODO kaþkà rodyt ir licencijø serverio reþime
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &links_ref, False);
                     if(SUCCEEDED(retc))
                     {
                        retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_STATUS, TV_CPP_SOURCE_CTBL);
                        if(FAILED(retc))
                           retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if((num_of_lics>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &licences_ref, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_CLIENTS);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
            
            if((strlen(rez_fname)>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &results_ref, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_RESULTS);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_a_table_cell_style, False);
               if(SUCCEEDED(retc))
               {
//                len=KP_MAX_FNAME_LEN+100-1;
                  retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_MESSAGES, /* &len, */ TV_CPP_SOURCE_CTBL);
                  if(FAILED(retc))
                     retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
               }
               if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &friends_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_NETWORK);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &admins_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_ADMINS);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
//       row_cnt++;
   
// ---------------------------- heading
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_heading);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
//       row_cnt++;

         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &ip_div_style, False);

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &cons_table_style, False);

// ---------------------------- console
                     if(SUCCEEDED(retc))
                     {
                        cur_line=m_pConsole;
                        while(cur_line && SUCCEEDED(retc))
                        {
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &msgi_table_cell_style, False);

                                 if(SUCCEEDED(retc))
                                 {
//                                  len=KP_MAX_FNAME_LEN+100-1;
                                    retc0=KptStrEncode(l_title, (const unsigned char *)cur_line->GetValue(), /* &len, */ KPST_DATA_FILE_CTBL);
                                    if(FAILED(retc0))
                                       /* retc= */ KpErrorProc.OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L);
                                 }
                                 if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);

                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                           row_cnt++;
                        
                           if(SUCCEEDED(retc)) retc = cur_line->GetFirstChild(&cur_line);
                        }
                     }
                     
                     while((row_cnt<KPST_NUM_OF_CONSOLE_LINES) && SUCCEEDED(retc))
                     {
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &msgi_table_cell_style, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                        row_cnt++;
                     }

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

// papildoma eilute - terminalo eilutes zemesnes
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &msgi_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                  if(SUCCEEDED(retc))
                  {
//                   len=KP_MAX_FNAME_LEN+100-1;
                     retc=KptStrEncode(l_title, KPSTLSVR_MSG_ERROR_HELP, /* &len, */ TV_CPP_SOURCE_CTBL);
                     if(FAILED(retc))
                        retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);

// ------------------------------------
   if(SUCCEEDED(retc))
   {
      retc=PutHtmTail(out_file);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   
// ------------------------------------
   KP_DELETE(out_file);

   if(SUCCEEDED(retc)) *plpszPagePtrPtr = buf_ptr;
   else
   {
      KP_DELETEA(buf_ptr);
   }

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::FormatIpListPage(KpStLisSvrEnvirs iCurEnv, unsigned char **plpszPagePtrPtr)
{
HRESULT retc=S_OK;
unsigned char title[KP_MAX_FNAME_LEN+100];
KpChar i_title[KP_MAX_FNAME_LEN+100];
KpChar l_title[KP_MAX_FNAME_LEN+100];
KpChar i_heading[KP_MAX_FNAME_LEN+100];
long buf_len=0L;
unsigned char *buf_ptr=NULL;
TvXmlFile *out_file=NULL;
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
KpChar i_str_buf[KP_MAX_FNAME_LEN+1];
// int len;
XmlTagPars *tag_pars=NULL;
int ii;
KpTreeEntry **ip_list_ptr=NULL; // ip saraso adreso adresas
KpTreeEntry *cur_ip_entry=NULL; // rodykle po *ip_list_ptr 
KpTreeEntry **saved_var_list_ptr=NULL; // html formos kintamuju reiksmiu saraso adreso adresas
unsigned char *page_style=NULL;
KpTreeEntry *var_rec_entry_ptr=NULL;  // rodykle po *saved_var_list_ptr
PostVarRec *var_rec_ptr=NULL;          // rodykle i kintamojo aprasa irase var_rec_entry_ptr
const unsigned char *val_ptr=NULL;
unsigned char msg_buf[KP_MSG_LEN+1];
KpChar i_msg_buf[KP_MSG_LEN+1];
int row_cnt=0;
int num_of_lics=0;
KpstSesData cur_link_record;
IN_ADDR cur_ip_addr;
struct tm *tm_time=NULL;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
   rez_fname[0]=Nul;
KpChar lic_bus_txt[KP_MAX_FNAME_LEN+1];
   lic_bus_txt[0] = C_Nul;
int ll;

   if((plpszPagePtrPtr==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) switch(iCurEnv)
   {
   case KPSTLSVR_FRIENDS:
      ip_list_ptr=&m_pFriendList;
      saved_var_list_ptr=&m_pFriendVarList;
      break;
   case KPSTLSVR_ADMINS:
      ip_list_ptr=&m_pAdminList;
      saved_var_list_ptr=&m_pAdminVarList;
      break;
   case KPSTLSVR_LINKS:
      ip_list_ptr=&m_pLinkList;
      saved_var_list_ptr=NULL;

      if(SUCCEEDED(retc))
      {
//       len=KP_MAX_FNAME_LEN;
         retc=KptStrEncode(lic_bus_txt, KPSTLSVR_MSG_SESSION_STATUS, /* &len, */ TV_CPP_SOURCE_CTBL);
         if(FAILED(retc))
            retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
      }
      break;
   default:   
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      break;
   }      

   if(((ip_list_ptr==NULL) || ((saved_var_list_ptr==NULL) && (iCurEnv != KPSTLSVR_LINKS))) && SUCCEEDED(retc))
   {
      retc=KP_E_SYSTEM_ERROR;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   { 
      retc=GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniRezFName(rez_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=GetIniProdName(title);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(title);
      retc=KptStrEncode(i_title, title, /* &len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) TvKpStrCpy(l_title, i_title);
   if(SUCCEEDED(retc)) TvKpStrLat(l_title);
   if(SUCCEEDED(retc))
   { 
      retc=KptStrDecode(title, l_title, /* len, */ TV_MAIN_HTML_CTBL);
      if(FAILED(retc))
         retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
   }
   if(SUCCEEDED(retc)) switch(iCurEnv)
   {
   case KPSTLSVR_FRIENDS:
      strcat(title, KPSTLSVR_MSG_NETWORKS);
      break;
   case KPSTLSVR_ADMINS:
      strcat(title, KPSTLSVR_MSG_ADMINS);
      break;
   case KPSTLSVR_LINKS:
      strcat(title, KPSTLSVR_MSG_STATUS_);
      break;
   }      

   if(SUCCEEDED(retc))
   {
//    len=KP_MAX_FNAME_LEN+100-1; // strlen(heading);
      switch(iCurEnv)
      {
      case KPSTLSVR_FRIENDS:
//       if(num_of_lics) retc=KptStrEncode(i_heading, KPSTLSVR_MSG_IP_LIST_REGISTER, &len, TV_CPP_SOURCE_CTBL);
//       else if(strlen(rez_fname)>0) retc=KptStrEncode(i_heading, KPSTLSVR_MSG_IP_LIST_SEND, &len, TV_CPP_SOURCE_CTBL);
//       else retc=KP_E_SYSTEM_ERROR;
         retc = KptStrEncode(i_heading, KPSTLSVR_MSG_IP_LIST, /* &len, */ TV_CPP_SOURCE_CTBL);
         if(SUCCEEDED(retc)) ll = TvKpStrLen(i_heading);
         if((rez_fname[0]) && SUCCEEDED(retc))
            retc = KptStrEncode(i_heading + ll, KPSTLSVR_MSG_IP_LIST_SEND, /* &len, */ TV_CPP_SOURCE_CTBL);
         if((num_of_lics > 0) && SUCCEEDED(retc)) 
            retc = KptStrEncode(i_heading + ll, KPSTLSVR_MSG_IP_LIST_REGISTER, /* &len, */ TV_CPP_SOURCE_CTBL);
         if(FAILED(retc))
            retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         break;
      case KPSTLSVR_ADMINS:
         retc=KptStrEncode(i_heading, KPSTLSVR_MSG_IP_LIST_ADMIN, /* &len, */ TV_CPP_SOURCE_CTBL);
         if(FAILED(retc))
            retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         break;
      case KPSTLSVR_LINKS:
         retc=KptStrEncode(i_heading, KPSTLSVR_MSG_CONNECTIONS_LIST, /* &len, */ TV_CPP_SOURCE_CTBL);
         if(FAILED(retc))
            retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         break;
      }      
   }

   if(SUCCEEDED(retc))
   {
int ii = 0;
      buf_len=KP_MAX_FILE_LIN_LEN;
      retc = (*ip_list_ptr)->CountEntries(&ii, 0, (*ip_list_ptr));
      if(SUCCEEDED(retc))
      {
         if(*ip_list_ptr) buf_len += ii*KP_MAX_FILE_LIN_LEN; 
         KP_NEWA(buf_ptr, unsigned char, buf_len);
      }
   }

   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, "%x %x", buf_ptr, buf_len);
      KP_NEWO(out_file, TvXmlFile(str_buf, (const unsigned char *)"w", XL_FT_DataFile,
                        CreateNewUniBFile, plpszaHtmSpecCharTags,
                        TV_XL_NUM_LEN, (KpChar)HTM_TG_FirstTag, plpszaHtmlTags, True,
                        XM_VERS_HTML401_TRANS, iaHtmNulCodeTables /* iaHtmCodeTables71 */, True, False));
   }

   if(SUCCEEDED(retc))
   {
//    retc=out_file->SetEncoding(UC_No_Mode, TV_CTBL_ASCII, TV_CTBL_ASCII);
      retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_NO_CTBL);
//    retc=out_file->SetEncoding(UC_UTF_8, TV_NO_CTBL, TV_CPP_SOURCE_CTBL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
         
// ----------------------------------
   KP_NEWA(page_style, unsigned char, strlen(lpszPageStyle) + 1);
   if(SUCCEEDED(retc))
   {
      page_style[0] = Nul;
      
      switch(iCurEnv)
      {
      case KPSTLSVR_FRIENDS:
      case KPSTLSVR_ADMINS:
      case KPSTLSVR_LINKS:
         sprintf((char *)page_style, (const char *)lpszPageStyle, 100/m_iNumOfPages, 100/m_iNumOfPages);
         break;
      }      

      switch(iCurEnv)
      {
      case KPSTLSVR_FRIENDS:
      case KPSTLSVR_ADMINS:
// KPSTLSVR_FRIENDS ir KPSTLSVR_ADMINS: 
//    Operai refreshinimo kaip ir reiketu - ji neatsimena, kad jau gavo atnaujinta puslapi po POST'o,
//    bet tada refreshinimas istrina pradeta rinkti lauka
         retc=PutHtmHat(out_file, title, NULL, NULL, KP_LNG_LIT, 
            0 /* KPST_SRV_REFRESH_TIMEOUT */, page_style, lpszJavaScript);
         break;
      case KPSTLSVR_LINKS:
         retc=PutHtmHat(out_file, title, NULL, NULL, KP_LNG_LIT, 
            KPST_SRV_REFRESH_TIMEOUT, page_style, lpszJavaScriptLinks);
         break;
      }      

      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   KP_DELETEA(page_style);


// ----------------------------------
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &main_div_style, False);

// ----------------------------------
      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, &tabs_table_style, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
   
// ---------------------------------- tabs
            if((strlen(rez_fname)>0) && SUCCEEDED(retc)) // !!!! TODO kaþkà rodyt ir licencijø serverio reþime
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, ((iCurEnv==KPSTLSVR_LINKS)?(&tab_a_table_cell_style):(&tab_n_table_cell_style)), False);
                  if((iCurEnv!=KPSTLSVR_LINKS) && SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &links_ref, False);
                     if(SUCCEEDED(retc))
                     {
                        retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_STATUS, TV_CPP_SOURCE_CTBL);
                        if(FAILED(retc))
                           retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                     }
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
                  if((iCurEnv!=KPSTLSVR_LINKS) && SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
            
            if((num_of_lics>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &licences_ref, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_CLIENTS);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
            
            if((strlen(rez_fname)>0) && SUCCEEDED(retc))
            {
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &results_ref, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_RESULTS);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            }
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &tab_n_table_cell_style, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &console_ref, False);
                  if(SUCCEEDED(retc))
                  {
//                   len=KP_MAX_FNAME_LEN+100-1;
                     retc=KptStrEncode(l_title, KPSTLSVR_MSG_TAB_MESSAGES, /* &len, */ TV_CPP_SOURCE_CTBL);
                     if(FAILED(retc))
                        retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, l_title);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, ((iCurEnv==KPSTLSVR_FRIENDS)?(&tab_a_table_cell_style):(&tab_n_table_cell_style)), False);
               if((iCurEnv!=KPSTLSVR_FRIENDS) && SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &friends_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_NETWORK);
               if((iCurEnv!=KPSTLSVR_FRIENDS) && SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, ((iCurEnv==KPSTLSVR_ADMINS)?(&tab_a_table_cell_style):(&tab_n_table_cell_style)), False);
               if((iCurEnv!=KPSTLSVR_ADMINS) && SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A, &admins_ref, False);
                  if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_TAB_ADMINS);
               if((iCurEnv!=KPSTLSVR_ADMINS) && SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_A_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
   
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         row_cnt++;
   
// ---------------------------- heading
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_title);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_heading);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         row_cnt++;

// ---------------------------- adresu lentele
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_centered_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &ip_div_style, False);

// ------------------------------------
// <form action='index.htm' name='IP' method='post' enctype='multipart/form-data'>
// <form action="friends.htm" name="IP_adresai" method="post" enctype="multipart/form-data">
                  if(SUCCEEDED(retc)) switch(iCurEnv)
                  {
                  case KPSTLSVR_FRIENDS:
                     retc=PutCharProc(out_file, (KpChar)HTM_TG_FORM, &friends_form_pars, False);
                     break;
                  case KPSTLSVR_ADMINS:   
                     retc=PutCharProc(out_file, (KpChar)HTM_TG_FORM, &admins_form_pars, False);
                     break;
                  case KPSTLSVR_LINKS:   
                     retc=PutCharProc(out_file, (KpChar)HTM_TG_FORM, &links_form_pars, False);
                     break;
                  }

// <input name="ButNum" value="" type="hidden"/>
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, &ButNum_control_description, False);

                  if((*ip_list_ptr) || (iCurEnv != KPSTLSVR_LINKS))
                  {
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE, 
                        (iCurEnv == KPSTLSVR_LINKS)?(&cons_table_style):(&ip_table_style), False);

// -----------------------------------
                        if(SUCCEEDED(retc)) cur_ip_entry=(*ip_list_ptr);
                        ii=1;
// IP
                        while(cur_ip_entry && SUCCEEDED(retc))
                        {
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
   
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                 if(SUCCEEDED(retc))
                                 {
                                    if(iCurEnv == KPSTLSVR_LINKS)
                                    {
                                       memcpy(&cur_link_record, cur_ip_entry->GetValue(), sizeof(cur_link_record));
                                       memcpy(&cur_ip_addr, &(cur_link_record.m_lIpAddr), sizeof(cur_ip_addr));
                                    }
                                    else memcpy(&cur_ip_addr, cur_ip_entry->GetValue(), sizeof(cur_ip_addr));
                                 }
                                 if(SUCCEEDED(retc))
                                 {
                                    pnts=(const unsigned char *)inet_ntoa(cur_ip_addr);
                                    if(pnts==NULL)
                                    {
                                       retc=E_INVALIDARG;
                                       OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
                                    }
                                 }
                                 if(SUCCEEDED(retc)) retc=PutStr(out_file, pnts);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                              if((iCurEnv == KPSTLSVR_LINKS) && SUCCEEDED(retc))
                              {
// laikas
                                 if(SUCCEEDED(retc))
                                 {
                                    tm_time=localtime(&cur_link_record.m_lTimeStamp);
                                    if((tm_time==NULL) && SUCCEEDED(retc))
                                    {
                                       retc=KP_E_SYSTEM_ERROR;
                                       OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                                    }
                                 }
                                 if(SUCCEEDED(retc))
                                 {
                                    sprintf((char *)str_buf, "%04d.%02d.%02d %02d:%02d:%02d",
                                          tm_time->tm_year+1900, tm_time->tm_mon + 1, tm_time->tm_mday,
                                          tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec); 
                                 }
                              
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &ip_table_cell_style, False);
                                    if(SUCCEEDED(retc)) retc=PutStr(out_file, str_buf);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

// vardas-pavarde
                                 
                                 if(SUCCEEDED(retc)) retc = GetNameFromResults(str_buf, KP_MAX_FNAME_LEN, cur_link_record.m_lpszData); 
                                 
                                 if(SUCCEEDED(retc))
                                 {
//                                  len=KP_MAX_FNAME_LEN;
                                    retc=KptStrEncode(i_str_buf, str_buf, /* &len, */ KPST_DATA_FILE_CTBL);
                                    if(FAILED(retc))
                                       KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
                                 }

                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, 
                                       &name_table_cell_style /* &rez_table_cell_style */, False);
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
                                    if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
                              
                              } // if((iCurEnv == KPSTLSVR_LINKS) && SUCCEEDED(retc))


// ----------------
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &checkbox_cell_style, False);
                        
                              if(SUCCEEDED(retc))
                              {
                                 if(iCurEnv == KPSTLSVR_LINKS)
                                 {
// sesijos busena
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                                       switch(cur_link_record.m_iSesStatus)
                                       {
                                       case KPST_SES_OPEN:
                                          retc=PutCharProc(out_file, C_Lpoint, NULL, False); // C_Point // '.'
                                          break;
                                       case KPST_SES_ACTIVE:
                                          retc=PutCharProc(out_file, C_MidRing, NULL, False);
                                          break;
                                       case KPST_SES_DONE:
                                          retc=PutCharProc(out_file, C_Bpoint, NULL, False);
                                          break;
                                       case KPST_SES_CLOSED:
                                          retc=PutCharProc(out_file, C_Excl /* '!' C_Bpoint C_NBSP */, NULL, False);
                                          break;
                                       case KPST_STAT_UNKNOWN:
                                       default:
                                          retc=PutCharProc(out_file, C_Quest, NULL, False); // '?'
                                          break;
                                       }
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                                 
                                 } // if(iCurEnv == KPSTLSVR_LINKS)
                                 else
                                 {
// <input type="checkbox" name="check[1]" />
                                    if(SUCCEEDED(retc)) 
                                    {
                                       KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"type", (const unsigned char *)"checkbox"));
                                    }
                                    if(SUCCEEDED(retc)) sprintf((char *)str_buf, "check[%d]", ii++);
                                    if(SUCCEEDED(retc))
                                    {
                                       retc=tag_pars->AddTextPar((const unsigned char *)"name", str_buf);
                                       if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                    }
                                    if((saved_var_list_ptr == NULL) && SUCCEEDED(retc))
                                    {
                                       retc=KP_E_SYSTEM_ERROR;
                                       OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                                    }
                                    if(SUCCEEDED(retc)) if(*saved_var_list_ptr)
                                    {
                                       retc=(*saved_var_list_ptr)->SearchTreeEntry(str_buf, TvStrCmpStrict_, &var_rec_entry_ptr, NULL);
                                       if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                    
                                       if(var_rec_entry_ptr && SUCCEEDED(retc))
                                       {
                                          var_rec_ptr = (PostVarRec *)var_rec_entry_ptr->GetValue();
                                          KP_ASSERTE(var_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, False);
                                          KP_ASSERTE(var_rec_entry_ptr->GetValSize() >= sizeof(PostVarRec), KP_E_SYSTEM_ERROR, null, False);
// !!! kazko nesuveikia (pazymi kuri nors, spaudi "Prideti" (ne "Ismesti") - pazymejimai dingsta
                                          if(SUCCEEDED(retc))
                                          {
                                             retc = tag_pars->AddTextPar((const unsigned char *)"value", var_rec_ptr->m_lpszVarData);
                                             if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                          }
                                       }
                                    }
                                    
                                    if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, tag_pars, False);

                                    KP_DELETE(tag_pars);

                                 } // else // if(iCurEnv == KPSTLSVR_LINKS)
                              
                              } // if(SUCCEEDED(retc))
                              
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                           row_cnt++;

                           if(SUCCEEDED(retc)) retc = cur_ip_entry->GetFirstChild(&cur_ip_entry);
                        }
   
// -------------------------
                        if((*ip_list_ptr) && (iCurEnv != KPSTLSVR_LINKS) && SUCCEEDED(retc))
                        {
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);

                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &form_cell_style, False);
// <input value="Iðmesti" type="button" class = "button" OnClick="submitas(1)"/>
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, &delete_button_description, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

// <td><input type="checkbox" name="check" onclick="checkUncheckAll(this);"/> </td>
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, NULL /* &form_cell_style */, False);
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, &check_all_chbox_description, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                           row_cnt++;
                        }
                        
// -------------------------
                        if((iCurEnv != KPSTLSVR_LINKS) && SUCCEEDED(retc))
                        {
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);

                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &form_cell_style, False);

// <input type='text' name='IP' value=''>
                                 if(SUCCEEDED(retc)) 
                                 {
                                    KP_NEW(tag_pars, XmlTagPars((const unsigned char *)"name", (const unsigned char *)"IP"));
                                 }
                              
                                 val_ptr=(const unsigned char *)"";
                                 if((saved_var_list_ptr == NULL) && SUCCEEDED(retc))
                                 {
                                    retc=KP_E_SYSTEM_ERROR;
                                    OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                                 }
                                 if(SUCCEEDED(retc)) if(*saved_var_list_ptr)
                                 {
                                    retc=(*saved_var_list_ptr)->SearchTreeEntry("IP", TvStrCmpStrict_, &var_rec_entry_ptr, NULL);
                                    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                    
                                    if(var_rec_entry_ptr && SUCCEEDED(retc))
                                    {
                                       var_rec_ptr = (PostVarRec *)var_rec_entry_ptr->GetValue();
                                       KP_ASSERTE(var_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, False);
                                       KP_ASSERTE(var_rec_entry_ptr->GetValSize() >= sizeof(PostVarRec), KP_E_SYSTEM_ERROR, null, False);
                                       if(SUCCEEDED(retc)) val_ptr = var_rec_ptr->m_lpszVarData;
                                    }
                                 }
                                 if(SUCCEEDED(retc))
                                 {
                                    retc=tag_pars->AddTextPar((const unsigned char *)"value", val_ptr);
                                    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                 }   
                                 if(SUCCEEDED(retc))
                                 {
                                    retc=tag_pars->AddTextPar((const unsigned char *)"type", (const unsigned char *)"text");
                                    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                 }
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, tag_pars, False);

                                 KP_DELETE(tag_pars);

// <input type='submit' value='Add'>
// <input value="Pridëti" type="button" class = "button" OnClick="submitas(2)"/>
                                 if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, &add_button_description, False);

                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, &checkbox_cell_style, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);

                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
                           row_cnt++;
                        
                        } // if((iCurEnv != KPSTLSVR_LINKS) && SUCCEEDED(retc))
                        
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
                  
                  } // if((*ip_list_ptr) || (iCurEnv != KPSTLSVR_LINKS))
                  
// <input value="Iðsaugoti" type="button" class = "button" OnClick="submitas(3)"/>
                  if((iCurEnv == KPSTLSVR_LINKS) && SUCCEEDED(retc))
                  {
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                     row_cnt++;

                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, &save_button_description, False);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_INPUT, &clean_button_description, False);
                     row_cnt++;
                  }

                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_FORM_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         row_cnt++;

// ------------------------------------ klaidos pranesimas
         if((FAILED(m_lhOpenResult) || m_lLastWindowsError) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &error_div_style, False);
                     if(SUCCEEDED(retc)) retc=PutStr(out_file, KPSTLSVR_MSG_ERROR);
                     if(FAILED(m_lhOpenResult) && SUCCEEDED(retc))
                     {
                        retc=KpErrorProc.FormatErrorMessage(m_lhOpenResult, msg_buf);
                        if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                  
                        if(SUCCEEDED(retc)) retc=PutStr(out_file, msg_buf);
                        if(m_lLastWindowsError && SUCCEEDED(retc))               
                           retc=PutCharProc(out_file, (KpChar)HTM_TG_BR, NULL, False);
                     }
                     if(m_lLastWindowsError && SUCCEEDED(retc))
                     {               
                        retc=KpErrorProc.FormatErrorMessageSystem(m_lLastWindowsError, msg_buf, False);               
                        if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                  
                        if(SUCCEEDED(retc)) retc=PutStr(out_file, msg_buf);
                     }
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
            row_cnt++;
         
            m_lhOpenResult=S_OK;
            m_lLastWindowsError=0L;
         }
      
// -------------------------
         if((iCurEnv == KPSTLSVR_LINKS) && SUCCEEDED(retc)) row_cnt+=6;
         row_cnt++;

         while((row_cnt<KPSTLSVR_MIN_ROW_CNT) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, NULL, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_NBSP, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
            row_cnt++;
         }
         
// ------------------------------------ hints
         if((iCurEnv == KPSTLSVR_LINKS) && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                     if(SUCCEEDED(retc)) retc=PutKpStr(out_file, lic_bus_txt);
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Colon, NULL, False); // ':'
//                if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
//             if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
//          if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
//          if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
//             if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
//                if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
         
                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_UL, &footnote_list_style, False);
         
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Lpoint, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                           if(SUCCEEDED(retc))
                           {
//                            len=KP_MAX_FNAME_LEN;
                              retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_SESSION_STARTED, /* &len, */ TV_CPP_SOURCE_CTBL);
                              if(FAILED(retc))
                                 retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                           }
                           if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);
         
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_MidRing, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                           if(SUCCEEDED(retc))
                           {
//                            len=KP_MAX_FNAME_LEN;
                              retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_RESULTS_BEING_SENT, /* &len, */ TV_CPP_SOURCE_CTBL);
                              if(FAILED(retc))
                                 retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                           }
                           if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);
         
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Bpoint, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                           if(SUCCEEDED(retc))
                           {
//                            len=KP_MAX_FNAME_LEN;
                              retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_FINAL_RESULTS_SENT, /* &len, */ TV_CPP_SOURCE_CTBL);
                              if(FAILED(retc))
                                 retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                           }
                           if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);

                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG, NULL, False);
                              if(SUCCEEDED(retc)) retc=PutCharProc(out_file, C_Excl /* '!' C_NBSP */, NULL, False);
                           if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_BIG_e, NULL, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_Spc, False);
                           if(SUCCEEDED(retc)) retc=out_file->PutChar(C_EnDash, False);
                           if(SUCCEEDED(retc))
                           {
//                            len=KP_MAX_FNAME_LEN;
                              retc=KptStrEncode(i_str_buf, KPSTLSVR_MSG_SESSION_ABORTED, /* &len, */ TV_CPP_SOURCE_CTBL);
                              if(FAILED(retc))
                                 retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                           }
                           if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_str_buf);
                        if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_LI_e, NULL, False);

                     if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_UL_e, NULL, False);
         
                  if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);

         } // if((iCurEnv == KPSTLSVR_LINKS) && SUCCEEDED(retc))
         
         
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD, body_table_cell_left_style_ptr, False);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV, &footnote_div_style, False);
                  if(SUCCEEDED(retc))
                  {
//                   len=KP_MSG_LEN;
                     retc=KptStrEncode(i_msg_buf, 
                        (iCurEnv == KPSTLSVR_LINKS)?KPSTLSVR_MSG_ABORT_PROMPT:KPSTLSVR_MSG_IP_HINT, /* &len, */ TV_CPP_SOURCE_CTBL);
                     if(FAILED(retc))
                        retc=OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
                  }
                  if(SUCCEEDED(retc)) retc=PutKpStr(out_file, i_msg_buf);
               if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);
            if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TD_e, NULL, False);
         if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TR_e, NULL, False);
         
// --------------------------
      if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_TABLE_e, NULL, False);
   if(SUCCEEDED(retc)) retc=PutCharProc(out_file, (KpChar)HTM_TG_DIV_e, NULL, False);

   if(SUCCEEDED(retc))
   {
      retc=PutHtmTail(out_file);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   
// ------------------------------------
   KP_DELETE(out_file);
   
   if(SUCCEEDED(retc)) *plpszPagePtrPtr = buf_ptr;
   else
   {
      KP_DELETEA(buf_ptr);
   }

return(retc);
}


//----------------------------------- broadcast listening procedure
DWORD WINAPI LicSockBroadcastListenProc(LPVOID /* lpParameter */)
{
HRESULT retc=S_OK;
KpStLicSvr *stap_ptr=NULL;
static unsigned char msg_buf[KP_MAX_FNAME_LEN + 1];
long ll = 0;
KpSocket *sock_ptr = NULL;
static unsigned char http_adr[KP_MAX_FNAME_LEN + 1];

   if(SUCCEEDED(retc))
   { 
      stap_ptr = &theApp;
      KP_ASSERT(stap_ptr, KP_E_SYSTEM_ERROR, null, True);
   }

   if(SUCCEEDED(retc))
   {
      if(stap_ptr->m_pListSocket == NULL) 
      {
         retc = KP_E_SYSTEM_ERROR;
         stap_ptr->OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc)) do
   {
      ll = KP_MAX_FNAME_LEN;            
      if(SUCCEEDED(retc)) retc = stap_ptr->m_pListSocket->RecvFrom(msg_buf, &ll, False);

      if(SUCCEEDED(retc))
      {
         if(ll > KP_MAX_FNAME_LEN) ll = KP_MAX_FNAME_LEN;
         msg_buf[ll] = Nul;

         if(strcmp(msg_buf, KPSTLSVR_REQUEST) == 0)
         {
            stap_ptr->AddIPConsMsg(KPSTLSVR_MSG_SERVER_ASKED, True, stap_ptr->m_pListSocket);

// gavom klausimà apie IP serverio adresà – siunèiam atsakymà
// kuriam naujà socketà – jeigu siunèiam atgal á tà patá, tada ant tikrø tinkliniø sujungimø (nelokaliø) 
//    pradeda ciklintis – RecvFrom pradeda gauti tà patá anksèiau jau priimtà praneðimà
            KP_NEWO(sock_ptr, KpSocket(SOCK_DGRAM));
            
            Sleep(500); // palaukiam, kad klientas spëtø persijungt á klausymà
            
            if(SUCCEEDED(retc))
            {
// keièiam portà, nes Vistoj tuo paèiu adresu/portu leidþia tik vienà sujungimà
//             sprintf((char *)http_adr, "http://%s:%d/", stap_ptr->m_pListSocket->m_PackedUrl.lpszServerName, stap_ptr->m_pListSocket->m_PackedUrl.m_iPort);
               sprintf((char *)http_adr, "http://%s:%d/", stap_ptr->m_pListSocket->m_PackedUrl.lpszServerName, stap_ptr->m_pListSocket->m_PackedUrl.m_iPort + KP_UDP_PORT_OFFSET);
               retc = sock_ptr->Resolve(http_adr, True); // False);
// stap_ptr->AddIPConsMsg(http_adr, True, sock_ptr);
            }
         
//          if(SUCCEEDED(retc)) retc = stap_ptr->m_pListSocket->SendTo(KPSTLSVR_ANSWER_OK, strlen(KPSTLSVR_ANSWER_OK), False);
            if(SUCCEEDED(retc)) retc = sock_ptr->SendTo(KPSTLSVR_ANSWER_OK, strlen(KPSTLSVR_ANSWER_OK), True); // False);
            
            KP_DELETE(sock_ptr);
         }

      }
   
      retc = S_OK;
            
   } while(True); // SUCCEEDED(retc));

return(RET_CODE_MAIN(retc));
}


//----------------------------------- start broadcast listening thread
HRESULT KpStLicSvr::StartBroadcastThread(HINSTANCE /* hInstance */)
{
HRESULT retc = S_OK;
HANDLE hh;
int prod_ver = 0;
int port = 0;

   KP_ASSERT(m_lBroadcastThreadId == 0L, retc = KP_E_DOUBLE_CALL, null, False);
   KP_ASSERT(m_pListSocket == NULL, retc = KP_E_DOUBLE_CALL, null, False);
   
   if(SUCCEEDED(retc))
   { 
      retc = GetIniProdVer(&prod_ver);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc)) 
   {
      port = prod_ver;
      if(port < KP_MIN_USER_PORT) port += KP_MIN_USER_PORT;

      port += KP_UDP_PORT_OFFSET;
   }
   
   if(SUCCEEDED(retc))
   {
      KP_NEW(m_pListSocket, KpSocket(SOCK_DGRAM));
   }
      
   if(SUCCEEDED(retc))
   {
      retc = m_pListSocket->Bind(port, INADDR_ANY); // ADDR_ANY);
      if(retc == KP_E_NO_CONN)
      {
         OutputErrorMessage(retc, WSAGetLastError(), False, __FILE__, __LINE__, 0L);
      }
      else if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }         

   if(SUCCEEDED(retc))
   {
      hh = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         LicSockBroadcastListenProc,   // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         NULL,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         &m_lBroadcastThreadId  // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      if(hh == NULL)
      {
         retc = KP_E_SYSTEM_ERROR;
         OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
      
      if(FAILED(retc)) m_lBroadcastThreadId = 0L;
   
   }

return(retc);
}


//----------------------------------- start HTTP listening thread
HRESULT KpStLicSvr::CreateLicSockThread(HINSTANCE /* hInstance */)
{
HRESULT retc=S_OK;
HANDLE hh;
int prod_ver=0;
int port=0;
// unsigned char rez_fname[KP_MAX_FNAME_LEN+1];

   if(((m_lLicListThreadId!=0L) || (m_pLicListSocket!=NULL)) && SUCCEEDED(retc))
   {
      retc=KP_E_DOUBLE_CALL;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   { 
      retc=GetIniProdVer(&prod_ver);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc)) 
   {
      port=prod_ver;
      if(port<KP_MIN_USER_PORT) port+=KP_MIN_USER_PORT;
   }

// ---- !!!! mest lauk
// if(SUCCEEDED(retc))
// {
//    retc=GetIniRezFName(rez_fname);
//    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
// }
// if(SUCCEEDED(retc)) if(strlen(rez_fname)>0) port=KPSTAP_SPORT;
// ----

   KP_NEW(m_pLicListSocket, KpSocket());
         
   if(SUCCEEDED(retc))
   {
      retc = m_pLicListSocket->Bind(port, INADDR_ANY); // ADDR_ANY);
      if(retc == KP_E_NO_CONN)
      {
//       KpMsgOut(KPSTLSVR_MSG_PORT_BUSSY, IDI_ERROR, KP_MB_BAIGTI);
         OutputErrorMessage(retc, WSAGetLastError(), False, __FILE__, __LINE__, 0L);
      }
      else if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }         
   if(SUCCEEDED(retc))
   {
      retc = m_pLicListSocket->Listen();
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
            
   if(SUCCEEDED(retc))
   {
      hh = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         LicSockListenProc,   // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         NULL,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         &m_lLicListThreadId  // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      if(hh == NULL)
      {
         retc = KP_E_SYSTEM_ERROR;
         OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }
         
      if(FAILED(retc)) m_lLicListThreadId = 0L;
      
   } // if(SUCCEEDED(retc))
   
return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::ProcessVars(KpStLisSvrEnvirs iCurEnv, KpTreeEntry *p_VarList)
{
HRESULT retc=S_OK;
KpTreeEntry **ip_list_ptr=NULL; // ip saraso adreso adresas
KpTreeEntry **saved_var_list_ptr=NULL; // html formos kintamuju reiksmiu saraso adreso adresas

KpTreeEntry *var_list=p_VarList;   // nuoroda i gauta kintamuju sarasa,
                                    // keiciasi, ismetinejant checkboxu irasus 
                                    // naudojama ir kaip indikatorius, ar reikia isvalyti pries iseinant
                                    // NULL - isvalyti jau nereikia, issaugota i *saved_var_list_ptr 

KpTreeEntry *var_rec_entry_ptr=NULL;  // rodykle po var_list
KpTreeEntry *var_rec_father=NULL;     // var_rec_entry_ptr tevas ismetimui
PostVarRec *var_rec_ptr=NULL;          // rodykle i pati kintamojo aprasa irase var_rec_entry_ptr

KpTreeEntry *cur_ip_entry=NULL;    // rodykle po *ip_list_ptr
KpTreeEntry *ip_father=NULL;       // cur_ip_entry tevas ismetimui
IN_ADDR ip;
int but_num;
unsigned char str_buf[100];
int ii;
int num_of_entries;
int cur_entry_no;

   if((p_VarList==NULL) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc)) var_list=p_VarList;

   if(SUCCEEDED(retc)) switch(iCurEnv)
   {
   case KPSTLSVR_FRIENDS:
      ip_list_ptr=&m_pFriendList;
      saved_var_list_ptr=&m_pFriendVarList;
      break;
   case KPSTLSVR_ADMINS:
      ip_list_ptr=&m_pAdminList;
      saved_var_list_ptr=&m_pAdminVarList;
      break;
   case KPSTLSVR_LINKS:
      ip_list_ptr=&m_pLinkList;
      saved_var_list_ptr=NULL;
      break;
   default:   
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      break;
   }      
   if(
      (
         (ip_list_ptr==NULL) ||
         (
            (saved_var_list_ptr==NULL) &&
            (iCurEnv != KPSTLSVR_LINKS)
         )
      ) &&
      SUCCEEDED(retc)
     )
   {
      retc=KP_E_SYSTEM_ERROR;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

// ButNum
   if(SUCCEEDED(retc))
   {
      retc=var_list->SearchTreeEntry("ButNum", TvStrCmpStrict_, &var_rec_entry_ptr, NULL);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
   if((var_rec_entry_ptr==NULL) && SUCCEEDED(retc))
   {
      retc=KP_E_MSG_FORMAT;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   if(SUCCEEDED(retc)) var_rec_ptr = (PostVarRec *)var_rec_entry_ptr->GetValue();
   KP_ASSERTE(var_rec_ptr != NULL, KP_E_MSG_FORMAT, null, False);
   KP_ASSERTE(var_rec_entry_ptr->GetValSize() >= sizeof(PostVarRec), KP_E_SYSTEM_ERROR, null, False);
   if(SUCCEEDED(retc))
   {
      but_num=0;
      if(sscanf((const char *)var_rec_ptr->m_lpszVarData, "%d", &but_num)<1) 
         but_num=2; // Enter adreso lauke - tas pats, kaip "Prideti"
      
      switch(but_num)
      {
      case 1:  // "Iðmesti"
         switch(iCurEnv)
         {
         case KPSTLSVR_FRIENDS:
         case KPSTLSVR_ADMINS:
            if(*ip_list_ptr)
            {
               num_of_entries = 0;
               retc = (*ip_list_ptr)->CountEntries(&num_of_entries, 0, (*ip_list_ptr));
               for(ii=0, cur_entry_no=0; (ii<num_of_entries) && SUCCEEDED(retc); ii++, cur_entry_no++)
               {
                  sprintf((char *)str_buf, "check[%d]", ii+1);
                  retc=var_list->SearchTreeEntry(str_buf, TvStrCmpStrict_, &var_rec_entry_ptr, &var_rec_father);
                  if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                  
                  if(var_rec_entry_ptr && SUCCEEDED(retc))
                  {
                     var_rec_ptr = (PostVarRec *)var_rec_entry_ptr->GetValue();
                     KP_ASSERTE(var_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, False);
                     KP_ASSERTE(var_rec_entry_ptr->GetValSize() >= sizeof(PostVarRec), KP_E_SYSTEM_ERROR, null, False);
                     if(SUCCEEDED(retc))
                     {
                        if(strcmp(var_rec_ptr->m_lpszVarData, "on")==0)
                        {
                           cur_ip_entry=ip_father=NULL;
int jj = cur_entry_no;
                           retc=(*ip_list_ptr)->GetEntryPtr(&jj, &cur_ip_entry, 0, (*ip_list_ptr));
                           if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                        
                           if((cur_ip_entry==NULL) && SUCCEEDED(retc))
                           {
                              retc=KP_E_SYSTEM_ERROR;
                              OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                           }

                           if(SUCCEEDED(retc)) retc = cur_ip_entry->GetFather(&ip_father);

                           if(SUCCEEDED(retc))
                           {
// --------------------- trinam  
                              if(ip_father)
                              {
                                 retc=ip_father->DeleteChild();
                                 if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                              }
                              else
                              {
// --------------------- trinam pirma irasa                        
                                 if((cur_entry_no>0) || (cur_ip_entry!=*ip_list_ptr))
                                 {
                                    retc=KP_E_SYSTEM_ERROR;
                                    OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                                 }
                                 if(SUCCEEDED(retc)) retc = (*ip_list_ptr)->GetFirstChild(&cur_ip_entry);
                                 
                                 if(SUCCEEDED(retc))
                                 {
                                    retc=(*ip_list_ptr)->SetFirstChild(NULL);
                                    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                 }
                                 if(SUCCEEDED(retc))
                                 {
                                    KP_DELETE(*ip_list_ptr);
                                    *ip_list_ptr = cur_ip_entry;
                                    if(cur_ip_entry) retc = cur_ip_entry->SetFather(NULL);                                 
                                 }                              
                              }
                              cur_entry_no--;                      
                           }
      
// // --------------------- trinam checkboxo reiksme                          
                           if(SUCCEEDED(retc))
                           {
                              if(var_rec_father)
                              {
                                 retc=var_rec_father->DeleteChild();
                                 if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                              }
                              else
                              {
                                 if(var_rec_entry_ptr!=var_list)
                                 {
                                    retc=KP_E_SYSTEM_ERROR;
                                    OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                                 }
                                 if(SUCCEEDED(retc)) retc = var_list->GetFirstChild(&var_rec_entry_ptr);
                                 if(SUCCEEDED(retc))
                                 {
                                    retc=var_list->SetFirstChild(NULL);
                                    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                                 }
                                 if(SUCCEEDED(retc))
                                 {
                                    KP_DELETE(var_list);
                                    var_list = var_rec_entry_ptr;
                                 }                              
                              }
                           }
                     
                        } // if(strcmp(var_rec_ptr->m_lpszVarData, "on")==0)
                        else
                        {
                           retc=KP_E_MSG_FORMAT;
                           OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
                        }
                  
                     } // if(SUCCEEDED(retc)) 
               
                  } // if(var_rec_entry_ptr && SUCCEEDED(retc))
               
               } // for(ii=0; ii<num_of_entries; ii++)  
      
            } // if(*ip_list_ptr)

// --------------------- issaugojam formos kintamuosius (tik buvusia "IP", checkboxai jau ismesti)                         
            if((saved_var_list_ptr == NULL) && SUCCEEDED(retc))
            {
               retc=KP_E_SYSTEM_ERROR;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc))
            {
               KP_DELETE(*saved_var_list_ptr);
               *saved_var_list_ptr = var_list;
               var_list = NULL;
            }         
      
            break; // case KPSTLSVR_FRIENDS: case KPSTLSVR_ADMINS:
         
         case KPSTLSVR_LINKS:
            KP_DELETE(m_pLinkList);
            if(SUCCEEDED(retc)) retc = SaveConfig();
            break;

         default:
            retc=E_INVALIDARG;
            OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            break;

         } // switch(iCurEnv)      

         break; // case 1:  // "Iðmesti"
         
      case 2:  // "Pridëti"
         switch(iCurEnv)
         {
         case KPSTLSVR_FRIENDS:
         case KPSTLSVR_ADMINS:
            retc=var_list->SearchTreeEntry("IP", TvStrCmpStrict_, &var_rec_entry_ptr, NULL);
            if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   
            if((var_rec_entry_ptr==NULL) && SUCCEEDED(retc))
            {
               retc=KP_E_MSG_FORMAT;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc)) var_rec_ptr = (PostVarRec *)var_rec_entry_ptr->GetValue();
            KP_ASSERTE(var_rec_ptr != NULL, KP_E_SYSTEM_ERROR, null, False);
            KP_ASSERTE(var_rec_entry_ptr->GetValSize() >= sizeof(PostVarRec), KP_E_SYSTEM_ERROR, null, False);
            if(SUCCEEDED(retc))
            {
               if(var_rec_ptr->m_lpszVarData[0]!=Nul) // tuscio neprideti 
               {
                  if(SUCCEEDED(retc))
                  {
                     retc=RemoveSpaces(var_rec_ptr->m_lpszVarData);
                     if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                  }
                  if(SUCCEEDED(retc))
                  {
                     retc=TestIP(var_rec_ptr->m_lpszVarData);
                     if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
                  
                     if(retc==E_INVALIDARG)
                     {
                        m_lLastWindowsError=WSAEFAULT;
                        retc=S_OK;
                     }
                     else if(SUCCEEDED(retc))
                     {
                        if(SUCCEEDED(retc)) ip.S_un.S_addr=inet_addr((const char *)var_rec_ptr->m_lpszVarData);
//                      if(ip.S_un.S_addr==INADDR_NONE)
//                      {
//                         retc=E_INVALIDARG;
//                         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
//                      }
                        if(SUCCEEDED(retc))
                        {
                           if(*ip_list_ptr != NULL) retc = (*ip_list_ptr)->PutToEnd(&ip, sizeof(ip));
                           else
                           {
                              KP_NEWO(*ip_list_ptr, KpTreeEntry(&ip, sizeof(ip), NULL));
                           }
                        }
                  
                     } // if(SUCCEEDED(retc)) // else if(retc==E_INVALIDARG) 
               
                  } // if(SUCCEEDED(retc))
               
               } // if(var_rec_ptr->m_lpszVarData[0]!=Nul)
            
            } // if(SUCCEEDED(retc))

            if((saved_var_list_ptr == NULL) && SUCCEEDED(retc))
            {
               retc=KP_E_SYSTEM_ERROR;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc))
            {
               KP_DELETE(*saved_var_list_ptr);
               *saved_var_list_ptr = var_list;
               var_list = NULL;
            }         
      
            break; // case KPSTLSVR_FRIENDS: case KPSTLSVR_ADMINS:
         
         case KPSTLSVR_LINKS:
         default:
            retc=E_INVALIDARG;
            OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            break;

         } // switch(iCurEnv)      
      
         break; // case 2:  // "Pridëti"
         
      case 3:  // "Iðsaugoti"
         switch(iCurEnv)
         {
         case KPSTLSVR_LINKS:
            retc = UpdateLinkList(KPST_SES_CLOSED, NULL);
            break;

         case KPSTLSVR_FRIENDS:
         case KPSTLSVR_ADMINS:
         default:
            retc=E_INVALIDARG;
            OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            break;

         } // switch(iCurEnv)      
      
         break; // case 3:  // "Iðsaugoti"

      default:
         retc=KP_E_MSG_FORMAT;
         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         
#ifdef Debug // #if TRUE //    
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs("-- KpStLicSvr::ProcessVars() -------------------\n>>>\n", out_file);
fputs((const char *)var_rec_ptr->m_lpszVarData, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif

         if(saved_var_list_ptr != NULL)
         {
            KP_DELETE(*saved_var_list_ptr);
            *saved_var_list_ptr = var_list;
            var_list = NULL;
         }         
      
         break;

      } // switch(but_num)

   } // if(SUCCEEDED(retc))

   KP_DELETE(var_list);

return(retc);
}


// -----------------------------------------------
HRESULT KpStLicSvr::GetCfgFname(unsigned char *lpszIniFnameBuf)
{                           
HRESULT retc=S_OK;
unsigned char *ini_fname_ptr;
   
   if(lpszIniFnameBuf==NULL)
      retc=OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   
   if(SUCCEEDED(retc))
   {
      retc=GetAppName(lpszIniFnameBuf);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
      
   if(SUCCEEDED(retc))
   {             
      strlwr(lpszIniFnameBuf);
      ini_fname_ptr=strstr(lpszIniFnameBuf, ".exe");

      if(ini_fname_ptr==NULL)
         retc=OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszIniFnameBuf, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) strcpy(ini_fname_ptr, ".cfg");

return(retc);   
}


//-----------------------------------
HRESULT KpStLicSvr::SaveConfig(void)
{
HRESULT retc=S_OK;
unsigned char cfg_fname[KP_MAX_FNAME_LEN+1];
FILE *out_file=NULL;
KpTreeEntry *cur_ip_entry=NULL;    // rodykle po m_pFriendList/m_pAdminList/m_pLinkList
IN_ADDR cur_ip_val;
int ii;

// ---------------------------
   if(SUCCEEDED(retc))
   {
      retc=GetCfgFname(cfg_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
      
   if(SUCCEEDED(retc)) 
   {
      out_file=fopen((const char *)cfg_fname, "wb");
      if(out_file==NULL)
      {
         retc=KP_E_DIR_ERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L);
      }
   }
   
// ---------------------------
   ii=0;
   if(m_pFriendList && SUCCEEDED(retc)) retc=m_pFriendList->CountEntries(&ii, 0, m_pFriendList);
   if(SUCCEEDED(retc))
   {
      fwrite(&ii, sizeof(int), 1, out_file); 
      if(ferror(out_file) || feof(out_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      cur_ip_entry=m_pFriendList;
      while(cur_ip_entry && SUCCEEDED(retc))
      {
         memcpy(&cur_ip_val, cur_ip_entry->GetValue(), sizeof(cur_ip_val));
      
         if(SUCCEEDED(retc))
         {
            fwrite(&cur_ip_val.S_un.S_addr, sizeof(cur_ip_val.S_un.S_addr), 1, out_file); 
            if(ferror(out_file) || feof(out_file))
            {
               retc=KP_E_FERROR;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
         }
      
         if(SUCCEEDED(retc)) retc = cur_ip_entry->GetFirstChild(&cur_ip_entry);
      }
   }   

// --------------------------------
   ii=0;
   if(m_pAdminList && SUCCEEDED(retc)) retc = m_pAdminList->CountEntries(&ii, 0, m_pAdminList);
   if(SUCCEEDED(retc)) fwrite(&ii, sizeof(int), 1, out_file); 
   
   if(SUCCEEDED(retc))
   {
      cur_ip_entry=m_pAdminList;
      while(cur_ip_entry && SUCCEEDED(retc))
      {
         memcpy(&cur_ip_val, cur_ip_entry->GetValue(), sizeof(cur_ip_val));
      
         if(SUCCEEDED(retc))
         {
            fwrite(&cur_ip_val.S_un.S_addr, sizeof(cur_ip_val.S_un.S_addr), 1, out_file); 
            if(ferror(out_file) || feof(out_file))
            {
               retc=KP_E_FERROR;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
         }
      
         if(SUCCEEDED(retc)) retc = cur_ip_entry->GetFirstChild(&cur_ip_entry);
      }
   }   

// --------------------------------
   ii=0;
   if(m_pLinkList && SUCCEEDED(retc)) retc = m_pLinkList->CountEntries(&ii, 0, m_pLinkList);
   if(SUCCEEDED(retc)) fwrite(&ii, sizeof(int), 1, out_file); 
   
   if(SUCCEEDED(retc))
   {
      cur_ip_entry = m_pLinkList;
      while((cur_ip_entry != NULL) && SUCCEEDED(retc))
      {
         KP_ASSERTE(cur_ip_entry->GetValSize() >= sizeof(KpstSesData), KP_E_SYSTEM_ERROR, null, False);
         if(SUCCEEDED(retc))
         {
            fwrite(cur_ip_entry->GetValue(), sizeof(KpstSesData), 1, out_file); 
            if(ferror(out_file) || feof(out_file))
            {
               retc = KP_E_FERROR;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
         }
      
         if(SUCCEEDED(retc)) retc = cur_ip_entry->GetFirstChild(&cur_ip_entry);
      }
   }   

// --------------------------------------
   if(SUCCEEDED(retc))
      if(fclose(out_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      }

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::ReadConfig(void)
{
HRESULT retc=S_OK;
unsigned char cfg_fname[KP_MAX_FNAME_LEN+1];
FILE *in_file=NULL;
IN_ADDR cur_ip;
int count;
int ii;
KpstSesData link_record;

// ---------------------------
   if(SUCCEEDED(retc))
   {
      retc=GetCfgFname(cfg_fname);
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
      
   if(SUCCEEDED(retc)) 
   {
      in_file=fopen((const char *)cfg_fname, "rb");
      if(in_file==NULL)
      {
         retc=KP_E_FILE_NOT_FOUND;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L);
      }
   }
   
// ---------------------------
   if(SUCCEEDED(retc))
   {
      count=0;
      fread(&count, sizeof(int), 1, in_file); 
      if(feof(in_file))
      {
         retc=KP_E_EOF;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   for(ii=0; ii<count && SUCCEEDED(retc); ii++)
   {
      fread(&cur_ip, sizeof(cur_ip), 1, in_file); 
      if(feof(in_file))
      {
         retc=KP_E_EOF;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         if(m_pFriendList)
         {
            retc=m_pFriendList->PutToEnd(&cur_ip, sizeof(cur_ip));
            if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
         }
         else
         {
            KP_NEWO(m_pFriendList, KpTreeEntry(&cur_ip, sizeof(cur_ip), NULL));
         }
      }   
   }

// --------------------------------------
   if(SUCCEEDED(retc))
   {
      count=0;
      fread(&count, sizeof(int), 1, in_file); 
      if(feof(in_file))
      {
         retc=KP_E_EOF;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   for(ii=0; ii<count && SUCCEEDED(retc); ii++)
   {
      fread(&cur_ip, sizeof(cur_ip), 1, in_file); 
      if(feof(in_file))
      {
         retc=KP_E_EOF;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         if(m_pAdminList)
         {
            retc=m_pAdminList->PutToEnd(&cur_ip, sizeof(cur_ip));
            if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
         }
         else
         {
            KP_NEWO(m_pAdminList, KpTreeEntry(&cur_ip, sizeof(cur_ip), NULL));
         }
      }   
   }

// --------------------------------------
   if(SUCCEEDED(retc))
   {
      count=0;
      fread(&count, sizeof(int), 1, in_file); 
      if(feof(in_file))
      {
         retc=KP_E_EOF;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

   for(ii=0; ii<count && SUCCEEDED(retc); ii++)
   {
      fread(&link_record, sizeof(link_record), 1, in_file); 
      if(feof(in_file))
      {
         retc=KP_E_EOF;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }
      if(ferror(in_file))
      {
         retc=KP_E_FERROR;
         OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         if(m_pLinkList)
         {
            retc=m_pLinkList->PutToEnd(&link_record, sizeof(link_record));
            if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
         }
         else
         {
            KP_NEWO(m_pLinkList, KpTreeEntry(&link_record, sizeof(link_record), NULL));
         }
      }   
   }

// --------------------------------------
   if(in_file)
      if(fclose(in_file))
      {
         if(SUCCEEDED(retc))
         {
            retc=KP_E_FERROR;
            OutputErrorMessage(retc, cfg_fname, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::CheckClientIP(/* IN_ADDR *pClientHost, */ KpStLisSvrEnvirs iCurEnv)
{
HRESULT retc=S_OK;
HRESULT reta=KP_E_ACCESS_DENIED;
KpTreeEntry **ip_list_ptr=NULL; // ip saraso adreso adresas
KpTreeEntry *cur_ip_entry=NULL;    // rodykle po *ip_list_ptr
KpTreeEntry *cur_admin=NULL;    // rodykle po prisijungusiu adminu sarasa
IN_ADDR cur_ip_val;

IN_ADDR *pClientHost=NULL;


   if((m_pLicListSocket==NULL) && SUCCEEDED(retc))
   {
      retc=KP_E_SYSTEM_ERROR;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   
   if(SUCCEEDED(retc)) pClientHost=&m_pLicListSocket->m_PackedUrl.m_Addr; 

   if((pClientHost==NULL) && SUCCEEDED(retc))
   {
//    retc=E_INVALIDARG;
      retc=KP_E_SYSTEM_ERROR;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) switch(iCurEnv)
   {
   case KPSTLSVR_FRIENDS:
      ip_list_ptr=&m_pFriendList;
      break;
   case KPSTLSVR_ADMINS:
      ip_list_ptr=&m_pAdminList;
      break;
   case KPSTLSVR_LINKS:
   default:   
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
      break;
   }      
   if((ip_list_ptr==NULL) && SUCCEEDED(retc))
   {
      retc=KP_E_SYSTEM_ERROR;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }

   if((iCurEnv==KPSTLSVR_ADMINS) && SUCCEEDED(retc))
      if(pClientHost->S_un.S_addr==KP_INADDR_LOOPBACK) reta=S_OK; // INADDR_LOOPBACK // LOCAL_HOST 127.0.0.1

   if(SUCCEEDED(retc))
   {
      cur_ip_entry=*ip_list_ptr;

      while((cur_ip_entry != NULL) && FAILED(reta) && SUCCEEDED(retc))
      {
         KP_ASSERTE(cur_ip_entry->GetValSize() >= sizeof(cur_ip_val), KP_E_SYSTEM_ERROR, null, False);
         if(SUCCEEDED(retc))
            memcpy(&cur_ip_val, cur_ip_entry->GetValue(), sizeof(cur_ip_val));
         
         if(SUCCEEDED(retc))
            if(
               ((cur_ip_val.S_un.S_un_b.s_b1==pClientHost->S_un.S_un_b.s_b1) || (cur_ip_val.S_un.S_un_b.s_b1==255)) && 
               ((cur_ip_val.S_un.S_un_b.s_b2==pClientHost->S_un.S_un_b.s_b2) || (cur_ip_val.S_un.S_un_b.s_b2==255)) && 
               ((cur_ip_val.S_un.S_un_b.s_b3==pClientHost->S_un.S_un_b.s_b3) || (cur_ip_val.S_un.S_un_b.s_b3==255)) && 
               ((cur_ip_val.S_un.S_un_b.s_b4==pClientHost->S_un.S_un_b.s_b4) || (cur_ip_val.S_un.S_un_b.s_b4==255))
              ) reta=S_OK;
      
         if(SUCCEEDED(retc)) retc = cur_ip_entry->GetFirstChild(&cur_ip_entry);
      }
   }
   
// pranesimas i console   
   if((iCurEnv==KPSTLSVR_ADMINS) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(reta))
      {
         cur_admin=m_pCurAdmins;
         while(cur_admin && SUCCEEDED(retc))
         {
            KP_ASSERTE(cur_admin->GetValSize() >= sizeof(cur_ip_val), KP_E_SYSTEM_ERROR, null, False);
            if(SUCCEEDED(retc))
               memcpy(&cur_ip_val, cur_admin->GetValue(), sizeof(cur_ip_val));
            if(SUCCEEDED(retc))
               if(pClientHost->S_un.S_addr==cur_ip_val.S_un.S_addr) break;
            
            if(SUCCEEDED(retc)) retc = cur_admin->GetFirstChild(&cur_admin);
         }

         if((cur_admin==NULL) && SUCCEEDED(retc))
         {
            if(m_pCurAdmins)
            {
               retc=m_pCurAdmins->PutToEnd(pClientHost, sizeof(*pClientHost));
               if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
            }
            else
            {
               KP_NEWO(m_pCurAdmins, KpTreeEntry(pClientHost, sizeof(*pClientHost), NULL));
            }
         
            if(SUCCEEDED(retc)) 
               retc=AddIPConsMsg(KPSTLSVR_MSG_MAINTENANCE_STARTED, True, m_pLicListSocket);
         }
      }
      else
         retc=AddIPConsMsg(KPSTLSVR_MSG_MAINTENANCE_REFUSED, True, m_pLicListSocket);
   }

   if(SUCCEEDED(retc)) retc=reta;

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::GetNameFromResults(unsigned char *lpszOutNameBuf, int iBufLen, const unsigned char *lpszResults)
{ 
HRESULT retc=S_OK;
const unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   if(((lpszOutNameBuf == NULL) || (lpszResults == NULL)) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc))
   {                                 
       pnts = lpszResults;
       pntd = lpszOutNameBuf;
       
       while((*pnts!=Ht) && *pnts && (strchr(lpszEols, *pnts)==NULL) && SUCCEEDED(retc)) // '\t'
       {
          if((pntd - lpszOutNameBuf) + 1 >= iBufLen)
          {
             retc=KP_E_BUFFER_OVERFLOW;
             OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
          } 
          if(SUCCEEDED(retc)) *(pntd++) = *(pnts++);
       }                                    
       if(*pnts==Ht){ *pntd++ = Spc; pnts++; } // '\t'
       while((*pnts!=Ht) && *pnts && (strchr(lpszEols, *pnts)==NULL) && SUCCEEDED(retc)) // '\t'
       {
          if((pntd - lpszOutNameBuf) + 1 >= iBufLen)
          {
             retc=KP_E_BUFFER_OVERFLOW;
             OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
          } 
          if(SUCCEEDED(retc)) *(pntd++) = *(pnts++);
       }                                    
       *pntd++=Nul;
   }
                              
return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::SearchLinkList(KpTreeEntry **ppEntryPtr, KpstSesData *pNewRecordData)
{
HRESULT retc=S_OK;
KpTreeEntry *cur_item = NULL;
KpTreeEntry *found_item = NULL;
unsigned char new_name[KP_MAX_FNAME_LEN+1];
unsigned char cur_name[KP_MAX_FNAME_LEN+1];
KpstSesData cur_link_record;
int namelen;

// static unsigned char log_msg[KPST_LOG_MSG_LEN+1];

   if(((ppEntryPtr == NULL) || (pNewRecordData == NULL)) && SUCCEEDED(retc))
   {
      retc=E_INVALIDARG;
      OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

#if FALSE
if(SUCCEEDED(retc))
{
log_msg[0] = Nul;
AppendLogMessage(log_msg, (const unsigned char *)"Ieðkom: ");
if((pNewRecordData->m_iSesStatus >=0) && (pNewRecordData->m_iSesStatus < KPST_NUM_OF_SES_STATES)) 
   AppendLogMessage(log_msg, lpszSesStates[pNewRecordData->m_iSesStatus]);
else AppendLogMessage(log_msg, (const unsigned char *)"SES_UNKNOWN");
AppendLogMessage(log_msg, (const unsigned char *)" ");
AppendLogMessage(log_msg, pNewRecordData->m_lpszData);
PutLogMessage(log_msg, NULL);
}
#endif

   if(SUCCEEDED(retc)) retc = GetNameFromResults(new_name, KP_MAX_FNAME_LEN, pNewRecordData->m_lpszData);

   if(SUCCEEDED(retc))
   {
      cur_item = m_pLinkList;
   
      while((cur_item != NULL) && (!found_item) && SUCCEEDED(retc))
      {
         KP_ASSERTE(cur_item->GetValSize() >= sizeof(cur_link_record), KP_E_SYSTEM_ERROR, null, False);
         if(SUCCEEDED(retc)) memcpy(&cur_link_record, cur_item->GetValue(), sizeof(cur_link_record)); 
         if(SUCCEEDED(retc)) retc = GetNameFromResults(cur_name, KP_MAX_FNAME_LEN, cur_link_record.m_lpszData);

#if FALSE
if(SUCCEEDED(retc))
{
log_msg[0] = Nul;
AppendLogMessage(log_msg, (const unsigned char *)"Randam: ");
if((cur_link_record.m_iSesStatus >=0) && (cur_link_record.m_iSesStatus < KPST_NUM_OF_SES_STATES)) 
   AppendLogMessage(log_msg, lpszSesStates[cur_link_record.m_iSesStatus]);
else AppendLogMessage(log_msg, (const unsigned char *)"SES_UNKNOWN");
AppendLogMessage(log_msg, (const unsigned char *)" ");
AppendLogMessage(log_msg, cur_link_record.m_lpszData);
PutLogMessage(log_msg, NULL);
}
#endif

// jei (strlen(pNewRecordData->m_lpszData) == 0) - nelyginam nei IP, nei pavardes - tik m_iSesStatus  
         namelen = strlen(new_name);
         if(
            ((!namelen) || (pNewRecordData->m_lIpAddr.S_un.S_addr == cur_link_record.m_lIpAddr.S_un.S_addr)) &&
            ((!namelen) || (strcmp(new_name, cur_name) == 0)) &&
            (pNewRecordData->m_iSesStatus >= cur_link_record.m_iSesStatus) &&
            SUCCEEDED(retc)
           )
            found_item = cur_item;
            
         if((!found_item) && SUCCEEDED(retc)) retc = cur_item->GetFirstChild(&cur_item);
                   
      } // while(cur_item && (found_item == NULL) && SUCCEEDED(retc))
      
   } // if(SUCCEEDED(retc))


   if(ppEntryPtr) *ppEntryPtr = found_item;
 
return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::UpdateLinkList(KpstSesStats iSessionStatus, const unsigned char *lpszResultData)
{
HRESULT retc=S_OK;
KpstSesData link_record;
KpTreeEntry *found_item = NULL;
KpstSesData found_data;
bool create_new = True;
unsigned char msg_buf[KP_MAX_FNAME_LEN+100];
KpStLicSvr *stap_ptr=this;

   if((stap_ptr==NULL) && SUCCEEDED(retc))
      retc=OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      time(&(link_record.m_lTimeStamp));
      link_record.m_iSesStatus = iSessionStatus;

// fiktyvus naujo iraso duomenys - jei (lpszResultData==NULL), irasas nebus kuriamas
      link_record.m_lIpAddr.S_un.S_addr=INADDR_NONE;
      link_record.m_lpszData[0] = Nul;
   }

   if(lpszResultData && SUCCEEDED(retc))
   {
// naujo/atnaujinamo iraso duomenys
      if((m_pLicListSocket == NULL) && SUCCEEDED(retc))
      {
         retc=KP_E_SYSTEM_ERROR;
         OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
      if(SUCCEEDED(retc))
         link_record.m_lIpAddr = m_pLicListSocket->m_PackedUrl.m_Addr;
      
      if(/* lpszResultData && */ SUCCEEDED(retc))
      {      
         if(strlen(lpszResultData) >= KP_MAX_FILE_LIN_LEN)
         { 
            retc=KP_E_BUFFER_OVERFLOW;
            OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
         }
         if(SUCCEEDED(retc)) strcpy(link_record.m_lpszData, lpszResultData); 
      }
   
   } // if(lpszResultData && SUCCEEDED(retc))

// ---------------------- 
   create_new = True;
   found_item = NULL;
   if(SUCCEEDED(retc))
   {
      if((iSessionStatus == KPST_SES_OPEN) || (lpszResultData==NULL))
      {
// naujos sesijos kurimas, jei (lpszResultData==NULL) - tik uzdaryti visas senas aktyvias, naujos nekurti
         if(lpszResultData==NULL) create_new = False;
         else create_new = True;
         
         found_item = NULL;

// uzdarom visas tokias pat, bet dar atviras
         link_record.m_iSesStatus = KPST_SES_ACTIVE;
   
         do
         {  
            found_item = NULL;
            retc = SearchLinkList(&found_item, &link_record);   
            
            if((found_item != NULL) && SUCCEEDED(retc))
            {
               KP_ASSERTE(found_item->GetValSize() >= sizeof(found_data), KP_E_SYSTEM_ERROR, null, False);
               if(SUCCEEDED(retc)) memcpy(&found_data, found_item->GetValue(), sizeof(found_data));

               if(SUCCEEDED(retc)) retc = GetNameFromResults(msg_buf, KP_MAX_FNAME_LEN, found_data.m_lpszData);
               if(SUCCEEDED(retc))
               {  
                  strcat(msg_buf, " – ");
                  strcat(msg_buf, KPSTLSVR_MSG_PREVIOUS_SESSION_ABANDONED);
                  retc=stap_ptr->AddConsMsg(msg_buf);
               }
               if(SUCCEEDED(retc)) retc=PutLogMessage(msg_buf, NULL);

// ka tik uzregistruotas seansas duomenu neturi - nera ka irasineti
               if((found_data.m_iSesStatus != KPST_SES_OPEN) && SUCCEEDED(retc))
               { 
                  retc=stap_ptr->WriteDataFile((const unsigned char *)"", (const unsigned char *)"", 
                           found_data.m_lpszData, True, False);
                  if(FAILED(retc))
                     retc=stap_ptr->OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);

                  if(SUCCEEDED(retc))
                     retc = GetNameFromResults(msg_buf, KP_MAX_FNAME_LEN, found_data.m_lpszData);
                  if(SUCCEEDED(retc))
                  {  
                     strcat(msg_buf, " – ");
                     strcat(msg_buf, KPSTLSVR_MSG_INCOMPLETE_REZULTS_WRITTEN);
                     retc=stap_ptr->AddConsMsg(msg_buf);
                  }
                  if(SUCCEEDED(retc)) retc=PutLogMessage(msg_buf, NULL);
               }
            
// stabdom ankstesni seansa
               found_data.m_iSesStatus = KPST_SES_CLOSED;
               KP_ASSERTE(found_item->GetValSize() >= sizeof(found_data), KP_E_SYSTEM_ERROR, null, False);
               if(SUCCEEDED(retc)) memcpy(found_item->GetValue(), &found_data, sizeof(found_data));
            }
   
         } while(found_item && SUCCEEDED(retc));

         found_item = NULL;
         link_record.m_iSesStatus = iSessionStatus;
   
      } // if(iSessionStatus == KPST_SES_OPEN)
      
      else 
      {
// pildom jau egzistuojancia atvira sesija
// (iSesStatus == KPST_SES_ACTIVE) || (iSesStatus == KPST_SES_DONE)
         create_new = False;
         found_item = NULL;

// ieskom tokios pat, bet dar atviros
         link_record.m_iSesStatus = KPST_SES_ACTIVE;
         retc = SearchLinkList(&found_item, &link_record);   
         link_record.m_iSesStatus = iSessionStatus;

         if(SUCCEEDED(retc))
         {
            if(found_item)
            {
               KP_ASSERTE(found_item->GetValSize() >= sizeof(link_record), KP_E_SYSTEM_ERROR, null, False);
               if(SUCCEEDED(retc)) memcpy(found_item->GetValue(), &link_record, sizeof(link_record));
            }
            else
            {
               create_new = True;

               if(SUCCEEDED(retc)) retc = GetNameFromResults(msg_buf, KP_MAX_FNAME_LEN, link_record.m_lpszData);
               if(SUCCEEDED(retc))
               {  
                  strcat(msg_buf, KPSTLSVR_MSG_UNLOGGED_RESULTS);
                  OutputErrorMessage(KP_E_TRANS_ERR, msg_buf, True, __FILE__, __LINE__, 0L, NULL);
               }
            }
         }

      } // else // if(iSessionStatus == KPST_SES_OPEN)
   
   } // if(SUCCEEDED(retc))


// --------------------
   if(create_new && SUCCEEDED(retc))
   {
      if(m_pLinkList != NULL) retc = m_pLinkList->PutToEnd(&link_record, sizeof(link_record));
      else
      {
         KP_NEWO(m_pLinkList, KpTreeEntry(&link_record, sizeof(link_record), NULL));
      }
      
   } // if(create_new && SUCCEEDED(retc))


// -------------------   
   if(SUCCEEDED(retc)) retc = SaveConfig();

return(retc);
}


//-----------------------------------
HRESULT KpStLicSvr::ScanPostData(unsigned char *lpszPostMsgBuf, unsigned char *lpszLogBuf)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
KpStLicSvr *stap_ptr=this;
const unsigned char *pnts=NULL;
unsigned char *pntd=NULL;
unsigned char msg_buf[KP_MAX_FILE_LIN_LEN /* KP_MSG_LEN */ +1];
KpChar i_str_buf[KP_MAX_FILE_LIN_LEN+1];
bool tarp_fl = False;
unsigned char head_str[KP_MAX_FILE_LIN_LEN+1];
   head_str[0] = Nul;
bool ignore = False; 
int ii;

   if((lpszPostMsgBuf==NULL) && SUCCEEDED(retc))
      retc=OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
   if((stap_ptr==NULL) && SUCCEEDED(retc))
      retc=OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                        
// -------------------------------------- perkoduojam %xx á ðeðioliktainá kodà
   if(SUCCEEDED(retc)) retc = stap_ptr->DecodePostMsg(lpszPostMsgBuf, lpszPostMsgBuf);
   
   if(lpszLogBuf && SUCCEEDED(retc))
   {
   /* retc = */ AppendLogMessage(lpszLogBuf, (const unsigned char *)" Message: ");
   /* if(SUCCEEDED(retc)) retc = */ AppendLogMessage(lpszLogBuf, lpszPostMsgBuf);
   }

#ifdef Debug
// if(SUCCEEDED(retc)) KpMsgOut(lpszPostMsgBuf, IDI_ERROR, KP_MB_BAIGTI);
#endif

   if(SUCCEEDED(retc))
   {

// ------------------------------------
// --- galutiniø rezultatø POST praneðimas, eilutes pabaigos gale nera: 

// sl=Kaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980
// sl=Kala%7cMala%7c7kl%7c336958436%7c898201907%7c944121410%7c741083137%7c875300865%7c68051204
// sl=%5c%5cu017Dydr%5c%5cu016Bnas%7c%5c%5cu010C%5c%5cu0117%5c%5cu017Ea%7c7kl%7c336958056%7c898201907%7c944121410%7c1797558301%7c1705985%7c67281668
// sl=Acrobat%7cArkim%7c7kl%7c336958036%7c898201907%7c944121410%7c74610818%7c105597761%7c102242053&is=
// sl=Mind%5c%5cu0117%7c%5c%5cu010C%5c%5cu0117%5c%5cu017Ea%7c7kl%7c336958052%7c898201907%7c944121410%7c892215297%7c1705985%7c371336226%7c70359303&is=

// ------------------------------------
// --- tarpiniø rezultatø POST praneðimas su þvaigþdute, eilutes pabaigos gale nera: 
// --- iki 2008.02.22

// sl=*%7cKaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980

// ------------------------------------
// --- pirmas fiktyvus rezultatø siuntimas - kad nedingtø tolesni praneðimai
// --- pirmas praneðimas kaþkodël ilgai laukia, jeigu Acrobatà greitai uþdarai - taip ir nenueina
// --- ateina kaþkodël prieð registracijos praneðimà, reikia ignoruoti.
// --- arkim 2008.02.15, realizuotas nebuvo. 

// sl=+%7cKaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980

// ------------------------------------
// --- tarpiniø rezultatø praneðimas, su uþdavinio nr., nuo 2008.02.22 

// sl=5%7cKaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980

// ------------------------------------
// --- pirmas fiktyvus rezultatø siuntimas su nuliu, reikia ignoruoti, nuo 2008.02.22

// sl=0%7cKaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980

      ignore = False;
      
      if(strstr(lpszPostMsgBuf, "sl=")==lpszPostMsgBuf)
      {
// tarpiniø duomenø praneðimas su þvaigþdute 
         if(strstr(lpszPostMsgBuf, "sl=*|")==lpszPostMsgBuf)
         {
            tarp_fl = True;
            strcpy(head_str, (const unsigned char *)"sl=*|");
         }
// fiktyvus duomenø praneðimas su pliusu           
         else if(strstr(lpszPostMsgBuf, "sl=+|")==lpszPostMsgBuf) 
         {
            tarp_fl = True;
            strcpy(head_str, (const unsigned char *)"sl=+|");
            ignore = True;
         }
// fiktyvus duomenø praneðimas su nuliu           
         else if(strstr(lpszPostMsgBuf, "sl=0|")==lpszPostMsgBuf) 
         {
            tarp_fl = True;
            strcpy(head_str, (const unsigned char *)"sl=0|");
            ignore = True;
         }
// tarpiniø duomenø praneðimas su uþdavinio nr. 
         else if(isdigit(lpszPostMsgBuf[3]))
         {
            tarp_fl = True;
            pnts = strchr(lpszPostMsgBuf, '|');
            if(pnts == NULL)
               retc=stap_ptr->OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               ii = pnts - lpszPostMsgBuf + 1;
               strncpy(head_str, lpszPostMsgBuf, ii);
               head_str[ii] = Nul;
            }
         }
// galutiniai duomenys
         else       
         {
            tarp_fl = False;
            strcpy(head_str, (const unsigned char *)"sl=");
         }

// ---------------      
         if((!ignore) && SUCCEEDED(retc))
         {
            retc0=stap_ptr->DecodePdfParText(lpszPostMsgBuf, lpszPostMsgBuf);
            if(FAILED(retc0))
               /* retc= */ stap_ptr->OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);
         }

//       if(lpszLogBuf && SUCCEEDED(retc))
//       {
//       /* retc = */ AppendLogMessage(lpszLogBuf, (const unsigned char *)" Message: ");
//       /* if(SUCCEEDED(retc)) retc = */ AppendLogMessage(lpszLogBuf, lpszPostMsgBuf);
//       }

         if((!ignore) && SUCCEEDED(retc))
         {
            pnts=lpszPostMsgBuf+strlen(head_str);

            pntd=strchr(pnts, '&'); // ..&is=
            if(pntd) *pntd=Nul;

// '+' --> ' '
            pntd = (unsigned char *)pnts;
            while((*pntd) && (*pntd!=Tab))
            {
               if(*pntd == '+') *pntd = Spc;
               pntd++;
            }
            if(*pntd==Tab) pntd++;
            while((*pntd) && (*pntd!=Tab))
            {
               if(*pntd == '+') *pntd = Spc;
               pntd++;
            }
         }
         
// --------------------
         if((!tarp_fl) && (!ignore) && SUCCEEDED(retc))
         {
            retc=stap_ptr->WriteDataFile((const unsigned char *)"", (const unsigned char *)"", 
                           pnts, True, False);
            if(FAILED(retc))
               retc=stap_ptr->OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
         }                                          

// --------------------
         if((!ignore) && SUCCEEDED(retc)) 
            retc = UpdateLinkList(tarp_fl? KPST_SES_ACTIVE: KPST_SES_DONE /* KPST_SES_CLOSED */, pnts);

// ----------------------
         if((!ignore) && SUCCEEDED(retc))
         {
            pntd=(unsigned char *)pnts;
            while((*pntd) && ((*pntd)!=Ht)) pntd++;
            if((*pntd)==Ht) *pntd++ = Spc;
            while((*pntd) && ((*pntd)!=Ht)) pntd++;
            if((*pntd)==Ht) *pntd++ = Nul;
         
            strcpy(msg_buf, pnts);
            strcat(msg_buf, KPSTLSVR_MSG_RECEIVED_RESULTS);
            if(tarp_fl) strcat(msg_buf, KPSTLSVR_MSG_INTERMEDIATE_RES);
            else strcat(msg_buf, KPSTLSVR_MSG_FINAL_RES);                                          
            strcat(msg_buf, KPSTLSVR_MSG_RESULTS_RECEIVED);                                          
      
            retc=stap_ptr->AddConsMsg(msg_buf);
         }
      }

// ------------------------------------
// --- registracijos POST pranesimas, eilutes pabaigos gale nera: 

// Text.Vardas=Acrobat&Text.Pavarde=Arkim&toliau=
// Text.Vardas=Mind%c4%97&Text.Pavarde=%c4%8c%c4%97%c5%bea&toliau=
// Text.Vardas=varrrrdas&Text.Pavarde=pavarrrrde&toliau=
      else if(strstr(lpszPostMsgBuf, "Text.Vardas=")==lpszPostMsgBuf)
      {
         if(SUCCEEDED(retc))
         {
            retc0=DecodeKpStrUnicode(i_str_buf, KP_MAX_FILE_LIN_LEN, lpszPostMsgBuf, UC_UTF_8);
            if(FAILED(retc0))
               /* retc= */ stap_ptr->OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
            i_str_buf[KP_MAX_FILE_LIN_LEN]=C_Nul;

            retc0=KptStrDecode(lpszPostMsgBuf, i_str_buf, /* stap_ptr->m_pLicListSocket->m_lContLen, */ TV_MAIN_HTML_CTBL);
            if(FAILED(retc0))
               /* retc= */ stap_ptr->OutputErrorMessage(retc0, null, False, __FILE__, __LINE__, 0L, NULL);
         }

//       if(lpszLogBuf && SUCCEEDED(retc))
//       {
//       /* retc = */ AppendLogMessage(lpszLogBuf, (const unsigned char *)" Message: ");
//       /* if(SUCCEEDED(retc)) retc = */ AppendLogMessage(lpszLogBuf, lpszPostMsgBuf);
//       }

// ---------------
         if(SUCCEEDED(retc))
         {
            pnts=lpszPostMsgBuf+strlen("Text.Vardas=");
            pntd=(unsigned char *)pnts;
            while((*pntd) && ((*pntd)!='&'))
            { 
               if(*pntd == '+') *pntd = Spc;
               pntd++;
            }
            if((*pntd)=='&') *pntd++ = Nul;
            
            if(strlen(pnts) + 1 >= KP_MAX_FILE_LIN_LEN)
            {
               retc = KP_E_BUFFER_OVERFLOW;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
         }
         if(SUCCEEDED(retc))
         {
            strcpy(msg_buf, pnts);
            strcat(msg_buf, "\t");
         
            if(strstr(pntd, "Text.Pavarde=")==pntd)
            {
               pntd += strlen("Text.Pavarde=");
               pnts=pntd;
               while((*pntd) && ((*pntd)!='&'))
               {
                  if(*pntd == '+') *pntd = Spc;
                  pntd++;
               }
               if((*pntd)=='&') *pntd++ = Nul;
               
               if(strlen(msg_buf) + strlen(pnts) >= KP_MAX_FILE_LIN_LEN)
               {
                  retc = KP_E_BUFFER_OVERFLOW;
                  OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
               }
            }
            if(SUCCEEDED(retc)) strcat(msg_buf, pnts);
         }

         if(SUCCEEDED(retc)) retc = UpdateLinkList(KPST_SES_OPEN, msg_buf);

         if(SUCCEEDED(retc))
         {
            pntd = strchr(msg_buf, '|');
            if(pntd) *pntd = Spc; // ' '
            
            pnts = KPSTLSVR_MSG_REGISTERED;
            if(strlen(msg_buf) + strlen(pnts) >= KP_MAX_FILE_LIN_LEN)
            {
               retc = KP_E_BUFFER_OVERFLOW;
               OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
            }
            if(SUCCEEDED(retc)) 
            {
               strcat(msg_buf, pnts);
               retc=stap_ptr->AddConsMsg(msg_buf);
            }
         }
      }

// ------------------------------------
// --- Matau5e uzdavinio pradzios POST pranesimas

// File_Name=cd5_3.pdf&Start_Time=2006.09.11+11%3a51%3a05&Lygis=1+lygis&Pasirinktas_rezimas=Mokausi&Pasirinkta_uzd_sk=5&Pasirinktas_laikas_sk=2
// File_Name=cd5_3.pdf&Start_Time=2006.09.11+16%3a06%3a51&Lygis=1+lygis&Pasirinktas_rezimas=Lenktyniauju&Pasirinktas_laikas_sk=4
// File_Name=cd5_3.pdf&Stop_Time=2006.09.11+16%3a06%3a39&Pateikta_uzd_sk=1

// !!! TODO - i m_pLinkList

      else if(strstr(lpszPostMsgBuf, "File_Name=")==lpszPostMsgBuf)
      {
//       if(lpszLogBuf && SUCCEEDED(retc))
//       {
//       /* retc = */ AppendLogMessage(lpszLogBuf, (const unsigned char *)" Message: ");
//       /* if(SUCCEEDED(retc)) retc = */ AppendLogMessage(lpszLogBuf, lpszPostMsgBuf);
//       }

         if(SUCCEEDED(retc))
         {   
            pntd=lpszPostMsgBuf;
            while(*pntd && SUCCEEDED(retc))
            {
               if(*pntd=='+') *pntd=Spc; // ' '
               pntd++;
            }
         }

         if(SUCCEEDED(retc) && SUCCEEDED(retc))
            retc=stap_ptr->WriteExercDataFile(lpszPostMsgBuf);
         
         if(SUCCEEDED(retc))
         {
            if(strstr(lpszPostMsgBuf, "Stop_Time=")) strcpy(msg_buf, KPSTLSVR_MSG_EXERCISE_DONE); // !!! nustatyti KPST_SES_CLOSED
            else strcpy(msg_buf, KPSTLSVR_MSG_EXCERCISE);                               // !!! nustatyti KPST_SES_ACTIVE
            pnts=lpszPostMsgBuf+strlen("File_Name=");
            pntd=strchr(pnts, '&');
            if(pntd) *pntd=Nul;
            if(strlen(msg_buf)+strlen(pnts)>=KP_MAX_FILE_LIN_LEN)
               retc=stap_ptr->OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL);
         }                              
         if(SUCCEEDED(retc))
         {
            strcat(msg_buf, pnts);
            retc=stap_ptr->AddIPConsMsg(msg_buf, False, m_pLicListSocket);
         }
      }

      else
      { 
//       if(lpszLogBuf && SUCCEEDED(retc))
//       {
//       /* retc = */ AppendLogMessage(lpszLogBuf, (const unsigned char *)" Message: ");
//       /* if(SUCCEEDED(retc)) retc = */ AppendLogMessage(lpszLogBuf, lpszPostMsgBuf);
//       }

         retc=stap_ptr->OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);
      }
   }

return(retc);
}                     


// -------------------
HRESULT AppendLogMessage(unsigned char *lpszLogMsgBuf, const unsigned char *lpszNewMessage)
{
HRESULT retc=S_OK;
int ll, rest;
KpStLicSvr *stap_ptr=NULL;

   if(SUCCEEDED(retc)) stap_ptr=&theApp;

   if(SUCCEEDED(retc)) if((lpszLogMsgBuf == NULL) || (lpszNewMessage == NULL))
      retc=stap_ptr->OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
   
   if(SUCCEEDED(retc))
// if((stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST) && lpszNewMessage && SUCCEEDED(retc))
   {
      ll = strlen(lpszLogMsgBuf);
      rest = KPST_LOG_MSG_LEN - ll; 
      if(rest < 0)
      {
         retc=stap_ptr->OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL);
         rest = 0;
      } 
      strncpy(lpszLogMsgBuf+ll, lpszNewMessage, rest);
      lpszLogMsgBuf[ll+rest] = Nul;
   } 
         
return(retc);
}
                     

// ------------------- licence socket listening idle loop
DWORD WINAPI LicSockListenProc(LPVOID /* lpParameter */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
HRESULT reta=S_OK; // atsakymo klientui klaidos kodas
KpStLicSvr *stap_ptr=NULL;
static unsigned char out_msg[KP_MAX_FILE_LIN_LEN*2 + 1];
unsigned char *cmd_ptr=NULL;
static unsigned char key_buf[KP_MAX_FILE_LIN_WDT+1];
static unsigned char msg_buf[KP_MAX_FILE_LIN_LEN /* KP_MSG_LEN */ +1];
PackedUrl url_sav; // siuntëjo adresø saugojimui
unsigned char *page_ptr=NULL;
unsigned char *fdf_ptr=NULL;
unsigned char *post_msg_buf=NULL;
long read=0L;
int http_ret_code;
KpTreeEntry *var_list=NULL;
int num_of_lics=0;
static unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
   rez_fname[0]=Nul;
static unsigned char log_msg[KPST_LOG_MSG_LEN+1];
   log_msg[0]=Nul;
int prev_free_cnt;
int free_cnt;
       
// if((theKpStAppPtr==NULL) && SUCCEEDED(retc))
// {
//    retc=KP_E_NO_FILE;
//    OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
// }

   if(SUCCEEDED(retc))
   { 
//    stap_ptr = static_cast<KpStLicSvr *> theKpStAppPtr;
      stap_ptr = &theApp;
      KP_ASSERT(stap_ptr, KP_E_SYSTEM_ERROR, null, True);
   }

   if(SUCCEEDED(retc))
   {
      if(stap_ptr->m_pLicListSocket == NULL) 
      {
         retc = KP_E_SYSTEM_ERROR;
         stap_ptr->OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc))
   {
      retc=stap_ptr->GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
      if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=stap_ptr->GetIniRezFName(rez_fname);
      if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc)) if(stap_ptr->m_pLicListSocket==NULL)
   {
      retc=KP_E_NO_FILE;
      stap_ptr->OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
   
   if(SUCCEEDED(retc)) do
   { 
//    page_ptr=NULL;
      out_msg[0]=Nul;
      fdf_ptr=NULL;
      
      if(SUCCEEDED(retc))
      {
         retc=stap_ptr->m_pLicListSocket->Accept();
         if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);
      }

// iðsaugojam siuntëjo adresus – RcvHttpRequest() uþkloja juos gavëjo (localhosto) adresais ið praneðimo kepurës
      if(SUCCEEDED(retc)) memcpy(&url_sav, &(stap_ptr->m_pLicListSocket->m_PackedUrl), sizeof(url_sav));

      reta=S_OK;
      http_ret_code=HTTP_ANSW_OK;
      
      if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
      {
         reta = stap_ptr->m_pLicListSocket->RcvHttpRequest(True);
         if(FAILED(reta)) stap_ptr->OutputErrorMessageLocal(reta, null, True, True);
      }
      
// atstatom siuntëjo adresus
      if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
         stap_ptr->m_pLicListSocket->m_PackedUrl.m_Addr.S_un.S_addr=url_sav.m_Addr.S_un.S_addr;
      if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
         strcpy(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszServerName, url_sav.lpszServerName);
      
#ifdef Debug // #if TRUE //       
unsigned char out_str[100];
sprintf((char *)out_str, "Request received:  Serv:%s  File:%s", 
   stap_ptr->m_pLicListSocket->m_PackedUrl.lpszServerName,
   stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName);
#ifdef Debug
KpStLicSvrCons.AddString(out_str);
#else
stap_ptr->OutputErrorMessage(S_OK, out_str, False, __FILE__, __LINE__, 0L, NULL);
#endif

#endif      

      if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
      {
         
// ---------------------- to log file
         log_msg[0] = Nul;
         if((stap_ptr->m_pLicListSocket->m_iMsgType<0) || (stap_ptr->m_pLicListSocket->m_iMsgType >= NUM_OF_HTTP_MSG_TYPES))
         {
         /* reta= */ stap_ptr->OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
         }
         else
         { 
            sprintf((char *)log_msg, "%s %s: %s", 
               KpsockMsgTypes[stap_ptr->m_pLicListSocket->m_iMsgType],
               stap_ptr->m_pLicListSocket->m_PackedUrl.lpszServerName,
               stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName);
         }
      
// ---------------------
// licence register request "/?instcode=JJ93-EARR-4L8G-E368"
         cmd_ptr=strstr(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, KPST_HTTP_REGISTER);
         if((cmd_ptr!=NULL) && (stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_GET_REQUEST))
         {
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
               reta=stap_ptr->CheckClientIP(KPSTLSVR_FRIENDS);

            if(SUCCEEDED(reta) && SUCCEEDED(retc)) retc = stap_ptr->CountFreeLicences(&prev_free_cnt);
            
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) cmd_ptr+=strlen(KPST_HTTP_REGISTER);

            if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->ScanInstCodeFull(cmd_ptr);
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->UnpackInstCode();
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->CheckResRequest();

            if(SUCCEEDED(retc)) retc=stap_ptr->RefreshLicDisplay();
            
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->CalcInstKey();
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatInstKeyFull(key_buf);
//          if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=RemoveSpaces(key_buf);
            if(SUCCEEDED(reta))
            {
               strcpy(out_msg, KPST_REG_OK);
               strcat(out_msg, key_buf);
            }
            
            if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
               if(!PostThreadMessage(stap_ptr->m_lParentProcess, WM_COMMAND, KPST_ID_SAVE_STATUS, 0L))
               {
//                reta=KP_E_SYSTEM_ERROR;
//                OutputErrorMessage(reta, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
               }

            if(SUCCEEDED(reta) && SUCCEEDED(retc)) retc = stap_ptr->CountFreeLicences(&free_cnt);
               
            if(SUCCEEDED(reta))
            {
               if((prev_free_cnt > free_cnt) && SUCCEEDED(retc)) 
                  retc = stap_ptr->AddIPConsMsg(KPSTLSVR_MSG_CLIENT_LOGGED_IN, True, stap_ptr->m_pLicListSocket);
            }
            else
            {
               if(SUCCEEDED(retc)) retc = stap_ptr->AddIPConsMsg(KPSTLSVR_MSG_LOGGING_REFUSED, True, stap_ptr->m_pLicListSocket);
            }
         }
         else // if(cmd_ptr!=NULL) // KPST_HTTP_REGISTER
         {
// licence release request "/?remcode=644A-8E15-25GR-5L3U"
            cmd_ptr=strstr(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, KPST_HTTP_REMOVE);
            if((cmd_ptr!=NULL) && (stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_GET_REQUEST))
            {
               if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                  reta=stap_ptr->CheckClientIP(KPSTLSVR_FRIENDS);
            
               if(SUCCEEDED(reta) && SUCCEEDED(retc)) cmd_ptr+=strlen(KPST_HTTP_REMOVE);

               if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->ScanRemCodeFull(cmd_ptr);
               if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->UnpackRemCode();
               if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->CheckRelRequest();

               if(SUCCEEDED(retc)) retc=stap_ptr->RefreshLicDisplay();
               
               if(SUCCEEDED(reta))
               {
                  strcpy(out_msg, KPST_REG_OK);
                  retc=KpErrorProc.FormatErrorMessage(reta, msg_buf);
                  strcat(out_msg, msg_buf);
               }

               if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                  if(!PostThreadMessage(stap_ptr->m_lParentProcess, WM_COMMAND, KPST_ID_SAVE_STATUS, 0L))
                     reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            
               if(SUCCEEDED(reta))
                  reta = stap_ptr->AddIPConsMsg(KPSTLSVR_MSG_CLIENT_LOGGED_OFF, True, stap_ptr->m_pLicListSocket);
            }
            else // if(cmd_ptr!=NULL) // KPST_HTTP_REMOVE
            {
// "/?<...>=" // Tado duomenu siuntimai - POST pranesimai su GET sintakse

// POST /?&File_Name=cd5_3.pdf&Start_Time=&Lygis=1%20lygis&Pasirinktas_rezimas=Mokausi&Pasirinkta_uzd_sk=5&Pasirinktas_laikas_sk=2 HTTP/1.1
// Accept: */*
// Content-Type: application/vnd.fdf
// Content-Length: 1841
// User-Agent: AcroForms
// Host: 127.0.0.1:13010
// Cache-Control: no-cache

// %FDF-1.2
// %âãÏÓ
// 1 0 obj<</FDF<</F(//cd/cd5_3.pdf)/ID[<5dda0de1fed58133fbfef5eda671b678><5dda0de1fed58133fbfef5eda671b678>]/Fields[<</T(Baigesi)/V(þÿ

// POST /?&File_Name=cd5_3.pdf&Stop_Time=2006.09.25%2014:07:22&Pateikta_uzd_sk=1&Teisingai_sk=&Neteisingai_sk=1 HTTP/1.1
// Accept: */*
// Content-Type: application/vnd.fdf
// Content-Length: 1862
// User-Agent: AcroForms
// Host: 127.0.0.1:13010
// Cache-Control: no-cache

// %FDF-1.2
// %âãÏÓ
// 1 0 obj<</FDF<</F(//cd/cd5_3.pdf)/ID[<5dda0de1fed58133fbfef5eda671b678><5dda0de1fed58133fbfef5eda671b678>]/Fields[<</T(Baigesi)/V(þÿ

// /?...
//             if(strchr(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, '?'))
//             if((strstr(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/?&File_Name=")==stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName) &&
               if((strstr(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/?&") == stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName) &&
                  (stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST))
               {
// fiktyviai priimam POST duomenis
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     KP_NEWA(post_msg_buf, unsigned char, stap_ptr->m_pLicListSocket->m_lContLen + 1);
                  }                     
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     read=stap_ptr->m_pLicListSocket->m_lContLen;
                     reta=stap_ptr->m_pLicListSocket->ReceiveMsg(post_msg_buf, &read, False, True);
                  }
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                  {
                     post_msg_buf[read]=Nul;
//                /* reta = */ AppendLogMessage(log_msg, (const unsigned char *)" Message: ");
//                /* reta = */ AppendLogMessage(log_msg, post_msg_buf);
                     
#ifdef Debug
FILE *out_file=fopen("http.txt", "ab");
fputs("---------------------\n>>>\n", out_file);
fputs((const char *)post_msg_buf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif              
                  }
                  KP_DELETEA(post_msg_buf);

                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  { 
                     KP_NEWA(post_msg_buf, unsigned char, strlen(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName) + 1);
                  }                     
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     strcpy(post_msg_buf, stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName + strlen("/?&"));                  
                     reta=stap_ptr->ScanPostData(post_msg_buf, NULL);
                  }
                  
                  /* if(SUCCEEDED(reta)) */ fdf_ptr=lpszEmptyFdf;                     
               }
// "/"
               else if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/")==0)
               {
// post result data "/" rezultatai.pdf
                  if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST)
                  {
                     if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     { 
                        reta=stap_ptr->CheckClientIP(KPSTLSVR_FRIENDS);
                        if(FAILED(reta))
                           retc = stap_ptr->AddIPConsMsg(KPSTLSVR_MSG_RES_LOG_REFUSED, True, stap_ptr->m_pLicListSocket);
                     }

                     if((stap_ptr->m_pLicListSocket->m_lContLen==0L) && SUCCEEDED(reta) && SUCCEEDED(retc))
                        reta=stap_ptr->OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);

// --- Matau5e uzdavinio pradzios POST pranesimas

// File_Name=cd5_3.pdf&Start_Time=2006.09.11+11%3a51%3a05&Lygis=1+lygis&Pasirinktas_rezimas=Mokausi&Pasirinkta_uzd_sk=5&Pasirinktas_laikas_sk=2
// File_Name=cd5_3.pdf&Start_Time=2006.09.11+16%3a06%3a51&Lygis=1+lygis&Pasirinktas_rezimas=Lenktyniauju&Pasirinktas_laikas_sk=4
// File_Name=cd5_3.pdf&Stop_Time=2006.09.11+16%3a06%3a39&Pateikta_uzd_sk=1

// --- registracijos POST pranesimas, eilutes pabaigos gale nera: 

// Text.Vardas=Acrobat&Text.Pavarde=Arkim&toliau=
// Text.Vardas=Mind%c4%97&Text.Pavarde=%c4%8c%c4%97%c5%bea&toliau=

// --- rezultatu POST pranesimas, eilutes pabaigos gale nera: 

// sl=Kaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980
// sl=Kala%7cMala%7c7kl%7c336958436%7c898201907%7c944121410%7c741083137%7c875300865%7c68051204
// sl=%5c%5cu017Dydr%5c%5cu016Bnas%7c%5c%5cu010C%5c%5cu0117%5c%5cu017Ea%7c7kl%7c336958056%7c898201907%7c944121410%7c1797558301%7c1705985%7c67281668
// sl=Acrobat%7cArkim%7c7kl%7c336958036%7c898201907%7c944121410%7c74610818%7c105597761%7c102242053&is=
// sl=Mind%5c%5cu0117%7c%5c%5cu010C%5c%5cu0117%5c%5cu017Ea%7c7kl%7c336958052%7c898201907%7c944121410%7c892215297%7c1705985%7c371336226%7c70359303&is=

// --- tarpiniu rezultatu POST pranesimas, eilutes pabaigos gale nera: 

// *sl=Kaulas%7cMaulas%7c7kl%7c336958036%7c898201907%7c944121410%7c741695590%7c875913318%7c67870980

// --- rezultatai.txt:

// Kaulas|Maulas|7kl|336958036|898201907|944121410|741695590|875913318|67870980
// Mind\\u0117|\\u010C\\u0117\\u017Ea|7kl|336958052|898201907|944121410|892215297|1705985|371336226|70359303

// --- bebras_b.dat:

// Kaulas   Maulas   7kl   314256   944121410   336958036   741695590   898201907   875913318   67870980 0  [dB=,351B,9$)2*=*=5B<9<,=+?<p:=* 0  0  1  0  RRqlniqQ Q50:=)7=+   20 4  2  5  0  K9,(5;9~N=;3~j 2195  9
// Mindë Èëþa  7kl   2435671  898201907   892215297   944121410   1705985  371336226   70359303 336958052   0  [dB=,351B,9$)2*=*=5B<9<,97?<p:=* 0  0  1  0  RRqlniqQ Q50:=)7=+   20 4  2  5  0  K9,(5;9~N=;3~j 2195  10

                     if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     {
                        read = stap_ptr->m_pLicListSocket->m_lContLen;
                        KP_NEWA(post_msg_buf, unsigned char, read + 1);
                     }                     
                     if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        reta=stap_ptr->m_pLicListSocket->ReceiveMsg(post_msg_buf, &read, False, True);
                     if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     {
                        post_msg_buf[read]=Nul;
#ifdef Debug // #if TRUE // 
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs("---------------------\n>>>\n", out_file);
fputs((const char *)post_msg_buf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif              
                     }
                     
                     if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->ScanPostData(post_msg_buf, log_msg);
                     
//                /* reta = */ AppendLogMessage(log_msg, (const unsigned char *)" Message: ");
//                /* reta = */ AppendLogMessage(log_msg, post_msg_buf);

                  /* if(SUCCEEDED(reta)) */ fdf_ptr=lpszEmptyFdf;                     
                  
                  }

// licences or results page request "/"
                  if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_GET_REQUEST)
                  {
                     if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                     if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     {
                        if(page_ptr!=NULL)
                           reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                        page_ptr=NULL;
                     }
                     if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     {
                        if(num_of_lics>0) reta=stap_ptr->FormatLicencesPage(&page_ptr);
                        else if(strlen(rez_fname)>0) reta=stap_ptr->FormatResultsPage(&page_ptr);
                        else reta=KP_E_FILE_NOT_FOUND;
                     }
                  }

                  else
                  {
//                   reta=E_INVALIDARG;
                     reta=KP_E_FILE_NOT_FOUND;

                  } // else // else if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST)
               
               } // if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/")==0)
               
//  Is There Anybody Out There? – answer to broadcast message – recognition of server IP address
// broadcast'as neina per HTTP
#if FALSE
               else if
               (
                  (
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/anybody") == 0)
                  ) &&
                  (stap_ptr->m_pLicListSocket->m_iMsgType == HTTP_GET_REQUEST)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                  }

                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     KP_NEWA(page_ptr, unsigned char, strlen(KPSTLSVR_ANSWER_OK) + 1);
                  }
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) strcpy(page_ptr, KPSTLSVR_ANSWER_OK); 

               } // if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/anybody") == 0)
#endif
               
// licences page request "/licences.htm"               
               else if
               (
                  (
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/clients")==0) || // "/licences"
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/clients.htm")==0) || // "/licences.htm"
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/clients.html")==0) // "/licences.html"
                  ) &&
                  (stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_GET_REQUEST)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                  }
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatLicencesPage(&page_ptr);
               
               } // if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/licences")==0)
               
// results page request "/results.htm"               
               else if
               (
                  (
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/results")==0) ||
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/results.htm")==0) ||
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/results.html")==0)
                  ) &&
                  (stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_GET_REQUEST)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                  }
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatResultsPage(&page_ptr);
               
               } // if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/results")==0)
               
// console page request "/console.htm"               
               else if
               (
                  (
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/console")==0) ||
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/console.htm")==0) ||
                     (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/console.html")==0)
                  ) &&
                  (stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_GET_REQUEST)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                  }
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatConsolePage(&page_ptr);
               
               } // if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/console")==0)
               
// friends page request "/friends.htm"               
               else if
               (
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/friends")==0) ||
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/friends.htm")==0) ||
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/friends.html")==0)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST)
                     {
//                      if(var_list!=NULL)
//                      {
//                         retc=KP_E_SYSTEM_ERROR;
//                         OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
//                      }
                        var_list=NULL;
                        if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        {
                           reta=stap_ptr->m_pLicListSocket->GetPostVars(&var_list, False);
                           if(FAILED(reta)) stap_ptr->OutputErrorMessageLocal(reta, null, True, True);
                        }
                        if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        {
                           if(var_list==NULL)
                              stap_ptr->OutputErrorMessage(KP_E_TRANS_ERR, null, False, __FILE__, __LINE__, 0L);
                           else
                           {
                              reta=stap_ptr->ProcessVars(KPSTLSVR_FRIENDS, var_list);
                              var_list=NULL; // ProcessVars() sutvarko apie tai nepranesdamas
                              
                              if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->SaveConfig();
                           }
                        }
                     }

                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                  }
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatIpListPage(KPSTLSVR_FRIENDS, &page_ptr);
               
               } // if(strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/friends")==0)

// admins page request "/admins.htm"               
               else if
               (
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/admins")==0) ||
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/admins.htm")==0) ||
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/admins.html")==0)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST)
                     {
                        var_list=NULL;
                        if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        {
                           reta=stap_ptr->m_pLicListSocket->GetPostVars(&var_list, False);
                           if(FAILED(reta)) stap_ptr->OutputErrorMessageLocal(reta, null, True, True);
                        }
                        if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        {
                           if(var_list==NULL)
                              stap_ptr->OutputErrorMessage(KP_E_TRANS_ERR, null, False, __FILE__, __LINE__, 0L);
                           else
                           {
                              reta=stap_ptr->ProcessVars(KPSTLSVR_ADMINS, var_list);
                              var_list=NULL; // ProcessVars() sutvarko apie tai nepranesdamas

                              if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->SaveConfig();
                           }
                        }
                     }

                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                     if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatIpListPage(KPSTLSVR_ADMINS, &page_ptr);
                  }
               }   

// admins page request "/links.htm"               
               else if
               (
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/links")==0) ||
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/links.htm")==0) ||
                  (strcmp(stap_ptr->m_pLicListSocket->m_PackedUrl.lpszFileName, "/links.html")==0)
               )
               {
                  if(SUCCEEDED(reta) && SUCCEEDED(retc)) 
                     reta=stap_ptr->CheckClientIP(KPSTLSVR_ADMINS);
            
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                     if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST)
                     {
                        var_list=NULL;
                        if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        {
                           reta=stap_ptr->m_pLicListSocket->GetPostVars(&var_list, False);
                           if(FAILED(reta)) stap_ptr->OutputErrorMessageLocal(reta, null, True, True);
                        }
                        if(SUCCEEDED(reta) && SUCCEEDED(retc))
                        {
                           if(var_list==NULL)
                              stap_ptr->OutputErrorMessage(KP_E_TRANS_ERR, null, False, __FILE__, __LINE__, 0L);
                           else
                           {
                              reta=stap_ptr->ProcessVars(KPSTLSVR_LINKS, var_list);
                              var_list=NULL; // ProcessVars() sutvarko apie tai nepranesdamas

                              if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->SaveConfig();
                           }
                        }
                     }

                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     if(page_ptr!=NULL)
                        reta=stap_ptr->OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
                     page_ptr=NULL;
                     if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta=stap_ptr->FormatIpListPage(KPSTLSVR_LINKS, &page_ptr);
                  }
               }   

               else
               {
//                reta=E_INVALIDARG;
                  reta=KP_E_FILE_NOT_FOUND;
               }

            } // else // if(cmd_ptr!=NULL) // KPST_HTTP_REMOVE
            
         } // else // if(cmd_ptr!=NULL) // KPST_HTTP_REGISTER

         if(stap_ptr->m_pLicListSocket->m_iMsgType==HTTP_POST_REQUEST) /* reta = */ PutLogMessage(log_msg, NULL);

      } // if(SUCCEEDED(retc))

// PutLogMessage_("LicSockListenProc(): %x %s", reta, log_msg);

// reta=E_NOTIMPL;
      if(FAILED(reta) && SUCCEEDED(retc))
      {
         if(reta==KP_E_FILE_NOT_FOUND) // kitiems atvejams protokolo lygio klaidos nereikia - neigiami atsakymai irgi geri
            http_ret_code = KpErrorProc.TranslToHTTP_RetCode(reta);
//       sprintf(out_msg, "%s %d ", KPST_REG_ERROR, http_ret_code);
         strcpy(out_msg, KPST_REG_ERROR);
         retc=KpErrorProc.FormatErrorMessage(reta, msg_buf);
         if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);

         if(SUCCEEDED(retc)) strcat(out_msg, msg_buf);
         reta=S_OK;
      }

      if(SUCCEEDED(retc)) // if(stap_ptr->m_pLicListSocket->m_iReqType==GET_REQUEST)
      {
         if(page_ptr)
         {
            retc=stap_ptr->m_pLicListSocket->SendHttpMsg(page_ptr, True, (unsigned char *)"text/html", http_ret_code); // "text/html; charset=ISO-8859-13"
            if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);
         }
         else if(fdf_ptr)
         {
            retc=stap_ptr->m_pLicListSocket->SendHttpMsg(fdf_ptr, True, (unsigned char *)"application/vnd.fdf", http_ret_code);
            if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);
         }
         else if(strlen(out_msg)>0)
         {
            retc=stap_ptr->m_pLicListSocket->SendHttpMsg(out_msg, True, (unsigned char *)"text/plain", http_ret_code);
            if(FAILED(retc)) stap_ptr->OutputErrorMessageLocal(retc, null, True, True);
         }
      }
#ifdef Debug      
const unsigned char *pnts=page_ptr?page_ptr:(fdf_ptr?fdf_ptr:out_msg);
unsigned char *pntd=strchr(pnts, '\n');
if(pntd) *pntd=Nul;
if(strlen(pnts)>0)
{
sprintf((char *)out_str, "Answer sent: %s", pnts);
KpStLicSvrCons.AddString(out_str);
}
#endif      

//    if((stap_ptr->m_pcListBuf!=NULL) && (stap_ptr->m_lListBufLen>0) && SUCCEEDED(retc))
//    {
//       retc=stap_ptr->m_pLicListSocket->SendMsg(stap_ptr->m_pcListBuf, stap_ptr->m_lListBufLen, True);
//       if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
//    }

      KP_DELETE(var_list);

      KP_DELETEA(page_ptr);

      KP_DELETEA(post_msg_buf);

   } while(SUCCEEDED(retc));
      
return(RET_CODE_MAIN(retc));
}


// -----------------------------------------
#if FALSE
HRESULT KpStLicSvr::CheckLicSockCmd(void)
{
HRESULT retc=S_OK;
                  
   if((m_pLicListSocket==NULL) && SUCCEEDED(retc))
   {
      retc=KP_E_NO_FILE;
      OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
   }
       
KpMsgOut("Before Accept", IDI_ASTERISK, KP_MB_TESTI);
   if(SUCCEEDED(retc))
   {
      retc=m_pLicListSocket->Accept();
      if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
   }
KpMsgOut("After Accept", IDI_ASTERISK, KP_MB_TESTI);

return(retc);
}
#endif


/*--------------------------------------------------- main */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     lpCmdLine,
                     int       /* nCmdShow */)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char ini_fname[KP_MAX_FNAME_LEN+1];
MSG msg;
int retp;
bool endfl=False;
int num_of_lics=0;
int ii;
// unsigned char start_msg[KP_MAX_FNAME_LEN+100];
   
#ifdef Debug // #if TRUE //    
system("mkdir C:\\Temp");
Sleep(1000);
#endif

// ------------------------------- 
// theKpStAppPtr = static_cast<KpStApp *> (&theApp);
   theKpStAppPtr = &theApp;

   if(SUCCEEDED(retc))
   {
      retc=GetIniFname(ini_fname);
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=theApp.Init(hInstance, ini_fname, lpCmdLine);
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
#ifndef Debug
   bServiceFl=(iWindowsVersion>=WinNT);
#endif


// if(SUCCEEDED(retc))
// {
//    retc=theApp.GetOpenResult(); // kazkodel linkeris neranda, turi buti KpCommonApp::GetOpenResult()
//    if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
// }

// !!!! KpMsgOut(ini_fname, IDI_ASTERISK, KP_MB_TESTI);

// FILE *out_file=fopen("e:\\kp\\source\\kpstart\\kpstlsvr.txt", "w");
// fprintf(out_file, "%s\n", ini_fname);
// fclose(out_file);
   
#ifdef Debug
   if(SUCCEEDED(retc))
   {
      retc=WndPreg(&KpStLicSvrCons, TYP_KpConsole, hInstance, (unsigned char *)"kpstlsvr.log", True);
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
#endif   


// ------------------------------
#ifdef Debug
   if(SUCCEEDED(retc))
   {
DWORD ll;
      ll=KP_MAX_FNAME_LEN;
      if(!GetUserName((char *)ini_fname, &ll))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      else
         retc=KpErrorProc.OutputErrorMessage(S_OK, ini_fname, False, __FILE__, __LINE__, 0L);
   }
#endif   


// ------------------------------
   if(SUCCEEDED(retc))
   {
      KP_NEWO(body_table_cell_centered_style_ptr, XmlTagPars((const unsigned char *)"colspan", theApp.m_iNumOfPages));
   }

   if(SUCCEEDED(retc))
   {
      KP_NEWO(body_table_cell_left_style_ptr, XmlTagPars((const unsigned char *)"colspan", theApp.m_iNumOfPages));
   }
// if(SUCCEEDED(retc))
// {
//    retc=body_table_cell_left_style_ptr->AddTextPar((const unsigned char *)"text-align", (const unsigned char *)"left");
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }
// if(SUCCEEDED(retc))
// {
//    retc=body_table_cell_left_style_ptr->AddTextPar((const unsigned char *)"class", (const unsigned char *)"msgi");
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }

// // if(SUCCEEDED(retc))
// // {
// //    retc=table_style.AddTextPar((const unsigned char *)"align", (const unsigned char *)"center");
// //    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// // }
// if(SUCCEEDED(retc))
// {
//    retc=table_style.AddNumPar((const unsigned char *)"cellpadding", 2);
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }
// if(SUCCEEDED(retc))
// {
//    retc=table_style.AddTextPar((const unsigned char *)"style", (const unsigned char *)"margin-left: 20px");
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }

   if(SUCCEEDED(retc))
   {
      retc=friends_form_pars.AddTextPar((const unsigned char *)"name", (const unsigned char *)"IP_adresai");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=friends_form_pars.AddTextPar((const unsigned char *)"method", (const unsigned char *)"post");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=friends_form_pars.AddTextPar((const unsigned char *)"enctype", (const unsigned char *)"multipart/form-data");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
   if(SUCCEEDED(retc))
   {
      retc=admins_form_pars.AddTextPar((const unsigned char *)"name", (const unsigned char *)"IP_adresai");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=admins_form_pars.AddTextPar((const unsigned char *)"method", (const unsigned char *)"post");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=admins_form_pars.AddTextPar((const unsigned char *)"enctype", (const unsigned char *)"multipart/form-data");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
   if(SUCCEEDED(retc))
   {
      retc=links_form_pars.AddTextPar((const unsigned char *)"name", (const unsigned char *)"IP_adresai");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=links_form_pars.AddTextPar((const unsigned char *)"method", (const unsigned char *)"post");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=links_form_pars.AddTextPar((const unsigned char *)"enctype", (const unsigned char *)"multipart/form-data");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
   if(SUCCEEDED(retc))
   {
      retc=ButNum_control_description.AddTextPar((const unsigned char *)"value", (const unsigned char *)"");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=ButNum_control_description.AddTextPar((const unsigned char *)"type", (const unsigned char *)"hidden");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
// <input value="Iðmesti" type="button" class = "button" OnClick="submitas(1)"/>
   if(SUCCEEDED(retc))
   {
      retc=delete_button_description.AddTextPar((const unsigned char *)"type", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=delete_button_description.AddTextPar((const unsigned char *)"class", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=delete_button_description.AddTextPar((const unsigned char *)"OnClick", (const unsigned char *)"submitas(1)");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
// <input value="Iðvalyti" type="button" class = "button" OnClick="submitas(1)"/>
   if(SUCCEEDED(retc))
   {
      retc=clean_button_description.AddTextPar((const unsigned char *)"type", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=clean_button_description.AddTextPar((const unsigned char *)"class", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=clean_button_description.AddTextPar((const unsigned char *)"OnClick", (const unsigned char *)"submitas(1)");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
// <input type="checkbox" name="check" onclick="checkUncheckAll(this);"/>
   if(SUCCEEDED(retc))
   {
      retc=check_all_chbox_description.AddTextPar((const unsigned char *)"name", (const unsigned char *)"check");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
// if(SUCCEEDED(retc))
// {
//    retc=check_all_chbox_description.AddTextPar((const unsigned char *)"OnClick", (const unsigned char *)"checkUncheckAll(this)");
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }
   if(SUCCEEDED(retc))
   {
      retc=check_all_chbox_description.AddTextPar((const unsigned char *)"onclick", (const unsigned char *)"checkUncheckAll(this);");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
// <input value="Pridëti" type="button" class = "button" OnClick="submitas(2)"/>
   if(SUCCEEDED(retc))
   {
      retc=add_button_description.AddTextPar((const unsigned char *)"type", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=add_button_description.AddTextPar((const unsigned char *)"class", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=add_button_description.AddTextPar((const unsigned char *)"OnClick", (const unsigned char *)"submitas(2)");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }

// <input value="Iðsaugoti" type="button" class = "button" OnClick="submitas(3)"/>
   if(SUCCEEDED(retc))
   {
      retc=save_button_description.AddTextPar((const unsigned char *)"type", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=save_button_description.AddTextPar((const unsigned char *)"class", (const unsigned char *)"button");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   if(SUCCEEDED(retc))
   {
      retc=save_button_description.AddTextPar((const unsigned char *)"OnClick", (const unsigned char *)"submitas(3)");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }

// if(SUCCEEDED(retc))
// {
//    retc=checkbox_cell_style.AddTextPar((const unsigned char *)"width", (const unsigned char *)"10%");
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }

// if(SUCCEEDED(retc))
// {
//    retc=footnote_div_style.AddTextPar((const unsigned char *)"style", (const unsigned char *)"margin-left: 20px");
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }

   if(SUCCEEDED(retc))
   {
      retc=error_div_style.AddTextPar((const unsigned char *)"style", (const unsigned char *)"margin-left: 20px; color: red");
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
// ------------------------------
   if(SUCCEEDED(retc)) theApp.m_lParentProcess=GetCurrentThreadId();

// ------------------------------
   if(SUCCEEDED(retc)) 
   {
      retc = theApp.StartBroadcastThread(hInstance);
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }

// --------------------- init server listenning socket
   if(SUCCEEDED(retc))
   {
      retc = theApp.CreateLicSockThread(hInstance);
      if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
   }
   
// --------------------------------
   if(SUCCEEDED(retc)) retc=theApp.RefreshLicDisplay();
   
// --------------------------------
// if(SUCCEEDED(retc))
// {
//    retc=theApp.GetIniProdName(start_msg);
//    if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
// }
// if(SUCCEEDED(retc))
// {
//    strcat(start_msg, " licencijø serveris paleistas");
//    KpMsgOut(start_msg, IDI_ASTERISK, KP_MB_GERAI);
// }

#if FALSE
static unsigned char str_buf[2000];
sprintf((char *)str_buf, ">>>> %d %d %s<<<", KPSTLSVR_MSG_TAB_CLIENTS_IX, iMsgLangOff, lpszaKpStlSvrMessages[KPSTLSVR_MSG_TAB_CLIENTS_IX][iMsgLangOff]);
theApp.AddConsMsg(str_buf);
#endif

// --------------------------------
static unsigned char str_buf[2000 + KP_MAX_FNAME_LEN + 1];
static unsigned char log_fname[KP_MAX_FNAME_LEN + 1];
   if(SUCCEEDED(retc)) retc = GetLogFileName(log_fname);
   if(SUCCEEDED(retc))
   { 
      sprintf((char *)str_buf, (const char *)KPSTLSVR_MSG_LOG_PROMPT, log_fname);
      theApp.AddConsMsg(str_buf);
   }

// --------------------------------
   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
      {
         retc=KP_E_SYSTEM_ERROR;
         theApp.OutputErrorMessage(retc, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp=LOWORD(msg.wParam);
      }
      
      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
         endfl=True;
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
            break;
         case IDCANCEL:
//          if(msg.hwnd==m_hDialogWindow) 
               endfl=True;
            break;
         case KPST_ID_SAVE_STATUS:
            retc=theApp.SaveLicences(False);
            if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
            break;
         } // switch(retp)
         break;
      
      case WM_TIMER:
         if(retp==theApp.m_iLicManagTimer) 
         {
// .ini refreshinimas
// negalima - luzta kitas threadas
//          retc=theApp.LoadIni();
//          if(FAILED(retc)) OutputErrorMessageLocal(retc, null, True, True);
         
// displejaus refreshinimas         
            if(SUCCEEDED(retc))
            {
               retc=theApp.GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
               if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
            }
            
            if(num_of_lics && SUCCEEDED(retc))
            {
               if((theApp.m_pLicArray==NULL) && SUCCEEDED(retc))
               {
                  retc=KP_E_SYSTEM_ERROR;
                  theApp.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
               }

               for(ii=0; (ii<num_of_lics) && SUCCEEDED(retc); ii++)
               {
                  if(theApp.m_pLicArray[ii].m_iLicState!=KpstLicFree)
                  {
                     theApp.m_pLicArray[ii].m_iSecondsToKill-=KPST_LIC_MANAG_TIMEOUT/KP_MILISECS_PER_SEC;
                     if(theApp.m_pLicArray[ii].m_iSecondsToKill<=0)
                     {
                        theApp.m_pLicArray[ii].m_iSecondsToKill=0;
                        theApp.m_pLicArray[ii].m_iLicState=KpstLicFree;
                     }
                     else if(theApp.m_pLicArray[ii].m_iSecondsToKill<=KPST_INI_SECS_TO_KILL-KP_SECS_PER_MIN)
                        theApp.m_pLicArray[ii].m_iLicState=KpstLicLost;
                  }
               }
         
               if(SUCCEEDED(retc)) retc=theApp.RefreshLicDisplay();

// licenciju issaugojimas
               if(SUCCEEDED(retc))
               {
                  retc=theApp.SaveLicences(False);
                  if(FAILED(retc)) theApp.OutputErrorMessageLocal(retc, null, True, True);
               }
            }
         }
         break;                                   
      
      }  // if(SUCCEEDED(retc)) switch(msg.message)
   
   } while((!endfl) && SUCCEEDED(retc));

   PutLogMessage((const unsigned char *)(SUCCEEDED(retc)?KPSTLSVR_MSG_SERVER_STOPPED:KPSTLSVR_MSG_SERVER_ABORTED), NULL);

   /* if(SUCCEEDED(retc)) */ retc0=theApp.CloseStApp(retc, KP_My_Documents);  
   if(SUCCEEDED(retc)) retc=retc0;
   else theApp.OutputErrorMessageLocal(retc, null, True, True);

// KpMsgOut("Pabaiga", IDI_ASTERISK, KP_MB_TESTI);

return(RET_CODE_WIN(retc));
}

