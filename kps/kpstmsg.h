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
KPST_MSG_REG_INFO_IX,               // "Kad programa veikt�, j� reikia u�registruoti."
KPST_MSG_IVESK_LIC_IX,              // "�veskite licencijos kod�, kur� gavote �sigydami produkt�."
KPST_MSG_IVESK_LIC_1_IX,            // "Vis� kod� galima kopijuoti � pirm� langel�."
KPST_MSG_REG_CARD_IX,               // "J� rasite registracijos kortel�je"
KPST_MSG_LIC_KOD_IX,                // "Licencijos kodas:"
KPST_MSG_BLOGAS_LIC_KODAS_IX,       // "Neteisingai �vestas licencijos kodas"
KPST_MSG_CHECK_CONN_IX,             // "Patikrinkite, ar kompiuteris prijungtas prie interneto"
KPST_MSG_CHECK_CONN_LOC_IX,         // "Patikrinkite, ar kompiuteris prijungtas prie tinklo"
KPST_MSG_REG_SUCC_IX,               // "Licencija u�registruota s�kmingai"
KPST_MSG_ALLREADY_REG_IX,           // "Licencija jau u�registruota"
KPST_MSG_REG_UNSUC_IX,              // "Internetu licencijos u�registruoti nepavyko."
KPST_MSG_REG_UNSUC_0_IX,            // "Pabandykite nar�ykle atverti �emiau"
KPST_MSG_REG_UNSUC_1_IX,            // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius."
KPST_MSG_REG_UNSUC_LOC_IX,          // "U�siregistruoti nepavyko."
KPST_MSG_DIEG_KOD_IX,               // "Diegimo kodas:"

KPST_MSG_UNREG_INFO_IX,             // "Licencijos registracija naikinama prie� program� perkeliant � kit� kompiuter�."
KPST_MSG_UNREG_IVESK_LIC_IX,        // KPST_MSG_IVESK_LIC

KPST_MSG_REG_PERSPEJ_IX,            // "U�registruota programa veiks tik �iame kompiuteryje!"

KPST_MSG_BUT_REG_IX,                // "Kaip registruosite:"
KPST_MSG_BUT_UNREG_IX,              // "Kaip naikinsite:"

KPST_MSG_INTERNETU_IX,              // "Internetu"
KPST_MSG_TELEFONU_IX,               // "Telefonu"
KPST_MSG_CANCEL_REG_IX,             // "At�aukti"
KPST_MSG_CANCEL_UNREG_IX,           // "Nenaikinti"

KPST_MSG_SIUSK_PASTU_IX,            // "Diegimo kod� galite i�si�sti elektroniniu pa�tu, adresu tech@tev.lt arba"
KPST_MSG_DARBO_LAIKAS_IX,           // "darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318"
KPST_MSG_DIKT_TELEF_IX,             // "padiktuoti operatoriui."

KPST_MSG_IVESK_RAKTA_IX,            // "�veskite gaut� atsakym� � diegimo rakt�."
KPST_MSG_IVESK_RAKTA_1_IX,          // "Vis� rakt� galima kopijuoti � pirm� langel�."
KPST_MSG_DIEG_RAKTAS_IX,            // "Diegimo raktas:"
KPST_MSG_DIEG_RAKTAS_1_IX,          // "Diegimo raktas"
KPST_MSG_BLOGAS_DIEG_RAKTAS_IX,     // "Neteisingai �vestas diegimo raktas"
KPST_MSG_START_FROM_CD_IX,          // "Program� paleiskite i� kompaktin�s plok�tel�s"
KPST_MSG_BAD_CD_IX,                 // "Bloga kompaktin� plok�tel�"

KPST_MSG_REZ_NESUFORM_IX,           // "Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt"
KPST_MSG_REZ_NFOUND_1_IX,           // "Rezultat� rasti nepavyko.\n D�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt "
KPST_MSG_REZ_NFOUND_2_IX,           // "Rezultat� rasti nepavyko.\nJ�s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator."
KPST_MSG_REZ_SUCCESS_IX,            // ". Rezultatai s�kmingai perkelti � "

KPST_MSG_REG_NOT_ADMIN_IX,          // "Norint u�registruoti licencij�, reikia sistemos\n administratoriaus teisi�"
KPST_MSG_UNREG_NOT_ADMIN_IX,        // "Nor�dami panaikinti produkto diegim�,\n u�siregistruokite sistemos administratoriumi"
KPST_MSG_NOT_REG_IX,                // "Produkto licencija dar neu�registruota"
KPST_MSG_INVALID_REG_IX,            // "Papildymo ir pagrindinio produkto licencij� kodai nesutampa. Pakartokite produkto diegim�."

KPST_MSG_UNREG_KOD_1_IX,            // "I�metimo kodas"
KPST_MSG_UNREG_KOD_IX,              // "Licencijos i�metimo kodas:              \n"
KPST_MSG_ALLREADY_REMOVED_IX,       // "Produktas jau i�mestas"
KPST_MSG_UNREG_SUCC_IX,             // "Licencijos diegimas panaikintas s�kmingai"
KPST_MSG_UNREG_UNSUCC_IX,           // "Internetu registracijos panaikinti nepavyko."
KPST_MSG_UNREG_UNSUCC_1_IX,         // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."

KPST_MSG_REG_NOT_YET_IX,            // "Programa dar neu�registruota. Registracijos proced�r� tur�site pakartoti paleidimo meniu komanda �Registracija�."

KPST_MSG_INI_NOT_ADMIN_IX,          // "Sistemos resursai nepasiekiami, u�siregistruokite administratoriumi"

KPST_MSG_UNREG_PASTU_IX,            // "I�metimo kod� i�si�skite elektroniniu pa�tu, adresu tech@tev.lt arba"
KPST_MSG_UNREG_DARBO_LAIKAS_IX,     // "darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318"
KPST_MSG_UNREG_DIKT_TELEF_IX,       // "padiktuokite operatoriui."

KPST_MSG_UNREG_NEGALESIT_IX,        // "To nepadar�, kitame kompiuteryje programos u�registruoti negal�site!"

KPST_MSG_INSERT_FLOPPY_IX,          // "�d�kite diskel�"
KPST_MSG_UNABLE_OPEN_REZFILE_IX,    // "Negaliu atverti rezultat� failo."
KPST_MSG_UNABLE_WRITE_REZFILE_IX,   // "Negaliu �ra�yti � rezultat� fail�."
KPST_MSG_UNABLE_CLOSE_REZFILE_IX,   // "Negaliu u�daryti rezultat� failo."
KP_MSG_UNABLE_READ_WRITTEN_IX,      // "Negaliu perskaityti �ra�yto failo."
KPST_MSG_COULDNT_WRITE_IX,          // "Duomenys ne�sira�o."
KPST_MSG_REFUSE_RESULTS_IX,         // "Ar tikrai norite atsisakyti rezultat�?"
KPST_MSG_TEST_SUCC_IX,              // "Konkurso programin� �ranga �iame kompiuteryje veikia tinkamai     "

KPST_MSG_TEST_UNSUC_IX,             // "Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu, adresu tech@tev.lt"

KPST_MSG_INSERT_FLASH_IX,           // "�ki�kite atmintuk� su \""
KPST_MSG_INSERT_FLASH_1_IX,         // "\""

KPST_MSG_ENTER_PWD_IX,              // "�veskite slapta�od�:"
KPST_MSG_BAD_PWD_IX,                // "Slapta�odis neteisingas"
KPST_MSG_ENTER_PUK_IX,              // "�veskite atmintuko licencijos kod�:"
KPST_MSG_BAD_PUK_IX,                // "Neteisingas licencijos kodas"

KPST_MSG_OBJ_REG_IX,                // "Dokumento registracija"
KPST_MSG_OBJ_REG_INFO_IX,           // "Prie� naudojant dokument� reikia u�registruoti."
KPST_MSG_OBJ_UNREG_INFO_IX,         // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
KPST_MSG_OBJ_REG_PERSPEJ_IX,        // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

KPST_MSG_OBJ_REG_NOT_YET_IX,        // "Dokumento registracija at�aukta."
KPST_MSG_OBJ_UNREG_NEGALESIT_IX,    // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

KPST_MSG_BAD_FLASH_IX,              // "�is atnaujinimas skirtas atmintukui %s"

KPST_MSG_LICENCE_EXPIRED_IX,        // "Licencijos galiojimas baig�si"
KPST_MSG_REST_MONTHS_IX,            // "Licencijos galiojimas baigsis po %d m�nesi�"
KPST_MSG_REST_LAST_MONTH_IX,        // "Licencijos galiojimas baigsis kit� m�nes�"
KPST_MSG_REST_DAYS_IX,              // "Licencijos galiojimas baigsis po %d dien�"
KPST_MSG_REST_DAY_IX,               // "Rytoj baigsis licencijos galiojimas"
KPST_MSG_REST_TODAY_IX,             // "�iandien baigiasi licencijos galiojimas"
KPST_MSG_TIME_CHEAT_IX,             // "Teisingai nustatykite sistemos laikrod�"

