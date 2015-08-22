// -----------------------------------------
// kpstmsg_pl_1257.h
// programos paleidimo aplikaciju pranesimai
// lenkø kalba Windows Baltic
// 

#ifndef kpstmsg_pl_1257_included
#define kpstmsg_pl_1257_included

#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

// #define KPST_MSG_PROD_REG_PL_1257        ((const unsigned char *)"Rejestracja programu")
// #define KPST_MSG_PROD_REG_PL_1257        ((const unsigned char *)"Rejestracja produktu")
#define KPST_MSG_PROD_REG_PL_1257        ((const unsigned char *)"Aktywacja produktu")

#define KPST_MSG_UNREG_PL_1257           ((const unsigned char *)"Odwoùanie licencji")
#define KPST_MSG_LIC_PL_1257             ((const unsigned char *)"Licencja")

// #define KPST_MSG_REG_INFO_PL_1257        ((const unsigned char *)"By uruchomiã program, wymagana jest rejestracja.")
// #define KPST_MSG_REG_INFO_PL_1257        ((const unsigned char *)"By uruchomiã produkt, wymagana jest rejestracja.")
#define KPST_MSG_REG_INFO_PL_1257        ((const unsigned char *)"By uruchomiã produkt, wymagana jest aktywacja.")

#define KPST_MSG_IVESK_LIC_PL_1257       ((const unsigned char *)"Wprowadê kod licencji, który otrzymaùeú nabywajàc produkt.")
// !!!! TODO iðversti
#define KPST_MSG_IVESK_LIC_1_PL_1257     ((const unsigned char *)"") // "(Visà kodà galima kopijuoti á pirmà langelá.)")
#define KPST_MSG_REG_CARD_PL_1257        ((const unsigned char *)"")
#define KPST_MSG_LIC_KOD_PL_1257         ((const unsigned char *)"Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1257   ((const unsigned char *)"Bùædnie wprowadzono kod licencji")

// #define KPST_MSG_CHECK_CONN_PL_1257      ((const unsigned char *)"Sprawdê, czy komputer jest podùàczony do Internetu")
#define KPST_MSG_CHECK_CONN_PL_1257      KP_MSG_FIREWALL_PL_1257
// #define KPST_MSG_CHECK_CONN_LOC_PL_1257  ((const unsigned char *)"Sprawdê, czy komputer jest podùàczony do sieci")
#define KPST_MSG_CHECK_CONN_LOC_PL_1257  ((const unsigned char *)"Nie ma dostæpu do sieci. Sprawdê ustawienia swojej zapory sieciowej – spróbuj wciàgnàã %s do listy zaufanych programów, którym dozwolone jest zwracanie siæ do internetu.")

// #define KPST_MSG_REG_SUCC_PL_1257        ((const unsigned char *)"%s\n                                       \nLicencja zostaùa zarejestrowana")
#define KPST_MSG_REG_SUCC_PL_1257        ((const unsigned char *)"%s\n                                       \nLicencja zostaùa aktywowana")
// #define KPST_MSG_ALLREADY_REG_PL_1257    ((const unsigned char *)"%s\n                                       \nLicencja juý jest zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1257    ((const unsigned char *)"%s\n                                       \nLicencja juý jest aktywowana")
// #define KPST_MSG_REG_UNSUC_PL_1257       ((const unsigned char *)"Licencji nie udaùo siæ zarejestrowaã przez Internet.")
#define KPST_MSG_REG_UNSUC_PL_1257       ((const unsigned char *)"Licencji nie udaùo siæ aktywowaã przez Internet.")
// !!!! TODO iðversti
#define KPST_MSG_REG_UNSUC_0_PL_1257     ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau")
#define KPST_MSG_REG_UNSUC_1_PL_1257     ((const unsigned char *)"") // "esanèià nuorodà, o gautà atsakymà ákopijuoti á diegimo kodo laukelius."

// #define KPST_MSG_REG_UNSUC_LOC_PL_1257   ((const unsigned char *)"Nieudana rejestracja.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1257   ((const unsigned char *)"Nieudana aktywacja.")
#define KPST_MSG_DIEG_KOD_PL_1257        ((const unsigned char *)"Kod instalacji:")

