// ---------------------------
// kpstedi.cpp
// aplikacijos paleidimo kpstart.exe .ini failo redagavimas
//
// kpstedi.exe kopijuojamas i:
//
//    kpstedf.exe - #define KPSTEDI_MODE GENERAL_MODE
//    kpstedr.exe, edini.exe   - #define KPSTEDI_MODE USER_MODE
//    kpstedb.exe - #define KPSTEDI_MODE BOUND_MODE
//

// -----------------------------------------
// #define KPSTEDI_EDITOR

#include "stdafx.h"

#include "envir.h"
#include "iBshn.h"
#include "lzdshn.h"

#include <stdio.h>
#include <string>
// #include <iostream>
#include <fstream>
#include <windows.h>
// #include <windowsx.h>
#include <commctrl.h>
#include <richedit.h>
#include <Richole.h>
#include <time.h>

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
#include "kptt.h"
#include "kptree.h"
#include "kpctype.h"
#include "kpstring.h"
#include "kpcolors.h"
#include "kpfonts.h"
#include "kpstdio.h"
#include "kpttucf.h"
#include "res_com.h"
#include "kpwindow.h"
#include "kpsock.h"
#include "kpmsg.h"
#include "kperr.h"
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
#include "kpstedi.h"
#include "kpstedi_en.h"
#include "kpstedi_lt.h"
#include "kpstedi_pl_1250.h"
#include "kpstedi_pl_1257.h"
#include "kpstedi_ru.h"


#if (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
// #error (Envir!=MSWin32) && (Envir!=MSWin32Mfc)
#if (Envir!=MSWin32Con)
#error (Envir!=MSWin32) && (Envir!=MSWin32Mfc) && (Envir!=MSWin32Con)
#endif
#endif


// ----------------------------------
// KpStEdiDlg KpstEdiDialog;
KpStEdiDlg *KpstEdiDialogPtr = NULL;


#if KPSTEDI_MODE & GENERAL_MODE
// ----------------------------------
/* const */ unsigned char KpstedTabHeaders[KPSTEDI_TAB_NUM_OF_TABS][KP_KWD_LEN + 1] =
{
/* ( */ /* const */ /* unsigned char *) */ KPSTEDI_TAB_PROD_LT,  // KPSTEDI_TAB_PROD,
/* ( */ /* const */ /* unsigned char *) */ KPSTEDI_TAB_START_LT, // KPSTEDI_TAB_START,
/* ( */ /* const */ /* unsigned char *) */ KPSTEDI_TAB_BOUND_LT, // KPSTEDI_TAB_BOUND,
/* ( */ /* const */ /* unsigned char *) */ KPSTEDI_TAB_DATA_LT,  // KPSTEDI_TAB_DATA,
/* ( */ /* const */ /* unsigned char *) */ KPSTEDI_TAB_OWNER_LT, // KPSTEDI_TAB_OWNER,
};
#endif

