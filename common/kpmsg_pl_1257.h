// -----------------------------------------
// kpmsg_pl_1257.h
// programos paleidimo aplikaciju pranesimai
// lenkø kalba Windows Baltic
//

#ifndef kpmsg_pl_1257_included
#define kpmsg_pl_1257_included

// --------------------------------------- common kp messages
#if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#define KP_MSG_TITLE_PL_1257              ((const unsigned char *)"Komunikat")
#define KP_INPUT_TITLE_PL_1257            ((const unsigned char *)"Wprowadzanie")

#define KP_MSG_TAIP_PL_1257               ((const unsigned char *)"Tak")
#define KP_MSG_YES_PL_1257                KP_MSG_TAIP_PL_1257
#define KP_MSG_NE_PL_1257                 ((const unsigned char *)"Nie")
#define KP_MSG_NO_PL_1257                 KP_MSG_NE_PL_1257
#define KP_MSG_GERAI_PL_1257              ((const unsigned char *)"Dobrze")
#define KP_MSG_OK_PL_1257                 KP_MSG_GERAI_PL_1257
#define KP_MSG_ATSAUKTI_PL_1257           ((const unsigned char *)"Odwoùaj")
#define KP_MSG_CANCEL_PL_1257             KP_MSG_ATSAUKTI_PL_1257
#define KP_MSG_TESTI_PL_1257              ((const unsigned char *)"Dalej")
#define KP_MSG_BAIGTI_PL_1257             ((const unsigned char *)"Zakoñcz")
#define KP_MSG_PAMIRSAU_SLAPTAZODI_PL_1257 ((const unsigned char *)"Zapomniaùem hasùo")

#define KP_MSG_ERROR_PL_1257              ((const unsigned char *)"Bùàd")
#define KP_MSG_WARNING_PL_1257            ((const unsigned char *)"Ostrzeýenie")
#define KP_MSG_FILE_LINE_PL_1257          ((const unsigned char *)", bùàd: %lx, plik: %s, linijka: %d")
#define KP_MSG_ENTRY_ID_PL_1257           ((const unsigned char *)", Nr. wpisu:%ld")
#define KP_MSG_ENTRY_PL_1257              ((const unsigned char *)", Wpis: %s")

#define KP_MSG_NO_STANDARD_PROG_PL_1257   ((const unsigned char *)"Nie znaleziono programu do otwierania plików tego typu")
#define KP_MSG_WND_NOT_FOUND_PL_1257      ((const unsigned char *)"Nie znaleziono okna")
#define KP_MSG_PID_NOT_FOUND_PL_1257      ((const unsigned char *)"Nie znaleziono indentyfikatora procesu")
#define KP_MSG_NO_SOCKET_PL_1257          ((const unsigned char *)"Wiæê jeszcze nie stworzona")
#define KP_MSG_SOCK_UNRESOLVED_PL_1257    ((const unsigned char *)"Nie znaleziono adresu stacji sùuýbowej")

#define KP_MSG_ERR_OK_PL_1257             ((const unsigned char *)"Operacja wykonana")
#define KP_MSG_INVALIDARG_PL_1257         ((const unsigned char *)"Bùædne parametry")
#define KP_MSG_NOTIMPL_PL_1257            ((const unsigned char *)"Wùaúciwoúã jeszcze nie zrealizowana")
#define KP_MSG_UNEXPECTED_PL_1257         ((const unsigned char *)"Nieoczekiwny zwrot do interfejsu")
#define KP_MSG_FERROR_PL_1257             ((const unsigned char *)"Bùàd sczytywania/zapisywania pliku")
#define KP_MSG_SYSTEM_ERROR_PL_1257       ((const unsigned char *)"Bùàd systemu")
#define KP_MSG_EOF_PL_1257                ((const unsigned char *)"Nieprawidùowe zakoñczenie pliku")
#define KP_MSG_FILE_FORMAT_PL_1257        ((const unsigned char *)"Nieprawidùowy format pliku")
#define KP_MSG_FILE_NOT_FOUND_PL_1257     ((const unsigned char *)"Nie znaleziono pliku")
#define KP_MSG_DIR_ERROR_PL_1257          ((const unsigned char *)"Nie udaùo siæ otworzyã/stworzyã pliku")
#define KP_MSG_OUTOFMEM_PL_1257           ((const unsigned char *)"Niewystarcza pamiæci")
#define KP_MSG_NO_FILE_PL_1257            ((const unsigned char *)"Nie otworzono pliku")
#define KP_MSG_DOUBLE_UNGET_PL_1257       ((const unsigned char *)"Podwójny unget")
#define KP_MSG_UNKN_CHR_PL_1257           ((const unsigned char *)"Nierozpoznano symbol")
#define KP_MSG_COMMAND_ERROR_PL_1257      ((const unsigned char *)"Bùàd zewnætrzny")
                                             