KPST_MSG_BAD_PRODVAR_IX,            // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

KPST_MSG_UPDATE_FINISHED_IX,        // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

KPST_MSG_SELDOWN_TITLE_IX,          // "Produkto komponent� parsisi�sdinimas: "
KPST_MSG_SELDOWN_PROMPT_IX,         // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
KPST_MSG_SELDOWN_NOMORE_PROMPT_IX,  // "Nauj� serijos leidini� daugiau netikrinti:"
KPST_MSG_SELDOWN_BUT_PROMPT_IX,     // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

KPST_MSG_SELUPD_TITLE_IX,           // "Produkto atnaujinim� parsisi�sdinimas")
KPST_MSG_SELUPD_PROMPT_IX,          // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
KPST_MSG_SELUPD_NOMORE_PROMPT_IX,   // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
KPST_MSG_SELUPD_BUT_PROMPT_IX,      // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

KPST_MSG_CLOSE_PROG_WND_IX,         // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

NumOfKpStMessages
};

#define NumOfKpStMessages_18 NumOfKpStMessages

extern const unsigned char *lpszaKpStMessages[NumOfKpStMessages][KpNumOfLangs];

// -----------------------------------------
#define KPST_MSG_PROD_REG              lpszaKpStMessages[KPST_MSG_PROD_REG_IX            ][iMsgLangOff] // "Programos registracija"
#define KPST_MSG_UNREG                 lpszaKpStMessages[KPST_MSG_UNREG_IX               ][iMsgLangOff] // "Registracijos naikinimas"
#define KPST_MSG_LIC                   lpszaKpStMessages[KPST_MSG_LIC_IX                 ][iMsgLangOff] // "Licencija"
#define KPST_MSG_REG_INFO              lpszaKpStMessages[KPST_MSG_REG_INFO_IX            ][iMsgLangOff] // "Kad programa veikt�, j� reikia u�registruoti."
#define KPST_MSG_IVESK_LIC             lpszaKpStMessages[KPST_MSG_IVESK_LIC_IX           ][iMsgLangOff] // "�veskite licencijos kod�, kur� gavote �sigydami produkt�."
#define KPST_MSG_IVESK_LIC_1           lpszaKpStMessages[KPST_MSG_IVESK_LIC_1_IX         ][iMsgLangOff] // "Vis� kod� galima kopijuoti � pirm� langel�."
#define KPST_MSG_REG_CARD              lpszaKpStMessages[KPST_MSG_REG_CARD_IX            ][iMsgLangOff] // "J� rasite registracijos kortel�je"
#define KPST_MSG_LIC_KOD               lpszaKpStMessages[KPST_MSG_LIC_KOD_IX             ][iMsgLangOff] // "Licencijos kodas:"
#define KPST_MSG_BLOGAS_LIC_KODAS      lpszaKpStMessages[KPST_MSG_BLOGAS_LIC_KODAS_IX    ][iMsgLangOff] // "Neteisingai �vestas licencijos kodas"
#define KPST_MSG_CHECK_CONN            lpszaKpStMessages[KPST_MSG_CHECK_CONN_IX          ][iMsgLangOff] // "Patikrinkite, ar kompiuteris prijungtas prie interneto"
#define KPST_MSG_CHECK_CONN_LOC        lpszaKpStMessages[KPST_MSG_CHECK_CONN_LOC_IX      ][iMsgLangOff] // "Patikrinkite, ar kompiuteris prijungtas prie tinklo"
#define KPST_MSG_REG_SUCC              lpszaKpStMessages[KPST_MSG_REG_SUCC_IX            ][iMsgLangOff] // "Licencija u�registruota s�kmingai"
#define KPST_MSG_ALLREADY_REG          lpszaKpStMessages[KPST_MSG_ALLREADY_REG_IX        ][iMsgLangOff] // "Licencija jau u�registruota"
#define KPST_MSG_REG_UNSUC             lpszaKpStMessages[KPST_MSG_REG_UNSUC_IX           ][iMsgLangOff] // "Internetu licencijos u�registruoti nepavyko."
#define KPST_MSG_REG_UNSUC_0           lpszaKpStMessages[KPST_MSG_REG_UNSUC_0_IX         ][iMsgLangOff] // "Pabandykite nar�ykle atverti �emiau"
#define KPST_MSG_REG_UNSUC_1           lpszaKpStMessages[KPST_MSG_REG_UNSUC_1_IX         ][iMsgLangOff] // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius."
#define KPST_MSG_REG_UNSUC_LOC         lpszaKpStMessages[KPST_MSG_REG_UNSUC_LOC_IX       ][iMsgLangOff] // "U�siregistruoti nepavyko."
#define KPST_MSG_DIEG_KOD              lpszaKpStMessages[KPST_MSG_DIEG_KOD_IX            ][iMsgLangOff] // "Diegimo kodas:"

#define KPST_MSG_UNREG_INFO            lpszaKpStMessages[KPST_MSG_UNREG_INFO_IX          ][iMsgLangOff] // "Licencijos registracija naikinama prie� program� perkeliant � kit� kompiuter�."
#define KPST_MSG_UNREG_IVESK_LIC       lpszaKpStMessages[KPST_MSG_UNREG_IVESK_LIC_IX     ][iMsgLangOff] // KPST_MSG_IVESK_LIC

#define KPST_MSG_REG_PERSPEJ           lpszaKpStMessages[KPST_MSG_REG_PERSPEJ_IX         ][iMsgLangOff] // "U�registruota programa veiks tik �iame kompiuteryje!"

#define KPST_MSG_BUT_REG               lpszaKpStMessages[KPST_MSG_BUT_REG_IX             ][iMsgLangOff] // "Kaip registruosite:"
#define KPST_MSG_BUT_UNREG             lpszaKpStMessages[KPST_MSG_BUT_UNREG_IX           ][iMsgLangOff] // "Kaip naikinsite:"

#define KPST_MSG_INTERNETU             lpszaKpStMessages[KPST_MSG_INTERNETU_IX           ][iMsgLangOff] // "Internetu"
#define KPST_MSG_TELEFONU              lpszaKpStMessages[KPST_MSG_TELEFONU_IX            ][iMsgLangOff] // "Telefonu"
#define KPST_MSG_CANCEL_REG            lpszaKpStMessages[KPST_MSG_CANCEL_REG_IX          ][iMsgLangOff] // "At�aukti"
#define KPST_MSG_CANCEL_UNREG          lpszaKpStMessages[KPST_MSG_CANCEL_UNREG_IX        ][iMsgLangOff] // "Nenaikinti"

#define KPST_MSG_SIUSK_PASTU           lpszaKpStMessages[KPST_MSG_SIUSK_PASTU_IX         ][iMsgLangOff] // "Diegimo kod� galite i�si�sti elektroniniu pa�tu, adresu tech@tev.lt arba"
#define KPST_MSG_DARBO_LAIKAS          lpszaKpStMessages[KPST_MSG_DARBO_LAIKAS_IX        ][iMsgLangOff] // "darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318"
#define KPST_MSG_DIKT_TELEF            lpszaKpStMessages[KPST_MSG_DIKT_TELEF_IX          ][iMsgLangOff] // "padiktuoti operatoriui."

#define KPST_MSG_IVESK_RAKTA           lpszaKpStMessages[KPST_MSG_IVESK_RAKTA_IX         ][iMsgLangOff] // "�veskite gaut� atsakym� � diegimo rakt�."
#define KPST_MSG_IVESK_RAKTA_1         lpszaKpStMessages[KPST_MSG_IVESK_RAKTA_1_IX       ][iMsgLangOff] // "Vis� rakt� galima kopijuoti � pirm� langel�."
#define KPST_MSG_DIEG_RAKTAS           lpszaKpStMessages[KPST_MSG_DIEG_RAKTAS_IX         ][iMsgLangOff] // "Diegimo raktas:"
#define KPST_MSG_DIEG_RAKTAS_1         lpszaKpStMessages[KPST_MSG_DIEG_RAKTAS_1_IX       ][iMsgLangOff] // "Diegimo raktas"
#define KPST_MSG_BLOGAS_DIEG_RAKTAS    lpszaKpStMessages[KPST_MSG_BLOGAS_DIEG_RAKTAS_IX  ][iMsgLangOff] // "Neteisingai �vestas diegimo raktas"
#define KPST_MSG_START_FROM_CD         lpszaKpStMessages[KPST_MSG_START_FROM_CD_IX       ][iMsgLangOff] // "Program� paleiskite i� kompaktin�s plok�tel�s"
#define KPST_MSG_BAD_CD                lpszaKpStMessages[KPST_MSG_BAD_CD_IX              ][iMsgLangOff] // "Bloga kompaktin� plok�tel�"