// ----------------------------------
const unsigned char *lpszaKpStEdiMessages[NumOfKpStEdiMessages_9][KpNumOfLangs_2] =
{
KPSTEDI_INI_FILTER_NAME_EN,        KPSTEDI_INI_FILTER_NAME_LT,        KPSTEDI_INI_FILTER_NAME_PL_1250,        KPSTEDI_INI_FILTER_NAME_PL_1257,        KPSTEDI_INI_FILTER_NAME_RU,        KPSTEDI_INI_FILTER_NAME_RU,        // "Ini failai"
KPSTEDI_INI_FILE_PROMPT_EN,        KPSTEDI_INI_FILE_PROMPT_LT,        KPSTEDI_INI_FILE_PROMPT_PL_1250,        KPSTEDI_INI_FILE_PROMPT_PL_1257,        KPSTEDI_INI_FILE_PROMPT_RU,        KPSTEDI_INI_FILE_PROMPT_EN,        // "Pasirinkite ini failà"
KPSTEDI_USER_DATA_CHANGED_EN,      KPSTEDI_USER_DATA_CHANGED_LT,      KPSTEDI_USER_DATA_CHANGED_PL_1250,      KPSTEDI_USER_DATA_CHANGED_PL_1257,      KPSTEDI_USER_DATA_CHANGED_RU,      KPSTEDI_USER_DATA_CHANGED_RU,      // "Slaptaþodis ir naudotojo duomenys sëkmingai pakeisti."

(const unsigned char *)KPSTEDI_TAB_PROD_EN,  (const unsigned char *)KPSTEDI_TAB_PROD_LT,  (const unsigned char *)KPSTEDI_TAB_PROD_PL_1250,  (const unsigned char *)KPSTEDI_TAB_PROD_PL_1257,               KPSTEDI_TAB_PROD_RU,               KPSTEDI_TAB_PROD_RU,               // "  Produktas  "
(const unsigned char *)KPSTEDI_TAB_START_EN, (const unsigned char *)KPSTEDI_TAB_START_LT, (const unsigned char *)KPSTEDI_TAB_START_PL_1250, (const unsigned char *)KPSTEDI_TAB_START_PL_1257,              KPSTEDI_TAB_START_RU,              KPSTEDI_TAB_START_RU,              // "  Paleistis  "
(const unsigned char *)KPSTEDI_TAB_BOUND_EN, (const unsigned char *)KPSTEDI_TAB_BOUND_LT, (const unsigned char *)KPSTEDI_TAB_BOUND_PL_1250, (const unsigned char *)KPSTEDI_TAB_BOUND_PL_1257,              KPSTEDI_TAB_BOUND_RU,              KPSTEDI_TAB_BOUND_RU,              // "  Pririðimas  "
(const unsigned char *)KPSTEDI_TAB_DATA_EN,  (const unsigned char *)KPSTEDI_TAB_DATA_LT,  (const unsigned char *)KPSTEDI_TAB_DATA_PL_1250,  (const unsigned char *)KPSTEDI_TAB_DATA_PL_1257,               KPSTEDI_TAB_DATA_RU,               KPSTEDI_TAB_DATA_RU,               // "  Duomenys  "
(const unsigned char *)KPSTEDI_TAB_OWNER_EN, (const unsigned char *)KPSTEDI_TAB_OWNER_LT, (const unsigned char *)KPSTEDI_TAB_OWNER_PL_1250, (const unsigned char *)KPSTEDI_TAB_OWNER_PL_1257,              KPSTEDI_TAB_OWNER_RU,              KPSTEDI_TAB_OWNER_RU,              // "  Naudotojas  "

KPSTEDI_TITLE_EN,                  KPSTEDI_TITLE_LT,                  KPSTEDI_TITLE_PL_1250,                  KPSTEDI_TITLE_PL_1257,                  KPSTEDI_TITLE_RU,                  KPSTEDI_TITLE_RU,                  // "Programos paleidimo parametrai"

KPSTEDI_REZ_NOT_CLOSE_1_EN,        KPSTEDI_REZ_NOT_CLOSE_1_LT,        KPSTEDI_REZ_NOT_CLOSE_1_PL_1250,        KPSTEDI_REZ_NOT_CLOSE_1_PL_1257,        KPSTEDI_REZ_NOT_CLOSE_1_RU,        KPSTEDI_REZ_NOT_CLOSE_1_RU,        // "Jei ðis langas neuþsidarys,"
KPSTEDI_REZ_NOT_CLOSE_2_EN,        KPSTEDI_REZ_NOT_CLOSE_2_LT,        KPSTEDI_REZ_NOT_CLOSE_2_PL_1250,        KPSTEDI_REZ_NOT_CLOSE_2_PL_1257,        KPSTEDI_REZ_NOT_CLOSE_2_RU,        KPSTEDI_REZ_NOT_CLOSE_2_RU,        // "pabandykite pakeisti duomenø failo vardà"

// Produktas
KPSTEDI_PROD_PROMPT_EN,            KPSTEDI_PROD_PROMPT_LT,            KPSTEDI_PROD_PROMPT_PL_1250,            KPSTEDI_PROD_PROMPT_PL_1257,            KPSTEDI_PROD_PROMPT_RU,            KPSTEDI_PROD_PROMPT_RU,            // "Produkto pavadinimas"
KPSTEDI_WNDNAME_PROMPT_EN,         KPSTEDI_WNDNAME_PROMPT_LT,         KPSTEDI_WNDNAME_PROMPT_PL_1250,         KPSTEDI_WNDNAME_PROMPT_PL_1257,         KPSTEDI_WNDNAME_PROMPT_RU,         KPSTEDI_WNDNAME_PROMPT_RU,         // "Programos lango pavadinimas"
KPSTEDI_PUBL_PROMPT_EN,            KPSTEDI_PUBL_PROMPT_LT,            KPSTEDI_PUBL_PROMPT_PL_1250,            KPSTEDI_PUBL_PROMPT_PL_1257,            KPSTEDI_PUBL_PROMPT_RU,            KPSTEDI_PUBL_PROMPT_RU,            // "Gamintojas"
KPSTEDI_PRODVER_PROMPT_EN,         KPSTEDI_PRODVER_PROMPT_LT,         KPSTEDI_PRODVER_PROMPT_PL_1250,         KPSTEDI_PRODVER_PROMPT_PL_1257,         KPSTEDI_PRODVER_PROMPT_RU,         KPSTEDI_PRODVER_PROMPT_RU,         // "Produktas/versija (VVPPP)"
KPSTEDI_UPDNUM_PROMPT_EN,          KPSTEDI_UPDNUM_PROMPT_LT,          KPSTEDI_UPDNUM_PROMPT_PL_1250,          KPSTEDI_UPDNUM_PROMPT_PL_1257,          KPSTEDI_UPDNUM_PROMPT_RU,          KPSTEDI_UPDNUM_PROMPT_RU,          // "Atnaujinimo Nr. (ProdVar + 1)"
KPSTEDI_VOL_PROMPT_EN,             KPSTEDI_VOL_PROMPT_LT,             KPSTEDI_VOL_PROMPT_PL_1250,             KPSTEDI_VOL_PROMPT_PL_1257,             KPSTEDI_VOL_PROMPT_RU,             KPSTEDI_VOL_PROMPT_RU,             // "Kodinis pavadinimas") // :"
KPSTEDI_VOL_PROMPT1_EN,            KPSTEDI_VOL_PROMPT1_LT,            KPSTEDI_VOL_PROMPT1_PL_1250,            KPSTEDI_VOL_PROMPT1_PL_1257,            KPSTEDI_VOL_PROMPT1_RU,            KPSTEDI_VOL_PROMPT1_RU,            // "Naudojamas kaip:"
KPSTEDI_VOL_PROMPT2_EN,            KPSTEDI_VOL_PROMPT2_LT,            KPSTEDI_VOL_PROMPT2_PL_1250,            KPSTEDI_VOL_PROMPT2_PL_1257,            KPSTEDI_VOL_PROMPT2_RU,            KPSTEDI_VOL_PROMPT2_RU,            // "   - kompaktinio disko þymë;"
KPSTEDI_VOL_PROMPT3_EN,            KPSTEDI_VOL_PROMPT3_LT,            KPSTEDI_VOL_PROMPT3_PL_1250,            KPSTEDI_VOL_PROMPT3_PL_1257,            KPSTEDI_VOL_PROMPT3_RU,            KPSTEDI_VOL_PROMPT3_RU,            // "   - lokalaus duomenø serverio failo/serviso vardo pradþia (ðituo atveju turi bûti neilgesnis kaip 5 baitai);"
KPSTEDI_VOL_PROMPT4_EN,            KPSTEDI_VOL_PROMPT4_LT,            KPSTEDI_VOL_PROMPT4_PL_1250,            KPSTEDI_VOL_PROMPT4_PL_1257,            KPSTEDI_VOL_PROMPT4_RU,            KPSTEDI_VOL_PROMPT4_RU,            // "   - MIMOK Mano katalogo failø sàraðo .dat failo vardas be plëtinio (Mano_... katalogo vardo priesaga);"
KPSTEDI_VOL_PROMPT5_EN,            KPSTEDI_VOL_PROMPT5_LT,            KPSTEDI_VOL_PROMPT5_PL_1250,            KPSTEDI_VOL_PROMPT5_PL_1257,            KPSTEDI_VOL_PROMPT5_RU,            KPSTEDI_VOL_PROMPT5_RU,            // "   - StartSel.exe atmintuko pririðimo .ini failo vardas be plëtinio (= paleidimo .exe failo vardas)."

// Paleistis
KPSTEDI_CMD_STR_PROMPT_EN,         KPSTEDI_CMD_STR_PROMPT_LT,         KPSTEDI_CMD_STR_PROMPT_PL_1250,         KPSTEDI_CMD_STR_PROMPT_PL_1257,         KPSTEDI_CMD_STR_PROMPT_RU,         KPSTEDI_CMD_STR_PROMPT_RU,         // "Paleidimo komanda"
KPSTEDI_CMD_STR_PROMPT1_EN,        KPSTEDI_CMD_STR_PROMPT1_LT,        KPSTEDI_CMD_STR_PROMPT1_PL_1250,        KPSTEDI_CMD_STR_PROMPT1_PL_1257,        KPSTEDI_CMD_STR_PROMPT1_RU,        KPSTEDI_CMD_STR_PROMPT1_RU,        // "Visos komandos gali bûti tiesiog failo vardas, kurio prievardþiui priskirta standartinë programa."
KPSTEDI_CMD_STR_PROMPT2_EN,        KPSTEDI_CMD_STR_PROMPT2_LT,        KPSTEDI_CMD_STR_PROMPT2_PL_1250,        KPSTEDI_CMD_STR_PROMPT2_PL_1257,        KPSTEDI_CMD_STR_PROMPT2_RU,        KPSTEDI_CMD_STR_PROMPT2_RU,        // "Paleidimo komandoje galima naudoti makrokomandas:"
KPSTEDI_CMD_STR_PROMPT3_EN,        KPSTEDI_CMD_STR_PROMPT3_LT,        KPSTEDI_CMD_STR_PROMPT3_PL_1250,        KPSTEDI_CMD_STR_PROMPT3_PL_1257,        KPSTEDI_CMD_STR_PROMPT3_RU,        KPSTEDI_CMD_STR_PROMPT3_RU,        // "   {att} - sugeneruotas priekabos failo vardas su keliu, bet be prievardþio;"
KPSTEDI_CMD_STR_PROMPT4_EN,        KPSTEDI_CMD_STR_PROMPT4_LT,        KPSTEDI_CMD_STR_PROMPT4_PL_1250,        KPSTEDI_CMD_STR_PROMPT4_PL_1257,        KPSTEDI_CMD_STR_PROMPT4_RU,        KPSTEDI_CMD_STR_PROMPT4_RU,        // "   {prog} - paleidëjo programos failo vardas (tik vardas, be kelio ir prievardþio);"
KPSTEDI_CMD_STR_PROMPT5_EN,        KPSTEDI_CMD_STR_PROMPT5_LT,        KPSTEDI_CMD_STR_PROMPT5_PL_1250,        KPSTEDI_CMD_STR_PROMPT5_PL_1257,        KPSTEDI_CMD_STR_PROMPT5_RU,        KPSTEDI_CMD_STR_PROMPT5_RU,        // "   {user} - kelias iki katalogo, kuriame yra paleidþiamos programos katalogas"
KPSTEDI_CMD_STR_PROMPT6_EN,        KPSTEDI_CMD_STR_PROMPT6_LT,        KPSTEDI_CMD_STR_PROMPT6_PL_1250,        KPSTEDI_CMD_STR_PROMPT6_PL_1257,        KPSTEDI_CMD_STR_PROMPT6_RU,        KPSTEDI_CMD_STR_PROMPT6_RU,        // "      (vienu aukðtesnis katalogas, naudojamas dinaminiam paleidimui ið atmintukø)."
KPSTEDI_ATTOFF_PROMPT_EN,          KPSTEDI_ATTOFF_PROMPT_LT,          KPSTEDI_ATTOFF_PROMPT_PL_1250,          KPSTEDI_ATTOFF_PROMPT_PL_1257,          KPSTEDI_ATTOFF_PROMPT_RU,          KPSTEDI_ATTOFF_PROMPT_RU,          // "Priekabos pradþia"
KPSTEDI_ATTEXT_PROMPT_EN,          KPSTEDI_ATTEXT_PROMPT_LT,          KPSTEDI_ATTEXT_PROMPT_PL_1250,          KPSTEDI_ATTEXT_PROMPT_PL_1257,          KPSTEDI_ATTEXT_PROMPT_RU,          KPSTEDI_ATTEXT_PROMPT_RU,          // "Priekabos prievardis"
KPSTEDI_PROL_PROMPT_EN,            KPSTEDI_PROL_PROMPT_LT,            KPSTEDI_PROL_PROMPT_PL_1250,            KPSTEDI_PROL_PROMPT_PL_1257,            KPSTEDI_PROL_PROMPT_RU,            KPSTEDI_PROL_PROMPT_RU,            // "Áþangos komanda"
KPSTEDI_PROL_TIME_PROMPT_EN,       KPSTEDI_PROL_TIME_PROMPT_LT,       KPSTEDI_PROL_TIME_PROMPT_PL_1250,       KPSTEDI_PROL_TIME_PROMPT_PL_1257,       KPSTEDI_PROL_TIME_PROMPT_RU,       KPSTEDI_PROL_TIME_PROMPT_RU,       // "Áþangos trukmë"
KPSTEDI_SEC_PROMPT_EN,             KPSTEDI_SEC_PROMPT_LT,             KPSTEDI_SEC_PROMPT_PL_1250,             KPSTEDI_SEC_PROMPT_PL_1257,             KPSTEDI_SEC_PROMPT_RU,             KPSTEDI_SEC_PROMPT_RU,             // "sec"
KPSTEDI_BMP_PROMPT_EN,             KPSTEDI_BMP_PROMPT_LT,             KPSTEDI_BMP_PROMPT_PL_1250,             KPSTEDI_BMP_PROMPT_PL_1257,             KPSTEDI_BMP_PROMPT_RU,             KPSTEDI_BMP_PROMPT_RU,             // "Áþangos paveiksliukas"
KPSTEDI_BMP_SIZ_PROMPT_EN,         KPSTEDI_BMP_SIZ_PROMPT_LT,         KPSTEDI_BMP_SIZ_PROMPT_PL_1250,         KPSTEDI_BMP_SIZ_PROMPT_PL_1257,         KPSTEDI_BMP_SIZ_PROMPT_RU,         KPSTEDI_BMP_SIZ_PROMPT_RU,         // "Paveiksliuko dydis"
KPSTEDI_TIMES_PROMPT_EN,           KPSTEDI_TIMES_PROMPT_LT,           KPSTEDI_TIMES_PROMPT_PL_1250,           KPSTEDI_TIMES_PROMPT_PL_1257,           KPSTEDI_TIMES_PROMPT_RU,           KPSTEDI_TIMES_PROMPT_RU,           // "x"
KPSTEDI_BMP_PIX_PROMPT_EN,         KPSTEDI_BMP_PIX_PROMPT_LT,         KPSTEDI_BMP_PIX_PROMPT_PL_1250,         KPSTEDI_BMP_PIX_PROMPT_PL_1257,         KPSTEDI_BMP_PIX_PROMPT_RU,         KPSTEDI_BMP_PIX_PROMPT_RU,         // "taðkø"
KPSTEDI_MUTE_PROMPT_EN,            KPSTEDI_MUTE_PROMPT_LT,            KPSTEDI_MUTE_PROMPT_PL_1250,            KPSTEDI_MUTE_PROMPT_PL_1257,            KPSTEDI_MUTE_PROMPT_RU,            KPSTEDI_MUTE_PROMPT_RU,            // "Garsas iðjungtas"
KPSTEDI_EPIL_PROMPT_EN,            KPSTEDI_EPIL_PROMPT_LT,            KPSTEDI_EPIL_PROMPT_PL_1250,            KPSTEDI_EPIL_PROMPT_PL_1257,            KPSTEDI_EPIL_PROMPT_RU,            KPSTEDI_EPIL_PROMPT_RU,            // "Pabaigos komanda"
KPSTEDI_EPIL_TIME_PROMPT_EN,       KPSTEDI_EPIL_TIME_PROMPT_LT,       KPSTEDI_EPIL_TIME_PROMPT_PL_1250,       KPSTEDI_EPIL_TIME_PROMPT_PL_1257,       KPSTEDI_EPIL_TIME_PROMPT_RU,       KPSTEDI_EPIL_TIME_PROMPT_RU,       // "Pabaigos trukmë"
KPSTEDI_ONTOP_PROMPT_EN,           KPSTEDI_ONTOP_PROMPT_LT,           KPSTEDI_ONTOP_PROMPT_PL_1250,           KPSTEDI_ONTOP_PROMPT_PL_1257,           KPSTEDI_ONTOP_PROMPT_RU,           KPSTEDI_ONTOP_PROMPT_RU,           // "Uþdrausti kitø programø paleidimà"
KPSTEDI_FULLSCR_PROMPT_EN,         KPSTEDI_FULLSCR_PROMPT_LT,         KPSTEDI_FULLSCR_PROMPT_PL_1250,         KPSTEDI_FULLSCR_PROMPT_PL_1257,         KPSTEDI_FULLSCR_PROMPT_RU,         KPSTEDI_FULLSCR_PROMPT_RU,         // "Pilno ekrano reþimas"
KPSTEDI_CLRCLIPBRD_PROMPT_EN,      KPSTEDI_CLRCLIPBRD_PROMPT_LT,      KPSTEDI_CLRCLIPBRD_PROMPT_PL_1250,      KPSTEDI_CLRCLIPBRD_PROMPT_PL_1257,      KPSTEDI_CLRCLIPBRD_PROMPT_RU,      KPSTEDI_CLRCLIPBRD_PROMPT_RU,      // "Trinti iðkarpinæ"
KPSTEDI_SUBST_PROMPT_EN,           KPSTEDI_SUBST_PROMPT_LT,           KPSTEDI_SUBST_PROMPT_PL_1250,           KPSTEDI_SUBST_PROMPT_PL_1257,           KPSTEDI_SUBST_PROMPT_RU,           KPSTEDI_SUBST_PROMPT_RU,           // "Paleisti virtualiame diske"
KPSTEDI_EBOARD_PROMPT_EN,          KPSTEDI_EBOARD_PROMPT_LT,          KPSTEDI_EBOARD_PROMPT_PL_1250,          KPSTEDI_EBOARD_PROMPT_PL_1257,          KPSTEDI_EBOARD_PROMPT_RU,          KPSTEDI_EBOARD_PROMPT_RU,          // "Elektroninë lenta"
KPSTEDI_SHIE_PROMPT_EN,            KPSTEDI_SHIE_PROMPT_LT,            KPSTEDI_SHIE_PROMPT_PL_1250,            KPSTEDI_SHIE_PROMPT_PL_1257,            KPSTEDI_SHIE_PROMPT_RU,            KPSTEDI_SHIE_PROMPT_RU,            // "Paleisti IE"
KPSTEDI_HBMARKS_PROMPT_EN,         KPSTEDI_HBMARKS_PROMPT_LT,         KPSTEDI_HBMARKS_PROMPT_PL_1250,         KPSTEDI_HBMARKS_PROMPT_PL_1257,         KPSTEDI_HBMARKS_PROMPT_RU,         KPSTEDI_HBMARKS_PROMPT_RU,         // "Slëpti bookmarkus"
KPSTEDI_SNDMUT_PROMPT_EN,          KPSTEDI_SNDMUT_PROMPT_LT,          KPSTEDI_SNDMUT_PROMPT_PL_1250,          KPSTEDI_SNDMUT_PROMPT_PL_1257,          KPSTEDI_SNDMUT_PROMPT_RU,          KPSTEDI_SNDMUT_PROMPT_RU,          // "Garsas iðjungtas"
KPSTEDI_TESTUPD_PROMPT_EN,         KPSTEDI_TESTUPD_PROMPT_LT,         KPSTEDI_TESTUPD_PROMPT_PL_1250,         KPSTEDI_TESTUPD_PROMPT_PL_1257,         KPSTEDI_TESTUPD_PROMPT_RU,         KPSTEDI_TESTUPD_PROMPT_RU,         // "Tikrinti atnaujinimus"
KPSTEDI_FINDBUT_PROMPT_EN,         KPSTEDI_FINDBUT_PROMPT_LT,         KPSTEDI_FINDBUT_PROMPT_PL_1250,         KPSTEDI_FINDBUT_PROMPT_PL_1257,         KPSTEDI_FINDBUT_PROMPT_RU,         KPSTEDI_FINDBUT_PROMPT_RU,         // "Paieðkos mygtukas"

// Pririðimas
KPSTEDI_BOUND_PROMPT_EN,           KPSTEDI_BOUND_PROMPT_LT,           KPSTEDI_BOUND_PROMPT_PL_1250,           KPSTEDI_BOUND_PROMPT_PL_1257,           KPSTEDI_BOUND_PROMPT_RU,           KPSTEDI_BOUND_PROMPT_RU,           // "Pririðti prie kompiuterio"
KPSTEDI_BOUND_PROMPT1_EN,          KPSTEDI_BOUND_PROMPT1_LT,          KPSTEDI_BOUND_PROMPT1_PL_1250,          KPSTEDI_BOUND_PROMPT1_PL_1257,          KPSTEDI_BOUND_PROMPT1_RU,          KPSTEDI_BOUND_PROMPT1_RU,          // "(lokalaus licencijø serverio)"
KPSTEDI_CITYP_PROMPT_EN,           KPSTEDI_CITYP_PROMPT_LT,           KPSTEDI_CITYP_PROMPT_PL_1250,           KPSTEDI_CITYP_PROMPT_PL_1257,           KPSTEDI_CITYP_PROMPT_RU,           KPSTEDI_CITYP_PROMPT_RU,           // "Kompiuterio ID"
KPSTEDI_CITYP_PROMPT_B_EN,         KPSTEDI_CITYP_PROMPT_B_LT,         KPSTEDI_CITYP_PROMPT_B_PL_1250,         KPSTEDI_CITYP_PROMPT_B_PL_1257,         KPSTEDI_CITYP_PROMPT_B_RU,         KPSTEDI_CITYP_PROMPT_B_RU,         // "BIOS data"
KPSTEDI_CITYP_PROMPT_D_EN,         KPSTEDI_CITYP_PROMPT_D_LT,         KPSTEDI_CITYP_PROMPT_D_PL_1250,         KPSTEDI_CITYP_PROMPT_D_PL_1257,         KPSTEDI_CITYP_PROMPT_D_RU,         KPSTEDI_CITYP_PROMPT_D_RU,         // "HD Serijinis Nr."
KPSTEDI_CITYP_PROMPT_P_EN,         KPSTEDI_CITYP_PROMPT_P_LT,         KPSTEDI_CITYP_PROMPT_P_PL_1250,         KPSTEDI_CITYP_PROMPT_P_PL_1257,         KPSTEDI_CITYP_PROMPT_P_RU,         KPSTEDI_CITYP_PROMPT_P_RU,         // "Procesoriaus ID"
KPSTEDI_CITYP_PROMPT_N_EN,         KPSTEDI_CITYP_PROMPT_N_LT,         KPSTEDI_CITYP_PROMPT_N_PL_1250,         KPSTEDI_CITYP_PROMPT_N_PL_1257,         KPSTEDI_CITYP_PROMPT_N_RU,         KPSTEDI_CITYP_PROMPT_N_RU,         // "Procesoriaus vardas"
KPSTEDI_CITYP_PROMPT_M_EN,         KPSTEDI_CITYP_PROMPT_M_LT,         KPSTEDI_CITYP_PROMPT_M_PL_1250,         KPSTEDI_CITYP_PROMPT_M_PL_1257,         KPSTEDI_CITYP_PROMPT_M_RU,         KPSTEDI_CITYP_PROMPT_M_RU,         // "MAC adresas"
KPSTEDI_CITYP_PROMPT_V_EN,         KPSTEDI_CITYP_PROMPT_V_LT,         KPSTEDI_CITYP_PROMPT_V_PL_1250,         KPSTEDI_CITYP_PROMPT_V_PL_1257,         KPSTEDI_CITYP_PROMPT_V_RU,         KPSTEDI_CITYP_PROMPT_V_RU,         // "Programinis „varþtas“"
KPSTEDI_CIDIR_PROMPT_EN,           KPSTEDI_CIDIR_PROMPT_LT,           KPSTEDI_CIDIR_PROMPT_PL_1250,           KPSTEDI_CIDIR_PROMPT_PL_1257,           KPSTEDI_CIDIR_PROMPT_RU,           KPSTEDI_CIDIR_PROMPT_RU,           // "Kompiuterio ID skaityti"
KPSTEDI_CIDIR_PROMPT1_EN,          KPSTEDI_CIDIR_PROMPT1_LT,          KPSTEDI_CIDIR_PROMPT1_PL_1250,          KPSTEDI_CIDIR_PROMPT1_PL_1257,          KPSTEDI_CIDIR_PROMPT1_RU,          KPSTEDI_CIDIR_PROMPT1_RU,          // "tiesiogiai ið HW"
KPSTEDI_CIDIR_PROMPT2_EN,          KPSTEDI_CIDIR_PROMPT2_LT,          KPSTEDI_CIDIR_PROMPT2_PL_1250,          KPSTEDI_CIDIR_PROMPT2_PL_1257,          KPSTEDI_CIDIR_PROMPT2_RU,          KPSTEDI_CIDIR_PROMPT2_RU,          // "ið slapto failo"

KPSTEDI_REGURL_PROMPT_EN,          KPSTEDI_REGURL_PROMPT_LT,          KPSTEDI_REGURL_PROMPT_PL_1250,          KPSTEDI_REGURL_PROMPT_PL_1257,          KPSTEDI_REGURL_PROMPT_RU,          KPSTEDI_REGURL_PROMPT_RU,          // "Registravimosi URL arba"
KPSTEDI_REGURL_PROMPT1_EN,         KPSTEDI_REGURL_PROMPT1_LT,         KPSTEDI_REGURL_PROMPT1_PL_1250,         KPSTEDI_REGURL_PROMPT1_PL_1257,         KPSTEDI_REGURL_PROMPT1_RU,         KPSTEDI_REGURL_PROMPT1_RU,         // "lokalaus serverio adresas"

KPSTEDI_LICNUM_PROMPT_EN,          KPSTEDI_LICNUM_PROMPT_LT,          KPSTEDI_LICNUM_PROMPT_PL_1250,          KPSTEDI_LICNUM_PROMPT_PL_1257,          KPSTEDI_LICNUM_PROMPT_RU,          KPSTEDI_LICNUM_PROMPT_RU,          // "Lokaliø licencijø sk."
KPSTEDI_BOUND_FL_PROMPT_EN,        KPSTEDI_BOUND_FL_PROMPT_LT,        KPSTEDI_BOUND_FL_PROMPT_PL_1250,        KPSTEDI_BOUND_FL_PROMPT_PL_1257,        KPSTEDI_BOUND_FL_PROMPT_RU,        KPSTEDI_BOUND_FL_PROMPT_RU,        // "Pririðti prie atmintuko") // :") // "Ar pririðti prie Flash'o:"

KPSTEDI_FLASH_ID_PROMPT_EN,        KPSTEDI_FLASH_ID_PROMPT_LT,        KPSTEDI_FLASH_ID_PROMPT_PL_1250,        KPSTEDI_FLASH_ID_PROMPT_PL_1257,        KPSTEDI_FLASH_ID_PROMPT_RU,        KPSTEDI_FLASH_ID_PROMPT_RU,        // "Atmintuko ID"
KPSTEDI_LIC_ID_PROMPT_EN,          KPSTEDI_LIC_ID_PROMPT_LT,          KPSTEDI_LIC_ID_PROMPT_PL_1250,          KPSTEDI_LIC_ID_PROMPT_PL_1257,          KPSTEDI_LIC_ID_PROMPT_RU,          KPSTEDI_LIC_ID_PROMPT_RU,          // "Licencijos kodas"
KPSTEDI_LIC_ID_PROMPT1_EN,         KPSTEDI_LIC_ID_PROMPT1_LT,         KPSTEDI_LIC_ID_PROMPT1_PL_1250,         KPSTEDI_LIC_ID_PROMPT1_PL_1257,         KPSTEDI_LIC_ID_PROMPT1_RU,         KPSTEDI_LIC_ID_PROMPT1_RU,         // "Naudojamas produkto papildymo pririðimui prie konkreèios licencijos."

KPSTEDI_PWD_WND_PROMPT_EN,         KPSTEDI_PWD_WND_PROMPT_LT,         KPSTEDI_PWD_WND_PROMPT_PL_1250,         KPSTEDI_PWD_WND_PROMPT_PL_1257,         KPSTEDI_PWD_WND_PROMPT_RU,         KPSTEDI_PWD_WND_PROMPT_RU,         // "Slaptaþodþio/programos langas"
KPSTEDI_PWD_WND_PROMPT1_EN,        KPSTEDI_PWD_WND_PROMPT1_LT,        KPSTEDI_PWD_WND_PROMPT1_PL_1250,        KPSTEDI_PWD_WND_PROMPT1_PL_1257,        KPSTEDI_PWD_WND_PROMPT1_RU,        KPSTEDI_PWD_WND_PROMPT1_RU,        // "Atsiradus ðiam langui, stabdoma áþanga / naikinamas paveiksliukas."
KPSTEDI_PWD_PROMPT_EN,             KPSTEDI_PWD_PROMPT_LT,             KPSTEDI_PWD_PROMPT_PL_1250,             KPSTEDI_PWD_PROMPT_PL_1257,             KPSTEDI_PWD_PROMPT_RU,             KPSTEDI_PWD_PROMPT_RU,             // "Slaptaþodis"
KPSTEDI_OLD_PWD_PROMPT_EN,         KPSTEDI_OLD_PWD_PROMPT_LT,         KPSTEDI_OLD_PWD_PROMPT_PL_1250,         KPSTEDI_OLD_PWD_PROMPT_PL_1257,         KPSTEDI_OLD_PWD_PROMPT_RU,         KPSTEDI_OLD_PWD_PROMPT_RU,         // "Senas slaptaþodis"
KPSTEDI_PWD_EDIT_PROMPT_EN,        KPSTEDI_PWD_EDIT_PROMPT_LT,        KPSTEDI_PWD_EDIT_PROMPT_PL_1250,        KPSTEDI_PWD_EDIT_PROMPT_PL_1257,        KPSTEDI_PWD_EDIT_PROMPT_RU,        KPSTEDI_PWD_EDIT_PROMPT_RU,        // "Slaptaþodþio ávedimo lauko id."
KPSTEDI_PWD_BUT_PROMPT_EN,         KPSTEDI_PWD_BUT_PROMPT_LT,         KPSTEDI_PWD_BUT_PROMPT_PL_1250,         KPSTEDI_PWD_BUT_PROMPT_PL_1257,         KPSTEDI_PWD_BUT_PROMPT_RU,         KPSTEDI_PWD_BUT_PROMPT_RU,         // "Mygtuko „OK” id."
KPSTEDI_CHCD_PROMPT_EN,            KPSTEDI_CHCD_PROMPT_LT,            KPSTEDI_CHCD_PROMPT_PL_1250,            KPSTEDI_CHCD_PROMPT_PL_1257,            KPSTEDI_CHCD_PROMPT_RU,            KPSTEDI_CHCD_PROMPT_RU,            // "Reikalauti CD"

// Duomenys
KPSTEDI_INI_PROMPT_EN,             KPSTEDI_INI_PROMPT_LT,             KPSTEDI_INI_PROMPT_PL_1250,             KPSTEDI_INI_PROMPT_PL_1257,             KPSTEDI_INI_PROMPT_RU,             KPSTEDI_INI_PROMPT_RU,             // "Inicializavimo failas"
KPSTEDI_INI_PROMPT1_EN,            KPSTEDI_INI_PROMPT1_LT,            KPSTEDI_INI_PROMPT1_PL_1250,            KPSTEDI_INI_PROMPT1_PL_1257,            KPSTEDI_INI_PROMPT1_RU,            KPSTEDI_INI_PROMPT1_RU,            // "Jo turinys perkeliamas á iðkarpinæ prieð paleidþiant pagrindinæ komandà."

KPSTEDI_REZ_PROMPT_EN,             KPSTEDI_REZ_PROMPT_LT,             KPSTEDI_REZ_PROMPT_PL_1250,             KPSTEDI_REZ_PROMPT_PL_1257,             KPSTEDI_REZ_PROMPT_RU,             KPSTEDI_REZ_PROMPT_RU,             // "Rezultatø failas"

KPSTEDI_REZ_VAR_PROMPT_EN,         KPSTEDI_REZ_VAR_PROMPT_LT,         KPSTEDI_REZ_VAR_PROMPT_PL_1250,         KPSTEDI_REZ_VAR_PROMPT_PL_1257,         KPSTEDI_REZ_VAR_PROMPT_RU,         KPSTEDI_REZ_VAR_PROMPT_RU,         // "Rez. kintamieji"
KPSTEDI_SHUFF_PROMPT_EN,           KPSTEDI_SHUFF_PROMPT_LT,           KPSTEDI_SHUFF_PROMPT_PL_1250,           KPSTEDI_SHUFF_PROMPT_PL_1257,           KPSTEDI_SHUFF_PROMPT_RU,           KPSTEDI_SHUFF_PROMPT_RU,           // "Maiðomø laukø sk. (nedaugiau 9)"
KPSTEDI_CUMUL_PROMPT_EN,           KPSTEDI_CUMUL_PROMPT_LT,           KPSTEDI_CUMUL_PROMPT_PL_1250,           KPSTEDI_CUMUL_PROMPT_PL_1257,           KPSTEDI_CUMUL_PROMPT_RU,           KPSTEDI_CUMUL_PROMPT_RU,           // "Rezultatus prijungti prie jau esanèiø"
KPSTEDI_TESTC_PROMPT_EN,           KPSTEDI_TESTC_PROMPT_LT,           KPSTEDI_TESTC_PROMPT_PL_1250,           KPSTEDI_TESTC_PROMPT_PL_1257,           KPSTEDI_TESTC_PROMPT_RU,           KPSTEDI_TESTC_PROMPT_RU,           // "Testo identifikatorius"

// Naudotojas
KPSTEDI_USER_PWD_PROMPT_EN,        KPSTEDI_USER_PWD_PROMPT_LT,        KPSTEDI_USER_PWD_PROMPT_PL_1250,        KPSTEDI_USER_PWD_PROMPT_PL_1257,        KPSTEDI_USER_PWD_PROMPT_RU,        KPSTEDI_USER_PWD_PROMPT_RU,        // "Slaptaþodis"

KPSTEDI_REPEAT_PWD_PROMPT_EN,      KPSTEDI_REPEAT_PWD_PROMPT_LT,      KPSTEDI_REPEAT_PWD_PROMPT_PL_1250,      KPSTEDI_REPEAT_PWD_PROMPT_PL_1257,      KPSTEDI_REPEAT_PWD_PROMPT_RU,      KPSTEDI_REPEAT_PWD_PROMPT_RU,      // "Pakartokite slaptaþodá"

KPSTEDI_ADMIN_PWD_PROMPT_EN,       KPSTEDI_ADMIN_PWD_PROMPT_LT,       KPSTEDI_ADMIN_PWD_PROMPT_PL_1250,       KPSTEDI_ADMIN_PWD_PROMPT_PL_1257,       KPSTEDI_ADMIN_PWD_PROMPT_RU,       KPSTEDI_ADMIN_PWD_PROMPT_RU,       // "Atmintuko licencija"

KPSTEDI_USER_DATA_PROMPT_EN,       KPSTEDI_USER_DATA_PROMPT_LT,       KPSTEDI_USER_DATA_PROMPT_PL_1250,       KPSTEDI_USER_DATA_PROMPT_PL_1257,       KPSTEDI_USER_DATA_PROMPT_RU,       KPSTEDI_USER_DATA_PROMPT_RU,       // "Naudotojas"

KPSTEDI_SEL_REZ_FILE_EN,           KPSTEDI_SEL_REZ_FILE_LT,           KPSTEDI_SEL_REZ_FILE_PL_1250,           KPSTEDI_SEL_REZ_FILE_PL_1257,           KPSTEDI_SEL_REZ_FILE_RU,           KPSTEDI_SEL_REZ_FILE_RU,           // "Pasirinkite rezultatø failà"

KPSTEDI_SURE_CHANGE_PWD_EN,        KPSTEDI_SURE_CHANGE_PWD_LT,        KPSTEDI_SURE_CHANGE_PWD_PL_1250,        KPSTEDI_SURE_CHANGE_PWD_PL_1257,        KPSTEDI_SURE_CHANGE_PWD_RU,        KPSTEDI_SURE_CHANGE_PWD_RU,        // "Jûs ávedëte paleidimo slaptaþodá. Jo bus reikalaujama kiekvieno programos paleidimo metu.\n \nAr sutinkate?"
KPSTEDI_PWD_NOT_MATCH_EN,          KPSTEDI_PWD_NOT_MATCH_LT,          KPSTEDI_PWD_NOT_MATCH_PL_1250,          KPSTEDI_PWD_NOT_MATCH_PL_1257,          KPSTEDI_PWD_NOT_MATCH_RU,          KPSTEDI_PWD_NOT_MATCH_RU,          // "Slaptaþodþiai nesutampa."
KPSTEDI_USER_PWD_NOT_MATCH_EN,     KPSTEDI_USER_PWD_NOT_MATCH_LT,     KPSTEDI_USER_PWD_NOT_MATCH_PL_1250,     KPSTEDI_USER_PWD_NOT_MATCH_PL_1257,     KPSTEDI_USER_PWD_NOT_MATCH_RU,     KPSTEDI_USER_PWD_NOT_MATCH_RU,     // "Paleidimo slaptaþodþiai nesutampa."
// KPSTEDI_ADMIN_PWD_NOT_MATCH_EN, // KPSTEDI_ADMIN_PWD_NOT_MATCH_LT, // KPSTEDI_ADMIN_PWD_NOT_MATCH_PL_1250, // KPSTEDI_ADMIN_PWD_NOT_MATCH_PL_1257, // KPSTEDI_ADMIN_PWD_NOT_MATCH_RU, // KPSTEDI_ADMIN_PWD_NOT_MATCH_RU, // "Redagavimo slaptaþodþiai nesutampa."

KPSTEDI_REZ_FILES_EN,              KPSTEDI_REZ_FILES_LT,              KPSTEDI_REZ_FILES_PL_1250,              KPSTEDI_REZ_FILES_PL_1257,              KPSTEDI_REZ_FILES_RU,              KPSTEDI_REZ_FILES_RU,              // "Resultatø failai"

KPSTEDI_NO_FLASH_LIC_EN,           KPSTEDI_NO_FLASH_LIC_LT,           KPSTEDI_NO_FLASH_LIC_PL_1250,           KPSTEDI_NO_FLASH_LIC_PL_1257,           KPSTEDI_NO_FLASH_LIC_RU,           KPSTEDI_NO_FLASH_LIC_RU,           // "Atmintuko licencija nenurodyta arba parametrai sukeisti vietomis"

KPSTEDI_LIC_FL_PROMPT_EN,          KPSTEDI_LIC_FL_PROMPT_LT,          KPSTEDI_LIC_FL_PROMPT_PL_1250,          KPSTEDI_LIC_FL_PROMPT_PL_1257,          KPSTEDI_LIC_FL_PROMPT_RU,          KPSTEDI_LIC_FL_PROMPT_RU,          // "Licencijuotas atmintukas"
};

