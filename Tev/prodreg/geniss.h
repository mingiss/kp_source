// ===================================================
// geniss.h
// Inno Setup scriptu generatorius
//

#ifndef geniss_included
#define geniss_included

// --------------------------
#define GEN_ISS_INI_FNAME ("geniss.ini")
#define GEN_ISS_INI_SAV_FNAME ("geniss.ini.sav")
#define GEN_CSS_STR_PAR_LEN KP_MAX_FNAME_LEN // 100 // turi b�ti nedaugiau, negu KP_MAX_FNAME_LEN

// --------------------------
//  prane�imai
enum
{
GENISS_MSG_START_PROG_IX,          // "Paleisti program�" 
GENISS_MSG_UNSUCC_START_IX,        // "Nepavyko paleisti failo"
GENISS_MSG_PROG_NOT_ISTALLED_IX,   // "Programa �\' + GetFirstVerName + \'� dar ne�diegta"
GENISS_MSG_UPD_NOT_ISTALLED_IX,    // /* atnaujinimas */ "�\' + GetPrevVerName + \'� dar ne�diegtas"

GENISS_MSG_RESTART_ADMIN_IX,       // "program� paleiskite i� naujo administratoriaus teis�mis"
GENISS_MSG_INST_ADMIN_IX,          // "Diegimui reikalingos administratoriaus teis�s"
GENISS_MSG_UNINST_ADMIN_IX,        // "Panaikinimui reikalingos administratoriaus teis�s"

GENISS_MSG_FLASH_PLAYER_IX,        // "Dabar bus �diegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."
GENISS_MSG_CABRI_IX,               // "Dabar bus �diegtas Cabri 3D �skiepis. Vykdykite tolesnius diegimo programos nurodymus."

GENISS_MSG_NAT_LET_IX,             // "Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti tik tuo atveju, jei J�s� operacin�je sistemoje Windows nustatytos Lietuvos regiono parinktys ir J�s nesiruo�iate j� keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti fail� varduose?"

GENISS_MSG_ATM_KOD_TIT_IX,         // "Atmintuko kodas"
GENISS_MSG_ATM_KOD_MAIN_IX,        // "�veskite kod�, kuris u�ra�ytas ant atmintuko."
GENISS_MSG_ATM_KOD_PROMPT_IX,      // GENISS_MSG_ATM_KOD_TIT

GENISS_MSG_CHK_UPD_TIT_IX,         // "Automatinis atnaujinim� tikrinimas"
GENISS_MSG_CHK_UPD_MAIN_IX,        // "I�valykite varnel�, jei nenorite, kad automati�kai internetu b�t� tikrinama, ar atsirado nauji programos pataisymai ar papildymai."
GENISS_MSG_CHK_UPD_PROMPT_IX,      // "Automatinis atnaujinim� tikrinimas"

// produkt� pavadinim� priesagos
GENISS_PROD_FLASH_IX,              // "atmintuke" // atmintukin� produkto versija
GENISS_PROD_LAN_IX,                // "tinkle" // tinklin� produkto versija
GENISS_PROD_SERVER_IX,             // "serveris" // produkto duomen�/licencij� serveris LAN-e   
 
// ikon�/katalog� pavadinimai ir j� priesagos
GENISS_LINK_OPTIONS_IX,            // "Parinktys"
GENISS_LINK_REG_IX,                // "Registracija"
GENISS_LINK_UNREG_IX,              // "Panaikinimas"
GENISS_LINK_FLASH_IX,              // GENISS_PROD_FLASH
GENISS_LINK_FLASH_CHK_IX,          // "atmintuko tikrinimas"
GENISS_LINK_LAN_IX,                // GENISS_PROD_LAN
GENISS_LINK_SERVER_IX,             // GENISS_PROD_SERVER
GENISS_LINK_SERVER_MANAGEMENT_IX,  // "Serverio valdymas"
GENISS_LINK_CLEAN_NAT_IX,          // "Sen� rezultat� valymas"
GENISS_LINK_CLEAN_LAT_IX,          // "Senu rezultatu valymas" 

GENISS_INSERT_FLASH_KEY_IX,        // "�ki�kite atmintuk� su programa "

GENISS_LINK_DIAG_MSG_NAT_IX,       // "Diagnostinio prane�imo siuntimas"
GENISS_LINK_DIAG_MSG_LAT_IX,       // "Diagnostinio pranesimo siuntimas"
 
NumOfGenissMessages
};

#define NumOfGenissMessages_2 NumOfGenissMessages
 
#define GENISS_MSG_START_PROG           lpszaGenissMessages[GENISS_MSG_START_PROG_IX        ][iMsgLangOff] // "Paleisti program�" 
#define GENISS_MSG_UNSUCC_START         lpszaGenissMessages[GENISS_MSG_UNSUCC_START_IX      ][iMsgLangOff] // "Nepavyko paleisti failo"
#define GENISS_MSG_PROG_NOT_ISTALLED    lpszaGenissMessages[GENISS_MSG_PROG_NOT_ISTALLED_IX ][iMsgLangOff] // "Programa �\' + GetFirstVerName + \'� dar ne�diegta"
#define GENISS_MSG_UPD_NOT_ISTALLED     lpszaGenissMessages[GENISS_MSG_UPD_NOT_ISTALLED_IX  ][iMsgLangOff] // /* atnaujinimas */ "�\' + GetPrevVerName + \'� dar ne�diegtas"
                                                                                         
