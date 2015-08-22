// -----------------------------------------
// kpmsg_lt.h
// programos paleidimo aplikaciju pranesimai
// liet. kalba
//

#ifndef kpmsg_lt_included
#define kpmsg_lt_included

// --------------------------------------- common kp messages

#if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

// #define KP_MSG_TITLE_LT          ((const unsigned char *)"KpMessage")
#define KP_MSG_TITLE_LT             ((const unsigned char *)"Praneðimas")
#define KP_INPUT_TITLE_LT           ((const unsigned char *)"Ávedimas")

#define KP_MSG_TAIP_LT              ((const unsigned char *)"Taip")
#define KP_MSG_YES_LT               KP_MSG_TAIP_LT
#define KP_MSG_NE_LT                ((const unsigned char *)"Ne")
#define KP_MSG_NO_LT                KP_MSG_NE_LT
#define KP_MSG_GERAI_LT             ((const unsigned char *)"Gerai")
#define KP_MSG_OK_LT                KP_MSG_GERAI_LT
#define KP_MSG_ATSAUKTI_LT          ((const unsigned char *)"Atðaukti")
#define KP_MSG_CANCEL_LT            KP_MSG_ATSAUKTI_LT
#define KP_MSG_TESTI_LT             ((const unsigned char *)"Toliau")
#define KP_MSG_BAIGTI_LT            ((const unsigned char *)"Baigti")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_LT ((const unsigned char *)"Pamirðau slaptaþodá")

#define KP_MSG_ERROR_LT             ((const unsigned char *)"Klaida")
#define KP_MSG_WARNING_LT           ((const unsigned char *)"Perspëjimas")
#define KP_MSG_FILE_LINE_LT         ((const unsigned char *)", klaida: %lx, failas: %s, eilutë: %d")
#define KP_MSG_ENTRY_ID_LT          ((const unsigned char *)", Áraðo nr.:%ld")
#define KP_MSG_ENTRY_LT             ((const unsigned char *)", Áraðas: %s")

#define KP_MSG_NO_STANDARD_PROG_LT  ((const unsigned char *)"Nerasta programa skirta atverti ðio tipo failus")
#define KP_MSG_WND_NOT_FOUND_LT     ((const unsigned char *)"Langas nerastas")
#define KP_MSG_PID_NOT_FOUND_LT     ((const unsigned char *)"Nerastas proceso identifikatorius")
#define KP_MSG_NO_SOCKET_LT         ((const unsigned char *)"Jungtis dar nesukurta")
#define KP_MSG_SOCK_UNRESOLVED_LT   ((const unsigned char *)"Tarnybines stoties adresas dar nesurastas")

#define KP_MSG_ERR_OK_LT            ((const unsigned char *)"Operacija atlikta sëkmingai") // !!!
#define KP_MSG_INVALIDARG_LT        ((const unsigned char *)"Neteisingi parametrai")
// #define KP_MSG_NOTIMPL_LT        ((const unsigned char *)"Priedas neádiegtas")
#define KP_MSG_NOTIMPL_LT           ((const unsigned char *)"Funkcija dar nerealizuota")
#define KP_MSG_UNEXPECTED_LT        ((const unsigned char *)"Netikëtas kreipinys á sàsajà")
#define KP_MSG_FERROR_LT            ((const unsigned char *)"Failo skaitymo/raðymo klaida")
#define KP_MSG_SYSTEM_ERROR_LT      ((const unsigned char *)"Klaida sistemoje")
#define KP_MSG_EOF_LT               ((const unsigned char *)"Neteisinga failo pabaiga")
#define KP_MSG_FILE_FORMAT_LT       ((const unsigned char *)"Neteisingas failo formatas")
#define KP_MSG_FILE_NOT_FOUND_LT    ((const unsigned char *)"Failas nerastas")
#define KP_MSG_DIR_ERROR_LT         ((const unsigned char *)"Nepavyko atverti/sukurti failo")
#define KP_MSG_OUTOFMEM_LT          ((const unsigned char *)"Trûksta atminties")
#define KP_MSG_NO_FILE_LT           ((const unsigned char *)"Failas neatvertas")
#define KP_MSG_DOUBLE_UNGET_LT      ((const unsigned char *)"Dvigubas ávedimo gràþinimas")
#define KP_MSG_UNKN_CHR_LT          ((const unsigned char *)"Neatpaþintas simbolis")
#define KP_MSG_COMMAND_ERROR_LT     ((const unsigned char *)"Iðorinë klaida")
#define KP_MSG_BUFFER_OVERFLOW_LT   ((const unsigned char *)"Persipildë buferis")
#define KP_MSG_FONT_UNDEF_LT        ((const unsigned char *)"Neapibrëþtas ðriftas")
#define KP_MSG_KWD_NOT_FOUND_LT     ((const unsigned char *)"Raktinis þodis nerastas")
#define KP_MSG_UNKNOWN_SYSTEM_LT    ((const unsigned char *)"Operacinë sistema neatpaþinta")
// #define KP_MSG_ILL_CODE_LT          ((const unsigned char *)"Klaidingas registracijos kodas")
#define KP_MSG_ILL_CODE_LT          ((const unsigned char *)"Klaidingas aktyvacijos kodas")
#define KP_MSG_CANCELLED_LT         ((const unsigned char *)"Operacija nutraukta")
#define KP_MSG_DOUBLE_CALL_LT       ((const unsigned char *)"Dvigubas iðkvietimas")
#define KP_MSG_TIMEOUT_LT           ((const unsigned char *)"Virðytas laukimo laikas")
#define KP_MSG_OBJ_NOT_FOUND_LT     ((const unsigned char *)"Objektas nerastas")
#define KP_MSG_NO_CONN_LT           ((const unsigned char *)"Tinklas neprijungtas") // "Nëra ryðio")