// ----------------------------------
KpStEdiDlg::KpStEdiDlg(void)
{
   m_lhOpenResult=S_OK;

   if(SUCCEEDED(m_lhOpenResult)) m_lhOpenResult=ClearControls();

   m_bShiftFl=False;
   m_bOpenFileFl=False;

   m_lpszErrTxt=(const unsigned char *)"";

#if FALSE
   if(iWindowsVersion<Win2000c) KpWinColorScheme[KpShadowNorm]=RGB(191,191,191); // Win98
   else if(iWindowsVersion<WinXP) KpWinColorScheme[KpShadowNorm]=RGB(214,211,206); // W2k
   else KpWinColorScheme[KpShadowNorm]=RGB(236,233,216); // WinXP
#endif

#if FALSE // KPSTEDI_MODE & GENERAL_MODE
int ii;
   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
      m_aPenScheme[ii]=CreatePen(PS_SOLID, 1, KpWinColorScheme[ii]);
      if(m_aPenScheme[ii]==NULL)
      /* m_lhOpenResult= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }
#endif
}


// ----------------------------------
HRESULT KpStEdiDlg::ClearControls(void)
{
   m_hDialogWindow=NULL;

// #if KPSTEDI_MODE & STARTER_MODE
   m_ExplPrompt1=NULL;
// #endif

// #if KPSTEDI_MODE & GENERAL_MODE
   m_TabCtrl = NULL;

   m_TabProduct = NULL;
   m_TabStart = NULL;
   m_TabBound = NULL;
   m_TabData = NULL;
   m_TabUser = NULL;

   m_CurTab = NULL;

   m_CmdStrEdit=NULL;
   m_Publisher=NULL;
   m_ChCDBox=NULL;
   m_AttOff=NULL;
   m_ProdVer = NULL;
   m_UpdNum = NULL;
   m_BoundBox=NULL;
   m_AttExt=NULL;
   m_NumOfLics=NULL;
   m_TestCid=NULL;
   m_BoundFlashBox=NULL;
   m_LicFlashBox=NULL;
   m_ProdName=NULL;
   m_WndName = NULL;
   m_ProlEdit=NULL;
   m_ProlTimeEdit=NULL;
   m_EpilEdit=NULL;
   m_EpilTimeEdit=NULL;
   m_BmpEdit=NULL;
   m_BmpDxEdit=NULL;
   m_BmpDyEdit=NULL;
   m_PwdWndEdit=NULL;
   m_PwdEdit=NULL;
   m_OldPwdEdit=NULL;
   m_CiDirBox=NULL;
   m_CiFileBox = NULL;
   m_CiTypBBox = NULL;
   m_CiTypDBox = NULL;
   m_CiTypPBox = NULL;
   m_CiTypNBox = NULL;
   m_CiTypMBox = NULL;
   m_CiTypVBox = NULL;
   m_PwdEditEdit=NULL;
   m_PwdButEdit=NULL;
   m_VolEdit=NULL;
   m_PresEdit=NULL;
   m_RezVarEdit=NULL;
   m_ShuffCnt=NULL;
   m_CumulBox=NULL;
   m_OnTopBox = NULL;
   m_MuteBox = NULL;
   m_FullScrBox = NULL;
   m_SubstBox = NULL;
   m_EboardBox = NULL;
   m_ClearClipBrdBox = NULL;
   m_ShIEBox = NULL;
   m_HideBkmrksBox = NULL;
   m_SoundMutedBox = NULL;
   m_TestUpdatesBox = NULL;
   m_FindButBox = NULL;

// #endif

// #if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
   m_RegURL=NULL;
// #endif
// #if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
   m_RezEdit=NULL;
   m_RezButton=NULL;
// #endif

// #if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
   m_FlashId=NULL;
   m_IniLicID=NULL;
// #endif

// #if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
   m_UserPwdEdit = NULL;
// #if KPSTEDI_MODE & OWNER_MODE
   m_UserPwd2Edit = NULL;
// #endif
// #if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
   m_AdminPwdEdit = NULL;
// m_AdminPwd2Edit = NULL;
// #endif
   m_UserDataEdit = NULL;
// #endif

   m_OkButton=NULL;
   m_CancelButton=NULL;

return(S_OK);
}


// ----------------------------------
KpStEdiDlg::~KpStEdiDlg(void)
{
#if FALSE // KPSTEDI_MODE & GENERAL_MODE
int ii;

   for(ii=0; ii<KpNumOfShadows0; ii++)
   {
      if(m_aPenScheme[ii]!=NULL)
         if(!DeleteObject(m_aPenScheme[ii]))
         {
      /* retc= */ KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
         }
      m_aPenScheme[ii]=NULL;
   }
#endif
}


// ----------------------
HRESULT KpStEdiDlg::GetOpenResult(void)
{
return(m_lhOpenResult);
}


// ----------------------------------
HRESULT KpStEdiDlg::OpenWindow(const unsigned char *lpszErrorText)
{
HRESULT retc=S_OK;
WNDCLASSEX wcx;
unsigned char str_tmp[KP_MAX_FNAME_LEN+100];
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
int win_dy = 0;
#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == USER_MODE
int num_of_lics = 0;
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
#endif
#if (KPSTEDI_MODE & BOUND_MODE)
bool bound_flash = False;
bool lic_flash = False;
#endif

   if((theKpStAppPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
      if(theKpStAppPtr->m_hInstance==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc))
   {
      m_lpszErrTxt=(const unsigned char *)"";
      if(lpszErrorText!=NULL) m_lpszErrTxt=lpszErrorText;
   }

   if(SUCCEEDED(retc)) retc = theKpStAppPtr->GetIniProdName(prod_name);
#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == USER_MODE
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniNumOfLics(&num_of_lics);
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniRezFName(rez_fname);
#endif
#if (KPSTEDI_MODE & BOUND_MODE)
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCheckFlash(&bound_flash);
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniLicFlash(&lic_flash);
#endif

   if(m_hDialogWindow==NULL)
   {
      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = theKpStAppPtr->m_hInstance;
         wcx.lpszClassName = "KPSTEDI",
         wcx.lpfnWndProc   = (WNDPROC)KpStEdiDialogProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(theKpStAppPtr->m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
         wcx.hIconSm       = LoadIcon(theKpStAppPtr->m_hInstance, MAKEINTRESOURCE(KP_IDI_SETUP_ICON /* IDI_APPLICATION */));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

         if(!RegisterClassEx(&wcx))
         {
//          retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc))
      {
#if KPSTEDI_MODE & LOGIN_MODE
         strcpy(str_tmp,  "Login");
#else
         strcpy(str_tmp, "Edini");
#  if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == 0
         strcat(str_tmp, " - [");
         strcat(str_tmp, theKpStAppPtr->m_lpszIniFName);
         strcat(str_tmp, "]");
#  else
         strcat(str_tmp, " - ");
         strcat(str_tmp, prod_name);
#  endif
#endif

         win_dy = KPSTEDI_WND_DY;
#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == USER_MODE
#ifndef NO_DIRECT_REZ_FILE
         if(num_of_lics) win_dy += KPSTEDI_CTRL_HGT; // kai num_of_lics>0 ar -1
#endif
         if(rez_fname[0]) win_dy += KPSTEDI_CTRL_HGT;
#endif

         m_hDialogWindow=CreateWindowEx
         (
            0,                      // DWORD dwExStyle,      // extended window style
            "KPSTEDI",
            (const char *)str_tmp,                // LPCTSTR lpWindowName, // pointer to window name
            WS_POPUPWINDOW|WS_VISIBLE|WS_CAPTION|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            KPSTEDI_WND_X, // CW_USEDEFAULT, // int x,               // horizontal position of window
            KPSTEDI_WND_Y, // CW_USEDEFAULT, // int y,               // vertical position of window
            KPSTEDI_WND_DX,         // int nWidth,           // window width
            win_dy,         // int nHeight,          // window height
            HWND_DESKTOP,           // HWND hWndParent,      // handle to parent or owner window
            0,                      // HMENU hMenu,          // handle to menu, or child-window identifier
            theKpStAppPtr->m_hInstance,
            NULL                    // LPVOID lpParam        // pointer to window-creation data
         );

         if(m_hDialogWindow==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }
#if KPSTEDI_MODE & STARTER_MODE
   else // if(m_hDialogWindow==NULL)
   {
      if((m_ExplPrompt1==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(m_ExplPrompt1, WM_SETTEXT, 0, (LPARAM)m_lpszErrTxt);
   }
#endif

return(retc);
}


// -----------------------------------------
BOOL CALLBACK KpStEdiDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HRESULT retc0;
BOOL retw=FALSE;
int retp;
bool endfl=False;
bool close_window=False;
unsigned char *str_buf = null;
int but_y = 0;

#if (KPSTEDI_MODE & (USER_MODE | OWNER_MODE)) == 0
unsigned char num_buf[MAX_LONG_DIGITS+1];
#endif

#if KPSTEDI_MODE & GENERAL_MODE
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
int prol_show_time;
unsigned char prol_fname[KP_MAX_FNAME_LEN+1];
int bmp_wdt;
int bmp_hgt;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[KP_KWD_LEN+1];
unsigned char old_pwd_buf[KP_KWD_LEN+1];
int pwd_ed_ctrl=0;
int pwd_ok_but=0;
unsigned char vol_name[KP_MAX_FNAME_LEN+1];
// long ser_no=0L;
unsigned char bmp_fname[KP_MAX_FNAME_LEN+1];
unsigned char epil_fname[KP_MAX_FNAME_LEN+1];
int epil_sh_time=0;
unsigned char pres_fname[KP_MAX_FNAME_LEN+1];
bool ch_cd=False;
bool bound=False;
int prod_ver = 0;
int upd_num = -1;
bool sh_ie = False;
bool hide_bkmrks = False;
bool sound_muted = False;
bool find_but = False;
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
bool test_upd = False;
#endif
#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == 0
bool bound_flash=False;
bool lic_flash = False;
#endif
#if (KPSTEDI_MODE & (BOUND_MODE | STARTER_MODE)) == 0
int num_of_lics=0;
#endif
#if KPSTEDI_MODE & GENERAL_MODE
unsigned char test_cid[KPST_TXTCD_CHARS_PER_VAL_TID+1];
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
unsigned char wnd_name[KP_MAX_FNAME_LEN+1];
unsigned char publisher[KP_MAX_FNAME_LEN+1];
unsigned char rez_var[KP_MAX_FNAME_LEN+1];
bool kumul=False;
int shuff_cnt=0;
long att_offset=0L;
unsigned char att_ext[KP_MAX_FTYPE_LEN+1];
bool cid_dir=False;
int cid_typ = 0;
bool on_top=False;
bool muted=False;
bool full_scr=False;
bool subst=False;
bool eboard=False;
bool clr_clipbrd = False;
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
unsigned char user_pwd_buf[KP_KWD_LEN + 1];
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
unsigned char user_data_buf[KP_MAX_FILE_LIN_WDT+1];
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
unsigned char admin_pwd_buf[KP_KWD_LEN+1];
#endif

#if KPSTEDI_MODE & GENERAL_MODE
TCITEM tie;
int ii;
WNDCLASSEX wcx;
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
unsigned char reg_url[KP_MAX_FNAME_LEN+1];
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
unsigned char rez_nam_sav[KP_MAX_FNAME_LEN+1];
unsigned char ini_dir[KP_MAX_FNAME_LEN+1];
OPENFILENAME op_fn_str;
unsigned char filters[100];
unsigned char *pnts;
unsigned char *pntd;
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
long flash_id=0L;
int lic_id = 0;
unsigned char lic_buf[KP_MAX_FILE_LIN_WDT+1];
#endif

#ifdef Debug
if(uMsg == WM_PARENTNOTIFY) // 528
uMsg = WM_PARENTNOTIFY;
#endif

#if KPSTEDI_MODE & (OWNER_MODE | BOUND_MODE | USER_MODE | STARTER_MODE)
HDC hdc = NULL;
PAINTSTRUCT ps;
#endif

   retp=LOWORD(wParam);
   endfl=False;
   close_window=False;

   if(((theKpStAppPtr==NULL) || (KpstEdiDialogPtr == NULL)) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == 0
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCheckFlash(&bound_flash);
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniLicFlash(&lic_flash);
#endif

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_CREATE:
#if KPSTEDI_MODE & GENERAL_MODE
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCmdStr(cmd_str);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProlShowTime(&prol_show_time);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProlFName(prol_fname);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniBitmapWdt(&bmp_wdt);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniBitmapHgt(&bmp_hgt);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPwdWndName(pwd_win_name);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPwd(pwd_buf);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniOldPwd(old_pwd_buf);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPwdEdCtrl(&pwd_ed_ctrl);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPwdOkBut(&pwd_ok_but);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniVolName(vol_name);
//    if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniSerNo(&ser_no);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniBmpFName(bmp_fname);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniEpilFName(epil_fname);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniEpilShowTime(&epil_sh_time);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPresetFName(pres_fname);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCheckCD(&ch_cd);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniBound(&bound);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdVer(&prod_ver);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniUpdNum(&upd_num);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniProdName(prod_name);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniWndName(wnd_name);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniPublisher(publisher);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniShowIE(&sh_ie);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniHideBkmrks(&hide_bkmrks);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniSoundMuted(&sound_muted);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniSoundMuted(&sound_muted);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniFindBut(&find_but);
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniTestUpdates(&test_upd);
#endif
#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == 0
//    if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCheckFlash(&bound_flash);
//    if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniLicFlash(&lic_flash);
#endif
#if (KPSTEDI_MODE & (BOUND_MODE | STARTER_MODE)) == 0
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniNumOfLics(&num_of_lics);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniTestCid(test_cid);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniRezVar(rez_var);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniKumul(&kumul);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniShuffCnt(&shuff_cnt);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniAttOff(&att_offset);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniAttExt(att_ext);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCiDirect(&cid_dir);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniCompIdMode(&cid_typ);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniOnTop(&on_top);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniSoundMuted(&muted);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniFullScr(&full_scr);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniSubst(&subst);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniEboard(&eboard);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniClearClipBrd(&clr_clipbrd);

#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniRegURL(reg_url);
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniRezFName(rez_fname);
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniFlashId(&flash_id);
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniIniLicID(&lic_id);
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniUserPwd(user_pwd_buf);
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniUserData(user_data_buf);
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniAdminPwd(admin_pwd_buf);
#endif

      KP_NEWA(str_buf, unsigned char, KPSTEDI_EDIT_MAX_CONTROL_CHARS + 1);

      if(SUCCEEDED(retc))
      {
         memset(str_buf, Spc, KPSTEDI_EDIT_MAX_CONTROL_CHARS);
         str_buf[KPSTEDI_EDIT_MAX_CONTROL_CHARS]=Nul;
      }

      if((hKpInstance==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// --------------------------------- tabai
#if KPSTEDI_MODE & GENERAL_MODE
      if(SUCCEEDED(retc))
      {
         KpstEdiDialogPtr->m_TabCtrl=CreateWindowEx(0, WC_TABCONTROL, "",
            WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, //  | TCS_BUTTONS,
            KPSTEDI_TAB_X, KPSTEDI_TAB_Y, KPSTEDI_TAB_DX, KPSTEDI_TAB_DY,
            hwndDlg, NULL, hKpInstance, NULL);
         if(KpstEdiDialogPtr->m_TabCtrl==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))retc = SetCtrlFont(KpstEdiDialogPtr->m_TabCtrl, KPW_CONTROL_STYLE_NORMAL);

      if(SUCCEEDED(retc))
      {
         tie.mask = TCIF_TEXT; // TCIF_IMAGE;
         tie.iImage = -1;
      }

      for(ii=0; (ii < KPSTEDI_TAB_NUM_OF_TABS) && SUCCEEDED(retc); ii++)
      {
         tie.pszText = (char *)(KpstedTabHeaders[ii]);
         if(TabCtrl_InsertItem(KpstEdiDialogPtr->m_TabCtrl, ii, &tie) == -1)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// ---------------------------- fiktyvus tabu langai
      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = hKpInstance;
         wcx.lpszClassName = "KpstediTabProductClass",
         wcx.lpfnWndProc   = (WNDPROC)KpstediTabProductProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

         if(!RegisterClassEx(&wcx))
         {
            long ll = GetLastError();
            if(ll != ERROR_CLASS_ALREADY_EXISTS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc))
      {
         KpstEdiDialogPtr->m_TabProduct=CreateWindowEx
         (
            0, // WS_EX_TRANSPARENT,                      // DWORD dwExStyle,      // extended window style
            "KpstediTabProductClass",
            "KpstediTabProduct",      // LPCTSTR lpWindowName, // pointer to window name
            WS_CHILD, // WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            KPSTEDI_TAB_WND_X,  // CW_USEDEFAULT, // int x,               // horizontal position of window
            KPSTEDI_TAB_WND_Y,  // CW_USEDEFAULT, // int y,               // vertical position of window
            KPSTEDI_TAB_WND_DX, // CW_USEDEFAULT, // int nWidth,          // window width
            KPSTEDI_TAB_WND_DY, // CW_USEDEFAULT, // int nHeight,         // window height
            hwndDlg, // KpstEdiDialogPtr->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
         if(KpstEdiDialogPtr->m_TabProduct==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = hKpInstance;
         wcx.lpszClassName = "KpstediTabStartClass",
         wcx.lpfnWndProc   = (WNDPROC)KpstediTabStartProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

         if(!RegisterClassEx(&wcx))
         {
            long ll = GetLastError();
            if(ll != ERROR_CLASS_ALREADY_EXISTS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc))
      {
         KpstEdiDialogPtr->m_TabStart=CreateWindowEx
         (
            0, // WS_EX_TRANSPARENT,                      // DWORD dwExStyle,      // extended window style
            "KpstediTabStartClass",
            "KpstediTabStart",      // LPCTSTR lpWindowName, // pointer to window name
            WS_CHILD, // WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            KPSTEDI_TAB_WND_X,  // CW_USEDEFAULT, // int x,               // horizontal position of window
            KPSTEDI_TAB_WND_Y,  // CW_USEDEFAULT, // int y,               // vertical position of window
            KPSTEDI_TAB_WND_DX, // CW_USEDEFAULT, // int nWidth,          // window width
            KPSTEDI_TAB_WND_DY, // CW_USEDEFAULT, // int nHeight,         // window height
            hwndDlg, // KpstEdiDialogPtr->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
         if(KpstEdiDialogPtr->m_TabStart==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = hKpInstance;
         wcx.lpszClassName = "KpstediTabBoundClass",
         wcx.lpfnWndProc   = (WNDPROC)KpstediTabBoundProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

         if(!RegisterClassEx(&wcx))
         {
            long ll = GetLastError();
            if(ll != ERROR_CLASS_ALREADY_EXISTS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc))
      {
         KpstEdiDialogPtr->m_TabBound=CreateWindowEx
         (
            0, // WS_EX_TRANSPARENT,                      // DWORD dwExStyle,      // extended window style
            "KpstediTabBoundClass",
            "KpstediTabBound",      // LPCTSTR lpWindowName, // pointer to window name
            WS_CHILD, // WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            KPSTEDI_TAB_WND_X,  // CW_USEDEFAULT, // int x,               // horizontal position of window
            KPSTEDI_TAB_WND_Y,  // CW_USEDEFAULT, // int y,               // vertical position of window
            KPSTEDI_TAB_WND_DX, // CW_USEDEFAULT, // int nWidth,          // window width
            KPSTEDI_TAB_WND_DY, // CW_USEDEFAULT, // int nHeight,         // window height
            hwndDlg, // KpstEdiDialogPtr->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
         if(KpstEdiDialogPtr->m_TabBound==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = hKpInstance;
         wcx.lpszClassName = "KpstediTabDataClass",
         wcx.lpfnWndProc   = (WNDPROC)KpstediTabDataProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

         if(!RegisterClassEx(&wcx))
         {
            long ll = GetLastError();
            if(ll != ERROR_CLASS_ALREADY_EXISTS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc))
      {
         KpstEdiDialogPtr->m_TabData=CreateWindowEx
         (
            0, // WS_EX_TRANSPARENT,                      // DWORD dwExStyle,      // extended window style
            "KpstediTabDataClass",
            "KpstediTabData",      // LPCTSTR lpWindowName, // pointer to window name
            WS_CHILD, // WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            KPSTEDI_TAB_WND_X,  // CW_USEDEFAULT, // int x,               // horizontal position of window
            KPSTEDI_TAB_WND_Y,  // CW_USEDEFAULT, // int y,               // vertical position of window
            KPSTEDI_TAB_WND_DX, // CW_USEDEFAULT, // int nWidth,          // window width
            KPSTEDI_TAB_WND_DY, // CW_USEDEFAULT, // int nHeight,         // window height
            hwndDlg, // KpstEdiDialogPtr->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
         if(KpstEdiDialogPtr->m_TabData==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc))
      {
         wcx.hInstance     = hKpInstance;
         wcx.lpszClassName = "KpstediTabUserClass",
         wcx.lpfnWndProc   = (WNDPROC)KpstediTabUserProc;
         wcx.style         = CS_DBLCLKS;
         wcx.cbSize        = sizeof(WNDCLASSEX);
         wcx.hIcon         = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hIconSm       = LoadIcon(hKpInstance, IDI_APPLICATION); // MAKEINTRESOURCE(IDI_APPLICATION));
         wcx.hCursor       = LoadCursor(0, IDC_ARROW);
         wcx.lpszMenuName  = 0;
         wcx.cbClsExtra    = 0;
         wcx.cbWndExtra    = 0;
         wcx.hbrBackground = CreateSolidBrush(GetSysColor(iaColorMap[KpShadowNorm])); // (HBRUSH)COLOR_BACKGROUND;

         if(!RegisterClassEx(&wcx))
         {
            long ll = GetLastError();
            if(ll != ERROR_CLASS_ALREADY_EXISTS)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, ll, False, __FILE__, __LINE__, 0L, NULL);
         }
      }

      if(SUCCEEDED(retc))
      {
         KpstEdiDialogPtr->m_TabUser=CreateWindowEx
         (
            0, // WS_EX_TRANSPARENT,                      // DWORD dwExStyle,      // extended window style
            "KpstediTabUserClass",
            "KpstediTabUser",      // LPCTSTR lpWindowName, // pointer to window name
            WS_CHILD, // WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME, // |WS_BORDER|WS_POPUP, // DWORD dwStyle,        // window style
            KPSTEDI_TAB_WND_X,  // CW_USEDEFAULT, // int x,               // horizontal position of window
            KPSTEDI_TAB_WND_Y,  // CW_USEDEFAULT, // int y,               // vertical position of window
            KPSTEDI_TAB_WND_DX, // CW_USEDEFAULT, // int nWidth,          // window width
            KPSTEDI_TAB_WND_DY, // CW_USEDEFAULT, // int nHeight,         // window height
            hwndDlg, // KpstEdiDialogPtr->m_hDialogWindow,  // HWND hWndParent,      // handle to parent or owner window
            NULL,          // HMENU hMenu,          // handle to menu, or child-window identifier
            hKpInstance,
            NULL           // LPVOID lpParam        // pointer to window-creation data
         );
         if(KpstEdiDialogPtr->m_TabUser==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_CurTab = KpstEdiDialogPtr->m_TabProduct;
      if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabProduct, SW_SHOW);
      if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabStart, SW_HIDE);
      if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabBound, SW_HIDE);
      if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabData, SW_HIDE);
      if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabUser, SW_HIDE);

#endif // #if KPSTEDI_MODE & GENERAL_MODE


// --------------------------------- siaip laukai

#if KPSTEDI_MODE & GENERAL_MODE
#define KPSTED_PARENT_PRODUCT KpstEdiDialogPtr->m_TabProduct
#define KPSTED_PARENT_START KpstEdiDialogPtr->m_TabStart
#define KPSTED_PARENT_BOUND KpstEdiDialogPtr->m_TabBound
#define KPSTED_PARENT_DATA KpstEdiDialogPtr->m_TabData
#define KPSTED_PARENT_USER KpstEdiDialogPtr->m_TabUser
#else
#define KPSTED_PARENT_PRODUCT hwndDlg
#define KPSTED_PARENT_START hwndDlg
#define KPSTED_PARENT_BOUND hwndDlg
#define KPSTED_PARENT_DATA hwndDlg
#define KPSTED_PARENT_USER hwndDlg
#endif

#if KPSTEDI_MODE & STARTER_MODE
      if(SUCCEEDED(retc)) retc=KpCreateIcon(hKpInstance, hwndDlg, NULL, LoadIcon(NULL /* hKpInstance */, IDI_ERROR), KPSTEDI_ICON_X, KPSTEDI_ICON_Y, KPSTEDI_ICON_WDT, KPSTEDI_ICON_WDT, 0);
#else
      if(SUCCEEDED(retc)) retc=KpCreateIcon(hKpInstance, hwndDlg, NULL, KP_IDI_SETUP_ICON, KPSTEDI_ICON_X, KPSTEDI_ICON_Y, KPSTEDI_ICON_WDT, KPSTEDI_ICON_WDT, 0);
#endif

#if (KPSTEDI_MODE & STARTER_MODE) == 0
// #if (KPSTEDI_MODE & USER_MODE) == 0
      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, KPSTEDI_TITLE, KPSTEDI_HEAD_X, KPSTEDI_HEAD_Y, 1, KPW_CONTROL_STYLE_HEADING_3, 0, 0, NULL);
// #endif
#endif

#if KPSTEDI_MODE & STARTER_MODE
      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, &(KpstEdiDialogPtr->m_ExplPrompt1), KpstEdiDialogPtr->m_lpszErrTxt, KPSTEDI_EXPL_X, KPSTEDI_EXPL_1_Y, KPSTEDI_EXPL_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, KPSTEDI_REZ_NOT_CLOSE_1, KPSTEDI_EXPL_X, KPSTEDI_EXPL_2_Y, KPSTEDI_EXPL_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, hwndDlg, NULL, KPSTEDI_REZ_NOT_CLOSE_2, KPSTEDI_EXPL_X, KPSTEDI_EXPL_3_Y, KPSTEDI_EXPL_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#endif

#if KPSTEDI_MODE & GENERAL_MODE

// ---------------------------------
// m_TabProduct vaikai

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_PROD_PROMPT, KPSTEDI_PROD_PROMPT_X, KPSTEDI_PROD_CTRL_Y, KPSTEDI_PROD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_PRODUCT, &(KpstEdiDialogPtr->m_ProdName), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PROD_NUM_CHARS), KPSTEDI_PROD_EDIT_X, KPSTEDI_PROD_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PROD_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ProdName==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_ProdName, WM_SETTEXT, 0, (LPARAM)prod_name);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_PUBL_PROMPT, KPSTEDI_PUBL_PROMPT_X, KPSTEDI_PUBL_CTRL_Y, KPSTEDI_PUBL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_PRODUCT, &(KpstEdiDialogPtr->m_Publisher), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PUBL_NUM_CHARS), KPSTEDI_PUBL_EDIT_X, KPSTEDI_PUBL_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PUBL_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_Publisher==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_Publisher, WM_SETTEXT, 0, (LPARAM)publisher);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_PRODVER_PROMPT, KPSTEDI_PRODVER_PROMPT_X, KPSTEDI_PRODVER_CTRL_Y, KPSTEDI_PRODVER_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_PRODUCT, &(KpstEdiDialogPtr->m_ProdVer), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PRODVER_NUM_CHARS), KPSTEDI_PRODVER_EDIT_X, KPSTEDI_PRODVER_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PRODVER_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ProdVer==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%05d", prod_ver);
         SendMessage(KpstEdiDialogPtr->m_ProdVer, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_UPDNUM_PROMPT, KPSTEDI_UPDNUM_PROMPT_X, KPSTEDI_UPDNUM_CTRL_Y, KPSTEDI_UPDNUM_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, KPSTED_PARENT_PRODUCT, &(KpstEdiDialogPtr->m_UpdNum), str_buf + (KPSTEDI_EDIT_MAX_CONTROL_CHARS - KPSTEDI_UPDNUM_NUM_CHARS), KPSTEDI_UPDNUM_EDIT_X, KPSTEDI_UPDNUM_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_UPDNUM_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_UpdNum == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", upd_num);
         SendMessage(KpstEdiDialogPtr->m_UpdNum, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_VOL_PROMPT, KPSTEDI_VOL_PROMPT_X, KPSTEDI_VOL_PROMPT_Y, KPSTEDI_VOL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_VOL_PROMPT1, KPSTEDI_VOL_PROMPT_X, KPSTEDI_VOL_PROMPT1_Y, KPSTEDI_VOL_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_VOL_PROMPT2, KPSTEDI_VOL_PROMPT_X, KPSTEDI_VOL_PROMPT2_Y, KPSTEDI_VOL_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_VOL_PROMPT3, KPSTEDI_VOL_PROMPT_X, KPSTEDI_VOL_PROMPT3_Y, KPSTEDI_VOL_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_VOL_PROMPT4, KPSTEDI_VOL_PROMPT_X, KPSTEDI_VOL_PROMPT4_Y, KPSTEDI_VOL_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_VOL_PROMPT5, KPSTEDI_VOL_PROMPT_X, KPSTEDI_VOL_PROMPT5_Y, KPSTEDI_VOL_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_PRODUCT, &(KpstEdiDialogPtr->m_VolEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_VOL_NUM_CHARS), KPSTEDI_VOL_EDIT_X, KPSTEDI_VOL_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_VOL_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_VolEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_VolEdit, WM_SETTEXT, 0, (LPARAM)vol_name);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, KPSTED_PARENT_PRODUCT, NULL, KPSTEDI_WNDNAME_PROMPT, KPSTEDI_WNDNAME_PROMPT_X, KPSTEDI_WNDNAME_CTRL_Y, KPSTEDI_WNDNAME_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateEdit(hKpInstance, KPSTED_PARENT_PRODUCT, &(KpstEdiDialogPtr->m_WndName), str_buf + (KPSTEDI_EDIT_MAX_CONTROL_CHARS - KPSTEDI_WNDNAME_NUM_CHARS), KPSTEDI_WNDNAME_EDIT_X, KPSTEDI_WNDNAME_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_WNDNAME_EDIT_NUMLINES);
      KP_ASSERT(KpstEdiDialogPtr->m_WndName != NULL, KP_E_SYSTEM_ERROR, null, True);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_WndName, WM_SETTEXT, 0, (LPARAM)wnd_name);

#endif // #if KPSTEDI_MODE & GENERAL_MODE


// ---------------------------
// m_TabStart vaikai

#if KPSTEDI_MODE & GENERAL_MODE

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT, KPSTEDI_CMD_STR_PROMPT_X, KPSTEDI_CMD_STR_PROMPT_Y, KPSTEDI_CMD_STR_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_CmdStrEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_CMD_STR_EDIT_NUM_CHARS), KPSTEDI_CMD_STR_EDIT_X, KPSTEDI_CMD_STR_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_CMD_STR_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CmdStrEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CmdStrEdit, WM_SETTEXT, 0, (LPARAM)cmd_str);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_ATTOFF_PROMPT, KPSTEDI_ATTOFF_PROMPT_X, KPSTEDI_ATTOFF_PROMPT_Y, KPSTEDI_ATTOFF_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_AttOff), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_ATTOFF_NUM_CHARS), KPSTEDI_ATTOFF_EDIT_X, KPSTEDI_ATTOFF_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_ATTOFF_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_AttOff==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%ld", att_offset);
         SendMessage(KpstEdiDialogPtr->m_AttOff, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_ATTEXT_PROMPT, KPSTEDI_ATTEXT_PROMPT_X, KPSTEDI_ATTEXT_CTRL_Y, KPSTEDI_ATTEXT_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_AttExt), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_ATTEXT_NUM_CHARS), KPSTEDI_ATTEXT_EDIT_X, KPSTEDI_ATTEXT_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_ATTEXT_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_AttExt==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_AttExt, WM_SETTEXT, 0, (LPARAM)att_ext);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_PROL_PROMPT, KPSTEDI_PROL_PROMPT_X, KPSTEDI_PROL_CTRL_Y, KPSTEDI_PROL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_ProlEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PROL_NUM_CHARS), KPSTEDI_PROL_EDIT_X, KPSTEDI_PROL_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PROL_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ProlEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_ProlEdit, WM_SETTEXT, 0, (LPARAM)prol_fname);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_PROL_TIME_PROMPT, KPSTEDI_PROL_TIME_PROMPT_X, KPSTEDI_PROL_TIME_CTRL_Y, KPSTEDI_PROL_TIME_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_SEC_PROMPT, KPSTEDI_PROL_SEC_PROMPT_X, KPSTEDI_PROL_TIME_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_ProlTimeEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PROL_TIME_NUM_CHARS), KPSTEDI_PROL_TIME_EDIT_X, KPSTEDI_PROL_TIME_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PROL_TIME_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ProlTimeEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", prol_show_time);
         SendMessage(KpstEdiDialogPtr->m_ProlTimeEdit, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_BMP_PROMPT, KPSTEDI_BMP_PROMPT_X, KPSTEDI_BMP_CTRL_Y, KPSTEDI_BMP_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_BmpEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_BMP_NUM_CHARS), KPSTEDI_BMP_EDIT_X, KPSTEDI_BMP_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_BMP_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_BmpEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_BmpEdit, WM_SETTEXT, 0, (LPARAM)bmp_fname);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_BMP_SIZ_PROMPT, KPSTEDI_BMP_SIZ_PROMPT_X, KPSTEDI_BMP_SIZ_CTRL_Y, KPSTEDI_BMP_SIZ_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_TIMES_PROMPT, KPSTEDI_BMP_X_PROMPT_X, KPSTEDI_BMP_SIZ_CTRL_Y, KPSTEDI_BMP_X_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_BMP_PIX_PROMPT, KPSTEDI_BMP_PIX_PROMPT_X, KPSTEDI_BMP_SIZ_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_BmpDxEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_BMP_SIZ_NUM_CHARS), KPSTEDI_BMP_DX_EDIT_X, KPSTEDI_BMP_SIZ_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_BMP_SIZ_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_BmpDxEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", bmp_wdt);
         SendMessage(KpstEdiDialogPtr->m_BmpDxEdit, WM_SETTEXT, 0, (LPARAM)num_buf);
      }
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_BmpDyEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_BMP_SIZ_NUM_CHARS), KPSTEDI_BMP_DY_EDIT_X, KPSTEDI_BMP_SIZ_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_BMP_SIZ_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_BmpDyEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", bmp_hgt);
         SendMessage(KpstEdiDialogPtr->m_BmpDyEdit, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_MUTE_PROMPT, KPSTEDI_MUTE_PROMPT_X, KPSTEDI_MUTE_CTRL_Y, KPSTEDI_MUTE_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_MuteBox), KPSTEDI_MUTE_BOX_X, KPSTEDI_MUTE_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_MuteBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_MuteBox, BM_SETCHECK, (WPARAM)(muted?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_EPIL_PROMPT, KPSTEDI_EPIL_PROMPT_X, KPSTEDI_EPIL_CTRL_Y, KPSTEDI_EPIL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_EpilEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_EPIL_NUM_CHARS), KPSTEDI_EPIL_EDIT_X, KPSTEDI_EPIL_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_EPIL_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_EpilEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_EpilEdit, WM_SETTEXT, 0, (LPARAM)epil_fname);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_EPIL_TIME_PROMPT, KPSTEDI_EPIL_TIME_PROMPT_X, KPSTEDI_EPIL_TIME_CTRL_Y, KPSTEDI_EPIL_TIME_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_SEC_PROMPT, KPSTEDI_EPIL_SEC_PROMPT_X, KPSTEDI_EPIL_TIME_CTRL_Y, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_EpilTimeEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_EPIL_TIME_NUM_CHARS), KPSTEDI_EPIL_TIME_EDIT_X, KPSTEDI_EPIL_TIME_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_EPIL_TIME_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_EpilTimeEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", epil_sh_time);
         SendMessage(KpstEdiDialogPtr->m_EpilTimeEdit, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_ONTOP_PROMPT, KPSTEDI_ONTOP_PROMPT_X, KPSTEDI_ONTOP_CTRL_Y, KPSTEDI_ONTOP_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_OnTopBox), KPSTEDI_ONTOP_BOX_X, KPSTEDI_ONTOP_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_OnTopBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_OnTopBox, BM_SETCHECK, (WPARAM)(on_top?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_FULLSCR_PROMPT, KPSTEDI_FULLSCR_PROMPT_X, KPSTEDI_FULLSCR_CTRL_Y, KPSTEDI_FULLSCR_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_FullScrBox), KPSTEDI_FULLSCR_BOX_X, KPSTEDI_FULLSCR_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_FullScrBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_FullScrBox, BM_SETCHECK, (WPARAM)(full_scr?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CLRCLIPBRD_PROMPT, KPSTEDI_CLRCLIPBRD_PROMPT_X, KPSTEDI_CLRCLIPBRD_CTRL_Y, KPSTEDI_CLRCLIPBRD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_ClearClipBrdBox), KPSTEDI_CLRCLIPBRD_BOX_X, KPSTEDI_CLRCLIPBRD_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ClearClipBrdBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_ClearClipBrdBox, BM_SETCHECK, (WPARAM)(clr_clipbrd?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_SUBST_PROMPT, KPSTEDI_SUBST_PROMPT_X, KPSTEDI_SUBST_CTRL_Y, KPSTEDI_SUBST_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_SubstBox), KPSTEDI_SUBST_BOX_X, KPSTEDI_SUBST_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_SubstBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_SubstBox, BM_SETCHECK, (WPARAM)(subst?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_EBOARD_PROMPT, KPSTEDI_EBOARD_PROMPT_X, KPSTEDI_EBOARD_CTRL_Y, KPSTEDI_EBOARD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_EboardBox), KPSTEDI_EBOARD_BOX_X, KPSTEDI_EBOARD_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_EboardBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_EboardBox, BM_SETCHECK, (WPARAM)(eboard?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_SHIE_PROMPT, KPSTEDI_SHIE_PROMPT_X, KPSTEDI_SHIE_CTRL_Y, KPSTEDI_SHIE_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_ShIEBox), KPSTEDI_SHIE_BOX_X, KPSTEDI_SHIE_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ShIEBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_ShIEBox, BM_SETCHECK, (WPARAM)(sh_ie?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_HBMARKS_PROMPT, KPSTEDI_HBMARKS_PROMPT_X, KPSTEDI_HBMARKS_CTRL_Y, KPSTEDI_HBMARKS_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_HideBkmrksBox), KPSTEDI_HBMARKS_BOX_X, KPSTEDI_HBMARKS_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_HideBkmrksBox == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_HideBkmrksBox, BM_SETCHECK, (WPARAM)(hide_bkmrks?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_SNDMUT_PROMPT, KPSTEDI_SNDMUT_PROMPT_X, KPSTEDI_SNDMUT_CTRL_Y, KPSTEDI_SNDMUT_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_SoundMutedBox), KPSTEDI_SNDMUT_BOX_X, KPSTEDI_SNDMUT_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_SoundMutedBox == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_SoundMutedBox, BM_SETCHECK, (WPARAM)(sound_muted?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_FINDBUT_PROMPT, KPSTEDI_FINDBUT_PROMPT_X, KPSTEDI_FINDBUT_CTRL_Y, KPSTEDI_FINDBUT_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_FindButBox), KPSTEDI_FINDBUT_BOX_X, KPSTEDI_FINDBUT_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_FindButBox == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_FindButBox, BM_SETCHECK, (WPARAM)(find_but?BST_CHECKED:BST_UNCHECKED), 0);
