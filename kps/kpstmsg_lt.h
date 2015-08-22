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

// #define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Kad programa veiktø, jà reikia uþregistruoti. Áveskite licencijos kodà,")
// #define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Norint naudotis produktu, já reikia uþregistruoti.")
// #define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Jei norite naudotis produktu, turite já uþregistruoti.")
#define KPST_MSG_REG_INFO_LT        ((const unsigned char *)"Jei norite naudotis produktu, turite já aktyvuoti.")

// #define KPST_MSG_IVESK_LIC_LT    ((const unsigned char *)"kurá rasite registracijos kortelëje arba ant kompaktinës plokðtelës.")
// #define KPST_MSG_IVESK_LIC_LT    ((const unsigned char *)"kurá gavote ásigydami produktà.")
#define KPST_MSG_IVESK_LIC_LT       ((const unsigned char *)"Áveskite licencijos kodà, kurá gavote ásigydami produktà.")
#define KPST_MSG_IVESK_LIC_1_LT     ((const unsigned char *)"(Visà kodà galima kopijuoti á pirmà langelá.)")
#define KPST_MSG_REG_CARD_LT        ((const unsigned char *)"")  // "Já rasite registracijos kortelëje"
#define KPST_MSG_LIC_KOD_LT         ((const unsigned char *)"Licencijos kodas:")
#define KPST_MSG_BLOGAS_LIC_KODAS_LT   ((const unsigned char *)"Neteisingai ávestas licencijos kodas")
// #define KPST_MSG_CHECK_CONN_LT   ((const unsigned char *)"Patikrinkite, ar kompiuteris prijungtas prie interneto")
#define KPST_MSG_CHECK_CONN_LT      KP_MSG_FIREWALL_LT
// #define KPST_MSG_CHECK_CONN_LOC_LT  ((const unsigned char *)"Patikrinkite, ar kompiuteris prijungtas prie tinklo")
#define KPST_MSG_CHECK_CONN_LOC_LT  ((const unsigned char *)"Neleista prisijungti prie lokalaus kompiuteriø tinklo. Patikrinkite Jûsø ugniasienës parinktis – pabandykite átraukti %s á sàraðà programø, kurioms leidþiama kreiptis á internetà.")
// #define KPST_MSG_REG_SUCC_LT        ((const unsigned char *)"%s\n                                       \nLicencija uþregistruota sëkmingai") 
#define KPST_MSG_REG_SUCC_LT        ((const unsigned char *)"%s\n                                       \nLicencija aktyvuota sëkmingai") 
// #define KPST_MSG_ALLREADY_REG_LT    ((const unsigned char *)"%s\n                                       \nLicencija jau uþregistruota") 
#define KPST_MSG_ALLREADY_REG_LT    ((const unsigned char *)"%s\n                                       \nLicencija jau aktyvuota") 
// #define KPST_MSG_REG_UNSUC_LT       ((const unsigned char *)"Internetu licencijos uþregistruoti nepavyko.")
#define KPST_MSG_REG_UNSUC_LT       ((const unsigned char *)"Internetu licencijos aktyvuoti nepavyko.")
#define KPST_MSG_REG_UNSUC_0_LT     ((const unsigned char *)"Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_LT     ((const unsigned char *)"esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius.")
// #define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"Licencijos uþregistruoti nepavyko.")
// #define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"Uþsiregistruoti nepavyko.")
#define KPST_MSG_REG_UNSUC_LOC_LT   ((const unsigned char *)"Aktyvuoti nepavyko.")
#define KPST_MSG_DIEG_KOD_LT        ((const unsigned char *)"Diegimo kodas:")

// #define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"Licencijos registracija naikinama prieð perkeliant programà á kità kompiuterá.")
// #define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"Licencijos registracija naikinama prieð produktà perkeliant á kità kompiuterá.")
#define KPST_MSG_UNREG_INFO_LT      ((const unsigned char *)"Licencijos aktyvacija naikinama prieð produktà perkeliant á kità kompiuterá.")

// #define KPST_MSG_UNREG_IVESK_LIC_LT ((const unsigned char *)"Áveskite licencijos kodà, kurá gavote ásigydami produktà.")
#define KPST_MSG_UNREG_IVESK_LIC_LT KPST_MSG_IVESK_LIC_LT

