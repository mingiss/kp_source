// -----------------------------------------
// kpstedi_lt.h
// kpstedi pranesimai
// liet. kalba
//

#ifndef kpstedi_lt_included
#define kpstedi_lt_included

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#define KPSTEDI_INI_FILTER_NAME_LT     ((const unsigned char *)"Parametr� failai") // "Ini failai" 
#define KPSTEDI_INI_FILE_PROMPT_LT     ((const unsigned char *)"Pasirinkite parametr� fail�") // "Pasirinkite ini fail�"
#if (KPSTEDI_MODE & OWNER_MODE)
#  define KPSTEDI_USER_DATA_CHANGED_LT ((const unsigned char *)"Slapta�odis ir naudotojo duomenys s�kmingai pakeisti.")
#else
#  define KPSTEDI_USER_DATA_CHANGED_LT ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_TAB_PROD_LT          (/* (const unsigned char *) */ "  Produktas  ")
#  define KPSTEDI_TAB_START_LT         (/* (const unsigned char *) */ "  Paleistis  ")
#  define KPSTEDI_TAB_BOUND_LT         (/* (const unsigned char *) */ "  Priri�imas  ")
#  define KPSTEDI_TAB_DATA_LT          (/* (const unsigned char *) */ "  Duomenys  ") // "  Rezultatai  ")
#  define KPSTEDI_TAB_OWNER_LT         (/* (const unsigned char *) */ "  Naudotojas  ") // "  Savininkas  ") // "  Vartotojas  ") // "  Vartotojo duomenys  ")
#else
#  define KPSTEDI_TAB_PROD_LT          (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_START_LT         (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_BOUND_LT         (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_DATA_LT          (/* (const unsigned char *) */ "")
#  define KPSTEDI_TAB_OWNER_LT         (/* (const unsigned char *) */ "")
#endif

#if ((KPSTEDI_MODE & STARTER_MODE) == 0) // && ((KPSTEDI_MODE & USER_MODE) == 0)
#  if KPSTEDI_MODE & OWNER_MODE
#     if KPSTEDI_MODE & LOGIN_MODE
// #     define KPSTEDI_TITLE_LT          ((const unsigned char *)"�veskite savo prisijungimo prie vartotoj� sistemos duomenis.")
#        define KPSTEDI_TITLE_LT          ((const unsigned char *)"�veskite savo prisijungimo duomenis.")
#     else
#        define KPSTEDI_TITLE_LT          ((const unsigned char *)"Naudotojo duomenys ir slapta�odis") // "Savininko duomenys") // "Vartotojo duomenys")
#     endif
#  else
#     define KPSTEDI_TITLE_LT          ((const unsigned char *)"Programos paleidimo parametrai")
#  endif      
#else
#  define KPSTEDI_TITLE_LT             ((const unsigned char *)"")
#endif      

#if KPSTEDI_MODE & STARTER_MODE
#  define KPSTEDI_REZ_NOT_CLOSE_1_LT   ((const unsigned char *)"Jei �is langas neu�sidarys,")
#  define KPSTEDI_REZ_NOT_CLOSE_2_LT   ((const unsigned char *)"pabandykite pakeisti duomen� failo vard�") // rinkmenos
#else
#  define KPSTEDI_REZ_NOT_CLOSE_1_LT   ((const unsigned char *)"")
#  define KPSTEDI_REZ_NOT_CLOSE_2_LT   ((const unsigned char *)"")
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
#  define KPSTEDI_PROD_PROMPT_LT       ((const unsigned char *)"")
#  define KPSTEDI_WNDNAME_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_PUBL_PROMPT_LT       ((const unsigned char *)"")
#  define KPSTEDI_PRODVER_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_UPDNUM_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT_LT        ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT1_LT       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT2_LT       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT3_LT       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT4_LT       ((const unsigned char *)"")
#  define KPSTEDI_VOL_PROMPT5_LT       ((const unsigned char *)"")
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
#  define KPSTEDI_CMD_STR_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT1_LT   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT2_LT   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT3_LT   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT4_LT   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT5_LT   ((const unsigned char *)"")
#  define KPSTEDI_CMD_STR_PROMPT6_LT   ((const unsigned char *)"")
#  define KPSTEDI_ATTOFF_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_ATTEXT_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_PROL_PROMPT_LT       ((const unsigned char *)"")
#  define KPSTEDI_PROL_TIME_PROMPT_LT  ((const unsigned char *)"")
#  define KPSTEDI_SEC_PROMPT_LT        ((const unsigned char *)"")
#  define KPSTEDI_BMP_PROMPT_LT        ((const unsigned char *)"")
#  define KPSTEDI_BMP_SIZ_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_TIMES_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_BMP_PIX_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_MUTE_PROMPT_LT       ((const unsigned char *)"")
#  define KPSTEDI_EPIL_PROMPT_LT       ((const unsigned char *)"")
#  define KPSTEDI_EPIL_TIME_PROMPT_LT  ((const unsigned char *)"")
#  define KPSTEDI_ONTOP_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_FULLSCR_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_CLRCLIPBRD_PROMPT_LT ((const unsigned char *)"")
#  define KPSTEDI_SUBST_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_EBOARD_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_SHIE_PROMPT_LT       ((const unsigned char *)"")
#  define KPSTEDI_HBMARKS_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_SNDMUT_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_FINDBUT_PROMPT_LT    ((const unsigned char *)"")
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
#  define KPSTEDI_BOUND_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_BOUND_PROMPT1_LT     ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_B_LT    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_D_LT    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_P_LT    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_N_LT    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_M_LT    ((const unsigned char *)"")
#  define KPSTEDI_CITYP_PROMPT_V_LT    ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT1_LT     ((const unsigned char *)"")
#  define KPSTEDI_CIDIR_PROMPT2_LT     ((const unsigned char *)"")
#endif

