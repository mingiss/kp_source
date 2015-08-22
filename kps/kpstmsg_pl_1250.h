// -----------------------------------------
// kpstmsg_pl_1250.h
// programos paleidimo aplikaciju pranesimai
// lenku kalba Central European
// 

#ifndef kpstmsg_pl_1250_included
#define kpstmsg_pl_1250_included

#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1250_p))

// #define KPST_MSG_PROD_REG_PL_1250        ((const unsigned char *)"Rejestracja programu")
// #define KPST_MSG_PROD_REG_PL_1250        ((const unsigned char *)"Rejestracja produktu")
#define KPST_MSG_PROD_REG_PL_1250        ((const unsigned char *)"Aktywacja produktu")

#define KPST_MSG_UNREG_PL_1250           ((const unsigned char *)"Odwo³anie licencji")
#define KPST_MSG_LIC_PL_1250             ((const unsigned char *)"Licencja")

// #define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"By uruchomiæ program, wymagana jest rejestracja.")
// #define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"By uruchomiæ produkt, wymagana jest rejestracja.")
#define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"By uruchomiæ produkt, wymagana jest aktywacja.")

#define KPST_MSG_IVESK_LIC_PL_1250       ((const unsigned char *)"WprowadŸ kod licencji, który otrzyma³eœ nabywaj¹c produkt.")
// !!!! TODO: išversti
#define KPST_MSG_IVESK_LIC_1_PL_1250     ((const unsigned char *)"") // "(Vis¹ kod¹ galima kopijuoti ? pirm¹ langel?.)")
#define KPST_MSG_REG_CARD_PL_1250        ((const unsigned char *)"")
#define KPST_MSG_LIC_KOD_PL_1250         ((const unsigned char *)"Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1250   ((const unsigned char *)"B³êdnie wprowadzono kod licencji")

// #define KPST_MSG_CHECK_CONN_PL_1250      ((const unsigned char *)"SprawdŸ, czy komputer jest pod³¹czony do Internetu")
#define KPST_MSG_CHECK_CONN_PL_1250      KP_MSG_FIREWALL_PL_1250
// #define KPST_MSG_CHECK_CONN_LOC_PL_1250  ((const unsigned char *)"SprawdŸ, czy komputer jest pod³¹czony do sieci")
#define KPST_MSG_CHECK_CONN_LOC_PL_1250  ((const unsigned char *)"Nie ma dostêpu do sieci. SprawdŸ ustawienia swojej zapory sieciowej - spróbuj wci¹gn¹æ %s do listy zaufanych programów, którym dozwolone jest zwracanie siê do internetu.")

// #define KPST_MSG_REG_SUCC_PL_1250        ((const unsigned char *)"%s\n                                       \nLicencja zosta³a zarejestrowana")
#define KPST_MSG_REG_SUCC_PL_1250        ((const unsigned char *)"%s\n                                       \nLicencja zosta³a aktywowana")
// #define KPST_MSG_ALLREADY_REG_PL_1250    ((const unsigned char *)"%s\n                                       \nLicencja ju¿ jest zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1250    ((const unsigned char *)"%s\n                                       \nLicencja ju¿ jest aktywowana")
// #define KPST_MSG_REG_UNSUC_PL_1250       ((const unsigned char *)"Licencji nie uda³o siê zarejestrowaæ przez Internet.")
#define KPST_MSG_REG_UNSUC_PL_1250       ((const unsigned char *)"Licencji nie uda³o siê aktywowaæ przez Internet.")
// !!!! TODO: išversti
#define KPST_MSG_REG_UNSUC_0_PL_1250     ((const unsigned char *)"") // "Pabandykite naršykle atverti žemiau")
#define KPST_MSG_REG_UNSUC_1_PL_1250     ((const unsigned char *)"") // "esanèi¹ nuorod¹, o gaut¹ atsakym¹ ?kopijuoti ? diegimo kodo laukelius."

// #define KPST_MSG_REG_UNSUC_LOC_PL_1250   ((const unsigned char *)"Nieudana rejestracja.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1250   ((const unsigned char *)"Nieudana aktywacja.")
#define KPST_MSG_DIEG_KOD_PL_1250        ((const unsigned char *)"Kod instalacji:")

// #define KPST_MSG_UNREG_INFO_PL_1250      ((const unsigned char *)"Przed przeniesieniem programu na inny komputer licencja powinna byæ usuniêta.")
#define KPST_MSG_UNREG_INFO_PL_1250      ((const unsigned char *)"Przed przeniesieniem produktu na inny komputer licencja powinna byæ deaktywowana.")

#define KPST_MSG_UNREG_IVESK_LIC_PL_1250 KPST_MSG_IVESK_LIC_PL_1250