#define GENISS_MSG_RESTART_ADMIN        lpszaGenissMessages[GENISS_MSG_RESTART_ADMIN_IX     ][iMsgLangOff] // "program� paleiskite i� naujo administratoriaus teis�mis"
#define GENISS_MSG_INST_ADMIN           lpszaGenissMessages[GENISS_MSG_INST_ADMIN_IX        ][iMsgLangOff] // "Diegimui reikalingos administratoriaus teis�s"
#define GENISS_MSG_UNINST_ADMIN         lpszaGenissMessages[GENISS_MSG_UNINST_ADMIN_IX      ][iMsgLangOff] // "Panaikinimui reikalingos administratoriaus teis�s"
                                                                                         
#define GENISS_MSG_FLASH_PLAYER         lpszaGenissMessages[GENISS_MSG_FLASH_PLAYER_IX      ][iMsgLangOff] // "Dabar bus �diegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."
#define GENISS_MSG_CABRI                lpszaGenissMessages[GENISS_MSG_CABRI_IX             ][iMsgLangOff] // "Dabar bus �diegtas Cabri 3D �skiepis. Vykdykite tolesnius diegimo programos nurodymus."
                                                                                         
#define GENISS_MSG_NAT_LET              lpszaGenissMessages[GENISS_MSG_NAT_LET_IX           ][iMsgLangOff] // "Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti tik tuo atveju, jei J�s� operacin�je sistemoje Windows nustatytos Lietuvos regiono parinktys ir J�s nesiruo�iate j� keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti fail� varduose?"
                                                                                         
#define GENISS_MSG_ATM_KOD_TIT          lpszaGenissMessages[GENISS_MSG_ATM_KOD_TIT_IX       ][iMsgLangOff] // "Atmintuko kodas"
#define GENISS_MSG_ATM_KOD_MAIN         lpszaGenissMessages[GENISS_MSG_ATM_KOD_MAIN_IX      ][iMsgLangOff] // "�veskite kod�, kuris u�ra�ytas ant atmintuko."
#define GENISS_MSG_ATM_KOD_PROMPT       lpszaGenissMessages[GENISS_MSG_ATM_KOD_PROMPT_IX    ][iMsgLangOff] // GENISS_MSG_ATM_KOD_TIT
                                                                                         
#define GENISS_MSG_CHK_UPD_TIT          lpszaGenissMessages[GENISS_MSG_CHK_UPD_TIT_IX       ][iMsgLangOff] // "Automatinis atnaujinim� tikrinimas"
#define GENISS_MSG_CHK_UPD_MAIN         lpszaGenissMessages[GENISS_MSG_CHK_UPD_MAIN_IX      ][iMsgLangOff] // "I�valykite varnel�, jei nenorite, kad automati�kai internetu b�t� tikrinama, ar atsirado nauji programos pataisymai ar papildymai."
#define GENISS_MSG_CHK_UPD_PROMPT       lpszaGenissMessages[GENISS_MSG_CHK_UPD_PROMPT_IX    ][iMsgLangOff] // "Automatinis atnaujinim� tikrinimas"
                                                                                         
// produkt� pavadinim� priesagos     
#define GENISS_PROD_FLASH               lpszaGenissMessages[GENISS_PROD_FLASH_IX            ][iMsgLangOff] // "atmintuke" // atmintukin� produkto versija
#define GENISS_PROD_LAN                 lpszaGenissMessages[GENISS_PROD_LAN_IX              ][iMsgLangOff] // "tinkle" // tinklin� produkto versija
#define GENISS_PROD_SERVER              lpszaGenissMessages[GENISS_PROD_SERVER_IX           ][iMsgLangOff] // "serveris" // produkto duomen�/licencij� serveris LAN-e   
                                                                                         
// ikon�/katalog� pavadinimai ir j� priesagos
#define GENISS_LINK_OPTIONS             lpszaGenissMessages[GENISS_LINK_OPTIONS_IX          ][iMsgLangOff] // "Parinktys"
#define GENISS_LINK_REG                 lpszaGenissMessages[GENISS_LINK_REG_IX              ][iMsgLangOff] // "Registracija"
#define GENISS_LINK_UNREG               lpszaGenissMessages[GENISS_LINK_UNREG_IX            ][iMsgLangOff] // "Panaikinimas"
#define GENISS_LINK_FLASH               lpszaGenissMessages[GENISS_LINK_FLASH_IX            ][iMsgLangOff] // GENISS_PROD_FLASH
#define GENISS_LINK_FLASH_CHK           lpszaGenissMessages[GENISS_LINK_FLASH_CHK_IX        ][iMsgLangOff] // "atmintuko tikrinimas"
#define GENISS_LINK_LAN                 lpszaGenissMessages[GENISS_LINK_LAN_IX              ][iMsgLangOff] // GENISS_PROD_LAN
#define GENISS_LINK_SERVER              lpszaGenissMessages[GENISS_LINK_SERVER_IX           ][iMsgLangOff] // GENISS_PROD_SERVER
#define GENISS_LINK_SERVER_MANAGEMENT   lpszaGenissMessages[GENISS_LINK_SERVER_MANAGEMENT_IX][iMsgLangOff] // "Serverio valdymas"
#define GENISS_LINK_CLEAN_NAT           lpszaGenissMessages[GENISS_LINK_CLEAN_NAT_IX        ][iMsgLangOff] // "Sen� rezultat� valymas"
#define GENISS_LINK_CLEAN_LAT           lpszaGenissMessages[GENISS_LINK_CLEAN_LAT_IX        ][iMsgLangOff] // "Senu rezultatu valymas" 
                                                                                         