#if (KPSTEDI_MODE & (GENERAL_MODE | USER_MODE)) && ((KPSTEDI_MODE & STARTER_MODE) == 0)
#  if KPSTEDI_MODE & USER_MODE
#     define KPSTEDI_REGURL_PROMPT_LT  ((const unsigned char *)"Serverio adresas") // :") 
#     define KPSTEDI_REGURL_PROMPT1_LT ((const unsigned char *)"")
#  else
// #     define KPSTEDI_REGURL_PROMPT_LT  ((const unsigned char *)"Registravimosi URL arba")
#     define KPSTEDI_REGURL_PROMPT_LT  ((const unsigned char *)"Aktyvavimo URL arba")
#     define KPSTEDI_REGURL_PROMPT1_LT ((const unsigned char *)"lokalaus serverio adresas") // :")
#  endif                
#else
#  define KPSTEDI_REGURL_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_REGURL_PROMPT1_LT    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_LICNUM_PROMPT_LT     ((const unsigned char *)"Lokali� licencij� sk.") // :")
#  define KPSTEDI_BOUND_FL_PROMPT_LT   ((const unsigned char *)"Priri�ti prie atmintuko") // :") // "Ar priri�ti prie Flash'o:")
#  define KPSTEDI_LIC_FL_PROMPT_LT     ((const unsigned char *)"Licencijuotas atmintukas")
#else
#  define KPSTEDI_LICNUM_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_BOUND_FL_PROMPT_LT   ((const unsigned char *)"")
#  define KPSTEDI_LIC_FL_PROMPT_LT     ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_FLASH_ID_PROMPT_LT   ((const unsigned char *)"Atmintuko ID") // :") // "Flash'o ID:"
#  define KPSTEDI_LIC_ID_PROMPT_LT     ((const unsigned char *)"Licencijos kodas") // :")
#  define KPSTEDI_LIC_ID_PROMPT1_LT    ((const unsigned char *)"Naudojamas produkto papildymo priri�imui prie konkre�ios licencijos.")
#else
#  define KPSTEDI_FLASH_ID_PROMPT_LT   ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT_LT     ((const unsigned char *)"")
#  define KPSTEDI_LIC_ID_PROMPT1_LT    ((const unsigned char *)"")
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
#  define KPSTEDI_PWD_WND_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_PWD_WND_PROMPT1_LT   ((const unsigned char *)"")
#  define KPSTEDI_PWD_PROMPT_LT        ((const unsigned char *)"")
#  define KPSTEDI_OLD_PWD_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_PWD_EDIT_PROMPT_LT   ((const unsigned char *)"")
#  define KPSTEDI_PWD_BUT_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_CHCD_PROMPT_LT       ((const unsigned char *)"")
#endif

// Duomenys
#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_INI_PROMPT_LT        ((const unsigned char *)"Inicializavimo failas") // :")
#  define KPSTEDI_INI_PROMPT1_LT       ((const unsigned char *)"Jo turinys perkeliamas � i�karpin� prie� paleid�iant pagrindin� komand�.")
#else
#  define KPSTEDI_INI_PROMPT_LT        ((const unsigned char *)"")
#  define KPSTEDI_INI_PROMPT1_LT       ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  define KPSTEDI_REZ_PROMPT_LT        ((const unsigned char *)"Rezultat� failas") // :")
#else
#  define KPSTEDI_REZ_PROMPT_LT        ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & GENERAL_MODE
#  define KPSTEDI_REZ_VAR_PROMPT_LT    ((const unsigned char *)"Rez. kintamieji") // :")
#  define KPSTEDI_SHUFF_PROMPT_LT      ((const unsigned char *)"Mai�om� lauk� sk. (nedaugiau 9)") // :")
#  define KPSTEDI_CUMUL_PROMPT_LT      ((const unsigned char *)"Rezultatus prijungti prie jau esan�i�") // :") // "Ar duomenis kaupti:")
#  define KPSTEDI_TESTC_PROMPT_LT      ((const unsigned char *)"Testo identifikatorius") // :")
#else
#  define KPSTEDI_REZ_VAR_PROMPT_LT    ((const unsigned char *)"")
#  define KPSTEDI_SHUFF_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_CUMUL_PROMPT_LT      ((const unsigned char *)"")
#  define KPSTEDI_TESTC_PROMPT_LT      ((const unsigned char *)"")
#endif