#define KP_MSG_BUFFER_OVERFLOW_PL_1257    ((const unsigned char *)"Przepeùniony bufor")
#define KP_MSG_FONT_UNDEF_PL_1257         ((const unsigned char *)"Nieokreúlono szryft")
#define KP_MSG_KWD_NOT_FOUND_PL_1257      ((const unsigned char *)"Nie znaleziono kluczowego sùowa")
#define KP_MSG_UNKNOWN_SYSTEM_PL_1257     ((const unsigned char *)"Nie rozpoznano systemu operacyjnego")
// #define KP_MSG_ILL_CODE_PL_1257           ((const unsigned char *)"Bùædny kod rejestracji")
#define KP_MSG_ILL_CODE_PL_1257           ((const unsigned char *)"Bùædny kod aktywacji")
                                            
#define KP_MSG_CANCELLED_PL_1257          ((const unsigned char *)"Przerwano operacjæ")
#define KP_MSG_DOUBLE_CALL_PL_1257        ((const unsigned char *)"Podwójne wywoùanie")
#define KP_MSG_TIMEOUT_PL_1257            ((const unsigned char *)"Przekroczono czas oczekiwania")
#define KP_MSG_OBJ_NOT_FOUND_PL_1257      ((const unsigned char *)"Nie znaleziono objektu")
                                            
#define KP_MSG_NO_CONN_PL_1257            ((const unsigned char *)"Nie ma ùàcznoúci")

#define KP_MSG_TRANS_ERR_PL_1257          ((const unsigned char *)"Bùàd przekazu")
#define KP_MSG_TRANS_ERR_1_PL_1257        ((const unsigned char *)"Bùàd przekazu. Zapuszczaj wysyùanie ponownie")

// #define KP_MSG_REFUSED_PL_1257            ((const unsigned char *)"Odrzucono rejestracjæ")
#define KP_MSG_REFUSED_PL_1257            ((const unsigned char *)"Odrzucono aktywacjæ")
#define KP_MSG_ACCESS_DENIED_PL_1257      ((const unsigned char *)"Ùàcznoúã niedozwolona")
#define KP_MSG_ILLEGAL_CHARACTER_PL_1257  ((const unsigned char *)"Niedopuszczalny symbol")
#define KP_MSG_DIV_ZERO_PL_1257           ((const unsigned char *)"Dzielenie przez zero")
#define KP_MSG_ILLMATHARG_PL_1257         ((const unsigned char *)"Niedopuszczalny argument matematycznej funkcji")
#define KP_MSG_ILLFUNC_PL_1257            ((const unsigned char *)"Niedopuszczalna operacja")

#define KP_MSG_NOTINST_PL_1257            ((const unsigned char *)"Program nie zainstalowany lub zepsuta instalacja. Zainstaluj ponownie.")
#define KP_MSG_NOTINST_S_PL_1257          ((const unsigned char *)"Program „%s” nie zainstalowany lub zepsuta instalacja. Zainstaluj ponownie.")
#define KP_MSG_NOTINST_DELETE_PL_1257     ((const unsigned char *)"Program nie zainstalowany lub zepsuta instalacja. Odinstaluj i zainstaluj produkt ponownie.")

#define KP_MSG_MSG_FORMAT_PL_1257         ((const unsigned char *)"Bùædny format komunikatu")
#define KP_MSG_OBSOLETE_PL_1257           ((const unsigned char *)"Stara funkcja")
                                            
