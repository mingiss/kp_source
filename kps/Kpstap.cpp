// ---------------------------
// kpstap.cpp
// common application for program starters
//
// 2012.10.11  mp  terminuotø lic. tikrinimas serveryje atskiram threade, kad WinXP nekabëtø prie atjungto interneto
// 2012.10.26  mp  lic. termino dinaminis pailginimas kreipinio á serverá bûdu; iki ðiol galëjo tik patrumpëti
// 2012.11.09  mp  PlayPrologue() iðkviesdavo KpSleep(0) – po pastarosios pataisymo pradëjo lûþti
// 2013-02-06  mp  daugiadokumentinio Adobe Readerio lango maksimizavimas
// 2013-03-03  mp  m_bMDImaximized – sending Ctrl+Shift+L to Adobe Reader flag – only one time
//

// -----------------------------------------
#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <ctype.h>
#include <stdio.h>
#include <string>
#include <iostream>
#if Compiler != Watcom
#include <sstream>
#endif
#include <fstream>
#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <winuser.h> // buvo kaþkodël uþkomentuotas, reikalingas Watcom 1.8
#include <windowsx.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <richedit.h>
#include <Richole.h>
#include <psapi.h>

#ifdef IBSH_RES_MODE_XGECKO
#if CompilerGr==Mingw
#include "IInputStream.hh"
#include "IString.hh"
#include "XApplication.hh"
#include "XGecko.hh"
#include "XGeckoDOMEvent.hh"
#include "XGeckoInit.hh"
#endif
#endif

#if (Compiler != Watcom) || (__WATCOMC__ > 1201)
using namespace std;
#endif

#include "kpstdlib.h"
#include "kperrno.h"
#include "kpmsg.h"
#include "kpmsg_en.h"
#include "kpmsg_lt.h"
#include "kpmsg_pl_1250.h"
#include "kpmsg_pl_1257.h"
#include "kpmsg_ru.h"
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpctype.h"
#include "kpctypp.h"
#include "kpstdlib.h"
#include "kpsort.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "res_com.h"
#include "tvxml.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "kpwindow.h"
#include "kpmsg.h"
#include "kperr.h"
#include "kpsock.h"
#include "kphp11y.h"
#include "kphp11i.h"
#include "kphp11t.h"
#include "kphp11m.h"
#include "kpcapp.h"
#include "tvmain.h"
#include "tvrtf.h"
#include "tvrtfo.h"
#include "tvtex.h"
#include "tvxml.h"
#include "xmlp.h"
#include "xmlh.h"
#include "xmlf.h"
#include "xml8.h"
#include "xmlu.h"
#include "xmlo1.h"
#include "xmlt.h"
#include "xmlis.h"
#include "xmli.h"
#include "KpFileSys.h"
#include "KpPubDlg.h"
#include "xmln.h"
#include "kpstap.h"
#include "kpstlsvr.h"
#include "kpstmsg.h"
#include "kpstmsg_en.h"
#include "kpstmsg_lt.h"
#include "kpstmsg_pl_1250.h"
#include "kpstmsg_pl_1257.h"
#include "kpstmsg_ru.h"
#include "kpstedi.h"
#include "kpsttre.h"
#include "kpsttrg.h"
#include "kpstapa.h"
#include "kpstaps.h"

#ifndef STAND_ALONE
#include "kpsttrg.h"
#endif

#if (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
// #error Envir!=MSWin32 && (Envir!=MSWin32Mfc)
#if (Envir!=MSWin32Con)
#error (Envir!=MSWin32) && (Envir!=MSWin32Mfc) && (Envir!=MSWin32Con)
#endif
#endif

#ifdef TUX_LIB
#include "tux_dbg.hh"
#endif

// -----------------------------------------
KpStApp *theKpStAppPtr = NULL;

const unsigned char *lpszaKpstClipCmds[KpstClipCmdCnt+1] =
{
   (const unsigned char *)"CW",
   (const unsigned char *)"PM",

   NULL
};


// -----------------------------------------
// XXX !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~XXX
// XXX+%21%22%23%24%25%26%27%28%29*%2b%2c-.%2f%3a%3b%3c%3d%3e%3f%40%5b%5c%5d%5e_%60%7b%7c%7d%7eXXX

unsigned char lpszPostSpChars[] = "!\"#$%&\'()+,/:;<=>?@[\\]^`{|}~";

// -----------------------------------------
// #ifdef KPST_MOVE_TO_KPHP11
KpStIniData IniDataBuf;
// #endif

// ------------------------------------ kpstart programø praneðimai
const unsigned char *lpszaKpStMessages[NumOfKpStMessages_18][KpNumOfLangs_2] =
{
KPST_MSG_PROD_REG_EN,               KPST_MSG_PROD_REG_LT,               KPST_MSG_PROD_REG_PL_1250,             KPST_MSG_PROD_REG_PL_1257,             KPST_MSG_PROD_REG_RU,               KPST_MSG_PROD_REG_RU,               // "Programos registracija"
KPST_MSG_UNREG_EN,                  KPST_MSG_UNREG_LT,                  KPST_MSG_UNREG_PL_1250,                KPST_MSG_UNREG_PL_1257,                KPST_MSG_UNREG_RU,                  KPST_MSG_UNREG_RU,                  // "Registracijos naikinimas"
KPST_MSG_LIC_EN,                    KPST_MSG_LIC_LT,                    KPST_MSG_LIC_PL_1250,                  KPST_MSG_LIC_PL_1257,                  KPST_MSG_LIC_RU,                    KPST_MSG_LIC_EN,                    // "Licencija"
KPST_MSG_REG_INFO_EN,               KPST_MSG_REG_INFO_LT,               KPST_MSG_REG_INFO_PL_1250,             KPST_MSG_REG_INFO_PL_1257,             KPST_MSG_REG_INFO_RU,               KPST_MSG_REG_INFO_RU,               // "Kad programa veiktø, jà reikia uþregistruoti."
KPST_MSG_IVESK_LIC_EN,              KPST_MSG_IVESK_LIC_LT,              KPST_MSG_IVESK_LIC_PL_1250,            KPST_MSG_IVESK_LIC_PL_1257,            KPST_MSG_IVESK_LIC_RU,              KPST_MSG_IVESK_LIC_RU,              // "Áveskite licencijos kodà, kurá gavote ásigydami produktà."
KPST_MSG_IVESK_LIC_1_EN,            KPST_MSG_IVESK_LIC_1_LT,            KPST_MSG_IVESK_LIC_1_PL_1250,          KPST_MSG_IVESK_LIC_1_PL_1257,          KPST_MSG_IVESK_LIC_1_RU,            KPST_MSG_IVESK_LIC_1_RU,            // "Visà kodà galima kopijuoti á pirmà langelá."
KPST_MSG_REG_CARD_EN,               KPST_MSG_REG_CARD_LT,               KPST_MSG_REG_CARD_PL_1250,             KPST_MSG_REG_CARD_PL_1257,             KPST_MSG_REG_CARD_RU,               KPST_MSG_REG_CARD_RU,               // "Já rasite registracijos kortelëje"
KPST_MSG_LIC_KOD_EN,                KPST_MSG_LIC_KOD_LT,                KPST_MSG_LIC_KOD_PL_1250,              KPST_MSG_LIC_KOD_PL_1257,              KPST_MSG_LIC_KOD_RU,                KPST_MSG_LIC_KOD_RU,                // "Licencijos kodas:"
KPST_MSG_BLOGAS_LIC_KODAS_EN,       KPST_MSG_BLOGAS_LIC_KODAS_LT,       KPST_MSG_BLOGAS_LIC_KODAS_PL_1250,     KPST_MSG_BLOGAS_LIC_KODAS_PL_1257,     KPST_MSG_BLOGAS_LIC_KODAS_RU,       KPST_MSG_BLOGAS_LIC_KODAS_RU,       // "Neteisingai ávestas licencijos kodas"
KPST_MSG_CHECK_CONN_EN,             KPST_MSG_CHECK_CONN_LT,             KPST_MSG_CHECK_CONN_PL_1250,           KPST_MSG_CHECK_CONN_PL_1257,           KPST_MSG_CHECK_CONN_RU,             KPST_MSG_CHECK_CONN_RU,             // "Patikrinkite, ar kompiuteris prijungtas prie interneto"
KPST_MSG_CHECK_CONN_LOC_EN,         KPST_MSG_CHECK_CONN_LOC_LT,         KPST_MSG_CHECK_CONN_LOC_PL_1250,       KPST_MSG_CHECK_CONN_LOC_PL_1257,       KPST_MSG_CHECK_CONN_LOC_RU,         KPST_MSG_CHECK_CONN_LOC_RU,         // "Patikrinkite, ar kompiuteris prijungtas prie tinklo"
KPST_MSG_REG_SUCC_EN,               KPST_MSG_REG_SUCC_LT,               KPST_MSG_REG_SUCC_PL_1250,             KPST_MSG_REG_SUCC_PL_1257,             KPST_MSG_REG_SUCC_RU,               KPST_MSG_REG_SUCC_RU,               // "Licencija uþregistruota sëkmingai"
KPST_MSG_ALLREADY_REG_EN,           KPST_MSG_ALLREADY_REG_LT,           KPST_MSG_ALLREADY_REG_PL_1250,         KPST_MSG_ALLREADY_REG_PL_1257,         KPST_MSG_ALLREADY_REG_RU,           KPST_MSG_ALLREADY_REG_RU,           // "Licencija jau uþregistruota"
KPST_MSG_REG_UNSUC_EN,              KPST_MSG_REG_UNSUC_LT,              KPST_MSG_REG_UNSUC_PL_1250,            KPST_MSG_REG_UNSUC_PL_1257,            KPST_MSG_REG_UNSUC_RU,              KPST_MSG_REG_UNSUC_RU,              // "Internetu licencijos uþregistruoti nepavyko."
KPST_MSG_REG_UNSUC_0_EN,            KPST_MSG_REG_UNSUC_0_LT,            KPST_MSG_REG_UNSUC_0_PL_1250,          KPST_MSG_REG_UNSUC_0_PL_1257,          KPST_MSG_REG_UNSUC_0_RU,            KPST_MSG_REG_UNSUC_0_RU,            // "Pabandykite narðykle atverti þemiau"
KPST_MSG_REG_UNSUC_1_EN,            KPST_MSG_REG_UNSUC_1_LT,            KPST_MSG_REG_UNSUC_1_PL_1250,          KPST_MSG_REG_UNSUC_1_PL_1257,          KPST_MSG_REG_UNSUC_1_RU,            KPST_MSG_REG_UNSUC_1_RU,            // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius."
KPST_MSG_REG_UNSUC_LOC_EN,          KPST_MSG_REG_UNSUC_LOC_LT,          KPST_MSG_REG_UNSUC_LOC_PL_1250,        KPST_MSG_REG_UNSUC_LOC_PL_1257,        KPST_MSG_REG_UNSUC_LOC_RU,          KPST_MSG_REG_UNSUC_LOC_RU,          // "Uþsiregistruoti nepavyko."
KPST_MSG_DIEG_KOD_EN,               KPST_MSG_DIEG_KOD_LT,               KPST_MSG_DIEG_KOD_PL_1250,             KPST_MSG_DIEG_KOD_PL_1257,             KPST_MSG_DIEG_KOD_RU,               KPST_MSG_DIEG_KOD_RU,               // "Diegimo kodas:"

KPST_MSG_UNREG_INFO_EN,             KPST_MSG_UNREG_INFO_LT,             KPST_MSG_UNREG_INFO_PL_1250,           KPST_MSG_UNREG_INFO_PL_1257,           KPST_MSG_UNREG_INFO_RU,             KPST_MSG_UNREG_INFO_RU,             // "Licencijos registracija naikinama prieð programà perkeliant á kità kompiuterá."
KPST_MSG_UNREG_IVESK_LIC_EN,        KPST_MSG_UNREG_IVESK_LIC_LT,        KPST_MSG_UNREG_IVESK_LIC_PL_1250,      KPST_MSG_UNREG_IVESK_LIC_PL_1257,      KPST_MSG_UNREG_IVESK_LIC_RU,        KPST_MSG_UNREG_IVESK_LIC_RU,        // KPST_MSG_IVESK_LIC

KPST_MSG_REG_PERSPEJ_EN,            KPST_MSG_REG_PERSPEJ_LT,            KPST_MSG_REG_PERSPEJ_PL_1250,          KPST_MSG_REG_PERSPEJ_PL_1257,          KPST_MSG_REG_PERSPEJ_RU,            KPST_MSG_REG_PERSPEJ_RU,            // "Uþregistruota programa veiks tik ðiame kompiuteryje!"

KPST_MSG_BUT_REG_EN,                KPST_MSG_BUT_REG_LT,                KPST_MSG_BUT_REG_PL_1250,              KPST_MSG_BUT_REG_PL_1257,              KPST_MSG_BUT_REG_RU,                KPST_MSG_BUT_REG_RU,                // "Kaip registruosite:"
KPST_MSG_BUT_UNREG_EN,              KPST_MSG_BUT_UNREG_LT,              KPST_MSG_BUT_UNREG_PL_1250,            KPST_MSG_BUT_UNREG_PL_1257,            KPST_MSG_BUT_UNREG_RU,              KPST_MSG_BUT_UNREG_RU,              // "Kaip naikinsite:"

KPST_MSG_INTERNETU_EN,              KPST_MSG_INTERNETU_LT,              KPST_MSG_INTERNETU_PL_1250,            KPST_MSG_INTERNETU_PL_1257,            KPST_MSG_INTERNETU_RU,              KPST_MSG_INTERNETU_EN,              // "Internetu"
KPST_MSG_TELEFONU_EN,               KPST_MSG_TELEFONU_LT,               KPST_MSG_TELEFONU_PL_1250,             KPST_MSG_TELEFONU_PL_1257,             KPST_MSG_TELEFONU_RU,               KPST_MSG_TELEFONU_EN,               // "Telefonu"
KPST_MSG_CANCEL_REG_EN,             KPST_MSG_CANCEL_REG_LT,             KPST_MSG_CANCEL_REG_PL_1250,           KPST_MSG_CANCEL_REG_PL_1257,           KPST_MSG_CANCEL_REG_RU,             KPST_MSG_CANCEL_REG_EN,             // "Atðaukti"
KPST_MSG_CANCEL_UNREG_EN,           KPST_MSG_CANCEL_UNREG_LT,           KPST_MSG_CANCEL_UNREG_PL_1250,         KPST_MSG_CANCEL_UNREG_PL_1257,         KPST_MSG_CANCEL_UNREG_RU,           KPST_MSG_CANCEL_UNREG_EN,           // "Nenaikinti"

KPST_MSG_SIUSK_PASTU_EN,            KPST_MSG_SIUSK_PASTU_LT,            KPST_MSG_SIUSK_PASTU_PL_1250,          KPST_MSG_SIUSK_PASTU_PL_1257,          KPST_MSG_SIUSK_PASTU_RU,            KPST_MSG_SIUSK_PASTU_RU,            // "Diegimo kodà galite iðsiøsti elektroniniu paðtu, adresu tech@tev.lt arba"
KPST_MSG_DARBO_LAIKAS_EN,           KPST_MSG_DARBO_LAIKAS_LT,           KPST_MSG_DARBO_LAIKAS_PL_1250,         KPST_MSG_DARBO_LAIKAS_PL_1257,         KPST_MSG_DARBO_LAIKAS_RU,           KPST_MSG_DARBO_LAIKAS_RU,           // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318"
KPST_MSG_DIKT_TELEF_EN,             KPST_MSG_DIKT_TELEF_LT,             KPST_MSG_DIKT_TELEF_PL_1250,           KPST_MSG_DIKT_TELEF_PL_1257,           KPST_MSG_DIKT_TELEF_RU,             KPST_MSG_DIKT_TELEF_RU,             // "padiktuoti operatoriui."

KPST_MSG_IVESK_RAKTA_EN,            KPST_MSG_IVESK_RAKTA_LT,            KPST_MSG_IVESK_RAKTA_PL_1250,          KPST_MSG_IVESK_RAKTA_PL_1257,          KPST_MSG_IVESK_RAKTA_RU,            KPST_MSG_IVESK_RAKTA_RU,            // "Áveskite gautà atsakymà – diegimo raktà."
KPST_MSG_IVESK_RAKTA_1_EN,          KPST_MSG_IVESK_RAKTA_1_LT,          KPST_MSG_IVESK_RAKTA_1_PL_1250,        KPST_MSG_IVESK_RAKTA_1_PL_1257,        KPST_MSG_IVESK_RAKTA_1_RU,          KPST_MSG_IVESK_RAKTA_1_RU,          // "Visà raktà galima kopijuoti á pirmà langelá."
KPST_MSG_DIEG_RAKTAS_EN,            KPST_MSG_DIEG_RAKTAS_LT,            KPST_MSG_DIEG_RAKTAS_PL_1250,          KPST_MSG_DIEG_RAKTAS_PL_1257,          KPST_MSG_DIEG_RAKTAS_RU,            KPST_MSG_DIEG_RAKTAS_RU,            // "Diegimo raktas:"
KPST_MSG_DIEG_RAKTAS_1_EN,          KPST_MSG_DIEG_RAKTAS_1_LT,          KPST_MSG_DIEG_RAKTAS_1_PL_1250,        KPST_MSG_DIEG_RAKTAS_1_PL_1257,        KPST_MSG_DIEG_RAKTAS_1_RU,          KPST_MSG_DIEG_RAKTAS_1_EN,          // "Diegimo raktas"
KPST_MSG_BLOGAS_DIEG_RAKTAS_EN,     KPST_MSG_BLOGAS_DIEG_RAKTAS_LT,     KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1250,   KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1257,   KPST_MSG_BLOGAS_DIEG_RAKTAS_RU,     KPST_MSG_BLOGAS_DIEG_RAKTAS_RU,     // "Neteisingai ávestas diegimo raktas"
KPST_MSG_START_FROM_CD_EN,          KPST_MSG_START_FROM_CD_LT,          KPST_MSG_START_FROM_CD_PL_1250,        KPST_MSG_START_FROM_CD_PL_1257,        KPST_MSG_START_FROM_CD_RU,          KPST_MSG_START_FROM_CD_RU,          // "Programà paleiskite ið kompaktinës plokðtelës"
KPST_MSG_BAD_CD_EN,                 KPST_MSG_BAD_CD_LT,                 KPST_MSG_BAD_CD_PL_1250,               KPST_MSG_BAD_CD_PL_1257,               KPST_MSG_BAD_CD_RU,                 KPST_MSG_BAD_CD_RU,                 // "Bloga kompaktinë plokðtelë"

KPST_MSG_REZ_NESUFORM_EN,           KPST_MSG_REZ_NESUFORM_LT,           KPST_MSG_REZ_NESUFORM_PL_1250,         KPST_MSG_REZ_NESUFORM_PL_1257,         KPST_MSG_REZ_NESUFORM_RU,           KPST_MSG_REZ_NESUFORM_RU,           // "Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt"
KPST_MSG_REZ_NFOUND_1_EN,           KPST_MSG_REZ_NFOUND_1_LT,           KPST_MSG_REZ_NFOUND_1_PL_1250,         KPST_MSG_REZ_NFOUND_1_PL_1257,         KPST_MSG_REZ_NFOUND_1_RU,           KPST_MSG_REZ_NFOUND_1_RU,           // "Rezultatø rasti nepavyko.\n Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt "
KPST_MSG_REZ_NFOUND_2_EN,           KPST_MSG_REZ_NFOUND_2_LT,           KPST_MSG_REZ_NFOUND_2_PL_1250,         KPST_MSG_REZ_NFOUND_2_PL_1257,         KPST_MSG_REZ_NFOUND_2_RU,           KPST_MSG_REZ_NFOUND_2_RU,           // "Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator."
KPST_MSG_REZ_SUCCESS_EN,            KPST_MSG_REZ_SUCCESS_LT,            KPST_MSG_REZ_SUCCESS_PL_1250,          KPST_MSG_REZ_SUCCESS_PL_1257,          KPST_MSG_REZ_SUCCESS_RU,            KPST_MSG_REZ_SUCCESS_RU,            // ". Rezultatai sëkmingai perkelti á "

KPST_MSG_REG_NOT_ADMIN_EN,          KPST_MSG_REG_NOT_ADMIN_LT,          KPST_MSG_REG_NOT_ADMIN_PL_1250,        KPST_MSG_REG_NOT_ADMIN_PL_1257,        KPST_MSG_REG_NOT_ADMIN_RU,          KPST_MSG_REG_NOT_ADMIN_RU,          // "Norint uþregistruoti licencijà, reikia sistemos\n administratoriaus teisiø"
KPST_MSG_UNREG_NOT_ADMIN_EN,        KPST_MSG_UNREG_NOT_ADMIN_LT,        KPST_MSG_UNREG_NOT_ADMIN_PL_1250,      KPST_MSG_UNREG_NOT_ADMIN_PL_1257,      KPST_MSG_UNREG_NOT_ADMIN_RU,        KPST_MSG_UNREG_NOT_ADMIN_RU,        // "Norëdami panaikinti produkto diegimà,\n uþsiregistruokite sistemos administratoriumi"
KPST_MSG_NOT_REG_EN,                KPST_MSG_NOT_REG_LT,                KPST_MSG_NOT_REG_PL_1250,              KPST_MSG_NOT_REG_PL_1257,              KPST_MSG_NOT_REG_RU,                KPST_MSG_NOT_REG_RU,                // "Produkto licencija dar neuþregistruota"
KPST_MSG_INVALID_REG_EN,            KPST_MSG_INVALID_REG_LT,            KPST_MSG_INVALID_REG_PL_1250,          KPST_MSG_INVALID_REG_PL_1257,          KPST_MSG_INVALID_REG_RU,            KPST_MSG_INVALID_REG_RU,            // "Papildymo ir pagrindinio produkto licencijø kodai nesutampa. Pakartokite produkto diegimà."

KPST_MSG_UNREG_KOD_1_EN,            KPST_MSG_UNREG_KOD_1_LT,            KPST_MSG_UNREG_KOD_1_PL_1250,          KPST_MSG_UNREG_KOD_1_PL_1257,          KPST_MSG_UNREG_KOD_1_RU,            KPST_MSG_UNREG_KOD_1_EN,            // "Iðmetimo kodas"
KPST_MSG_UNREG_KOD_EN,              KPST_MSG_UNREG_KOD_LT,              KPST_MSG_UNREG_KOD_PL_1250,            KPST_MSG_UNREG_KOD_PL_1257,            KPST_MSG_UNREG_KOD_RU,              KPST_MSG_UNREG_KOD_RU,              // "Licencijos iðmetimo kodas:              \n"
KPST_MSG_ALLREADY_REMOVED_EN,       KPST_MSG_ALLREADY_REMOVED_LT,       KPST_MSG_ALLREADY_REMOVED_PL_1250,     KPST_MSG_ALLREADY_REMOVED_PL_1257,     KPST_MSG_ALLREADY_REMOVED_RU,       KPST_MSG_ALLREADY_REMOVED_RU,       // "Produktas jau iðmestas"
KPST_MSG_UNREG_SUCC_EN,             KPST_MSG_UNREG_SUCC_LT,             KPST_MSG_UNREG_SUCC_PL_1250,           KPST_MSG_UNREG_SUCC_PL_1257,           KPST_MSG_UNREG_SUCC_RU,             KPST_MSG_UNREG_SUCC_RU,             // "Licencijos diegimas panaikintas sëkmingai"
KPST_MSG_UNREG_UNSUCC_EN,           KPST_MSG_UNREG_UNSUCC_LT,           KPST_MSG_UNREG_UNSUCC_PL_1250,         KPST_MSG_UNREG_UNSUCC_PL_1257,         KPST_MSG_UNREG_UNSUCC_RU,           KPST_MSG_UNREG_UNSUCC_RU,           // "Internetu registracijos panaikinti nepavyko."
KPST_MSG_UNREG_UNSUCC_1_EN,         KPST_MSG_UNREG_UNSUCC_1_LT,         KPST_MSG_UNREG_UNSUCC_1_PL_1250,       KPST_MSG_UNREG_UNSUCC_1_PL_1257,       KPST_MSG_UNREG_UNSUCC_1_RU,         KPST_MSG_UNREG_UNSUCC_1_RU,         // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

KPST_MSG_REG_NOT_YET_EN,            KPST_MSG_REG_NOT_YET_LT,            KPST_MSG_REG_NOT_YET_PL_1250,          KPST_MSG_REG_NOT_YET_PL_1257,          KPST_MSG_REG_NOT_YET_RU,            KPST_MSG_REG_NOT_YET_RU_0,          // "Programa dar neuþregistruota. Registracijos procedûrà turësite pakartoti paleidimo meniu komanda „Registracija”."

KPST_MSG_INI_NOT_ADMIN_EN,          KPST_MSG_INI_NOT_ADMIN_LT,          KPST_MSG_INI_NOT_ADMIN_PL_1250,        KPST_MSG_INI_NOT_ADMIN_PL_1257,        KPST_MSG_INI_NOT_ADMIN_RU,          KPST_MSG_INI_NOT_ADMIN_RU,          // "Sistemos resursai nepasiekiami, uþsiregistruokite administratoriumi"

KPST_MSG_UNREG_PASTU_EN,            KPST_MSG_UNREG_PASTU_LT,            KPST_MSG_UNREG_PASTU_PL_1250,          KPST_MSG_UNREG_PASTU_PL_1257,          KPST_MSG_UNREG_PASTU_RU,            KPST_MSG_UNREG_PASTU_RU,            // "Iðmetimo kodà iðsiøskite elektroniniu paðtu, adresu tech@tev.lt arba"
KPST_MSG_UNREG_DARBO_LAIKAS_EN,     KPST_MSG_UNREG_DARBO_LAIKAS_LT,     KPST_MSG_UNREG_DARBO_LAIKAS_PL_1250,   KPST_MSG_UNREG_DARBO_LAIKAS_PL_1257,   KPST_MSG_UNREG_DARBO_LAIKAS_RU,     KPST_MSG_UNREG_DARBO_LAIKAS_RU,     // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318"
KPST_MSG_UNREG_DIKT_TELEF_EN,       KPST_MSG_UNREG_DIKT_TELEF_LT,       KPST_MSG_UNREG_DIKT_TELEF_PL_1250,     KPST_MSG_UNREG_DIKT_TELEF_PL_1257,     KPST_MSG_UNREG_DIKT_TELEF_RU,       KPST_MSG_UNREG_DIKT_TELEF_RU,       // "padiktuokite operatoriui."

KPST_MSG_UNREG_NEGALESIT_EN,        KPST_MSG_UNREG_NEGALESIT_LT,        KPST_MSG_UNREG_NEGALESIT_PL_1250,      KPST_MSG_UNREG_NEGALESIT_PL_1257,      KPST_MSG_UNREG_NEGALESIT_RU,        KPST_MSG_UNREG_NEGALESIT_RU,        // "To nepadaræ, kitame kompiuteryje programos uþregistruoti negalësite!"

KPST_MSG_INSERT_FLOPPY_EN,          KPST_MSG_INSERT_FLOPPY_LT,          KPST_MSG_INSERT_FLOPPY_PL_1250,        KPST_MSG_INSERT_FLOPPY_PL_1257,        KPST_MSG_INSERT_FLOPPY_RU,          KPST_MSG_INSERT_FLOPPY_RU,          // "Ádëkite diskelá"
KPST_MSG_UNABLE_OPEN_REZFILE_EN,    KPST_MSG_UNABLE_OPEN_REZFILE_LT,    KPST_MSG_UNABLE_OPEN_REZFILE_PL_1250,  KPST_MSG_UNABLE_OPEN_REZFILE_PL_1257,  KPST_MSG_UNABLE_OPEN_REZFILE_RU,    KPST_MSG_UNABLE_OPEN_REZFILE_RU,    // "Negaliu atverti rezultatø failo."
KPST_MSG_UNABLE_WRITE_REZFILE_EN,   KPST_MSG_UNABLE_WRITE_REZFILE_LT,   KPST_MSG_UNABLE_WRITE_REZFILE_PL_1250, KPST_MSG_UNABLE_WRITE_REZFILE_PL_1257, KPST_MSG_UNABLE_WRITE_REZFILE_RU,   KPST_MSG_UNABLE_WRITE_REZFILE_RU,   // "Negaliu áraðyti á rezultatø failà."
KPST_MSG_UNABLE_CLOSE_REZFILE_EN,   KPST_MSG_UNABLE_CLOSE_REZFILE_LT,   KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1250, KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1257, KPST_MSG_UNABLE_CLOSE_REZFILE_RU,   KPST_MSG_UNABLE_CLOSE_REZFILE_RU,   // "Negaliu uþdaryti rezultatø failo."
KP_MSG_UNABLE_READ_WRITTEN_EN,      KP_MSG_UNABLE_READ_WRITTEN_LT,      KP_MSG_UNABLE_READ_WRITTEN_PL_1250,    KP_MSG_UNABLE_READ_WRITTEN_PL_1257,    KP_MSG_UNABLE_READ_WRITTEN_RU,      KP_MSG_UNABLE_READ_WRITTEN_RU,      // "Negaliu perskaityti áraðyto failo."
KPST_MSG_COULDNT_WRITE_EN,          KPST_MSG_COULDNT_WRITE_LT,          KPST_MSG_COULDNT_WRITE_PL_1250,        KPST_MSG_COULDNT_WRITE_PL_1257,        KPST_MSG_COULDNT_WRITE_RU,          KPST_MSG_COULDNT_WRITE_RU,          // "Duomenys neásiraðo."
KPST_MSG_REFUSE_RESULTS_EN,         KPST_MSG_REFUSE_RESULTS_LT,         KPST_MSG_REFUSE_RESULTS_PL_1250,       KPST_MSG_REFUSE_RESULTS_PL_1257,       KPST_MSG_REFUSE_RESULTS_RU,         KPST_MSG_REFUSE_RESULTS_RU,         // "Ar tikrai norite atsisakyti rezultatø?"
KPST_MSG_TEST_SUCC_EN,              KPST_MSG_TEST_SUCC_LT,              KPST_MSG_TEST_SUCC_PL_1250,            KPST_MSG_TEST_SUCC_PL_1257,            KPST_MSG_TEST_SUCC_RU,              KPST_MSG_TEST_SUCC_RU,              // "Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     "

KPST_MSG_TEST_UNSUC_EN,             KPST_MSG_TEST_UNSUC_LT,             KPST_MSG_TEST_UNSUC_PL_1250,           KPST_MSG_TEST_UNSUC_PL_1257,           KPST_MSG_TEST_UNSUC_RU,             KPST_MSG_TEST_UNSUC_RU,             // "Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt"

KPST_MSG_INSERT_FLASH_EN,           KPST_MSG_INSERT_FLASH_LT,           KPST_MSG_INSERT_FLASH_PL_1250,         KPST_MSG_INSERT_FLASH_PL_1257,         KPST_MSG_INSERT_FLASH_RU,           KPST_MSG_INSERT_FLASH_RU,           // "Ákiðkite atmintukà su \""
KPST_MSG_INSERT_FLASH_1_EN,         KPST_MSG_INSERT_FLASH_1_LT,         KPST_MSG_INSERT_FLASH_1_PL_1250,       KPST_MSG_INSERT_FLASH_1_PL_1257,       KPST_MSG_INSERT_FLASH_1_RU,         KPST_MSG_INSERT_FLASH_1_RU,         // "\""

KPST_MSG_ENTER_PWD_EN,              KPST_MSG_ENTER_PWD_LT,              KPST_MSG_ENTER_PWD_PL_1250,            KPST_MSG_ENTER_PWD_PL_1257,            KPST_MSG_ENTER_PWD_RU,              KPST_MSG_ENTER_PWD_RU,              // "Áveskite slaptaþodá:"
KPST_MSG_BAD_PWD_EN,                KPST_MSG_BAD_PWD_LT,                KPST_MSG_BAD_PWD_PL_1250,              KPST_MSG_BAD_PWD_PL_1257,              KPST_MSG_BAD_PWD_RU,                KPST_MSG_BAD_PWD_RU,                // "Slaptaþodis neteisingas"
KPST_MSG_ENTER_PUK_EN,              KPST_MSG_ENTER_PUK_LT,              KPST_MSG_ENTER_PUK_PL_1250,            KPST_MSG_ENTER_PUK_PL_1257,            KPST_MSG_ENTER_PUK_RU,              KPST_MSG_ENTER_PUK_RU,              // "Áveskite atmintuko licencijos kodà:"
KPST_MSG_BAD_PUK_EN,                KPST_MSG_BAD_PUK_LT,                KPST_MSG_BAD_PUK_PL_1250,              KPST_MSG_BAD_PUK_PL_1257,              KPST_MSG_BAD_PUK_RU,                KPST_MSG_BAD_PUK_RU,                // "Neteisingas licencijos kodas"

KPST_MSG_OBJ_REG_EN,                KPST_MSG_OBJ_REG_LT,                KPST_MSG_OBJ_REG_PL_1250,              KPST_MSG_OBJ_REG_PL_1257,              KPST_MSG_OBJ_REG_RU,                KPST_MSG_OBJ_REG_RU,                // "Dokumento registracija"
KPST_MSG_OBJ_REG_INFO_EN,           KPST_MSG_OBJ_REG_INFO_LT,           KPST_MSG_OBJ_REG_INFO_PL_1250,         KPST_MSG_OBJ_REG_INFO_PL_1257,         KPST_MSG_OBJ_REG_INFO_RU,           KPST_MSG_OBJ_REG_INFO_RU,           // "Prieð naudojant dokumentà reikia uþregistruoti."
KPST_MSG_OBJ_UNREG_INFO_EN,         KPST_MSG_OBJ_UNREG_INFO_LT,         KPST_MSG_OBJ_UNREG_INFO_PL_1250,       KPST_MSG_OBJ_UNREG_INFO_PL_1257,       KPST_MSG_OBJ_UNREG_INFO_RU,         KPST_MSG_OBJ_UNREG_INFO_RU,         // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
KPST_MSG_OBJ_REG_PERSPEJ_EN,        KPST_MSG_OBJ_REG_PERSPEJ_LT,        KPST_MSG_OBJ_REG_PERSPEJ_PL_1250,      KPST_MSG_OBJ_REG_PERSPEJ_PL_1257,      KPST_MSG_OBJ_REG_PERSPEJ_RU,        KPST_MSG_OBJ_REG_PERSPEJ_RU,        // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

KPST_MSG_OBJ_REG_NOT_YET_EN,        KPST_MSG_OBJ_REG_NOT_YET_LT,        KPST_MSG_OBJ_REG_NOT_YET_PL_1250,      KPST_MSG_OBJ_REG_NOT_YET_PL_1257,      KPST_MSG_OBJ_REG_NOT_YET_RU,        KPST_MSG_OBJ_REG_NOT_YET_RU,        // "Dokumento registracija atðaukta."
KPST_MSG_OBJ_UNREG_NEGALESIT_EN,    KPST_MSG_OBJ_UNREG_NEGALESIT_LT,    KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250,  KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1257,  KPST_MSG_OBJ_UNREG_NEGALESIT_RU,    KPST_MSG_OBJ_UNREG_NEGALESIT_RU,    // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

KPST_MSG_BAD_FLASH_EN,              KPST_MSG_BAD_FLASH_LT,              KPST_MSG_BAD_FLASH_PL_1250,            KPST_MSG_BAD_FLASH_PL_1257,            KPST_MSG_BAD_FLASH_RU,              KPST_MSG_BAD_FLASH_RU,              // "Ðis atnaujinimas skirtas atmintukui %s"

KPST_MSG_LICENCE_EXPIRED_EN,        KPST_MSG_LICENCE_EXPIRED_LT,        KPST_MSG_LICENCE_EXPIRED_PL_1250,      KPST_MSG_LICENCE_EXPIRED_PL_1257,      KPST_MSG_LICENCE_EXPIRED_RU,        KPST_MSG_LICENCE_EXPIRED_RU,        // "Licencijos galiojimas baigësi"
KPST_MSG_REST_MONTHS_EN,            KPST_MSG_REST_MONTHS_LT,            KPST_MSG_REST_MONTHS_PL_1250,          KPST_MSG_REST_MONTHS_PL_1257,          KPST_MSG_REST_MONTHS_RU,            KPST_MSG_REST_MONTHS_RU,            // "Licencijos galiojimas baigsis po %d mënesiø"
KPST_MSG_REST_LAST_MONTH_EN,        KPST_MSG_REST_LAST_MONTH_LT,        KPST_MSG_REST_LAST_MONTH_PL_1250,      KPST_MSG_REST_LAST_MONTH_PL_1257,      KPST_MSG_REST_LAST_MONTH_RU,        KPST_MSG_REST_LAST_MONTH_RU,        // "Licencijos galiojimas baigsis kità mënesá"
KPST_MSG_REST_DAYS_EN,              KPST_MSG_REST_DAYS_LT,              KPST_MSG_REST_DAYS_PL_1250,            KPST_MSG_REST_DAYS_PL_1257,            KPST_MSG_REST_DAYS_RU,              KPST_MSG_REST_DAYS_RU,              // "Licencijos galiojimas baigsis po %d dienø"
KPST_MSG_REST_DAY_EN,               KPST_MSG_REST_DAY_LT,               KPST_MSG_REST_DAY_PL_1250,             KPST_MSG_REST_DAY_PL_1257,             KPST_MSG_REST_DAY_RU,               KPST_MSG_REST_DAY_RU,               // "Rytoj baigsis licencijos galiojimas"
KPST_MSG_REST_TODAY_EN,             KPST_MSG_REST_TODAY_LT,             KPST_MSG_REST_TODAY_PL_1250,           KPST_MSG_REST_TODAY_PL_1257,           KPST_MSG_REST_TODAY_RU,             KPST_MSG_REST_TODAY_RU,             // "Ðiandien baigiasi licencijos galiojimas"
KPST_MSG_TIME_CHEAT_EN,             KPST_MSG_TIME_CHEAT_LT,             KPST_MSG_TIME_CHEAT_PL_1250,           KPST_MSG_TIME_CHEAT_PL_1257,           KPST_MSG_TIME_CHEAT_RU,             KPST_MSG_TIME_CHEAT_RU,             // "Teisingai nustatykite sistemos laikrodá"

KPST_MSG_BAD_PRODVAR_EN,            KPST_MSG_BAD_PRODVAR_LT,            KPST_MSG_BAD_PRODVAR_PL_1250,          KPST_MSG_BAD_PRODVAR_PL_1257,          KPST_MSG_BAD_PRODVAR_RU,            KPST_MSG_BAD_PRODVAR_RU,            // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

KPST_MSG_UPDATE_FINISHED_EN,        KPST_MSG_UPDATE_FINISHED_LT,        KPST_MSG_UPDATE_FINISHED_PL_1250,      KPST_MSG_UPDATE_FINISHED_PL_1257,      KPST_MSG_UPDATE_FINISHED_RU,        KPST_MSG_UPDATE_FINISHED_RU,        // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

KPST_MSG_SELDOWN_TITLE_EN,          KPST_MSG_SELDOWN_TITLE_LT,          KPST_MSG_SELDOWN_TITLE_PL_1250,        KPST_MSG_SELDOWN_TITLE_PL_1257,        KPST_MSG_SELDOWN_TITLE_RU,          KPST_MSG_SELDOWN_TITLE_EN,          // "Produkto komponentø parsisiøsdinimas:"
KPST_MSG_SELDOWN_PROMPT_EN,         KPST_MSG_SELDOWN_PROMPT_LT,         KPST_MSG_SELDOWN_PROMPT_PL_1250,       KPST_MSG_SELDOWN_PROMPT_PL_1257,       KPST_MSG_SELDOWN_PROMPT_RU,         KPST_MSG_SELDOWN_PROMPT_RU,         // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
KPST_MSG_SELDOWN_NOMORE_PROMPT_EN,  KPST_MSG_SELDOWN_NOMORE_PROMPT_LT,  KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1250,KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1257,KPST_MSG_SELDOWN_NOMORE_PROMPT_RU,  KPST_MSG_SELDOWN_NOMORE_PROMPT_RU,  // "Naujø serijos leidiniø daugiau netikrinti:"
KPST_MSG_SELDOWN_BUT_PROMPT_EN,     KPST_MSG_SELDOWN_BUT_PROMPT_LT,     KPST_MSG_SELDOWN_BUT_PROMPT_PL_1250,   KPST_MSG_SELDOWN_BUT_PROMPT_PL_1257,   KPST_MSG_SELDOWN_BUT_PROMPT_RU,     KPST_MSG_SELDOWN_BUT_PROMPT_RU,     // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“."

KPST_MSG_SELUPD_TITLE_EN,           KPST_MSG_SELUPD_TITLE_LT,           KPST_MSG_SELUPD_TITLE_PL_1250,         KPST_MSG_SELUPD_TITLE_PL_1257,         KPST_MSG_SELUPD_TITLE_RU,           KPST_MSG_SELUPD_TITLE_RU,           // "Produkto atnaujinimø parsisiøsdinimas")
KPST_MSG_SELUPD_PROMPT_EN,          KPST_MSG_SELUPD_PROMPT_LT,          KPST_MSG_SELUPD_PROMPT_PL_1250,        KPST_MSG_SELUPD_PROMPT_PL_1257,        KPST_MSG_SELUPD_PROMPT_RU,          KPST_MSG_SELUPD_PROMPT_RU,          // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
KPST_MSG_SELUPD_NOMORE_PROMPT_EN,   KPST_MSG_SELUPD_NOMORE_PROMPT_LT,   KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1250, KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1257, KPST_MSG_SELUPD_NOMORE_PROMPT_RU,   KPST_MSG_SELUPD_NOMORE_PROMPT_RU,   // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
KPST_MSG_SELUPD_BUT_PROMPT_EN,      KPST_MSG_SELUPD_BUT_PROMPT_LT,      KPST_MSG_SELUPD_BUT_PROMPT_PL_1250,    KPST_MSG_SELUPD_BUT_PROMPT_PL_1257,    KPST_MSG_SELUPD_BUT_PROMPT_RU,      KPST_MSG_SELUPD_BUT_PROMPT_RU,      // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

KPST_MSG_CLOSE_PROG_WND_EN,         KPST_MSG_CLOSE_PROG_WND_LT,         KPST_MSG_CLOSE_PROG_WND_PL_1250,       KPST_MSG_CLOSE_PROG_WND_PL_1257,       KPST_MSG_CLOSE_PROG_WND_RU,         KPST_MSG_CLOSE_PROG_WND_RU,         // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"
};


// -----------------------------------------
KpStApp::KpStApp(void)
{
/* const */ unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
// bool hide_bkmrks = False;

// FILE *out_file=fopen("kpstlsvr.txt", "w");
// fprintf(out_file, "KpStApp() called\n");
// fclose(out_file);

   m_hBitMap = NULL;
   m_hBitmapWindow = NULL;
// m_hBitmapCtrl = NULL;
   m_iBitmapCnt = 0;
// m_iCurBmp = 0;
// m_plpszBmpList = NULL;
// m_iaBmpTimes = NULL;

   m_hMuteButton = NULL;

   m_lProlThreadId=0L;
   m_lEpilThreadId=0L;
   m_lClipViewerThreadId=0L;
   m_lpszClipViewerFName[0]=Nul;

   m_hCmdProcess = NULL;
   m_hCmdThread = NULL;
   m_lCmdThread = 0L;

   m_lpszIniFName[0]=Nul;

   m_RetcPr=KP_E_NO_FILE;

   m_iKpStMode = KpStarterMode;

// m_bMaximizeAcroWindow = False;

// m_iCompId=0;
// m_iInstCount=0;

// m_iLicID=0;

// -------------------
// m_iLicHigh = 0;
// m_iRestDaysInit = 0;
// m_lRestMinutes = Maxlong;
// m_lRestMinutesMain = Maxlong;

// ---------
// m_iRestDaysWarningShowed = False;
// m_iRestDaysWarningShowed = TestRestDaysWarningShowed();

// -------------------
// m_iLicCode1=0;
// m_iLicCode2=0;
// m_iLicCode3=0;

// m_iInstCode1=0;
// m_iInstCode2=0;
// m_iInstCode3=0;
// m_iInstCode4=0;

// m_iInstKey1=0;
// m_iInstKey2=0;
// m_iInstKey3=0;
// m_iInstKey4=0;

// m_iRemCode1=0;
// m_iRemCode2=0;
// m_iRemCode3=0;
// m_iRemCode4=0;

// m_iRemSesID=0;
// m_iRemLicID=0;
// m_iRemProdVer=0;

   m_pLicArray = NULL;

   m_iLicManagTimer = 0;
   m_iProcCmdTimer = 0;
// m_iPrologTimer = 0;
   m_iFlashCheckTimer = 0;
   m_iSesCtrlTimer = 0;
   m_iRestMinsTimer = 0;
   m_bIPserver = False;

   m_lpszProjDir[0] = Nul;

   m_lpszFlashDevName[0] = Nul;
// surandam pradinio aktyvaus katalogo tëvà
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = GetAppPath(m_lpszFlashDevName, False); // "I:\\Matematika Tau-5E mokytojui" CD dalyje
   if(SUCCEEDED(m_lhOpenResult))
   {
      pnts = strchr(m_lpszFlashDevName, '\\'); // "\\Matematika Tau-5E mokytojui" CD dalyje
      if(pnts == NULL)
      {
// StartSel.exe paleidþiamas ið ðaknies
//       m_lhOpenResult = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, m_lpszFlashDevName, False, __FILE__, __LINE__, 0L, NULL);
      }
      else
      {
         while(pnts)
         {
            pntd = pnts; // atsimenam vienu þemesná pakatalogá
            pnts = strchr(pnts + 1, '\\');
         }
         *pntd = Nul;
      }
   }

   m_lpszaExtProcessed = NULL;
   m_lpszaExtViewers = NULL;
   m_lpszaExtViewersBuffer = null;

   m_pUserJsList = NULL;

   m_hLicDialogWindow = NULL;

   m_hLicCodeEdit1=NULL;
   m_hLicCodeEdit2=NULL;
   m_hLicCodeEdit3=NULL;

   m_hLicOkButton=NULL;
   m_hLicSkipButton=NULL;
   m_hLicCancelButton=NULL;

   m_hKeyDialogWindow = NULL;

   m_hKeyUrlButton = NULL;

   m_hInstCodeEdit = NULL;

   m_hInstKey1Edit=NULL;
   m_hInstKey2Edit=NULL;
   m_hInstKey3Edit=NULL;
   m_hInstKey4Edit=NULL;

   m_hKeyOkButton = NULL;
   m_hKeyCancelButton = NULL;

   m_hRemDialogWindow = NULL;

   m_hRemCodeEdit = NULL;

   m_hRemOkButton = NULL;

   m_hHideCloseButtonWnd = NULL;
   m_hHideCloseButtonBmp = 0;

// if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = GetIniHideBkmrks(&hide_bkmrks);
   m_iBkmrkFontSize = 0;
   m_bBookMarksHided = False; // !hide_bkmrks;

   m_iNumWaveDevs = 0;
   m_bSoundPlaying = False;
   m_lInitVolume = m_lCurVolume = 0xFFFFFFFF;

#ifndef KPST_MOVE_TO_KPHP11
   memset(m_Ini.m_lpszCmdStr, Nul, KP_MAX_FILE_LIN_WDT+1);
   m_Ini.m_iProlShowTime=0;
   memset(m_Ini.m_lpszProlFName, Nul, KP_MAX_FNAME_LEN+1);
   m_Ini.m_iBitmapWdt=0;
   m_Ini.m_iBitmapHgt=0;
   memset(m_Ini.m_lpszPwdWndName, Nul, KP_MAX_FNAME_LEN+1);
   memset(m_Ini.m_lpszPwd, Nul, TV_TAG_LEN + 1);
   memset(m_Ini.m_lpszOldPwd, Nul, TV_TAG_LEN + 1);
   m_Ini.m_iPwdEdCtrl=0;
   m_Ini.m_iPwdOkBut=0;
   memset(m_Ini.m_lpszVolName, Nul, KP_MAX_FNAME_LEN+1);
   m_Ini.m_lSerNo=0L;
   memset(m_Ini.m_lpszBmpFName, Nul, KP_MAX_FNAME_LEN+1);
   memset(m_Ini.m_lpszEpilFName, Nul, KP_MAX_FNAME_LEN+1);
   m_Ini.m_iEpilShowTime=0;
   memset(m_Ini.m_lpszPresetFName, Nul, KP_MAX_FNAME_LEN+1);
   memset(m_Ini.m_lpszRezFName, Nul, KP_MAX_FNAME_LEN+1);
   m_Ini.m_bCheckCD=False;
   m_Ini.m_bBound=False;
   m_Ini.m_iProdVer = 0;
   m_Ini.m_iUpdNum = -1;
   memset(m_Ini.m_lpszProdName, Nul, KP_MAX_FNAME_LEN+1);
   memset(m_Ini.m_lpszPublisher, Nul, KP_MAX_FNAME_LEN+1);
   memset(m_Ini.m_lpszRegURL, Nul, KP_MAX_FNAME_LEN+1);
   memset(m_Ini.m_lpszRezVar, Nul, KP_MAX_FNAME_LEN+1);
   m_Ini.m_bKumul=False;
   m_Ini.m_iShuffCnt=0;
   m_Ini.m_lAttOff=0L;
   memset(m_Ini.m_lpszAttExt, Nul, KP_MAX_FTYPE_LEN+1);
   m_Ini.m_bCiDirect=False;
   m_Ini.m_lFlashId=0L;
   m_Ini.m_bCheckFlash=False;
   m_Ini.m_iNumOfLics=0;
   memset(m_Ini.m_lpszTestCid, Nul, KPST_TXTCD_CHARS_PER_VAL_TID+1);
   m_Ini.m_bOnTop = False;
   m_Ini.m_bFullScr = False;
   m_Ini.m_bSubst = False;
   m_Ini.m_bEboard = False;
   m_Ini.m_iCheckSum=0;
   m_Ini.m_bClearClipBrd = False;
   m_Ini.m_bShowIE = False;
   m_Ini.m_bHideBkmrks = False;
#endif

   m_lpszAttFname[0]=Nul;

// m_lpszDrivePath[0]=Nul;

   m_ClipBuf[0]=Nul;
   m_PdfParBuf[0]=Nul;

// KP_NEWC(m_pRezFNameDialog, KpStEdiDlg);

   m_bShiftFl = False;

   m_pcListBuf = NULL;
   m_lListBufLen = 0L;

   m_pListSocket = NULL;
   m_lListThreadId = 0L;
   m_hListThread = NULL;
   m_bInstanceLocked = False;
   m_bCheckUpdPending = False;

   m_pLicListSocket = NULL;

   InitKeyFmts();

   m_iKpstRand0 = 0x12345; // 0;

   m_lpszObjFileName[0] = Nul;

   m_ProdVar = -1;
   strcpy(m_ProdDate, "2010.00.00");
   strcpy(m_ProdVersion, "0.00");

   m_lKpStArcStart[0] = 0L;
   m_lKpStArcLen[0] = 0L;
   m_lKpStArcStart[1] = 0L;
   m_lKpStArcLen[1] = 0L;

// -----------------------------
   m_lpszGrpCfgBuf = null;
   m_pGrpCfgNode = NULL;

   m_lpszGrpCfgFName[0] = Nul;
   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult = CalcGrpCfgFName();

   m_aGrpDownLoads = NULL;

// m_iGrpSvrRequestRetCode = S_OK;

   m_lpszGrpMenu = NULL;
   m_pGrpKpPubDlg = NULL;
// m_pGrpKpFileSys = NULL;

   m_bSaveTestUpdatesToIni = False;

   m_lGrpRefreshThreadId = 0L;
   m_bGrpDownloadListProcessing = False;
   m_GrpDownLoadThreadList = NULL;
   m_GrpDownloadFNameList = NULL;

   m_bGrpRefreshGlobalFlg = m_bGrpRefreshFlg = True;

// m_iCompId = 0;

   m_bForceGrpCfg = False;

   m_bLogin = False;

// >>>>>> 2013-03-03  mp
#ifdef KPST_MULTI_DOCS
   m_bMDImaximized = False;
#endif
// <<<<<< 2013-03-03  mp
}


// -----------------------------------------
KpStApp::~KpStApp(void)
{
HRESULT retc = S_OK;
int ii;

// KP_DELETE(m_pRezFNameDialog);
#ifdef KPST_USE_CLIPBOARD
   /* retc= */ SetClipboardText(/* m_hBitmapWindow */ HWND_DESKTOP, (const unsigned char *)"");
#endif

// ---------------------
   if(m_iLicManagTimer) KillTimer(HWND_DESKTOP, m_iLicManagTimer);
   m_iLicManagTimer = 0;

   if(m_iSesCtrlTimer) KillTimer(HWND_DESKTOP, m_iSesCtrlTimer);
   m_iSesCtrlTimer = 0;

   if(m_iProcCmdTimer) KillTimer(HWND_DESKTOP, m_iProcCmdTimer);
   m_iProcCmdTimer = 0;

   if(m_iFlashCheckTimer) KillTimer(HWND_DESKTOP, m_iFlashCheckTimer);
   m_iFlashCheckTimer = 0;

   if(m_iRestMinsTimer) KillTimer(HWND_DESKTOP, m_iRestMinsTimer);
   m_iRestMinsTimer = 0;

// if(m_iPrologTimer) KillTimer(HWND_DESKTOP, m_iPrologTimer);
// m_iPrologTimer = 0;

   if(m_plpszBmpList != NULL)
      for(ii = 0; ii < m_iBitmapCnt; ii++) KP_DELETEA(m_plpszBmpList[ii]);
   KP_DELETEA(m_plpszBmpList);

   KP_DELETEA(m_iaBmpTimes);
   m_iBitmapCnt = 0;

   KP_DELETE(m_pListSocket);

   KP_DELETEA(m_pcListBuf);
   m_lListBufLen = 0L;

   KP_DELETEA(m_pLicArray);
   KP_DELETE(m_pLicListSocket);

   if(WSACleanup())
   {
// jau vienà kartà iðkviestas ið CloseStApp()
// /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), False, __FILE__, __LINE__, 0L);
   }

   if(m_hHideCloseButtonWnd) if(!DestroyWindow(m_hHideCloseButtonWnd))
      /*retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
   m_hHideCloseButtonWnd = NULL;

   KP_DELETE(KpstEdiDialogPtr)

   KP_DELETEA(m_lpszaExtProcessed);
   KP_DELETEA(m_lpszaExtViewers);
   KP_DELETEA(m_lpszaExtViewersBuffer);
   KP_DELETE(m_pUserJsList);

// -----------------------------
   KP_DELETEA(m_lpszGrpCfgBuf);
   KP_DELETE(m_pGrpCfgNode);
   KP_DELETE(m_aGrpDownLoads);
   KP_DELETE(m_pGrpKpPubDlg);
// KP_DELETE(m_pGrpKpFileSys);

   KP_DELETEA(m_lpszGrpMenu);
// KP_DELETE(m_GrpDownloadFNameList); // volatile – jeigu kitas threadas dar naudoja, trint negerai
   KP_DELETE(m_aGrpDownLoads);
}


// -----------------------------------------
HRESULT KpStApp::InitStApp(HINSTANCE hInstance, const unsigned char *lpszIniFName, 
   LPCSTR lpCmdLine, KpStModes iStMode, bool bCommonAppInitiated, bool *pbLicEntered,
   bool bCheckReg)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
#ifdef KPST_USE_CLIPBOARD
static unsigned char pres_fname[KP_MAX_FNAME_LEN + 1];
unsigned char *contents_ptr = NULL;
const unsigned char *clip_contents = NULL;
long ll;
#endif
int num_of_lics=0;
// bool check_flash;
bool subst = False;
bool hide_bkmrks = False;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
const unsigned char *par = null;
bool obj_fl = False;

PutLogMessage_("KpStApp::InitStApp() 1");

   if(StackTop == NULL) StackTop = &bCommonAppInitiated;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.1 InitCommonApp", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if((!bCommonAppInitiated) && SUCCEEDED(retc)) retc = InitCommonApp(hInstance, lpCmdLine);

   m_iKpStMode=iStMode;

   if((lpszIniFName!=NULL) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) if(strlen(lpszIniFName)>=KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) strcpy(m_lpszIniFName, lpszIniFName);
   }

// ----------------------
   m_lStartTime = 0L; // time(&m_lStartTime);

PutLogMessage_("KpStApp::InitStApp() 2");

// ----------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.2 StartHp11", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc = StartHp11(m_hInstance);

   if(EmuTv.m_lKphp11ThreadId) m_iKpstRand0 = KpstRand(0);

PutLogMessage_("KpStApp::InitStApp() 3");

// ----------------------
#ifdef Debug
// laukiam, kol atsidarys KpHp11 trace langas, po to pagrindiná keliam á virðø
// if(SUCCEEDED(retc)) Sleep(3000);
// if(SUCCEEDED(retc)) SetWindowPos(KpTraceWindow.m_hWndHandle, HWND_TOPMOST, 100, 100, 900, 600, SWP_NOMOVE | SWP_NOSIZE);

// if(SUCCEEDED(retc)) while(EmuWv.m_hWndHandle == NULL);
// if(SUCCEEDED(retc)) Sleep(500);
// if(SUCCEEDED(retc)) SetWindowPos(EmuWv.m_hWndHandle, HWND_BOTTOM, 100, 100, 900, 600, SWP_NOMOVE | SWP_NOSIZE);
#endif

// ----------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.3 LoadIni", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

// if(SUCCEEDED(retc)) retc = ReadIni();
   if(/* m_lpszIniFName && */ SUCCEEDED(retc)) if(m_lpszIniFName[0] /* strlen(m_lpszIniFName) > 0 */) retc = LoadIni();

PutLogMessage_("KpStApp::InitStApp() 4");

// ---------------------- start prologue
   if ((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc)) retc = PlayPrologue();

PutLogMessage_("KpStApp::InitStApp() 5");

// ----------------------------------- ieðkom parametro – .tev objekto
   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_PAR)) obj_fl = True;

   if((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))
      if(obj_fl)
      {
         par = null;
         if(m_plCmdLineArgs) par = (const unsigned char *)m_plCmdLineArgs->GetValue();

PutLogMessage_("KpStApp::InitStApp() 6");

// ---------------------- TODO !!!!! failo atidarymo dialogas
         KP_ASSERT(par != null, E_NOTIMPL, null, True);

#if FALSE
int prod_ver;
GetIniProdVer(&prod_ver);
unsigned char pwd_buf[TV_TAG_LEN + 1];
GetIniPwd(pwd_buf);
KpMsgOutF("KpStApp::InitStApp() prieð: prod_ver: %d pwd_buf: [%s] par: [%s]", prod_ver, pwd_buf, par);
KpMsgOutF("KpStApp::InitStApp() [%s]", m_Ini.m_lpszPwd);
#endif

// ------------ ieðkom papildomø produkto parametrø faile
         if(SUCCEEDED(retc)) retc = IoRid(par, False);

// iðarchyvuojam failus
         if(SUCCEEDED(retc)) retc = UnpackObjFiles();

PutLogMessage_("KpStApp::InitStApp() 7");

#if FALSE // TRUE //
int prod_ver;
GetIniProdVer(&prod_ver);
unsigned char pwd_buf[TV_TAG_LEN + 1];
GetIniPwd(pwd_buf);
KpMsgOutF("KpStApp::InitStApp() po: prod_ver: %d pwd_buf: [%s] par: [%s]", prod_ver, pwd_buf, par);
#endif

      } // if(obj_fl)

// ----------------------
   if(SUCCEEDED(retc)) retc=GetIniProdVer(&iProdVerGlob);
   if(SUCCEEDED(retc)) retc=GetIniUpdNum(&iUpdNumGlob);
// if(SUCCEEDED(retc)) retc=GetIniCheckFlash(&check_flash);
   if(SUCCEEDED(retc)) retc=GetIniSubst(&subst);

   if(SUCCEEDED(retc)) retc = GetIniHideBkmrks(&hide_bkmrks);
   m_bBookMarksHided = !hide_bkmrks;

PutLogMessage_("KpStApp::InitStApp() 8");

// ----------------------
   if(EmuTv.m_lKphp11ThreadId)
   {
      retc0 = GetCommonCompID();
      if(SUCCEEDED(retc)) retc=retc0;
   }

PutLogMessage_("KpStApp::InitStApp() 9");

// ----------------------
   if((m_iKpStMode==KpStarterMode) && SUCCEEDED(retc))
   {
//    if(SUCCEEDED(retc)) retc = CheckKpStartRunning();

// ----------------------
//    if(SUCCEEDED(retc)) retc = CloseLaunchPrompt();
      if(SUCCEEDED(retc)) retc = CloseAutoPlay();
//    if(SUCCEEDED(retc)) retc = CloseCompatibilityAssistant();

PutLogMessage_("KpStApp::InitStApp() 10");

// ----------------------
      if(SUCCEEDED(retc)) retc = SaveGlobalJs();

PutLogMessage_("KpStApp::InitStApp() 11");

// ----------------------
      if(SUCCEEDED(retc)) retc = TestCD();
   }

// ----------------------
   if(((m_iKpStMode == KpStarterMode) ||
       (strcmp(lpszProdName, "StartGrp") == 0) || // (m_iKpStMode == KpStEditMode) || // (m_iKpStMode == KpStRegMode) ||
                                       // reikia StartGrp.exe, kad veiktø ir atmintukinës aplikacijos
                                       // TODO: nors StartGrp.exe reiktø perdaryti á saviregistruojantá KpStarterMode, tada nereiktø
                                       // Dabar StartGrp yra KpStEditMode
       (m_iKpStMode == KpStrpdMode)) && SUCCEEDED(retc))
         retc = TestFlash();

PutLogMessage_("KpStApp::InitStApp() 12");

#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.4 CheckReg", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

#if FALSE
static unsigned char dir_buf[KP_MAX_FNAME_LEN + 1];
GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf);
KpMsgOutF(dir_buf);
#endif

// èia Audrius Vinipuchas nulauþia ipaf_20060210.exe
   if(
      (
         (m_iKpStMode == KpStarterMode) ||
// :00402309 8B45DC                  mov eax, dword[ebp-24]
// :0040230C 80782000                cmp byte[eax+20], 00
// :00402310 7406                    je 00402318
         (strcmp(lpszProdName, "StartGrp") == 0) || // (m_iKpStMode == KpStEditMode) || // (m_iKpStMode == KpStRegMode) ||
                                       // Dabar StartGrp yra KpStEditMode
                                       // StartGrp net ir nepririðtam reikia – kad nusiimtø KP11_BLOCK_PROCESSING
         (m_iKpStMode == KpStLicSvrMode) || (m_iKpStMode == KpStrpdMode)
      ) &&
      bCheckReg &&
      SUCCEEDED(retc) // FAILED(retc) //
// :00402312 837DD800                cmp dword[ebp-28], 000
// :00402316 7D02                    jge 0040231A  // Audrius keièia á // :00402316 7C02                    jl 0040231A
// :00402318 EB14                    jmp 0040232E
     )
   {
// PutLogMessage("KpStApp::InitStApp(): CHKRG");
      retc = CheckReg(m_hInstance, pbLicEntered);
// :0040231A 8D5DFC                  lea ebx, dword[ebp-04]
// :0040231D 8B45DC                  mov eax, dword[ebp-24]
// :00402320 8B5008                  mov edx, dword[eax+08]
// :00402323 8B45DC                  mov eax, dword[ebp-24]
// :00402326 E84A3A0100              call 00415D75
// :0040232B 8945D8                  mov dword[ebp-28], eax

// KpMsgOutF_1("InitStApp [2]: %x", retc);

   } // if(m_iKpStMode == KpStarterMode) ...

PutLogMessage_("KpStApp::InitStApp() 13");

// --------------------------
   if(SUCCEEDED(retc)) retc = InitExtViewers();

PutLogMessage_("KpStApp::InitStApp() 14");

// --------------------------
   if(SUCCEEDED(retc)) retc = CheckBinaries();

PutLogMessage_("KpStApp::InitStApp() 15");

// --------------------------
   if(
      (m_iKpStMode == KpStarterMode) &&
      SUCCEEDED(retc)
     )
   {

// ----------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.6 TestSound", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

      if(SUCCEEDED(retc)) retc = TestSound();

// PutLogMessage_("KpStApp::InitStApp() 6.1 %x", retc);
PutLogMessage_("KpStApp::InitStApp() 16");

// ---------------------- start prologue
#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.5 StartPrologue", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

// Iðkeltas á pradþià – TK910 ilgai kraunasi
//    if(SUCCEEDED(retc)) retc = PlayPrologue();

// PutLogMessage_("KpStApp::InitStApp() 6.2 %x", retc);
PutLogMessage_("KpStApp::InitStApp() 17");

// ----------------------
      if(subst && SUCCEEDED(retc)) retc = SubstToLocal();

      if(SUCCEEDED(retc)) retc = SetAppPathPar();

      if(SUCCEEDED(retc)) retc = Detach();

//    if(SUCCEEDED(retc)) /* retc = */ InitUserFileList();

PutLogMessage_("KpStApp::InitStApp() 18");

      if((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))
      {
// vartotojo vardas (UserData) --> data.dat (kintamasis SI)
// atm. lic. kodas (AdminPwd) <--> data.dat (kintamasisi AI)
         if(obj_fl)
         {
// TODO jei objektø þiûryklë – áraðyti data.dat failà á objektà
         }
         else  /* retc = */ SetDataDatUserData(); // data.dat raðom tik jei ne objektø þiûryklë (
      }

//    if(SUCCEEDED(retc)) /* retc = */ CopyUpdateDat();

      if(SUCCEEDED(retc)) /* retc = */ CopyCalcFiles();

      if(SUCCEEDED(retc)) /* retc = */ CopyUserJscripts();

PutLogMessage_("KpStApp::InitStApp() 19");

// ----------------------
      if(SUCCEEDED(retc)) retc = StartClipViewer();

PutLogMessage_("KpStApp::InitStApp() 20");

// ----------------------
      if(SUCCEEDED(retc)) retc = InitTestPar();

      if(SUCCEEDED(retc)) retc = SetRezSrvData();

PutLogMessage_("KpStApp::InitStApp() 21");

// ---------------------- ini data to clipboard
#ifdef KPST_USE_CLIPBOARD
#ifdef Debug
#ifdef DebugStop
KpMsgOut("1.7 SetIniData", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

      if(SUCCEEDED(retc)) retc=GetIniPresetFName(pres_fname);
      if(SUCCEEDED(retc))
      {
         if(strlen(pres_fname)>0)
         {
            retc = ReadFileContents(pres_fname, &contents_ptr, &ll, False, False);
            if(retc == KP_E_FILE_NOT_FOUND)
            {
               KP_DELETEA(contents_ptr);
               retc = S_OK;
            }
            else
               if(FAILED(retc))
                  retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               if(contents_ptr != NULL) clip_contents = contents_ptr;
               else clip_contents = (const unsigned char *)"";
            }
         }
         else clip_contents = (const unsigned char *)"";

         if(SUCCEEDED(retc)) retc = SetClipboardText(m_hBitmapWindow, clip_contents);

         KP_DELETEA(contents_ptr);

      } // if(SUCCEEDED(retc))
#endif // #ifdef KPST_USE_CLIPBOARD

PutLogMessage_("KpStApp::InitStApp() 22");

// ------------------------- msvcp60.dll
      if(SUCCEEDED(retc)) retc=RenewDllsAll();

PutLogMessage_("KpStApp::InitStApp() 23");

// ----------------------
   } // if((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))

// --------------------- init server listenning socket
// gali ir neatsidaryti Bind(), portas gali bûti jau uþimtas – tux_ipa inicializuojamas du kartus
   if(SUCCEEDED(retc))
   {
      if(m_iKpStMode == KpStIpSvrMode)
      {
#ifdef TUX_LIB
         CreateSockThread(m_hInstance);
#else
         retc = CreateSockThread(m_hInstance);
         if(FAILED(retc)) KP_WARNING0(retc, null); // einam lauk - viena instancija jau paleista
#ifndef Debug
         if(retc != KP_E_NO_CONN)
#endif
            retc = S_OK; // kitos klaidos - nekreipiam dëmesio (kaþin kaip, kai proxis uþdraudþia?)
#endif
      }
      else if(m_iKpStMode == KpStarterMode)
      {
// paleidþiam atskirà porto klausymo serveriukà, kuris veiks visà laikà iki kompo perkrovimo
// Vista neleidþia pakartotinio portø atidarymo
         retc = StartSockProcess();

      } // else if(m_iKpStMode == KpStarterMode)

   } // if(SUCCEEDED(retc))

PutLogMessage_("KpStApp::InitStApp() 24");

// ----------------------
   if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(((m_iKpStMode==KpStLicSvrMode) || (m_iKpStMode==KpStEditMode)) && num_of_lics && SUCCEEDED(retc))
   {
      KP_NEWA(m_pLicArray, LicStatus, num_of_lics);

      if(SUCCEEDED(retc)) retc = GetSavedLicences();
      if(SUCCEEDED(retc)) retc = SaveLicences(True);
   }

PutLogMessage_("KpStApp::InitStApp() 25");

// --------------------------------
// Turi bûti po StartSockProcess(), nes tikrina m_bIPserver
   if(SUCCEEDED(retc)) retc = SetTimers();

PutLogMessage_("KpStApp::InitStApp() 26");

// --------------------------------
   if((m_iKpStMode != KpStLicSvrMode) && SUCCEEDED(retc))
   {
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
      if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
      if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);
      if(SUCCEEDED(retc)) if((m_iKpStMode == KpStEditMode) || (strlen(rez_fname) > 0))
      {
         KP_NEW(KpstEdiDialogPtr, KpStEdiDlg);
//       KP_NEWO(KpstEdiDialogPtr, KpStEdiDlg);
      }
   }

#ifdef Debug
unsigned char str_buf[1000];
bool data_fl[1] = {False};
FormAddData(str_buf, data_fl, 1, 7, False);
#endif

PutLogMessage_("KpStApp::InitStApp() 27");

// ------------------------------ update tikrinimas
#ifdef KPST_UPDATE_OLD_LAUNCH
// paleidziam automatinio update tikrinimo threadà
   if((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc)) retc = StartCheckUpdateThread();
#else
// tikrinam paleidþiant IP serverá kpstisvr.exe – ne, ateis per spec. IP praneðimà "CU="
// if((m_iKpStMode == KpStLicSvrMode)
// {
//    retc0 = CheckUpdate(False, False);
//    if(SUCCEEDED(retc)) retc = retc0;
// }

// siunèiam IP praneðimà "CU=" á kpstisvr.exe
   if((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))
   {
bool test_upd = False;
bool lic_flash = False;
      retc = GetTestUpdates(&test_upd);
      if(SUCCEEDED(retc)) retc = GetIniLicFlash(&lic_flash);
      if((test_upd || lic_flash) && SUCCEEDED(retc)) /* retc = */ SendCheckUpdateMsg();
   }
#endif

PutLogMessage_("KpStApp::InitStApp() 28");

// ---------------------------------
#ifndef TUX_LIB
   if(SUCCEEDED(retc)) if((m_iKpStMode == KpStarterMode) || (m_iKpStMode == KpStRegMode)) // reikia ir registratoriui – Win 7 neadminui neleidþia áraðyt net á vartotojo raktus, ypaè XFS-ui
   {
// ------------------------- acroread 5.0 initial settings
      if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD50_PATHNAME) != null) retc = InitAcro50();

// ------------------------- acroread 6.0 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD60_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) != null)) retc = InitAcro60();

// ------------------------- acroread 7.0 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD70_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT) != null)) retc = InitAcro70();

// ------------------------- acroread 8 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD80_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT) != null)) retc = InitAcro80();

// ------------------------- acroread 9.0 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD90_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT) != null)) retc = InitAcro90();

   } // if((m_iKpStMode==KpStarterMode) || (m_iKpStMode == KpStRegMode))
#endif // #ifndef TUX_LIB

PutLogMessage_("KpStApp::InitStApp() 29");

// ------------------------------- iððsitraukiam CompId, reikia StartGrp.exe, KpStApp::GrpSvrRequest(), iðkvieèiamam ne ið pagrindinio threado
// if(SUCCEEDED(retc)) retc = GetPhysCompId();
// if(SUCCEEDED(retc)) retc = EmuTv.GetHp11Variable(&m_iCompId, KP11_COMPID);

// PutLogMessage_("KpStApp::InitStApp(): %d %d %d %d : %x %x %x : %x %x", m_lCmdThread, m_lListThreadId, iKpMainThread, GetCurrentThreadId(), m_hCmdThread, m_hListThread, GetCurrentThread(), m_hCmdProcess, GetCurrentProcess());
PutLogMessage_("KpStApp::InitStApp() 30");

return(retc);
}


// ----------------------------------------
HRESULT KpStApp::SetTimers(void)
{
HRESULT retc=S_OK;
bool check_flash;

   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);

// --------------------------------
   if(((m_iKpStMode==KpStarterMode) || (m_iKpStMode==KpStLicSvrMode)) && SUCCEEDED(retc))
   {
      m_iLicManagTimer = SetTimer(HWND_DESKTOP, KPST_LIC_MANAG_TIMER, KPST_LIC_MANAG_TIMEOUT, NULL);
      KP_ASSERT(m_iLicManagTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if((((m_iKpStMode == KpStarterMode) && m_bIPserver) || (m_iKpStMode == KpStIpSvrMode)) && SUCCEEDED(retc))
   {
      m_iSesCtrlTimer = SetTimer(HWND_DESKTOP, KPST_SES_CTRL_TIMER, ((m_iKpStMode == KpStarterMode)?KPST_SES_PROLONG_TIMEOUT:KPST_SES_RELEASE_TIMEOUT), NULL);
      KP_ASSERT(m_iSesCtrlTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

// if((m_iKpStMode != KpStrpdMode) && SUCCEEDED(retc))
   if((m_iKpStMode == KpStarterMode) && SUCCEEDED(retc))
   {
      m_iProcCmdTimer = SetTimer(HWND_DESKTOP, KPST_PROC_CMD_TIMER, KPST_PROC_CMD_TIMEOUT, NULL);
      KP_ASSERT(m_iProcCmdTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

   if(check_flash && ((m_iKpStMode==KpStarterMode) || (m_iKpStMode == KpStrpdMode)) && SUCCEEDED(retc))
   {
      m_iFlashCheckTimer = SetTimer(HWND_DESKTOP, KPST_CHK_FLASH_TIMER, KPST_CHK_SER_FLASH_TIMEOUT, NULL);
      KP_ASSERT(m_iFlashCheckTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::SetRestMinsTimer(void)
{
HRESULT retc=S_OK;

   if(cMemBank[KP11_REST_DAYS_INIT/2]) // esam HP11 viduje, kintamuosius skaitom tiesiogiai
   {
      m_iRestMinsTimer = SetTimer(HWND_DESKTOP, KPST_CHK_FLASH_TIMER, KPST_REST_MINS_TIMEOUT, NULL);
      KP_ASSERT(m_iRestMinsTimer, KP_E_SYSTEM_ERROR, GetLastError(), True);
   }

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::SubstToLocal(void)
{
HRESULT retc=S_OK;
unsigned char drive_path[10];
unsigned char cmd_buf[KP_MAX_FNAME_LEN+100];
int ii;
UINT drive_type;
HANDLE cmd_proc=NULL;
unsigned char dir_buf[KP_MAX_FNAME_LEN+1];
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
bool substed = False;

   dir_buf[0]=Nul;
#if FALSE
   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf), KP_E_SYSTEM_ERROR, GetLastError(), True);
#else
// ne current, o start dir
   if(SUCCEEDED(retc)) retc = GetAppPath(dir_buf, False);
#endif
   if(SUCCEEDED(retc))
      if(strlen(dir_buf)==0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc))
      if(
         (strcmp(dir_buf+1, ":\\") != 0) && // cia jeigu jau ir taip saknyje - subst nereikia, leidziam iskart is ten
         (TvStrChr(cmd_str, (KpChar)':')==NULL) &&
         (TvStrChr(cmd_str, (KpChar)'%')==NULL) &&
         (TvStrChr(cmd_str, (KpChar)'\\')!=NULL)
        )
      {
// gal naudot KP_NUM_OF_DISKS

//       strcpy(drive_path, "D:\\"); // "A:\\");
         strcpy(drive_path, "Z:\\");

         substed = False;

//       for(ii='D' /* 'A' */; ii<='Z'; ii++)
         for(ii='Z'; (ii >= 'D' /* 'A' */) && (!substed); ii--)
         {
            drive_path[0]=ii;
            drive_type=GetDriveType((const char *)drive_path);
            if(drive_type == DRIVE_NO_ROOT_DIR /* DRIVE_UNKNOWN */)
            {

//             if(ii>'Z')
               if(ii<'D' /* 'A' */)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

               if(SUCCEEDED(retc))
               {
                  drive_path[2]=Nul;
                  strcpy(m_lpszDrivePath, drive_path);
               }

// subst automatiskai paleidzia start.exe is autorun.inf - specialu autorun.inf su null.exe !!!
               if(SUCCEEDED(retc))
               {
//                sprintf((char *)cmd_buf, "subst \"%s\" .", drive_path);
//                sprintf((char *)cmd_buf, "subst \"%s\" \"%s\"", drive_path, dir_buf);
                  sprintf((char *)cmd_buf, "subst %s \"%s\"", drive_path, dir_buf);
                  retc = StartProcess(cmd_buf, KPST_CUR_DIR, NULL, &cmd_proc, SW_SHOWMINIMIZED);
               }

               if(SUCCEEDED(retc)) retc = WaitForProcessEnd(cmd_proc, NULL);
               if(SUCCEEDED(retc)) retc = KpSleep(500, HWND_DESKTOP);

               if(SUCCEEDED(retc))
               {
                  drive_path[2]='\\';
                  drive_path[3]=Nul;
                  if(SetCurrentDirectory((const char *)drive_path))
                  {
                     substed = True;
                     break;
                  }
                  else
                  {
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L);
#if TRUE // #ifdef Debug
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, drive_path, False, __FILE__, __LINE__, 0L);
#endif
                  }
               }

            } // if(drive_type==DRIVE_NO_ROOT_DIR /* DRIVE_UNKNOWN */)

         } // for(ii='Z'; ii >= 'D' /* 'A' */; ii--)

         if((!substed) && SUCCEEDED(retc))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      } // if(TvStrChr(cmd_str, ':')==NULL)

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::InitBmpList(void)
{
HRESULT retc = S_OK;
unsigned char bmp_fname[KP_MAX_FNAME_LEN+1];
const unsigned char *pnt_ext;
const unsigned char *pnt_next;
int ii;
unsigned char *pntd = NULL;
// static unsigned char cur_dir[KP_MAX_FNAME_LEN + 100];

   if(SUCCEEDED(retc)) retc = GetIniBmpFName(bmp_fname);
   if(SUCCEEDED(retc)) strlwr(bmp_fname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(bmp_fname);

   KP_ASSERT(m_plpszBmpList == NULL, KP_E_SYSTEM_ERROR, null, False);
   m_plpszBmpList = NULL;

// KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir), KP_E_SYSTEM_ERROR, GetLastError(), True);
// if(SUCCEEDED(retc)) strcat(cur_dir, "\\");

   if(SUCCEEDED(retc)) if(strlen(bmp_fname) > 0)
   {
      pnt_ext = strchr(bmp_fname, '.');
      if(pnt_ext != NULL)
      {
         do
         {
            pnt_next = strchr(pnt_ext + 1, '.');
            if(pnt_next != NULL) pnt_ext = pnt_next;
         } while(pnt_next != NULL);
      }
      else pnt_ext = bmp_fname + strlen(bmp_fname);

      if(SUCCEEDED(retc))
      {
         if((strcmp(pnt_ext, ".bmp") == 0) || (strcmp(pnt_ext, "") == 0))
         {
            m_iBitmapCnt = 1;
            KP_NEWA(m_plpszBmpList, unsigned char *, m_iBitmapCnt);
            KP_NEWA(m_plpszBmpList[0], unsigned char, /* strlen(cur_dir) + */ strlen(bmp_fname) + 1);

            if(SUCCEEDED(retc))
            {
//             strcpy(m_plpszBmpList[0], cur_dir);
            /* strcat */ strcpy(m_plpszBmpList[0], bmp_fname);
            }
         }
         else if(strcmp(pnt_ext, ".mcl") == 0)
         {
            m_iBitmapCnt = CountFileLines(bmp_fname);
            if(m_iBitmapCnt)
            {
               KP_NEWA(m_plpszBmpList, unsigned char *, m_iBitmapCnt);

               if(SUCCEEDED(retc)) for(ii = 0; ii < m_iBitmapCnt; ii++) m_plpszBmpList[ii] = NULL;

               if(SUCCEEDED(retc))
               {
                  retc = ReadStrArr(bmp_fname, m_plpszBmpList, &m_iBitmapCnt /* , cur_dir */);
                  KP_ASSERT(retc != KP_E_BUFFER_OVERFLOW, retc, null, False);
               }

// ---- skanuojam laikus
               KP_NEWA(m_iaBmpTimes, int, m_iBitmapCnt);

               if(SUCCEEDED(retc)) for(ii = 0; (ii < m_iBitmapCnt) && SUCCEEDED(retc); ii++)
               {
                  m_iaBmpTimes[ii] = 1000;
                  pntd = strchr(m_plpszBmpList[ii], '\t');
                  if(pntd)
                  {
                     *pntd++ = Nul;
                     KP_ASSERT(sscanf((const char *)pntd, "%d", &m_iaBmpTimes[ii]) == 1, KP_E_FILE_FORMAT, null, False);
                  }
               }
            }
         } // else if(strcmp(pnt_ext, ".mcl") == 0)
         else KP_ERROR(E_INVALIDARG, null);

      } // if(SUCCEEDED(retc))

   } // if(SUCCEEDED(retc)) if(strlen(bmp_fname) > 0)

return(retc);
}


// -----------------------------------------
KpBmpData mute_bmp_pars; // statinis, kad neiðsitrintø iðëjus – KpStShBmpProc() jo reikës vëliau, per WM_CREATE praneðimo apdorojimà

HRESULT KpStApp::PlayPrologue(void)
{
HRESULT retc=S_OK;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
// unsigned char bmp_fname[KP_MAX_FNAME_LEN + 1];
int bmp_wdt;
int bmp_hgt;
static unsigned char prol_fname[KP_MAX_FNAME_LEN + 1];
int prol_show_time;
bool muted;
// HBITMAP mute_bmp;

// ---------------------------------------
   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

   if(SUCCEEDED(retc)) retc = GetIniBitmapWdt(&bmp_wdt);
   if(SUCCEEDED(retc)) retc = GetIniBitmapHgt(&bmp_hgt);

   if(SUCCEEDED(retc)) retc = GetIniProlFName(prol_fname);
   if(SUCCEEDED(retc)) retc = GetIniProlShowTime(&prol_show_time);

   if(SUCCEEDED(retc)) retc = GetIniSoundMuted(&muted);

// ---------------------------------------
// show bmp (list movie)
// if(SUCCEEDED(retc)) retc = GetIniBmpFName(bmp_fname);
// if(SUCCEEDED(retc)) strlwr(bmp_fname);
   if(SUCCEEDED(retc)) retc = InitBmpList();

// ------------------- mute mygtuko bitmapai
// mute_bmp = NULL;

   if(SUCCEEDED(retc)) if(IsSoundFileProcessed(prol_fname))
   {
//    mute_bmp = (HBITMAP)LoadImage(GetModuleHandle(0), "mute.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
//    KP_ASSERT(mute_bmp, KP_E_FILE_NOT_FOUND, "mute.bmp", False);
//    if(SUCCEEDED(retc)) mute_bmp_pars.m_hBitMap /* mute_bmp */ = LoadBitmap(hKpInstance, MAKEINTRESOURCE(muted?KP_IDI_MUTED_BMP:KP_IDI_MUTE_BMP));
//    KP_ASSERT(mute_bmp_pars.m_hBitMap /* mute_bmp */, KP_E_FILE_NOT_FOUND, GetLastError(), True);
      if(SUCCEEDED(retc)) mute_bmp_pars.m_hBitMap = (HBITMAP)LoadImage(GetModuleHandle(0), muted?"gars-1-48.bmp":"gars-2-48.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
      KP_ASSERT(mute_bmp_pars.m_hBitMap, KP_E_FILE_NOT_FOUND, muted?"gars-1-48.bmp":"gars-2-48.bmp", False);

//    if(SUCCEEDED(retc)) mute_bmp_pars.m_hSliderBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(muted?KP_IDI_MUTE_BMP:KP_IDI_MUTED_BMP));
//    KP_ASSERT(mute_bmp_pars.m_hSliderBmp, KP_E_FILE_NOT_FOUND, GetLastError(), True);
      if(SUCCEEDED(retc)) mute_bmp_pars.m_hSliderBmp = (HBITMAP)LoadImage(GetModuleHandle(0), muted?"gars-2-48.bmp":"gars-1-48.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
      KP_ASSERT(mute_bmp_pars.m_hSliderBmp, KP_E_FILE_NOT_FOUND, muted?"gars-2-48.bmp":"gars-1-48.bmp", False);

      if(SUCCEEDED(retc)) mute_bmp_pars.CalcDimensions();
   }

#if TRUE // #ifndef Debug // Debug rezime kazkodel perpildo steka
   if(m_plpszBmpList && SUCCEEDED(retc))
      if(m_plpszBmpList[0])
         if(m_plpszBmpList[0][0])
            retc = ShowBmp(m_plpszBmpList[0] /* bmp_fname */, bmp_wdt, bmp_hgt, &m_hBitmapWindow, True,
               m_iBitmapCnt, m_plpszBmpList, m_iaBmpTimes,
            /* strstr(bmp_fname, ".mcl")? */ KP_IDI_SLIDER_2_BMP /* :KP_IDI_SLIDER_1_BMP */,
               KPST_ACRO_LOAD_TIME + prol_show_time, // kad pilnai prasisuktø per Acrobato krovimosi laikà
               HWND_DESKTOP, 0, 0,
               IsSoundFileProcessed(prol_fname)?&mute_bmp_pars:NULL, // mute_bmp,
               prod_name, MAKEINTRESOURCE(KP_IDI_MAIN_ICON));
#endif

// start minimized internet Explorer
// if(SUCCEEDED(retc)) rtet = StartIE(); // iðkelta á StartCmd(), nes pjaunasi su pwd ávedimo dialogu – pasileidþia antrà k. ir maximizuotas

// ---------------------------------------
// run prologue
   if(SUCCEEDED(retc)) if((strlen(prol_fname)>0))
      if(strcmp(prol_fname, KPSTART_IEXPLORE) != 0) // "iexplore"
      {
         if(SUCCEEDED(retc)) if(IsSoundFileProcessed(prol_fname))
         {
            if((m_iNumWaveDevs > 0) && (!muted))
            {
               m_bSoundPlaying = True;
               m_RetcPr = StartCmdProcess(prol_fname, KPST_CUR_DIR, &m_lProlThreadId, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
            }
         }
         else
            m_RetcPr = StartCmdProcess(prol_fname, KPST_CUR_DIR, &m_lProlThreadId, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
      }

PutLogMessage_("KpStApp::PlayPrologue() 6 %x", retc);
// ---------------------------------------
// delay for bmp movie/prologue
   if(SUCCEEDED(retc))
      if(
         ((strlen(prol_fname)>0) && SUCCEEDED(m_RetcPr)) ||
         m_plpszBmpList // (strlen(bmp_fname)>0)
        )
      {
PutLogMessage_("KpStApp::PlayPrologue() 6.3 %x", retc);
         if((prol_show_time > 0) && SUCCEEDED(retc))
         {
            retc = KpSleep(prol_show_time*1000, m_hBitmapWindow); // m_hBitmapWindow gali but ir NULL - nieko tokio
PutLogMessage_("KpStApp::PlayPrologue() 6.4 %x", retc);
//          Sleep(prol_show_time*1000);
         }
      }

PutLogMessage_("KpStApp::PlayPrologue() 7 %x", retc);
return(retc);
}


// -----------------------------------------
HRESULT KpStApp::StopSlider(int *piCurrentIncrement)
{
HRESULT retc = S_OK;
KpWnd *bmp_wnd = NULL;
// KpWnd *prog_wnd = NULL;

   KP_ASSERT(piCurrentIncrement, E_INVALIDARG, null, true);

   if(m_hBitmapWindow && SUCCEEDED(retc))
   {
// KpMsgOutF_1("m_hBitmapWindow: %x", m_hBitmapWindow);
      retc = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
      if(bmp_wnd && SUCCEEDED(retc))
      {
// KpMsgOutF_1("bmp_wnd: %x", bmp_wnd);
//       if(bmp_wnd->m_hMDI_Client)
         {
// KpMsgOutF_1("bmp_wnd->m_hMDI_Client: %x", bmp_wnd->m_hMDI_Client);
//          retc = GetCurWindow(&prog_wnd, bmp_wnd->m_hMDI_Client);
//          if(prog_wnd && SUCCEEDED(retc))
            {
// KpMsgOutF_2("prog_wnd: %x prog_wnd->m_iWndXStep_10: %d", prog_wnd, prog_wnd->m_iWndXStep_10);
// KpMsgOutF_1("bmp_wnd->m_iWndXStep_10: %d", bmp_wnd->m_iWndXStep_10);
               *piCurrentIncrement = bmp_wnd /* prog_wnd */->m_iWndXStep_10;
               bmp_wnd /* prog_wnd */->m_iWndXStep_10 = 0;
            }
         }
      }
   }

return(retc);
}


HRESULT KpStApp::ReleaseSlider(int iPreviousIncrement)
{
HRESULT retc = S_OK;
KpWnd *bmp_wnd = NULL;
// KpWnd *prog_wnd = NULL;

   if(m_hBitmapWindow && SUCCEEDED(retc))
   {
      retc = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
      if(bmp_wnd /* prog_wnd */ && SUCCEEDED(retc))
      {
// KpMsgOutF_1("prog_wnd->m_iWndXStep_10: %d", prog_wnd->m_iWndXStep_10);
// KpMsgOutF_1("bmp_wnd->m_iWndXStep_10: %d", bmp_wnd->m_iWndXStep_10);
         bmp_wnd /* prog_wnd */->m_iWndXStep_10 = iPreviousIncrement;
      }
   }

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::StartIE(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static unsigned char prol_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char str_buf[KP_MAX_FNAME_LEN + 1];
bool sh_ie = False;
HKEY key = NULL;
DWORD data_type;
DWORD data_len;
unsigned char *pntd = NULL;

// ---------------------------------------
   if(SUCCEEDED(retc)) retc = GetIniShowIE(&sh_ie);
   if(SUCCEEDED(retc)) retc = GetIniProlFName(prol_fname);

// ---------------------------------------
   if(SUCCEEDED(retc)) if((strlen(prol_fname) > 0))
      if(strcmp(prol_fname, KPSTART_IEXPLORE) == 0) sh_ie = True; // "iexplore"
   if(sh_ie && SUCCEEDED(retc))
      if(GetWindowByName(KPST_IE_WINDOW_NAME, False, NULL) == NULL)
      {
         if(ERROR_SUCCESS == RegCreateKeyEx(HKEY_CLASSES_ROOT, "Applications\\iexplore.exe\\shell\\open\\command",
            0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &key, NULL))
         {
            data_len = KP_MAX_FNAME_LEN;
            if(ERROR_SUCCESS == RegQueryValueEx(key, "", NULL, &data_type, prol_fname, &data_len))
               if(data_type == REG_SZ)
               {
// "C:\Program Files\Internet Explorer\iexplore.exe" %1
                  pntd = strchr(prol_fname, '%');
                  if(pntd) *pntd = Nul;
                  /* retc = */ CutInitTrailSpcs(prol_fname);
                  pntd = prol_fname;
                  if(*pntd == '\"')
                  {
                     pntd = pntd + strlen(prol_fname) - 1;
                     if(pntd > prol_fname)
                     {
                        if(*pntd == '\"')
                        {
                           *pntd = Nul;
                           pntd = prol_fname + 1;
                        }
                        else pntd = prol_fname;
                     }
                  }

// ------------ atsklanda.htm
                  retc0 = S_OK;
                  KP_ASSERT00(GetFullPathName("atsklanda.htm", KP_MAX_FNAME_LEN, (char *)str_buf, NULL), KP_E_SYSTEM_ERROR, null, False);
                  KP_ASSERT00((pntd - prol_fname) + strlen(pntd) + 1 + strlen(str_buf) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, False);
                  if(SUCCEEDED(retc0))
                  {
                     strcat(pntd, " ");
                     strcat(pntd, str_buf);

                  /* m_RetcPr = */ StartCmdProcess(pntd, KPST_CUR_DIR, NULL, NULL, False, SW_MINIMIZE /*  SW_SHOWMINIMIZED */ /* SW_HIDE */);
                  }

               } // if(data_type == REG_SZ)

         } // if(ERROR_SUCCESS == RegCreateKeyEx()

         if(key) RegCloseKey(key);
         key = NULL;

      } // if(GetWindowByName("Windows Internet Explorer", False, NULL) == NULL)

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::StartClipViewer(void)
{
HRESULT retc=S_OK;

#ifdef KPST_USE_CLIPBOARD
FILE *in_file;

   if(SUCCEEDED(retc))
   {
      if(!GetWindowsDirectory((char *)m_lpszClipViewerFName, KP_MAX_FNAME_LEN))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      }
      else
      {
         m_lpszClipViewerFName[KP_MAX_FNAME_LEN]=Nul;
         if(strlen(m_lpszClipViewerFName) + strlen(KPST_CLIP_VWR_SUB_PATH) >=KP_MAX_FNAME_LEN)
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L);
         }
         else
         {
            strcat(m_lpszClipViewerFName, KPST_CLIP_VWR_SUB_PATH);

            in_file=fopen((const char *)m_lpszClipViewerFName, "r");
            if(in_file)
            {
               fclose(in_file);

               if(m_bNormalStart && SUCCEEDED(retc))
               /* retc= */ StartCmdProcess(m_lpszClipViewerFName, KPST_CUR_DIR, &m_lClipViewerThreadId, NULL, False, SW_FORCEMINIMIZE /* SW_SHOWMINIMIZED */);
            }

         } // else // if(strlen(m_lpszClipViewerFName) + strlen(KPST_CLIP_VWR_SUB_PATH) >=KP_MAX_FNAME_LEN)

      } // else // if(!GetWindowsDirectory((char *)m_lpszClipViewerFName, KP_MAX_FNAME_LEN))

   } // if(SUCCEEDED(retc))
#endif

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::DelAttachment(void)
{
HRESULT retc=S_OK;
unsigned char fnam_buf[KP_MAX_FNAME_LEN+KP_MAX_FTYPE_LEN+1];
unsigned char att_ext[KP_MAX_FTYPE_LEN+1];

   if(SUCCEEDED(retc)) retc=GetIniAttExt(att_ext);

   if(SUCCEEDED(retc)) if(strlen(m_lpszAttFname)>0)
   {
      strcpy(fnam_buf, m_lpszAttFname);
      if(SUCCEEDED(retc))
         if(strlen(fnam_buf)+1+strlen(att_ext)>=KP_MAX_FNAME_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         strcat(fnam_buf, ".");
         strcat(fnam_buf, att_ext);

         retc=KpSleep(1000, HWND_DESKTOP); // Sleep(1000);
      }

      if(SUCCEEDED(retc))
         if(remove((const char *)fnam_buf)!=0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null /* fnam_buf */, True, __FILE__, __LINE__, 0L);
   }

return(retc);
}

// -----------------------------------------
HRESULT KpStApp::Detach(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char fnam_buf[KP_MAX_FNAME_LEN+1];
FILE *in_file=NULL;
FILE *out_file=NULL;
// int ch;
unsigned char *pnts;
unsigned char *file_buf = NULL;
long file_len=0L;
long att_offset=0L;
unsigned char att_ext[KP_MAX_FTYPE_LEN+1];

   m_lpszAttFname[0]=Nul;

   if(SUCCEEDED(retc)) retc=GetIniAttOff(&att_offset);
   if(SUCCEEDED(retc)) retc=GetIniAttExt(att_ext);

   if((att_offset>0) && SUCCEEDED(retc))
   {
// ------------------- exe file
      fnam_buf[0]=Nul;
      if(SUCCEEDED(retc)) retc=GetAppName(fnam_buf);

      if(SUCCEEDED(retc))
      {
         in_file=fopen((const char *)fnam_buf, "rb");
         if(in_file==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, null /* m_szExeFile */, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc)) retc=KpGetFileSizeFile(in_file, &file_len);
      if(SUCCEEDED(retc))
      {
         file_len-=att_offset;
         if(file_len<=0)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      KP_NEWA(file_buf, unsigned char, file_len + 1);

      if(SUCCEEDED(retc))
         if(fseek(in_file, att_offset, SEEK_SET)!=0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
         if(fread(file_buf, 1, file_len, in_file)!=file_len)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) if(ferror(in_file))
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc)) retc = EnctBufSimpl(file_buf, file_len);

// ------------------- attachment file
      if(SUCCEEDED(retc)) retc = GetLocalPath(m_lpszAttFname, KP_Temp_Dir, True);

      if(SUCCEEDED(retc)) retc=TvUniFname.Generate(fnam_buf);
      if(SUCCEEDED(retc))
      {
         pnts=strchr(fnam_buf, '.');
         if(pnts) *pnts=Nul;
      }

      if(SUCCEEDED(retc)) if(strlen(m_lpszAttFname)+strlen(fnam_buf)>=KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
      {
         strcat(m_lpszAttFname, fnam_buf);
         strcpy(fnam_buf, m_lpszAttFname);

         if(strlen(fnam_buf)+1+strlen(att_ext)>=KP_MAX_FNAME_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc))
      {
         strcat(fnam_buf, ".");
         strcat(fnam_buf, att_ext);
      }

      if(SUCCEEDED(retc))
      {
         out_file=fopen((const char *)fnam_buf, "wb");
         if(out_file==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null /* fnam_buf */, True, __FILE__, __LINE__, 0L);
      }

#if TRUE
      if(SUCCEEDED(retc))
         if(fwrite(file_buf, 1, file_len, out_file)!=file_len)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
         if(feof(out_file) || ferror(out_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
#else
      if(SUCCEEDED(retc)) while((!feof(in_file)) && SUCCEEDED(retc))
      {
         ch=fgetc(in_file);
         if(ferror(in_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc)) if(!feof(in_file))
         {
            fputc(ch, out_file);
            if(ferror(out_file) || feof(out_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         }
      }
#endif

      if(in_file!=NULL) fclose(in_file);
      in_file=NULL;

      if(out_file!=NULL)
         if(fclose(out_file)!=0)
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
            if(SUCCEEDED(retc)) retc=retc0;
         }
      out_file=NULL;

      if(SUCCEEDED(retc))
      {
         in_file=NULL;
         in_file=fopen((const char *)fnam_buf, "rb");
         if(in_file==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
         else
            fclose(in_file);
         in_file=NULL;
      }

   } // if((att_offset>0) && SUCCEEDED(retc))

   KP_DELETEA(file_buf);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RenewDll(const unsigned char *lpszDllName, const unsigned char *lpszDest)
{
HRESULT retc=S_OK;
unsigned char fnam_buf_dll[KP_MAX_FNAME_LEN+1];
unsigned char fnam_buf_sav[KP_MAX_FNAME_LEN+1];
unsigned char fnam_buf_add[KP_MAX_FNAME_LEN+1];
unsigned char *win_dir;
bool ready_to_copy = False;

   if(SUCCEEDED(retc))
   {
      strcpy(fnam_buf_add, "AddInst\\");
      strcat(fnam_buf_add, lpszDllName);
      strcat(fnam_buf_add, ".DLL");
      retc=CheckFile(fnam_buf_add);
      if(retc==KP_E_DIR_ERROR) retc=S_OK; // jei nera AddInst - nieko nedarom
      else if(SUCCEEDED(retc))
      {
         win_dir=(unsigned char *)getenv("WINDIR");
         if(win_dir==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
         else
         {
            if(SUCCEEDED(retc))
            {
               ready_to_copy = False;

               strcpy(fnam_buf_dll, win_dir);
               strcat(fnam_buf_dll, "\\");
               strcat(fnam_buf_dll, lpszDest);
               strcat(fnam_buf_dll, "\\");
               strcat(fnam_buf_dll, lpszDllName);
               strcat(fnam_buf_dll, ".DLL");
               retc=CheckFile(fnam_buf_dll);
               if(retc==KP_E_DIR_ERROR)
               {
                  ready_to_copy = True; // .dll nera - galim kopijuoti
                  retc=S_OK;
               }
               else if(SUCCEEDED(retc))
               {
                  strcpy(fnam_buf_sav, win_dir);
                  strcat(fnam_buf_sav, "\\");
                  strcat(fnam_buf_sav, lpszDest);
                  strcat(fnam_buf_sav, "\\");
                  strcat(fnam_buf_sav, lpszDllName);
                  strcat(fnam_buf_sav, TEV_SAV_FILE_TYPE); // ".tvs" // ".sav"
// jei *.tvs jau yra - nieko nedarom
                  retc=CheckFile(fnam_buf_sav);
                  if(retc==KP_E_DIR_ERROR)
                  {
                     retc=S_OK;
                     if(!CopyFile((const char *)fnam_buf_dll, (const char *)fnam_buf_sav, False))
                     {
#ifdef Debug
// SYSTEM32 gali ir nebuti
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
                     }
                     else ready_to_copy = True; // kopijuojam, tik jei sekmingai issaugojom
                  }

               } // else // if(retc==KP_E_DIR_ERROR) // retc=CheckFile("system/.dll");

            } // if(SUCCEEDED(retc))

            if(ready_to_copy && SUCCEEDED(retc))
            {
               if(!CopyFile((const char *)fnam_buf_add, (const char *)fnam_buf_dll, False))
               {
#ifdef Debug
// SYSTEM32 gali ir nebuti
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
               }
            }

         } // else // if(win_dir==NULL)

      } // else // if(retc==KP_E_DIR_ERROR)

   } // if(SUCCEEDED(retc))

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RenewDllsAll(void)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"msvcp60",  (const unsigned char *)"SYSTEM");
   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"msvcp60",  (const unsigned char *)"SYSTEM32");
   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"msvcp70",  (const unsigned char *)"SYSTEM");
   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"msvcp70",  (const unsigned char *)"SYSTEM32");
   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"msvcr70",  (const unsigned char *)"SYSTEM");
   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"msvcr70",  (const unsigned char *)"SYSTEM32");

   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"unicows",  (const unsigned char *)"SYSTEM");
   if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"unicows",  (const unsigned char *)"SYSTEM32");

#ifdef Debug
   if((iWindowsVersion==WinUnkn) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
   if((iWindowsVersion<WinCE) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"riched",   (const unsigned char *)"SYSTEM");
      if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"riched",   (const unsigned char *)"SYSTEM32");
      if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"riched20", (const unsigned char *)"SYSTEM");
      if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"riched20", (const unsigned char *)"SYSTEM32");
      if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"riched32", (const unsigned char *)"SYSTEM");
      if(SUCCEEDED(retc)) retc=RenewDll((const unsigned char *)"riched32", (const unsigned char *)"SYSTEM32");
   }

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreDll(const unsigned char *lpszDllName, const unsigned char *lpszDest, HMODULE *phLibHandle)
{
HRESULT retc=S_OK;
unsigned char fnam_buf[KP_MAX_FNAME_LEN+1];
unsigned char fnam_buf_1[KP_MAX_FNAME_LEN+1];
unsigned char *win_dir;

   if(SUCCEEDED(retc)) if(phLibHandle!=NULL) if(*phLibHandle!=NULL)
   {
      if(SUCCEEDED(retc)) if(!FreeLibrary(*phLibHandle))
      {
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
      }
      *phLibHandle=NULL;
   }

// ------------------------
   if(SUCCEEDED(retc))
   {
      win_dir=(unsigned char *)getenv("WINDIR");
      if(win_dir==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      else
      {
         if(SUCCEEDED(retc))
         {
            strcpy(fnam_buf, win_dir);
            strcat(fnam_buf, "\\");
            strcat(fnam_buf, lpszDest);
            strcat(fnam_buf, "\\");
            strcat(fnam_buf, lpszDllName);
            strcat(fnam_buf, TEV_SAV_FILE_TYPE); // ".tvs" // ".sav"
            retc=CheckFile(fnam_buf);
            if(retc==KP_E_DIR_ERROR) retc=S_OK;
            else if(SUCCEEDED(retc))
            {
               strcpy(fnam_buf_1, win_dir);
               strcat(fnam_buf_1, "\\");
               strcat(fnam_buf_1, lpszDest);
               strcat(fnam_buf_1, "\\");
               strcat(fnam_buf_1, lpszDllName);
               strcat(fnam_buf_1, ".DLL");
               if(!CopyFile((const char *)fnam_buf, (const char *)fnam_buf_1, False))
               {
// jeigu failas atviras - neiseis
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
               }
               else
//             if(SUCCEEDED(retc))
               {
                  if(!DeleteFile((const char *)fnam_buf))
                  {
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
                  }
               }
            }
         }

      } // else // if(win_dir==NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreDllsAll(void)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"msvcp60", (const unsigned char *)"SYSTEM", NULL);
   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"msvcp60", (const unsigned char *)"SYSTEM32", NULL);
   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"msvcp70", (const unsigned char *)"SYSTEM", NULL);
   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"msvcp70", (const unsigned char *)"SYSTEM32", NULL);
   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"msvcr70", (const unsigned char *)"SYSTEM", NULL);
   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"msvcr70", (const unsigned char *)"SYSTEM32", NULL);

   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"unicows",  (const unsigned char *)"SYSTEM", &hUnicowsLib);
   if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"unicows",  (const unsigned char *)"SYSTEM32", &hUnicowsLib);

#ifdef Debug
   if((iWindowsVersion==WinUnkn) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
   if((iWindowsVersion<WinCE) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"riched",   (const unsigned char *)"SYSTEM", &hRichEditLib);
      if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"riched",   (const unsigned char *)"SYSTEM32", &hRichEditLib);
      if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"riched20", (const unsigned char *)"SYSTEM", &hRichEditLib);
      if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"riched20", (const unsigned char *)"SYSTEM32", &hRichEditLib);
      if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"riched32", (const unsigned char *)"SYSTEM", &hRichEditLib);
      if(SUCCEEDED(retc)) retc=RestoreDll((const unsigned char *)"riched32", (const unsigned char *)"SYSTEM32", &hRichEditLib);
   }

return(retc);
}


//-------------------------------------------
#if FALSE
// cia buvo be reikalo kopijuojama ant tikro AcroRd32.exe - uztenka tik paleist is bet kur
// be to buvo forsuojamas rasymas i c:\arkim\rezultatai
// kataloge prie start.exe turedavo buti ema.exe
// (buvo #define KPST_EMA_FNAME ((const unsigned char *)"ema.exe"))
HRESULT KpStApp::InitAcroSaveAs(void)
{
HRESULT retc=S_OK;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
static unsigned char cmd_path[KP_MAX_FILE_LIN_WDT+1];
static unsigned char cmd_buf[KP_MAX_FNAME_LEN+1];
static unsigned char cmd_buf_1[KP_MAX_FNAME_LEN+1];
unsigned char *acro_fname_ptr;
static unsigned char rez_fullname[KP_MAX_FNAME_LEN+1];
static unsigned char rez_disk[KP_MAX_FNAME_LEN+1];
static unsigned char rez_path[KP_MAX_FNAME_LEN+1];
static unsigned char rez_name[KP_MAX_FNAME_LEN+1];
static unsigned char rez_type[KP_MAX_FTYPE_LEN+1];
HANDLE ema_proc;

   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fullname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fullname);

   if(SUCCEEDED(retc)) if(SUCCEEDED(CheckFile(KPST_EMA_FNAME)) && (iWindowsVersion>=WinNT))
   {

// surandam AcroRd32.exe vieta
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_path, cmd_str);
         acro_fname_ptr = strstr(cmd_path, KPST_ACROREAD_FNAME_SHORT);
         if(acro_fname_ptr==NULL)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) *acro_fname_ptr=Nul;

// AcroRd32.exe.sav atstatom atgal, jei buvo nuluzes po paskutinio issaugojimo
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_buf, cmd_path);
         strcat(cmd_buf, KPST_ACROREAD_FNAME);

         strcpy(cmd_buf_1, cmd_path);
         strcat(cmd_buf_1, KPST_ACROREAD_FNAME);
         strcat(cmd_buf_1, SAV_FILE_TYPE);

         if(SUCCEEDED(CheckFile(cmd_buf_1)))
         {
            if(!DeleteFile((char const *)cmd_buf))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
               retc=KP_E_ACCESS_DENIED;
            }
            if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP);

            if(SUCCEEDED(retc))
               if(!MoveFile((char const *)cmd_buf_1, (char const *)cmd_buf))
               {
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
                  retc=KP_E_ACCESS_DENIED;
               }
         }
      }
      if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP);

// issaugojam AcroRd32.exe i AcroRd32.exe.sav
      if(SUCCEEDED(retc))
      {
//       strcpy(cmd_buf, cmd_path);
//       strcat(cmd_buf, KPST_ACROREAD_FNAME);

//       strcpy(cmd_buf_1, cmd_path);
//       strcat(cmd_buf_1, KPST_ACROREAD_FNAME);
//       strcat(cmd_buf_1, SAV_FILE_TYPE);

         if(!MoveFile((const char *)cmd_buf, (const char *)cmd_buf_1))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            retc=KP_E_ACCESS_DENIED;
         }
      }
      if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP);

// kopijuojam ema.exe ant AcroRd32.exe
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_buf_1, KPST_EMA_FNAME);

         if(!CopyFile((const char *)cmd_buf_1, (const char *)cmd_buf, True))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            retc=KP_E_ACCESS_DENIED;
         }
      }
      if(SUCCEEDED(retc)) retc=KpSleep(200, HWND_DESKTOP);

// randam rezultatu failo vieta
      if(SUCCEEDED(retc))
         retc=TvFnameSplit(rez_disk, rez_path, rez_name, rez_type, rez_fullname);

// paleidziam ema.exe
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_buf, cmd_path);
         strcat(cmd_buf, KPST_ACROREAD_FNAME);
         strcat(cmd_buf, " \"");
         strcat(cmd_buf, rez_disk);
         strcat(cmd_buf, rez_path);
         strcat(cmd_buf, "\"");

// KpMsgOut(cmd_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

         retc = StartCmdProcess(cmd_buf, KPST_CUR_DIR, NULL, &ema_proc, True, SW_SHOWNORMAL /* SW_SHOWDEFAULT SW_SHOWMAXIMIZED SW_MAXIMIZE SW_FORCEMAXIMIZE */);

//       retc = StartCmdProcess(cmd_str, KPST_CUR_DIR, NULL, &ema_proc, True, SW_SHOWNORMAL /* SW_SHOWDEFAULT SW_SHOWMAXIMIZED SW_MAXIMIZE SW_FORCEMAXIMIZE */);
      }

#if FALSE
char str_buf[100];
sprintf(str_buf, "%d %d %d", iWindowsVersion, WinNT, KPST_EMA_OKBUT);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

      if(SUCCEEDED(retc)) retc = WaitForWindow(KPST_EMA_WNAME, null, KPST_EMA_OKBUT, 0, NULL, NULL, 0L, NULL);

      if(SUCCEEDED(retc)) retc = WaitForProcessEnd(ema_proc, NULL);
      if(SUCCEEDED(retc)) retc = KpSleep(1000, HWND_DESKTOP);

// AcroRd32.exe.sav atstatom atgal
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_buf, cmd_path);
         strcat(cmd_buf, KPST_ACROREAD_FNAME);

         strcpy(cmd_buf_1, cmd_path);
         strcat(cmd_buf_1, KPST_ACROREAD_FNAME);
         strcat(cmd_buf_1, SAV_FILE_TYPE);

         if(SUCCEEDED(CheckFile(cmd_buf_1)))
         {
            if(!DeleteFile((char const *)cmd_buf))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
               retc=KP_E_ACCESS_DENIED;
            }
            if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP);

            if(SUCCEEDED(retc))
               if(!MoveFile((char const *)cmd_buf_1, (char const *)cmd_buf))
               {
//                retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
                  retc=KP_E_ACCESS_DENIED;
               }
         }
         else
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      }
      if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP);
   }

   if(retc==KP_E_ACCESS_DENIED) retc=S_OK;

return(retc);
}
#endif

// ---------------------------------------
// cia paleidziamas ema.exe, pervadintas i AcroRd32.exe
// forsuojamas AcroRd32.exe Save As rasymas i My Documents
// kataloge prie start.exe turi buti AcroRd32.exe (pervadintas is ema.exe)
// #define KPST_EMA_FNAME ((const unsigned char *)"AcroRd32.exe")
HRESULT KpStApp::InitAcroSaveAs(void)
{
HRESULT retc=S_OK;
static unsigned char cmd_buf[KP_MAX_FNAME_LEN+1];
static unsigned char my_docs_path[KP_MAX_FNAME_LEN+1];
HANDLE ema_proc;
int ii;

   if(SUCCEEDED(retc)) if(SUCCEEDED(CheckFile(KPST_EMA_FNAME)) && (iWindowsVersion>=WinNT))
   {

// randam My Documents kelia
      if(SUCCEEDED(retc)) retc=GetLocalPath(my_docs_path, KP_My_Documents);
      if(SUCCEEDED(retc))
      {
         ii=strlen(my_docs_path);
         if(ii>0) if(my_docs_path[ii-1]=='\\') my_docs_path[ii-1]=Nul;
      }

// paleidziam ema.exe
      if(SUCCEEDED(retc))
      {
         strcpy(cmd_buf, KPST_EMA_FNAME);
         strcat(cmd_buf, " \"");
         strcat(cmd_buf, my_docs_path);
         strcat(cmd_buf, "\"");

// KpMsgOut(cmd_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

         retc = StartCmdProcess(cmd_buf, KPST_CUR_DIR, NULL, &ema_proc, True, SW_SHOWNORMAL /* SW_SHOWDEFAULT SW_SHOWMAXIMIZED SW_MAXIMIZE SW_FORCEMAXIMIZE */);

//       retc = StartCmdProcess(cmd_str, KPST_CUR_DIR, NULL, &ema_proc, True, SW_SHOWNORMAL /* SW_SHOWDEFAULT SW_SHOWMAXIMIZED SW_MAXIMIZE SW_FORCEMAXIMIZE */);
      }

#if FALSE
char str_buf[100];
sprintf(str_buf, "%d %d %d", iWindowsVersion, WinNT, KPST_EMA_OKBUT);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

      if(SUCCEEDED(retc)) retc = WaitForWindow(KPST_EMA_WNAME, null, KPST_EMA_OKBUT, 0, NULL, NULL, 0L, NULL);

      if(SUCCEEDED(retc)) retc = WaitForProcessEnd(ema_proc, NULL);
      if(SUCCEEDED(retc)) retc = KpSleep(1000, HWND_DESKTOP);
   }

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::InitAcro(int iVers)
{
HRESULT retc=S_OK;
bool eboard = False;
// int wnd_y;
// HDC dc = NULL;
HKEY key = NULL;
LONG retw = ERROR_SUCCESS;
static unsigned char vol_name[KP_MAX_FNAME_LEN+1];
static unsigned char str_buf[KP_MAX_FNAME_LEN+1];
unsigned char *pntd;

   if(SUCCEEDED(retc)) retc = GetIniEboard(&eboard);
   if(SUCCEEDED(retc)) retc = GetIniVolName(vol_name);


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0] // patikrint, ar susikuria??!!!

   if((iVers >= 600) && (iVers < 900))
   {

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AdsInReader] // Tado.5c9

// "bShowAds"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdsInReader", "bShowAds", (DWORD)0);


// if(iVers < 700)
      {

// "sAdsLastUpdate"=hex:32,30,30,38,30,38,31,33,30,38,34,33,31,31,5a,00
// "20080813111803Z"
// TUX_XFS nëra
         if(eboard && SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdsInReader", "sAdsLastUpdate", "20080813111803Z");

      } // if(iVers < 700)

   } // if((iVers >= 600) && (iVers < 900))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AdobeViewer]

// kad neklaustu licenzijos
// "EULA"=dword:00000001
   if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "EULA", 1);


   if(iVers < 600)
   {

// kad neklaustu, ar nori readeri prijungt prie eksplorerio
// "BrowserCheck"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "BrowserCheck", (DWORD)0);

   } // if(iVers < 600)


   if((iVers >= 600) && (iVers < 900))
   {

// kad maksimizuotu langa
// "MaxApp"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "MaxApp", 1);


      if(iVers < 700)
      {

// kad maksimizuotø dokumentà - projektas pprc
// iðmesti parametrà "MaxDoc"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc))
         {
            if(ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Adobe\\Acrobat Reader\\6.0\\AdobeViewer",
                  0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &key, NULL))
            {
               retc = KP_E_KWD_NOT_FOUND;
//             retc=KpErrorProc.OutputErrorMessage(retc, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
            {
               retw = RegDeleteValue(key, "MaxDoc");
//             if(retw != ERROR_SUCCESS)
//                retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
            }

            if(key) RegCloseKey(key);
            key = NULL;

            retc = S_OK;
         }

      } // if(iVers < 700)


//    if(iVers < 700)
      {

         if(eboard && SUCCEEDED(retc))
         {
// "DialogX0"=dword:000000cf
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogX0", 0x0000008a);

// "DialogY0"=dword:000000cf
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogY0", 0x0000008a); // 0x000000cf ????

// "DialogW0"=dword:00000438
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogW0", 0x00000438);

// "DialogH0"=dword:0000027a
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogH0", 0x0000027a);

// "DialogX1"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogX1", 0xffff8000);

// "DialogY1"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogY1", 0xffff8000);

// "DialogW1"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogW1", 0xffff8000);

// "DialogH1"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogH1", 0xffff8000);

// "DialogX2"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogX2", 0xffff8000);

// "DialogY2"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogY2", 0xffff8000);

// "DialogW2"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogW2", 0xffff8000);

// "DialogH2"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogH2", 0xffff8000);

// "DialogX3"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogX3", 0xffff8000);

// "DialogY3"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogY3", 0xffff8000);

// "DialogW3"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogW3", 0xffff8000);

// "DialogH3"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogH3", 0xffff8000);

// "DialogX4"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogX4", 0xffff8000);

// "DialogY4"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogY4", 0xffff8000);

// "DialogW4"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogW4", 0xffff8000);

// "DialogH4"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogH4", 0xffff8000);

// "DialogX5"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogX5", 0xffff8000);

// "DialogY5"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogY5", 0xffff8000);

// "DialogW5"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogW5", 0xffff8000);

// "DialogH5"=dword:ffff8000
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "DialogH5", 0xffff8000);

// "xRes"=dword:000005a0
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "xRes", 0x000005a0);

// "yRes"=dword:00000384
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "yRes", 0x00000384);

         } // if(eboard && SUCCEEDED(retc))

      } // if(iVers < 700)

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVAlert] // patikrint, ar susikuria??!!!

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVAlert\cCheckbox]

// "iwarnFieldsWillNotBeSaved"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVAlert\\cCheckbox", "iwarnFieldsWillNotBeSaved", 1);

// "iexitWithExternalDocsOpen"=dword:00000001 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVAlert\\cCheckbox", "iexitWithExternalDocsOpen", 1);

// kad nepasakotu kazko apie paveikslus
// "iPictureTasksFeaturesNotice"=dword:00000001 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVAlert\\cCheckbox", "iPictureTasksFeaturesNotice", 1);


//    if(iVers < 700)
      {

// "iUBDontShowAgain"=dword:00000001
         if(/* eboard && */ SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVAlert\\cCheckbox", "iUBDontShowAgain", 1);

      } // if(iVers < 700)

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral] // Tado.5c9

// "bToolbarsLocked"=dword:00000001 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "bToolbarsLocked", (DWORD)0); // 1);

   } // if((iVers >= 600) && (iVers < 900))


   if(iVers >= 600)
   {
//    if(iVers < 700)
      {

// "bLastExitNormal"=dword:00000001
// TUX_XFS nëra
         if(/* eboard && */ SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "bLastExitNormal", 1);

// "sInDocTabs"=hex:2a,42,6f,6f,6b,6d,61,72,6b,73,2c,53,69,67,6e,61,74,75,72,65,73,2c,4f,70,74,43,6f,6e,74,2c,54,68,75,6d,62,6e,61,69,6c,73,00
// "*Bookmarks,Signatures,OptCont,Thumbnails,AnnotManager."
// if(eboard && SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "sInDocTabs", "*Bookmarks,Signatures,OptCont,Thumbnails,AnnotManager.");
// èia dël bookmarkø
// "sInDocTabs"=hex:2a,42,6f,6f,6b,6d,61,72,6b,73,2c,54,68,75,6d,62,6e,61,69,6c,73,00
// "*Bokmarks,Thumbnails"
// TUX_XFS nëra
// if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "sInDocTabs", "*Bookmarks,Thumbnails");

      } // if(iVers < 700)

   } // if(iVers >= 600)


   if((iVers >= 600) && (iVers < 900))
   {
      if(iVers >= 700)
      {
// Tadas MIMOK5_70 2011.05.05
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral]
// "bMDCEShowInstructions"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "bMDCEShowInstructions", (DWORD)0);

      } // if(iVers >= 700)


      if(iVers < 700)
      {

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars] // patikrint, ar susikuria??!!!

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c0]

// "sToolBarName"=hex:46,69,6c,65,00 // "File"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "sToolBarName", "File");

// "bHidden"=dword:00000001 // 00000000
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "bExternal", (DWORD)0);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "iOffset", (DWORD)0);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "iStackNum", (DWORD)0);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowBottom", (DWORD)0);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowLeft", (DWORD)0);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowRight", (DWORD)0);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowTop", (DWORD)0);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// Tadas 2009.07.28
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c1]
// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c1", "bHidden", 1);

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c11]

// "sToolBarName"=hex:4e,61,76,69,67,61,74,69,6f,6e,00 // "Navigation"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "sToolBarName", "Navigation");

// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "bExternal", (DWORD)0);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "iOffset", (DWORD)0);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "iStackNum", (DWORD)0);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowBottom", (DWORD)0);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowLeft", (DWORD)0);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowRight", (DWORD)0);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowTop", (DWORD)0);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c12]

// "sToolBarName"=hex:4e,61,76,69,67,61,74,69,6f,6e,00 // "Navigation"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "sToolBarName", "Navigation");

// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "iDockPosition"=dword:00000004
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iDockPosition", 4);

// "bExternal"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "bExternal", 1);

// "iOffset"=dword:7fffffff
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iOffset", 0x7fffffff);

// "iOrder"=dword:00000005
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iOrder", 0x00000005);

// "iStackNum"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iStackNum", 0x00000001);

// "iWindowBottom"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowBottom", 0x80000000);

// "bWindowHidden"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "bWindowHidden", 1);

// "iWindowLeft"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowLeft", 0x80000000);

// "iWindowRight"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowRight", 0x80000000);

// "iWindowTop"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowTop", 0x80000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c13]

// "sToolBarName"=hex:50,72,6f,70,65,72,74,69,65,73,00 // "Properties"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "sToolBarName", "Properties");

// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "bExternal", (DWORD)0);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "iOffset", (DWORD)0);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "iStackNum", (DWORD)0);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowBottom", (DWORD)0);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowLeft", (DWORD)0);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowRight", (DWORD)0);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowTop", (DWORD)0);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c14]

// "sToolBarName"=hex:50,72,6f,70,65,72,74,69,65,73,00 // "Properties"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "sToolBarName", "Properties");

// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "iDockPosition"=dword:00000004
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iDockPosition", 0x00000004);

// "bExternal"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "bExternal", 1);

// "iOffset"=dword:7fffffff
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iOffset", 0x7fffffff);

// "iOrder"=dword:00000005
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iOrder", 0x00000005);

// "iStackNum"=dword:00000002
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iStackNum", 0x00000002);

// "iWindowBottom"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowBottom", 0x80000000);

// "bWindowHidden"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "bWindowHidden", 1);

// "iWindowLeft"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowLeft", 0x80000000);

// "iWindowRight"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowRight", 0x80000000);

// "iWindowTop"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowTop", 0x80000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c15]

// "sToolBarName"=hex:43,6f,6d,6d,65,6e,74,69,6e,67,00 // "Commenting"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "sToolBarName", "Commenting");

// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "bExternal", (DWORD)0);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "iOffset", (DWORD)0);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "iStackNum", (DWORD)0);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowBottom", (DWORD)0);

// "bWindowHidden"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "bWindowHidden", 1);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowLeft", (DWORD)0);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowRight", (DWORD)0);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowTop", (DWORD)0);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c16]

// "sToolBarName"=hex:43,6f,6d,6d,65,6e,74,69,6e,67,00 // "Commenting"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "sToolBarName", "Commenting");

// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "iDockPosition"=dword:00000004
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iDockPosition", 4);

// "bExternal"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "bExternal", 1);

// "iOffset"=dword:7fffffff
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iOffset", 0x7fffffff);

// "iOrder"=dword:0000000a
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iOrder", 0x0000000a);

// "iStackNum"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iStackNum", 0x00000001);

// "iWindowBottom"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowBottom", 0x80000000);

// "bWindowHidden"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "bWindowHidden", 1);

// "iWindowLeft"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowLeft", 0x80000000);

// "iWindowRight"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowRight", 0x80000000);

// "iWindowTop"=dword:80000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowTop", 0x80000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c17]

// "sToolBarName"=hex:4a,53,54,6f,6f,6c,42,61,72,00 // "JSToolBar"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "sToolBarName", "JSToolBar");

// "bHidden"=dword:00000000 // 00000001
// TUX_XFS 00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "bHidden", (DWORD)0);

         if(eboard && SUCCEEDED(retc))
         {
// "iDockPosition"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iDockPosition", 1);

// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "bExternal", (DWORD)0);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iOffset", (DWORD)0);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iStackNum", (DWORD)0);

#if FALSE
            if(SUCCEEDED(retc))
            {
               wnd_y = iWndCaptionHgt;

               dc=GetDC(HWND_DESKTOP);
               if(dc==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
               else
                  wnd_y = GetDeviceCaps(dc, VERTRES) - 24 - iWndCaptionHgt;
            }
#endif

// #if FALSE
// "iWindowBottom"=dword:00000037
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowBottom", 0x0000006e); // 0x000000ca); // wnd_y + 24);

// "iWindowTop"=dword:00000013
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowTop", 0x0000004a); // 0x000000a6); // wnd_y);
// #endif

// "iWindowLeft"=dword:00000000
// "iWindowLeft"=dword:00000036
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowLeft", 0x00000036); // 0x0000092);

// "iWindowRight"=dword:00000400
// "iWindowRight"=dword:0000045e
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowRight", 0x0000045e); // 0x000004ba);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c18]

// "sToolBarName"=hex:4a,53,54,6f,6f,6c,42,61,72,00 // "JSToolBar"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "sToolBarName", "JSToolBar");

// "bHidden"=dword:00000000 // 00000001
// TUX_XFS 00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "bHidden", (DWORD)0);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "bExternal", 1);

// "bInDoc"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "bInDoc", 1);

// "iLayout"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iLayout", 1);

// "iOffset"=dword:7fffffff
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iOffset", 0x7fffffff);

// "iOrder"=dword:00000032
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iOrder", 0x00000032);

// "iStackNum"=dword:00000001
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iStackNum", 0x00000001);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowBottom", (DWORD)0x00000000);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowLeft", (DWORD)0x00000000);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowRight", (DWORD)0x00000000);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowTop", (DWORD)0x00000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c2]

// "sToolBarName"=hex:42,61,73,69,63,54,6f,6f,6c,73,00 // "BasicTools"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "sToolBarName", "BasicTools");

// "bHidden"=dword:00000001 // 00000000
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "bExternal", (DWORD)0x00000000);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "iOffset", (DWORD)0x00000000);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "iStackNum", (DWORD)0x00000000);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowBottom", (DWORD)0x00000000);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowLeft", (DWORD)0x00000000);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowRight", (DWORD)0x00000000);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowTop", (DWORD)0x00000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// Tadas 2009.07.28
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c3]
// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c3", "bHidden", 1);

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c4]

// "sToolBarName"=hex:56,69,65,77,69,6e,67,00 // "Viewing"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "sToolBarName", "Viewing");

// "bHidden"=dword:00000001 // 00000000
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "bExternal", (DWORD)0x00000000);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "iOffset", (DWORD)0x00000000);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "iStackNum", (DWORD)0x00000000);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowBottom", (DWORD)0x00000000);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowLeft", (DWORD)0x00000000);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowRight", (DWORD)0x00000000);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowTop", (DWORD)0x00000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// Tadas 2009.07.28
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c5]
// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c5", "bHidden", 1);

// ------------------------------------
// Tadas 2009.07.28
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c6]
// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c6", "bHidden", 1);

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c7]

// "sToolBarName"=hex:52,6f,74,61,74,65,00 // "Rotate"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "sToolBarName", "Rotate");

// "bHidden"=dword:00000001 // 00000000
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "bExternal", (DWORD)0x00000000);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "iOffset", (DWORD)0x00000000);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "iStackNum", (DWORD)0x00000000);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowBottom", (DWORD)0x00000000);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowLeft", (DWORD)0x00000000);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowRight", (DWORD)0x00000000);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowTop", (DWORD)0x00000000);

         } // if(eboard && SUCCEEDED(retc))


// ------------------------------------
// Tadas 2009.07.28
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c8]
// "bHidden"=dword:00000001
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c8", "bHidden", 1);

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cToolbars\c9]

// "sToolBarName"=hex:54,61,73,6b,73,00 // "Tasks"
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "sToolBarName", "Tasks");

// "bHidden"=dword:00000001 // 00000000
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "bHidden", 1);

         if(eboard && SUCCEEDED(retc))
         {
// "bExternal"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "bExternal", (DWORD)0x00000000);

// "iOffset"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "iOffset", (DWORD)0x00000000);

// "iStackNum"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "iStackNum", (DWORD)0x00000000);

// "iWindowBottom"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowBottom", (DWORD)0x00000000);

// "iWindowLeft"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowLeft", (DWORD)0x00000000);

// "iWindowRight"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowRight", (DWORD)0x00000000);

// "iWindowTop"=dword:00000000
// TUX_XFS nëra
            if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowTop", (DWORD)0x00000000);

         } // if(eboard && SUCCEEDED(retc))

      } // if(iVers < 700)


// -------------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\FeatureLockdown] // Tado.5c9

// "bShowAdsAllow"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FeatureLockdown", "bShowAdsAllow", (DWORD)0);


// "bUpdater"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FeatureLockdown", "bUpdater", (DWORD)0);


// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\FormsPrefs]

// "bAutoCompleteOnTab"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bAutoCompleteOnTab", (DWORD)0);

// "bFocusRect"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bFocusRect", (DWORD)0);

// "bInlineAutoComplete"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bInlineAutoComplete", (DWORD)0);

// "bRecordNewEntries"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bRecordNewEntries", (DWORD)0);

// "bRuntimeHighlight"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bRuntimeHighlight", (DWORD)0);

// "bRuntimeShowOverflow"=dword:00000001 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bRuntimeShowOverflow", 1);

// "bShowDropDown"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bShowDropDown", (DWORD)0);

// "bStoreNumericEntries"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bStoreNumericEntries", (DWORD)0);

// "bUserAskedToEnableAutoComplete"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FormsPrefs", "bUserAskedToEnableAutoComplete", 1);

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\JSPrefs] // Tado.5c9

// "bEnableJS"=dword:00000001 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "JSPrefs", "bEnableJS", 1);

// if(iVers == 700)
   {
// Tadas 2013-02-26 dël KDK neuþsidarymo
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "JSPrefs", "iExceptions", (DWORD)0);
   }

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\Originals]

// "bDisplayAboutDialog"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bDisplayAboutDialog", (DWORD)0);

// "iTrustedMode"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "iTrustedMode", (DWORD)0);

// "bBrowserIntegration"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bBrowserIntegration", (DWORD)0);

// "bBrowserCheck"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bBrowserCheck", (DWORD)0);

// "bSkipDeleteWarnings"=dword:00000001 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bSkipDeleteWarnings", 1);

//    if(iVers < 700)
      {

// "sProofingSpace"=hex:55,2e,53,2e,20,57,65,62,20,43,6f,61,74,65,64,20,28,53,57,4f,50,29,20,76,32,00
// "U.S. Web Coated (SWOP) v2"
// TUX_XFS nëra
         if(eboard && SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "sProofingSpace", "U.S. Web Coated (SWOP) v2");

      } // if(iVers < 700)

// ------------------------------------
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\Updater] // Tado.5c9

// "bShowAutoUpdateConfDialog"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Updater", "bShowAutoUpdateConfDialog", (DWORD)0);

// "bShowNotifDialog"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Updater", "bShowNotifDialog", (DWORD)0);

// "iUpdateFrequency"=dword:00000000 // Tado.5c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Updater", "iUpdateFrequency", (DWORD)0);

//    KpSleep(5000, m_hBitmapWindow); // eboard ka_ko kartais nesuveikia
//    KpMsgOut("InitAcro60()", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);


// ---------------------------------------
// bookmarkai

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral]
// "sInDocTabs"=hex:2a,42,6f,6f,6b,6d,61,72,6b,73,00
// "*Bookmarks"
// TUX_XFS nëra
      if(iVers < 700)
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "sInDocTabs", "*Bookmarks");

      if(iVers < 700)
      {
HDC dc;
int desktop_dx = 1600;
int font_size = 2;
HRESULT retc0 = S_OK;
bool hide_bkmrks = False;

         if(SUCCEEDED(retc)) retc = GetIniHideBkmrks(&hide_bkmrks);

         if(SUCCEEDED(retc))
         {
            dc = GetDC(HWND_DESKTOP);
            if(dc == NULL)
            {
#ifdef Debug
               retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
               retc0 = KP_E_SYSTEM_ERROR;
            }

            if(SUCCEEDED(retc0))
            {
               desktop_dx = GetDeviceCaps(dc, HORZRES);

//             font_size = (desktop_dx - 800) / 200;
               font_size = (desktop_dx - 800) / 400;
               if(font_size < 0) font_size = 0;
               if(font_size > 2) font_size = 2;

               m_iBkmrkFontSize = font_size;
            }
         }

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVBookmark]
// "iFontSize"=dword:00000002
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVBookmark", "iFontSize", font_size); // 2);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cPalettes\c0]
// "iBottom"=dword:00000122
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "iBottom", 0x00000122);
// "iLeft"=dword:000003fe
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "iLeft", 0x000003fe);
// "bMinimized"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "bMinimized", (DWORD)0x00000000);
// "iRight"=dword:0000057a
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "iRight", 0x0000057a);
// "sTabs"=hex:2a,41,72,74,69,63,6c,65,73,00
// "*Articles"
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "sTabs", "*Articles");
// "iTop"=dword:00000078
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "iTop", 0x00000078);
// "bVisible"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c0", "bVisible", (DWORD)0x00000000);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cPalettes\c1]
// "iBottom"=dword:0000010c
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c1", "iBottom", 0x0000010c);
// "iLeft"=dword:000004fd
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c1", "iLeft", 0x000004fd);
// "bMinimized"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c1", "bMinimized", (DWORD)0x00000000);
// "iRight"=dword:00000575
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c1", "iRight", 0x00000575);
// "sTabs"=hex:2a,53,69,67,6e,61,74,75,72,65,73,00
// "*Signatures"
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c1", "sTabs", "*Signatures");
// "iTop"=dword:00000083
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c1", "iTop", 0x00000083);
// "bVisible"=dword:00000000

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cPalettes\c2]
// "iBottom"=dword:00000113
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "iBottom", 0x00000113);
// "iLeft"=dword:000004f0
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "iLeft", 0x000004f0);
// "bMinimized"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "bMinimized", (DWORD)0x00000000);
// "iRight"=dword:00000568
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "iRight", 0x00000568);
// "sTabs"=hex:2a,4f,70,74,43,6f,6e,74,00
// "*OptCont"
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "sTabs", "*OptCont");
// "iTop"=dword:0000008a
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "iTop", 0x0000008a);
// "bVisible"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c2", "bVisible", (DWORD)0x00000000);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\AVGeneral\cPalettes\c3]
// "iBottom"=dword:00000112
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "iBottom", 0x00000112);
// "iLeft"=dword:000004f4
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "iLeft", 0x000004f4);
// "bMinimized"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "bMinimized", (DWORD)0x00000000);
// "iRight"=dword:0000056c
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "iRight", 0x0000056c);
// "sTabs"=hex:2a,54,68,75,6d,62,6e,61,69,6c,73,00
// "*Thumbnails"
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "sTabs", "*Thumbnails");
// "iTop"=dword:00000089
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "iTop", 0x00000089);
// "bVisible"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cPalettes\\c3", "bVisible", (DWORD)0x00000000);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\Originals]
// "iDefaultSplitterPos"=dword:0000015c
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "iDefaultSplitterPos", desktop_dx / 4); // 0x0000015c);
// "bBookmarkShowLocation"=dword:00000000
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bBookmarkShowLocation", (DWORD)0x00000000);
// "bMinimizeBookmarks"=dword:00000001
// vëliavëlë "Hide bookmarks after use"
// TUX_XFS nëra
         if(hide_bkmrks && SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bMinimizeBookmarks", 0x00000001);

// ----------------------------- 2009.07.23 Tadas
// nustatyt MIMOKO papildomø puslapiø Open dialogo pradiná katalogà?
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\Appearance]
// "tFile"=hex:2f,51,2f,4d,61,6e,6f,5f,4d,61,74,61,75,35,65,2f,78,37,2e,70,64,66,\00
// "/Q/Mano_Matau5e/x7.pdf" // Q - atmintuko raidë
// TUX_XFS nëra
         if(SUCCEEDED(retc))
         {
            retc0 = S_OK;
            if(strlen("//Mano_/x7.pdf") + strlen(m_lpszFlashDevName) + strlen(vol_name) >= KP_MAX_FNAME_LEN)
               retc0 = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, False, __FILE__, __LINE__, 0L, NULL, False);
            if(SUCCEEDED(retc0))
            {
               strcpy(str_buf, "/");
               strcat(str_buf, m_lpszFlashDevName);
               pntd = strchr(str_buf, ':'); if(pntd) *pntd = Nul;
               strcat(str_buf, "/Mano_");
               strcat(str_buf, vol_name);
               strcat(str_buf, "/x7.pdf");

               retc = KpRegSetValueAcro(iVers, "Appearance", "tFile", (const char *)str_buf);
            }
         }

// "iPage"=dword:00000001
// TUX_XFS nëra
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Appearance", "iPage", 0x00000001);

      } // if(iVers < 700)


// ------------------------------------  Tadas 2009.11.19
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\6.0\TaskButtons]
// "iCommentTask"=dword:00000000
// "iFillInTask"=dword:00000000
// "iPictureTasks"=dword:00000000
// "iSignTask"=dword:00000000
// "iNewDocumentTask"=dword:00000000
// "iEBookTask"=dword:00000000
//
// ------------------------------------  Tadas 2009.12.29
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\TaskButtons]
// "iEBookTask"=dword:00000000
// "iCommentTask"=dword:00000000
// "iFormTasks"=dword:00000000
// "iPictureTasks"=dword:00000000
// "iSignTask"=dword:00000000
//
// TUX_XFS nëra
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iCommentTask", (DWORD)0L);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iFillInTask", (DWORD)0L);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iPictureTasks", (DWORD)0L);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iSignTask", (DWORD)0L);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iNewDocumentTask", (DWORD)0L);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iEBookTask", (DWORD)0L);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TaskButtons", "iFormTasks", (DWORD)0L);

   } // if((iVers >= 600) && (iVers < 900))

   if((iVers >= 700) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cBasicTools\\cPositions\\cInternal",          "bWindowHidden", DWORD(0x00000001)); // c2
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cCommenting\\cPositions\\cInternal",          "bWindowHidden", DWORD(0x00000001)); // c15, c16
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cCommentPanelToolbar\\cPositions\\cInternal", "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cData\\cPositions\\cInternal",                "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFile\\cPositions\\cInternal",                "bWindowHidden", DWORD(0x00000001)); // c0
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFileAttachmentFlyout\\cPositions\\cInternal","bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cInternal",                "bWindowHidden", DWORD(0x00000001));
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cHelpToolbar\\cPositions\\cInternal",         "bWindowHidden", DWORD(0x00000001));
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cHistoryMini\\cPositions\\cInternal",         "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cHowTo\\cPositions\\cInternal",               "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal",        "bWindowHidden", DWORD(0x00000000)); // "JSToolBar" c17, c18
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSDocToolBar\\cPositions\\cInternal",        "bWindowHidden", DWORD(0x00000000));

// Tadas 2009.12.08
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral\cToolbars\cJSAppToolBar\cPositions\cInternal]
// "iDockPosition"=dword:00000001
// TUX_XFS nëra
      if(eboard && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iDockPosition", DWORD(0x00000001)); // DWORD(0x00000000)); //

//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iFrameL", DWORD(0x0000100));
//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iFrameR", DWORD(0x0000200));
//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iFrameT", DWORD(0x0000100));
//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iFrameB", DWORD(0x0000200));

//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iWindowBottom", 0x0000006e); // 0x000000ca); // wnd_y + 24);
//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iWindowTop", 0x0000004a); // 0x000000a6); // wnd_y);
//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iWindowLeft", 0x00000036); // 0x0000092);
//       if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iWindowRight", 0x0000045e); // 0x000004ba);
      }

//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cLayoutMini\\cPositions\\cInternal",      "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cMeasuring\\cPositions\\cInternal",       "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cNavigation\\cPositions\\cInternal",      "bWindowHidden", DWORD(0x00000001)); // c11, c12
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cNavMini\\cPositions\\cInternal",         "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cProperties\\cPositions\\cInternal",      "bWindowHidden", DWORD(0x00000001)); // c13, c14
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cRotate\\cPositions\\cInternal",          "bWindowHidden", DWORD(0x00000001)); // c7
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cTasks\\cPositions\\cInternal",           "bWindowHidden", DWORD(0x00000001)); // c9
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cTypewriter\\cPositions\\cInternal",      "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cUndoRedo\\cPositions\\cInternal",        "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cViewing\\cPositions\\cInternal",         "bWindowHidden", DWORD(0x00000001)); // c4
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cViewModeMini\\cPositions\\cInternal",    "bWindowHidden", DWORD(0x00000001));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cWebSearchView\\cPositions\\cInternal",   "bWindowHidden", DWORD(0x00000001));
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cZoomMini\\cPositions\\cInternal",        "bWindowHidden", DWORD(0x00000001));
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cZoomToolFlyout\\cPositions\\cInternal",  "bWindowHidden", DWORD(0x00000001));

// Tadas 2010.06.04
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral\cToolbars\cAdvCommenting\cPositions\cInternal]
// "iFrameB"=dword:00000072
// "iFrameL"=dword:0000000a
// "iFrameR"=dword:000001af
// "iFrameT"=dword:00000050
// "bWindowHidden"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameB", DWORD(0x00000072));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameL", DWORD(0x0000000a));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameR", DWORD(0x000001af));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameT", DWORD(0x00000050));

// Tadas 2010.06.18
// tik vadovëliams, kur yra paieðka
bool find_but = False;
      if(SUCCEEDED(retc)) retc = GetIniFindBut(&find_but);
      if(find_but && SUCCEEDED(retc))
      {
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral\cToolbars\cFind\cPositions\cExternal]
// "iDockPosition"=dword:00000000
// "bHidden"=dword:00000000
// "iOffset"=dword:7fffffff
// "iOrder"=dword:00000015
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "iDockPosition", DWORD(0x00000000));
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "bHidden",       DWORD(0x00000000));
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "iOffset",       DWORD(0x7fffffff));
         if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "iOrder",        DWORD(0x00000015));
      }

// Tadas 2010.11.04
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cExternal",        "iDockPosition", DWORD(0x00000000));
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cExternal",        "bWindowHidden", DWORD(0x00000000));

      if(SUCCEEDED(retc)) /* retc = */ UpdateTMGrpPrm(); // Mano emuliatoriuj WinXP Administrator neturi AddData, ignoruoti klaidas

   } // if((iVers >= 700) && (iVers < 900))


// Vistoj kad nesikeiktø Application Compatibility Assistant (Program Compatibility Assistant, PCA)
// HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags
// {f5352b91-2de6-46e4-a4bb-0ba25ce71513}: 0x4
   if((iWindowsVersion >= WinVistaC) && SUCCEEDED(retc))
   {
#if FALSE
// sukuria *_sav laukà
      retc = KpRegSetValue("Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags",
               "{f5352b91-2de6-46e4-a4bb-0ba25ce71513}", 0x4);
#else
LONG retw = ERROR_SUCCESS;
HKEY key = NULL;
DWORD value;

      retw = RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags",
               0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &key, NULL);
      KP_ASSERT(retw == ERROR_SUCCESS, KP_E_KWD_NOT_FOUND, retw, False);
      if(retw == ERROR_SUCCESS)
      {
         KP_ASSERT(key, KP_E_SYSTEM_ERROR, retw, False);
         if(key)
         {
            value = 0x4;
            retw = RegSetValueEx(key, "{f5352b91-2de6-46e4-a4bb-0ba25ce71513}", 0L, REG_DWORD, (BYTE *)&value, sizeof(value));
            KP_ASSERT(retw == ERROR_SUCCESS, KP_E_FERROR, retw, False);
         }
      }
#endif
   }


// Tadas 20101228 dël MIMOK5_70
   if((iVers >= 700) && (iVers < 900))
   {
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AdobeViewer]
// "EULA"=dword:00000001
// jau nustatytas

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral]
// "iLabelVisibility"=dword:00000002
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "iLabelVisibility", 2);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\PICommonPrefs]
// "bSpellingUnderline"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "PICommonPrefs", "bSpellingUnderline", (DWORD)0L);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\PICommonPrefs\cPICommonPrefs\cSpelling]
// "bSpellUnderline"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling", "bSpellUnderline", (DWORD)0L);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\PICommonPrefs\cPICommonPrefs\cSpelling\cSpellColor]
// "t0"=hex:52,47,42,00 // "RGB"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "t0", "RGB");
// "d1"="1.000000"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "d1", "1.000000");
// "d2"="0.000000"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "d2", "0.000000");
// "d3"="0.000000"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "d3", "0.000000");

   } // if((iVers >= 700) && (iVers < 900))


#if FALSE
// Gintaras 2011.02.14 dël Audio leidimo Acrobatui
   if((iVers >= 700) && (iVers < 900))
   {
// [HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\LowRegistry\Audio\PolicyConfig\PropertyStore\9f191864_0\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}]
// "3"=hex:04,00,00,00,00,00,00,00,00,00,80,3f,00,00,00,00,00,00,00,00,00,00,00,00
// "4"=hex:04,20,00,00,00,00,00,00,18,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,80,3f,00,00,80,3f
// "5"=hex:0b,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00

#define val_3_len 24
static BYTE val_3[val_3_len] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      if(SUCCEEDED(retc)) retc = KpRegSetValue(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\9f191864_0\\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}", "3", REG_BINARY, val_3, val_3_len);

#define val_4_len 32
static BYTE val_4[val_4_len] = {0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x80, 0x3f};
      if(SUCCEEDED(retc)) retc = KpRegSetValue(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\9f191864_0\\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}", "4", REG_BINARY, val_4, val_4_len);

#define val_5_len 24
static BYTE val_5[val_5_len] = { 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      if(SUCCEEDED(retc)) retc = KpRegSetValue(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\9f191864_0\\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}", "4", REG_BINARY, val_4, val_4_len);

// [HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\LowRegistry\Audio\PolicyConfig\PropertyStore\93977ab6_0]
// @="{0.0.0.00000000}.{4b07641f-08d6-41a6-b88a-2a22273bb983}|\\Device\\HarddiskVolume2\\Program Files (x86)\\KTU\\Kalbos akustika glaustai\\AcroRead709\\Reader\\AcroRd32.exe%b{00000000-0000-0000-0000-000000000000}"
static char dir_buf[MAX_PATH + 1];
static char key_val[MAX_PATH + 200];
      GetCurDevPath(dir_buf);
      sprintf(key_val, "{0.0.0.00000000}.{4b07641f-08d6-41a6-b88a-2a22273bb983}|%s\\AcroRead709\\Reader\\AcroRd32.exe%%b{00000000-0000-0000-0000-000000000000}", dir_buf);
      if(SUCCEEDED(retc)) retc = KpRegSetValue(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\93977ab6_0", "", key_val);

   } // if((iVers >= 700) && (iVers < 900))
#endif


// Tadas 2011.06.10 dël perspëjimø apie kreipimàsi á atnaujinimus prodreg.tev.lt
   if((iVers >= 700) && (iVers < 900))
   {
// [HKEY_CURRENT_USERS\Software\Adobe\Acrobat Reader\7.0\TrustManager]
// "bExternalStream"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TrustManager", "bExternalStream", 1);

// [HKEY_CURRENT_USERS\Software\Adobe\Acrobat Reader\7.0\TrustManager\cDefaultLaunchURLPerms]
// "iUnknownURLPerms"=dword:00000002
// "iURLPerms"=dword:00000002
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TrustManager\\cDefaultLaunchURLPerms", "iUnknownURLPerms", 2);
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TrustManager\\cDefaultLaunchURLPerms", "iURLPerms", 2);

   } // if((iVers >= 700) && (iVers < 900))

// Tadas 2011.07.18
   if((iVers >= 700) && (iVers < 900))
   {
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\Selection]
// "bHandSelects"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Selection", "bHandSelects", (DWORD)0);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\Language\current]
// @="acrord32.dll"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Language\\current", "", "AcroRd32.dll", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\Language\next]
// @="acrord32.dll"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Language\\next", "", "AcroRd32.dll", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\TrustManager\cDefaultLaunchURLPerms]
// "iURLPerms"=dword:00000002
// jau yra
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "TrustManager\\cDefaultLaunchURLPerms", "iUnknownURLPerms", 2);

   } // if((iVers >= 700) && (iVers < 900))

// Tadas 2011.08.01
   if((iVers >= 700) && (iVers < 900))
   {
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVAlert\cCheckbox]
// "iRememberNoMSAA"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVAlert\\cCheckbox", "iRememberNoMSAA", (DWORD)1);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\AVGeneral]
// "bToolbarsLocked"=dword:00000001
// jau yra
//    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "bToolbarsLocked", (DWORD)1);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\FeatureLockdown]
// "bEFIPrintMe"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FeatureLockdown", "bEFIPrintMe", (DWORD)0);
// "bPurchaseAcro"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FeatureLockdown", "bPurchaseAcro", (DWORD)0);
// "bShowEbookMenu"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "FeatureLockdown", "bShowEbookMenu", (DWORD)0);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\Originals]
// "bDisplayedSplash"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "bDisplayedSplash", (DWORD)1);
// "iPageUnits"=dword:00000003
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Originals", "iPageUnits", (DWORD)3);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\7.0\Updater]
// "bShowInstCompDialog"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Updater", "bShowInstCompDialog", (DWORD)0);

   } // if((iVers >= 700) && (iVers < 900))


// ------------------------------------------
// Tadas 2012.05.04
   if(iVers >= 900)
   {
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\AdobeViewer]
// "TrustedMode"=dword:00000000
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "TrustedMode", (DWORD)0);

// "EULA"=dword:00000001
// jau nustatytas

// "Launched"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AdobeViewer", "Launched", (DWORD)1);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\Annots]
// "bStampsPaletteInvisible"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Annots", "bStampsPaletteInvisible", (DWORD)1);


// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\AVGeneral]
// "bLastExitNormal"=dword:00000001
// jau nustatytas

// "bAppInitialized"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "bAppInitialized", (DWORD)1);

// "iReaderLaunchCount"=dword:00000004
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral", "iReaderLaunchCount", (DWORD)4);


// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\AVGeneral\cToolbars\cCommenting\cStamp]
// "bInternalExpanded"=dword:00000001
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "AVGeneral\\cToolbars\\cCommenting\\cStamp", "bInternalExpanded", (DWORD)1);


// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\Language]
// "UI"="LTH"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Language", "UI", "LTH", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\Language\current]
// @="rdlang32.lth"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Language\\current", "", "rdlang32.lth", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\9.0\Language\next]
// @="RdLang32.LTH"
      if(SUCCEEDED(retc)) retc = KpRegSetValueAcro(iVers, "Language\\next", "", "RdLang32.LTH", REG_SZ);

   } // if(iVers >= 900)

// Tadas 2015-07-31 dël AcroReader DC

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\JSPrefs]
// "bConsoleOpen"=dword:00000000
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "JSPrefs", "bConsoleOpen", (DWORD)0);
// "bEnableGlobalSecurity"=dword:00000000
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "JSPrefs", "bEnableGlobalSecurity", (DWORD)0);
// "bEnableJS"=dword:00000001
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "JSPrefs", "bEnableJS", (DWORD)1);
// "bEnableMenuItems"=dword:00000001 
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "JSPrefs", "bEnableMenuItems", (DWORD)1);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\Privileged]
// "bProtectedMode"=dword:00000000
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "Privileged", "bProtectedMode", (DWORD)0);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager]
// "iProtectedView"=dword:00000000
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager", "iProtectedView", (DWORD)0);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cDefaultLaunchURLPerms]
// "tHostPerms"="version:2|http://www.tevukas.lt:2|tev.lt:2"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cDefaultLaunchURLPerms", "tHostPerms", "version:2|http://www.tevukas.lt:2|tev.lt:2", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders]
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cAlwaysTrustedForJavaScript]
// "t9"="c:\\users\\tadas\\appdata\\roaming\\tev"
    sprintf((char *)str_buf, "%s\\tev", getenv("appdata"));
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cAlwaysTrustedForJavaScript", "t9", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cCrossdomain]
// "t3"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cCrossdomain", "t3", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cDataInjection]
// "t7"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cDataInjection", "t7", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cExternalStream]
// "t4"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cExternalStream", "t4", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cFileAttachment]
// "t12"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cFileAttachment", "t12", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cJavaScript]
// "t5"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cJavaScript", "t5", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cJavaScriptURL]
// "t10"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cJavaScriptURL", "t10", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cMultiMedia]
// "t11"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cMultiMedia", "t11", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cScriptInjection]
// "t6"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cScriptInjection", "t6", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cSilentPrint]
// "t1"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cSilentPrint", "t1", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cTrustedAuxDownload]
// "t14"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cTrustedAuxDownload", "t14", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cTrustedForPV]
// "t13"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cTrustedForPV", "t13", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cUnsafeJavaScript]
// "t8"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cUnsafeJavaScript", "t8", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedFolders\cWeblink]
// "t2"="c:\\users\\tadas\\appdata\\roaming\\tev"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedFolders\\cWeblink", "t2", str_buf, REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites]
// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cAlwaysTrustedForJavaScript]
// "t9"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cAlwaysTrustedForJavaScript", "t9", "www.tev.lt", REG_SZ);
// "t23"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cAlwaysTrustedForJavaScript", "t23", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cCrossdomain]
// "t3"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cCrossdomain", "t3", "www.tev.lt", REG_SZ);
// "t17"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cCrossdomain", "t17", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cDataInjection]
// "t7"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cDataInjection", "t7", "www.tev.lt", REG_SZ);
// "t21"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cDataInjection", "t21", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cExternalStream]
// "t4"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cExternalStream", "t4", "www.tev.lt", REG_SZ);
// "t18"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cExternalStream", "t18", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cFileAttachment]
// "t12"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cFileAttachment", "t12", "www.tev.lt", REG_SZ);
// "t26"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cFileAttachment", "t26", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cJavaScript]
// "t5"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cJavaScript", "t5", "www.tev.lt", REG_SZ);
// "t19"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cJavaScript", "t19", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cJavaScriptURL]
// "t10"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cJavaScriptURL", "t10", "www.tev.lt", REG_SZ);
// "t24"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cJavaScriptURL", "t24", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cMultiMedia]
// "t11"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cMultiMedia", "t11", "www.tev.lt", REG_SZ);
// "t25"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cMultiMedia", "t25", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cScriptInjection]
// "t6"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cScriptInjection", "t6", "www.tev.lt", REG_SZ);
// "t20"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cScriptInjection", "t20", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cSilentPrint]
// "t1"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cSilentPrint", "t1", "www.tev.lt", REG_SZ);
// "t15"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cSilentPrint", "t15", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cTrustedAuxDownload]
// "t14"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cTrustedAuxDownload", "t14", "www.tev.lt", REG_SZ);
// "t28"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cTrustedAuxDownload", "t28", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cTrustedForPV]
// "t13"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cTrustedForPV", "t13", "www.tev.lt", REG_SZ);
// "t27"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cTrustedForPV", "t27", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cUnsafeJavaScript]
// "t8"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cUnsafeJavaScript", "t8", "www.tev.lt", REG_SZ);
// "t22"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cUnsafeJavaScript", "t22", "www.tevukas.lt", REG_SZ);

// [HKEY_CURRENT_USER\Software\Adobe\Acrobat Reader\DC\TrustManager\cTrustedSites\cWeblink]
// "t2"="www.tev.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cWeblink", "t2", "www.tev.lt", REG_SZ);
// "t16"="www.tevukas.lt"
    if(SUCCEEDED(retc)) retc = KpRegSetValueAcro("DC", "TrustManager\\cTrustedSites\\cWeblink", "t16", "www.tevukas.lt", REG_SZ);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreAcro(int iVers)
{
HRESULT retc=S_OK;
bool eboard = False;

   if(SUCCEEDED(retc)) retc = GetIniEboard(&eboard);

// ------------------------------------
   if((iVers >= 600) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdsInReader", "bShowAds");
//    if(iVers < 700)
         if(eboard && SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdsInReader", "sAdsLastUpdate");

   } // if(iVers >= 600)

   if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "EULA");

   if(iVers < 600) if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "BrowserCheck");

   if((iVers >= 600) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "MaxApp");
//    if(iVers < 700)
      {
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogX0");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogY0");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogW0");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogH0");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogX1");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogY1");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogW1");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogH1");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogX2");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogY2");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogW2");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogH2");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogX3");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogY3");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogW3");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogH3");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogX4");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogY4");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogW4");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogH4");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogX5");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogY5");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogW5");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "DialogH5");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "xRes");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "yRes");
         }

      } // if(iVers < 700)

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVAlert\\cCheckbox", "iwarnFieldsWillNotBeSaved");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVAlert\\cCheckbox", "iexitWithExternalDocsOpen");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVAlert\\cCheckbox", "iPictureTasksFeaturesNotice");
//    if(iVers < 700)
         if(/* eboard && */ SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVAlert\\cCheckbox", "iUBDontShowAgain");

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "bToolbarsLocked");

   } // if((iVers >= 600) && (iVers < 900))

   if(iVers >= 600)
   {
//    if(iVers < 700)
      {
         if(/* eboard && */ SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "bLastExitNormal");
//       if(eboard && SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "sInDocTabs");
      }
   }

   if((iVers >= 600) && (iVers < 900))
   {
      if(iVers < 700)
      {
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c0", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c11", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iDockPosition");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iOrder");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "bWindowHidden");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c12", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c13", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iDockPosition");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iOrder");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "bWindowHidden");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c14", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "bWindowHidden");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c15", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iDockPosition");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iOrder");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "bWindowHidden");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c16", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iDockPosition");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowTop");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c17", "iWindowRight");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "bInDoc");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iLayout");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iOrder");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c18", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c2", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c4", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c7", "iWindowTop");
         }

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "sToolBarName");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "bHidden");
         if(eboard && SUCCEEDED(retc))
         {
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "bExternal");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "iOffset");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "iStackNum");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowBottom");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowLeft");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowRight");
            if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\c9", "iWindowTop");
         }

      } // if(iVers < 700)

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FeatureLockdown", "bShowAdsAllow");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FeatureLockdown", "bUpdater");

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bAutoCompleteOnTab");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bFocusRect");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bInlineAutoComplete");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bRecordNewEntries");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bRuntimeHighlight");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bRuntimeShowOverflow");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bShowDropDown");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bStoreNumericEntries");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FormsPrefs", "bUserAskedToEnableAutoComplete");

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "JSPrefs", "bEnableJS");
//    if(iVers == 700)
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "JSPrefs", "iExceptions");

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bDisplayAboutDialog");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "iTrustedMode");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bBrowserIntegration");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bBrowserCheck");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bSkipDeleteWarnings");
//    if(iVers < 700)
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "sProofingSpace");

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Updater", "bShowAutoUpdateConfDialog");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Updater", "bShowNotifDialog");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Updater", "iUpdateFrequency");

// ---------------------------------------
// bookmarkai

      if(iVers < 700)
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "sInDocTabs");

      if(iVers < 700)
      {
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVBookmark", "iFontSize");

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "iBottom");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "iLeft");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "bMinimized");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "iRight");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "sTabs");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "iTop");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c0", "bVisible");

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c1", "iBottom");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c1", "iLeft");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c1", "bMinimized");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c1", "iRight");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c1", "sTabs");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c1", "iTop");

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "iBottom");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "iLeft");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "bMinimized");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "iRight");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "sTabs");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "iTop");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c2", "bVisible");

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "iBottom");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "iLeft");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "bMinimized");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "iRight");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "sTabs");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "iTop");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cPalettes\\c3", "bVisible");

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "iDefaultSplitterPos");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bBookmarkShowLocation");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bMinimizeBookmarks");

         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Appearance", "tFile");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Appearance", "iPage");

      } // if(iVers < 700)

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iCommentTask");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iFillInTask");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iPictureTasks");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iSignTask");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iNewDocumentTask");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iEBookTask");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TaskButtons", "iFormTasks");

   } // if((iVers >= 600) && (iVers < 900))

   if((iVers >= 700) && (iVers < 900))
   {

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cBasicTools\\cPositions\\cInternal",          "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cCommenting\\cPositions\\cInternal",          "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cCommentPanelToolbar\\cPositions\\cInternal", "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cData\\cPositions\\cInternal",                "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFile\\cPositions\\cInternal",                "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFileAttachmentFlyout\\cPositions\\cInternal","bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cInternal",                "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cHelpToolbar\\cPositions\\cInternal",         "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cHistoryMini\\cPositions\\cInternal",         "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cHowTo\\cPositions\\cInternal",               "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal",        "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cJSDocToolBar\\cPositions\\cInternal",        "bWindowHidden");

      if(eboard && SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cJSAppToolBar\\cPositions\\cInternal", "iDockPosition");

//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cLayoutMini\\cPositions\\cInternal",      "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cMeasuring\\cPositions\\cInternal",       "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cNavigation\\cPositions\\cInternal",      "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cNavMini\\cPositions\\cInternal",         "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cProperties\\cPositions\\cInternal",      "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cRotate\\cPositions\\cInternal",          "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cTasks\\cPositions\\cInternal",           "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cTypewriter\\cPositions\\cInternal",      "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cUndoRedo\\cPositions\\cInternal",        "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cViewing\\cPositions\\cInternal",         "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cViewModeMini\\cPositions\\cInternal",    "bWindowHidden");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cWebSearchView\\cPositions\\cInternal",   "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cZoomMini\\cPositions\\cInternal",        "bWindowHidden");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cZoomToolFlyout\\cPositions\\cInternal",  "bWindowHidden");

      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameB");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameL");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameR");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cAdvCommenting\\cPositions\\cInternal",   "iFrameT");

bool find_but = False;
      if(SUCCEEDED(retc)) retc = GetIniFindBut(&find_but);
      if(find_but && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "iDockPosition");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "bHidden");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "iOffset");
         if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cFind\\cPositions\\cExternal", "iOrder");
      }

      if(SUCCEEDED(retc)) retc = RestoreTMGrpPrm();

   } // if((iVers >= 700) && (iVers < 900))

   if((iVers >= 700) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "iLabelVisibility");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "PICommonPrefs", "bSpellingUnderline");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling", "bSpellUnderline");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "t0");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "d1");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "d2");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "PICommonPrefs\\cPICommonPrefs\\cSpelling\\cSpellColor", "d3");
   }

   if((iVers >= 700) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestore(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\9f191864_0\\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}", "3");
      if(SUCCEEDED(retc)) retc = KpRegRestore(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\9f191864_0\\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}", "4");
      if(SUCCEEDED(retc)) retc = KpRegRestore(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\9f191864_0\\{219ED5A0-9CBF-4F3A-B927-37C9E5C5F14F}", "4");
//    if(SUCCEEDED(retc)) retc = KpRegRestore(KP_HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\LowRegistry\\Audio\\PolicyConfig\\PropertyStore\\93977ab6_0", "");
   }

   if((iVers >= 700) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TrustManager", "bExternalStream");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TrustManager\\cDefaultLaunchURLPerms", "iUnknownURLPerms");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TrustManager\\cDefaultLaunchURLPerms", "iURLPerms");
   }

   if((iVers >= 700) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Selection", "bHandSelects");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Language\\current", "");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Language\\next", "");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "TrustManager\\cDefaultLaunchURLPerms", "iUnknownURLPerms"); // jau yra
   }

   if((iVers >= 700) && (iVers < 900))
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVAlert\\cCheckbox", "iRememberNoMSAA");
//    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "bToolbarsLocked");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FeatureLockdown", "bEFIPrintMe");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FeatureLockdown", "bPurchaseAcro");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "FeatureLockdown", "bShowEbookMenu");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "bDisplayedSplash");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Originals", "iPageUnits");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Updater", "bShowInstCompDialog");
   }

   if(iVers >= 900)
   {
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "TrustedMode");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AdobeViewer", "Launched");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Annots", "bStampsPaletteInvisible");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "bAppInitialized");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral", "iReaderLaunchCount");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "AVGeneral\\cToolbars\\cCommenting\\cStamp", "bInternalExpanded");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Language", "UI");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Language\\current", "");
      if(SUCCEEDED(retc)) retc = KpRegRestoreAcro(iVers, "Language\\next", "");
   }

    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "JSPrefs", "bConsoleOpen");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "JSPrefs", "bEnableGlobalSecurity");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "JSPrefs", "bEnableJS");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "JSPrefs", "bEnableMenuItems");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "Privileged", "bProtectedMode");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager", "iProtectedView");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cDefaultLaunchURLPerms", "tHostPerms");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cAlwaysTrustedForJavaScript", "t9");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cCrossdomain", "t3");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cDataInjection", "t7");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cExternalStream", "t4");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cFileAttachment", "t12");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cJavaScript", "t5");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cJavaScriptURL", "t10");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cMultiMedia", "t11");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cScriptInjection", "t6");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cSilentPrint", "t1");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cTrustedAuxDownload", "t14");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cTrustedForPV", "t13");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cUnsafeJavaScript", "t8");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedFolders\\cWeblink", "t2");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cAlwaysTrustedForJavaScript", "t9");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cAlwaysTrustedForJavaScript", "t23");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cCrossdomain", "t3");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cCrossdomain", "t17");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cDataInjection", "t7");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cDataInjection", "t21");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cExternalStream", "t4");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cExternalStream", "t18");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cFileAttachment", "t12");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cFileAttachment", "t26");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cJavaScript", "t5");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cJavaScript", "t19");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cJavaScriptURL", "t10");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cJavaScriptURL", "t24");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cMultiMedia", "t11");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cMultiMedia", "t25");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cScriptInjection", "t6");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cScriptInjection", "t20");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cSilentPrint", "t1");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cSilentPrint", "t15");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cTrustedAuxDownload", "t14");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cTrustedAuxDownload", "t28");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cTrustedForPV", "t13");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cTrustedForPV", "t27");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cUnsafeJavaScript", "t8");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cUnsafeJavaScript", "t22");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cWeblink", "t2");
    if(SUCCEEDED(retc)) retc = KpRegRestoreAcro("DC", "TrustManager\\cTrustedSites\\cWeblink", "t16");

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::InitAcro50(void)
{
HRESULT retc=S_OK;

// XRegistry2 r007("SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral", "bToolbarsLocked", DWORD(0x00000001));
// XRegistry2 r008("SOFTWARE\\Adobe\\Acrobat Reader\\7.0\\AVGeneral\\cToolbars\\c0", "sToolBarName", "File");

   retc = InitAcro(500);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreAcro50(void)
{
HRESULT retc=S_OK;

   retc = RestoreAcro(500);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::InitAcro60(void)
{
HRESULT retc=S_OK;

// KpMsgOut("Pries InitAcro60", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   retc = InitAcro(600);

// KpMsgOut("Po InitAcro60", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreAcro60(void)
{
HRESULT retc=S_OK;

// KpMsgOut("Pries RestoreAcro60", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   retc = RestoreAcro(600);

// KpMsgOut("Po RestoreAcro60", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::InitAcro70(void)
{
HRESULT retc=S_OK;

// KpMsgOut("Pries InitAcro70", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   retc = InitAcro(700);

// KpMsgOut("Po InitAcro70", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreAcro70(void)
{
HRESULT retc=S_OK;

// KpMsgOut("Pries RestoreAcro70", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   retc = RestoreAcro(700);

// KpMsgOut("Po RestoreAcro70", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::InitAcro80(void)
{
HRESULT retc=S_OK;

   retc = InitAcro(800);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreAcro80(void)
{
HRESULT retc=S_OK;

   retc = RestoreAcro(800);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::InitAcro90(void)
{
HRESULT retc=S_OK;

// KpMsgOut("Pries InitAcro90", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   retc = InitAcro(900);

// KpMsgOut("Po InitAcro90", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


//-------------------------------------------
HRESULT KpStApp::RestoreAcro90(void)
{
HRESULT retc=S_OK;

// KpMsgOut("Pries RestoreAcro90", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

   retc = RestoreAcro(900);

// KpMsgOut("Po RestoreAcro90", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

return(retc);
}


// -----------------------------------------
#ifdef TUX_LIB
DWORD WINAPI tux_dbg_thread_proc(LPVOID lpParameter)
{
// HRESULT retc=S_OK;
   /* retc= */ tux_dbg();
}
#endif


HRESULT KpStApp::StartCmd(const unsigned char *lpszCmdLine, const unsigned char *lpszPwd)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static unsigned char fnam_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char fnam_buf_1[KP_MAX_FNAME_LEN + 1];
unsigned char *pnts;
KpStIniData *ini_ptr = NULL;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
static unsigned char att_ext[KP_MAX_FTYPE_LEN + 1];
static unsigned char def_dir[KP_MAX_FNAME_LEN + 1];

#if FALSE
static unsigned char rez_fullname[KP_MAX_FNAME_LEN+1];
static unsigned char rez_disk[KP_MAX_FNAME_LEN+1];
static unsigned char rez_path[KP_MAX_FNAME_LEN+1];
static unsigned char rez_name[KP_MAX_FNAME_LEN+1];
static unsigned char rez_type[KP_MAX_FTYPE_LEN+1];
#endif

static unsigned char app_disk[KP_MAX_FNAME_LEN+1];
static unsigned char app_path[KP_MAX_FNAME_LEN+1];
static unsigned char app_name[KP_MAX_FNAME_LEN+1];
static unsigned char app_type[KP_MAX_FTYPE_LEN+1];


// -------------------------
PutLogMessage_("StartCmd() 1");

   if((lpszCmdLine != null) && SUCCEEDED(retc)) retc = SetIniCmdStr(lpszCmdLine);
   if((lpszPwd != null) && SUCCEEDED(retc))
   {
// TODO !!!! sutvarkyt kpstisvr.exe CheckReg()
MemBankObj[KP11_BLOCK_PROCESSING/2] = False;
MemBankObj[KP11_BLOCK_TERM/2] = False;

PutLogMessage_("StartCmd() 0: %s", m_Ini.m_lpszPwd);
      retc = SetIniPwd(lpszPwd);
PutLogMessage_("StartCmd() 1: %s", m_Ini.m_lpszPwd);

#ifdef KPST_MOVE_TO_KPHP11
      ini_ptr = &IniDataBuf;
#else
      ini_ptr = &m_Ini;
#endif

PutLogMessage_("StartCmd() 2");

unsigned char pwd_buf[TV_TAG_LEN + 1];
GetIniPwdRC(pwd_buf);
EnctBuf(&MemBankObj[HP11_RC_INI_BUF/2], ((sizeof(KpStIniData) - sizeof(m_Ini.m_iCheckSum))/4)*4, m_Ini.m_iCheckSum, False);
PutLogMessage_("StartCmd() 2: [%s] [%s]", pwd_buf, (const unsigned char *)MemBankObj + HP11_RC_INI_BUF + (IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf));
EnctBuf(&MemBankObj[HP11_RC_INI_BUF/2], ((sizeof(KpStIniData) - sizeof(m_Ini.m_iCheckSum))/4)*4, m_Ini.m_iCheckSum, False);
      if(SUCCEEDED(retc)) retc = EnctIniData(sizeof(KpStIniData));
      if(SUCCEEDED(retc)) retc = SendIniToHp11(ini_ptr, False);
      if(SUCCEEDED(retc)) retc = EnctIniData(sizeof(KpStIniData));
GetIniPwdRC(pwd_buf);
EnctBuf(&MemBankObj[HP11_RC_INI_BUF/2], ((sizeof(KpStIniData) - sizeof(m_Ini.m_iCheckSum))/4)*4, m_Ini.m_iCheckSum, False);
PutLogMessage_("StartCmd() 3: [%s] [%s]", pwd_buf, (const unsigned char *)MemBankObj + HP11_RC_INI_BUF + (IniDataBuf.m_lpszPwd - (unsigned char *)&IniDataBuf));
EnctBuf(&MemBankObj[HP11_RC_INI_BUF/2], ((sizeof(KpStIniData) - sizeof(m_Ini.m_iCheckSum))/4)*4, m_Ini.m_iCheckSum, False);
   }

PutLogMessage_("StartCmd() 3");

// -------------------------
   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) retc = GetIniAttExt(att_ext);
#if FALSE
   rez_fullname[0]=Nul;
   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fullname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fullname);
#endif

PutLogMessage_("StartCmd() 4");

// ----------------------------------------------
   if(SUCCEEDED(retc)) retc = AskUserPwd();

PutLogMessage_("StartCmd() 5");

// ----------------------------------------------
   if(SUCCEEDED(retc)) retc = StartIE(); // atkelta èia, nes pjaunasi su pwd ávedimo dialogu – pasileidþia antrà k. ir maximizuotas

PutLogMessage_("StartCmd() 6");

// ---------------------------- surandam app_name - paleistos programos varda be pletinio, istatysim vietoj {prog}
   if(SUCCEEDED(retc)) retc = GetAppName(fnam_buf);
   if(SUCCEEDED(retc)) retc = TvFnameSplit(app_disk, app_path, app_name, app_type, fnam_buf);

PutLogMessage_("StartCmd() 7");

#if FALSE // iðkeltas á InitStApp(), kad iðkviestø ir registr.exe
#ifndef TUX_LIB
   if(SUCCEEDED(retc)) if((m_iKpStMode == KpStarterMode) || (m_iKpStMode == KpStRegMode)) // reikia ir registratoriui – Win 7 neadminui neleidþia áraðyt net á vartotojo raktus, ypaè XFS-ui
   {
// ------------------------- acroread 5.0 initial settings
      if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD50_PATHNAME) != null) retc = InitAcro50();

// ------------------------- acroread 6.0 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD60_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) != null)) retc = InitAcro60();

// ------------------------- acroread 7.0 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD70_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT) != null)) retc = InitAcro70();

// ------------------------- acroread 8 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD80_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT) != null)) retc = InitAcro80();

// ------------------------- acroread 9.0 initial settings
      if(SUCCEEDED(retc)) if((strstr(cmd_str, KPST_ACROREAD90_PATHNAME) != null) ||
         (strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT) != null)) retc = InitAcro70();

   } // if((m_iKpStMode==KpStarterMode) || (m_iKpStMode == KpStRegMode))
#endif // #ifndef TUX_LIB
#endif

PutLogMessage_("StartCmd() 8");

// ------------------------- setting acroread SaveAs default folder
   if(SUCCEEDED(retc)) if((m_iKpStMode==KpStarterMode) && (strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT)))
      retc = InitAcroSaveAs();

PutLogMessage_("StartCmd() 9");

// -------------------------
   if(SUCCEEDED(retc)) if(strlen(cmd_str)>=KP_MAX_FNAME_LEN)
      retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) strcpy(fnam_buf, cmd_str);

// -------------------------
// TODO iðkelti á paprogrames !!!!!
// ----------------------------- {att} --> m_lpszAttFname
   if(SUCCEEDED(retc)) do
   {
      pnts = strstr(fnam_buf, KPST_FNAME_SHORTCUT_ATT); // "{att}");
      if(pnts)
      {
         if(strlen(fnam_buf) + strlen(m_lpszAttFname) /* + strlen(att_ext) */ >= KP_MAX_FNAME_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            *pnts = Nul;
            pnts += 5; // strlen(KPST_FNAME_SHORTCUT_ATT); // "{att}");

            strcpy(fnam_buf_1, fnam_buf);
            strcat(fnam_buf_1, m_lpszAttFname);
//          strcat(fnam_buf_1, ".");   // jau su visu pletiniu
//          strcat(fnam_buf_1, att_ext);
            strcat(fnam_buf_1, pnts);

            strcpy(fnam_buf, fnam_buf_1);
         }
      }

   } while(pnts && SUCCEEDED(retc));

PutLogMessage_("StartCmd() 10");

// ----------------------------- {prog} --> app_name
   if(SUCCEEDED(retc)) do
   {
      pnts=strstr(fnam_buf, KPST_FNAME_SHORTCUT_PROG); // "{prog}");
      if(pnts)
      {
         if(strlen(fnam_buf) + strlen(app_name) >= KP_MAX_FNAME_LEN)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            *pnts = Nul;
            pnts += 6; // strlen(KPST_FNAME_SHORTCUT_PROG); // "{prog}");

            strcpy(fnam_buf_1, fnam_buf);
            strcat(fnam_buf_1, app_name);
            strcat(fnam_buf_1, pnts);

            strcpy(fnam_buf, fnam_buf_1);
         }
      }

   } while(pnts && SUCCEEDED(retc));

PutLogMessage_("StartCmd() 11");

// ----------------------------- {user} --> m_lpszFlashDevName
   if(SUCCEEDED(retc)) do
   {
      pnts = strstr(fnam_buf, KPST_FNAME_SHORTCUT_USER); // "{user}");
      if(pnts)
      {
         if(strlen(fnam_buf) + strlen(m_lpszFlashDevName) >= KP_MAX_FNAME_LEN)
            retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
         {
            *pnts = Nul;
            pnts += 6; // strlen(KPST_FNAME_SHORTCUT_USER); // "{user}");

            strcpy(fnam_buf_1, fnam_buf);
            strcat(fnam_buf_1, m_lpszFlashDevName);
            strcat(fnam_buf_1, pnts);

            strcpy(fnam_buf, fnam_buf_1);
         }
      }

   } while(pnts && SUCCEEDED(retc));

PutLogMessage_("StartCmd() 12");

// ----------------------------- {par} --> m_plCmdLineArgs
   if(SUCCEEDED(retc)) if(strstr(fnam_buf, KPST_FNAME_SHORTCUT_PAR))
   {
const unsigned char *par = null;
      KP_ASSERT(m_plCmdLineArgs, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc)) par = (const unsigned char *)m_plCmdLineArgs->GetValue();
      KP_ASSERT(par, E_INVALIDARG, null, True);
      if(SUCCEEDED(retc)) do
      {
         pnts = strstr(fnam_buf, KPST_FNAME_SHORTCUT_PAR); // "{par}");
         if(pnts)
         {
            if(strlen(fnam_buf) + strlen(par) >= KP_MAX_FNAME_LEN)
               retc = KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

            if(SUCCEEDED(retc))
            {
               *pnts = Nul;
               pnts += 5; // strlen(KPST_FNAME_SHORTCUT_PAR); // "{par}");

               strcpy(fnam_buf_1, fnam_buf);
               strcat(fnam_buf_1, par);
               strcat(fnam_buf_1, pnts);

               strcpy(fnam_buf, fnam_buf_1);
            }
         }

      } while(pnts && SUCCEEDED(retc));

   } // if(strstr(fnam_buf, KPST_FNAME_SHORTCUT_PAR))

PutLogMessage_("KpStApp::StartCmd() 13: [%s]", fnam_buf);

// pradini folderi
   if(SUCCEEDED(retc))
   {
#if FALSE
      if(strlen(rez_fullname)>0)
      {
         retc=TvFnameSplit(rez_disk, rez_path, rez_name, rez_type, rez_fullname);
         if(SUCCEEDED(retc))
         {
            strcpy(def_dir, rez_disk);
            strcat(def_dir, rez_path);
//          strcat(def_dir, "\\");
// KpMsgOut(def_dir, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
         }
      }
      else
#endif
         strcpy(def_dir, KPST_CUR_DIR);
   }

#ifdef TUX_LIB
// if(SUCCEEDED(retc)) retc=tux_dbg();

   if(SUCCEEDED(retc))
   {
      m_hCmdThread = CreateThread
      (
         NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
         0L,                  // DWORD dwStackSize,                         // initial thread stack size
         tux_dbg_thread_proc, // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
         NULL,                // LPVOID lpParameter,                        // argument for new thread
         0L,                  // DWORD dwCreationFlags,                     // creation flags
         (LPDWORD)&m_lCmdThread   // LPDWORD lpThreadId                         // pointer to receive thread ID
      );
      if(m_hCmdThread==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }
#else

PutLogMessage_("StartCmd() 14");

PutLogMessage_((const unsigned char *)"KpStApp::StartCmd(%s)", fnam_buf);
   if(SUCCEEDED(retc)) retc = StartCmdProcess(fnam_buf, def_dir, &m_lCmdThread, &m_hCmdProcess, True, SW_SHOWNORMAL /* SW_SHOWDEFAULT SW_SHOWMAXIMIZED SW_MAXIMIZE SW_FORCEMAXIMIZE */, False, False, (const unsigned char *)"", False);
PutLogMessage_((const unsigned char *)"KpStApp::StartCmd(%s) jau", fnam_buf);
#endif

PutLogMessage_("StartCmd() 15");

   if(FAILED(retc) && (m_hBitmapWindow != NULL))
   {
//    KP_ASSERT0(::DestroyWindow(m_hBitmapWindow), KP_E_SYSTEM_ERROR, GetLastError(), False);
KpWnd *bmp_wnd = NULL;
      retc0 = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
      if((bmp_wnd != NULL) && SUCCEEDED(retc0)) retc0 = DeleteWnd(bmp_wnd);

      m_hBitmapWindow = NULL;
   }

PutLogMessage_("StartCmd() 16");

// unsigned char str_buf[1000];
// strcpy(str_buf, "paleidau ");
// strcat(str_buf, fnam_buf);
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
return(retc);
}


// -----------------------------------------
HRESULT KpStApp::StartComplete(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
// int prol_show_time=0;
int pwd_ok_but=0;
unsigned char prol_fname[KP_MAX_FNAME_LEN+1];
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
bool full_scr = False;

// if(SUCCEEDED(retc)) retc=GetIniProlShowTime(&prol_show_time);
   if(SUCCEEDED(retc)) retc=GetIniPwdOkBut(&pwd_ok_but);
   if(SUCCEEDED(retc)) retc=GetIniProlFName(prol_fname);
   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) retc=GetIniPwdWndName(pwd_win_name);
   if(SUCCEEDED(retc)) retc=CutInitTrailSpcs(pwd_win_name);
   if(SUCCEEDED(retc)) retc=GetIniFullScr(&full_scr);

#ifdef Debug
#ifdef DebugStop
KpMsgOut("3.1 WaitForWnd", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

#ifdef KPST_BITMAP_TO_TOP
   if((pwd_ok_but != 0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, NULL);
#endif

   if(((m_iKpStMode == KpStarterMode) || (m_iKpStMode == KpStIpSvrMode)) && SUCCEEDED(retc))
   {
//    retc=KpSleep(prol_show_time*1000);
      if(SUCCEEDED(retc)) if(strlen(pwd_win_name)>0) retc = WaitForPwd();
//    if(SUCCEEDED(retc)) retc = MinimizeIEWindow();
      if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = WaitForPwdCloses();
   }

// ---------------------- maximize AcroReader window
#if FALSE
// KP_TRACE(cmd_str);
   if(
      (m_iKpStMode == KpStarterMode) &&

//    (strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT)) &&
      (!full_scr) &&

      SUCCEEDED(retc)
     )
   {
//    retc = MaximizeAcroWindowProcess();
      m_bMaximizeAcroWindow = True;
// KP_TRACE("m_bMaximizeAcroWindow = True;");
   }
#endif

// ---------------------- close prologue
   if(SUCCEEDED(retc)) retc = KpSleep(5000, HWND_DESKTOP); // Sleep(5000); // letuose kompuose uzsidarius slaptazodzio langui akrobato langas ilgai neatsidaro

#ifdef Debug
#ifdef DebugStop
KpMsgOut("3.2 CosePrologue", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(((m_iKpStMode == KpStarterMode) || (m_iKpStMode == KpStIpSvrMode)) && m_lProlThreadId && SUCCEEDED(m_RetcPr))
   {
      m_RetcPr = CloseProcess(prol_fname, m_lProlThreadId);
      if(SUCCEEDED(retc)) retc = m_RetcPr;
   }
   m_lProlThreadId = 0L;

// if(SUCCEEDED(retc)) retc = StopSound();

// ---------------------- close bitmap
   if(((m_iKpStMode == KpStarterMode) || (m_iKpStMode == KpStIpSvrMode)) && (m_hBitmapWindow != NULL))
   {
// iskeltas á taimerá po 5 sec
#if FALSE
//    KP_ASSERT0(::DestroyWindow(m_hBitmapWindow), KP_E_SYSTEM_ERROR, GetLastError(), False);
KpWnd *bmp_wnd = NULL;
      retc0 = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
      if((bmp_wnd != NULL) && SUCCEEDED(retc0)) retc0 = DeleteWnd(bmp_wnd);

      m_hBitmapWindow = NULL;
#endif

// bent jau nuimsim ið TOPMOST
      SetWindowPos(m_hBitmapWindow, HWND_NOTOPMOST, 0, 0, 100, 100, SWP_NOMOVE|SWP_NOSIZE);
   }

return(retc);
}


//----------------------------------- start HTTP listening thread
HRESULT KpStApp::CreateSockThread(HINSTANCE /* hInstance */)
{
HRESULT retc=S_OK;
static unsigned char svr_data_path[KP_MAX_FNAME_LEN + 100];

   if(((m_lListThreadId != 0L) || (m_pListSocket != NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_DOUBLE_CALL, null, True, __FILE__, __LINE__, 0L, NULL);

// if(SUCCEEDED(retc)) retc = GetAppPath(svr_data_path, True);

   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)svr_data_path), KP_E_SYSTEM_ERROR, GetLastError(), True);
   if(SUCCEEDED(retc)) strcat(svr_data_path, "\\");

   if(SUCCEEDED(retc)) strcat(svr_data_path, KPSTAP_SVR_DATA_FILE);

   if(SUCCEEDED(retc))
   {
      retc = ReadFileContents(svr_data_path, &m_pcListBuf, &m_lListBufLen, False, True);
      if(retc == KP_E_FILE_NOT_FOUND)
      {
         retc = S_OK;
         m_lListBufLen = strlen(KPST_IP_OK);

         KP_NEWA(m_pcListBuf, unsigned char, m_lListBufLen + 1);

         if(SUCCEEDED(retc)) strcpy(m_pcListBuf, KPST_IP_OK);
      }
      else
         if((m_pcListBuf != null) && (m_lListBufLen > 0) && SUCCEEDED(retc))
            retc = EnctBufSimpl(m_pcListBuf, m_lListBufLen);

      if((m_pcListBuf != null) && (m_lListBufLen > 0) && SUCCEEDED(retc))
      {
         KP_NEW(m_pListSocket, KpSocket);

         if(SUCCEEDED(retc)) retc = m_pListSocket->Bind(KPSTAP_PORT, inet_addr((const char *)KP_IPADDR_LOCAL_HOST) /* INADDR_LOOPBACK */);
// KP_TRACE("CreateSockThread(): Bind()");

         if(SUCCEEDED(retc)) retc = m_pListSocket->Listen();
// KP_TRACE("CreateSockThread(): Listen()");

         if(SUCCEEDED(retc))
         {
// ------------------------- threadui m_hListThread reikia THREAD_TERMINATE access - neþinau kaip nustatyti
            m_hListThread = CreateThread
            (
               NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
               0L,                  // DWORD dwStackSize,                         // initial thread stack size
               SockListenProc,      // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
               NULL,                // LPVOID lpParameter,                        // argument for new thread
               0L,                  // DWORD dwCreationFlags,                     // creation flags
               &m_lListThreadId     // LPDWORD lpThreadId                         // pointer to receive thread ID
            );
            if(m_hListThread == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

            if(FAILED(retc))
            {
               m_lListThreadId = 0L;
               m_hListThread = NULL;
            }
         }
// KP_TRACE("CreateSockThread(): CreateThread()");

      } // else // if(retc==KP_E_FILE_NOT_FOUND)

   } // if(SUCCEEDED(retc))

return(retc);
}


//----------------------------------- start HTTP listening process kpstisvr.exe (kpstisvr.bin)
HRESULT KpStApp::StartSockProcess(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static unsigned char svr_data_path[KP_MAX_FNAME_LEN + 100];
static unsigned char svr_exe_path[KP_MAX_FNAME_LEN + 100];
static unsigned char cur_dir[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_buf[KP_MAX_FNAME_LEN * 2 + 100];
static unsigned char cmd_buf_1[KP_MAX_FNAME_LEN + 100];
FILE *in_file = NULL;

// --------------------
PutLogMessage_("KpStApp::StartSockProcess() 1");

// --------------------
// if(SUCCEEDED(retc)) retc = GetAppPath(cur_dir, True);

   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir), KP_E_SYSTEM_ERROR, GetLastError(), True);
   if(SUCCEEDED(retc)) strcat(cur_dir, "\\");

// èia kai norëjau testuoti kpstisvr.bin ið flash'inës atmintuko dalies, kad nereiktø kiekvienà kartà kepti CD-ROM'inës dalies
// if(SUCCEEDED(retc)) retc = GetAppPath(cur_dir, True);

PutLogMessage_("KpStApp::StartSockProcess() 2");

// --------------------
   if(SUCCEEDED(retc))
   {
      strcpy(svr_data_path, cur_dir);
//    strcat(svr_data_path, KPSTAP_SVR_DATA_FILE); // kpstisvr.bin paleidþiam, tik jei yra kpstdf.bin
      strcat(svr_data_path, KPSTISVR_EXE_FNAME); // kpstisvr.bin paleidþiam visada, jei tik jis pats yra

// ar yra kpstdf.bin/kpstisvr.bin?
      in_file = fopen((const char *)svr_data_path, "rb");
      if(in_file)
      {
         fclose(in_file);
         m_bIPserver = True;

PutLogMessage_("KpStApp::StartSockProcess() 3: %s", svr_data_path);

         strcpy(svr_exe_path, cur_dir);
         strcat(svr_exe_path, KPSTISVR_EXE_FNAME);

         if(SUCCEEDED(retc)) retc = GetLocalPath(cmd_buf, KP_Temp_Dir, True);
         if(SUCCEEDED(retc)) strcat(cmd_buf, KPSTISVR_EXE_FNAME);

// kopijuojam serverio exe'kà á temp katalogà, kad po to netrukdytø iðtraukt atmintuko
         retc0 = S_OK;

         if(CopyFile((const char *)svr_exe_path, (const char *)cmd_buf, False))
         {
// nuimam readonly – kopijuota ið atmintuko CD-ROM srities
#if FALSE
            strcpy(cmd_buf_1, "attrib \"");
            strcat(cmd_buf_1, cmd_buf);
            strcat(cmd_buf_1, "\" -r -h");

//          system((const char *)cmd_buf_1);
            if(SUCCEEDED(retc0)) /* retc0 = */ StartProcess(cmd_buf_1, KPST_CUR_DIR, NULL, NULL, SW_SHOW /* SW_SHOWMINIMIZED */, False, False, False);
#else

PutLogMessage_("KpStApp::StartSockProcess() 4");

            if(!SetFileAttributes((const char *)cmd_buf, FILE_ATTRIBUTE_NORMAL))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            }
#endif

PutLogMessage_("KpStApp::StartSockProcess() 5: %s", cmd_buf);

// paleidþiam ið temp katalogo, tik jei pavyko nukopijuot. Jei ne – reiðkia jau yra ir paleistas.
            if(SUCCEEDED(retc0))
            {
               strcpy(cmd_buf_1, "\"");
               strcat(cmd_buf_1, cmd_buf);
               strcat(cmd_buf_1, "\" \"");
               strcat(cmd_buf_1, cur_dir);
               strcat(cmd_buf_1, "\"");

               retc0 = StartProcess(cmd_buf_1, KPST_CUR_DIR, NULL, NULL, SW_SHOW /* SW_SHOWMINIMIZED */, False, False, False);
            }

PutLogMessage_("KpStApp::StartSockProcess() 6: %s", cmd_buf_1);

// palaukiam kol pasileis
            if(SUCCEEDED(retc0)) KpSleep(1000);

PutLogMessage_("KpStApp::StartSockProcess() 7");

         } // if(CopyFile((const char *)svr_exe_path, (const char *)cmd_buf, False))

PutLogMessage_("KpStApp::StartSockProcess() 8");
         if(SUCCEEDED(retc0)) retc = SendIPSesAlive(); // siunèiam "CD=" á kpstisvr.exe, jei neigiamas atsakymas – tyliai nusiimam

PutLogMessage_("KpStApp::StartSockProcess() 9");

      } // if(in_file)

   } // if(SUCCEEDED(retc))

return(retc);
}


// -------------------
HRESULT KpStApp::SendIPSesAlive(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
KpSocket *sock_ptr = NULL;
static unsigned char out_buf[KP_MAX_FNAME_LEN + 100];
long ll = 0;
static unsigned char svr_data_path[KP_MAX_FNAME_LEN + 100];
FILE *in_file = NULL;

// --------------------
// if(SUCCEEDED(retc)) retc = GetAppPath(svr_data_path, True);

   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)svr_data_path), KP_E_SYSTEM_ERROR, GetLastError(), True);
   if(SUCCEEDED(retc)) strcat(svr_data_path, "\\");

// --------------------
   if(SUCCEEDED(retc))
   {
      strcat(svr_data_path, KPSTAP_SVR_DATA_FILE); // jei nëra kpstdf.bin – projektas ne leidybinis, nereikia rezervuoti kpstisvr.exe, naudojamas tik atnaujinimø tikrinimui

// ar yra kpstdf.bin?
      in_file = fopen((const char *)svr_data_path, "rb");
      if(in_file != NULL)
      {
         fclose(in_file);

// nustatom darbiná katalogà / patikrinam, ar nëra kitos jau uþsiregistravusios instancijos sesijos / rezervuojam kpstisvr.exe
         if(SUCCEEDED(retc0))
         {
            KP_NEW(sock_ptr, KpSocket);
            retc0 = retc;
         }

         if(SUCCEEDED(retc0)) retc0 = sock_ptr->GetOpenResult();

         if(SUCCEEDED(retc0)) retc0 = sock_ptr->Resolve(KPST_IP_CMD_URL, False); // "http://127.0.0.1:49494/"
// PutLogMessage((const unsigned char *)"StartSockProcess()", null);
         if(SUCCEEDED(retc0)) retc0 = sock_ptr->Connect(False);

         if(SUCCEEDED(retc0))
         {
            strcpy(out_buf, KPSTIP_ALIVE_CMD); // "CD="
            KP_ASSERT0(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)out_buf + strlen(out_buf)), KP_E_SYSTEM_ERROR, GetLastError(), True);
         }

         if(SUCCEEDED(retc0))
            retc0 = sock_ptr->SendHttpRequest(HTTP_POST_REQUEST_CMD,
                  (const unsigned char *)"/", // failo vardas // KPST_IP_CMD_URL, // "http://127.0.0.1:49494/"
                  False, strlen(out_buf)); // "POST"
         if(SUCCEEDED(retc0)) retc0 = sock_ptr->SendMsg(out_buf, strlen(out_buf), False);

         ll = KP_MAX_FILE_LIN_LEN;
         if(SUCCEEDED(retc0))
         {
            ll = KP_MAX_FNAME_LEN;
            retc0 = sock_ptr->RcvHttpMsg(out_buf, &ll, False);
            if(retc0 == KP_E_NEG_ANSW)
            {
// iðsaugojam KP_E_NEG_ANSW
               if(SUCCEEDED(retc)) retc = retc0;
               retc0 = S_OK;
            }
            if(((ll < 0) || (ll > KP_MAX_FILE_LIN_LEN)) && SUCCEEDED(retc0))
            {
               retc0 = KP_E_BUFFER_OVERFLOW;
               KP_WARNING(retc0, null);
            }
            if(SUCCEEDED(retc0)) out_buf[ll] = Nul;
         }

// KpMsgOutF_4("KP_E_NEG_ANSW: %x  retc0: %x  retc: %x  %s", KP_E_NEG_ANSW, retc0, retc, out_buf);

         KP_DELETE(sock_ptr);

      } // if(in_file != NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}


// -------------------------------
DWORD WINAPI StartCmdThreadProc(LPVOID lpParameter)
{
HRESULT retc = S_OK;

// ----------------- thread ID
DWORD thread_id = GetCurrentThreadId();
// PutLogMessage_("StartCmdThreadProc() start: %ld", thread_id);

// ----------------- parametrai
   KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);

StartCmdThreadPars *par_ptr = (StartCmdThreadPars *)lpParameter;
   KP_ASSERT(par_ptr != NULL, E_INVALIDARG, null, True);

unsigned char cmd_buf[KP_MAX_FNAME_LEN + 1];
   KP_ASSERT(strlen(par_ptr->m_lpszCmdLine) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(cmd_buf, par_ptr->m_lpszCmdLine);

unsigned char cur_dir[KP_MAX_FNAME_LEN + 1];
   KP_ASSERT(strlen(par_ptr->m_lpszCurDir) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcpy(cur_dir, par_ptr->m_lpszCurDir);

unsigned char *start_cmd = null;
   KP_NEWA(start_cmd, unsigned char, strlen(par_ptr->m_lpszStartCmdLine) + 1);

   if(SUCCEEDED(retc)) strcpy(start_cmd, par_ptr->m_lpszStartCmdLine);

// ----------------------------- paleidþiam
HANDLE process = NULL;
   if(SUCCEEDED(retc))
   {
PutLogMessage_("StartCmdThreadProc(): StartCmdProcess(%s, %s, %s)", cmd_buf, cur_dir, start_cmd);
         retc = StartCmdProcess(cmd_buf, cur_dir, NULL, &process, False,
            SW_SHOWNORMAL /* SW_SHOWDEFAULT */, SW_SHOWMINIMIZED, False, start_cmd, True);
// StartProcess(cmd_buf, cur_dir, NULL, NULL, SW_SHOWNORMAL);
   }
   KP_ASSERT(process != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);

// ---------------------------- laukiam kol pasibaigs
DWORD exit_code = ~STILL_ACTIVE;
   if(SUCCEEDED(retc)) do
   {
      if(SUCCEEDED(retc)) KpSleep(500);
      KP_ASSERT(GetExitCodeProcess(process, &exit_code), KP_E_SYSTEM_ERROR, GetLastError(), True);
   } while((exit_code == STILL_ACTIVE) && SUCCEEDED(retc));


#if FALSE
// ------------------------- pasibaigë – ieðkom AcroRead lango
HWND dlg_wnd = NULL;
   if(SUCCEEDED(retc))
   {
unsigned char str_buf[KP_MAX_FNAME_LEN + 1];
      dlg_wnd = GetWindowByName(KPST_ACROREAD_WINDOW_NAME, False);
      if(dlg_wnd != NULL)
         if(GetWindowText(dlg_wnd, (char *)str_buf, KP_MAX_FNAME_LEN) > 0)
            if(strcmp(str_buf, KPST_ACROREAD_WINDOW_NAME) == 0) dlg_wnd = NULL;
   }
// PutLogMessage_("StartCmdThreadProc() wnd: %ld", dlg_wnd);
#endif


// ------------------------- pasibaigë – fokusuojam AcroRead langà
   if(/* (dlg_wnd != NULL) && */ SUCCEEDED(retc)) retc = theKpStAppPtr->MaximizeAcroWindowSingle(True);

// ------------------ trinam objektus
   KP_DELETEA(start_cmd);
   KP_DELETE(par_ptr);

// -------------------
// PutLogMessage_("StartCmdThreadProc() end: %ld", thread_id);

return(RET_CODE_WIN(retc));
}


// -------------------------------
HRESULT KpStApp::StartCmdThread(unsigned char *lpszCmdLine, const unsigned char *lpszPwd, const unsigned char *lpszCurDir, const unsigned char *lpszStartCmdLine)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszCmdLine != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszCurDir != null, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      if(lpszPwd == null)
      {
#if FALSE
PutLogMessage_("StartCmdThread(): StartCmdProcess(%s)", lpszCmdLine);
         retc = StartCmdProcess(lpszCmdLine, lpszCurDir, NULL, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */, SW_SHOWMINIMIZED, False, lpszStartCmdLine, True);
// StartProcess(lpszCmdLine, lpszCurDir, NULL, NULL, SW_SHOWNORMAL);
#else

StartCmdThreadPars *par_ptr = NULL;
         KP_NEW(par_ptr, StartCmdThreadPars); // naikinti nereikia, iðnaikins StartCmdThreadProc()

         if(SUCCEEDED(retc))
         {
            par_ptr->m_lpszCmdLine = lpszCmdLine;
            par_ptr->m_lpszCurDir = lpszCurDir;
            par_ptr->m_lpszStartCmdLine = lpszStartCmdLine;

DWORD thread_id = 0L;
HANDLE thread = CreateThread
            (
               NULL,                // LPSECURITY_ATTRIBUTES lpThreadAttributes,  // pointer to security attributes
               0L,                  // DWORD dwStackSize,                         // initial thread stack size
               StartCmdThreadProc,  // LPTHREAD_START_ROUTINE lpStartAddress,     // pointer to thread function
               par_ptr,               // LPVOID lpParameter,                        // argument for new thread
               0L,                  // DWORD dwCreationFlags,                     // creation flags
               &thread_id           // LPDWORD lpThreadId                         // pointer to receive thread ID
            );
            KP_ASSERT(thread != NULL, KP_E_SYSTEM_ERROR, GetLastError(), True);
// PutLogMessage_("StartCmdThread(): %ld", thread_id);

         } // if(SUCCEEDED(retc))
#endif
      }
      else // if(lpszPwd == null)
      {
// KpStApp AcroRead paleidimo á atskirà threadà nekeliam, bent jau dël tos prieþasties, kad kphp11 nëra multitaskinis
// PutLogMessage_("StartCmdThread(): StartCmd(%s, %s)", lpszCmdLine, lpszPwd);
         retc = theKpStAppPtr->StartCmd(lpszCmdLine, lpszPwd);
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->StartComplete();
      }

   } // if(SUCCEEDED(retc))

return(retc);
}


// ------------------- command socket listening idle loop
DWORD WINAPI SockListenProc(LPVOID /* lpParameter */)
{
HRESULT retc = S_OK;
HRESULT reta = S_OK;
// const unsigned char *out_str=(const unsigned char *)"&status=ðàla bàla sàla";
// const unsigned char *out_str=(const unsigned char *)"&status=kala mala";
// long read;
// static unsigned char cmd_buf[KP_MAX_FILE_LIN_LEN + 1];
#ifdef Debug
// static unsigned char log_msg[KPST_LOG_MSG_LEN + 1];
#endif
unsigned char *post_msg_buf = NULL;
long read = 0L;
unsigned char sender_ip[KP_MAX_FNAME_LEN+1]; // siuntëjo adresas
int http_ret_code;
static unsigned char out_msg[KP_MAX_FILE_LIN_LEN*2 + 1];
static unsigned char msg_buf[KP_MAX_FILE_LIN_LEN /* KP_MSG_LEN */ + 1];
static unsigned char dir_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_buf[KP_MAX_FNAME_LEN + 1];
static unsigned char cmd_buf_tmp[KP_MAX_FNAME_LEN + KP_MAX_FILE_LIN_WDT + 1]; // KP_MAX_FILE_LIN_WDT reikia dël GetIniCmdStr()
static unsigned char start_cmd[KP_MAX_FILE_LIN_WDT + 1];
const unsigned char *pnts;
unsigned char *pntd;
unsigned char *pntd1;
bool endfl = False;
unsigned char *par_ptr = null;
unsigned char *pwd_ptr = null;

   KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);
   KP_ASSERT(theKpStAppPtr->m_pListSocket, KP_E_NO_FILE, null, True);

   if(SUCCEEDED(retc)) do
   {
      reta = S_OK;

// KP_TRACE("SockListenProc(): entering Accept()");
// KpMsgOutF_0("SockListenProc(): entering Accept()");

      if(SUCCEEDED(reta) && SUCCEEDED(retc)) retc = theKpStAppPtr->m_pListSocket->Accept();
#if TRUE // #ifdef Debug
// KpMsgOut("Accepted", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
// KP_TRACE("SockListenProc(): Accept()");

      if(SUCCEEDED(reta) && SUCCEEDED(retc)) strcpy(sender_ip, theKpStAppPtr->m_pListSocket->m_PackedUrl.m_lpszServerName);

//    read=KP_MAX_FILE_LIN_LEN;
//    if(SUCCEEDED(retc)) retc = theKpStAppPtr->m_pListSocket->ReceiveMsg(cmd_buf, &read, True, False);
      if(SUCCEEDED(reta) && SUCCEEDED(retc)) reta = theKpStAppPtr->m_pListSocket->RcvHttpRequest(False);
// KP_TRACE("SockListenProc(): RcvHttpRequest()");

      if(SUCCEEDED(reta) && SUCCEEDED(retc))
         if(strcmp(sender_ip /* theKpStAppPtr->m_pListSocket->m_PackedUrl.lpszServerName */, KP_IPADDR_LOCAL_HOST) != 0)
            reta = KP_E_ACCESS_DENIED;

#ifdef Debug
// KpMsgOut(cmd_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KpMsgOut(theKpStAppPtr->m_pListSocket->m_PackedUrl.lpszFileName, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KpMsgOut(theKpStAppPtr->m_pListSocket->m_PackedUrl.lpszServerName, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

// ---------------------- to log file
#if FALSE // #ifdef Debug
      log_msg[0] = Nul;
      if(SUCCEEDED(reta) && SUCCEEDED(retc))
      {
         if((theKpStAppPtr->m_pListSocket->m_iMsgType<0) || (theKpStAppPtr->m_pListSocket->m_iMsgType >= NUM_OF_HTTP_MSG_TYPES))
         {
            retc = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
         }
         else
         {
            sprintf((char *)log_msg, "----- Gautas praneðimas: %s %s:%d %s",
               KpsockMsgTypes[theKpStAppPtr->m_pListSocket->m_iMsgType],
               theKpStAppPtr->m_pListSocket->m_PackedUrl.lpszServerName,
               theKpStAppPtr->m_pListSocket->m_PackedUrl.m_iPort,
               theKpStAppPtr->m_pListSocket->m_PackedUrl.lpszFileName);

            KP_TRACE(log_msg);
         }
      }
#endif

#if FALSE // #if TRUE //
if(read<KP_MAX_FILE_LIN_LEN) cmd_buf[read]=Nul;
else cmd_buf[KP_MAX_FILE_LIN_LEN]=Nul;
KpMsgOut(cmd_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif

      if(SUCCEEDED(reta) && SUCCEEDED(retc)) switch(theKpStAppPtr->m_pListSocket->m_iMsgType)
      {
      case HTTP_POST_REQUEST:
         if(strcmp(theKpStAppPtr->m_pListSocket->m_PackedUrl.m_lpszFileName, "/") == 0)
         {
//          reta = S_OK;
            if(SUCCEEDED(reta) && SUCCEEDED(retc))
            {
               read = theKpStAppPtr->m_pListSocket->m_lContLen + 1; // paliekam vietos galiniam nuliui
               KP_NEWA(post_msg_buf, unsigned char, read + 1); // dar kartà apsidraudþiam
            }
            if(SUCCEEDED(reta) && SUCCEEDED(retc))
            {
//             reta = theKpStAppPtr->m_pListSocket->ReceiveMsg(post_msg_buf, &read, False, False);
               reta = theKpStAppPtr->m_pListSocket->RcvHttpMsg(post_msg_buf, &read, False, False);
// KP_TRACE("SockListenProc(): ReceiveMsg()");
            }

            if(SUCCEEDED(reta) && SUCCEEDED(retc))
            {
               post_msg_buf[read] = Nul;
#if FALSE // #ifdef Debug
FILE *out_file=fopen("C:\\Temp\\http.txt", "ab");
fputs("---------------------\n>>>\n", out_file);
fputs((const char *)post_msg_buf, out_file);
fputs("<<<\n", out_file);
fclose(out_file);
#endif
// KP_TRACE(post_msg_buf);
PutLogMessage_("SockListenProc(): post_msg_buf: %s", post_msg_buf);

//             if(strcmp(post_msg_buf, "sl=0%7caaaa%7cbbbb%7c11111111111%7c1212120%7c2323233%7c343435%7c69273601%7c138547201%7c872415233%7c2081216581") == 0)

//             post_msg_buf[3] = Nul;
//             if(strcmp(post_msg_buf, "sl=") == 0)

// ------------------- Save As emuliavimas Acrobatui – emuliuojam Shift+Ctrl+'S'
//             if(strcmp(post_msg_buf, "cmd=SaveAs") == 0)

               if(strcmp(post_msg_buf, "SA=SaveAs") == 0)
               {
INPUT input_arr[6];

// Sleep(5000);

// KP_TRACE("------------ Vykdom komandà: Save As");
                  if(SUCCEEDED(reta) && SUCCEEDED(retc))
                  {
                     for(int ii = 0; ii < 6; ii++)
                     {
                        input_arr[ii].type = INPUT_KEYBOARD;
                        input_arr[ii].ki.time = 0L;
                        input_arr[ii].ki.dwExtraInfo = 0L;
                        input_arr[ii].ki.wScan = 0;
                     }

                     input_arr[0].ki.wVk = VK_SHIFT;
                     input_arr[0].ki.dwFlags = 0;
                     input_arr[1].ki.wVk = VK_CONTROL;
                     input_arr[1].ki.dwFlags = 0;
                     input_arr[2].ki.wVk = 'S';
                     input_arr[2].ki.dwFlags = 0;
                     input_arr[3].ki.wVk = 'S';
                     input_arr[3].ki.dwFlags = KEYEVENTF_KEYUP;
                     input_arr[4].ki.wVk = VK_CONTROL;
                     input_arr[4].ki.dwFlags = KEYEVENTF_KEYUP;
                     input_arr[5].ki.wVk = VK_SHIFT;
                     input_arr[5].ki.dwFlags = KEYEVENTF_KEYUP;

                     if(!SendInput(6, &input_arr[0], sizeof(input_arr[0])))
                        reta = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
// KP_TRACE("SockListenProc(): SendInput()");


//                if(SUCCEEDED(reta) && SUCCEEDED(retc))
//                {
//                   system("kpsekb.bat");
// KP_TRACE("SockListenProc(): system(\"kpsekb.bat\");");
//
//                   reta = StartProcess((const unsigned char *)"kpsekb.bat", (const unsigned char *)".", NULL, NULL, SW_SHOWMINNOACTIVE);
// KP_TRACE("SockListenProc(): StartProcess(\"kpsekb.bat\", ...);");
//                }

               }
// ------------------- garso stabdymas
               else if(strcmp(post_msg_buf, "SA=StopSound") == 0)
                  reta = theKpStAppPtr->StopSound();
               else if(strcmp(post_msg_buf, "SS=StopSound") == 0)
                  reta = theKpStAppPtr->StopSound();

// ------------------- failo atidarymas/vykdymas absoliuèiu keliu // Tado MIMOK5
// EXT=EXT%3dfile%3a%2f%2f%2fR%7c%2fMano_MaTau6e%2fBebras_TEO.tif&Mano_www_28_2=
// EXT=EXT%3dfile%3a%2f%2f%2fR%7c%2fMano_MaTau6e%2fMKRI_2009.doc&Mano_www_28_3=
//             else if(strstr(post_msg_buf, KPSTIP_EXEC_EXT_CMD) == post_msg_buf) // "EXT="
// failo atidarymas santykinai nuo produkto katalogo atmintuko flash dalyje (glob.js kintamasis "prog_path", dabar – ir kpstart.exe paleidimo katalogas)
// ar nesugedo seni Tado paleidimai, ar tikrai visuose yra absoliutus kelias?
// Raimio su Rolandu
// EXT_1=failai\dokumentas.doc
//
// mano .pdf su parametrais ir slaptaþodþiu
// EXT=cd\matematika_tau_9_1.pdf&Pars=/n/h/Apage=10&Pwd=W1X2C79t14q9
// EKO9-10
// EXT_f1010101=failai%2ff1010101.doc&f1010101=
//
               else if(strstr(post_msg_buf, "EXT") == post_msg_buf) // KPSTIP_EXEC_EXT_0_CMD
               {
                  par_ptr = null;
                  pwd_ptr = null;

                  pnts = strchr(post_msg_buf, '=');
                  if(pnts)
                  {
//                   pnts = post_msg_buf + 4; // strlen(KPSTIP_EXEC_EXT_CMD); // "EXT="
                     pnts++;

                     pntd = strchr(pnts, '&');
                     if(pntd)
                     {
                        *pntd++ = Nul;

// ieðkom papildomø parametrø
                        while(pntd != null)
                        {
                           if(strstr(pntd, "Pars=") == pntd)
                           {
                              pntd += 5; // strlen("Pars=");
                              par_ptr = pntd;
                           }

                           if(strstr(pntd, "Pwd=") == pntd)
                           {
                              pntd += 4; // strlen("Pwd=");
                              pwd_ptr = pntd;
                           }

                           pntd = strchr(pntd, '&');
                           if(pntd != null) *pntd++ = Nul;
                        }
                     }

// pntd - pagrindinio parametro pradþia buferyje post_msg_buf
                     pntd = (unsigned char *)pnts;

                     if(SUCCEEDED(reta)) reta = theKpStAppPtr->GetIniCmdStr(start_cmd);

                     if(SUCCEEDED(reta)) reta = theKpStAppPtr->DecodePostMsg(pntd, pntd);

// buvo Tado persistengimas
// EXT=file:///R|/Mano_MaTau6e/Bebras_TEO.tif
// EXT=file:///R|/Mano_MaTau6e/MKRI_2009.doc
                     if(SUCCEEDED(reta)) if(strstr(pntd, KPSTIP_EXEC_EXT_CMD) == pntd) pntd += 4; // strlen(KPSTIP_EXEC_EXT_CMD); // "EXT="

// file:///G|/Mano_MaTau6e/Bebras_TEO.tif
                     if(SUCCEEDED(reta)) if((strstr(pntd, "file://") == pntd) || (strstr(pntd, "file:\\\\") == pntd))
                        pntd += 7; // strlen("file://");

// Rolando persistengimas:
// fi|le:\\\G\Mano_ZU\x\11-12.PDF
                     if(SUCCEEDED(reta)) if((strstr(pntd, "fi|le://") == pntd) || (strstr(pntd, "fi|le:\\\\") == pntd))
                        pntd += 8; // strlen("fi|le://");

                     if(SUCCEEDED(reta)) reta = theKpStAppPtr->DecodePdfPath(pntd, pntd);

// uþdraudþiam .exe-kus
                     if(SUCCEEDED(reta)) if(
                                             (strstr(pntd, ".exe") && (strstr(pntd, "arksh.exe") == 0)) ||
                                             strstr(pntd, ".com") ||
                                             strstr(pntd, ".bat")
                                           )
                        KP_ERRORA(E_INVALIDARG, post_msg_buf);

                     cmd_buf[0] = Nul;
                     if(SUCCEEDED(reta))
                     {
                        dir_buf[0] = Nul;

// jei yra ".pdf" ir nëra ".exe" - pridedam dabar paleisto mûsø readerio AcroRd32.exe path
                        if((strstr(pntd, KPST_PDF_FILE_TYPE) || strstr(pntd, KPST_TEV_OBJ_FILE_TYPE)) && !strstr(pntd, ".exe") && !strstr(pntd, ".bin"))
                        {
                           reta = theKpStAppPtr->GetIniCmdStr(cmd_buf_tmp);
                           if(SUCCEEDED(reta))
                           {
                              cmd_buf_tmp[KP_MAX_FNAME_LEN] = Nul; // GetIniCmdStr() gràþina KP_MAX_FILE_LIN_WDT ilgio buferá, nupjaunam
                              if(strstr(cmd_buf_tmp, KPST_ACROREAD_FNAME_SHORT))
                              {
                                 strcat(cmd_buf, "\""); // átraukiam á kabutes
                                 strcat(cmd_buf, cmd_buf_tmp);
                                 pntd1 = strstr(cmd_buf, KPST_ACROREAD_FNAME_SHORT);
                                 if(pntd1) *(pntd1 + strlen(KPST_ACROREAD_FNAME)) = Nul;
                                 strcat(cmd_buf, "\""); // átraukiam á kabutes
                                 strcat(cmd_buf, " ");
                              }
                           }
                        }

// PutLogMessage_("SockListenProc() 2: [%s]", cmd_buf);
                     }

                     dir_buf[0] = Nul;
                     if(SUCCEEDED(reta))
                     {
// jei nëra ':' (santykinis kelias), pridedam glob_js parametrà prog_path
                        if(strchr(pntd, ':') == NULL)
                        {
                           reta = theKpStAppPtr->GetPdfPar(JS_PROG_PATH_PAR_NAME, cmd_buf_tmp, KP_MAX_FNAME_LEN);
                           if(SUCCEEDED(reta)) reta = theKpStAppPtr->DecodePdfPath(dir_buf, cmd_buf_tmp);
                        }

// PutLogMessage_("SockListenProc() 3: [%s]", dir_buf);
                     }

// if(par_ptr) PutLogMessage_("SockListenProc(): par_ptr: %s", par_ptr);
// if(pwd_ptr) PutLogMessage_("SockListenProc(): pwd_ptr: %s", pwd_ptr);

                     if(SUCCEEDED(reta))
                     {
                        if(par_ptr)
                        {
                           strcat(cmd_buf, par_ptr);
                           strcat(cmd_buf, " ");
                        }

// átraukiam parametrà (dokumento vardà) á kabutes, bet tik jei jau prigeneravom mûsø papildomà .exe (AcroRead.bin)
                     int quot_fl = (cmd_buf[0] != Nul);
                        if(quot_fl) strcat(cmd_buf, "\"");

                        strcat(cmd_buf, dir_buf);
                        if(dir_buf[0]) strcat(cmd_buf, "\\");

                        strcat(cmd_buf, pntd);
// strcpy(cmd_buf, "G:\\Mano_MaTau6e\\porunacabez2.wav");
// strcpy(cmd_buf, "G:\\Mano_MaTau6e\\istorija-atsklanda.bmp");
// strcpy(cmd_buf, "G:\\Mano_MaTau6e\\DSCF2614.AVI");
// strcpy(cmd_buf, "G:\\Mano_MaTau6e\\10_pamokos_medziaga.zip");
// strcpy(cmd_buf, "G:\\Mano_MaTau6e\\baubai.pas");

                        if(quot_fl) strcat(cmd_buf, "\""); // átraukiam á kabutes

#if TRUE
// iðkelta á naujà threadà
                        if(SUCCEEDED(reta)) reta = theKpStAppPtr->StartCmdThread(cmd_buf, pwd_ptr, KPST_CUR_DIR, start_cmd);
#else
                        if(pwd_ptr == null)
                        {
// PutLogMessage_("SockListenProc(): StartCmdProcess(%s)", cmd_buf);
                           reta = StartCmdProcess(cmd_buf, KPST_CUR_DIR, NULL, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */, SW_SHOWMINIMIZED, False, start_cmd, True);
                        }
                        else
                        {
// PutLogMessage_("SockListenProc(): StartCmd(%s, %s)", cmd_buf, pwd_ptr);
                           reta = theKpStAppPtr->StartCmd(cmd_buf, pwd_ptr);
                           if(SUCCEEDED(reta)) reta = theKpStAppPtr->StartComplete();
                        }
#endif
                     }

                  } // if(pnts) // pnts = strchr(post_msg_buf, '=');

                  else
                     KP_ERRORA(E_INVALIDARG, post_msg_buf);
               }

// exec'o vykdymas santykinai nuo kpstart.exe paleidimo katalogo (glob.js kintamasis "prog_path")
// ne, dabar nuo einamojo katalogo (ið atmintuko CD dalies)
// EX_1=kpscalc&calc=
// EX_2=kpsclc
               else if(strstr(post_msg_buf, KPSTIP_EXEC_0_CMD) == post_msg_buf) // "EX"
               {
                  pnts = strchr(post_msg_buf, '=');
                  if(pnts)
                  {
                     pnts++;

                     pntd = strchr(pnts, '&');
                     if(pntd) *pntd = Nul;

                     if((strcmp(pnts, "kpscalc") != 0) && (strcmp(pnts, "kpsclc") != 0) && // Waldek MIMOK6
                        (strcmp(pnts, "EPPK") != 0) && (strcmp(pnts, "EVR") != 0) && // Rolandas MI1
                        (strcmp(pnts, "MLTV") != 0) && (strcmp(pnts, "WW2") != 0) &&
                        SUCCEEDED(retc))
                     {
                        reta = E_INVALIDARG;
                        KpErrorProc.OutputErrorMessage(reta, pnts, False, __FILE__, __LINE__, 0L, NULL);
                     }

//                   if(SUCCEEDED(reta)) reta = GetAppPath(dir_buf, False); // ne, dabar kpstart.exe paleidþiamas flash dalyje
                     KP_ASSERTA(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)dir_buf), KP_E_SYSTEM_ERROR, GetLastError(), True);

                     if(SUCCEEDED(reta)) if(strlen(dir_buf) + 1 + strlen(pnts) + 4 /* strlen(".exe") */ >= KP_MAX_FNAME_LEN)
                     {
                        reta = KP_E_BUFFER_OVERFLOW;
                        KpErrorProc.OutputErrorMessage(reta, null, False, __FILE__, __LINE__, 0L, NULL);
                     }
                     if(SUCCEEDED(reta))
                     {
                        strcpy(cmd_buf, dir_buf);
                        strcat(cmd_buf, "\\");
                        strcat(cmd_buf, pnts);
//                      if((strcmp(pnts, "kpscalc") == 0) || (strcmp(pnts, "kpsclc") == 0))
                           strcat(cmd_buf, ".bin");
//                      else
//                         strcat(cmd_buf, ".exe");
#if FALSE
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
TvFnameSplit(disk, path, name, type, dir_buf);
strcpy(dir_buf, theKpStAppPtr->m_lpszFlashDevName);
if(path[0]) strcat(dir_buf, "\\");
#endif

#if FALSE // testuojam .pdf failo paleidimà (þr. "EXT=")
{
const char * pntd = "e35968001us.pdf";

cmd_buf[0] = Nul;

// jei yra ".pdf" ir nëra ".exe" - pridedam dabar paleisto mûsø readerio AcroRd32.exe path
if((strstr(pntd, KPST_PDF_FILE_TYPE) || strstr(pntd, KPST_TEV_OBJ_FILE_TYPE)) && !strstr(pntd, ".exe") && !strstr(pntd, ".bin"))
{
theKpStAppPtr->GetIniCmdStr(cmd_buf_tmp);
cmd_buf_tmp[KP_MAX_FNAME_LEN] = Nul;
if(strstr(cmd_buf_tmp, KPST_ACROREAD_FNAME_SHORT))
{
strcpy(cmd_buf, cmd_buf_tmp);
unsigned char *pntd1 = strstr(cmd_buf, KPST_ACROREAD_FNAME_SHORT);
if(pntd1) *(pntd1 + strlen(KPST_ACROREAD_FNAME)) = Nul;
strcat(cmd_buf, " ");
}
}

dir_buf[0] = Nul;
// jei nëra ':' (santykinis kelias), pridedam glob_js parametrà prog_path
if(strchr(pntd, ':') == NULL)
{
// strcat(dir_buf, "G:\\DAM1");
theKpStAppPtr->GetPdfPar(JS_PROG_PATH_PAR_NAME, cmd_buf_tmp, KP_MAX_FNAME_LEN);
theKpStAppPtr->DecodePdfPath(dir_buf, cmd_buf_tmp);
}

strcat(cmd_buf, dir_buf);
if(dir_buf[0]) strcat(cmd_buf, "\\");

strcat(cmd_buf, pntd);
// KpMsgOutF(cmd_buf);
}
#endif

#if TRUE
// iðkelta á naujà threadà
                        if(SUCCEEDED(reta)) reta = theKpStAppPtr->StartCmdThread(cmd_buf, null, dir_buf, (const unsigned char *)"");
#else
                        reta = StartCmdProcess(cmd_buf, dir_buf, NULL, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
// StartProcess(cmd_buf, dir_buf, NULL, NULL, SW_SHOWNORMAL);
#endif
                     }
                  } // if(pnts) // pnts = strchr(post_msg_buf, '=');

                  else
                     KP_ERRORA(E_INVALIDARG, post_msg_buf);
               }

// ------------------- set currend dir, lock instance
// CD=E:\DAT5
               else if(strstr(post_msg_buf, KPSTIP_ALIVE_CMD) == post_msg_buf) // "CD="
               {
// vartotojo aplikacija kpstart.exe vis dar gyva – atnaujinam lockinimo nusiëmimo taimerá
                  PostThreadMessage(iKpMainThread, KPST_WM_BLOCK_SES, 0L, 0L);

                  if(!SetCurrentDirectory((const char *)post_msg_buf + strlen(KPSTIP_ALIVE_CMD))) // "CD="
                  {
                     reta = KP_E_SYSTEM_ERROR;
                     /* reta = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                     /* reta = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, post_msg_buf, False, __FILE__, __LINE__, 0L, NULL);
                  }

                  if((!theKpStAppPtr->m_bInstanceLocked) && SUCCEEDED(reta))
                  {
                     theKpStAppPtr->m_bInstanceLocked = True;
PutLogMessage_("---------------- SockListenProc: SendHttpMsg() 1 %x %x", reta, retc);
                     reta = theKpStAppPtr->m_pListSocket->SendHttpMsg(KPSTAP_SVR_ANSWER_OK, False, (const unsigned char *)"text/plain", HTTP_ANSW_OK);
PutLogMessage_("---------------- SockListenProc: SendHttpMsg() 1 grizom %x %x", reta, retc);
                  }
                  else
PutLogMessage_("---------------- SockListenProc: SendHttpMsg() 2 %x %x", reta, retc);
                  /* reta = */ theKpStAppPtr->m_pListSocket->SendHttpMsg(KPSTAP_SVR_ANSWER_ERROR, False, (const unsigned char *)"text/plain", HTTP_ANSW_CONFLICT); // 409); // "Conflict"
PutLogMessage_("---------------- SockListenProc: SendHttpMsg() 2 grizom %x %x", reta, retc);
               }

// ------------------- set safe dir, unlock instance, quit the server
// RD=C:\Program Files
               else if(strstr(post_msg_buf, KPSTIP_DISCONNECT_CMD) == post_msg_buf) // "RD="
               {
                  if(theKpStAppPtr->m_iSesCtrlTimer) KillTimer(HWND_DESKTOP, theKpStAppPtr->m_iSesCtrlTimer);

                  if(!SetCurrentDirectory((const char *)post_msg_buf + strlen(KPSTIP_DISCONNECT_CMD))) // "RD="
                  {
                     /* reta = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                     /* reta = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, post_msg_buf, False, __FILE__, __LINE__, 0L, NULL);
                  }

                  theKpStAppPtr->m_bInstanceLocked = False;

                  if(!theKpStAppPtr->m_bCheckUpdPending) endfl = True;
               }

// ------------------- check update
// CU=WinLED.exe&PI=R5LG-J135-AJ9A-E8J6	LJ88-23JJ-A2J5-JAU1	0	[dBI+9,+B150:=)7=+BZ/;)190*+B	0	0	1	43627	RRqmnkqQj	150:=)7=+	40	0	2	6	1		7600	0&ProdVer=3012&ProdVar=0
// Pirmo parametro reikðmë – produkto lango pavadinimas (.ini failo parametras KpStIniData::m_lpszWndName, GetIniWndName())
//    Pagal já uþdaromas atnaujinamo produkto langas, jeigu paleistas
// Galas nuo PI= – tiksliai, kas turi bûti siunèiama á http://updates.tev.lt/versija.php (KPST_CHK_UPDATE_URL)
               else if(strstr(post_msg_buf, KPSTIP_CHK_UPDATE_CMD) == post_msg_buf) // "CU="
               {
               /* reta = */ theKpStAppPtr->StartCheckUpdateThread(post_msg_buf);
                  post_msg_buf = null; // netrinam, kad buferis pasiektø threado funkcijà
               }

// ------------------- nepaþástama komanda
               else
                  KP_ERRORA(E_INVALIDARG, post_msg_buf);
            }

            KP_DELETEA(post_msg_buf);
         }
         else // if(strcmp(theKpStAppPtr->m_pListSocket->m_PackedUrl.lpszFileName, "/") == 0)
            reta = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
         break;

      case HTTP_GET_REQUEST:
         if((theKpStAppPtr->m_pcListBuf != NULL) && (theKpStAppPtr->m_lListBufLen > 0))
         {
unsigned char *msg_buf = NULL;

            KP_NEWA(msg_buf, unsigned char, theKpStAppPtr->m_lListBufLen + KP_MAX_FNAME_LEN + 100);

            if(SUCCEEDED(retc))
            {
               memcpy(msg_buf, theKpStAppPtr->m_pcListBuf, theKpStAppPtr->m_lListBufLen);
               msg_buf[theKpStAppPtr->m_lListBufLen] = Nul;
#if FALSE
               strcat(msg_buf, "\nWorking directory: ");
               KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)msg_buf + strlen(msg_buf)), KP_E_SYSTEM_ERROR, GetLastError(), False);
#endif
//             reta = theKpStAppPtr->m_pListSocket->SendMsg(theKpStAppPtr->m_pcListBuf, theKpStAppPtr->m_lListBufLen, True);
               reta = theKpStAppPtr->m_pListSocket->SendMsg(msg_buf, strlen(msg_buf), True);
// KpMsgOut("Sent", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KP_TRACE("SockListenProc(): SendMsg()");
            }

            KP_DELETEA(msg_buf);
         }
         break;

      default:
         reta = KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
         break;

      } // switch(theKpStAppPtr->m_pListSocket->m_iMsgType)

      if(SUCCEEDED(retc)) if(FAILED(reta))
      {
         http_ret_code = KpErrorProc.TranslToHTTP_RetCode(reta);
         strcpy(out_msg, KPST_IP_ERROR);
         retc = KpErrorProc.FormatErrorMessage(reta, msg_buf);
         if(SUCCEEDED(retc)) strcat(out_msg, msg_buf);

PutLogMessage_("---------------- SockListenProc: SendHttpMsg() 3 %x %x", reta, retc);
      /* retc = */ theKpStAppPtr->m_pListSocket->SendHttpMsg(out_msg, False, (unsigned char *)"text/plain", http_ret_code); // "text/html; charset=ISO-8859-13"
PutLogMessage_("---------------- SockListenProc: SendHttpMsg() 3 grizom %x %x", reta, retc);
      }

   } while((!endfl) && SUCCEEDED(retc));

// PostQuitMessage(SUCCEEDED(retc)?IDOK:IDABORT);
   PostThreadMessage(iKpMainThread, WM_QUIT, SUCCEEDED(retc)?IDOK:IDABORT, 0L);

return(RET_CODE_WIN(retc));
}


// -----------------------------------------
#if FALSE
HRESULT KpStApp::CheckSockCmd(void)
{
HRESULT retc=S_OK;

#ifdef KPST_USE_SOCKET
   if(SUCCEEDED(retc))
   {
      if(m_pListSocket==NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_NO_FILE, null, False, __FILE__, __LINE__, 0L, NULL);
      else
      {
// KpMsgOut("Before Accept", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
         if(SUCCEEDED(retc)) retc = m_pListSocket->Accept();
// KpMsgOut("After Accept", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

         retc = S_OK;

      } // else // if(m_pListSocket==NULL)

   } // if(SUCCEEDED(retc))
#endif

return(retc);
}
#endif


// -----------------------------------------
HRESULT KpStApp::CheckClipCmd(void)
{
HRESULT retc=S_OK;

#ifdef KPST_USE_CLIPBOARD

unsigned char clip_buf[KP_MAX_FILE_LIN_LEN+1];
unsigned char *pt_hat=NULL;
unsigned char *pt_cmd=NULL;
unsigned char *pt_par=NULL;
unsigned char *pt_parend=NULL;
int cmd_idx;

   if(SUCCEEDED(retc))
   {
      retc=GetClipboardText(/* m_hBitmapWindow */ HWND_DESKTOP, clip_buf, KP_MAX_FILE_LIN_LEN, False);
      clip_buf[KP_MAX_FILE_LIN_LEN]=Nul;
      if(FAILED(retc))
      {
         retc=S_OK;
         clip_buf[0]=Nul;
      }
      else
      {
         pt_hat=clip_buf;
         pt_cmd=TvStrChr(pt_hat, KPST_CLIP_CMD_DELIM); // '|'
         if(pt_cmd==NULL)
         {
//          retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
         }
         else
         {
            *(pt_cmd++)=Nul;
            if(strcmp(pt_hat, KPST_CLIP_CMD_HAT)!=0)
            {
//             retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
            }
            else
            {
               pt_par=TvStrChr(pt_cmd, KPST_CLIP_CMD_DELIM); // '|'
               if(pt_par!=NULL)
               {
                  *(pt_par++)=Nul;

                  pt_parend=TvStrChr(pt_par, KPST_CLIP_CMD_DELIM); // '|'
                  if(pt_parend==NULL)
                     retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
                  else *pt_parend=Nul;

                  if(*pt_par!='\"')
                     retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
                  else pt_par++;

                  pt_parend=TvStrChr(pt_par, '\"');
                  if(pt_parend==NULL)
                     retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
                  else *pt_parend=Nul;
               }

               retc=GetKwrdIndex(&cmd_idx, pt_cmd, lpszaKpstClipCmds, -1, True, True);
               if(FAILED(retc))
                  retc=KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L, NULL);
               else
               {
                  switch(cmd_idx)
                  {
                     case KpstCloseWindow:  // "CW"
                        if(pt_par==NULL)
                           retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
                        else
                           /* retc= */ KpCloseWindow(pt_par);

                     /* retc= */ SetClipboardText(/* m_hBitmapWindow */ HWND_DESKTOP, (const unsigned char *)"");
                        break;

                     case KpstPutMsg:       // "PM"
                        if(pt_par==NULL)
                           retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
                        else
                           retc=KpMsgOut(pt_par, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

                     /* retc= */ SetClipboardText(/* m_hBitmapWindow */ HWND_DESKTOP, (const unsigned char *)"");
                        break;

                     default:
//                      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);
                        break;

                  } // switch(cmd_idx)

//             /* retc= */ SetClipboardText(/* m_hBitmapWindow */ HWND_DESKTOP, (const unsigned char *)"");

               } // else // if(FAILED(retc))

            } // else // if(strcmp(pt_hat, KPST_CLIP_CMD_HAT)!=0)

         } // else // if(pt_cmd==NULL)

      } // else // if(FAILED(retc))

   } // if(SUCCEEDED(retc))

#endif

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::WatchExec(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
DWORD exit_code;
// BOOL msg_ready;
MSG msg;
int retp;
bool endfl = False;
// unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

   if(SUCCEEDED(retc)) do
   {
//    if(SUCCEEDED(retc)) msg_ready=PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
//    if(msg_ready && SUCCEEDED(retc))

      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp = LOWORD(msg.wParam);
         exit_code = (m_hCmdProcess || m_lCmdThread || m_hCmdThread || (m_iKpStMode == KpStrpdMode))?STILL_ACTIVE:(~STILL_ACTIVE);
      }

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_TIMER:
         if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iProcCmdTimer)
         {
// bool on_top = False;

//          if(SUCCEEDED(retc)) retc = GetIniOnTop(&on_top);

// uzdaryti langelius "Launch: ..."
            if(SUCCEEDED(retc)) retc = CloseLaunchPrompt();
            if(SUCCEEDED(retc)) retc = CloseAutoPlay();
            if(SUCCEEDED(retc)) retc = CloseCompatibilityAssistant();

// ar programa dar gyva?
#if FALSE // #ifdef Debug //
char str_buf[20];
static ii;
// sprintf(str_buf, "m_iProcCmdTimer: %d %d", ii++, on_top);
sprintf(str_buf, "m_iProcCmdTimer: %d", ii++);
KP_TRACE(str_buf);
#endif

            if((m_iKpStMode != KpStrpdMode) && SUCCEEDED(retc))
            {
               if(m_hCmdProcess)
               {
                  if(!GetExitCodeProcess(m_hCmdProcess, &exit_code))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE_3("GetExitCodeProcess(): %x  retc: %x  STILL_ACTIVE: %x", exit_code, retc, STILL_ACTIVE)
               }
               else if(m_hCmdThread)
               {
                  if(!GetExitCodeThread(m_hCmdThread, &exit_code))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
// KP_TRACE_3("GetExitCodeThread(): %x  retc: %x  STILL_ACTIVE: %x", exit_code, retc, STILL_ACTIVE)
               }
               else exit_code = (~STILL_ACTIVE);
            }

// maximizuoti/aktyvuoti programos langa
            if((exit_code == STILL_ACTIVE) && SUCCEEDED(retc))
            {
HWND pwd_wnd = 0;
// HWND save_as_wnd = 0;
               pwd_wnd = GetWindowByName((const unsigned char *)"Password", True);
//             save_as_wnd=GetWindowByName((const unsigned char *)"Save As", True);
//             if(!save_as_wnd)
//                save_as_wnd=GetWindowByName((const unsigned char *)"_raðyti kaip", True);

//             retc = MaximizeAcroWindowSingle();

               if(!m_lStartTime) time(&m_lStartTime);

#if TRUE // #if FALSE
//             if(on_top)
//             {
// jei yra slaptazodzio ar "save as" langas - nemaximizuoti
//                if((!pwd_wnd) && (!save_as_wnd))
//                      retc = MaximizeAcroWindowSingle(False);
//             }
#  if TRUE // #  if FALSE
//             else // if(m_bMaximizeAcroWindow)
//             {
// maximize only during the very first half minute after start
//                if(!m_lStartTime) retc=MaximizeAcroWindowSingle(False);
//                else
//                {
// jei yra langas "Password", pratesti maximizavimo laika (arkim, bebras - maksimizuoti tik po slaptazodzio ivedimo)
                     if(pwd_wnd)
                     {
                        time(&m_lStartTime);
//                      m_lStartTime = time(NULL);
//                      retc = MaximizeAcroWindowSingle(False);
                     }
                     else
                     {
                        if(SUCCEEDED(retc)) /* retc = */ HideBookMarks(); // slepia, tik jei langas jau maximizuotas, todël prieð MaximizeAcroWindowSingle()

//                      if(SUCCEEDED(retc)) if(time(NULL)-m_lStartTime <= 30)
//                         retc = MaximizeAcroWindowSingle(True);
                        if(SUCCEEDED(retc)) retc = MaximizeAcroWindowSingle(time(NULL) - m_lStartTime <= KPST_ACRO_MAXIMIZE_TIMEOUT);
                     }

//                } // else // if(!m_lStartTime)

//             } // else if(m_bMaximizeAcroWindow) // if(on_top)
#  endif
//             else
//                retc=MaximizeAcroWindowSingle(True);
#endif

               if(SUCCEEDED(retc)) if(m_bSoundPlaying) if(time(NULL) - m_lStartTime > KPST_SOUND_STOP_TIMEOUT)
               {
//                retc = StopSound();
                  retc = FadeSound(70);
               }

            } // if((exit_code == STILL_ACTIVE) && SUCCEEDED(retc))

//          if(SUCCEEDED(retc)) if(time(NULL) - m_lStartTime <= 5) retc = MinimizeIEWindow();

// ---------------------- close bitmap

            /* if(SUCCEEDED(retc)) */ if((m_iKpStMode==KpStarterMode) && (m_hBitmapWindow!=NULL)) if(time(NULL) - m_lStartTime >= 5)
            {
//             KP_ASSERT0(::DestroyWindow(m_hBitmapWindow), KP_E_SYSTEM_ERROR, GetLastError(), False);
KpWnd *bmp_wnd = NULL;
               retc0 = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
               if((bmp_wnd != NULL) && SUCCEEDED(retc0)) retc0 = DeleteWnd(bmp_wnd);

               m_hBitmapWindow = NULL;
            }

#if FALSE // #ifdef Debug
static int ii;
KP_TRACE_5("exit_code: %x  m_hCmdProcess: %d  m_lCmdThread: %d  m_hCmdThread: %d  %d", exit_code, m_hCmdProcess, m_lCmdThread, m_hCmdThread, ii++);
#endif
         } // if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iProcCmdTimer)

// ------------------------------------------------------------------
//       if(SUCCEEDED(retc)) if(retp == m_iRestMinsTimer)
//       {
// KpMsgOutF("WatchExec() WM_TIMER m_iRestMinsTimer");
// èia neapdorojam, ateina ir á KpStaWindowProc()
// èia neateina tux_ipa ir XFS aplikacijose
//       }

         break; // case WM_TIMER:

      case WM_COMMAND:
PutLogMessage_("WatchExec() WM_COMMAND: %d %ld", retp, msg.lParam);
         switch(retp)
         {
#if FALSE
// ðiaip jau apdorojimas yra ir KpStaWindowProc()
// èia niekada neateina – suvalgo anksèiau esantys praneðimø imtuvai
         case KPST_ID_REST_DAYS_EXCEEDED:
            if(msg.lParam <= KPST_REST_DAYS_WARNING)
            {
               if(msg.lParam <= 0)
               {
static unsigned char str_buf[2000];
                  sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
                  KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
                  KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                  endfl = True;
                  retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
               }
               else
               {
                  if(!RestDaysWarningShowed())
                  {
                     switch(msg.lParam)
                     {
                     case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
                     case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
                     default: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, msg.lParam); break;
                     }
                  }
//                m_iRestDaysWarningShowed = True;
                  KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
               }
            }
            break;
#endif
         case IDCANCEL:
            endfl = True;
            retc = KP_E_CANCEL;
            break;
         }
         break;

      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl = True;
         break;

      } // if(SUCCEEDED(retc)) switch(msg.message)

      if((exit_code == STILL_ACTIVE) && SUCCEEDED(retc)) KpStaWindowProc(msg.hwnd, msg.message, msg.wParam, msg.lParam);

// --------------------------------
//    if((exit_code==STILL_ACTIVE) && SUCCEEDED(retc)) KpSleep(KPST_PROC_CMD_TIMEOUT, HWND_DESKTOP);

   } while((!endfl) && (exit_code==STILL_ACTIVE) && SUCCEEDED(retc));

// ----------------------------------
   if(m_hBitmapWindow != NULL)
   {
//    KP_ASSERT0(::DestroyWindow(m_hBitmapWindow), KP_E_SYSTEM_ERROR, GetLastError(), False);
KpWnd *bmp_wnd = NULL;
      retc0 = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
      if((bmp_wnd != NULL) && SUCCEEDED(retc0)) retc0 = DeleteWnd(bmp_wnd);

      m_hBitmapWindow = NULL;
   }

// ----------------------------------
   if((exit_code==STILL_ACTIVE) && m_hCmdProcess && FAILED(retc))
   {
      if(!TerminateProcess(m_hCmdProcess, RET_CODE_MAIN(retc)))
         /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False /* True */, __FILE__, __LINE__, 0L, NULL); // Elvyrai Dainauskienei lenda klaida
      m_hCmdProcess = NULL;
      m_hCmdThread = NULL;
      m_lCmdThread = 0L;
   }
// if((exit_code==STILL_ACTIVE) && (m_lCmdThread /* || m_hCmdThread */) && FAILED(retc))
// {
//    if(!TerminateThread(m_hCmdThread, RET_CODE_MAIN(retc))) // nëra tokios funkcijos
//       /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//    m_hCmdThread = NULL;
//    m_lCmdThread = 0L;
// }

   if(exit_code != STILL_ACTIVE)
   {
      m_hCmdProcess = NULL;
      m_hCmdThread = NULL;
      m_lCmdThread = 0L;
   }

return(retc);
}




// -----------------------------------------
HRESULT KpStApp::CloseStApp(HRESULT hRetc, LocalPaths iTxtFileLocation)
{
HRESULT retc = hRetc; // S_OK;
HRESULT retc0 = S_OK;
// unsigned char **words=NULL;
// int word_cnt;
bool data_ok=False;
// unsigned char *pntd;
unsigned char cmd_buf[100];
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
unsigned char rez_var[KP_MAX_FNAME_LEN+1];
unsigned char epil_fname[KP_MAX_FNAME_LEN+1];
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
int num_of_lics=0;
int epil_sh_time=0;
#ifdef Debug
#ifdef DebugStop
char str_buf[KP_MAX_FNAME_LEN+100];
#endif
#endif
bool subst = False;
KpSocket *sock_ptr = NULL;
static unsigned char out_buf[KP_MAX_FNAME_LEN+100];
static unsigned char cur_dir[KP_MAX_FNAME_LEN + 1];
static unsigned char svr_data_path[KP_MAX_FNAME_LEN + 100];
FILE *in_file = NULL;

// --------------------
   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);

   if(SUCCEEDED(retc)) retc=GetIniRezVar(rez_var);
   if(SUCCEEDED(retc)) retc=GetIniEpilFName(epil_fname);
   if(SUCCEEDED(retc)) retc=GetIniEpilShowTime(&epil_sh_time);

   cmd_str[0] = Nul;
   /* if(SUCCEEDED(retc)) retc = */ GetIniCmdStr(cmd_str);

   retc0=GetIniNumOfLics(&num_of_lics); if(SUCCEEDED(retc)) retc=retc0; if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc=GetIniSubst(&subst);

// --------------------
// if(SUCCEEDED(retc)) retc = GetAppPath(cur_dir, True);

   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)cur_dir), KP_E_SYSTEM_ERROR, GetLastError(), True);
   if(SUCCEEDED(retc)) strcat(cur_dir, "\\");

// --------------------
// PutLogMessage_("KpStApp::CloseStApp() URS");
   UnRegSert();

// --------------------
   if(SUCCEEDED(retc)) if(
//    (
//       (strlen(epil_fname)>0) ||
//       (strlen(rez_fname)>0) ||
//       (m_lAttOff!=0L)
//    ) &&
      (m_iKpStMode==KpStarterMode) // && SUCCEEDED(retc)
     )
   {

      if(/* SUCCEEDED(retc) && */ (m_hBitmapWindow != NULL))
      {
//       KP_ASSERT0(::DestroyWindow(m_hBitmapWindow), KP_E_SYSTEM_ERROR, GetLastError(), False);
KpWnd *bmp_wnd = NULL;
         retc0 = GetCurWindow(&bmp_wnd, m_hBitmapWindow);
         if((bmp_wnd != NULL) && SUCCEEDED(retc0)) retc0 = DeleteWnd(bmp_wnd);

         m_hBitmapWindow = NULL;
      }

// ---------------------- wait while main procedure ends
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.1 WaitForProcessEnd", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

      if((m_hCmdProcess || m_hCmdThread /* || m_lCmdThread */) && SUCCEEDED(retc))
      {
         retc = WaitForProcessEnd(m_hCmdProcess, m_hCmdThread);
         if(SUCCEEDED(retc)) KpSleep(1000, HWND_DESKTOP); // Sleep(1000);
      }
      m_hCmdProcess = NULL;
      m_hCmdThread = NULL;
      m_lCmdThread = 0L;

// -------------------------- get result data
      if((strlen(rez_fname)>0) && SUCCEEDED(retc))
      {
// ---------------------- get clipboard data
         m_ClipBuf[0]=Nul;
// !!!! Clipboard'a uzdarem galutinai
//       if(SUCCEEDED(retc)) retc=GetClipPars(m_ClipBuf, KP_MAX_FILE_LIN_LEN, &data_ok);

// ---------------------- get PDF pars
         m_PdfParBuf[0]=Nul;
// ið glob.js rezultatø jau nebeskaitom – kad senos ðiukðlës netrukdytø (pas Rolandà buvo kintamasis "klase")
#if FALSE
         if(SUCCEEDED(retc))
         {
// numetam tarpus galuose, be to dar Cr/Lf gale kartais buna
            CutInitTrailSpcs(rez_var);
            pntd=rez_var+strlen(rez_var);
            while(pntd>rez_var)
            {
               if(TvStrChr(lpszWordDelims, (KpChar)*(pntd-1))!=NULL) pntd--;
               else break;
            }
            *pntd = Nul;

            if(strlen(rez_var) != 0)
            {
               words = NULL;
               retc = SplitStrings(&words, &word_cnt, rez_var, lpszWordDelims, False);

#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.2 GetPdfPars", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

               if(SUCCEEDED(retc))
                  retc = GetPdfPars(m_PdfParBuf, KP_MAX_FILE_LIN_LEN, (const unsigned char **)words, &data_ok);
               KP_DELETEA(words);
            }
         }
#endif

// ---------------------- get data from .txt file
         m_FileDataBuf[0]=Nul;
         if(SUCCEEDED(retc)) retc=GetFilePars(m_FileDataBuf, KP_MAX_FILE_LIN_LEN, &data_ok, iTxtFileLocation);

// ---------------------- write results
#ifdef Debug
#ifdef DebugStop
{
sprintf(str_buf, "4.3 WriteDataFile [%s]", rez_fname);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
}
#endif
#endif
         if(/* data_ok && */ SUCCEEDED(retc)) retc=WriteDataFile(m_FileDataBuf, m_PdfParBuf, m_ClipBuf, False, True);

      } // if((strlen(rez_fname)>0) && SUCCEEDED(retc))

// ---------------------- start epilogue
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.6 StartEpilogue", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

      if(SUCCEEDED(retc)) if(strlen(epil_fname)>0)
      {
         if(SUCCEEDED(retc))
            m_RetcPr = StartCmdProcess(epil_fname, KPST_CUR_DIR, &m_lEpilThreadId, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
         if(SUCCEEDED(m_RetcPr) && SUCCEEDED(retc))
         {
            retc=KpSleep(epil_sh_time*1000, NULL);

// ---------------------- close epilogue
            m_RetcPr=CloseProcess(epil_fname, m_lEpilThreadId);
            if(SUCCEEDED(retc)) retc=m_RetcPr;
         }
         m_lEpilThreadId=0L;
      }

   } //    (m_iKpStMode==KpStarterMode) // && SUCCEEDED(retc)

// ----------------------------
   if(num_of_lics && (m_iKpStMode==KpStarterMode))
   {
      retc0=RemoveReg(retc, m_hInstance);
      if(SUCCEEDED(retc)) retc=retc0;
   }


// ---------------------------- perjungiam IP komandø serveriukà á saugø katalogà
/* if(SUCCEEDED(retc)) */ if(
      (m_iKpStMode==KpStarterMode) && (hRetc != KP_E_NEG_ANSW) // && SUCCEEDED(retc)
     )
   {
      retc0 = S_OK;

// ---------------------
      strcpy(svr_data_path, cur_dir);
      strcat(svr_data_path, KPSTAP_SVR_DATA_FILE);

// ar yra kpstdf.bin? jei ne – èia ne leidybinis projektas, kpstisvr.exe nusibaigs savaime, kurá laikà negavæs "CD="
// "RD=" siøsti bet kokiu atveju negalima, nes numuð tuo metu atviro leidybinio projekto paleistà kpstisvr.exe
      in_file = fopen((const char *)svr_data_path, "rb");
      if(in_file != NULL)
      {
         fclose(in_file);

// --------------------
         if(SUCCEEDED(retc0))
         {
            KP_NEWO(sock_ptr, KpSocket);
            retc0 = retc;
         }

         if(SUCCEEDED(retc0)) retc0 = sock_ptr->GetOpenResult();

         if(SUCCEEDED(retc0)) retc0 = sock_ptr->Resolve(KPST_IP_CMD_URL, False); // "http://127.0.0.1:49494/"
         if(SUCCEEDED(retc0)) retc0 = sock_ptr->Connect(False);

         if(SUCCEEDED(retc0))
         {
            strcpy(out_buf, KPSTIP_DISCONNECT_CMD); // "RD="
            retc0 = GetLocalPath(out_buf + strlen(out_buf), KP_Program_Files);
         }

         if(SUCCEEDED(retc0))
            retc0 = sock_ptr->SendHttpRequest(HTTP_POST_REQUEST_CMD,
                  (const unsigned char *)"/", // failo vardas // KPST_IP_CMD_URL, // "http://127.0.0.1:49494/"
                  False, strlen(out_buf)); // "POST"

         if(SUCCEEDED(retc0)) retc0 = sock_ptr->SendMsg(out_buf, strlen(out_buf), False);

         KP_DELETE(sock_ptr);

      } // if(in_file) // in_file = fopen((const char *)svr_data_path, "rb");

   } // if((m_iKpStMode == KpStarterMode) && (hRetc != KP_E_NEG_ANSW) // && SUCCEEDED(retc)


// ------------------------- stop socket listenning - dangerous
// Vistoje kaþkodël likdavo kabët Accept socketas - paleidus ið naujo neleisdavo prisijungt prie porto -
//    CreateSockThread() gràþindavo KP_E_NO_CONN
// threadui m_hListThread reikia THREAD_TERMINATE access - neþinau kaip nustatyti
// ir iþvis èia nerekomenduojamas elgesys
// jau pataisiau – SO_REUSEADDR prie KpSocket::Bind() – naikinam
#if FALSE
   if(m_hListThread)
   {
      if(!TerminateThread(m_hListThread, RET_CODE_MAIN(retc)))
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }
   m_lListThreadId = 0L;
   m_hListThread = NULL;
#endif

   KP_DELETE(m_pListSocket);
   KP_DELETE(m_pLicListSocket);

   if(WSACleanup())
   {
//    /*retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, WSAGetLastError(), False, __FILE__, __LINE__, 0L);
   }


// ----------------------------
/* if(SUCCEEDED(retc)) */ if(
//    (
//       (strlen(epil_fname)>0) ||
//       (strlen(rez_fname)>0) ||
//       (m_lAttOff!=0L)
//    ) &&
      (
         (m_iKpStMode == KpStarterMode)
//       || (m_iKpStMode == KpStRegMode) // registratoriui nereikia atstatinët – paliekam visam laikui; jeigu registratorius numuð ádiegto acrobato registrus – atsistatys po pirmo paleidimo
      ) // && SUCCEEDED(retc)
     )
   {

// --------------------
//    if(SUCCEEDED(retc)) retc = GetClipboardText(unsigned char *lpszClipData, int iBufSize, bool bTestErrors);

      retc0 = CloseClipViewer();
//    if(SUCCEEDED(retc)) retc=retc0;

// ------------------------- msvcp60.dll
      retc0 = RestoreDllsAll();
      if(SUCCEEDED(retc)) retc = retc0;

#ifndef TUX_LIB
// ------------------------- acroread 5.0 initial settings
      /* if(SUCCEEDED(retc)) */ if(strstr(cmd_str, KPST_ACROREAD50_PATHNAME)) /* retc = */ RestoreAcro50();

// ------------------------- acroread 6.0 initial settings
//    /* if(SUCCEEDED(retc)) */ if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT)) /* retc = */ ResetAcro60();
      /* if(SUCCEEDED(retc)) */ if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT)) /* retc = */ RestoreAcro60();

// ------------------------- acroread 7.0 initial settings
      /* if(SUCCEEDED(retc)) */ if(strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT)) /* retc = */ RestoreAcro70();

// ------------------------- acroread 8 initial settings
      /* if(SUCCEEDED(retc)) */ if(strstr(cmd_str, KPST_ACROREAD80_PATHNAME) || strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT)) /* retc = */ RestoreAcro80();

// ------------------------- acroread 9.0 initial settings
      /* if(SUCCEEDED(retc)) */ if(strstr(cmd_str, KPST_ACROREAD90_PATHNAME) || strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT)) /* retc = */ RestoreAcro90();
#endif // #ifndef TUX_LIB

// --------------------
      retc0 = DelAttachment();
      if(SUCCEEDED(retc)) retc=retc0;

// ------------------------------------------
#if FALSE // gal arkimui ir bebrui reikëtø palikt - ten, kur yra RezFName
   /* if(SUCCEEDED(retc)) retc = */ RestoreGlobalJs();
#else
#if FALSE // dabar ið vis nieko nedarom (2009.04.28) – Tadas saugoja vartotojo duomenis – varneles, kad jau nereikia rodyt pradinës informacijos, pavyzdþiui
   /* if(SUCCEEDED(retc)) retc = */ DeleteGlobalJs();
#else
   /* if(SUCCEEDED(retc)) retc = */ DeleteGlobalJsVariables();
#endif
#endif

   /* if(SUCCEEDED(retc)) retc = */ DeleteUserJscripts();

// ----------------------------
   /* if(SUCCEEDED(retc)) retc = */ DeleteObjFiles();

// --------------------
   } // if(m_iKpStMode==KpStarterMode)

   if((m_iKpStMode==KpStLicSvrMode) && num_of_lics /* && SUCCEEDED(retc)*/)
   {
      retc0=SaveLicences(False);
      if(SUCCEEDED(retc)) retc=retc0;
   }

// ---------------- un'subst
   if(subst /* && SUCCEEDED(retc) */)
   {
//    if(SUCCEEDED(retc))
         if(!SetCurrentDirectory("C:\\"))
            if(SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);

      if((strlen(m_lpszDrivePath)>0) /* && SUCCEEDED(retc) */)
      {
         sprintf((char *)cmd_buf, "subst %s /D", m_lpszDrivePath);
         retc0 = StartProcess(cmd_buf, KPST_CUR_DIR, NULL, NULL, SW_SHOWMINIMIZED);
         if(SUCCEEDED(retc)) retc=retc0;

//       system((const char *)cmd_buf);

//       FILE *out_file=fopen("kp2835.bat", "w");
//       fprintf(out_file, (const char *)cmd_buf);
//       fprintf(out_file, "\n");
//       fprintf(out_file, "pause");
//       fclose(out_file);
//       system("kp2835.bat");
      }
   } // if(subst /* && SUCCEEDED(retc) */)

// ------------------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.7 StopKpHp11", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   retc0 = EmuTv.StopThread();
   if(SUCCEEDED(retc)) retc = retc0;

// retc0 = StopHp11();
// if(SUCCEEDED(retc)) retc = retc0;

// ------------------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.8 CloseCommonApp", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif
   retc0=CloseCommonApp();
   if(SUCCEEDED(retc)) retc=retc0;

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::StartHp11(HINSTANCE hInstance)
{
HRESULT retc = S_OK;

#ifdef Debug
   retc=EmuTv.KpHp11CreateThread(hInstance, False); // True); //
#else
   retc=EmuTv.KpHp11CreateThread(hInstance, False);
#endif

return(retc);
}



// -----------------------------------------
#if FALSE
HRESULT KpStApp::StopHp11(void)
{
HRESULT retc = S_OK;

   for(int ii = 0; (ii < KP_TIMEOUT_TIMEOUT/KPST_STOP_PROCESS_POLLING_TIMER) && SUCCEEDED(retc); ii++)
   {
      if(EmuTv.m_lKphp11ThreadId != 0L)
         PostThreadMessage(EmuTv.m_lKphp11ThreadId, WM_QUIT, IDCANCEL, 0);

// PutLogMessage_("KpStApp::StopHp11() thread: %d stabdom EmuTv.m_lKphp11ThreadId", EmuTv.m_lKphp11ThreadId);

      Sleep(KPST_STOP_PROCESS_POLLING_TIMER);

      if(EmuTv.m_lKphp11ThreadId == 0L) break;
   }

return(retc);
}
#endif


// -----------------------------------------
#if FALSE
HRESULT KpStApp::ReadIni(void)
{
HRESULT retc=S_OK;
FILE *ini_file=NULL;
int ii;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
int prol_show_time;
unsigned char prol_fname[KP_MAX_FNAME_LEN+1];
int bmp_wdt;
int bmp_hgt;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[TV_TAG_LEN + 1];
int pwd_ed_ctrl=0;
int pwd_ok_but=0;
unsigned char vol_name[KP_MAX_FNAME_LEN+1];
long ser_no=0L;

   if(SUCCEEDED(retc)) if(strlen(m_lpszIniFName)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ini_file=fopen((const char *)m_lpszIniFName, "r");
      if(ini_file==NULL)
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fgets((char *)cmd_str, KP_MAX_FILE_LIN_WDT, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         cmd_str[0]=Nul;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         cmd_str[KP_MAX_FILE_LIN_WDT]=Nul;
         ii=strlen(cmd_str);
         if(ii>0) if(cmd_str[ii-1]=='\n') cmd_str[ii-1]=Nul;
      }
   }

   if(SUCCEEDED(retc))
   {
      fscanf(ini_file, "%d\n", &prol_show_time);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         prol_show_time=0;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fgets((char *)prol_fname, KP_MAX_FNAME_LEN, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         prol_fname[0]=Nul;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         prol_fname[KP_MAX_FNAME_LEN]=Nul;
         ii=strlen(prol_fname);
         if(ii>0) if(prol_fname[ii-1]=='\n') prol_fname[ii-1]=Nul;
      }
   }

   if(SUCCEEDED(retc))
   {
      fscanf(ini_file, "%d %d\n", &bmp_wdt, &bmp_hgt);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         bmp_wdt=0;
         bmp_hgt=0;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fgets((char *)pwd_win_name, KP_MAX_FNAME_LEN, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         pwd_win_name[0]=Nul;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         pwd_win_name[KP_MAX_FNAME_LEN]=Nul;
         ii=strlen(pwd_win_name);
         if(ii>0) if(pwd_win_name[ii-1]=='\n') pwd_win_name[ii-1]=Nul;
      }
   }

   if(SUCCEEDED(retc))
   {
      fgets((char *)pwd_buf, TV_TAG_LEN, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         pwd_buf[0]=Nul;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         pwd_buf[TV_TAG_LEN]=Nul;
         ii=strlen(pwd_buf);
         if(ii>0) if(pwd_buf[ii-1]=='\n') pwd_buf[ii-1]=Nul;
      }
   }

   if(SUCCEEDED(retc))
   {
      fscanf(ini_file, "%d %d\n", &pwd_ed_ctrl, &pwd_ok_but);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         pwd_ed_ctrl=0;
         pwd_ok_but=0;
         if(ferror(ini_file))
         {
            retv=GetLastError();
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         }
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fgets((char *)vol_name, KP_MAX_FNAME_LEN, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         vol_name[0]=Nul;
         if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         if(feof(ini_file) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
      else
      {
         vol_name[KP_MAX_FNAME_LEN]=Nul;
         ii=strlen(vol_name);
         if(ii>0) if(vol_name[ii-1]=='\n') vol_name[ii-1]=Nul;
      }
   }

   if(SUCCEEDED(retc))
   {
      fscanf(ini_file, "%d\n", &ser_no);
      if(ferror(ini_file) /* || feof(ini_file) */)
      {
         retv=GetLastError();
         ser_no=0;
//       if(ferror(ini_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
//       if(feof(ini_file) && SUCCEEDED(retc))
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }


   if(ini_file!=NULL) fclose(ini_file);
   ini_file=NULL;

   if(SUCCEEDED(retc)) retc=SetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) retc=SetIniProlShowTime(prol_show_time);
   if(SUCCEEDED(retc)) retc=SetIniProlFName(prol_fname);
   if(SUCCEEDED(retc)) retc=SetIniBitmapWdt(bmp_wdt);
   if(SUCCEEDED(retc)) retc=SetIniBitmapHgt(bmp_hgt);
   if(SUCCEEDED(retc)) retc=SetIniPwdWndName(pwd_win_name);
   if(SUCCEEDED(retc)) retc=SetIniPwd(pwd_buf);
   if(SUCCEEDED(retc)) retc=SetIniPwdEdCtrl(pwd_ed_ctrl);
   if(SUCCEEDED(retc)) retc=SetIniPwdOkBut(pwd_ok_but);
   if(SUCCEEDED(retc)) retc=SetIniVolName(vol_name);
   if(SUCCEEDED(retc)) retc=SetIniSerNo(ser_no);

return(retc);
}
#endif


#if FALSE
// -----------------------------------------
HRESULT KpStApp::WriteIni(void)
{
HRESULT retc=S_OK;
FILE *ini_file=NULL;
int retv;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
int prol_show_time;
unsigned char prol_fname[KP_MAX_FNAME_LEN+1];
int bmp_wdt;
int bmp_hgt;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[TV_TAG_LEN+1];
int pwd_ed_ctrl=0;
int pwd_ok_but=0;
unsigned char vol_name[KP_MAX_FNAME_LEN+1];
long ser_no=0L;

   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) retc=GetIniProlShowTime(&prol_show_time);
   if(SUCCEEDED(retc)) retc=GetIniProlFName(prol_fname);
   if(SUCCEEDED(retc)) retc=GetIniBitmapWdt(&bmp_wdt);
   if(SUCCEEDED(retc)) retc=GetIniBitmapHgt(&bmp_hgt);
   if(SUCCEEDED(retc)) retc=GetIniPwdWndName(pwd_win_name);
   if(SUCCEEDED(retc)) retc=GetIniPwd(pwd_buf);
   if(SUCCEEDED(retc)) retc=GetIniPwdEdCtrl(&pwd_ed_ctrl);
   if(SUCCEEDED(retc)) retc=GetIniPwdOkBut(&pwd_ok_but);
   if(SUCCEEDED(retc)) retc=GetIniVolName(vol_name);
   if(SUCCEEDED(retc)) retc=GetIniSerNo(&ser_no);

   if(SUCCEEDED(retc)) if(strlen(m_lpszIniFName)==0)
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      ini_file=fopen((const char *)m_lpszIniFName, "w");
      if(ini_file==NULL)
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fputs((const char *)cmd_str, ini_file);
      fputc(Lf, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fprintf(ini_file, "%d\n", prol_show_time);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fputs((const char *)prol_fname, ini_file);
      fputc(Lf, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fprintf(ini_file, "%d %d\n", bmp_wdt, bmp_hgt);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fputs((const char *)pwd_win_name, ini_file);
      fputc(Lf, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fputs((const char *)pwd_buf, ini_file);
      fputc(Lf, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fprintf(ini_file, "%d %d\n", pwd_ed_ctrl, pwd_ok_but);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fputs((const char *)vol_name, ini_file);
      fputc(Lf, ini_file);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(SUCCEEDED(retc))
   {
      fprintf(ini_file, "%d\n", ser_no);
      if(ferror(ini_file) || feof(ini_file))
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      }
   }

   if(ini_file!=NULL)
   {
      if(fclose(ini_file)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
         if(ferror(ini_file) || feof(ini_file))
         {
            retv=GetLastError();
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, m_lpszIniFName, True, __FILE__, __LINE__, 0L);
         }
   }
   ini_file=NULL;

return(retc);
}
#endif


// -----------------------------------------
HRESULT KpStApp::LoadIni(void)
{
HRESULT retc=S_OK;

   retc=LoadIniFile(m_lpszIniFName, False);
   if(retc==KP_E_DIR_ERROR)
      retc=KpErrorProc.OutputErrorMessage(retc, m_lpszIniFName, True, __FILE__, __LINE__, 0L);

return(retc);
}

HRESULT KpStApp::LoadIniFile(const unsigned char *lpszIniFileName, bool bForceExternal, bool bOutputErrorMessages)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
#ifdef KPST_WINDOWS_INTERFACE
HANDLE ini_file=INVALID_HANDLE_VALUE;
#else
FILE *ini_file=NULL;
#endif
DWORD file_len = sizeof(KpStIniData);
int retv;
KpStIniData *ini_ptr=NULL;
bool load_external=True;

   m_bSaveTestUpdatesToIni = False;

   if(SUCCEEDED(retc)) if(lpszIniFileName==NULL)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc)) if(strlen(lpszIniFileName)==0)
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(((theKpStAppPtr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_MOVE_TO_KPHP11
      ini_ptr=&IniDataBuf;
#else
      ini_ptr=&m_Ini;
#endif

      if((InternalIniData[0] || InternalIniData[1] || InternalIniData[2] || InternalIniData[3]) && (!bForceExternal)) load_external=False;

      if(load_external)
      {
#ifdef KPST_WINDOWS_INTERFACE
         ini_file = CreateFile((const char *)lpszIniFileName, GENERIC_READ, FILE_SHARE_READ,
            0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
         if(ini_file == INVALID_HANDLE_VALUE)
#else
         ini_file = fopen((const char *)lpszIniFileName, "rb");
         if(ini_file == NULL)
#endif
         {
            retv = GetLastError();
            retc = KP_E_FILE_NOT_FOUND;
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      if(!load_external)
      {
         memcpy(ini_ptr, InternalIniData, sizeof(KpStIniData));
      }
      else
      {
         memset(ini_ptr, 0, sizeof(KpStIniData));

#ifdef KPST_MOVE_TO_KPHP11
//       if(SUCCEEDED(retc))
         {
            retc0 = EnctBuf(&IniDataBuf, (sizeof(KpStIniData)/4)*4, True);
            if(SUCCEEDED(retc)) retc=retc0;
         }
#else
//       if(SUCCEEDED(retc))
         {
            retc0 = EnctIniData(sizeof(KpStIniData), True);
            if(SUCCEEDED(retc)) retc = retc0;
         }
#endif

         if(SUCCEEDED(retc))
         {
#ifdef KPST_WINDOWS_INTERFACE
            if(!ReadFile(ini_file, ini_ptr, sizeof(KpStIniData), &file_len, NULL))
#else
            file_len=fread(ini_ptr, 1, sizeof(KpStIniData), ini_file);
            if(ferror(ini_file))
#endif
            {
               retv=GetLastError();
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszIniFileName, True, __FILE__, __LINE__, 0L);
            }
//          if(feof(ini_file))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, lpszIniFileName, True, __FILE__, __LINE__, 0L);
         }

      } // else // if(!load_external)

#ifdef KPST_WINDOWS_INTERFACE
      if(ini_file!=INVALID_HANDLE_VALUE) CloseHandle(ini_file);
      ini_file = INVALID_HANDLE_VALUE;
#else
      if(ini_file!=NULL) fclose(ini_file);
      ini_file = NULL;
#endif

#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
      if(SUCCEEDED(retc)) retc = SendIniToHp11(ini_ptr, True);
#endif

      if(SUCCEEDED(retc)) if((file_len > KPST_SIZEOF_INI_DATA_OLD) && (file_len < sizeof(KpStIniData)))
         ini_ptr->m_iCheckSum = *(int *)(((char *)ini_ptr) + file_len - sizeof(int)); // kad kodavimo seed nusistatytø á senà m_iCheckSum
               // kai file_len == KPST_SIZEOF_INI_DATA_OLD nereikia - koduojam nuo nulinio seed

#ifndef KPST_MOVE_TO_KPHP11
//    if(SUCCEEDED(retc))
      {
         retc0 = EnctIniData(file_len, True);
         if(SUCCEEDED(retc)) retc = retc0;
      }
#endif

   } // if(SUCCEEDED(retc))

   if(load_external && SUCCEEDED(retc))
   {
      retc = TestIniChSum(True);
      if((retc == KP_E_FILE_FORMAT) || (file_len != sizeof(KpStIniData)))
      {
//        KpErrorProc.OutputErrorMessage(retc, lpszIniFileName, True, __FILE__, __LINE__, 0L);
//        retc = S_OK;
          if(bOutputErrorMessages) retc = KpErrorProc.OutputErrorMessage(retc, lpszIniFileName, True, __FILE__, __LINE__, 0L);
          if((m_iKpStMode == KpStEditMode) /* || (!bOutputErrorMessages) */) retc = S_OK;
      }
      if(/* (file_len < 0) || */ (file_len > sizeof(KpStIniData)) && SUCCEEDED(retc))
          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, lpszIniFileName, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
         memset(((unsigned char *)ini_ptr) + file_len - sizeof(IniDataBuf.m_iCheckSum), Nul, sizeof(KpStIniData) - file_len + sizeof(IniDataBuf.m_iCheckSum));
      if(SUCCEEDED(retc)) if(file_len <= ((unsigned char *)&IniDataBuf.m_iIniLicID - (unsigned char *)&IniDataBuf) + sizeof(IniDataBuf.m_iCheckSum))
         ini_ptr->m_iIniLicID = KpstRand(0);
   }

return(retc);
}


// -----------------------------------------
HRESULT KpStApp::SaveIniFile(const unsigned char *lpszIniFileName)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
#ifdef KPST_WINDOWS_INTERFACE
DWORD written;
HANDLE ini_file=INVALID_HANDLE_VALUE;
#else
FILE *ini_file=NULL;
#endif
int retv;
KpStIniData *ini_ptr=NULL;

   KP_ASSERT(lpszIniFileName, E_INVALIDARG, null, True);
   KP_ASSERT(theKpStAppPtr, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc)) retc = SetIniChSum();

#ifdef KPST_MOVE_TO_KPHP11
   ini_ptr=&IniDataBuf;

   if(SUCCEEDED(retc)) retc=GetIniFromHp11(ini_ptr);
#else
   ini_ptr=&m_Ini;

   if(SUCCEEDED(retc0))
   {
      retc0=theKpStAppPtr->EnctIniData(sizeof(KpStIniData));
      if(SUCCEEDED(retc)) retc=retc0;
   }
#endif

   KP_ASSERT((strlen(lpszIniFileName)!=0), KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
#ifdef KPST_WINDOWS_INTERFACE
      ini_file = CreateFile((const char *)lpszIniFileName, GENERIC_WRITE, FILE_SHARE_WRITE,
         0, CREATE_ALWAYS /* OPEN_ALWAYS */, FILE_ATTRIBUTE_NORMAL, 0);
      if(ini_file == INVALID_HANDLE_VALUE)
      {
         ini_file = CreateFile((const char *)lpszIniFileName, GENERIC_WRITE, FILE_SHARE_WRITE,
            0, CREATE_ALWAYS /* OPEN_ALWAYS */, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_HIDDEN, 0);
         if(ini_file == INVALID_HANDLE_VALUE)
#else
      ini_file=fopen((const char *)lpszIniFileName, "wb");
      if(ini_file == NULL)
      {
#endif
         {
            retv = GetLastError();
            KP_WARNING(KP_E_DIR_ERROR, retv);
            KP_ERROR(KP_E_DIR_ERROR, lpszIniFileName);
         }
      }
   }

   if(SUCCEEDED(retc))
   {
#ifdef KPST_WINDOWS_INTERFACE
      if(!WriteFile(ini_file, ini_ptr, sizeof(KpStIniData), &written, NULL))
#else
      fwrite(ini_ptr, 1, sizeof(KpStIniData), ini_file);
      if(ferror(ini_file) || feof(ini_file))
#endif
      {
         retv=GetLastError();
         retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszIniFileName, True, __FILE__, __LINE__, 0L);
      }
   }

#ifdef KPST_WINDOWS_INTERFACE
   if(ini_file!=INVALID_HANDLE_VALUE)
   {
      if(!CloseHandle(ini_file))
#else
   if(ini_file!=NULL)
   {
      if(fclose(ini_file)!=0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, lpszIniFileName, True, __FILE__, __LINE__, 0L);
      if(SUCCEEDED(retc))
         if(ferror(ini_file) || feof(ini_file))
#endif
         {
            retv=GetLastError();
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, lpszIniFileName, True, __FILE__, __LINE__, retv);
         }
   }
#ifdef KPST_WINDOWS_INTERFACE
   ini_file = INVALID_HANDLE_VALUE;
#else
   ini_file=NULL;
#endif

#ifndef KPST_MOVE_TO_KPHP11
   if(SUCCEEDED(retc0))
   {
      retc0=theKpStAppPtr->EnctIniData(sizeof(KpStIniData));
      if(SUCCEEDED(retc)) retc=retc0;
   }
#endif

return(retc);
}


HRESULT KpStApp::SaveIni(void)
{
return(SaveIniFile(m_lpszIniFName));
}


// -------------------------------------------
#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::SendIniToHp11(KpStIniData *pBuffer, bool bCheckErrors)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
int ii;

   if((pBuffer==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   ii=sizeof(KpStIniData);
   if((ii>=HP11_RC_INI_BUF_MAX_LEN) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_REC_INI;
      rc_pars.iParBlSize = sizeof(KpRcPars);
      rc_pars.enc.iDataLen = (sizeof(KpStIniData)/4)*4;
      rc_pars.enc.pData = pBuffer;

// #ifdef Debug
// unsigned char str_buf[100];
// sprintf((char *)str_buf, "%d", sizeof(KpStIniData));
// KP_TRACE(str_buf);

// while(SUCCEEDED(retc)) retc=KpSleep(1000, HWND_DESKTOP);
// retc=S_OK;
// #endif

// PutLogMessage_("KpStApp::SITH ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("SITH() .... %x %x", &rc_pars, pBuffer);
#endif

      retc = EmuTv.ExecRemoteCall(&rc_pars, bCheckErrors);

#if FALSE // #ifdef Debug
while(SUCCEEDED(retc)) retc=KpSleep(1000, HWND_DESKTOP);

static unsigned char str_buf[4000];
int ii;
GetIniCmdStr(str_buf); KP_TRACE(str_buf);
GetIniProdVer(&ii); sprintf((char *)str_buf, "%d", ii); KP_TRACE(str_buf);
GetIniProdName(str_buf); KP_TRACE(str_buf);
GetIniPublisher(str_buf); KP_TRACE(str_buf);
GetIniRegURL(str_buf); KP_TRACE(str_buf);

retc=S_OK;
while(SUCCEEDED(retc)) retc=KpSleep(1000, HWND_DESKTOP);
#endif
   }

return(retc);
}
#endif


#if TRUE // #ifdef KPST_MOVE_TO_KPHP11
HRESULT KpStApp::GetIniFromHp11(KpStIniData *pBuffer)
{
HRESULT retc=S_OK;
static KpRcPars rc_pars;

   if((pBuffer==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_SEND_INI;
      rc_pars.iParBlSize = sizeof(KpRcPars);
      rc_pars.enc.iDataLen = (sizeof(KpStIniData)/4)*4;
      rc_pars.enc.pData = pBuffer;

// PutLogMessage_("KpStApp::GIFH ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("GIFH() ....>>>> %x %x", &rc_pars, pBuffer);
#endif

      retc=EmuTv.ExecRemoteCall(&rc_pars);
   }

return(retc);
}
#endif


// -------------------------------------------
HRESULT KpStApp::TestCD(void)
{
HRESULT retc=S_OK;
unsigned char drv_buf[KP_MAX_FILE_LIN_WDT+2];
unsigned char *pntd;
unsigned char file_system[KP_MAX_FNAME_LEN+1];
DWORD max_fname_len;
DWORD sys_flags;
bool ch_cd=False;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
unsigned char vol_name[KP_MAX_FNAME_LEN+1];
unsigned char vol_name_chk[KP_MAX_FNAME_LEN+1];
long ser_no=0L;
DWORD ser_no_chk;

   if(SUCCEEDED(retc)) retc=GetIniCheckCD(&ch_cd);
   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) retc=GetIniVolName(vol_name);
   if(SUCCEEDED(retc)) retc=GetIniSerNo(&ser_no);

   if(ch_cd && SUCCEEDED(retc))
   {
      strcpy(drv_buf, cmd_str);
      pntd=strchr(drv_buf, ':');
      if(pntd!=NULL)
      {
         pntd++;
         (*pntd++)='\\';
         (*pntd++)=Nul;
         pntd=drv_buf;
      }

      if(DRIVE_CDROM!=GetDriveType((const char *)pntd))
      {
      /* retc= */ KpMsgOut(KPST_MSG_START_FROM_CD, IDI_ERROR, KP_MB_TESTI);
         retc=KP_E_SYSTEM_ERROR;
      }

// -------------------------
//    if(SUCCEEDED(retc)) retc=KpSleep(500, HWND_DESKTOP); // Sleep(500);

      if(SUCCEEDED(retc))
      {
         if((strlen(vol_name)>0) || (ser_no!=0L))
         {
            if(!GetVolumeInformation((const char *)pntd, (char *)vol_name_chk, KP_MAX_FNAME_LEN, &ser_no_chk,
               &max_fname_len, &sys_flags, (char *)file_system, KP_MAX_FNAME_LEN))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #ifdef Debug //
{
char str_buf[1000];
if(SUCCEEDED(retc))
{
sprintf(str_buf, "%s %lx/%ld %ld %lx %s", vol_name_chk, ser_no_chk, ser_no_chk, max_fname_len, sys_flags, file_system);
KP_TRACE(str_buf);
}
}
#endif

            if(SUCCEEDED(retc))
            {
               strlwr((char *)vol_name_chk);
               strlwr((char *)vol_name);

               if(
                  ((strlen(vol_name)>0) && (strcmp(vol_name, vol_name_chk)!=0)) ||
                  ((ser_no!=0L) && (ser_no!=(long)ser_no_chk)) // ||
//                (strcmp(file_system, "CDFS")!=0)
               )
               {
               /* retc= */ KpMsgOut(KPST_MSG_BAD_CD, IDI_ERROR, KP_MB_BAIGTI);
                  retc=KP_E_SYSTEM_ERROR;
               }
            }
         }
      }
   }

return(retc);
}


// ------------------------------------------------------------
HRESULT KpStApp::WaitForWindow(
const unsigned char *lpszWndName,
const unsigned char *lpszPwdText,
int iOkBut, int iPwdEditCtrl,
HANDLE hCmdProcess,
HANDLE hCmdThread,
DWORD /* lCmdThread */,
HWND hBitmapWindow
)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
MSG msg;
HWND dlg_wnd=NULL;
HWND edit_wnd=NULL;
HWND button_wnd=NULL;
// unsigned char str_buf[KP_MAX_FNAME_LEN+1];
int msg_fl=False;
// bool timer_killed=False;
UINT poll_timer_id=0;
bool endfl=False;
// WINDOWPLACEMENT wnd_pl;
// HDC dc;
int wnd_x;
int wnd_y;
DWORD exit_code;
int ii;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[TV_TAG_LEN + 1];
unsigned char pwd_win_name_ini[KP_MAX_FNAME_LEN+1];
int pwd_ok_but=0;
int pwd_ed_ctrl=0;
int prog_inc_sav = 0;
int retp;
// unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);
   if(SUCCEEDED(retc)) retc = GetIniPwdWndName(pwd_win_name_ini);

   pwd_win_name[0]=Nul;
   if((lpszWndName!=NULL) && SUCCEEDED(retc))
   {
      if(strlen(lpszWndName)>=KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) strcpy(pwd_win_name, lpszWndName);
   }
   if(SUCCEEDED(retc)) retc=CutInitTrailSpcs(pwd_win_name);

   pwd_buf[0]=Nul;
   if((lpszPwdText!=NULL) && SUCCEEDED(retc))
   {
      if(strlen(lpszPwdText)>=TV_TAG_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) strcpy(pwd_buf, lpszPwdText);
   }

   pwd_ok_but=iOkBut;
   pwd_ed_ctrl=iPwdEditCtrl;

   if(SUCCEEDED(retc)) if((strlen(pwd_win_name)>0) /* && (hCmdProcess || hCmdThread || lCmdThread) */)
   {
      if(
//       (hBitmapWindow!=NULL) &&
         SUCCEEDED(retc)
      )
      {
         poll_timer_id = SetTimer(HWND_DESKTOP /* hBitmapWindow */, KP_POLL_TIMER, KP_POLL_TIMEOUT, NULL);
         if(!poll_timer_id)
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc)) do
      {
         msg_fl = False;

//       if(hBitmapWindow!=NULL)
//       {
            if(GetMessage(&msg, NULL, 0, 0)<0)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            else msg_fl=True;
//       }
//       else
//          msg_fl=PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

         if(msg_fl && SUCCEEDED(retc))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            retp = LOWORD(msg.wParam);
         }

         if(msg_fl && SUCCEEDED(retc)) switch(msg.message)
         {
         case WM_CHAR:
            switch(retp)
            {
            case KP_HP11_TOGGLE_CONSOLE:
               if(lKphp11ThreadId!=0L)
                  if(!::PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               break;
            }
            break;

         case WM_TIMER:
//          if(retp == KP_POLL_TIMER)
            if(retp == poll_timer_id)
            {
KP_TRACE("WaitForWindow(): WM_TIMER: poll_timer_id");
// ---------------------------
//             if(SUCCEEDED(retc)) retc = CloseLaunchPrompt();
               if(SUCCEEDED(retc)) retc = CloseAutoPlay();
               if(SUCCEEDED(retc)) retc = CloseCompatibilityAssistant();

// check if window is allready open
               dlg_wnd = GetWindowByName(pwd_win_name, False); // True); - kartais reikia sulaukti ir dalinio lango vardo - pprc,
               if(dlg_wnd!=NULL)                                    // nes galutinis multidocument langas kaþkodël bûna minimizuotas
               {
//                if((strlen(pwd_buf) == 0) /* || (pwd_ed_ctrl == 0) || (pwd_ok_but == 0) */) endfl = True;
//                else
                  {
                     if(pwd_ed_ctrl == 0) edit_wnd = dlg_wnd;
                     else edit_wnd = GetChildWindow(dlg_wnd, pwd_ed_ctrl);
                     if(edit_wnd != NULL)
                     {
                        if(pwd_ok_but == 0) button_wnd = dlg_wnd;
                        else button_wnd = GetChildWindow(dlg_wnd, pwd_ok_but);
                        if(button_wnd != NULL)
                        {
// tikrinam, ar tikrai slaptazodzio langas
#if FALSE // #ifdef Debug
                           str_buf[0] = Nul;
                           if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))
                              retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
#endif
                           if(SUCCEEDED(retc))
                           {
#if FALSE // #ifdef Debug
                              if((strcmp(str_buf, "OK") != 0) && (button_wnd != dlg_wnd))
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);
                              else
#endif
                              {
// ------------------------
                                 if(strlen(pwd_buf) > 0)
                                 {



//                                  if(SUCCEEDED(retc) /* && (hBitmapWindow!=NULL) */)
//                                  {
//                                     timer_killed=True;
//                                     if(!KillTimer(HWND_DESKTOP /* hBitmapWindow */, retp))
//                                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//                                  }

// ---------------------- hide password window
#if FALSE
                                    if(SUCCEEDED(retc))
                                    {
                                       wnd_pl.length=sizeof(WINDOWPLACEMENT);
                                       ...
                                    }

                                    if(SUCCEEDED(retc))
                                       if(!SetWindowPlacement(dlg_wnd, &wnd_pl))
                                          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
#if FALSE
                                    if(SUCCEEDED(retc))
                                    {
                                       dc=GetDC(HWND_DESKTOP);
                                       if(dc==NULL)
                                          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                                    }
#endif

// move to kpsta.ini ???
#define KPSPWD_WND_WDT 350
#define KPSPWD_WND_HGT 120
#define KPSPWD_WND_X 300
#define KPSPWD_WND_Y 300

                                    if(SUCCEEDED(retc))
                                    {
//                                     wnd_x=(GetDeviceCaps(dc, HORZRES)-KPSPWD_WND_WDT)/2;
//                                     wnd_y=(GetDeviceCaps(dc, VERTRES)-KPSPWD_WND_HGT)/2;
                                       wnd_x=KPSPWD_WND_X;
                                       wnd_y=KPSPWD_WND_Y;
                                    }
#ifdef KPST_BITMAP_TO_TOP
if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) retc = KpSleep(400, HWND_DESKTOP); // Sleep(400); // 100 // 1000 // 100
// dar kartà - lëtiems kompams?
#ifdef KPST_BITMAP_TO_TOP
if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif

// #ifdef Debug
// sprintf((char *)str_buf, "%x", hBitmapWindow); KpMsgOut(str_buf, KP_MB_TESTI);
// #endif


// ----------------------
                                    if(SUCCEEDED(retc)) retc = KpSleep(200, HWND_DESKTOP); // Sleep(200); // 100 // 1000 // 100
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) SendMessage(edit_wnd, EM_SETPASSWORDCHAR, Spc, 0); // ' '
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) retc = KpSleep(100, HWND_DESKTOP); // Sleep(100); //
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
//                                  if(SUCCEEDED(retc)) retc=SendStringToWindow(edit_wnd, (const unsigned char *)"\0x1"); // Ctrl+A

//                                  if(SUCCEEDED(retc)){ PostMessage(edit_wnd, WM_KEYDOWN, Ctrl, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
//                                  if(SUCCEEDED(retc)){ PostMessage(edit_wnd, WM_KEYDOWN, 'A', 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
//                                  if(SUCCEEDED(retc)){ PostMessage(edit_wnd, WM_KEYUP, 'A', 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
//                                  if(SUCCEEDED(retc)){ PostMessage(edit_wnd, WM_KEYUP, Ctrl, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //

                                    if(SUCCEEDED(retc)){ PostMessage(edit_wnd, EM_SETSEL, 0, -1); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
//                                  if(SUCCEEDED(retc)){ PostMessage(edit_wnd, WM_CLEAR, 0, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //

                                    if(SUCCEEDED(retc))
                                    {
                                       ii=strlen(pwd_buf);
                                       if(ii>0)
                                       {
//                                        retc=SendStringToWindow(edit_wnd, pwd_buf+ii-1);
// apsauga nuo hookdump - pirma pask. raide, poto Home, poto likusios
                                          PostMessage(edit_wnd, WM_CHAR, pwd_buf[ii-1], 0);
                                          pwd_buf[ii-1]=Nul;
                                          retc = KpSleep(50, HWND_DESKTOP); // Sleep(50); //
                                       }
                                    }
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc))
                                    {
                                       PostMessage(edit_wnd, WM_KEYDOWN, Hom, 0);
                                       retc = KpSleep(50, HWND_DESKTOP); // Sleep(50); //
                                    }

#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) retc = SendStringToWindow(edit_wnd, pwd_buf,
                                          ((m_iKpStMode==KpStarterMode) && (pwd_ok_but!=0))?hBitmapWindow:NULL);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) retc = KpSleep(300, HWND_DESKTOP); // Sleep(300); // 200 // 1000 // 100

// restore password window
//                                  if(SUCCEEDED(retc))
//                                     if(!SetWindowPos(dlg_wnd, HWND_TOPMOST /* hBitmapWindow */, wnd_x, wnd_y, KPSPWD_WND_WDT, KPSPWD_WND_HGT, SWP_SHOWWINDOW /* | SWP_NOMOVE|SWP_NOSIZE */))
//                                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
//                                  if(SUCCEEDED(retc))
//                                     if(!SetActiveWindow(dlg_wnd))
//                                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
//                                  if(SUCCEEDED(retc))
//                                     if(!SetForegroundWindow(dlg_wnd))
//                                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);

                                 } // if(strlen(pwd_buf)>0)
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                 if((button_wnd != dlg_wnd) && SUCCEEDED(retc))
                                 {
                                    if(SUCCEEDED(retc)) SendMessage(button_wnd, WM_ACTIVATE , WA_CLICKACTIVE, 0);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) retc = KpSleep(200, HWND_DESKTOP); // Sleep(200); // 40 // 200 // 20
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) SendMessage(button_wnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) retc = KpSleep(200, HWND_DESKTOP); // Sleep(200); // 40 // 200 // 20
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(hBitmapWindow, dlg_wnd);
#endif
                                    if(SUCCEEDED(retc)) SendMessage(button_wnd, WM_LBUTTONUP, 0, 0);
                                 }

                                 endfl=True;

                              } // else // if(SUCCEEDED(retc) && (strcmp(str_buf, "OK") != 0))

                           } // if(SUCCEEDED(retc))

                        } // if(button_wnd!=NULL)

                     } // if(edit_wnd!=NULL)

                  } // else if((pwd_ed_ctrl==0) || (pwd_ok_but==0))

               } // if(dlg_wnd!=NULL)

// check whether main process is still running

               if((hCmdProcess || hCmdThread /* || lCmdThread */) && SUCCEEDED(retc))
               {
                  if(hCmdProcess)
                  {
                     if(!GetExitCodeProcess(hCmdProcess, &exit_code))
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
                  else // if(hCmdThread)
                  {
                     if(!GetExitCodeThread(hCmdThread, &exit_code))
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
//                else exit_code = (~STILL_ACTIVE);

                  if((exit_code!=STILL_ACTIVE) && SUCCEEDED(retc)) endfl=True;

//                if(FAILED(retc) /* && (hBitmapWindow != NULL) */)
//                if(!KillTimer(HWND_DESKTOP /* hBitmapWindow */, retp))
//                {
//                   retc0 = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
//                   if(SUCCEEDED(retc)) retc = retc0;
//                }
               }

// pristabdyti sliderá kol yra slaptaþodþio langas (Bebras, Arkim)
               if(!endfl && (strcmp(pwd_win_name_ini, "Password") != 0) && SUCCEEDED(retc))
               {
                  if(GetWindowByName((const unsigned char *)"Password", True))
                  {
                     if(prog_inc_sav == 0) retc = StopSlider(&prog_inc_sav);
                  }
                  else
                  {
                     if(prog_inc_sav) retc = ReleaseSlider(prog_inc_sav);
                     prog_inc_sav = 0;
                  }
               }
            }
            break;

// ----------------------------
         case WM_COMMAND:
PutLogMessage_("WaitForWindow() WM_COMMAND: %d %ld", retp, msg.lParam);
            switch(retp)
            {
            case KP_ID_MUTE:
               if(SUCCEEDED(retc)) retc = SwitchMute();
               break;
#if FALSE
// jei nepagaunam èia – apdorojimas yra ir KpStaWindowProc()
            case KPST_ID_REST_DAYS_EXCEEDED:
               if(msg.lParam <= KPST_REST_DAYS_WARNING)
               {
                  if(msg.lParam <= 0)
                  {
static unsigned char str_buf[2000];
                     sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
                     KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
                     KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                     endfl = True;
                     retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
                  }
                  else
                  {
                     if(!RestDaysWarningShowed())
                     {
                        switch(msg.lParam)
                        {
                        case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
                        case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
                        default: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, msg.lParam); break;
                        }
                     }
//                   m_iRestDaysWarningShowed = True;
                     KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                  }
               }
               break;
#endif
            case IDCANCEL:
               endfl = True;
               retc = KP_E_CANCEL;
               break;
            }
            break;

         case WM_QUIT:
            switch(retp)
            {
            case IDCANCEL: retc = KP_E_CANCEL; break;
            case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
            }
            endfl=True;
            break;

         default:
            break;
         }

//       if(endfl && (!timer_killed) /* && (hBitmapWindow==NULL) */ && SUCCEEDED(retc))
//       {
//          if(!PostMessage(NULL, WM_TIMER, KP_POLL_TIMER, 0L))
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

//          if(SUCCEEDED(retc)) retc = KpSleep(KP_POLL_TIMEOUT, HWND_DESKTOP); // Sleep(KP_POLL_TIMEOUT); //
//       }

      } while((!endfl) && SUCCEEDED(retc));

      if(poll_timer_id)
      {
         if(!KillTimer(HWND_DESKTOP /* hBitmapWindow */, poll_timer_id))
         {
            retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc)) retc=retc0;
         }
         poll_timer_id=0;
      }
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::WaitForPwd(void)
{
HRESULT retc=S_OK;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[TV_TAG_LEN + 1];
int pwd_ok_but=0;
int pwd_ed_ctrl=0;

   if(SUCCEEDED(retc)) retc = GetIniPwdWndName(pwd_win_name);

// if(SUCCEEDED(retc)) retc = GetIniPwd(pwd_buf);
   if(SUCCEEDED(retc)) retc = GetIniPwdRC(pwd_buf);

   if(SUCCEEDED(retc)) retc = GetIniPwdOkBut(&pwd_ok_but);
   if(SUCCEEDED(retc)) retc = GetIniPwdEdCtrl(&pwd_ed_ctrl);

   if(SUCCEEDED(retc)) retc = WaitForWindow(pwd_win_name, pwd_buf, pwd_ok_but, pwd_ed_ctrl, m_hCmdProcess, m_hCmdThread, m_lCmdThread, m_hBitmapWindow);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::WaitForPwdCloses()
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
MSG msg;
HWND dlg_wnd = NULL;
HWND edit_wnd = NULL;
HWND button_wnd = NULL;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
int msg_fl = False;
UINT poll_timer_id = 0;
bool endfl = False;
DWORD exit_code;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[TV_TAG_LEN + 1];
int pwd_ok_but = 0;
int pwd_ed_ctrl = 0;
int ii;
// int prog_inc_sav = 1;
int retp;
// unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// if(SUCCEEDED(retc)) retc = StopSlider(&prog_inc_sav);

// if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

   if(SUCCEEDED(retc)) retc = GetIniPwdWndName(pwd_win_name);

// if(SUCCEEDED(retc)) retc = GetIniPwd(pwd_buf);
   if(SUCCEEDED(retc)) retc = GetIniPwdRC(pwd_buf);

   if(SUCCEEDED(retc)) retc = GetIniPwdOkBut(&pwd_ok_but);
   if(SUCCEEDED(retc)) retc = GetIniPwdEdCtrl(&pwd_ed_ctrl);

   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(pwd_win_name);

// laukti tik tikro Password lango, Flasho laukt nereikia - vis tiek neuzsidarys
   if(SUCCEEDED(retc))
      if((strlen(pwd_win_name)>0) && (m_hCmdProcess || m_hCmdThread || m_lCmdThread) &&
         (strlen(pwd_buf)>0) && (pwd_ed_ctrl!=0) && (pwd_ok_but!=0))
   {
      poll_timer_id = SetTimer(HWND_DESKTOP /* m_hBitmapWindow */, KP_POLL_TIMER, KP_POLL_TIMEOUT, NULL);
      if(!poll_timer_id)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) do
      {
         if(GetMessage(&msg, NULL, 0, 0)<0)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         else msg_fl=True;

         if(msg_fl && SUCCEEDED(retc))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            retp = LOWORD(msg.wParam);
         }

         if(msg_fl && SUCCEEDED(retc)) switch(msg.message)
         {
         case WM_CHAR:
            switch(retp)
            {
            case KP_HP11_TOGGLE_CONSOLE:
               if(lKphp11ThreadId!=0L)
                  if(!::PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               break;
            }
            break;

         case WM_TIMER:
            if(retp == poll_timer_id)
            {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: poll_timer_id");
// check if window is still open
               dlg_wnd = GetWindowByName(pwd_win_name, True);
               if(dlg_wnd == NULL)
               {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: dlg_wnd == NULL");
                  endfl = True;
               }
               else
               {
                  if(pwd_ed_ctrl == 0) edit_wnd = dlg_wnd;
                  else edit_wnd = GetChildWindow(dlg_wnd, pwd_ed_ctrl);
                  if(edit_wnd == NULL)
                  {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: edit_wnd == NULL");
                     endfl = True;
                  }
                  else
                  {
                     if(pwd_ok_but == 0) button_wnd = dlg_wnd;
                     else button_wnd = GetChildWindow(dlg_wnd, pwd_ok_but);
                     if(button_wnd == NULL)
                     {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: button_wnd == NULL");
                        endfl = True;
                     }
                     else
                     {
                        str_buf[0]=Nul;
                        if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))
                        {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: GetWindowText() == False");
                           retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                           endfl = True;
                        }
                        else
                        {
                           if((strcmp(str_buf, "OK") != 0) && (button_wnd != dlg_wnd))
                           {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: GetWindowText() != \"OK\"");
#ifdef Debug
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#endif
                              endfl=True;
                           }
                           else
                           {
KP_TRACE("WaitForPwdCloses(): WM_TIMER: KpBringToTop()");
#ifdef KPST_BITMAP_TO_TOP
if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc)) retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc)) PostMessage(edit_wnd, EM_SETSEL, 0, -1);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc)) retc=KpSleep(100, HWND_DESKTOP); // Sleep(100);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc))
                              {
                                 ii=strlen(pwd_buf);
                                 if(ii>0)
                                 {
//                                  retc=SendStringToWindow(edit_wnd, pwd_buf+ii-1);
// apsauga nuo hookdump - pirma pask. raide, poto Home, poto likusios
                                    PostMessage(edit_wnd, WM_CHAR, pwd_buf[ii-1], 0);
                                    pwd_buf[ii-1]=Nul;
                                    retc = KpSleep(50, HWND_DESKTOP); // Sleep(50);
                                 }
                              }
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc))
                              {
                                 PostMessage(edit_wnd, WM_KEYDOWN, Hom, 0);
                                 retc=KpSleep(50, HWND_DESKTOP); // Sleep(50);
                              }
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc))
                                 retc = SendStringToWindow(edit_wnd, pwd_buf,
                                          ((m_iKpStMode==KpStarterMode) && (pwd_ok_but!=0))?m_hBitmapWindow:NULL);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if(SUCCEEDED(retc)) retc=KpSleep(300, HWND_DESKTOP); // Sleep(300);
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                              if((button_wnd != dlg_wnd) && SUCCEEDED(retc))
                              {
                                 if(SUCCEEDED(retc))
                                 {
                                    SendMessage(button_wnd, WM_ACTIVATE , WA_CLICKACTIVE, 0);
                                    retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
                                 }
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                                 if(SUCCEEDED(retc))
                                 {
                                    SendMessage(button_wnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                                    retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
                                 }
#ifdef KPST_BITMAP_TO_TOP
// if((pwd_ok_but!=0) && SUCCEEDED(retc)) retc = KpBringToTop(m_hBitmapWindow, dlg_wnd);
#endif
                                 if(SUCCEEDED(retc)) SendMessage(button_wnd, WM_LBUTTONUP, 0, 0);
                              }

//                            endfl=True;

                           } // else // if(SUCCEEDED(retc) && (strcmp(str_buf, "OK") != 0))

                        } // else // if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))

                     } // if(button_wnd!=NULL)

                  } // if(edit_wnd!=NULL)

               } // if(dlg_wnd!=NULL)

// check whether main process is still running

               if(SUCCEEDED(retc))
               {
                  if(m_hCmdProcess)
                  {
                     if(!GetExitCodeProcess(m_hCmdProcess, &exit_code))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
                  else if(m_hCmdThread)
                  {
                     if(!GetExitCodeThread(m_hCmdThread, &exit_code))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }
                  else exit_code = (~STILL_ACTIVE);
               }
               if((exit_code!=STILL_ACTIVE) && SUCCEEDED(retc)) endfl=True;

            }
            break;

         case WM_COMMAND:
PutLogMessage_("WaitForPwdCloses() WM_COMMAND: %d %ld", retp, msg.lParam);
            switch(retp)
            {
#if FALSE
// jei nepagaunam èia – apdorojimas yra ir KpStaWindowProc()
            case KPST_ID_REST_DAYS_EXCEEDED:
               if(msg.lParam <= KPST_REST_DAYS_WARNING)
               {
                  if(msg.lParam <= 0)
                  {
static unsigned char str_buf[2000];
                     sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
                     KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
                     KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                     endfl = True;
                     retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
                  }
                  else
                  {
                     if(!RestDaysWarningShowed())
                     {
                        switch(msg.lParam)
                        {
                        case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
                        case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
                        default: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, msg.lParam); break;
                        }
                     }
//                   m_iRestDaysWarningShowed = True;
                     KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                  }
               }
               break;
#endif
            case IDCANCEL:
               endfl = True;
               retc = KP_E_CANCEL;
               break;
            }
            break;

         case WM_QUIT:
            switch(retp)
            {
            case IDCANCEL: retc = KP_E_CANCEL; break;
            case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
            }
            endfl=True;
            break;

         default:
            break;
         }

      } while((!endfl) && SUCCEEDED(retc));

      if(poll_timer_id)
      {
         if(!KillTimer(m_hBitmapWindow, poll_timer_id))
         {
//          KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
         poll_timer_id=0;
      }
   }

// if(SUCCEEDED(retc)) retc = ReleaseSlider(prog_inc_sav);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::MaximizeAcroWindowSingle(bool bForceMaximization /* bool bIfMinimizedOnly */)
{
HRESULT retc=S_OK;
HWND dlg_wnd;
int msg_fl=False;
UINT poll_timer_id=0;
WINDOWPLACEMENT wnd_pl;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];
bool on_top = False;
bool full_scr = False;
HWND pwd_wnd = 0;
HWND save_as_wnd = 0;
HDC dc = NULL;

   if(SUCCEEDED(retc)) retc=GetIniOnTop(&on_top);
   if(SUCCEEDED(retc)) retc=GetIniFullScr(&full_scr);

// KP_TRACE_1("MaximizeAcroWindowSingle(): %d", bForceMaximization);
#ifdef CHECK_MAXIMIZE
if(!bForceMaximization) KpMsgOut("jau 15 sec", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI, 300);
#endif

   if((on_top /* || full_scr */ || bForceMaximization) && SUCCEEDED(retc))
   {

// if(((!full_scr) || on_top) && SUCCEEDED(retc))
      {
         if(SUCCEEDED(retc)) pwd_wnd = GetWindowByName((const unsigned char *)"Password", True);
         if(SUCCEEDED(retc)) save_as_wnd = GetWindowByName((const unsigned char *)"Save As", True);
         if(SUCCEEDED(retc)) if(!save_as_wnd)
            save_as_wnd = GetWindowByName((const unsigned char *)"_raðyti kaip", True);

#ifdef CHECK_MAXIMIZE
if(pwd_wnd || save_as_wnd) KpMsgOut("pwd", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI, 300);
#endif
         if((!pwd_wnd) && (!save_as_wnd) && SUCCEEDED(retc))
         {
            dlg_wnd = NULL;
            
            do
            {
               dlg_wnd = GetWindowByName(KPST_ACROREAD_WINDOW_NAME, False, dlg_wnd);
               
               if(SUCCEEDED(retc))
               {
                  if (dlg_wnd)
                  {
                     if (GetWindowText(dlg_wnd, (char *)str_buf, KP_MAX_FNAME_LEN) > 0)
                     {
PutLogMessage_("MaximizeAcroWindowSingle 4 %s %x", KPST_ACROREAD_WINDOW_NAME, dlg_wnd);

// >>>>>> 2013-02-06  mp
// Nieko nedarom, jei Adobe Readerio langas be dokumento pavadinimo – Readeris dar uþsiëmæs,
// á maximizavimà nereaguoja, turi bûti „Adobe Reader - [Dokumento vardas]“
#if FALSE // #ifndef KPST_MULTI_DOCS
// Daugiadokumenèio projekto (Uþdaviniø konstruktoriaus) langas vadinasi bûtent „Adobe Reader“,
// be dokumento vardo
                        if(strcmp(str_buf, KPST_ACROREAD_WINDOW_NAME) == 0) dlg_wnd = NULL;
#endif
// <<<<<< 2013-02-06  mp
                     }
                  }
                  else
                  {
// KP_TRACE("MaximizeAcroWindowSingle(): dlg_wnd == NULL");
                  }
               }

#ifdef CHECK_MAXIMIZE
if(!dlg_wnd) KpMsgOut("nematau lango", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI, 300);
#endif
               if (dlg_wnd && SUCCEEDED(retc))
               {
// --------------------- maksimizuojam

// KP_TRACE("MaximizeAcroWindowSingle() found");

// atsimenam pirmo lango pasirodymo laika
// negerai, sioks toks Acrobato langas jau atsiranda, dar neivedus slaptazodzio
// reikia laukti, kol uzsidarys "Password" langas - jau padaryta
//                if(!m_lStartTime) time(&m_lStartTime);

                  if (SUCCEEDED(retc))
                     wnd_pl.length = sizeof(WINDOWPLACEMENT);

                  if(SUCCEEDED(retc))
                     if (!GetWindowPlacement(dlg_wnd, &wnd_pl)) // klaida, jei langa jau spejo uzdaryt
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

#ifdef CHECK_MAXIMIZE
char str_buf[100];
sprintf(str_buf, "wnd_pl.showCmd: %d", wnd_pl.showCmd);
KpMsgOut((wnd_pl.showCmd == SW_SHOWMINIMIZED)?"wnd_pl.showCmd: SW_SHOWMINIMIZED":str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI, 300);
#endif
// KP_TRACE_2("MaximizeAcroWindowSingle(): wnd_pl.showCmd: %x  SW_SHOWMINIMIZED: %x", wnd_pl.showCmd, SW_SHOWMINIMIZED);
                  if(((wnd_pl.showCmd == SW_SHOWMINIMIZED) /* || (wnd_pl.showCmd == SW_SHOWNORMAL) */) && 
                     ((!on_top) /* bIfMinimizedOnly */ || full_scr) && 
                     SUCCEEDED(retc))
                  {
                     Sleep(KPST_ACRO_MAXIMIZE_INTERVAL);

                     if (!GetWindowPlacement(dlg_wnd, &wnd_pl)) // klaida, jei langa jau spejo uzdaryt
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

#ifdef CHECK_MAXIMIZE
sprintf(str_buf, "wnd_pl.showCmd: %d", wnd_pl.showCmd);
KpMsgOut((wnd_pl.showCmd == SW_SHOWMINIMIZED)?"wnd_pl.showCmd: SW_SHOWMINIMIZED":str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI, 300);
#endif
                  }

// KP_TRACE_2("MaximizeAcroWindowSingle() 2: wnd_pl.showCmd: %x  SW_SHOWMINIMIZED: %x", wnd_pl.showCmd, SW_SHOWMINIMIZED);
PutLogMessage_("MaximizeAcroWindowSingle 6 %d %d", wnd_pl.showCmd, SW_SHOWMINIMIZED);
                  if(((wnd_pl.showCmd == SW_SHOWMINIMIZED) /* || (wnd_pl.showCmd == SW_SHOWNORMAL) */ || 
                       on_top /* (!bIfMinimizedOnly) */) && SUCCEEDED(retc))
                  {
//                   wnd_pl.flags = WPF_RESTORETOMAXIMIZED;

                     wnd_pl.showCmd = (full_scr /* && (wnd_pl.showCmd!=SW_SHOWMINIMIZED) */ /* || (!on_top) */)?
                                    SW_SHOWNORMAL:
                                    SW_SHOWMAXIMIZED; // SW_MAXIMIZE
                     if(full_scr)
                     {
                        dc = GetDC(HWND_DESKTOP);
                        if(dc == NULL)
                           retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL, False);
                        else
                        {
                           wnd_pl.rcNormalPosition.left   = -iWndBorderWdt;
                           wnd_pl.rcNormalPosition.top    = -(iWndCaptionHgt + iWndBorderWdt*3/2);
                           wnd_pl.rcNormalPosition.right  = GetDeviceCaps(dc, HORZRES) + iWndBorderWdt*7/2;
                           wnd_pl.rcNormalPosition.bottom = GetDeviceCaps(dc, VERTRES) + iWndCaptionHgt + iWndBorderWdt*5/2;
                        }
                     }

// char str_buf[100];
// sprintf(str_buf, "%x", wnd_pl.showCmd);
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

//                   if(SUCCEEDED(retc)) retc = KpSleep(KPST_ACRO_MAXIMIZE_INTERVAL, HWND_DESKTOP); // Sleep(KPST_ACRO_MAXIMIZE_INTERVAL);

#ifdef CHECK_MAXIMIZE
if(wnd_pl.showCmd == SW_SHOWMAXIMIZED) sprintf(str_buf, "nustatom wnd_pl.showCmd: SW_SHOWMAXIMIZED %x", retc);
else sprintf(str_buf, "nustatom wnd_pl.showCmd: %d %x", wnd_pl.showCmd, retc);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI, 300);
#endif
PutLogMessage_("MaximizeAcroWindowSingle 8 %x %x %d", retc, dlg_wnd, wnd_pl.showCmd);
                     if (SUCCEEDED(retc))
                        if (!SetWindowPlacement(dlg_wnd, &wnd_pl)) // klaida, jei langa jau spejo uzdaryt
                           retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

PutLogMessage_("MaximizeAcroWindowSingle 9 %x", retc);

// if(SUCCEEDED(retc)){ KP_TRACE("MaximizeAcroWindowSingle() maximized"); }

// ------------------------------------------ iskeliam i virsu
                     if(on_top && SUCCEEDED(retc))
                     {
// --------------------------
#if TRUE // #if FALSE //
//                      if (SUCCEEDED(retc)) if(!SetFocus(dlg_wnd))
//                         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

                        if (SUCCEEDED(retc)) if(!SetForegroundWindow(dlg_wnd))
                        {
//                         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                        }
#endif

// ---------------------
#if FALSE // #if TRUE //
                        if (SUCCEEDED(retc))
                           if (!BringWindowToTop(dlg_wnd))
                              retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif

// ---------------------
#if TRUE // #if FALSE
HDC hdc=NULL;
int win_dx=0;
int win_dy=0;
                        if (SUCCEEDED(retc))
                        {
                           hdc = GetDC(HWND_DESKTOP);
                           if (hdc == NULL)
                              retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
                        }
                        if (hdc && SUCCEEDED(retc))
                        {
                           win_dx = GetDeviceCaps(hdc, HORZRES);
                           win_dy = GetDeviceCaps(hdc, VERTRES);
                        }

// KP_TRACE("SetWindowPos(dlg_wnd, HWND_TOP...");

                        if (SUCCEEDED(retc)) if (dlg_wnd != GetForegroundWindow())
                           if (!SetWindowPos(dlg_wnd, HWND_TOPMOST /* HWND_TOP */, 0, 0, win_dx, win_dy, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE))
                              retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
                     } // if(on_top && SUCCEEDED(retc))

                  } // if(((wnd_pl.showCmd == SW_SHOWMINIMIZED) || on_top) && SUCCEEDED(retc))

// --------------------- uzpiesiam maza languti virs uzdarymo mygtuku
#if FALSE
                  if (SUCCEEDED(retc))
                  {
WNDCLASSEX wcx;

                     wcx.hInstance     = hKpInstance;
                     wcx.lpszClassName = "KPSBMP",
                     wcx.lpfnWndProc   = (WNDPROC)KpStShBmpProc;
                     wcx.style         = CS_DBLCLKS;
                     wcx.cbSize        = sizeof(WNDCLASSEX);
                     wcx.hIcon         = LoadIcon(NULL /* hKpInstance */, MAKEINTRESOURCE(IDI_APPLICATION));
                     wcx.hIconSm       = LoadIcon(NULL /* hKpInstance */, MAKEINTRESOURCE(IDI_APPLICATION));
                     wcx.hCursor       = LoadCursor(0, IDC_ARROW);
                     wcx.lpszMenuName  = 0;
                     wcx.cbClsExtra    = 0;
                     wcx.cbWndExtra    = 0;
                     wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

                     if (!RegisterClassEx(&wcx))
                     {
//                      retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                     }
                  }

                  if ((m_hHideCloseButtonBmp == 0) && SUCCEEDED(retc))
                  {
                     m_hHideCloseButtonBmp = LoadBitmap(hKpInstance, MAKEINTRESOURCE(KP_IDI_HIDE_CLOSE_BUTTON_BMP_XP));
                     if (m_hHideCloseButtonBmp == 0)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
                  }


                  if ((m_hHideCloseButtonWnd == NULL) && SUCCEEDED(retc))
                  {
                     m_hHideCloseButtonWnd = CreateWindowEx
                     (
                        WS_EX_TOPMOST,        // DWORD dwExStyle,      // extended window style
                        "KPSBMP",
                        "",       // LPCTSTR lpWindowName, // pointer to window name
                        WS_POPUP | WS_VISIBLE,             //  WS_POPUPWINDOW|WS_BORDER|WS_THICKFRAME|WS_CAPTION|WS_POPUP, // DWORD dwStyle,        // window style
                        win_dx - KPST_HIDE_CLOSE_BUT_WND_DX,   // CW_USEDEFAULT, // int x,               // horizontal position of window
                        0,                                     // CW_USEDEFAULT, // int y,               // vertical position of window
                        KPST_HIDE_CLOSE_BUT_WND_DX,   // int nWidth,           // window width
                        KPST_HIDE_CLOSE_BUT_WND_DY,   // int nHeight,          // window height
                        HWND_DESKTOP,  // HWND hWndParent,      // handle to parent or owner window
                        0,             // HMENU hMenu,          // handle to menu, or child-window identifier
                        hKpInstance,
                        &m_hHideCloseButtonBmp  // bmp_pars  // this  /* KpStApp */  // LPVOID lpParam  // pointer to window-creation data
                     );
                     if (m_hHideCloseButtonWnd==NULL)
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  }

                  if (m_hHideCloseButtonWnd && SUCCEEDED(retc))
                     if (!SetWindowPos(m_hHideCloseButtonWnd, HWND_TOPMOST, win_dx - KPST_HIDE_CLOSE_BUT_WND_DX, 0, KPST_HIDE_CLOSE_BUT_WND_DX, KPST_HIDE_CLOSE_BUT_WND_DY, SWP_NOMOVE | SWP_NOSIZE))
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif

// -------------------------------------- bandom nustatyti fokusà á darbinæ AcroRead sritá – po iðorinës komandos iðkvietimo fokusas jai negráþta
// -------------------------------------- nieko neiðëjo – reikia Acrobate kiekvieno mygtuko procedûros pabaigoje paðokinët per puslapius pirmyn/atgal – tada mygtukas pameta fokusà
#if FALSE
unsigned char wnd_name[KP_MAX_FNAME_LEN + 1];
GetWindowText(dlg_wnd, (char *)wnd_name, KP_MAX_FNAME_LEN);

// --- bandom fokusuot kaþkurá controlà, bet vargu – problema Acrobato darbinës srities viduj – po mygtuko paspaudimo fokusas lieka jam (tarpas vël já paspaudþia)
int ii = 0;
HWND cur_wnd = NULL;
                  if(SUCCEEDED(retc))
                  {
                     cur_wnd = GetWindow(dlg_wnd, GW_CHILD);
                     while (cur_wnd && SUCCEEDED(retc))
                     {
GetWindowText(cur_wnd, (char *)wnd_name, KP_MAX_FNAME_LEN);
PutLogMessage_("MaximizeAcroWindowSingle()    2: %d [%s]", ii, wnd_name);

// WM_NEXTDLGCTL nepadeda, gal dar SetFocus() padëtø, bet vargu
#if FALSE
                        if (ii == 1) // AcroRead_709 langas turi 7 vaikus
                        {
//                         KP_ASSERT0(SetFocus(cur_wnd), KP_E_SYTEM_ERROR, GetLastError(), null, True);
                           SendMessage(dlg_wnd, WM_NEXTDLGCTL, (WPARAM)cur_wnd, TRUE);
PutLogMessage_("MaximizeAcroWindowSingle()    3: %d", ii);
                        }
#endif

// --------------- mygtuko fokusà numuða Esc
//                      if(SUCCEEDED(retc)) PostMessage(cur_wnd, WM_CHAR, Esc, 0);
                        if(SUCCEEDED(retc)){ PostMessage(cur_wnd, WM_KEYDOWN, Esc, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                        if(SUCCEEDED(retc)){ PostMessage(cur_wnd, WM_KEYUP, Esc, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //

                        ii++;
                        cur_wnd = GetWindow(cur_wnd, GW_HWNDNEXT);
                     }
                  }

// --------------- mygtuko fokusà numuða Esc
//                if (SUCCEEDED(retc)) PostMessage(dlg_wnd, WM_CHAR, Esc, 0);
                  if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYDOWN, Esc, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                  if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYUP, Esc, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
#endif



// >>>>>> 2013-02-06  mp
// --------------------------------------------
#ifdef KPST_MULTI_DOCS
// Daugiadokumenèiam Adobe Redaerio langui siunèiam Ctrl+Shift+L
                  if (!m_bMDImaximized)
                  {
                     m_bMDImaximized = True;
#  if FALSE
                     if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYDOWN, Ctrl, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                     if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYDOWN, Shift, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                     if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYDOWN, 'L', 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                     if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYUP, 'L', 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                     if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYUP, Shift, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
                     if (SUCCEEDED(retc)){ PostMessage(dlg_wnd, WM_KEYUP, Ctrl, 0); retc = KpSleep(100, HWND_DESKTOP); } // Sleep(100); } //
#  endif
INPUT input_arr[6];
                     for (int ii = 0; ii < 6; ii++)
                     {
                        input_arr[ii].type = INPUT_KEYBOARD;
                        input_arr[ii].ki.time = 0L;
                        input_arr[ii].ki.dwExtraInfo = 0L;
                        input_arr[ii].ki.wScan = 0;
                     }

                     input_arr[0].ki.wVk = VK_SHIFT;
                     input_arr[0].ki.dwFlags = 0;
                     input_arr[1].ki.wVk = VK_CONTROL;
                     input_arr[1].ki.dwFlags = 0;
                     input_arr[2].ki.wVk = 'L';
                     input_arr[2].ki.dwFlags = 0;
                     input_arr[3].ki.wVk = 'L';
                     input_arr[3].ki.dwFlags = KEYEVENTF_KEYUP;
                     input_arr[4].ki.wVk = VK_CONTROL;
                     input_arr[4].ki.dwFlags = KEYEVENTF_KEYUP;
                     input_arr[5].ki.wVk = VK_SHIFT;
                     input_arr[5].ki.dwFlags = KEYEVENTF_KEYUP;

                     if (!SendInput(6, &input_arr[0], sizeof(input_arr[0])))
                        KP_WARNING(KP_E_SYSTEM_ERROR, GetLastError());
            
                  } // if (!m_bMDImaximized)
#endif
// <<<<<< 2013-02-06  mp

               } // if (dlg_wnd)
               
            } while (dlg_wnd && SUCCEEDED(retc));   

         } // if((!pwd_wnd) && (!save_as_wnd) && SUCCEEDED(retc))

      } // if(((!full_scr) || on_top) && SUCCEEDED(retc))

   } // if((on_top || full_scr) && SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
#if FALSE
HRESULT KpStApp::MaximizeAcroWindowProcess(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
MSG msg;
HWND dlg_wnd=NULL;
bool endfl=False;
DWORD exit_code;
int retp;
// unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

   if(SUCCEEDED(retc))
   {
      poll_timer_id = SetTimer(HWND_DESKTOP /* m_hBitmapWindow */, KP_POLL_TIMER, KP_POLL_TIMEOUT, NULL);
      if(!poll_timer_id)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      else msg_fl=True;

      if(msg_fl && SUCCEEDED(retc))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);

         retp = LOWORD(msg.wParam);
      }

      if(msg_fl && SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_CHAR:
// KP_TRACE("keyboard message");
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
// KP_TRACE("KP_HP11_TOGGLE_CONSOLE keyboard message");
            if(lKphp11ThreadId!=NULL)
               if(!::PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            break;
         }
         break;

      case WM_TIMER:
         if(retp == poll_timer_id)
         {
// check if window is allready open
            dlg_wnd=GetWindowByName(KPST_ACROREAD_WINDOW_NAME, False);
            if(dlg_wnd!=NULL)
            {
               if(SUCCEEDED(retc)) retc=KpSleep(1000, HWND_DESKTOP); // Sleep(1000);
               if(SUCCEEDED(retc)) retc=MaximizeAcroWindowSingle(False);

// ------ kartoti letiems kompams
               if(SUCCEEDED(retc)) retc=KpSleep(2000, HWND_DESKTOP); // Sleep(2000);
               if(SUCCEEDED(retc)) retc=MaximizeAcroWindowSingle(False);

               endfl=True;
            }

// check whether main process is still running
            if(SUCCEEDED(retc))
            {
               if(m_hCmdProcess)
               {
                  if(!GetExitCodeProcess(m_hCmdProcess, &exit_code))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }
               else if(m_hCmdThread)
               {
                  if(!GetExitCodeThread(m_hCmdThread, &exit_code))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
               }
               else exit_code = (~STILL_ACTIVE);
            }
            if((exit_code!=STILL_ACTIVE) && SUCCEEDED(retc)) endfl=True;

         } // if(retp == poll_timer_id)

         break;

      case WM_COMMAND:
PutLogMessage_("MaximizeAcroWindowProcess() WM_COMMAND: %d %ld", retp, msg.lParam);
         switch(retp)
         {
#if FALSE
// jei nepagaunam èia – apdorojimas yra ir KpStaWindowProc()
            case KPST_ID_REST_DAYS_EXCEEDED:
               if(msg.lParam <= KPST_REST_DAYS_WARNING)
               {
                  if(msg.lParam <= 0)
                  {
static unsigned char str_buf[2000];
                     sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
                     KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
                     KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                     endfl = True;
                     retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
                  }
                  else
                  {
                     if(!RestDaysWarningShowed())
                     {
                        switch(msg.lParam)
                        {
                        case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
                        case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
                        default: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, msg.lParam); break;
                        }
                     }
//                   m_iRestDaysWarningShowed = True;
                     KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
                  }
               }
               break;
#endif
         case IDCANCEL:
            endfl = True;
            retc = KP_E_CANCEL;
            break;
         }
         break;

      case WM_QUIT:
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT: retc = KP_E_SYSTEM_ERROR; break;
         }
         endfl=True;
         break;

      default:
         break;

      } // switch(msg.message)

   } while((!endfl) && SUCCEEDED(retc));

   if(poll_timer_id)
   {
      if(!KillTimer(m_hBitmapWindow, poll_timer_id))
      {
         retc0=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc)) retc=retc0;
      }
      poll_timer_id=0;
   }

return(retc);
}
#endif


// ----------------------
#if FALSE
HRESULT KpStApp::MinimizeIEWindow(void)
{
HRESULT retc = S_OK;
HWND ie_wnd = NULL;
WINDOWPLACEMENT wnd_pl;

   if(SUCCEEDED(retc)) ie_wnd = GetWindowByName((const unsigned char *)"Windows Internet Explorer", False, NULL);

   if(ie_wnd && SUCCEEDED(retc))
   {
//    if(!SetWindowPos(ie_wnd, HWND_BOTTOM, 0, 0, 600, 800, SWP_HIDEWINDOW | SWP_NOMOVE | SWP_NOSIZE))
//       KP_ERROR(KP_E_SYSTEM_ERROR, null);

      wnd_pl.length = sizeof(WINDOWPLACEMENT);
      if(!GetWindowPlacement(ie_wnd, &wnd_pl)) // klaida, jei langa jau spejo uzdaryt
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         wnd_pl.showCmd = SW_MINIMIZE; // SW_SHOWMINIMIZED;
         if(!SetWindowPlacement(ie_wnd, &wnd_pl)) // klaida, jei langa jau spejo uzdaryt
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      }
   }

return(retc);
}
#endif


// ----------------------
bool KpStApp::TestPradInf(void)
{
HWND dlg_wnd = NULL;

   dlg_wnd = GetWindowByName((const unsigned char *)"Pradin", False); // "Pradinë informacija"
   if(!dlg_wnd) dlg_wnd = GetWindowByName((const unsigned char *)"Informacinis prane", False); // "Informacinis praneðimas"

return(dlg_wnd != NULL);
}


HRESULT KpStApp::DoHideBookMark(void /* int iBarWdt */)
{
HRESULT retc=S_OK;
INPUT input_str;
// HDC dc;
// int desktop_dx;
HCURSOR curs = NULL;
CURSORINFO ci;
int back_dx = 0;

   if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

   if(SUCCEEDED(retc))
   {
      input_str.type = INPUT_MOUSE;
      input_str.mi.mouseData = 0;
      input_str.mi.time = 0;

      input_str.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
      input_str.mi.dx = 0; // 1050;
      input_str.mi.dy = 65535 / 2;

      if(!SendInput(1, &input_str, sizeof(input_str)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      Sleep(50);
   }

#if FALSE
   if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

   if(SUCCEEDED(retc))
   {
      dc = GetDC(HWND_DESKTOP);
      if(dc == NULL)
      {
#ifdef Debug
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
         retc = KP_E_SYSTEM_ERROR;
      }
   }
#endif

   if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

// if(SUCCEEDED(retc)) desktop_dx = GetDeviceCaps(dc, VERTRES);

   if(SUCCEEDED(retc))
   {
//    curs =  GetCursor();
// KpMsgOutF_1("curs %x", curs);

      ci.cbSize =  sizeof(CURSORINFO);
      if(!GetCursorInfo(&ci))
      {
#ifdef Debug
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
      }
      else
      {
         curs = ci.hCursor;
// KpMsgOutF_1("curs %x", curs);
      }
   }

   if(SUCCEEDED(retc))
   {
      input_str.mi.dwFlags = MOUSEEVENTF_MOVE;
      input_str.mi.dy = 0;

//    switch(m_iBkmrkFontSize)
//    {
//    case 0: input_str.mi.dx = 11; break;
//    case 1: input_str.mi.dx = 20; break;
//    case 2: input_str.mi.dx = 30; break;
//    default: input_str.mi.dx = 20; break;
//    }

//    input_str.mi.dx = 11;
// // if(desktop_dx > 800) input_str.mi.dx = 20;
//    if(iWindowsVersion >= WinVista) input_str.mi.dx = 20;

//    input_str.mi.dx = iBarWdt;

      input_str.mi.dx = 8;

      back_dx = 7;

      if(!SendInput(1, &input_str, sizeof(input_str)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      Sleep(10);

// KpMsgOutF_2("Jau dx:%d font:%d", input_str.mi.dx, m_iBkmrkFontSize);
// KpMsgOutF_1("Jau dx:%d", input_str.mi.dx);

   }

   if(SUCCEEDED(retc)) do
   {
      if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

//    if(curs ==  GetCursor()) retc = KP_E_SKIP;
// KpMsgOutF_1("GetCursor() %x", GetCursor());

      ci.cbSize =  sizeof(CURSORINFO);
      if(!GetCursorInfo(&ci))
      {
#ifdef Debug
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL, False);
#endif
      }
      else
      {
// KpMsgOutF_1("new curs 1 %x", ci.hCursor);
//       if(curs == ci.hCursor) retc = KP_E_SKIP;
         if(curs != ci.hCursor) break;
      }

      if(SUCCEEDED(retc)) if(curs == ci.hCursor)
      {
         input_str.mi.dwFlags = MOUSEEVENTF_MOVE;
         input_str.mi.dy = 0;

         input_str.mi.dx = 2;

         back_dx += input_str.mi.dx;

         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(50);
      }

   } while((curs == ci.hCursor) && (back_dx < 100) && SUCCEEDED(retc));

   if(SUCCEEDED(retc)) if(back_dx >= 100) retc = KP_E_SKIP;

   if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

   if(SUCCEEDED(retc))
   {
      input_str.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

// KpMsgOutF_0("Jau");
      if(!SendInput(1, &input_str, sizeof(input_str)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      Sleep(50);
   }

   if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

   if(SUCCEEDED(retc))
   {
      input_str.mi.dwFlags = MOUSEEVENTF_MOVE; // | MOUSEEVENTF_LEFTDOWN;
      input_str.mi.dy = 0;

//    input_str.mi.dx = 1 - input_str.mi.dx; // = -20; // -1000;
      input_str.mi.dx = -back_dx;

      if(!SendInput(1, &input_str, sizeof(input_str)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      Sleep(50);
   }

   if(SUCCEEDED(retc)) if(TestPradInf()) retc = KP_E_SKIP;

   if(SUCCEEDED(retc))
   {
      input_str.mi.dwFlags = MOUSEEVENTF_LEFTUP;

      if(!SendInput(1, &input_str, sizeof(input_str)))
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      Sleep(50);
   }

   if(retc == KP_E_SKIP) retc = S_OK;

return(retc);
}


HRESULT KpStApp::HideBookMarks(void)
{
HRESULT retc=S_OK;

#if FALSE
bool hide_bkmrks = False;
POINT old_mouse_pos;
HWND dlg_wnd = NULL;
WINDOWPLACEMENT wnd_pl;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];

   if(SUCCEEDED(retc)) retc = GetIniHideBkmrks(&hide_bkmrks);

   if(SUCCEEDED(retc))
   {
// jei atsirado langas "Pradinë informacija" – kartosim, kai uþsidarys
      if(TestPradInf())
      {
         m_bBookMarksHided = False;
// KpMsgOutF_0("Dar kartà");
      }
   }

   if(!m_bBookMarksHided && SUCCEEDED(retc)) // if(time(NULL) - m_lStartTime > 15)
   {

      if(hide_bkmrks && SUCCEEDED(retc))
      {
// KpMsgOutF_0("Jau");

// ----------------------------------- ar Acro langas jau maximizuotas?
         if(SUCCEEDED(retc))
         {
            dlg_wnd = GetWindowByName(KPST_ACROREAD_WINDOW_NAME, False);
            if(dlg_wnd != NULL)
               if(GetWindowText(dlg_wnd, (char *)str_buf, KP_MAX_FNAME_LEN) > 0)
                  if(strcmp(str_buf, KPST_ACROREAD_WINDOW_NAME) == 0) dlg_wnd = NULL;
         }

         if(dlg_wnd && SUCCEEDED(retc))
         {
            wnd_pl.length = sizeof(WINDOWPLACEMENT);

            if(!GetWindowPlacement(dlg_wnd, &wnd_pl))
               retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
            else
            {

// KpMsgOutF_3("HideBookMarks: %d SW_SHOWMAXIMIZED: %d SW_SHOWNORMAL: %d", wnd_pl.showCmd, SW_SHOWMAXIMIZED, SW_SHOWNORMAL);

               if((wnd_pl.showCmd == SW_SHOWMAXIMIZED) /* || (wnd_pl.showCmd == SW_SHOWNORMAL) */)
               {
//                Sleep(4000); // laukiam, kol, gal bût, atsidarys langas "Pradinë informacija"

// KpMsgOutF_0("Jau 1");

// ----------------------------------- ar jau uþgesintas langelis "Pradinë informacija"
                  if(!TestPradInf())
                  {
// KpMsgOutF_0("Jau 2");

                     m_bBookMarksHided = True;

                     Sleep(3000); // laukiam, kol maximizuotas langas pradës reaguoti ir "Pradinë informacija" tikrai uþsidarys

// ---------------------------
                     if(SUCCEEDED(retc)) if(!GetCursorPos(&old_mouse_pos)) // get current mouse possition
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// --------------------------- stumiam du kartus dviem skirtingiem ploèiams, nes neaiðku, nuo ko priklauso
//                   if(SUCCEEDED(retc)) retc = DoHideBookMark(11);
//                   if(SUCCEEDED(retc)) retc = DoHideBookMark(17);
//                   if(SUCCEEDED(retc)) retc = DoHideBookMark(20);

                     if(SUCCEEDED(retc)) retc = DoHideBookMark();

// ---------------------------
                     if(SUCCEEDED(retc)) if(!SetCursorPos(old_mouse_pos.x, old_mouse_pos.y)) // restore mouse possition
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

// ---------------------------
                  } // if(!dlg_wnd) ("Pradinë informacija")

               } // if(wnd_pl.showCmd == SW_SHOWMAXIMIZED)

            } // else // if(!GetWindowPlacement(dlg_wnd, &wnd_pl))

         } // if(dlg_wnd && SUCCEEDED(retc)) (KPST_ACROREAD_WINDOW_NAME)

      } // if(hide_bkmrks && SUCCEEDED(retc))

   } // if(!m_bBookMarksHided && SUCCEEDED(retc))
#endif

return(retc);
}


// ----------------------
HRESULT KpStApp::CloseLaunchPrompt(void)
{
HRESULT retc=S_OK;
HWND launch_wnd = 0;
HWND button_wnd = 0;
static unsigned char str_buf[KP_MAX_FNAME_LEN+1];

   launch_wnd = GetWindowByName((const unsigned char *)"Launch: ", False);
   if(launch_wnd)
   {
// GetWindowText(launch_wnd, (char *)str_buf, KP_MAX_FNAME_LEN);
// KpMsgOut("radau Launch:", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

      launch_wnd=GetChildWindow(launch_wnd, 0);
      if(launch_wnd)
      {
         launch_wnd=GetChildWindow(launch_wnd, 0);
         if(launch_wnd)
         {

// ------------------------------------------------------- "Do not show this message again"
            if(SUCCEEDED(retc))
            {
               button_wnd=GetChildWindow(launch_wnd, 2);
               if(button_wnd)
               {
// KpMsgOut("radau chbox", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
                  str_buf[0]=Nul;
                  if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  else
                  {
                     if(strcmp(str_buf, "&Do not show this message again") != 0)
                     {
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#ifdef Debug
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#endif
                     }
                     else
                     {
// KpMsgOut("radau \"Do not show\"", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

                        if(SUCCEEDED(retc)) retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);

                        if(SUCCEEDED(retc))
                        {
                           SendMessage(button_wnd, WM_ACTIVATE , WA_CLICKACTIVE, 0);
                           retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
                        }

                        if(SUCCEEDED(retc))
                        {
                           SendMessage(button_wnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                           retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
                        }

                        if(SUCCEEDED(retc)) SendMessage(button_wnd, WM_LBUTTONUP, 0, 0);

                     } // else // if(strcmp(str_buf, "OK") != 0)

                  } // else // if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))

               } // if(button_wnd)

            } // if(SUCCEEDED(retc))


// ------------------------------------------------------- "Open"
            if(SUCCEEDED(retc))
            {
               button_wnd=GetChildWindow(launch_wnd, 3);
               if(button_wnd)
               {
// KpMsgOut("radau button", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
                  str_buf[0]=Nul;
                  if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  else
                  {
                     if(strcmp(str_buf, "&Open") != 0)
                     {
// KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#ifdef Debug
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
#endif
                     }
                     else
                     {
// KpMsgOut("radau Open", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

                        if(SUCCEEDED(retc)) retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);

                        if(SUCCEEDED(retc))
                        {
                           SendMessage(button_wnd, WM_ACTIVATE , WA_CLICKACTIVE, 0);
                           retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
                        }

                        if(SUCCEEDED(retc))
                        {
                           SendMessage(button_wnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                           retc=KpSleep(200, HWND_DESKTOP); // Sleep(200);
                        }

                        if(SUCCEEDED(retc)) SendMessage(button_wnd, WM_LBUTTONUP, 0, 0);

                     } // else // if(strcmp(str_buf, "OK") != 0)

                  } // else // if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))

               } // if(button_wnd)

            } // if(SUCCEEDED(retc))

// -------------
         } // if(launch_wnd)

      } // if(launch_wnd)

   } // if(launch_wnd)

return(retc);
}


// ----------------------
HRESULT KpStApp::CloseAutoPlay(void)
{
HRESULT retc=S_OK;
HWND autoplay_wnd = 0;
HWND button_wnd = 0;
unsigned char vol_name[KP_MAX_FNAME_LEN+10];
// char str_buf[KP_MAX_FNAME_LEN+1];

   vol_name[0] = Nul;

// ------------------------------------------------
// Vista
   if(SUCCEEDED(retc)) autoplay_wnd = GetWindowByName((const unsigned char *)"AutoPlay", True);
   if(autoplay_wnd && SUCCEEDED(retc))
   {
// KpMsgOut("radau AutoPlay", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

#if FALSE
      if(!(::DestroyWindow(autoplay_wnd)))
      {
// KpMsgOut("negaliu u_daryt AutoPlay", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#ifdef Debug
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif
      }
#endif

//    PostMessage(autoplay_wnd, WM_QUIT, IDABORT /* 0 */, 0);
      PostMessage(autoplay_wnd, WM_COMMAND, IDCANCEL, 0);

   } // if(autoplay_wnd && SUCCEEDED(retc))

// ------------------------------------------------
// XP
   if((!autoplay_wnd) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = GetIniVolName(vol_name);
      if(SUCCEEDED(retc)) strcat(vol_name, " ("); // "keng_3131 (F:)"
      if(SUCCEEDED(retc)) do
      {
         autoplay_wnd = GetWindowByName(vol_name, False, autoplay_wnd);
// KpMsgOut(vol_name, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

         if(autoplay_wnd && SUCCEEDED(retc))
         {
#if FALSE
// KpMsgOut("radau AutoPlay", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
str_buf[0]=Nul;
GetWindowText(autoplay_wnd, (char *)str_buf, KP_MAX_FNAME_LEN);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
            button_wnd=GetChildWindow(autoplay_wnd, 9-1); // XP Autoplay lango mygtukas "Cancel" yra 9-tas
//          if(!button_wnd)
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);

            if(button_wnd!=NULL) // reikia tikrint - jei nera Cancel (9-to) mygtuko - tada cia explorerio langas (su 6-ais laukais, 9-to nera)
            {
// tikrinam, ar tikrai "Cancel" mygtukas
#if FALSE // #if TRUE // #ifdef Debug
               str_buf[0]=Nul;
               if(!GetWindowText(button_wnd, (char *)str_buf, KP_MAX_FNAME_LEN))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

               if(SUCCEEDED(retc))
#endif
               {
#if FALSE // #ifdef Debug
                  if((strcmp(str_buf, "Cancel") != 0) && (button_wnd!=dlg_wnd))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L);
                  else
#endif
                  {
#if FALSE
                     if(SUCCEEDED(retc))
                     {
                        SendMessage(button_wnd, WM_ACTIVATE , WA_CLICKACTIVE, 0);
                        Sleep(100); // retc=KpSleep(100, HWND_DESKTOP);
                     }
                     if(SUCCEEDED(retc))
                     {
                        SendMessage(button_wnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
                        Sleep(100); // retc=KpSleep(100, HWND_DESKTOP);
                     }
                     if(SUCCEEDED(retc))
                        SendMessage(button_wnd, WM_LBUTTONUP, 0, 0);
//                      Sleep(100); // retc=KpSleep(100, HWND_DESKTOP);
#endif
                     PostMessage(autoplay_wnd, WM_COMMAND, IDCANCEL, 0);
                  }

               } // if(SUCCEEDED(retc))

            } // if(button_wnd!=NULL)

         } // if(autoplay_wnd && SUCCEEDED(retc))

      } while(autoplay_wnd && SUCCEEDED(retc));

   } // if((!autoplay_wnd) && SUCCEEDED(retc))

return(retc);
}


// ----------------------
HRESULT KpStApp::CloseCompatibilityAssistant(void)
{
HRESULT retc=S_OK;
HWND comp_wnd = 0;
HWND button_wnd = 0;
INPUT input_str;

   comp_wnd = GetWindowByName((const unsigned char *)"Program Compatibility Assistant", True);
   if(comp_wnd)
   {
// KpMsgOut("radau Compatibility", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

#if FALSE // #if TRUE //
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYDOWN, Alt, 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYDOWN, 'D', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYUP, 'D', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYUP, Alt, 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);

      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYDOWN, Alt, 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYDOWN, 'D', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYUP, 'D', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYUP, Alt, 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);

      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_CHAR, ' ', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);

      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_CHAR, ' ', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);

//    if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_CHAR, 'R', 0); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);

      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYDOWN, 'R', 0x130001); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);
      if(SUCCEEDED(retc)){ PostMessage(comp_wnd, WM_KEYUP, 'R', 0xc0130001); retc=KpSleep(100, HWND_DESKTOP); } // Sleep(100);

#else

      if(SUCCEEDED(retc))
      {
         input_str.type = INPUT_KEYBOARD;
         input_str.ki.time = 0L;
         input_str.ki.dwFlags = 0; // KEYEVENTF_SCANCODE;
         input_str.ki.dwExtraInfo = 0L;
      }
//-------------------- Alt+D
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = Alt;
         input_str.ki.wScan = 0x38;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = 'D';
         input_str.ki.wScan = 0x20;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;
         input_str.ki.wVk = 'D';
         input_str.ki.wScan = 0x20;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;
         input_str.ki.wVk = Alt;
         input_str.ki.wScan = 0x38;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
// Sleep(500);

//-------------------- Alt+D
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = Alt;
         input_str.ki.wScan = 0x38;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = 'D';
         input_str.ki.wScan = 0x20;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;
         input_str.ki.wVk = Alt;
         input_str.ki.wScan = 0x38;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
// Sleep(500);

//-------------------- ' '
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = ' ';
         input_str.ki.wScan = 0x39;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;

         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         Sleep(100);
      }
// Sleep(500);

#if FALSE
//-------------------- ' '
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = ' ';
         input_str.ki.wScan = 0x39;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;

         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         Sleep(100);
      }
// Sleep(500);
#endif

//-------------------- R
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags &= ~KEYEVENTF_KEYUP;
         input_str.ki.wVk = 'R';
         input_str.ki.wScan = 0x13;
         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         Sleep(100);
      }
      if(SUCCEEDED(retc))
      {
         input_str.ki.dwFlags |= KEYEVENTF_KEYUP;

         if(!SendInput(1, &input_str, sizeof(input_str)))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

         Sleep(100);
      }

#endif

   } // if(comp_wnd)

return(retc);
}


// ----------------------
// glob.js nebearchyvuojam, kad neiðgliaudytø kintamøjø, tik arkimui ir bebrui - ten, kur yra RezFName
// nearchyvuojam jau niekam – ið glob.js rezultatø nebeskaitom – kad senos ðiukðlës netrukdytø (pas Rolandà buvo kintamasis "klase")
HRESULT KpStApp::SaveGlobalJs(void)
{
HRESULT retc=S_OK;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];

// KP_TRACE("SaveGlobalJs()");

   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc)) // if(strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT))
   {
      strlwr(cmd_str);
      if((strstr(cmd_str, KPST_PDF_FILE_TYPE) != NULL) || (strstr(cmd_str, KPST_TEV_OBJ_FILE_TYPE) != NULL))
      {
// glob.js nebearchyvuolam
#if FALSE
static unsigned char js_fname[KP_MAX_FNAME_LEN+1];
static unsigned char js_sav_fname[KP_MAX_FNAME_LEN+1];
static unsigned char js_log_fname[KP_MAX_FNAME_LEN+1];
unsigned char *pntd=NULL;
FILE *js_file=NULL;
FILE *js_sav_file=NULL;
FILE *js_log_file=NULL;
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
unsigned char *js_file_contents = NULL;
long js_file_len;

         if(SUCCEEDED(retc)) retc=GetGlobalJsName(js_fname);

         if(SUCCEEDED(retc)) retc=CreatePath(js_fname, True);

// KpMsgOut(js_fname, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

         if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, js_fname);

         if(SUCCEEDED(retc))
         {
            strcpy(js_sav_fname, disk);
            strcat(js_sav_fname, path);
            strcat(js_sav_fname, "\\");
            strcat(js_sav_fname, name);
            strcat(js_sav_fname, SAV_FILE_TYPE);

// ar yra glob.js? jei ne - nieko nedarom
            js_file=fopen((const char *)js_fname, "r");
            if(js_file!=NULL)
            {
               fclose(js_file);
               js_file = NULL;

               js_file_contents = NULL;
               if(SUCCEEDED(ReadFileContents(js_fname, &js_file_contents, &js_file_len, False, False)))
               {
// tikrinam, ar jau yra glob.sav
                  js_sav_file=fopen((const char *)js_sav_fname, "r");
                  if(js_sav_file!=NULL)
                  {
                     fclose(js_sav_file);
                     js_sav_file=NULL;

// glob.sav jau yra, glob.js prijunginesim prie glob.log - jame gali buti senu rezultatu
                     strcpy(js_log_fname, disk);
                     strcat(js_log_fname, path);
                     strcat(js_log_fname, "\\");
                     strcat(js_log_fname, name);
                     strcat(js_log_fname, HIST_FILE_TYPE);

                     js_log_file=fopen((const char *)js_log_fname, "a");
                     if(js_log_file==NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, False, __FILE__, __LINE__, 0L);
                     else
                     {
                        fprintf(js_log_file, "---------------------------\n");
                        if(ferror(js_log_file) || feof(js_log_file))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);

                        fputs((const char *)js_file_contents, js_log_file);
                        if(ferror(js_log_file) || feof(js_log_file))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);

                        if(fclose(js_log_file))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, False, __FILE__, __LINE__, 0L);
                        js_log_file=NULL;

                     } // else // if(js_file==NULL)

                  } // if(js_sav_file!=NULL)

// perkopijuojam/prijungiam glob.js i glob.sav
                  js_sav_file=fopen((const char *)js_sav_fname, "a");
                  if(js_sav_file==NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  else
                  {
                     fputs((const char *)js_file_contents, js_sav_file);
                     if(ferror(js_sav_file) || feof(js_sav_file))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);

                     if(fclose(js_sav_file) && SUCCEEDED(retc))
                        retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                     js_sav_file=NULL;
                  }

               } // if(SUCCEEDED(ReadFileContents(js_fname, &js_file_contents, &js_file_len, False, False))

               KP_DELETEA(js_file_contents);

            } // if(js_file!=NULL)

         } // if(SUCCEEDED(retc))

// ----------------
// padarem glob.sav, vis delto patikrinam, ar tikrai atsirado, jei nera - glob.js paliekam sena
         if(SUCCEEDED(retc))
         {
            js_sav_file=fopen((const char *)js_sav_fname, "r");
            if(js_sav_file!=NULL)
            {
// glob.sav yra - glob.js trinam
               fclose(js_sav_file);
               js_sav_file=NULL;

               js_file=fopen((const char *)js_fname, "w");
               if(js_file==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
               else
               {
                  if(fclose(js_file)!=0)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  js_file=NULL;

               } // else // if(js_file==NULL) // js_fname

            } // if(js_sav_file!=NULL)

         } // if(SUCCEEDED(retc))
#endif

// --------------------------------------
// issaugojam/istrinam rezultatai.txt

static unsigned char rez_file_name[KP_MAX_FNAME_LEN + 20 + 1];
         if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_file_name);
         if((rez_file_name[0] != Nul) && SUCCEEDED(retc))
         {
            rez_file_name[0] = Nul;

static unsigned char arc_file_name[KP_MAX_FNAME_LEN + 20 + 1];
FILE *rez_file = NULL;
FILE *arc_file = NULL;
unsigned char *rez_file_contents = NULL;
long rez_file_len;

            if(SUCCEEDED(retc)) retc = GetLocalPath(rez_file_name, KP_My_Documents);

            if(SUCCEEDED(retc))
            {
               strcpy(arc_file_name, rez_file_name);
               strcat(rez_file_name, KPST_REZ_FILE_NAME);
               strcat(arc_file_name, KPST_REZ_LOG_FILE_NAME);

               rez_file=fopen((const char *)rez_file_name, "r");
               if(rez_file!=NULL)
               {
                  fclose(rez_file);
                  rez_file = NULL;

                  if(SUCCEEDED(ReadFileContents(rez_file_name, &rez_file_contents, &rez_file_len, False, False)))
                  {
                     arc_file=fopen((const char *)arc_file_name, "a");
                     if(arc_file==NULL)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, False, __FILE__, __LINE__, 0L);
                     else
                     {
                        fputs((const char *)rez_file_contents, arc_file);
                        if(ferror(arc_file) || feof(arc_file))
                           retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);
                        else
                        {
                           if(fclose(arc_file))
                              retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, False, __FILE__, __LINE__, 0L);
                           else
                           {
                              if(!DeleteFile((const char *)rez_file_name))
                                 retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                           }
                           arc_file=NULL;

                        } // else // if(ferror(arc_file) || feof(arc_file))

                     } // else // if(arc_file==NULL)

                  } // if(SUCCEEDED(ReadFileContents(rez_file_name, &rez_file_contents, &rez_file_len, False, False)))

               } // if(rez_file!=NULL)

            } // if(SUCCEEDED(retc))

         } // if((rez_file_name[0] != Nul) && SUCCEEDED(retc))

      } // if(strstr(cmd_str_buf, KPST_PDF_FILE_TYPE)!=NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}


// ----------------------
#if FALSE
HRESULT KpStApp::RestoreGlobalJs(void)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
static unsigned char js_fname[KP_MAX_FNAME_LEN+1];
static unsigned char js_sav_fname[KP_MAX_FNAME_LEN+1];
static unsigned char js_log_fname[KP_MAX_FNAME_LEN+1];
unsigned char *pntd=NULL;
FILE *js_file=NULL;
FILE *js_sav_file=NULL;
FILE *js_log_file=NULL;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
static unsigned char disk[KP_MAX_FNAME_LEN+1];
static unsigned char path[KP_MAX_FNAME_LEN+1];
static unsigned char name[KP_MAX_FNAME_LEN+1];
static unsigned char type[KP_MAX_FTYPE_LEN+1];
bool skip_restore = False;
unsigned char *js_file_contents = NULL;
long js_file_len;

// KP_TRACE("RestoreGlobalJs()");

   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc)) // if(strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT))
   {
      strlwr(cmd_str);
      if((strstr(cmd_str, KPST_PDF_FILE_TYPE) != NULL) || (strstr(cmd_str, KPST_TEV_OBJ_FILE_TYPE) != NULL))
      {
         if(SUCCEEDED(retc)) retc=GetGlobalJsName(js_fname);

         if(SUCCEEDED(retc)) retc=CreatePath(js_fname, True);

         if(SUCCEEDED(retc)) retc=TvFnameSplit(disk, path, name, type, js_fname);

         skip_restore = False;

         if(SUCCEEDED(retc))
         {
// prijungiam glob.js prie glob.log - galimam busimam duomenu gelbejimui
            strcpy(js_log_fname, disk);
            strcat(js_log_fname, path);
            strcat(js_log_fname, "\\");
            strcat(js_log_fname, name);
            strcat(js_log_fname, HIST_FILE_TYPE);

            js_log_file=fopen((const char *)js_log_fname, "a");
            if(js_log_file==NULL)
            {
               retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, False, __FILE__, __LINE__, 0L);
               skip_restore = True;
            }
            else
            {
               fprintf(js_log_file, "---------------------------\n");
               if(ferror(js_log_file) || feof(js_log_file))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);

               js_file_contents = NULL;
               if(SUCCEEDED(ReadFileContents(js_fname, &js_file_contents, &js_file_len, False, False)))
               {
                  fputs((const char *)js_file_contents, js_log_file);
                  if(ferror(js_log_file) || feof(js_log_file))
                  {
                     skip_restore = True;
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, False, __FILE__, __LINE__, 0L);
                  }
               }

               KP_DELETEA(js_file_contents);

               if(fclose(js_log_file))
               {
                  skip_restore = True;
                  retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, False, __FILE__, __LINE__, 0L);
               }
               js_log_file=NULL;

            } // else // if(js_log_file==NULL)

         } // if(SUCCEEDED(retc))

         if((!skip_restore) && SUCCEEDED(retc))
         {
            strcpy(js_sav_fname, disk);
            strcat(js_sav_fname, path);
            strcat(js_sav_fname, "\\");
            strcat(js_sav_fname, name);
            strcat(js_sav_fname, SAV_FILE_TYPE);

            js_sav_file=fopen((const char *)js_sav_fname, "r");
            if(js_sav_file!=NULL)
            {
               fclose(js_sav_file);
               js_sav_file=NULL;

               if(!CopyFile((const char *)js_sav_fname, (const char *)js_fname, False))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
               else
               {
                  if(!DeleteFile((const char *)js_sav_fname))
                  {
                     retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
                  }
               }

            } // if(js_sav_file!=NULL)

         } // if(SUCCEEDED(retc))

      } // if(strstr(cmd_str_buf, KPST_PDF_FILE_TYPE)!=NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}
#elif FALSE
HRESULT KpStApp::DeleteGlobalJs(void)
{
HRESULT retc=S_OK;
static unsigned char js_fname[KP_MAX_FNAME_LEN+1];
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];

   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc)) // if(strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT))
   {
      strlwr(cmd_str);
      if((strstr(cmd_str, KPST_PDF_FILE_TYPE) != NULL) || (strstr(cmd_str, KPST_TEV_OBJ_FILE_TYPE) != NULL))
      {
         if(SUCCEEDED(retc)) retc=GetGlobalJsName(js_fname);

         if(SUCCEEDED(retc)) if(!DeleteFile((const char *)js_fname))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, GetLastError(), False, __FILE__, __LINE__, 0L);

      } // if(strstr(cmd_str_buf, KPST_PDF_FILE_TYPE)!=NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}
#else
HRESULT KpStApp::DeleteGlobalJsVariables(void)
{
HRESULT retc=S_OK;

   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_PRODVAR_SH_NAME, null, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT); // "ProdVar"
   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_PRODVER_SH_NAME, null, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT); // "ProdVer"
   if(SUCCEEDED(retc)) retc = SetPdfPar((const unsigned char *)"ProductDate", null);
   if(SUCCEEDED(retc)) retc = SetPdfPar((const unsigned char *)"ProductVersion", null, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT);

// try{eval((new String("global.ProductVersionMin=(new Number(1.02))")).valueOf());}catch(e){}
   if(SUCCEEDED(retc)) retc = SetPdfPar((const unsigned char *)"ProductVersionMin", null, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT);

   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_DATA_READY_PAR_NAME, null);
   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_TEST_PAR_NAME, null, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT);
   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_SRV_ADR_PAR_NAME, null);
   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_WAVE_DEVS_PAR_NAME, null, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT);
   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_FLASH_DEV_PAR_NAME, null);
   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_PROG_PATH_PAR_NAME, null);

// try{eval((new String("global.print_all=(new Boolean(false))")).valueOf());}catch(e){}
   if(SUCCEEDED(retc)) retc = SetPdfPar((const unsigned char *)"print_all", null, JS_BOOL_PAR_PREF_SHORT, JS_BOOL_PAR_TAIL_SHORT);

return(retc);
}
#endif


// -------------------------------------------
#include "TMGrpPrm.cpp"

HRESULT KpStApp::GetTMGrpPrmFName(unsigned char *lpszTMGrpPrmFNamBuf)
{
HRESULT retc=S_OK;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];

// ---------------------------------
   KP_ASSERT(lpszTMGrpPrmFNamBuf, E_INVALIDARG, null, True);

// -------------------------
   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc))
   {
      lpszTMGrpPrmFNamBuf[0]=Nul;

      if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) ||
         strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT) ||
         strstr(cmd_str, KPST_ACROREAD80_PATHNAME) || strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT) ||
         strstr(cmd_str, KPST_ACROREAD90_PATHNAME) || strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT))
      {
/* C:\My Documents\Adobe\Acrobat\6.0\ */
/* C:\WINNT\Profiles\tadas\Personal\Adobe\Acrobat\6.0\ */
/* C:\Documents and Settings\tadas\Application Data\Adobe\Acrobat\6.0\ */
         retc=GetLocalPath(lpszTMGrpPrmFNamBuf, KP_Application_Data);
      }
      else // if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT))
      {
//       if(strstr(cmd_str, "AcroRd32"))  // AcroRead 5.0
         {
/* C:\My Documents\Adobe\Acrobat\ */
/* C:\WINNT\Profiles\tadas\Personal\Adobe\Acrobat\ */
/* C:\Documents and Settings\tadas\My Documents\Adobe\Acrobat\ */
            retc=GetLocalPath(lpszTMGrpPrmFNamBuf, KP_My_Documents);
         }
      }
   }

   KP_ASSERT(strlen(lpszTMGrpPrmFNamBuf) + strlen(JS_SUB_PATH_1) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcat(lpszTMGrpPrmFNamBuf, JS_SUB_PATH_1);

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT))
   {
      KP_ASSERT(strlen(lpszTMGrpPrmFNamBuf) + strlen(JS_SUB_PATH_2_60) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcat(lpszTMGrpPrmFNamBuf, JS_SUB_PATH_2_60);
   }

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT))
   {
      KP_ASSERT(strlen(lpszTMGrpPrmFNamBuf) + strlen(JS_SUB_PATH_2_70) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcat(lpszTMGrpPrmFNamBuf, JS_SUB_PATH_2_70);
   }

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD80_PATHNAME) || strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT))
   {
      KP_ASSERT(strlen(lpszTMGrpPrmFNamBuf) + strlen(JS_SUB_PATH_2_80) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc)) strcat(lpszTMGrpPrmFNamBuf, JS_SUB_PATH_2_80);
   }

   KP_ASSERT(strlen(lpszTMGrpPrmFNamBuf) + strlen(TMGrpPrm_FNAME) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc)) strcat(lpszTMGrpPrmFNamBuf, TMGrpPrm_FNAME);

return(retc);
}


HRESULT KpStApp::UpdateTMGrpPrm(void)
{
HRESULT retc=S_OK;
static unsigned char tm_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char tm_sav_fname[KP_MAX_FNAME_LEN + 4 + 1];
FILE *tm_file = NULL;
unsigned char *tm_file_contents = NULL;
long tm_file_len;
FILE *tm_sav_file = NULL;

   if(SUCCEEDED(retc)) retc = GetTMGrpPrmFName(tm_fname);
   if(SUCCEEDED(retc))
   {
      strcpy(tm_sav_fname, tm_fname);
      strcat(tm_sav_fname, SAV_FILE_TYPE);
   }

   if(SUCCEEDED(retc)) retc = CreatePath(tm_fname, True);

// ---------------- saugojam senà TMGrpPrm.sav
   if(SUCCEEDED(retc))
   {
// ar yra TMGrpPrm.sav? jei ne - nieko nedarom
      tm_file = fopen((const char *)tm_fname, "r");
      if(tm_file != NULL)
      {
         fclose(tm_file);
         tm_file = NULL;

         tm_file_contents = NULL;
         if(SUCCEEDED(ReadFileContents(tm_fname, &tm_file_contents, &tm_file_len, False, True)))
         {
// tikrinam, ar jau yra TMGrpPrm.sav.sav
            tm_sav_file = fopen((const char *)tm_sav_fname, "r");
            if(tm_sav_file != NULL)
            {
// yra, nieko nedarom
               fclose(tm_sav_file);
               tm_sav_file = NULL;
            }
            else
            {
// TMGrpPrm.sav.sav dar nëra, kopijuojam TMGrpPrm.sav i TMGrpPrm.sav.sav
// !!!! TODO paprasèiau naudoti CopyFile()
               tm_sav_file = fopen((const char *)tm_sav_fname, "wb");
               KP_ASSERT(tm_sav_file, KP_E_DIR_ERROR, GetLastError(), False);

               if(SUCCEEDED(retc))
               {
                  fwrite(tm_file_contents, tm_file_len, 1, tm_sav_file);
                  KP_ASSERT((!ferror(tm_sav_file)) && (!feof(tm_sav_file)), KP_E_FERROR, null, False);
                  KP_ASSERT(!fclose(tm_sav_file), KP_E_DIR_ERROR, GetLastError(), False);
                  tm_sav_file = NULL;
               }

            } // else // if(tm_sav_file != NULL)

         } // if(SUCCEEDED(ReadFileContents(tm_fname, &tm_file_contents, &tm_file_len, False, True))

         KP_DELETEA(tm_file_contents);

      } // if(tm_file != NULL)

   } // if(SUCCEEDED(retc))

// ---------------- áraðom naujà TMGrpPrm.sav
   if(SUCCEEDED(retc))
   {
      tm_file = fopen((const char *)tm_fname, "wb");
      KP_ASSERT(tm_file, KP_E_DIR_ERROR, GetLastError(), False);
   }

   if(SUCCEEDED(retc))
   {
      fwrite(TMGrpPrm, TMGrpPrm_FILE_SIZE, 1, tm_file);
      KP_ASSERT((!ferror(tm_file)) && (!feof(tm_file)), KP_E_FERROR, null, False);
      KP_ASSERT(!fclose(tm_file), KP_E_DIR_ERROR, GetLastError(), False);
      tm_file = NULL;
   }

return(retc);
}


HRESULT KpStApp::RestoreTMGrpPrm(void)
{
HRESULT retc=S_OK;
static unsigned char tm_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char tm_sav_fname[KP_MAX_FNAME_LEN + 4 + 1];
unsigned char *tm_sav_file_contents = NULL;
long tm_sav_file_len;
FILE *tm_file = NULL;

   if(SUCCEEDED(retc)) retc = GetTMGrpPrmFName(tm_fname);
   if(SUCCEEDED(retc))
   {
      strcpy(tm_sav_fname, tm_fname);
      strcat(tm_sav_fname, SAV_FILE_TYPE);
   }

   if(SUCCEEDED(retc)) retc = CreatePath(tm_fname, True);

   if(SUCCEEDED(retc))
   {
      tm_sav_file_contents = NULL;
      if(SUCCEEDED(ReadFileContents(tm_sav_fname, &tm_sav_file_contents, &tm_sav_file_len, False, True)))
      {
// kopijuojam TMGrpPrm.sav.sav atgal á TMGrpPrm.sav
// !!!! TODO paprasèiau naudoti CopyFile()
         tm_file = fopen((const char *)tm_fname, "wb");
         KP_ASSERT(tm_file, KP_E_DIR_ERROR, GetLastError(), False);

         if(SUCCEEDED(retc))
         {
            fwrite(tm_sav_file_contents, tm_sav_file_len, 1, tm_file);
            KP_ASSERT((!ferror(tm_file)) && (!feof(tm_file)), KP_E_FERROR, null, False);
            KP_ASSERT(!fclose(tm_file), KP_E_DIR_ERROR, GetLastError(), False);
            tm_file = NULL;
         }

// trinam TMGrpPrm.sav.sav
         KP_ASSERT(DeleteFile((const char *)tm_sav_fname), KP_E_DIR_ERROR, GetLastError(), False);

      } // if(SUCCEEDED(ReadFileContents(tm_sav_fname, &tm_sav_file_contents, &tm_sav_file_len, False, True)))

      KP_DELETEA(tm_sav_file_contents);

   } // if(SUCCEEDED(retc))


return(retc);
}


// -------------------------------------------
HRESULT KpStApp::TestSound(void)
{
HRESULT retc = S_OK;
// DWORD volume;
static unsigned char prol_fname[KP_MAX_FNAME_LEN + 1];

   if(SUCCEEDED(retc)) retc = GetIniProlFName(prol_fname);

   m_iNumWaveDevs = waveOutGetNumDevs();

   if((m_iNumWaveDevs > 0) && SUCCEEDED(retc))
   {
#if FALSE
      if(MMSYSERR_NOERROR == waveOutGetVolume(0, &volume))
      {
         m_lInitVolume = m_lCurVolume = volume;
      }
      else KP_WARNING(KP_E_SYSTEM_ERROR, null);
#else
      m_lInitVolume = m_lCurVolume = 0xFFFFFFFF;

      if(SUCCEEDED(retc)) if(IsSoundFileProcessed(prol_fname))
         if(MMSYSERR_NOERROR != waveOutSetVolume(0, m_lInitVolume))
            KP_WARNING(KP_E_SYSTEM_ERROR, null);
#endif
   }

   retc = SetPdfPar(JS_WAVE_DEVS_PAR_NAME, m_iNumWaveDevs);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::FadeSound(int iPerCent)
{
HRESULT retc=S_OK;
DWORD left;
DWORD right;

   if(m_bSoundPlaying && SUCCEEDED(retc))
   {
      left = LOWORD(m_lCurVolume);
      right = HIWORD(m_lCurVolume);

      left = left * iPerCent / 100;
      right = right * iPerCent / 100;

      if((left < 0xFF) && (right < 0xFF)) retc = StopSound();
      else
      {
         m_lCurVolume = (left | (right << 16));

         if(MMSYSERR_NOERROR != waveOutSetVolume(0, m_lCurVolume))
            KP_WARNING(KP_E_SYSTEM_ERROR, null);
      }
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::DoMute(void)
{
HRESULT retc=S_OK;
static unsigned char prol_fname[KP_MAX_FNAME_LEN + 1];

   if(SUCCEEDED(retc)) retc = GetIniProlFName(prol_fname);

   while(m_bSoundPlaying && SUCCEEDED(retc))
   {
      retc = FadeSound(50);
      retc = KpSleep(50);
   }

   if(m_lProlThreadId && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc))
      {
         retc = CloseProcess(prol_fname, m_lProlThreadId);
         m_lProlThreadId = 0L;
      }
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetFlashIniFname(unsigned char *lpszIniFName)
{
HRESULT retc = S_OK;
static unsigned char ini_disk[KP_MAX_FNAME_LEN + 1];
static unsigned char ini_path[KP_MAX_FNAME_LEN + 1];
static unsigned char ini_name[KP_MAX_FNAME_LEN + 1];
static unsigned char ini_type[KP_MAX_FTYPE_LEN + 1];

   KP_ASSERT(lpszIniFName != null, E_INVALIDARG, null, True);

// ieðkom atmintuko su .ini failu su einamuoju vardu, pakeliui bus perskaitytas atmintuko .ini ir uþpildytas m_Ini
// viskas jau turëtø bût patikrinta
// if(SUCCEEDED(retc)) retc = theKpStAppPtr->TestFlash();

   if(SUCCEEDED(retc)) retc = TvFnameSplit(ini_disk, ini_path, ini_name, ini_type, m_lpszIniFName);
   KP_ASSERT(strlen(m_lpszFlashDevName) + 1 + strlen(ini_name) + 1 + strlen(ini_type) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);
   if(SUCCEEDED(retc))
   {
      strcpy(lpszIniFName, m_lpszFlashDevName);
      strcat(lpszIniFName, "\\");
      strcat(lpszIniFName, ini_name);
      strcat(lpszIniFName, ".");
      strcat(lpszIniFName, ini_type);
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SwitchMute(void)
{
HRESULT retc = S_OK;
bool bound;
bool muted;
static unsigned char prol_fname[KP_MAX_FNAME_LEN + 1];
static unsigned char ini_fname[KP_MAX_FNAME_LEN + 1];
KpWnd *mute_wnd;
HBITMAP bmp_tmp;

   if(SUCCEEDED(retc)) retc = GetIniProlFName(prol_fname);

// ar pririðtas prie atmintuko
   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&bound);

   if(SUCCEEDED(retc))
   {
      if(bound)
      {
         retc = GetFlashIniFname(ini_fname);

// invertuojam muted
         if(SUCCEEDED(retc)) retc = GetIniSoundMuted(&muted);
         if(SUCCEEDED(retc)) retc = SetIniSoundMuted(!muted);

// raðom atmintuko .ini atgal
         if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIniFile(ini_fname);

// keièiam mygtuko paveiksliukà
         KP_ASSERT(m_hMuteButton, KP_E_SYSTEM_ERROR, null, True);
         if(SUCCEEDED(retc)) retc = GetCurWindow(&mute_wnd, m_hMuteButton);
         KP_ASSERT(mute_wnd, KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(mute_wnd->m_iWndType == TYP_Button, KP_E_SYSTEM_ERROR, null, True);
#if FALSE
         KP_ASSERT(mute_wnd->m_phBmpList[0], KP_E_SYSTEM_ERROR, null, True);
         KP_ASSERT(DeleteObject(mute_wnd->m_phBmpList[0]), KP_E_SYSTEM_ERROR, GetLastError(), False);
         if(SUCCEEDED(retc)) mute_wnd->m_phBmpList[0] = LoadBitmap(hKpInstance, MAKEINTRESOURCE(muted?KP_IDI_MUTE_BMP:KP_IDI_MUTED_BMP));
         KP_ASSERT(mute_wnd->m_phBmpList[0], KP_E_FILE_NOT_FOUND, GetLastError(), True);
#else
         if(SUCCEEDED(retc))
         {
            bmp_tmp = mute_wnd->m_phBmpList[0];
            mute_wnd->m_phBmpList[0] = mute_wnd->m_phBmpList[1];
            mute_wnd->m_phBmpList[1] = bmp_tmp;
         }
#endif
         if(SUCCEEDED(retc))
            SendMessage(m_hMuteButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)mute_wnd->m_phBmpList[0]);

         if(SUCCEEDED(retc))
         {
            if(muted)
            {
               if(IsSoundFileProcessed(prol_fname))
               {
                  if(m_iNumWaveDevs > 0)
                  {
                     KP_ASSERT(m_lProlThreadId == 0L, KP_E_SYSTEM_ERROR, null, True);
                     if(SUCCEEDED(retc))
                     {
                        m_bSoundPlaying = True;
                        retc = StartCmdProcess(prol_fname, KPST_CUR_DIR, &m_lProlThreadId, NULL, False, SW_SHOWNORMAL /* SW_SHOWDEFAULT */);
                     }
                  }
               }

            } // if(muted)
            else
               retc = DoMute();
         }

      } // if(bound)
      else
         retc = DoMute();
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::StopSound(void)
{
HRESULT retc=S_OK;
static unsigned char prol_fname[KP_MAX_FNAME_LEN + 1];

   m_lCurVolume = m_lInitVolume;

   if(m_iNumWaveDevs > 0)
   {
      if(SUCCEEDED(retc)) retc = GetIniProlFName(prol_fname);

      if(SUCCEEDED(retc)) if(IsSoundFileProcessed(prol_fname))
         PlaySound(NULL, NULL, 0);

      if(MMSYSERR_NOERROR != waveOutSetVolume(0, m_lInitVolume))
         KP_WARNING(KP_E_SYSTEM_ERROR, null);
   }

   m_bSoundPlaying = False;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::InitTestPar(void)
{
HRESULT retc=S_OK;
static unsigned char rez_fname[KP_MAX_FNAME_LEN+1];

   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);

   if(SUCCEEDED(retc)) if(strlen(rez_fname) > 0)
   {
      retc = SetPdfPar(JS_TEST_PAR_NAME, 12348765);
      if(SUCCEEDED(retc)) retc=SetPdfPar(JS_DATA_READY_PAR_NAME, (const unsigned char *)"No");
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SetRezSrvData(void)
{
HRESULT retc = S_OK;
static unsigned char reg_url[KP_MAX_FNAME_LEN + 1];
// int prod_ver=0;
int port=0;
unsigned char srv_adr[KP_MAX_FNAME_LEN + 1 + MAX_LONG_DIGITS + 1];
   srv_adr[0]=Nul;
int num_of_lics=0;
bool bound=False;

   if(SUCCEEDED(retc)) retc = GetIniRegURL(reg_url);
// if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);
   if(SUCCEEDED(retc)) retc = GetIniNumOfLics(&num_of_lics); if(num_of_lics<0) num_of_lics = 0;
   if(SUCCEEDED(retc)) retc = GetIniBound(&bound);
   if((num_of_lics || (!bound)) && SUCCEEDED(retc))
   {
      retc = GetServerPort(&port);

// ieðkom rezultatø/licencijø serverio – siunciam broadcastà
      if(SUCCEEDED(retc)) /* retc = */ RetrieveLicServer(reg_url, KP_MAX_FNAME_LEN, port);

      if(SUCCEEDED(retc)) sprintf((char *)srv_adr, "%s:%d", reg_url, port);
   }

   if(SUCCEEDED(retc)) retc = SetPdfPar(JS_SRV_ADR_PAR_NAME, srv_adr);
// if(SUCCEEDED(retc)) retc = SetPdfPar(JS_PROD_VER_PAR_NAME, prod_ver);
// if(SUCCEEDED(retc)) retc = SetPdfPar(JS_SRV_PORT_PAR_NAME, port);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SetAppPathPar(void)
{
HRESULT retc=S_OK;
static unsigned char dir_buf[KP_MAX_FNAME_LEN+1];

   if(SUCCEEDED(retc)) retc = GetAppPath(dir_buf, False);

   if(SUCCEEDED(retc)) retc = SetPdfPathPar(JS_PROG_PATH_PAR_NAME, dir_buf);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetGlobalJsName(unsigned char *lpszGlobJsFNamBuf, unsigned char *lpszJsPathBuf)
{
HRESULT retc=S_OK;
#if FALSE // #ifdef Logging // Debug
char str_buf[KP_MAX_FNAME_LEN+100];
#endif
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];

// ---------------------------------
   if((lpszGlobJsFNamBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// -------------------------
   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc))
   {
      lpszGlobJsFNamBuf[0]=Nul;

      if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) ||
         strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT) ||
         strstr(cmd_str, KPST_ACROREAD80_PATHNAME) || strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT) ||
         strstr(cmd_str, KPST_ACROREAD90_PATHNAME) || strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT))
      {
/* C:\My Documents\Adobe\Acrobat\6.0\JavaScripts\ ???  */
/* C:\WINNT\Profiles\tadas\Personal\Adobe\Acrobat\6.0\JavaScripts\ ???  */
/* C:\Documents and Settings\tadas\Application Data\Adobe\Acrobat\6.0\JavaScripts\  */
         retc=GetLocalPath(lpszGlobJsFNamBuf, KP_Application_Data);
      }
      else // if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT))
      {
//       if(strstr(cmd_str, "AcroRd32"))  // AcroRead 5.0
         {
/* C:\My Documents\Adobe\Acrobat\JavaScripts\  */
/* C:\WINNT\Profiles\tadas\Personal\Adobe\Acrobat\JavaScripts\   ??? */
/* C:\Documents and Settings\tadas\My Documents\Adobe\\Acrobat\\JavaScripts\\  */
            retc=GetLocalPath(lpszGlobJsFNamBuf, KP_My_Documents);
         }
      }
   }

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszGlobJsFNamBuf)+strlen(JS_SUB_PATH_1)<KP_MAX_FNAME_LEN)
         strcat(lpszGlobJsFNamBuf, JS_SUB_PATH_1);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME) || strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT))
   {
      if(strlen(lpszGlobJsFNamBuf)+strlen(JS_SUB_PATH_2_60)<KP_MAX_FNAME_LEN)
         strcat(lpszGlobJsFNamBuf, JS_SUB_PATH_2_60);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD70_PATHNAME) || strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT))
   {
      if(strlen(lpszGlobJsFNamBuf)+strlen(JS_SUB_PATH_2_70)<KP_MAX_FNAME_LEN)
         strcat(lpszGlobJsFNamBuf, JS_SUB_PATH_2_70);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD80_PATHNAME) || strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT))
   {
      if(strlen(lpszGlobJsFNamBuf)+strlen(JS_SUB_PATH_2_80)<KP_MAX_FNAME_LEN)
         strcat(lpszGlobJsFNamBuf, JS_SUB_PATH_2_80);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD90_PATHNAME) || strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT))
   {
      if(strlen(lpszGlobJsFNamBuf)+strlen(JS_SUB_PATH_2_90)<KP_MAX_FNAME_LEN)
         strcat(lpszGlobJsFNamBuf, JS_SUB_PATH_2_90);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszGlobJsFNamBuf) + strlen(JS_SUB_PATH_3) < KP_MAX_FNAME_LEN)
         strcat(lpszGlobJsFNamBuf, JS_SUB_PATH_3);
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);

#if FALSE // #ifdef Logging // Debug
sprintf(str_buf, "### 4.2.1.6 Glob.js path: %s", lpszGlobJsFNamBuf);
KP_TRACE(str_buf);
#ifdef DebugStop
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

#if FALSE // #ifdef Logging // Debug
KP_TRACE("---------------");

sprintf(str_buf, "dir \"%s\" > c:\\arkim\\rezultatai\\java.dir", lpszGlobJsFNamBuf);
KP_TRACE(str_buf);
system(str_buf);
KpSleep(500, HWND_DESKTOP); // Sleep(500);

strcpy(str_buf, "dir c:\\arkim /S > c:\\arkim\\rezultatai\\arkim.dir");
KP_TRACE(str_buf);
system(str_buf);
KpSleep(500, HWND_DESKTOP); // Sleep(500);
#endif
   }

   if(lpszJsPathBuf && SUCCEEDED(retc)) strcpy(lpszJsPathBuf, lpszGlobJsFNamBuf);

   if(SUCCEEDED(retc))
   {
      if(strlen(lpszGlobJsFNamBuf) + 1 + strlen(GLOB_JS_FILE_NAME)<KP_MAX_FNAME_LEN)
      {
         strcat(lpszGlobJsFNamBuf, "\\");
         strcat(lpszGlobJsFNamBuf, GLOB_JS_FILE_NAME);
      }
      else
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   }


#if FALSE // #ifdef Logging // Debug
sprintf(str_buf, "copy \"%s\" c:\\arkim\\rezultatai\\*.*", lpszGlobJsFNamBuf);
KP_TRACE(str_buf);
system(str_buf);
KpSleep(500, HWND_DESKTOP); // Sleep(500);

KP_TRACE("---------------");
#endif

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SetPdfPar(const unsigned char *lpszParName, const unsigned char *lpszValue, const unsigned char *lpszPrefix, const unsigned char *lpszTail)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
unsigned char js_fname[KP_MAX_FNAME_LEN + 1];
unsigned char par_pref[KP_MAX_FILE_LIN_WDT + 1];
unsigned char par_pref_short[TV_TAG_LEN + 1];
unsigned char par_tail[TV_TAG_LEN + 1];
unsigned char *contents_ptr;
FILE *out_file;
unsigned char *pntd = NULL;
unsigned char *pntr = NULL;
int retv;
long ll;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];

// KP_TRACE("SetPdfPar()");
// KpMsgOutF_2("SetPdfPar() %s %s", lpszParName, lpszValue?lpszValue:(const unsigned char *)"<null>");

// ----------------
   if(SUCCEEDED(retc)) retc=GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc)) // if(strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT))
   {
      strlwr(cmd_str);
      if((strstr(cmd_str, KPST_PDF_FILE_TYPE) != NULL) || (strstr(cmd_str, KPST_TEV_OBJ_FILE_TYPE) != NULL))
      {
         if((lpszParName == NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

         if(SUCCEEDED(retc))
            if(strlen(lpszPrefix) + strlen(lpszParName) > TV_TAG_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
            sprintf((char *)par_pref_short, (const char *)lpszPrefix, lpszParName);

         if(SUCCEEDED(retc))
            if(strlen(JS_PAR_PREF) + strlen(par_pref_short) > KP_MAX_FILE_LIN_WDT)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            strcpy(par_pref, JS_PAR_PREF);
            strcat(par_pref, par_pref_short);
         }

         if(SUCCEEDED(retc))
            if(strlen(lpszTail)+strlen(JS_PAR_TAIL) > TV_TAG_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            strcpy(par_tail, lpszTail);
            strcat(par_tail, JS_PAR_TAIL);
         }

// ----------------- get glob.js file name
         if(SUCCEEDED(retc)) retc = GetGlobalJsName(js_fname);
// PutLogMessage_("SetPdfPar() %s", js_fname);

// ----------------- read glob.js file
         contents_ptr = NULL;
         if(SUCCEEDED(retc))
         {
            retc = ReadFileContents(js_fname, &contents_ptr, &ll, False, False);
            if(retc == KP_E_FILE_NOT_FOUND)
            {
               if(contents_ptr != NULL)
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               contents_ptr = NULL;
               retc = S_OK;
            }
         }

         if((contents_ptr == NULL) && SUCCEEDED(retc))
         {
            KP_NEWA(contents_ptr, unsigned char, strlen(par_pref) + 1 + strlen(lpszTail) + strlen(JS_PAR_TAIL) + 100);

            if(SUCCEEDED(retc))
            {
               strcpy(contents_ptr, par_pref);
               strcat(contents_ptr, "0");
               strcat(contents_ptr, par_tail);
               strcat(contents_ptr, "\n");
            }
         }

// ----------------- write glob.js file
         out_file=NULL;

         if(SUCCEEDED(retc))
         {
// KpMsgOutF_2("SetPdfPar() par_pref_short: %s contents_ptr: %s", par_pref_short, contents_ptr);

            pntd = strstr(contents_ptr, par_pref);
            if(pntd != NULL)
            {
               pntr = pntd + strlen(par_pref);
               if(lpszValue != null) pntd = pntr;

               pntr = strstr(pntr, par_tail);
               if(pntr == NULL)
               {
                  retc = KP_E_FILE_FORMAT;
                  KpErrorProc.OutputErrorMessage(retc, null, False, __FILE__, __LINE__, 0L);
               }
               else if(lpszValue == null)
               {
                  pntr += strlen(par_tail);
                  if(*pntr == Cr) pntr++;
                  if(*pntr == Lf) pntr++;
               }

// KpMsgOutF_2("SetPdfPar() pntd: %s pntr: %s", pntd, pntr?pntr:(const unsigned char *)"<null>");

               *(pntd++)=Nul;
            }

// -------------
            if(SUCCEEDED(retc)) retc=CreatePath(js_fname, True);

            if(SUCCEEDED(retc))
            {
               out_file = fopen((const char *)js_fname, "w");
               if(out_file == NULL)
               {
                  retv = GetLastError();
                  retc = KP_E_DIR_ERROR;
						KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, js_fname, False /* True */, __FILE__, __LINE__, 0L); // Elvyrai Dainauskienei neleidþia – gal Acrobatas jau atidaræs?
               }
            }

            if(SUCCEEDED(retc))
            {
               fputs((const char *)contents_ptr, out_file);
               if(ferror(out_file) || feof(out_file))
               {
                  retv=GetLastError();
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, js_fname, True, __FILE__, __LINE__, 0L);
               }
            }

            if((lpszValue != null) && SUCCEEDED(retc))
            {
               if((pntd == NULL) && SUCCEEDED(retc))
               {
                  if((lpszValue != null) && SUCCEEDED(retc))
                  {
                     fputs((const char *)par_pref, out_file);
                     if(ferror(out_file) || feof(out_file))
                     {
                        retv=GetLastError();
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, js_fname, True, __FILE__, __LINE__, 0L);
                     }
                  }
               }

               fprintf(out_file, "%s", lpszValue);
               if(ferror(out_file) || feof(out_file))
               {
                  retv=GetLastError();
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, js_fname, True, __FILE__, __LINE__, 0L);
               }
            }

            if(SUCCEEDED(retc))
            {
               if(pntr != NULL)
               {
                  if(lpszValue != null) *pntr = par_tail[0];   // jei duomenys buvo tuscia eilute, tai pirmas uodegos
                                                               //    baitas isvalytas - atstatom
                  fputs((const char *)pntr, out_file);
                  if(ferror(out_file) || feof(out_file))
                  {
                     retv=GetLastError();
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, js_fname, True, __FILE__, __LINE__, 0L);
                  }
               }
               else if(lpszValue != null)
               {
                  fputs((const char *)par_tail, out_file);
                  fputs("\n", out_file);
                  if(ferror(out_file) || feof(out_file))
                  {
                     retv=GetLastError();
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, js_fname, True, __FILE__, __LINE__, 0L);
                  }

               } // else // if(pntr!=NULL)

            } // if(SUCCEEDED(retc))

// ----------
            if(out_file!=NULL)
            {
               if(fclose(out_file))
               {
                  retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L);
                  if(SUCCEEDED(retc)) retc=retc0;
               }
            }
            out_file=NULL;
         }

// ----------------
         KP_DELETEA(contents_ptr);

         if((retc == KP_E_FILE_FORMAT) || (retc == KP_E_DIR_ERROR) || (retc == KP_E_FERROR))
            retc = S_OK;

      } // if(strstr(cmd_str, KPST_PDF_FILE_TYPE)!=NULL)

   } // if(SUCCEEDED(retc))

return(retc);
}


HRESULT KpStApp::SetPdfPar(const unsigned char *lpszParName, const unsigned char *lpszValue)
{
return(SetPdfPar(lpszParName, lpszValue, JS_STR_PAR_PREF_SHORT, JS_STR_PAR_TAIL_SHORT));
}


HRESULT KpStApp::SetPdfPar(const unsigned char *lpszParName, int iValue)
{
HRESULT retc=S_OK;
unsigned char val_buf[MAX_LONG_DIGITS+1];

   sprintf((char *)val_buf, "%d", iValue);
   retc=SetPdfPar(lpszParName, val_buf, JS_NUM_PAR_PREF_SHORT, JS_NUM_PAR_TAIL_SHORT);

return(retc);
}


HRESULT KpStApp::SetPdfPathPar(const unsigned char *lpszParName, const unsigned char *lpszPathValue)
{
HRESULT retc=S_OK;
static unsigned char out_buf[KP_MAX_FNAME_LEN + 100];

   KP_ASSERT(lpszPathValue, E_INVALIDARG, null, True);
   KP_ASSERT(strlen(lpszPathValue) < KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, null, True);

   if(SUCCEEDED(retc)) retc = EncodePdfPath(out_buf, lpszPathValue);

   if(SUCCEEDED(retc)) retc = SetPdfPar(lpszParName, out_buf);

return(retc);
}


// -----------------------------------
HRESULT KpStApp::DecodePostMsg(unsigned char *lpszOutBuf, const unsigned char *lpszInStr, bool bCleanPluses)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;
int in_ch;

   if(((lpszOutBuf==NULL) || (lpszInStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// -------------------------------------- perkoduojam %xx á ðeðioliktainá kodà
   if(SUCCEEDED(retc))
   {
      pntd=lpszOutBuf;
      pnts=lpszInStr;

      while(*pnts && SUCCEEDED(retc))
      {
         if(*pnts=='%')
         {
            pnts++;
            if(sscanf((const char *)pnts, "%2x", &in_ch)<1)
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);
            if((in_ch>Maxuchar) && SUCCEEDED(retc))
               /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_MSG_FORMAT, null, False, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               *pntd++ = in_ch;
               pnts += 2;
            }
         }
         else if((*pnts=='+') && bCleanPluses) { *pntd++ = Spc; pnts++; } // ' '
         else *pntd++ = *pnts++;
      }
   }
   if(SUCCEEDED(retc)) *pntd=Nul;


return(retc);
}


// -----------------------------------
HRESULT KpStApp::EncodePostMsg(unsigned char *lpszOutBuf, const unsigned char *lpszInStr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;

   if(((lpszOutBuf==NULL) || (lpszInStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntd=lpszOutBuf;
      pnts=lpszInStr;

      while(*pnts && SUCCEEDED(retc))
      {

// PI=73R2-LL54-3UUR-1UJ3  722G-89UU-LLA7-LR8E  0  [dBI+9,+B]:1505+*,=*/,BZ/;)190*+B   0  0  1  33650 RRqlniqQk   ]:1505+*,=*/,  32 0  2  6  0     6000  0&ProdVer=2010&ProdVar=7
// PI=73R2-LL54-3UUR-1UJ3\t722G-89UU-LLA7-LR8E\t0\t[dBI+9,+B]:1505+*,=*/,BZ/;)190*+B\t0\t0\t1\t33650\tRRqlniqQk\t]:1505+*,=*/,\t32\t0\t2\t6\t0\t\t6000\t0&ProdVer=2010&ProdVar=1
// PI=73R2-LL54-3UUR-1UJ3%09722G-89UU-LLA7-LR8E%090%09%5bdBI%2b9%2c%2bB%5d%3a1505%2b*%2c%3d*%2f%2cBZ%2f%3b%29190*%2bB%090%090%091%0933650%09RRqlniqQk%09%5d%3a1505%2b*%2c%3d*%2f%2c%0932%090%092%096%090%09%096000%090&ProdVer=2010&ProdVar=9

         if((*pnts <= Spc) || (strchr(lpszPostSpChars, *pnts)!=NULL))
         {
            *pntd++ = '%';
            sprintf((char *)pntd, "%02x", *pnts++);
            pntd += 2;
         }
         else if(*pnts == Spc) { *pntd++ = '+'; pnts++; } // ' '
         else *pntd++ = *pnts++;
      }
   }
   if(SUCCEEDED(retc)) *pntd=Nul;


return(retc);
}


// -----------------------------------
HRESULT KpStApp::DecodePdfParText(unsigned char *lpszOutBuf, const unsigned char *lpszInStr)
{
HRESULT retc=S_OK;
const unsigned char *pnts;
unsigned char *pntd;
unsigned char *pnte;
unsigned char out_ch;
int uni_ch;
int jj;
KpChar in_ch;
unsigned char str_buf[100];

   if(((lpszOutBuf==NULL) || (lpszInStr==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      pntd=lpszOutBuf;
      pnts=lpszInStr;

      while((*pnts) && SUCCEEDED(retc))
      {
         switch(*pnts)
         {
         case '\\':
            out_ch='?';
            pnts++;
            if((*pnts++)=='\\')
            {
               switch(*pnts++)
               {
                  case 'u':
                     uni_ch=C_Nul;
                     pnte=str_buf;
                     for(jj=0; jj<4; jj++) *(pnte++)=(*pnts++);
                     *pnte=Nul;
                     sscanf((char *)str_buf, "%x", &uni_ch);

                     in_ch=(KpChar)'?';
                     if(uni_ch)
                        for(jj=0; jj<C_CharSize0; jj++)
                        {
                           if(iaUniChars[jj]==uni_ch)
                           {
                              in_ch=(KpChar)jj;
                              break;
                           }
                        }

                     out_ch='?';
                     if(FAILED(KptCharDecode(&out_ch, in_ch, 71)))
                        out_ch='?';
                     break;

                  case 'x':
                     out_ch='?';
                     pnte=str_buf;
                     for(jj=0; jj<2; jj++) *(pnte++)=(*pnts++);
                     *pnte=Nul;
                     sscanf((char *)str_buf, "%x", &out_ch);
                     if(out_ch==Nul) out_ch='?';
                     switch(out_ch)
                     {
                        case 0xA5: out_ch=0xC0; break; // C_A_Ogon 79 --> 71
                        case 0xB9: out_ch=0xE0; break; // C_a_Ogon 79 --> 71
//                      case 0xC8: out_ch=0xC8; break; // C_C_Car  79, 71 --> 71
//                      case 0xE8: out_ch=0xE8; break; // C_c_Car  79, 71 --> 71
                        case 0xCA: out_ch=0xC6; break; // C_E_Ogon 79 --> 71
                        case 0xEA: out_ch=0xE6; break; // C_e_Ogon 79 --> 71
                        case 0x8A: out_ch=0xD0; break; // C_S_Car 79, 74 --> 71
                        case 0x9A: out_ch=0xF0; break; // C_s_Car 79, 74 --> 71
                        case 0x8E: out_ch=0xDE; break; // C_Z_Car 79, 74 --> 71
                        case 0x9E: out_ch=0xFE; break; // C_z_Car 79, 74 --> 71
                     }
                     break;

                  case '\\':
                     if((*pnts++)=='\"') out_ch='\"';
                     else
                        retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                     break;

                  default:
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
                     break;
               }
               *(pntd++)=out_ch;
            }
            break;

         case '|':
            pnts++;
            *(pntd++)=Tab;
            break;

         default:
            *(pntd++)=(*pnts++);
            break;

         } // switch(*pnts)

      } // while(*pnts)

      *pntd=Nul;

   } // if(SUCCEEDED(retc))

return(retc);
}


// -----------------------------------
HRESULT KpStApp::EncodePdfParText(unsigned char *lpszOutBuf, const unsigned char *lpszInStr, int iOutBufLen)
{
HRESULT retc = S_OK;
const unsigned char *pnts;
unsigned char *pntd;
int ll;
KpChar kp_char;
unsigned char str_buf[100];

   KP_ASSERT(lpszOutBuf, E_INVALIDARG, null, True);
   KP_ASSERT(lpszInStr, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pntd = lpszOutBuf;
      pnts = lpszInStr;

      while((*pnts) && SUCCEEDED(retc))
      {
         if(*pnts >= KPT_FirstKptChar)
         {
            retc = KptCharEncode(&kp_char, *pnts, 71);
            if(FAILED(retc)) KP_ERROR(retc, null);

            KP_ASSERT(iaUniChars[kp_char], KP_E_UNKN_CHR, null, True);
            if(SUCCEEDED(retc)) sprintf((char *)str_buf, "\\\\u%04x", iaUniChars[kp_char]);

            if(SUCCEEDED(retc)) ll = strlen(str_buf);
            KP_ASSERT(((pntd + ll) - lpszOutBuf) < iOutBufLen, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc)){ strcpy(pntd, str_buf); pntd += ll; }
         }
         else
         {
            KP_ASSERT(((pntd + 1) - lpszOutBuf) < iOutBufLen, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc)) *pntd++ = *pnts;
         }

         pnts++;

      } // while(*pnts)

      *pntd = Nul;

   } // if(SUCCEEDED(retc))

return(retc);
}


// -----------------------------------
// kaþkodël neveikia
HRESULT KpStApp::EncodePdfParText(KpString *psOutStr, /* const */ KpString sInStr)
{
HRESULT retc = S_OK;
const unsigned char *pnts;
KpChar kp_char;
unsigned char str_buf[100];

   KP_ASSERT(psOutStr, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = sInStr.ExtractUnsignedValueA();
      *psOutStr = "";

      while((*pnts) && SUCCEEDED(retc))
      {
         if(*pnts >= KPT_FirstKptChar)
         {
            retc = KptCharEncode(&kp_char, *pnts, 71);
            if(FAILED(retc)) KP_ERROR(retc, null);

            KP_ASSERT(iaUniChars[kp_char], KP_E_UNKN_CHR, null, True);
            if(SUCCEEDED(retc)) sprintf((char *)str_buf, "\\\\u%04x", iaUniChars[kp_char]);

//          *psOutStr = *psOutStr + (const char *)str_buf;
            *psOutStr += (const char *)str_buf;
// KpMsgOutF_0(psOutStr->ExtractUnsignedValueA());
         }
         else *psOutStr += *pnts;

         pnts++;

      } // while(*pnts)

   } // if(SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
// gal reikëtø ':' keist á '|'?
HRESULT KpStApp::EncodePdfPath(unsigned char *lpszPdfPathBuf, const unsigned char *lpszPath)
{
HRESULT retc=S_OK;
const unsigned char *pnts = null;
unsigned char *pntd = null;

   KP_ASSERT(lpszPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPdfPathBuf, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = lpszPath;
      pntd = lpszPdfPathBuf;
      *pntd++ = '/';
      while(*pnts)
      {
         if((*pnts == ':') && ((*(pnts+1) == '\\') || (*(pnts+1) == Nul)));
         else if((*pnts == '\\') || (*pnts == ':')) (*pntd++) = '/';
         else (*pntd++) = *pnts;

         pnts++;
      }
      *pntd = Nul;
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::DecodePdfPath(unsigned char *lpszPathBuf, const unsigned char *lpszPdfPath)
{
HRESULT retc=S_OK;
const unsigned char *pnts = null;
unsigned char *pntd = null;

   KP_ASSERT(lpszPdfPath, E_INVALIDARG, null, True);
   KP_ASSERT(lpszPathBuf, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      pnts = lpszPdfPath;
      pntd = lpszPathBuf;

// praleidþiam pirmà '/'
// /R|/Mano_MaTau6e/Bebras_TEO.tif
      if((strchr(pnts, '|') || (pnts[2] == '/')) && (*pnts == '/')) pnts++;

      while(*pnts)
      {
         switch(*pnts)
         {
         case '|': *pntd = ':'; break;
         case '/':
// /R/Mano_MaTau6e/Bebras_TEO.tif – Tadas su Rolandu '|' ðiaip ástato per jëgà, kartais gali ir neástatyti
//    arba Rolandas ástato ne á tà vietà:
// fi|le:\\\G\Mano_ZU\x\11-12.PDF
            if((pnts - lpszPdfPath == 2) && lpszPdfPath[0] == '/') *pntd++ = ':';
            *pntd = '\\';
            break;
         default: *pntd = *pnts; break;
         }

         pnts++;
         pntd++;
      }
      *pntd = Nul;
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetClipPars(unsigned char *lpszBuf, int iBufSize, bool *pbDataReady)
{
HRESULT retc=S_OK;

   if(((lpszBuf==NULL) || (pbDataReady==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      lpszBuf[0]=Nul;
      *pbDataReady=True;
   }

   if(SUCCEEDED(retc)) retc = GetClipboardText(m_hBitmapWindow, lpszBuf, iBufSize, False);
   if(FAILED(retc))
   {
      switch(retc)
      {
      case KP_E_OBJ_NOT_FOUND:
         *pbDataReady=False;
         retc=S_OK;
         lpszBuf[0]=Nul;
         break;
      case KP_E_BUFFER_OVERFLOW:
      /* retc= */ KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         retc=S_OK;
         lpszBuf[iBufSize]=Nul;
         break;
      default:
         *pbDataReady=False;
      /* retc= */ KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         retc=S_OK;
         lpszBuf[0]=Nul;
         break;
      }
   }

   if(SUCCEEDED(retc)) if(*pbDataReady) retc=DecodePdfParText(lpszBuf, lpszBuf);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetFilePars(unsigned char *lpszBuf, int iBufSize, bool *pbDataReady, LocalPaths iTxtFileLocation)
{
HRESULT retc=S_OK;
static unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
// static unsigned char rez_disk[KP_MAX_FNAME_LEN+1];
// static unsigned char rez_path[KP_MAX_FNAME_LEN+1];
// static unsigned char rez_name[KP_MAX_FNAME_LEN+1];
// static unsigned char rez_type[KP_MAX_FTYPE_LEN+1];
unsigned char *buf_ptr=NULL;
unsigned char *pntd=NULL;
long file_len=0L;

   if(((lpszBuf==NULL) || (pbDataReady==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc))
   {
      lpszBuf[0]=Nul;
      *pbDataReady=False;
   }

// if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
// if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);
// if(SUCCEEDED(retc)) retc = TvFnameSplit(rez_disk, rez_path, rez_name, rez_type, rez_fname);

   if(SUCCEEDED(retc)) retc=GetLocalPath(rez_fname, iTxtFileLocation); // KP_My_Documents

// if(SUCCEEDED(retc)) if(strlen(rez_fname)+strlen(rez_name)+strlen(".txt")>=KP_MAX_FNAME_LEN)
   if(SUCCEEDED(retc)) if(strlen(rez_fname)+strlen(KPST_REZ_FILE_NAME)>=KP_MAX_FNAME_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
//    strcat(rez_fname, rez_name);
//    strcat(rez_fname, ".txt");
      strcat(rez_fname, KPST_REZ_FILE_NAME);

      retc=ReadFileContents(rez_fname, &buf_ptr, &file_len, False, False);
      if(SUCCEEDED(retc))
      {
         if(buf_ptr==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if((iBufSize<file_len) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
         {
            pntd = strchr(buf_ptr, '\r'); if(pntd) *pntd = Nul;
            pntd = strchr(buf_ptr, '\n'); if(pntd) *pntd = Nul;

            strncpy(lpszBuf, buf_ptr, iBufSize);
            lpszBuf[file_len/*iBufSize*/]=Nul;

            *pbDataReady=True;

            retc=DecodePdfParText(lpszBuf, lpszBuf);
         }
      }
      if(retc==KP_E_FILE_NOT_FOUND) retc=S_OK;

      KP_DELETEA(buf_ptr);
   }

return(retc);
}


// ===========================================
// ið glob.js rezultatø jau nebeskaitom – kad senos ðiukðlës netrukdytø (pas Rolandà buvo kintamasis "klase")
// -----------------------------------
HRESULT KpStApp::ScanPdfParValue(const unsigned char *lpszParNam, unsigned char **plpszValBuf)
{
HRESULT retc=S_OK;
unsigned char *pnts;
unsigned char *pnte;
unsigned char str_buf[KP_MAX_FNAME_LEN+1];

   if(((lpszParNam==NULL) || (plpszValBuf==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) *plpszValBuf=NULL; // negalima - istrinsiu anksciau jau gal but surasta reiksme

   if(SUCCEEDED(retc))
      if(strlen(lpszParNam)+strlen(JS_STR_PAR_PREF_SHORT)>KP_MAX_FNAME_LEN)
         retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      sprintf((char *)str_buf, (const char *)JS_STR_PAR_PREF_SHORT, lpszParNam);
      pnts=strstr(m_StrBuf, str_buf);
      if(!pnts)
      {
         sprintf((char *)str_buf, (const char *)JS_NUM_PAR_PREF_SHORT, lpszParNam);
         pnts=strstr(m_StrBuf, str_buf);
      }
   }
   if(pnts && SUCCEEDED(retc))
   {
      pnts+=strlen(str_buf);
      pnte=strstr(pnts, JS_STR_PAR_TAIL_MID);
      if(!pnte) pnte=strstr(pnts, JS_NUM_PAR_TAIL_MID);
//    if(!pnte) pnte=strchr(pnts, JS_PAR_TAIL_1); // ')'
      if(!pnte)
         retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      if(SUCCEEDED(retc))
      {
         *pnte=Nul;
         if(strlen(pnts)>=KP_MAX_FILE_LIN_WDT)
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc))
         if(*plpszValBuf) // faile kelios eilutes su tuo paciu parametru
            retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, null, True, __FILE__, __LINE__, 0L);

      KP_NEWA(*plpszValBuf, unsigned char, strlen(pnts) + 1);

      if(SUCCEEDED(retc)) retc=DecodePdfParText(*plpszValBuf, pnts);

   } // if(pnts)

return(retc);
}


HRESULT KpStApp::GetPdfPars(unsigned char *lpszBuf, int iBufSize, const unsigned char **plpszaParNames, bool *pbDataReady)
{
HRESULT retc=S_OK;
HRESULT retc0=S_OK;
FILE *js_file=NULL;
unsigned char js_file_name[KP_MAX_FNAME_LEN+1];
const unsigned char **pntc;
bool endfl;
unsigned char **res_arr_ptr=NULL;
int res_cnt;
int ii;
unsigned char *data_ready_val=NULL;
int retv;
// bool kumul=False;
#ifdef Debug
#ifdef DebugStop
char str_buf[KP_MAX_FNAME_LEN+100];
#endif
#endif

   if(((lpszBuf==NULL) || (plpszaParNames==NULL) || (pbDataReady==NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

// if(SUCCEEDED(retc)) retc=GetIniKumul(&kumul);

   if(SUCCEEDED(retc))
   {
      lpszBuf[0]=Nul;
      *pbDataReady=False;
   }

// -------------------- suskaiciuoju parametru kieki ir isskiriu vietos rezultatams
   if(SUCCEEDED(retc))
   {
      res_cnt=0;
      pntc=plpszaParNames;
      if(pntc) while(*pntc++) res_cnt++;

      if(res_cnt==0)
         retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
   }

   KP_NEWA(res_arr_ptr, KpStrPtr, res_cnt);

   if(SUCCEEDED(retc))
      for(ii = 0; ii < res_cnt; ii++) res_arr_ptr[ii] = (unsigned char *)null;


// -----------------------------
#ifdef Debug
#ifdef DebugStop
sprintf(str_buf, "4.2.1 GetGlobalJsName res_cnt:%d", res_cnt);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc)) retc=GetGlobalJsName(js_file_name);


// ---------------------------------
#ifdef Debug
#ifdef DebugStop
sprintf(str_buf, "4.2.2 FopenJs js_file_name: [%s]", js_file_name);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc))
   {
      js_file=fopen((const char *)js_file_name, "r");
      if(!js_file)
      {
         retv=GetLastError();
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, retv /* js_file_name */, True, __FILE__, __LINE__, 0L);
      }
   }

   endfl=False;

#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.2.3 FgetsJs", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(js_file && SUCCEEDED(retc)) while((!endfl) && SUCCEEDED(retc))
   {
      fgets((char *)m_StrBuf, KP_MAX_FILE_LIN_LEN, js_file);
//    if(ferror(js_file))
//       retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      if((ferror(js_file) || feof(js_file)) && SUCCEEDED(retc)) endfl=True;

      if((!endfl) && SUCCEEDED(retc))
      {
         for(ii = 0; (ii < res_cnt) && SUCCEEDED(retc); ii++)
            retc = ScanPdfParValue(plpszaParNames[ii], &(res_arr_ptr[ii]));

#if FALSE
         if(SUCCEEDED(retc))
         {
            data_ready_val=NULL;
            retc=ScanPdfParValue(JS_DATA_READY_PAR_NAME, &data_ready_val);
            if((data_ready_val!=NULL) && SUCCEEDED(retc))
            {
               TvStrUpr(data_ready_val);
               if(strcmp(data_ready_val, "OK")==0) *pbDataReady=True;
            }

            KP_DELETEA(data_ready_val);
         }
#else
         *pbDataReady = True; // Tadas nesuformuoja duomenys = (new String(\"\"))"))
#endif
      }

   }

#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.2.4 FgcloseJs", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif


// ---------------------------------
#if FALSE
   if(SUCCEEDED(retc))
   {
      if(/* (!js_file) || */ ((!*pbDataReady) && kumul))
      {
         *pbDataReady=True;
         retc=KpMsgOut(KPST_MSG_REZ_NESUFORM, IDI_ERROR, KP_MB_BAIGTI);
      }
   }
#endif

   if(js_file) fclose(js_file);
   js_file=NULL;


// ---------------------------------
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.2.5 FormatResArr", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(SUCCEEDED(retc))
   {
      lpszBuf[0]=Nul;

      if(*pbDataReady)
      {
         for(ii=0; (ii<res_cnt) && SUCCEEDED(retc); ii++)
         {
            if(res_arr_ptr[ii])
            {
               if(strlen(lpszBuf)+strlen(res_arr_ptr[ii])<iBufSize)
                  strcat(lpszBuf, res_arr_ptr[ii]);
               else
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
            }

            if((strlen(lpszBuf)+1<iBufSize) && (ii<res_cnt-1))
               strcat(lpszBuf, "\t");
         }
      }
   }


// ----------------------------- release memory
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.2.6 ReleaseResArr", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

   if(res_arr_ptr != NULL)
      for(ii = 0; ii < res_cnt; ii++) KP_DELETEA(res_arr_ptr[ii]);

   KP_DELETEA(res_arr_ptr);

return(retc);
}


HRESULT KpStApp::GetPdfPar(const unsigned char *lpszParName, unsigned char *lpszValue, int iBufSize)
{
HRESULT retc = S_OK;
const unsigned char *par_nam_buf[2];
bool ready = False;

   KP_ASSERT(lpszParName, E_INVALIDARG, null, True);
   KP_ASSERT(lpszValue, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      par_nam_buf[0] = lpszParName;
      par_nam_buf[1] = null;

      retc = GetPdfPars(lpszValue, iBufSize, par_nam_buf, &ready);
   }
   if((!ready) && SUCCEEDED(retc)) KP_ERROR(KP_E_KWD_NOT_FOUND, null);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetRezFileName(unsigned char *lpszFNamBuf)
{
HRESULT retc=S_OK;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];

   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);

// ---------------------------------
   if((lpszFNamBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   if(SUCCEEDED(retc)) strcpy(lpszFNamBuf, rez_fname);

   if(SUCCEEDED(retc))
      if((strchr(lpszFNamBuf, '\\')==NULL) && (strchr(lpszFNamBuf, ':')==NULL))
      {
// relative path - search for My Documets folder
         retc=GetLocalPath(lpszFNamBuf, KP_My_Documents);
         if(SUCCEEDED(retc))
            if(strlen(lpszFNamBuf)+strlen(rez_fname)+1>=KP_MAX_FNAME_LEN)
               retc=KpErrorProc.OutputErrorMessage(KP_E_OUTOFMEM, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc))
            strcat(lpszFNamBuf, rez_fname);
      }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::FormAddData(unsigned char *lpszAddDataBuf, bool baDataFl[KPSTAP_NUM_OF_SETS], int iNumOfRecs, int iFieldCnt, bool bSrvFl)
{
HRESULT retc=S_OK;
unsigned char file_name[KP_MAX_FNAME_LEN+1];
KpStDataFileTypes server_file;
unsigned char *str_buf = null;
DWORD ll;
int comp_id=0;

   if((lpszAddDataBuf==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);

   /* retc0= */ GetCommonCompID();
   if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&comp_id, KP11_COMPID);

   KP_NEWA(str_buf, unsigned char, WRITE_DATA_FILE_STR_BUF_LEN + 1);

   if(SUCCEEDED(retc)) lpszAddDataBuf[0] = Nul;

// server data file? !!!!
   if(SUCCEEDED(retc)) retc=GetRezFileName(file_name);

   if(SUCCEEDED(retc))
   {
      if(bSrvFl) server_file=KpStServerFilePost;
      else
      {
         server_file=KpStLocalFile;
//       if(ctoupper(file_name[0])>'d') server_file=True;
         if(
            (strstr(file_name, "a:") == NULL) &&
            (strstr(file_name, "A:") == NULL) &&
            (strstr(file_name, "b:") == NULL) &&
            (strstr(file_name, "B:") == NULL) &&
            (strstr(file_name, "c:") == NULL) &&
            (strstr(file_name, "C:") == NULL) &&
            (strstr(file_name, "d:") == NULL) &&
            (strstr(file_name, "D:") == NULL)
         )
            server_file=KpStServerFileDirect;
      }
   }


// ServFl // ar duom. i serveri?
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf, "%d\t", server_file);

// RezFileName // duom. failo vardas
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+strlen(file_name)+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, file_name);
      EncodeText(str_buf);
      strcat(lpszAddDataBuf, str_buf);
      strcat((char *)lpszAddDataBuf, "\t");
   }

// ClipBrdFl // ar buvo duomenu clipboard'e?
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", baDataFl[0]);

// GlobJsFl // ar buvo duomenu pdf parametruose?
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", baDataFl[1]);

// NumOfRecs // duom. eiluciu skaicius
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", iNumOfRecs);

// CompId // kompo ID
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", comp_id /* m_iCompId */);

// CompName // kompo vardas
   if(SUCCEEDED(retc))
   {
      ll=KP_MAX_FNAME_LEN;
      if(!GetComputerName((char *)str_buf, &ll))
      {
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
         strcpy(str_buf, "???");
      }
      str_buf[KP_MAX_FNAME_LEN]=Nul;
   }
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+strlen(str_buf)+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      EncodeText(str_buf);
      strcat(lpszAddDataBuf, str_buf);
      strcat(lpszAddDataBuf, "\t");
   }

// UserName // user name
   if(SUCCEEDED(retc))
   {
      ll=KP_MAX_FNAME_LEN;
      if(!GetUserName((char *)str_buf, &ll))
      {
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
         strcpy(str_buf, "???");
      }
      str_buf[KP_MAX_FNAME_LEN]=Nul;
   }
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+strlen(str_buf)+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      EncodeText(str_buf);
      strcat(lpszAddDataBuf, str_buf);
      strcat(lpszAddDataBuf, "\t");
   }

// WinVer // windows version
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", iWindowsVersion);

// WinSP // service pack
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", iWindowsSP);

// OsPlatformID // os platform OSVERSIONINFOEX
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", Osvi.dwPlatformId);

// OsMajorVers // os major version OSVERSIONINFOEX
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", Osvi.dwMajorVersion);

// OsMinorVers // os minor version OSVERSIONINFOEX
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", Osvi.dwMinorVersion);

// OsVers // os version OSVERSIONINFOEX
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+strlen(Osvi.szCSDVersion)+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
   {
      strcpy(str_buf, Osvi.szCSDVersion);
      EncodeText(str_buf);
      strcat(lpszAddDataBuf, str_buf);
      strcat(lpszAddDataBuf, "\t");
   }

// OsBuildNo // os build no OSVERSIONINFOEX
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d\t", Osvi.dwBuildNumber);

// ---------------------------------------------------
// FieldCnt // duom. lauku skaicius (atsirado nuo 2005.04.14) - nafig reikia?
   if(SUCCEEDED(retc)) if(strlen(lpszAddDataBuf)+MAX_LONG_DIGITS+1>=KP_MAX_FILE_LIN_LEN)
      retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
   if(SUCCEEDED(retc))
      sprintf((char *)lpszAddDataBuf+strlen(lpszAddDataBuf), "%d" /* "%d\t" */, iFieldCnt);

   KP_DELETEA(str_buf);

return(retc);
}


// -------------------------------------------
unsigned char lpszSupplementToMaxField[KPSTAP_MAX_NUM_OF_FIELDS+1]={"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"};

HRESULT KpStApp::WriteDataFile(const unsigned char *lpszBuf1, const unsigned char *lpszBuf2, const unsigned char *lpszBuf3, bool bSrvFl, bool bShowErrorMessages)
{
HRESULT retc = S_OK;
const unsigned char *args[KPSTAP_NUM_OF_SETS] = { NULL, NULL, NULL};
unsigned char *text_bufs[KPSTAP_NUM_OF_SETS] = { NULL, NULL, NULL};
unsigned char *text_bufs1[KPSTAP_NUM_OF_SETS] = { NULL, NULL, NULL};
int buf_len; // duomenu dalies ilgis
int buf_size[KPSTAP_NUM_OF_SETS]={0, 0, 0}; // visas duomenu buferiu ilgis
unsigned char **field_arrays[KPSTAP_NUM_OF_SETS] = { NULL, NULL, NULL};
int field_cnt;
int field_cnts[KPSTAP_NUM_OF_SETS];
unsigned char user_name[KP_MAX_FNAME_LEN + 1];
long shuff_val;
int *shuffle=NULL;
int cur_shuff;
bool no_fields[KPSTAP_NUM_OF_SETS];
bool no_fields_all;
unsigned char *file_buf=NULL;
int nn;
int ii;
int kk;
int jj;
DWORD ll;
unsigned char *str_buf = null;
bool done;
int rep_count;
FILE *res_file;
bool file_error;
int retv;
bool data_fl[KPSTAP_NUM_OF_SETS]={False, False, False};
int num_of_recs = 0;
long file_len;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
bool kumul = False;
int shuff_cnt = 0;
const unsigned char *pnts;
unsigned char *pntd;
unsigned char *add_data = null;

   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);

   if(SUCCEEDED(retc)) retc=GetIniKumul(&kumul);
   if(SUCCEEDED(retc)) retc=GetIniShuffCnt(&shuff_cnt);

   KP_NEWA(str_buf, unsigned char, WRITE_DATA_FILE_STR_BUF_LEN + 1);

   if(SUCCEEDED(retc)) if(strlen(rez_fname) > 0)
   {

//    if((m_pRezFNameDialog == NULL) && SUCCEEDED(retc))
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

      args[0]=lpszBuf1;
      args[1]=lpszBuf2;
      args[2]=lpszBuf3;

      KP_NEWA(add_data, unsigned char, KP_MAX_FILE_LIN_LEN + 100);

// nusikopijuojam buferiu duomenis
      for(nn = 0; (nn < KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
      {
         if(SUCCEEDED(retc))
         {
            data_fl[nn] = False;
            buf_len=0;
            if(args[nn] != NULL) buf_len = strlen(args[nn]);
            if(buf_len) data_fl[nn] = True;

            buf_size[nn] = buf_len+KPSTAP_MAX_NUM_OF_FIELDS+
                        KP_MAX_FILE_LIN_LEN+100; // MAX_LONG_DIGITS+1+KP_MAX_FNAME_LEN+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+KP_MAX_FNAME_LEN+1+KP_MAX_FNAME_LEN+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+MAX_LONG_DIGITS+1+KP_MAX_FNAME_LEN+1+100;

         }
         KP_NEWA(text_bufs[nn], unsigned char, buf_size[nn]);
         KP_NEWA(text_bufs1[nn], unsigned char, buf_size[nn]);

         if(SUCCEEDED(retc))
         {
            if(buf_len==0) text_bufs[nn][0]=Nul;
            else strcpy(text_bufs[nn], args[nn]);
         }
      }

// jei vienodi duomenys - viena istrinam
      for(nn=1; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
         if(strcmp(text_bufs[0], text_bufs[nn])==0) text_bufs[nn][0]=Nul;

// skaiciuojam max lauku skaiciu
      for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
         retc=CountStrings(&field_cnts[nn], text_bufs[nn], (const unsigned char *)"\t", True);
      field_cnt=field_cnts[0];
      for(nn=1; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
      {
         if(field_cnt<field_cnts[nn]) field_cnt=field_cnts[nn];
         if(field_cnt>KPSTAP_MAX_NUM_OF_FIELDS)
            retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L);
      }

// suvienodinam lauku sk.
      for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
         strcat(text_bufs[nn], lpszSupplementToMaxField+KPSTAP_MAX_NUM_OF_FIELDS-(field_cnt-field_cnts[nn]));

// skaidom i laukus
      for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
      {
         retc=SplitStrings(&field_arrays[nn], &field_cnts[nn], text_bufs[nn], (const unsigned char *)"\t", True);
         if((field_cnts[nn]!=field_cnt) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) for(ii=0; (ii<field_cnt) && SUCCEEDED(retc); ii++)
         {
            if(SUCCEEDED(retc)) retc=SpcEolToSpc(field_arrays[nn][ii]);
            if(SUCCEEDED(retc)) retc=CutInitTrailSpcs(field_arrays[nn][ii]);
         }
      }

// tikrinam, ar ne tusti
      no_fields_all=True;
      for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
      {
         no_fields[nn]=True;
         {
            for(ii=0; ii<field_cnt; ii++)
            {
               if(field_arrays[nn][ii]==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  if(strlen(field_arrays[nn][ii])>0)
                  {
                     no_fields[nn]=False;
                     no_fields_all=False;
                     break;
                  }
            }
         }
         if(!no_fields[nn]) num_of_recs++;
      }

      if(SUCCEEDED(retc))
      {
         ll=KP_MAX_FNAME_LEN;
         if(!GetUserName((char *)user_name, &ll))
         {
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
            strcpy(user_name, "???");
         }
         user_name[KP_MAX_FNAME_LEN]=Nul;
      }

      if(((field_cnt==0) || no_fields_all) && SUCCEEDED(retc))
      {
         if(/* kumul && */ bShowErrorMessages && SUCCEEDED(retc))
         {
//          if(strcmp(user_name, "administrator")==0)
               strcpy(str_buf, KPST_MSG_REZ_NFOUND_1);
//          else
//             sprintf((char *)str_buf, (char *)KPST_MSG_REZ_NFOUND_2, user_name, lpszaWindowsVerNames[iWindowsVersionCut]);

            retc=KpMsgOut(str_buf, IDI_ERROR, KP_MB_BAIGTI);
         }
         if(SUCCEEDED(retc))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_OBJ_NOT_FOUND, null, True, __FILE__, __LINE__, 0L);
            retc=KP_E_OBJ_NOT_FOUND;
         }
      }

// shuffle
      if(SUCCEEDED(retc))
      {
         shuff_val=0;

         if(shuff_cnt<0) shuff_cnt=0;
         if(shuff_cnt>KPSTAP_MAX_NUM_OF_SHUFFLED_FIELDS)
            shuff_cnt=KPSTAP_MAX_NUM_OF_SHUFFLED_FIELDS;
         if(field_cnt<shuff_cnt) shuff_cnt=field_cnt;

         if(shuff_cnt>0)
         {
            KP_NEWA(shuffle, int, shuff_cnt);

            if(SUCCEEDED(retc))
               for(ii=0; ii<shuff_cnt; ii++) shuffle[ii]=(-1);

            if(SUCCEEDED(retc)) retc=TvUniFname.RandInt(&shuff_val);

            if(SUCCEEDED(retc))
            {
               for(ii=0; ii<shuff_cnt; ii++)
               {
                  cur_shuff=shuff_val%(shuff_cnt-ii);
                  shuff_val/=(shuff_cnt-ii);

                  kk=0;
                  for(jj=0; jj<cur_shuff; jj++)
                  {
                     kk=(kk+1)%shuff_cnt;
                     while(shuffle[kk]!=(-1)) kk=(kk+1)%shuff_cnt;
                  }
                  while(shuffle[kk]!=(-1)) kk=(kk+1)%shuff_cnt;
                  shuffle[kk]=ii;
               }
               for(ii=0; (ii<shuff_cnt) && SUCCEEDED(retc); ii++) if(shuffle[ii]==(-1))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

// sumaisymu kauke
// skaitmenys rodo, kurioje pozicijoje tarp sumaisytu yra laukas, atitinkantis skaitmens pozicija:
// 315264 33333 11111 55555 22222 66666 44444
            shuff_val=0;
            if(SUCCEEDED(retc))
               for(ii=0; ii<shuff_cnt; ii++) shuff_val=shuff_val*10+shuffle[ii]+1;

         } // if(shuff_cnt>0)

      } // if(SUCCEEDED(retc))

      if(SUCCEEDED(retc)) retc=FormAddData(add_data, data_fl, num_of_recs, field_cnt, bSrvFl);

// suformuoti teksto eilutes atgal
      for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
      {
         text_bufs1[nn][0]=Nul;

         if((!no_fields[nn]) && SUCCEEDED(retc))
         {
            text_bufs1[nn][0]=Nul;

            for(ii=0; (ii<field_cnt-shuff_cnt) && SUCCEEDED(retc); ii++)
            {
               if(strlen(text_bufs1[nn])+strlen(field_arrays[nn][ii])+1>=buf_size[nn]-1)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  strcat(text_bufs1[nn], field_arrays[nn][ii]);
               /* if(ii<field_cnt-1) */ strcat(text_bufs1[nn], "\t");
               }
            }

            if(shuff_cnt>0)
            {
               if(strlen(text_bufs1[nn])+MAX_LONG_DIGITS+1>=buf_size[nn]-1)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
                  sprintf((char *)(text_bufs1[nn]+strlen(text_bufs1[nn])), "%ld\t", shuff_val);
            }

            for(ii=field_cnt-shuff_cnt; (ii<field_cnt) && SUCCEEDED(retc); ii++)
            {
               if(strlen(text_bufs1[nn])+strlen(field_arrays[nn][field_cnt-shuff_cnt+shuffle[ii-(field_cnt-shuff_cnt)]])+1>=buf_size[nn]-1)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
               if(SUCCEEDED(retc))
               {
                  strcat(text_bufs1[nn],
                     field_arrays[nn][field_cnt-shuff_cnt+shuffle[ii-(field_cnt-shuff_cnt)]]);
               /* if(ii<field_cnt-1) */ strcat(text_bufs1[nn], "\t");
               }
            }

         } // if((!no_fields[nn]) && SUCCEEDED(retc))

         if(strlen(text_bufs1[nn])+strlen(add_data)+1>=buf_size[nn]-1)
            retc=KpErrorProc.OutputErrorMessage(KP_E_BUFFER_OVERFLOW, null, True, __FILE__, __LINE__, 0L);
         if(SUCCEEDED(retc)) strcat(text_bufs1[nn], add_data);

      } // for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)


// loop while data written
      done=False;
      rep_count=0;
      while((!done) && SUCCEEDED(retc))
      {

// open file
#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.3.5 OpenResFile", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

         res_file=NULL;
         file_error=False;

         while((!res_file) && SUCCEEDED(retc))
         {

#if FALSE // #ifdef Debug
sprintf(str_buf, "%lx %lx %lx %lx %s %s", theKpStAppPtr, this, theKpStAppPtr->m_Ini.m_lpszRezFName, m_Ini.m_lpszRezFName, theKpStAppPtr->m_Ini.m_lpszRezFName, m_Ini.m_lpszRezFName);
KpMsgOut(str_buf, IDI_QUESTION, KP_MB_TESTI);
#endif

// get data file name
            if(SUCCEEDED(retc)) retc=GetRezFileName(rez_fname);

// open file
            if(SUCCEEDED(retc))
            {
               res_file=fopen((const char *)rez_fname, kumul?"a+":"w");
               if(!res_file)
               {
                  retv=GetLastError();
                  if(
                     (
                        (strstr(rez_fname, "a:") != NULL) ||
                        (strstr(rez_fname, "A:") != NULL) ||
                        (strstr(rez_fname, "b:") != NULL) ||
                        (strstr(rez_fname, "B:") != NULL)
                     ) &&
                     (!bSrvFl)
                    )
                     retc=KpMsgOut(KPST_MSG_INSERT_FLOPPY, IDI_ERROR, KP_MB_TESTI);
                  else
                  {
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, rez_fname, True, __FILE__, __LINE__, 0L);
                     if((++rep_count)<3) retc = KpSleep(1000, m_hBitmapWindow);
                     else
                     {
                        if(bSrvFl) retc=KP_E_DIR_ERROR;
                        else
                        {
                           retc = S_OK;
                           if(!KpstEdiDialogPtr)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

                           if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->OpenWindow(KPST_MSG_UNABLE_OPEN_REZFILE);
                           if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->DoEdit(1000);
                        }
                     }
                  }

               } // if(!res_file)

            } // if(SUCCEEDED(retc))

         } // while((!res_file) && SUCCEEDED(retc))


#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.3.6 FPuts", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

         if(res_file)
         {
            for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && (!file_error) && SUCCEEDED(retc); nn++)
            {
               if((!no_fields[nn]) && SUCCEEDED(retc))
               {
                  fputs((const char *)text_bufs1[nn], res_file);
                  if(text_bufs1[nn][strlen(text_bufs1[nn])-1]!='\n')
                     fputs("\n", res_file);

                  if(ferror(res_file) || feof(res_file))
                  {
                     retv=GetLastError();
//                   retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, rez_fname, True, __FILE__, __LINE__, 0L);
                     file_error=True;
                     if(bSrvFl) retc=KP_E_FERROR;
                     else
                     {
                        retc = S_OK;
                        if(!KpstEdiDialogPtr)
                           retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

                        if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->OpenWindow(KPST_MSG_UNABLE_WRITE_REZFILE);
                        if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->DoEdit(1000);
                     }
                  }
               }

            } // for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && (!file_error) && SUCCEEDED(retc); nn++)

         } // if(res_file)

#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.3.7 FClose", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif

         if(res_file && SUCCEEDED(retc))
         {
            if(fclose(res_file))
            {
               retv=GetLastError();
//             retc0=KpErrorProc.OutputErrorMessage(KP_E_FERROR, rez_fname, True, __FILE__, __LINE__, 0L);
//             if(SUCCEEDED(retc)) retc=retc0;
               if(!file_error)
               {
                  file_error=True;
                  if(bSrvFl) retc=KP_E_FERROR;
                  else
                  {
                     retc = S_OK;
                     if(!KpstEdiDialogPtr)
                        retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

                     if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->OpenWindow(KPST_MSG_UNABLE_CLOSE_REZFILE);
                     if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->DoEdit(1000);
                  }
               }
            }
            res_file=NULL;
         }

#ifdef Debug
#ifdef DebugStop
KpMsgOut("4.3.8 TestCompare", IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);
#endif
#endif
         if((!file_error) && SUCCEEDED(retc))
         {
            done=True;
            file_buf=NULL;
            if(SUCCEEDED(retc))
            {
               retc=ReadFileContents(rez_fname, &file_buf, &file_len, False, False);
               if(FAILED(retc)) if(!bSrvFl)
               {
                  retc = S_OK;
                  if(!KpstEdiDialogPtr)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

                  if(SUCCEEDED(retc)) retc=/*m_pRezFNameDialog-> */ KpstEdiDialogPtr->OpenWindow(KP_MSG_UNABLE_READ_WRITTEN);
                  if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->DoEdit(1000);
               }
               if(file_buf==NULL)
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc))
            {
               for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
               {
                  if(!no_fields[nn])
                  {
                     if(strstr(file_buf, text_bufs1[nn])==NULL)
                     {
                        if(bSrvFl)
                        {
                           retc=KP_E_FERROR;
                           KpErrorProc.OutputErrorMessage(retc, null, !bSrvFl, __FILE__, __LINE__, 0L);
                        }
                        else
                        {
                           done=False;
                           retc = S_OK;
                           if(!KpstEdiDialogPtr)
                              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);

                           if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->OpenWindow(KPST_MSG_COULDNT_WRITE);
                           if(SUCCEEDED(retc)) retc=/* m_pRezFNameDialog-> */ KpstEdiDialogPtr->DoEdit(1000);
                        }
                     }
                  }
               }
            }

            KP_DELETEA(file_buf);

         } // if((!file_error) && SUCCEEDED(retc))

         if(retc==KP_E_CANCEL)
         {
            if(bSrvFl) done=True;
            else
            {
               retc=KpMsgOut(KPST_MSG_REFUSE_RESULTS, IDI_QUESTION, KP_MB_TAIP_NE);
               if(SUCCEEDED(retc))
               {
                  done=True;
                  retc=KP_E_CANCEL;
               }
               else if(retc==KP_E_CANCEL)
               {
                  done=False;
                  retc=S_OK;
               }
            }
         }

      } // while((!done) && SUCCEEDED(retc))


      if(done && SUCCEEDED(retc))
      {
         pntd=str_buf;

         for(nn=0; (nn<KPSTAP_NUM_OF_SETS) && SUCCEEDED(retc); nn++)
         {
            if(!no_fields[nn])
            {
               if((nn>0) && (pntd>str_buf))
               {
                  *(pntd++)=',';
                  *(pntd++)=Spc;
               }

               pnts=text_bufs1[nn];
               while(*pnts && (*pnts!='\t') && (pntd-str_buf<WRITE_DATA_FILE_STR_BUF_LEN-1))
                  *(pntd++)=(*pnts++);
               *(pntd++)=Spc;
               if(*pnts=='\t') pnts++;
               while(*pnts && (*pnts!='\t') && (pntd-str_buf<WRITE_DATA_FILE_STR_BUF_LEN-1))
                  *(pntd++)=(*pnts++);
            }
         }
         *pntd=Nul;

         pnts=KPST_MSG_REZ_SUCCESS;
         if(pntd-str_buf+strlen(pnts)<WRITE_DATA_FILE_STR_BUF_LEN)
         {
            strcpy(pntd, pnts);
            pntd+=strlen(pnts);
         }

         if(pntd-str_buf+strlen(rez_fname)<WRITE_DATA_FILE_STR_BUF_LEN) strcpy(pntd, rez_fname);

         if(!bSrvFl) retc=KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_BAIGTI);
      }

      if(!bSrvFl)
      {
         if(!KpstEdiDialogPtr)
            /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L);
         else  /* m_pRezFNameDialog-> */ KpstEdiDialogPtr->CloseWindow();
      }

   } // if(strlen(rez_fname)>0)

   KP_DELETEA(shuffle);

   for(nn=0; nn<KPSTAP_NUM_OF_SETS; nn++)
   {
      KP_DELETEA(field_arrays[nn]);
      KP_DELETEA(text_bufs[nn]);
      KP_DELETEA(text_bufs1[nn]);
   }

   KP_DELETEA(add_data);
   KP_DELETEA(str_buf);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::CloseClipViewer(void)
{
HRESULT retc=S_OK;

#ifdef KPST_USE_CLIPBOARD
   if(m_lClipViewerThreadId)
   /* retc= */ CloseProcess(m_lpszClipViewerFName, m_lClipViewerThreadId);
#endif

return(retc);
}



//-----------------------------------
KpstExercDataFileLine_tag::KpstExercDataFileLine_tag(void)
{
   m_lpszIP=(const unsigned char *)"";
   m_lpszUzduotis=(const unsigned char *)"";
   m_lpszPradzia=(const unsigned char *)"";
   m_lpszPabaiga=(const unsigned char *)"";
   m_lpszLygis=(const unsigned char *)"";
   m_lpszPasirinktasRezimas=(const unsigned char *)"";
   m_lpszPasirinktasUzdSk=(const unsigned char *)"";
   m_lpszPateiktasUzdSk=(const unsigned char *)"";
   m_lpszTeisingai=(const unsigned char *)"";
   m_lpszNeteisingai=(const unsigned char *)"";
   m_lpszPasirinktasLaikas=(const unsigned char *)"";
}


//-----------------------------------
// File_Name=cd5_3.pdf&Start_Time=2006.09.11+11%3a51%3a05&Lygis=1+lygis&Pasirinktas_rezimas=Mokausi&Pasirinkta_uzd_sk=5&Pasirinktas_laikas_sk=2
// File_Name=cd5_3.pdf&Start_Time=2006.09.11+17%3a27%3a28&Lygis=1+lygis&Pasirinktas_rezimas=Mokausi&Pasirinktas_laikas_sk=4
// File_Name=cd5_3.pdf&Lygis=1+lygis&Pasirinktas_rezimas=Mokausi&Pasirinkta_uzd_sk=5&Pasirinktas_laikas_sk=2
// File_Name=cd5_3.pdf&Stop_Time=2006.09.11+16%3a06%3a39&Pateikta_uzd_sk=1
// File_Name=cd5_3.pdf&Stop_Time=2006.09.11+17%3a01%3a00&Pateikta_uzd_sk=3&Teisingai_sk=1&Neteisingai_sk=1
HRESULT KpStApp::WriteExercDataFile(const unsigned char *lpszInMsg)
{
HRESULT retc = S_OK;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
FILE *res_file;
bool kumul = False;
int shuff_cnt = 0;
KpstExercDataFileLine data_line;
unsigned char *msg_buf = null;
const unsigned char *pnts;
unsigned char *pntd;

   if((lpszInMsg==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) retc = GetIniRezFName(rez_fname);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(rez_fname);

   if(SUCCEEDED(retc)) retc = GetIniKumul(&kumul);
   if(SUCCEEDED(retc)) retc = GetIniShuffCnt(&shuff_cnt);

   if(SUCCEEDED(retc)) if(strlen(rez_fname)>0)
   {
      if((shuff_cnt>0) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(E_NOTIMPL, null, True, __FILE__, __LINE__, 0L, NULL);

// get data file name
      if(SUCCEEDED(retc)) retc=GetRezFileName(rez_fname);

// kepure
      if(SUCCEEDED(retc))
      {
         res_file=fopen((const char *)rez_fname, "r");
         if((res_file==NULL) || (!kumul))
         {
            res_file=fopen((const char *)rez_fname, "w");
            if((res_file==NULL) && SUCCEEDED(retc))
               retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, rez_fname, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               fputs(KPST_EXC_HAT, res_file);
               if(ferror(res_file) || feof(res_file))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, rez_fname, True, __FILE__, __LINE__, 0L, NULL);
            }
         }
         if(res_file /* SUCCEEDED(retc) */)
            if(fclose(res_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, rez_fname, True, __FILE__, __LINE__, 0L, NULL);
         res_file = NULL;
      }

// buferis
      KP_NEWA(msg_buf, unsigned char, strlen(lpszInMsg) + 1);

      if(SUCCEEDED(retc)) strcpy(msg_buf, lpszInMsg);

// duomenys
      if((m_pLicListSocket!=NULL) && SUCCEEDED(retc))
         data_line.m_lpszIP=m_pLicListSocket->m_PackedUrl.m_lpszServerName;

      if(SUCCEEDED(retc))
      {
         pnts=strstr(msg_buf, "File_Name=");
         if(pnts) data_line.m_lpszUzduotis=pnts+strlen("File_Name=");

         pnts=strstr(msg_buf, "Start_Time=");
         if(pnts) data_line.m_lpszPradzia=pnts+strlen("Start_Time=");

         pnts=strstr(msg_buf, "Stop_Time=");
         if(pnts) data_line.m_lpszPabaiga=pnts+strlen("Stop_Time=");

         pnts=strstr(msg_buf, "Lygis=");
         if(pnts) data_line.m_lpszLygis=pnts+strlen("Lygis=");

         pnts=strstr(msg_buf, "Pasirinktas_rezimas=");
         if(pnts) data_line.m_lpszPasirinktasRezimas=pnts+strlen("Pasirinktas_rezimas=");

         pnts=strstr(msg_buf, "Pasirinkta_uzd_sk=");
         if(pnts) data_line.m_lpszPasirinktasUzdSk=pnts+strlen("Pasirinkta_uzd_sk=");

         pnts=strstr(msg_buf, "Pateikta_uzd_sk=");
         if(pnts) data_line.m_lpszPateiktasUzdSk=pnts+strlen("Pateikta_uzd_sk=");

         pnts=strstr(msg_buf, "Teisingai_sk=");
         if(pnts) data_line.m_lpszTeisingai=pnts+strlen("Teisingai_sk=");

         pnts=strstr(msg_buf, "Neteisingai_sk=");
         if(pnts) data_line.m_lpszNeteisingai=pnts+strlen("Neteisingai_sk=");

         pnts=strstr(msg_buf, "Pasirinktas_laikas_sk=");
         if(pnts) data_line.m_lpszPasirinktasLaikas=pnts+strlen("Pasirinktas_laikas_sk=");

         pntd=msg_buf;
         do
         {
            pntd=strchr(pntd, '&');
            if(pntd) *(pntd++) = Nul;
         } while(pntd);

//       TvStrLwr(data_line.m_lpszUzduotis);
         pntd = strstr(data_line.m_lpszUzduotis, KPST_PDF_FILE_TYPE);
         if(pntd == NULL) pntd = strstr(data_line.m_lpszUzduotis, KPST_TEV_OBJ_FILE_TYPE);
         if(pntd) *pntd=Nul;
      }

// failas
      if(SUCCEEDED(retc))
      {
         res_file=fopen((const char *)rez_fname, "a+");
         if((res_file==NULL) && SUCCEEDED(retc))
            retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, rez_fname, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         fprintf(res_file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
            data_line.m_lpszIP=m_pLicListSocket->m_PackedUrl.m_lpszServerName,
            data_line.m_lpszUzduotis,
            data_line.m_lpszPradzia,
            data_line.m_lpszPabaiga,
            data_line.m_lpszLygis,
            data_line.m_lpszPasirinktasRezimas,
            data_line.m_lpszPasirinktasUzdSk,
            data_line.m_lpszPateiktasUzdSk,
            data_line.m_lpszTeisingai,
            data_line.m_lpszNeteisingai,
            data_line.m_lpszPasirinktasLaikas);

            if(ferror(res_file) || feof(res_file))
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, rez_fname, True, __FILE__, __LINE__, 0L, NULL);
      }

      if(res_file /* SUCCEEDED(retc) */)
         if(fclose(res_file))
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, rez_fname, True, __FILE__, __LINE__, 0L, NULL);
      res_file = NULL;
   }

   KP_DELETEA(msg_buf);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::TestFlashId(long lFlashId, bool *pbFound, int *piNumOfFlashes, unsigned char cDriveLetter)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
static TestFlashIdPars_1 test_fl_pars;

   rc_pars.iOpCode=KP_RC_CALLBACK;
   rc_pars.iParBlSize=sizeof(rc_pars);
   rc_pars.enc.iCallBackIx=KP_RC_CBIX_TestFlashID;

   test_fl_pars.m_pThis = this;
   test_fl_pars.m_lFlashId = lFlashId;
   test_fl_pars.m_pbFound = pbFound;
   test_fl_pars.m_piNumOfFlashes = piNumOfFlashes;
   test_fl_pars.m_cDriveLetter = cDriveLetter;

   rc_pars.enc.pCallBackPars = &test_fl_pars;

// PutLogMessage_("KpStApp::TFI ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */, True);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::CallRCCallBackPtr(KpCommonCallBackIxs iCallBackIx, bool bCheckErrors)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;

   KP_ASSERT((iCallBackIx >= 0) && (iCallBackIx < KpHp11NumOfExtFun), E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_CALLBACK;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.iCallBackIx = iCallBackIx;
      rc_pars.enc.pCallBackPars = this;

// PutLogMessage_("KpStApp::CRCCBP ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */, bCheckErrors);
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::InitLicId(void)
{
HRESULT retc=S_OK;
static KpRcPars rc_pars;

   rc_pars.iOpCode = KP_RC_INIT_LICID;
   rc_pars.iParBlSize = sizeof(rc_pars);

// PutLogMessage_("KpStApp::ILI ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
HRESULT KpstTuxDecodeBuf(char *lpszFileBuf, long lFileLen)
{
HRESULT retc=S_OK;
static KpRcPars rc_pars;

   rc_pars.iOpCode=KP_RC_TUX_DECODE;
   rc_pars.iParBlSize=sizeof(rc_pars);

   rc_pars.enc.lCtrl /* iDataLen */ = ((lFileLen+3L)/4L)*4L;
   rc_pars.enc.pData = lpszFileBuf;

// PutLogMessage_("KpStApp::KTDB ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("KTDB() .... %x %x", &rc_pars, lpszFileBuf);
#endif

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

return(retc);
}


#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
unsigned long KpstTuxHash(unsigned long ulVal)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
int ss1;
int ss2;

   ss1 = sizeof(ulVal);
   ss2 = sizeof(rc_pars.value);
   KP_ASSERT(ss1 == ss2, KP_E_SYSTEM_ERROR, null, True);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_TUX_HASH;
      rc_pars.iParBlSize = sizeof(rc_pars);

      rc_pars.value = ulVal;

// PutLogMessage_("KpStApp::KTH ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   }

#if FALSE // #ifdef Debug
#if (Envir==MSWin32) && (Compiler != Watcom)
stringstream str_stream;
str_stream << "tux hash: " << hex << ulVal << " --> " << hex << rc_pars.value << ", " << hex << TUX_HASH(ulVal);
KP_TRACE(KpString(str_stream.str()));
#endif
#endif

return(rc_pars.value);
}


// -------------------------------------------
HRESULT KpStApp::GetTestUpdates(bool *pbTestUpdates, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszIniFName)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
HKEY hKey = NULL;
LONG retw = ERROR_SUCCESS;
DWORD /* bool */ test_updates = 0L; // = False;
DWORD /* bool */ test_updates_local = 0L; // = False;
// unsigned char publisher[KP_MAX_FNAME_LEN + 1];

   if((pbTestUpdates == NULL) && SUCCEEDED(retc))
      KpErrorProc.OutputErrorMessage(E_INVALIDARG, null, False, __FILE__, __LINE__, 0L, NULL);

// -----------------------------------
// if(SUCCEEDED(retc))
// {
//    if(lpszPublisher != null)
//    {
//       KP_ASSERT(strlen(lpszPublisher) <= KP_MAX_FNAME_LEN, KP_E_BUFFEROVERFLOW, null, True);
//       if(SUCCEEDED(retc)) strcpy(publisher, lpszPublisher);
//    }
//    else retc = GetIniPublisher(publisher);
// }

// if(SUCCEEDED(retc)) retc = GetIniProdVer(&iProdVerGlob);

int prod_ver = iProdVer;
   if((prod_ver == 0) && SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = GetProdVerRegVariableDword(&test_updates, /* publisher, */ prod_ver, KPST_PRODVER_REG_KEY_TestUpdates);

// ----------------------------------- lpszIniFName
   if((lpszIniFName != null) && SUCCEEDED(retc))
   {
      m_bSaveTestUpdatesToIni = False;
      retc0 = LoadIniFile(lpszIniFName, True, True);
      if(SUCCEEDED(retc0))
      {
         strcpy(m_lpszIniFName, lpszIniFName);
         m_bSaveTestUpdatesToIni = True; // perskaityt pavyko – produktas atmintukinis, reikës ir iðsaugot á .ini
      }
   }
bool test_upd = False;
   if(SUCCEEDED(retc)) retc = GetIniTestUpdates(&test_upd);
   if(test_upd && SUCCEEDED(retc)) test_updates = 1L;

PutLogMessage_("KpStApp::GetTestUpdates() %d %s %s %d %x", m_bSaveTestUpdatesToIni, lpszIniFName?lpszIniFName:(const unsigned char *)"null", m_lpszIniFName, test_upd, retc);

// ----------------------------
   if(SUCCEEDED(retc)) *pbTestUpdates = (test_updates != 0L);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SetTestUpdates(bool bTestUpdates, int iProdVer)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

// -----------------------------------
// unsigned char publisher[KP_MAX_FNAME_LEN+1];
// if(SUCCEEDED(retc)) retc = GetIniPublisher(publisher);

// if(SUCCEEDED(retc)) retc = GetIniProdVer(&iProdVerGlob);

int prod_ver = iProdVer;
   if((prod_ver == 0) && SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

   if(SUCCEEDED(retc)) retc = SetProdVerRegVariableDword(bTestUpdates, /* publisher, */ prod_ver, KPST_PRODVER_REG_KEY_TestUpdates);

// ----------------
   if(m_bSaveTestUpdatesToIni && SUCCEEDED(retc))
   {
      retc = SetIniTestUpdates(bTestUpdates);
      if(SUCCEEDED(retc)) retc = SaveIni();
   }
PutLogMessage_("KpStApp::SetTestUpdates() %d %s", m_bSaveTestUpdatesToIni, m_lpszIniFName);

return(retc);
}


// ----------------------------------------
HRESULT KpStApp::GetProdVerRegVariableStr(unsigned char *lpszValBuf, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName)
{
HRESULT retc = S_OK;
// unsigned char publisher[KP_MAX_FNAME_LEN + 1];
unsigned char key_name[KP_MAX_FILE_LIN_WDT + 1];
HKEY hKey = NULL;

// -----------------------------------
   KP_ASSERT(lpszValBuf != null, E_INVALIDARG, null, True);
   KP_ASSERT(lpszVarName != null, E_INVALIDARG, null, True);
// KP_ASSERT(lpszPublisher != null, E_INVALIDARG, null, True);

// -----------------------------------
// TODO: publisher perduoti per parametrà, nes StartGrp reikia iðoriniø produktø duomenø
// if(SUCCEEDED(retc)) retc = GetIniPublisher(publisher);

// -----------------------------------
   if(SUCCEEDED(retc))
   {
// publisher visada "TEV", nes per StartGrp.cfg publisher'is neperduodamas
      sprintf((char *)key_name, "Software\\%s\\%d", "TEV" /* lpszPublisher */ /* publisher */, iProdVer);

// -------------------------- pradþiai ieðkom lokalaus HKCU
      retc = KpRegQueryValue(HKEY_CURRENT_USER, (LPCTSTR)key_name, (LPCTSTR)lpszVarName, REG_SZ, lpszValBuf, KP_MAX_FNAME_LEN, False);

// -------------------------- neradom – ieðkom globalaus HKLM
      if(FAILED(retc)) retc = KpRegQueryValue(HKEY_LOCAL_MACHINE, (LPCTSTR)key_name, (LPCTSTR)lpszVarName, REG_SZ, lpszValBuf, KP_MAX_FNAME_LEN, False);
   }

return(retc);
}


// ----------------------------------------
HRESULT KpStApp::GetProdVerRegVariableDword(DWORD *plVarPtr, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName)
{
HRESULT retc = S_OK;
unsigned char key_name[KP_MAX_FILE_LIN_WDT + 1];
HKEY hKey = NULL;

// -----------------------------------
   KP_ASSERT(plVarPtr != NULL, E_INVALIDARG, null, True);
   KP_ASSERT(lpszVarName != null, E_INVALIDARG, null, True);
// KP_ASSERT(lpszPublisher != null, E_INVALIDARG, null, True);

// -----------------------------------
   if(SUCCEEDED(retc))
   {
// publisher visada "TEV", nes per StartGrp.cfg publisher'is neperduodamas
      sprintf((char *)key_name, "Software\\%s\\%d", "TEV" /* lpszPublisher */, iProdVer);

// -------------------------- pradþiai ieðkom lokalaus HKCU
      retc = KpRegQueryValue(HKEY_CURRENT_USER, (LPCTSTR)key_name, (LPCTSTR)lpszVarName, REG_DWORD, (BYTE *)plVarPtr, sizeof(DWORD), False);

// -------------------------- neradom – ieðkom globalaus HKLM
      if(FAILED(retc)) retc = KpRegQueryValue(HKEY_LOCAL_MACHINE, (LPCTSTR)key_name, (LPCTSTR)lpszVarName, REG_DWORD, (BYTE *)plVarPtr, sizeof(DWORD), False);
   }

return(retc);
}


// ----------------------------------------
HRESULT KpStApp::SetProdVerRegVariableStr(const unsigned char *lpszValue, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName)
{
HRESULT retc = S_OK;
unsigned char key_name[KP_MAX_FILE_LIN_WDT + 1];
HKEY hKey = NULL;
LONG retw = ERROR_SUCCESS;
DWORD dwDisposition;

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s",
         "TEV"); // lpszPublisher);

      hKey = NULL;
      retw = RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
               (LPCTSTR)key_name,
               0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &hKey, &dwDisposition);

      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);

      if(hKey != NULL) RegCloseKey(hKey);
      hKey = NULL;
   }

// ------------------
unsigned char *value = null;
   KP_NEWA(value, unsigned char, strlen(lpszValue) + 1);
   if(SUCCEEDED(retc))
   {
      strcpy(value, lpszValue);

      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         "TEV", // lpszPublisher,
         iProdVer // prod_name
         );

      retc = KpRegSetValue(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
               (LPCTSTR)key_name, (LPCTSTR)lpszVarName, REG_SZ, (BYTE *)value, strlen(lpszValue));
   }
   KP_DELETEA(value);

return(retc);
}


// ----------------------------------------
HRESULT KpStApp::SetProdVerRegVariableDword(DWORD lValue, /* const unsigned char *lpszPublisher, */ int iProdVer, const unsigned char *lpszVarName)
{
HRESULT retc = S_OK;
unsigned char key_name[KP_MAX_FILE_LIN_WDT + 1];
HKEY hKey = NULL;
LONG retw = ERROR_SUCCESS;
DWORD dwDisposition;

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s",
         "TEV"); // lpszPublisher);

      hKey = NULL;
      retw = RegCreateKeyEx(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
               (LPCTSTR)key_name,
               0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
               &hKey, &dwDisposition);

      KP_ASSERTE(retw == ERROR_SUCCESS, KP_E_SYSTEM_ERROR, retw, False);

      if(hKey != NULL) RegCloseKey(hKey);
      hKey = NULL;
   }

// ------------------
   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         "TEV", // lpszPublisher,
         iProdVer // prod_name
         );

DWORD ll = lValue;
      retc = KpRegSetValue(HKEY_CURRENT_USER, // HKEY_LOCAL_MACHINE,
               (LPCTSTR)key_name, (LPCTSTR)lpszVarName, REG_DWORD, (BYTE *)&ll, sizeof(ll));
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetProdVarReg(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
unsigned char publisher[KP_MAX_FNAME_LEN+1];
int prod_ver = 0;
long /* DWORD */ /* int */ prod_var = -1L; // 0L;
long /* DWORD */ /* int */ prod_var_local = -1L; // 0L;
unsigned char key_name[KP_MAX_FILE_LIN_WDT+1];
HKEY hKey = NULL;
DWORD dwBufLen;
DWORD dwValType;
LONG retw = ERROR_SUCCESS;

// -----------------------------------
   if(SUCCEEDED(retc)) retc = GetIniPublisher(publisher);
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver);

// ---------------------------------- ieskom registre ProdVar (Installed - 1) ir TestUpdates
// ---------------------------------- Installed
   prod_var = -1L;
   prod_var_local = -1L;

   if(SUCCEEDED(retc))
   {
      sprintf((char *)key_name,
         "Software\\%s\\%d", // "Software\\%s\\%s",
         publisher,
         prod_ver // prod_name
         );

// --------------------------
      retc0 = S_OK;

      retw = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
            (LPCTSTR)key_name,
            0, KEY_QUERY_VALUE, &hKey);
      if(retw!=ERROR_SUCCESS)
      {
         retc0 = KP_E_KWD_NOT_FOUND;
         hKey = NULL;
#ifdef Debug
         KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      }

      if(SUCCEEDED(retc0))
      {
         prod_var = -1L; // 1L;

         dwBufLen = sizeof(prod_var);
         retw = RegQueryValueEx(hKey, "Installed", NULL, &dwValType, (LPBYTE)&prod_var, &dwBufLen);
         if((dwValType != REG_DWORD) || (retw!=ERROR_SUCCESS))
         {
            prod_var = -1L; // 1L; // 0L;
//          retc0 = KP_E_KWD_NOT_FOUND;
#ifdef Debug
            KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         }
      }

      if(hKey)
      {
         retw = RegCloseKey(hKey);
//       if(retw != ERROR_SUCCESS) retc0 = KP_E_KWD_NOT_FOUND;
#ifdef Debug
         if(retw != ERROR_SUCCESS)
            KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         hKey = NULL;
      }

// --------------------------
      retc0 = S_OK;

      retw = RegOpenKeyEx(HKEY_CURRENT_USER,
            (LPCTSTR)key_name,
            0, KEY_QUERY_VALUE, &hKey);
      if(retw != ERROR_SUCCESS)
      {
         retc0 = KP_E_KWD_NOT_FOUND;
         hKey = NULL;
#ifdef Debug
         KpErrorProc.OutputErrorMessage(KP_E_KWD_NOT_FOUND, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
      }

      if(SUCCEEDED(retc0))
      {
         prod_var_local = -1L; // 1L;

         dwBufLen = sizeof(prod_var);
         retw = RegQueryValueEx(hKey, "Installed", NULL, &dwValType, (LPBYTE)&prod_var_local, &dwBufLen);
         if((dwValType != REG_DWORD) || (retw != ERROR_SUCCESS))
         {
            prod_var_local = -1L; // 1L; // 0L;
//          retc0 = KP_E_KWD_NOT_FOUND;
#ifdef Debug
            KP_WARNING(KP_E_KWD_NOT_FOUND, retw);
#endif
         }
      }

      if(hKey)
      {
         retw = RegCloseKey(hKey);
//       if(retw != ERROR_SUCCESS) retc0 = KP_E_KWD_NOT_FOUND;
#ifdef Debug
         if(retw != ERROR_SUCCESS)
            KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, KP_TRACE_WINDOW);
#endif
         hKey = NULL;
      }

// ---------------------
#if FALSE
char str_buf[100];
sprintf(str_buf, "prod_ver: %d, prod_var_local: %d, prod_var: %d", prod_ver, prod_var_local, prod_var);
KpMsgOut(str_buf, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

iProdVerGlob = prod_ver = 3012;
#endif

// PutLogMessage_("KpStApp::GetProdVarReg(): prod_ver: %d  prod_var: %d  prod_var_local: %d  iUpdNumGlob: %d", prod_ver, prod_var, prod_var_local, iUpdNumGlob);

      if(prod_var_local > prod_var) prod_var = prod_var_local;

      if(iUpdNumGlob > prod_var) prod_var = iUpdNumGlob;

   /* if(prod_var > 0L) */ prod_var--; // mano update numeriai nuo 1, Tado ir Gintaro - nuo 0 (-1 – produktas neádiegtas)
// prod_var = 2; // 9; //
   }

   if(SUCCEEDED(retc)) m_ProdVar = prod_var;

// PutLogMessage_("KpStApp::GetProdVarReg(): m_ProdVar: %d", m_ProdVar);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetProdVarRegTmp(int iProdVer, int *piProdVar)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;

int prod_ver_sav = 0;
int prod_var_sav = m_ProdVar;

   KP_ASSERT(piProdVar != NULL, E_INVALIDARG, null, True);

// ----------------- iðsaugojam ProdVer
   if(SUCCEEDED(retc)) retc = GetIniProdVer(&prod_ver_sav);

   if(SUCCEEDED(retc))
   {
// ----------------- ieðkom ProdVar
      if(SUCCEEDED(retc)) retc = SetIniProdVer(iProdVer);

      if(SUCCEEDED(retc)) retc = GetProdVarReg();

      if(SUCCEEDED(retc)) *piProdVar = m_ProdVar;

// ----------------- atstatom
      if(SUCCEEDED(retc0)) retc0 = GetIniProdVer(&prod_ver_sav);
      if(SUCCEEDED(retc)) retc = retc0;

   } // if(SUCCEEDED(retc))

   m_ProdVar = prod_var_sav;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::GetProdDir(unsigned char *lpszProdDir)
{
HRESULT retc=S_OK;
static unsigned char user_path[KP_MAX_FNAME_LEN+1]; // darbinis laukas, ið pradþiø po aplikacijos pakatalogius, po to po atmintukà
static unsigned char app_dir[KP_MAX_FNAME_LEN+1]; // aplikacijos pakatalogis su kpstart.exe ("Matematika Tau-5E mokytojui")
/* const */ unsigned char *pnts = NULL;
unsigned char *pntd = NULL;

   KP_ASSERT(lpszProdDir, E_INVALIDARG, True, null);

// if(SUCCEEDED(retc)) retc = GetAppPath(user_path, False); // "I:\\Matematika Tau-5E mokytojui" CD dalyje
// nesuveikia, kai yra m_Ini.m_bSubst – tada darbinis katalogas yra ðakninis, be pakatalogiø
   KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)user_path), KP_E_SYSTEM_ERROR, GetLastError(), True);

// if(SUCCEEDED(retc)) strcpy(user_path, m_lpszFlashDevName);
// user_path[2] = Nul; // trinam '\\' gale ("I:\\")
// if(SUCCEEDED(retc)) retc = GetAppName(app_full_path);
// if(SUCCEEDED(retc)) retc = TvFnameSplit(app_disk, app_path, app_fname, app_ftype, app_full_path);

   app_dir[0] = Nul;
   if(/* app_path[0] && */ SUCCEEDED(retc)) // o kam tikrinti app_path[0]??? visada juk bent jau "\\"
   {
      pnts = strchr(user_path, '\\'); // "\\Matematika Tau-5E mokytojui" CD dalyje
      if(pnts == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
      {
         while(pnts)
         {
            pntd = pnts; // atsimenam vienu þemesná pakatalogá
            pnts = strchr(pnts+1, '\\');
         }
         strcpy(app_dir, pntd + 1); // "Matematika Tau-5E mokytojui" CD dalyje // atsimenam, kur reikës padëti data failà, vienu giliau // atsimenam vëlesniam ákomponavimui á JS

//       *pntd = Nul;
      }
   }

   if(lpszProdDir && SUCCEEDED(retc)) strcpy(lpszProdDir, app_dir);

return(retc);
}


// -------------------------------------------
#if FALSE
HRESULT KpStApp::InitUserFileList(void)
{
HRESULT retc=S_OK;
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;
static unsigned char vol_name[KP_MAX_FNAME_LEN+1];

static unsigned char app_disk[KP_MAX_FNAME_LEN+1];
static unsigned char app_path[KP_MAX_FNAME_LEN+1];
static unsigned char app_fname[KP_MAX_FNAME_LEN+1];
static unsigned char app_ftype[KP_MAX_FTYPE_LEN+1];

static unsigned char app_dir[KP_MAX_FNAME_LEN+1]; // aplikacijos pakatalogis su kpstart.exe ("Matematika Tau-5E mokytojui")
static unsigned char user_path[KP_MAX_FNAME_LEN+1]; // darbinis laukas, ið pradþiø po aplikacijos pakatalogius, po to po atmintukà
static unsigned char user_fmask[KP_MAX_FNAME_LEN+1];
static unsigned char user_full_path[KP_MAX_FNAME_LEN+1];
static unsigned char dat_fname[KP_MAX_FNAME_LEN+1];
/* const */ unsigned char *pnts = NULL;
unsigned char *pntd = NULL;
KpFStream *p_out_file = NULL;
unsigned char *file_buf = NULL;
// int cnt;
static unsigned char file_names[KP_MAX_FNAME_LEN+1];
static unsigned char pages[KP_MAX_FNAME_LEN+1];
KpString data_str;
KpString out_str;
filebuf fb;
KpInStream *in_file_ptr = NULL;
XmlTagPars *data_rec = NULL;
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
static unsigned char atm_kod_fdf[MAX_XML_PAR_VAL_LEN + 1];
unsigned char atm_kod[TV_TAG_LEN + 1];
int par_num;
bool skip_file = False;
KpString atm_kod_str;
KpString file_name_str;
// bool found = False;
bool check_flash = False;
bool subst = False;

// ----------------------------
   if(SUCCEEDED(retc)) retc = GetIniVolName(vol_name);
   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);
   if(SUCCEEDED(retc)) retc = GetIniSubst(&subst);

// ------------------------------ kopijuojam tik atmintukinius
   if(check_flash && // jei ir atmintukinis, bet nepririðtas, tai nëra kur kopijuoti – nëra galimybës surasti atmintukinæ dalá
      (!subst) && // jei setupinis, tai blogai bent jau kai subst'intas – darbinis katalogas ðakninis, nerandam produkto pakatalogio
      SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = GetProdDir(app_dir);

      if(SUCCEEDED(retc)) retc = GetAtmKodTxt(atm_kod);

//    KpMsgOut(atm_kod, IDI_INFORMATION /* IDI_ASTERISK */, KP_MB_TESTI);

// ----------------------------
      if(SUCCEEDED(retc))
      {
         file_names[0] = Nul;
         pages[0] = Nul;
      }

      if(SUCCEEDED(retc))
      {
         strcpy(user_path, m_lpszFlashDevName); // "E:" Flash dalis
         pntd = user_path + strlen(user_path);

         strcpy(pntd, "\\Mano_");
         strcat(pntd, vol_name); // user_path: "E:\\Mano_MaTau5e" Flash dalyje
      }

      if(SUCCEEDED(retc))
      {
         strcpy(user_fmask, user_path);
         strcat(user_fmask, "\\*.fdf"); // "E:\\Mano_MaTau5e\\*.fdf" Flash dalyje
      }

// ----------------------------------------------------------------------------------
//    found = False;

      if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)user_fmask, &file_data);
      if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {
         retw = GetLastError();
         if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
            KP_ERROR(KP_E_SYSTEM_ERROR, retw);
      }
      if(/* (enumeration != INVALID_HANDLE_VALUE) && */ SUCCEEDED(retc))
      {
//       found = True;
// ------------------------
//       file_names_array = ["x7_1.pdf", "x7.pdf", "matavimo_vienetai_t.pdf"];
//       pages_array = [6,4,5];

         strcpy(file_names, "file_names_array = [");
         strcpy(pages, "pages_array = [");

         if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
         {
//          cnt = 1;
            if(SUCCEEDED(retc)) do
            {
               skip_file = False;

               strcpy(user_full_path, user_path);
               strcat(user_full_path, "\\");
               strcat(user_full_path, file_data.cFileName);

// ---------------------------------- skaitom .fdf su JavaScriptu
#if FALSE
               file_buf = NULL;
               if(SUCCEEDED(retc)) retc = ReadFileContents(user_full_path, &file_buf, NULL, True, False);
               if(SUCCEEDED(retc)) retc = SpcEolToSpc(file_buf);
#else
               if(SUCCEEDED(retc))
                  if(!fb.open((const char *)user_full_path, ios::in))
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_NOT_FOUND, user_full_path, True, __FILE__, __LINE__, 0L, NULL);

               KP_NEW(in_file_ptr, KpInStream(&fb));

               data_rec = NULL;
               if(SUCCEEDED(retc))
               {
// PutLogMessage_("InitUserFileList() 1: %s", user_full_path);
                  retc = GetKpstFdfDataRec(&data_rec, in_file_ptr, FdfInputFdf);
// PutLogMessage_("InitUserFileList() 2:");
                  if(SUCCEEDED(retc))
                  {
                     if(data_rec == NULL)
                     {
                        retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, user_full_path, False, __FILE__, __LINE__, 0L, NULL);
                        skip_file = True;
                     }
                  }
                  else
                  {
                     retc = S_OK;
                     skip_file = True;
                  }
               }

               if((!skip_file) && SUCCEEDED(retc))
               {
                  retc = data_rec->SeekTextPar("JavaScript", par_val, &par_num);
                  if(retc == KP_E_KWD_NOT_FOUND)
                  {
                     retc=KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, user_full_path, False, __FILE__, __LINE__, 0L, NULL);
                     skip_file = True;
                  }
               }

               KP_DELETE(data_rec);

               fb.close();

               KP_DELETE(in_file_ptr);

               file_buf = par_val;
#endif
               if((!skip_file) && SUCCEEDED(retc)) retc = RemoveSpacesCode(file_buf);

// ----------------- iðtraukiam atm. kodà ið .fdf
               if((!skip_file) && SUCCEEDED(retc))
               {
                  pnts = strstr(file_buf, "varAN=");
                  if(pnts != NULL) pnts += strlen("varAN=");
                  else
                  {
                     retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, user_full_path, False, __FILE__, __LINE__, 0L, NULL);
                     skip_file = True;
                  }
               }
               atm_kod_fdf[0] = Nul;
               if((!skip_file) && SUCCEEDED(retc)) retc = ExtractStringLitteral(atm_kod_fdf, pnts);

               if((!skip_file) && SUCCEEDED(retc))
               {
                  atm_kod_str = (const char *)atm_kod_fdf;
                  file_name_str = file_data.cFileName;

                  retc = EncAtmKod(&atm_kod_str, file_name_str);
                  if(SUCCEEDED(retc)) strcpy(atm_kod_fdf, atm_kod_str.ExtractUnsignedValueA());

// KpMsgOutF_2(">>>%s<<< >>>%s<<<", atm_kod_fdf, atm_kod);

               }

// --------------- tikrinam, ar ðito atmintuko failai
               if((!skip_file) && SUCCEEDED(retc))
                 if((strcmp(atm_kod_fdf, atm_kod) != 0) && (strcmp(atm_kod_fdf, "000-000000") != 0)) skip_file = True;

// KpMsgOutF_1("%d", skip_file);

// ----------------- iðtraukiam puslapius ið .fdf
               if((!skip_file) && SUCCEEDED(retc))
               {
                  pnts = strstr(file_buf, "varpsl=");
                  if(pnts != NULL) pnts += strlen("varpsl=");
                  else
                  {
                     retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, user_full_path, False, __FILE__, __LINE__, 0L, NULL);
                     skip_file = True;
                  }
               }
               if((!skip_file) && SUCCEEDED(retc))
               {
                  pntd = strchr(pnts, ';'); // Lf);
                  if(pntd != NULL) *pntd = Nul;
                  else
                  {
                     retc = KpErrorProc.OutputErrorMessage(KP_E_FILE_FORMAT, user_full_path, False, __FILE__, __LINE__, 0L, NULL);
                     skip_file = True;
                  }
               }
               if((!skip_file) && SUCCEEDED(retc)) retc = RemoveSpaces(pnts);

               if((!skip_file) && SUCCEEDED(retc))
               {
                  strcat(pages, pnts);
                  strcat(pages, ",");
               }

//             KP_DELETEA(file_buf);
// ----------------------------------

// ----------------- konstruojam .pdf failo vardà
               if((!skip_file) && SUCCEEDED(retc)) retc = TvFnameSplit(app_disk, app_path, app_fname, app_ftype, (const unsigned char *)file_data.cFileName);

               if((!skip_file) && SUCCEEDED(retc))
               {
                  strcat(file_names, "\"");
                  strcat(file_names, app_fname);
                  strcat(file_names, KPST_PDF_FILE_TYPE);
                  strcat(file_names, "\",");
               }

// ------------------
               retw = ERROR_SUCCESS;
               if(SUCCEEDED(retc))
                  if(!FindNextFile(enumeration, &file_data))
                  {
                     retw = GetLastError();
                     if(retw == ERROR_NO_MORE_FILES)
                     {
                        // retc = KP_E_FILE_NOT_FOUND;
                     }
                     else
                        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
                  }

//             cnt++;

//          } while(SUCCEEDED(retc));
            } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));
//          if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;

         } // if(enumeration != INVALID_HANDLE_VALUE)

         if(SUCCEEDED(retc)) if(strlen(pages) > 0) if(pages[strlen(pages) - 1] == ',') pages[strlen(pages) - 1] = Nul;
         if(SUCCEEDED(retc)) strcat(pages, "];");

         if(SUCCEEDED(retc)) if(strlen(file_names) > 0) if(file_names[strlen(file_names) - 1] == ',') file_names[strlen(file_names) - 1] = Nul;
         if(SUCCEEDED(retc)) strcat(file_names, "];");

      } // if(SUCCEEDED(retc)) // if(enumeration != INVALID_HANDLE_VALUE)

      if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {
         if(!FindClose(enumeration))
            /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         enumeration = INVALID_HANDLE_VALUE;

      } // if(enumeration != INVALID_HANDLE_VALUE)


// -----------------------------------------------------
      if(/* found && */ SUCCEEDED(retc))
      {
//       if(SUCCEEDED(retc)) retc = TvFnameSplit(app_disk, app_path, app_fname, app_ftype, user_path);
         if(SUCCEEDED(retc))
         {
//          strcpy(dat_fname, user_path);
//          strcpy(dat_fname, app_disk);
            strcpy(dat_fname, m_lpszFlashDevName); // "E:" Flash dalis
            strcat(dat_fname, "\\");
            strcat(dat_fname, app_dir);
            strcat(dat_fname, "\\");
            strcat(dat_fname, vol_name);
            strcat(dat_fname, KPST_FDF_DATA_FTYPE); // ".dat"); // "E:\\Matematika Tau-5E mokytojui\\MaTau5e.dat"
         }

         KP_NEW(p_out_file, KpFStream((const char *)dat_fname, ios::out));

         if(SUCCEEDED(retc))
         {
            data_str =  "for(var i = this.numFields-1; i > -1; i--)\n"
                        "{var fn = this.getNthFieldName(i);\n"
                        "if(fn.indexOf(\"Mano_pdf\") > -1)\n"
                        "{\n"
                        "this.removeField(fn)\n"
                        "}\n"
                        "}\n"

//                      "var file_path = this.path;\n"
                        "var file_path = \"";
            data_str += (const char *)m_lpszFlashDevName; // "E:"
            data_str += "/\";\n";

//                      "var pos=file_path.indexOf(\"";
//          data_str += (const char *)app_dir; // "Matema"
//          data_str += "\");\n";
            data_str += "var pos = 4;\n";

            data_str += "var file_names_array = new Array();\n"
                        "var pages_array = new Array();\n"

//                      "// uzpildo programa\n"
                        "//\n";

            data_str += (const char *)file_names;
            data_str += "\n";

            data_str += (const char *)pages;
            data_str += "\n";

            data_str += "//\n"
                        "for (var i=0; i<pages_array.length; i++)\n"
                        "{\n"
                        "var psl=pages_array[i];\n"
                        "var file_path1=file_path.substring(0,pos)+\"Mano_";
            data_str += (char *)vol_name;
            data_str += "/\"+file_names_array[i];\n"
                        "var ff1=this.addField(\"Mano_pdf_\"+psl, \"button\", psl, [0,30,30,60]);\n"
                        "ff1.setAction(\"MouseUp\", \"app.openDoc(\'\"+file_path1+\"\')\");\n"
                        "ff1.borderStyle = border.s;\n"
                        "ff1.highlight = \"none\";\n"
                        "ff1.textSize = 0;\n"
                        "ff1.textColor = color.red;\n"
                        "ff1.fillColor = color.white;\n"
                        "ff1.textFont = font.ZapfD;\n"
                        "ff1.buttonSetCaption(\"\\052\");\n"
                        "ff1.userName = file_names_array[i];\n"
                        "}\n"
                        "//\n";

            retc = StrToA85(&out_str, data_str);
            if(FAILED(retc))
               retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L);
         }

         if(SUCCEEDED(retc))
         {
            *p_out_file << "%FDF-1.2" << endl;
            *p_out_file << "1 0 obj" << endl;
            *p_out_file << "<< /FDF << /JavaScript <<" << endl;
            *p_out_file << "  /Doc    2 0 R >> >> >>" << endl;
            *p_out_file << "endobj" << endl;
            *p_out_file << "2 0 obj" << endl;
            *p_out_file << "[ (mano_pdf) 3 0 R" << endl;
            *p_out_file << "]" << endl;
            *p_out_file << "endobj" << endl;
            *p_out_file << "3 0 obj" << endl;

//          *p_out_file << "<<>>" << endl;
            *p_out_file << "<</Filter[/A85]>>" << endl;

            *p_out_file << "stream" << endl;

KpString str_tmp(out_str.substr(2, out_str.length() - 2));
            *p_out_file << str_tmp.ExtractValueA() << ">" << endl;

            *p_out_file << "endstream" << endl;
            *p_out_file << "endobj" << endl;
            *p_out_file << "trailer" << endl;
            *p_out_file << "<< /Root 1 0 R >>" << endl;
            *p_out_file << "%%EOF" << endl;
         }

// -----------------
         if(p_out_file != NULL) p_out_file->close();

         KP_DELETE(p_out_file);

// -----------------------------------------------------
      } // if(found && SUCCEEDED(retc))

      if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;

   } // if(check_flash && (!subst) && SUCCEEDED(retc))

return(retc);
}
#endif


// -------------------------------------------
#if FALSE
HRESULT KpStApp::CopyUpdateDat(void)
{
HRESULT retc = S_OK;
static unsigned char app_dir[KP_MAX_FNAME_LEN+1]; // aplikacijos pakatalogis su kpstart.exe ("Matematika Tau-5E mokytojui")
static unsigned char user_file[KP_MAX_FNAME_LEN+1];
bool check_flash = False;
bool subst = False;

// ----------------------------
   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);
   if(SUCCEEDED(retc)) retc = GetIniSubst(&subst);

// ------------------------------ kopijuojam tik atmintukinius
   if(check_flash && // jei ir atmintukinis, bet nepririðtas, tai nëra kur kopijuoti – nëra galimybës surasti atmintukinæ dalá
      (!subst) && // jei setupinis, tai blogai bent jau kai subst'intas – darbinis katalogas ðakninis, nerandam produkto pakatalogio
      SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = GetProdDir(app_dir);

      if(SUCCEEDED(retc))
         if(strlen(m_lpszFlashDevName) + 1 + strlen(app_dir) + 1 + strlen(KPSTART_UPDATE_DAT) >= KP_MAX_FNAME_LEN)
            KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

      if(SUCCEEDED(retc))
      {
         strcpy(user_file, m_lpszFlashDevName);
         strcat(user_file, "\\");
         strcat(user_file, app_dir);
         strcat(user_file, "\\");
         strcat(user_file, KPSTART_UPDATE_DAT);

         if(!SetFileAttributes((const char *)user_file, FILE_ATTRIBUTE_NORMAL))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
         }

         if(!CopyFile(KPSTART_UPDATE_DAT, (const char *)user_file, False))
         {
#ifdef Debug
            retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
         }
      }

   } // if(check_flash && (!subst) && SUCCEEDED(retc))

return(retc);
}
#endif


// ---------------------------------------------------------
// kopijuoja kpscalc.exe ir KPSCLC.EXE á atmintukà
// perdaryti visus atmintukinius produktus per EX_1=kpscalc&calc=
// tada CopyCalcFiles() bus galima iðmesti
// Waldek MIMOK6 jau
// Dar trûksta:
//    MaTau6e atmintukinio
//    MaTau7e atmintukinio
HRESULT KpStApp::CopyCalcFiles(void)
{
HRESULT retc = S_OK;
static unsigned char app_dir[KP_MAX_FNAME_LEN+1]; // aplikacijos pakatalogis su kpstart.exe ("Matematika Tau-5E mokytojui")
static unsigned char user_file[KP_MAX_FNAME_LEN+1];
unsigned char *pntd = NULL;
bool check_flash = False;
bool subst = False;

   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);
   if(SUCCEEDED(retc)) retc = GetIniSubst(&subst);

   if(check_flash && // jei ir atmintukinis, bet nepririðtas, tai nëra kur kopijuoti – nëra galimybës surasti atmintukinæ dalá
      (!subst) && // jei setupinis, tai blogai bent jau kai subst'intas – darbinis katalogas ðakninis, nerandam produkto pakatalogio
      SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = GetProdDir(app_dir);

      if(SUCCEEDED(retc))
         if(strlen(m_lpszFlashDevName) + 1 + strlen(app_dir) + 1 + strlen(KPSTART_KPSCALC_EXE) >= KP_MAX_FNAME_LEN)
            KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

      if(SUCCEEDED(retc))
      {
         strcpy(user_file, m_lpszFlashDevName);
         strcat(user_file, "\\");
         strcat(user_file, app_dir);
         if(app_dir[0]) strcat(user_file, "\\"); // antras sleðas, tik jei app_dir netuðèias

         pntd = user_file + strlen(user_file);

         strcpy(pntd, KPSTART_KPSCALC_EXE);

         if(!SetFileAttributes((const char *)user_file, FILE_ATTRIBUTE_NORMAL))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
         }

         if(!CopyFile(KPSTART_KPSCALC_EXE, (const char *)user_file, False))
         {
#ifdef Debug
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
         }

         strcpy(pntd, KPSTART_KPSCLC_EXE);

         if(!SetFileAttributes((const char *)user_file, FILE_ATTRIBUTE_NORMAL))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
         }

         if(!CopyFile(KPSTART_KPSCLC_EXE, (const char *)user_file, False))
         {
#ifdef Debug
//          retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
         }

      } // if(SUCCEEDED(retc))

   } // if((!check_flash) && (!subst) && SUCCEEDED(retc))

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::DelUserJscriptsSingle(const unsigned char *lpszFMask)
{
HRESULT retc = S_OK;
static unsigned char dest_path[KP_MAX_FNAME_LEN+1];
static unsigned char dest_fmask[KP_MAX_FNAME_LEN+100];
static unsigned char dest_file[KP_MAX_FNAME_LEN+1];
static unsigned char glob_js_fname[KP_MAX_FNAME_LEN+1];
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;

// ----------------------------------------------------------------------------------
   if(SUCCEEDED(retc)) retc = GetGlobalJsName(glob_js_fname, dest_path);
   if(SUCCEEDED(retc))
   {
      strcpy(dest_fmask, dest_path);
      strcat(dest_fmask, lpszFMask);
   }

// ----------------------------------------------------------------------------------
   if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)dest_fmask, &file_data);
   if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      retw = GetLastError();
      if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
         KP_ERROR(KP_E_SYSTEM_ERROR, retw);
   }
   if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) do
      {
         if(strcmp(file_data.cFileName, GLOB_JS_FILE_NAME) != 0)
         {
            if(SUCCEEDED(retc)) if(strlen(dest_path) + 1 + strlen(file_data.cFileName) >= KP_MAX_FNAME_LEN)
               KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

            if(SUCCEEDED(retc))
            {
               strcpy(dest_file, dest_path);
               strcat(dest_file, "\\");
               strcat(dest_file, file_data.cFileName);
            }

            if(SUCCEEDED(retc)) if(!SetFileAttributes((const char *)dest_file, FILE_ATTRIBUTE_NORMAL))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) if(!DeleteFile((const char *)dest_file))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            }

         } // if(strcmp(file_data.cFileName, GLOB_JS_FILE_NAME) != 0)

// ---------------
         retw = ERROR_SUCCESS;
         if(SUCCEEDED(retc))
            if(!FindNextFile(enumeration, &file_data))
            {
               retw = GetLastError();
               if(retw == ERROR_NO_MORE_FILES)
               {
               // retc = KP_E_FILE_NOT_FOUND;
               }
               else
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
            }

      } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// ---------------
      if(!FindClose(enumeration))
         /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
      enumeration = INVALID_HANDLE_VALUE;

   } // if(enumeration != INVALID_HANDLE_VALUE)

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::DelAllUserJscripts(void)
{
HRESULT retc = S_OK;

   if(SUCCEEDED(retc)) retc = DelUserJscriptsSingle((const unsigned char *)"\\*.js");
   if(SUCCEEDED(retc)) retc = DelUserJscriptsSingle((const unsigned char *)"\\*.jss");
// if(SUCCEEDED(retc)) retc = DelUserJscriptsSingle((const unsigned char *)"\\JSByteCodeWin.bin");

return(retc);
}


HRESULT KpStApp::CopyUserJscriptsSingle(const unsigned char *lpszUserPath, const unsigned char *lpszFMask)
{
HRESULT retc = S_OK;
unsigned char acro_vers = Nul;
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
static unsigned char user_path[KP_MAX_FNAME_LEN+1]; // darbinis laukas, aplikacijos pakatalogis atmintuke
static unsigned char user_fmask[KP_MAX_FNAME_LEN+100];
static unsigned char user_full_path[KP_MAX_FNAME_LEN+1];
static unsigned char glob_js_fname[KP_MAX_FNAME_LEN+1];
static unsigned char dest_path[KP_MAX_FNAME_LEN+1];
static unsigned char dest_file[KP_MAX_FNAME_LEN+1];
HANDLE enumeration = INVALID_HANDLE_VALUE;
WIN32_FIND_DATA file_data;
DWORD retw = ERROR_SUCCESS;

// ----------------------------------------------------------------------------------
   KP_ASSERT(lpszUserPath, E_INVALIDARG, True, null);

   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);

   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD50_PATHNAME)) acro_vers = '5';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME)) acro_vers = '6';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT)) acro_vers = 'S';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD70_PATHNAME)) acro_vers = '7';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT)) acro_vers = 'N';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD80_PATHNAME)) acro_vers = '8';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT)) acro_vers = 'A';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD90_PATHNAME)) acro_vers = '9';
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT)) acro_vers = 'F';

   if(acro_vers && SUCCEEDED(retc))
   {
// ----------------------------------------------------------------------------------
      if(SUCCEEDED(retc))
         if(strlen(lpszUserPath) + 1 + strlen(KPST_ACROREAD60_PATHNAME) + 1 + strlen(JS_SUB_PATH_3) + 5 >= KP_MAX_FNAME_LEN)
            KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

      if(SUCCEEDED(retc))
      {
         strcpy(user_path, lpszUserPath);
         strcat(user_path, "\\"); // user_path: "E:\\Matematika Tau-5E mokytojui\\AcroRead602\\Reader\\Javascripts" flash dalyje
         switch(acro_vers)
         {
         case '5': strcat(user_path, KPST_ACROREAD50_PATHNAME); break;
         case '6': strcat(user_path, KPST_ACROREAD60_PATHNAME); break;
         case 'S': strcat(user_path, KPST_ACROREAD60_PATHNAME_SHORT); break;
         case '7': strcat(user_path, KPST_ACROREAD70_PATHNAME); break;
         case 'N': strcat(user_path, KPST_ACROREAD70_PATHNAME_SHORT); break;
         case '8': strcat(user_path, KPST_ACROREAD80_PATHNAME); break;
         case 'A': strcat(user_path, KPST_ACROREAD80_PATHNAME_SHORT); break;
         case '9': strcat(user_path, KPST_ACROREAD90_PATHNAME); break;
         case 'F': strcat(user_path, KPST_ACROREAD90_PATHNAME_SHORT); break;
         }
         strcat(user_path, "\\");
         strcat(user_path, JS_SUB_PATH_3);

         strcpy(user_fmask, user_path);
         strcat(user_fmask, lpszFMask); // "E:\\Matematika Tau-5E mokytojui\\AcroRead602\\Reader\\Javascripts\\*.js" Flash dalyje
      }

// ----------------------------------------------------------------------------------
      if(SUCCEEDED(retc)) enumeration = FindFirstFile((const char *)user_fmask, &file_data);
      if((enumeration == INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {
         retw = GetLastError();
         if((retw != ERROR_FILE_NOT_FOUND) && (retw != ERROR_PATH_NOT_FOUND) && (retw != ERROR_NO_MORE_FILES))
            KP_ERROR(KP_E_SYSTEM_ERROR, retw);
      }
      if((enumeration != INVALID_HANDLE_VALUE) && SUCCEEDED(retc))
      {
//       appdata_dir = (unsigned char *)getenv("APPDATA");
//       KP_ASSERT(appdata_dir, KP_E_SYSTEM_ERROR, GetLastError(), True);

         if(SUCCEEDED(retc)) retc = GetGlobalJsName(glob_js_fname, dest_path);

         if(SUCCEEDED(retc)) do
         {
// ------------------
            if(SUCCEEDED(retc)) if(strlen(user_path) + 1 + strlen(file_data.cFileName) >= KP_MAX_FNAME_LEN)
               KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

            if(SUCCEEDED(retc))
            {
               strcpy(user_full_path, user_path);
               strcat(user_full_path, "\\");
               strcat(user_full_path, file_data.cFileName);
            }

            if(SUCCEEDED(retc)) if(strlen(dest_path) + 1 + strlen(file_data.cFileName) >= KP_MAX_FNAME_LEN)
               KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

            if(SUCCEEDED(retc))
            {
               strcpy(dest_file, dest_path);
               strcat(dest_file, "\\");
               strcat(dest_file, file_data.cFileName);
            }

            if(!SetFileAttributes((const char *)dest_file, FILE_ATTRIBUTE_NORMAL))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
            }

            if(SUCCEEDED(retc)) if(!CopyFile((const char *)user_full_path, (const char *)dest_file, False))
            {
#ifdef Debug
               retc=KpErrorProc.OutputErrorMessage(KP_E_FERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
#endif
            }

            if(SUCCEEDED(retc))
            {
               if(m_pUserJsList != NULL) retc = m_pUserJsList->PutToEnd(dest_file);
               else KP_NEW(m_pUserJsList, KpTreeEntry(dest_file, NULL));
            }

// ---------------
            retw = ERROR_SUCCESS;
            if(SUCCEEDED(retc))
               if(!FindNextFile(enumeration, &file_data))
               {
                  retw = GetLastError();
                  if(retw == ERROR_NO_MORE_FILES)
                  {
                  // retc = KP_E_FILE_NOT_FOUND;
                  }
                  else
                     retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, True, __FILE__, __LINE__, 0L, NULL);
               }

         } while((retw != ERROR_NO_MORE_FILES) && SUCCEEDED(retc));

// ---------------
         if(!FindClose(enumeration))
            /* retc = */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, retw, False, __FILE__, __LINE__, 0L, NULL);
         enumeration = INVALID_HANDLE_VALUE;

      } // if(enumeration != INVALID_HANDLE_VALUE)

// ---------------
   } // if(acro_vers && SUCCEEDED(retc))

return(retc);
}


HRESULT KpStApp::CopyUserJscripts(void)
{
HRESULT retc = S_OK;
static unsigned char app_dir[KP_MAX_FNAME_LEN+1]; // aplikacijos pakatalogis su kpstart.exe ("Matematika Tau-5E mokytojui")
static unsigned char user_path[KP_MAX_FNAME_LEN+1]; // darbinis laukas, aplikacijos pakatalogis atmintuke
static unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
bool check_flash = False;
bool subst = False;

   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);
   if(SUCCEEDED(retc)) retc = GetIniSubst(&subst);
   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);

// ------------------------------ kopijuojam tik atmintukinius
// if(check_flash && // jei ir atmintukinis, bet nepririðtas, tai nëra ið kur kopijuoti - nëra galimybës surasti atmintukinës dalies
//    (!subst) && // jei setupinis, tai blogai bent jau kai subst'intas - darbinis katalogas ðakninis, nerandam produkto pakatalogio
//    SUCCEEDED(retc))

// ------------------------------ kopijuojam, tik jei paleidimo komandoje yra {user} - paleidþiama ið atmintuko
// if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_USER)) // "{user}")) // negerai – reikia MIMOK instrukcijoms, o ten nëra {user}

// ------------------------------ kopijuojam, tik jei paleidimo komandoje akrobatas ne darbiniam kataloge, tada darbiniam tik java scriptai
// kai "..\\AR6\\Reader" kopijuojam, kai "AcroRead602\\Reader" – ne
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_ACROREAD_FNAME_SHORT))
      if(
         (strstr(cmd_str, KPST_ACROREAD60_PATHNAME) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD60_PATHNAME_SHORT) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD70_PATHNAME) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD70_PATHNAME_SHORT) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD80_PATHNAME) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD80_PATHNAME_SHORT) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD90_PATHNAME) != cmd_str) &&
         (strstr(cmd_str, KPST_ACROREAD90_PATHNAME_SHORT) != cmd_str)
        )
   {

// ------------------------------------------------------- kad neliktø ðiukðliø nuo seniau
      if(SUCCEEDED(retc)) retc = DelAllUserJscripts();

// ------------------------------- lokalus katalogas
      if(SUCCEEDED(retc)) retc = GetAppPath(user_path, False);
//    KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)user_path), KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc)) retc = CopyUserJscriptsSingle(user_path, (const unsigned char *)"\\*.js");
      if(SUCCEEDED(retc)) retc = CopyUserJscriptsSingle(user_path, (const unsigned char *)"\\*.jss");
      if(SUCCEEDED(retc)) retc = CopyUserJscriptsSingle(user_path, (const unsigned char *)"\\JSByteCodeWin.bin");

// ------------------------------- "E:" Flash dalis
      if(SUCCEEDED(retc)) retc = GetProdDir(app_dir);

      if(SUCCEEDED(retc))
         if(strlen(m_lpszFlashDevName) + 1 + strlen(app_dir) >= KP_MAX_FNAME_LEN)
            KP_ERROR(KP_E_BUFFER_OVERFLOW, null);

      if(SUCCEEDED(retc))
      {
         strcpy(user_path, m_lpszFlashDevName);
         strcat(user_path, "\\"); // user_path: "E:\\Matematika Tau-5E mokytojui\\AcroRead602\\Reader\\Javascripts" flash dalyje
         strcat(user_path, app_dir);
      }

      if(SUCCEEDED(retc)) retc = CopyUserJscriptsSingle(user_path, (const unsigned char *)"\\*.js");
      if(SUCCEEDED(retc)) retc = CopyUserJscriptsSingle(user_path, (const unsigned char *)"\\*.jss");
      if(SUCCEEDED(retc)) retc = CopyUserJscriptsSingle(user_path, (const unsigned char *)"\\JSByteCodeWin.bin");

   } // if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_USER)) // "{user}"))

return(retc);
}


HRESULT KpStApp::DeleteUserJscripts(void)
{
HRESULT retc = S_OK;
KpTreeEntry *js_list;
const char *file_name = NULL;

   js_list = m_pUserJsList;

   while(js_list && SUCCEEDED(retc))
   {
      file_name = (const char *)js_list->GetValue();

      if(SUCCEEDED(retc)) if(!SetFileAttributes(file_name, FILE_ATTRIBUTE_NORMAL))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      }

      if(SUCCEEDED(retc)) if(!DeleteFile(file_name))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L);
      }

//    if(SUCCEEDED(retc)) js_list->GetFirstChild(&js_list);
      if(SUCCEEDED(retc)) js_list = js_list->m_pFirstChild;
   }

return(retc);
}


// ------------------------------
HRESULT KpStApp::GetDataDatVariable(/* const */ KpString *psFileName, const unsigned char *lpszVarName, /* const */ KpString *psVarVal, bool bOutMsg)
{
HRESULT retc = S_OK;
filebuf fb;
KpInStream *in_file_ptr = NULL;
XmlTagPars *data_rec = NULL;
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1]; // ilgis reikalingas SeekTextPar()
int par_num;

// ---------------------------
   KP_ASSERT(psFileName, E_INVALIDARG, null, True);
   KP_ASSERT(lpszVarName, E_INVALIDARG, null, True);
   KP_ASSERT(psVarVal, E_INVALIDARG, null, True);

// ---------------------------
   if(SUCCEEDED(retc))
   {
      if(!fb.open(psFileName->ExtractValueA(), ios::in))
      {
         retc = KP_E_FILE_NOT_FOUND;
         if(bOutMsg) KP_ERROR(retc, null);
      }
      else
      {
         KP_NEW(in_file_ptr, KpInStream(&fb));

         if(SUCCEEDED(retc))
         {
// PutLogMessage_("GetDataDatVariable() 1: %s %s", psFileName->ExtractValueA(), lpszVarName);
            retc = GetKpstFdfDataRec(&data_rec, in_file_ptr, FdfInputFdf, bOutMsg); // !!!! TODO perdaryt GetKpstFdfDataRec(), kad neiðvedinëtø praneðimø
// PutLogMessage_("GetDataDatVariable() 2");
            if(data_rec == NULL)
            {
               retc = KP_E_FILE_FORMAT;
               if(bOutMsg) KP_ERROR(retc, null);
            }
            else if(SUCCEEDED(retc))
            {
               retc = data_rec->SeekTextPar(lpszVarName, par_val, &par_num);
               if(bOutMsg && FAILED(retc)) KP_ERROR(retc, null);
            }
         }

         KP_DELETE(data_rec);

         fb.close();

         KP_DELETE(in_file_ptr);

      } // else // if(!fb.open((const char *)dat_fname, ios::in))

   } // if(SUCCEEDED(retc))

   if(SUCCEEDED(retc)) *psVarVal = par_val;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SetDataDatVariable(/* const */ KpString *psFileName, const unsigned char *lpszVarName, /* const */ KpString *psVarVal, bool bOutMsg)
{
HRESULT retc = S_OK;
filebuf fb;
KpInStream *in_file_ptr = NULL;
KpOutStream *out_file_ptr = NULL;
XmlTagPars *dat_rec = NULL;
static unsigned char par_val[MAX_XML_PAR_VAL_LEN + 1];
int par_num;

   KP_ASSERT(psFileName, E_INVALIDARG, null, True);
   KP_ASSERT(lpszVarName, E_INVALIDARG, null, True);
   KP_ASSERT(psVarVal, E_INVALIDARG, null, True);

// -------------------------------- skaitom data.dat
   if(SUCCEEDED(retc))
      if(!fb.open(psFileName->ExtractValueA(), ios::in))
      {
         retc = KP_E_FILE_NOT_FOUND;
         if(bOutMsg) retc = KpErrorProc.OutputErrorMessage(retc, psFileName->ExtractValueA(), True, __FILE__, __LINE__, 0L, NULL);
      }

   KP_NEW(in_file_ptr, KpInStream(&fb));

   if(SUCCEEDED(retc))
   {
      dat_rec = NULL;
// PutLogMessage_("SetDataDatVariable(): %s %s", psFileName->ExtractValueA(), lpszVarName);
      retc = GetKpstFdfDataRec(&dat_rec, in_file_ptr, FdfInputFdf, bOutMsg);
   }
   if((dat_rec == NULL) && SUCCEEDED(retc))
   {
      retc = KP_E_FILE_FORMAT;
      if(bOutMsg) retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
   }

   fb.close();

   KP_DELETE(in_file_ptr);

// ----------------------------- ástatom á sàraðà
   if(SUCCEEDED(retc))
   {
      retc = dat_rec->SeekTextPar(lpszVarName, par_val, &par_num);
      if(SUCCEEDED(retc))
         retc = dat_rec->SetTextPar(par_num, psVarVal->ExtractUnsignedValueA());
      else
         if(retc == KP_E_KWD_NOT_FOUND)
            retc = dat_rec->AddTextPar(lpszVarName, psVarVal->ExtractUnsignedValueA());
   }

// ----------------------------- áraðom failà atgal
   if(SUCCEEDED(retc))
      if(!fb.open(psFileName->ExtractValueA(), ios::out | ios::binary))
      {
         retc = KP_E_DIR_ERROR;
         if(bOutMsg) retc = KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
      }

   KP_NEW(out_file_ptr, KpOutStream(&fb));

   if(SUCCEEDED(retc))
      retc = SaveKpstFdfDataRec(dat_rec, out_file_ptr, FdfOutputFdf, bOutMsg);

   if(!fb.close()) if(SUCCEEDED(retc))
   {
      retc = KP_E_FERROR;
      if(bOutMsg) retc = KpErrorProc.OutputErrorMessage(retc, psFileName->ExtractUnsignedValueA(), True, __FILE__, __LINE__, 0L, NULL);
   }

   KP_DELETE(out_file_ptr);

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::SetDataDatUserData(void)
{
HRESULT retc = S_OK;
static unsigned char user_data[KP_MAX_FILE_LIN_WDT + 1];
KpString user_data_str;
unsigned char adm_pwd[TV_TAG_LEN + 1];
KpString adm_pwd_str;
static unsigned char dat_fname[2*KP_MAX_FNAME_LEN + 1];
static unsigned char app_path[KP_MAX_FNAME_LEN + 1];
KpString dat_fname_str;
bool check_flash = False;
unsigned char *pnts;
unsigned char *pntd;

   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);
   if(check_flash && SUCCEEDED(retc))
   {
      if(SUCCEEDED(retc)) retc = GetIniUserData(user_data);
      if(SUCCEEDED(retc)) user_data_str = (const char *)user_data;

      if(SUCCEEDED(retc)) retc = GetIniAdminPwd(adm_pwd);
      if(SUCCEEDED(retc)) adm_pwd_str = (const char *)adm_pwd;

// -------------- data.dat ten pat, kur ir paleistas .exe
//    if(SUCCEEDED(retc)) retc = GetAppPath(dat_fname, False);

// -------------- data.dat atmintuko pakatalogyje
      if(SUCCEEDED(retc)) retc = GetAppPath(app_path, False);
//    KP_ASSERT(GetCurrentDirectory(KP_MAX_FNAME_LEN, (char *)app_path), KP_E_SYSTEM_ERROR, GetLastError(), True);

      if(SUCCEEDED(retc))
      {
         pnts = strchr(app_path, '\\'); // "\\Matematika Tau-5E mokytojui" –tas pats pakatalogis bus ir atmintuke
         if(pnts == NULL) KP_ERROR(KP_E_SYSTEM_ERROR, app_path)
         else
         {
            while(pnts)
            {
               pntd = pnts; // atsimenam vienu þemesná pakatalogá
               pnts = strchr(pnts + 1, '\\');
            }
         }
      }
      if(SUCCEEDED(retc))
      {
         strcpy(dat_fname, m_lpszFlashDevName);
         strcat(dat_fname, pntd);
      }

// --------------
      if(SUCCEEDED(retc))
      {
         strcat(dat_fname, "\\");
         strcat(dat_fname, KPST_FDF_DATA_FNAME);
         dat_fname_str = (const char *)dat_fname;
      }
      if(SUCCEEDED(retc)) retc = SetDataDatVariable(&dat_fname_str, (const unsigned char *)"SI", &user_data_str, False);
      if(SUCCEEDED(retc)) retc = SetDataDatVariable(&dat_fname_str, (const unsigned char *)"AI", &adm_pwd_str, False);
   }

return(retc);
}


// -------------------------------------------
// #ifndef STAND_ALONE
#ifdef KPSTTRG_DLL
extern "C" __declspec(dllexport)
#endif
BOOL CALLBACK KpStaWindowProc(
  HWND /* hwndDlg */,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM /* lParam */ // second message parameter
)
{
HRESULT retc = S_OK;
int retp;
BOOL retw = False;
bool clear_clipbrd = False;
// unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, True);
// KpMsgOutF_0("KpStaWindowProc()");

   retp = LOWORD(wParam);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_TIMER:
// if(SUCCEEDED(retc))
// KpMsgOutF_4("KpStaWindowProc(): WM_TIMER %d m_iFlashCheckTimer: %d m_iProcCmdTimer: %d m_iLicManagTimer: %d",
//    retp, theKpStAppPtr->m_iFlashCheckTimer, theKpStAppPtr->m_iProcCmdTimer, theKpStAppPtr->m_iLicManagTimer);
// KpMsgOutF_0("KpStaWindowProc(): WM_TIMER");
// PutLogMessage_("KpStaWindowProc() %d %d", retp, theKpStAppPtr->m_iRestMinsTimer);

      if(retp)
      {
         KP_ASSERT(theKpStAppPtr, KP_E_NO_FILE, null, False);
         if(theKpStAppPtr)
         {
            if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iLicManagTimer)
               retc = theKpStAppPtr->CheckLicSvr(retp);

// kpstart.exe – siunèiam pakartotiná "CD=" serveriui kpstisvr.exe – aplikacija dar gyva – pratæsiam sesijos blokavimà
            if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iSesCtrlTimer)
               /* retc = */ theKpStAppPtr->SendIPSesAlive(); // neigiamà atsakymà ignoruojam

            if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iFlashCheckTimer)
               retc = theKpStAppPtr->TestFlash();

            if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iProcCmdTimer)
            {
// procesinti spec komandas is programos
//             if(theKpStAppPtr->m_hCmdProcess || theKpStAppPtr->m_hCmdThread || theKpStAppPtr->m_lCmdThread)
               {
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->CheckClipCmd();

//                if(SUCCEEDED(retc)) retc = theKpStAppPtr->CheckSockCmd();  // dabar atskiram threade su Accept

// naikinti clipboardà, kad nekopijuotø knygø
unsigned char wnd_name[KP_MAX_FNAME_LEN + 1];
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniClearClipBrd(&clear_clipbrd);
                  if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniWndName(wnd_name);
                  if(clear_clipbrd && SUCCEEDED(retc)) retc = KpClearClipboard(HWND_DESKTOP, wnd_name);
               }
            } // if((retp==m_iProcCmdTimer) && SUCCEEDED(retc))

// ------------------------------------------------------------------
            if(SUCCEEDED(retc)) if(retp == theKpStAppPtr->m_iRestMinsTimer)
            {
// KpMsgOutF("KpStaWindowProc() WM_TIMER m_iRestMinsTimer");
PutLogMessage("KpStaWindowProc() WM_TIMER RMT");
            /* retc = */ theKpStAppPtr->ProcessRestDays();
            }

         } // if(theKpStAppPtr)

      } // if(retp)

      break;

// ----------------------
#if FALSE
   case WM_COMMAND:
PutLogMessage_("KpStaWindowProc() WM_COMMAND: %d %ld", retp, lParam);
      switch(retp)
      {
// èia ateina tik belangëse aplikacijose (tux_ipa, XFS)
// kpstart aplikacijose suvalgo ankstesni praneðimø imtuvai
      case KPST_ID_REST_DAYS_EXCEEDED:
         if(lParam <= KPST_REST_DAYS_WARNING)
         {
            if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

            if(lParam <= 0L)
            {
static unsigned char str_buf[2000];
               sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
               KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
               KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
               retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
            }
            else
            {
               if(SUCCEEDED(retc))
               {
                  if(!RestDaysWarningShowed())
                  {
                     switch(msg.lParam)
                     {
                     case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
                     case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
                     default: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, msg.lParam); break;
                     }
                  }
//                m_iRestDaysWarningShowed = True;
                  KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
               }
            }
         }
         break;
      }
      break;
#endif
   }

   retw |= FAILED(retc);

   if(retw) PostQuitMessage(IDABORT);

if(FAILED(retc)) PutLogMessage_("KpStaWindowProc() XX: %x %d", retc, retw);

return(retw);
}
// #endif // #ifndef STAND_ALONE



// -------------------------------------------
HRESULT KpStApp::GetServerPort(int *piPort)
{
HRESULT retc = S_OK;

   KP_ASSERT(piPort, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) retc = GetIniProdVer(piPort);
   if(SUCCEEDED(retc)) if(*piPort < KP_MIN_USER_PORT) *piPort += KP_MIN_USER_PORT;

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::RetrieveLicServerSingle(unsigned char *lpszIpAddrBuf, int iAddrBufSize,  int iPort, const unsigned char *lpszBroadcastAddr)
{
HRESULT retc = S_OK;
KpSocket *sock_ptr = NULL;
KpSocket *sock_in_ptr = NULL;
// #define sock_in_ptr sock_ptr

long ll = 0;
static unsigned char http_adr[KP_MAX_FNAME_LEN + 1];
static unsigned char msg_buf[KP_MAX_FNAME_LEN + 1];

   KP_NEWO(sock_ptr, KpSocket(SOCK_DGRAM));

   if(SUCCEEDED(retc))
   {
      sprintf((char *)http_adr, "http://%s:%d/", lpszBroadcastAddr, iPort + KP_UDP_PORT_OFFSET); // "http://255.255.255.255:13106/"
      retc = sock_ptr->Resolve(http_adr, True); // False);
   }

// if(SUCCEEDED(retc)) retc = sock_ptr->Connect(False);

// siunciam klausimà broadcastu
   if(SUCCEEDED(retc))
   {
//    retc = sock_ptr->SendHttpRequest(HTTP_GET_REQUEST_CMD,
//          (const unsigned char *)"/anybody", False);
//    retc = sock_ptr->SendMsg(KPSTLSVR_REQUEST, strlen(KPSTLSVR_REQUEST), False);
      retc = sock_ptr->SendTo(KPSTLSVR_REQUEST, strlen(KPSTLSVR_REQUEST), False); // True); //
   }
// if(FAILED(retc)) KpMsgOutF("sent %d", retc);

// KP_DELETE(sock_ptr);

// ---------------------------------- priëmimo dalis
#if TRUE // FALSE
   KP_NEWO(sock_in_ptr, KpSocket(SOCK_DGRAM));

// if(FAILED(retc)) KpMsgOutF("po new KpSocket %d", retc);
#endif

// keièiam portà, nes Vistoj tuo paèiu adresu/portu leidþia tik vienà sujungimà
// if(SUCCEEDED(retc)) retc = sock_in_ptr->Bind(iPort + KP_UDP_PORT_OFFSET, INADDR_ANY, False); // ADDR_ANY);
   if(SUCCEEDED(retc)) retc = sock_in_ptr->Bind(iPort + KP_UDP_PORT_OFFSET * 2, INADDR_ANY, False); // True); //

// if(FAILED(retc)) KpMsgOutF("po Bind %d", retc);

// laukiam atsakymo
   if(SUCCEEDED(retc))
   {
      ll = KP_MAX_FNAME_LEN;
//    if(SUCCEEDED(retc)) retc = sock_in_ptr->RcvHttpMsg(msg_buf, &ll, False);
//    if(SUCCEEDED(retc)) retc = sock_in_ptr->ReceiveMsg(msg_buf, &ll, True, False);
//    if(SUCCEEDED(retc)) retc = sock_in_ptr->RecvFrom(msg_buf, &ll, False);
      if(SUCCEEDED(retc)) retc = sock_in_ptr->RecvFromAsynch(msg_buf, &ll, False); // True); //

      if(SUCCEEDED(retc))
      {
         if(ll > KP_MAX_FNAME_LEN) ll = KP_MAX_FNAME_LEN;
         msg_buf[ll] = Nul;
// KpMsgOutF("received %d %s", ll, msg_buf);

         if(strcmp(msg_buf, KPSTLSVR_ANSWER_OK) == 0)
         {
// serveris atsiliepë – keièiam adresà
// KpMsgOutF("keièiam %s á %s", lpszIpAddrBuf, sock_in_ptr->m_PackedUrl.lpszServerName);
// PutLogMessage_("%s, keièiam %s á %s", lpszBroadcastAddr, lpszIpAddrBuf, sock_in_ptr->m_PackedUrl.lpszServerName);
            KP_ASSERT(strlen(sock_in_ptr->m_PackedUrl.m_lpszServerName) <= iAddrBufSize, KP_E_BUFFER_OVERFLOW, null, True);
            if(SUCCEEDED(retc))
            {
               strncpy(lpszIpAddrBuf, sock_in_ptr->m_PackedUrl.m_lpszServerName, iAddrBufSize);
               lpszIpAddrBuf[iAddrBufSize] = Nul;
            }
         }
      }

   } // if(SUCCEEDED(retc))

// KpMsgOutF("po priemimo %lx %s %d %d", sock_in_ptr->m_PackedUrl.m_Addr.S_un.S_addr, sock_in_ptr->m_PackedUrl.lpszServerName, sock_in_ptr->m_PackedUrl.m_iPort, retc);

   KP_DELETE(sock_in_ptr);
   KP_DELETE(sock_ptr);

return(retc);
}

HRESULT KpStApp::RetrieveLicServer(unsigned char *lpszIpAddrBuf, int iAddrBufSize, int iPort)
{
HRESULT retc = S_OK;

   KP_ASSERT(lpszIpAddrBuf, E_INVALIDARG, null, True);

// ----------------------------- broadcasto dalis
   if(SUCCEEDED(retc)) if(strcmp(lpszIpAddrBuf, KP_IPADDR_LOCAL_HOST) == 0) // jei adresas jau nustatytas rankom – nedarom nieko
   {
      retc = RetrieveLicServerSingle(lpszIpAddrBuf, iAddrBufSize, iPort, KP_IPADDR_LOCAL_HOST);
      if(FAILED(retc)) retc = RetrieveLicServerSingle(lpszIpAddrBuf, iAddrBufSize, iPort, KP_IPADDR_BROADCAST);
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::AskUserPwd(void)
{
HRESULT retc=S_OK;
unsigned char user_pwd_buf[TV_TAG_LEN + 1];
unsigned char pwd_entered[TV_TAG_LEN + 1];
bool end_fl = False;
int prog_inc_sav = 1;

   if(SUCCEEDED(retc)) retc = GetIniUserPwd(user_pwd_buf);
   if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(user_pwd_buf);
   if(SUCCEEDED(retc)) TvStrLwr(user_pwd_buf, TV_MAIN_CTBL);
   if(SUCCEEDED(retc)) if(user_pwd_buf[0])
   {
// stabdom bitmapo slankiklá
      if(SUCCEEDED(retc)) retc = StopSlider(&prog_inc_sav);

      do
      {
//       retc = S_OK;
         pwd_entered[0] = Nul;
         retc = KpInputStr(KPST_MSG_ENTER_PWD, pwd_entered, TV_TAG_LEN, KPSTEDI_PWD_EDIT_WDT, 0, ES_PASSWORD, KP_MB_GERAI_ATSAUKTI_PAMIRSAU); // KP_MB_GERAI_ATSAUKTI); //
         if(SUCCEEDED(retc))
         {
            TvStrLwr(pwd_entered, TV_MAIN_CTBL);

            if(strcmp(user_pwd_buf, pwd_entered) == 0) end_fl = True;
            else
            {
// KpMsgOutF_3("user_pwd_buf >>>%s<<< pwd_entered >>>%s<<< %d", user_pwd_buf, pwd_entered, strcmp(user_pwd_buf, pwd_entered));
//             retc = KP_E_ACCESS_DENIED;
               KpMsgOut(KPST_MSG_BAD_PWD, IDI_ERROR, KP_MB_BAIGTI);
            }
         }
#if TRUE // #if FALSE
         else if(retc == KP_E_HELP)
         {
            retc = AskUserPUK();
            if(SUCCEEDED(retc)) end_fl = True;
         }
#endif
      }
      while(/* (retc == KP_E_ACCESS_DENIED) || */ (!end_fl) && SUCCEEDED(retc));

// atstatom bitmapo slankiklio greitá
      if(SUCCEEDED(retc)) retc = ReleaseSlider(prog_inc_sav);
   }

return(retc);
}


// -------------------------------------------
HRESULT KpStApp::AskUserPUK(const unsigned char *lpszPrompt)
{
HRESULT retc=S_OK;
unsigned char admin_pwd_buf[TV_TAG_LEN + 1];
unsigned char pwd_entered[TV_TAG_LEN + 1];
bool end_fl = False;
unsigned char msg_buf[KP_MAX_FILE_LIN_WDT + 1];
bool check_flash = False;

   if(SUCCEEDED(retc)) retc = GetIniCheckFlash(&check_flash);
   if(check_flash && SUCCEEDED(retc)) // tikrinam tik pririðtus prie atmintuko produktus
   {
      msg_buf[0] = Nul;
      if((lpszPrompt != null) && SUCCEEDED(retc))
      {
         KP_ASSERT(strlen(lpszPrompt) < KP_MAX_FILE_LIN_WDT + 100, KP_E_BUFFER_OVERFLOW, null, True);
         if(SUCCEEDED(retc))
         {
            strcpy(msg_buf, lpszPrompt);
//          strcat(msg_buf, "\n                                      \n");
            strcat(msg_buf, " ");
         }
      }
      if(SUCCEEDED(retc)) strcat(msg_buf, KPST_MSG_ENTER_PUK);

      if(SUCCEEDED(retc)) retc = GetIniAdminPwd(admin_pwd_buf);
      if(SUCCEEDED(retc)) retc = CutInitTrailSpcs(admin_pwd_buf);
      if(SUCCEEDED(retc)) TvStrLwr(admin_pwd_buf, TV_MAIN_CTBL);
      do
      {
         pwd_entered[0] = Nul;
         retc = KpInputStr(msg_buf, pwd_entered, TV_TAG_LEN, max(KPSTEDI_PWD_EDIT_WDT, KPW_CALC_STATIC_WDT_FACTOR(msg_buf, KPW_CONTROL_STYLE_NORMAL) - KP_INPUT_STR_EDIT_X),
                  0, 0 /* ES_PASSWORD */, KP_MB_GERAI_ATSAUKTI);
         if(SUCCEEDED(retc)) TvStrLwr(pwd_entered, TV_MAIN_CTBL);
         if(SUCCEEDED(retc))
         {
            if(strcmp(admin_pwd_buf, pwd_entered) == 0) end_fl = True;
            else KpMsgOutF_0(KPST_MSG_BAD_PUK);
         }
      }
      while(/* (retc == KP_E_ACCESS_DENIED) || */ (!end_fl) && SUCCEEDED(retc));

   } // if(check_flash)

return(retc);
}


// -------------------------------------------
HRESULT KpExpandMacro(unsigned char *lpszCmdBuf, int iBufSize, const unsigned char *lpszMacroName, const unsigned char *lpszReplaceText)
{
HRESULT retc=S_OK;
unsigned char *cmd_buf_tmp = null;
unsigned char *pnts;

   KP_ASSERT(lpszCmdBuf, E_INVALIDARG, null, True);
   KP_ASSERT(lpszMacroName, E_INVALIDARG, null, True);
   KP_ASSERT(lpszReplaceText, E_INVALIDARG, null, True);

   KP_NEWA(cmd_buf_tmp, unsigned char, iBufSize + 1);

   if(SUCCEEDED(retc)) do
   {
      pnts = strstr(lpszCmdBuf, lpszMacroName); // "{user}");
      if(pnts)
      {
         KP_ASSERT(strlen(lpszCmdBuf) + strlen(lpszReplaceText) < iBufSize, KP_E_BUFFER_OVERFLOW, null, True);

         if(SUCCEEDED(retc))
         {
            *pnts = Nul;
            pnts += strlen(lpszMacroName); // "{user}");

            strcpy(cmd_buf_tmp, lpszCmdBuf);
            strcat(cmd_buf_tmp, lpszReplaceText);
            strcat(cmd_buf_tmp, pnts);

            strcpy(lpszCmdBuf, cmd_buf_tmp);
         }
      }

   } while(pnts && SUCCEEDED(retc));

   KP_DELETEA(cmd_buf_tmp);

return(retc);
}


// -------------------------------------------
#if FALSE
HRESULT KpStApp::CheckKpStartRunning(void)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
DWORD retw = ERROR_SUCCESS;
static DWORD proc_ids[1000];
DWORD cnt = 0L;
int ii;
HANDLE hh = NULL;

   KP_ASSERT(EnumProcesses(proc_ids, sizeof(proc_ids), &cnt), KP_E_SYSTEM_ERROR, GetLastError(), True);

   for(ii = 0; (ii < cnt/sizeof(DWORD)) && SUCCEEDED(retc); ii++)
   {
      if(proc_ids[ii] && SUCCEEDED(retc))
      {
         hh = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ /* READ_CONTROL */, False, proc_ids[ii]);
         if(hh == NULL)
         {
            retw = GetLastError();
            if(retw != SE_ERR_ACCESSDENIED) KP_ERROR(KP_E_SYSTEM_ERROR, retw);
         }
         else
         {
// tik nuo XP
//          KP_ASSERT(GetProcessImageFileName(hh, (char *)app_name, KP_MAX_FNAME_LEN), KP_E_SYSTEM_ERROR, GetLastError(), True);

#if TRUE // #ifdef Debug
static unsigned char app_name[KP_MAX_FNAME_LEN + 1];
app_name[KP_MAX_FNAME_LEN] = Nul;
if(0 == GetModuleFileNameEx(hh, 0, (char *)app_name, KP_MAX_FNAME_LEN))
{
retw = GetLastError();
if(retw != SE_ERR_ACCESSDENIED) KP_ERROR(KP_E_SYSTEM_ERROR, retw);
}
app_name[KP_MAX_FNAME_LEN] = Nul;
KpMsgOutF_3("%d %lx %s", ii, proc_ids[ii], app_name);
#endif

         } // else // if(hh == NULL)

      } // if(proc_ids[ii] && SUCCEEDED(retc))


      if(hh) KP_ASSERT0(CloseHandle(hh), KP_E_SYSTEM_ERROR, GetLastError(), True);
      hh = NULL;
   }

return(retc);
}
#endif



// ------------------------------------------
HRESULT KpStApp::KpBringToTop(HWND hBitmapWindow, HWND hDlgWnd)
{
HRESULT retc = S_OK;

// if((hBitmapWindow != NULL) && SUCCEEDED(retc)) SetFocus(hBitmapWindow);

// if(hBitmapWindow == NULL) KpMsgOutF_0("NULL");

KP_TRACE_("KpStApp::KpBringToTop(%d, %d)", hBitmapWindow, hDlgWnd);

   if(/* (m_iKpStMode==KpStarterMode) && */ (hBitmapWindow) && SUCCEEDED(retc))
//    if(!BringWindowToTop(hBitmapWindow))
//    if(!SetForegroundWindow(hBitmapWindow))
      if(!SetWindowPos(hBitmapWindow, HWND_TOPMOST, 0, 0, 100, 100, SWP_NOMOVE|SWP_NOSIZE))
      {
//       retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      }

   if(hDlgWnd && SUCCEEDED(retc))
      if(!SetWindowPos(hDlgWnd, HWND_BOTTOM /* HWND_TOPMOST */ /* hBitmapWindow */, 0 /* wnd_x */, 0 /* wnd_y */, KPSPWD_WND_WDT, KPSPWD_WND_HGT, SWP_NOMOVE|SWP_NOSIZE /* SWP_HIDEWINDOW */))
      {
//        retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L);
      }

return(retc);
}


// ------------------------------------------
HRESULT KpStApp::InitExtViewers(void)
{
HRESULT retc = S_OK;
static unsigned char ini_fname[KP_MAX_FNAME_LEN + 100];
int line_count;
int ii;
const unsigned char *pnts;
unsigned char *pntd;

   KP_DELETEA(m_lpszaExtProcessed);
   KP_DELETEA(m_lpszaExtViewers);
   KP_DELETEA(m_lpszaExtViewersBuffer);

   strcpy(ini_fname, m_lpszFlashDevName);
   strcat(ini_fname, KPST_EXT_PLAYERS_INI_FNAME);
   retc = ReadFileContents(ini_fname, &m_lpszaExtViewersBuffer, NULL, False, False);
   if(SUCCEEDED(retc))
   {
      KP_ASSERT(m_lpszaExtViewersBuffer, KP_E_SYSTEM_ERROR, null, True);

// skaièiuojam eilutes
      if(SUCCEEDED(retc))
      {
         pnts = m_lpszaExtViewersBuffer;
         line_count = 0;
         while(*pnts) if(*pnts++ == Lf) line_count++;

// iðskiriam vietà masyvams
         KP_NEWA(m_lpszaExtProcessed, unsigned char *, line_count + 2); // vienas uþbaigimo nuliui, kitas – paskutinei eilutei (galimai be Lf gale)
         KP_NEWA(m_lpszaExtViewers, unsigned char *, line_count + 2);

// skanuojam
         ii = 0;
         pntd = m_lpszaExtViewersBuffer;
         while((*pntd) && SUCCEEDED(retc))
         {
            m_lpszaExtProcessed[ii] = pntd;
            while((*pntd != '=') && (*pntd != Lf) && (*pntd)) pntd++;
            switch(*pntd)
            {
            case '=':
               *pntd++ = Nul;
               m_lpszaExtViewers[ii] = pntd;
               while((*pntd != Lf) && (*pntd)) pntd++;
               if(*pntd == Lf) *pntd++ = Nul;
               break;
            case Lf: m_lpszaExtViewers[ii] = pntd; *pntd++ = Nul; break;
            case Nul: m_lpszaExtViewers[ii] = pntd; break;
            default: retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            }

            if(SUCCEEDED(retc))
            {
               CutInitTrailSpcs(m_lpszaExtProcessed[ii]);
               CutInitTrailSpcs(m_lpszaExtViewers[ii]);

               ii++;
               if((ii >= line_count + 1) && *pntd)
               {
                  retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                  break;
               }
            }
         }

         m_lpszaExtProcessed[ii] = null;
         m_lpszaExtViewers[ii] = null;
      }
   }
   else if(retc == KP_E_FILE_NOT_FOUND) retc = S_OK;

return(retc);
}


// ------------------------------------------
HRESULT KpStApp::CheckBinaries(void)
{
HRESULT retc = S_OK;
static unsigned char fname[KP_MAX_FNAME_LEN + 100 + 1];
static unsigned char fname_chk[KP_MAX_FNAME_LEN + 100 + 1];
static unsigned char disk[KP_MAX_FNAME_LEN + 1];
static unsigned char path[KP_MAX_FNAME_LEN + 1];
static unsigned char fname_out[KP_MAX_FNAME_LEN + 1];
static unsigned char typ[KP_MAX_FNAME_LEN + 1];
fstream *p_in_file = NULL;
long flen, flen_act;
int ll;
unsigned char *pntd = null;

// ---------------
   if(SUCCEEDED(retc)) retc = GetAppPath(fname, False);
   if(SUCCEEDED(retc)) strcat(fname, KPST_CHK_BIN_INI_FNAME);

   KP_NEW(p_in_file, KpFStream((const char *)fname, ios::in));

   if(SUCCEEDED(retc))
   {
      if(p_in_file->fail())
      {
//       KP_WARNING(KP_E_FILE_NOT_FOUND, fname)
      }
      else
      {
// ---------------
         ll = strlen(m_lpszFlashDevName);
         strcpy(fname_chk, m_lpszFlashDevName);
         fname_chk[ll++] = '\\';
         do
         {
            p_in_file->getline((char *)fname_chk + ll, KP_MAX_FNAME_LEN + 100 - ll);
            if(p_in_file->eof()) retc = KP_E_EOF;
            KP_ASSERT(!p_in_file->fail(), KP_E_FERROR, null, True);

            if(SUCCEEDED(retc))
            {
               flen = 0L;
               pntd = strchr(fname_chk + ll, Tab);
               if(pntd)
               {
                  *pntd++ = Nul;
                  sscanf((const char *)pntd, "%ld", &flen);
               }
            }

            if(SUCCEEDED(retc))
            {
               retc = KpGetFileSizeName(fname_chk, &flen_act, False);

               TvFnameSplit(disk, path, fname_out, typ, fname_chk);
               strcat(fname_out, ".");
               strcat(fname_out, typ);
               strlwr(fname_out);

               if((retc == KP_E_FILE_NOT_FOUND) && strstr(fname_chk, "autorun.inf")) retc = S_OK;
               else
               {
                  if(FAILED(retc)) KP_ERROR(retc, fname_out);
                  KP_ASSERTW(flen_act == flen, KP_E_FILE_CHANGED, fname_out, False);
               }
            }

         } while(SUCCEEDED(retc));
         if(retc == KP_E_EOF) retc = S_OK;

// ---------------
         if(SUCCEEDED(retc)) p_in_file->close();

      } // else // if(p_in_file->fail())

   } // if(SUCCEEDED(retc))

   KP_DELETE(p_in_file);

retc = S_OK;
return(retc);
}


// -------------------------------------------
// R/ID[<42f081e0602ae74b8b6092889b64a869><add62604141cdd499a7c5ab762fe3951>]
// R/ID[<5390a1606090c00982114141371e04f2><00f61ea600fba93300fbaa0c010145e2>]
// Password: 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 (0, 1, 2, 4, 6, 10, 12, 16, 18, 22, 28, 30) simboliai
// orig:
// 42f186ed062ae74b8b6092889b64a869
// su ProdVer:
// 42f081e0602ae74b8b6092889b64a869
// *** * *   * *   * *   *     * *
// 42f8e2e868a6
// 42F8E2E868A6
// ProdVer: 4, 6, 8, 9, 10 (3, 5, 7, 8, 9)
// 42f081e0602ae74b8b6092889b64a869
//    * * ***
// 01060
// failø archyvo blokø adresai:
//                             <add62604141cdd499a7c5ab762fe3951>
// m_lKpStArcStart[0] = add62604  ********
// m_KpStArcEnd[0]    = 141cdd49          ********
// m_lKpStArcStart[1] = 9a7c5ab7                  ********
// m_KpStArcEnd[1]    = 62fe3951                          ********
//
//                                <00f61ea600fba93300fbaa0c010145e2>
// 00f61ea6 - pirmo bloko pradzia  ********
// 00fba933 - pirmo bloko galas            ********
// 00fba933 - 00f61ea6 = 58a8d - pirmo bloko ilgis
// 00fbaa0c - antro bloko pradzia                  ********
// 010145e2 - antro bloko galas                            ********
// 010145e2 - 00fbaa0c = 69bd6 - antro bloko ilgis
//
HRESULT KpStApp::IoRid(const unsigned char *lpszObjFileName, bool bWrite)
{
HRESULT retc = S_OK;
static unsigned char rid_buf[KPST_RID_LEN * 2 + 1 + 4]; // padidintas iki word ribos dël EmuTv.ExecRemoteCall()
unsigned char ptr_buf[KPST_RID_LEN * 2 + 1 + 4];
long file_pos = 0L;
bool done = False;
unsigned char *rid_ptr = null;
static KpRcPars rc_pars;
const unsigned char *pnts = null;

   KP_ASSERT(lpszObjFileName, E_NOTIMPL, null, True);
   KP_ASSERT(strlen(lpszObjFileName) <= KP_MAX_FNAME_LEN, KP_E_BUFFER_OVERFLOW, lpszObjFileName, True);
   if(SUCCEEDED(retc)) strcpy(m_lpszObjFileName, lpszObjFileName);

   if(SUCCEEDED(retc))
   {
fstream obj_file((const char *)lpszObjFileName, (bWrite?(ios::in | ios::out):ios::in));
      KP_ASSERT(!obj_file.fail(), KP_E_FILE_NOT_FOUND, lpszObjFileName, True);

      memset(rid_buf, Nul, KPST_RID_LEN * 2 + 1);
      file_pos = 0L;
      done = False;

      if(SUCCEEDED(retc))
      {
         obj_file.read((char *)rid_buf, KPST_RID_LEN);
         KP_ASSERT(!obj_file.eof(), KP_E_FILE_FORMAT, lpszObjFileName, True);
         KP_ASSERT(!obj_file.fail(), KP_E_FERROR, lpszObjFileName, True);
      }

      if(SUCCEEDED(retc)) do
      {
         obj_file.read((char *)rid_buf + KPST_RID_LEN, KPST_RID_LEN);
//       KP_ASSERT(!obj_file.eof(), KP_E_FILE_FORMAT, lpszObjFileName, True);
//       KP_ASSERT(!obj_file.fail(), KP_E_FILE_FORMAT /* KP_E_FERROR */, lpszObjFileName, True); // kaþkodël neduoda .eof()
         if(obj_file.fail())
         {
            KP_WARNING(KP_E_FILE_FORMAT, lpszObjFileName);
            KpMsgOut(KP_MSG_FILE_FORMAT, IDI_ERROR, KP_MB_BAIGTI);
            retc = KP_E_FILE_FORMAT;
         }

         if(SUCCEEDED(retc))
         {
// ---------- keièiam nulius á '@' (nors .pdf-e nuliø ir neturëtø bût)
            for(int ii = 0; ii < KPST_RID_LEN * 2; ii++) if(rid_buf[ii] == Nul) rid_buf[ii] = '@';
            rid_buf[KPST_RID_LEN * 2] = Nul;

            rid_ptr = strstr(rid_buf, KPST_RID_PATTERN);
            if(rid_ptr && (rid_ptr <= rid_buf + KPST_RID_LEN))
            {
               rc_pars.iOpCode = KP_RC_UNPACK_RID;
               rc_pars.iParBlSize = sizeof(rc_pars);
               rc_pars.enc.iDataLen = KPST_RID_ELEM_LEN;
               rc_pars.enc.pData = rid_ptr + strlen(KPST_RID_PATTERN); // perðokam per "R/ID[<"

// PutLogMessage_("KpStApp::IR ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#if FALSE
rid_ptr[KPST_RID_LEN] = Nul;
KpMsgOutF("KpStApp::IoRid(): rid: [%s]", rid_ptr);
#endif

#ifdef Debug_RYt_putw
PutLogMessage_("KpStApp::InitStApp() .... %x %x", &rc_pars, rid_ptr + strlen(KPST_RID_PATTERN));
#endif
               retc = EmuTv.ExecRemoteCall(&rc_pars);

#ifndef KPST_MOVE_TO_KPHP11
               if(SUCCEEDED(retc)) retc = EnctIniData(sizeof(KpStIniData));
               if(SUCCEEDED(retc)) retc = GetIniFromHp11(&m_Ini);
               if(SUCCEEDED(retc)) retc = EnctIniData(sizeof(KpStIniData));
#endif

               pnts = rid_ptr + strlen(KPST_RID_PATTERN); // perðokam per "R/ID[<"
               m_ProdVar = pnts[11] - '0'; // ProdVar 12-as baitas

               m_ProdDate[3] = pnts[13]; // ProdDate(YMMDD) 14, 15, 16, 20, 21
               m_ProdDate[5] = pnts[14];
               m_ProdDate[6] = pnts[15];
               m_ProdDate[8] = pnts[19];
               m_ProdDate[9] = pnts[20];

               m_ProdVersion[0] = pnts[17]; // ProdVers(XZZ) 18, 22, 24
               m_ProdVersion[2] = pnts[21];
               m_ProdVersion[3] = pnts[23];
               m_ProdVersion[4] = Nul;

               pnts += 32 + 2; // perðokam per "42f081e0602ae74b8b6092889b64a869><"

               strcpy(ptr_buf, pnts);
               ptr_buf[8] = Nul;
               sscanf((const char *)ptr_buf, "%lx", &m_lKpStArcStart[0]);

               strcpy(ptr_buf, pnts + 8);
               ptr_buf[8] = Nul;
               sscanf((const char *)ptr_buf, "%lx", &m_lKpStArcLen[0]);
               m_lKpStArcLen[0] -= m_lKpStArcStart[0];

               strcpy(ptr_buf, pnts + 16);
               ptr_buf[8] = Nul;
               sscanf((const char *)ptr_buf, "%lx", &m_lKpStArcStart[1]);

               strcpy(ptr_buf, pnts + 24);
               ptr_buf[8] = Nul;
               sscanf((const char *)ptr_buf, "%lx", &m_lKpStArcLen[1]);
               m_lKpStArcLen[1] -= m_lKpStArcStart[1];

               done = True;
            }
            else // if(rid_ptr && (rid_ptr <= rid_buf + KPST_RID_LEN))
            {
               memcpy(rid_buf, rid_buf + KPST_RID_LEN, KPST_RID_LEN);
               file_pos += KPST_RID_LEN;
            }

         } // if(SUCCEEDED(retc))

      } while((!done) && SUCCEEDED(retc));

      obj_file.close();

   } // if(SUCCEEDED(retc)) // lpszObjFileName != null

return(retc);
}


HRESULT KpStApp::UnpackObjFiles(void)
{
HRESULT retc = S_OK;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
KpStArc *arc = NULL;
int ii;
static unsigned char tmp_dir[KP_MAX_FNAME_LEN + 1];

   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_PAR))
      for(ii = 0; (ii < 2) && SUCCEEDED(retc); ii++)
      {
         KP_NEWO(arc, KpStArc(m_lpszObjFileName, m_lKpStArcStart[ii], m_lKpStArcLen[ii]));

         if(SUCCEEDED(retc)) retc = arc->LookupArc();

         if(SUCCEEDED(retc)) retc = GetLocalPath(tmp_dir, KP_Temp_Dir, True);
         if(SUCCEEDED(retc)) retc = arc->ExtractFiles(tmp_dir);

         KP_DELETE(arc);
      }

return(retc);
}


HRESULT KpStApp::DeleteObjFiles(void)
{
HRESULT retc = S_OK;
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT + 1];
KpStArc *arc = NULL;
int ii;
static unsigned char tmp_dir[KP_MAX_FNAME_LEN + 1];

   if(SUCCEEDED(retc)) retc = GetIniCmdStr(cmd_str);
   if(SUCCEEDED(retc)) if(strstr(cmd_str, KPST_FNAME_SHORTCUT_PAR))
      for(ii = 0; (ii < 2) && SUCCEEDED(retc); ii++)
      {
         KP_NEWO(arc, KpStArc(m_lpszObjFileName, m_lKpStArcStart[ii], m_lKpStArcLen[ii]));

         if(SUCCEEDED(retc)) retc = arc->LookupArc();

         if(SUCCEEDED(retc)) retc = GetLocalPath(tmp_dir, KP_Temp_Dir, True);
         if(SUCCEEDED(retc)) retc = arc->DelFiles(tmp_dir);

         KP_DELETE(arc);
      }

return(retc);
}


// ----------------------------------------- áraðom uþkoduotà individualaus atmintuko atnaujinimo lic. kodà á R__svarbiinfo.js
// buvo "DAT10 OU00LTY1MjQ2LTA1NzY=" – du par. – atmintuko pakatalogis ir AI_e kintamojo reikðmë
// dabar "DAT10 global.AI_e=SdS('ME0xLTMxOTQ0LTM1MTU=')"
// gali bûti keli: "DAT9,DAT10 global.AI_e=SdS('ME0xLTMxOTQ0LTM1MTU=')"
HRESULT KpStApp::CorFlashUpdLicId(unsigned char *lpszUpdUserPars)
{
HRESULT retc = S_OK;
static unsigned char js_fname[KP_MAX_FNAME_LEN + 1];
unsigned char *val_ptr = NULL;
unsigned char val_first_chr = Nul;
unsigned char *js_var_ptr = NULL;
unsigned char *js_var_name_ptr = NULL;
unsigned char *js_cont = NULL;
long js_len = 0L;
unsigned char **dir_arr = NULL;
int dir_num;
int ii;

// ----------------------
   KP_ASSERT(lpszUpdUserPars, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc)) val_ptr = strchr(lpszUpdUserPars, Spc);
   KP_ASSERT(val_ptr, E_INVALIDARG, null, True);
   if(SUCCEEDED(retc))
   {
      *val_ptr++ = Nul;
      while(*val_ptr == Spc) val_ptr++;
      js_var_name_ptr = val_ptr;
      val_ptr = strstr(val_ptr, JS_VAR_START);

      retc = SplitStrings(&dir_arr, &dir_num, lpszUpdUserPars, (const unsigned char *)",", True);
   }
   KP_ASSERT(val_ptr, KP_E_FILE_FORMAT, null, True);
   KP_ASSERT(dir_arr, KP_E_SYSTEM_ERROR, null, True);

   for(ii = 0; (ii < dir_num) && SUCCEEDED(retc); ii++)
   {
      val_ptr += strlen(JS_VAR_START);
      val_first_chr = *val_ptr;
      *val_ptr = Nul; // kad galëtume naudoti js_var_name_ptr, po to atstatysim

// ----------------------
      KP_ASSERT(strlen(m_lpszFlashDevName) + 1 + strlen(dir_arr[ii] /* lpszUpdUserPars */) + 1 + strlen(KPST_ACROREAD60_PATHNAME_SHORT) + strlen(JS_SUB_PATH_4) + strlen(JS_SVARBIINFO_FLASH) <= KP_MAX_FNAME_LEN,
         KP_E_BUFFER_OVERFLOW, null, True);
      if(SUCCEEDED(retc))
      {
         strcpy(js_fname, m_lpszFlashDevName);
         strcat(js_fname, "\\");
         strcat(js_fname, dir_arr[ii]); // lpszUpdUserPars);
         strcat(js_fname, "\\");
         strcat(js_fname, KPST_ACROREAD60_PATHNAME_SHORT);
         strcat(js_fname, JS_SUB_PATH_4);
         strcat(js_fname, JS_SVARBIINFO_FLASH);
      }

// ----------------------
      if(SUCCEEDED(retc)) retc = ReadFileContents(js_fname, &js_cont, &js_len, True, False);
      KP_ASSERT(js_cont, KP_E_SYSTEM_ERROR, null, True);

      if(SUCCEEDED(retc)) js_var_ptr = strstr(js_cont, js_var_name_ptr); // JS_AI_VAR_NAME);
      KP_ASSERT(js_var_ptr, KP_E_FILE_FORMAT, null, True);

      if(SUCCEEDED(retc))
      {
//       js_var_ptr += strlen(JS_AI_VAR_NAME);
         *js_var_ptr++ = Nul;
         js_var_ptr = strstr(js_var_ptr, JS_VAR_TAIL);
      }
      KP_ASSERT(js_var_ptr, KP_E_FILE_FORMAT, null, True);
      if(SUCCEEDED(retc)) js_var_ptr += strlen(JS_VAR_TAIL);

// ----------------------
      if(SUCCEEDED(retc))
      {
fstream out_file((const char *)js_fname, ios::out);
         KP_ASSERT(!out_file.fail(), KP_E_DIR_ERROR, null, True);

         if(SUCCEEDED(retc)) out_file << js_cont;
         *val_ptr = val_first_chr;
         if(SUCCEEDED(retc)) out_file << js_var_name_ptr; // val_ptr;
         if(SUCCEEDED(retc)) out_file << js_var_ptr;
         KP_ASSERT(!out_file.fail(), KP_E_FERROR, null, True);

         out_file.close();
         KP_ASSERT(!out_file.fail(), KP_E_FERROR, null, True);
      }

// ----------------------
      KP_DELETEA(js_cont);

   } // for(ii = 0; (ii < dir_num) && SUCCEEDED(retc); ii++)

   KP_DELETEA(dir_arr);

return(retc);
}


// =================================================================
HRESULT KpStApp::SaveRestDaysInitHp11Common(int iRestDaysInitChSum, int iOpCode)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
static int val[3];

#if TRUE // FALSE //
int lic_high, rest_days_init;
long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("SRDIHC() 1: l_h: %d r_d_i: %d %x r_m: %ld", lic_high, rest_days_init, iRestDaysInitChSum, rest_mins);
#endif

   val[0] = iRestDaysInitChSum;

   rc_pars.iOpCode = iOpCode;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.enc.pData = val;
   rc_pars.enc.iDataLen = sizeof(iRestDaysInitChSum);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::SRDIHC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("SRDIHC() ....>>>> %x %x", &rc_pars, val);
#endif

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc)) retc = KP_E_ILL_CODE;

   if(FAILED(retc)) KP_ERROR(retc, null);

// int rest_days;
// EmuTv.GetHp11Variable(&rest_days, KP11_REST_DAYS_INIT);
// KpMsgOutF("SaveRestDaysInitHp11Common(): iRestDaysInitChSum: %x rest_days: %x %d", iRestDaysInitChSum, rest_days, rest_days);

#if TRUE // FALSE //
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("SRDIHC() 2: l_h: %d r_d_i: %d %x r_m: %ld", lic_high, rest_days_init, iRestDaysInitChSum, rest_mins);
#endif

return(retc);
}


HRESULT KpStApp::SaveRestDaysInitHp11WithRC(int iRestDaysInitChSum, int iOpCode, int iRCOpCode)
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
static KpRcPars rc_pars;
static int val[3];

   val[0] = iRestDaysInitChSum;

   rc_pars.iOpCode = iOpCode;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.enc.pData = val;
   rc_pars.enc.iDataLen = sizeof(iRestDaysInitChSum);
   rc_pars.value = False;
   rc_pars.enc.iCallBackIx = iRCOpCode;
   rc_pars.enc.pCallBackPars = &retc;

// PutLogMessage_("KpStApp::SRDIHWRC ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("SRDIHWRC() ....>>>> %x %x", &rc_pars, val);
#endif

   retc0 = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   if(SUCCEEDED(retc)) retc = retc0;

   if((!rc_pars.value) && SUCCEEDED(retc)) retc = KP_E_ILL_CODE;

   if(FAILED(retc)) KP_ERROR(retc, null);

// int rest_days;
// EmuTv.GetHp11Variable(&rest_days, KP11_REST_DAYS_INIT);
// KpMsgOutF("SaveRestDaysInitHp11WithRC(): iRestDaysInitChSum: %x rest_days: %x %d", iRestDaysInitChSum, rest_days, rest_days);

#if FALSE
int lic_high, rest_days_init;
long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("SRDIHWRC(): l_h: %d r_d_i: %d %x r_m: %ld", lic_high, rest_days_init, iRestDaysInitChSum, rest_mins);
#endif

return(retc);
}


int InitResumeRestDaysHp11Called = 0;
HRESULT KpStApp::InitResumeRestDaysHp11(KpCommonCallBackIxs iCallBackIx) // raðo KP11_REST_DAYS_INIT á failà, kalkuliuoja KP11_REST_MINS
{
HRESULT retc = S_OK;
HRESULT retc0 = S_OK;
int rest_days_init = 0L;
long rest_mins_init = 0L;
long cur_day_minute = 0L;
long rest_mins = 0L;
long rest_days = 0L;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];

// EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
// EmuTv.GetHp11VariableLong(&rest_mins_init, KP11_REST_MINS);
// PutLogMessage_("IRRDH() 000: %d  r_d_i: %d r_m_i: %ld retc: %x %x", iCallBackIx, rest_days_init, rest_mins_init, retc, &InitRestDays_RC);

   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

// if(InitResumeRestDaysHp11Called == 0) // apsauga nuo rekursijos – CheckReg() vël iðkvieèia InitResumeRestDaysHp11()
   {
      if(SUCCEEDED(retc)) retc = EmuTv.CallRCCallBackRetC(iCallBackIx);

      if(InitResumeRestDaysHp11Called == 0) // apsauga nuo rekursijos – CheckReg() vël iðkvieèia InitResumeRestDaysHp11()
//    if(iCallBackIx != InitRestDays_RC) // apsauga nuo rekursijos – CheckReg() vël iðkvieèia InitResumeRestDaysHp11()
         if((retc == KP_E_TIMEOUT) || (retc == KP_E_EXPIRED))
         {
// Èia tam, kad WinXP galëtø nusikraut ið serverio pratæstos licencijos laikus
// registr.exe laikus atnaujina tik adminui, lokalaus userio lieka seni
            InitResumeRestDaysHp11Called++;
PutLogMessage_("IRRDH() 2: r_d_i: %d r_m_i: %ld retc: %x", rest_days_init, rest_mins_init, retc);
            retc = CheckReg(m_hInstance, NULL, True); // Èia prievartinio praneðimo nereikia – dubliuojasi ProcessRestDays() atveju
PutLogMessage_("IRRDH() 3: r_d_i: %d r_m_i: %ld retc: %x", rest_days_init, rest_mins_init, retc);
            InitResumeRestDaysHp11Called--;
         }
   }

// TODO: Èia reiktø pabandyt nulauþt – pasibaigusiai licencijai pakiðt padidintus terminus
   retc0 = EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT); if(SUCCEEDED(retc)) retc = retc0;
   retc0 = EmuTv.GetHp11VariableLong(&rest_mins_init, KP11_REST_MINS); if(SUCCEEDED(retc)) retc = retc0;

PutLogMessage_("IRRDH() 00: r_d_i: %d r_m_i: %ld retc: %x", rest_days_init, rest_mins_init, retc);
   if(SUCCEEDED(retc))
   {
SYSTEMTIME tt;
      GetSystemTime(&tt);
      cur_day_minute = tt.wHour * KPST_MINS_PER_HOUR + tt.wMinute;
      rest_mins = rest_mins_init + cur_day_minute;
      rest_days = rest_mins / KPST_MINS_PER_DAY;
PutLogMessage_("IRRDH() 0: r_d_i: %d r_d: %d r_m_i: %ld r_m: %ld c_d_m: %ld  retc: %x", rest_days_init, rest_days, rest_mins_init, rest_mins, cur_day_minute, retc);

      if(rest_days_init > 0) if((rest_mins <= (long)KPST_MINS_PER_DAY * KPST_REST_DAYS_WARNING) || (m_iKpStMode == KpStRegMode))
      {
         if(rest_mins <= 0)
         {
#if FALSE // ðitas atvejis ateina per retc = KP_E_EXPIRED /* KP_E_TIMEOUT */ ið CallRCCallBackRetC()?
static unsigned char str_buf[2000];
            sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
            KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
            KP_WARNING(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
            endfl = True;
            retc = KP_E_EXPIRED; // KP_E_TIMEOUT;
#endif
         }
         else
         {
            if(!RestDaysWarningShowed())
            {
               switch(rest_mins / KPST_MINS_PER_DAY)
               {
               case 0L: KpMsgOutF(KPST_MSG_REST_TODAY, prod_name); break;
               case 1L: KpMsgOutF(KPST_MSG_REST_DAY, prod_name); break;
               default:
                  switch(rest_mins / KPST_MINS_PER_DAY / KPST_DAYS_PER_MONTH)
                  {
                  case 0L: KpMsgOutF(KPST_MSG_REST_DAYS, prod_name, rest_mins / KPST_MINS_PER_DAY); break;
                  case 1L: KpMsgOutF(KPST_MSG_REST_LAST_MONTH, prod_name); break;
                  default: KpMsgOutF(KPST_MSG_REST_MONTHS, prod_name, rest_mins / KPST_MINS_PER_DAY / KPST_DAYS_PER_MONTH); break;
                  }
                  break;
               }
            }
//          m_iRestDaysWarningShowed = True;
            KP_WARNING0(KP_E_EXPIRED /* KP_E_TIMEOUT */, null);
         }
      }
   }

static unsigned char str_buf[2000];
   if(FAILED(retc)) switch(retc)
   {
   case KP_E_REFUSED:
      if(!RestDaysWarningShowed())
      {
         sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED /* KPST_MSG_TIME_CHEAT */, prod_name);
         KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI);
      }
//    m_iRestDaysWarningShowed = True;
      KP_WARNING0(retc, null);
      break;

   case KP_E_TIMEOUT:
   case KP_E_EXPIRED:
      if(!RestDaysWarningShowed())
      {
         sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
         KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI); // nereikia, jei dubliuojasi su KPST_ID_REST_DAYS_EXCEEDED praneðimu
      }
//    m_iRestDaysWarningShowed = True;
      KP_WARNING0(retc, null);
      break;

   default:
      KP_ERROR(retc, null);
      break;
   }

#if TRUE // FALSE //
int lic_high;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins_init, KP11_REST_MINS);
PutLogMessage_("IRRDH(): l_h: %d r_d_i: %d r_m_i: %ld r_m: %ld c_d_m: %ld", lic_high, rest_days_init, rest_mins_init, rest_mins, cur_day_minute);
#endif

return(retc);
}


HRESULT KpStApp::GetRestDaysInitHp11(int *piRestDaysInitChSum)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
static int ret_val[3];

   KP_ASSERT(piRestDaysInitChSum, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_GET_REST_DAYS;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.pData = ret_val;
      rc_pars.enc.iDataLen = sizeof(int);

// PutLogMessage_("KpStApp::GRDIH ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("GRDIH() ....>>>> %x %x", &rc_pars, ret_val);
#endif

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   }

   if(SUCCEEDED(retc)) *piRestDaysInitChSum = ret_val[0];

// int rest_days;
// EmuTv.GetHp11Variable(&rest_days, KP11_REST_DAYS_INIT);
// KpMsgOutF("GetRestDaysInitHp11(): rest_days: %d %x ret_val: %x %x", rest_days, rest_days, *piRestDaysInitChSum, (rest_days << 4) | ((rest_days ^ (rest_days >> 4) ^ (rest_days >> 8)) & 0xF));

return(retc);
}


HRESULT KpStApp::SaveLicHighHp11(int iLicHighChSum)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
static int val[3];

#if TRUE // FALSE
   val[0] = iLicHighChSum;

   rc_pars.iOpCode = KP_RC_SAVE_LIC_HIGH;
   rc_pars.iParBlSize = sizeof(rc_pars);
   rc_pars.enc.pData = val;
   rc_pars.enc.iDataLen = sizeof(iLicHighChSum);
   rc_pars.value = False;

// PutLogMessage_("KpStApp::SLHH ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("SLHH() .... %x %x", &rc_pars, val);
#endif

   retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);

   if((!rc_pars.value) && SUCCEEDED(retc)) retc = KP_E_ILL_CODE;

#else
   EmuTv.SetHp11Variable(iLicHighChSum >> 4, KP11_LIC_HIGH);
#endif

// int lic_high;
// EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
// KpMsgOutF("SaveLicHighHp11(): lic_high: %d, iLicHighChSum: %x", lic_high, iLicHighChSum);

return(retc);
}


HRESULT KpStApp::GetLicHighHp11(int *piLicHighChSum)
{
HRESULT retc = S_OK;
static KpRcPars rc_pars;
static int ret_val[3];

// int lic_high;
// EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);

#if TRUE // FALSE
   KP_ASSERT(piLicHighChSum, E_INVALIDARG, null, True);

   if(SUCCEEDED(retc))
   {
      rc_pars.iOpCode = KP_RC_GET_LIC_HIGH;
      rc_pars.iParBlSize = sizeof(rc_pars);
      rc_pars.enc.pData = ret_val;
      rc_pars.enc.iDataLen = sizeof(int);

// PutLogMessage_("KpStApp::GLHH ERC %d %d %d", rc_pars.iOpCode, EmuTv.m_lMainThreadId, GetCurrentThreadId());

#ifdef Debug_RYt_putw
PutLogMessage_("SLHH() ....>>>> %x %x", &rc_pars, ret_val);
#endif

      retc = EmuTv.ExecRemoteCall(&rc_pars /* , lMainThreadId */);
   }

   if(SUCCEEDED(retc)) *piLicHighChSum = ret_val[0];

#else
   if(SUCCEEDED(retc)) *piLicHighChSum = (lic_high << 4) | ((lic_high ^ (lic_high >> 4)) & 0xF);
#endif

// KpMsgOutF("GetLicHighHp11(): lic_high: %d, *piLicHighChSum %x, %x", lic_high, *piLicHighChSum, (lic_high << 4) | ((lic_high ^ (lic_high >> 4)) & 0xF));

return(retc);
}


HRESULT KpStApp::ProcessRestDays(void)
{
HRESULT retc = S_OK;
unsigned char prod_name[KP_MAX_FNAME_LEN + 1];
static unsigned char str_buf[2000];

#if TRUE // FALSE
int lic_high, rest_days_init;
long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("PRD() 1: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

   if(SUCCEEDED(retc)) /* retc = */ CheckReg(m_hInstance, NULL, True, True); // reikia prievartinio praneðimo, jeigu ið serverio pagauna pasibaigusià licencijà

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("PRD() 2: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

   if(SUCCEEDED(retc)) retc = EmuTv.CallRCCallBackRetC(KP_RC_CBIX_ProcessRestDays);

   if(SUCCEEDED(retc)) retc = GetIniProdName(prod_name);

#if TRUE // FALSE
// int lic_high, rest_days_init;
// long rest_mins;
EmuTv.GetHp11Variable(&lic_high, KP11_LIC_HIGH);
EmuTv.GetHp11Variable(&rest_days_init, KP11_REST_DAYS_INIT);
EmuTv.GetHp11VariableLong(&rest_mins, KP11_REST_MINS);
PutLogMessage_("PRD() 3: l_h: %d r_d_i: %d r_m: %ld", lic_high, rest_days_init, rest_mins);
#endif

   if(FAILED(retc))
   {
      switch(retc)
      {
      case KP_E_TIMEOUT:
      case KP_E_EXPIRED:
         if(!RestDaysWarningShowed())
         {
            sprintf((char *)str_buf, (const char *)KPST_MSG_LICENCE_EXPIRED, prod_name);
            KpMsgOut(str_buf, IDI_ERROR, KP_MB_TESTI); // nereikia, jei dubliuojasi su KPST_ID_REST_DAYS_EXCEEDED praneðimu
         }
//       m_iRestDaysWarningShowed = True;
         KP_WARNING0(retc, null);
         break;

      default:
         KP_ERROR(retc, null);
         break;
      }

// PutLogMessage_("PRD(): %d %d %d %d : %x %x : %x %x", m_lCmdThread, m_lListThreadId, iKpMainThread, GetCurrentThreadId(), m_hCmdThread, GetCurrentThread(), m_hCmdProcess, GetCurrentProcess());

//    PostQuitMessage(IDABORT);
      PostThreadMessage(iKpMainThread, WM_QUIT, IDABORT, 0L);
   }

// PutLogMessage_("PRD() %d %d", GetCurrentThreadId(), m_lListThreadId);

return(retc);
}


// ------------------------------------------------
bool KpStApp::RestDaysWarningShowed(void)
{
bool warn_showed = False;

// atsimenam faile paskutinio iðvedimo laikà – tux_ipa sukuria KpStApp objektà 2 kartus, iðkvieèia ið viso 4 kartus
long cur_secs = GetTickCount() / 1000;
unsigned char fname[KP_MAX_FNAME_LEN + 1];
   strcpy(fname, getenv("TEMP"));
   strcat(fname, "\\kpst_last_warning.txt");
FILE *file = fopen((const char *)fname, "r");
long last_secs = 0l;
   if(file != NULL)
   {
      fscanf(file, "%ld", &last_secs);
      if((cur_secs >= last_secs) && (cur_secs < last_secs + 15 /* KP_SECS_PER_MIN */)) warn_showed = True;
      fclose(file);
      file = NULL;
   }
   if(!warn_showed)
   {
      file = fopen((const char *)fname, "w");
      if(file != NULL)
      {
         fprintf(file, "%ld\n", cur_secs);
         fclose(file);
         file = NULL;
      }
   }

// KpMsgOutF("KpStApp::KpStApp() %ld %ld %d", cur_secs, last_secs, m_iRestDaysWarningShowed);
return(warn_showed);
}
