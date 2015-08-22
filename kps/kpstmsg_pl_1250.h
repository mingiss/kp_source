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

#define KPST_MSG_UNREG_PL_1250           ((const unsigned char *)"Odwo�anie licencji")
#define KPST_MSG_LIC_PL_1250             ((const unsigned char *)"Licencja")

// #define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"By uruchomi� program, wymagana jest rejestracja.")
// #define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"By uruchomi� produkt, wymagana jest rejestracja.")
#define KPST_MSG_REG_INFO_PL_1250        ((const unsigned char *)"By uruchomi� produkt, wymagana jest aktywacja.")

#define KPST_MSG_IVESK_LIC_PL_1250       ((const unsigned char *)"Wprowad� kod licencji, kt�ry otrzyma�e� nabywaj�c produkt.")
// !!!! TODO: i�versti
#define KPST_MSG_IVESK_LIC_1_PL_1250     ((const unsigned char *)"") // "(Vis� kod� galima kopijuoti ? pirm� langel?.)")
#define KPST_MSG_REG_CARD_PL_1250        ((const unsigned char *)"")
#define KPST_MSG_LIC_KOD_PL_1250         ((const unsigned char *)"Kod licencji:")
#define KPST_MSG_BLOGAS_LIC_KODAS_PL_1250   ((const unsigned char *)"B��dnie wprowadzono kod licencji")

// #define KPST_MSG_CHECK_CONN_PL_1250      ((const unsigned char *)"Sprawd�, czy komputer jest pod��czony do Internetu")
#define KPST_MSG_CHECK_CONN_PL_1250      KP_MSG_FIREWALL_PL_1250
// #define KPST_MSG_CHECK_CONN_LOC_PL_1250  ((const unsigned char *)"Sprawd�, czy komputer jest pod��czony do sieci")
#define KPST_MSG_CHECK_CONN_LOC_PL_1250  ((const unsigned char *)"Nie ma dost�pu do sieci. Sprawd� ustawienia swojej zapory sieciowej - spr�buj wci�gn�� %s do listy zaufanych program�w, kt�rym dozwolone jest zwracanie si� do internetu.")

// #define KPST_MSG_REG_SUCC_PL_1250        ((const unsigned char *)"%s\n                                       \nLicencja zosta�a zarejestrowana")
#define KPST_MSG_REG_SUCC_PL_1250        ((const unsigned char *)"%s\n                                       \nLicencja zosta�a aktywowana")
// #define KPST_MSG_ALLREADY_REG_PL_1250    ((const unsigned char *)"%s\n                                       \nLicencja ju� jest zarejestrowana")
#define KPST_MSG_ALLREADY_REG_PL_1250    ((const unsigned char *)"%s\n                                       \nLicencja ju� jest aktywowana")
// #define KPST_MSG_REG_UNSUC_PL_1250       ((const unsigned char *)"Licencji nie uda�o si� zarejestrowa� przez Internet.")
#define KPST_MSG_REG_UNSUC_PL_1250       ((const unsigned char *)"Licencji nie uda�o si� aktywowa� przez Internet.")
// !!!! TODO: i�versti
#define KPST_MSG_REG_UNSUC_0_PL_1250     ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau")
#define KPST_MSG_REG_UNSUC_1_PL_1250     ((const unsigned char *)"") // "esan�i� nuorod�, o gaut� atsakym� ?kopijuoti ? diegimo kodo laukelius."

// #define KPST_MSG_REG_UNSUC_LOC_PL_1250   ((const unsigned char *)"Nieudana rejestracja.")
#define KPST_MSG_REG_UNSUC_LOC_PL_1250   ((const unsigned char *)"Nieudana aktywacja.")
#define KPST_MSG_DIEG_KOD_PL_1250        ((const unsigned char *)"Kod instalacji:")

// #define KPST_MSG_UNREG_INFO_PL_1250      ((const unsigned char *)"Przed przeniesieniem programu na inny komputer licencja powinna by� usuni�ta.")
#define KPST_MSG_UNREG_INFO_PL_1250      ((const unsigned char *)"Przed przeniesieniem produktu na inny komputer licencja powinna by� deaktywowana.")

#define KPST_MSG_UNREG_IVESK_LIC_PL_1250 KPST_MSG_IVESK_LIC_PL_1250