// #define KP_MSG_ERROR_HELP_PL_1257      ((const unsigned char *)".  Po pomoc technicznà zwróã siæ pod adres tech@tev.lt. Do listu zaùàcz plik %s")
#define KP_MSG_ERROR_HELP_PL_1257         ((const unsigned char *)".  Po pomoc technicznà zwróã siæ pod adres pagalba@tev.lt")
#define KP_MSG_ERROR_HELP_REST_PL_1257    ((const unsigned char *)"   Do listu zaùàcz plik %s z Twego pulpitu.")
                                             
#define KP_MSG_WSAEACCES_PL_1257               ((const unsigned char *)"Nie masz uprawnienia")
#define KP_MSG_WSAEADDRINUSE_PL_1257           ((const unsigned char *)"Adres jest juý wykorzystany")
#define KP_MSG_WSAEADDRNOTAVAIL_PL_1257        ((const unsigned char *)"Wskazany adres nie moýe byã przyùàczony")
#define KP_MSG_WSAEAFNOSUPPORT_PL_1257         ((const unsigned char *)"Grupa adresów nie podtrzymywana przez protokóù")
#define KP_MSG_WSAEALREADY_PL_1257             ((const unsigned char *)"Operacja juý jest wykonywana")
#define KP_MSG_WSAECONNABORTED_PL_1257         ((const unsigned char *)"Program wywoùaù rozerwanie poùàczenia")
#define KP_MSG_WSAECONNREFUSED_PL_1257         ((const unsigned char *)"Poùàczenie zostaùo odrzucone")

#define KP_MSG_WSAECONNRESET_PL_1257           ((const unsigned char *)"Poùàczenie zostaùo rozerwane")
#define KP_MSG_WSAEDESTADDRREQ_PL_1257         ((const unsigned char *)"Wymagany jest adres")
#define KP_MSG_WSAEFAULT_PL_1257               ((const unsigned char *)"Bùædny adres")

#define KP_MSG_WSAEHOSTDOWN_PL_1257            ((const unsigned char *)"Serwer czasowo niedostæpny")
#define KP_MSG_WSAEHOSTUNREACH_PL_1257         ((const unsigned char *)"Serwer jest nieosiàgalny")
#define KP_MSG_WSAEINPROGRESS_PL_1257          ((const unsigned char *)"Operacja jest wykonywana")
#define KP_MSG_WSAEINTR_PL_1257                ((const unsigned char *)"Funkcja zostaùa przerwana")

#define KP_MSG_WSAEINVAL_PL_1257               ((const unsigned char *)"Bùædne parametry")
#define KP_MSG_WSAEISCONN_PL_1257              ((const unsigned char *)"Poùàczenie juý jest nawiàzane")
#define KP_MSG_WSAEMFILE_PL_1257               ((const unsigned char *)"Otworzono za duýo plików")

#define KP_MSG_WSAEMSGSIZE_PL_1257             ((const unsigned char *)"Zbyt dùugi komunikat")
#define KP_MSG_WSAENETDOWN_PL_1257             ((const unsigned char *)"Sieã nie dziaùa")
#define KP_MSG_WSAENETRESET_PL_1257            ((const unsigned char *)"Odùàczono siæ od sieci")

#define KP_MSG_WSAENETUNREACH_PL_1257          ((const unsigned char *)"Sieã nieosiàgalna")
#define KP_MSG_WSAENOBUFS_PL_1257              ((const unsigned char *)"Brakuje miejsca w buforze")
#define KP_MSG_WSAENOPROTOOPT_PL_1257          ((const unsigned char *)"Bùædne opcje protokoùu")

#define KP_MSG_WSAENOTCONN_PL_1257             ((const unsigned char *)"Nieudane poùàczenie")
#define KP_MSG_WSAENOTSOCK_PL_1257             ((const unsigned char *)"Socket operation on non-socket")
#define KP_MSG_WSAEOPNOTSUPP_PL_1257           ((const unsigned char *)"Operacja nie moýe byã wykonana")

#define KP_MSG_WSAEPFNOSUPPORT_PL_1257         ((const unsigned char *)"Niepodtrzymywana rodzina protokoùów")
#define KP_MSG_WSAEPROCLIM_PL_1257             ((const unsigned char *)"Zbyt duýo procesów")
#define KP_MSG_WSAEPROTONOSUPPORT_PL_1257      ((const unsigned char *)"Protokóù nie jest podtrzymywany")

