// -----------------------------------------
// kpstedi_pl_1257.h
// kpstedi pranesimai
// lenk� kalba Windows Baltic
//

#ifndef kpstedi_pl_1257_included
#define kpstedi_pl_1257_included

#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#define KPSTEDI_INI_FILTER_NAME_PL_1257     ((const unsigned char *)"Pliki z parametrami")
#define KPSTEDI_INI_FILE_PROMPT_PL_1257     ((const unsigned char *)"Wybierz plik z parametrami")
#if (KPSTEDI_MODE & OWNER_MODE)
#  define KPSTEDI_USER_DATA_CHANGED_PL_1257 ((const unsigned char *)"Zmieniono has�o i dane u�ytkownika.") // "Has�o i dane u�ytkownika zostali zamienione.")
#else
#  define KPSTEDI_USER_DATA_CHANGED_PL_1257 ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_TAB_PROD_LT          (/* (const unsigned char *) */ "  Produktas  ")
#  define KPSTEDI_TAB_START_LT         (/* (const unsigned char *) */ "  Paleistis  ")
#  define KPSTEDI_TAB_BOUND_LT         (/* (const unsigned char *) */ "  Priri�imas  ")
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
#     define KPSTEDI_TITLE_PL_1257     ((const unsigned char *)"Has�o i dane u�ytkownika")
#  else
#     define KPSTEDI_TITLE_LT          ((const unsigned char *)"Programos paleidimo parametrai")
#  endif      
#else
#  define KPSTEDI_TITLE_PL_1257             ((const unsigned char *)"")
#endif      

#if KPSTEDI_MODE & STARTER_MODE
#  define KPSTEDI_REZ_NOT_CLOSE_1_PL_1257   ((const unsigned char *)"Je�eli aktualne okno si� nie zamknie,")
#  define KPSTEDI_REZ_NOT_CLOSE_2_PL_1257   ((const unsigned char *)"spr�buj zmieni� nazw� pliku z danymi")
#else
#  define KPSTEDI_REZ_NOT_CLOSE_1_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_REZ_NOT_CLOSE_2_PL_1257   ((const unsigned char *)"")
#endif