#define GENISS_INSERT_FLASH_KEY         lpszaGenissMessages[GENISS_INSERT_FLASH_KEY_IX      ][iMsgLangOff] // "�ki�kite atmintuk� su programa "

#define GENISS_LINK_DIAG_MSG_NAT        lpszaGenissMessages[GENISS_LINK_DIAG_MSG_NAT_IX     ][iMsgLangOff] // "Diagnostinio prane�imo siuntimas"
#define GENISS_LINK_DIAG_MSG_LAT        lpszaGenissMessages[GENISS_LINK_DIAG_MSG_LAT_IX     ][iMsgLangOff] // "Diagnostinio pranesimo siuntimas"


// ------------------------
#if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

#define GENISS_MSG_START_PROG_EN          ((const unsigned char *)"") // "Run program" 
#define GENISS_MSG_UNSUCC_START_EN        ((const unsigned char *)"") // "Unable to run file"
#define GENISS_MSG_PROG_NOT_ISTALLED_EN   ((const unsigned char *)"") // "Program �\' + GetFirstVerName + \'� not yet installed"
#define GENISS_MSG_UPD_NOT_ISTALLED_EN    ((const unsigned char *)"") // /* update */ "�\' + GetPrevVerName + \'� not yet installed"

#define GENISS_MSG_RESTART_ADMIN_EN       ((const unsigned char *)"") // "run the program again under privileged user rights"
#define GENISS_MSG_INST_ADMIN_EN          ((const unsigned char *)"") // "Privileged user rights are required for the installation"
#define GENISS_MSG_UNINST_ADMIN_EN        ((const unsigned char *)"") // "Privileged user rights are required for the uninstallation"

#define GENISS_MSG_FLASH_PLAYER_EN        ((const unsigned char *)"") // "Macromedia Flash player will be installed. Follow further instructions of the installation program."
#define GENISS_MSG_CABRI_EN               ((const unsigned char *)"") // "Cabri 3D plugin will be installed. Follow further instructions of the installation program."

#define GENISS_MSG_NAT_LET_EN             ((const unsigned char *)"") // "National letters with diacritical marks in file names could be used only in case of proper settings of the Regional Options of your Windows OS.\'+Chr(10)+Chr(10)+\'Do you want to use such letters in file names?"

#define GENISS_MSG_ATM_KOD_TIT_EN         ((const unsigned char *)"") // "USB flash drive licence code"
#define GENISS_MSG_ATM_KOD_MAIN_EN        ((const unsigned char *)"") // "Enter USB flash drive licence code."
#define GENISS_MSG_ATM_KOD_PROMPT_EN      ((const unsigned char *)"") // GENISS_MSG_ATM_KOD_TIT_EN

#define GENISS_MSG_CHK_UPD_TIT_EN         ((const unsigned char *)"") // "Automatic checking of updates"
#define GENISS_MSG_CHK_UPD_MAIN_EN        ((const unsigned char *)"") // "Clear the checkbox, if you don\'t want updates to be checked automatically by Internet."
#define GENISS_MSG_CHK_UPD_PROMPT_EN      ((const unsigned char *)"") // GENISS_MSG_CHK_UPD_TIT_EN
    
// produkt� pavadinim� priesagos
#define GENISS_PROD_FLASH_EN              ((const unsigned char *)"") // "USB flash" // atmintukin� produkto versija
#define GENISS_PROD_LAN_EN                ((const unsigned char *)"") // "network" // tinklin� produkto versija
#define GENISS_PROD_SERVER_EN             ((const unsigned char *)"") // "server" // produkto duomen�/licencij� serveris LAN-e   
 
// ikon�/katalog� pavadinimai ir j� priesagos
#define GENISS_LINK_OPTIONS_EN            ((const unsigned char *)"") // "Options"
#define GENISS_LINK_REG_EN                ((const unsigned char *)"") // "Registration"
#define GENISS_LINK_UNREG_EN              ((const unsigned char *)"") // "Remove"
#define GENISS_LINK_FLASH_EN              ((const unsigned char *)"") // GENISS_PROD_FLASH_EN
#define GENISS_LINK_FLASH_CHK_EN          ((const unsigned char *)"") // "USB flash chek "
#define GENISS_LINK_LAN_EN                ((const unsigned char *)"") // GENISS_PROD_LAN_EN
#define GENISS_LINK_SERVER_EN             ((const unsigned char *)"") // GENISS_PROD_SERVER_EN
#define GENISS_LINK_SERVER_MANAGEMENT_EN  ((const unsigned char *)"") // "Server management"
#define GENISS_LINK_CLEAN_NAT_EN          ((const unsigned char *)"") // "Clean obsolete results"
#define GENISS_LINK_CLEAN_LAT_EN          ((const unsigned char *)"") // GENISS_LINK_CLEAN_NAT_EN

#define GENISS_INSERT_FLASH_KEY_EN        ((const unsigned char *)"") // "Insert flash drive with the program "

#define GENISS_LINK_DIAG_MSG_NAT_EN       ((const unsigned char *)"") // "Diagnostinio prane�imo siuntimas"
#define GENISS_LINK_DIAG_MSG_LAT_EN       ((const unsigned char *)"") // "Diagnostinio pranesimo siuntimas"

#endif // #if FALSE // ((MsgLang != KpLangNo_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangEn_p))

