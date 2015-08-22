// -----------------------------------------
// kpstedi_pl_1257.h
// kpstedi pranesimai
// lenkø kalba Windows Baltic
//

#ifndef kpstedi_pl_1257_included
#define kpstedi_pl_1257_included

#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#define KPSTEDI_INI_FILTER_NAME_PL_1257     ((const unsigned char *)"Pliki z parametrami")
#define KPSTEDI_INI_FILE_PROMPT_PL_1257     ((const unsigned char *)"Wybierz plik z parametrami")
#if (KPSTEDI_MODE & OWNER_MODE)
#  define KPSTEDI_USER_DATA_CHANGED_PL_1257 ((const unsigned char *)"Zmieniono hasùo i dane uýytkownika.") // "Hasùo i dane uýytkownika zostali zamienione.")
#else
#  define KPSTEDI_USER_DATA_CHANGED_PL_1257 ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_TAB_PROD_LT          (/* (const unsigned char *) */ "  Produktas  ")
#  define KPSTEDI_TAB_START_LT         (/* (const unsigned char *) */ "  Paleistis  ")
#  define KPSTEDI_TAB_BOUND_LT         (/* (const unsigned char *) */ "  Pririðimas  ")
#  define KPSTEDI_TAB_DATA_LT          (/* (const unsigned char *) */ "  Duomenys  ") // "  Rezultatai  ")
#  define KPSTEDI_TAB_OWNER_LT         (/* (const unsigned char *) */ "  Naudotojas  ") // "  Savininkas  ") // "  Vartotojas  ") // "  Vartotojo duomenys  ")
#else
#  define KPSTEDI_TAB_PROD_PL_1257          (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_START_PL_1257         (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_BOUND_PL_1257         (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_DATA_PL_1257          (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_OWNER_PL_1257         (/* (const unsigned char *) */ "")
#endif

#if ((KPSTEDI_MODE & STARTER_MODE) == 0) // && ((KPSTEDI_MODE & USER_MODE) == 0)
#  if KPSTEDI_MODE & OWNER_MODE
#     define KPSTEDI_TITLE_PL_1257     ((const unsigned char *)"Hasùo i dane uýytkownika")
#  else
#     define KPSTEDI_TITLE_LT          ((const unsigned char *)"Programos paleidimo parametrai")
#  endif      
#else
#  define KPSTEDI_TITLE_PL_1257             ((const unsigned char *)"")
#endif      

#if KPSTEDI_MODE & STARTER_MODE
#  define KPSTEDI_REZ_NOT_CLOSE_1_PL_1257   ((const unsigned char *)"Jeýeli aktualne okno siæ nie zamknie,")
#  define KPSTEDI_REZ_NOT_CLOSE_2_PL_1257   ((const unsigned char *)"spróbuj zmieniã nazwæ pliku z danymi")
#else
#  define KPSTEDI_REZ_NOT_CLOSE_1_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_REZ_NOT_CLOSE_2_PL_1257   ((const unsigned char *)"")
#endif

// Produktas
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_PROD_PROMPT_LT       ((const unsigned char *)"Produkto pavadinimas") // :")
#  define KPSTEDI_WNDNAME_PROMPT_LT    ((const unsigned char *)"Programos lango pavadinimas") // :")
#  define KPSTEDI_PUBL_PROMPT_LT       ((const unsigned char *)"Gamintojas") // :") // "Leidëjas:")
#  define KPSTEDI_PRODVER_PROMPT_LT    ((const unsigned char *)"Produktas/versija (VVPPP)") // :")
#  define KPSTEDI_UPDNUM_PROMPT_LT     ((const unsigned char *)"Atnaujinimo Nr. (ProdVar + 1)") // :")
#  define KPSTEDI_VOL_PROMPT_LT        ((const unsigned char *)"Kodinis pavadinimas") // :") // "Disko þymë:")
#  define KPSTEDI_VOL_PROMPT1_LT       ((const unsigned char *)"Naudojamas kaip:")
#  define KPSTEDI_VOL_PROMPT2_LT       ((const unsigned char *)"   - kompaktinio disko þymë;")
#  define KPSTEDI_VOL_PROMPT3_LT       ((const unsigned char *)"   - lokalaus duomenø serverio failo/serviso vardo pradþia (ðituo atveju turi bûti neilgesnis kaip 5 baitai);")
#  define KPSTEDI_VOL_PROMPT4_LT       ((const unsigned char *)"   - MIMOK Mano katalogo failø sàraðo .dat failo vardas be plëtinio; Mano_... katalogo vardo priesaga;")
#  define KPSTEDI_VOL_PROMPT5_LT       ((const unsigned char *)"   - StartSel.exe atmintuko pririðimo .ini failo vardas be plëtinio; = paleidimo .exe failo vardas.")
#else
#  define KPSTEDI_PROD_PROMPT_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_WNDNAME_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_PUBL_PROMPT_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_PRODVER_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_UPDNUM_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT_PL_1257        ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT1_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT2_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT3_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT4_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT5_PL_1257       ((const unsigned char *)"")
#endif