// #define KPST_MSG_UNREG_INFO_PL_1257      ((const unsigned char *)"Przed przeniesieniem programu na inny komputer licencja powinna byã usuniæta.")
#define KPST_MSG_UNREG_INFO_PL_1257      ((const unsigned char *)"Przed przeniesieniem produktu na inny komputer licencja powinna byã deaktywowana.")

#define KPST_MSG_UNREG_IVESK_LIC_PL_1257 KPST_MSG_IVESK_LIC_PL_1257

// #define KPST_MSG_REG_PERSPEJ_PL_1257     ((const unsigned char *)"Zarejestrowany program bædzie dziaùaù tylko na tym komputerze!")
// #define KPST_MSG_REG_PERSPEJ_PL_1257     ((const unsigned char *)"Zarejestrowany produkt bædzie dziaùaù tylko na tym komputerze!")
#define KPST_MSG_REG_PERSPEJ_PL_1257     ((const unsigned char *)"Aktywowany produkt bædzie dziaùaù tylko na tym komputerze!")

// #define KPST_MSG_BUT_REG_PL_1257         ((const unsigned char *)"W jaki sposób zarejestrujesz program?")
// #define KPST_MSG_BUT_REG_PL_1257         ((const unsigned char *)"W jaki sposób zarejestrujesz produkt?")
#define KPST_MSG_BUT_REG_PL_1257         ((const unsigned char *)"W jaki sposób aktywujesz licencjæ produktu?")

// #define KPST_MSG_BUT_UNREG_PL_1257       ((const unsigned char *)"W jaki sposób usuniesz rejestracjæ programu?")
// #define KPST_MSG_BUT_UNREG_PL_1257       ((const unsigned char *)"W jaki sposób usuniesz rejestracjæ produktu?")
#define KPST_MSG_BUT_UNREG_PL_1257       ((const unsigned char *)"W jaki sposób deaktywujesz licencjæ produktu?")

#define KPST_MSG_INTERNETU_PL_1257       ((const unsigned char *)"Przez Internet")
#define KPST_MSG_TELEFONU_PL_1257        ((const unsigned char *)"Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1257      ((const unsigned char *)"Odwoùaj")
// #define KPST_MSG_CANCEL_UNREG_PL_1257    ((const unsigned char *)"Nie usuwaj")
#define KPST_MSG_CANCEL_UNREG_PL_1257    ((const unsigned char *)"Nie deaktywuj")

#define KPST_MSG_SIUSK_PASTU_PL_1257     ((const unsigned char *)"Kod instalacji moýesz wysùaã pocztà elektronicznà na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1257    ((const unsigned char *)"w dniach pracy od godz. 9 do 16 dzwoniàc pod nr. tel. +370-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1257      ((const unsigned char *)"podyktowaã go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1257     ((const unsigned char *)"Wprowadê otrzymanà odpowiedê – klucz instalacji.")
// !!!! TODO iðversti
#define KPST_MSG_IVESK_RAKTA_1_PL_1257   ((const unsigned char *)"") // "(Visà raktà galima kopijuoti á pirmà langelá.)")
#define KPST_MSG_DIEG_RAKTAS_PL_1257     ((const unsigned char *)"Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1257   ((const unsigned char *)"Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1257 ((const unsigned char *)"Bùædnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1257   ((const unsigned char *)"Wywoùaj program z pùyty CD")
#define KPST_MSG_BAD_CD_PL_1257          ((const unsigned char *)"Wadliwa plùyta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1257    ((const unsigned char *)"Rezultatai nesuformuoti.\nDël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1257    ((const unsigned char *)"Rezultatø rasti nepavyko.\n Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1257    ((const unsigned char *)"Rezultatø rasti nepavyko.\nJûs esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1257     ((const unsigned char *)". Rezultatai sëkmingai perkelti á ")

