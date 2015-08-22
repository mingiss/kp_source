// -----------------------------------------
// kpstmsg.h
// programos paleidimo aplikaciju pranesimai
//

#ifndef kpstmsg_included
#define kpstmsg_included

// #define KPST_ARKIM
#define KPST_TEV

// arkim@tev.lt
// tech@tev.lt
// tev@tev.lt
// 8-5-2729805
// 8-5-2729318

// --------------------------------------- kpst messages
enum
{
KPST_MSG_PROD_REG_IX,               // "Programos registracija"
KPST_MSG_UNREG_IX,                  // "Registracijos naikinimas"
KPST_MSG_LIC_IX,                    // "Licencija"
KPST_MSG_REG_INFO_IX,               // "Kad programa veiktø, jà reikia uþregistruoti."
KPST_MSG_IVESK_LIC_IX,              // "Áveskite licencijos kodà, kurá gavote ásigydami produktà."
KPST_MSG_IVESK_LIC_1_IX,            // "Visà kodà galima kopijuoti á pirmà langelá."
KPST_MSG_REG_CARD_IX,               // "Já rasite registracijos kortelëje"
KPST_MSG_LIC_KOD_IX,                // "Licencijos kodas:"
KPST_MSG_BLOGAS_LIC_KODAS_IX,       // "Neteisingai ávestas licencijos kodas"
KPST_MSG_CHECK_CONN_IX,             // "Patikrinkite, ar kompiuteris prijungtas prie interneto"
KPST_MSG_CHECK_CONN_LOC_IX,         // "Patikrinkite, ar kompiuteris prijungtas prie tinklo"
KPST_MSG_REG_SUCC_IX,               // "Licencija uþregistruota sëkmingai"
KPST_MSG_ALLREADY_REG_IX,           // "Licencija jau uþregistruota"
KPST_MSG_REG_UNSUC_IX,              // "Internetu licencijos uþregistruoti nepavyko."
KPST_MSG_REG_UNSUC_0_IX,            // "Pabandykite narðykle atverti þemiau"
KPST_MSG_REG_UNSUC_1_IX,            // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius."
KPST_MSG_REG_UNSUC_LOC_IX,          // "Uþsiregistruoti nepavyko."
KPST_MSG_DIEG_KOD_IX,               // "Diegimo kodas:"

KPST_MSG_UNREG_INFO_IX,             // "Licencijos registracija naikinama prieð programà perkeliant á kità kompiuterá."
KPST_MSG_UNREG_IVESK_LIC_IX,        // KPST_MSG_IVESK_LIC

KPST_MSG_REG_PERSPEJ_IX,            // "Uþregistruota programa veiks tik ðiame kompiuteryje!"

KPST_MSG_BUT_REG_IX,                // "Kaip registruosite:"
KPST_MSG_BUT_UNREG_IX,              // "Kaip naikinsite:"

KPST_MSG_INTERNETU_IX,              // "Internetu"
KPST_MSG_TELEFONU_IX,               // "Telefonu"
KPST_MSG_CANCEL_REG_IX,             // "Atðaukti"
KPST_MSG_CANCEL_UNREG_IX,           // "Nenaikinti"

KPST_MSG_SIUSK_PASTU_IX,            // "Diegimo kodà galite iðsiøsti elektroniniu paðtu, adresu tech@tev.lt arba"
KPST_MSG_DARBO_LAIKAS_IX,           // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318"
KPST_MSG_DIKT_TELEF_IX,             // "padiktuoti operatoriui."

KPST_MSG_IVESK_RAKTA_IX,            // "Áveskite gautà atsakymà – diegimo raktà."
KPST_MSG_IVESK_RAKTA_1_IX,          // "Visà raktà galima kopijuoti á pirmà langelá."
KPST_MSG_DIEG_RAKTAS_IX,            // "Diegimo raktas:"
KPST_MSG_DIEG_RAKTAS_1_IX,          // "Diegimo raktas"
KPST_MSG_BLOGAS_DIEG_RAKTAS_IX,     // "Neteisingai ávestas diegimo raktas"
KPST_MSG_START_FROM_CD_IX,          // "Programà paleiskite ið kompaktinës plokðtelës"
KPST_MSG_BAD_CD_IX,                 // "Bloga kompaktinë plokðtelë"

KPST_MSG_REZ_NESUFORM_IX,           // "Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt"
KPST_MSG_REZ_NFOUND_1_IX,           // "Rezultatø rasti nepavyko.\n Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt "
KPST_MSG_REZ_NFOUND_2_IX,           // "Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator."
KPST_MSG_REZ_SUCCESS_IX,            // ". Rezultatai sëkmingai perkelti á "

KPST_MSG_REG_NOT_ADMIN_IX,          // "Norint uþregistruoti licencijà, reikia sistemos\n administratoriaus teisiø"
KPST_MSG_UNREG_NOT_ADMIN_IX,        // "Norëdami panaikinti produkto diegimà,\n uþsiregistruokite sistemos administratoriumi"
KPST_MSG_NOT_REG_IX,                // "Produkto licencija dar neuþregistruota"
KPST_MSG_INVALID_REG_IX,            // "Papildymo ir pagrindinio produkto licencijø kodai nesutampa. Pakartokite produkto diegimà."

KPST_MSG_UNREG_KOD_1_IX,            // "Iðmetimo kodas"
KPST_MSG_UNREG_KOD_IX,              // "Licencijos iðmetimo kodas:              \n"
KPST_MSG_ALLREADY_REMOVED_IX,       // "Produktas jau iðmestas"
KPST_MSG_UNREG_SUCC_IX,             // "Licencijos diegimas panaikintas sëkmingai"
KPST_MSG_UNREG_UNSUCC_IX,           // "Internetu registracijos panaikinti nepavyko."
KPST_MSG_UNREG_UNSUCC_1_IX,         // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

KPST_MSG_REG_NOT_YET_IX,            // "Programa dar neuþregistruota. Registracijos procedûrà turësite pakartoti paleidimo meniu komanda „Registracija”."

KPST_MSG_INI_NOT_ADMIN_IX,          // "Sistemos resursai nepasiekiami, uþsiregistruokite administratoriumi"

KPST_MSG_UNREG_PASTU_IX,            // "Iðmetimo kodà iðsiøskite elektroniniu paðtu, adresu tech@tev.lt arba"
KPST_MSG_UNREG_DARBO_LAIKAS_IX,     // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318"
KPST_MSG_UNREG_DIKT_TELEF_IX,       // "padiktuokite operatoriui."

KPST_MSG_UNREG_NEGALESIT_IX,        // "To nepadaræ, kitame kompiuteryje programos uþregistruoti negalësite!"

KPST_MSG_INSERT_FLOPPY_IX,          // "Ádëkite diskelá"
KPST_MSG_UNABLE_OPEN_REZFILE_IX,    // "Negaliu atverti rezultatø failo."
KPST_MSG_UNABLE_WRITE_REZFILE_IX,   // "Negaliu áraðyti á rezultatø failà."
KPST_MSG_UNABLE_CLOSE_REZFILE_IX,   // "Negaliu uþdaryti rezultatø failo."
KP_MSG_UNABLE_READ_WRITTEN_IX,      // "Negaliu perskaityti áraðyto failo."
KPST_MSG_COULDNT_WRITE_IX,          // "Duomenys neásiraðo."
KPST_MSG_REFUSE_RESULTS_IX,         // "Ar tikrai norite atsisakyti rezultatø?"
KPST_MSG_TEST_SUCC_IX,              // "Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     "

KPST_MSG_TEST_UNSUC_IX,             // "Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt"

KPST_MSG_INSERT_FLASH_IX,           // "Ákiðkite atmintukà su \""
KPST_MSG_INSERT_FLASH_1_IX,         // "\""

KPST_MSG_ENTER_PWD_IX,              // "Áveskite slaptaþodá:"
KPST_MSG_BAD_PWD_IX,                // "Slaptaþodis neteisingas"
KPST_MSG_ENTER_PUK_IX,              // "Áveskite atmintuko licencijos kodà:"
KPST_MSG_BAD_PUK_IX,                // "Neteisingas licencijos kodas"

KPST_MSG_OBJ_REG_IX,                // "Dokumento registracija"
KPST_MSG_OBJ_REG_INFO_IX,           // "Prieð naudojant dokumentà reikia uþregistruoti."
KPST_MSG_OBJ_UNREG_INFO_IX,         // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
KPST_MSG_OBJ_REG_PERSPEJ_IX,        // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

KPST_MSG_OBJ_REG_NOT_YET_IX,        // "Dokumento registracija atðaukta."
KPST_MSG_OBJ_UNREG_NEGALESIT_IX,    // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

KPST_MSG_BAD_FLASH_IX,              // "Ðis atnaujinimas skirtas atmintukui %s"

KPST_MSG_LICENCE_EXPIRED_IX,        // "Licencijos galiojimas baigësi"
KPST_MSG_REST_MONTHS_IX,            // "Licencijos galiojimas baigsis po %d mënesiø"
KPST_MSG_REST_LAST_MONTH_IX,        // "Licencijos galiojimas baigsis kità mënesá"
KPST_MSG_REST_DAYS_IX,              // "Licencijos galiojimas baigsis po %d dienø"
KPST_MSG_REST_DAY_IX,               // "Rytoj baigsis licencijos galiojimas"
KPST_MSG_REST_TODAY_IX,             // "Ðiandien baigiasi licencijos galiojimas"
KPST_MSG_TIME_CHEAT_IX,             // "Teisingai nustatykite sistemos laikrodá"

KPST_MSG_BAD_PRODVAR_IX,            // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

KPST_MSG_UPDATE_FINISHED_IX,        // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

KPST_MSG_SELDOWN_TITLE_IX,          // "Produkto komponentø parsisiøsdinimas: "
KPST_MSG_SELDOWN_PROMPT_IX,         // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
KPST_MSG_SELDOWN_NOMORE_PROMPT_IX,  // "Naujø serijos leidiniø daugiau netikrinti:"
KPST_MSG_SELDOWN_BUT_PROMPT_IX,     // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

KPST_MSG_SELUPD_TITLE_IX,           // "Produkto atnaujinimø parsisiøsdinimas")
KPST_MSG_SELUPD_PROMPT_IX,          // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
KPST_MSG_SELUPD_NOMORE_PROMPT_IX,   // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
KPST_MSG_SELUPD_BUT_PROMPT_IX,      // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

KPST_MSG_CLOSE_PROG_WND_IX,         // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

NumOfKpStMessages
};