// #define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"Zarejestrowany program b�dzie dzia�a� tylko na tym komputerze!")
// #define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"Zarejestrowany produkt b�dzie dzia�a� tylko na tym komputerze!")
#define KPST_MSG_REG_PERSPEJ_PL_1250     ((const unsigned char *)"Aktywowany produkt b�dzie dzia�a� tylko na tym komputerze!")

// #define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"W jaki spos�b zarejestrujesz program?")
// #define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"W jaki spos�b zarejestrujesz produkt?")
#define KPST_MSG_BUT_REG_PL_1250         ((const unsigned char *)"W jaki spos�b aktywujesz licencj� produktu?")

// #define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"W jaki spos�b usuniesz rejestracj� programu?")
// #define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"W jaki spos�b usuniesz rejestracj� produktu?")
#define KPST_MSG_BUT_UNREG_PL_1250       ((const unsigned char *)"W jaki spos�b deaktywujesz licencj� produktu?")

#define KPST_MSG_INTERNETU_PL_1250       ((const unsigned char *)"Przez Internet")
#define KPST_MSG_TELEFONU_PL_1250        ((const unsigned char *)"Telefonicznie")
#define KPST_MSG_CANCEL_REG_PL_1250      ((const unsigned char *)"Odwo�aj")
// #define KPST_MSG_CANCEL_UNREG_PL_1250    ((const unsigned char *)"Nie usuwaj")
#define KPST_MSG_CANCEL_UNREG_PL_1250    ((const unsigned char *)"Nie deaktywuj")

#define KPST_MSG_SIUSK_PASTU_PL_1250     ((const unsigned char *)"Kod instalacji mo�esz wys�a� poczt� elektroniczn� na adres tech@tev.lt albo")
#define KPST_MSG_DARBO_LAIKAS_PL_1250    ((const unsigned char *)"w dniach pracy od godz. 9 do 16 dzwoni�c pod nr. tel. +370-5-2729318")
#define KPST_MSG_DIKT_TELEF_PL_1250      ((const unsigned char *)"podyktowa� go dla operatora.")

#define KPST_MSG_IVESK_RAKTA_PL_1250     ((const unsigned char *)"Wprowad� otrzyman� odpowied� - klucz instalacji.")
// !!!! TODO: i�versti
#define KPST_MSG_IVESK_RAKTA_1_PL_1250   ((const unsigned char *)"") // "(Vis� rakt� galima kopijuoti ? pirm� langel?.)")
#define KPST_MSG_DIEG_RAKTAS_PL_1250     ((const unsigned char *)"Klucz instalacji:")
#define KPST_MSG_DIEG_RAKTAS_1_PL_1250   ((const unsigned char *)"Klucz instalacji")
#define KPST_MSG_BLOGAS_DIEG_RAKTAS_PL_1250 ((const unsigned char *)"B��dnie wprowadzono klucz instalacji")

#define KPST_MSG_START_FROM_CD_PL_1250   ((const unsigned char *)"Wywo�aj program z p�yty CD")
#define KPST_MSG_BAD_CD_PL_1250          ((const unsigned char *)"Wadliwa pl�yta CD")
#define KPST_MSG_REZ_NESUFORM_PL_1250    ((const unsigned char *)"Rezultatai nesuformuoti.\nD?l technin?s pagalbos kreipkit?s elektroniniu pa�tu, adresu tech@tev.lt")
#define KPST_MSG_REZ_NFOUND_1_PL_1250    ((const unsigned char *)"Rezultat? rasti nepavyko.\n D?l technin?s pagalbos kreipkit?s elektroniniu pa�tu, adresu tech@tev.lt ")
#define KPST_MSG_REZ_NFOUND_2_PL_1250    ((const unsigned char *)"Rezultat? rasti nepavyko.\nJ?s esate %s, OS %s.\n   Pabandykite prisiregistruoti vartotoju administrator.")
#define KPST_MSG_REZ_SUCCESS_PL_1250     ((const unsigned char *)". Rezultatai s?kmingai perkelti ? ")