// #define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"Zarejestrowany program bêdzie dzia³a³ tylko na tym komputerze!")
// #define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"Zarejestrowany produkt bêdzie dzia³a³ tylko na tym komputerze!")
#define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"Aktywowany produkt bêdzie dzia³a³ tylko na tym komputerze!")

// #define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"W jaki sposób zarejestrujesz program?")
// #define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"W jaki sposób zarejestrujesz produkt?")
#define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"W jaki sposób aktywujesz licencjê produktu?")

// #define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"W jaki sposób usuniesz rejestracjê programu?")
// #define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"W jaki sposób usuniesz rejestracjê produktu?")
#define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"W jaki sposób deaktywujesz licencjê produktu?")

#define KPST_MSG_INTERNETU_PL_1250       ((const unsigned char *)"Przez Internet")
#define KPST_MSG_TELEFONU_PL_1250        ((const unsigned char *)"Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1250      ((const unsigned char *)"Odwo³aj")
// #define KPST_MSG_CANCEL_UNREG_PL_1250    ((const unsigned char *)"Nie usuwaj")
#define KPST_MSG_CANCEL_UNREG_PL_1250    ((const unsigned char *)"Nie deaktywuj")

#define KPST_MSG_SIUSK_PASTU_PL_1250     ((const unsigned char *)"Kod instalacji mo¿esz wys³aæ poczt¹ elektroniczn¹ na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1250    ((const unsigned char *)"w dniach pracy od godz. 9 do 16 dzwoni¹c pod nr. tel. +370-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1250      ((const unsigned char *)"podyktowaæ go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1250     ((const unsigned char *)"WprowadŸ otrzyman¹ odpowiedŸ - klucz instalacji.")
// !!!! TODO: išversti
#define KPST_MSG_IVESK_RAKTA_1_PL_1250   ((const unsigned char *)"") // "(Vis¹ rakt¹ galima kopijuoti ? pirm¹ langel?.)")
#define KPST_MSG_DIEG_RAKTAS_PL_1250     ((const unsigned char *)"Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1250   ((const unsigned char *)"Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1250 ((const unsigned char *)"B³êdnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1250   ((const unsigned char *)"Wywo³aj program z p³yty CD")
#define KPST_MSG_BAD_CD_PL_1250          ((const unsigned char *)"Wadliwa pl³yta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1250    ((const unsigned char *)"Rezultatai nesuformuoti.\nD?l technin?s pagalbos kreipkit?s elektroniniu paštu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1250    ((const unsigned char *)"Rezultat? rasti nepavyko.\n D?l technin?s pagalbos kreipkit?s elektroniniu paštu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1250    ((const unsigned char *)"Rezultat? rasti nepavyko.\nJ?s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1250     ((const unsigned char *)". Rezultatai s?kmingai perkelti ? ")

// #define KPST_MSG_REG_NOT_ADMIN_PL_1250   ((const unsigned char *)"Dla rejestracji licencji powinieneœ\n zalogowaæ siê do systemu jako administrator")
#define KPST_MSG_REG_NOT_ADMIN_PL_1250   ((const unsigned char *)"Dla aktywacji licencji powinieneœ\n zalogowaæ siê do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1250 ((const unsigned char *)"Dla usuniêcia instalacji produktu powinieneœ\n zalogowaæ siê do systemu jako administrator")
// #define KPST_MSG_UNREG_NOT_ADMIN_PL_1250 ((const unsigned char *)"Dla deaktywacji licencji produktu powinieneœ\n zalogowaæ siê do systemu jako administrator")

// #define KPST_MSG_NOT_REG_PL_1250         ((const unsigned char *)"Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_NOT_REG_PL_1250         ((const unsigned char *)"Licencja produktu jeszcze nie jest aktywowana")
#define KPST_MSG_INVALID_REG_PL_1250     ((const unsigned char *)"Kod uaktualnienia i podstawowego produktu nie s¹ zgodne. Zainstaluj produkt ponownie.")

// #define KPST_MSG_UNREG_KOD_1_PL_1250     ((const unsigned char *)"Kod usuniêcia")
#define KPST_MSG_UNREG_KOD_1_PL_1250     ((const unsigned char *)"Kod deaktywacji")
// #define KPST_MSG_UNREG_KOD_PL_1250       ((const unsigned char *)"Kod usuniêcia licencji:              \n")
#define KPST_MSG_UNREG_KOD_PL_1250       ((const unsigned char *)"Kod deaktywacji licencji:              \n")
// #define KPST_MSG_ALLREADY_REMOVED_PL_1250   ((const unsigned char *)"%s\n                                       \nProdukt ju¿ usuniêty")
#define KPST_MSG_ALLREADY_REMOVED_PL_1250   ((const unsigned char *)"%s\n                                       \nProdukt ju¿ jest deaktywowany")
// #define KPST_MSG_UNREG_SUCC_PL_1250      ((const unsigned char *)"Licencja zosta³a usuniêta") 
#define KPST_MSG_UNREG_SUCC_PL_1250      ((const unsigned char *)"Licencja zosta³a deaktywowana") 
// #define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"Nie uda³o siê usun¹æ rejestracji przez Internet.")
// #define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"Nie uda³o siê usun¹æ aktywacji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"Nie uda³o siê deaktywowaæ przez Internet.")
// !!!! TODO: išversti
#define KPST_MSG_UNREG_UNSUCC_1_PL_1250  ((const unsigned char *)"") // "Pabandykite naršykle atverti žemiau esanèi¹ nuorod¹.")