#define NumOfKpStMessages_18 NumOfKpStMessages

extern const unsigned char *lpszaKpStMessages[NumOfKpStMessages][KpNumOfLangs];

// -----------------------------------------
#define KPST_MSG_PROD_REG              lpszaKpStMessages[KPST_MSG_PROD_REG_IX            ][iMsgLangOff] // "Programos registracija"
#define KPST_MSG_UNREG                 lpszaKpStMessages[KPST_MSG_UNREG_IX               ][iMsgLangOff] // "Registracijos naikinimas"
#define KPST_MSG_LIC                   lpszaKpStMessages[KPST_MSG_LIC_IX                 ][iMsgLangOff] // "Licencija"
#define KPST_MSG_REG_INFO              lpszaKpStMessages[KPST_MSG_REG_INFO_IX            ][iMsgLangOff] // "Kad programa veiktø, jà reikia uþregistruoti."
#define KPST_MSG_IVESK_LIC             lpszaKpStMessages[KPST_MSG_IVESK_LIC_IX           ][iMsgLangOff] // "Áveskite licencijos kodà, kurá gavote ásigydami produktà."
#define KPST_MSG_IVESK_LIC_1           lpszaKpStMessages[KPST_MSG_IVESK_LIC_1_IX         ][iMsgLangOff] // "Visà kodà galima kopijuoti á pirmà langelá."
#define KPST_MSG_REG_CARD              lpszaKpStMessages[KPST_MSG_REG_CARD_IX            ][iMsgLangOff] // "Já rasite registracijos kortelëje"
#define KPST_MSG_LIC_KOD               lpszaKpStMessages[KPST_MSG_LIC_KOD_IX             ][iMsgLangOff] // "Licencijos kodas:"
#define KPST_MSG_BLOGAS_LIC_KODAS      lpszaKpStMessages[KPST_MSG_BLOGAS_LIC_KODAS_IX    ][iMsgLangOff] // "Neteisingai ávestas licencijos kodas"
#define KPST_MSG_CHECK_CONN            lpszaKpStMessages[KPST_MSG_CHECK_CONN_IX          ][iMsgLangOff] // "Patikrinkite, ar kompiuteris prijungtas prie interneto"
#define KPST_MSG_CHECK_CONN_LOC        lpszaKpStMessages[KPST_MSG_CHECK_CONN_LOC_IX      ][iMsgLangOff] // "Patikrinkite, ar kompiuteris prijungtas prie tinklo"
#define KPST_MSG_REG_SUCC              lpszaKpStMessages[KPST_MSG_REG_SUCC_IX            ][iMsgLangOff] // "Licencija uþregistruota sëkmingai"
#define KPST_MSG_ALLREADY_REG          lpszaKpStMessages[KPST_MSG_ALLREADY_REG_IX        ][iMsgLangOff] // "Licencija jau uþregistruota"
#define KPST_MSG_REG_UNSUC             lpszaKpStMessages[KPST_MSG_REG_UNSUC_IX           ][iMsgLangOff] // "Internetu licencijos uþregistruoti nepavyko."
#define KPST_MSG_REG_UNSUC_0           lpszaKpStMessages[KPST_MSG_REG_UNSUC_0_IX         ][iMsgLangOff] // "Pabandykite narðykle atverti þemiau"
#define KPST_MSG_REG_UNSUC_1           lpszaKpStMessages[KPST_MSG_REG_UNSUC_1_IX         ][iMsgLangOff] // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius."
#define KPST_MSG_REG_UNSUC_LOC         lpszaKpStMessages[KPST_MSG_REG_UNSUC_LOC_IX       ][iMsgLangOff] // "Uþsiregistruoti nepavyko."
#define KPST_MSG_DIEG_KOD              lpszaKpStMessages[KPST_MSG_DIEG_KOD_IX            ][iMsgLangOff] // "Diegimo kodas:"

#define KPST_MSG_UNREG_INFO            lpszaKpStMessages[KPST_MSG_UNREG_INFO_IX          ][iMsgLangOff] // "Licencijos registracija naikinama prieð programà perkeliant á kità kompiuterá."
#define KPST_MSG_UNREG_IVESK_LIC       lpszaKpStMessages[KPST_MSG_UNREG_IVESK_LIC_IX     ][iMsgLangOff] // KPST_MSG_IVESK_LIC

#define KPST_MSG_REG_PERSPEJ           lpszaKpStMessages[KPST_MSG_REG_PERSPEJ_IX         ][iMsgLangOff] // "Uþregistruota programa veiks tik ðiame kompiuteryje!"

#define KPST_MSG_BUT_REG               lpszaKpStMessages[KPST_MSG_BUT_REG_IX             ][iMsgLangOff] // "Kaip registruosite:"
#define KPST_MSG_BUT_UNREG             lpszaKpStMessages[KPST_MSG_BUT_UNREG_IX           ][iMsgLangOff] // "Kaip naikinsite:"

#define KPST_MSG_INTERNETU             lpszaKpStMessages[KPST_MSG_INTERNETU_IX           ][iMsgLangOff] // "Internetu"
#define KPST_MSG_TELEFONU              lpszaKpStMessages[KPST_MSG_TELEFONU_IX            ][iMsgLangOff] // "Telefonu"
#define KPST_MSG_CANCEL_REG            lpszaKpStMessages[KPST_MSG_CANCEL_REG_IX          ][iMsgLangOff] // "Atðaukti"
#define KPST_MSG_CANCEL_UNREG          lpszaKpStMessages[KPST_MSG_CANCEL_UNREG_IX        ][iMsgLangOff] // "Nenaikinti"

#define KPST_MSG_SIUSK_PASTU           lpszaKpStMessages[KPST_MSG_SIUSK_PASTU_IX         ][iMsgLangOff] // "Diegimo kodà galite iðsiøsti elektroniniu paðtu, adresu tech@tev.lt arba"
#define KPST_MSG_DARBO_LAIKAS          lpszaKpStMessages[KPST_MSG_DARBO_LAIKAS_IX        ][iMsgLangOff] // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318"
#define KPST_MSG_DIKT_TELEF            lpszaKpStMessages[KPST_MSG_DIKT_TELEF_IX          ][iMsgLangOff] // "padiktuoti operatoriui."

#define KPST_MSG_IVESK_RAKTA           lpszaKpStMessages[KPST_MSG_IVESK_RAKTA_IX         ][iMsgLangOff] // "Áveskite gautà atsakymà – diegimo raktà."
#define KPST_MSG_IVESK_RAKTA_1         lpszaKpStMessages[KPST_MSG_IVESK_RAKTA_1_IX       ][iMsgLangOff] // "Visà raktà galima kopijuoti á pirmà langelá."
#define KPST_MSG_DIEG_RAKTAS           lpszaKpStMessages[KPST_MSG_DIEG_RAKTAS_IX         ][iMsgLangOff] // "Diegimo raktas:"
#define KPST_MSG_DIEG_RAKTAS_1         lpszaKpStMessages[KPST_MSG_DIEG_RAKTAS_1_IX       ][iMsgLangOff] // "Diegimo raktas"
#define KPST_MSG_BLOGAS_DIEG_RAKTAS    lpszaKpStMessages[KPST_MSG_BLOGAS_DIEG_RAKTAS_IX  ][iMsgLangOff] // "Neteisingai ávestas diegimo raktas"
#define KPST_MSG_START_FROM_CD         lpszaKpStMessages[KPST_MSG_START_FROM_CD_IX       ][iMsgLangOff] // "Programà paleiskite ið kompaktinës plokðtelës"
#define KPST_MSG_BAD_CD                lpszaKpStMessages[KPST_MSG_BAD_CD_IX              ][iMsgLangOff] // "Bloga kompaktinë plokðtelë"

#define KPST_MSG_REZ_NESUFORM          lpszaKpStMessages[KPST_MSG_REZ_NESUFORM_IX        ][iMsgLangOff] // "Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt"
#define KPST_MSG_REZ_NFOUND_1          lpszaKpStMessages[KPST_MSG_REZ_NFOUND_1_IX        ][iMsgLangOff] // "Rezultatø rasti nepavyko.\n Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt "
#define KPST_MSG_REZ_NFOUND_2          (const char *)lpszaKpStMessages[KPST_MSG_REZ_NFOUND_2_IX        ][iMsgLangOff] // "Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator."
#define KPST_MSG_REZ_SUCCESS           lpszaKpStMessages[KPST_MSG_REZ_SUCCESS_IX         ][iMsgLangOff] // ". Rezultatai sëkmingai perkelti á "

#define KPST_MSG_REG_NOT_ADMIN         lpszaKpStMessages[KPST_MSG_REG_NOT_ADMIN_IX       ][iMsgLangOff] // "Norint uþregistruoti licencijà, reikia sistemos\n administratoriaus teisiø"
#define KPST_MSG_UNREG_NOT_ADMIN       lpszaKpStMessages[KPST_MSG_UNREG_NOT_ADMIN_IX     ][iMsgLangOff] // "Norëdami panaikinti produkto diegimà,\n uþsiregistruokite sistemos administratoriumi"
#define KPST_MSG_NOT_REG               lpszaKpStMessages[KPST_MSG_NOT_REG_IX             ][iMsgLangOff] // "Produkto licencija dar neuþregistruota"
#define KPST_MSG_INVALID_REG           lpszaKpStMessages[KPST_MSG_INVALID_REG_IX         ][iMsgLangOff] // "Papildymo ir pagrindinio produkto licencijø kodai nesutampa. Pakartokite produkto diegimà."