#define KPST_MSG_REZ_NESUFORM          lpszaKpStMessages[KPST_MSG_REZ_NESUFORM_IX        ][iMsgLangOff] // "Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt"
#define KPST_MSG_REZ_NFOUND_1          lpszaKpStMessages[KPST_MSG_REZ_NFOUND_1_IX        ][iMsgLangOff] // "Rezultat� rasti nepavyko.\n D�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt "
#define KPST_MSG_REZ_NFOUND_2          (const char *)lpszaKpStMessages[KPST_MSG_REZ_NFOUND_2_IX        ][iMsgLangOff] // "Rezultat� rasti nepavyko.\nJ�s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator."
#define KPST_MSG_REZ_SUCCESS           lpszaKpStMessages[KPST_MSG_REZ_SUCCESS_IX         ][iMsgLangOff] // ". Rezultatai s�kmingai perkelti � "

#define KPST_MSG_REG_NOT_ADMIN         lpszaKpStMessages[KPST_MSG_REG_NOT_ADMIN_IX       ][iMsgLangOff] // "Norint u�registruoti licencij�, reikia sistemos\n administratoriaus teisi�"
#define KPST_MSG_UNREG_NOT_ADMIN       lpszaKpStMessages[KPST_MSG_UNREG_NOT_ADMIN_IX     ][iMsgLangOff] // "Nor�dami panaikinti produkto diegim�,\n u�siregistruokite sistemos administratoriumi"
#define KPST_MSG_NOT_REG               lpszaKpStMessages[KPST_MSG_NOT_REG_IX             ][iMsgLangOff] // "Produkto licencija dar neu�registruota"
#define KPST_MSG_INVALID_REG           lpszaKpStMessages[KPST_MSG_INVALID_REG_IX         ][iMsgLangOff] // "Papildymo ir pagrindinio produkto licencij� kodai nesutampa. Pakartokite produkto diegim�."

#define KPST_MSG_UNREG_KOD_1           lpszaKpStMessages[KPST_MSG_UNREG_KOD_1_IX         ][iMsgLangOff] // "I�metimo kodas"
#define KPST_MSG_UNREG_KOD             lpszaKpStMessages[KPST_MSG_UNREG_KOD_IX           ][iMsgLangOff] // "Licencijos i�metimo kodas:              \n"
#define KPST_MSG_ALLREADY_REMOVED      lpszaKpStMessages[KPST_MSG_ALLREADY_REMOVED_IX    ][iMsgLangOff] // "Produktas jau i�mestas"
#define KPST_MSG_UNREG_SUCC            lpszaKpStMessages[KPST_MSG_UNREG_SUCC_IX          ][iMsgLangOff] // "Licencijos diegimas panaikintas s�kmingai"
#define KPST_MSG_UNREG_UNSUCC          lpszaKpStMessages[KPST_MSG_UNREG_UNSUCC_IX        ][iMsgLangOff] // "Internetu registracijos panaikinti nepavyko."
#define KPST_MSG_UNREG_UNSUCC_1        lpszaKpStMessages[KPST_MSG_UNREG_UNSUCC_1_IX      ][iMsgLangOff] // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."
#define KPST_MSG_REG_NOT_YET           lpszaKpStMessages[KPST_MSG_REG_NOT_YET_IX         ][iMsgLangOff] // "Programa dar neu�registruota. Registracijos proced�r� tur�site pakartoti paleidimo meniu komanda �Registracija�."

#define KPST_MSG_INI_NOT_ADMIN         lpszaKpStMessages[KPST_MSG_INI_NOT_ADMIN_IX       ][iMsgLangOff] // "Sistemos resursai nepasiekiami, u�siregistruokite administratoriumi"

#define KPST_MSG_UNREG_PASTU           lpszaKpStMessages[KPST_MSG_UNREG_PASTU_IX         ][iMsgLangOff] // "I�metimo kod� i�si�skite elektroniniu pa�tu, adresu tech@tev.lt arba"
#define KPST_MSG_UNREG_DARBO_LAIKAS    lpszaKpStMessages[KPST_MSG_UNREG_DARBO_LAIKAS_IX  ][iMsgLangOff] // "darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318"
#define KPST_MSG_UNREG_DIKT_TELEF      lpszaKpStMessages[KPST_MSG_UNREG_DIKT_TELEF_IX    ][iMsgLangOff] // "padiktuokite operatoriui."

#define KPST_MSG_UNREG_NEGALESIT       lpszaKpStMessages[KPST_MSG_UNREG_NEGALESIT_IX     ][iMsgLangOff] // "To nepadar�, kitame kompiuteryje programos u�registruoti negal�site!"

#define KPST_MSG_INSERT_FLOPPY         lpszaKpStMessages[KPST_MSG_INSERT_FLOPPY_IX       ][iMsgLangOff] // "�d�kite diskel�"
#define KPST_MSG_UNABLE_OPEN_REZFILE   lpszaKpStMessages[KPST_MSG_UNABLE_OPEN_REZFILE_IX ][iMsgLangOff] // "Negaliu atverti rezultat� failo."
#define KPST_MSG_UNABLE_WRITE_REZFILE  lpszaKpStMessages[KPST_MSG_UNABLE_WRITE_REZFILE_IX][iMsgLangOff] // "Negaliu �ra�yti � rezultat� fail�."
#define KPST_MSG_UNABLE_CLOSE_REZFILE  lpszaKpStMessages[KPST_MSG_UNABLE_CLOSE_REZFILE_IX][iMsgLangOff] // "Negaliu u�daryti rezultat� failo."
#define KP_MSG_UNABLE_READ_WRITTEN     lpszaKpStMessages[KP_MSG_UNABLE_READ_WRITTEN_IX   ][iMsgLangOff] // "Negaliu perskaityti �ra�yto failo."
#define KPST_MSG_COULDNT_WRITE         lpszaKpStMessages[KPST_MSG_COULDNT_WRITE_IX       ][iMsgLangOff] // "Duomenys ne�sira�o."
#define KPST_MSG_REFUSE_RESULTS        lpszaKpStMessages[KPST_MSG_REFUSE_RESULTS_IX      ][iMsgLangOff] // "Ar tikrai norite atsisakyti rezultat�?"
#define KPST_MSG_TEST_SUCC             lpszaKpStMessages[KPST_MSG_TEST_SUCC_IX           ][iMsgLangOff] // "Konkurso programin� �ranga �iame kompiuteryje veikia tinkamai     "

#define KPST_MSG_TEST_UNSUC            lpszaKpStMessages[KPST_MSG_TEST_UNSUC_IX          ][iMsgLangOff] // "Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu, adresu tech@tev.lt"

#define KPST_MSG_INSERT_FLASH          lpszaKpStMessages[KPST_MSG_INSERT_FLASH_IX        ][iMsgLangOff] // "�ki�kite atmintuk� su \""
#define KPST_MSG_INSERT_FLASH_1        lpszaKpStMessages[KPST_MSG_INSERT_FLASH_1_IX      ][iMsgLangOff] // "\""

#define KPST_MSG_ENTER_PWD             lpszaKpStMessages[KPST_MSG_ENTER_PWD_IX           ][iMsgLangOff] // "�veskite slapta�od�:"
#define KPST_MSG_BAD_PWD               lpszaKpStMessages[KPST_MSG_BAD_PWD_IX             ][iMsgLangOff] // "Slapta�odis neteisingas"
#define KPST_MSG_ENTER_PUK             lpszaKpStMessages[KPST_MSG_ENTER_PUK_IX           ][iMsgLangOff] // "�veskite atmintuko licencijos kod�:"
#define KPST_MSG_BAD_PUK               lpszaKpStMessages[KPST_MSG_BAD_PUK_IX             ][iMsgLangOff] // "Neteisingas licencijos kodas"

#define KPST_MSG_OBJ_REG               lpszaKpStMessages[KPST_MSG_OBJ_REG_IX             ][iMsgLangOff] // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO          lpszaKpStMessages[KPST_MSG_OBJ_REG_INFO_IX        ][iMsgLangOff] // "Prie� naudojant dokument� reikia u�registruoti."
#define KPST_MSG_OBJ_UNREG_INFO        lpszaKpStMessages[KPST_MSG_OBJ_UNREG_INFO_IX      ][iMsgLangOff] // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
#define KPST_MSG_OBJ_REG_PERSPEJ       lpszaKpStMessages[KPST_MSG_OBJ_REG_PERSPEJ_IX     ][iMsgLangOff] // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET       lpszaKpStMessages[KPST_MSG_OBJ_REG_NOT_YET_IX     ][iMsgLangOff] // "Dokumento registracija at�aukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT   lpszaKpStMessages[KPST_MSG_OBJ_UNREG_NEGALESIT_IX ][iMsgLangOff] // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