// -----------------------------------------------
#if FALSE // (((MsgLang) != KpLangSel_p) && ((MsgLang) != KpLangLt_p))

#define GENISS_MSG_START_PROG_LT          ((const unsigned char *)"") // "Paleisti program�" 
#define GENISS_MSG_UNSUCC_START_LT        ((const unsigned char *)"") // "Nepavyko paleisti failo"
#define GENISS_MSG_PROG_NOT_ISTALLED_LT   ((const unsigned char *)"") // "Programa �\' + GetFirstVerName + \'� dar ne�diegta"
#define GENISS_MSG_UPD_NOT_ISTALLED_LT    ((const unsigned char *)"") // /* atnaujinimas */ "�\' + GetPrevVerName + \'� dar ne�diegtas"

#define GENISS_MSG_RESTART_ADMIN_LT       ((const unsigned char *)"") // "program� paleiskite i� naujo administratoriaus teis�mis"
#define GENISS_MSG_INST_ADMIN_LT          ((const unsigned char *)"") // "Diegimui reikalingos administratoriaus teis�s"
#define GENISS_MSG_UNINST_ADMIN_LT        ((const unsigned char *)"") // "Panaikinimui reikalingos administratoriaus teis�s"

#define GENISS_MSG_FLASH_PLAYER_LT        ((const unsigned char *)"") // "Dabar bus �diegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus."
#define GENISS_MSG_CABRI_LT               ((const unsigned char *)"") // "Dabar bus �diegtas Cabri 3D �skiepis. Vykdykite tolesnius diegimo programos nurodymus."

#define GENISS_MSG_NAT_LET_LT             ((const unsigned char *)"") // "Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti tik tuo atveju, jei J�s� operacin�je sistemoje Windows nustatytos Lietuvos regiono parinktys ir J�s nesiruo�iate j� keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti fail� varduose?"

#define GENISS_MSG_ATM_KOD_TIT_LT         ((const unsigned char *)"") // "Atmintuko licencijos kodas"
#define GENISS_MSG_ATM_KOD_MAIN_LT        ((const unsigned char *)"") // "�veskite atmintuko licencijos kod�."
#define GENISS_MSG_ATM_KOD_PROMPT_LT      ((const unsigned char *)"") // GENISS_MSG_ATM_KOD_TIT_LT

#define GENISS_MSG_CHK_UPD_TIT_LT         ((const unsigned char *)"") // "Automatinis atnaujinim� tikrinimas"
#define GENISS_MSG_CHK_UPD_MAIN_LT        ((const unsigned char *)"") // "I�valykite varnel�, jei nenorite, kad automati�kai internetu b�t� tikrinama, ar atsirado nauji programos pataisymai ar papildymai."
#define GENISS_MSG_CHK_UPD_PROMPT_LT      ((const unsigned char *)"") // GENISS_MSG_CHK_UPD_TIT_LT
    
// produkt� pavadinim� priesagos
#define GENISS_PROD_FLASH_LT              ((const unsigned char *)"") // "atmintuke" // atmintukin� produkto versija
#define GENISS_PROD_LAN_LT                ((const unsigned char *)"") // "tinkle" // tinklin� produkto versija
#define GENISS_PROD_SERVER_LT             ((const unsigned char *)"") // "serveris" // produkto duomen�/licencij� serveris LAN-e   
 
// ikon�/katalog� pavadinimai ir j� priesagos
#define GENISS_LINK_OPTIONS_LT            ((const unsigned char *)"") // "Parinktys"
#define GENISS_LINK_REG_LT                ((const unsigned char *)"") // "Registracija"
#define GENISS_LINK_UNREG_LT              ((const unsigned char *)"") // "Panaikinimas"
#define GENISS_LINK_FLASH_LT              ((const unsigned char *)"") // GENISS_PROD_FLASH_LT
#define GENISS_LINK_FLASH_CHK_LT          ((const unsigned char *)"") // "atmintuko tikrinimas"
#define GENISS_LINK_LAN_LT                ((const unsigned char *)"") // GENISS_PROD_LAN_LT
#define GENISS_LINK_SERVER_LT             ((const unsigned char *)"") // GENISS_PROD_SERVER_LT
#define GENISS_LINK_SERVER_MANAGEMENT_LT  ((const unsigned char *)"") // "Serverio valdymas"
#define GENISS_LINK_CLEAN_NAT_LT          ((const unsigned char *)"") // "Sen� rezultat� valymas"
#define GENISS_LINK_CLEAN_LAT_LT          ((const unsigned char *)"") // "Senu rezultatu valymas" 

#define GENISS_INSERT_FLASH_KEY_LT        ((const unsigned char *)"") // "�ki�kite atmintuk� su programa "

#define GENISS_LINK_DIAG_MSG_NAT_LT       ((const unsigned char *)"") // "Diagnostinio prane�imo siuntimas"
#define GENISS_LINK_DIAG_MSG_LAT_LT       ((const unsigned char *)"") // "Diagnostinio pranesimo siuntimas"

#endif // #if (((MsgLang) != KpLangSel_p) && ((MsgLang) != KpLangLt_p))

// -----------------------------------------------
#if FALSE // ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))