#define KPST_MSG_UNREG_KOD_1           lpszaKpStMessages[KPST_MSG_UNREG_KOD_1_IX         ][iMsgLangOff] // "Iðmetimo kodas"
#define KPST_MSG_UNREG_KOD             lpszaKpStMessages[KPST_MSG_UNREG_KOD_IX           ][iMsgLangOff] // "Licencijos iðmetimo kodas:              \n"
#define KPST_MSG_ALLREADY_REMOVED      lpszaKpStMessages[KPST_MSG_ALLREADY_REMOVED_IX    ][iMsgLangOff] // "Produktas jau iðmestas"
#define KPST_MSG_UNREG_SUCC            lpszaKpStMessages[KPST_MSG_UNREG_SUCC_IX          ][iMsgLangOff] // "Licencijos diegimas panaikintas sëkmingai"
#define KPST_MSG_UNREG_UNSUCC          lpszaKpStMessages[KPST_MSG_UNREG_UNSUCC_IX        ][iMsgLangOff] // "Internetu registracijos panaikinti nepavyko."
#define KPST_MSG_UNREG_UNSUCC_1        lpszaKpStMessages[KPST_MSG_UNREG_UNSUCC_1_IX      ][iMsgLangOff] // "Pabandykite narðykle atverti þemiau esanèià nuorodà."
#define KPST_MSG_REG_NOT_YET           lpszaKpStMessages[KPST_MSG_REG_NOT_YET_IX         ][iMsgLangOff] // "Programa dar neuþregistruota. Registracijos procedûrà turësite pakartoti paleidimo meniu komanda „Registracija”."

#define KPST_MSG_INI_NOT_ADMIN         lpszaKpStMessages[KPST_MSG_INI_NOT_ADMIN_IX       ][iMsgLangOff] // "Sistemos resursai nepasiekiami, uþsiregistruokite administratoriumi"

#define KPST_MSG_UNREG_PASTU           lpszaKpStMessages[KPST_MSG_UNREG_PASTU_IX         ][iMsgLangOff] // "Iðmetimo kodà iðsiøskite elektroniniu paðtu, adresu tech@tev.lt arba"
#define KPST_MSG_UNREG_DARBO_LAIKAS    lpszaKpStMessages[KPST_MSG_UNREG_DARBO_LAIKAS_IX  ][iMsgLangOff] // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318"
#define KPST_MSG_UNREG_DIKT_TELEF      lpszaKpStMessages[KPST_MSG_UNREG_DIKT_TELEF_IX    ][iMsgLangOff] // "padiktuokite operatoriui."

#define KPST_MSG_UNREG_NEGALESIT       lpszaKpStMessages[KPST_MSG_UNREG_NEGALESIT_IX     ][iMsgLangOff] // "To nepadaræ, kitame kompiuteryje programos uþregistruoti negalësite!"

#define KPST_MSG_INSERT_FLOPPY         lpszaKpStMessages[KPST_MSG_INSERT_FLOPPY_IX       ][iMsgLangOff] // "Ádëkite diskelá"
#define KPST_MSG_UNABLE_OPEN_REZFILE   lpszaKpStMessages[KPST_MSG_UNABLE_OPEN_REZFILE_IX ][iMsgLangOff] // "Negaliu atverti rezultatø failo."
#define KPST_MSG_UNABLE_WRITE_REZFILE  lpszaKpStMessages[KPST_MSG_UNABLE_WRITE_REZFILE_IX][iMsgLangOff] // "Negaliu áraðyti á rezultatø failà."
#define KPST_MSG_UNABLE_CLOSE_REZFILE  lpszaKpStMessages[KPST_MSG_UNABLE_CLOSE_REZFILE_IX][iMsgLangOff] // "Negaliu uþdaryti rezultatø failo."
#define KP_MSG_UNABLE_READ_WRITTEN     lpszaKpStMessages[KP_MSG_UNABLE_READ_WRITTEN_IX   ][iMsgLangOff] // "Negaliu perskaityti áraðyto failo."
#define KPST_MSG_COULDNT_WRITE         lpszaKpStMessages[KPST_MSG_COULDNT_WRITE_IX       ][iMsgLangOff] // "Duomenys neásiraðo."
#define KPST_MSG_REFUSE_RESULTS        lpszaKpStMessages[KPST_MSG_REFUSE_RESULTS_IX      ][iMsgLangOff] // "Ar tikrai norite atsisakyti rezultatø?"
#define KPST_MSG_TEST_SUCC             lpszaKpStMessages[KPST_MSG_TEST_SUCC_IX           ][iMsgLangOff] // "Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     "

#define KPST_MSG_TEST_UNSUC            lpszaKpStMessages[KPST_MSG_TEST_UNSUC_IX          ][iMsgLangOff] // "Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt"

#define KPST_MSG_INSERT_FLASH          lpszaKpStMessages[KPST_MSG_INSERT_FLASH_IX        ][iMsgLangOff] // "Ákiðkite atmintukà su \""
#define KPST_MSG_INSERT_FLASH_1        lpszaKpStMessages[KPST_MSG_INSERT_FLASH_1_IX      ][iMsgLangOff] // "\""

#define KPST_MSG_ENTER_PWD             lpszaKpStMessages[KPST_MSG_ENTER_PWD_IX           ][iMsgLangOff] // "Áveskite slaptaþodá:"
#define KPST_MSG_BAD_PWD               lpszaKpStMessages[KPST_MSG_BAD_PWD_IX             ][iMsgLangOff] // "Slaptaþodis neteisingas"
#define KPST_MSG_ENTER_PUK             lpszaKpStMessages[KPST_MSG_ENTER_PUK_IX           ][iMsgLangOff] // "Áveskite atmintuko licencijos kodà:"
#define KPST_MSG_BAD_PUK               lpszaKpStMessages[KPST_MSG_BAD_PUK_IX             ][iMsgLangOff] // "Neteisingas licencijos kodas"

#define KPST_MSG_OBJ_REG               lpszaKpStMessages[KPST_MSG_OBJ_REG_IX             ][iMsgLangOff] // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO          lpszaKpStMessages[KPST_MSG_OBJ_REG_INFO_IX        ][iMsgLangOff] // "Prieð naudojant dokumentà reikia uþregistruoti."
#define KPST_MSG_OBJ_UNREG_INFO        lpszaKpStMessages[KPST_MSG_OBJ_UNREG_INFO_IX      ][iMsgLangOff] // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
#define KPST_MSG_OBJ_REG_PERSPEJ       lpszaKpStMessages[KPST_MSG_OBJ_REG_PERSPEJ_IX     ][iMsgLangOff] // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET       lpszaKpStMessages[KPST_MSG_OBJ_REG_NOT_YET_IX     ][iMsgLangOff] // "Dokumento registracija atðaukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT   lpszaKpStMessages[KPST_MSG_OBJ_UNREG_NEGALESIT_IX ][iMsgLangOff] // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

#define KPST_MSG_BAD_FLASH             (const char *)lpszaKpStMessages[KPST_MSG_BAD_FLASH_IX           ][iMsgLangOff] // "Ðis atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED       (const char *)lpszaKpStMessages[KPST_MSG_LICENCE_EXPIRED_IX     ][iMsgLangOff] // "Licencijos galiojimas baigësi"
#define KPST_MSG_REST_MONTHS           (const char *)lpszaKpStMessages[KPST_MSG_REST_MONTHS_IX         ][iMsgLangOff] // "Licencijos galiojimas baigsis po %d mënesiø"
#define KPST_MSG_REST_LAST_MONTH       (const char *)lpszaKpStMessages[KPST_MSG_REST_LAST_MONTH_IX     ][iMsgLangOff] // "Licencijos galiojimas baigsis kità mënesá"
#define KPST_MSG_REST_DAYS             (const char *)lpszaKpStMessages[KPST_MSG_REST_DAYS_IX           ][iMsgLangOff] // "Licencijos galiojimas baigsis po %d dienø"
#define KPST_MSG_REST_DAY              (const char *)lpszaKpStMessages[KPST_MSG_REST_DAY_IX            ][iMsgLangOff] // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY            (const char *)lpszaKpStMessages[KPST_MSG_REST_TODAY_IX          ][iMsgLangOff] // "Ðiandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT            lpszaKpStMessages[KPST_MSG_TIME_CHEAT_IX          ][iMsgLangOff] // "Teisingai nustatykite sistemos laikrodá"

#define KPST_MSG_BAD_PRODVAR           lpszaKpStMessages[KPST_MSG_BAD_PRODVAR_IX         ][iMsgLangOff] // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

#define KPST_MSG_UPDATE_FINISHED       lpszaKpStMessages[KPST_MSG_UPDATE_FINISHED_IX     ][iMsgLangOff] // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

#define KPST_MSG_SELDOWN_TITLE         lpszaKpStMessages[KPST_MSG_SELDOWN_TITLE_IX       ][iMsgLangOff] // "Produkto komponentø parsisiøsdinimas: "
#define KPST_MSG_SELDOWN_PROMPT        lpszaKpStMessages[KPST_MSG_SELDOWN_PROMPT_IX      ][iMsgLangOff] // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT lpszaKpStMessages[KPST_MSG_SELDOWN_NOMORE_PROMPT_IX][iMsgLangOff] // "Naujø serijos leidiniø daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT    lpszaKpStMessages[KPST_MSG_SELDOWN_BUT_PROMPT_IX  ][iMsgLangOff] // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE          lpszaKpStMessages[KPST_MSG_SELUPD_TITLE_IX        ][iMsgLangOff] // "Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT         lpszaKpStMessages[KPST_MSG_SELUPD_PROMPT_IX       ][iMsgLangOff] // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT  lpszaKpStMessages[KPST_MSG_SELUPD_NOMORE_PROMPT_IX][iMsgLangOff] // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT     lpszaKpStMessages[KPST_MSG_SELUPD_BUT_PROMPT_IX   ][iMsgLangOff] // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

#define KPST_MSG_CLOSE_PROG_WND        (const char *)lpszaKpStMessages[KPST_MSG_CLOSE_PROG_WND_IX      ][iMsgLangOff] // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