#define KPST_MSG_BAD_FLASH             (const char *)lpszaKpStMessages[KPST_MSG_BAD_FLASH_IX           ][iMsgLangOff] // "�is atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED       (const char *)lpszaKpStMessages[KPST_MSG_LICENCE_EXPIRED_IX     ][iMsgLangOff] // "Licencijos galiojimas baig�si"
#define KPST_MSG_REST_MONTHS           (const char *)lpszaKpStMessages[KPST_MSG_REST_MONTHS_IX         ][iMsgLangOff] // "Licencijos galiojimas baigsis po %d m�nesi�"
#define KPST_MSG_REST_LAST_MONTH       (const char *)lpszaKpStMessages[KPST_MSG_REST_LAST_MONTH_IX     ][iMsgLangOff] // "Licencijos galiojimas baigsis kit� m�nes�"
#define KPST_MSG_REST_DAYS             (const char *)lpszaKpStMessages[KPST_MSG_REST_DAYS_IX           ][iMsgLangOff] // "Licencijos galiojimas baigsis po %d dien�"
#define KPST_MSG_REST_DAY              (const char *)lpszaKpStMessages[KPST_MSG_REST_DAY_IX            ][iMsgLangOff] // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY            (const char *)lpszaKpStMessages[KPST_MSG_REST_TODAY_IX          ][iMsgLangOff] // "�iandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT            lpszaKpStMessages[KPST_MSG_TIME_CHEAT_IX          ][iMsgLangOff] // "Teisingai nustatykite sistemos laikrod�"

#define KPST_MSG_BAD_PRODVAR           lpszaKpStMessages[KPST_MSG_BAD_PRODVAR_IX         ][iMsgLangOff] // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

#define KPST_MSG_UPDATE_FINISHED       lpszaKpStMessages[KPST_MSG_UPDATE_FINISHED_IX     ][iMsgLangOff] // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

#define KPST_MSG_SELDOWN_TITLE         lpszaKpStMessages[KPST_MSG_SELDOWN_TITLE_IX       ][iMsgLangOff] // "Produkto komponent� parsisi�sdinimas: "
#define KPST_MSG_SELDOWN_PROMPT        lpszaKpStMessages[KPST_MSG_SELDOWN_PROMPT_IX      ][iMsgLangOff] // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT lpszaKpStMessages[KPST_MSG_SELDOWN_NOMORE_PROMPT_IX][iMsgLangOff] // "Nauj� serijos leidini� daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT    lpszaKpStMessages[KPST_MSG_SELDOWN_BUT_PROMPT_IX  ][iMsgLangOff] // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE          lpszaKpStMessages[KPST_MSG_SELUPD_TITLE_IX        ][iMsgLangOff] // "Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT         lpszaKpStMessages[KPST_MSG_SELUPD_PROMPT_IX       ][iMsgLangOff] // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT  lpszaKpStMessages[KPST_MSG_SELUPD_NOMORE_PROMPT_IX][iMsgLangOff] // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT     lpszaKpStMessages[KPST_MSG_SELUPD_BUT_PROMPT_IX   ][iMsgLangOff] // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

#define KPST_MSG_CLOSE_PROG_WND        (const char *)lpszaKpStMessages[KPST_MSG_CLOSE_PROG_WND_IX      ][iMsgLangOff] // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

// -----------------------------------------------
#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define KPST_MSG_PROD_REG_EN        ((const unsigned char *)"") // "Program registration")
#define KPST_MSG_UNREG_EN           ((const unsigned char *)"") // "Registration cancellation")
#define KPST_MSG_LIC_EN             ((const unsigned char *)"") // "Licence")
#define KPST_MSG_REG_INFO_EN        ((const unsigned char *)"") // "To keep program running, licence should be registered.")
#define KPST_MSG_IVESK_LIC_EN       ((const unsigned char *)"") // "Enter licence code acquired together with the product.")
#define KPST_MSG_IVESK_LIC_1_EN     ((const unsigned char *)"") // "Vis� kod� galima kopijuoti � pirm� langel�."
#define KPST_MSG_REG_CARD_EN        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_EN         ((const unsigned char *)"") // "Licence code:")
#define KPST_MSG_BLOGAS_LIC_KODAS_EN   ((const unsigned char *)"") // "Invalid licence code")
#define KPST_MSG_CHECK_CONN_EN      ((const unsigned char *)"") // "Check your computer Internet connection")
#define KPST_MSG_CHECK_CONN_LOC_EN  ((const unsigned char *)"") // "Check your computer network connection")
#define KPST_MSG_REG_SUCC_EN        ((const unsigned char *)"") // "Licence registered successfully")
#define KPST_MSG_ALLREADY_REG_EN    ((const unsigned char *)"") // "Licence already registered")
#define KPST_MSG_REG_UNSUC_EN       ((const unsigned char *)"") // "Unsuccessful licence registration by Internet.")
#define KPST_MSG_REG_UNSUC_0_EN     ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_EN     ((const unsigned char *)"") // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius.")
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
#define KPST_MSG_IVESK_RAKTA_1_EN   ((const unsigned char *)"") // "Vis� rakt� galima kopijuoti � pirm� langel�."
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
#define KPST_MSG_UNREG_UNSUCC_1_EN  ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."

#define KPST_MSG_REG_NOT_YET_EN     ((const unsigned char *)"") // "Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command �Registration�.")

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

#define KPST_MSG_INSERT_FLASH_EN    ((const unsigned char *)"") // "Put the USB flash drive with �")
#define KPST_MSG_INSERT_FLASH_1_EN  ((const unsigned char *)"") // "�")

#define KPST_MSG_ENTER_PWD_EN       ((const unsigned char *)"") // "Enter the password:")
#define KPST_MSG_BAD_PWD_EN         ((const unsigned char *)"") // "Password incorrect")
#define KPST_MSG_ENTER_PUK_EN       ((const unsigned char *)"") // "Enter the USB flash drive licence code:")
#define KPST_MSG_BAD_PUK_EN         ((const unsigned char *)"") // "Licence code invalid")

#define KPST_MSG_OBJ_REG_EN         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_EN    ((const unsigned char *)"") // "Prie� naudojant dokument� reikia u�registruoti."
#define KPST_MSG_OBJ_UNREG_INFO_EN  ((const unsigned char *)"") // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
#define KPST_MSG_OBJ_REG_PERSPEJ_EN ((const unsigned char *)"") // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_EN     ((const unsigned char *)"") // "Dokumento registracija at�aukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_EN ((const unsigned char *)"") // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

#define KPST_MSG_BAD_FLASH_EN       ((const unsigned char *)"") // "�is atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_EN ((const unsigned char *)"") // "Licencijos galiojimas baig�si"
#define KPST_MSG_REST_MONTHS_EN     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d m�nesi�"
#define KPST_MSG_REST_LAST_MONTH_EN ((const unsigned char *)"") // "Licencijos galiojimas baigsis kit� m�nes�"
#define KPST_MSG_REST_DAYS_EN       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dien�"
#define KPST_MSG_REST_DAY_EN        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_EN      ((const unsigned char *)"") // "�iandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_EN      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrod�"

#define KPST_MSG_BAD_PRODVAR_EN     ((const unsigned char *)"") // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

#define KPST_MSG_UPDATE_FINISHED_EN ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

#define KPST_MSG_SELDOWN_TITLE_EN   ((const unsigned char *)"") // "Produkto komponent� parsisi�sdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_EN  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_EN ((const unsigned char *)"") // "Nauj� serijos leidini� daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_EN ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE_EN    ((const unsigned char *)"") // "Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT_EN   ((const unsigned char *)"") // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_EN ((const unsigned char *)"") // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_EN ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

#define KPST_MSG_CLOSE_PROG_WND_EN  ((const unsigned char *)"") // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

#endif // #if ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

// -----------------------------------------------
#if (((MsgLang) != KpLangSel_p) && ((MsgLang) != KpLangLt_p))

#define KPST_MSG_PROD_REG_LT        ((const unsigned char *)"") // "Programos registracija")
#define KPST_MSG_UNREG_LT           ((const unsigned char *)"") // "Registracijos naikinimas")
#define KPST_MSG_LIC_LT             ((const unsigned char *)"") // "Licencija")
#define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"") // "Kad programa veikt�, j� reikia u�registruoti.")
#define KPST_MSG_IVESK_LIC_LT       ((const unsigned char *)"") // "�veskite licencijos kod�, kur� gavote �sigydami produkt�.")
#define KPST_MSG_IVESK_LIC_1_LT     ((const unsigned char *)"") // "Vis� kod� galima kopijuoti � pirm� langel�."
#define KPST_MSG_REG_CARD_LT        ((const unsigned char *)"") // "")  // "J� rasite registracijos kortel�je"
#define KPST_MSG_LIC_KOD_LT         ((const unsigned char *)"") // "Licencijos kodas:")
#define KPST_MSG_BLOGAS_LIC_KODAS_LT   ((const unsigned char *)"") // "Neteisingai �vestas licencijos kodas")
#define KPST_MSG_CHECK_CONN_LT      ((const unsigned char *)"") // "Patikrinkite, ar kompiuteris prijungtas prie interneto")
#define KPST_MSG_CHECK_CONN_LOC_LT  ((const unsigned char *)"") // "Patikrinkite, ar kompiuteris prijungtas prie tinklo")
#define KPST_MSG_REG_SUCC_LT        ((const unsigned char *)"") // "Licencija u�registruota s�kmingai")
#define KPST_MSG_ALLREADY_REG_LT    ((const unsigned char *)"") // "Licencija jau u�registruota")
#define KPST_MSG_REG_UNSUC_LT       ((const unsigned char *)"") // "Internetu licencijos u�registruoti nepavyko.")
#define KPST_MSG_REG_UNSUC_0_LT     ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_LT     ((const unsigned char *)"") // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"") // "U�siregistruoti nepavyko.") // "Licencijos u�registruoti nepavyko.")
#define KPST_MSG_DIEG_KOD_LT        ((const unsigned char *)"") // "Diegimo kodas:")