#define KP_MSG_TRANS_ERR_LT         ((const unsigned char *)"Perdavimo klaida")
#define KP_MSG_TRANS_ERR_1_LT       ((const unsigned char *)"Ryðio klaida, pakartokite siuntimo procedûrà")

// #define KP_MSG_REFUSED_LT           ((const unsigned char *)"Registracija atmesta")
#define KP_MSG_REFUSED_LT           ((const unsigned char *)"Aktyvacija atmesta")
#define KP_MSG_ACCESS_DENIED_LT     ((const unsigned char *)"Neleista prisijungti")
#define KP_MSG_ILLEGAL_CHARACTER_LT ((const unsigned char *)"Neleistinas simbolis")
#define KP_MSG_DIV_ZERO_LT          ((const unsigned char *)"Dalyba ið nulio")
#define KP_MSG_ILLMATHARG_LT        ((const unsigned char *)"Neleistinas matematinës funkcijos argumentas") // "Ðaknis ið neigiamo skaièiaus"
#define KP_MSG_ILLFUNC_LT           ((const unsigned char *)"Neleistina operacija") // illegal function call (at the moment)
                                      
// #define KP_MSG_NOTINST_LT        ((const unsigned char *)"Programa neádiegta arba diegimas sugedo, pakartokite diegimo procedûrà")
#define KP_MSG_NOTINST_LT           ((const unsigned char *)"Produktas neádiegtas arba jo diegimas sugedo, pakartokite diegimo procedûrà")
#define KP_MSG_NOTINST_S_LT         ((const unsigned char *)"Produktas „%s“ neádiegtas arba jo diegimas sugedo, pakartokite diegimo procedûrà")
#define KP_MSG_NOTINST_DELETE_LT    ((const unsigned char *)"Produktas neádiegtas arba jo diegimas sugedo. Produktà panaikinkite ir pakartokite diegimo procedûrà.")
                                      
#define KP_MSG_MSG_FORMAT_LT        ((const unsigned char *)"Neteisingas praneðimo formatas")
#define KP_MSG_OBSOLETE_LT          ((const unsigned char *)"Pasenusi funkcija")

// #define KP_MSG_ERROR_HELP_LT     ((const unsigned char *)".  Dël techninës pagalbos kreipkitës elektroniniu paðtu tech@tev.lt   Smulkesnë informacija faile %s")
// #define KP_MSG_ERROR_HELP_LT     ((const unsigned char *)".  Dël techninës pagalbos kreipkitës elektroniniu paðtu tech@tev.lt, prie laiðko prikabinkite failà %s")
// #define KP_MSG_ERROR_HELP_LT     ((const unsigned char *)".  Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu tech@tev.lt, prie laiðko prikabinkite failà %s")
#define KP_MSG_ERROR_HELP_LT        ((const unsigned char *)".  Dël techninës pagalbos kreipkitës elektroniniu paðtu, adresu pagalba@tev.lt")
#define KP_MSG_ERROR_HELP_REST_LT   ((const unsigned char *)"   Prie laiðko prikabinkite Jûsø darbalaukyje atsiradusá failà %s.")