#endif // #if KPSTEDI_MODE & GENERAL_MODE

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
      if(SUCCEEDED(retc)) retc = KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_TESTUPD_PROMPT, KPSTEDI_TESTUPD_PROMPT_X, KPSTEDI_TESTUPD_CTRL_Y, KPSTEDI_TESTUPD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc = KpCreateCheckBox(hKpInstance, KPSTED_PARENT_START, &(KpstEdiDialogPtr->m_TestUpdatesBox), KPSTEDI_TESTUPD_BOX_X, KPSTEDI_TESTUPD_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_TestUpdatesBox == NULL)
         retc = KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_TestUpdatesBox, BM_SETCHECK, (WPARAM)(test_upd?BST_CHECKED:BST_UNCHECKED), 0);
#endif // #  if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)

#if KPSTEDI_MODE & GENERAL_MODE
//    if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_ATTOFF_PROMPT1, KPSTEDI_ATTOFF_PROMPT_X, KPSTEDI_ATTOFF_PROMPT1_Y, KPSTEDI_ATTOFF_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
//    if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_ATTOFF_PROMPT2, KPSTEDI_ATTOFF_PROMPT_X, KPSTEDI_ATTOFF_PROMPT2_Y, KPSTEDI_ATTOFF_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT1, KPSTEDI_CMD_STR_PROMPT_X, KPSTEDI_CMD_STR_PROMPT1_Y, KPSTEDI_CMD_STR_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT2, KPSTEDI_CMD_STR_PROMPT_X /* KPSTEDI_ATTOFF_PROMPT_X */, KPSTEDI_CMD_STR_PROMPT2_Y /* KPSTEDI_ATTOFF_PROMPT1_Y */, KPSTEDI_CMD_STR_PROMPT1_DX /* KPSTEDI_ATTOFF_PROMPT1_DX */, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT3, KPSTEDI_CMD_STR_PROMPT_X /* KPSTEDI_ATTOFF_PROMPT_X */, KPSTEDI_CMD_STR_PROMPT3_Y /* KPSTEDI_ATTOFF_PROMPT2_Y */, KPSTEDI_CMD_STR_PROMPT1_DX /* KPSTEDI_ATTOFF_PROMPT1_DX */, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT4, KPSTEDI_CMD_STR_PROMPT_X, KPSTEDI_CMD_STR_PROMPT4_Y, KPSTEDI_CMD_STR_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT5, KPSTEDI_CMD_STR_PROMPT_X, KPSTEDI_CMD_STR_PROMPT5_Y, KPSTEDI_CMD_STR_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_START, NULL, KPSTEDI_CMD_STR_PROMPT6, KPSTEDI_CMD_STR_PROMPT_X, KPSTEDI_CMD_STR_PROMPT6_Y, KPSTEDI_CMD_STR_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#endif // #if KPSTEDI_MODE & GENERAL_MODE


// ------------------------
// m_TabBound vaikai

#if KPSTEDI_MODE & GENERAL_MODE

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_BOUND_PROMPT, KPSTEDI_BOUND_PROMPT_X, KPSTEDI_BOUND_PROMPT_Y, KPSTEDI_BOUND_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_BOUND_PROMPT1, KPSTEDI_BOUND_PROMPT_X, KPSTEDI_BOUND_PROMPT_Y1, KPSTEDI_BOUND_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_BoundBox), KPSTEDI_BOUND_BOX_X, KPSTEDI_BOUND_CTRL_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_BoundBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_BoundBox, BM_SETCHECK, (WPARAM)(bound?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT, KPSTEDI_CITYP_PROMPT_X, KPSTEDI_CITYP_CTRL_Y, KPSTEDI_CITYP_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT_B, KPSTEDI_CITYP_PROMPT1_X, KPSTEDI_CITYP_BOX_B_Y, KPSTEDI_CITYP_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiTypBBox), KPSTEDI_CITYP_BOX1_X, KPSTEDI_CITYP_BOX_B_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiTypBBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiTypBBox, BM_SETCHECK, (WPARAM)((cid_typ&KPST_COMPID_BIOS_DATE)?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT_P, KPSTEDI_CITYP_PROMPT1_X, KPSTEDI_CITYP_BOX_P_Y, KPSTEDI_CITYP_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiTypPBox), KPSTEDI_CITYP_BOX1_X, KPSTEDI_CITYP_BOX_P_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiTypPBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiTypPBox, BM_SETCHECK, (WPARAM)((cid_typ&KPST_COMPID_PROC_ID)?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT_N, KPSTEDI_CITYP_PROMPT1_X, KPSTEDI_CITYP_BOX_N_Y, KPSTEDI_CITYP_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiTypNBox), KPSTEDI_CITYP_BOX1_X, KPSTEDI_CITYP_BOX_N_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiTypNBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiTypNBox, BM_SETCHECK, (WPARAM)((cid_typ&KPST_COMPID_PROC_NAME)?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT_D, KPSTEDI_CITYP_PROMPT2_X, KPSTEDI_CITYP_BOX_D_Y, KPSTEDI_CITYP_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiTypDBox), KPSTEDI_CITYP_BOX2_X, KPSTEDI_CITYP_BOX_D_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiTypDBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiTypDBox, BM_SETCHECK, (WPARAM)((cid_typ&KPST_COMPID_DISK_ID)?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT_M, KPSTEDI_CITYP_PROMPT2_X, KPSTEDI_CITYP_BOX_M_Y, KPSTEDI_CITYP_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiTypMBox), KPSTEDI_CITYP_BOX2_X, KPSTEDI_CITYP_BOX_M_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiTypMBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiTypMBox, BM_SETCHECK, (WPARAM)((cid_typ&KPST_COMPID_MAC)?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CITYP_PROMPT_V, KPSTEDI_CITYP_PROMPT2_X, KPSTEDI_CITYP_BOX_V_Y, KPSTEDI_CITYP_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiTypVBox), KPSTEDI_CITYP_BOX2_X, KPSTEDI_CITYP_BOX_V_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiTypVBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiTypVBox, BM_SETCHECK, (WPARAM)((cid_typ&KPST_COMPID_BOLT)?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CIDIR_PROMPT, KPSTEDI_CIDIR_PROMPT_X, KPSTEDI_CIDIR_PROMPT_Y, KPSTEDI_CIDIR_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CIDIR_PROMPT1, KPSTEDI_CIDIR_PROMPT1_X, KPSTEDI_CIDIR_PROMPT_Y, KPSTEDI_CIDIR_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CIDIR_PROMPT2, KPSTEDI_CIDIR_PROMPT1_X, KPSTEDI_CIDIR_PROMPT1_Y, KPSTEDI_CIDIR_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
//    if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiDirBox), KPSTEDI_CIDIR_BOX_X, KPSTEDI_CIDIR_CTRL_Y, 0, 0);
      if(SUCCEEDED(retc)) retc=KpCreateRadioBut(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiDirBox), KPSTEDI_CIDIR_BOX_X, KPSTEDI_CIDIR_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CiDirBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiDirBox, BM_SETCHECK, (WPARAM)(cid_dir?BST_CHECKED:BST_UNCHECKED), 0);
      if(SUCCEEDED(retc)) retc=KpCreateRadioBut(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_CiFileBox), KPSTEDI_CIDIR_BOX_X, KPSTEDI_CIDIR_BOX1_Y, 0, 0);
      if(((KpstEdiDialogPtr->m_CiFileBox)==NULL) && SUCCEEDED(retc))
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CiFileBox, BM_SETCHECK, (WPARAM)(cid_dir?BST_UNCHECKED:BST_CHECKED), 0);