// #define KPST_MSG_REG_NOT_ADMIN_PL_1257   ((const unsigned char *)"Dla rejestracji licencji powinieneú\n zalogowaã siæ do systemu jako administrator")
#define KPST_MSG_REG_NOT_ADMIN_PL_1257   ((const unsigned char *)"Dla aktywacji licencji powinieneú\n zalogowaã siæ do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1257 ((const unsigned char *)"Dla usuniæcia instalacji produktu powinieneú\n zalogowaã siæ do systemu jako administrator")
// #define KPST_MSG_UNREG_NOT_ADMIN_PL_1257 ((const unsigned char *)"Dla deaktywacji licencji produktu powinieneú\n zalogowaã siæ do systemu jako administrator")

// #define KPST_MSG_NOT_REG_PL_1257         ((const unsigned char *)"Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_NOT_REG_PL_1257         ((const unsigned char *)"Licencja produktu jeszcze nie jest aktywowana")
#define KPST_MSG_INVALID_REG_PL_1257     ((const unsigned char *)"Kod uaktualnienia i podstawowego produktu nie sà zgodne. Zainstaluj produkt ponownie.")

// #define KPST_MSG_UNREG_KOD_1_PL_1257     ((const unsigned char *)"Kod usuniæcia")
#define KPST_MSG_UNREG_KOD_1_PL_1257     ((const unsigned char *)"Kod deaktywacji")
// #define KPST_MSG_UNREG_KOD_PL_1257       ((const unsigned char *)"Kod usuniæcia licencji:              \n")
#define KPST_MSG_UNREG_KOD_PL_1257       ((const unsigned char *)"Kod deaktywacji licencji:              \n")
// #define KPST_MSG_ALLREADY_REMOVED_PL_1257   ((const unsigned char *)"%s\n                                       \nProdukt juý usuniæty")
#define KPST_MSG_ALLREADY_REMOVED_PL_1257   ((const unsigned char *)"%s\n                                       \nProdukt juý jest deaktywowany")
// #define KPST_MSG_UNREG_SUCC_PL_1257      ((const unsigned char *)"Licencja zostaùa usuniæta") 
#define KPST_MSG_UNREG_SUCC_PL_1257      ((const unsigned char *)"Licencja zostaùa deaktywowana") 
// #define KPST_MSG_UNREG_UNSUCC_PL_1257    ((const unsigned char *)"Nie udaùo siæ usunàã rejestracji przez Internet.")
// #define KPST_MSG_UNREG_UNSUCC_PL_1257    ((const unsigned char *)"Nie udaùo siæ usunàã aktywacji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_PL_1257    ((const unsigned char *)"Nie udaùo siæ deaktywowaã przez Internet.")
// !!!! TODO iðversti
#define KPST_MSG_UNREG_UNSUCC_1_PL_1257  ((const unsigned char *)"") // "Pabandykite narðykle atverti þemiau esanèià nuorodà.")

// #define KPST_MSG_REG_NOT_YET_PL_1257     ((const unsigned char *)"Program jeszcze nie byù zarejestrowany. Ponów rejestracjæ podczac wywoùywania programu poprzez menu „Rejestracja”.")
// #define KPST_MSG_REG_NOT_YET_PL_1257     ((const unsigned char *)"Produkt jeszcze nie byù zarejestrowany. Ponów rejestracjæ podczac wywoùywania produktu poprzez menu „Rejestracja”.")
// #define KPST_MSG_REG_NOT_YET_PL_1257     ((const unsigned char *)"Produkt jeszcze nie byù aktywowany. Ponów aktywacjæ podczac wywoùywania produktu poprzez menu „Aktywacja”.")
#define KPST_MSG_REG_NOT_YET_PL_1257     ((const unsigned char *)"Produkt jeszcze nie byù aktywowany")

#define KPST_MSG_INI_NOT_ADMIN_PL_1257   ((const unsigned char *)"Zasoby systemu nie sà dostæpne. Zaloguj siæ do systemu jako administrator.")


// #define KPST_MSG_UNREG_PASTU_PL_1257     ((const unsigned char *)"Kod usuniæcia moýesz wysùaã pocztà elektronowà na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_PASTU_PL_1257     ((const unsigned char *)"Kod deaktywacji moýesz wysùaã pocztà elektronowà na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1257 ((const unsigned char *)"w dniach pracy od godz. 9 do 16 dzwoniàc pod nr. tel. +370-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1257   ((const unsigned char *)"i podyktowaã dla operatora.")