#define KP_MSG_WSAEPROTOTYPE_PL_1257           ((const unsigned char *)"Nieprawidùowy typ poùàczenia protokoùu")
#define KP_MSG_WSAESHUTDOWN_PL_1257            ((const unsigned char *)"Wysyùanie niemoýliwe, poùàczenie zerwane")
#define KP_MSG_WSAESOCKTNOSUPPORT_PL_1257      ((const unsigned char *)"Typ poùàczenia niepodtrzymywany")
#define KP_MSG_WSAETIMEDOUT_PL_1257            ((const unsigned char *)"Przewyýszono maksymalny czas oczekiwania poùàczenia")

#define KP_MSG_WSATYPE_NOT_FOUND_PL_1257       ((const unsigned char *)"Nie znaleziono typ klasy")
#define KP_MSG_WSAEWOULDBLOCK_PL_1257          ((const unsigned char *)"Êródùo czasowo niedostæpne")
#define KP_MSG_WSAHOST_NOT_FOUND_PL_1257       ((const unsigned char *)"Nie znaleziono serweru")
#define KP_MSG_WSA_INVALID_HANDLE_PL_1257      ((const unsigned char *)"Bùædny kontroler objektu")
#define KP_MSG_WSA_INVALID_PARAMETER_PL_1257   ((const unsigned char *)"Bùædne parametry")
#define KP_MSG_WSAINVALIDPROCTABLE_PL_1257     ((const unsigned char *)"Bùædna tablica procedur")
#define KP_MSG_WSAINVALIDPROVIDER_PL_1257      ((const unsigned char *)"Bùædny kod dostawcy")
#define KP_MSG_WSA_IO_INCOMPLETE_PL_1257       ((const unsigned char *)"Nakùadajà siæ zdarzenia wprowdzania/wyprowadzania")
#define KP_MSG_WSA_IO_PENDING_PL_1257          ((const unsigned char *)"Nakùadajàce siæ operacje bædà wykonane póêniej")

#define KP_MSG_WSA_NOT_ENOUGH_MEMORY_PL_1257   ((const unsigned char *)"Brak pamiæci")
#define KP_MSG_WSANOTINITIALISED_PL_1257       ((const unsigned char *)"Podsystem sieci nieaktywowany")
#define KP_MSG_WSANO_DATA_PL_1257              ((const unsigned char *)"Nie ma danych wymaganego typu")
#define KP_MSG_WSANO_RECOVERY_PL_1257          ((const unsigned char *)"Nienaprawialny bùàd")
#define KP_MSG_WSAPROVIDERFAILEDINIT_PL_1257   ((const unsigned char *)"Nie moýliwa jest inicjacja dostawcy usùugi")
#define KP_MSG_WSASYSCALLFAILURE_PL_1257       ((const unsigned char *)"Bùædny zwrot systemu")
#define KP_MSG_WSASYSNOTREADY_PL_1257          ((const unsigned char *)"Podsystem sieci nieosiàgalny")
#define KP_MSG_WSATRY_AGAIN_PL_1257            ((const unsigned char *)"Nieautoryzowany serwer nie znaleziony")

#define KP_MSG_WSAVERNOTSUPPORTED_PL_1257      ((const unsigned char *)"Bùædna wersja WINSOCK.DLL")
#define KP_MSG_WSAEDISCON_PL_1257              ((const unsigned char *)"Rozpoczæto porzàdne wyùàczanie")
#define KP_MSG_WSA_OPERATION_ABORTED_PL_1257   ((const unsigned char *)"Nakùadajàca siæ operacja przerwana")