#define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"") // "Licencijos registracija naikinama prie� program� perkeliant � kit� kompiuter�.")
#define KPST_MSG_UNREG_IVESK_LIC_LT KPST_MSG_IVESK_LIC_LT

#define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"") // "U�registruota programa veiks tik �iame kompiuteryje!")

#define KPST_MSG_BUT_REG_LT         ((const unsigned char *)"") // "Kaip registruosite:")
#define KPST_MSG_BUT_UNREG_LT       ((const unsigned char *)"") // "Kaip naikinsite:")

#define KPST_MSG_INTERNETU_LT       ((const unsigned char *)"") // "Internetu")
#define KPST_MSG_TELEFONU_LT        ((const unsigned char *)"") // "Telefonu")
#define KPST_MSG_CANCEL_REG_LT      ((const unsigned char *)"") // "At�aukti") // "Neregistruoti")
#define KPST_MSG_CANCEL_UNREG_LT    ((const unsigned char *)"") // "Nenaikinti")

#define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"") // "Diegimo kod� galite i�si�sti elektroniniu pa�tu, adresu tech@tev.lt arba")
#define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"") // "darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_LT      ((const unsigned char *)"") // "padiktuoti operatoriui.")

#define KPST_MSG_IVESK_RAKTA_LT     ((const unsigned char *)"") // "�veskite gaut� atsakym� � diegimo rakt�.")
#define KPST_MSG_IVESK_RAKTA_1_LT   ((const unsigned char *)"") // "Vis� rakt� galima kopijuoti � pirm� langel�."
#define KPST_MSG_DIEG_RAKTAS_LT     ((const unsigned char *)"") // "Diegimo raktas:")
#define KPST_MSG_DIEG_RAKTAS_1_LT   ((const unsigned char *)"") // "Diegimo raktas")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_LT ((const unsigned char *)"") // "Neteisingai �vestas diegimo raktas")
#define KPST_MSG_START_FROM_CD_LT   ((const unsigned char *)"") // "Program� paleiskite i� kompaktin�s plok�tel�s") // ((const unsigned char *)"Program� paleiskite i� kompaktinio disko")
#define KPST_MSG_BAD_CD_LT          ((const unsigned char *)"") // "Bloga kompaktin� plok�tel�") // ((const unsigned char *)"Blogas kompaktinis diskas")

#define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"") // "Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"") // "Rezultat� rasti nepavyko.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_LT    ((const unsigned char *)"") // "Rezultat� rasti nepavyko.\nJ�s esate %s, OS %s.\nPabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_LT     ((const unsigned char *)"") // ". Rezultatai s�kmingai perkelti � ")

#define KPST_MSG_REG_NOT_ADMIN_LT   ((const unsigned char *)"") // "Norint u�registruoti licencij�, reikia sistemos\nadministratoriaus teisi�")
#define KPST_MSG_UNREG_NOT_ADMIN_LT ((const unsigned char *)"") // "Nor�dami panaikinti produkto diegim�,\nu�siregistruokite sistemos administratoriumi")
#define KPST_MSG_NOT_REG_LT         ((const unsigned char *)"") // "Produkto licencija dar neu�registruota")
#define KPST_MSG_INVALID_REG_LT     ((const unsigned char *)"") // "Papildymo ir pagrindinio produkto licencij� kodai nesutampa. Pakartokite produkto diegim�.")

#define KPST_MSG_UNREG_KOD_1_LT     ((const unsigned char *)"") // "I�metimo kodas")
#define KPST_MSG_UNREG_KOD_LT       ((const unsigned char *)"") // "Licencijos i�metimo kodas:              \n")
#define KPST_MSG_ALLREADY_REMOVED_LT   ((const unsigned char *)"") // "Produktas jau i�mestas")
#define KPST_MSG_UNREG_SUCC_LT      ((const unsigned char *)"") // "Licencijos diegimas panaikintas s�kmingai")
#define KPST_MSG_UNREG_UNSUCC_LT    ((const unsigned char *)"") // "Internetu registracijos panaikinti nepavyko.")
#define KPST_MSG_UNREG_UNSUCC_1_LT  ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."

#define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"") // "Programa dar neu�registruota. Registracijos proced�r� tur�site pakartoti paleidimo meniu komanda �Registracija�.")

#define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"") // "Sistemos resursai nepasiekiami, u�siregistruokite administratoriumi") // "Produkto diegimui reikia sistemos administratoriaus teisi�"

#define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"") // "I�metimo kod� i�si�skite elektroniniu pa�tu, adresu tech@tev.lt arba")
#define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"") // "darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_LT   ((const unsigned char *)"") // "padiktuokite operatoriui.")

#define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"") // "To nepadar�, kitame kompiuteryje programos u�registruoti negal�site!")

#define KPST_MSG_INSERT_FLOPPY_LT   ((const unsigned char *)"") // "�d�kite diskel�")
#define KPST_MSG_UNABLE_OPEN_REZFILE_LT   ((const unsigned char *)"") // "Negaliu atverti rezultat� failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_LT  ((const unsigned char *)"") // "Negaliu �ra�yti � rezultat� fail�.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_LT  ((const unsigned char *)"") // "Negaliu u�daryti rezultat� failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_LT     ((const unsigned char *)"") // "Negaliu perskaityti �ra�yto failo.")
#define KPST_MSG_COULDNT_WRITE_LT   ((const unsigned char *)"") // "Duomenys ne�sira�o.")
#define KPST_MSG_REFUSE_RESULTS_LT  ((const unsigned char *)"") // "Ar tikrai norite atsisakyti rezultat�?")
#define KPST_MSG_TEST_SUCC_LT       ((const unsigned char *)"") // "Konkurso programin� �ranga �iame kompiuteryje veikia tinkamai     ") // "�is kompiuteris parengtas darbui su programine priemone Acrobat Reader CE" // "Duomen� surinkimo testas baig�si s�kmingai"

#define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"") // "Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� aplanko c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_LT    ((const unsigned char *)"") // "�ki�kite atmintuk� su �")
#define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"") // "�")

#define KPST_MSG_ENTER_PWD_LT       ((const unsigned char *)"") // "�veskite slapta�od�:")
#define KPST_MSG_BAD_PWD_LT         ((const unsigned char *)"") // "Slapta�odis neteisingas")
#define KPST_MSG_ENTER_PUK_LT       ((const unsigned char *)"") // "�veskite atmintuko licencijos kod�:")
#define KPST_MSG_BAD_PUK_LT         ((const unsigned char *)"") // "Neteisingas licencijos kodas")

#define KPST_MSG_OBJ_REG_LT         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_LT    ((const unsigned char *)"") // "Prie� naudojant dokument� reikia u�registruoti."
#define KPST_MSG_OBJ_UNREG_INFO_LT  ((const unsigned char *)"") // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
#define KPST_MSG_OBJ_REG_PERSPEJ_LT ((const unsigned char *)"") // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_LT     ((const unsigned char *)"") // "Dokumento registracija at�aukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_LT ((const unsigned char *)"") // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

#define KPST_MSG_BAD_FLASH_LT       ((const unsigned char *)"") // "�is atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_LT ((const unsigned char *)"") // "Licencijos galiojimas baig�si"
#define KPST_MSG_REST_MONTHS_LT     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d m�nesi�"
#define KPST_MSG_REST_LAST_MONTH_LT ((const unsigned char *)"") // "Licencijos galiojimas baigsis kit� m�nes�"
#define KPST_MSG_REST_DAYS_LT       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dien�"
#define KPST_MSG_REST_DAY_LT        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_LT      ((const unsigned char *)"") // "�iandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_LT      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrod�"

#define KPST_MSG_BAD_PRODVAR_LT     ((const unsigned char *)"") // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

#define KPST_MSG_UPDATE_FINISHED_LT ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

#define KPST_MSG_SELDOWN_TITLE_LT   ((const unsigned char *)"") // "Produkto komponent� parsisi�sdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_LT  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_LT ((const unsigned char *)"") // "Nauj� serijos leidini� daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_LT ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE_LT    ((const unsigned char *)"") // "Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT_LT   ((const unsigned char *)"") // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_LT ((const unsigned char *)"") // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_LT ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