// Paleistis
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_CMD_STR_PROMPT_LT    ((const unsigned char *)"Paleidimo komanda") // :")
#  define KPSTEDI_CMD_STR_PROMPT1_LT   ((const unsigned char *)"Visos komandos gali bûti tiesiog failo vardas, kurio prievardþiui priskirta standartinë programa.")
#  define KPSTEDI_CMD_STR_PROMPT2_LT   ((const unsigned char *)"Paleidimo komandoje galima naudoti makrokomandas:")
#  define KPSTEDI_CMD_STR_PROMPT3_LT   ((const unsigned char *)"   {att} - sugeneruotas priekabos failo vardas su keliu, bet be prievardþio;")
#  define KPSTEDI_CMD_STR_PROMPT4_LT   ((const unsigned char *)"   {prog} - paleidëjo programos failo vardas (tik vardas, be kelio ir prievardþio);")
#  define KPSTEDI_CMD_STR_PROMPT5_LT   ((const unsigned char *)"   {user} - kelias iki katalogo, kuriame yra paleidþiamos programos katalogas;")
#  define KPSTEDI_CMD_STR_PROMPT6_LT   ((const unsigned char *)"      (vienu aukðtesnis katalogas, naudojamas dinaminiam paleidimui ið atmintukø).")
#  define KPSTEDI_ATTOFF_PROMPT_LT     ((const unsigned char *)"Priekabos pradþia") // :")
// #define KPSTEDI_ATTOFF_PROMPT1_LT   ((const unsigned char *)"Jei naudojama priekaba, jos failo vardas be prievardþio paleidimo komandoje þymimas %1,")
// #define KPSTEDI_ATTOFF_PROMPT2_LT   ((const unsigned char *)"pvz., jei priekabos prievardis exe, paleidimo komanda gali bûti \"%1.exe\".")
#  define KPSTEDI_ATTEXT_PROMPT_LT     ((const unsigned char *)"Priekabos prievardis") // :")
#  define KPSTEDI_PROL_PROMPT_LT       ((const unsigned char *)"Áþangos komanda") // :")
#  define KPSTEDI_PROL_TIME_PROMPT_LT  ((const unsigned char *)"Áþangos trukmë") // :")
#  define KPSTEDI_SEC_PROMPT_LT        ((const unsigned char *)"sec")
#  define KPSTEDI_BMP_PROMPT_LT        ((const unsigned char *)"Áþangos paveiksliukas") // :")
#  define KPSTEDI_BMP_SIZ_PROMPT_LT    ((const unsigned char *)"Paveiksliuko dydis") // :")
#  define KPSTEDI_TIMES_PROMPT_LT      ((const unsigned char *)"x")
#  define KPSTEDI_BMP_PIX_PROMPT_LT    ((const unsigned char *)"taðkø")
#  define KPSTEDI_MUTE_PROMPT_LT       ((const unsigned char *)"Garsas iðjungtas") // :")
#  define KPSTEDI_EPIL_PROMPT_LT       ((const unsigned char *)"Pabaigos komanda") // :")
#  define KPSTEDI_EPIL_TIME_PROMPT_LT  ((const unsigned char *)"Pabaigos trukmë") // :")
#  define KPSTEDI_ONTOP_PROMPT_LT      ((const unsigned char *)"Uþdrausti kitø programø paleidimà") // :")
#  define KPSTEDI_FULLSCR_PROMPT_LT    ((const unsigned char *)"Pilno ekrano reþimas") // :")
#  define KPSTEDI_CLRCLIPBRD_PROMPT_LT ((const unsigned char *)"Trinti iðkarpinæ") // :")
#  define KPSTEDI_SUBST_PROMPT_LT      ((const unsigned char *)"Paleisti virtualiame diske") // :")
#  define KPSTEDI_EBOARD_PROMPT_LT     ((const unsigned char *)"Elektroninë lenta") // :")
#  define KPSTEDI_SHIE_PROMPT_LT       ((const unsigned char *)"Paleisti IE") // :")
#  define KPSTEDI_HBMARKS_PROMPT_LT    ((const unsigned char *)"Slëpti bookmarkus") // :")
#  define KPSTEDI_SNDMUT_PROMPT_LT     ((const unsigned char *)"Garsas iðjungtas") // :")
#  define KPSTEDI_FINDBUT_PROMPT_LT    ((const unsigned char *)"Paieðkos mygtukas") // :")
#else
#  define KPSTEDI_CMD_STR_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT1_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT2_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT3_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT4_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT5_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT6_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_ATTOFF_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_ATTEXT_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_PROL_PROMPT_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_PROL_TIME_PROMPT_PL_1257  ((const unsigned char *)"")
#  define KPSTEDI_SEC_PROMPT_PL_1257        ((const unsigned char *)"")
#  define KPSTEDI_BMP_PROMPT_PL_1257        ((const unsigned char *)"")
#  define KPSTEDI_BMP_SIZ_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_TIMES_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_BMP_PIX_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_MUTE_PROMPT_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_EPIL_PROMPT_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_EPIL_TIME_PROMPT_PL_1257  ((const unsigned char *)"")
#  define KPSTEDI_ONTOP_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_FULLSCR_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CLRCLIPBRD_PROMPT_PL_1257 ((const unsigned char *)"")
#  define KPSTEDI_SUBST_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_EBOARD_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_SHIE_PROMPT_PL_1257       ((const unsigned char *)"")
#  define KPSTEDI_HBMARKS_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_SNDMUT_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_FINDBUT_PROMPT_PL_1257    ((const unsigned char *)"")
#endif