// -----------------------------------------------
#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define KPST_MSG_PROD_REG_EN        ((const unsigned char *)"") // "Program registration")
#define KPST_MSG_UNREG_EN           ((const unsigned char *)"") // "Registration cancellation")
#define KPST_MSG_LIC_EN             ((const unsigned char *)"") // "Licence")
#define KPST_MSG_REG_INFO_EN        ((const unsigned char *)"") // "To keep program running, licence should be registered.")
#define KPST_MSG_IVESK_LIC_EN       ((const unsigned char *)"") // "Enter licence code acquired together with the product.")
#define KPST_MSG_IVESK_LIC_1_EN     ((const unsigned char *)"") // "Visà kodà galima kopijuoti á pirmà langelá."
#define KPST_MSG_REG_CARD_EN        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_EN         ((const unsigned char *)"") // "Licence code:")
#define KPST_MSG_BLOGAS_LIC_KODAS_EN   ((const unsigned char *)"") // "Invalid licence code")
#define KPST_MSG_CHECK_CONN_EN      ((const unsigned char *)"") // "Check your computer Internet connection")
#define KPST_MSG_CHECK_CONN_LOC_EN  ((const unsigned char *)"") // "Check your computer network connection")
#define KPST_MSG_REG_SUCC_EN        ((const unsigned char *)"") // "Licence registered successfully")
#define KPST_MSG_ALLREADY_REG_EN    ((const unsigned char *)"") // "Licence already registered")
#define KPST_MSG_REG_UNSUC_EN       ((const unsigned char *)"") // "Unsuccessful licence registration by Internet.")
#define KPST_MSG_REG_UNSUC_0_EN     ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_EN     ((const unsigned char *)"") // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_EN   ((const unsigned char *)"") // "Registration unsuccessful.")
#define KPST_MSG_DIEG_KOD_EN        ((const unsigned char *)"") // "Installation code:")

#define KPST_MSG_UNREG_INFO_EN      ((const unsigned char *)"") // "Licence registration should be cancelled before moving the program to another computer.")
#define KPST_MSG_UNREG_IVESK_LIC_EN KPST_MSG_IVESK_LIC_EN

#define KPST_MSG_REG_PERSPEJ_EN     ((const unsigned char *)"") // "Registered program will run on this computer only!")

#define KPST_MSG_BUT_REG_EN         ((const unsigned char *)"") // "How would you register:")
#define KPST_MSG_BUT_UNREG_EN       ((const unsigned char *)"") // "How would you cancel registration:")

#define KPST_MSG_INTERNETU_EN       ((const unsigned char *)"") // "By Internet")
#define KPST_MSG_TELEFONU_EN        ((const unsigned char *)"") // "By phone")
#define KPST_MSG_CANCEL_REG_EN      ((const unsigned char *)"") // "Cancel")
#define KPST_MSG_CANCEL_UNREG_EN    ((const unsigned char *)"") // "Do not cancel")

#define KPST_MSG_SIUSK_PASTU_EN     ((const unsigned char *)"") // "Installation code should be sent by an e-mail, address tech@tev.lt or told")
#define KPST_MSG_DARBO_LAIKAS_EN    ((const unsigned char *)"") // "to the operator at working hours from 9 to 16 EET by phone, number")
#define KPST_MSG_DIKT_TELEF_EN      ((const unsigned char *)"") // "+370-5-2729318.")

#define KPST_MSG_IVESK_RAKTA_EN     ((const unsigned char *)"") // "Enter received answer - installation key.")
#define KPST_MSG_IVESK_RAKTA_1_EN   ((const unsigned char *)"") // "Visà raktà galima kopijuoti á pirmà langelá."
#define KPST_MSG_DIEG_RAKTAS_EN     ((const unsigned char *)"") // "Installation key:")
#define KPST_MSG_DIEG_RAKTAS_1_EN   ((const unsigned char *)"") // "Installation key")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_EN ((const unsigned char *)"") // "Invalid installation key")
#define KPST_MSG_START_FROM_CD_EN   ((const unsigned char *)"") // "Run the program directly from CD")
#define KPST_MSG_BAD_CD_EN          ((const unsigned char *)"") // "Invalid CD")

#define KPST_MSG_REZ_NESUFORM_EN    ((const unsigned char *)"") // "Results were not generated.\nAsk for the technical support by e-mail, address tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_EN    ((const unsigned char *)"") // "Results were not found.\nAsk for the technical support by e-mail, address tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_2_EN    ((const unsigned char *)"") // "Results were not found.\nYou are %s, OS %s.\nTry login to the privileged user.")
#define KPST_MSG_REZ_SUCCESS_EN     ((const unsigned char *)"") // ". Results were successfully moved to ")

#define KPST_MSG_REG_NOT_ADMIN_EN   ((const unsigned char *)"") // "Licence registration requires rights of privileged user ")
#define KPST_MSG_UNREG_NOT_ADMIN_EN ((const unsigned char *)"") // "Licence cancellation requires\nrights of privileged user")
#define KPST_MSG_NOT_REG_EN         ((const unsigned char *)"") // "Product licence not yet registered")
#define KPST_MSG_INVALID_REG_EN     ((const unsigned char *)"") // "Licence codes of the update and the main product are different. Repeat installation of the product.")

#define KPST_MSG_UNREG_KOD_1_EN     ((const unsigned char *)"") // "Cancellation code")
#define KPST_MSG_UNREG_KOD_EN       ((const unsigned char *)"") // "Licence cancellation code:              \n")
#define KPST_MSG_ALLREADY_REMOVED_EN   ((const unsigned char *)"") // "Product already removed")
#define KPST_MSG_UNREG_SUCC_EN      ((const unsigned char *)"") // "Licence registration cancelled successfully")
#define KPST_MSG_UNREG_UNSUCC_EN    ((const unsigned char *)"") // "Unsuccessful licence cancellation by Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_EN  ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

#define KPST_MSG_REG_NOT_YET_EN     ((const unsigned char *)"") // "Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command “Registration”.")

#define KPST_MSG_INI_NOT_ADMIN_EN   ((const unsigned char *)"") // "System resources inaccessible, login as privileged user")

#define KPST_MSG_UNREG_PASTU_EN     ((const unsigned char *)"") // "Cancellation code should be sent by e-mail, address tech@tev.lt or told")
#define KPST_MSG_UNREG_DARBO_LAIKAS_EN ((const unsigned char *)"") // "to the operator at working hours from 9 to 16 EET by phone, number")
#define KPST_MSG_UNREG_DIKT_TELEF_EN   ((const unsigned char *)"") // "+370-5-2729318.")

#define KPST_MSG_UNREG_NEGALESIT_EN /* KPST_MSG_UNREG_TELEF_EN */ ((const unsigned char *)"") // "Without doing it you will be unable to run the program on another computer!")

#define KPST_MSG_INSERT_FLOPPY_EN   ((const unsigned char *)"") // "Put the floppy disk")
#define KPST_MSG_UNABLE_OPEN_REZFILE_EN   ((const unsigned char *)"") // "Result file could not be opened.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_EN  ((const unsigned char *)"") // "Result file could not be written.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_EN  ((const unsigned char *)"") // "Result file could not be closed.")
#define KP_MSG_UNABLE_READ_WRITTEN_EN     ((const unsigned char *)"") // "Written file could not be read.")
#define KPST_MSG_COULDNT_WRITE_EN   ((const unsigned char *)"") // "Data could not be written.")
#define KPST_MSG_REFUSE_RESULTS_EN  ((const unsigned char *)"") // "Are you sure you want to discard results?")
#define KPST_MSG_TEST_SUCC_EN       ((const unsigned char *)"") // "Software of the test does work on this computer properly")

#define KPST_MSG_TEST_UNSUC_EN      ((const unsigned char *)"") // "Results were not generated.\nPlease pack files of the folder c:\\arkim\\rezultatai to the archive and send it by e-mail, address tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_EN    ((const unsigned char *)"") // "Put the USB flash drive with “")
#define KPST_MSG_INSERT_FLASH_1_EN  ((const unsigned char *)"") // "”")

#define KPST_MSG_ENTER_PWD_EN       ((const unsigned char *)"") // "Enter the password:")
#define KPST_MSG_BAD_PWD_EN         ((const unsigned char *)"") // "Password incorrect")
#define KPST_MSG_ENTER_PUK_EN       ((const unsigned char *)"") // "Enter the USB flash drive licence code:")
#define KPST_MSG_BAD_PUK_EN         ((const unsigned char *)"") // "Licence code invalid")

#define KPST_MSG_OBJ_REG_EN         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_EN    ((const unsigned char *)"") // "Prieð naudojant dokumentà reikia uþregistruoti."
#define KPST_MSG_OBJ_UNREG_INFO_EN  ((const unsigned char *)"") // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
#define KPST_MSG_OBJ_REG_PERSPEJ_EN ((const unsigned char *)"") // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_EN     ((const unsigned char *)"") // "Dokumento registracija atðaukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_EN ((const unsigned char *)"") // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

#define KPST_MSG_BAD_FLASH_EN       ((const unsigned char *)"") // "Ðis atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_EN ((const unsigned char *)"") // "Licencijos galiojimas baigësi"
#define KPST_MSG_REST_MONTHS_EN     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d mënesiø"
#define KPST_MSG_REST_LAST_MONTH_EN ((const unsigned char *)"") // "Licencijos galiojimas baigsis kità mënesá"
#define KPST_MSG_REST_DAYS_EN       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dienø"
#define KPST_MSG_REST_DAY_EN        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_EN      ((const unsigned char *)"") // "Ðiandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_EN      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrodá"

#define KPST_MSG_BAD_PRODVAR_EN     ((const unsigned char *)"") // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

#define KPST_MSG_UPDATE_FINISHED_EN ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

#define KPST_MSG_SELDOWN_TITLE_EN   ((const unsigned char *)"") // "Produkto komponentø parsisiøsdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_EN  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_EN ((const unsigned char *)"") // "Naujø serijos leidiniø daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_EN ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE_EN    ((const unsigned char *)"") // "Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_EN   ((const unsigned char *)"") // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_EN ((const unsigned char *)"") // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_EN ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

#define KPST_MSG_CLOSE_PROG_WND_EN  ((const unsigned char *)"") // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

#endif // #if ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

// -----------------------------------------------
#if (((MsgLang) != KpLangSel_p) && ((MsgLang) != KpLangLt_p))