#define KP_MSG_WSAEACCES_LT               ((const unsigned char *)"Teisës nesuteiktos")
#define KP_MSG_WSAEADDRINUSE_LT           ((const unsigned char *)"Adresas jau naudojamas")
#define KP_MSG_WSAEADDRNOTAVAIL_LT        ((const unsigned char *)"Praðomas adresas negali bûti priskirtas")
#define KP_MSG_WSAEAFNOSUPPORT_LT         ((const unsigned char *)"Adresø ðeimos grupë nepalaikoma protokolo")
#define KP_MSG_WSAEALREADY_LT             ((const unsigned char *)"Operacija jau vykdoma")
#define KP_MSG_WSAECONNABORTED_LT         ((const unsigned char *)"Programinis ryðio trûkis") // "Programa iððaukë ryðio nutraukimà")
#define KP_MSG_WSAECONNREFUSED_LT         ((const unsigned char *)"Susijungimas atmestas")
#define KP_MSG_WSAECONNRESET_LT           ((const unsigned char *)"Sujungimas nutrauktas")
#define KP_MSG_WSAEDESTADDRREQ_LT         ((const unsigned char *)"Bûtinas kreipties adresas")
#define KP_MSG_WSAEFAULT_LT               ((const unsigned char *)"Neteisingas adresas")
#define KP_MSG_WSAEHOSTDOWN_LT            ((const unsigned char *)"Tarnybinë stotis laikinai neveikia") // "Serveris laikinai neveikia")
#define KP_MSG_WSAEHOSTUNREACH_LT         ((const unsigned char *)"Tarnybinë stotis nepasiekiama") // "Serveris nepasiekiamas")
#define KP_MSG_WSAEINPROGRESS_LT          ((const unsigned char *)"Operacija vykdoma")
#define KP_MSG_WSAEINTR_LT                ((const unsigned char *)"Funkcija nutraukta")
#define KP_MSG_WSAEINVAL_LT               ((const unsigned char *)"Neteisingi parametrai")
#define KP_MSG_WSAEISCONN_LT              ((const unsigned char *)"Jungtis uþimta") // "Susijungimas jau ávykæs")
#define KP_MSG_WSAEMFILE_LT               ((const unsigned char *)"Perdaug atvertø failø")
#define KP_MSG_WSAEMSGSIZE_LT             ((const unsigned char *)"Perdaug ilgas praneðimas")
#define KP_MSG_WSAENETDOWN_LT             ((const unsigned char *)"Tinklas neveikia")
#define KP_MSG_WSAENETRESET_LT            ((const unsigned char *)"Tinklas atsijungë") // "Atsijungë nuo tinklo")
#define KP_MSG_WSAENETUNREACH_LT          ((const unsigned char *)"Tinklas nepasiekiamas")
#define KP_MSG_WSAENOBUFS_LT              ((const unsigned char *)"Trûksta vietos buferyje")
#define KP_MSG_WSAENOPROTOOPT_LT          ((const unsigned char *)"Neteisinga protokolo parinktis")
#define KP_MSG_WSAENOTCONN_LT             ((const unsigned char *)"Sujungimas nepavyko")
#define KP_MSG_WSAENOTSOCK_LT             ((const unsigned char *)"Jungties operacija ne jungèiai")
#define KP_MSG_WSAEOPNOTSUPP_LT           ((const unsigned char *)"Operacija negali bûti atlikta")
#define KP_MSG_WSAEPFNOSUPPORT_LT         ((const unsigned char *)"Protokolo ðeima nepalaikoma")
#define KP_MSG_WSAEPROCLIM_LT             ((const unsigned char *)"Per daug procesø")
#define KP_MSG_WSAEPROTONOSUPPORT_LT      ((const unsigned char *)"Protokolas nepalaikomas")
#define KP_MSG_WSAEPROTOTYPE_LT           ((const unsigned char *)"Neteisingas protokolo sujungimo tipas")
#define KP_MSG_WSAESHUTDOWN_LT            ((const unsigned char *)"Siuntimas nebegalimas, jungtis nutraukta") // "Siuntimas nebegalimas, sujungimas nutrauktas")
#define KP_MSG_WSAESOCKTNOSUPPORT_LT      ((const unsigned char *)"Sujungimo tipas nepalaikomas")
#define KP_MSG_WSAETIMEDOUT_LT            ((const unsigned char *)"Maksimalus sujungimo laukimo laikas virðytas")
#define KP_MSG_WSATYPE_NOT_FOUND_LT       ((const unsigned char *)"Klasës tipas nerastas")
#define KP_MSG_WSAEWOULDBLOCK_LT          ((const unsigned char *)"Ðaltinis laikinai nepasiekiamas")
#define KP_MSG_WSAHOST_NOT_FOUND_LT       ((const unsigned char *)"Tarnybinë stotis nerasta") // "Serveris nerastas")
#define KP_MSG_WSA_INVALID_HANDLE_LT      ((const unsigned char *)"Klaidingas objekto valdiklis") // "Klaidingas pasirinkto ávykio objekto valdiklis"
#define KP_MSG_WSA_INVALID_PARAMETER_LT   ((const unsigned char *)"Neteisingi parametrai") // "Neteisingi vienas ar daugiau parametrø"
#define KP_MSG_WSAINVALIDPROCTABLE_LT     ((const unsigned char *)"Klaidinga procedûrø lentelë")
#define KP_MSG_WSAINVALIDPROVIDER_LT      ((const unsigned char *)"Neteisingas tiekëjo kodas")
#define KP_MSG_WSA_IO_INCOMPLETE_LT       ((const unsigned char *)"Persiklojanèios ávesties/iðvesties ávykiai dar nepasibaigæ") // "Persiklojanèios ávesties/iðvesties ávykiai neaktyvûs") // "Persikloja ávesties/iðvesties ávykiai")
#define KP_MSG_WSA_IO_PENDING_LT          ((const unsigned char *)"Persiklojanèios operacijos bus atliktos vëliau")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_LT   ((const unsigned char *)"Nepakanka atminties")
#define KP_MSG_WSANOTINITIALISED_LT       ((const unsigned char *)"Tinklo posistemis neaktyvuotas")
#define KP_MSG_WSANO_DATA_LT              ((const unsigned char *)"Vardas teisingas, taèiau nëra reikiamo tipo duomenø")
#define KP_MSG_WSANO_RECOVERY_LT          ((const unsigned char *)"Nepataisoma klaida")
#define KP_MSG_WSAPROVIDERFAILEDINIT_LT   ((const unsigned char *)"Negalima inicializuoti paslaugos tiekëjo")
#define KP_MSG_WSASYSCALLFAILURE_LT       ((const unsigned char *)"Sistemos kreipinio klaida")
#define KP_MSG_WSASYSNOTREADY_LT          ((const unsigned char *)"Tinklo posistemë nepasiekiama")
#define KP_MSG_WSATRY_AGAIN_LT            ((const unsigned char *)"Nerasta neautorizuota tarnybinë stotis") // "Neautorizuotas serveris nerastas")
#define KP_MSG_WSAVERNOTSUPPORTED_LT      ((const unsigned char *)"Netinka WINSOCK.DLL versija")
#define KP_MSG_WSAEDISCON_LT              ((const unsigned char *)"Pradëtas tvarkingas iðjungimas") // ((const unsigned char *)"Pradëtas gracingas iðjungimas")
#define KP_MSG_WSA_OPERATION_ABORTED_LT   ((const unsigned char *)"Persiklojanti operacija nutraukta")