#endif // #if KPSTEDI_MODE & GENERAL_MODE

// {
// unsigned char str_buf[100];
// sprintf((char *)str_buf, "%d", num_of_lics);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
// }

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
#  if (KPSTEDI_MODE & STARTER_MODE) == 0
      if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_RegURL = NULL;
      if(SUCCEEDED(retc))
//#   if (KPSTEDI_MODE & (USER_MODE | STARTER_MODE)) == USER_MODE
#     if KPSTEDI_MODE & USER_MODE
         if(num_of_lics) // kai num_of_lics>0 ar -1, paèiam serveriui nereikia
#     endif
         if(theKpStAppPtr->m_iKpStMode==KpStEditMode)
      {
         if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_REGURL_PROMPT, KPSTEDI_REGURL_PROMPT_X, KPSTEDI_REGURL_PROMPT_Y
#     if KPSTEDI_MODE & USER_MODE
                  - ((rez_fname[0])?0:KPSTEDI_CTRL_HGT)
#     endif
                  , KPSTEDI_REGURL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#     if KPSTEDI_MODE & GENERAL_MODE
         if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_REGURL_PROMPT1, KPSTEDI_REGURL_PROMPT_X, KPSTEDI_REGURL_PROMPT1_Y, KPSTEDI_REGURL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#     endif
         if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_RegURL), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_REGURL_NUM_CHARS),
            KPSTEDI_REGURL_EDIT_X, KPSTEDI_REGURL_CTRL_Y
#     if KPSTEDI_MODE & USER_MODE
               - ((rez_fname[0])?0:KPSTEDI_CTRL_HGT)
#     endif
               , KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_REGURL_EDIT_NUMLINES);
         if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_RegURL==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            SendMessage(KpstEdiDialogPtr->m_RegURL, WM_SETTEXT, 0, (LPARAM)reg_url);
      }
#  endif // #if (KPSTEDI_MODE & STARTER_MODE) == 0
#endif // #if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)

#if KPSTEDI_MODE & GENERAL_MODE

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_LICNUM_PROMPT, KPSTEDI_LICNUM_PROMPT_X, KPSTEDI_LICNUM_CTRL_Y, KPSTEDI_LICNUM_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_NumOfLics), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_LICNUM_NUM_CHARS), KPSTEDI_LICNUM_EDIT_X, KPSTEDI_LICNUM_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_LICNUM_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_NumOfLics==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", num_of_lics);
         SendMessage(KpstEdiDialogPtr->m_NumOfLics, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_BOUND_FL_PROMPT, KPSTEDI_BOUND_FL_PROMPT_X, KPSTEDI_BOUND_FL_CTRL_Y, KPSTEDI_BOUND_FL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_BoundFlashBox), KPSTEDI_BOUND_FL_BOX_X, KPSTEDI_BOUND_FL_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_BoundFlashBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_BoundFlashBox, BM_SETCHECK, (WPARAM)(bound_flash?BST_CHECKED:BST_UNCHECKED), 0);
         
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_LIC_FL_PROMPT, KPSTEDI_LIC_FL_PROMPT_X, KPSTEDI_LIC_FL_CTRL_Y, KPSTEDI_LIC_FL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_LicFlashBox), KPSTEDI_LIC_FL_BOX_X, KPSTEDI_LIC_FL_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_LicFlashBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_LicFlashBox, BM_SETCHECK, (WPARAM)(lic_flash?BST_CHECKED:BST_UNCHECKED), 0);

#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
      if(SUCCEEDED(retc))
      {
#  if KPSTEDI_MODE & BOUND_MODE
         if(bound_flash || lic_flash)
#  endif
         {
            if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_FLASH_ID_PROMPT, KPSTEDI_FLASH_ID_PROMPT_X, KPSTEDI_FLASH_ID_CTRL_Y, KPSTEDI_FLASH_ID_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
            if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_FlashId), (const unsigned char *)"" /* str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_FLASH_ID_NUM_CHARS) */, KPSTEDI_FLASH_ID_EDIT_DX, KPSTEDI_FLASH_ID_EDIT_X, KPSTEDI_FLASH_ID_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_FLASH_ID_EDIT_NUMLINES);
            if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_FlashId==NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
            if(SUCCEEDED(retc))
            {
               sprintf((char *)num_buf, "%08lx", flash_id);
               SendMessage(KpstEdiDialogPtr->m_FlashId, WM_SETTEXT, 0, (LPARAM)num_buf);
            }
         }
#  if KPSTEDI_MODE & BOUND_MODE
         else
#  endif
         {
            if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_LIC_ID_PROMPT, KPSTEDI_LIC_ID_PROMPT_X, KPSTEDI_LIC_ID_PROMPT_Y, KPSTEDI_LIC_ID_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#  if KPSTEDI_MODE & GENERAL_MODE
            if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_LIC_ID_PROMPT1, KPSTEDI_LIC_ID_PROMPT_X, KPSTEDI_LIC_ID_PROMPT1_Y, KPSTEDI_LIC_ID_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#  endif
            if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_IniLicID), (const unsigned char *)"", KPSTEDI_LIC_ID_EDIT_DX, KPSTEDI_LIC_ID_EDIT_X, KPSTEDI_LIC_ID_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_LIC_ID_EDIT_NUMLINES);
            if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_IniLicID == NULL)
               retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

// char out_buf[100];
// sprintf(out_buf, "%d", lic_id);
// KpMsgOut(out_buf, IDI_ASTERISK, KP_MB_TESTI);

            if((lic_id != KpstRand(0)) && SUCCEEDED(retc))
            {
//             if(SUCCEEDED(retc)) *theKpStAppPtr->m_iLicID = lic_id;
               if(SUCCEEDED(retc))
               {
                  retc = EmuTv.SetHp11Variable(lic_id, KP11_LICID);
                  if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
               }

               if(SUCCEEDED(retc))
               {
                  retc = theKpStAppPtr->CalcLicCode();
                  if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
               }
               lic_buf[0] = Nul;
               if(SUCCEEDED(retc))
               {
                  retc = theKpStAppPtr->FormatLicCodeFull(lic_buf);
                  if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc)) SendMessage(KpstEdiDialogPtr->m_IniLicID, WM_SETTEXT, 0, (LPARAM)lic_buf);

            } // if((lic_id != KpstRand(0)) && SUCCEEDED(retc))

         } // if(bound_flash)

      } // if(SUCCEEDED(retc))

#endif // #if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)

#if KPSTEDI_MODE & GENERAL_MODE

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_PWD_WND_PROMPT, KPSTEDI_PWD_WND_PROMPT_X, KPSTEDI_PWD_WND_PROMPT_Y, KPSTEDI_PWD_WND_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_PWD_WND_PROMPT1, KPSTEDI_PWD_WND_PROMPT_X, KPSTEDI_PWD_WND_PROMPT1_Y, KPSTEDI_PWD_WND_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_PwdWndEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PWD_WND_NUM_CHARS), KPSTEDI_PWD_WND_EDIT_X, KPSTEDI_PWD_WND_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PWD_WND_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_PwdWndEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_PwdWndEdit, WM_SETTEXT, 0, (LPARAM)pwd_win_name);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_PWD_PROMPT, KPSTEDI_PWD_PROMPT_X, KPSTEDI_PWD_CTRL_Y, KPSTEDI_PWD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_PwdEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PWD_NUM_CHARS), KPSTEDI_PWD_EDIT_X, KPSTEDI_PWD_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PWD_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_PwdEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_PwdEdit, WM_SETTEXT, 0, (LPARAM)pwd_buf);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_OLD_PWD_PROMPT, KPSTEDI_OLD_PWD_PROMPT_X, KPSTEDI_OLD_PWD_CTRL_Y, KPSTEDI_OLD_PWD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_OldPwdEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_OLD_PWD_NUM_CHARS), KPSTEDI_OLD_PWD_EDIT_X, KPSTEDI_OLD_PWD_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_OLD_PWD_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_OldPwdEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_OldPwdEdit, WM_SETTEXT, 0, (LPARAM)old_pwd_buf);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_PWD_EDIT_PROMPT, KPSTEDI_PWD_EDIT_PROMPT_X, KPSTEDI_PWD_EDIT_CTRL_Y, KPSTEDI_PWD_EDIT_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_PwdEditEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PWD_CTRL_NUM_CHARS), KPSTEDI_PWD_EDIT_EDIT_X, KPSTEDI_PWD_EDIT_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PWD_EDIT_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_PwdEditEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", pwd_ed_ctrl);
         SendMessage(KpstEdiDialogPtr->m_PwdEditEdit, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_PWD_BUT_PROMPT, KPSTEDI_PWD_BUT_PROMPT_X, KPSTEDI_PWD_BUT_CTRL_Y, KPSTEDI_PWD_BUT_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_PwdButEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_PWD_CTRL_NUM_CHARS), KPSTEDI_PWD_BUT_EDIT_X, KPSTEDI_PWD_BUT_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_PWD_BUT_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_PwdButEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", pwd_ok_but);
         SendMessage(KpstEdiDialogPtr->m_PwdButEdit, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_BOUND, NULL, KPSTEDI_CHCD_PROMPT, KPSTEDI_CHCD_PROMPT_X, KPSTEDI_CHCD_CTRL_Y, KPSTEDI_CHCD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_BOUND, &(KpstEdiDialogPtr->m_ChCDBox), KPSTEDI_CHCD_BOX_X, KPSTEDI_CHCD_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ChCDBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_ChCDBox, BM_SETCHECK, (WPARAM)(ch_cd?BST_CHECKED:BST_UNCHECKED), 0);

#endif // #if KPSTEDI_MODE & GENERAL_MODE


// ------------------------------
// m_TabData vaikai

#if KPSTEDI_MODE & GENERAL_MODE
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_INI_PROMPT, KPSTEDI_INI_PROMPT_X, KPSTEDI_INI_PROMPT_Y, KPSTEDI_INI_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL); // rinkmena
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_PresEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_INI_NUM_CHARS), KPSTEDI_INI_EDIT_X, KPSTEDI_INI_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_INI_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_PresEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_PresEdit, WM_SETTEXT, 0, (LPARAM)pres_fname);
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_INI_PROMPT1, KPSTEDI_INI_PROMPT_X, KPSTEDI_INI_PROMPT1_Y, KPSTEDI_INI_PROMPT1_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  if (KPSTEDI_MODE & (USER_MODE | STARTER_MODE)) == USER_MODE
      if(
#     ifdef NO_DIRECT_REZ_FILE
         (num_of_lics == 0) &&
#     endif
         (rez_fname[0])
        )
#  endif
      {
         if(SUCCEEDED(retc)) /* retc= */ KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_REZ_PROMPT, KPSTEDI_REZ_PROMPT_X, KPSTEDI_REZ_CTRL_Y, KPSTEDI_REZ_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL); // rinkmena
         if(SUCCEEDED(retc)) /* retc= */ KpCreateEdit(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_RezEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_REZ_NUM_CHARS), KPSTEDI_REZ_EDIT_X, KPSTEDI_REZ_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_REZ_EDIT_NUMLINES);
         if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_RezEdit==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            SendMessage(KpstEdiDialogPtr->m_RezEdit, WM_SETTEXT, 0, (LPARAM)rez_fname);
         if(SUCCEEDED(retc)) /* retc= */ KpCreateButton(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_RezButton), KP_ID_OPEN, KP_IDI_OPEN_ICON, KPSTEDI_REZ_BUT_X, KPSTEDI_REZ_CTRL_Y, KPW_BUTTON_HGT, KPW_BUTTON_HGT, 0, 0);
         if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_RezButton==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);
      }
#endif // #if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)

#if KPSTEDI_MODE & GENERAL_MODE

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_REZ_VAR_PROMPT, KPSTEDI_REZ_VAR_PROMPT_X, KPSTEDI_REZ_VAR_CTRL_Y, KPSTEDI_REZ_VAR_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_RezVarEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_REZ_VAR_NUM_CHARS), KPSTEDI_REZ_VAR_EDIT_X, KPSTEDI_REZ_VAR_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_REZ_VAR_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_RezVarEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_RezVarEdit, WM_SETTEXT, 0, (LPARAM)rez_var);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_SHUFF_PROMPT, KPSTEDI_SHUFF_PROMPT_X, KPSTEDI_SHUFF_CTRL_Y, KPSTEDI_SHUFF_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_ShuffCnt), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_SHUFF_NUM_CHARS), KPSTEDI_SHUFF_EDIT_X, KPSTEDI_SHUFF_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_SHUFF_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_ShuffCnt==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
      {
         sprintf((char *)num_buf, "%d", shuff_cnt);
         SendMessage(KpstEdiDialogPtr->m_ShuffCnt, WM_SETTEXT, 0, (LPARAM)num_buf);
      }

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_CUMUL_PROMPT, KPSTEDI_CUMUL_PROMPT_X, KPSTEDI_CUMUL_CTRL_Y, KPSTEDI_CUMUL_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateCheckBox(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_CumulBox), KPSTEDI_CUMUL_BOX_X, KPSTEDI_CUMUL_BOX_Y, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CumulBox==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_CumulBox, BM_SETCHECK, (WPARAM)(kumul?BST_CHECKED:BST_UNCHECKED), 0);

      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_DATA, NULL, KPSTEDI_TESTC_PROMPT, KPSTEDI_TESTC_PROMPT_X, KPSTEDI_TESTC_CTRL_Y, KPSTEDI_TESTC_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_DATA, &(KpstEdiDialogPtr->m_TestCid), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_TESTC_NUM_CHARS), KPSTEDI_TESTC_EDIT_X, KPSTEDI_TESTC_CTRL_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_TESTC_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_TestCid==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_TestCid, WM_SETTEXT, 0, (LPARAM)test_cid);

#endif

// ------------------------------
// m_TabUser vaikai

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_USER, NULL, KPSTEDI_USER_DATA_PROMPT, KPSTEDI_USER_DATA_PROMPT_X, KPSTEDI_USER_DATA_PROMPT_Y, KPSTEDI_USER_DATA_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_USER, &(KpstEdiDialogPtr->m_UserDataEdit), str_buf+(KPSTEDI_EDIT_MAX_CONTROL_CHARS-KPSTEDI_USER_DATA_NUM_CHARS), KPSTEDI_USER_DATA_EDIT_X, KPSTEDI_USER_DATA_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE, 0, KPSTEDI_USER_DATA_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_UserDataEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_UserDataEdit, WM_SETTEXT, 0, (LPARAM)user_data_buf);
#endif // #if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)


#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_USER, NULL, KPSTEDI_USER_PWD_PROMPT, KPSTEDI_USER_PWD_PROMPT_X, KPSTEDI_USER_PWD_PROMPT_Y, KPSTEDI_USER_PWD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_USER, &(KpstEdiDialogPtr->m_UserPwdEdit), str_buf + (KPSTEDI_EDIT_MAX_CONTROL_CHARS - KPSTEDI_PWD_NUM_CHARS), KPSTEDI_PWD_EDIT_WDT, KPSTEDI_USER_PWD_EDIT_X, KPSTEDI_USER_PWD_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE,
#  if KPSTEDI_MODE & OWNER_MODE
         ES_PASSWORD,
#  else
         0,
#  endif
         KPSTEDI_PWD_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_UserPwdEdit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_UserPwdEdit, WM_SETTEXT, 0, (LPARAM)user_pwd_buf);

#  if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
      if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_USER, NULL, KPSTEDI_REPEAT_PWD_PROMPT, KPSTEDI_USER_PWD_PROMPT_X /* KPSTEDI_USER_PWD_2_PROMPT_X */, KPSTEDI_USER_PWD_2_PROMPT_Y, KPSTEDI_USER_PWD_2_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
      if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_USER, &(KpstEdiDialogPtr->m_UserPwd2Edit), str_buf + (KPSTEDI_EDIT_MAX_CONTROL_CHARS - KPSTEDI_PWD_NUM_CHARS), KPSTEDI_PWD_EDIT_WDT, KPSTEDI_USER_PWD_2_EDIT_X, KPSTEDI_USER_PWD_2_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE,
#     if KPSTEDI_MODE & OWNER_MODE
         ES_PASSWORD,
#     else
         0,
#     endif
         KPSTEDI_PWD_EDIT_NUMLINES);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_UserPwd2Edit==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         SendMessage(KpstEdiDialogPtr->m_UserPwd2Edit, WM_SETTEXT, 0, (LPARAM)user_pwd_buf);

#  endif // #  if KPSTEDI_MODE & OWNER_MODE

#endif // #if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)


#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  if KPSTEDI_MODE & BOUND_MODE
      if(bound_flash || lic_flash)
#  endif
      {
         if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_USER, NULL, KPSTEDI_ADMIN_PWD_PROMPT, KPSTEDI_ADMIN_PWD_PROMPT_X, KPSTEDI_ADMIN_PWD_PROMPT_Y, KPSTEDI_ADMIN_PWD_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
         if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_USER, &(KpstEdiDialogPtr->m_AdminPwdEdit), str_buf + (KPSTEDI_EDIT_MAX_CONTROL_CHARS - KPSTEDI_PWD_NUM_CHARS), KPSTEDI_PWD_EDIT_WDT, KPSTEDI_ADMIN_PWD_EDIT_X, KPSTEDI_ADMIN_PWD_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE,
#  if KPSTEDI_MODE & OWNER_MODE
            ES_PASSWORD,
#  else
            0,
#  endif
            KPSTEDI_PWD_EDIT_NUMLINES);
         if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_AdminPwdEdit==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            SendMessage(KpstEdiDialogPtr->m_AdminPwdEdit, WM_SETTEXT, 0, (LPARAM)admin_pwd_buf);

#  if KPSTEDI_MODE & OWNER_MODE
         if(SUCCEEDED(retc)) retc=KpCreateStatic(hKpInstance, KPSTED_PARENT_USER, NULL, KPSTEDI_REPEAT_PWD_PROMPT, KPSTEDI_ADMIN_PWD_PROMPT_X /* KPSTEDI_ADMIN_PWD_2_PROMPT_X */, KPSTEDI_ADMIN_PWD_2_PROMPT_Y, KPSTEDI_ADMIN_PWD_2_PROMPT_DX, 1, KPW_CONTROL_STYLE_NORMAL, 0, 0, NULL);
         if(SUCCEEDED(retc)) retc=KpCreateEdit(hKpInstance, KPSTED_PARENT_USER, &(KpstEdiDialogPtr->m_AdminPwd2Edit), str_buf + (KPSTEDI_EDIT_MAX_CONTROL_CHARS - KPSTEDI_PWD_NUM_CHARS), KPSTEDI_PWD_EDIT_WDT, KPSTEDI_ADMIN_PWD_2_EDIT_X, KPSTEDI_ADMIN_PWD_2_EDIT_Y, KPW_CONTROL_STYLE_NORMAL, WS_EX_CLIENTEDGE,
#     if KPSTEDI_MODE & OWNER_MODE
            ES_PASSWORD,
#     else
            0,
#     endif
            KPSTEDI_PWD_EDIT_NUMLINES);
         if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_AdminPwd2Edit==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
         if(SUCCEEDED(retc))
            SendMessage(KpstEdiDialogPtr->m_AdminPwd2Edit, WM_SETTEXT, 0, (LPARAM)admin_pwd_buf);

#  endif // #        if KPSTEDI_MODE & OWNER_MODE
      }
#endif // #     if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)


// ------------------------------------
// OK Cancel mygtukai

      but_y = KPSTEDI_BUT_Y;
#if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == USER_MODE
#ifndef NO_DIRECT_REZ_FILE
      if(num_of_lics) but_y += KPSTEDI_CTRL_HGT; // kai num_of_lics>0 ar -1
#endif
      if(rez_fname[0]) but_y += KPSTEDI_CTRL_HGT;
#endif

      if(SUCCEEDED(retc)) /* retc= */ KpCreateButton(hKpInstance, hwndDlg, &(KpstEdiDialogPtr->m_OkButton), IDOK, KP_MSG_GERAI, KPSTEDI_OK_BUT_X, but_y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_OkButton==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) /* retc= */ KpCreateButton(hKpInstance, hwndDlg, &(KpstEdiDialogPtr->m_CancelButton), IDCANCEL, KP_MSG_ATSAUKTI, KPSTEDI_CANCEL_BUT_X, but_y, KPW_BUTTON_WDT, KPW_BUTTON_HGT, 0, 0);
      if(SUCCEEDED(retc)) if(KpstEdiDialogPtr->m_CancelButton==NULL)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, False, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
#if KPSTEDI_MODE & LOGIN_MODE
         if(!SetFocus(KpstEdiDialogPtr->m_UserDataEdit))
#else
         if(!SetFocus(KpstEdiDialogPtr->m_OkButton))
#endif
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);

#if FALSE // #if KPSTEDI_MODE & GENERAL_MODE
      if(SUCCEEDED(retc))
         if(!InvalidateRect(KpstEdiDialogPtr->m_TabProduct, 0, TRUE))
              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!InvalidateRect(KpstEdiDialogPtr->m_TabStart, 0, TRUE))
              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!InvalidateRect(KpstEdiDialogPtr->m_TabBound, 0, TRUE))
              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!InvalidateRect(KpstEdiDialogPtr->m_TabData, 0, TRUE))
              retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
#endif

      KP_DELETEA(str_buf);

      break;

   case WM_INITDIALOG:
      retw=TRUE;
      break;

#if KPSTEDI_MODE & (OWNER_MODE | BOUND_MODE | USER_MODE | STARTER_MODE)
   case WM_PAINT:
// ------------------------
// frames inside of m_TabUser

#if KPSTEDI_MODE & (STARTER_MODE | USER_MODE)
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniRezFName(rez_fname);
#endif
#  if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == USER_MODE
      if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniNumOfLics(&num_of_lics);