// Naudotojas
#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE)
// #  if KPSTEDI_MODE & OWNER_MODE
#        if KPSTEDI_MODE & LOGIN_MODE
#           define KPSTEDI_USER_PWD_PROMPT_LT  ((const unsigned char *)"Slapta�odis:")
#        else
#           define KPSTEDI_USER_PWD_PROMPT_LT  ((const unsigned char *)"Slapta�odis") // :")
#        endif
// #  else
// #     define KPSTEDI_USER_PWD_PROMPT_LT  ((const unsigned char *)"Paleidimo slapta�odis") // :") 
// #  endif
#  define KPSTEDI_TESTUPD_PROMPT_LT    ((const unsigned char *)"Tikrinti atnaujinimus") // :")
#else
#  define KPSTEDI_USER_PWD_PROMPT_LT  ((const unsigned char *)"")
#  define KPSTEDI_TESTUPD_PROMPT_LT    ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
#  define KPSTEDI_REPEAT_PWD_PROMPT_LT ((const unsigned char *)"Pakartokite slapta�od�") // :")
#else
#  define KPSTEDI_REPEAT_PWD_PROMPT_LT ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | BOUND_MODE)
#  define KPSTEDI_ADMIN_PWD_PROMPT_LT  ((const unsigned char *)"Atmintuko licencija") // :") // "Savininko slapta�odis:") // "Informacijos keitimo slapta�odis:") // "Redagavimo slapta�odis:")
#  define KPSTEDI_NO_FLASH_LIC_LT      ((const unsigned char *)"Atmintuko licencija nenurodyta arba parametrai sukeisti vietomis")
#else
#  define KPSTEDI_ADMIN_PWD_PROMPT_LT  ((const unsigned char *)"")
#  define KPSTEDI_NO_FLASH_LIC_LT      ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | OWNER_MODE | BOUND_MODE)
#  if KPSTEDI_MODE & LOGIN_MODE
#     define KPSTEDI_USER_DATA_PROMPT_LT  ((const unsigned char *)"Vartotojas:")
#  else
#     define KPSTEDI_USER_DATA_PROMPT_LT  ((const unsigned char *)"Naudotojas") // "Naudotojo vardas:") // "Savininko vardas:") // "Savininko informacija:")
#  endif
#else
#  define KPSTEDI_USER_DATA_PROMPT_LT  ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & (GENERAL_MODE | USER_MODE | STARTER_MODE)
#  define KPSTEDI_SEL_REZ_FILE_LT      ((const unsigned char *)"Pasirinkite rezultat� fail�") // rinkmen�")
#else
#  define KPSTEDI_SEL_REZ_FILE_LT      ((const unsigned char *)"")
#endif

#if KPSTEDI_MODE & OWNER_MODE
// #  define KPSTEDI_SURE_CHANGE_PWD_LT   ((const unsigned char *)"J�s �ved�te paleidimo slapta�od�. Jo bus reikalaujama kiekvieno programos paleidimo metu.\n \nAr sutinkate?") // ka�kod�l "\n\n" netinka - �r. CalcMsgPars()
#  define KPSTEDI_SURE_CHANGE_PWD_LT   ((const unsigned char *)"J�s pakeit�te vartotojo duomenis ar paleidimo slapta�od�.")
#  define KPSTEDI_PWD_NOT_MATCH_LT     ((const unsigned char *)"Slapta�od�iai nesutampa.")
#else
#  define KPSTEDI_SURE_CHANGE_PWD_LT   ((const unsigned char *)"")
#  define KPSTEDI_PWD_NOT_MATCH_LT     ((const unsigned char *)"")
#endif
#  define KPSTEDI_USER_PWD_NOT_MATCH_LT  KPSTEDI_PWD_NOT_MATCH_LT // ((const unsigned char *)"Paleidimo slapta�od�iai nesutampa.")
// #define KPSTEDI_ADMIN_PWD_NOT_MATCH_LT KPSTEDI_PWD_NOT_MATCH_LT // ((const unsigned char *)"Redagavimo slapta�od�iai nesutampa.")

#define KPSTEDI_REZ_FILES_LT           ((const unsigned char *)"Rezultat� failai (*.txt)")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef kpstedi_lt_included