#define KP_MSG_OUT_OF_MEM_RES_PL_1257          ((const unsigned char *)"Brak pamiæci systemu operacyjnego")
#define KP_MSG_ERROR_FILE_NOT_FOUND_PL_1257    ((const unsigned char *)"Nie znaleziono wskazanego pliku")
#define KP_MSG_ERROR_PATH_NOT_FOUND_PL_1257    ((const unsigned char *)"Nie znaleziono wskazanej úcieýki do pliku")
#define KP_MSG_ERROR_BAD_FORMAT_PL_1257        ((const unsigned char *)"Wybrany plik .exe jest zepsuty")
#define KP_MSG_SE_ERR_ACCESSDENIED_PL_1257     ((const unsigned char *)"System operacyjny zabroniù ùàcznoúci z potrzebnymi plikami")
#define KP_MSG_SE_ERR_ASSOCINCOMPLETE_PL_1257  ((const unsigned char *)"Wiæê pliku z programem jest niepeùna lub bùædna")
#define KP_MSG_SE_ERR_DDEBUSY_PL_1257          ((const unsigned char *)"DDE transakcja nie moýe byã zakoñczona, bo inne DDE transakcje sà jeszcze wykonywane")
#define KP_MSG_SE_ERR_DDEFAIL_PL_1257          ((const unsigned char *)"DDE transakcja przerwana")
#define KP_MSG_SE_ERR_DDETIMEOUT_PL_1257       ((const unsigned char *)"DDE transakcja nie moýe byã zakoñczona, bo zabrakùo wskazanego czasu oczekiwania")
#define KP_MSG_SE_ERR_DLLNOTFOUND_PL_1257      ((const unsigned char *)"Nie znaleziono wskazanej biblioteki dynamicznej")
#define KP_MSG_SE_ERR_FNF_PL_1257              ((const unsigned char *)"Nie znaleziono wskazanego pliku")
#define KP_MSG_SE_ERR_NOASSOC_PL_1257          ((const unsigned char *)"Nie znaleziono programu do otwarcia plików danego typu")

#define KP_MSG_SE_ERR_OOM_PL_1257              ((const unsigned char *)"Brak pamiæci do wykonania operacji")
#define KP_MSG_SE_ERR_PNF_PL_1257              ((const unsigned char *)"Nie znaleziono wskazanej úcieýki")
#define KP_MSG_SE_ERR_SHARE_PL_1257            ((const unsigned char *)"Bùàd podziaùu")

#define KP_MSG_FIRST_TIME_ADMIN_PL_1257        ((const unsigned char *)"Zapuszczajàc program poraz pierwszy wymagane sà uprawnienia administratora. Zapuúã program ponownie z uprawnieniami administratora.")

#define KP_MSG_NOW_NOT_ADMIN_PL_1257           KP_MSG_NOT_ADMIN_PL_1257
#define KP_MSG_NOT_ADMIN_PL_1257               ((const unsigned char *)"Zapuúã program ponownie z uprawnieniami zwykùego uýytkownika")

#define KP_MSG_COPY_FILE_ACCESS_DENIED_PL_1257 ((const unsigned char *)"Nie udaùo siæ skopiowaã pliku. Zapuúã program ponownie z uprawnieniami administratora.")


#define KP_PROGRESS_TITLE_PL_1257               ((const unsigned char *)"Zaczekaj...")
#define KP_MSG_DELETING_FILE_PL_1257            ((const unsigned char *)"Kasuje siæ plik %s.%s...")

#define KP_MSG_COPYING_PL_1257                  ((const unsigned char *)"Kopiuje siæ plik...")

#define KP_MSG_COPYING_DIR_PL_1257              ((const unsigned char *)"Kopiuje siæ katalog %s.%s...")
#define KP_MSG_COPYING_FILE_PL_1257             ((const unsigned char *)"Kopiuje siæ plik %s.%s...")

// TODO: iðversti
#define KP_MSG_DOWNLOADING_PL_1257              ((const unsigned char *)"Siunèiamas failas...")
#define KP_MSG_DOWNLOADING_FILE_PL_1257         ((const unsigned char *)"Siunèiamas failas %s.%s...")

#define KP_MSG_NEG_ANSW_PL_1257                 ((const unsigned char *)"Odpowiedê negatywna")

#define KP_MSG_UNABLE_TO_EXECUTE_PL_1257        ((const unsigned char *)"Polecenie %s nie moýe byã wykonane, sprawdê, czy prawidùowo sà zainstalowane wszystkie komponenty systemowe")

#define KP_MSG_FLASH_PLAYER_INSTALL_PL_1257     ((const unsigned char *)"Nastæpnie bædzie zainstalowany \"Macromedia Flash player\". Wykonuj dalsze polecenia instalatora.")

#define KP_MSG_FILE_CHANGED_PL_1257             ((const unsigned char *)"Plik zostaù zmieniony")

#define KP_MSG_ALL_FILES_PL_1257                ((const unsigned char *)"Wszystkie pliki (*.*)")
#define KP_MSG_SAVE_AS_PL_1257                  ((const unsigned char *)"Zapisz jako")