#define KPST_MSG_CLOSE_PROG_WND_LT  ((const unsigned char *)"") // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangLt_p))

// -----------------------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define KPST_MSG_PROD_REG_PL_1250        ((const unsigned char *)"") // "Rejestracja programu")
#define KPST_MSG_UNREG_PL_1250           ((const unsigned char *)"") // "Odwo�anie licencji")
#define KPST_MSG_LIC_PL_1250             ((const unsigned char *)"") // "Licencja")
#define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"") // "By uruchomi� program, wymagana jest rejestracja.")
#define KPST_MSG_IVESK_LIC_PL_1250       ((const unsigned char *)"") // "Wprowad� kod licencji, kt�ry otrzyma�e� nabywaj�c produkt.")
#define KPST_MSG_IVESK_LIC_1_PL_1250     ((const unsigned char *)"") // "Vis� kod� galima kopijuoti � pirm� langel�."
#define KPST_MSG_REG_CARD_PL_1250        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_PL_1250         ((const unsigned char *)"") // "Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1250   ((const unsigned char *)"") // "B��dnie wprowadzono kod licencji")

#define KPST_MSG_CHECK_CONN_PL_1250      ((const unsigned char *)"") // "Sprawd�, czy komputer jest pod��czony do Internetu")
#define KPST_MSG_CHECK_CONN_LOC_PL_1250  ((const unsigned char *)"") // "Sprawd�, czy komputer jest pod��czony do sieci")

#define KPST_MSG_REG_SUCC_PL_1250        ((const unsigned char *)"") // "Licencja zosta�a zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1250    ((const unsigned char *)"") // "Licencja ju� jest zarejestrowana")
#define KPST_MSG_REG_UNSUC_PL_1250       ((const unsigned char *)"") // "Licencji nie uda�o si� zarejestrowa� przez Internet.")
#define KPST_MSG_REG_UNSUC_0_PL_1250     ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_PL_1250     ((const unsigned char *)"") // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1250   ((const unsigned char *)"") // "Nieudana rejestracja.")
#define KPST_MSG_DIEG_KOD_PL_1250        ((const unsigned char *)"") // "Kod instalacji:")

#define KPST_MSG_UNREG_INFO_PL_1250      ((const unsigned char *)"") // "Przed przeniesieniem programu na inny komputer licencja powinna by� usuni�ta.")
#define KPST_MSG_UNREG_IVESK_LIC_PL_1250 KPST_MSG_IVESK_LIC_PL_1250

#define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"") // "Zarejestrowany program b�dzie dzia�a� tylko na tym komputerze!")

#define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"") // "W jaki spos�b zarejestrujesz program:")
#define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"") // "W jaki spos�b usuniesz rejestracj� programu:")

#define KPST_MSG_INTERNETU_PL_1250       ((const unsigned char *)"") // "Przez Internet")
#define KPST_MSG_TELEFONU_PL_1250        ((const unsigned char *)"") // "Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1250      ((const unsigned char *)"") // "Odwo�aj")
#define KPST_MSG_CANCEL_UNREG_PL_1250    ((const unsigned char *)"") // "Nie usuwaj")

#define KPST_MSG_SIUSK_PASTU_PL_1250     ((const unsigned char *)"") // "Kod instalacji mo�esz wys�a� poczt� elektroniczn� na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1250    ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoni�c pod nr. tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1250      ((const unsigned char *)"") // "podyktowa� go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1250     ((const unsigned char *)"") // "Wprowad� otrzyman� odpowied� - klucz instalacji.")
#define KPST_MSG_IVESK_RAKTA_1_PL_1250   ((const unsigned char *)"") // "Vis� rakt� galima kopijuoti � pirm� langel�."
#define KPST_MSG_DIEG_RAKTAS_PL_1250     ((const unsigned char *)"") // "Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1250   ((const unsigned char *)"") // "Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1250 ((const unsigned char *)"") // "B��dnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1250   ((const unsigned char *)"") // "Wywo�aj program z p�yty CD")
#define KPST_MSG_BAD_CD_PL_1250          ((const unsigned char *)"") // "Wadliwa pl�yta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1250    ((const unsigned char *)"") // "Rezultatai nesuformuoti.\nD?l technin?s pagalbos kreipkit?s elektroniniu pa�tu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1250    ((const unsigned char *)"") // "Rezultat? rasti nepavyko.\n D?l technin?s pagalbos kreipkit?s elektroniniu pa�tu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1250    ((const unsigned char *)"") // "Rezultat? rasti nepavyko.\nJ?s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1250     ((const unsigned char *)"") // ". Rezultatai s?kmingai perkelti ? ")

#define KPST_MSG_REG_NOT_ADMIN_PL_1250   ((const unsigned char *)"") // "Dla rejestracji licencji powiniene�\n zalogowa� si� do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1250 ((const unsigned char *)"") // "Dla usuni�cia instalacji produktu powiniene�\n zalogowa� si� do systemu jako administrator")

#define KPST_MSG_NOT_REG_PL_1250         ((const unsigned char *)"") // "Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_INVALID_REG_PL_1250     ((const unsigned char *)"") // "Kod uaktualnienia i podstawowego produktu nie s� zgodne. Zainstaluj produkt ponownie.")

#define KPST_MSG_UNREG_KOD_1_PL_1250     ((const unsigned char *)"") // "Kod usuni�cia")
#define KPST_MSG_UNREG_KOD_PL_1250       ((const unsigned char *)"") // "Kod usuni�cia licencji:              \n")
#define KPST_MSG_ALLREADY_REMOVED_PL_1250   ((const unsigned char *)"") // "Produkt ju� usuni�ty")
#define KPST_MSG_UNREG_SUCC_PL_1250      ((const unsigned char *)"") // "Licencja zosta�a usuni�ta")
#define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"") // "Nie uda�o si� usun�� rejestracji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_PL_1250  ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."

#define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"") // "Program jeszcze nie by� zarejestrowany. Pon�w rejestracj� podczac wywo�ywania programu poprzez menu �Rejestracja�.")
#define KPST_MSG_INI_NOT_ADMIN_PL_1250   ((const unsigned char *)"") // "Zasoby systemu nie s� dost�pne. Zaloguj si� do systemu jako administrator")

#define KPST_MSG_UNREG_PASTU_PL_1250     ((const unsigned char *)"") // "Kod usuni�cia mo�esz wys�a� poczt� elektronow� na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1250 ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoni�c pod nr. tel. 8-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1250   ((const unsigned char *)"") // "i podyktowa� dla operatora.")

#define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"") // "Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� zarejestrowa� programu na innym komputerze!")
#define KPST_MSG_INSERT_FLOPPY_PL_1250   ((const unsigned char *)"") // "?d?kite diskel?")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1250   ((const unsigned char *)"") // "Negaliu atverti rezultat? failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1250  ((const unsigned char *)"") // "Negaliu ?ra�yti ? rezultat? fail�.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1250  ((const unsigned char *)"") // "Negaliu u�daryti rezultat? failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1250     ((const unsigned char *)"") // "Negaliu perskaityti ?ra�yto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1250   ((const unsigned char *)"") // "Duomenys ne?sira�o.")
#define KPST_MSG_REFUSE_RESULTS_PL_1250  ((const unsigned char *)"") // "Ar tikrai norite atsisakyti rezultat??")
#define KPST_MSG_TEST_SUCC_PL_1250       ((const unsigned char *)"") // "Konkurso programin? ?ranga �iame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1250      ((const unsigned char *)"") // "Rezultat? suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin? atsi?sti elektroniniu pa�tu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1250    ((const unsigned char *)"") // "Pod�acz USB no�nik z \"")

#define KPST_MSG_INSERT_FLASH_1_PL_1250  ((const unsigned char *)"") // "\"")

#define KPST_MSG_ENTER_PWD_PL_1250       ((const unsigned char *)"") // "Wprowad� has�o:")
#define KPST_MSG_BAD_PWD_PL_1250         ((const unsigned char *)"") // "B��dne has�o")

#define KPST_MSG_ENTER_PUK_PL_1250       ((const unsigned char *)"") // "Wprowad� kod licencji no�nika USB:")
#define KPST_MSG_BAD_PUK_PL_1250         ((const unsigned char *)"") // "Niepoprawny kod licencji")

#define KPST_MSG_OBJ_REG_PL_1250         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_PL_1250    ((const unsigned char *)"") // "Prie� naudojant dokument� reikia u�registruoti."
#define KPST_MSG_OBJ_UNREG_INFO_PL_1250  ((const unsigned char *)"") // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1250 ((const unsigned char *)"") // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_PL_1250     ((const unsigned char *)"") // "Dokumento registracija at�aukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250 ((const unsigned char *)"") // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