// Pririðimas
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_BOUND_PROMPT_LT      ((const unsigned char *)"Pririðti prie kompiuterio") // :")
#  define KPSTEDI_BOUND_PROMPT1_LT     ((const unsigned char *)"(lokalaus licencijø serverio)")
#  define KPSTEDI_CITYP_PROMPT_LT      ((const unsigned char *)"Kompiuterio ID:")
#  define KPSTEDI_CITYP_PROMPT_B_LT    ((const unsigned char *)"BIOS data")
#  define KPSTEDI_CITYP_PROMPT_D_LT    ((const unsigned char *)"HD Serijinis Nr.")
#  define KPSTEDI_CITYP_PROMPT_P_LT    ((const unsigned char *)"Procesoriaus ID")
#  define KPSTEDI_CITYP_PROMPT_N_LT    ((const unsigned char *)"Procesoriaus vardas")
#  define KPSTEDI_CITYP_PROMPT_M_LT    ((const unsigned char *)"MAC adresas")
#  define KPSTEDI_CITYP_PROMPT_V_LT    ((const unsigned char *)"Programinis „varþtas“")
#  define KPSTEDI_CIDIR_PROMPT_LT      ((const unsigned char *)"Kompiuterio ID skaityti:")
#  define KPSTEDI_CIDIR_PROMPT1_LT     ((const unsigned char *)"tiesiogiai ið HW")
#  define KPSTEDI_CIDIR_PROMPT2_LT     ((const unsigned char *)"ið slapto failo")
#else
#  define KPSTEDI_BOUND_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_BOUND_PROMPT1_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_B_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_D_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_P_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_N_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_M_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_V_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT1_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT2_PL_1257     ((const unsigned char *)"")
#endif