#define KPST_MSG_PROD_REG_LT        ((const unsigned char *)"") // "Programos registracija")
#define KPST_MSG_UNREG_LT           ((const unsigned char *)"") // "Registracijos naikinimas")
#define KPST_MSG_LIC_LT             ((const unsigned char *)"") // "Licencija")
#define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"") // "Kad programa veiktø, jà reikia uþregistruoti.")
#define KPST_MSG_IVESK_LIC_LT       ((const unsigned char *)"") // "Áveskite licencijos kodà, kurá gavote ásigydami produktà.")
#define KPST_MSG_IVESK_LIC_1_LT     ((const unsigned char *)"") // "Visà kodà galima kopijuoti á pirmà langelá."
#define KPST_MSG_REG_CARD_LT        ((const unsigned char *)"") // "")  // "Já rasite registracijos kortelëje"
#define KPST_MSG_LIC_KOD_LT         ((const unsigned char *)"") // "Licencijos kodas:")
#define KPST_MSG_BLOGAS_LIC_KODAS_LT   ((const unsigned char *)"") // "Neteisingai ávestas licencijos kodas")
#define KPST_MSG_CHECK_CONN_LT      ((const unsigned char *)"") // "Patikrinkite, ar kompiuteris prijungtas prie interneto")
#define KPST_MSG_CHECK_CONN_LOC_LT  ((const unsigned char *)"") // "Patikrinkite, ar kompiuteris prijungtas prie tinklo")
#define KPST_MSG_REG_SUCC_LT        ((const unsigned char *)"") // "Licencija uþregistruota sëkmingai")
#define KPST_MSG_ALLREADY_REG_LT    ((const unsigned char *)"") // "Licencija jau uþregistruota")
#define KPST_MSG_REG_UNSUC_LT       ((const unsigned char *)"") // "Internetu licencijos uþregistruoti nepavyko.")
#define KPST_MSG_REG_UNSUC_0_LT     ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_LT     ((const unsigned char *)"") // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"") // "Uþsiregistruoti nepavyko.") // "Licencijos uþregistruoti nepavyko.")
#define KPST_MSG_DIEG_KOD_LT        ((const unsigned char *)"") // "Diegimo kodas:")

#define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"") // "Licencijos registracija naikinama prieð programà perkeliant á kità kompiuterá.")
#define KPST_MSG_UNREG_IVESK_LIC_LT KPST_MSG_IVESK_LIC_LT

#define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"") // "Uþregistruota programa veiks tik ðiame kompiuteryje!")

#define KPST_MSG_BUT_REG_LT         ((const unsigned char *)"") // "Kaip registruosite:")
#define KPST_MSG_BUT_UNREG_LT       ((const unsigned char *)"") // "Kaip naikinsite:")

#define KPST_MSG_INTERNETU_LT       ((const unsigned char *)"") // "Internetu")
#define KPST_MSG_TELEFONU_LT        ((const unsigned char *)"") // "Telefonu")
#define KPST_MSG_CANCEL_REG_LT      ((const unsigned char *)"") // "Atðaukti") // "Neregistruoti")
#define KPST_MSG_CANCEL_UNREG_LT    ((const unsigned char *)"") // "Nenaikinti")

#define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"") // "Diegimo kodà galite iðsiøsti elektroniniu paðtu, adresu tech@tev.lt arba")
#define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"") // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_LT      ((const unsigned char *)"") // "padiktuoti operatoriui.")

#define KPST_MSG_IVESK_RAKTA_LT     ((const unsigned char *)"") // "Áveskite gautà atsakymà – diegimo raktà.")
#define KPST_MSG_IVESK_RAKTA_1_LT   ((const unsigned char *)"") // "Visà raktà galima kopijuoti á pirmà langelá."
#define KPST_MSG_DIEG_RAKTAS_LT     ((const unsigned char *)"") // "Diegimo raktas:")
#define KPST_MSG_DIEG_RAKTAS_1_LT   ((const unsigned char *)"") // "Diegimo raktas")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_LT ((const unsigned char *)"") // "Neteisingai ávestas diegimo raktas")
#define KPST_MSG_START_FROM_CD_LT   ((const unsigned char *)"") // "Programà paleiskite ið kompaktinës plokðtelës") // ((const unsigned char *)"Programà paleiskite ið kompaktinio disko")
#define KPST_MSG_BAD_CD_LT          ((const unsigned char *)"") // "Bloga kompaktinë plokðtelë") // ((const unsigned char *)"Blogas kompaktinis diskas")

#define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"") // "Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"") // "Rezultatø rasti nepavyko.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_LT    ((const unsigned char *)"") // "Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\nPabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_LT     ((const unsigned char *)"") // ". Rezultatai sëkmingai perkelti á ")

#define KPST_MSG_REG_NOT_ADMIN_LT   ((const unsigned char *)"") // "Norint uþregistruoti licencijà, reikia sistemos\nadministratoriaus teisiø")
#define KPST_MSG_UNREG_NOT_ADMIN_LT ((const unsigned char *)"") // "Norëdami panaikinti produkto diegimà,\nuþsiregistruokite sistemos administratoriumi")
#define KPST_MSG_NOT_REG_LT         ((const unsigned char *)"") // "Produkto licencija dar neuþregistruota")
#define KPST_MSG_INVALID_REG_LT     ((const unsigned char *)"") // "Papildymo ir pagrindinio produkto licencijø kodai nesutampa. Pakartokite produkto diegimà.")

#define KPST_MSG_UNREG_KOD_1_LT     ((const unsigned char *)"") // "Iðmetimo kodas")
#define KPST_MSG_UNREG_KOD_LT       ((const unsigned char *)"") // "Licencijos iðmetimo kodas:              \n")
#define KPST_MSG_ALLREADY_REMOVED_LT   ((const unsigned char *)"") // "Produktas jau iðmestas")
#define KPST_MSG_UNREG_SUCC_LT      ((const unsigned char *)"") // "Licencijos diegimas panaikintas sëkmingai")
#define KPST_MSG_UNREG_UNSUCC_LT    ((const unsigned char *)"") // "Internetu registracijos panaikinti nepavyko.")
#define KPST_MSG_UNREG_UNSUCC_1_LT  ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

#define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"") // "Programa dar neuþregistruota. Registracijos procedûrà turësite pakartoti paleidimo meniu komanda „Registracija”.")

#define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"") // "Sistemos resursai nepasiekiami, uþsiregistruokite administratoriumi") // "Produkto diegimui reikia sistemos administratoriaus teisiø"

#define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"") // "Iðmetimo kodà iðsiøskite elektroniniu paðtu, adresu tech@tev.lt arba")
#define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"") // "darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_LT   ((const unsigned char *)"") // "padiktuokite operatoriui.")

#define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"") // "To nepadaræ, kitame kompiuteryje programos uþregistruoti negalësite!")

#define KPST_MSG_INSERT_FLOPPY_LT   ((const unsigned char *)"") // "Ádëkite diskelá")
#define KPST_MSG_UNABLE_OPEN_REZFILE_LT   ((const unsigned char *)"") // "Negaliu atverti rezultatø failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_LT  ((const unsigned char *)"") // "Negaliu áraðyti á rezultatø failà.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_LT  ((const unsigned char *)"") // "Negaliu uþdaryti rezultatø failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_LT     ((const unsigned char *)"") // "Negaliu perskaityti áraðyto failo.")
#define KPST_MSG_COULDNT_WRITE_LT   ((const unsigned char *)"") // "Duomenys neásiraðo.")
#define KPST_MSG_REFUSE_RESULTS_LT  ((const unsigned char *)"") // "Ar tikrai norite atsisakyti rezultatø?")
#define KPST_MSG_TEST_SUCC_LT       ((const unsigned char *)"") // "Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     ") // "Ðis kompiuteris parengtas darbui su programine priemone Acrobat Reader CE" // "Duomenø surinkimo testas baigësi sëkmingai"

#define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"") // "Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà aplanko c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_LT    ((const unsigned char *)"") // "Ákiðkite atmintukà su „")
#define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"") // "“")

#define KPST_MSG_ENTER_PWD_LT       ((const unsigned char *)"") // "Áveskite slaptaþodá:")
#define KPST_MSG_BAD_PWD_LT         ((const unsigned char *)"") // "Slaptaþodis neteisingas")
#define KPST_MSG_ENTER_PUK_LT       ((const unsigned char *)"") // "Áveskite atmintuko licencijos kodà:")
#define KPST_MSG_BAD_PUK_LT         ((const unsigned char *)"") // "Neteisingas licencijos kodas")

#define KPST_MSG_OBJ_REG_LT         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_LT    ((const unsigned char *)"") // "Prieð naudojant dokumentà reikia uþregistruoti."
#define KPST_MSG_OBJ_UNREG_INFO_LT  ((const unsigned char *)"") // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
#define KPST_MSG_OBJ_REG_PERSPEJ_LT ((const unsigned char *)"") // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_LT     ((const unsigned char *)"") // "Dokumento registracija atðaukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_LT ((const unsigned char *)"") // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

#define KPST_MSG_BAD_FLASH_LT       ((const unsigned char *)"") // "Ðis atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_LT ((const unsigned char *)"") // "Licencijos galiojimas baigësi"
#define KPST_MSG_REST_MONTHS_LT     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d mënesiø"
#define KPST_MSG_REST_LAST_MONTH_LT ((const unsigned char *)"") // "Licencijos galiojimas baigsis kità mënesá"
#define KPST_MSG_REST_DAYS_LT       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dienø"
#define KPST_MSG_REST_DAY_LT        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_LT      ((const unsigned char *)"") // "Ðiandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_LT      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrodá"

#define KPST_MSG_BAD_PRODVAR_LT     ((const unsigned char *)"") // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

#define KPST_MSG_UPDATE_FINISHED_LT ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

#define KPST_MSG_SELDOWN_TITLE_LT   ((const unsigned char *)"") // "Produkto komponentø parsisiøsdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_LT  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_LT ((const unsigned char *)"") // "Naujø serijos leidiniø daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_LT ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE_LT    ((const unsigned char *)"") // "Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_LT   ((const unsigned char *)"") // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_LT ((const unsigned char *)"") // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_LT ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

#define KPST_MSG_CLOSE_PROG_WND_LT  ((const unsigned char *)"") // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