// #define KPST_MSG_REG_NOT_ADMIN_PL_1250   ((const unsigned char *)"Dla rejestracji licencji powiniene�\n zalogowa� si� do systemu jako administrator")
#define KPST_MSG_REG_NOT_ADMIN_PL_1250   ((const unsigned char *)"Dla aktywacji licencji powiniene�\n zalogowa� si� do systemu jako administrator")
#define KPST_MSG_UNREG_NOT_ADMIN_PL_1250 ((const unsigned char *)"Dla usuni�cia instalacji produktu powiniene�\n zalogowa� si� do systemu jako administrator")
// #define KPST_MSG_UNREG_NOT_ADMIN_PL_1250 ((const unsigned char *)"Dla deaktywacji licencji produktu powiniene�\n zalogowa� si� do systemu jako administrator")

// #define KPST_MSG_NOT_REG_PL_1250         ((const unsigned char *)"Licencja produktu jeszcze nie zarejestrowana")
#define KPST_MSG_NOT_REG_PL_1250         ((const unsigned char *)"Licencja produktu jeszcze nie jest aktywowana")
#define KPST_MSG_INVALID_REG_PL_1250     ((const unsigned char *)"Kod uaktualnienia i podstawowego produktu nie s� zgodne. Zainstaluj produkt ponownie.")

// #define KPST_MSG_UNREG_KOD_1_PL_1250     ((const unsigned char *)"Kod usuni�cia")
#define KPST_MSG_UNREG_KOD_1_PL_1250     ((const unsigned char *)"Kod deaktywacji")
// #define KPST_MSG_UNREG_KOD_PL_1250       ((const unsigned char *)"Kod usuni�cia licencji:              \n")
#define KPST_MSG_UNREG_KOD_PL_1250       ((const unsigned char *)"Kod deaktywacji licencji:              \n")
// #define KPST_MSG_ALLREADY_REMOVED_PL_1250   ((const unsigned char *)"%s\n                                       \nProdukt ju� usuni�ty")
#define KPST_MSG_ALLREADY_REMOVED_PL_1250   ((const unsigned char *)"%s\n                                       \nProdukt ju� jest deaktywowany")
// #define KPST_MSG_UNREG_SUCC_PL_1250      ((const unsigned char *)"Licencja zosta�a usuni�ta") 
#define KPST_MSG_UNREG_SUCC_PL_1250      ((const unsigned char *)"Licencja zosta�a deaktywowana") 
// #define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"Nie uda�o si� usun�� rejestracji przez Internet.")
// #define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"Nie uda�o si� usun�� aktywacji przez Internet.")
#define KPST_MSG_UNREG_UNSUCC_PL_1250    ((const unsigned char *)"Nie uda�o si� deaktywowa� przez Internet.")
// !!!! TODO: i�versti
#define KPST_MSG_UNREG_UNSUCC_1_PL_1250  ((const unsigned char *)"") // "Pabandykite nar�ykle atverti �emiau esan�i� nuorod�.")

// #define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Program jeszcze nie by� zarejestrowany. Pon�w rejestracj� podczac wywo�ywania programu poprzez menu �Rejestracja�.")
// #define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Produkt jeszcze nie by� zarejestrowany. Pon�w rejestracj� podczac wywo�ywania produktu poprzez menu �Rejestracja�.")
// #define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Produkt jeszcze nie by� aktywowany. Pon�w aktywacj� podczac wywo�ywania produktu poprzez menu �Aktywacja�.")
#define KPST_MSG_REG_NOT_YET_PL_1250     ((const unsigned char *)"Produkt jeszcze nie by� aktywowany")

#define KPST_MSG_INI_NOT_ADMIN_PL_1250   ((const unsigned char *)"Zasoby systemu nie s� dost�pne. Zaloguj si� do systemu jako administrator.")


// #define KPST_MSG_UNREG_PASTU_PL_1250     ((const unsigned char *)"Kod usuni�cia mo�esz wys�a� poczt� elektronow� na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_PASTU_PL_1250     ((const unsigned char *)"Kod deaktywacji mo�esz wys�a� poczt� elektronow� na adres tech@tev.lt lub")
#define KPST_MSG_UNREG_DARBO_LAIKAS_PL_1250 ((const unsigned char *)"w dniach pracy od godz. 9 do 16 dzwoni�c pod nr. tel. +370-5-2729318")
#define KPST_MSG_UNREG_DIKT_TELEF_PL_1250   ((const unsigned char *)"i podyktowa� dla operatora.")

