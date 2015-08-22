// -----------------------------------------
// kpstmsg_lt.h
// programos paleidimo aplikaciju pranesimai
// liet. kalba
// 

#ifndef kpstmsg_lt_included
#define kpstmsg_lt_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

// #define KPST_MSG_PROD_REG_LT        ((const unsigned char *)"Produkto registracija")
#define KPST_MSG_PROD_REG_LT        ((const unsigned char *)"Produkto aktyvacija")
// #define KPST_MSG_UNREG_LT           ((const unsigned char *)"Registracijos naikinimas")
#define KPST_MSG_UNREG_LT           ((const unsigned char *)"Aktyvacijos naikinimas")
#define KPST_MSG_LIC_LT             ((const unsigned char *)"Licencija")

// #define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Kad programa veikt�, j� reikia u�registruoti. �veskite licencijos kod�,")
// #define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Norint naudotis produktu, j� reikia u�registruoti.")
// #define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Jei norite naudotis produktu, turite j� u�registruoti.")
#define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Jei norite naudotis produktu, turite j� aktyvuoti.")

// #define KPST_MSG_IVESK_LIC_LT    ((const unsigned char *)"kur� rasite registracijos kortel�je arba ant kompaktin�s plok�tel�s.")
// #define KPST_MSG_IVESK_LIC_LT    ((const unsigned char *)"kur� gavote �sigydami produkt�.")
#define KPST_MSG_IVESK_LIC_LT       ((const unsigned char *)"�veskite licencijos kod�, kur� gavote �sigydami produkt�.")
#define KPST_MSG_IVESK_LIC_1_LT     ((const unsigned char *)"(Vis� kod� galima kopijuoti � pirm� langel�.)")
#define KPST_MSG_REG_CARD_LT        ((const unsigned char *)"")  // "J� rasite registracijos kortel�je"
#define KPST_MSG_LIC_KOD_LT         ((const unsigned char *)"Licencijos kodas:")
#define KPST_MSG_BLOGAS_LIC_KODAS_LT   ((const unsigned char *)"Neteisingai �vestas licencijos kodas")
// #define KPST_MSG_CHECK_CONN_LT   ((const unsigned char *)"Patikrinkite, ar kompiuteris prijungtas prie interneto")
#define KPST_MSG_CHECK_CONN_LT      KP_MSG_FIREWALL_LT
// #define KPST_MSG_CHECK_CONN_LOC_LT  ((const unsigned char *)"Patikrinkite, ar kompiuteris prijungtas prie tinklo")
#define KPST_MSG_CHECK_CONN_LOC_LT  ((const unsigned char *)"Neleista prisijungti prie lokalaus kompiuteri� tinklo. Patikrinkite J�s� ugniasien�s parinktis � pabandykite �traukti %s � s�ra�� program�, kurioms leid�iama kreiptis � internet�.")
// #define KPST_MSG_REG_SUCC_LT        ((const unsigned char *)"%s\n                                       \nLicencija u�registruota s�kmingai") 
#define KPST_MSG_REG_SUCC_LT        ((const unsigned char *)"%s\n                                       \nLicencija aktyvuota s�kmingai") 
// #define KPST_MSG_ALLREADY_REG_LT    ((const unsigned char *)"%s\n                                       \nLicencija jau u�registruota") 
#define KPST_MSG_ALLREADY_REG_LT    ((const unsigned char *)"%s\n                                       \nLicencija jau aktyvuota") 
// #define KPST_MSG_REG_UNSUC_LT       ((const unsigned char *)"Internetu licencijos u�registruoti nepavyko.")
#define KPST_MSG_REG_UNSUC_LT       ((const unsigned char *)"Internetu licencijos aktyvuoti nepavyko.")
#define KPST_MSG_REG_UNSUC_0_LT     ((const unsigned char *)"Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_LT     ((const unsigned char *)"esan�i� nuorod�, o gaut� atsakym� �kopijuoti � diegimo kodo laukelius.")
// #define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"Licencijos u�registruoti nepavyko.")
// #define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"U�siregistruoti nepavyko.")
#define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"Aktyvuoti nepavyko.")
#define KPST_MSG_DIEG_KOD_LT        ((const unsigned char *)"Diegimo kodas:")

// #define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"Licencijos registracija naikinama prie� perkeliant program� � kit� kompiuter�.")
// #define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"Licencijos registracija naikinama prie� produkt� perkeliant � kit� kompiuter�.")
#define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"Licencijos aktyvacija naikinama prie� produkt� perkeliant � kit� kompiuter�.")