// -----------------------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define KPST_MSG_PROD_REG_PL_1250        ((const unsigned char *)"") // "Rejestracja programu")
#define KPST_MSG_UNREG_PL_1250           ((const unsigned char *)"") // "Odwo³anie licencji")
#define KPST_MSG_LIC_PL_1250             ((const unsigned char *)"") // "Licencja")
#define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"") // "By uruchomiæ program, wymagana jest rejestracja.")
#define KPST_MSG_IVESK_LIC_PL_1250       ((const unsigned char *)"") // "WprowadŸ kod licencji, który otrzyma³eœ nabywaj¹c produkt.")
#define KPST_MSG_IVESK_LIC_1_PL_1250     ((const unsigned char *)"") // "Visà kodà galima kopijuoti á pirmà langelá."
#define KPST_MSG_REG_CARD_PL_1250        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_PL_1250         ((const unsigned char *)"") // "Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1250   ((const unsigned char *)"") // "B³êdnie wprowadzono kod licencji")

#define KPST_MSG_CHECK_CONN_PL_1250      ((const unsigned char *)"") // "SprawdŸ, czy komputer jest pod³¹czony do Internetu")
#define KPST_MSG_CHECK_CONN_LOC_PL_1250  ((const unsigned char *)"") // "SprawdŸ, czy komputer jest pod³¹czony do sieci")

#define KPST_MSG_REG_SUCC_PL_1250        ((const unsigned char *)"") // "Licencja zosta³a zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1250    ((const unsigned char *)"") // "Licencja ju¿ jest zarejestrowana")
#define KPST_MSG_REG_UNSUC_PL_1250       ((const unsigned char *)"") // "Licencji nie uda³o siê zarejestrowaæ przez Internet.")
#define KPST_MSG_REG_UNSUC_0_PL_1250     ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_PL_1250     ((const unsigned char *)"") // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1250   ((const unsigned char *)"") // "Nieudana rejestracja.")
#define KPST_MSG_DIEG_KOD_PL_1250        ((const unsigned char *)"") // "Kod instalacji:")

#define KPST_MSG_UNREG_INFO_PL_1250      ((const unsigned char *)"") // "Przed przeniesieniem programu na inny komputer licencja powinna byæ usuniêta.")
#define KPST_MSG_UNREG_IVESK_LIC_PL_1250 KPST_MSG_IVESK_LIC_PL_1250

#define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"") // "Zarejestrowany program bêdzie dzia³a³ tylko na tym komputerze!")

#define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"") // "W jaki sposób zarejestrujesz program:")
#define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"") // "W jaki sposób usuniesz rejestracjê programu:")

#define KPST_MSG_INTERNETU_PL_1250       ((const unsigned char *)"") // "Przez Internet")
#define KPST_MSG_TELEFONU_PL_1250        ((const unsigned char *)"") // "Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1250      ((const unsigned char *)"") // "Odwo³aj")
#define KPST_MSG_CANCEL_UNREG_PL_1250    ((const unsigned char *)"") // "Nie usuwaj")

#define KPST_MSG_SIUSK_PASTU_PL_1250     ((const unsigned char *)"") // "Kod instalacji mo¿esz wys³aæ poczt¹ elektroniczn¹ na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1250    ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoni¹c pod nr. tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1250      ((const unsigned char *)"") // "podyktowaæ go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1250     ((const unsigned char *)"") // "WprowadŸ otrzyman¹ odpowiedŸ - klucz instalacji.")
#define KPST_MSG_IVESK_RAKTA_1_PL_1250   ((const unsigned char *)"") // "Visà raktà galima kopijuoti á pirmà langelá."
#define KPST_MSG_DIEG_RAKTAS_PL_1250     ((const unsigned char *)"") // "Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1250   ((const unsigned char *)"") // "Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1250 ((const unsigned char *)"") // "B³êdnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1250   ((const unsigned char *)"") // "Wywo³aj program z p³yty CD")
#define KPST_MSG_BAD_CD_PL_1250          ((const unsigned char *)"") // "Wadliwa pl³yta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1250    ((const unsigned char *)"") // "Rezultatai nesuformuoti.\nD?l technin?s pagalbos kreipkit?s elektroniniu paštu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1250    ((const unsigned char *)"") // "Rezultat? rasti nepavyko.\n D?l technin?s pagalbos kreipkit?s elektroniniu paštu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1250    ((const unsigned char *)"") // "Rezultat? rasti nepavyko.\nJ?s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1250     ((const unsigned char *)"") // ". Rezultatai s?kmingai perkelti ? ")

#define KPST_MSG_REG_NOT_ADMIN_PL_1250   ((const unsigned char *)"") // "Dla rejestracji licencji powinieneœ\n zalogowaæ siê do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1250 ((const unsigned char *)"") // "Dla usuniêcia instalacji produktu powinieneœ\n zalogowaæ siê do systemu jako administrator")

#define KPST_MSG_NOT_REG_PL_1250         ((const unsigned char *)"") // "Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_INVALID_REG_PL_1250     ((const unsigned char *)"") // "Kod uaktualnienia i podstawowego produktu nie s¹ zgodne. Zainstaluj produkt ponownie.")

#define KPST_MSG_UNREG_KOD_1_PL_1250     ((const unsigned char *)"") // "Kod usuniêcia")
#define KPST_MSG_UNREG_KOD_PL_1250       ((const unsigned char *)"") // "Kod usuniêcia licencji:              \n")
#define KPST_MSG_ALLREADY_REMOVED_PL_1250   ((const unsigned char *)"") // "Produkt ju¿ usuniêty")
#define KPST_MSG_UNREG_SUCC_PL_1250      ((const unsigned char *)"") // "Licencja zosta³a usuniêta")
#define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"") // "Nie uda³o siê usun¹æ rejestracji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_PL_1250  ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

#define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"") // "Program jeszcze nie by³ zarejestrowany. Ponów rejestracjê podczac wywo³ywania programu poprzez menu „Rejestracja”.")
#define KPST_MSG_INI_NOT_ADMIN_PL_1250   ((const unsigned char *)"") // "Zasoby systemu nie s¹ dostêpne. Zaloguj siê do systemu jako administrator")

#define KPST_MSG_UNREG_PASTU_PL_1250     ((const unsigned char *)"") // "Kod usuniêcia mo¿esz wys³aæ poczt¹ elektronow¹ na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1250 ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoni¹c pod nr. tel. 8-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1250   ((const unsigned char *)"") // "i podyktowaæ dla operatora.")

#define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"") // "Nie wykonuj¹c tej czynnoœci, nie bêdziesz móg³ zarejestrowaæ programu na innym komputerze!")
#define KPST_MSG_INSERT_FLOPPY_PL_1250   ((const unsigned char *)"") // "?d?kite diskel?")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1250   ((const unsigned char *)"") // "Negaliu atverti rezultat? failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1250  ((const unsigned char *)"") // "Negaliu ?rašyti ? rezultat? fail¹.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1250  ((const unsigned char *)"") // "Negaliu uždaryti rezultat? failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1250     ((const unsigned char *)"") // "Negaliu perskaityti ?rašyto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1250   ((const unsigned char *)"") // "Duomenys ne?sirašo.")
#define KPST_MSG_REFUSE_RESULTS_PL_1250  ((const unsigned char *)"") // "Ar tikrai norite atsisakyti rezultat??")
#define KPST_MSG_TEST_SUCC_PL_1250       ((const unsigned char *)"") // "Konkurso programin? ?ranga šiame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1250      ((const unsigned char *)"") // "Rezultat? suformuoti nepavyko.\nPrašome suarchyvuot¹ katalogo c:\\arkim\\rezultatai turin? atsi?sti elektroniniu paštu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1250    ((const unsigned char *)"") // "Pod³acz USB noœnik z \"")

#define KPST_MSG_INSERT_FLASH_1_PL_1250  ((const unsigned char *)"") // "\"")

#define KPST_MSG_ENTER_PWD_PL_1250       ((const unsigned char *)"") // "WprowadŸ has³o:")
#define KPST_MSG_BAD_PWD_PL_1250         ((const unsigned char *)"") // "B³êdne has³o")

#define KPST_MSG_ENTER_PUK_PL_1250       ((const unsigned char *)"") // "WprowadŸ kod licencji noœnika USB:")
#define KPST_MSG_BAD_PUK_PL_1250         ((const unsigned char *)"") // "Niepoprawny kod licencji")

#define KPST_MSG_OBJ_REG_PL_1250         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_PL_1250    ((const unsigned char *)"") // "Prieð naudojant dokumentà reikia uþregistruoti."
#define KPST_MSG_OBJ_UNREG_INFO_PL_1250  ((const unsigned char *)"") // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1250 ((const unsigned char *)"") // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_PL_1250     ((const unsigned char *)"") // "Dokumento registracija atðaukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250 ((const unsigned char *)"") // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

#define KPST_MSG_BAD_FLASH_PL_1250       ((const unsigned char *)"") // "Ðis atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_PL_1250 ((const unsigned char *)"") // "Licencijos galiojimas baigësi"
#define KPST_MSG_REST_MONTHS_PL_1250     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d mënesiø"
#define KPST_MSG_REST_LAST_MONTH_PL_1250 ((const unsigned char *)"") // "Licencijos galiojimas baigsis kità mënesá"
#define KPST_MSG_REST_DAYS_PL_1250       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dienø"
#define KPST_MSG_REST_DAY_PL_1250        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_PL_1250      ((const unsigned char *)"") // "Ðiandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_PL_1250      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrodá"

#define KPST_MSG_BAD_PRODVAR_PL_1250     ((const unsigned char *)"") // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

#define KPST_MSG_UPDATE_FINISHED_PL_1250 ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

#define KPST_MSG_SELDOWN_TITLE_PL_1250   ((const unsigned char *)"") // "Produkto komponentø parsisiøsdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_PL_1250  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"") // "Naujø serijos leidiniø daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1250 ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE_PL_1250    ((const unsigned char *)"") // "Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1250   ((const unsigned char *)"") // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"") // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1250 ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

#define KPST_MSG_CLOSE_PROG_WND_PL_1250  ((const unsigned char *)"") // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