// #define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� zarejestrowa� programu na innym komputerze!")
// #define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� zarejestrowa� produktu na innym komputerze!")
#define KPST_MSG_UNREG_NEGALESIT_PL_1250 /* KPST_MSG_UNREG_TELEF_PL_1250 */ ((const unsigned char *)"Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� aktywowa� produktu na innym komputerze!")

#define KPST_MSG_INSERT_FLOPPY_PL_1250   ((const unsigned char *)"?d?kite diskel?")
#define KPST_MSG_UNABLE_OPEN_REZFILE_PL_1250   ((const unsigned char *)"Negaliu atverti rezultat? failo.")
#define KPST_MSG_UNABLE_WRITE_REZFILE_PL_1250  ((const unsigned char *)"Negaliu ?ra�yti ? rezultat? fail�.")
#define KPST_MSG_UNABLE_CLOSE_REZFILE_PL_1250  ((const unsigned char *)"Negaliu u�daryti rezultat? failo.")
#define KP_MSG_UNABLE_READ_WRITTEN_PL_1250     ((const unsigned char *)"Negaliu perskaityti ?ra�yto failo.")
#define KPST_MSG_COULDNT_WRITE_PL_1250   ((const unsigned char *)"Duomenys ne?sira�o.")
#define KPST_MSG_REFUSE_RESULTS_PL_1250  ((const unsigned char *)"Ar tikrai norite atsisakyti rezultat??")
#define KPST_MSG_TEST_SUCC_PL_1250       ((const unsigned char *)"Konkurso programin? ?ranga �iame kompiuteryje veikia tinkamai     ")

#define KPST_MSG_TEST_UNSUC_PL_1250      ((const unsigned char *)"Rezultat? suformuoti nepavyko.\nPra�ome suarchyvuot� katalogo c:\\arkim\\rezultatai turin? atsi?sti elektroniniu pa�tu, adresu tech@tev.lt")

#define KPST_MSG_INSERT_FLASH_PL_1250    ((const unsigned char *)"Pod��cz USB no�nik z �")

#define KPST_MSG_INSERT_FLASH_1_PL_1250  ((const unsigned char *)"�")

#define KPST_MSG_ENTER_PWD_PL_1250       ((const unsigned char *)"Wprowad� has�o:")
#define KPST_MSG_BAD_PWD_PL_1250         ((const unsigned char *)"B��dne has�o")

#define KPST_MSG_ENTER_PUK_PL_1250       ((const unsigned char *)"Wprowad� kod licencji no�nika USB:")
#define KPST_MSG_BAD_PUK_PL_1250         ((const unsigned char *)"Niepoprawny kod licencji")

// #define KPST_MSG_OBJ_REG_PL_1250         ((const unsigned char *)"Rejestracja dokumentu")
#define KPST_MSG_OBJ_REG_PL_1250         ((const unsigned char *)"Aktywacja dokumentu")
// #define KPST_MSG_OBJ_REG_INFO_PL_1250    ((const unsigned char *)"By uruchomi� dokument, wymagana jest rejestracja.")
#define KPST_MSG_OBJ_REG_INFO_PL_1250    ((const unsigned char *)"By uruchomi� dokument, wymagana jest aktywacja.")
// #define KPST_MSG_OBJ_UNREG_INFO_PL_1250  ((const unsigned char *)"Przed przeniesieniem dokumentu na inny komputer licencja powinna by� usuni�ta.") 
#define KPST_MSG_OBJ_UNREG_INFO_PL_1250  ((const unsigned char *)"Przed przeniesieniem dokumentu na inny komputer licencja powinna by� deaktywowana.") 
// #define KPST_MSG_OBJ_REG_PERSPEJ_PL_1250 ((const unsigned char *)"Zarejestrowany dokument b�dzie dzia�a� tylko na tym komputerze!")
#define KPST_MSG_OBJ_REG_PERSPEJ_PL_1250 ((const unsigned char *)"Aktywowany dokument b�dzie dzia�a� tylko na tym komputerze!")

// #define KPST_MSG_OBJ_REG_NOT_YET_PL_1250     ((const unsigned char *)"Rejestracja dokumentu zosta�a odwo�ona.")
#define KPST_MSG_OBJ_REG_NOT_YET_PL_1250     ((const unsigned char *)"Aktywacja dokumentu zosta�a odwo�ona.")
// #define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250 ((const unsigned char *)"Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� zarejestrowa� dokumentu na innym komputerze!")
#define KPST_MSG_OBJ_UNREG_NEGALESIT_PL_1250 ((const unsigned char *)"Nie wykonuj�c tej czynno�ci, nie b�dziesz m�g� aktywowa� dokumentu na innym komputerze!")