#define GENISS_MSG_START_PROG_PL_1250          ((const unsigned char *)"") // "Zapu�ci� program" 
#define GENISS_MSG_UNSUCC_START_PL_1250        ((const unsigned char *)"") // "Nie uda�o si� zapu�ci� pliku"
#define GENISS_MSG_PROG_NOT_ISTALLED_PL_1250   ((const unsigned char *)"") // "Program �\' + GetFirstVerName + \'� nie jest jeszcze zainstalowany"
#define GENISS_MSG_UPD_NOT_ISTALLED_PL_1250    ((const unsigned char *)"") // /* uaktualnienie */ "�\' + GetPrevVerName + \'� nie jest jeszcze zainstalowane"

#define GENISS_MSG_RESTART_ADMIN_PL_1250       ((const unsigned char *)"") // "od nowa zapu�� program z prawami administratora"
#define GENISS_MSG_INST_ADMIN_PL_1250          ((const unsigned char *)"") // "Do instalacji powiniene� posiada� prawa administratora"
#define GENISS_MSG_UNINST_ADMIN_PL_1250        ((const unsigned char *)"") // "Do usuni�cia powiniene� posiada� prawa administratora"

#define GENISS_MSG_FLASH_PLAYER_PL_1250        ((const unsigned char *)"") // "Nast�pnie b�dzie zainstalowany odtwarzacz Macromedia Flash. Wykonuj wszystkie polecenia instalatora."
#define GENISS_MSG_CABRI_PL_1250               ((const unsigned char *)"") // "Nast�pnie b�dzie zainstalowany dodatek Cabri 3D. Wykonuj wszystkie polecenia instalatora."

#define GENISS_MSG_NAT_LET_PL_1250             ((const unsigned char *)"") // "Lietuvi�kas raides su diakritiniais �enklais (nosin?mis, pauk��iukais ir kt.) fail? varduose galima naudoti tik tuo atveju, jei J?s? operacin?je sistemoje Windows nustatytos Lietuvos regiono parinktys ir J?s nesiruo�iate j? keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti fail? varduose?"

#define GENISS_MSG_ATM_KOD_TIT_PL_1250         ((const unsigned char *)"") // "Kod no�nika USB"
#define GENISS_MSG_ATM_KOD_MAIN_PL_1250        ((const unsigned char *)"") // "Wprowad� kod podany na no�niku USB."
#define GENISS_MSG_ATM_KOD_PROMPT_PL_1250      ((const unsigned char *)"") // GENISS_MSG_ATM_KOD_TIT_PL_1250

#define GENISS_MSG_CHK_UPD_TIT_PL_1250         ((const unsigned char *)"") // "Automatyczne sprawdzanie uaktualnie�"
#define GENISS_MSG_CHK_UPD_MAIN_PL_1250        ((const unsigned char *)"") // "Wyczy�� pole, je�eli nie chcesz by poprzez Internet automatycznie sprawdzano czy s� uaktualnienia."
#define GENISS_MSG_CHK_UPD_PROMPT_PL_1250      ((const unsigned char *)"") // "Automatyczne sprawdzanie uaktualnie�"

// produkt? pavadinim? priesagos
#define GENISS_PROD_FLASH_PL_1250              ((const unsigned char *)"") // "na no�niku USB" // atmintukin? produkto versija
#define GENISS_PROD_LAN_PL_1250                ((const unsigned char *)"") // "w sieci" // tinklin? produkto versija
#define GENISS_PROD_SERVER_PL_1250             ((const unsigned char *)"") // "serwer" // produkto duomen?/licencij? serveris LAN-e   
 
// ikon?/katalog? pavadinimai ir j? priesagos
#define GENISS_LINK_OPTIONS_PL_1250            ((const unsigned char *)"") // "Opcje"
#define GENISS_LINK_REG_PL_1250                ((const unsigned char *)"") // "Rejestracja"
#define GENISS_LINK_UNREG_PL_1250              ((const unsigned char *)"") // "Usuwanie"
#define GENISS_LINK_FLASH_PL_1250              ((const unsigned char *)"") // GENISS_PROD_FLASH_PL_1250
#define GENISS_LINK_FLASH_CHK_PL_1250          ((const unsigned char *)"") // "sprawdzanie no�nika USB"
#define GENISS_LINK_LAN_PL_1250                ((const unsigned char *)"") // GENISS_PROD_LAN_PL_1250
#define GENISS_LINK_SERVER_PL_1250             ((const unsigned char *)"") // GENISS_PROD_SERVER_PL_1250
#define GENISS_LINK_SERVER_MANAGEMENT_PL_1250  ((const unsigned char *)"") // "Zarz�dzanie serwerem"
#define GENISS_LINK_CLEAN_NAT_PL_1250          ((const unsigned char *)"") // "Kasowanie starych wynik�w"
#define GENISS_LINK_CLEAN_LAT_PL_1250          ((const unsigned char *)"") // "Kasowanie starych wynik�w"

#define GENISS_INSERT_FLASH_KEY_PL_1250        ((const unsigned char *)"") // "�ki�kite atmintuk� su programa "

#define GENISS_LINK_DIAG_MSG_NAT_PL_1250       ((const unsigned char *)"") // "Diagnostinio prane�imo siuntimas"
#define GENISS_LINK_DIAG_MSG_LAT_PL_1250       ((const unsigned char *)"") // "Diagnostinio pranesimo siuntimas"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1250_p))


// -----------------------------------------------
#if FALSE // ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))