// -----------------------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define KPST_MSG_PROD_REG_PL_1257        ((const unsigned char *)"") // "Rejestracja programu")
#define KPST_MSG_UNREG_PL_1257           ((const unsigned char *)"") // "Odwoùanie licencji")
#define KPST_MSG_LIC_PL_1257             ((const unsigned char *)"") // "Licencja")
#define KPST_MSG_REG_INFO_PL_1257        ((const unsigned char *)"") // "By uruchomiã program, wymagana jest rejestracja.")
#define KPST_MSG_IVESK_LIC_PL_1257       ((const unsigned char *)"") // "Wprowadê kod licencji, który otrzymaùeú nabywajàc produkt.")
#define KPST_MSG_IVESK_LIC_1_PL_1257     ((const unsigned char *)"") // "Visà kodà galima kopijuoti á pirmà langelá."
#define KPST_MSG_REG_CARD_PL_1257        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_PL_1257         ((const unsigned char *)"") // "Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1257   ((const unsigned char *)"") // "Bùædnie wprowadzono kod licencji")

#define KPST_MSG_CHECK_CONN_PL_1257      ((const unsigned char *)"") // "Sprawdê, czy komputer jest podùàczony do Internetu")
#define KPST_MSG_CHECK_CONN_LOC_PL_1257  ((const unsigned char *)"") // "Sprawdê, czy komputer jest podùàczony do sieci")

#define KPST_MSG_REG_SUCC_PL_1257        ((const unsigned char *)"") // "Licencja zostaùa zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1257    ((const unsigned char *)"") // "Licencja juý jest zarejestrowana")
#define KPST_MSG_REG_UNSUC_PL_1257       ((const unsigned char *)"") // "Licencji nie udaùo siæ zarejestrowaã przez Internet.")
#define KPST_MSG_REG_UNSUC_0_PL_1257     ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_PL_1257     ((const unsigned char *)"") // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1257   ((const unsigned char *)"") // "Nieudana rejestracja.")
#define KPST_MSG_DIEG_KOD_PL_1257        ((const unsigned char *)"") // "Kod instalacji:")

#define KPST_MSG_UNREG_INFO_PL_1257      ((const unsigned char *)"") // "Przed przeniesieniem programu na inny komputer licencja powinna byã usuniæta.")
#define KPST_MSG_UNREG_IVESK_LIC_PL_1257 KPST_MSG_IVESK_LIC_PL_1257

#define KPST_MSG_REG_PERSPEJ_PL_1257     ((const unsigned char *)"") // "Zarejestrowany program bædzie dziaùaù tylko na tym komputerze!")

#define KPST_MSG_BUT_REG_PL_1257         ((const unsigned char *)"") // "W jaki sposób zarejestrujesz program:")
#define KPST_MSG_BUT_UNREG_PL_1257       ((const unsigned char *)"") // "W jaki sposób usuniesz rejestracjæ programu:")

#define KPST_MSG_INTERNETU_PL_1257       ((const unsigned char *)"") // "Przez Internet")
#define KPST_MSG_TELEFONU_PL_1257        ((const unsigned char *)"") // "Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1257      ((const unsigned char *)"") // "Odwoùaj")
#define KPST_MSG_CANCEL_UNREG_PL_1257    ((const unsigned char *)"") // "Nie usuwaj")

#define KPST_MSG_SIUSK_PASTU_PL_1257     ((const unsigned char *)"") // "Kod instalacji moýesz wysùaã pocztà elektronicznà na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1257    ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoniàc pod nr. tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1257      ((const unsigned char *)"") // "podyktowaã go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1257     ((const unsigned char *)"") // "Wprowadê otrzymanà odpowiedê – klucz instalacji.")
#define KPST_MSG_IVESK_RAKTA_1_PL_1257   ((const unsigned char *)"") // "Visà raktà galima kopijuoti á pirmà langelá."
#define KPST_MSG_DIEG_RAKTAS_PL_1257     ((const unsigned char *)"") // "Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1257   ((const unsigned char *)"") // "Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1257 ((const unsigned char *)"") // "Bùædnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1257   ((const unsigned char *)"") // "Wywoùaj program z pùyty CD")
#define KPST_MSG_BAD_CD_PL_1257          ((const unsigned char *)"") // "Wadliwa plùyta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1257    ((const unsigned char *)"") // "Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1257    ((const unsigned char *)"") // "Rezultatø rasti nepavyko.\n Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1257    ((const unsigned char *)"") // "Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1257     ((const unsigned char *)"") // ". Rezultatai sëkmingai perkelti á ")

#define KPST_MSG_REG_NOT_ADMIN_PL_1257   ((const unsigned char *)"") // "Dla rejestracji licencji powinieneú\n zalogowaã siæ do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1257 ((const unsigned char *)"") // "Dla usuniæcia instalacji produktu powinieneú\n zalogowaã siæ do systemu jako administrator")

#define KPST_MSG_NOT_REG_PL_1257         ((const unsigned char *)"") // "Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_INVALID_REG_PL_1257     ((const unsigned char *)"") // "Kod uaktualnienia i podstawowego produktu nie sà zgodne. Zainstaluj produkt ponownie.")

#define KPST_MSG_UNREG_KOD_1_PL_1257     ((const unsigned char *)"") // "Kod usuniæcia")
#define KPST_MSG_UNREG_KOD_PL_1257       ((const unsigned char *)"") // "Kod usuniæcia licencji:              \n")
#define KPST_MSG_ALLREADY_REMOVED_PL_1257   ((const unsigned char *)"") // "Produkt juý usuniæty")
#define KPST_MSG_UNREG_SUCC_PL_1257      ((const unsigned char *)"") // "Licencja zostaùa usuniæta")
#define KPST_MSG_UNREG_UNSUCC_PL_1257    ((const unsigned char *)"") // "Nie udaùo siæ usunàã rejestracji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_PL_1257  ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

#define KPST_MSG_REG_NOT_YET_PL_1257     ((const unsigned char *)"") // "Program jeszcze nie byù zarejestrowany. Ponów rejestracjæ podczac wywoùywania programu poprzez menu „Rejestracja”.")
#define KPST_MSG_INI_NOT_ADMIN_PL_1257   ((const unsigned char *)"") // "Zasoby systemu nie sà dostæpne. Zaloguj siæ do systemu jako administrator")

#define KPST_MSG_UNREG_PASTU_PL_1257     ((const unsigned char *)"") // "Kod usuniæcia moýesz wysùaã pocztà elektronowà na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1257 ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoniàc pod nr. tel. 8-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1257   ((const unsigned char *)"") // "i podyktowaã dla operatora.")

#define KPST_MSG_UNREG_NEGALESIT_PL_1257 /* KPST_MSG_UNREG_TELEF_PL_1257 */ ((const unsigned char *)"") // "Nie wykonujàc tej czynnoúci, nie bædziesz mógù zarejestrowaã programu na innym komputerze!")
#define KPST_MSG_INSERT_FLOPPY_PL_1257   ((const unsigned char *)"") // "Ádëkite diskelá")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1257   ((const unsigned char *)"") // "Negaliu atverti rezultatø failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1257  ((const unsigned char *)"") // "Negaliu áraðyti á rezultatø failà.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1257  ((const unsigned char *)"") // "Negaliu uþdaryti rezultatø failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1257     ((const unsigned char *)"") // "Negaliu perskaityti áraðyto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1257   ((const unsigned char *)"") // "Duomenys neásiraðo.")
#define KPST_MSG_REFUSE_RESULTS_PL_1257  ((const unsigned char *)"") // "Ar tikrai norite atsisakyti rezultatø?")
#define KPST_MSG_TEST_SUCC_PL_1257       ((const unsigned char *)"") // "Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1257      ((const unsigned char *)"") // "Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1257    ((const unsigned char *)"") // "Podùacz USB noúnik z \"")

#define KPST_MSG_INSERT_FLASH_1_PL_1257  ((const unsigned char *)"") // "\"")

#define KPST_MSG_ENTER_PWD_PL_1257       ((const unsigned char *)"") // "Wprowadê hasùo:")
#define KPST_MSG_BAD_PWD_PL_1257         ((const unsigned char *)"") // "Bùædne hasùo")

#define KPST_MSG_ENTER_PUK_PL_1257       ((const unsigned char *)"") // "Wprowadê kod licencji noúnika USB:")
#define KPST_MSG_BAD_PUK_PL_1257         ((const unsigned char *)"") // "Niepoprawny kod licencji")

#define KPST_MSG_OBJ_REG_PL_1257         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_PL_1257    ((const unsigned char *)"") // "Prieð naudojant dokumentà reikia uþregistruoti."
#define KPST_MSG_OBJ_UNREG_INFO_PL_1257  ((const unsigned char *)"") // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1257 ((const unsigned char *)"") // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_PL_1257     ((const unsigned char *)"") // "Dokumento registracija atðaukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1257 ((const unsigned char *)"") // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

#define KPST_MSG_BAD_FLASH_PL_1257       ((const unsigned char *)"") // "Ðis atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_PL_1257 ((const unsigned char *)"") // "Licencijos galiojimas baigësi"
#define KPST_MSG_REST_MONTHS_PL_1257     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d mënesiø"
#define KPST_MSG_REST_LAST_MONTH_PL_1257 ((const unsigned char *)"") // "Licencijos galiojimas baigsis kità mënesá"
#define KPST_MSG_REST_DAYS_PL_1257       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dienø"
#define KPST_MSG_REST_DAY_PL_1257        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_PL_1257      ((const unsigned char *)"") // "Ðiandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_PL_1257      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrodá"

#define KPST_MSG_BAD_PRODVAR_PL_1257     ((const unsigned char *)"") // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

#define KPST_MSG_UPDATE_FINISHED_PL_1257 ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

#define KPST_MSG_SELDOWN_TITLE_PL_1257   ((const unsigned char *)"") // "Produkto komponentø parsisiøsdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_PL_1257  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1257 ((const unsigned char *)"") // "Naujø serijos leidiniø daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1257 ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE_PL_1257    ((const unsigned char *)"") // "Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1257   ((const unsigned char *)"") // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1257 ((const unsigned char *)"") // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1257 ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

#define KPST_MSG_CLOSE_PROG_WND_PL_1257  ((const unsigned char *)"") // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