#define KPST_MSG_BAD_FLASH_PL_1250       ((const unsigned char *)"Dana aktualizacja jest przeznaczona dla no�nika USB %s")

#define KPST_MSG_LICENCE_EXPIRED_PL_1250 ((const unsigned char *)"%s\n                                       \nWa�no�� licencji si� konczy�a")
#define KPST_MSG_REST_MONTHS_PL_1250     ((const unsigned char *)"%s\n                                       \nWa�no�� licencji b�de si� konczy�a po %ld miesi�cach")
#define KPST_MSG_REST_LAST_MONTH_PL_1250 ((const unsigned char *)"%s\n                                       \nWa�no�� licencji b�de si� konczy�a w przysz�ym miesi�cu")
#define KPST_MSG_REST_DAYS_PL_1250       ((const unsigned char *)"%s\n                                       \nWa�no�� licencji b�de si� konczy�a po %ld dniach")
#define KPST_MSG_REST_DAY_PL_1250        ((const unsigned char *)"%s\n                                       \nWa�no�� licencji jutro b�de si� konczy�a")
#define KPST_MSG_REST_TODAY_PL_1250      ((const unsigned char *)"%s\n                                       \nWa�no�� licencji dzi� b�de si� konczy�a")
#define KPST_MSG_TIME_CHEAT_PL_1250      KPST_MSG_LICENCE_EXPIRED_PL_1250 // "Teisingai nustatykite sistemos laikrod?"

// !!!! TODO: i�versti
#define KPST_MSG_BAD_PRODVAR_PL_1250     ((const unsigned char *)"J?s naudojate pasenusi� produkto versij�. Paleiskite produkt�, paspauskite versijos tikrinimo mygtuk� �i�, parsisi?sdinkite pasi?lyt� atnaujinim� ir j? ?diekite.")
#define KPST_MSG_UPDATE_FINISHED_PL_1250 ((const unsigned char *)"       Spragtel?kite mygtuk� �Baigti�.         \n       Po to paleiskite MIKO knyg�.         ")
#define KPST_MSG_SELDOWN_TITLE_PL_1250   ((const unsigned char *)"Serijos leidini? parsisi?sdinimas")
#define KPST_MSG_SELDOWN_PROMPT_PL_1250  ((const unsigned char *)"J?s? turima serija turi nauj? leidini?.\nPanaikinkite varneles tiems i� j?, kuri? parsisi?sdinti nenorite:")
#define KPST_MSG_SELDOWN_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"Nauj? serijos leidini? daugiau nebetikrinti:")
#define KPST_MSG_SELDOWN_BUT_PROMPT_PL_1250 ((const unsigned char *)"Jei norite parsisi?sdinti pa�ym?tus leidinius, spragtel?kite mygtuk� �Gerai�,\njei t�sti jau turim? leidini? naudojim� - �At�aukti�.")

#define KPST_MSG_SELUPD_TITLE_PL_1250   ((const unsigned char *)"Produkto atnaujinim? parsisi?sdinimas")
#define KPST_MSG_SELUPD_PROMPT_PL_1250  ((const unsigned char *)"J?s? turimam produktui rasti atnaujinimai.                       \n"\
                                                           "Panaikinkite varneles tiems i� j?, kuri? parsisi?sdinti nenorite:")
#define KPST_MSG_SELUPD_NOMORE_PROMPT_PL_1250 ((const unsigned char *)"Nauj? produkto atnaujinim? daugiau nebetikrinti:")
#define KPST_MSG_SELUPD_BUT_PROMPT_PL_1250 ((const unsigned char *)"Jei norite parsisi?sdinti pa�ym?tus atnaujinimus, spragtel?kite mygtuk� �Gerai�,\n"\
                                                              "jei ne - �At�aukti�.                                                            ")

#define KPST_MSG_CLOSE_PROG_WND_PL_1250 ((const unsigned char *)"Jei norite t�sti atnaujinimo diegim�, turite u�verti programos �%s� lang�")

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1250_p))

#endif // #ifndef kpstmsg_pl_1250_included