#define GENISS_MSG_START_PROG_PL_1257          ((const unsigned char *)"") // "Zapu�ci� program" 
#define GENISS_MSG_UNSUCC_START_PL_1257        ((const unsigned char *)"") // "Nie uda�o si� zapu�ci� pliku"
#define GENISS_MSG_PROG_NOT_ISTALLED_PL_1257   ((const unsigned char *)"") // "Program �\' + GetFirstVerName + \'� nie jest jeszcze zainstalowany"
#define GENISS_MSG_UPD_NOT_ISTALLED_PL_1257    ((const unsigned char *)"") // /* uaktualnienie */ "�\' + GetPrevVerName + \'� nie jest jeszcze zainstalowane"

#define GENISS_MSG_RESTART_ADMIN_PL_1257       ((const unsigned char *)"") // "od nowa zapu�� program z prawami administratora"
#define GENISS_MSG_INST_ADMIN_PL_1257          ((const unsigned char *)"") // "Do instalacji powiniene� posiada� prawa administratora"
#define GENISS_MSG_UNINST_ADMIN_PL_1257        ((const unsigned char *)"") // "Do usuni�cia powiniene� posiada� prawa administratora"

#define GENISS_MSG_FLASH_PLAYER_PL_1257        ((const unsigned char *)"") // "Nast�pnie b�dzie zainstalowany odtwarzacz Macromedia Flash. Wykonuj wszystkie polecenia instalatora."
#define GENISS_MSG_CABRI_PL_1257               ((const unsigned char *)"") // "Nast�pnie b�dzie zainstalowany dodatek Cabri 3D. Wykonuj wszystkie polecenia instalatora."

#define GENISS_MSG_NAT_LET_PL_1257             ((const unsigned char *)"") // "Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti tik tuo atveju, jei J�s� operacin�je sistemoje Windows nustatytos Lietuvos regiono parinktys ir J�s nesiruo�iate j� keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti fail� varduose?"

#define GENISS_MSG_ATM_KOD_TIT_PL_1257         ((const unsigned char *)"") // "Kod no�nika USB"
#define GENISS_MSG_ATM_KOD_MAIN_PL_1257        ((const unsigned char *)"") // "Wprowad� kod podany na no�niku USB."
#define GENISS_MSG_ATM_KOD_PROMPT_PL_1257      ((const unsigned char *)"") // GENISS_MSG_ATM_KOD_TIT_PL_1257

#define GENISS_MSG_CHK_UPD_TIT_PL_1257         ((const unsigned char *)"") // "Automatyczne sprawdzanie uaktualnie�"
#define GENISS_MSG_CHK_UPD_MAIN_PL_1257        ((const unsigned char *)"") // "Wyczy�� pole, je�eli nie chcesz by poprzez Internet automatycznie sprawdzano czy s� uaktualnienia."
#define GENISS_MSG_CHK_UPD_PROMPT_PL_1257      ((const unsigned char *)"") // "Automatyczne sprawdzanie uaktualnie�"

// produkt� pavadinim� priesagos
#define GENISS_PROD_FLASH_PL_1257              ((const unsigned char *)"") // "na no�niku USB" // atmintukin� produkto versija
#define GENISS_PROD_LAN_PL_1257                ((const unsigned char *)"") // "w sieci" // tinklin� produkto versija
#define GENISS_PROD_SERVER_PL_1257             ((const unsigned char *)"") // "serwer" // produkto duomen�/licencij� serveris LAN-e   
 
// ikon�/katalog� pavadinimai ir j� priesagos
#define GENISS_LINK_OPTIONS_PL_1257            ((const unsigned char *)"") // "Opcje"
#define GENISS_LINK_REG_PL_1257                ((const unsigned char *)"") // "Rejestracja"
#define GENISS_LINK_UNREG_PL_1257              ((const unsigned char *)"") // "Usuwanie"
#define GENISS_LINK_FLASH_PL_1257              ((const unsigned char *)"") // GENISS_PROD_FLASH_PL_1257
#define GENISS_LINK_FLASH_CHK_PL_1257          ((const unsigned char *)"") // "sprawdzanie no�nika USB"
#define GENISS_LINK_LAN_PL_1257                ((const unsigned char *)"") // GENISS_PROD_LAN_PL_1257
#define GENISS_LINK_SERVER_PL_1257             ((const unsigned char *)"") // GENISS_PROD_SERVER_PL_1257
#define GENISS_LINK_SERVER_MANAGEMENT_PL_1257  ((const unsigned char *)"") // "Zarz�dzanie serwerem"
#define GENISS_LINK_CLEAN_NAT_PL_1257          ((const unsigned char *)"") // "Kasowanie starych wynik�w"
#define GENISS_LINK_CLEAN_LAT_PL_1257          ((const unsigned char *)"") // "Kasowanie starych wynik�w"

#define GENISS_INSERT_FLASH_KEY_PL_1257        ((const unsigned char *)"") // "�ki�kite atmintuk� su programa "

#define GENISS_LINK_DIAG_MSG_NAT_PL_1257       ((const unsigned char *)"") // "Diagnostinio prane�imo siuntimas"
#define GENISS_LINK_DIAG_MSG_LAT_PL_1257       ((const unsigned char *)"") // "Diagnostinio pranesimo siuntimas"

#endif // #if ((MsgLang != KpLangPl_p) && (MsgLang != KpLangSel_p) && (MsgLang != KpLangPl_1257_p))


// --------------------------------------------
#if FALSE // ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

#define GENISS_MSG_START_PROG_RU          ((const unsigned char *)"") // "Run program") 
#define GENISS_MSG_UNSUCC_START_RU        ((const unsigned char *)"") // "Unable to run file")
#define GENISS_MSG_PROG_NOT_ISTALLED_RU   ((const unsigned char *)"") // "Program �\' + GetFirstVerName + \'� not yet installed")
#define GENISS_MSG_UPD_NOT_ISTALLED_RU    ((const unsigned char *)"") //  /* update */ "�\' + GetPrevVerName + \'� not yet installed")