#endif

      hdc = NULL;
      if(SUCCEEDED(retc))
      {
         hdc = BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

#if KPSTEDI_MODE & OWNER_MODE
// KPSTEDI_FRAME13
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME13_Y1, KPSTEDI_FRAME_X + KPSTEDI_FRAME_DX, KPSTEDI_FRAME13_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
#endif
#if KPSTEDI_MODE & BOUND_MODE
// KPSTEDI_FRAME6
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME6_Y1, KPSTEDI_FRAME_X + KPSTEDI_FRAME_DX, KPSTEDI_FRAME6_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
#endif

#if KPSTEDI_MODE & (STARTER_MODE | USER_MODE)
      but_y = KPSTEDI_FRAME6_Y2; // KPSTEDI_BUT_Y;
#  if (KPSTEDI_MODE & (STARTER_MODE | USER_MODE)) == USER_MODE
#     ifndef NO_DIRECT_REZ_FILE
      if(num_of_lics) but_y += KPSTEDI_CTRL_HGT; // kai num_of_lics>0 ar -1
#     endif
      if(rez_fname[0]) but_y += KPSTEDI_CTRL_HGT;
#  endif

// KPSTEDI_FRAME6
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME6_Y1, KPSTEDI_FRAME_X + KPSTEDI_FRAME_DX, but_y, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
#endif

// ------------------------
      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
#endif

   case WM_CLOSE:
// KpMsgOut("KpStEdiDialogProc:WM_CLOSE", IDI_ASTERISK, KP_MB_TESTI);
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      endfl=True;
      close_window=True;
      break;

   case WM_QUIT:
// KpMsgOut("KpStEdiDialogProc:WM_QUIT", IDI_ASTERISK, KP_MB_TESTI);
      switch(retp)
      {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT:
// KpMsgOut("KpStEdiDialogProc:IDABORT", IDI_ASTERISK, KP_MB_TESTI);
            retc = KP_E_SYSTEM_ERROR;
            break;
      }
      endfl=True;
      break;

   case WM_COMMAND:
      switch(retp)
      {
      case IDOK:
         endfl=True;
         break;

      case IDCANCEL:
// KpMsgOut("KpStEdiDialogProc:IDCANCEL", IDI_ASTERISK, KP_MB_TESTI);
         if(SUCCEEDED(retc)) if(!KpstEdiDialogPtr->m_bOpenFileFl)
         {
            endfl=True;
            close_window=True;
         }
         break;

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
      case KP_ID_OPEN:
         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_bOpenFileFl=True;

         if(SUCCEEDED(retc))
         {
            if(KpstEdiDialogPtr->m_RezEdit!=NULL)
            {
               SendMessage(KpstEdiDialogPtr->m_RezEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)rez_fname);
               rez_fname[KP_MAX_FNAME_LEN]=Nul;
            }

            op_fn_str.lStructSize=sizeof(op_fn_str);
            op_fn_str.hwndOwner=hwndDlg;
            op_fn_str.hInstance=hKpInstance;

            strcpy(filters, KPSTEDI_REZ_FILES);
            pntd=filters+strlen(filters)+1;
            strcpy(pntd, "*.dat");
            pntd+=strlen(pntd)+1;
            *(pntd++)=Nul;
            *(pntd++)=Nul;
            op_fn_str.lpstrFilter=(const char *)filters;

            op_fn_str.lpstrCustomFilter=NULL;
            op_fn_str.nMaxCustFilter=0;
            op_fn_str.nFilterIndex=1;
            op_fn_str.lpstrFile=(char *)rez_fname;
            op_fn_str.nMaxFile=KP_MAX_FNAME_LEN;
            op_fn_str.lpstrFileTitle=NULL;
            op_fn_str.nMaxFileTitle=0;


            strcpy(ini_dir, rez_fname);
            pntd=ini_dir;
            do
            {
               pnts=strchr(pntd, '\\');
               if(pnts) pntd=pnts+1;
            } while(pnts);
            if(pntd==ini_dir)
            {
               strcpy(ini_dir, KPSTEDI_INIT_DIR);
               op_fn_str.nFileOffset=(WORD)0;
            }
            else
            {
               *pntd=Nul;
               op_fn_str.nFileOffset=(WORD)strlen(ini_dir);
            }
            op_fn_str.lpstrInitialDir=(char *)ini_dir;

            op_fn_str.lpstrTitle = (const char *)KPSTEDI_SEL_REZ_FILE;
            op_fn_str.Flags=0;

            pnts=strchr(rez_fname, '.');
            if(pnts!=NULL) op_fn_str.nFileExtension=pnts-rez_fname+1;
            else op_fn_str.nFileExtension=(int)strlen(rez_fname);

            op_fn_str.lpstrDefExt="dat";
            op_fn_str.lCustData=0L;
            op_fn_str.lpfnHook=0L;
            op_fn_str.lpTemplateName=NULL;
         }

         if(SUCCEEDED(retc))
         {
            strcpy(rez_nam_sav, rez_fname);
            if(!GetOpenFileName(&op_fn_str))
            {
// nesuveikia, jei neteisingas pradinio failo vardas - isvalom
               rez_fname[0]=Nul;
               strcpy(ini_dir, KPSTEDI_INIT_DIR);
               op_fn_str.nFileOffset=(WORD)0;
               op_fn_str.nFileExtension=0;

               if(!GetOpenFileName(&op_fn_str))
               {
//                retc=KpErrorProc.OutputErrorMessage(KP_E_CANCEL, CommDlgExtendedError(), True, __FILE__, __LINE__, 0L);
                  retc=KP_E_CANCEL;
               }
            }
            if(FAILED(retc))
            {
               strcpy(rez_fname, rez_nam_sav);
               retc=S_OK;
            }
            SendMessage(KpstEdiDialogPtr->m_RezEdit, WM_SETTEXT, 0, (LPARAM)rez_fname);
         }

         if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniRezFName(rez_fname);

         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_bOpenFileFl=False;
         break;
#endif
      }
      break;

#if KPSTEDI_MODE & GENERAL_MODE
   case WM_NOTIFY:
      if(SUCCEEDED(retc)) switch(TabCtrl_GetCurSel(KpstEdiDialogPtr->m_TabCtrl))
      {
      case KPSTEDI_ID_PRODUCT_TAB:
         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_CurTab = KpstEdiDialogPtr->m_TabProduct;
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabProduct, SW_SHOW);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabStart, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabBound, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabData, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabUser, SW_HIDE);
         break;

      case KPSTEDI_ID_START_TAB:
         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_CurTab = KpstEdiDialogPtr->m_TabStart;
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabProduct, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabStart, SW_SHOW);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabBound, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabData, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabUser, SW_HIDE);
         break;

      case KPSTEDI_ID_BOUND_TAB:
         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_CurTab = KpstEdiDialogPtr->m_TabBound;
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabProduct, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabStart, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabBound, SW_SHOW);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabData, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabUser, SW_HIDE);
         break;

      case KPSTEDI_ID_DATA_TAB:
         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_CurTab = KpstEdiDialogPtr->m_TabData;
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabProduct, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabStart, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabBound, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabData, SW_SHOW);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabUser, SW_HIDE);
         break;

      case KPSTEDI_ID_USER_TAB:
         if(SUCCEEDED(retc)) KpstEdiDialogPtr->m_CurTab = KpstEdiDialogPtr->m_TabUser;
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabProduct, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabStart, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabBound, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabData, SW_HIDE);
         if(SUCCEEDED(retc)) ShowWindow(KpstEdiDialogPtr->m_TabUser, SW_SHOW);
         break;
      }
      break;
#endif

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(close_window)
   {
      retc0 = S_OK;
      if(SUCCEEDED(retc)) retc0=KpstEdiDialogPtr->CloseWindow();
//    if(SUCCEEDED(retc)) retc=retc0;

      retc=KP_E_CANCEL;
   }

   if(endfl && SUCCEEDED(retc))
   {
      PostMessage(NULL, uMsg, wParam, lParam);
      retw=TRUE;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}


#if KPSTEDI_MODE & GENERAL_MODE
// ----------------------------------
BOOL CALLBACK KpstediTabProductProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HDC hdc = NULL;
PAINTSTRUCT ps;
BOOL retw=FALSE;

   if((KpstEdiDialogPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_PAINT:
// ------------------------
// frames inside of m_TabProduct
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=BeginPaint(hwndDlg, &ps);
//       hdc=BeginPaint(KpstEdiDialogPtr->m_TabProduct, &ps);
//       hdc=GetDC(KpstEdiDialogPtr->m_TabProduct);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// KPSTEDI_FRAME1
#if FALSE
      if(SUCCEEDED(retc))
         if(!SelectObject(hdc, KpstEdiDialogPtr->m_aPenScheme[KpShadowDark]))
             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!MoveToEx(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME1_Y1, NULL))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!LineTo(hdc, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME1_Y1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc))
         if(!SelectObject(hdc, KpstEdiDialogPtr->m_aPenScheme[KpShadowBlack]))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!MoveToEx(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME1_Y1+1, NULL))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      if(SUCCEEDED(retc))
         if(!LineTo(hdc, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME1_Y1+1))
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
#endif

#if FALSE
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, KPSTEDI_FRAME_X,                  KPSTEDI_FRAME1_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX,  KPSTEDI_FRAME1_Y1, KP_WND_SUNKEN, KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, KPSTEDI_FRAME_X,                  KPSTEDI_FRAME1_Y2, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX+1,KPSTEDI_FRAME1_Y2, KP_WND_SUNKEN, KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, KPSTEDI_FRAME_X,                  KPSTEDI_FRAME1_Y1, KPSTEDI_FRAME_X,                   KPSTEDI_FRAME1_Y2, KP_WND_SUNKEN, KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawLine(hdc, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME1_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX,  KPSTEDI_FRAME1_Y2, KP_WND_SUNKEN, KpstEdiDialogPtr->m_aPenScheme);
#endif

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME1_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME1_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);

// KPSTEDI_FRAME2
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME2_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME2_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);


// ------------------------
//    if(SUCCEEDED(retc)) EndPaint(KpstEdiDialogPtr->m_TabProduct, &ps);
      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