// #define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"Uþregistruota programa veiks tik ðiame kompiuteryje!")
// #define KPST_MSG_REG_PERSPEJ_LT        ((const unsigned char *)"{\\cf6\\lang1031\\langfe1033\\highlight16\\langnp1031 U\\'9eregistruota programa veiks tik \\'9aiame kompiuteryje!\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~\\~}")
// #define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"Uþregistruotas produktas veiks tik ðiame kompiuteryje!")
#define KPST_MSG_REG_PERSPEJ_LT     ((const unsigned char *)"Aktyvuotas produktas veiks tik ðiame kompiuteryje!")

// #define KPST_MSG_BUT_REG_LT         ((const unsigned char *)"Kaip registruosite?")
#define KPST_MSG_BUT_REG_LT         ((const unsigned char *)"Kaip aktyvuosite?")
#define KPST_MSG_BUT_UNREG_LT       ((const unsigned char *)"Kaip naikinsite?")

#define KPST_MSG_INTERNETU_LT       ((const unsigned char *)"Internetu")
#define KPST_MSG_TELEFONU_LT        ((const unsigned char *)"Telefonu")
#define KPST_MSG_CANCEL_REG_LT      ((const unsigned char *)"Atðaukti") // "Neregistruoti")
#define KPST_MSG_CANCEL_UNREG_LT    ((const unsigned char *)"Nenaikinti")

#define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Nesëkmës atveju diegimo kodà galite iðsiøsti elektroniniu paðtu,") // !!!! TODO perkelti á kitas kalbas
#ifdef KPST_ARKIM
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kodà galite iðsiøsti elektroniniu paðtu arkim@tev.lt")
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kodà galite iðsiøsti elektroniniu paðtu, adresu arkim@tev.lt arba")
#define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)" adresu arkim@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti á kitas kalbas
#endif
#ifdef KPST_TEV
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kodà galite iðsiøsti elektroniniu paðtu tech@tev.lt")
// #define KPST_MSG_SIUSK_PASTU_LT     ((const unsigned char *)"Diegimo kodà galite iðsiøsti elektroniniu paðtu, adresu tech@tev.lt arba")
#define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"adresu tech@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti á kitas kalbas
#endif
// #define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"arba darbo dienomis nuo 9 val. iki 16 val.")
// #define KPST_MSG_DARBO_LAIKAS_LT    ((const unsigned char *)"darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318")
#define KPST_MSG_DIKT_TELEF_LT      ((const unsigned char *)"paskambinæ tel. 8-5-2729318 padiktuoti operatoriui.") // !!!! TODO perkelti á kitas kalbas
// #define KPST_MSG_DIKT_TELEF_LT      ((const unsigned char *)"padiktuoti operatoriui.")

// #define KPST_MSG_IVESK_RAKTA_LT     ((const unsigned char *)"Áveskite gautà atsakymà – diegimo raktà.")
#define KPST_MSG_IVESK_RAKTA_LT     ((const unsigned char *)"Áveskite/ákopijuokite gautà atsakymà – diegimo raktà.") // !!!! TODO perkelti á kitas kalbas
#define KPST_MSG_IVESK_RAKTA_1_LT   ((const unsigned char *)"(Visà raktà galima kopijuoti á pirmà langelá.)")
#define KPST_MSG_DIEG_RAKTAS_LT     ((const unsigned char *)"Diegimo raktas:")
#define KPST_MSG_DIEG_RAKTAS_1_LT   ((const unsigned char *)"Diegimo raktas")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_LT ((const unsigned char *)"Neteisingai ávestas diegimo raktas")


#define KPST_MSG_START_FROM_CD_LT   ((const unsigned char *)"Programà paleiskite ið kompaktinës plokðtelës") // ((const unsigned char *)"Programà paleiskite ið kompaktinio disko")
#define KPST_MSG_BAD_CD_LT          ((const unsigned char *)"Bloga kompaktinë plokðtelë") // ((const unsigned char *)"Blogas kompaktinis diskas")

#ifdef KPST_ARKIM
// #define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu arkim@tev.lt")
#define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu arkim@tev.lt")
// #define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultatø rasti nepavyko.\nDël techninës pagalbos kreipkitës elektroniniu paðtu arkim@tev.lt ")
#define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultatø rasti nepavyko.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu arkim@tev.lt ")
#endif
#ifdef KPST_TEV
// #define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu tech@tev.lt")
#define KPST_MSG_REZ_NESUFORM_LT    ((const unsigned char *)"Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt")
// #define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultatø rasti nepavyko.\nDël techninës pagalbos kreipkitës elektroniniu paðtu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_1_LT    ((const unsigned char *)"Rezultatø rasti nepavyko.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt ")
#endif
// #define KPST_MSG_REZ_NFOUND_2_LT    ((const unsigned char *)"Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\nPabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_NFOUND_2_LT    ((const unsigned char *)"Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\nPabandykite prisijungti privilegijuotu Windows vartotoju.")
#define KPST_MSG_REZ_SUCCESS_LT     ((const unsigned char *)". Rezultatai sëkmingai perkelti á ")