#define KPST_MSG_BAD_FLASH_PL_1250       ((const unsigned char *)"") // "�is atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_PL_1250 ((const unsigned char *)"") // "Licencijos galiojimas baig�si"
#define KPST_MSG_REST_MONTHS_PL_1250     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d m�nesi�"
#define KPST_MSG_REST_LAST_MONTH_PL_1250 ((const unsigned char *)"") // "Licencijos galiojimas baigsis kit� m�nes�"
#define KPST_MSG_REST_DAYS_PL_1250       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dien�"
#define KPST_MSG_REST_DAY_PL_1250        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_PL_1250      ((const unsigned char *)"") // "�iandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_PL_1250      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrod�"

#define KPST_MSG_BAD_PRODVAR_PL_1250     ((const unsigned char *)"") // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

#define KPST_MSG_UPDATE_FINISHED_PL_1250 ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

#define KPST_MSG_SELDOWN_TITLE_PL_1250   ((const unsigned char *)"") // "Produkto komponent� parsisi�sdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_PL_1250  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"") // "Nauj� serijos leidini� daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1250 ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE_PL_1250    ((const unsigned char *)"") // "Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1250   ((const unsigned char *)"") // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"") // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1250 ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

#define KPST_MSG_CLOSE_PROG_WND_PL_1250  ((const unsigned char *)"") // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

// -----------------------------------------------
#if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define KPST_MSG_PROD_REG_PL_1257        ((const unsigned char *)"") // "Rejestracja programu")
#define KPST_MSG_UNREG_PL_1257           ((const unsigned char *)"") // "Odwo�anie licencji")
#define KPST_MSG_LIC_PL_1257             ((const unsigned char *)"") // "Licencja")
#define KPST_MSG_REG_INFO_PL_1257        ((const unsigned char *)"") // "By uruchomi� program, wymagana jest rejestracja.")
#define KPST_MSG_IVESK_LIC_PL_1257       ((const unsigned char *)"") // "Wprowad� kod licencji, kt�ry otrzyma�e� nabywaj�c produkt.")
#define KPST_MSG_IVESK_LIC_1_PL_1257     ((const unsigned char *)"") // "Vis� kod� galima kopijuoti � pirm� langel�."
#define KPST_MSG_REG_CARD_PL_1257        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_PL_1257         ((const unsigned char *)"") // "Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1257   ((const unsigned char *)"") // "B��dnie wprowadzono kod licencji")

#define KPST_MSG_CHECK_CONN_PL_1257      ((const unsigned char *)"") // "Sprawd�, czy komputer jest pod��czony do Internetu")
#define KPST_MSG_CHECK_CONN_LOC_PL_1257  ((const unsigned char *)"") // "Sprawd�, czy komputer jest pod��czony do sieci")

#define KPST_MSG_REG_SUCC_PL_1257        ((const unsigned char *)"") // "Licencja zosta�a zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1257    ((const unsigned char *)"") // "Licencja ju� jest zarejestrowana")
#define KPST_MSG_REG_UNSUC_PL_1257       ((const unsigned char *)"") // "Licencji nie uda�o si� zarejestrowa� przez Internet.")
#define KPST_MSG_REG_UNSUC_0_PL_1257     ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_PL_1257     ((const unsigned char *)"") // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1257   ((const unsigned char *)"") // "Nieudana rejestracja.")
#define KPST_MSG_DIEG_KOD_PL_1257        ((const unsigned char *)"") // "Kod instalacji:")

#define KPST_MSG_UNREG_INFO_PL_1257      ((const unsigned char *)"") // "Przed przeniesieniem programu na inny komputer licencja powinna by� usuni�ta.")
#define KPST_MSG_UNREG_IVESK_LIC_PL_1257 KPST_MSG_IVESK_LIC_PL_1257

#define KPST_MSG_REG_PERSPEJ_PL_1257     ((const unsigned char *)"") // "Zarejestrowany program b�dzie dzia�a� tylko na tym komputerze!")

#define KPST_MSG_BUT_REG_PL_1257         ((const unsigned char *)"") // "W jaki spos�b zarejestrujesz program:")
#define KPST_MSG_BUT_UNREG_PL_1257       ((const unsigned char *)"") // "W jaki spos�b usuniesz rejestracj� programu:")

#define KPST_MSG_INTERNETU_PL_1257       ((const unsigned char *)"") // "Przez Internet")
#define KPST_MSG_TELEFONU_PL_1257        ((const unsigned char *)"") // "Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1257      ((const unsigned char *)"") // "Odwo�aj")
#define KPST_MSG_CANCEL_UNREG_PL_1257    ((const unsigned char *)"") // "Nie usuwaj")

#define KPST_MSG_SIUSK_PASTU_PL_1257     ((const unsigned char *)"") // "Kod instalacji mo�esz wys�a� poczt� elektroniczn� na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1257    ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoni�c pod nr. tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1257      ((const unsigned char *)"") // "podyktowa� go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1257     ((const unsigned char *)"") // "Wprowad� otrzyman� odpowied� � klucz instalacji.")
#define KPST_MSG_IVESK_RAKTA_1_PL_1257   ((const unsigned char *)"") // "Vis� rakt� galima kopijuoti � pirm� langel�."
#define KPST_MSG_DIEG_RAKTAS_PL_1257     ((const unsigned char *)"") // "Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1257   ((const unsigned char *)"") // "Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1257 ((const unsigned char *)"") // "B��dnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1257   ((const unsigned char *)"") // "Wywo�aj program z p�yty CD")
#define KPST_MSG_BAD_CD_PL_1257          ((const unsigned char *)"") // "Wadliwa pl�yta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1257    ((const unsigned char *)"") // "Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1257    ((const unsigned char *)"") // "Rezultat� rasti nepavyko.\n D�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1257    ((const unsigned char *)"") // "Rezultat� rasti nepavyko.\nJ�s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1257     ((const unsigned char *)"") // ". Rezultatai s�kmingai perkelti � ")

#define KPST_MSG_REG_NOT_ADMIN_PL_1257   ((const unsigned char *)"") // "Dla rejestracji licencji powiniene�\n zalogowa� si� do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1257 ((const unsigned char *)"") // "Dla usuni�cia instalacji produktu powiniene�\n zalogowa� si� do systemu jako administrator")

#define KPST_MSG_NOT_REG_PL_1257         ((const unsigned char *)"") // "Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_INVALID_REG_PL_1257     ((const unsigned char *)"") // "Kod uaktualnienia i podstawowego produktu nie s� zgodne. Zainstaluj produkt ponownie.")

#define KPST_MSG_UNREG_KOD_1_PL_1257     ((const unsigned char *)"") // "Kod usuni�cia")
#define KPST_MSG_UNREG_KOD_PL_1257       ((const unsigned char *)"") // "Kod usuni�cia licencji:              \n")
#define KPST_MSG_ALLREADY_REMOVED_PL_1257   ((const unsigned char *)"") // "Produkt ju� usuni�ty")
#define KPST_MSG_UNREG_SUCC_PL_1257      ((const unsigned char *)"") // "Licencja zosta�a usuni�ta")
#define KPST_MSG_UNREG_UNSUCC_PL_1257    ((const unsigned char *)"") // "Nie uda�o si� usun�� rejestracji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_1_PL_1257  ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."

#define KPST_MSG_REG_NOT_YET_PL_1257     ((const unsigned char *)"") // "Program jeszcze nie by� zarejestrowany. Pon�w rejestracj� podczac wywo�ywania programu poprzez menu �Rejestracja�.")
#define KPST_MSG_INI_NOT_ADMIN_PL_1257   ((const unsigned char *)"") // "Zasoby systemu nie s� dost�pne. Zaloguj si� do systemu jako administrator")

#define KPST_MSG_UNREG_PASTU_PL_1257     ((const unsigned char *)"") // "Kod usuni�cia mo�esz wys�a� poczt� elektronow� na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1257 ((const unsigned char *)"") // "w dniach pracy od godz. 9 do 16 dzwoni�c pod nr. tel. 8-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1257   ((const unsigned char *)"") // "i podyktowa� dla operatora.")

#define KPST_MSG_UNREG_NEGALESIT_PL_1257 /* KPST_MSG_UNREG_TELEF_PL_1257 */ ((const unsigned char *)"") // "Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� zarejestrowa� programu na innym komputerze!")
#define KPST_MSG_INSERT_FLOPPY_PL_1257   ((const unsigned char *)"") // "�d�kite diskel�")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1257   ((const unsigned char *)"") // "Negaliu atverti rezultat� failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1257  ((const unsigned char *)"") // "Negaliu �ra�yti � rezultat� fail�.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1257  ((const unsigned char *)"") // "Negaliu u�daryti rezultat� failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1257     ((const unsigned char *)"") // "Negaliu perskaityti �ra�yto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1257   ((const unsigned char *)"") // "Duomenys ne�sira�o.")
#define KPST_MSG_REFUSE_RESULTS_PL_1257  ((const unsigned char *)"") // "Ar tikrai norite atsisakyti rezultat�?")
#define KPST_MSG_TEST_SUCC_PL_1257       ((const unsigned char *)"") // "Konkurso programin� �ranga �iame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1257      ((const unsigned char *)"") // "Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1257    ((const unsigned char *)"") // "Pod�acz USB no�nik z \"")