#define KP_MSG_FILE_EXISTS_PL_1257              ((const unsigned char *)"Plik %s juý istnieje, czy chcesz go zastàpiã?")

#define KP_MSG_DIAG_MSG_PL_1257                 ((const unsigned char *)"Formowanie wiadomoúci diagnostycznej")
#define KP_MSG_DIAG_MSG_TITLE_PL_1257           ((const unsigned char *)"Wiadomoúã diagnostyczna")

#if FALSE
#define KP_MSG_DIAG_MSG_EXPL_PL_1257            ((const unsigned char *)"Jeúli chcesz producentowi wysùaã wiadomoúã diagnostycznà, wypeùnij dane " \
                                                                        "pola. Wiadomoúã o konfiguracji komputera, produkcie oraz naturze bùædu " \
                                                                        "bædzie wysùana na serwer producenta. Jeýeli w krótkim czasie nie otrzymasz " \
                                                                        "odpowiedzi na swój podany e-mail, skontatuj siæ z producentem piszàc na " \
                                                                        "adres pagalba@tev.lt")
#endif
#define KP_MSG_DIAG_MSG_EXPL_PL_1257            ((const unsigned char *)"Jeúli chcesz producentowi wysùaã wiadomoúã diagnostycznà, wypeùnij dane pola.")

#define KP_MSG_DIAG_MSG_EXPL1_PL_1257          ((const unsigned char *)"Jeúli chcesz wysùaã wiadomoúã diagnostycznà kliknij przycisk „Wyúlij”, jeúli nie – „Odwoùaj”.")
#define KP_MSG_DIAG_MSG_EXPL2_PL_1257          ((const unsigned char *)"Jeúli chcesz wysùaã wiadomoúã diagnostycznà producentowi, wpisz swój adres e-mail w odpowiednie pole i kliknij przycisk „Wyúlij”.")

#define KP_MSG_DIAG_MSG_EMAIL_PROMPT_PL_1257    ((const unsigned char *)"Twój e-mail:")
#define KP_MSG_DIAG_MSG_COMMENTS_PROMPT_PL_1257 ((const unsigned char *)"Komentarze o okolicznoúciach wystàpienia bùædu:")
#define KP_MSG_DIAG_MSG_FILE_PROMPT_PL_1257     ((const unsigned char *)"Dodatkowy plik, kóry chciaùbyú doùàczyã\n(np. zrzut ekranu):")

#define KP_MSG_BAD_EMAIL_ADDRESS_PL_1257        ((const unsigned char *)"Nieprawidùowy adres e-mail")

#define KP_MSG_DIAG_MSG_SEL_FILE_PL_1257        ((const unsigned char *)"Wybierz plik do wysùania")

// #define KP_MSG_DIAG_MSG_SUCCEEDED_PL_1257       ((const unsigned char *)"Wiadomoc diagnostyczna zostaùa wysùana")
#define KP_MSG_DIAG_MSG_SUCCEEDED_PL_1257       ((const unsigned char *)"Wiadomoúã diagnostyczna zostaùa wysùana")

#define KP_MSG_SIUSTI_PL_1257                   ((const unsigned char *)"Wyúlij")

#define KP_MSG_FIREWALL_PL_1257                 ((const unsigned char *)"Nie ma dostæpu do Internetu. Sprawdê ustawienia swojej zapory sieciowej – spróbuj wciàgnàã %s do listy zaufanych programów, którym dozwolone jest zwracanie siæ do internetu.")

#define KP_MSG_POINTER_PL_1257                  ((const unsigned char *)"Bùàd wskaênika")

// TODO: iðversti
#define KP_MSG_LOG_STARTED_PL_1257             ((const unsigned char *)"Þurnalas iðvedamas ir á failà %s")
#define KP_MSG_CONS_TITLE_PL_1257              ((const unsigned char *)"%s: Praneðimø þurnalas") // ((const unsigned char *)"Pulto terminalas") // ((const unsigned char *)"Pultas")

#endif // #if ((MsgLang == KpLangPl_p) || (MsgLang == KpLangSel_p) || (MsgLang == KpLangPl_1257_p))

#endif // #ifndef kpmsg_pl_1257_included