// #define KPST_MSG_REG_NOT_ADMIN_LT   ((const unsigned char *)"Norint uþregistruoti licencijà, reikia sistemos\nadministratoriaus teisiø")
#define KPST_MSG_REG_NOT_ADMIN_LT   ((const unsigned char *)"Licencijos aktyvacijai reikia privilegijuoto\nWindows vartotojo teisiø")
// #define KPST_MSG_UNREG_NOT_ADMIN_LT ((const unsigned char *)"Norëdami panaikinti produkto diegimà,\nuþsiregistruokite sistemos administratoriumi")
#define KPST_MSG_UNREG_NOT_ADMIN_LT ((const unsigned char *)"Jei norite panaikinti produkto diegimà,\nprisijunkite privilegijuotu Windows vartotoju")
// #define KPST_MSG_NOT_REG_LT         ((const unsigned char *)"Produkto licencija dar neuþregistruota")
#define KPST_MSG_NOT_REG_LT         ((const unsigned char *)"Produkto licencija dar neaktyvuota")
// #define KPST_MSG_INVALID_REG_LT     ((const unsigned char *)"Produktas uþregistruotas netinkamu licencijos kodu")
#define KPST_MSG_INVALID_REG_LT     ((const unsigned char *)"Papildymo ir pagrindinio produkto licencijø kodai nesutampa. Pakartokite produkto diegimà.")

#define KPST_MSG_UNREG_KOD_1_LT     ((const unsigned char *)"Iðmetimo kodas")
#define KPST_MSG_UNREG_KOD_LT       ((const unsigned char *)"Licencijos iðmetimo kodas:              \n")
#define KPST_MSG_ALLREADY_REMOVED_LT   ((const unsigned char *)"%s\n                                       \nProduktas jau iðmestas")
// #define KPST_MSG_UNREG_SUCC_LT      ((const unsigned char *)"Licencijos diegimas panaikintas sëkmingai") 
#define KPST_MSG_UNREG_SUCC_LT      ((const unsigned char *)"Licencijos aktyvacija panaikinta sëkmingai") 
// #define KPST_MSG_UNREG_UNSUCC_LT    ((const unsigned char *)"Internetu registracijos panaikinti nepavyko.")
#define KPST_MSG_UNREG_UNSUCC_LT    ((const unsigned char *)"Internetu aktyvacijos panaikinti nepavyko.")
#define KPST_MSG_UNREG_UNSUCC_1_LT  ((const unsigned char *)"Pabandykite narðykle atverti þemiau esanèià nuorodà.")

// #define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Programa dar neuþregistruota. Registracijos procedûrà turësite pakartoti paleidimo meniu komanda „Registracija”.")
// #define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Produktas dar neuþregistruotas. Registracijos procedûrà turësite pakartoti paleidimo meniu komanda „Registracija”.")
// #define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Produktas dar neaktyvuotas. Aktyvacijos procedûrà turësite pakartoti paleidimo meniu komanda „Aktyvacija”.")
#define KPST_MSG_REG_NOT_YET_LT     ((const unsigned char *)"Produktas dar neaktyvuotas. Aktyvacijos procedûrà turësite pakartoti.")

// #define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"Produkto diegimui reikia sistemos administratoriaus teisiø"
// #define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"Sistemos resursai nepasiekiami, uþsiregistruokite administratoriumi") 
#define KPST_MSG_INI_NOT_ADMIN_LT   ((const unsigned char *)"Sistemos resursai nepasiekiami, prisijunkite privilegijuotu Windows vartotoju") 