#if KPSTEDI_MODE & GENERAL_MODE
// ----------------------------------
BOOL CALLBACK KpstediTabStartProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HDC hdc = NULL;
PAINTSTRUCT ps;
BOOL retw=FALSE;

   if((KpstEdiDialogPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_PAINT:
// ------------------------
// frames inside of m_TabStart
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME3_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME3_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME4_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME4_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME12_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME12_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME14_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME14_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


#if KPSTEDI_MODE & GENERAL_MODE
// ----------------------------------
BOOL CALLBACK KpstediTabBoundProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HDC hdc = NULL;
PAINTSTRUCT ps;
BOOL retw=FALSE;

   if((KpstEdiDialogPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_PAINT:
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME6_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME6_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME7_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME7_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME8_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME8_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME9_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME9_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME10_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME10_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);

      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


#if KPSTEDI_MODE & GENERAL_MODE
// ----------------------------------
BOOL CALLBACK KpstediTabDataProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HDC hdc = NULL;
PAINTSTRUCT ps;
BOOL retw=FALSE;

   if((KpstEdiDialogPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_PAINT:
// ------------------------
// frames inside of m_TabData
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME5_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME5_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME11_Y1, KPSTEDI_FRAME_X+KPSTEDI_FRAME_DX, KPSTEDI_FRAME11_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);


// ------------------------
      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;


   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case KP_ID_OPEN:
         PostMessage(KpstEdiDialogPtr->m_hDialogWindow, uMsg, wParam, lParam);
         break;
      }
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


#if KPSTEDI_MODE & GENERAL_MODE
// ----------------------------------
BOOL CALLBACK KpstediTabUserProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
HRESULT retc=S_OK;
HDC hdc = NULL;
PAINTSTRUCT ps;
BOOL retw=FALSE;

   if((KpstEdiDialogPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

   if(SUCCEEDED(retc)) switch(uMsg)
   {
   case WM_PAINT:
// ------------------------
// frames inside of m_TabUser
      hdc=NULL;
      if(SUCCEEDED(retc))
      {
         hdc=BeginPaint(hwndDlg, &ps);
         if(hdc==NULL)
            retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }

// KPSTEDI_FRAME13
      if(SUCCEEDED(retc)) retc=KpDrawRect(hdc, KPSTEDI_FRAME_X, KPSTEDI_FRAME13_Y1, KPSTEDI_FRAME_X + KPSTEDI_FRAME_DX, KPSTEDI_FRAME13_Y2, KP_WND_SUNKEN, NULL); // KpstEdiDialogPtr->m_aPenScheme);

// ------------------------
      if(SUCCEEDED(retc)) EndPaint(hwndDlg, &ps);

      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;


   case WM_COMMAND:
      switch(LOWORD(wParam))
      {
      case KP_ID_OPEN:
         PostMessage(KpstEdiDialogPtr->m_hDialogWindow, uMsg, wParam, lParam);
         break;
      }
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;

   default:
      retw=DefWindowProc(hwndDlg, uMsg, wParam, lParam);
      break;
   }

   if(FAILED(retc)) PostQuitMessage(IDABORT);

return(retw);
}
#endif


// ----------------------------------
HRESULT KpStEdiDlg::DoEdit(long lMsec)
{
HRESULT retc=S_OK;
MSG msg;
int retp;
bool endfl=False;
HWND cur_wnd;
UINT exit_timer_id=0;

#if (KPSTEDI_MODE & (USER_MODE | OWNER_MODE)) == 0
unsigned char num_buf[MAX_64BIT_HEX_DIGITS /* MAX_LONG_DIGITS */ + 1];
#endif

#if KPSTEDI_MODE & GENERAL_MODE
unsigned char cmd_str[KP_MAX_FILE_LIN_WDT+1];
int prol_show_time;
unsigned char prol_fname[KP_MAX_FNAME_LEN+1];
int bmp_wdt;
int bmp_hgt;
unsigned char pwd_win_name[KP_MAX_FNAME_LEN+1];
unsigned char pwd_buf[KP_KWD_LEN+1];
unsigned char old_pwd_buf[KP_KWD_LEN+1];
int pwd_ed_ctrl=0;
int pwd_ok_but=0;
unsigned char vol_name[KP_MAX_FNAME_LEN+1];
//long ser_no=0L;
unsigned char bmp_fname[KP_MAX_FNAME_LEN+1];
unsigned char epil_fname[KP_MAX_FNAME_LEN+1];
int epil_sh_time=0;
unsigned char pres_fname[KP_MAX_FNAME_LEN+1];
bool ch_cd=False;
bool bound=False;
bool bound_flash=False;
bool lic_flash=False;
int prod_ver = 0;
int upd_num = -1;
int num_of_lics=0;
unsigned char test_cid[KPST_TXTCD_CHARS_PER_VAL_TID+1];
unsigned char prod_name[KP_MAX_FNAME_LEN+1];
unsigned char wnd_name[KP_MAX_FNAME_LEN+1];
unsigned char publisher[KP_MAX_FNAME_LEN+1];
unsigned char rez_var[KP_MAX_FNAME_LEN+1];
bool kumul=False;
int shuff_cnt=0;
long att_offset=0L;
bool cid_dir=False;
int cid_typ = 0;
unsigned char att_ext[KP_MAX_FTYPE_LEN+1];
bool on_top=False;
bool muted=False;
bool full_scr=False;
bool subst = False;
bool eboard = False;
bool clr_clipbrd = False;
bool sh_ie = False;
bool hide_bkmrks = False;
bool sound_muted = False;
bool find_but = False;
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
bool test_upd = False;
#endif
bool skip_fl = False;
int st_pos = 0;

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
unsigned char reg_url[KP_MAX_FNAME_LEN+1];
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
unsigned char rez_fname[KP_MAX_FNAME_LEN+1];
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
long flash_id=0L;
int lic_id = 0;
unsigned char lic_buf[KP_MAX_FILE_LIN_WDT+1];
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
unsigned char user_pwd_buf[KP_KWD_LEN+1];
unsigned char user_pwd_sav[KP_KWD_LEN + 1];
#  if KPSTEDI_MODE & OWNER_MODE
unsigned char user_pwd_2_buf[KP_KWD_LEN+1];
#  endif
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
unsigned char user_data_buf[KP_MAX_FILE_LIN_WDT+1];
unsigned char user_data_sav[KP_MAX_FILE_LIN_WDT+1];
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
unsigned char admin_pwd_buf[KP_KWD_LEN+1];
// unsigned char admin_pwd_2_buf[KP_KWD_LEN+1];
#endif

bool user_data_changed = False;

#ifdef Debug
unsigned char str_buf[100];
#endif

   if((theKpStAppPtr==NULL) && SUCCEEDED(retc))
      retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
   if(SUCCEEDED(retc)) retc=theKpStAppPtr->GetIniRegURL(reg_url);
#endif

   if((lMsec!=0) && SUCCEEDED(retc))
   {
      exit_timer_id=SetTimer(m_hDialogWindow, KP_SLEEP_TIMER, lMsec, NULL);
      if(!exit_timer_id)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
   }

   if(SUCCEEDED(retc)) do
   {
      if(GetMessage(&msg, NULL, 0, 0)<0)
         retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);

      if(SUCCEEDED(retc)) TranslateMessage(&msg);

      retp=LOWORD(msg.wParam);
      skip_fl = False;

      if(SUCCEEDED(retc)) switch(msg.message)
      {
      case WM_QUIT:
// KpMsgOut("DoEdit:WM_QUIT", IDI_ASTERISK, KP_MB_TESTI);
         switch(retp)
         {
         case IDCANCEL: retc = KP_E_CANCEL; break;
         case IDABORT:
// KpMsgOut("DoEdit:IDABORT", IDI_ASTERISK, KP_MB_TESTI);
            retc = KP_E_SYSTEM_ERROR;
            break;
         }
         endfl=True;
         break;

      case WM_CLOSE:
// KpMsgOut("DoEdit:WM_CLOSE", IDI_ASTERISK, KP_MB_TESTI);
         endfl=True;
         break;

      case WM_TIMER:
         if((UINT)retp==exit_timer_id)
         {
            if(!KillTimer(m_hDialogWindow, retp))
            {
//             retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
            }
// KpMsgOut("DoEdit:WM_TIMER", IDI_ASTERISK, KP_MB_TESTI);
            endfl=True;
         }
         break;

      case WM_CHAR:
         switch(retp)
         {
         case KP_HP11_TOGGLE_CONSOLE:
            if(lKphp11ThreadId!=0L)
               if(!PostThreadMessage(lKphp11ThreadId, msg.message, msg.wParam, msg.lParam))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), False, __FILE__, __LINE__, 0L, NULL);
            break;

         case Tab:
            cur_wnd=GetFocus();
#if KPSTEDI_MODE & GENERAL_MODE
            if(m_CurTab==m_TabProduct)
            {
               if(cur_wnd==m_ProdName) SetFocus(m_bShiftFl?m_CancelButton:m_Publisher);
               else if(cur_wnd==m_Publisher) SetFocus(m_bShiftFl?m_ProdName:m_ProdVer);
               else if(cur_wnd==m_ProdVer) SetFocus(m_bShiftFl?m_Publisher:m_UpdNum);
               else if(cur_wnd==m_UpdNum) SetFocus(m_bShiftFl?m_ProdVer:m_VolEdit);
               else if(cur_wnd==m_VolEdit) SetFocus(m_bShiftFl?m_UpdNum:m_WndName);
               else if(cur_wnd==m_WndName) SetFocus(m_bShiftFl?m_VolEdit:m_OkButton);

               else if(cur_wnd==m_OkButton) SetFocus(m_bShiftFl?m_VolEdit:m_CancelButton);
               else if(cur_wnd==m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_ProdName);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabStart)
            {
               if(cur_wnd==m_CmdStrEdit) SetFocus(m_bShiftFl?m_CancelButton:m_AttOff);
               else if(cur_wnd==m_AttOff) SetFocus(m_bShiftFl?m_CmdStrEdit:m_AttExt);
               else if(cur_wnd==m_AttExt) SetFocus(m_bShiftFl?m_AttOff:m_ProlEdit);
               else if(cur_wnd==m_ProlEdit) SetFocus(m_bShiftFl?m_AttExt:m_BmpEdit);
               else if(cur_wnd==m_BmpEdit) SetFocus(m_bShiftFl?m_ProlEdit:m_BmpDxEdit);
               else if(cur_wnd==m_BmpDxEdit) SetFocus(m_bShiftFl?m_BmpEdit:m_BmpDyEdit);
               else if(cur_wnd==m_BmpDyEdit) SetFocus(m_bShiftFl?m_BmpDxEdit:m_MuteBox);
               else if(cur_wnd==m_MuteBox) SetFocus(m_bShiftFl?m_BmpDyEdit:m_EpilEdit);
               else if(cur_wnd==m_EpilEdit) SetFocus(m_bShiftFl?m_MuteBox:m_ProlTimeEdit);
               else if(cur_wnd==m_ProlTimeEdit) SetFocus(m_bShiftFl?m_EpilEdit:m_EpilTimeEdit);
               else if(cur_wnd==m_EpilTimeEdit) SetFocus(m_bShiftFl?m_ProlTimeEdit:m_OnTopBox);
               else if(cur_wnd==m_OnTopBox) SetFocus(m_bShiftFl?m_EpilTimeEdit:m_FullScrBox);
               else if(cur_wnd==m_FullScrBox) SetFocus(m_bShiftFl?m_OnTopBox:m_ClearClipBrdBox);
               else if(cur_wnd==m_ClearClipBrdBox) SetFocus(m_bShiftFl?m_FullScrBox:m_SubstBox);
               else if(cur_wnd==m_SubstBox) SetFocus(m_bShiftFl?m_ClearClipBrdBox:m_EboardBox);
               else if(cur_wnd==m_EboardBox) SetFocus(m_bShiftFl?m_SubstBox:m_ShIEBox);
               else if(cur_wnd==m_ShIEBox) SetFocus(m_bShiftFl?m_EboardBox:m_HideBkmrksBox);
               else if(cur_wnd==m_HideBkmrksBox) SetFocus(m_bShiftFl?m_ShIEBox:m_SoundMutedBox);
               else if(cur_wnd==m_SoundMutedBox) SetFocus(m_bShiftFl?m_HideBkmrksBox:m_TestUpdatesBox);
               else if(cur_wnd==m_TestUpdatesBox) SetFocus(m_bShiftFl?m_SoundMutedBox:m_FindButBox);
               else if(cur_wnd==m_FindButBox) SetFocus(m_bShiftFl?m_TestUpdatesBox:m_OkButton);

               else if(cur_wnd==m_OkButton) SetFocus(m_bShiftFl?m_FindButBox:m_CancelButton);
               else if(cur_wnd==m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_CmdStrEdit);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabBound)
            {
               if(cur_wnd==m_BoundBox) SetFocus(m_bShiftFl?m_CancelButton:m_CiTypBBox);
               else if(cur_wnd==m_CiTypBBox) SetFocus(m_bShiftFl?m_BoundBox:m_CiTypDBox);
               else if(cur_wnd==m_CiTypDBox) SetFocus(m_bShiftFl?m_CiTypBBox:m_CiTypPBox);
               else if(cur_wnd==m_CiTypPBox) SetFocus(m_bShiftFl?m_CiTypDBox:m_CiTypMBox);
               else if(cur_wnd==m_CiTypMBox) SetFocus(m_bShiftFl?m_CiTypPBox:m_CiTypNBox);
               else if(cur_wnd==m_CiTypNBox) SetFocus(m_bShiftFl?m_CiTypMBox:m_CiTypVBox);
               else if(cur_wnd==m_CiTypVBox) SetFocus(m_bShiftFl?m_CiTypNBox:m_CiDirBox);
               else if(cur_wnd==m_CiDirBox) SetFocus(m_bShiftFl?m_CiTypVBox:m_CiFileBox);
               else if(cur_wnd==m_CiFileBox) SetFocus(m_bShiftFl?m_CiDirBox:m_RegURL);
               else if(cur_wnd==m_RegURL) SetFocus(m_bShiftFl?m_CiFileBox:m_NumOfLics);
               else if(cur_wnd==m_NumOfLics) SetFocus(m_bShiftFl?m_RegURL:m_IniLicID);
               else if(cur_wnd==m_IniLicID) SetFocus(m_bShiftFl?m_NumOfLics:m_BoundFlashBox);
               else if(cur_wnd==m_BoundFlashBox) SetFocus(m_bShiftFl?m_IniLicID:m_LicFlashBox);
               else if(cur_wnd==m_LicFlashBox) SetFocus(m_bShiftFl?m_BoundFlashBox:m_FlashId);
               else if(cur_wnd==m_FlashId) SetFocus(m_bShiftFl?m_LicFlashBox:m_PwdWndEdit);
               else if(cur_wnd==m_PwdWndEdit) SetFocus(m_bShiftFl?m_FlashId:m_PwdEditEdit);
               else if(cur_wnd==m_PwdEditEdit) SetFocus(m_bShiftFl?m_PwdWndEdit:m_PwdEdit);
               else if(cur_wnd==m_PwdEdit) SetFocus(m_bShiftFl?m_PwdEditEdit:m_OldPwdEdit);
               else if(cur_wnd==m_OldPwdEdit) SetFocus(m_bShiftFl?m_PwdEdit:m_PwdButEdit);
               else if(cur_wnd==m_PwdButEdit) SetFocus(m_bShiftFl?m_OldPwdEdit:m_ChCDBox);
               else if(cur_wnd==m_ChCDBox) SetFocus(m_bShiftFl?m_PwdButEdit:m_OkButton);

               else if(cur_wnd==m_OkButton) SetFocus(m_bShiftFl?m_ChCDBox:m_CancelButton);
               else if(cur_wnd==m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_BoundBox);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabData)
            {
               if(cur_wnd==m_PresEdit) SetFocus(m_bShiftFl?m_CancelButton:m_RezEdit);
               else if(cur_wnd==m_RezEdit) SetFocus(m_bShiftFl?m_PresEdit:m_RezButton);
               else if(cur_wnd==m_RezButton) SetFocus(m_bShiftFl?m_RezEdit:m_RezVarEdit);
               else if(cur_wnd==m_RezVarEdit){ skip_fl = True; SetFocus(m_bShiftFl?m_RezButton:m_ShuffCnt); }
               else if(cur_wnd==m_ShuffCnt) SetFocus(m_bShiftFl?m_RezVarEdit:m_CumulBox);
               else if(cur_wnd==m_CumulBox) SetFocus(m_bShiftFl?m_ShuffCnt:m_TestCid);
               else if(cur_wnd==m_TestCid) SetFocus(m_bShiftFl?m_CumulBox:m_OkButton);

               else if(cur_wnd==m_OkButton) SetFocus(m_bShiftFl?m_TestCid:m_CancelButton);
               else if(cur_wnd==m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_PresEdit);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab == m_TabUser)
            {
#endif
#if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
               if(cur_wnd == m_UserDataEdit) SetFocus(m_bShiftFl?m_CancelButton:m_UserPwdEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_bShiftFl?m_UserDataEdit:m_UserPwd2Edit);
               else if(cur_wnd == m_UserPwd2Edit) SetFocus(m_bShiftFl?m_UserPwdEdit:m_OkButton); // m_AdminPwdEdit);
//             else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_bShiftFl?m_UserPwd2Edit:m_AdminPwd2Edit);
//             else if(cur_wnd == m_AdminPwd2Edit) SetFocus(m_bShiftFl?m_AdminPwdEdit:m_UserDataEdit);

               else if(cur_wnd == m_OkButton) SetFocus(m_bShiftFl?m_UserPwd2Edit:m_CancelButton);
               else if(cur_wnd == m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_UserDataEdit);
#endif
#if KPSTEDI_MODE & LOGIN_MODE
               if(cur_wnd == m_UserDataEdit) SetFocus(m_bShiftFl?m_CancelButton:m_UserPwdEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_bShiftFl?m_UserDataEdit:m_OkButton);

               else if(cur_wnd == m_OkButton) SetFocus(m_bShiftFl?m_UserPwdEdit:m_CancelButton);
               else if(cur_wnd == m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_UserDataEdit);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
               if(cur_wnd == m_UserDataEdit) SetFocus(m_bShiftFl?m_CancelButton:m_UserPwdEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_bShiftFl?m_UserDataEdit:m_AdminPwdEdit); // m_UserPwd2Edit);
//             else if(cur_wnd == m_UserPwd2Edit) SetFocus(m_bShiftFl?m_UserPwdEdit:m_AdminPwdEdit);
               else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_bShiftFl?m_UserPwdEdit /* m_UserPwd2Edit */:m_OkButton); // m_AdminPwd2Edit);
//             else if(cur_wnd == m_AdminPwd2Edit) SetFocus(m_bShiftFl?m_AdminPwdEdit:m_OkButton);

               else if(cur_wnd == m_OkButton) SetFocus(m_bShiftFl?m_AdminPwdEdit /* m_AdminPwd2Edit */:m_CancelButton);
               else if(cur_wnd == m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_UserDataEdit);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
               else SetFocus(m_OkButton);
            }
#endif

#if KPSTEDI_MODE & (STARTER_MODE | USER_MODE)
            if(cur_wnd==m_RezEdit) SetFocus(m_bShiftFl?m_CancelButton:m_RezButton);
#  if (KPSTEDI_MODE & STARTER_MODE) == 0
            else if(cur_wnd==m_RezButton) SetFocus(m_bShiftFl?m_RezEdit:(m_RegURL?m_RegURL:m_OkButton));
            else if(cur_wnd==m_RegURL) SetFocus(m_bShiftFl?m_RezButton:m_OkButton);
            else if(cur_wnd==m_OkButton) SetFocus(m_bShiftFl?(m_RegURL?m_RegURL:m_RezButton):m_CancelButton);
#  else
            else if(cur_wnd==m_RezButton) SetFocus(m_bShiftFl?m_RezEdit:m_OkButton);
            else if(cur_wnd==m_OkButton) SetFocus(m_bShiftFl?m_RezButton:m_CancelButton);
#  endif
            else if(cur_wnd==m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_RezEdit);
#endif

#if KPSTEDI_MODE & BOUND_MODE
            if(m_IniLicID != NULL)
            {
               if(cur_wnd == m_IniLicID) SetFocus(m_bShiftFl?m_CancelButton:m_UserDataEdit);
               else if(cur_wnd == m_UserDataEdit) SetFocus(m_bShiftFl?m_IniLicID:m_OkButton);

               else if(cur_wnd == m_OkButton) SetFocus(m_bShiftFl?m_UserDataEdit:m_CancelButton);
               else if(cur_wnd == m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_IniLicID);

               else SetFocus(m_OkButton);
            }
            else
            {
               if(cur_wnd == m_FlashId) SetFocus(m_bShiftFl?m_CancelButton:m_UserDataEdit);
               else if(cur_wnd == m_UserDataEdit) SetFocus(m_bShiftFl?m_FlashId:m_AdminPwdEdit);
               else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_bShiftFl?m_UserDataEdit:m_OkButton);

               else if(cur_wnd == m_OkButton) SetFocus(m_bShiftFl?m_AdminPwdEdit:m_CancelButton);
               else if(cur_wnd == m_CancelButton) SetFocus(m_bShiftFl?m_OkButton:m_FlashId);

               else SetFocus(m_OkButton);
            }

#else
            else SetFocus(m_OkButton);
#endif

            break;

         case Enter:
            PostMessage(NULL, WM_COMMAND, IDOK, 0L);
            break;

         case Esc:
// KpMsgOut("DoEdit:Esc", IDI_ASTERISK, KP_MB_TESTI);
            if(!m_bOpenFileFl)
            {
               endfl = True;
               retc = KP_E_CANCEL;
            }
            break;

#ifdef Debug
         default:
sprintf((char *)str_buf, "WM_CHAR: %x", retp); KP_TRACE(str_buf);
            break;
#endif
         } // switch(retp)

         break; // case WM_CHAR:

//    case WM_KEYFIRST:
      case WM_KEYDOWN:
         switch(retp)
         {
         case Shift:
            m_bShiftFl=True;
#ifdef Debug
// KP_TRACE("Shift");
#endif
            break;

         case Dn:
            cur_wnd=GetFocus();
            skip_fl = True;
#if KPSTEDI_MODE & GENERAL_MODE
            if(m_CurTab==m_TabProduct)
            {
               if(cur_wnd==m_ProdName) SetFocus(m_Publisher);
               else if(cur_wnd==m_Publisher) SetFocus(m_ProdVer);
               else if(cur_wnd==m_ProdVer) SetFocus(m_VolEdit);
               else if(cur_wnd==m_UpdNum) SetFocus(m_VolEdit);
               else if(cur_wnd==m_VolEdit) SetFocus(m_WndName);
               else if(cur_wnd == m_WndName) SetFocus(m_OkButton);
               else if(cur_wnd==m_CancelButton);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabStart)
            {
               if(cur_wnd==m_CmdStrEdit) SetFocus(m_AttOff);
               else if(cur_wnd==m_AttOff) SetFocus(m_ProlEdit);
               else if(cur_wnd==m_AttExt) SetFocus(m_ProlEdit);
               else if(cur_wnd==m_ProlEdit) SetFocus(m_BmpEdit);
               else if(cur_wnd==m_BmpEdit) SetFocus(m_BmpDxEdit);
               else if(cur_wnd==m_BmpDxEdit) SetFocus(m_EpilEdit);
               else if(cur_wnd==m_BmpDyEdit) SetFocus(m_EpilEdit);
               else if(cur_wnd==m_MuteBox) SetFocus(m_EpilEdit);
               else if(cur_wnd==m_EpilEdit) SetFocus(m_ProlTimeEdit);
               else if(cur_wnd==m_ProlTimeEdit) SetFocus(m_OnTopBox);
               else if(cur_wnd==m_EpilTimeEdit) SetFocus(m_FullScrBox);
               else if(cur_wnd==m_OnTopBox) SetFocus(m_SubstBox);
               else if(cur_wnd==m_FullScrBox) SetFocus(m_EboardBox);
               else if(cur_wnd==m_ClearClipBrdBox) SetFocus(m_ShIEBox);
               else if(cur_wnd==m_SubstBox) SetFocus(m_HideBkmrksBox);
               else if(cur_wnd==m_EboardBox) SetFocus(m_SoundMutedBox);
               else if(cur_wnd==m_ShIEBox) SetFocus(m_TestUpdatesBox);
               else if(cur_wnd==m_HideBkmrksBox) SetFocus(m_FindButBox);
               else if(cur_wnd==m_SoundMutedBox) SetFocus(m_FindButBox);
               else if(cur_wnd==m_TestUpdatesBox) SetFocus(m_FindButBox);
               else if(cur_wnd==m_FindButBox) SetFocus(m_OkButton);
               else if(cur_wnd==m_CancelButton);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabBound)
            {
               if(cur_wnd==m_BoundBox) SetFocus(m_CiDirBox);
               else if(cur_wnd==m_CiTypBBox) SetFocus(m_CiTypPBox);
               else if(cur_wnd==m_CiTypPBox) SetFocus(m_CiTypNBox);
               else if(cur_wnd==m_CiTypNBox) SetFocus(m_CiDirBox);
               else if(cur_wnd==m_CiTypDBox) SetFocus(m_CiTypMBox);
               else if(cur_wnd==m_CiTypMBox) SetFocus(m_CiTypVBox);
               else if(cur_wnd==m_CiTypVBox) SetFocus(m_CiDirBox);
               else if(cur_wnd==m_CiDirBox) SetFocus(m_CiFileBox);
               else if(cur_wnd==m_CiFileBox) SetFocus(m_RegURL);
               else if(cur_wnd==m_RegURL) SetFocus(m_NumOfLics);
               else if(cur_wnd==m_NumOfLics) SetFocus(m_BoundFlashBox);
               else if(cur_wnd==m_IniLicID) SetFocus(m_LicFlashBox);
               else if(cur_wnd==m_BoundFlashBox) SetFocus(m_PwdWndEdit);
               else if(cur_wnd==m_LicFlashBox) SetFocus(m_PwdWndEdit);
               else if(cur_wnd==m_FlashId) SetFocus(m_PwdWndEdit);
               else if(cur_wnd==m_PwdWndEdit) SetFocus(m_OldPwdEdit);
               else if(cur_wnd==m_PwdEditEdit) SetFocus(m_ChCDBox);
               else if(cur_wnd==m_PwdEdit) SetFocus(m_PwdButEdit);
               else if(cur_wnd==m_OldPwdEdit) SetFocus(m_ChCDBox);
               else if(cur_wnd==m_PwdButEdit) SetFocus(m_ChCDBox);
               else if(cur_wnd==m_ChCDBox) SetFocus(m_OkButton);
               else if(cur_wnd==m_CancelButton);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabData)
            {
               if(cur_wnd==m_PresEdit) SetFocus(m_RezEdit);
               else if(cur_wnd==m_RezEdit) SetFocus(m_RezVarEdit);
               else if(cur_wnd==m_RezButton) SetFocus(m_RezVarEdit);
               else if(cur_wnd==m_RezVarEdit) SetFocus(m_ShuffCnt);
               else if(cur_wnd==m_ShuffCnt) SetFocus(m_TestCid);
               else if(cur_wnd==m_CumulBox) SetFocus(m_TestCid);
               else if(cur_wnd==m_TestCid) SetFocus(m_OkButton);
               else if(cur_wnd==m_CancelButton);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab == m_TabUser)
            {
#endif
#if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
               if(cur_wnd == m_UserDataEdit) SetFocus(m_UserPwdEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_UserPwd2Edit);
               else if(cur_wnd == m_UserPwd2Edit) SetFocus(m_OkButton); // m_AdminPwdEdit);
//             else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_AdminPwd2Edit);
//             else if(cur_wnd == m_AdminPwd2Edit) SetFocus(m_OkButton);
#endif
#if KPSTEDI_MODE & LOGIN_MODE
               if(cur_wnd == m_UserDataEdit) SetFocus(m_UserPwdEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_OkButton);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
               if(cur_wnd == m_UserDataEdit) SetFocus(m_UserPwdEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_AdminPwdEdit); // m_UserPwd2Edit);
//             else if(cur_wnd == m_UserPwd2Edit) SetFocus(m_AdminPwdEdit);
               else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_OkButton); // m_AdminPwd2Edit);
//             else if(cur_wnd == m_AdminPwd2Edit) SetFocus(m_OkButton);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
               else if(cur_wnd==m_CancelButton);
               else SetFocus(m_OkButton);
            }
#endif

#if KPSTEDI_MODE & (STARTER_MODE | USER_MODE)
#  if (KPSTEDI_MODE & STARTER_MODE) == 0
            if(cur_wnd==m_RezEdit) SetFocus(m_RegURL?m_RegURL:m_OkButton);
            else if(cur_wnd==m_RezButton) SetFocus(m_RegURL?m_RegURL:m_CancelButton);
            else if(cur_wnd==m_RegURL) SetFocus(m_OkButton);
#  else
            if(cur_wnd==m_RezEdit) SetFocus(m_OkButton);
            else if(cur_wnd==m_RezButton) SetFocus(m_OkButton);
#  endif
#endif

#if KPSTEDI_MODE & BOUND_MODE
            if(m_IniLicID != NULL)
            {
               if(cur_wnd == m_IniLicID) SetFocus(m_UserDataEdit);
               else if(cur_wnd == m_UserDataEdit) SetFocus(m_OkButton);

               else if(cur_wnd == m_OkButton);
               else if(cur_wnd == m_CancelButton);
               else SetFocus(m_OkButton);
            }
            else
            {
               if(cur_wnd == m_FlashId) SetFocus(m_UserDataEdit);
               else if(cur_wnd == m_UserDataEdit) SetFocus(m_AdminPwdEdit);
               else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_OkButton);

               else if(cur_wnd == m_OkButton);
               else if(cur_wnd == m_CancelButton);
               else SetFocus(m_OkButton);
            }
#else
            else if(cur_wnd == m_OkButton);
            else if(cur_wnd == m_CancelButton);
            else SetFocus(m_OkButton);
#endif
            break;

         case Up:
            cur_wnd=GetFocus();
            skip_fl = True;
#if KPSTEDI_MODE & GENERAL_MODE
            if(m_CurTab==m_TabProduct)
            {
               if(cur_wnd==m_ProdName);
               else if(cur_wnd==m_Publisher) SetFocus(m_ProdName);
               else if(cur_wnd==m_ProdVer) SetFocus(m_Publisher);
               else if(cur_wnd==m_UpdNum) SetFocus(m_Publisher);
               else if(cur_wnd==m_VolEdit) SetFocus(m_ProdVer);
               else if(cur_wnd == m_WndName) SetFocus(m_VolEdit);
               else if(cur_wnd==m_OkButton) SetFocus(m_WndName);
               else if(cur_wnd==m_CancelButton) SetFocus(m_WndName);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabStart)
            {
               if(cur_wnd==m_CmdStrEdit);
               else if(cur_wnd==m_AttOff) SetFocus(m_CmdStrEdit);
               else if(cur_wnd==m_AttExt) SetFocus(m_CmdStrEdit);
               else if(cur_wnd==m_ProlEdit) SetFocus(m_AttOff);
               else if(cur_wnd==m_BmpEdit) SetFocus(m_ProlEdit);
               else if(cur_wnd==m_BmpDxEdit) SetFocus(m_BmpEdit);
               else if(cur_wnd==m_BmpDyEdit) SetFocus(m_BmpEdit);
               else if(cur_wnd==m_MuteBox) SetFocus(m_BmpEdit);
               else if(cur_wnd==m_EpilEdit) SetFocus(m_BmpDxEdit);
               else if(cur_wnd==m_ProlTimeEdit) SetFocus(m_EpilEdit);
               else if(cur_wnd==m_EpilTimeEdit) SetFocus(m_EpilEdit);
               else if(cur_wnd==m_OnTopBox) SetFocus(m_ProlTimeEdit);
               else if(cur_wnd==m_FullScrBox) SetFocus(m_EpilTimeEdit);
               else if(cur_wnd==m_ClearClipBrdBox) SetFocus(m_EpilTimeEdit);
               else if(cur_wnd==m_SubstBox) SetFocus(m_OnTopBox);
               else if(cur_wnd==m_EboardBox) SetFocus(m_FullScrBox);
               else if(cur_wnd==m_ShIEBox) SetFocus(m_ClearClipBrdBox);
               else if(cur_wnd==m_HideBkmrksBox) SetFocus(m_SubstBox);
               else if(cur_wnd==m_SoundMutedBox) SetFocus(m_EboardBox);
               else if(cur_wnd==m_TestUpdatesBox) SetFocus(m_ShIEBox);
               else if(cur_wnd==m_FindButBox) SetFocus(m_HideBkmrksBox);
               else if(cur_wnd==m_OkButton) SetFocus(m_FindButBox);
               else if(cur_wnd==m_CancelButton) SetFocus(m_FindButBox);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabBound)
            {
               if(cur_wnd==m_BoundBox);
               else if(cur_wnd==m_CiTypBBox);
               else if(cur_wnd==m_CiTypPBox) SetFocus(m_CiTypBBox);
               else if(cur_wnd==m_CiTypNBox) SetFocus(m_CiTypPBox);
               else if(cur_wnd==m_CiTypDBox);
               else if(cur_wnd==m_CiTypMBox) SetFocus(m_CiTypDBox);
               else if(cur_wnd==m_CiTypVBox) SetFocus(m_CiTypMBox);
               else if(cur_wnd==m_CiDirBox) SetFocus(m_BoundBox);
               else if(cur_wnd==m_CiFileBox) SetFocus(m_CiDirBox);
               else if(cur_wnd==m_RegURL) SetFocus(m_CiFileBox);
               else if(cur_wnd==m_NumOfLics) SetFocus(m_RegURL);
               else if(cur_wnd==m_IniLicID) SetFocus(m_RegURL);
               else if(cur_wnd==m_BoundFlashBox) SetFocus(m_NumOfLics);
               else if(cur_wnd==m_LicFlashBox) SetFocus(m_IniLicID);
               else if(cur_wnd==m_FlashId) SetFocus(m_IniLicID);
               else if(cur_wnd==m_PwdWndEdit) SetFocus(m_BoundFlashBox);
               else if(cur_wnd==m_PwdEdit) SetFocus(m_PwdWndEdit);
               else if(cur_wnd==m_PwdEditEdit) SetFocus(m_PwdWndEdit);
               else if(cur_wnd==m_OldPwdEdit) SetFocus(m_PwdWndEdit);
               else if(cur_wnd==m_PwdButEdit) SetFocus(m_PwdEditEdit);
               else if(cur_wnd==m_ChCDBox) SetFocus(m_PwdEdit);
               else if(cur_wnd==m_OkButton) SetFocus(m_ChCDBox);
               else if(cur_wnd==m_CancelButton) SetFocus(m_ChCDBox);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabData)
            {
               if(cur_wnd==m_PresEdit);
               else if(cur_wnd==m_RezEdit) SetFocus(m_PresEdit);
               else if(cur_wnd==m_RezButton) SetFocus(m_PresEdit);
               else if(cur_wnd==m_RezVarEdit) SetFocus(m_RezEdit);
               else if(cur_wnd==m_ShuffCnt) SetFocus(m_RezVarEdit);
               else if(cur_wnd==m_CumulBox) SetFocus(m_RezVarEdit);
               else if(cur_wnd==m_TestCid) SetFocus(m_ShuffCnt);
               else if(cur_wnd==m_OkButton) SetFocus(m_TestCid);
               else if(cur_wnd==m_CancelButton) SetFocus(m_TestCid);
               else SetFocus(m_OkButton);
            }
            else if(m_CurTab==m_TabUser)
            {
#endif
#if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
               if(cur_wnd == m_UserDataEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_UserDataEdit);
               else if(cur_wnd == m_UserPwd2Edit) SetFocus(m_UserPwdEdit);
//             else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_UserPwd2Edit);
//             else if(cur_wnd == m_AdminPwd2Edit) SetFocus(m_AdminPwdEdit);
               else if(cur_wnd == m_OkButton) SetFocus(m_UserPwd2Edit); // m_AdminPwd2Edit);
               else if(cur_wnd == m_CancelButton) SetFocus(m_UserPwd2Edit); // m_AdminPwd2Edit);
#endif
#if KPSTEDI_MODE & LOGIN_MODE
               if(cur_wnd == m_UserDataEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_UserDataEdit);
               else if(cur_wnd == m_OkButton) SetFocus(m_UserPwdEdit);
               else if(cur_wnd == m_CancelButton) SetFocus(m_UserPwdEdit);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
               if(cur_wnd == m_UserDataEdit);
               else if(cur_wnd == m_UserPwdEdit) SetFocus(m_UserDataEdit);
//             else if(cur_wnd == m_UserPwd2Edit) SetFocus(m_UserPwdEdit);
               else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_UserPwdEdit); // m_UserPwd2Edit);
//             else if(cur_wnd == m_AdminPwd2Edit) SetFocus(m_AdminPwdEdit);
               else if(cur_wnd == m_OkButton) SetFocus(m_AdminPwdEdit); // m_AdminPwd2Edit);
               else if(cur_wnd == m_CancelButton) SetFocus(m_UserDataEdit);
#endif
#if KPSTEDI_MODE & GENERAL_MODE
               else SetFocus(m_OkButton);
            }