#define KP_MSG_OUT_OF_MEM_RES_LT          ((const unsigned char *)"Operacinei sistemai trûksta atminties")
#define KP_MSG_ERROR_FILE_NOT_FOUND_LT    ((const unsigned char *)"Nurodytas failas nerastas")
#define KP_MSG_ERROR_PATH_NOT_FOUND_LT    ((const unsigned char *)"Nurodytas kelias iki failø nerastas")
#define KP_MSG_ERROR_BAD_FORMAT_LT        ((const unsigned char *)"Pasirinktas .exe failas sugadintas")
#define KP_MSG_SE_ERR_ACCESSDENIED_LT     ((const unsigned char *)"Operacinë sistema uþdraudë prisijungimà prie reikiamø failø")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_LT  ((const unsigned char *)"Failo sàryðis su programa nepilnas arba neteisingas")
#define KP_MSG_SE_ERR_DDEBUSY_LT          ((const unsigned char *)"DDE transakcija negali bûti baigta, nes kitos DDE transakcijos dar vykdomos")
#define KP_MSG_SE_ERR_DDEFAIL_LT          ((const unsigned char *)"DDE transakcija nutraukta")
#define KP_MSG_SE_ERR_DDETIMEOUT_LT       ((const unsigned char *)"DDE transakcija negali bûti baigta, nes neuþteko nurodyto laukimo laiko")
#define KP_MSG_SE_ERR_DLLNOTFOUND_LT      ((const unsigned char *)"Nurodyta dinaminë biblioteka nerasta")
#define KP_MSG_SE_ERR_FNF_LT              ((const unsigned char *)"Nurodytas failas nerastas")
#define KP_MSG_SE_ERR_NOASSOC_LT          ((const unsigned char *)"Nerasta programa skirta atverti ðio tipo failus")
#define KP_MSG_SE_ERR_OOM_LT              ((const unsigned char *)"Nepakanka atminties atlikti operacijai")
#define KP_MSG_SE_ERR_PNF_LT              ((const unsigned char *)"Nurodytas kelias nerastas")
#define KP_MSG_SE_ERR_SHARE_LT            ((const unsigned char *)"Dalijimosi klaida")