// Produktas
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_PROD_PROMPT_LT       ((const unsigned char *)"Produkto pavadinimas") // :")
#  define KPSTEDI_WNDNAME_PROMPT_LT    ((const unsigned char *)"Programos lango pavadinimas") // :")
#  define KPSTEDI_PUBL_PROMPT_LT       ((const unsigned char *)"Gamintojas") // :") // "Leid�jas:")
#  define KPSTEDI_PRODVER_PROMPT_LT    ((const unsigned char *)"Produktas/versija (VVPPP)") // :")
#  define KPSTEDI_UPDNUM_PROMPT_LT     ((const unsigned char *)"Atnaujinimo Nr. (ProdVar + 1)") // :")
#  define KPSTEDI_VOL_PROMPT_LT        ((const unsigned char *)"Kodinis pavadinimas") // :") // "Disko �ym�:")
#  define KPSTEDI_VOL_PROMPT1_LT       ((const unsigned char *)"Naudojamas kaip:")
#  define KPSTEDI_VOL_PROMPT2_LT       ((const unsigned char *)"   - kompaktinio disko �ym�;")
#  define KPSTEDI_VOL_PROMPT3_LT       ((const unsigned char *)"   - lokalaus duomen� serverio failo/serviso vardo prad�ia (�ituo atveju turi b�ti neilgesnis kaip 5 baitai);")
#  define KPSTEDI_VOL_PROMPT4_LT       ((const unsigned char *)"   - MIMOK Mano katalogo fail� s�ra�o .dat failo vardas be pl�tinio; Mano_... katalogo vardo priesaga;")
#  define KPSTEDI_VOL_PROMPT5_LT       ((const unsigned char *)"   - StartSel.exe atmintuko priri�imo .ini failo vardas be pl�tinio; = paleidimo .exe failo vardas.")
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
#  define KPSTEDI_CMD_STR_PROMPT1_LT   ((const unsigned char *)"Visos komandos gali b�ti tiesiog failo vardas, kurio prievard�iui priskirta standartin� programa.")
#  define KPSTEDI_CMD_STR_PROMPT2_LT   ((const unsigned char *)"Paleidimo komandoje galima naudoti makrokomandas:")
#  define KPSTEDI_CMD_STR_PROMPT3_LT   ((const unsigned char *)"   {att} - sugeneruotas priekabos failo vardas su keliu, bet be prievard�io;")
#  define KPSTEDI_CMD_STR_PROMPT4_LT   ((const unsigned char *)"   {prog} - paleid�jo programos failo vardas (tik vardas, be kelio ir prievard�io);")
#  define KPSTEDI_CMD_STR_PROMPT5_LT   ((const unsigned char *)"   {user} - kelias iki katalogo, kuriame yra paleid�iamos programos katalogas;")
#  define KPSTEDI_CMD_STR_PROMPT6_LT   ((const unsigned char *)"      (vienu auk�tesnis katalogas, naudojamas dinaminiam paleidimui i� atmintuk�).")
#  define KPSTEDI_ATTOFF_PROMPT_LT     ((const unsigned char *)"Priekabos prad�ia") // :")
// #define KPSTEDI_ATTOFF_PROMPT1_LT   ((const unsigned char *)"Jei naudojama priekaba, jos failo vardas be prievard�io paleidimo komandoje �ymimas %1,")
// #define KPSTEDI_ATTOFF_PROMPT2_LT   ((const unsigned char *)"pvz., jei priekabos prievardis exe, paleidimo komanda gali b�ti \"%1.exe\".")
#  define KPSTEDI_ATTEXT_PROMPT_LT     ((const unsigned char *)"Priekabos prievardis") // :")
#  define KPSTEDI_PROL_PROMPT_LT       ((const unsigned char *)"��angos komanda") // :")
#  define KPSTEDI_PROL_TIME_PROMPT_LT  ((const unsigned char *)"��angos trukm�") // :")
#  define KPSTEDI_SEC_PROMPT_LT        ((const unsigned char *)"sec")
#  define KPSTEDI_BMP_PROMPT_LT        ((const unsigned char *)"��angos paveiksliukas") // :")
#  define KPSTEDI_BMP_SIZ_PROMPT_LT    ((const unsigned char *)"Paveiksliuko dydis") // :")
#  define KPSTEDI_TIMES_PROMPT_LT      ((const unsigned char *)"x")
#  define KPSTEDI_BMP_PIX_PROMPT_LT    ((const unsigned char *)"ta�k�")
#  define KPSTEDI_MUTE_PROMPT_LT       ((const unsigned char *)"Garsas i�jungtas") // :")
#  define KPSTEDI_EPIL_PROMPT_LT       ((const unsigned char *)"Pabaigos komanda") // :")
#  define KPSTEDI_EPIL_TIME_PROMPT_LT  ((const unsigned char *)"Pabaigos trukm�") // :")
#  define KPSTEDI_ONTOP_PROMPT_LT      ((const unsigned char *)"U�drausti kit� program� paleidim�") // :")
#  define KPSTEDI_FULLSCR_PROMPT_LT    ((const unsigned char *)"Pilno ekrano re�imas") // :")
#  define KPSTEDI_CLRCLIPBRD_PROMPT_LT ((const unsigned char *)"Trinti i�karpin�") // :")
#  define KPSTEDI_SUBST_PROMPT_LT      ((const unsigned char *)"Paleisti virtualiame diske") // :")
#  define KPSTEDI_EBOARD_PROMPT_LT     ((const unsigned char *)"Elektronin� lenta") // :")
#  define KPSTEDI_SHIE_PROMPT_LT       ((const unsigned char *)"Paleisti IE") // :")
#  define KPSTEDI_HBMARKS_PROMPT_LT    ((const unsigned char *)"Sl�pti bookmarkus") // :")
#  define KPSTEDI_SNDMUT_PROMPT_LT     ((const unsigned char *)"Garsas i�jungtas") // :")
#  define KPSTEDI_FINDBUT_PROMPT_LT    ((const unsigned char *)"Paie�kos mygtukas") // :")
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