// #define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Program jeszcze nie by³ zarejestrowany. Ponów rejestracjê podczac wywo³ywania programu poprzez menu „Rejestracja”.")
// #define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Produkt jeszcze nie by³ zarejestrowany. Ponów rejestracjê podczac wywo³ywania produktu poprzez menu „Rejestracja”.")
// #define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Produkt jeszcze nie by³ aktywowany. Ponów aktywacjê podczac wywo³ywania produktu poprzez menu „Aktywacja”.")
#define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Produkt jeszcze nie by³ aktywowany")

#define KPST_MSG_INI_NOT_ADMIN_PL_1250   ((const unsigned char *)"Zasoby systemu nie s¹ dostêpne. Zaloguj siê do systemu jako administrator.")


// #define KPST_MSG_UNREG_PASTU_PL_1250     ((const unsigned char *)"Kod usuniêcia mo¿esz wys³aæ poczt¹ elektronow¹ na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_PASTU_PL_1250     ((const unsigned char *)"Kod deaktywacji mo¿esz wys³aæ poczt¹ elektronow¹ na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1250 ((const unsigned char *)"w dniach pracy od godz. 9 do 16 dzwoni¹c pod nr. tel. +370-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1250   ((const unsigned char *)"i podyktowaæ dla operatora.")

// #define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"Nie wykonuj¹c tej czynnoœci, nie bêdziesz móg³ zarejestrowaæ programu na innym komputerze!")
// #define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"Nie wykonuj¹c tej czynnoœci, nie bêdziesz móg³ zarejestrowaæ produktu na innym komputerze!")
#define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"Nie wykonuj¹c tej czynnoœci, nie bêdziesz móg³ aktywowaæ produktu na innym komputerze!")

#define KPST_MSG_INSERT_FLOPPY_PL_1250   ((const unsigned char *)"?d?kite diskel?")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1250   ((const unsigned char *)"Negaliu atverti rezultat? failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1250  ((const unsigned char *)"Negaliu ?rašyti ? rezultat? fail¹.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1250  ((const unsigned char *)"Negaliu uždaryti rezultat? failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1250     ((const unsigned char *)"Negaliu perskaityti ?rašyto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1250   ((const unsigned char *)"Duomenys ne?sirašo.")
#define KPST_MSG_REFUSE_RESULTS_PL_1250  ((const unsigned char *)"Ar tikrai norite atsisakyti rezultat??")
#define KPST_MSG_TEST_SUCC_PL_1250       ((const unsigned char *)"Konkurso programin? ?ranga šiame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1250      ((const unsigned char *)"Rezultat? suformuoti nepavyko.\nPrašome suarchyvuot¹ katalogo c:\\arkim\\rezultatai turin? atsi?sti elektroniniu paštu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1250    ((const unsigned char *)"Pod³¹cz USB noœnik z „")

#define KPST_MSG_INSERT_FLASH_1_PL_1250  ((const unsigned char *)"”")

#define KPST_MSG_ENTER_PWD_PL_1250       ((const unsigned char *)"WprowadŸ has³o:")
#define KPST_MSG_BAD_PWD_PL_1250         ((const unsigned char *)"B³êdne has³o")

#define KPST_MSG_ENTER_PUK_PL_1250       ((const unsigned char *)"WprowadŸ kod licencji noœnika USB:")
#define KPST_MSG_BAD_PUK_PL_1250         ((const unsigned char *)"Niepoprawny kod licencji")

// #define KPST_MSG_OBJ_REG_PL_1250         ((const unsigned char *)"Rejestracja dokumentu")
#define KPST_MSG_OBJ_REG_PL_1250         ((const unsigned char *)"Aktywacja dokumentu")
// #define KPST_MSG_OBJ_REG_INFO_PL_1250    ((const unsigned char *)"By uruchomiæ dokument, wymagana jest rejestracja.")
#define KPST_MSG_OBJ_REG_INFO_PL_1250    ((const unsigned char *)"By uruchomiæ dokument, wymagana jest aktywacja.")
// #define KPST_MSG_OBJ_UNREG_INFO_PL_1250  ((const unsigned char *)"Przed przeniesieniem dokumentu na inny komputer licencja powinna byæ usuniêta.") 
#define KPST_MSG_OBJ_UNREG_INFO_PL_1250  ((const unsigned char *)"Przed przeniesieniem dokumentu na inny komputer licencja powinna byæ deaktywowana.") 
// #define KPST_MSG_OBJ_REG_PERSPEJ_PL_1250 ((const unsigned char *)"Zarejestrowany dokument bêdzie dzia³a³ tylko na tym komputerze!")
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1250 ((const unsigned char *)"Aktywowany dokument bêdzie dzia³a³ tylko na tym komputerze!")