// -----------------------------------------------
#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"") // "Program registration")
#define KPST_MSG_UNREG_RU           ((const unsigned char *)"") // "Registration cancellation")
#define KPST_MSG_LIC_RU             ((const unsigned char *)"") // "Licence")
#define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"") // "To keep program running, licence should be registered.")
#define KPST_MSG_IVESK_LIC_RU       ((const unsigned char *)"") // "Enter licence code acquired together with the product.")
#define KPST_MSG_IVESK_LIC_1_RU     ((const unsigned char *)"") // "Visà kodà galima kopijuoti á pirmà langelá."
#define KPST_MSG_REG_CARD_RU        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_RU         ((const unsigned char *)"") // "Licence code:")
#define KPST_MSG_BLOGAS_LIC_KODAS_RU   ((const unsigned char *)"") // "Invalid licence code")
#define KPST_MSG_CHECK_CONN_RU      ((const unsigned char *)"") // "Check your computer Internet connection")
#define KPST_MSG_CHECK_CONN_LOC_RU  ((const unsigned char *)"") // "Check your computer network connection")
#define KPST_MSG_REG_SUCC_RU        ((const unsigned char *)"") // "Licence registered successfully")
#define KPST_MSG_ALLREADY_REG_RU    ((const unsigned char *)"") // "Licence already registered")
#define KPST_MSG_REG_UNSUC_RU       ((const unsigned char *)"") // "Unsuccessful licence registration by Internet.")
#define KPST_MSG_REG_UNSUC_0_RU     ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_RU     ((const unsigned char *)"") // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_RU   ((const unsigned char *)"") // "Registration unsuccessful.")
#define KPST_MSG_DIEG_KOD_RU        ((const unsigned char *)"") // "Installation code:")

#define KPST_MSG_UNREG_INFO_RU      ((const unsigned char *)"") // "Licence registration should be cancelled before moving the program to another computer.")
#define KPST_MSG_UNREG_IVESK_LIC_RU KPST_MSG_IVESK_LIC_RU

#define KPST_MSG_REG_PERSPEJ_RU     ((const unsigned char *)"") // "Registered program will run on this computer only!")

#define KPST_MSG_BUT_REG_RU         ((const unsigned char *)"") // "How would you register:")
#define KPST_MSG_BUT_UNREG_RU       ((const unsigned char *)"") // "How would you cancel registration:")

#define KPST_MSG_INTERNETU_RU       ((const unsigned char *)"") // "By Internet")
#define KPST_MSG_TELEFONU_RU        ((const unsigned char *)"") // "By phone")
#define KPST_MSG_CANCEL_REG_RU      ((const unsigned char *)"") // "Cancel")
#define KPST_MSG_CANCEL_UNREG_RU    ((const unsigned char *)"") // "Do not cancel")

#define KPST_MSG_SIUSK_PASTU_RU     ((const unsigned char *)"") // "Installation code should be sent by an e-mail, address tech@tev.lt or told")
#define KPST_MSG_DARBO_LAIKAS_RU    ((const unsigned char *)"") // "to the operator at working hours from 9 to 16 EET by phone, number")
#define KPST_MSG_DIKT_TELEF_RU      ((const unsigned char *)"") // "+370-5-2729318.")

#define KPST_MSG_IVESK_RAKTA_RU     ((const unsigned char *)"") // "Enter received answer - installation key.")
#define KPST_MSG_IVESK_RAKTA_1_RU   ((const unsigned char *)"") // "Visà raktà galima kopijuoti á pirmà langelá."
#define KPST_MSG_DIEG_RAKTAS_RU     ((const unsigned char *)"") // "Installation key:")
#define KPST_MSG_DIEG_RAKTAS_1_RU   ((const unsigned char *)"") // "Installation key")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_RU ((const unsigned char *)"") // "Invalid installation key")
#define KPST_MSG_START_FROM_CD_RU   ((const unsigned char *)"") // "Run the program directly from CD")
#define KPST_MSG_BAD_CD_RU          ((const unsigned char *)"") // "Invalid CD")

#define KPST_MSG_REZ_NESUFORM_RU    ((const unsigned char *)"") // "Results were not generated.\nAsk for the technical support by e-mail, address tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_RU    ((const unsigned char *)"") // "Results were not found.\nAsk for the technical support by e-mail, address tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_2_RU    ((const unsigned char *)"") // "Results were not found.\nYou are %s, OS %s.\nTry login to the privileged user.")
#define KPST_MSG_REZ_SUCCESS_RU     ((const unsigned char *)"") // ". Results were successfully moved to ")

#define KPST_MSG_REG_NOT_ADMIN_RU   ((const unsigned char *)"") // "Licence registration requires rights of privileged user ")
#define KPST_MSG_UNREG_NOT_ADMIN_RU ((const unsigned char *)"") // "Licence cancellation requires\nrights of privileged user")
#define KPST_MSG_NOT_REG_RU         ((const unsigned char *)"") // "Product licence not yet registered")
#define KPST_MSG_INVALID_REG_RU     ((const unsigned char *)"") // "Licence codes of the update and the main product are different. Repeat installation of the product.")

#define KPST_MSG_UNREG_KOD_1_RU     ((const unsigned char *)"") // "Cancellation code")
#define KPST_MSG_UNREG_KOD_RU       ((const unsigned char *)"") // "Licence cancellation code:              \n")
#define KPST_MSG_ALLREADY_REMOVED_RU   ((const unsigned char *)"") // "Product already removed")
#define KPST_MSG_UNREG_SUCC_RU      ((const unsigned char *)"") // "Licence registration cancelled successfully")
#define KPST_MSG_UNREG_UNSUCC_RU    ((const unsigned char *)"") // "Unsuccessful licence cancellation by Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_RU  ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau esanèià nuorodà."

#define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"") // "Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command “Registration”.")
#define KPST_MSG_REG_NOT_YET_RU_0   ((const unsigned char *)"") // "Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command “Registration”.")

#define KPST_MSG_INI_NOT_ADMIN_RU   ((const unsigned char *)"") // "System resources inaccessible, login as privileged user")

#define KPST_MSG_UNREG_PASTU_RU     ((const unsigned char *)"") // "Cancellation code should be sent by e-mail, address tech@tev.lt or told")
#define KPST_MSG_UNREG_DARBO_LAIKAS_RU ((const unsigned char *)"") // "to the operator at working hours from 9 to 16 EET by phone, number")
#define KPST_MSG_UNREG_DIKT_TELEF_RU   ((const unsigned char *)"") // "+370-5-2729318.")

#define KPST_MSG_UNREG_NEGALESIT_RU /* KPST_MSG_UNREG_TELEF_RU */ ((const unsigned char *)"") // "Without doing it you will be unable to run the program on another computer!")

#define KPST_MSG_INSERT_FLOPPY_RU   ((const unsigned char *)"") // "Put the floppy disk")
#define KPST_MSG_UNABLE_OPEN_REZFILE_RU   ((const unsigned char *)"") // "Result file could not be opened.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_RU  ((const unsigned char *)"") // "Result file could not be written.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_RU  ((const unsigned char *)"") // "Result file could not be closed.")
#define KP_MSG_UNABLE_READ_WRITTEN_RU     ((const unsigned char *)"") // "Written file could not be read.")
#define KPST_MSG_COULDNT_WRITE_RU   ((const unsigned char *)"") // "Data could not be written.")
#define KPST_MSG_REFUSE_RESULTS_RU  ((const unsigned char *)"") // "Are you sure you want to discard results?")
#define KPST_MSG_TEST_SUCC_RU       ((const unsigned char *)"") // "Software of the test does work on this computer properly")

#define KPST_MSG_TEST_UNSUC_RU      ((const unsigned char *)"") // "Results were not generated.\nPlease pack files of the folder c:\\arkim\\rezultatai to the archive and send it by e-mail, address tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_RU    ((const unsigned char *)"") // "Put the USB flash drive with “")
#define KPST_MSG_INSERT_FLASH_1_RU  ((const unsigned char *)"") // "”")

#define KPST_MSG_ENTER_PWD_RU       ((const unsigned char *)"") // "Enter the password:")
#define KPST_MSG_BAD_PWD_RU         ((const unsigned char *)"") // "Password incorrect")
#define KPST_MSG_ENTER_PUK_RU       ((const unsigned char *)"") // "Enter the USB flash drive licence code:")
#define KPST_MSG_BAD_PUK_RU         ((const unsigned char *)"") // "Licence code invalid")

#define KPST_MSG_OBJ_REG_RU         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_RU    ((const unsigned char *)"") // "Prieð naudojant dokumentà reikia uþregistruoti."
#define KPST_MSG_OBJ_UNREG_INFO_RU  ((const unsigned char *)"") // "Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá."
#define KPST_MSG_OBJ_REG_PERSPEJ_RU ((const unsigned char *)"") // "Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_RU     ((const unsigned char *)"") // "Dokumento registracija atðaukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_RU ((const unsigned char *)"") // "To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!"

#define KPST_MSG_BAD_FLASH_RU       ((const unsigned char *)"") // "Ðis atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_RU ((const unsigned char *)"") // "Licencijos galiojimas baigësi"
#define KPST_MSG_REST_MONTHS_RU     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d mënesiø"
#define KPST_MSG_REST_LAST_MONTH_RU ((const unsigned char *)"") // "Licencijos galiojimas baigsis kità mënesá"
#define KPST_MSG_REST_DAYS_RU       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %ld dienø"
#define KPST_MSG_REST_DAY_RU        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_RU      ((const unsigned char *)"") // "Ðiandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_RU      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrodá"

#define KPST_MSG_BAD_PRODVAR_RU     ((const unsigned char *)"") // "Jûsø atmintuko versija pasenusi. Paleiskite atmintuke esantá produktà, paspauskite mygtukà „i“, parsisiøskite atnaujinimà ir já ádiekite."

#define KPST_MSG_UPDATE_FINISHED_RU ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtukà „Baigti“. Po to paleiskite MIKO knygà."

#define KPST_MSG_SELDOWN_TITLE_RU   ((const unsigned char *)"") // "Produkto komponentø parsisiøsdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_RU  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuriø parsisiøsti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_RU ((const unsigned char *)"") // "Naujø serijos leidiniø daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_RU ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE_RU    ((const unsigned char *)"") // "Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_RU   ((const unsigned char *)"") // "Jûsø turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_RU ((const unsigned char *)"") // "Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_RU ((const unsigned char *)"") // "Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\njei ne – „Atðaukti“.")

#define KPST_MSG_CLOSE_PROG_WND_RU  ((const unsigned char *)"") // "Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#endif // #ifndef kpstmsg_included