#define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"Nesëkmës atveju iðmetimo kodà iðsiøskite elektroniniu paðtu,") // !!!! TODO perkelti á kitas kalbas
#ifdef KPST_ARKIM
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"Iðmetimo kodà iðsiøskite elektroniniu paðtu arkim@tev.lt ")
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"Iðmetimo kodà iðsiøskite elektroniniu paðtu, adresu arkim@tev.lt arba")
#define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"adresu arkim@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti á kitas kalbas
#endif
#ifdef KPST_TEV
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"Iðmetimo kodà iðsiøskite elektroniniu paðtu tech@tev.lt ")
// #define KPST_MSG_UNREG_PASTU_LT     ((const unsigned char *)"Iðmetimo kodà iðsiøskite elektroniniu paðtu, adresu tech@tev.lt arba")
#define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"adresu tech@tev.lt arba darbo dienomis nuo 9 val. iki 16 val.") // !!!! TODO perkelti á kitas kalbas
#endif
// #define KPST_MSG_UNREG_DARBO_LAIKAS_LT ((const unsigned char *)"darbo dienomis nuo 9 val. iki 16 val. paskambinæ tel. 8-5-2729318")
// #define KPST_MSG_UNREG_DIKT_TELEF_LT   ((const unsigned char *)"padiktuokite operatoriui.")
#define KPST_MSG_UNREG_DIKT_TELEF_LT   ((const unsigned char *)"paskambinæ tel. 8-5-2729318, padiktuokite operatoriui.") // !!!! TODO perkelti á kitas kalbas

// #define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"To nepadaræ, kitame kompiuteryje programos uþregistruoti negalësite!")
// #define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"To nepadaræ, kitame kompiuteryje produkto uþregistruoti negalësite!")
#define KPST_MSG_UNREG_NEGALESIT_LT /* KPST_MSG_UNREG_TELEF_LT */ ((const unsigned char *)"To nepadaræ, kitame kompiuteryje produkto aktyvuoti negalësite!")

#define KPST_MSG_INSERT_FLOPPY_LT   ((const unsigned char *)"Ádëkite diskelá")
#define KPST_MSG_UNABLE_OPEN_REZFILE_LT   ((const unsigned char *)"Negaliu atverti rezultatø failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_LT  ((const unsigned char *)"Negaliu áraðyti á rezultatø failà.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_LT  ((const unsigned char *)"Negaliu uþdaryti rezultatø failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_LT     ((const unsigned char *)"Negaliu perskaityti áraðyto failo.")
#define KPST_MSG_COULDNT_WRITE_LT   ((const unsigned char *)"Duomenys neásiraðo.")
#define KPST_MSG_REFUSE_RESULTS_LT  ((const unsigned char *)"Ar tikrai norite atsisakyti rezultatø?")
#define KPST_MSG_TEST_SUCC_LT       ((const unsigned char *)"Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     ") // "Ðis kompiuteris parengtas darbui su programine priemone Acrobat Reader CE" // "Duomenø surinkimo testas baigësi sëkmingai"

#ifdef KPST_ARKIM
// #define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu arkim@tev.lt")
#define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà aplanko c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu arkim@tev.lt")
#endif

#ifdef KPST_TEV
// #define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu tech@tev.lt")
#define KPST_MSG_TEST_UNSUC_LT      ((const unsigned char *)"Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà aplanko c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt")
#endif

// #define KPST_MSG_INSERT_FLASH_LT    ((const unsigned char *)"Ákiðkite atmintukà su programos „")
#define KPST_MSG_INSERT_FLASH_LT    ((const unsigned char *)"Ákiðkite atmintukà su „")
// #define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"“ kodu")
// #define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"“")
#define KPST_MSG_INSERT_FLASH_1_LT  ((const unsigned char *)"”")

#define KPST_MSG_ENTER_PWD_LT       ((const unsigned char *)"Áveskite slaptaþodá:")
#define KPST_MSG_BAD_PWD_LT         ((const unsigned char *)"Slaptaþodis neteisingas")
#define KPST_MSG_ENTER_PUK_LT       ((const unsigned char *)"Áveskite atmintuko licencijos kodà:")
#define KPST_MSG_BAD_PUK_LT         ((const unsigned char *)"Neteisingas licencijos kodas")