// #define KP_MSG_FIRST_TIME_ADMIN_LT     ((const unsigned char *)"Programos paleidimui pirmà kartà reikalingos\n administratoriaus teisës")
// #define KP_MSG_FIRST_TIME_ADMIN_LT     ((const unsigned char *)"Programà paleiskite ið naujo administratoriaus teisëmis")
#define KP_MSG_FIRST_TIME_ADMIN_LT        ((const unsigned char *)"Programà paleidþiant pirmà kartà, reikalingos\n administratoriaus teisës. Paleiskite programà ið naujo\n administratoriaus teisëmis.")
#define KP_MSG_NOW_NOT_ADMIN_LT           KP_MSG_NOT_ADMIN_LT // ((const unsigned char *)"Dabar programà paleiskite dar kartà paprasto vartotojo teisëmis")
// #define KP_MSG_NOT_ADMIN_LT            ((const unsigned char *)"Programà paleiskite paprasto vartotojo teisëmis")
#define KP_MSG_NOT_ADMIN_LT               ((const unsigned char *)"Programà paleiskite ið naujo paprasto vartotojo teisëmis")
// #define KP_MSG_COPY_FILE_ACCESS_DENIED_LT ((const unsigned char *)"Failo nukopijuoti nepavyko, pabandykite prisijungti administratorium")
#define KP_MSG_COPY_FILE_ACCESS_DENIED_LT ((const unsigned char *)"Failo nukopijuoti nepavyko, programà paleiskite ið naujo administratoriaus teisëmis")

#define KP_PROGRESS_TITLE_LT              ((const unsigned char *)"Palaukite...")
#define KP_MSG_DELETING_FILE_LT           ((const unsigned char *)"Naikinamas failas %s.%s...")
#define KP_MSG_COPYING_LT                 ((const unsigned char *)"Kopijuojamas failas...")
#define KP_MSG_COPYING_FILE_LT            ((const unsigned char *)"Kopijuojamas failas %s.%s...")
#define KP_MSG_COPYING_DIR_LT             ((const unsigned char *)"Kopijuojamas aplankas %s.%s...")

#define KP_MSG_DOWNLOADING_LT             ((const unsigned char *)"Siunèiamas failas...")
#define KP_MSG_DOWNLOADING_FILE_LT        ((const unsigned char *)"Siunèiamas failas %s.%s...")

#define KP_MSG_NEG_ANSW_LT                ((const unsigned char *)"Neigiamas atsakymas")

#define KP_MSG_UNABLE_TO_EXECUTE_LT       ((const unsigned char *)"Komandos %s ávykdyti negaliu - patikrinkite, ar teisingai ádiegëte visus sistemos komponentus")