#define GENISS_MSG_RESTART_ADMIN_RU       ((const unsigned char *)"") // "run the program again under privileged user rights")
#define GENISS_MSG_INST_ADMIN_RU          ((const unsigned char *)"") // "Privileged user rights are required for the installation")
#define GENISS_MSG_UNINST_ADMIN_RU        ((const unsigned char *)"") // "Privileged user rights are required for the uninstallation")

#define GENISS_MSG_FLASH_PLAYER_RU        ((const unsigned char *)"") // "Macromedia Flash player will be installed. Follow further instructions of the installation program.")
#define GENISS_MSG_CABRI_RU               ((const unsigned char *)"") // "Cabri 3D plugin will be installed. Follow further instructions of the installation program.")

#define GENISS_MSG_NAT_LET_RU             ((const unsigned char *)"") // "National letters with diacritical marks in file names could be used only in case of proper settings of the Regional Options of your Windows OS.\'+Chr(10)+Chr(10)+\'Do you want to use such letters in file names?")

#define GENISS_MSG_ATM_KOD_TIT_RU         ((const unsigned char *)"") // "USB flash drive licence code")
#define GENISS_MSG_ATM_KOD_MAIN_RU        ((const unsigned char *)"") // "Enter USB flash drive licence code.")
#define GENISS_MSG_ATM_KOD_PROMPT_RU      GENISS_MSG_ATM_KOD_TIT_RU

#define GENISS_MSG_CHK_UPD_TIT_RU         ((const unsigned char *)"") // "Automatic checking of updates")
#define GENISS_MSG_CHK_UPD_MAIN_RU        ((const unsigned char *)"") // "Clear the checkbox, if you don\'t want updates to be checked automatically by Internet.")
#define GENISS_MSG_CHK_UPD_PROMPT_RU      GENISS_MSG_CHK_UPD_TIT_RU
    
// produkt� pavadinim� priesagos
#define GENISS_PROD_FLASH_RU              ((const unsigned char *)"") // "USB flash") // atmintukin� produkto versija
#define GENISS_PROD_LAN_RU                ((const unsigned char *)"") // "network") // tinklin� produkto versija
#define GENISS_PROD_SERVER_RU             ((const unsigned char *)"") // "server") // produkto duomen�/licencij� serveris LAN-e   
 
// ikon�/katalog� pavadinimai ir j� priesagos
#define GENISS_LINK_OPTIONS_RU            ((const unsigned char *)"") // "Options")
#define GENISS_LINK_REG_RU                ((const unsigned char *)"") // "Registration")
#define GENISS_LINK_UNREG_RU              ((const unsigned char *)"") // "Remove")
#define GENISS_LINK_FLASH_RU              GENISS_PROD_FLASH_RU
#define GENISS_LINK_FLASH_CHK_RU          ((const unsigned char *)"") // "USB flash chek ")
#define GENISS_LINK_LAN_RU                GENISS_PROD_LAN_RU
#define GENISS_LINK_SERVER_RU             GENISS_PROD_SERVER_RU
#define GENISS_LINK_SERVER_MANAGEMENT_RU  ((const unsigned char *)"") // "Server management")
#define GENISS_LINK_CLEAN_NAT_RU          ((const unsigned char *)"") // "Clean obsolete results")
#define GENISS_LINK_CLEAN_LAT_RU          GENISS_LINK_CLEAN_NAT_RU

#define GENISS_INSERT_FLASH_KEY_RU        ((const unsigned char *)"") // "Insert flash drive with the program ")

#define GENISS_LINK_DIAG_MSG_NAT_RU       ((const unsigned char *)"") // "Diagnostinio prane�imo siuntimas"
#define GENISS_LINK_DIAG_MSG_LAT_RU       ((const unsigned char *)"") // "Diagnostinio pranesimo siuntimas"

#endif // #if ((MsgLang != KpLangSel_p) && (MsgLang != KpLangRu_p) && (MsgLang != KpLangRu_1251_p) && (MsgLang != KpLangRu_0_p))

// --------------------------
typedef enum
{
   GenIssFiles,

   GenIssCd,
   GenIssSh,
   GenIssCert,
   GenIssUpd,
   GenIssUpdWhole,

   GenIssGrp, // keli skirting� koduo�i� setupai, pasirenkami su kpstset.exe (setup.exe) pagal konkre�ius reg. settingus 

   GenIssFlash,
   GenIssFlashUpd,
   GenIssFlashUpdWhole,

   GenIssFlashStart,
   GenIssFlashStartUpd,

   GenIssChkVol,

   GenIssNet,
   GenIssSvr,
   GenIssCli,

   GenIssRez,

   GenIssFonts,

   GenIssDel,
   GenIssDelWhole,

   GenIssFinst, // diegiamiems (terminuotiems) Mikams

   MaxGenIssType

} GenIssTypes;

#define MaxGenIssType_13 MaxGenIssType

