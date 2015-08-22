// ===================================================
// geniss_lt.h
// Inno Setup scriptu generatorius
// lietuviski prane�imai
//


#ifndef geniss_lt_included
#define geniss_lt_included

#if TRUE // ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#define GENISS_MSG_START_PROG_LT          ((const unsigned char *)"Paleisti program�")
#define GENISS_MSG_UNSUCC_START_LT        ((const unsigned char *)"Nepavyko paleisti failo")
#define GENISS_MSG_PROG_NOT_ISTALLED_LT   ((const unsigned char *)"Programa �\' + GetFirstVerName + \'� dar ne�diegta")
#define GENISS_MSG_UPD_NOT_ISTALLED_LT    ((const unsigned char *) /* atnaujinimas */ "�\' + GetPrevVerName + \'� dar ne�diegtas")

// #define GENISS_MSG_RESTART_ADMIN_LT    ((const unsigned char *)"pabandykite prisijungti administratorium")
#define GENISS_MSG_RESTART_ADMIN_LT       ((const unsigned char *)"program� paleiskite i� naujo administratoriaus teis�mis")
#define GENISS_MSG_INST_ADMIN_LT          ((const unsigned char *)"Diegimui reikalingos administratoriaus teis�s")
#define GENISS_MSG_UNINST_ADMIN_LT        ((const unsigned char *)"Panaikinimui reikalingos administratoriaus teis�s")

#define GENISS_MSG_FLASH_PLAYER_LT        ((const unsigned char *)"Dabar bus �diegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus.")
#define GENISS_MSG_CABRI_LT               ((const unsigned char *)"Dabar bus �diegtas Cabri 3D �skiepis. Vykdykite tolesnius diegimo programos nurodymus.")

// #define GENISS_MSG_NAT_LET_TIT_LT      ((const unsigned char *)"Lietuvi�k� raid�i� naudojimas fail� varduose")
// #define GENISS_MSG_NAT_LET_MAIN_LT     ((const unsigned char *)"Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti, tik jei J�s� Windows operacin�je sistemoje nustatytos lietuvi�kos regiono parinktys, ir J�s nesiruo�iate j� keisti.")
// #define GENISS_MSG_NAT_LET_PROMPT_LT   ((const unsigned char *)"Naudoti lietuvi�kas raides fail� varduose")
// #define GENISS_MSG_NAT_LET_LT          ((const unsigned char *)"Ar norite naudoti lietuvi�kas raides fail� varduose? Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti tik tuo atveju, jei J�s� operacin�je sistemoje Windows nustatytos Lietuvos regiono parinktys, ir J�s nesiruo�iate j� keisti.")
#define GENISS_MSG_NAT_LET_LT             ((const unsigned char *)"Lietuvi�kas raides su diakritiniais �enklais (nosin�mis, pauk��iukais ir kt.) fail� varduose galima naudoti tik tuo atveju, jei J�s� operacin�je sistemoje Windows nustatytos Lietuvos regiono parinktys ir J�s nesiruo�iate j� keisti.\'+Chr(10)+Chr(10)+\'Ar norite tokias raides naudoti fail� varduose?")

#define GENISS_MSG_ATM_KOD_TIT_LT         ((const unsigned char *)"Atmintuko licencijos kodas")
#define GENISS_MSG_ATM_KOD_MAIN_LT        ((const unsigned char *)"�veskite atmintuko licencijos kod�.")
#define GENISS_MSG_ATM_KOD_PROMPT_LT      GENISS_MSG_ATM_KOD_TIT_LT

#define GENISS_MSG_CHK_UPD_TIT_LT         ((const unsigned char *)"Automatinis atnaujinim� tikrinimas")
#define GENISS_MSG_CHK_UPD_MAIN_LT        ((const unsigned char *)"I�valykite varnel�, jei nenorite, kad automati�kai internetu b�t� tikrinama, ar atsirado nauji programos pataisymai ar papildymai.")
#define GENISS_MSG_CHK_UPD_PROMPT_LT      GENISS_MSG_CHK_UPD_TIT_LT
    
// produkt� pavadinim� priesagos
#define GENISS_PROD_FLASH_LT              ((const unsigned char *)"atmintuke") // atmintukin� produkto versija
#define GENISS_PROD_LAN_LT                ((const unsigned char *)"tinkle") // tinklin� produkto versija
#define GENISS_PROD_SERVER_LT             ((const unsigned char *)"serveris") // produkto duomen�/licencij� serveris LAN-e   
 
// ikon�/katalog� pavadinimai ir j� priesagos
#define GENISS_LINK_OPTIONS_LT            ((const unsigned char *)"Parinktys")
// #define GENISS_LINK_REG_LT                ((const unsigned char *)"Registracija")
#define GENISS_LINK_REG_LT                ((const unsigned char *)"Aktyvacija")
#define GENISS_LINK_UNREG_LT              ((const unsigned char *)"Panaikinimas")
#define GENISS_LINK_FLASH_LT              GENISS_PROD_FLASH_LT
#define GENISS_LINK_FLASH_CHK_LT          ((const unsigned char *)"atmintuko tikrinimas")
#define GENISS_LINK_LAN_LT                GENISS_PROD_LAN_LT
#define GENISS_LINK_SERVER_LT             GENISS_PROD_SERVER_LT
#define GENISS_LINK_SERVER_MANAGEMENT_LT  ((const unsigned char *)"Serverio valdymas")
#define GENISS_LINK_CLEAN_NAT_LT          ((const unsigned char *)"Sen� rezultat� valymas")
#define GENISS_LINK_CLEAN_LAT_LT          ((const unsigned char *)"Senu rezultatu valymas")

#define GENISS_INSERT_FLASH_KEY_LT        ((const unsigned char *)"�ki�kite atmintuk� su programa ")

#define GENISS_LINK_DIAG_MSG_NAT_LT       ((const unsigned char *)"Diagnostinio prane�imo siuntimas")
#define GENISS_LINK_DIAG_MSG_LAT_LT       ((const unsigned char *)"Diagnostinio pranesimo siuntimas")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef geniss_lt_included