// #define KPST_MSG_UNREG_NEGALESIT_PL_1257 /* KPST_MSG_UNREG_TELEF_PL_1257 */ ((const unsigned char *)"Nie wykonujàc tej czynnoúci, nie bædziesz mógù zarejestrowaã programu na innym komputerze!")
// #define KPST_MSG_UNREG_NEGALESIT_PL_1257 /* KPST_MSG_UNREG_TELEF_PL_1257 */ ((const unsigned char *)"Nie wykonujàc tej czynnoúci, nie bædziesz mógù zarejestrowaã produktu na innym komputerze!")
#define KPST_MSG_UNREG_NEGALESIT_PL_1257 /* KPST_MSG_UNREG_TELEF_PL_1257 */ ((const unsigned char *)"Nie wykonujàc tej czynnoúci, nie bædziesz mógù aktywowaã produktu na innym komputerze!")

#define KPST_MSG_INSERT_FLOPPY_PL_1257   ((const unsigned char *)"Ádëkite diskelá")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1257   ((const unsigned char *)"Negaliu atverti rezultatø failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1257  ((const unsigned char *)"Negaliu áraðyti á rezultatø failà.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1257  ((const unsigned char *)"Negaliu uþdaryti rezultatø failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1257     ((const unsigned char *)"Negaliu perskaityti áraðyto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1257   ((const unsigned char *)"Duomenys neásiraðo.")
#define KPST_MSG_REFUSE_RESULTS_PL_1257  ((const unsigned char *)"Ar tikrai norite atsisakyti rezultatø?")
#define KPST_MSG_TEST_SUCC_PL_1257       ((const unsigned char *)"Konkurso programinë áranga ðiame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1257      ((const unsigned char *)"Rezultatø suformuoti nepavyko.\nPraðome suarchyvuotà katalogo c:\\arkim\\rezultatai turiná atsiøsti elektroniniu paðtu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1257    ((const unsigned char *)"Podùàcz USB noúnik z „")

#define KPST_MSG_INSERT_FLASH_1_PL_1257  ((const unsigned char *)"”")

#define KPST_MSG_ENTER_PWD_PL_1257       ((const unsigned char *)"Wprowadê hasùo:")
#define KPST_MSG_BAD_PWD_PL_1257         ((const unsigned char *)"Bùædne hasùo")

#define KPST_MSG_ENTER_PUK_PL_1257       ((const unsigned char *)"Wprowadê kod licencji noúnika USB:")
#define KPST_MSG_BAD_PUK_PL_1257         ((const unsigned char *)"Niepoprawny kod licencji")

// #define KPST_MSG_OBJ_REG_PL_1257         ((const unsigned char *)"Rejestracja dokumentu")
#define KPST_MSG_OBJ_REG_PL_1257         ((const unsigned char *)"Aktywacja dokumentu")
// #define KPST_MSG_OBJ_REG_INFO_PL_1257    ((const unsigned char *)"By uruchomiã dokument, wymagana jest rejestracja.")
#define KPST_MSG_OBJ_REG_INFO_PL_1257    ((const unsigned char *)"By uruchomiã dokument, wymagana jest aktywacja.")
// #define KPST_MSG_OBJ_UNREG_INFO_PL_1257  ((const unsigned char *)"Przed przeniesieniem dokumentu na inny komputer licencja powinna byã usuniæta.") 
#define KPST_MSG_OBJ_UNREG_INFO_PL_1257  ((const unsigned char *)"Przed przeniesieniem dokumentu na inny komputer licencja powinna byã deaktywowana.") 
// #define KPST_MSG_OBJ_REG_PERSPEJ_PL_1257 ((const unsigned char *)"Zarejestrowany dokument bædzie dziaùaù tylko na tym komputerze!")
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1257 ((const unsigned char *)"Aktywowany dokument bædzie dziaùaù tylko na tym komputerze!")