// #define KPST_MSG_UNREG_IVESK_LIC_LT ((const unsigned char *)"�veskite licencijos kod�, kur� gavote �sigydami produkt�.")
#define KPST_MSG_UNREG_IVESK_LIC_LT KPST_MSG_IVESK_LIC_LT

// #define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"U�registruota programa veiks tik �iame kompiuteryje!")
// #define KPST_MSG_REG_PERSPEJ_LT        ((const unsigned char *)"{\\cf6\\lang1031\\langfe1033\\highlight16\\langnp1031 U\\'9eregistruota programa veiks tik \\'9aiame kompiuteryje!\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~}")
// #define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"U�registruotas produktas veiks tik �iame kompiuteryje!")
#define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"Aktyvuotas produktas veiks tik �iame kompiuteryje!")

// #define KPST_MSG_BUT_REG_LT         ((const unsigned char *)"Kaip registruosite?")
#define KPST_MSG_BUT_REG_LT         ((const unsigned char *)"Kaip aktyvuosite?")
#define KPST_MSG_BUT_UNREG_LT       ((const unsigned char *)"Kaip naikinsite?")

#define KPST_MSG_INTERNETU_LT       ((const unsigned char *)"Internetu")
#define KPST_MSG_TELEFONU_LT        ((const unsigned char *)"Telefonu")
#define KPST_MSG_CANCEL_REG_LT      ((const unsigned char *)"At�aukti") // "Neregistruoti")
#define KPST_MSG_CANCEL_UNREG_LT    ((const unsigned char *)"Nenaikinti")

#define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Nes�km�s atveju diegimo kod� galite i�si�sti elektroniniu pa�tu,") // !!!! TODO perkelti � kitas kalbas
#ifdef KPST_ARKIM
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kod� galite i�si�sti elektroniniu pa�tu arkim@tev.lt")
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kod� galite i�si�sti elektroniniu pa�tu, adresu arkim@tev.lt arba")
#define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)" adresu arkim@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti � kitas kalbas
#endif
#ifdef KPST_TEV
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kod� galite i�si�sti elektroniniu pa�tu tech@tev.lt")
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kod� galite i�si�sti elektroniniu pa�tu, adresu tech@tev.lt arba")
#define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"adresu tech@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti � kitas kalbas
#endif
// #define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"arba darbo dienomis nuo 9 val. iki 16 val.")
// #define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_LT      ((const unsigned char *)"paskambin� tel. 8-5-2729318 padiktuoti operatoriui.") // !!!! TODO perkelti � kitas kalbas
// #define KPST_MSG_DIKT_TELEF_LT      ((const unsigned char *)"padiktuoti operatoriui.")

// #define KPST_MSG_IVESK_RAKTA_LT     ((const unsigned char *)"�veskite gaut� atsakym� � diegimo rakt�.")
#define KPST_MSG_IVESK_RAKTA_LT     ((const unsigned char *)"�veskite/�kopijuokite gaut� atsakym� � diegimo rakt�.") // !!!! TODO perkelti � kitas kalbas
#define KPST_MSG_IVESK_RAKTA_1_LT   ((const unsigned char *)"(Vis� rakt� galima kopijuoti � pirm� langel�.)")
#define KPST_MSG_DIEG_RAKTAS_LT     ((const unsigned char *)"Diegimo raktas:")
#define KPST_MSG_DIEG_RAKTAS_1_LT   ((const unsigned char *)"Diegimo raktas")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_LT ((const unsigned char *)"Neteisingai �vestas diegimo raktas")


#define KPST_MSG_START_FROM_CD_LT   ((const unsigned char *)"Program� paleiskite i� kompaktin�s plok�tel�s") // ((const unsigned char *)"Program� paleiskite i� kompaktinio disko")
#define KPST_MSG_BAD_CD_LT          ((const unsigned char *)"Bloga kompaktin� plok�tel�") // ((const unsigned char *)"Blogas kompaktinis diskas")