// #define KPST_MSG_OBJ_REG_NOT_YET_PL_1250     ((const unsigned char *)"Rejestracja dokumentu zosta³a odwo³ona.")
#define KPST_MSG_OBJ_REG_NOT_YET_PL_1250     ((const unsigned char *)"Aktywacja dokumentu zosta³a odwo³ona.")
// #define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250 ((const unsigned char *)"Nie wykonuj¹c tej czynnoœci, nie bêdziesz móg³ zarejestrowaæ dokumentu na innym komputerze!")
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250 ((const unsigned char *)"Nie wykonuj¹c tej czynnoœci, nie bêdziesz móg³ aktywowaæ dokumentu na innym komputerze!")

#define KPST_MSG_BAD_FLASH_PL_1250       ((const unsigned char *)"Dana aktualizacja jest przeznaczona dla noœnika USB %s")

#define KPST_MSG_LICENCE_EXPIRED_PL_1250 ((const unsigned char *)"%s\n                                       \nWa¿noœæ licencji siê konczy³a")
#define KPST_MSG_REST_MONTHS_PL_1250     ((const unsigned char *)"%s\n                                       \nWa¿noœæ licencji bêde siê konczy³a po %ld miesi¹cach")
#define KPST_MSG_REST_LAST_MONTH_PL_1250 ((const unsigned char *)"%s\n                                       \nWa¿noœæ licencji bêde siê konczy³a w przysz³ym miesi¹cu")
#define KPST_MSG_REST_DAYS_PL_1250       ((const unsigned char *)"%s\n                                       \nWa¿noœæ licencji bêde siê konczy³a po %ld dniach")
#define KPST_MSG_REST_DAY_PL_1250        ((const unsigned char *)"%s\n                                       \nWa¿noœæ licencji jutro bêde siê konczy³a")
#define KPST_MSG_REST_TODAY_PL_1250      ((const unsigned char *)"%s\n                                       \nWa¿noœæ licencji dziœ bêde siê konczy³a")
#define KPST_MSG_TIME_CHEAT_PL_1250      KPST_MSG_LICENCE_EXPIRED_PL_1250 // "Teisingai nustatykite sistemos laikrod?"

// !!!! TODO: išversti
#define KPST_MSG_BAD_PRODVAR_PL_1250     ((const unsigned char *)"J?s naudojate pasenusi¹ produkto versij¹. Paleiskite produkt¹, paspauskite versijos tikrinimo mygtuk¹ „i“, parsisi?sdinkite pasi?lyt¹ atnaujinim¹ ir j? ?diekite.")
#define KPST_MSG_UPDATE_FINISHED_PL_1250 ((const unsigned char *)"       Spragtel?kite mygtuk¹ „Baigti“.         \n       Po to paleiskite MIKO knyg¹.         ")
#define KPST_MSG_SELDOWN_TITLE_PL_1250   ((const unsigned char *)"Serijos leidini? parsisi?sdinimas")
#define KPST_MSG_SELDOWN_PROMPT_PL_1250  ((const unsigned char *)"J?s? turima serija turi nauj? leidini?.\nPanaikinkite varneles tiems iš j?, kuri? parsisi?sdinti nenorite:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"Nauj? serijos leidini? daugiau nebetikrinti:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1250 ((const unsigned char *)"Jei norite parsisi?sdinti pažym?tus leidinius, spragtel?kite mygtuk¹ „Gerai“,\njei têsti jau turim? leidini? naudojim¹ - „Atšaukti“.")

#define KPST_MSG_SELUPD_TITLE_PL_1250   ((const unsigned char *)"Produkto atnaujinim? parsisi?sdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1250  ((const unsigned char *)"J?s? turimam produktui rasti atnaujinimai.                       \n"\
                                                           "Panaikinkite varneles tiems iš j?, kuri? parsisi?sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"Nauj? produkto atnaujinim? daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1250 ((const unsigned char *)"Jei norite parsisi?sdinti pažym?tus atnaujinimus, spragtel?kite mygtuk¹ „Gerai“,\n"\
                                                              "jei ne - „Atšaukti“.                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_PL_1250 ((const unsigned char *)"Jei norite têsti atnaujinimo diegim¹, turite užverti programos „%s“ lang¹")

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1250_p))

#endif // #ifndef kpstmsg_pl_1250_included