#endif

#if KPSTEDI_MODE & (STARTER_MODE | USER_MODE)
            if(cur_wnd==m_RezEdit);
            else if(cur_wnd==m_RezButton);
#  if (KPSTEDI_MODE & STARTER_MODE) == 0
            else if(cur_wnd==m_RegURL) SetFocus(m_RezEdit);
            else if(cur_wnd==m_OkButton) SetFocus(m_RegURL?m_RegURL:m_RezEdit);
            else if(cur_wnd==m_CancelButton) SetFocus(m_RegURL?m_RegURL:m_RezEdit);
#  else
            else if(cur_wnd==m_OkButton) SetFocus(m_RezEdit);
            else if(cur_wnd==m_CancelButton) SetFocus(m_RezEdit);
#  endif
#endif

#if KPSTEDI_MODE & BOUND_MODE
            if(m_IniLicID != NULL)
            {
               if(cur_wnd == m_IniLicID);
               else if(cur_wnd == m_UserDataEdit) SetFocus(m_IniLicID);

               else if(cur_wnd == m_OkButton) SetFocus(m_UserDataEdit);
               else if(cur_wnd == m_CancelButton) SetFocus(m_UserDataEdit);

               else SetFocus(m_OkButton);
            }
            else
            {
               if(cur_wnd == m_FlashId);
               else if(cur_wnd == m_UserDataEdit) SetFocus(m_FlashId);
               else if(cur_wnd == m_AdminPwdEdit) SetFocus(m_UserDataEdit);

               else if(cur_wnd == m_OkButton) SetFocus(m_AdminPwdEdit);
               else if(cur_wnd == m_CancelButton) SetFocus(m_AdminPwdEdit);

               else SetFocus(m_OkButton);
            }
#else
            else SetFocus(m_OkButton);
#endif
            break;

#ifdef Debug
         default:
sprintf((char *)str_buf, "WM_KEYDOWN: %x", retp); KP_TRACE(str_buf);
            break;
#endif
         } // switch(retp)

         break; // case WM_KEYDOWN:

      case WM_KEYUP:
         if(retp==Shift)
         {
            m_bShiftFl=False;
#ifdef Debug
// KP_TRACE("UnShift");
#endif
         }
         break;

      case WM_COMMAND:
         switch(retp)
         {
         case IDOK:
#if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
            if((m_UserPwdEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_UserPwdEdit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)user_pwd_buf);
               user_pwd_buf[KP_KWD_LEN] = Nul;
               CutInitTrailSpcs(user_pwd_buf);
            }
#endif
            endfl = True;

#if KPSTEDI_MODE & GENERAL_MODE
            cid_typ = 0;

            if((m_CmdStrEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_CmdStrEdit, WM_GETTEXT, KP_MAX_FILE_LIN_WDT, (LPARAM)cmd_str);
               cmd_str[KP_MAX_FILE_LIN_WDT]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniCmdStr(cmd_str);
            }

            if((m_Publisher!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_Publisher, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)publisher);
               publisher[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniPublisher(publisher);
            }

            if((m_ChCDBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_ChCDBox, BM_GETSTATE, 0, 0)&BST_CHECKED) ch_cd=True;
               else ch_cd=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniCheckCD(ch_cd);
            }

            if((m_AttOff!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_AttOff, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%ld", &att_offset);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniAttOff(att_offset);
            }

            if((m_ProdVer!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_ProdVer, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &prod_ver);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniProdVer(prod_ver);
            }

            if((m_UpdNum!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_UpdNum, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS] = Nul;
               sscanf((char *)num_buf, "%d", &upd_num);

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUpdNum(upd_num);
            }

            if((m_BoundBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_BoundBox, BM_GETSTATE, 0, 0)&BST_CHECKED) bound=True;
               else bound=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniBound(bound);
            }

            if((m_AttExt!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_AttExt, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)att_ext);
               att_ext[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniAttExt(att_ext);
            }

            if((m_NumOfLics!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_NumOfLics, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &num_of_lics);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniNumOfLics(num_of_lics);
            }

            if((m_BoundFlashBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_BoundFlashBox, BM_GETSTATE, 0, 0)&BST_CHECKED) bound_flash=True;
               else bound_flash=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniCheckFlash(bound_flash);
            }

            if((m_LicFlashBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_LicFlashBox, BM_GETSTATE, 0, 0)&BST_CHECKED) lic_flash = True;
               else lic_flash = False;

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniLicFlash(lic_flash);
            }

            if((m_ProdName!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_ProdName, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)prod_name);
               prod_name[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniProdName(prod_name);
            }

            if((m_WndName!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_WndName, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)wnd_name);
               wnd_name[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniWndName(wnd_name);
            }

            if((m_ProlEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_ProlEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)prol_fname);
               prol_fname[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniProlFName(prol_fname);
            }

            if((m_ProlTimeEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_ProlTimeEdit, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &prol_show_time);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniProlShowTime(prol_show_time);
            }

            if((m_EpilEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_EpilEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)epil_fname);
               epil_fname[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniEpilFName(epil_fname);
            }

            if((m_EpilTimeEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_EpilTimeEdit, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &epil_sh_time);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniEpilShowTime(epil_sh_time);
            }

            if((m_BmpEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_BmpEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)bmp_fname);
               bmp_fname[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniBmpFName(bmp_fname);
            }

            if((m_BmpDxEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_BmpDxEdit, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &bmp_wdt);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniBitmapWdt(bmp_wdt);
            }

            if((m_BmpDyEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_BmpDyEdit, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &bmp_hgt);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniBitmapHgt(bmp_hgt);
            }

            if((m_PwdWndEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_PwdWndEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)pwd_win_name);
               pwd_win_name[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniPwdWndName(pwd_win_name);
            }

            if((m_PwdEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_PwdEdit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)pwd_buf);
               pwd_buf[KP_KWD_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniPwd(pwd_buf);
            }

            if((m_OldPwdEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_OldPwdEdit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)old_pwd_buf);
               old_pwd_buf[KP_KWD_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniOldPwd(old_pwd_buf);
            }

            if((m_CiDirBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_CiDirBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_dir=True;
               else cid_dir=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniCiDirect(cid_dir);
            }

            if((m_CiTypBBox!=NULL) && (m_CiTypDBox!=NULL) && (m_CiTypPBox!=NULL) && (m_CiTypNBox!=NULL) && (m_CiTypMBox!=NULL) && (m_CiTypVBox!=NULL) && SUCCEEDED(retc))
            {
               cid_typ = 0;
               if(SendMessage(m_CiTypBBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_typ|=KPST_COMPID_BIOS_DATE;
               if(SendMessage(m_CiTypDBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_typ|=KPST_COMPID_DISK_ID;
               if(SendMessage(m_CiTypPBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_typ|=KPST_COMPID_PROC_ID;
               if(SendMessage(m_CiTypNBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_typ|=KPST_COMPID_PROC_NAME;
               if(SendMessage(m_CiTypMBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_typ|=KPST_COMPID_MAC;
               if(SendMessage(m_CiTypVBox, BM_GETSTATE, 0, 0)&BST_CHECKED) cid_typ|=KPST_COMPID_BOLT;

               retc=theKpStAppPtr->SetIniCompIdMode(cid_typ);
            }

            if((m_PwdEditEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_PwdEditEdit, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &pwd_ed_ctrl);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniPwdEdCtrl(pwd_ed_ctrl);
            }

            if((m_PwdButEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_PwdButEdit, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &pwd_ok_but);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniPwdOkBut(pwd_ok_but);
            }

            if((m_VolEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_VolEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)vol_name);
               vol_name[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniVolName(vol_name);
            }

            if((m_TestCid!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_TestCid, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)test_cid);
               test_cid[KPST_TXTCD_CHARS_PER_VAL_TID]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniTestCid(test_cid);
            }

            if((m_PresEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_PresEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)pres_fname);
               pres_fname[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniPresetFName(pres_fname);
            }

            if((m_RezVarEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_RezVarEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)rez_var);
               rez_var[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniRezVar(rez_var);
            }

            if((m_ShuffCnt!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_ShuffCnt, WM_GETTEXT, MAX_LONG_DIGITS, (LPARAM)num_buf);
               num_buf[MAX_LONG_DIGITS]=Nul;
               sscanf((char *)num_buf, "%d", &shuff_cnt);

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniShuffCnt(shuff_cnt);
            }

            if((m_CumulBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_CumulBox, BM_GETSTATE, 0, 0)&BST_CHECKED) kumul=True;
               else kumul=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniKumul(kumul);
            }

            if((m_MuteBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_MuteBox, BM_GETSTATE, 0, 0)&BST_CHECKED) muted=True;
               else muted=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniSoundMuted(muted);
            }

            if((m_OnTopBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_OnTopBox, BM_GETSTATE, 0, 0)&BST_CHECKED) on_top=True;
               else on_top=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniOnTop(on_top);
            }

            if((m_FullScrBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_FullScrBox, BM_GETSTATE, 0, 0)&BST_CHECKED) full_scr=True;
               else full_scr=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniFullScr(full_scr);
            }

            if((m_SubstBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_SubstBox, BM_GETSTATE, 0, 0)&BST_CHECKED) subst=True;
               else subst=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniSubst(subst);
            }

            if((m_EboardBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_EboardBox, BM_GETSTATE, 0, 0)&BST_CHECKED) eboard=True;
               else eboard=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniEboard(eboard);
            }

            if((m_ClearClipBrdBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_ClearClipBrdBox, BM_GETSTATE, 0, 0)&BST_CHECKED) clr_clipbrd=True;
               else clr_clipbrd=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniClearClipBrd(clr_clipbrd);
            }

            if((m_ShIEBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_ShIEBox, BM_GETSTATE, 0, 0)&BST_CHECKED) sh_ie=True;
               else sh_ie=False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniShowIE(sh_ie);
            }

            if((m_HideBkmrksBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_HideBkmrksBox, BM_GETSTATE, 0, 0)&BST_CHECKED) hide_bkmrks = True;
               else hide_bkmrks = False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniHideBkmrks(hide_bkmrks);
            }

            if((m_SoundMutedBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_SoundMutedBox, BM_GETSTATE, 0, 0)&BST_CHECKED) sound_muted = True;
               else sound_muted = False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniSoundMuted(sound_muted);
            }

            if((m_FindButBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_FindButBox, BM_GETSTATE, 0, 0)&BST_CHECKED) find_but = True;
               else find_but = False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniFindBut(find_but);
            }
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
            if((m_TestUpdatesBox!=NULL) && SUCCEEDED(retc))
            {
               if(SendMessage(m_TestUpdatesBox, BM_GETSTATE, 0, 0)&BST_CHECKED) test_upd = True;
               else test_upd = False;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniTestUpdates(test_upd);
            }
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)
            if(SUCCEEDED(retc)) if((m_RegURL!=NULL) && (theKpStAppPtr->m_iKpStMode==KpStEditMode))
            {
               SendMessage(m_RegURL, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)reg_url);
               reg_url[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniRegURL(reg_url);
            }
#endif
#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
            if((m_RezEdit!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_RezEdit, WM_GETTEXT, KP_MAX_FNAME_LEN, (LPARAM)rez_fname);
               rez_fname[KP_MAX_FNAME_LEN]=Nul;

               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniRezFName(rez_fname);
            }
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
            if((m_FlashId!=NULL) && SUCCEEDED(retc))
            {
               SendMessage(m_FlashId, WM_GETTEXT, MAX_64BIT_HEX_DIGITS /* MAX_LONG_DIGITS */, (LPARAM)num_buf);
               num_buf[MAX_64BIT_HEX_DIGITS /* MAX_LONG_DIGITS */] = Nul;
               st_pos = strlen(num_buf) - MAX_LONG_HEX_DIGITS;
               if(st_pos < 0) st_pos = 0;
               retc = ForceTextToHex(num_buf + st_pos);
               if(SUCCEEDED(retc)) sscanf((const char *)num_buf + st_pos, "%lx", &flash_id);
#  if FALSE
char str_buf[100];
sprintf(str_buf, "%x", flash_id);
// KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
KpMsgOut(num_buf, IDI_ASTERISK, KP_MB_TESTI);
#  endif

//             if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniSerNo(ser_no);
               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniFlashId(flash_id);
            }

            if((m_IniLicID!=NULL) && SUCCEEDED(retc))
            {
               if((theKpStAppPtr==NULL) && SUCCEEDED(retc))
                  retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);

               lic_buf[0] = Nul;
               SendMessage(m_IniLicID, WM_GETTEXT, KP_MAX_FILE_LIN_WDT, (LPARAM)lic_buf);
// KpMsgOut(lic_buf, IDI_ASTERISK, KP_MB_TESTI);
               if(SUCCEEDED(retc))
               {
                  retc = RemoveSpaces(lic_buf);
                  if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
               }
               lic_buf[KPST_NUM_OF_LIC_CHARS]=Nul;
               if(SUCCEEDED(retc))
               {
                  if(strlen(lic_buf)==0) lic_id = KpstRand(0);
                  else
                  {
// KpMsgOut(lic_buf, IDI_ASTERISK, KP_MB_TESTI);
                     if(SUCCEEDED(retc))
                     {
                        retc = theKpStAppPtr->ScanLic(lic_buf);
                        if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
                     }
// KpMsgOut(lic_buf, IDI_ASTERISK, KP_MB_TESTI);
                     if(SUCCEEDED(retc))
                     {
                        retc = theKpStAppPtr->UnpackLic();
                        if(FAILED(retc)) retc=KpErrorProc.OutputErrorMessage(retc, null, True, __FILE__, __LINE__, 0L, NULL);
                     }

//                   if(SUCCEEDED(retc)) lic_id = theKpStAppPtr->m_iLicID;
                     if(SUCCEEDED(retc)) retc=EmuTv.GetHp11Variable(&lic_id, KP11_LICID);

                  } // else // if(strlen(lic_buf)==0) lic_id = KpstRand(0);

               } // if(SUCCEEDED(retc))

// irasom duomenis .iss failui
FILE *iss_file = NULL;
HRESULT retc0 = S_OK;
               iss_file = NULL;
               if(SUCCEEDED(retc))
               {
                  iss_file = fopen(KPST_ISS_FILE_NAME, "w");
                  if(iss_file == NULL)
                     retc=KpErrorProc.OutputErrorMessage(KP_E_DIR_ERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               }
               if(SUCCEEDED(retc))
               {
                  fprintf(iss_file, "\n\n");
                  fprintf(iss_file, "function GetLicCode(Param: String): String;\n");
                  fprintf(iss_file, "begin\n");
                  fprintf(iss_file, "Result:=\'%s\';\n", lic_buf);
                  fprintf(iss_file, "end;\n");
                  if(ferror(iss_file) || feof(iss_file))
                     retc = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
               }
               if(iss_file)
               {
                  if(fclose(iss_file)==EOF)
                  {
                     retc0 = KpErrorProc.OutputErrorMessage(KP_E_FERROR, null, True, __FILE__, __LINE__, 0L, NULL);
                     if(SUCCEEDED(retc)) retc = retc0;
                  }
               }

// char out_buf[100];
// sprintf(out_buf, "%d", lic_id);
// KpMsgOut(out_buf, IDI_ASTERISK, KP_MB_TESTI);

// ----------------
               if(SUCCEEDED(retc)) retc=theKpStAppPtr->SetIniIniLicID(lic_id);

            } // if(m_IniLicID!=NULL)
#endif


#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
            if((m_UserPwdEdit!=NULL) && SUCCEEDED(retc))
            {
               retc = theKpStAppPtr->GetIniUserPwd(user_pwd_sav);
#  if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
               KP_ASSERT(m_UserPwd2Edit, KP_E_SYSTEM_ERROR, null, True);
#  endif
               if(SUCCEEDED(retc))
               {
                  SendMessage(m_UserPwdEdit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)user_pwd_buf);
                  user_pwd_buf[KP_KWD_LEN] = Nul;
                  CutInitTrailSpcs(user_pwd_buf);

#  if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
                  SendMessage(m_UserPwd2Edit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)user_pwd_2_buf);
                  user_pwd_2_buf[KP_KWD_LEN] = Nul;
                  CutInitTrailSpcs(user_pwd_2_buf);

                  if(strcmp(user_pwd_buf, user_pwd_2_buf) != 0)
                  {
                     endfl = False;
                     KpMsgOut(KPSTEDI_USER_PWD_NOT_MATCH, IDI_ERROR, KP_MB_TESTI);
                  }
#  endif
               }
               if(endfl && SUCCEEDED(retc))
               {
                  retc = theKpStAppPtr->SetIniUserPwd(user_pwd_buf);
                  if(SUCCEEDED(retc)) if(strcmp(user_pwd_sav, user_pwd_buf) != 0) user_data_changed = True;
               }
            }
#endif // #if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
            if((m_AdminPwdEdit!=NULL) && SUCCEEDED(retc))
            {
#  if FALSE
               KP_ASSERT(m_AdminPwd2Edit, KP_E_SYSTEM_ERROR, null, True);
#  endif
               if(SUCCEEDED(retc))
               {
                  SendMessage(m_AdminPwdEdit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)admin_pwd_buf);
                  admin_pwd_buf[KP_KWD_LEN] = Nul;

#  if FALSE
                  SendMessage(m_AdminPwd2Edit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)admin_pwd_2_buf);
                  admin_pwd_2_buf[KP_KWD_LEN] = Nul;

                  if(strcmp(admin_pwd_buf, admin_pwd_2_buf) != 0)
                  {
                     endfl = False;
                     KpMsgOut(KPSTEDI_ADMIN_PWD_NOT_MATCH, IDI_ERROR, KP_MB_TESTI);
                  }
#  endif
               }
               if(endfl && SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniAdminPwd(admin_pwd_buf);
            }

#endif // #  if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
           if((m_UserDataEdit != NULL) && SUCCEEDED(retc))
            {
               retc = theKpStAppPtr->GetIniUserData(user_data_sav);

               SendMessage(m_UserDataEdit, WM_GETTEXT, KP_KWD_LEN, (LPARAM)user_data_buf);
               user_data_buf[KP_MAX_FILE_LIN_WDT] = Nul;

               if(SUCCEEDED(retc)) retc = theKpStAppPtr->SetIniUserData(user_data_buf);
               if(SUCCEEDED(retc)) if(strcmp(user_data_sav, user_data_buf) != 0) user_data_changed = True;
            }
#endif // #if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)


#if FALSE // #ifdef Debug
{
char str_buf[100];
sprintf(str_buf, "%lx %lx %s", theKpStAppPtr, theKpStAppPtr->m_Ini.lpszRezFName, theKpStAppPtr->m_Ini.lpszRezFName);
KpMsgOut(str_buf, IDI_ASTERISK, KP_MB_TESTI);
}
#endif

#if (KPSTEDI_MODE & STARTER_MODE) == 0
#  if KPSTEDI_MODE & OWNER_MODE
            if(user_data_changed && SUCCEEDED(retc))
            {
#if FALSE
               if(user_pwd_buf[0] != Nul)
               {
                  retc = KpMsgOut(KPSTEDI_SURE_CHANGE_PWD, IDI_ASTERISK, KP_MB_TAIP_NE, 0, KPW_ALIGN_LEFT);
                  if(retc == KP_E_CANCEL)
                  {
                     retc = S_OK;
                     break;
                  }
               }
#else
               retc = theKpStAppPtr->AskUserPUK(KPSTEDI_SURE_CHANGE_PWD);
#endif
            }
#  endif
            if(SUCCEEDED(retc)) retc = theKpStAppPtr->SaveIni();
//          if(SUCCEEDED(retc)) retc = theKpStAppPtr->WriteIni();

#  if (KPSTEDI_MODE & (OWNER_MODE | LOGIN_MODE)) == OWNER_MODE
            if(user_data_changed && SUCCEEDED(retc)) KpMsgOut(KPSTEDI_USER_DATA_CHANGED, IDI_ASTERISK, KP_MB_TESTI);
#  endif
#endif

//          endfl=True;
            break;

         case IDCANCEL:
// KpMsgOut("DoEdit:IDCANCEL", IDI_ASTERISK, KP_MB_TESTI);
            if(!m_bOpenFileFl)
            {
               endfl=True;
               retc = KP_E_CANCEL;
            }
            break;

         } // switch(retp)

         break; // case WM_COMMAND:

      } // if(SUCCEEDED(retc)) switch(msg.message)

      if((!skip_fl) && SUCCEEDED(retc)) DispatchMessage(&msg);

   } while((!endfl) && SUCCEEDED(retc));

return(retc);
}


// ----------------------------------
HRESULT KpStEdiDlg::CloseWindow(void)
{
HRESULT retc=S_OK;

   if(m_hDialogWindow!=NULL)
   {
      if(!(::DestroyWindow(m_hDialogWindow)))
      {
//       retc=KpErrorProc.OutputErrorMessage(KP_E_SYSTEM_ERROR, GetLastError(), True, __FILE__, __LINE__, 0L, NULL);
      }
   }

   if(SUCCEEDED(retc)) retc=ClearControls();

return(retc);
}