#ifdef KPST_ARKIM
// #define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu arkim@tev.lt")
#define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu arkim@tev.lt")
// #define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultat� rasti nepavyko.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu arkim@tev.lt ")
#define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultat� rasti nepavyko.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu arkim@tev.lt ")
#endif
#ifdef KPST_TEV
// #define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu tech@tev.lt")
#define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt")
// #define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultat� rasti nepavyko.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultat� rasti nepavyko.\nD�l technin�s pagalbos kreipkit�s elektroniniu pa�tu, adresu tech@tev.lt ")
#endif
// #define KPST_MSG_REZ_NFOUND_2_LT    ((const unsigned char *)"Rezultat� rasti nepavyko.\nJ�s esate %s, OS %s.\nPabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_NFOUND_2_LT    ((const unsigned char *)"Rezultat� rasti nepavyko.\nJ�s esate %s, OS %s.\nPabandykite prisijungti privilegijuotu Windows vartotoju.")
#define KPST_MSG_REZ_SUCCESS_LT     ((const unsigned char *)". Rezultatai s�kmingai perkelti � ")

// #define KPST_MSG_REG_NOT_ADMIN_LT   ((const unsigned char *)"Norint u�registruoti licencij�, reikia sistemos\nadministratoriaus teisi�")
#define KPST_MSG_REG_NOT_ADMIN_LT   ((const unsigned char *)"Licencijos aktyvacijai reikia privilegijuoto\nWindows vartotojo teisi�")
// #define KPST_MSG_UNREG_NOT_ADMIN_LT ((const unsigned char *)"Nor�dami panaikinti produkto diegim�,\nu�siregistruokite sistemos administratoriumi")
#define KPST_MSG_UNREG_NOT_ADMIN_LT ((const unsigned char *)"Jei norite panaikinti produkto diegim�,\nprisijunkite privilegijuotu Windows vartotoju")
// #define KPST_MSG_NOT_REG_LT         ((const unsigned char *)"Produkto licencija dar neu�registruota")
#define KPST_MSG_NOT_REG_LT         ((const unsigned char *)"Produkto licencija dar neaktyvuota")
// #define KPST_MSG_INVALID_REG_LT     ((const unsigned char *)"Produktas u�registruotas netinkamu licencijos kodu")
#define KPST_MSG_INVALID_REG_LT     ((const unsigned char *)"Papildymo ir pagrindinio produkto licencij� kodai nesutampa. Pakartokite produkto diegim�.")

#define KPST_MSG_UNREG_KOD_1_LT     ((const unsigned char *)"I�metimo kodas")
#define KPST_MSG_UNREG_KOD_LT       ((const unsigned char *)"Licencijos i�metimo kodas:              \n")
#define KPST_MSG_ALLREADY_REMOVED_LT   ((const unsigned char *)"%s\n                                       \nProduktas jau i�mestas")
// #define KPST_MSG_UNREG_SUCC_LT      ((const unsigned char *)"Licencijos diegimas panaikintas s�kmingai") 
#define KPST_MSG_UNREG_SUCC_LT      ((const unsigned char *)"Licencijos aktyvacija panaikinta s�kmingai") 
// #define KPST_MSG_UNREG_UNSUCC_LT    ((const unsigned char *)"Internetu registracijos panaikinti nepavyko.")
#define KPST_MSG_UNREG_UNSUCC_LT    ((const unsigned char *)"Internetu aktyvacijos panaikinti nepavyko.")
#define KPST_MSG_UNREG_UNSUCC_1_LT  ((const unsigned char *)"Pabandykite nar�ykle atverti �emiau esan�i� nuorod�.")

// #define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Programa dar neu�registruota. Registracijos proced�r� tur�site pakartoti paleidimo meniu komanda �Registracija�.")
// #define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Produktas dar neu�registruotas. Registracijos proced�r� tur�site pakartoti paleidimo meniu komanda �Registracija�.")
// #define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Produktas dar neaktyvuotas. Aktyvacijos proced�r� tur�site pakartoti paleidimo meniu komanda �Aktyvacija�.")
#define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Produktas dar neaktyvuotas. Aktyvacijos proced�r� tur�site pakartoti.")

// #define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"Produkto diegimui reikia sistemos administratoriaus teisi�"
// #define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"Sistemos resursai nepasiekiami, u�siregistruokite administratoriumi") 
#define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"Sistemos resursai nepasiekiami, prisijunkite privilegijuotu Windows vartotoju") 