// #define KPST_MSG_OBJ_REG_LT         ((const unsigned char *)"Dokumento registracija")
#define KPST_MSG_OBJ_REG_LT         ((const unsigned char *)"Dokumento aktyvacija") // KPST_MSG_PROD_REG_LT
// #define KPST_MSG_OBJ_REG_INFO_LT    ((const unsigned char *)"Prieð naudojant dokumentà reikia uþregistruoti.")
#define KPST_MSG_OBJ_REG_INFO_LT    ((const unsigned char *)"Prieð naudojant dokumentà reikia aktyvuoti.") // KPST_MSG_REG_INFO_LT
// #define KPST_MSG_OBJ_UNREG_INFO_LT  ((const unsigned char *)"Licencijos registracija naikinama prieð dokumento perkëlimà á kità kompiuterá.") 
#define KPST_MSG_OBJ_UNREG_INFO_LT  ((const unsigned char *)"Licencijos aktyvacija naikinama prieð dokumento perkëlimà á kità kompiuterá.") // KPST_MSG_UNREG_INFO_LT 
// #define KPST_MSG_OBJ_REG_PERSPEJ_LT ((const unsigned char *)"Uþregistruotas dokumentas atsivers tik ðiame kompiuteryje!")
#define KPST_MSG_OBJ_REG_PERSPEJ_LT ((const unsigned char *)"Aktyvuotas dokumentas atsivers tik ðiame kompiuteryje!") // KPST_MSG_REG_PERSPEJ_LT

// #define KPST_MSG_OBJ_REG_NOT_YET_LT     ((const unsigned char *)"Dokumento registracija atðaukta.")
#define KPST_MSG_OBJ_REG_NOT_YET_LT     ((const unsigned char *)"Dokumento aktyvacija atðaukta.") // KPST_MSG_REG_NOT_YET_LT
// #define KPST_MSG_OBJ_UNREG_NEGALESIT_LT ((const unsigned char *)"To nepadaræ, kitame kompiuteryje dokumento uþregistruoti negalësite!") // KPST_MSG_UNREG_NEGALESIT_LT
#define KPST_MSG_OBJ_UNREG_NEGALESIT_LT ((const unsigned char *)"To nepadaræ, kitame kompiuteryje dokumento aktyvuoti negalësite!") // KPST_MSG_UNREG_NEGALESIT_LT

#define KPST_MSG_BAD_FLASH_LT       ((const unsigned char *)"Ðis atnaujinimas skirtas atmintukui %s")

#define KPST_MSG_LICENCE_EXPIRED_LT ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigësi")
#define KPST_MSG_REST_MONTHS_LT     ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigsis po %ld mënesiø")
#define KPST_MSG_REST_LAST_MONTH_LT ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigsis kità mënesá")
#define KPST_MSG_REST_DAYS_LT       ((const unsigned char *)"%s\n                                       \nLicencijos galiojimas baigsis po %ld dienø")
#define KPST_MSG_REST_DAY_LT        ((const unsigned char *)"%s\n                                       \nRytoj baigsis licencijos galiojimas")
#define KPST_MSG_REST_TODAY_LT      ((const unsigned char *)"%s\n                                       \nÐiandien baigiasi licencijos galiojimas")
#define KPST_MSG_TIME_CHEAT_LT      ((const unsigned char *)"Teisingai nustatykite sistemos laikrodá")

#define KPST_MSG_BAD_PRODVAR_LT     ((const unsigned char *)"Jûs naudojate pasenusià produkto versijà. Paleiskite produktà, paspauskite versijos tikrinimo mygtukà „i“, parsisiøsdinkite pasiûlytà atnaujinimà ir já ádiekite.")

// #define KPST_MSG_UPDATE_FINISHED_LT ((const unsigned char *)"Atnaujinimas baigtas. Paspauskite „Baigti“. Po to paleiskite MIKO knygà.")
#define KPST_MSG_UPDATE_FINISHED_LT ((const unsigned char *)"       Spragtelëkite mygtukà „Baigti“.         \n       Po to paleiskite MIKO knygà.         ")

// #define KPST_MSG_SELDOWN_TITLE_LT   ((const unsigned char *)"Produkto komponentø parsisiøsdinimas")
#define KPST_MSG_SELDOWN_TITLE_LT   ((const unsigned char *)"Serijos leidiniø parsisiøsdinimas")
#define KPST_MSG_SELDOWN_PROMPT_LT  ((const unsigned char *)"Jûsø turima serija turi naujø leidiniø.                          \n"\
                                                            "Panaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_LT ((const unsigned char *)"Naujø serijos leidiniø daugiau nebetikrinti:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_LT ((const unsigned char *)"Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\n"\
                                                               "jei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.                        ")

#define KPST_MSG_SELUPD_TITLE_LT   ((const unsigned char *)"Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_LT  ((const unsigned char *)"Jûsø turimam produktui rasti atnaujinimai.                       \n"\
                                                           "Panaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_LT ((const unsigned char *)"Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_LT ((const unsigned char *)"Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\n"\
                                                              "jei ne – „Atðaukti“.                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_LT ((const unsigned char *)"Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef kpstmsg_lt_included