#if (KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)) && ((KPSTEDI_MODE & STARTER_MODE) == 0)
#  if KPSTEDI_MODE & USER_MODE
#     define KPSTEDI_REGURL_PROMPT_LT  ((const unsigned char *)"Serverio adresas") // :") 
#     define KPSTEDI_REGURL_PROMPT1_PL_1257 ((const unsigned char *)"")
#  else
#     define KPSTEDI_REGURL_PROMPT_LT  ((const unsigned char *)"Registravimosi URL arba")
#     define KPSTEDI_REGURL_PROMPT1_LT ((const unsigned char *)"lokalaus serverio adresas") // :")
#  endif                
#else
#  define KPSTEDI_REGURL_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_REGURL_PROMPT1_PL_1257    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_LICNUM_PROMPT_LT     ((const unsigned char *)"Lokaliø licencijø sk.") // :")
#  define KPSTEDI_BOUND_FL_PROMPT_LT   ((const unsigned char *)"Pririðti prie atmintuko") // :") // "Ar pririðti prie Flash'o:")
#else
#  define KPSTEDI_LICNUM_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_BOUND_FL_PROMPT_PL_1257   ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_FLASH_ID_PROMPT_LT   ((const unsigned char *)"Atmintuko ID") // :") // "Flash'o ID:"
#  define KPSTEDI_LIC_ID_PROMPT_LT     ((const unsigned char *)"Licencijos kodas") // :")
#  define KPSTEDI_LIC_ID_PROMPT1_LT    ((const unsigned char *)"Naudojamas produkto papildymo pririðimui prie konkreèios licencijos.")
#else
#  define KPSTEDI_FLASH_ID_PROMPT_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT1_PL_1257    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_PWD_WND_PROMPT_LT    ((const unsigned char *)"Slaptaþodþio/programos langas") // :")
#  define KPSTEDI_PWD_WND_PROMPT1_LT   ((const unsigned char *)"Atsiradus ðiam langui, stabdoma áþanga / naikinamas paveiksliukas.")
#  define KPSTEDI_PWD_PROMPT_LT        ((const unsigned char *)"Slaptaþodis") // :")
#  define KPSTEDI_OLD_PWD_PROMPT_LT    ((const unsigned char *)"Senas slaptaþodis") // :")
#  define KPSTEDI_PWD_EDIT_PROMPT_LT   ((const unsigned char *)"Slaptaþodþio ávedimo lauko id.") // :")
#  define KPSTEDI_PWD_BUT_PROMPT_LT    ((const unsigned char *)"Mygtuko „OK” id.") // :")
#  define KPSTEDI_CHCD_PROMPT_LT       ((const unsigned char *)"Reikalauti CD") // :")
#else
#  define KPSTEDI_PWD_WND_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_PWD_WND_PROMPT1_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_PWD_PROMPT_PL_1257        ((const unsigned char *)"")
#  define KPSTEDI_OLD_PWD_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_PWD_EDIT_PROMPT_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_PWD_BUT_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_CHCD_PROMPT_PL_1257       ((const unsigned char *)"")
#endif

// Duomenys
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_INI_PROMPT_LT        ((const unsigned char *)"Inicializavimo failas") // :")
#  define KPSTEDI_INI_PROMPT1_LT       ((const unsigned char *)"Jo turinys perkeliamas á iðkarpinæ prieð paleidþiant pagrindinæ komandà.")
#else
#  define KPSTEDI_INI_PROMPT_PL_1257        ((const unsigned char *)"")
#  define KPSTEDI_INI_PROMPT1_PL_1257       ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  define KPSTEDI_REZ_PROMPT_PL_1257        ((const unsigned char *)"Plik z wynikami")
#else
#  define KPSTEDI_REZ_PROMPT_PL_1257        ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_REZ_VAR_PROMPT_LT    ((const unsigned char *)"Rez. kintamieji") // :")
#  define KPSTEDI_SHUFF_PROMPT_LT      ((const unsigned char *)"Maiðomø laukø sk. (nedaugiau 9)") // :")
#  define KPSTEDI_CUMUL_PROMPT_LT      ((const unsigned char *)"Rezultatus prijungti prie jau esanèiø") // :") // "Ar duomenis kaupti:")
#  define KPSTEDI_TESTC_PROMPT_LT      ((const unsigned char *)"Testo identifikatorius") // :")
#else
#  define KPSTEDI_REZ_VAR_PROMPT_PL_1257    ((const unsigned char *)"")
#  define KPSTEDI_SHUFF_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_CUMUL_PROMPT_PL_1257      ((const unsigned char *)"")
#  define KPSTEDI_TESTC_PROMPT_PL_1257      ((const unsigned char *)"")
#endif