#define KP_MSG_FLASH_PLAYER_INSTALL_LT    ((const unsigned char *)"Dabar bus ádiegtas Macromedia Flash grotuvas. Vykdykite tolesnius diegimo programos nurodymus.")

#define KP_MSG_FILE_CHANGED_LT            ((const unsigned char *)"Failas pasikeitë")

#define KP_MSG_ALL_FILES_LT               ((const unsigned char *)"Visi failai (*.*)")
#define KP_MSG_SAVE_AS_LT                 ((const unsigned char *)"Áraðyti kaip")

#define KP_MSG_FILE_EXISTS_LT             ((const unsigned char *)"Failas %s jau yra, perraðyti?")

#define KP_MSG_DIAG_MSG_LT                ((const unsigned char *)"Formuojamas diagnostinis praneðimas")
#define KP_MSG_DIAG_MSG_TITLE_LT          ((const unsigned char *)"Diagnostinis praneðimas")

#if FALSE
#define KP_MSG_DIAG_MSG_EXPL_LT           ((const unsigned char *)"Jei norite nusiøsti diagnostiná praneðimà gamintojui, uþpildykite " \
                                                                  "pateiktus laukus. Praneðimas apie kompiuterio konfigûracijà, produktà " \
                                                                  "bei klaidos pobûdá bus iðsiøstas internetu á produkto gamintojo tarnybinæ " \
                                                                  "stotá. Jei po kurio laiko su Jumis nebus susisiekta Jûsø nurodytu paðto " \
                                                                  "adresu, kreipkitës adresu pagalba@tev.lt")
#endif
// #define KP_MSG_DIAG_MSG_EXPL_LT        ((const unsigned char *)"Jei norite nusiøsti diagnostiná praneðimà gamintojui, uþpildykite pateiktus laukus.")
#define KP_MSG_DIAG_MSG_EXPL_LT           ((const unsigned char *)"Jei turite problemø naudodami ðá produktà, gamintojui galite nusiøsti diagnostiná praneðimà. Uþpildykite pateiktus laukus.")
#define KP_MSG_DIAG_MSG_EXPL1_LT          ((const unsigned char *)"Jei norite siøsti diagnostiná praneðimà, spragtelëkite mygtukà „Siøsti“, jei ne – „Atðaukti“.")
#define KP_MSG_DIAG_MSG_EXPL2_LT          ((const unsigned char *)"Jei norite nusiøsti diagnostiná praneðimà gamintojui, uþpildykite Jûsø el. paðto adreso laukà ir spragtelëkite mygtukà „Siøsti“.")

#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_LT   ((const unsigned char *)"Jûsø el. paðto adresas:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_LT ((const unsigned char *)"Komentarai apie klaidos atsiradimo aplinkybes:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_LT    ((const unsigned char *)"Papildomas failas, kurá norëtumëte nusiøsti\n(pvz., ekrano kopijos paveikslëlis):")

#define KP_MSG_BAD_EMAIL_ADDRESS_LT       ((const unsigned char *)"Neteisingas el. paðto adresas")

#define KP_MSG_DIAG_MSG_SEL_FILE_LT       ((const unsigned char *)"Pasirinkite siunèiamà failà")

#define KP_MSG_DIAG_MSG_SUCCEEDED_LT      ((const unsigned char *)"Diagnostinis praneðimas nusiøstas sëkmingai")

#define KP_MSG_SIUSTI_LT                  ((const unsigned char *)"Siøsti")

#define KP_MSG_FIREWALL_LT                ((const unsigned char *)"Neleista prisijungti prie interneto. Patikrinkite Jûsø ugniasienës parinktis – pabandykite átraukti %s á sàraðà programø, kurioms leidþiama kreiptis á internetà.")

#define KP_MSG_POINTER_LT                 ((const unsigned char *)"Bloga rodyklë")

#define KP_MSG_LOG_STARTED_LT             ((const unsigned char *)"Þurnalas iðvedamas ir á failà %s")
#define KP_MSG_CONS_TITLE_LT              ((const unsigned char *)"%s: Praneðimø þurnalas") // ((const unsigned char *)"Pulto terminalas") // ((const unsigned char *)"Pultas")

#endif // #if ((MsgLang == KpLangSel_p) || (MsgLang == KpLangLt_p))

#endif // #ifndef kpmsg_lt_included