// Priri�imas
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_BOUND_PROMPT_LT      ((const unsigned char *)"Priri�ti prie kompiuterio") // :")
#  define KPSTEDI_BOUND_PROMPT1_LT     ((const unsigned char *)"(lokalaus licencij� serverio)")
#  define KPSTEDI_CITYP_PROMPT_LT      ((const unsigned char *)"Kompiuterio ID:")
#  define KPSTEDI_CITYP_PROMPT_B_LT    ((const unsigned char *)"BIOS data")
#  define KPSTEDI_CITYP_PROMPT_D_LT    ((const unsigned char *)"HD Serijinis Nr.")
#  define KPSTEDI_CITYP_PROMPT_P_LT    ((const unsigned char *)"Procesoriaus ID")
#  define KPSTEDI_CITYP_PROMPT_N_LT    ((const unsigned char *)"Procesoriaus vardas")
#  define KPSTEDI_CITYP_PROMPT_M_LT    ((const unsigned char *)"MAC adresas")
#  define KPSTEDI_CITYP_PROMPT_V_LT    ((const unsigned char *)"Programinis �var�tas�")
#  define KPSTEDI_CIDIR_PROMPT_LT      ((const unsigned char *)"Kompiuterio ID skaityti:")
#  define KPSTEDI_CIDIR_PROMPT1_LT     ((const unsigned char *)"tiesiogiai i� HW")
#  define KPSTEDI_CIDIR_PROMPT2_LT     ((const unsigned char *)"i� slapto failo")
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
#  define KPSTEDI_LICNUM_PROMPT_LT     ((const unsigned char *)"Lokali� licencij� sk.") // :")
#  define KPSTEDI_BOUND_FL_PROMPT_LT   ((const unsigned char *)"Priri�ti prie atmintuko") // :") // "Ar priri�ti prie Flash'o:")
#else
#  define KPSTEDI_LICNUM_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_BOUND_FL_PROMPT_PL_1257   ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_FLASH_ID_PROMPT_LT   ((const unsigned char *)"Atmintuko ID") // :") // "Flash'o ID:"
#  define KPSTEDI_LIC_ID_PROMPT_LT     ((const unsigned char *)"Licencijos kodas") // :")
#  define KPSTEDI_LIC_ID_PROMPT1_LT    ((const unsigned char *)"Naudojamas produkto papildymo priri�imui prie konkre�ios licencijos.")
#else
#  define KPSTEDI_FLASH_ID_PROMPT_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT_PL_1257     ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT1_PL_1257    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_PWD_WND_PROMPT_LT    ((const unsigned char *)"Slapta�od�io/programos langas") // :")
#  define KPSTEDI_PWD_WND_PROMPT1_LT   ((const unsigned char *)"Atsiradus �iam langui, stabdoma ��anga / naikinamas paveiksliukas.")
#  define KPSTEDI_PWD_PROMPT_LT        ((const unsigned char *)"Slapta�odis") // :")
#  define KPSTEDI_OLD_PWD_PROMPT_LT    ((const unsigned char *)"Senas slapta�odis") // :")
#  define KPSTEDI_PWD_EDIT_PROMPT_LT   ((const unsigned char *)"Slapta�od�io �vedimo lauko id.") // :")
#  define KPSTEDI_PWD_BUT_PROMPT_LT    ((const unsigned char *)"Mygtuko �OK� id.") // :")
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
#  define KPSTEDI_INI_PROMPT1_LT       ((const unsigned char *)"Jo turinys perkeliamas � i�karpin� prie� paleid�iant pagrindin� komand�.")
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
#  define KPSTEDI_SHUFF_PROMPT_LT      ((const unsigned char *)"Mai�om� lauk� sk. (nedaugiau 9)") // :")
#  define KPSTEDI_CUMUL_PROMPT_LT      ((const unsigned char *)"Rezultatus prijungti prie jau esan�i�") // :") // "Ar duomenis kaupti:")
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
#           define KPSTEDI_USER_PWD_PROMPT_PL_1257   ((const unsigned char *)"Has�o:")
#        else
#           define KPSTEDI_USER_PWD_PROMPT_PL_1257   ((const unsigned char *)"Has�o")
#        endif
// #  else
// #     define KPSTEDI_USER_PWD_PROMPT_LT  ((const unsigned char *)"Paleidimo slapta�odis") // :") 
// #  endif
#        define KPSTEDI_TESTUPD_PROMPT_LT    ((const unsigned char *)"Tikrinti atnaujinimus") // :")
#else
#        define KPSTEDI_USER_PWD_PROMPT_PL_1257  ((const unsigned char *)"")
#        define KPSTEDI_TESTUPD_PROMPT_PL_1257    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_REPEAT_PWD_PROMPT_PL_1257 ((const unsigned char *)"Powt�rz has�o")
#else
#  define KPSTEDI_REPEAT_PWD_PROMPT_PL_1257 ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_ADMIN_PWD_PROMPT_LT  ((const unsigned char *)"Atmintuko licencija") // :") // "Savininko slapta�odis:") // "Informacijos keitimo slapta�odis:") // "Redagavimo slapta�odis:")
#  define KPSTEDI_NO_FLASH_LIC_LT      ((const unsigned char *)"Atmintuko licencija nenurodyta arba parametrai sukeisti vietomis")
#else
#  define KPSTEDI_ADMIN_PWD_PROMPT_PL_1257  ((const unsigned char *)"")
#  define KPSTEDI_NO_FLASH_LIC_PL_1257      ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
#  if KPSTEDI_MODE & LOGIN_MODE
#     define KPSTEDI_USER_DATA_PROMPT_PL_1257  ((const unsigned char *)"U�ytkownik:")
#  else
#     define KPSTEDI_USER_DATA_PROMPT_PL_1257  ((const unsigned char *)"U�ytkownik")
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
#  define KPSTEDI_SURE_CHANGE_PWD_PL_1257    ((const unsigned char *)"Wprowadzi�e� has�o, kt�re b�dzie wymagane po ka�dym uruchomieniu programu.\n \nCzy wyra�asz na to zgod�?")
#  define KPSTEDI_PWD_NOT_MATCH_PL_1257      ((const unsigned char *)"Has�a nie s� identyczne.")
#else
#  define KPSTEDI_SURE_CHANGE_PWD_PL_1257   ((const unsigned char *)"")
#  define KPSTEDI_PWD_NOT_MATCH_PL_1257     ((const unsigned char *)"")
#endif
#  define KPSTEDI_USER_PWD_NOT_MATCH_PL_1257  KPSTEDI_PWD_NOT_MATCH_PL_1257 // ((const unsigned char *)"Paleidimo slapta�od�iai nesutampa.")
// #define KPSTEDI_ADMIN_PWD_NOT_MATCH_PL_1257 KPSTEDI_PWD_NOT_MATCH_PL_1257 // ((const unsigned char *)"Redagavimo slapta�od�iai nesutampa.")

#define KPSTEDI_REZ_FILES_PL_1257           ((const unsigned char *)"Pliki z wynikami (*.txt)") // "Pliki rezultat�w (*.txt)"

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#endif // #ifndef kpstedi_pl_1257_included