// #define KPST_MSG_OBJ_REG_NOT_YET_PL_1257     ((const unsigned char *)"Rejestracja dokumentu zostaùa odwoùona.")
#define KPST_MSG_OBJ_REG_NOT_YET_PL_1257     ((const unsigned char *)"Aktywacja dokumentu zostaùa odwoùona.")
// #define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1257 ((const unsigned char *)"Nie wykonujàc tej czynnoúci, nie bædziesz mógù zarejestrowaã dokumentu na innym komputerze!")
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1257 ((const unsigned char *)"Nie wykonujàc tej czynnoúci, nie bædziesz mógù aktywowaã dokumentu na innym komputerze!")

#define KPST_MSG_BAD_FLASH_PL_1257       ((const unsigned char *)"Dana aktualizacja jest przeznaczona dla noúnika USB %s")

#define KPST_MSG_LICENCE_EXPIRED_PL_1257 ((const unsigned char *)"%s\n                                       \nWaýnoúã licencji siæ konczyùa")
#define KPST_MSG_REST_MONTHS_PL_1257     ((const unsigned char *)"%s\n                                       \nWaýnoúã licencji bæde siæ konczyùa po %ld miesiàcach")
#define KPST_MSG_REST_LAST_MONTH_PL_1257 ((const unsigned char *)"%s\n                                       \nWaýnoúã licencji bæde siæ konczyùa w przyszùym miesiàcu")
#define KPST_MSG_REST_DAYS_PL_1257       ((const unsigned char *)"%s\n                                       \nWaýnoúã licencji bæde siæ konczyùa po %ld dniach")
#define KPST_MSG_REST_DAY_PL_1257        ((const unsigned char *)"%s\n                                       \nWaýnoúã licencji jutro bæde siæ konczyùa")
#define KPST_MSG_REST_TODAY_PL_1257      ((const unsigned char *)"%s\n                                       \nWaýnoúã licencji dziú bæde siæ konczyùa")
#define KPST_MSG_TIME_CHEAT_PL_1257      KPST_MSG_LICENCE_EXPIRED_PL_1257 // "Teisingai nustatykite sistemos laikrodá"

// !!!! TODO: iðversti
#define KPST_MSG_BAD_PRODVAR_PL_1257     ((const unsigned char *)"Jûs naudojate pasenusià produkto versijà. Paleiskite produktà, paspauskite versijos tikrinimo mygtukà „i“, parsisiøsdinkite pasiûlytà atnaujinimà ir já ádiekite.")
#define KPST_MSG_UPDATE_FINISHED_PL_1257 ((const unsigned char *)"       Spragtelëkite mygtukà „Baigti“.         \n       Po to paleiskite MIKO knygà.         ")
#define KPST_MSG_SELDOWN_TITLE_PL_1257   ((const unsigned char *)"Serijos leidiniø parsisiøsdinimas")
#define KPST_MSG_SELDOWN_PROMPT_PL_1257  ((const unsigned char *)"Jûsø turima serija turi naujø leidiniø.\nPanaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1257 ((const unsigned char *)"Naujø serijos leidiniø daugiau nebetikrinti:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1257 ((const unsigned char *)"Jei norite parsisiøsdinti paþymëtus leidinius, spragtelëkite mygtukà „Gerai“,\njei tæsti jau turimø leidiniø naudojimà – „Atðaukti“.")

#define KPST_MSG_SELUPD_TITLE_PL_1257   ((const unsigned char *)"Produkto atnaujinimø parsisiøsdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1257  ((const unsigned char *)"Jûsø turimam produktui rasti atnaujinimai.                       \n"\
                                                           "Panaikinkite varneles tiems ið jø, kuriø parsisiøsdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1257 ((const unsigned char *)"Naujø produkto atnaujinimø daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1257 ((const unsigned char *)"Jei norite parsisiøsdinti paþymëtus atnaujinimus, spragtelëkite mygtukà „Gerai“,\n"\
                                                              "jei ne – „Atðaukti“.                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_PL_1257 ((const unsigned char *)"Jei norite tæsti atnaujinimo diegimà, turite uþverti programos „%s“ langà")

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#endif // #ifndef kpstmsg_pl_1257_included