// Naudotojas
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
// #  if KPSTEDI_MODE & OWNER_MODE
#        if KPSTEDI_MODE & LOGIN_MODE
#           define KPSTEDI_USER_PWD_PROMPT_PL_1257   ((const unsigned char *)"Hasùo:")
#        else
#           define KPSTEDI_USER_PWD_PROMPT_PL_1257   ((const unsigned char *)"Hasùo")
#        endif
// #  else
// #     define KPSTEDI_USER_PWD_PROMPT_LT  ((const unsigned char *)"Paleidimo slaptaþodis") // :") 
// #  endif
#        define KPSTEDI_TESTUPD_PROMPT_LT    ((const unsigned char *)"Tikrinti atnaujinimus") // :")
#else
#        define KPSTEDI_USER_PWD_PROMPT_PL_1257  ((const unsigned char *)"")
#        define KPSTEDI_TESTUPD_PROMPT_PL_1257    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_REPEAT_PWD_PROMPT_PL_1257 ((const unsigned char *)"Powtórz hasùo")
#else
#  define KPSTEDI_REPEAT_PWD_PROMPT_PL_1257 ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_ADMIN_PWD_PROMPT_LT  ((const unsigned char *)"Atmintuko licencija") // :") // "Savininko slaptaþodis:") // "Informacijos keitimo slaptaþodis:") // "Redagavimo slaptaþodis:")
#  define KPSTEDI_NO_FLASH_LIC_LT      ((const unsigned char *)"Atmintuko licencija nenurodyta arba parametrai sukeisti vietomis")
#else
#  define KPSTEDI_ADMIN_PWD_PROMPT_PL_1257  ((const unsigned char *)"")
#  define KPSTEDI_NO_FLASH_LIC_PL_1257      ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
#  if KPSTEDI_MODE & LOGIN_MODE
#     define KPSTEDI_USER_DATA_PROMPT_PL_1257  ((const unsigned char *)"Uýytkownik:")
#  else
#     define KPSTEDI_USER_DATA_PROMPT_PL_1257  ((const unsigned char *)"Uýytkownik")
#  endif
#else
#  define KPSTEDI_USER_DATA_PROMPT_PL_1257  ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  define KPSTEDI_SEL_REZ_FILE_PL_1257      ((const unsigned char *)"Wybierz plik z wynikami")
#else
#  define KPSTEDI_SEL_REZ_FILE_PL_1257      ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_SURE_CHANGE_PWD_PL_1257    ((const unsigned char *)"Wprowadziùeú hasùo, które bædzie wymagane po kaýdym uruchomieniu programu.\n \nCzy wyraýasz na to zgodæ?")
#  define KPSTEDI_PWD_NOT_MATCH_PL_1257      ((const unsigned char *)"Hasùa nie sà identyczne.")
#else
#  define KPSTEDI_SURE_CHANGE_PWD_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_PWD_NOT_MATCH_PL_1257     ((const unsigned char *)"")
#endif
#  define KPSTEDI_USER_PWD_NOT_MATCH_PL_1257  KPSTEDI_PWD_NOT_MATCH_PL_1257 // ((const unsigned char *)"Paleidimo slaptaþodþiai nesutampa.")
// #define KPSTEDI_ADMIN_PWD_NOT_MATCH_PL_1257 KPSTEDI_PWD_NOT_MATCH_PL_1257 // ((const unsigned char *)"Redagavimo slaptaþodþiai nesutampa.")

#define KPSTEDI_REZ_FILES_PL_1257           ((const unsigned char *)"Pliki z wynikami (*.txt)") // "Pliki rezultatów (*.txt)"

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#endif // #ifndef kpstedi_pl_1257_included