typedef enum
{
   NoGenIssIx = -1,

   ProdNameIx,
   ProdNameRawIx,
   ProdDirIx,
   ProdGroupIx,
   ProdFNameRawIx,
   ProdFNameIx,
   VerNameIx,
   VerIx,
   ProdVerIx,
   ProdVerFlashIx,
   ProdVerNetIx,
   UpdVerNameIx,
   UpdNumIx,
   PrevVerNameIx,
   PrevVerIx,
   PrevUpdNumIx,
   BuildNumIx,
   FirstVerNameIx,
   FirstVerIx,
   IconFNameIx,
   SetupFNameIx,
   ExeFNameIx,
   SvrFNameIx,
   AutoRunIx,
   RequireAdminIx,
   PartialInstallIx,
   PartialDirIx,
   ProdTypeIx,
   ChkUpdIx,
   PublisherIx,
   SplashBMPIx,
   StartPDFIx,
   PasswordIx,
   ProjIDIx,
   KalbaIx,
   CidModeIx,
   
   NumOfGenKwds,

} GenIssKwdIxs;

#define NumOfGenKwds_11 NumOfGenKwds


// ------------------------------------
typedef enum
{
   KpPROG,  // Programa
   KpKMP,   // Kompiuterin� mokymo priemon�
   KpEVAD,  // E. vadov�lis
   KpMIKO,  // MIKO knyga
   KpUPD,   // Atnaujinimas
   KpEBOOK, // E. knyga
   KpSALT,  // �altini� knyga

   ProdTypeCnt
      
} ProdTypes;

#define ProdTypeCnt_5 ProdTypeCnt


// ------------------------------------
// #define GENISS_INCBUILD_URL   ((const unsigned char *)"http://serveri5.ll/jura/kpn/incbuild.php") 
// #define GENISS_INCBUILD_URL   ((const unsigned char *)"http://10.2.0.155/jura_kp/kpn/incbuild.php") 
#define GENISS_INCBUILD_URL   ((const unsigned char *)"http://serveri5.ll/jura_kp/kpn/incbuild.php") 
// #define GENISS_INCBUILD_FMT   (/* (const unsigned char *) */ "/jura/kpn/incbuild.php?ProdVer=%d&Comments=%s") 
#define GENISS_INCBUILD_FMT   (/* (const unsigned char *) */ "/jura_kp/kpn/incbuild.php?ProdVer=%d&Comments=%s") 

#define GENISS_INI_BUF_SIZE   10000

#define GENISS_XFS_HH_FNAME ((const unsigned char *)"tux_XFS\\include\\tux\\fs\\XFS.hh")
#define GENISS_EXE_FNAME (/* (const unsigned char *) */ "geniss.exe")
#define KP_CURDAT_CPP_FNAME (/* (const unsigned char *) */ "f:\\kp\\source\\common\\kpcurdat.cpp")

#define GENISS_SVR_OK ("Jura-Ok:")
#define GENISS_SVR_ERROR ("Jura-Error:")

// ------------------------------------
extern const unsigned char *YesNoKwds[];
extern const unsigned char *lpszaProdTypeKwds[ProdTypeCnt];

// ------------------------------------
extern unsigned char ProdName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdNameRaw[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdFNameRaw[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdFName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdDir[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdGroup[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char VerName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char Ver[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdVer[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdVerFlash[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProdVerNet[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char UpdVerName[GEN_CSS_STR_PAR_LEN + 1];
extern int UpdNum;
extern unsigned char PrevVerName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char PrevVer[GEN_CSS_STR_PAR_LEN + 1];
extern int PrevUpdNum;
extern int BuildNum;
extern unsigned char FirstVerName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char FirstVer[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char IconFName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char SetupFName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ExeFName[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char SvrFName[GEN_CSS_STR_PAR_LEN + 1];
extern bool AutoRun;
extern bool RequireAdmin;
extern bool PartialInstall;
extern bool PartialDir;
extern ProdTypes iProdType;
extern bool ChkUpd;
extern unsigned char Publisher[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char SplashBMP[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char StartPDF[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char Password[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char ProjID[GEN_CSS_STR_PAR_LEN + 1];
extern unsigned char Kalba[GEN_CSS_STR_PAR_LEN + 1];
extern int CidMode;


// ------------------------------------
extern HRESULT InitVars(void);
extern HRESULT ReadIniFile(void);
extern HRESULT DelHeadTailApost(unsigned char *lpszString);
extern HRESULT OutputGenIssBat(void);
extern HRESULT OutputFilesPl(GenIssTypes iGenType);
extern HRESULT OutputFilesBat(GenIssTypes iGenType);
extern HRESULT OutputGenBat(GenIssTypes iGenType);
extern HRESULT OutputGenIss(GenIssTypes iGenType);
extern HRESULT OutputKpstartIni(const unsigned char *lpszIniFName);
extern HRESULT GenXFS_XFS_hh(void);
extern HRESULT ScanXFS_XFS_hh(unsigned char *lpszXFSver); // lpszXFSver[GEN_CSS_STR_PAR_LEN + 1];
extern HRESULT GenXFS_tux_core_hh(void);
extern HRESULT GenXFS_Xipa_hh(void);
extern HRESULT GenXFS_XipaResource_rc(void);
extern HRESULT GenXFSTool_cfg(void);
extern HRESULT OutputGenLocalBat(const unsigned char *lpszBatName); // lpszBatName be uodegos "_local.bat"
extern HRESULT GetGenIssExeDate(unsigned char *lpszCommentsBuf); // lpszCommentsBuf[GEN_CSS_STR_PAR_LEN + 1]
extern HRESULT ScanKpCurDatCpp(unsigned char *lpszCommentsBuf); // lpszCommentsBuf[GEN_CSS_STR_PAR_LEN + 1]

#endif // #ifndef geniss_included