#define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"Nes�km�s atveju i�metimo kod� i�si�skite elektroniniu pa�tu,") // !!!! TODO perkelti � kitas kalbas
#ifdef KPST_ARKIM
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"I�metimo kod� i�si�skite elektroniniu pa�tu arkim@tev.lt ")
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"I�metimo kod� i�si�skite elektroniniu pa�tu, adresu arkim@tev.lt arba")
#define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"adresu arkim@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti � kitas kalbas
#endif
#ifdef KPST_TEV
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"I�metimo kod� i�si�skite elektroniniu pa�tu tech@tev.lt ")
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"I�metimo kod� i�si�skite elektroniniu pa�tu, adresu tech@tev.lt arba")
#define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"adresu tech@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti � kitas kalbas
#endif
// #define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"darbo dienomis nuo 9 val. iki 16 val. paskambin� tel. 8-5-2729318")
// #define KPST_MSG_UNREG_DIKT_TELEF_LT   ((const unsigned char *)"padiktuokite operatoriui.")
#define KPST_MSG_UNREG_DIKT_TELEF_LT   ((const unsigned char *)"paskambin� tel. 8-5-2729318, padiktuokite operatoriui.") // !!!! TODO perkelti � kitas kalbas

// #define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"To nepadar�, kitame kompiuteryje programos u�registruoti negal�site!")
// #define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"To nepadar�, kitame kompiuteryje produkto u�registruoti negal�site!")
#define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"To nepadar�, kitame kompiuteryje produkto aktyvuoti negal�site!")

#define KPST_MSG_INSERT_FLOPPY_LT   ((const unsigned char *)"�d�kite diskel�")
#define KPST_MSG_UNABLE_OPEN_REZFILE_LT   ((const unsigned char *)"Negaliu atverti rezultat� failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_LT  ((const unsigned char *)"Negaliu �ra�yti � rezultat� fail�.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_LT  ((const unsigned char *)"Negaliu u�daryti rezultat� failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_LT     ((const unsigned char *)"Negaliu perskaityti �ra�yto failo.")
#define KPST_MSG_COULDNT_WRITE_LT   ((const unsigned char *)"Duomenys ne�sira�o.")
#define KPST_MSG_REFUSE_RESULTS_LT  ((const unsigned char *)"Ar tikrai norite atsisakyti rezultat�?")
#define KPST_MSG_TEST_SUCC_LT       ((const unsigned char *)"Konkurso programin� �ranga �iame kompiuteryje veikia tinkamai     ") // "�is kompiuteris parengtas darbui su programine priemone Acrobat Reader CE" // "Duomen� surinkimo testas baig�si s�kmingai"

#ifdef KPST_ARKIM
// #define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu arkim@tev.lt")
#define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� aplanko c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu, adresu arkim@tev.lt")
#endif

#ifdef KPST_TEV
// #define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu tech@tev.lt")
#define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultat� suformuoti nepavyko.\nPra�ome suarchyvuot� aplanko c:\\arkim\\rezultatai turin� atsi�sti elektroniniu pa�tu, adresu tech@tev.lt")
#endif

// #define KPST_MSG_INSERT_FLASH_LT    ((const unsigned char *)"�ki�kite atmintuk� su programos �")
#define KPST_MSG_INSERT_FLASH_LT    ((const unsigned char *)"�ki�kite atmintuk� su �")
// #define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"� kodu")
// #define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"�")
#define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"�")

#define KPST_MSG_ENTER_PWD_LT       ((const unsigned char *)"�veskite slapta�od�:")
#define KPST_MSG_BAD_PWD_LT         ((const unsigned char *)"Slapta�odis neteisingas")
#define KPST_MSG_ENTER_PUK_LT       ((const unsigned char *)"�veskite atmintuko licencijos kod�:")
#define KPST_MSG_BAD_PUK_LT         ((const unsigned char *)"Neteisingas licencijos kodas")


// #define KPST_MSG_OBJ_REG_LT         ((const unsigned char *)"Dokumento registracija")
#define KPST_MSG_OBJ_REG_LT         ((const unsigned char *)"Dokumento aktyvacija") // KPST_MSG_PROD_REG_LT
// #define KPST_MSG_OBJ_REG_INFO_LT    ((const unsigned char *)"Prie� naudojant dokument� reikia u�registruoti.")
#define KPST_MSG_OBJ_REG_INFO_LT    ((const unsigned char *)"Prie� naudojant dokument� reikia aktyvuoti.") // KPST_MSG_REG_INFO_LT
// #define KPST_MSG_OBJ_UNREG_INFO_LT  ((const unsigned char *)"Licencijos registracija naikinama prie� dokumento perk�lim� � kit� kompiuter�.") 
#define KPST_MSG_OBJ_UNREG_INFO_LT  ((const unsigned char *)"Licencijos aktyvacija naikinama prie� dokumento perk�lim� � kit� kompiuter�.") // KPST_MSG_UNREG_INFO_LT 
// #define KPST_MSG_OBJ_REG_PERSPEJ_LT ((const unsigned char *)"U�registruotas dokumentas atsivers tik �iame kompiuteryje!")
#define KPST_MSG_OBJ_REG_PERSPEJ_LT ((const unsigned char *)"Aktyvuotas dokumentas atsivers tik �iame kompiuteryje!") // KPST_MSG_REG_PERSPEJ_LT