#define KPST_MSG_INSERT_FLASH_1_PL_1257  ((const unsigned char *)"") // "\"")

#define KPST_MSG_ENTER_PWD_PL_1257       ((const unsigned char *)"") // "Wprowad� has�o:")
#define KPST_MSG_BAD_PWD_PL_1257         ((const unsigned char *)"") // "B��dne has�o")

#define KPST_MSG_ENTER_PUK_PL_1257       ((const unsigned char *)"") // "Wprowad� kod licencji no�nika USB:")
#define KPST_MSG_BAD_PUK_PL_1257         ((const unsigned char *)"") // "Niepoprawny kod licencji")

#define KPST_MSG_OBJ_REG_PL_1257         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_PL_1257    ((const unsigned char *)"") // "Prie� naudojant dokument� reikia u�registruoti."
#define KPST_MSG_OBJ_UNREG_INFO_PL_1257  ((const unsigned char *)"") // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1257 ((const unsigned char *)"") // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_PL_1257     ((const unsigned char *)"") // "Dokumento registracija at�aukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1257 ((const unsigned char *)"") // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

#define KPST_MSG_BAD_FLASH_PL_1257       ((const unsigned char *)"") // "�is atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_PL_1257 ((const unsigned char *)"") // "Licencijos galiojimas baig�si"
#define KPST_MSG_REST_MONTHS_PL_1257     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d m�nesi�"
#define KPST_MSG_REST_LAST_MONTH_PL_1257 ((const unsigned char *)"") // "Licencijos galiojimas baigsis kit� m�nes�"
#define KPST_MSG_REST_DAYS_PL_1257       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d dien�"
#define KPST_MSG_REST_DAY_PL_1257        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_PL_1257      ((const unsigned char *)"") // "�iandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_PL_1257      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrod�"

#define KPST_MSG_BAD_PRODVAR_PL_1257     ((const unsigned char *)"") // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

#define KPST_MSG_UPDATE_FINISHED_PL_1257 ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

#define KPST_MSG_SELDOWN_TITLE_PL_1257   ((const unsigned char *)"") // "Produkto komponent� parsisi�sdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_PL_1257  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1257 ((const unsigned char *)"") // "Nauj� serijos leidini� daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1257 ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE_PL_1257    ((const unsigned char *)"") // "Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1257   ((const unsigned char *)"") // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1257 ((const unsigned char *)"") // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1257 ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

#define KPST_MSG_CLOSE_PROG_WND_PL_1257  ((const unsigned char *)"") // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

// -----------------------------------------------
#if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define KPST_MSG_PROD_REG_RU        ((const unsigned char *)"") // "Program registration")
#define KPST_MSG_UNREG_RU           ((const unsigned char *)"") // "Registration cancellation")
#define KPST_MSG_LIC_RU             ((const unsigned char *)"") // "Licence")
#define KPST_MSG_REG_INFO_RU        ((const unsigned char *)"") // "To keep program running, licence should be registered.")
#define KPST_MSG_IVESK_LIC_RU       ((const unsigned char *)"") // "Enter licence code acquired together with the product.")
#define KPST_MSG_IVESK_LIC_1_RU     ((const unsigned char *)"") // "Vis� kod� galima kopijuoti � pirm� langel�."
#define KPST_MSG_REG_CARD_RU        ((const unsigned char *)"") // "")
#define KPST_MSG_LIC_KOD_RU         ((const unsigned char *)"") // "Licence code:")
#define KPST_MSG_BLOGAS_LIC_KODAS_RU   ((const unsigned char *)"") // "Invalid licence code")
#define KPST_MSG_CHECK_CONN_RU      ((const unsigned char *)"") // "Check your computer Internet connection")
#define KPST_MSG_CHECK_CONN_LOC_RU  ((const unsigned char *)"") // "Check your computer network connection")
#define KPST_MSG_REG_SUCC_RU        ((const unsigned char *)"") // "Licence registered successfully")
#define KPST_MSG_ALLREADY_REG_RU    ((const unsigned char *)"") // "Licence already registered")
#define KPST_MSG_REG_UNSUC_RU       ((const unsigned char *)"") // "Unsuccessful licence registration by Internet.")
#define KPST_MSG_REG_UNSUC_0_RU     ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_RU     ((const unsigned char *)"") // "esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius.")
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
#define KPST_MSG_IVESK_RAKTA_1_RU   ((const unsigned char *)"") // "Vis� rakt� galima kopijuoti � pirm� langel�."
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
#define KPST_MSG_UNREG_UNSUCC_1_RU  ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�."

#define KPST_MSG_REG_NOT_YET_RU     ((const unsigned char *)"") // "Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command �Registration�.")
#define KPST_MSG_REG_NOT_YET_RU_0   ((const unsigned char *)"") // "Product licence not yet registered. Procedure of the registration should be proceeded using Start Menu command �Registration�.")

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

#define KPST_MSG_INSERT_FLASH_RU    ((const unsigned char *)"") // "Put the USB flash drive with �")
#define KPST_MSG_INSERT_FLASH_1_RU  ((const unsigned char *)"") // "�")

#define KPST_MSG_ENTER_PWD_RU       ((const unsigned char *)"") // "Enter the password:")
#define KPST_MSG_BAD_PWD_RU         ((const unsigned char *)"") // "Password incorrect")
#define KPST_MSG_ENTER_PUK_RU       ((const unsigned char *)"") // "Enter the USB flash drive licence code:")
#define KPST_MSG_BAD_PUK_RU         ((const unsigned char *)"") // "Licence code invalid")

#define KPST_MSG_OBJ_REG_RU         ((const unsigned char *)"") // "Dokumento registracija"
#define KPST_MSG_OBJ_REG_INFO_RU    ((const unsigned char *)"") // "Prie� naudojant dokument� reikia u�registruoti."
#define KPST_MSG_OBJ_UNREG_INFO_RU  ((const unsigned char *)"") // "Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�."
#define KPST_MSG_OBJ_REG_PERSPEJ_RU ((const unsigned char *)"") // "U�registruotas dokumentas atsivers tik �iame kompiuteryje!"

#define KPST_MSG_OBJ_REG_NOT_YET_RU     ((const unsigned char *)"") // "Dokumento registracija at�aukta."
#define KPST_MSG_OBJ_UNREG_NEGALESIT_RU ((const unsigned char *)"") // "To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!"

#define KPST_MSG_BAD_FLASH_RU       ((const unsigned char *)"") // "�is atnaujinimas skirtas atmintukui %s"

#define KPST_MSG_LICENCE_EXPIRED_RU ((const unsigned char *)"") // "Licencijos galiojimas baig�si"
#define KPST_MSG_REST_MONTHS_RU     ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %d m�nesi�"
#define KPST_MSG_REST_LAST_MONTH_RU ((const unsigned char *)"") // "Licencijos galiojimas baigsis kit� m�nes�"
#define KPST_MSG_REST_DAYS_RU       ((const unsigned char *)"") // "Licencijos galiojimas baigsis po %ld dien�"
#define KPST_MSG_REST_DAY_RU        ((const unsigned char *)"") // "Rytoj baigsis licencijos galiojimas"
#define KPST_MSG_REST_TODAY_RU      ((const unsigned char *)"") // "�iandien baigiasi licencijos galiojimas"
#define KPST_MSG_TIME_CHEAT_RU      ((const unsigned char *)"") // "Teisingai nustatykite sistemos laikrod�"

#define KPST_MSG_BAD_PRODVAR_RU     ((const unsigned char *)"") // "J�s� atmintuko versija pasenusi. Paleiskite atmintuke esant� produkt�, paspauskite mygtuk� �i�, parsisi�skite atnaujinim� ir j� �diekite."

#define KPST_MSG_UPDATE_FINISHED_RU ((const unsigned char *)"") // "Atnaujinimas baigtas. Paspauskite mygtuk� �Baigti�. Po to paleiskite MIKO knyg�."

#define KPST_MSG_SELDOWN_TITLE_RU   ((const unsigned char *)"") // "Produkto komponent� parsisi�sdinimas: "
#define KPST_MSG_SELDOWN_PROMPT_RU  ((const unsigned char *)"") // "Panaikinkite varneles tiems serijos leidiniams, kuri� parsisi�sti nenorite:"
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_RU ((const unsigned char *)"") // "Nauj� serijos leidini� daugiau netikrinti:"
#define KPST_MSG_SELDOWN_BUT_PROMPT_RU ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\njei t�sti jau turim� leidini� naudojim� � �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE_RU    ((const unsigned char *)"") // "Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT_RU   ((const unsigned char *)"") // "J�s� turimam produktui rasti atnaujinimai.\nPanaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_RU ((const unsigned char *)"") // "Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_RU ((const unsigned char *)"") // "Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\njei ne � �At�aukti�.")

#define KPST_MSG_CLOSE_PROG_WND_RU  ((const unsigned char *)"") // "Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#endif // #ifndef kpstmsg_included