// #define KPST_MSG_OBJ_REG_NOT_YET_LT     ((const unsigned char *)"Dokumento registracija at�aukta.")
#define KPST_MSG_OBJ_REG_NOT_YET_LT     ((const unsigned char *)"Dokumento aktyvacija at�aukta.") // KPST_MSG_REG_NOT_YET_LT
// #define KPST_MSG_OBJ_UNREG_NEGALESIT_LT ((const unsigned char *)"To nepadar�, kitame kompiuteryje dokumento u�registruoti negal�site!") // KPST_MSG_UNREG_NEGALESIT_LT
#define KPST_MSG_OBJ_UNREG_NEGALESIT_LT ((const unsigned char *)"To nepadar�, kitame kompiuteryje dokumento aktyvuoti negal�site!") // KPST_MSG_UNREG_NEGALESIT_LT

#define KPST_MSG_BAD_FLASH_LT       ((const unsigned char *)"�is atnaujinimas skirtas atmintukui %s")

#define KPST_MSG_LICENCE_EXPIRED_LT ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baig�si")
#define KPST_MSG_REST_MONTHS_LT     ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigsis po %ld m�nesi�")
#define KPST_MSG_REST_LAST_MONTH_LT ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigsis kit� m�nes�")
#define KPST_MSG_REST_DAYS_LT       ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigsis po %ld dien�")
#define KPST_MSG_REST_DAY_LT        ((const unsigned char *)"%s\n                                       \nRytoj baigsis licencijos galiojimas")
#define KPST_MSG_REST_TODAY_LT      ((const unsigned char *)"%s\n                                       \n�iandien baigiasi licencijos galiojimas")
#define KPST_MSG_TIME_CHEAT_LT      ((const unsigned char *)"Teisingai nustatykite sistemos laikrod�")

#define KPST_MSG_BAD_PRODVAR_LT     ((const unsigned char *)"J�s naudojate pasenusi� produkto versij�. Paleiskite produkt�, paspauskite versijos tikrinimo mygtuk� �i�, parsisi�sdinkite pasi�lyt� atnaujinim� ir j� �diekite.")

// #define KPST_MSG_UPDATE_FINISHED_LT ((const unsigned char *)"Atnaujinimas baigtas. Paspauskite �Baigti�. Po to paleiskite MIKO knyg�.")
#define KPST_MSG_UPDATE_FINISHED_LT ((const unsigned char *)"       Spragtel�kite mygtuk� �Baigti�.         \n       Po to paleiskite MIKO knyg�.         ")

// #define KPST_MSG_SELDOWN_TITLE_LT   ((const unsigned char *)"Produkto komponent� parsisi�sdinimas")
#define KPST_MSG_SELDOWN_TITLE_LT   ((const unsigned char *)"Serijos leidini� parsisi�sdinimas")
#define KPST_MSG_SELDOWN_PROMPT_LT  ((const unsigned char *)"J�s� turima serija turi nauj� leidini�.                          \n"\
                                                            "Panaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_LT ((const unsigned char *)"Nauj� serijos leidini� daugiau nebetikrinti:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_LT ((const unsigned char *)"Jei norite parsisi�sdinti pa�ym�tus leidinius, spragtel�kite mygtuk� �Gerai�,\n"\
                                                               "jei t�sti jau turim� leidini� naudojim� � �At�aukti�.                        ")

#define KPST_MSG_SELUPD_TITLE_LT   ((const unsigned char *)"Produkto atnaujinim� parsisi�sdinimas")
#define KPST_MSG_SELUPD_PROMPT_LT  ((const unsigned char *)"J�s� turimam produktui rasti atnaujinimai.                       \n"\
                                                           "Panaikinkite varneles tiems i� j�, kuri� parsisi�sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_LT ((const unsigned char *)"Nauj� produkto atnaujinim� daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_LT ((const unsigned char *)"Jei norite parsisi�sdinti pa�ym�tus atnaujinimus, spragtel�kite mygtuk� �Gerai�,\n"\
                                                              "jei ne � �At�aukti�.                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_LT ((const unsigned char *)"Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef kpstmsg_lt_included
